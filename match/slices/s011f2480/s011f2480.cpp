// slice s011f2480 -- rw::graphics::GlobalState::D3D9Initialize (RenderWare 4, rwgdrvglobalstate.cpp).
//
// Fills the software mirror of the D3D9 device state with the defaults: identity transform, white
// material colour, black ambient, every render state, texture-stage state and sampler state of the
// 17 stages, the matching dirty masks, the fog state; then pushes it all to the device (Dispatch)
// and clears the dirty flags.  The dev build's rwgdrvglobalstate.obj was compiled by cl 13.10.3077
// (its PDB S_COMPILE2 record), so this is /vc71 code; the module uses SSE floats.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "game/types.h"
#include <xmmintrin.h>
#include "_D3DRENDERSTATETYPE.h"
#include "_D3DSAMPLERSTATETYPE.h"
#include "_D3DCAPS9.h"

typedef unsigned int u32;

// ---- D3D9 values used below (d3d9types.h / d3d9caps.h) ----------------------------------------
enum _D3DTEXTURESTAGESTATETYPE {
  D3DTSS_COLOROP = 1,
  D3DTSS_COLORARG1 = 2,
  D3DTSS_COLORARG2 = 3,
  D3DTSS_ALPHAOP = 4,
  D3DTSS_ALPHAARG1 = 5,
  D3DTSS_ALPHAARG2 = 6,
  D3DTSS_BUMPENVMAT00 = 7,
  D3DTSS_BUMPENVMAT01 = 8,
  D3DTSS_BUMPENVMAT10 = 9,
  D3DTSS_BUMPENVMAT11 = 10,
  D3DTSS_TEXCOORDINDEX = 11,
  D3DTSS_BUMPENVLSCALE = 22,
  D3DTSS_BUMPENVLOFFSET = 23,
  D3DTSS_TEXTURETRANSFORMFLAGS = 24,
  D3DTSS_COLORARG0 = 26,
  D3DTSS_ALPHAARG0 = 27,
  D3DTSS_RESULTARG = 28,
  D3DTSS_CONSTANT = 32
};

enum {
  D3DZB_TRUE = 1,
  D3DFILL_SOLID = 3,
  D3DSHADE_GOURAUD = 2,
  D3DBLEND_ZERO = 1,
  D3DBLEND_ONE = 2,
  D3DBLEND_SRCALPHA = 5,
  D3DBLEND_INVSRCALPHA = 6,
  D3DCULL_CW = 2,
  D3DCMP_LESSEQUAL = 4,
  D3DCMP_GREATER = 5,
  D3DCMP_ALWAYS = 8,
  D3DSTENCILOP_KEEP = 1,
  D3DMCS_MATERIAL = 0,
  D3DVBF_DISABLE = 0,
  D3DPATCHEDGE_DISCRETE = 0,
  D3DDMT_DISABLE = 1,
  D3DBLENDOP_ADD = 1,
  D3DDEGREE_CUBIC = 3,
  D3DDEGREE_LINEAR = 1,
  D3DCOLORWRITEENABLE_ALL = 0xf,

  D3DTOP_DISABLE = 1,
  D3DTOP_SELECTARG1 = 2,
  D3DTA_DIFFUSE = 0,
  D3DTA_CURRENT = 1,
  D3DTSS_TCI_PASSTHRU = 0,
  D3DTTFF_DISABLE = 0,

  D3DTADDRESS_WRAP = 1,
  D3DTEXF_NONE = 0,
  D3DTEXF_POINT = 1,

  D3DPMISCCAPS_PERSTAGECONSTANT = 0x8000
};

namespace rw {

// The integer views are volatile in the original (dev PDB: LF_MODIFIER volatile on nInt and nUInt).
union SplitBits {
  float nReal;
  volatile int nInt;
  volatile unsigned int nUInt;
};

namespace math { namespace vpu {
enum MatrixType { MATRIXTYPE_IDENTITY = 4 };
struct __declspec(align(16)) Matrix44Affine {
  __m128 xAxis, yAxis, zAxis, wAxis;
};
}}  // namespace math::vpu

namespace graphics {

enum FogType { FOGTYPE_NONE = 0 };

struct RwRGBRealTag  { float red, green, blue; };
struct RwRGBARealTag { float red, green, blue, alpha; };
struct Raster;
struct Palette;

class DevCapsManager {
public:
  static const _D3DCAPS9* GetD3DCAPS9(void);     // 0x011f8af0
};

// ---- update / validity masks (an anonymous namespace in the original) ------------------------
extern u32 rwg_D3D9TextureStageStateToUpdate[17];   // 0x016f95a8
extern u32 rwg_D3D9SamplerStateToUpdate[17];        // 0x016f95f0
extern u32 rwg_D3D9RenderStateToUpdate[7];          // 0x016f9634
extern u32 rwg_D3D9AllValidRenderState[7];          // 0x016fa4c0
extern u32 rwg_D3D9AllValidTextureStageState;       // 0x016fa4dc
extern u32 rwg_D3D9AllValidSamplerState;            // 0x016fa4e0


class GlobalState {
public:
  static void Dispatch(void);                    // 0x011f1c20
  static void D3D9ClearDirtyFlags(void);         // 0x011f1b20
  static void D3D9Initialize(void);              // 0x011f2480

  // inline in the original (dev-build PDB: "dev only")
  static void D3D9AddRenderStateFlags(u32 index, u32 flags);
  static void D3D9ForcedSetRenderState(u32 state, u32 value);
  static void D3D9AddTextureStageStateFlags(u32 stage, u32 flags);
  static void D3D9SetTextureStageState(u32 stage, u32 state, u32 value);
  static void D3D9AddSamplerStateFlags(u32 stage, u32 flags);
  static void SetRasterState(u32 stage, _D3DSAMPLERSTATETYPE state, u32 value);
  static void D3D9AddRasterFlags(u32 flags);
  static void SetRaster(u32 stage, const Raster* raster);
  static void D3D9AddPaletteFlag(void);
  static void SetPalette(const Palette* palette);

  static u32  m_renderState[210];                 // 0x016f91e0
  static u32  m_softStateDirty;                   // 0x016f9528
  static u32  m_samplerStateDirty[17];            // 0x016f9530
  static float m_fogStartDensity;                 // 0x016f9594
  static RwRGBRealTag m_ambient;                  // 0x016f9598
  static const Raster* m_raster[17];              // 0x016f9650
  static RwRGBRealTag m_fogColor;                 // 0x016f9694
  static math::vpu::MatrixType m_transformType;   // 0x016f96a0
  static const Palette* m_palette;                // 0x016f96a4
  static RwRGBARealTag m_color;                   // 0x016f96a8
  static u32  m_textureStageState[17][33];        // 0x016f96b8
  static FogType m_fogType;                       // 0x016f9f7c
  static u32  m_textureStageStateDirty[17];       // 0x016f9f80
  static u32  m_samplerState[17][14];             // 0x016f9fc8
  static math::vpu::Matrix44Affine* m_transform;  // 0x016fa380
  static u32  m_paletteDirty;                     // 0x016fa384
  static float m_fogEnd;                          // 0x016fa388
  static u32  m_renderStateDirty[7];              // 0x016fa38c
  static u32  m_rasterStageDirty;                 // 0x016fa3a8
  static math::vpu::Matrix44Affine m_transformLocalCopy;  // 0x016fa4f0
};

}  // namespace graphics
}  // namespace rw

using namespace rw;
using namespace rw::graphics;


// The render states are numbered from D3DRS_ZENABLE (7) in the dirty and valid masks, the
// texture-stage and sampler states from 1.
inline void GlobalState::D3D9AddRenderStateFlags(u32 index, u32 flags)
{
  m_renderStateDirty[index] |= flags;
}

inline void GlobalState::D3D9ForcedSetRenderState(u32 state, u32 value)
{
  const u32 bit = state - D3DRS_ZENABLE;
  D3D9AddRenderStateFlags(bit >> 5, 1u << (bit & 31));
  m_renderState[state] = value;
}

inline void GlobalState::D3D9AddTextureStageStateFlags(u32 stage, u32 flags)
{
  m_textureStageStateDirty[stage] |= flags;
}

inline void GlobalState::D3D9SetTextureStageState(u32 stage, u32 state, u32 value)
{
  D3D9AddTextureStageStateFlags(stage, 1u << (state - 1));
  m_textureStageState[stage][state] = value;
}

inline void GlobalState::D3D9AddSamplerStateFlags(u32 stage, u32 flags)
{
  m_samplerStateDirty[stage] |= flags;
}

inline void GlobalState::SetRasterState(u32 stage, _D3DSAMPLERSTATETYPE state, u32 value)
{
  D3D9AddSamplerStateFlags(stage, 1u << (state - 1));
  m_samplerState[stage][state] = value;
}

inline void GlobalState::D3D9AddRasterFlags(u32 flags)
{
  m_rasterStageDirty |= flags;
}

inline void GlobalState::SetRaster(u32 stage, const Raster* raster)
{
  D3D9AddRasterFlags(1u << stage);
  m_raster[stage] = raster;
}

inline void GlobalState::D3D9AddPaletteFlag(void)
{
  m_paletteDirty |= 1;
}

inline void GlobalState::SetPalette(const Palette* palette)
{
  D3D9AddPaletteFlag();
  m_palette = palette;
}

// @ 0x011f2480
void GlobalState::D3D9Initialize(void)
{
  // ---- soft state
  m_transformType = math::vpu::MATRIXTYPE_IDENTITY;
  const __m128 xAxis = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
  const __m128 yAxis = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
  const __m128 zAxis = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
  const __m128 wAxis = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

  for (int w = 0; w < 7; ++w) {
    m_renderStateDirty[w] = 0;
    rwg_D3D9RenderStateToUpdate[w] = 0;
  }
  m_softStateDirty = 0;
  m_rasterStageDirty = 0;
  m_paletteDirty = 0;

  m_transform = &m_transformLocalCopy;
  m_transformLocalCopy.xAxis = xAxis;
  m_transformLocalCopy.yAxis = yAxis;
  m_transformLocalCopy.zAxis = zAxis;
  m_transformLocalCopy.wAxis = wAxis;

  m_color.red = 1.0f;
  m_color.green = 1.0f;
  m_color.blue = 1.0f;
  m_color.alpha = 1.0f;
  m_ambient.red = 0.0f;
  m_ambient.green = 0.0f;
  m_ambient.blue = 0.0f;

  // ---- render states
  SplitBits splitZero, splitOne, split64;
  splitZero.nReal = 0.0f;
  splitOne.nReal = 1.0f;
  split64.nReal = 64.0f;

  D3D9ForcedSetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
  D3D9ForcedSetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
  D3D9ForcedSetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
  D3D9ForcedSetRenderState(D3DRS_ZWRITEENABLE, 1);
  D3D9ForcedSetRenderState(D3DRS_ALPHATESTENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_LASTPIXEL, 1);
  D3D9ForcedSetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  D3D9ForcedSetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
  D3D9ForcedSetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
  D3D9ForcedSetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
  D3D9ForcedSetRenderState(D3DRS_ALPHAREF, 0);
  D3D9ForcedSetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
  D3D9ForcedSetRenderState(D3DRS_DITHERENABLE, 1);
  D3D9ForcedSetRenderState(D3DRS_ALPHABLENDENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_FOGENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_SPECULARENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_FOGCOLOR, 0xffffffff);
  D3D9ForcedSetRenderState(D3DRS_FOGTABLEMODE, 0);
  D3D9ForcedSetRenderState(D3DRS_FOGSTART, 0);
  D3D9ForcedSetRenderState(D3DRS_FOGEND, splitOne.nUInt);
  D3D9ForcedSetRenderState(D3DRS_FOGDENSITY, splitOne.nUInt);
  rwg_D3D9AllValidRenderState[0] |= m_renderStateDirty[0];
  D3D9ForcedSetRenderState(D3DRS_RANGEFOGENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_STENCILENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
  D3D9ForcedSetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
  D3D9ForcedSetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
  D3D9ForcedSetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
  D3D9ForcedSetRenderState(D3DRS_STENCILREF, 0);
  D3D9ForcedSetRenderState(D3DRS_STENCILMASK, 0xffffffff);
  D3D9ForcedSetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
  D3D9ForcedSetRenderState(D3DRS_TEXTUREFACTOR, 0);
  rwg_D3D9AllValidRenderState[1] |= m_renderStateDirty[1];
  D3D9ForcedSetRenderState(D3DRS_WRAP0, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP1, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP2, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP3, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP4, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP5, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP6, 0);
  rwg_D3D9AllValidRenderState[3] |= m_renderStateDirty[3];
  D3D9ForcedSetRenderState(D3DRS_WRAP7, 0);
  D3D9ForcedSetRenderState(D3DRS_CLIPPING, 1);
  D3D9ForcedSetRenderState(D3DRS_LIGHTING, 0);
  D3D9ForcedSetRenderState(D3DRS_AMBIENT, 0);
  D3D9ForcedSetRenderState(D3DRS_FOGVERTEXMODE, 0);
  D3D9ForcedSetRenderState(D3DRS_COLORVERTEX, 1);
  D3D9ForcedSetRenderState(D3DRS_LOCALVIEWER, 0);
  D3D9ForcedSetRenderState(D3DRS_NORMALIZENORMALS, 0);
  D3D9ForcedSetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
  D3D9ForcedSetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
  D3D9ForcedSetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
  D3D9ForcedSetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
  D3D9ForcedSetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
  D3D9ForcedSetRenderState(D3DRS_CLIPPLANEENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_POINTSIZE, split64.nUInt);
  D3D9ForcedSetRenderState(D3DRS_POINTSIZE_MIN, 0);
  D3D9ForcedSetRenderState(D3DRS_POINTSPRITEENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_POINTSCALEENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_POINTSCALE_A, splitOne.nUInt);
  D3D9ForcedSetRenderState(D3DRS_POINTSCALE_B, splitZero.nUInt);
  D3D9ForcedSetRenderState(D3DRS_POINTSCALE_C, splitZero.nUInt);
  D3D9ForcedSetRenderState(D3DRS_MULTISAMPLEANTIALIAS, 1);
  D3D9ForcedSetRenderState(D3DRS_MULTISAMPLEMASK, 0xffffffff);
  D3D9ForcedSetRenderState(D3DRS_PATCHEDGESTYLE, D3DPATCHEDGE_DISCRETE);
  D3D9ForcedSetRenderState(D3DRS_DEBUGMONITORTOKEN, D3DDMT_DISABLE);
  D3D9ForcedSetRenderState(D3DRS_POINTSIZE_MAX, split64.nUInt);
  rwg_D3D9AllValidRenderState[4] |= m_renderStateDirty[4];
  D3D9ForcedSetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
  D3D9ForcedSetRenderState(D3DRS_TWEENFACTOR, splitZero.nUInt);
  D3D9ForcedSetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
  D3D9ForcedSetRenderState(D3DRS_POSITIONDEGREE, D3DDEGREE_CUBIC);
  D3D9ForcedSetRenderState(D3DRS_NORMALDEGREE, D3DDEGREE_LINEAR);
  D3D9ForcedSetRenderState(D3DRS_SCISSORTESTENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, 0);
  D3D9ForcedSetRenderState(D3DRS_ANTIALIASEDLINEENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_ADAPTIVETESS_X, splitZero.nUInt);
  D3D9ForcedSetRenderState(D3DRS_ADAPTIVETESS_Y, splitZero.nUInt);
  D3D9ForcedSetRenderState(D3DRS_ADAPTIVETESS_Z, splitOne.nUInt);
  D3D9ForcedSetRenderState(D3DRS_ADAPTIVETESS_W, splitZero.nUInt);
  D3D9ForcedSetRenderState(D3DRS_ENABLEADAPTIVETESSELLATION, 0);
  D3D9ForcedSetRenderState(D3DRS_TWOSIDEDSTENCILMODE, 0);
  D3D9ForcedSetRenderState(D3DRS_CCW_STENCILFAIL, D3DSTENCILOP_KEEP);
  D3D9ForcedSetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_KEEP);
  D3D9ForcedSetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP_KEEP);
  D3D9ForcedSetRenderState(D3DRS_CCW_STENCILFUNC, D3DCMP_ALWAYS);
  D3D9ForcedSetRenderState(D3DRS_COLORWRITEENABLE1, D3DCOLORWRITEENABLE_ALL);
  D3D9ForcedSetRenderState(D3DRS_COLORWRITEENABLE2, D3DCOLORWRITEENABLE_ALL);
  D3D9ForcedSetRenderState(D3DRS_COLORWRITEENABLE3, D3DCOLORWRITEENABLE_ALL);
  D3D9ForcedSetRenderState(D3DRS_BLENDFACTOR, 0xffffffff);
  D3D9ForcedSetRenderState(D3DRS_SRGBWRITEENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_DEPTHBIAS, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP8, 0);
  rwg_D3D9AllValidRenderState[5] |= m_renderStateDirty[5];
  D3D9ForcedSetRenderState(D3DRS_WRAP9, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP10, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP11, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP12, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP13, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP14, 0);
  D3D9ForcedSetRenderState(D3DRS_WRAP15, 0);
  D3D9ForcedSetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, 0);
  D3D9ForcedSetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
  D3D9ForcedSetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
  D3D9ForcedSetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
  rwg_D3D9AllValidRenderState[6] |= m_renderStateDirty[6];

  // ---- raster and palette
  SetRaster(0, 0);
  SetPalette(0);

  // ---- texture stage 0
  rwg_D3D9TextureStageStateToUpdate[0] = 0;
  m_textureStageStateDirty[0] = 0;
  D3D9SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
  D3D9SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
  D3D9SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
  D3D9SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
  D3D9SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
  D3D9SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
  D3D9SetTextureStageState(0, D3DTSS_BUMPENVMAT00, 0);
  D3D9SetTextureStageState(0, D3DTSS_BUMPENVMAT01, 0);
  D3D9SetTextureStageState(0, D3DTSS_BUMPENVMAT10, 0);
  D3D9SetTextureStageState(0, D3DTSS_BUMPENVMAT11, 0);
  D3D9SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU);
  D3D9SetTextureStageState(0, D3DTSS_BUMPENVLSCALE, 0);
  D3D9SetTextureStageState(0, D3DTSS_BUMPENVLOFFSET, 0);
  D3D9SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
  D3D9SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_CURRENT);
  D3D9SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
  D3D9SetTextureStageState(0, D3DTSS_RESULTARG, D3DTA_CURRENT);
  rwg_D3D9AllValidTextureStageState |= 0x0ee007ff;

  const _D3DCAPS9* d3dcaps9 = DevCapsManager::GetD3DCAPS9();
  if (d3dcaps9->PrimitiveMiscCaps & D3DPMISCCAPS_PERSTAGECONSTANT) {
    D3D9SetTextureStageState(0, D3DTSS_CONSTANT, 0);
    rwg_D3D9AllValidTextureStageState |= 0x80000000;
  }

  // ---- sampler stage 0
  rwg_D3D9AllValidSamplerState |= 0x1fff;
  rwg_D3D9SamplerStateToUpdate[0] = 0;
  m_samplerStateDirty[0] = 0;
  SetRasterState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
  SetRasterState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
  SetRasterState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
  SetRasterState(0, D3DSAMP_BORDERCOLOR, 0);
  SetRasterState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
  SetRasterState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
  SetRasterState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
  SetRasterState(0, D3DSAMP_MIPMAPLODBIAS, 0);
  SetRasterState(0, D3DSAMP_MAXMIPLEVEL, 0);
  SetRasterState(0, D3DSAMP_MAXANISOTROPY, 1);
  SetRasterState(0, D3DSAMP_SRGBTEXTURE, 0);
  SetRasterState(0, D3DSAMP_ELEMENTINDEX, 0);
  SetRasterState(0, D3DSAMP_DMAPOFFSET, 0x100);

  // ---- stages 1..16
  for (u32 i = 1; i < 17; ++i) {
    SetRaster(i, 0);
    rwg_D3D9TextureStageStateToUpdate[i] = 0;
    m_textureStageStateDirty[i] = 0;
    D3D9SetTextureStageState(i, D3DTSS_COLOROP, D3DTOP_DISABLE);
    D3D9SetTextureStageState(i, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    D3D9SetTextureStageState(i, D3DTSS_COLORARG2, D3DTA_CURRENT);
    D3D9SetTextureStageState(i, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    D3D9SetTextureStageState(i, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    D3D9SetTextureStageState(i, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
    D3D9SetTextureStageState(i, D3DTSS_BUMPENVMAT00, 0);
    D3D9SetTextureStageState(i, D3DTSS_BUMPENVMAT01, 0);
    D3D9SetTextureStageState(i, D3DTSS_BUMPENVMAT10, 0);
    D3D9SetTextureStageState(i, D3DTSS_BUMPENVMAT11, 0);
    D3D9SetTextureStageState(i, D3DTSS_TEXCOORDINDEX, i);
    D3D9SetTextureStageState(i, D3DTSS_BUMPENVLSCALE, 0);
    D3D9SetTextureStageState(i, D3DTSS_BUMPENVLOFFSET, 0);
    D3D9SetTextureStageState(i, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    D3D9SetTextureStageState(i, D3DTSS_COLORARG0, D3DTA_CURRENT);
    D3D9SetTextureStageState(i, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
    D3D9SetTextureStageState(i, D3DTSS_RESULTARG, D3DTA_CURRENT);
    if (d3dcaps9->PrimitiveMiscCaps & D3DPMISCCAPS_PERSTAGECONSTANT)
      D3D9SetTextureStageState(i, D3DTSS_CONSTANT, 0);

    rwg_D3D9SamplerStateToUpdate[i] = 0;
    m_samplerStateDirty[i] = 0;
    SetRasterState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    SetRasterState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    SetRasterState(i, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
    SetRasterState(i, D3DSAMP_BORDERCOLOR, 0);
    SetRasterState(i, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
    SetRasterState(i, D3DSAMP_MINFILTER, D3DTEXF_POINT);
    SetRasterState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
    SetRasterState(i, D3DSAMP_MIPMAPLODBIAS, 0);
    SetRasterState(i, D3DSAMP_MAXMIPLEVEL, 0);
    SetRasterState(i, D3DSAMP_MAXANISOTROPY, 1);
    SetRasterState(i, D3DSAMP_SRGBTEXTURE, 0);
    SetRasterState(i, D3DSAMP_ELEMENTINDEX, 0);
    SetRasterState(i, D3DSAMP_DMAPOFFSET, 0x100);
  }

  // ---- fog
  m_fogStartDensity = 0.0f;
  m_fogType = FOGTYPE_NONE;
  m_fogEnd = 1.0f;
  m_fogColor.red = 1.0f;
  m_fogColor.green = 1.0f;
  m_fogColor.blue = 1.0f;

  Dispatch();
  D3D9ClearDirtyFlags();
}
