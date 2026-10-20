// Slice s00fc4cd0: SP::cWeatherManager weather-cell / terrain-map methods
// (0x00fc4cd0 .. 0x00fc58ec).  Object file SPTerrain/SPWeatherManager.obj.
//
// 0x00fc4cd0  sample a vector texel into a Vector4 (w = 1)
// 0x00fc5480  advance one weather cell inside its map and stamp the terrain
// 0x00fc57b0  tear the weather manager down (releases every member object)
//
// Retail layout confirmed against the 0x00fc6640 constructor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <intrin.h>

// ------------------------------------------------------------------ globals
extern float g_weatherFloat_15b16fc;   // 0x015b16fc (phase threshold)
extern float g_weatherFloat_15b1700;   // 0x015b1700 (height offset)

// Truncating float->int (cvttss2si from the helper's stack slot); asm helper as in the original.
#pragma warning(push)
#pragma warning(disable : 4035)   // result returned in eax
inline int TruncToInt_s00fc_4cd0(float f)
{
    __asm cvttss2si eax, f
}
#pragma warning(pop)

// -------------------------------------------------------------- small types
struct Vec3    { float x, y, z; };
struct Vector4 { float x, y, z, w; };

// ------------------------------------------------------------------ maps
// Direction -> cube face + integer texel coordinates.
struct MapUV_s00fc_4cd0 { int x, y, face; };

// cTerrainMap<T>: vtable, refcount, face size, mod count, then the texel vector.
struct cTerrainMapBase_s00fc_4cd0 {
    void*    mpVtable;    // +0x00
    int      mRefCount;   // +0x04
    int      mFaceSize;   // +0x08
    uint32_t mModCount;   // +0x0c
};
template <class T> struct cTerrainMap_s00fc_4cd0 : cTerrainMapBase_s00fc_4cd0 {
    T* mpData;            // +0x10

    // Texel at `uv`; the caller has already clamped the coordinates to the face edge.
    __forceinline const T& GetCubeValue(const MapUV_s00fc_4cd0& uv) const
    {
        return mpData[(mFaceSize * uv.face + uv.y) * mFaceSize + uv.x];
    }

    void SetCell(const MapUV_s00fc_4cd0& index, T value);   // 0x00f87b30
};

extern cTerrainMap_s00fc_4cd0<float>* g_terrainMap_16d7150;   // 0x016d7150

// Texel coordinates of `v`'s cube face, scaled to `map`'s face size and clamped at the face edge.
template <class T>
static __forceinline MapUV_s00fc_4cd0 DirToMapUV_s00fc_4cd0(const Vec3& v, const cTerrainMap_s00fc_4cd0<T>* map)
{
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    int size = map->mFaceSize;
    float half = (float)size * 0.5f;
    MapUV_s00fc_4cd0 r;
    if (az >= ax && az >= ay) {
        r.x = TruncToInt_s00fc_4cd0((x / z + 1.0f) * half);
        r.y = TruncToInt_s00fc_4cd0((y / az + 1.0f) * half);
        r.face = (z >= 0.0f) ? 0 : 1;
    } else if (ay >= ax) {
        r.x = TruncToInt_s00fc_4cd0((z / y + 1.0f) * half);
        r.y = TruncToInt_s00fc_4cd0((x / ay + 1.0f) * half);
        r.face = (y >= 0.0f) ? 4 : 5;
    } else {
        r.x = TruncToInt_s00fc_4cd0((y / x + 1.0f) * half);
        r.y = TruncToInt_s00fc_4cd0((z / ax + 1.0f) * half);
        r.face = (x >= 0.0f) ? 2 : 3;
    }
    if (r.x == size) r.x--;
    if (r.y == size) r.y--;
    return r;
}

// ------------------------------------------------- reference-counted objects
// Any polymorphic object stored by pointer in the manager: only its vtable shape matters here.
class cRefObj_s00fc_4cd0 {
public:
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
};

// EA RefCountTemplate: virtual scalar-deleting destructor at vtable +0x00, refcount at +0x04.
class cRefCount_s00fc_4cd0 {
public:
    virtual ~cRefCount_s00fc_4cd0();
    int mRefCount;   // +0x04

    int Release()
    {
        int count = mRefCount - 1;
        mRefCount = mRefCount - 1;
        if (count)
            return count;
        mRefCount = 1;
        delete this;
        return 0;
    }
};

// An 0x18-byte manager member torn down by an out-of-line routine (0x004b5440).
struct cObj170_s00fc_4cd0 {
    uint32_t pad[6];
    void Clear();   // 0x004b5440
};

// ----------------------------------------------------------- the weather class
class cWeatherManager_s00fc_4cd0 {
public:
    void GetTerrainVector4(Vector4& out, const Vec3& dir);   // 0x00fc4cd0
    void Reset();                                            // 0x00fc57b0

    template <class T> __forceinline cTerrainMap_s00fc_4cd0<T>* GetTerrainMap()
    {
        return (cTerrainMap_s00fc_4cd0<T>*)mpTerrainMap;
    }

    void*    mpVtbl0;         // +0x00
    uint32_t mRefCount04;     // +0x04
    void*    mpVtbl8;         // +0x08
    cRefObj_s00fc_4cd0* mp0C;   // +0x0c
    cRefObj_s00fc_4cd0* mp10;   // +0x10
    cRefObj_s00fc_4cd0* mp14;   // +0x14
    cRefObj_s00fc_4cd0* mp18;   // +0x18
    cRefObj_s00fc_4cd0* mp1C;   // +0x1c
    cRefObj_s00fc_4cd0* mp20;   // +0x20
    cRefObj_s00fc_4cd0* mp24;   // +0x24
    cRefObj_s00fc_4cd0* mp28;   // +0x28
    cRefObj_s00fc_4cd0* mp2C;   // +0x2c
    cRefObj_s00fc_4cd0* mp30;   // +0x30
    cRefObj_s00fc_4cd0* mpTerrainMap;   // +0x34
    uint32_t pad38[31];       // +0x38 .. +0xb3
    cRefObj_s00fc_4cd0* mpB4;   // +0xb4
    uint32_t padB8[3];        // +0xb8 .. +0xc3
    cRefObj_s00fc_4cd0* mpC4;   // +0xc4
    uint32_t padC8[3];        // +0xc8 .. +0xd3
    cRefObj_s00fc_4cd0* mpD4;   // +0xd4
    cRefObj_s00fc_4cd0* mpD8;   // +0xd8
    uint32_t padDC[0x22];     // +0xdc .. +0x163
    cRefCount_s00fc_4cd0* mp164;   // +0x164
    uint32_t pad168[2];       // +0x168 .. +0x16f
    cObj170_s00fc_4cd0 m170;  // +0x170
    cRefObj_s00fc_4cd0* mp188;   // +0x188
};

// ----------------------------------------------------------- vtable sentinels
extern void* g_vftblCWeatherA_1491604;   // 0x01491604
extern void* g_vftblCWeatherB_14915f4;   // 0x014915f4
extern void* g_vftblGmeRefCount_13ef094; // 0x013ef094
extern void* g_vftblIMsgHandler_13eb394; // 0x013eb394

// ----------------------------------------------------- the weather-cell state
// Object whose +0x08 accumulates the elapsed time and whose +0x0c is the cell duration.
struct cWeatherCell_s00fc_4cd0 {
    uint32_t pad00[2];      // +0x00
    float    mElapsed;      // +0x08
    float    mDuration;     // +0x0c
    float    mX, mY, mZ;    // +0x10, +0x14, +0x18
};

// Simulation state that owns the transform the cell is pushed through.
struct cWeatherSim_s00fc_4cd0 {
    uint32_t pad00[0x42];   // +0x00 .. +0x107
    uint8_t  mFlags108;     // +0x108
    uint8_t  pad109[3];
    float    m10C;          // +0x10c
    float    m110;          // +0x110
    float    m114;          // +0x114
    float    m118;          // +0x118
    float    m11C;          // +0x11c
    float    m120;          // +0x120
    float    m124;          // +0x124
    float    m128;          // +0x128
    float    m12C;          // +0x12c
    float    m130;          // +0x130
    float    m134;          // +0x134
    float    m138;          // +0x138
    float    m13C;          // +0x13c
};

// @ 0x00fc4cd0
void cWeatherManager_s00fc_4cd0::GetTerrainVector4(Vector4& out, const Vec3& dir)
{
    MapUV_s00fc_4cd0 uv = DirToMapUV_s00fc_4cd0(dir, GetTerrainMap<Vec3>());
    const Vec3& texel = GetTerrainMap<Vec3>()->GetCubeValue(uv);
    Vector4 t;
    t.x = texel.x;
    t.y = texel.y;
    t.z = texel.z;
    t.w = 1.0f;
    out.x = t.x;
    out.y = t.y;
    out.z = t.z;
    out.w = t.w;
}

// @ 0x00fc5480
bool AdvanceWeatherCell_s00fc_4cd0(cWeatherCell_s00fc_4cd0* cell, float dt, uint32_t param3,
                                   cWeatherSim_s00fc_4cd0* sim)
{
    float elapsed = cell->mElapsed + dt;
    cell->mElapsed = elapsed;
    if (cell->mDuration <= elapsed)
        return false;

    float x = cell->mX;
    float y = cell->mY;
    float z = cell->mZ;

    int face = 2;
    float ratio = elapsed / cell->mDuration;

    float px = x;
    float py = y;
    float pz = z;
    if (sim->mFlags108 & 2) {
        px = (sim->m128 * y + sim->m134 * z) + x * sim->m11C;
        py = (sim->m12C * y + sim->m120 * x) + sim->m138 * z;
        pz = (sim->m130 * y + sim->m124 * x) + sim->m13C * z;
    }

    float scale = sim->m118;
    float sx = sim->m10C + scale * px;
    float sy = sim->m110 + scale * py;
    float sz = sim->m114 + scale * pz;

    float ax = fabsf(sx);
    float ay = fabsf(sy);
    float az = fabsf(sz);

    cTerrainMap_s00fc_4cd0<float>* map = g_terrainMap_16d7150;
    int size = map->mFaceSize;
    float half = (float)size * 0.5f;

    MapUV_s00fc_4cd0 uv;
    int ix, iy;
    if (az >= ax && az >= ay) {
        ix = TruncToInt_s00fc_4cd0((sx / sz + 1.0f) * half);
        iy = TruncToInt_s00fc_4cd0((sy / az + 1.0f) * half);
        face = (sz >= 0.0f) ? 0 : 1;
    } else if (ay >= ax) {
        ix = TruncToInt_s00fc_4cd0((sz / sy + 1.0f) * half);
        iy = TruncToInt_s00fc_4cd0((sx / ay + 1.0f) * half);
        face = (sy >= 0.0f) ? 4 : 5;
    } else {
        ix = TruncToInt_s00fc_4cd0((sy / sx + 1.0f) * half);
        iy = TruncToInt_s00fc_4cd0((sz / ax + 1.0f) * half);
        face = (sx >= 0.0f) ? 2 : 3;
    }
    if (ix == size) ix--;
    if (iy == size) iy--;
    uv.x = ix;
    uv.y = iy;
    uv.face = face;

    if (map != 0 && g_weatherFloat_15b16fc < ratio) {
        float value = map->GetCubeValue(uv) - g_weatherFloat_15b1700;
        if (value < 0.0f)
            value = 0.0f;
        map->SetCell(uv, value);
    }
    return true;
}

// @ 0x00fc57b0
void cWeatherManager_s00fc_4cd0::Reset()
{
    *(void* volatile*)&mpVtbl0 = (void*)&g_vftblCWeatherA_1491604;
    *(void* volatile*)&mpVtbl8 = (void*)&g_vftblCWeatherB_14915f4;
    _ReadWriteBarrier();
    if (mp188)
        mp188->vf04();
    m170.Clear();
    if (mp164)
        mp164->Release();
    if (mpD8)
        mpD8->vf0c();
    if (mpD4)
        mpD4->vf04();
    if (mpC4)
        mpC4->vf04();
    if (mpB4)
        mpB4->vf04();
    if (mpTerrainMap)
        mpTerrainMap->vf04();
    if (mp30)
        mp30->vf04();
    if (mp2C)
        mp2C->vf04();
    if (mp28)
        mp28->vf04();
    if (mp24)
        mp24->vf04();
    if (mp20)
        mp20->vf04();
    if (mp1C)
        mp1C->vf04();
    if (mp18)
        mp18->vf04();
    if (mp14)
        mp14->vf04();
    if (mp10)
        mp10->vf04();
    if (mp0C)
        mp0C->vf04();
    *(void* volatile*)&mpVtbl0 = (void*)&g_vftblGmeRefCount_13ef094;
    *(void* volatile*)&mpVtbl8 = (void*)&g_vftblIMsgHandler_13eb394;
}
