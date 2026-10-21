// Slice s00dc0040: the SP::UFO_FOLLOW_RANDOM_RAIDER command / AI behavior family.
// Twelve free functions over one object (fields +0x34 / +0x508 vtable-bearing
// subobjects, +0x624 byte flag, +0x68c refcounted target, +0x690/+0x691 bytes,
// +0x694 vec, +0x6ac float, +0x6b0 int, +0x6b4/+0x6b8 floats, +0x6c8 pointer,
// +0x710 pointer, +0x714 int, +0x718 subobject).  Target swapping is a raw
// manual AddRef(slot 0)/Release(slot 4) pair over a RefCountVTemplate.
// Almost every callee here is a __thiscall member (this in ecx), so they are
// declared as members of the object they belong to; relocations are masked.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <intrin.h>

typedef unsigned char byte;
struct Vec3 { float x, y, z; };

extern "C" float __cdecl sqrtf(float);

// ------------------------------------------------------------------ globals
extern float g_one;      // 0x01485720  (1.0f)
extern float g_x444;     // 0x0169f444
extern float g_xF448;    // 0x0169f448
extern float g_xF44c;    // 0x0169f44c

extern float g_9d578;    // 0x0159d578
extern float g_9d5e8;    // 0x0159d5e8
extern float g_9d5f8;    // 0x0159d5f8
extern float g_9d604;    // 0x0159d604
extern float g_9d608;    // 0x0159d608
extern float g_9d60c;    // 0x0159d60c
extern float g_9d610;    // 0x0159d610
extern float g_9d614;    // 0x0159d614
extern float g_9d628;    // 0x0159d628
extern float g_9d630;    // 0x0159d630
extern float g_9d634;    // 0x0159d634
extern float g_9d638;    // 0x0159d638
extern float g_9d63c;    // 0x0159d63c

extern float g_473c70;   // 0x01473c70
extern float g_47c308;   // 0x0147c308
extern float g_3ec4d0;   // 0x013ec4d0
extern float g_3eb1bc;   // 0x013eb1bc
extern float g_3eecd8;   // 0x013eecd8

extern float g_fA18;     // 0x0169fa18
extern float g_fA1c;     // 0x0169fa1c
extern float g_fA20;     // 0x0169fa20
extern float g_fA24;     // 0x0169fa24
extern float g_fA28;     // 0x0169fa28
extern float g_fA2c;     // 0x0169fa2c

extern struct RRngObj g_rng;   // 0x01601760 (the RNG object itself)

// ------------------------------------------------------------------ object
struct Sub {                             // view on the outer object (this in ecx)
    void  Be70(void* p);                 // 0x00c3be70
    void  Daa0(float f);                 // 0x00c3daa0
    char* B00();                         // 0x00c38b00  -> returns an object*
    void  B10();                         // 0x00c38b10
    char* B80();                         // 0x00c38b80  -> returns an object*
    char* B7720();                       // 0x00c37720  -> returns an object*
    void  Bf0(int, int, float, int);     // 0x00bc97f0  (this = *(+0x6c8) + 8)
    bool  C8990(int a);                  // 0x00c38990
    float C7120();                       // 0x00c37120  (this = the target object)
};
struct Planet { float* MakeRandomWorldPosition(); };   // 0x00b81780 (thiscall, 0 args)
struct Sub2 { float F10(); };                          // 0x0104be30 (thiscall, 0 args)

struct RRngObj {                         // 0x01601760 (RNG instance, direct object)
    unsigned RandomUint32Uniform(unsigned n);  // 0x00a68fb0
    double   RandomDoubleUniform();            // 0x009360d0
};
struct Sim { void* GetPlayerInventory(); };    // 0x00a1ad60 (this = UFO simulator)

extern "C" void* SPGetUFOSimulator();                        // 0x00ffbe50
extern "C" void* GetBestUFOTarget(void*, unsigned, int);     // 0x0102bc90
extern "C" bool  CommCanTarget(void*, void*, unsigned);      // 0x0102aa50
extern "C" void* PlanetModel(void*, void*, float, float);    // 0x00b3d350
extern "C" float RandomSigned(float);                        // 0x00572a60

// ===========================================================================
// @ 0x00dc0040
// ===========================================================================
void FUN_00dc0040(char* self) {
    byte z = 0;
    float one = g_one;
    *(float*)(self + 0x6b4) = one;
    *(float*)(self + 0x6b8) = one;
    *(byte*)(self + 0x690) = z;
    *(byte*)(self + 0x691) = z;
    _ReadWriteBarrier();
    void* p = *(void**)(self + 0x68c);
    if (p != 0) {
        *(void**)(self + 0x68c) = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    ((Sub*)self)->Be70(self + 0x718);
}

// ===========================================================================
// @ 0x00dc00a0
// ===========================================================================
Vec3* FUN_00dc00a0(Vec3* out, unsigned flags, void* arg) {
    out->x = g_x444;
    out->y = g_xF448;
    out->z = g_xF44c;
    char* inv = (char*)((Sim*)SPGetUFOSimulator())->GetPlayerInventory();
    unsigned b = (flags >> 0xc) & 1;
    void* best = GetBestUFOTarget(inv, b, 0);
    if (best != 0) {
        char* v8 = (char*)(*(void* (__thiscall**)(void*))((char*)*(void**)best + 8))(best);
        float* ph = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)(inv + 0x34) + 0x2c))(inv + 0x34);
        float* pf = (float*)(*(void* (__thiscall**)(void*))((char*)*(void**)v8 + 0x2c))(v8);
        float dx = pf[0] - ph[0];
        float dy = pf[1] - ph[1];
        float dz = pf[2] - ph[2];
        if (sqrtf(dx*dx + dy*dy + dz*dz) < g_9d578) return out;
    }
    void* q = *(void**)(inv + 0x710);
    if (q != 0 && CommCanTarget(q, arg, b)) return out;
    if (!b) {
        int zz = 0;
        out->x = *(float*)&zz;
        out->y = g_9d5e8;
        out->z = *(float*)&zz;
    }
    return out;
}

// ===========================================================================
// @ 0x00dc01c0
// ===========================================================================
void FUN_00dc01c0(char* self) {
    float one = g_one;
    *(float*)(self + 0x6b4) = one;
    *(float*)(self + 0x6b8) = one;
    *(byte*)(self + 0x690) = 0;
    *(byte*)(self + 0x691) = 0;
    _ReadWriteBarrier();
    void* p = *(void**)(self + 0x68c);
    if (p != 0) {
        *(void**)(self + 0x68c) = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    ((Sub*)self)->Be70(self + 0x718);
    (*(void (__thiscall**)(char*, int))((char*)*(void**)(self + 0x508) + 0x50))(self + 0x508, 0);
}

// ===========================================================================
// @ 0x00dc0230
// ===========================================================================
bool FUN_00dc0230(char* self) {
    if (*(char*)(self + 0x74c) != 0 && *(char*)(*(int*)(self + 0x68c) + 0x74c) != 0) {
        char* a = self + 0x34;
        char* b = (char*)*(int*)(self + 0x68c) + 0x34;
        float* pa = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        float ax = pa[0], ay = pa[1], az = pa[2];
        float* pb = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)b + 0x2c))(b);
        float x1 = pb[0] - ax * 2.0f;
        float y1 = pb[1] - ay * 2.0f;
        float z1 = pb[2] - az * 2.0f;
        float* pa2 = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        Vec3 v;
        v.x = pa2[0] + x1;
        v.y = pa2[1] + y1;
        v.z = pa2[2] + z1;
        ((Sub*)self)->Be70(&v);
        ((Sub*)self)->Daa0(((Sub*)*(void**)(self + 0x68c))->C7120());
        *(byte*)(self + 0x624) = 1;
    }
    if (*(char*)(*(int*)(self + 0x68c) + 0x74c) == 0) {
        char* a = self + 0x34;
        float loc[3];
        float* pv = (float*)(*(void* (__thiscall**)(char*, float*))((char*)*(void**)a + 0x5c))(a, loc);
        float x1 = pv[0] * 100.0f;
        float y1 = pv[1] * 100.0f;
        float z1 = pv[2] * 100.0f;
        float* pa = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        Vec3 v;
        v.x = pa[0] + x1;
        v.y = pa[1] + y1;
        v.z = pa[2] + z1;
        ((Sub*)self)->Be70(&v);
        ((Sub*)self)->Daa0(((Sub*)*(void**)(self + 0x68c))->C7120());
        *(byte*)(self + 0x624) = 1;
    }
    return true;
}

// ===========================================================================
// @ 0x00dc0410
// ===========================================================================
bool FUN_00dc0410(char* self) {
    char* inv = (char*)((Sim*)SPGetUFOSimulator())->GetPlayerInventory();
    if (((Sub*)inv)->C8990(1)) return false;
    if (*(void**)(self + 0x68c) == inv) return false;
    void* old = *(void**)(self + 0x68c);
    if (inv != old) {
        if (inv != 0) (*(void (__thiscall**)(void*))(*(void**)inv))(inv);
        *(void**)(self + 0x68c) = inv;
        if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    *(int*)(self + 0x6b0) = (int)g_rng.RandomUint32Uniform(2);
    double f = g_rng.RandomDoubleUniform() * 50.0;
    if (f > 50.0) f = 50.0;
    else if (f < 0.0) f = 0.0;
    float v = (float)f - 25.0f;
    *(float*)(self + 0x694) = g_fA24 * v + g_fA18 * g_47c308;
    *(float*)(self + 0x698) = g_fA28 * v + g_fA1c * g_47c308;
    *(float*)(self + 0x69c) = g_fA2c * v + g_fA20 * g_47c308;
    *(float*)(self + 0x6ac) = RandomSigned(g_473c70);
    return true;
}

// ===========================================================================
// @ 0x00dc0550
// ===========================================================================
bool FUN_00dc0550(char* self) {
    void* best = GetBestUFOTarget(self, 0, 1);
    if (best == 0) return false;
    void* info = (*(void* (__thiscall**)(void*, unsigned))((char*)*(void**)best + 0x5c))(best, 0xb033b403);
    if (info == 0) return false;
    if (*(void**)(self + 0x68c) == info) return false;
    void* old = *(void**)(self + 0x68c);
    if (info != old) {
        (*(void (__thiscall**)(void*))(*(void**)info))(info);
        *(void**)(self + 0x68c) = info;
        if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    *(int*)(self + 0x6b0) = (int)g_rng.RandomUint32Uniform(2);
    double f = g_rng.RandomDoubleUniform() * 50.0;
    if (f > 50.0) f = 50.0;
    else if (f < 0.0) f = 0.0;
    float v = (float)f - 25.0f;
    *(float*)(self + 0x694) = g_fA24 * v + g_fA18 * g_47c308;
    *(float*)(self + 0x698) = g_fA28 * v + g_fA1c * g_47c308;
    *(float*)(self + 0x69c) = g_fA2c * v + g_fA20 * g_47c308;
    *(float*)(self + 0x6ac) = RandomSigned(g_473c70);
    return true;
}

// ===========================================================================
// @ 0x00dc06a0
// ===========================================================================
bool FUN_00dc06a0(char* self) {
    char* o = ((Sub*)self)->B00();
    if (o == 0) return false;
    void* info = (*(void* (__thiscall**)(char*, unsigned))((char*)*(void**)o + 0xc))(o, 0xb033b403);
    if (info == 0) return false;
    if ((*(char (__thiscall**)(void*))((char*)*(void**)info + 0x2c))(info) != 0) {
        ((Sub*)self)->B10();
        return false;
    }
    if ((*(char (__thiscall**)(void*))((char*)*(void**)info + 0x2c))(info) != 0) return false;
    void* old = *(void**)(self + 0x68c);
    if (info != old) {
        (*(void (__thiscall**)(void*))(*(void**)info))(info);
        *(void**)(self + 0x68c) = info;
        if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    return true;
}

// ===========================================================================
// @ 0x00dc0720
// ===========================================================================
bool FUN_00dc0720(char* self) {
    void* p = *(void**)(self + 0x68c);
    if (p != 0) {
        *(void**)(self + 0x68c) = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    return false;
}

// ===========================================================================
// @ 0x00dc0750
// ===========================================================================
bool FUN_00dc0750(char* self, void* a2, void* a3, void* a4, void* a5, void* a6, void* src) {
    if (src != 0) {
        char* q = *(char**)((char*)src + 4);
        void* info;
        if (q != 0) info = (*(void* (__thiscall**)(char*, unsigned))((char*)*(void**)q + 0x5c))(q, 0xb033b403);
        else info = 0;
        void* old = *(void**)(self + 0x68c);
        if (info != old) {
            if (info != 0) (*(void (__thiscall**)(void*))(*(void**)info))(info);
            *(void**)(self + 0x68c) = info;
            if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        ((Sub*)((char*)*(void**)(self + 0x6c8) + 8))->Bf0(4, 0, g_9d5f8, 0);
    }
    return true;
}

// ===========================================================================
// @ 0x00dc07d0
// ===========================================================================
bool FUN_00dc07d0(char* self, void* a2, void* a3, void* a4, void* a5, Vec3* out) {
    out->x = g_9d604;
    out->y = g_9d608;
    char* a = self + 0x34;
    float* pa = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
    Vec3 neg;
    neg.x = pa[0] * g_3eb1bc;
    neg.y = pa[1] * g_3eb1bc;
    neg.z = pa[2] * g_3eb1bc;
    Vec3 loc;
    char* m = (char*)PlanetModel(&loc, &neg, g_3eecd8, g_3ec4d0);
    float* r = ((Planet*)m)->MakeRandomWorldPosition();
    loc = *(Vec3*)r;
    ((Sub*)self)->Be70(&loc);
    ((Sub*)self)->Daa0(g_9d614);
    if (*(int*)(self + 0x714) == 5) {
        *(float*)(self + 0x6b4) = g_9d630;
        *(float*)(self + 0x6b8) = g_9d634;
    }
    *(float*)(self + 0x6b4) = g_9d60c;
    bool one = true;
    *(float*)(self + 0x6b8) = g_9d610;
    *(bool*)(self + 0x624) = one;
    return one;
}

// ===========================================================================
// @ 0x00dc08f0
// ===========================================================================
bool FUN_00dc08f0(char* self, void* a2, void* a3, void* a4, void* a5, Vec3* out) {
    char* o = ((Sub*)self)->B80();
    if (o != 0) {
        char* info = (char*)(*(void* (__thiscall**)(char*, void*))((char*)*(void**)o + 0xc))(o, (void*)0x1186577);
        if (info != 0) {
            float* p = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)info + 0x2c))(info);
            *out = *(Vec3*)p;
            void* r = (*(void* (__thiscall**)(char*))((char*)*(void**)info + 0x2c))(info);
            ((Sub*)self)->Be70(r);
        }
    }
    ((Sub*)self)->Daa0(g_9d628);
    *(float*)(self + 0x6b4) = g_9d638;
    float vb = g_9d63c;
    bool one = true;
    *(bool*)(self + 0x624) = one;
    *(float*)(self + 0x6b8) = vb;
    return one;
}

// ===========================================================================
// @ 0x00dc0980
// ===========================================================================
bool FUN_00dc0980(char* self, void* a2, void* a3, void* a4, void* a5, void* a6, Vec3* pos) {
    char* o = ((Sub*)self)->B80();
    if (o == 0) return false;
    char* infoF = (char*)(*(void* (__thiscall**)(char*, unsigned))((char*)*(void**)o + 0xc))(o, 0x11c0ba3);
    char* infoH = (char*)(*(void* (__thiscall**)(char*, void*))((char*)*(void**)o + 0xc))(o, (void*)0x1186577);
    char* infoX = (char*)(*(void* (__thiscall**)(char*, void*))((char*)*(void**)o + 0xc))(o, (void*)0x13f94d4);
    if ((*(char (__thiscall**)(char*))((char*)*(void**)o + 0x2c))(o) != 0) return false;
    if (infoF == 0) return false;
    if (infoH == 0) return false;
    if (infoX == 0) return false;
    if (*(char*)(self + 0x74c) == 0) return true;
    unsigned t = (*(unsigned (__thiscall**)(char*))((char*)*(void**)infoF + 0x24))(infoF);
    if (t != 0x114242e6) {
        float* ph = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)infoH + 0x2c))(infoH);
        float dx = ph[0] - pos->x;
        float dy = ph[1] - pos->y;
        float dz = ph[2] - pos->z;
        if (sqrtf(dx*dx + dy*dy + dz*dz) >= g_473c70) {
            pos->x = ph[0];
            pos->y = ph[1];
            pos->z = ph[2];
            void* r = (*(void* (__thiscall**)(char*))((char*)*(void**)infoH + 0x2c))(infoH);
            ((Sub*)self)->Be70(r);
            return true;
        }
    }
    char* u = ((Sub*)self)->B7720();
    if (u != 0) {
        float f = ((Sub2*)u)->F10();
        float* ps = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)(self + 0x34) + 0x2c))(self + 0x34);
        float* pm = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)infoX + 0x2c))(infoX);
        float dx = pm[0] - ps[0];
        float dy = pm[1] - ps[1];
        float dz = pm[2] - ps[2];
        if (sqrtf(dx*dx + dy*dy + dz*dz) < f) {
            (*(void (__thiscall**)(char*, char*))((char*)*(void**)(self + 0x508) + 0x50))(self + 0x508, infoX);
        }
    }
    return true;
}
