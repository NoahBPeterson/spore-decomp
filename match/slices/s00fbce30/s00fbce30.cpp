// slice s00fbce30: implicit copy-assignment of a large render-state record (0x2b8 bytes):
// 14 image references, 8 intrusive refcounted objects, then plain scalar fields.
#include "types.h"

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

// @ 0x00fbce30
RenderState& RenderState::operator=(const RenderState& o) {
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

// ---------------------------------------------------------------------------
// Terrain planet object that owns the render state (0x00fbd650 - 0x00fbdc60).
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
extern void* g_renderDevice;                 // 0x015b1600

extern Vec3* FUN_00fb8fc0(Vec3* out, float a, float b, float c, float d, float e); // 0x00fb8fc0
extern void* FUN_0067dd60();                 // 0x0067dd60 scene render manager
extern void* FUN_0067ddd0();                 // 0x0067ddd0 effects manager
extern float10 FUN_00fc2ab0(void* scatter);  // 0x00fc2ab0 terrain scatter, x87 float

// Sub-object at +0x008 of cPlanet (the terrain state manager).
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
