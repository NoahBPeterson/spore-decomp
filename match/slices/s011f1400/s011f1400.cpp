// slice s011f1400 -- RenderWare 4 D3D9 state dispatch (rwgdrvgraph / D3D9 soft-state + device state).
//
// These are the rw::graphics::GlobalState "dispatch" entry points that push the software mirror of
// the D3D9 device state (m_renderState / m_textureStageState / m_samplerState and the soft state in
// ActiveState) out to the IDirect3DDevice9, plus D3D9Reset and D3D9ClearDirtyFlags.
//
// RenderWare 4 core was built with VC .NET 2003 (cl 13.10) and /LTCG; single-object codegen cannot
// reproduce the cross-call register allocation, so byte-exactness is not the goal here.  These are
// complete behavioural reconstructions (equivalence only).
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int  u32;
typedef unsigned char u8;

namespace rw { namespace graphics {

struct RwRGBRealTag  { float red, green, blue; };
struct RwRGBARealTag { float red, green, blue, alpha; };
struct Matrix44Affine { u32 m[16]; };
struct Raster;
struct Palette;

// ---- free helpers in this address range (no symbol; resolved by address) ----
void FUN_011f2bf0(void);                 // 0x011f2bf0
void FUN_011f9560(void);                 // 0x011f9560

// ------------------------------------------------------------------ DevCapsManager
class DevCapsManager {
public:
  static const u32* GetD3DCAPS9(void);   // 0x011f8af0
};

// ------------------------------------------------------------------ Device
class Device {
public:
  static u32 D3D9GetMaxSamplerStage(u32 capsFlags);   // 0x011f8400
};

// ------------------------------------------------------------------ ActiveState
// Software mirror of the device state; the members marked here are the ones touched by the
// GlobalState dispatch routines.  Addresses are the dev-PDB pdb_globals addresses.
class ActiveState {
public:
  static void Reset(void);                                    // 0x011f0fc0
  static void FindLights(void);                               // 0x011f1130
  static void CheckUVMapping(void);                           // 0x011f1210
  static void SetTexture(u32 stage, const Raster* raster);    // 0x011f1280

  static RwRGBARealTag m_color;               // 0x016f6590
  static u32  m_colorIsWhite;                 // 0x016f89c4
  static RwRGBARealTag m_ambient;             // 0x016f5c40
  static u32  m_ambientIsBlack;               // 0x016f89d4
  static Matrix44Affine* m_transform;         // 0x016f85ac
  static int  m_transformType;                // 0x016f8b50
  static u32  m_softStateUpdated;             // 0x016f9110
  static const void* m_transposedTransform;   // 0x016f8cf4
  static const void* m_inverseTransform;      // 0x016f9120
  static const void* m_inverseNormalizedTransform; // 0x016f9114
  static void* m_light[8];                    // 0x016f656c
  static u8   m_UVMapping[17];                // 0x016f85b4
  static int  m_fogType;                      // 0x016f90c0
  static RwRGBRealTag m_fogColor;             // 0x016f9168
  static float m_fogStartDensity;             // 0x016f5c54
  static float m_fogEnd;                      // 0x016f8d00
  static void* m_d3d9Device;                  // 0x016f89d0
  static const Palette* m_paletteShadow;      // 0x016f9130
  static u32  m_renderStateShadow[210];             // 0x016f85c8
  static u32  m_textureStageStateShadow[17][33];    // 0x016f5ca0
  static u32  m_samplerStateShadow[17][14];         // 0x016f8d08
};

// ------------------------------------------------------------------ GlobalState
class GlobalState {
public:
  static void D3D9SoftStateDispatch(u32 softState);    // 0x011f1400
  static void D3D9RenderStateDispatch(void);           // 0x011f1810
  static void D3D9RasterDispatch(void);                // 0x011f18b0
  static void D3D9PaletteDispatch(void);               // 0x011f1900
  static void D3D9TextureStageStateDispatch(void);     // 0x011f1950
  static void D3D9SamplerStateDispatch(void);          // 0x011f1a10
  static void D3D9ClearDirtyFlags(void);               // 0x011f1b20
  static void Dispatch(void);                          // 0x011f1c20
  static void D3D9Reset(void);                         // 0x011f1d70

  static u32  m_renderState[210];                 // 0x016f91e0
  static u32  m_softStateDirty;                   // 0x016f9528
  static u32  m_samplerStateDirty[17];            // 0x016f9530
  static void* m_light[8];                        // 0x016f9574
  static float m_fogStartDensity;                 // 0x016f9594
  static RwRGBRealTag m_ambient;                  // 0x016f9598
  static const Raster* m_raster[17];              // 0x016f9650
  static RwRGBRealTag m_fogColor;                 // 0x016f9694
  static int  m_transformType;                    // 0x016f96a0
  static const Palette* m_palette;                // 0x016f96a4
  static RwRGBARealTag m_color;                   // 0x016f96a8
  static u32  m_textureStageState[17][33];        // 0x016f96b8
  static int  m_fogType;                          // 0x016f9f7c
  static u32  m_textureStageStateDirty[17];       // 0x016f9f80
  static u32  m_samplerState[17][14];             // 0x016f9fc8
  static Matrix44Affine* m_transform;             // 0x016fa380
  static u32  m_paletteDirty;                     // 0x016fa384
  static float m_fogEnd;                          // 0x016fa388
  static u32  m_renderStateDirty[7];              // 0x016fa38c
  static u32  m_rasterStageDirty;                 // 0x016fa3a8
  static u8   m_UVMapping[17];                    // 0x016fa3ac
};

}} // namespace rw::graphics

using namespace rw::graphics;

// ---- rwg_D3D9* update masks (anonymous namespace in the original) -----------------
extern u32 rwg_D3D9RasterToUpdate;                  // 0x016f95a4
extern u32 rwg_D3D9TextureStageStateToUpdate[17];   // 0x016f95a8
extern u32 rwg_D3D9SamplerStateToUpdate[17];        // 0x016f95f0
extern u32 rwg_D3D9RenderStateToUpdate[7];          // 0x016f9634
extern u8  rwgD3D9BitShiftTable[256];               // 0x016fa3c0
extern u8  DAT_016fa3bd;                            // 0x016fa3bd


// ===================================================================================
//  rw::graphics::GlobalState::D3D9SoftStateDispatch -- 0x011f1400
//
//  Copies the requested subsets of the software state into the ActiveState mirror (transform,
//  colour, ambient, lights, UV mapping, fog) and sets the matching "soft state updated" bits.
//  param_1 is the mask of soft-state classes to apply (bits: 0 transform, 0x10 colour,
//  0x20 ambient, 0x3fc0 lights, 0x4000 ?, 0x8000 UV mapping, 0x10000 fountain/fog-type,
//  0x20000 fog colour, 0x40000 fog start density, 0x80000 fog end).
// @ 0x011f1400
// ===================================================================================
void GlobalState::D3D9SoftStateDispatch(u32 softState)
{
  u32 mask = softState & 0xfffffff3u;

  if ((softState & 0x4000u) != 0) {
    ActiveState::m_softStateUpdated |= 0x4000u;
    mask = softState & 0xffffbff3u;
    if (mask == 0)
      return;
  }

  if ((mask & 1u) != 0) {
    ActiveState::m_transformType = GlobalState::m_transformType;
    ActiveState::m_transform = GlobalState::m_transform;

    // Normalise the (row-major, SIMD) affine matrix: bottom of each row gets w = 0 / 1.
    Matrix44Affine* t = GlobalState::m_transform;
    t->m[3]  = 0;
    t->m[7]  = 0;
    t->m[11] = 0;
    t->m[15] = 0x3f800000u;             // 1.0f

    ActiveState::m_softStateUpdated |= 1u;
    mask &= 0xfffffffcu;
    ActiveState::m_transposedTransform = 0;
    ActiveState::m_inverseTransform = 0;
    ActiveState::m_inverseNormalizedTransform = 0;
    if (mask == 0)
      return;
  }

  if ((mask & 0x10u) != 0) {
    float r = GlobalState::m_color.red;
    float g = GlobalState::m_color.green;
    float b = GlobalState::m_color.blue;
    float a = GlobalState::m_color.alpha;

    if (!(ActiveState::m_color.red   == r &&
          ActiveState::m_color.green == g &&
          ActiveState::m_color.blue  == b &&
          ActiveState::m_color.alpha == a)) {
      ActiveState::m_softStateUpdated |= 0x10u;
      if (r == 1.0f && g == 1.0f && b == 1.0f && a == 1.0f)
        ActiveState::m_colorIsWhite = 1;
      else
        ActiveState::m_colorIsWhite = 0;
    }
    ActiveState::m_color.red   = r;
    ActiveState::m_color.green = g;
    ActiveState::m_color.blue  = b;
    ActiveState::m_color.alpha = a;
    ActiveState::m_softStateUpdated |= 0x10u;
    mask &= 0xffffffefu;
    if (mask == 0)
      return;
  }

  if ((mask & 0x20u) != 0) {
    float r = GlobalState::m_ambient.red;
    float g = GlobalState::m_ambient.green;
    float b = GlobalState::m_ambient.blue;

    if (!(ActiveState::m_ambient.red   == r &&
          ActiveState::m_ambient.green == g &&
          ActiveState::m_ambient.blue  == b)) {
      ActiveState::m_softStateUpdated |= 0x20u;
      ActiveState::m_ambient.red   = r;
      ActiveState::m_ambient.green = g;
      ActiveState::m_ambient.blue  = b;
      if (r == 0.0f && g == 0.0f && b == 0.0f)
        ActiveState::m_ambientIsBlack = 1;
      else
        ActiveState::m_ambientIsBlack = 0;
    }
    mask &= 0xffffffdfu;
    if (mask == 0)
      return;
  }

  u32 lights = mask & 0x3fc0u;
  if (lights != 0) {
    ActiveState::m_softStateUpdated |= lights;
    int off = 0;
    do {
      if ((lights & 0x40u) != 0)
        ActiveState::m_light[off >> 2] = GlobalState::m_light[off >> 2];
      lights >>= 1;
      off += 4;
    } while (lights > 0x3fu);
    ActiveState::FindLights();
    mask &= 0xffffc03fu;
    if (mask == 0)
      return;
  }

  if ((char)(mask >> 8) < '\0') {          // bit 0x8000: UV mapping
    for (u32 i = 0; i < 0x11u; ++i) {
      if (ActiveState::m_UVMapping[i] != GlobalState::m_UVMapping[i]) {
        ActiveState::m_UVMapping[i] = GlobalState::m_UVMapping[i];
        ActiveState::m_softStateUpdated |= 0x8000u;
      }
    }
    if ((char)(ActiveState::m_softStateUpdated >> 8) < '\0')
      ActiveState::CheckUVMapping();
    mask &= 0xffff7fffu;
    if (mask == 0)
      return;
  }

  if ((mask & 0xf0000u) != 0) {
    if ((mask & 0x10000u) != 0) {
      ActiveState::m_fogType = GlobalState::m_fogType;
      ActiveState::m_softStateUpdated |= 0x10000u;
    }
    if ((mask & 0xe0000u) != 0) {
      if ((mask & 0x20000u) != 0) {
        ActiveState::m_fogColor.blue = GlobalState::m_fogColor.blue;
        ActiveState::m_softStateUpdated |= 0x20000u;
        ActiveState::m_fogColor.red = GlobalState::m_fogColor.red;
        ActiveState::m_fogColor.green = GlobalState::m_fogColor.green;
      }
      if ((mask & 0x40000u) != 0) {
        ActiveState::m_softStateUpdated |= 0x40000u;
        ActiveState::m_fogStartDensity = GlobalState::m_fogStartDensity;
      }
      if ((mask & 0x80000u) != 0) {
        ActiveState::m_softStateUpdated |= 0x80000u;
        ActiveState::m_fogEnd = GlobalState::m_fogEnd;
      }
    }
  }
}


// ===================================================================================
//  rw::graphics::GlobalState::D3D9RenderStateDispatch -- 0x011f1810
// @ 0x011f1810
// ===================================================================================
void GlobalState::D3D9RenderStateDispatch(void)
{
  u32 wordOff = 0;
  int state = 7;
  do {
    int idx = state;
    for (u32 bits = rwg_D3D9RenderStateToUpdate[wordOff / 4]; bits != 0; bits >>= 1) {
      for (; (bits & 1u) == 0;
           bits >>= (rwgD3D9BitShiftTable[bits & 0xff] & 0x1f))
        idx += (u8)rwgD3D9BitShiftTable[bits & 0xff];

      u32 value = m_renderState[idx];
      if (value != ActiveState::m_renderStateShadow[idx]) {
        typedef void (__stdcall *Fn)(void*, u32, u32);
        Fn fn = *(Fn*)(*(u32*)ActiveState::m_d3d9Device + 0xe4);
        fn(ActiveState::m_d3d9Device, (u32)idx, value);
        ActiveState::m_renderStateShadow[idx] = value;
      }
      ++idx;
    }
    wordOff += 4;
    state += 0x20;
  } while (wordOff < 0x1c);
}


// ===================================================================================
//  rw::graphics::GlobalState::D3D9RasterDispatch -- 0x011f18b0
// @ 0x011f18b0
// ===================================================================================
void GlobalState::D3D9RasterDispatch(void)
{
  u32 stage = 0;
  u32 bits = rwg_D3D9RasterToUpdate;
  do {
    const u32* caps = DevCapsManager::GetD3DCAPS9();
    u32 maxStage = Device::D3D9GetMaxSamplerStage(caps[0xcc / 4]);
    if (maxStage <= stage)
      return;
    if ((bits & 1u) != 0)
      ActiveState::SetTexture(stage, m_raster[stage]);
    bits >>= 1;
    ++stage;
  } while (stage < 0x11u);
}


// ===================================================================================
//  rw::graphics::GlobalState::D3D9PaletteDispatch -- 0x011f1900
// @ 0x011f1900
// ===================================================================================
void GlobalState::D3D9PaletteDispatch(void)
{
  const Palette* palette = m_palette;
  if (m_palette != ActiveState::m_paletteShadow) {
    if (m_palette != 0) {
      {
        typedef void (__stdcall *Fn)(void*, u32, const void*);
        Fn fn = *(Fn*)(*(u32*)ActiveState::m_d3d9Device + 0x11c);
        fn(ActiveState::m_d3d9Device, 0, m_palette);
      }
      {
        typedef void (__stdcall *Fn)(void*, u32);
        Fn fn = *(Fn*)(*(u32*)ActiveState::m_d3d9Device + 0x124);
        fn(ActiveState::m_d3d9Device, 0);
      }
      ActiveState::m_paletteShadow = palette;
      return;
    }
    {
      typedef void (__stdcall *Fn)(void*, u32, const void*);
      Fn fn = *(Fn*)(*(u32*)ActiveState::m_d3d9Device + 0x11c);
      fn(ActiveState::m_d3d9Device, 0, 0);
    }
    ActiveState::m_paletteShadow = palette;
  }
}


// ===================================================================================
//  rw::graphics::GlobalState::D3D9TextureStageStateDispatch -- 0x011f1950
// @ 0x011f1950
// ===================================================================================
void GlobalState::D3D9TextureStageStateDispatch(void)
{
  u32 stage = 0;
  int flat = 0;
  do {
    u32 maxStage = Device::D3D9GetMaxSamplerStage(0xffff0000u);
    if (maxStage <= stage)
      return;
    int type = 1;
    for (u32 bits = rwg_D3D9TextureStageStateToUpdate[stage]; bits != 0; bits >>= 1) {
      for (; (bits & 1u) == 0;
           bits >>= (rwgD3D9BitShiftTable[bits & 0xff] & 0x1f))
        type += (u8)rwgD3D9BitShiftTable[bits & 0xff];

      int fi = flat + type;
      u32 value = *(u32*)(&m_textureStageState[0][0] + fi);
      if (value != ActiveState::m_textureStageStateShadow[fi / 33][fi % 33]) {
        typedef void (__stdcall *Fn)(void*, u32, u32, u32);
        Fn fn = *(Fn*)(*(u32*)ActiveState::m_d3d9Device + 0x10c);
        fn(ActiveState::m_d3d9Device, stage, (u32)type, value);
        ActiveState::m_textureStageStateShadow[fi / 33][fi % 33] = value;
      }
      ++type;
    }
    ++stage;
    flat += 0x21;
  } while (stage < 0x11u);
}


// ===================================================================================
//  rw::graphics::GlobalState::D3D9SamplerStateDispatch -- 0x011f1a10
// @ 0x011f1a10
// ===================================================================================
void GlobalState::D3D9SamplerStateDispatch(void)
{
  u32 stage = 0;
  int flat = 0;
  do {
    const u32* caps = DevCapsManager::GetD3DCAPS9();
    u32 maxStage = Device::D3D9GetMaxSamplerStage(caps[0xcc / 4]);
    if (maxStage <= stage)
      return;

    int type = 1;
    for (u32 bits = rwg_D3D9SamplerStateToUpdate[stage]; bits != 0; bits >>= 1) {
      for (; (bits & 1u) == 0;
           bits >>= (rwgD3D9BitShiftTable[bits & 0xff] & 0x1f))
        type += (u8)rwgD3D9BitShiftTable[bits & 0xff];

      int fi = flat + type;
      u32 value = *(u32*)(&m_samplerState[0][0] + fi);
      if (DAT_016fa3bd != 0 && value == 2 && (type == 6 || type == 5) &&
          m_samplerState[stage][7] == 2)
        value = 3;
      if (value != ActiveState::m_samplerStateShadow[fi / 14][fi % 14]) {
        typedef void (__stdcall *Fn)(void*, u32, u32, u32);
        Fn fn = *(Fn*)(*(u32*)ActiveState::m_d3d9Device + 0x114);
        fn(ActiveState::m_d3d9Device, stage, (u32)type, value);
        ActiveState::m_samplerStateShadow[fi / 14][fi % 14] = value;
      }
      ++type;
    }
    ++stage;
    flat += 0xe;
  } while (stage < 0x11u);
}


// ===================================================================================
//  rw::graphics::GlobalState::D3D9ClearDirtyFlags -- 0x011f1b20
// @ 0x011f1b20
// ===================================================================================
void GlobalState::D3D9ClearDirtyFlags(void)
{
  m_softStateDirty = 0;
  for (int i = 0; i < 7; ++i)
    m_renderStateDirty[i] = 0;
  m_rasterStageDirty = 0;
  m_paletteDirty = 0;
  for (int i = 0; i < 17; ++i) {
    m_samplerStateDirty[i] = 0;
    m_textureStageStateDirty[i] = 0;
  }
}


// ===================================================================================
//  rw::graphics::GlobalState::Dispatch -- 0x011f1c20
// @ 0x011f1c20
// ===================================================================================
void GlobalState::Dispatch(void)
{
  if (m_softStateDirty != 0) {
    D3D9SoftStateDispatch(m_softStateDirty);
    m_softStateDirty = 0;
  }

  rwg_D3D9RasterToUpdate = m_rasterStageDirty;
  if (m_rasterStageDirty != 0) {
    D3D9RasterDispatch();
    m_rasterStageDirty = 0;
  }

  if (m_paletteDirty != 0) {
    D3D9PaletteDispatch();
    m_paletteDirty = 0;
  }

  u32 renderAny = 0;
  for (int i = 0; i < 7; ++i) {
    u32 v = m_renderStateDirty[i];
    rwg_D3D9RenderStateToUpdate[i] = v;
    m_renderStateDirty[i] = 0;
    renderAny |= v;
  }
  if (renderAny != 0)
    D3D9RenderStateDispatch();

  u32 textureAny = 0;
  for (int i = 0; i < 17; ++i) {
    u32 v = m_textureStageStateDirty[i];
    rwg_D3D9TextureStageStateToUpdate[i] = v;
    m_textureStageStateDirty[i] = 0;
    textureAny |= v;
  }
  if (textureAny != 0)
    D3D9TextureStageStateDispatch();

  u32 samplerAny = 0;
  for (int i = 0; i < 17; ++i) {
    u32 v = m_samplerStateDirty[i];
    rwg_D3D9SamplerStateToUpdate[i] = v;
    m_samplerStateDirty[i] = 0;
    samplerAny |= v;
  }
  if (samplerAny != 0)
    D3D9SamplerStateDispatch();
}


// ===================================================================================
//  rw::graphics::GlobalState::D3D9Reset -- 0x011f1d70
//
//  Pushes the full default state to a freshly-reset device, then restores whatever was dirty
//  before the call (so the caller's pending state survives the device reset).
// @ 0x011f1d70
// ===================================================================================
void GlobalState::D3D9Reset(void)
{
  FUN_011f2bf0();
  FUN_011f9560();

  u32 savedRender[7];
  for (int i = 0; i < 7; ++i) {
    savedRender[i] = m_renderStateDirty[i];
    m_renderStateDirty[i] = 0;
    rwg_D3D9RenderStateToUpdate[i] = 0;
  }
  u32 savedSoftState = m_softStateDirty;

  ActiveState::Reset();

  u32 savedRaster = m_rasterStageDirty;
  u32 savedPalette = m_paletteDirty;

  m_renderStateDirty[0] |= 0xf87fb387u;
  m_softStateDirty |= 0xfffffu;
  m_renderStateDirty[1] |= 0x37e200u;
  m_renderStateDirty[3] |= 0xfe000000u;
  m_renderStateDirty[6] |= 0x7ffu;
  m_renderStateDirty[5] |= 0x9fffe3fbu;
  m_renderStateDirty[4] |= 0xdffb3df7u;

  m_rasterStageDirty = 1;
  m_raster[0] = 0;
  m_paletteDirty = 1;
  m_palette = 0;

  u32 savedTextureDirty[17];
  u32 savedSamplerDirty[17];

  savedTextureDirty[0] = m_textureStageStateDirty[0];
  rwg_D3D9TextureStageStateToUpdate[0] = 0;
  m_textureStageStateDirty[0] = 0xee007ffu;

  const u32* caps = DevCapsManager::GetD3DCAPS9();
  int constEdgeCaps = ((caps[0x20 / 4] & 0x8000u) != 0);
  if (constEdgeCaps)
    m_textureStageStateDirty[0] |= 0x80000000u;

  savedSamplerDirty[0] = m_samplerStateDirty[0];
  rwg_D3D9SamplerStateToUpdate[0] = 0;
  m_samplerStateDirty[0] = 0x1fffu;

  int idx = 1;
  do {
    m_raster[idx] = 0;
    rwg_D3D9TextureStageStateToUpdate[idx] = 0;
    m_rasterStageDirty |= 1u << (idx & 0x1f);
    savedTextureDirty[idx] = m_textureStageStateDirty[idx];
    m_textureStageStateDirty[idx] = 0xee007ffu;
    if (constEdgeCaps)
      m_textureStageStateDirty[idx] = 0x8ee007ffu;
    savedSamplerDirty[idx] = m_samplerStateDirty[idx];
    rwg_D3D9SamplerStateToUpdate[idx] = 0;
    m_samplerStateDirty[idx] = 0x1fffu;
    ++idx;
  } while (idx < 17);

  Dispatch();
  D3D9ClearDirtyFlags();

  m_softStateDirty = savedSoftState;
  for (int i = 0; i < 7; ++i)
    m_renderStateDirty[i] = savedRender[i];
  m_rasterStageDirty = savedRaster;
  m_paletteDirty = savedPalette;
  for (int i = 0; i < 17; ++i) {
    m_samplerStateDirty[i] = savedSamplerDirty[i];
    m_textureStageStateDirty[i] = savedTextureDirty[i];
  }
}
