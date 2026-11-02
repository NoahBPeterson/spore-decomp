// src/game/SPTerrain/SPTerrainStateMgr.cpp -- migrated from slice(s) s00fc03c0, s00fbe7d0, s00fbce30, s00fba330 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainStateMgr.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainStateMgr.h"
#include "EA/Variant.h"
#include "cSPVector3.h"
#include "SP/cPropertyList.h"
#include "SP/cPlanet.h"
#include "SP/cTerrainSphere.h"
#include <math.h>
#include <string.h>
#include "SP/cPropertyManager.h"
#include "SP/cTerrainMapSet.h"
#include "SP/cTextureInstance.h"

// ---- items of slice s00fba330 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
struct ResourceKey {
    uint32_t instance, type, group;
};
struct IResMan {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool GetResource(const ResourceKey* key, IRef** out, int, int, int, int);   // 0x0c
};
struct IImageSrc {   // object returned by FUN_0067dd60
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual IRef* GetImage(uint32_t id, int, int);   // 0x20
};
struct AutoRef {
    IRef* p;
    AutoRef& operator=(IRef* n) {
        IRef* old = p;
        if (n != old) {
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
        return *this;
    }
};
struct AtomicRef {
    IRef* p;
    void Assign(IRef* n);   // 0x576650
};
IImageSrc* GetImageSrc();   // 0x67dd60
IResMan* GetManager();      // 0x67dcd0
inline ResourceKey MakeKey(uint32_t a, uint32_t b, uint32_t c) {
    ResourceKey k; k.instance = a; k.type = b; k.group = c; return k;
}
static inline void SetB(AutoRef& g, IRef* n) {
    if (n != g.p) {
        IRef* old = g.p;
        if (n) n->AddRef();
        g.p = n;
        if (old) old->Release();
    }
}
struct TmpRef {
    IRef* p;
    void Reset() {
        if (p) { IRef* t = p; p = 0; t->Release(); }
    }
};
extern AutoRef g16d6ab8, g16d6ab4, g16d6abc, g16d6ac0, g16d6ac4, g16d6ac8;
extern AtomicRef g16d6aa8, g16d6aa0, g16d6a78, g16d6a7c, g16d6a80, g16d6a8c, g16d6a90, g16d6a94,
    g16d6a98, g16d6a9c, g16d6a84, g16d6a88, g16d6aa4;
extern AutoRef g16d6ab0, g16d698c, g16d6990, g16d6994, g16d6998, g16d6974, g16d6acc;
extern AutoRef g16d6d30[16], g16d6d70[16];
// ---- items of slice s00fba330 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00fbce30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_renderDevice;                 // 0x015b1600
extern void* FUN_0067dd60();                 // 0x0067dd60 scene render manager
extern void* FUN_0067ddd0();                 // 0x0067ddd0 effects manager
struct ImageRef {
  void* mpResource;
  void __thiscall GetImageResource(void* resource);   // 0x00576650 (ref-counted reassign)
};
struct RefCounted {
  virtual int AddRef();
  virtual int Release();
};
template <class T>
struct RefPtr {
  T* mpObject;
  RefPtr& operator=(T* p) {
    T* old = mpObject;
    if (p != old) {
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  RefPtr& operator=(const RefPtr& o) {
    T* p = o.mpObject;
    T* old = mpObject;
    if (p != old) {
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
};
struct Quad {
  uint32_t a, b, c, d;
};
struct Mat16 {
  uint32_t m[16];
};
struct RenderState {
  ImageRef images[14];            // +0x00
  RefPtr<RefCounted> refs[8];     // +0x38
  uint32_t w058, w05c, w060, w064, w068, w06c, w070, w074;
  uint32_t w078, w07c, w080, w084, w088, w08c, w090, w094;
  uint32_t w098, w09c, w0a0, w0a4, w0a8, w0ac, w0b0, w0b4;
  uint32_t w0b8, w0bc, w0c0, w0c4, w0c8, w0cc, w0d0, w0d4;
  uint32_t w0d8, w0dc, w0e0, w0e4, w0e8, w0ec, w0f0, w0f4;
  uint32_t w0f8, w0fc, w100, w104, w108, w10c, w110, w114;
  uint32_t w118, w11c, w120, w124, w128, w12c, w130, w134;
  uint32_t w138, w13c, w140, w144, w148, w14c, w150, w154;
  uint32_t w158, w15c, w160, w164, w168, w16c, w170, w174;
  uint32_t w178, w17c, w180, w184;
  Mat16 matrix;            // +0x188
  uint32_t w1c8, w1cc, w1d0, w1d4, w1d8, w1dc, w1e0, w1e4;
  uint32_t w1e8, w1ec, w1f0, w1f4, w1f8, w1fc, w200, w204;
  uint32_t w208, w20c, w210, w214, w218, w21c, w220, w224;
  uint32_t w228, w22c, w230, w234, w238, w23c, w240, w244;
  uint32_t w248, w24c, w250, w254, w258, w25c, w260, w264;
  uint32_t w268, w26c, w270, w274, w278, w27c, w280, w284;
  uint32_t w288, w28c, w290, w294, w298, w29c, w2a0, w2a4;
  Quad tail;                      // +0x2a8
  void ReleaseImages();           // 0x00fb9fc0 (drops the 14 image references)
  RenderState& operator=(const RenderState& o);
};
typedef long double float10;                 // x87 wide float: returned in ST(0)
struct Vec3 {
  float x, y, z;
};
struct cPlanetGame {
  void Dirty();                              // 0x00fb8a10
};
struct cTerrainSphere {
  void Relevel(int, int);                    // 0x00fa43e0, ret 8
};
struct cHeightField {
  void SetValueTable(float);                 // 0x00ff03c0, ret 4
};
struct EffectTarget {
  char pad_000[0xf4];
  Vec3 pos;                                  // +0xf4 effect position
};
extern RefCounted* g_terrainLayers[];        // 0x016d6d30 terrain layer table
extern RefCounted* g_terrainRefA;            // 0x016d6990
extern RefCounted* g_terrainRefB;            // 0x016d6994
extern RefCounted* g_terrainRefC;            // 0x016d6998
extern RefCounted* g_terrainRefD;            // 0x016d6974
extern RenderState g_terrainPreset;          // 0x016d6a78 render-state preset
extern Vec3* FUN_00fb8fc0(Vec3* out, float a, float b, float c, float d, float e); // 0x00fb8fc0
extern float10 FUN_00fc2ab0(void* scatter);  // 0x00fc2ab0 terrain scatter, x87 float
struct cPlanetState {
  float m_008, m_00c;                        // +0x008 sector origin
  char pad_010[0x008];
  float m_018;                               // +0x018 current height
  char pad_01c[0x010];
  float m_02c;                               // +0x02c view height
  char pad_030[0x004];
  float m_034, m_038, m_03c;                 // +0x034 effect position
  char pad_040[0x048];
  float m_088, m_08c, m_090;                 // +0x088 LOD thresholds
  char pad_094[0x160];
  RefPtr<RefCounted> ref_1f4;                // +0x1f4
  char pad_1f8[0x014];
  RefPtr<RefCounted> ref_20c;                // +0x20c terrain layers
  RefPtr<RefCounted> ref_210;                // +0x210
  RefPtr<RefCounted> ref_214;                // +0x214
  RefPtr<RefCounted> ref_218;                // +0x218
  char pad_21c[0x048];
  unsigned char m_264;                       // +0x264 ramps enabled
  char pad_265[0x003];
  Vec3 ptA;                                  // +0x268 point A
  Vec3 ptB;                                  // +0x274 point B
  char pad_280[0x044];
  float m_2c4, m_2c8;                        // +0x2c4 point A parameters
  char pad_2cc[0x010];
  float m_2dc, m_2e0;                        // +0x2dc point B parameters
  void DestroySubObjects();                  // 0x00fbcd80
};
struct cPlanet {
  cPlanetGame* mpGame;                       // +0x000
  cHeightField* mpHeightField;               // +0x004
  cPlanetState state;                        // +0x008
  char pad_2e4[0x010];
  RenderState renderState;                   // +0x2f4
  char pad_5ac[0x004];
  RefPtr<RefCounted> ref_5b0;                // +0x5b0
  char pad_5b4[0x004];
  RefPtr<RefCounted> ref_5b8;                // +0x5b8
  char pad_5bc[0x004];
  int m_5c0;                                 // +0x5c0 terrain layer index
  char pad_5c4[0x034];
  RefPtr<RefCounted> ref_5f8;                // +0x5f8
  RefPtr<RefCounted> ref_5fc;                // +0x5fc
  char pad_600[0x028];
  float heights[101];                        // +0x628 sorted height breakpoints
  unsigned char m_7bc;                       // +0x7bc height histogram valid

  void ReleaseAuxObjects();                  // 0x00fbd650
  void SetRampEnabled(bool enabled);         // 0x00fbd6b0
  void SetPointA(float x, float y, float z); // 0x00fbd6e0
  void SetPointB(float x, float y, float z); // 0x00fbd7b0
  void SetExtent(float u, float v);          // 0x00fbd880
  __declspec(noinline) float10 HeightToRatio(float height); // 0x00fbd8b0
  __declspec(noinline) float10 RatioToHeight(float ratio);  // 0x00fbd9d0
  float10 CurrentRatio();                    // 0x00fbda80
  void ApplyHeightRatio(float ratio);        // 0x00fbdaa0
  void ResetRenderState();                   // 0x00fbdb10
  void UpdateEffects();                      // 0x00fbdc60
  void BuildHeightHistogram();               // 0x00fbb1a0
  void ExportRampTexture();                  // 0x00fbbc00
};
// ---- items of slice s00fbce30 end

// ---- items of slice s00fbe7d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gTerrainVector3ArrayIDs[4];   // 0x014911c0
extern const float g_16d6710;                  // 0x016d6710  base sample point
extern const float g_16d6714;                  // 0x016d6714
extern const float g_16d6718;                  // 0x016d6718
extern const float g_1432214;                  // 0x01432214  1/31
extern const float g_1471064;                  // 0x01471064
extern const float g_1485720;                  // 0x01485720  _HK_REAL_ONE
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct Property {
    uint32_t pad00[4];
    uint16_t pad10;
    uint16_t mnType;
    float* GetFloat();                        // 0x0041ea70
};
struct cPropertyList {
    virtual void AddRef();
    virtual void Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};
bool GetPropertyAsVector2(cPropertyList* list, uint32_t id, Vector2* out);                          // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList* list, uint32_t id, Vector3* out);                          // 0x006a1110
bool GetPropertyAsVector4(cPropertyList* list, uint32_t id, Vector4* out);                          // 0x006a1160
bool GetPropertyArrayVector2(cPropertyList* list, uint32_t id, int* count, Vector2** data);         // 0x006a0920
bool GetPropertyArrayVector3(cPropertyList* list, uint32_t id, int* count, Vector3** data);         // 0x006a0990
template <class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};
struct AssignTag { AssignTag() {} };   // eastl tag type with a user constructor (nothing is stored)
struct Vector3Array {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator[2];
    void DoAssign(Vector3* first, Vector3* last, AssignTag tag);   // 0x0056fee0
    void assign(Vector3* first, Vector3* last) { DoAssign(first, last, AssignTag()); }
};
struct Vector2Array {
    Vector2* mpBegin;
    Vector2* mpEnd;
    Vector2* mpCapacity;
    uint32_t mAllocator[2];
    void DoAssign(Vector2* first, Vector2* last, AssignTag tag);   // 0x00fbdf80
    void assign(Vector2* first, Vector2* last) { DoAssign(first, last, AssignTag()); }
};
struct FloatVector {
    float* mpBegin;                            // +0x00
    float* mpEnd;                              // +0x04
    float* mpCapacity;                         // +0x08
    uint32_t mAllocator[2];                    // +0x0c
    void VectorPushBack(const float* value);   // 0x00455660
    void erase(float* first, float* last);     // 0x0050f740
    void Resize(int count, uint32_t* alloc);   // 0x004aa350
    void operator=(const FloatVector& src);    // 0x0050d4e0
};
struct Vector3Vector {
    Vector3* mpBegin;                          // +0x00
    Vector3* mpEnd;                            // +0x04
    Vector3* mpCapacity;                       // +0x08
    uint32_t mAllocator[2];                    // +0x0c
    void DoInsertValue(Vector3* pos, const Vector3* value);   // 0x004b5ad0
    void erase(Vector3* first, Vector3* last);                 // 0x0050f740
    void operator=(const Vector3Vector& src);                 // 0x00473500
};
class cTerrainStateMgr {
public:
    uint32_t pad000[0xb4 / 4];
    Vector4 m0b4;                  // +0x0b4
    uint32_t pad0c4;
    Vector3 m0c8;                  // +0x0c8
    Vector3 m0d4;                  // +0x0d4
    Vector3 m0e0;                  // +0x0e0
    Vector3 m0ec;                  // +0x0ec
    Vector3 m0f8;                  // +0x0f8
    Vector3 m104;                  // +0x104
    Vector4 m110;                  // +0x110
    float m120;                    // +0x120
    float m124;                    // +0x124
    Vector2Array m128;             // +0x128
    Vector2 m13c;                  // +0x13c
    float m144;                    // +0x144
    float m148;                    // +0x148
    float m14c;                    // +0x14c
    float m150;                    // +0x150
    float m154;                    // +0x154
    Vector3Array m158[4];          // +0x158
    Vector2Array m1a8;             // +0x1a8
    Vector3Array m1bc;             // +0x1bc
    Vector2Array m1d0;             // +0x1d0
    uint32_t pad1e4;
    float m1e8;                    // +0x1e8
    float m1ec;                    // +0x1ec
    float m1f0;                    // +0x1f0
    uint32_t pad1f4;
    float m1f8;                    // +0x1f8
    float m1fc;                    // +0x1fc
    float m200;                    // +0x200
    float m204;                    // +0x204
    float m208;                    // +0x208
    uint32_t pad20c[4];
    Vector3 m21c;                  // +0x21c
    Vector3 m228;                  // +0x228
    Vector3 m234;                  // +0x234
    Vector3 m240;                  // +0x240
    Vector3 m24c;                  // +0x24c
    Vector3 m258;                  // +0x258
    uint8_t m264;                  // +0x264  ramp-dirty flag
    uint8_t pad265[3];
    float m268;                    // +0x268
    float m26c;                    // +0x26c
    float m270;                    // +0x270
    float m274;                    // +0x274
    float m278;                    // +0x278
    float m27c;                    // +0x27c
    float m280;                    // +0x280
    float m284;                    // +0x284
    float m288;                    // +0x288
    float m28c;                    // +0x28c
    float m290;                    // +0x290
    float m294;                    // +0x294
    FloatVector m298;              // +0x298
    Vector3Vector m2ac;            // +0x2ac
    uint32_t pad2c0[5];
    float m2d4;                    // +0x2d4
    uint32_t pad2d8[5];
    float m2ec;                    // +0x2ec
    float m2f0;                    // +0x2f0
    uint32_t pad2f4[(0x3cc - 0x2f4) / 4];
    float m3cc;                    // +0x3cc
    float m3d0;                    // +0x3d0
    float m3d4;                    // +0x3d4
    uint32_t pad3d8[(0x42c - 0x3d8) / 4];
    float m42c;                    // +0x42c
    float m430;                    // +0x430
    float m434;                    // +0x434
    uint32_t pad438[(0x5b0 - 0x438) / 4];
    AutoRefCount<cPropertyList> mpPlanetProps;   // +0x5b0

    void Initialize();
    void FUN_00fbee30();                         // 0x00fbee30
    void FUN_00fbf1c0(Vector3Vector* in, int unused);            // 0x00fbf1c0
    Vector3Vector* FUN_00fbf430(Vector3Vector* out, char build); // 0x00fbf430
    FloatVector* FUN_00fbf3d0(FloatVector* out); // 0x00fbf3d0
    void UpdateLightColors(float phase, bool flag);              // 0x00fbc770
    void ExportRampTextureEx();                                  // 0x00fbbc00
};
struct cRampOwner {
    uint32_t pad000[0x494 / 4];
    float m494; float m498; float m49c; float m4a0; float m4a4; float m4a8;
    float m4ac; float m4b0; float m4b4; float m4b8; float m4bc; float m4c0;
    float m4c4; float m4c8; float m4cc; float m4d0; float m4d4; float m4d8;
    float m4dc; float m4e0; float m4e4; float m4e8; float m4ec; float m4f0;
};
Vector3* FUN_00fb8dd0(cTerrainStateMgr* self, Vector3* out, float phase);  // 0x00fb8dd0
Vector3* FUN_00fb8fc0(Vector3* out, float x, float y, float z, float a, float b);  // 0x00fb8fc0
Vector3* FUN_00fb90b0(Vector3* out, float x, float y, float z, float a, float b);  // 0x00fb90b0
void FUN_00fb9ad0(Vector3* out);               // 0x00fb9ad0
void FUN_00fb9ca0(Vector3* out);               // 0x00fb9ca0
void FUN_00fb9500(int flag);                   // 0x00fb9500
inline void ReadFloat(cPropertyList* list, uint32_t id, float& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, &prop) && prop->mnType == 0xd)
        dst = *prop->GetFloat();
}
// ---- items of slice s00fbe7d0 end

// ---- items of slice s00fc03c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst
struct Vector2_s00fc_03c0 {
    float x, y;
    Vector2_s00fc_03c0() {}
    Vector2_s00fc_03c0(float ax, float ay) : x(ax), y(ay) {}
};
struct Vector3_s00fc_03c0 {
    float x, y, z;
    Vector3_s00fc_03c0() {}
    Vector3_s00fc_03c0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00fc_03c0(const Vector3_s00fc_03c0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vector4_s00fc_03c0 {
    float x, y, z, w;
    Vector4_s00fc_03c0() {}
    Vector4_s00fc_03c0(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
struct Matrix3 {
    float m[3][3];
    void Assign(const Matrix3& other);       // 0x41cb40
};
struct Matrix4 {
    float m[4][4];
    Matrix4()
    {
        m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f;
        m[0][0] = 1.0f; m[1][1] = 1.0f; m[2][2] = 1.0f; m[3][3] = 1.0f;
    }
};
extern const Vector3_s00fc_03c0 kVector3Zero;          // 0x16d6710
extern const Matrix3 kMatrix3Identity;      // 0x16d6db0
struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3_s00fc_03c0 mOffset;
    float mfScale;
    Matrix3 mRotation;

    Transform() : mnFlags(0), mnTransformCount(0), mOffset(kVector3Zero), mfScale(1.0f)
    {
        mRotation.Assign(kMatrix3Identity);
    }
    void SetRotationFromDirs(const Vector3_s00fc_03c0& dir, const Vector3_s00fc_03c0& up);   // 0x6bac90
    void ToMatrix4(Matrix4& out) const;                                 // 0x6b9440
};
struct Property_s00fc_03c0 {
    uint32_t pad0[4];
    uint16_t pad10; uint16_t mnType;          // +0x12
    float* GetFloat();                        // 0x41ea70
};
struct cPropertyList_s00fc_03c0 {
    virtual void AddRef();
    virtual void Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual bool GetProperty(uint32_t id, Property_s00fc_03c0** out);   // +0x24
};
struct cPropertyManager_s00fc_03c0 {
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
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList_s00fc_03c0** out);   // +0x2c
};
namespace SP {
 cPropertyManager_s00fc_03c0* PropertyManager();   // 0x67de30
}
bool GetPropertyAsVector2(cPropertyList_s00fc_03c0* list, uint32_t id, Vector2_s00fc_03c0* out);   // 0x6a10c0
template <class T> struct AutoRefCount_s00fc_03c0 {
    T* mpObject;
    AutoRefCount_s00fc_03c0& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** AsPointer()
    {
        *this = (T*)0;
        return &mpObject;
    }
};
struct cTerrainMapSet_s00fc_03c0 {
    uint32_t pad00[13];
    float mRadius;                // +0x34
    float mMaxHeight;             // +0x38
    float mWaterHeight;           // +0x3c
    uint32_t pad40[2];
    float mMinCliffGradient;      // +0x48
    float mMaxCliffGradient;      // +0x4c
    void SetWaterHeight(float h);                 // 0xff03c0
    void SetMaxHeight(float h);                   // 0xf924e0
    void SetCliffGradients(float lo, float hi);   // 0xf92500
};
struct cTextureInstance_s00fc_03c0 {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04[6];
    float m1c;                    // +0x1c
};
extern cTextureInstance_s00fc_03c0* g_pDefaultTerrainTexture;   // 0x16d6acc
struct cTerrainEditor {
    uint32_t pad000[0x1c8 / 4];
    cPropertyList_s00fc_03c0* mpLightingProps;   // +0x1c8
};
namespace SP {
 cTerrainEditor* TerrainEditor();   // 0xf48a70
}
bool __cdecl IsWorldFlagSet(int flag);              // 0x685520
struct IVisualEffect {
    virtual void AddRef();
    virtual void Release();
};
struct IEffectsManager {
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
    virtual IVisualEffect* GetEffect(uint32_t id);   // +0x54
};
namespace SP {
 IEffectsManager* EffectsManager();   // 0x67ddd0
}
struct VectorKey {                 // 12-byte elements, out-of-line erase
    Vector3_s00fc_03c0* mpBegin;
    Vector3_s00fc_03c0* mpEnd;
    Vector3_s00fc_03c0* mpCapacity;
    uint32_t mAllocator;
    Vector3_s00fc_03c0* erase(Vector3_s00fc_03c0* first, Vector3_s00fc_03c0* last);   // 0x50f740
    void clear() { erase(mpBegin, mpEnd); }
};
struct VectorU32 {                 // 4-byte elements, inline erase
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;
    uint32_t* erase(uint32_t* first, uint32_t* last)
    {
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct cTerrainStateMgr_s00fc_03c0 {
    uint32_t pad000;
    cTerrainMapSet_s00fc_03c0* mpMapSet;     // +0x004
    float m008;                   // +0x008
    float m00c;                   // +0x00c
    float m010;                   // +0x010
    float m014;                   // +0x014
    float m018;                   // +0x018
    float mMaxAltLow;             // +0x01c
    float mMaxAltMid;             // +0x020
    float mMaxAltHigh;            // +0x024
    float m028;                   // +0x028
    float mTimeOfDay;             // +0x02c
    float mLatitude;              // +0x030
    Vector3_s00fc_03c0 mSunDir;              // +0x034
    Matrix4 mSunMatrix;           // +0x040
    int m080;                     // +0x080
    Vector2_s00fc_03c0 mLightRange[6];       // +0x084
    Vector4_s00fc_03c0 m0b4;                 // +0x0b4
    uint32_t pad0c4;
    Vector3_s00fc_03c0 mColorA0;             // +0x0c8
    Vector3_s00fc_03c0 mColorB0;             // +0x0d4
    Vector3_s00fc_03c0 mColorA1;             // +0x0e0
    Vector3_s00fc_03c0 mColorB1;             // +0x0ec
    Vector3_s00fc_03c0 mColorA2;             // +0x0f8
    Vector3_s00fc_03c0 mColorB2;             // +0x104
    Vector4_s00fc_03c0 m110;                 // +0x110
    float m120, m124;             // +0x120
    uint32_t pad128[5];
    float m13c, m140, m144, m148; // +0x13c
    float m14c;                   // +0x14c
    float m150;                   // +0x150
    float m154;                   // +0x154
    uint32_t pad158[36];
    float m1e8;                   // +0x1e8
    float m1ec;                   // +0x1ec
    float m1f0;                   // +0x1f0
    uint32_t pad1f4;
    float m1f8;                   // +0x1f8
    float m1fc;                   // +0x1fc
    float m200;                   // +0x200
    float m204;                   // +0x204
    float m208;                   // +0x208
    uint32_t pad20c[4];
    Vector3_s00fc_03c0 m21c;                 // +0x21c
    Vector3_s00fc_03c0 m228;                 // +0x228
    Vector3_s00fc_03c0 m234;                 // +0x234
    Vector3_s00fc_03c0 m240;                 // +0x240
    Vector3_s00fc_03c0 m24c;                 // +0x24c
    Vector3_s00fc_03c0 m258;                 // +0x258
    bool m264;                    // +0x264
    uint8_t pad265[3];
    Vector3_s00fc_03c0 m268;                 // +0x268
    Vector3_s00fc_03c0 m274;                 // +0x274
    uint32_t pad280[6];
    VectorU32 mVec298;            // +0x298
    uint32_t pad2a8;
    VectorKey mVec2ac;            // +0x2ac
    uint32_t pad2bc;
    float m2c0[13];               // +0x2c0
    uint32_t pad2f4[21];
    AutoRefCount_s00fc_03c0<cTextureInstance_s00fc_03c0> mpTexture;   // +0x348
    uint32_t pad34c[64];
    float mAmbient;               // +0x44c
    float m450;                   // +0x450
    float mMinCliffGradient;      // +0x454
    float mMaxCliffGradient;      // +0x458
    uint32_t pad45c[40];
    Vector4_s00fc_03c0 m4fc;                 // +0x4fc
    uint32_t pad50c[41];
    AutoRefCount_s00fc_03c0<cPropertyList_s00fc_03c0> mpPlanetProps;   // +0x5b0
    uint32_t pad5b4;
    AutoRefCount_s00fc_03c0<cPropertyList_s00fc_03c0> mpTuningProps;   // +0x5b8
    uint32_t pad5bc[15];
    AutoRefCount_s00fc_03c0<IVisualEffect> mpEffect;        // +0x5f8

    void Initialize();                 // 0xfbe7d0
    void ApplyTuning();                // 0xfb8ae0
    void UpdateWater();                // 0xfbdb10
    float ComputeAmbient();            // 0xfb88d0
    void UpdateSeasonsNow();           // 0xfbbc00

    void Reset(bool updateNow);  // 0x00fc04b0 (cTerrainStateMgr::Reset)
};
// ---- items of slice s00fc03c0 end

// ---- items of slice s00fc03c0_state begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector2_s00fc_03c0__state { float x, y; };
template <class T>
struct eastl_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator0;
    uint32_t mAllocator1;
    eastl_vector& operator=(const eastl_vector& other);
};
typedef eastl_vector<Vector2_s00fc_03c0__state> Vector2Vector;
struct IRefCounted {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};
template <class T>
struct AutoRefCount_s00fc_03c0__state {
    T* mpObject;
    AutoRefCount_s00fc_03c0__state& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pOld = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};
struct TexturingParms {
    Vector2Vector mTable;           // +0x00
    float m134;                     // +0x14
    float m138;                     // +0x18
    TexturingParms& operator=(const TexturingParms& other)
    {
        mTable = other.mTable;
        m134 = other.m134;
        m138 = other.m138;
        return *this;
    }
};
struct PlanarDef {                  // 0xa0 bytes: five floats + seven vectors
    uint32_t mData[0xa0 / 4];
    PlanarDef& operator=(const PlanarDef& other);
};
struct TerrainRecord {              // 0x6c bytes
    uint32_t mData[0x6c / 4];
    void Assign(const TerrainRecord& other);
};
struct StateOutputParms {           // 0x90 bytes
    uint32_t mData[0x90 / 4];
    StateOutputParms& operator=(const StateOutputParms& other);
};
namespace SP {
struct cTerrainStateMgr_s00fc_03c0__state {
    struct cStateParms;
};
}
namespace SP {
struct cTerrainStateMgr_s00fc_03c0__state::cStateParms {
    struct PodBlock { uint32_t m[0x118 / 4]; };

    PodBlock mPlanetaryParms;       // +0x000 opaque value block
    uint32_t m118;                  // +0x118
    uint32_t m11c;                  // +0x11c
    TexturingParms mTexturingParms; // +0x120
    PlanarDef mTerrainParms;        // +0x13c
    float m1dc;                     // +0x1dc
    float m1e0;                     // +0x1e0
    float m1e4;                     // +0x1e4
    float m1e8;                     // +0x1e8
    AutoRefCount_s00fc_03c0__state<IRefCounted> m1ec; // +0x1ec
    TerrainRecord mScatterParms;    // +0x1f0
    StateOutputParms mOutputParms;  // +0x25c

    cStateParms* Reset();                                   // 0x00fbe050
    void DestroySubObjects();                               // 0x00fbcd80
    cStateParms& operator=(const cStateParms& other);
};
}
struct ImageRef_s00fc_03c0__state {
    void* mpResource;
};
template <class T>
struct RefPtr_s00fc_03c0__state {
    T* mpObject;
};
struct RenderState_s00fc_03c0__state {                // 0x2b8 bytes
    ImageRef_s00fc_03c0__state images[14];            // +0x000
    RefPtr_s00fc_03c0__state<IRefCounted> refs[8];    // +0x038
    uint32_t mScalars[(0x2b8 - 0x58) / 4];

    void ReleaseImages();                                   // 0x00fb9fc0
    RenderState_s00fc_03c0__state& operator=(const RenderState_s00fc_03c0__state& other);       // 0x00fbce30
};
extern SP::cTerrainStateMgr_s00fc_03c0__state::cStateParms gCoreState;   // 0x016d6788
extern RenderState_s00fc_03c0__state gRenderState;                       // 0x016d6a78
extern IRefCounted* gTerrainLayerTable[];              // 0x016d6d30, 16 entries
extern IRefCounted* gTerrainLayerTable2[];             // 0x016d6d70, 16 entries
// ---- items of slice s00fc03c0_state end

// @ 0x00fba330
void SP::cTerrainStateMgr::StaticInit()
{
    IImageSrc* src = GetImageSrc();
    TmpRef r;
    r.p = 0;
    ResourceKey key;
    key.instance = 0x2ec45f93; key.type = 0x3e421ed; key.group = 0;
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    SetB(g16d6ab8, r.p);
    key.instance = 0x362ac39e;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ab4 = r.p;
    key.instance = 0x7c6b9fd9;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6abc = r.p;
    key.instance = 0x88566056;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ac0 = r.p;
    key.instance = 0xf30d0a76;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ac4 = r.p;
    key.instance = 0xc71ef96a;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    SetB(g16d6ac8, r.p);

    g16d6aa8.Assign(src->GetImage(0xdef55713, 0, 0));
    g16d6aa0.Assign(src->GetImage(0x9d64f524, 0, 0));
    g16d6a78.Assign(src->GetImage(0x9d8d0398, 0, 0));
    g16d6a7c.Assign(src->GetImage(0x11b5ee6f, 0, 0));
    g16d6a80.Assign(src->GetImage(0x11b5ee6e, 0, 0));
    g16d6a8c.Assign(src->GetImage(0x08c05ad9, 0, 0));
    g16d6a90.Assign(src->GetImage(0xa3973ea2, 0, 0));
    g16d6a94.Assign(src->GetImage(0xa5ab24f5, 0, 0));
    g16d6a98.Assign(src->GetImage(0x3cef83d5, 0, 0));
    g16d6a9c.Assign(src->GetImage(0x3c9c0255, 0, 0));
    g16d6a84.Assign(src->GetImage(0x84613ac8, 0, 0));
    g16d6a88.Assign(src->GetImage(0xc66c3fcd, 0, 0));
    g16d6aa4.Assign(src->GetImage(0x3f05c913, 0, 0));

    key.instance = 0xc5d262e4; key.type = 0x3e421ec;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ab0 = r.p;
    key.instance = 0xe2e599a0; key.type = 0x3e421ed;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d698c = r.p;
    key.instance = 0xc74bc5b0;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6990 = r.p;
    key.instance = 0x9c751f5e;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6994 = r.p;
    key.instance = 0xd1830e14;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6998 = r.p;
    key.instance = 0x54633685;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6974 = r.p;

    for (uint32_t i = 0; i < 16; i++) {
        key.instance = 0x5359c50 + i;
        r.Reset();
        if (GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0))
            g16d6d30[i] = r.p;
        else
            g16d6d30[i] = g16d698c.p;
    }
    for (uint32_t i = 0; i < 16; i++) {
        key.instance = 0x536dd50 + i;
        r.Reset();
        if (GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0))
            g16d6d70[i] = r.p;
        else
            g16d6d70[i] = g16d6974.p;
    }

    key = MakeKey(0x1fa9ab84, 0x2cb4f2f, 0);
    IResMan* mgr = GetManager();
    r.Reset();
    if (mgr->GetResource(&key, &r.p, 0, 0, 0, 0))
        g16d6acc = r.p;
    if (r.p) r.p->Release();
}

// @ 0x00fbce30
RenderState& RenderState::operator=(const RenderState& o)
{
  images[0].GetImageResource(o.images[0].mpResource);
  images[1].GetImageResource(o.images[1].mpResource);
  images[2].GetImageResource(o.images[2].mpResource);
  images[3].GetImageResource(o.images[3].mpResource);
  images[4].GetImageResource(o.images[4].mpResource);
  images[5].GetImageResource(o.images[5].mpResource);
  images[6].GetImageResource(o.images[6].mpResource);
  images[7].GetImageResource(o.images[7].mpResource);
  images[8].GetImageResource(o.images[8].mpResource);
  images[9].GetImageResource(o.images[9].mpResource);
  images[10].GetImageResource(o.images[10].mpResource);
  images[11].GetImageResource(o.images[11].mpResource);
  images[12].GetImageResource(o.images[12].mpResource);
  images[13].GetImageResource(o.images[13].mpResource);
  refs[0] = o.refs[0];
  refs[1] = o.refs[1];
  refs[2] = o.refs[2];
  refs[3] = o.refs[3];
  refs[4] = o.refs[4];
  refs[5] = o.refs[5];
  refs[6] = o.refs[6];
  refs[7] = o.refs[7];
  w058 = o.w058; w05c = o.w05c; w060 = o.w060; w064 = o.w064;
  w068 = o.w068; w06c = o.w06c; w070 = o.w070; w074 = o.w074;
  w078 = o.w078; w07c = o.w07c; w080 = o.w080; w084 = o.w084;
  w088 = o.w088; w08c = o.w08c; w090 = o.w090; w094 = o.w094;
  w098 = o.w098; w09c = o.w09c; w0a0 = o.w0a0; w0a4 = o.w0a4;
  w0a8 = o.w0a8; w0ac = o.w0ac; w0b0 = o.w0b0; w0b4 = o.w0b4;
  w0b8 = o.w0b8; w0bc = o.w0bc; w0c0 = o.w0c0; w0c4 = o.w0c4;
  w0c8 = o.w0c8; w0cc = o.w0cc; w0d0 = o.w0d0; w0d4 = o.w0d4;
  w0d8 = o.w0d8; w0dc = o.w0dc; w0e0 = o.w0e0; w0e4 = o.w0e4;
  w0e8 = o.w0e8; w0ec = o.w0ec; w0f0 = o.w0f0; w0f4 = o.w0f4;
  w0f8 = o.w0f8; w0fc = o.w0fc; w100 = o.w100; w104 = o.w104;
  w108 = o.w108; w10c = o.w10c; w110 = o.w110; w114 = o.w114;
  w118 = o.w118; w11c = o.w11c; w120 = o.w120; w124 = o.w124;
  w128 = o.w128; w12c = o.w12c; w130 = o.w130; w134 = o.w134;
  w138 = o.w138; w13c = o.w13c; w140 = o.w140; w144 = o.w144;
  w148 = o.w148; w14c = o.w14c; w150 = o.w150; w154 = o.w154;
  w158 = o.w158; w15c = o.w15c; w160 = o.w160; w164 = o.w164;
  w168 = o.w168; w16c = o.w16c; w170 = o.w170; w174 = o.w174;
  w178 = o.w178; w17c = o.w17c; w180 = o.w180; w184 = o.w184;
  matrix = o.matrix;
  w1c8 = o.w1c8; w1cc = o.w1cc; w1d0 = o.w1d0; w1d4 = o.w1d4;
  w1d8 = o.w1d8; w1dc = o.w1dc; w1e0 = o.w1e0; w1e4 = o.w1e4;
  w1e8 = o.w1e8; w1ec = o.w1ec; w1f0 = o.w1f0; w1f4 = o.w1f4;
  w1f8 = o.w1f8; w1fc = o.w1fc; w200 = o.w200; w204 = o.w204;
  w208 = o.w208; w20c = o.w20c; w210 = o.w210; w214 = o.w214;
  w218 = o.w218; w21c = o.w21c; w220 = o.w220; w224 = o.w224;
  w228 = o.w228; w22c = o.w22c; w230 = o.w230; w234 = o.w234;
  w238 = o.w238; w23c = o.w23c; w240 = o.w240; w244 = o.w244;
  w248 = o.w248; w24c = o.w24c; w250 = o.w250; w254 = o.w254;
  w258 = o.w258; w25c = o.w25c; w260 = o.w260; w264 = o.w264;
  w268 = o.w268; w26c = o.w26c; w270 = o.w270; w274 = o.w274;
  w278 = o.w278; w27c = o.w27c; w280 = o.w280; w284 = o.w284;
  w288 = o.w288; w28c = o.w28c; w290 = o.w290; w294 = o.w294;
  w298 = o.w298; w29c = o.w29c; w2a0 = o.w2a0; w2a4 = o.w2a4;
  tail = o.tail;
  return *this;
}

// @ 0x00fbd650
void cPlanet::ReleaseAuxObjects()
{
  RefCounted* p = this->ref_5fc.mpObject;
  if (p)
    p->Release();
  p = this->ref_5f8.mpObject;
  if (p)
    p->Release();
  p = this->ref_5b8.mpObject;
  if (p)
    p->Release();
  p = this->ref_5b0.mpObject;
  if (p)
    p->Release();
  this->renderState.ReleaseImages();
  this->state.DestroySubObjects();
}

// @ 0x00fbd6b0
void cPlanet::SetRampEnabled(bool enabled)
{
  if (this->state.m_264 != enabled) {
    this->state.m_264 = enabled;
    this->ExportRampTexture();
    this->mpGame->Dirty();
  }
}

// @ 0x00fbd6e0
void cPlanet::SetPointA(float x, float y, float z)
{
  Vec3 v;
  FUN_00fb8fc0(&v, x, y, z, this->state.m_2c4, this->state.m_2dc);
  if ((this->state.ptA.x != v.x || this->state.ptA.y != v.y || this->state.ptA.z != v.z) &&
      this->state.m_264) {
    this->state.ptA = v;
    this->ExportRampTexture();
    this->mpGame->Dirty();
  }
}

// @ 0x00fbd7b0
void cPlanet::SetPointB(float x, float y, float z)
{
  Vec3 v;
  FUN_00fb8fc0(&v, x, y, z, this->state.m_2c8, this->state.m_2e0);
  if ((this->state.ptB.x != v.x || this->state.ptB.y != v.y || this->state.ptB.z != v.z) &&
      this->state.m_264) {
    this->state.ptB = v;
    this->ExportRampTexture();
    this->mpGame->Dirty();
  }
}

// @ 0x00fbd880
void cPlanet::SetExtent(float u, float v)
{
  this->state.m_008 = u;
  this->state.m_00c = v;
  this->ExportRampTexture();
  this->mpGame->Dirty();
}

// @ 0x00fbd8b0
float10 cPlanet::HeightToRatio(float height)
{
  if (!this->m_7bc)
    this->BuildHeightHistogram();
  int hi = 100;
  int lo = 0;
  int i;
  float h;
  do {
    i = (lo + hi) / 2;
    h = this->heights[i];
    if (height <= h) {
      if (h <= height)
        break;
      hi = i - 1;
    } else {
      lo = i + 1;
    }
  } while (lo <= hi);
  if (i < 100) {
    h = this->heights[i];
    if (h < height) {
      float upper = this->heights[i + 1];
      if (h < upper) {
        float10 t = ((float10)height - (float10)h) / ((float10)upper - (float10)h);
        return (((float10)1 - t) * (float10)i + (float10)(i + 1) * t) * (float10)0.01f;
      }
    }
  }
  if (i > 0) {
    h = this->heights[i];
    if (height < h) {
      float lower = this->heights[i - 1];
      if (lower < h) {
        float10 t = ((float10)height - (float10)lower) / ((float10)h - (float10)lower);
        return (((float10)1 - t) * (float10)(i - 1) + (float10)i * t) * (float10)0.01f;
      }
    }
  }
  return (float10)i * (float10)0.01f;
}

// @ 0x00fbd9d0
float10 cPlanet::RatioToHeight(float ratio)
{
  if (!this->m_7bc)
    this->BuildHeightHistogram();
  float t = ratio > 0.0f ? ratio : 0.0f;
  t = t > 1.0f ? 1.0f : t;
  float index = t * 99.9f;
  int i = (int)index;
  float f = index - (float)i;
  float h = this->heights[i];
  if (i < 100)
    h = this->heights[i + 1] * f + (1.0f - f) * h;
  return (float10)h;
}

// @ 0x00fbda80
float10 cPlanet::CurrentRatio()
{
  if (this->m_7bc)
    return this->HeightToRatio(this->state.m_018);
  return (float10)0.0f;
}

// @ 0x00fbdaa0
void cPlanet::ApplyHeightRatio(float ratio)
{
  float10 h = this->RatioToHeight(ratio);
  float10 d = (float10)this->state.m_018 - h;
  if (d < (float10)0)
    d = -d;
  if (d >= (float10)0.001f) {
    float hf = (float)h;
    this->state.m_018 = hf;
    this->mpHeightField->SetValueTable(hf * 2.0f - 1.0f);
    ((void (__thiscall*)(void*, int))((void**)*(void**)this->mpGame)[0x48 / 4])(this->mpGame, 10);
    ((cTerrainSphere*)this->mpGame)->Relevel(0, 1);
  }
}

// @ 0x00fbdb10
void cPlanet::ResetRenderState()
{
  this->renderState = g_terrainPreset;
  void* mgr = FUN_0067dd60();
  void** vt = *(void***)mgr;
  void* img = ((void* (__thiscall*)(void*, int, void*, int, int, int, int, int, int))vt[0x3c / 4])(
      mgr, 0x62908aa9, g_renderDevice, 0x100, 0x100, 1, 8, 0x15, 0);
  this->renderState.images[13].GetImageResource(img);
  this->state.ref_20c = g_terrainLayers[this->m_5c0];
  this->state.ref_210 = g_terrainRefA;
  this->state.ref_214 = g_terrainRefB;
  this->state.ref_218 = g_terrainRefC;
  this->state.ref_1f4 = g_terrainRefD;
}

// @ 0x00fbdc60
void cPlanet::UpdateEffects()
{
  void* fx = FUN_0067ddd0();
  void** vt = *(void***)fx;
  EffectTarget* target = (EffectTarget*)((void* (__thiscall*)(void*))vt[0xa0 / 4])(fx);
  target->pos.x = this->state.m_034;
  target->pos.y = this->state.m_038;
  target->pos.z = this->state.m_03c;

  float ratio = 0.0f;
  int near = 0;
  if (this->m_7bc) {
    ratio = (float)this->HeightToRatio(this->state.m_018);
    if (ratio > 0.05f)
      near = 1;
  }
  ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 5, near);

  float view = 1.0f - this->state.m_02c;
  int level;
  if (this->state.m_088 > view) {
    ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0xd, 1);
    ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0xe, 0);
    level = 0;
  } else if (this->state.m_090 > view) {
    ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0xd, 0);
    ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0xe, 1);
    level = 0;
  } else {
    ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0xd, 0);
    ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0xe, 0);
    level = 1;
  }
  ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0xf, level);

  float10 scatter = FUN_00fc2ab0(&this->renderState.w168);
  int on = (scatter < (float10)21600.0f || ratio > 64800.0f) ? 1 : 0;
  ((void (__thiscall*)(void*, int, int))vt[0x98 / 4])(fx, 0x15, on);
}

// @ 0x00fbe7d0
void cTerrainStateMgr::Initialize()
{
    Vector2 range;

    ReadFloat(mpPlanetProps.mpObject, 0x257035a, m1f8);
    ReadFloat(mpPlanetProps.mpObject, 0x2570386, m1fc);
    ReadFloat(mpPlanetProps.mpObject, 0x2570391, m200);
    ReadFloat(mpPlanetProps.mpObject, 0x257039b, m204);
    ReadFloat(mpPlanetProps.mpObject, 0x25703a4, m208);

    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703ad, &m21c);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703b9, &m228);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703c1, &m234);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703cc, &m240);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703d6, &m24c);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x25703e1, &m258);

    ReadFloat(mpPlanetProps.mpObject, 0x23227bd, m1ec);
    ReadFloat(mpPlanetProps.mpObject, 0x60ae1385, m1f0);
    ReadFloat(mpPlanetProps.mpObject, 0x1c387e7, m120);
    ReadFloat(mpPlanetProps.mpObject, 0x1c387f2, m124);

    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x87c2473f, &m0c8);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x7cb9e01a, &m0e0);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0xdafa9ed3, &m0f8);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x1331b443, &m0d4);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0xe5ac96bc, &m0ec);
    GetPropertyAsVector3(mpPlanetProps.mpObject, 0x1ce679bf, &m104);
    GetPropertyAsVector4(mpPlanetProps.mpObject, 0x54b6d2b6, &m110);
    GetPropertyAsVector4(mpPlanetProps.mpObject, 0x31e1d79, &m0b4);

    ReadFloat(mpPlanetProps.mpObject, 0xa14ad299, m0b4.w);

    if (GetPropertyAsVector2(mpPlanetProps, 0x10ebd9e, &range)) {
        m13c.x = range.x;
        m13c.y = range.y;
    }

    ReadFloat(mpPlanetProps.mpObject, 0x17eda5f, m148);
    ReadFloat(mpPlanetProps.mpObject, 0x17eda6b, m144);
    ReadFloat(mpPlanetProps.mpObject, 0x2c66e2c5, m14c);
    ReadFloat(mpPlanetProps.mpObject, 0x2c66e2c6, m150);
    ReadFloat(mpPlanetProps.mpObject, 0x58d751bc, m154);
    ReadFloat(mpPlanetProps.mpObject, 0x6b3936a8, m1e8);

    int count;
    Vector3* pVec3;
    Vector2* pVec2;
    for (int i = 0; i < 4; ++i) {
        if (GetPropertyArrayVector3(mpPlanetProps, gTerrainVector3ArrayIDs[i], &count, &pVec3))
            m158[i].assign(pVec3, pVec3 + count);
    }

    if (GetPropertyArrayVector2(mpPlanetProps, 0xecdf0df2, &count, &pVec2))
        m1a8.assign(pVec2, pVec2 + count);
    if (GetPropertyArrayVector3(mpPlanetProps, 0x8e35c36e, &count, &pVec3))
        m1bc.assign(pVec3, pVec3 + count);
    if (GetPropertyArrayVector2(mpPlanetProps, 0x57a0c0c2, &count, &pVec2))
        m1d0.assign(pVec2, pVec2 + count);
    if (GetPropertyArrayVector2(mpPlanetProps, 0x7578caba, &count, &pVec2))
        m128.assign(pVec2, pVec2 + count);
}

// @ 0x00fbee30
void cTerrainStateMgr::FUN_00fbee30()
{
    Vector3 sample;
    Vector3 out;

    FUN_00fb9ad0(&sample);                     // 0x00fb9ad0
    m268 = sample.x;
    m26c = sample.y;
    m270 = sample.z;
    FUN_00fb9ca0(&sample);                     // 0x00fb9ca0
    m274 = sample.x;
    m278 = sample.y;
    m27c = sample.z;
    FUN_00fb9500(1);                           // 0x00fb9500
    m280 = m42c;
    m284 = m430;
    m288 = m434;
    UpdateLightColors(g_1471064, true);        // 0x00fbc770
    m28c = m3cc;
    m290 = m3d0;
    m294 = m3d4;

    Vector3 base;
    base.x = g_16d6710;
    base.y = g_16d6714;
    base.z = g_16d6718;

    FloatVector scalars;
    scalars.mpBegin = 0;
    scalars.mpEnd = 0;
    scalars.mpCapacity = 0;
    Vector3Vector points;
    points.mpBegin = 0;
    points.mpEnd = 0;
    points.mpCapacity = 0;

    for (int i = 0; i < 0x20; ++i) {
        float t = (float)i * g_1432214;
        FUN_00fb8dd0(this, &out, g_1485720 - t);   // 0x00fb8dd0
        float dx = base.x - out.x;
        float dy = base.y - out.y;
        float dz = base.z - out.z;
        float dist = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
        if (m2f0 < dist) {
            scalars.VectorPushBack(&t);             // 0x00455660
            points.DoInsertValue(points.mpEnd, &out);   // 0x004b5ad0
            base = out;
        }
    }

    if (((char*)scalars.mpEnd - (char*)scalars.mpBegin & 0xfffffffc) == 0) {
        float zero = 0.0f;
        scalars.VectorPushBack(&zero);              // 0x00455660
        Vector3* p = FUN_00fb8dd0(this, &out, g_1485720);   // 0x00fb8dd0
        points.DoInsertValue(points.mpEnd, p);      // 0x004b5ad0
        float one = g_1485720;
        scalars.VectorPushBack(&one);               // 0x00455660
        p = FUN_00fb8dd0(this, &out, 0.0f);         // 0x00fb8dd0
        points.DoInsertValue(points.mpEnd, p);      // 0x004b5ad0
    }

    m298 = scalars;                                 // 0x0050d4e0
    m2ac = points;                                  // 0x00473500
}

// @ 0x00fbf1c0
void cTerrainStateMgr::FUN_00fbf1c0(Vector3Vector* in, int unused)
{
    if (m264) {
        m2ac.erase(m2ac.mpEnd, m2ac.mpCapacity);    // 0x0050f740
        int n = (int)((char*)in->mpEnd - (char*)in->mpBegin) / 0xc;
        for (int i = 0; i < n; ++i) {
            Vector3* v = &in->mpBegin[i];
            Vector3 sample;
            Vector3* p = FUN_00fb8fc0(&sample, v->x, v->y, v->z, m2d4, m2ec);   // 0x00fb8fc0
            m2ac.DoInsertValue(m2ac.mpEnd, p);      // 0x004b5ad0
        }
        // The ramp scalars share the argument vector's storage.
        m298.mpBegin = (float*)in->mpBegin;
        m298.mpEnd = (float*)in->mpEnd;
        m298.mpCapacity = (float*)in->mpCapacity;
        ExportRampTextureEx();                      // 0x00fbbc00
        cRampOwner* o = *(cRampOwner**)this;        // +0x00 owner
        o->m494 = 0.0f;  o->m4a4 = 0.0f;  o->m498 = 0.0f;
        o->m49c = g_1485720; o->m4a0 = g_1485720; o->m4a8 = 0.0f;
        o->m4ac = g_1485720; o->m4b0 = g_1485720; o->m4b4 = 0.0f;
        o->m4b8 = 0.0f; o->m4bc = g_1485720; o->m4c0 = g_1485720;
        o->m4c4 = 0.0f; o->m4c8 = 0.0f; o->m4cc = g_1485720;
        o->m4d0 = g_1485720; o->m4d4 = 0.0f; o->m4d8 = 0.0f;
        o->m4dc = g_1485720; o->m4e0 = g_1485720; o->m4e4 = 0.0f;
        o->m4e8 = 0.0f; o->m4ec = g_1485720; o->m4f0 = g_1485720;
    }
}

// @ 0x00fbf3d0
#pragma function(memcpy)
FloatVector* cTerrainStateMgr::FUN_00fbf3d0(FloatVector* out)
{
    out->Resize((int)((char*)m298.mpEnd - (char*)m298.mpBegin) >> 2, m298.mAllocator);
    int bytes = (int)((char*)m298.mpEnd - (char*)m298.mpBegin);
    float* src = m298.mpBegin;
    memcpy(out->mpBegin, src, bytes);
    out->mpEnd = out->mpBegin + (bytes >> 2);
    return out;
}

// @ 0x00fbf430
Vector3Vector* cTerrainStateMgr::FUN_00fbf430(Vector3Vector* out, char build)
{
    if (!build) {
        *out = m2ac;                                // 0x00473500
        return out;
    }
    Vector3Vector tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    for (int i = 0; i < (int)((char*)m2ac.mpEnd - (char*)m2ac.mpBegin) / 0xc; ++i) {
        Vector3* v = &m2ac.mpBegin[i];
        Vector3 sample;
        Vector3* p = FUN_00fb90b0(&sample, v->x, v->y, v->z, m2d4, m2ec);   // 0x00fb90b0
        tmp.DoInsertValue(tmp.mpEnd, p);            // 0x004b5ad0
    }
    *out = tmp;                                     // 0x00473260
    return out;
}

// @ 0x00fc04b0
void cTerrainStateMgr_s00fc_03c0::Reset(bool updateNow)
{
    m010 = 0.0f;
    m018 = 0.5f;
    m014 = 1.0f;
    mpMapSet->SetWaterHeight(0.0f);

    mVec2ac.clear();
    mVec298.clear();

    m268 = kVector3Zero;
    m274 = kVector3Zero;
    mColorA0 = Vector3_s00fc_03c0(1.0f, 1.0f, 1.0f);
    m264 = false;
    m2c0[0] = 1.0f;
    m2c0[1] = 1.0f;
    m2c0[2] = 1.0f;
    m2c0[3] = 1.0f;
    m2c0[4] = 1.0f;
    m2c0[5] = 1.0f;
    m2c0[6] = 1.0f;
    m2c0[7] = 1.0f;
    m2c0[8] = 1.0f;
    m2c0[9] = 1.0f;
    m2c0[10] = 1.0f;
    m2c0[11] = 1.0f;
    m2c0[12] = 0.1f;
    m028 = 1.0f;
    m008 = 0.5f;
    m00c = 0.5f;
    mTimeOfDay = 0.5f;
    mColorB0 = Vector3_s00fc_03c0(0.3f, 0.3f, 0.3f);
    mColorA1 = Vector3_s00fc_03c0(1.0f, 0.8f, 0.8f);
    mColorB1 = Vector3_s00fc_03c0(0.3f, 0.1f, 0.1f);
    mColorA2 = Vector3_s00fc_03c0(0.8f, 1.0f, 0.8f);
    mColorB2 = Vector3_s00fc_03c0(0.1f, 0.3f, 0.1f);
    m110 = Vector4_s00fc_03c0(50.0f, 70.0f, 50.0f, 70.0f);
    m0b4 = Vector4_s00fc_03c0(0.6f, 0.6f, 2.0f, 0.0f);
    mSunDir = Vector3_s00fc_03c0(0.0f, 1.0f, 0.0f);
    mSunMatrix = Matrix4();
    mLightRange[0] = Vector2_s00fc_03c0(0.1f, 0.3f);
    mLightRange[1] = Vector2_s00fc_03c0(0.3f, 0.7f);
    mLightRange[2] = Vector2_s00fc_03c0(0.7f, 1.0f);
    mLightRange[3] = Vector2_s00fc_03c0(0.0f, 0.3f);
    mLightRange[4] = Vector2_s00fc_03c0(0.3f, 0.7f);
    mLightRange[5] = Vector2_s00fc_03c0(0.7f, 1.0f);
    m080 = 0;
    mLatitude = 0.5f;

    Transform xform;
    xform.SetRotationFromDirs(mSunDir, Vector3_s00fc_03c0(0.0f, 0.0f, 1.0f));
    xform.ToMatrix4(mSunMatrix);

    m4fc = Vector4_s00fc_03c0(0.5f, 0.5f, 0.5f, 0.5f);
    m13c = -1.0f;
    m140 = 1.0f;
    m144 = 5.0f;
    m148 = 67.0f;
    m14c = 0.01f;
    m150 = 0.01f;
    m154 = 100.0f;
    m1e8 = 25.0f;
    m1ec = 20.0f;
    m1f0 = 8.0f;
    m1f8 = 300.0f;
    m1fc = 1.35f;
    m200 = 0.95f;
    m204 = 1.0f;
    m208 = 1.0f;
    m21c = Vector3_s00fc_03c0(0.01f, 0.01f, 0.01f);
    m228 = Vector3_s00fc_03c0(1.0f, 1.0f, 1.0f);
    m234 = Vector3_s00fc_03c0(0.4f, 0.5f, 0.7f);
    m240 = Vector3_s00fc_03c0(0.15f, 0.15f, 0.18f);
    m24c = Vector3_s00fc_03c0(-0.045f, -0.045f, -0.045f);
    m258 = Vector3_s00fc_03c0(0.1f, 0.1f, 0.1f);
    float minGradient;   // never initialized in the original: reads the stale 0.1f temp slot
    float maxGradient;
    m120 = 0.5f;
    m124 = 0.5f;

    SP::PropertyManager()->GetPropertyList(0xd985994c, 0x243ad2b, mpPlanetProps.AsPointer());
    Initialize();
    if (IsWorldFlagSet(2)) {
        SP::PropertyManager()->GetPropertyList(0x1726fe2, 0x243ad2b, mpTuningProps.AsPointer());
        ApplyTuning();
    }

    mpTexture = g_pDefaultTerrainTexture;
    if (mpTexture.mpObject)
        mpTexture.mpObject->m1c = m1ec;

    cPropertyList_s00fc_03c0* list = SP::TerrainEditor()->mpLightingProps;
    if (list)
        list->AddRef();
    GetPropertyAsVector2(list, 0x328a103, &mLightRange[0]);
    GetPropertyAsVector2(list, 0x328a10c, &mLightRange[1]);
    GetPropertyAsVector2(list, 0x328a115, &mLightRange[2]);
    GetPropertyAsVector2(list, 0x328a11d, &mLightRange[3]);
    GetPropertyAsVector2(list, 0x328a125, &mLightRange[4]);
    GetPropertyAsVector2(list, 0x328a12f, &mLightRange[5]);

    if (list) {
        Property_s00fc_03c0* prop;
        if (list->GetProperty(0x21126c2, &prop) && prop->mnType == 0xd)
            mMaxAltLow = *prop->GetFloat();
        if (list->GetProperty(0x21126ce, &prop) && prop->mnType == 0xd)
            mMaxAltMid = *prop->GetFloat();
        if (list->GetProperty(0x21126e3, &prop) && prop->mnType == 0xd)
            mMaxAltHigh = *prop->GetFloat();
        if (list->GetProperty(0x228d235, &prop) && prop->mnType == 0xd)
            minGradient = *prop->GetFloat();
        if (list->GetProperty(0x228d23f, &prop) && prop->mnType == 0xd)
            maxGradient = *prop->GetFloat();
    }
    mpMapSet->SetCliffGradients(minGradient, maxGradient);

    float t = mpMapSet->mRadius * 0.002f;
    float maxAlt;
    if (t >= 1.0f)
        maxAlt = (mMaxAltHigh - mMaxAltMid) * (t - 1.0f) + mMaxAltMid;
    else
        maxAlt = (mMaxAltMid - mMaxAltLow) * t + mMaxAltLow;
    mpMapSet->SetMaxHeight(maxAlt);

    UpdateWater();
    mAmbient = ComputeAmbient();
    m450 = 0.0f;
    mMinCliffGradient = mpMapSet->mMinCliffGradient;
    mMaxCliffGradient = mpMapSet->mMaxCliffGradient;
    if (updateNow)
        UpdateSeasonsNow();

    if (SP::EffectsManager()->GetEffect(0x23541242))
        mpEffect = SP::EffectsManager()->GetEffect(0x23541242);

    if (list)
        list->Release();
}

// @ 0x00fc0fe0
void ResetTerrainGlobals()
{
    {
        SP::cTerrainStateMgr_s00fc_03c0__state::cStateParms state;
        gCoreState = *state.Reset();
        state.DestroySubObjects();
    }

    {
        RenderState_s00fc_03c0__state renderState;
        void** refs = &renderState.images[0].mpResource;    // 22 reference slots, images then refs
        for (unsigned i = 0; i < 22; i++)
            refs[i] = 0;
        gRenderState = renderState;
        renderState.ReleaseImages();
    }

    for (unsigned i = 0; i < 16; i++) {
        IRefCounted* p = gTerrainLayerTable[i];
        if (p) {
            gTerrainLayerTable[i] = 0;
            p->Release();
        }
    }
    for (unsigned i = 0; i < 16; i++) {
        IRefCounted* p = gTerrainLayerTable2[i];
        if (p) {
            gTerrainLayerTable2[i] = 0;
            p->Release();
        }
    }
}
