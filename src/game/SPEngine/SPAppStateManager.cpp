// src/game/SPEngine/SPAppStateManager.cpp -- migrated from slice(s) s006a32a0, s007e5220, s007e4260, s007e32c0, s007e20a0, s007e17a0, s007e06b0, s006a7e40 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppStateManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cIFileParser.h"
#include "SP/cAppStateManager.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/Swarm/cDescription.h"
#include "EA/ArgScript/cError.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cExprFunction.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ---- items of slice s006a7e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  EASTL_allocator_deallocate(void* p);   // 0x00f47380
struct Str16 { void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator; };
struct Node  { Str16 mValue; uint32_t mSecond; Node* mpNext; };
struct HTable {
    // @ 0x006a85b0
    void DoFreeNodes(Node** pBucketArray, uint32_t n);
};
// ---- items of slice s006a7e40 end

// ---- items of slice s007e06b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VtblObj;
struct IRefCounted {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7();
};
struct cAppStateManager {
    char pad00[0x84];
    void* field84;              // +0x84
    void* field88;              // +0x88
    char pad8c[4];
    void** mpPrevBegin;         // +0x90
    void** mpPrevEnd;           // +0x94
    char pad98[0xa8];
    IRefCounted* field140;      // +0x140
    void* field144;             // +0x144
    void* field148;             // +0x148
    void* field14c;             // +0x14c
    void* field150;             // +0x150
    IRefCounted* field154;      // +0x154
    IRefCounted* field158;      // +0x158
    bool Shutdown();
    bool StateOccurredPreviously(void* p);
};
void __cdecl RemoveHandler(void* handler, void* a, void* b, void* c, void* d); // 0x00571db0
void* CheatManager();                                                          // 0x0067de20
struct VtblObj {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(int a, int b);   // +0x18
};
struct cForwarder {
    char pad[0x15c];
    VtblObj* p15c;
    VtblObj* p160;
    void Forward(int a, int b);
};
// ---- items of slice s007e06b0 end

// ---- items of slice s007e17a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_007e25a0(unsigned n, void* a, void* b); // 0x007e25a0
extern "C" void  FUN_007e1a50(void* a, void* b);             // 0x007e1a50
#undef CMDCLASS
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
void* operator new[](size_t size);
void  __cdecl EFree(void* p);                       // 0x00f47380
void* __cdecl EAlloc6(int size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
namespace eastl {
extern char gEmptyBuf[];
}
namespace eastl {
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    EString() : mpBegin(gEmptyBuf), mpEnd(gEmptyBuf), mpCapacity(gEmptyBuf + 1), mAllocator(0) {}
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    ~EString() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EFree(mpBegin); }
};
}
namespace EA {
namespace ArgScript {
class cArguments_s007e_17a0 {
public:
    const char** MainArguments(int n);                              // 0x00838320
    const char** MainArguments(int* pCount, int min, int max);      // 0x00838020
    const char** OptionArguments(const char* name, int n);          // 0x00838330
};
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s007e_17a0 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
    virtual void v36();                                            // +0x90
    virtual char  v37(const char* s);                              // +0x94
    virtual float v38(const char* s);                              // +0x98
    virtual int   v39(const char* s);                              // +0x9c
    virtual int   v40(const char* s);                              // +0xa0
};
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s007e_17a0 {
virtual void i0();
virtual void i1();
virtual void i2();
virtual void i3();
virtual void i4();
virtual void i5();
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s007e_17a0 : cICommand_s007e_17a0 {
    cCommandBase_s007e_17a0();                                                 // 0x0083c800
    virtual void AddCommand(void* key, void* cmd);                  // +0x18
    cIParser_s007e_17a0* mParser;      // +0x4
    int       mRefCount;    // +0x8
};
}
}
namespace EA {
namespace ArgScript {
void MakeCaseInsensitive(eastl::EString* s);                        // 0x008409b0
}
}
struct RefObj {
virtual void r0();
virtual void r1();
virtual void r2();
virtual void r3();
};
struct AutoRef {
    RefObj* p;
    int     field4;
};
struct AutoRefVal {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCapacity;
    void DoInsertValue(AutoRef* pos, const AutoRef* v);   // 0x007e1340
};
static inline void AddRefObj(RefObj* p) {
    if (p) ((void(__thiscall*)(RefObj*))(*(void***)p)[1])(p);
}
static inline void ReleaseObj(RefObj* p) {
    if (p) ((void(__thiscall*)(RefObj*))(*(void***)p)[2])(p);
}
static inline void ReleaseRef(RefObj* p) {
    if (p) ((void(__thiscall*)(RefObj*))(*(void***)p)[0])(p);
}
struct cStateFlagCommand : EA::ArgScript::cCommandBase_s007e_17a0 {
    void* mpState;   // +0xc
    void Execute(EA::ArgScript::cArguments_s007e_17a0& args);
};
struct cStateFlag2Command : EA::ArgScript::cCommandBase_s007e_17a0 {
    void* mpState;
    void Execute(EA::ArgScript::cArguments_s007e_17a0& args);
};
struct cSetStateCommand : EA::ArgScript::cCommandBase_s007e_17a0 {
    void* mpState;
    void Execute(EA::ArgScript::cArguments_s007e_17a0& args);
};
struct HashTable {
    char pad0[4];
    int*   mpBuckets;      // +0x4
    int    mnBucketCount;  // +0x8
    int    mnElementCount; // +0xc
    void   rehash(int n);
};
void EAllocAndZero(void* dst, int zero, unsigned size);  // 0x011e073e
struct SomeDesc {
    char*  a0;  char* a1;    // +0x0  string1 (begin/end)
    char*  a8;  char* ac;    // +0x8  string2
    int    a10; void* a14; void* a18;   // +0x10 vector
    void*  a1c;              // +0x1c (alignment hole)
    void*  p20;              // +0x20
    ~SomeDesc();
};
void* operator new(size_t, const char*, int, int, int, int);
struct HKey {
    RefObj* p;       // +0x0
    int     field4;  // +0x4
    int     field8;  // +0x8
};
struct HashNode {
    HKey       key;      // +0x0 .. +0xb
    HashNode*  mpNext;   // +0xc
};
struct HashGrowResult {
    uint8_t need;        // +0x0
    int     newCount;    // +0x4
};
struct HashGrow {
    void grow(HashGrowResult* out, int buckets, int elements, int flag);  // 0x00921440
};
struct HashTable3 : HashTable {
    void* insert(void* pOut, const HKey* key, void* hint);
};
struct cTransitionListCommand : EA::ArgScript::cCommandBase_s007e_17a0 {
    void* mpState;
    void Execute(EA::ArgScript::cArguments_s007e_17a0& args);
};
struct cStateNameMap {
    char pad0[4];
    int* mpBuckets;      // +0x4
    int  mnBucketCount;  // +0x8
    int  mnElementCount; // +0xc
};
struct cAppStateManagerX {
    char pad00[0xf8];
    cStateNameMap mMap;         // +0xf8
    char pad104[0x60];
    eastl::EString mName;       // +0x164
    int StateIDFromName(const char* name);
    cAppStateManagerX* CopyCtor(char* src);      // 0x007e2ae0
};
void hashtablefind(void* out, void* table, eastl::EString* key);  // 0x007e2ea0
struct cStateNameTable {
    char  pad0[4];
    int*  mpBuckets;      // +0x4
    int   mnBucketCount;  // +0x8
    void  find(void* out, const void* key);   // 0x007e2960 (thiscall)
};
struct cTransitionMgr {
    void FUN_007e2ce0(int idx);   // 0x007e2ce0
    void FUN_007e30a0(int a, int b);
};
void hashfind2(void* out, void* table, void* key); // 0x007e2960
struct VecCopy2 {                                    // vector<AutoRef>-style copy ctor target
    void copyCtorFrom(const void* src);              // 0x007e2520
};
struct RawVec {
    char* mpBegin; char* mpEnd; char* mpCap; void* mpAlloc;
    void DoAllocate(int n, const void* alloc);       // 0x006a40a0
};
struct RawStr {
    char* mpBegin; char* mpEnd; char* mpCap;
    void RangeInitialize(unsigned n);                // 0x00475ab0
};
void* eastl_copy(void* out, void* f, void* l, void* d, void* a); // 0x0076ffd0
void* memcpyE(void* dst, const void* src, size_t n); // 0x011e0744
void* MessageServer();                             // 0x0067dcc0
void* EffectsManager();                            // 0x0067ddd0
void SetMessageString8(void* msg, int a, void* s); // 0x00618bd0
struct AVec {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCapacity;
    AutoRef* grow(unsigned n, const AutoRef* first, const AutoRef* last);  // 0x007e25a0
    void     destroy(AutoRef* first, AutoRef* last);                       // 0x007e1a50
    AutoRef* assign(const AVec* o);
};
// ---- items of slice s007e17a0 end

// ---- items of slice s007e20a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];
void EASTL_allocator_deallocate(void* p) throw();
struct string8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  struct allocator {} mAllocator;
  const char* c_str() const { return mpBegin; }
  ~string8() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
};
struct string16 {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  struct allocator {} mAllocator;
  string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
  ~string16() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
};
bool FUN_00931fa0(const wchar_t* path);
string8 FUN_0093c440(const wchar_t* s, int len);
string8 FUN_0093c570(const string16& s);
struct ICommandLine {
  int FindSwitch(const wchar_t* name, int a, string16* value, int b);
};
struct IAppProps {
  virtual void v00();
  virtual void v04();
  virtual void Init();
  virtual void v0c();
  virtual void SetOwner(void* p);
  virtual void v14();
  virtual void Reset();
  virtual void Load(const char* path, int flags);
  virtual void Finish();
};
struct IDemoQuery {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual bool IsDemo();
};
IDemoQuery* FUN_0067dd00();
void* FUN_00840940();
struct PropsPtr {
  IAppProps* p;
  IAppProps* operator->() const { return p; }
  void Assign(void* q);
};
class cModeManager {
public:
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24();
  virtual void SetActiveMode(int id);
  virtual void v2c(); virtual void v30(); virtual void v34();
  virtual int GetModeID(const char* name);

  bool FUN_007e20a0(const wchar_t* path, ICommandLine* cmd, bool flag);

  char pad04[0x81 - 4];
  bool mFlag81;
  char pad82[0x154 - 0x82];
  PropsPtr mProps;
  void* mOwner;
};
// ---- items of slice s007e20a0 end

// ---- items of slice s007e32c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct EString_s007e_32c0 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    EString_s007e_32c0& operator=(const EString_s007e_32c0& o) { if (&o != this) assign(o.mpBegin, o.mpEnd); return *this; }
};
}
namespace EA {
namespace ArgScript {
class cArguments_s007e_32c0 {
public:
    const char** MainArguments(int n);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
    const char** MainArguments(int* pCount, int min, int max);  // 0x00838020 (EA::ArgScript::cArguments::MainArguments)
    const char** OptionArguments(const char* name, int n);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
    bool HasFlag(const char* name);                     // 0x008380b0
};
}
}
struct AMVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* a10;
    void* a14;
    AMVec& operator=(const AMVec& o);
};
struct cActionMessage;
struct cActions {
    AMVec           mEntryMessages;    // +0x00
    AMVec           mExitMessages;     // +0x14
    AMVec           mHandler;          // +0x28
    eastl::EString_s007e_32c0  mName;             // +0x3c
    int             field4c;           // +0x4c
    cActions& operator=(const cActions& o);
};
struct cActionMessage {
    RefObj* p;
    int     flag;
};
struct AMVecFull {
    cActionMessage* mpBegin;
    cActionMessage* mpEnd;
    cActionMessage* mpCapacity;
    cActionMessage* a10;
    cActionMessage* a14;
    __declspec(noinline) void push_back(const cActionMessage* m);   // 0x007e3d90
    void grow(cActionMessage* pos, const cActionMessage* m);  // 0x007e32c0
};
struct cAppState {
    char pad00[0x14];
    int  field14;            // +0x14
    char pad18[0x14];
    AMVecFull mMsgs;         // +0x2c  (begin/end/cap at +0x2c/+0x30/+0x34)
    AMVecFull mExitMsgs;     // +0x40
    char pad54[0x2c];
    uint8_t field80;         // +0x80
    uint8_t field81;         // +0x81
    void AddAction(EA::ArgScript::cArguments_s007e_32c0* args, RefObj* msg);
    void AddMessage(EA::ArgScript::cArguments_s007e_32c0* args, RefObj* msg, char c);
};
void AMVecFull_push_back(AMVecFull* v, const cActionMessage* m);  // 0x007e3d90
void FUN_007e32c0(AMVecFull* v, cActionMessage* pos, const cActionMessage* m); // 0x007e32c0
// ---- items of slice s007e32c0 end

// ---- items of slice s007e4260 begin (TODO(rewrite): local stubs, replace by canonical classes)

long  _InterlockedExchange(volatile long* target, long value);
namespace EA {
namespace ArgScript {
class cArguments_s007e_4260 {
public:
    const char** MainArguments(int n);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
    const char** MainArguments(int* pCount, int min, int max);  // 0x00838020 (EA::ArgScript::cArguments::MainArguments)
    const char** OptionArguments(const char* name, int n);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
    bool HasFlag(const char* name);  // 0x008380b0 (EA::ArgScript::cArguments::HasFlag)
};
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s007e_4260 {
virtual void i0();
virtual void i1();
virtual void i2();
virtual void i3();
virtual void i4();
virtual void i5();
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s007e_4260 : cICommand_s007e_4260 {
    virtual void AddCommand(void* key, void* cmd);
    void* mParser;
    int   mRefCount;
    ~cCommandBase_s007e_4260();
};
}
}
void SetMessageString8(void* msg, int a, const char* s);   // 0x00618bd0
void* cAppStateManager_AddAction(void* self, EA::ArgScript::cArguments_s007e_4260* args, void* msg); // 0x007e40d0
struct BehaviorMessageBase {
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
    int mRefCount;          // +0x4
};
struct BehaviorMessage : BehaviorMessageBase {
    virtual void b4();      // gives the derived level its own vtable
    char pad08[0x28];
    int  field30;           // +0x30 message id
    int  field34;           // +0x34
    int  field38;           // +0x38
    BehaviorMessage() : field30(0), field38(0) { _InterlockedExchange((volatile long*)&mRefCount, 0); }
};
static inline BehaviorMessage* NewBehaviorMessage(int msgid) {
    BehaviorMessage* m = new ("App", 0, 0, 0, 0) BehaviorMessage();
    m->field30 = msgid;
    return m;
}
struct cAppStateCmd : EA::ArgScript::cCommandBase_s007e_4260 {
    void* mpState;   // +0xc
};
// ---- items of slice s007e4260 end

// ---- items of slice s007e5220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVtbl_13eb384; extern void* gVtbl_13ef094; extern void* gVtbl_1413628;
extern void* gVtbl_1413614; extern void* gVtbl_1413610; extern void* gVtbl_154df28;
extern char  gEmptyStringData[];      // 0x01667bac (empty string byte)
extern char  gEmptyStringObj[];       // 0x013ec47c (empty eastl::string)
void FUN_007e5a30(void* p);
void* FUN_007e30f0(void* p);
void* FUN_007e3e20(void* first, void* end, void* last);
void StringAssign(void* self, const void* s);
struct EaStringOps {
    void assign(const char* first, const char* last);  // 0x454cb0
};
void MakeCaseInsensitive(void* p);
struct cAppStateManagerC { void* ctor(); };
void* SP_CheatManager();
struct cStateCommandC { void OnEndBlock(char arg); };
struct cTransitionCommandC { void OnEndBlock(char arg); };
// ---- items of slice s007e5220 end

// ---- items of slice s006a32a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ArgScript {
class cExprFunction_s006a_32a0 {
public:
    void** vftable;     // +0x0
    int mRefCount;      // +0x4
    bool EvalBool(int a, int b);  // 0x006a32a0 (EA::ArgScript::cExprFunction::EvalBool)
};
}
}
// ---- items of slice s006a32a0 end

// @ 0x006a32a0
bool EA::ArgScript::cExprFunction_s006a_32a0::EvalBool(int a, int b)
{
    return ((int (__thiscall*)(cExprFunction_s006a_32a0*, int, int))vftable[1])(this, a, b) != 0;
}

// @ 0x006a85b0
void HTable::DoFreeNodes(Node** pBucketArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        Node* p = pBucketArray[i];
        while (p) {
            Node* pNode = p;
            p = p->mpNext;
            if ((int)((char*)pNode->mValue.mpCapacity - (char*)pNode->mValue.mpBegin) > 1 && pNode->mValue.mpBegin)
                EASTL_allocator_deallocate(pNode->mValue.mpBegin);
            EASTL_allocator_deallocate(pNode);
        }
        pBucketArray[i] = 0;
    }
}

// @ 0x007e1650
bool cAppStateManager::Shutdown()
{
    if (field140) {
        void* h = field140;
        field140 = 0;
        RemoveHandler(h, field144, field148, field14c, field150);
    }
    if (field84) {
        void* cm = CheatManager();
        ((void(__thiscall*)(void*, void*))(*(void***)cm)[7])(cm, field84);
        field84 = 0;
    }
    if (field154) {
        field154->v3();
        IRefCounted* p = field154;
        if (p) {
            field154 = 0;
            p->v1();
        }
    } else if (field158) {
        field158->v3();
        IRefCounted* p = field158;
        if (p) {
            field158 = 0;
            p->v1();
        }
    }
    return true;
}

// @ 0x007e1710
bool cAppStateManager::StateOccurredPreviously(void* p)
{
    int n = (int)((mpPrevEnd - mpPrevBegin)) - 1;
    if (n >= 0) {
        void** it = mpPrevBegin + n;
        do {
            if (*it == p)
                return true;
            if (*it == field88)
                break;
            --n;
            --it;
        } while (n >= 0);
    }
    return false;
}

// @ 0x007e1760
void cForwarder::Forward(int a, int b)
{
    p15c->v6(a, b);
    p160->v6(a, b);
}

// @ 0x007e17a0
AutoRef* FUN_007e17a0(AutoRef** out, const AutoRef* first, const AutoRef* last, AutoRef* dst)
{
    *out = dst;
    for (; first != last; ++first) {
        if (dst) {
            dst->p = first->p;
            AddRefObj(first->p);
            dst->field4 = first->field4;
        }
        ++dst;
        *out = dst;
    }
    return (AutoRef*)out;
}

// @ 0x007e1830
AutoRef* FUN_007e1830(const AutoRef* first, const AutoRef* last, AutoRef* dst)
{
    for (; first != last; ++first) {
        if (dst) {
            dst->p = first->p;
            AddRefObj(first->p);
            dst->field4 = first->field4;
        }
        ++dst;
    }
    return dst;
}

// @ 0x007e1910
void cStateFlagCommand::Execute(EA::ArgScript::cArguments_s007e_17a0& args)
{
    args.MainArguments(0);
    *(uint8_t*)((char*)mpState + 0x80) = 0;
}

// @ 0x007e1930
void cStateFlag2Command::Execute(EA::ArgScript::cArguments_s007e_17a0& args)
{
    args.MainArguments(0);
    *(uint8_t*)((char*)mpState + 0x80) = 1;
}

// @ 0x007e1950
void HashTable::rehash(int n)
{
    unsigned size = n * 4;
    char* p = (char*)EAlloc6((int)(size + 4), "App", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    EAllocAndZero(p, 0, size);
    *(uint32_t*)(p + size) = 0xffffffff;
    unsigned i = 0;
    if (mnBucketCount != 0) {
        do {
            char* link = (char*)mpBuckets + i * 4;
            char* node = *(char**)link;
            while (node) {
                unsigned h = (*(uint32_t*)(node + 4) ^ *(uint32_t*)node) % n;
                *(char**)link = *(char**)(node + 0xc);
                *(char**)(node + 0xc) = *(char**)(p + h * 4);
                *(char**)(p + h * 4) = node;
                node = *(char**)link;
            }
            ++i;
        } while (i < (unsigned)mnBucketCount);
    }
    if (mnBucketCount > 1)
        EFree(mpBuckets);
    mpBuckets = (int*)p;
    mnBucketCount = n;
}

// @ 0x007e1a10
void cSetStateCommand::Execute(EA::ArgScript::cArguments_s007e_17a0& args)
{
    args.MainArguments(0);
    *(int*)((char*)mpState + 0x7c) = -1;
}

// @ 0x007e1a80
SomeDesc::~SomeDesc()
{
    RefObj* p = (RefObj*)p20;
    if (p)
        ((void(__thiscall*)(RefObj*))(*(void***)p)[1])(p);
    if ((int)((char*)a18 - (char*)a10) > 1 && a10)
        EFree((void*)a10);
    if ((int)((char*)a8 - (char*)a0) > 1 && a0)
        EFree((void*)a0);
}

// @ 0x007e1b00
AutoRef* FUN_007e1b00(AutoRef* first, AutoRef* last, AutoRef* dst)
{
    if (first == last)
        return dst;
    do {
        RefObj* src = first->p;
        RefObj* oldp = dst->p;
        if (src != oldp) {
            AddRefObj(src);
            dst->p = src;
            ReleaseObj(oldp);
        }
        dst->field4 = first->field4;
        ++first;
        ++dst;
    } while (first != last);
    return dst;
}

// @ 0x007e20a0
bool cModeManager::FUN_007e20a0(const wchar_t* path, ICommandLine* cmd, bool flag)
{
  mFlag81 = flag;
  if (!path || !FUN_00931fa0(path))
    return false;
  if (!mProps.p) {
    mProps.Assign(FUN_00840940());
    mProps->Init();
    IAppProps* p = mProps.p;
    void* o = mOwner;
    p->SetOwner(o);
  } else {
    mProps->Reset();
  }
  mProps->Load(FUN_0093c440(path, -1).c_str(), 5);
  mProps->Finish();

  if (cmd->FindSwitch(L"preload", 0, 0, 0) != -1) {
    int id = GetModeID("Preload");
    if (id != -1)
      SetActiveMode(id);
  }

  string16 state;
  int id;
  if (FUN_0067dd00()->IsDemo()) {
    id = GetModeID("Demo");
  } else if (cmd->FindSwitch(L"state", 0, &state, 0) != -1) {
    id = GetModeID(FUN_0093c570(state).c_str());
  } else {
    id = GetModeID("Main");
  }
  if (id != -1)
    SetActiveMode(id);
  return true;
}

// @ 0x007e29d0
void* HashTable3::insert(void* pOut, const HKey* key, void* hint)
{
    (void)hint;
    const HKey* k = key;
    uint32_t h0 = (uint32_t)k->p ^ (uint32_t)k->field4;
    unsigned hv = h0 % (unsigned)mnBucketCount;
    HashNode** slot0 = (HashNode**)(mpBuckets + hv);
    HashNode* node = *slot0;
    while (node) {
        if (node->key.p == k->p && node->key.field4 == k->field4) {
            *(HashNode**)pOut = node;
            *(uint8_t*)((char*)pOut + 8) = 0;
            *(HashNode***)((char*)pOut + 4) = slot0;
            return pOut;
        }
        node = node->mpNext;
    }
    HashGrowResult gr;
    ((HashGrow*)((char*)this + 0x10))->grow(&gr, mnBucketCount, mnElementCount, 1);
    node = (HashNode*)operator new(0x10, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (node) {
        node->key.p = k->p;
        node->key.field4 = k->field4;
        node->key.field8 = k->field8;
    }
    node->mpNext = 0;
    if (gr.need) {
        hv = h0 % (unsigned)gr.newCount;
        rehash(gr.newCount);
    }
    HashNode** slot = (HashNode**)(mpBuckets + hv);
    node->mpNext = *slot;
    *slot = node;
    mnElementCount = mnElementCount + 1;
    *(HashNode**)pOut = node;
    *(HashNode***)((char*)pOut + 4) = slot;
    *(uint8_t*)((char*)pOut + 8) = 1;
    return pOut;
}

// @ 0x007e2ae0
cAppStateManagerX* cAppStateManagerX::CopyCtor(char* src)
{
    ((VecCopy2*)this)->copyCtorFrom(src);
    ((VecCopy2*)((char*)this + 0x14))->copyCtorFrom(src + 0x14);
    RawVec* dstVec = (RawVec*)((char*)this + 0x28);
    int n = (*(int*)(src + 0x2c) - *(int*)(src + 0x28)) >> 3;
    dstVec->DoAllocate(n, src + 0x34);
    void* pEnd = 0;
    eastl_copy(&pEnd, src + 0x28, src + 0x2c, dstVec->mpBegin, src);
    dstVec->mpEnd = (char*)pEnd;
    RawStr* dstStr = (RawStr*)((char*)this + 0x3c);
    dstStr->mpBegin = 0;
    dstStr->mpEnd = 0;
    dstStr->mpCap = 0;
    unsigned len = *(int*)(src + 0x40) - *(int*)(src + 0x3c);
    dstStr->RangeInitialize(len + 1);
    memcpyE(dstStr->mpBegin, *(void**)(src + 0x3c), len);
    dstStr->mpEnd = dstStr->mpBegin + len;
    dstStr->mpBegin[len] = 0;
    *(int*)((char*)this + 0x4c) = *(int*)(src + 0x4c);
    return this;
}

// @ 0x007e2ce0
void cTransitionMgr::FUN_007e2ce0(int idx)
{
    cTransitionMgr* self = this;
    char* piVar5 = (char*)(*(int*)((char*)self + 0xa4) + idx * 0x50);
    MessageServer();
    unsigned n = (*(int*)(piVar5 + 4) - *(int*)piVar5) >> 3;
    unsigned i = 0;
    if (n != 0) {
        do {
            char* e = *(char**)piVar5 + i * 8;
            int iVar1 = *(int*)e;
            void* piVar2 = MessageServer();
            if ((e[4] & 1) == 0) {
                int p2 = *(int*)(iVar1 + 0x30);
                if (*(int*)((char*)self + 0x14) == 0)
                    ((void(__thiscall*)(void*, int, int, int, int))(*(void***)piVar2)[6])(piVar2, p2, iVar1, 0, (int)self + 4);
                else if (*(int*)((char*)self + 0x14) == 1)
                    ((void(__thiscall*)(void*, int, int, int))(*(void***)piVar2)[5])(piVar2, p2, iVar1, (int)self + 4);
            } else {
                int p2 = *(int*)(iVar1 + 0x30);
                if (*(int*)((char*)self + 0x14) == 0)
                    ((void(__thiscall*)(void*, int, int, int, int))(*(void***)piVar2)[6])(piVar2, p2, iVar1, 0, 0);
                else if (*(int*)((char*)self + 0x14) == 1)
                    ((void(__thiscall*)(void*, int, int, int))(*(void***)piVar2)[5])(piVar2, p2, iVar1, 0);
            }
            ++i;
        } while (i < (unsigned)((*(int*)(piVar5 + 4) - *(int*)piVar5) >> 3));
    }
    void* em = EffectsManager();
    if (em) {
        unsigned k = 0;
        unsigned m = (*(int*)(piVar5 + 0x2c) - *(int*)(piVar5 + 0x28)) >> 3;
        while (k < m) {
            char* e = *(char**)(piVar5 + 0x28) + k * 8;
            ((void(__thiscall*)(void*, int, uint8_t))(*(void***)em)[0x98 / 4])(em, *(int*)e, (uint8_t)e[4]);
            ++k;
        }
    }
    int f = *(int*)(piVar5 + 0x4c);
    if (f != -1)
        *(int*)((char*)self + 0x8c) = f;
    if (*(char*)((char*)self + 0x81) && *(int*)(piVar5 + 0x3c) != *(int*)(piVar5 + 0x40)) {
        void* msg = EAlloc6(0x40, "App", 0, 0, 0, 0);
        if (msg) {
            *(int*)((char*)msg + 0x30) = 0;
            *(void**)msg = (void*)0x13eb90c;
            *(int*)((char*)msg + 4) = 0;
            *(int*)((char*)msg + 0x38) = 0;
            *(void**)msg = (void*)0x13eb844;
        }
        SetMessageString8(msg, 0, (void*)*(int*)(piVar5 + 0x3c));
        *(void**)((char*)msg + 0x10) = self;
        void* ms = MessageServer();
        if (*(int*)((char*)self + 0x14) == 0)
            ((void(__thiscall*)(void*, int, void*, int, int))(*(void***)ms)[6])(ms, 0xe11331, msg, 0, 0);
        else if (*(int*)((char*)self + 0x14) == 1)
            ((void(__thiscall*)(void*, int, void*, int))(*(void***)ms)[5])(ms, 0xe11331, msg, 0);
    }
}

// @ 0x007e2fb0
void cTransitionListCommand::Execute(EA::ArgScript::cArguments_s007e_17a0& args)
{
    const char** av = args.MainArguments(2);
    int a = mParser->v39(av[0]);
    char b = mParser->v37(av[1]);
    AutoRef tmp;
    tmp.p = (RefObj*)a;
    ((char*)&tmp.field4)[0] = b;
    char* vec = (char*)mpState + 0x54;
    AutoRef* end = *(AutoRef**)(vec + 4);
    if (end < *(AutoRef**)(vec + 8)) {
        *(AutoRef**)(vec + 4) = end + 1;
        if (end) {
            *(uint32_t*)end = *(uint32_t*)&tmp.p;
            *(uint32_t*)((char*)end + 4) = *(uint32_t*)&tmp.field4;
        }
    } else {
        ((AutoRefVal*)vec)->DoInsertValue(end, &tmp);
    }
}

// @ 0x007e3030
int cAppStateManagerX::StateIDFromName(const char* name)
{
    const char* e = name;
    while (*e) ++e;
    mName.assign(name, e);
    EA::ArgScript::MakeCaseInsensitive(&mName);
    int it[2];
    hashtablefind(it, &mMap, &mName);
    if (it[0] != mMap.mpBuckets[mMap.mnBucketCount])
        return *(int*)((char*)it[0] + 0x10);
    return -1;
}

// @ 0x007e30a0
void cTransitionMgr::FUN_007e30a0(int a, int b)
{
    cTransitionMgr* self = this;
    int key[2];
    key[0] = a;
    key[1] = b;
    int it[2];
    cStateNameTable* tbl = (cStateNameTable*)((char*)self + 0xd8);
    tbl->find(it, key);
    if (it[0] != tbl->mpBuckets[tbl->mnBucketCount])
        self->FUN_007e2ce0(*(int*)((char*)it[0] + 8));
}

// @ 0x007e3160
AutoRef* AVec::assign(const AVec* o)
{
    AVec* self = this;
    if (o == self)
        return self->mpBegin;
    unsigned n = (unsigned)((o->mpEnd - o->mpBegin));
    unsigned cap = (unsigned)((self->mpCapacity - self->mpBegin));
    if (cap < n) {
        AutoRef* p = self->grow(n, o->mpBegin, o->mpEnd);
        self->destroy(self->mpBegin, self->mpEnd);
        if (self->mpBegin && *(int*)((char*)self->mpBegin - 4))
            EFree(self->mpBegin);
        self->mpCapacity = p + n;
        self->mpEnd = p + n;
        self->mpBegin = p;
        return (AutoRef*)self;
    }
    unsigned have = (unsigned)(self->mpEnd - self->mpBegin);
    if (have < n) {
        FUN_007e1b00(o->mpBegin, o->mpBegin + have, self->mpBegin);
        AutoRef* out = self->mpEnd;
        FUN_007e17a0(&out, o->mpBegin + have, o->mpEnd, self->mpEnd);
        self->mpEnd = self->mpBegin + n;
        return (AutoRef*)self;
    }
    AutoRef* e = FUN_007e1b00(o->mpBegin, o->mpEnd, self->mpBegin);
    self->destroy(e, self->mpEnd);
    self->mpEnd = self->mpBegin + n;
    return (AutoRef*)self;
}

// @ 0x007e32c0
void FUN_007e32c0(AMVecFull* v, cActionMessage* pos, const cActionMessage* m)
{
    (void)pos; (void)m; (void)v;
}

// @ 0x007e34a0
cActions& cActions::operator=(const cActions& o)
{
    mEntryMessages = o.mEntryMessages;
    mExitMessages = o.mExitMessages;
    mHandler = o.mHandler;
    mName = o.mName;
    field4c = o.field4c;
    return *this;
}

// @ 0x007e34f0
void FUN_007e34f0(void* self, EA::ArgScript::cArguments_s007e_32c0* args)
{
    (void)self; (void)args;
}

// @ 0x007e3610
void FUN_007e3610(void* self, void* msg)
{
    (void)self; (void)msg;
}

// @ 0x007e3b40
void FUN_007e3b40(void* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x007e3d90
void AMVecFull::push_back(const cActionMessage* m)
{
    cActionMessage* end = mpEnd;
    if (end >= mpCapacity) {
        grow(end, m);
        return;
    }
    mpEnd = end + 1;
    if (end) {
        end->p = m->p;
        if (end->p)
            ((void(__thiscall*)(RefObj*))(*(void***)end->p)[1])(end->p);
        end->flag = m->flag;
    }
}

// @ 0x007e3e20
cActions* FUN_007e3e20(cActions* first, cActions* last, cActions* dst)
{
    for (; first != last; ++first, ++dst)
        *dst = *first;
    return dst;
}

// @ 0x007e3e90
cActions* FUN_007e3e90(cActions* first, cActions* last, cActions* dstEnd)
{
    if (last != first) {
        do {
            --last;
            --dstEnd;
            *dstEnd = *last;
        } while (first != last);
    }
    return dstEnd;
}

// @ 0x007e3f00
void FUN_007e3f00(void* self, EA::ArgScript::cArguments_s007e_32c0* args)
{
    (void)self; (void)args;
}

// @ 0x007e40d0
void cAppState::AddAction(EA::ArgScript::cArguments_s007e_32c0* args, RefObj* msg)
{
    cAppState* self = this;
    bool exitPath = (args && args->HasFlag("onExit")) || self->field80;
    cActionMessage m;
    m.p = msg;
    if (msg)
        ((void(__thiscall*)(RefObj*))(*(void***)msg)[1])(msg);
    m.flag = 0;
    if (exitPath)
        self->mExitMsgs.push_back(&m);
    else
        self->mMsgs.push_back(&m);
    if (m.p)
        ((void(__thiscall*)(RefObj*))(*(void***)m.p)[2])(m.p);
}

// @ 0x007e4190
void cAppState::AddMessage(EA::ArgScript::cArguments_s007e_32c0* args, RefObj* msg, char c)
{
    cAppState* self = this;
    bool exitPath = (args && args->HasFlag("onExit")) || self->field80 || c;
    cActionMessage m;
    m.p = msg;
    if (msg)
        ((void(__thiscall*)(RefObj*))(*(void***)msg)[1])(msg);
    m.flag = 1;
    if (exitPath)
        self->mExitMsgs.push_back(&m);
    else
        self->mMsgs.push_back(&m);
    if (m.p)
        ((void(__thiscall*)(RefObj*))(*(void***)m.p)[2])(m.p);
}

// @ 0x007e4260
void FUN_007e4260(cAppStateCmd* self, EA::ArgScript::cArguments_s007e_4260* args)
{
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xe11330);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e42d0
void FUN_007e42d0(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007e44c0
void FUN_007e44c0(void* a)
{ (void)a; }

// @ 0x007e4550
void FUN_007e4550(cAppStateCmd* self, EA::ArgScript::cArguments_s007e_4260* args)
{
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xcef220e0);
    SetMessageString8(m, 0, av[0]);
    m->field34 = args->HasFlag("softStop") ? 1 : 0;
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e45e0
void FUN_007e45e0(cAppStateCmd* self, EA::ArgScript::cArguments_s007e_4260* args)
{
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xe11333);
    SetMessageString8(m, 0, av[0]);
    (void)self;
    (void)av;
    (void)m;
}

// @ 0x007e46f0
void FUN_007e46f0(cAppStateCmd* self, EA::ArgScript::cArguments_s007e_4260* args)
{
    const char** av = args->MainArguments(1);
    BehaviorMessage* m = NewBehaviorMessage(0xcef220e1);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e4760
void FUN_007e4760(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007e48f0
void FUN_007e48f0(cAppStateCmd* self, EA::ArgScript::cArguments_s007e_4260* args)
{
    BehaviorMessage* m = NewBehaviorMessage(0x6f188ef2);
    const char** av = args->MainArguments(1);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e4970
void FUN_007e4970(cAppStateCmd* self, EA::ArgScript::cArguments_s007e_4260* args)
{
    BehaviorMessage* m = NewBehaviorMessage(0x6f188ef8);
    const char** av = args->MainArguments(1);
    SetMessageString8(m, 0, av[0]);
    cAppStateManager_AddAction(self->mpState, args, m);
}

// @ 0x007e49f0
void FUN_007e49f0(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007e4a80
void FUN_007e4a80(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007e4b20
void FUN_007e4b20(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007e4bc0
void FUN_007e4bc0(void* a)
{ (void)a; }

// @ 0x007e4e00
void FUN_007e4e00(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007e4e90
void FUN_007e4e90(void* a)
{ (void)a; }

// @ 0x007e4f40
void FUN_007e4f40(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007e5220
void* cAppStateManagerC::ctor()
{
    char* p = (char*)this;
    *(void**)(p + 4)    = &gVtbl_13eb384;
    *(uint32_t*)(p + 0x10) = 0xceee7649;
    *(void**)(p + 8)    = &gVtbl_13ef094;
    *(uint32_t*)(p + 0xc)  = 0;
    *(void**)(p + 0)    = &gVtbl_1413628;
    *(void**)(p + 4)    = &gVtbl_1413614;
    *(void**)(p + 8)    = &gVtbl_1413610;
    *(uint32_t*)(p + 0x14) = 0;
    *(void**)(p + 0x18) = gEmptyStringData;
    *(void**)(p + 0x1c) = gEmptyStringData;
    *(void**)(p + 0x20) = gEmptyStringData + 1;
    *(uint32_t*)(p + 0x28) = 0xffffffff;
    *(uint32_t*)(p + 0x2c) = 0; *(uint32_t*)(p + 0x30) = 0; *(uint32_t*)(p + 0x34) = 0;
    *(uint32_t*)(p + 0x40) = 0; *(uint32_t*)(p + 0x44) = 0; *(uint32_t*)(p + 0x48) = 0;
    *(uint32_t*)(p + 0x54) = 0; *(uint32_t*)(p + 0x58) = 0; *(uint32_t*)(p + 0x5c) = 0;
    *(void**)(p + 0x68) = gEmptyStringData;
    *(void**)(p + 0x6c) = gEmptyStringData;
    *(void**)(p + 0x70) = gEmptyStringData + 1;
    *(uint32_t*)(p + 0x78) = 0xffffffff;
    *(uint32_t*)(p + 0x7c) = 0xffffffff;
    *(uint8_t*)(p + 0x80) = 0;
    *(uint8_t*)(p + 0x81) = 0;
    *(uint32_t*)(p + 0x84) = 0;
    *(uint32_t*)(p + 0x88) = 0xffffffff;
    *(uint32_t*)(p + 0x8c) = 0xffffffff;
    *(uint32_t*)(p + 0x90) = 0; *(uint32_t*)(p + 0x94) = 0; *(uint32_t*)(p + 0x98) = 0;
    *(uint32_t*)(p + 0xa4) = 0; *(uint32_t*)(p + 0xa8) = 0; *(uint32_t*)(p + 0xac) = 0;
    for (int off = 0xbc; off <= 0xfc; off += 0x20) {
        *(void**)(p + off)        = &gVtbl_154df28;
        *(uint32_t*)(p + off + 4) = 1;
        *(uint32_t*)(p + off + 8) = 0;
        *(float*)(p + off + 0xc)  = 1.0f;
        *(float*)(p + off + 0x10) = 2.0f;
        *(uint32_t*)(p + off + 0x14) = 0;
    }
    *(uint32_t*)(p + 0x118) = 0; *(uint32_t*)(p + 0x11c) = 0; *(uint32_t*)(p + 0x120) = 0;
    *(uint32_t*)(p + 0x12c) = 0; *(uint32_t*)(p + 0x130) = 0; *(uint32_t*)(p + 0x134) = 0;
    for (int off = 0x140; off <= 0x160; off += 4)
        *(uint32_t*)(p + off) = 0;
    *(void**)(p + 0x164) = gEmptyStringData;
    *(void**)(p + 0x168) = gEmptyStringData;
    *(void**)(p + 0x16c) = gEmptyStringData + 1;
    return p;
}

// @ 0x007e5430
void cAppStateManagerInit(void* self)
{
    (void)self;
    // Parser/command registration is not reconstructed (see partial.txt).
    (void)SP_CheatManager();
}

// @ 0x007e5830
void* cActionsEraseHelper(void* vec, void* first, void* last)
{
    char* v = (char*)vec;
    char* dst = (char*)FUN_007e3e20(last, *(void**)(v + 4), first);
    char* end = *(char**)(v + 4);
    while (dst < end) {
        FUN_007e5a30(dst);        // ~cActions
        dst += 0x50;
    }
    *(int*)(v + 4) += (int)(((char*)last - (char*)first) / 0x50) * 0x50;
    return first;
}

// @ 0x007e5890
void cActionsEraseRange(void* vec, void* first, void* last)
{
    (void)vec; (void)first; (void)last;
    // EASTL reallocating erase not reconstructed (see partial.txt).
}

// @ 0x007e5ab0
void cStateCommandC::OnEndBlock(char arg)
{
    char* self = (char*)this;
    if (arg == 0) {
        char* mgr = *(char**)(self + 0x30);
        int count = (*(int*)(mgr + 0xa8) - *(int*)(mgr + 0xa4)) / 0x50;
        FUN_007e5a30(mgr + 0x2c);
        MakeCaseInsensitive(mgr + 0x18);
        // hash_map operator[] / hashtable find not reconstructed (see partial.txt)
        *(int*)(mgr + 0x7c) = *(int*)(mgr + 0x28);
        (void)count;
    }
    *(uint8_t*)(*(char**)(self + 0x30) + 0x80) = 0;
    StringAssign(gEmptyStringObj, gEmptyStringObj);
    *(int*)(*(char**)(self + 0x30) + 0x28) = 0xffffffff;
}

// @ 0x007e5bc0
void cTransitionCommandC::OnEndBlock(char arg)
{
    char* self = (char*)this;
    if (arg == 0) {
        char* mgr = *(char**)(self + 0x30);
        int iVar2 = *(int*)(mgr + 0xa8);
        int iVar3 = *(int*)(mgr + 0xa4);
        int count = (iVar2 - iVar3) / 0x50;
        FUN_007e5a30(mgr + 0x2c);
        int local_4 = *(int*)(self + 0x38);
        int local_8 = *(int*)(self + 0x34);
        int* r = (int*)FUN_007e30f0(&local_8);
        (void)local_4;
        *r = count;
    }
    ((EaStringOps*)(*(char**)(self + 0x30) + 0x18))->assign(gEmptyStringObj, gEmptyStringObj);
}

// @ 0x007e5c40
void cAppStateManagerUpdate(void* self)
{
    (void)self;
    // EASTL hash-map state replay not reconstructed (see partial.txt).
}
