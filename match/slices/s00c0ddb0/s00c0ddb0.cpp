// Slice s00c0ddb0 - cCommunity / cCreatureBase helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

typedef void* P;

void* __cdecl FUN_009ff6f0(void*, void*);   // 0x009ff6f0
void* __cdecl SP_GetCurrentGameMode();       // 0x00b5b800
void* __cdecl FUN_0067cb20();                // 0x0067cb20
void* __cdecl FUN_00b3d300();                // 0x00b3d300
void* __cdecl FUN_00b3d4c0(...);             // 0x00b3d4c0
void* __cdecl FUN_00b3d2c0(void*);           // 0x00b3d2c0
void* __cdecl FUN_00ac8960(void*);           // 0x00ac8960
void  __cdecl FUN_011e07ef(void*);           // 0x011e07ef

struct F_58     { void  __thiscall f(float*); };      // 0x00c886d0 cCommunity::func58h
struct F_64     { char  __thiscall f(); };            // 0x00c887e0 cCommunity::func64h
struct F_a02bd0 { int   __thiscall f(); };            // 0x00a02bd0
struct F_b3050  { char  __thiscall f(int, int); };    // 0x009b3050
struct F_cab60  { void* __thiscall f(int); };         // 0x009cab60
struct F_a02b40 { char  __thiscall f(int); };         // 0x00a02b40
struct F_a04940 { char  __thiscall f(int); };         // 0x00a04940
struct F_a02b20 { char  __thiscall f(int); };         // 0x00a02b20
struct F_a04990 { char  __thiscall f(int); };         // 0x00a04990
struct F_a049f0 { float __thiscall f(int); };         // 0x00a049f0
struct F_a048a0 { float* __thiscall f(); };           // 0x00a048a0
struct F_c04750 { void* __thiscall f(); };            // 0x00c04750
struct F_c04790 { int   __thiscall f(); };            // 0x00c04790
struct F_c232c0 { char  __thiscall f(); };            // 0x00c232c0
struct F_bfc5f0 { void* __thiscall f(); };            // 0x00bfc5f0
struct F_b1fdb0 { void* __thiscall GetAvatar(); };    // 0x00b1fdb0
struct F_ba3f90 { int   __thiscall f(void*, void*, void*); }; // 0x00ba3f90
struct F_d00a70 { int   __thiscall f(); };            // 0x00d00a70
struct F_d9b0   { void  __thiscall f(); };            // 0x00c0d9b0 (slice 117)
struct F_sw     { void __thiscall Ctor(int, int); unsigned long long __thiscall GetElapsedTime(); }; // 0x168db70

// Object reachable at CCM+0xb54: holds a creature-id lookup table at +0x17c and
// an animating-creature array (id/value records) at +0x8c (count at +0x14c).
struct CCMInner {
    uint32_t pad_00[0x17c / 4];  // +0x000
    void*    mpTable_17c;        // +0x17c  lookup object (find by id)
};

#define G32(a)  (*(uint32_t*)(a))
#define GF(a)   (*(float*)(a))

struct CCM {
    void  __thiscall ddb0(float*);
    char  __thiscall de30();
    void  __thiscall de60(int, int);
    bool  __thiscall dee0(int, int*, char);
    void* __thiscall dfb0(int);
    void* __thiscall dfd0(int);
    char  __thiscall e000(int, int);
    void* __thiscall e040();
    bool  __thiscall e070(int);
    bool  __thiscall e0c0(int);
    char  __thiscall e120(int);
    char  __thiscall e170(int);
    char  __thiscall e2c0(int);
    void* __thiscall e370();
    float __thiscall e3a0();
    char  __thiscall e3d0();
    char  __thiscall e420();
    float __thiscall e480();
    float __thiscall e4f0();
    void* __thiscall e580();
    void  __thiscall e5f0(float);
    void  __thiscall e640(int);
    int   __thiscall e660();
    int   __thiscall e680(int);
    int   __thiscall e6a0();
    char  __thiscall e8d0(int, int);

    uint32_t pad_a94[0xa94 / 4];                 // +0x000 .. +0xa93
    void*    mpGraspObj_a94;                     // +0xa94  grasped/sound object
    uint32_t pad_b54[(0xb54 - 0xa94 - 4) / 4];   // +0xa98 .. +0xb53
    CCMInner* mpInner_b54;                       // +0xb54  animation/creature table
};

// @ 0x00c0ddb0
void __thiscall CCM::ddb0(float* param_2) {
    ((F_58*)this)->f(param_2);
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        *(int*)(p + 0x10) = *(int*)((char*)param_2 + 4);
        GF(p + 0x14) = -param_2[0];
        *(int*)(p + 0x18) = *(int*)((char*)param_2 + 0xc);
        GF(p + 0x1c) = -param_2[2];
    }
}

// @ 0x00c0de30
char __thiscall CCM::de30() {
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        if (*(char*)((char*)this + 0xed0) != 0) {
            if (((F_a02bd0*)p)->f() != 0) return 1;
        }
        return 0;
    }
    return ((F_64*)this)->f();
}

// @ 0x00c0de60  SP::cSPCreatureCitizen::SetGraspedEffectOffsets
void __thiscall CCM::de60(int param_2, int param_3) {
    char* edi = (char*)param_2 + 0x150;
    if (!((F_b3050*)edi)->f(0x70737267, 0)) {
        if (!((F_b3050*)edi)->f(0x74756f6d, 0)) return;
    }
    float f1 = GF((char*)this + 0x124);
    GF((char*)param_3 + 0xc) = f1 * GF((char*)param_2 + 0x330);
    GF((char*)param_3 + 0x10) = GF((char*)param_2 + 0x334) * f1;
    GF((char*)param_3 + 0x14) = GF((char*)param_2 + 0x338) * f1;
}

// @ 0x00c0dee0
bool __thiscall CCM::dee0(int param_2, int* param_3, char param_4) {
    *param_3 = -1;
    char* base = *(char**)((char*)this + 0xb54);
    unsigned n = G32(base + 0x14c);
    unsigned i = 0;
    if (n == 0) return 0;
    int* p = (int*)(base + 0x8c);
    while (*p != param_2) {
        ++i;
        p += 3;
        if (n <= i) return 0;
    }
    *param_3 = *(int*)(base + (i * 3 + 0x24) * 4);
    if (param_4 != 0) {
        base = *(char**)((char*)this + 0xb54);
        --G32(base + 0x14c);
        if (i < G32(base + 0x14c)) {
            char* e = base + i * 0xc;
            do {
                *(int*)(e + 0x8c) = *(int*)(e + 0x98);
                *(int*)(e + 0x90) = *(int*)(e + 0x9c);
                *(int*)(e + 0x94) = *(int*)(e + 0xa0);
                ++i;
                e += 0xc;
                base = *(char**)((char*)this + 0xb54);
            } while (i < G32(base + 0x14c));
        }
    }
    return 1;
}

// @ 0x00c0dfb0
void* __thiscall CCM::dfb0(int param) {
    CCMInner* p = mpInner_b54;
    if (p != 0) return ((F_cab60*)p->mpTable_17c)->f(param);
    return 0;
}

// @ 0x00c0dfd0
void* __thiscall CCM::dfd0(int param) {
    CCMInner* p = mpInner_b54;
    if (p != 0) {
        char* r = (char*)((F_cab60*)p->mpTable_17c)->f(param);
        if (r != 0) return *(void**)(r + 0x8c);
    }
    return 0;
}

// @ 0x00c0e000
char __thiscall CCM::e000(int param_2, int param_3) {
    CCMInner* p = mpInner_b54;
    if (p != 0) {
        char* r = (char*)((F_cab60*)p->mpTable_17c)->f(param_2);
        if (r != 0 && param_3 != -1) {
            *(int*)(r + 8) = param_3;
            return 1;
        }
    }
    return 0;
}

// @ 0x00c0e040  SP::cSPCreatureBase::GetCurrentAnimationGUID
void* __thiscall CCM::e040() {
    char* c = *(char**)((char*)this + 0xb54);
    uint32_t local_4 = 0;
    if (c == 0) return (void*)local_4;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    return (void*)local_4;
}

// @ 0x00c0e070
bool __thiscall CCM::e070(int param_2) {
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0 && *(int*)(c + 0x184) != 0) {
        char* r = (char*)FUN_009ff6f0(*(void**)(c + 0x184), (void*)param_2);
        if (r != 0) return *(int*)(r + 0xc0) != 0;
        return 0;
    }
    return 1;
}

// @ 0x00c0e0c0
bool __thiscall CCM::e0c0(int param_2) {
    CCMInner* c = mpInner_b54;
    if (c == 0) return 0;
    uint32_t local_4 = 0;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    if ((int)local_4 == param_2) return 1;
    if (!((F_a02b40*)c)->f(param_2)) return 0;
    return 1;
}

// @ 0x00c0e120
char __thiscall CCM::e120(int param_2) {
    char* p = *(char**)(*(char**)((char*)this + 0xb54) + 0x184);
    int* pu = (int*)(p + 0xf4c);
    for (int i = 0; i < 0x10; ++i) {
        int v = *pu;
        if (v != -1 && *(int*)(v * 0xf0 + (int)p + 0xe0) == param_2) return 1;
        ++pu;
    }
    return 0;
}

// @ 0x00c0e170
char __thiscall CCM::e170(int param_2) {
    char* pi = *(char**)((char*)this + 0xb54);
    if (pi == 0) return 1;
    if (param_2 == 0) {
        char* r = (char*)FUN_009ff6f0(*(void**)(pi + 0x184), *(void**)((char*)this + 0xe88));
        if (r != 0) {
            if (*(int*)(r + 0xc0) == 0) return 0;
            if (((F_a04940*)pi)->f(*(int*)((char*)this + 0xe88))) return 1;
            if (((F_a02b20*)pi)->f(*(int*)((char*)this + 0xe88))) return 1;
            if (!((F_a04990*)pi)->f(*(int*)((char*)this + 0xe88))) return 0;
            if (((F_a049f0*)pi)->f(*(int*)((char*)this + 0xe88)) < 1.0f) return 0;
            return 1;
        }
    } else {
        uint32_t local = 0;
        void* vt = *(void**)pi;
        (*(void(__thiscall**)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            pi, &local, 0, 0, 0);
        if (local != 0) {
            if (param_2 != (int)local) {
                return ((F_a02b40*)pi)->f(param_2) == 0;
            }
            if (((F_a04940*)pi)->f(0)) return 1;
            if (((F_a02b20*)pi)->f(0)) return 1;
            if (((F_a04990*)pi)->f(0)) {
                if (((F_a049f0*)pi)->f(0) >= 1.0f) return 1;
            }
            return 0;
        }
    }
    return 1;
}

// @ 0x00c0e2c0
char __thiscall CCM::e2c0(int param_2) {
    char* c = *(char**)((char*)this + 0xb54);
    if (c == 0 || *(int*)(c + 0x184) == 0) return 1;
    char* r = (char*)FUN_009ff6f0(*(void**)(c + 0x184), (void*)param_2);
    if (r == 0) return 1;
    if (*(int*)(r + 0xc0) == 0) return 0;
    if (((F_a04940*)c)->f(param_2)) return 1;
    if (((F_a02b20*)c)->f(param_2)) return 1;
    if (((F_a04990*)c)->f(param_2)) {
        if (((F_a049f0*)c)->f(*(int*)((char*)this + 0xe88)) >= 1.0f) return 1;
    }
    return 0;
}

// ======================================================================
// @ 0x00c0e370
void* __thiscall CCM::e370() {
    char* c = *(char**)((char*)this + 0xb54);
    if (c == 0) return 0;
    uint32_t local_4 = 0;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, int, int, void*, int))(*(void**)((char*)vt + 0x58)))(
        c, 0, 0, &local_4, 0);
    return (void*)local_4;
}

// ======================================================================
// @ 0x00c0e3a0
float __thiscall CCM::e3a0() {
    char* c = *(char**)((char*)this + 0xb54);
    float local_4 = 0.0f;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, void*, int, int))(*(void**)((char*)vt + 0x58)))(
            c, 0, &local_4, 0, 0);
    }
    return local_4;
}

// ======================================================================
// @ 0x00c0e3d0
char __thiscall CCM::e3d0() {
    char* c = *(char**)((char*)this + 0xa94);
    if (c != 0) {
        uint32_t local_4 = 0;
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
        if (local_4 != 0) {
            void* lm = FUN_0067cb20();
            char* r = (char*)((void*(__thiscall*)(void*, uint32_t))(*(void**)((char*)*(void**)lm + 0x40)))(
                lm, local_4);
            if (r != 0) return *(char*)(r + 0x1d);
        }
    }
    return 1;
}

// ======================================================================
// @ 0x00c0e420
char __thiscall CCM::e420() {
    void* lm = FUN_0067cb20();
    char* c = *(char**)((char*)this + 0xb54);
    uint32_t local_4 = 0;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
    }
    char* r = (char*)((void*(__thiscall*)(void*, uint32_t))(*(void**)((char*)*(void**)lm + 0x40)))(
        lm, local_4);
    if (r != 0 && *(char*)(r + 0x1c) != 0) return 1;
    return 0;
}

// ======================================================================
// @ 0x00c0e480  SP::cSPCreatureBase::GetTime
float __thiscall CCM::e480() {
    if ((G32(0x168db88) & 1) == 0) {
        G32(0x168db88) |= 1;
        ((F_sw*)0x168db70)->Ctor(4, 1);
        FUN_011e07ef((void*)0x13c3580);
    }
    unsigned long long u = ((F_sw*)0x168db70)->GetElapsedTime();
    double d = (double)(long long)u;
    return (float)(d * *(double*)0x13f6560);
}

// ======================================================================
// @ 0x00c0e4f0
float __thiscall CCM::e4f0() {
    if (SP_GetCurrentGameMode() == (void*)0x1654c10
        && *(int*)(G32(0x16c7aa4) + 0xcc) == 2
        && this != 0) {
        int r = (*(int(__thiscall**)(void*, int))((*(void***)this)[0xc / 4]))(this, 0xd0036e08);
        if (r != 0 && ((G32((char*)this + 0xb58) >> 9) & 1) == 0) {
            int* q = (int*)((F_c04750*)(void*)r)->f();
            if (q != 0) return GF((char*)q + 0x484);
        }
    }
    char* e = *(char**)((char*)this + 0xe84);
    if (e != 0) {
        float v = GF(e + 0x34c);
        if (v >= 0.0f) return v;
    }
    return GF(0x150c8bc);
}

// ======================================================================
// @ 0x00c0e580
void* __thiscall CCM::e580() {
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0) {
        float* p = ((F_a048a0*)c)->f();
        if (p[0] != GF(0x168d910) || p[1] != GF(0x168d914) || p[2] != GF(0x168d918)) {
            return ((F_a048a0*)(*(void**)((char*)this + 0xb54)))->f();
        }
    }
    void* self = (char*)this + 0xc0;
    return (*(void*(__thiscall**)(void*))((*(void***)self)[0x2c / 4]))(self);
}

// ======================================================================
// @ 0x00c0e5f0
void __thiscall CCM::e5f0(float param_2) {
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        GF(p + 0x3c) = param_2;
        SP_GetCurrentGameMode();
    }
    if (param_2 != GF((char*)this + 0x64)) {
        GF((char*)this + 0x64) = param_2;
        GF((char*)this + 0x7c) = param_2;
        ((F_d9b0*)((char*)this - 0xc0))->f();
    }
}

// ======================================================================
// @ 0x00c0e640
void __thiscall CCM::e640(int param_2) {
    char* p = *(char**)((char*)this + 0xb54);
    if (p != 0) *(int*)(p + 0x170) = param_2;
}

// ======================================================================
// @ 0x00c0e660
int __thiscall CCM::e660() {
    char* b = *(char**)((char*)this + 0xb20);
    return (*(int*)(b + 0x6d8) - *(int*)(b + 0x6d4)) >> 2;
}

// ======================================================================
// @ 0x00c0e680
int __thiscall CCM::e680(int param_2) {
    if (param_2 == -1) return 0;
    char* b = *(char**)((char*)this + 0xb20);
    return *(int*)(*(int*)(b + 0x6d4) + param_2 * 4);
}

// ======================================================================
// @ 0x00c0e6a0  SP::cSPCreatureBase::GetSocialGoal
int __thiscall CCM::e6a0() {
    int u = 0;
    if (this == 0) return 0;
    char* pi = (char*)(*(void*(__thiscall**)(void*, int))((*(void***)this)[0xc / 4]))(this, 0x4f176642);
    if (pi == 0) return 0;
    if (!((F_c232c0*)pi)->f()) return 0;
    void* nm = FUN_00b3d300();
    void* gd = ((F_bfc5f0*)nm)->f();
    void* a = (*(void*(__thiscall**)(void*, int))(*(void**)((char*)gd + 0x4c)))(gd, 1);
    void* b = (*(void*(__thiscall**)(void*, void*))(*(void**)((char*)pi + 0x4c)))(pi, a);
    void* rm = FUN_00b3d2c0(b);
    int iVar8 = ((F_d00a70*)rm)->f();
    char c1 = (*(char(__thiscall**)(void*))((*(void***)this)[0xd4 / 4]))(this);
    if (iVar8 == 1) { if (c1 == 0) return 3; }
    else if (iVar8 == 2) { if (c1 == 0) return 2; }
    else if (iVar8 == 3 && c1 == 0) return 1;
    return u;
}

// ======================================================================
// @ 0x00c0e8d0
char __thiscall CCM::e8d0(int param_2, int param_3) {
    char* p2 = (char*)param_2;
    if ((G32((char*)this + 0xb20) == G32(p2 + 0xb20) && SP_GetCurrentGameMode() != (void*)0x1654c10)
        || (((G32((char*)this + 0xb58) >> 8) & 1) != 0
            && (((G32(p2 + 0xb58) >> 8) & 1) != 0 || ((G32(p2 + 0xb58) >> 9) & 1) != 0)))
        return 1;
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        if (((G32((char*)this + 0xb58) >> 9) & 1) != 0 && ((G32(p2 + 0xb58) >> 8) & 1) != 0)
            return 1;
    } else {
        char c1 = (*(char(__thiscall**)(void*, int))((*(void***)this)[0xd0 / 4]))(this, param_3);
        if (c1 != 0 && ((G32(p2 + 0xb58) >> 8) & 1) != 0) return 1;
    }
    char* ebx = (char*)FUN_00b3d4c0();
    if (ebx == 0) return 0;
    if (((G32((char*)this + 0xb58) >> 8) & 1) != 0) {
        if (SP_GetCurrentGameMode() == (void*)0x1654c10
            && ((G32(p2 + 0xb58) >> 9) & 1) == 0
            && ((G32((char*)this + 0xb58) >> 9) & 1) == 0) {
            char* s = (char*)FUN_00ac8960((void*)param_2);
            char* d = (char*)FUN_00ac8960((void*)this);
            if (s == 0 || d == 0) return 0;
            int x = ((F_c04790*)s)->f();
            int y = ((F_c04790*)d)->f();
            if (x != y || y == 1) return 0;
            return 1;
        }
        switch (param_3) {
        case 3:
            if (((F_ba3f90*)ebx)->f((void*)((char*)this + 0xb28), (void*)this, (void*)param_2) == 3) return 1;
            /* fallthrough */
        case 4:
            if (((F_ba3f90*)ebx)->f((void*)((char*)this + 0xb28), (void*)this, (void*)param_2) == 4) return 1;
            /* fallthrough */
        case 6:
            return ((F_ba3f90*)ebx)->f((void*)((char*)this + 0xb28), (void*)this, (void*)param_2) == 6;
        default:
            return 0;
        }
    }
    switch (param_3) {
    case 3:
        if (((F_ba3f90*)ebx)->f((void*)(p2 + 0xb28), (void*)this, (void*)param_2) == 3) return 1;
        /* fallthrough */
    case 4:
        if (((F_ba3f90*)ebx)->f((void*)(p2 + 0xb28), (void*)this, (void*)param_2) == 4) return 1;
        /* fallthrough */
    case 6:
        return ((F_ba3f90*)ebx)->f((void*)(p2 + 0xb28), (void*)this, (void*)param_2) == 6;
    default:
        return 0;
    }
}
