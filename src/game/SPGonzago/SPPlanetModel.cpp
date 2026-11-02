// src/game/SPGonzago/SPPlanetModel.cpp -- migrated from slice(s) s00b8bb70, s00b87dc0, s00b84270, s00b832d0, s00b815a0, s00b7ea80, s00472b80, s00b8d190, s00b8aea0, s00b8a760, s00b89a30, s00b894a0, s00b85380, s00b80630, s00b7f920 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlanetModel.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cITerrainSphere.h"
#include "SP/cPlanetModel.h"
#include "SP/cStaticBuffer.h"
#include "rw/graphics/ImmediateMode.h"
#include <new>
#include "SP/cGameNounManager.h"
#include "SP/cTerrainMapSet.h"
#include <math.h>
#include <intrin.h>
#include <stdarg.h>
#include "SP/cTerrainSphere.h"
#include <xmmintrin.h>
#include "SP/cPoliticalZone.h"
#include "cSPVector3.h"
#include "SP/cCity.h"
#include "SP/cCivilization.h"
#include "SP/cPlanet.h"
#include "SP/cRenderer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(memcpy, memset, sqrt)

// ---- items of slice s00b7f920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" double __cdecl sqrt(double);
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    Vector3 Normalized() const {
        float f = 1.0f / Length();
        return Vector3(x * f, y * f, z * f);
    }
    Vector3 Cross(const Vector3& v) const {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float x_, float y_) : x(x_), y(y_) {}
};
inline Vector3 Hermite(const Vector3& p0, const Vector3& p1, const Vector3& m0, const Vector3& m1, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    float h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
    float h01 = 3.0f * t2 - 2.0f * t3;
    float h10 = t3 - 2.0f * t2 + t;
    float h11 = t3 - t2;
    return p0 * h00 + p1 * h01 + m0 * h10 + m1 * h11;
}
struct RibbonVertex {
    Vector3 pos;      // +0x00
    Vector3 normal;   // +0x0c
    uint32_t color;   // +0x18
    Vector2 uv;       // +0x1c
};
namespace SP {
class cStaticBuffer_s00b7_f920 {
public:
    int GetVertexBuffer(int count, RibbonVertex** ppVertices, int* pStride);   // 0x007a47c0
    void Unlock();                                                              // 0x007a4650
};
}
namespace SP {
class cStaticBufferDraw_s00b7_f920 { public:
    cStaticBuffer_s00b7_f920* mpBuffer;
    static cStaticBufferDraw_s00b7_f920* spInstance;   // 0x015ddc84
};
}
namespace SP {
struct cGridInfo { uint32_t pad[0x38 / 4]; float mHeightOffset; };   // +0x38
}
namespace SP {
struct IGrid { virtual void v00(); virtual void v04(); virtual void v08(); virtual cGridInfo* GetInfo(); };
}
namespace SP {
IGrid* DebugDrawGrid();   // 0x00f48aa0
}
namespace SP {
struct cPlanetInfo { uint32_t pad[0x34 / 4]; float mRadius; };      // +0x34
}
namespace SP {
struct IPlanet { virtual void v00(); virtual void v04(); virtual void v08(); virtual cPlanetInfo* GetInfo(); };
}
namespace SP {
class cPlanetModel_s00b7_f920 { public: uint32_t pad[0x24 / 4]; IPlanet* mpPlanet; };  // +0x24
}
namespace SP {
cPlanetModel_s00b7_f920* PlanetModel();   // 0x00b3d350
}
class cArcRibbon {
public:
    void DrawArc(const Vector3& a, const Vector3& b, uint32_t color);
};
// ---- items of slice s00b7f920 end

// ---- items of slice s00b80630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long *, long);
extern "C" long __cdecl _InterlockedExchange(volatile long *, long);
extern "C" float sqrtf(float);
extern "C" void  operator_delete_array(void *p);                                     // 0xf47380
extern const float kOne;      // 0x1485720 = 1.0f
extern const float kEps;      // 0x146543c = 1.5258789e-05f
extern const float k64;       // 0x140f334 = 64.0f
extern const float k128;      // 0x1400a58 = 128.0f
extern "C" void *FUN_0067dd50();                    // 0x0067dd50
extern "C" void *FUN_00761cf0(int n);               // 0x00761cf0
extern "C" void  FUN_007a4650();                    // 0x007a4650
extern "C" void *SP_GetActiveTerrainSphere();       // 0x00f48aa0
extern "C" void *SP_GetUniverseContext();           // 0x01021080
extern "C" void *SP_PlanetModel();                  // 0x00b3d350
extern "C" void *SP_NounManager(int id);            // 0x00b3d300
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
typedef unsigned int   u32;
typedef unsigned char  u8;
#define FORCEINLINE __forceinline
extern "C" void *operator_new(u32 n, const char *pFile, int a, int b, int c, int d); // 0xf473a0
extern const u8    gPlaneOrder[]; // 0x14653b8 face-permutation table
struct Mode;
struct Layer;
struct RefObj {
    void         **m_vtbl;  // +0x00
    volatile long  m_ref;   // +0x04
    void          *m_data;  // +0x08
};
struct RangeEntry {
    const void *m_begin;   // +0x00
    const void *m_end;     // +0x04
    u8          m_pad08[0x0c];
};
struct RangeSecondEntry {
    const void *m_ptr;     // +0x00
    u8          m_pad04[0x10];
};
struct Mode {
    void         **m_vtbl;          // +0x00
    volatile long  m_ref;           // +0x04
    void          *m_buffer;        // +0x08  cStaticBuffer*
    RangeSecondEntry *m_rangeSecond;// +0x0c  per-range second vertex pointer
    u8             m_pad10[0x10];   // +0x10
    RangeEntry    *m_ranges;        // +0x20  per-range span table, stride 0x14
    u8             m_pad24[0x10];   // +0x24
    u32           *m_idBegin;       // +0x34  planet-id vector begin
    u32           *m_idEnd;         // +0x38  planet-id vector end

    void Submit();                                   // 0x00b80b40
    void DrawMaterial(void *pMaterial, void *pParam); // 0x00b80a50
    void SetMaterialA(void *pParam);                 // 0x00b80a80
    void SetMaterialB(void *pParam);                 // 0x00b80ac0
    void SetMaterialC(void *pParam);                 // 0x00b80b00
    Mode *DeleteInstance(u32 flags);                 // 0x00b80ff0
    void BuildRibbon(const void *pVerts, const void *pOther, int count, u32 color); // 0x00b807e0
};
FORCEINLINE void DestroyMode(Mode *p)
{
    if (p != 0) {
        long n = _InterlockedDecrement(&p->m_ref);
        if (n == 0) {
            _InterlockedExchange(&p->m_ref, 1);
            if (p != 0) {
                ((void (__thiscall *)(Mode *, int))((RefObj *)p)->m_vtbl[0])(p, 1);
            }
        }
    }
}
FORCEINLINE void AssignMode(Mode **ppField, Mode *pNew)
{
    Mode *pOld = *ppField;
    if (pNew != pOld) {
        if (pNew != 0)
            _InterlockedExchangeAdd(&pNew->m_ref, 1);
        *ppField = pNew;
        if (pOld != 0) {
            long n = _InterlockedDecrement(&pOld->m_ref);
            if (n == 0) {
                _InterlockedExchange(&pOld->m_ref, 1);
                ((void (__thiscall *)(Mode *, int))((RefObj *)pOld)->m_vtbl[0])(pOld, 1);
            }
        }
    }
}
FORCEINLINE Mode *NewModifier()
{
    Mode *p = (Mode *)operator_new(0xc, "Simulator", 0, 0, 0, 0);
    if (p != 0) {
        p->m_vtbl = (void **)0x13ef094;
        _InterlockedExchange(&p->m_ref, 0);
        p->m_vtbl = (void **)0x146545c;
        ((RefObj *)p)->m_data = 0;
    } else {
        p = 0;
    }
    return p;
}
struct RefArray {
    void         **m_vtbl;   // +0x00
    u32            m_flags;  // +0x04
    u8             m_pad08[0x38];
    int            m_ref;    // +0x40
};
struct Layer {
    void     **m_vtbl;       // +0x00
    void     **m_vtbl2;      // +0x04
    volatile long m_lock8;   // +0x08
    u8         m_flag0c;     // +0x0c
    u8         m_pad0d[3];
    void      *m_p10;        // +0x10
    void      *m_p14;        // +0x14
    void      *m_p18;        // +0x18
    void      *m_p1c;        // +0x1c
    RefArray  *m_pRanges;    // +0x20
    Mode      *m_pMode;      // +0x24
    u8         m_flag28;     // +0x28
    u8         m_pad29[3];
    Mode      *m_pMod0;      // +0x2c
    Mode      *m_pMod1;      // +0x30
    Mode      *m_pMod2;      // +0x34

    Layer *Init();                                                   // 0x00b80630
    void   Destroy();                                                // 0x00b80d30
    void   StopAudio();                                              // 0x00b80e40
    void   DispatchEvent(void *p2, int event, void *pViewer, void *pMaterial); // 0x00b80ea0
};
struct cStaticBuffer {
    void Dispatch(void *a, void *b);   // 0x007a3e60
};
struct Vertex {
    float x, y, z;
};
struct RibbonVertex_s00b8_0630 {
    float x, y, z;    // +0x00
    u32   color;      // +0x0c
    float u;          // +0x10
    float v;          // +0x14
};
struct MaterialRef {
    void *m_unknown0;   // +0x00
    void *m_material;   // +0x04
};
struct MaterialManager {
    void *m_vtbl;       // +0x00
};
typedef MaterialRef *(__thiscall *FindMaterialFn)(MaterialManager *, u32);
extern "C" MaterialManager *SP_MaterialManager();   // 0x0067dd70
struct EffectsDispatch_t {
    float m[4][4];
};
extern "C" void EffectsDispatch(EffectsDispatch_t *m, u32 n); // 0x005291f0
struct Viewer {
    bool Update();   // 0x007c4fd0
    void Finish();   // 0x007c3c10
};
struct ViewerHandle {
    Viewer *m_viewer;  // +0x00
};
struct PlanetRecord {
    int  m_noun;       // +0x00
    u8   m_pad04[0x0d];
    u8   m_flag11;     // +0x11
    u8   m_pad12[6];
};
struct PlanetModel_s00b8_0630 {
    u8            m_pad00[0x80];
    PlanetRecord *m_records;   // +0x80
};
struct NounColor {
    u8    m_pad00[0xc4];
    float m_r;   // +0xc4
    float m_g;   // +0xc8
    float m_b;   // +0xcc
};
struct NounThing {
    NounColor *GetColor();   // 0x00b25f40
};
struct DrawHolder {
    void *m_draw;   // +0x00
    void Begin(u32 a, u32 b, u32 c, u32 d);   // 0x007a4420
};
extern DrawHolder *gDrawHolder;   // 0x15ddc84
struct Draw {
    void Flush();                                            // 0x007a4710
    void GetVertexBuffer(int a, void *b, void *c);           // 0x007a47c0
};
struct StampState {
    u8    m_pad00[0x4c];
    u32  *m_bits;   // +0x4c
    u8    m_pad50[0x2c];
    u8   *m_mask;   // +0x7c

    void Stamp(const float *pDir, float radius, u32 planeMask);   // 0x00b81020
};
struct SearchCoord {
    int m_a;   // +0x00
    int m_b;   // +0x04
    int m_c;   // +0x08
};
struct StampSpan {
    u32 m_plane;   // +0x00
    int m_minB;    // +0x04
    int m_minC;    // +0x08
    int m_maxB;    // +0x0c
    int m_maxC;    // +0x10
};
extern "C" int FUN_00685450(int maxVal, int *pCoord, int count, StampSpan *pOut); // 0x685450
extern "C" float acosf(float);
extern const float kHalf;     // 0x1471064 = 0.5f
extern const float kNegOne;   // 0x13eb1bc = -1.0f
// ---- items of slice s00b80630 end

// ---- items of slice s00b85380 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void *FUN_00b7f710(void *first, void *pos, void *dst);       // 0x00b7f710
extern "C" void  FUN_00b7f780(void *a, void *b, void *c, void *d, void *e); // 0x00b7f780
extern "C" void  FUN_00b7f800(void *a, void *b, void *c, void *d);      // 0x00b7f800
extern "C" void  FUN_00b7f6a0(void *a, void *b, void *c);               // 0x00b7f6a0
extern "C" void *FUN_00b7f8b0(void *a, void *b, void *c);               // 0x00b7f8b0
extern "C" void  FUN_00b85090(void *a, void *b, void *c);               // 0x00b85090
extern "C" void  FUN_00b7f5c0(void *a, void *b, void *c, void *d, void *e); // 0x00b7f5c0
extern "C" void  FUN_720250_CopyVertex3D(const void *first, const void *last, void *dst); // 0x00720250
static inline bool BlockIsOurs(const void *p)
{
    return p != 0 && ((const u32 *)p)[-1] != 0;
}
extern "C" void *memmove(void *d, const void *s, u32 n);                // via [0x13cc480]
extern "C" void  FUN_00b84e90(void *a, u32 b, void *c);                 // 0x00b84e90
extern "C" u32   FUN_00921340(u32 n);                                   // 0x00921340
struct Vec20B {
    u32 m0; u32 m4; u32 m8; u32 mc; u32 m10;
    void Assign(const Vec20B &src);       // 0x00473500
};
#define Vec20BAssign(pDst, pSrc) ((pDst)->Assign(*(pSrc)))
struct Vertex3D {
    float x, y, z, w;   // +0x00..0x0c
    u32   m10;          // +0x10
    float m14, m18, m1c; // +0x14..0x1c
    u32   m20;          // +0x20
};
struct Vec3f { float x, y, z; };
struct SpVector3 {
    Vec3f *mpBegin;   // +0x00
    Vec3f *mpEnd;     // +0x04
    Vec3f *mpCap;     // +0x08
    void  *mpGuard;   // +0x0c
    Vec3f *insert(Vec3f *pos, const Vec3f *pVal);   // 0x00b85d40
    void   DoInsertValue(Vec3f *pos, const Vec3f *pVal); // 0x004b5ad0
    Vec3f *end() const { return mpEnd; }
};
struct Vertex3DVec {
    Vertex3D *mpBegin;   // +0x00
    Vertex3D *mpEnd;     // +0x04
    Vertex3D *mpCap;     // +0x08
    void  *mpGuard;      // +0x0c
    void push_back(const Vertex3D *pVal);   // 0x00b85db0
    void GrowAndInsert(Vertex3D *pos, const Vertex3D *pVal); // 0x00b85380
    Vertex3D *CopyUninit(Vertex3D *pSrc, Vertex3D *pDst);    // 0x00b85500
    void InsertFillN(Vertex3D *pos, u32 n, const Vertex3D *pVal); // 0x00b85710
};
struct Vertex2D { float x, y, z, w; u32 m10; u32 m14; };  // 0x18
struct Vertex2DVec {
    Vertex2D *mpBegin;   // +0x00
    Vertex2D *mpEnd;     // +0x04
    Vertex2D *mpCap;     // +0x08
    Vertex2D *Assign(const Vertex2DVec *pSrc);          // 0x00b855e0
    Vertex2D *ReallocAssign(u32 n, const Vertex2D *pSrc, const Vertex2D *pSrcEnd); // 0x00b83be0
};
struct TileMapLookup {
    u8   mPad00[0x0c];
    Vec20B *mpData;   // +0x0c
    u8   mPad10[0x24];
    u32 *mpKeys;      // +0x34
    u32 *mpKeysEnd;   // +0x38
    char LookupAssign(u32 key, Vec20B *pOut);   // 0x00b859c0
};
struct FixedPool {
    u32   mPad00;         // +0x00
    void *mpBegin;        // +0x04  (+0xf8 in the object)
    u32   mCount;         // +0x08  (+0xfc)
    u32   mSize;          // +0x0c  (+0x100)
    u8    mPad10[0x0c];   // +0x10..0x1b
    void *mpFree;         // +0x1c  (+0x110) free-list head
    u8    mPad20[0x04];   // +0x20..0x23
    void *mpLow;          // +0x24  (+0x118) allocator range start
    void *mpHigh;         // +0x28  (+0x11c) allocator range end
    u8    mPad2c[0x04];   // +0x2c..0x2f
    void *mpSentinel;     // +0x30  (+0x124)
};
struct PaintSystem {
    void *mpVtbl;         // +0x00 (cListenerBase vtable)
    void *mpSubVtbl;      // +0x04 (cGonzagoSubsystem vtable)
    void *mpSubVtbl08;    // +0x08
    u32  *mpVec0c;        // +0x0c
    u8    mPad10[0x10];   // +0x10..0x1f
    void *mpField20;      // +0x20
    u8    mPad24[0x14];   // +0x24..0x37
    u32  *mpBits38;       // +0x38 bitvector begin
    u8    mPad3c[0x04];   // +0x3c
    u32  *mpBits40;       // +0x40 bitvector end
    u8    mPad44[0x0c];   // +0x44..0x4f
    u32  *mpVec50;        // +0x50
    u8    mPad54[0x10];   // +0x54..0x63
    u32  *mpVec64;        // +0x64
    u8    mPad68[0x18];   // +0x68..0x7f
    u32  *mpVec80;        // +0x80
    u8    mPad84[0x10];   // +0x84..0x93
    u32  *mpVec94;        // +0x94
    u8    mPad98[0x14];   // +0x98..0xab
    u32  *mpVecAc;        // +0xac
    u8    mPadB0[0x10];   // +0xb0..0xbf
    u32  *mpVecC0;        // +0xc0
    u8    mPadC4[0x10];   // +0xc4..0xd3
    u32  *mpVecD4;        // +0xd4
    u32  *mpVecD8;        // +0xd8
    u8    mPadDc[0x18];   // +0xdc..0xf3
    FixedPool mPool;      // +0xf4

    void Dtor();                             // 0x00b85a30
};
typedef void (__thiscall *PoolFreeNodesFn)(void *self, void *begin, void *count);
typedef void (__thiscall *PoolFreeVecFn)(void *self, void *begin, void *end);
typedef void (__thiscall *SubsystemDtorFn)(void *self);
typedef void (__thiscall *SubsystemCtorFn)(void *self);
struct FixedPoolBase {
    u32  m0;            // +0x00
    u32  m4;            // +0x04
    void *mpBegin;      // +0x08
    void *mpEnd;        // +0x0c
    u32  mElemSize;     // +0x10
    void *mpOwner;      // +0x14
};
typedef void (__thiscall *FixedPoolInitFn)(void *self, void *pBegin, u32 nBytes, u32 nElem, u32 nAlign, u32 nFlags);
typedef void (__thiscall *PoolInitNodesFn)(void *self, u32 nCount,
                                           void *a, void *pB1, void *pB2, void *b, void *pB3, void *pPool);
typedef u32  (__thiscall *PoolSizeFn)(void *self, u32 nCount);
typedef void (__thiscall *PoolGrowFn)(void *self, u32 nCount);
struct PaintSystemPool {
    u8   mPad00[0x08];      // +0x00..0x07
    u32  mSize;             // +0x08
    u32  mCount;            // +0x0c
    u32  mBoundHigh;        // +0x10 (10000.0f)
    u32  mBoundLow;         // +0x14 (2.0f)
    u32  mField18;          // +0x18
    u8   mPad1c[0x18];      // +0x1c..0x33
    u8   mField34[0x04];    // +0x34
    u8   mPad38[0x800];     // +0x38..0x837
    u8   mNodes[0x12000];   // +0x838 fixed-block pool
    u8   mTail[0x04];       // +0x12838

    void *InitPool(void *a, void *b);   // 0x00b85bc0 (thiscall)
};
struct TileMapIndex {
    u8      mPad00[0x04];   // +0x00
    void  **mpTable;        // +0x04 indexed record table
    u32     mIndex;         // +0x08

    void *IndexLookup(void *pKey);   // 0x00b85ca0 (thiscall)
};
struct TileMapKey {
    u32 m0;                 // +0x00
    u32 m4;                 // +0x04
    u32 m8;                 // +0x08
    u32 mC;                 // +0x0c
    u32 m10;                // +0x10
    u32 m14;                // +0x14
};
typedef void (__thiscall *MapFindFn)(void *self, void *pOut, const void *pKey);
typedef void (__thiscall *MapInsertFn)(void *self, void *pRec, const void *pKey, void *pArg);
struct LookupBuffer {
    u32        mRec[5];     // +0x00..0x13 located/inserted record
    TileMapKey key;         // +0x14..0x2b (overlaps the buffer tail)
    u32        mTail0;      // +0x2c
    u32        mTail1;      // +0x30
};
struct Vec20BElem { u32 m[5]; void Construct(void *pDefault); };  // 0x00b84ba0
struct SpVector20B {
    u32 *mpBegin;   // +0x00
    u32 *mpEnd;     // +0x04
    u32 *mpCap;     // +0x08
    void *AssignN(u32 n, u32 unused);       // 0x00b85e10
};
struct ByteVec {
    u8 *mpBegin;   // +0x00
    u8 *mpEnd;     // +0x04
    u8 *mpCap;     // +0x08
    void *CopyCtor(const ByteVec *pSrc);   // 0x00b85fb0
    void *AssignFrom(const ByteVec *pSrc); // 0x00b86010
    void *InsertFill(u8 *pos, u32 n, const u8 *pVal);  // 0x00b860d0
};
struct cGonzagoListener {
    u32 m00;                    // +0x00 vtable (cListenerBase)
    u32 mSubVtbl;               // +0x04 cGonzagoSubsystem vtable
    u32 mSubVtbl08;             // +0x08
    u8  mSysRest[0x14];         // +0x0c..0x1f
    u32 m20, m24;               // +0x20,+0x24
    float m28;                  // +0x28
    u32 m2c, m30, m34;          // +0x2c..0x34
    u32 m38, m3c;               // +0x38,+0x3c (wstring begin/end)
    u32 m40;                    // +0x40 (wstring cap)
    u8  m48;                    // +0x48
    u32 m4c, m50, m54, m58;     // +0x4c..0x58
    u32 m64, m68, m6c;          // +0x64..0x6c
    u8  m78;                    // +0x78
    u32 m7c, m80, m84, m88;     // +0x7c..0x88
    u32 m94, m98, m9c;          // +0x94..0x9c
    u32 mac, mb0, mb4;          // +0xac..0xb4
    u32 mc0, mc4, mc8;          // +0xc0..0xc8
    u32 md4, md8, mdc;          // +0xd4..0xdc
    u32 mec;                    // +0xec
    u8  mf0;                    // +0xf0
    u8  mpPool[4];              // +0xf4 fixed pool (thiscall member target)

    cGonzagoListener *Ctor();   // 0x00b863e0 (returns this)
};
// ---- items of slice s00b85380 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void * __stdcall AllocAndCopy(u32 n, const void *pSrc, const void *pSrcEnd);  // 0x00b85930 (stays in the slice: not this object's)

// ---- items of slice s00b894a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern const float kZero;   // 0x01485378  (0.0f)
extern char DAT_018c43e8;  // 0x018c43e8
#pragma intrinsic(fabs)
inline float Abs(float x) { return (float)fabs(x); }
#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)
void* FUN_00f473a0(unsigned int, const char*, int, int, const char*, int);  // 0x00f473a0 operator new[]
void  FUN_00f47380(void*);                                                  // 0x00f47380 operator delete[]
void* FUN_00b850c0(void*, void*, void*);                                    // 0x00b850c0 uninitialized_copy
void  FUN_00b7f6d0(void*, void*, void*);                                    // 0x00b7f6d0 destroy-after-move
void  FUN_00b86390(void*, void*, void*);                                    // 0x00b86390 copy_backward
void  FUN_00473460(void*, void*);                                           // 0x00473460 (thiscall, ret 4)
void  FUN_00bd9480(void*, void*);                                           // 0x00bd9480 (thiscall, ret 4)
void* FUN_00b3d300(void);                                                   // 0x00b3d300 SP::NounManager
void* FUN_00b21340(void*, void*, void*, void*, void*, void*);               // 0x00b21340 (thiscall, ret 0x14)
void FUN_00cd7d10(void);   // 0x00cd7d10
void FUN_00d3d420(void);   // 0x00d3d420
void FUN_00acdff0(void);   // 0x00acdff0
void FUN_00b1e500(void);   // 0x00b1e500
struct Vec3 { float x, y, z; };   // 0x0c
class Vec3Vec {
 public:
    Vec3* mpBegin;        // +0x00
    Vec3* mpEnd;          // +0x04
    Vec3* mpCapacity;     // +0x08
    int   mAllocator[2];  // +0x0c

    Vec3Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Vec3Vec(const Vec3Vec&) throw();          // 0x00473460
    Vec3Vec& operator=(const Vec3Vec&) throw();  // 0x00473500
    void assignRange(const Vec3*, const Vec3*, uint32_t);  // 0x00b86270
    void Free() {
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            FUN_00f47380(mpBegin);
    }
};
class OuterVec {
 public:
    Vec3Vec* mpBegin;     // +0x00
    Vec3Vec* mpEnd;       // +0x04
    Vec3Vec* mpCapacity;  // +0x08
    int      mAllocator[2];

    void DoInsertValue(Vec3Vec*, const Vec3Vec&);  // 0x00b88430
    void PushDefault();                            // 0x00b89770
};
struct Elem1c {
    uint32_t mA;      // +0x00
    uint32_t mB;      // +0x04
    Vec3Vec  mVec;    // +0x08
};
class Vec1c {
 public:
    Elem1c* mpBegin;     // +0x00
    Elem1c* mpEnd;       // +0x04
    Elem1c* mpCapacity;  // +0x08

    void DoInsertValue28(Elem1c*, const Elem1c&);  // 0x00b89830
};
class SPVectorI {
 public:
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;

    void DoInsertValueI(uint32_t*, const uint32_t&);  // 0x04558a0
    void push_back(const uint32_t& value) {
        uint32_t* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e)
                *e = value;
        } else {
            DoInsertValueI(e, value);
        }
    }
};
class cNatlBounds {
 public:
    char      _p00[0x0c];
    OuterVec  mVec0c;   // +0x0c
    OuterVec  mVec20;   // +0x20
    SPVectorI mVec34;   // +0x34

    void AddBoundary(const Vec3*, const Vec3*, uint32_t, uint32_t);  // 0x00b899b0
};
struct CellRec {                       // 0x18
    char    _p00[0x14];
    int32_t mId;                       // +0x14
};
struct GameDataVec {                   // returned by cGameNounManager::GetGameDataVector
    char      _p00[4];
    int32_t*  mpBegin;                 // +0x04
    int32_t*  mpEnd;                   // +0x08
};
class cCellGrid {
 public:
    char        _p00[0x80];
    CellRec*    mpCells;    // +0x80
    char        _p84[0x10];
    int8_t*     mpGrid;     // +0x94

    int32_t CellFromDirection(float* dir);   // 0x00b894a0
};
// ---- items of slice s00b894a0 end

// ---- items of slice s00b89a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const signed char gDirX[4];   // 0x1465420 {-1, 0, 1, 0}
extern const signed char gDirY[4];   // 0x1465424 { 0,-1, 0, 1}
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                         // 0xf473a0
void __cdecl operator_delete__(void* p);                                 // 0xf47380
struct Vec3_s00b8_9a30 {
    float x, y, z;
    Vec3_s00b8_9a30() {}
    Vec3_s00b8_9a30(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vec3_s00b8_9a30(const Vec3_s00b8_9a30& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3_s00b8_9a30 operator+(const Vec3_s00b8_9a30& b) const { return Vec3_s00b8_9a30(x + b.x, y + b.y, z + b.z); }
    Vec3_s00b8_9a30 operator-(const Vec3_s00b8_9a30& b) const { return Vec3_s00b8_9a30(x - b.x, y - b.y, z - b.z); }
    Vec3_s00b8_9a30 operator*(float f) const { return Vec3_s00b8_9a30(x * f, y * f, z * f); }
    float Dot(const Vec3_s00b8_9a30& b) const { return x * b.x + y * b.y + z * b.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vec3_s00b8_9a30 Normalized() const { float inv = 1.0f / Length(); return Vec3_s00b8_9a30(x * inv, y * inv, z * inv); }
};
inline Vec3_s00b8_9a30 Cross(const Vec3_s00b8_9a30& a, const Vec3_s00b8_9a30& b)
{
    return Vec3_s00b8_9a30(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
struct sp_vector_allocator { uint32_t mFlags; sp_vector_allocator() {} };
template <typename T>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    T* begin() { return mpBegin; }
    T& front() { return *mpBegin; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);                                            // 0x473890
    void DoInsertValue(T* position, const T& value);                     // 0x4b5ad0
    T* erase(T* first, T* last)
    {
        T* position = first;
        for (T* p = last; p != mpEnd; ++p, ++position)
            *position = *p;
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct cTerrainMapSet {
    char  pad00[0x34];
    float mRadius;      // +0x34
    float mMaxHeight;   // +0x38
    float mWaterHeight; // +0x3c
    float GetHeightAt(const Vec3_s00b8_9a30* p);                                    // 0xf927c0
};
struct ISphere {
virtual void a();
virtual void b();
virtual void c();
    virtual cTerrainMapSet* GetMap();                                    // slot 0xc
};
struct cPlanetModel {
    char     pad00[0x20];
    void*    mpSphere;     // +0x20
    ISphere* mpISphere;    // +0x24

    float GetWaterHeight()                                               // 0xb7e390
    {
        if (mpISphere != 0) {
            cTerrainMapSet* t = mpISphere->GetMap();
            return t->mWaterHeight * t->mMaxHeight + t->mRadius;
        }
        return 0.0f;
    }
    cTerrainMapSet* GetTerrain()
    {
        if (mpISphere != 0 && mpISphere->GetMap() != 0)
            return mpISphere->GetMap();
        return 0;
    }
    float GetRadius()                                                    // 0xb7e4d0
    {
        if (mpISphere != 0) {
            if (mpISphere->GetMap() != 0)
                return mpISphere->GetMap()->mRadius;
        }
        return 500.0f;
    }
    float GetHeightAt(const Vec3_s00b8_9a30& p)
    {
        if (mpSphere != 0)
            return mpISphere->GetMap()->GetHeightAt(&p);
        return GetRadius();
    }
};
cPlanetModel* __cdecl SP_PlanetModel_s00b8_9a30();                                  // 0xb3d350
struct cGameNounManager {
    void GetGameDataVector(void* a, void* b, void* c, void* d, void* e); // 0xb21340
};
cGameNounManager* __cdecl SP_NounManager();                              // 0xb3d300
struct TileKey {
    int x, y, z;
    bool operator==(const TileKey& b) const { return x == b.x && y == b.y && z == b.z; }
};
struct TileNode {
    TileKey     mKey;        // +0x00
    Vec3_s00b8_9a30        mPos;        // +0x0c
    signed char mLevel[4];   // +0x18 owner level per edge
    bool        mDone[4];    // +0x1c edge already traced
    TileNode*   mpNext;      // +0x20
};
struct TileIterator {
    TileNode*  mpNode;
    TileNode** mpBucket;
    TileIterator() {}
    TileIterator(const TileIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    explicit TileIterator(TileNode** pBucket) : mpNode(*pBucket), mpBucket(pBucket)
    {
        if (!mpNode)
            increment_bucket();
    }
    void increment_bucket()
    {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
struct TileMap {
    uint32_t   mUnk0;
    TileNode** mpBucketArray;   // +4
    uint32_t   mnBucketCount;   // +8
    TileIterator find(const TileKey& k);                                 // 0xb83af0
    TileNode* end_node() const { return mpBucketArray[mnBucketCount]; }
};
void __cdecl FUN_00b7e220(uint32_t face, TileKey* key, int* dx, int* dy); // 0xb7e220 cube-map step
struct cRefCounted {
    int mnRefCount;
    cRefCounted() { _InterlockedExchange((long*)&mnRefCount, 0); }
    virtual ~cRefCounted() {}
    void Release()
    {
        if (_InterlockedExchangeAdd((long*)&mnRefCount, -1) - 1 == 0) {
            _InterlockedExchange((long*)&mnRefCount, 1);
            delete this;
        }
    }
};
struct BoundsVec { void* mpBegin; void* mpEnd; void* mpCapacity; sp_vector_allocator mAllocator;
                   BoundsVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {} };
struct cNatlBounds_s00b8_9a30 : public cRefCounted {
    uint32_t  mUnk8;      // +0x08
    BoundsVec mStrips0;   // +0x0c
    BoundsVec mStrips1;   // +0x20
    BoundsVec mLevels;    // +0x34
    uint32_t  mUnk44;     // +0x44
    cNatlBounds_s00b8_9a30() : mUnk8(0) {}
    ~cNatlBounds_s00b8_9a30();
    void AddBoundary(const Vec3_s00b8_9a30* ground, const Vec3_s00b8_9a30* curve, int count, int level); // 0xb899b0
};
template <typename T>
struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr& operator=(T* pObject);                                // 0x8fd240
    T* operator->() const { return mpObject; }
    void reset0()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
};
struct cNatlBoundsBuilder {
    char  pad00[0xc];
    bool  mbBuilt;                         // +0x0c
    char  pad0d[0x24 - 0x0d];
    intrusive_ptr<cNatlBounds_s00b8_9a30> mpBounds;   // +0x24
    bool  mbEnabled;                       // +0x28

    void Build(TileMap* tiles);
};
// ---- items of slice s00b89a30 end

// ---- items of slice s00b8a760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned char g_cubeFaceAxes[];   // 0x014653b8: 4 bytes per face pair
struct TileKey_s00b8_a760 {
    int x, y, z;
};
struct TileValue {              // node + 0x0c
    Vec3        mPos;           // +0x00
    signed char mLevel[4];      // +0x0c zone id per texel around the vertex
    bool        mDone[4];       // +0x10 edge is not a border
};
struct TileNode_s00b8_a760 {
    TileKey_s00b8_a760     mKey;           // +0x00
    TileValue   mValue;         // +0x0c
    TileNode_s00b8_a760*   mpNext;         // +0x20
};
struct TileIterator_s00b8_a760 {
    TileNode_s00b8_a760*  mpNode;
    TileNode_s00b8_a760** mpBucket;
    TileIterator_s00b8_a760() {}
    explicit TileIterator_s00b8_a760(TileNode_s00b8_a760** pBucket) : mpNode(*pBucket), mpBucket(pBucket)
    {
        if (!mpNode)
            increment_bucket();
    }
    void increment_bucket()
    {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
struct TileMap_s00b8_a760 {
    uint32_t   mUnk0;
    TileNode_s00b8_a760** mpBucketArray;   // +4
    uint32_t   mnBucketCount;   // +8
    uint32_t   mnElementCount;  // +0xc
    TileValue& operator[](const TileKey_s00b8_a760& k);                              // 0xb85ca0
    void DoFreeNodes(TileNode_s00b8_a760** pBuckets, uint32_t n);                    // 0xb7f430
    TileNode_s00b8_a760* end_node() const { return mpBucketArray[mnBucketCount]; }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
};
namespace SP {
 int __cdecl WrapCubeFace(int size, int* face, int* x, int* y, int a, int b);   // 0x684ca0
}
struct CubeCell { int x, y, face; };
__forceinline void CubeVertexDirection(int face, float fx, float fy, float* v)
{
    const unsigned char* axes = &g_cubeFaceAxes[(face >> 1) * 4];
    float d = fy * fy; d += fx * fx; d += 1.0f; float inv = 1.0f / sqrtf(d);
    float s = inv;
    if (face & 1)
        s = -s;
    v[axes[0]] = s * fx;
    v[axes[1]] = inv * fy;
    v[axes[2]] = s;
}
inline float VertexCoord(int i) { return (float)i * 0.03125f - 1.0f; }
struct cTerrainMapSet_s00b8_a760 {
    char  pad00[0x34];
    float mRadius;      // +0x34
};
struct ISphere_s00b8_a760 {
virtual void a();
virtual void b();
virtual void c();
    virtual cTerrainMapSet_s00b8_a760* GetMap();           // slot 0xc
};
struct cNatlBoundsBuilder_s00b8_a760 {
    void Build(TileMap_s00b8_a760* tiles);                 // 0xb89a30
};
namespace SP {
class cPlanetModel_s00b8_a760 {
public:
    char     pad00[0x24];
    ISphere_s00b8_a760* mpISphere;                         // +0x24
    char     pad28[0x94 - 0x28];
    uint8_t* mPoliticalZoneIdxMap;              // +0x94
    char     pad98[0xa8 - 0x98];
    cNatlBoundsBuilder_s00b8_a760* mpNatlBoundsBuilder;    // +0xa8
    char     pada8[0xf4 - 0xac];
    TileMap_s00b8_a760  mTileMap;                          // +0xf4

    float GetRadius()
    {
        if (mpISphere != 0) {
            if (mpISphere->GetMap() != 0)
                return mpISphere->GetMap()->mRadius;
        }
        return 500.0f;
    }

    void RebuildPoliticalZones();               // 0x00b8a760
};  // namespace SP
}
// ---- items of slice s00b8a760 end

// ---- items of slice s00b8aea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_PoliticalZoneUpdateCount;      // 0x016881e4
extern int g_PoliticalZoneUpdateBusy;       // 0x016881e8
extern int g_PoliticalZoneUpdatePending;    // 0x016881ec
struct Vector3_s00b8_aea0 {
    float x, y, z;
    Vector3_s00b8_aea0() {}
    Vector3_s00b8_aea0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00b8_aea0(const Vector3_s00b8_aea0& v) { x = v.x; y = v.y; z = v.z; }
};
struct random_access_iterator_tag {};
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
inline void EASTLFree(void* p)
{
    if (p && ((int*)p)[-1] != 0)
        operator delete[](p);
}
struct CubeCellVector {
    CubeCell* mpBegin;
    CubeCell* mpEnd;
    CubeCell* mpCapacity;
    uint32_t mAllocator[2];
    ~CubeCellVector() { EASTLFree(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    CubeCell& operator[](int i) { return mpBegin[i]; }
    CubeCellVector& operator=(const CubeCellVector& x);                // 0x00b375f0
    void swap(CubeCellVector& x);                                      // 0x00b85190
    void reserve(uint32_t n);                                          // 0x00b84a60
    void DoInsertValue(CubeCell* position, const CubeCell& value);     // 0x00b535d0
    void DoInsertFromIterator(CubeCell* position, CubeCell* first, CubeCell* last,
                              random_access_iterator_tag);             // 0x00b84cb0
    void push_back(const CubeCell& value)
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) CubeCell(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    void insert(CubeCell* position, CubeCell* first, CubeCell* last)
    {
        DoInsertFromIterator(position, first, last, random_access_iterator_tag());
    }
    CubeCell* erase(CubeCell* first, CubeCell* last)
    {
        CubeCell* const position = first;
        CubeCell* d = first;
        for (CubeCell* s = last; s != mpEnd; ++s, ++d)
            *d = *s;
        mpEnd -= (last - first);
        return position;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct CubeCellVectorVector {
    CubeCellVector* mpBegin;
    CubeCellVector* mpEnd;
    CubeCellVector* mpCapacity;
    uint32_t mAllocator[2];
    CubeCellVectorVector(uint32_t n, const char& allocator);           // 0x00b85e10
    ~CubeCellVectorVector()
    {
        for (CubeCellVector* p = mpBegin; p < mpEnd; ++p)
            p->~CubeCellVector();
        EASTLFree(mpBegin);
    }
    CubeCellVector& operator[](int i) { return mpBegin[i]; }
};
struct FixedIDVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mOverflowAllocator;
    uint32_t* mpPoolBegin;
    uint32_t pad;
    uint32_t mBuffer[64];
    FixedIDVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 64;
    }
    ~FixedIDVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(uint32_t* position, const uint32_t& value);     // 0x004281d0
    void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) uint32_t(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
struct FixedVector3Vector {
    Vector3_s00b8_aea0* mpBegin;
    Vector3_s00b8_aea0* mpEnd;
    Vector3_s00b8_aea0* mpCapacity;
    uint32_t mOverflowAllocator;
    Vector3_s00b8_aea0* mpPoolBegin;
    uint32_t pad;
    __declspec(align(16)) float mBuffer[64 * 3];
    FixedVector3Vector()
    {
        mpPoolBegin = (Vector3_s00b8_aea0*)mBuffer;
        mpBegin = (Vector3_s00b8_aea0*)mBuffer;
        mpEnd = (Vector3_s00b8_aea0*)mBuffer;
        mpCapacity = (Vector3_s00b8_aea0*)mBuffer + 64;
    }
    ~FixedVector3Vector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(Vector3_s00b8_aea0* position, const Vector3_s00b8_aea0& value);       // 0x00ac4720
    void push_back(const Vector3_s00b8_aea0& value)
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) Vector3_s00b8_aea0(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
template <uint32_t n>
struct MaskVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    MaskVector()
    {
        mpBegin = (uint32_t*)new ("Simulator", 0, 0, kAllocatorFile, 0xd1) char[n * sizeof(uint32_t)];
        uint32_t* q = mpBegin;
        for (uint32_t i = n; i != 0; --i)
            *q++ = 0;
        mpEnd = mpBegin + n;
        mpCapacity = mpBegin + n;
    }
    ~MaskVector() { EASTLFree(mpBegin); }
};
namespace SP {
int WrapCubeFace(int size, int* face, int* x, int* y, int* rot, int* flip);   // 0x00684ca0
}
__forceinline void CubeTexelDirection(int face, float fx, float fy, float* v)
{
    const unsigned char* axes = &g_cubeFaceAxes[(face >> 1) * 4];
    float inv = 1.0f / sqrtf(fx * fx + fy * fy + 1.0f);
    float s = inv;
    if (face & 1)
        s = -s;
    v[axes[0]] = s * fx;
    v[axes[1]] = inv * fy;
    v[axes[2]] = s;
}
inline float TexelCoord(int i) { return ((float)i + 0.5f) * 0.03125f - 1.0f; }
namespace SP {
struct cPoliticalZone_s00b8_aea0 {
    uint32_t mPoliticalID;      // 0x00
    Vector3_s00b8_aea0 mCenter;            // 0x04
    bool mCityZone;             // 0x10
    bool mVisible;              // 0x11
    uint32_t mpCity;            // 0x14
};
}
namespace SP {
class cPlanetModel_s00b8_aea0 {
public:
    uint32_t pad00[0x50 / 4];
    uint32_t* mContinentAreasBegin;     // 0x50
    uint32_t* mContinentAreasEnd;       // 0x54
    uint32_t pad58[(0x64 - 0x58) / 4];
    bool* mContinentFlags;              // 0x64
    uint32_t pad68[(0x80 - 0x68) / 4];
    cPoliticalZone_s00b8_aea0* mPoliticalZonesBegin;   // 0x80
    cPoliticalZone_s00b8_aea0* mPoliticalZonesEnd;     // 0x84
    uint32_t pad88[(0x94 - 0x88) / 4];
    uint8_t* mPoliticalZoneIdxMap;      // 0x94

    int GetContinent(const Vector3_s00b8_aea0* pos);   // 0x00b88590
    void RebuildPoliticalZones();           // 0x00b8a760
    void BuildPoliticalZoneMap();
};
}
// ---- items of slice s00b8aea0 end

// ---- items of slice s00b8d190 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct cHandlerHost {
    PV(0)  PV(1)  PV(2)  PV(3)  PV(4)  PV(5)  PV(6)  PV(7)  PV(8)  PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42)
    virtual void v43();                                   // +0xac
};
struct cCursorHost {
    PV(0)  PV(1)  PV(2)  PV(3)  PV(4)  PV(5)  PV(6)  PV(7)  PV(8)  PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void v35(uint32_t value);                     // +0x8c
};
struct cKey3 {                                            // three-word property key
    uint32_t m0;                                          // +0x00
    uint32_t m4;                                          // +0x04
    uint32_t m8;                                          // +0x08
    cKey3() : m0(0), m4(0), m8(0) {}
};
struct cPlanetModel_s00b8_d190 {
    uint8_t  mPad00[0x20];                                // +0x000
    cHandlerHost* mField20;                               // +0x020
    cCursorHost*  mField24;                               // +0x024
    int32_t  mField28;                                    // +0x028
    uint32_t mField2C;                                    // +0x02c
    uint8_t  mPad30[0x48];                                // +0x030
    uint8_t  mField78;                                    // +0x078
    uint8_t  mPad79[0x5b];                                // +0x079
    char*    mFieldD4;                                    // +0x0d4
    char*    mFieldD8;                                    // +0x0d8
    char*    mFieldDC;                                    // +0x0dc
    uint8_t  mPadE0[0x0a];                                // +0x0e0
    uint8_t  mFieldEA;                                    // +0x0ea
    uint8_t  mPadEB;                                      // +0x0eb
    int32_t  mFieldEC;                                    // +0x0ec
    uint8_t  mPadF0[0x44];                                // +0x0f0
    char*    mField134;                                   // +0x134
    char*    mField138;                                   // +0x138
    uint8_t  mPad13C[0x20];                               // +0x13c
    char*    mField15C;                                   // +0x15c
    char*    mField160;                                   // +0x160
    uint8_t  mPad164[0x0c];                               // +0x164
    char*    mField170;                                   // +0x170
    char*    mField174;                                   // +0x174
    uint8_t  mPad178[0x0c];                               // +0x178
    uint32_t mField184;                                   // +0x184
    uint8_t  mPad188[0x0c];                               // +0x188
    int32_t  mField194;                                   // +0x194
    uint8_t  mPad198[0x0c];                               // +0x198
    uint32_t mField1A4;                                   // +0x1a4
    uint32_t mField1A8;                                   // +0x1a8
    uint32_t mField1AC;                                   // +0x1ac

    void  UpdateMinimap(int32_t a, int32_t b, int32_t c);  // 0x00b8c330
    void  FUN_00b8c0f0();                                  // 0x00b8c0f0
    bool  HandleMessage(uint32_t id, void* msg);           // 0x00b8d2a0
    void  FUN_00b8d2f0();                                  // 0x00b8d2f0
    bool  FUN_00b8d750(uint32_t a, uint32_t b);            // 0x00b8d750
    bool  FUN_00b8d8a0(uint32_t a, bool refresh, uint32_t c); // 0x00b8d8a0
    uint32_t FUN_00b8d8f0();                               // 0x00b8d8f0
    void  FUN_00b8d910();                                  // 0x00b8d910
    void  FUN_00b8d920(bool flag);                         // 0x00b8d920
    void  FUN_00b8d950(bool flag);                         // 0x00b8d950
    void  FUN_00b8d980(bool flag);                         // 0x00b8d980
    int32_t FUN_00b8d9b0();                                // 0x00b8d9b0
    bool  FUN_00b8d9f0();                                  // 0x00b8d9f0
    int32_t FUN_00b8da70();                                // 0x00b8da70
    cKey3* FUN_00b8dd60(cKey3* out);                       // 0x00b8dd60
    void  FUN_00b8dde0(cKey3* key, int32_t unused);        // 0x00b8dde0
    void  FUN_00b8de60();                                  // 0x00b8de60
    int32_t FUN_00b8dec0(int32_t index);                   // 0x00b8dec0
    int32_t FUN_00b8def0(int32_t index);                   // 0x00b8def0
    void  FUN_00b8df20();                                  // 0x00b8df20
    void  FUN_00b8df80(int32_t index);                     // 0x00b8df80
    void  FUN_00b8dfe0(int32_t index);                     // 0x00b8dfe0
    bool  FUN_00b8e040(uint32_t id);                       // 0x00b8e040
    cKey3* FUN_00b8e090();                                 // 0x00b8e090
};
// ---- items of slice s00b8d190 end

// ---- items of slice s00472b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char* p);                          // inlined (intrinsic)
#pragma intrinsic(strlen)
void* EASTL_Allocate(void* alloc, uint32_t n, uint32_t align, uint32_t flags); // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                                      // @ 0x00f47380
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct sp_vector_allocator_s0047_2b80 {
    uint32_t mDummy;
    void deallocate(void* p, uint32_t) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct Counted { void Release(); };                                  // 0x40f360
struct AutoRefCount {
    Counted* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct Pod12 { float x, y, z; };                                     // 12-byte POD
template<class T> struct ResizeHoles { enum { N = 6 }; };
template<> struct ResizeHoles<AutoRefCount> { enum { N = 15 }; };
template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* dest);   // out of line
template<class T> inline void destruct(T* first, T* last)
{ for (; first < last; ++first) first->~T(); }
template<class T> inline T* CopyRef(T* first, T* last, T* dest)
{
    const bool from = false, left = false, pos = false;
    { uint32_t unused[2]; }
    T* pSource = first;
    T* pDest = dest;
    for (; pSource != last; ++pSource, ++pDest) *pDest = *pSource;
    return pDest;
}
template<class T, int A>
struct vector_s0047_2b80 {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator_s0047_2b80 mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p && ((int*)p)[-1]) mAllocator.deallocate(p, n); }

    void DoInsertValues(T* pos, uint32_t n, const T& v);   // out of line
    void erase(T* first, T* last);                         // out of line 0x00621f50
    void insert(T* pos, uint32_t n, const T& v) { DoInsertValues(pos, n, v); }

    vector_s0047_2b80& operator=(const vector_s0047_2b80& x);
    T* DoRealloc(uint32_t n, T* first, T* last);           // out of line
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);
    void resize(uint32_t n);
};
template<class T, int A>
vector_s0047_2b80<T,A>& vector_s0047_2b80<T,A>::operator=(const vector_s0047_2b80& x)
{
    if (&x != this) {
        const uint32_t n = x.size();
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            T* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            ScratchSlots<9>();
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if (n > size()) {
            CopyRef(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            uninitialized_copy_ptr(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<8>();
        } else {
            T* const position = CopyRef(x.mpBegin, x.mpEnd, mpBegin);
            destruct(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
template<class T, int A>
void vector_s0047_2b80<T,A>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        const int nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}
template<class T, int A>
void vector_s0047_2b80<T,A>::resize(uint32_t n)
{
    if (n > size()) {
        insert(mpEnd, n - size(), T());
        ScratchSlots<ResizeHoles<T>::N>();
    } else
        erase(mpBegin + n, mpEnd);
}
// ---- items of slice s00472b80 end

// ---- items of slice s00b7ea80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_016881f0, DAT_016881f4, DAT_016881f8;
#define VTC(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
struct Quat { float x, y, z, w; };
struct S18 { int a; float b, c, d; char e; char f; int g; };  // +0x12..+0x13 implicit padding
struct S24a { float a, b, c, d; int e; float f, g, h; int i; };
struct S24b { float a, b, c, d, e, f; int g; float h, i; };
struct cTerrainMapSet_s00b7_ea80 {
    float GetFloat(float* uv);                                   // SP::cTerrainMap<unsigned>::GetFloat 0x00f88650
    float GetHeightAt();                                         // cTerrainMapSet::GetHeightAt 0x00f927c0
};
struct cTerrainData {
    void        FUN_00f92c20(Vec3* out, const Vec3* dir);   // 0x00f92c20 surface normal of a direction
};
struct cPlanetModel_s00b7_ea80 {
    char  pad0[0x1c];
    int   f1c;           // +0x1c
    void* mpSphere;      // +0x20
    void* mpISphere;     // +0x24
    float f28;           // +0x28
    char  pad1[0x94 - 0x2c];
    int   f94;           // +0x94
    char  pad2[0xec - 0x98];
    int   fec;           // +0xec

    int   FUN_ea80(const Vec3* v);                    // 0x00b7ea80
    float FUN_ec50();                                 // 0x00b7ec50
    float FUN_ecc0(const Vec3* v);                    // 0x00b7ecc0
    void  FUN_ee70(Vec3* out, Vec3* in);              // 0x00b7ee70
    float GetRadiusAt(unsigned coords);               // 0x00b7ef70
    float FUN_efe0(float p);                          // 0x00b7efe0
    void  FUN_f060(Vec3* out, const Vec3* v, float* frac); // 0x00b7f060
    char  FUN_00b7e3e0(const Vec3* v);                // 0x00b7e3e0
    int   FUN_00b7f4a0(unsigned n);                   // 0x00b7f4a0
    void  FUN_f390(int v);                            // 0x00b7f390
    void  FUN_f510(unsigned n);                       // 0x00b7f510

    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* a);                     // 0x00b7f190
    Quat* BuildSurfaceOrientation_2(Quat* out, const Vec3* a, const Vec3* b);    // 0x00b7f1f0
    Quat* BuildSurfaceOrientation2(Quat* out, const Vec3* a, const Vec3* b);     // 0x00b7f250
    Quat* BuildPitchedSurfaceOrientation(Quat* out, const Vec3* a, const Vec3* b, float c); // 0x00b7f2b0
    Quat* BuildSurfaceNormalOrientation(Quat* out, const Vec3* a, const Vec3* b, float c);  // 0x00b7f320
};
// ---- items of slice s00b7ea80 end

// ---- items of slice s00b815a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_0167ecd0;
typedef unsigned int uint;
struct RadialRay {
    float pos[4];                          // +0x00
    float h0, h1;                          // +0x10, +0x14
};
struct RayHitResult {
    int   status;                          // +0x00
    int   pad04[3];                        // +0x04
    float pos[4];                          // +0x10
    void* normalOut;                       // +0x20
    void* distOut;                         // +0x24
    void* userData;                        // +0x28
    void* entity;                          // +0x2c
};
float* FUN_0059aed0(float* out, const float* a, const float* b);    // 0x0059aed0
int   FUN_00b3d310();                                                // 0x00b3d310
void  FUN_00b65b10(const RadialRay* ray, void* world, void* obj, bool useWorld, unsigned int filterInfo, RayHitResult* out); // 0x00b65b10
struct cPlanetModel_s00b8_15a0 {
    char  pad0[0x20];
    void* mpSphere;      // +0x20
    void* mpISphere;     // +0x24
    float f28;           // +0x28
    char  pad1[0xf0 - 0x2c];
    char  f0;            // +0xf0

    long double GetRadiusAt(uint coords);                            // 0x00b7ef70
    void  DirectionToSurfacePosition(Vec3* out, const Vec3* dir);    // 0x00b815a0
    void  FUN_00b81630(Vec3* out, const Vec3* dir);                  // 0x00b81630
    Vec3* FUN_00b816f0(Vec3* out, const Vec3* dir);                  // 0x00b816f0
    void  FUN_00b81720(Vec3* out);                                   // 0x00b81720
    void  MakeRandomWorldPosition(Vec3* out, const Vec3* dir, float a, float b); // 0x00b81780
    void  FUN_00b81a40(Vec3* out, const Vec3* dir, float a, float b);            // 0x00b81a40
    void  FUN_00b81c80(Vec3* out, const Vec3* a, const Vec3* b, float s);        // 0x00b81c80
    int   IsPositionBelowSurface(const Vec3* dir);                   // 0x00b81f90
    Vec3* FUN_00b82060(Vec3* out, int a, int b);                     // 0x00b82060
    void  FUN_00b82110(Vec3* out, Vec3* a, Vec3* b);                 // 0x00b82110
    long double FUN_00b82310(void* param);                           // 0x00b82310
};
// ---- items of slice s00b815a0 end

// ---- items of slice s00b832d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kSpiralMaxAngle;             // 0x01688274
extern const float kBasis9[9];                  // 0x01688284
extern const float kNoTerrain;                  // 0x0156b624
extern const float kHeightUnit;                 // 0x0140d4f8
#pragma warning(disable: 4100)
struct Vec3POD { float x, y, z; };
struct cTerrainMapSet_s00b8_32d0 {
    char pad0[0x34];
    float f34;                                  // mRadius
    float f38;                                  // mMaxHeight
    float f3c;                                  // mWaterHeight
    float GetHeightAt(const Vec3POD* pos);      // 0x00f927c0, thiscall ret 4
};
struct cITerrainSphere {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual cTerrainMapSet_s00b8_32d0* s3();               // +0xC
};
struct cPlanetModel_s00b8_32d0 {
    char pad0[0x20];
    void* mpSphere;                             // +0x20
    cITerrainSphere* mpISphere;                 // +0x24
    char pad1[0x4c - 0x28];
    void* mpContinentMap;                       // +0x4c
    char pad2[0x7c - 0x50];
    void* mpBitmap;                             // +0x7c
    char pad3[0xf0 - 0x80];
    char mFlagF0;                               // +0xf0

    bool FUN_00b832d0(const float* dir, float step);  // 0x00b832d0 (cPlanetModel::FUN_00b832d0)
    float FUN_00b83620(int a, float b);  // 0x00b83620 (cPlanetModel::FUN_00b83620)
    uint FUN_00b83870(int arg);  // 0x00b83870 (cPlanetModel::FUN_00b83870)
    void FUN_00b83c40(const float* dir, float radius, uint flags, char (*cb)(float*));
    void MakeRandomWorldPosition(Vec3POD* out, int a, float b, float c);  // 0x00b81780 (cPlanetModel::MakeRandomWorldPosition)
};
cPlanetModel_s00b8_32d0* PlanetModel_s00b8_32d0();                    // 0x00b3d350, cdecl
void QuaternionFromDirections(float* out, const float* a, const float* b); // 0x698180, cdecl
void FUN_00ac1510(unsigned x, unsigned y, unsigned z, float* out);         // 0x00ac1510, cdecl
void* PropertyManager();                        // 0x67de30, cdecl
void* MessageServer();                          // 0x67dcc0, cdecl
extern const Vec3POD kQuatRef;                  // 0x01688278
struct HashTableA {
    char pad0[4];
    int* table;      // +4
    uint size;       // +8
    int** Find(int** out, int* key);
};
struct MessageBasicRC5 {
    void* vftable;          // +0
    int mRefCount;          // +4
    int mId;                // +8
    int mFieldC;            // +0xc
    int mField10;           // +0x10
    int mField14;           // +0x14
    int mField18;           // +0x18
    int mField1c;           // +0x1c
};
struct ColorVector {
    char pad0[0x80];
    int mBegin;             // +0x80
    int mEnd;               // +0x84
    char pad2[0xa8 - 0x88];
    void* mOwner;           // +0xa8
    void DoInsertValue(uint index, uint value, int param4);
};
// ---- items of slice s00b832d0 end

// ---- items of slice s00b84270 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char kEventModifierVtbl;   // 0x013ef094
void* __cdecl operator_new_eastl(unsigned int size, const char* name, int flags, int align,
                                 const char* file, int line);   // 0x00f473a0
void __cdecl operator_delete_eastl(void* p);                    // 0x00f47380
void* __cdecl MemCpy(void* dst, const void* src, unsigned int n);  // 0x011e0744
struct U16Vec {
    uint16_t* mpBegin;      // +0x00
    uint16_t* mpEnd;        // +0x04
    uint16_t* mpCapacity;   // +0x08
    int mAllocator[2];      // +0x0c

    void Reserve(unsigned int n);
};
struct Vec14 {
    void* mpBegin;     // +0x00
    void* mpEnd;       // +0x04
    void* mpCapacity;  // +0x08
    int   mAllocator[2];

    void Copy(const Vec14& other);   // 0x00473460
};
struct Elem1C {
    uint32_t mA;    // +0x00
    uint32_t mB;    // +0x04
    Vec14    mVec;  // +0x08
};
struct IntVector {
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpCapacity;   // +0x08
    int mAllocator[2];      // +0x0c

    void Free()
    {
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_eastl(mpBegin);
    }

    ~IntVector() { Free(); }
};
struct IntVectorVec {
    IntVector* mpBegin;      // +0x00
    IntVector* mpEnd;        // +0x04
    IntVector* mpCapacity;   // +0x08
    int mAllocator[2];       // +0x0c

    void DestroyRange(void* first, void* last);   // 0x01023030

    ~IntVectorVec()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_eastl(mpBegin);
    }
};
struct EventModifier {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct ScalarList {
    void* mpVtbl;            // +0x00
    int   m04;               // +0x04
    EventModifier* mp08;     // +0x08
    IntVectorVec mVec0c;     // +0x0c
    IntVectorVec mVec20;     // +0x20
    IntVector mVec34;        // +0x34

    void Dtor();
};
// ---- items of slice s00b84270 end

// ---- items of slice s00b87dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl MemMove(void* dst, const void* src, unsigned int n);   // 0x011e0744 (memcpy thunk)
namespace SP {
uint16_t __cdecl FloatToHeight16(float v);                                       // 0x00b7e680
}
namespace SP {
struct UnionFind {
  uint16_t* mpBegin;
  uint16_t* mpEnd;
  uint16_t* mpCapacity;
  UnionFind() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~UnionFind()
  {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      operator_delete__(mpBegin);
  }
  void reserve(unsigned int n);                       // 0x00b849e0, ret 4
  uint16_t Union(uint32_t a, uint32_t b);             // 0x00b7e6f0, ret 8
  int Flatten(int limit, uint32_t seed);              // 0x00b7e790, ret 8
};
}
namespace SP {
struct ByteVector {
  uint8_t* mpBegin;
  uint8_t* mpEnd;
  uint8_t* mpCapacity;
  void DoInsertValues(uint8_t* pos, unsigned int n, const uint8_t* value);   // 0x005151b0, ret 0xc
  __forceinline void resize(unsigned int n)
  {
    const unsigned int sz = (unsigned int)(mpEnd - mpBegin);
    if (n > sz) {
      uint8_t fill = 0;
      DoInsertValues(mpEnd, n - sz, &fill);
    } else {
      uint8_t* first = mpBegin + n;
      uint8_t* last = mpEnd;
      MemMove(first, last, (unsigned int)(mpEnd - last));
      mpEnd = mpEnd + (first - last);
    }
  }
};
}
namespace SP {
struct UIntVector {
  uint32_t* mpBegin;
  uint32_t* mpEnd;
  uint32_t* mpCapacity;
  void DoInsertValues(uint32_t* pos, unsigned int n, const uint32_t* value);   // 0x004cea40, ret 0xc
  __forceinline void clear()
  {
    uint32_t* first = mpBegin;
    uint32_t* last = mpEnd;
    MemMove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
    mpEnd = (uint32_t*)((char*)mpEnd + (first - last) * 4);
  }
  __forceinline void resize(unsigned int n)
  {
    const unsigned int sz = (unsigned int)(mpEnd - mpBegin);
    if (n > sz) {
      uint32_t fill = 0;
      DoInsertValues(mpEnd, n - sz, &fill);
    } else {
      uint32_t* first = mpBegin + n;
      uint32_t* last = mpEnd;
      MemMove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
      mpEnd = (uint32_t*)((char*)mpEnd + (first - last) * 4);
    }
  }
};
}
namespace SP {
struct cTerrainHeights {
  char pad[0x10];
  uint8_t* mpData;          // +0x10: 4 uint16 samples per cell quad, 0x1000 bytes per cell row
};
}
namespace SP {
class cTerrainMap { public:
  char pad[8];
  cTerrainHeights* mpHeights;   // +8
  float GetWaterLevel();        // 0x00b7e0a0: fld [this+0x3c]
};
}
namespace SP {
class cTerrainSphere_s00b8_7dc0 { public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual cTerrainMap* GetMap();   // slot 3
};
}
namespace SP {
struct Vector3_s00b8_7dc0 {
  float x, y, z;
};
}
namespace SP {
struct Element20 {
  uint32_t mData[5];
  Element20(const Element20& o);                  // 0x473460 (eastl::vector<cSPVector3> copy ctor)
  Element20& operator=(const Element20& o);       // 0x473500
};
}
namespace SP {
void FUN_00b85980(Element20* first, Element20* last, Element20* dest);   // 0x00b85980
}
namespace SP {
struct Vector20 {
  Element20* mpBegin;
  Element20* mpEnd;
  Element20* mpCapacity;
  void insert(Element20* pos, const Element20* value);   // 0x00b88430, ret 8
};
}
namespace SP {
void* operator new[](unsigned int size, const char* name, int flags,
                     unsigned int debugFlags, const char* file, int line); // 0x00f473a0
}
namespace SP {
class cPlanetModel_s00b8_7dc0 {
 public:
  void ComputeContinents();
  void Refresh();                                       // 0x00b88420
  uint32_t GetCellValue(const Vector3_s00b8_7dc0* dir);            // 0x00b88590

  char pad00[0x24];
  cTerrainSphere_s00b8_7dc0* mpISphere;              // +0x24
  char pad28[0x4c - 0x28];
  uint32_t* mContinentMap;                // +0x4c  (6 * 128 * 128 cells)
  UIntVector mContinentAreas;             // +0x50
  char pad5c[0x64 - 0x5c];
  ByteVector mContinentAboveWater;        // +0x64
  char pad70[0x78 - 0x70];
  bool mContinentMapDirty;                // +0x78
  char pad79[3];
  uint8_t* mCellNibbles;                  // +0x7c  (one nibble per cell)
};
}
// ---- items of slice s00b87dc0 end

// ---- items of slice s00b8bb70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SVector3 {
    float x, y, z;
};
class RCSub {
public:
    virtual void Del(int);
    volatile long mnRefCount;                  // +0x04
    long Release()
    {
        long n = _InterlockedDecrement(&mnRefCount);
        if (n == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            if (this)
                Del(1);
        }
        return n;
    }
};
class cMinimapGfx {
public:
    char     pad00[0x0c];
    bool     mbDirty;                          // +0x0c
    char     pad0d[0x24 - 0x0d];
    RCSub*   mpRefObject;                      // +0x24
    bool     mbActive;                         // +0x28
};
class cPlanet {
public:
    void SetRampEnabled(bool bEnabled);        // 0x00fbd6b0
};
class IWorldEditor {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual cPlanet* v10();                    // +0x10
virtual void v14();
virtual void v18();
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
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAC();
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
virtual void vD8();
virtual void vDC();
virtual void vE0();
virtual void vE4();
virtual void vE8();
virtual void vEC();
virtual void vF0();
virtual void vF4();
virtual void vF8();
virtual void vFC();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10C();
    virtual void ShutdownScene();              // +0x110
};
class IPlanetSphere {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
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
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void SetInputManager(void* pManager);        // +0x90
virtual void v94();
virtual void v98();
virtual void v9c();
    virtual void vA0();
    virtual void vA4();                        // +0xa4
    virtual void vA8();
    virtual void vAC();                        // +0xac
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
virtual void vD8();
virtual void vDC();
virtual void vE0();
virtual void vE4();
virtual void vE8();
    virtual void vEC();                        // +0xec
virtual void vF0();
virtual void vF4();
    virtual void vF8();                        // +0xf8
};
struct CityPair {
    void* mpFirst;
    void* mpSecond;
};
struct LandRoute {
    uint8_t mData[0x1c];
};
class CityPairVector {
public:
    CityPair* mpBegin;                         // +0x00
    CityPair* mpEnd;                           // +0x04
    CityPair* mpCapacity;                      // +0x08
    uint32_t  mAllocator;                      // +0x0c
    void EraseRange(CityPair* pFirst, CityPair* pLast);        // 0x00d018d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};
class LandRouteVector {
public:
    LandRoute* mpBegin;                        // +0x00
    LandRoute* mpEnd;                          // +0x04
    LandRoute* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
    void EraseRange(LandRoute* pFirst, LandRoute* pLast);      // 0x00b897d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};
class cCivilization {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
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
virtual void v44();
virtual void v48();
    virtual int GetID();                       // +0x4c
};
class IPositionSource {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const SVector3* GetPosition();     // +0x2c
};
class cCity {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
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
virtual void v44();
virtual void v48();
    virtual int GetOwnerID(bool bPrimary);     // +0x4c
    char              pad04[0x34 - 0x04];
    IPositionSource   mNodeValue;              // +0x34
    char              pad38[0x120 - 0x38];
    IPositionSource   mPosition;               // +0x120
    cCivilization*    GetCivilization();       // 0x00bd9bf0
};
struct GraphNodeValue {
    uint32_t mValue[3];
};
struct GraphNode {
    int32_t         mnID;                      // +0x00
    GraphNodeValue  mValue;                    // +0x04
    bool            mbResourceNode;            // +0x10
    bool            mbDirty;                   // +0x11
    uint16_t        pad12;
    cCity*          mpCity;                    // +0x14
};
class GraphNodeVector {
public:
    GraphNode* mpBegin;                        // +0x00
    GraphNode* mpEnd;                          // +0x04
    GraphNode* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
};
struct IVec3U {
    uint32_t mX, mY, mZ;
    IVec3U() {}
    IVec3U(uint32_t x, uint32_t y, uint32_t z) : mX(x), mY(y), mZ(z) {}
};
class cPlanetModel_s00b8_bb70 {
public:
    char            pad00[0x20];
    IWorldEditor*   mpWorldEditor;             // +0x20
    IPlanetSphere*  mpISphere;                 // +0x24
    char            pad28[0x2c - 0x28];
    IVec3U          mField2C;                  // +0x2c
    uint16_t*       mpIndexBegin;              // +0x38
    uint16_t*       mpIndexEnd;                // +0x3c
    char            pad40[0x48 - 0x40];
    bool            mbRegistered;              // +0x48
    char            pad49[0x4c - 0x49];
    uint32_t*       mContinentMap;             // +0x4c
    char            pad50[0x64 - 0x50];
    uint8_t*        mContinentAboveWater;      // +0x64
    char            pad68[0x7c - 0x68];
    uint32_t*       mpCellNibbles;             // +0x7c
    GraphNodeVector mNodes;                    // +0x80
    char            pad90[0x94 - 0x90];
    uint8_t*        mpZoneMap;                 // +0x94
    uint8_t*        mpZoneMapEnd;              // +0x98
    char            pad9c[0xa8 - 0x9c];
    cMinimapGfx*    mpMinimapGfx;              // +0xa8
    CityPairVector  mSeaTradeRoutes;           // +0xac
    char            padBC[0xc0 - 0xbc];
    CityPairVector  mLandTradeRoutes;          // +0xc0
    char            padD0[0xd4 - 0xd0];
    LandRouteVector mPathRoutes;               // +0xd4
    char            padE4[0xe8 - 0xe4];
    bool            mbSeaRoutesDirty;          // +0xe8
    bool            mbLandRoutesDirty;         // +0xe9
    bool            mbPathRoutesDirty;         // +0xea

    bool RayCast(const SVector3* pOrigin, float fDirection, SVector3* pOut,
                 float fRadius, bool bLayer, uint32_t nMask);          // 0x00b88770
    bool FindClosestWater(const SVector3* pOrigin, float fDirection,
                          SVector3* pOut);                             // 0x00b8bb70
    void Reset();                                                      // 0x00b87bb0
    int  AddNode(const SVector3* pValue, bool bResourceNode);          // 0x00b86500
    void SetNodeFlag(int nIndex, bool bValue);                         // 0x00b7ea30
    void SetNodeID(int nIndex, int nValue);                            // 0x00b841a0
    int  GetContinent(const SVector3* pPosition);                      // 0x00b88590
    void BuildPoliticalZoneMap();                                      // 0x00b8aea0
    void Shutdown();                                                   // 0x00b8c0f0
    void AddResourceNodes();                                           // 0x00b8bba0
};
// ---- items of slice s00b8bb70 end

// ---- items of slice s00b84270_g8 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00b8_4270__g8 {
    float x, y, z;
};
struct cTerrainMapSet_s00b8_4270__g8 {
    char  pad00[0x34];
    float mRadius;          // +0x34
    float mMaxHeight;       // +0x38
    float mWaterHeight;     // +0x3c
    float GetHeightAt(const Vector3_s00b8_4270__g8& p);                    // 0x00f927c0
};
struct ISphere_s00b8_4270__g8 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual cTerrainMapSet_s00b8_4270__g8* GetMap();                       // slot +0x0c
};
struct cPlanetModel_s00b8_4270__g8 {
    char      pad00[0x20];
    void*     mpSphere;     // +0x20
    ISphere_s00b8_4270__g8*  mpISphere;    // +0x24
    float GetRadiusAt(const Vector3_s00b8_4270__g8& p);                    // 0x00b7ef70
    void  FindSurfacePosition(Vector3_s00b8_4270__g8* out);                // 0x00b84730
};
void RandomDirection3(Vector3_s00b8_4270__g8* out);                       // 0x00b7e560
extern Vector3_s00b8_4270__g8 gNoSurfacePosition;                          // 0x016881f0
// ---- items of slice s00b84270_g8 end

// @ 0x00473500
template vector_s0047_2b80<Pod12, 4>& vector_s0047_2b80<Pod12, 4>::operator=(const vector_s0047_2b80<Pod12, 4>&)
;

// @ 0x00473890
template void vector_s0047_2b80<Pod12, 4>::reserve(uint32_t)
;

// @ 0x00b7ea80
#pragma optimize("s", on)
int cPlanetModel_s00b7_ea80::FUN_ea80(const Vec3* v)
{
    float x = v->x, ax = fabsf(x);
    float y = v->y, ay = fabsf(y);
    float z = v->z, az = fabsf(z);
    int i7, i8, i9;
    if (az < ax || az < ay) {
        if (ay < ax) {
            i7 = (int)((y / x + 1.0f) * 32.0f);
            i8 = (int)((z / ax + 1.0f) * 32.0f);
            i9 = (x < 0.0f) ? 3 : 2;
        } else {
            i7 = (int)((z / y + 1.0f) * 32.0f);
            i8 = (int)((x / ay + 1.0f) * 32.0f);
            i9 = (y < 0.0f) ? 5 : 4;
        }
    } else {
        i7 = (int)((x / z + 1.0f) * 32.0f);
        i8 = (int)((y / az + 1.0f) * 32.0f);
        i9 = (z < 0.0f) ? 1 : 0;
    }
    if (i7 == 0x40) i7 = 0x3f;
    if (i8 == 0x40) i8 = 0x3f;
    return (int)*(char*)((i9 * 0x40 + i8) * 0x40 + f94 + i7);
}
#pragma optimize("t", on)

// @ 0x00b7ecc0
float cPlanetModel_s00b7_ea80::FUN_ecc0(const Vec3* v)
{
    int m0 = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
    void* map = *(void**)(m0 + 0xc);
    float f1 = v->x, f2 = v->y, f3 = v->z;
    float a1 = fabsf(f1), a2 = fabsf(f2), a3 = fabsf(f3);
    // cube-face UV sample: u, v and the face index live in one 12-byte record
    struct CubeUV { float u, v; int face; } uv;
    if (a3 >= a1 && a3 >= a2) {
        uv.u = (f1 / f3 + 1.0f) * 0.5f;
        uv.v = (f2 / a3 + 1.0f) * 0.5f;
        uv.face = (f3 < 0.0f) ? 1 : 0;
    } else if (a2 >= a1) {
        uv.u = (f3 / f2 + 1.0f) * 0.5f;
        uv.v = (f1 / a2 + 1.0f) * 0.5f;
        uv.face = (f2 < 0.0f) ? 5 : 4;
    } else {
        uv.u = (f2 / f1 + 1.0f) * 0.5f;
        uv.v = (f3 / a1 + 1.0f) * 0.5f;
        uv.face = (f1 < 0.0f) ? 3 : 2;
    }
    int m1 = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
    float h = *(float*)(m1 + 0x38);
    float r = ((cTerrainMapSet_s00b7_ea80*)map)->GetFloat((float*)&uv);
    return r * h;
}

// @ 0x00b7ee70
void cPlanetModel_s00b7_ea80::FUN_ee70(Vec3* out, Vec3* in)
{
    Vec3 n;
    cTerrainData* d = (cTerrainData*)((void*(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
    d->FUN_00f92c20(&n, in);          // surface normal of `in`
    float x = in->x, y = in->y, z = in->z;
    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
    float nx = n.x, ny = n.y, nz = n.z;
    float a = ny * (inv * z) - nz * (inv * y);
    float b = nx * (inv * y) - ny * (x * inv);
    float c = nz * (x * inv) - nx * (inv * z);
    out->x = c * nz - b * ny;
    out->y = b * nx - nz * a;
    out->z = ny * a - c * nx;
}

// @ 0x00b7ef70
float cPlanetModel_s00b7_ea80::GetRadiusAt(unsigned coords)
{
    if (mpSphere) {
        cTerrainMapSet_s00b7_ea80* map = (cTerrainMapSet_s00b7_ea80*)((void*(__thiscall*)(void*, unsigned))VTC(mpISphere, 0xc))(mpISphere, coords);
        return map->GetHeightAt();
    }
    if (mpISphere) {
        int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        if (m) {
            int m2 = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
            float r = *(float*)(m2 + 0x34);
            return r;
        }
    }
    float r = 500.0f;
    return r;
}

// @ 0x00b7f060
void cPlanetModel_s00b7_ea80::FUN_f060(Vec3* out, const Vec3* v, float* frac)
{
    void* s = mpISphere;
    int m = ((int(__thiscall*)(void*))VTC(s, 0xc))(s);
    float lo = *(float*)(m + 0x48);
    float hi = *(float*)(m + 0x4c);
    float r = FUN_ecc0(v);
    if (lo < r && !FUN_00b7e3e0(v)) {
        *frac = (r - lo) / (hi - lo);
        Vec3 n;
        FUN_ee70(&n, (Vec3*)v);
        float inv = 1.0f / sqrtf(n.x * n.x + n.z * n.z + n.y * n.y + 1e-08f);
        out->x = -(inv * n.x);
        out->y = -(inv * n.y);
        out->z = -(inv * n.z);
        return;
    }
    out->x = DAT_016881f0;
    out->y = DAT_016881f4;
    out->z = DAT_016881f8;
}

// @ 0x00b7f510
void cPlanetModel_s00b7_ea80::FUN_f510(unsigned n)
{
    int table = FUN_00b7f4a0(n);
    unsigned i = 0;
    if (*(unsigned*)((char*)this + 8) != 0) {
        do {
            int node = *(int*)(*(int*)((char*)this + 4) + i * 4);
            while (node) {
                unsigned h = (unsigned)(*(int*)(node + 8) * 0xfd + *(int*)node * 0x25 + *(int*)(node + 4)) % n;
                *(int*)(*(int*)((char*)this + 4) + i * 4) = *(int*)(node + 0x20);
                *(int*)(node + 0x20) = *(int*)(table + h * 4);
                *(int*)(table + h * 4) = node;
                node = *(int*)(*(int*)((char*)this + 4) + i * 4);
            }
            i++;
        } while (i < *(unsigned*)((char*)this + 8));
    }
    int p = *(int*)((char*)this + 4);
    if (*(unsigned*)((char*)this + 8) > 1 && p != *(int*)((char*)this + 0x30)) {
        if (p >= *(int*)((char*)this + 0x24) && p < *(int*)((char*)this + 0x28)) {
            *(int*)p = *(int*)((char*)this + 0x1c);
            *(int*)((char*)this + 0x1c) = p;
            *(int*)((char*)this + 4) = table;
            *(unsigned*)((char*)this + 8) = n;
            return;
        }
        operator_delete__((void*)p);
    }
    *(int*)((char*)this + 4) = table;
    *(unsigned*)((char*)this + 8) = n;
}

// @ 0x00b7f5c0
S18** FUN_00b7f5c0(S18** out, const S18* first, const S18* last, S18* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
                dst->e = first->e; dst->f = first->f; dst->g = first->g;
            }
            first++;
            dst++;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x00b7f630
S18* FUN_00b7f630(const S18* first, const S18* last, S18* dst)
{
    while (first != last) {
        if (dst) {
            dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
            dst->e = first->e; dst->f = first->f; dst->g = first->g;
        }
        first++;
        dst++;
    }
    return dst;
}

// @ 0x00b7f710
S24a* FUN_00b7f710(const S24a* first, const S24a* last, S24a* dst)
{
    while (first != last) {
        if (dst) {
            dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
            dst->e = first->e; dst->f = first->f; dst->g = first->g; dst->h = first->h;
            dst->i = first->i;
        }
        first++;
        dst++;
    }
    return dst;
}

// @ 0x00b7f780
void FUN_00b7f780(S24b** out, const S24b* first, const S24b* last, S24b* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
                dst->e = first->e; dst->f = first->f; dst->g = first->g; dst->h = first->h;
                dst->i = first->i;
            }
            first++;
            dst++;
        } while (first != last);
        *out = dst;
    }
}

// @ 0x00b7f800
void* FUN_00b7f800(S24b* dst, unsigned count, const S24b* src)
{
    // The original only touches eax after the count>0 test, so a count==0 call hands
    // back the caller's incoming eax unchanged; leave that path without a return.
    if (count != 0) {
        S24b* d = dst;
        do {
            if (d) {
                d->a = src->a; d->b = src->b; d->c = src->c; d->d = src->d;
                d->e = src->e; d->f = src->f; d->g = src->g; d->h = src->h;
                d->i = src->i;
            }
            --count;
            ++d;
        } while (count != 0);
        // The retail loop keeps its cursor biased to the `f` member (+0x14) in eax.
        return (char*)d + 0x14;
    }
}

// @ 0x00b7f860
void* FUN_00b7f860(S18* dst, unsigned count, const S18* src)
{
    // See FUN_00b7f800: void return, count==0 leaves eax untouched in the original.
    if (count != 0) {
        S18* d = dst;
        do {
            if (d) {
                d->a = src->a; d->b = src->b; d->c = src->c; d->d = src->d;
                d->e = src->e; d->f = src->f; d->g = src->g;
            }
            --count;
            ++d;
        } while (count != 0);
        // The retail loop keeps its cursor biased to the `d` member (+0xc) in eax.
        return (char*)d + 0x0c;
    }
}

// @ 0x00b7f8b0
S24b* FUN_00b7f8b0(const S24b* first, const S24b* last, S24b* dst)
{
    while (first != last) {
        if (dst) {
            dst->a = first->a; dst->b = first->b; dst->c = first->c; dst->d = first->d;
            dst->e = first->e; dst->f = first->f; dst->g = first->g; dst->h = first->h;
            dst->i = first->i;
        }
        first++;
        dst++;
    }
    return dst;
}

// @ 0x00b7f920
void cArcRibbon::DrawArc(const Vector3& a, const Vector3& b, uint32_t color)
{
    RibbonVertex buffer[0x80];
    RibbonVertex* pVertex = buffer;
    SP::cStaticBufferDraw_s00b7_f920* pDraw = SP::cStaticBufferDraw_s00b7_f920::spInstance;

    Vector3 startTangent = a.Normalized() * 90.0f;
    Vector3 endTangent = -b.Normalized() * 90.0f;

    float gridOffset = SP::DebugDrawGrid()->GetInfo()->mHeightOffset;
    SP::cPlanetModel_s00b7_f920* pPlanetModel = SP::PlanetModel();
    float radius;
    if (pPlanetModel->mpPlanet && pPlanetModel->mpPlanet->GetInfo())
        radius = pPlanetModel->mpPlanet->GetInfo()->mRadius;
    else
        radius = 500.0f;
    radius = radius + gridOffset + 5.0f;

    Vector3 middle = (b + a).Normalized() * radius;
    Vector3 dir = (b - a) * 1.2f;
    Vector3 dirN = dir.Normalized();
    Vector3 tangentA = dirN * 50.0f + startTangent;
    Vector3 tangentB = dirN * 50.0f + endTangent;
    Vector3 side = a.Cross(b).Normalized();

    Vector3 prev = Hermite(a, middle, tangentA, dir, 0.1f);
    uint32_t prevColor = color;
    float dist = 0.0f;

    for (int i = 1; i <= 16; i++) {
        Vector3 cur = Hermite(a, middle, tangentA, dir, i * 0.05625f + 0.1f);
        uint32_t curColor = (i < 4) ? (uint32_t)(i << 30) : 0xff000000;
        curColor |= color;

        pVertex->pos = prev - side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;
        pVertex->pos = prev + side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        dist += (cur - prev).Length();
        pVertex->pos = cur + side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        pVertex->pos = cur - side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;

        prev = cur;
        prevColor = curColor;
    }

    for (int i = 0; i < 16; i++) {
        Vector3 cur = Hermite(middle, b, dir, tangentB, (i + 1) * 0.05625f);
        uint32_t curColor = (i < 12) ? 0xff000000 : (uint32_t)((15 - i) << 30);
        curColor |= color;

        pVertex->pos = prev - side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;
        pVertex->pos = prev + side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        dist += (cur - prev).Length();
        pVertex->pos = cur + side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        pVertex->pos = cur - side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;

        prev = cur;
        prevColor = curColor;
    }

    int stride;
    int count = pDraw->mpBuffer->GetVertexBuffer(0x80, &pVertex, &stride);
    if (stride == sizeof(RibbonVertex) && count == 0x80)
        memcpy(pVertex, buffer, sizeof(buffer));
    else
        memset(pVertex, 0, stride * count);
    pDraw->mpBuffer->Unlock();
}

// @ 0x00b80630
Layer *Layer::Init()
{
    volatile int probe;
    m_vtbl = (void **)0x13f1ab0;
    m_vtbl2 = (void **)0x13ef094;
    _InterlockedExchange(&m_lock8, 0);
    m_vtbl = (void **)0x1465474;
    m_vtbl2 = (void **)0x1465470;
    m_flag0c = 0;
    m_p10 = 0;
    m_p14 = 0;
    m_p18 = 0;
    m_p1c = 0;
    m_pRanges = 0;
    m_pMode = 0;
    m_flag28 = 0;
    m_pMod0 = 0;
    m_pMod1 = 0;
    m_pMod2 = 0;
    AssignMode(&m_pMod0, NewModifier());
    AssignMode(&m_pMod1, NewModifier());
    AssignMode(&m_pMod2, NewModifier());
    return this;
}

// @ 0x00b807e0
void Mode::BuildRibbon(const void *pVerts, const void *pOther, int count, u32 color)
{
    RibbonVertex_s00b8_0630 *pOut = (RibbonVertex_s00b8_0630 *)pVerts;
    const Vertex *pV = (const Vertex *)pOther;
    float dist = 0.0f;
    float prevX = 0.0f, prevY = 0.0f, prevZ = 0.0f;
    int idx = 1;
    int nSeg = count * 2 - 2;
    if (count <= 1)
        return;
    do {
        int got = 0;
        ((Draw *)gDrawHolder->m_draw)->GetVertexBuffer(nSeg + 4, &pOut, &got);
        nSeg += 4 - got;
        idx--;
        const Vertex *pCur = (const Vertex *)pVerts + idx;
        pOut->x = pCur->x;
        pOut->y = pCur->y;
        pOut->z = pCur->z;
        pOut->color = color;
        pOut->u = kOne;
        pOut->v = dist;
        pOut++;
        prevX = pCur->x;
        prevY = pCur->y;
        prevZ = pCur->z;
        if (got - 1 > 1) {
            int wraps = ((got - 3) >> 1) + 1;
            idx += wraps;
            do {
                const Vertex *pNext = pCur + 1;
                float dx = pNext->x - prevX;
                float dy = pNext->y - prevY;
                float dz = pNext->z - prevZ;
                pOut->x = pNext->x;
                pOut->y = pNext->y;
                pOut->z = pNext->z;
                pOut->color = color;
                pOut->u = kOne;
                dist = (float)(dz * dz + dy * dy + dx * dx);
                dist = sqrtf(dist) + dist;
                pOut->v = dist;
                pOut->x = pNext->x;
                pOut->y = pNext->y;
                pOut->z = pNext->z;
                pOut->color = color;
                pOut->u = 0.0f;
                pOut->v = dist;
                prevX = pCur->x;
                prevY = pCur->y;
                prevZ = pCur->z;
                pOut++;
                pCur = pNext;
                wraps--;
            } while (wraps != 0);
        }
        const Vertex *pTail = (const Vertex *)pOther + idx;
        pOut->x = pTail->x;
        pOut->y = pTail->y;
        pOut->z = pTail->z;
        pOut->color = color;
        pOut->u = 0.0f;
        pOut->v = dist;
        FUN_007a4650();
    } while (idx < count);
}

// @ 0x00b80a50
void Mode::DrawMaterial(void *pMaterial, void *pParam)
{
    if (m_buffer != 0) {
        FUN_00761cf0(200);
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, ((MaterialRef *)pMaterial)->m_material);
    }
}

// @ 0x00b80a80
void Mode::SetMaterialA(void *pParam)
{
    MaterialManager *mm = SP_MaterialManager();
    MaterialRef *pMaterial = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0x9276314a);
    if (pMaterial != 0 && m_buffer != 0) {
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, pMaterial->m_material);
    }
}

// @ 0x00b80ac0
void Mode::SetMaterialB(void *pParam)
{
    MaterialManager *mm = SP_MaterialManager();
    MaterialRef *pMaterial = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0x32fb723);
    if (pMaterial != 0 && m_buffer != 0) {
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, pMaterial->m_material);
    }
}

// @ 0x00b80b00
void Mode::SetMaterialC(void *pParam)
{
    MaterialManager *mm = SP_MaterialManager();
    MaterialRef *pMaterial = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0xc13ad5ef);
    if (pMaterial != 0 && m_buffer != 0) {
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, pMaterial->m_material);
    }
}

// @ 0x00b80b40
void Mode::Submit()
{
    if (m_buffer != 0) {
        void *pOld = m_buffer;
        m_buffer = 0;
        ((void (__thiscall *)(void *))((RefObj *)pOld)->m_vtbl[2])(pOld);
    }
    if (m_idBegin == m_idEnd)
        return;

    gDrawHolder->Begin(0, 4, 2, 0x1000);

    int i = 0;
    int n = (int)(m_idEnd - m_idBegin);
    if (n > 0) {
        do {
            PlanetModel_s00b8_0630 *pModel = (PlanetModel_s00b8_0630 *)SP_PlanetModel();
            u32 id = m_idBegin[i];
            PlanetRecord *pRec = &pModel->m_records[id];
            if (pRec->m_flag11 != 0) {
                float cr = 0.5f, cg = 0.5f, cb = 0.5f;
                int noun = pRec->m_noun;
                if (noun != -1) {
                    NounColor *pColor = ((NounThing *)SP_NounManager(noun))->GetColor();
                    if (pColor != 0) {
                        cr = pColor->m_r;
                        cg = pColor->m_g;
                        cb = pColor->m_b;
                    }
                }
                float fr = cr > 0.0f ? cr : 0.0f;
                fr = fr * 255.0f;
                if (fr > 255.0f) fr = 255.0f;
                float fg = cg > 0.0f ? cg : 0.0f;
                fg = fg * 255.0f;
                if (fg > 255.0f) fg = 255.0f;
                float fb = cb > 0.0f ? cb : 0.0f;
                fb = fb * 255.0f;
                if (fb > 255.0f) fb = 255.0f;
                u32 r = (u32)(int)fr;
                u32 g = (u32)(int)fg;
                u32 b = (u32)(int)fb;
                u32 color = (((r | 0xffffff00u) << 8) | g) << 8 | b;

                RangeEntry *pRange = &m_ranges[i];
                int begin = (int)(size_t)pRange->m_begin;
                int end = (int)(size_t)pRange->m_end;
                int count = (end - begin) / 0xc;
                BuildRibbon((const void *)begin,
                            m_rangeSecond[i].m_ptr,
                            count, color);
            }
            i++;
        } while (i < n);
    }

    if (m_buffer != 0) {
        void *pOld = m_buffer;
        m_buffer = 0;
        ((void (__thiscall *)(void *))((RefObj *)pOld)->m_vtbl[2])(pOld);
    }
    Draw *pDraw2 = (Draw *)gDrawHolder->m_draw;
    pDraw2->Flush();
    m_buffer = gDrawHolder->m_draw;
    gDrawHolder->m_draw = 0;
}

// @ 0x00b80d30
void Layer::Destroy()
{
    volatile int probe;
    m_vtbl = (void **)0x1465474;
    m_vtbl2 = (void **)0x1465470;
    DestroyMode(m_pMod2);
    DestroyMode(m_pMod1);
    DestroyMode(m_pMod0);
    DestroyMode(m_pMode);
    if (m_pRanges != 0) {
        if (m_pRanges->m_ref <= 1) {
            void **iface = (void **)((RefObj *)m_pRanges)->m_vtbl[0];
            u32 flags = (m_pRanges->m_flags >> 31) & 1;
            ((void (__thiscall *)(void *, RefArray *, u32))iface[0x170 / 4])
                (((RefObj *)m_pRanges)->m_vtbl, m_pRanges, flags);
        } else {
            m_pRanges->m_ref--;
        }
    }
    if (m_p1c != 0) {
        ((void (__thiscall *)(void *))((RefObj *)m_p1c)->m_vtbl[1])(m_p1c);
    }
    m_vtbl = (void **)0x13eb938;
    m_vtbl2 = (void **)0x13ef094;
}

// @ 0x00b80e40
void Layer::StopAudio()
{
    volatile int probe;
    void *p = FUN_0067dd50();
    ((void (__thiscall *)(void *, int))((RefObj *)p)->m_vtbl[0x50 / 4])(p, 9);
    p = FUN_0067dd50();
    ((void (__thiscall *)(void *, int))((RefObj *)p)->m_vtbl[0x50 / 4])(p, 0x19);

    Mode *pMode = m_pMode;
    if (pMode != 0) {
        m_pMode = 0;
        long n = _InterlockedDecrement(&pMode->m_ref);
        if (n == 0) {
            _InterlockedExchange(&pMode->m_ref, 1);
            ((void (__thiscall *)(Mode *, int))((RefObj *)pMode)->m_vtbl[0])(pMode, 1);
        }
    }
}

// @ 0x00b80ea0
void Layer::DispatchEvent(void *p2, int event, void *pViewer, void *pMaterial)
{
    (void)p2;
    if (m_pMode == 0 || m_pMod0 == 0)
        return;
    if (SP_GetActiveTerrainSphere() == 0)
        return;
    if (SP_GetUniverseContext() != 0)
        return;
    if (m_flag0c != 0) {
        m_flag0c = 0;
        m_pMode->Submit();
    }
    ViewerHandle *pHandle = (ViewerHandle *)pViewer;
    if (!pHandle->m_viewer->Update())
        return;

    EffectsDispatch_t mat;
    mat.m[0][0] = kOne;  mat.m[0][1] = 0.0f; mat.m[0][2] = 0.0f; mat.m[0][3] = 0.0f;
    mat.m[1][0] = 0.0f;  mat.m[1][1] = kOne; mat.m[1][2] = 0.0f; mat.m[1][3] = 0.0f;
    mat.m[2][0] = 0.0f;  mat.m[2][1] = 0.0f; mat.m[2][2] = kOne; mat.m[2][3] = 0.0f;
    mat.m[3][0] = 0.0f;  mat.m[3][1] = 0.0f; mat.m[3][2] = 0.0f; mat.m[3][3] = 0.0f;
    EffectsDispatch(&mat, 4);

    if (event == 9) {
        MaterialManager *mm = SP_MaterialManager();
        MaterialRef *pMat = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0x8c4c893e);
        m_pMode->DrawMaterial(pMat, pMaterial);
        pHandle->m_viewer->Finish();
        return;
    }
    if (event == 0x19) {
        m_pMod0->SetMaterialA(pMaterial);
        m_pMod1->SetMaterialB(pMaterial);
        m_pMod2->SetMaterialC(pMaterial);
    }
    pHandle->m_viewer->Finish();
}

// @ 0x00b80ff0
Mode *Mode::DeleteInstance(u32 flags)
{
    if (m_buffer != 0) {
        ((void (__thiscall *)(void *))((RefObj *)m_buffer)->m_vtbl[2])(m_buffer);
    }
    m_vtbl = (void **)0x13ef094;
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// @ 0x00b81020
void StampState::Stamp(const float *pDir, float radius, u32 planeMask)
{
    float vx = pDir[0];
    float vy = pDir[1];
    float vz = pDir[2];
    float len = sqrtf(vx * vx + vy * vy + vz * vz);
    if (len <= kEps)
        return;

    float inv = kOne / len;
    float scaled = inv * k128 * radius;
    int steps = (int)scaled;
    if ((float)steps < scaled)
        steps++;
    if (steps == 0)
        return;

    vx *= inv;
    vy *= inv;
    vz *= inv;
    float reach = (inv * radius) * (inv * radius);

    float ax = vx < 0.0f ? -vx : vx;
    float ay = vy < 0.0f ? -vy : vy;
    float az = vz < 0.0f ? -vz : vz;

    int ca, cb, plane;
    if (az < ax || az < ay) {
        if (ay < ax) {
            ca = (int)((vy / vx + kOne) * k64);
            cb = (int)((vz / ax + kOne) * k64);
            plane = vx < 0.0f ? 3 : 2;
        } else {
            ca = (int)((vz / vy + kOne) * k64);
            cb = (int)((vx / ay + kOne) * k64);
            plane = vy < 0.0f ? 5 : 4;
        }
    } else {
        ca = (int)((vx / vz + kOne) * k64);
        cb = (int)((vy / az + kOne) * k64);
        plane = vz < 0.0f ? 1 : 0;
    }
    if (ca == 0x80) ca = 0x7f;
    if (cb == 0x80) cb = 0x7f;

    SearchCoord coord;
    coord.m_a = ca;
    coord.m_b = cb;
    coord.m_c = plane;

    StampSpan spans[29];
    int nSpans = FUN_00685450(0x80, &coord.m_a, steps, spans);
    if (nSpans <= 0)
        return;

    u8 *pMask = m_mask;
    u32 *pBits = m_bits;
    u32 andMask = planeMask & 0x3c000000u;
    u8 sel0 = (u8)(andMask >> 0x16);
    u8 sel1 = (u8)(andMask >> 0x1a);
    u8 sel[2] = { sel0, sel1 };

    for (int s = 0; s < nSpans; s++) {
        StampSpan *pSpan = &spans[s];
        for (int c = pSpan->m_minC; c < pSpan->m_maxC; c++) {
            for (int b = pSpan->m_minB; b < pSpan->m_maxB; b++) {
                u32 idx = (pSpan->m_plane * 0x80 + (u32)c) * 0x80 + (u32)b;
                u8 *pCell = pMask + (idx >> 1);
                u8 cell = *pCell;
                u8 mask = sel[idx & 1];
                if ((mask & cell) == 0)
                    continue;

                const u8 *order = &gPlaneOrder[(pSpan->m_plane >> 1) * 4];
                float fbx = ((float)b + 0.5f) * 0.015625f - kOne;
                float fcy = ((float)c + 0.5f) * 0.015625f - kOne;
                float invLen = kOne / sqrtf(fcy * fcy + fbx * fbx + kOne);
                float sgn = (pSpan->m_plane & 1) ? -invLen : invLen;

                float normal[3];
                normal[order[0]] = sgn * fbx;
                normal[order[1]] = invLen * fcy;
                normal[order[2]] = sgn;

                float dx = normal[0] - vx;
                float dy = normal[1] - vy;
                float dz = normal[2] - vz;
                if (dx * dx + dy * dy + dz * dz <= reach) {
                    *pCell = (u8)(~mask & cell);
                    pBits[idx] &= ~andMask;
                }
            }
        }
    }
}

// @ 0x00b81470
float SP::cPlanetModel::DistanceBetweenPoints(cSPVector3 const & a, cSPVector3 const & b) const
{
    float r1 = GetRadiusAt(a);
    float r2 = GetRadiusAt(b);

    float ax = a.x, ay = a.y, az = a.z;
    float bx = b.x, by = b.y, bz = b.z;

    float alen = sqrtf(ax * ax + ay * ay + az * az);
    float blen = sqrtf(bx * bx + by * by + bz * bz);
    float aInv = kOne / alen;
    float bInv = kOne / blen;

    float dot = (ax * aInv) * (bx * bInv) +
                (ay * aInv) * (by * bInv) +
                (az * aInv) * (bz * bInv);

    if (dot > kOne)
        dot = kOne;
    if (dot < kNegOne)
        dot = kNegOne;

    float angle = acosf(dot);
    return angle * ((r1 + r2) * kHalf);
}

// @ 0x00b81c80
void cPlanetModel_s00b8_15a0::FUN_00b81c80(Vec3* out, const Vec3* pa, const Vec3* pb, float s)
{
    Vec3 va, vb;
    va.x = pa->x;
    float l1 = 1.0f / sqrtf((va.x * va.x + pa->y * pa->y) + pa->z * pa->z);
    va.x = va.x * l1;
    va.z = l1 * pa->z;
    va.y = l1 * pa->y;

    vb.x = pb->x;
    float l2 = 1.0f / sqrtf((vb.x * vb.x + pb->y * pb->y) + pb->z * pb->z);
    vb.x = vb.x * l2;
    vb.y = pb->y * l2;
    vb.z = pb->z * l2;

    float r = (float)GetRadiusAt((uint)&va);

    float cx = vb.z * va.y - va.z * vb.y;
    float cy = va.z * vb.x - vb.z * va.x;
    float cz = vb.y * va.x - vb.x * va.y;
    float inv = 1.0f / sqrtf(cy * cy + (cz * cz + cx * cx));
    float sn, cs;
    if ((vb.z * va.z + vb.y * va.y) + vb.x * va.x <= 0.0f) {
        float t = (s / r) * -0.5f;
        sn = sinf(t);
        cs = cosf(t);
    } else {
        float t = (s / r) * 0.5f;
        sn = sinf(t);
        cs = cosf(t);
    }
    Quat q;
    q.w = cs;
    q.x = sn * (inv * cx);
    q.y = (cy * inv) * sn;
    q.z = (cz * inv) * sn;
    Vec3 axis;
    axis.x = q.x;
    axis.y = q.y;
    axis.z = q.z;
    float* p = FUN_0059aed0((float*)&axis, (const float*)&va, (const float*)&q);
    float rx = p[0], ry = p[1], rz = p[2];
    float rr2 = (float)GetRadiusAt((uint)&rx);
    float inv2 = 1.0f / sqrtf((ry * ry + (rz * rz + rx * rx)) + 1e-8f);
    out->x = (inv2 * rx) * rr2;
    out->y = (ry * inv2) * rr2;
    out->z = (rz * inv2) * rr2;
}

// @ 0x00b82310
long double cPlanetModel_s00b8_15a0::FUN_00b82310(void* param)
{
    int h = FUN_00b3d310();
    if (*(int*)(h + 0x20) != 0)
        return GetRadiusAt((uint)param);

    Vec3 d;
    DirectionToSurfacePosition(&d, (const Vec3*)param);
    float f1 = d.z * d.z + (d.x * d.x + d.y * d.y);
    float f2 = sqrtf(f1);
    float f5;
    if (mpISphere != 0) {
        int m = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
        if (m != 0) {
            int m2 = ((int(__thiscall*)(void*))VTC(mpISphere, 0xc))(mpISphere);
            f5 = *(float*)(m2 + 0x34);
        } else {
            f5 = 500.0f;
        }
    } else {
        f5 = 500.0f;
    }
    float height = f5 * 2.0f - f2;

    RadialRay ray;
    ray.pos[0] = d.x;
    ray.pos[1] = d.y;
    ray.pos[2] = d.z;
    ray.pos[3] = 0.0f;
    ray.h0 = height;
    ray.h1 = 0.0f;

    RayHitResult hit;
    hit.normalOut = 0;
    hit.distOut = 0;
    hit.userData = 0;
    hit.entity = 0;
    FUN_00b65b10(&ray, DAT_0167ecd0, 0, true, 6, &hit);
    if (hit.status != 0) {
        float v = (hit.pos[1] * hit.pos[1] + hit.pos[2] * hit.pos[2]) + hit.pos[0] * hit.pos[0];
        if (f1 < v)
            return (long double)sqrtf(v);
    }
    return (long double)f2;
}

// @ 0x00b832d0
bool cPlanetModel_s00b8_32d0::FUN_00b832d0(const float* dir, float step)
{
    float local_38 = dir[0];
    if ((dir[1] * dir[1] + dir[2] * dir[2]) + local_38 * local_38 != 0.0f) {
        float local_30 = 1.0f / (float)sqrt((double)((dir[1] * dir[1] + dir[2] * dir[2]) + local_38 * local_38));
        local_38 = local_38 * local_30;
        float local_34 = local_30 * dir[1];
        local_30 = local_30 * dir[2];
        float local_10[4];
        QuaternionFromDirections(local_10, (const float*)&kQuatRef, &local_38);
        float local_20[3];
        float* pfVar5 = FUN_0059aed0(local_20, kBasis9, local_10);
        float fVar1 = pfVar5[0];
        float fVar2 = pfVar5[1];
        float fVar3 = pfVar5[2];
        float angle = 0.0f;
        if (0.0f < kSpiralMaxAngle) {
            do {
                float s = (float)sin((double)(angle * 0.5f));
                float c = (float)cos((double)(angle * 0.5f));
                float fVar10 = local_34 * s;
                float fVar11 = local_30 * s;
                float fVar9 = s * local_38;
                float local_2c = ((c * fVar10 + fVar11 * fVar9) * fVar3 +
                                  (fVar10 * fVar9 - c * fVar11) * fVar2) * 2.0f +
                                 (1.0f - (fVar11 * fVar11 + fVar10 * fVar10) * 2.0f) * fVar1;
                float local_28 = ((fVar11 * fVar10 - c * fVar9) * fVar3 +
                                  (c * fVar11 + fVar10 * fVar9) * fVar1) * 2.0f +
                                 (1.0f - (fVar11 * fVar11 + fVar9 * fVar9) * 2.0f) * fVar2;
                float local_24 = ((c * fVar9 + fVar11 * fVar10) * fVar2 +
                                  (fVar11 * fVar9 - c * fVar10) * fVar1) * 2.0f +
                                 (1.0f - (fVar9 * fVar9 + fVar10 * fVar10) * 2.0f) * fVar3;
                local_2c = (dir[0] + local_2c * step) + local_2c;
                local_28 = (local_28 * step + dir[1]) + local_28;
                local_24 = (local_24 * step + dir[2]) + local_24;
                if (mpISphere != 0) {
                    Vec3POD p;
                    p.x = local_2c; p.y = local_28; p.z = local_24;
                    cTerrainMapSet_s00b8_32d0* pcVar6 = mpISphere->s3();
                    float h = pcVar6->GetHeightAt(&p);
                    cTerrainMapSet_s00b8_32d0* pc2 = mpISphere->s3();
                    if (h < pc2->f3c * pc2->f38 + pc2->f34)
                        return 1;
                }
                angle = angle + 1.0f / step;
            } while (angle < kSpiralMaxAngle);
        }
    }
    return 0;
}

// @ 0x00b83620
float cPlanetModel_s00b8_32d0::FUN_00b83620(int a, float b)
{
    int iVar3 = 0;
    int iVar4 = 100;
    do {
        Vec3POD local_c;
        MakeRandomWorldPosition(&local_c, a, 0.0f, b);
        if (mpISphere != 0) {
            float h = mpISphere->s3()->GetHeightAt(&local_c);
            cTerrainMapSet_s00b8_32d0* m = mpISphere->s3();
            if (h < m->f3c * m->f38 + m->f34)
                iVar3 = iVar3 + 1;
        }
        iVar4 = iVar4 - 1;
    } while (iVar4 != 0);
    return (float)iVar3 * 0.01f;
}

// @ 0x00b836b0
float FUN_00b836b0(uint param_1, uint param_2)
{
    cPlanetModel_s00b8_32d0* iVar2 = PlanetModel_s00b8_32d0();
    int iVar4 = *(int*)((char*)iVar2 + 0x4c);
    cTerrainMapSet_s00b8_32d0* iVar3 = iVar2->mpISphere->s3();
    float fVar5 = iVar3->f34;
    uint uVar1 = *(uint*)(iVar4 + (((param_2 >> 8 & 0xff) + (param_2 >> 0x11) * 0x80) * 0x80 +
                                   (param_2 & 0xff)) * 4);
    float fVar6 = iVar3->f38;
    float fVar7;
    if (iVar2->mpISphere == 0) {
        fVar7 = 0.0f;
    } else {
        cTerrainMapSet_s00b8_32d0* p = iVar2->mpISphere->s3();
        fVar7 = p->f3c * p->f38 + p->f34;
    }
    fVar5 = ((float)(int)((uVar1 & 0xffff) - 0x8000) * fVar6) * kHeightUnit + fVar5;
    if (fVar7 <= fVar5)
        return kNoTerrain;
    fVar5 = (fVar7 - fVar5) * 0.06666667f;
    float fStack_10 = 0.0f;
    if (0.0f <= fVar5)
        fStack_10 = fVar5;
    if (1.0f <= fStack_10)
        fStack_10 = 1.0f;
    float fVar5b = fStack_10 * 9.0f;
    Vec3POD A, B;
    FUN_00ac1510(param_1 >> 0x11, param_1 & 0xff, param_1 >> 8 & 0xff, (float*)&A);
    FUN_00ac1510(param_2 >> 0x11, param_2 & 0xff, param_2 >> 8 & 0xff, (float*)&B);
    float dz = B.z - A.z;
    if (iVar2->mpISphere == 0) {
        fVar6 = 0.0f;
    } else {
        cTerrainMapSet_s00b8_32d0* p = iVar2->mpISphere->s3();
        fVar6 = p->f3c * p->f38 + p->f34;
    }
    return fVar6 * (float)sqrtf(((B.y - A.y) * (B.y - A.y) + (B.x - A.x) * (B.x - A.x)) + dz * dz) *
           (10.0f - fVar5b);
}

// @ 0x00b83870
uint cPlanetModel_s00b8_32d0::FUN_00b83870(int arg)
{
    void* pm = PropertyManager();
    int listA = 0, listB = 0;
    // mpISphere slot +0xb4: return two parallel arrays (A stride 0xc, B stride 0x38) + count.
    uint count = ((uint (__thiscall*)(void*, int*, int*))(*(void***)mpISphere)[0xb4 / 4])(mpISphere, &listA, &listB);
    float* ref = (float*)((char*)this + 0x28);
    for (uint i = 0; i < count; ++i) {
        int item = listA + (int)i * 0xc;
        void* prop = 0;
        ((char (__thiscall*)(void*, int, int, void**))(*(void***)pm)[0x2c / 4])(
            pm, *(int*)(item), *(int*)(item + 8), &prop);
        if (prop != 0) {
            float va = 0.0f, vb = 0.0f;
            char fa = 0, fb = 0;
            void* p = 0;
            if (((char (__thiscall*)(void*, int, void**))(*(void***)prop)[0x24 / 4])(prop, 0x254cf89, &p) &&
                p != 0 && *(short*)((char*)p + 0x12) == 0xd) {
                if ((*(unsigned char*)((char*)p + 0x10) & 0x30) != 0)
                    p = *(void**)p;
                va = *(float*)p;
                fa = 1;
            }
            p = 0;
            if (((char (__thiscall*)(void*, int, void**))(*(void***)prop)[0x24 / 4])(prop, 0x4ee9f45, &p) &&
                p != 0 && *(short*)((char*)p + 0x12) == 0xd) {
                if ((*(unsigned char*)((char*)p + 0x10) & 0x30) != 0)
                    p = *(void**)p;
                vb = *(float*)p;
                fb = 1;
            }
            if (fa || fb) {
                float v = (vb > va) ? vb : va;
                float* pos = (float*)(listB + (int)i * 0x38);
                float dx = pos[1] - ref[0];
                float dy = pos[2] - ref[1];
                float dz = pos[3] - ref[2];
                if (v * v >= dx * dx + dz * dz + dy * dy)
                    return 1;
            }
        }
        if (prop != 0)
            ((void (__thiscall*)(void*))(*(void***)prop)[4 / 4])(prop);
    }
    return 0;
}

// @ 0x00b83af0
int** HashTableA::Find(int** out, int* key)
{
    uint uVar2 = (uint)(*key * 0x25 + key[2] * 0xfd + key[1]) % size;
    int* p = table;
    int* slot = p + uVar2;
    int* node = (int*)p[uVar2];
    for (; node != 0; node = (int*)node[8]) {
        if ((*key == node[0]) && (key[1] == node[1]) && (key[2] == node[2]))
            break;
    }
    if (node == 0) {
        slot = p + size;
        node = (int*)*slot;
    }
    out[0] = node;
    out[1] = slot;
    return out;
}

// @ 0x00b841a0
void ColorVector::DoInsertValue(uint index, uint value, int param4)
{
    if ((0 < (int)index) && (index < (uint)((mEnd - mBegin) / 0x18))) {
        uint* puVar3 = (uint*)(mBegin + index * 0x18);
        if (*puVar3 != value) {
            *puVar3 = value;
            *(char*)((char*)mOwner + 0xc) = 1;
            MessageBasicRC5 local_40;
            local_40.mId = 0x66603cd;
            local_40.mRefCount = 0;
            local_40.vftable = 0;
            local_40.mFieldC = 0;
            local_40.mField10 = value;
            void** piVar1 = (void**)MessageServer();
            ((void (__thiscall*)(void*, int, void*, int))(*(void***)piVar1)[0x14 / 4])(piVar1, 0x66603cd, &local_40, 0);
        }
        int iVar2 = mBegin + index * 0x18;
        if (*(char*)(iVar2 + 0x10) != '\0')
            *(int*)(iVar2 + 0x14) = param4;
    }
}

// @ 0x00b84730
void cPlanetModel_s00b8_4270__g8::FindSurfacePosition(Vector3_s00b8_4270__g8* out)
{
    Vector3_s00b8_4270__g8 pos;
    Vector3_s00b8_4270__g8 dir;
    RandomDirection3(&dir);
    volatile float radius = GetRadiusAt(dir);
    pos.x = dir.x * radius;
    pos.y = dir.y * radius;
    pos.z = dir.z * radius;

    int i = 0;
    do {
        int prev = i;
        i = prev + 1;
        if (mpISphere == 0)
            break;
        float height = mpISphere->GetMap()->GetHeightAt(pos);
        cTerrainMapSet_s00b8_4270__g8* terrain = mpISphere->GetMap();
        float water = terrain->mWaterHeight * terrain->mMaxHeight + terrain->mRadius;
        if (water <= height)
            break;

        Vector3_s00b8_4270__g8 ndir;
        RandomDirection3(&ndir);
        float r;
        if (mpSphere != 0) {
            r = mpISphere->GetMap()->GetHeightAt(ndir);
        } else if (mpISphere != 0 && mpISphere->GetMap() != 0) {
            r = mpISphere->GetMap()->mRadius;
        } else {
            r = 500.0f;
        }
        dir.x = ndir.x * r;
        dir.y = ndir.y * r;
        dir.z = ndir.z * r;
        pos = dir;
    } while (i < 10000);

    if (i < 10000) {
        out->x = pos.x;
        out->y = pos.y;
        out->z = pos.z;
    } else {
        out->x = gNoSurfacePosition.x;
        out->y = gNoSurfacePosition.y;
        out->z = gNoSurfacePosition.z;
    }
}

// @ 0x00b849e0
void U16Vec::Reserve(unsigned int n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        uint16_t* pNew = n
            ? (uint16_t*)operator_new_eastl(n * 2, "Simulator", 0, 0, ALLOC_FILE, 0xd1)
            : 0;
        MemCpy(pNew, mpBegin, (uint32_t)((char*)mpEnd - (char*)mpBegin));
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_eastl(mpBegin);
        uint16_t* pNewEnd = pNew + (mpEnd - mpBegin);
        uint16_t* pNewCap = pNew + n;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNewCap;
    }
}

// @ 0x00b850c0
Elem1C* UninitCopy1C(const Elem1C* first, const Elem1C* last, Elem1C* dst)
{
    while (first != last) {
        if (dst) {
            dst->mA = first->mA;
            dst->mB = first->mB;
            dst->mVec.Copy(first->mVec);
        }
        first += 1;
        dst += 1;
    }
    return dst;
}

// @ 0x00b85110
void ScalarList::Dtor()
{
    mVec34.~IntVector();
    mVec20.~IntVectorVec();
    mVec0c.~IntVectorVec();
    if (mp08)
        mp08->s2();
    mpVtbl = &kEventModifierVtbl;
}

// @ 0x00b85380
void Vertex3DVec::GrowAndInsert(Vertex3D *pos, const Vertex3D *pVal)
{
    Vertex3D *pEnd = mpEnd;
    if (pEnd != mpCap) {
        if (pVal >= pos && pVal < pEnd)
            pVal += 1;
        if (pEnd != 0) {
            pEnd->x = (pEnd - 1)->x;
            pEnd->y = (pEnd - 1)->y;
            pEnd->z = (pEnd - 1)->z;
            pEnd->w = (pEnd - 1)->w;
            pEnd->m10 = (pEnd - 1)->m10;
            pEnd->m14 = (pEnd - 1)->m14;
            pEnd->m18 = (pEnd - 1)->m18;
            pEnd->m1c = (pEnd - 1)->m1c;
            pEnd->m20 = (pEnd - 1)->m20;
        }
        for (Vertex3D *p = mpEnd - 1; p != pos; ) {
            p -= 1;
            p[1] = p[0];
        }
        *pos = *pVal;
        mpEnd += 1;
        return;
    }

    // grow: new capacity = max(2*size, 1)
    u32 size = (u32)(pEnd - mpBegin);
    u32 newCap = size * 2;
    if (newCap == 0)
        newCap = 1;
    void *pNew = 0;
    if (newCap != 0)
        pNew = operator_new(newCap * 0x24, "Simulator", 0, 0, (int)0x013ebb38, 0xd1);

    Vertex3D *pMid = (Vertex3D *)FUN_00b7f710(mpBegin, pos, pNew);
    if (pMid != 0)
        *pMid = *pVal;
    Vertex3D *pNewEnd = (Vertex3D *)FUN_00b7f710(pos, mpEnd, pMid + 1);
    if (BlockIsOurs(mpBegin))
        operator_delete_array(mpBegin);
    mpEnd = pNewEnd;
    mpBegin = (Vertex3D *)pNew;
    mpCap = (Vertex3D *)pNew + newCap;
}

// @ 0x00b85500
Vertex3D *Vertex3DVec::CopyUninit(Vertex3D *pDst, Vertex3D *pSrc)
{
    Vertex3D *pEnd = mpEnd;
    Vertex3D *s = pSrc;
    Vertex3D *d = pDst;
    while (s != pEnd) {
        *d = *s;
        s += 1;
        d += 1;
    }
    mpEnd = mpEnd + (pDst - pSrc);
    return pDst;
}

// @ 0x00b85570
void Vec3f_ReverseSwap(Vec3f *pBegin, Vec3f *pEnd)
{
    Vec3f *pLo = pBegin;
    Vec3f *pHi = pEnd - 1;
    while (pLo < pHi) {
        float a = pLo->x;
        float b = pLo->y;
        float c = pLo->z;
        pLo->x = pHi->x;
        pLo->y = pHi->y;
        pLo->z = pHi->z;
        pHi->x = a;
        pHi->y = b;
        pHi->z = c;
        ++pLo;
        --pHi;
    }
}

// @ 0x00b855e0
Vertex2D *Vertex2DVec::Assign(const Vertex2DVec *pSrc)
{
    if (pSrc == this)
        return (Vertex2D *)this;
    Vertex2D *pFirst = pSrc->mpBegin;
    Vertex2D *pLast = pSrc->mpEnd;
    u32 n = (u32)(pLast - pFirst);
    u32 cap = (u32)(mpCap - mpBegin);
    if (n > cap) {
        Vertex2D *pNew = ReallocAssign(n, pFirst, pLast);
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpCap = pNew + n;
        mpBegin = pNew;
        mpEnd = pNew + n;
        return (Vertex2D *)this;
    }
    u32 size = (u32)(mpEnd - mpBegin);
    if (size < n) {
        FUN_720250_CopyVertex3D(pFirst, pFirst + size, mpBegin);
        FUN_00b7f5c0(&pLast, mpBegin + size, pLast, mpEnd, pLast);
        mpEnd = mpBegin + n;
        return (Vertex2D *)this;
    }
    FUN_720250_CopyVertex3D(pFirst, pLast, mpBegin);
    mpEnd = mpBegin + n;
    return (Vertex2D *)this;
}

// @ 0x00b85710
void Vertex3DVec::InsertFillN(Vertex3D *pos, u32 n, const Vertex3D *pVal)
{
    u32 capCount = (u32)(mpCap - mpEnd);
    if (n > capCount) {
        u32 size = (u32)(mpEnd - mpBegin);
        u32 newCap = size * 2;
        if (size == 0)
            newCap = 1;
        u32 need = size + n;
        if (need > newCap)
            newCap = need;
        Vertex3D *pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (Vertex3D *)operator_new(newCap * 0x24, "Simulator", 0, 0, (int)0x013ebb38, 0xd1);
        Vertex3D *pMid = (Vertex3D *)FUN_00b7f8b0(mpBegin, pos, pNew);
        FUN_00b7f800(pMid, (void *)n, (void *)pVal, pos);
        Vertex3D *pNewEnd = (Vertex3D *)FUN_00b7f8b0(pos, mpEnd, pMid + n);
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + newCap;
        return;
    }
    if (n != 0) {
        Vertex3D value = *pVal;
        Vertex3D *pOldEnd = mpEnd;
        u32 tailCount = (u32)(pOldEnd - pos);
        if (n < tailCount) {
            Vertex3D *pSplit = pOldEnd - n;
            FUN_00b7f780((void *)&pVal, pSplit, pOldEnd, pOldEnd, pOldEnd);
            mpEnd = mpEnd + n;
            FUN_00b85090(pos, pSplit, pOldEnd);
            FUN_00b7f6a0(pos, pos + n, &value);
            return;
        }
        u32 fillNew = n - tailCount;
        FUN_00b7f800(pOldEnd, (void *)fillNew, &value, pos);
        mpEnd = mpEnd + fillNew;
        FUN_00b7f780((void *)&pos, pos, pOldEnd, mpEnd, pos);
        mpEnd = mpEnd + tailCount;
        FUN_00b7f6a0(pos, pOldEnd, &value);
    }
}

// @ 0x00b85930
void * __stdcall AllocAndCopy(u32 n, const void *pSrc, const void *pSrcEnd)
{
    void *pDst;
    if (n != 0)
        pDst = operator_new(n, "Simulator", 0, 0, (int)0x013ebb38, 0xd1);
    else
        pDst = 0;
    memcpy(pDst, pSrc, (u32)((const char *)pSrcEnd - (const char *)pSrc));
    return pDst;
}

// @ 0x00b859c0
char TileMapLookup::LookupAssign(u32 key, Vec20B *pOut)
{
    int n = (int)(mpKeysEnd - mpKeys);
    for (int i = 0; i < n; ++i) {
        if (mpKeys[i] == key) {
            Vec20BAssign(pOut, &mpData[i]);
            return 1;
        }
    }
    return 0;
}

// @ 0x00b85a30
void PaintSystem::Dtor()
{
    mpVtbl      = (void *)0x014654e0;
    mpSubVtbl   = (void *)0x01465490;
    mpSubVtbl08 = (void *)0x01465488;

    ((PoolFreeNodesFn)0x00b7f430)(&mPool, mPool.mpBegin, (void *)mPool.mCount);
    mPool.mSize = 0;
    u32   count = mPool.mCount;
    void *first = mPool.mpBegin;
    if (count > 1 && first != mPool.mpSentinel) {
        if (first < mPool.mpLow || mPool.mpHigh <= first)
            operator_delete_array(first);
        else {
            *(u32 *)first = (u32)mPool.mpFree;
            mPool.mpFree = first;
        }
    }

    ((PoolFreeVecFn)0x00b7f3f0)(&mpVecD4, mpVecD4, mpVecD8);
    if (BlockIsOurs(mpVecD4))
        operator_delete_array(mpVecD4);
    if (BlockIsOurs(mpVecC0))
        operator_delete_array(mpVecC0);
    if (BlockIsOurs(mpVecAc))
        operator_delete_array(mpVecAc);
    if (BlockIsOurs(mpVec94))
        operator_delete_array(mpVec94);
    if (BlockIsOurs(mpVec80))
        operator_delete_array(mpVec80);
    if (BlockIsOurs(mpVec64))
        operator_delete_array(mpVec64);
    if (BlockIsOurs(mpVec50))
        operator_delete_array(mpVec50);

    u32 n = ((u32)mpBits40 - (u32)mpBits38) & 0xfffffffe;
    if ((int)n > 2 && mpBits38 != 0)
        operator_delete_array(mpBits38);

    if (mpField20 != 0)
        ((void (__thiscall *)(void *))((void **)*(void **)mpField20)[1])(mpField20);

    ((SubsystemDtorFn)0x00b5b9a0)(&mpSubVtbl);
    mpVtbl = (void *)0x013eb394;
}

// @ 0x00b85bc0
void *PaintSystemPool::InitPool(void *a, void *b)
{
    FixedPoolBase fixedPool;
    fixedPool.m0 = 0;
    ((FixedPoolInitFn)0x00921260)(&fixedPool, mNodes, 0x12000, 0x24, 4, 0);

    fixedPool.mpBegin   = mNodes;
    fixedPool.mpEnd     = mNodes + 0x12000;
    fixedPool.mElemSize = 0x24;
    fixedPool.mpOwner   = (u8 *)this + 0x34;

    u32 nNodes = FUN_00921340(0x200);
    ((PoolInitNodesFn)0x00b83a40)(this, nNodes, a, &b, &b, b, &b, &fixedPool);

    mBoundHigh = *(const u32 *)0x013f0620;   // 10000.0f
    mBoundLow  = *(const u32 *)0x01470f1c;   // 2.0f
    mField18   = 0;
    fixedPool.mpBegin = 0;                   // +0x08 cleared before the size query
    u32 need = ((PoolSizeFn)0x009213c0)(&fixedPool, mCount);
    if (need > mSize)
        ((PoolGrowFn)0x00b7f510)(this, need);
    return this;
}

// @ 0x00b85ca0
void *TileMapIndex::IndexLookup(void *pKey)
{
    LookupBuffer buf;
    ((MapFindFn)0x00b83af0)(this, &buf, pKey);
    if (buf.mRec[0] == (u32)mpTable[mIndex]) {
        const u32 *pIn = (const u32 *)pKey;
        buf.key.m0  = pIn[0];
        buf.key.m4  = pIn[1];
        buf.key.m8  = pIn[2];
        buf.mTail0  = buf.mRec[3];
        buf.mTail1  = buf.mRec[4];
        buf.key.mC  = buf.mRec[0];
        buf.key.m10 = buf.mRec[1];
        buf.key.m14 = buf.mRec[2];
        ((MapInsertFn)0x00b848f0)(this, &buf, &buf.key, (void *)((u32)pKey & 0xffffff00));
    }
    return (u8 *)buf.mRec[0] + 0xc;
}

// @ 0x00b85d40
Vec3f *SpVector3::insert(Vec3f *pos, const Vec3f *pVal)
{
    u32 idx = (u32)(pos - mpBegin);
    Vec3f *pOld = mpEnd;
    if (pos == pOld && pOld != mpCap) {
        mpEnd = pOld + 1;
        if (pOld != 0) {
            pOld->x = pVal->x;
            pOld->y = pVal->y;
            pOld->z = pVal->z;
        }
    } else {
        DoInsertValue(pos, pVal);
    }
    return mpBegin + idx;
}

// @ 0x00b85db0
void Vertex3DVec::push_back(const Vertex3D *pVal)
{
    Vertex3D *p = mpEnd;
    if (p < mpCap) {
        mpEnd = p + 1;
        if (p != 0) {
            p->x = pVal->x;
            p->y = pVal->y;
            p->z = pVal->z;
            p->w = pVal->w;
            p->m10 = pVal->m10;
            p->m14 = pVal->m14;
            p->m18 = pVal->m18;
            p->m1c = pVal->m1c;
            p->m20 = pVal->m20;
        }
        return;
    }
    GrowAndInsert(p, pVal);
}

// @ 0x00b85e10
void *SpVector20B::AssignN(u32 n, u32 unused)
{
    u8 *pBuf;
    if (n != 0)
        pBuf = (u8 *)operator_new(n * 0x14, "Simulator", 0, 0, (int)0x013ebb38, 0xd1);
    else
        pBuf = 0;
    u32 bytes = n * 0x14;
    Vec20BElem defaultValue;
    defaultValue.m[0] = 0;
    defaultValue.m[1] = 0;
    defaultValue.m[2] = 0;
    mpBegin = (u32 *)pBuf;
    mpEnd = (u32 *)pBuf;
    mpCap = (u32 *)(pBuf + bytes);
    u8 *pIt = pBuf;
    while (n > 0) {
        if (pIt != 0)
            ((Vec20BElem *)pIt)->Construct(&defaultValue);
        --n;
        pIt += 0x14;
    }
    mpEnd = (u32 *)((u8 *)mpBegin + bytes);
    return this;
}

// @ 0x00b85f30
void Vertex2DVec_Resize(void *pThis, u32 n)
{
    Vertex2DVec *p = (Vertex2DVec *)pThis;
    u32 size = (u32)(p->mpEnd - p->mpBegin);
    if (size < n) {
        FUN_00b84e90(p->mpEnd, n - size, 0);
        return;
    }
    FUN_720250_CopyVertex3D(p->mpEnd, p->mpEnd, p->mpBegin + n);
    p->mpEnd = p->mpEnd + (p->mpEnd - (p->mpBegin + n));
}

// @ 0x00b85fb0
void *ByteVec::CopyCtor(const ByteVec *pSrc)
{
    u32 bytes = (u32)(pSrc->mpEnd - pSrc->mpBegin);
    u8 *pBuf;
    if (bytes != 0)
        pBuf = (u8 *)operator_new(bytes, "Simulator", 0, 0, (int)0x013ebb38, 0xd1);
    else
        pBuf = 0;
    mpBegin = pBuf;
    mpEnd = pBuf;
    mpCap = pBuf + bytes;
    u32 n = (u32)(pSrc->mpEnd - pSrc->mpBegin);
    u8 *pDst = (u8 *)memcpy(pBuf, pSrc->mpBegin, n);
    mpEnd = pDst + n;
    return this;
}

// @ 0x00b86010
void *ByteVec::AssignFrom(const ByteVec *pSrc)
{
    if (pSrc == this)
        return this;
    u32 n = (u32)(pSrc->mpEnd - pSrc->mpBegin);
    u32 cap = (u32)(mpCap - mpBegin);
    if (n > cap) {
        u8 *pNew = (u8 *)AllocAndCopy(n, pSrc->mpBegin, pSrc->mpEnd);
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpCap = pNew + n;
        mpEnd = mpBegin + n;
        return this;
    }
    u32 size = (u32)(mpEnd - mpBegin);
    if (n > size) {
        memcpy(mpBegin, pSrc->mpBegin, size);
        u8 *pSrc2 = pSrc->mpBegin + (mpEnd - mpBegin);
        memcpy(mpEnd, pSrc2, (u32)(pSrc->mpEnd - pSrc2));
        mpEnd = mpBegin + n;
        return this;
    }
    memcpy(mpBegin, pSrc->mpBegin, n);
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00b860d0
void *ByteVec::InsertFill(u8 *pos, u32 n, const u8 *pVal)
{
    u32 cap = (u32)(mpCap - mpEnd);
    if (n > cap) {
        u32 size = (u32)(mpEnd - mpBegin);
        u32 newCap = size * 2;
        if (size == 0)
            newCap = 1;
        u32 need = size + n;
        if (need > newCap)
            newCap = need;
        u8 *pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (u8 *)operator_new(newCap, "Simulator", 0, 0, (int)0x013ebb38, 0xd1);
        u32 headBytes = (u32)(pos - mpBegin);
        u8 *pMid = (u8 *)memcpy(pNew, mpBegin, headBytes) + headBytes;
        u8 value = *pVal;
        if (n != 0)
            memset(pMid, value, n);
        u32 tailBytes = (u32)(mpEnd - pos);
        u8 *pNewEnd = (u8 *)memcpy(pMid + n, pos, tailBytes) + tailBytes;
        if (BlockIsOurs(mpBegin))
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + newCap;
        return this;
    }
    if (n != 0) {
        u8 value = *pVal;
        u8 *pOldEnd = mpEnd;
        u32 tailBytes = (u32)(mpEnd - pos);
        if (tailBytes <= n) {
            u32 fillNew = n - tailBytes;
            if (fillNew != 0)
                memset(mpEnd, value, fillNew);
            mpEnd += fillNew;
            memcpy(mpEnd, pos, (u32)(pOldEnd - pos));
            mpEnd += (u32)(pOldEnd - pos);
            memset(pos, value, (u32)(pOldEnd - pos));
            return this;
        }
        u8 *pSrc = mpEnd - n;
        memcpy(mpEnd, pSrc, (u32)(mpEnd - pSrc));
        mpEnd += n;
        memmove(pSrc + (u32)(pos - mpBegin) - (u32)(pSrc - mpBegin), pos, (u32)(pSrc - pos));
        memset(pos, value, n);
    }
    return this;
}

// @ 0x00b86350
u32 *CopyVec20BForward(u32 *pFirst, u32 *pLast, u32 *pDst)
{
    u32 *pResult = pDst;
    if (pFirst != pLast) {
        do {
            pDst[0] = pFirst[0];
            pDst[1] = pFirst[1];
            Vec20BAssign((Vec20B *)(pDst + 2), (const Vec20B *)(pFirst + 2));
            pFirst += 7;
            pDst += 7;
        } while (pFirst != pLast);
        pResult = pDst;
    }
    return pResult;
}

// @ 0x00b86390
u32 *CopyVec20BBackward(u32 *pFirst, u32 *pLast, u32 *pDst)
{
    u32 *pResult = pDst;
    if (pLast != pFirst) {
        do {
            pLast -= 7;
            pDst -= 7;
            pDst[0] = pLast[0];
            pDst[1] = pLast[1];
            Vec20BAssign((Vec20B *)(pDst + 2), (const Vec20B *)(pLast + 2));
            pResult = pDst;
        } while (pLast != pFirst);
    }
    return pResult;
}

// @ 0x00b863e0
cGonzagoListener *cGonzagoListener::Ctor()
{
    m00 = 0x013eb384u;
    ((SubsystemCtorFn)0x00b5b960)(&mSubVtbl);
    m00 = 0x014654e0u;
    mSubVtbl   = 0x01465490u;
    mSubVtbl08 = 0x01465488u;

    m20 = 0;
    m24 = 0;
    m28 = *(float *)0x013eb1bc;
    m2c = 0;
    m30 = 0;
    m34 = 0;
    m40 = 0x01667baeu;
    m38 = 0x01667bacu;
    m3c = 0x01667bacu;
    m48 = 0;
    m4c = 0;
    m50 = 0;
    m54 = 0;
    m58 = 0;
    m64 = 0;
    m68 = 0;
    m6c = 0;
    m78 = 0;
    m7c = 0;
    m80 = 0;
    m84 = 0;
    m88 = 0;
    m94 = 0;
    m98 = 0;
    m9c = 0;
    mac = 0;
    mb0 = 0;
    mb4 = 0;
    mc0 = 0;
    mc4 = 0;
    mc8 = 0;
    md4 = 0;
    md8 = 0;
    mdc = 0;
    mf0 = 0;
    mec = 0xffffffffu;
    u32 tmp = 0;
    ((PaintSystemPool *)mpPool)->InitPool(&tmp, &tmp);
    return this;
}

// @ 0x00b87dc0
namespace SP {
void cPlanetModel_s00b8_7dc0::ComputeContinents()
{
  if (!mContinentMap || !mpISphere)
    return;

  const unsigned int threshold = FloatToHeight16(mpISphere->GetMap()->GetWaterLevel());
  const uint8_t* heights = mpISphere->GetMap()->mpHeights->mpData;
  uint32_t* cells = mContinentMap;

  UnionFind uf;
  uf.reserve(0x10000);
  {
    uint16_t* p = uf.mpEnd;
    int i = 0;
    do {
      *p = (uint16_t)i;
      i++;
      p++;
    } while (i < 0x10000);
    uf.mpEnd = p;
  }

  // Pass 1: classify every cell (land bit 30, partial-water bit 31, attribute word) from its
  // 2x2 block of height samples and label connected runs with union-find.
  const __m64 thr = _mm_set1_pi32((int)threshold - 1);
  const __m64 zero = _mm_setzero_si64();
  const __m64 ones = _mm_set1_pi32(-1);
  uint32_t nextLabel = 1;
  int rowBase = 0;
  const uint8_t* rowPtr = heights;
  uint32_t* prev = cells - 1;
  do {
    uint32_t row = 0;
    do {
      uint32_t col = 0;
      const uint8_t* sample = rowPtr;
      const uint8_t* info = rowPtr + 0x804;
      do {
        __m64 anyAbove = zero;
        __m64 allAbove = ones;
        const uint8_t* q = sample;
        int k = 2;
        do {
          __m64 v = *(const __m64*)q;
          __m64 lo = _mm_cmpgt_pi32(_mm_unpacklo_pi16(v, zero), thr);
          __m64 hi = _mm_cmpgt_pi32(_mm_unpackhi_pi16(v, zero), thr);
          anyAbove = _mm_or_si64(anyAbove, lo);
          anyAbove = _mm_or_si64(anyAbove, hi);
          allAbove = _mm_and_si64(allAbove, lo);
          allAbove = _mm_and_si64(allAbove, hi);
          q += 0x800;
        } while (--k);
        uint32_t land = (anyAbove.m64_u32[1] | anyAbove.m64_u32[0]) & 0x40000000;
        uint32_t cell = (~(allAbove.m64_u32[1] & allAbove.m64_u32[0]) & 0x80000000) |
                        *(const uint16_t*)info | land;
        prev[1] = cell;

        bool hasUp = false;
        if (row != 0 && (cells[rowBase + col - 0x80] & 0x40000000) == land)
          hasUp = true;
        bool hasLeft = false;
        if (col != 0 && (prev[0] & 0x40000000) == land)
          hasLeft = true;

        if (hasUp) {
          if (hasLeft) {
            uint32_t upLabel = cells[rowBase + col - 0x80] & 0x3fff0000;
            uint32_t leftLabel = prev[0] & 0x3fff0000;
            if (upLabel == leftLabel) {
              prev[1] = cell | upLabel;
            } else {
              uint16_t merged = uf.Union(upLabel >> 16, leftLabel >> 16);
              prev[1] |= (uint32_t)merged << 16;
            }
          } else {
            prev[1] = (cells[rowBase + col - 0x80] & 0x3fff0000) | cell;
          }
        } else if (hasLeft) {
          prev[1] = (prev[0] & 0x3fff0000) | cell;
        } else {
          prev[1] = ((nextLabel & 0x3fff) << 16) | cell;
          nextLabel++;
        }
        sample += 8;
        info += 8;
        col++;
        prev++;
      } while (col < 0x80);
      rowPtr += 0x1000;
      rowBase += 0x80;
      row++;
    } while (row < 0x80);
  } while (rowBase < 0x18000);
  _mm_empty();

  // Pass 2: merge labels across the cube-face seams (faces 0-3 against their higher neighbours).
  int startX[4] = {0, 0, 0x7f, 0x7f};
  int startY[4] = {0, 0x7f, 0x7f, 0};
  int stepX[4] = {1, 0, -1, 0};
  int stepY[4] = {0, -1, 0, 1};
  int outX[4] = {0, -1, 0, 1};
  int outY[4] = {-1, 0, 1, 0};
  int faceRow = 0;
  for (int f = 0; faceRow < 0x200; f++, faceRow += 0x80) {
    for (int j = 0; j < 4; j++) {
      int face = f;
      int x = outX[j] + startX[j];
      int y = outY[j] + startY[j];
      int dx = stepX[j];
      int dy = stepY[j];
      WrapCubeFace(0x80, &face, &x, &y, &dx, &dy);
      if (f < face) {
        uint32_t* cur = cells + (faceRow + startY[j]) * 0x80 + startX[j];
        int stride = stepY[j] * 0x80 + stepX[j];
        for (uint32_t t = 0; t < 0x80; t++) {
          uint32_t other = cells[(face * 0x80 + y) * 0x80 + (dy * 0x80 + dx) * t + x];
          if (((other ^ *cur) & 0x40000000) == 0)
            uf.Union((*cur >> 16) & 0x3fff, (other >> 16) & 0x3fff);
          cur += stride;
        }
      }
    }
  }

  const unsigned int regions = (unsigned int)uf.Flatten(nextLabel, 0x3ff);
  mContinentAboveWater.resize(regions);
  mContinentAreas.clear();
  mContinentAreas.resize(regions);

  // Pass 3: replace the provisional labels by the flattened ones, accumulate the region areas and
  // above-water flags, and fold in the per-cell attribute nibble (two cells per byte).
  const uint8_t* nibbles = mCellNibbles;
  uint8_t* aboveWater = mContinentAboveWater.mpBegin;
  uint32_t* areas = mContinentAreas.mpBegin;
  uint32_t* end = cells + 0x18000;
  for (uint32_t* p = cells; p < end; p += 2) {
    uint32_t b = *nibbles++;
    uint32_t c0 = p[0];
    uint32_t id0 = uf.mpBegin[((const uint16_t*)p)[1] & 0x3fff] & 0x3ff;
    uint32_t n0 = (c0 & 0xc000ffff) | ((((b & 0xf0) << 6) | id0) << 16);
    p[0] = n0;
    aboveWater[id0] = (uint8_t)((n0 >> 30) & 1);
    areas[id0]++;

    uint32_t c1 = p[1];
    uint32_t id1 = uf.mpBegin[((const uint16_t*)p)[3] & 0x3fff] & 0x3ff;
    uint32_t n1 = (c1 & 0xc000ffff) | ((((b & 0xf) << 10) | id1) << 16);
    p[1] = n1;
    aboveWater[id1] = (uint8_t)((n1 >> 30) & 1);
    areas[id1]++;
  }
  mContinentMapDirty = false;
}
}  // namespace SP

// @ 0x00b88420
namespace SP {
void cPlanetModel_s00b8_7dc0::Refresh()
{
  if (mContinentMapDirty) {
    mContinentMapDirty = false;
    ComputeContinents();
  }
}
}  // namespace SP

// @ 0x00b88430
namespace SP {
void Vector20::insert(Element20* pos, const Element20* value)
{
  if (mpEnd != mpCapacity) {
    const Element20* v = value;
    if (v >= pos && v < mpEnd)
      v = v + 1;
    if (mpEnd)
      new (mpEnd) Element20(*(mpEnd - 1));
    FUN_00b85980(pos, mpEnd - 1, mpEnd);
    *pos = *v;
    ++mpEnd;
  } else {
    unsigned int count = (unsigned int)(mpEnd - mpBegin);
    unsigned int newCapacity = count ? count * 2 : 1;
    Element20* buffer = newCapacity
        ? (Element20*)operator new[](newCapacity * sizeof(Element20),
            (const char*)0x13f09b4, 0, 0, (const char*)0x13ebb38, 0xd1)
        : 0;
    unsigned int prefixBytes = (unsigned int)((char*)pos - (char*)mpBegin);
    Element20* newPos = (Element20*)MemMove(buffer, mpBegin, prefixBytes) + (pos - mpBegin);
    if (newPos)
      new (newPos) Element20(*value);
    unsigned int suffixBytes = (unsigned int)((char*)mpEnd - (char*)pos);
    Element20* newEnd = (Element20*)MemMove(newPos + 1, pos, suffixBytes) + (mpEnd - pos);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      operator_delete__(mpBegin);
    mpBegin = buffer;
    mpEnd = newEnd;
    mpCapacity = buffer + newCapacity;
  }
}
}  // namespace SP

// @ 0x00b88590
namespace SP {
uint32_t cPlanetModel_s00b8_7dc0::GetCellValue(const Vector3_s00b8_7dc0* dir)
{
  if (mContinentMapDirty) {
    mContinentMapDirty = false;
    ComputeContinents();
  }

  float x = dir->x;
  float y = dir->y;
  float z = dir->z;
  float ax = (float)fabs((double)x);
  float ay = (float)fabs((double)y);
  float az = (float)fabs((double)z);

  int u;
  int v;
  int face;
  if (az >= ax && az >= ay) {
    u = (int)((x / z + 1.0f) * 64.0f);
    v = (int)((y / az + 1.0f) * 64.0f);
    face = z < 0.0f ? 1 : 0;
  } else if (ay >= ax) {
    u = (int)((z / y + 1.0f) * 64.0f);
    v = (int)((x / ay + 1.0f) * 64.0f);
    face = y < 0.0f ? 5 : 4;
  } else {
    u = (int)((y / x + 1.0f) * 64.0f);
    v = (int)((z / ax + 1.0f) * 64.0f);
    face = x < 0.0f ? 3 : 2;
  }

  if (u == 0x80) u = 0x7f;
  if (v == 0x80) v = 0x7f;
  unsigned int index = (unsigned int)(((face << 7) + v) << 7) + (unsigned int)u;
  const uint16_t* cellWords = (const uint16_t*)mContinentMap;
  return cellWords[index * 2 + 1] & 0x3ff;
}
}  // namespace SP

// @ 0x00b894a0
int32_t cCellGrid::CellFromDirection(float* dir)
{
    float x = dir[0];
    float ax = Abs(x);
    float y = dir[1];
    float ay = Abs(y);
    float z = dir[2];
    float az = Abs(z);

    int iX, iY, iFace;
    if (az < ax || az < ay) {
        if (ay < ax) {
            iX = (int)((y / x + 1.0f) * 32.0f);
            iY = (int)((z / ax + 1.0f) * 32.0f);
            if (x < kZero)
                iFace = 3;
            else
                iFace = 2;
        } else {
            iX = (int)((z / y + 1.0f) * 32.0f);
            iY = (int)((x / ay + 1.0f) * 32.0f);
            if (y < kZero)
                iFace = 5;
            else
                iFace = 4;
        }
    } else {
        iX = (int)((x / z + 1.0f) * 32.0f);
        iY = (int)((y / az + 1.0f) * 32.0f);
        if (z < kZero)
            iFace = 1;
        else
            iFace = 0;
    }
    if (iX == 0x40) iX = 0x3f;
    if (iY == 0x40) iY = 0x3f;

    int32_t result = mpCells[mpGrid[(iFace * 0x40 + iY) * 0x40 + iX]].mId;
    if (result == 0) {
        void* nounMgr = FUN_00b3d300();
        GameDataVec* gv = TCS(GameDataVec*, (void*, void*, void*, void*, void*, void*), FUN_00b21340)(
            nounMgr, (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
            (void*)FUN_00b1e500, (void*)&DAT_018c43e8);
        int32_t* it = gv->mpBegin;
        if (it != gv->mpEnd) {
            Vec3 local;
            float* c = (float*)TCS(Vec3*, (void*, void*), FUN_00bd9480)((void*)(uint32_t)*it, &local);
            result = *it;
            float best = (dir[1] - c[1]) * (dir[1] - c[1]) + (dir[2] - c[2]) * (dir[2] - c[2]) +
                         (dir[0] - c[0]) * (dir[0] - c[0]);
            while (++it != gv->mpEnd) {
                c = (float*)TCS(Vec3*, (void*, void*), FUN_00bd9480)((void*)(uint32_t)*it, &local);
                float d = (dir[1] - c[1]) * (dir[1] - c[1]) + (dir[2] - c[2]) * (dir[2] - c[2]) +
                          (dir[0] - c[0]) * (dir[0] - c[0]);
                if (best > d) {
                    result = *it;
                    best = d;
                }
            }
            return result;
        }
        result = 0;
    }
    return result;
}

// @ 0x00b89770
void OuterVec::PushDefault()
{
    Vec3Vec* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e) {
            e->mpBegin = 0;
            e->mpEnd = 0;
            e->mpCapacity = 0;
        }
        return;
    }
    Vec3Vec value;
    DoInsertValue(e, value);
    value.Free();
}

// @ 0x00b89830
void Vec1c::DoInsertValue28(Elem1c* position, const Elem1c& value)
{
    Elem1c* pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        const Elem1c* pv = &value;
        if (pv >= position && pv < pEnd)
            pv = pv + 1;
        if (pEnd) {
            pEnd->mA = pEnd[-1].mA;
            pEnd->mB = pEnd[-1].mB;
            TCS(void, (void*, void*), FUN_00473460)(&pEnd->mVec, (void*)&pEnd[-1].mVec);
        }
        FUN_00b86390(position, mpEnd - 1, mpEnd);
        position->mA = pv->mA;
        position->mB = pv->mB;
        position->mVec = pv->mVec;
        mpEnd += 1;
        return;
    }

    int count = (int)(mpEnd - mpBegin);
    uint32_t newCap = (count != 0) ? (uint32_t)(count * 2) : 1;
    Elem1c* pNewData = newCap
        ? (Elem1c*)FUN_00f473a0(newCap * 0x1c, "Simulator", 0, 0, ALLOC_FILE, 0xd1)
        : 0;
    Elem1c* dst = (Elem1c*)FUN_00b850c0(mpBegin, position, pNewData);
    FUN_00b7f6d0(mpBegin, position, pNewData);
    if (dst) {
        dst->mA = value.mA;
        dst->mB = value.mB;
        TCS(void, (void*, void*), FUN_00473460)(&dst->mVec, (void*)&value.mVec);
    }
    Elem1c* pNewEnd = (Elem1c*)FUN_00b850c0(position, mpEnd, dst + 1);
    FUN_00b7f6d0(position, mpEnd, dst + 1);
    if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
        FUN_00f47380(mpBegin);
    mpEnd = pNewEnd;
    mpBegin = pNewData;
    mpCapacity = (Elem1c*)((char*)pNewData + (uint32_t)newCap * 0x1c);
}

// @ 0x00b899b0
void cNatlBounds::AddBoundary(const Vec3* p2, const Vec3* p3, uint32_t count, uint32_t id)
{
    mVec34.push_back(id);
    mVec0c.PushDefault();
    mVec20.PushDefault();
    mVec0c.mpEnd[-1].assignRange(p3, p3 + count, id);
    mVec20.mpEnd[-1].assignRange(p2, p2 + count, id);
}

// @ 0x00b89a30
void cNatlBoundsBuilder::Build(TileMap* tiles)
{
    cPlanetModel* planet = SP_PlanetModel_s00b8_9a30();
    mpBounds.reset0();
    if (!mbEnabled)
        return;

    float water = planet->GetWaterHeight();
    planet->GetTerrain();

    vector<Vec3_s00b8_9a30> ground;
    vector<Vec3_s00b8_9a30> curve;
    curve.reserve(1000);
    ground.reserve(1000);
    cGameNounManager* nouns = SP_NounManager();
    nouns->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                        (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);
    mpBounds = new("Simulator/NatlBounds", 0, 0, 0, 0) cNatlBounds_s00b8_9a30();

    for (TileIterator it(tiles->mpBucketArray); it.mpNode != tiles->end_node(); it.increment()) {
        TileNode* node = it.mpNode;
        for (int edge = 0; edge < 4; ++edge) {
            if (node->mDone[edge])
                continue;
            int level = node->mLevel[edge];
            if (level <= 0)
                continue;

            TileKey key = node->mKey;
            ground.clear();
            curve.clear();
            Vec3_s00b8_9a30 p0 = node->mPos;
            Vec3_s00b8_9a30 p1 = node->mPos;
            int dx = gDirX[edge];
            int dy = gDirY[edge];
            TileKey startKey;
            Vec3_s00b8_9a30 prevCtrl;

            for (int i = 0; i <= 2000; ++i) {
                key.x += dx;
                key.y += dy;
                FUN_00b7e220(0x40, &key, &dx, &dy);
                TileIterator next = tiles->find(key);
                if (next.mpNode == tiles->end_node())
                    break;
                TileNode* n = next.mpNode;

                // Pick the outgoing edge: rotate away from edges on the same side.
                uint32_t dir = (dx + dy + (dx & 1) + ((dy & 1) + 1) * 2) & 3;
                if (n->mLevel[dir] == level) {
                    dir = (dir + 1) & 3;
                    if (n->mLevel[dir] == level) {
                        dir = (dir + 1) & 3;
                        if (n->mLevel[dir] == level)
                            dir = (dir + 1) & 3;
                    }
                } else {
                    dir = (dir - 1) & 3;
                    if (n->mLevel[(dir - 1) & 3] == level) {
                        dir = (dir - 1) & 3;
                        if (n->mLevel[(dir - 1) & 3] == level)
                            dir = (dir - 1) & 3;
                    }
                }
                n->mDone[dir] = true;
                Vec3_s00b8_9a30 p2 = n->mPos;

                if (i > 0) {
                    Vec3_s00b8_9a30 toNext = p2 - p1;
                    Vec3_s00b8_9a30 toPrev = p0 - p1;
                    float cosA = Clamp(toPrev.Dot(toNext) / (toNext.Length() * toPrev.Length()),
                                       -1.0f, 0.999f);
                    Vec3_s00b8_9a30 n0 = Cross(p0, p1).Normalized();
                    Vec3_s00b8_9a30 n1 = Cross(p1, p2).Normalized();
                    float bend = sqrtf(2.0f / (1.0f - cosA));
                    Vec3_s00b8_9a30 ctrl = (n1 + n0).Normalized() * 5.0f * bend + p1;

                    if (i > 1) {
                        Vec3_s00b8_9a30 dPos = p1 - p0;
                        Vec3_s00b8_9a30 dCtrl = ctrl - prevCtrl;
                        for (int j = 0; j < 3; ++j) {
                            float t = (float)j / 3.0f;
                            Vec3_s00b8_9a30 a = dPos * t + p0;
                            float hA = Max(water, planet->GetHeightAt(a)) + 0.6f;
                            Vec3_s00b8_9a30 b = dCtrl * t + prevCtrl;
                            float hB = Max(water, planet->GetHeightAt(b)) + 0.6f;
                            float h = hB * 0.6f + hA * 0.4f;
                            ground.push_back(a * (hA / a.Length()));
                            curve.push_back(b * (h / b.Length()));
                        }
                        if (key == startKey)
                            break;
                    } else if (i == 1) {
                        startKey = key;
                    }
                    prevCtrl = ctrl;
                }
                p0 = p1;
                p1 = p2;
                dx = gDirX[dir];
                dy = gDirY[dir];
            }

            ground.push_back(ground.front());
            curve.push_back(curve.front());
            mpBounds->AddBoundary(ground.begin(), curve.begin(), (int)ground.size(), level);
        }
    }
    mbBuilt = true;
}

// @ 0x00b8a760
namespace SP {
void cPlanetModel_s00b8_a760::RebuildPoliticalZones()
{
    float radius = GetRadius();
    uint8_t* zoneMap = mPoliticalZoneIdxMap;
    mTileMap.clear();

    for (int face = 0; face < 6; ++face) {
        int yMin = (face + 2) >> 2;
        int xMin = face >> 2;
        for (int y = yMin; y <= 0x40 - yMin; ++y) {
            for (int x = xMin; x <= 0x40 - xMin; ++x) {
                CubeCell cells[4];
                cells[0].x = x - 1; cells[0].y = y - 1; cells[0].face = face;
                cells[1].x = x;     cells[1].y = y - 1; cells[1].face = face;
                cells[2].x = x;     cells[2].y = y;     cells[2].face = face;
                cells[3].x = x - 1; cells[3].y = y;     cells[3].face = face;
                if ((cells[0].x | cells[0].y) & ~63)
                    WrapCubeFace(64, &cells[0].face, &cells[0].x, &cells[0].y, 0, 0);
                if ((cells[1].x | cells[1].y) & ~63)
                    WrapCubeFace(64, &cells[1].face, &cells[1].x, &cells[1].y, 0, 0);
                if ((cells[2].x | cells[2].y) & ~63)
                    WrapCubeFace(64, &cells[2].face, &cells[2].x, &cells[2].y, 0, 0);
                if ((cells[3].x | cells[3].y) & ~63)
                    WrapCubeFace(64, &cells[3].face, &cells[3].x, &cells[3].y, 0, 0);
                char c[4];
                c[0] = zoneMap[(cells[0].face * 64 + cells[0].y) * 64 + cells[0].x];
                c[1] = zoneMap[(cells[1].face * 64 + cells[1].y) * 64 + cells[1].x];
                c[2] = zoneMap[(cells[2].face * 64 + cells[2].y) * 64 + cells[2].x];
                c[3] = zoneMap[(cells[3].face * 64 + cells[3].y) * 64 + cells[3].x];
                if (c[0] != c[1] || c[0] != c[2] || c[0] != c[3]) {
                    TileKey_s00b8_a760 wrapped;
                    wrapped.x = x; wrapped.y = y; wrapped.z = face;
                    ((void (__cdecl *)(uint32_t, void *, int *, int *))FUN_00b7e220)(64, &wrapped, 0, 0);
                    TileKey_s00b8_a760 key;
                    key.x = x; key.y = y; key.z = face;
                    TileValue& value = mTileMap[key];
                    Vec3 pv;
                    CubeVertexDirection(face, VertexCoord(x), VertexCoord(y), &pv.x);
                    value.mPos = pv;
                    value.mLevel[0] = c[0];
                    value.mLevel[1] = c[1];
                    value.mLevel[2] = c[2];
                    value.mLevel[3] = c[3];
                    value.mDone[0] = c[3] == c[0];
                    value.mDone[1] = c[0] == c[1];
                    value.mDone[2] = c[1] == c[2];
                    value.mDone[3] = c[2] == c[3];
                }
            }
        }
    }

    for (TileIterator_s00b8_a760 it(mTileMap.mpBucketArray); it.mpNode != mTileMap.end_node(); it.increment()) {
        TileNode_s00b8_a760* node = it.mpNode;
        float sx = 0.0f, sy = 0.0f, sz = 0.0f;
        int borders = 0;
        int prev = 3;
        for (int i = 0; i < 4; ++i) {
            if (node->mValue.mLevel[prev] != node->mValue.mLevel[i]) {
                TileKey_s00b8_a760 key;
                uint32_t a = (i & 2) - 1;
                uint32_t b = (i & 1) - 1;
                key.x = node->mKey.x + (b & a);
                key.y = node->mKey.y + (~b & a);
                key.z = node->mKey.z;
                ((void (__cdecl *)(uint32_t, void *, int *, int *))FUN_00b7e220)(64, &key, 0, 0);
                float v[3];
                CubeVertexDirection(key.z, VertexCoord(key.x), VertexCoord(key.y), v);
                ++borders;
                sx = sx + v[0];
                sy = v[1] + sy;
                sz = v[2] + sz;
            }
            prev = i;
        }
        float d[3];
        CubeVertexDirection(node->mKey.z, VertexCoord(node->mKey.x), VertexCoord(node->mKey.y), d);
        if (borders == 2) {
            float wx = d[0] * 2.0f + sx;
            float wy = d[1] * 2.0f + sy;
            float wz = d[2] * 2.0f + sz;
            float inv = 1.0f / sqrtf(wx * wx + (wy * wy + wz * wz));
            node->mValue.mPos.x = inv * wx * radius;
            node->mValue.mPos.y = wy * inv * radius;
            node->mValue.mPos.z = wz * inv * radius;
        } else {
            node->mValue.mPos.x = d[0] * radius;
            node->mValue.mPos.y = d[1] * radius;
            node->mValue.mPos.z = d[2] * radius;
        }
    }

    mpNatlBoundsBuilder->Build(&mTileMap);
}
}  // namespace SP

// @ 0x00b8aea0
namespace SP {
void cPlanetModel_s00b8_aea0::BuildPoliticalZoneMap()
{
    g_PoliticalZoneUpdateCount++;
    if (g_PoliticalZoneUpdateBusy) {
        g_PoliticalZoneUpdatePending = 1;
        return;
    }

    FixedIDVector continents;
    FixedVector3Vector directions;
    uint8_t* zoneMap = mPoliticalZoneIdxMap;
    int numZones = mPoliticalZonesEnd - mPoliticalZonesBegin;
    g_PoliticalZoneUpdatePending = 0;
    g_PoliticalZoneUpdateBusy = 1;
    continents.push_back(0);
    directions.push_back(Vector3_s00b8_aea0(0.0f, 0.0f, 0.0f));

    for (int i = 1; i < numZones; i++) {
        continents.push_back(GetContinent(&mPoliticalZonesBegin[i].mCenter));
        Vector3_s00b8_aea0 c = mPoliticalZonesBegin[i].mCenter;
        float inv = 1.0f / sqrtf(c.z * c.z + c.y * c.y + c.x * c.x + 1e-8f);
        Vector3_s00b8_aea0 dir(inv * c.x, inv * c.y, inv * c.z);
        directions.push_back(dir);
    }

    // 1 = texel on a land continent big enough to hold a zone; zone bits are or'ed in later.
    MaskVector<6 * 64 * 64> mask;
    uint32_t* p = mask.mpBegin;
    for (int face = 0; face < 6; face++) {
        for (int y = 0; y < 64; y++) {
            float fy = TexelCoord(y);
            for (int x = 0; x < 64; x++) {
                float v[3];
                CubeTexelDirection(face, TexelCoord(x), fy, v);
                int continent = GetContinent((const Vector3_s00b8_aea0*)v);
                bool land = mContinentFlags[continent] == 0;
                uint32_t area = (continent >= 0 && continent < (int)(mContinentAreasEnd - mContinentAreasBegin))
                                    ? mContinentAreasBegin[continent] : 0;
                *p++ = (land && area >= 40) ? 1 : 0;
            }
        }
    }

    {
        char allocator;
        CubeCellVectorVector frontier(numZones, allocator);
        CubeCellVectorVector pending(numZones, allocator);
        frontier[0].reserve(100);
        for (int i = 1; i < numZones; i++) {
            frontier[i].reserve(100);
            pending[i].reserve(100);
            const Vector3_s00b8_aea0& d = directions.mpBegin[i];
            float ax = fabs(d.x);
            float ay = fabs(d.y);
            float az = fabs(d.z);
            CubeCell cell;
            if (az >= ax && az >= ay) {
                cell.x = (int)((d.x / d.z + 1.0f) * 32.0f);
                cell.y = (int)((d.y / az + 1.0f) * 32.0f);
                cell.face = (d.z >= 0.0f) ? 0 : 1;
            } else if (ay >= ax) {
                cell.x = (int)((d.z / d.y + 1.0f) * 32.0f);
                cell.y = (int)((d.x / ay + 1.0f) * 32.0f);
                cell.face = (d.y >= 0.0f) ? 4 : 5;
            } else {
                cell.x = (int)((d.y / d.x + 1.0f) * 32.0f);
                cell.y = (int)((d.z / ax + 1.0f) * 32.0f);
                cell.face = (d.x >= 0.0f) ? 2 : 3;
            }
            if (cell.x == 64)
                cell.x = 63;
            if (cell.y == 64)
                cell.y = 63;
            pending[i].push_back(cell);
        }

        for (int iter = 3; iter <= 16; iter++) {
            float cosLimit = cosf(3.14159274f * 0.0625f * iter);
            for (int i = 1; i < numZones; i++) {
                frontier[i] = pending[i];
                pending[i].clear();
            }
            bool changed;
            do {
                changed = false;
                uint32_t bit = 2;
                for (int i = 1; i < numZones; i++, bit <<= 1) {
                    CubeCellVector& cells = frontier[i];
                    int count = cells.size();
                    for (int j = 0; j < count; j++) {
                        CubeCell& c = cells[j];
                        int x = c.x;
                        int y = c.y;
                        int face = c.face;
                        float v[3];
                        CubeTexelDirection(face, TexelCoord(x), TexelCoord(y), v);
                        const Vector3_s00b8_aea0& d = directions.mpBegin[i];
                        if (cosLimit > d.y * v[1] + d.z * v[2] + v[0] * d.x) {
                            pending[i].push_back(c);
                        } else {
                            uint32_t& m = mask.mpBegin[(face * 64 + y) * 64 + x];
                            uint32_t old = m;
                            m = old | bit;
                            if (old == 0) {
                                CubeCell neighbors[4];
                                neighbors[0].x = c.x - 1;
                                neighbors[0].y = c.y;
                                neighbors[0].face = c.face;
                                neighbors[1].x = c.x + 1;
                                neighbors[1].y = c.y;
                                neighbors[1].face = c.face;
                                neighbors[2].x = c.x;
                                neighbors[2].y = c.y - 1;
                                neighbors[2].face = c.face;
                                neighbors[3].x = c.x;
                                neighbors[3].y = c.y + 1;
                                neighbors[3].face = c.face;
                                for (int k = 0; k < 4; k++) {
                                    CubeCell& n = neighbors[k];
                                    if ((n.x | n.y) & ~63)
                                        WrapCubeFace(64, &n.face, &n.x, &n.y, 0, 0);
                                }
                                frontier[0].insert(frontier[0].mpEnd, neighbors, neighbors + 4);
                            }
                        }
                    }
                    if (!frontier[0].empty())
                        changed = true;
                    cells.swap(frontier[0]);
                    frontier[0].clear();
                }
            } while (changed);
        }
    }

    uint32_t* bits = mask.mpBegin;
    uint8_t* out = zoneMap;
    for (int face = 0; face < 6; face++) {
        for (int y = 0; y < 64; y++) {
            float fy = TexelCoord(y);
            for (int x = 0; x < 64; x++) {
                uint32_t zoneBits = *bits;
                float v[3];
                CubeTexelDirection(face, TexelCoord(x), fy, v);
                int best = 0;
                float bestDot = -1.0f;
                uint32_t bit = 2;
                for (int k = 1; k < numZones; k++, bit <<= 1) {
                    if (zoneBits & bit) {
                        const Vector3_s00b8_aea0& d = directions.mpBegin[k];
                        float dot = d.y * v[1] + d.x * v[0] + d.z * v[2];
                        if (dot > bestDot) {
                            bestDot = dot;
                            best = k;
                        }
                    }
                }
                out[x] = (uint8_t)best;
                bits++;
            }
            out += 64;
        }
    }

    RebuildPoliticalZones();
}
}  // namespace SP

// @ 0x00b8bb70
bool cPlanetModel_s00b8_bb70::FindClosestWater(const SVector3* pOrigin, float fDirection, SVector3* pOut)
{
    return RayCast(pOrigin, fDirection, pOut, 1.0f, true, 0);
}

// @ 0x00b8d2a0
bool cPlanetModel_s00b8_d190::HandleMessage(uint32_t id, void* msg)
{
    if (id == 0x1b537e5) {
        int32_t value = 0;
        if (msg != 0) {
            value = ((int32_t*)msg)[2];
        }
        UpdateMinimap(0, 1, value);
        return true;
    }
    if (id == 0x44448ed) {
        mFieldEA = 1;
        mField78 = 1;
    } else if (id == 0x45fe992) {
        mField78 = 1;
    }
    return false;
}

// @ 0x00b8d2f0
void cPlanetModel_s00b8_d190::FUN_00b8d2f0()
{
    if (mField20 != 0) {
        mField20->v43();
        FUN_00b8c0f0();
    }
    mFieldEC = -1;
}
