// slice s011f4e90 -- RenderWare 4 core: D3D9 vertex/index buffer pool manager
// (rw::graphics::VertexBuffer / IndexBuffer resource tracking).
//
// The retail object was built with VC .NET 2003 (cl 13.10) + /GL /LTCG, so a single-object
// /vc71 compile cannot reproduce the cross-call register allocation; most of these are
// complete behavioural reconstructions (equivalence only).  The member functions are declared
// on small reconstructed classes so the __thiscall ABI matches the retail build.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;

// small custom pool allocator (thiscall members; ECX = pool)
struct Allocator {
  void* FUN_011fd610();             // 0x011fd610
  void  FUN_011fd530(u32 a, u32 b); // 0x011fd530
  void  FUN_011fd5d0();             // 0x011fd5d0
  void  FUN_011fd6b0(void* p);      // 0x011fd6b0
};

// ------------------------------------------------------------------ globals
extern void* g_d3d9Device;          // 0x016f89d0  ActiveState::m_d3d9Device
extern u32   g_boundIndexBuffer;    // 0x016f8afc
extern u32   g_vtxPoolHead;         // 0x0170a6b4
extern Allocator g_pool_6bc;        // 0x0170a6bc
extern Allocator g_pool_6d0;        // 0x0170a6d0
extern Allocator g_pool_6e4;        // 0x0170a6e4
extern u32   g_vtxInited;           // 0x0170a6ec
extern u32   g_vtxSlots[12];        // 0x0170a720  [4] x {vb, cap, used}
extern u32   g_vtxCurSlot;          // 0x0170a750
extern u32   g_vtxFreeHead;         // 0x0170a754
extern Allocator g_pool_75c;        // 0x0170a75c
extern u32   g_vtxInited2;          // 0x0170a764
extern u32   g_idxFreeHead;         // 0x0170a798
extern Allocator g_pool_7a0;        // 0x0170a7a0
extern Allocator g_pool_7b4;        // 0x0170a7b4
extern u32   g_idxInited;           // 0x0170a7bc
extern Allocator g_pool_7c8;        // 0x0170a7c8
extern u32   g_vtxGrowSize;         // 0x015d07c0
extern u32   g_vtxPoolSize;         // 0x015d07c4
extern u32   g_idxGrowSize;         // 0x015d07c8

// ------------------------------------------------------------------ callees
void  FUN_011f5db0(u32, u32, u32, u32, u32);                // 0x011f5db0
void  FUN_011f6080(u32);                                    // 0x011f6080
int   FUN_011f5fa0(u32, u32, void**, void*);                // 0x011f5fa0
int   FUN_011f5bd0(u32, u32, u32, int, u32*, u32*);         // 0x011f5bd0

struct Arena {
  void* IdToObject(u32 id);                                 // 0x011e2300
};

// member-carrying stubs (thiscall)
struct IBufA { u32   FUN_011f4f20(u32, void*); };
struct IBufB { void* FUN_011f4fd0(void**); };

struct ResDesc { u32 v[8]; };


// ===================================================================================
//  FUN_011f4e90 @ 0x011f4e90 -- rw::graphics::IndexBuffer::Destroy (ECX = ib)
// @ 0x011f4e90
// ===================================================================================
void __fastcall FUN_011f4e90(u32* param_1)
{
  if (g_boundIndexBuffer == param_1[0]) {
    void* dev = g_d3d9Device;
    g_boundIndexBuffer = 0;
    (*(int(__stdcall**)(void*, void*))(*(u32*)dev + 0x1a0))(dev, 0);
  }
  u32 flags = param_1[3];
  if ((flags & 0x208) != 0x208) {
    u32 c = (u32)(param_1[4] != 0x65) * 2 + 2;
    FUN_011f5db0(c, flags & 0xff3fffff, param_1[2] * c, param_1[0], param_1[1] * c);
  } else {
    FUN_011f6080(param_1[0]);
  }
  param_1[0] = 0;
}


// ===================================================================================
//  FUN_011f4f20 @ 0x011f4f20 -- rw::graphics::IndexBuffer::Lock (ECX = ib)
// @ 0x011f4f20
// ===================================================================================
u32 IBufA::FUN_011f4f20(u32 param_2, void* param_3)
{
  u32* this_ = (u32*)this;
  u32* p3 = (u32*)param_3;

  p3[0] = 0;
  p3[1] = this_[4];
  p3[2] = param_2;

  u32 flags = 0;
  u32 esize = (u32)(this_[4] != 0x65) * 2 + 2;
  if ((param_2 & 2) == 0) {
    if ((this_[3] & 8) == 0)
      flags = 0x10;
  } else if ((this_[3] & 0x200) != 0) {
    if ((param_2 & 4) == 0) {
      if ((param_2 & 8) != 0)
        flags = 0x1000;
    } else {
      flags = 0x2000;
    }
  }

  void* vb = (void*)this_[0];
  int hr = (*(int(__stdcall**)(void*, u32, u32, void*, u32))(*(u32*)vb + 0x2c))
               (vb, this_[1] * esize, this_[2] * esize, p3, flags);
  return ((u32)(hr < 0) - 1) & (u32)this_;
}


// ===================================================================================
//  rw::graphics::IndexBuffer::GetDepth @ 0x011f4fb0
// @ 0x011f4fb0
// ===================================================================================
int __fastcall FUN_011f4fb0(u32* this_)
{
  u32 e = (this_[4] != 0x65) ? 1 : 0;
  return (int)((e - 1) & 0xfffffff0) + 0x20;
}


// ===================================================================================
//  FUN_011f4fd0 @ 0x011f4fd0 -- rw::graphics::IndexBuffer::Release (ECX = ib)
// @ 0x011f4fd0
// ===================================================================================
void* IBufB::FUN_011f4fd0(void** out)
{
  u32* this_ = (u32*)this;

  int hr = (*(int(__stdcall**)(void*))(*(u32*)this_[0] + 0x30))((void*)this_[0]);
  if (hr < 0)
    return 0;
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  return this;
}


// ===================================================================================
//  rw::graphics::IndexBuffer::Initialize @ 0x011f5010
// @ 0x011f5010
// ===================================================================================
u32* FUN_011f5010(u32* param_1, int* param_2, u32 param_3, int param_4, u32 param_5, u32 param_6)
{
  u32* puVar1 = (u32*)*param_1;

  puVar1[2] = (u32)param_4;
  puVar1[1] = 0;
  puVar1[0] = 0;
  puVar1[3] = param_5;
  puVar1[4] = (u32)*param_2;
  puVar1[5] = param_6;
  puVar1[6] = 0;

  u32 iVar2 = (u32)(*param_2 != 0x65) * 2 + 2;
  u32 iVar3 = iVar2 * (u32)param_4;

  int hr;
  if ((param_5 & 0x208) == 0x208) {
    hr = FUN_011f5fa0(iVar3, puVar1[4], (void**)&param_1, puVar1);
  } else {
    hr = FUN_011f5bd0(iVar2, param_5 & 0xff3fffff, iVar3,
                      (int)(~(param_5 >> 0x17) & 1), (u32*)&param_1, puVar1 + 1);
  }
  if (hr < 0)
    return 0;
  puVar1[0] = (u32)param_1;
  return puVar1;
}


// ===================================================================================
//  rw::graphics::IndexBuffer::Fixup @ 0x011f50d0  (arena read callback)
// @ 0x011f50d0
// ===================================================================================
u32 FUN_011f50d0(u32* param_1, void* param_2)
{
  Arena* arena = (Arena*)*(void**)((char*)param_2 + 0x78);
  param_1[6] = (u32)arena->IdToObject(param_1[6]);

  u32 uVar4 = param_1[3];
  u32 esize = (u32)(param_1[4] != 0x65) * 2 + 2;
  u32 uVar5 = param_1[2] * esize;

  if ((uVar4 & 0x200) == 0) {
    if (param_1[6] != 0) {
      if (FUN_011f5bd0(esize, uVar4 & 0xff3fffff, uVar5, (int)(~(uVar4 >> 0x17) & 1),
                       (u32*)&param_2, param_1 + 1) >= 0) {
        param_1[0] = (u32)param_2;
        void* dst = 0;
        if ((*(int(__stdcall**)(void*, u32, u32, void**, u32))(*(u32*)param_2 + 0x2c))
              ((void*)param_2, param_1[1] * esize, uVar5, &dst, 0) >= 0) {
          u32 n = uVar5;
          u32* d = (u32*)dst;
          const u32* s = (const u32*)param_1[6];
          for (u32 k = n >> 2; k != 0; --k) *d++ = *s++;
          for (u32 k = n & 3; k != 0; --k) *(u8*)d++ = *(u8*)s++;
          if ((*(int(__stdcall**)(void*))(*(u32*)param_2 + 0x30))((void*)param_2) >= 0)
            return 1;
        }
      }
    }
  } else {
    if (FUN_011f5fa0(uVar5, param_1[4], (void**)&param_2, param_1) >= 0) {
      param_1[0] = (u32)param_2;
      return 1;
    }
  }
  return 0;
}


// ===================================================================================
//  rw::graphics::IndexBuffer::GetResourceDescriptor @ 0x011f51d0
// @ 0x011f51d0
// ===================================================================================
void FUN_011f51d0(ResDesc* out)
{
  ResDesc d;
  d.v[0] = 0x1c;
  d.v[1] = 4;
  d.v[2] = 0;
  d.v[3] = 1;
  d.v[4] = 0;
  d.v[5] = 1;
  d.v[6] = 0;
  d.v[7] = 1;
  *out = d;
}


// ===================================================================================
//  FUN_011f5220 @ 0x011f5220 -- create the vertex-buffer pool
// @ 0x011f5220
// ===================================================================================
u32 FUN_011f5220(void)
{
  if (g_vtxInited != 0)
    return 0;
  g_pool_6e4.FUN_011fd530(0x10, 0x10);
  g_vtxPoolHead = 0;
  g_pool_6bc.FUN_011fd530(0x14, 100);
  g_pool_6d0.FUN_011fd530(8, 100);
  return 1;
}


// ===================================================================================
//  FUN_011f5270 @ 0x011f5270 -- destroy the vertex-buffer pool
// @ 0x011f5270
// ===================================================================================
void FUN_011f5270(void)
{
  if (g_vtxPoolHead != 0) {
    u32 iVar1;
    do {
      iVar1 = *(u32*)(g_vtxPoolHead + 4);
      while (iVar1 != 0) {
        u32 uVar2 = *(u32*)(*(u32*)(g_vtxPoolHead + 4) + 0xc);
        g_pool_6bc.FUN_011fd6b0((void*)*(u32*)(g_vtxPoolHead + 4));
        *(u32*)(g_vtxPoolHead + 4) = uVar2;
        iVar1 = *(u32*)(g_vtxPoolHead + 4);
      }
      iVar1 = *(u32*)(g_vtxPoolHead + 8);
      while (iVar1 != 0) {
        u32* piVar3 = (u32*)*(u32*)(g_vtxPoolHead + 8);
        iVar1 = piVar3[1];
        if (piVar3[0] != 0)
          (*(int(__stdcall**)(void*))(*(u32*)piVar3[0] + 8))((void*)piVar3[0]);
        g_pool_6d0.FUN_011fd6b0((void*)*(u32*)(g_vtxPoolHead + 8));
        *(u32*)(g_vtxPoolHead + 8) = iVar1;
        iVar1 = *(u32*)(g_vtxPoolHead + 8);
      }
      iVar1 = *(u32*)(g_vtxPoolHead + 0xc);
      g_pool_6e4.FUN_011fd6b0((void*)g_vtxPoolHead);
      g_vtxPoolHead = iVar1;
    } while (iVar1 != 0);
    g_vtxPoolHead = 0;
  }
  g_pool_6d0.FUN_011fd5d0();
  g_pool_6bc.FUN_011fd5d0();
  g_pool_6e4.FUN_011fd5d0();
}


// ===================================================================================
//  FUN_011f5330 @ 0x011f5330 -- allocate a range from the vertex-buffer pool
// @ 0x011f5330
// ===================================================================================
int FUN_011f5330(u32 param_1, u32 param_2, u32 param_3, int param_4, u32* param_5, u32* param_6)
{
  u16* puVar1 = 0;
  u32* puVar2;
  int local_4 = 0;

  // find (or create) the pool entry keyed by (param_1, param_2)
  for (u16* e = (u16*)g_vtxPoolHead; e != 0; e = *(u16**)((u8*)e + 0xc)) {
    if (param_1 == *(u16*)e && param_2 == *(u16*)((u8*)e + 2)) { puVar1 = e; break; }
  }
  if (puVar1 == 0) {
    puVar1 = (u16*)g_pool_6e4.FUN_011fd610();
    if (puVar1 == 0)
      return 0x8007000e;
    *(u16*)puVar1 = (u16)param_1;
    *(u16*)((u8*)puVar1 + 2) = (u16)param_2;
    *(u32*)((u8*)puVar1 + 4) = 0;
    *(u32*)((u8*)puVar1 + 8) = 0;
    *(u32*)((u8*)puVar1 + 0xc) = g_vtxPoolHead;
    g_vtxPoolHead = (u32)puVar1;
  }

  // find a free node with size >= param_3
  if (param_4 == 0 || g_vtxGrowSize == 0) {
    puVar2 = 0;
  } else {
    for (puVar2 = (u32*)*(u32*)((u8*)puVar1 + 4);
         puVar2 != 0 && puVar2[1] < param_3;
         puVar2 = (u32*)puVar2[3]) {
    }
  }

  if (puVar2 == 0) {
    puVar2 = (u32*)g_pool_6bc.FUN_011fd610();
    if (puVar2 == 0)
      return 0x8007000e;
    puVar2[0] = 0;
    if (param_4 == 0 || g_vtxGrowSize == 0) {
      puVar2[1] = (((param_3 - 1) + param_1) / param_1) * param_1;
    } else {
      u32 uVar3 = ((g_vtxGrowSize - 1 + param_1) / param_1) * param_1;
      puVar2[1] = uVar3;
      if (uVar3 < param_3)
        puVar2[1] = param_3;
    }
    local_4 = (*(int(__stdcall**)(void*, u32, u32, u32, u32, void*, u32))(*(u32*)g_d3d9Device + 0x68))
                 (g_d3d9Device, puVar2[1], param_2, 0, 1, puVar2 + 2, 0);
    if (local_4 < 0)
      goto LAB_54e4;
    puVar2[4] = 0;
    puVar2[3] = *(u32*)((u8*)puVar1 + 4);
    if (*(u32*)((u8*)puVar1 + 4) != 0)
      *(u32*)(*(u32*)((u8*)puVar1 + 4) + 0x10) = (u32)puVar2;
    *(u32*)((u8*)puVar1 + 4) = (u32)puVar2;
    u32* puVar4 = (u32*)g_pool_6d0.FUN_011fd610();
    if (puVar4 == 0)
      return 0x8007000e;
    puVar4[0] = puVar2[2];
    puVar4[1] = *(u32*)((u8*)puVar1 + 8);
    *(u32*)((u8*)puVar1 + 8) = (u32)puVar4;
  }

  *param_5 = puVar2[2];
  *param_6 = puVar2[0] / param_1;
  u32 uVar3 = puVar2[1];
  puVar2[1] = uVar3 - param_3;
  puVar2[0] = puVar2[0] + param_3;
  if (uVar3 - param_3 != 0)
    return local_4;
  if (puVar2[4] != 0)
    *(u32*)(puVar2[4] + 0xc) = puVar2[3];
  if (puVar2[3] != 0)
    *(u32*)(puVar2[3] + 0x10) = puVar2[4];
  if (puVar2 == (u32*)*(u32*)((u8*)puVar1 + 4))
    *(u32*)((u8*)puVar1 + 4) = puVar2[3];
LAB_54e4:
  g_pool_6bc.FUN_011fd6b0(puVar2);
  return local_4;
}


// ===================================================================================
//  FUN_011f5500 @ 0x011f5500 -- return a range to the vertex-buffer pool (coalesce)
// @ 0x011f5500
// ===================================================================================
void FUN_011f5500(u32 param_1, u32 param_2, int param_3, int param_4, int param_5)
{
  u16* puVar3 = (u16*)g_vtxPoolHead;
  if (puVar3 == 0)
    return;
  while (param_1 != *(u16*)puVar3 || param_2 != *(u16*)((u8*)puVar3 + 2)) {
    u16* nxt = *(u16**)((u8*)puVar3 + 0xc);
    if (nxt == 0)
      return;
    puVar3 = nxt;
  }

  int* piVar2;
  for (piVar2 = (int*)*(u32*)((u8*)puVar3 + 4); piVar2 != 0; piVar2 = (int*)piVar2[3]) {
    if (param_4 == piVar2[2] &&
        (piVar2[1] + piVar2[0] == param_5 || param_3 + param_5 == piVar2[0]))
      break;
  }
  if (piVar2 == 0) {
    piVar2 = (int*)g_pool_6bc.FUN_011fd610();
    piVar2[2] = param_4;
    piVar2[0] = param_5;
    piVar2[1] = param_3;
    piVar2[4] = 0;
    piVar2[3] = *(u32*)((u8*)puVar3 + 4);
    if (*(u32*)((u8*)puVar3 + 4) != 0)
      *(u32*)(*(u32*)((u8*)puVar3 + 4) + 0x10) = (u32)piVar2;
    *(u32*)((u8*)puVar3 + 4) = (u32)piVar2;
    return;
  }

  for (;;) {
    if (piVar2[0] + piVar2[1] == param_5) {
      piVar2[1] += param_3;
    } else if (param_3 + param_5 == piVar2[0]) {
      piVar2[0] = param_5;
      piVar2[1] += param_3;
    }
    int iVar5 = piVar2[0];
    int size2 = piVar2[1];
    int* piVar4 = (int*)*(u32*)((u8*)puVar3 + 4);
    while (piVar4 != 0 &&
           (param_4 != piVar4[2] ||
            (piVar4[0] + piVar4[1] != iVar5 && size2 + iVar5 != piVar4[0])))
      piVar4 = (int*)piVar4[3];
    if (piVar4 == 0)
      return;
    if (piVar2[4] != 0)
      *(int*)(piVar2[4] + 0xc) = piVar2[3];
    if (piVar2[3] != 0)
      *(int*)(piVar2[3] + 0x10) = piVar2[4];
    if (piVar2 == (int*)*(u32*)((u8*)puVar3 + 4))
      *(int*)((u8*)puVar3 + 4) = piVar2[3];
    g_pool_6bc.FUN_011fd6b0(piVar2);
    piVar2 = piVar4;
  }
}


// ===================================================================================
//  FUN_011f5630 @ 0x011f5630 -- reset the vertex-buffer pool state
// @ 0x011f5630
// ===================================================================================
void FUN_011f5630(void)
{
  for (int i = 0; i < 12; ++i)
    g_vtxSlots[i] = 0;

  for (u32* p = (u32*)g_vtxFreeHead; p != 0; p = (u32*)p[4]) {
    u32 obj = p[0];
    if (obj != 0) {
      (*(int(__stdcall**)(void*))(*(u32*)obj + 8))((void*)obj);
      p[0] = 0;
    }
    p[2] = 0;
    p[3] = 0;
  }
  g_pool_75c.FUN_011fd5d0();
}


// ===================================================================================
//  FUN_011f56b0 @ 0x011f56b0 -- get/create a vertex buffer of a given size
// @ 0x011f56b0
// ===================================================================================
int FUN_011f56b0(u32 param_1, void** param_2, u32 param_3)
{
  u32* puVar2 = 0;
  u32* puVar4;
  for (puVar4 = (u32*)g_vtxFreeHead; puVar4 != 0; puVar4 = (u32*)puVar4[4]) {
    if (puVar4[2] == 0) {
      if (puVar4[1] == param_1)
        break;
      if (puVar2 == 0 || puVar2[1] < param_1)
        puVar2 = puVar4;
    }
  }
  if (puVar4 != 0) {
    puVar4[3] = param_3;
    puVar4[2] = 1;
    *param_2 = (void*)puVar4[0];
    return 0;
  }
  if (puVar2 == 0) {
    puVar2 = (u32*)g_pool_75c.FUN_011fd610();
    if (puVar2 == 0)
      return 0x8007000e;
    puVar2[4] = g_vtxFreeHead;
    g_vtxFreeHead = (u32)puVar2;
  } else {
    (*(int(__stdcall**)(void*))(*(u32*)puVar2[0] + 8))((void*)puVar2[0]);
  }
  int iVar1 = (*(int(__stdcall**)(void*, u32, u32, u32, u32, void*, u32))(*(u32*)g_d3d9Device + 0x68))
                (g_d3d9Device, param_1, 0x208, 0, 0, puVar2, 0);
  if (iVar1 >= 0) {
    puVar2[3] = param_3;
    puVar2[2] = 1;
    puVar2[1] = param_1;
    *param_2 = (void*)puVar2[0];
  }
  return iVar1;
}


// ===================================================================================
//  FUN_011f5770 @ 0x011f5770 -- mark a vertex buffer as free
// @ 0x011f5770
// ===================================================================================
void FUN_011f5770(int param_1)
{
  int* p = (int*)g_vtxFreeHead;
  while (p != 0) {
    if (p[0] == param_1) {
      p[2] = 0;
      p[3] = 0;
      return;
    }
    p = (int*)p[4];
  }
}


// ===================================================================================
//  FUN_011f57a0 @ 0x011f57a0 -- allocate within the current vertex-buffer slot
// @ 0x011f57a0
// ===================================================================================
int FUN_011f57a0(u32 param_1, int param_2, void** param_3, void** param_4, u32* param_5)
{
  u32 slot = g_vtxCurSlot;
  u32 vb   = g_vtxSlots[slot * 3 + 0];
  if (vb == 0)
    return 0x8007000e;
  u32 used = g_vtxSlots[slot * 3 + 2];
  u32 cap  = g_vtxSlots[slot * 3 + 1];

  u32 need = (u32)param_2 * param_1;
  u32 uVar5 = ((used + param_1 - 1) / param_1) * param_1;
  u32 local = need + uVar5;

  if (cap < need + uVar5) {
    // look for a different slot with enough room
    u32 i = 0, off = 0;
    bool found = false;
    do {
      if (g_vtxCurSlot != i) {
        u32 used_i = *(u32*)((u8*)g_vtxSlots + off + 8);
        u32 cap_i  = *(u32*)((u8*)g_vtxSlots + off + 4);
        u32 a = ((used_i + param_1 - 1) / param_1) * param_1;
        local = need + a;
        if (local <= cap_i) {
          g_vtxCurSlot = i;
          uVar5 = a;
          found = (i < 4);
          if (found)
            break;
        }
      }
      off += 0xc;
      ++i;
    } while (off < 0x30);
    if (!found) {
      ++g_vtxCurSlot;
      if (g_vtxCurSlot > 3)
        g_vtxCurSlot = 0;
      uVar5 = 0;
      local = need;
    }
  }

  slot = g_vtxCurSlot;
  if (g_vtxSlots[slot * 3 + 1] < need) {
    // grow: recreate the D3D buffer for this slot
    u32 vb_cur = g_vtxSlots[slot * 3 + 0];
    for (u32* e = (u32*)g_vtxFreeHead; e != 0; e = (u32*)e[4]) {
      if (e[0] == vb_cur) {
        e[2] = 0;
        e[3] = 0;
        break;
      }
    }
    g_vtxSlots[g_vtxCurSlot * 3 + 1] = need;
    if (FUN_011f56b0(need, (void**)(g_vtxSlots + g_vtxCurSlot * 3), 0) < 0)
      return 0x8007000e;
    g_vtxSlots[g_vtxCurSlot * 3 + 2] = 0;
  }

  vb = g_vtxSlots[g_vtxCurSlot * 3 + 0];
  *param_3 = (void*)vb;

  int hr;
  if (uVar5 == 0) {
    hr = (*(int(__stdcall**)(void*, u32, u32, void**, u32))(*(u32*)vb + 0x2c))
           ((void*)vb, 0, need, param_4, 0x2000);
    *param_5 = 0;
  } else {
    hr = (*(int(__stdcall**)(void*, u32, u32, void**, u32))(*(u32*)vb + 0x2c))
           ((void*)vb, uVar5, need, param_4, 0x1000);
    *param_5 = uVar5 / param_1;
  }
  g_vtxSlots[g_vtxCurSlot * 3 + 2] = local;
  return hr;
}


// ===================================================================================
//  FUN_011f5940 @ 0x011f5940 -- release a D3D buffer
// @ 0x011f5940
// ===================================================================================
void FUN_011f5940(void* param_1)
{
  (*(int(__stdcall**)(void*))(*(u32*)param_1 + 0x30))(param_1);
}


// ===================================================================================
//  FUN_011f5950 @ 0x011f5950 -- advance the current vertex-buffer slot
// @ 0x011f5950
// ===================================================================================
void FUN_011f5950(void)
{
  u32 c = g_vtxCurSlot + 1;
  u32 z = 0;
  g_vtxSlots[2] = z;
  g_vtxSlots[5] = z;
  g_vtxSlots[8] = z;
  g_vtxSlots[11] = z;
  g_vtxCurSlot = c;
  if (c >= 4)
    g_vtxCurSlot = z;
}


// ===================================================================================
//  FUN_011f5980 @ 0x011f5980 -- release all vertex buffers
// @ 0x011f5980
// ===================================================================================
void FUN_011f5980(void)
{
  for (u32* p = (u32*)g_vtxFreeHead; p != 0; p = (u32*)p[4]) {
    u32 obj = p[0];
    if (obj != 0) {
      (*(int(__stdcall**)(void*))(*(u32*)obj + 8))((void*)obj);
      p[0] = 0;
    }
    u32 next = p[3];
    if (next != 0)
      *(u32*)(next + 4) = 0;
    else
      p[2] = 0;
  }
}


// ===================================================================================
//  FUN_011f59c0 @ 0x011f59c0 -- restore the vertex-buffer pool buffers
// @ 0x011f59c0
// ===================================================================================
void FUN_011f59c0(void)
{
  for (u32* p = (u32*)g_vtxFreeHead; p != 0; p = (u32*)p[4]) {
    (*(int(__stdcall**)(void*, u32, u32, u32, u32, void*, u32))(*(u32*)g_d3d9Device + 0x68))
      (g_d3d9Device, p[1], 0x208, 0, 0, p, 0);
    if (p[3] != 0)
      *(u32*)(p[3] + 4) = p[0];
  }
  g_vtxCurSlot = 0;
  u32 off = 0;
  do {
    if (FUN_011f56b0(*(u32*)((u8*)g_vtxSlots + off + 4),
                     (void**)((u8*)g_vtxSlots + off), 0) < 0)
      return;
    *(u32*)((u8*)g_vtxSlots + off + 8) = 0;
    off += 0xc;
  } while (off < 0x30);
}


// ===================================================================================
//  FUN_011f5a40 @ 0x011f5a40 -- create the vertex-slot pool
// @ 0x011f5a40
// ===================================================================================
u32 FUN_011f5a40(void)
{
  if (g_vtxInited2 != 0)
    return 0;
  g_pool_75c.FUN_011fd530(0x14, 4);
  g_vtxFreeHead = 0;
  if (g_vtxPoolSize == 0)
    return 1;
  g_vtxCurSlot = 0;
  u32 off = 0;
  do {
    if (FUN_011f56b0(g_vtxPoolSize, (void**)((u8*)g_vtxSlots + off), 0) < 0)
      return 0;
    *(u32*)((u8*)g_vtxSlots + off + 4) = g_vtxPoolSize;
    *(u32*)((u8*)g_vtxSlots + off + 8) = 0;
    off += 0xc;
  } while (off < 0x30);
  return 1;
}


// ===================================================================================
//  FUN_011f5ac0 @ 0x011f5ac0 -- create the index-buffer pool
// @ 0x011f5ac0
// ===================================================================================
u32 FUN_011f5ac0(void)
{
  if (g_idxInited != 0)
    return 0;
  g_pool_7b4.FUN_011fd530(0x10, 0x10);
  g_idxFreeHead = 0;
  g_pool_7a0.FUN_011fd530(0x14, 100);
  g_pool_7c8.FUN_011fd530(8, 100);
  return 1;
}


// ===================================================================================
//  FUN_011f5b10 @ 0x011f5b10 -- destroy the index-buffer pool
// @ 0x011f5b10
// ===================================================================================
void FUN_011f5b10(void)
{
  if (g_idxFreeHead != 0) {
    u32 e;
    u32 iVar1;
    do {
      e = g_idxFreeHead;
      iVar1 = *(u32*)(e + 4);
      while (iVar1 != 0) {
        u32 node = *(u32*)(g_idxFreeHead + 4);
        u32 nxt = *(u32*)(node + 0xc);
        g_pool_7a0.FUN_011fd6b0((void*)node);
        *(u32*)(g_idxFreeHead + 4) = nxt;
        iVar1 = *(u32*)(g_idxFreeHead + 4);
      }
      iVar1 = *(u32*)(g_idxFreeHead + 8);
      while (iVar1 != 0) {
        u32* p = (u32*)*(u32*)(g_idxFreeHead + 8);
        iVar1 = p[1];
        if (p[0] != 0)
          (*(int(__stdcall**)(void*))(*(u32*)p[0] + 8))((void*)p[0]);
        g_pool_7c8.FUN_011fd6b0((void*)*(u32*)(g_idxFreeHead + 8));
        *(u32*)(g_idxFreeHead + 8) = iVar1;
        iVar1 = *(u32*)(g_idxFreeHead + 8);
      }
      iVar1 = *(u32*)(g_idxFreeHead + 0xc);
      g_pool_7b4.FUN_011fd6b0((void*)g_idxFreeHead);
      g_idxFreeHead = iVar1;
    } while (iVar1 != 0);
    g_idxFreeHead = 0;
  }
  g_pool_7c8.FUN_011fd5d0();
  g_pool_7a0.FUN_011fd5d0();
  g_pool_7b4.FUN_011fd5d0();
}


// ===================================================================================
//  FUN_011f5bd0 @ 0x011f5bd0 -- allocate a range from the index-buffer pool
// @ 0x011f5bd0
// ===================================================================================
int FUN_011f5bd0(u32 param_1, u32 param_2, u32 param_3, int param_4, u32* param_5, u32* param_6)
{
  u16* puVar1 = 0;
  u32* puVar2;
  int local_4 = 0;

  for (u16* e = (u16*)g_idxFreeHead; e != 0; e = *(u16**)((u8*)e + 0xc)) {
    if (param_1 == *(u16*)e && param_2 == *(u16*)((u8*)e + 2)) { puVar1 = e; break; }
  }
  if (puVar1 == 0) {
    puVar1 = (u16*)g_pool_7b4.FUN_011fd610();
    if (puVar1 == 0)
      return 0x8007000e;
    *(u16*)puVar1 = (u16)param_1;
    *(u16*)((u8*)puVar1 + 2) = (u16)param_2;
    *(u32*)((u8*)puVar1 + 4) = 0;
    *(u32*)((u8*)puVar1 + 8) = 0;
    *(u32*)((u8*)puVar1 + 0xc) = g_idxFreeHead;
    g_idxFreeHead = (u32)puVar1;
  }

  if (param_4 == 0 || g_idxGrowSize == 0) {
    puVar2 = 0;
  } else {
    for (puVar2 = (u32*)*(u32*)((u8*)puVar1 + 4);
         puVar2 != 0 && puVar2[1] < param_3;
         puVar2 = (u32*)puVar2[3]) {
    }
  }

  if (puVar2 == 0) {
    puVar2 = (u32*)g_pool_7a0.FUN_011fd610();
    if (puVar2 == 0)
      return 0x8007000e;
    puVar2[0] = 0;
    if (param_4 == 0 || g_idxGrowSize == 0) {
      puVar2[1] = (((param_1 - 1) + param_3) / param_1) * param_1;
    } else {
      u32 uVar3 = ((g_idxGrowSize - 1 + param_1) / param_1) * param_1;
      puVar2[1] = uVar3;
      if (uVar3 < param_3)
        puVar2[1] = param_3;
    }
    local_4 = (*(int(__stdcall**)(void*, u32, u32, u32, u32, void*, u32))(*(u32*)g_d3d9Device + 0x6c))
                 (g_d3d9Device, puVar2[1], param_2, (u32)(param_1 != 2) + 0x65, 1, puVar2 + 2, 0);
    if (local_4 < 0)
      goto LAB_5d8f;
    puVar2[4] = 0;
    puVar2[3] = *(u32*)((u8*)puVar1 + 4);
    if (*(u32*)((u8*)puVar1 + 4) != 0)
      *(u32*)(*(u32*)((u8*)puVar1 + 4) + 0x10) = (u32)puVar2;
    *(u32*)((u8*)puVar1 + 4) = (u32)puVar2;
    u32* puVar4 = (u32*)g_pool_7c8.FUN_011fd610();
    if (puVar4 == 0)
      return 0x8007000e;
    puVar4[0] = puVar2[2];
    puVar4[1] = *(u32*)((u8*)puVar1 + 8);
    *(u32*)((u8*)puVar1 + 8) = (u32)puVar4;
  }

  *param_5 = puVar2[2];
  *param_6 = puVar2[0] / param_1;
  u32 uVar3 = puVar2[1];
  puVar2[1] = uVar3 - param_3;
  puVar2[0] = puVar2[0] + param_3;
  if (uVar3 - param_3 != 0)
    return local_4;
  if (puVar2[4] != 0)
    *(u32*)(puVar2[4] + 0xc) = puVar2[3];
  if (puVar2[3] != 0)
    *(u32*)(puVar2[3] + 0x10) = puVar2[4];
  if (puVar2 == (u32*)*(u32*)((u8*)puVar1 + 4))
    *(u32*)((u8*)puVar1 + 4) = puVar2[3];
LAB_5d8f:
  g_pool_7a0.FUN_011fd6b0(puVar2);
  return local_4;
}
