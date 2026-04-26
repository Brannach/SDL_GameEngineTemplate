# Optimization Opportunities

## High Impact — Per-Frame Work

### 1. TextPrinter creates an SDL texture every frame

**File:** `Rendering/TextPrinter.cpp` — `PrintText()`

Every call creates a surface, promotes it to a texture, queries it, renders it, then destroys it — all in one frame. For any static or slowly-changing text this is pure waste.

**Fix:** Cache the last rendered texture alongside the text string that produced it. Only recreate when the string changes.

```cpp
// TextPrinter.h — add members
SDL_Texture* mCachedTexture = nullptr;
std::string  mCachedText;

// TextPrinter.cpp — PrintText()
if (text != mCachedText)
{
    SDL_DestroyTexture(mCachedTexture);
    SDL_Surface* surface = TTF_RenderText_Solid(mFont, text.c_str(), mColor);
    mCachedTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    mCachedText = text;
}
// then render mCachedTexture
```

---

### 2. TileLayer tileset lookup is O(n×m) per frame

**File:** `Map/TileLayer.cpp` — `Render()` lines 42–53

For every tile in the map, a linear scan walks `mTileSets` to find which tileset owns that tile ID. With hundreds of tiles per frame this accumulates.

**Fix:** Pre-build a sorted lookup structure at construction time so each tile ID resolves in O(log n) or O(1).

```cpp
// TileLayer.h — add member
std::map<int, int> mTilesetIndexByFirstGid;  // firstGid → tilesetIndex, sorted descending

// TileLayer.cpp — after loading tilesets, build it once:
for (int i = 0; i < (int)mTileSets.size(); i++)
    mTilesetIndexByFirstGid[mTileSets[i].FirstGidIndex] = i;

// In Render(), replace the loop with:
auto it = mTilesetIndexByFirstGid.upper_bound(tileId);
--it;  // largest firstGid <= tileId
int tsIdx = it->second;
```

---

### 3. TextureRenderer queries SDL texture dimensions every draw call

**File:** `Rendering/TextureRenderer.cpp` — `Draw()` lines 33–35

`SDL_QueryTexture()` is called every time any actor is drawn, just to get width and height. These never change after the texture is loaded.

**Fix:** Cache dimensions in a parallel map at load time.

```cpp
// TextureRenderer.h — add member
std::map<std::string, std::pair<int,int>> mTextureDimensions;

// TextureRenderer.cpp — Load(), after SDL_CreateTextureFromSurface:
int w, h;
SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
mTextureDimensions[textureId] = {w, h};

// Draw() — replace SDL_QueryTexture with:
auto [w, h] = mTextureDimensions[textureId];
```

---

## Medium Impact — Unnecessary Copies

### 4. GetTileMap() returns a vector of vectors by value

**File:** `Map/TileLayer.h` line 37

```cpp
// Before
TileMap GetTileMap() { return mTileMap; }

// After
const TileMap& GetTileMap() { return mTileMap; }
```

---

### 5. TextureRenderer draw methods take string by value

**File:** `Rendering/TextureRenderer.h` lines 27–31

```cpp
// Before
void Draw(string textureId, ...);

// After
void Draw(const string& textureId, ...);
```

Apply the same change to `Load()`, `DrawTile()`, and `DrawAnimationTile()`.

---

### 6. Actor getters return RigidBody and Collider by value

**File:** `Entities/Actor.h` lines 30–31

```cpp
// Before
inline RigidBody GetRigidBody() { return ActorRigidBody; }
inline Collider  GetCollider()  { return ActorCollider; }

// After
inline const RigidBody& GetRigidBody() { return ActorRigidBody; }
inline const Collider&  GetCollider()  { return ActorCollider; }
```

---

### 7. GameObject getters return structs by value

**File:** `Entities/GameObject.h` lines 48, 53

```cpp
// Before
inline Point2d     GetOrigin()    { return Origin; }
inline Transform2d GetTransform() { return ObjectTransform; }

// After
inline const Point2d&     GetOrigin()    { return Origin; }
inline const Transform2d& GetTransform() { return ObjectTransform; }
```

---

### 8. Layer::GetName() and ViewRenderer::DisplayModalMessage() take/return by value

**File:** `Map/Layer.h` line 13, `Rendering/ViewRenderer.h` line 15

```cpp
// Layer.h
inline const string& GetName() { return mName; }

// ViewRenderer.h
void DisplayModalMessage(const string& message);
```

---

## Low Impact — Minor Cleanup

### 9. Singleton GetInstance() called multiple times per frame per entity

**Files:** `Entities/Brick.cpp` lines 13–14, `Entities/Health.cpp` lines 14–18, `Entities/BouncingBall.cpp`, `Entities/Paddle.cpp`

Cache the reference at the top of `Update()` / `Draw()` instead of calling `GetInstance()` repeatedly.

```cpp
// Example — Brick::Draw()
SDL_Renderer* renderer = Engine::GetInstance().GetRenderer();
SDL_SetRenderDrawColor(renderer, ...);
SDL_RenderFillRect(renderer, &box);
```

---

### 10. MapParser uses temporary string objects for XML tag comparison

**File:** `Map/MapParser.cpp` lines 39, 48, 78, 84, 91, 121

```cpp
// Before
if (e->Value() == string("tileset"))

// After
if (strcmp(e->Value(), "tileset") == 0)
```

---

### 11. Tileset lookup logic duplicated in TileLayer

**File:** `Map/TileLayer.cpp` — `Render()` lines 42–53 and `SpawnActors()` lines 86–97

The same tileID-to-tilesetIndex loop appears verbatim in both methods. Extract to a private helper:

```cpp
int TileLayer::GetTilesetIndex(int tileId) const;
```

---
