// slice s00d36940: SP::cCreatureModeInputStrategy::Init (0x00d36940)
// Builds the creature-mode UI input state machine: clears both maps of the
// tGonzagoInputControllerStateMachine at this+4, names its 4 states, picks the
// one- or two-button hit-box layout, then adds 36 transitions and registers the
// machine with the GameInputManager.
// Module flags: /O2 /MD /Gy /TP (no /EHsc: string temporaries get no EH frame).
#include "types.h"
#include <string.h>  // strlen (intrinsic)

extern char gEmptyString[];                           // 0x01667bac shared empty string
// memcpy: E8 call (0x11e0744 thunk); operator delete[]: 0xf47380

// ---------------------------------------------------------------- eastl::string
// eastl::basic_string<char, eastl::allocator> (16 bytes), written as EASTL source.
// The original inlines the first 26 string("") constructions and then (inline
// budget used up) calls RangeInitialize(const char*) at 0x0057cc10 for the last
// 10. With plain `inline` our cl inlines none of them, so the construction chain
// is __forceinline and all 36 are inlined (the only remaining difference).
namespace eastl {
inline size_t CharStrlen(const char* p) { return strlen(p); }

template <typename T>
__forceinline T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
  memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
  return pDestination + (pSourceEnd - pSource);
}

struct allocator {
  allocator() {}
  void* allocate(size_t n, int flags = 0);            // EA operator new[]
  void deallocate(void* p, size_t) { operator delete[](p); }
};

template <typename T, typename Allocator = allocator>
class basic_string {
 public:
  typedef T value_type;
  typedef size_t size_type;

  value_type* mpBegin;
  value_type* mpEnd;
  value_type* mpCapacity;
  Allocator mAllocator;

  basic_string(const value_type* p, const Allocator& alloc = Allocator());
  ~basic_string() { DeallocateSelf(); }

  void RangeInitialize(const value_type* pBegin, const value_type* pEnd);
  void RangeInitialize(const value_type* pBegin);
  value_type* DoAllocate(size_type n);
  void DoFree(value_type* p, size_type n);
  void AllocateSelf();
  void AllocateSelf(size_type n);
  void DeallocateSelf();
};

template <typename T, typename Allocator>
__forceinline basic_string<T, Allocator>::basic_string(const value_type* p, const Allocator& alloc)
    : mpBegin(NULL), mpEnd(NULL), mpCapacity(NULL), mAllocator(alloc) {
  RangeInitialize(p);
}

template <typename T, typename Allocator>
__forceinline void basic_string<T, Allocator>::RangeInitialize(const value_type* pBegin, const value_type* pEnd) {
  const size_type n = (size_type)(pEnd - pBegin);
  AllocateSelf((size_type)(n + 1));
  mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
  *mpEnd = 0;
}

template <typename T, typename Allocator>
__forceinline void basic_string<T, Allocator>::RangeInitialize(const value_type* pBegin) {
  RangeInitialize(pBegin, pBegin + CharStrlen(pBegin));
}

template <typename T, typename Allocator>
inline T* basic_string<T, Allocator>::DoAllocate(size_type n) {
  return (value_type*)mAllocator.allocate(n * sizeof(value_type));
}

template <typename T, typename Allocator>
inline void basic_string<T, Allocator>::DoFree(value_type* p, size_type n) {
  if (p)
    mAllocator.deallocate(p, n * sizeof(value_type));
}

template <typename T, typename Allocator>
inline void basic_string<T, Allocator>::AllocateSelf() {
  mpBegin = gEmptyString;
  mpEnd = mpBegin;
  mpCapacity = mpBegin + 1;
}

template <typename T, typename Allocator>
__forceinline void basic_string<T, Allocator>::AllocateSelf(size_type n) {
  if (n > 1) {
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
  } else
    AllocateSelf();
}

template <typename T, typename Allocator>
inline void basic_string<T, Allocator>::DeallocateSelf() {
  if ((mpCapacity - mpBegin) > 1)
    DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
}

typedef basic_string<char> string;
}  // namespace eastl
typedef eastl::string String;

// ---------------------------------------------------------------- types
// eastl::rbtree_node_base / eastl::map (0x1c bytes, empty compare at +0)
struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};

// map<unsigned, vector<tGonzagoInputControllerStateTransition>> stateTransitions
struct TransitionMap {
  uint32_t mCompare;
  rbtree_node_base mAnchor;
  uint32_t mnSize;
  uint32_t mAllocator;
  void DoNuke(rbtree_node_base* pNode);               // 0x00b1b830
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear() {
    DoNuke(mAnchor.mpNodeParent);
    reset();
  }
};

// map<unsigned, eastl::string> names
struct NameMap {
  uint32_t mCompare;
  rbtree_node_base mAnchor;
  uint32_t mnSize;
  uint32_t mAllocator;
  void DoNuke(rbtree_node_base* pNode);               // 0x00e4b990
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear() {
    DoNuke(mAnchor.mpNodeParent);
    reset();
  }
};

// SP::tGonzagoInputControllerStateMachine (0x38)
struct tGonzagoInputControllerStateMachine {
  TransitionMap stateTransitions;                     // +0x00
  NameMap names;                                      // +0x1c
};

namespace EA { namespace ArgScript {
class cCommandBase {
 public:
  cCommandBase();                                     // 0x0083c800
  ~cCommandBase();                                    // 0x0083c750
  virtual void ParseLine(void* line);
  void* mParser;                                      // +0x04
  int mRefCount;                                      // +0x08
  int field_c;                                        // +0x0c
};
}}

// ArgScript command that fills a tGonzagoInputControllerStateMachine (vtable
// 0x0145d210). The class name is coined here; the PDB gives none.
class cUIStateMachineParser : public EA::ArgScript::cCommandBase {
 public:
  cUIStateMachineParser(tGonzagoInputControllerStateMachine* pMachine);  // 0x00b198d0
  void SetStateName(int state, const char* name);     // 0x00b1c080
  void ParseFile(const char* name);                   // 0x00b1b410
  // fields of SP::tGonzagoInputControllerStateTransition / ModAPI UIStateMachineTransition
  void AddTransition(int srcState, int eventType, int keyModFlags, int eventParam,
                     int objectTypeId, int objectFlags, uint32_t messageId, int messageParam,
                     int dstState, bool isPush, const String& comment,
                     int longMouseMove);              // 0x00b1c8d0
  tGonzagoInputControllerStateMachine* mpMachine;     // +0x10
};

struct cGameInputManager {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void AddUIStateMachine(tGonzagoInputControllerStateMachine* pMachine,
                                 int initialState, int unk);  // +0x20
};
cGameInputManager* GameInputManager();                // 0x00b3d250

namespace SP {
class cCreatureModeInputStrategy {
 public:
  void* vptr;                                         // +0x000
  tGonzagoInputControllerStateMachine mStateMachine;  // +0x004
  uint8_t pad3c[0x106 - 0x3c];
  bool mbOneButtonMouse;                              // +0x106
  void Init(int mouseMode);
};
}

// ---------------------------------------------------------------- 0x00d36940
void SP::cCreatureModeInputStrategy::Init(int mouseMode) {
  mStateMachine.stateTransitions.clear();
  mStateMachine.names.clear();

  cUIStateMachineParser builder(&mStateMachine);
  builder.SetStateName(0, "CRGNeutral");
  builder.SetStateName(1, "CRGFreeCamera");
  builder.SetStateName(2, "CRGBanContent");
  builder.SetStateName(3, "CRGInspectContent");

  switch (mouseMode) {
    case 0:
      builder.ParseFile("UIMachineCreature");
      mbOneButtonMouse = true;
      break;
    case 1:
      builder.ParseFile("UIMachineCreatureTwoButton");
      mbOneButtonMouse = false;
      break;
    default:
      builder.ParseFile("UIMachineCreature");
      mbOneButtonMouse = true;
      break;
  }

  builder.AddTransition(2, 1, 0x3ff, 1000, -1, 0, 0xb332763d, -1, 2, false, String(""), 0);
  builder.AddTransition(2, 4, 0x3ff, 0x1b, -1, 0, 0xf3327645, 0, 0, false, String(""), 0);
  builder.AddTransition(2, 6, 0x3ff, -1, -1, 0, 0x0639939b, -1, 2, false, String(""), 0);
  builder.AddTransition(2, 1, 0x3ff, 0x3ea, -1, 0, 0x06493c83, 1, 2, false, String(""), 0);
  builder.AddTransition(2, 3, 0x3ff, 0x3ea, -1, 0, 0x06493c83, 0, 2, false, String(""), 0);
  builder.AddTransition(3, 1, 0x3ff, 1000, -1, 0, 0x062663dc, -1, 3, false, String(""), 0);
  builder.AddTransition(3, 4, 0x3ff, 0x1b, -1, 0, 0x062663dd, 0, 0, false, String(""), 0);
  builder.AddTransition(3, 1, 0x3ff, 0x3ea, -1, 0, 0x06493c83, 1, 3, false, String(""), 0);
  builder.AddTransition(3, 3, 0x3ff, 0x3ea, -1, 0, 0x06493c83, 0, 3, false, String(""), 0);
  builder.AddTransition(0, 10, 0x3ff, 0x21, -1, 0, 0x03c7560d, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x18, -1, 0, 0x035f7b83, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x18, -1, 0, 0x035f7b83, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x15, -1, 0, 0x01c41da1, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x051893ad, -1, 0, 0x051893a3, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x540665ff, -1, 0, 0x940666d2, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x14, -1, 0, 0x50567351, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 1, -1, 0, 0x027c7119, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 2, -1, 0, 0x027c7119, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 3, -1, 0, 0x027c67ea, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 4, -1, 0, 0x027c67ea, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x93cf382f, -1, 0, 0x53c4bde7, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x10, -1, 0, 0x705673e1, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x10, -1, 0, 0x705673e1, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x11, -1, 0, 0x705673e9, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x11, -1, 0, 0x705673e9, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x13, -1, 0, 0x025db76f, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x13, -1, 0, 0x025db76f, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x12, -1, 0, 0x025db76a, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x12, -1, 0, 0x025db76a, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x051cba70, -1, 0, 0x051cbb29, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x051cba70, -1, 0, 0x051cbb29, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x051cba7b, -1, 0, 0x051cbb2d, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x051cba7b, -1, 0, 0x051cbb2d, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x3ff, 0x16, -1, 0, 0x02c4bfde, 1, -2, false, String(""), 0);
  builder.AddTransition(-1, 11, 0x3ff, 0x16, -1, 0, 0x02c4bfde, 0, -2, false, String(""), 0);
  builder.AddTransition(-1, 10, 0x40, 0xf3ce0149, -1, 0, 0x13cdf6fa, 0, -2, false, String(""), 0);

  GameInputManager()->AddUIStateMachine(&mStateMachine, 0, 0);
}
