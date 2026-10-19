// src/game/SPTerrain/SPTerrainStateMgr.cpp -- migrated from slice(s) s00fbe7d0, s00fbce30, s00fba330 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainStateMgr.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainStateMgr.h"
#include "EA/Variant.h"
#include "cSPVector3.h"
#include "SP/cPropertyList.h"

// ---- items of slice s00fba330 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
struct ResourceKey {
    uint32_t instance, type, group;
};
struct IResMan {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const ResourceKey* key, IRef** out, int, int, int, int);   // 0x0c
};
struct IImageSrc {   // object returned by FUN_0067dd60
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
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
// ---- items of slice s00fba330 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern AutoRef g16d6ab8, g16d6ab4, g16d6abc, g16d6ac0, g16d6ac4, g16d6ac8;
extern AtomicRef g16d6aa8, g16d6aa0, g16d6a78, g16d6a7c, g16d6a80, g16d6a8c, g16d6a90, g16d6a94,
    g16d6a98, g16d6a9c, g16d6a84, g16d6a88, g16d6aa4;
extern AutoRef g16d6ab0, g16d698c, g16d6990, g16d6994, g16d6998, g16d6974, g16d6acc;
extern AutoRef g16d6d30[16], g16d6d70[16];

// ---- items of slice s00fbce30 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
  RenderState& operator=(const RenderState& o);
};
// ---- items of slice s00fbce30 end

// ---- items of slice s00fbe7d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gTerrainVector3ArrayIDs[4];   // 0x014911c0
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
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
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
    uint32_t pad264[(0x5b0 - 0x264) / 4];
    AutoRefCount<cPropertyList> mpPlanetProps;   // +0x5b0

    void Initialize();
};
inline void ReadFloat(cPropertyList* list, uint32_t id, float& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, &prop) && prop->mnType == 0xd)
        dst = *prop->GetFloat();
}
// ---- items of slice s00fbe7d0 end

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
