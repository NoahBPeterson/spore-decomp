// Slice s00e52b40: SP::cCellGame level-side helper.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// The cell game is reached through one global pointer (mov eax,[0x16b3c04]); the level
// object sits at +0x5190 and its per-slot kind array at +0x34.
extern void* gCellGame_16b3c04;          // 0x016b3c04 SP::cCellGame*

struct CellLevelStub {
    char pad00[0x34];
    int  mKinds[1];                      // +0x34 per-slot kind
};

struct CellGameStub {
    char pad00[0x5190];
    CellLevelStub* m5190;                // +0x5190
};

// @ 0x00e52b40  is slot i one of the two "active" kinds?
bool FUN_00e52b40(int i)
{
    int kind = ((CellGameStub*)gCellGame_16b3c04)->m5190->mKinds[i];
    return kind == 1 || kind == 2;
}
