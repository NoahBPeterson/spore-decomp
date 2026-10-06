// Slice s00ecda80 (bfs3 slice 23) -- SP editor palette/swatch UI + scenario helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---- vtable call helpers (__thiscall in a cast is legal; free __thiscall decls are not)
#define C0(p, off)      ((void(__thiscall*)(void*))(((void**)(p))[(off) / 4]))(p)
#define C1(p, off, a)   ((void(__thiscall*)(void*, int))(((void**)(p))[(off) / 4]))(p, a)
#define C2(p, off, a, b) ((void(__thiscall*)(void*, int, int))(((void**)(p))[(off) / 4]))(p, a, b)
#define C3(p, off, a, b, c) ((void(__thiscall*)(void*, int, int, int))(((void**)(p))[(off) / 4]))(p, a, b, c)
#define K0(p, off)      ((int(__thiscall*)(void*))(((void**)(p))[(off) / 4]))(p)
#define K1(p, off, a)   ((int(__thiscall*)(void*, int))(((void**)(p))[(off) / 4]))(p, a)

// ---- globals
extern int* g_15ad298;       // PTR_PTR_015ad298
extern int* g_15abf0c;       // PTR_DAT_015abf0c
extern int* g_15abf1c;       // PTR_DAT_015abf1c
extern float g_15abee4;      // DAT_015abee4
extern float g_13ec468;      // DAT_013ec468
extern char vtbl_BakeSprites[];
extern char vtbl_cSPScenarioSwatchItemUI[];
extern char vtbl_PaintSystem[];
extern char vtbl_cEditorResource[];
extern char vtbl_cContentValidationSummarizer[];

// ---- callees
int* __cdecl GetSystemAT();
int* __cdecl FUN_00efc910();
void __cdecl FUN_00f00380(int a);
int* __cdecl SP_MessageServer();
int  __cdecl FUN_00eece20(int a);
bool __cdecl FUN_005f3060();
void __cdecl FUN_00805fe0(void* out, int a);
bool __cdecl FUN_00efc9c0();
void __cdecl FUN_005f4750();
void __cdecl FUN_00401020();
int* __cdecl FUN_0113ae10();
int* __cdecl SP_WindowManager();
void __cdecl cSPUIPropertyLayout_SetPositionAndOffset(void* self, float a, float b, float c, float d);
void __cdecl FUN_005c6c50();
int  __cdecl FUN_005c6a30();
int* __cdecl EA_Messaging_GetServer();
void __cdecl SP_cSPPaletteItemUI_Shutdown();
void __cdecl cSPUILayout_Shutdown(void* self, int a);
void __cdecl FUN_005f0a60(int a);
void __cdecl FUN_005f0ca0(void* a);
void __cdecl FUN_00ecde60();
void __cdecl FUN_005c6c50_v();
void __cdecl FUN_005f22f0(int a);
int* __cdecl cSPUILayout_FindWindowByID2(void* l, int id);
void __cdecl SPUIHelpers_SetWindowImage(void* w, void* v, int a);
void __cdecl FUN_008068d0(int a, int b, int c);
void __cdecl FUN_00ece140(int a);
void __cdecl FUN_00efbbe0(int a, int b);
void __cdecl SP_cSPPaletteItemUI_DoMessage(void* self, int* msg, int a);
void __cdecl FUN_00834e30();
void __cdecl SPUIHelpers_VisitWindowTreeDepthFirst(int a, void* f, int b);
void __cdecl FUN_00ecd9c0();
int  __cdecl FUN_00f3e8a0(int a);
int  __cdecl FUN_00ecda00();
void __cdecl FUN_005f0c60(int a, int b);
int* __cdecl FUN_01137690();
void __cdecl FUN_005f33f0();
int  __cdecl FUN_005ff1c0();
void __cdecl FUN_00ecda80(int a);
void __cdecl EA_LimitStopwatch_SetTimeLimit(void* self, int a, int b);
int* __cdecl FUN_00b1de80();
void __cdecl FUN_00b3d320();
int* __cdecl SP_GetPropertyAsFloat();
struct LimitStopwatch { char pad[8]; };
void __cdecl FUN_006a1400(int* a, int b, void* c);
void __cdecl FUN_00ef0b80();
void __cdecl SP_cSPPaletteItemUI_ctor(void* self);
void __cdecl FUN_005f7380();

// ============================================================ 0x00ecda80
void FUN_00ecda80_fn(int param_1)
{
    int u = 0;
    int* at = GetSystemAT();
    if (at)
        u = K0(at, 0x20);
    at = GetSystemAT();
    if (at) {
        C1(at, 0x38, 0x3475365);
        C2(at, 0x40, 0x3475381, 0x72d342a9);
        C2(at, 0x40, 0x3475385, u);
        C0(at, 0x58);
    }
    int* p = FUN_00efc910();
    if (p == 0 || *p != param_1) {
        C1(g_15ad298, 0x20, 0);
        FUN_00f00380(param_1);
    }
    int tmp = param_1;
    int* ms = SP_MessageServer();
    C3(ms, 0x14, 0x7465518, (int)&tmp, 0);
}

// ============================================================ 0x00ecdb30
void __fastcall FUN_00ecdb30(int* p)
{
    int a = 0, b = 0, c = 0;
    C1(p, 0x30, (int)&a);
    (void)b; (void)c;
}

// ============================================================ 0x00ecdb50
void FUN_00ecdb50(int* p, int param_2)
{
    if (param_2 == -1) {
        p[4] = -1;
        C0(p, 0x18);
    } else {
        p[4] = param_2;
        C0(p, 0x14);
    }
}

// ============================================================ 0x00ecdb80
bool __fastcall FUN_00ecdb80(int p)
{
    return *(int*)(p + 0x10) == -1;
}

// ============================================================ 0x00ecdb90
void __fastcall FUN_00ecdb90(int* p)
{
    if (p[4] != -1)
        C1(p, 0x1c, -1);
}

// ============================================================ 0x00ecdbb0
void __fastcall FUN_00ecdbb0(int p)
{
    if (*(int*)(p + 0x14) == (int)0x867a9ee9)
        FUN_00eece20(p + 0x18);
}

// ============================================================ 0x00ecdc20
void FUN_00ecdc20(int* p, int param_2)
{
    p[5] = *(int*)(param_2 + 0x14);
    p[3] = *(int*)(param_2 + 0xc);
    C1(p, 0x1c, *(int*)(param_2 + 0x10));
}

// ============================================================ 0x00ecdc70
int FUN_00ecdc70(int param_1)
{
    char c = FUN_005f3060();
    if (c) {
        char buf[8];
        FUN_00805fe0(buf, *(int*)(param_1 + 0x18c));
        float f = *(float*)(buf + 8);
        if (f < *(float*)(param_1 + 0x84)) {
            if (FUN_00efc9c0())
                return 1;
        }
    }
    return 0;
}

// ============================================================ 0x00ecdcc0
void __fastcall FUN_00ecdcc0(int param_1)
{
    FUN_005f4750();
    FUN_00401020();
    void* prop = (void*)FUN_0113ae10();
    void* cand = *(void**)(*(int*)(param_1 + 0x17c) + 0x14);
    if (cand && *(char*)(*(int*)(param_1 + 0x17c) + 0x31) != 0)
        prop = cand;
    if (prop && *(char*)(param_1 + 0x16b) != 0) {
        int* wm = SP_WindowManager();
        int* w = (int*)K0(wm, 4);
        float* r = (float*)K0(w, 0x34);
        cSPUIPropertyLayout_SetPositionAndOffset(prop, *(float*)(param_1 + 0x84),
            *(float*)(param_1 + 0x88), (r[2] - r[0]) * 0.09375f, (r[3] - r[1]) * -0.025f);
    }
}

// ============================================================ 0x00ecdd70
void __fastcall FUN_00ecdd70(int* p)
{
    if ((int*)p[0x18]) C1((int*)p[0x18], 4, 0);
    if ((int*)p[0x17]) C1((int*)p[0x17], 4, 0);
    if ((int*)p[0x16]) C1((int*)p[0x16], 4, 0);
    if ((int*)p[0x15]) C1((int*)p[0x15], 4, 0);
    if ((int*)p[0x14]) C1((int*)p[0x14], 8, 0);
    if ((int*)p[0x13]) C1((int*)p[0x13], 4, 0);
    if ((int*)p[0x12]) C1((int*)p[0x12], 8, 0);
    p[0x11] = (int)vtbl_PaintSystem;
    FUN_005c6c50();
    p[2] = (int)vtbl_cEditorResource;
    p[0] = (int)vtbl_cContentValidationSummarizer;
}

// ============================================================ 0x00ecde00
int FUN_00ecde00(int param_1, int param_2)
{
    if (param_2 == 0x4785a3d) {
        if (param_1 != 8)
            return param_1 + 0x1c;
        param_1 = 0;
    } else {
        if (param_2 == 0x722de52)
            return param_1 - 8;
        if (param_2 == (int)0xee3f516e) {
            if (param_1 == 8)
                goto done;
        } else {
            if (param_2 != 0x82a70e8)
                goto done;
            param_1 -= 8;
        }
        if (param_1 == 0) {
        done:
            return FUN_005c6a30();
        }
    }
    return param_1;
}

// ============================================================ 0x00ecde60
void __fastcall FUN_00ecde60_fn(int param_1)
{
    SP_cSPPaletteItemUI_Shutdown();
    int iVar2 = (param_1 == 0x24) ? 0 : param_1 + 0x20;
    int* srv = EA_Messaging_GetServer();
    C3(srv, 0x2c, iVar2, 0x72304d0, 0xffffd8f1);
    iVar2 = *(int*)(param_1 + 0x28);
    if (iVar2) {
        FUN_00401020();
        FUN_005f0a60(iVar2);
    }
    if (*(int**)(param_1 + 0x2c))
        cSPUILayout_Shutdown(*(void**)(param_1 + 0x2c), 1);
    int* p;
    p = *(int**)(param_1 + 0x24);
    if (p) { *(int*)(param_1 + 0x24) = 0; C1(p, 8, 0); }
    p = *(int**)(param_1 + 0x2c);
    if (p) { *(int*)(param_1 + 0x2c) = 0; C1(p, 8, 0); }
    p = *(int**)(param_1 + 0x28);
    if (p) { *(int*)(param_1 + 0x28) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x34);
    if (p) { *(int*)(param_1 + 0x34) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x38);
    if (p) { *(int*)(param_1 + 0x38) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x3c);
    if (p) { *(int*)(param_1 + 0x3c) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x30);
    if (p) { *(int*)(param_1 + 0x30) = 0; C1(p, 4, 0); }
    // ctor/dtor tail emitted via FUN_00ecdd70 chain in the real code
    FUN_00ecdd70((int*)param_1);
}

// ============================================================ 0x00ecdf60
void FUN_00ecdf60_fn(void)
{
    int* p = (int*)operator new(0x1c8);
    if (p) {
        FUN_005f7380();
        p[0] = (int)vtbl_BakeSprites;
        p[1] = (int)vtbl_cSPScenarioSwatchItemUI;
        p[3] = (int)vtbl_PaintSystem;
        FUN_00401020();
        FUN_005f0ca0(p);
        return;
    }
    FUN_00401020();
    FUN_005f0ca0(0);
}

// ============================================================ 0x00ecdfc0
void __fastcall FUN_00ecdfc0(int param_1)
{
    if (*(int*)(param_1 + 0x4c) != 0) {
        float f = *(float*)(param_1 + 100);
        if (*(float*)(param_1 + 100) < 0.0f)
            f = g_15abee4;
        if (*(int**)(param_1 + 0x4c)) {
            int r = K1(*(int**)(param_1 + 0x4c), 0xc, 0x3349c94);
            (void)f;
            if (r != 0)
                FUN_005f22f0(0x3349c94);
        }
    }
}

// ============================================================ 0x00ece010
void FUN_00ece010(int param_1, int* param_2)
{
    if (*(int**)(param_1 + 0x50) == 0)
        return;
    int* w = (int*)cSPUILayout_FindWindowByID2(*(void**)(param_1 + 0x50), 0x4a1cb6e);
    if (w == 0)
        return;
    int local[3];
    local[0] = param_2[0]; local[1] = param_2[1]; local[2] = param_2[2];
    int uStack_18 = 0xece055;
    int* err = (int*)GetSystemAT();
    uStack_18 = 0;
    int r = K1(err, 0x30, (int)&local);
    if (r == 0) {
        err = (int*)GetSystemAT();
        r = K1(err, 0x30, (int)&uStack_18);
        if (r == 0) {
            uStack_18 = *(int*)(*(int*)(param_1 + 0x48) + 0x18);
            err = (int*)GetSystemAT();
            r = K1(err, 0x30, (int)&uStack_18);
            if (r == 0) {
                FUN_008068d0((int)w, 0, -1);
                goto tail;
            }
        }
    }
    SPUIHelpers_SetWindowImage(w, &uStack_18, -1);
tail:
    if ((char)local[2] == 0)
        C1(w, 0x5c, -1);
    else
        C1(w, 0x5c, 0x77ffffff);
}

// ============================================================ 0x00ece110
void __fastcall FUN_00ece110(int param_1)
{
    if (*(int**)(param_1 + 0x50) != 0) {
        int* w = (int*)cSPUILayout_FindWindowByID2(*(void**)(param_1 + 0x50), 0x79591e0);
        if (w)
            C0(w, 0x80);
    }
}

// ============================================================ 0x00ece140
void __fastcall FUN_00ece140_fn(int param_1, int param_2)
{
    if (*(int**)(param_1 + 0x4c) == 0)
        return;
    int* w = *(int**)(param_1 + 0x4c);
    int* sub = (int*)K1(w, 0xc, 0x3349c94);
    int* a = 0;
    if (w)
        a = w;
    (void)sub;
    C2(a, 0x38, param_2, 1);
    C2(a, 0x5c, (param_2 & 0xff000000) + 0xffffff, 0);
    C1(a, 0x7c, (param_2 == 0) ? 0 : 1);
    C2(a, 0x80, 0x1000, 1);
}

// ============================================================ 0x00ece200
void FUN_00ece200(int* param_1, int* param_2, int param_3)
{
    if (*(int*)(param_3 + 8) == 6) {
        int i = K0(param_2, 0x1c);
        if (i == 0x4a1cb6e && *(int*)(param_3 + 0x18) == 0x3ea) {
            int* v = *(int**)(param_1 - 1);
            FUN_00f00380((int)v);
            if (v == (int*)0xfffffffe)
                FUN_00efbbe0(6, 7);
        }
    }
    SP_cSPPaletteItemUI_DoMessage(param_1, param_2, param_3);
}

// ============================================================ 0x00ece270
void __fastcall FUN_00ece270(int* p)
{
    int local[3] = {0, 0, 0};
    C1(p, 0x30, (int)&local);
    FUN_008068d0(p[0x16], p[0x15], 0);
    int a = 0, b = 0;
    C2(p, 0x38, (int)&a, 1);
    int* q = 0;
    C2(p, 0x3c, (int)&q, 1);
    C1(p, 0x40, (int)&g_13ec468);
    FUN_00ece140(0);
}

// ============================================================ 0x00ece300
void __fastcall FUN_00ece300(int param_1)
{
    int v = *(int*)(param_1 + 0x4c);
    FUN_00401020();
    FUN_005f0c60(v, 0x40a00000);
}

// ============================================================ 0x00ece320
void __fastcall FUN_00ece320(int param_1)
{
    if (*(int*)(param_1 + 0x58) != 0) {
        FUN_00834e30();
        int* p = *(int**)(param_1 + 0x58);
        if (p) { *(int*)(param_1 + 0x58) = 0; C1(p, 8, 0); }
    }
    if (*(int*)(param_1 + 0x1c) != 0) {
        int iVar2 = (param_1 == 0x24) ? 0 : param_1 + 0x48;
        SPUIHelpers_VisitWindowTreeDepthFirst(*(int*)(param_1 + 0x1c), (void*)&FUN_00ecd9c0, iVar2);
    }
    FUN_00ecde60();
}

// ============================================================ 0x00ece370
int FUN_00ece370(int param_1, int param_2)
{
    if (param_2 == 0x722de63)
        return param_1 - 8;
    if (param_2 == 0x2f009dd0) {
        if (param_1 != 8)
            return param_1 + 100;
        return 0;
    }
    return FUN_00ecde00(param_1, param_2);
}

// ============================================================ 0x00ece3b0
int FUN_00ece3b0(int* param_1)
{
    if (param_1 != 0) {
        int i = K1(param_1, 0xc, 0x3349c94);
        if (i != 0) {
            FUN_005f33f0();
            int* p = (int*)FUN_01137690();
            if (p != 0) {
                int j = K1(p, 0xc, 0x722de52);
                if (j != 0)
                    return j;
            }
        }
    }
    return 0;
}

// ============================================================ 0x00ece3f0
void* __stdcall FUN_00ece3f0(char param_1)
{
    void* v = (void*)g_15abf0c;
    if (param_1 == 0)
        v = (void*)g_15abf1c;
    return v;
}

// ============================================================ 0x00ece410
bool FUN_00ece410(int* param_1, int* eax)
{
    bool b1, b2;
    int a = K0(param_1, 0x28);
    int b = K0(eax, 0x28);
    if (a != b) {
        b1 = (a == 0x5b3d1d0d) || (b == 0x5b3d1d0d);
        b2 = (a == (int)0xd37c1045) || (b == (int)0xd37c1045);
        if (!b1) return false;
        if (!b2) return false;
    }
    int x = eax[4], y = param_1[4];
    if (x != -2 && y != -2) {
        if (y == -1)
            return param_1[3] != 7;
        int yy = FUN_00f3e8a0(y);
        int xx = FUN_00f3e8a0(x);
        if (yy != 0 && xx != 0) {
            int r1 = FUN_00ecda00();
            int r2 = FUN_00ecda00();
            return r2 == r1;
        }
    }
    return false;
}

// ============================================================ 0x00ece4d0
int FUN_00ece4d0(int param_1, int param_2, int* param_3)
{
    int iVar1 = K0(param_3, 0x1c);
    if (iVar1 == 0x4a1cb6d || K0(param_3, 0x1c) == 0x73d54a0) {
        FUN_00ef0b80();
        int base = *(int*)(param_1 - 0x24);
        int* p = *(int**)(param_1 - 100);
        (void)base; (void)p;
        return 0;
    }
    return 0;
}

// ============================================================ 0x00ece730
int FUN_00ece730(int param_1, int* param_2, int param_3, int param_4, int param_5)
{
    (void)param_3; (void)param_4;
    int i = K0(param_2, 0x1c);
    if (i == 0x4a1cb6e && param_5 == 1000) {
        if (*(int*)(param_1 + 0x14) != 0 || *(int*)(param_1 + 0x18) != 0) {
            if (!FUN_005ff1c0()) {
                FUN_00ecda80(*(int*)(param_1 - 0x5c));
                return 1;
            }
        }
        EA_LimitStopwatch_SetTimeLimit((void*)(param_1 + 0x14), 0xfa, 1);
    }
    return 0;
}

// ============================================================ 0x00ece790
void __fastcall FUN_00ece790(int* p)
{
    if (p[4] != -1 && p[0x17] != 0) {
        char c = K0(p, 0x44) ? 1 : 0;
        if (c) {
            int u = K0((int*)p[0x17], 0x30);
            C1((int*)p[0x17], 0x5c, (u & 0xff000000) + 0xaa2222);
            return;
        }
        int u = K0((int*)p[0x17], 0x30);
        C1((int*)p[0x17], 0x5c, (u & 0xff000000) + 0xffffff);
    }
}

// ============================================================ 0x00ece7f0
int __fastcall FUN_00ece7f0(int param_1)
{
    int i = FUN_00f3e8a0(*(int*)(param_1 + 0x10));
    if (i == 0)
        return 0;
    if (*(char*)(i + 0x1c) == 0 && *(char*)(i + 0x44) == 0 && *(char*)(i + 0x6c) == 0)
        return 0;
    return 1;
}

// ============================================================ 0x00ece870
int* FUN_00ece870(int* param_1, int param_2)
{
    param_1[1] = 0;
    param_1[2] = (int)vtbl_BakeSprites;
    param_1[0] = (int)vtbl_cSPScenarioSwatchItemUI;
    param_1[2] = (int)vtbl_PaintSystem;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[5] = *(int*)(param_2 + 0x14);
    param_1[3] = *(int*)(param_2 + 0xc);
    C1(param_1, 0x1c, *(int*)(param_2 + 0x10));
    return param_1;
}

// ============================================================ 0x00ece8c0
void __fastcall FUN_00ece8c0(int* p)
{
    if (p[4] != -1) {
        int u = FUN_00f3e8a0(p[4]);
        C1(p, 0x30, u);
    }
}

// ============================================================ 0x00ece8f0
int __fastcall FUN_00ece8f0(int param_1)
{
    if (*(int*)(param_1 + 0x10) != -1) {
        int i = FUN_00f3e8a0(*(int*)(param_1 + 0x10));
        if (i != 0)
            return FUN_00eece20(i);
    }
    return *(int*)(param_1 + 0x14);
}

// ============================================================ 0x00ece920
void FUN_00ece920(void)
{
    FUN_00b3d320();
    int* p = FUN_00b1de80();
    if (p != 0) {
        int local = 0;
        char c = K1(p, 0x24, (int)&local) ? 1 : 0;
        if (c && *(short*)(local + 0x12) == 0xd) {
            int* v = SP_GetPropertyAsFloat();
            g_15abee4 = *(float*)v;
        }
    }
    FUN_006a1400(p, 0x27c26ec0, &g_15abf0c);
    FUN_006a1400(p, 0x92bb2e5f, &g_15abf1c);
}

// ============================================================ 0x00ece990
int* __fastcall FUN_00ece990(int* param_1)
{
    param_1[1] = 0;
    param_1[2] = (int)vtbl_BakeSprites;
    param_1[0] = (int)vtbl_cSPScenarioSwatchItemUI;
    param_1[2] = (int)vtbl_PaintSystem;
    param_1[3] = -1;
    param_1[4] = -1;
    param_1[5] = (int)0x867a9ee9;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    SP_cSPPaletteItemUI_ctor((void*)(param_1 + 9));
    param_1[0x11] = (int)vtbl_PaintSystem;
    param_1[0] = (int)vtbl_PaintSystem;
    param_1[2] = (int)vtbl_PaintSystem;
    param_1[0xc] = (int)vtbl_PaintSystem;
    param_1[0xd] = (int)vtbl_PaintSystem;
    param_1[0x11] = (int)vtbl_PaintSystem;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    param_1[0x17] = 0;
    param_1[0x18] = 0;
    *(char*)(param_1 + 0x1a) = 0;
    param_1[0x19] = (int)0xbf800000;
    return param_1;
}
