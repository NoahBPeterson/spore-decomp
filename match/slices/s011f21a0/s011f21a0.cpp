// Slice s011f21a0 -- RenderWare graphics: rw::graphics::GlobalState::D3D9Initialize (0x011f2480, 1840 bytes).
//
// Resets the software mirror of the D3D9 device state to its power-on defaults and marks what has to
// be pushed to the device: m_renderState / m_textureStageState / m_samplerState get the D3D9 default
// table (a few entries deliberately differ from Microsoft's defaults, e.g. SRCBLEND = SRCALPHA,
// DESTBLEND = INVSRCALPHA, CULLMODE = CW, ALPHAFUNC = GREATER, POINTSIZE = 64), the "dirty" and "valid"
// bit masks per state class are initialised, the 16 extra texture/sampler stages are filled with their
// defaults, and the cached transform is reset to the identity.  PERSTAGECONSTANT support (D3DCAPS9)
// adds the D3DTSS_CONSTANT bit.  Ends with GlobalState::Dispatch() and D3D9ClearDirtyFlags().
//
// Member names are the dev-PDB / pdb_globals names (m_renderState, m_renderStateDirty, ...,
// rwg_D3D9AllValidRenderState).  The store order is Claude's grouping, not the original's (cl schedules
// these stores by register value, so the original order can't be read back).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include <windows.h>
#include <d3d9types.h>
#include <d3d9caps.h>
#include <xmmintrin.h>
#include "types.h"

namespace rw {
namespace graphics {

typedef uint32_t u32;

// Float bits stored into a DWORD render-state slot (D3D9 convention).
static inline u32 F2D(float f) {
  union {
    float f;
    u32 d;
  } u;
  u.f = f;
  return u.d;
}

struct RwRGBRealTag {
  float red, green, blue;
};
struct RwRGBARealTag {
  float red, green, blue, alpha;
};

// Rows are held as __m128 values: built through an aligned float temp, copied with movaps.
static inline __m128 MakeVector4(float x, float y, float z, float w) {
  __declspec(align(16)) float t[4] = {x, y, z, w};
  return *(__m128*)t;
}
struct Matrix44Affine {
  __m128 mRow[4];
};

class DevCapsManager {
 public:
  static const D3DCAPS9* GetD3DCAPS9();  // 0x011f8af0
};

class GlobalState {
 public:
  static void D3D9Initialize();  // 0x011f2480
  static void Dispatch();        // 0x011f1c20
  static void D3D9ClearDirtyFlags();  // 0x011f1b20

  static u32 m_renderState[210];                 // 0x016f91e0
  static u32 m_softStateDirty;                   // 0x016f9528
  static u32 m_samplerStateDirty[17];            // 0x016f9530
  static float m_fogStartDensity;                // 0x016f9594
  static RwRGBRealTag m_ambient;                 // 0x016f9598
  static u32 m_raster[17];                       // 0x016f9650
  static RwRGBRealTag m_fogColor;                // 0x016f9694
  static int m_transformType;                    // 0x016f96a0
  static u32 m_palette;                          // 0x016f96a4
  static RwRGBARealTag m_color;                  // 0x016f96a8
  static u32 m_textureStageState[17][33];        // 0x016f96b8
  static int m_fogType;                          // 0x016f9f7c
  static u32 m_textureStageStateDirty[17];       // 0x016f9f80
  static u32 m_samplerState[17][14];             // 0x016f9fc8
  static Matrix44Affine* m_transform;            // 0x016fa380
  static u32 m_paletteDirty;                     // 0x016fa384
  static float m_fogEnd;                         // 0x016fa388
  static u32 m_renderStateDirty[7];              // 0x016fa38c
  static u32 m_rasterStageDirty;                 // 0x016fa3a8
  static Matrix44Affine m_transformLocalCopy;    // 0x016fa4f0
};

// File-scope helpers of the D3D9 backend (anonymous namespace in the original).
extern u32 rwg_D3D9RenderStateToUpdate[7];        // 0x016f9634
extern u32 rwg_D3D9TextureStageStateToUpdate[17]; // 0x016f95a8
extern u32 rwg_D3D9SamplerStateToUpdate[17];      // 0x016f95f0
extern u32 rwg_D3D9AllValidRenderState[7];        // 0x016fa4c0
extern u32 rwg_D3D9AllValidTextureStageState;     // 0x016fa4dc
extern u32 rwg_D3D9AllValidSamplerState;          // 0x016fa4e0

// @ 0x011F2480
void GlobalState::D3D9Initialize() {
  m_transformType = 4;
  m_renderState[D3DRS_ZFUNC] = D3DCMP_LESSEQUAL;
  m_renderState[D3DRS_SRCBLEND] = D3DBLEND_SRCALPHA;
  m_renderState[D3DRS_ALPHAFUNC] = D3DCMP_GREATER;
  m_ambient.red = 0.0f;
  m_ambient.green = 0.0f;
  m_ambient.blue = 0.0f;
  m_renderState[D3DRS_FOGEND] = F2D(1.0f);
  rwg_D3D9RenderStateToUpdate[0] = 0;
  rwg_D3D9RenderStateToUpdate[1] = 0;
  m_renderStateDirty[2] = 0;
  rwg_D3D9RenderStateToUpdate[2] = 0;
  rwg_D3D9RenderStateToUpdate[3] = 0;
  rwg_D3D9RenderStateToUpdate[4] = 0;
  rwg_D3D9RenderStateToUpdate[5] = 0;
  rwg_D3D9RenderStateToUpdate[6] = 0;
  m_softStateDirty = 0;

  // Cached transform: identity.
  m_transform = &m_transformLocalCopy;
  m_transformLocalCopy.mRow[0] = MakeVector4(1.0f, 0.0f, 0.0f, 0.0f);
  m_transformLocalCopy.mRow[1] = MakeVector4(0.0f, 1.0f, 0.0f, 0.0f);
  m_transformLocalCopy.mRow[2] = MakeVector4(0.0f, 0.0f, 1.0f, 0.0f);
  m_transformLocalCopy.mRow[3] = MakeVector4(0.0f, 0.0f, 0.0f, 1.0f);
  m_color.red = 1.0f;
  m_color.green = 1.0f;
  m_color.blue = 1.0f;
  m_color.alpha = 1.0f;

  // Render states (D3D9 default table, see the file comment for the deliberate deviations).
  m_renderState[D3DRS_ZENABLE] = D3DZB_TRUE;
  m_renderState[D3DRS_FILLMODE] = D3DFILL_SOLID;
  m_renderState[D3DRS_SHADEMODE] = D3DSHADE_GOURAUD;
  m_renderState[D3DRS_ZWRITEENABLE] = TRUE;
  m_renderState[D3DRS_ALPHATESTENABLE] = FALSE;
  m_renderState[D3DRS_LASTPIXEL] = TRUE;
  m_renderState[D3DRS_DESTBLEND] = D3DBLEND_INVSRCALPHA;
  m_renderState[D3DRS_CULLMODE] = D3DCULL_CW;
  m_renderState[D3DRS_ALPHAREF] = 0;
  m_renderState[D3DRS_DITHERENABLE] = TRUE;
  m_renderState[D3DRS_ALPHABLENDENABLE] = FALSE;
  m_renderState[D3DRS_FOGENABLE] = FALSE;
  m_renderState[D3DRS_SPECULARENABLE] = FALSE;
  m_renderState[D3DRS_FOGCOLOR] = 0xffffffff;
  m_renderState[D3DRS_FOGTABLEMODE] = D3DFOG_NONE;
  m_renderState[D3DRS_FOGSTART] = 0;
  m_renderStateDirty[0] = 0xf87fb387;
  m_renderState[D3DRS_FOGDENSITY] = F2D(1.0f);
  rwg_D3D9AllValidRenderState[0] |= 0xf87fb387;
  m_renderStateDirty[1] = 0x3fe200;
  rwg_D3D9AllValidRenderState[1] |= 0x3fe200;
  m_renderStateDirty[3] = 0xfe000000;
  m_renderState[D3DRS_POINTSIZE] = F2D(64.0f);
  m_renderState[D3DRS_POINTSCALE_A] = F2D(1.0f);
  m_renderState[D3DRS_POINTSCALE_B] = F2D(0.0f);
  m_renderState[D3DRS_POINTSCALE_C] = F2D(0.0f);
  rwg_D3D9AllValidRenderState[3] |= 0xfe000000;
  m_renderState[D3DRS_POINTSIZE_MAX] = F2D(64.0f);
  m_renderStateDirty[4] = 0xdffb3df7;
  m_renderState[D3DRS_TWEENFACTOR] = F2D(0.0f);
  rwg_D3D9AllValidRenderState[4] |= 0xdffb3df7;
  m_renderState[D3DRS_ADAPTIVETESS_X] = F2D(0.0f);
  m_renderState[D3DRS_RANGEFOGENABLE] = FALSE;
  m_renderState[D3DRS_STENCILENABLE] = FALSE;
  m_renderState[D3DRS_STENCILFAIL] = D3DSTENCILOP_KEEP;
  m_renderState[D3DRS_STENCILZFAIL] = D3DSTENCILOP_KEEP;
  m_renderState[D3DRS_STENCILPASS] = D3DSTENCILOP_KEEP;
  m_renderState[D3DRS_STENCILFUNC] = D3DCMP_ALWAYS;
  m_renderState[D3DRS_STENCILREF] = 0;
  m_renderState[D3DRS_STENCILMASK] = 0xffffffff;
  m_renderState[D3DRS_STENCILWRITEMASK] = 0xffffffff;
  m_renderState[D3DRS_TEXTUREFACTOR] = 0;
  m_renderState[D3DRS_WRAP0] = 0;
  m_renderState[D3DRS_WRAP1] = 0;
  m_renderState[D3DRS_WRAP2] = 0;
  m_renderState[D3DRS_WRAP3] = 0;
  m_renderState[D3DRS_WRAP4] = 0;
  m_renderState[D3DRS_WRAP5] = 0;
  m_renderState[D3DRS_WRAP6] = 0;
  m_renderState[D3DRS_WRAP7] = 0;
  m_renderState[D3DRS_CLIPPING] = TRUE;
  m_renderState[D3DRS_LIGHTING] = FALSE;
  m_renderState[D3DRS_AMBIENT] = 0;
  m_renderState[D3DRS_FOGVERTEXMODE] = D3DFOG_NONE;
  m_renderState[D3DRS_COLORVERTEX] = TRUE;
  m_renderState[D3DRS_LOCALVIEWER] = FALSE;
  m_renderState[D3DRS_NORMALIZENORMALS] = FALSE;
  m_renderState[D3DRS_DIFFUSEMATERIALSOURCE] = D3DMCS_MATERIAL;
  m_renderState[D3DRS_SPECULARMATERIALSOURCE] = D3DMCS_MATERIAL;
  m_renderState[D3DRS_AMBIENTMATERIALSOURCE] = D3DMCS_MATERIAL;
  m_renderState[D3DRS_EMISSIVEMATERIALSOURCE] = D3DMCS_MATERIAL;
  m_renderState[D3DRS_VERTEXBLEND] = D3DVBF_DISABLE;
  m_renderState[D3DRS_CLIPPLANEENABLE] = 0;
  m_renderState[D3DRS_POINTSIZE_MIN] = 0;
  m_renderState[D3DRS_POINTSPRITEENABLE] = FALSE;
  m_renderState[D3DRS_POINTSCALEENABLE] = FALSE;
  m_renderState[D3DRS_MULTISAMPLEANTIALIAS] = TRUE;
  m_renderState[D3DRS_MULTISAMPLEMASK] = 0xffffffff;
  m_renderState[D3DRS_PATCHEDGESTYLE] = D3DPATCHEDGE_DISCRETE;
  m_renderState[D3DRS_DEBUGMONITORTOKEN] = D3DDMT_ENABLE;
  m_renderState[D3DRS_INDEXEDVERTEXBLENDENABLE] = FALSE;
  m_renderState[D3DRS_COLORWRITEENABLE] = 0xf;
  m_renderState[D3DRS_BLENDOP] = D3DBLENDOP_ADD;
  m_renderState[D3DRS_POSITIONDEGREE] = D3DDEGREE_CUBIC;
  m_renderState[D3DRS_NORMALDEGREE] = D3DDEGREE_LINEAR;
  m_renderState[D3DRS_SCISSORTESTENABLE] = FALSE;
  m_renderState[D3DRS_SLOPESCALEDEPTHBIAS] = 0;
  m_renderState[D3DRS_ANTIALIASEDLINEENABLE] = FALSE;
  m_renderState[D3DRS_ADAPTIVETESS_Y] = F2D(0.0f);
  m_renderState[D3DRS_COLORWRITEENABLE1] = 0xf;
  m_renderState[D3DRS_COLORWRITEENABLE2] = 0xf;
  m_renderState[D3DRS_COLORWRITEENABLE3] = 0xf;
  m_renderState[D3DRS_ADAPTIVETESS_Z] = F2D(1.0f);
  m_renderState[D3DRS_BLENDFACTOR] = 0xffffffff;
  m_renderState[D3DRS_ADAPTIVETESS_W] = F2D(0.0f);
  m_renderStateDirty[5] = 0x9fffe3fb;
  rwg_D3D9AllValidRenderState[5] |= 0x9fffe3fb;
  m_renderStateDirty[6] = 0x7ff;
  m_renderState[D3DRS_ENABLEADAPTIVETESSELLATION] = FALSE;
  m_renderState[D3DRS_TWOSIDEDSTENCILMODE] = FALSE;
  m_renderState[D3DRS_CCW_STENCILFAIL] = D3DSTENCILOP_KEEP;
  m_renderState[D3DRS_CCW_STENCILZFAIL] = D3DSTENCILOP_KEEP;
  m_renderState[D3DRS_CCW_STENCILPASS] = D3DSTENCILOP_KEEP;
  m_renderState[D3DRS_CCW_STENCILFUNC] = D3DCMP_ALWAYS;
  m_renderState[D3DRS_SRGBWRITEENABLE] = FALSE;
  m_renderState[D3DRS_DEPTHBIAS] = 0;
  m_renderState[D3DRS_WRAP8] = 0;
  m_renderState[D3DRS_WRAP9] = 0;
  m_renderState[D3DRS_WRAP10] = 0;
  m_renderState[D3DRS_WRAP11] = 0;
  m_renderState[D3DRS_WRAP12] = 0;
  m_renderState[D3DRS_WRAP13] = 0;
  m_renderState[D3DRS_WRAP14] = 0;
  m_renderState[D3DRS_WRAP15] = 0;
  m_renderState[D3DRS_SEPARATEALPHABLENDENABLE] = FALSE;
  m_renderState[D3DRS_SRCBLENDALPHA] = D3DBLEND_ONE;
  m_renderState[D3DRS_DESTBLENDALPHA] = D3DBLEND_ZERO;
  m_renderState[D3DRS_BLENDOPALPHA] = D3DBLENDOP_ADD;
  rwg_D3D9AllValidRenderState[6] |= 0x7ff;

  m_rasterStageDirty = 1;
  m_raster[0] = 0;
  m_paletteDirty = 1;
  m_palette = 0;
  rwg_D3D9TextureStageStateToUpdate[0] = 0;

  // Texture stage 0.
  m_textureStageState[0][D3DTSS_COLOROP] = D3DTOP_SELECTARG1;
  m_textureStageState[0][D3DTSS_COLORARG1] = D3DTA_DIFFUSE;
  m_textureStageState[0][D3DTSS_COLORARG2] = D3DTA_CURRENT;
  m_textureStageState[0][D3DTSS_ALPHAOP] = D3DTOP_SELECTARG1;
  m_textureStageState[0][D3DTSS_ALPHAARG1] = D3DTA_DIFFUSE;
  m_textureStageState[0][D3DTSS_ALPHAARG2] = D3DTA_CURRENT;
  m_textureStageState[0][D3DTSS_BUMPENVMAT00] = 0;
  m_textureStageState[0][D3DTSS_BUMPENVMAT01] = 0;
  m_textureStageState[0][D3DTSS_BUMPENVMAT10] = 0;
  m_textureStageState[0][D3DTSS_BUMPENVMAT11] = 0;
  m_textureStageState[0][D3DTSS_TEXCOORDINDEX] = 0;
  m_textureStageState[0][D3DTSS_BUMPENVLSCALE] = 0;
  m_textureStageState[0][D3DTSS_BUMPENVLOFFSET] = 0;
  m_textureStageState[0][D3DTSS_TEXTURETRANSFORMFLAGS] = D3DTTFF_DISABLE;
  m_textureStageState[0][D3DTSS_COLORARG0] = D3DTA_CURRENT;
  m_textureStageState[0][D3DTSS_ALPHAARG0] = D3DTA_CURRENT;
  m_textureStageStateDirty[0] = 0xee007ff;
  m_textureStageState[0][D3DTSS_RESULTARG] = D3DTA_CURRENT;
  rwg_D3D9AllValidTextureStageState |= 0xee007ff;

  const D3DCAPS9* caps = DevCapsManager::GetD3DCAPS9();
  if (caps->PrimitiveMiscCaps & D3DPMISCCAPS_PERSTAGECONSTANT) {
    m_textureStageStateDirty[0] |= 0x80000000;
    m_textureStageState[0][D3DTSS_CONSTANT] = 0;
    rwg_D3D9AllValidTextureStageState |= 0x80000000;
  }
  rwg_D3D9AllValidSamplerState |= 0x1fff;

  // Sampler state of stage 0.
  rwg_D3D9SamplerStateToUpdate[0] = 0;
  m_samplerState[0][D3DSAMP_ADDRESSU] = D3DTADDRESS_WRAP;
  m_samplerState[0][D3DSAMP_ADDRESSV] = D3DTADDRESS_WRAP;
  m_samplerState[0][D3DSAMP_ADDRESSW] = D3DTADDRESS_WRAP;
  m_samplerState[0][D3DSAMP_BORDERCOLOR] = 0;
  m_samplerState[0][D3DSAMP_MAGFILTER] = D3DTEXF_POINT;
  m_samplerState[0][D3DSAMP_MINFILTER] = D3DTEXF_POINT;
  m_samplerState[0][D3DSAMP_MIPFILTER] = D3DTEXF_NONE;
  m_samplerState[0][D3DSAMP_MIPMAPLODBIAS] = 0;
  m_samplerState[0][D3DSAMP_MAXMIPLEVEL] = 0;
  m_samplerState[0][D3DSAMP_MAXANISOTROPY] = 1;
  m_samplerState[0][D3DSAMP_SRGBTEXTURE] = 0;
  m_samplerState[0][D3DSAMP_ELEMENTINDEX] = 0;
  m_samplerStateDirty[0] = 0x1fff;
  m_samplerState[0][D3DSAMP_DMAPOFFSET] = 0x100;

  // The remaining 16 stages: stage disabled, texcoord set = stage index.
  for (int stage = 1; stage < 17; stage++) {
    m_textureStageState[stage][D3DTSS_COLOROP] = D3DTOP_DISABLE;
    m_textureStageState[stage][D3DTSS_COLORARG1] = D3DTA_DIFFUSE;
    m_textureStageState[stage][D3DTSS_COLORARG2] = D3DTA_CURRENT;
    m_textureStageState[stage][D3DTSS_ALPHAOP] = D3DTOP_DISABLE;
    m_textureStageState[stage][D3DTSS_ALPHAARG1] = D3DTA_DIFFUSE;
    m_textureStageState[stage][D3DTSS_ALPHAARG2] = D3DTA_CURRENT;
    m_textureStageState[stage][D3DTSS_BUMPENVMAT00] = 0;
    m_textureStageState[stage][D3DTSS_BUMPENVMAT01] = 0;
    m_textureStageState[stage][D3DTSS_BUMPENVMAT10] = 0;
    m_textureStageState[stage][D3DTSS_BUMPENVMAT11] = 0;
    m_rasterStageDirty |= 1u << stage;
    m_textureStageState[stage][D3DTSS_TEXCOORDINDEX] = stage;
    m_textureStageState[stage][D3DTSS_BUMPENVLSCALE] = 0;
    m_textureStageState[stage][D3DTSS_BUMPENVLOFFSET] = 0;
    m_textureStageState[stage][D3DTSS_TEXTURETRANSFORMFLAGS] = D3DTTFF_DISABLE;
    m_textureStageState[stage][D3DTSS_COLORARG0] = D3DTA_CURRENT;
    m_textureStageState[stage][D3DTSS_ALPHAARG0] = D3DTA_CURRENT;
    m_raster[stage] = 0;
    rwg_D3D9TextureStageStateToUpdate[stage] = 0;
    m_textureStageStateDirty[stage] = 0xee007ff;
    m_textureStageState[stage][D3DTSS_RESULTARG] = D3DTA_CURRENT;
    if (caps->PrimitiveMiscCaps & D3DPMISCCAPS_PERSTAGECONSTANT) {
      m_textureStageStateDirty[stage] = 0x8ee007ff;
      m_textureStageState[stage][D3DTSS_CONSTANT] = 0;
    }
    m_samplerState[stage][D3DSAMP_ADDRESSU] = D3DTADDRESS_WRAP;
    m_samplerState[stage][D3DSAMP_ADDRESSV] = D3DTADDRESS_WRAP;
    m_samplerState[stage][D3DSAMP_ADDRESSW] = D3DTADDRESS_WRAP;
    m_samplerState[stage][D3DSAMP_BORDERCOLOR] = 0;
    m_samplerState[stage][D3DSAMP_MAGFILTER] = D3DTEXF_POINT;
    m_samplerState[stage][D3DSAMP_MINFILTER] = D3DTEXF_POINT;
    m_samplerState[stage][D3DSAMP_MIPFILTER] = D3DTEXF_NONE;
    m_samplerState[stage][D3DSAMP_MIPMAPLODBIAS] = 0;
    m_samplerState[stage][D3DSAMP_MAXMIPLEVEL] = 0;
    m_samplerState[stage][D3DSAMP_MAXANISOTROPY] = 1;
    m_samplerState[stage][D3DSAMP_SRGBTEXTURE] = 0;
    m_samplerState[stage][D3DSAMP_ELEMENTINDEX] = 0;
    rwg_D3D9SamplerStateToUpdate[stage] = 0;
    m_samplerStateDirty[stage] = 0x1fff;
    m_samplerState[stage][D3DSAMP_DMAPOFFSET] = 0x100;
  }

  m_fogStartDensity = 0.0f;
  m_fogType = 0;
  m_fogEnd = 1.0f;
  m_fogColor.red = 1.0f;
  m_fogColor.green = 1.0f;
  m_fogColor.blue = 1.0f;
  Dispatch();
  D3D9ClearDirtyFlags();
}

}  // namespace graphics
}  // namespace rw
