// src/game/SPEngine/SPGraphicsStaticBufferDraw.cpp -- migrated from slice(s) s007a41c0, s007a3260 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsStaticBufferDraw.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl FUN_007c3af0(const char* fmt);         // vertex-format lookup by name
extern char gVertexFormatsDirty;       // 0x0153b690 (starts nonzero)
extern int gVertexFormats[12];         // 0x01634770
#include <intrin.h>
#include <new>
#include "SP/cDebugDraw.h"
#include "SP/cGraphicsSystem.h"
#include "SP/cIRTTManager.h"
#include "SP/cIRenderer.h"
#include "SP/cPropertyList.h"
#include "SP/cStaticBuffer.h"
#include "SP/cStaticBufferDraw.h"
#include "SP/cViewer.h"
#include <math.h>
#include <stdlib.h>
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---- items of slice s007a3260 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cStaticBufferDraw;
extern cStaticBufferDraw* gStaticBufferDraw;                  // 0x015ddc84
extern "C" int __cdecl FUN_007c3af0(const char* fmt);         // vertex-format lookup by name
struct SingletonBaseStub {
    SingletonBaseStub(cStaticBufferDraw* p) { gStaticBufferDraw = p; }
    ~SingletonBaseStub();
};
struct cStaticBufferDraw : SingletonBaseStub {
    int mStaticBuffer;       // +0x00
    int mField04;
    int mField08;
    int mField0c;
    int mField10;
    int mField14;
    int mField18;
    int mField1c;
    char mField20;
    char _pad21[3];
    int mField24;
    int mField28;
    int mField2c;
    int mField30;
    char _pad34[12];
    char mField40;
    char _pad41[3];
    int mVertexDesc;         // +0x44

    cStaticBufferDraw();
    void SetVertexFormat(int fmt);
    static void sInstanceReset();
};
cStaticBufferDraw* gStaticBufferDraw;
extern char gVertexFormatsDirty;       // 0x0153b690 (starts nonzero)
extern int gVertexFormats[12];         // 0x01634770
// ---- items of slice s007a3260 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cStaticBufferDraw* gStaticBufferDraw;                  // 0x015ddc84

// ---- items of slice s007a41c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  EXT_6de350(...);
extern "C" void  EXT_6ec4a0(...);
extern "C" void* EXT_720200(...);
extern "C" void  EXT_762a00(...);
extern "C" void  EXT_762a30(...);
extern "C" void  EXT_7a3ce0(...);
extern "C" void  EXT_cc8b50(...);
extern "C" void  EXT_f47380(...);
extern "C" void* EXT_f473a0(...);
extern "C" void* FUN_011f3620(...);
extern "C" void  EXT_11f36a0();
extern "C" void  EXT_11f4fd0(...);
extern "C" void* FUN_00762b70(...);
typedef unsigned char  u8;
typedef unsigned int   u32;
struct MeshElement {
  u32 v0;  // +0x00
  u32 v1;  // +0x04
  u32 v2;  // +0x08
  u32 v3;  // +0x0c
  u32 v4;  // +0x10
  u32 v5;  // +0x14
};
struct MeshVector {
  MeshElement* mpBegin;     // +0x00
  MeshElement* mpEnd;       // +0x04
  MeshElement* mpCapacity;  // +0x08

  void grow(MeshElement* at, MeshElement* src);  // 0x007a44b0
  void push_back(MeshElement* src);              // 0x007a4600
};
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
struct cStaticBufferDraw_s007a_41c0 {
  cStaticBuffer buffer;  // +0x00  (0x4c bytes; the ctor sets +0x48)

  void Ctor(u32 param_1, u32 param_2, u32 param_3, u32 count);  // 0x007a4420
};
extern cStaticBufferDraw_s007a_41c0* g_pStaticBufferDraw;  // 0x15ddc84
// ---- items of slice s007a41c0 end

// @ 0x007a3ce0
void cStaticBufferDraw::SetVertexFormat(int fmt)
{
    if (gVertexFormatsDirty) {
        gVertexFormatsDirty = 0;
        gVertexFormats[0] = FUN_007c3af0("V3FC4B");
        gVertexFormats[1] = FUN_007c3af0("V3FT2F");
        gVertexFormats[2] = FUN_007c3af0("V3FC4BT2F");
        gVertexFormats[3] = FUN_007c3af0("V3FC4BT3F");
        gVertexFormats[4] = FUN_007c3af0("V3FN3FC4BT2F");
        gVertexFormats[5] = FUN_007c3af0("V3FC4BP1F");
        gVertexFormats[6] = FUN_007c3af0("V4FN4FC4BT2F");
        gVertexFormats[7] = FUN_007c3af0("V4FN4FC4BC4B");
        gVertexFormats[8] = FUN_007c3af0("V4FN4FG3FC4BC4B");
        gVertexFormats[9] = FUN_007c3af0("V4FN3FC4BT4FT4FT4FT4FT4F");
        gVertexFormats[10] = FUN_007c3af0("V3FC4BT2FT2FT2F");
        gVertexFormats[11] = FUN_007c3af0("V4FN4FC4BC4BT4B");
    }
    mVertexDesc = gVertexFormats[fmt];
}

// @ 0x007a4220
cStaticBuffer::~cStaticBuffer()
{
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

// @ 0x007a4320
void __cdecl FUN_007a4320()
{
  cStaticBufferDraw_s007a_41c0* const p = g_pStaticBufferDraw;
  if (p != 0) {
    EXT_6de350(p);
    g_pStaticBufferDraw = 0;
    EXT_f47380(p);
  }
}

// @ 0x007a4380
cStaticBuffer* cStaticBuffer::Ctor(u32 param_1, u32 param_2)
{
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

// @ 0x007a4420
void cStaticBufferDraw_s007a_41c0::Ctor(u32 param_1, u32 param_2, u32 param_3, u32 count)
{
  buffer.mUnk04 = (u32)(((int)count < 1) ? 0 : count);
  cStaticBuffer* p =
      (cStaticBuffer*)EXT_f473a0(0x4c, "Graphics/StaticBufferDraw", 0, 0, 0, 0);
  if (p != 0) {
    p->Ctor(param_2, param_3);
  }
  buffer.mDrawVector.mpCapacity = (MeshElement*)p;
  p->sb01();
}

// @ 0x007a44b0
void MeshVector::grow(MeshElement* at, MeshElement* src)
{
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

// @ 0x007a4600
void MeshVector::push_back(MeshElement* src)
{
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

// @ 0x007a4650
void cStaticBuffer::SnapshotPending()
{
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

// @ 0x007a4710
void cStaticBuffer::Flush()
{
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

// @ 0x007a47c0
u32 cStaticBuffer::GetVertexBuffer(u32 numVertices, u32* outCount, u32* outStride)
{
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
