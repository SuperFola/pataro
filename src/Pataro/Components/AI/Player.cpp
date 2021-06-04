#include <Pataro/Components/AI/Player.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Container.hpp>
#include <Pataro/Actions/Move.hpp>
#include <Pataro/Actions/Attack.hpp>
#include <Pataro/Actions/PickUp.hpp>
#include <Pataro/Actions/Use.hpp>

using namespace pat::component::details;

std::unique_ptr<pat::Action> PlayerAI::update(pat::Entity* owner, pat::Engine* engine)
{
    // do nothing if we're dead
    if (Destructible* d = owner->destructible(); d != nullptr && d->is_dead())
    {
        engine->change_state(pat::GameState::Defeat);
        return nullptr;
    }

    int dx = 0,
        dy = 0;
    std::unique_ptr<pat::Action> action;

    switch (engine->lastkey().vk)
    {
        case TCODK_UP:    --dy; break;
        case TCODK_DOWN:  ++dy; break;
        case TCODK_LEFT:  --dx; break;
        case TCODK_RIGHT: ++dx; break;

        case TCODK_CHAR:
            action = handle_action_key(owner, engine, engine->lastkey().c);
            break;

        default:
            break;
    }

    if (dy != 0 || dx != 0)
    {
        engine->change_state(pat::GameState::NewTurn);
        engine->log("turn");
        return std::make_unique<pat::MoveAction>(owner, dx, dy);
    }
    else if (action)
    {
        engine->change_state(pat::GameState::NewTurn);
        engine->log("turn");
        return action;
    }

    return nullptr;
}

std::unique_ptr<pat::Action> PlayerAI::handle_action_key(pat::Entity* owner, pat::Engine* engine, int ascii)
{
    switch (ascii)
    {
        // pick an item
        case 'g':
            return std::make_unique<pat::PickUpAction>(owner, owner->get_x(), owner->get_y());

        // display inventory
        case 'i':
        {
            Entity* e = choose_from_inventory(owner, engine);
            if (e != nullptr)
                return std::make_unique<pat::UseAction>(owner, e);
            break;
        }
    }

    return nullptr;
}

pat::Entity* PlayerAI::choose_from_inventory(pat::Entity* owner, pat::Engine* engine)
{
    // TODO put this in Pataro/Gui/Inventory
    static const int INVENTORY_WIDTH = 50,
                     INVENTORY_HEIGHT = 28;
    static TCODConsole con(INVENTORY_WIDTH, INVENTORY_HEIGHT);
    con.setDefaultForeground(TCODColor(200, 180, 50));
    con.printFrame(0, 0, INVENTORY_WIDTH, INVENTORY_HEIGHT, true, TCOD_BKGND_DEFAULT, "inventory");

    // display the items with their keyboard shortcut
    con.setDefaultForeground(TCODColor::white);
    int y = 1;
    Container& c = *owner->container();

    for (std::size_t i = 0, end = c.size(); i < end; ++i)
    {
        con.printf(2, y, "(%c) %s", 'a' + y - 1, c[i].get_name().c_str());
        y++;
    }

    TCODConsole::blit(
        &con, 0, 0, INVENTORY_WIDTH, INVENTORY_HEIGHT,
        TCODConsole::root,
        engine->width() / 2 - INVENTORY_WIDTH / 2,
        engine->height() / 2 - INVENTORY_HEIGHT / 2
    );
    TCODConsole::flush();

    // wait for a key press
    TCOD_key_t key;
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr, true);

    if (key.vk == TCODK_CHAR)
    {
        int idx = key.c - 'a';
        if (0 <= idx && idx < c.size())
            return c.ptr_at(idx);
    }

    return nullptr;
}

PlayerAI* PlayerAI::clone_impl() const
{
    return new PlayerAI(*this);
}