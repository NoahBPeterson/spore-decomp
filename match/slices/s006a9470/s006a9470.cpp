// Slice s006a9470 — property-system commands + SP::cPropertyManager init/write.
// Module flags: /O2 /MD /Gy /EHsc /TP
//
// All five functions in this slice are large, EH-heavy command/manager bodies whose
// byte-exactness depends on the exact EASTL hash_map/basic_string instantiations used by
// the retail build, which are not reproduced here.  They are recorded as partial.
#include "types.h"

namespace EA { namespace ArgScript { struct cArguments; } }
using EA::ArgScript::cArguments;

// ===========================================================================
// `anonymous namespace'::cListPropsCheat::Execute
// ===========================================================================
struct cListPropsCheat {
    void Execute(cArguments* args);
};

// @ 0x006a9470
void cListPropsCheat::Execute(cArguments* args)
{
    // TODO(partial): "listprops" cheat.  Parses an optional property-list key
    // (OptionArguments + SPKeyFromName), looks the list up through the property
    // manager vtable (+0x2c), then walks the list's property array (vtable +0x44)
    // and prints "0x%08x = %s %s %s" / "%s = %s (%s) %s" per property via
    // EA::ArgScript::Output, after GetVariantTypeDescription / GetVariantValueDescription.
    (void)args;
}

// ===========================================================================
// `anonymous namespace'::cPropCheat::Execute
// ===========================================================================
struct cPropCheat {
    void Execute(cArguments* args);
};

// @ 0x006a9790
void cPropCheat::Execute(cArguments* args)
{
    // TODO(partial): "prop" cheat — resolves a property by name/id through the manager
    // and prints or sets its value.
    (void)args;
}

// ===========================================================================
// SP::cPropertyManager::Init / WriteResource
// ===========================================================================
struct cPropertyManager {
    char pad00[0x14];
    bool mInitialized;   // +0x14

    uint32_t Init();                                  // @ 0x006a9b60
    uint8_t  WriteResource(int* param_2, int* param_3); // @ 0x006aa130
};

// @ 0x006a9b60
uint32_t cPropertyManager::Init()
{
    // TODO(partial): registers the property-command cheats, loads the base property list
    // and wires the resource manager.  See the 1377-byte original.
    return 0;
}

// @ 0x006aa130
uint8_t cPropertyManager::WriteResource(int* param_2, int* param_3)
{
    // TODO(partial): serialises the property tables into the resource writer.
    return 0;
}

// ===========================================================================
// FUN_006aa0d0 — bool-vector append helper
// ===========================================================================
struct BoolVec {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
};

struct BoolVecOwner {
    void* vtbl;      // +0

    bool Append(int arg1, BoolVec* v);
};

void FUN_0050f0d0(void*, void*);
void* FUN_0050e4b0(void*, void*);
void BoolVec_DoInsertValue(void* dst, void* src, int count);

// @ 0x006aa0d0
bool BoolVecOwner::Append(int arg1, BoolVec* v)
{
    // this->vfunc_0x48(arg1, v)
    typedef void (__thiscall* Fn48)(void*, int, BoolVec*);
    ((Fn48)((void**)vtbl)[0x48 / 4])(this, arg1, v);

    FUN_0050f0d0(v->mpBegin, v->mpEnd);
    void* dst = FUN_0050e4b0(v->mpBegin, v->mpEnd);
    void* src = v->mpEnd;
    BoolVec_DoInsertValue(dst, src, 0);
    v->mpEnd = (char*)v->mpEnd - (((char*)src - (char*)dst) >> 2) * 4;
    return v->mpBegin != v->mpEnd;
}
