// Slice s00e52910: SP::cCellGame level-side helpers (source-level lookup tables).
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// The cell game is reached through one global pointer (mov eax,[0x16b3c04]); the level
// object sits at +0x5190 and its "source level" kind at +0x7c.
extern void* gCellGame_16b3c04;          // 0x016b3c04 SP::cCellGame*

struct CellLevelStub {
    char pad00[0x7c];
    int  m7c;                            // +0x7c source-level kind
};

struct CellGameStub {
    char pad00[0x5190];
    CellLevelStub* m5190;                // +0x5190
};

// ---------------------------------------------------------------------------
// @ 0x00e52910  level kind -> table of block types (fallback: the level's +0xe0 slot)
// ---------------------------------------------------------------------------
int* FUN_00e52910(void* slot)
{
    int* table;
    switch (((CellGameStub*)gCellGame_16b3c04)->m5190->m7c) {
    case 0:
        table = (int*)((char*)slot + 0x248);
        break;
    case 1:
        return (int*)((char*)slot + 0xe0);
    case 2:
        table = (int*)((char*)slot + 0x194);
        break;
    default:
        return (int*)((char*)slot + 0xe0);
    }
    if (*table == -1)
        return (int*)((char*)slot + 0xe0);
    return table;
}
