// Slice s00ed9150 -- terrain/posse effect placement and UI cursor helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);
typedef void  (__thiscall *FV_i)(void*, int);
typedef void* (__thiscall *FV_ip)(void*, int);
typedef void  (__thiscall *FV_ii)(void*, int, int);
typedef int   (__thiscall *FV_ir)(void*, int);
typedef int   (__thiscall *FV_r0)(void*);
typedef char  (__thiscall *FV_c0)(void*);

// A tutorial step: a type tag and two noun-target operands. Position is
// obtained through vtable slot 0x2c.
struct Step95d0 {
    int   mType;    // +0x00
    void* mA;       // +0x04
    void* mB;       // +0x08
};

// Tutorial entry as stored in the scenario tutorial list (stride 0x188).
struct Tutorial188 {
    int   mType;    // +0x00
    void* mA;       // +0x04
    void* mB;       // +0x08
    char  pad0[0x188 - 0x0c];
};

struct TutVec {
    char         pad0[0x84];
    Tutorial188* mBegin;    // +0x84
    Tutorial188* mEnd;      // +0x88
};

// Setter object whose +0x48 member is set by TutorialPanel::Refresh.
struct StateSync {
    char  pad0[0x04];
    void* m4;       // +0x04  effect slot 0
    void* m8;       // +0x08  effect slot 1
    void* mc;       // +0x0c  effect slot 2
    void* m10;      // +0x10  path slot 0 A
    void* m14;      // +0x14  path slot 1 A
    void* m18;      // +0x18  path slot 2 A
    void* m1c;      // +0x1c  path slot 0 B
    void* m20;      // +0x20  path slot 1 B
    void* m24;      // +0x24  path slot 2 B
    void __thiscall Set(int v);     // 0x00ed9990
};

// free callees
void* __cdecl FUN_00ed9040(int, float*);
extern float g_1470f1c;
extern unsigned char g_16065f8;
extern void* g_15ad298;
extern void* g_16c7aa4;

void  __cdecl FUN_00ed9150(int* out, float* pos, void* objPos, float f);
void  __cdecl FUN_00ed95d0(int* out1, int* out2, float* pos, Step95d0* step);
void  __cdecl FUN_00ed9560(int* out, void* pos, int key);
void* __cdecl SP_GetGameTerrainCursor(void);   // 0xb30d70
void  __cdecl FUN_00572020(void*, int);        // 0x572020
void  __cdecl SetGlobalProperty(int, float);   // 0x5ca880
void* __cdecl SP_GameInputManager(void);       // 0xb3d250
void  __cdecl SP_cTribeInputStrategy_ToggleBanningContent(int); // 0xdd17f0
void  __cdecl SP_cUIBanningContent_EndBanMode(int);             // 0xdd1840
void  __cdecl FUN_00e099d0(int);
void  __cdecl FUN_00e09a50(int);
void  __cdecl FUN_00571db0(int,int,int,int,int);
void* __cdecl FUN_00efc510(void);
char  __cdecl FUN_00efcd90(void);
void* __cdecl FUN_0067cab0(void);
int   __fastcall FUN_008013c0(void*, int);         // cCursorManager::GetCursor (edx = dummy)
void  __fastcall FUN_00801bb0(void*, int, int);    // cCursorManager::SetCursor (edx = dummy)

void* __cdecl SP_App(void);                    // 0x67dd10
int   __cdecl FUN_008d2fb0(int);               // 0x8d2fb0
char  __fastcall FUN_00b0f9a0(void*, int);     // 0xb0f9a0 (edx = dummy)
void* __cdecl FUN_00b3d4d0(void);              // 0xb3d4d0
void* __cdecl FUN_00b3d230(void);              // 0xb3d230
char  __fastcall FUN_00b5ca60(void*, int);     // 0xb5ca60 (edx = dummy)
void* __cdecl FUN_00b3d240(void);              // 0xb3d240
void* __cdecl FUN_00b18e00(void*);             // 0xb18e00
char  __cdecl FUN_00dd18b0(void*);             // 0xdd18b0
char  __cdecl FUN_00e09ad0(void*);             // 0xe09ad0

void* __cdecl FUN_00efe5a0(void);              // 0xefe5a0
void* __fastcall FUN_006c0200(void*, int);     // 0x6c0200 (edx = dummy)
void* __fastcall FUN_00b18530(void*, int);     // 0xb18530 (edx = dummy)
void* __cdecl FUN_00ed8490(int);               // 0xed8490
void* __cdecl FUN_00ed8500(int);               // 0xed8500
void* __cdecl FUN_00ed8570(int);               // 0xed8570
int   __cdecl FUN_00efc520(void);              // 0xefc520
void* __fastcall FUN_00f3be60(void*, int, int);     // 0xf3be60 (edx = dummy)
void* __fastcall FUN_00f3e8a0(void*, int, int);     // 0xf3e8a0 (edx = dummy)
char  __fastcall FUN_00f25530(void*, int);     // 0xf25530 (edx = dummy)

void* __cdecl FUN_0067ddd0(void);              // 0x67ddd0 (effects manager)
void  __cdecl FUN_00f47380(void*);             // 0xf47380

// ================================================================ 0x00ed9150
// Builds the cursor path (up to 128 segments) between two positions.
// @ 0x00ed9150
void __cdecl FUN_00ed9150(int* out, float* pos, void* objPos, float f)
{
    const float* pA = pos;
    const float* pB = (const float*)objPos;
    float dx = pB[0] - pA[0];
    float dy = pB[1] - pA[1];
    float dz = pB[2] - pA[2];
    float dist = sqrtf(dx * dx + dy * dy + dz * dz);

    int count = 3;
    float scale = f;
    if (f <= 0.0f) {
        scale = dist * (1.0f / 3.0f);
    } else if (f * 3.0f > dist) {
        scale = dist * (1.0f / 3.0f);
    } else if (dist > f * 128.0f) {
        scale = dist * (1.0f / 128.0f);
        count = 128;
    } else {
        count = (int)(dist / f) + 1;
    }

    void* cursor = *(void**)out;
    int oldCount = 0;
    float* oldPts = (float*)((void* (__thiscall*)(void*, int, int*))(*(void***)cursor)[0x50 / 4])(cursor, 13, &oldCount);
    if (oldCount == count &&
        oldPts[0] == pA[0] && oldPts[1] == pA[1] && oldPts[2] == pA[2] &&
        oldPts[(oldCount - 1) * 3 + 0] == pB[0] &&
        oldPts[(oldCount - 1) * 3 + 1] == pB[1] &&
        oldPts[(oldCount - 1) * 3 + 2] == pB[2])
        return;

    float len = sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);
    float inv = 1.0f / len;
    float sx = dx * inv * scale;
    float sy = dy * inv * scale;
    float sz = dz * inv * scale;

    float pts[130 * 3];
    int n = 0;
    for (int i = 0; i < count; i++) {
        float t = (float)i;
        pts[n * 3 + 0] = pA[0] + sx * t;
        pts[n * 3 + 1] = pA[1] + sy * t;
        pts[n * 3 + 2] = pA[2] + sz * t;
        n++;
    }
    int last = n - 1;
    if (!(pts[last * 3 + 0] == pB[0] && pts[last * 3 + 1] == pB[1] && pts[last * 3 + 2] == pB[2])) {
        pts[n * 3 + 0] = pB[0];
        pts[n * 3 + 1] = pB[1];
        pts[n * 3 + 2] = pB[2];
        n++;
    }

    if (n != oldCount) {
        void* cur = *(void**)out;
        char b = (char)((FV_r0)(*(void***)cur)[0x10 / 4])(cur);
        if (b)
            ((FV_i)(*(void***)cur)[0xc / 4])(cur, 1);
        void* old = *(void**)out;
        void* fx = FUN_0067ddd0();
        if (old != 0) {
            *(void**)out = 0;
            ((FV_v)(*(void***)old)[4 / 4])(old);
        }
        unsigned __int64 h = ((unsigned __int64 (__thiscall*)(void*, void*))(*(void***)old)[0x60 / 4])(old, out);
        ((void (__thiscall*)(void*, unsigned __int64))(*(void***)fx)[0x2c / 4])(fx, h);
        if (b)
            ((FV_i)(*(void***)(*(void**)out))[8 / 4])(*(void**)out, 1);
    }

    void* cur2 = *(void**)out;
    ((void (__thiscall*)(void*, int, void*, int))(*(void***)cur2)[0x40 / 4])(cur2, 13, pts, n);
}

// ================================================================ 0x00ed9560
// @ 0x00ed9560
void FUN_00ed9560(int* out, void* p2, int p3)
{
    int* obj = (int*)FUN_00ed9040(p3, (float*)p2);
    if (obj != 0) {
        float f = g_1470f1c;
        void* v = (void*)((FV_p)(*(void***)obj)[0x2c / 4])(obj);
        FUN_00ed9150(out, (float*)p2, v, f);
    }
    char c = (char)((FV_r0)(*(void***)out)[0x10 / 4])(out);
    if (c == 0) {
        if (obj != 0)
            ((FV_i)(*(void***)out)[8 / 4])(out, 0);
    } else {
        if (obj == 0)
            ((FV_i)(*(void***)out)[0xc / 4])(out, 0);
    }
}

// ================================================================ 0x00ed95d0
// Chooses a noun target pair for the tutorial step and drives the two path
// slots; handles step types 6/9/10 specially and falls back to one operand.
// @ 0x00ed95d0
void __cdecl FUN_00ed95d0(int* out1, int* out2, float* pos, Step95d0* step)
{
    void* r1 = 0;
    void* r2 = 0;
    if (step == 0)
        goto tail;

    if (step->mType == 6 || step->mType == 10) {
        void* mgr = *(void**)((char*)g_16c7aa4 + 0x74);
        void* tA = FUN_00f3e8a0(mgr, 0, (int)step->mA);
        char bl = (tA == 0) ? (char)1 : (char)(FUN_00f25530(tA, 0) != 0);
        void* tB = FUN_00f3e8a0(mgr, 0, (int)step->mB);
        char al = (tB == 0) ? (char)1 : (char)(FUN_00f25530(tB, 0) != 0);
        if (bl == 0) {
            r1 = FUN_00ed9040((int)step->mB, pos);
            if (r1 != 0) {
                float* v = (float*)((FV_p)(*(void***)r1)[0x2c / 4])(r1);
                r2 = FUN_00ed9040((int)step->mA, v);
            } else {
                r1 = FUN_00ed9040((int)step->mA, pos);
            }
        } else if (al == 0) {
            r1 = FUN_00ed9040((int)step->mA, pos);
            if (r1 != 0) {
                float* v = (float*)((FV_p)(*(void***)r1)[0x2c / 4])(r1);
                r2 = FUN_00ed9040((int)step->mB, v);
            } else {
                r1 = FUN_00ed9040((int)step->mB, pos);
            }
        } else {
            r1 = FUN_00ed9040((int)step->mA, pos);
            void* rB = FUN_00ed9040((int)step->mB, pos);
            if (r1 == 0) {
                r2 = 0;
                r1 = rB;
            } else if (rB != 0) {
                r2 = FUN_00ed9040((int)step->mB, (float*)((FV_p)(*(void***)r1)[0x2c / 4])(r1));
                void* alt = FUN_00ed9040((int)step->mA, (float*)((FV_p)(*(void***)rB)[0x2c / 4])(rB));
                float* pa = (float*)((FV_p)(*(void***)r1)[0x2c / 4])(r1);
                float* pb = (float*)((FV_p)(*(void***)r1)[0x2c / 4])(r1);
                float* pc = (float*)((FV_p)(*(void***)r2)[0x2c / 4])(r2);
                float* pd = (float*)((FV_p)(*(void***)rB)[0x2c / 4])(rB);
                float* pe = (float*)((FV_p)(*(void***)rB)[0x2c / 4])(rB);
                float* pf = (float*)((FV_p)(*(void***)alt)[0x2c / 4])(alt);
                float d1 = (pa[0] - pos[0]) * (pa[0] - pos[0]) +
                           (pa[1] - pos[1]) * (pa[1] - pos[1]) +
                           (pa[2] - pos[2]) * (pa[2] - pos[2]);
                float d2 = (pc[0] - pb[0]) * (pc[0] - pb[0]) +
                           (pc[1] - pb[1]) * (pc[1] - pb[1]) +
                           (pc[2] - pb[2]) * (pc[2] - pb[2]);
                float d3 = (pd[0] - pos[0]) * (pd[0] - pos[0]) +
                           (pd[1] - pos[1]) * (pd[1] - pos[1]) +
                           (pd[2] - pos[2]) * (pd[2] - pos[2]);
                float d4 = (pf[0] - pe[0]) * (pf[0] - pe[0]) +
                           (pf[1] - pe[1]) * (pf[1] - pe[1]) +
                           (pf[2] - pe[2]) * (pf[2] - pe[2]);
                if (sqrtf(d1) + sqrtf(d2) > sqrtf(d3) + sqrtf(d4)) {
                    r2 = alt;
                    r1 = rB;
                }
            }
        }
    } else if (step->mType == 9) {
        r1 = FUN_00ed9040((int)step->mA, pos);
        if (r1 != 0) {
            float* v = (float*)((FV_p)(*(void***)r1)[0x2c / 4])(r1);
            r2 = FUN_00ed9040((int)step->mB, v);
        } else {
            r1 = FUN_00ed9040((int)step->mB, pos);
        }
    } else {
        r1 = FUN_00ed9040((int)step->mA, pos);
    }

tail:
    if (r1 != 0) {
        FUN_00ed9150(out1, pos, (void*)((FV_p)(*(void***)r1)[0x2c / 4])(r1), g_1470f1c);
        if (r2 != 0) {
            float* p1 = (float*)((FV_p)(*(void***)r1)[0x2c / 4])(r1);
            float* p2 = (float*)((FV_p)(*(void***)r2)[0x2c / 4])(r2);
            FUN_00ed9150(out2, p1, p2, g_1470f1c);
        }
    }

    void* c1 = *(void**)out1;
    char v1 = (char)((FV_r0)(*(void***)c1)[0x10 / 4])(c1);
    if (v1 != 0) {
        if (r1 == 0)
            ((FV_i)(*(void***)c1)[0xc / 4])(c1, 0);
    } else {
        if (r1 != 0)
            ((FV_i)(*(void***)c1)[8 / 4])(c1, 0);
    }

    void* c2 = *(void**)out2;
    char v2 = (char)((FV_r0)(*(void***)c2)[0x10 / 4])(c2);
    if (v2 != 0) {
        if (r2 == 0)
            ((FV_i)(*(void***)c2)[0xc / 4])(c2, 0);
    } else {
        if (r2 != 0)
            ((FV_i)(*(void***)c2)[8 / 4])(c2, 0);
    }
}

// ================================================================ 0x00ed9990
// StateSync::Set -- feeds the three effect slots and the three paired path
// slots for the current tutorial step / active scenario selection.
// @ 0x00ed9990
void StateSync::Set(int v)
{
    if (m4 == 0)
        return;

    float vec[3] = { 0.0f, 0.0f, 0.0f };
    int keys[3] = { -1, -1, -1 };
    Step95d0* steps[3] = { 0, 0, 0 };

    void* edi = FUN_00efe5a0();
    if (edi != 0) {
        void* esi = FUN_006c0200(edi, 0);
        if (esi != 0) {
            void* q = (void*)((FV_ip)(*(void***)edi)[0xc / 4])(edi, 0x1186577);
            float* vp = (float*)((FV_p)(*(void***)q)[0x2c / 4])(q);
            vec[0] = vp[0];
            vec[1] = vp[1];
            vec[2] = vp[2];

            int active = FUN_00efc520();
            if (*(int*)esi == -2) {
                void* mgr = *(void**)((char*)g_16c7aa4 + 0x74);
                TutVec* tv = (TutVec*)FUN_00f3be60(mgr, 0, active);
                int n = (int)(tv->mEnd - tv->mBegin) / 0x188;
                for (int i = 0; i < n && i < 3; i++)
                    steps[i] = (Step95d0*)((char*)tv->mBegin + i * 0x188);
            } else if (v != 0) {
                void* obj = FUN_00b18530(edi, 0);
                char* arr = (char*)(*(void**)((char*)obj + 0x70)) + active * 0x4e0;
                keys[0] = (int)FUN_00ed8490((int)arr);
                keys[1] = (int)FUN_00ed8500((int)arr);
                keys[2] = (int)FUN_00ed8570((int)arr);
            }
        }
    }

    FUN_00ed9560((int*)&m4, vec, keys[0]);
    FUN_00ed9560((int*)&m8, vec, keys[1]);
    FUN_00ed9560((int*)&mc, vec, keys[2]);
    FUN_00ed95d0((int*)&m10, (int*)&m1c, vec, steps[0]);
    FUN_00ed95d0((int*)&m14, (int*)&m20, vec, steps[1]);
    FUN_00ed95d0((int*)&m18, (int*)&m24, vec, steps[2]);
}

// ================================================================ 0x00ed9b10
struct Obj9b10 { char pad0[0x50]; char m50; char pad1[0x17]; int* m68; void f(); };
void Obj9b10::f()
{
    char* s = (char*)this;
    if (*(s + 0x50) == 0) {
        *(s + 0x50) = 1;
        int* cur = (int*)SP_GetGameTerrainCursor();
        *(int**)(s + 0x68) = cur;
        ((FV_i)(*(void***)cur)[0xb8 / 4])(cur, 0);
    }
}

// ================================================================ 0x00ed9b40
struct Obj9b40 { void f(int a); };
void Obj9b40::f(int a)
{
    (void)a;
    char* s = (char*)this;
    int v = *(int*)(s + 0x6c);
    if (v != 0) {
        FUN_00572020((void*)v, 0);
        *(int*)(s + 0x6c) = 0;
        SetGlobalProperty(0x8dff6314, 0.0f);
    }
}

// ================================================================ 0x00ed9b80
void FUN_00ed9b80(void)
{
    int* gm = (int*)SP_GameInputManager();
    int st = (int)((FV_p)(*(void***)gm)[0x34 / 4])(gm);
    if (st != 4) {
        SP_cTribeInputStrategy_ToggleBanningContent(1);
        int* gm2 = (int*)SP_GameInputManager();
        ((FV_i)(*(void***)gm2)[0x38 / 4])(gm2, 4);
        return;
    }
    SP_cUIBanningContent_EndBanMode(1);
    int* gm3 = (int*)SP_GameInputManager();
    ((FV_i)(*(void***)gm3)[0x38 / 4])(gm3, 0);
}

// ================================================================ 0x00ed9bd0
void FUN_00ed9bd0(void)
{
    int* gm = (int*)SP_GameInputManager();
    int st = (int)((FV_p)(*(void***)gm)[0x34 / 4])(gm);
    if (st != 5) {
        FUN_00e099d0(0);
        int* gm2 = (int*)SP_GameInputManager();
        ((FV_i)(*(void***)gm2)[0x38 / 4])(gm2, 5);
        return;
    }
    FUN_00e09a50(0);
    int* gm3 = (int*)SP_GameInputManager();
    ((FV_i)(*(void***)gm3)[0x38 / 4])(gm3, 0);
}

// ================================================================ 0x00ed9c20
struct Obj9c20 { char pad0[0x14]; unsigned m14; int m18; char m20; void f(); };
void Obj9c20::f()
{
    char* s = (char*)this;
    if (*(s + 0x20) != 0 && *(unsigned*)(s + 0x14) > 0) {
        unsigned e = *(unsigned*)(s + 0x14) - 1;
        *(unsigned*)(s + 0x14) = e;
        *(s + 0x20) = 0;
        int* p = *(int**)(*(int*)s + e * 4);
        ((FV_v)(*(void***)p)[0x10 / 4])(p);
        *(int*)(s + 0x18) += 1;
        *(s + 0x20) = 1;
    }
}

// ================================================================ 0x00ed9c60
struct Obj9c60 { int* m0; int* m4; char pad0[0xc]; unsigned m14; int m18; int m1c; char m20; void f(); };
void Obj9c60::f()
{
    if (m20 != 0 && m14 < (unsigned)((int*)m4 - (int*)m0)) {
        unsigned i = m14;
        m14 = i + 1;
        m20 = 0;
        int* p = *(int**)((char*)m0 + i * 4);
        ((FV_v)(*(void***)p)[0x14 / 4])(p);
        m18 += 1;
        m20 = 1;
    }
}

// ================================================================ 0x00ed9ca0
struct Obj9ca0 { char pad0[0x54]; int m54; int m58; int m5c; int m60; int m64; void f(); };
void Obj9ca0::f()
{
    int h = m54;
    if (h != 0) {
        m54 = 0;
        FUN_00571db0(h, m58, m5c, m60, m64);
    }
    *(char*)((char*)this + 0x50) = 0;
}

// ================================================================ 0x00ed9cd0
// Picks the cursor id for the current game-input strategy / selection mode.
// @ 0x00ed9cd0
bool __stdcall FUN_00ed9cd0(int unused)
{
    (void)unused;
    void* p = FUN_00b3d4d0();
    int t = *(int*)((char*)p + 0x2c);
    if (t == 1 || t == 2)
        return false;

    void* q = FUN_00b3d230();
    if (FUN_00b5ca60(q, 0) == 1)
        return false;

    void* s = FUN_00b3d240();
    void* obj = ((FV_p)(*(void***)s)[0x30 / 4])(s);
    void* edi = 0;
    if (obj != 0)
        edi = (void*)((FV_ip)(*(void***)obj)[0xc / 4])(obj, 0x17f243b);

    void* ebp = FUN_00b18e00(edi);
    void* gm = SP_GameInputManager();
    int ebx = (int)((FV_p)(*(void***)gm)[0x34 / 4])(gm);
    if (FUN_00efcd90() != 0)
        return false;

    unsigned esi = 0x1002;
    if (ebx <= 5) {
        switch (ebx) {
        case 0:
            if (ebp != 0 && ((FV_r0)(*(void***)ebp)[0x24 / 4])(ebp) != 0) {
                int n = (int)((FV_r0)(*(void***)g_15ad298)[0x1c / 4])(g_15ad298) != 0;
                esi = 0x747d67b + (unsigned)n;
            }
            break;
        case 1: {
            unsigned k = (unsigned)FUN_00efc510();
            if (k <= 3) {
                if (k == 0 || k == 1)
                    esi = 0x747d67c;
                else if (k == 2)
                    esi = 0x7391920b;
                else
                    esi = 0xf728e452;
            }
            break;
        }
        case 2:
            esi = 0xe84563d4;
            break;
        case 3:
            if (((FV_r0)(*(void***)g_15ad298)[0x1c / 4])(g_15ad298) != 0) {
                esi = 0x747d67c;
            } else if (ebp != 0 && ((FV_r0)(*(void***)ebp)[0x24 / 4])(ebp) != 0) {
                int n = (int)((FV_r0)(*(void***)g_15ad298)[0x1c / 4])(g_15ad298) != 0;
                esi = 0x747d67b + (unsigned)n;
            }
            break;
        case 4:
            if (edi != 0 && FUN_00dd18b0(edi) != 0)
                esi = 0xf212a38b;
            else
                esi = 0x5ecbdffd;
            break;
        case 5:
            if (edi != 0) {
                esi = 0xf6879190;
                if (FUN_00e09ad0(edi) == 0)
                    esi = 0x5ecbdffd;
            } else {
                esi = 0x5ecbdffd;
            }
            break;
        }
    }

    void* cur = FUN_0067cab0();
    int old = FUN_008013c0(cur, 0);
    if ((int)esi != old)
        FUN_00801bb0(cur, 0, (int)esi);
    return true;
}

// ================================================================ 0x00ed9e60
// UI/banning predicate: blocked when the UI gate is closed or the current
// selection carries one of the tutorial-banning resources.
// @ 0x00ed9e60
bool __stdcall FUN_00ed9e60(char a)
{
    if (g_16065f8 == 0)
        return false;
    if (((FV_r0)(*(void***)g_15ad298)[0x38 / 4])(g_15ad298) != 0)
        return false;

    if (a != 0) {
        if (FUN_008d2fb0(1000) != 0)
            return false;
        if (FUN_008d2fb0(1002) != 0)
            return false;
        if (FUN_008d2fb0(1001) != 0)
            return false;
    }

    void* app = SP_App();
    void* viewer = ((FV_p)(*(void***)app)[0x50 / 4])(app);
    void* obj = ((FV_p)(*(void***)viewer)[0x38 / 4])(viewer);
    if (obj == 0)
        return true;
    void* z = (void*)((FV_ip)(*(void***)obj)[0xc / 4])(obj, 0x11966ed);
    if (z == 0)
        return true;
    return FUN_00b0f9a0(z, 0) == 0;
}
