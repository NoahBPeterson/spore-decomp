// slice s005794b0
// Mixed editor helpers (render settings, camera, cheats, eastl strings).
// Optimized module (/O2 /arch:SSE /fp:fast).
#include <new>
#include <string.h>
#include "types.h"

namespace SP {
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};
struct Bits128 { uint32_t w[4]; };
struct ResKey { uint32_t instance, type, group; };
struct cEditorLaunchData {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04[2];
    uint32_t mConfig;                             // +0x0c
    ResKey mModelKey;                             // +0x10
    uint32_t mCallingAppModeID;                   // +0x1c
    bool mIsFirstTimeInEditor;                    // +0x20
    Bits128 mValidation;                          // +0x24
    bool mCanSwitchEditor;                        // +0x34
    char pad38[0x90 - 0x38];
    uint32_t mCallerID;                           // +0x90
    char pad94[8];
    cEditorLaunchData();                          // 0x5a9080
};
class cAppModeEditorBase {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5();
    virtual void FinishConfig();                  // +0x18
    virtual void ClearConfig();                   // +0x1c
    virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16();
    virtual void* LoadProps(int group, IRefCounted** out);   // +0x44
    char pad[0x20];
    IRefCounted* mSlot;                           // +0x24
    char pad2[0x1a4];
    cEditorLaunchData* mLaunch;                   // +0x1cc
    char pad3[0x88];
    void UpdateRenderSettings();                  // 0x5794b0
    void SetCurrentConfig(uint32_t id, ResKey key);   // 0x579720
    void SwitchToEditorCamera();                  // 0x5798f0
    void SavePreferenceSomething();               // 0x5799a0
    bool HasSameMask();                           // 0x579a20
    class cEditorCameraController* GetCurrentCameraContext();   // 0x574590
};
}

using SP::cAppModeEditorBase;
using SP::IRefCounted;
using SP::cEditorLaunchData;
using SP::ResKey;
using SP::Bits128;

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t> helper
// ---------------------------------------------------------------------------
struct cWString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    void AllocateSelf(uint32_t n);                // 0x429760
    void RangeInitialize(const wchar_t* s);       // 0x579a90
    int find(const wchar_t* s, uint32_t pos);     // 0x579af0
};

wchar_t* SearchWide(wchar_t* b, wchar_t* e, const wchar_t* sb, const wchar_t* se);   // 0x005497e0

extern unsigned g_mask[4];                        // 0x15da7c4

// @ 0x00579a20
bool cAppModeEditorBase::HasSameMask()
{
    void* p = *(void**)((char*)this + 0x1cc);
    if (p == 0)
        return false;
    unsigned local[4];
    local[0] = *(unsigned*)((char*)p + 0x24) & g_mask[0];
    local[1] = *(unsigned*)((char*)p + 0x28) & g_mask[1];
    local[2] = *(unsigned*)((char*)p + 0x2c) & g_mask[2];
    local[3] = *(unsigned*)((char*)p + 0x30) & g_mask[3];
    for (unsigned i = 0; i < 16; i += 4) {
        if (*(unsigned*)((char*)local + i) != *(unsigned*)((char*)g_mask + i))
            return false;
    }
    return true;
}

// @ 0x00579a90
void cWString::RangeInitialize(const wchar_t* s)
{
    const wchar_t* e = s;
    while (*e != 0)
        ++e;
    uint32_t len = (uint32_t)(e - s);
    uint32_t nSize = len * 2;
    AllocateSelf(len + 1);
    memcpy(mpBegin, s, nSize);
    mpEnd = (wchar_t*)((char*)mpBegin + nSize);
    *mpEnd = 0;
}

// ---------------------------------------------------------------------------
// eastl::basic_string<char> assignment
// ---------------------------------------------------------------------------
struct cString8 {
    char* mpBegin;
    char* mpEnd;
    void assign(const char* first, const char* last);   // 0x454cb0
    cString8& operator=(const cString8& other);          // 0x579c60
};

// @ 0x00579c60
cString8& cString8::operator=(const cString8& other)
{
    if (&other != this)
        assign(other.mpBegin, other.mpEnd);
    return *this;
}

// @ 0x00579af0
int cWString::find(const wchar_t* s, uint32_t pos)
{
    const wchar_t* p = s;
    while (*p != 0)
        ++p;
    uint32_t n = (uint32_t)(p - s);
    wchar_t* en = mpEnd;
    wchar_t* b = mpBegin;
    if (pos <= (uint32_t)(en - b)) {
        wchar_t* r = SearchWide(b + pos, en, s, s + n);
        if (r != en)
            return (int)(r - b);
    }
    return -1;
}

// ---------------------------------------------------------------------------
// Placeholders (see partial.txt)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// "freedom" cheat command
// ---------------------------------------------------------------------------
typedef void* (__thiscall *VFnGet)(void*);
typedef bool  (__thiscall *VFnB1)(void*, void*);
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

struct IApp { };
IApp* App();                                      // 0x0067dd10
int __cdecl Output(void* stream, const char* fmt, ...);   // 0x00841000

struct DirectPropertyList {
    bool GetBool(uint32_t id);                    // 0x006a25a0 (named GetDescription by Ghidra)
    void SetBoolProperty(int id, bool v);         // 0x006a17e0
};
extern DirectPropertyList* g_sAppProperties;      // 0x015fd918

struct cArguments {
    void** MainArguments(int* pCount, int a, int b);   // 0x00838020
};

struct CheatCmd {
    char pad0[4];
    void* mParser;                                // +0x04
    char pad8[8];
    cAppModeEditorBase* mMode;                    // +0x10
    void Execute(cArguments* args);               // 0x579d40
};

// @ 0x00579d40
void CheatCmd::Execute(cArguments* args)
{
    int count;
    void** argv = args->MainArguments(&count, 0, 1);
    IApp* app = App();
    cAppModeEditorBase* mode = mMode;
    if (((VFnGet)VSLOT(app, 0x2c))(app) == mode && !mode->HasSameMask()) {
        bool prev = g_sAppProperties->GetBool(0x677d3ea);
        bool v;
        if (count > 0)
            v = ((VFnB1)VSLOT(mParser, 0x94))(mParser, argv[0]);
        else
            v = !prev;
        g_sAppProperties->SetBoolProperty(0x677d3ea, v);
        if (v)
            Output(mParser, "Editor limits are disabled. Freedom!\n");
        else
            Output(mParser, "Editor limits are enabled. Creations will be pollinated\n");
        return;
    }
    Output(mParser, "The freedom cheat can only be run from within the non-game editors.\n");
}

// ---------------------------------------------------------------------------
// Render settings
// ---------------------------------------------------------------------------
struct Bits64 { uint32_t w[2]; };
class SP::cEditorCameraController { public:
    void SetCenterCameraOffset();                 // 0x5a2370
    void SetPartModeCameraOffset();               // 0x5a2400
    void SetPaintModeCameraOffset();              // 0x5a24c0
};
using SP::cEditorCameraController;

typedef void* (__thiscall *VFnV0)(void*);
typedef int   (__thiscall *VFnI1)(void*, int);
typedef void  (__thiscall *VFnV1)(void*, uint32_t);
typedef void  (__thiscall *VFnV3)(void*, void*, void*, int);
typedef void  (__thiscall *VFnV2)(void*, void*, int, int);
typedef void  (__thiscall *VFnV1i)(void*, int);
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
#define FLD(T, off) (*(T*)((char*)this + (off)))

struct ILayerMgr { };
ILayerMgr* GetLayerMgr();                         // 0x0067dd50
bool GetPropertyAsKeyInstance(void* list, uint32_t id, uint32_t* out);   // 0x006a12a0

inline void OrWide(uint32_t* d, const uint32_t* a, const uint32_t* b)
{
    d[0] = a[0] | b[0];
    d[1] = a[1] | b[1];
    d[2] = a[2] | b[0];
    d[3] = a[3] | b[1];
}

// @ 0x005794b0
void cAppModeEditorBase::UpdateRenderSettings()
{
    struct { uint32_t tmp[4]; uint32_t zero[2]; } L;
    void* cfg = FLD(void*, 0x20);
    void* a = ((VFnV0)VSLOT(cfg, 0x50))(cfg);
    void* b = ((VFnV0)VSLOT(a, 0x38))(a);
    if (b) {
        if (((VFnI1)VSLOT(b, 0xc))(b, 0x29da727)) {
            switch (FLD(int, 0x31c)) {
            case 0:
                GetCurrentCameraContext()->SetPartModeCameraOffset();
                break;
            case 1:
                GetCurrentCameraContext()->SetPaintModeCameraOffset();
                break;
            case 2:
                GetCurrentCameraContext()->SetCenterCameraOffset();
                break;
            }
        }
    }
    if (FLD(int, 0x31c) != 2) {
        uint32_t& key = L.tmp[0];
        key = 0;
        if (GetPropertyAsKeyInstance(FLD(void*, 0x24), 0xb00db8c8, &key)) {
            if (FLD(int, 0x31c) == 1)
                GetPropertyAsKeyInstance(FLD(void*, 0x24), 0x14140dd, &key);
            void* o = FLD(void*, 0x80);
            ((VFnV1)VSLOT(o, 0x30))(o, key);
        }
    }
    int mode = FLD(int, 0x31c);
    if (mode != 2) {
        if (mode == 0) {
            FLD(Bits128, 0x260) = FLD(Bits128, 0x220);
            FLD(Bits64, 0x270) = FLD(Bits64, 0x250);
        } else if (mode == 1) {
            FLD(Bits128, 0x260) = FLD(Bits128, 0x230);
            FLD(Bits64, 0x270) = FLD(Bits64, 0x258);
        }
        L.zero[0] = 0;
        L.zero[1] = 0;
        if (FLD(char, 0x384) == 0)
            OrWide(L.tmp, &FLD(uint32_t, 0x260), &FLD(uint32_t, 0x270));
        else
            OrWide(L.tmp, &FLD(uint32_t, 0x240), &FLD(uint32_t, 0x270));
        void* r = FLD(void*, 0x84);
        ((VFnV3)VSLOT(r, 0x11c))(r, L.tmp, L.zero, 0);
        r = FLD(void*, 0x84);
        ((VFnV3)VSLOT(r, 0x11c))(r, L.tmp + 2, L.zero, 1);
    }
    if (FLD(int, 0x31c) == 0 && FLD(char, 0x384) == 0) {
        void* layer = (char*)this + 4;
        ILayerMgr* m = GetLayerMgr();
        ((VFnV2)VSLOT(m, 0x4c))(m, layer, 0x1a, 2);
    } else {
        ILayerMgr* m = GetLayerMgr();
        ((VFnV1i)VSLOT(m, 0x50))(m, 0x1a);
    }
}

// ---------------------------------------------------------------------------
// Editor config / launch data
// ---------------------------------------------------------------------------
bool __cdecl IsEditorConfigEnabled(int config);   // 0x00685520
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);   // 0x00f473a0
inline void* operator new(size_t size, const char* n, int f, unsigned d, const char* fi, int l)
{ return EA_New((unsigned)size, n, f, (int)d, fi, l); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
extern SP::Bits128 g_launchValidation;            // 0x015da784

// @ 0x00579720
void cAppModeEditorBase::SetCurrentConfig(uint32_t id, ResKey key)
{
    if (!IsEditorConfigEnabled(2) && id == 0xa56567f7)
        return;
    cEditorLaunchData* saved = mLaunch;
    if (saved)
        saved->AddRef();
    if (mLaunch) {
        cEditorLaunchData* old = mLaunch;
        mLaunch = 0;
        old->Release();
    }
    ClearConfig();
    cEditorLaunchData* cur = mLaunch;
    if (saved != cur) {
        if (saved)
            saved->AddRef();
        mLaunch = saved;
        if (cur)
            cur->Release();
    }
    if (mLaunch) {
        mLaunch->mConfig = id;
        mLaunch->mIsFirstTimeInEditor = (key.instance == 0);
        mLaunch->mModelKey = key;
    } else {
        cEditorLaunchData* d = new ("App", 0, 0, (const char*)0, 0) cEditorLaunchData;
        cEditorLaunchData* oldp = mLaunch;
        if (d != oldp) {
            if (d)
                d->AddRef();
            mLaunch = d;
            if (oldp)
                oldp->Release();
        }
        mLaunch->mCallingAppModeID = 0x2ccd1d2;
        mLaunch->mConfig = id;
        mLaunch->mCallerID = 0x2ccd1d2;
        mLaunch->mCanSwitchEditor = true;
        mLaunch->mValidation = g_launchValidation;
        mLaunch->mIsFirstTimeInEditor = (key.instance == 0);
        mLaunch->mModelKey = key;
    }
    FinishConfig();
    if (saved)
        saved->Release();
}

// ---------------------------------------------------------------------------
// Editor camera switch
// ---------------------------------------------------------------------------
struct IPropManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void SetCameraProps(void* props);      // +0x2c
};
IPropManager* PropertyManager();                  // 0x0067de30
extern int g_cameraPropGroup;                     // 0x0150cdd4
bool GetPropertyAsKeyInstance(IRefCounted* list, uint32_t id, uint32_t* out);   // 0x006a12a0

struct IEditorHost {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19();
    virtual void v20();
};
struct ICameraMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void SetKey(uint32_t key);             // +0x34
};
struct IAppCam {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual ICameraMgr* GetCameraMgr();            // +0x50
};
IAppCam* AppCam();                                // 0x0067dd10 (same function as App)

typedef void (__thiscall *VFnSet)(void*, void*);
typedef void* (__thiscall *VFnLoad)(void*, int, void*);   // this vtable +0x44

// @ 0x005798f0
void cAppModeEditorBase::SwitchToEditorCamera()
{
    IRefCounted** slot = &mSlot;
    if (*slot) {
        IRefCounted* old = *slot;
        *slot = 0;
        old->Release();
    }
    IPropManager* pm = PropertyManager();
    if (*slot) {
        IRefCounted* old = *slot;
        *slot = 0;
        old->Release();
    }
    void** pvt = *(void***)pm;
    void* r = LoadProps(g_cameraPropGroup, slot);
    ((VFnSet)pvt[0x2c / 4])(pm, r);
    IRefCounted* list = *slot;
    if (list) {
        uint32_t key;
        if (GetPropertyAsKeyInstance(list, 0x300db745, &key)) {
            if (AppCam()) {
                if (AppCam()->GetCameraMgr())
                    AppCam()->GetCameraMgr()->SetKey(key);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Preference save
// ---------------------------------------------------------------------------
// 16-byte tagged value (flags bit 2 = owns heap storage)
struct Variant {
    uint32_t data[4];
    uint16_t flags;
    uint16_t type;
    Variant(const bool& b) : flags(0), type(0) {
        type = 1;
        flags = 2;
        Store((bool*)&b);
    }
    void Store(bool* p);        // 0x00422e20
    void Free(int a);           // 0x0093db80
    ~Variant() { if (flags & 4) Free(0); }
};

struct IPrefs {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, const Variant& v);      // +0x14
};
extern IPrefs* g_sAppPreferences;                 // 0x015fd91c
int GetSaveArea(uint32_t id);                     // 0x006b1f90
void SaveResource(void* res, int area, char flag);   // 0x006b1d50

// @ 0x005799a0
void SavePreferenceSomething()
{
    IPrefs* prefs = g_sAppPreferences;
    Variant v(true);
    prefs->SetProperty(0x7be27a2, v);
    SaveResource(prefs, GetSaveArea(0x11ac192), 0);
}

// ---------------------------------------------------------------------------
// Editor cheat command object (multiple inheritance: interface at +0, GmeRefCount at +4)
// ---------------------------------------------------------------------------
extern "C" void __cdecl EA_Free(void* p);                    // 0x00f47380
extern wchar_t g_emptyStr[2];                     // 0x01667bac

struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap;
    WStr() { mpBegin = g_emptyStr; mpEnd = mpBegin; mpCap = mpBegin + 1; }
};

struct GmeRefCount {
    virtual ~GmeRefCount() {}
    int mRefCount;
    GmeRefCount() : mRefCount(0) {}
};
struct ICmd {
    virtual void Dummy1();
};
struct CheatObject : ICmd, GmeRefCount {
    void* f0c;
    int f10, f14, f18, f1c;
    void* f20;
    WStr f24;
    int f30, f34, f38, f3c, f40;
    char f44, f45;
    CheatObject();       // 0x579c80
    ~CheatObject();      // 0x579ce0
};

// @ 0x00579c80
CheatObject::CheatObject()
    : f0c(0), f10(0), f14(-1), f18(0), f1c(0), f20(0), f24(), f34(0), f38(0), f44(0), f45(0)
{
}

// The deleting destructor at 0x579ce0 is the one reached through the GmeRefCount subobject
// (this = object + 4), so it is modelled on a class that starts at that subobject.
struct FreeBuf {
    void* p;
    ~FreeBuf() { if (p && ((int*)p)[-1]) EA_Free(p); }
};
struct CheatSub : GmeRefCount {
    FreeBuf a8;                     // object +0x0c
    int b, c, d, e;
    FreeBuf b20;                    // object +0x20
    virtual ~CheatSub() {}          // 0x579ce0 (scalar deleting form)
};

// @ 0x00579ce0
CheatSub* g_keepCheatSub = new CheatSub;
