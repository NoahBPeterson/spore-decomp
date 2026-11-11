// Slice s00e5af30 -- SPGonzago cell-game effect update loop.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---- globals ---------------------------------------------------------------
extern void* g_16b3c08;                        // 0x016b3c08
extern int   g_16b3c18;                        // 0x016b3c18
struct Entry_16b39e4 { void* mKey; void* mPad; };
extern Entry_16b39e4 g_16b39e4[];              // 0x016b39e4

// ---- callees ---------------------------------------------------------------
struct Table_00b721d0 {
    void* Find(void* key);                     // 0x00b721d0
};
struct Table_00b72210 {
    void* At(unsigned int id);                 // 0x00b72210
};

struct CellGame_00e5af30 {
    char             pad_000[0x1c];            // +0x000 .. +0x1b
    Table_00b721d0   mTable;                   // +0x1c
};

extern CellGame_00e5af30* gspCellGame;        // 0x016b3c04

// @ 0x00e5af30
void __cdecl FUN_00e5af30(void)
{
    int i = 0;
    if (g_16b3c18 <= 0)
        goto done;
    do {
        void* key;
        Table_00b721d0* tbl;
        key = g_16b39e4[i].mKey;
        tbl = (Table_00b721d0*)((char*)gspCellGame + 0x1c);
        char* obj = (char*)tbl->Find(key);
        if (obj != 0) {
            void* p248 = *(void**)(obj + 0x248);
            if (p248 != 0 && *(int*)(obj + 0xfc) != 0) {
                Table_00b72210* tbl2 = (Table_00b72210*)((char*)g_16b3c08 + 0x168);
                char* p = (char*)tbl2->At((unsigned int)p248);
                char* q = *(char**)(p + 0x24);
                if (q != 0) {
                    void* inner = *(void**)(q + 0x190);
                    ((void (__thiscall*)(void*, void*, int, int))(*(void***)inner)[0x40 / 4])
                        (inner, q, 2, 1);
                }
            }
        }
        ++i;
    } while (i < g_16b3c18);
done:
    g_16b3c18 = 0;
}
