// src/game/SPBake/SPEditorStats.cpp -- migrated from slice(s) s004e5050 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorStats.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/eVerbIconCategory.h"

// ---- items of slice s004e5050 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VerbObject {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual bool HasCategory(int key); // +0x1c
};
bool GetPropertyAsKeyInstance(VerbObject* p, int key, int* out); // 0x006a12a0, cdecl
// ---- items of slice s004e5050 end

// @ 0x004e5050
void GetVerbIconKeyForModelType(void* modelType, void* out)
{
    (void)modelType; (void)out;
}

// @ 0x004e5180
void VerbIconBody5180(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e5410
void VerbIconBody5410(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e57f0
bool VerbIconPredicate57f0(void* self)
{
    (void)self;
    return false;
}

// @ 0x004e58c0
int GetVerbCategory(VerbObject* p)
{
    if (p->HasCategory(0x4abbb0d)) {
        int local = 0;
        if (GetPropertyAsKeyInstance(p, 0x4abbb0d, &local))
            return local;
    }
    return 0;
}

// @ 0x004e5910
namespace SP {
namespace EditorUtils {
bool IsDietCategory(SP::eVerbIconCategory id)
{
    return (id == (int)0xa28a67e8 || id == 0x2dfb4f9f || id == (int)0xdfa0d6bf ||
            id == (int)0xd9bcb9f0 || id == 0x521a15d5);
}
}
}  // namespace SP::EditorUtils
