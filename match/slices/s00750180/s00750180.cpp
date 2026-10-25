// Slice s00750180: cModelWorld occluder/preload helpers (~0x00750180-0x00750780).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"

// ---------------------------------------------------------------------------
// @ 0x00750780  SP::cModelWorld::AddOccluder
// ---------------------------------------------------------------------------
struct cOccluderInfo { int f0; int x, y, z; float r; };

struct SlotVector {
    cOccluderInfo* mBegin;   // +0x00
    char pad0[0x18];
    int create(void* out);   // 00750030
};

struct MW6 {
    char pad[0x2bc];
    SlotVector vec;          // +0x2bc
    void AddOccluder(int* src, float f);
};

void MW6::AddOccluder(int* src, float f)
{
    uint32_t tmp[4];
    int idx = vec.create(tmp);
    char* base = (char*)vec.mBegin;
    int off = idx * 0x14;
    *(int*)(base + off + 4) = src[0];
    *(int*)(base + off + 8) = src[1];
    *(int*)(base + off + 0xc) = src[2];
    *(float*)((char*)vec.mBegin + off + 0x10) = f;
}

// ---------------------------------------------------------------------------
// eastl::deque<Elem28, alloc, 8>::erase(const_iterator)
// Element size 0x1c, eight elements per 0xe0 subarray.
// ---------------------------------------------------------------------------
struct RC { virtual int AddRef(); virtual int Release(); };

struct Elem28 {
    int  f00;
    RC*  mpRef;                       // +0x04
    char pad08[0x14];                 // through +0x1b
    ~Elem28() { RC* p = mpRef; if (p) p->Release(); }
};

struct Flag { };

struct DequeIter {
    Elem28*  mpCurrent;
    Elem28*  mpBegin;
    Elem28*  mpEnd;
    Elem28** mpCurrentArrayPtr;

    struct Increment { };

    DequeIter(const DequeIter& x)
        : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd),
          mpCurrentArrayPtr(x.mpCurrentArrayPtr) { }
    DequeIter(const DequeIter& x, Increment);
    DequeIter&  operator+=(int n);                 // 0x00745710
    DequeIter   operator+(int n) const;
    void copy_backward(const DequeIter& first, const DequeIter& last, Flag);  // 0x0074f330
    DequeIter   copy(const DequeIter& first, const DequeIter& last, Flag);    // 0x0074f2c0
};

inline DequeIter::DequeIter(const DequeIter& x, Increment)
    : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd),
      mpCurrentArrayPtr(x.mpCurrentArrayPtr)
{
    if (++mpCurrent == mpEnd) {
        mpBegin   = *++mpCurrentArrayPtr;
        mpEnd     = mpBegin + 8;
        mpCurrent = mpBegin;
    }
}

inline DequeIter DequeIter::operator+(int n) const
{
    return DequeIter(*this).operator+=(n);
}

inline int operator-(const DequeIter& a, const DequeIter& b)
{
    return 8 * ((a.mpCurrentArrayPtr - b.mpCurrentArrayPtr) - 1)
         + (a.mpCurrent - a.mpBegin)
         + (b.mpEnd - b.mpCurrent);
}

typedef unsigned int size_type;

struct Deque {
    void*    mpPtrArray;
    int      mnPtrArraySize;
    DequeIter mItBegin;               // +0x08
    DequeIter mItEnd;                 // +0x18

    size_type size() const;
    void pop_front();
    void popFrontSlow();              // 0x007455e0
    void pop_back();                  // 0x00747920
    DequeIter erase(DequeIter position);
};

inline size_type Deque::size() const
{
    return (size_type)(mItEnd - mItBegin);
}

inline void Deque::pop_front()
{
    if ((mItBegin.mpCurrent + 1) != mItBegin.mpEnd) {
        Elem28* e = mItBegin.mpCurrent++;
        e->~Elem28();
    } else {
        popFrontSlow();
    }
}

// @ 0x00750180  Deque::erase
DequeIter Deque::erase(DequeIter position)
{
    DequeIter itNext(position, DequeIter::Increment());
    const int i = position - mItBegin;

    if (i < (int)(size() / 2))
    {
        Flag flag;
        itNext.copy_backward(mItBegin, position, flag);
        pop_front();
    }
    else
    {
        Flag flag;
        position.copy(itNext, mItEnd, flag);
        pop_back();
    }

    return mItBegin + i;
}

// ---------------------------------------------------------------------------
// 0x00750310: destructor of the cModelWorld sub-object at +0x118.
// Members (ascending): +0x24 Obj24 (out-of-line dtor), +0x38 intrusive list (inline dtor),
// +0x4c refcounted eastl vector (inline dtor), +0x60 Obj60 (out-of-line dtor).
// ---------------------------------------------------------------------------
extern "C" void EA_Free(void* p);                     // 0x00f47380
struct Obj24_50310 { int pad[5]; ~Obj24_50310(); };
struct Obj60_50310 { int pad[5]; ~Obj60_50310(); };

struct ListHead50310 { ListHead50310* mpNext; };
struct IntrusiveList50310 {
    ListHead50310 mHead;                              // +0x00
    uint8_t       pad[0x10];
    ~IntrusiveList50310()
    {
        ListHead50310* p = mHead.mpNext;
        while (p != &mHead) {
            ListHead50310* n = p;
            p = p->mpNext;
            EA_Free(n);
        }
    }
};

struct RefVec50310 {
    void*    mpBegin;                                 // +0x00
    void*    mpEnd;                                   // +0x04
    void*    mpCapacity;                              // +0x08
    uint32_t mAllocator[2];                           // +0x0c
    ~RefVec50310()
    {
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            EA_Free(mpBegin);
    }
};

struct Inner50310 {
    uint8_t            pad0[0x24];
    Obj24_50310        m24;                           // +0x24
    IntrusiveList50310 m38;                           // +0x38
    RefVec50310        m4c;                           // +0x4c
    Obj60_50310        m60;                           // +0x60
    ~Inner50310();
};

// @ 0x00750310
Inner50310::~Inner50310()
{
}

// ---------------------------------------------------------------------------
// cModelWorld: full teardown order and the model-preload banks.
// ---------------------------------------------------------------------------
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) { }

namespace SP {

class cMWModel;

class ModelRefCount {
 public:
  virtual int AddRef();
  virtual int Release();
};

class cMWModel {
 public:
  void*     mpWorld;      // +0x00
  uint32_t  mFlags;       // +0x04
  uint32_t  mPad08[14];
  int       mRefCount;    // +0x40
  void AddRef() { ++mRefCount; }
  void Release();
};

inline void cMWModel::Release() {
  if (mRefCount > 1) {
    --mRefCount;
  } else {
    ((void(__thiscall*)(void*, cMWModel*, bool))(*(void***)mpWorld)[0x170 / 4])
        (mpWorld, this, (mFlags >> 31) & 1);
  }
}

struct AutoRef {
  cMWModel* mpObject;
  AutoRef() : mpObject(0) {}
  AutoRef(cMWModel* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRef(const AutoRef& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRef() { if (mpObject) mpObject->Release(); }
  cMWModel* operator->() const { return mpObject; }
  operator cMWModel*() const { return mpObject; }
};

extern "C" AutoRef* eastl_copy_autoref(AutoRef* first, AutoRef* last, AutoRef* dest);  // 0x005f4e10

struct AutoRefVec {                  // 0x14 bytes
  AutoRef*  mpBegin;
  AutoRef*  mpEnd;
  AutoRef*  mpCapacity;
  uint32_t  mField0C;
  uint32_t  mField10;

  void DoDestroyValues(AutoRef* first, AutoRef* last);            // 0x005f3680
  void reserve(uint32_t n);                                        // 0x004e0880
  void DoInsertValue(AutoRef* pos, const AutoRef* value);          // 0x00423c40
  ~AutoRefVec();                                                   // 0x0041e640

  void erase(AutoRef* first, AutoRef* last) {
    AutoRef* position = eastl_copy_autoref(last, mpEnd, first);
    DoDestroyValues(position, mpEnd);
    mpEnd -= (last - first);
  }

  void push_back_model(cMWModel* model, const AutoRef& value) {
    if (mpEnd < mpCapacity) {
      AutoRef* slot = mpEnd++;
      if (slot) {
        slot->mpObject = model;
        model->AddRef();
      }
    } else {
      DoInsertValue(mpEnd, &value);
    }
  }
};

struct RefCountHeader { int mRefCount; };

struct RefVec {                      // 0x14 bytes
  void*    mpBegin;
  void*    mpEnd;
  void*    mpCapacity;
  uint32_t mAllocator[2];
  ~RefVec() {
    if (mpBegin && ((RefCountHeader*)mpBegin)[-1].mRefCount != 0)
      EA_Free(mpBegin);
  }
};

struct FreePtr {
  void* mpObject;
  ~FreePtr() { if (mpObject) EA_Free(mpObject); }
};

struct RefObject {
  virtual int AddRef();
  virtual int Release();
};

struct AutoRefMember {
  RefObject* mpObject;
  ~AutoRefMember() { if (mpObject) mpObject->Release(); }
};

struct Elem8 {
  void* mpObject;
  void* mpNext;
  ~Elem8();                          // 0x007445a0
};

struct IntrusiveList {
  void* mpNext;
  void* mpPrev;
  ~IntrusiveList();                  // 0x00620230
};

struct cLoadQueue {
  uint8_t mPad[0x2b4];
  ~cLoadQueue();                     // 0x0074b2b0
};

struct ModelRec {
  uint32_t mField00;
  uint32_t mField04;
  uint32_t mField08;
};

extern "C" bool LoadModelRecords(void* list, uint32_t group, uint32_t* count,
                                 ModelRec** records);  // 0x006a0ae0

// The five polymorphic base subobjects occupy +0x00..+0x13.
struct MWBase0 { virtual ~MWBase0() {} };
struct MWBase1 { virtual ~MWBase1() {} };
struct MWBase2 { virtual ~MWBase2() {} };
struct MWBase3 { virtual ~MWBase3() {} };
struct MWBase4 { virtual ~MWBase4() {} };

struct cModelWorld : MWBase0, MWBase1, MWBase2, MWBase3, MWBase4 {
  uint8_t       mPad14[0x118 - 0x14];
  Inner50310    mInner118;           // +0x118
  uint8_t       mPad18C[0x19c - 0x18c];
  IntrusiveList mList19C;            // +0x19c
  IntrusiveList mList1A4;            // +0x1a4
  IntrusiveList mList1AC;            // +0x1ac
  Elem8         mArray1B4[0x20];     // +0x1b4
  uint8_t       mPad2B4[0x2bc - 0x2b4];
  FreePtr       mPtr2BC;             // +0x2bc
  uint8_t       mPad2C0[0x2d8 - 0x2c0];
  RefVec        mVec2D8;             // +0x2d8
  RefVec        mVec2EC;             // +0x2ec
  RefVec        mVec300;             // +0x300
  cLoadQueue    mLoadQueue314;       // +0x314
  AutoRefMember mModel5C8;           // +0x5c8
  uint8_t       mPad5CC[0x5d0 - 0x5cc];
  AutoRefVec    mPreload5D0[0x10];   // +0x5d0
  AutoRefVec    mPreload710[0x10];   // +0x710
  uint8_t       mPad850[0x864 - 0x850];
  RefVec        mVec864;             // +0x864
  uint8_t       mPad878[0x880 - 0x878];
  AutoRefMember mModel880;           // +0x880
  uint8_t       mPad884[0xc];

  virtual ~cModelWorld();
  void PreloadModels(void* list, int index);
};

}  // namespace SP

// @ 0x007503A0  SP::cModelWorld::~cModelWorld
SP::cModelWorld::~cModelWorld()
{
}

// @ 0x007505A0  SP::cModelWorld::PreloadModels
void SP::cModelWorld::PreloadModels(void* list, int index)
{
  SP::AutoRefVec& vecs0 = mPreload5D0[index];
  SP::AutoRefVec& vecs1 = mPreload710[index];

  vecs0.erase(vecs0.mpBegin, vecs0.mpEnd);
  vecs1.erase(vecs1.mpBegin, vecs1.mpEnd);

  if (list == 0)
    return;

  uint32_t count;
  SP::ModelRec* recs;
  int i;
  if (!SP::LoadModelRecords(list, 0x49b48ee, &count, &recs))
    return;

  vecs0.reserve(count);
  vecs1.reserve(count);

  for (i = 0; i < (int)count; ++i) {
    SP::cMWModel* model =
        ((SP::cMWModel*(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))
         (*(void***)this)[0xc / 4])(this, recs[i].mField00, recs[i].mField08, 0x80000008);
    SP::AutoRef ref(model);
    if (model) {
      if ((model->mFlags >> 14) & 1)
        vecs1.push_back_model(model, ref);
      else
        vecs0.push_back_model(model, ref);
    }
  }
}
