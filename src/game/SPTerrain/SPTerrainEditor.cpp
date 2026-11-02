// src/game/SPTerrain/SPTerrainEditor.cpp -- migrated from slice(s) s00f6df40, s00f69a30, s00f67e70, s00f66f80, s00f66050, s00f4c300, s00f4baa0, s00f4aaf0, s00f6b9a0, s00f6a960 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainEditor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <intrin.h>
#include "SP/cTerrainSphere.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/Swarm/cTransform.h"
#include <math.h>
#include "SP/cTextureInstance.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Swarm/cEffectParams.h"
#include "SP/cTerrainDistributeInfo.h"
#include "SP/cTerrainMapSet.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s00f6a960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __stdcall GetImageResource(void* handle);          // 0x00576650 (ret 4)
extern "C" void* __cdecl operator_new(int size, const char* file, int line, int a3,
                                      const char* name, int line2);  // 0x00f473a0
extern const char kAllocFile[];      // 0x013f09b4  "Simulator"
extern const char kAllocFile2[];     // 0x013ebb38
extern "C" void __cdecl VectorCopy(void* dst, const void* src, int elemSize, int count,
                                   void* ctor);   // 0x00406540
extern "C" void __cdecl kVec3Ctor();              // 0x004098a0
struct Vec4 { float x, y, z, w; Vec4() {} Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct Vec3 { float x, y, z; Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Rect { float x0, y0, x1, y1; };
struct Handle { uint32_t value; uint32_t flags; };   // lazily resolved resource handle (bit0 = resolved)
struct IResolver { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
                   virtual void Resolve(Handle* h); };                                  // +0x34
struct IViewportInfo { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
                       virtual void Query(uint32_t a, uint32_t b, int* px, int* py, int* w, int* h); }; // +0x24
IResolver* __cdecl GetResolver();       // 0x0067dd60
IViewportInfo* __cdecl GetViewportInfo(); // 0x0067dda0
struct ShaderIds { char pad[4]; uint32_t id; };      // [ptr+4] is the shader id
struct ShaderTable { char pad34[0x34]; ShaderIds* s34; ShaderIds* s38; ShaderIds* s3c; };
ShaderTable* __cdecl GetShaderTable();    // 0x00f48a60
void __cdecl SetShaderConst(int slot, const void* data, int zero);   // 0x00777ae0
struct Binding {
    uint32_t m0, m4, m8, mc;
    Binding(uint32_t shader, int index, uint32_t value);
    ~Binding();
};
struct DrawData {                 // object returned by Owner-arg vtable slot 4 (+0x10)
    char pad00[0x31c];
    Handle* h31c;
    Handle* h320;
    Handle* h324;
    Handle* h328;
    char pad32c[0x43c - 0x32c];
    Vec4 c43c;
    Vec4 c44c;
    Vec4* Query1(Vec4* tmp);      // 0x00fb9ad0
    Vec4* Query2(Vec4* tmp);      // 0x00fb9ca0
};
struct Source {                   // arg1: vtable +0x10 returns DrawData; indexed handle getters
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual DrawData* GetData();   // +0x10
    uint32_t TexA(int i);         // 0x00f98260
    uint32_t TexB(int i);         // 0x00f98270
    uint32_t TexC(int i);         // 0x00f98280
};
struct Viewer {
    void SetRaster(const void* r, int flag);   // 0x007c4be0
    bool Update();                             // 0x007c4fd0
    void Finish();                             // 0x007c3c10
};
struct IBatch {
virtual void v0();
virtual void v1();
    virtual bool Alloc(void** out, int stride, int count, int zero);   // +0x08
    virtual bool Apply(uint32_t shader, void* arg);                    // +0x0c
    virtual void Flush();                                              // +0x10
};
struct Compositor {
    char pad00[0x1c];
    Viewer* mViewer;
    char pad20[0x200 - 0x20];
    IBatch* mBatch;
    bool Draw(Source* src, const uint32_t* raster, int a3, Rect r,
              float v0, float v1, float v2, int a11, void* a12);       // 0x00f6a960
};
static inline uint32_t ResolveHandle(Handle* h)
{
    if (!(h->flags & 1))
        GetResolver()->Resolve(h);
    return h->value;
}
static inline void RefRelease(int* p)
{
    volatile long* c = (volatile long*)p;
    _InterlockedDecrement(c);
    if (_InterlockedExchangeAdd(c, 0) < 1)
        _InterlockedIncrement(c);
    else
        _InterlockedExchangeAdd(c, 0);
}
struct ImgDesc {
    char* mpRes;                 // +0x00  intrusive resource pointer (counter at +8)
    uint8_t m04;                 // +0x04
    uint8_t m05;                 // +0x05
    uint8_t m06;                 // +0x06
    char  _pad07;
    float m08;                   // +0x08
    uint32_t m0c;                // +0x0c
    float m10;                   // +0x10
    float m14;                   // +0x14
    float m18;                   // +0x18
    float m1c;                   // +0x1c
    float m20;                   // +0x20
    float m24;                   // +0x24
    float m28;                   // +0x28
    float m2c;                   // +0x2c
    float m30;                   // +0x30
    float m34;                   // +0x34
    float m38;                   // +0x38
    uint32_t m3c;                // +0x3c
    float m40;                   // +0x40
    float m44;                   // +0x44
    float m48;                   // +0x48
    float m4c;                   // +0x4c
    float m50;                   // +0x50
    float m54;                   // +0x54
    float m58;                   // +0x58
    float m5c;                   // +0x5c
    float m60;                   // +0x60
    float m64;                   // +0x64
    float m68;                   // +0x68
    uint32_t m6c;                // +0x6c
    uint32_t m70;                // +0x70
    uint32_t m74;                // +0x74

    ImgDesc(const ImgDesc& o);          // 0x00f6b000
    ImgDesc& Assign(const char* rec);    // 0x00f6b330
};
struct TexBlock {                // 0xe0 bytes of packed floats
    float v[0xe0 / 4];
    TexBlock() {}
    TexBlock(const TexBlock& o) { for (int i = 0; i < 0xe0 / 4; ++i) v[i] = o.v[i]; }
};
struct TexDesc {                 // 0x1c4 bytes
    uint32_t m00;
    TexBlock b[2];               // +0x04 and +0xe4 (0xe0 each)
    TexDesc() {}
};
TexDesc** CopyTexRange(TexDesc** out, TexDesc* first, TexDesc* last, TexDesc* dst,
                       const void* owner);  // 0x00f6b0e0
struct TexVector {
    TexDesc* mpBegin;
    TexDesc* mpCur;
    TexDesc* mpEnd;
    TexVector(const TexVector& o);      // 0x00f6b4b0
};
struct QuadSource {
    uint32_t _raw000[0x7c / 4];
    uint32_t m7c;                    // +0x7c
    ImgDesc  mDesc80;                // +0x80  (0x78)
    float    mf8;                    // +0xf8
    float    mfc;                    // +0xfc
    float    m100;                   // +0x100
    float    m104;                   // +0x104
    float    m108;                   // +0x108
    uint32_t m10c;                   // +0x10c
    char     mVec110[0x0c * 0x10];   // +0x110  inline array of 0x10 0xc-byte vectors
    uint32_t m1d0;                   // +0x1d0
    TexVector mTex1d4;               // +0x1d4

    QuadSource(const QuadSource& o); // 0x00f6b670
    QuadSource& CopyFrom(const QuadSource& o); // 0x00f6b670
    void Release();                  // 0x00f6b2d0
};
struct QuadNode {                   // intrusive list node; the sentinel embeds the same head
    QuadNode* mpNext;               // +0x00
    QuadNode* mpPrev;               // +0x04
    uint32_t  pad08[0x88 / 4 - 2];
    void*     mpRef88;              // +0x88  refcounted pointer (counter at +8)
    uint32_t  pad8c[(0x1dc - 0x8c) / 4];
    void*     mpRes1dc;             // +0x1dc intrusive resource pointer (counter at -4)
    void FreeAll();                 // 0x00f6b7c0  (called on the sentinel)
};
struct ImgDescRaw {
    uint32_t mHandle;            // +0x00
    uint8_t  m04, m05, m06;      // +0x04..+0x06
    char     _pad07;
    float    m08;                // +0x08
    uint32_t m0c;                // +0x0c
    float    m10, m14, m18, m1c; // +0x10..+0x1c
    uint32_t m20, m24, m28, m2c, m30, m34, m38, m3c;   // +0x20..+0x3c
    uint32_t m40, m44, m48, m4c, m50, m54;             // +0x40..+0x54
    float    m58;                                      // +0x58
    uint32_t m5c, m60, m64;                            // +0x5c..+0x64
    float    m68;                                      // +0x68
    uint32_t m6c, m70, m74;                            // +0x6c..+0x74
};
// ---- items of slice s00f6a960 end

// ---- items of slice s00f6b9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace TE {
template <class T> inline const T& Min(const T& a, const T& b) { return b < a ? b : a; }
}
namespace TE {
struct Rect_s00f6_b9a0 {
    float l, t, r, b;
    float Width() const { return r - l; }
    float Height() const { return b - t; }
};
}
namespace TE {
struct MinMax { float mn, mx; };
}
namespace TE {
struct Raster {
    uint32_t pad0[3];
    uint16_t width;            // +0x0c
    uint16_t height;           // +0x0e
    uint8_t depth;             // +0x10 (bits per pixel)
    // read back the pixels into dst (anonymous_namespace::FillSpriteTexture, thiscall ret 0xc)
    void ReadPixels(uint32_t* dst, uint32_t bytes, int offset);   // 0x011F0440
};
}
namespace TE {
struct HeightData {
    uint32_t pad0[2];
    int mSide;                 // +0x08
    int mVersion;              // +0x0c
    uint16_t* mSamples;        // +0x10  [face][side*side]
};
}
namespace TE {
struct HeightMap {
    uint32_t pad0[2];
    HeightData* mpData;        // +0x08
    char pad0c[0x50 - 0x0c];
    float mMinHeight;          // +0x50
    float mMaxHeight;          // +0x54
    void SetRange(const MinMax* r);                               // 0x00F92520 (thiscall, ret 4)
};
}
namespace TE {
struct cTerrainSphere {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual HeightMap* GetHeightMap();                            // +0x0c
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual bool IsReady();                                       // +0x30
    virtual void OnEnter();                                       // +0x34
    virtual void v14();                                           // +0x38
    virtual void Reset();                                         // +0x3c
    virtual void v17();
    virtual void Notify(int flag);                                // +0x48
    void Relevel(float a, int b);                                 // 0x00FA43E0 (thiscall, ret 8)
    void MarkFaceDirty(int face, const Rect_s00f6_b9a0* r);                  // 0x00F99AC0 (thiscall, ret 8)
};
}
namespace TE {
struct IMessageServer {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
    virtual void Post(uint32_t id, int a, int b);                 // +0x14
};
}
namespace TE {
IMessageServer* MessageServer();                                  // 0x0067DCC0
}
namespace TE {
struct U32Vector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void resize(uint32_t n);                                      // 0x004CD3C0 (thiscall, ret 4)
};
}
namespace TE {
extern void* g_gate;                                              // 0x015B0E48: self-referencing pointer
}
namespace TE {
extern const float kMinTileFraction;                              // 0x013EB8A0 constant 0.25f
}
namespace TE {
extern const float kHeightUnit;                                   // 0x0140D4F8 (1/32768)
}
namespace TE {
template <class T> inline const T& Min_s00f6_b9a0(const T& a, const T& b) { return b < a ? b : a; }
}
namespace TE {
template <class T> inline const T& Max(const T& a, const T& b) { return a < b ? b : a; }
}
namespace TE {
struct cTerrainEditor {
    char pad0[0x20];
    Raster* mHeightRaster[6];           // +0x20
    char pad38[0x74 - 0x38];
    cTerrainSphere* mpSphere;           // +0x74
    char pad78[0x80 - 0x78];
    Rect_s00f6_b9a0 mDirty[6];                     // +0x80
    Rect_s00f6_b9a0 mRectsE0[6];                   // +0xe0
    uint16_t mMinMax[6][2];             // +0x140: per face {min, max} heights
    char pad158[0x168 - 0x158];
    U32Vector mTemp;                    // +0x168

    bool ReadTile(int face, const int* rect, float a);            // 0x00F69F50 (thiscall, ret 0xc)
    bool UpdateCPUFromGPU(float elapsed);
    void ResetEditor();                                           // 0x00F6BC10
};
}
namespace TE {
static __forceinline void ClearRect(Rect_s00f6_b9a0& r) { r.l = 0.0f; r.t = 0.0f; r.r = 0.0f; r.b = 0.0f; }
}
namespace TE {
struct ListNode
{
    ListNode* mpNext;                     // +0x00
    ListNode* mpPrev;                     // +0x04
    char      mPayload[0x1f0 - 0x08];     // +0x08
};
}
namespace TE {
struct TilePayload
{
    void Construct(const void* arg);      // 0x00f6b670 (thiscall, ret 4)
};
}
namespace TE {
struct ListHead
{
    ListNode* mpHead;                     // +0x00 (sentinel next)
    ListNode* mpTail;                     // +0x04 (sentinel prev)
    void PushFront(const void* arg);      // 0x00f6bd20
};
}
namespace TE {
void* __cdecl operator_new(uint32_t size, const char* name, int a, int b,
                           const char* allocator, int line);       // 0x00f473a0
}
namespace TE {
struct GateList
{
    GateList* mpNext;                     // +0x00
    GateList* mpPrev;                     // +0x04
    void Reset();                         // 0x00f6b7c0
};
}
namespace TE {
extern GateList g_gateList;               // 0x015B0E48
}
// ---- items of slice s00f6b9a0 end

// ---- items of slice s00f4aaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct Matrix3 { float m[9]; Matrix3* Assign(const Matrix3* src); };   // 0x0041cb40
struct cTransform {                       // EA::Swarm::cTransform, 0x38
    uint16 mFlags;
    uint16 mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    void PreTransformBy(const cTransform* x);            // 0x00537f40
    cTransform& operator=(const cTransform& o);          // 0x00537dc0
};
struct FloatVector {                       // eastl::vector<float, sp_vector_allocator> 0x14
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAlloc[2];
    uint32 size() const { return (uint32)(mpEnd - mpBegin); }
};
struct cBrushVertex {                      // SP::cBrushVertex, 0x1c
    Vector3 mPosition;
    Vector2 mUV;
    float mIntensity;
    float mSize;
};
struct BrushVertexVector {                 // eastl::vector<cBrushVertex, sp_vector_allocator>
    cBrushVertex* mpBegin;                 // +0x00
    cBrushVertex* mpEnd;                   // +0x04
    cBrushVertex* mpCapacity;              // +0x08
    uint32 mAlloc[2];                      // +0x0c
    uint32 size() const;                   // 0x00f4b160
    cBrushVertex* back();                  // 0x00f4b180
};
struct cTerrainBrushDescription {          // SP::cTerrainBrushDescription (retail layout)
    uint32 mDescriptionBase[2];            // +0x00
    float  mLocation[3];                   // +0x08
    uint32 pad14;                          // +0x14
    uint32 mTexture[2];                    // +0x18
    uint8  mDrawMode;                      // +0x20
    bool   mDoGaussian;                    // +0x21
    char   pad22[2];
    float  mGaussianSlope;                 // +0x24
    float  mLifetime;                      // +0x28
    FloatVector mSizeCurve;                // +0x2c
    FloatVector mIntensityCurve;           // +0x40
    bool   mWaterLevelIsZero;              // +0x54
    char   pad55[3];
    float  mIntensityVary;                 // +0x58
    float  mSizeVary;                      // +0x5c
    float  mRotationVary;                  // +0x60
    float  mTextureOffset[2];              // +0x64
    float  mLevelValue;                    // +0x6c
    float  mLevelVary;                     // +0x70
    float  mLevelRangeValue1;              // +0x74
    float  mLevelRangeValue2;              // +0x78
    float  mImprintsPerSecond;             // +0x7c
    bool   mDoFiltering;                   // +0x80
    bool   mFilterGlobal;                  // +0x81
    uint8  mKernelType;                    // +0x82
    uint8  mKernelOp;                      // +0x83
    float  mDeltaAmount;                   // +0x84
    FloatVector mSpacingCurve;             // +0x88
    float  mSpacingVary;                   // +0x9c
    uint8  mCondOp;                        // +0xa0
    char   padA1[3];
    float  mCondN1;                        // +0xa4
    float  mCondN2;                        // +0xa8
    uint8  mFallOffOp;                     // +0xac
    char   padAd[3];
    float  mFallOffN1;                     // +0xb0
    float  mFallOffN2;                     // +0xb4
    uint8  mGradientCondOp;                // +0xb8
    char   padB9[3];
    float  mGradientCondN1;                // +0xbc
    float  mGradientCondN2;                // +0xc0
    uint8  mGradientFallOffOp;             // +0xc4
    char   padC5[3];
    float  mGradientFallOffN1;             // +0xc8
    float  mGradientFallOffN2;             // +0xcc
    bool   mDoCubeMap;                     // +0xd0
    char   padD1[3];
    Vector3 mRot;                          // +0xd4
    Vector3 mRotVary;                      // +0xe0
    bool   mRibbonBrush;                   // +0xec
    char   padEd[0x108 - 0xed];            // tail (ribbon params)

    cTerrainBrushDescription();                                  // 0x00f49040
    cTerrainBrushDescription& operator=(const cTerrainBrushDescription&);  // 0x00f4a5d0
    ~cTerrainBrushDescription();                                 // 0x00f48b00
    cTerrainBrushDescription* Construct(const cTerrainBrushDescription& src);  // 0x00f4a810
};
struct cComponentStats;
struct cDecalFront {                       // brush/level descriptor
    uint8  mUseNoise;                      // +0x00  (no texture, or gaussian draw)
    uint8  mFilterGlobal;                  // +0x01
    uint8  mDoCubeMap;                     // +0x02
    uint8  pad03;
    float  mGaussianSlope;                 // +0x04
    uint32 mDrawMode;                      // +0x08
    float  mLevel;                         // +0x0c
    float  mLevelRange1;                   // +0x10
    float  mLevelRange2;                   // +0x14
    float  mRotationVary;                  // +0x18
};
struct cDecalBoxParams {                   // filter / gradient descriptor
    uint8  mDoFiltering;                   // +0x00
    uint8  mRibbonKernel;                  // +0x01  (mKernelType == 0x12)
    char   pad02[2];
    uint32 mKernel[17];                    // +0x04  kernel weights (0x44 bytes)
    uint32 mGradientCondOp;                // +0x48
    float  mGradientCondN1;                // +0x4c
    float  mGradientCondN2;                // +0x50
    uint32 mGradientFallOffOp;             // +0x54
    float  mGradientFallOffN1;             // +0x58
    float  mGradientFallOffN2;             // +0x5c
};
struct cTerrainEditor_s00f4_aaf0 {
    float GetWaterLevel();                                // 0x00f678d0
    float GetHeightAt(Vector3 p);                         // 0x00f67aa0
    void  BuildDecalBox(int a2, int a3, int a4, void** outRef,
                        const cDecalFront* front, const cDecalBoxParams* params,
                        int zero, float offset, float rotVary, int zero2, int one);
    // 0x00f6c940
};
cTerrainEditor_s00f4_aaf0* TerrainEditor();                          // 0x00f48a70
class cTerrainBrushEffect {
public:
    virtual void Initialize(void*, void*, void*);
    virtual void Dispose();
    virtual void Start(int hardStart);
    virtual int  Stop(int hardStop);
    virtual int  IsRunning();
    virtual void ApplyEffect(float dt, float, cComponentStats*);

    void ApplyGlobal(float intensity, const Matrix3& kernel);   // 0x00f4bcb0
    bool SetParam(int id, float* value, int);                   // 0x00f4b110
    void Imprint(const Vector3& pos, int, int, int, const void* kernel);  // 0x00f4b870
    void SetTransform(void* a, const cTransform* t);            // 0x00f4b6e0

    int mRefCount;                           // +0x04
    int mRefCountPad;                        // +0x08
    cTerrainBrushDescription* mDesc;         // +0x0c
    bool mActive;                            // +0x10
    cTransform mTransform;                   // +0x14
    float mSize;                             // +0x4c
    cTransform mPreviousTransform;           // +0x50
    float mPreviousSize;                     // +0x88
    bool mPreviousValuesInitialized;         // +0x8c
    float mAccumulatedTime;                  // +0x90
    float mLODSizeScale;                     // +0x94
    float mIntensityScale;                   // +0x98
    float mOverallTime;                      // +0x9c
    float mInvLifetime;                      // +0xa0
    float mLifeTime;                         // +0xa4
    bool mDoSpacing;                         // +0xa8
    bool mDoSpacingVary;                     // +0xa9
    float mSpacingVaryVal;                   // +0xac
    float mDistTraveled;                     // +0xb0
    float mUserLevelParm;                    // +0xb4
    float mUserSizeParm;                     // +0xb8
    float mLevelValue;                       // +0xbc
    void* mpTexture;                         // +0xc0
    BrushVertexVector mRibbonBrushList;      // +0xc4
};
float RandomRange(float a, float b);                 // 0x007d45d0
struct BrushBigElem { uint32 v[0x71]; };
struct BrushHugeElem { uint32 v[0x71]; };
// ---- items of slice s00f4aaf0 end

// ---- items of slice s00f4baa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __stdcall VectorCopyCtorIterator(void* dst, const void* src, int elemSize,
                                                 int count, void* ctor);   // 0x00406540
extern "C" void BrushVertexCopyCtor(void* dst, const void* src);           // 0x00705c00
extern const char gSimulatorName[];   // 0x013f09b4
extern const char gAllocatorPath[];   // 0x013ebb38
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
struct cSPVector3_s00f4_baa0 {                   // 0x0c
    float x, y, z;
};
struct cSPVector2_s00f4_baa0 {                   // 0x08
    float x, y;
};
namespace SP {
struct cBrushVertex_s00f4_baa0 {                 // 0x1c
    cSPVector3_s00f4_baa0 mPosition;             // +0x00
    cSPVector2_s00f4_baa0 mUV;                   // +0x0c
    float      mIntensity;            // +0x14
    float      mSize;                 // +0x18

    cBrushVertex_s00f4_baa0() {}
    cBrushVertex_s00f4_baa0(const cBrushVertex_s00f4_baa0& o) {
        mPosition.x = o.mPosition.x;
        mPosition.y = o.mPosition.y;
        mPosition.z = o.mPosition.z;
        mUV.x = o.mUV.x;
        mUV.y = o.mUV.y;
        mIntensity = o.mIntensity;
        mSize = o.mSize;
    }
};
}
namespace SP {
struct cRibbonBrushPoly {             // 0x1c4
    int          mNumVertices;        // +0x000
    cBrushVertex_s00f4_baa0 mVertices[16];       // +0x004

    cRibbonBrushPoly() {}
    cRibbonBrushPoly(const cRibbonBrushPoly& o) {
        mNumVertices = o.mNumVertices;
        VectorCopyCtorIterator(mVertices, o.mVertices, sizeof(cBrushVertex_s00f4_baa0), 16,
                               (void*)BrushVertexCopyCtor);
    }
};
}
void* EAAllocate(size_t size, const char* name, unsigned a, unsigned b, const char* file,
                 int line);           // 0x00f473a0
void  operator delete[](void* p);     // 0x00f47380
namespace eastl {
struct sp_vector_allocator_s00f4_baa0 {
    int mFlags;
    int mUnused;

    bool operator==(const sp_vector_allocator_s00f4_baa0&) const { return true; }
    void deallocate(void* p, size_t) {
        if (p != 0 && ((int*)p)[-1] != 0)
            ::operator delete[](p);
    }
};
}
namespace eastl {
template <class T, class Allocator> class vector_s00f4_baa0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    void push_back();
    void erase(T* first, T* last);    // 0x00d73090
};
}
typedef eastl::vector_s00f4_baa0<SP::cRibbonBrushPoly, eastl::sp_vector_allocator_s00f4_baa0> RibbonPolyVector;
SP::cRibbonBrushPoly* CopyPolysBackward(SP::cRibbonBrushPoly* first, SP::cRibbonBrushPoly* last, SP::cRibbonBrushPoly* dest); // 0x00f4b190
SP::cRibbonBrushPoly* CopyPolysForward(SP::cRibbonBrushPoly* first, SP::cRibbonBrushPoly* last, SP::cRibbonBrushPoly* dest);  // 0x00f4b4c0
inline void* operator new(size_t, void* p) { return p; }
// ---- items of slice s00f4baa0 end

// ---- items of slice s00f4c300 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3Tmp;  // value returned by the out-of-line Vector3 operators
struct Vector3_s00f4_c300 {
    float x, y, z;
    Vector3_s00f4_c300();                       // 0x00572590 (empty ctor, returns this)
    Vector3_s00f4_c300(const Vector3_s00f4_c300& o);       // 0x004098a0
    Vector3_s00f4_c300(const Vec3Tmp& o);       // 0x004098a0 (same body)
    float& operator[](int i);        // 0x00572580
};
struct Vec3Tmp { float x, y, z; Vec3Tmp(); };
struct Vector2_s00f4_c300 {
    float x, y;
    Vector2_s00f4_c300(float x_, float y_);     // 0x00508780
};
struct Quaternion {
    float x, y, z, w;
    Quaternion();                                    // 0x00572590
    Quaternion(float x_, float y_, float z_, float w_);  // 0x00628970
};
struct Matrix3_s00f4_c300 {
    float m[9];
    Matrix3_s00f4_c300();                                   // 0x00572590
    Matrix3_s00f4_c300& operator=(const Matrix3_s00f4_c300& o);        // 0x005a88a0
};
struct cTransform_s00f4_c300 {                  // EA::Swarm::cTransform, 0x38
    uint16 mFlags;
    uint16 mModificationCount;
    Vector3_s00f4_c300 mTranslation;
    float mScale;
    Matrix3_s00f4_c300 mRotation;
    const Vector3_s00f4_c300& GetOffset() const;            // 0x006e64f0
    const Matrix3_s00f4_c300& GetRotation() const;          // 0x009892e0
    cTransform_s00f4_c300& operator=(const cTransform_s00f4_c300& o);  // 0x00537dc0
};
float VectorLength(const Vector3_s00f4_c300& v);                                   // 0x0040ae50
float Dot3(const Vector3_s00f4_c300& v);                                           // 0x004885d0
Vector3_s00f4_c300 normalized_safe(const Vector3_s00f4_c300& v);                              // 0x00449c20
Vector3_s00f4_c300 Normalize(const Vector3_s00f4_c300& v);                                    // 0x00436ce0
Vec3Tmp operator-(const Vector3_s00f4_c300& a, const Vector3_s00f4_c300& b);                  // 0x0041db10
Vec3Tmp RotateVector(const Vector3_s00f4_c300& v, const Quaternion& q);            // 0x0059aed0
Quaternion MatrixToQuaternion(const Matrix3_s00f4_c300& m);                        // 0x0046d660
Quaternion QuaternionFromDirections(const Vector3_s00f4_c300& from, const Vector3_s00f4_c300& to);  // 0x00698180
Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);    // 0x005b26f0
extern const Quaternion kQuaternionIdentity;                            // 0x015b0a48
const float& Min(const float& a, const float& b);   // 0x0059c010
float Clamp01(float v);                             // 0x005a6e00
float Clamp(float v, float lo, float hi);           // 0x0059ab50
float Abs(float v);                                 // 0x00571ce0
int   FloatToInt(float v);                          // 0x00684be0 (truncate)
int   RoundToInt(float v);                          // 0x005e4d30 (cvtss2si)
struct RandomLinearCongruential {
    double RandomDoubleUniform();                   // 0x009360d0
};
RandomLinearCongruential* GetRandom();              // 0x007dad70
struct cTerrainEditor_s00f4_c300 {
    float GetWaterLevel();                          // 0x00f678d0
};
cTerrainEditor_s00f4_c300* TerrainEditor_s00f4_c300();                    // 0x00f48a70
struct FloatVector_s00f4_c300 {                 // eastl::vector<float, sp_vector_allocator> (retail 0x14)
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAllocator[2];
    uint32 size() const;                            // 0x00572c90
    const float& front() const;                     // 0x00fc8380
    const float& operator[](uint32 n) const { return mpBegin[n]; }
};
struct cBrushVertex_s00f4_c300 {                // SP::cBrushVertex, 0x1c
    Vector3_s00f4_c300 mPosition;
    Vector2_s00f4_c300 mUV;
    float mIntensity;
    float mSize;
};
struct BrushVertexVector_s00f4_c300 {           // eastl::vector<cBrushVertex, sp_vector_allocator>
    cBrushVertex_s00f4_c300* mpBegin;
    cBrushVertex_s00f4_c300* mpEnd;
    cBrushVertex_s00f4_c300* mpCapacity;
    uint32 mAllocator[2];
    uint32 size() const;                            // 0x00f4b160
    cBrushVertex_s00f4_c300& back();                           // 0x00f4b180
    void push_back();                               // 0x00f4c150
};
struct cMapKernel {                  // SP::cMapKernel, 0x44
    float mArray[9];
    float mNormalizer;
    uint32 mOp;
    uint32 mCondOp;
    float mCondN1;
    float mCondN2;
    uint32 mFallOffOp;
    float mFallOffN1;
    float mFallOffN2;
};
extern const cMapKernel kKernelSmooth;      // 0x0148e2f8
extern const cMapKernel kKernelMedian;      // 0x0148e340
extern const cMapKernel kKernelLowPass1;    // 0x0148e388
extern const cMapKernel kKernelLowPass2;    // 0x0148e3d0
extern const cMapKernel kKernelLowPass3;    // 0x0148e418
extern const cMapKernel kKernelLowPass4;    // 0x0148e460
extern const cMapKernel kKernelLowPass5;    // 0x0148e4a8
extern const cMapKernel kKernelHighPass1;   // 0x0148e4f0
extern const cMapKernel kKernelHighPass2;   // 0x0148e538
extern const cMapKernel kKernelHighPass3;   // 0x0148e588
extern const cMapKernel kKernelHighPass4;   // 0x0148e5d8
extern const cMapKernel kKernelEdge1;       // 0x0148e620
extern const cMapKernel kKernelEdge2;       // 0x0148e668
extern const cMapKernel kKernelEdge3;       // 0x0148e6b0
extern const cMapKernel kKernelAdd;         // 0x0148e268
extern const cMapKernel kKernelLevel;       // 0x0148e2b0
struct cTerrainBrushDescription_s00f4_c300 {    // SP::cTerrainBrushDescription (retail layout)
    uint32 mDescriptionBase[2];      // +0x00 EA::Swarm::cDescription
    float mLocation[3];              // +0x08
    uint32 pad14;                    // +0x14
    uint32 mTexture[2];              // +0x18
    uint8 mDrawMode;                 // +0x20
    bool mDoGaussian;                // +0x21
    float mGaussianSlope;            // +0x24
    float mLifetime;                 // +0x28
    FloatVector_s00f4_c300 mSizeCurve;          // +0x2c
    FloatVector_s00f4_c300 mIntensityCurve;     // +0x40
    bool mWaterLevelIsZero;          // +0x54
    float mIntensityVary;            // +0x58
    float mSizeVary;                 // +0x5c
    float mRotationVary;             // +0x60
    float mTextureOffset[2];         // +0x64
    float mLevelValue;               // +0x6c
    float mLevelVary;                // +0x70
    float mLevelRangeValue1;         // +0x74
    float mLevelRangeValue2;         // +0x78
    float mImprintsPerSecond;        // +0x7c
    bool mDoFiltering;               // +0x80
    bool mFilterGlobal;              // +0x81
    uint8 mKernelType;               // +0x82
    uint8 mKernelOp;                 // +0x83
    float mDeltaAmount;              // +0x84
    FloatVector_s00f4_c300 mSpacingCurve;       // +0x88
    float mSpacingVary;              // +0x9c
    uint8 mCondOp;                   // +0xa0
    float mCondN1;                   // +0xa4
    float mCondN2;                   // +0xa8
    uint8 mFallOffOp;                // +0xac
    float mFallOffN1;                // +0xb0
    float mFallOffN2;                // +0xb4
    uint8 mGradientCondOp;           // +0xb8
    float mGradientCondN1;           // +0xbc
    float mGradientCondN2;           // +0xc0
    uint8 mGradientFallOffOp;        // +0xc4
    float mGradientFallOffN1;        // +0xc8
    float mGradientFallOffN2;        // +0xcc
    bool mDoCubeMap;                 // +0xd0
    Vector3_s00f4_c300 mRot;                    // +0xd4
    Vector3_s00f4_c300 mRotVary;                // +0xe0
    bool mRibbonBrush;               // +0xec
};
class cTerrainBrushEffect_s00f4_c300 {          // SP::cTerrainBrushEffect : EA::Swarm::cComponentBase
public:
    virtual void Initialize(void*, void*, void*);  // 0x00f4b420 (cTerrainBrushEffect::Initialize)
    virtual void Dispose();
    virtual void Start(int hardStart);
    virtual int  Stop(int hardStop);                // +0x0c
    virtual int  IsRunning();
    virtual void ApplyEffect(float dt, float, cComponentStats*);  // +0x14

    void ApplyGlobal(float intensity, const cMapKernel& kernel);  // 0x00f4bcb0
    void Imprint(const Vector3_s00f4_c300& pos, const Quaternion& rot, float size, float intensity,
                 const cMapKernel& kernel);                       // 0x00f4b870

    int mRefCount;                           // +0x04
    int mRefCountPad;                        // +0x08
    cTerrainBrushDescription_s00f4_c300* mDesc;         // +0x0c
    bool mActive;                            // +0x10
    cTransform_s00f4_c300 mTransform;                   // +0x14
    float mSize;                             // +0x4c
    cTransform_s00f4_c300 mPreviousTransform;           // +0x50
    float mPreviousSize;                     // +0x88
    bool mPreviousValuesInitialized;         // +0x8c
    float mAccumulatedTime;                  // +0x90
    float mLODSizeScale;                     // +0x94
    float mIntensityScale;                   // +0x98
    float mOverallTime;                      // +0x9c
    float mInvLifetime;                      // +0xa0
    float mLifeTime;                         // +0xa4
    bool mDoSpacing;                         // +0xa8
    bool mDoSpacingVary;                     // +0xa9
    float mSpacingVaryVal;                   // +0xac
    float mDistTraveled;                     // +0xb0
    float mUserLevelParm;                    // +0xb4
    float mUserSizeParm;                     // +0xb8
    float mLevelValue;                       // +0xbc
    void* mpTexture;                         // +0xc0
    BrushVertexVector_s00f4_c300 mRibbonBrushList;      // +0xc4
};
template <int N> inline void ScratchSlots() { uint32 s[N]; }   // frame of a declined inline callee
__forceinline float CurveValue(const FloatVector_s00f4_c300& curve, float t)
{
    uint32 n = curve.size() - 1;
    if (n == 0)
        return curve[0];
    t *= n;
    int index = FloatToInt(t);
    t -= index;
    if (t > 0.0f) {
        const float& lo2 = curve[index];
        const float& hi = curve[index + 1];
        return (hi - curve[index]) * t + lo2;
    } else
        return curve[index];
}
__forceinline bool IsClose(const Vector3_s00f4_c300& a, const Vector3_s00f4_c300& b)
{
    return Abs(a.x - b.x) < 0.001 && Abs(a.y - b.y) < 0.001 && Abs(a.z - b.z) < 0.001;
}
// ---- items of slice s00f4c300 end

// ---- items of slice s00f66050 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_meshRefCount;                          // 0x016C96A0
void __cdecl FreeArrayMemory(void* p);                    // 0x00F47410
namespace SP {
struct cFormatInfo {
    uint8_t  mPad00[0xf];                    // +0x00
    uint8_t  mIndexStride;                   // +0x0f
};
}
namespace SP {
class cMeshBuffer {                          // 0x10 (vertex/index buffer interface)
public:
    void* Lock(unsigned int type, unsigned int first, unsigned int count);  // 0x011F3620
    cFormatInfo* mpFormat;                   // +0x00
    uint32_t mPad04;                         // +0x04
    int mBaseIndex;                          // +0x08
    int mCapacity;                           // +0x0c
};
}
namespace SP {
class cIndexBuffer {
public:
    unsigned int Lock(unsigned int type, void** ppData);     // 0x011F4F20
    void* Unlock(void** ppData);                             // 0x011F4FD0
};
}
namespace SP {
class cDistCellMesh {                        // 0x34
public:
    void Init(const void* desc, int indexCount, int numCells);
    ~cDistCellMesh();
    bool LockItems(int* pOut, void* unused, int count, int param);

    uint32_t mPad00;                         // +0x00
    void*    mTexture;                       // +0x04
    cMeshBuffer* mBuffer;                    // +0x08
    void*    mDynamicBuffer;                 // +0x0c
    void*    mMesh;                          // +0x10
    int      mIndexCount;                    // +0x14 (capacity in entries)
    int      mBaseOffset;                    // +0x18 (next free entry)
    int      mNumCells;                      // +0x1c
    uint32_t mPad20;                         // +0x20
    int      mItemCount;                     // +0x24
    uint32_t mPad28;                         // +0x28
    int      mParam;                         // +0x2c
    int      mFlag;                          // +0x30
};
}
struct cRenderDevice { uint32_t mPad00; };
extern cRenderDevice g_renderDevice;                  // 0x015D07B0
extern SP::cIndexBuffer* g_indexBufferLarge_s00f6_6050;              // 0x016C9698
extern SP::cIndexBuffer* g_indexBufferSmall_s00f6_6050;              // 0x016C969C
void* __cdecl CreateRenderBuffer(cRenderDevice* device, int width, int height, int format,
                                 int usage, int flags);          // 0x00762C60
void* __cdecl CreateMeshBuffers(void* texture, int count, int a, int b);  // 0x00762B70
void  __cdecl ReleaseRenderBuffer(void* buffer);                 // 0x00762A30
void  __cdecl ReleaseMeshBuffer(void* buffer);                   // 0x00762A00
void* __cdecl LoadTexture(const void* desc);                     // 0x007C3AF0
void* __cdecl SP_CreateMesh(int a);                              // 0x00761840
// ---- items of slice s00f66050 end

// ---- items of slice s00f66f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_one_1485720;              // 0x01485720 = 1.0f
extern float g_half_1471064;             // 0x01471064 = 0.5f
extern float g_c_13eb1bc;                // 0x013eb1bc = -1.0f
extern float g_c_1470f1c;                // 0x01470f1c = 2.0f
extern float g_c_148f69c;                // 0x0148f69c = 1.0039062f (0x3f808081)
extern float g_c_148f6a0;                // 0x0148f6a0 = 1.5259022e-05f
extern float g_c_148f6a4;                // 0x0148f6a4
extern float g_c_148f6a8;                // 0x0148f6a8
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                     // 0x00f47380
void* __cdecl TerrainManager();                                                             // 0x0067dda0
void  __cdecl RWFillSpriteTexture(void* dst, unsigned a, int b);                                  // 0x011f0440
struct TerrainDraw {
    void**  mpVtbl;      // +0x00
    void*   mpVb;        // +0x04
    void*   mpIb;        // +0x08
    void*   mpIb2;       // +0x0c
    void*   mpShader;    // +0x10
    int32_t mStart0;     // +0x14
    int32_t mCount0;     // +0x18
    int32_t mStart1;     // +0x1c
    int32_t mCount1;     // +0x20
    int32_t mBase0;      // +0x24
    int32_t mBase1;      // +0x28
    void*   mpParam;     // +0x2c
    int32_t mLockState;  // +0x30

    char BuildIndexed(unsigned* pa, void* unused, int vertCount, int* pd, int indexCount, void* param);  // 0x00f66f80
    int  Draw(void* compiledState, void* out);                                              // 0x00f67070
    void Advance();                                                                         // 0x00f67290
    void Init(void* a, void* b, void* c);                                                   // 0x00f66d20
    void Deinit();                                                                          // 0x00f66e70
};
struct TexFactory {
    void** mpVtbl;
};
struct TempExtract {
    void*   hA_handle;   // +0x00
    int32_t hA_id;       // +0x04
    void*   hB_handle;   // +0x08
    int32_t hB_id;       // +0x0c
    int32_t hA_tex;      // +0x10
    int32_t hB_tex;      // +0x14
    void*   buf0;        // +0x18
    void*   buf1;        // +0x1c

    char Build(int size);   // 0x00f67360
    void Destroy();         // 0x00f674c0
};
void* __cdecl ShaderGet(unsigned a, unsigned b, unsigned c);        // 0x00777ae0
void* __cdecl TerrainEditorGet();                                   // 0x00f48a60
struct RasterState {
    unsigned mData[4];              // +0x00 .. +0x0f
    void Construct(void* a, void* b, void* c);   // 0x00fc2c10
    void Clear();                                // 0x00fc2830
};
struct Viewer_s00f6_6f80 {
    int  SetRaster(void* raster, bool b);        // 0x007c4be0
    char Update();                               // 0x007c4fd0
    void EndDraw();                              // 0x007c3c10
    void SetClearColor(const void* c);           // 0x007c3c20
    void Clear(unsigned flags);                  // 0x007c3c50
};
struct DepthCtx { float Read(); };                                  // 0x00fd9400
void  __cdecl FUN_00fa3b30(void* self);                             // 0x00fa3b30
int*  __cdecl SP_CoordToIndex(int* out, int n, float* v);           // 0x00684bf0
struct Vec4_s00f6_6f80 { float x, y, z, w; };
struct TerrainFace {
    char raw[0x300];
    void SetDepth(float d);        // 0x00f67540
    void ClearDepth();             // 0x00f67560
    void SetLodByte(int slot, unsigned char v);  // 0x00f67580
    void Draw(int slot, void* a3); // 0x00f67810
    float GetDepth();              // 0x00f678d0
    void MergeRectA(int slot, float* r);  // 0x00f67900
    void MergeRectB(int slot, float* r);  // 0x00f679b0
    float ProjectDir(float dx, float dy, float dz);  // 0x00f67aa0
    void ClearSprites();           // 0x00f67da0
};
// ---- items of slice s00f66f80 end

// ---- items of slice s00f67e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);        // 0x011e073e
extern "C" void  __cdecl VecInsert(void* self, const void* data, int n);    // 0x011e0744
extern const float C_1485720;   // 0x01485720   (= 1.0f)
extern const float C_13eb1bc;   // 0x013eb1bc   (= -1.0f)
extern const float C_148f6cc;   // 0x0148f6cc   (= 0.001953125f)
extern const float C_1470f1c;   // 0x01470f1c   (= 2.0f)
extern const float C_1471064;   // 0x01471064   (= 0.5f)
#undef DUMMY_V
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct Vec3_s00f6_7e70 { float x, y, z; Vec3_s00f6_7e70() {} Vec3_s00f6_7e70(float a, float b, float c) : x(a), y(b), z(c) {} };
namespace SP {
class cViewer_s00f6_7e70 { public:
    cViewer_s00f6_7e70* FUN_007c3f70();                                  // 0x007c3f70
    bool     Init(bool flag);                                 // 0x007c4dd0
    void     SetA(float v);                                   // 0x007c4ba0
    void     SetB(float v);                                   // 0x007c4bc0
    void     ViewportRectArgs(int x, int y, int w, int h);    // 0x007c5310
    void     SetC(float a, float b);                          // 0x007c4b00
    void     SetRasterDirect(void* r);                        // 0x007c3cb0
    void     Clear(u32 flags);                                // 0x007c3cc0
    void     SetRaster(const void* r, bool flag);             // 0x007c4be0
    bool     Update();                                        // 0x007c4fd0
    void     Finish();                                        // 0x007c3c10
};  // namespace SP
}
struct Raster_s00f6_7e70 { u32 pad[3]; u16 width; u16 height; u8 depth; u8 pad2[3]; };
struct RasterDesc { u32 v0, v1; };
#define DUMMY_V(n) virtual void v##n();
struct IResolver_s00f6_7e70 {
    DUMMY_V(0)  DUMMY_V(1)  DUMMY_V(2)  DUMMY_V(3)  DUMMY_V(4)  DUMMY_V(5)
    DUMMY_V(6)  DUMMY_V(7)  DUMMY_V(8)  DUMMY_V(9)  DUMMY_V(10) DUMMY_V(11) DUMMY_V(12)
    virtual void Resolve(void* handle);                       // +0x34 (slot 13)
};
IResolver_s00f6_7e70* __cdecl FUN_0067dd60();                            // 0x0067dd60
struct ShaderIds_s00f6_7e70 { u32 pad; u32 id; };
struct ShaderTable_s00f6_7e70 {
    char       pad00[0x0c];
    ShaderIds_s00f6_7e70* table[0x10];                                   // +0x0c (indexed by id)
    ShaderIds_s00f6_7e70* s4c;                                           // +0x4c
};
ShaderTable_s00f6_7e70* __cdecl GetShaderTable_s00f6_7e70();                        // 0x00f48a60
struct IBatch_s00f6_7e70 {
    virtual void v0();
    virtual bool BigAlloc(void** out, int stride, int count, const int* desc, int verts, int one); // +0x04
    virtual bool Alloc(void** out, int stride, int count, int zero);                               // +0x08
    virtual bool Apply(u32 shader, void* arg);                                                     // +0x0c
    virtual void Flush();                                                                          // +0x10
};
struct Binding_s00f6_7e70 {
    u32 w[4];
    void Init(u32 shader, int index, u32 value);              // 0x00fc2c10
    void Done();                                              // 0x00fc2830
};
struct FaceVertex { float f0, y, z, f0c, f10, f14, f18; };   // 0x1c
struct FaceOrIdx { int count; int* data; };                  // the original keeps a raw union here
struct Face { int count; FaceVertex v[16]; };                // 0x1c4
struct FaceVec { Face* mpBegin; Face* mpEnd; };
void __cdecl FUN_00777ae0(int slot, const void* data, int zero);            // 0x00777ae0
int  __stdcall FUN_00f67770(u32 a, int* b);                                 // 0x00f67770
extern const u8    T_148f608[]; // 0x0148f608 texture-axis table
namespace SP {
u32 __cdecl ColorRGBToU32(const float* rgb);                  // 0x00458a40
}
namespace SP {
class cTerrainEditor_s00f6_7e70 { public:
    char       pad0[0x1c];
    cViewer_s00f6_7e70*   mViewer;        // +0x1c
    Raster_s00f6_7e70*    mRaster0;       // +0x20
    char       pad24[0x38 - 0x24];
    RasterDesc mRasterDesc[6]; // +0x38: six 8-byte raster descriptors
    u32        mHandle68;      // +0x68
    char       pad6c[0x80 - 0x6c];
    float      mDirty[24];     // +0x80
    char       padE0[0x164 - 0xe0];
    float      mF164;          // +0x164
    char       pad168[0x1d0 - 0x168];
    float      mRange[4];      // +0x1d0
    float      mMat[8];        // +0x1e0
    IBatch_s00f6_7e70*    mBatch;         // +0x200
    IBatch_s00f6_7e70*    mBatch2;        // +0x204

    void Refresh();                                                 // 0x00f67da0
    void B0(u32 a, u32 b, float* out);                              // 0x00f675b0
    void Init();                                                    // 0x00f67e70
    void Enable(int unused);                                        // 0x00f67ff0
    bool BuildBrush(FaceVec* faces, u32 flipIdx, u32 a3, u32 a4);   // 0x00f68070
    void UpdateRange(int* p);                                       // 0x00f684c0
    bool DrawUnitQuad(int idx, u32 a, u32 b);                       // 0x00f68650
    static void __stdcall TessellateBrush(void* out, void* vec, const float* in, int count,
                                          int strips, int limit, int unused); // 0x00f687f0
    void DrawRaster(int idx, u32 a, int* handle, u32 b);            // 0x00f68c80
};
}
// ---- items of slice s00f67e70 end

// ---- items of slice s00f69a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float C_148f63c;    // 0x0148f63c  = 0.017453292f
extern float       g_16c9824[11];
extern float       g_16c990c;
extern float       g_16c9910;
extern float       g_16c9914;
extern void*       g_015b0e40;   // 0x015b0e40
#pragma intrinsic(_InterlockedExchangeAdd)
#undef V
struct Vec2 { float x, y; Vec2() {} Vec2(float a, float b) : x(a), y(b) {} };
extern const u8    T_148f624[];  // 0x0148f624  ping id table (6 dwords)
extern const u32   D_148f614;    // 0x0148f614  AutoHandler id array
extern u8          g_16c998c[];  // 0x016c998c
extern u8          g_16c9858[];  // 0x016c9858
extern u32         g_16c9898;
void* __cdecl FUN_00f672f0(const char* fmt, int a, int b);                      // 0x00f672f0
void* __cdecl FUN_0067dda0();                                                   // 0x0067dda0
void* __cdecl FUN_0067dd60_s00f6_9a30();                                                   // 0x0067dd60
void* __cdecl FUN_0067dcc0();                                                   // 0x0067dcc0
void* __cdecl FUN_0067de30();                                                   // 0x0067de30
void* __cdecl FUN_0067dd10();                                                   // 0x0067dd10
void* __cdecl GetShaderTable_s00f6_9a30();                                                 // 0x00f48a60
void  __cdecl FUN_00f959f0(void* table, int a);                                 // 0x00f959f0
void  __cdecl RemoveHandler(void* h, u32 a, u32 b, u32 c, u32 d);               // 0x00571db0
typedef void (__thiscall *tfn1)(void*, void*);
typedef void (__thiscall *tfnf)(void*, float);
void  Matrix3_Assign();                                                         // 0x0041cb40
void  cXform_PreRotateX();                                                      // 0x005a2d90
void  cXform_RotateY();                                                         // 0x006b9050
void  cTransform_PreRotateY();                                                  // 0x004099b0
void  Basis3_Build();                                                           // 0x006b9440
void  __cdecl FUN_011e0744(void* self, const void* data, int n);                // 0x011e0744
void* __cdecl FUN_011e073e(void* dst, int val, u32 n);                          // 0x011e073e memset
void* __cdecl FUN_011f0440();                                                   // 0x011f0440 thiscall sprite upload
int   __cdecl FUN_00fc2c10();                                                   // 0x00fc2c10 RasterState::Construct
int   __cdecl FUN_00fc2830();                                                   // 0x00fc2830 RasterState::Clear
int   __cdecl FUN_007c4be0();                                                   // 0x007c4be0 cViewer::SetRaster
int   __cdecl FUN_007c4fd0();                                                   // 0x007c4fd0 cViewer::Update
int   __cdecl FUN_007c3c10();                                                   // 0x007c3c10 cViewer method
#define V(n) virtual void v##n();
struct IVP {
    V(0) V(1) V(2) V(3)
    virtual void* CreateRasterID(void* out, int w, int h, int fmt, int a, u32 id, int b); // +0x10
    V(5)
    virtual void* GetRaster(u32 pageID, u32 allocID);                        // +0x18
    V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
    virtual void  Remap(u32 pageID, u32 allocID, const char* name);          // +0x48
};
struct IResolver_s00f6_9a30 {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12)
    virtual void  Prepare(void* res);                                       // +0x34 (slot 13)
    V(14)
    virtual void* CreateTexture(u32 id, void* r, int w, int h, int a, int b, int c, int d); // +0x3c
};
struct IBatch_s00f6_9a30 {
    V(0)
    virtual bool BigAlloc(void** out, int stride, int count, const int* desc, int verts, int one); // +0x04
    virtual bool Alloc(void** out, int stride, int count, int zero);         // +0x08
    virtual bool Apply(u32 shader, float time);                              // +0x0c
    virtual void Flush();                                                    // +0x10
};
struct IPropertyManager {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10)
    virtual void Register(u32 a, u32 b, void** pp);              // +0x2c
};
struct IServer {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
    virtual void Register(void* handler, u32 id);                // +0x24
};
struct ITerrainSphere {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
    V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25)
    V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37)
    V(38)
    virtual void SetProp(void* s, int zero);     // +0x9c (slot 39)
};
struct RectT { float l, t, r, b; };
struct RectId { u32 pageID; u32 allocID; };
struct RasterLike { u32 pad0[3]; u16 width; u16 height; u8 depth; u8 pad2[3]; };
struct TempExtractTex { void* raster; u32 flags; u32 refcount; };
struct LockableRaster {
    int  Lock(int a, int b, void* state);    // 0x011ef750
    void Unlock(void* state);                // 0x011ef880
};
struct RasterStateStub { u32 d[4]; };
struct cTerrainEditor_s00f6_9a30 {
    char       pad0[0x08];            // +0x00 vfptr(s)
    void*      mpServer;              // +0x08
    void*      mpHandler;             // +0x0c
    void*      mpIdArray;             // +0x10
    u32        mnIdArrayCount;        // +0x14
    u32        mnPriority;            // +0x18
    void*      mRTTCamera;            // +0x1c
    RasterLike* mHeightRasterArray[6];// +0x20
    RectId     mHeightRectIDArray[6]; // +0x38
    RasterLike* mHeightRTPingRaster;  // +0x68
    RectId     mHeightRTPingRectID;   // +0x6c
    void*      mTextureType;          // +0x74
    u8         mGPUDirtyFace[6];      // +0x78
    char       pad7e[2];
    RectT      mCPUDirtyRect[6];      // +0x80
    RectT      mBrushDirtyRect[6];    // +0xe0
    char       pad140[0x158 - 0x140];
    u8         mTempBuffer0;          // +0x158
    u8         pad159[3];
    float      mTempBufferF;          // +0x15c
    char       pad160[4];
    float      mMaxTimePerRenderJob;  // +0x164
    void*      mUploadHeightMapTexture; // +0x168
    RectId     mTempExtractRectID[2]; // +0x16c
    RasterLike* mTempExtractTexture;  // +0x17c
    Vec2       mTileVec[2];           // +0x180
    void*      mUploadRaster[2];      // +0x190
    RasterLike* mTileRaster[2];       // +0x198
    int        mTileIndex;            // +0x1a0
    char       pad1a4[0x1c8 - 0x1a4];
    void*      mpSphere;              // +0x1c8 (AutoRefCount target)
    char       pad1cc[4];
    float      mRange[4];             // +0x1d0
    float      mMat[8];               // +0x1e0
    IBatch_s00f6_9a30*    mBatch;                // +0x200
    IBatch_s00f6_9a30*    mBatch2;               // +0x204
    IBatch_s00f6_9a30*    mBatch3;               // +0x208

    void Init();                                                      // 0x00f69a30
    u32  HandleMessage(u32 id, void* p);                              // 0x00f69e50
    bool ReadTile(int face, const int* rect, float elapsed);          // 0x00f69f50
    bool DrawBrushLayer(u32 param);                                   // 0x00f6a3a0
    void Construct();                                                 // 0x00f6a4b0
    void Destroy();                                                   // 0x00f6a5d0
    void DrawBrush(u32 a, u32 b, void* p, void* q, u32 c);            // 0x00f6a6a0
    void SetBrushShaderData(void* p, int q);                          // 0x00f6a710
    void TextureMapQuadRTT(u32 a1, u32 a2, int a3, void* a4, u32 a5, void* a6, u32 a7); // 0x00f6a8d0

    void Refresh();                                                   // 0x00f67da0
    void InitViewer();                                                // 0x00f67e70
    bool BuildBrush(void* faces, u32 flipIdx, u32 a3, u32 a4);        // 0x00f68070
    void UpdateRange(void* p);                                        // 0x00f684c0
    bool DrawUnitQuad(int idx, u32 a, u32 b);                         // 0x00f68650
    void DrawRaster(int idx, u32 a, void* handle, u32 b);             // 0x00f68c80
    bool TextureMapQuad(u32 a, u32 b, u32 c, void* p, u32 d, void* e);// 0x00f68d50
    void PairResize(int size);                                        // 0x00f67360 (this = container)
    void PairClear();                                                 // 0x00f674c0
    void ApplyRaster(int idx, void* p);                               // 0x00f67810
};
// ---- items of slice s00f69a30 end

// ---- items of slice s00f6df40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint8_t gCubeFaceAxes[3][4];            // 0x0148f608
extern "C" double __cdecl fabs(double);
#pragma intrinsic(memcpy, memset)
#pragma intrinsic(fabs)
struct cSPVector3_s00f6_df40 {
    float x, y, z;
    cSPVector3_s00f6_df40() {}
    cSPVector3_s00f6_df40(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3_s00f6_df40(const cSPVector3_s00f6_df40& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cSPVector2_s00f6_df40 {
    float x, y;
    cSPVector2_s00f6_df40() {}
    cSPVector2_s00f6_df40(const cSPVector2_s00f6_df40& o) : x(o.x), y(o.y) {}
};
namespace SP {
struct cBrushVertex_s00f6_df40 {   // 0x1c
    cSPVector3_s00f6_df40 mPosition;   // 0x00
    cSPVector2_s00f6_df40 mUV;         // 0x0c
    float mIntensity;       // 0x14
    float mSize;            // 0x18
};
}
namespace SP {
struct cRibbonBrushPoly_s00f6_df40 {   // 0x1c4
    int mNumVertices;
    cBrushVertex_s00f6_df40 mVertices[16];
};
}
struct AABox {   // min/max box, empty while min.x > max.x
    cSPVector3_s00f6_df40 mMin;
    cSPVector3_s00f6_df40 mMax;
    void Extend(const cSPVector3_s00f6_df40& p) {
        if (mMin.x > mMax.x) {
            mMin = p;
            mMax = p;
        } else {
            if (mMin.x > p.x) mMin.x = p.x;
            else if (p.x > mMax.x) mMax.x = p.x;
            if (mMin.y > p.y) mMin.y = p.y;
            else if (p.y > mMax.y) mMax.y = p.y;
            if (mMin.z > p.z) mMin.z = p.z;
            else if (p.z > mMax.z) mMax.z = p.z;
        }
    }
};
struct Rect_s00f6_df40 {
    float x1, y1, x2, y2;
    Rect_s00f6_df40(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};
namespace eastl {
struct sp_vector_allocator_s00f6_df40 {
    int mFlags;
    int mUnused;
    sp_vector_allocator_s00f6_df40() {}
    void deallocate(void* p) {
        if (((int*)p)[-1] != 0)
            ::operator delete[](p);
    }
};
}
namespace eastl {
template <class T, class Allocator> struct VectorBase_s00f6_df40 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    VectorBase_s00f6_df40() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s00f6_df40() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
};
}
namespace eastl {
template <class T, class Allocator> class vector_s00f6_df40 : public VectorBase_s00f6_df40<T, Allocator> { public:
    void DoInsertValue(T* position, const T& value);   // 0x00f4c180 (cRibbonBrushPoly instance)
    void push_back(const T& value) {
        if (this->mpEnd < this->mpCapacity)
            ::new (this->mpEnd++) T(value);
        else
            DoInsertValue(this->mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
    bool empty() const { return this->mpBegin == this->mpEnd; }
};
}
typedef eastl::vector_s00f6_df40<SP::cRibbonBrushPoly_s00f6_df40, eastl::sp_vector_allocator_s00f6_df40> PolyVector;
struct BrushTarget {
    char pad0[0x60];
    unsigned int mWidth;    // 0x60
    unsigned int mHeight;   // 0x64
    unsigned int mDepth;    // 0x68
};
void ClipPolyToPlane(SP::cBrushVertex_s00f6_df40* verts, int* numVerts, const cSPVector3_s00f6_df40* plane);   // 0x00fc2c70
extern const cSPVector3_s00f6_df40 gCubeFaceClipPlanes[6][4];   // 0x016d6fa8
struct BrushCubeSplitter {
    void RenderFace(PolyVector* polys, int face, BrushTarget* target, int arg, const Rect_s00f6_df40* rect,
                    bool flag, int extra);   // 0x00f6c800
    void SplitPolysToCubeFaces(int arg, BrushTarget* target, int numPolys,
                               const SP::cRibbonBrushPoly_s00f6_df40* polys, int extra);
};
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
// ---- items of slice s00f6df40 end

// @ 0x00f4b180
cBrushVertex* BrushVertexVector::back()
{
    return mpEnd - 1;
}

// @ 0x00f4b190
BrushBigElem* CopyElemsBackward(BrushBigElem* first, BrushBigElem* last, BrushBigElem* dst)
{
    while (last != first) {
        --last;
        --dst;
        *dst = *last;
    }
    return dst;
}

// @ 0x00f4b4c0
void CopyElemsForward(BrushHugeElem* first, BrushHugeElem* last, BrushHugeElem* dst)
{
    for (; first != last; ++first) {
        if (dst)
            *dst = *first;
        ++dst;
    }
}

// @ 0x00f4b6e0
void cTerrainBrushEffect::SetTransform(void* p, const cTransform* t)
{
    cTransform tmp;
    tmp.mFlags = t->mFlags;
    tmp.mModificationCount = t->mModificationCount;
    tmp.mTranslation.x = t->mTranslation.x;
    tmp.mTranslation.y = t->mTranslation.y;
    tmp.mTranslation.z = t->mTranslation.z;
    tmp.mScale = t->mScale;
    tmp.mRotation.Assign(&t->mRotation);
    tmp.PreTransformBy((const cTransform*)p);
    mPreviousTransform = mTransform;
    mPreviousSize = mSize;
    mSize = tmp.mScale;
    mTransform = tmp;
    if (!mPreviousValuesInitialized) {
        mPreviousTransform = mTransform;
        mPreviousSize = mSize;
        float dx = tmp.mTranslation.x, dy = tmp.mTranslation.y, dz = tmp.mTranslation.z;
        if (sqrtf(dz * dz + dy * dy + dx * dx) > 0.01f) {
            mPreviousValuesInitialized = true;
            if (mDesc->mDrawMode == 3) {
                float v = mUserLevelParm;
                if (v == 9999.0f) {
                    float r = RandomRange(1.0f, mDesc->mLevelVary);
                    float lv = mDesc->mLevelValue;
                    if (lv < -1.0f) {
                        mLevelValue = TerrainEditor()->GetHeightAt(tmp.mTranslation) * r;
                    } else {
                        mLevelValue = lv * r;
                    }
                } else {
                    mLevelValue = v;
                }
            }
        }
    }
}

// @ 0x00f4c180
void RibbonPolyVector::DoInsertValue(SP::cRibbonBrushPoly* position, const SP::cRibbonBrushPoly& value)
{
    if (this->mpEnd != this->mpCapacity) {
        const SP::cRibbonBrushPoly* pValue = &value;
        if (pValue >= position && pValue < this->mpEnd)
            ++pValue;
        ::new ((void*)this->mpEnd) SP::cRibbonBrushPoly(*(this->mpEnd - 1));
        CopyPolysBackward(position, this->mpEnd - 1, this->mpEnd);
        *position = *pValue;
        ++this->mpEnd;
        return;
    }

    unsigned int nPrevSize = (unsigned int)(this->mpEnd - this->mpBegin);
    unsigned int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    SP::cRibbonBrushPoly* pNewData = nNewSize
        ? (SP::cRibbonBrushPoly*)EAAllocate(nNewSize * sizeof(SP::cRibbonBrushPoly), gSimulatorName, 0, 0,
                                        gAllocatorPath, 0xd1)
        : 0;
    SP::cRibbonBrushPoly* pNewEnd = CopyPolysForward(this->mpBegin, position, pNewData);
    ::new ((void*)pNewEnd) SP::cRibbonBrushPoly(value);
    pNewEnd = CopyPolysForward(position, this->mpEnd, ++pNewEnd);
    if (this->mpBegin != 0 && ((int*)this->mpBegin)[-1] != 0)
        ::operator delete[](this->mpBegin);
    this->mpEnd = pNewEnd;
    this->mpBegin = pNewData;
    this->mpCapacity = pNewData + nNewSize;
}

// @ 0x00f4c300
void cTerrainBrushEffect_s00f4_c300::ApplyEffect(float dt, float, cComponentStats*)
{
    Quaternion spare;
    cMapKernel mapKernel;

    if (mDesc->mDoFiltering) {
        switch (mDesc->mKernelType) {
        case 1:  mapKernel = kKernelSmooth;    break;
        case 2:  mapKernel = kKernelMedian;    break;
        case 3:  mapKernel = kKernelLowPass1;  break;
        case 4:  mapKernel = kKernelLowPass2;  break;
        case 5:  mapKernel = kKernelLowPass3;  break;
        case 6:  mapKernel = kKernelLowPass4;  break;
        case 7:  mapKernel = kKernelLowPass5;  break;
        case 8:  mapKernel = kKernelHighPass1; mapKernel.mOp = 6; break;
        case 9:  mapKernel = kKernelHighPass2; mapKernel.mOp = 6; break;
        case 10: mapKernel = kKernelHighPass3; mapKernel.mOp = 6; break;
        case 11: mapKernel = kKernelHighPass4; break;
        case 12: mapKernel = kKernelEdge1;     mapKernel.mOp = 1; break;
        case 13: mapKernel = kKernelEdge2;     mapKernel.mOp = 1; break;
        case 14: mapKernel = kKernelEdge3;     mapKernel.mOp = 1; break;
        case 15:
            mapKernel = kKernelAdd;
            mapKernel.mArray[4] = mDesc->mDeltaAmount;
            break;
        case 20:
            mapKernel = kKernelLevel;
            mapKernel.mArray[4] = mDesc->mDeltaAmount;
            break;
        case 16:
            mapKernel = kKernelAdd;
            mapKernel.mArray[4] = -mDesc->mDeltaAmount;
            break;
        case 18: break;
        case 19: break;
        case 17: break;
        default:
            return;
        }
        switch (mDesc->mKernelOp) {
        case 1: mapKernel.mOp = 0; break;
        case 2: mapKernel.mOp = 1; break;
        case 3: mapKernel.mOp = 6; break;
        }
    }

    float heightOffset7 = 0.0f;
    float seaLevelQ = 0.0f;
    if (mDesc->mWaterLevelIsZero) {
        cTerrainEditor_s00f4_c300* terrainEditor = TerrainEditor_s00f4_c300();
        seaLevelQ = terrainEditor->GetWaterLevel() * 2.0f - 1.0f;
        heightOffset7 = terrainEditor->GetWaterLevel() - 0.5f;
    }
    mapKernel.mCondOp = mDesc->mCondOp;
    mapKernel.mCondN1 = mDesc->mCondN1 + heightOffset7;
    mapKernel.mCondN2 = mDesc->mCondN2 + heightOffset7;
    mapKernel.mFallOffOp = mDesc->mFallOffOp;
    mapKernel.mFallOffN1 = mDesc->mFallOffN1 + heightOffset7;
    mapKernel.mFallOffN2 = mDesc->mFallOffN2 + heightOffset7;

    if (mDesc->mFilterGlobal || mDesc->mDoCubeMap) {
        float intensityRand = RandomRange(1.0f, mDesc->mIntensityVary);
        float intensity = intensityRand * mDesc->mIntensityCurve.front() * mIntensityScale;
        GetRandom()->RandomDoubleUniform();
        ApplyGlobal(intensity, mapKernel);
        Stop(0);
        return;
    }

    float elapsed = Min(dt, 1.0f);
    float accumTime2 = mAccumulatedTime + elapsed;
    float stepTime = 1.0f / mDesc->mImprintsPerSecond;
    int dummy = 0;
    uint32 nImprints = RoundToInt(accumTime2 * mDesc->mImprintsPerSecond);

    Vector3_s00f4_c300 oldUp5(mPreviousTransform.GetOffset());
    Vector3_s00f4_c300 curNormal7 = normalized_safe(mTransform.GetOffset());
    if (VectorLength(oldUp5) > 0.0001f)
        oldUp5 = Normalize(oldUp5);
    else
        oldUp5 = curNormal7;

    Matrix3_s00f4_c300 mat2;
    Quaternion rotPrev;
    Quaternion newRotation;
    Quaternion dirRotation;
    mat2 = mPreviousTransform.GetRotation();
    rotPrev = MatrixToQuaternion(mat2);
    mat2 = mTransform.GetRotation();
    newRotation = MatrixToQuaternion(mat2);
    if (Dot3(oldUp5) < 1.5258789e-05f || Dot3(curNormal7) < 1.5258789e-05f)
        dirRotation = kQuaternionIdentity;
    else
        dirRotation = QuaternionFromDirections(oldUp5, curNormal7);

    float invDt1 = 1.0f / elapsed;
    float travel = VectorLength(curNormal7 - oldUp5) * 500.0f;
    float spacingParam0 = 0.0f;
    float spacingStep3 = 0.0f;

    if (mDoSpacing) {
        mPreviousTransform = mTransform;
        if (mDoSpacingVary) {
            mDoSpacingVary = false;
            mSpacingVaryVal = RandomRange(1.0f, mDesc->mSpacingVary);
        }
        ScratchSlots<19>();
        float size = CurveValue(mDesc->mSizeCurve, 0.0f);
        ScratchSlots<1>();
        if (mUserSizeParm != 9999.0f)
            size = mUserSizeParm;
        float spacingVal = mSpacingVaryVal *
                        CurveValue(mDesc->mSpacingCurve, Clamp01(accumTime2 * mInvLifetime));
        float spacingDistance = size * spacingVal * mSize;
        if (mDistTraveled + travel >= spacingDistance) {
            nImprints = RoundToInt((mDistTraveled + travel) / spacingDistance);
            mDoSpacingVary = true;
            if (travel > 0.0f) {
                spacingParam0 = (spacingDistance - mDistTraveled) / travel;
                spacingStep3 = spacingDistance / travel;
            }
            mDistTraveled = mDistTraveled + travel;
            mDistTraveled = mDistTraveled - nImprints * spacingDistance;
            if (nImprints > 0)
                stepTime = elapsed / nImprints;
        } else {
            mDistTraveled = mDistTraveled + travel;
            nImprints = 0;
        }
    }

    for (uint32 i = 0; i < nImprints; i++) {
        mOverallTime = mOverallTime + stepTime;
        float age = mOverallTime * mInvLifetime;
        if (age > 1.0f) {
            Stop(0);
            return;
        }
        float stepStart = i * stepTime;
        float blend = (stepStart - mAccumulatedTime) * invDt1;
        if (mDoSpacing) {
            blend = spacingParam0;
            spacingParam0 = spacingParam0 + spacingStep3;
        }
        blend = Clamp(blend, 0.0f, 1.0f);

        float intensityVary = RandomRange(1.0f, mDesc->mIntensityVary);
        float intensity = intensityVary * CurveValue(mDesc->mIntensityCurve, age) * mIntensityScale;
        float sizeVary = RandomRange(1.0f, mDesc->mSizeVary);
        float size = sizeVary * CurveValue(mDesc->mSizeCurve, age) * mSize * mLODSizeScale;
        ScratchSlots<8>();
        if (mUserSizeParm != 9999.0f)
            size = mUserSizeParm;
        if (mUserLevelParm != 9999.0f)
            mLevelValue = mUserLevelParm;

        Quaternion imprintRot;
        Quaternion upBlend;
        Quaternion qIdentity(0.0f, 0.0f, 0.0f, 1.0f);
        if (mDesc->mRot[0] != 0.0f || mDesc->mRot[1] != 0.0f || mDesc->mRot[2] != 0.0f) {
            Vector3_s00f4_c300 randomRot;
            randomRot[0] = RandomRange(mDesc->mRot[0], mDesc->mRotVary[0]);
            randomRot[1] = RandomRange(mDesc->mRot[0], mDesc->mRotVary[1]);
            randomRot[2] = RandomRange(mDesc->mRot[0], mDesc->mRotVary[2]);
        }

        if (blend < 0.0001f) {
            imprintRot = rotPrev;
            upBlend = qIdentity;
        } else if (blend > 0.9999f) {
            imprintRot = newRotation;
            upBlend = dirRotation;
        } else {
            imprintRot = Slerp(rotPrev, newRotation, blend);
            upBlend = Slerp(qIdentity, dirRotation, blend);
        }

        Vector3_s00f4_c300 position(RotateVector(mPreviousTransform.GetOffset(), upBlend));
        if (!mDesc->mRibbonBrush) {
            Imprint(position, imprintRot, size, intensity, mapKernel);
        } else if (!mRibbonBrushList.size() || !IsClose(position, mRibbonBrushList.back().mPosition)) {
            ScratchSlots<8>();
            mRibbonBrushList.push_back();
            cBrushVertex_s00f4_c300* vertex = &mRibbonBrushList.back();
            vertex->mPosition = position;
            vertex->mUV = Vector2_s00f4_c300(0.0f, 0.0f);
            vertex->mIntensity = intensity;
            vertex->mSize = size;
        }
    }

    mAccumulatedTime = mAccumulatedTime + elapsed - nImprints * stepTime;
}

// @ 0x00f66d20
void SP::cDistCellMesh::Init(const void* desc, int indexCount, int numCells)
{
    mIndexCount = indexCount;
    mNumCells = numCells;

    if (g_meshRefCount++ == 0) {
        g_indexBufferLarge_s00f6_6050 = (SP::cIndexBuffer*)CreateRenderBuffer(&g_renderDevice, 0xc00, 0xc00,
                                                              8, 4, 0);
        void* data = 0;
        g_indexBufferLarge_s00f6_6050->Lock(2, &data);
        {
            uint16_t* p = (uint16_t*)data;
            for (int i = 0; i < 0x400; i++, p += 3) {
                p[0] = (uint16_t)i;
                p[1] = (uint16_t)(i + 1);
                p[2] = (uint16_t)(i + 2);
            }
        }
        g_indexBufferLarge_s00f6_6050->Unlock(&data);

        g_indexBufferSmall_s00f6_6050 = (SP::cIndexBuffer*)CreateRenderBuffer(&g_renderDevice, 0x100, 0x100,
                                                              8, 5, 0);
        data = 0;
        g_indexBufferSmall_s00f6_6050->Lock(2, &data);
        {
            uint16_t* q = (uint16_t*)data;
            for (int i = 0; i < 0x100; i++)
                q[i] = (uint16_t)i;
        }
        g_indexBufferSmall_s00f6_6050->Unlock(&data);
    }

    mTexture = LoadTexture(desc);
    mBuffer = (SP::cMeshBuffer*)CreateMeshBuffers(mTexture, mIndexCount, 1, 0);
    mDynamicBuffer = numCells ? CreateRenderBuffer(&g_renderDevice, numCells, numCells,
                                                   0x208, 4, 0) : 0;
    mMesh = SP_CreateMesh(1);
}

// @ 0x00f66e70
SP::cDistCellMesh::~cDistCellMesh()
{
    if (mMesh) {
        FreeArrayMemory(mMesh);
        mMesh = 0;
    }
    if (mDynamicBuffer) {
        ReleaseRenderBuffer(mDynamicBuffer);
        mDynamicBuffer = 0;
    }
    if (mBuffer) {
        ReleaseMeshBuffer(mBuffer);
        mBuffer = 0;
    }
    mTexture = 0;
    if (--g_meshRefCount == 0) {
        ReleaseRenderBuffer(g_indexBufferSmall_s00f6_6050);
        g_indexBufferSmall_s00f6_6050 = 0;
        ReleaseRenderBuffer(g_indexBufferLarge_s00f6_6050);
        g_indexBufferLarge_s00f6_6050 = 0;
    }
}

// @ 0x00f672b0
void TerrainDrawDestroy(void* self)
{
    ((TerrainDraw*)self)->Deinit();
    if (self) {
        void** vt = *(void***)self;
        ((void(__thiscall*)(void*, int))vt[0])(self, 1);
    }
}

// @ 0x00f672f0
void* __cdecl AllocTerrainDraw(void* a, void* b, void* c)
{
    TerrainDraw* p = (TerrainDraw*)EAAllocate(0x34, "Terrain/TerrainDraw", 0, 0, 0, 0);
    TerrainDraw* r = 0;
    if (p) {
        p->mpVb = 0;
        p->mpIb = 0;
        p->mpIb2 = 0;
        p->mpShader = 0;
        p->mStart0 = 0;
        p->mCount0 = 0;
        p->mStart1 = 0;
        p->mCount1 = 0;
        p->mBase0 = 0;
        p->mBase1 = 0;
        p->mLockState = 0;
        p->mpVtbl = (void**)0x0148f598;
        p->mpParam = (void*)1;
        r = p;
    }
    ((TerrainDraw*)r)->Init(a, b, c);
    return r;
}

// @ 0x00f67360
char TempExtract::Build(int size)
{
    unsigned texA, texB, nameA, nameB;
    if (size == 0x20) {
        texA = 0x860dfc11;
        nameA = 0x0148f660;   // "TerrainTempExtract0"
        texB = 0x860dfc10;
        nameB = 0x0148f64c;   // "TerrainTempExtract1"
    } else {
        texA = 0x860dfc13;
        nameA = 0x0148f688;   // "TerrainTempExtract2"
        texB = 0x860dfc12;
        nameB = 0x0148f674;   // "TerrainTempExtract3"
    }

    TexFactory* svc = (TexFactory*)TerrainManager();
    void** vt = svc->mpVtbl;

    unsigned out[2];
    ((void*(__thiscall*)(void*, unsigned*, int, int, int, int, int, int))vt[0x10 / 4])(
        svc, out, size, size, 0x15, 0, (int)texA, 0);
    hA_handle = (void*)out[0];
    hA_id = (int)out[1];
    ((void(__thiscall*)(void*, unsigned, unsigned, unsigned))vt[0x48 / 4])(svc, out[0], out[1], nameA);
    if (hA_id != -1)
        hA_tex = (int)((void*(__thiscall*)(void*, unsigned, int))vt[0x18 / 4])(svc, out[0], out[1]);

    buf0 = EAAllocate(size * size * 4, "Terrain/TerrainEditor/TempExtractBuffer0", 0, 0, 0, 0);

    ((void*(__thiscall*)(void*, unsigned*, int, int, int, int, int, int))vt[0x10 / 4])(
        svc, out, size, size, 0x15, 0, (int)texB, 0);
    hB_handle = (void*)out[0];
    hB_id = (int)out[1];
    ((void(__thiscall*)(void*, unsigned, unsigned, unsigned))vt[0x48 / 4])(svc, out[0], out[1], nameB);
    if (hB_id != -1)
        hB_tex = (int)((void*(__thiscall*)(void*, unsigned, int))vt[0x18 / 4])(svc, out[0], out[1]);

    buf1 = EAAllocate(size * size * 4, "Terrain/TerrainEditor/TempExtractBuffer1", 0, 0, 0, 0);
    return 1;
}

// @ 0x00f674c0
void TempExtract::Destroy()
{
    TexFactory* svc = (TexFactory*)TerrainManager();
    if (hB_tex != 0) {
        void** vt = svc->mpVtbl;
        ((void(__thiscall*)(void*, void*, int))vt[0x14 / 4])(svc, hB_handle, hB_id);
        hB_tex = 0;
        hB_handle = (void*)-1;
    }
    if (buf1) {
        operator_delete(buf1);
        buf1 = 0;
    }
    if (hA_tex != 0) {
        void** vt = svc->mpVtbl;
        ((void(__thiscall*)(void*, void*, int))vt[0x14 / 4])(svc, hA_handle, hA_id);
        hA_tex = 0;
        hA_handle = (void*)-1;
    }
    if (buf0) {
        operator_delete(buf0);
        buf0 = 0;
    }
}

// @ 0x00f675b0
void __stdcall FUN_00f675b0(char* self, char* info, float* out)
{
    int kind = *(int*)(info + 0xc);
    if (kind == 5 || kind == 6) {
        out[0] = *(float*)(info + 0x1c);
        out[1] = *(float*)(info + 0x10);
        float a = *(float*)(info + 0x14);
        if (a == *(float*)(info + 0x18)) {
            if (*(int*)(info + 0xc) == 5) {
                out[2] = a;
                out[3] = a + g_one_1485720;
            } else {
                out[3] = a;
                out[2] = a - g_one_1485720;
            }
            goto tail;
        }
        out[2] = a;
        out[3] = *(float*)(info + 0x18);
    } else {
        out[0] = *(float*)(info + 0x1c);
        if (kind == 3) {
            out[1] = 0.0f;
            out[2] = 0.0f;
            out[3] = *(float*)(info + 0x10);
        } else {
            out[1] = g_one_1485720;
            if (kind != 4) {
                out[2] = g_one_1485720;
                out[3] = 0.0f;
                if (*(int*)(info + 0xc) == 2)
                    out[1] = g_c_13eb1bc;
                else if (*(int*)(info + 0xc) == 1) {
                    out[2] = g_c_1470f1c;
                    out[3] = g_c_148f69c;
                }
                goto tail;
            }
            out[2] = *(float*)(info + 0x18);
            out[3] = *(float*)(info + 0x14);
        }
    }
tail:
    if (*self != 0) {
        int k = *(int*)(self + 0x2c);
        if (k == 6) {
            out[0] = g_one_1485720;
            out[2] = g_half_1471064;
            out[1] = g_one_1485720;
            return;
        }
        out[2] = g_one_1485720;
        if (k == 1) {
            out[0] = g_one_1485720;
            out[1] = g_one_1485720;
            return;
        }
        out[0] = 0.0f;
        out[1] = g_one_1485720;
    }
}

// @ 0x00f67770
int __stdcall FUN_00f67770(char* self, char* info)
{
    if (info[6] != 0) {
        if (*(int*)(info + 0xc) != 3 && *(int*)(info + 0xc) != 4)
            return 0x0e;
        return 0x0f;
    }
    if (*self != 0)
        return (self[1] != 0) + 5;
    int kind = *(int*)(info + 0xc);
    if (kind == 5)
        return kind + 0xd;
    if (kind == 6)
        return kind + 0xd;
    if (kind == 3 && info[4])
        return (info[5] != 0) + 3;
    if (kind == 3 || kind == 4)
        return 9;
    if (info[4] != 0)
        return (info[5] != 0) + 1;
    return 8;
}

// @ 0x00f67810
void TerrainFace::Draw(int slot, void* a3)
{
    char* p = (char*)this;
    RasterState raster;       // rw::graphics::RasterState on the stack (0x10 bytes)
    ShaderGet(0x201, 0, 0);
    void* e = TerrainEditorGet();
    void* u = *(void**)(*(char**)((char*)e + 0x28) + 4);
    raster.Construct(u, 0, *(void**)(p + 0x20 + slot * 4));
    ((Viewer_s00f6_6f80*)*(void**)(p + 0x1c))->SetRaster(p + 0x6c, true);
    if (((Viewer_s00f6_6f80*)*(void**)(p + 0x1c))->Update()) {
        void* o = *(void**)(p + 0x204);
        void** vt = *(void***)o;
        ((void(__thiscall*)(void*, void*, void*))vt[0xc / 4])(o, u, a3);
        ((Viewer_s00f6_6f80*)*(void**)(p + 0x1c))->EndDraw();
    }
    raster.Clear();
}

// @ 0x00f678d0
float TerrainFace::GetDepth()
{
    char* p = (char*)this;
    if (p[0x158] != 0)
        return *(float*)(p + 0x15c);
    void* o = *(void**)(p + 0x74);
    if (!o)
        return g_half_1471064;
    void* r = ((void*(__thiscall*)(void*))((void**)*(void***)o)[0x10 / 4])(o);
    return ((DepthCtx*)r)->Read();
}

// @ 0x00f67900
void TerrainFace::MergeRectA(int slot, float* r)
{
    Vec4_s00f6_6f80* v = (Vec4_s00f6_6f80*)((char*)this + ((slot + 8) << 4));
    if (v->x == v->z || v->y == v->w) {
        *v = *(Vec4_s00f6_6f80*)r;
        return;
    }
    if (r[0] < v->x) v->x = r[0];
    if (r[1] < v->y) v->y = r[1];
    if (r[2] > v->z) v->z = r[2];
    if (r[3] > v->w) v->w = r[3];
}

// @ 0x00f679b0
void TerrainFace::MergeRectB(int slot, float* r)
{
    Vec4_s00f6_6f80* v = (Vec4_s00f6_6f80*)((char*)this + ((slot + 0xe) << 4));
    if (v->x == v->z || v->y == v->w) {
        *v = *(Vec4_s00f6_6f80*)r;
        return;
    }
    if (r[0] < v->x) v->x = r[0];
    if (r[1] < v->y) v->y = r[1];
    if (r[2] > v->z) v->z = r[2];
    if (r[3] > v->w) v->w = r[3];
}

// @ 0x00f67aa0
float TerrainFace::ProjectDir(float dx, float dy, float dz)
{
    char* p = (char*)this;
    if (*(void**)(p + 0x20) == 0)
        return 0.0f;

    float invLen = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    float nx = dx * invLen;
    float ny = dy * invLen;
    float nz = dz * invLen;
    float ax = fabsf(nx);
    float ay = fabsf(ny);
    float az = fabsf(nz);

    float u, v;
    int face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            u = (ny / nx + 1.0f) * 0.5f;
            v = (nz / ax + 1.0f) * 0.5f;
            face = (nx < 0.0f) ? 3 : 2;
        } else {
            u = (nz / ny + 1.0f) * 0.5f;
            v = (nx / ay + 1.0f) * 0.5f;
            face = (ny < 0.0f) ? 5 : 4;
        }
    } else {
        u = (nx / nz + 1.0f) * 0.5f;
        v = (ny / az + 1.0f) * 0.5f;
        face = (nz < 0.0f) ? 1 : 0;
    }

    int idx[2];
    SP_CoordToIndex(idx, 0x200, &u);

    unsigned* sprite = *(unsigned**)(p + 0x20 + face * 4);
    unsigned char c = *(unsigned char*)(sprite + 0x10 / 4);

    unsigned rect[8];
    rect[0] = 0x20;
    rect[1] = 0x20;
    rect[2] = *(unsigned*)&u;
    rect[3] = *(unsigned*)&v;
    rect[4] = (unsigned)(int)u + 1;
    rect[5] = (unsigned)(int)v + 1;
    rect[6] = 0;
    rect[7] = 0;
    (void)c;

    int slot = *(int*)(p + 0x1c4);
    void* tex = *(void**)(p + 0x1b4 + slot * 4);
    *(int*)(p + 0x1c4) = 1 - slot;

    void* a = *(void**)((char*)tex + 8);
    void* b = *(void**)((char*)sprite + 8);
    unsigned h1 = 0, h2 = 0;
    void** vta = *(void***)a;
    ((void(__thiscall*)(void*, void*, int, unsigned*))vta[0x48 / 4])(vta, a, 0, &h1);
    void** vtb = *(void***)b;
    ((void(__thiscall*)(void*, void*, int, unsigned*))vtb[0x48 / 4])(vtb, b, 0, &h2);

    if (h1 != 0) {
        if (h2 != 0) {
            void* dev = *(void**)0x016f89d0;
            void** devVt = *(void***)dev;
            ((void(__thiscall*)(void*, void*, unsigned, void*, unsigned, void*, int))devVt[0x88 / 4])(
                devVt, dev, h2, rect, h1, &rect[4], 1);
            RWFillSpriteTexture(rect, h1 >> 3, 0);
        }
        void** vh1 = *(void***)h1;
        ((void(__thiscall*)(void*, void*))vh1[8 / 4])(vh1, (void*)h1);
    }
    if (h2 != 0) {
        void** vh2 = *(void***)h2;
        ((void(__thiscall*)(void*, void*))vh2[8 / 4])(vh2, (void*)h2);
    }

    return ((float)((rect[0] >> 8) & 0xffff) * g_c_148f6a0) * 2.0f - 1.0f;
}

// @ 0x00f67da0
void TerrainFace::ClearSprites()
{
    char* p = (char*)this;
    if (*(void**)(p + 0x20) == 0)
        return;
    if (*(void**)(p + 0x74) != 0)
        FUN_00fa3b30(*(void**)(p + 0x74));

    struct RGBA { float r, g, b, a; } col;
    col.r = g_c_148f6a8;
    col.g = g_c_148f6a4;
    col.b = 0.0f;
    col.a = 0.0f;

    int* raster = (int*)(p + 0x38);
    float* sprite = (float*)(p + 0x88);
    Viewer_s00f6_6f80* v = *(Viewer_s00f6_6f80**)(p + 0x1c);
    for (int i = 0; i < 6; ++i) {
        sprite[-2] = 0.0f;
        sprite[-1] = 0.0f;
        sprite[0] = g_one_1485720;
        sprite[1] = g_one_1485720;
        v->SetRaster(raster, true);
        if (v->Update()) {
            v->SetClearColor(&col);
            v->Clear(7);
            v->EndDraw();
        }
        sprite += 4;
        raster += 2;
    }
}

// @ 0x00f68070
namespace SP {
bool cTerrainEditor_s00f6_7e70::BuildBrush(FaceVec* faces, u32 flipIdx, u32 a3, u32 a4)
{
    union { int* idx; int count; } nVertexIdx;
    nVertexIdx.idx = 0;
    int n0 = 0, n2 = 0, total = 0;
    int idxData = 0;
    int* unused26 = 0;
    const int n = (int)(((char*)faces->mpEnd - (char*)faces->mpBegin) / 0x1c4);
    int rest[2];
    rest[0] = 0;
    rest[1] = 0;
    if (n >= 2) {
        Face* f = faces->mpBegin;
        int iters = ((n - 2) >> 1) + 1;
        nVertexIdx.count = iters * 2;
        do {
            rest[0] += f->count;
            n0 += f->count * 3 - 6;
            rest[1] += f[1].count;
            n2 += f[1].count * 3 - 6;
            f += 2;
        } while (--iters);
    }
    const u32 nVi = (u32)nVertexIdx.count;
    if (nVi < (u32)n) {
        idxData = ((FaceOrIdx*)faces->mpBegin)[nVi].count;
        total = idxData * 3 - 6;
    }
    n0 += n2;
    n0 += total;
    void* out = 0;
    if (!mBatch2->BigAlloc(&out, 0x2c, rest[0] + rest[1] + idxData, (const int*)&nVertexIdx, n0, 1))
        return false;

    const float one = C_1485720;
    const float eps = C_148f6cc;
    const float two = C_1470f1c;
    const float half = C_1471064;
    const u8* te = &T_148f608[(flipIdx >> 1) * 4];
    float arr[3];
    arr[0] = (flipIdx & 1) ? C_13eb1bc : one;
    arr[2] = arr[0];
    arr[1] = 1.0f;
    float t0 = arr[te[0]];
    float t1 = arr[te[1]];
    float t2 = arr[te[2]];

    float tb[4];
    B0(a3, a4, tb);

    u32 written = 0;
    u32 fi = 0;
    for (; fi < (u32)(((char*)faces->mpEnd - (char*)faces->mpBegin) / 0x1c4); ++fi) {
        int vi = 0;
        if (faces->mpBegin[fi].count > 0) {
            char* vo = (char*)out + written * 0x2c;
            do {
                FaceVertex* fv = &faces->mpBegin[fi].v[vi];
                float px = fv->y * eps;
                float py = 1.0f - fv->z * eps;
                *(float*)(vo + 0x00) = px;
                *(float*)(vo + 0x04) = py;
                *(float*)(vo + 0x08) = 1.0f;
                *(float*)(vo + 0x0c) = 1.0f;
                arr[0] = *(float*)(vo + 0x00);
                arr[1] = 1.0f - *(float*)(vo + 0x04);
                float r1 = arr[te[1]];
                float r0 = arr[te[0]];
                *(float*)(vo + 0x24) = fv->f10;
                float r2 = arr[te[2]];
                *(float*)(vo + 0x28) = fv->f14;
                tb[0] = fv->f18;
                *(float*)(vo + 0x10) = tb[0];
                *(float*)(vo + 0x14) = tb[1];
                *(float*)(vo + 0x18) = tb[2];
                *(float*)(vo + 0x1c) = tb[3];
                float rgb[3];
                rgb[0] = ((r0 * two - one) * t0) * half + half;
                rgb[1] = ((r1 * two - one) * t1) * half + half;
                rgb[2] = ((r2 * two - one) * t2) * half + half;
                *(u32*)(vo + 0x20) = ColorRGBToU32(rgb);
                ++written;
                vo += 0x2c;
                arr[2] = 1.0f;
            } while (++vi < faces->mpBegin[fi].count);
        }
    }

    u16* pidx = (u16*)idxData;
    u32 cursor = 0;
    u32 base = 0;
    u32 fc = 0;
    for (; fc < (u32)(((char*)faces->mpEnd - (char*)faces->mpBegin) / 0x1c4); ++fc) {
        int k = 0;
        int n3 = faces->mpBegin[fc].count - 2;
        if (n3 > 0) {
            do {
                pidx[cursor] = (u16)base;
                pidx[cursor + 1] = (u16)(base + k + 1);
                pidx[cursor + 2] = (u16)(base + k + 2);
                ++k;
                cursor += 3;
            } while (k < n3);
        }
        base += faces->mpBegin[fc].count;
    }
    return true;
}
}  // namespace SP

// @ 0x00f684c0
namespace SP {
void cTerrainEditor_s00f6_7e70::UpdateRange(int* p)
{
    float* f = mRange;
    f[0] = -2.0f;
    f[1] = -1.0f;
    f[2] = 1.0f;
    f[3] = 2.0f;

    int mode = p[0x30 / 4];
    if (mode == 1) {
        f[0] = -2.0f;
        f[1] = -1.0f;
        if (p[0x3c / 4] == 1)
            f[2] = *(float*)((char*)p + 0x40);
        else
            f[2] = *(float*)((char*)p + 0x34);
        f[3] = *(float*)((char*)p + 0x34);
    } else if (mode == 2) {
        f[0] = *(float*)((char*)p + 0x34);
        if (p[0x3c / 4] == 1)
            f[1] = *(float*)((char*)p + 0x40);
        else
            f[1] = *(float*)((char*)p + 0x34);
        f[2] = 1.0f;
        f[3] = 2.0f;
    } else if (mode == 3) {
        f[0] = *(float*)((char*)p + 0x34);
        f[1] = *(float*)((char*)p + 0x34);
        f[2] = *(float*)((char*)p + 0x38);
        f[3] = *(float*)((char*)p + 0x38);
        if (p[0x3c / 4] == 1) {
            f[0] = *(float*)((char*)p + 0x40);
            f[3] = *(float*)((char*)p + 0x44);
        }
    }

    f[2] = f[2] + 0.0078125f;
    f[3] = f[3] + 0.0078125f;

    float dx = f[1] - f[0];
    float dy = f[3] - f[2];
    float sx = dx > 0.0f ? 1.0f / dx : 0.0f;
    float sy = dy > 0.0f ? -1.0f / dy : 0.0f;

    f[4] = sx;
    f[5] = 0.0f;
    f[6] = sy;
    f[7] = 0.0f;
    f[8] = f[0] * sx;
    f[9] = -1.0f;
    f[10] = f[2] * sy - 1.0f;
    f[11] = 0.0f;

    FUN_00777ae0(0x24a, f, 0);
}
}  // namespace SP

// @ 0x00f68650
namespace SP {
bool cTerrainEditor_s00f6_7e70::DrawUnitQuad(int idx, u32 a, u32 b)
{
    u32 shader = GetShaderTable_s00f6_7e70()->s4c->id;

    void* out = 0;
    if (!mBatch->Alloc(&out, 0x18, 4, 0))
        return false;

    memset(out, 0, 0x60);
    *(Vec3_s00f6_7e70*)((char*)out + 0x00) = Vec3_s00f6_7e70(0.0f, 0.0f, 0.0f);
    *(Vec3_s00f6_7e70*)((char*)out + 0x18) = Vec3_s00f6_7e70(1.0f, 0.0f, 0.0f);
    *(Vec3_s00f6_7e70*)((char*)out + 0x30) = Vec3_s00f6_7e70(0.0f, 1.0f, 0.0f);
    *(Vec3_s00f6_7e70*)((char*)out + 0x48) = Vec3_s00f6_7e70(1.0f, 1.0f, 0.0f);
    FUN_00777ae0(0x201, 0, 0);

    mViewer->SetRaster(&mRasterDesc[idx], true);
    if (!mViewer->Update())
        return true;

    Binding_s00f6_7e70 bind;
    bind.Init(shader, 0, a);
    if (!mBatch->Apply(shader, (void*)b)) {
        bind.Done();
        return false;
    }
    mBatch->Flush();
    mViewer->Finish();
    bind.Done();
    return true;
}
}  // namespace SP

// @ 0x00f687f0
namespace SP {
void __stdcall cTerrainEditor_s00f6_7e70::TessellateBrush(void* out, void* vec, const float* in, int count, int strips, int limit, int unused)
{
    (void)unused;
    const float eps = 0.001953125f;

    int written = 0;
    if (count >= 4) {
        const float* src = in + 3;
        int iters = ((count - 4) >> 2) + 1;
        written = iters * 4;
        float* dst = (float*)out;
        do {
            dst[0x00] = src[-3] * eps;
            dst[0x01] = 1.0f - src[-2] * eps;
            dst[0x02] = 1.0f;
            dst[0x03] = 1.0f;
            dst[0x0b] = src[0] * eps;
            dst[0x0c] = 1.0f - src[1] * eps;
            dst[0x0d] = 1.0f;
            dst[0x0e] = 1.0f;
            dst[0x16] = src[3] * eps;
            dst[0x17] = 1.0f - src[4] * eps;
            dst[0x18] = 1.0f;
            dst[0x19] = 1.0f;
            dst[0x21] = src[6] * eps;
            dst[0x22] = 1.0f - src[7] * eps;
            dst[0x23] = 1.0f;
            dst[0x24] = 1.0f;
            dst += 0x2c;
            src += 12;
            --iters;
        } while (iters);
    }
    if (written < count) {
        const float* src = in + written * 3;
        int n = count - written;
        float* dst = (float*)out + written * 0xb;
        written += n;
        do {
            dst[0] = src[0] * eps;
            dst[1] = 1.0f - src[1] * eps;
            dst[2] = 1.0f;
            dst[3] = 1.0f;
            dst += 0xb;
            src += 3;
            --n;
        } while (n);
    }

    u16 idxbuf[2046];
    int cursor = 0;
    int k = 0;
    int n2 = count - 2;
    if (n2 > 0) {
        do {
            idxbuf[cursor] = 0;
            idxbuf[cursor + 1] = (u16)(k + 1);
            idxbuf[cursor + 2] = (u16)(k + 2);
            ++k;
            cursor += 3;
        } while (k < n2);
    }

    int start = 0;
    while (strips > 0) {
        int newStrips = (cursor - start) / 3;
        int top = cursor;
        if (written + newStrips * 3 <= limit && (u32)(cursor + newStrips * 12) < 0x801 && newStrips > 0) {
            float* dst = (float*)out + written * 0xb;
            u16* ip = idxbuf + start + 2;
            int cnt = newStrips;
            do {
                u16 i0 = ip[-2];
                u16 i1 = ip[-1];
                u16 i2 = ip[0];
                int m = written;
                const float* v0 = (const float*)((char*)out + i0 * 0x2c);
                const float* v1 = (const float*)((char*)out + i1 * 0x2c);
                const float* v2 = (const float*)((char*)out + i2 * 0x2c);
                dst[0x00] = (v1[0] + v0[0]) * 0.5f;
                dst[0x01] = (v1[1] + v0[1]) * 0.5f;
                dst[0x02] = (v1[2] + v0[2]) * 0.5f;
                dst[0x03] = (v1[3] + v0[3]) * 0.5f;
                ++written;
                dst[0x0b] = (v1[0] + v2[0]) * 0.5f;
                dst[0x0c] = (v1[1] + v2[1]) * 0.5f;
                dst[0x0d] = (v1[2] + v2[2]) * 0.5f;
                dst[0x0e] = (v1[3] + v2[3]) * 0.5f;
                ++written;
                dst[0x16] = (v2[0] + v0[0]) * 0.5f;
                dst[0x17] = (v2[1] + v0[1]) * 0.5f;
                dst[0x18] = (v2[2] + v0[2]) * 0.5f;
                dst[0x19] = (v2[3] + v0[3]) * 0.5f;
                ++written;
                idxbuf[cursor] = i0;
                idxbuf[cursor + 1] = (u16)m;
                idxbuf[cursor + 2] = (u16)(m + 2);
                idxbuf[cursor + 3] = i1;
                idxbuf[cursor + 4] = (u16)(m + 1);
                idxbuf[cursor + 5] = (u16)m;
                idxbuf[cursor + 6] = i2;
                idxbuf[cursor + 7] = (u16)(m + 2);
                idxbuf[cursor + 8] = (u16)(m + 1);
                idxbuf[cursor + 9] = (u16)m;
                idxbuf[cursor + 10] = (u16)(m + 1);
                idxbuf[cursor + 11] = (u16)(m + 2);
                dst += 0x21;
                cursor += 12;
                ip += 3;
            } while (--cnt);
        }
        start = top;
        --strips;
    }

    VecInsert(vec, idxbuf + start, (cursor - start) * 2);
}
}  // namespace SP

// @ 0x00f68c80
namespace SP {
void cTerrainEditor_s00f6_7e70::DrawRaster(int idx, u32 a, int* handle, u32 b)
{
    int sh = FUN_00f67770(a, handle);
    u32 shader = GetShaderTable_s00f6_7e70()->table[sh]->id;
    Binding_s00f6_7e70 b0;
    b0.Init(shader, 0, mHandle68);

    void* h = (void*)*handle;
    u32 resolved;
    if (h != 0) {
        if ((*(u8*)((char*)h + 4) & 1) == 0)
            FUN_0067dd60()->Resolve(h);
        resolved = *(u32*)h;
    } else {
        resolved = 0;
    }

    Binding_s00f6_7e70 b1;
    b1.Init(shader, 1, resolved);

    mViewer->SetRaster(&mRasterDesc[idx], true);
    if (mViewer->Update()) {
        mBatch2->Apply(shader, (void*)b);
        mBatch2->Flush();
        mViewer->Finish();
    }
    b1.Done();
    b0.Done();
}
}  // namespace SP

// @ 0x00f69a30
void cTerrainEditor_s00f6_9a30::Init()
{
    mMaxTimePerRenderJob = 100.0f;

    mBatch  = (IBatch_s00f6_9a30*)FUN_00f672f0("V3FC4BT2F", 0x100, 0);
    mBatch2 = (IBatch_s00f6_9a30*)FUN_00f672f0("V4FN4FC4BT2F", 0x400, 0xc00);
    mBatch3 = (IBatch_s00f6_9a30*)FUN_00f672f0("V4FN3FC4BT4FT4FT4FT4FT4F", 0x10, 0);

    IPropertyManager* pm = (IPropertyManager*)FUN_0067de30();
    void* old = mpSphere;
    if (old) {
        mpSphere = 0;
        ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
    pm->Register(0x5f848353, 0x243ad2b, &mpSphere);

    IServer* server = (IServer*)FUN_0067dcc0();
    mpServer = server;
    mpHandler = this;
    mpIdArray = (void*)&D_148f614;
    mnIdArrayCount = 4;
    mnPriority = 0;
    if (server) {
        u32 i = 0;
        do {
            u32 id = *(const u32*)((const char*)&D_148f614 + i);
            server->Register(this, id);
            i += 4;
        } while (i < 0x10);
    }

    mTempBuffer0 = 0;
    mTempBufferF = 0.0f;

    for (int i = 0; i < 6; ++i)
        mGPUDirtyFace[i] = 0;

    const float z = 0.0f;
    for (int i = 0; i < 6; ++i) {
        mCPUDirtyRect[i].l = z;
        mCPUDirtyRect[i].t = z;
        mCPUDirtyRect[i].r = z;
        mCPUDirtyRect[i].b = z;
    }
    for (int i = 0; i < 6; ++i) {
        mBrushDirtyRect[i].l = z;
        mBrushDirtyRect[i].t = z;
        mBrushDirtyRect[i].r = z;
        mBrushDirtyRect[i].b = z;
    }

    IVP* vp = (IVP*)FUN_0067dda0();
    RectId* dst = mHeightRectIDArray;
    RasterLike** rasters = mHeightRasterArray;
    const u32* ids = (const u32*)&T_148f624;
    do {
        u32 tmp[2];
        u32* r = (u32*)vp->CreateRasterID(tmp, 0x200, 0x200, 0x15, 0, *ids, 0);
        u32 pageID = r[0];
        u32 allocID = r[1];
        vp->Remap(pageID, allocID, "TerrainHeightRasters");
        if (allocID != 0xffffffff) {
            *rasters = (RasterLike*)vp->GetRaster(pageID, allocID);
            dst->pageID = pageID;
            dst->allocID = allocID;
        }
        ++dst;
        ++rasters;
        ++ids;
    } while ((int)ids < 0x148f63c);

    IResolver_s00f6_9a30* res = (IResolver_s00f6_9a30*)FUN_0067dd60_s00f6_9a30();
    RasterLike* tex = (RasterLike*)res->CreateTexture(0xc88d71ef, g_015b0e40, 0x200, 0x200, 1, 8, 0x51, 0);
    RasterLike* oldTex = mTempExtractTexture;
    if (tex != oldTex) {
        if (tex) {
            void** rc = (void**)tex;
            _InterlockedExchangeAdd((volatile long*)&rc[2], 1);
        }
        mTempExtractTexture = tex;
        if (oldTex) {
            void** rc = (void**)oldTex;
            _InterlockedExchangeAdd((volatile long*)&rc[2], -1);
            if (_InterlockedExchangeAdd((volatile long*)&rc[2], 0) < 1)
                _InterlockedExchangeAdd((volatile long*)&rc[2], 1);
        }
    }

    u32 tmp2[2];
    u32* r2 = (u32*)vp->CreateRasterID(tmp2, 0x200, 0x200, 0x15, 0, 0x3356f173, 0);
    u32 pageID = r2[0];
    u32 allocID = r2[1];
    vp->Remap(pageID, allocID, "TerrainPing");
    if (allocID != 0xffffffff) {
        mHeightRTPingRaster = (RasterLike*)vp->GetRaster(pageID, allocID);
        mHeightRTPingRectID.pageID = pageID;
        mHeightRTPingRectID.allocID = allocID;
    }

    ((cTerrainEditor_s00f6_9a30*)((char*)this + 0x180))->PairResize(0x40);
    ((cTerrainEditor_s00f6_9a30*)((char*)this + 0x1a4))->PairResize(0x20);
    return InitViewer();
}

// @ 0x00f69e50
u32 cTerrainEditor_s00f6_9a30::HandleMessage(u32 id, void* p)
{
    if (id > 0x12d74a2) {
        if (id == 0x24e5e7f) {
            void* t = GetShaderTable_s00f6_9a30();
            FUN_00f959f0(t, *(u8*)p);
            return 1;
        }
        return 0;
    }
    if (id == 0x12d74a2) {
        if (!mTextureType)
            return 1;
        void* s;
        if (p == 0 || (s = *(void**)((char*)p + 8)) == 0) {
            void* app = (void*)FUN_0067dd10();
            void** avt = *(void***)app;
            void* ar = ((void*(__thiscall*)(void*))avt[0x50 / 4])(app);
            void** rvt = *(void***)ar;
            s = ((void*(__thiscall*)(void*))rvt[0x1c / 4])(ar);
        }
        void* app2 = (void*)FUN_0067dd10();
        void** a2vt = *(void***)app2;
        u32 k = ((u32(__thiscall*)(void*))a2vt[0x38 / 4])(app2);
        if (k == 0x9ac9c2) {
            void* ts = mTextureType;
            void** tvt = *(void***)ts;
            ((void(__thiscall*)(void*, void*, int))tvt[0x9c / 4])(ts, s, 0);
            return 1;
        }
        void* ms = (void*)FUN_0067dcc0();
        void** mvt = *(void***)ms;
        ((void(__thiscall*)(void*, u32, void*, int))mvt[0x14 / 4])(ms, 0x1b537e5, p, 0);
        return 1;
    }
    switch (id) {
    case 0x1216ec2:
        Refresh();
        return 1;
    case 0x1216ec4:
        if (mTextureType)
            *(void**)((char*)mTextureType + 0x1cc) = *(void**)((char*)p + 8);
        return 1;
    default:
        break;
    }
    return 0;
}

// @ 0x00f69f50
bool cTerrainEditor_s00f6_9a30::ReadTile(int face, const int* rect, float elapsed)
{
    void* st = GetShaderTable_s00f6_9a30();
    u32 shader = *(u32*)(*(char**)((char*)st + 0x50) + 4);
    void* out;
    if (!mBatch->Alloc(&out, 0x18, 4, 0))
        return false;

    FUN_011e073e(out, 0, 0x60);

    RasterLike* raster = mHeightRasterArray[face];
    int w = raster->width;
    int h = raster->height;
    int depth = raster->depth;

    float wf = (float)w;
    float hf = (float)h;
    float zero = 0.0f;
    float n = -(zero / wf);
    float o = 1.0f - zero / wf;

    float* v = (float*)out;
    v[0] = n;
    v[1] = n;
    v[2] = zero;
    v[6] = o;
    v[7] = n;
    v[8] = zero;
    v[12] = n;
    v[13] = o;
    v[14] = zero;
    v[18] = o;
    v[19] = o;
    v[20] = zero;

    float u0 = (float)rect[0] / wf;
    float v0 = (float)rect[1] / hf;
    float u1 = (float)rect[2] / wf;
    float v1 = (float)rect[3] / hf;
    v[4] = u0;
    v[5] = v1;
    v[10] = u1;
    v[11] = v1;
    v[16] = u0;
    v[17] = v0;
    v[22] = u1;
    v[23] = v0;

    FUN_00777ae0(0x201, 0, 0);

    int idx = mTileIndex;
    Vec2 rs = mTileVec[idx];
    ((void(__thiscall*)(void*, int*, int))FUN_007c4be0)(mRTTCamera, (int*)&rs, 1);
    if (((char(__thiscall*)(void*))FUN_007c4fd0)(mRTTCamera)) {
        RasterStateStub state;
        ((void(__thiscall*)(void*, u32, int, RasterLike*))FUN_00fc2c10)(
            &state, shader, 0, raster);
        if (!mBatch->Apply(shader, elapsed)) {
            ((void(__thiscall*)(void*))FUN_00fc2830)(&state);
            return false;
        }
        mBatch->Flush();
        ((void(__thiscall*)(void*))FUN_007c3c10)(mRTTCamera);
        ((void(__thiscall*)(void*))FUN_00fc2830)(&state);
    }

    ((void(__thiscall*)(void*, void*, u32, int))FUN_011f0440)(
        mUploadRaster[idx], mTileRaster[idx], (u32)(depth >> 3) << 12, 0);

    ITerrainSphere* ts = (ITerrainSphere*)mTextureType;
    void* a = ((void*(__thiscall*)(void*))(*(void***)ts)[0xc / 4])((void*)ts);
    void* hd = *(void**)((char*)a + 8);
    int side = *(int*)((char*)hd + 8);
    u16* dst = (u16*)(*(int*)((char*)hd + 0x10) + side * side * face * 2);

    int row = 0;
    u32 off = 0;
    do {
        u32* src = (u32*)mTileRaster[mTileIndex];
        int x = 0;
        do {
            int y = rect[1] + row;
            if (rect[0] + x < w && y < h)
                dst[y * w + rect[0] + x] = (u16)(src[off + x] >> 8);
            if (rect[0] + x + 1 < w && y < h)
                dst[y * w + rect[0] + x + 1] = (u16)(src[off + x + 1] >> 8);
            if (rect[0] + x + 2 < w && y < h)
                dst[y * w + rect[0] + x + 2] = (u16)(src[off + x + 2] >> 8);
            if (rect[0] + x + 3 < w && y < h)
                dst[y * w + rect[0] + x + 3] = (u16)(src[off + x + 3] >> 8);
            x += 4;
        } while (x < 0x40);
        ++row;
        off += 0x40;
    } while (off < 0x1000);

    mTileIndex = 1 - mTileIndex;
    return true;
}

// @ 0x00f6a3a0
bool cTerrainEditor_s00f6_9a30::DrawBrushLayer(u32 param)
{
    if (!mTextureType)
        return false;
    ITerrainSphere* ts = (ITerrainSphere*)mTextureType;
    void* a = ((void*(__thiscall*)(void*))(*(void***)ts)[0xc / 4])((void*)ts);
    void* hd = *(void**)((char*)a + 8);
    int side = *(int*)((char*)hd + 8);

    for (int i = 0; i < 6; ++i) {
        if (!mGPUDirtyFace[i])
            continue;

        TempExtractTex* tex = (TempExtractTex*)mTempExtractTexture;
        int src = *(int*)((char*)hd + 0x10) + side * side * i * 2;
        if ((tex->flags & 1) == 0) {
            IResolver_s00f6_9a30* res = (IResolver_s00f6_9a30*)FUN_0067dd60_s00f6_9a30();
            res->Prepare(tex);
        }

        void* handle = tex->raster;
        u32 state[7];
        if (!((LockableRaster*)handle)->Lock(2, 0, state))
            return false;
        FUN_011e0744((void*)state[0], (void*)src, side * side * 2);
        ((LockableRaster*)handle)->Unlock(state);

        if (!DrawUnitQuad(i, (u32)handle, param))
            return false;

        if (i < 0) {
            mGPUDirtyFace[0] = 0;
            mGPUDirtyFace[1] = 0;
            mGPUDirtyFace[2] = 0;
            mGPUDirtyFace[3] = 0;
            mGPUDirtyFace[4] = 0;
            mGPUDirtyFace[5] = 0;
        } else {
            mGPUDirtyFace[i] = 0;
        }
    }
    return true;
}

// @ 0x00f6a4b0
void cTerrainEditor_s00f6_9a30::Construct()
{
    char* t = (char*)this;
    *(u32*)(t + 0x04) = 0x013f1ab0;
    *(u32*)(t + 0x00) = 0x0148f704;
    *(u32*)(t + 0x04) = 0x0148f6f4;
    *(u32*)(t + 0x08) = 0;
    *(u32*)(t + 0x0c) = 0;
    *(u32*)(t + 0x10) = 0;
    *(u32*)(t + 0x14) = 0;
    *(u32*)(t + 0x18) = 0;
    *(u32*)(t + 0x1c) = 0;
    *(u32*)(t + 0x38) = 0xffffffff;
    *(u32*)(t + 0x3c) = 0xffffffff;
    *(u32*)(t + 0x40) = 0xffffffff;
    *(u32*)(t + 0x44) = 0xffffffff;
    *(u32*)(t + 0x48) = 0xffffffff;
    *(u32*)(t + 0x4c) = 0xffffffff;
    *(u32*)(t + 0x50) = 0xffffffff;
    *(u32*)(t + 0x54) = 0xffffffff;
    *(u32*)(t + 0x58) = 0xffffffff;
    *(u32*)(t + 0x5c) = 0xffffffff;
    *(u32*)(t + 0x60) = 0xffffffff;
    *(u32*)(t + 0x64) = 0xffffffff;
    *(u32*)(t + 0x68) = 0;
    *(u32*)(t + 0x6c) = 0xffffffff;
    *(u32*)(t + 0x70) = 0xffffffff;
    *(u32*)(t + 0x74) = 0;
    *(u32*)(t + 0x168) = 0;
    *(u32*)(t + 0x16c) = 0;
    *(u32*)(t + 0x170) = 0;
    *(u32*)(t + 0x17c) = 0;
    *(u32*)(t + 0x180) = 0;
    *(u32*)(t + 0x184) = 0;
    *(u32*)(t + 0x188) = 0;
    *(u32*)(t + 0x18c) = 0;
    *(u32*)(t + 0x190) = 0;
    *(u32*)(t + 0x194) = 0;
    *(u32*)(t + 0x198) = 0;
    *(u32*)(t + 0x19c) = 0;
    *(u32*)(t + 0x1a0) = 0;
    *(u32*)(t + 0x1a4) = 0;
    *(u32*)(t + 0x1a8) = 0;
    *(u32*)(t + 0x1ac) = 0;
    *(u32*)(t + 0x1b0) = 0;
    *(u32*)(t + 0x1b4) = 0;
    *(u32*)(t + 0x1b8) = 0;
    *(u32*)(t + 0x1bc) = 0;
    *(u32*)(t + 0x1c0) = 0;
    *(u32*)(t + 0x1c4) = 0;
    *(u32*)(t + 0x1c8) = 0;
    *(u8*)(t + 0x1cc) = 0;
    *(u8*)(t + 0x1cd) = 0;
    *(u8*)(t + 0x1ce) = 0;
    *(u32*)(t + 0x200) = 0;
    *(u32*)(t + 0x204) = 0;
    *(u32*)(t + 0x208) = 0;
}

// @ 0x00f6a5d0
void cTerrainEditor_s00f6_9a30::Destroy()
{
    *(void**)((char*)this + 0) = (void*)0x0148f704;
    *(void**)((char*)this + 4) = (void*)0x0148f6f4;
    void* p = *(void**)((char*)this + 0x1c8);
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[1])(p);
    }
    ((cTerrainEditor_s00f6_9a30*)((char*)this + 0x1a4))->PairClear();
    ((cTerrainEditor_s00f6_9a30*)((char*)this + 0x180))->PairClear();
    {
        u32 r = *(u32*)((char*)this + 0x17c);
        if (r) {
            volatile long* c = (volatile long*)(r + 8);
            _InterlockedExchangeAdd(c, -1);
            if (_InterlockedExchangeAdd(c, 0) < 1)
                _InterlockedExchangeAdd(c, 1);
            else
                _InterlockedExchangeAdd(c, 0);
        }
    }
    {
        void* b = *(void**)((char*)this + 0x168);
        if (b) {
            if (*(int*)((char*)b - 4) != 0)
                operator_delete((char*)b);
        }
    }
    {
        void* s = *(void**)((char*)this + 0x74);
        if (s) {
            void** vt = *(void***)s;
            ((void(__thiscall*)(void*))vt[1])(s);
        }
    }
    {
        void* h = *(void**)((char*)this + 0x08);
        if (h) {
            u32 c = *(u32*)((char*)this + 0x0c);
            u32 d = *(u32*)((char*)this + 0x10);
            u32 e = *(u32*)((char*)this + 0x14);
            u32 f = *(u32*)((char*)this + 0x18);
            *(u32*)((char*)this + 0x08) = 0;
            RemoveHandler(h, c, d, e, f);
        }
    }
    *(void**)((char*)this + 0) = (void*)0x013eb394;
    *(void**)((char*)this + 4) = (void*)0x013eb938;
}

// @ 0x00f6a710
void cTerrainEditor_s00f6_9a30::SetBrushShaderData(void* p, int q)
{
    UpdateRange(p);
    void* out;
    if (*(u8*)((char*)q + 6)) {
        g_16c9898 |= 1;
        u8 m[0x10];
        *(u8*)((char*)m + 0x00) = 0;
        *(u8*)((char*)m + 0x01) = 0;
        float f;
        f = g_16c990c; *(float*)((char*)m + 0x00) = f;
        f = g_16c9910; *(float*)((char*)m + 0x04) = f;
        *(u8*)((char*)m + 0x02) = 0;
        *(u8*)((char*)m + 0x03) = 0;
        f = g_16c9914; *(float*)((char*)m + 0x08) = f;
        *(u8*)((char*)m + 0x0c) = 0;
        f = C_1485720; *(float*)((char*)m + 0x0c) = f;
        ((tfn1)Matrix3_Assign)((char*)m + 0x04, g_16c998c);
        float rx = *(float*)((char*)p + 0x20) * C_148f63c;
        ((tfnf)cXform_PreRotateX)(m, rx);
        float ry = *(float*)((char*)p + 0x24) * C_148f63c;
        ((tfnf)cXform_RotateY)(m, ry);
        float rz = *(float*)((char*)p + 0x28) * C_148f63c;
        ((tfnf)cTransform_PreRotateY)(m, rz);
        ((tfn1)Basis3_Build)(m, g_16c9858);
        out = g_16c9858;
    } else {
        out = 0;
    }
    FUN_00777ae0(0x241, out, 0);

    if (*(u8*)p) {
        g_16c9824[0] = *(float*)((char*)p + 4);
        g_16c9824[1] = *(float*)((char*)p + 0xc);
        g_16c9824[2] = *(float*)((char*)p + 0x1c);
        g_16c9824[3] = *(float*)((char*)p + 0x24);
        g_16c9824[4] = *(float*)((char*)p + 8);
        g_16c9824[5] = *(float*)((char*)p + 0x10);
        g_16c9824[6] = *(float*)((char*)p + 0x18);
        g_16c9824[7] = *(float*)((char*)p + 0x20);
        g_16c9824[8] = *(float*)((char*)p + 0x14);
        g_16c9824[9] = *(float*)((char*)p + 0x28);
        g_16c9824[10] = 0.001953125f;
        out = g_16c9824;
    } else {
        out = 0;
    }
    FUN_00777ae0(0x23c, out, 0);
}

// @ 0x00f6a960
bool Compositor::Draw(Source* src, const uint32_t* raster, int a3, Rect r, float v0, float v1, float v2, int a11, void* a12)
{
    DrawData* d = src->GetData();
    if (!d)
        return false;

    Vec4 v;
    v.x = v0;
    v.y = v1;
    v.z = 1.0f / (v2 - v0);
    v.w = 0.0f;
    int vx, vy, vw, vh;
    GetViewportInfo()->Query(raster[0], raster[1], &vx, &vy, &vw, &vh);

    uint32_t shader = GetShaderTable()->s34->id;
    static Vec4 cb0[4];
    cb0[0] = d->c44c;
    cb0[1] = d->c43c;
    cb0[2] = v;
    cb0[2].w = 0.5f / (float)vw;
    cb0[3] = Vec4(0.0f, -1.0f, 1.0f, 1.0f);

    void* out = 0;
    if (!mBatch->Alloc(&out, 0x18, 4, 0))
        return false;
    SetShaderConst(0x242, cb0, 0);
    SetShaderConst(0x201, 0, 0);
    memset(out, 0, 0x60);
    *(Vec3*)out = Vec3(r.x0, 1.0f - r.y1, 1.0f);
    *(Vec3*)((char*)out + 0x18) = Vec3(r.x1, 1.0f - r.y1, 1.0f);
    *(Vec3*)((char*)out + 0x30) = Vec3(r.x0, 1.0f - r.y0, 1.0f);
    *(Vec3*)((char*)out + 0x48) = Vec3(r.x1, 1.0f - r.y0, 1.0f);
    mViewer->SetRaster(raster, 1);
    if (mViewer->Update()) {
        Binding b0(shader, 0, src->TexC(a3));
        Binding b1(shader, 1, ResolveHandle(d->h328));
        if (!mBatch->Apply(shader, a12))
            return false;
        mViewer->Finish();
    }
    SetShaderConst(0x242, 0, 0);

    {
        shader = GetShaderTable()->s38->id;
        static Vec4 cb1;
        {
            Vec4 tmp;
            cb1 = *d->Query1(&tmp);
        }
        SetShaderConst(0x242, cb0, 0);
        SetShaderConst(0x250, &cb1, 0);
        mViewer->SetRaster(raster, 1);
        if (mViewer->Update()) {
            Binding b0(shader, 0, src->TexA(a3));
            Binding b1(shader, 1, ResolveHandle(d->h31c));
            if (!mBatch->Apply(shader, a12))
                return false;
            mViewer->Finish();
        }
        SetShaderConst(0x242, 0, 0);
        SetShaderConst(0x250, 0, 0);
    }

    {
        shader = GetShaderTable()->s3c->id;
        static Vec4 cb2;
        {
            Vec4 tmp;
            cb2 = *d->Query2(&tmp);
        }
        SetShaderConst(0x242, cb0, 0);
        SetShaderConst(0x251, &cb2, 0);
        mViewer->SetRaster(raster, 1);
        if (mViewer->Update()) {
            Binding b0(shader, 0, src->TexB(a3));
            Binding b1(shader, 1, src->TexA(a3));
            Binding b2(shader, 2, ResolveHandle(d->h320));
            if (!mBatch->Apply(shader, a12))
                return false;
            mBatch->Flush();
            mViewer->Finish();
        }
        SetShaderConst(0x242, 0, 0);
        SetShaderConst(0x251, 0, 0);
    }
    return true;
}

// @ 0x00f6b000
ImgDesc::ImgDesc(const ImgDesc& o)
{
    mpRes = o.mpRes;
    if (mpRes != 0)
        _InterlockedIncrement((volatile long*)(mpRes + 8));
    m04 = o.m04;
    m05 = o.m05;
    m06 = o.m06;
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    m18 = o.m18;
    m1c = o.m1c;
    m20 = o.m20;
    m24 = o.m24;
    m28 = o.m28;
    m2c = o.m2c;
    m30 = o.m30;
    m34 = o.m34;
    m38 = o.m38;
    m3c = o.m3c;
    m40 = o.m40;
    m44 = o.m44;
    m48 = o.m48;
    m4c = o.m4c;
    m50 = o.m50;
    m54 = o.m54;
    m58 = o.m58;
    m5c = o.m5c;
    m60 = o.m60;
    m64 = o.m64;
    m68 = o.m68;
    m6c = o.m6c;
    m70 = o.m70;
    m74 = o.m74;
}

// @ 0x00f6b0e0
TexDesc** CopyTexRange(TexDesc** out, TexDesc* first, TexDesc* last, TexDesc* dst, const void* owner)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0)
                new (dst) TexDesc(*first);
            first = (TexDesc*)((char*)first + sizeof(TexDesc));
            dst   = (TexDesc*)((char*)dst   + sizeof(TexDesc));
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x00f6b2d0
void QuadSource::Release()
{
    TexDesc* tex = mTex1d4.mpBegin;
    if (tex != 0 && *(int*)((char*)tex - 4) != 0)
        operator_delete(tex);
    char* res = mDesc80.mpRes;
    if (res != 0)
        RefRelease((int*)(res + 8));
}

// @ 0x00f6b330
ImgDesc& ImgDesc::Assign(const char* rec)
{
    const ImgDescRaw* r = (const ImgDescRaw*)rec;
    ImgDescRaw* d = (ImgDescRaw*)this;
    GetImageResource((void*)r->mHandle);
    d->m04 = r->m04;
    d->m05 = r->m05;
    d->m06 = r->m06;
    d->m08 = r->m08;
    d->m0c = r->m0c;
    d->m10 = r->m10;
    d->m14 = r->m14;
    d->m18 = r->m18;
    d->m1c = r->m1c;
    d->m20 = r->m20;
    d->m24 = r->m24;
    d->m28 = r->m28;
    d->m2c = r->m2c;
    d->m30 = r->m30;
    d->m34 = r->m34;
    d->m38 = r->m38;
    d->m3c = r->m3c;
    d->m40 = r->m40;
    d->m44 = r->m44;
    d->m48 = r->m48;
    d->m4c = r->m4c;
    d->m50 = r->m50;
    d->m54 = r->m54;
    d->m58 = r->m58;
    d->m5c = r->m5c;
    d->m60 = r->m60;
    d->m64 = r->m64;
    d->m68 = r->m68;
    d->m6c = r->m6c;
    d->m70 = r->m70;
    d->m74 = r->m74;
    return *this;
}

// @ 0x00f6b4b0
TexVector::TexVector(const TexVector& o)
{
    int count = (int)((char*)o.mpCur - (char*)o.mpBegin) / 0x1c4;
    TexDesc* mem;
    if (count != 0)
        mem = (TexDesc*)operator_new(count * 0x1c4, kAllocFile, 0, 0, kAllocFile2, 0xd1);
    else
        mem = 0;
    mpBegin = mem;
    mpCur = mem;
    mpEnd = (TexDesc*)((char*)mem + count * 0x1c4);
    TexDesc* newCur;
    const TexVector* owner = &o;
    CopyTexRange(&newCur, o.mpBegin, o.mpCur, mpBegin, owner);
    mpCur = newCur;
}

// @ 0x00f6b670
QuadSource& QuadSource::CopyFrom(const QuadSource& o)
{
    memcpy(this, &o, 0x7c);
    m7c = o.m7c;
    ImgDesc* pd = new (&mDesc80) ImgDesc(o.mDesc80);
    __assume(pd != 0);
    mf8 = o.mf8;
    mfc = o.mfc;
    m100 = o.m100;
    m104 = o.m104;
    m108 = o.m108;
    m10c = o.m10c;
    VectorCopy(mVec110, o.mVec110, 0xc, 0x10, (void*)kVec3Ctor);
    m1d0 = o.m1d0;
    TexVector* pt = new (&mTex1d4) TexVector(o.mTex1d4);
    __assume(pt != 0);
    return *this;
}

// @ 0x00f6b7c0
void QuadNode::FreeAll()
{
    QuadNode* next = mpNext;
    while (next != this) {
        QuadNode* it = next;
        next = it->mpNext;
        void* res = it->mpRes1dc;
        if (res != 0 && *(int*)((char*)res - 4) != 0)
            operator_delete(res);
        void* cnt = it->mpRef88;
        if (cnt != 0)
            RefRelease((int*)((char*)cnt + 8));
        operator_delete(it);
    }
}

// @ 0x00f6bc10
namespace TE {
void cTerrainEditor::ResetEditor()
{
    if (mpSphere != 0)
    {
        mpSphere->OnEnter();
        if (!mpSphere->IsReady())
            mpSphere->Reset();
    }
    g_gateList.Reset();
    g_gateList.mpNext = &g_gateList;
    g_gateList.mpPrev = &g_gateList;
    for (int i = 0; i < 6; i++)
        ClearRect(mRectsE0[i]);
}
}  // namespace TE

// @ 0x00f6bd20
namespace TE {
void ListHead::PushFront(const void* arg)
{
    ListNode* node = (ListNode*)operator_new(0x1f0, "Simulator", 0, 0,
                                             "eastl/allocator.h", 0xd1);
    struct NodePayload { char pad[8]; TilePayload mPayload; };
    if (&node->mPayload != 0)
        ((TilePayload*)&node->mPayload)->Construct(arg);

    node->mpNext = (ListNode*)this;
    node->mpPrev = this->mpTail;
    this->mpTail->mpNext = node;
    this->mpTail = node;
}
}  // namespace TE

// @ 0x00f6bd70
namespace TE {
bool cTerrainEditor::UpdateCPUFromGPU(float elapsed)
{
    cTerrainSphere* sphere = mpSphere;
    if (sphere == 0 || g_gate != (void*)&g_gate)
        return false;

    const float eps = 0.001953125f;
    bool dirty = false;
    for (int i = 0; i < 5; i++) {
        Rect_s00f6_b9a0& r = mDirty[i];
        if (r.l != r.r && r.t != r.b) {
            _ReadWriteBarrier();
            if (r.Width() < eps || r.Height() < eps)
                ClearRect(r);
            else
                dirty = true;
        }
    }
    {
        Rect_s00f6_b9a0& r = mDirty[5];
        if (r.l != r.r && r.t != r.b) {
            _ReadWriteBarrier();
            if (r.Width() < eps || r.Height() < eps)
                ClearRect(r);
            else
                goto relevel;
        }
    }
    if (!dirty)
        return true;
relevel:
    sphere->Relevel(elapsed, 0);

    {
        Raster* raster = mHeightRaster[0];
        const uint32_t width = raster->width;
        const uint32_t height = raster->height;
        const uint32_t bytesPerPixel = raster->depth >> 3;
        HeightData* heights = mpSphere->GetHeightMap()->mpData;
        bool anyUpdated = false;
        uint16_t* minMax = &mMinMax[0][0];

        for (int face = 0; face < 6; face++, minMax += 2) {
            Rect_s00f6_b9a0& r = mDirty[face];
            if (r.l != r.r && r.t != r.b) {
                static float sFullFraction = kMinTileFraction;
                uint16_t mn = 0xffff;
                uint16_t mx = 0;
                uint16_t* src = heights->mSamples + heights->mSide * heights->mSide * face;
                _ReadWriteBarrier();
                const bool wFull = r.Width() >= sFullFraction;
                _ReadWriteBarrier();
                const bool hFull = r.Height() >= sFullFraction;
                if (wFull || hFull) {
                    // large dirty area: read the whole face back
                    const uint32_t count = height * width;
                    mTemp.resize(count);
                    uint32_t* buf = mTemp.mpBegin;
                    mHeightRaster[face]->ReadPixels(buf, bytesPerPixel * height * width, 0);
                    anyUpdated = true;
                    uint16_t* dst = src;
                    for (uint32_t i = 0; i < count; i++) {
                        const uint16_t v = (uint16_t)(buf[i] >> 8);
                        dst[i] = v;
                        if (v < mn) mn = v;
                        if (mx < v) mx = v;
                    }
                } else {
                    // small dirty area: read it back in 64x64 tiles
                    const float fh = (float)height;
                    const float fw = (float)width;
                    const int row1 = (int)(r.b * fh);
                    const int col1 = (int)(r.r * fw);
                    const int row0 = (int)(r.t * fh);
                    const int col0 = (int)(r.l * fw);
                    const int nrows = (((uint32_t)(row1 - row0) - 1) >> 6) + 1;
                    const int ncols = (((uint32_t)(col1 - col0) - 1) >> 6) + 1;
                    int y = row0;
                    for (int rb = 0; rb < nrows; rb++, y += 0x40) {
                        int x = col0;
                        for (int cb = 0; cb < ncols; cb++, x += 0x40) {
                            int tile[4];
                            tile[0] = x;
                            tile[1] = y;
                            tile[2] = x + 0x40;
                            tile[3] = y + 0x40;
                            if (!ReadTile(face, tile, elapsed))
                                return false;
                        }
                    }
                    anyUpdated = true;
                    const uint32_t count = height * width;
                    for (uint32_t i = 0; i < count; i++) {
                        const uint16_t v = src[i];
                        if (v < mn) mn = v;
                        if (mx < v) mx = v;
                    }
                }
                minMax[0] = mn;
                minMax[1] = mx;
                mpSphere->MarkFaceDirty(face, &r);
                mpSphere->Notify(1);
            }
        }

        for (int i = 0; i < 6; i++)
            ClearRect(mDirty[i]);

        if (anyUpdated) {
            uint16_t lo = 0xffff;
            uint16_t hi = 0;
            lo = Min_s00f6_b9a0(lo, mMinMax[0][0]); hi = Max(hi, mMinMax[0][1]);
            lo = Min_s00f6_b9a0(lo, mMinMax[1][0]); hi = Max(hi, mMinMax[1][1]);
            lo = Min_s00f6_b9a0(lo, mMinMax[2][0]); hi = Max(hi, mMinMax[2][1]);
            lo = Min_s00f6_b9a0(lo, mMinMax[3][0]); hi = Max(hi, mMinMax[3][1]);
            lo = Min_s00f6_b9a0(lo, mMinMax[4][0]); hi = Max(hi, mMinMax[4][1]);
            lo = Min_s00f6_b9a0(lo, mMinMax[5][0]); hi = Max(hi, mMinMax[5][1]);
            MinMax range;
            range.mn = (float)((int)lo - 0x8000) * kHeightUnit;
            range.mx = (float)((int)hi - 0x8000) * kHeightUnit;
            mpSphere->GetHeightMap()->SetRange(&range);
        }
        mpSphere->GetHeightMap()->mpData->mVersion++;
        MessageServer()->Post(0x44448ed, 0, 0);
    }
    return true;
}
}  // namespace TE

// @ 0x00f6e120
void BrushCubeSplitter::SplitPolysToCubeFaces(int arg, BrushTarget* target, int numPolys, const SP::cRibbonBrushPoly_s00f6_df40* polys, int extra)
{
    target->mWidth = 0x200;
    target->mHeight = 0x200;
    target->mDepth = 0x200;

    PolyVector faces[6];
    AABox bounds[6];
    memset(bounds, 0, sizeof(bounds));

    SP::cRibbonBrushPoly_s00f6_df40 out;
    SP::cBrushVertex_s00f6_df40 verts[16];
    for (int p = 0; p < numPolys; p++, polys++) {
        for (int face = 0; face < 6; face++) {
            int numVerts = polys->mNumVertices;
            for (int k = 0; k < numVerts; k++)
                verts[k] = polys->mVertices[k];
            int plane;
            for (plane = 0; plane < 4; plane++) {
                if (numVerts == 0)
                    break;
                ClipPolyToPlane(verts, &numVerts, &gCubeFaceClipPlanes[face][plane]);
            }
            if (numVerts == 0)
                continue;

            out.mNumVertices = numVerts;
            const uint8_t* axes = gCubeFaceAxes[face >> 1];
            float sign = (face & 1) ? -1.0f : 1.0f;
            float signs[3];
            signs[0] = sign;
            signs[1] = 1.0f;
            signs[2] = sign;
            int i0 = axes[0], i1 = axes[1], i2 = axes[2];
            float s0 = signs[i0];
            float s1 = signs[i1];
            float s2 = signs[i2];
            for (int v = 0; v < numVerts; v++) {
                const SP::cBrushVertex_s00f6_df40& src = verts[v];
                float tmp[3];
                tmp[i0] = src.mPosition.x * s0;
                tmp[i1] = s1 * src.mPosition.y;
                tmp[i2] = src.mPosition.z * s2;
                float inv = 1.0f / tmp[2];
                float u = (tmp[0] * inv + 1.0f) * 0.5f;
                float w = (tmp[1] * inv + 1.0f) * 0.5f;
                bounds[face].Extend(cSPVector3_s00f6_df40(u, w, 0.0f));
                SP::cBrushVertex_s00f6_df40& dst = out.mVertices[v];
                dst.mPosition = cSPVector3_s00f6_df40((float)target->mWidth * u, (float)target->mHeight * w, 0.0f);
                dst.mUV = src.mUV;
                dst.mIntensity = src.mIntensity;
            }
            faces[face].push_back(out);
        }
    }

    for (int face = 0; face < 6; face++) {
        if (!faces[face].empty()) {
            const AABox& b = bounds[face];
            Rect_s00f6_df40 r(b.mMin.x, b.mMin.y, b.mMax.x, b.mMax.y);
            RenderFace(&faces[face], face, target, arg, &r, true, extra);
        }
    }
}
