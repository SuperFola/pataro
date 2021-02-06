# Pataro

A C++ 17 Rogue Like library built on top of [lib TCOD](https://github.com/libtcod/libtcod).

Pataro means *Walker Male* in Quenya.

## Deps

* download [tcod 1.16.0-a15](https://github.com/libtcod/libtcod/releases/tag/1.16.0-alpha.15) and put it under tcod/

## Controls

- Move/attack with the arrows
- Take a screenshot with F3

## Current state of the project

- [x] generation of the world map (rooms + corridors)
- [x] field of view handling
- [x] explored tiles handling
- [x] the player can move and attack
- [x] monsters spawn, can follow the player (if they are in their field of view) and attack them
- [x] everyone has health points, attack power, and AI
- [ ] the world map moves with the player