// Slice s00b1c8d0 -- ArgScript line handler of the input state-machine loader (see s00b1a7b0, whose
// LoadStateMachine (0x00b1b410) registers this object for "DeclareState", "DeclareMenu",
// "DeclareMessage", "AddTransition" and "IncludeMachine").
// The image names 0x00b1cca0 "$E259" (a compiler-generated symbol); it is a __thiscall taking the
// parsed line (EA::ArgScript::cArguments, ModAPI ArgScript::Line).
// Flags: /O2 /MD /Gy /TP (no /EHsc: string locals get no EH frame).
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

struct cStateMachineInfo {
  uint32_t pad[7];
  StateTable mStates;  // +0x1c
};

class cStateMachineHost {
public:
  void ParseLine(cArguments& args);
  void LoadStateMachine(const char* name);           // 0x00b1b410
  void DeclareState(int index, const char* name);    // 0x00b1c080
  void AddTransition(int fromState, int eventType, int keyMod, int eventValue, int object, int objectFlags,
                     int messageId, int messageParam, int toState, int longMouseMove,
                     const eastl::string& comment, int stackOp);  // 0x00b1c8d0

  uint32_t pad[4];
  cStateMachineInfo* mpInfo;  // +0x10
};

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
