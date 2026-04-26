# Decoupling Analysis — Making the Engine Game-Agnostic

## Summary Table

| Category | Current State | Should Be |
|---|---|---|
| Level loading | Hardcoded `BreakoutLevel` in `LevelManager` constructor | Factory or config-driven |
| Actor spawning | `TileLayer` spawns only `Brick`; `BreakoutLevel` hardcodes Ball/Paddle/Health | Actor factory with tile→type mapping |
| Completion logic | `brickCounter == 0` in `BreakoutLevel` | Pluggable condition per level |
| Game rules | Health loss at Y=525 hardcoded in `BouncingBall` and `TemplateGameplayRules` | Abstract rules with injected config |
| State machine | Breakout states (`LifeLost`, `NewLevel`) hardcoded in `GameStateMachine` | Pluggable state handlers |
| Collision response | Ball reflection logic lives in `CollisionHandler` | Response delegated to each actor |
| Input | Paddle hardcoded to `HORIZONTAL` axis | Input mapping per actor type |
| Screen bounds | `DEFAULT_SCREEN_WIDTH` constant in `CollisionHandler` | Runtime viewport dimensions |
| HUD | `Health` actor polls `GetHealth()` from `GameplayRules` | Event/callback-driven HUD |

---

## 1. Level System

### 1.1 LevelManager constructor hardcodes Breakout levels
**File:** `Core/LevelManager.cpp` lines 5–10

```cpp
mLevels.push_back(make_unique<BreakoutLevel>("Map01", "./Resources/Maps/Map01.tmx"));
mLevels.push_back(make_unique<BreakoutLevel>("Map02", "./Resources/Maps/Map02.tmx"));
mLevels.push_back(make_unique<BreakoutLevel>("Map03", "./Resources/Maps/Map03.tmx"));
```

Adding a new game requires modifying `LevelManager`. An `AddLevel()` method already exists (line 12) but is never used — levels should be registered there by game-specific startup code, not baked into the constructor.

### 1.2 BreakoutLevel hardcodes Ball, Paddle, and Health on every level load
**File:** `Core/BreakoutLevel.cpp` lines 19–21

```cpp
mActors.push_back(make_unique<BouncingBall>(Properties(...)));
mActors.push_back(make_unique<Paddle>(Properties(...)));
mActors.push_back(make_unique<Health>(Properties(...)));
```

Every level unconditionally spawns these three Breakout actors. A general-purpose level should receive its actors through a factory or a data description, not hardcode them.

### 1.3 Completion condition hardcoded as "no bricks left"
**File:** `Core/BreakoutLevel.cpp` `IsComplete()`

The brick counter is entirely Breakout-specific. Other games might complete on: enemy count, collected items, elapsed time, boss health, etc. Completion logic should be injected per level, not embedded in the base class.

---

## 2. Actor Spawning

### 2.1 TileLayer only spawns Bricks
**File:** `Map/TileLayer.cpp` `SpawnActors()` lines 86–108

```cpp
actors.push_back(make_unique<Brick>(Properties(...)));
```

There is no factory or mapping table — every spawnable actor tile unconditionally creates a `Brick`. Supporting enemies, powerups, or platforms in any other game requires modifying `TileLayer`.

**Fix direction:** A tile-to-actor factory registered at startup (e.g., `RegisterActor(tileGid, factoryFn)`) so `TileLayer` never names a concrete type.

### 2.2 TileLayer distinguishes "brick layers" by a magic TileSourceMap size check
**File:** `Map/TileLayer.cpp` lines 55–56

```cpp
if (tileSet.TileSourceMap.size() != 0)
    continue;   // brick tiles — rendered by their own Actor::Draw(), skip here
```

This is an implicit convention that only works for Breakout's structure.

---

## 3. Game Rules & State Machine

### 3.1 GameState enum contains Breakout concepts
**File:** `Core/Gameplay.h` line 9

```cpp
enum GameState { Initializing, Running, NewLevel, LifeLost, GameOver, Restarting, GameComplete };
```

`LifeLost` and `NewLevel` are Breakout-specific states. A generic base enum should only contain: `Initializing`, `Running`, `Paused`, `GameOver` — with game-specific states defined by each game's own state machine.

### 3.2 GameStateMachine hardcodes Breakout state behaviors
**File:** `Core/GameStateMachine.cpp` lines 8–64

State handlers contain Breakout-specific text, positions, and logic:
- Line 25: displays "Life Lost! Press space key" at (250, 520)
- Line 41: displays "New Level Unlocked!"
- Line 53: resets health to `3` (hardcoded)
- Line 60: displays "You beat it!"

**Fix direction:** State handlers should be strategy objects registered per state, not a monolithic switch statement. Each game supplies its own handlers.

### 3.3 TemplateGameplayRules constructed with a magic number
**File:** `Core/Engine.cpp` line 33

```cpp
GameplayRules = make_unique<TemplateGameplayRules>(TemplateGameplayRules(525));
```

525 is the Breakout ball-drop Y boundary (screen height 600 minus paddle area). This should come from configuration.

---

## 4. Collision System

### 4.1 CollisionHandler uses hardcoded screen dimensions
**File:** `Physics/CollisionHandler.cpp` line 62

```cpp
bool xOverlap = (object.x < 0) || (object.x + object.w > DEFAULT_SCREEN_WIDTH);
```

`DEFAULT_SCREEN_WIDTH` (800) is a compile-time constant from `MainApplication.h`. The handler should accept viewport bounds at runtime.

### 4.2 Ball reflection logic lives in the collision handler
**File:** `Physics/CollisionHandler.cpp` `GetCollisionValues()` lines 10–50

The handler returns axis-flip vectors (`-1.0`/`1.0`) suited specifically to a bouncing ball. Other games need knockback, damage, state changes, or destruction — none of which fit this return type.

**Fix direction:** `CheckCollision` returns raw contact data (which axis was hit, overlap amount, center distances). Each actor decides its own response.

### 4.3 Bounce response and health-loss intertwined in BouncingBall
**File:** `Entities/BouncingBall.cpp` lines 26–56

Ball `Update()` directly calls `gameRules->DecreaseHealth(1)` when it crosses the Y threshold, and performs axis-reflection manually. Physics response and game rule side effects are fused together. These should be separated — the ball handles movement, and loss of life is triggered through an event or callback.

---

## 5. Input

### 5.1 Paddle hardcoded to HORIZONTAL axis only
**File:** `Entities/Paddle.cpp` lines 17–24

```cpp
if (eventHandler.GetAxisKey(HORIZONTAL) == 1) { ActorRigidBody.ApplyForceX(1.0); }
if (eventHandler.GetAxisKey(HORIZONTAL) == -1) { ActorRigidBody.ApplyForceX(-1.0); }
```

Other games need 8-directional movement, rotation, jumping, abilities. Input bindings should be configurable per actor type, not hardcoded per class.

---

## 6. HUD

### 6.1 Health actor polls GameplayRules every frame
**File:** `Entities/Health.cpp` lines 14–19

```cpp
int currentHealth = Engine::GetInstance().GetGameplayRules()->GetHealth();
for (int i = 0; i < currentHealth; i++) { ... }
```

The HUD is coupled to: the existence of `GameplayRules`, an integer health value, and a specific rendering style (repeated icon, 5px gap). A general HUD system should receive state updates via callbacks or an event bus, and render based on its own data — not by polling a game-specific rules object each frame.

---

## 7. Files That Must Change to Add a New Game (OCP Violations)

Any new game currently requires modifying these engine files:

| File | What must change |
|---|---|
| `Core/LevelManager.cpp` | Add new level instances in constructor |
| `Core/BreakoutLevel.h/.cpp` | Contains Brick coupling; must be replaced or forked |
| `Map/TileLayer.cpp` | Hardcoded `Brick` spawn in `SpawnActors()` |
| `Core/GameStateMachine.cpp` | Add/modify state case handlers |
| `Core/Gameplay.h` | Add new `GameState` enum values |
| `Core/Engine.cpp` | Hardcoded rules init and level setup |

---

## Recommended Decoupling Order

1. **Actor factory** — break the `TileLayer` → `Brick` hardlink; everything else flows from this
2. **Abstract level** — separate `ILevel` interface from `BreakoutLevel`; move ball/paddle/health spawning to Breakout-specific subclass
3. **Pluggable state handlers** — replace the switch in `GameStateMachine` with registered handlers
4. **Collision response delegation** — return contact data only from `CollisionHandler`; actors own their response
5. **Config-driven init** — screen bounds, health limits, level list all come from config, not magic numbers
6. **Event-driven HUD** — decouple `Health` actor from `GameplayRules` via events or callbacks
