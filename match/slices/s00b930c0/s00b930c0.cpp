// Spore retail 00b930c0..00b9408a -- cGameEditModeStrategy scenario loading,
// planet-surface placement math, closest-water scans, and the array-rebuild
// helpers used by the space/planet editors.
// Compile: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" float sqrtf(float);

// ------------------------------------------------------------------ callees
struct ThiscallStub {
    // 0x00b225d0 remove a noun from the noun manager
    void FUN_00b225d0_RemoveNoun(int noun);
    // 0x00ba6d80 returns the star banner-list for a star record
    int  FUN_00ba6d80(u32 id);
    // 0x00bb9af0 test a banner-list flag
    char FUN_00bb9af0(int flag);
    // 0x00bbe5f0 terraforming score query
    int  FUN_00bbe5f0();
    // 0x00b20c60 create a noun of a fixed type
    int  FUN_00b20c60(int type);
    // 0x00b21000 build scenario noun (fixed type)
    int  FUN_00b21000(int type, int id);
    // 0x00b23650 build scenario noun (generic type)
    int  FUN_00b23650(int type, int id, void* out1, void* out2, void* out3);
    // 0x00ff2d50 set element index on an array
    void FUN_00ff2d50(int index, int array);
};

// __fastcall puts its first argument in ECX (== thiscall's this) and pops the
// stack arguments itself when declared __thiscall-style; free stubs are used
// where no `this` object exists.
extern "C" void* SP_PlanetModel(void* out, void* pos);          // 0x00b3d350
extern "C" void* SP_NounManager();                              // 0x00b3d300
extern "C" void* SP_StarManager();                              // 0x00b3d2a0
extern "C" void* SP_TerraformingManager(int);                   // 0x00b3d430
extern "C" void* SP_PropertyManager();                          // 0x0067de30
extern "C" int   FUN_00b8d8f0();                                // 0x00b8d8f0
extern "C" int   FUN_00ff35d0();                                // 0x00ff35d0
extern "C" int   FUN_006bb5e0();                                // 0x006bb5e0
extern "C" void* FUN_0059aed0(void* out, void* key, void* src); // 0x0059aed0
extern "C" char  FUN_00b7e3e0(float* pos);                      // 0x00b7e3e0
extern "C" void* FUN_00bd8750(void* out, void* pos);            // 0x00bd8750
extern "C" int   FUN_00c71000(int);                             // 0x00c71000
extern "C" int   FUN_00c710c0(int);                             // 0x00c710c0
extern "C" int   FUN_00c71030(int self, int index);             // 0x00c71030
extern "C" void* FUN_00572590(int self);                        // 0x00572590 UintArray::Self
extern "C" int   FUN_00f47380(void*);                           // 0x00f47380 operator delete[]
extern "C" int   FUN_00ac0730(int, int);                        // 0x00ac0730 array element compare
extern "C" int   FUN_00b90b10(int*, int, int, ...);             // 0x00b90b10 rebuild range
extern "C" int   SP_GetPropertyAsKey(int, int, void*);          // 0x006a1250
extern "C" float* __fastcall Property_GetFloat(void*);          // 0x0041ea70
extern "C" int   FUN_00ae2e40(int*, int*);                      // 0x00ae2e40 stream write vector
extern "C" int   EA_IO_WriteUint32(void*, void*, int, int);     // 0x0093aa70
extern "C" int   EA_IO_StreamWrite(void*, int, int);            // 0x0093a9a0
extern "C" int   EA_Random_RandomUint32Uniform(void*, int);     // 0x00a68fb0
extern "C" int   msvcr90_rand();                                // 0x013cc560
extern "C" void* SP_cPlanetModel_BuildSurfaceOrientation(void* self, void* out, void* pos, void* up); // 0x00b7f190
extern "C" void* SP_cPlanetModel_DirectionToSurfacePosition(void* self, void* out, void* dir);         // 0x00b7... 
extern "C" char  SP_cPlanetModel_FindClosestWater(void* self, float range, void* out);                 // 0x00b8bb70
extern "C" void  EA_UTFWin_AutoRefCount_Assign(int);            // 0x00b5f950

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
    ScenarioRecord* begin = DAT_0168890c;
    ScenarioRecord* end   = DAT_01688910;
    int count = (int)((char*)end - (char*)begin) >> 4;

    StreamAPI* a = (StreamAPI*)self->GetSubStream();
    int stream = a->GetStream();
    EA_IO_WriteUint32((void*)stream, &count, 1, 0);

    for (ScenarioRecord* r = DAT_0168890c; r != DAT_01688910; ++r) {
        StreamAPI* w1 = (StreamAPI*)self->GetSubStream();
        int v0 = r->mField0;
        int s1 = w1->GetStream();
        EA_IO_WriteUint32((void*)s1, &v0, 1, 0);

        StreamAPI* w2 = (StreamAPI*)self->GetSubStream();
        int v1 = r->mField4;
        int s2 = w2->GetStream();
        EA_IO_WriteUint32((void*)s2, &v1, 1, 0);

        FUN_00ae2e40((int*)self, (int*)((char*)(int)r->mNoun + 0x504));

        StreamAPI* w3 = (StreamAPI*)self->GetSubStream();
        u8 flag = r->mFlag;
        int s3 = w3->GetStream();
        int b = (flag != 0) ? 1 : 0;
        EA_IO_StreamWrite((void*)s3, b, 1);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00b931c0 -- SP::cGameEditModeStrategy::LoadScenario
// ---------------------------------------------------------------------------
struct IWinText;
struct GameEditStrategy {
    char FUN_00b931c0(int type, int id);
    int FUN_00b93dc0(int mode);
};

// @ 0x00b931c0
char GameEditStrategy::FUN_00b931c0(int param_2, int param_3)
{
    int* self = (int*)this;
    if (self == 0)
        return 0;

    ThiscallStub* nm = (ThiscallStub*)SP_NounManager();
    int* slot = (int*)((char*)self + 0x1a4);
    if (*slot != 0) {
        ((ThiscallStub*)nm)->FUN_00b225d0_RemoveNoun(*slot);
        int* p = (int*)*slot;
        if (p != 0) {
            *slot = 0;
            ((void(__fastcall*)(void*))(*(void***)p)[1])(p);
        }
    }

    int t = param_2;
    if (t == -1)
        t = *(int*)((char*)self + 0x10c);
    int i = param_3;
    if (i == -1)
        i = *(int*)((char*)self + 0x110);

    if (t == 0 || i == 0)
        return 0;

    if (t == 0x36be27e) {
        int r = ((ThiscallStub*)nm)->FUN_00b21000(0x36be27e, i);
        if (r != 0) {
            ((void(__fastcall*)(void*, void*, void*))(*(void***)self)[0x24 / 4])(
                self, (char*)self + 0x114, (char*)self + 0x1a8);
            return 1;
        }
    } else {
        int r = ((ThiscallStub*)nm)->FUN_00b23650(t, i, (char*)self + 0x114,
                                                (char*)self + 0x1a8, (char*)self + 0x1b4);
        EA_UTFWin_AutoRefCount_Assign(r);
        if (r == 0)
            *(u8*)((char*)self + 0x1c4) = 1;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00b932a0 -- step a point along a surface direction and re-project it.
// ---------------------------------------------------------------------------
extern float DAT_0168894c;              // 0x0168894c direction base
extern float DAT_013ec4b8;              // 0x013ec4b8 1e-08
extern float DAT_013eb8b0;              // 0x013eb8b0 sign mask

// @ 0x00b932a0
void FUN_00b932a0(float* pos, float* outQuat, float range)
{
    float local34[3];
    float* d = (float*)FUN_0059aed0(local34, &DAT_0168894c, pos);
    float dx = d[0];
    float dy = d[1];
    float dz = d[2];

    float inv = 1.0f / (float)sqrtf(dy * dy + (dx * dx + dz * dz) + DAT_013ec4b8);
    float ux = -(inv * dx);
    float uy = -(inv * dy);
    float uz = -(inv * dz);

    float lo = range;
    float hi = range * 2.0f;
    float t = 0.0f;
    int iter = 0;
    do {
        t = (hi - lo) * 0.5f + lo;
        float px = pos[0] + ux * t;
        float py = pos[1] + uy * t;
        float pz = pos[2] + uz * t;

        float pm[3];
        void* model = SP_PlanetModel(0, pm);
        (void)model;
        float* q = (float*)SP_cPlanetModel_DirectionToSurfacePosition(0, pm, pm);
        pm[0] = q[0]; pm[1] = q[1]; pm[2] = q[2];
        char ok = FUN_00b7e3e0(pm);
        if (ok == 0) { lo = t; }
        else          { hi = t; }
        iter++;
    } while ((0.1f <= hi - lo) && iter < 12);

    float dt = t - range;
    pos[0] += ux * dt;
    pos[1] += uy * dt;
    pos[2] += uz * dt;

    float pm[3];
    void* model = SP_PlanetModel(0, pos);
    (void)model;
    float* q = (float*)SP_cPlanetModel_DirectionToSurfacePosition(0, pos, pos);
    pos[0] = q[0]; pos[1] = q[1]; pos[2] = q[2];

    float up[3];
    void* u = FUN_00bd8750(pm, pos);
    (void)u;
    float* quat = (float*)SP_cPlanetModel_BuildSurfaceOrientation(0, up, pos, u);
    outQuat[0] = quat[0];
    outQuat[1] = quat[1];
    outQuat[2] = quat[2];
    outQuat[3] = quat[3];

    if (range < 55.0f) {
        pos[0] += ux * 20.0f;
        pos[1] += uy * 20.0f;
        pos[2] += uz * 20.0f;
    }
}

// ---------------------------------------------------------------------------
// 0x00b93550 -- banner-derived planet population target.
// ---------------------------------------------------------------------------
struct BannerList {
    int  FUN_00ba6d80(u32 id);
};
struct PlayerObj {
    int FUN_00ff35d0();
};

// @ 0x00b93550
int __fastcall FUN_00b93550(PlayerObj* self)
{
    int star = FUN_00b8d8f0();
    BannerList* bl = (BannerList*)SP_StarManager();
    int idx = ((ThiscallStub*)bl)->FUN_00ba6d80((u32)star);
    char flag = ((ThiscallStub*)(void*)(long)idx)->FUN_00bb9af0(2);
    (void)flag;
    char haveBanner = ((ThiscallStub*)(void*)(long)idx)->FUN_00bb9af0(0x100);
    int pop = self->FUN_00ff35d0();
    int base;
    if (haveBanner == 0) {
        void* tm = SP_TerraformingManager(0);
        base = ((ThiscallStub*)tm)->FUN_00bbe5f0();
    } else {
        base = 2;
    }
    int denom = haveBanner == 0 ? 2 : 4;
    return (int)(base * ((float)pop / (float)denom) + 0.5f);
}

// ---------------------------------------------------------------------------
// 0x00b935e0 -- find the closest pair of elements between two arrays.
// ---------------------------------------------------------------------------
struct IPosArray {
    void* FUN_00572590();
};
// An object with a dynamic array at +0x3c (begin) / +0x40 (end).
struct Elem {
    void* mpBegin;      // +0x3c
    void* mpEnd;        // +0x40
};

// @ 0x00b935e0
void* FUN_00b935e0(void* out, int param_2, int param_3)
{
    int* o = (int*)out;
    o[0] = 0;
    o[1] = 0;
    *(float*)((char*)o + 8) = 3.402823466e38f;   // FLT_MAX (0x7f7fffff)

    if (param_2 == 0 || param_3 == 0)
        return out;

    int* arr = (int*)FUN_00c71000(param_2);
    if ((u32)((arr[1] - arr[0]) >> 2) <= 1)
        return out;

    int nOuter = (*(int*)(param_3 + 0x40) - *(int*)(param_3 + 0x3c)) >> 2;
    for (int i = 0; i < nOuter; ++i) {
        int nInner = FUN_00c710c0(param_2);
        for (int j = 0; j < nInner; ++j) {
            int obj = FUN_00c71030(param_2, j);
            if (obj == param_3)
                continue;
            int nElem = (*(int*)(obj + 0x40) - *(int*)(obj + 0x3c)) >> 2;
            for (int k = 0; k < nElem; ++k) {
                int u = *(int*)(*(int*)(obj + 0x3c) + k * 4);
                float* pa = (float*)FUN_00572590(u);
                float* pb = (float*)FUN_00572590(*(int*)(*(int*)(param_3 + 0x3c) + i * 4));
                float d = ((pb[0] - pa[0]) * (pb[0] - pa[0]) +
                           (pb[1] - pa[1]) * (pb[1] - pa[1])) +
                          (pb[2] - pa[2]) * (pb[2] - pa[2]);
                if (d < *(float*)(o + 2)) {
                    *(float*)(o + 2) = d;
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
extern char _sMathRandom[];    // 0x01601760 RandomLinearCongruential instance

// @ 0x00b93750
void FUN_00b93750(int count, int param_2)
{
    if (count <= 0)
        return;
    do {
        int n = FUN_00c710c0(param_2);
        int r = EA_Random_RandomUint32Uniform(_sMathRandom, n);
        int arr = FUN_00c71030(param_2, r);
        if ((*(int*)(arr + 0x40) - *(int*)(arr + 0x3c)) & 0xfffffffc) {
            int local[3];
            FUN_00b935e0(local, param_2, arr);
            if (local[0] != 0 && local[1] != 0) {
                int n2 = (*(int*)(local[1] + 0x40) - *(int*)(local[1] + 0x3c)) >> 2;
                bool found = false;
                for (int i = 0; i < n2 && !found; ++i) {
                    if (*(int*)(*(int*)(local[1] + 0x3c) + i * 4) == local[0]) {
                        ((ThiscallStub*)(void*)(long)arr)->FUN_00ff2d50(i, arr);
                        found = true;
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
void Weighted::FUN_00b93870(int, int, int)
{
    int* self = (int*)this;
    int idx = msvcr90_rand() % *(int*)((char*)self + 0x30);
    unsigned count = (unsigned)((*(int*)((char*)self + 0xc) - *(int*)((char*)self + 8)) >> 2);
    if (count != 0) {
        int* w = *(int**)((char*)self + 8);
        unsigned i = 0;
        do {
            idx -= *w;
            if (idx < 0) {
                int el = *(int*)(*(int*)((char*)self + 0x1c) + i * 4);
                return ((void(__fastcall*)(void*))(*(void***)el)[0x10 / 4])((void*)el);
            }
            ++i;
            ++w;
        } while (i < count);
    }
}

// ---------------------------------------------------------------------------
// 0x00b938d0 -- read a float3 property or use a fallback float3.
// ---------------------------------------------------------------------------
struct Float3 {
    float x, y, z;
};

// @ 0x00b938d0
float* FUN_00b938d0(float* out, int* prop, float fx, float fy, float fz)
{
    if (prop != 0) {
        int got = 0;
        char ok = ((char(__fastcall*)(void*, int*))(*(void***)prop)[0x24 / 4])(prop, &got);
        if (ok != 0) {
            int p = got;
            u16 type = *(u16*)((char*)p + 0x12);
            float* src;
            if (type == 0x31 || type == 0x10) {
                if ((*(u8*)((char*)p + 0x10) & 0x30) != 0)
                    src = (float*)p;
                else
                    src = (float*)((type != 0) ? (u32)p : 0u);
            } else {
                src = (float*)FUN_006bb5e0();
            }
            out[0] = src[0];
            out[1] = src[1];
            out[2] = src[2];
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
    int  FUN_00b93980(int buckets);      // 0x00b93980 allocate
    void FUN_00b939f0(int buckets);
};

// @ 0x00b939f0
void BucketArray::FUN_00b939f0(int param_2)
{
    int* self = (int*)this;
    int* buckets = (int*)((BucketArray*)self)->FUN_00b93980(param_2);
    for (unsigned int i = 0; i < (u32)self[2]; ++i) {
        int* p = *(int**)(self[1] + i * 4);
        while (p != 0) {
            unsigned int v = (unsigned int)p[0];
            *(int*)(self[1] + i * 4) = p[0x10];
            p[0x10] = *(int*)((char*)buckets + (v % (unsigned)param_2) * 4);
            *(int**)((char*)buckets + (v % (unsigned)param_2) * 4) = p;
            p = *(int**)(self[1] + i * 4);
        }
    }
    int* old = (int*)self[1];
    if ((u32)self[2] > 1 && old != (int*)self[0x30 / 4]) {
        if (old >= (int*)self[0x24 / 4] && old < (int*)self[0x28 / 4]) {
            *old = self[0x1c / 4];
            self[0x1c / 4] = (int)old;
            self[1] = (int)buckets;
            self[2] = param_2;
            return;
        }
        FUN_00f47380(old);
    }
    self[1] = (int)buckets;
    self[2] = param_2;
}

// ---------------------------------------------------------------------------
// 0x00b93a90 -- sift-down helper over reference-counted elements.
// ---------------------------------------------------------------------------
struct RefElem {
    int refcntInc();       // +0xbc
    int refcntDec();       // +0xc0
};

// @ 0x00b93a90
void FUN_00b93a90(int* arr, int count, int start, int end)
{
    int i = start;
    int* p = arr + i;
    for (;;) {
        int j = i * 2 + 2;
        if (j >= end)
            break;
        if (FUN_00ac0730(*(int*)((char*)arr + j * 4), *(int*)((char*)arr + j * 4 - 4)))
            --j;
        int* a = *(int**)((char*)arr + i * 4);
        int* b = *(int**)((char*)arr + j * 4);
        if (b != a) {
            if (b != 0)
                ((void(__fastcall*)(void*))(*(void***)b)[0xbc / 4])(b);
            *(int**)((char*)arr + i * 4) = b;
            if (a != 0)
                ((void(__fastcall*)(void*))(*(void***)a)[0xc0 / 4])(a);
        }
        i = j;
        if (i * 2 + 2 >= end)
            break;
    }
    if (i * 2 + 2 == end) {
        int j = i * 2 + 1;
        int* a = *(int**)((char*)arr + i * 4);
        int* b = *(int**)((char*)arr + j * 4);
        if (b != a) {
            if (b != 0)
                ((void(__fastcall*)(void*))(*(void***)b)[0xbc / 4])(b);
            *(int**)((char*)arr + i * 4) = b;
            if (a != 0)
                ((void(__fastcall*)(void*))(*(void***)a)[0xc0 / 4])(a);
        }
    }
    FUN_00b90b10(arr, count, i, 0);
    if (p != 0) { (void)p; }
}

// ---------------------------------------------------------------------------
// 0x00b93ba0 -- find the first array element with no closest water.
// ---------------------------------------------------------------------------
struct VecObj {
    float* GetPosition(float range, float* out);   // vtable +0x2c of the +0x34 subobject
};

// @ 0x00b93ba0
int* FUN_00b93ba0(int* begin, int* end)
{
    int* p = begin;
    while (p != end) {
        int obj = *p;
        float out[3];
        // vtable at *(obj) + 0x34, then slot 0x2c; ecx = obj + 0x34.
        void* sub = (void*)(obj + 0x34);
        float range = 70.0f;   // 0x428c0000
        void* model = (void*)(*(int(__fastcall*)(void*, float, float*))(*(void***)sub)[0x2c / 4])(sub, range, out);
        void* pm = SP_PlanetModel(0, model);
        char c = SP_cPlanetModel_FindClosestWater(pm, range, out);
        (void)c;
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
    if (begin == end)
        return out;
    do {
        int obj = *begin;
        float tmp[3];
        void* sub = (void*)(obj + 0x34);
        float range = 70.0f;
        void* model = (void*)(*(int(__fastcall*)(void*, float, float*))(*(void***)sub)[0x2c / 4])(sub, range, tmp);
        void* pm = SP_PlanetModel(0, model);
        char c = SP_cPlanetModel_FindClosestWater(pm, range, tmp);
        (void)c;
        if (c != 0) {
            *out = *begin;
            ++out;
        }
        ++begin;
    } while (begin != end);
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b93cc0 -- move a reference into slot[-1] then re-heapify.
// ---------------------------------------------------------------------------
// @ 0x00b93cc0
void FUN_00b93cc0(int* arr, int* slot, float fx, float fy, float fz)
{
    int* old = (int*)*(slot - 1);
    if (old != 0)
        ((void(__fastcall*)(void*))(*(void***)old)[0xbc / 4])(old);
    int* nw = (int*)*arr;
    int* prev = (int*)*(slot - 1);
    if (nw != prev) {
        if (nw != 0)
            ((void(__fastcall*)(void*))(*(void***)nw)[0xbc / 4])(nw);
        *(slot - 1) = (int)nw;
        if (prev != 0)
            ((void(__fastcall*)(void*))(*(void***)prev)[0xc0 / 4])(prev);
    }
    if (old != 0)
        ((void(__fastcall*)(void*))(*(void***)old)[0xbc / 4])(old);
    int count = ((int)slot - (int)arr) >> 2;
    (void)fx; (void)fy; (void)fz;
    FUN_00b90b10(arr, 0, count - 1, 0);
    if (old != 0)
        ((void(__fastcall*)(void*))(*(void***)old)[0xc0 / 4])(old);
}

// ---------------------------------------------------------------------------
// 0x00b93dc0 -- property-driven macro-stage value getter.
// ---------------------------------------------------------------------------
// @ 0x00b93dc0
int GameEditStrategy::FUN_00b93dc0(int mode)
{
    int* self = (int*)this;
    float value;
    if (mode == 0 || mode == 2)
        value = 48.5f;       // 0x42420000
    else
        value = 65.591f;     // 0x42832560
    int slot = 0;
    void* pm = SP_PropertyManager();
    int key = 0x2e4b4cc;
    char ok = ((char(__fastcall*)(void*, int, int, int*))(*(void***)pm)[0x2c / 4])(
        pm, key, (int)(long)self, &slot);
    if (ok == 0) {
        if (slot != 0)
            ((void(__fastcall*)(void*))(*(void***)slot)[1 / 4])((void*)slot);
        return (int)(long)&value - (int)(long)&value + value;
    }
    int sub = SP_GetPropertyAsKey((int)(long)self, 0x44449ba, &slot);
    (void)sub;
    return (int)(long)&value - (int)(long)&value + value;
}

// ---------------------------------------------------------------------------
// 0x00b93f40 -- create a scenario noun and initialise its fields.
// ---------------------------------------------------------------------------
struct ScenarioObj {
    int   mF108;        // +0x108
    int   mF10c;        // +0x10c
    int   mF110;        // +0x110
    int   mF114;        // +0x114
    float mF11c;        // +0x11c
    float mF120;        // +0x120
    float mF124;        // +0x124
    int   mF128;        // +0x128
    float mF12c;        // +0x12c
    float mF130;        // +0x130
    float mF134;        // +0x134
    float mF138;        // +0x138
    int   mF13c;        // +0x13c
    int   mF140;        // +0x140
    void* mSub34;       // +0x34 first field of the embedded orientation object
    void CreateScenario(int type);
};

extern int DAT_0168894c_dummy;

// @ 0x00b93f40
void FUN_00b93f40(int param_1, int param_2, int param_3, int param_4)
{
    int obj = *(int*)(param_1 + 0x43c);
    u8 useDefault = 0;
    if (obj != 0) {
        int got = 0;
        char ok = ((char(__fastcall*)(void*, int, int*))(*(void***)obj)[0x24 / 4])((void*)obj, 0xa8f33541, &got);
        if (ok != 0) {
            int p = got;
            u16 type = *(u16*)((char*)p + 0x12);
            if (type == 1 || type == 0x10) {
                if ((*(u8*)((char*)p + 0x10) & 0x30) != 0)
                    useDefault = *(u8*)(*(int*)p);
                else
                    useDefault = *(u8*)((type != 0) ? (u32)p : 0u);
            } else {
                useDefault = *(u8*)0x15d9c70;
            }
        }
    }
    ThiscallStub* nm = (ThiscallStub*)SP_NounManager();
    int noun = ((ThiscallStub*)nm)->FUN_00b21000(0x36be27e, 0);
    (void)noun;
    ScenarioObj* s = (ScenarioObj*)noun;
    (void)useDefault;
    (void)s;
}

// ---------------------------------------------------------------------------
// 0x00b94090 -- build a scenario noun from type/id and optionally load it.
// ---------------------------------------------------------------------------
// @ 0x00b94090
int FUN_00b94090(void* arg1, void* arg2, int arg3, int* arg4, char arg5)
{
    ThiscallStub* nm = (ThiscallStub*)SP_NounManager();
    int noun = ((ThiscallStub*)nm)->FUN_00b20c60(0x36be27e);
    int s = 0;
    if (noun != 0)
        s = ((int(__fastcall*)(void*, int))(*(void***)noun)[0xc / 4])((void*)noun, 0x36be278);

    void* sub = (void*)(s + 0x34);
    *(int*)(s + 0x108) = 0;
    *(int*)(s + 0x114) = 0;
    *(int*)(s + 0x10c) = arg3;
    *(int*)(s + 0x110) = (int)arg4;
    ((void(__fastcall*)(void*, void*))(*(void***)sub)[0x38 / 4])(sub, arg1);
    ((void(__fastcall*)(void*, void*))(*(void***)sub)[0x3c / 4])(sub, arg2);

    if (arg3 == 0x1be418e)
        *(int*)(s + 0x108) = 0x91fe517b;
    else if (arg3 == 0x36be27e)
        *(int*)(s + 0x108) = (int)arg4;

    char r = 0;
    if (arg5 != 0) {
        if (((GameEditStrategy*)s)->FUN_00b931c0(-1, -1) != 0)
            r = 1;
    }
    if (arg4 != 0)
        *arg4 = s;
    return r;
}

