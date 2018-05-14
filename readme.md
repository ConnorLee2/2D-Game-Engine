# 2D Game Engine
2D Game Engine using SFML library. [Executable] (https://github.com/ConnorLee2/2D-Game-Engine/tree/master/Other/Game%20Executable) available in the Other folder.

## Screenshots
### Title Screen
![alt text](https://raw.githubusercontent.com/ConnorLee2/2D-Game-Engine/master/Other/title_screen.png "title_screen")
### Level Selection
![alt text](https://raw.githubusercontent.com/ConnorLee2/2D-Game-Engine/master/Other/level_selection.png "level_selection")
### Level One
![alt text](https://raw.githubusercontent.com/ConnorLee2/2D-Game-Engine/master/Other/level_one.png "level_one")
### Level Two
![alt text](https://raw.githubusercontent.com/ConnorLee2/2D-Game-Engine/master/Other/level_two.png "level_two")

## Features
* Game states - state machine handles switching between states (Title screen, levels etc.).
* Audio manager - plays audio files (sound effects and BGM).
* File IO - loads in text files which contain level data (number of enemies / tilemap)
* Graphics - Tilemap functionality, basic entity functionality (enemy, player, projectile)
* Input manager - manages user input (controller/keyboard) and converts it into enumerated controls.
* Physics manager - handles physics for all entities and also converts user input into physics (e.g. player movement).
* Profiling - displays frame rate and memory usage.
* Asset manager - stores all assets used in the game (audio, graphics, font).

## Usage
* Up Arrow - Move player up.
* Down Arrow - Move player down.
* Right Arrow - Move player right.
* Left Arrow - Move player left.
* O - Confirm / Fire projectile.
* P - Cancel.
* ESC - Pause menu.
* There are also Xbox One controls available.

## Issues/Future work
* Physics system  - better physics (impulse method / integrated movement)
** Such as collision detection between enemy objects and wall tiles.
* Physics system  - needs to be compartmentalised (currently holds majority/all game logic).
* Create a logic manager.
* Graphics system - create a renderer manager (for graphics rendering).
* Graphics system - bottom right corner of tilemap isn't being drawn.
* Graphics system - better entity management?
* Input manager - Swap between PS4 controller and Xbox controller.
* Resource manager - remove resources if no longer used (lifetime of an asset)
* Profiling - per subsystem profilling (execution time of each subsystem)
* Compartmentalise "Core" project into "Core" and "Game".

## Credits
* [SFML](https://www.sfml-dev.org/) - a simple and fast multimedia library.
