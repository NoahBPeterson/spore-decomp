// SP::cSPEditorManipulationSpine / SP::cSPEditorManipulationSpineResize (Spore creature editor)
// plus the eastl::sort helpers instantiated for float*.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (+ /fp:fast where noted in the manifest).
#include <new>
#include <math.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int debugFlags, const char* file, int line);

#define PV(n) virtual void pv##n();

namespace rw { namespace math { namespace fpu {
template <typename T, int N>
class Vector3Template {
 public:
  T x, y, z;
  Vector3Template() {}
  Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
template <typename T, int N>
inline Vector3Template<T, N> operator+(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return Vector3Template<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
template <typename T, int N>
inline Vector3Template<T, N> operator-(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return Vector3Template<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
template <typename T, int N>
inline Vector3Template<T, N> operator*(const Vector3Template<T, N>& a, T s) {
  return Vector3Template<T, N>(a.x * s, a.y * s, a.z * s);
}
template <typename T, int N>
inline T Dot(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
}}}  // namespace rw::math::fpu

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
  typedef rw::math::fpu::Vector3Template<float, 0> base;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
  float Dot(const cSPVector3& o) const { return x * o.x + y * o.y + z * o.z; }
};

struct cSPMatrix3 { float m[9]; };

// eastl::bitset<54>
struct eastl_bitset54 {
  uint32_t mWord[2];
  bool test(unsigned int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};
enum { kBlockFlagHidden = 7, kBlockFlagSkinPart = 11 };  // bit meanings guessed

namespace SP {

class cViewer {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& direction);
};

class cSPApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer* GetViewer();
};
cSPApp* App();

// intrusive refcount at +4 (vtable) / +8 (count) inside cSPEditorModel
class RefCountedBase {
 public:
  virtual ~RefCountedBase();
  volatile int mRefCount;
  void AddRef() { ++mRefCount; }
  int Release() {
    const int rc = --mRefCount;
    if (rc == 0) {
      mRefCount = 1;
      delete this;
    }
    return rc;
  }
};

class cSPEditorModelBase { public: PV(0) };
class cSPEditorModel : public cSPEditorModelBase, public RefCountedBase {
 public:
  void SetUsingSymmetry(bool b);     // FUN_004adc20
  bool IsUsingSymmetry();            // FUN_004adc40
  void SetDirty(bool b);             // FUN_004adfc0
};

class cSPEditorBlock {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x28 - 4];
  cSPEditorModel* mEditorModel;  // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3 mPosition;          // +0x48
  char pad54[0x340 - 0x54];
  cSPEditorBlock** mChildrenBegin;  // +0x340
  cSPEditorBlock** mChildrenEnd;    // +0x344
  char pad348[0xdc8 - 0x348];
  eastl_bitset54 mFlags;            // +0xdc8 (eastl::bitset<54>)
  void SetHighlight(int color, int a, int b, int c);  // FUN_0043a5e0
};

class cSPEditorBlockLink;
class cSPEditorSkinPart;
class cSPEditorSkinManager {
 public:
  virtual void AddRef();
  virtual void Release();
  struct Pinner { void Pin(cSPEditorBlock* b); /* FUN_00438700 */ };
  bool Raycast(int a, cSPVector3 origin, cSPVector3 dir, cSPVector3* hitPos, cSPVector3* hitNormal, int b, int c);  // FUN_004c4a30
  Pinner* GetPinner(int a, cSPVector3 pos);                                                                          // FUN_004c4d30
};
class cSPEditorAppEconomy;
class cSPEditorLimbStructure { public: void Rebuild(); /* FUN_0048a4c0 */ };

class cSPEditorSpinePart {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual void SetState(int a, int b);  // +0x30
};

class cSPEditorSpine {
 public:
  void MoveBlock(cSPEditorBlock* block, cSPVector3 origin, cSPVector3 dir);   // FUN_005d3010
  void StartDrag(cSPEditorBlock** block, cSPVector3 origin, cSPVector3 dir);  // FUN_005d43d0
  void Drag(cSPEditorBlock** block, cSPVector3 origin, cSPVector3 dir);       // FUN_005d4630
  void Rebuild(bool a, bool b);                                              // FUN_005d1600
  cSPEditorSpinePart* GetPart(cSPEditorBlock* block);                        // FUN_005ce270
  cSPEditorBlock* GetFrontNext();                                            // FUN_005ce250
  cSPEditorBlock* GetBackNext();                                             // FUN_005ce260
  char pad[0xe8];
  cSPEditorBlock* mFrontBlock;  // +0xe8
  cSPEditorBlock* mBackBlock;   // +0xec
};

class cSPEditorAnimatedEventInfo {
 public:
  cSPEditorAnimatedEventInfo();
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  void MessagePost(uint32_t id, cSPEditorBlock* block, cSPEditorModel* model, int a, int b, float c, int d, int e, float f);
  char pad[0x30 - 4];
};

class cSPEditorSkinPart {
 public:
  char pad[0xbc];
  struct Ref {
    virtual void AddRef();
    virtual void Release();
  } mRef;  // +0xbc
  void SetHighlight(bool on);  // FUN_004cca40
};

namespace EditorUtils {
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 pos, cSPMatrix3 orient, int flag);
void UnpinBlock(cSPEditorBlock* block, int flag);  // FUN_0049fee0
}

}  // namespace SP

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

template <>
class AutoRefCount<SP::cSPEditorSkinPart> {
 public:
  SP::cSPEditorSkinPart* mpObject;
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->mRef.AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->mRef.Release(); }
};
}  // namespace EA

namespace eastl {

// ---------------------------------------------------------------- sort helpers (float*)
template <typename RandomAccessIterator, typename Distance, typename T>
inline void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, const T& value) {
  for (Distance parentPosition = (position - 1) >> 1; (position > topPosition) && (*(first + parentPosition) < value);
       parentPosition = (position - 1) >> 1) {
    *(first + position) = *(first + parentPosition);
    position = parentPosition;
  }
  *(first + position) = value;
}

// @ 0x005B7AF0  eastl::adjust_heap<float*, int, float>
template <typename RandomAccessIterator, typename Distance, typename T>
void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value) {
  Distance childPosition = (2 * position) + 2;
  for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
    if (*(first + childPosition) < *(first + (childPosition - 1)))
      --childPosition;
    *(first + position) = *(first + childPosition);
    position = childPosition;
  }
  if (childPosition == heapSize) {
    *(first + position) = *(first + (childPosition - 1));
    position = childPosition - 1;
  }
  eastl::promote_heap<RandomAccessIterator, Distance, T>(first, topPosition, position, value);
}

// @ 0x005B81A0  eastl::make_heap<float*>
template <typename RandomAccessIterator>
void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
  const int heapSize = (int)(last - first);
  if (heapSize >= 2) {
    int parentPosition = ((heapSize - 2) >> 1) + 1;
    do {
      --parentPosition;
      const float temp(*(first + parentPosition));
      eastl::adjust_heap<RandomAccessIterator, int, float>(first, parentPosition, heapSize, parentPosition, temp);
    } while (parentPosition != 0);
  }
}

template <typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
  const float tempBottom(*(last - 1));
  *(last - 1) = *first;
  eastl::adjust_heap<RandomAccessIterator, int, float>(first, (int)0, (int)(last - first - 1), 0, tempBottom);
}

// @ 0x005B81E0  eastl::sort_heap<float*>
template <typename RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
  for (; (last - first) > 1; --last)
    eastl::pop_heap<RandomAccessIterator>(first, last);
}

// @ 0x005B82A0  eastl::partial_sort<float*>
template <typename RandomAccessIterator>
void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last) {
  eastl::make_heap<RandomAccessIterator>(first, middle);
  for (RandomAccessIterator i = middle; i < last; ++i) {
    if (*i < *first) {
      const float temp(*i);
      *i = *first;
      eastl::adjust_heap<RandomAccessIterator, int, float>(first, int(0), int(middle - first), int(0), temp);
    }
  }
  eastl::sort_heap<RandomAccessIterator>(first, middle);
}

template <typename T>
inline const T& median(const T& a, const T& b, const T& c) {
  if (a < b) {
    if (b < c)
      return b;
    else if (a < c)
      return c;
    else
      return a;
  } else if (a < c)
    return a;
  else if (b < c)
    return c;
  return b;
}

template <typename RandomAccessIterator, typename T>
inline RandomAccessIterator get_partition(RandomAccessIterator first, RandomAccessIterator last, T pivotValue) {
  const T pivotCopy(pivotValue);
  for (;; ++first) {
    while (*first < pivotCopy)
      ++first;
    --last;
    while (pivotCopy < *last)
      --last;
    if (first >= last)
      return first;
    const T temp(*first);
    *first = *last;
    *last = temp;
  }
}

// @ 0x005B7880  eastl::insertion_sort<float*>
template <typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
  if (first != last) {
    for (RandomAccessIterator i = first + 1; i != last; ++i) {
      const float value(*i);
      RandomAccessIterator ins(i), insPrev(i);
      for (--insPrev; (ins != first) && (value < *insPrev); --ins, --insPrev)
        *ins = *insPrev;
      *ins = value;
    }
  }
}

// @ 0x005B78D0  eastl::insertion_sort_simple<float*>
template <typename RandomAccessIterator>
void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last) {
  for (RandomAccessIterator current = first; current != last; ++current) {
    const float value(*current);
    RandomAccessIterator end(current), prev(current);
    for (--prev; value < *prev; --end, --prev)
      *end = *prev;
    *end = value;
  }
}

static const int kQuickSortLimit = 28;

// @ 0x005B8410  eastl::quick_sort_impl<float*, int>
template <typename RandomAccessIterator, typename Size>
void quick_sort_impl(RandomAccessIterator first, RandomAccessIterator last, Size kRecursionCount) {
  while (((last - first) > kQuickSortLimit) && (kRecursionCount > 0)) {
    const RandomAccessIterator position(
        eastl::get_partition(first, last, eastl::median(*first, *(first + (last - first) / 2), *(last - 1))));
    eastl::quick_sort_impl<RandomAccessIterator, Size>(position, last, --kRecursionCount);
    last = position;
  }
  if (kRecursionCount == 0)
    eastl::partial_sort<RandomAccessIterator>(first, last, last);
}

template <typename Size>
inline Size Log2(Size n) {
  int i;
  for (i = 0; n; ++i)
    n >>= 1;
  return i - 1;
}

// @ 0x005B8560  eastl::quick_sort<float*>
template <typename RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last) {
  if (first != last) {
    eastl::quick_sort_impl<RandomAccessIterator, int>(first, last, 2 * Log2((int)(last - first)));
    if ((last - first) > (int)kQuickSortLimit) {
      eastl::insertion_sort<RandomAccessIterator>(first, first + kQuickSortLimit);
      eastl::insertion_sort_simple<RandomAccessIterator>(first + kQuickSortLimit, last);
    } else
      eastl::insertion_sort<RandomAccessIterator>(first, last);
  }
}

template void quick_sort<float*>(float*, float*);

// ---------------------------------------------------------------- rbtree (map<cSPEditorBlock*, AutoRefCount<cSPEditorSkinPart>>)
struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);
void RBTreeInsert(rbtree_node_base* pNode, rbtree_node_base* pNodeParent, rbtree_node_base* pNodeAnchor, int insertionSide);

template <typename K, typename V>
struct pair {
  K first;
  V second;
};

typedef pair<SP::cSPEditorBlock* const, EA::AutoRefCount<SP::cSPEditorSkinPart> > BlockLimbPair;

struct rbtree_node : public rbtree_node_base {
  BlockLimbPair mValue;
};

struct rbtree_iterator {
  rbtree_node* mpNode;
  rbtree_iterator(rbtree_node* p) : mpNode(p) {}
};

class allocator {
 public:
  const char* mpName;
};

class BlockLimbMap {
 public:
  int mCompare;                // empty less<> padded
  rbtree_node_base mAnchor;    // +4
  unsigned int mnSize;         // +0x14
  allocator mAllocator;        // +0x18

  ~BlockLimbMap() { DoNukeSubtree((rbtree_node*)mAnchor.mpNodeParent); }

  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear();

  rbtree_node* DoCreateNode(const BlockLimbPair& value) {
    rbtree_node* const pNode = (rbtree_node*)EASTL_allocator_allocate(
        sizeof(rbtree_node), "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&pNode->mValue) BlockLimbPair(value);
    return pNode;
  }
  rbtree_iterator DoInsertValueImpl(rbtree_node_base* pNodeParent, const BlockLimbPair& value, bool bForceToLeft);
  void DoNukeSubtree(rbtree_node* pNode);
};

// @ 0x005B8070  rbtree<...>::DoInsertValueImpl
rbtree_iterator BlockLimbMap::DoInsertValueImpl(rbtree_node_base* pNodeParent, const BlockLimbPair& value, bool bForceToLeft) {
  int side;
  if (bForceToLeft || (pNodeParent == &mAnchor) || (value.first < ((rbtree_node*)pNodeParent)->mValue.first))
    side = 0;
  else
    side = 1;
  rbtree_node* const pNodeNew = DoCreateNode(value);
  RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
  mnSize++;
  return rbtree_iterator(pNodeNew);
}

// @ 0x005B8250  rbtree<...>::DoNukeSubtree
void BlockLimbMap::DoNukeSubtree(rbtree_node* pNode) {
  while (pNode) {
    DoNukeSubtree((rbtree_node*)pNode->mpNodeRight);
    rbtree_node* const pNodeLeft = (rbtree_node*)pNode->mpNodeLeft;
    pNode->mValue.~BlockLimbPair();
    EASTL_allocator_deallocate(pNode);
    pNode = pNodeLeft;
  }
}

// @ 0x005B8310  rbtree<...>::clear
void BlockLimbMap::clear() {
  DoNukeSubtree((rbtree_node*)mAnchor.mpNodeParent);
  reset();
}

template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
};

}  // namespace eastl

namespace SP {

class cSPEditorManipulationObject {
 public:
  cSPEditorManipulationObject();  // FUN_005b0f80
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

class cSPEditorManipulationSpine : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  cSPEditorBlock* mBlock;      // +0x1c
  cSPVector3 mMouseOffset;     // +0x20
  cSPEditorSpine* mSpine;      // +0x2c
  bool mModelUsingSymmetry;    // +0x30

  cSPEditorManipulationSpine();
  void Init(cSPEditorBlock* block, cSPVector3 mouseOffset, cSPEditorSpine* spine);
  bool OnMouseUp(int button, float x, float y, int modifiers);
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
  bool DoOnMouseMove(float x, float y, int modifiers);
};

// @ 0x005B7460
void cSPEditorManipulationSpine::Init(cSPEditorBlock* block, cSPVector3 mouseOffset, cSPEditorSpine* spine) {
  mBlock = block;
  mMouseOffset = mouseOffset;
  mSpine = spine;
}

// @ 0x005B7490
cSPEditorManipulationSpine::cSPEditorManipulationSpine()
    : mBlock(0), mMouseOffset(0.0f, 0.0f, 0.0f), mSpine(0), mModelUsingSymmetry(false) {
  mChangedObject = false;
}

// @ 0x005B74F0
bool cSPEditorManipulationSpine::OnMouseUp(int button, float x, float y, int modifiers) {
  if (mBlock && mSpine) {
    cSPVector3 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = origin + mMouseOffset;
    mSpine->MoveBlock(mBlock, origin, dir);
  }
  mBlock->mEditorModel->SetUsingSymmetry(mModelUsingSymmetry);
  return false;
}

// @ 0x005B75E0
bool cSPEditorManipulationSpine::DoOnMouseDown(int button, float x, float y, int modifiers) {
  EA::AutoRefCount<cSPEditorModel> model(mBlock->mEditorModel);
  mModelUsingSymmetry = model->IsUsingSymmetry();
  model->SetUsingSymmetry(false);
  if (mBlock && mSpine) {
    cSPVector3 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = mMouseOffset + origin;
    mSpine->StartDrag(&mBlock, origin, dir);
    model->SetDirty(true);
    mSpine->Rebuild(true, true);
  }
  return false;
}

// @ 0x005B7720
bool cSPEditorManipulationSpine::DoOnMouseMove(float x, float y, int modifiers) {
  if (mBlock && mSpine) {
    cSPVector3 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = origin + mMouseOffset;
    mSpine->Drag(&mBlock, origin, dir);
    if (!mChangedObject)
      mChangedObject = true;
    return true;
  }
  return false;
}

class cSPEditorManipulationSpineResize : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  cSPEditorBlock* mBlock;                                  // +0x1c
  cSPVector3 mMouseOffset;                                 // +0x20
  eastl::sp_vector<cSPEditorLimbStructure*> mLimbs;        // +0x2c
  cSPEditorSpine* mSpine;                                  // +0x40
  EA::AutoRefCount<cSPEditorSkinManager> mSkinManager;     // +0x44
  cSPEditorAppEconomy* mEconomy;                           // +0x48
  bool mHasRoutes;                                         // +0x4c
  float mFrontAnchor;                                      // +0x50
  float mBackAnchor;                                       // +0x54
  eastl::BlockLimbMap mBlockLimbs;                         // +0x58
  float mColorTimer;                                       // +0x74
  float mFrameDelay;                                       // +0x78
  bool mHasPlanePoint;                                     // +0x7c
  cSPVector3 mPlanePoint;                                  // +0x80

  ~cSPEditorManipulationSpineResize();
  bool OnMouseUp(int button, float x, float y, int modifiers);
  cSPEditorBlock* GetNextVertebra();
  void Init(cSPEditorBlock* block, cSPVector3 mouseOffset, cSPEditorSpine* spine, cSPEditorSkinManager* skinManager,
            cSPEditorAppEconomy* economy);
  void UpdatePlanePoint(float x, float y);
  bool DoOnMouseDown(float x, float y, int modifiers);
  void RepinSimple();
  void SetBlockHighlight(cSPEditorBlock* block, bool highlight);
};

// @ 0x005B7920
bool cSPEditorManipulationSpineResize::OnMouseUp(int button, float x, float y, int modifiers) {
  if (mBlock && mSpine) {
    EditorUtils::UnpinBlock(mBlock, 0);
    if (mChangedObject) {
      EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
      info->MessagePost(0x503b1435, mBlock, mBlock == 0 ? 0 : mBlock->mEditorModel, 0, 0, 0.0f, 0, -1, 1.0f);
    }
    mSpine->Rebuild(false, true);
    mSpine->GetPart(mBlock)->SetState(3, 1);
    bool usingSymmetry = mBlock->mEditorModel->IsUsingSymmetry();
    mBlock->mEditorModel->SetUsingSymmetry(false);
    int count = mLimbs.size();
    for (int i = 0; i < count; i++)
      mLimbs[i]->Rebuild();
    mBlock->mEditorModel->SetUsingSymmetry(usingSymmetry);
  }
  mHasPlanePoint = false;
  return false;
}

// @ 0x005B7A40
cSPEditorBlock* cSPEditorManipulationSpineResize::GetNextVertebra() {
  if (mBlock == mSpine->mFrontBlock)
    return mSpine->GetFrontNext();
  if (mBlock == mSpine->mBackBlock)
    return mSpine->GetBackNext();
  return 0;
}

// @ 0x005B7A70
void cSPEditorManipulationSpineResize::Init(cSPEditorBlock* block, cSPVector3 mouseOffset, cSPEditorSpine* spine,
                                            cSPEditorSkinManager* skinManager, cSPEditorAppEconomy* economy) {
  mBlock = block;
  mMouseOffset = mouseOffset;
  mSpine = spine;
  mSkinManager = skinManager;
  mEconomy = economy;
}

// @ 0x005B7B80
void cSPEditorManipulationSpineResize::UpdatePlanePoint(float x, float y) {
  cSPVector3 point;
  if (mBlock && mSpine) {
    cSPVector3 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = origin + mMouseOffset;
    const cSPVector3 normal(1.0f, 0.0f, 0.0f);
    float denom = dir.Dot(normal);
    if (denom != 0.0f) {
      float t = -(origin.Dot(normal) / denom);
      if (t >= 0.0f) {
        point = dir * t + origin;
        mPlanePoint = point;
        mPlanePoint.x = 0.0f;
        mHasPlanePoint = true;
        return;
      }
    }
    point = cSPVector3(0.0f, 0.0f, 0.0f);
  } else {
    point = cSPVector3(0.0f, 0.0f, 0.0f);
  }
  mPlanePoint = point;
  mHasPlanePoint = false;
}

// @ 0x005B8230
bool cSPEditorManipulationSpineResize::DoOnMouseDown(float x, float y, int modifiers) {
  UpdatePlanePoint(x, y);
  return true;
}

cSPMatrix3 GetOrientationFromNormal(cSPEditorBlock* block, cSPVector3 normal);  // FUN_0049c140

// @ 0x005B7CF0
void cSPEditorManipulationSpineResize::RepinSimple() {
  cSPEditorBlock** end = mBlock->mChildrenEnd;
  for (cSPEditorBlock** it = mBlock->mChildrenBegin; it != end; ++it) {
    EA::AutoRefCount<cSPEditorBlock> child(*it);
    if (!child->mFlags.test(kBlockFlagHidden)) {
      cSPVector3 d = child->mPosition - mBlock->mPosition;
      float invLen = 1.0f / sqrtf(d.Dot(d) + 1e-8f);
      cSPVector3 hitPos, hitNormal;
      if (mSkinManager->Raycast(0, mBlock->mPosition, d * invLen, &hitPos, &hitNormal, 0, 0)) {
        cSPMatrix3 orient = GetOrientationFromNormal(child, hitNormal);
        EditorUtils::RepinBlockToTorso(child, hitPos, orient, 0);
        mSkinManager->GetPinner(0, hitPos)->Pin(child);
      }
    }
  }
}

// @ 0x005B7F70
void cSPEditorManipulationSpineResize::SetBlockHighlight(cSPEditorBlock* block, bool highlight) {
  int color = highlight ? 5 : 0;
  if (block) {
    if (block->mFlags.test(kBlockFlagSkinPart)) {
      for (eastl::rbtree_node* it = (eastl::rbtree_node*)mBlockLimbs.mAnchor.mpNodeLeft; it != (eastl::rbtree_node*)&mBlockLimbs.mAnchor;
           it = (eastl::rbtree_node*)eastl::RBTreeIncrement(it)) {
        if (it->mValue.first == block) {
          EA::AutoRefCount<cSPEditorSkinPart> part(it->mValue.second);
          part.mpObject->SetHighlight(highlight);
          break;
        }
      }
    } else if (!block->mFlags.test(kBlockFlagHidden)) {
      block->SetHighlight(color, 1, 0, 1);
    }
    cSPEditorBlock** end = block->mChildrenEnd;
    for (cSPEditorBlock** it = block->mChildrenBegin; it != end; ++it) {
      EA::AutoRefCount<cSPEditorBlock> child(*it);
      if (!child->mFlags.test(kBlockFlagHidden))
        SetBlockHighlight(child, highlight);
    }
  }
}

// @ 0x005B84F0
cSPEditorManipulationSpineResize::~cSPEditorManipulationSpineResize() {}

}  // namespace SP


