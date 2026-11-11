// Slice s00e6f5b0 -- 0x00e6f5b0: per-frame sync of the player critter's window.
//
// The critter's target cell is resolved through the cell game's cell pool and the resolved position
// is copied into the window's +0x8..+0x11 members.  The window then re-lays itself against the
// frame time, looks its progress-bar widget up in the player's HUD layout and runs the generic
// progress update with (rect x, rect y, 1.0, the player's zone value).
//
// Local stand-in layout (retail offsets).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct CellGame;                            // SP::cCellGame
struct Player;                              // the cell-mode player at 0x016b3c0c
struct PlayerClock;

extern CellGame* gspCellGame;               // 0x016b3c04
extern Player*   gpPlayer;                  // 0x016b3c0c
extern const float kZero462C;               // the value stored into the player clock's flag slot

// Three floats, copied whole (no float load/store pairs).
struct Vec3 {
    float x, y, z;
};

// One resolved cell: its position vector starts at +0x4c.
struct Cell {
    uint8_t pad0[0x4c];
    Vec3    mPosition;          // +0x4c
};

// cSPObjectPoolT<SP::cSPCell,4096>::Get(id) -- null when the id is out of range or stale.
struct CellPool {
    Cell* Get(uint32_t id);     // 0x00b721d0 (thiscall, ret 4)
};

struct PlayerClock {
    uint8_t      pad00[0xc4];
    const float* mpFlag;        // +0xc4
};

struct CellGame {
    uint8_t      pad00[0x1c];
    CellPool     mCells;        // +0x1c
    uint8_t      pad38[0xc4 - 0x38];
    PlayerClock* mpClock;       // +0xc4
};

// The window found for the critter's rect.
struct Window {
    uint8_t pad00[0x1254];
    Player* mpPlayer;           // +0x1254
    float   mZone;              // +0x1258
};

// The player: the HUD layout at +0x70, the player clock at +0xc4 and the critter's window (the
// window's player back-pointer at +0x1254, its zone value at +0x1258).
struct HUDLayout {
    Window* Find(void* key);             // 0x00e39fb0
    Window* operator[](void* key);       // 0x00e67940
};

struct Player {
    uint8_t      pad00[0x70];
    HUDLayout    mWindows;      // +0x70
    uint8_t      pad74[0xc4 - 0x74];
    PlayerClock* mpClock;       // +0xc4
    uint8_t      padC8[0x1254 - 0xc8];
    Player*      mpSelf;        // +0x1254
    float        mZone;         // +0x1258
};

// The critter's window: the target cell id at +0x0 and the layout members from +0x4.
struct CritterWindow {
    uint32_t mCellId;           // +0x00
    bool     mPlaced;           // +0x04
    uint8_t  pad05[0x03];
    Vec3     mPosition;         // +0x08, +0x0c, +0x10
    Cell*    mpCell;            // +0x14 (the resolved target cell)
    uint8_t  pad18[0xfc - 0x18];
    Vec3     mRect;             // +0xfc, +0x100, +0x104
    float    mTime;             // +0x108
};

// Lays the window out against the frame time.
void LayoutWindow(CritterWindow* self, float t);                        // 0x00e68170

// Generic widget progress update. 0x00e6eec0
void UpdateProgress(void* widget, float x, float y, float level, float duration, int mode);

// @ 0x00e6f5b0
void CritterSync(CritterWindow* self)
{
    CellGame* game = gspCellGame;
    Player* player = gpPlayer;

    Cell* cell = game->mCells.Get(self->mCellId);
    if (cell) {
        self->mpCell = cell;
        Vec3 srcPos = cell->mPosition;
        const int* src = (const int*)&srcPos;
        int x = src[0];
        int y = src[1];
        int z = src[2];
        *(int*)&self->mPosition.x = x;
        *(int*)&self->mPosition.y = y;
        *(int*)&self->mPosition.z = z;
        self->mPlaced = false;
    } else {
        game->mpClock->mpFlag = &kZero462C;
    }

    LayoutWindow(self, self->mTime);

    Window* window = player->mWindows[&self->mRect];
    UpdateProgress(window, self->mRect.x, self->mRect.y, 1.0f, player->mZone, 0);
}
