// slice s00575270
// SP::cAppModeEditorBase methods, optimized module (/O2 /arch:SSE /fp:fast).
// Member offsets are taken from the disassembly (retail differs from the 2008 PDB
// by +4 on the early members).
#include <new>
#include <string.h>
#include <math.h>
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// ---------------------------------------------------------------------------
// Stub interfaces (vtable slots at the observed offsets)
// ---------------------------------------------------------------------------
struct VObj {                       // object at cAppModeEditorBase+0x8c
    virtual void slot0(int);
    virtual int  slot1();
};
struct VCheck {                     // object at cAppModeEditorBase+0x7c
    char pad0[0x8c + 0x8c];         // enough that the direct callee is externally visible
    bool SomeCheck();               // 0x628930
};

struct IWindowManager {             // WindowManager() 0x67caa0
    PV16 PV4 PV2
    virtual void SetVisible(int, void*);          // +0x58
};

struct IPaletteInner {              // *[self+0x78]+0x8c
    PV16 PV8 PV4 PV2 PV
    virtual void SetMode(int, int);               // +0x7c
};

struct IMovieSystem {               // MovieSystem() 0x67cb10
    PV8 PV4
    virtual bool IsSomething();                   // +0x30
};

struct IAppSystem {                 // AppSystem() 0x67dd00
    PV8 PV4 PV
    virtual bool IsSomething();                   // +0x34
};

struct IAssetBrowser {              // AssetBrowser() 0x401030
    char pad0[0x1c];
    bool mbActive;                                // +0x1c
};

struct IPlayerUI {                  // *[self+0x74]+0xc
    PV8 PV4 PV2
    virtual bool IsUIGroupEnabled(uint32_t);      // +0x38
};

IWindowManager* __cdecl WindowManager();
IMovieSystem*   __cdecl MovieSystem();
IAppSystem*     __cdecl AppSystem();
IAssetBrowser*  __cdecl AssetBrowser();
void*           __cdecl EditorTuning();
void*           __cdecl FXManager();
bool  __cdecl SomeModeCheck();                    // 0x628930

// --- TestCondition (0x575810) helpers ---
struct IConfigManager {             // ConfigManager() 0x67dd30
    PV8 PV4
    virtual int Query(uint32_t id);               // +0x30
};
IConfigManager* __cdecl ConfigManager();

struct cEffectsWorld {              // object at cAppModeEditorBase+0x90
    char pad0[0x58];
    int  mMode;                                   // +0x58 (current tool/mode id)
};
struct cSPPlayModeUI {              // object at *[self+0x74]+0xc
    bool IsUIGroupEnabled(uint32_t group);        // 0x635890
};
struct cSPPlayMode {                // object at cAppModeEditorBase+0x74
    char pad0[0xc];
    cSPPlayModeUI* mpUI;                          // +0x0c
};
struct cSPPaletteUI {               // object at cAppModeEditorBase+0x3bc
    bool IsPaintByNumber();                       // 0x5ca920
};
struct cDevFlags {                  // object at cAppModeEditorBase+0x4d0: one bool per debug/editor option
    bool f[0x22];
};
struct IEditorEntries {             // object at cAppModeEditorBase+0x42c
    PV
    virtual int Query(int);                       // +0x04
};

// direct-call helpers on the parts palette
struct cPartsPalette {
    void Reset(int, int);                         // 0x43cfc0
    void SomeA();                                 // 0x43cad0
    void SomeB();                                 // 0x43c710
};

namespace SP {
class cAppModeEditorBase {
public:
    char pad[0x458];
    // --- observed offsets ---
    void  SetEconomyValue(int, int);              // 0x575270 (renamed)
    void  ResetEconomy();                         // 0x5754c0
    void  DoSomePaletteThing();                   // 0x575790
    void  StopSomething();                        // 0x5757b0
    bool  TestCondition(uint32_t);                // 0x575810
    void  GetSomething1(int);                     // 0x575e20
    int   GetSomething2();                        // 0x575e50
    bool  SomeBool(char);                         // 0x575eb0
    void  SetupCameraUI();                        // 0x575f20
    void  ToggleCameraMode();                     // 0x575f70
    void  UpdateSpineVertebra(float);             // 0x575520
};
}

using SP::cAppModeEditorBase;

template <typename T> static inline T* Field(void* self, uint32_t off) {
    return *(T**)((char*)self + off);
}
template <typename T> static inline T Value(void* self, uint32_t off) {
    return *(T*)((char*)self + off);
}
static inline char& ByteRef(void* self, uint32_t off) {
    return *(char*)((char*)self + off);
}

// @ 0x00575790
void cAppModeEditorBase::DoSomePaletteThing()
{
    cPartsPalette* p = Field<cPartsPalette>(this, 0xd4);
    if (p)
        p->Reset(0, 1);
}

// @ 0x00575e20
void cAppModeEditorBase::GetSomething1(int arg)
{
    if (Value<int>(this, 0x1d0) == Value<int>(this, 0x1d4)) {
        void* p = Field<void>(this, 0x1c0);
        if (p == 0 || Value<char>(p, 0x35) == 0) {
            Field<VObj>(this, 0x8c)->slot0(arg);
        }
    }
}

// @ 0x00575e50
int cAppModeEditorBase::GetSomething2()
{
    int v = Value<int>(this, 0x1d0);
    if (v == Value<int>(this, 0x1d4)) {
        void* p = Field<void>(this, 0x1c0);
        if (p != 0 && Value<char>(p, 0x35) != 0)
            return Value<int>(p, 0x40);
        int r = Field<VObj>(this, 0x8c)->slot1();
        return r;
    }
    return v;
}

// @ 0x00575eb0
bool cAppModeEditorBase::SomeBool(char param)
{
    if (param == 0) {
        if (AssetBrowser()->mbActive == 0) {
            if (!MovieSystem()->IsSomething()) {
                if (Value<char>(Field<void>(this, 0x7c), 0x3709) == 0) {
                    if (!AppSystem()->IsSomething()) {
                        if (Value<int>(this, 0x31c) == 2) {
                            if (Field<VCheck>(this, 0x7c)->SomeCheck())
                                return true;
                        } else {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// @ 0x005757b0
void cAppModeEditorBase::StopSomething()
{
    if (Field<cPartsPalette>(this, 0xd4)) {
        Field<cPartsPalette>(this, 0xd4)->SomeA();
        Field<cPartsPalette>(this, 0xd4)->SomeB();
    }
    if (Value<char>(this, 0x4d4) != 0) {
        void* fx = FXManager();
        if (fx) {
            // fx->Fade(0x1002, 0.0f, 0.0f, 1)
            typedef void (__thiscall *FadeFn)(void*, uint32_t, float, float, int);
            FadeFn f = *(FadeFn*)(*(void***)fx + 7);
            f(fx, 0x1002, 0.0f, 0.0f, 1);
        }
        ByteRef(this, 0x4d4) = 0;
    }
}

// @ 0x00575f20
void cAppModeEditorBase::SetupCameraUI()
{
    IWindowManager* wm = WindowManager();
    Field<IPaletteInner>(Field<void>(this, 0x78), 0x8c)->SetMode(1, 1);
    wm->SetVisible(1, Field<IPaletteInner>(Field<void>(this, 0x78), 0x8c));
    wm->SetVisible(0, Field<IPaletteInner>(Field<void>(this, 0x78), 0x8c));
}

// ---------------------------------------------------------------------------
// Large functions: kept as compiling placeholders (see partial.txt).
// ---------------------------------------------------------------------------
void cAppModeEditorBase::SetEconomyValue(int, int) {}
void cAppModeEditorBase::ResetEconomy() {}
void cAppModeEditorBase::ToggleCameraMode() {}
void cAppModeEditorBase::UpdateSpineVertebra(float) {}

// @ 0x00575810
// Editor condition test: `id` is the FNV hash of a condition name.
bool cAppModeEditorBase::TestCondition(uint32_t id)
{
    if (id == 0x29930bb7)
        return true;
    if (id == 0xb7b7acea)
        return ConfigManager()->Query(0x4ea96cb) != 0;
    cEffectsWorld* world = Field<cEffectsWorld>(this, 0x90);
    int mode = -1;
    if (world)
        mode = world->mMode;
    if (id == 0x32d61d9f)
        return mode == 0xdfad9f51;
    if (id == 0xaa9b2bd0)
        return mode == 0x9ea3031a;
    if (id == 0x7579b23b)
        return mode == 0xdfad9f51 || mode == 0x9ea3031a;
    if (id == 0xbb107abd) {
        switch (mode) {
        case 0x1a4e0708: case 0xbc1041e6: case 0x8f963dcb: case 0x98e03c0d: case 0x9ad7d4aa:
        case 0xc0b74287: case 0xc15695da: case 0xf670aa43: case 0x441cd3e6: case 0x1f2a25b6:
        case 0x2090a11b: case 0x2a5147a9: case 0x449c040f: case 0x7d433fad:
            return true;
        }
        return false;
    }
    if (id == 0x5caf038c) {
        switch (mode) {
        case 0x1a4e0708: case 0xbc1041e6: case 0x99e92f05: case 0x8f963dcb: case 0x98e03c0d:
        case 0x9ad7d4aa: case 0xc15695da: case 0xbdd15f3d: case 0xc0b74287: case 0xf670aa43:
        case 0x449c040f: case 0x2a5147a9: case 0x1f2a25b6: case 0x2090a11b: case 0x441cd3e6:
        case 0x72c49181: case 0x47c10953: case 0x4e3f7777: case 0x7d433fad:
            return true;
        }
        return false;
    }
    if (id == 0xeef0ea70)
        return Value<int>(this, 0x314) == 0;
    if (id == 0x724eb5a)
        return Value<int>(this, 0x314) == 1;
    if (id == 0xe3e13884)
        return Value<int>(this, 0x314) == 2;
    if (id == 0xb801a2e9) {
        int state = Value<int>(this, 0x314);
        return state == 0 || state == 1;
    }
    if (id == 0x2ad85c42) {
        if (Value<int>(this, 0x314) != 1)
            return false;
        return Field<cSPPaletteUI>(this, 0x3bc)->IsPaintByNumber();
    }
    if (id == 0x8c8e374f) {
        cSPPlayMode* pm = Field<cSPPlayMode>(this, 0x74);
        if (!pm || !pm->mpUI)
            return false;
        return pm->mpUI->IsUIGroupEnabled(0x3e831e4);
    }
    if (id == 0xbb8adf33) {
        cSPPlayMode* pm = Field<cSPPlayMode>(this, 0x74);
        if (!pm || !pm->mpUI)
            return false;
        return !pm->mpUI->IsUIGroupEnabled(0x3e831e4);
    }
    if (id == 0x1b31085a) {
        cSPPlayMode* pm = Field<cSPPlayMode>(this, 0x74);
        if (!pm || !pm->mpUI)
            return false;
        return pm->mpUI->IsUIGroupEnabled(0x445ea18);
    }
    if (id == 0x014d1e0f) return Field<cDevFlags>(this, 0x4d0)->f[0x00];
    if (id == 0x161221ce) return Field<cDevFlags>(this, 0x4d0)->f[0x01];
    if (id == 0x2430a336) return Field<cDevFlags>(this, 0x4d0)->f[0x02];
    if (id == 0x6048fb3d) return Field<cDevFlags>(this, 0x4d0)->f[0x03];
    if (id == 0x0b4ca6a9) return Field<cDevFlags>(this, 0x4d0)->f[0x04];
    if (id == 0xf69266e2) return Field<cDevFlags>(this, 0x4d0)->f[0x05];
    if (id == 0x9b2b681c) return Field<cDevFlags>(this, 0x4d0)->f[0x06];
    if (id == 0x6d7524f9) return Field<cDevFlags>(this, 0x4d0)->f[0x07];
    if (id == 0x7fed6bf3) return Field<cDevFlags>(this, 0x4d0)->f[0x08];
    if (id == 0x7a0819fb) return Field<cDevFlags>(this, 0x4d0)->f[0x0a];
    if (id == 0xfb1889ca) return Field<cDevFlags>(this, 0x4d0)->f[0x09];
    if (id == 0x60a3fd04) return Field<cDevFlags>(this, 0x4d0)->f[0x0b];
    if (id == 0x4ade2e01) return Field<cDevFlags>(this, 0x4d0)->f[0x0d];
    if (id == 0xde0b3ea5) return Field<cDevFlags>(this, 0x4d0)->f[0x0e];
    if (id == 0xb10dafec) return Field<cDevFlags>(this, 0x4d0)->f[0x0f];
    if (id == 0x017d4661) return Field<cDevFlags>(this, 0x4d0)->f[0x10];
    if (id == 0xd0092be3) return Field<cDevFlags>(this, 0x4d0)->f[0x11];
    if (id == 0x1c06bc61) return Field<cDevFlags>(this, 0x4d0)->f[0x13];
    if (id == 0xe433bdff) return Field<cDevFlags>(this, 0x4d0)->f[0x14];
    if (id == 0xfd0e3743) return Field<cDevFlags>(this, 0x4d0)->f[0x15];
    if (id == 0xf4e08da8) return Field<cDevFlags>(this, 0x4d0)->f[0x16];
    if (id == 0xf15525c4) return Field<cDevFlags>(this, 0x4d0)->f[0x17];
    if (id == 0xf7d20932) return Field<cDevFlags>(this, 0x4d0)->f[0x18];
    if (id == 0x23f2b3a5) return Field<cDevFlags>(this, 0x4d0)->f[0x19];
    if (id == 0xeca69bad) return Field<cDevFlags>(this, 0x4d0)->f[0x1a];
    if (id == 0x7069b614) return Field<cDevFlags>(this, 0x4d0)->f[0x1b];
    if (id == 0xf665cf0c) return Field<cDevFlags>(this, 0x4d0)->f[0x1c];
    if (id == 0x33b98f05) return Field<cDevFlags>(this, 0x4d0)->f[0x1d];
    if (id == 0x6e1efa9d) return Field<cDevFlags>(this, 0x4d0)->f[0x1e];
    if (id == 0x51b1fcf8) return Field<cDevFlags>(this, 0x4d0)->f[0x1f];
    if (id == 0x10378cc2) return Field<cDevFlags>(this, 0x4d0)->f[0x20];
    if (id == 0xb6ce8f75) return Field<cDevFlags>(this, 0x4d0)->f[0x21];
    if (id == 0x1fadf1ce) return Value<int>(this, 0x4e4) >= 2;
    if (id == 0x3929810f) return Value<int>(this, 0x4e4) >= 3;
    if (id == 0xe6bc4398) return Value<int>(this, 0x4e4) >= 4;
    if (id == 0x0417cce9) return Value<int>(this, 0x4e4) >= 5;
    if (id == 0x9040ba0a) return Value<int>(this, 0x4e4) >= 6;
    if (id == 0x2546df79) {
        cDevFlags* flags = Field<cDevFlags>(this, 0x4d0);
        return flags->f[9] || flags->f[0xa] || flags->f[0xc];
    }
    if (id == 0x83bf2549) {
        IEditorEntries* entries = Field<IEditorEntries>(this, 0x42c);
        if (!entries)
            return false;
        return entries->Query(0) < 0;
    }
    return false;
}
