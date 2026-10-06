// Slice s009a0d60 (bfs4 #33): nSPCreatureAnim::CreateAnimationBindRecords helpers
// (bind_record_helper / variant_helper local classes) and animation blob loader.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;
extern "C" void  operator_delete(void*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern const float g_one;     // 0x01485720  1.0f
extern const float g_u32bias; // 0x013f4fd0  4294967296.0f

// ---------------------------------------------------------------------------
// small shared types (offsets verified against the disassembly)
// ---------------------------------------------------------------------------
struct U64Pair { uint a; uint b; };                 // 8-byte record
struct Rec16 { uint w0; uint w1; uint w2; uint w3; }; // 16-byte bind record

struct IntVec {                                      // eastl::vector<int>-like (begin,end,cap)
  int* mpBegin;
  int* mpEnd;
  int* mpCap;
  void clear() {
    int* last = mpEnd;
    int* first = mpBegin;
    memcpy(first, last, (char*)mpEnd - (char*)last);
    mpEnd = mpEnd - (last - first);
  }
};

// ===========================================================================
// @ 0x009a0d60  load a relocatable blob, rebase its pointer table, write it out
// ===========================================================================
extern "C" char* FUN_0099f110(void* a, void* b);
struct IBlobSink {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual int  Write(void* p, int n);               // slot 3
};
bool FUN_009a0d60(void* a, void* b, IBlobSink* sink) {
  char* blob = FUN_0099f110(a, b);
  bool ok;
  if (blob != 0 && *(int*)(blob + 4) != 0) {
    uint count = *(uint*)(blob + 0x14c);
    if (count != 0) {
      int* table = (int*)(blob + *(int*)(blob + 0x150));
      int neg = -(int)blob;
      uint i = 0;
      for (; i < count; ++i) {
        int* slot = (int*)(table[i] + (int)blob);
        int v = *slot;
        if (v <= neg) goto fail;
        *slot = v + neg;
      }
      int r = sink->Write(blob, *(int*)(blob + 4));
      if (r == *(int*)(blob + 4)) {
        ok = true;
        goto done;
      }
    }
  }
fail:
  ok = false;
done:
  if (blob != 0) operator_delete(blob);
  return ok;
}

struct BindSlot {                                    // 0x1f0 bytes, per-record state
  int  mpRecord;       // +0x000
  char pad0[0x1b8];
  int  mCursor;        // +0x1bc  (index 0x6f)
  float mV[7];         // +0x1c0 .. +0x1d8 (0 0 0 0 0 0 1.0f)
  IntVec mList;        // +0x1dc
  char pad1[4];
};

// ===========================================================================
// @ 0x009a0df0  reset a bind slot (zero fields, clear its list)
// ===========================================================================
struct SlotReset {
  uint mState;         // +0x000
  char pad0[0x1bc];
  float mV0, mV1, mV2, mV3, mV4, mV5, mV6;   // +0x1c0..+0x1d8
  IntVec mList;        // +0x1dc
  void Reset();
};
void SlotReset::Reset() {
  mState = 0;
  mV0 = 0.0f; mV1 = 0.0f; mV2 = 0.0f;
  mV3 = 0.0f; mV4 = 0.0f; mV5 = 0.0f;
  mV6 = g_one;
  int* last = mList.mpEnd;
  int* first = mList.mpBegin;
  memcpy(first, last, (char*)mList.mpEnd - (char*)last);
  mList.mpEnd = mList.mpEnd - (last - first);
}

// ===========================================================================
// @ 0x009a0e70  push_back of an 8-byte record (vector at this: +4 end, +8 cap)
// ===========================================================================
struct Vec8 {
  U64Pair* mpBegin;    // +0
  U64Pair* mpEnd;      // +4
  U64Pair* mpCap;      // +8
  void push_back(const U64Pair* v);
  void GrowAppend(U64Pair* pos, const U64Pair* v);   // 0x009a0c50
};
void Vec8::push_back(const U64Pair* v) {
  U64Pair* p = mpEnd;
  if (p < mpCap) {
    mpEnd = p + 1;
    if (p != 0) {
      p->a = v->a;
      p->b = v->b;
    }
  } else {
    GrowAppend(p, v);
  }
}

// ===========================================================================
// 16-byte record vector (eastl::vector<Rec16>)
// ===========================================================================
struct Vec16 {
  Rec16* mpBegin;      // +0
  Rec16* mpEnd;        // +4
  Rec16* mpCap;        // +8
  void GrowAppend(Rec16* pos, const Rec16* v);       // 0x0092a100
};
struct VariantEntry {                                // 0x28 bytes, array at +0x218
  uint mType;      // +0x218
  int  mChosen;    // +0x21c
  uint mArg;       // +0x220
  int  mFlag;      // +0x224
  int  mFlag2;     // +0x228
  int* mpBegin;    // +0x22c  candidate list (begin)
  int* mpEnd;      // +0x230  (end)
  int* mpCap;      // +0x234
  uint pad[2];
};
struct AnimRec { char pad0[0x88]; uint8_t mFlags; char pad1[0x23]; uint mCtx; };
struct AnimData {                                    // *(this+0xc1c)
  char pad[0x144];
  uint mNumRecords;      // +0x144
  AnimRec** mpRecords;   // +0x148
};

// ===========================================================================
// bind object (this of 0x009a0f10; also of nSPCreatureAnim bind_record_helper::InitChannel)
// ===========================================================================
namespace {
struct AnimEntry {                                   // 0x20 bytes
  uint mTypeFlags;       // +0x00  (& 0xf = kind, byte &0x10 = flag)
  uint mHash;            // +0x04
  uint mData8;           // +0x08
  uint mData12;          // +0x0c
  uint mSlot;            // +0x10  slot index (< 9)
  uint pad[3];
};
struct AnimRec2 {
  char    pad0[0x8c];
  uint    mCtx;          // +0x8c
  char    pad1[0x1c];
  uint8_t mFlagsAC;      // +0xac
  uint8_t pad2;
  uint8_t mIdAE;         // +0xae
  uint8_t mTypeAF;       // +0xaf
  char    pad3[0x24];
  uint    mCount;        // +0xd4
  char    pad4[4];
  uint    mNumEntries;   // +0xdc
  AnimEntry* mpEntries;  // +0xe0
};
struct CtxEntry {                                    // 0x468 bytes
  char pad[0x200];
  int  mNameIdx;         // +0x200
  char pad2[0x264];
};
struct CtxObj {
  char pad[0x384];
  CtxEntry* mpEntries;   // +0x384
};
struct BindRec {                                     // 16 bytes, local to AddBindRecord
  uint w0;
  uint w1;
  uint w2;
  uint8_t mSlot;         // +0x0c
  uint8_t mArg;          // +0x0d
  uint8_t mName;         // +0x0e
  uint8_t mFlags;        // +0x0f
};
struct BindObj {
  AnimData* mpOwner;       // +0x000
  CtxObj*   mpCtx;         // +0x004
  Vec16*    mpOut;         // +0x008
  int       mNumFlagged;   // +0x00c
  int       mNumPlain;     // +0x010
  int       mNumNamed;     // +0x014
  uint8_t   mSlots[0x8f8]; // +0x018
  AnimRec2* mpCur;         // +0x910
  uint8_t   mBuf[0x3fc];   // +0x914
  uint      mDiv;          // +0xd10
  int       mDefault;      // +0xd14
  uint8_t   mHasName;      // +0xd18
};

extern "C" uint FUN_0099c670(void* rec, void* ctxEntry, uint c);

// ===========================================================================
// @ 0x009a0eb0  append a bind record and bump counters (ctx in EAX originally)
// ===========================================================================
static void AddRecordCountedS(BindObj* b, BindRec* r) {
  if ((r->mFlags & 1) != 0) {
    b->mNumFlagged += 1;
  } else if (r->mSlot == 0) {
    b->mNumPlain += 1;
  }
  if (r->mName != 0xff) {
    b->mNumNamed += 1;
  }
  Vec16* v = b->mpOut;
  Rec16* p = v->mpEnd;
  if (p < v->mpCap) {
    v->mpEnd = p + 1;
    if (p != 0) {
      *(BindRec*)p = *r;
    }
  } else {
    v->GrowAppend(p, (Rec16*)r);
  }
}

// ===========================================================================
// @ 0x009a0f10  compute and append the bind record(s) for one (channel, variant)
// ===========================================================================
static void __stdcall AddBindRecordS(BindObj* self, uint x, int index, uint8_t kind, int typeKey,
                           uint lo, uint hi, uint c) {
  AnimRec2* cur = self->mpCur;
  int iVar7 = (int)FUN_0099c670(cur, (char*)self->mpCtx->mpEntries + index * 0x468, c);
  uint hiKey = (uint)typeKey << 24;
  BindRec rec;
  rec.w0 = lo;
  rec.w1 = hi;
  uint ctxv = cur->mCtx & 0x100003;
  rec.w2 = hiKey;
  rec.mSlot = (uint8_t)index;
  rec.mArg = kind;
  rec.mName = 0xff;
  uint8_t bl = (iVar7 != 0) ? 2 : 0;
  rec.mFlags = bl;
  bool bVar6 = false;
  if (ctxv == 0x100000 || ctxv == 0x100001) bVar6 = true;
  bool eq1 = (ctxv == 1);
  if (bVar6) {
    rec.mFlags |= 1;
    rec.mSlot = 0xff;
  }
  uint count = cur->mNumEntries;
  uint chosenIdx = 0xffffffff;
  bool bVar5 = false;
  uint k = 0;
  uint mask = 1;
  if (count > 0) {
    uint off = 0;
    do {
      AnimRec2* cur2 = self->mpCur;
      AnimEntry* e = (AnimEntry*)((char*)cur2->mpEntries + off);
      if (e->mSlot < 9) {
        uint8_t* p = &self->mSlots[e->mSlot + index * 9];
        uint8_t cv = *p;
        if (cv == 0xff || cv == cur2->mIdAE || bVar6) {
          if ((*(uint8_t*)e & 0x10) != 0) {
            if (!bVar6) *p = cur2->mIdAE;
            if (eq1 && index == 0 && (e->mTypeFlags & 0xf) == 3 && e->mHash == 0x70e47545) {
              chosenIdx = k;
            } else {
              rec.w2 = rec.w2 ^ (((mask | rec.w2) ^ rec.w2) & 0xffffff);
              if ((e->mTypeFlags & 0xf) == 1) rec.mFlags |= 0x20;
            }
          }
          bVar5 = true;
        }
      }
      off += 0x20;
      ++k;
      mask = (mask << 1) | (mask >> 31);
    } while (k < count);
  }
  uint div = self->mDiv;
  if (div == 0) {
    if (self->mDefault != -1) {
      rec.mName = (uint8_t)self->mDefault;
      rec.mFlags |= 0x10;
    }
  } else {
    if (self->mHasName != 0) {
      int v = self->mpCtx->mpEntries[index].mNameIdx;
      if (v != -1) {
        rec.mName = (uint8_t)v;
        if ((uint8_t)v != 0xff) goto havename;
      }
    }
    rec.mName = self->mBuf[(x % div) * 4];
  }
havename:
  if ((rec.w2 & 0xffffff) != 0) {
    if ((rec.mFlags & 1) != 0) {
      self->mNumFlagged += 1;
    } else if (rec.mSlot == 0) {
      self->mNumPlain += 1;
    }
    if (rec.mName != 0xff) self->mNumNamed += 1;
    Vec16* v = self->mpOut;
    Rec16* p = v->mpEnd;
    if (p < v->mpCap) {
      v->mpEnd = p + 1;
      if (p != 0) *(BindRec*)p = rec;
    } else {
      v->GrowAppend(p, (Rec16*)&rec);
    }
  } else if (bVar5 && (self->mpCur->mFlagsAC & 8) != 0) {
    rec.mFlags |= 8;
    AddRecordCountedS(self, &rec);
  }
  if (chosenIdx != 0xffffffff) {
    rec.mArg = kind;
    rec.w0 = lo;
    rec.w1 = hi;
    rec.w2 = hiKey ^ (((1u << (chosenIdx & 0x1f)) | hiKey) ^ hiKey) & 0xffffff;
    rec.mName = 0xff;
    bl |= 5;
    rec.mFlags = bl;
    rec.mSlot = 0xff;
    if ((bl & 1) != 0) self->mNumFlagged += 1;
    Vec16* v = self->mpOut;
    Rec16* p = v->mpEnd;
    if (p < v->mpCap) {
      v->mpEnd = p + 1;
      if (p != 0) *(BindRec*)p = rec;
    } else {
      v->GrowAppend(p, (Rec16*)&rec);
    }
  }
}

// ===========================================================================
// variant generator object
// ===========================================================================
struct VecHolder { Rec16* mpBegin; };
struct Gen {
  struct { int key; int val; } mKeys[64];            // +0x000 (stride 8)
  int   mCounter;        // +0x200
  char  pad0[4];
  VecHolder** mppVec;    // +0x208
  uint  mIdx;            // +0x20c
  uint  mEndIdx;         // +0x210
  BindObj* mpBind;       // +0x214
  VariantEntry mEntries[64];   // +0x218
  uint  mNumEntries;     // +0xc18
  AnimData* mpAnim;      // +0xc1c
  CtxObj* mpCtx;         // +0xc20

  void GenerateVariantsRecurse(uint index, void* p3);   // 0x009a1470
  void Prepare(int flag);                               // 0x0099d1f0
};

extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" void FUN_009b1d80(void* buf, uint* outCount, void* ctx, void* ctxEntry, void* rec);
extern void InitChannelStatic(BindObj* b, int index, void* p3);   // 0x0099c7b0 (separate slice)

// ===========================================================================
// @ 0x009a1250  emit the bind records for the current variant selection
// ===========================================================================
static void __stdcall EmitVariantS(Gen* g, void* p3) {
  memset((char*)g->mpBind + 0x18, 0xff, 0x8f7);
  int c = g->mCounter;
  unsigned __int64 mask = (unsigned __int64)1 << c;
  g->mCounter = c + 1;
  uint e = 0;
  if (g->mNumEntries != 0) {
    VariantEntry* ent = g->mEntries;
    do {
      uint chosen = (uint)ent->mChosen;
      if (chosen != 0xffffffff) {
        uint typeKey = ent->mType;
        uint arg = ent->mFlag2 == 0 ? ent->mArg : ent->mArg;
        arg = ent->mArg;
        uint numRec = g->mpAnim->mNumRecords;
        uint r = 0;
        if (numRec != 0) {
          do {
            AnimRec* rec = g->mpAnim->mpRecords[r];
            if ((rec->mFlags & 1) != 0 && ((uint8_t*)rec)[0xaf] == typeKey) {
              uint outCount = 1;
              uint buf[0x100];
              buf[0] = chosen;
              memset(&buf[1], 0, 0x3f8);
              FUN_009b1d80(buf, &outCount, g->mpCtx,
                           (char*)g->mpCtx->mpEntries + chosen * 0x468, (char*)rec + 0x8c);
              InitChannelStatic(g->mpBind, (int)r, p3);
              uint k = 0;
              if (outCount != 0) {
                do {
                  uint v = buf[k];
                  uint i = g->mIdx;
                  if (i < g->mEndIdx) {
                    do {
                      uint* p = (uint*)((char*)(*g->mppVec)->mpBegin + i * 16);
                      if (((uint8_t*)p)[0xc] == v) {
                        p[0] = p[0] & ~(uint)mask;
                        p[1] = p[1] & ~(uint)(mask >> 32);
                      }
                      ++i;
                    } while (i < g->mEndIdx);
                  }
                  AddBindRecordS(g->mpBind, arg, (int)v, (uint8_t)r, (int)typeKey,
                                (uint)mask, (uint)(mask >> 32), (uint)(unsigned)(size_t)p3);
                  ++k;
                } while (k < outCount);
              }
            }
            ++r;
          } while (r < numRec);
        }
      }
      ++e;
      ++ent;
    } while (e < g->mNumEntries);
  }
}

// ===========================================================================
// @ 0x009a1470  GenerateVariantsRecurse
// ===========================================================================
void Gen::GenerateVariantsRecurse(uint index, void* p3) {
  int idx = (int)index;
  char* base = (char*)this + idx * 0x28;
  uint i = 0;
  uint count = (uint)((*(int*)(base + 0x230) - *(int*)(base + 0x22c)) >> 2);
  do {
    int chosen;
    if (count != 0) {
      chosen = (*(int**)(base + 0x22c))[i];
    } else {
      chosen = -1;
    }
    int j = idx - 1;
    if (j >= 0) {
      int* p = (int*)((char*)this + 0x21c + j * 0x28);
      do {
        if (*p == chosen) {
          chosen = -1;
          break;
        }
        j = j - 1;
        p = p - 10;
      } while (j >= 0);
    }
    *(int*)(base + 0x21c) = chosen;
    if (*(int*)(base + 0x224) == 0 || chosen != -1) {
      if (idx == (int)mNumEntries - 1) {
        EmitVariantS(this, p3);
      } else {
        GenerateVariantsRecurse(idx + 1, p3);
      }
    }
    ++i;
  } while (i < count);
}


// ===========================================================================
// @ 0x009a1a60  GenerateVariants  (this in ESI originally)
// ===========================================================================
static int __stdcall GenerateVariantsS(Gen* g, void* p) {
  Gen* const self = g;
  if (self->mNumEntries != 0) {
    self->Prepare(0);
    uint n = self->mNumEntries;
    uint i = 0;
    if (0 < n) {
      int* q = &((VariantEntry*)((char*)self + 0x218))[0].mFlag2;
      do {
        if (q[-1] == 0 && q[0] != 0) return 0;
        ++i;
        q += 10;
      } while (i < n);
    }
    int before = self->mCounter;
    self->GenerateVariantsRecurse(0, p);
    return self->mCounter - before;
  }
  return 1;
}
}  // namespace

int GenerateVariantsEntry(Gen* g, void* p) { return GenerateVariantsS(g, p); }

// ===========================================================================
// slot object (0x1f0 bytes): header block, 7 floats, int list
// ===========================================================================
struct SlotBase { void Init(); };                    // 0x0099ece0
struct SlotBlock { uint w[0x6e]; };                  // +0x004 .. +0x1bc (rep movsd copies)
struct F7 {                                          // copied with fld/fstp (x87)
  float v[7];
  F7() {}
  F7(const F7& o) { for (int i = 0; i < 7; ++i) v[i] = o.v[i]; }
};
struct ListAlloc { uint a; uint b; };
struct FVec {                                        // eastl vector with fixed allocator: begin,end,cap,alloc
  int*      mpBegin;
  int*      mpEnd;
  int*      mpCap;
  ListAlloc mAlloc;
  void Allocate(uint n, const ListAlloc* src);       // 0x00a69430
  void Assign(const FVec* o);                        // 0x0050d4e0 (vector<float>::operator=)
};
struct SlotObj {
  uint      mState;      // +0x000
  SlotBlock mBlock;      // +0x004
  int       mCursor;     // +0x1bc
  float     mV0, mV1, mV2, mV3, mV4, mV5, mV6;   // +0x1c0..+0x1d8
  FVec      mList;       // +0x1dc
  SlotObj* Construct();                              // 0x009a1530
  void Reset();                                      // 0x009a0df0
  SlotObj* CopyConstruct(const SlotObj* o);          // 0x009a17d0
  SlotObj* CopyAssign(const SlotObj* o);             // 0x009a18a0
};

// ===========================================================================
// @ 0x009a1530  slot constructor (zero state, empty list)
// ===========================================================================
SlotObj* SlotObj::Construct() {
  ((SlotBase*)((char*)this + 4))->Init();
  mV2 = 0.0f; mV1 = 0.0f; mV0 = 0.0f;
  mV5 = 0.0f; mV4 = 0.0f; mV3 = 0.0f;
  mV6 = g_one;
  mList.mpBegin = 0;
  mList.mpEnd = 0;
  mList.mpCap = 0;
  Reset();
  return this;
}

// ===========================================================================
// @ 0x009a15a0  scan a channel's sample table for the first sample after time f
// ===========================================================================
struct TagIdx { uint16_t tag; uint16_t pad; int index; };
int FUN_009a15a0(float unused, float f, AnimRec2* rec, uint16_t tag, uint maxv,
                 uint* arr, Vec8* out) {
  int n = (int)rec->mCount;
  int idx = -1;
  if (0 < n) {
    uint i = 0;
    AnimEntry* e = rec->mpEntries;
    uint ne = rec->mNumEntries;
    if (ne > 0) {
      do {
        if ((*(uint8_t*)e & 0xf) == 0 && e->mHash != 0) {
          e = (AnimEntry*)((char*)rec->mpEntries + i * 0x20);
          goto found;
        }
        ++i;
        ++e;
      } while (i < ne);
    }
    e = 0;
found:
    int* p = (int*)(e->mData8 + *(int*)((char*)rec + 0xd8));
    idx = 0;
    if (0 < n) {
      do {
        float fv = (float)*(uint*)p;
        if (f < fv) return idx;
        if (((uint8_t*)p)[10] != 0 && arr != 0 && arr[idx] < maxv && out != 0) {
          TagIdx t;
          t.tag = tag;
          t.index = idx;
          out->push_back((const U64Pair*)&t);
        }
        p = (int*)((char*)p + e->mData12);
        ++idx;
      } while (idx < n);
    }
  }
  return idx;
}

// ===========================================================================
// @ 0x009a1670  run FUN_009a15a0 over every selected channel of the animation
// ===========================================================================
struct AnimInst {
  AnimData* mpData;        // +0x00
  char pad0[0x10];
  char* mpSlots;           // +0x14  (stride 0x1f0)
  char pad1[0x28];
  int  mCount;             // +0xc0 (obj[0x30])
};
extern "C" void FUN_0099f970(float f, int idx, void* rec, void* p, int zero);
void FUN_009a1670(int* obj, float f, char p3, char p4, uint p5, uint p6, uint p7, uint p8) {
  uint n = *(uint*)(*obj + 0x144);
  uint idx = 0;
  if (n != 0) {
    int off = 0;
    do {
      int* sl = (int*)(obj[5] + off);
      unsigned __int64 m = (unsigned __int64)1 << idx;
      uint lo = (uint)m;
      uint hi = (uint)(m >> 32);
      if ((((lo & p5) != 0) || ((hi & p6) != 0)) && *(int*)(*sl + 0xd4) != 0 &&
          (*(uint8_t*)(*sl + 0xac) & 1) != 0) {
        Vec8* outv;
        if (p4 == 0) outv = 0; else outv = (Vec8*)(obj + 0x32);
        int r = FUN_009a15a0(0.0f, f, (AnimRec2*)*sl, (uint16_t)idx, (uint)obj[0x30],
                             (uint*)sl[0x77], outv);
        if (p3 != 0 && (((lo & p7) != 0) || ((hi & p8) != 0))) {
          sl[0x6f] = sl[4];
          FUN_0099f970(f, r, (void*)*sl, sl + 1, 0);
        }
      }
      off += 0x1f0;
      ++idx;
    } while (idx < n);
  }
}

// ===========================================================================
// @ 0x009a1770  Vec8::resize(n): pad with {0xffff, -1} or erase the tail
// ===========================================================================
struct Vec8b {
  U64Pair* mpBegin;    // +0
  U64Pair* mpEnd;      // +4
  U64Pair* mpCap;      // +8
  uint size() const { return (uint)(mpEnd - mpBegin); }
  void resize(uint n);
};
extern "C" void __stdcall FUN_00abb660(void* end, uint count, const void* val);
extern "C" void __stdcall FUN_00d018d0(void* pos, void* end);
struct PadVal { uint16_t a; uint16_t pad; int b; PadVal(uint16_t x, int y) { a = x; b = y; } };
void Vec8b::resize(uint n) {
  if (n > size()) {
    PadVal v(0xffff, -1);
    FUN_00abb660(mpEnd, n - size(), &v);
    return;
  }
  FUN_00d018d0(mpBegin + n, mpEnd);
}

// ===========================================================================
// @ 0x009a17d0  slot copy-construct
// ===========================================================================
SlotObj* SlotObj::CopyConstruct(const SlotObj* o) {
  mState = o->mState;
  mBlock = o->mBlock;
  mCursor = o->mCursor;
  mV0 = o->mV0; mV1 = o->mV1; mV2 = o->mV2; mV3 = o->mV3;
  mV4 = o->mV4; mV5 = o->mV5; mV6 = o->mV6;
  mList.Allocate((uint)(o->mList.mpEnd - o->mList.mpBegin), &o->mList.mAlloc);
  int* e = o->mList.mpEnd;
  int* b = o->mList.mpBegin;
  int bytes = (int)e - (int)b;
  int* d = (int*)memcpy(mList.mpBegin, b, (uint)bytes);
  mList.mpEnd = d + (bytes >> 2);
  return this;
}

// ===========================================================================
// @ 0x009a18a0  slot copy-assign
// ===========================================================================
SlotObj* SlotObj::CopyAssign(const SlotObj* o) {
  mState = o->mState;
  mBlock = o->mBlock;
  mCursor = o->mCursor;
  mV0 = o->mV0; mV1 = o->mV1; mV2 = o->mV2; mV3 = o->mV3;
  mV4 = o->mV4; mV5 = o->mV5; mV6 = o->mV6;
  mList.Assign(&o->mList);
  return this;
}

// ===========================================================================
// @ 0x009a1960  destroy a slot range, returning dest advanced
// ===========================================================================
int FUN_009a1960(SlotObj* first, SlotObj* last, int dest) {
  if (first != last) {
    do {
      first->mState = 0;
      first->mV0 = 0.0f; first->mV1 = 0.0f; first->mV2 = 0.0f;
      first->mV3 = 0.0f; first->mV4 = 0.0f; first->mV5 = 0.0f;
      first->mV6 = g_one;
      int* lastp = first->mList.mpEnd;
      int* firstp = first->mList.mpBegin;
      memcpy(firstp, lastp, (char*)first->mList.mpEnd - (char*)lastp);
      first->mList.mpEnd = first->mList.mpEnd - (lastp - firstp);
      int* p = first->mList.mpBegin;
      if (p != 0 && p[-1] != 0) operator_delete(p);
      dest += 0x1f0;
      ++first;
    } while (first != last);
  }
  return dest;
}

// ===========================================================================
// @ 0x009a1ad0  clear active flag and the time list, then notify
// ===========================================================================
extern "C" void FUN_009a80e0(void* obj);
void FUN_009a1ad0(char* obj) {
  obj[0xac] = 0;
  ((Vec8b*)(obj + 0xc8))->resize(0);
  FUN_009a80e0(obj);
}

// ===========================================================================
// @ 0x009a1b00  destroy a slot range
// ===========================================================================
void FUN_009a1b00(SlotObj* first, SlotObj* last) {
  if (first < last) {
    do {
      first->mState = 0;
      first->mV0 = 0.0f; first->mV1 = 0.0f; first->mV2 = 0.0f;
      first->mV3 = 0.0f; first->mV4 = 0.0f; first->mV5 = 0.0f;
      first->mV6 = g_one;
      int* lastp = first->mList.mpEnd;
      int* firstp = first->mList.mpBegin;
      memcpy(firstp, lastp, (char*)first->mList.mpEnd - (char*)lastp);
      first->mList.mpEnd = first->mList.mpEnd - (lastp - firstp);
      int* p = first->mList.mpBegin;
      if (p != 0 && p[-1] != 0) operator_delete(p);
      ++first;
    } while (first < last);
  }
}

// ===========================================================================
// @ 0x009a1c60  build the per-key variant lists
// ===========================================================================
extern "C" uint FUN_009b2340(void* buf, int mask, void* ctx, void* rec, void* p, int one);
struct IntVecI {
  int* mpBegin; int* mpEnd; int* mpCap;
  void insert(int* pos, uint n, const int* v);       // 0x00999dd0
  void erase(int* first, int* last) {
    memcpy(first, last, (char*)mpEnd - (char*)last);
    mpEnd = mpEnd - (last - first);
  }
};
bool __stdcall FUN_009a1c60(Gen* g, void* p2) {
  uint buf[0x100];
  uint i = 0;
  VariantEntry* ent = g->mEntries;
  do {
    if (g->mKeys[i].key != -1) {
      ent->mType = i;
      ent->mFlag = 0;
      ent->mFlag2 = g->mKeys[i].val;
      uint n = FUN_009b2340(buf, 0xff, g->mpCtx,
                            (char*)g->mpAnim->mpRecords[g->mKeys[i].key] + 0x8c, p2, 1);
      IntVecI* v = (IntVecI*)&ent->mpBegin;
      uint cur = (uint)(v->mpEnd - v->mpBegin);
      if (n > cur) {
        int z = 0;
        v->insert(v->mpEnd, n - cur, &z);
      } else {
        v->erase(v->mpBegin + n, v->mpEnd);
      }
      if (n == 0) {
        g->mNumEntries = g->mNumEntries - 1;
        if (ent->mFlag2 != 0) return false;
      } else {
        memcpy(v->mpBegin, buf, n * 4);
        ++ent;
      }
    }
    ++i;
  } while (i < 0x40);
  return true;
}
