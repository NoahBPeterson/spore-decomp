// Spore retail 00b930c0..00b9408a -- cGameEditModeStrategy scenario loading,
// planet-surface placement math, closest-water scans, and the array-rebuild
// helpers used by the space/planet editors.
// Compile: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast

#include <stdlib.h>

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" double sqrt(double);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// ------------------------------------------------------------------ callees
// The original object code calls these through `mov ecx,obj; call addr`, i.e. an
// MSVC __thiscall member with the callee popping its stack arguments.  Free
// functions cannot be declared __thiscall (C3865), so every helper is a member
// of one of the stub structs below and the object is passed explicitly.
struct NounManagerStub {
    void FUN_00b225d0_RemoveNoun(int noun);                             // 0x00b225d0
    int  FUN_00b21000(int type, int id);                               // 0x00b21000
    int  FUN_00b23650(int type, int id, void* o1, void* o2, void* o3);  // 0x00b23650
    int  FUN_00b20c60(int type);                                       // 0x00b20c60
};
struct StarManagerStub { int FUN_00ba6d80(u32 id); };                    // 0x00ba6d80
struct BannerStub      { char FUN_00bb9af0(int flag); };                 // 0x00bb9af0
struct TerraformStub   { int FUN_00bbe5f0(int); };                       // 0x00bbe5f0
struct Sub13C          { int FUN_00b8d8f0(); };                          // 0x00b8d8f0
struct PlayerObj       { int FUN_00ff35d0(); };                          // 0x00ff35d0
struct ArrayStub       { void FUN_00ff2d50(int index, int array); };      // 0x00ff2d50
struct AutoRefCountStub{ void Assign(int p); };                          // 0x00b5f950

struct PlanetModelStub {
    void* FUN_00b815a0(void* out, void* pos);                            // 0x00b815a0 ret 8
    char  FUN_00b7e3e0(void* pos);                                       // 0x00b7e3e0 ret 4
    void* FUN_00b7f250(void* out, void* pos, void* up);                  // 0x00b7f250 ret 0xc
    void* FUN_00b7f190(void* out, void* pos);                            // 0x00b7f190 ret 8
    char  FUN_00b8bb70(int handle);                                      // 0x00b8bb70 ret 4
};

// Component sub-object living at object+0x34.  It is only ever used through its
// vtable, so model it as a class with the right number of virtual slots.
struct Sub34 {
    virtual int v00(); virtual int v04(); virtual int v08(); virtual int v0c();
    virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1c();
    virtual int v20(); virtual int v24(); virtual int v28();
    virtual int v2c(float range, float* out);   // 0x2c
    virtual int v30(); virtual int v34();
    virtual int v38(void* pos);                 // 0x38
    virtual int v3c(void* quat);                // 0x3c
    virtual int v40();
};

struct ElemArray {
    int* FUN_00c71000();                                                 // 0x00c71000
    int  FUN_00c710c0();                                                 // 0x00c710c0
    int  FUN_00c71030(int index);                                        // 0x00c71030 ret 4
};
struct IPos          { float* FUN_00572590(); };                         // 0x00572590
struct RandStub      { int FUN_00a68fb0(int n); };                       // 0x00a68fb0 ret 4
struct PropFloatStub { float* FUN_0041ea70(); };                         // 0x0041ea70
struct CmpStub       { char FUN_00ac0730(void* a, void* b); };           // 0x00ac0730 ret 8

// __thiscall vtable-slot call shapes.  The first parameter is `this`; the
// remaining parameters are the callee's stack arguments in MSVC push order.
typedef void (__thiscall *TCV)(void*);                                   // ret 0
typedef void (__thiscall *TCV_p)(void*, void*);                          // ret 4
typedef char (__thiscall *TCC_k2)(void*, int, void**);                   // (key, out) ret 8
typedef char (__thiscall *TCC_3v)(void*, void*, void*, void*);           // (a, b, out) ret 0xc
typedef int  (__thiscall *TCI_p)(void*, int);                            // (arg) ret 4
typedef int  (__thiscall *TCI_fp)(void*, float, void*);                  // (float, out) ret 8
typedef void (__thiscall *TCV_III)(void*, int, int, int);                // ret 0xc
typedef void (__thiscall *TCV_ppp)(void*, void*, void*, void*);          // ret 0xc, all pointers

// Argument-less accessors are plain cdecl functions in the original.
extern "C" void* SP_PlanetModel();                              // 0x00b3d350
extern "C" void* SP_NounManager();                              // 0x00b3d300
extern "C" void* SP_StarManager();                              // 0x00b3d2a0
extern "C" void* SP_TerraformingManager();                       // 0x00b3d430
extern "C" void* SP_PropertyManager();                          // 0x0067de30

extern "C" void* FUN_0059aed0(void* out, void* vec, void* quat); // 0x0059aed0
extern "C" void* FUN_00bd8750(void* out, void* pos);             // 0x00bd8750
extern "C" int   FUN_00ae2e40(int* self, int* stream);           // 0x00ae2e40
extern "C" int   EA_IO_WriteUint32(void* s, void* p, int n, int z); // 0x0093aa70
extern "C" int   EA_IO_StreamWrite(void* s, void* p, int n);     // 0x0093a9a0
extern "C" void  FUN_00f47380(void* p);                          // 0x00f47380
extern "C" void  SP_GetPropertyAsKey(void* obj, int key, void* out3); // 0x006a1250
extern "C" void* FUN_006bb5e0();                                 // 0x006bb5e0
extern "C" int   FUN_00b90b10(int* arr, int top, int index, int* elem,
                              float kx, float ky, float kz);      // 0x00b90b10
extern "C" char  FUN_00b931c0(void* self, int type, int id);     // 0x00b931c0
extern "C" void  FUN_00b93a90(int* arr, int top, int end, int start,
                              int* elem, float kx, float ky, float kz); // 0x00b93a90
extern "C" void  FUN_00b93cc0(int* arr, int* slot, float fx, float fy, float fz); // 0x00b93cc0
extern "C" float FUN_00b93dc0(void* self, int mode);             // 0x00b93dc0
extern "C" void  FUN_00b93f40(int pos, int self, int p3, int p4);// 0x00b93f40
extern "C" int   FUN_00b94090(void* a0, void* a1, int type, int id,
                              int unused, int* out, char load);  // 0x00b94090
extern "C" __declspec(dllimport) int __cdecl msvcr90_rand();     // 0x013cc560 imported rand

// ------------------------------------------------------------------ constants
extern float DAT_01465960;      // 70.0f
extern float DAT_01465984;      // FLT_MAX
extern float DAT_014659c8;      // 55.0f
extern float DAT_01465a04;      // 0x42420000
extern float DAT_01465a08;      // 0x42832560
extern float DAT_013ec4b8;      // 1e-08f
extern float DAT_013eb8b0;      // sign mask
extern float DAT_01470f1c;      // 2.0f
extern float DAT_01471064;      // 0.5f
extern float DAT_01488874;      // 0.1f
extern float DAT_013eecd8;      // 20.0f
extern float DAT_0168894c;      // direction vector base
extern u8    DAT_015d9c70;

// ---------------------------------------------------------------------------
// 0x00b930c0 -- serialise the global scenario record array (stride 0x10).
// ---------------------------------------------------------------------------
struct ScenarioRecord {
    int mField0;        // +0x00
    int mField4;        // +0x04
    int mNoun;          // +0x08  noun + 0x504 is the stream target
    u8  mFlag;          // +0x0c
    u8  pad0d; u8 pad0e; u8 pad0f;
};

struct StreamAPI {
    virtual int v00(); virtual int v04();                   // +0x00, +0x04
    virtual int v08(); virtual int v0c();
    virtual int v10(); virtual int v14();
    virtual int GetStream();                                // +0x18
    virtual int v1c();
    virtual int GetSubStream();                             // +0x20
};

extern ScenarioRecord* DAT_0168890c;    // 0x0168890c begin
extern ScenarioRecord* DAT_01688910;    // 0x01688910 end

// @ 0x00b930c0
int FUN_00b930c0(StreamAPI* self)
{
    int count = DAT_01688910 - DAT_0168890c;

    StreamAPI* a = (StreamAPI*)self->GetSubStream();
    int stream = a->GetStream();
    EA_IO_WriteUint32((void*)stream, &count, 1, 0);

    ScenarioRecord* r = DAT_0168890c;
    ScenarioRecord* end = DAT_01688910;
    while (r != end) {
        StreamAPI* w1 = (StreamAPI*)self->GetSubStream();
        int s1 = w1->GetStream();
        EA_IO_WriteUint32((void*)s1, &r->mField0, 1, 0);

        StreamAPI* w2 = (StreamAPI*)self->GetSubStream();
        int s2 = w2->GetStream();
        EA_IO_WriteUint32((void*)s2, &r->mField4, 1, 0);

        FUN_00ae2e40((int*)self, (int*)(r->mNoun + 0x504));

        StreamAPI* w3 = (StreamAPI*)self->GetSubStream();
        int s3 = w3->GetStream();
        u8 flag = (r->mFlag != 0) ? 1 : 0;
        EA_IO_StreamWrite((void*)s3, &flag, 1);

        ++r;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00b931c0 -- SP::cGameEditModeStrategy::LoadScenario (cdecl: self, type, id)
// ---------------------------------------------------------------------------
// @ 0x00b931c0
extern "C" char FUN_00b931c0(void* selfp, int type, int id)
{
    int* self = (int*)selfp;
    if (self == 0)
        return 0;

    int nm = (int)SP_NounManager();
    int* slot = (int*)((char*)self + 0x1a4);
    if (*slot != 0) {
        ((NounManagerStub*)(void*)nm)->FUN_00b225d0_RemoveNoun(*slot);
        int* p = (int*)*slot;
        if (p != 0) {
            *slot = 0;
            ((TCV)(*(void***)p)[1])((void*)p);
        }
    }

    int i = id;
    if (i == -1)
        i = *(int*)((char*)self + 0x110);
    int t = type;
    if (t == -1)
        t = *(int*)((char*)self + 0x10c);

    if (t == 0 || i == 0)
        return 0;

    char* s = (char*)self;
    if (t == 0x36be27e) {
        int r = ((NounManagerStub*)(void*)nm)->FUN_00b21000(t, i);
        if (r != 0) {
            ((TCV_ppp)(*(void***)self)[0x24 / 4])((void*)self, (void*)r,
                                                  s + 0x114, s + 0x1a8);
        }
    } else {
        int r = ((NounManagerStub*)(void*)nm)->FUN_00b23650(
                    t, i, s + 0x114, s + 0x1a8, s + 0x1b4);
        ((AutoRefCountStub*)(void*)slot)->Assign(r);
        if (r == 0)
            *(u8*)(s + 0x1c4) = 1;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00b932a0 -- step a point along a surface direction and re-project it.
// ---------------------------------------------------------------------------
// @ 0x00b932a0
void FUN_00b932a0(float* pos, float* outQuat, float range)
{
    float buf[3];
    float* v = (float*)FUN_0059aed0(buf, &DAT_0168894c, outQuat);
    buf[0] = v[0];
    buf[1] = v[1];
    buf[2] = v[2];

    float inv = (float)(1.0 / sqrt((double)buf[2] * buf[2] + (double)buf[0] * buf[0] +
                                   (double)buf[1] * buf[1] + DAT_013ec4b8));
    float ux = -(inv * buf[0]);
    float uy = -(inv * buf[1]);
    float hi = range * DAT_01470f1c;
    float lo = range;
    float uz = -(inv * buf[2]);

    float t;
    int iter = 0;
    do {
        t = (hi - lo) * DAT_01471064 + lo;

        buf[0] = pos[0] + ux * t;
        buf[1] = pos[1] + uy * t;
        buf[2] = pos[2] + uz * t;

        float scratch[3];
        float* r = (float*)((PlanetModelStub*)SP_PlanetModel())->FUN_00b815a0(scratch, buf);
        buf[0] = r[0];
        buf[1] = r[1];
        buf[2] = r[2];

        char ok = ((PlanetModelStub*)SP_PlanetModel())->FUN_00b7e3e0(buf);
        if (ok != 0)
            hi = t;
        else
            lo = t;
        ++iter;
    } while (DAT_01488874 <= hi - lo && iter < 12);

    float dt = t - range;
    pos[0] += ux * dt;
    pos[1] += uy * dt;
    pos[2] += uz * dt;

    float scratch[3];
    float* r = (float*)((PlanetModelStub*)SP_PlanetModel())->FUN_00b815a0(scratch, pos);
    pos[0] = r[0];
    pos[1] = r[1];
    pos[2] = r[2];

    void* up = FUN_00bd8750(scratch, pos);
    float quat[4];
    float* q = (float*)((PlanetModelStub*)SP_PlanetModel())->FUN_00b7f250(
                     quat, pos, up);
    outQuat[0] = q[0];
    outQuat[1] = q[1];
    outQuat[2] = q[2];
    outQuat[3] = q[3];

    if (range < DAT_014659c8) {
        pos[0] += ux * DAT_013eecd8;
        pos[1] += uy * DAT_013eecd8;
        pos[2] += uz * DAT_013eecd8;
    }
}

// Round to nearest, ties to even -- what cvtss2si does with the default MXCSR.
static int RoundEven(float x)
{
    if (x >= 4194304.0f || x <= -4194304.0f)
        return (int)x;                  // |x| >= 2^22: no roundable fraction at this scale
    float m = 12582912.0f;              // 1.5 * 2^23: forces round-to-nearest-even
    x = (x + m) - m;
    return (int)x;
}

// ---------------------------------------------------------------------------
// 0x00b93550 -- banner-derived planet population target.
// ---------------------------------------------------------------------------
// @ 0x00b93550
int FUN_00b93550(void* arg0, char* self)
{
    int id = ((Sub13C*)(void*)*(int*)(self + 0x13c))->FUN_00b8d8f0();
    int banner = ((StarManagerStub*)SP_StarManager())->FUN_00ba6d80((u32)id);
    char have = ((BannerStub*)(void*)banner)->FUN_00bb9af0(0x100) != 0;
    int pop = ((PlayerObj*)arg0)->FUN_00ff35d0();
    int denom = 4;
    if (have != 0)
        denom = 2;
    float ratio = (float)pop / (float)denom;

    int base = 2;
    if (have == 0)
        base = ((TerraformStub*)SP_TerraformingManager())->FUN_00bbe5f0(0);

    float prod = (float)base * ratio;
    return RoundEven(prod);
}

// ---------------------------------------------------------------------------
// 0x00b935e0 -- find the closest pair of elements between two arrays.
// ---------------------------------------------------------------------------
// @ 0x00b935e0
void* FUN_00b935e0(void* out, int param_2, int param_3)
{
    int* o = (int*)out;
    o[0] = 0;
    o[1] = 0;
    *(float*)((char*)o + 8) = DAT_01465984;

    if (param_2 == 0 || param_3 == 0)
        return out;

    int* arr = ((ElemArray*)(void*)param_2)->FUN_00c71000();
    if ((u32)((arr[1] - arr[0]) >> 2) <= 1)
        return out;

    int nOuter = (*(int*)(param_3 + 0x40) - *(int*)(param_3 + 0x3c)) >> 2;
    if (nOuter <= 0)
        return out;

    for (int i = 0; i < nOuter; ++i) {
        int el = *(int*)(*(int*)(param_3 + 0x3c) + i * 4);
        int n = ((ElemArray*)(void*)param_2)->FUN_00c710c0();
        if (n <= 0)
            continue;
        for (int j = 0; j < n; ++j) {
            int obj = ((ElemArray*)(void*)param_2)->FUN_00c71030(j);
            if (obj == param_3)
                continue;
            int nElem = (*(int*)(obj + 0x40) - *(int*)(obj + 0x3c)) >> 2;
            if (nElem <= 0)
                continue;
            for (int k = 0; k < nElem; ++k) {
                int u = *(int*)(*(int*)(obj + 0x3c) + k * 4);
                float* pa = ((IPos*)(void*)u)->FUN_00572590();
                float* pb = ((IPos*)(void*)el)->FUN_00572590();
                float dy = pb[1] - pa[1];
                float dx = pb[0] - pa[0];
                float dz = pb[2] - pa[2];
                float dist = (dx * dx + dy * dy) + dz * dz;
                if (dist < *(float*)((char*)o + 8)) {
                    *(float*)((char*)o + 8) = dist;
                    o[0] = u;
                    o[1] = obj;
                }
            }
        }
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b93750 -- seed random colours on a set of arrays.
// ---------------------------------------------------------------------------
// @ 0x00b93750
void FUN_00b93750(int count, int param_2)
{
    if (count <= 0)
        return;
    do {
        int n = ((ElemArray*)(void*)param_2)->FUN_00c710c0();
        int r = ((RandStub*)0x1601760)->FUN_00a68fb0(n);
        int arr = ((ElemArray*)(void*)param_2)->FUN_00c71030(r);
        if ((*(int*)(arr + 0x40) - *(int*)(arr + 0x3c)) & 0xfffffffc) {
            int local[3];
            FUN_00b935e0(local, param_2, arr);
            int local0 = local[0];
            int local1 = local[1];
            if (local0 != 0 && local1 != 0) {
                int n2 = (*(int*)(local1 + 0x40) - *(int*)(local1 + 0x3c)) >> 2;
                char found = 0;
                for (int i = 0; i < n2; ++i) {
                    if (found != 0)
                        break;
                    if (*(int*)(*(int*)(local1 + 0x3c) + i * 4) == local0) {
                        found = 1;
                        ((ArrayStub*)(void*)local1)->FUN_00ff2d50(i, arr);
                    }
                }
            }
        }
        --count;
    } while (count != 0);
}

// ---------------------------------------------------------------------------
// 0x00b93810 / 0x00b93840 -- two tiny float-pair constructors (distinct vtables).
// ---------------------------------------------------------------------------
struct FloatPairCtorA {
    FloatPairCtorA* FUN_00b93810(float a, float b);
};
struct FloatPairCtorB {
    FloatPairCtorB* FUN_00b93840(float a, float b);
};

// @ 0x00b93810
FloatPairCtorA* FloatPairCtorA::FUN_00b93810(float a, float b)
{
    *(float*)((char*)this + 8) = a;
    *(int*)((char*)this + 4) = 0;
    *(int*)this = 0x14659cc;
    *(float*)((char*)this + 0xc) = b;
    return this;
}

// @ 0x00b93840
FloatPairCtorB* FloatPairCtorB::FUN_00b93840(float a, float b)
{
    *(float*)((char*)this + 8) = a;
    *(int*)((char*)this + 4) = 0;
    *(int*)this = 0x14659e8;
    *(float*)((char*)this + 0xc) = b;
    return this;
}

// ---------------------------------------------------------------------------
// 0x00b93870 -- weighted random pick from a float array, dispatch to element.
// ---------------------------------------------------------------------------
struct Weighted {
    void FUN_00b93870(int, int, int);
};

// @ 0x00b93870
void Weighted::FUN_00b93870(int a, int b, int c)
{
    int* self = (int*)this;
    int idx = msvcr90_rand() % self[0xc];
    unsigned count = (unsigned)((self[3] - self[2]) >> 2);
    unsigned i = 0;
    _ReadWriteBarrier();
    if (count > 0) {
        int* w = (int*)self[2];
        do {
            idx -= *w;
            if (idx < 0) {
                int el = *(int*)(self[7] + i * 4);
                ((TCV_III)(*(void***)el)[0x10 / 4])((void*)el, a, b, c);
                return;
            }
            ++i;
            ++w;
        } while (i < count);
    }
}

// ---------------------------------------------------------------------------
// 0x00b938d0 -- read a float3 property or use a fallback float3.
// ---------------------------------------------------------------------------
// @ 0x00b938d0
struct Float3 { float x, y, z; };
typedef char (__thiscall *TC_Char_IPtr)(void*, int, int*);

float* FUN_00b938d0(float* out, int* prop, int mode, float fx, float fy, float fz)
{
    if (prop != 0) {
        char ok = ((TC_Char_IPtr)(*(void***)prop)[0x24 / 4])((void*)prop, mode, (int*)&prop);
        if (ok != 0) {
            int p = (int)prop;
            u16 type = *(u16*)((char*)p + 0x12);
            float* src;
            if (type == 0x31 || type == 0x10) {
                if ((*(u8*)((char*)p + 0x10) & 0x30) != 0)
                    src = *(float**)p;
                else
                    src = (float*)(type != 0 ? p : 0);
            } else {
                src = (float*)FUN_006bb5e0();
            }
            Float3* o = (Float3*)out;
            o->x = src[0];
            o->y = src[1];
            o->z = src[2];
            return out;
        }
    }
    out[0] = fx;
    out[1] = fy;
    out[2] = fz;
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b939f0 -- rebuild a bucket array with a new bucket count.
// ---------------------------------------------------------------------------
struct BucketArray {
    int* FUN_00b93980(int buckets);      // 0x00b93980 allocate
    void FUN_00b939f0(int buckets);
};

// @ 0x00b939f0
void BucketArray::FUN_00b939f0(int param_2)
{
    int* self = (int*)this;
    int* buckets = (int*)FUN_00b93980(param_2);
    for (u32 i = 0; i < (u32)self[2]; ++i) {
        int* p = *(int**)(self[1] + i * 4);
        while (p != 0) {
            unsigned rem = (unsigned)p[0] % (unsigned)param_2;
            int* next = (int*)p[0x10];
            *(int*)(self[1] + i * 4) = (int)next;
            p[0x10] = buckets[rem];
            buckets[rem] = (int)p;
            p = *(int**)(self[1] + i * 4);
        }
    }
    int* old = (int*)self[1];
    if ((u32)self[2] > 1 && old != (int*)self[0x30 / 4]) {
        if (old < (int*)self[0x24 / 4] || old >= (int*)self[0x28 / 4]) {
            FUN_00f47380(old);
        } else {
            *old = self[0x1c / 4];
            self[0x1c / 4] = (int)old;
        }
    }
    self[1] = (int)buckets;
    self[2] = param_2;
}

// ---------------------------------------------------------------------------
// 0x00b93a90 -- sift-down helper over reference-counted elements.
// ---------------------------------------------------------------------------
// @ 0x00b93a90
void FUN_00b93a90(int* arr, int top, int end, int start, int* elem,
                  float kx, float ky, float kz)
{
    int i = start;
    int j = i * 2 + 2;
    if (j < end) {
        do {
            if (((CmpStub*)(void*)&kx)->FUN_00ac0730((void*)arr[j], (void*)arr[j - 1]))
                --j;
            int* cur = (int*)arr[i];
            int* child = (int*)arr[j];
            if (child != cur) {
                if (child != 0)
                    ((TCV)(*(void***)child)[0xbc / 4])((void*)child);
                arr[i] = (int)child;
                if (cur != 0)
                    ((TCV)(*(void***)cur)[0xc0 / 4])((void*)cur);
            }
            i = j;
            j = i * 2 + 2;
        } while (j < end);
    }
    if (j == end) {
        int* cur = (int*)arr[i];
        int* child = (int*)arr[j - 1];
        if (child != cur) {
            if (child != 0)
                ((TCV)(*(void***)child)[0xbc / 4])((void*)child);
            arr[i] = (int)child;
            if (cur != 0)
                ((TCV)(*(void***)cur)[0xc0 / 4])((void*)cur);
        }
        i = j - 1;
    }
    if (elem != 0)
        ((TCV)(*(void***)elem)[0xbc / 4])((void*)elem);
    FUN_00b90b10(arr, top, i, elem, kx, ky, kz);
    if (elem != 0)
        ((TCV)(*(void***)elem)[0xc0 / 4])((void*)elem);
}

// ---------------------------------------------------------------------------
// 0x00b93ba0 -- find the first array element with no closest water.
// ---------------------------------------------------------------------------
// @ 0x00b93ba0
int* FUN_00b93ba0(int* begin, int* end)
{
    int* p = begin;
    while (p != end) {
        int obj = *p;
        float out[3];
        void** vt = *(void***)(obj + 0x34);
        int handle = ((TCI_fp)vt[0x2c / 4])((void*)(obj + 0x34), DAT_01465960, out);
        char c = ((PlanetModelStub*)SP_PlanetModel())->FUN_00b8bb70(handle);
        if (c == 0)
            break;
        ++p;
    }
    return p;
}

// ---------------------------------------------------------------------------
// 0x00b93bf0 -- copy the elements with no closest water.
// ---------------------------------------------------------------------------
// @ 0x00b93bf0
int* FUN_00b93bf0(int* begin, int* end, int* out)
{
    if (begin != end) {
        do {
            int obj = *begin;
            float tmp[3];
            int handle = ((Sub34*)(obj + 0x34))->v2c(DAT_01465960, tmp);
            char c = ((PlanetModelStub*)SP_PlanetModel())->FUN_00b8bb70(handle);
            if (c != 0) {
                *out = *begin;
                ++out;
            }
            ++begin;
        } while (begin != end);
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b93cc0 -- move a reference into slot[-1] then re-heapify.
// ---------------------------------------------------------------------------
// @ 0x00b93cc0
void FUN_00b93cc0(int* arr, int* slot, float fx, float fy, float fz)
{
    int* old = (int*)slot[-1];
    if (old != 0)
        ((TCV)(*(void***)old)[0xbc / 4])((void*)old);
    int* nw = (int*)*arr;
    int* prev = (int*)slot[-1];
    if (nw != prev) {
        if (nw != 0)
            ((TCV)(*(void***)nw)[0xbc / 4])((void*)nw);
        slot[-1] = (int)nw;
        if (prev != 0)
            ((TCV)(*(void***)prev)[0xc0 / 4])((void*)prev);
    }
    if (old != 0)
        ((TCV)(*(void***)old)[0xbc / 4])((void*)old);
    FUN_00b93a90(arr, 0, (int)(slot - arr) - 1, 0, old, fx, fy, fz);
    if (old != 0)
        ((TCV)(*(void***)old)[0xc0 / 4])((void*)old);
}

// ---------------------------------------------------------------------------
// 0x00b93dc0 -- property-driven macro-stage value getter.
// ---------------------------------------------------------------------------
// @ 0x00b93dc0
extern "C" float FUN_00b93dc0(void* self, int mode)
{
    float value;
    if (mode == 0 || mode == 2)
        value = DAT_01465a04;
    else
        value = DAT_01465a08;

    int* temp = 0;
    void* pm = SP_PropertyManager();
    char ok = ((TCC_3v)(*(void***)pm)[0x2c / 4])(pm, self, (void*)0x2e4b4cc,
                                                  (void*)&temp);
    if (ok == 0) {
        if (temp != 0) {
            int* t = temp;
            temp = 0;
            ((TCV)(*(void***)t)[1])((void*)t);
        }
        return value;
    }

    int vec[3];
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
    switch (mode) {
    case 0:
        SP_GetPropertyAsKey(self, 0x44449ba, vec);
        break;
    case 1:
        SP_GetPropertyAsKey((void*)temp, 0x44449bb, vec);
        break;
    case 2:
        SP_GetPropertyAsKey((void*)temp, 0x44449bc, vec);
        break;
    case 3:
        SP_GetPropertyAsKey(self, 0x44449bd, vec);
        break;
    }
    vec[2] = 0x40828100;

    int* temp2 = 0;
    void* pm2 = SP_PropertyManager();
    char ok2 = ((TCC_3v)(*(void***)pm2)[0x2c / 4])(pm2, (void*)vec[0],
                                                    (void*)vec[2], (void*)&temp2);
    if (ok2 != 0 && temp2 != 0) {
        int* t3 = 0;
        char ok3 = ((TCC_k2)(*(void***)temp2)[0x24 / 4])(
                       (void*)temp2, 0x4408ed7, (void**)&t3);
        if (ok3 != 0 && *(u16*)((char*)t3 + 0x12) == 0xd)
            value = *((PropFloatStub*)(void*)t3)->FUN_0041ea70();
    }

    if (temp2 != 0) {
        int* t = temp2;
        temp2 = 0;
        ((TCV)(*(void***)t)[1])((void*)t);
    }
    if (temp != 0) {
        int* t = temp;
        temp = 0;
        ((TCV)(*(void***)t)[1])((void*)t);
    }
    return value;
}

// ---------------------------------------------------------------------------
// 0x00b93f40 -- create a scenario noun and initialise its fields.
// ---------------------------------------------------------------------------
// @ 0x00b93f40
extern "C" void FUN_00b93f40(int pos, int selfp, int p3, int p4)
{
    int obj = *(int*)(selfp + 0x43c);
    u8 useDefault = 0;
    if (obj != 0) {
        int got = 0;
        char ok = ((TCC_k2)(*(void***)obj)[0x24 / 4])((void*)obj, 0xa8f33541, (void**)&got);
        if (ok != 0) {
            u16 type = *(u16*)(got + 0x12);
            if (type == 1 || type == 0x10) {
                if ((*(u8*)(got + 0x10) & 0x30) != 0)
                    useDefault = *(u8*)(*(int*)got);
                else
                    useDefault = *(u8*)(type != 0 ? got : 0);
            } else {
                useDefault = DAT_015d9c70;
            }
        }
    }

    int noun = ((NounManagerStub*)SP_NounManager())->FUN_00b20c60(0x36be27e);
    int s = 0;
    if (noun != 0)
        s = ((TCI_p)(*(void***)noun)[0xc / 4])((void*)noun, 0x36be278);

    *(int*)(s + 0x11c) = 0;
    *(int*)(s + 0x120) = 0;
    *(int*)(s + 0x124) = 0;
    *(int*)(s + 0x13c) = 0;
    *(int*)(s + 0x114) = p4;
    *(int*)(s + 0x110) = p3;
    *(int*)(s + 0x128) = (useDefault == 0);
    *(int*)(s + 0x108) = 0x91fe517b;
    *(int*)(s + 0x10c) = 0x1be418e;
    *(int*)(s + 0x12c) = 0;
    *(int*)(s + 0x130) = 0;
    *(int*)(s + 0x134) = 0;
    *(int*)(s + 0x138) = 0;
    *(int*)(s + 0x140) = 5;

    ((Sub34*)(s + 0x34))->v38((void*)pos);

    float quat[4];
    ((PlanetModelStub*)SP_PlanetModel())->FUN_00b7f190(quat, (void*)pos);
    ((Sub34*)(s + 0x34))->v3c(quat);

    FUN_00b931c0((void*)s, -1, -1);
}

// ---------------------------------------------------------------------------
// 0x00b94090 -- build a scenario noun from type/id and optionally load it.
// ---------------------------------------------------------------------------
// @ 0x00b94090
extern "C" int FUN_00b94090(void* a0, void* a1, int type, int id,
                            int unused, int* out, char load)
{
    int noun = ((NounManagerStub*)SP_NounManager())->FUN_00b20c60(0x36be27e);
    int s = 0;
    if (noun != 0)
        s = ((TCI_p)(*(void***)noun)[0xc / 4])((void*)noun, 0x36be278);

    *(int*)(s + 0x108) = 0;
    *(int*)(s + 0x114) = 0;
    *(int*)(s + 0x10c) = type;
    *(int*)(s + 0x110) = id;

    ((Sub34*)(s + 0x34))->v38(a0);
    ((Sub34*)(s + 0x34))->v3c(a1);

    if (type == 0x1be418e)
        *(int*)(s + 0x108) = 0x91fe517b;
    else if (type == 0x36be27e)
        *(int*)(s + 0x108) = id;

    char r = 0;
    if (load != 0) {
        if (FUN_00b931c0((void*)s, -1, -1) != 0)
            r = 1;
    }
    if (out != 0)
        *out = s;
    return r;
}
