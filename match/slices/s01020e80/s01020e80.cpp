// Slice s01020e80 -- SP::cSPLivingUniverse accessors + cSPBackgroundSimManager
// (0x01020e80..0x01021e4c).  Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned int   uintptr_t;
typedef int            intptr_t;

// ---------------------------------------------------------------------------
extern void* DAT_016dda8c;                 // gspBackgroundSimManager singleton
extern float DAT_016dda90, DAT_016dda94, DAT_016dda98;
extern u32   DAT_016ddb10;
extern float DAT_013f9428, DAT_01485720, DAT_013ec4b8;
extern u32   DAT_01495910;
extern u32   DAT_015b7080;
extern void* DAT_01654c04;
extern void* DAT_01654c02;

// ---------------------------------------------------------------------------
// free callees
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b3d2a0();                        // StarManager
void* __cdecl FUN_00ffbe50();                        // GetUFOSimulator
void* __cdecl FUN_0067de00();                        // 0x0067de00
void* __cdecl FUN_0067dd80();                        // SP::ModelManager
void* __cdecl FUN_0067dcc0();                        // SP::MessageServer
void* __cdecl FUN_0067de30();                        // SP::PropertyManager
void* __cdecl FUN_00b5b800();                        // GetCurrentGameMode
void* __cdecl FUN_00b3d350();                        // SP::PlanetModel
void* __cdecl FUN_00b3d380();                        // GameTimeManager
void* __cdecl FUN_00675250(u32, int);                // AchievementsController
void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int);
void  __cdecl FUN_00f47380(void*);
void* __cdecl FUN_00c70f90_float(void*, int);        // 0x00c70f90
void* __cdecl FUN_00c70e20(void*, int);              // 0x00c70e20
float* __cdecl FUN_0059c190(void*, const void*);     // Matrix3FromQuaternion
void  __cdecl FUN_0059aed0(void*, void*, void*);     // QuaternionFromDirections
void  __cdecl FUN_0041cb40(void*, const void*);      // Matrix3::Assign
void* __cdecl FUN_0040efa0();                        // PartTransform::Invert
void* __cdecl FUN_008414c0();
void  __cdecl FUN_00e39ab0_ctor(void*, void*, void*, int);   // 0x692f90
void  __cdecl FUN_00e39ab0_serialize(void*, int);            // 0x692900
void  __cdecl FUN_00c8b360_free(void*, void*);               // placeholder
void  __cdecl FUN_01001360(void*, void*);                    // 0x1001360
void  __cdecl FUN_0040efa0_rw(void);                         // placeholder
void  __cdecl FUN_0105c3d0v();                               // placeholder

// thiscall callees
struct Ext {
    void* FUN_0101fb40();
    void* FUN_00c70f90(int);                 // float
    void  FUN_01017bb0();
    void* FUN_00c70c00();
    void  FUN_00c82f00();
    void* FUN_00c71e70();
    void* FUN_00c8b360();
    void  FUN_00c8b800();
    void* FUN_00c31730();
    void* FUN_00ba9370();
    void  FUN_00bb3750();
    void  FUN_00bb59b0();
    void* FUN_00b8de30();
    void  FUN_00b3d2a0i(int);    void  FUN_00ad92d0();
    void* FUN_00ff3f00();
    void  FUN_0140efa0();
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }

static inline void RefAssign(int*& dst, int* src) {
    int* old = dst;
    if (src != old) {
        if (src) ((void(__thiscall*)(void*))VTP(src)[0xbc / 4])(src);
        dst = src;
        if (old) ((void(__thiscall*)(void*))VTP(old)[0xc0 / 4])(old);
    }
}
static inline void Release(int* p) {
    if (p) ((void(__thiscall*)(void*))VTP(p)[0xc0 / 4])(p);
}
static inline void AddRef2(int* p) {
    if (p) ((void(__thiscall*)(void*))VTP(p)[0xbc / 4])(p);
}

// ===========================================================================
// 0x01020e80
// ===========================================================================
// @ 0x01020e80
struct Cam { char f20e80(int msg, int* p); };
char Cam::f20e80(int msg, int* p) {
    if (msg == 0xf62def && *(int*)((char*)p + 0x18) == 0x521d0174) {
        E((char*)this - 4)->FUN_0101fb40();
    }
    return 0;
}

// ===========================================================================
// 0x01020eb0  (approximate)
// ===========================================================================
// @ 0x01020eb0
void FUN_01020eb0(void* self, int param_2, int param_3) {
    char* s = (char*)self;
    int local = 100;
    int* p = &param_2;
    if (param_2 >= 100) p = &local;
    FUN_00b3d380();
    (void)param_3;
}

// ===========================================================================
// 0x01020fc0
// ===========================================================================
// @ 0x01020fc0
void FUN_01020fc0(void* self) {
    char* s = (char*)self;
    E(s)->FUN_0101fb40();
    void* edi = (s == 0) ? 0 : (s + 4);
    void* ms = FUN_0067dcc0();
    *(void**)(s + 0x18) = ms;
    *(void**)(s + 0x1c) = edi;
    *(void**)(s + 0x20) = &DAT_01495910;
    *(u32*)(s + 0x24) = 1;
    *(u32*)(s + 0x28) = 0;
    if (ms && edi)
        ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, edi, 0xf62def);
}

// ===========================================================================
// 0x01021020
// ===========================================================================
// @ 0x01021020
void FUN_01021020(void* self) {
    char* s = (char*)self;
    FUN_01020fc0(self);
    int* p = (int*)(s + 0x84);
    if (*p == 0) {
        void* pman = FUN_0067de30();
        int old = *p;
        if (old) {
            *p = 0;
            ((void(__thiscall*)(void*))VTP((void*)old)[1])((void*)old);
        }
        ((void(__thiscall*)(void*, u32, u32, void*))VTP(pman)[0x2c / 4])(
            pman, 0x1106d054, 0x2ae0c7e, p);
    }
}

// ===========================================================================
// 0x010210a0 SP::cSPLivingUniverse::Write  (approximate)
// ===========================================================================
// @ 0x010210a0
void __stdcall FUN_010210a0(int param) {
    u8 buf[0xa14];
    u32 g = (u32)(uintptr_t)DAT_016dda8c;
    FUN_00e39ab0_ctor(buf, (void*)g, (void*)0x15b70d0, 0x1a80d26);
    FUN_00e39ab0_serialize(buf, param);
}

// ===========================================================================
// 0x010210e0
// ===========================================================================
// @ 0x010210e0
void FUN_010210e0(void* planet) {
    char c = (char)(intptr_t)E(planet)->FUN_00c70c00();
    if (c) {
        void* x = FUN_008414c0();
        ((void(__thiscall*)(void*))VTP(x)[0x20 / 4])(x);
        return;
    }
    void* p2 = E(planet)->FUN_00c71e70();
    ((void(__thiscall*)(void*))VTP(p2)[0x20 / 4])(p2);
}

// ===========================================================================
// 0x01021110
// ===========================================================================
// @ 0x01021110
int FUN_01021110(void* a, void* b) {
    float f1 = (float)(intptr_t)E(a)->FUN_00c70f90(2);
    float f2 = (float)(intptr_t)E(b)->FUN_00c70f90(2);
    return (f1 < f2) ? 1 : 0;
}

// ===========================================================================
// 0x01021180
// ===========================================================================
// @ 0x01021180
int* FUN_01021180(int* a, int* b, int* c, int (*cmp)(int, int)) {
    if (cmp(*a, *b) != 0) {
        if (cmp(*b, *c) == 0) {
            if (cmp(*a, *c) != 0) return c;
            return a;
        }
        return b;
    }
    if (cmp(*a, *c) != 0) return a;
    if (cmp(*b, *c) != 0) return c;
    return b;
}

// ===========================================================================
// 0x01021200
// ===========================================================================
// @ 0x01021200
void __stdcall FUN_01021200(int a, int b) {
    void* gm = FUN_00b5b800();
    if (gm != &DAT_01654c04) {
        gm = FUN_00b5b800();
        if (gm != &DAT_01654c02) return;
    }
    void* s = DAT_016dda8c;
    void* o = *(void**)((char*)s + 0xc);
    ((void(__thiscall*)(void*))VTP(o)[0xc / 4])(o);
    (void)a; (void)b;
}

// ===========================================================================
// 0x01021240 SP::cSPMission::IsArchived
// ===========================================================================
// @ 0x01021240
int FUN_01021240() {
    int* p = *(int**)((char*)DAT_016dda8c + 8);
    if (p) return *(int*)((char*)p + 0x48);
    return 0;
}

// ===========================================================================
// 0x01021260 SP::cSPLivingUniverse::GetActivePlanet
// ===========================================================================
// @ 0x01021260
void* FUN_01021260() {
    void* s = DAT_016dda8c;
    void* p = *(void**)((char*)s + 4);
    return p;
}

// ===========================================================================
// 0x010212a0 SP::cSPLivingUniverse::GetActivePlanetRecord
// ===========================================================================
// @ 0x010212a0
void* FUN_010212a0() {
    void* s = DAT_016dda8c;
    void* p = *(void**)((char*)s + 4);
    if (!p) return 0;
    return *(void**)((char*)p + 0x13c);
}

// ===========================================================================
// 0x01021300 SP::cSPLivingUniverse::GetPlayerEmpire
// ===========================================================================
// @ 0x01021300
void* FUN_01021300() {
    int* s = (int*)DAT_016dda8c;
    int id = s[6];
    if (id == -1) return 0;
    int* old = (int*)s[7];
    if (old && old[0x21] == id) return old;
    void* sm = FUN_00b3d2a0();
    int* got = (int*)((void*(__thiscall*)(void*, int))VTP(sm)[0 / 4])(sm, id);
    int*& slot = (int*&)s[7];
    if (got != old) {
        if (got) ((void(__thiscall*)(void*))VTP(got)[0])(got);
        slot = got;
        if (old) ((void(__thiscall*)(void*))VTP(old)[1])(old);
    }
    return slot;
}

// ===========================================================================
// 0x01021370 SP::cSPLivingUniverse::GetPlayerHomePlanet
// ===========================================================================
// @ 0x01021370
void* FUN_01021370() {
    void* emp = FUN_01021300();
    if (!emp) return 0;
    void* home = E(FUN_01021300())->FUN_00c31730();
    if (home) return E(FUN_01021300())->FUN_00c31730();
    void* ap = FUN_01021260();
    return *(void**)((char*)ap + 0x13c);
}

// ===========================================================================
// 0x010213b0
// ===========================================================================
// @ 0x010213b0
void FUN_010213b0(int param) {
    if (param != 2) return;
    int* s = (int*)DAT_016dda8c;
    int* one = (int*)s[2];
    void* ufo = FUN_00ffbe50();
    if (one && ufo) {
        void* r = ((void*(__thiscall*)(void*))VTP(one)[0 / 4])(one);
        (void)r;
    }
}

// ===========================================================================
// 0x01021420  (approximate heap sort)
// ===========================================================================
// @ 0x01021420
void FUN_01021420(int* begin, int* end, int (*cmp)(int, int)) {
    if (begin == end) return;
    for (int* it = begin + 1; it != end; ++it) {
        int* v = (int*)*it;
        AddRef2(v);
        int* p = it;
        while (p != begin && cmp((int)(intptr_t)v, p[-1]) != 0) {
            RefAssign(*(int**)p, *(int**)&p[-1]);
            --p;
        }
        RefAssign(*(int**)p, v);
        Release(v);
    }
}

// ===========================================================================
// 0x01021500  (approximate heap sort variant)
// ===========================================================================
// @ 0x01021500
void FUN_01021500(int* begin, int* end, int (*cmp)(int, int)) {
    for (int* it = begin; it != end; ++it) {
        int* v = (int*)*it;
        AddRef2(v);
        int* p = it;
        while (p != begin && cmp((int)(intptr_t)v, p[-1]) != 0) {
            RefAssign(*(int**)p, *(int**)&p[-1]);
            --p;
        }
        RefAssign(*(int**)p, v);
        Release(v);
    }
}

// ===========================================================================
// 0x010215e0  (sift-up, approximate)
// ===========================================================================
// @ 0x010215e0
void FUN_010215e0(int* a, int idx, int count, int v, int (*cmp)(int, int)) {
    int i = idx;
    while (i > 0) {
        int parent = (i - 1) >> 1;
        if (cmp(a[parent], v) == 0) break;
        RefAssign(*(int**)&a[i], (int*)a[parent]);
        i = parent;
    }
    RefAssign(*(int**)&a[i], (int*)(intptr_t)v);
    Release((int*)v);
}

// ===========================================================================
// 0x010216a0  (swap, approximate)
// ===========================================================================
// @ 0x010216a0
void FUN_010216a0(int** a, int** b) {
    int* va = *a;
    AddRef2(va);
    int* pa = *a;
    if (*b != pa) {
        if (*b) AddRef2(*b);
        *a = *b;
        Release(pa);
    }
    int* pb = *b;
    if (va != pb) {
        if (va) AddRef2(va);
        *b = va;
        Release(pb);
    }
    Release(va);
}

// ===========================================================================
// 0x01021740  (approximate)
// ===========================================================================
// @ 0x01021740
void FUN_01021740(int* param) {
    void* s = DAT_016dda8c;
    if (param != *(int**)((char*)s + 4)) return;
    if (*(int*)((char*)s + 0x10) != 0) return;
    (void)param;
}

// ===========================================================================
// 0x01021960
// ===========================================================================
// @ 0x01021960
void FUN_01021960(int param) {
    int* s = (int*)DAT_016dda8c;
    if (s[4] == param) return;
    s[4] = param;
    if (param != 2) return;
    int* one = (int*)s[2];
    void* ufo = FUN_00ffbe50();
    if (one && ufo) {
        int* r = (int*)E(one)->FUN_00c8b360();
        (void)r;
    }
}

// ===========================================================================
// 0x010219b0  (approximate)
// ===========================================================================
// @ 0x010219b0
void FUN_010219b0(int param_1, int* param_2) {
    int ivar4 = (int)(intptr_t)param_2;
    if (param_2) {
        int r = (int)(intptr_t)E(param_2)->FUN_00b8de30();
        if (r != param_1) ivar4 = 0;
    }
    int* local = 0;
    FUN_00b3d2a0();
    int*& slot8 = *(int**)((char*)DAT_016dda8c + 8);
    int* old = slot8;
    int* newv = local;
    if (old != newv) {
        if (newv) ((void(__thiscall*)(void*))VTP(newv)[0])(newv);
        slot8 = newv;
        if (old) ((void(__thiscall*)(void*))VTP(old)[1])(old);
    }
    (void)ivar4;
}

// ===========================================================================
// 0x01021ab0 SP::cSPBackgroundSimManager::RemovePlayerColony  (approximate)
// ===========================================================================
// @ 0x01021ab0
void FUN_01021ab0(void* self, int param) {
    int* s = (int*)self;
    int* local = 0;
    FUN_00b3d2a0();
    int* begin = (int*)s[8];
    int* end = (int*)s[9];
    int* it = begin;
    while (it != end && (int*)*it != local) ++it;
    if (it == end) { Release(local); return; }
    int* v = (int*)*it;
    int* last = (int*)*(end - 1);
    if (last != v) { RefAssign(*(int**)it, last); }
    int*& cap = (int*&)s[9];
    cap = cap - 1;
    Release((int*)*cap);
    void* ach = FUN_00675250(0xfd534550, 1);
    ((void(__thiscall*)(void*, u32, int))VTP(ach)[0])(ach, 0xfd534550, 1);
    Release(local);
    (void)param;
}

// ===========================================================================
// 0x01021b70
// ===========================================================================
// @ 0x01021b70
int FUN_01021b70(int* p1, int** p2) {
    int* v = *p2;
    if (v) {
        *p2 = 0;
        void* q = (void*)((char*)v + 8);
        ((void(__thiscall*)(void*))VTP(q)[0xc / 4])(q);
    }
    ((int(__thiscall*)(void*, u32, void*, int))VTP(p1)[0x28 / 4])(p1, 0x301b5d9f, p2, 0);
    return 1;
}

// ===========================================================================
// 0x01021bb0  (sift-down, approximate)
// ===========================================================================
// @ 0x01021bb0
void FUN_01021bb0(int* a, int idx, int count, int start, int v, int (*cmp)(int, int)) {
    int i = start;
    while (2 * i + 2 < count) {
        int c = 2 * i + 2;
        if (cmp(a[c], a[c - 1]) != 0) c = 2 * i + 1;
        RefAssign(*(int**)&a[i], (int*)a[c]);
        i = c;
    }
    if (2 * i + 2 == count) {
        RefAssign(*(int**)&a[i], (int*)a[2 * i + 1]);
        i = 2 * i + 1;
    }
    FUN_010215e0(a, idx, i, v, cmp);
    (void)idx;
}

// ===========================================================================
// 0x01021ca0  (approximate)
// ===========================================================================
// @ 0x01021ca0
void FUN_01021ca0(int* a, int* p, int v) {
    int* first = (int*)*(p - 1);
    AddRef2(first);
    int* v0 = (int*)*a;
    int* old = (int*)*(p - 1);
    if (v0 != old) { RefAssign(*(int**)&p[-1], v0); }
    (void)v;
    FUN_01021bb0(a, 0, (int)(p - a) - 1, 0, v, 0);
    Release(first);
}

// ===========================================================================
// 0x01021d40
// ===========================================================================
// @ 0x01021d40
void FUN_01021d40() {
    void* p = FUN_00f473a0(0x34, "Simulator", 0, 0, 0, 0);
    float one = DAT_01485720;
    DAT_016dda8c = p;
    if (p) {
        *(u32*)((char*)p + 4) = 0;
        *(u32*)((char*)p + 8) = 0;
        *(u32*)((char*)p + 0xc) = 0;
        *(u32*)((char*)p + 0x10) = 0xffffffff;
        *(u32*)((char*)p + 0x18) = 0xffffffff;
        *(u32*)((char*)p + 0x1c) = 0;
        *(u32*)((char*)p + 0x20) = 0;
        *(u32*)((char*)p + 0x24) = 0;
        *(u32*)((char*)p + 0x28) = 0;
        *(float*)((char*)p + 0x14) = one;
    } else {
        *(float*)0x14 = one;
    }
}

// ===========================================================================
// 0x01021da0  (deleting destructor)
// ===========================================================================
// @ 0x01021da0
int FUN_01021da0(void* self, u8 flags) {
    char* s = (char*)self;
    E(s + 0x20)->FUN_00ad92d0();
    int* p1 = *(int**)(s + 0x1c);
    if (p1) ((void(__thiscall*)(void*))VTP(p1)[1])(p1);
    int v = *(int*)(s + 0xc);
    if (v) {
        void* q = (void*)(v + 8);
        ((void(__thiscall*)(void*))VTP(q)[0xc / 4])(q);
    }
    int* p2 = *(int**)(s + 8);
    if (p2) ((void(__thiscall*)(void*))VTP(p2)[1])(p2);
    int* p3 = *(int**)(s + 4);
    if (p3) ((void(__thiscall*)(void*))VTP(p3)[0xc0 / 4])(p3);
    if (flags & 1) FUN_00f47380(s);
    return (int)(intptr_t)s;
}

// ===========================================================================
// 0x01021e00  (heapify, approximate)
// ===========================================================================
// @ 0x01021e00
void FUN_01021e00(int a, int b, int v) {
    int n = (b - a) >> 2;
    if (n < 2) return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        int* p = *(int**)(a + i * 4);
        if (p) ((void(__thiscall*)(void*))VTP(p)[0xbc / 4])(p);
        FUN_01021bb0((int*)a, i, n, i, v, 0);
    } while (i != 0);
}
