// Slice s011f0840 -- RenderWare 4 D3D9 ActiveState / GlobalState state initialisation.
//
// This is the front of the rwgdrvgraph / D3D9 state translation unit: the ActiveState::Initialize
// global initialiser, ActiveState::Reset / FindLights / CheckUVMapping / SetTexture, and the small
// GlobalState blend-mode and bit-shift-table helpers.  The software mirror of the IDirect3DDevice9
// state lives at fixed addresses in the 0x016f5xxx..0x016fxxxx range; the classes below use the
// dev-PDB global addresses from the neighbouring s011f1400 reconstruction.
//
// RenderWare 4 core was built with VC .NET 2003 (cl 13.10) and /GL + /LTCG, so a single-object
// compile cannot reproduce the cross-call register allocation; the functions here are complete
// behavioural reconstructions (see manifest.txt / nonmatching.txt for which are byte-exact).
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;

namespace rw { namespace graphics {

struct RwRGBRealTag  { float red, green, blue; };
struct RwRGBARealTag { float red, green, blue, alpha; };
struct Matrix44Affine { u32 m[16]; };

// D3D9 texture object wrapper: the IDirect3DTexture9 pointer sits at +8.
struct Raster {
  u32  m_pad0;         // +0x0
  u32  m_pad4;         // +0x4
  void* m_d3dTexture;  // +0x8
};

// D3DPRESENT_PARAMETERS (the subset zeroed by Initialize) -- 0xe dwords in the retail build.
struct PresentParams {
  u32 m_words[0xe];
};

// ------------------------------------------------------------------ ActiveState
// Software mirror of the D3D9 device state.  Addresses are the dev-PDB pdb_globals addresses.
class ActiveState {
public:
  static int  Initialize(void);                            // 0x011f0840
  static void Reset(void);                                 // 0x011f0fc0
  static void FindLights(void);                            // 0x011f1130
  static void CheckUVMapping(void);                        // 0x011f1210
  static void SetTexture(u32 stage, const Raster* raster); // 0x011f1280

  static u32  m_d3d9ActiveState;              // 0x016f89c8
  static u32  m_windowHandle;                 // 0x016f658c
  static PresentParams m_presentParams;       // 0x016f8b9c
  static void* m_d3d9Device;                  // 0x016f89d0

  static Matrix44Affine* m_transform;         // 0x016f85ac
  static int  m_transformType;                // 0x016f8b50
  static const void* m_transposedTransform;   // 0x016f8cf4
  static const void* m_inverseTransform;      // 0x016f9120
  static const void* m_inverseNormalizedTransform; // 0x016f9114

  static u32  m_colorIsWhite;                 // 0x016f89c4
  static RwRGBARealTag m_color;               // 0x016f6590
  static u32  m_ambientIsBlack;               // 0x016f89d4
  static RwRGBARealTag m_ambient;             // 0x016f5c40

  static int  m_numLights;                    // 0x016f90c4
  static void* m_light[8];                    // 0x016f656c
  static u32  m_lightsArray[8];               // 0x016f8910
  static u32  m_lightsArray1[8];              // 0x016f8934
  static u32  m_lightsArray2[8];              // 0x016f8958
  static u32  m_lightsArray3[8];              // 0x016f897c
  static u32  m_lightsArray4[8];              // 0x016f89a0

  static u32  m_softStateUpdated;             // 0x016f9110
  static u32  m_softStateDelta;               // 0x016f8af8

  static u8   m_UVMapping[17];                // 0x016f85b4
  static u32  m_UVUsed;                       // 0x016f5c50
  static u8   m_numUsedUV;                    // 0x016f9134

  static u32  m_renderStateShadow[210];       // 0x016f85c8
  static const Raster* m_rasterShadow[17];    // 0x016f5c58

  static int  m_fogType;                      // 0x016f90c0
  static RwRGBRealTag m_fogColor;             // 0x016f9168
  static float m_fogStartDensity;             // 0x016f5c54
  static float m_fogEnd;                      // 0x016f8d00

  static u32  m_textureStageStateShadow[17][33];  // 0x016f5ca0
  static u32  m_samplerStateShadow[17][14];       // 0x016f8d08

  static int  m_primitiveType;                // 0x016f85a8
  static const void* m_vertexDescriptor;      // 0x016f65a0

  static u32  m_vertexShaderBound;            // 0x016f89dc
  static u32  m_pixelShaderBound;             // 0x016f89e4
  static u32  m_vertexShaderPtr;              // 0x016f89e0
  static u32  m_pixelShaderPtr;               // 0x016f89e8
};

// ------------------------------------------------------------------ GlobalState
class GlobalState {
public:
  static void SetBlendMode(u32 mode);             // 0x011f1340
  static u32  GetBlendMode(void);                 // 0x011f13a0
  static void D3D9InitializeBitShiftTable(void);  // 0x011f13c0

  static volatile u32  m_blendModeSrc;                     // 0x016f922c
  static volatile u32  m_blendModeDst;                     // 0x016f9230
  static volatile u32  m_blendModeIsDefault;               // 0x016f924c
  static u32  m_renderStateDirty;                 // 0x016fa38c
};

}} // namespace rw::graphics

// ---- rwgD3D9BitShiftTable (anonymous namespace in the original) -------------------
extern u8 rwgD3D9BitShiftTable[256];          // 0x016fa3c0

using namespace rw::graphics;

// IDirect3DDevice9 vtbl slot helpers (call through the interface pointer).
static void DeviceSetVertexShader(void* device, u32 shader) {
  typedef void (__stdcall *Fn)(void*, u32);
  Fn fn = *(Fn*)(*(u32*)device + 0x170);
  fn(device, shader);
}
static void DeviceSetPixelShader(void* device, u32 shader) {
  typedef void (__stdcall *Fn)(void*, u32);
  Fn fn = *(Fn*)(*(u32*)device + 0x1ac);
  fn(device, shader);
}
static void DeviceSetTexture(void* device, u32 stage, void* texture) {
  typedef void (__stdcall *Fn)(void*, u32, void*);
  Fn fn = *(Fn*)(*(u32*)device + 0x104);
  fn(device, stage, texture);
}

// ===================================================================================
//  rw::graphics::ActiveState::Initialize -- 0x011f0840
//
//  Zero/definite-initialise the whole ActiveState mirror: the D3DPRESENT_PARAMETERS, the
//  transform / colour / ambient / light / UV / fog state and the per-stage render, texture-stage
//  and sampler state shadows, then return 1.
// @ 0x011f0840
// ===================================================================================
int ActiveState::Initialize(void) {
  m_d3d9ActiveState = 0;
  m_windowHandle = 0;
  for (u32 i = 0; i < 0xe; ++i) m_presentParams.m_words[i] = 0;
  m_d3d9Device = 0;

  m_transformType = 0;
  m_transform = 0;
  m_transposedTransform = 0;
  m_inverseTransform = 0;
  m_inverseNormalizedTransform = 0;

  m_softStateUpdated = 0;
  m_softStateDelta = 0;
  m_colorIsWhite = 1;
  m_color.red = 0.0f; m_color.green = 0.0f; m_color.blue = 0.0f; m_color.alpha = 1.0f;
  m_ambientIsBlack = 1;
  m_ambient.red = 0.0f; m_ambient.green = 0.0f; m_ambient.blue = 0.0f; m_ambient.alpha = 1.0f;

  m_numLights = 0;
  for (u32 i = 0; i < 8; ++i) m_light[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray1[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray2[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray3[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray4[i] = 0;

  m_renderStateShadow[0] = 0;
  for (u32 i = 1; i < 210; ++i) m_renderStateShadow[i] = 0;
  m_UVUsed = 0;
  for (u32 i = 0; i < 17; ++i) m_UVMapping[i] = 0;
  m_numUsedUV = 0;

  for (u32 i = 0; i < 17; ++i) m_rasterShadow[i] = 0;
  for (u32 s = 0; s < 17; ++s)
    for (u32 j = 0; j < 33; ++j) m_textureStageStateShadow[s][j] = 0;
  for (u32 s = 0; s < 17; ++s)
    for (u32 j = 0; j < 14; ++j) m_samplerStateShadow[s][j] = 0;

  m_fogType = 0;
  m_fogColor.red = 1.0f; m_fogColor.green = 1.0f; m_fogColor.blue = 1.0f;
  m_fogStartDensity = 0.0f;
  m_fogEnd = 1.0f;

  m_vertexShaderBound = 0;
  m_vertexShaderPtr = 0;
  m_pixelShaderBound = 0;
  m_pixelShaderPtr = 0;
  m_renderStateShadow[0] = 0;
  m_softStateDelta = 0;

  m_primitiveType = 0xffffffff;
  m_vertexDescriptor = 0;
  return 1;
}

// ===================================================================================
//  rw::graphics::ActiveState::Reset -- 0x011f0fc0
// @ 0x011f0fc0
// ===================================================================================
void ActiveState::Reset(void) {
  for (u32 i = 0; i < 210; ++i) m_renderStateShadow[i] = 0xcdcdcdcd;
  for (u32 s = 0; s < 17; ++s)
    for (u32 j = 0; j < 33; ++j) m_textureStageStateShadow[s][j] = 0xcdcdcdcd;
  for (u32 s = 0; s < 17; ++s)
    for (u32 j = 0; j < 14; ++j) m_samplerStateShadow[s][j] = 0xcdcdcdcd;

  for (u32 i = 0; i < 17; ++i) m_rasterShadow[i] = 0;
  m_transform = 0;
  m_numLights = 0;
  for (u32 i = 0; i < 8; ++i) m_light[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray1[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray2[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray3[i] = 0;
  for (u32 i = 0; i < 8; ++i) m_lightsArray4[i] = 0;

  m_color.red = 0.0f; m_color.green = 0.0f; m_color.blue = 0.0f; m_color.alpha = 1.0f;
  m_ambient.red = 0.0f; m_ambient.green = 0.0f; m_ambient.blue = 0.0f; m_ambient.alpha = 1.0f;
  m_softStateUpdated = 0;
  m_softStateDelta = 0;
  m_vertexDescriptor = 0;
  m_vertexShaderBound = 0;
  m_pixelShaderBound = 0;

  if (m_vertexShaderBound != 0) {
    DeviceSetVertexShader(m_d3d9Device, 0);
    m_vertexShaderBound = 0;
  }
  if (m_pixelShaderBound != 0) {
    DeviceSetPixelShader(m_d3d9Device, 0);
    m_pixelShaderBound = 0;
  }
}

// ===================================================================================
//  rw::graphics::ActiveState::FindLights -- 0x011f1130
// @ 0x011f1130
// ===================================================================================
void ActiveState::FindLights(void) {
  m_numLights = 0;
  m_lightsArray[0] = 0;
  m_lightsArray1[0] = 0;
  m_lightsArray2[0] = 0;
  m_lightsArray3[0] = 0;
  m_lightsArray4[0] = 0;
  u32 num = 0;
  for (u32 off = 0; off < 0x20; off += 4) {
    u32* light = *(u32**)((u8*)&m_light[0] + off);
    if (light != 0) {
      switch (light[0]) {
        case 0:
          m_lightsArray[num] = (u32)light;
          ++num;
          break;
        case 1:
          m_lightsArray1[num] = (u32)light;
          ++num;
          break;
        case 2:
          m_lightsArray2[num] = (u32)light;
          ++num;
          break;
        case 3:
          m_lightsArray3[num] = (u32)light;
          ++num;
          break;
        case 4:
          m_lightsArray4[num] = (u32)light;
          ++num;
          break;
      }
      ++m_numLights;
    }
  }
}

// ===================================================================================
//  rw::graphics::ActiveState::CheckUVMapping -- 0x011f1210
// @ 0x011f1210
// ===================================================================================
void ActiveState::CheckUVMapping(void) {
  u8 maxUV = 0;
  u32 mask = 0;
  u32 old = m_UVUsed;
  m_numUsedUV = maxUV;
  m_UVUsed = mask;
  for (u32 i = 0; i < 0x11; ++i) {
    u8 v = m_UVMapping[i];
    if (v != 0) {
      if (maxUV < v)
        maxUV = v;
      mask |= 1u << (v + 5);
    }
  }
  if (old != mask)
    m_softStateUpdated |= 0x100000;
  m_UVUsed = mask;
  m_numUsedUV = maxUV;
}

// ===================================================================================
//  rw::graphics::ActiveState::SetTexture -- 0x011f1280
// @ 0x011f1280
// ===================================================================================
void ActiveState::SetTexture(u32 stage, const Raster* raster) {
  m_softStateUpdated |= 0x400000;
  const Raster* p = raster;
  if (p != m_rasterShadow[stage]) {
    if (p != 0) {
      DeviceSetTexture(m_d3d9Device, stage, p->m_d3dTexture);
      m_rasterShadow[stage] = p;
      return;
    }
    DeviceSetTexture(m_d3d9Device, stage, 0);
    m_rasterShadow[stage] = p;
  }
}

// ===================================================================================
//  FUN_011f12e0 -- 0x011f12e0 (SetTexture without the shadow compare)
// @ 0x011f12e0
// ===================================================================================
void FUN_011f12e0(u32 stage, const Raster* raster) {
  ActiveState::m_softStateUpdated |= 0x400000;
  if (raster != 0) {
    DeviceSetTexture(ActiveState::m_d3d9Device, stage, raster->m_d3dTexture);
    ActiveState::m_rasterShadow[stage] = raster;
    return;
  }
  DeviceSetTexture(ActiveState::m_d3d9Device, stage, 0);
  ActiveState::m_rasterShadow[stage] = raster;
}

// ===================================================================================
//  rw::graphics::GlobalState::SetBlendMode -- 0x011f1340
// @ 0x011f1340
// ===================================================================================
void GlobalState::SetBlendMode(u32 mode) {
  if (mode == 0x10002) {
    m_renderStateDirty |= 0x100000;
    m_blendModeIsDefault = 0;
    return;
  }
  int src = (int)mode;
  m_blendModeSrc = (u32)(src & 0xffff);
  u32 dirty = m_renderStateDirty;
  dirty |= 0x103000;
  m_blendModeIsDefault = 1;
  m_renderStateDirty = dirty;
  m_blendModeDst = mode >> 0x10;
}

// ===================================================================================
//  rw::graphics::GlobalState::GetBlendMode -- 0x011f13a0
// @ 0x011f13a0
// ===================================================================================
u32 GlobalState::GetBlendMode(void) {
  if (m_blendModeIsDefault == 0)
    return 0x10002;
  u32 hi = m_blendModeDst;
  u32 lo = m_blendModeSrc;
  return (hi << 0x10) | lo;
}

// ===================================================================================
//  rw::graphics::GlobalState::D3D9InitializeBitShiftTable -- 0x011f13c0
// @ 0x011f13c0
// ===================================================================================
void GlobalState::D3D9InitializeBitShiftTable(void) {
  u8 cur = rwgD3D9BitShiftTable[0];
  u8 eight = 8;
  if (cur != eight) {
    rwgD3D9BitShiftTable[0] = eight;
    u32 v = 1;
    do {
      u32 shift = 0;
      int t = (int)v;
      while ((t & 1) == 0) {
        ++shift;
        t = (int)(v >> shift);
      }
      rwgD3D9BitShiftTable[v] = (u8)shift;
      ++v;
    } while (v < 0x100);
  }
}
