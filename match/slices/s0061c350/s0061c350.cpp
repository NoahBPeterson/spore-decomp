// Slice s0061c350: SP::Pollen transaction base constructors, request/result helpers and
// eastl vector<string> insert helpers. Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "../s00622f20/s00622f20.h"
#include <intrin.h>

extern char gEmptyString[];   // 0x01667bac (re-declared here so the checker can map it)

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);

inline void* operator new(unsigned, void* p) { return p; }

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};

// fixed_vector<void*, 40> introduced at +0x30 of the transaction base
struct FixedPtrVector {
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  uint32_t pad[2];
  uint32_t mOverflow;
  void* mBuffer[40];
  FixedPtrVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 40), mOverflow(0) {}
  FixedPtrVector& operator=(const FixedPtrVector& x);  // 0x0061c070
};
class cFeedTransactionBase : public cITransaction {
 public:
  uint32_t mpFeed;         // +0x8
  uint32_t mFeedType;      // +0xc
  uint32_t mnIntParam;     // +0x10
  uint32_t mnCount;        // +0x14
  uint32_t mUnk18;         // +0x18
  string8 mStringParam;    // +0x1c
  uint32_t pad28[1];
  FixedPtrVector mAssets;  // +0x30
  uint8_t mFlag;           // +0xe8
  cFeedTransactionBase(uint32_t type, const FixedPtrVector& assets);
  virtual ~cFeedTransactionBase();
};
class cGetAssetFeedTransaction : public cFeedTransactionBase {
 public:
  cGetAssetFeedTransaction(const FixedPtrVector& assets);
  virtual ~cGetAssetFeedTransaction();
  bool HandleResult(int code, void* result, struct Deque* queue);
};
class cEditFeedTransaction : public cFeedTransactionBase {
 public:
  bool HandleResult(int code, void* result, struct Deque* queue);
};

// @ 0x0061c570
cFeedTransactionBase::cFeedTransactionBase(uint32_t type, const FixedPtrVector& assets)
    : mpFeed(0), mFeedType(type), mnIntParam(0), mnCount(0xffffffff), mUnk18(0) {
  mAssets = assets;
  mFlag = 0;
}

// @ 0x0061c5e0
cGetAssetFeedTransaction::cGetAssetFeedTransaction(const FixedPtrVector& assets)
    : cFeedTransactionBase(4, assets) {
  mFlag = 1;
}

// ---------------------------------------------------------------------------------------------
// Raw-offset helpers: the feed / transaction / metadata objects here are only partly recovered.
// ---------------------------------------------------------------------------------------------
#define VFN(o, off, R, args) ((R (__thiscall*)args)(*(void***)(o))[(off) / 4])
#define I(p, off) (*(int*)((char*)(p) + (off)))
#define U(p, off) (*(unsigned*)((char*)(p) + (off)))
#define PI(p, off) (*(void**)((char*)(p) + (off)))

struct Key3 { unsigned a; unsigned b; unsigned c; };   // 12-byte resource key (instance, type, group order as stored)
struct EStr3 { void* b; void* e; void* c; };           // eastl string begin/end/capacity (allocator word omitted)

// Pollen directory / cache / message-bus objects (offsets into the Pollen manager from FUN_0067cb30).
struct cAssetDirectory {
  bool GetLocalKey(unsigned a, unsigned b, Key3* out);        // 0x54e460
  void AddMapping(unsigned a, unsigned b, Key3* k);           // 0x54e250
  void FUN_0054e7b0(unsigned a, unsigned b, int flag);        // 0x54e7b0
  bool FUN_0054e740(unsigned a, unsigned b);                  // 0x54e740
  void FUN_0054e970(int tag, unsigned lo, unsigned hi);       // 0x54e970
};
struct cAssetCache {
  bool FUN_00613860(unsigned type);                           // 0x613860
  void AddAsset(unsigned a, unsigned b, void* variantMap);    // 0x614280
};
struct cPollenMgr {
  virtual void v0();
  virtual void Notify(unsigned id, void* data);               // +4
  char pad[0x50];
  cAssetDirectory* mpDirectory;                               // +0x58
  cAssetCache* mpCache;                                       // +0x5c
};
cPollenMgr* GetPollenMgr();                                   // 0x67cb30
struct IMessageServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                        virtual void Post(unsigned id, void* data, int flag); };   // +0x14
IMessageServer* GetMessageServer();                           // 0x67dcc0 / EA::Messaging::GetServer 0x883860
void* GetResourceManager();                                   // 0x67dcd0
void* GetSaveArea(unsigned id);                               // 0x6b1f90
void* IDGenerator();                                          // 0x67de60
void operator_delete_arr(void* p);                            // 0xf47380

struct Deque { void Push(void* tx, int addref); };            // 0x60eaf0 deque<TransactionPtr,64>::PushSlow

// Feed description (0x70 bytes): DateTime at +0, destructor 0x547840, ctor 0x546630.
struct FeedDescription {
  unsigned lo, hi;
  uint32_t pad[0x19];
  int tail;
  FeedDescription();    // 0x546630
  ~FeedDescription();   // 0x547840
};
void FillFeedInfo(void* feed, FeedDescription* out);          // 0x618c70, cdecl
struct DateTimeLike { void Set(int now); };                   // 0x92e3d0

// ---------------------------------------------------------------------------------------------
// @ 0x0061c350  (transaction result handler: register the local assets of the matching feed entry)
// ---------------------------------------------------------------------------------------------
struct FeedEvent {
  virtual void v0();
  virtual void Release();
  int refcount;
  int* mOwner;
  int mIndex;
  unsigned mKey;
  Key3 mLocal;
  int mZero;
  FeedEvent(int* owner, int index, unsigned key, const Key3& local)
      : refcount(0), mOwner(owner), mIndex(index), mKey(key), mLocal(local), mZero(0) {
    if (mOwner) mOwner[1]++;
  }
};
extern void* gFeedEventPoolHead;   // 0x15f5264, free list head of the pool at 0x15f5254
struct FeedEventPoolT { bool AddCore(int, int); };   // 0x00926650 EA::Allocator::FixedAllocatorBase::AddCore (thiscall)
extern FeedEventPoolT gFeedEventPool;   // 0x015f5254

unsigned* LowerBound(unsigned* b, unsigned* e, const unsigned* key, char flag);   // 0x555a20 cdecl
struct SortedUIntVec {
  unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity;
  void Insert(unsigned* pos, const unsigned* v);   // 0x5481d0
};

struct cAssetFeedTransaction {
  bool HandleResult(int code, void* result, Deque* queue);
};

// @ 0x0061c350
bool cAssetFeedTransaction::HandleResult(int code, void* result, Deque* queue) {
  if (result) {
    void* o = PI(result, 0xf3c);
    if (o) VFN(o, 0x18, void, (void*))(o);
  }
  if (code != 0) return false;
  cAssetDirectory* dir = GetPollenMgr()->mpDirectory;
  char* feed = (char*)PI(this, 8);
  char* e = (char*)PI(feed, 0x60);
  char* end = (char*)PI(feed, 0x64);
  for (; e != end; e += 0x118) {
    unsigned ka = U(e, 0x10), kb = U(e, 0x14);
    Key3 local = { 0, 0, 0 };
    if (ka == U(this, 0xf0) && kb == U(this, 0xf4) && dir && dir->GetLocalKey(ka, kb, &local)) {
      unsigned* a = (unsigned*)PI(e, 0x8c);
      unsigned* aend = (unsigned*)PI(e, 0x90);
      for (; a != aend; a += 5) {
        unsigned key = *a;
        FeedEvent* ev;
        for (;;) {
          void** h = (void**)gFeedEventPoolHead;
          if (h) {
            gFeedEventPoolHead = *h;
            ev = (FeedEvent*)h;
            if (ev) {
              new (ev) FeedEvent((int*)PI(this, 8), (int)((e - (char*)PI(feed, 0x60)) / 0x118), key, local);
            }
            break;
          }
          if (!gFeedEventPool.AddCore(0, 0)) { ev = 0; break; }
        }
        queue->Push(ev, 1);
        unsigned* vb = (unsigned*)PI(this, 0xf8);
        unsigned* ve = (unsigned*)PI(this, 0xfc);
        unsigned* it = LowerBound(vb, ve, &key, *(char*)((char*)this + 0x10c));
        if (it == ve) {
          if (ve == (unsigned*)PI(this, 0x100)) {
            ((SortedUIntVec*)((char*)this + 0xf8))->Insert(it, &key);
          } else {
            PI(this, 0xfc) = ve + 1;
            if (ve) *ve = key;
          }
        } else if (key < *it) {
          ((SortedUIntVec*)((char*)this + 0xf8))->Insert(it, &key);
        }
      }
      return true;
    }
  }
  return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0061c610 / 0x0061c760  (eastl::vector<FeedDescription>::DoAssign, reversed / forward range)
// ---------------------------------------------------------------------------------------------
struct FDVec {
  FeedDescription* mpBegin;
  FeedDescription* mpEnd;
  FeedDescription* mpCapacity;
  FeedDescription* AllocCopyBackward(unsigned n, FeedDescription* a, FeedDescription* b);   // 0x61c1c0
  FeedDescription* AllocCopy(unsigned n, FeedDescription* a, FeedDescription* b);           // 0x61c220
  void DestructRange(FeedDescription* newEnd, FeedDescription* oldEnd);                      // 0x60e910
  // third argument: the iterator-tag slot (ignored, but it makes both ret 0xc)
  void AssignBackward(FeedDescription* last, FeedDescription* first, int tag);
  void Assign(FeedDescription* first, FeedDescription* last, int tag);
};
FeedDescription* CopyBackward(FeedDescription* last, FeedDescription* first, FeedDescription* destEnd);   // 0x619650
void UninitializedCopyBackward(FeedDescription** out, FeedDescription* a, FeedDescription* b, FeedDescription* c, FeedDescription* d);  // 0x6195d0
FeedDescription* Copy(FeedDescription* first, FeedDescription* last, FeedDescription* dest);              // 0x60ee50
void UninitializedCopy(FeedDescription** out, FeedDescription* a, FeedDescription* b, FeedDescription* c, FeedDescription* d);        // 0x619610

static __forceinline void DestroyAndFree(FDVec* v) {
  FeedDescription* b = v->mpBegin;
  FeedDescription* e = v->mpEnd;
  for (; b < e; ++b) b->~FeedDescription();
  void* p = v->mpBegin;
  if (p && ((int*)p)[-1]) operator_delete_arr(p);
}

// @ 0x0061c610
void FDVec::AssignBackward(FeedDescription* last, FeedDescription* first, int) {
  unsigned n = (unsigned)(last - first);
  if (n > (unsigned)(mpCapacity - mpBegin)) {
    FeedDescription* nb = AllocCopyBackward(n, last, first);
    DestroyAndFree(this);
    mpBegin = nb;
    mpEnd = nb + n;
    mpCapacity = nb + n;
    return;
  }
  unsigned sz = (unsigned)(mpEnd - mpBegin);
  if (n <= sz) {
    FeedDescription* ne = CopyBackward(last, first, mpBegin);
    DestructRange(ne, mpEnd);
    mpEnd = ne;
    return;
  }
  FeedDescription* mid = last - sz;
  CopyBackward(last, mid, mpBegin);
  FeedDescription* res;
  UninitializedCopyBackward(&res, mid, first, mpEnd, first);
  mpEnd = res;
}

// @ 0x0061c760
void FDVec::Assign(FeedDescription* first, FeedDescription* last, int) {
  unsigned n = (unsigned)(last - first);
  if (n > (unsigned)(mpCapacity - mpBegin)) {
    FeedDescription* nb = AllocCopy(n, first, last);
    DestroyAndFree(this);
    mpEnd = nb + n;
    mpCapacity = nb + n;
    mpBegin = nb;
    return;
  }
  unsigned sz = (unsigned)(mpEnd - mpBegin);
  if (n <= sz) {
    FeedDescription* ne = Copy(first, last, mpBegin);
    DestructRange(ne, mpEnd);
    mpEnd = ne;
    return;
  }
  FeedDescription* mid = first + sz;
  Copy(first, mid, mpBegin);
  FeedDescription* res;
  UninitializedCopy(&res, mid, last, mpEnd, last);
  mpEnd = res;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0061c880  RequestAssetsFromFeed(feed, maxCount, queue, flag)
// ---------------------------------------------------------------------------------------------
struct cAssetMetadata {
  cAssetMetadata();                                                    // 0x550450
  virtual void AddRef();
  virtual void Release();
  bool UpdateFromEntry(void* entry, void* feedInfo);                   // 0x551ba0
  bool GetCreatureName(Key3* out, void* entry, void* feedInfo);        // 0x550da0
  unsigned* GetKeyPair();                                              // 0x5507a0
  int FUN_005508e0();                                                  // 0x5508e0
};
struct IDGen { virtual void v0(); virtual void Register(Key3* key, void* data, void* extra); };  // +4
struct VariantMapVec {   // fixed vector<EA::Variant,N> on the stack (0x18-byte elements, begin at +4)
  char* mpBegin; char* mpEnd; char* mpCapacity; char* mpFixed; char* mpFixedEnd; char buf[0xf0];
  void* Index(unsigned* hash);                                         // 0x613d20 (vector_map operator[])
};
struct Variant { Variant& operator=(const Variant& o); };              // 0x542b80
void VariantDestruct(void* v, int flag);                               // EA::Variant::Destruct 0x93db80, thiscall
unsigned FNV1_String16(const wchar_t* s, unsigned seed, int flag);     // 0x932f30 cdecl
unsigned FNV1_String8(const char* s, unsigned seed, int flag);         // 0x932e80 cdecl
void SortFeedIndices(unsigned* b, unsigned* e, void* feed);            // 0x61c140
struct IndexVec { unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity; void Resize(unsigned n); };   // 0x4cd3c0
bool SetAssetData(void* list, int a);                                  // 0x4bbe20 (cSPAssetDataList::SetAssetData)
unsigned FUN_004bbc70(void* list, int a, int b, int c, int d);
void FUN_006ac0a0(int type, void* obj);
void FUN_006ad010(void* obj);
void FUN_00616d60(void* obj, void* sa, int flag);
void* AllocTx28(unsigned size);                                        // 0x615a00
void* AllocTx24(unsigned size);                                        // 0x6159d0
struct TxA { TxA* Init(Key3 key, cAssetMetadata* md, void* feed, void* entry, int flag); };   // 0x6163e0 (thiscall, key by value)
struct TxB { TxB* Init(Key3* key, void* feed, void* entry); };         // 0x616300
void WStr_Format(void* wstr, const wchar_t* fmt, ...);                 // 0x41e050 cdecl
extern wchar_t gEmptyWide[];   // 0x01667bac (shared empty string)

unsigned RequestAssetsFromFeed(void* feed, unsigned maxCount, Deque* queue, char flag) {
  unsigned count = 0;
  cPollenMgr* mgr = GetPollenMgr();
  cAssetDirectory* dir = mgr->mpDirectory;
  if (PI(feed, 0x60) == PI(feed, 0x64)) return 0;
  char notifyDone = *(char*)((char*)feed + 0x74);
  GetSaveArea(0x11ac19d);
  GetResourceManager();
  IndexVec idx = { 0, 0, 0 };
  idx.Resize((unsigned)(((char*)PI(feed, 0x64) - (char*)PI(feed, 0x60)) / 0x118));
  unsigned* ib = idx.mpBegin;
  unsigned n = (unsigned)(idx.mpEnd - idx.mpBegin);
  for (unsigned i = 0; i < n; i++) ib[i] = i;
  SortFeedIndices(idx.mpBegin, idx.mpEnd, feed);
  unsigned* ip = ib;
  if (ip != idx.mpEnd) {
    do {
      if (maxCount <= count) break;
      unsigned entryIdx = *ip;
      char* entry = (char*)PI(feed, 0x60) + entryIdx * 0x118;
      unsigned ka = U(entry, 0x10), kb = U(entry, 0x14);
      if ((ka != 0 || kb != 0) && (ka & kb) != 0xffffffff) {
        Key3 local = { 0, 0, 0 };
        bool found = dir->GetLocalKey(ka, kb, &local);
        if (!found) {
          if (!flag) {
            cAssetMetadata* md = new("Pollinator", 0, 0, 0, 0) cAssetMetadata();
            if (md) md->AddRef();
            bool ok = SetAssetData(PI(entry, 0xc8), 0);
            IDGen* gen = *(IDGen**)IDGenerator();
            unsigned x = FUN_004bbc70(PI(entry, 0xc8), 1, 0, ok ? 0x62 : 0, 0);
            ((IDGen*)gen)->Register(&local, PI(entry, 0xc8), (void*)x);
            local.b = (unsigned)I(entry, 0xc8);
            struct { wchar_t* b; wchar_t* e; wchar_t* c; } ws = { gEmptyWide, gEmptyWide, gEmptyWide + 1 };
            WStr_Format(&ws, L"%s(%llu)", PI(entry, 0x18), ka, kb);
            Key3 saved = local;
            if (md->GetCreatureName(&local, entry, (char*)feed + 8)) {
              U(md, 8) = saved.a;
              U(md, 0xc) = 0x30bdee3;
              U(md, 0x10) = saved.c;
              unsigned* kp = md->GetKeyPair();
              dir->AddMapping(kp[0], kp[1], &local);
              kp = md->GetKeyPair();
              dir->FUN_0054e7b0(kp[0], kp[1], 1);
              if (ok) {
                TxA* t = (TxA*)AllocTx28(0x28);
                Deque* q = queue;
                void* r = t ? t->Init(local, md, feed, (void*)entryIdx, 0) : 0;
                q->Push(r, 1);
                TxB* t2 = (TxB*)AllocTx24(0x24);
                void* r2 = t2 ? t2->Init(&local, feed, (void*)entryIdx) : 0;
                q->Push(r2, 1);
              } else if (local.b == 0x366a930d) {
                TxA* t = (TxA*)AllocTx28(0x28);
                void* r = t ? t->Init(local, md, feed, (void*)entryIdx, 1) : 0;
                queue->Push(r, 1);
              }
              count++;
            }
            if (((char*)ws.c - (char*)ws.b & ~1) > 2 && ws.b) operator_delete_arr(ws.b);
            if (md) md->Release();
          }
        } else if (!flag) {
          Key3 k = { local.a, 0x30bdee3, local.c };
          void* obj = 0;
          void* rm = GetResourceManager();
          if (obj) { void* o = obj; obj = 0; VFN(o, 4, void, (void*))(o); }
          if (VFN(rm, 0xc, bool, (void*, Key3*, void**, int, int, int, int))(rm, &k, &obj, 0, 0, 0, 0)) {
            cAssetMetadata* md2 = obj ? (cAssetMetadata*)VFN(obj, 0xc, void*, (void*, unsigned))(obj, 0x30bdee3) : 0;
            int before = md2->FUN_005508e0();
            if (md2->UpdateFromEntry(entry, (char*)feed + 8)) {
              U(obj, 8) = k.a;
              U(obj, 0xc) = k.b;
              U(obj, 0x10) = k.c;
              void* sa = GetSaveArea(0x11ac19d);
              FUN_006ac0a0(10, obj);
              FUN_006ad010(obj);
              FUN_00616d60(obj, sa, 0);
              unsigned* kp = md2->GetKeyPair();
              if (!dir->FUN_0054e740(kp[0], kp[1]) && before != md2->FUN_005508e0()) {
                struct { unsigned hash; int one; Key3 key; } msg;
                msg.hash = FNV1_String8(*(const char**)((char*)feed + 8), 0x811c9dc5, 0);
                msg.one = 1;
                msg.key = local;
                GetMessageServer()->Post(0x64e331c, &msg, 0);
              }
            }
          }
          if (obj) VFN(obj, 4, void, (void*))(obj);
        }
        if (local.a != 0) {
          GetPollenMgr();
          if (GetPollenMgr()->mpCache->FUN_00613860(local.b)) {
            VariantMapVec vv;
            vv.mpBegin = vv.mpEnd = vv.buf;
            vv.mpFixed = vv.buf; vv.mpFixedEnd = vv.buf + sizeof(vv.buf); vv.mpCapacity = vv.buf + sizeof(vv.buf);
            char* ap = (char*)PI(entry, 0x78);
            while (ap != (char*)PI(entry, 0x7c)) {
              unsigned h = FNV1_String16(*(const wchar_t**)ap, 0x811c9dc5, 1);
              Variant* v = (Variant*)vv.Index(&h);
              *v = *(Variant*)(ap + 0x20);
              ap += 0x34;
            }
            GetPollenMgr()->mpCache->AddAsset(ka, kb, &vv);
            for (char* vp = vv.mpBegin + 4; vp < vv.mpEnd; vp += 0x18) {
              if (*(unsigned char*)(vp + 0x10) & 4) VariantDestruct(vp, 0);
            }
            if (vv.mpBegin && vv.mpBegin != vv.mpFixed) operator_delete_arr(vv.mpBegin);
          }
        }
      }
      ip++;
    } while (ip != idx.mpEnd);
  } else {
    count = 0;
  }
  if (notifyDone && count) {
    struct { unsigned count; int a; int b; } msg;
    msg.count = count;
    msg.a = I(feed, 0x1c);
    msg.b = (PI(feed, 0x78) == PI(feed, 0x7c)) ? 0 : I(feed, 0x78);
    GetMessageServer()->Post(0x7bd0aaa, &msg, 0);
  }
  if (idx.mpBegin && ((int*)idx.mpBegin)[-1]) operator_delete_arr(idx.mpBegin);
  return count;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0061cf60  cGetAssetFeedTransaction::HandleResult
// ---------------------------------------------------------------------------------------------
struct TxC { TxC* Init(int a, unsigned b, unsigned c, void* d); };      // 0x618d40
void* AllocTxF0(unsigned size);                                        // 0x6158b0

bool cGetAssetFeedTransaction::HandleResult(int code, void* result, Deque* queue) {
  if (result) {
    void* o = PI(result, 0xf3c);
    if (o) VFN(o, 0x18, void, (void*))(o);
  }
  GetPollenMgr();
  bool ret = false;
  if (code != 0) {
    if (mFeedType == 1) GetMessageServer()->Post(0x3d1cd0b, 0, 0);
    return ret;
  }
  {
    FeedDescription desc;
    FillFeedInfo((void*)mpFeed, &desc);
    if (mFeedType == 1) {
      GetPollenMgr()->Notify(0x3d1cd0b, &desc);
      GetMessageServer()->Post(0x3d1cd0b, &desc, 0);
    }
    unsigned want = 0xffffffff;
    if (mFeedType == 0) want = mnCount;
    unsigned got = RequestAssetsFromFeed((void*)mpFeed, want, queue, mFlag);
    ((DateTimeLike*)&desc)->Set(1);
    GetPollenMgr()->mpDirectory->FUN_0054e970(desc.tail, desc.lo, desc.hi);
    if (mFeedType == 0 && got < mnCount && PI((void*)mpFeed, 0x60) != PI((void*)mpFeed, 0x64)) {
      TxC* t = (TxC*)AllocTxF0(0xf0);
      void* r = t ? t->Init(0, mnIntParam, mnCount - got, (void*)(mUnk18 + 1)) : 0;
      queue->Push(r, 0);
    }
    ret = true;
  }
  return ret;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0061d0d0  cEditFeedTransaction::HandleResult
// ---------------------------------------------------------------------------------------------
void RemoveFeedFromAll(void* a, void* b);                              // 0x6175c0 cdecl

bool cEditFeedTransaction::HandleResult(int code, void* result, Deque* queue) {
  if (result) {
    void* o = PI(result, 0xf3c);
    if (o) VFN(o, 0x18, void, (void*))(o);
  }
  GetPollenMgr();
  bool ret = false;
  if (code == 0) {
    FeedDescription desc;
    FillFeedInfo((void*)mpFeed, &desc);
    if (mFeedType == 0) {
      GetPollenMgr()->Notify(0x3cdd5f9, &desc);
      GetMessageServer()->Post(0x3cdd5f9, &desc, 0);
    }
    if (mFeedType == 1) {
      GetMessageServer()->Post(0x49a3777, &desc, 0);
      if (PI(this, 0x5c))
        RemoveFeedFromAll((char*)this + 0x50, (char*)this + 0x10);
    }
    RequestAssetsFromFeed((void*)mpFeed, 0xffffffff, queue, 0);
    ret = true;
  }
  return ret;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0061d1c0  (ctor of the 0x13fc88c transaction: empty eastl strings + zeroed members)
// ---------------------------------------------------------------------------------------------
class cFeedStateTransaction : public cITransaction {
 public:
  string8 mS8;            // +0x08
  uint32_t pad18;
  string16 mS1c;          // +0x1c
  string16 mS2c;          // +0x2c
  uint32_t pad3c;
  uint32_t m40, m44, m48, m4c;
  string8 mS50;           // +0x50
  uint32_t mV60, mV64, mV68;
  uint32_t pad6c, pad70;
  uint8_t m74;
  string16 mS78;          // +0x78
  cFeedStateTransaction();
  virtual ~cFeedStateTransaction();
};
cFeedStateTransaction::cFeedStateTransaction()
    : m40(0), m44(0), m48(0xffffffff), m4c(0), mV60(0), mV64(0), mV68(0), m74(0) {}
}  // namespace Pollen
}  // namespace SP
