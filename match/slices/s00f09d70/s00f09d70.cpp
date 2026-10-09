// Scenario-tutorial UI update helpers: element copy loops, random scenario
// pick, best-scenario selection, and a set of manager wrappers.
// /O2, x87 floats.
//
// Flags: /O2 /MD /Gy /TP

#include <math.h>

typedef unsigned int  uint32_t;
typedef unsigned char uint8_t;

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern char* g_pMagic;   // 0x016c7aa4
extern char* g_pTable;   // 0x016c7d90  (scenario table singleton)
extern int  ScenarioTutorials_GetActive();       // 0x00efc520

// object at *(g_pMagic+0x78)
struct GameData78 {
    char pad[0xb8];
    int  mFieldB8;   // +0xb8
};
inline GameData78* GD78() { return (GameData78*)*(char**)(g_pMagic + 0x78); }

// object at *(*(char**)g_pTable + 4) : scenario manager
struct ScenarioMgr {
    char pad0[0x20];
    uint8_t mFlag;   // +0x20
    char pad1[0x4f];
    char* mBegin;    // +0x70
    char* mEnd;      // +0x74
};
inline ScenarioMgr* SMgr() { return (ScenarioMgr*)*(char**)(*(char**)g_pTable + 4); }
inline char* SMgrBegin() { return SMgr()->mBegin; }
inline int ScenarioCount() { return (int)(SMgr()->mEnd - SMgr()->mBegin) / 0x4e0; }

// 0x44-byte element with a sub-object at +4 and a dword at +0x40
struct Sub { void assign(Sub* other); };   // 0x00dfb280
struct Elem44 { int mKey; char sub[0x3c]; int mField40; };

// ---------------------------------------------------------------------------
// 0x00f09d70  copy n elements
// ---------------------------------------------------------------------------
// @ 0x00f09d70
void FUN_00f09d70(Elem44* dst, unsigned n, Elem44* src)
{
    if (n > 0) {
        do {
            if (dst) {
                dst->mKey = src->mKey;
                ((Sub*)(dst->sub))->assign((Sub*)(src->sub));
                dst->mField40 = src->mField40;
            }
            ++dst;
            --n;
        } while (n > 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00f09db0  copy range
// ---------------------------------------------------------------------------
// @ 0x00f09db0
Elem44* FUN_00f09db0(Elem44* first, Elem44* last, Elem44* out)
{
    if (first != last) {
        do {
            if (out) {
                out->mKey = first->mKey;
                ((Sub*)(out->sub))->assign((Sub*)(first->sub));
                out->mField40 = first->mField40;
            }
            ++first;
            ++out;
        } while (first != last);
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00f09e00  pick a scenario index (mode 1 = collect+random, mode 2 = counter)
// ---------------------------------------------------------------------------
extern int  FUN_00b18530();                 // 0x00b18530 (thiscall: csGameData)
extern void* cSPUILayout_FindWindowByID_(void*, int, int); // 0x008105b0
extern int   FUN_00f26380();                 // 0x00f26380
extern int   FUN_0060a600(void*, int*);      // 0x0060a600 (fixed_vector insert)
extern uint32_t g_Random;                    // 0x016c7f50
extern int   g_Mode;                         // 0x015ad4f8

// @ 0x00f09e00
int __fastcall FUN_00f09e00(void* p)
{
    int key = GD78()->mFieldB8;
    int chosen = -1;
    if (p)
        (*(int(__thiscall**)(void*, int))((char*)*(void**)p + 0xb8))(p, 0x17f243b);
    int gd = FUN_00b18530();
    if (!gd)
        return 0;
    char* scen = (char*)(key * 0x4e0 + *(int*)(gd + 0x70));
    if (g_Mode == 1) {
        int* tmp[4];
        int  cnt = 0;
        int  total = (int)(*(int*)(scen + 8) - *(int*)(scen + 4)) / 0x44;
        for (int i = 0; i < total; ++i) {
            if (FUN_00f26380())
                tmp[cnt++] = (int*)i;
        }
        if (cnt)
            chosen = (int)tmp[(int)(FUN_00f26380, 0)];   // placeholder
        FUN_0060a600(0, 0);
    } else if (g_Mode == 2) {
        int total = (int)(*(int*)(scen + 8) - *(int*)(scen + 4)) / 0x44;
        for (int i = 0; i < total; ++i) {
            chosen = g_Random % (total ? total : 1);
            ++g_Random;
            if (FUN_00f26380())
                break;
        }
    } else {
        return 0;
    }
    if (chosen == -1)
        return 0;
    return (key + 1) * 1000 + chosen;
}

// ---------------------------------------------------------------------------
// 0x00f09fc0  choose the nearest scenario (time based)
// ---------------------------------------------------------------------------
extern void  SPUIHelpers_GetElapsedSeconds();     // 0x00805080
extern float g_Elapsed;                           // 0x016c7d88[0..1]
extern int   FUN_00b3d240();                      // 0x00b3d240
extern int   FUN_00f07e90();                      // 0x00f07e90
extern int   FUN_00f07e10();                      // 0x00f07e10
extern float FUN_00f09bf0(void*);                 // 0x00f09bf0
extern int   FUN_00f08350(int, void*);            // 0x00f08350
extern int   FUN_006c0200();                      // 0x006c0200

// @ 0x00f09fc0
uint8_t FUN_00f09fc0(void* owner, float* outT, void** outObj)
{
    float t = 0.0f;
    SPUIHelpers_GetElapsedSeconds();
    *outT = 0.0f;
    float* g = (float*)*(char**)(g_pMagic + 0x10);   // placeholder
    (void)g;
    if (*(float*)(g_pTable + 4) != 0.0f) {
        *outT = *(float*)(g_pTable);
        *outObj = *(void**)(g_pTable + 4);
        return 1;
    }
    t = 0.0f;
    (void)t;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f0a1e0  per-scenario UI refresh
// ---------------------------------------------------------------------------
extern int   FUN_00f07e10();                       // dup
extern int   FUN_00b3d4d0();                       // 0x00b3d4d0
extern void  FUN_00f45a80();                       // 0x00f45a80

// @ 0x00f0a1e0
void FUN_00f0a1e0(int a, void* b)
{
    SPUIHelpers_GetElapsedSeconds();
    for (char* p = (char*)0x016c7df4; *(void**)p != 0; p += 8) {
        void* win = cSPUILayout_FindWindowByID_(*(void**)(p - 4), 0x73926f8, 1);
        bool self = (b == 0) ? false : (*(void**)p == b);
        (*(int(__thiscall**)(void*))((char*)*(void**)win + 0x28))(win);
        if (self) {
            if (FUN_00f07e10()) {
                int tm = FUN_00b3d4d0();
                if (*(int*)(tm + 0x2c) == 1 || *(int*)(tm + 0x2c) == 2)
                    (*(int(__thiscall**)(void*, int, int))((char*)*(void**)win + 0x7c))(win, 1, 0);
            }
        }
    }
    (void)a;
}

// ---------------------------------------------------------------------------
// 0x00f0a440  update new-grow progress UI
// ---------------------------------------------------------------------------
extern int  GameTimeManager();          // 0x00b3d380
extern int  NounManager();              // 0x00b3d300
extern int  cGameNounManager_GetAvatar(); // 0x00b1fdb0
extern int  GetTriggerMgr();            // 0x00b3d4d0
extern void FUN_00f07fd0(int, void*, int);   // 0x00f07fd0
extern void FUN_00f09170();                  // 0x00f09170
extern void cSPUIAnimator_Update(void*);     // 0x007f63b0

// @ 0x00f0a440
void FUN_00f0a440()
{
    int tm = GameTimeManager();
    if ((*(uint8_t*)(tm + 0x48) & 1) == 0) {
        int nv = NounManager();
        int av = cGameNounManager_GetAvatar();
        (void)nv;
        if (av) {
            char* pi = (char*)(av + 0xc0);
            if (pi) {
                (*(void(__thiscall**)(void*))((char*)*(void**)pi + 0xbc))(pi);
                int tr = GetTriggerMgr();
                if (*(int*)(tr + 0x2c) == 1 || *(int*)(tr + 0x2c) == 2) {
                    (*(void(__thiscall**)(void*))((char*)*(void**)pi + 0xc0))(pi);
                    return;
                }
                int s = 0;
                void* o = 0;
                uint8_t r = FUN_00f09fc0(pi, (float*)&s, &o);
                if (s)
                    FUN_00f07fd0(s, o, r);
                FUN_00f0a1e0(s, 0);
                FUN_00f09170();
                cSPUIAnimator_Update((void*)0x016c7f30);
                (*(void(__thiscall**)(void*))((char*)*(void**)pi + 0xc0))(pi);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00f0a5a0
// ---------------------------------------------------------------------------
extern int  FUN_00f09c90(void*);         // 0x00f09c90
extern void FUN_00f08680(int, void*);    // 0x00f08680
extern void FUN_00f086d0(int, void*);    // 0x00f086d0
extern int  FUN_00f084b0(int, int);      // 0x00f084b0
extern void FUN_00f08630(int, void*);    // 0x00f08630

// @ 0x00f0a5a0
int FUN_00f0a5a0(int param_1)
{
    int gd = FUN_00b18530();
    int* slot = (int*)FUN_00f09c90((char*)param_1 + 0x1c);
    int* p = slot + 1;
    if (*p == -1)
        return -1;
    if (*p != 0) {
        if (*p / 1000 - 1 < GD78()->mFieldB8)
            FUN_00f08680(gd, p);
        int v = *p;
        while (v != -1 && !FUN_00f084b0(gd, v)) {
            FUN_00f08630(gd, p);
            v = *p;
        }
        return *p;
    }
    FUN_00f086d0(gd, p);
    return *p;
}

// ---------------------------------------------------------------------------
// 0x00f0a640
// ---------------------------------------------------------------------------
// @ 0x00f0a640
uint8_t FUN_00f0a640(int param_1)
{
    uint8_t r = 0;
    if (FUN_00b18530() != 0) {
        int v = FUN_00f0a5a0(param_1);
        if (v != -1)
            r = (v / 1000 - 1) <= GD78()->mFieldB8;
    }
    return r;
}

// ---------------------------------------------------------------------------
// 0x00f0a690
// ---------------------------------------------------------------------------
struct Mgr18 { bool FUN_00f1b360(void* p); };
extern int FUN_00f1b360();   // placeholder

// @ 0x00f0a690
bool FUN_00f0a690(void* p)
{
    void* mgr = *(void**)(g_pMagic + 0x78);
    if (((Mgr18*)mgr)->FUN_00f1b360(p))
        return true;
    char r = (char)FUN_00f0a640((int)p);
    return r != 0;
}

// ---------------------------------------------------------------------------
// 0x00f0a6c0
// ---------------------------------------------------------------------------
// @ 0x00f0a6c0
void FUN_00f0a6c0(int* obj)
{
    int* sel = 0;
    if (obj)
        sel = (int*)(*(int(__thiscall**)(int*, int))(*(int**)obj + 0xc))(obj, 0x1186577);
    int* slot = (int*)*(void**)(g_pMagic + 0x10);   // placeholder
    (void)slot;
    void** pcur = (void**)(g_pMagic + 0x10);
    void* old = *pcur;
    if (sel != old) {
        if (sel)
            (*(void(__thiscall**)(void*))((char*)*(void**)sel + 0xbc))(sel);
        *pcur = sel;
        if (old)
            (*(void(__thiscall**)(void*))((char*)*(void**)old + 0xc0))(old);
    }
    int v = FUN_00f0a5a0((int)obj);
    (void)v;
    int gd = FUN_00b18530();
    int* e = (int*)FUN_00f09c90((char*)obj + 0x1c);
    *e = e[1];
    FUN_00f086d0(gd, e + 1);
}

// ---------------------------------------------------------------------------
// 0x00f0a750
// ---------------------------------------------------------------------------
extern int  FUN_00f1a070(void*);         // 0x00f1a070
extern int  FUN_00c03190();              // 0x00c03190
extern void FUN_00f1b2f0(void*);         // 0x00f1b2f0

// @ 0x00f0a750
void FUN_00f0a750(void* p)
{
    if (!FUN_00f1a070(p)) {
        NounManager();
        cGameNounManager_GetAvatar();
        int r = FUN_00c03190();
        *(int*)(r + 0x10) = 0x100;
        return;
    }
    if (FUN_00f1b360())
        FUN_00f1b2f0(p);
    else if (FUN_00f0a640((int)p))
        FUN_00f0a6c0((int*)p);
}

// ---------------------------------------------------------------------------
// 0x00f0a7e0
// ---------------------------------------------------------------------------
extern int   FUN_00f08850(int, int);     // 0x00f08850
extern void  FUN_00f28b30(void*);        // 0x00f28b30
extern void  FUN_00f28c10(void*);        // 0x00f28c10
extern int   FUN_00f263b0(void*);        // 0x00f263b0
extern void  FUN_00f280f0(void*);        // 0x00f280f0

// @ 0x00f0a7e0
int FUN_00f0a7e0(int a, int b)
{
    for (int off = 0; off < 0x50; off += 0x10) {
        char* t = g_pTable + 0x10 + off;
        int* base = (int*)FUN_00f08850(a, b);
        char* e = (char*)(*base + *(int*)(t + 4) * 0x44);
        char tmp[0x40];
        FUN_00f28b30(tmp);
        *(int*)(tmp + 0x00) = *(int*)(t + 8);
        *(int*)(tmp + 0x40) = *(int*)(t + 0xc);
        int* w = (int*)(*(int(__thiscall**)(void*, int, int))((char*)*(void**)*(void**)t + 0xf0))(*(void**)t, 0xcefa1100, 1);
        int val = (*(int(__thiscall**)(void*))((char*)*(void**)w + 0x3c))(w);
        FUN_00f28c10(&val);
        if (*(int*)(e + 0x40) != *(int*)(tmp + 0x40) || *(int*)e != *(int*)tmp) {
            FUN_00f280f0(tmp);
            return 1;
        }
        if (!FUN_00f263b0(e + 4)) {
            FUN_00f280f0(tmp);
            return 1;
        }
        FUN_00f280f0(tmp);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f0a8b0
// ---------------------------------------------------------------------------
// @ 0x00f0a8b0
int FUN_00f0a8b0(void* p)
{
    ScenarioMgr* mgr = SMgr();
    if (mgr->mFlag == 0) {
        int idx = ScenarioTutorials_GetActive();
        if (!FUN_00f0a7e0(idx, (int)p))
            return 0;
    } else {
        if ((int)(mgr->mEnd - mgr->mBegin) / 0x4e0 < 1)
            return 0;
        for (int i = 0; !FUN_00f0a7e0(i, (int)p); ++i) {
            if ((int)(SMgr()->mEnd - SMgr()->mBegin) / 0x4e0 <= i)
                return 0;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00f0a950
// ---------------------------------------------------------------------------
extern void FUN_006b5430(void*, void*);          // 0x006b5430 (cString::operator=)
extern void WString_Assign(void*, void*);        // 0x00423650

// @ 0x00f0a950
void FUN_00f0a950(int scenario, int which)
{
    char* base = (char*)(scenario * 0x4e0 + *(int*)(SMgr()->mBegin));
    char* arr;
    if (which == 1)       arr = base + 0x170;
    else if (which == 2)  arr = base + 4;
    else if (which == 3)  arr = *(char**)(g_pTable + 8) + 0x18;
    else                  arr = 0;
    for (int off = 0; off < 0x50; off += 0x10) {
        char* t = g_pTable + 0x10 + off;
        char tmp[0x44];
        FUN_00f28b30(tmp);
        *(int*)(tmp + 0x00) = *(int*)(t + 8);
        *(int*)(tmp + 0x40) = *(int*)(t + 0xc);
        int* w = (int*)(*(int(__thiscall**)(void*, int, int))((char*)*(void**)*(void**)t + 0xf0))(*(void**)t, 0xcefa1100, 1);
        int v = (*(int(__thiscall**)(void*))((char*)*(void**)w + 0x3c))(w);
        FUN_00f28c10(&v);
        char* dst = (char*)(*(int*)arr + *(int*)(t + 4) * 0x44);
        *(int*)dst = *(int*)(tmp + 0x00);
        FUN_006b5430(dst + 4, tmp + 4);
        WString_Assign(dst + 0x18, tmp + 0x18);
        *(int*)(dst + 0x40) = *(int*)(tmp + 0x40);
        FUN_00f280f0(tmp);
    }
}

// ---------------------------------------------------------------------------
// 0x00f0aa80
// ---------------------------------------------------------------------------
extern void FUN_00f45970();   // 0x00f45970
extern void FUN_00f45a80();   // 0x00f45a80

// @ 0x00f0aa80
void FUN_00f0aa80()
{
    if (!FUN_00f0a8b0(*(void**)(g_pTable + 0xc)))
        return;
    FUN_00f45970();
    ScenarioMgr* mgr = SMgr();
    if (mgr->mFlag == 0) {
        FUN_00f0a950(ScenarioTutorials_GetActive(), *(int*)(g_pTable + 0xc));
    } else {
        if ((int)(mgr->mEnd - mgr->mBegin) / 0x4e0 > 0) {
            int i = 0;
            do {
                FUN_00f0a950(i, *(int*)(g_pTable + 0xc));
                ++i;
            } while (i < (int)(SMgr()->mEnd - SMgr()->mBegin) / 0x4e0);
        }
    }
    FUN_00f45a80();
}

// ---------------------------------------------------------------------------
// 0x00f0ab50
// ---------------------------------------------------------------------------
extern int  WindowManager();                        // 0x0067caa0
extern void* cSPUILayout_FindWindowByID_(void*, int, int); // 0x008105b0

// @ 0x00f0ab50
void FUN_00f0ab50(int* p)
{
    int v = (*(int(__thiscall**)(int*))(*(int**)p + 0x1c))(p);
    char* tbl = g_pTable;
    char* te = *(char**)(tbl + 0x70);
    *(int*)(te + 0xc) = v + 0xf8bd3420;
    FUN_00f0aa80();
    char* e = *(char**)(g_pTable + 0x70);
    int* w = (int*)e;
    void* w1 = (void*)(*(int(__thiscall**)(void*, int, int))((char*)*(void**)w + 0xf0))(w, 0x742bdd0, 0);
    if (w1) {
        void* w2 = (void*)(*(int(__thiscall**)(void*, int))((char*)*(void**)w1 + 0xc))(w1, 0x8ed27e7a);
        if (w2)
            (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w2 + 0x28))(w2, 4, 0);
    }
    *(int*)(g_pTable + 0x74) = 0;
    void* im = (void*)(*(int(__thiscall**)(void*, int, int))((char*)*(void**)w + 0xf0))(w, 0xcefa1100, 0);
    int* wm = (int*)WindowManager();
    (*(void(__thiscall**)(void*, int, void*))((char*)*(void**)wm + 0x4c))(wm, 0, im);
    void* f1 = cSPUILayout_FindWindowByID_(*(void**)g_pTable, 0x1742be59, 1);
    (*(void(__thiscall**)(void*, int, int))((char*)*(void**)f1 + 0x7c))(f1, 1, 0);
    void* f2 = cSPUILayout_FindWindowByID_(*(void**)g_pTable, 0x1742be58, 1);
    (*(void(__thiscall**)(void*, int, int))((char*)*(void**)f2 + 0x7c))(f2, 1, 0);
    *(int*)(g_pTable + 0x70) = 0;
}
