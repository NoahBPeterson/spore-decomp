// Slice s0053f960: continuation of the Swarm "SPSkinPaintParticle" paint-variable
// evaluator (hash maps, entry tables, modifier flush).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <xmmintrin.h>

typedef unsigned int size_t;

struct cSPVector3 { float x, y, z; cSPVector3(){} };

// ---------------------------------------------------------------- externals
void* operator new[](size_t, const char*, int, unsigned, const char*, int);
void  operator_delete__(void*);

uint32_t FUN_0050ea00(int key);                       // @ 0x50ea00 hash
uint32_t FUN_0050e850(int a, int b);                  // @ 0x50e850 hash
char     FUN_00509850(int a, int b);                  // @ 0x509850 equal
void*    FUN_0042dee0(void* alloc, int size, int align, int flags); // @ 0x42dee0
void     DefaultRefCounted_Release(void* p);          // DefaultRefCounted::Release
void     FUN_0053e580();                              // @ 0x53e580
void     FUN_0053eca0();                              // @ 0x53eca0
char     FUN_0053e690();                              // @ 0x53e690
char     SP_GetResourceTypeFromModelType();           // @ SP::GetResourceTypeFromModelType
void     FUN_00508400();                              // @ 0x508400
void     FUN_004098a0(cSPVector3* dst, const cSPVector3* src); // @ 0x4098a0
void*    FUN_0041dc10(void* out, void* a, void* b);   // @ 0x41dc10
void*    FUN_0041de40(void* out, void* scale, void* v);// @ 0x41de40
void     FUN_0041ddb0(void* dst, void* src);          // @ 0x41ddb0
void     FUN_004739d0(void* v);                       // @ 0x4739d0
void     FUN_005156b0();                              // @ 0x5156b0
void     FUN_004cef00(void* a, int b, void* c);       // @ 0x4cef00
void     FUN_00541030(void* a, int b, void* c);       // @ 0x541030
void     FUN_0050e690(void* a, void* b);              // @ 0x50e690
void     FUN_0053f300(void* self, int key, int* out); // @ 0x53f300
void     Vector3_Add(void* dst, void* src);           // @ 0x41ddb0 reuse

extern uint32_t gMxcsrBits;        // @ 0x15db058

// default-refcounted object header used at context +0x90 / +0x94
struct RefCounted { void* vptr; int mRef; };

// ---------------------------------------------------------------- object
// `this` is the paint-variable evaluator when the offset pattern is used; for
// the container helpers below `this` is the container itself (begin/end/cap at
// +0/+4/+8).
struct Obj {
    char mPad[0x200];

    int          FUN_0053f960(int* out, int a, int b, int c, int d);
    unsigned int FUN_0053fe30(int entry, unsigned char mask);
    int          FUN_005400a0(int param_2, int param_3, float param_4);
    void         FUN_00540210();
    void         FUN_005402c0(int* value);
    unsigned int FUN_00540340(int key);
    Obj*         FUN_00540470(int unused);
    void         FUN_00540560(int* pos, int* value);
    void         FUN_005407a0(unsigned int n);
    unsigned int FUN_00540820(int key);
};

// ---------------------------------------------------------------- extern data
// static tables used by the modifier flush
extern unsigned char gPaintVarModNormal[];   // @ 0x15e2d08
extern unsigned short gFe30TableA[];         // @ 0x15e2658
extern unsigned char  gFe30TableB[];         // @ 0x15e2858
extern unsigned char  gFe30TableC[];         // @ 0x15e28d0
extern unsigned char  gFe30TableD[];         // @ 0x15e2928
extern unsigned char  gFe30TableE[];         // @ 0x15e25f8
extern unsigned char  gFe30TableF[];         // @ 0x15e2870

// @ 0x005400a0
int Obj::FUN_005400a0(int param_2, int param_3, float param_4)
{
    char* self = (char*)this;
    *(int*)(self + 0x1c) = 0;

    int* p = (int*)(self + 0x90);
    if (param_2 != *p) {
        int old = *p;
        if (param_2 != 0) *(int*)(param_2 + 4) = *(int*)(param_2 + 4) + 1;
        *p = param_2;
        if (old != 0) DefaultRefCounted_Release((void*)old);
    }
    p = (int*)(self + 0x94);
    if (param_3 != *p) {
        int old = *p;
        if (param_3 != 0) *(int*)(param_3 + 4) = *(int*)(param_3 + 4) + 1;
        *p = param_3;
        if (old != 0) DefaultRefCounted_Release((void*)old);
    }
    *(float*)(self + 0x14) = param_4;
    *(float*)(self + 0x18) = 1.0f / param_4;
    _mm_setcsr((_mm_getcsr() & 0xffffffc0) | 0x8000 | gMxcsrBits);
    FUN_0053e580();
    FUN_0053eca0();
    if (FUN_0053e690() == 0) {
        FUN_00540210();
        return 0;
    }
    if (SP_GetResourceTypeFromModelType() == 0)
        FUN_00508400();
    return 1;
}

// @ 0x00540210
void Obj::FUN_00540210()
{
    char* self = (char*)this;
    int* p = (int*)(self + 0x94);
    if (*p != 0) {
        int old = *p;
        *p = 0;
        if (old != 0) DefaultRefCounted_Release((void*)old);
    }
    p = (int*)(self + 0x90);
    if (*p != 0) {
        int old = *p;
        *p = 0;
        if (old != 0) DefaultRefCounted_Release((void*)old);
    }
}

// @ 0x005402c0  (vector of 8-byte pairs: push_back)
void Obj::FUN_005402c0(int* value)
{
    int* v = (int*)this;
    if ((unsigned int)v[1] < (unsigned int)v[2]) {
        int* dst = (int*)v[1];
        v[1] = v[1] + 8;
        if (dst != 0) {
            dst[0] = value[0];
            dst[1] = value[1];
        }
    } else {
        FUN_00540560((int*)v[1], value);
    }
}

// @ 0x00540340
unsigned int Obj::FUN_00540340(int key)
{
    int* map = (int*)this;
    unsigned int h = FUN_0050ea00(key);
    unsigned int idx = h & 0x3fff;
    if (*(char*)(*map + idx * 8 + 3) != (char)-1
        && *(int*)(*map + idx * 8) != key) {
        unsigned int n = 1;
        do {
            idx = idx + (h >> 0x10 & 0x3fff | 1) & 0x3fff;
            n = n + 1;
            if (*(int*)(*map + idx * 8) == key)
                return idx;
            if (*(char*)(*map + idx * 8 + 3) == (char)-1)
                return idx;
        } while (n < 0x4001);
        idx = 0xffffffff;
    }
    return idx;
}

// @ 0x00540470
Obj* Obj::FUN_00540470(int unused)
{
    ((int*)this)[0] = 0;
    ((int*)this)[1] = 0;
    ((int*)this)[2] = 0;
    return this;
}

// @ 0x00540560  (vector of 8-byte pairs: DoInsertValue/grow)
void Obj::FUN_00540560(int* pos, int* value)
{
    int* v = (int*)this;
    if (v[1] == v[2]) {
        int oldCount = (v[1] - *v) >> 3;
        int newCap = oldCount == 0 ? 1 : oldCount << 1;
        int* newBuf = newCap == 0 ? 0
            : (int*)FUN_0042dee0((char*)v + 0xc, newCap << 3, 4, 0);
        int at = (pos - (int*)*v) >> 3;
        int* old = (int*)*v;
        for (int i = 0; i < at; i = i + 1) {
            newBuf[i * 2] = old[i * 2];
            newBuf[i * 2 + 1] = old[i * 2 + 1];
        }
        newBuf[at * 2] = value[0];
        newBuf[at * 2 + 1] = value[1];
        for (int i = at; i < oldCount; i = i + 1) {
            newBuf[(i + 1) * 2] = old[i * 2];
            newBuf[(i + 1) * 2 + 1] = old[i * 2 + 1];
        }
        if (old != 0 && *(int*)((char*)old - 4) != 0)
            operator_delete__(old);
        *v = (int)newBuf;
        v[1] = (int)(newBuf + (oldCount + 1) * 2);
        v[2] = (int)(newBuf + newCap * 2);
    } else {
        int* insertAt = pos;
        if ((int*)pos <= (int*)value && (int*)value < (int*)v[1])
            insertAt = value + 2;
        int* dst = (int*)v[1];
        if (dst != 0) {
            dst[0] = *(int*)(v[1] - 8);
            dst[1] = *(int*)(v[1] - 4);
        }
        int* w = (int*)v[1];
        int* r = (int*)(v[1] - 8);
        while (r != insertAt) {
            w[-2] = r[-2];
            w[-1] = r[-1];
            w = w - 2;
            r = r - 2;
        }
        insertAt[0] = value[0];
        insertAt[1] = value[1];
        v[1] = v[1] + 8;
    }
}

// @ 0x005407a0  (resize a vector of 8-byte pairs)
void Obj::FUN_005407a0(unsigned int n)
{
    int* v = (int*)this;
    if ((unsigned int)(v[1] - *v >> 3) < n) {
        FUN_004cef00((void*)v[1], n - (v[1] - *v >> 3), &n);
    } else {
        // vector<pair<int,float>>::erase(begin + n, end) @ 0x530c80
        extern void VectorErasePair(void* begin, void* end);
        VectorErasePair((void*)(*v + n * 8), (void*)v[1]);
    }
}

// @ 0x00540820
unsigned int Obj::FUN_00540820(int key)
{
    int* map = (int*)this;
    unsigned int h = FUN_0050ea00(key);
    unsigned int idx = h & 0x7fff;
    if (*(char*)(idx * 0xc + *map + 3) != (char)-1
        && *(int*)(idx * 0xc + *map) != key) {
        unsigned int n = 1;
        do {
            idx = idx + (h >> 0x10 & 0x7fff | 1) & 0x7fff;
            n = n + 1;
            if (*(int*)(idx * 0xc + *map) == key)
                return idx;
            if (*(char*)(idx * 0xc + *map + 3) == (char)-1)
                return idx;
        } while (n < 0x8001);
        idx = 0xffffffff;
    }
    return idx;
}

// @ 0x0053fe30
unsigned int Obj::FUN_0053fe30(int entry, unsigned char mask)
{
    unsigned short local_8 = gFe30TableA[mask];
    do {
        if (local_8 == 0)
            return 1;
        int local_20 = -1;
        int local_18 = -1;
        unsigned char local_9 = 0;
        unsigned short local_1c = 1;
        for (; local_9 < 0xc && (local_8 & local_1c) == 0; local_1c = local_1c << 1)
            local_9 = local_9 + 1;
        unsigned char local_a;
        if ((mask & gFe30TableB[local_9 * 2]) == 0)
            local_a = local_9 << 1;
        else
            local_a = (unsigned char)(local_9 << 1 | 1);
        unsigned short local_14 = local_a;
        unsigned short local_10 = local_1c;
        do {
            unsigned char bVar1 = gFe30TableC[local_14 ^ 1];
            int local_28, local_2c;
            char* a = (char*)(gPaintVarModNormal + gFe30TableC[local_14]);
            char* b = (char*)(gPaintVarModNormal + bVar1);
            // FUN_0053eaa0(out, x, y)
            extern char* VecAdd(char*, const char*, const char*);
            VecAdd((char*)&local_28, (char*)&entry, a);
            VecAdd((char*)&local_2c, (char*)&entry, b);
            int local_24;
            unsigned int uVar2;
            if ((local_14 & 1) == 0)
                uVar2 = ((Obj*)this)->FUN_0053f960(&local_24, local_28, local_2c, local_28, local_2c);
            else
                uVar2 = ((Obj*)this)->FUN_0053f960(&local_24, local_2c, local_28, local_28, local_2c);
            if ((uVar2 & 0xff) == 0)
                return uVar2 & 0xffffff00;
            if (local_20 == -1)
                local_20 = local_24;
            else if (local_18 == -1)
                local_18 = local_24;
            else {
                if (local_24 != local_18 && local_24 != local_20 && local_18 != local_20) {
                    extern void PushIntVector(int* v, int value);
                    PushIntVector(&local_20, local_20);
                    PushIntVector(&local_18, local_18);
                    PushIntVector(&local_24, local_24);
                }
                local_18 = local_24;
            }
            unsigned int local_34 = *(unsigned int*)(gFe30TableD + (unsigned int)local_14 * 4);
            if (((unsigned short)local_34 & local_8) == 0) {
                local_34 = *(unsigned int*)(gFe30TableE + (unsigned int)local_14 * 4);
                if (((unsigned short)local_34 & local_8) == 0)
                    local_34 = *(unsigned int*)(gFe30TableF + (unsigned int)local_14 * 4);
            }
            local_10 = (unsigned short)local_34;
            local_14 = (unsigned short)(local_34 >> 16);
            local_8 = local_8 ^ (unsigned short)local_34;
        } while (local_14 != local_a);
    } while (true);
}

// @ 0x0053f960
int Obj::FUN_0053f960(int* out, int a, int b, int c, int d)
{
    char* self = (char*)this;
    int local_60 = a;
    int local_5c = b;
    int local_b0 = a;
    int local_ac = b;
    int* local_a8 = (int*)(self + 0x7c);
    unsigned int local_a0 = FUN_0050e850(a, b);
    unsigned int local_8 = local_a0;
    int local_24 = 0;
    char flag;
    if (local_a0 < 0x8000) {
        int local_a4 = local_a0 * 0xc + *local_a8;
        if (FUN_00509850(local_b0, local_ac) != 0) {
            *out = *(int*)(*local_a8 + 8 + local_a0 * 0xc);
            flag = 1;
            goto LAB;
        }
        (void)local_a4;
    }
    flag = 0;
LAB:
    if (flag == 0) {
        *(unsigned int*)(self + 0x1c) = local_8 & 0xffff8000 | *(unsigned int*)(self + 0x1c);
        int local_3c[4];
        int local_50[4];
        FUN_0053f300(self, c, local_3c);
        FUN_0053f300(self, d, local_50);
        if (*(int*)(self + 0x1c) != 0)
            return 0;
        int e0 = local_3c[1];
        int e1 = local_50[1];
        cSPVector3 v0, v1;
        FUN_004098a0(&v0, (cSPVector3*)(*(int*)(self + 0x50) + 0xc + e0 * 0x18));
        FUN_004098a0(&v1, (cSPVector3*)(*(int*)(self + 0x50) + 0xc + e1 * 0x18));
        float half = 0.5f;
        cSPVector3 cross;
        void* pc = FUN_0041dc10(&cross, &v0, &v1);
        cSPVector3 scaled;
        void* ps = FUN_0041de40(&scaled, &half, pc);
        local_24 = *(int*)ps;
        cSPVector3 local_10;
        local_10.x = ((float*)ps)[0];
        local_10.y = ((float*)ps)[1];
        local_10.z = ((float*)ps)[2];
        char* evaluator = *(char**)(self + 0x90);
        float blend;
        typedef char (__thiscall *Fn8)(void*, void*, float*);
        void** vtbl = *(void***)evaluator;
        Fn8 fn = (Fn8)vtbl[2];
        fn(evaluator, &local_10, &blend);
        int local_18;
        if (blend < 0.0f) {
            void* p = FUN_0041de40(&cross, (void*)(self + 0x14), &local_10);
            local_10 = *(cSPVector3*)p;
            local_18 = e0;
        } else {
            void* p = FUN_0041de40(&cross, &local_10, (void*)(*(int*)(self + 0x50) + 0xc + e1 * 0x18));
            local_10 = *(cSPVector3*)p;
            local_18 = e1;
        }
        if (*(int*)(*(int*)(self + 0x50) + 4 + local_18 * 0x18) == -1) {
            int* eval2 = *(int**)(self + 0x94);
            *out = (*(int*)((char*)eval2 + 0xc) - *(int*)((char*)eval2 + 8)) / 0xc;
            *(int*)(*(int*)(self + 0x50) + 4 + local_18 * 0x18) = *out;
            *(int*)(*(int*)(self + 0x50) + 8 + local_18 * 0x18) = e0;
            FUN_004739d0((char*)eval2 + 8);
            int pair[2];
            pair[1] = 1;
            pair[0] = local_18;
            ((Obj*)((char*)eval2 + 0x1b8))->FUN_005402c0(pair);
        } else {
            *out = *(int*)(*(int*)(self + 0x50) + 4 + local_18 * 0x18);
            int* eval3 = *(int**)(self + 0x94);
            FUN_0041ddb0((void*)(*out * 0xc + *(int*)((char*)eval3 + 8)), &local_10);
            int* pv = (int*)(*(int*)((char*)eval3 + 0x1b8) + 4 + *out * 8);
            *pv = *pv + 1;
        }
        int idx = *out;
        int* map = (int*)(self + 0x7c);
        int base = *map;
        *(int*)(base + (local_8 & 0x7fff) * 0xc) = a;
        *(int*)(base + 4 + (local_8 & 0x7fff) * 0xc) = b;
        *(int*)(base + 8 + (local_8 & 0x7fff) * 0xc) = idx;
    }
    return 1;
}
