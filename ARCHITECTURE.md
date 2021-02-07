# Pataro's architecture

## The engine

In `include/Pataro/Engine.hpp` and `src/Pataro/Engine.cpp`.

In charge of the controls, the map, the player. Updates and renders the game (map + player + GUI).

Updates the player separetly from the map.

## The map

In `include/Pataro/Map.hpp`, `include/Pataro/Map/`, `src/Pataro/Map.cpp` and `src/Pataro/Map/`.

Handles multiple levels (/ floors), works only on the current level.

Acts as a proxy for most of the level's methods.

## The level

In `include/Pataro/Map/Level.hpp` and `src/Pataro/Map/Level.cpp`.

Generates rooms, monsters, handles the field of view, collisions with actors and walls. Updates all the actor except the player, given a pointer to the engine.

## The actor

in `include/Pataro/Actor.hpp`, `include/Pataro/Actor/`, `src/Pataro/Actor.cpp` and `src/Pataro/Actor/`.

Handles the position, the blocking state, representation of the actor on the overworld. Also handles components such as attacker, destructible and AI through composition.

Updates its AI when called, given a pointer to the engine.

Note that the PlayerAI is just reading the engine last key.