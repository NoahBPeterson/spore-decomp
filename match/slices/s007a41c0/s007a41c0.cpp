// slice s007a41c0 — SP::cGraphicsSystem accessors (bake/effects RTT rect bookkeeping,
// debug-draw configuration) rewritten as real C++.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;

#include <math.h>
#include <stdlib.h>
#include <intrin.h>

extern "C" long _InterlockedExchange(volatile long* target, long value);

// ---------------------------------------------------------------------------
// External entry points still referenced by the not-yet-ported naked blocks.
// ---------------------------------------------------------------------------
// Retail-address entry points.  Declared variadic so that every call shape
// used below type-checks; only the returned value and call-site placement
// matter for the byte comparison (the target address is a masked reloc).
extern "C" void* EXT_67dd10();
extern "C" void  EXT_67df60(...);
extern "C" void  EXT_6a25a0();
extern "C" void  EXT_6ad7c0(...);
extern "C" void  EXT_6de350(...);
extern "C" void  EXT_6ec4a0(...);
extern "C" void* EXT_720200(...);
extern "C" void* EXT_75fb90();
extern "C" void* EXT_67dd60();
extern "C" void  EXT_762a00(...);
extern "C" void  EXT_762a30(...);
extern "C" void  EXT_762b70();
extern "C" void  EXT_762c60();
extern "C" void  EXT_7a3ce0(...);
extern "C" void* EXT_7a3df0(...);
extern "C" void  EXT_7a4380();
extern "C" void  EXT_7a44b0();
extern "C" void  EXT_7a4600();
extern "C" void  EXT_7a4650();
extern "C" void  EXT_7a4710();
extern "C" void  EXT_7a47c0();
extern "C" void  EXT_7c3d30(...);
extern "C" void  EXT_cc8b50(...);
extern "C" void  EXT_f47380(...);
extern "C" void* EXT_f473a0(...);
extern "C" void  EXT_11f3620();
extern "C" void* FUN_011f3620(...);
extern "C" void  EXT_11f36a0();
extern "C" void  EXT_11f4f20();
extern "C" void  EXT_11f4fd0(...);
extern "C" void* EXT_11f8af0();
extern "C" void** FUN_11f8af0(...);
extern "C" void* FUN_00762b70(...);

// ---------------------------------------------------------------------------
// Types touched by the ported functions.  Offsets were read off the original
// disassembly; addresses of referenced globals/entry points are masked by the
// verifier, so only the instruction shape matters.
// ---------------------------------------------------------------------------

// A DirectX page/alloc pair used to reference an RTT texture rectangle.
struct TextureRectID {
  u32 mPageID;   // +0x0
  u32 mAllocID;  // +0x4
};

// SP::cPropertyList — query interface of the global application properties.
struct cPropertyList {
  bool GetDescription(u32 id);  // 0x6a25a0
};
extern cPropertyList* _sAppProperties;  // 0x15fd918

// Renderer (cIRenderer): only slot 0x54 is used here.
struct cIRenderer {
  virtual void vr00(); virtual void vr01(); virtual void vr02(); virtual void vr03();
  virtual void vr04(); virtual void vr05(); virtual void vr06(); virtual void vr07();
  virtual void vr08(); virtual void vr09(); virtual void vr10(); virtual void vr11();
  virtual void vr12(); virtual void vr13(); virtual void vr14(); virtual void vr15();
  virtual void vr16(); virtual void vr17(); virtual void vr18(); virtual void vr19();
  virtual void vr20();
  virtual void RendererPreShutdown();  // +0x54
};

// RTT manager (cIRTTManager): slot 0x14 releases a rectangle.
struct cIRTTManager {
  virtual void vt00(); virtual void vt01(); virtual void vt02(); virtual void vt03();
  virtual void vt04();
  virtual void ReleaseRect(u32 pageID, u32 allocID);  // +0x14
};

// Buffer manager reached through the 0x67dd60 thunk; slot 0x34 creates a buffer.
struct cIBufferManager {
  virtual void vb00(); virtual void vb01(); virtual void vb02(); virtual void vb03();
  virtual void vb04(); virtual void vb05(); virtual void vb06(); virtual void vb07();
  virtual void vb08(); virtual void vb09(); virtual void vb10(); virtual void vb11();
  virtual void vb12();
  virtual void CreateBuffer(void* pBuffer);  // +0x34
};
extern "C" cIBufferManager* APP_GetBufferManager();  // 0x67dd60

// Lazily created buffer cached at cGraphicsSystem::mLazyBufferObject.
struct cLazyBuffer {
  void* mpValue;  // +0x0
  u32   mFlags;   // +0x4
};

// Object holding a pointer whose +8 sub-object is driven through its vtable.
struct cInnerObject {
  virtual void i00();  // +0x0
  virtual void i01();  // +0x4
};
struct cRefTarget {
  u32          mUnk00;   // +0x0
  u32          mUnk04;   // +0x4
  cInnerObject mInner;   // +0x8
};
struct cObjectRef {
  cRefTarget* mpObject;  // +0x0
  void Flush();
};

// SP::cGraphicsSystem — the graphics manager singleton.
struct cGraphicsSystem {
  // base_cIGraphicsSystem vtable (only slot 0x24 is called here)
  virtual void vg00(); virtual void vg01(); virtual void vg02(); virtual void vg03();
  virtual void vg04(); virtual void vg05(); virtual void vg06(); virtual void vg07();
  virtual void vg08();
  virtual void CreateBakeBuffer(int index);  // +0x24

  u32           mUnk04[3];                       // +0x04
  cIRenderer*   mRenderer;                        // +0x10
  void*         mTextureManager;                  // +0x14
  cIRTTManager* mRTTManager;                      // +0x18
  u32           mUnk1c;                           // +0x1c
  void*         mMaterialManager;                 // +0x20
  void*         mLightingManager;                 // +0x24
  void*         mModelManager;                    // +0x28
  u32           mUnk2c[10];                       // +0x2c
  void*         mGIFExportTexture;                // +0x54
  u32           mUnk58[2];                        // +0x58
  void*         mAOTexture;                       // +0x60
  void*         mFinalBakedTexture;               // +0x64
  u32           mUnk68;                           // +0x68
  void*         mShadowBlurTexture;               // +0x6c
  void*         mShadowTexture;                   // +0x70
  u32           mUnk74[4];                        // +0x74
  cLazyBuffer*  mLazyBufferObject;                // +0x84
  void*         mBakeBuffers[5];                  // +0x88
  void*         mEffectsBuffers[4];               // +0x9c
  TextureRectID mEffectsBufferRectIDs[4];         // +0xac
  u8            mByteFlags[4];                    // +0xcc
  TextureRectID mSplatterTextureRectID;           // +0xd0
  TextureRectID mGIFExportRectID;                 // +0xd8
  TextureRectID mRectE0;                          // +0xe0
  TextureRectID mRectE8;                          // +0xe8
  TextureRectID mFinalBakedTextureRectID;         // +0xf0
  TextureRectID mSmallFinalBakedTextureRectID;    // +0xf8
  TextureRectID mUnk100;                          // +0x100
  TextureRectID mUnk108;                          // +0x108
  u32           mUnk110[10];                      // +0x110
  TextureRectID mBakeBufferRectIDs[6];            // +0x138
  u32           mUnk168[2];                       // +0x168
  u16           mDebugParam;                      // +0x170
  u16           mUnk172;                          // +0x172
  f32           mDebugRadius;                     // +0x174
  f32           mDebugNear;                       // +0x178
  f32           mDebugFar;                        // +0x17c
  f32           mDebugRange;                      // +0x180
  f32           mDebugDistance;                   // +0x184
  u8            mShowDebug;                       // +0x188
  u8            mUnk189[7];                       // +0x189
  u8            mDebugFlushState;                 // +0x190
  u8            mUnk191[3];                       // +0x191

  void  SetDebugParam(u16 v);
  u32   ShouldShowDebug();
  void  SetDebugRange(f32 range, f32 distance, f32 near_, f32 far_);
  void  GetRectID(TextureRectID* out, u32 id);
  void  GetCurrentCubemapFaceRectID(u32* out);
  void  SetCurrentCubemapFaceRectID(const u32* in);
  u8    GetByteFlag(u32 i);
  void  SetByteFlag(u32 i, u8 v);
  bool  PreShutdown();
  void  RecycleEffectsBuffers();
  void* GetLazyBuffer();
  void  GetBakeBuffer(u32* out, int index);

  u32   SwapRendererDevice();                            // 0x007a4cb0
  void  UpdateManagers(u32 param_1, f32 param_2);        // 0x007a4d90
  void  RecycleBakingRTTs(u32 param_1, u32 param_2);     // 0x007a5020
  void  ReleaseRTT(void*& texture, const TextureRectID& rect);
};

// SP::cDebugDraw — the debug-overlay interpolator updated once per frame.
struct cDebugDraw {
  u8   mUnk00[0x174];
  f32  mDebugRadius;    // +0x174
  f32  mDebugNear;      // +0x178
  f32  mDebugFar;       // +0x17c
  f32  mDebugRange;     // +0x180
  f32  mDebugDistance;  // +0x184
  u8   mUnk188[8];      // +0x188
  void Update(u32 param_1, f32 param_2);  // 0x007a4e40
};

// The application singleton reached through 0x67dd10; only the camera accessor
// at vtable slot 0x58 is called from this slice.
struct cApp {
  u8  mUnk00[0x58];
  virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
  virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
  virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
  virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
  virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
  virtual void a20(); virtual void a21();
  virtual char* GetCameraViewer(u32* outPos, u32 a, u32 b, u32 c);};
extern "C" cApp* APP_GetApp();  // 0x67dd10

// The camera/viewer object returned by cApp::GetCameraViewer.  Only the
// refiner at 0x7c3d30 (this-call) is reached from this slice.
struct cViewer {
  virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
  virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
  void Refine(u32* pos, u32 a, u32 b, u32 c);
};

// ---------------------------------------------------------------------------
// Ported functions
// ---------------------------------------------------------------------------

// @ 0x007a4a60
void cGraphicsSystem::SetDebugParam(u16 v) {
  mDebugParam = v;
}

// @ 0x007a4a80
u32 cGraphicsSystem::ShouldShowDebug() {
  if (mShowDebug != 0) {
    if (_sAppProperties->GetDescription(0x64574abu)) {
      return 1;
    }
  }
  return 0;
}

// @ 0x007a4ac0
void cGraphicsSystem::SetDebugRange(f32 range, f32 distance, f32 near_, f32 far_) {
  mDebugFar = far_;
  mDebugNear = near_;
  mDebugDistance = distance;
  mDebugRange = range;
}

// @ 0x007a4b10
void cGraphicsSystem::GetRectID(TextureRectID* out, u32 id) {
  if (id == 1) {
    const TextureRectID r = mGIFExportRectID;
    out[0] = r;
    return;
  }
  if (id == 0) {
    const TextureRectID r = mSplatterTextureRectID;
    out[0] = r;
    return;
  }
  if (id == 3) {
    const TextureRectID r = mSmallFinalBakedTextureRectID;
    out[0] = r;
    return;
  }
  if (id == 4) {
    const TextureRectID r = mFinalBakedTextureRectID;
    out[0] = r;
    return;
  }
  out->mPageID = 0;
  out->mAllocID = 0xffffffffu;
}

// @ 0x007a4bb0
void cGraphicsSystem::GetCurrentCubemapFaceRectID(u32* out) {
  out[0] = mBakeBufferRectIDs[1].mPageID;
  out[1] = mBakeBufferRectIDs[1].mAllocID;
}

// @ 0x007a4be0
void cGraphicsSystem::SetCurrentCubemapFaceRectID(const u32* in) {
  mBakeBufferRectIDs[1].mPageID = in[0];
  mBakeBufferRectIDs[1].mAllocID = in[1];
}

// @ 0x007a4c00
u8 cGraphicsSystem::GetByteFlag(u32 i) {
  return mByteFlags[i];
}

// @ 0x007a4c10
void cGraphicsSystem::SetByteFlag(u32 i, u8 v) {
  mByteFlags[i] = v;
}

// @ 0x007a4c90
void cObjectRef::Flush() {
  cRefTarget* const p = mpObject;
  if (p) {
    p->mInner.i01();
  }
}

// @ 0x007a4d20
bool cGraphicsSystem::PreShutdown() {
  cIRenderer* const r = mRenderer;
  if (r) {
    r->RendererPreShutdown();
  }
  return true;
}

// @ 0x007a4d40
void cGraphicsSystem::RecycleEffectsBuffers() {
  for (int i = 0; i < 4; ++i) {
    if (mEffectsBuffers[i] != 0) {
      mRTTManager->ReleaseRect(mEffectsBufferRectIDs[i].mPageID,
                               mEffectsBufferRectIDs[i].mAllocID);
      mEffectsBuffers[i] = 0;
    }
  }
}

// @ 0x007a4ef0
void* cGraphicsSystem::GetLazyBuffer() {
  cLazyBuffer* const b = mLazyBufferObject;
  if ((b->mFlags & 1) == 0) {
    cIBufferManager* const mgr = APP_GetBufferManager();
    mgr->CreateBuffer(b);
  }
  return b->mpValue;
}

// @ 0x007a4f10
void cGraphicsSystem::GetBakeBuffer(u32* out, int index) {
  if (mBakeBuffers[index + 1] == 0) {
    CreateBakeBuffer(index);
  }
  out[0] = mBakeBufferRectIDs[index + 2].mPageID;
  out[1] = mBakeBufferRectIDs[index + 2].mAllocID;
}
// ===========================================================================
// Static-buffer subsystem (cStaticBuffer / cStaticBufferDraw).
// Support types come first so that no declaration sits between a
// `// @ 0x<va>` marker and the function definition it names.
// ===========================================================================

// One accumulated element: 6 dwords (0x18 bytes).
struct MeshElement {
  u32 v0;  // +0x00
  u32 v1;  // +0x04
  u32 v2;  // +0x08
  u32 v3;  // +0x0c
  u32 v4;  // +0x10
  u32 v5;  // +0x14
};

// Growable element vector (EASTL sp_vector layout).
struct MeshVector {
  MeshElement* mpBegin;     // +0x00
  MeshElement* mpEnd;       // +0x04
  MeshElement* mpCapacity;  // +0x08

  void grow(MeshElement* at, MeshElement* src);  // 0x007a44b0
  void push_back(MeshElement* src);              // 0x007a4600
};

// SP::cStaticBuffer — the per-draw merged static geometry buffer.
// Field offsets are exactly those touched by the routines below.
struct cStaticBuffer {
  virtual void sb00();  // +0x00
  virtual void sb01();  // +0x04  scalar deleting destructor

  u32         mUnk04;             // +0x04
  u32         mUnk08;             // +0x08  element count of vector A
  u32         mUnk0c;             // +0x0c  vector A data pointer
  u32         mUnk10;             // +0x10  pending cursor
  u32         mUnk14;             // +0x14
  u32         mUnk18;             // +0x18
  MeshVector  mVertexBuffers;     // +0x1c .. +0x24
  u32         mUnk28;             // +0x28
  u32         mUnk2c;             // +0x2c  vector B data pointer
  MeshVector  mDrawVector;        // +0x30 .. +0x38
  u32         mUnk3c;             // +0x3c
  u32         mUnk40;             // +0x40  pending-cursor flag byte
  u32         mUnk44;             // +0x44
  u32         mUnk48;             // +0x48

  cStaticBuffer* Ctor(u32 param_1, u32 param_2);   // 0x007a4380
  ~cStaticBuffer();                                // 0x007a4220
  void Flush();                                    // 0x007a4710
  u32  GetVertexBuffer(u32 numVertices, u32* outCount, u32* outStride);  // 0x007a47c0
  void SnapshotPending();                          // 0x007a4650
};

// The singleton owning the shared cStaticBuffer.
struct cStaticBufferDraw {
  cStaticBuffer buffer;  // +0x00  (0x4c bytes; the ctor sets +0x48)

  void Ctor(u32 param_1, u32 param_2, u32 param_3, u32 count);  // 0x007a4420
};

extern cStaticBufferDraw* g_pStaticBufferDraw;  // 0x15ddc84

// The retail entry points (EXT_*) are declared in this file's preamble.

// ---------------------------------------------------------------------------
// @ 0x007a41c0  cStaticBufferDraw factory: allocate a 0x44-byte
// cStaticBufferDraw and run its constructor.  The retail SEH frame exists only
// to unwind the constructor; expressed here as a plain allocation + ctor call.
// ---------------------------------------------------------------------------
void* __cdecl FUN_007a41c0(void* param_1) {
  cStaticBufferDraw* p =
      (cStaticBufferDraw*)EXT_f473a0(0x44, "Graphics/StaticBufferDraw",
                                     0, 0, 0, 0, (const char*)param_1);
  if (p != 0) {
    EXT_7a3df0(p);
  }
  return p;
}

// ---------------------------------------------------------------------------
// @ 0x007a4220  SP::cStaticBuffer::~cStaticBuffer — release every retained
// vertex/index buffer, then free the three element arrays.
// ---------------------------------------------------------------------------
cStaticBuffer::~cStaticBuffer() {
  int nVertex = (int)(mVertexBuffers.mpEnd - mVertexBuffers.mpBegin);
  for (int i = 0; i < nVertex; ++i) {
    if (mVertexBuffers.mpBegin[i].v0 != 0) {
      EXT_762a00((void*)mVertexBuffers.mpBegin[i].v0);
    }
    mVertexBuffers.mpBegin[i].v0 = 0;
  }
  int nIndex = (int)(mDrawVector.mpBegin - mVertexBuffers.mpBegin);
  for (int i = 0; i < nIndex; ++i) {
    if (mDrawVector.mpBegin[i].v0 != 0) {
      EXT_762a30((void*)mDrawVector.mpBegin[i].v0);
    }
    mDrawVector.mpBegin[i].v0 = 0;
  }
  if (mDrawVector.mpCapacity != 0) {
    EXT_f47380(mDrawVector.mpCapacity);
  }
  if (mVertexBuffers.mpBegin != 0) {
    EXT_f47380(mVertexBuffers.mpBegin);
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a4320  Destroy the cStaticBufferDraw singleton.
// ---------------------------------------------------------------------------
void __cdecl FUN_007a4320() {
  cStaticBufferDraw* const p = g_pStaticBufferDraw;
  if (p != 0) {
    EXT_6de350(p);
    g_pStaticBufferDraw = 0;
    EXT_f47380(p);
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a4380  cStaticBuffer constructor.  `ret 8` — two stack arguments.
// ---------------------------------------------------------------------------
cStaticBuffer* cStaticBuffer::Ctor(u32 param_1, u32 param_2) {
  mUnk04 = 0;
  mUnk08 = 0;
  mUnk0c = 0;
  mUnk10 = 0;
  mVertexBuffers.mpBegin = 0;
  mVertexBuffers.mpEnd = 0;
  mVertexBuffers.mpCapacity = 0;
  mDrawVector.mpBegin = 0;
  mDrawVector.mpEnd = 0;
  mDrawVector.mpCapacity = 0;
  mUnk44 = 0;
  mUnk48 = param_1;
  EXT_7a3ce0(this, param_2);
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x007a4420  cStaticBufferDraw constructor.  `ret 0x10` — four stack
// arguments.  Clamps the element count and builds the embedded cStaticBuffer.
// ---------------------------------------------------------------------------
void cStaticBufferDraw::Ctor(u32 param_1, u32 param_2, u32 param_3,
                             u32 count) {
  buffer.mUnk04 = (u32)(((int)count < 1) ? 0 : count);
  cStaticBuffer* p =
      (cStaticBuffer*)EXT_f473a0(0x4c, "Graphics/StaticBufferDraw", 0, 0, 0, 0);
  if (p != 0) {
    p->Ctor(param_2, param_3);
  }
  buffer.mDrawVector.mpCapacity = (MeshElement*)p;
  p->sb01();
}

// ---------------------------------------------------------------------------
// @ 0x007a44b0  MeshVector insert/grow for the 0x18-byte element.
// `ret 8`: ecx = vector, two stack arguments.
// ---------------------------------------------------------------------------
void MeshVector::grow(MeshElement* at, MeshElement* src) {
  MeshElement* const end = mpEnd;
  if (end != mpCapacity) {
    if ((at <= src) && (src < end)) {
      src = (MeshElement*)((char*)src + 0x18);
    }
    if (end != 0) {
      end->v0 = end[-1].v0;
      end->v1 = end[-1].v1;
      end->v2 = end[-1].v2;
      end->v3 = end[-1].v3;
      end->v4 = end[-1].v4;
      end->v5 = end[-1].v5;
    }
    EXT_cc8b50(at, (char*)mpEnd - 0x18, mpEnd);
    at->v0 = src->v0;
    at->v1 = src->v1;
    at->v2 = src->v2;
    at->v3 = src->v3;
    at->v4 = src->v4;
    at->v5 = src->v5;
    mpEnd = (MeshElement*)((char*)mpEnd + 0x18);
    return;
  }

  int count = (int)(end - mpBegin);
  if (count == 0) {
    count = 1;
  } else {
    count *= 2;
    if (count == 0) {
      return;
    }
  }
  MeshElement* const fresh =
      (MeshElement*)EXT_f473a0(count * 0x18, "Graphics", 0, 0,
                               "EASTL/allocator.h", 0xd1);
  MeshElement* ins = (MeshElement*)EXT_720200(fresh, at, mpEnd);
  if (ins != 0) {
    ins->v0 = src->v0;
    ins->v1 = src->v1;
    ins->v2 = src->v2;
    ins->v3 = src->v3;
    ins->v4 = src->v4;
    ins->v5 = src->v5;
  }
  MeshElement* const newEnd = (MeshElement*)EXT_720200(at, mpEnd, ins + 6);
  if (mpBegin != 0) {
    EXT_f47380(mpBegin);
  }
  mpBegin = fresh;
  mpEnd = newEnd;
  mpCapacity = (MeshElement*)((char*)fresh + count * 0x18);
}

// ---------------------------------------------------------------------------
// @ 0x007a4600  MeshVector push_back.  `ret 4`: ecx = vector, one argument.
// ---------------------------------------------------------------------------
void MeshVector::push_back(MeshElement* src) {
  MeshElement* const p = mpEnd;
  if (p < mpCapacity) {
    mpEnd = (MeshElement*)((char*)p + 0x18);
    if (p != 0) {
      p->v0 = src->v0;
      p->v1 = src->v1;
      p->v2 = src->v2;
      p->v3 = src->v3;
      p->v4 = src->v4;
      p->v5 = src->v5;
    }
  } else {
    grow(mpEnd, src);
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a4650  cStaticBuffer::SnapshotPending — publish the accumulated
// element counts into the draw vector and reset the pending cursors.
// ---------------------------------------------------------------------------
void cStaticBuffer::SnapshotPending() {
  cStaticBuffer* const d = &g_pStaticBufferDraw->buffer;
  u32 cursor = (u32)((char*)mUnk0c - (char*)mUnk08);
  u32 countA = (u32)((char*)mUnk10 - (char*)mUnk14);
  u32 countB;
  u32 stride;
  u32 start;
  if (d->mUnk40 != 0) {
    stride = (u32)((char*)d->mUnk2c - (char*)d->mDrawVector.mpBegin);
    start = 0;
    countB = (u32)((char*)d->mVertexBuffers.mpEnd -
                   (char*)d->mVertexBuffers.mpBegin);
  } else {
    stride = 0;
    start = 0xffffffffu;
    countB = 0;
  }
  mUnk18 = 0;
  d->mUnk40 = 0;
  d->mUnk14 = d->mUnk10;
  d->mDrawVector.mpBegin = (MeshElement*)d->mUnk2c;

  if (countA != 0 && ((int)stride < 0 || start != 0)) {
    // Merge with the previous entry when it describes the same contiguous run.
    if (d->mDrawVector.mpBegin != d->mDrawVector.mpEnd) {
      MeshElement* const tail = d->mDrawVector.mpEnd - 1;
      if (start == 0xffffffffu && tail->v0 == cursor) {
        tail->v2 += countA;
        return;
      }
    }
    MeshElement range;
    range.v0 = cursor;
    range.v1 = countB;
    range.v2 = 0;
    range.v3 = start;
    range.v4 = stride;
    range.v5 = countA;
    d->mDrawVector.push_back(&range);
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a4710  SP::cStaticBuffer::Flush — hand the current vertex/index
// buffers back to the singleton's retention vectors and reset the handles.
// ---------------------------------------------------------------------------
void cStaticBuffer::Flush() {
  cStaticBuffer* const d = &g_pStaticBufferDraw->buffer;
  if ((d->mVertexBuffers.mpEnd - d->mVertexBuffers.mpBegin != 0) ||
      (d->mUnk40 != 0)) {
    SnapshotPending();
  }
  if (mUnk0c != 0) {
    EXT_11f36a0();
    if (mVertexBuffers.mpEnd < mVertexBuffers.mpCapacity) {
      *(u32*)mVertexBuffers.mpEnd = mUnk0c;
      mVertexBuffers.mpEnd = (MeshElement*)((char*)mVertexBuffers.mpEnd + 4);
    } else {
      EXT_6ec4a0(mVertexBuffers.mpEnd, &mUnk0c);
    }
    mUnk0c = 0;
    mUnk14 = 0;
    mUnk10 = 0;
    mUnk08 = 0;
  }
  if (mUnk28 != 0) {
    EXT_11f4fd0(&mDrawVector.mpEnd);
    if (mDrawVector.mpBegin < mDrawVector.mpCapacity) {
      *(u32*)mDrawVector.mpBegin = mUnk28;
      mDrawVector.mpBegin = (MeshElement*)((char*)mDrawVector.mpBegin + 4);
    } else {
      EXT_6ec4a0(mDrawVector.mpBegin, &mUnk28);
    }
    mUnk28 = 0;
    mDrawVector.mpEnd = 0;
    mDrawVector.mpCapacity = 0;
    mUnk3c = 0;
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a47c0  SP::cStaticBuffer::GetVertexBuffer — reserve `numVertices`
// elements in the singleton's shared vertex buffer, flushing first when the
// request would not fit.  `ret 0xc`: ecx = this, three stack arguments.
// ---------------------------------------------------------------------------
u32 cStaticBuffer::GetVertexBuffer(u32 numVertices, u32* outCount,
                                   u32* outStride) {
  cStaticBuffer* const s = &g_pStaticBufferDraw->buffer;
  u32 have = s->mUnk04;   // currently reserved capacity
  u32 want = numVertices;
  if ((int)s->mUnk08 < (int)(s->mUnk10 + numVertices)) {
    if ((int)have >= 1) {
      u32 room = s->mUnk08 - s->mUnk10;
      if ((int)room < 0x31) {
        Flush();
        want = numVertices;
      }
    }
  }
  if (s->mUnk0c == 0) {
    if ((mUnk04 == 3) && (0x1ff8 < (int)want)) {
      want = 0x1ff8;
    }
    if ((int)have <= (int)want) {
      have = want;
    }
    s->mUnk08 = have;
    u32* const vb = (u32*)FUN_00762b70(mUnk44, have, 0, 0);
    s->mUnk0c = (u32)vb;
    u32 stride = s->mUnk08;
    if (stride == 0) {
      stride = vb[3];
    }
    int u = (int)FUN_011f3620(2, (u32)*(u8*)(*vb + 0xf) * vb[2],
                              (u32)*(u8*)(*vb + 0xf) * stride);
    if (u == 0) {
      want = 0;
    } else {
      s->mUnk10 = 0;
      s->mUnk14 = 0;
      s->mUnk18 = (u32)*(u8*)(*(u32*)s->mUnk0c + 0xf);
      s->mUnk28 = (u32)u;
    }
  }
  switch (mUnk04) {
    case 1:
    case 4:
      want -= want & 1;
      break;
    case 2:
      want = (want / 3) * 3;
      break;
    case 3:
      want -= want & 3;
      break;
    default:
      break;
  }
  *outStride = s->mUnk18;
  *outCount = s->mUnk10 * s->mUnk18 + s->mUnk28;
  s->mUnk10 += want;
  s->mUnk40 = 1;
  return want;
}

// ---------------------------------------------------------------------------
// @ 0x007a49e0  Direct3D9 capability probe: query the caps manager for the
// vertex- and pixel-shader version and test the active device for each.  The
// routine is cdecl (plain `ret`) and receives its arguments from the caller's
// registers/stack frame as the original did.
// ---------------------------------------------------------------------------
int __cdecl FUN_007a49e0(u32 param_1, u32 param_2, u32 param_3, u32 param_4,
                         u32 param_5) {
  (void)param_3;
  (void)param_4;
  (void)param_5;
  u32* const capsRoot = (u32*)FUN_11f8af0();
  u32* const caps = (u32*)capsRoot[0];
  u32* const d3d9 = *(u32**)0x16f89c8;   // _m_d3d9_ActiveState

  u32* const query = (u32*)FUN_11f8af0(caps, *(u32*)0x1712458, 1, 3, param_1);
  int rc = (int)(*(int(**)(u32*, u32))(d3d9[0] + 0x28))(d3d9, query[1]);
  if (rc < 0) {
    return 0;
  }

  u32* const capsRoot2 = (u32*)FUN_11f8af0();
  u32* const caps2 = (u32*)capsRoot2[0];
  u32* const query2 = (u32*)FUN_11f8af0(caps2, *(u32*)0x1712458,
                                        *(u32*)0x16f8bc4, param_1);
  rc = (int)(*(int(**)(u32*, u32))(d3d9[0] + 0x30))(d3d9, query2[1]);
  if (rc < 0) {
    return 0;
  }
  (void)param_2;
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x007a4cb0  Swap the renderer device held at +0x10 and probe it; on a
// failed probe drop the device again.
// ---------------------------------------------------------------------------
u32 cGraphicsSystem::SwapRendererDevice() {
  char* const fresh = (char*)EXT_75fb90();
  char* const old = (char*)mRenderer;
  if (fresh != old) {
    if (fresh != 0) {
      (*(void(**)(char*))*(void**)fresh)(fresh);
    }
    mRenderer = (cIRenderer*)fresh;
    if (old != 0) {
      u32* const vt = *(u32**)old;
      (*(void(**)(char*))(vt + 1))(old);
    }
  }
  char* const cur = (char*)mRenderer;
  {
    u32* const vt = *(u32**)cur;
    if ((*(char(**)(char*))(vt + 3))(cur) != 0) {
      EXT_67df60(cur);
      return 1;
    }
  }
  char* const dead = (char*)mRenderer;
  if (dead != 0) {
    mRenderer = 0;
    u32* const vt = *(u32**)dead;
    (*(void(**)(char*))(vt + 1))(dead);
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x007a4d90  SP::cGraphicsSystem::UpdateManagers.  `ret 8` — a frame
// identifier and the elapsed seconds.
// ---------------------------------------------------------------------------
void cGraphicsSystem::UpdateManagers(u32 param_1, f32 param_2) {
  bool flag = *(int*)(*(int*)((char*)_sAppProperties + 0x3c) + 0x130) != 0;
  if (mDebugFlushState != (u8)flag) {
    mDebugFlushState = (u8)flag;
    EXT_6ad7c0((u32)4);
    EXT_6ad7c0((u32)5);
    EXT_6ad7c0((u32)9);
    EXT_6ad7c0((u32)10);
  }
  char* const light = (char*)mLightingManager;
  if (light != 0) {
    u32* const vt = *(u32**)light;
    (*(void(**)(char*, int))(vt + 5))(light, (int)(param_2 * 1000.0f));
  }
  char* const tex = (char*)mTextureManager;
  if (tex != 0) {
    u32* const vt = *(u32**)tex;
    (*(void(**)(char*))(vt + 5))(tex);
  }
  char* const mat = (char*)mMaterialManager;
  if (mat != 0) {
    u32* const vt = *(u32**)mat;
    (*(void(**)(char*))(vt + 5))(mat);
  }
  char* const mod = (char*)mModelManager;
  if (mod != 0) {
    u32* const vt = *(u32**)mod;
    (*(void(**)(char*, u32, f32))(vt + 14))(mod, param_1, param_2);
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a4e40  SP::cDebugDraw::Update.  Plain `ret` with `ecx` read at entry,
// so the retail form is a fastcall taking only the object pointer.
// ---------------------------------------------------------------------------
void __fastcall FUN_007a4e40(cDebugDraw* thiz) {
  cDebugDraw* const self = thiz;
  // The camera accessor writes the current camera position into `pos`;
  // the viewer's refiner then adjusts it in place.
  u32 pos[3];
  const f32 lo = 0.0f;
  const f32 hi = 1.0f;
  cApp* const app = APP_GetApp();
  cViewer* const viewer = (cViewer*)app->GetCameraViewer(pos, 0, 0, 0);
  viewer->Refine(pos, 0, 0, 0);

  const f32 dx = *(f32*)&pos[0];
  const f32 dy = *(f32*)&pos[1];
  const f32 dz = *(f32*)&pos[2];
  const f32 dist = (f32)sqrt(dx * dx + dy * dy + dz * dz);

  f32 t = (dist - self->mDebugDistance) /
          (self->mDebugRange - self->mDebugDistance);
  t = __max(t, lo);
  t = __min(t, hi);
  self->mDebugRadius =
      (self->mDebugNear - self->mDebugFar) * t + self->mDebugFar;
}

// ---------------------------------------------------------------------------
// @ 0x007a4f50  Bake-texture rectangle dispatch.  `ret 8`: ecx = the renderer
// source object, one stack argument selecting which rectangle to fetch.
// ---------------------------------------------------------------------------
void __fastcall FUN_007a4f50(void* thiz, u32 /*unused*/, u32 which) {
  u32 rect[2] = { 0xffffffffu, 0xffffffffu };
  char* const self = (char*)thiz;
  u32* const vtbl = *(u32**)self;
  switch (which) {
    case 0: (*(void(**)(char*, u32*))(vtbl + (0xb0 / 4)))(self, rect); break;
    case 1: (*(void(**)(char*, u32*))(vtbl + (0xac / 4)))(self, rect); break;
    case 2: (*(void(**)(char*, u32*))(vtbl + (0xbc / 4)))(self, rect); break;
    case 3: (*(void(**)(char*, u32*))(vtbl + (0xb4 / 4)))(self, rect); break;
    case 4: (*(void(**)(char*, u32*))(vtbl + (0xb8 / 4)))(self, rect); break;
    default: break;
  }
  char* const a = *(char**)(self + 0x18);
  char* const b = *(char**)(self + 0x14);
  char* const desc = (*(char*(**)(char*, u32, u32))(*(u32**)a + (0x1c / 4)))(
      a, rect[0], rect[1]);
  char* const out = (*(char*(**)(char*, u32*, char*))(*(u32**)b + (0x2c / 4)))(
      b, rect, desc);
  u32* const dst = *(u32**)(self + 0x24);
  dst[0] = ((u32*)out)[0];
  dst[1] = ((u32*)out)[1];
  dst[2] = ((u32*)out)[2];
}

// ---------------------------------------------------------------------------
// Shared release helper for the baking render targets: return the rectangle to
// the RTT manager and drop the texture's reference count.
// ---------------------------------------------------------------------------
void cGraphicsSystem::ReleaseRTT(void*& texture, const TextureRectID& rect) {
  if (texture != 0) {
    mRTTManager->ReleaseRect(rect.mPageID, rect.mAllocID);
    void* const dead = texture;
    if (dead != 0) {
      texture = 0;
      volatile long* const rc = (volatile long*)((char*)dead + 8);
      _InterlockedExchange(rc, *rc - 1);
      if (*rc < 1) {
        _InterlockedExchange(rc, *rc + 1);
      }
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x007a5020  SP::cGraphicsSystem::RecycleBakingRTTs — release the six
// baking render targets and the rectangles they were allocated from.  `ret 8`:
// two stack arguments present but unused.
// ---------------------------------------------------------------------------
void cGraphicsSystem::RecycleBakingRTTs(u32 /*param_1*/, u32 /*param_2*/) {
  ReleaseRTT(mGIFExportTexture, mGIFExportRectID);
  ReleaseRTT(mShadowBlurTexture, mUnk100);
  ReleaseRTT(mAOTexture, mFinalBakedTextureRectID);
  ReleaseRTT(mFinalBakedTexture, mSmallFinalBakedTextureRectID);
  ReleaseRTT(mShadowTexture, mUnk108);
  (*(void(**)(void))(*(u32*)this + 0x34))();
}
