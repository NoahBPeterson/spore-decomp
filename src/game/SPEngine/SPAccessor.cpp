// src/game/SPEngine/SPAccessor.cpp -- migrated from slice(s) s0080d670, s004da330 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAccessor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayeredObject.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern void* GetManager();   // 0x0067dcd0
#pragma pack(push, 4)

// ---- items of slice s004da330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* GetManager();   // 0x0067dcd0
struct IResourceManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t a, int b, int c, int d, int e, int f);
};
// ---- items of slice s004da330 end

// ---- items of slice s0080d670 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
void  __cdecl  VisitTree(void*, void*, void*);    // 0x807d30 SPUIHelpers::VisitWindowTreeDepthFirst
// ---- items of slice s0080d670 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
u8 __cdecl FUN_0080d6b0(void* p, u8* p2);  // 0x0080d6b0 (stays in the slice: not this object's)

// @ 0x004da3a0
void ResourceManager(uint32_t param)
{
    IResourceManager* p = (IResourceManager*)GetManager();
    p->v0c(param, 0, 0, 0, 0, 0);
}

// @ 0x0080d710
void __stdcall FUN_0080d710(void* a, void* b, u8 c)
{
    u8 local[8];
    local[0] = c;
    *(void**)(local + 4) = b;
    VisitTree(a, (void*)FUN_0080d6b0, local);
}
