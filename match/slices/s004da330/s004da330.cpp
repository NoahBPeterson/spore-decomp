// Slice s004da330: SP::cSpeciesProfile::GetUiName, a ResourceManager forwarder and
// SP::GetValidatedSpeciesKey.  Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

// --- eastl::basic_string<wchar_t> (16-byte header used by these accessors) ---
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    void sprintf(const wchar_t* fmt, ...);                    // 0x0041e050
    bool empty() const { return mpBegin == mpEnd; }
};

struct cSpeciesProfile {
    char    pad0[0x504];
    int     mInstance;   // +0x504
    char    pad1[0x51c - 0x508];
    WString mName;       // +0x51c
    void GetUiName(WString* out);
};

// @ 0x004DA330  SP::cSpeciesProfile::GetUiName
void cSpeciesProfile::GetUiName(WString* out)
{
    WString* pName = &mName;
    if (pName != out)
        out->assign(pName->mpBegin, pName->mpEnd);
    if (out->empty())
        out->sprintf(L"Species %d", mInstance);
}

// --- resource-manager forwarder (vtable +0xc) ---
extern void* GetManager();   // 0x0067dcd0

struct IResourceManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t a, int b, int c, int d, int e, int f);
};

// @ 0x004DA3A0  SP::ResourceManager
void ResourceManager(uint32_t param)
{
    IResourceManager* p = (IResourceManager*)GetManager();
    p->v0c(param, 0, 0, 0, 0, 0);
}

// --- validated species key ---
extern uint32_t kCreatureEditorModelGroup;   // 0x015d97ac
extern uint32_t kFloraEditorModelGroup;      // 0x015d9760

// @ 0x004DA3D0  SP::GetValidatedSpeciesKey
uint32_t* GetValidatedSpeciesKey(uint32_t* out, uint32_t instance, bool flora)
{
    uint32_t keyInstance;              // actually the group id (slot -0x10)
    if (!flora)
        keyInstance = kCreatureEditorModelGroup;
    else
        keyInstance = kFloraEditorModelGroup;
    uint32_t group = instance;         // actually the instance (slot -0xc)
    uint32_t keyGroup = ((flora ? 0xffffffffu : 0u) & 0x17f7d701) + 0x2b978c46;  // type (slot -8)
    uint32_t keyType = keyInstance;    // group copy (slot -4)
    ResourceManager((uint32_t)&group);
    out[0] = group;
    out[1] = keyGroup;
    out[2] = keyType;
    return out;
}
