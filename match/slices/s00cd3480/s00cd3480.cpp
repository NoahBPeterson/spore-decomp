// Slice s00cd3480 -- tribe-mission manager / tribe-mode strategy / terrain helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- globals / vtables (addresses for equivalence mapping) -------------------
extern void* g_vt147734c[];    // 0x0147734c
extern void* g_vt1477328[];    // 0x01477328
extern void* g_vt1477318[];    // 0x01477318
extern void* g_vt154df28[];    // 0x0154df28
extern void* g_vt14774b0[];    // 0x014774b0
extern void* g_appProps;       // 0x015fd918
extern void* g_1581288;        // 0x01581288
extern uint32_t g_169b27c;     // 0x0169b27c
extern const float g_fltmax;   // 0x01477430
extern const char g_StrTRGMac[];    // 0x01477468
extern const char g_StrTRG[];       // 0x01477458
extern const char g_StrTRGBegin[];  // 0x014774a4

// ---- cdecl external callees --------------------------------------------------
void*         FUN_00b3d400(void);                            // 0x00b3d400
void*         NounManager();                                 // 0x00b3d300
void*         GetGameTerrainCursor();                        // 0x00b30d70
void*         GetGameInputManager();                         // 0x00b3d250
void          FUN_00adf390(int a);                           // 0x00adf390
void*         GetTriggerMgr(int a);                          // 0x00b3d4d0
void          FUN_00c77380(void*, int);                      // unused
void          FUN_00c79f00(void*, int, int);                 // unused
void          FUN_00e18200(void* a, void* b, int c, int d, int e); // 0x00e18200
int           FNV1_String8(const char* s, uint32_t h, int a); // 0x00932e80
unsigned char GetPropertyAsUint32Array(void* a, int b, void* c, void* d); // 0x006a0840
void          WriteUint32(void* s, void* p, int a, int b);   // 0x0093aa70

struct CActTarget {
    char pad[0x20];
    void Ctor(void* t, int a);
    void Dtor();
};
struct CTerrain {
    unsigned char F772c0(int key);       // 0x00c772c0
    void F77300(int a);                  // 0x00c77300
    void F77380(int key, int* out);      // 0x00c77380
    void F77bf0(int a);                  // 0x00c77bf0
    void F79f00(int key, int v);         // 0x00c79f00
};
struct CMgr {
    CTerrain* GetCurrentTerrainSphere(); // 0x00f67d90
    void* GetPlayerTribe();              // 0x00bfc5f0
};
struct CTribe { unsigned int GetAdultPopulation(); };  // 0x00c8f370
struct CProps { unsigned char GetDesc(int id); }; // 0x006a25a0
struct C9630 { void M(); };              // 0x00cc9630
struct CUnk { virtual void AddRef(); virtual void Release(); };
struct CTrig { void PostAction(int id, void* tgt, void* c); }; // 0x00ae09b0
struct CPanel {
    unsigned char HasMissionCard(void* card);   // 0x00e15cd0 thiscall ret 4
    void RemoveMissionCard(void* card);          // 0x00e17fb0 thiscall ret 4
    void ExpandMissionCard(void* card);          // 0x00e15b90 thiscall ret 4
    void AddMissionCard(void* card, int a, int b, int c); // 0x00e18200 thiscall ret 0x10
};
struct CAch { void F(int a, int b); };   // 0x00676ed0

struct TM {
    void M_b6f7d0();
    void M_b6f650(int a, int b);
    void M_b6f760();
    void M_b70070();
    void M_b6f820(void* a);
    void M_b6f4e0(void* a);

    void F_cd35c0(int a, int b);
    void F_cd3610();
    void F_cd3650();
    void F_cd3670(void* a);
    void F_cd3760(int a);
    void* F_cd4070(int id);
    void F_cd40f0(void* p);
    unsigned char F_cd4160(void* p);
    void F_cd4180(int a, float f1, float f2, int b);
    void F_cd41d0(float f, int a);
    void F_cd4220(int a, float f1, float f2, int b);
    void F_cd43c0(int a);
    bool F_cd4490();
    unsigned int F_cd4460(int a);
    unsigned int F_cd44a0();
    unsigned int F_cd44e0(void* a, void* b);
    void F_cd3ff0(int kind, void* tgt);
    void F_cd3e60();
};
void F_cd3f20(uint32_t idx);
void F_cd3fb0(int a);
void F_cd3fd0(int a);

// @ 0x00cd35c0
void TM::F_cd35c0(int a, int b)
{
    M_b6f7d0();
    if (*(unsigned char*)((char*)this + 0x70) != 0) {
        int p = *(int*)((char*)this + 0x68);
        if (p) ((void(__thiscall*)(void*))(*(void***)p)[0x80 / 4])((void*)p);
        int q = *(int*)((char*)this + 0x74);
        if (q) ((void(__thiscall*)(void*))(*(void***)q)[0x80 / 4])((void*)q);
        M_b6f650(a, b);
        *(unsigned char*)((char*)this + 0x70) = 0;
    }
}

// @ 0x00cd3610
void TM::F_cd3610()
{
    M_b6f760();
    void* panel = FUN_00b3d400();
    if (panel != 0 && *(int*)((char*)this + 0x74) != 0) {
        if (!((CPanel*)panel)->HasMissionCard(*(void**)((char*)this + 0x74)))
            ((CPanel*)panel)->AddMissionCard(*(void**)((char*)this + 0x74), 0, 1, 0);
    }
}

// @ 0x00cd3650
void TM::F_cd3650()
{
    void* p = *(void**)((char*)this + 0x74);
    if (p != 0) {
        *(void**)((char*)this + 0x74) = 0;
        ((CUnk*)p)->Release();
    }
    M_b70070();
}

// @ 0x00cd3670
void TM::F_cd3670(void* a)
{
    M_b6f820(a);
    if (a == *(void**)((char*)this + 0x74)) {
        if (FUN_00b3d400() != 0) {
            ((CPanel*)FUN_00b3d400())->RemoveMissionCard(*(void**)((char*)this + 0x74));
        }
        void* p = *(void**)((char*)this + 0x74);
        if (p != 0) {
            *(void**)((char*)this + 0x74) = 0;
            ((CUnk*)p)->Release();
        }
    }
}

// @ 0x00cd3760
void TM::F_cd3760(int a)
{
    M_b6f4e0((void*)a);
    if (a != 0) {
        int it0 = 0;
        if (it0 != *(int*)(*(int*)((char*)this + 0x7c) + *(int*)((char*)this + 0x80) * 4)) {
            int p = *(int*)(it0 + 4);
            ((void(__thiscall*)(void*))(*(void***)p)[0x80 / 4])((void*)p);
        }
    }
}

// @ 0x00cd4070
void* TM::F_cd4070(int id)
{
    if (id <= 0x116dd1b) {
        if (id == 0x116dd1b)
            return this;
        if (id != (int)0xee3f516e) {
            if (id != 0x116d389)
                return 0;
            return this;
        }
        goto tail;
    }
    if (id != 0x2f009dd0)
        return 0;
tail:
    if (this == 0)
        return 0;
    return (char*)this + 4;
}

// ============================================================ 0x00cd40c0
unsigned int F_cd40c0(void* tribe)
{
    if (((CMgr*)NounManager())->GetPlayerTribe() != tribe) {
        if (((CTribe*)tribe)->GetAdultPopulation() > 0)
            return 1;
    }
    return 0;
}

// @ 0x00cd4160
unsigned char TM::F_cd4160(void* p)
{
    void* base = (char*)p + 0x34;
    void* o = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    return ((unsigned char(__thiscall*)(void*))(*(void***)o)[0x50 / 4])(o);
}

// @ 0x00cd40f0
void TM::F_cd40f0(void* p)
{
    void* base = (char*)p + 0x34;
    void* o = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    if (!((unsigned char(__thiscall*)(void*))(*(void***)o)[0x50 / 4])(o))
        ((void(__thiscall*)(void*, int))(*(void***)this)[0xf0 / 4])(this, 0x29b);
    void* o2 = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    ((void(__thiscall*)(void*, int))(*(void***)o2)[0x54 / 4])(o2, 1);
    void* cur = GetGameTerrainCursor();
    ((void(__thiscall*)(void*))(*(void***)cur)[0x74 / 4])(cur);
    cur = GetGameTerrainCursor();
    ((void(__thiscall*)(void*))(*(void***)cur)[0xc8 / 4])(cur);
}

// @ 0x00cd4180
void TM::F_cd4180(int a, float f1, float f2, int b)
{
    void* in = (char*)this + 0x1e0;
    ((void(__thiscall*)(void*, int, float, float, int))(*(void***)in)[0 / 4])(in, a, f1, f2, b);
    void* m = GetGameInputManager();
    ((void(__thiscall*)(void*, int, float, float, int))(*(void***)m)[0x54 / 4])(m, a, f1, f2, b);
}

// @ 0x00cd41d0
void TM::F_cd41d0(float f, int a)
{
    void* in = (char*)this + 0x1e0;
    ((void(__thiscall*)(void*, float, int))(*(void***)in)[0 / 4])(in, f, a);
    void* m = GetGameInputManager();
    ((void(__thiscall*)(void*, float, int))(*(void***)m)[0x5c / 4])(m, f, a);
}

// @ 0x00cd4220
void TM::F_cd4220(int a, float f1, float f2, int b)
{
    void* in = (char*)this + 0x1e0;
    ((void(__thiscall*)(void*, int, float, float, int))(*(void***)in)[0 / 4])(in, a, f1, f2, b);
    void* m = GetGameInputManager();
    ((void(__thiscall*)(void*, int, float, float, int))(*(void***)m)[0x58 / 4])(m, a, f1, f2, b);
}

// @ 0x00cd43c0
void TM::F_cd43c0(int a)
{
    void* o = ((void*(__thiscall*)(void*, int))(*(void***)this)[0x6c / 4])(this, a);
    ((C9630*)o)->M();
    (void)o;
    (void)a;
}

// @ 0x00cd4460
unsigned int TM::F_cd4460(int a)
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        if (s->F772c0(a))
            return 1;
    }
    return 0;
}

// @ 0x00cd4490
bool TM::F_cd4490()
{
    return *(int*)((char*)this + 0x22c) != 0xb;
}

// @ 0x00cd44a0
unsigned int TM::F_cd44a0()
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        if (s->F772c0(0x056d1871))
            return 0;
    }
    return 1;
}

// @ 0x00cd44e0
unsigned int TM::F_cd44e0(void* a, void* b)
{
    uint32_t v = *(uint32_t*)b;
    void* p = ((void*(__thiscall*)(void*))(*(void***)a)[0x20 / 4])(a);
    void* s = ((void*(__thiscall*)(void*))(*(void***)p)[0x18 / 4])(p);
    WriteUint32(s, &v, 1, 0);
    return 1;
}

// @ 0x00cd3e60
void TM::F_cd3e60()
{
    unsigned int r;
    if (((CProps*)g_appProps)->GetDesc(0x061b67b6) != 0)
        r = (unsigned int)FNV1_String8(g_StrTRGMac, 0x811c9dc5, 1);
    else
        r = (unsigned int)FNV1_String8(g_StrTRG, 0x811c9dc5, 1);
    (void)r;
}

// @ 0x00cd3f20
void F_cd3f20(uint32_t idx)
{
    int local_c = 0;
    int local_8 = 0;
    if (GetPropertyAsUint32Array(g_1581288, 0xf5bf4d8e, &local_c, &local_8)
        && local_c > 0 && (uint32_t)local_c > idx) {
        CTerrain* te = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
        int v = *(int*)(local_8 + (int)idx * 4);
        int local_4 = 0;
        te->F77380(0x055d6335, &local_4);
        te->F79f00(0x055d6335, local_4 + v);
    }
}

// @ 0x00cd3fb0
void F_cd3fb0(int a)
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        s->F77bf0(a);
        return;
    }
}

// @ 0x00cd3fd0
void F_cd3fd0(int a)
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        s->F77300(a);
        return;
    }
}

// @ 0x00cd3ff0
void TM::F_cd3ff0(int kind, void* tgt)
{
    int id;
    switch (kind) {
    case 0: id = 0x4dbdc67d; break;
    case 1: id = 0x4dbdc67e; break;
    case 2: id = 0x4dbdc67f; break;
    case 3: id = 0x4dbdc678; break;
    case 4: id = 0x4dbdc679; break;
    default: return;
    }
    CActTarget t;
    t.Ctor(tgt, 0);
    CTrig* mgr = (CTrig*)GetTriggerMgr(0);
    mgr->PostAction(id, &t, 0);
    t.Dtor();
}

// @ 0x00cd4580
struct ThemeMgr { char pad[0x100]; ThemeMgr(); };
ThemeMgr::ThemeMgr()
{
    float m = g_fltmax;
    *(int*)((char*)this + 4) = 0;
    *(void**)this = g_vt14774b0;
    int* p = (int*)((char*)this + 8);
    int n = 0x17;
    do {
        *p = 0;
        *(float*)(p + 1) = m;
        p += 2;
        --n;
    } while (n >= 0);
}

// ---- complex: best-effort / partial ------------------------------------------
// @ 0x00cd3480
void F_cd3480(int* s) { (void)s; }
// @ 0x00cd3530
void F_cd3530(int* s) { (void)s; }
// @ 0x00cd36f0
unsigned char F_cd36f0(void* a, void* b) { (void)a; (void)b; return 1; }
// @ 0x00cd37b0
void F_cd37b0(void* a, void* b) { (void)a; (void)b; }
// @ 0x00cd3920
unsigned char F_cd3920(void* a, int b, int c) { (void)a; (void)b; (void)c; return 1; }
// @ 0x00cd3ab0
void F_cd3ab0(void* self) { (void)self; }
// @ 0x00cd3b60
void* F_cd3b60(void* self) { (void)self; return 0; }
// @ 0x00cd3bf0
void F_cd3bf0(void* self, void* a) { (void)self; (void)a; }
// @ 0x00cd4280
void F_cd4280() {}
// @ 0x00cd43e0
void F_cd43e0(void* self, void* v) { (void)self; (void)v; }
