#include <Pataro/Components/AI/Player.hpp>

#include <Pataro/Entity.hpp>
#include <Pataro/Engine.hpp>
#include <Pataro/Colors.hpp>
#include <Pataro/Constants.hpp>
#include <Pataro/Components/Destructible.hpp>
#include <Pataro/Components/Inventory.hpp>

#include <Pataro/Actions/Move.hpp>
#include <Pataro/Actions/Attack.hpp>
#include <Pataro/Actions/PickUp.hpp>
#include <Pataro/Actions/Use.hpp>
#include <Pataro/Actions/Drop.hpp>

#include <SDL2/SDL_keycode.h>

using namespace pat::component;

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

    switch (engine->lastkey())
    {
        case SDLK_UP:    --dy; break;
        case SDLK_DOWN:  ++dy; break;
        case SDLK_LEFT:  --dx; break;
        case SDLK_RIGHT: ++dx; break;

        default:
            action = handle_action_key(owner, engine, engine->lastkey());
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

std::unique_ptr<pat::Action> PlayerAI::handle_action_key(pat::Entity* owner, pat::Engine* engine, int keycode)
{
    // TODO find a way to make the keycode customisable
    switch (keycode)
    {
        // pick an item
        case SDLK_g:
            return std::make_unique<pat::PickUpAction>(owner, owner->get_x(), owner->get_y());

        // display inventory
        case SDLK_i:
        {
            Entity* e = choose_from_inventory(owner, engine);
            if (e != nullptr)
                return std::make_unique<pat::UseAction>(owner, e);
            break;
        }

        // drop an object
        case SDLK_d:
        {
            Entity* e = choose_from_inventory(owner, engine);
            if (e != nullptr)
                return std::make_unique<pat::DropAction>(owner, e);
            break;
        }

        default:
            break;
    }

    return nullptr;
}

// TODO: this shouldn't be here, we are doing some kind of rendering and event loop
pat::Entity* PlayerAI::choose_from_inventory(pat::Entity* owner, pat::Engine* engine)
{
    // TODO put this in Pataro/Gui/Inventory
    static const int INVENTORY_WIDTH = 50,
                     INVENTORY_HEIGHT = 28;
    static tcod::Console con(INVENTORY_WIDTH, INVENTORY_HEIGHT);

    tcod::draw_frame(con, {0, 0, INVENTORY_WIDTH, INVENTORY_HEIGHT}, details::frame, tcod::ColorRGB(200, 180, 50), std::nullopt, TCOD_BKGND_DEFAULT);

    // display the items with their keyboard shortcut
    int y = 1;
    Inventory& c = *owner->inventory();

    for (std::size_t i = 0, end = c.size(); i < end; ++i)
    {
        tcod::print(con, {2, y}, tcod::stringf("(%c) %s", 'a' + y - 1, c[i].get_name().c_str()), colors::white, std::nullopt);
        y++;
    }

    tcod::blit(
        engine->console(),
        con,
        {
            static_cast<int>(engine->width()) / 2 - INVENTORY_WIDTH / 2,
            static_cast<int>(engine->height()) / 2 - INVENTORY_HEIGHT / 2
        }
    );
    engine->flush();

    // wait for a key press
    while (true)
    {
        engine->handle_events();

        if (engine->lastkey() != SDLK_UNKNOWN)
            break;
    }

    if (engine->lastkey() >= 'a' && engine->lastkey() <= 'z')
    {
        int idx = engine->lastkey() - 'a';
        if (0 <= idx && static_cast<std::size_t>(idx) < c.size())
            return c.ptr_at(idx);
    }

    return nullptr;
}

PlayerAI* PlayerAI::clone_impl() const
{
    return new PlayerAI(*this);
}