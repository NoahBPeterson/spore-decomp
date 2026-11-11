// slice s00e52960 - cCellGame-side predicate: does the current mission/mode want the cell stage?
//
// Retail 0x00e52960 is 149 bytes and reads `esi` (and `edx`) at entry with no loading instruction: its
// caller leaves the object pointer in esi (the /LTCG custom register ABI, docs/codegen.md 11.4).  There is
// no C declaration that makes cl 15 put the argument in esi, so this is an equivalence-only row.
//
// Decoded body (esi = object):
//   cGuard16 g;                                       ctor 0x00743b50 (g.p = 0)
//   p = FUN_00e4cc40(*(void**)(esi + 0x108), &g);     FUN_00e4cc40 @0x00e4cc40 -> 0x00e823a0
//   sel = gspCellGame->field5190->field7c;            gspCellGame = 0x016b3c04
//   switch (sel) { 0: q = p + 0x248; 2: q = p + 0x194; default: q = p + 0xe0; }
//   if (*q == -1) q = p + 0xe0;
//   if (*q == 0 && *esi != gspCellGame->field411c)      return false;   ~g();
//   if (*(int*)(esi + 0x244) == 0)                     return false;
//   if (*(uint8_t*)(esi + 0x112) == 1)                 return false;
//   if (*(int*)(p + 0xb4) != 2)                        return false;
//   return true;                                        ~g();
//
// Retail returns the two values from two separate copies of the epilogue, so the source is written as
// separate early returns; the guard is released on both paths.
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct cGuard16 {                 // 4-byte ref-count guard
    void* p;
    cGuard16() throw();           // 0x00743b50
    ~cGuard16() throw();          // 0x00e82130
};

extern "C" void* __cdecl FUN_00e4cc40(void* arg, void* guard);   // 0x00e4cc40

struct cSelector { char pad[0x7c]; int m7c; };
struct cGame {
    char   pad0[0x411c];
    int    field411c;      // +0x411c  (the "active mission" id)
    char   pad4120[0x5190 - 0x4120];
    cSelector* field5190;  // +0x5190
};
extern cGame* gspCellGame;   // 0x016b3c04

struct cCellMode {
    char pad0[0xb4];
    int  fieldb4;          // +0xb4
};
struct cSelf {
    int      field0;       // +0x00
    char     pad4[0x108 - 4];
    void*    field108;     // +0x108
    char     pad10c[0x112 - 0x10c];
    uint8_t  field112;     // +0x112
    char     pad113[0x244 - 0x113];
    int      field244;     // +0x244
};

// The object pointer arrives in a register chosen by the /LTCG caller, so it is
// modelled as a global that the function loads at entry (docs/codegen.md 11.4).
cSelf* volatile gSelf;      // register-passed argument

// @ 0x00e52960
bool FUN_00e52960()
{
    cSelf* self = gSelf;
    cGuard16 g;
    cCellMode* p = (cCellMode*)FUN_00e4cc40(self->field108, &g);
    int* q;
    switch (gspCellGame->field5190->m7c) {
        case 0:  q = (int*)((char*)p + 0x248); break;
        case 1:  q = (int*)((char*)p + 0xe0);  break;
        case 2:  q = (int*)((char*)p + 0x194); break;
        default: q = (int*)((char*)p + 0xe0);  break;
    }
    if (*q == -1)
        q = (int*)((char*)p + 0xe0);
    if (*q == 0 && self->field0 != gspCellGame->field411c)
        return false;
    if (self->field244 == 0 || self->field112 == 1 || p->fieldb4 != 2)
        return false;
    return true;
}
