// src/game/SPEditors/_at_00560000.cpp -- migrated from slice(s) s005609a0 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00560000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cJob.h"
#include "SP/cISPObjectTemplateDB.h"
#include "SP/cSPObjectTemplateDB.h"

// ---- items of slice s005609a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct EcxStub9a {
    int FUN_00560c30(void* pKey);
    bool FUN_00560d20(void* other);
    void* FUN_00561090_();
    void FUN_005611b0();
    bool FUN_005609a0(void* pKey, char flag);
    bool FUN_00560d60(void* job);
    void FUN_00561220(void* pData);
    bool FUN_00561340(void* pKey);
};
}
namespace SP {
void __fastcall FUN_005156b0(void* self, int reserved, void* owner);
}
// ---- items of slice s005609a0 end

// @ 0x00560d20
namespace SP {
bool EcxStub9a::FUN_00560d20(void* other)
{
    void* this_ = this;
    if (*(uint32_t*)this_ != *(uint32_t*)other)
        return false;
    if (*(uint32_t*)((char*)this_ + 8) != *(uint32_t*)((char*)other + 8))
        return false;
    return true;
}
}  // namespace SP

// @ 0x005611b0
namespace SP {
void EcxStub9a::FUN_005611b0()
{
    void* this_ = this;
    *(void**)this_ = (void*)0x13f4b00;
    *(void**)((char*)this_ + 4) = (void*)0x13f4afc;
    *(void**)((char*)this_ + 8) = (void*)0x13f4af8;
    char* v = (char*)this_ + 0x1c;
    for (char* it = *(char**)v; it < *(char**)(v + 4); it += 0xc) {
    }
    FUN_005156b0(v, 0, this_);
    *(void**)((char*)this_ + 8) = (void*)0x13ef094;
    *(void**)this_ = (void*)0x13eb938;
}
}  // namespace SP
