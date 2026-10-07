// Slice s00b1a7b0: EASTL container instances (vector of 0x38-byte elements, rbtree copy/insert/nuke for
// map<int, string>, map<int, vector<Elem38>>, map<string, V>), a nearest-noun query, an ArgScript state-machine
// loader and the "Event:... Value:... Object:..." input message handler.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void operator delete[](void* p);  // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

#define EASTL_ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define SPORE_ALLOC(n) operator new((n), "Simulator", 0, 0, EASTL_ALLOC_FILE, 0xd1)

inline void* operator new(unsigned int, void* p) { return p; }
extern char gEmptyString[];  // 0x01667bac

// ------------------------------------------------------------------ basic_string<char>
struct string8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  string8() {
    mpBegin = gEmptyString;
    mpEnd = gEmptyString;
    mpCapacity = gEmptyString + 1;
  }
  // copy: capacity n+1, memcpy, terminate
  string8(const char* b, const char* e) {
    unsigned n = (unsigned)(e - b);
    unsigned cap = n + 1;
    if (cap > 1) {
      mpBegin = (char*)SPORE_ALLOC(cap);
      mpCapacity = mpBegin + cap;
    } else {
      mpBegin = gEmptyString;
      mpCapacity = gEmptyString + 1;
    }
    mpEnd = mpBegin;
    memcpy(mpBegin, b, n);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  ~string8() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) delete[] mpBegin;
  }
  string8 substr(unsigned pos, unsigned n) const;  // 0x006082a0
};

// ------------------------------------------------------------------ Elem38: 0x38-byte vector element (string first)
struct Elem38 {
  string8 name;
  char rest[0x38 - sizeof(string8)];
  Elem38(const Elem38& o);                 // 0x00b1a0f0
  Elem38& __thiscall operator=(const Elem38& o);  // 0x00b19d40
};

// helpers (cdecl) shared by the vector<Elem38> instances
Elem38* __cdecl Elem38_Copy(Elem38* first, Elem38* last, Elem38* dest);          // 0x00b19df0 (eastl::copy)
Elem38* __cdecl Elem38_CopyBackward(Elem38* first, Elem38* last, Elem38* dest);  // 0x00b19e70
Elem38* __cdecl Elem38_UninitCopy(Elem38* first, Elem38* last, Elem38* dest);    // 0x00b1a210
void __cdecl Elem38_UninitCopyGuard(Elem38* first, Elem38* last, Elem38* dest);  // 0x00b19da0
Elem38* __cdecl Elem38_UninitCopy5(void* tmp, Elem38* first, Elem38* last, Elem38* dest, const void* vec);  // 0x00b1a1d0

struct Elem38Vector {
  Elem38* mpBegin;
  Elem38* mpEnd;
  Elem38* mpCapacity;
  Elem38* __thiscall DoAllocateAndCopy(unsigned n, Elem38* first, Elem38* last);  // 0x00b1a540
  void __thiscall Destruct(Elem38* first, Elem38* last);                             // 0x00b1a190
  void __thiscall DoFree(Elem38* p) {}
  Elem38Vector(const Elem38Vector& x);              // 0x00b1a350
  Elem38Vector& operator=(const Elem38Vector& x);   // 0x00b1a7b0
  void DoInsertValue(Elem38* position, const Elem38& value);  // 0x00b1a900
};

static inline void Elem38Free(Elem38* p) {
  if (p && ((int*)p)[-1]) delete[] (char*)p;
}

// @ 0x00b1a7b0
Elem38Vector& Elem38Vector::operator=(const Elem38Vector& x) {
  if (&x != this) {
    Elem38* const xBegin = x.mpBegin;
    Elem38* const xEnd = x.mpEnd;
    const unsigned nNewSize = (unsigned)(xEnd - xBegin);
    Elem38* const pBegin = mpBegin;
    if (nNewSize > (unsigned)(mpCapacity - pBegin)) {
      Elem38* pNewData = DoAllocateAndCopy(nNewSize, xBegin, xEnd);
      Destruct(mpBegin, mpEnd);
      Elem38Free(mpBegin);
      mpBegin = pNewData;
      mpCapacity = mpBegin + nNewSize;
    } else if (nNewSize > (unsigned)(mpEnd - pBegin)) {
      unsigned size = (unsigned)(mpEnd - pBegin);
      Elem38_Copy(xBegin, xBegin + size, pBegin);
      char tmp[4];
      Elem38_UninitCopy5(tmp, x.mpBegin + (unsigned)(mpEnd - mpBegin), x.mpEnd, mpEnd, &x);
    } else {
      Elem38* pNewEnd = Elem38_Copy(xBegin, xEnd, pBegin);
      Destruct(pNewEnd, mpEnd);
    }
    mpEnd = mpBegin + nNewSize;
  }
  return *this;
}

static __forceinline Elem38* UCopy(Elem38* first, Elem38* last, Elem38* dest) {
  Elem38* r = Elem38_UninitCopy(first, last, dest);
  Elem38_UninitCopyGuard(first, last, dest);
  return r;
}

// @ 0x00b1a900
// insert one element at position: shift up by one when there is room, otherwise grow to double capacity.
void Elem38Vector::DoInsertValue(Elem38* position, const Elem38& value) {
  if (mpEnd != mpCapacity) {
    const Elem38* pValue = &value;
    if (&value >= position && &value < mpEnd) ++pValue;
    if (mpEnd) new (mpEnd) Elem38(*(mpEnd - 1));
    Elem38_CopyBackward(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
    const unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
    volatile Elem38* pNewDataV = nNewSize ? (Elem38*)SPORE_ALLOC(nNewSize * sizeof(Elem38)) : 0;
    Elem38* pNewData = (Elem38*)pNewDataV;
    Elem38* pNewEnd = UCopy(mpBegin, position, pNewData);
    if (pNewEnd) new (pNewEnd) Elem38(value);
    Elem38* pOldEnd = mpEnd;
    Elem38* pTail = pNewEnd + 1;
    pNewEnd = UCopy(position, pOldEnd, pTail);
    Elem38Free(mpBegin);
    mpEnd = pNewEnd;
    mpBegin = pNewData;
    mpCapacity = pNewData + nNewSize;
  }
}

// ------------------------------------------------------------------ rbtree node plumbing (EASTL layout)
struct RBNodeBase {
  RBNodeBase* mpNodeRight;   // +0
  RBNodeBase* mpNodeLeft;    // +4
  RBNodeBase* mpNodeParent;  // +8
  char mColor;               // +0xc
};
struct IntStringNode : RBNodeBase {  // map<int, string8>, node size 0x24
  int first;                         // +0x10
  string8 second;                    // +0x14
  char pad[4];
};
struct IntVecNode : RBNodeBase {  // map<int, vector<Elem38>>, node size 0x28
  int first;                      // +0x10
  Elem38Vector second;            // +0x14
  char pad[4];
};

struct IntStringMap {
  int mDummy;
  IntStringNode* __thiscall DoCreateNodeCopy(const IntStringNode* src, IntStringNode* parent);  // 0x00b1a5a0
  IntStringNode* DoCopySubtree(const IntStringNode* src, IntStringNode* dest);
};

// @ 0x00b1aa50
IntStringNode* IntStringMap::DoCopySubtree(const IntStringNode* pNodeSource, IntStringNode* pNodeDest) {
  IntStringNode* pNewNodeRoot = DoCreateNodeCopy(pNodeSource, pNodeDest);
  if (pNodeSource->mpNodeRight)
    pNewNodeRoot->mpNodeRight = DoCopySubtree((const IntStringNode*)pNodeSource->mpNodeRight, pNewNodeRoot);
  pNodeDest = pNewNodeRoot;
  pNodeSource = (const IntStringNode*)pNodeSource->mpNodeLeft;
  while (pNodeSource) {
    IntStringNode* pNewNode = (IntStringNode*)SPORE_ALLOC(0x24);
    if (&pNewNode->first) {
      pNewNode->first = pNodeSource->first;
      new (&pNewNode->second) string8(pNodeSource->second.mpBegin, pNodeSource->second.mpEnd);
    }
    pNewNode->mpNodeRight = 0;
    pNewNode->mpNodeLeft = 0;
    pNewNode->mpNodeParent = pNodeDest;
    pNewNode->mColor = pNodeSource->mColor;
    pNodeDest->mpNodeLeft = pNewNode;
    if (pNodeSource->mpNodeRight)
      pNewNode->mpNodeRight = DoCopySubtree((const IntStringNode*)pNodeSource->mpNodeRight, pNewNode);
    pNodeDest = pNewNode;
    pNodeSource = (const IntStringNode*)pNodeSource->mpNodeLeft;
  }
  return pNewNodeRoot;
}

// ------------------------------------------------------------------ map<string8, V> insert
struct StrKeyedValue {
  string8 first;  // key; the mapped part follows
};
struct StrNode : RBNodeBase {
  string8 key;  // +0x10
};
struct Iter { RBNodeBase* mpNode; };
struct InsertResult { RBNodeBase* first; bool second; };

extern int __cdecl FUN_005f7870(const char* a, const char* b, unsigned n);          // eastl::Compare(char*, char*, n)
extern RBNodeBase* __cdecl RBTreeDecrement(RBNodeBase* p);                           // 0x009215c0
extern bool __cdecl StringLess(const string8* a, const string8* b);                  // 0x00812210 (operator<)

struct StrMap {
  int mDummy;
  RBNodeBase mAnchor;  // +4: right, +8: left, +0x0c: parent
  unsigned mnSize;
  Iter __thiscall DoInsertValueImpl(RBNodeBase* pParent, const StrKeyedValue& value, bool bForceToLeft);  // 0x00b1a600
  InsertResult insert(const StrKeyedValue& value, int unusedArg);
};

// @ 0x00b1aba0
InsertResult StrMap::insert(const StrKeyedValue& value, int unusedArg) {
  InsertResult result;
  StrNode* pCurrent = (StrNode*)mAnchor.mpNodeParent;
  RBNodeBase* pLowerBound = &mAnchor;
  bool bValueLessThanNode = true;
  const char* kb = value.first.mpBegin;
  int kLen = (int)(value.first.mpEnd - value.first.mpBegin);
  while (pCurrent) {
    int nLen = (int)(pCurrent->key.mpEnd - pCurrent->key.mpBegin);
    int minLen = nLen < kLen ? nLen : kLen;
    int n = FUN_005f7870(kb, pCurrent->key.mpBegin, minLen);
    if (!n) {
      if (kLen < nLen) n = -1;
      else n = kLen > nLen ? 1 : 0;
    }
    bValueLessThanNode = n < 0;
    pLowerBound = pCurrent;
    if (bValueLessThanNode) pCurrent = (StrNode*)pCurrent->mpNodeLeft;
    else pCurrent = (StrNode*)pCurrent->mpNodeRight;
  }
  RBNodeBase* pParent = pLowerBound;
  if (bValueLessThanNode) {
    if (pLowerBound != mAnchor.mpNodeLeft) {
      pLowerBound = RBTreeDecrement(pLowerBound);
    } else {
      Iter i = DoInsertValueImpl(pParent, value, false);
      result.first = i.mpNode;
      result.second = true;
      return result;
    }
  }
  if (StringLess(&((StrNode*)pLowerBound)->key, &value.first)) {
    Iter i = DoInsertValueImpl(pParent, value, false);
    result.first = i.mpNode;
    result.second = true;
    return result;
  }
  result.first = pLowerBound;
  result.second = false;
  return result;
}

// ------------------------------------------------------------------ map<int, vector<Elem38>>
struct IntVecPair {  // eastl::pair<int, vector<Elem38>>
  int first;
  Elem38Vector second;
  IntVecPair(const IntVecPair& x) : first(x.first), second(x.second) {}
};

struct IntVecMap {
  int mDummy;
  IntVecNode* __thiscall DoCreateNodeCopy(const IntVecNode* src, IntVecNode* parent);  // 0x00b1aca0
  IntVecNode* DoCopySubtree(const IntVecNode* src, IntVecNode* dest);                   // 0x00b1b6c0
  void DoNuke(IntVecNode* pNode);                                                       // 0x00b1b830
};

// @ 0x00b1aca0
IntVecNode* IntVecMap::DoCreateNodeCopy(const IntVecNode* src, IntVecNode* parent) {
  const IntVecNode* s = src;
  IntVecNode* node = (IntVecNode*)SPORE_ALLOC(0x28);
  new ((void*)&node->first) IntVecPair(*(const IntVecPair*)&s->first);
  node->mpNodeParent = parent;
  node->mpNodeRight = 0;
  node->mpNodeLeft = 0;
  node->mColor = src->mColor;
  return node;
}

// @ 0x00b1add0
// Finds the game-data object (of the given kind) whose position component is closest to the camera anchor.
struct IPositionComponent {
  virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5();
  virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10();
  virtual const float* GetPosition();  // +0x2c
};
struct IGameData {
  virtual void p0(); virtual void p1(); virtual void p2();
  virtual IPositionComponent* QueryInterface(unsigned id);  // +0xc
};
struct GameDataPtrVec { IGameData** mpBegin; IGameData** mpEnd; IGameData** mpCapacity; };
struct GameDataVector { int pad; GameDataPtrVec vec; };  // vector at +4
struct cTerrainCameraController {
  const float* __thiscall GetAnchorDirection1();  // 0x00b10260
};
struct cGameNounManager {
  GameDataVector* __thiscall FUN_00b21340(void (*fa)(), void (*fb)(), void (*fc)(), void (*fd)(), int kind);  // 0x00b21340
};
cTerrainCameraController* GetTerrainCameraController();  // 0x00b3d280
cGameNounManager* NounManager();                         // 0x00b3d300
bool __cdecl GameDataMatches(IGameData* obj, int flags);  // 0x00b18f90 (ecx = obj)
void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00b1a4c0(); void FUN_00b1e520();

IGameData* FindClosestGameData(int kind, int flags) {
  const float* a = GetTerrainCameraController()->GetAnchorDirection1();
  float ax = a[0], ay = a[1], az = a[2];
  IGameData* best = 0;
  float bestD = 0.0f;
  GameDataPtrVec* v = &NounManager()->FUN_00b21340(FUN_00cd7d10, FUN_00d3d420, FUN_00b1a4c0, FUN_00b1e520, kind)->vec;
  unsigned n = (unsigned)(v->mpEnd - v->mpBegin);
  for (unsigned i = 0; i < n; i++) {
    if (GameDataMatches(v->mpBegin[i], flags)) {
      IGameData* obj = v->mpBegin[i];
      IPositionComponent* comp = obj ? obj->QueryInterface(0x1186577) : 0;
      float d = 3.4028234663852886e+38f;
      if (comp) {
        const float* p = comp->GetPosition();
        float dy = p[1] - ay;
        float dx = p[0] - ax;
        float dz = p[2] - az;
        d = dz * dz + dy * dy + dx * dx;
      }
      if (!best || bestD > d) {
        best = v->mpBegin[i];
        bestD = d;
      }
    }
  }
  return best;
}

// @ 0x00b1b6c0
IntVecNode* IntVecMap::DoCopySubtree(const IntVecNode* pNodeSource, IntVecNode* pNodeDest) {
  IntVecNode* pNewNodeRoot = DoCreateNodeCopy(pNodeSource, pNodeDest);
  if (pNodeSource->mpNodeRight)
    pNewNodeRoot->mpNodeRight = DoCopySubtree((const IntVecNode*)pNodeSource->mpNodeRight, pNewNodeRoot);
  pNodeDest = pNewNodeRoot;
  pNodeSource = (const IntVecNode*)pNodeSource->mpNodeLeft;
  while (pNodeSource) {
    IntVecNode* pNewNode = (IntVecNode*)SPORE_ALLOC(0x28);
    if (&pNewNode->first) {
      pNewNode->first = pNodeSource->first;
      unsigned n = (unsigned)(pNodeSource->second.mpEnd - pNodeSource->second.mpBegin);
      Elem38* data = n ? (Elem38*)SPORE_ALLOC(n * sizeof(Elem38)) : 0;
      pNewNode->second.mpBegin = data;
      pNewNode->second.mpEnd = data;
      pNewNode->second.mpCapacity = data + n;
      Elem38* dst = data;
      for (Elem38* p = pNodeSource->second.mpBegin; p != pNodeSource->second.mpEnd; ++p, ++dst)
        if (dst) new (dst) Elem38(*p);
      pNewNode->second.mpEnd = dst;
    }
    pNewNode->mpNodeRight = 0;
    pNewNode->mpNodeLeft = 0;
    pNewNode->mpNodeParent = pNodeDest;
    pNewNode->mColor = pNodeSource->mColor;
    pNodeDest->mpNodeLeft = pNewNode;
    if (pNodeSource->mpNodeRight)
      pNewNode->mpNodeRight = DoCopySubtree((const IntVecNode*)pNodeSource->mpNodeRight, pNewNode);
    pNodeDest = pNewNode;
    pNodeSource = (const IntVecNode*)pNodeSource->mpNodeLeft;
  }
  return pNewNodeRoot;
}

// @ 0x00b1b830
void IntVecMap::DoNuke(IntVecNode* pNode) {
  while (pNode) {
    DoNuke((IntVecNode*)pNode->mpNodeRight);
    Elem38* pEnd = pNode->second.mpEnd;
    Elem38* p = pNode->second.mpBegin;
    IntVecNode* pLeft = (IntVecNode*)pNode->mpNodeLeft;
    for (; p < pEnd; ++p) p->name.~string8();
    Elem38Free(pNode->second.mpBegin);
    delete[] (char*)pNode;
    pNode = pLeft;
  }
}

// ------------------------------------------------------------------ ArgScript state machine loader
struct string16 {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  ~string16() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) delete[] mpBegin;
  }
};
struct ResourceKey { unsigned instanceID, typeID, groupID; };
#define PV(n) virtual void pv##n();
struct IArgScriptParser {
  PV(0) PV(1)
  virtual void Reset();                                  // +8
  PV(3) PV(4)
  virtual void Declare(const char* name, void* owner);   // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void Parse(void* stream);                      // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  virtual void SetCheats(void* p);                       // +0xbc
};
struct IResourceManager {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  virtual void MakeKey(ResourceKey* out, const wchar_t* name, unsigned type, unsigned group);  // +0x78
};
struct ICheatInner {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  PV(47) PV(48)
  virtual void* GetCheatTable();  // +0xc4
};
struct ICheatManager {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual ICheatInner* GetInner();  // +0x38
};
IArgScriptParser* CreateParser();                               // 0x008408d0 (EA::ArgScript::CreateParser)
IResourceManager* GetManager();                                 // 0x0067dcd0
ICheatManager* CheatManager();                                  // 0x0067de20
string16* __cdecl ConvertToString16(string16* out, const char* in, int n);  // 0x0093c5a0
void* __cdecl OpenRecordAsStream(ResourceKey* key, void** outStream);       // 0x00686490
void __cdecl EraseEntry(void* rec);                                         // 0x006861d0

struct ParserPtrVector {
  IArgScriptParser** mpBegin;
  IArgScriptParser** mpEnd;
  IArgScriptParser** mpCapacity;
  ParserPtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~ParserPtrVector() { if (mpBegin) delete[] mpBegin; }
  void __thiscall DoInsertValue(IArgScriptParser** position, IArgScriptParser* const& value);  // 0x00b96600
  void push_back(IArgScriptParser* const& value) {
    if (mpEnd < mpCapacity) {
      IArgScriptParser** p = mpEnd;
      ++mpEnd;
      if (p) *p = value;
    } else {
      DoInsertValue(mpEnd, value);
    }
  }
};

struct StrNodeRoot { RBNodeBase* anchorRight; RBNodeBase* anchorLeft; RBNodeBase* parent; char color; unsigned size; };
struct StrNukeMap {
  int mDummy;
  RBNodeBase mAnchor;
  unsigned mnSize;
  void __thiscall DoNuke(RBNodeBase* pNode);  // 0x00e84940
};
extern StrNukeMap gScriptNames;  // 0x015682ec
extern void* gScriptOwner;       // 0x0167be94
extern IArgScriptParser* gScriptParser;  // 0x0167be98

struct cStateMachineHost {
  char pad[0x10];
  struct { char pad[0x30]; void* mpOwner; }* mpInfo;  // +0x10
  void LoadStateMachine(const char* name);           // 0x00b1b410
};

// @ 0x00b1b410
// (the PDB names this address InitCreatureHitBoxes, but the body parses an ArgScript state-machine resource)
void cStateMachineHost::LoadStateMachine(const char* name) {
  static ParserPtrVector sParserStack;
  gScriptOwner = mpInfo->mpOwner;
  sParserStack.push_back(gScriptParser);
  gScriptParser = CreateParser();
  ResourceKey key = {0, 0, 0};
  void* stream = 0;
  IResourceManager* mgr = GetManager();
  {
    string16 tmp;
    wchar_t* w = ConvertToString16(&tmp, name, -1)->mpBegin;
    mgr->MakeKey(&key, w, 0x24a0e52, 0x24a4f5a);
  }
  void* rec = OpenRecordAsStream(&key, &stream);
  gScriptParser->Reset();
  gScriptParser->Declare("DeclareState", this);
  gScriptParser->Declare("DeclareMenu", this);
  gScriptParser->Declare("DeclareMessage", this);
  gScriptParser->Declare("AddTransition", this);
  gScriptParser->Declare("IncludeMachine", this);
  gScriptParser->SetCheats(CheatManager()->GetInner()->GetCheatTable());
  gScriptParser->Parse(stream);
  EraseEntry(rec);
  gScriptParser = *(sParserStack.mpEnd - 1);
  --sParserStack.mpEnd;
  if (!gScriptParser) {
    gScriptOwner = 0;
    gScriptNames.DoNuke(gScriptNames.mAnchor.mpNodeParent);
    gScriptNames.mAnchor.mpNodeRight = &gScriptNames.mAnchor;
    gScriptNames.mAnchor.mpNodeLeft = &gScriptNames.mAnchor;
    gScriptNames.mAnchor.mpNodeParent = 0;
    gScriptNames.mAnchor.mColor = 0;
    gScriptNames.mnSize = 0;
  }
}

// ------------------------------------------------------------------ input message handler
struct Vec3 { float x, y, z; };
struct Variant {
  char data[16];     // +0: pointer to an external string8 when (flags & 0x30)
  uint16_t flags;    // +0x10
  uint16_t typeId;   // +0x12
  Variant& __thiscall operator=(const Variant& rhs);  // 0x00542b80
  void __thiscall Destruct(bool b);                   // 0x0093db80
};
struct IMsgArgs {  // Y
  PV(0) PV(1) PV(2) PV(3)
  virtual unsigned Count();                 // +0x10
  PV(5) PV(6)
  virtual const Variant& Get(unsigned i);   // +0x1c
};
struct IMsgTarget {  // X
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void Reset(int a);  // +0x2c
};
struct IMessage {
  PV(0) PV(1) PV(2) PV(3)
  virtual IMsgArgs* GetArgs();       // +0x10
  virtual IMsgTarget* GetTarget();   // +0x14
};
struct ITerrainSource {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void GetPosition(Vec3* out, int a);  // +0x3c
};
struct ITerrainCursor {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual void WorldToTerrain(Vec3* p);  // +0x38
};
struct cTerrainCursor { char pad[0x34]; ITerrainCursor mCursor; };  // +0x34
struct cTribeInputStrategy {
  void Init();  // 0x00cd0aa0
};
struct cTribeModeStrategy {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  virtual cTribeInputStrategy* GetInputStrategy(IGameData* obj);  // +0x70
  static cTribeModeStrategy* Instance();                          // 0x00cd40b0
};
struct cCameraCtl { void __thiscall FUN_00b13bb0(Vec3* p, int a); };  // 0x00b13bb0
struct cInputOwner {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual void OnInput(unsigned ev, int value, IGameData* obj, const Vec3* pos, unsigned objFlags, unsigned keyMod);  // +0x30
};

ITerrainSource* GetTerrainSource();             // 0x00b3d240
cTerrainCursor* GetGameTerrainCursor();         // 0x00b30d70
void* GetUniverseContext();                     // 0x01021080
unsigned GetCurrentGameMode();                  // 0x00b5b800
const Vec3* __cdecl FUN_00b19000();             // 0x00b19000 (flags in eax, out in edi)
bool __cdecl StrEqLiteral(const char* lit, const string8* s);  // 0x00b198f0
int __cdecl ParseEvent(const string8* s);       // 0x00b19a90
unsigned __cdecl ParseKeyMod(const string8* s); // 0x00b19a50
int __cdecl ParseValueFlag(const string8* s);   // 0x00b1a250
int __cdecl ParseValue(const string8* s);       // 0x00b19ef0
int __cdecl ParseObject(const string8* s);      // 0x00b1a290
unsigned __cdecl ParseObjectFlag(const string8* s);  // 0x00b19ad0
extern "C" int __cdecl sscanf(const char*, const char*, ...);

struct cInputHandler {  // lives at cInputOwner + 8
  virtual void h0();
  bool HandleMessage(unsigned msgID, IMessage* msg);  // 0x00b1af20
};

// @ 0x00b1af20
bool cInputHandler::HandleMessage(unsigned msgID, IMessage* msg) {
  if (msgID != 0x2168a93) return true;
  IMsgTarget* target = msg->GetTarget();
  IMsgArgs* args = msg->GetArgs();
  target->Reset(0);
  unsigned n = args->Count();
  unsigned eventId = 0xc;
  unsigned objFlags = 0, keyMod = 0;
  int value = 0;
  int objectKey = 0;
  IGameData* obj = 0;
  Vec3 pos;
  GetTerrainSource()->GetPosition(&pos, 0);
  bool havePos = false;
  if (n != 0) {
    for (unsigned i = 0; i < n; i++) {
      Variant v;
      v.typeId = 0x12;
      v.flags = 0xb;
      v = args->Get(i);
      const string8* s;
      if (v.typeId == 0x12 || v.typeId == 0x10) {
        if (v.flags & 0x30) s = *(string8**)v.data;
        else s = (const string8*)((-(unsigned)(v.typeId != 0)) & (unsigned)&v);
      } else {
        static string8 sEmpty;
        s = &sEmpty;
      }
      string8 text(s->mpBegin, s->mpEnd);
      if (v.flags & 4) v.Destruct(false);
      const char* p = text.mpBegin;
      for (; p != text.mpEnd; ++p) {
        const char* q = ":";
        do {
          if (*p == *q) goto found;
          ++q;
        } while (q != ":" + 1);
      }
      goto next;
    found:
      if (p != text.mpEnd) {
        int idx = (int)(p - text.mpBegin);
        if (idx != -1) {
          string8 key = text.substr(0, idx);
          string8 val = text.substr(idx + 1, (unsigned)(text.mpEnd - text.mpBegin));
          if (StrEqLiteral("TerrainPos", &key)) {
            float x, y, z;
            sscanf(val.mpBegin, "%f,%f,%f", &x, &y, &z);
            pos.x = x; pos.y = y; pos.z = z;
          } else if (StrEqLiteral("Event", &key)) {
            eventId = ParseEvent(&val);
          } else if (StrEqLiteral("KeyMod", &key)) {
            keyMod |= ParseKeyMod(&val);
          } else if (StrEqLiteral("Value", &key)) {
            if (eventId == 9) value = ParseValueFlag(&val);
            else value = ParseValue(&val);
          } else if (StrEqLiteral("Object", &key)) {
            objectKey = ParseObject(&val);
          } else if (StrEqLiteral("ObjectFlag", &key)) {
            objFlags |= ParseObjectFlag(&val);
          }
        }
      }
    next:;
    }
    if (objectKey != 0) {
      obj = FindClosestGameData(objectKey, objFlags);
      if (!obj) return true;
      IPositionComponent* comp = obj->QueryInterface(0x1186577);
      const float* pp = comp->GetPosition();
      Vec3 world;
      world.x = pp[0]; world.y = pp[1]; world.z = pp[2];
      GetGameTerrainCursor()->mCursor.WorldToTerrain(&world);
      if (GetTerrainCameraController() != 0) {
        ((cCameraCtl*)GetTerrainCameraController())->FUN_00b13bb0(&world, 0);
      }
      havePos = true;
    }
  }
  if (!havePos) {
    if (!GetUniverseContext()) {
      const Vec3* d = FUN_00b19000();
      pos.x = d->x; pos.y = d->y; pos.z = d->z;
    }
  }
  if (eventId != 0xc) {
    cInputOwner* owner = (cInputOwner*)((char*)this - 8);
    owner->OnInput(eventId, value, obj, &pos, objFlags, keyMod);
    if (GetCurrentGameMode() == 0x1654c02) {
      cTribeModeStrategy::Instance()->GetInputStrategy(obj)->Init();
    }
  }
  return true;
}
