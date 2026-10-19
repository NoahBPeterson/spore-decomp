// src/game/SPEngine/SPGraphicsAnimationBaker.cpp -- migrated from slice(s) s006c0db0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsAnimationBaker.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* EAGetManager();
extern void* IDGenerator();
#include <string.h>

// ---- items of slice s006c0db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
extern void  sub_ac040(u32, int);                          // SP::SetCachingType
extern void* EAGetManager();
extern void* IDGenerator();
struct cAnimationBaker {
    char pad00[8];
    u32 f08, f0c, f10;
    void GetBakedAnimations();
};
// ---- items of slice s006c0db0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void  sub_ac040(u32, int);                          // SP::SetCachingType

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void CollectArenaObjects(int self, u32* out, u32 a3);  // 0x006c1680 (stays in the slice: not this object's)

// @ 0x006c1ae0
void cAnimationBaker::GetBakedAnimations()
{
    u32 a = f08, b = f0c, c = f10;
    void* handle = 0;
    if (((c & 0xc0000000) == 0x40000000) && ((c & 0xff0000) == 0x600000) && ((c & 0x1f000000) == 0)) {
        c = (c & 0xe1ffffff) | 0x1000000;
        void* mgr = EAGetManager();
        if (handle != 0) {
            handle = 0;
            ((void(__thiscall*)(void*))(*(void***)handle)[4 / 4])(handle);
        }
        bool ok = ((bool(__thiscall*)(void*, u32*, void**))(*(void***)mgr)[0xc / 4])(mgr, &a, &handle);
        if (ok && b != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))(*(void***)(void*)b)[0xc / 4])((void*)b, 0x2f4e681b);
            if (p != 0) {
                *(u32*)c = (u32)p;
                ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
                goto done;
            }
        }
    } else {
        void* g = IDGenerator();
        ((void(__thiscall*)(void*))(*(void***)g)[4 / 4])(g);
    }
    CollectArenaObjects((int)this, (u32*)c, (u32)&a);
done:
    if (*(u32*)c != 0)
        sub_ac040(*(u32*)c, 9);
    if (b != 0)
        ((void(__thiscall*)(void*))(*(void***)(void*)b)[4 / 4])((void*)b);
}
