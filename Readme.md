# OsEngine

**OsEngine** is a custom **2D game engine** designed to allow users to define objects, maps, music, and game logic using a dedicated scripting language (`.ose`) and related extensions (`.struct`, `.music`, `.map`). The engine automatically generates native C code, which can be compiled as a GRUB kernel or run as a standalone application.

---

## Features

- **Custom DSL for game development**  
  - `.ose` → main game loops and logic
  - `.struct` → object definitions (characters, enemies, items)   
  - `.map` → levels and map structures  
  - `.music` → background tracks and sound effects  

- **Flexible import system with aliases**  
  - `$characters * as h` → import all characters from the `characters` folder as alias `h`  
  - `$enemies|easy enemy.ose as e` → import a specific file from a subfolder with alias `e`  

- **Automatic resource conversion**  
  - Folders `a_main_image` and `a_main_music` are automatically converted into binary data in C  

- **Native C code generation**  
  - The compiler transforms all objects and loops into C structures and functions  

---

## Sample structure
> **Note:** Files/folders with tag #!important are required by the compiler. The game **will not compile** without them.

````markdown
├── a_main_image
│   ├── im1.png
│   ├── im2.png
│   └── im3.png
├── a_main_music
│   ├── sound1.mp3
│   └── sound2.mp3
├── characters
│   └── hero.struct
├── compiler.cpp #!important
├── enemies
│   └── enemy.struct
├── images
├── loops #!important
│   ├── main_game.ose
│   └── menu.ose #!important
├── maps
│   └── map1_logic.map
├── music
│   └── soundtrack.music
├── Readme.md
└── sounds
    └── sound1.music
