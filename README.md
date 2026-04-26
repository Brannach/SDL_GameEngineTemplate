# SDL Game Engine Template

A 2D game engine built with SDL2, demonstrated through a Breakout-style game. Written in C++20, targeting Windows x64 with Visual Studio 2022.

---

## Features

- Game loop with fixed-target frame timing (180 FPS)
- AABB collision detection and resolution
- Tiled TMX map loading and tile rendering
- Texture cache with SDL2_image support
- TTF text rendering
- Keyboard input handling
- Simple rigid body physics (forces, velocity, acceleration)
- Game state machine (initializing, running, level transitions, game over)
- Singleton-based core systems

---

## Requirements

- **Visual Studio 2022** (MSVC v143, C++20)
- **Windows x64** — all SDL2 libraries are bundled under `SDL_Libraries/`, nothing to install

| Library | Version |
|---|---|
| SDL2 | 2.0.20 |
| SDL2_image | 2.0.5 |
| SDL2_ttf | 2.0.18 |
| SDL2_mixer | 2.0.4 |

---

## Building

Open `GameEngineTemplate.sln` in Visual Studio 2022 and build, or use MSBuild:

```bash
msbuild GameEngineTemplate.sln /p:Configuration=Debug /p:Platform=x64
```

A post-build event (`copy_libs.bat`) copies the required SDL2 DLLs to the output directory automatically. The output binary lands in `x64/Debug/`.

> Note: x86 build paths are hardcoded to `C:\` absolute paths and may need updating on a different machine. x64 uses `$(SolutionDir)`-relative paths throughout.

---

## Project Structure

```
SDL_GameEngineTemplate/
├── Core/               # Engine loop, application window, event handling, game state
├── Entities/           # Game objects: GameObject, Actor, Brick, Paddle, BouncingBall, Health
├── Physics/            # RigidBody, Collider, CollisionHandler
├── Rendering/          # TextureRenderer, TextPrinter, ViewRenderer
├── Map/                # TMX map parser, GameMap, Layer, TileLayer
├── Geometry/           # Vector2d, Point2d, Transform2d, Dimension2d
├── tinyxml/            # Bundled TinyXML for TMX parsing
├── SDL_Libraries/      # Bundled SDL2, SDL2_image, SDL2_ttf, SDL2_mixer
└── Resources/
    ├── Actors/         # Sprite PNGs (ball variants, paddle, health icon)
    ├── Fonts/          # TTF font file
    └── Maps/           # TMX level files and tileset PNGs (Map01–03)
```

---

## Architecture

### Entry Point

`GameEngineTemplate.cpp` → `Engine::GetInstance()->Run()`

### Core Systems (all Singletons)

| Class | Responsibility |
|---|---|
| `Engine` | Main game loop, scene management, rendering coordination, state machine driver |
| `MainApplication` | SDL window and renderer init (800×600) |
| `EventHandler` | Keyboard input polling |
| `Ticker` | Frame timing and delta time |
| `CollisionHandler` | AABB collision detection between actors and walls |
| `TextureRenderer` | Texture cache keyed by file path; SDL_Texture drawing |
| `TextPrinter` | SDL_ttf text rendering |

### Game Object Hierarchy

```
GameObject  (position, texture, transform, basic collision rect)
└── Actor   (adds Collider + RigidBody)
    ├── BouncingBall
    ├── Paddle
    ├── Brick
    └── Health  (life counter HUD element)
```

`Engine` owns a list of `Actor*` and drives `Update()` / `Draw()` for all actors each frame.

### Physics

- `RigidBody` — mass, forces, velocity, acceleration. Gravity is available but disabled by default for the ball.
- `Collider` — thin wrapper around `SDL_Rect` for AABB boxes.
- `CollisionHandler` — detects actor-to-actor and actor-to-wall collisions; returns contact data for the actor to resolve.

### Map / Level System

Levels are **Tiled TMX files** (`Resources/Maps/Map01–03.tmx`). `MapParser` uses bundled TinyXML to parse them. `GameMap` holds a list of `Layer*`; `TileLayer` renders tile grids from tileset PNGs and spawns `Brick` actors from tile data.

### Game State Machine

```
Initializing → Running ←─────────────────────┐
                  │                           │
               NewLevel ──────────────────────┘
                  │
              LifeLost (3 lives total)
                  │
              GameOver → Restarting → Running
                  │
            GameComplete
```

Life is lost when the ball's Y position exceeds ~525 px. All bricks cleared advances to the next level or triggers GameComplete.

---

## Design Notes

| Document | Description |
|---|---|
| [optimizations.md](optimizations.md) | Catalogued performance improvements — per-frame SDL texture creation, O(n×m) tile lookups, unnecessary copies, and repeated singleton calls |
| [decoupling_analysis.md](decoupling_analysis.md) | Analysis of Breakout-specific coupling in the engine and a recommended order for making it game-agnostic |

---

## Controls

| Key | Action |
|---|---|
| Left Arrow | Move paddle left |
| Right Arrow | Move paddle right |
| Space | Launch ball / continue after life lost |
