# Pataro's architecture

## Engine

In `include/Pataro/Engine.hpp` and `src/Pataro/Engine.cpp`.

In charge of the controls, the map, the player. Updates and renders the game (map + player + GUI).

Updates the player separetly from the map.

## Map

In `include/Pataro/Map.hpp`, `include/Pataro/Map/`, `src/Pataro/Map.cpp` and `src/Pataro/Map/`.

Handles multiple levels (/ floors), works only on the current level.

Acts as a proxy for most of the level's methods.

### Level

In `include/Pataro/Map/Level.hpp` and `src/Pataro/Map/Level.cpp`.

Generates rooms, monsters, handles the field of view, collisions with entities and walls. Updates all the entities except the player, given a pointer to the engine.

## Actions

In `include/Pataro/Action.hpp`, `include/Pataro/Actions/`, `src/Pataro/Action.cpp` and `src/Pataro/Actions/`.

Handle everything the entities can do.

## Entities

In `include/Pataro/Entity.hpp`, `include/Pataro/Entities/`, `src/Pataro/Entity.cpp` and `src/Pataro/Entities/`.

Handles the position, the blocking state, representation of the entity on the overworld. Also handles components such as attacker, destructible and AI through composition.

Updates its AI when called, given a pointer to the engine. It returns an action which is ran by the engine.

Note that the PlayerAI is just reading the engine last key.