#ifndef S00F18EB0_H
#define S00F18EB0_H

#include "types.h"

namespace UI {

// ---------------------------------------------------------------------------
// cScenarioPlayProgressBar
//
// Object layout recovered from the constructor 0x00f18eb0:
//   +0x00/+0x04/+0x08  vftables (0x148c180 / 0x148c178 / 0x148c168)
//   +0x0c/+0x10/+0x14  pointers
//   +0x18..+0x2c       floats (+0x28 == 1.0f)
//   +0x30/+0x31        bytes
//   +0x34..+0x53       embedded member (ctor 0x7f83e0, dtor 0x7f8c20)
//   +0x54..+0x64       five pointers (freed together via 0x571db0)
//   +0x64              element array base, stride 0x1ac
//   +0x68              element array end
//   +0x90              state enum
// ---------------------------------------------------------------------------
class cScenarioPlayProgressBar
{
public:
    cScenarioPlayProgressBar();               // 0x00f18eb0
    ~cScenarioPlayProgressBar();              // 0x00f18f50

    void    Tick();                           // 0x00f19050
    void    Reset();                          // 0x00f190a0
    void    Release();                        // 0x00f19130
    float   GetProgressF();                   // 0x00f19160
    void*   IsEnabled();                      // 0x00f191a0
    bool    IsActive();                       // 0x00f19b80
    uint8_t GetByte(int idx);                 // 0x00f19be0
    int     GetField(int idx);                // 0x00f19c00
    int     GetField2(int idx);               // 0x00f19c20
    int     GetField3(int idx);               // 0x00f19c40
    int     GetDelta(int idx);                // 0x00f19c60
    uint8_t GetKind(int idx);                 // 0x00f19c80
    bool    IsKindAb(int idx);                // 0x00f19cc0
    void    Apply(bool a);                    // 0x00f198f0
    void    Setup(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                  uint32_t e, uint32_t f, uint32_t g, uint32_t h,
                  uint32_t i);                // 0x00f19940
    void    Remove(void* a, uint32_t b);      // 0x00f19ac0
    float   ScanFrac();                       // 0x00f19d10
    void    EachChild(uint32_t* a, uint32_t b); // 0x00f19660
};

// ---- external helpers ----------------------------------------------------
// __thiscall callees are reached through one-method placeholder structs so the
// compiler emits a direct `call rel32` (unresolved; relocations are masked).
extern "C" void __cdecl sub_571db0(int e, int d, int c, int b, int a);
extern "C" void __cdecl sub_572020(void* p, int n);
extern "C" int  __stdcall sub_b320d0(unsigned int id);
struct Xb32250 { void  Release(unsigned int id); };
extern "C" int  __cdecl sub_b3d380(void);
extern "C" void* __cdecl sub_b3d300(void);
struct Xb1fdb0 { void* Find(void* a); };
struct Xc15d50 { void  Add(void* a, int b, int c); };
struct X7f83e0 { void  Ctor(); };
struct X7f8c20 { void  Dtor(); };
struct X93a2e0 { void  Reset(); };
struct Xefcae0 { void  Tick(); };
struct Xf3be60 { void* Find(int id); };
struct X4bf38a7 { static const unsigned int kId = 0x04bf38a7u; };

// ---- free helpers ---------------------------------------------------------
bool  __cdecl cScenarioPlayProgressBar_HasFlag();            // 0x00f18ff0
bool  __cdecl cScenarioPlayProgressBar_KindOk(void* p);      // 0x00f19220
void  __cdecl cScenarioPlayProgressBar_Merge(void* a, void* b); // 0x00f19270
void  __cdecl cScenarioPlayProgressBar_SetAttr(void* o);     // 0x00f19530
void  __cdecl cScenarioPlayProgressBar_Link(void* a);        // 0x00f195a0
bool  __cdecl cScenarioPlayProgressBar_IsReady();            // 0x00f19640
void  __cdecl cScenarioPlayProgressBar_EachChild2(void* p);  // 0x00f196f0
int   __cdecl cScenarioPlayProgressBar_ByIndex(void* a);     // 0x00f19840
void  __cdecl cScenarioPlayProgressBar_Apply2(void* a, uint32_t b); // 0x00f198f0
bool  __cdecl cScenarioPlayProgressBar_Pred(void* a);        // 0x00f19e00

} // namespace UI

#endif
