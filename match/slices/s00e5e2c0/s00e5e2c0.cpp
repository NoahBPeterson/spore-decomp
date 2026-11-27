// @ 0x00e5e2c0
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// SP::sUpdateTileBackground (dev PDB name and parameters; SPGonzago/SPCellGame.obj).  Walks the level grid
// pool and, for the background grids of one tiling level, drives their tiling effect: alpha 0 stops and
// drops the effect, anything else creates it on first use (centred on and sized to the grid block's
// extents) and sets its alpha parameter.

namespace rw { namespace math { namespace fpu {

template <class T, int Aligned> class Vector3Template {
public:
    T x, y, z;
    Vector3Template() {}
    Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
    Vector3Template(const Vector3Template& v) : x(v.x), y(v.y), z(v.z) {}
};

template <class T, int Aligned>
class Matrix33Template {
public:
    T m[9];
};

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator-(const Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    return Vector3Template<T, Aligned>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator*(const Vector3Template<T, Aligned>& v, const T& s)
{
    return Vector3Template<T, Aligned>(v.x * s, v.y * s, v.z * s);
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator+(const Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    Vector3Template<T, Aligned> r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator*(const Vector3Template<T, Aligned>& v, const Matrix33Template<T, Aligned>& m)
{
    Vector3Template<T, Aligned> r;
    r.x = v.x * m.m[0] + v.y * m.m[3] + v.z * m.m[6];
    r.y = v.x * m.m[1] + v.y * m.m[4] + v.z * m.m[7];
    r.z = v.x * m.m[2] + v.y * m.m[5] + v.z * m.m[8];
    return r;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator-=(Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    T x = a.x - b.x;
    T y = a.y - b.y;
    T z = a.z - b.z;
    a.x = x;
    a.y = y;
    a.z = z;
    return a;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator+=(Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    T x = a.x + b.x;
    T y = a.y + b.y;
    T z = a.z + b.z;
    a.x = x;
    a.y = y;
    a.z = z;
    return a;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator*=(Vector3Template<T, Aligned>& v, const T& s)
{
    T x = v.x * s;
    T y = v.y * s;
    T z = v.z * s;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator/=(Vector3Template<T, Aligned>& v, const T& s)
{
    T inv = 1.0f / s;
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    return v;
}

} } }

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : rw::math::fpu::Vector3Template<float, 0>(ax, ay, az) {}
    cSPVector3(const cSPVector3& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3(const rw::math::fpu::Vector3Template<float, 0>& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3& operator=(const rw::math::fpu::Vector3Template<float, 0>& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

struct cSPMatrix3 : public rw::math::fpu::Matrix33Template<float, 0> {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& src);   // 0x0041cb40 (Matrix3::Assign)
};

extern const cSPVector3 kZeroVector;      // 0x016b3c28
extern const cSPMatrix3 kIdentityMatrix;  // 0x016b3dac

struct cSPTransform {
    enum tFlags { kHasScale = 1, kHasRotation = 2, kHasTranslation = 4 };

    unsigned short mFlags;               // +0x00 tFlags
    unsigned short mModificationCount;   // +0x02
    cSPVector3     mTranslation;         // +0x04
    float          mScale;               // +0x10
    cSPMatrix3     mRotation;            // +0x14

    cSPTransform()
        : mFlags(0), mModificationCount(0), mTranslation(kZeroVector), mScale(1.0f), mRotation(kIdentityMatrix) {}

    void SetTranslation(const cSPVector3& t)
    {
        mTranslation = t;
        mFlags |= kHasTranslation;
        mModificationCount++;
    }
    void SetScale(float s)
    {
        mScale = s;
        mModificationCount++;
    }
};

struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
};

namespace EA { namespace Swarm {
struct cIVisualEffect {
    virtual int  AddRef();                                                    // +0x00
    virtual int  Release();                                                   // +0x04
    virtual bool Start(int hardStart);                                        // +0x08
    virtual bool Stop(int hardStop);                                          // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void SetTransform(const cSPTransform& transform);                 // +0x18
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void SetFloatParams(int param, const float* values, int count);   // +0x44
};
struct cIEffectsWorld;
} }

namespace EA { namespace COM {
template <class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T** AsPPTypeParam() { *this = 0; return &mpObject; }
};
} }

// Untyped object pool (shared out-of-line code) and its typed front end.
struct cSPObjectPool {
    int   GetHead();           // 0x00e31100
    void* GetNext(int* it);    // 0x00b72230
};

template <class T, int N> struct cSPObjectPoolT {
    cSPObjectPool mPool;
    int GetHead() { return mPool.GetHead(); }
    T* GetNext(int& it) { return (T*)mPool.GetNext(&it); }
};

namespace SP {

typedef int eLayer;
typedef int eLevel;

struct cBlockCoord {
    eLayer layer;      // +0x00
    eLevel level;      // +0x04
    int    i;          // +0x08
    int    j;          // +0x0c
    bool   startTile;  // +0x10
};

struct cLevelGrid {
    unsigned int id;                                                  // +0x000
    cBlockCoord  block;                                               // +0x004
    char         pad_018[0x300 - 0x18];
    EA::COM::AutoRefCount<EA::Swarm::cIVisualEffect> tilingEffect;   // +0x300
};

struct CellSaveGame {
    char pad_00[0x1c];
    int  foodProgression;   // +0x1c
};

struct cCellGame {
    char pad_0000[0x38];
    cSPObjectPoolT<cLevelGrid, 512> mGridSquares;   // +0x0038
    char pad_003c[0x514c - 0x3c];
    float mZoomLevel;                                // +0x514c (dev +0x5128)
    char pad_5150[0x5190 - 0x5150];
    CellSaveGame* mSaveGame;                         // +0x5190 (dev +0x5178)
};

struct cCellGfx {
    char pad_00000[0x161bc];
    EA::Swarm::cIEffectsWorld* mpEffectsWorld;      // +0x161bc
};

extern cCellGame* gspCellGame;   // 0x016b3c04
extern cCellGfx*  gspCellGfx;    // 0x016b3c08
extern float kLevelSize[];       // 0x01483bd0, block size per level
extern const float kBoxScale;    // 0x013f6a20

extern int g_1483c34[];          // 0x01483c34 level thresholds (stride 7 dwords)
extern int g_1483c14[];          // 0x01483c14 level values (stride 7 dwords)
extern int g_1483e60;            // 0x01483e60 level for food progression 1000
extern const float kOne_1485720, kHalf_1471064, kQuarter_13eb8a0, kEighth_1486d94, kSixteenth_13f115c,
                   k32nd_140e964;

// 0x00e4ee60 (matched in slice s00e4e8d0) and 0x00e51ff0 (slice s00e51820) are defined earlier in this
// translation unit, so the caller below is compiled knowing they leave every xmm register alone.
int __fastcall sGetSourceLevel(int, int foodProgression)
{
    if (foodProgression == 1000) return g_1483e60;
    int i = 0;
    if (foodProgression >= 0) {
        int* p = g_1483c34;
        do { p += 7; ++i; } while (foodProgression >= *p);
    }
    return g_1483c14[i * 7];
}

float sGetBoxSizeMultiplier2(eLevel level, eLayer layer)
{
    int d = level - sGetSourceLevel(0, gspCellGame->mSaveGame->foodProgression);
    if (d <= -2) return kOne_1485720;
    if (d >= 5) return k32nd_140e964;
    switch (d) {
    case -1: return kOne_1485720;
    case 0:  return kHalf_1471064;
    case 1:  return kQuarter_13eb8a0;
    case 2:  return kEighth_1486d94;
    case 3:  return kSixteenth_13f115c;
    case 4:  return k32nd_140e964;
    default: return kHalf_1471064;
    }
}

inline float sGetBoxSizeMultiplier(eLevel level, eLayer layer)
{
    return sGetBoxSizeMultiplier2(level, layer) * kBoxScale;
}

// World-space extents of one grid block (dev: SP::sBlockCoordGetExtents; static, so cl inlines it here).
static void sBlockCoordGetExtents(const cBlockCoord& coord, cSPBoundingBox& box, bool debugdraw)
{
    const float border = debugdraw ? 1.0f : 0.0f;
    const float size = kLevelSize[coord.level];
    const float inset = (float)coord.level * border;
    box.mMin.x = (float)coord.i * size + inset;
    box.mMin.y = (float)coord.j * size + inset;
    box.mMin.z = 0.0f;
    box.mMax.x = (float)(coord.i + 1) * size - inset;
    box.mMax.y = (float)(coord.j + 1) * size - inset;
    box.mMax.z = 0.0f;
    float boxSizeFactor = sGetBoxSizeMultiplier(coord.level, coord.layer);
    box.mMin /= gspCellGame->mZoomLevel / boxSizeFactor;
    box.mMax /= gspCellGame->mZoomLevel / boxSizeFactor;
}

bool CreateEffect(EA::Swarm::cIEffectsWorld* world, unsigned int id, unsigned int instance,
                  EA::Swarm::cIVisualEffect** out);   // 0x00628450

// @ 0x00e5e2c0
void sUpdateTileBackground(const unsigned int& effect, float alpha, eLevel tilingGrid)
{
    int it = gspCellGame->mGridSquares.GetHead();
    for (cLevelGrid* grid = gspCellGame->mGridSquares.GetNext(it); grid; grid = gspCellGame->mGridSquares.GetNext(it)) {
        if (grid->block.layer == 1 && grid->block.level == tilingGrid) {
            EA::COM::AutoRefCount<EA::Swarm::cIVisualEffect>& tilingEffect = grid->tilingEffect;
            if (alpha == 0.0f) {
                if (tilingEffect) {
                    tilingEffect->Stop(1);
                    tilingEffect = 0;
                }
            } else {
                cSPBoundingBox box;
                sBlockCoordGetExtents(grid->block, box, false);
                if (!grid->tilingEffect) {
                    CreateEffect(gspCellGfx->mpEffectsWorld, effect, 0, tilingEffect.AsPPTypeParam());
                    cSPVector3 pos = (box.mMax + box.mMin) * 0.5f;
                    cSPTransform transform;
                    transform.SetTranslation(pos);
                    transform.SetScale((box.mMax - box.mMin).x);
                    tilingEffect->SetTransform(transform);
                    tilingEffect->Start(0);
                }
                tilingEffect->SetFloatParams(4, &alpha, 1);
            }
        }
    }
}

}  // namespace SP
