// Slice s00f927c0 -- SPTerrain/SPTerrainMapSet.obj + SPTerrain/SPTerrainResourceManager.obj.
// SP::cTerrainMapSet (refcounted terrain-map holder) plus cTerrainResourceManager helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>
#include <math.h>

void* __cdecl EAAllocate(unsigned int size, const char* name, int, int, int, int);  // 0x00f473a0
void __cdecl op_delete(void*);                                                       // 0x00f47380

// ---- refcount base --------------------------------------------------------------------------------
struct GmeRefCount {
    GmeRefCount() : mRefCount(0) {}
    virtual ~GmeRefCount() {}
    void AddRef() { ++mRefCount; }
    void Release() {
        int m = mRefCount;
        mRefCount = m - 1;
        if (m - 1 == 0) {
            mRefCount = 1;
            delete this;
        }
    }
    int mRefCount;                                          // +0x04
};

// ---- terrain map (cTerrainMap<unsigned short>) ----------------------------------------------------
struct CubeUV { float u; float v; int face; };

struct cTerrainMapBase : GmeRefCount {
    unsigned int  mFaceSize;                                // +0x08
    unsigned int  mModCount;                                // +0x0c
};

struct cTerrainMapU16 : cTerrainMapBase {
    unsigned short* mBegin;                                 // +0x10
    float GetFloat(const CubeUV*);                          // 0x00f8d620
    void  GetVector4(float*, const CubeUV*);                // 0x00f89e50
};

// ---- height ranges --------------------------------------------------------------------------------
struct cHeightRanges {
    cHeightRanges();                                        // 0x00f92540
    ~cHeightRanges() { op_delete(mCells); mCells = 0; }
    unsigned short* At(int, int, int, int);                 // 0x00f63da0
    int mField00;                                           // +0x00
    int mField04;                                           // +0x04
    int mField08;                                           // +0x08
    int mField0C;                                           // +0x0c
    int mField10;                                           // +0x10
    int mField14;                                           // +0x14
    unsigned short* mCells;                                 // +0x18
};

// ---- vector3 / globals ----------------------------------------------------------------------------
struct cSPVector3 { float x, y, z; };

extern cSPVector3 g_defNormal;                              // 0x016c9c08
extern cSPVector3 g_n;                                      // 0x015b0fa4
extern const unsigned char g_scatter[];                     // 0x01491464

// ---- terrain rect helper (the `this` of 00f92e30 / 00f92ff0) --------------------------------------
struct TerrainRect {
    int m0;                                                 // +0x00
    int m1;                                                 // +0x04
    int m2;                                                 // +0x08
    int m3;                                                 // +0x0c
    int m4;                                                 // +0x10
    int m5;                                                 // +0x14
    unsigned int* m6;                                       // +0x18

    void Build(cTerrainMapU16*, int, int, int, int, int);   // 0x00f92e30
    void Set(cTerrainMapU16*, int, const float*);           // 0x00f92ff0
    void Fill(int, int, int, int, int, int);                // 0x00f925b0
};

// ---- SP::cTerrainMapSet ---------------------------------------------------------------------------
struct cTerrainMapSet : GmeRefCount {
    cTerrainMapSet();                                       // 0x00f92a50
    virtual ~cTerrainMapSet();                              // 0x00f92b10
    float GetHeightAt(const cSPVector3&);                   // 0x00f927c0
    void  GetHeightRange(int, int, int, int, float*, float*);  // 0x00f929c0
    void  ReleaseMaps();                                    // 0x00f92b90
    void  RegisterMap(int, cTerrainMapBase*);               // 0x00f92be0
    void  GetNormalAt(cSPVector3*, const cSPVector3*);      // 0x00f92c20

    cTerrainMapBase* mMaps[11];                             // +0x08
    float mRadius;                                          // +0x34
    float mMaxHeight;                                       // +0x38
    float mWaterHeight;                                     // +0x3c
    float mWaterDelta;                                      // +0x40
    float mBeachHeight;                                     // +0x44
    float mMinCliffGradient;                                // +0x48
    float mMaxCliffGradient;                                // +0x4c
    float mHeightRangeX;                                    // +0x50
    float mHeightRangeY;                                    // +0x54
    cHeightRanges* mHeightRanges;                           // +0x58
};

// ---- generic callee surface (opaque objects; only the call shape matters) --------------------------
struct CObj {
    void  v0();                                             // generic vtbl slot 0
    void  v1();                                             // generic vtbl slot 1
    bool  IsA();                                            // 0x00f699a0
    void  DoB();                                            // 0x00f6bc10
    void  DoC();                                            // 0x00f678a0
    void  DoD(int);                                         // 0x00fc04b0
    void  DoE(int, int, int, int, int);                     // 0x00f9b8c0
    void  DoF();                                            // 0x004535d0
};

struct cTerrainStateMgr {
    cTerrainStateMgr(void*);                                // 0x00fbe130
};

void* __cdecl FUN_00fa23a0();                               // 0x00fa23a0
void* __cdecl FUN_00f48a70();                               // 0x00f48a70
void* __cdecl SP_PropertyManager();                         // 0x0067de30
bool  __cdecl SP_GetPropertyAsVector3(const void*, unsigned int, cSPVector3*);  // 0x006a1110
void  __cdecl TerraBlend(float*, float, float);             // 0x00fc20e0
void  __cdecl SetEffectSeed(unsigned int);                  // 0x007dade0

// ---- cTerrainResourceManager ----------------------------------------------------------------------
struct cTerrainResourceManagerBase {
    virtual ~cTerrainResourceManagerBase() {}
    virtual void v1() {}
};

struct TerrainVec {
    void* mpBegin;                                          // +0x00
    void* mpEnd;                                            // +0x04
    void* mpCapacity;                                       // +0x08
    unsigned int mAlloc[2];                                 // +0x0c
};

struct cTerrainResourceManager : cTerrainResourceManagerBase, GmeRefCount {
    ~cTerrainResourceManager();                             // 0x00f93420
    void  GetVector(float*);                                // 0x00f931f0
    void* Create(void*, int, int, float);                   // 0x00f932f0
    int   GetCount(int);                                    // 0x00f933f0
    bool  GetPlanet(void*, int, int, int, float);           // 0x00f93490
    void* Get(int*);                                        // 0x00f93560

    unsigned int mPad0C;                                    // +0x0c
    TerrainVec   mVec0;                                     // +0x10
    TerrainVec   mVec1;                                     // +0x24
    TerrainVec   mVec2;                                     // +0x38
    TerrainVec   mVec3;                                     // +0x4c
    void*        m60;                                       // +0x60
    void*        m64;                                       // +0x64
};

// ===================================================================================================
// 0x00f927c0  float SP::cTerrainMapSet::GetHeightAt(cSPVector3 const&)
// ===================================================================================================
// @ 0x00f927c0
float cTerrainMapSet::GetHeightAt(const cSPVector3& p)
{
    if (mMaps[0] == 0)
        return mRadius;

    cTerrainMapU16* map = (cTerrainMapU16*)mMaps[0];
    CubeUV uv;

    float x = p.x;
    float y = p.y;
    float z = p.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);

    if (ax <= az && ay <= az) {
        uv.u = (x / z + 1.0f) * 0.5f;
        uv.v = (y / az + 1.0f) * 0.5f;
        if (z < 0.0f) {
            uv.face = 1;
            return map->GetFloat(&uv) * mMaxHeight + mRadius;
        }
        uv.face = 0;
        return map->GetFloat(&uv) * mMaxHeight + mRadius;
    }
    if (ay < ax) {
        uv.u = (y / x + 1.0f) * 0.5f;
        uv.v = (z / ax + 1.0f) * 0.5f;
        uv.face = 2;
        if (x < 0.0f)
            uv.face = 3;
        return map->GetFloat(&uv) * mMaxHeight + mRadius;
    }
    uv.u = (z / y + 1.0f) * 0.5f;
    uv.v = (x / ay + 1.0f) * 0.5f;
    if (y < 0.0f) {
        uv.face = 5;
        return map->GetFloat(&uv) * mMaxHeight + mRadius;
    }
    uv.face = 4;
    return map->GetFloat(&uv) * mMaxHeight + mRadius;
}

// ===================================================================================================
// 0x00f929c0  void SP::cTerrainMapSet::GetHeightRange(int,int,int,int,float*,float*)
// ===================================================================================================
// @ 0x00f929c0
void cTerrainMapSet::GetHeightRange(int a2, int a3, int a4, int a5, float* a6, float* a7)
{
    if (mHeightRanges != 0) {
        int sh = a2 - 4;
        if (sh > 0) {
            a4 >>= sh;
            a2 -= sh;
            a5 >>= sh;
        }
        unsigned short* p = mHeightRanges->At(a2, a3, a4, a5);
        *a6 = (float)(int)(p[0] - 0x8000) * 3.0518509447574615e-05f;
        *a7 = (float)(int)(p[1] - 0x8000) * 3.0518509447574615e-05f;
    } else {
        *a6 = mHeightRangeX;
        *a7 = mHeightRangeY;
    }
}

// ===================================================================================================
// 0x00f92a50  SP::cTerrainMapSet::cTerrainMapSet()
// ===================================================================================================
// @ 0x00f92a50
cTerrainMapSet::cTerrainMapSet()
{
    mMaps[0] = 0;
    mMaps[1] = 0;
    mMaps[2] = 0;
    mMaps[3] = 0;
    mMaps[4] = 0;
    mMaps[5] = 0;
    mMaps[6] = 0;
    mMaps[7] = 0;
    mMaps[8] = 0;
    mMaps[9] = 0;
    mMaps[10] = 0;
    mRadius = 500.0f;
    mMaxHeight = 100.0f;
    mWaterHeight = 0.0f;
    mWaterDelta = 0.0f;
    mBeachHeight = 0.025f;
    mMinCliffGradient = 0.0f;
    mMaxCliffGradient = 0.0f;
    mHeightRangeX = -1.0f;
    mHeightRangeY = 1.0f;
    void* p = EAAllocate(0x1c, "Terrain/TerrainMapSet/cHeightRanges", 0, 0, 0, 0);
    mHeightRanges = p ? new (p) cHeightRanges : 0;
}

// ===================================================================================================
// 0x00f92b10  SP::cTerrainMapSet::~cTerrainMapSet()
// ===================================================================================================
// @ 0x00f92b10
cTerrainMapSet::~cTerrainMapSet()
{
    cHeightRanges* hr = mHeightRanges;
    if (hr != 0) {
        op_delete(hr->mCells);
        hr->mCells = 0;
        op_delete(hr);
    }

    cTerrainMapBase** p = mMaps + 11;
    int n = 10;
    do {
        cTerrainMapBase* q = *--p;
        if (q != 0)
            q->Release();
    } while (--n >= 0);
}

// ===================================================================================================
// 0x00f92b90  void SP::cTerrainMapSet::ReleaseMaps()
// ===================================================================================================
// @ 0x00f92b90
void cTerrainMapSet::ReleaseMaps()
{
    for (int i = 0; i < 11; ++i) {
        cTerrainMapBase* p = mMaps[i];
        if (p != 0) {
            mMaps[i] = 0;
            p->Release();
        }
    }
}

// ===================================================================================================
// 0x00f92be0  void SP::cTerrainMapSet::RegisterMap(int, cTerrainMapBase*)
// ===================================================================================================
// @ 0x00f92be0
void cTerrainMapSet::RegisterMap(int idx, cTerrainMapBase* p)
{
    cTerrainMapBase* old = mMaps[idx];
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mMaps[idx] = p;
        if (old != 0)
            old->Release();
    }
}

// ===================================================================================================
// 0x00f92c20  void SP::cTerrainMapSet::GetNormalAt(cSPVector3*, cSPVector3 const*)
// ===================================================================================================
// @ 0x00f92c20
void cTerrainMapSet::GetNormalAt(cSPVector3* out, const cSPVector3* in)
{
    cTerrainMapU16* map = (cTerrainMapU16*)mMaps[1];
    if (map == 0) {
        out->x = g_defNormal.x;
        out->y = g_defNormal.y;
        out->z = g_defNormal.z;
        return;
    }

    float x = in->x;
    float y = in->y;
    float z = in->z;

    CubeUV uv;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    if (az < ax || az < ay) {
        if (ay < ax) {
            uv.u = (y / x + 1.0f) * 0.5f;
            uv.v = (z / ax + 1.0f) * 0.5f;
            uv.face = 2;
            if (x < 0.0f)
                uv.face = 3;
        } else {
            uv.u = (z / y + 1.0f) * 0.5f;
            uv.v = (x / ay + 1.0f) * 0.5f;
            if (y < 0.0f)
                uv.face = 5;
            else
                uv.face = 4;
        }
    } else {
        uv.u = (x / z + 1.0f) * 0.5f;
        uv.v = (y / az + 1.0f) * 0.5f;
        if (z < 0.0f)
            uv.face = 1;
        else
            uv.face = 0;
    }

    float r[4];
    map->GetVector4(r, &uv);
    out->x = r[0] * 2.0f - g_n.x;
    out->y = r[1] * 2.0f - g_n.y;
    out->z = r[2] * 2.0f - g_n.z;
}

// ===================================================================================================
// 0x00f92e30  void TerrainRect::Build(cTerrainMapU16*, int, int, int, int, int)
// ===================================================================================================
// @ 0x00f92e30
void TerrainRect::Build(cTerrainMapU16* map, int p3, int p4, int p5, int p6, int p7)
{
    int face = map->mFaceSize;
    int g = (face + (face >> 31 & 0xf)) >> 4;
    int r0 = this->m0;
    int r5 = this->m5;
    unsigned int* outBase = this->m6;

    if (p5 < p7) {
        unsigned short* rowp = (unsigned short*)((char*)map->mBegin
            + face * face * p3 * 2 + g * face * p5 * 2);
        int j = p5;
        do {
            if (p4 < p6) {
                unsigned short* src = (unsigned short*)((char*)rowp + g * p4 * 2);
                int i = p4;
                do {
                    int idx = ((((g_scatter[(i >> 4) & 0xf] | g_scatter[(j >> 4) & 0xf] * 2) << 7)
                                | g_scatter[j & 0xf]) * 2) | g_scatter[i & 0xf];
                    unsigned short* cell = (unsigned short*)((char*)outBase + (r0 * p3 + r5) * 4 + idx * 4);
                    unsigned short v = src[0];
                    cell[0] = v;
                    cell[1] = v;
                    if (g > 0) {
                        unsigned short* rp = src;
                        for (int r = g; r != 0; --r) {
                            for (int c = 0; c < g; ++c) {
                                unsigned short u = rp[c];
                                if (u < cell[0]) cell[0] = u;
                                else if (cell[1] < u) cell[1] = u;
                            }
                            rp += face;
                        }
                    }
                    ++i;
                    src += g;
                } while (i < p6);
            }
            rowp += g * face;
            ++j;
        } while (j < p7);
    }

    Fill(3, p3, p4, p5, p6, p7);
}

// ===================================================================================================
// 0x00f92ff0  void TerrainRect::Set(cTerrainMapU16*, int, float const*)
// ===================================================================================================
// @ 0x00f92ff0
void TerrainRect::Set(cTerrainMapU16* map, int a3, const float* v)
{
    float f1 = 0.0f;
    if (0.0f <= v[1]) f1 = v[1];
    if (1.0f <= f1) f1 = 1.0f;

    float f0 = 0.0f;
    if (0.0f <= v[0]) f0 = v[0];
    if (1.0f <= f0) f0 = 1.0f;

    float f3 = 0.0f;
    if (0.0f <= v[3]) f3 = v[3];
    if (1.0f <= f3) f3 = 1.0f;

    float f2 = 0.0f;
    if (0.0f <= v[2]) f2 = v[2];
    if (1.0f <= f2) f2 = 1.0f;

    int i1 = (int)(f0 * 16.0f);
    if (f0 * 16.0f < (float)i1) --i1;
    int i2 = (int)(f1 * 16.0f);
    if (f1 * 16.0f < (float)i2) --i2;
    int i3 = (int)(f2 * 16.0f);
    if ((float)i3 < f2 * 16.0f) ++i3;
    int i4 = (int)(f3 * 16.0f);
    if ((float)i4 < f3 * 16.0f) ++i4;

    Build(map, a3, i1, i2, i3, i4);
}

// ===================================================================================================
// 0x00f93190  bool TerrainMapSetCheck(void*)
// ===================================================================================================
// @ 0x00f93190
bool __stdcall TerrainMapSetCheck(void* p)
{
    if (*(int*)((char*)p + 4) != 0xb1b104)
        return false;
    unsigned int v = *(unsigned int*)((char*)p + 8);
    return (v & 0xff0000) == 0x840000
        && (v & 0x1f000000) == 0
        && (unsigned char)v == 0
        && ((v >> 8) & 0xff) >= 0xa1
        && ((v >> 8) & 0xff) <= 0xb3;
}

// ===================================================================================================
// 0x00f931f0  void cTerrainResourceManager::GetVector(float*)
// ===================================================================================================
// @ 0x00f931f0
void cTerrainResourceManager::GetVector(float* out)
{
    void** vt = *(void***)this;
    void* obj = ((void*(__thiscall*)(void*, float*))vt[1])(this, out);
    if (obj != 0)
        ((CObj*)obj)->v0();

    cSPVector3 a;
    a.x = 0.5f;
    a.y = 0.5f;
    a.z = 0.5f;
    SP_GetPropertyAsVector3(obj, 0x3a23f98, &a);

    float b[4];
    b[0] = a.x;
    b[1] = a.y;
    b[2] = a.z;
    TerraBlend(b, a.z, a.y);

    out[0] = (b[0] + a.x) * 0.5f;
    out[1] = a.x;
    out[2] = a.y;
    out[3] = a.z;

    cSPVector3 c;
    c.x = 32.0f;
    c.y = 32.0f;
    c.z = 500.0f;
    SP_GetPropertyAsVector3(obj, 0x3a23f99, &c);
    out[4] = c.z;

    if (obj != 0)
        ((CObj*)obj)->v1();
}

// ===================================================================================================
// 0x00f932f0  void* cTerrainResourceManager::Create(void*, int, int, float)
// ===================================================================================================
// @ 0x00f932f0
void* cTerrainResourceManager::Create(void* obj, int a3, int a4, float a5)
{
    int v1 = *(int*)((char*)obj + 0x10);
    int v2 = *(int*)((char*)obj + 8);
    void** ovt = *(void***)obj;
    int local = 0;
    bool ok = ((bool(__thiscall*)(void*, unsigned int, int*))ovt[0x24 / 4])(obj, 0x2a907b7, &local);
    if (ok && *(short*)(*(int*)&local + 0x12) == 10) {
        int* r = (int*)FUN_00fa23a0();
        v2 = *r;
    }
    void* mgr = FUN_00fa23a0();
    if (mgr != 0)
        ((CObj*)mgr)->v0();
    void* state = EAAllocate(0xc40, "Terrain/ResourceManager/cTerrainStateMgr", 0, 0, 0, 0);
    if (state != 0)
        state = new (state) cTerrainStateMgr(mgr);
    else
        state = 0;
    *(void**)((char*)mgr + 0x20c) = state;
    ((CObj*)state)->DoD(0);
    *(int*)((char*)mgr + 0x1cc) = v2;
    void** mvt = *(void***)mgr;
    ((void(__thiscall*)(void*, void*))mvt[0x114 / 4])(mgr, this);
    ((void(__thiscall*)(void*))mvt[0x128 / 4])(mgr);
    ((void(__thiscall*)(void*))mvt[0xa0 / 4])(mgr);
    SetEffectSeed((unsigned int)v2);
    int cond = (local == 0) ? 1 : 0;
    ((CObj*)mgr)->DoE(0, 0, cond, a3, a4);
    ((void(__thiscall*)(void*))mvt[1])(mgr);
    (void)v1; (void)a5;
    return mgr;
}

// ===================================================================================================
// 0x00f933f0  int cTerrainResourceManager::GetCount(int)
// ===================================================================================================
// @ 0x00f933f0
int cTerrainResourceManager::GetCount(int idx)
{
    int* p = (int*)((char*)this + 0x10 + idx * 0x14);
    return (p[1] - p[0]) / 12;
}

// ===================================================================================================
// 0x00f93420  cTerrainResourceManager::~cTerrainResourceManager()
// ===================================================================================================
// @ 0x00f93420
cTerrainResourceManager::~cTerrainResourceManager()
{
    void* p = m64;
    if (p != 0) {
        void* sub = (char*)p + 4;
        void** vt = *(void***)sub;
        ((void(__thiscall*)(void*))vt[1])(sub);
    }

    TerrainVec* vec = (TerrainVec*)((char*)this + 0x10);
    TerrainVec* q = vec + 4;
    int i = 3;
    for (;;) {
        void* d = (--q)->mpBegin;
        if (d != 0 && *(int*)((char*)d - 4) != 0)
            op_delete(d);
        if (--i < 0)
            break;
    }
}

// ===================================================================================================
// 0x00f93490  bool cTerrainResourceManager::GetPlanet(void*, int, int, int, float)
// ===================================================================================================
// @ 0x00f93490
bool cTerrainResourceManager::GetPlanet(void* out, int a3, int a4, int a5, float a6)
{
    void* e = FUN_00f48a70();
    if (!((CObj*)e)->IsA()) {
        e = FUN_00f48a70();
        ((CObj*)e)->DoB();
    }
    e = FUN_00f48a70();
    ((CObj*)e)->DoC();

    cSPVector3 local;
    local.x = *(float*)((char*)out + 0);
    local.y = *(float*)((char*)out + 4);
    local.z = *(float*)((char*)out + 8);

    void** vt = *(void***)this;
    void* obj = ((void*(__thiscall*)(void*, cSPVector3*))vt[1])(this, &local);
    if (obj != 0) {
        void** ovt = *(void***)obj;
        ((void(__thiscall*)(void*))ovt[0])(obj);
        ((void(__thiscall*)(void*, unsigned int, int*))ovt[0x24 / 4])(obj, 0x3ad556a, &a5);
    }
    void* res = Create(obj, a3, a4, a6);
    if (res != 0) {
        *(void**)out = res;
        ((CObj*)res)->v0();
        if (obj != 0)
            ((CObj*)obj)->v1();
        return true;
    }
    if (obj != 0)
        ((CObj*)obj)->v1();
    return false;
}

// ===================================================================================================
// 0x00f93560  void* cTerrainResourceManager::Get(int*)
// ===================================================================================================
// @ 0x00f93560
void* cTerrainResourceManager::Get(int* p)
{
    void* pm = SP_PropertyManager();
    int local = 0;
    void** pvt = *(void***)pm;
    bool ok = ((bool(__thiscall*)(void*, int, int, int*))pvt[0x2c / 4])(pm, p[0], p[2], &local);
    if (!ok) {
        unsigned int key = (unsigned int)p[2];
        if ((key & 0xff0000) != 0x840000) {
            if (local != 0)
                ((CObj*)local)->v1();
            return 0;
        }
        unsigned int idx = (key >> 8) & 0xff;
        if (idx >= 0xb0 && idx <= 0xb3) {
            TerrainVec* v = (TerrainVec*)((char*)this + 0x10 + (idx - 0xb0) * 0x14);
            if (v->mpBegin == v->mpEnd) {
                if (local != 0)
                    ((CObj*)local)->v1();
                return 0;
            }
        }
    }
    if (local != 0)
        ((CObj*)local)->v1();
    return 0;
}
