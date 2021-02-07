# Pataro

A C++ 17 Rogue Like library built on top of [lib TCOD](https://github.com/libtcod/libtcod).

Pataro means *Walker Male* in Quenya.

Read **[ARCHITECTURE.md](ARCHITECTURE.md)** before diving in.

## Deps

* download [tcod 1.16.0-a15](https://github.com/libtcod/libtcod/releases/tag/1.16.0-alpha.15) and put it under tcod/
* CMake >= 3.8

## Controls

- Move/attack with the arrows
- Take a screenshot with F3

## Roadmap

- [x] generation of the world map (rooms + corridors)
- [x] field of view handling
- [x] explored tiles handling
- [x] the player can move and attack
- [x] monsters spawn, can follow the player (if they are in their field of view) and attack them
- [x] everyone has health points, attack power, and AI
- [ ] transitionning from libtcod event system to SDL event system
- [ ] the world map moves with the player
- [ ] GUI about the player, its inventory...
- [ ] items handling, generation and spawn
- [ ] spells and ranged combat
- [ ] travelling between levels / floors
- [ ] saving player progress on a given map + level
- [ ] loading preconfigured maps/levels (eg the overworld with shops...)
- [ ] add a game menu
- [ ] dungeons and character progression
- [ ] (generic?) scripting engine to configure Pataro's engine