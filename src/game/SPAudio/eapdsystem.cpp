// src/game/SPAudio/eapdsystem.cpp -- migrated from slice(s) s00a670b0, s00a52ff0, s00a52080, s00a68140 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdsystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"

// unnamed retail callees and globals (address in the comment)
extern "C" extern float g_ten_k;                  // 0x13f0620
extern "C" extern float g_two;                    // 0x1470f1c
#include <intrin.h>
#include <math.h>
#include <string.h>
#include <new>

// ---- items of slice s00a68140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern char g_vtbl_1403934[];          // 0x01403934
extern "C" extern char g_vtbl_1454fac[];          // 0x01454fac
extern "C" extern char g_vtbl_14557f8[];          // 0x014557f8
extern "C" extern char g_vtbl_1455808[];          // 0x01455808
extern "C" extern char g_vtbl_145581c[];          // 0x0145581c
extern "C" extern char g_vtbl_1455828[];          // 0x01455828
extern "C" extern float g_0p05;                   // 0x01455768
extern "C" void FUN_00a646e0(int p);              // cdecl, one argument
extern "C" bool FUN_00a495e0();                   // cdecl, no arguments
extern "C" void FUN_00a53300(int p);              // cdecl, one argument
class IAlloc {
public:
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size);    // +0x08
    virtual void  Free(void* p);           // +0x0c
};
class PolSub   { public: int GetPoliticalID(); };                     // 0x005aacf0
class Sub240A  { public: int Get(); };                                // 0x00a1ad10
class Sub7cA   { public: void Fill(int* a, int* b, int* c); };        // 0x00a66c60 ret 0xc
class FileSub  { public: int GetFileCount(); };                       // 0x008e7f80
class Sub240B  { public: int StartTime(); };                          // 0x006c10e0
class Sub7cB   { public: void Fill(int* a, int* b, int* c); };        // 0x00a66c90 ret 0xc
class EapdInfo {
public:
    char pad[0x300];
    void GetInfoA(int* out);               // va 0xa68140
    void GetInfoB(int* out);               // va 0xa68190
};
struct LNode { LNode* next; LNode* prev; int key; };
class KeyList {
public:
    LNode* mNext;                          // +0x00
    LNode* mPrev;                          // +0x04
    IAlloc mAlloc;                         // +0x08
    void RemoveKey(const int* key);        // va 0xa68280
};
struct GEntry {                            // object passed in: key at +0x2c
    char pad0[0x2c];
    unsigned mKey;                         // +0x2c
    unsigned mA;                           // +0x30
    unsigned mB;                           // +0x34
    char pad1[0x40 - 0x38];
    GEntry* mNext;                         // +0x40
};
struct Group_s00a6_8140 {                             // value pair second: {key, head}, 8 bytes
    unsigned x;                            // +0x00
    GEntry*  head;                         // +0x04
    Group_s00a6_8140(GEntry* p);                      // 0x00a646f0 thiscall ret 4: x = p->0x34, head = p
    Group_s00a6_8140(const Group_s00a6_8140& g) : x(g.x), head(g.head) {}
    ~Group_s00a6_8140();                              // 0x00a64710
    bool RemoveEntry(GEntry* p);           // 0x00a64750 thiscall ret 4
    bool IsEmpty() const;                  // 0x00a647a0
    bool OpA(unsigned x);                  // 0x00a648f0 thiscall ret 4
    bool OpB();                            // 0x00a64950 thiscall
    bool Push(GEntry* p);                  // 0x00a64730 thiscall ret 4
};
struct HNode { HNode* next; Group_s00a6_8140 value; HNode* chain; };
struct HIter { HNode* node; HNode** bucket; };
struct PoolNode { PoolNode* next; int pad4; int pad8; PoolNode* chain; };
class SubObj { public: ~SubObj(); };       // 0x00a67d30
class NodePool {
public:
    unsigned pad0;
    PoolNode** mBuckets;                   // +0x04
    unsigned mBucketCount;                 // +0x08
    unsigned mElems;                       // +0x0c
    char padA[0x1c - 0x10];
    SubObj mSub;                           // +0x1c
    char padB[0x28 - 0x1d];
    IAlloc mAlloc;                         // +0x28
    char pad1[0x34 - 0x28 - sizeof(IAlloc)];
    unsigned mSize;                        // +0x34
    PoolNode* mBegin;                      // +0x38
    PoolNode* mEnd;                        // +0x3c
    PoolNode* mFree;                       // +0x40
    unsigned mCount;                       // +0x44
    unsigned mHigh;                        // +0x48
    char pad2[4];
    PoolNode* mSpecial;                    // +0x50
    void* Allocate(const int* src);        // va 0xa682d0
    void FreeChains(PoolNode** buckets, unsigned n);   // va 0xa68330
    ~NodePool();                           // va 0xa687f0
};
class Sub4 { public: void Destroy(); };    // 0x00a64710
class AllocRef : public IAlloc {
public:
    int mA, mB;
    AllocRef(int a, int b) : mA(a), mB(b) {}
    ~AllocRef() {}
};
class EapdSingleton {
public:
    virtual void* Dtor(int flag);          // slot 0
    int pad4;
    int mA;                                // +0x08
    int mB;                                // +0x0c
    unsigned char Shutdown();              // 0x00a678d0
};
extern "C" EapdSingleton* spEapdSystem;    // 0x16758d4
struct TaskNode { TaskNode* next; TaskNode* prev; void* value; };
class TaskList {
public:
    TaskNode* mNext;                       // +0x00
    TaskNode* mPrev;                       // +0x04
    IAlloc    mAlloc;                      // +0x08
    void PushBack(void* t)
    {
        TaskNode* n = (TaskNode*)mAlloc.Alloc(0xc);
        if (&n->value)
            n->value = t;
        n->next = (TaskNode*)this;
        n->prev = mPrev;
        mPrev->next = n;
        mPrev = n;
    }
};
class EapdTasks {
public:
    char pad[0x31c];
    TaskList mTasks;                       // +0x31c
    void PushTask(void* t);                // va 0xa685a0
};
struct Vec3F { float x, y; unsigned z; unsigned Fn(unsigned a); };       // Fn: 0x9213c0
class AssetMgr {
public:
    char pad[0x30];
    unsigned mCount;                       // +0x30
    bool Open(int a, int b, int c);        // 0x00a67d90 thiscall ret 0xc
};
class EapdAssets {
public:
    char pad0[8];
    unsigned m8;                           // +0x08
    unsigned mC;                           // +0x0c
    Vec3F    m10;                          // +0x10
    AssetMgr mAssets;                      // +0x1c
    void Grow(unsigned n);                 // 0x00a67f60 thiscall ret 4
    bool Init(int a, int b, int c);        // va 0xa685e0
};
struct GTable {
    unsigned pad0;
    HNode** mBuckets;                      // +0x04
    unsigned mBucketCount;                 // +0x08
    unsigned mElems;                       // +0x0c
    char padE[0x1c - 0x10];
    SubObj mSub;                           // +0x1c
    char padA[0x28 - 0x1d];
    IAlloc mAlloc;                         // +0x28
    char pad1[0x38 - 0x28 - 4];
    HNode* mBegin;                         // +0x38
    HNode* mEnd;                           // +0x3c
    HNode* mFree;                          // +0x40
    unsigned mCount;                       // +0x44
    unsigned mHigh;                        // +0x48
    char pad2[0x50 - 0x4c];
    HNode* mSpecial;                       // +0x50
    HIter find(const unsigned& key);       // 0x00685f30 thiscall sret ret 8
    HIter erase(HIter it);                 // va 0xa68430 thiscall sret ret 0xc
};
class IntrusiveListBase  { public: void* mpNext; void* mpPrev; ~IntrusiveListBase() throw(); };   // 0x00620230
class IntrusiveListBase2 { public: void* mpNext; void* mpPrev; ~IntrusiveListBase2() throw(); };          // 0x00620230
class FixedPoolT { public: char pad[0x30]; ~FixedPoolT(); };  // 0x00a531b0
class IInternalAllocator {
public:
    virtual ~IInternalAllocator() throw() {}   // vtable 0x1403934, slot 0
    virtual void* AllocateNamed(unsigned bytes, const char* name) = 0; // slot 1
    virtual void* Allocate(unsigned bytes) = 0;                       // slot 2
    virtual void Free(void* memory) = 0;                             // slot 3
};
class AllocatorT : public IInternalAllocator {
public:
    int pad4, pad8;
    virtual void* AllocateNamed(unsigned bytes, const char* name); // 0x00a52b40
    virtual void* Allocate(unsigned bytes);                       // 0x00a52b70
    virtual void Free(void* memory);                              // 0x00a52b90
};
class FixedAllocator : public FixedPoolT, public IInternalAllocator {
public:
    virtual void* AllocateNamed(unsigned bytes, const char* name); // 0x00a657f0
    virtual void* Allocate(unsigned bytes);                       // 0x00a64400
    virtual void Free(void* memory);                              // 0x00a65800
};
class CallbackManager {
public:
    AllocatorT         mAllocator;         // +0x00
    FixedAllocator     mFixedAllocator;    // +0x0c
    void*              mpCallbackPool;     // +0x40
    IntrusiveListBase  mCurrentCallbacks;  // +0x44
    IntrusiveListBase2 mNextCallbacks;     // +0x4c
    ~CallbackManager();                    // va 0xa683b0
};
typedef char CallbackCurrentListSize[(sizeof(IntrusiveListBase) == 8) ? 1 : -1];
typedef char CallbackNextListSize[(sizeof(IntrusiveListBase2) == 8) ? 1 : -1];
typedef char CallbackManagerSize[(sizeof(CallbackManager) == 0x54) ? 1 : -1];
typedef char CallbackCurrentListOffset[(offsetof(CallbackManager, mCurrentCallbacks) == 0x44) ? 1 : -1];
typedef char CallbackNextListOffset[(offsetof(CallbackManager, mNextCallbacks) == 0x4c) ? 1 : -1];
class AllocA {
public:
    AllocA(int d) : mpVtbl(g_vtbl_1454fac), mData(d), mpName(g_vtbl_145581c) {}
    ~AllocA() { mpVtbl = g_vtbl_1403934; }
    void*       mpVtbl;                    // +0x00
    int         mData;                     // +0x04
    const char* mpName;                    // +0x08
};
class AllocB {
public:
    AllocB() : mpVtbl(g_vtbl_1454fac), mData(0), mpName(g_vtbl_1455808) {}
    ~AllocB() { mpVtbl = g_vtbl_1403934; }
    void*       mpVtbl;                    // +0x00
    int         mData;                     // +0x04
    const char* mpName;                    // +0x08
};
class AssetManagerExt {
public:
    AssetManagerExt(AllocA&);              // 0x00a63c90 thiscall ret 4
    ~AssetManagerExt();                    // 0x00a63d20
    virtual void v0();
    virtual bool OnX(unsigned char v);     // +4
    virtual void v2();
    void Setup(int v);                     // 0x00a63490 ret 4
    char pad[0x5c];
};
class SymMgrSub {
public:
    char pad[0x54];
    ~SymMgrSub();                          // 0x00a672e0
};
class SymMgrBase {
public:
    virtual ~SymMgrBase();                 // 0x00a66830
};
class SymbolManagerExt : public SymMgrBase {
public:
    SymbolManagerExt();                    // 0x00a67810
    bool Init(int a, int b, int c, AllocA& alloc, AllocB& overflow, int d);  // 0x00a67670 ret 0x18
    char    padBase[0x2c - 4];
    SymMgrSub m2c;                         // +0x2c
    SymMgrSub m80;                         // +0x80
    char    padEnd[4];                     // up to 0xd8
};
class InstanceManagerExt {
public:
    InstanceManagerExt(AllocA&, AssetManagerExt&);   // 0x00a66780 thiscall ret 8
    ~InstanceManagerExt();                 // 0x00a66670
    bool Init(int a, AllocA& alloc, AllocB& overflow);   // 0x00a65f90 ret 0xc
    char pad[0xec];
};
class CallbackManagerExt {
public:
    CallbackManagerExt();                  // 0x00a64470
    ~CallbackManagerExt();                 // 0x00a683b0
    bool Init(int a, AllocA& alloc, AllocB& overflow);   // 0x00a64390 ret 0xc
    char pad[0x54];
};
class FixedInputMapExt : public EapdAssets {
public:
    FixedInputMapExt(const char*);         // 0x00a68b50
    ~FixedInputMapExt();                   // 0x00a687f0
};
class TaskListExt {
public:
    TaskListExt(int arg)
        : mNext(this), mPrev(this), mpVtbl(g_vtbl_1454fac), mArg(arg), mpVtbl2(g_vtbl_14557f8) {}
    ~TaskListExt();                        // 0x00a67e80
    TaskListExt* mNext;                    // +0x00
    TaskListExt* mPrev;                    // +0x04
    void*        mpVtbl;                   // +0x08
    int          mArg;                     // +0x0c
    void*        mpVtbl2;                  // +0x10
};
class InputManagerBaseS {
public:
    InputManagerBaseS(void* pSub) : mpSub(pSub), m8(0), mC(0) {}
    virtual ~InputManagerBaseS() {}        // vtable 0x1455648
    virtual void OnAdd(void*);             // +4
    virtual void OnRemove(void*);          // +8
    void* mpSub;                           // +0x04
    int   m8;                              // +0x08
    int   mC;                              // +0x0c
};
class FixedInputManagerS : public InputManagerBaseS {
public:
    FixedInputManagerS();
    FixedInputMapExt mFixedInputMap;       // +0x10
};
class ISystemS {
public:
    virtual ~ISystemS() {}                 // vtable 0x1455770
};
class AllocatorS : public IInternalAllocator {
public:
    int pad4, pad8;
    virtual void* AllocateNamed(unsigned bytes, const char* name); // 0x00a52b40
    virtual void* Allocate(unsigned bytes);                       // 0x00a52b70
    virtual void Free(void* memory);                              // 0x00a52b90
};
class __declspec(novtable) EapdSystemFull : public ISystemS {
public:
    AllocatorS          mAllocator;        // +0x04
    AllocatorS          mOverflowAllocator;// +0x10
    AssetManagerExt     mAssetManager;     // +0x1c
    SymbolManagerExt    mSymbolManager;    // +0x7c
    InstanceManagerExt  mInstanceManager;  // +0x154
    CallbackManagerExt  mCallbackManager;  // +0x240
    FixedInputManagerS  mGlobalInputManager; // +0x294
    char                padm[0x2f8 - 0x2f4];
    int                 m2f8;              // +0x2f8
    char                padm2[0x300 - 0x2fc];
    double              m300;              // +0x300
    double              m308;              // +0x308
    float               m310;              // +0x310
    float               m314;              // +0x314
    float               m318;              // +0x318
    TaskListExt         mTasks;            // +0x31c
    ~EapdSystemFull();                     // va 0xa68dd0
};
struct EapdInitArgs {
    int m00;                               // +0x00
    int m04;                               // +0x04
    int m08;                               // +0x08
    int m0c;                               // +0x0c
    int m10;                               // +0x10
    int m14;                               // +0x14
    unsigned char m18;                     // +0x18
    char pad19[3];
    int m1c;                               // +0x1c
    unsigned char m20;                     // +0x20
    char pad21[3];
    int m24;                               // +0x24
    int m28;                               // +0x28
    int m2c;                               // +0x2c
    int m30;                               // +0x30
    int m34;                               // +0x34
    int m38;                               // +0x38
    int m3c;                               // +0x3c
};
class AllocRefC {
public:
    AllocRefC(void* raw, const char* name)
        : mpVtbl(g_vtbl_1454fac), mpRaw(raw), mpName(name) {}
    void* Alloc(unsigned size)
    {
        return ((void* (__thiscall*)(void*, unsigned))(*(void***)&mpVtbl)[2])(&mpVtbl, size);
    }
    void Free(void* p)
    {
        ((void (__thiscall*)(void*, void*))(*(void***)&mpVtbl)[3])(&mpVtbl, p);
    }
    void*       mpVtbl;                    // +0x00
    void*       mpRaw;                     // +0x04
    const char* mpName;                    // +0x08
};
class EapdSystemImpl {
public:
    EapdSystemImpl(AllocA& alloc, int arg);         // va 0xa68cb0 thiscall ret 8
    bool Init(EapdInitArgs* a);                     // va 0xa68890 thiscall ret 4
    void*               mpVtbl;            // +0x000
    AllocA              mAllocator;        // +0x004
    AllocB              mOverflowAllocator;// +0x010
    AssetManagerExt     mAssetManager;     // +0x01c
    SymbolManagerExt    mSymbolManager;    // +0x07c
    InstanceManagerExt  mInstanceManager;  // +0x154
    CallbackManagerExt  mCallbackManager;  // +0x240
    FixedInputManagerS  mGlobalInputManager; // +0x294
    char                padm[0x2f8 - 0x2f4];
    int                 m2f8;              // +0x2f8
    char                padm2[0x300 - 0x2fc];
    double              m300;              // +0x300
    double              m308;              // +0x308
    float               m310;              // +0x310
    float               m314;              // +0x314
    float               m318;              // +0x318
    TaskListExt         mTasks;            // +0x31c
};
class EapdSystem {
public:
    void  Destroy();                       // 0xa68dd0
    void* ScalarDtor(int flag);            // @ 0xa68e80
};
class IntrusiveList {
public:
    void Remove(void* p);                  // 0xa68280
};
class Outer310 {
public:
    char pad[0x31c];
    IntrusiveList mList;                   // +0x31c
    void RemoveEntry(int p);               // @ 0xa68410
};
// ---- items of slice s00a68140 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00a52ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
class Allocator { public:
    virtual ~Allocator() {}                       // +0x00
    virtual void  v04();                          // +0x04
    virtual void* v08(uint32_t n);                // +0x08
    virtual void  v0c(void* p);                   // +0x0c
    void* mpCoreAllocator;                        // +0x04
    void* mpNamePtr;                              // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class FixedPool { public:
    Allocator mInitAllocator;                     // +0x00
    Allocator mOverflowAllocator;                 // +0x0c
    uint32_t  mnNodeSize;                         // +0x18
    void*     mpPoolBegin;                        // +0x1c
    void*     mpPoolEnd;                          // +0x20
    void*     mpHead;                             // +0x24
    uint32_t  mnCurrentSize;                      // +0x28
    uint32_t  mnPeakSize;                         // +0x2c
    // +0x30

    ~FixedPool();
    bool Init(uint32_t nodeSize, int count, struct InitAllocator* a1, struct InitAllocator* a2);
    void* Alloc();
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class FixedHashtableAllocator : public FixedPool { public:
    uint32_t  mnBucketCount;                      // +0x30
    void*     mpBucketBuffer;                     // +0x34
    // +0x38

    ~FixedHashtableAllocator();
    bool InitBuckets(unsigned count, struct InitAllocator* a1, struct InitAllocator* a2);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ListLink {
    ListLink* mpNext;      // +0x00
    ListLink* mpPrev;      // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct VoiceList {
    ListLink  mNode;       // +0x00 sentinel (8 bytes)
    FixedPool mPool;       // +0x08
    // +0x38

    ~VoiceList();
    void Clear();
    void PopFront();
    void PushBack(ListLink* anchor, const unsigned* value2);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Symbol { public:                 // 8 bytes
    unsigned    mHash;          // +0x00
    const char* mpName;         // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamPair {              // pair<Symbol const, _atom> = 0x14
    Symbol   first;             // +0x00
    unsigned a_type;            // +0x08
    union {
        float          a_float;   // +0x0c
        const char*    a_sym;     // +0x0c
    };
    const char* a_sym2;         // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamNode {
    ParamPair   mValue;         // +0x00
    ParamNode*  mpNext;         // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamTable {
    void*        mpVftable;       // +0x00
    ParamNode**  mpBucketArray;   // +0x04
    unsigned     mnBucketCount;   // +0x08
    unsigned     mnElementCount;  // +0x0c
    unsigned     pad10[3];        // +0x10 rehash policy
    FixedHashtableAllocator mAllocator;   // +0x1c (FixedPool at +0x1c)
    // +0x54

    ~ParamTable();
    void FreeBuckets(ParamNode** buckets, unsigned n);
    ParamNode* AllocNode(const ParamPair* v);
    void Bucket(void** out, const Symbol* key, void* a3, void* a4);
    unsigned Find(Symbol* key, ParamPair* out);
    ParamPair* LocateOrInsert(const Symbol* key);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Play { public:
    VoiceList   mVoices;         // +0x00
    ParamTable  mParameters;     // +0x38
    unsigned    mnBusyVoices;    // +0x8c
    unsigned    mnMaxVoices;     // +0x90
    unsigned    mnMaxParameters; // +0x94
    void*       mVoiceManager;   // +0x98
    void*       mInstance;       // +0x9c
    Symbol      mName;           // +0xa0
    bool        mbSteal;         // +0xa8
    bool        mbUpdatePlaying; // +0xa9
    bool        mbPaused;        // +0xaa
    int         mnStepRule;      // +0xac
    unsigned    mnLastGroupID;   // +0xb0
    void*       mpObject;        // +0xb4

    ~Play();
    bool Init(unsigned maxVoices, unsigned maxParams, void* a3, void* a4);
    void UpdatePlaying();
    void SetPlaying();
    void SetPaused(bool b);
    void StartVoice(void* a1, void* a2, float t);
    void ParamEvent(Symbol key, ParamPair* atom);
    unsigned GetParam(void* outAtom, Symbol key);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_play {                 // PDB size 0xec
    unsigned  object[0x28 / 4]; // +0x00
    Play      play;             // +0x28
    void*     pUpdateCallback;  // +0xe0
    void*     pDoneOutlet;      // +0xe4
    bool      bIsDynamic;       // +0xe8
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct VectorOfSymbol {
    Symbol*   mpBegin;     // +0x00
    Symbol*   mpEnd;       // +0x04
    void*     mpAlloc;     // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Group { public:
    VectorOfSymbol mSamples;   // +0x00
    Symbol         mLocation;  // +0x18
    bool Init(void* a2, void* a3, int nAtoms, void* argv);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct InitAllocator {
    void* vftable;         // +0x00
    void* field4;          // +0x04
    void* name;            // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct EapdSystem_s00a5_2ff0 {
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual bool  Load(Symbol* location, void* a, void* b, void* c, int* outCount, void* e);
    virtual void  Destroy(void* a);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
Symbol* atom_gensym(Symbol* out, void* atom);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
Symbol* gensym(Symbol* out, const char* s);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    getSymbol(Symbol* out);                 // 0xa635d0 fills *out
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   getEapdSystemData();                    // 0xa67d20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    vectorSymbolResize(VectorOfSymbol* vec, int n);   // 0xa52fa0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int     roundLog2(unsigned n);                  // 0x921340
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void artists_play_setname(t_play* x, unsigned hash, const char* name);
}
}
}
#define NOINLINE __declspec(noinline)
// ---- items of slice s00a52ff0 end

// ---- items of slice s00a670b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float clock_getlogicaltimeafter(float t);                           // 0xa49240
extern "C" void  EapdSetLogicalTime(double t);                                 // 0xa492c0
extern "C" void  EapdSetLookAhead(float f);                                    // 0xa492e0
extern "C" bool  clearallclasses();                                            // 0xa47e30
extern "C" bool  g_editor_free();                                              // 0xa4d070
extern "C" bool  EapdResetGlobals();                                           // 0xa480b0
extern "C" void  EapdStubCall(void* p);                                        // 0xa5ecb0
extern "C" uint32_t EapdSymbolHash(const char* s);                             // 0xa66970
extern "C" uint32_t EapdPrimeBelow(uint32_t n);                                // 0x921340
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {
    int a_type;
    union { float w_float; t_symbol w_symbol; } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_class* t_pd;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    char pad00[0x1c];
    void*  c_methods;                                   // +0x1c
    int    c_nmethod;                                   // +0x20
    char   pad24[4];
    void (*c_bangmethod)(t_pd* x);                      // +0x28
    void (*c_floatmethod)(t_pd* x, float f);            // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);        // +0x30
    void (*c_listmethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);  // +0x34
    void (*c_anymethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);   // +0x38
};
}
}
}
extern "C" extern void*    spEapdSystem_s00a6_70b0;       // 0x16758d4
class SymbolManager;
struct NamedAllocator {
    void*       mpVtbl;   // +0x00
    int         mA;       // +0x04
    const char* mpName;   // +0x08
};
inline void* AllocatorAlloc(void* a, unsigned n)
{
    void** v = *(void***)a;
    return ((void* (__thiscall*)(void*, unsigned))v[2])(a, n);
}
inline void AllocatorFree(void* a, void* p)
{
    void** v = *(void***)a;
    ((void (__thiscall*)(void*, void*))v[3])(a, p);
}
struct HashNode { uint32_t mKey; void* mValue; HashNode* mpNext; };
struct KeyValue { uint32_t mKey; void* mValue; };
struct Iterator { HashNode* mpNode; HashNode** mpBucket; };
class FixedPool_s00a6_70b0 {
public:
    NamedAllocator mInitAllocator;       // +0x00
    NamedAllocator mOverflowAllocator;   // +0x0c
    uint32_t  mnNodeSize;                // +0x18
    void*     mpPoolBegin;               // +0x1c
    void*     mpPoolEnd;                 // +0x20
    void*     mpHead;                    // +0x24
    uint32_t  mnCurrentSize;             // +0x28
    uint32_t  mnPeakSize;                // +0x2c
    void Destroy();                      // 0xa531b0  (~FixedPool)
};
class FixedHashtableAllocator_s00a6_70b0 : public FixedPool_s00a6_70b0 {
public:
    uint32_t mnBucketCount;              // +0x30
    void*    mpBucketBuffer;             // +0x34
    bool Initialize(unsigned n, int a2, int a3);           // 0xa67d90
    bool InitTables(uint32_t a, uint32_t b, uint32_t c);   // 0xa669d0
    void DestroyAllocator();                               // 0xa67d30
};
class Hashtable {
public:
    uint32_t   mFunctors;                 // +0x00
    HashNode** mpBucketArray;             // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator_s00a6_70b0 mAlloc;       // +0x1c

    Hashtable(const char* name);                                    // 0xa67770
    void  Destroy();                                               // 0xa672e0
    void  ClearBuckets(HashNode** arr, uint32_t n);                // 0xa66bf0
    void  Rehash(uint32_t n);                                      // 0xa66b40
    HashNode** AllocateBuckets(uint32_t n);                        // 0xa67ee0
    void  RehashTo(uint32_t n);                                    // 0xa67f60
    bool  Init(uint32_t a, uint32_t b, uint32_t c);                // 0xa67440
    Iterator find(const uint32_t& key);                            // 0x645ed0
    Iterator equal_range(const uint32_t& key);                     // 0x9a6dd0
    Iterator* DoInsertValue(Iterator* sret, const KeyValue* value, const uint32_t* key); // 0xa67370
};
class SymbolManager {
public:
    void*         mpVtbl;                    // +0x00
    NamedAllocator mAllocA;                  // +0x04
    NamedAllocator mAllocB;                  // +0x10
    char          pad1c[0x10];               // +0x1c
    Hashtable     mSymbols;                  // +0x2c
    Hashtable     mBindings;                 // +0x80
    uint32_t (*mHashFunction)(const char*);  // +0xd4

    SymbolManager();

    // callees
    void  VguiBind(uint32_t a, uint32_t b, uint32_t c);                  // 0xa66e30
    void  BindX(uint32_t a, uint32_t b);                                 // 0xa66ec0
    EA::Audio::Eapd::t_pd* FindByClass(uint32_t a, uint32_t b, uint32_t c);               // 0xa66f10
    void  SendBang(uint32_t a, uint32_t b);                              // 0xa66f70
    void  SendFloat(uint32_t a, uint32_t b, float f);                    // 0xa66fd0
    void  SendSymbol(uint32_t a, uint32_t b, uint32_t c, uint32_t d);    // 0xa67040
    bool  InitBuffer(uint32_t a, uint32_t b, uint32_t c);                // 0xa66890
    bool  FindSym(uint32_t a, EA::Audio::Eapd::t_symbol* out);                            // 0xa66de0
    bool  ClearClasses();                                                // 0xa66d60

    // defined here
    void  BindingsListDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);      // 0xa670b0
    void  BindingsTypedmessDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f); // 0xa67130
    bool  GetSymbolFromName(const char* name, EA::Audio::Eapd::t_symbol* out);            // 0xa67570
    bool  InsertSymbol(uint32_t hash, const char* name, EA::Audio::Eapd::t_symbol* out);  // 0xa674e0
    bool  Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t (*hashFn)(const char*)); // 0xa67670
};
class SubObj_s00a6_70b0 {
public:
    virtual void v0();                                       // +0x00
    virtual void v1();                                       // +0x04
    virtual void v2();                                       // +0x08
    virtual bool VfnC(uint32_t a, uint32_t b);               // +0x0c
    virtual bool Vfn10(uint32_t a, float f);                 // +0x10
    virtual bool Vfn14(uint32_t a);                          // +0x14
};
class InstanceObj {
public:
    char pad00[0x34];
    char mSub;                          // +0x34 (returned by 0xff5b80)
    char pad35[0x74 - 0x35];
    bool mFlag;                         // +0x74
    bool GetFlag();                     // 0xa64a00
    void SetX(void* p);                 // 0xa64aa0
    void* GetSub();                     // 0xff5b80
};
class InstanceManager {
public:
    char pad[0xec];
    void* Find(uint32_t key);                       // 0xa65d60
    bool  Shutdown();                               // 0xa65fe0
    bool  Op(uint32_t a, uint32_t b, uint32_t c);   // 0xa657a0
    bool  Op2(uint32_t a, uint32_t b);              // 0xa663e0
    bool  Op3(uint32_t a, uint32_t b);              // 0xa66410
};
class AssetManager {
public:
    char pad[0x60];
    bool FindA(uint32_t a, void** out);                  // 0xa63860
    bool FindB(uint32_t a, uint32_t b, void** out);      // 0xa63dd0
    bool OpC(uint32_t a, uint32_t b);                    // 0xa636b0
};
class CallbackManager_s00a6_70b0 {
public:
    char pad[0x54];
    bool Shutdown();       // 0xa64560
    void Update();         // 0xa645c0
};
struct TaskNode_s00a6_70b0 { TaskNode_s00a6_70b0* mpNext; TaskNode_s00a6_70b0* mpPrev; void* mpValue; };
class TaskList_s00a6_70b0 {
public:
    TaskNode_s00a6_70b0* mpHead;      // +0x00
    TaskNode_s00a6_70b0* mpTail;      // +0x04
    char      mAlloc;      // +0x08 (IInternalAllocator)
    char      pad0c[0x14 - 9];
    void Destroy();        // 0xa67e80
};
class System_s00a6_70b0 {
public:
    void*          mpVtbl;                 // +0x00
    NamedAllocator mAllocator;             // +0x04
    NamedAllocator mOverflowAllocator;     // +0x10
    char           pad1c[0x60];            // +0x1c  asset manager
    SymbolManager  mSymbolManager;         // +0x7c
    char           pad154[0xec];           // +0x154 instance manager
    char           pad240[0x54];           // +0x240 callback manager
    char           pad294[0x64];           // +0x294 global input manager
    void*          mpVoiceManager;         // +0x2f8
    char           pad2fc[4];              // +0x2fc
    double         mdSystemSyncTime;       // +0x300
    double         mdVoiceSyncTime;        // +0x308
    float          mfLatency;              // +0x310
    float          mfLookAhead;            // +0x314
    float          mfMaximumDrift;         // +0x318
    TaskList_s00a6_70b0       mTasks;                 // +0x31c

    bool  Shutdown();                                     // 0xa678d0
    void  SetMaximumDrift(float f);                       // 0xa67960
    static float GetVoiceStartTime(float t);              // 0xa67c70
    bool  FindInstanceSym(uint32_t a, uint32_t b);        // 0xa67990
    bool  GetInstanceFlag(uint32_t a);                    // 0xa679f0
    bool  SetInstanceX(uint32_t a, uint32_t b);           // 0xa67a20
    bool  InstanceVfn10(uint32_t a, uint32_t b, float c); // 0xa67a50
    bool  InstanceVfnC(uint32_t a, uint32_t b, uint32_t c); // 0xa67a90
    bool  InstanceVfn14(uint32_t a, uint32_t b);          // 0xa67ad0
    void  InputVfn10(uint32_t a, float f);                        // 0xa67b10
    bool  AssetInstanceOpA(uint32_t a, uint32_t b, uint32_t* out); // 0xa67b60
    bool  AssetInstanceOpB(uint32_t a);                            // 0xa67bb0
    bool  AssetOpC(uint32_t a);                                    // 0xa67c00
    void  Update(double t);                                        // 0xa68010
    void  UpdateNoTime();                                          // 0xa680c0
};
void* GetVoiceManager();                       // 0xa67d00
void __stdcall SysGfxStubFree(void* p);        // 0xa67c50 (__stdcall)
// ---- items of slice s00a670b0 end

// @ 0x00a52da0
void __cdecl FUN_00a52da0(int* first, int* last, int* value)
{
  for (; first != last; first += 2) {
    first[0] = value[0];
    first[1] = value[1];
  }
}

// @ 0x00a52ff0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE bool Group::Init(void* param_2, void* param_3, int nAtoms, void* argv)
{
    if (nAtoms > 0) {
        Symbol loc;
        getSymbol(&loc);
        mLocation = loc;
        vectorSymbolResize(&mSamples, nAtoms);
        for (int i = 0; i < nAtoms; ++i) {
            mSamples.mpBegin[i] = *atom_gensym(&loc, argv);
            argv = (char*)argv + 0xc;
        }
        return true;
    }

    int count;
    getSymbol((Symbol*)&count);
    EapdSystem_s00a5_2ff0* sys = (EapdSystem_s00a5_2ff0*)getEapdSystemData();
    if (!sys->Load((Symbol*)&count, param_3, param_2, param_3, &count, 0))
        return false;

    if (count <= 4) {
        sys->Destroy(&count);
        return false;
    }

    Symbol loc;
    getSymbol(&loc);
    mLocation = loc;
    unsigned n = *(unsigned*)argv;
    vectorSymbolResize(&mSamples, n);

    char* p = (char*)argv + 4;
    char* end = (char*)argv + count;
    unsigned i = 0;
    while (i < n) {
        if (p >= end)
            break;
        mSamples.mpBegin[i] = *gensym(&loc, p);
        while (*p)
            ++p;
        ++p;
        ++i;
    }
    bool ok = (i == n);
    sys->Destroy(&count);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a531b0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE FixedPool::~FixedPool()
{
    if (mpPoolBegin != 0)
        mInitAllocator.v0c(mpPoolBegin);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53210
namespace EA { namespace Audio { namespace Eapd {
NOINLINE bool FixedPool::Init(uint32_t nodeSize, int count, InitAllocator* a1, InitAllocator* a2)
{
    if (mpPoolBegin != 0) {
        mInitAllocator.v0c(mpPoolBegin);
        mpPoolBegin = 0;
    }
    if (nodeSize >= 4) {
        mnNodeSize = nodeSize;
        uint32_t total = mnNodeSize * (unsigned)count;
        mInitAllocator.mpCoreAllocator = a1->field4;
        mOverflowAllocator.mpCoreAllocator = a2->field4;
        char* begin = (char*)mInitAllocator.v08(total);
        char* end = begin + total;
        mpPoolBegin = begin;
        mpPoolEnd = end;
        mnCurrentSize = 0;
        mnPeakSize = 0;
        mpHead = 0;
        if (begin != 0 && (unsigned)count > 0) {
            mpHead = begin;
            char* p = begin;
            while (p < end - nodeSize) {
                *(char**)p = p + nodeSize;
                p = p + nodeSize;
            }
            *(char**)p = 0;
        }
    }
    return mpPoolBegin != 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a532b0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void* FixedPool::Alloc()
{
    void* p = mpHead;
    if (p != 0) {
        mpHead = *(void**)p;
    } else {
        p = mOverflowAllocator.v08(mnNodeSize);
    }
    if (p != 0) {
        ++mnCurrentSize;
        if (mnCurrentSize > mnPeakSize)
            mnPeakSize = mnCurrentSize;
    }
    return p;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53310
namespace EA { namespace Audio { namespace Eapd {
NOINLINE void artists_play_setname(t_play* x, unsigned hash, const char* name)
{
    if (x->bIsDynamic) {
        if (x->play.mName.mHash != hash)
            x->play.mnLastGroupID = 0xffffffff;
        x->play.mName.mHash = hash;
        x->play.mName.mpName = name;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53360
namespace EA { namespace Audio { namespace Eapd {
NOINLINE bool FixedHashtableAllocator::InitBuckets(unsigned count, InitAllocator* p1, InitAllocator* p2)
{
    if (mpBucketBuffer != 0) {
        mInitAllocator.v0c(mpBucketBuffer);
        mpBucketBuffer = 0;
    }
    unsigned nb = (unsigned)(long long)((float)count * 1.3333334f);
    mnBucketCount = nb;
    if (nb < 3)
        mnBucketCount = 3;
    else
        mnBucketCount = roundLog2(nb) + 1;
    if (mnBucketCount * 4 == 0x18)
        return Init(0x18, count + 1, p1, p2);
    if (Init(0x18, count, p1, p2)) {
        mpBucketBuffer = mInitAllocator.v08(mnBucketCount * 4);
        return mpBucketBuffer != 0;
    }
    return false;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53790
namespace EA { namespace Audio { namespace Eapd {
NOINLINE VoiceList::~VoiceList()
{
    Clear();
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a538e0
namespace EA { namespace Audio { namespace Eapd {
NOINLINE ParamTable::~ParamTable()
{
    FreeBuckets(mpBucketArray, mnBucketCount);
    unsigned n = mnBucketCount;
    ParamNode** arr = mpBucketArray;
    mnElementCount = 0;
    if (n > 1 && arr != (ParamNode**)mAllocator.mpBucketBuffer) {
        --mAllocator.mnCurrentSize;
        if ((void*)arr >= mAllocator.mpPoolBegin && (void*)arr < mAllocator.mpPoolEnd) {
            *(void**)arr = mAllocator.mpHead;
            mAllocator.mpHead = arr;
        } else {
            mAllocator.mOverflowAllocator.v0c(arr);
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a53b20
namespace EA { namespace Audio { namespace Eapd {
NOINLINE Play::~Play()
{
    UpdatePlaying();
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a67810
SymbolManager::SymbolManager()
: mSymbols("EAPd/Symbols"), mBindings("EAPd/Bindings")
{
    mpVtbl = (void*)0x1455710;
    mAllocA.mpVtbl = (void*)0x1454fac;
    mAllocA.mA = 0;
    mAllocA.mpName = "EAPd/SymbolBuffer";
    mAllocB.mpVtbl = (void*)0x1454fac;
    mAllocB.mA = 0;
    mAllocB.mpName = "EAPd/SymbolBuffer";
    for (int i = 0; i < 0x10; ++i)
        pad1c[i] = 0;
    mHashFunction = EapdSymbolHash;
}

// @ 0x00a678d0
bool System_s00a6_70b0::Shutdown()
{
    bool b = ((InstanceManager*)((char*)this + 0x154))->Shutdown() & 1;
    b &= ((bool (__thiscall*)(void*))(*(void***)((char*)this + 0x1c))[2])((char*)this + 0x1c);
    b &= ((CallbackManager_s00a6_70b0*)((char*)this + 0x240))->Shutdown();
    b &= g_editor_free();
    b &= EapdResetGlobals();
    b &= clearallclasses();
    b &= mSymbolManager.ClearClasses();
    return b;
}

// @ 0x00a67960
void System_s00a6_70b0::SetMaximumDrift(float f)
{
    mfMaximumDrift = f * f;
}

// @ 0x00a67990
bool System_s00a6_70b0::FindInstanceSym(uint32_t a, uint32_t b)
{
    bool r = false;
    EA::Audio::Eapd::t_symbol sym;
    if (mSymbolManager.FindSym(a, &sym))
        r = ((InstanceManager*)((char*)this + 0x154))->Op(sym.mHash, (uint32_t)sym.mpName, b);
    return r;
}

// @ 0x00a679f0
bool System_s00a6_70b0::GetInstanceFlag(uint32_t a)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = o->GetFlag();
    return r;
}

// @ 0x00a67a20
bool System_s00a6_70b0::SetInstanceX(uint32_t a, uint32_t b)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o) {
        o->SetX((void*)b);
        r = true;
    }
    return r;
}

// @ 0x00a67a50
bool System_s00a6_70b0::InstanceVfn10(uint32_t a, uint32_t b, float c)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = ((SubObj_s00a6_70b0*)o->GetSub())->Vfn10(b, c);
    return r;
}

// @ 0x00a67a90
bool System_s00a6_70b0::InstanceVfnC(uint32_t a, uint32_t b, uint32_t c)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = ((SubObj_s00a6_70b0*)o->GetSub())->VfnC(b, c);
    return r;
}

// @ 0x00a67ad0
bool System_s00a6_70b0::InstanceVfn14(uint32_t a, uint32_t b)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = ((SubObj_s00a6_70b0*)o->GetSub())->Vfn14(b);
    return r;
}

// @ 0x00a67b10
void System_s00a6_70b0::InputVfn10(uint32_t a, float f)
{
    void* self = (char*)this + 0x294;
    void** vt = *(void***)self;
    ((void (__thiscall*)(void*, uint32_t, float))vt[4])(self, a, f);
}

// @ 0x00a67b60
bool System_s00a6_70b0::AssetInstanceOpA(uint32_t a, uint32_t b, uint32_t* out)
{
    void* pair[2];
    bool ok = ((AssetManager*)((char*)this + 0x1c))->FindB(a, b, pair);
    if (ok) {
        ((InstanceManager*)((char*)this + 0x154))->Op3((uint32_t)pair[0], (uint32_t)pair[1]);
        *out = (uint32_t)pair[0];
    }
    return ok;
}

// @ 0x00a67bb0
bool System_s00a6_70b0::AssetInstanceOpB(uint32_t a)
{
    void* pair[2];
    bool ok = ((AssetManager*)((char*)this + 0x1c))->FindA(a, pair);
    if (ok)
        ((InstanceManager*)((char*)this + 0x154))->Op2((uint32_t)pair[0], (uint32_t)pair[1]);
    return ok;
}

// @ 0x00a67c00
bool System_s00a6_70b0::AssetOpC(uint32_t a)
{
    bool r = false;
    EA::Audio::Eapd::t_symbol sym;
    if (mSymbolManager.FindSym(a, &sym))
        r = ((AssetManager*)((char*)this + 0x1c))->OpC(sym.mHash, (uint32_t)sym.mpName);
    return r;
}

// @ 0x00a67c50
void __stdcall SysGfxStubFree(void* p)
{
    EapdStubCall(p);
}

// @ 0x00a67c70
float System_s00a6_70b0::GetVoiceStartTime(float t)
{
    System_s00a6_70b0* sys = (System_s00a6_70b0*)spEapdSystem_s00a6_70b0;
    float v = clock_getlogicaltimeafter(t) - sys->mdSystemSyncTime
              + sys->mfLatency + sys->mdVoiceSyncTime;
    if (v < 0.0f)
        return 0.0f;
    return v;
}

// @ 0x00a67d00
void* GetVoiceManager()
{
    if (spEapdSystem_s00a6_70b0)
        return *(void**)((char*)spEapdSystem_s00a6_70b0 + 0x2f8);
    return 0;
}

// @ 0x00a67d30
void FixedHashtableAllocator_s00a6_70b0::DestroyAllocator()
{
    if (mpBucketBuffer) {
        AllocatorFree(this, mpBucketBuffer);
    }
    Destroy();
}

// @ 0x00a67d90
bool FixedHashtableAllocator_s00a6_70b0::Initialize(unsigned n, int a2, int a3)
{
    if (mpBucketBuffer) {
        AllocatorFree(this, mpBucketBuffer);
        mpBucketBuffer = 0;
    }
    uint32_t buckets = (uint32_t)((float)n * 1.3333334f);
    mnBucketCount = buckets;
    if (buckets < 3) {
        mnBucketCount = 3;
    } else {
        mnBucketCount = EapdPrimeBelow(buckets) + 1;
    }
    uint32_t bytes = mnBucketCount * 4;
    if (bytes == 0x10) {
        if (!((bool (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))
                (*(void***)this)[2])(this, 0x10, n + 1, a2, a3))
            return false;
    } else {
        if (!((bool (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))
                (*(void***)this)[2])(this, 0x10, n, a2, a3))
            return false;
        void* buf = AllocatorAlloc(this, mnBucketCount * 4);
        mpBucketBuffer = buf;
        return buf != 0;
    }
    return false;
}

// @ 0x00a67e80
void TaskList_s00a6_70b0::Destroy()
{
    if (mpHead != (TaskNode_s00a6_70b0*)this) {
        TaskNode_s00a6_70b0* n = mpHead;
        do {
            TaskNode_s00a6_70b0* next = n->mpNext;
            AllocatorFree(&mAlloc, n);
            n = next;
        } while (n != (TaskNode_s00a6_70b0*)this);
    }
    *(void**)(&mAlloc) = (void*)0x1403934;
}

// @ 0x00a67f60
void Hashtable::RehashTo(uint32_t n)
{
    HashNode** nb = AllocateBuckets(n);
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        HashNode* node = mpBucketArray[i];
        while (node) {
            uint32_t idx = node->mKey % n;
            HashNode* next = node->mpNext;
            mpBucketArray[i] = next;
            node->mpNext = nb[idx];
            nb[idx] = node;
            node = mpBucketArray[i];
        }
    }
    HashNode** old = mpBucketArray;
    if (mnBucketCount > 1 && old != (HashNode**)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if (old < (HashNode**)mAlloc.mpPoolBegin || old >= (HashNode**)mAlloc.mpPoolEnd) {
            AllocatorFree(&mAlloc.mOverflowAllocator, old);
        } else {
            *(void**)old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
    }
    mpBucketArray = nb;
    mnBucketCount = n;
}

// @ 0x00a68010
void System_s00a6_70b0::Update(double t)
{
    EapdSetLogicalTime(t);
    double voice = ((double (__thiscall*)(void*))((*(void***)mpVoiceManager)[1]))(mpVoiceManager);
    double diff = (t - mdSystemSyncTime) - (voice - mdVoiceSyncTime);
    if (diff * diff > (double)mfMaximumDrift) {
        mdSystemSyncTime = t;
        mdVoiceSyncTime = voice;
    }
    for (TaskNode_s00a6_70b0* n = mTasks.mpHead; n != (TaskNode_s00a6_70b0*)&mTasks.mpHead; n = n->mpNext) {
        void* obj = n->mpValue;
        ((void (__thiscall*)(void*, double))((*(void***)obj)[1]))(obj, t);
    }
    ((CallbackManager_s00a6_70b0*)((char*)this + 0x240))->Update();
    EapdSetLookAhead(mfLookAhead);
}

// @ 0x00a680c0
void System_s00a6_70b0::UpdateNoTime()
{
    double voice = ((double (__thiscall*)(void*))((*(void***)mpVoiceManager)[1]))(mpVoiceManager);
    EapdSetLogicalTime(voice);
    for (TaskNode_s00a6_70b0* n = mTasks.mpHead; n != (TaskNode_s00a6_70b0*)&mTasks.mpHead; n = n->mpNext) {
        void* obj = n->mpValue;
        ((void (__thiscall*)(void*, double))((*(void***)obj)[1]))(obj, voice);
    }
    ((CallbackManager_s00a6_70b0*)((char*)this + 0x240))->Update();
    EapdSetLookAhead(mfLookAhead);
}

// @ 0x00a68140
void EapdInfo::GetInfoA(int* out)
{
    out[0] = ((PolSub*)(pad + 0x154))->GetPoliticalID();
    out[1] = ((Sub240A*)(pad + 0x240))->Get();
    out[2] = *(int*)(pad + 0x2e8);
    ((Sub7cA*)(pad + 0x7c))->Fill(&out[3], &out[4], &out[5]);
}

// @ 0x00a68190
void EapdInfo::GetInfoB(int* out)
{
    out[0] = ((FileSub*)(pad + 0x154))->GetFileCount();
    out[1] = ((Sub240B*)(pad + 0x240))->StartTime();
    out[2] = *(int*)(pad + 0x2ec);
    ((Sub7cB*)(pad + 0x7c))->Fill(&out[3], &out[4], &out[5]);
}

// @ 0x00a681e0
bool DestroyEapdSystem() // @ 0xa681e0
{
    if (spEapdSystem) {
        AllocRef a(spEapdSystem->mA, spEapdSystem->mB);
        bool r = spEapdSystem->Shutdown() & 1;
        EapdSingleton* s = spEapdSystem;
        s->Dtor(0);
        IAlloc& al = a;
        al.Free(s);
        spEapdSystem = 0;
        return r;
    }
    return false;
}

// @ 0x00a68280
void KeyList::RemoveKey(const int* key)
{
    LNode* n = mNext;
    while (n != (LNode*)this) {
        int k = n->key;
        n = n->next;
        if (k == *key) {
            LNode* x = n->prev;
            x->prev->next = x->next;
            x->next->prev = x->prev;
            mAlloc.Free(x);
        }
    }
}

// @ 0x00a682d0
void* NodePool::Allocate(const int* src)
{
    int* p = (int*)mFree;
    if (p)
        mFree = *(PoolNode**)p;
    else
        p = (int*)mAlloc.Alloc(mSize);
    if (p) {
        ++mCount;
        if (mCount > mHigh)
            mHigh = mCount;
        p[0] = src[0];
        p[1] = src[1];
        p[2] = src[2];
    }
    p[3] = 0;
    return p;
}

// @ 0x00a68330
void NodePool::FreeChains(PoolNode** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        PoolNode* node = buckets[i];
        while (node) {
            PoolNode* cur = node;
            node = node->chain;
            ((Sub4*)((char*)cur + 4))->Destroy();
            if (cur != mSpecial) {
                --mCount;
                if (cur < mBegin || cur >= mEnd) {
                    mAlloc.Free(cur);
                } else {
                    cur->next = mFree;
                    mFree = cur;
                }
            }
        }
        buckets[i] = 0;
    }
}

// @ 0x00a683b0
CallbackManager::~CallbackManager()
{
}

// @ 0x00a68410
void Outer310::RemoveEntry(int p)
{
    if (p)
        mList.Remove(&p);
}

// @ 0x00a68430
HIter GTable::erase(HIter it)
{
    HIter r;
    r.node = it.node->chain;
    r.bucket = it.bucket;
    while (!r.node) {
        ++r.bucket;
        r.node = *r.bucket;
    }
    HNode* node = it.node;
    HNode* p = *it.bucket;
    if (p == node) {
        *it.bucket = p->chain;
    } else {
        HNode* q = p->chain;
        while (q != node) {
            p = q;
            q = q->chain;
        }
        p->chain = q->chain;
    }
    node->value.~Group_s00a6_8140();
    int delta = -1;
    if (node != mSpecial) {
        mCount += delta;
        if (node >= mBegin && node < mEnd) {
            node->next = mFree;
            mFree = node;
            mElems += delta;
            return r;
        }
        mAlloc.Free(node);
    }
    mElems += delta;
    return r;
}

// @ 0x00a685a0
void EapdTasks::PushTask(void* t)
{
    if (t)
        mTasks.PushBack(t);
}

// @ 0x00a685e0
bool EapdAssets::Init(int a, int b, int c)
{
    AssetMgr* am = &mAssets;
    bool r = am->Open(a, b, c);
    if (r) {
        Grow(am->mCount - 1);
        Vec3F v;
        v.x = g_ten_k;
        v.y = g_two;
        v.z = 0;
        m10 = v;
        unsigned n = v.Fn(mC);
        if (n > m8)
            Grow(n);
    }
    return r;
}

// @ 0x00a687f0
NodePool::~NodePool()
{
    FreeChains(mBuckets, mBucketCount);
    unsigned n = mBucketCount;
    PoolNode* b = (PoolNode*)mBuckets;
    mElems = 0;
    if (n > 1 && b != mSpecial) {
        --mCount;
        if (b < mBegin || b >= mEnd) {
            mAlloc.Free(b);
        } else {
            b->next = mFree;
            mFree = b;
        }
    }
}

// @ 0x00a68890
bool EapdSystemImpl::Init(EapdInitArgs* a)
{
    if (a->m34)
        FUN_00a646e0(a->m34);
    mOverflowAllocator.mData = a->m1c;
    bool ok = mSymbolManager.Init(a->m0c, a->m10, a->m14, mAllocator, mOverflowAllocator, a->m30);
    ok &= mCallbackManager.Init(a->m04, mAllocator, mOverflowAllocator);
    ok &= mGlobalInputManager.mFixedInputMap.Init(a->m08, (int)&mAllocator, (int)&mOverflowAllocator);
    ok &= mAssetManager.OnX(a->m20);
    ok &= mInstanceManager.Init(a->m00, mAllocator, mOverflowAllocator);
    ok &= FUN_00a495e0();
    if (ok) {
        FUN_00a53300(a->m24);
        if (a->m2c)
            mAssetManager.Setup(a->m2c);
        if (a->m38)
            mGlobalInputManager.OnAdd((void*)a->m38);
        if (a->m3c)
            mGlobalInputManager.OnRemove((void*)a->m3c);
    }
    return ok;
}

// @ 0x00a68bf0
FixedInputManagerS::FixedInputManagerS()
: InputManagerBaseS((char*)this + 0x10),
      mFixedInputMap("EAPd/InputManager")
{
}

// @ 0x00a68cb0
EapdSystemImpl::EapdSystemImpl(AllocA& alloc, int arg)
: mpVtbl(g_vtbl_1455828),
      mAllocator(alloc.mData),
      mOverflowAllocator(),
      mAssetManager(mAllocator),
      mSymbolManager(),
      mInstanceManager(mAllocator, mAssetManager),
      mCallbackManager(),
      mGlobalInputManager(),
      m2f8(arg),
      m300(0.0),
      m308(0.0),
      m310(0.0f),
      m314(0.0f),
      m318(g_0p05),
      mTasks(mAllocator.mData)
{
}

// @ 0x00a68dd0
EapdSystemFull::~EapdSystemFull()
{
}

// @ 0x00a68e80
void* EapdSystem::ScalarDtor(int flag)
{
    Destroy();
    return this;
}

// @ 0x00a68e90
extern "C" bool __cdecl CreateEapdSystem(void* pRaw, EapdInitArgs args)
{
    if (spEapdSystem)
        return false;
    if (!pRaw)
        return false;
    if (args.m18 && !args.m1c)
        args.m1c = (int)pRaw;
    AllocRefC local(pRaw, "EAPd/CreateSingleton");
    if (!args.m28)
        return false;
    void* mem = local.Alloc(0x330);
    EapdSystemImpl* sys = mem ? new (mem) EapdSystemImpl((AllocA&)local, args.m28) : 0;
    spEapdSystem = (EapdSingleton*)sys;
    bool ok = false;
    if (sys && sys->Init(&args))
        ok = true;
    if (!ok) {
        if (spEapdSystem) {
            spEapdSystem->Shutdown();
            EapdSingleton* s = spEapdSystem;
            s->Dtor(0);
            local.Free(s);
            spEapdSystem = 0;
        }
    }
    return ok;
}
