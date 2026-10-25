// Slice s006f43e0: Graphics/image-resource dispatch helpers, intrusive-pointer copy loops,
// camera/lighting distance queries and a Graphics-hashtable destructor.
// Region 0x6f43e0-0x6f54a0. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>
#include <math.h>

extern "C" void* memmove(void* dst, const void* src, unsigned int n);

// ---- external callees -------------------------------------------------------------------
void* __cdecl FUN_0067dd60();          // graphics manager (vfn +8: make resource)
void* __cdecl FUN_0067dd40();          // graphics manager (raster helpers)
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void  __cdecl FUN_007c40f0(void* a, void* b);      // 0x007c40f0
char  __cdecl FUN_006ddcc0(int a, int b, void* c, void* d);
void  __cdecl FUN_006ddd10(int a, void* b);
void  __cdecl FUN_00921440(void* out, unsigned a, unsigned b, int c);
void* __cdecl FUN_011f1120();
void* __cdecl operator_new_graphics(unsigned n, const char* name, int a, int b,
                                    const char* file, int line);

extern "C" void* SP_App();                              // 0x0067dd10 SP::App
extern "C" void* SP_LightingManager();                  // 0x0067dd90 SP::LightingManager
extern "C" void  cSPMatrix3_Assign(void* self, const void* src);   // 0x0041cb40
extern "C" unsigned SP_ColorRGBAToU32(float* rgba);     // 0x004580c0

// Camera / lighting position vectors written by the App light query.
extern float g_16194f8;   // 0x16194f8  camera position x
extern float g_16194fc;   // 0x16194fc  camera position y
extern float g_1619500;   // 0x1619500  camera position z
extern float g_1619638[9]; // 0x1619638  Matrix33 data (row-major, 9 floats)

// Numeric constants read as floats (some hold small integer bit patterns).
extern float g_1485720;   // 0x1485720  _HK_REAL_ONE = 1.0f
extern float g_13ec4b8;   // 0x13ec4b8  1e-08f
extern float g_1471064;   // 0x1471064  0.5f
extern float g_1486374;   // 0x1486374  0.8f
extern float g_13eecd8;   // 0x13eecd8  20.0f
extern float g_13ef580;   // 0x13ef580  0.02f
extern float g_13f56a4;   // 0x13f56a4  1.15f
extern float g_13ef74c;   // 0x13ef74c  0.15f
extern float g_13eecd4;   // 0x13eecd4  0.003921569f
extern float g_1470f1c;   // 0x1470f1c  2.0f
extern float g_13eb1bc;   // 0x13eb1bc  -1.0f
extern float g_16077c4;   // 0x16077c4  (small int bit pattern, treated as float)
extern float g_16077c8;   // 0x16077c8  (small int bit pattern, treated as float)

// render-state globals touched by the CompiledState setup
extern "C" unsigned g_16f9230;    // 0x16f9230
extern "C" unsigned g_16f922c;    // 0x16f922c
extern "C" unsigned g_16f9218;    // 0x16f9218
extern "C" unsigned g_16f9200;    // 0x16f9200
extern "C" unsigned g_16f923c;    // 0x16f923c
extern "C" unsigned g_16fa38c;    // 0x16fa38c  render-state dirty flags

static inline void** Vt(void* p) { return *(void***)p; }
static inline void* CallSlot0(void* p, int slot) {
    return ((void* (__thiscall*)(void*))Vt(p)[slot])(p);
}

struct cImageHost {
    void GetImageResource(void* r);      // 0x576650
};

// ---- eastl containers touched by the 0x6f51b0 owner destructor --------------------------
struct VecBase {
    void*  mpBegin;        // +0x00
    void*  mpEnd;          // +0x04
    void*  mpCapacityEnd;  // +0x08
    void*  mnSize;         // +0x0c
    void DestroyRange(void** first, void** last);   // 0x0070f520
};

struct HashtableHead {
    char     mHead[4];        // +0x00
    void**   mpBucketArray;   // +0x04
    unsigned mnBucketCount;   // +0x08
    unsigned mnElementCount;  // +0x0c
};
struct WideHashtable : HashtableHead {
    void DoFreeNodes(void** array, unsigned count);   // 0x00693230
};
struct ResourceHashtable : HashtableHead {
    void DoFreeNodes(void** array, unsigned count);   // 0x007611f0
};

// @ 0x006f44c0
bool __stdcall FUN_006f44c0(void* a, void* b, cImageHost* host) {
    void* mgr = FUN_0067dd60();
    int r = (*(int (__thiscall**)(void*, void*, void*, int))(Vt(mgr) + 8))(mgr, a, b, 0);
    if (r != 0) {
        host->GetImageResource((void*)r);
        return true;
    }
    return false;
}

// @ 0x006f4500
bool __stdcall FUN_006f4500(unsigned int id, void* unused, cImageHost* host) {
    (void)unused;
    if (id == 0x0F19D8D5) {
        void* mgr = FUN_0067dd40();
        void* r = CallSlot0(mgr, 30);
        host->GetImageResource(r);
        return true;
    }
    if (id == 0xFD9802C7) {
        void* mgr = FUN_0067dd40();
        void* r = CallSlot0(mgr, 31);
        host->GetImageResource(r);
        return true;
    }
    if (id == 0x9B304161) {
        void* mgr = FUN_0067dd40();
        void* r = CallSlot0(mgr, 29);
        host->GetImageResource(r);
        return true;
    }
    return false;
}

// intrusive_ptr copy + release helpers
static void AddRef(void* p) { _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1); }
static void Release(void* p) {
    volatile long* rc = (volatile long*)((char*)p + 8);
    _InterlockedExchangeAdd(rc, -1);
    long c = _InterlockedExchangeAdd(rc, 0);
    if (c < 1) _InterlockedExchangeAdd(rc, 1);
}
// @ 0x006f43e0
void FUN_006f43e0(void** first, void** last, void** dest) {
    for (; first != last; ++first, ++dest) {
        void* s = *first;
        void* d = *dest;
        if (s != d) {
            if (s) AddRef(s);
            *dest = s;
            if (d) Release(d);
        }
    }
}

// @ 0x006f4450
void** FUN_006f4450(void** first, void** last, void** destEnd) {
    while (last != first) {
        void* s = *--last;
        void* d = *--destEnd;
        if (s != d) {
            if (s) AddRef(s);
            *destEnd = s;
            if (d) Release(d);
        }
    }
    return destEnd;
}

// @ 0x006f51b0
void __fastcall FUN_006f51b0(char* self) {
    VecBase* vec = (VecBase*)(self + 0x78);
    vec->DestroyRange((void**)vec->mpBegin, (void**)vec->mpEnd);
    void* p = vec->mpBegin;
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = *(void**)(self + 0x60);
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = *(void**)(self + 0x4c);
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    ResourceHashtable* res = (ResourceHashtable*)(self + 0x2c);
    res->DoFreeNodes(res->mpBucketArray, res->mnBucketCount);
    res->mnElementCount = 0;
    if (res->mnBucketCount > 1) EASTL_allocator_deallocate((void*)res->mpBucketArray);
    WideHashtable* wide = (WideHashtable*)(self + 0xc);
    wide->DoFreeNodes(wide->mpBucketArray, wide->mnBucketCount);
    wide->mnElementCount = 0;
    if (wide->mnBucketCount > 1) EASTL_allocator_deallocate((void*)wide->mpBucketArray);
}

// ------------------------------------------------------------------------------------------
// Camera helpers.  Each builds the same App camera/light position triple into a local, then
// runs the caller-specific math.  A 3-float local pair (`pos`, `light`) plus a 4-float
// scratch; the Matrix33 local is filled from g_1619638 by cSPMatrix3::Assign and then copied.
// ------------------------------------------------------------------------------------------
struct CamVec { float x, y, z; float w; };   // 4 floats; w doubles as the homogeneous term

// Fills `pos` from the App light query and `light` from the lighting manager.
static void Camera_FetchPositions(CamVec* pos, float* light) {
    pos->x = g_16194f8;
    pos->y = g_16194fc;
    pos->z = g_1619500;
    pos->w = 0.0f;

    float mat[9];
    cSPMatrix3_Assign(mat, g_1619638);
    for (int i = 0; i < 9; ++i) mat[i] = g_1619638[i];

    pos->x = g_16194f8;
    pos->y = g_16194fc;
    pos->z = g_1619500;
    pos->w = g_1485720;

    void* app = SP_App();
    void* a2 = CallSlot0(app, 0x50 / 4);
    (*(void (__thiscall**)(void*, CamVec*))(Vt(a2)[0x1c / 4]))(a2, pos);
    FUN_007c40f0(pos, 0);

    void* lm = SP_LightingManager();
    (*(void (__thiscall**)(void*, float*))(Vt(lm)[0x24 / 4]))(lm, light);
}

// @ 0x006f4580
float FUN_006f4580() {
    CamVec pos;
    float light[3];
    Camera_FetchPositions(&pos, light);

    float len = sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + g_13ec4b8);
    float inv = 1.0f / len;

    float nx = pos.x * inv;
    float ny = pos.y * inv;
    float nz = pos.z * inv;

    return 1.0f - ((nx * light[0] + nz * light[2] + ny * light[1]) + 1.0f) * g_1471064;
}

// @ 0x006f46f0
// Distance-based LOD scale: compares camera position with the cached point at +0x194.
float __fastcall FUN_006f46f0(char* self) {
    CamVec pos;
    float light[3];
    Camera_FetchPositions(&pos, light);

    float dx = pos.x - *(float*)(self + 0x194);
    float dy = pos.y - *(float*)(self + 0x198);
    float dz = pos.z - *(float*)(self + 0x19c);
    float dist = fabsf(sqrtf(dx * dx + dy * dy + dz * dz));

    float cachedRadius = *(float*)(self + 0x1a0);

    float scale = (dist <= cachedRadius) ? 1.0f : g_1486374;

    float camLen = fabsf(sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) -
                         sqrtf(*(float*)(self + 0x194) * *(float*)(self + 0x194) +
                               *(float*)(self + 0x198) * *(float*)(self + 0x198) +
                               *(float*)(self + 0x19c) * *(float*)(self + 0x19c)) + dist);
    float v = (camLen - cachedRadius) * scale + cachedRadius;

    float result;
    if (g_13eecd8 <= v)
        result = g_13f56a4 - v * g_13ef580;
    else
        result = 1.0f;

    if (result < g_13ef74c) result = g_13ef74c;
    if (result > 1.0f) result = 1.0f;

    *(float*)(self + 0x194) = pos.x;
    *(float*)(self + 0x198) = pos.y;
    *(float*)(self + 0x19c) = pos.z;
    *(float*)(self + 0x1a0) = dist;
    return result;
}

// @ 0x006f4930
float FUN_006f4930() {
    CamVec pos;
    float light[3];
    Camera_FetchPositions(&pos, light);
    return sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
}

// @ 0x006f4a10
void __fastcall FUN_006f4a10(char* self, float* point, int extra, char enabled) {
    if (enabled) {
        CamVec pos;
        float light[3];
        Camera_FetchPositions(&pos, light);

        float dx = pos.x - point[0];
        float dy = pos.y - point[1];
        float dz = pos.z - point[2];
        float v = sqrtf(dx * dx + dy * dy + dz * dz) / *(float*)(self + 0x150);
        *(float*)(self + 0x1a8) = v;
        if (v > 1.0f)
            *(float*)(self + 0x1a8) = g_1485720;
        *(float*)(self + 0x1ac) = 0.0f;
        *(float*)(self + 0x1b0) = *(float*)&extra;
    }
    *(char*)(self + 0x1a4) = enabled;
}

// @ 0x006f4b90
void __fastcall FUN_006f4b90(char* self, void* state, unsigned a, float b, float c,
                             float d, float e) {
    unsigned save16f9230 = g_16f9230;
    unsigned save16f922c = g_16f922c;
    unsigned save16f9218 = g_16f9218;
    unsigned save16f9200 = g_16f9200;
    bool prevNotFour = (g_16f923c != 4);

    g_16fa38c |= 2;
    g_16f9200 = 3;
    ((void (__thiscall*)(void*))0x11ee580)(state);      // rw::graphics::CompiledState::Dispatch
    g_16fa38c |= 0x10080;
    g_16f923c = 8;
    g_16f9218 = 0;

    void* p1 = FUN_011f1120();
    unsigned short w = *(unsigned short*)(*(int*)((char*)p1 + 0x40) + 0xc);
    void* p2 = FUN_011f1120();
    unsigned short h = *(unsigned short*)(*(int*)((char*)p2 + 0x40) + 0xe);

    float local14[4];
    char ok = FUN_006ddcc0(2, 4, state, local14);
    if (ok != 0) {
        float fi = (float)w;
        float saved = g_16077c8;
        float m = g_16077c4;
        float col[4];
        struct Mat { unsigned d[0x60 / 4]; };
        Mat* base = (Mat*)state;

        *(float*)&base->d[0x00 / 4] = -1.0f - (m * g_1470f1c) / fi;
        *(float*)&base->d[0x04 / 4] = 0.0f;
        *(float*)&base->d[0x08 / 4] = -1.0f - (saved * g_1470f1c) / (float)h;
        *(float*)&base->d[0x18 / 4] = 1.0f - (g_16077c4 * g_1470f1c) / fi;
        *(float*)&base->d[0x1c / 4] = 0.0f;
        *(float*)&base->d[0x20 / 4] = 1.0f - (g_16077c8 * g_1470f1c) / (float)h;
        *(float*)&base->d[0x30 / 4] = -1.0f - (g_16077c4 * g_1470f1c) / fi;
        *(float*)&base->d[0x34 / 4] = 0.0f;
        *(float*)&base->d[0x38 / 4] = -1.0f - (g_16077c8 * g_1470f1c) / (float)h;
        *(float*)&base->d[0x48 / 4] = 1.0f - (g_16077c4 * g_1470f1c) / fi;
        *(float*)&base->d[0x4c / 4] = 0.0f;
        *(float*)&base->d[0x50 / 4] = 1.0f - (g_16077c8 * g_1470f1c) / (float)h;

        *(float*)&base->d[0x0c / 4] = 1.0f;
        *(float*)&base->d[0x10 / 4] = 0.0f;
        *(float*)&base->d[0x14 / 4] = 1.0f;
        *(float*)&base->d[0x24 / 4] = 1.0f;
        *(float*)&base->d[0x28 / 4] = 1.0f;
        *(float*)&base->d[0x2c / 4] = 1.0f;
        *(float*)&base->d[0x3c / 4] = 1.0f;
        *(float*)&base->d[0x40 / 4] = 1.0f;
        *(float*)&base->d[0x44 / 4] = 1.0f;
        *(float*)&base->d[0x54 / 4] = 0.0f;
        *(float*)&base->d[0x58 / 4] = 1.0f;
        *(float*)&base->d[0x5c / 4] = 1.0f;

        col[0] = b * g_13eecd4;
        col[1] = c * g_13eecd4;
        col[2] = d * g_13eecd4;
        col[3] = e * g_13eecd4;
        unsigned packed = SP_ColorRGBAToU32(col);
        base->d[0x00 / 4] = packed;   // placeholder overwritten below by rgba store
        // The original writes the packed colour to 0x00,0x24,0x3c,0x54 of the state block.
        base->d[0x00 / 4] = packed;
        base->d[0x24 / 4] = packed;
        base->d[0x3c / 4] = packed;
        base->d[0x54 / 4] = packed;
        (void)local14;
        FUN_006ddd10(3, *(void**)(self + 0x224));
    }

    g_16f9230 = save16f9230;
    g_16f922c = save16f922c;
    g_16fa38c |= 0x13082;
    g_16f923c = (unsigned)prevNotFour * 4 + 4;
    g_16f9218 = save16f9218;
    g_16f9200 = save16f9200;
}

// @ 0x006f4ff0
// Hashtable insert: key at param_3 (a 16-bit tag), out-iterator at param_2.
void __fastcall FUN_006f4ff0(char* self, void** out, unsigned short* key) {
    unsigned short k = *key;
    unsigned mod = *(unsigned*)(self + 8);
    unsigned idx = (unsigned)k % mod;
    unsigned* bucket = (unsigned*)(*(int*)(self + 4) + idx * 4);
    unsigned node = *bucket;

    while (node != 0) {
        if (k == *(unsigned short*)node) {
            *out = (void*)node;
            *((unsigned char*)out + 8) = 0;
            out[1] = bucket;
            return;
        }
        node = *(unsigned*)(node + 8);
    }

    char local8[4];
    unsigned local4;
    FUN_00921440(local8, *(unsigned*)(self + 8), *(unsigned*)(self + 0xc), 1);

    unsigned* fresh = (unsigned*)operator_new_graphics(0xc, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (fresh) {
        fresh[0] = *(unsigned*)key;
        fresh[1] = *(unsigned*)(key + 1);
    }
    fresh[2] = 0;
    (void)local4;

    unsigned* link = (unsigned*)(*(int*)(self + 4) + idx * 4);
    fresh[2] = *link;
    *link = (unsigned)fresh;
    ++*(unsigned*)(self + 0xc);

    *out = fresh;
    *((unsigned char*)out + 8) = 1;
    out[1] = link;
}

// @ 0x006f5260
// Physics-world viewer spawn: allocate a 0x174 cViewer, init, copy, pick a raster, clear.
void __fastcall FUN_006f5260(char* self, unsigned a2, int a3, unsigned a4, void** params) {
    void* raw = operator_new_graphics(0x174, "Graphics", 0, 0, 0, 0);
    void* viewer;
    if (raw == 0)
        viewer = 0;
    else
        viewer = ((void* (__thiscall*)(void*))0x7c3f70)(raw);   // cViewer::cViewer

    ((bool (__thiscall*)(void*, bool))0x7c4dd0)(viewer, false);  // cViewer::Init
    ((bool (__thiscall*)(void*, void*, bool, bool))0x7c50b0)(viewer, *params, false, false); // Copy

    int local1c = -1;
    unsigned local18 = 0xffffffff;
    unsigned char kind = (unsigned char)a4;

    if (kind == 1) {
        void* mgr = FUN_0067dd40();
        if (((char (__thiscall*)(void*))Vt(mgr)[0x38 / 4])(mgr) != 0) {
            void* mgr2 = FUN_0067dd40();
            void* raster;
            ((void (__thiscall*)(void*, void*))Vt(mgr2)[0xdc / 4])(mgr2, &raster);
            ((void (__thiscall*)(void*, void*, bool))0x7c4be0)(viewer, &raster, true);
        }
    } else if ((unsigned char)(kind - 2) < 4) {
        void* mgr = FUN_0067dd40();
        ((void (__thiscall*)(void*, int, void*, bool))Vt(mgr)[0xa8 / 4])(mgr, kind - 2, &local1c, true);
        ((void (__thiscall*)(void*, void*, bool))0x7c4be0)(viewer, &local1c, true);
    } else {
        unsigned k = (unsigned)a4 & 0xff;
        void* it = ((void* (__thiscall*)(void*, unsigned*))0x892970)(self + 0xc, &k);
        unsigned nodeFirst = *(unsigned*)it;
        unsigned bucketArr = *(unsigned*)(self + 4);
        unsigned bucket = *(unsigned*)(self + 8);
        if (nodeFirst == *(unsigned*)(bucketArr + bucket * 4))
            goto after_first;
        {
            unsigned row = *(unsigned*)(nodeFirst + 4);
            int* arr = *(int**)(self + 0x4c);
            ((void (__thiscall*)(void*, int*, bool))0x7c4be0)(viewer, arr + row * 2, true);
        }
    }
after_first:
    ((void (__thiscall*)(void*, unsigned))0x7c3c50)(viewer, 7);   // cViewer::Clear

    local18 = 0xffffffff;
    local1c = -1;
    if (a2 == 0 && a3 == 0) {
        if (*(unsigned short*)(self + 8) == 0xffff)
            goto after_second;
        ((void (__thiscall*)(void*, int*, bool))0x7c4be0)(viewer, &local1c, true);
    } else {
        if ((a3 - 1 + (unsigned)(a2 > 1) == 0) && (a2 - 2 < 4)) {
            void* mgr = FUN_0067dd40();
            ((void (__thiscall*)(void*, int, void*, bool))Vt(mgr)[0xa8 / 4])(mgr,
                (int)((unsigned short)a2) - 2, &local1c, true);
            goto after_second;
        }
        unsigned k = a2 & 0xffff;
        void* it = ((void* (__thiscall*)(void*, unsigned*))0x892970)(self + 0xc, &k);
        unsigned nodeFirst = *(unsigned*)it;
        unsigned bucketArr = *(unsigned*)(self + 4);
        unsigned bucket = *(unsigned*)(self + 8);
        if (nodeFirst == *(unsigned*)(bucketArr + bucket * 4))
            goto after_second;
        unsigned row = *(unsigned*)(nodeFirst + 4);
        local1c = *(int*)(*(int*)(self + 0x4c) + row * 8);
        local18 = *(unsigned*)(*(int*)(self + 0x4c) + 4 + row * 8);
    }
after_second:
    if (local1c != -1) {
        ((void (__thiscall*)(void*, void*, bool))0x7c4be0)(viewer, &local1c, true);
        ((void (__thiscall*)(void*, unsigned))0x7c3c50)(viewer, 7);
    }
    ((void (__thiscall*)(void*))0x7c3ba0)(viewer);
    if (viewer != 0) {
        ((void (__thiscall*)(void*))0x7c4000)(viewer);
        EASTL_allocator_deallocate(viewer);
    }
}
