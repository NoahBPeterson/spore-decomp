// Slice s00ecad70 -- SP cell-stage UI: ban/palette item rows and slider helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>
#include <intrin.h>
#pragma intrinsic(fabs)
#pragma intrinsic(_ReadWriteBarrier)

inline float AbsF(float v) { return (float)fabs(v); }

// ---------------------------------------------------------------- globals
extern void*         g_16c7584;      // 0x016c7584 (object pointer; [g] = layout)
extern void**        g_16c757c;      // 0x016c757c
extern unsigned int  g_15abd00;      // 0x015abd00
extern unsigned int  g_15abcfc;      // 0x015abcfc
extern unsigned char g_15abcd0;      // 0x015abcd0
extern unsigned char g_16c7574[];

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00efc520(void);                       // 0x00efc520
void  __cdecl FUN_00eca920(void*);                      // 0x00eca920
void  __cdecl FUN_00ec9c70(void*, void*);               // 0x00ec9c70
void  __cdecl FUN_00eca9c0(void);                       // 0x00eca9c0
void  __cdecl FUN_00eca1d0(void);                       // 0x00eca1d0
void  __cdecl FUN_00eca2f0(void);                       // 0x00eca2f0
void  __cdecl FUN_00ec7e90(void);                       // 0x00ec7e90
void  __cdecl FUN_00ec70a0(int);                        // 0x00ec70a0
void  __cdecl FUN_00ec70d0(void*);                      // 0x00ec70d0
void  __cdecl FUN_00ec7320(int*);                       // 0x00ec7320
bool  __cdecl FUN_00ec73c0(int, void*);                 // 0x00ec73c0
int   __cdecl FUN_00ec74e0(void);                       // 0x00ec74e0
void  __cdecl FUN_00ecb520(void*, char);                // 0x00ecb520
void  __cdecl FUN_00ecad70(float);                      // 0x00ecad70
void  __cdecl FUN_00ecb010(int, int);                   // 0x00ecb010
void  __cdecl FUN_00ecb090(int, int);                   // 0x00ecb090
void  __cdecl FUN_00ecb0d0(int, int);                   // 0x00ecb0d0
void  __cdecl FUN_00ecb110(int, int);                   // 0x00ecb110
void  __cdecl FUN_00ecb150(int, int);                   // 0x00ecb150
void* __stdcall FUN_0067cad0(void*, int, int);          // 0x0067cad0
void  __fastcall FUN_0080d710(void*);                   // 0x0080d710
void  __cdecl FUN_00ecaab0(void*);                      // 0x00ecaab0
void  __cdecl FUN_00ecabc0(void*);                      // 0x00ecabc0
char  __cdecl FUN_008d3200(int, int);                   // 0x008d3200
char  __cdecl FUN_008d2fb0(int);                        // 0x008d2fb0
unsigned int __cdecl FUN_00435e90(void);                // 0x00435e90 GetRecorderState
void  __cdecl FUN_00435ed0(unsigned int, unsigned int); // 0x00435ed0 RecordEvent2
void* __cdecl FUN_00a206f0(void);                       // 0x00a206f0 EA::Audio::GetSystemAT
void  __fastcall FUN_00f2a6a0(void*);                   // 0x00f2a6a0
void* __cdecl FUN_0067caa0(void);                       // 0x0067caa0 SP::WindowManager
void* __cdecl FUN_00ec6d00(void);                       // 0x00ec6d00
void  __cdecl FUN_00ec9e20(void*, void*);               // 0x00ec9e20
void  __cdecl FUN_00ec98d0(void);                       // 0x00ec98d0
void  __fastcall FUN_005c6d20(void*);                   // 0x005c6d20 SP::cSPPaletteItemUI::Shutdown
void  __fastcall FUN_005c6bf0(void*);                   // 0x005c6bf0 SP::cSPPaletteItemUI::cSPPaletteItemUI
unsigned char __stdcall FUN_00ecb1f0(int, void**);      // 0x00ecb1f0

typedef void* (__thiscall *FV_1)(void*);
typedef void* (__thiscall *FV_i)(void*, int);
typedef int   (__thiscall *FV_ii)(void*, int, int);
typedef bool  (__thiscall *FB_1)(void*);
typedef int   (__thiscall *FI_1)(void*);

namespace UTFWin { struct IWindow; }

struct cSPUILayout {
    UTFWin::IWindow* FindWindowByID(unsigned int, bool) const;   // 0x008105b0
};

// Active cell-stage object (g_16c7584 points at it; its first field is the layout).
struct BanRow {
    unsigned char  active;      // +0x00 (row base is state+4)
    unsigned char  pad1[3];
    void*          obj;         // +0x04
    int            value;       // +0x08
    int            f0c;         // +0x0c
    int            f10;         // +0x10
    int            f14;         // +0x14
    int            f18;         // +0x18
    int            f1c;         // +0x1c
};
struct CellStageState {
    unsigned char pad0[4];
    BanRow        rows[10];     // +0x04 .. +0x144, stride 0x20
    int           field144;     // +0x144
    void*         p148;         // +0x148
    void*         p14c;         // +0x14c
    unsigned char pad150[8];
    unsigned char b158;         // +0x158
};
struct BanTarget {
    float f00;          // +0x00
    float f04;          // +0x04
    unsigned char pad08[4];
    float f0c;          // +0x0c
};

struct cSPUILayout_s0081_17f0 { void Shutdown(unsigned int); };  // 0x00811ad0

typedef void* (__thiscall *FBanObj)(void*);
typedef void  (__thiscall *FSetBan)(void*, float, float);
typedef void  (__thiscall *FSetInt)(void*, int, int);
typedef void* (__thiscall *FObj0)(void*);
typedef int   (__thiscall *FInt0)(void*);
typedef unsigned char (__thiscall *FBArg)(void*, void*);
typedef void* (__thiscall *FWinGet)(void*, unsigned int, int);
typedef void  (__thiscall *FWinSet)(void*, int);
typedef void  (__thiscall *FRelease)(void*);

// ---------------------------------------------------------------- 0x00ecad70
// @ 0x00ecad70
void FUN_00ecad70(float)
{
    if (FUN_008d2fb0(1000) == 0) {
        if (((CellStageState*)g_16c7584)->p148 != 0) {
            void* a = *(void**)((char*)((CellStageState*)g_16c7584)->p148 + 4);
            FUN_0080d710(FUN_0067cad0(a, 0, 1));
            if (*(int*)((char*)((CellStageState*)g_16c7584)->p148 + 8) == -1)
                FUN_00ecaab0(((CellStageState*)g_16c7584)->p148);
            ((CellStageState*)g_16c7584)->p148 = 0;
            if (((CellStageState*)g_16c7584)->p14c != 0) {
                void* o = *(void**)((char*)((CellStageState*)g_16c7584)->p14c + 4);
                ((FSetInt)(*(void***)o)[0x7c / 4])(o, 1, 1);
            }
            FUN_00eca1d0();
        }
    } else {
        if (((CellStageState*)g_16c7584)->p148 != 0)
            FUN_00ec70d0(((CellStageState*)g_16c7584)->p148);
    }
    for (int off = 0; off < 0x140; off += 0x20) {
        char* p = (char*)g_16c7584 + off + 4;
        if (*p == 0 || p == (char*)((CellStageState*)g_16c7584)->p148)
            continue;
        void* obj = *(void**)(p + 4);
        BanTarget* t = (BanTarget*)((FBanObj)(*(void***)obj)[0x34 / 4])(obj);
        float d = (t->f0c - t->f04 - 1.0f) * (float)*(int*)(p + 8);
        BanTarget* q = (BanTarget*)((FBanObj)(*(void***)obj)[0x34 / 4])(obj);
        float x = q->f00;
        float y = q->f04;
        float nx;
        if (4.0f <= AbsF(x)) {
            float negx = -x;
            nx = negx * 0.2f + x;
            if (AbsF(x - nx) < 4.0f)
                nx = (AbsF(negx) / negx) * 4.0f + x;
        } else {
            nx = 0.0f;
        }
        if (4.0f <= AbsF(y - d)) {
            float dy = d - y;
            d = dy * 0.2f + y;
            if (AbsF(y - d) < 4.0f)
                d = (AbsF(dy) / dy) * 4.0f + y;
        }
        ((FSetBan)(*(void***)obj)[0x64 / 4])(obj, nx, d);
    }
    if (((CellStageState*)g_16c7584)->b158 == 0) {
        if (FUN_008d3200(0x12, 0x3ff) && ((CellStageState*)g_16c7584)->p148 != 0) {
            FUN_00ecabc0(((CellStageState*)g_16c7584)->p148);
            ((CellStageState*)g_16c7584)->b158 = 1;
            return;
        }
    } else {
        if (FUN_008d3200(0x12, 0x3ff))
            return;
    }
    ((CellStageState*)g_16c7584)->b158 = 0;
}

// ---------------------------------------------------------------- 0x00ecb090
// @ 0x00ecb090
void FUN_00ecb090(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    *(int*)(p + 0x10) = param_2;
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb0d0
// @ 0x00ecb0d0
void FUN_00ecb0d0(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    *(int*)(p + 0x14) = param_2;
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb110
// @ 0x00ecb110
void FUN_00ecb110(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    *(int*)(p + 0x1c) = param_2;
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb010
// @ 0x00ecb010
void FUN_00ecb010(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    int local[5];
    local[0] = *(int*)(p + 0xc);
    local[1] = *(int*)(p + 0x10);
    local[2] = *(int*)(p + 0x14);
    local[3] = *(int*)(p + 0x18);
    local[4] = *(int*)(p + 0x1c);
    *(int*)(p + 0x18) = param_2;
    FUN_00ec9c70(local, p + 0xc);
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb150
// @ 0x00ecb150
void FUN_00ecb150(int param_1, int param_2)
{
    char* g = (char*)g_16c7584;
    char* p = g + 4;
    int i = 0;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    if (p == *(char**)(g + 0x14c)) {
        *(int*)(g + 0x14c) = 0;
        FUN_00eca9c0();
        *(int*)(p + 0xc) = -1;
    }
    int local[5];
    local[0] = *(int*)(p + 0xc);
    local[1] = *(int*)(p + 0x10);
    local[2] = *(int*)(p + 0x14);
    local[3] = *(int*)(p + 0x18);
    local[4] = *(int*)(p + 0x1c);
    *(int*)(p + 0xc) = param_2;
    FUN_00ec9c70(local, p + 0xc);
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb690
// @ 0x00ecb690
void FUN_00ecb690(float f)
{
    if (*g_16c757c != 0)
        FUN_00ecad70(f);
    (void)f;
}

// ---------------------------------------------------------------- 0x00ecb730
// @ 0x00ecb730
void FUN_00ecb730(void)
{
    // g_16c7584 is the object pointer; its first field is the active layout.
    cSPUILayout* layout = *(cSPUILayout**)g_16c7584;
    char* w = (char*)layout->FindWindowByID(0x8de6958, 1);
    if (((FI_1)(*(void***)w)[0x28 / 4])(w) & 1)
        FUN_00eca2f0();
}

// ---------------------------------------------------------------- 0x00ecb6b0
// @ 0x00ecb6b0
unsigned char FUN_00ecb6b0(int param_1)
{
    int idx = (int)FUN_00efc520();
    char bl = *(char*)(*(int*)(param_1 + 0x70) + idx * 0x4e0 + 0x4c8);
    cSPUILayout* layout = *(cSPUILayout**)g_16c7584;
    char* w = (char*)layout->FindWindowByID(0x8de6958, 1);
    if ((((FI_1)(*(void***)w)[0x28 / 4])(w) & 1) && param_1 != (int)*g_16c757c) {
        if (*(char*)(*(int*)(param_1 + 0x70) + idx * 0x4e0 + 0x4c8) == 1) {
            FUN_00eca2f0();
            FUN_00ecb520((void*)param_1, 0);
        } else {
            FUN_00eca2f0();
        }
    }
    return (unsigned char)bl;
}

// ---------------------------------------------------------------- 0x00ecb7a0
inline float ClampF(float v, float lo, float hi)
{
    v = (v > lo) ? v : lo;
    v = (v < hi) ? v : hi;
    return v;
}

struct CItem {
    char pad[0x58];
    float f58;      // +0x58
    float f5c;      // +0x5c
    float f60;      // +0x60
    float f64;      // +0x64
    float FUN_A(float);
    float FUN_B(float);
};

// @ 0x00ecb7a0
float CItem::FUN_A(float param)
{
    float f = f58;
    if (f < f5c) {
        f = (param - f) / (f5c - f);
        return ClampF(f, 0.0f, 1.0f);
    }
    return 0.5f;
}

// @ 0x00ecb830
float CItem::FUN_B(float param)
{
    float f = f60;
    if (f < f64) {
        f = (param - f) / (f64 - f);
        return ClampF(f, 0.0f, 1.0f);
    }
    return 0.5f;
}

// ---------------------------------------------------------------- 0x00ecb8c0
// Interface subobjects released through their vtables (slots +4 / +8).
struct IRelease {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

namespace SP {
struct cSPPaletteItemUI_s005c_6340 {
    virtual ~cSPPaletteItemUI_s005c_6340();   // 0x005c6c50
};
}

struct PaletteItem {
    void* vt0;
    char pad[0x20 - 4];
    void* vt20;     // +0x20
    void* p24;      // +0x24
    void* p28;      // +0x28
    void* p2c;      // +0x2c
    void dtor();
};
// @ 0x00ecb8c0
void PaletteItem::dtor()
{
    vt0 = (void*)0x1489350;
    *(void**)((char*)this + 0xc) = (void*)0x1489334;
    *(void**)((char*)this + 0x10) = (void*)0x1489324;
    *(void**)((char*)this + 0x20) = (void*)0x1489314;
    if (p2c) ((IRelease*)p2c)->v2();
    if (p28) ((IRelease*)p28)->v2();
    if (p24) ((IRelease*)p24)->v1();
    *(void**)((char*)this + 0x20) = (void*)0x13eb394;
    ((SP::cSPPaletteItemUI_s005c_6340*)this)->SP::cSPPaletteItemUI_s005c_6340::~cSPPaletteItemUI_s005c_6340();
}
// ================================================================ cell-stage message handler / window helpers
struct ItemAux {
    unsigned char pad[8];
    void* obj;          // +0x08
};
struct PaletteItemUI {
    void* vt00;             // +0x00
    void* inner;            // +0x04
    unsigned char pad08[4];
    void* vt0c;             // +0x0c
    void* vt10;             // +0x10
    unsigned char pad14[8];
    void* win;              // +0x1c
    volatile void* vt20;    // +0x20
    void* p24;              // +0x24
    void* layout;           // +0x28
    void* aux;              // +0x2c
    void* p30;              // +0x30
    void* p34;              // +0x34
    void* p38;              // +0x38
    void* p3c;              // +0x3c
    void* p40;              // +0x40
    void* p44;              // +0x44
    void* p48;              // +0x48
    void* p4c;              // +0x4c
    void* p50;              // +0x50
    void* p54;              // +0x54
    float f58;
    float f5c;
    float f60;
    float f64;
    unsigned char f68;
    unsigned char f69;
    unsigned char f6a;
    unsigned char pad6b;
    float f6c;
    float f70;
    float f74;
    void Update(int arg);
};

// ---------------------------------------------------------------- 0x00ecb1f0
// @ 0x00ecb1f0
unsigned char __stdcall FUN_00ecb1f0(int param_1, void** param_2)
{
    unsigned int kind = (unsigned int)param_2[2];
    if (kind == 0x1c) {
        if (param_2[3] == 0 && FUN_00ec74e0())
            FUN_00eca2f0();
    } else if (kind == 0x4cab02d) {
        if (param_2[3] == (void*)0x6849178) {
            void* at = FUN_00a206f0();
            unsigned int vol = 0;
            if (at)
                vol = (unsigned int)((FInt0)(*(void***)at)[0x20 / 4])(at);
            FUN_00435ed0(0xe76c9b4f, vol);
            void* o1 = ((FObj0)(*(void***)param_2[0])[0x10 / 4])(param_2[0]);
            void* o2 = ((FObj0)(*(void***)o1)[0x10 / 4])(o1);
            unsigned int type = (unsigned int)((FInt0)(*(void***)o2)[0x1c / 4])(o2);
            switch (type) {
            case 0xcdfb1000: {
                void* a = ((FObj0)(*(void***)param_2[0])[0x10 / 4])(param_2[0]);
                void* b = ((FObj0)(*(void***)a)[0x10 / 4])(a);
                int v = ((FInt0)(*(void***)b)[0x10 / 4])(b);
                FUN_00ecb150(v, (int)param_2[4]);
                break;
            }
            case 0xcdfb1020: {
                void* a = ((FObj0)(*(void***)param_2[0])[0x10 / 4])(param_2[0]);
                void* b = ((FObj0)(*(void***)a)[0x10 / 4])(a);
                int v = ((FInt0)(*(void***)b)[0x10 / 4])(b);
                FUN_00ecb090(v, (int)param_2[4]);
                break;
            }
            case 0xcdfb1030: {
                void* a = ((FObj0)(*(void***)param_2[0])[0x10 / 4])(param_2[0]);
                void* b = ((FObj0)(*(void***)a)[0x10 / 4])(a);
                int v = ((FInt0)(*(void***)b)[0x10 / 4])(b);
                FUN_00ecb0d0(v, (int)param_2[4]);
                break;
            }
            case 0xcdfb1040: {
                void* a = ((FObj0)(*(void***)param_2[0])[0x10 / 4])(param_2[0]);
                void* b = ((FObj0)(*(void***)a)[0x10 / 4])(a);
                int v = ((FInt0)(*(void***)b)[0x10 / 4])(b);
                FUN_00ecb010(v, (int)param_2[4]);
                break;
            }
            case 0xcdfb1050: {
                void* a = ((FObj0)(*(void***)param_2[0])[0x10 / 4])(param_2[0]);
                void* b = ((FObj0)(*(void***)a)[0x10 / 4])(a);
                int v = ((FInt0)(*(void***)b)[0x10 / 4])(b);
                FUN_00ecb110(v, (int)param_2[4]);
                break;
            }
            }
            FUN_00eca1d0();
        }
    } else if (kind == 0x287259f6) {
        unsigned int id = (unsigned int)param_2[3];
        switch (id) {
        case 0xcdfb1000:
        case 0xcdfb1020:
        case 0xcdfb1030:
        case 0xcdfb1040:
        case 0xcdfb1050:
            FUN_00435ed0(0xe76c9b4f, FUN_00435e90());
            FUN_00ec70a0(0);
            FUN_00ec7320((int*)param_2[0]);
            return 1;
        case 0x595e0a9:
            FUN_00ec7e90();
            return 1;
        case 0x595e0b9: {
            int local[2];
            FUN_00ec70a0(0);
            FUN_00ec73c0(param_1, local);
            return 1;
        }
        case 0x695e0a8:
            FUN_00435ed0(0xe76c9b4f, FUN_00435e90());
            FUN_00eca2f0();
            return 1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ecb520
// @ 0x00ecb520
void FUN_00ecb520(void*, char flag)
{
    void* w = (*(cSPUILayout**)g_16c7584)->FindWindowByID(0x8de6958, 1);
    if (((FInt0)(*(void***)w)[0x28 / 4])(w) & 1)
        return;
    w = (*(cSPUILayout**)g_16c7584)->FindWindowByID(0x8de6960, 1);
    ((FSetInt)(*(void***)w)[0x7c / 4])(w, 0x400, 1);
    ((CellStageState*)g_16c7584)->field144 = 0;
    ((CellStageState*)g_16c7584)->p14c = 0;
    ((CellStageState*)g_16c7584)->p148 = 0;
    void* win = (*(cSPUILayout**)g_16c7584)->FindWindowByID(0x8de6958, 1);
    ((FSetInt)(*(void***)win)[0x7c / 4])(win, 1, 1);
    *g_16c757c = win;
    int idx = (int)FUN_00efc520();
    if ((unsigned char)flag) {
        int base = *(int*)((char*)*g_16c757c + 0x70);
        FUN_00f2a6a0((void*)(base + idx * 0x4e0));
    }
    FUN_00ec98d0();
    g_15abcd0 = 1;
    idx = (int)FUN_00efc520();
    int base = *(int*)((char*)*g_16c757c + 0x70);
    int* arr = (int*)(base + idx * 0x4e0 + 0x4cc);
    int count = (arr[1] - arr[0]) >> 5;
    int off = 0;
    for (int i = 0; i < count; ++i) {
        void* item = FUN_00ec6d00();
        FUN_00ec9e20((void*)(arr[0] + off), (char*)item + 0xc);
        *(int*)((char*)item + 8) = i;
        FUN_00eca920(item);
        off += 0x20;
    }
    FUN_00eca9c0();
    if ((unsigned char)flag)
        FUN_00eca1d0();
    void* wm = FUN_0067caa0();
    ((FSetInt)(*(void***)wm)[0x4c / 4])(wm, 0, (int)win);
}

// ---------------------------------------------------------------- 0x00ecb950
// @ 0x00ecb950
void __fastcall FUN_00ecb950(PaletteItemUI* self)
{
    void* q = self->aux;
    if (q) {
        self->aux = 0;
        ((FRelease)(*(void***)q)[2])(q);
    }
    void* l = self->layout;
    if (l) {
        ((cSPUILayout_s0081_17f0*)l)->Shutdown(1);
        l = self->layout;
        if (l) {
            self->layout = 0;
            ((FRelease)(*(void***)l)[2])(l);
        }
    }
    FUN_005c6d20(self);
}

// ---------------------------------------------------------------- 0x00ecb9a0
// @ 0x00ecb9a0
void PaletteItemUI::Update(int)
{
    ItemAux* aux = (ItemAux*)this->aux;
    void* obj = aux->obj;
    void* arg = (char*)this->inner + 0xc;
    unsigned char r = ((FBArg)(*(void***)obj)[2])(obj, arg);
    this->f69 = r;
    void* w = ((FWinGet)(*(void***)this->win)[0xf0 / 4])(this->win, 0x73933b8, 1);
    unsigned int color = this->f69 ? g_15abd00 : g_15abcfc;
    ((FWinSet)(*(void***)w)[0x5c / 4])(w, (int)color);
    if (this->f69 == 0) {
        ((FWinSet)(*(void***)w)[0x78 / 4])(w, 0);
        return;
    }
    if (this->f6a != 0) {
        ((FWinSet)(*(void***)w)[0x78 / 4])(w, 0x747d67c);
        return;
    }
    ((FWinSet)(*(void***)w)[0x78 / 4])(w, 0x747d67b);
}

// ---------------------------------------------------------------- 0x00ecba50
// @ 0x00ecba50
PaletteItemUI* __fastcall FUN_00ecba50(PaletteItemUI* self)
{
    FUN_005c6bf0(self);
    _ReadWriteBarrier();
    self->vt20 = (void*)0x13eb384;
    self->vt00 = (void*)0x1489350;
    self->vt0c = (void*)0x1489334;
    self->vt10 = (void*)0x1489324;
    _ReadWriteBarrier();
    self->vt20 = (void*)0x1489314;
    _ReadWriteBarrier();
    self->p24 = 0;
    self->layout = 0;
    self->aux = 0;
    self->p30 = 0;
    self->p34 = 0;
    self->p38 = 0;
    self->p3c = 0;
    self->p40 = 0;
    self->p44 = 0;
    self->p48 = 0;
    self->p4c = 0;
    self->p50 = 0;
    self->p54 = 0;
    self->f58 = 0.0f;
    self->f5c = 1.0f;
    self->f60 = 0.0f;
    self->f64 = 1.0f;
    self->f68 = 0;
    self->f6a = 0;
    self->f69 = 1;
    self->f6c = 0.5f;
    self->f70 = 0.5f;
    self->f74 = 1.0f;
    return self;
}

