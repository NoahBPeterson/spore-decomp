// Slice s00b1c8d0 -- ArgScript line handler of the input state-machine loader (see s00b1a7b0, whose
// LoadStateMachine (0x00b1b410) registers this object for "DeclareState", "DeclareMenu",
// "DeclareMessage", "AddTransition" and "IncludeMachine").
// The image names 0x00b1cca0 "$E259" (a compiler-generated symbol); it is a __thiscall taking the
// parsed line (EA::ArgScript::cArguments, ModAPI ArgScript::Line).
// Flags: /O2 /MD /Gy /TP /GS- (no /EHsc: string locals get no EH frame; no /GS: no stack cookie).
#include "types.h"
#include <string.h>

void* operator new[](unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file,
                     int line);  // 0x00f473a0
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy, strlen)

#define EASTL_ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace eastl {

extern char gEmptyString[];  // 0x01667bac

struct true_type {};

// The module's default allocator ("Simulator" heap name, EASTL allocator.h line 209).
class allocator {
public:
  allocator(const char* = 0) {}
  allocator(const allocator&) {}
  void* allocate(unsigned int n, int flags = 0) {
    return ::new ("Simulator", flags, 0, EASTL_ALLOC_FILE, 0xd1) char[n];
  }
  void deallocate(void* p, unsigned int) { delete[] (char*)p; }
};

// eastl::basic_string<char, eastl::allocator> (16 bytes)
class string {
public:
  typedef unsigned int size_type;

  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  allocator mAllocator;

  string() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
  string(const char* p, const allocator& a = allocator("EASTL basic_string")) : mAllocator(a) { RangeInitialize(p); }
  ~string() { DeallocateSelf(); }

  const char* c_str() const { return mpBegin; }

  string& assign(const char* pBegin, const char* pEnd);  // 0x00454cb0
  string& assign(const char* p) { return assign(p, p + strlen(p)); }

  string& operator=(const string& x) {
    if (this != &x) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }

  void RangeInitialize(const char* pBegin, const char* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  void RangeInitialize(const char* p) { RangeInitialize(p, p + strlen(p)); }

  void AllocateSelf() {
    mpBegin = gEmptyString;
    mpEnd = gEmptyString;
    mpCapacity = gEmptyString + 1;
  }
  void AllocateSelf(size_type n) {
    if (n > 1) {
      mpBegin = DoAllocate(n);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else
      AllocateSelf();
  }
  char* DoAllocate(size_type n) { return (char*)mAllocator.allocate(n); }
  void DoFree(char* p, size_type n) {
    if (p) mAllocator.deallocate(p, n);
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
  }

  static char* CharStringUninitializedCopy(const char* pSource, const char* pSourceEnd, char* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource));
    return pDestination + (pSourceEnd - pSource);
  }
};

bool operator==(const string& a, const char* p);  // 0x00555020

}  // namespace eastl

namespace EA {
namespace ArgScript {

class cArguments {
public:
  int NumArguments();                                                 // 0x00837f30
  const char* operator[](int i);                                      // 0x00837f20
  bool HasArgument(const char* p);                                    // 0x00837ee0
  char** OptionArguments(const char* label, int* count, int min, int max);  // 0x00838130
  char** OptionArguments(const char* label, int n);                   // 0x00838330
};

class FormatParser {
public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
  virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
  virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26();
  virtual int ParseInt(const char* pString) const;  // +0x9c
};

}  // namespace ArgScript
}  // namespace EA

using EA::ArgScript::cArguments;

// eastl::map<eastl::string, int> instances (rbtree: dummy +0, anchor +4, size +0x14).
struct RBNodeBase {
  RBNodeBase* mpNodeRight;
  RBNodeBase* mpNodeLeft;
  RBNodeBase* mpNodeParent;
  char mColor;
};

struct StringIntPair {  // eastl::pair<const eastl::string, int>
  const eastl::string first;
  int second;
  StringIntPair(const eastl::string& a, const int& b);  // 0x006a3f40
};

struct StringIntNode : RBNodeBase {
  StringIntPair mValue;  // +0x10
};

struct StringIntMap {
  struct iterator {
    StringIntNode* mpNode;
    StringIntPair* operator->() const { return &mpNode->mValue; }
    bool operator==(const iterator& x) const { return mpNode == x.mpNode; }
  };
  struct insert_return_type {
    iterator first;
    bool second;
  };

  int mDummy;
  RBNodeBase mAnchor;  // +4
  unsigned int mnSize;

  iterator end() {
    iterator it;
    it.mpNode = (StringIntNode*)&mAnchor;
    return it;
  }
  iterator find(const eastl::string& key);                                                // 0x00b20930
  insert_return_type DoInsertValue(const StringIntPair& value, eastl::true_type);           // 0x00b1aba0
  insert_return_type insert(const StringIntPair& value) { return DoInsertValue(value, eastl::true_type()); }
  int& operator[](const eastl::string& key);                                              // 0x00b1c220
};

extern StringIntMap gMessageNames;  // 0x015682ec
extern StringIntMap gMenuNames;     // 0x015680cc
extern int gNextStateIndex;         // 0x0167be94
extern EA::ArgScript::FormatParser* gScriptParser;  // 0x0167be98

struct StateTable {  // state-name container searched by FindState
  uint32_t mData[4];
};
int __cdecl FindState(StateTable* states, const char* name);  // 0x00b19b10
int __cdecl GetEventType(const eastl::string& s);             // 0x00b19a90
int __cdecl GetEventMessage(const eastl::string& s);          // 0x00b1a250
int __cdecl GetEventKey(const eastl::string& s);              // 0x00b19ef0
int __cdecl GetKeyModifier(const eastl::string& s);           // 0x00b19a50
int __cdecl GetObjectType(const eastl::string& s);            // 0x00b1a290
int __cdecl GetObjectFlag(const eastl::string& s);            // 0x00b19ad0

inline void* operator new(unsigned int, void* p) { return p; }

extern "C" RBNodeBase* __cdecl RBTreeIncrement(RBNodeBase* p);  // 0x00921580

// One "AddTransition" script record; the value type of the per-state vector.
struct Transition {          // 0x38 bytes
  eastl::string mComment;    // +0x00
  int mToState;              // +0x10
  int mObjectFlags;          // +0x14
  int mMessageParam;         // +0x18
  int mEventValue;           // +0x1c
  int mObject;               // +0x20
  char mStackOp;             // +0x24
  char mPad25[3];            // +0x25
  int mEventType;            // +0x28
  int mKeyMod;               // +0x2c
  int mObjectFlagsCopy;      // +0x30 (the original stores the object flags twice)
  int mLongMouseMove;        // +0x34

  Transition() {}
  Transition(const Transition& x);  // 0x00b1a0f0
};

struct TransitionVector {  // eastl::vector<Transition> (12 bytes)
  Transition* mpBegin;     // +0x00
  Transition* mpEnd;       // +0x04
  Transition* mpCapacity;  // +0x08

  void push_back(const Transition& v) {
    if (mpEnd < mpCapacity) {
      Transition* p = mpEnd;
      mpEnd = p + 1;
      if (p) new (p) Transition(v);
    } else
      Insert(mpEnd, &v);  // 0x00b1a900
  }
  TransitionVector& operator=(const TransitionVector& x);  // 0x00b1a7b0
  void Insert(Transition* pPos, const Transition* pValue);  // 0x00b1a900
};

struct TransitionMapNode : RBNodeBase {
  int mKey;                          // +0x10
  TransitionVector mTransitions;     // +0x14
};

// eastl::map<int, eastl::vector<Transition> > (rbtree: dummy +0, anchor +4, size +0x14).
struct TransitionMap {
  int mDummy;            // +0x00
  RBNodeBase mAnchor;    // +0x04
  unsigned int mnSize;   // +0x14
  int mPad18;            // +0x18

  TransitionMapNode* Begin() { return (TransitionMapNode*)mAnchor.mpNodeRight; }
  TransitionMapNode* End() { return (TransitionMapNode*)&mAnchor; }

  void Find(void** pOut, const int* pKey);                  // 0x00e5c780
  TransitionMapNode* FindNode(const int& key) {
    void* pNode;
    Find(&pNode, &key);
    return (TransitionMapNode*)pNode;
  }
  TransitionVector& operator[](const int& key);             // 0x00b1c150
};

// The two state tables held by a cStateMachineHost (each an eastl::map copy).
struct StateMapA {       // 0x1c bytes
  int mDummy;            // +0x00
  RBNodeBase mAnchor;    // +0x04
  unsigned int mnSize;   // +0x14
  int mPad18;            // +0x18

  StateMapA() {
    mAnchor = RBNodeBase();
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  StateMapA& operator=(const StateMapA& x);  // 0x00b1c0c0
  void FreeTree(void* pNode);                // 0x00b1b830
  ~StateMapA() { FreeTree(mAnchor.mpNodeParent); }
};

struct StateMapB {       // 0x1c bytes
  int mDummy;            // +0x00
  RBNodeBase mAnchor;    // +0x04
  unsigned int mnSize;   // +0x14
  int mPad18;            // +0x18

  StateMapB() {
    mAnchor = RBNodeBase();
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  StateMapB& operator=(const StateMapB& x);  // 0x00b1b630
  void FreeTree(void* pNode);                // 0x00e4b990
  ~StateMapB() { FreeTree(mAnchor.mpNodeParent); }
};

struct Transitions {     // 0x38 bytes
  StateMapA mPrimary;    // +0x00
  StateMapB mSecondary;  // +0x1c
};

class cMessageServer {
public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04();
  virtual void v05(int a, int b, int c);  // +0x14
};
cMessageServer* MessageServer();  // 0x0067dcc0

class cStateMachineHost;

class cCommandBase {
public:
  cCommandBase();                             // 0x0083c800
  ~cCommandBase();                            // 0x0083c750
  virtual void Execute(int a, int b, int c);  // slot 0
  uint32_t m04;                               // +0x04
  uint32_t m08;                               // +0x08
  uint32_t m0c;                               // +0x0c
};

class cLoadMachineCmd : public cCommandBase {
public:
  cLoadMachineCmd(Transitions* pTransitions) : mpTransitions(pTransitions) {}
  void LoadStateMachine(const char* name);  // 0x00b1b410
  Transitions* mpTransitions;               // +0x10
};

struct cStateMachineInfo {
  TransitionMap mTransitions;  // +0x00
  uint32_t mPad18;             // +0x18
  StateTable mStates;          // +0x1c
};

class cStateMachineHost {
public:
  void ParseLine(cArguments& args);
  void LoadStateMachine(const char* name);           // 0x00b1b410
  void DeclareState(int index, const char* name);    // 0x00b1c080
  void AddTransition(int fromState, int eventType, int keyMod, int eventValue, int object, int objectFlags,
                     int messageId, int messageParam, int toState, int longMouseMove,
                     const eastl::string& comment, int stackOp);  // 0x00b1c8d0
  void ResetAndLoad(const char* name);               // 0x00b1caa0
  void SetTransitions(const Transitions* pTransitions, int a, int b);  // 0x00b1cc00

  uint32_t pad[4];              // +0x00
  cStateMachineInfo* mpInfo;    // +0x10
  uint32_t pad14[5];            // +0x14
  Transitions mTransitions;     // +0x28
  int m60;                      // +0x60
  int m64;                      // +0x64
  uint32_t pad68[0x1d];         // +0x68
  eastl::string mName;          // +0xdc
  uint32_t padEc[4];            // +0xec
  uint32_t* mPendingBegin;      // +0xfc
  uint32_t* mPendingEnd;        // +0x100
};

// The script-object side of the state-machine hand-off (0x00b1d770..0x00b1d7f0).
class cTransferMessage {
public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05();
  virtual cTransferMessage* v06();  // +0x18
  virtual void v07();
  virtual cTransferMessage* v08();  // +0x20
};

struct cTransferType {
  int m00;   // +0x00
  int m04;   // +0x04
  int mType; // +0x08
};

struct cTransferState {
  uint32_t mPad[8];  // +0x00
  uint32_t m20;      // +0x20

  bool IsHandledType(cTransferType* p) const;  // 0x00b1d770
  bool Save(cTransferMessage* p) const;        // 0x00b1d7b0
  bool Load(cTransferMessage* p);              // 0x00b1d7f0
};

extern "C" bool __cdecl FUN_0093aa70(void* pStream, void* pValue, int a, int b);  // 0x0093aa70
extern "C" bool __cdecl FUN_0093a780(void* pStream, void* pValue, int a, int b);  // 0x0093a780

// @ 0x00b1cca0
void cStateMachineHost::ParseLine(cArguments& args) {
  int numArgs = args.NumArguments();
  if (numArgs <= 0) return;

  eastl::string command(args[0]);

  if ((command == "IncludeMachine") && (numArgs > 1)) LoadStateMachine(args[1]);

  if (command == "DeclareState") {
    if (numArgs > 1) {
      eastl::string name(args[1]);
      DeclareState(gNextStateIndex, name.c_str());
      ++gNextStateIndex;
    }
  } else if (command == "DeclareMessage") {
    if (numArgs > 2) {
      int id = gScriptParser->ParseInt(args[2]);
      eastl::string name(args[1]);
      gMessageNames.insert(StringIntPair(name, id));
    }
  } else if (command == "DeclareMenu") {
    if (numArgs > 2) {
      int id = gScriptParser->ParseInt(args[2]);
      gMenuNames[args[1]] = id;
    }
  }

  if (command == "AddTransition") {
    int count;
    char** p;

    int fromState = -1;
    p = args.OptionArguments("FromState", 1);
    if (p) fromState = FindState(&mpInfo->mStates, p[0]);

    eastl::string comment;
    p = args.OptionArguments("Comment", 1);
    if (p) comment.assign(p[0]);

    int toState = -2;
    p = args.OptionArguments("ToState", 1);
    if (p) toState = FindState(&mpInfo->mStates, p[0]);

    int eventType = 12;
    int eventValue = -1;
    p = args.OptionArguments("Event", &count, 1, 2);
    int eventMessage = 0;
    if (p) {
      eastl::string eventName(p[0]);
      eventType = GetEventType(eventName);
      if (count > 1) {
        eastl::string valueName(p[1]);
        if (eventType == 9)
          eventValue = eventMessage = GetEventMessage(valueName);
        else
          eventValue = GetEventKey(valueName);
      }
    }

    int keyMod = 0;
    p = args.OptionArguments("KeyMod", &count, 1, 4);
    if (p) {
      do {
        --count;
        eastl::string modName(p[count]);
        keyMod |= GetKeyModifier(modName);
      } while (count > 0);
    }

    int object = -1;
    p = args.OptionArguments("Object", 1);
    if (p) {
      eastl::string objectName(p[0]);
      object = GetObjectType(objectName);
    }

    int objectFlags = 0;
    p = args.OptionArguments("ObjectFlags", &count, 1, 4);
    if (p) {
      for (int i = 0; i < count; ++i) {
        eastl::string flagName(p[i]);
        objectFlags |= GetObjectFlag(flagName);
      }
    }

    int longMouseMove = 0;
    p = args.OptionArguments("LongMouseMove", &count, 1, 0x7fffffff);
    if (p) longMouseMove = gScriptParser->ParseInt(p[0]);

    int messageId = 0;
    int messageParam = 666;
    p = args.OptionArguments("Message", &count, 1, 2);
    if (p) {
      eastl::string messageName(p[0]);
      StringIntMap::iterator it = gMessageNames.find(messageName);
      if (it == gMessageNames.end()) goto done;  // unknown message: no transition
      messageId = it->second;
      if (count > 1)
        messageParam = gScriptParser->ParseInt(p[1]);
      else if (eventType == 9)
        messageParam = eventMessage;
    }

    if (args.HasArgument("Push")) {
      args.OptionArguments("Push", 0);
      AddTransition(fromState, eventType, keyMod, eventValue, object, objectFlags, messageId, messageParam, toState,
                    longMouseMove, comment, 1);
    } else if (args.HasArgument("Pop")) {
      args.OptionArguments("Pop", 0);
      AddTransition(fromState, eventType, keyMod, eventValue, object, objectFlags, messageId, messageParam, -3,
                    longMouseMove, comment, 0);
    } else {
      AddTransition(fromState, eventType, keyMod, eventValue, object, objectFlags, messageId, messageParam, toState,
                    longMouseMove, comment, 0);
    }
  done:;
  }
}

// @ 0x00b1c8d0
void cStateMachineHost::AddTransition(int fromState, int eventType, int keyMod, int eventValue, int object,
                                      int objectFlags, int messageId, int messageParam, int toState,
                                      int longMouseMove, const eastl::string& comment, int stackOp) {
  Transition t;
  t.mComment = comment;
  t.mObjectFlags = objectFlags;
  t.mMessageParam = messageParam;
  t.mEventType = eventType;
  t.mKeyMod = keyMod;
  t.mEventValue = eventValue;
  t.mObject = object;
  t.mToState = toState;
  t.mObjectFlagsCopy = objectFlags;
  t.mLongMouseMove = longMouseMove;
  t.mStackOp = (char)stackOp;

  if (fromState == -1) {
    for (TransitionMapNode* pNode = mpInfo->mTransitions.Begin(); pNode != mpInfo->mTransitions.End();
         pNode = (TransitionMapNode*)RBTreeIncrement(pNode))
      pNode->mTransitions.push_back(t);
  } else {
    TransitionMapNode* pNode = mpInfo->mTransitions.FindNode(fromState);
    if (pNode == mpInfo->mTransitions.End() || pNode->mTransitions.mpBegin == pNode->mTransitions.mpEnd) {
      TransitionMapNode* pAny = mpInfo->mTransitions.FindNode(-1);
      if (pAny != mpInfo->mTransitions.End() && pAny->mTransitions.mpBegin != pAny->mTransitions.mpEnd)
        mpInfo->mTransitions[fromState] = pAny->mTransitions;
    }
  }
  mpInfo->mTransitions[fromState].push_back(t);
}

// @ 0x00b1caa0
void cStateMachineHost::ResetAndLoad(const char* name) {
  mTransitions = Transitions();

  cLoadMachineCmd cmd(&mTransitions);
  if (name == 0) {
    if (mName.length() != 0) cmd.LoadStateMachine(mName.mpBegin);
  } else {
    mName.assign(name, name + strlen(name));
    cmd.LoadStateMachine(mName.mpBegin);
  }

  while (mPendingBegin != mPendingEnd) --mPendingEnd;
  m60 = 0;
  m64 = 0;
  MessageServer()->v05(0x7561116, 0, 0);
}

// @ 0x00b1cc00
void cStateMachineHost::SetTransitions(const Transitions* pTransitions, int a, int b) {
  mName.clear();
  m60 = a;
  m64 = b;
  mTransitions = *pTransitions;
  while (mPendingBegin != mPendingEnd) --mPendingEnd;
  return MessageServer()->v05(0x7561116, 0, 0);
}

// @ 0x00b1d770
bool cTransferState::IsHandledType(cTransferType* p) const {
  switch (p->mType - 1) {
    case 0:
    case 1:
      return false;
    case 2:
    case 3:
      return true;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      return false;
    default:
      return false;
  }
}

// @ 0x00b1d7b0
bool cTransferState::Save(cTransferMessage* p) const {
  uint32_t value = m20;
  FUN_0093aa70(p->v08()->v06(), &value, 1, 0);
  return true;
}

// @ 0x00b1d7f0
bool cTransferState::Load(cTransferMessage* p) {
  uint32_t value;
  cTransferMessage* pStream = p->v08()->v06();
  FUN_0093a780(pStream, &value, 1, 0);
  m20 = value;
  return true;
}
