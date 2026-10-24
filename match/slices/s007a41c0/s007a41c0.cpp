// slice s007a41c0 — SP::cGraphicsSystem accessors (bake/effects RTT rect bookkeeping,
// debug-draw configuration) rewritten as real C++.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;

// ---------------------------------------------------------------------------
// External entry points still referenced by the not-yet-ported naked blocks.
// ---------------------------------------------------------------------------
extern "C" void EXT_67dd10();
extern "C" void EXT_67dd60();
extern "C" void EXT_67df60();
extern "C" void EXT_6a25a0();
extern "C" void EXT_6ad7c0();
extern "C" void EXT_6de350();
extern "C" void EXT_6ec4a0();
extern "C" void EXT_720200();
extern "C" void EXT_75fb90();
extern "C" void EXT_762a00();
extern "C" void EXT_762a30();
extern "C" void EXT_762b70();
extern "C" void EXT_762c60();
extern "C" void EXT_7a3ce0();
extern "C" void EXT_7a3df0();
extern "C" void EXT_7a4380();
extern "C" void EXT_7a44b0();
extern "C" void EXT_7a4600();
extern "C" void EXT_7a4650();
extern "C" void EXT_7a4710();
extern "C" void EXT_7a47c0();
extern "C" void EXT_7c3d30();
extern "C" void EXT_cc8b50();
extern "C" void EXT_f47380();
extern "C" void EXT_f473a0();
extern "C" void EXT_11f3620();
extern "C" void EXT_11f36a0();
extern "C" void EXT_11f4f20();
extern "C" void EXT_11f4fd0();
extern "C" void EXT_11f8af0();

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
  u32           mUnkE0[4];                        // +0xe0
  TextureRectID mFinalBakedTextureRectID;         // +0xf0
  TextureRectID mSmallFinalBakedTextureRectID;    // +0xf8
  u32           mUnk100[14];                      // +0x100
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
}// @ 0x007a41c0
__declspec(naked) void FUN_007a41c0() {
  __asm {
    _emit 06Ah
    _emit 0FFh
    _emit 068h
    _emit 08Ah
    _emit 03Dh
    _emit 021h
    _emit 001h
    _emit 064h
    _emit 0A1h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 050h
    _emit 064h
    _emit 089h
    _emit 025h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 051h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 068h
    _emit 028h
    _emit 0F6h
    _emit 040h
    _emit 001h
    _emit 06Ah
    _emit 044h
    call EXT_f473a0
    _emit 083h
    _emit 0C4h
    _emit 018h
    _emit 089h
    _emit 004h
    _emit 024h
    _emit 0C7h
    _emit 044h
    _emit 024h
    _emit 00Ch
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 007h
    _emit 08Bh
    _emit 0C8h
    call EXT_7a3df0
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 004h
    _emit 064h
    _emit 089h
    _emit 00Dh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 083h
    _emit 0C4h
    _emit 010h
    _emit 0C3h
  }
}

// @ 0x007a4220
__declspec(naked) void FUN_007a4220() {
  __asm {
    _emit 06Ah
    _emit 0FFh
    _emit 068h
    _emit 0C9h
    _emit 03Dh
    _emit 021h
    _emit 001h
    _emit 064h
    _emit 0A1h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 050h
    _emit 064h
    _emit 089h
    _emit 025h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 051h
    _emit 053h
    _emit 056h
    _emit 08Bh
    _emit 0F1h
    _emit 057h
    _emit 089h
    _emit 074h
    _emit 024h
    _emit 00Ch
    _emit 0C7h
    _emit 006h
    _emit 044h
    _emit 0F6h
    _emit 040h
    _emit 001h
    _emit 0C7h
    _emit 046h
    _emit 044h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 05Eh
    _emit 00Ch
    _emit 02Bh
    _emit 05Eh
    _emit 008h
    _emit 033h
    _emit 0FFh
    _emit 0C1h
    _emit 0FBh
    _emit 002h
    _emit 0C7h
    _emit 044h
    _emit 024h
    _emit 018h
    _emit 003h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 085h
    _emit 0DBh
    _emit 07Eh
    _emit 026h
    _emit 08Bh
    _emit 046h
    _emit 008h
    _emit 083h
    _emit 03Ch
    _emit 0B8h
    _emit 000h
    _emit 08Dh
    _emit 004h
    _emit 0B8h
    _emit 074h
    _emit 00Bh
    _emit 08Bh
    _emit 008h
    _emit 051h
    call EXT_762a00
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 08Bh
    _emit 056h
    _emit 008h
    _emit 0C7h
    _emit 004h
    _emit 0BAh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 047h
    _emit 03Bh
    _emit 0FBh
    _emit 07Ch
    _emit 0DAh
    _emit 08Bh
    _emit 05Eh
    _emit 020h
    _emit 02Bh
    _emit 05Eh
    _emit 01Ch
    _emit 033h
    _emit 0FFh
    _emit 0C1h
    _emit 0FBh
    _emit 002h
    _emit 085h
    _emit 0DBh
    _emit 07Eh
    _emit 02Eh
    _emit 0EBh
    _emit 006h
    _emit 08Dh
    _emit 09Bh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 046h
    _emit 01Ch
    _emit 083h
    _emit 03Ch
    _emit 0B8h
    _emit 000h
    _emit 08Dh
    _emit 004h
    _emit 0B8h
    _emit 074h
    _emit 00Bh
    _emit 08Bh
    _emit 008h
    _emit 051h
    call EXT_762a30
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 08Bh
    _emit 056h
    _emit 01Ch
    _emit 0C7h
    _emit 004h
    _emit 0BAh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 047h
    _emit 03Bh
    _emit 0FBh
    _emit 07Ch
    _emit 0DAh
    _emit 08Bh
    _emit 046h
    _emit 030h
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 00Fh
    _emit 083h
    _emit 078h
    _emit 0FCh
    _emit 000h
    _emit 074h
    _emit 009h
    _emit 050h
    call EXT_f47380
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 08Bh
    _emit 046h
    _emit 01Ch
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 00Fh
    _emit 083h
    _emit 078h
    _emit 0FCh
    _emit 000h
    _emit 074h
    _emit 009h
    _emit 050h
    call EXT_f47380
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 08Bh
    _emit 046h
    _emit 008h
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 00Fh
    _emit 083h
    _emit 078h
    _emit 0FCh
    _emit 000h
    _emit 074h
    _emit 009h
    _emit 050h
    call EXT_f47380
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 010h
    _emit 05Fh
    _emit 0C7h
    _emit 006h
    _emit 058h
    _emit 0C4h
    _emit 03Eh
    _emit 001h
    _emit 05Eh
    _emit 05Bh
    _emit 064h
    _emit 089h
    _emit 00Dh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 083h
    _emit 0C4h
    _emit 010h
    _emit 0C3h
  }
}

// @ 0x007a4320
__declspec(naked) void FUN_007a4320() {
  __asm {
    _emit 06Ah
    _emit 0FFh
    _emit 068h
    _emit 0E8h
    _emit 03Dh
    _emit 021h
    _emit 001h
    _emit 064h
    _emit 0A1h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 050h
    _emit 064h
    _emit 089h
    _emit 025h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 051h
    _emit 0A1h
    _emit 084h
    _emit 0DCh
    _emit 05Dh
    _emit 001h
    _emit 056h
    _emit 08Bh
    _emit 0F0h
    _emit 089h
    _emit 074h
    _emit 024h
    _emit 004h
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 020h
    _emit 0C7h
    _emit 044h
    _emit 024h
    _emit 010h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    call EXT_6de350
    _emit 056h
    _emit 0C7h
    _emit 005h
    _emit 084h
    _emit 0DCh
    _emit 05Dh
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    call EXT_f47380
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 008h
    _emit 05Eh
    _emit 064h
    _emit 089h
    _emit 00Dh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 083h
    _emit 0C4h
    _emit 010h
    _emit 0C3h
  }
}

// @ 0x007a4380
__declspec(naked) void FUN_007a4380() {
  __asm {
    _emit 06Ah
    _emit 0FFh
    _emit 068h
    _emit 0C9h
    _emit 03Dh
    _emit 021h
    _emit 001h
    _emit 064h
    _emit 0A1h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 050h
    _emit 064h
    _emit 089h
    _emit 025h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 051h
    _emit 056h
    _emit 08Bh
    _emit 0F1h
    _emit 033h
    _emit 0C0h
    _emit 089h
    _emit 074h
    _emit 024h
    _emit 004h
    _emit 089h
    _emit 046h
    _emit 004h
    _emit 0C7h
    _emit 006h
    _emit 044h
    _emit 0F6h
    _emit 040h
    _emit 001h
    _emit 089h
    _emit 044h
    _emit 024h
    _emit 010h
    _emit 089h
    _emit 046h
    _emit 008h
    _emit 089h
    _emit 046h
    _emit 00Ch
    _emit 089h
    _emit 046h
    _emit 010h
    _emit 089h
    _emit 046h
    _emit 01Ch
    _emit 089h
    _emit 046h
    _emit 020h
    _emit 089h
    _emit 046h
    _emit 024h
    _emit 089h
    _emit 046h
    _emit 030h
    _emit 089h
    _emit 046h
    _emit 034h
    _emit 089h
    _emit 046h
    _emit 038h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 01Ch
    _emit 089h
    _emit 046h
    _emit 044h
    _emit 08Bh
    _emit 044h
    _emit 024h
    _emit 018h
    _emit 051h
    _emit 08Bh
    _emit 0CEh
    _emit 0C6h
    _emit 044h
    _emit 024h
    _emit 014h
    _emit 003h
    _emit 089h
    _emit 046h
    _emit 048h
    call EXT_7a3ce0
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 008h
    _emit 08Bh
    _emit 0C6h
    _emit 05Eh
    _emit 064h
    _emit 089h
    _emit 00Dh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 083h
    _emit 0C4h
    _emit 010h
    _emit 0C2h
    _emit 008h
    _emit 000h
  }
}

// @ 0x007a4420
__declspec(naked) void FUN_007a4420() {
  __asm {
    _emit 064h
    _emit 0A1h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 06Ah
    _emit 0FFh
    _emit 068h
    _emit 01Ah
    _emit 03Eh
    _emit 021h
    _emit 001h
    _emit 050h
    _emit 064h
    _emit 089h
    _emit 025h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 044h
    _emit 024h
    _emit 01Ch
    _emit 056h
    _emit 08Bh
    _emit 0F1h
    _emit 033h
    _emit 0C9h
    _emit 085h
    _emit 0C0h
    _emit 06Ah
    _emit 000h
    _emit 00Fh
    _emit 09Eh
    _emit 0C1h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 068h
    _emit 028h
    _emit 0F6h
    _emit 040h
    _emit 001h
    _emit 06Ah
    _emit 04Ch
    _emit 049h
    _emit 023h
    _emit 0C8h
    _emit 089h
    _emit 04Eh
    _emit 004h
    call EXT_f473a0
    _emit 083h
    _emit 0C4h
    _emit 018h
    _emit 089h
    _emit 044h
    _emit 024h
    _emit 020h
    _emit 0C7h
    _emit 044h
    _emit 024h
    _emit 00Ch
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 013h
    _emit 08Bh
    _emit 054h
    _emit 024h
    _emit 01Ch
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 018h
    _emit 052h
    _emit 051h
    _emit 08Bh
    _emit 0C8h
    call EXT_7a4380
    _emit 0EBh
    _emit 002h
    _emit 033h
    _emit 0C0h
    _emit 089h
    _emit 006h
    _emit 08Bh
    _emit 010h
    _emit 08Bh
    _emit 0C8h
    _emit 08Bh
    _emit 042h
    _emit 004h
    _emit 0C7h
    _emit 044h
    _emit 024h
    _emit 00Ch
    _emit 0FFh
    _emit 0FFh
    _emit 0FFh
    _emit 0FFh
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 004h
    _emit 064h
    _emit 089h
    _emit 00Dh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 05Eh
    _emit 083h
    _emit 0C4h
    _emit 00Ch
    _emit 0C2h
    _emit 010h
    _emit 000h
  }
}

// @ 0x007a44b0
__declspec(naked) void FUN_007a44b0() {
  __asm {
    _emit 053h
    _emit 056h
    _emit 08Bh
    _emit 0F1h
    _emit 08Bh
    _emit 046h
    _emit 004h
    _emit 057h
    _emit 03Bh
    _emit 046h
    _emit 008h
    _emit 074h
    _emit 077h
    _emit 08Bh
    _emit 05Ch
    _emit 024h
    _emit 014h
    _emit 08Bh
    _emit 07Ch
    _emit 024h
    _emit 010h
    _emit 03Bh
    _emit 0DFh
    _emit 072h
    _emit 007h
    _emit 03Bh
    _emit 0D8h
    _emit 073h
    _emit 003h
    _emit 083h
    _emit 0C3h
    _emit 018h
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 023h
    _emit 08Bh
    _emit 048h
    _emit 0E8h
    _emit 089h
    _emit 008h
    _emit 08Bh
    _emit 050h
    _emit 0ECh
    _emit 089h
    _emit 050h
    _emit 004h
    _emit 08Bh
    _emit 048h
    _emit 0F0h
    _emit 089h
    _emit 048h
    _emit 008h
    _emit 08Bh
    _emit 050h
    _emit 0F4h
    _emit 089h
    _emit 050h
    _emit 00Ch
    _emit 08Bh
    _emit 048h
    _emit 0F8h
    _emit 089h
    _emit 048h
    _emit 010h
    _emit 08Bh
    _emit 050h
    _emit 0FCh
    _emit 089h
    _emit 050h
    _emit 014h
    _emit 08Bh
    _emit 046h
    _emit 004h
    _emit 050h
    _emit 083h
    _emit 0C0h
    _emit 0E8h
    _emit 050h
    _emit 057h
    call EXT_cc8b50
    _emit 08Bh
    _emit 003h
    _emit 089h
    _emit 007h
    _emit 08Bh
    _emit 04Bh
    _emit 004h
    _emit 089h
    _emit 04Fh
    _emit 004h
    _emit 08Bh
    _emit 053h
    _emit 008h
    _emit 089h
    _emit 057h
    _emit 008h
    _emit 08Bh
    _emit 043h
    _emit 00Ch
    _emit 089h
    _emit 047h
    _emit 00Ch
    _emit 08Bh
    _emit 04Bh
    _emit 010h
    _emit 089h
    _emit 04Fh
    _emit 010h
    _emit 08Bh
    _emit 053h
    _emit 014h
    _emit 083h
    _emit 0C4h
    _emit 00Ch
    _emit 089h
    _emit 057h
    _emit 014h
    _emit 083h
    _emit 046h
    _emit 004h
    _emit 018h
    _emit 05Fh
    _emit 05Eh
    _emit 05Bh
    _emit 0C2h
    _emit 008h
    _emit 000h
    _emit 02Bh
    _emit 006h
    _emit 055h
    _emit 08Bh
    _emit 0C8h
    _emit 0B8h
    _emit 0ABh
    _emit 0AAh
    _emit 0AAh
    _emit 02Ah
    _emit 0F7h
    _emit 0E9h
    _emit 0C1h
    _emit 0FAh
    _emit 002h
    _emit 08Bh
    _emit 0C2h
    _emit 0C1h
    _emit 0E8h
    _emit 01Fh
    _emit 003h
    _emit 0C2h
    _emit 074h
    _emit 031h
    _emit 08Dh
    _emit 02Ch
    _emit 000h
    _emit 085h
    _emit 0EDh
    _emit 074h
    _emit 031h
    _emit 068h
    _emit 0D1h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 068h
    _emit 038h
    _emit 0BBh
    _emit 03Eh
    _emit 001h
    _emit 06Ah
    _emit 000h
    _emit 08Dh
    _emit 044h
    _emit 06Dh
    _emit 000h
    _emit 003h
    _emit 0C0h
    _emit 06Ah
    _emit 000h
    _emit 003h
    _emit 0C0h
    _emit 003h
    _emit 0C0h
    _emit 068h
    _emit 0A4h
    _emit 0B8h
    _emit 03Eh
    _emit 001h
    _emit 050h
    call EXT_f473a0
    _emit 083h
    _emit 0C4h
    _emit 018h
    _emit 08Bh
    _emit 0F8h
    _emit 0EBh
    _emit 009h
    _emit 0BDh
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0EBh
    _emit 0CFh
    _emit 033h
    _emit 0FFh
    _emit 08Bh
    _emit 05Ch
    _emit 024h
    _emit 014h
    _emit 08Bh
    _emit 006h
    _emit 057h
    _emit 053h
    _emit 050h
    call EXT_720200
    _emit 083h
    _emit 0C4h
    _emit 00Ch
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 026h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 018h
    _emit 08Bh
    _emit 011h
    _emit 089h
    _emit 010h
    _emit 08Bh
    _emit 051h
    _emit 004h
    _emit 089h
    _emit 050h
    _emit 004h
    _emit 08Bh
    _emit 051h
    _emit 008h
    _emit 089h
    _emit 050h
    _emit 008h
    _emit 08Bh
    _emit 051h
    _emit 00Ch
    _emit 089h
    _emit 050h
    _emit 00Ch
    _emit 08Bh
    _emit 051h
    _emit 010h
    _emit 089h
    _emit 050h
    _emit 010h
    _emit 08Bh
    _emit 049h
    _emit 014h
    _emit 089h
    _emit 048h
    _emit 014h
    _emit 08Bh
    _emit 04Eh
    _emit 004h
    _emit 083h
    _emit 0C0h
    _emit 018h
    _emit 050h
    _emit 051h
    _emit 053h
    call EXT_720200
    _emit 08Bh
    _emit 0D8h
    _emit 08Bh
    _emit 006h
    _emit 083h
    _emit 0C4h
    _emit 00Ch
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 00Fh
    _emit 083h
    _emit 078h
    _emit 0FCh
    _emit 000h
    _emit 074h
    _emit 009h
    _emit 050h
    call EXT_f47380
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 08Dh
    _emit 054h
    _emit 06Dh
    _emit 000h
    _emit 05Dh
    _emit 089h
    _emit 03Eh
    _emit 08Dh
    _emit 004h
    _emit 0D7h
    _emit 05Fh
    _emit 089h
    _emit 05Eh
    _emit 004h
    _emit 089h
    _emit 046h
    _emit 008h
    _emit 05Eh
    _emit 05Bh
    _emit 0C2h
    _emit 008h
    _emit 000h
  }
}

// @ 0x007a4600
__declspec(naked) void FUN_007a4600() {
  __asm {
    _emit 08Bh
    _emit 041h
    _emit 004h
    _emit 03Bh
    _emit 041h
    _emit 008h
    _emit 073h
    _emit 033h
    _emit 08Dh
    _emit 050h
    _emit 018h
    _emit 089h
    _emit 051h
    _emit 004h
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 034h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 004h
    _emit 08Bh
    _emit 011h
    _emit 089h
    _emit 010h
    _emit 08Bh
    _emit 051h
    _emit 004h
    _emit 089h
    _emit 050h
    _emit 004h
    _emit 08Bh
    _emit 051h
    _emit 008h
    _emit 089h
    _emit 050h
    _emit 008h
    _emit 08Bh
    _emit 051h
    _emit 00Ch
    _emit 089h
    _emit 050h
    _emit 00Ch
    _emit 08Bh
    _emit 051h
    _emit 010h
    _emit 089h
    _emit 050h
    _emit 010h
    _emit 08Bh
    _emit 049h
    _emit 014h
    _emit 089h
    _emit 048h
    _emit 014h
    _emit 0C2h
    _emit 004h
    _emit 000h
    _emit 08Bh
    _emit 054h
    _emit 024h
    _emit 004h
    _emit 052h
    _emit 050h
    call EXT_7a44b0
    _emit 0C2h
    _emit 004h
    _emit 000h
  }
}

// @ 0x007a4650
__declspec(naked) void FUN_007a4650() {
  __asm {
    _emit 083h
    _emit 0ECh
    _emit 018h
    _emit 0A1h
    _emit 084h
    _emit 0DCh
    _emit 05Dh
    _emit 001h
    _emit 08Bh
    _emit 051h
    _emit 00Ch
    _emit 02Bh
    _emit 051h
    _emit 008h
    _emit 053h
    _emit 055h
    _emit 056h
    _emit 08Bh
    _emit 070h
    _emit 014h
    _emit 057h
    _emit 08Bh
    _emit 078h
    _emit 010h
    _emit 0C1h
    _emit 0FAh
    _emit 002h
    _emit 02Bh
    _emit 0FEh
    _emit 033h
    _emit 0DBh
    _emit 089h
    _emit 054h
    _emit 024h
    _emit 010h
    _emit 089h
    _emit 074h
    _emit 024h
    _emit 014h
    _emit 089h
    _emit 07Ch
    _emit 024h
    _emit 018h
    _emit 038h
    _emit 058h
    _emit 040h
    _emit 074h
    _emit 019h
    _emit 08Bh
    _emit 071h
    _emit 020h
    _emit 02Bh
    _emit 071h
    _emit 01Ch
    _emit 08Bh
    _emit 058h
    _emit 030h
    _emit 08Bh
    _emit 068h
    _emit 02Ch
    _emit 0C1h
    _emit 0FEh
    _emit 002h
    _emit 089h
    _emit 05Ch
    _emit 024h
    _emit 020h
    _emit 02Bh
    _emit 0EBh
    _emit 033h
    _emit 0DBh
    _emit 0EBh
    _emit 009h
    _emit 083h
    _emit 0CEh
    _emit 0FFh
    _emit 089h
    _emit 05Ch
    _emit 024h
    _emit 020h
    _emit 033h
    _emit 0EDh
    _emit 088h
    _emit 058h
    _emit 020h
    _emit 088h
    _emit 058h
    _emit 040h
    _emit 08Bh
    _emit 058h
    _emit 010h
    _emit 089h
    _emit 058h
    _emit 014h
    _emit 08Bh
    _emit 058h
    _emit 02Ch
    _emit 089h
    _emit 06Ch
    _emit 024h
    _emit 024h
    _emit 089h
    _emit 074h
    _emit 024h
    _emit 01Ch
    _emit 089h
    _emit 058h
    _emit 030h
    _emit 085h
    _emit 0FFh
    _emit 074h
    _emit 03Eh
    _emit 085h
    _emit 0F6h
    _emit 07Ch
    _emit 004h
    _emit 085h
    _emit 0EDh
    _emit 074h
    _emit 036h
    _emit 08Bh
    _emit 059h
    _emit 030h
    _emit 03Bh
    _emit 059h
    _emit 034h
    _emit 08Dh
    _emit 041h
    _emit 030h
    _emit 074h
    _emit 01Fh
    _emit 083h
    _emit 0FEh
    _emit 0FFh
    _emit 075h
    _emit 01Ah
    _emit 08Bh
    _emit 049h
    _emit 034h
    _emit 083h
    _emit 0E9h
    _emit 018h
    _emit 039h
    _emit 011h
    _emit 075h
    _emit 010h
    _emit 039h
    _emit 071h
    _emit 00Ch
    _emit 075h
    _emit 00Bh
    _emit 001h
    _emit 079h
    _emit 008h
    _emit 05Fh
    _emit 05Eh
    _emit 05Dh
    _emit 05Bh
    _emit 083h
    _emit 0C4h
    _emit 018h
    _emit 0C3h
    _emit 08Dh
    _emit 04Ch
    _emit 024h
    _emit 010h
    _emit 051h
    _emit 08Bh
    _emit 0C8h
    call EXT_7a4600
    _emit 05Fh
    _emit 05Eh
    _emit 05Dh
    _emit 05Bh
    _emit 083h
    _emit 0C4h
    _emit 018h
    _emit 0C3h
  }
}

// @ 0x007a4710
__declspec(naked) void FUN_007a4710() {
  __asm {
    _emit 053h
    _emit 055h
    _emit 056h
    _emit 08Bh
    _emit 035h
    _emit 084h
    _emit 0DCh
    _emit 05Dh
    _emit 001h
    _emit 033h
    _emit 0DBh
    _emit 057h
    _emit 08Bh
    _emit 0E9h
    _emit 038h
    _emit 05Eh
    _emit 020h
    _emit 075h
    _emit 005h
    _emit 038h
    _emit 05Eh
    _emit 040h
    _emit 074h
    _emit 005h
    call EXT_7a4650
    _emit 08Bh
    _emit 04Eh
    _emit 00Ch
    _emit 08Dh
    _emit 07Eh
    _emit 00Ch
    _emit 03Bh
    _emit 0CBh
    _emit 074h
    _emit 032h
    call EXT_11f36a0
    _emit 08Bh
    _emit 045h
    _emit 00Ch
    _emit 03Bh
    _emit 045h
    _emit 010h
    _emit 08Dh
    _emit 04Dh
    _emit 008h
    _emit 073h
    _emit 010h
    _emit 08Dh
    _emit 050h
    _emit 004h
    _emit 089h
    _emit 051h
    _emit 004h
    _emit 03Bh
    _emit 0C3h
    _emit 074h
    _emit 00Dh
    _emit 08Bh
    _emit 00Fh
    _emit 089h
    _emit 008h
    _emit 0EBh
    _emit 007h
    _emit 057h
    _emit 050h
    call EXT_6ec4a0
    _emit 089h
    _emit 01Fh
    _emit 089h
    _emit 05Eh
    _emit 014h
    _emit 089h
    _emit 05Eh
    _emit 010h
    _emit 089h
    _emit 05Eh
    _emit 008h
    _emit 08Bh
    _emit 04Eh
    _emit 028h
    _emit 08Dh
    _emit 07Eh
    _emit 028h
    _emit 03Bh
    _emit 0CBh
    _emit 074h
    _emit 044h
    _emit 08Dh
    _emit 046h
    _emit 034h
    _emit 050h
    call EXT_11f4fd0
    _emit 08Bh
    _emit 045h
    _emit 020h
    _emit 03Bh
    _emit 045h
    _emit 024h
    _emit 08Dh
    _emit 04Dh
    _emit 01Ch
    _emit 073h
    _emit 01Eh
    _emit 08Dh
    _emit 050h
    _emit 004h
    _emit 089h
    _emit 051h
    _emit 004h
    _emit 03Bh
    _emit 0C3h
    _emit 074h
    _emit 01Bh
    _emit 08Bh
    _emit 00Fh
    _emit 089h
    _emit 008h
    _emit 089h
    _emit 01Fh
    _emit 05Fh
    _emit 089h
    _emit 05Eh
    _emit 030h
    _emit 089h
    _emit 05Eh
    _emit 02Ch
    _emit 089h
    _emit 05Eh
    _emit 024h
    _emit 05Eh
    _emit 05Dh
    _emit 05Bh
    _emit 0C3h
    _emit 057h
    _emit 050h
    call EXT_6ec4a0
    _emit 089h
    _emit 01Fh
    _emit 089h
    _emit 05Eh
    _emit 030h
    _emit 089h
    _emit 05Eh
    _emit 02Ch
    _emit 089h
    _emit 05Eh
    _emit 024h
    _emit 05Fh
    _emit 05Eh
    _emit 05Dh
    _emit 05Bh
    _emit 0C3h
  }
}

// @ 0x007a47c0
__declspec(naked) void FUN_007a47c0() {
  __asm {
    _emit 053h
    _emit 055h
    _emit 056h
    _emit 08Bh
    _emit 035h
    _emit 084h
    _emit 0DCh
    _emit 05Dh
    _emit 001h
    _emit 08Bh
    _emit 046h
    _emit 010h
    _emit 08Bh
    _emit 05Eh
    _emit 004h
    _emit 057h
    _emit 08Bh
    _emit 07Ch
    _emit 024h
    _emit 014h
    _emit 08Bh
    _emit 0E9h
    _emit 08Bh
    _emit 04Eh
    _emit 008h
    _emit 08Dh
    _emit 014h
    _emit 038h
    _emit 03Bh
    _emit 0D1h
    _emit 07Eh
    _emit 016h
    _emit 085h
    _emit 0DBh
    _emit 07Eh
    _emit 00Bh
    _emit 02Bh
    _emit 0C8h
    _emit 083h
    _emit 0F9h
    _emit 030h
    _emit 07Eh
    _emit 004h
    _emit 08Bh
    _emit 0F9h
    _emit 0EBh
    _emit 007h
    _emit 08Bh
    _emit 0CDh
    call EXT_7a4710
    _emit 083h
    _emit 07Eh
    _emit 00Ch
    _emit 000h
    _emit 075h
    _emit 078h
    _emit 083h
    _emit 07Dh
    _emit 048h
    _emit 003h
    _emit 075h
    _emit 00Dh
    _emit 081h
    _emit 0FFh
    _emit 0F8h
    _emit 01Fh
    _emit 000h
    _emit 000h
    _emit 07Eh
    _emit 005h
    _emit 0BFh
    _emit 0F8h
    _emit 01Fh
    _emit 000h
    _emit 000h
    _emit 03Bh
    _emit 0DFh
    _emit 08Bh
    _emit 0C3h
    _emit 07Fh
    _emit 002h
    _emit 08Bh
    _emit 0C7h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 050h
    _emit 089h
    _emit 046h
    _emit 008h
    _emit 08Bh
    _emit 045h
    _emit 044h
    _emit 050h
    call EXT_762b70
    _emit 08Bh
    _emit 04Eh
    _emit 008h
    _emit 083h
    _emit 0C4h
    _emit 010h
    _emit 089h
    _emit 046h
    _emit 00Ch
    _emit 085h
    _emit 0C9h
    _emit 075h
    _emit 003h
    _emit 08Bh
    _emit 048h
    _emit 00Ch
    _emit 08Bh
    _emit 010h
    _emit 08Ah
    _emit 052h
    _emit 00Fh
    _emit 00Fh
    _emit 0B6h
    _emit 0DAh
    _emit 00Fh
    _emit 0AFh
    _emit 0D9h
    _emit 00Fh
    _emit 0B6h
    _emit 0CAh
    _emit 00Fh
    _emit 0AFh
    _emit 048h
    _emit 008h
    _emit 053h
    _emit 051h
    _emit 06Ah
    _emit 002h
    _emit 08Bh
    _emit 0C8h
    call EXT_11f3620
    _emit 033h
    _emit 0C9h
    _emit 03Bh
    _emit 0C1h
    _emit 074h
    _emit 017h
    _emit 08Bh
    _emit 056h
    _emit 00Ch
    _emit 089h
    _emit 04Eh
    _emit 010h
    _emit 089h
    _emit 04Eh
    _emit 014h
    _emit 08Bh
    _emit 00Ah
    _emit 00Fh
    _emit 0B6h
    _emit 051h
    _emit 00Fh
    _emit 089h
    _emit 056h
    _emit 018h
    _emit 089h
    _emit 046h
    _emit 01Ch
    _emit 0EBh
    _emit 002h
    _emit 033h
    _emit 0FFh
    _emit 08Bh
    _emit 045h
    _emit 048h
    _emit 048h
    _emit 083h
    _emit 0F8h
    _emit 003h
    _emit 077h
    _emit 050h
    _emit 0FFh
    _emit 024h
    _emit 085h
    _emit 0F8h
    _emit 048h
    _emit 07Ah
    _emit 000h
    _emit 08Bh
    _emit 0C7h
    _emit 025h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 080h
    _emit 079h
    _emit 005h
    _emit 048h
    _emit 083h
    _emit 0C8h
    _emit 0FEh
    _emit 040h
    _emit 02Bh
    _emit 0F8h
    _emit 0EBh
    _emit 037h
    _emit 0B8h
    _emit 056h
    _emit 055h
    _emit 055h
    _emit 055h
    _emit 0F7h
    _emit 0EFh
    _emit 08Bh
    _emit 0C2h
    _emit 0C1h
    _emit 0E8h
    _emit 01Fh
    _emit 003h
    _emit 0C2h
    _emit 08Dh
    _emit 03Ch
    _emit 040h
    _emit 0EBh
    _emit 024h
    _emit 08Bh
    _emit 0CFh
    _emit 081h
    _emit 0E1h
    _emit 003h
    _emit 000h
    _emit 000h
    _emit 080h
    _emit 079h
    _emit 005h
    _emit 049h
    _emit 083h
    _emit 0C9h
    _emit 0FCh
    _emit 041h
    _emit 02Bh
    _emit 0F9h
    _emit 0EBh
    _emit 011h
    _emit 08Bh
    _emit 0D7h
    _emit 081h
    _emit 0E2h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 080h
    _emit 079h
    _emit 005h
    _emit 04Ah
    _emit 083h
    _emit 0CAh
    _emit 0FEh
    _emit 042h
    _emit 02Bh
    _emit 0FAh
    _emit 08Bh
    _emit 046h
    _emit 018h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 01Ch
    _emit 089h
    _emit 001h
    _emit 08Bh
    _emit 056h
    _emit 010h
    _emit 00Fh
    _emit 0AFh
    _emit 056h
    _emit 018h
    _emit 003h
    _emit 056h
    _emit 01Ch
    _emit 08Bh
    _emit 044h
    _emit 024h
    _emit 018h
    _emit 089h
    _emit 010h
    _emit 001h
    _emit 07Eh
    _emit 010h
    _emit 08Bh
    _emit 0C7h
    _emit 05Fh
    _emit 0C6h
    _emit 046h
    _emit 020h
    _emit 001h
    _emit 05Eh
    _emit 05Dh
    _emit 05Bh
    _emit 0C2h
    _emit 00Ch
    _emit 000h
    _emit 08Bh
    _emit 0FFh
    _emit 084h
    _emit 048h
    _emit 07Ah
    _emit 000h
    _emit 096h
    _emit 048h
    _emit 07Ah
    _emit 000h
    _emit 0A9h
    _emit 048h
    _emit 07Ah
    _emit 000h
    _emit 0BCh
    _emit 048h
    _emit 07Ah
    _emit 000h
    _emit 0CCh
    _emit 0CCh
    _emit 0CCh
    _emit 0CCh
    _emit 0CCh
    _emit 0CCh
    _emit 0CCh
    _emit 0CCh
    _emit 051h
    _emit 053h
    _emit 055h
    _emit 08Bh
    _emit 06Ch
    _emit 024h
    _emit 010h
    _emit 081h
    _emit 0FDh
    _emit 0FFh
    _emit 07Fh
    _emit 000h
    _emit 000h
    _emit 056h
    _emit 08Bh
    _emit 035h
    _emit 084h
    _emit 0DCh
    _emit 05Dh
    _emit 001h
    _emit 057h
    _emit 089h
    _emit 04Ch
    _emit 024h
    _emit 010h
    _emit 08Dh
    _emit 05Eh
    _emit 034h
    _emit 00Fh
    _emit 08Fh
    _emit 09Eh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 07Ch
    _emit 024h
    _emit 024h
    _emit 081h
    _emit 0FFh
    _emit 000h
    _emit 000h
    _emit 001h
    _emit 000h
    _emit 00Fh
    _emit 08Fh
    _emit 08Eh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 046h
    _emit 010h
    _emit 003h
    _emit 0C5h
    _emit 03Bh
    _emit 046h
    _emit 008h
    _emit 07Fh
    _emit 00Ah
    _emit 08Bh
    _emit 056h
    _emit 02Ch
    _emit 003h
    _emit 0D7h
    _emit 03Bh
    _emit 056h
    _emit 024h
    _emit 07Eh
    _emit 009h
    call EXT_7a4710
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 010h
    _emit 08Bh
    _emit 044h
    _emit 024h
    _emit 020h
    _emit 08Bh
    _emit 054h
    _emit 024h
    _emit 01Ch
    _emit 050h
    _emit 052h
    _emit 055h
    call EXT_7a47c0
    _emit 033h
    _emit 0EDh
    _emit 039h
    _emit 06Eh
    _emit 028h
    _emit 075h
    _emit 03Ch
    _emit 0B8h
    _emit 056h
    _emit 055h
    _emit 055h
    _emit 055h
    _emit 0F7h
    _emit 0EFh
    _emit 055h
    _emit 06Ah
    _emit 004h
    _emit 08Bh
    _emit 0C2h
    _emit 06Ah
    _emit 008h
    _emit 0C1h
    _emit 0E8h
    _emit 01Fh
    _emit 057h
    _emit 003h
    _emit 0C2h
    _emit 050h
    _emit 068h
    _emit 0B0h
    _emit 007h
    _emit 05Dh
    _emit 001h
    _emit 089h
    _emit 07Eh
    _emit 024h
    call EXT_762c60
    _emit 083h
    _emit 0C4h
    _emit 018h
    _emit 053h
    _emit 06Ah
    _emit 006h
    _emit 08Bh
    _emit 0C8h
    _emit 089h
    _emit 046h
    _emit 028h
    _emit 089h
    _emit 06Eh
    _emit 02Ch
    _emit 089h
    _emit 06Eh
    _emit 030h
    call EXT_11f4f20
    _emit 085h
    _emit 0C0h
    _emit 074h
    _emit 01Eh
    _emit 08Bh
    _emit 04Eh
    _emit 02Ch
    _emit 08Bh
    _emit 013h
    _emit 08Dh
    _emit 004h
    _emit 04Ah
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 028h
    _emit 089h
    _emit 001h
    _emit 001h
    _emit 07Eh
    _emit 02Ch
    _emit 05Fh
    _emit 0B0h
    _emit 001h
    _emit 088h
    _emit 046h
    _emit 040h
    _emit 05Eh
    _emit 05Dh
    _emit 05Bh
    _emit 059h
    _emit 0C2h
    _emit 014h
    _emit 000h
    _emit 05Fh
    _emit 05Eh
    _emit 05Dh
    _emit 032h
    _emit 0C0h
    _emit 05Bh
    _emit 059h
    _emit 0C2h
    _emit 014h
    _emit 000h
  }
}

// @ 0x007a49e0
__declspec(naked) void FUN_007a49e0() {
  __asm {
    _emit 056h
    _emit 057h
    call EXT_11f8af0
    _emit 08Bh
    _emit 074h
    _emit 024h
    _emit 00Ch
    _emit 08Bh
    _emit 015h
    _emit 058h
    _emit 024h
    _emit 071h
    _emit 001h
    _emit 08Bh
    _emit 000h
    _emit 08Bh
    _emit 00Dh
    _emit 0C8h
    _emit 089h
    _emit 06Fh
    _emit 001h
    _emit 08Bh
    _emit 039h
    _emit 056h
    _emit 06Ah
    _emit 003h
    _emit 06Ah
    _emit 001h
    _emit 052h
    _emit 050h
    call EXT_11f8af0
    _emit 08Bh
    _emit 048h
    _emit 004h
    _emit 08Bh
    _emit 015h
    _emit 0C8h
    _emit 089h
    _emit 06Fh
    _emit 001h
    _emit 08Bh
    _emit 047h
    _emit 028h
    _emit 051h
    _emit 052h
    _emit 0FFh
    _emit 0D0h
    _emit 085h
    _emit 0C0h
    _emit 07Ch
    _emit 03Dh
    call EXT_11f8af0
    _emit 08Bh
    _emit 015h
    _emit 0C4h
    _emit 08Bh
    _emit 06Fh
    _emit 001h
    _emit 08Bh
    _emit 00Dh
    _emit 0C8h
    _emit 089h
    _emit 06Fh
    _emit 001h
    _emit 08Bh
    _emit 039h
    _emit 08Bh
    _emit 00Dh
    _emit 058h
    _emit 024h
    _emit 071h
    _emit 001h
    _emit 052h
    _emit 08Bh
    _emit 010h
    _emit 056h
    _emit 051h
    _emit 052h
    call EXT_11f8af0
    _emit 08Bh
    _emit 040h
    _emit 004h
    _emit 08Bh
    _emit 00Dh
    _emit 0C8h
    _emit 089h
    _emit 06Fh
    _emit 001h
    _emit 08Bh
    _emit 057h
    _emit 030h
    _emit 050h
    _emit 051h
    _emit 0FFh
    _emit 0D2h
    _emit 085h
    _emit 0C0h
    _emit 07Ch
    _emit 005h
    _emit 05Fh
    _emit 0B0h
    _emit 001h
    _emit 05Eh
    _emit 0C3h
    _emit 05Fh
    _emit 032h
    _emit 0C0h
    _emit 05Eh
    _emit 0C3h
  }
}

// @ 0x007a4cb0
__declspec(naked) void FUN_007a4cb0() {
  __asm {
    _emit 053h
    _emit 056h
    _emit 057h
    _emit 08Bh
    _emit 0F1h
    call EXT_75fb90
    _emit 08Bh
    _emit 05Eh
    _emit 010h
    _emit 08Bh
    _emit 0F8h
    _emit 03Bh
    _emit 0FBh
    _emit 074h
    _emit 01Ch
    _emit 085h
    _emit 0FFh
    _emit 074h
    _emit 008h
    _emit 08Bh
    _emit 007h
    _emit 08Bh
    _emit 010h
    _emit 08Bh
    _emit 0CFh
    _emit 0FFh
    _emit 0D2h
    _emit 089h
    _emit 07Eh
    _emit 010h
    _emit 085h
    _emit 0DBh
    _emit 074h
    _emit 009h
    _emit 08Bh
    _emit 003h
    _emit 08Bh
    _emit 050h
    _emit 004h
    _emit 08Bh
    _emit 0CBh
    _emit 0FFh
    _emit 0D2h
    _emit 08Bh
    _emit 04Eh
    _emit 010h
    _emit 08Bh
    _emit 001h
    _emit 08Bh
    _emit 050h
    _emit 00Ch
    _emit 0FFh
    _emit 0D2h
    _emit 084h
    _emit 0C0h
    _emit 074h
    _emit 012h
    _emit 08Bh
    _emit 046h
    _emit 010h
    _emit 050h
    call EXT_67df60
    _emit 083h
    _emit 0C4h
    _emit 004h
    _emit 05Fh
    _emit 05Eh
    _emit 0B0h
    _emit 001h
    _emit 05Bh
    _emit 0C3h
    _emit 08Bh
    _emit 04Eh
    _emit 010h
    _emit 085h
    _emit 0C9h
    _emit 074h
    _emit 00Eh
    _emit 0C7h
    _emit 046h
    _emit 010h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 011h
    _emit 08Bh
    _emit 042h
    _emit 004h
    _emit 0FFh
    _emit 0D0h
    _emit 05Fh
    _emit 05Eh
    _emit 032h
    _emit 0C0h
    _emit 05Bh
    _emit 0C3h
  }
}

// @ 0x007a4d90
__declspec(naked) void FUN_007a4d90() {
  __asm {
    _emit 051h
    _emit 0A1h
    _emit 018h
    _emit 0D9h
    _emit 05Fh
    _emit 001h
    _emit 056h
    _emit 08Bh
    _emit 0F1h
    _emit 08Bh
    _emit 048h
    _emit 03Ch
    _emit 083h
    _emit 0B9h
    _emit 030h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 00Fh
    _emit 095h
    _emit 0C0h
    _emit 038h
    _emit 086h
    _emit 090h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 074h
    _emit 025h
    _emit 06Ah
    _emit 004h
    _emit 088h
    _emit 086h
    _emit 090h
    _emit 001h
    _emit 000h
    _emit 000h
    call EXT_6ad7c0
    _emit 06Ah
    _emit 005h
    call EXT_6ad7c0
    _emit 06Ah
    _emit 009h
    call EXT_6ad7c0
    _emit 06Ah
    _emit 00Ah
    call EXT_6ad7c0
    _emit 083h
    _emit 0C4h
    _emit 010h
    _emit 08Bh
    _emit 04Eh
    _emit 024h
    _emit 085h
    _emit 0C9h
    _emit 074h
    _emit 022h
    _emit 0F3h
    _emit 00Fh
    _emit 010h
    _emit 044h
    _emit 024h
    _emit 010h
    _emit 0F3h
    _emit 00Fh
    _emit 059h
    _emit 005h
    _emit 0B4h
    _emit 0C5h
    _emit 03Eh
    _emit 001h
    _emit 0F3h
    _emit 00Fh
    _emit 011h
    _emit 044h
    _emit 024h
    _emit 004h
    _emit 0F3h
    _emit 00Fh
    _emit 02Dh
    _emit 044h
    _emit 024h
    _emit 004h
    _emit 08Bh
    _emit 011h
    _emit 050h
    _emit 08Bh
    _emit 042h
    _emit 014h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 04Eh
    _emit 014h
    _emit 085h
    _emit 0C9h
    _emit 074h
    _emit 007h
    _emit 08Bh
    _emit 011h
    _emit 08Bh
    _emit 042h
    _emit 014h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 04Eh
    _emit 020h
    _emit 085h
    _emit 0C9h
    _emit 074h
    _emit 007h
    _emit 08Bh
    _emit 011h
    _emit 08Bh
    _emit 042h
    _emit 014h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 04Eh
    _emit 028h
    _emit 05Eh
    _emit 085h
    _emit 0C9h
    _emit 074h
    _emit 019h
    _emit 0D9h
    _emit 044h
    _emit 024h
    _emit 00Ch
    _emit 08Bh
    _emit 011h
    _emit 08Bh
    _emit 042h
    _emit 038h
    _emit 083h
    _emit 0ECh
    _emit 008h
    _emit 0D9h
    _emit 05Ch
    _emit 024h
    _emit 004h
    _emit 0D9h
    _emit 044h
    _emit 024h
    _emit 010h
    _emit 0D9h
    _emit 01Ch
    _emit 024h
    _emit 0FFh
    _emit 0D0h
    _emit 059h
    _emit 0C2h
    _emit 008h
    _emit 000h
  }
}

// @ 0x007a4e40
__declspec(naked) void FUN_007a4e40() {
  __asm {
    _emit 083h
    _emit 0ECh
    _emit 024h
    _emit 056h
    _emit 08Bh
    _emit 0F1h
    call EXT_67dd10
    _emit 08Bh
    _emit 010h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 06Ah
    _emit 000h
    _emit 08Dh
    _emit 04Ch
    _emit 024h
    _emit 018h
    _emit 051h
    _emit 08Bh
    _emit 0C8h
    _emit 08Bh
    _emit 042h
    _emit 058h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 0C8h
    call EXT_7c3d30
    _emit 0D9h
    _emit 086h
    _emit 084h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 0D9h
    _emit 044h
    _emit 024h
    _emit 014h
    _emit 00Fh
    _emit 057h
    _emit 0C0h
    _emit 0DCh
    _emit 0C8h
    _emit 0F3h
    _emit 00Fh
    _emit 011h
    _emit 044h
    _emit 024h
    _emit 008h
    _emit 0D9h
    _emit 044h
    _emit 024h
    _emit 010h
    _emit 0F3h
    _emit 00Fh
    _emit 010h
    _emit 005h
    _emit 020h
    _emit 057h
    _emit 048h
    _emit 001h
    _emit 0DCh
    _emit 0C8h
    _emit 0F3h
    _emit 00Fh
    _emit 011h
    _emit 044h
    _emit 024h
    _emit 004h
    _emit 0DEh
    _emit 0C1h
    _emit 0D9h
    _emit 044h
    _emit 024h
    _emit 00Ch
    _emit 0DCh
    _emit 0C8h
    _emit 0DEh
    _emit 0C1h
    _emit 0D9h
    _emit 0FAh
    _emit 0D8h
    _emit 0E1h
    _emit 0D9h
    _emit 086h
    _emit 080h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 0DEh
    _emit 0E2h
    _emit 0DEh
    _emit 0F1h
    _emit 0D9h
    _emit 05Ch
    _emit 024h
    _emit 018h
    _emit 0F3h
    _emit 00Fh
    _emit 010h
    _emit 044h
    _emit 024h
    _emit 018h
    _emit 0F3h
    _emit 00Fh
    _emit 05Fh
    _emit 044h
    _emit 024h
    _emit 008h
    _emit 0F3h
    _emit 00Fh
    _emit 05Dh
    _emit 044h
    _emit 024h
    _emit 004h
    _emit 0F3h
    _emit 00Fh
    _emit 011h
    _emit 044h
    _emit 024h
    _emit 018h
    _emit 0F3h
    _emit 00Fh
    _emit 010h
    _emit 086h
    _emit 07Ch
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 0F3h
    _emit 00Fh
    _emit 010h
    _emit 08Eh
    _emit 078h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 0F3h
    _emit 00Fh
    _emit 05Ch
    _emit 0C8h
    _emit 0F3h
    _emit 00Fh
    _emit 059h
    _emit 04Ch
    _emit 024h
    _emit 018h
    _emit 0F3h
    _emit 00Fh
    _emit 058h
    _emit 0C8h
    _emit 0F3h
    _emit 00Fh
    _emit 011h
    _emit 08Eh
    _emit 074h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 05Eh
    _emit 083h
    _emit 0C4h
    _emit 024h
    _emit 0C3h
  }
}

// @ 0x007a4f50
__declspec(naked) void FUN_007a4f50() {
  __asm {
    _emit 083h
    _emit 0ECh
    _emit 014h
    _emit 083h
    _emit 0C8h
    _emit 0FFh
    _emit 089h
    _emit 004h
    _emit 024h
    _emit 089h
    _emit 044h
    _emit 024h
    _emit 004h
    _emit 08Bh
    _emit 044h
    _emit 024h
    _emit 018h
    _emit 056h
    _emit 057h
    _emit 08Bh
    _emit 0F1h
    _emit 085h
    _emit 0C0h
    _emit 075h
    _emit 00Ah
    _emit 08Bh
    _emit 006h
    _emit 08Bh
    _emit 090h
    _emit 0B0h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0EBh
    _emit 03Ah
    _emit 083h
    _emit 0F8h
    _emit 001h
    _emit 075h
    _emit 00Ah
    _emit 08Bh
    _emit 006h
    _emit 08Bh
    _emit 090h
    _emit 0ACh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0EBh
    _emit 02Bh
    _emit 083h
    _emit 0F8h
    _emit 002h
    _emit 075h
    _emit 00Ah
    _emit 08Bh
    _emit 006h
    _emit 08Bh
    _emit 090h
    _emit 0BCh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0EBh
    _emit 01Ch
    _emit 083h
    _emit 0F8h
    _emit 004h
    _emit 075h
    _emit 00Ah
    _emit 08Bh
    _emit 006h
    _emit 08Bh
    _emit 090h
    _emit 0B8h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0EBh
    _emit 00Dh
    _emit 083h
    _emit 0F8h
    _emit 003h
    _emit 075h
    _emit 011h
    _emit 08Bh
    _emit 006h
    _emit 08Bh
    _emit 090h
    _emit 0B4h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Dh
    _emit 04Ch
    _emit 024h
    _emit 008h
    _emit 051h
    _emit 08Bh
    _emit 0CEh
    _emit 0FFh
    _emit 0D2h
    _emit 08Bh
    _emit 054h
    _emit 024h
    _emit 00Ch
    _emit 08Bh
    _emit 04Eh
    _emit 018h
    _emit 08Bh
    _emit 076h
    _emit 014h
    _emit 08Bh
    _emit 001h
    _emit 08Bh
    _emit 03Eh
    _emit 08Bh
    _emit 040h
    _emit 01Ch
    _emit 052h
    _emit 08Bh
    _emit 054h
    _emit 024h
    _emit 00Ch
    _emit 052h
    _emit 083h
    _emit 0C7h
    _emit 02Ch
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 017h
    _emit 050h
    _emit 08Dh
    _emit 04Ch
    _emit 024h
    _emit 014h
    _emit 051h
    _emit 08Bh
    _emit 0CEh
    _emit 0FFh
    _emit 0D2h
    _emit 08Bh
    _emit 010h
    _emit 08Bh
    _emit 04Ch
    _emit 024h
    _emit 024h
    _emit 089h
    _emit 011h
    _emit 08Bh
    _emit 050h
    _emit 004h
    _emit 089h
    _emit 051h
    _emit 004h
    _emit 08Bh
    _emit 040h
    _emit 008h
    _emit 05Fh
    _emit 089h
    _emit 041h
    _emit 008h
    _emit 05Eh
    _emit 083h
    _emit 0C4h
    _emit 014h
    _emit 0C2h
    _emit 008h
    _emit 000h
  }
}

// @ 0x007a5020
__declspec(naked) void FUN_007a5020() {
  __asm {
    _emit 056h
    _emit 057h
    _emit 08Bh
    _emit 0F1h
    _emit 033h
    _emit 0FFh
    _emit 039h
    _emit 07Eh
    _emit 054h
    _emit 074h
    _emit 04Ch
    _emit 08Bh
    _emit 096h
    _emit 0DCh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 04Eh
    _emit 018h
    _emit 08Bh
    _emit 001h
    _emit 08Bh
    _emit 040h
    _emit 014h
    _emit 052h
    _emit 08Bh
    _emit 096h
    _emit 0D8h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 052h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 046h
    _emit 054h
    _emit 03Bh
    _emit 0C7h
    _emit 074h
    _emit 02Dh
    _emit 083h
    _emit 0C0h
    _emit 008h
    _emit 089h
    _emit 07Eh
    _emit 054h
    _emit 08Bh
    _emit 0C8h
    _emit 083h
    _emit 0CAh
    _emit 0FFh
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 011h
    _emit 033h
    _emit 0C9h
    _emit 08Bh
    _emit 0D0h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 00Ah
    _emit 083h
    _emit 0F9h
    _emit 001h
    _emit 07Dh
    _emit 00Bh
    _emit 0B9h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 008h
    _emit 0EBh
    _emit 006h
    _emit 033h
    _emit 0D2h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 010h
    _emit 039h
    _emit 07Eh
    _emit 06Ch
    _emit 074h
    _emit 04Ch
    _emit 08Bh
    _emit 096h
    _emit 004h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 04Eh
    _emit 018h
    _emit 08Bh
    _emit 001h
    _emit 08Bh
    _emit 040h
    _emit 014h
    _emit 052h
    _emit 08Bh
    _emit 096h
    _emit 000h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 052h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 046h
    _emit 06Ch
    _emit 03Bh
    _emit 0C7h
    _emit 074h
    _emit 02Dh
    _emit 083h
    _emit 0C0h
    _emit 008h
    _emit 089h
    _emit 07Eh
    _emit 06Ch
    _emit 08Bh
    _emit 0C8h
    _emit 083h
    _emit 0CAh
    _emit 0FFh
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 011h
    _emit 033h
    _emit 0C9h
    _emit 08Bh
    _emit 0D0h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 00Ah
    _emit 083h
    _emit 0F9h
    _emit 001h
    _emit 07Dh
    _emit 00Bh
    _emit 0B9h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 008h
    _emit 0EBh
    _emit 006h
    _emit 033h
    _emit 0D2h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 010h
    _emit 039h
    _emit 07Eh
    _emit 060h
    _emit 074h
    _emit 04Ch
    _emit 08Bh
    _emit 096h
    _emit 0F4h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 04Eh
    _emit 018h
    _emit 08Bh
    _emit 001h
    _emit 08Bh
    _emit 040h
    _emit 014h
    _emit 052h
    _emit 08Bh
    _emit 096h
    _emit 0F0h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 052h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 046h
    _emit 060h
    _emit 03Bh
    _emit 0C7h
    _emit 074h
    _emit 02Dh
    _emit 083h
    _emit 0C0h
    _emit 008h
    _emit 089h
    _emit 07Eh
    _emit 060h
    _emit 08Bh
    _emit 0C8h
    _emit 083h
    _emit 0CAh
    _emit 0FFh
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 011h
    _emit 033h
    _emit 0C9h
    _emit 08Bh
    _emit 0D0h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 00Ah
    _emit 083h
    _emit 0F9h
    _emit 001h
    _emit 07Dh
    _emit 00Bh
    _emit 0B9h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 008h
    _emit 0EBh
    _emit 006h
    _emit 033h
    _emit 0D2h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 010h
    _emit 039h
    _emit 07Eh
    _emit 064h
    _emit 074h
    _emit 04Ch
    _emit 08Bh
    _emit 096h
    _emit 0FCh
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 04Eh
    _emit 018h
    _emit 08Bh
    _emit 001h
    _emit 08Bh
    _emit 040h
    _emit 014h
    _emit 052h
    _emit 08Bh
    _emit 096h
    _emit 0F8h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 052h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 046h
    _emit 064h
    _emit 03Bh
    _emit 0C7h
    _emit 074h
    _emit 02Dh
    _emit 083h
    _emit 0C0h
    _emit 008h
    _emit 089h
    _emit 07Eh
    _emit 064h
    _emit 08Bh
    _emit 0C8h
    _emit 083h
    _emit 0CAh
    _emit 0FFh
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 011h
    _emit 033h
    _emit 0C9h
    _emit 08Bh
    _emit 0D0h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 00Ah
    _emit 083h
    _emit 0F9h
    _emit 001h
    _emit 07Dh
    _emit 00Bh
    _emit 0B9h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 008h
    _emit 0EBh
    _emit 006h
    _emit 033h
    _emit 0D2h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 010h
    _emit 039h
    _emit 07Eh
    _emit 070h
    _emit 074h
    _emit 04Ch
    _emit 08Bh
    _emit 096h
    _emit 00Ch
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 08Bh
    _emit 04Eh
    _emit 018h
    _emit 08Bh
    _emit 001h
    _emit 08Bh
    _emit 040h
    _emit 014h
    _emit 052h
    _emit 08Bh
    _emit 096h
    _emit 008h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 052h
    _emit 0FFh
    _emit 0D0h
    _emit 08Bh
    _emit 046h
    _emit 070h
    _emit 03Bh
    _emit 0C7h
    _emit 074h
    _emit 02Dh
    _emit 083h
    _emit 0C0h
    _emit 008h
    _emit 089h
    _emit 07Eh
    _emit 070h
    _emit 08Bh
    _emit 0C8h
    _emit 083h
    _emit 0CAh
    _emit 0FFh
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 011h
    _emit 033h
    _emit 0C9h
    _emit 08Bh
    _emit 0D0h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 00Ah
    _emit 083h
    _emit 0F9h
    _emit 001h
    _emit 07Dh
    _emit 00Bh
    _emit 0B9h
    _emit 001h
    _emit 000h
    _emit 000h
    _emit 000h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 008h
    _emit 0EBh
    _emit 006h
    _emit 033h
    _emit 0D2h
    _emit 0F0h
    _emit 00Fh
    _emit 0C1h
    _emit 010h
    _emit 08Bh
    _emit 006h
    _emit 08Bh
    _emit 050h
    _emit 034h
    _emit 05Fh
    _emit 08Bh
    _emit 0CEh
    _emit 05Eh
    _emit 0FFh
    _emit 0E2h
  }
}
