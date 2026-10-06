// Slice s00834a00 -- UI::TextZoomName animators + UI::TooltipManager / cSPUITooltipWinProc.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

typedef void*  (__thiscall *VFi)(void*);
typedef void   (__thiscall *VFv)(void*);
typedef uint32_t (__thiscall *VFu)(void*);
static inline void** VT(void* o) { return *(void***)o; }

// ---------------------------------------------------------------- masked externs
extern char  g_vtblTooltipMgr;   // 0x141aec8
extern char  g_vtblContentValid; // 0x13ec458
extern void* g_p164f328;         // 0x164f328
extern float g_164f45c;          // 0x164f45c
extern float g_164f44c;          // 0x164f44c
extern float g_164f46c;          // 0x164f46c
extern float g_164f47c;          // 0x164f47c
extern float g_13fdcf4;          // 0x13fdcf4
extern float g_13fdcf8;          // 0x13fdcf8
extern char  g_1548560;          // 0x1548560

extern "C" float FUN_00805080(void);   // SPUIHelpers::GetElapsedSeconds
extern "C" void  FUN_0080fee0(void);   // MultiHeapObject::operator_new
extern "C" void* FUN_00810620(void);   // cSPUILayoutManager::GetWorldMainWindow
extern "C" void  FUN_00805ea0(void);   // SPUIHelpers::GetMainWindowArea
extern "C" void  FUN_0080d710(void);   // SPUIHelpers::Renderer
extern "C" void  FUN_00805150(void);
extern "C" void  FUN_006237d0(void);   // eastl copy_impl
extern "C" void  FUN_0067cad0(void);   // cSPBoundingBox::AddBoundingBox
extern "C" void* FUN_0067de30(void);   // SP::PropertyManager
extern "C" void  FUN_008105b0(void);   // cSPUILayout::FindWindowByID

// ---------------------------------------------------------------- UI::TooltipManager (retail layout)
struct TooltipManager {
    void*    vptr;   // +0x00
    int      rc;     // +0x04
    void*    layout; // +0x08
    void*    window; // +0x0c
    void*    parent; // +0x10
    void*    props;  // +0x14
    uint32_t key0;   // +0x18
    uint32_t key1;   // +0x1c
    uint32_t key2;   // +0x20
    float    f24;    // +0x24
    float    f28;    // +0x28
    uint8_t  b2c;    // +0x2c
    uint8_t  b2d;    // +0x2d
    uint8_t  b2e;    // +0x2e

    TooltipManager();
    void Dtor();
    bool ReleaseRefs();
    bool ShouldDisplayTooltip(void* w);
    int  ShouldTimeoutTooltip();
    int  ShouldDisplayDetailedTooltip();
    void SetTooltipText(int a, int b);
    void MakeFullyVisibleInMainWindow(int dummy);
    bool LoadProps();
};

struct TooltipWinProc {
    char    pad[0x58];
    uint8_t mbMouseOver;   // +0x58
    uint32_t GetEventMask();
};

// ================================================================ bodies

// @ 0x00834a00 (partial)
__declspec(noinline) bool FUN_00834a00_impl(void* self, void* param)
{
    (void)self; (void)param;
    return false;
}

// @ 0x00834c60 (partial)
__declspec(noinline) void FUN_00834c60_impl(void* self, char param)
{
    (void)self; (void)param;
}

// @ 0x00834e30 (partial)
void FUN_00834e30(void* self)
{
    (void)self;
}

// @ 0x00834f30 (partial)
uint32_t FUN_00834f30(void* self, void* param2, void* param3)
{
    (void)self; (void)param2; (void)param3;
    return 0;
}

// @ 0x00834fa0 (partial)
void* FUN_00834fa0(void* self, void* a, void* b, void* c, void* d, void* e, void* f, void* g)
{
    (void)self; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g;
    return 0;
}

// @ 0x008352a0
uint32_t TooltipWinProc::GetEventMask()
{
    return (uint32_t)(((mbMouseOver != 0) ? 0xFFFFFFFFu : 0) & 2) | 0x441;
}

// @ 0x008352c0
void* FUN_008352c0()
{
    if (g_p164f328 != 0)
        return (char*)g_p164f328 - 8;
    return 0;
}

// @ 0x008352d0
TooltipManager::TooltipManager()
{
    g_p164f328 = (void*)((char*)this + 8);
    rc = 0;
    vptr = &g_vtblTooltipMgr;
    layout = 0;
    window = 0;
    parent = 0;
    props = 0;
    key0 = 0;
    key1 = 0;
    key2 = 0;
    f24 = 0.0f;
    f28 = 0.0f;
    b2c = 0;
    b2d = 0;
    b2e = 0;
}

// @ 0x00835320
void TooltipManager::Dtor()
{
    *(void* volatile*)this = &g_vtblTooltipMgr;
    void* p14 = *(void* volatile*)((char*)this + 0x14);
    if (p14)  ((VFv)VT(p14)[4 / 4])(p14);
    void* p10 = *(void* volatile*)((char*)this + 0x10);
    if (p10) ((VFv)VT(p10)[4 / 4])(p10);
    void* pc = *(void* volatile*)((char*)this + 0x0c);
    if (pc) ((VFv)VT(pc)[4 / 4])(pc);
    void* p8 = *(void* volatile*)((char*)this + 0x08);
    if (p8) ((VFv)VT(p8)[8 / 4])(p8);
    *(void* volatile*)this = &g_vtblContentValid;
    g_p164f328 = 0;
}

// @ 0x008353a0
bool TooltipManager::ReleaseRefs()
{
    if (layout) { layout = 0; ((VFv)VT(layout)[8 / 4])(layout); }
    if (window) { window = 0; ((VFv)VT(window)[4 / 4])(window); }
    if (parent) { parent = 0; ((VFv)VT(parent)[4 / 4])(parent); }
    if (props)  { props = 0;  ((VFv)VT(props)[4 / 4])(props); }
    return true;
}

// @ 0x008353f0
bool TooltipManager::ShouldDisplayTooltip(void* w)
{
    bool r = false;
    if (b2c == 0 && w != parent) {
        if (b2d != 0 && FUN_00805080() - f28 < g_164f45c)
            r = true;
        if (FUN_00805080() - f24 > g_164f44c)
            return true;
    }
    return r;
}

// @ 0x00835440
int TooltipManager::ShouldTimeoutTooltip()
{
    if (b2c != 0) {
        if (FUN_00805080() - f24 > g_164f46c)
            return 1;
    }
    return 0;
}

// @ 0x00835470
int TooltipManager::ShouldDisplayDetailedTooltip()
{
    if (b2c != 0 && b2e == 0) {
        if (FUN_00805080() - f24 > g_164f47c)
            return 1;
    }
    return 0;
}

// @ 0x008354a0
void TooltipManager::SetTooltipText(int a, int b)
{
    ((void (__thiscall*)(void*, int))VT(window)[0x80 / 4])(window, a);
    ((void (__thiscall*)(void*, int))VT(window)[0x5c / 4])(window, b);
    if (window) {
        void* p = ((void* (__thiscall*)(void*, void*))VT(window)[0xc / 4])(window, (void*)0xf15f4bd);
        if (p) {
            ((void (__thiscall*)(void*, float, float))VT(window)[0x68 / 4])(window, g_13fdcf4, g_13fdcf8);
            ((void (__thiscall*)(void*, int))VT(p)[0x14 / 4])(p, 1);
            ((void (__thiscall*)(void*, int))VT(p)[0x14 / 4])(p, 0);
        }
    }
}

// @ 0x00835520
void TooltipManager::MakeFullyVisibleInMainWindow(int dummy)
{
    (void)dummy;
    float area[4];
    ((void (__cdecl*)(void*))FUN_00805ea0)(area);
    float* r = ((float* (__thiscall*)(void*))VT(window)[0x38 / 4])(window);
    float sx = 0.0f;
    float* p = r;
    if (!(*r > 0.0f)) p = &sx;
    sx = *p;
    float sy = 0.0f;
    float* q = r + 1;
    if (!(r[1] > 0.0f)) q = &sy;
    sy = *q;
    if (area[2] < r[2]) sx = r[0] - (r[2] - area[2]);
    if (area[3] < r[3]) sy = r[1] - (r[3] - r[1]);
    ((void (__thiscall*)(void*, float, float))VT(window)[0x70 / 4])(window, sx, sy);
}

// @ 0x00835610
bool TooltipManager::LoadProps()
{
    void* pm = FUN_0067de30();
    if (props) { props = 0; ((VFv)VT(props)[4 / 4])(props); }
    char c = ((char (__thiscall*)(void*, int, void**))VT(pm)[0x30 / 4])(pm, 0x5c770db7, &props);
    if (c)
        ((void (__thiscall*)(void*, void*))FUN_006237d0)(&g_1548560, props);
    return true;
}

// @ 0x00835660 (partial)
void FUN_00835660(void* self, int id, int a3, int a4)
{
    (void)self; (void)id; (void)a3; (void)a4;
}
