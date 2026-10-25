// src/game/SPGonzago/SPPlanetModel.cpp -- migrated from slice(s) s00b8d190, s00b8aea0, s00b8a760, s00b89a30, s00b894a0, s00b85380, s00b80630, s00b7f920 by tools/migrate/rewrite.py
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
extern "C" float sqrtf(float);
extern "C" void  operator_delete_array(void *p);                                     // 0xf47380
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long *, long);
extern "C" long __cdecl _InterlockedExchange(volatile long *, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long *);
extern const float kOne;      // 0x1485720 = 1.0f
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
