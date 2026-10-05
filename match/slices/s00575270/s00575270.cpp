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
    bool  TestCondition(int);                     // 0x575810
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
bool cAppModeEditorBase::TestCondition(int) { return false; }
void cAppModeEditorBase::ToggleCameraMode() {}
void cAppModeEditorBase::UpdateSpineVertebra(float) {}
