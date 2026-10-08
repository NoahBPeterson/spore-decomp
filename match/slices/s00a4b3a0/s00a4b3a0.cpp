// Slice s00a4b3a0: FUN_00a4b3a0 (VA 00a4b3a0, 410 bytes, cdecl, args (canvas, a2, a3, argc, av), plain ret).
//
// Pd-style canvas restore of one object's creation atom av (type +0x24, w0 +0x28, w1 +0x2c):
//   if (argc > 3) {
//       a "$<digits>" symbol becomes a float-like arg (type 7, atoi); a "$<other>" symbol is
//       interned with gensym (type 8); then type 8 looks up the object's info via pd_findbyclass
//       and FUN_00a477a0, and type 2 renames directly.
//   }
//   pd_popsym / resort inlets+outlets, clear flag 0x08, run FUN_00a67ce0()->FUN_00a643b0, then
//   attach the class object and call canvas_objfor.
//
// Flags: /O2 /MD /Gy /TP (no /EHsc, no SEH; atoi comes from the CRT import).
#include "types.h"
#include <stdlib.h>

struct cSymPair {                       // gensym() result, also the FUN_00a477a0 out pair
    uint32_t a;
    uint32_t b;
};

struct cPdInfo {
    uint8_t pad00[8];
    uint32_t mA8;                       // +0x08
    uint32_t mAc;                       // +0x0c
};

struct cPdObj {
    uint8_t pad00[0x2c];
    cPdObj* mpNext;                     // +0x2c
    uint8_t pad30[0x74 - 0x30];
    cPdInfo* mpInfo;                    // +0x74
};

struct cCanvas {
    uint8_t pad00[0x2c];
    cPdObj* mpObj;                      // +0x2c
    uint8_t pad30[0x78 - 0x30];
    uint32_t mFlags;                    // +0x78
    uint8_t pad7c[0x80 - 0x7c];
    uint32_t mHelperResult;             // +0x80
};

struct cAtom {
    uint8_t pad00[0x24];
    int32_t mType;                      // +0x24 (2 symbol, 7 digit arg, 8 gensym'd symbol)
    uint32_t mW0;                       // +0x28
    uint32_t mW1;                       // +0x2c (char* for a symbol)
};

struct cCanvasFactory {
    uint32_t FUN_00a643b0(cCanvas* c, void (*fn)());     // 0x00a643b0 (thiscall, 2 args)
};

extern uint32_t gHashXSymbol;           // 0x016758bc
extern uint32_t gSymbolArg2;            // 0x016758c0
extern uint32_t gpCanvasClass;          // 0x01675490
extern uint32_t gEmptySymbol;           // 0x0167589c
extern uint32_t gSymbol5;               // 0x016758a0

cPdObj* pd_findbyclass(uint32_t a, uint32_t b, uint32_t c);   // 0x00a671f0
void pd_popsym(cCanvas* c);                                    // 0x00a49500
void canvas_resortinlets(cCanvas* c);                          // 0x00a4d4d0
void canvas_resortoutlets(cCanvas* c);                         // 0x00a4d6a0
void canvas_rename(cCanvas* c, uint32_t a, uint32_t b, uint32_t emptySym, uint32_t sym5);   // 0x00a4ae50
void canvas_objfor(cPdObj* o, cCanvas* c, int argc, cAtom* av);   // 0x00a4f590
cSymPair* gensym(cSymPair* out, const char* s);                // 0x00a675f0
void FUN_00a477a0(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int e, cSymPair* out);   // 0x00a477a0
cCanvasFactory* FUN_00a67ce0();                                // 0x00a67ce0
void FUN_00a4a6b0();                                           // 0x00a4a6b0 (callback)

void FUN_00a4b3a0(cCanvas* c, int a2, int a3, int argc, cAtom* av)
{
    cSymPair local;

    if (argc > 3) {
        if (av->mType == 2 && ((const char*)av->mW1)[0] == '$') {
            const char* s = (const char*)av->mW1;
            if (s[1] >= '0' && s[1] <= '9') {
                const char* p = s + 2;
                bool bad = false;
                while (*p != 0) {
                    if (*p < '0' || '9' < *p) {
                        bad = true;
                        break;
                    }
                    ++p;
                }
                if (bad) {
                    av->mType = 8;
                    cSymPair* sp = gensym(&local, s + 1);
                    av->mW0 = sp->a;
                    av->mW1 = sp->b;
                } else {
                    av->mType = 7;
                    av->mW0 = (uint32_t)atoi(s + 1);
                }
            }
        }

        if (av->mType == 8) {
            cPdObj* o = pd_findbyclass(gHashXSymbol, gSymbolArg2, gpCanvasClass);
            while (o->mpInfo == 0)
                o = o->mpNext;
            cPdInfo* info = o->mpInfo;
            FUN_00a477a0(av->mW0, av->mW1, info->mA8, info->mAc, 1, &local);
            canvas_rename(c, local.a, local.b, gEmptySymbol, gSymbol5);
        } else if (av->mType == 2) {
            canvas_rename(c, av->mW0, av->mW1, gEmptySymbol, gSymbol5);
        }
    }

    pd_popsym(c);
    canvas_resortinlets(c);
    canvas_resortoutlets(c);
    c->mFlags &= 0xfffffff7u;
    cCanvasFactory* f = FUN_00a67ce0();
    c->mHelperResult = f->FUN_00a643b0(c, FUN_00a4a6b0);
    cPdObj* o2 = pd_findbyclass(gHashXSymbol, gSymbolArg2, gpCanvasClass);
    if (o2) {
        c->mpObj = o2;
        canvas_objfor(o2, c, argc, av);
    }
}
