// src/game/SPEngine/SPAccessor.cpp -- migrated from slice(s) s004da330 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAccessor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

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

// @ 0x004da3a0
void ResourceManager(uint32_t param)
{
    IResourceManager* p = (IResourceManager*)GetManager();
    p->v0c(param, 0, 0, 0, 0, 0);
}
