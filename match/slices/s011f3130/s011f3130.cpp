// slice s011f3130 -- RenderWare 4 core: rw::graphics vertex/index buffer & render-target
// state management (VertexDescriptor / VertexBuffer / Viewport).
//
// RenderWare 4 core was built with VC .NET 2003 (cl 13.10) + /GL /LTCG; single-object codegen
// cannot reproduce the cross-call register allocation, so most of these are complete behavioural
// reconstructions (equivalence only).  The member functions are declared on the reconstructed
// classes so the __thiscall / __fastcall ABIs match the retail build.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;

// ------------------------------------------------------------------ forward decls / callees
namespace rw { namespace graphics {
struct Raster;
struct VertexDescriptor;
struct VertexBuffer;
struct Palette;

// ---- free helpers (no pdb symbol; resolved by address) ----
void  FUN_011f2d20(void*);                       // 0x011f2d20
int   FUN_011f2c00(void*);                       // 0x011f2c00
void  FUN_011f2e10(void);                        // 0x011f2e10
struct VD2 { void FUN_011f2f10(int index, void* src); // 0x011f2f10
};
char  rwg_D3D9FindBestDeclType(void);            // 0x011f3070
u32   ElementHashFunction(u8, u8);               // 0x011f2fd0
int   FUN_011f5330(int, u32, int, int, int*, int*);  // 0x011f5330
void  FUN_011f5500(int, u32, int, void*, int);   // 0x011f5500
int   FUN_011f56b0(int, int*, int*);             // 0x011f56b0
void  FUN_011f5770(void*);                       // 0x011f5770

int   ArenaTypeRegGetType(u32);                  // 0x011e22c0
struct Arena { void* IdToObject(u32 id); // 0x011e2300
};

class DevCapsManager {
public:
  static const u32* GetD3DCAPS9(void);           // 0x011f8af0
};

// ---- ActiveState subset used by the buffer manager -------------------------------
struct StreamSource { void* vb; u32 offset; u32 stride; };
struct RenderTargetShadow { u32 flags; void* raster; };
struct ViewportShadow { i32 x, y, width, height; float minZ, maxZ; };

class ActiveState {
public:
  static void* m_vertexDescriptor;    // 0x016f65a0
  static void* m_d3d9Device;          // 0x016f89d0
  static void* m_paletteShadow;       // 0x016f9130
  static u8    m_numUsedUV;           // 0x016f9134
  static StreamSource m_stream[4];    // 0x016f9138
  static float m_fogColor[3];         // 0x016f9168
  static RenderTargetShadow m_renderTarget[4]; // 0x016f9174
  static void* m_zBufferShadow;       // 0x016f9194
  static ViewportShadow m_viewport;   // 0x016f9198
};

class Device {
public:
  static void* m_defaultCameraRaster;   // 0x015d0838
  static void* m_defaultZBufferRaster;  // 0x015d083c
};
}} // namespace rw::graphics

// unnamed module globals
extern const float f13f2100;            // 0x013f2100   (255.0f colour scale)
extern u8   DAT_014f73b8[];             // 0x014f73b8   (per-source-element decl table)
extern u8   DAT_016f8bc4;               // 0x016f8bc4
extern u32  DAT_016fa5b8;               // 0x016fa5b8

using namespace rw::graphics;

// reconstructed classes carrying the __thiscall member functions
struct VD  { void* FUN_011f3160(void* dst); };
struct VBi { u32  FUN_011f3620(u8, u32, u32); void FUN_011f38f0(int, u32); };
struct VPi { bool FUN_011f3d40(u32, u32); };

namespace rw { namespace graphics {
struct VertexBuffer { VertexBuffer* Unlock(); };
}}


// ===================================================================================
//  FUN_011f3130 @ 0x011f3130 -- VertexDescriptor destructor / detach
// @ 0x011f3130
// ===================================================================================
void __fastcall FUN_011f3130(void* desc)
{
  if (ActiveState::m_vertexDescriptor == desc)
    ActiveState::m_vertexDescriptor = 0;
  if (*(int*)((char*)desc + 8) != 0)
    FUN_011f2d20(desc);
}


// ===================================================================================
//  FUN_011f3160 @ 0x011f3160 -- VertexDescriptor deep copy (this=src, dst on stack)
// @ 0x011f3160
// ===================================================================================
void* VD::FUN_011f3160(void* dst)
{
  u8* s = (u8*)this;
  u8* d = (u8*)dst;

  if (ActiveState::m_vertexDescriptor == this)
    ActiveState::m_vertexDescriptor = 0;
  if (*(u32*)(d + 8) != 0)
    FUN_011f2d20(dst);

  *(u32*)(d + 0)  = 0;
  *(u32*)(d + 4)  = 0;
  *(u32*)(d + 8)  = 0;
  *(u16*)(d + 0xc) = *(u16*)(s + 0xc);
  *(u8*)(d + 0xf)  = *(u8*)(s + 0xf);
  *(u32*)(d + 0x10) = *(u32*)(s + 0x10);
  *(u32*)(d + 0x14) = *(u32*)(s + 0x14);

  u32 n = *(u16*)(s + 0xc);
  // copy n 12-byte element records at offset 0x18, high-to-low (source may alias dst)
  for (u32 k = n; k-- > 0; ) {
    const u8* se = s + 0x18 + 12 * k;
    u8* de = d + 0x18 + 12 * k;
    for (int j = 0; j < 12; ++j)
      de[j] = se[j];
  }

  FUN_011f2c00(dst);
  return dst;
}


// ===================================================================================
//  FUN_011f3220 @ 0x011f3220 -- rw::graphics::VertexDescriptor::Unlock (ECX = descriptor)
// @ 0x011f3220
// ===================================================================================
int __fastcall FUN_011f3220(int desc)
{
  u8* p = (u8*)desc;

  if ((p[0xe] & 1) != 0)
    p[0xe] &= 0xfe;

  if ((p[0xe] & 2) != 0) {
    u8 local[16];
    for (int i = 0; i < 16; ++i)
      local[i] = 0;

    u32 count = 0;
    if (*(int*)(p + 8) != 0)
      FUN_011f2d20(p);
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0x14) = 0;

    if (*(u16*)(p + 0xc) != 0) {
      u8* pc = p + 0x1c;
      do {
        int iVar4 = *(int*)(pc + 4);
        if (pc[0] == 0xff)
          pc[0] = rwg_D3D9FindBestDeclType();
        if (pc[2] == 0xff)
          pc[2] = ((char*)DAT_014f73b8)[iVar4 * 8];
        if (pc[3] == 0xff)
          pc[3] = ((char*)DAT_014f73b8)[iVar4 * 8 + 1];

        if (*(u16*)(pc - 2) == 0xffff) {
          u8 idx = pc[-4];
          u8* slot = &local[idx];
          *(u16*)(pc - 2) = local[idx];
          switch (pc[0]) {
            case 0: case 4: case 5: case 6: case 8: case 9: case 0xb: case 0xd:
            case 0xe: case 0xf: *slot += 4;  break;
            case 1: case 7: case 10: case 0xc: case 0x10: *slot += 8;  break;
            case 2: *slot += 0xc; break;
            case 3: *slot += 0x10; break;
            default: break;
          }
        } else {
          char cVar2;
          switch (pc[0]) {
            case 0: case 4: case 5: case 6: case 8: case 9: case 0xb: case 0xd:
            case 0xe: case 0xf: cVar2 = 0x04; break;
            case 1: case 7: case 10: case 0xc: case 0x10: cVar2 = 0x08; break;
            case 2: cVar2 = 0x0c; break;
            case 3: cVar2 = 0x10; break;
            default: cVar2 = 0x00; break;
          }
          u8 idx = pc[-4];
          if (local[idx] < (u8)(pc[-2] + cVar2))
            local[idx] = (u8)(pc[-2] + cVar2);
        }

        *(u32*)(p + 0x10) |= *(u32*)((char*)DAT_014f73b8 + iVar4 * 8 + 4);
        u32 uVar3 = ElementHashFunction(pc[2], pc[3]);
        *(u32*)(p + 0x14) |= uVar3;
        ++count;
        pc += 0xc;
      } while (count < *(u16*)(p + 0xc));
    }

    u32 nb = (u32)*(u16*)(p + 0xc);
    char cVar2;
    switch (p[0x10 + nb * 0xc]) {
      case 0: case 4: case 5: case 6: case 8: case 9: case 0xb: case 0xd:
      case 0xe: case 0xf: cVar2 = 0x04; break;
      case 1: case 7: case 10: case 0xc: case 0x10: cVar2 = 0x08; break;
      case 2: cVar2 = 0x0c; break;
      case 3: cVar2 = 0x10; break;
      default: cVar2 = 0x00; break;
    }
    p[0xf] = p[nb * 0xc + 0xe] + cVar2;
    p[0xe] &= 0xfd;
    int iVar4b = FUN_011f2c00(p);
    if (iVar4b == 0)
      return 0;
  }
  return desc;
}


// ===================================================================================
//  FUN_011f34a0 @ 0x011f34a0 -- build a VertexDescriptor; 0=default array, else from src
// @ 0x011f34a0
// ===================================================================================
u32* FUN_011f34a0(u32* param_1, int n, int src)
{
  u32* p = (u32*)*param_1;

  p[0] = 0;
  p[1] = 0;
  p[2] = 0;
  *(u16*)(p + 3) = (u16)n;
  *(u8*)((char*)p + 0xe) = 0;
  *(u8*)((char*)p + 0xf) = 0;
  p[4] = 0;
  p[5] = 0;

  if (src == 0) {
    for (int k = 0; k < n; ++k) {
      u8* e = (u8*)p + 0x18 + 12 * k;
      *(u16*)(e + 0) = 0;
      *(u16*)(e + 2) = 0xffff;
      e[4] = 0xff;
      e[5] = 0x00;
      e[6] = 0xff;
      e[7] = 0xff;
      *(u32*)(e + 8) = 0xffffffff;
    }
    return p;
  }

  *(u8*)((char*)p + 0xe) = 2;
  for (int k = n - 1; k >= 0; --k)
    ((VD2*)p)->FUN_011f2f10(k, (void*)((char*)src + 12 * k));

  FUN_011f3220((int)p);
  return p;
}


// ===================================================================================
//  FUN_011f3540 @ 0x011f3540 -- (EAX = creation flags) can we use a D3D vertex buffer?
// @ 0x011f3540
// ===================================================================================
int FUN_011f3540(u32 flags)
{
  if ((flags & 0x800000) != 0)
    return 0;
  if ((flags & 0x400000) != 0 &&
      (DevCapsManager::GetD3DCAPS9()[0xd4 / 4] & 1) == 0)
    return 0;
  return 1;
}


// ===================================================================================
//  FUN_011f3580 @ 0x011f3580 -- rw::graphics::VertexBuffer::Release (ECX = vb)
// @ 0x011f3580
// ===================================================================================
void __fastcall FUN_011f3580(int par)
{
  u8* p = (u8*)par;

  if ((p[0x15] & 3) != 0) {
    void* obj = *(void**)(p + 4);
    (*(void(__stdcall**)(void*))(*(u32*)obj + 0x30))(obj);
  }

  for (int i = 3; i >= 0; --i) {
    if (ActiveState::m_stream[i].vb == *(void**)(p + 4)) {
      ActiveState::m_stream[i].vb = 0;
      ActiveState::m_stream[i].offset = 0;
      ActiveState::m_stream[i].stride = 0;
      (*(void(__stdcall**)(void*, u32, u32, u32, u32))(*(u32*)ActiveState::m_d3d9Device + 400))
          (ActiveState::m_d3d9Device, (u32)i, 0, 0, 0);   // SetStreamSource
    }
  }

  if ((*(u32*)(p + 0x10) & 0x200) == 0) {
    u32 elem = p[0x14];
    FUN_011f5500(elem, *(u32*)(p + 0x10) & 0xff3fffff, *(int*)(p + 0xc) * elem,
                 *(void**)(p + 4), *(int*)(p + 8) * elem);
    return;
  }
  FUN_011f5770(*(void**)(p + 4));
}


// ===================================================================================
//  FUN_011f3620 @ 0x011f3620 -- rw::graphics::VertexBuffer::Lock (ECX = vb)
// @ 0x011f3620
// ===================================================================================
u32 VBi::FUN_011f3620(u8 param_2, u32 param_3, u32 param_4)
{
  u32 flags = 0;
  u32 local_4 = 0;

  if ((param_2 & 2) == 0 && (*(u32*)((char*)this + 0x10) & 8) == 0)
    flags = 0x10;
  if ((param_2 & 4) == 0) {
    if ((param_2 & 8) != 0)
      flags |= 0x1000;
  } else {
    flags |= 0x2000;
  }

  void* vb = *(void**)((char*)this + 4);
  int hr = (*(int(__stdcall**)(void*, u32, u32, u32*, u32))(*(u32*)vb + 0x2c))
               (vb, param_3, param_4, &local_4, flags);
  if (hr < 0)
    return 0;

  *(u8*)((char*)this + 0x15) |= param_2 & 3;
  return local_4;
}


// ===================================================================================
//  rw::graphics::VertexBuffer::Unlock @ 0x011f36a0
// @ 0x011f36a0
// ===================================================================================
VertexBuffer* VertexBuffer::Unlock()
{
  void* vb = *(void**)((char*)this + 4);
  int hr = (*(int(__stdcall**)(void*))(*(u32*)vb + 0x30))(vb);
  if (hr < 0)
    return 0;
  *(u8*)((char*)this + 0x15) = 0;
  return this;
}


// ===================================================================================
//  FUN_011f36d0 @ 0x011f36d0 -- create a dynamic/static D3D vertex buffer wrapper
// @ 0x011f36d0
// ===================================================================================
int* FUN_011f36d0(int* param_1, int param_2, int param_3, u32 param_4)
{
  int* p = (int*)*param_1;

  u32 createFlags;
  u32 kind = param_4 & 3;
  if (kind == 0)
    createFlags = 8;
  else if (kind == 1)
    createFlags = 0x208;
  else if (kind == 2)
    createFlags = 0;
  else
    return 0;

  if ((param_4 & 4) != 0)
    createFlags |= 0x400000;
  if ((param_4 & 8) != 0)
    createFlags |= 0x800000;

  p[0] = param_2;
  p[1] = 0;
  p[2] = 0;
  p[3] = param_3;
  p[4] = createFlags;
  *(u8*)(p + 5) = *(u8*)(param_2 + 0xf);
  *(u8*)((char*)p + 0x15) = 0;
  *(u16*)((char*)p + 0x16) = 0;
  p[6] = 0;

  int size = (u32)*(u8*)(param_2 + 0xf) * param_3;

  if ((createFlags & 0x200) != 0) {
    int r = FUN_011f56b0(size, &param_2, p);
    if (r < 0)
      return 0;
    p[1] = param_2;
    return p;
  }

  int bVar2;
  if ((createFlags & 0x800000) == 0) {
    if ((createFlags & 0x400000) != 0) {
      const u32* caps = DevCapsManager::GetD3DCAPS9();
      if ((caps[0xd4 / 4] & 1) == 0) {
        bVar2 = 1;
        goto haveFlag;
      }
    }
    bVar2 = 0;
  } else {
    bVar2 = 1;
  }
haveFlag:
  int r = FUN_011f5330(*(u8*)(p + 5), createFlags & 0xff3fffff, size, !bVar2, &param_2, p + 2);
  if (r < 0)
    return 0;
  p[1] = param_2;
  return p;
}


// ===================================================================================
//  FUN_011f37e0 @ 0x011f37e0 -- VertexBuffer arena fixup (re-lock + copy + unlock)
// @ 0x011f37e0
// ===================================================================================
u32 FUN_011f37e0(u32* obj, u8* ctx)
{
  void* arena = *(void**)(ctx + 0x78);
  int* vb = 0;

  obj[0] = (u32)((Arena*)arena)->IdToObject(obj[0]);
  obj[6] = (u32)((Arena*)arena)->IdToObject(obj[6]);

  u32 size = (u32)((u8*)obj)[0x14] * obj[3];

  if ((obj[4] & 0x200) == 0) {
    void* src = (void*)obj[6];
    if (src != 0) {
      int keep = FUN_011f3540(obj[4]);
      int hr = FUN_011f5330(((u8*)obj)[0x14], obj[4] & 0xff3fffff, (int)size, keep,
                            (int*)&vb, (int*)(obj + 2));
      if (hr >= 0) {
        obj[1] = (u32)vb;
        void* locked = 0;
        int hr2 = (*(int(__stdcall**)(void*, u32, u32, void**, u32))(*(u32*)vb + 0x2c))
                      (vb, (u32)((u8*)obj)[0x14] * obj[2], size, &locked, 0);
        if (hr2 >= 0) {
          u8* d = (u8*)locked;
          u8* s = (u8*)src;
          for (u32 k = 0; k < size; ++k)
            d[k] = s[k];
          int hr3 = (*(int(__stdcall**)(void*))(*(u32*)vb + 0x30))(vb);
          if (hr3 >= 0)
            return 1;
        }
      }
    }
  } else {
    int hr = FUN_011f56b0((int)size, (int*)&vb, (int*)obj);
    if (hr >= 0) {
      obj[1] = (u32)vb;
      return 1;
    }
  }
  return 0;
}


// ===================================================================================
//  FUN_011f38e0 @ 0x011f38e0
// @ 0x011f38e0
// ===================================================================================
u32 FUN_011f38e0(void)
{
  DAT_016fa5b8 = 0;
  return 1;
}


// ===================================================================================
//  FUN_011f38f0 @ 0x011f38f0 -- store a render-target pointer (ECX = this)
// @ 0x011f38f0
// ===================================================================================
void VBi::FUN_011f38f0(int index, u32 value)
{
  *(u32*)((char*)this + 0x40 + index * 4) = value;
}


// ===================================================================================
//  FUN_011f3900 @ 0x011f3900 -- release all render targets + depth-stencil
// @ 0x011f3900
// ===================================================================================
void FUN_011f3900(void)
{
  void* dev = ActiveState::m_d3d9Device;

  for (int i = 0; i < 4; ++i) {
    if (ActiveState::m_renderTarget[i].raster != 0) {
      if (i != 0) {
        (*(void(__stdcall**)(void*, u32, u32))(*(u32*)dev + 0x94))(dev, (u32)i, 0);
      }
      if ((ActiveState::m_renderTarget[i].flags & 9) == 9) {
        void* rt = ActiveState::m_renderTarget[i].raster;
        (*(void(__stdcall**)(void*))(*(u32*)rt + 8))(rt);
      }
      ActiveState::m_renderTarget[i].raster = 0;
    }
  }

  if (ActiveState::m_zBufferShadow != 0) {
    (*(void(__stdcall**)(void*, u32))(*(u32*)dev + 0x9c))(dev, 0);
    ActiveState::m_zBufferShadow = 0;
  }
}


// ===================================================================================
//  FUN_011f3990 @ 0x011f3990 -- reset the render-target shadows to the device defaults
// @ 0x011f3990
// ===================================================================================
void FUN_011f3990(void)
{
  ActiveState::m_renderTarget[0].raster =
      *(void**)((char*)Device::m_defaultCameraRaster + 8);
  ActiveState::m_zBufferShadow =
      *(void**)((char*)Device::m_defaultZBufferRaster + 8);
}


// ===================================================================================
//  FUN_011f39b0 @ 0x011f39b0 -- push render targets + depth-stencil (ECX = this)
// @ 0x011f39b0
// ===================================================================================
void __fastcall FUN_011f39b0(int par)
{
  u8* p = (u8*)par;
  int* slot = (int*)(p + 0x40);
  void* dev = ActiveState::m_d3d9Device;

  for (u32 i = 0; i < 4; ++i) {
    int rtObj = *slot;
    u32 flags = 1;
    void* raster = 0;
    if (rtObj != 0) {
      flags = *(u32*)(rtObj + 4);
      if ((flags & 9) == 9) {
        int* inner = *(int**)(rtObj + 8);
        if (inner != 0) {
          if ((flags & 0x1000) == 0) {
            void* out = 0;
            (*(void(__stdcall**)(void*, u32, void**))(*(u32*)inner + 0x48))(inner, 0, &out);
            raster = out;
          } else {
            void* out = 0;
            (*(void(__stdcall**)(void*, u32, u32, void**))(*(u32*)inner + 0x48))
                (inner, *(u8*)(rtObj + 0x12), 0, &out);
            raster = out;
          }
        }
      } else {
        raster = *(void**)(rtObj + 8);
      }
    }

    void* cur = ActiveState::m_renderTarget[i].raster;
    if (cur == raster) {
      if ((flags & 9) == 9) {
        (*(void(__stdcall**)(void*))(*(u32*)raster + 8))(raster);
      }
    } else {
      if ((ActiveState::m_renderTarget[i].flags & 9) == 9) {
        (*(void(__stdcall**)(void*))(*(u32*)cur + 8))(cur);
      }
      (*(void(__stdcall**)(void*, u32, void*))(*(u32*)dev + 0x94))(dev, i, raster);
      ActiveState::m_renderTarget[i].flags = flags;
      ActiveState::m_renderTarget[i].raster = raster;
    }
    ++slot;
  }

  int zbuf = 0;
  if (*(int*)(p + 0x50) != 0)
    zbuf = *(int*)(*(int*)(p + 0x50) + 8);
  if (ActiveState::m_zBufferShadow != (void*)zbuf) {
    (*(void(__stdcall**)(void*, u32))(*(u32*)dev + 0x9c))(dev, (u32)zbuf);
    ActiveState::m_zBufferShadow = (void*)zbuf;
  }
}


// ===================================================================================
//  FUN_011f3ab0 @ 0x011f3ab0 -- 3x3 transpose + negated translation (dst in EAX, src in ECX)
// @ 0x011f3ab0
// ===================================================================================
void FUN_011f3ab0(float* dst, float* src)
{
  dst[0]  = src[0];
  dst[4]  = src[1];
  dst[8]  = src[2];
  dst[1]  = src[4];
  dst[5]  = src[5];
  dst[9]  = src[6];
  dst[2]  = src[8];
  dst[6]  = src[9];
  dst[10] = src[10];
  dst[0xc] = 0.0f - (src[0xc] * src[0] + (src[0xd] * src[1] + src[0xe] * src[2]));
  dst[0xd] = 0.0f - (src[0xc] * src[4] + (src[0xd] * src[5] + src[0xe] * src[6]));
  dst[0xe] = 0.0f - (src[0xc] * src[8] + (src[0xd] * src[9] + src[0xe] * src[10]));
}


// ===================================================================================
//  FUN_011f3c40 @ 0x011f3c40 -- build a default 3D immediate-mode matrix block
// @ 0x011f3c40
// ===================================================================================
void FUN_011f3c40(u32* param_1)
{
  u32* p = (u32*)*param_1;

  p[0x1d] = 0x41200000;
  p[0x17] = 0x3f800000;
  p[0x18] = 0x3f800000;
  p[0x19] = 0x3f800000;
  p[0x1a] = 0x3f800000;
  p[0x15] = 0;
  p[0x16] = 0;
  p[0x22] = 0;
  p[0x23] = 0x3f800000;
  p[0x1c] = 0x3f800000;
  p[0x1e] = 0;
  p[0x1f] = 0;
  p[0x20] = 0;
  p[0x21] = 0;
  p[0x10] = 0;
  p[0x11] = 0;
  p[0x12] = 0;
  p[0x13] = 0;
  p[0x14] = 0;
  p[0x1b] = 1;
  p[0]  = 0x3f800000;
  p[1]  = 0;
  p[2]  = 0;
  p[3]  = 0;
  p[4]  = 0;
  p[5]  = 0x3f800000;
  p[6]  = 0;
  p[7]  = 0;
  p[8]  = 0;
  p[9]  = 0;
  p[10] = 0x3f800000;
  p[0xb] = 0;
  p[0xc] = 0;
  p[0xd] = 0;
  p[0xe] = 0;
  p[0xf] = 0;
  p[0x24] = 0;
  p[0x25] = 0;
}


// ===================================================================================
//  FUN_011f3d40 @ 0x011f3d40 -- push viewport + clear (ECX = device wrapper)
// @ 0x011f3d40
// ===================================================================================
bool VPi::FUN_011f3d40(u32 colorPtr, u32 param_3)
{
  u8* p = (u8*)this;

  u8 flags = (param_3 & 1) ? 1 : 0;
  u32 packed = 0;

  if (param_3 & 1) {
    const float* col = (const float*)colorPtr;
    u32 a = (u32)(col[3] * f13f2100) & 0xff;
    u32 r = (u32)(col[0] * f13f2100) & 0xff;
    u32 g = (u32)(col[1] * f13f2100) & 0xff;
    u32 b = (u32)(col[2] * f13f2100) & 0xff;
    packed = ((a << 8 | r) << 8 | g) << 8 | b;
  }

  if (*(int*)(p + 0x50) != 0) {
    if (param_3 & 2)
      flags |= 2;
    if ((param_3 & 4) &&
        (DAT_016f8bc4 == 0x4b || DAT_016f8bc4 == 0x4f ||
         DAT_016f8bc4 == 0x53 || DAT_016f8bc4 == 0x49))
      flags |= 4;
  }

  FUN_011f39b0((int)this);

  bool same =
      ActiveState::m_viewport.x == *(i32*)(p + 0x78) &&
      ActiveState::m_viewport.y == *(i32*)(p + 0x7c) &&
      ActiveState::m_viewport.width == *(i32*)(p + 0x80) &&
      ActiveState::m_viewport.height == *(i32*)(p + 0x84) &&
      ((ActiveState::m_viewport.minZ - *(float*)(p + 0x88)) <= 1.1920929e-07f &&
       (*(float*)(p + 0x88) - ActiveState::m_viewport.minZ) <= 1.1920929e-07f) &&
      ((ActiveState::m_viewport.maxZ - *(float*)(p + 0x8c)) <= 1.1920929e-07f &&
       (*(float*)(p + 0x8c) - ActiveState::m_viewport.maxZ) <= 1.1920929e-07f);

  void* dev = ActiveState::m_d3d9Device;
  if (!same) {
    ActiveState::m_viewport.x = *(i32*)(p + 0x78);
    ActiveState::m_viewport.y = *(i32*)(p + 0x7c);
    ActiveState::m_viewport.width = *(i32*)(p + 0x80);
    ActiveState::m_viewport.height = *(i32*)(p + 0x84);
    ActiveState::m_viewport.minZ = *(float*)(p + 0x88);
    ActiveState::m_viewport.maxZ = *(float*)(p + 0x8c);
    int hr = (*(int(__stdcall**)(void*, void*))(*(u32*)dev + 0xbc))(dev, (void*)(p + 0x78));
    if (hr < 0)
      return false;
  }

  int hr = (*(int(__stdcall**)(void*, u32, u32, u32, u32, u32, void*))(*(u32*)dev + 0xac))
               (dev, 0, 0, flags, packed, 0x3f800000, *(void**)(p + 0x94));
  return hr > -1;
}
