// src/game/SPAudio/AudioSystem.cpp -- migrated from slice(s) s00e22860, s00a2f660, s00a2bfa0, s00a2af30, s00a290b0, s00a28120, s00a25c40, s00a17690, s00a26e10, s00a21130, s00a0f350, s00a32f20, s00a31f20, s00a31170, s00a30460, s00a2e650, s00a2d790, s00a2c6c0, s00a2a020, s00a24e10, s00a23360, s00a22220, s00a20060, s00432830 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1452970[];

#include "game/types.h"
#include "SP/cIReleaseCallback.h"
#include "SP/cResourceBase.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Thread/Mutex.h"
#include "EA/Audio/Playlist.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "EA/Audio/IMixable.h"
#include "EA/IO/FileStream.h"
#include "EA/Audio/ResourceDeviceDriver.h"
#include "EA/Audio/Subscription.h"
#include <intrin.h>
#include "EA/Audio/ISystem.h"
#include "EA/Stopwatch.h"
#include "EA/Audio/System.h"
#include "EA/Audio/VoiceContainer.h"
#include <math.h>
#include "EA/Thread/Condition.h"
#include "EA/Allocator/ZoneObject.h"
#include "EA/Messaging/IHandlerRC.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/Messaging/Server.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "EA/Thread/Thread.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "EA/Audio/Submix.h"
#include <string.h>
#include "EA/Audio/Command.h"
#include <stdlib.h>
#include "EA/Allocator/ICoreAllocator.h"
#include "rw/audio/core/StreamPool.h"
#include "rw/audio/core/System.h"
#include "EA/Messaging/AutoHandler.h"
#include "rw/core/debug/Channel.h"
#include "EA/Audio/Allocator.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Audio/Allocator2.h"
#include <stddef.h>
#include "SP/cSPCreatureAnimManager.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/Audio/FactoryVoiceTemplate.h"
#include <stdarg.h>
#include "EA/Audio/ResourceConfiguration.h"
#include "EA/Variant.h"
#include <stdio.h>
#include <float.h>
#include "cSPUIAnimator.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* target, long value);
extern "C" long __cdecl _InterlockedIncrement(long volatile* target);
extern "C" long __cdecl _InterlockedDecrement(long volatile* target);
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

// ---- items of slice s00432830 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Queryable {
    void* Cast(unsigned id);           // 0x00432AD0
};
// ---- items of slice s00432830 end

// ---- items of slice s00a20060 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_166d9fc;
extern int g_166d9f4;
extern int g_166d9f8;
typedef unsigned char u8;
typedef unsigned int  u32;
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);   // 0xf473a0
unsigned int __cdecl FNV1_String8(const void* s, unsigned int basis, int flag);
struct Mutex {
    void Lock(void* tag);   // 0x9221b0 (EA::Thread::Mutex::Lock)
    void Unlock();          // 0x922270 (EA::Thread::Mutex::Unlock)
    int  GetLocation();
};
struct ScopedLock {
    Mutex* volatile m;
    ScopedLock(Mutex* mm, void* tag) : m(mm) { m->Lock(tag); }
    ~ScopedLock() { m->Unlock(); }
};
struct Sub264 {
    void F(void*);                        // 0xa0fee0
};
struct Sub20 {
    void F(void*, int);                   // 0x922940
};
struct SubRel { virtual void r0(); virtual void r1(); virtual void r2(); virtual void Rel(); };
void ThreadSleep(const int*);              // 00921df0
struct DPF {
    int GetLocation();
};
struct Sub214 {
    void Release();      // 00a0fdd0
    int  Get();          // 00a0f9f0
    void Reset();        // 00a0f940
    void Add(void*, float); // 00a10390
};
struct Node {
    virtual void n0(int flags);   // scalar deleting destructor slot
};
struct Obj {
    int Check();       // 00a1b3f0
    int Span();        // 00a1ad70
};
struct X119 {
    void m(void* b);   // 00926460
    void m2();         // 00926300
};
unsigned long long __stdcall GetZero(int);  // 0x00a20690 (defined below; used by a stub's inline body)
struct Sys {
    u8 pad[0x200000];

    long long GetZero(int);                       // 00a20690

    int   ReleaseSub();                           // 00a207a0
    bool  Shutdown();                             // 00a207d0
    bool  Route1(u32 id, int a, int b, float c, int d); // 00a20910
    bool  Route2(u32 id, float value);            // 00a20950
    bool  Route3(u32 id, float a, float b, float c); // 00a20990
    bool  Route4(u32 id, void* a, void* b, void* c); // 00a20a00
    void  SetSlot(int idx, void* a, void* b);     // 00a20a40
    void  GetSlot(int idx, void* out, void* big); // 00a20ac0
    void  Add214(void* a, float b);               // 00a20b20
    void  Commit214();                            // 00a20ba0
    void  Flush();                                // 00a20be0
    void  LockB8();                               // 00a210d0
    bool  HasLocation();                          // 00a21100
    bool  WithinRange(void* a, int b);            // 00a21080
    void* SlotA(int idx);                         // 00a20d20
    void* SlotB(int idx);                         // 00a20d40
    void* Field119();                             // 00a20cf0? no
    void  Tick119(int a, int b);                  // 00a20cf0
    void  Tick119b();                             // 00a20d10
};
struct V3 { u32 a, b, c; };
struct Big9 { u32 v[9]; };
struct Sound2 {                           // Audio::Sound, 0x1e10 bytes
    Sound2();                             // 0xa1fbb0
    virtual void s0();
    virtual void s1();
    char data[0x1e10 - 4];
};
struct PropSet {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
    virtual void GetFloat(u32 key, float* out);   // +0x10
};
struct SoundOrd {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual bool Flag(int which, int z);          // +0x20
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual float Dist();                         // +0x60
    PropSet props;                                // +4 (embedded subobject with its own vptr)
    bool  Has();        // 00a1af50
    float Key1();       // 00a1af70
    float Key2();       // 00a1adb0
    u32 Flags() { return *(u32*)((char*)this + 0xce4); }
};
struct OrdInfo {
    u8 present;
    u8 pad[0xb];
    float dist;
    float key;
};
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s00a20060 end

// ---- items of slice s00a22220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);
#pragma warning(disable:4035)
void __cdecl op_delete(void*);            // operator_delete__ (0x00f47380)
struct HNode28 { u32 key; u32 pad; HNode28* next; };   // next at +8
struct HNode20 { u32 key; HNode20* next; };            // next at +4
struct HTable28 {
    u32       pad0;
    HNode28** buckets;     // +4
    u32       bucketCount; // +8
    u32       pad0c[4];
    void*     freeList;    // +0x1c
    u32       pad20;
    void*     poolBegin;   // +0x24
    void*     poolEnd;     // +0x28
    u32       pad2c;
    void*     inlineBuckets; // +0x30
    HNode28** AllocBuckets(u32 n);      // 00a221b0
    void      Rehash(u32 n);
};
struct HTable20 {
    u32       pad0;
    HNode20** buckets;     // +4
    u32       bucketCount; // +8
    u32       pad0c[4];
    void*     freeList;    // +0x1c
    u32       pad20;
    void*     poolBegin;   // +0x24
    void*     poolEnd;     // +0x28
    u32       pad2c;
    void*     inlineBuckets; // +0x30
    HNode20** AllocBuckets(u32 n);      // 00a22300
    void      Rehash(u32 n);
};
struct PoolList {
    void*  head;        // +0  (circular, this is the anchor)
    u32    pad4;
    void*  freeList;    // +8
    u32    padc;
    void*  poolBegin;   // +0x10
    void*  poolEnd;     // +0x14
    void   FreeNodes(); // 00a222c0
};
struct Snd;
struct SNode { SNode* next; SNode* prev; };
struct Snd {
    void** vt;
    u32    pad04[3];
    SNode  node;       // +0x10
    static Snd* FromNode(SNode* n) { return n ? (Snd*)((char*)n - 0x10) : 0; }
    bool Check();                       // 00ef6410
};
struct SIter { Snd* p; SIter() {} SIter(Snd* q) : p(q) {} };
struct SList {
    SNode anchor;
    void  merge(SList& x, bool (__cdecl* compare)(Snd*, Snd*));   // 00a22410
    void  splice(SIter pos, SList& x, SIter first, SIter last);    // 00a212b0
};
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}
struct ARef {
    IRef* p;
    ARef() : p(0) {}
    ARef(const ARef& o) : p(o.p) { if (p) p->AddRef(); }
    ARef& operator=(const ARef& o)
    {
        IRef* np = o.p;
        IRef* old = p;
        if (np != old) {
            if (np) np->AddRef();
            p = np;
            if (old) old->Release();
        }
        return *this;
    }
};
struct AR {
    u32  a, b, c, d;
    ARef r;

    AR() {}
    AR(const AR& o) : a(o.a), b(o.b), c(o.c), d(o.d), r(o.r) {}
    AR& operator=(const AR& o)
    {
        a = o.a;
        b = o.b;
        c = o.c;
        d = o.d;
        r = o.r;
        return *this;
    }
};
AR& (AR::*g_arAssign)(const AR&) = &AR::operator=;
struct RefBaseA22 {
    virtual void v0();
    volatile long rc;
    RefBaseA22() { _InterlockedExchange(&rc, 0); }
};
struct DrvArgA22 {          // non-polymorphic base, laid out after RefBaseA22 (+8)
    u32   pad[0x1e];       // +8 .. +0x80
    void* mArg;            // +0x80
    DrvArgA22(void* arg) : mArg(arg) {}
};
struct DrvBA22 : DrvArgA22, RefBaseA22 {
    u32   mPad84;
    u32   mZero;           // +0x88
    DrvBA22(void* arg);
    virtual void v0();
};
struct RCSub {                              // refcounted base at +4 of a shared block
    virtual void Del(int);
    volatile long rc;
    void Release()
    {
        long n = _InterlockedExchangeAdd(&rc, -1);
        if (--n == 0) {
            _InterlockedExchange(&rc, 1);
            if (this)
                this->Del(1);
        }
    }
};
struct MutexObj { ~MutexObj(); };
struct RecVec { ~RecVec(); };
struct DDBase { virtual ~DDBase() {} };
struct ResourceDeviceDriver : DDBase {
    u32      pad[4];
    RecVec   mRecordContainer;     // +0x14
    u32      pad18[4];
    MutexObj mMutex;               // +0x28
    ResourceDeviceDriver() {}
};
struct SharedBlock {                       // pointer p: sub-object at +4, refcount at +8
    u32   pad0;
    RCSub sub;
};
struct SharedRef {
    SharedBlock* p;
    void Assign(void* np);                                      // 006ae2a0
    ~SharedRef()
    {
        if (p)
            p->sub.Release();
    }
};
struct Builder {
    void  Begin(u32 key);                      // 00a102e0
    void  AddInt(u32 key, u32 value);          // 00a103b0
    void  AddFloat(u32 key, float value);      // 00a10390
    void  Commit();                            // 00a0f940
};
struct IMix {
    virtual void m0();
    virtual void m1();
    virtual int  GetId();                       // +8
    virtual void m3();
    virtual bool Query(u32 key, float* out);    // +0x10
};
struct RBNode {
    RBNode* right;
    RBNode* left;
    RBNode* parent;
    u32     color;
    u32     key;     // +0x10
    u32     value;   // +0x14
};
RBNode* RBTreeIncrement(RBNode* n);           // 00921580
struct Subscription {
    IMix*  mpMixable;       // +0
    u32    pad4;
    RBNode anchor;          // +8 (anchor.left is begin at +0xc)
    void   UpdateOutput(Builder* b);
};
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}
u32  GetThreadId_();                                       // 00921cc0
struct Stopwatch {
    unsigned __int64 mnStartTime;
    unsigned __int64 mnTotalElapsedTime;
    int   mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    Stopwatch(int units, int start);                       // 0093a560
    void Restart();                                         // 00571e80
    __int64 GetElapsedTimeFloat();                          // 0093a3a0
    void RestartInline()
    {
        if (mnUnits == 1) {
            unsigned __int64 t = __rdtsc();
            ((u32*)&mnStartTime)[1] = (u32)(t >> 32);
            ((u32*)&mnStartTime)[0] = (u32)t;
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mnStartTime = t;
        }
        mnTotalElapsedTime = 0;
    }
};
struct WorkerCtx {
    u32  pad[0x18];
    u8   stop;                // +0x60
    u8   pad61[3];
    u32  mode;                // +0x64
    void Init(int);           // 00922050
};
#define VCALL(T, p, off) ((T)((*(void***)(p))[(off) / 4]))
struct IStream_ {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual void* Next();         // +0x18
};
struct IProvider {
    virtual void p0(); virtual void p1(); virtual void p2();
    virtual u32 GetType();        // +0xc
    virtual void p4(); virtual void p5(); virtual void p6();
    virtual int GetSize();        // +0x1c
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual int Read(int buf, int size);   // +0x30
};
struct IAlloc {
    virtual void a0(); virtual void a1();
    virtual int Alloc(int size, const char* name, int flags);   // +8
};
struct SharedPtr {
    u32 pad[6];
    SharedPtr(int data, int own, IAlloc* a);                    // 0093bc40
    static void* operator new(unsigned size, const char* name, int, int, int, int);  // 00926020
    static void  operator delete(void* p, const char* name, int, int, int, int);
};
struct Item {
    u32       pad0[5];
    int       data;       // +0x14
    int       size;       // +0x18
    u32       pad1c[3];
    SharedRef mShared;    // +0x28
};
IAlloc* GetDefaultAllocator();                                  // 00925cb0
struct Query {
    int a;
    u32 key;
    int c;
};
// ---- items of slice s00a22220 end

// ---- items of slice s00a23360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, unsigned int);
extern float g_1485720;
struct AudioCoreSystem_s00a2_1220 {   // rw::audio::core::System
    char pad0[8];
    double mTime;                      // +8
};
extern AudioCoreSystem_s00a2_1220* g_16e61a8;     // 0x016e61a8
extern const char g_lockName[];   // 0x01452970
#define EA_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* operator new(unsigned int, const char*, int, int, const char*, int);
void  operator_delete__(void*);              // 0x00f47380
template<class R> static inline R vc(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template<class R, class A1> static inline R vc(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }
template<class R, class A1, class A2> static inline R vc(void* o, int off, A1 a1, A2 a2)
{ return ((R (__thiscall*)(void*, A1, A2))(*(void***)o)[off / 4])(o, a1, a2); }
template<class R, class A1, class A2, class A3> static inline R vc(void* o, int off, A1 a1, A2 a2, A3 a3)
{ return ((R (__thiscall*)(void*, A1, A2, A3))(*(void***)o)[off / 4])(o, a1, a2, a3); }
template<class R, class A1, class A2, class A3, class A4>
static inline R vc(void* o, int off, A1 a1, A2 a2, A3 a3, A4 a4)
{ return ((R (__thiscall*)(void*, A1, A2, A3, A4))(*(void***)o)[off / 4])(o, a1, a2, a3, a4); }
struct ISystem {
    virtual void vInit();
    virtual ~ISystem();
};
struct System : ISystem {
    u8       pad_04[4];                // +0x04
    void*    mAutoMsg;                 // +0x08 (IHandlerRC subobject)
    u8       pad_0c[0x9a - 0x0c];
    u8       mbMuted;                  // +0x9a
    u8       pad_9b[0x400 - 0x9b];
    float    s400;                     // +0x400
    u8       pad_404[0x157438 - 0x404];
    void*    listNext;                 // +0x157438
    void*    listPrev;                 // +0x15743c
    u8       pad_157440[0x15bbe4 - 0x157440];
    float    pos[3];                   // +0x15bbe4
    u8       b15bbf0;                  // +0x15bbf0

    float GetPosDist(float* p);        // 0x00a23360
    void  MuteAll(bool bMute, bool bParam); // 0x00a233b0
};
void __cdecl sub_112c600();                     // 0x0112c600
void __cdecl sub_112c620();                     // 0x0112c620
void __stdcall sub_112ccc0(int a, void* b);     // 0x0112ccc0
struct MuteParams { double d0; float fParam; float fMute; float f3; };
struct PluginIface { void Call112ccc0(int a, void* b); };    // 0x0112ccc0 (thiscall)
struct VoiceContainer { void* FindPlugin(u32 id); };         // 0x00a34230
struct EHNode { int key; void* value; EHNode* next; };
struct EInsertRes;
struct ERehashInfo { int bNeed; u32 nNew; };
struct AllocStub { void RehashRequired(ERehashInfo* out, u32 nBuckets, u32 nElems, int extra); }; // 0x00921440
struct EInsertRes { EHNode* node; EHNode** bucket; bool inserted; u8 pad[3]; };
struct EHTable {
    void*    allocatorTag;   // +0
    EHNode** mpBuckets;      // +4
    u32      mnBucketCount;  // +8
    u32      mnElementCount; // +0x0c
    AllocStub* mAllocator;   // +0x10
    void     DoRehash(u32 n);                      // 0x00902000
    EInsertRes* DoInsertKey(EInsertRes* out, const int* pkey, u32 unused); // 0x00a23830
};
struct RefCounted { virtual void v00(); virtual void Release(); };
// a vector of reference-counted pointers: the base frees the storage (when it is a heap block), the vector releases
// each element first
struct RefVecStorage {
    RefCounted** mpBegin;   // +0
    RefCounted** mpEnd;     // +4
    ~RefVecStorage();
};
struct RefVec : RefVecStorage {
    ~RefVec();              // 0x00a23920
};
struct PHNode { int key; PHNode* next; };
struct PHTable {
    u32       pad0;
    PHNode**  mpBuckets;    // +4
    u32       mnBucketCount;// +8
    u32       mnElementCount;// +0xc
    u32       pad10[3];
    PHNode*   mpFreeList;   // +0x1c
    u32       pad20;
    void*     mpPoolBegin;  // +0x24
    void*     mpPoolEnd;    // +0x28
    u32       pad2c;
    void*     mpInline;     // +0x30

    int  Erase(const int* pkey);                   // 0x00a23d20
    PHNode** EraseNode(PHNode** out, PHNode* n, PHNode** pb); // 0x00a23db0
    void FreeBuckets(PHNode** buckets, u32 count); // 0x00a24480
};
struct RBNode_s00a2_3360 {
    RBNode_s00a2_3360* left;    // +0
    RBNode_s00a2_3360* right;   // +4
    RBNode_s00a2_3360* parent;  // +8
    u8      color;   // +0xc
    u8      pad0d[3];
    u32     key0;    // +0x10
    u32     key1;    // +0x14
};
struct Snd_s00a2_3360 {
    u8    mPad00[0x10];   // +0x00 payload (not inspected by the sort)
    SNode node;           // +0x10 { next, prev }
    static Snd_s00a2_3360* FromNode(SNode* n) { return n ? (Snd_s00a2_3360*)((char*)n - 0x10) : 0; }
    static SNode* ToNode(Snd_s00a2_3360* p) { return p ? (SNode*)((char*)p + 0x10) : 0; }
};
typedef bool (__cdecl* CompareFn)(Snd_s00a2_3360*, Snd_s00a2_3360*);
struct ElemList {
    SNode anchor;                                               // +0x00 { next, prev }
    ElemList();                                                 // self-links the anchor
    ~ElemList();                                                // unlinks what is left
    void Assign(void* pCompare);                                // 0x00a24210 (merge sort)
    Snd_s00a2_3360* begin() { return Snd_s00a2_3360::FromNode(anchor.next); }
    // Out-of-slice intrusive-list helpers (the original passes the list in ecx).
    void splice(Snd_s00a2_3360* pos, ElemList& x, Snd_s00a2_3360* first, Snd_s00a2_3360* last);  // 0x00a212b0
    void spliceAll(Snd_s00a2_3360* pos, ElemList& x);                      // 0x00a21310
    void merge(ElemList& x, CompareFn pCompare);                // 0x00a22410
};
struct RBTree {
    u8      pad00[0x1c];
    void*   mpFreeList;                 // +0x1c
    u8      pad20[0x2c - 0x20];
    u32     mAllocator;                 // +0x2c
    void*  AllocNode2(const void* src);         // 0x00a243e0
    RBNode_s00a2_3360* CloneNode(RBNode_s00a2_3360* src, RBNode_s00a2_3360* parent);   // 0x00a24530
};
inline ElemList::ElemList()
{
    anchor.next = &anchor;
    anchor.prev = &anchor;
}
__forceinline ElemList::~ElemList()
{
    SNode* n = anchor.next;
    while (n != &anchor) {
        SNode* next = n->next;
        n->prev = 0;
        n->next = 0;
        n = next;
    }
    anchor.next = 0;
    anchor.prev = 0;
}
struct Elem20 { u32 d0, d1, d2, d3; void* ref; };
struct DeviceDriver { void ctor(const char* name); };           // 0x011e5d80
struct Mutex_s00a2_3360 {
    u32 a;
    void ctor(int a, int b);           // 0x009222a0
    int  Lock(const void* name);       // 0x009221b0
    int  Unlock();                     // 0x00922270
};
struct MutexGuard_s00a2_3360 {
    Mutex_s00a2_3360* m;
    MutexGuard_s00a2_3360(Mutex_s00a2_3360* mm, const char* n) : m(mm) { m->Lock(n); }
    ~MutexGuard_s00a2_3360() { m->Unlock(); }
};
struct Stopwatch_s00a2_3360 {
    long long mnStartTime;         // +0
    long long mnTotalElapsedTime;  // +8
    int       mnUnits;             // +0x10
    float     mfCyclesToUnitsCoefficient; // +0x14
    void      ctor(int units, int b);                       // 0x0093a560
    long long GetElapsedTimeFloat();                        // 0x0093a3a0
};
struct ProfileTimer {
    Stopwatch_s00a2_3360 sw;                  // +0
    void*     mpAccumulator;       // +0x18
    ProfileTimer(void* acc);       // 0x00a248a0
    void Accumulate();             // 0x00a24900
};
struct ScopedTimer {
    Stopwatch_s00a2_3360 sw;                  // +0
    float*    acc;                 // +0x18
    ScopedTimer(float* a);         // 0x00a248a0
    ~ScopedTimer()
    {
        *acc = (float)sw.GetElapsedTimeFloat() * sw.mfCyclesToUnitsCoefficient + *acc;
    }
};
struct RDD {
    void*   vftable;               // +0
    u8      pad04[0x14 - 4];
    void**  mpBegin;               // +0x14
    void**  mpEnd;                 // +0x18
    void**  mpCapacity;            // +0x1c
    u8      pad20[0x28 - 0x20];
    Mutex_s00a2_3360   mMutex;                // +0x28
    u8      pad2c[0x58 - 0x2c];
    float   mfAccum;               // +0x58
    ProfileTimer mTimer;           // +0x5c

    void    Construct();           // 0x00a247f0
    void*   FindById(void* id);                              // 0x00a24970
    void*   FindAndCall1(void* id, void* a, void* b, void* c, void* d); // 0x00a24a90
    int     FindAndCall2(void* id, void* a, void* b, void* c, void* d); // 0x00a24b40
    long long FindAndCall3(void* id, void* a, void* b, void* c, void* d, void* e); // 0x00a24bf0
    void*   FindAndCall4(void* id);  // 0x00a24cb0
    long long FindAndCall5(void* id); // 0x00a24d60

    bool    Tick3(void* a, void* b, void* c);   // 0x00a24930
};
// ---- items of slice s00a23360 end
// Construction view of RDD (0x00a247f0): the driver base and the vector have destructors; the mutex is built last.
struct RDDDriverBase {
    RDDDriverBase(const char* name);  // 0x011e5d80
    virtual ~RDDDriverBase();
    u8 pad04[0x14 - 4];
};
struct RDDPtrVec {
    void** mpBegin; void** mpEnd; void** mpCapacity;
    RDDPtrVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~RDDPtrVec();
};
struct RDDMutex : Mutex_s00a2_3360 {
    RDDMutex() { ctor(0, 1); }
    ~RDDMutex();
};
struct RDDCtorView : RDDDriverBase {
    RDDPtrVec mVec;               // +0x14
    u8        pad20[0x28 - 0x20];
    RDDMutex  mMutex;             // +0x28
    RDDCtorView();
};

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
__declspec(noinline) RBNode_s00a2_3360* __stdcall RB_AllocNode(const RBNode_s00a2_3360* src, RBNode_s00a2_3360* parent);   // defined at 0x00a245e0, called earlier in the TU

// ---- items of slice s00a24e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_tid1;      // 0x0166d9f8
extern unsigned g_tid2;      // 0x0166d9fc
extern const unsigned g_msgIds[7];   // 0x01452b6c
extern const char g_iidErr[];        // 0x01552da0
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);
void  operator delete(void* p, const char* name, int a, int b, int c, int d);
struct Obj_s00a2_4e10 {
    virtual void AddRef();
    virtual void Release();
    virtual void Free();
};
struct TObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct ARC {
    Obj_s00a2_4e10* p;
    ARC() : p(0) {}
    ARC(Obj_s00a2_4e10* o) : p(o) { if (p) p->AddRef(); }
    ARC& assign(Obj_s00a2_4e10* o);        // 0x00b5f950 (out of line)
    ~ARC() { if (p) p->Release(); }
};
struct Stopwatch_s00a2_4e10 {
    char  pad[0x14];
    float coeff;
    __int64 GetElapsedTimeFloat();    // 0x0093a3a0
};
struct ScopedTimer_s00a2_4e10 {
    Stopwatch_s00a2_4e10 sw;
    float*    acc;
    int       pad;
    ScopedTimer_s00a2_4e10(float* a);            // 0x00a248a0
    ~ScopedTimer_s00a2_4e10()
    {
        *acc = (float)sw.GetElapsedTimeFloat() * sw.coeff + *acc;
    }
};
struct Mutex_s00a2_4e10 {
    void Lock(const char* name);      // 0x009221b0
    void Unlock();                    // 0x00922270
};
struct MutexGuard {
    Mutex_s00a2_4e10* m;
    MutexGuard(Mutex_s00a2_4e10* mm, const char* n) : m(mm) { m->Lock(n); }
    ~MutexGuard() { m->Unlock(); }
};
struct Prim {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void Update(int a, float b, int c);   // slot 3
};
struct PNode { unsigned key; Prim* val; PNode* next; };
struct PIter { PNode* node; PNode** bucket; PIter() {} PIter(const PIter& o) { node = o.node; bucket = o.bucket; } };
struct PIt {
    PNode*  node;
    PNode** bucket;
    PIt(PNode* n, PNode** b) : node(n), bucket(b) {}
    void IncrBucket() { ++bucket; while (*bucket == 0) ++bucket; node = *bucket; }
    void Incr() { node = node->next; while (node == 0) { ++bucket; node = *bucket; } }
};
struct PHT {
    int      pad;
    PNode**  mBuckets;
    unsigned mBucketCount;
    PIter    find(const unsigned& key);   // 0x00645ed0
    PNode*   end() { return mBuckets[mBucketCount]; }
    PNode*   begin(PNode*** bucketOut)
    {
        PNode** b = mBuckets;
        PNode* n = *b;
        if (n == 0) {
            ++b;
            while (*b == 0) ++b;
            n = *b;
        }
        *bucketOut = b;
        return n;
    }
};
__forceinline void Zero(int* p) { _InterlockedExchange((volatile long*)p, 0); }
struct PropBase : Obj_s00a2_4e10 {
    int rc;
    int f8, fc, f10;
    __forceinline PropBase() { Zero(&rc); f8 = 0; fc = 0; f10 = 0; }
};
struct PropList : PropBase {
    int  f14;
    int* mpData;
    int  f1c, f20;
    __forceinline PropList() { f14 = -1; mpData = 0; f1c = 0; f20 = 0; }
    virtual void AddRef();
    virtual void Release();
};
struct Str16 {
    wchar_t* b; wchar_t* e; wchar_t* cap; int alloc;
    const wchar_t* c_str() const { return b; }
    ~Str16() { if ((int)(((char*)cap - (char*)b) & ~1) > 2 && b) operator_delete__(b); }
};
Str16 ConvertToString16(const char* s, int n);   // 0x0093c5a0
struct StrOut { int a, b, c; };
typedef void (__cdecl* StringFn)(StrOut*, int, int, int, int, int);
extern StringFn g_pfnString;                     // 0x0154c464
struct RbIter { int* n; RbIter() {} RbIter(const RbIter& o) { n = o.n; } };
struct RbTree {
    char pad[0x14];
    int  size;      // tree object at owner+4: size at owner+0x18
    RbIter find(const unsigned& key);    // 0x00e5c780
};
void RBTreeIncrement(void* n);                 // 0x00921580
void RBTreeErase(void* n, void* anchor);       // 0x00921880
struct Obj30 {
    Obj_s00a2_4e10* Init();                       // 0x00a22cf0
};
struct Obj30b {
    Obj_s00a2_4e10* Init();                       // 0x00a22cf0 (identical code folded)
};
struct Tracker {
    char   pad0[0x14];
    TObj**  mBegin;      // +0x14
    TObj**  mEnd;        // +0x18
    char   pad1[0x28 - 0x1c];
    Mutex_s00a2_4e10  mMutex;      // +0x28
    char   pad2[0x58 - 0x28 - 4];
    float  mElapsed;    // +0x58
    // ScopedTimer anchor value lives at +0x5c (arg to timer ctor)
    char   pad3[4];

    void  Remove(TObj* o);               // 00a24e10
    void  Process(TObj* o);              // 00a24f50
    TObj*  Find(TObj* o);                 // 00a24970
};
struct RcMap {
    char   pad[4];
    RbTree mTree;      // +4
    void Release(unsigned key);         // 00a25000
};
struct Factory {
virtual void f00();
virtual void f01();
virtual void f02();
virtual void f03();
virtual void f04();
virtual void f05();
virtual void f06();
virtual void f07();
    virtual void f08();
    virtual bool Create(const char* a, Obj_s00a2_4e10* o, int c, int d);   // +0x24
    bool MakeProps(const char* a, Obj_s00a2_4e10** out, int c, int d);     // 00a25090
    bool MakeAudio(const char* a, ARC* out, int c, int id);     // 00a25190
};
struct Namer {
virtual void n00();
virtual void n01();
virtual void n02();
virtual void n03();
virtual void n04();
virtual void n05();
virtual void n06();
virtual void n07();
virtual void n08();
virtual void n09();
virtual void n0a();
virtual void n0b();
virtual void n0c();
virtual void n0d();
virtual void n0e();
virtual void n0f();
virtual void n10();
virtual void n11();
virtual void n12();
virtual void n13();
virtual void n14();
virtual void n15();
virtual void n16();
virtual void n17();
virtual void n18();
virtual void n19();
virtual void n1a();
virtual void n1b();
virtual void n1c();
virtual void n1d();
virtual void n1e();
virtual void n1f();
virtual void n20();
virtual void n21();
    virtual void Dispatch(wchar_t* name, int a, int b, double c);   // +0x88
    void Convert(const char* s, int a, int b, double c);            // 00a25980
};
struct Subscription_s00a2_4e10 {
    void UpdateOutput(void* outputs);   // 0x00a22820
};
struct FNode { unsigned key; float val; FNode* next; };
struct GIter { void* node; void** bucket; GIter() {} GIter(const GIter& o) { node = o.node; bucket = o.bucket; } };
struct FHT {
    int      pad;
    FNode**  mBuckets;
    unsigned mBucketCount;
    GIter*   find(GIter* out, const unsigned& key);   // 0x00645ed0 (pair<uint,float>)
    FNode*   end() { return mBuckets[mBucketCount]; }
};
struct NNode { unsigned key; FHT inner; };
struct NHT {
    int      pad;
    NNode**  mBuckets;
    unsigned mBucketCount;
    GIter*   find(GIter* out, const unsigned& key);   // 0x00a23b00
    NNode*   end() { return mBuckets[mBucketCount]; }
};
struct SubNode { unsigned key; char val[0x20]; SubNode* next; };
struct SubHT {
    int       pad;
    SubNode** mBuckets;
    unsigned  mBucketCount;
    SubNode*  end() { return mBuckets[mBucketCount]; }
};
struct SubIt {
    SubNode*  node;
    SubNode** bucket;
    SubIt(SubNode* n, SubNode** b) : node(n), bucket(b) {}
    void IncrBucket() { ++bucket; while (*bucket == 0) ++bucket; node = *bucket; }
    void Incr() { node = node->next; while (node == 0) { ++bucket; node = *bucket; } }
};
struct AudioSys {
    char pad0[0x3a4];
    char mOutputs[0x60];
    PHT  mPrims;                  // +0x404 (buckets +0x408, count +0x40c)
    char pad2[0x11b3c8 - 0x404 - sizeof(PHT)];
    NHT  mNested;                 // +0x11b3c8
    char pad3[0x1277b4 - 0x11b3c8 - sizeof(NHT)];
    SubHT mSubs;                  // +0x1277b4 (buckets +0x1277b8, count +0x1277bc)

    bool CallPrim(unsigned id, int a, float b, int c);       // 00a25a40
    void CallAll(int a, float b, int c);                     // 00a25aa0
    bool HasPrim(unsigned id);                               // 00a25b20
    void UpdateOutput();                                     // 00a25b60
    bool GetFloat(unsigned k1, unsigned k2, float* out);     // 00a25bd0
};
struct Server {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
    virtual void m8();
    virtual void Register(void* handler, unsigned id);        // +0x24
};
Server* GetMessagingServer();                                  // 0x00883860
struct IHandlerRC {
    virtual void h0();
    virtual void h1();
    virtual void AddRef();       // +8
    virtual void Release();      // +0xc
};
struct ISystem0 {
    virtual void i0();
};
struct Config {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c0a();
    virtual void Get(unsigned key, int* out);                 // +0x2c
};
struct DbgObj {
    static void* operator new(unsigned size, const char* n, int a, int b, int c, int d);   // 0x00926020
    static void operator delete(void* p, const char* n, int a, int b, int c, int d);
    DbgObj();                                                                               // 0x00a19d60
    char pad[0x70];
};
struct ErrIf {
virtual void e0();
virtual void e1();
virtual void e2();
    virtual bool Query(const void* iid, ARC* out, int a, int b, int c, int d);   // +0xc
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
virtual void e10();
virtual void e11();
virtual void e12();
virtual void e13();
virtual void e14();
virtual void e15();
    virtual void e16();
    virtual void Set(int a, DbgObj* o, int b);                                   // +0x44
};
ErrIf* GetObjectError();                                        // 0x008de1a0
struct CharMap {
    CharMap(int a, int b, int c, int d, int e);                  // 0x00926350
    char pad[0x50];
};
struct Queue {
    void Init(int n);                                            // 0x00a102a0
    char pad[0x50];
};
struct ThreadParams {
    int  pad0[2];
    int  priority;
    int  pad1[2];
    const char* name;
    ThreadParams();                                              // 0x00922900
};
unsigned GetDefaultAffinity();                                   // 0x00922920
struct Cond {
    char pad[0x60];
    int Wait(Mutex_s00a2_4e10* m, const char* name);                        // 0x00921f80
};
struct Thread {
    char pad[8];
    void Begin(void* proc, void* arg, ThreadParams* p, unsigned aff);   // 0x00922f30
};
unsigned GetThreadId();                                          // 0x00921cc0
void TickProc(void*);                                            // 0x00a228d0
struct Ring {
    unsigned* cBegin;
    unsigned* cEnd;
    char      pad[0xfbc - 8];
    unsigned* mBegin;
    unsigned* mEnd;
    int       mSize;

    __forceinline void Push(unsigned v)
    {
        *mEnd = v;
        mEnd += 1;
        if (mEnd == cEnd) mEnd = cBegin;
        if (mEnd == mBegin) {
            mBegin += 1;
            if (mBegin == cEnd) mBegin = cBegin;
        } else {
            mSize += 1;
        }
    }
};
struct System_s00a2_4e10;
extern System_s00a2_4e10*  g_pSystem;   // 0x0166d9f4
struct System_s00a2_4e10 : ISystem0, IHandlerRC {
    // +8: EA::Messaging::AutoHandler
    Server*   mpServer;
    void*     mpHandler;
    const unsigned* mpIdArray;
    int       mnIdArrayCount;
    int       mnPriority;
    char      pad1c[0x20 - 0x1c];
    Thread    mTickThread;                 // +0x20
    Cond      mCondInit;                   // +0x28 (+0x28 .. +0x88)
    bool      mbExitThread;                // +0x88
    char      pad89[0x8c - 0x89];
    int       mStarted;                    // +0x8c
    char      pad90[0x94 - 0x90];
    bool      mbInitialized;               // +0x94
    char      pad95[0xb8 - 0x95];
    Mutex_s00a2_4e10     mMutex;                      // +0xb8
    char      padbc[0x1f8 - 0xb8 - sizeof(Mutex_s00a2_4e10)];
    ARC       mpConfiguration;             // +0x1f8
    char      pad1fc[0x214 - 0x1fc];
    Queue     q214;
    Queue     q264;
    char      pad2b4[0x304 - 0x2b4];
    Queue     q304;
    Queue     q354;
    char      pad3a4[0x119ba0 - 0x3a4];
    CharMap*  mpCharMap;                   // +0x119ba0
    char      pad119ba4[0x12c9ac - 0x119ba4];
    Ring      mExternalIdsPool;            // +0x12c9ac
    char      padring1[0x1366d4 - 0x12c9ac - sizeof(Ring)];
    Ring      mAllocatedIdsPool;           // +0x1366d4

    bool Init();                           // 00a252b0
};
    void operator_delete__(...); // 0x00f47380
// ---- items of slice s00a24e10 end

// ---- items of slice s00a2a020 begin (TODO(rewrite): local stubs, replace by canonical classes)
#undef FIXED_CTOR
void* operator new(unsigned int);
struct HashBase {
    void ctorA(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23570
    void ctorB(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23620
    void ctorC(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23780
    void ctorD(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23c70
    void ctorE(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23e40
    void ctorF(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23f50
    void ctorG(u32, void*, void*, void*, u32, void*, void*);   // 0x00a23990
    void ctorH(u32, void*, void*, void*, u32, void*, void*);   // 0x00a24160
    void rehashA(u32);                                          // 0x00a22220
    void rehashB(u32);                                          // 0x00a22370
    void DoFreeNodes(void*, void*);                             // 0x00a1b6c0
};
template<class R, class A1> static inline R vc_s00a2_a020(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }
struct Submix {
    void* vftable;                       // +0
    void  DisconnectFromSubmix();        // 0x00a21390
    bool  ConnectToSubmix(Submix* o);    // 0x00a27ed0
};
struct SysLike { void* vftable; bool ConnectSubmixTree(); };
struct HashFindStub { void find(void* sret, const void* key); };   // 0x00645ed0
struct BoolTag { bool b; };                                        // 1-byte by-value tag
struct SmallStubs {
    int  GetOrInsert(int* key);
    void Insert(void* sret, const int* key, BoolTag tag);          // 0x00a136f0
    void Dtor();
    void DestroyBuckets(int param_2, u32 param_3);
    int  EraseRange(int param_2, int param_3);
    int* VecIntInsert(int* param_2, int* param_3);
};
struct E12 { u32 a, b, c; };
struct Vec12 {
    void* mpBegin;   // +0
    E12*  mpEnd;     // +4
    E12*  mpCap;     // +8
    void pushEmpty();
    void DoInsertValue(E12* pos, void* val);   // 0x00a27910
};
struct E18 { int a; int b; float f; int c; int d; int e; };
struct Vec18 {
    void* mpBegin;   // +0
    E18*  mpEnd;     // +4
    E18*  mpCap;     // +8
    void pushEmpty();
    void DoInsertValue(E18* pos, E18* val);   // 0x00a27a40
};
struct Zone_s00a2_a020 { u32 d[0xb]; };
struct ZoneVec {
    void* mpBegin;   // +0
    u8*   mpEnd;     // +4
    u8*   mpCap;     // +8
    void push_back(const Zone_s00a2_a020* v);
    void DoInsertValue(u8* pos, const Zone_s00a2_a020* val);   // 0x00a27b90
};
struct RBTreeStub { void DoNukeSubtree(void*); };   // 0x009a9600
void* ARCopy(void* a, void* b, void* c);   // 0x00a22730
// ---- items of slice s00a2a020 end

// ---- items of slice s00a2c6c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<class R> __forceinline R vcall(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template<class R, class A1> __forceinline R vcall(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }
template<class R, class A1, class A2> __forceinline R vcall(void* o, int off, A1 a1, A2 a2)
{ return ((R (__thiscall*)(void*, A1, A2))(*(void***)o)[off / 4])(o, a1, a2); }
template<class R, class A1, class A2, class A3> __forceinline R vcall(void* o, int off, A1 a1, A2 a2, A3 a3)
{ return ((R (__thiscall*)(void*, A1, A2, A3))(*(void***)o)[off / 4])(o, a1, a2, a3); }
template<class R, class A1, class A2, class A3, class A4>
__forceinline R vcall(void* o, int off, A1 a1, A2 a2, A3 a3, A4 a4)
{ return ((R (__thiscall*)(void*, A1, A2, A3, A4))(*(void***)o)[off / 4])(o, a1, a2, a3, a4); }
template<class R, class A1, class A2, class A3, class A4, class A5>
__forceinline R vcall(void* o, int off, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{ return ((R (__thiscall*)(void*, A1, A2, A3, A4, A5))(*(void***)o)[off / 4])(o, a1, a2, a3, a4, a5); }
namespace EA {
namespace Audio {
struct Vec3  { float x, y, z; };
}
}
namespace EA {
namespace Audio {
struct Mat33 { float m[9]; };
}
}
namespace EA {
namespace Audio {
struct Key { u32 instance, type, group; };
}
}
namespace EA {
namespace Audio {
struct Command_s00a2_c6c0 {
    u8* mCommandStart; u8* mCommandEnd; u8* mCommandPtr;
    u32 mCommandId; u32 mCommandSize; u32 mNumParameters;
    u32  Type();                                   // 0xfc7e50 (returns mCommandId)
    bool SetT1(int id, int* type, int* size);      // 0xa0fa50
    bool GetFloat(int id, float* out);             // 0xa0fa70
    bool GetUint32(int id, u32* out);              // 0xa0fab0
    const char* GetString8(int id);                // 0xa0fb60
    bool GetVoidPtr(int id, void** out);           // 0xa0fb90
    void* GetData(int id, u32* outSize);           // 0xa0fbd0
    bool GetVector3(int id, float* out);           // 0xa0fc10
    bool GetMatrix33(int id, float* out);          // 0xa0fc60
};
}
}
namespace EA {
namespace Audio {
struct IVisualEffect { void** vftable; };
}
}
namespace EA {
namespace Audio {
struct VisualEffectRef {
    IVisualEffect* mp;
    VisualEffectRef() : mp(0) {}
    ~VisualEffectRef() { if (mp) vcall<void>(mp, 4); }
    void** AsPPTypeParam();                        // 0xa16f40
};
}
}
namespace EA {
namespace Audio {
struct ListNode { ListNode* next; ListNode* prev; };
}
}
namespace EA {
namespace Audio {
struct Sound_s00a2_c6c0 { void** vftable; u32 pad[3]; ListNode node; };
}
}
namespace EA {
namespace Audio {
struct SoundIter { Sound_s00a2_c6c0* p; SoundIter() : p(0) {} };
}
}
namespace EA {
namespace Audio {
struct SoundList {
    ListNode anchor;
    SoundIter begin();                             // 0xa21c70
    SoundIter end();                               // 0xa21c90
};
}
}
namespace EA {
namespace Audio {
static inline Sound_s00a2_c6c0* FromNode(ListNode* n) { return n ? (Sound_s00a2_c6c0*)((char*)n - 0x10) : 0; }
}
}
namespace EA {
namespace Audio {
static inline Sound_s00a2_c6c0* NextSound(Sound_s00a2_c6c0* s)   { return FromNode(s->node.next); }
}
}
namespace EA {
namespace Audio {
struct HashNode { u32 key; void* value; HashNode* next; };
}
}
namespace EA {
namespace Audio {
struct HashIter {
    HashNode* node; HashNode** bucket;
    HashIter() : node(0), bucket(0) {}
};
}
}
namespace EA {
namespace Audio {
struct StyleTable {
    u32 pad0;
    HashNode** mpBucketArray;
    u32 mnBucketCount;
    HashIter find(const u32& key) const;           // 0x645ed0
};
}
}
namespace EA {
namespace Audio {
struct UIntVector {
    u32* mpBegin; u32* mpEnd; u32* mpCapacity;
    void DoInsertValue(u32* pos, const u32& v);    // 0x899480
};
}
}
namespace EA {
namespace Audio {
struct Lookup12 { u32 a, b, c; Lookup12() {} };
}
}
namespace EA {
namespace Audio {
struct LookupTable {
    Lookup12 Find(const u32& key);                 // 0xa27600
};
}
}
namespace EA {
namespace Audio {
struct System_s00a2_c6c0 {
    void** vftable;                                // ISystem
    u32 pad0[(0x3fc - 4) / 4];
    u8  mbFlag3fc;                                 // +0x3fc
    u8  pad3fd[7];
    StyleTable mStyleTable;                        // +0x404
    u32 pad1[(0x13769c - 0x404 - sizeof(StyleTable)) / 4];
    UIntVector mUIntVector;                        // +0x13769c
    u32 pad2[(0x13795c - 0x13769c - sizeof(UIntVector)) / 4];
    LookupTable mLookup;                           // +0x13795c
    u32 pad3[(0x157438 - 0x13795c - sizeof(LookupTable)) / 4];
    SoundList mSounds;                             // +0x157438
    u32 pad4[(0x15b6d8 - 0x157438 - sizeof(SoundList)) / 4];
    Vec3  mListenerPos[2];                         // +0x15b6d8 (indexed by listener id)
    Mat33 mListenerMat[1];                         // +0x15b6f0 (indexed by listener id)
    u32 pad5[(0x15bbe4 - 0x15b6f0 - sizeof(Mat33)) / 4];
    Vec3 mVec15bbe4;                               // +0x15bbe4
    u8   mbHasVec15bbe4;                           // +0x15bbf0

    bool DoCommand(Command_s00a2_c6c0* cmd);  // 0x00a2c6c0 (EA::Audio::System::DoCommand)
};
}
}
// ---- items of slice s00a2c6c0 end

// ---- items of slice s00a2d790 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned char uchar;
struct XF;           // generic stub for external __thiscall callees
struct AudioSystem;
struct LastInstr;
struct XF {
    void* hashtable_find(void* out, void* key);      // 0x645ed0 (arg1 = out iterator, arg2 = key)
    void* rbtree_find(void* out, void* key);         // 0xe5c780
    void* FUN_00a2a150(void* out);
    void* FUN_00a2a510(void* out);
    void  FUN_00a276e0(void* a, void* b);
    void  FUN_00a2b230(void* a, void* b, void* c, void* d);
    void  FUN_00a26a20(void* a, void* b, void* c);
    void  FUN_00a26ce0(void* a, void* b, void* c);
    void  FUN_00a26fa0(void* a);
    void  FUN_00a2ac20(void* a, void* b);
    void  FUN_00a2af30(void* a, void* b);
    void  FUN_00a22220(uint n);
    void  FUN_00a2bb30();
    void  FUN_00a21390();
    void  AutoRef_op(uint* p);
    void* DoInsertValue(void* a, void* b, void* c);
    int   DoFreeNodes(void* a, void* b);
    void  DoNukeSubtree(void* a);
    void  StopwatchCtor(void* a, void* b);
    void  Noop();
};
void* __cdecl operator_new(uint, const char*, int, int, const char*, int);   // 0x00f473a0
void  __cdecl operator_delete(void*) throw();
struct IUnk_a26da0 { virtual void AddRef(); virtual void Release(); };
void* __cdecl FUN_00a17090(uint size);
void* __cdecl FUN_00a17100(void* p);
void __cdecl FUN_00fccdd0(unsigned id);   // 0x00fccdd0
void FUN_00a26ce0();   // 0x00a26ce0 hashtable insert (thiscall, called through a cast)
void* __cdecl copy_impl(void* first, void* last, void* dst);   // 0x006782c0
struct AudioSystem {
    uchar pad[0x140000];

    // 00a2d790
    bool RegisterPrimitive(void* p);
    // 00a2d880
    bool  FUN_00a2d880(uint key, void* out);
    // 00a2d940 : ctor
    void* FUN_00a2d940(void* arg);
    // 00a2d990
    int FUN_00a2d990(void* arg);
    // 00a2d9d0 : dtor
    void* FUN_00a2d9d0(uchar flags);
    // 00a2da30
    void FUN_00a2da30();
    // 00a2dc40
    void SetupPropertyAggregationRules();
    // 00a2de20
    bool DestroySubmixes();
    // 00a2dfe0  (retail call site 0x00a2e5b5 keeps this out of line)
    __declspec(noinline) void FUN_00a2dfe0(void* p);
    // 00a2e060
    uint& FUN_00a2e060(const uint& k);
    // 00a2e0e0
    int FUN_00a2e0e0(uint* p);
    // 00a2e1b0
    void* FUN_00a2e1b0(void* out, void* node, void* parent);
    // 00a2e260
    void FUN_00a2e260(void* p);
    // 00a2e2f0
    AudioSystem* FUN_00a2e2f0(void* p);
    // 00a2e420
    void* FUN_00a2e420(void* p);
    // 00a2e4c0
    void* FUN_00a2e4c0(void* p);
};
static void* vc_s00a2_d790(void* obj, int off) {
    return ((void**)*(void**)obj)[off / 4];
}
extern "C" void* DAT_016e61a8;
extern "C" void  FUN_0112c600();
extern "C" void  FUN_0112c620();
// ---- items of slice s00a2d790 end

// ---- items of slice s00a2e650 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl ObjectError();  // 0x008de1a0
void* __cdecl EaNew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
void __cdecl EaDelete(void* p);                                                                    // 0xf47380
struct MapUU {
    __declspec(noalias) int& operator[](const uint32_t& key);  // 0x00a2e060
};
static inline void ObjAddRef(void* p) { VCALL(void(__thiscall*)(void*), p, 0)(p); }
static inline void ObjRelease(void* p) { VCALL(void(__thiscall*)(void*), p, 4)(p); }
struct FxRef {
    void* p;
    FxRef() : p(0) {}
    ~FxRef()
    {
        if (p)
            ObjRelease(p);
    }
    FxRef& operator=(void* o)
    {
        if (o != p) {
            void* old = p;
            if (o)
                ObjAddRef(o);
            p = o;
            if (old)
                ObjRelease(old);
        }
        return *this;
    }
    void** AsPP();  // 0x00a16f40
};
struct FxRef2 {  // AutoRefCount with out-of-line assignment (0x00b5f950)
    void* p;
    FxRef2() : p(0) {}
    ~FxRef2()
    {
        if (p)
            ObjRelease(p);
    }
    void Assign(void* o);
};
struct Stopwatch_s00a2_e650 {
    unsigned __int64 mnStartTime;
    unsigned __int64 mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    Stopwatch_s00a2_e650(int units, int start);  // 0x0093a560
    void RestartInline()
    {
        if (mnUnits == 1) {
            unsigned __int64 t = __rdtsc();
            ((unsigned*)&mnStartTime)[1] = (unsigned)(t >> 32);
            ((unsigned*)&mnStartTime)[0] = (unsigned)t;
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mnStartTime = t;
        }
        mnTotalElapsedTime = 0;
    }
};
struct HIter {
    void* node;
    void** bucket;
    HIter() {}
    HIter(const HIter& o) : node(o.node), bucket(o.bucket) {}
};
struct HT1 {  // key -> node table at +0x1277b4
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    HIter find(const unsigned& key);  // 0x00a23c10
    HIter erase(HIter it);            // 0x00a2e1b0
    void* End() { return mpBuckets[mnBuckets]; }
};
struct Pair2 {
    unsigned key;
    FxRef val;
    Pair2(const unsigned& k, void* v);  // 0x00a21d90
};
struct HT2 {  // table at +0x157440
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    HIter find(const unsigned& key);        // 0x00645ed0
    HIter Insert(const Pair2& p);           // 0x00a27630
    HIter erase(HIter it);                  // 0x00d2c9f0
    void* End() { return mpBuckets[mnBuckets]; }
};
struct HT4 {  // table at +0x404 (unsigned -> int)
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    HIter find(const unsigned& key);        // 0x00645ed0
    HIter* findInto(HIter* out, const unsigned& key); // explicit result buffer, 0x00645ed0
    HIter* eraseInto(HIter* out, HIter it); // explicit result buffer, 0x00b51640
    HIter Op(const unsigned* id);           // 0x00a274d0
    HIter erase(HIter it);                  // 0x00b51640
    void* End() { return mpBuckets[mnBuckets]; }
};
struct LPair {
    void* cur;
    void* ve;
};
struct LIter {
    void* p;
    void Next();  // 0x00a21290
};
struct List3 {  // at +0x157438
    void Begin_(LIter* out);               // 0x00a21c70
    void End_(LIter* out);                 // 0x00a21c90
    void Insert(LPair** pp);               // 0x00a21cb0
};
bool __cdecl MatchEntry(void* entry, bool flag, void* g48);  // 0x00a20df0
struct Props {
    void** vt;
    int pad[2];
    int m0c;   // 0x0166da38
    int m10;   // 0x0166da3c
    Props();           // 0x00a107a0
    ~Props();          // 0x013c17e0 (atexit)
    void Set(void* o);   // 0x00a108e0
    void Load(void* o);  // 0x00a10920
};
struct G48 {
    char b0;
    char b1;
    char pad[0x12];
    int kind;  // +0x14
    char pad2[0x48 - 0x18];
};
extern G48 g_g48;  // 0x0166da48
#define AT(T, base, off) (*(T*)((char*)(base) + (off)))
struct MgrBase {
    bool Create(unsigned name, unsigned id, void* existing, float* pos, void** out);  // 0xa2e650
    void SetEntry(unsigned key, void* val);                                           // 0xa2edd0
    void PostEvent(unsigned a, unsigned b, unsigned c, unsigned d, void* ref);        // 0xa2ee40
    bool RemoveEntry(void* obj);                                                       // 0xa2eed0
    void Rebuild();                                                                    // 0xa2ef60
};
struct EntryVal {
    char pad[0x18];
    int m18;
    void Assign(void* v);  // 0x00a25000
};
struct EventMsg {
    unsigned a, b, c, d;
    void* ref;
    EventMsg(unsigned a_, unsigned b_, unsigned c_, unsigned d_, void* r) : a(a_), b(b_), c(c_), d(d_), ref(r)
    {
        if (ref)
            ObjAddRef(ref);
    }
    __forceinline EventMsg(const EventMsg& o) : a(o.a), b(o.b), c(o.c), d(o.d), ref(o.ref)
    {
        if (ref)
            ObjAddRef(ref);
    }
    ~EventMsg()
    {
        if (ref)
            ObjRelease(ref);
    }
    static void* operator new(size_t, void* q) throw() { return q; }
    static void operator delete(void*, void*) throw() {}
};
struct EventQueue {
    void Push(const EventMsg& m);  // 0x00a2e260
};
struct IdObj {
    virtual void v0();
    virtual void v1();
    virtual unsigned GetId();  // +8
};
struct HT1b {
    void Remove(const unsigned* key);  // 0x00a2e0e0
};
struct SNode_s00a2_e650 {
    void* sub;
    SNode_s00a2_e650* next;
};
struct Tree {
    void DoNukeSubtree(void* n);  // 0x009a9600
};
struct Snap {
    int pad0;
    Tree tree;   // +4
    int pad8[2];
    SNode_s00a2_e650* head; // +0x10
    Snap(MapUU* m);  // 0x00a2d940
    ~Snap()
    {
        SNode_s00a2_e650* p = head;
        while (p) {
            tree.DoNukeSubtree(p->sub);
            SNode_s00a2_e650* nx = p->next;
            EaDelete(p);
            p = nx;
        }
    }
};
struct Elem {
    unsigned key;
    unsigned val;
    unsigned third;
};
struct EVec {
    Elem* b;
    Elem* e;
    Elem* c;
    ~EVec()
    {
        if (b && ((int*)b)[-1] != 0)
            EaDelete(b);
    }
};
struct HT5 {  // table at +0x33d4
    char pad[4];
    void** mpBuckets;
    unsigned mnBuckets;
    unsigned mnCount;
    void DoFreeNodes(void** buckets, unsigned n);  // 0x00a1b6c0
    HIter find(const unsigned& key);                // 0x00645ed0
    void* End() { return mpBuckets[mnBuckets]; }
};
struct P2 {
    unsigned a, b;
};
struct HT5I {
    HIter Insert(const P2* p, bool flag);  // 0x00a26ce0
};
class cTypeMapHolder {
public:
    char pad[0x118a5c];
    MapUU mMap;                                               // +0x118a5c
    void SetTypePriority(uint32_t type, uint32_t priority);   // 0xa2f180
    void InitDefaultPriorities();                             // 0xa2f1a0
};
struct MappedVal {
    char d[0x1e0];
    MappedVal(const MappedVal& o);  // 0x00a2e2f0
};
struct HNodeV {
    unsigned key;
    MappedVal val;
    int m1e4;
};
struct SrcPair {
    unsigned key;
    MappedVal val;
};
struct NodePool_s00a2_e650 {
    char pad[0x1c];
    void* mpHead;  // +0x1c
    char pad20[0x2c - 0x20];
    unsigned mnNodeSize;  // +0x2c
    HNodeV* Alloc(const SrcPair* src);  // 0x00a27010 (NodePool::Alloc)
};
// ---- items of slice s00a2e650 end

// ---- items of slice s00a30460 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl FUN_011e0744(void*, void*, int);              // eastl::vector<bool>::DoInsertValue
unsigned int __cdecl FUN_00921340(unsigned int);
unsigned int __stdcall FUN_009213c0(unsigned int);
template<class R> static inline R vc0(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template<class R, class A1> static inline R vc_s00a3_0460(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }
struct MapNode { u32 key; float val; u32 next; };
struct SysMap {
    void* f0;
    MapNode** buckets;   // +4
    u32       count;     // +8
    void insert(u32 key, float val);
};
struct FixedPoolBase {
    void* mpHead;
    void* pad[7];
    void init(void* base, u32 size, u32 nodeSize, u32 align, u32 flags);
};
struct HashBaseCD {
    void ctor(u32, void*, void*, void*, u32, void*, void*);   // 0x00a236d0
    void rehash(u32);                                          // 0x00a21eb0
};
struct FixedMap30e10 {
    int ctor(void* a2, void* a3);
};
struct NodeMap {
    void* f0;
    int*  mpBuckets;       // +4
    u32   mnBucketCount;   // +8
    int   mnElementCount;  // +0xc
    void FreeNode(void* node);   // 0x00a2f660
    int  eraseKey(u32* key);
};
struct FixedVec11 {
    u32* mpBegin;    // +0
    u32* mpEnd;      // +4
    u32* mpCap;      // +8
    u32* f0c;        // +0xc
    u32* f10;        // +0x10
    u32* f14;        // +0x14
    u32  storage[1000];  // +0x18
    u32  fStart;     // +0xfbc
    u32  fEnd;       // +0xfc0
    u32  fCount;     // +0xfc4
    void resize(int n);   // 0x0089cb60
};
struct FixedVec11b {
    u32* mpBegin;    // +0
    u32* mpEnd;      // +4
    u32* mpCap;      // +8
    u32* f0c;        // +0xc
    u32* f10;        // +0x10
    u32* f14;        // +0x14
    u32  storage[250];   // +0x18
    void InitRange(u32 a, u32 b, void* c);   // 0x00a2b2e0
    FixedVec11b* ctor(u32* param_2);
};
// the constructors' view of the fixed vectors: the storage base points the vector at its inline buffer, and frees a
// heap block on unwind if filling the vector throws
template <int N> struct FixedVecStorage11 {
    u32* mpBegin;    // +0
    u32* mpEnd;      // +4
    u32* mpCap;      // +8
    u32* f0c;        // +0xc
    u32* f10;        // +0x10
    u32* f14;        // +0x14
    u32  storage[N]; // +0x18
    FixedVecStorage11() {
        u32* p = storage;
        f10 = p;
        mpEnd = p;
        mpBegin = p;
        mpCap = p + N;
    }
    ~FixedVecStorage11() { if (mpBegin != f10) f_00f47380(mpBegin); }
};
struct FixedVec11Obj : FixedVecStorage11<1001> {
    u32  fStart;     // +0xfbc
    u32  fEnd;       // +0xfc0
    u32  fCount;     // +0xfc4
    void resize(int n);   // 0x0089cb60
    FixedVec11Obj(int param_2);
};
// ---- items of slice s00a30460 end

// ---- items of slice s00a31f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vt_0140de80[];
extern char vt_01403934[];
extern char vtbl_PaintSystem[];       // 0x013eb394
extern char vtbl_01452d38[];
extern char vtbl_01452d24[];
namespace EA {
namespace Audio {
struct Command_s00a3_1f20 {
    uint Type();                                   // EA::XHTML::DOM::Node::Type, 0x00fc7e50
    void GetUint32(uint key, uint32_t* out);       // 0x00a0fab0
    void GetBool(uint key, float* out);            // 0x00a0fa70 (the flag lands in a float-typed slot)
};
}
}
struct MsgServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Send(uint id, void* msg, uint flags);   // slot 5 (+0x14)
};
MsgServer* __cdecl GetServer();                          // EA::Messaging::GetServer 0x00883860
void __cdecl RemoveHandler(uint a, uint b, uint c, uint d, uint e);   // EA::Messaging::RemoveHandler 0x00571db0
struct MsgBase {
    int refcount;           // +4
    MsgBase() : refcount(0) {}
    virtual ~MsgBase() {}
};
struct Msg : MsgBase {
    uint32_t f8;
    uint32_t pad0c;
    uint32_t f10;
    uint32_t pad14;
    uint32_t f18;
    uint32_t pad1c;
    uint32_t f20;
    char     pad24[0x80 - 0x24];
    uint32_t id;            // +0x80
    uint32_t pad84;
    uint32_t flags;         // +0x88
    virtual ~Msg() {}
};
struct MsgC {                 // message whose base is built by an out-of-line ctor (0x00a227a0)
    int refcount;
    uint32_t f8, pad0c, f10, pad14, f18, pad1c, f20;
    char pad24[0x80 - 0x24];
    uint32_t id, pad84, flags;
    virtual ~MsgC() {}
};
struct HMapRaw {                                          // eastl hash_map reached by raw offset
    void* Find(uint32_t* outIter, uint32_t* key);                    // FUN_00a23ef0 (returns out iterator)
    void  Erase(uint32_t* outIter, uint32_t node, uint32_t bucket);  // FUN_00a23db0
};
struct MsgCtor { void Init(uint id); };                   // FUN_00a227a0, this = &Msg::refcount
struct ListA { void Add(uint32_t* key); };                // FUN_00a30f10
struct ListB {
    void Push(uint32_t* key);                             // 0x00a21d30
};
struct System_s00a3_1f20 {
    bool DoCommandMainThread(EA::Audio::Command_s00a3_1f20* cmd);  // 0x00a31f20 (System::DoCommandMainThread)
};
struct fixed_pool_base {
    uint32_t mpHead;
    uint32_t mpOwner;
    uint32_t mpPoolBegin;
    uint32_t mpPoolEnd;
    uint32_t mnNodeSize;
    uint32_t mpBuckets;
    void init(void* mem, uint size, uint nodeSize, uint align, uint offset);   // 0x00921260
};
void* __cdecl FUN_00921340_s00a3_1f20(uint n);                                                   // 0x00921340
struct FHMapBase {
    uint32_t pad[4];
    void Ctor(void* a, uint b, uint32_t* c, uint32_t* d, uint e, uint32_t* f, fixed_pool_base* g);   // FUN_00a23b60
    void Rehash(uint n);                                                              // FUN_00a22110
};
struct PrimePolicy { uint GetBucketCount(uint n); };                                  // FUN_009213c0
struct FixedHashMap {
    uint32_t pad0[2];
    uint32_t mnBucketCount;     // +8
    uint32_t mnElementCount;    // +0xc
    float    mfMaxLoadFactor;   // +0x10
    float    mfGrowthFactor;    // +0x14
    uint32_t mnRehashCount;     // +0x18
    char     pad1c[0x34 - 0x1c];
    char     pad34[0x1cc - 0x34];
    FixedHashMap(uint a, uint b);
};
struct HashTmp {
    void Ctor(void* src);                              // FUN_00a310b0
    void Dtor();                                       // FUN_00a26da0
};
struct HashDst {
    void Clear(uint32_t a, uint32_t b);                // FUN_00a2ae90
    void Assign(uint32_t a, uint32_t b, uint32_t c);   // FUN_00a2b2e0
};
struct OuterMap {
    uint32_t pad[1];
    uint32_t* mpBuckets;        // +4
    uint32_t mnBucketCount;     // +8
    uint32_t* operator_index(uint32_t* key);
};
struct OMFind {
    void Find(uint32_t* out, uint32_t* key);               // 0x00a23b00
};
struct OMNodeCtor {
    void Ctor(void* a);                                    // 0x00a2e2f0
};
struct OMTmp {
    void* Make(char* a, char* b);                          // 0x00a1e320
};
struct OMInsert {
    void Insert(uint32_t* out, void* node, uint32_t flag); // 0x00a30f80
};
struct OMNodeDtor {
    void Dtor();                                           // 0x00a2aa70
};
struct OMFree {
    void DoFreeNodes(uint32_t nodes, uint32_t count);      // 0x00a1b6c0
};
struct HT {
    void Key_Free(uint32_t, uint32_t);          // 0x007611f0
    void TS_Free(uint32_t, uint32_t);           // 0x00a1b6c0 (TextStyle pair table DoFreeNodes)
    void F68fb70(uint32_t, uint32_t);
    void F24480(uint32_t, uint32_t);
    void F2add0(uint32_t, uint32_t);
    void F2f6e0(uint32_t, uint32_t);            // table of fixed_hash_map<uint,float,...>
    void F276e0(uint32_t, uint32_t);            // Subscription table
    void F26f30(uint32_t, uint32_t);
    void Fb6fdf0(uint32_t, uint32_t);
    void RbNuke(uint32_t node);                 // 0x009a9600
};
struct SimpleA {
    void a26da0(); void a222c0(); void a23920(); void ilb(); void a227d0();
    void f11e64d0();                            // 0x011e64d0
    void mutexDtor();                           // 0x00922130 (EA::Thread::Mutex::~Mutex)
    void f921e40();                             // 0x00921e40
    void f922e10();                             // 0x00922e10
};
template<int I> static inline void PoolTail(uint32_t* d)
{
    uint32_t* p = (uint32_t*)d[I];
    d[I + 2] = 0;
    if (d[I + 1] > 1 && p != (uint32_t*)d[I + 0xb]) {
        if (p < (uint32_t*)d[I + 8] || (uint32_t*)d[I + 9] <= p)
            operator_delete__(p);
        else {
            *p = d[I + 6];
            d[I + 6] = (uint32_t)p;
        }
    }
}
template<int I> static inline void NoPoolTail(uint32_t* d)
{
    d[I + 2] = 0;
    if (d[I + 1] > 1)
        operator_delete__((void*)d[I]);
}
template<int I> static inline void FixedBuf(uint32_t* d)       // fixed_vector buffer, I+4 = inline buffer
{
    uint32_t p = d[I];
    if (p != 0 && p != d[I + 4])
        operator_delete__((void*)p);
}
template<int I> static inline void CountedBuf(uint32_t* d)     // new[] with count cookie
{
    uint32_t p = d[I];
    if (p != 0 && *(uint32_t*)(p - 4) != 0)
        operator_delete__((void*)p);
}
struct SystemDtor {
    void Destroy();
};
#define HTBASE(I) ((HT*)&d[(I) - 1])
struct InnerMap {
    uint32_t pad;
    uint32_t* mpBuckets;
    uint32_t mnBucketCount;
};
struct OuterIdx {
    InnerMap* Index(uint32_t* key);                        // 0x00a323e0 (operator[], ret 4)
};
struct InnerFind {
    void Find(uint32_t* out, uint32_t* key);               // 0x00645ed0
};
struct InnerInsert {
    void Insert(uint32_t* pairOut, uint32_t* pairKV, uint32_t flag);   // 0x00a26ce0
};
struct SystemProps {
    void SetOutputProperty(uint32_t id, uint32_t prop, float value);
};
// ---- items of slice s00a31f20 end

// ---- items of slice s00a32f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_vec3[3];         // 0x0166da00, copied twice into the listener positions
extern const double g_cacheAge; // 0x01452f48
extern "C" int atexit(void (*fn)());
struct TagA { TagA() {} }; struct TagB { TagB() {} };   // empty hash / equal_to / allocator tag temporaries
struct Th743
{
    Th743(); // 0x743b50
    ~Th743(); uint32_t d;
};
struct Ctx921
{
    Ctx921(int a, int b); // 0x921f00
    ~Ctx921(); uint32_t d;
};
struct Mtx9222
{
    Mtx9222(int a, int b); // 0x9222a0
    ~Mtx9222(); uint32_t d;
};
struct Rdd
{
    Rdd(); // 0xa247f0
    ~Rdd(); uint32_t d;
};
struct Q0fd
{
    Q0fd(); // 0xa0fdf0
    ~Q0fd(); uint32_t d;
    bool FunF980();             // 0xa0f980  pending work?
    bool FunF9a0();             // 0xa0f9a0  one dispatcher step
    int  FunF990();             // 0xa0f990  shutdown state
    void FunFdd0();             // 0xa0fdd0
    void FunFdc0();             // 0xa0fdc0
    void FunF940();             // 0xa0f940
    void FunFee0(void* msg);    // 0xa0fee0  push a command
    void* GetArg();             // 0x9892e0
    void Fun102e0(uint32_t tag);                 // 0xa102e0
    void Fun10120(uint32_t tag, uint32_t value); // 0xa10120
};
struct TA210
{
    TA210(const TagA&, const TagB&); // 0xa2a210
    ~TA210(); uint32_t d;
};
struct TF210
{
    TF210(const TagA&, const TagB&); // 0xa2f210
    ~TF210(); uint32_t d;
};
struct TB310
{
    TB310(const TagA&, const TagB&); // 0xa2a310
    ~TB310(); uint32_t d;
};
struct TCe10
{
    TCe10(const TagA&, const TagB&); // 0xa30e10
    ~TCe10(); uint32_t d;
};
struct TD410
{
    TD410(const TagA&, const TagB&); // 0xa2a410
    ~TD410(); uint32_t d;
};
struct TF310
{
    TF310(const TagA&, const TagB&); // 0xa2f310
    ~TF310(); uint32_t d;
};
struct T33500
{
    T33500(const TagA&, const TagB&); // 0xa33500
    ~T33500(); uint32_t d;
};
struct T32220
{
    T32220(const TagA&, const TagB&); // 0xa32220
    ~T32220(); uint32_t d;
};
struct T570
{
    T570(const TagA&, const TagB&); // 0xa2a570
    ~T570();
    uint32_t  m0;            // +0x0
    uint32_t* mpBuckets;     // +0x4  bucket array
    uint32_t  mBucket;       // +0x8  bucket index used as the end() marker
    uint32_t  mOpCode;       // +0xc
    void* Find(void* out, const uint32_t* key); // 0xa23ef0
    void  Erase(const uint32_t* key);           // 0xa23d20
};
struct T1040
{
    T1040(int n); // 0xa31040
    ~T1040();
    void* mpFirst;           // +0x0  ring buffer begin
    void* mpLimit;           // +0x4  ring buffer end
};
struct T1e320
{
    T1e320(const TagA&, const TagB&); // 0xa1e320
    ~T1e320(); uint32_t d;
};
struct T670
{
    T670(const TagA&, const TagB&); // 0xa2a670
    ~T670(); uint32_t d;
};
struct T770
{
    T770(const TagA&, const TagB&); // 0xa2a770
    ~T770(); uint32_t d;
};
struct T26990
{
    T26990(); // 0xa26990
    ~T26990();
    T26990* pNext;           // +0x00  list next
    T26990* pPrev;           // +0x04  list prev
    void*   pObj;            // +0x08  bound audio object
};
struct TF410
{
    TF410(const TagA&, const TagB&); // 0xa2f410
    ~TF410();
    uint32_t  m0;            // +0x0
    void**    mpBuckets;     // +0x4  node bucket array
    uint32_t  mBucket;       // +0x8  bucket index used as the end() marker
    void Begin(void** out);  // 0x594410
};
struct Channel
{
    Channel(const char* name, int a, int b); // 0x11e64f0
    ~Channel(); uint32_t d;
};
struct ISystem_s00a3_2f20 {
    virtual void Init();
    virtual ~ISystem_s00a3_2f20();
};
struct IHandler_s00a3_2f20 {
    IHandler_s00a3_2f20() {}
    virtual void HandleMsg();
    virtual ~IHandler_s00a3_2f20();
};
struct IHandlerRC_s00a3_2f20 : IHandler_s00a3_2f20 {
    IHandlerRC_s00a3_2f20() {}
    virtual void HandleMsg();
    virtual ~IHandlerRC_s00a3_2f20();
};
struct AutoHandler_s00a3_2f20 {
    void* mpServer; void* mpHandler; uint32_t* mpIdArray; uint32_t mnIdArrayCount; uint32_t mnPriority;
    AutoHandler_s00a3_2f20() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
    ~AutoHandler_s00a3_2f20();
};
struct CoreAllocator  { CoreAllocator()  {} virtual ~CoreAllocator();  };
struct ResAllocator   { ResAllocator()   {} virtual ~ResAllocator();   };
struct Env {
    Env() : mA(1), mB(0), mC(1.0f), mD(2.0f), mE(0) {}
    virtual ~Env();
    int mA; int mB; float mC; float mD; int mE;
};
struct Vec3p { Vec3p() : a(0), b(0), c(0) {} ~Vec3p(); uint32_t a, b, c, pad[2]; };
#define PAD(name, from, to) uint32_t name[((to) - (from)) / 4]
class System_s00a3_2f20 : public ISystem_s00a3_2f20, public IHandlerRC_s00a3_2f20 {
public:
    System_s00a3_2f20();  // 0x00a33600 (System::System_s00a3_2f20)
    virtual void Init();
    virtual ~System_s00a3_2f20();  // 0x00a33600 (System::System_s00a3_2f20)
    virtual void HandleMsg();

    void Update(void* ctx, float dt);       // 0x00a32f20
    void MuteAll(bool muted, bool immediate); // 0x00a233b0
    void MaintainLRU();                     // 0x00a28810

    AutoHandler_s00a3_2f20       mAutoMsg;          // +0x08
    int               mRefCount;         // +0x1c
    Th743           mTickThread;       // +0x20
    uint32_t          padThr;
    Ctx921           mTickCtx;          // +0x28
    PAD(pad_a, 0x28 + 4, 0x90);
    uint32_t          mCommandBufferSize;// +0x90
    bool              mbInitialized;     // +0x94
    bool              mbPaused;
    bool              mbMutedForSilence;
    bool              mbMutedForFocus;
    bool              mbMutedByProperty;
    bool              mbMuted;
    uint8_t           b9a, b9b;
    CoreAllocator     mAllocator;        // +0x9c
    ResAllocator      mAllocator2;       // +0xa0
    uint32_t          mpRWAC;            // +0xa4
    float             mDacOutputMode;    // +0xa8
    float             mDacOutputSampleRate; // +0xac
    int               mNumOutputChannels;// +0xb0
    uint32_t          padb4;
    Mtx9222           mMutex;            // +0xb8
    PAD(pad_b, 0xb8 + 4, 0xec);
    uint32_t          mStreamPoolNumStreams;   // +0xec
    uint32_t          mStreamPoolBufferSize;   // +0xf0
    uint32_t          mStreamPoolMaxRequests;  // +0xf4
    Channel           mDebugChannel;     // +0xf8
    PAD(pad_c, 0xf8 + 4, 0x198);
    Rdd           mResourceDeviceDriver; // +0x198
    PAD(pad_d, 0x198 + 4, 0x1f8);
    uint32_t          mpConfiguration;   // +0x1f8 (AutoRefCount<IConfiguration>-like, null)
    uint8_t           mMax3d;            // +0x1fc
    uint8_t           pad1fd[3];
    int               mPerformanceLevel; // +0x200
    uint32_t          cq0, cq1, cq2;     // +0x204..0x20c
    float             cqName;            // +0x210
    Q0fd q0; uint32_t qp0[19];   // +0x214
    Q0fd q1; uint32_t qp1[19];   // +0x264
    Q0fd q2; uint32_t qp2[19];   // +0x2b4
    Q0fd q3; uint32_t qp3[19];   // +0x304
    Q0fd q4; uint32_t qp4[19];   // +0x354
    Q0fd q5; uint32_t qp5[19];   // +0x3a4
    uint8_t           s3f4, s3f5;        // +0x3f4
    uint8_t           pad3f6[2];
    uint32_t          s3f8;
    uint8_t           s3fc, s3fd;
    uint8_t           pad3fe[2];
    float             s400;              // +0x400
    TA210          mMixables;         // +0x404
    PAD(pad_g, 0x404 + 4, 0x13f4);
    TF210          mPrimitives;       // +0x13f4
    PAD(pad_h, 0x13f4 + 4, 0x23e4);
    TA210          mMapA;             // +0x23e4
    PAD(pad_i, 0x23e4 + 4, 0x33d4);
    TB310          mPrimitiveProxys;  // +0x33d4
    PAD(pad_j, 0x33d4 + 4, 0x80424);
    TCe10          mBig;              // +0x80424
    PAD(pad_k, 0x80424 + 4, 0x118a00);
    Env               env0; uint32_t e0pad[2];   // +0x118a00
    Env               env1; uint32_t e1pad[2];   // +0x118a20
    Env               env2; uint32_t e2pad[2];   // +0x118a40
    uint32_t          lst[2]; uint32_t lstA; uint8_t lstB; uint8_t lstBp[3]; uint32_t lstC; uint32_t lstD; // +0x118a60
    TD410          mEmitterConstructorMap;  // +0x118a78
    PAD(pad_l, 0x118a78 + 4, 0x118b94);
    Env               env3;              // +0x118b94
    PAD(pad_m, 0x118b94 + 0x18, 0x118bb0);
    TA210          mMapB;             // +0x118bb0
    PAD(pad_n, 0x118bb0 + 4, 0x119ba4);
    Vec3p             mVecA;             // +0x119ba4
    TF310          mHT2a;             // +0x119bb8
    PAD(pad_o, 0x119bb8 + 4, 0x11a3d8);
    TA210          mMapC;             // +0x11a3d8
    PAD(pad_p, 0x11a3d8 + 4, 0x11b3c8);
    T33500          mOutputs;          // +0x11b3c8
    PAD(pad_q, 0x11b3c8 + 4, 0x1277b4);
    T32220          mSubscriptions;    // +0x1277b4
    PAD(pad_r, 0x1277b4 + 4, 0x128ae0);
    T570          mPolyA;            // +0x128ae0
    PAD(pad_s, 0x128ae0 + 0x10, 0x12c9ac);
    T1040          mPoolA;            // +0x12c9ac
    PAD(pad_t, 0x12c9ac + 8, 0x12d974);
    T570          mPolyB;            // +0x12d974
    PAD(pad_u, 0x12d974 + 0x10, 0x131840);
    T1040          mPoolB;            // +0x131840
    PAD(pad_v, 0x131840 + 8, 0x1327fc);
    uint32_t*         mIdRead;          // +0x1327fc
    uint32_t*         mIdWrite;         // +0x132800
    uint32_t          mIdDropped;       // +0x132804
    T570          mPolyC;            // +0x132808
    PAD(pad_w, 0x132808 + 0x10, 0x1366d4);
    T1040          mPoolC;            // +0x1366d4
    PAD(pad_x, 0x1366d4 + 8, 0x13769c);
    uint32_t*         fv0;               // +0x13769c
    uint32_t*         fv1;               // +0x1376a0
    uint32_t*         fv2;               // +0x1376a4
    uint32_t          fvpad;             // +0x1376a8
    uint32_t*         fv3;               // +0x1376ac
    PAD(pad_y, 0x1376ac + 4, 0x1376b4);
    uint32_t          fvBuf[(0x13777c - 0x1376b4) / 4];   // +0x1376b4
    T1e320          mJ;                // +0x13777c
    PAD(pad_z, 0x13777c + 4, 0x13795c);
    T670          mK;                // +0x13795c
    PAD(pad_aa, 0x13795c + 4, 0x137fe8);
    T770          mExternalIds;      // +0x137fe8
    PAD(pad_ab, 0x137fe8 + 4, 0x157438);
    uint32_t          listNext, listPrev;// +0x157438
    TF310          mHT2b;             // +0x157440
    PAD(pad_ac, 0x157440 + 4, 0x157c60);
    T26990          mObj157c60;        // +0x157c60
    PAD(pad_ad, 0x157c60 + 0xc, 0x158f48);
    T26990*         pObj;              // +0x158f48
    uint32_t          z158f4c;
    TF410          mHT3;              // +0x158f50
    PAD(pad_ae, 0x158f50 + 0xc, 0x15b6b0);
    uint32_t          z6b0, z6b4, z6b8, z6bc;     // +0x15b6b0
    PAD(pad_af, 0x15b6bc + 4, 0x15b6d8);
    float             posA[3];           // +0x15b6d8
    float             posB[3];           // +0x15b6e4
    float             mat0[9];           // +0x15b6f0
    float             mat1[9];           // +0x15b714
    uint32_t          z738, z73c, z740;  // +0x15b738
    PAD(pad_ag, 0x15b740 + 4, 0x15b750);
    uint32_t          z750, z754, z758, z75c, z760; // +0x15b750
    uint32_t          n764;              // +0x15b764
    double            ageSecs;           // +0x15b768
    uint32_t          m770;              // +0x15b770
    uint8_t           b774; uint8_t b774p[3];
    uint32_t          z778;              // +0x15b778
    uint32_t*         rb0; uint32_t* rb1; uint32_t* rb2; uint32_t* rb3; // +0x15b77c
    uint32_t*         rb4;               // +0x15b78c
    uint32_t          rbPad[(0x15bb7c - 0x15b790) / 4];
    uint32_t*         sb0; uint32_t* sb1; uint32_t* sb2; uint32_t* sb3; // +0x15bb7c
    uint32_t*         sb4;               // +0x15bb8c
    PAD(pad_ai, 0x15bb8c + 4, 0x15bbf0);
    uint8_t           b15bbf0;           // +0x15bbf0
    PAD(pad_aj, 0x15bbf0 + 4, 0x15bbf8);
    Env               env4;              // +0x15bbf8
};
#define AVS(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
namespace EA {
struct Stopwatch_s00a3_2f20
{
    Stopwatch_s00a3_2f20(int units, bool highRes);      // 0x0093a560
    void Start();                            // inlined in the original
    uint32_t mnUnits;                        // +0x00
    uint32_t mnStartLo;                      // +0x04
    uint32_t mnStartHi;                      // +0x08
    uint32_t mnTotalLo;                      // +0x0c
    uint32_t mnTotalHi;                      // +0x10
};
}
namespace EA {
struct LimitStopwatch_s00a3_2f20 : Stopwatch_s00a3_2f20
{
    LimitStopwatch_s00a3_2f20(int units, bool highRes); // 0x0093a560
    void SetTimeLimit(uint32_t units, bool b);  // 0x0093a480
    bool HasTimeLeft();                         // inlined in the original
    uint32_t mnEndLo;                        // +0x14
    uint32_t mnEndHi;                        // +0x18
};
}
namespace rt {
struct MsgObj            // object with a virtual command interface
{
    virtual void Slot0();
    virtual void Slot4();
    virtual void Slot18(int, int);
    virtual void Slot24(uint32_t);
};
}
namespace rt {
struct cmdStub           // 0x0166d9f4: mixer/notification sink with two vtable slots
{
    virtual void SlotC0();
    virtual void SlotC4();
};
}
namespace rt {
extern cmdStub* gpCmdStub;          // 0x0166d9f4
}
namespace rt {
struct CmdRecord
{
    uint32_t mType;         // +0x00
    uint32_t mArg1;         // +0x04
    uint32_t mArg2;         // +0x08
    uint32_t mArg3;         // +0x0c
    uint32_t mArg4;         // +0x10
};
}
namespace rt {
struct CmdList
{
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpGuard;      // +0x08
    uint32_t* mpCap;        // +0x0c
    void Assign(const uint32_t* begin, const uint32_t* end); // 0x00a32320
    void EraseRange(uint32_t* begin, uint32_t* end);         // 0x00a2ae90
};
}
namespace rt {
extern CmdList   gDeferredCmds;     // 0x0166da90
}
namespace rt {
extern uint32_t  gDeferredGuard;    // 0x0166de90
}
namespace rt {
extern uint32_t  gDeferredStorage[];// 0x0166daa8
}
void DeferredListInit();            // 0x013c1810 (atexit target)
namespace eastl {
struct fixed_pool_base_s00a3_2f20
{
    void* mpHead;   // +0x00  first free node
    void init(void* pMemory, uint32_t nSize, uint32_t nNodeSize, uint32_t nAlignment, uint32_t nOffset); // 0x00921260
};
}
namespace eastl {
struct node_pool_desc
{
    void*    mpMap;       // +0x00  map being constructed
    uint8_t* mpNodes;     // +0x04  first node slot
    uint8_t* mpNodesEnd;  // +0x08  one past the last node slot
    uint32_t mnNodeSize;  // +0x0c  bytes per node
};
}
namespace eastl {
struct fixed_hash_map_u32_nested
{
    void*    mpBegin;                   // +0x000
    void*    mpEnd;                     // +0x004
    uint32_t mnBucketCount;             // +0x008  buckets currently allocated
    void*    mpBucketArray;             // +0x00c
    float    mLoadFactor;               // +0x010
    float    mGrowthFactor;             // +0x014
    uint32_t mnElementCount;            // +0x018
    uint8_t  mPad1c[0x1cc - 0x1c];      // +0x01c  rest of the hashtable state
    uint8_t  mNodeStorage[0xbea0];      // +0x1cc  100 slots * 0x1e8 bytes

    fixed_hash_map_u32_nested(const struct hash_tag&, const struct equal_to_tag&); // 0x00a33500
    void BaseInit(void* pAllocator, const node_pool_desc& desc);  // 0x00a23a40
    void Rehash(uint32_t nBucketCount);                           // 0x00a22060
};
}
namespace eastl {
struct hash_tag {};
}
namespace eastl {
struct equal_to_tag {};
}
namespace eastl {
void* RequestPoolBookkeeping(uint32_t tag);
}
namespace eastl {
uint32_t BucketCount(void* pBucketArray);
}
// ---- items of slice s00a32f20 end

// ---- items of slice s00a31170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtRefBase[];             // 0x013effa8
extern void* g_vtFactoryA[];            // 0x01452a44
extern void* g_vtFactoryB[];            // 0x01452a78
extern void* g_vtFactoryC[];            // 0x01452ac0
extern const char g_audioName[];        // 0x0140a5a0 "Audio"
extern int g_FsAllocatorManager;                            // 0x016f4b10
extern char g_1552da0[];                // 0x01552da0
extern const char g_systemName[];       // 0x01452d1c "system"
extern uint32_t g_teardownFlag;             // 0x0166d9fc
extern float kPromptReleaseTime;            // 0x013ef548
#define V1(n) virtual void n();
#define V4(n) V1(n##a) V1(n##b) V1(n##c) V1(n##d)
#define V16(n) V4(n##a) V4(n##b) V4(n##c) V4(n##d)
void __cdecl operator_delete_array(void* p);                       // 0x00f47380 operator delete[]
struct ResKey { uint32_t instance, type, group; };
struct ListNode_s00a3_1170 {
    ListNode_s00a3_1170* mpNext;
    ListNode_s00a3_1170* mpPrev;
    void* mpData;                       // +0x08
};
struct DbList {                         // eastl::list<AutoRefCount<Database>> with an allocator
    ListNode_s00a3_1170 mAnchor;                   // next/prev only used
    void* mpAllocator;                  // +0x08
    uint32_t mFlags;                    // +0x0c
};
struct CoreAlloc {
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void Free(void* p, unsigned size);                              // +0x0c
};
CoreAlloc* __cdecl GetDefaultAllocator_s00a3_1170();                                   // 0x00925cb0
struct ByteVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    ByteVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ByteVec()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete_array(mpBegin);
    }
    void resize(unsigned n);            // 0x004c0410
};
struct FactoryObj {
    void** vt;
    long ref;
    __forceinline FactoryObj* Init(void** derived)
    {
        vt = g_vtRefBase;
        _InterlockedExchange(&ref, 0);
        vt = derived;
        return this;
    }
};
class IFactory {
public:
    virtual void v0();
    virtual int AddRef();               // +0x04
    virtual int Release();              // +0x08
};
void* __cdecl ZoneAlloc(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00926020
struct IStream { private:
public:
virtual void v0();
virtual void v4();
virtual void v8();
virtual void vc();
virtual void v10();
virtual void v14();
    virtual void Close();                                   // +0x18
    virtual uint32_t GetSize();                             // +0x1c
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual uint32_t Read(void* buf, uint32_t size);        // +0x30
};
class IResource {
public:
virtual void v0();
virtual void v4();
    virtual int Release();                                  // +0x08
virtual void vc();
virtual void v10();
virtual void v14();
    virtual IStream* OpenStream();                          // +0x18
    virtual uint32_t GetTypeID();                           // +0x1c
};
class IDatabase {
public:
    V4(d0) V4(d1) V4(d2) V1(d3)
    virtual bool GetResource(const ResKey* key, IResource** out, int a, int b, int c, int d);   // +0x34
};
class IResourceType {                    // result of the manager's +0x58 lookup
public:
virtual void v0();
virtual void v4();
virtual void v8();
    virtual uint32_t GetTypeID();                           // +0x0c
};
class IResourceManager {
public:
    V16(m1)
    V1(m40)
    virtual void RegisterFactory(int kind, IFactory* factory, int flags);   // +0x44
virtual void m48();
virtual void m4c();
virtual void m50();
virtual void m54();
    virtual IResourceType* GetResourceType(const ResKey* key);              // +0x58
    virtual void GetDatabases(DbList* out, const ResKey* key);              // +0x5c
};
IResourceManager* __cdecl GetResourceManager();             // 0x008de1a0 (EA::Audio::Eapd::Debug::ObjectError)
class IPluginParam {
public:
    void SetParam(int index, const void* value);            // 0x0112ccc0 (merged thunk: jmp [vtbl+4])
};
struct VoiceContainer_s00a3_1170 {
    IPluginParam* FindPlugin(uint32_t id);                  // 0x00a34230
};
struct RWSystem {
    uint32_t pad[0xa8 / 4];
    void* mpCallback;                                       // +0xa8
    void SetCallback(void* fn);                             // 0x0112c870
    void AddPlugin(IPluginParam* p);                        // 0x009879d0
    void shutdown();                                        // 0x0112c880
};
struct StreamPool {
    void QueueRelease();                                    // 0x0112e410
};
RWSystem* __cdecl CreateInstance(void* allocator, uint32_t size);                      // 0x0112c9e0
StreamPool* __cdecl ReleaseHandler(uint32_t id, uint32_t a, uint32_t b, uint32_t c,
                                   RWSystem* rw, void* allocator, int d);              // 0x0112e290
struct FsParams {
    void* mpChannel;
    void* mpAllocator2;
    uint32_t mA;
    uint32_t mB;
    FsParams();                                             // 0x011e64c0
};
void __cdecl FsInit(FsParams* p);                           // 0x011e5cd0
struct FsManager {
    void SetDriver(void* driver, int a);                    // 0x011e59b0
};
FsManager* __cdecl GetFsManager();                          // 0x011e58f0
struct AudioLock {                      // global mutex wrapper (thiscall, ecx = lock)
    void Lock();                        // 0x0112c600
    void Unlock();                      // 0x0112c620
};
extern AudioLock* g_pAudioLock;         // 0x016e61a8
struct AutoAudioLock {
    __forceinline AutoAudioLock()
    {
        if (g_pAudioLock)
            g_pAudioLock->Lock();
    }
    __forceinline ~AutoAudioLock()
    {
        if (g_pAudioLock)
            g_pAudioLock->Unlock();
    }
};
struct HashIter_s00a3_1170 {
    void* mpNode;
    void** mpBucket;
    void Init(void* flag);              // 0x00a26fa0 (ret 4)
};
struct PolyPair {
    uint32_t first;
    uint32_t second;
};
struct HashInsertResult {
    HashIter_s00a3_1170 it;
    bool inserted;
};
struct PolyphonyMap {                   // eastl::hash_map<uint32_t, int>
    uint32_t mAllocator;
    void** mpBucketArray;               // +0x04
    uint32_t mnBucketCount;             // +0x08
    uint32_t mnNodeCount;               // +0x0c
    HashIter_s00a3_1170* find(HashIter_s00a3_1170* out, const uint32_t& key);                      // 0x00645ed0
    void insert(HashInsertResult* out, const PolyPair* value, bool b);       // 0x00a26ce0
    void FreeNodes(void* first, void* last);                                 // 0x00a1b6c0
};
struct EmitterMap {                     // fixed_hash_map<uint32_t, IEmitter*(*)()>
    uint32_t mAllocator;                // +0x00
    void* mpBegin;                      // +0x04
    void* mpEnd;                        // +0x08
    uint32_t mCount;                    // +0x0c
    void*& At(const uint32_t& key);     // 0x00a2a510 operator[]
    void FreeNodes(void* first, void* last);                                 // 0x00a1b6c0
};
struct IdRing {                         // ring buffer of ids
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    uint32_t mCount;                    // +0x08
    void push_back(const uint32_t& id); // 0x00a21d30
    void Reset(void* base) { mpEnd = mpBegin = base; mCount = 0; }
};
struct IdPool {
    uint32_t mData[0xf0 / 4];
    void Init(unsigned capacity);       // 0x00a102a0
    void Reset();                       // 0x00a0fdd0
};
struct IdPoolShort {                    // second id pool; its allocator block ends at +0x404
    uint32_t mData[0x60 / 4];
    void Init(unsigned capacity);       // 0x00a102a0
};
struct EaTable {                        // eastl node container: allocator word, {begin, end, count}
    uint32_t mAllocator;                // +0x00
    void* mpBegin;                      // +0x04
    void* mpEnd;                        // +0x08
    uint32_t mCount;                    // +0x0c
    void DoFreeNodes(void* first, void* last);          // 0x00a1b6c0 (ret 8)
    void FreeBuckets(void** buckets, uint32_t n);       // 0x00a24480 (ret 8)
    void FreeSubNodes(void** nodes, uint32_t n);        // 0x00a276e0 (ret 8)
    void FreeResNodes(void** nodes, uint32_t n);        // 0x00a26f30 (ret 8)
    void FreeProfBuckets(void* first, uint32_t n);      // 0x0068fb70 (ret 8)
    void FreeFloatNodes(void* first, void* last);       // 0x00a2f6e0 (ret 8)
    void FreeMiscNodes(void* first, void* last);        // 0x00a2add0 (ret 8)
    void FreeFdfNodes(void* first, void* last);         // 0x00b6fdf0 (ret 8)
    void FindMisc(HashIter_s00a3_1170* out, const uint32_t& key);  // 0x00a23c10 (ret 8)
    void FindInt(HashIter_s00a3_1170* out, const uint32_t& key);   // 0x00645ed0 (ret 8)
    void* Sentinel() { return ((void**)mpBegin)[(int)(intptr_t)mpEnd]; }
};
struct EaVec {                          // eastl vector / id ring storage
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    void* mpCapacity;                   // +0x08
};
struct BitVec {                         // eastl::vector<bool> storage (4-byte word stride)
    uint32_t* mpBegin;                  // +0x00
    uint32_t* mpEnd;                    // +0x04
    uint32_t* mpCapacity;               // +0x08
    void EraseAll();                    // erase(begin(), end()) -> memcpy + restamped end
};
struct EaTree {                         // eastl::rbtree header
    uint32_t mAllocator;                // +0x00
    void* mpHeaderNode;                 // +0x04
    void* mpRoot;                       // +0x08
    void* mpNodeChain;                  // +0x0c
    uint8_t mbFlag;                     // +0x10
    uint8_t mPad11[3];
    uint32_t mCount;                    // +0x14
    uint32_t mPad18;                    // +0x18
    void NukeSubtree(void* node);       // 0x009a9600 (ret 4)
    void Clear()
    {
        NukeSubtree(mpNodeChain);
        mpRoot = &mpHeaderNode;
        mpNodeChain = 0;
        mbFlag = 0;
        mCount = 0;
        mpHeaderNode = &mpHeaderNode;
    }
};
struct EaList {                         // eastl::list anchor (no destructor, pool allocated)
    ListNode_s00a3_1170* mpNext;                   // +0x00
    ListNode_s00a3_1170* mpPrev;                   // +0x04
    void FreeNodes();                   // 0x00a222c0
    void Clear()
    {
        ListNode_s00a3_1170* node = mpNext;
        while (node != (ListNode_s00a3_1170*)this) {
            ListNode_s00a3_1170* next = node->mpNext;
            node->mpPrev = 0;
            node->mpNext = 0;
            node = next;
        }
        mpNext = (ListNode_s00a3_1170*)this;
        mpPrev = (ListNode_s00a3_1170*)this;
    }
};
void* __cdecl ConstructEmitterSndPlayer();                  // 0x00a20700
template<int N> struct Gap { uint32_t pad[N]; };
class cSystem {
public:
    V16(a)                              // slots 0x00..0x3c
    V4(b1) V4(b2) V4(b3) V1(b13)        // 0x40..0x70
    virtual void Hook74(void* pending);                         // +0x74
    V1(b15) V1(b16)                     // 0x78, 0x7c
    virtual void Hook80(int enable);                            // +0x80
    V4(c1) V4(c2) V4(c3) V1(c4) V1(c5) V1(c6)                   // 0x84..0xbc
    V4(d)                               // 0xc0..0xcc
    V1(ea) V1(eb) V1(ec)                // 0xd0..0xd8
    virtual void HookDC();                                      // +0xdc
    V4(f)                               // 0xe0..0xec
    V1(g)                               // 0xf0
    virtual uint32_t HashName(const char* name);                // +0xf4
    V1(h)                               // 0xf8
    virtual void SetTuning(uint32_t key, float value);          // +0xfc
    V16(i)                              // 0x100..0x13c
    V4(j) V4(k) V4(l)                   // 0x140..0x16c
    V1(m) V1(n) V1(o)                   // 0x170..0x178
    virtual VoiceContainer_s00a3_1170* GetVoiceHolder(uint32_t id);        // +0x17c (object with a container at +0x10)
    V4(p) V4(q) V4(r)                   // 0x180..0x1ac
    V1(s)                               // 0x1b0
    virtual void Hook1b4();                                     // +0x1b4
    virtual void Hook1b8();                                     // +0x1b8
    virtual void Hook1bc(const char* p);                        // +0x1bc
    V1(u)                               // 0x1c0
    virtual void Hook1c4();                                     // +0x1c4
    virtual void Hook1c8();                                     // +0x1c8
    virtual void Hook1cc();                                     // +0x1cc
    virtual void Hook1d0();                                     // +0x1d0
    V1(v1) V1(v2) V4(w) V1(x)           // 0x1d4..0x1ec
    virtual void Hook1f0();                                     // +0x1f0

    Gap<1> pad04;                       // +0x04
    void* mpMessageHandler;             // +0x08
    uint32_t mHandlerArg0;              // +0x0c
    uint32_t mHandlerArg1;              // +0x10
    uint32_t mHandlerArg2;              // +0x14
    uint32_t mHandlerArg3;              // +0x18
    Gap<(0x90 - 0x1c) / 4> pad1c;
    uint32_t mCommandBufferSize;        // +0x90
    uint8_t pad94[2];
    bool mbMutedForSilence;             // +0x96
    bool mbMutedForFocus;               // +0x97
    bool mbMutedByProperty;             // +0x98
    bool mbMuted;                       // +0x99
    bool mbMuteApplied;                 // +0x9a
    uint8_t pad9b;
    uint32_t mAllocator;                // +0x9c
    uint32_t mAllocator2;               // +0xa0
    RWSystem* mpRWAC;                   // +0xa4
    float mDacOutputMode;               // +0xa8
    float mDacOutputSampleRate;         // +0xac
    Gap<(0xe8 - 0xb0) / 4> padb0;
    StreamPool* mpStreamPoolDefault;    // +0xe8
    uint32_t mStreamPoolNumStreams;     // +0xec
    uint32_t mStreamPoolBufferSize;     // +0xf0
    uint32_t mStreamPoolMaxRequests;    // +0xf4
    Gap<(0x198 - 0xf8) / 4> mDebugChannel;      // +0xf8
    Gap<(0x200 - 0x198) / 4> mResourceDeviceDriver;   // +0x198
    int mPerformanceLevel;              // +0x200
    Gap<(0x210 - 0x204) / 4> pad204;
    float mFadeVolume;                  // +0x210
    Gap<(0x2b4 - 0x214) / 4> pad214;
    IdPool mPoolA;                      // +0x2b4
    IdPoolShort mPoolB;                 // +0x3a4
    EaTable mHash404;                   // +0x404
    Gap<(0x13f4 - 0x414) / 4> pad414;
    EaTable mHash13f4;                  // +0x13f4
    Gap<(0x23e4 - 0x1404) / 4> pad1404;
    EaTable mHash23e4;                  // +0x23e4
    Gap<(0x33d4 - 0x23f4) / 4> pad23f4;
    EaTable mHash33d4;                  // +0x33d4
    Gap<(0x80424 - 0x33e4) / 4> pad33e4;
    EaTable mHash80424;                 // +0x80424
    Gap<(0x1189fc - 0x80434) / 4> pad80434;
    EaTable mFdf1189fc;                 // +0x1189fc
    Gap<(0x118a1c - 0x118a0c) / 4> pad118a0c;
    EaTable mIdTable;                   // +0x118a1c (mIdArray's base/index are its begin/end)
    Gap<(0x118a3c - 0x118a2c) / 4> pad118a2c;
    EaTable mFdf118a3c;                 // +0x118a3c
    Gap<(0x118a5c - 0x118a4c) / 4> pad118a4c;
    EaTree mTree118a5c;                 // +0x118a5c
    EmitterMap mEmitterMap;             // +0x118a78
    Gap<(0x118b90 - 0x118a88) / 4> pad118a88;
    EaTable mRes118b90;                 // +0x118b90
    Gap<(0x118bb0 - 0x118ba0) / 4> pad118ba0;
    EaTable mHash118bb0;                // +0x118bb0
    Gap<(0x119ba0 - 0x118bc0) / 4> pad118bc0;
    void* mpLogReporterList;            // +0x119ba0
    EaVec mReporterVec;                 // +0x119ba4
    Gap<(0x119bb8 - 0x119bb0) / 4> pad119bb0;
    EaTable mHash119bb8;                // +0x119bb8
    Gap<(0x11a3d8 - 0x119bc8) / 4> pad119bc8;
    EaTable mHash11a3d8;                // +0x11a3d8
    Gap<(0x11b3c8 - 0x11a3e8) / 4> pad11a3e8;
    EaTable mFloat11b3c8;               // +0x11b3c8
    Gap<(0x1277b4 - 0x11b3d8) / 4> pad11b3d8;
    EaTable mMisc1277b4;                // +0x1277b4
    Gap<(0x128ae0 - 0x1277c4) / 4> pad1277c4;
    EaTable mProf128ae0;                // +0x128ae0
    Gap<(0x12c9ac - 0x128af0) / 4> pad128af0;
    void* mpProfPool;                   // +0x12c9ac
    Gap<(0x12d968 - 0x12c9b0) / 4> pad12c9b0;
    EaVec mRing12d968;                  // +0x12d968
    EaTable mProf12d974;                // +0x12d974
    Gap<(0x131840 - 0x12d984) / 4> pad12d984;
    IdRing mIdRing;                     // +0x131840
    Gap<(0x1327fc - 0x13184c) / 4> pad13184c;
    EaVec mRing1327fc;                  // +0x1327fc
    EaTable mProf132808;                // +0x132808
    Gap<(0x1366d4 - 0x132818) / 4> pad132818;
    void* mpProfPool2;                  // +0x1366d4
    Gap<(0x137690 - 0x1366d8) / 4> pad1366d8;
    EaVec mRing137690;                  // +0x137690
    BitVec mBits13769c;                 // +0x13769c
    Gap<(0x13777c - 0x1376a8) / 4> pad1376a8;
    EaTable mHash13777c;                // +0x13777c
    Gap<(0x137fe8 - 0x13778c) / 4> pad13778c;
    PolyphonyMap mPolyphonyMap;         // +0x137fe8
    Gap<(0x157438 - 0x137ff8) / 4> pad137ff8;
    EaList mList157438;                 // +0x157438
    EaTable mProf157440;                // +0x157440
    Gap<(0x157c60 - 0x157450) / 4> pad157450;
    EaList mPromptList;                 // +0x157c60
    Gap<(0x158f48 - 0x157c68) / 4> pad157c68;
    ListNode_s00a3_1170* mpPromptIter;             // +0x158f48
    Gap<(0x15b750 - 0x158f4c) / 4> pad158f4c;
    uint32_t mIterValue;                // +0x15b750
    void* mIterPos;                     // +0x15b754
    uint32_t mIter8, mIterC, mIter10;   // +0x15b758..0x15b760
    Gap<(0x15b778 - 0x15b764) / 4> pad15b764;
    IFactory* mpFactoryB;               // +0x15b778
    Gap<(0x15bb7c - 0x15b77c) / 4> pad15b77c;
    BitVec mBits15bb7c;                 // +0x15bb7c

    void MuteAll(bool mute, bool immediate);        // 0x00a233b0
    void PreloadConfigurations();                   // 0x00a30940
    void FUN_a2ef60();                              // 0x00a2ef60
    void FUN_a2da30();                              // 0x00a2da30
    bool InitAT();
    bool ShutdownAT();                              // 0x00a31800
    void InsertMapped(HashIter_s00a3_1170* out, const PolyPair* value, uint8_t flag);  // 0x00a2f510
    bool FUN_00a31dc0(uint32_t key, void* query);   // 0x00a31dc0
};
void __cdecl FUN_00571db0(void* handler, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // Messaging::RemoveHandler
void __cdecl FUN_011e5d30();                                        // filesys_destroy
void __cdecl FUN_00e25bd0(void* first, void* last);                 // eastl::vector::erase(first, last)
void __cdecl FUN_00926410(void* p);                                 // list-node release
void __cdecl FUN_011e0744(void* dst, const void* src, uint32_t n);  // memcpy
struct KeyValue {
    uint32_t mKey;                      // +0x00
    uint32_t mValue;                    // +0x04
    bool Remove(void* query);           // 0x00a27e60 (ret 4)
};
struct MapNode_s00a3_1170 {
    void* mpNext;                       // +0x00
    KeyValue mPair;                     // +0x04
};
struct IPrompt {
    virtual void v0();
    virtual void v4();
    virtual void Release(float a, float b); // +0x08
};
void BitVec::EraseAll()
{
    FUN_011e0744(mpBegin, mpEnd, 0);
    mpEnd -= mpEnd - mpBegin;
}
// ---- items of slice s00a31170 end

// ---- items of slice s00a0f350 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_audioAllocatorFile[];
struct MemPool {
    void* LockedAlloc(int a, int b, int zero, const char* name, int c, int d);                  // 0x9289f0
    void* LockedAligned(int a, int b, int c, int d, int zero, const char* name, int e, int f);  // 0x928a30
    void  Free(void* p);                                                                        // 0x9276c0
};
extern MemPool* g_memPool;       // 0x16c8b44
struct AudioBlock { void* mPtr; int a, b, c; };
// ---- items of slice s00a0f350 end

// ---- items of slice s00a21130 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* f_00a158d0(void);
extern void* f_00a151c0(void);
extern void* f_00a149a0(void);
extern void* f_00a161b0(void);
extern void* f_00a15d30(void);
extern void* f_00a14800(void);
extern void  f_00f47380(void* p) throw();
extern void* f_00f473a0(unsigned size, void* name, void* a3, void* a4, void* file, unsigned line);
struct Callee_Th {
void* m_0112ce00();
void m_0112dca0();
void m_0112cd60(void* v);
void* m_0112dc80();
void m_0112dbd0();
void* m_00a34230(unsigned tag);
void m_00a34890();
void m_0112c600();
void m_0112c620();
    void m_0112ccc0(int a, void* b);
};
#define TH(p) ((Callee_Th*)(p))
#define VPTR(ret, obj, slot, ...) \
    ((ret (__thiscall*)(void*, __VA_ARGS__))((void**)*(void**)obj)[(slot) / 4])
struct AudioSystem_00a21170 { void RegisterBuiltInModules(); };
struct VoiceContainer_s00a2_1130 {
    bool Connect(int a1, int a2);  // 0x00a21410 (VoiceContainer::Connect)
    bool Connect4(int a1, int a2, int a3, int a4);  // 0x00a214b0 (VoiceContainer::Connect4)
};
struct MsgTarget_00a21630 { bool Handle(int a1, int a2); };
// a vector of voice pointers: the base frees the storage, the vector releases each voice (vtable slot 2) first
struct IVoice_00a21c00 { virtual void Slot0(); virtual void Slot1(); virtual void Release(); };
struct VoiceVecBase_00a21c00 {
    IVoice_00a21c00** mpBegin;
    IVoice_00a21c00** mpEnd;
    IVoice_00a21c00** mpCapacity;
    ~VoiceVecBase_00a21c00() { if (mpBegin != 0) f_00f47380(mpBegin); }
};
struct VoiceVec_00a21c00 : VoiceVecBase_00a21c00 { ~VoiceVec_00a21c00(); };
struct RbTree_00a21dc0 { void* Find(void** out, void* key); };
struct HashA_00a21eb0 { void Rehash(unsigned a); void* Alloc(unsigned n); };
struct HashB_00a22060 { void Rehash(unsigned a); void* Alloc(unsigned n); };
struct HashC_00a22110 { void Rehash(unsigned a); void* Alloc(unsigned n); };
struct AudioSys_00a21a80 { void* FindVoice(unsigned tag); };
struct AudioSys_00a21b20 { bool Command(int a1, int a2, int a3, int a4, int a5); };
struct AudioSys_00a21b90 { bool Command4(int a1, int a2, int a3, int a4, int a5); };
__declspec(noinline) void __fastcall disconnect_00a21590(char* self);
// ---- items of slice s00a21130 end

// ---- items of slice s00a26e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_EmptyStrRep[];            // 0x01667bac
#define EASTL_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* eaNew(size_t size, const char* name, int flags, unsigned dbgFlags, const char* file, int line);   // 0x00f473a0
void* operator new(size_t size, const char* name, int a, int b, int c, int d);                           // 0x00f473a0 (new-expression form)
void  operator delete(void*);                                                                           // 0x00f47380
template <class T> static inline T& fld(void* p, int off) { return *(T*)((char*)p + off); }
struct RefObj {
    virtual void AddRef();
    virtual void Release();
};
struct CountedRes {
    virtual void Destroy(int flag);
    volatile int mnRefCount;
};
static inline void ReleaseCounted(CountedRes* r)
{
    if (r) {
        int n = (r->mnRefCount += -1);
        if (n == 0) {
            r->mnRefCount = 1;
            _ReadWriteBarrier();
            r->Destroy(1);
        }
    }
}
struct Key4 { uint32_t a, b, c, d; };
struct KNode { Key4 key; KNode* next; };
struct RehashRes { bool bNeed; uint32_t nNew; };
struct RehashPolicy { void GetRehashRequired(RehashRes* out, uint32_t nBuckets, uint32_t nElems, uint32_t nExtra); };  // 0x00921440
struct InsertRes { KNode* node; KNode** bucket; bool inserted; };
struct KTable {
    void* pad0;
    KNode** mpBuckets;      // +4
    uint32_t mnBuckets;     // +8
    uint32_t mnElements;    // +0xc
    RehashPolicy mPolicy;   // +0x10
    void DoRehash(uint32_t n);                                   // 0x00998870
    InsertRes* Insert(InsertRes* out, const Key4* k, int tag);   // 0x00a26e10
};
struct ResNode { uint32_t key; CountedRes* value; ResNode* next; };
struct ResTable {
    void DoFreeNodes(ResNode** buckets, uint32_t n);
};
struct Payload { uint32_t a, b, c; RefObj* obj; };
struct NodePool {
    char pad[0x18];
    void** mpFree;          // +0x18
    char pad1c[0xc];
    size_t mnNodeSize;      // +0x28
    void* Alloc(const Payload* src);
};
struct EdRes {
    virtual void AddRef();                                  // 0x00432a50
    virtual void Release();                                 // 0x00432a70
    virtual ~EdRes() {}
    virtual void Slot3();                                   // 0x00432ad0
    virtual int GetReferenceCount();                        // 0x004c0190
};
struct PropBase_s00a2_6e10 : EdRes {                                   // vtable 0x013ebcdc
    long mnRefCount;        // +4
    uint32_t a, b, c;       // +8..+0x10
    PropBase_s00a2_6e10()
    {
        _InterlockedExchange(&mnRefCount, 0);
        a = 0; b = 0; c = 0;
    }
};
struct FixedVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    int   pad;
    char* mpLocal;
    ~FixedVec() { if (mpBegin && mpBegin != mpLocal) operator delete(mpBegin); }
};
template <int N> struct FixedVecBuf : FixedVec {           // fixed_vector: header, pad, inline buffer
    int pad;
    char buf[N];
    FixedVecBuf()
    {
        mpLocal = buf;
        mpBegin = mpEnd = buf;
        mpCap = mpBegin + N;
    }
};
struct PropList_s00a2_6e10 : PropBase_s00a2_6e10 {
    FixedVecBuf<0x168> v1;  // +0x14 (buffer +0x2c)
    FixedVecBuf<0x2d0> v2;  // +0x194 (buffer +0x1ac)
    PropList_s00a2_6e10();  // 0x00a270b0 (PropList::PropList_s00a2_6e10)
    virtual ~PropList_s00a2_6e10();  // 0x00a270b0 (PropList::PropList_s00a2_6e10)
};
struct FactoryVoiceTemplate {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool InitResource(int key, PropList_s00a2_6e10* res, int a, int b);     // slot 9 (+0x24)
    bool CreateResource(int key, PropList_s00a2_6e10** out, int a, int b);
};
struct OwnerBase { virtual ~OwnerBase() {} };               // vtable 0x013ef094
struct OwnedVec {
    char* mpBegin; char pad[0xc]; char* mpLocal;
    ~OwnedVec() { if (mpBegin && mpBegin != mpLocal) operator delete(mpBegin); }
};
struct AbilityList : OwnerBase {
    char pad4[4];
    OwnedVec v;             // +8
    AbilityList();
};
struct HIter_s00a2_6e10 { void* node; void** bucket; };
struct StyleTable_s00a2_6e10 {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    void find(HIter_s00a2_6e10* out, const uint32_t* key) const;       // 0x00645ed0
    HIter_s00a2_6e10 erase(HIter_s00a2_6e10 it);                                  // 0x00d2c9f0
};
struct StyleNode { uint32_t key; RefObj* value; };
struct StyleMgr {
    virtual void v0();
    char pad[0x119bb4];
    StyleTable_s00a2_6e10 mStyles;     // +0x119bb8
    bool Remove(uint32_t key);
    void RemoveAll();
};
typedef void (__thiscall* VFn1)(void*, void*);
typedef bool (__thiscall* VFnB)(void*);
#define VSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
struct TexNode { uint32_t key[3]; void* value; };
struct TexTable {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    void find(HIter_s00a2_6e10* out, const void* key) const;           // 0x00833840
};
struct TexMgr { char pad[0x80424]; TexTable mTex; void* Find(const void* key); };
struct MapNode_s00a2_6e10 { uint32_t key; CountedRes* value; };
struct RefSlot {                                            // AutoRefCount<CountedRes>
    CountedRes* p;
    RefSlot() : p(0) {}
    RefSlot(const RefSlot& o) : p(o.p) { if (p) p->mnRefCount++; }
    ~RefSlot()
    {
        if (p) {
            int n = p->mnRefCount - 1;
            p->mnRefCount = n;
            if (n == 0) {
                p->mnRefCount = 1;
                p->Destroy(1);
            }
        }
    }
};
struct MapValue {                                           // pair<const uint, AutoRefCount<X>>
    uint32_t key;
    RefSlot value;
    MapValue(uint32_t k, const RefSlot& v) : key(k), value(v) {}
};
struct MapIter {
    MapNode_s00a2_6e10* node; void** bucket;
    MapIter() {}
    explicit MapIter(void** b) : node((MapNode_s00a2_6e10*)*b), bucket(b) {}
};
struct MapInsertRet { MapIter first; bool second; };      // pair<iterator, bool> (12 bytes)
struct MapTrueType {};                                      // eastl::true_type tag passed by value
struct RefMap {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    MapIter find(const uint32_t& key) const;                // 0x00645ed0
    MapInsertRet Insert(const MapValue& v, MapTrueType tag);   // 0x00a23830 (DoInsertValue)
    CountedRes** FindOrInsert(const uint32_t* key);
};
struct ENode { uint32_t pad[3]; RefObj* value; ENode* next; };
struct ETable {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    uint32_t mnElements;    // +0xc
    HIter_s00a2_6e10* erase(HIter_s00a2_6e10* out, ENode* node, ENode** bucket);
};
struct SubNode_s00a2_6e10 { void* link; uint32_t key; void* pad; char* sub; SubNode_s00a2_6e10* next; };
struct SubTable {
    char pad[0x1c];
    SubNode_s00a2_6e10* mpFreeList;    // +0x1c
    char pad20[4];
    char* mpPoolBegin;      // +0x24
    char* mpPoolEnd;        // +0x28
    char pad2c[4];
    SubNode_s00a2_6e10* mpInline;      // +0x30
    void DoFreeNodes(SubNode_s00a2_6e10** buckets, uint32_t n);
};
struct RcPtr {                                              // AutoRefCount<T>
    RefObj* p;
    RcPtr() : p(0) {}
    RcPtr(const RcPtr& o) : p(o.p) { if (p) p->AddRef(); }
    ~RcPtr() { if (p) p->Release(); }
    RcPtr& operator=(const RcPtr& o)
    {
        if (p != o.p) {
            RefObj* old = p;
            p = o.p;
            if (p) p->AddRef();
            if (old) old->Release();
        }
        return *this;
    }
};
RcPtr* CopyBackwardRc(RcPtr* first, RcPtr* last, RcPtr* destEnd);     // 0x00ac97a0 (cdecl)
void* memcpy_11e0744(void* dst, const void* src, size_t n);           // 0x011e0744 (memcpy)
struct RcVector {
    RcPtr* mpBegin;
    RcPtr* mpEnd;
    RcPtr* mpCap;
    void DoInsertValue(RcPtr* pos, const RcPtr* value);
};
struct Rec12 { uint32_t a, b, c; };
Rec12* RelocateRec12(Rec12* first, Rec12* last, Rec12* dest);         // 0x00a11310 (cdecl)
struct Rec12Vector {
    Rec12* mpBegin;
    Rec12* mpEnd;
    Rec12* mpCap;
    char pad[4];
    Rec12* mpFixed;         // +0x10
    void DoInsertValue(Rec12* pos, const Rec12* value);
};
struct Rec24 { uint32_t d[6]; };
Rec24* CopyBackwardRec24(Rec24* first, Rec24* last, Rec24* destEnd);   // 0x00cc8b50 (cdecl)
Rec24* RelocateRec24(Rec24* first, Rec24* last, Rec24* dest);          // 0x00720200 (cdecl)
struct Rec24Vector {
    Rec24* mpBegin;
    Rec24* mpEnd;
    Rec24* mpCap;
    char pad[4];
    Rec24* mpFixed;         // +0x10
    void DoInsertValue(Rec24* pos, const Rec24* value);
};
struct Zone { uint32_t d[11]; };
Zone* RelocateZone(Zone* first, Zone* last, Zone* dest);               // 0x00b3d890 (cdecl)
struct ZoneVector {
    Zone* mpBegin;
    Zone* mpEnd;
    Zone* mpCap;
    void DoInsertValue(Zone* pos, const Zone* value);
};
struct CountNode { char pad[0x14]; int count; };   // rbtree node: value.second at +0x14
struct CountPair { uint32_t key; int count; CountPair(uint32_t k, int c) : key(k), count(c) {} };
struct CountTrueType {};  // eastl::true_type: empty tag passed by value
struct CountTree {
    void find(HIter_s00a2_6e10* out, const uint32_t* key);                            // 0x00e5c780
    HIter_s00a2_6e10 findv(const uint32_t& key) { HIter_s00a2_6e10 r; find(&r, &key); return r; }
    HIter_s00a2_6e10 Insert(const CountPair& v, CountTrueType tag);                   // 0x00a246c0
    HIter_s00a2_6e10 insert(const CountPair& v) { return Insert(v, CountTrueType()); }
};
struct CountMap {
    char pad0[4];
    CountTree mTree;        // +4
    char pad_anchor[4];     // +8 is the tree anchor node address
    bool AddRef(uint32_t key);
};
struct EStr {
    char* mpBegin; char* mpEnd; char* mpCap;
    struct Alloc {} mAllocator;         // eastl::allocator (empty)
    const char* c_str() const { return mpBegin; }
    EStr() : mpBegin(g_EmptyStrRep), mpEnd(g_EmptyStrRep), mpCap(g_EmptyStrRep + 1) {}
    ~EStr() { if (mpCap - mpBegin > 1 && mpBegin) operator delete(mpBegin); }
    void sprintf(const char* fmt, ...);                                    // 0x00472fe0 (cdecl, this pushed)
};
struct LockObj { void Lock(); void Unlock(); };                            // 0x0112c600 / 0x0112c620
extern LockObj* g_pAudioLock_s00a2_6e10;           // 0x016e61a8
struct AudioLockGuard {
    AudioLockGuard() { if (g_pAudioLock_s00a2_6e10) g_pAudioLock_s00a2_6e10->Lock(); }
    ~AudioLockGuard() { if (g_pAudioLock_s00a2_6e10) g_pAudioLock_s00a2_6e10->Unlock(); }
};
struct VoiceContainer_s00a2_6e10 {
    void* FindPlugin(uint32_t id);                                         // 0x00a34230
    bool ConnectToSubmix(void* submixVoice, int flag);                     // 0x00a34b50
};
struct Plugin { void SetName(int a, const char* const& name); };                 // 0x0112ccc0
struct Submix_s00a2_6e10 {
    char pad0[0x10];
    VoiceContainer_s00a2_6e10 mVoiceContainer;     // +0x10
    char pad_988[0x977];
    const char* mpName;                 // +0x988
    bool ConnectToSubmix(Submix_s00a2_6e10* other);  // 0x00a27ed0 (Submix::ConnectToSubmix)
};
struct EvTable {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    void find(HIter_s00a2_6e10* out, const uint32_t* key);                            // 0x00a23ef0
    void Insert(HIter_s00a2_6e10* out, const uint32_t* v, int tag);                   // 0x00a26be0
};
struct EvOwner {
    virtual void v0();
    char pad[0x13795c - 4];
    EvTable mEvents;        // +0x13795c
    bool Register(uint32_t a1, uint32_t a2, void* a3, double a4);
};
typedef bool (__thiscall* VCreate)(void*, uint32_t, uint32_t, void*, int, RefObj**);
typedef void (__thiscall* VNotify)(void*, uint32_t, int);
typedef bool (__thiscall* VFire)(void*, double);
// ---- items of slice s00a26e10 end

// ---- items of slice s00a25c40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* DAT_0166d9f4;
extern const char kEastlAlloc[];   // "EASTL"
struct XF_s00a2_5c40;   // generic stub for external __thiscall callees
struct XF_s00a2_5c40 {
    bool FUN_00a0f980();                 // 0xa0f980  predicate
    bool FUN_00a0f9a0();                 // 0xa0f9a0  predicate
    int  FUN_00a0f990();                 // 0xa0f990  count
    void FUN_00a0fdc0();                 // 0xa0fdc0
    void FUN_00a0fdd0();                 // 0xa0fdd0
    void FUN_00a0fee0(void* p);          // 0xa0fee0
    void FUN_009892e0();                 // (unused shape)
};
struct Mutex_s00a2_5c40 {  // 0x9221b0 / 0x922270
    void Lock(uint name);
    void Unlock();
};
struct HTable {
    void*    mp0;              // 0x00
    void**   mpBucketArray;    // 0x04
    uint32_t mnBucketCount;    // 0x08
    uint32_t mnElementCount;   // 0x0c
    void*    mpPool;           // 0x10
    void*    mpFreeList;       // 0x14  (fixed_pool head etc.)

    void  find(void* itOut, const uint* key);                 // 0x645ed0
    uint* find2(void* itOut, const uint* key);                // 0xa23ef0
    void  Rehash(uint n);                                     // 0xa22370
    void  EraseNode(void** itOut, void* node, void* prev);    // 0xa23db0
    void  DoFreeNodes(void* a, void* b);                      // 0xa1b6c0
    void* Insert(void* ret, const uint* key, uint hash);      // 0xa26be0
    void  AssignLess2(void* fn);                              // 0xa24210

    // The "end node": bucketArray[bucketCount].
    void* End() const { return mpBucketArray[mnBucketCount]; }
    bool  NotFound(const void* itNode) const { return itNode == End(); }
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
struct RBTree_s00a2_5c40 {  // 0x9a9600 / 0xa24210
    void* mpRoot;
    void* mpNode;
    void DoNukeSubtree(void* n);  // 0x006ae600 (RBTree::DoNukeSubtree)
    void AssignLess2(void* fn);
};
struct SubTree { void __thiscall DoNukeSubtree(void* n); };   // 0x9a9600-style
// the destructor's view of the 0x00a26860 object: a base whose destructor restores vtable 0x13eb394, and an rbtree at
// +4 that nukes its nodes from the root at +0x10 when destroyed
struct SubTreeHolder {
    uint  mAnchor[3];         // +0x00
    void* mpRoot;             // +0x0c
    uint  mRest[2];           // +0x10
    void __thiscall DoNukeSubtree(void* n);
    ~SubTreeHolder() { DoNukeSubtree(mpRoot); }
};
struct TreeOwnerBase_00a26860 { virtual void Slot0(); ~TreeOwnerBase_00a26860() {} };
struct __declspec(novtable) TreeOwner_00a26860 : TreeOwnerBase_00a26860 {
    SubTreeHolder mTree;      // +0x04
    ~TreeOwner_00a26860();
};
struct fixed_pool_base_s00a2_5c40 {
    void* mpHead;
    void* mpNext;
    void init(void* pMemory, uint memorySize, uint nodeSize, uint alignment, uint alignmentOffset); // 0x921260
};
struct fixed_pool_with_overflow : fixed_pool_base_s00a2_5c40 {
    void* mpPoolBegin;
    void* mpCapacity;
    uint  mnNodeSize;
    fixed_pool_with_overflow(void* pMemory, uint size, uint nodeSize, uint align) {
        mpHead = 0;
        init(pMemory, size, nodeSize, align, 0);
        mpPoolBegin = pMemory;
        mpCapacity = (uchar*)pMemory + size;
        mnNodeSize = nodeSize;
    }
};
void* __cdecl operator_new(size_t sz, const char* name, int a, int b, const char* file, int line);
void* __cdecl ConvertToString8Impl(void* out, const wchar_t* s, uint len);   // 0x93c440
bool  __cdecl FUN_00ef6410();                                               // 0xef6410
void  __cdecl FUN_00a16fd0(uint* node, float f);                            // 0xa16fd0
struct MapValue_s00a2_5c40 { void __thiscall FUN_00a16fd0(float f); };                 // 0xa16fd0 (thiscall form)
void  __cdecl FUN_00a21d30(void* ring, void* key);                          // 0xa21d30
void  __cdecl Func_68fb70(void* a, void* b);                                // 0x68fb70
class AudioSystem_s00a2_5c40 {
 public:
    void*    mpVtbl;                 // 0x000
    void*    mpVtblRC;               // 0x004
    uint32_t mAutoMsg[0x23];         // 0x008
    uint8_t  mbInitialized;          // 0x094
    uint8_t  pad_095[0x6];           // 0x095..0x09b
    uint8_t  mbX_9b;                 // 0x09b
    uint8_t  pad_09c[0x1c];          // 0x09c..0x0b8
    uint8_t  mMutex[0x30];           // 0x0b8 (EA::Thread::Mutex)
    uint8_t  pad_0e8[0x120];         // 0x0e8..0x208
    void*    mpX_208;                // 0x208
    uint8_t  pad_20c[0x8];           // 0x20c..0x214
    XF_s00a2_5c40       mQueue_214;             // 0x214
    uint8_t  pad_215[0x4f];          // 0x215..0x264
    XF_s00a2_5c40       mQueue_264;             // 0x264
    uint8_t  pad_265[0x9f];          // 0x265..0x304
    XF_s00a2_5c40       mQueue_304;             // 0x304
    uint8_t  pad_305[0x4f];          // 0x305..0x354
    XF_s00a2_5c40       mQueue_354;             // 0x354
    uint8_t  pad_355[0x4f];          // 0x355..0x3a4
    XF_s00a2_5c40       mQueue_3a4;             // 0x3a4
    uint8_t  pad_3a5[0x4f];          // 0x3a5..0x3f4
    uint8_t  mbX_3f4;                // 0x3f4
    uint8_t  mbX_3f5;                // 0x3f5
    uint8_t  pad_3f6[0x6];           // 0x3f6..0x3fc
    uint8_t  mbX_3fc;                // 0x3fc
    uint8_t  pad_3fd[0x7];           // 0x3fd..0x404
    HTable   mMap_404;               // 0x404
    uint8_t  pad_41c[0xfd8];         // 0x41c..0x13f4
    HTable   mMap_13f4;              // 0x13f4
    uint8_t  pad_140c[0xfd8];        // 0x140c..0x23e4
    HTable   mMap_23e4;              // 0x23e4
    uint8_t  pad_23fc[0xfd8];        // 0x23fc..0x33d4
    HTable   mMap_33d4;              // 0x33d4
    uint8_t  pad_33ec[0x11568c];     // 0x33ec..0x118a78
    HTable   mMap_118a78;            // 0x118a78
    uint8_t  pad_118a90[0x120];      // 0x118a90..0x118bb0
    HTable   mMap_118bb0;            // 0x118bb0
    uint8_t  pad_118bc8[0xff0];      // 0x118bc8..0x119bb8
    HTable   mMap_119bb8;            // 0x119bb8
    uint8_t  pad_119bd0[0x808];      // 0x119bd0..0x11a3d8
    HTable   mMap_11a3d8;            // 0x11a3d8
    uint8_t  pad_11a3f0[0xe6f0];     // 0x11a3f0..0x128ae0
    HTable   mMap_128ae0;            // 0x128ae0
    uint8_t  pad_128af8[0x9d10];     // 0x128af8..0x132808
    HTable   mMap_132808;            // 0x132808
    uint8_t  pad_132820[0x3eb4];     // 0x132820..0x1366d4
    uint8_t  mRing_1366d4[0xb8];     // 0x1366d4
    uint8_t  pad_13678c[0x11d0];     // 0x13678c..0x13795c
    HTable   mProfHash_13795c;       // 0x13795c
    uint8_t  pad_137974[0x1fac4];    // 0x137974..0x157438
    RBTree_s00a2_5c40   mTree_157438;           // 0x157438 (mpRoot,mpNode)
    HTable   mMap_157440;            // 0x157440
    uint8_t  pad_157448[0x7f8];      // 0x157448..0x157c50
    RBTree_s00a2_5c40   mTree_157c50;           // 0x157c50 (mpRoot,mpNode)
    uint8_t  pad_157c58[0x8];        // 0x157c58..0x157c60
    uint8_t  mList_157c60[0x12b0];   // 0x157c60
    uint8_t  pad_158f10[0x38];       // 0x158f10..0x158f48
    void*    mpX_158f48;             // 0x158f48
    uint8_t  pad_158f4c[0x8];        // 0x158f4c..0x158f54
    HTable   mMap_158f54;            // 0x158f54
    uint8_t  pad_158f6c[0x2744];     // 0x158f6c..0x15b6b0
    uint32_t mX_15b6b0;              // 0x15b6b0
    uint32_t mX_15b6b4;              // 0x15b6b4
    uint32_t mX_15b6b8;              // 0x15b6b8
    uint32_t mX_15b6bc;              // 0x15b6bc

    // --- member functions (definitions below) ---
    void  Update(float dt);                                     // 0xa25c40
    void  RemoveFromList(void* item);                           // 0xa25ed0
    bool  Lookup_25ff0(uint key, uint* out);                    // 0xa25ff0
    uint  RemovePrimitiveFromUpdate(void* p);                   // 0xa26040
    uint  Lookup_260c0(uint key);                              // 0xa260c0
    bool  Map_26100(uint key, uint arg);                        // 0xa26100
    void  Map_261c0(uint arg);                                  // 0xa261c0
    void  Map_26230(uint a, uint b);                            // 0xa26230
    bool  Map_262a0(uint key, uint arg);                        // 0xa262a0
    bool  Map_26300(uint key, uint arg);                        // 0xa26300
    uint  Lookup_26360(uint key);                               // 0xa26360
    bool  Map_263a0(uint key, void** out);                      // 0xa263a0
    void  UpdateSoundStates();                                  // 0xa26450
    void  Map_26530();                                          // 0xa26530
    uint  Lookup_26570(uint key);                              // 0xa26570
    uint  Lookup_265b0(uint key);                               // 0xa265b0
    void  Map_265f0(float, uint);                               // 0xa265f0
    bool  Map_26680(uint key, void** out);                      // 0xa26680
    bool  Map_266e0(uint key, float f);                         // 0xa266e0
    bool  Map_26730(uint key, void** out);                      // 0xa26730
    bool  Map_26790(uint arg);                                  // 0xa26790
    void  Map_267d0(uint id);                                   // 0xa267d0
    void  Shutdown_268b0();                                     // 0xa268b0
    void* InitPool_26990();                                     // 0xa26990
    void  Insert_26be0(void* ret, const uint* key, uint hash);  // 0xa26be0
    void  VecDtor_26da0();                                      // 0xa26da0
};
static void* vc_s00a2_5c40(void* obj, int off) {
    return ((void**)*(void**)obj)[off / 4];
}
// ---- items of slice s00a25c40 end

// ---- items of slice s00a28120 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_voiceVT;                                                 // 0x01452bac
struct Key4_s00a2_8120 { unsigned a, b, c, d; };
struct Vec3_s00a2_8120 { float x, y, z; };
struct SndA {
    virtual void AddRef();                                    // slot 0
    virtual void Release();                                   // slot 1
virtual void s02();
virtual void s03();
virtual void s04();
    virtual void SetGain(double v);                           // slot 5  (+0x14)
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
    virtual unsigned GetKey();                                // slot 21 (+0x54)
    virtual bool IsPlaying();                                 // slot 22 (+0x58)
    virtual bool GetLayers(void** out);                       // slot 23 (+0x5c)
    virtual void s24();
    virtual void Prop3(int type, unsigned value, unsigned extra); // slot 25 (+0x64)
};
struct SndB {                                                 // secondary base at +4
virtual void b0();
virtual void b1();
virtual void b2();
    virtual void PropF(int type, float value, int extra);     // slot 3 (+0xc)
};
struct Snd_s00a2_8120 : SndA, SndB {
    char pad_[0x10 - 8];
    Snd_s00a2_8120* listNext;                                            // +0x10
    Snd_s00a2_8120* listPrev;                                            // +0x14
};
struct Command {
    bool   GetUint32(unsigned hash, unsigned* out);           // 0x00a0fab0
    char*  GetString8(unsigned hash);                         // 0x00a0fb60
    bool   GetBool(unsigned hash, bool* out);                 // 0x00a0fa70
    bool   GetVoidPtr(unsigned hash, void** out);             // 0x00a0fb90
    void*  EnumParameter(void** value, unsigned* id2, unsigned* type, void** extra); // 0x00a0f880
};
struct IConfig {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
    virtual void c08();
    virtual bool GetBool(unsigned hash, bool* out);           // slot 9  (+0x24)
    virtual void c10();
    virtual bool GetUint32(unsigned hash, unsigned* out);     // slot 11 (+0x2c)
    virtual bool GetFloat(unsigned hash, float* out);         // slot 12 (+0x30)
    virtual void c13();
    virtual bool GetId(unsigned hash, unsigned* out);         // slot 14 (+0x38)
};
struct HIter_s00a2_8120 {
    void* node; void** bucket;
    HIter_s00a2_8120() {}
    HIter_s00a2_8120(const HIter_s00a2_8120& x) : node(x.node), bucket(x.bucket) {}
};
struct U32Table {
    char     pad0[4];
    void**   mpBuckets;      // +4
    unsigned mnBuckets;      // +8
    void  find(HIter_s00a2_8120* out, const void* key);                  // 0x00645ed0
    HIter_s00a2_8120* erase(HIter_s00a2_8120* out, HIter_s00a2_8120 it);    // 0x00d2c9f0 (returns the iterator through out)
};
void  T4Find(U32Table* t, HIter_s00a2_8120* out, const void* key);                // 0x00a23ef0
void  T4Op(U32Table* t, HIter_s00a2_8120* it, const void* key, int tag);          // 0x00a26be0
void  T4Insert2(U32Table* t, HIter_s00a2_8120* it, const void* pair, int tag);    // 0x00a26b00
void  T4Insert3(U32Table* t, HIter_s00a2_8120* it, const void* pair, int tag);    // 0x00a26ce0
void  PairInsert(U32Table* t, HIter_s00a2_8120* it, const void* pair, int tag);   // 0x00a136f0
HIter_s00a2_8120* PairErase(U32Table* t, void* node, void** bucket);              // 0x00a27660
struct InsertRes_s00a2_8120 { void* node; void** bucket; };
InsertRes_s00a2_8120* KInsert(InsertRes_s00a2_8120* out, const void* pair, int tag);         // 0x00a26e10
struct ENode_s00a2_8120 { unsigned pad[3]; void* owner; ENode_s00a2_8120* next; void* prev; };
struct KeyNode { unsigned pad[1]; void* value; };
void* EAAllocate(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
struct Voice {
    virtual void AddRef();                                   // slot 0
    virtual void Release2();                                 // slot 1 (+0x4) r=1
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
    virtual bool IsPlaying();                                // slot 22 (+0x58)
    virtual bool GetLayers(void** out);                      // slot 23 (+0x5c)
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
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
virtual void v52();
virtual void v53();
virtual void v54();
virtual void v55();
virtual void v56();
virtual void v57();
virtual void v58();
virtual void v59();
virtual void v60();
virtual void v61();
virtual void v62();
    virtual void DestroyV(int flag);                         // (operator delete, +0x8c)
    int     rc;        // +0x04
    void*   f08;
    void*   f0c;
    void*   f10;
    void*   f14;
    void*   f18;       // +0x18
    void*   f1c;       // +0x1c (points at +0x20)
    char    pad[0x98 - 0x20];
    void*   f98;       // +0x98
    void*   f9c;       // +0x9c
    bool    Init();                                          // 0x00a147b0
    void    AddLayer(void* layer);                           // 0x00a14780
    void*   Reset();                                         // 0x00a14730
};
Voice** RefMapFindOrInsert(U32Table* t, const void* key);                // 0x00a27530
void*   PoolAlloc(void* pool, int cb);                                   // 0x00a10ef0
struct Sys_s00a2_8120 {
virtual void vs0();
void vs1();
void vs2();
void vs3();
virtual void vs4();
void vs5();
void vs6();
void vs7();
virtual void vs8();
void vs9();
void vs10();
void vs11();
virtual void vs12();
void vs13();
void vs14();
void vs15();
virtual void vs16();
void vs17();
void vs18();
void vs19();
virtual void vs20();
void vs21();
void vs22();
void vs23();
virtual void vs24();
void vs25();
void vs26();
void vs27();
virtual void vs28();
void vs29();
void vs30();
void vs31();
virtual void vs32();
void vs33();
void vs34();
void vs35();
    virtual bool     StartSound(unsigned key, unsigned a2, void* data, Vec3_s00a2_8120* pos, Snd_s00a2_8120** out); // slot 36 (+0x94)
    virtual bool     StopSound2(unsigned id, int a2);                           // slot 37 (+0x98)
virtual void vs38();
void vs39();
void vs40();
void vs41();
virtual void vs42();
void vs43();
void vs44();
void vs45();
virtual void vs46();
void vs47();
void vs48();
void vs49();
virtual void vs50();
void vs51();
void vs52();
void vs53();
virtual void vs54();
void vs55();
void vs56();
void vs57();
virtual void vs58();
void vs59();
    virtual unsigned SymbolToId(char const* name);                              // slot 60 (+0xf4)
virtual void vs61();
void vs62();
void vs63();
void vs64();
virtual void vs65();
void vs66();
void vs67();
void vs68();
virtual void vs69();
void vs70();
void vs71();
void vs72();
virtual void vs73();
void vs74();
void vs75();
void vs76();
virtual void vs77();
void vs78();
void vs79();
void vs80();
virtual void vs81();
void vs82();
void vs83();
void vs84();
    virtual void vs85();
    virtual int      AddPlaylistRef(unsigned id, int a2);                       // slot 86 (+0x15c)
virtual void vs87();
void vs88();
void vs89();
    virtual bool     RegisterKey(void* key);                                    // slot 90 (+0x16c)
    virtual bool     UnregisterKey(void* key);                                  // slot 91 (+0x170)
virtual void vs92();
void vs93();
void vs94();
void vs95();
    virtual void vs96();
    virtual bool     FindPlaylistTable(Key4_s00a2_8120* key, void* out);                   // slot 97 (+0x188)
    virtual bool     GetPlaylistOwner(Key4_s00a2_8120* key, void* out);                    // slot 98 (+0x18c)
    virtual bool     GetPlaylistOwner2(Key4_s00a2_8120* key, void* out);                   // slot 99 (+0x190)
virtual void vs100();
void vs101();
void vs102();
    virtual void vs103();
    virtual int      ReleasePlaylistRef(unsigned id);                           // slot 104 (+0x1a4)
virtual void vs105();
void vs106();
void vs107();
void vs108();
virtual void vs109();
void vs110();
void vs111();
void vs112();
virtual void vs113();
void vs114();
void vs115();
    virtual Snd_s00a2_8120*     FindSound(unsigned id);                                    // slot 116 (+0x1d4)
virtual void vs117();
void vs118();
void vs119();
void vs120();

    char pad_[0x118a1c - 0x4];
    U32Table mActiveTable;        // +0x118a1c (buckets +0x118a20, count +0x118a24)
    char pad2[0x118a3c - (0x118a1c + sizeof(U32Table))];
    U32Table mLRUTable;           // +0x118a3c (buckets +0x118a40, count +0x118a44)
    char pad3[0x118b90 - (0x118a3c + sizeof(U32Table))];
    U32Table mVoiceMap;           // +0x118b90 (buckets +0x118b94, count +0x118b98)
    char pad3b[0x118bb0 - (0x118b90 + sizeof(U32Table))];
    U32Table mCounterA;           // +0x118bb0 (buckets +0x118bb4, count +0x118bb8)
    char pad4[0x13795c - (0x118bb0 + sizeof(U32Table))];
    U32Table mSoundMap;           // +0x13795c
    char pad5[0x137fe8 - (0x13795c + sizeof(U32Table))];
    U32Table mCounterMap;         // +0x137fe8 (buckets +0x137fec, count +0x137ff0)
    char pad6[0x157440 - (0x137fe8 + sizeof(U32Table))];
    U32Table mKeyMap;             // +0x157440
    char pad7[0x158f50 - (0x157440 + sizeof(U32Table))];
    U32Table mObjMap;             // +0x158f50
    char pad8[0x15b750 - (0x158f50 + sizeof(U32Table))];
    void* mLRUIterNode;           // +0x15b750
    void* mLRUIterBucket;         // +0x15b754
    int   mLRUBytes;              // +0x15b758
    int   mLRUEnabled;            // +0x15b75c
    char pad9[0x15b770 - 0x15b760];
    int   mTexEnabled;            // +0x15b770
    char pad10[0x15bbf4 - 0x15b774];
    U32Table mTexTable;           // +0x15bbf4

    bool StartSoundFromCommand(Command& cmd, unsigned id);          // 00a28120
    bool TryStartSound(char* out, unsigned id, IConfig* cfg,
                       Vec3_s00a2_8120* pos, unsigned a5);                     // 00a28450
    void MaintainLRU();                                             // 00a28810
    void AddTextureRef(Key4_s00a2_8120* key);                                  // 00a28a20
    bool GetOrRegisterVoice(unsigned key, Voice** out, int nLayers, void* layers); // 00a28aa0
    void RegisterObj(Snd_s00a2_8120* p);                                       // 00a28c60
    bool UnregisterObj(unsigned key);                               // 00a28d10
    int  GetCounterPlaylist(unsigned key);                          // 00a28d70
    int  AddCounter(unsigned key, int delta);                       // 00a28e90
    bool TrackPlayingKey(Snd_s00a2_8120* obj);                                 // 00a28f10
    bool UntrackPlayingKey(Snd_s00a2_8120* obj);                               // 00a29000
};
struct ListenerObj {
virtual void ls00();
virtual void ls01();
virtual void ls02();
virtual void ls03();
virtual void ls04();
virtual void ls05();
virtual void ls06();
virtual void ls07();
virtual void ls08();
virtual void ls09();
virtual void ls10();
virtual void ls11();
virtual void ls12();
virtual void ls13();
virtual void ls14();
virtual void ls15();
virtual void ls16();
virtual void ls17();
virtual void ls18();
virtual void ls19();
virtual void ls20();
virtual void ls21();
virtual void ls22();
virtual void ls23();
virtual void ls24();
virtual void ls25();
virtual void ls26();
virtual void ls27();
virtual void ls28();
virtual void ls29();
    virtual void* GetListenerTransform(unsigned surf);         // slot 30 (+0x7c)
};
extern ListenerObj* g_audioSys;                                          // 0x0166d9f4
struct ResponseCurve {
    char raw[0x30];
    ResponseCurve();                                                     // 0x00a1aa50
    bool InitFromConfiguration(unsigned hash, IConfig* cfg);             // 0x00a1a9d0
    float GetOutputValue(float x);                                       // 0x00a1a110
};
// ---- items of slice s00a28120 end

// ---- items of slice s00a290b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_keyA;    // 0x01552da0
extern unsigned g_keyB;    // 0x01552da4
extern unsigned g_keyC;    // 0x01552da8
extern const wchar_t g_wMono[];    // 0x01452c80
extern const wchar_t g_wStereo[];  // 0x01452c70
extern const wchar_t g_wQuad[];    // 0x01452c68
extern const wchar_t g_wSurround[];// 0x01452c60
extern const float   g_fQuadVal;   // 0x01470f1c
extern const float   g_fSurroundVal; // 0x013eb95c
void* FUN_008d5d00();                                  // 0x008d5d00
void* FUN_00a16f40(void* self, void* a, void* b, void* c, void* d, void* e);  // 0x00a16f40
void* FUN_00a21d00(void* self, void* key, void* out);  // 0x00a21d00
void  FUN_00a27500(void* out, void* val);              // 0x00a27500
bool  WideEquals(void* ws, const wchar_t* lit);        // 0x006ab760
struct Key12 { unsigned a, b, c; };
struct Key16 { unsigned a, b, c, d; };
struct PairU { unsigned first; void* second; };
struct Tag { bool b; };
struct HNode;
struct HIter_s00a2_90b0 {
    void* node; HNode** bucket;
    HIter_s00a2_90b0() {}
    HIter_s00a2_90b0(const HIter_s00a2_90b0& x) : node(x.node), bucket(x.bucket) {}
};
struct InsertRes_s00a2_90b0 { void* node; HNode** bucket; bool inserted; };
struct HNode { unsigned key; void* value; HNode* next; };
struct FactoryB;
struct Obj_s00a2_90b0 {
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    virtual void v02();             // +0x08
    virtual void v03();             // +0x0c
    virtual void v04(FactoryB* f, void* r); // +0x10
    virtual void v05();             // +0x14
    virtual void v06();             // +0x18
    virtual void v07();             // +0x1c
    virtual void v08();             // +0x20
    virtual void v09();             // +0x24
    virtual void v10();             // +0x28
    virtual void v11();             // +0x2c
    virtual void v12();             // +0x30
    virtual void v13();             // +0x34
    virtual void v14();             // +0x38
    virtual void v15();             // +0x3c
};
struct KeyObj {
    virtual void k0();              // +0x00
    virtual void k1();              // +0x04
    virtual unsigned GetId8();      // +0x08
    virtual void k3();              // +0x0c
    virtual void k4();              // +0x10
    virtual void k5();              // +0x14
    virtual unsigned GetId18();     // +0x18
};
struct TexObj : Obj_s00a2_90b0 {
    int     pad4;                   // +0x04
    Key12   key;                    // +0x08
    int     pad14;                  // +0x14
    int     size;                   // +0x18
    int     pad1c;                  // +0x1c
    double  time;                   // +0x20
};
struct DbInfo {
virtual void i0();
virtual void i1();
    virtual void i2();              // +0x08
virtual void i3();
virtual void i4();
virtual void i5();
virtual void i6();
virtual void i7();
virtual void i8();
    virtual void i9();              // +0x24
};
struct DbObj {
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
    virtual bool Create(const void* key, void* out, int a, int b, int c, int d);  // +0x34
};
struct IConfig_s00a2_90b0 {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
    virtual bool GetList1(unsigned hash, void** out);          // +0x1c
    virtual void c8();
    virtual bool GetBool(unsigned hash, bool* out);            // +0x24
    virtual void c10();
    virtual bool GetUint32(unsigned hash, unsigned* out);      // +0x2c
    virtual bool GetFloat(unsigned hash, float* out);          // +0x30
virtual void c13();
virtual void c14();
    virtual void* GetString(unsigned id);                      // +0x3c
virtual void c16();
virtual void c17();
virtual void c18();
    virtual bool GetList2(unsigned hash, void** out, void** out2);  // +0x4c
};
struct FactoryB {
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
    virtual bool Create(void* info, void* out, int a, unsigned b); // +0x1c
};
struct HTable_s00a2_90b0 {
    int      pad0;          // +0x00
    HNode**  mpBuckets;     // +0x04
    unsigned mnBuckets;     // +0x08
    unsigned mnElements;    // +0x0c

    void  find(HIter_s00a2_90b0* out, const unsigned* key);                    // 0x00645ed0
    void  findKey12(HIter_s00a2_90b0* out, const void* key);                   // 0x00833840
    HIter_s00a2_90b0* erase(HIter_s00a2_90b0* out, HIter_s00a2_90b0 it);    // 0x00d2c9f0 (returns the iterator through out)
    HIter_s00a2_90b0* eraseNode(HIter_s00a2_90b0 node, HIter_s00a2_90b0* out);                       // 0x00a27660
    void  FreeBuckets(HNode** buckets, unsigned count);             // 0x00a24480
    void  InsertKey(InsertRes_s00a2_90b0* out, const unsigned* key, Tag t);    // 0x00a26be0
    void  InsertPair(InsertRes_s00a2_90b0* out, const void* pair, Tag t);      // 0x00a26ce0
    void  InsertPair16(InsertRes_s00a2_90b0* out, const void* pair, Tag t);    // 0x00a26b00
};
struct TexNode_s00a2_90b0 { Key12 key; TexObj* value; TexNode_s00a2_90b0* next; };
struct IdRing_s00a2_90b0 {
    unsigned* cBegin;       // +0x000
    unsigned* cEnd;         // +0x004
    char      pad[0xfbc - 8];
    unsigned* mBegin;       // +0xfbc
    unsigned* mEnd;         // +0xfc0
    int       mSize;        // +0xfc4
};
struct PooledTable {
    HTable_s00a2_90b0 table;                       // +0x0000
    char   pad[0x3ecc - sizeof(HTable_s00a2_90b0)];
    IdRing_s00a2_90b0 ring;                        // +0x3ecc
};
struct Stopwatch_s00a2_90b0 {
    char pad[0x14];
    float coeff;                        // +0x14
    Stopwatch_s00a2_90b0(int a, bool b);           // 0x0093a560
    void Restart();                     // 0x00571e80
    __int64 GetElapsedTimeF();          // 0x0093a3a0
};
struct WString {
    wchar_t* b; wchar_t* e; wchar_t* cap; int alloc;
    void RangeInit(const wchar_t* first);   // 0x00579a90
    ~WString()
    {
        if ((((char*)e - (char*)b) & ~1) > 2 && b)
            operator_delete__(b);
    }
};
struct StrList {
    const void*    mpBegin;     // +0x00
    unsigned       mnEnd;       // +0x04
    unsigned       mnSize;      // +0x08
    unsigned       mnCap;       // +0x0c
    unsigned short mFlags;      // +0x10
    unsigned short mInlineLen;  // +0x12
};
struct Str16_s00a2_90b0 { const char* mpStr; int b, c, d; };
struct Sys_s00a2_90b0 {
virtual void v000();
virtual void v001();
virtual void v002();
virtual void v003();
virtual void v004();
virtual void v005();
virtual void v006();
virtual void v007();
virtual void v008();
virtual void v009();
virtual void v010();
virtual void v011();
virtual void v012();
virtual void v013();
virtual void v014();
virtual void v015();
virtual void v016();
virtual void v017();
virtual void v018();
virtual void v019();
virtual void v020();
virtual void v021();
virtual void v022();
virtual void v023();
virtual void v024();
virtual void v025();
virtual void v026();
virtual void v027();
virtual void v028();
virtual void v029();
virtual void v030();
virtual void v031();
virtual void v032();
virtual void v033();
virtual void v034();
virtual void v035();
virtual void v036();
virtual void v037();
virtual void v038();
virtual void v039();
virtual void v040();
virtual void v041();
virtual void v042();
virtual void v043();
virtual void v044();
virtual void v045();
virtual void v046();
virtual void v047();
virtual void v048();
virtual void v049();
virtual void v050();
    virtual double SystemTime();                                // +0xcc (slot 51)
virtual void v052();
virtual void v053();
virtual void v054();
virtual void v055();
virtual void v056();
virtual void v057();
    virtual void v058(unsigned id, const char* name);           // +0xe8 (slot 58)
virtual void v059();
virtual void v060();
    virtual unsigned SymbolToId(const char* name);              // +0xf4 (slot 61)
    virtual void v062();
    virtual void SetProperty(float value, unsigned hash);       // +0xfc (slot 63)
virtual void v064();
virtual void v065();
virtual void v066();
virtual void v067();
virtual void v068();
virtual void v069();
virtual void v070();
virtual void v071();
    virtual void v072(unsigned id);                             // +0x120 (slot 72)
virtual void v073();
virtual void v074();
virtual void v075();
virtual void v076();
virtual void v077();
virtual void v078();
virtual void v079();
virtual void v080();
virtual void v081();
virtual void v082();
virtual void v083();
virtual void v084();
virtual void v085();
virtual void v086();
virtual void v087();
virtual void v088();
virtual void v089();
virtual void v090();
virtual void v091();
virtual void v092();
virtual void v093();
virtual void v094();
virtual void v095();
virtual void v096();
    virtual void v097();
    virtual void* FindDatabase(const void* key);                // +0x188 (slot 98)
virtual void v099();
virtual void v100();
virtual void v101();
virtual void v102();
virtual void v103();
virtual void v104();
virtual void v105();
virtual void v106();
virtual void v107();
virtual void v108();
virtual void v109();
virtual void v110();
    virtual void v111();
    virtual void Slot112();                                     // +0x1c0 (slot 112)

    char     pad_ec[0xec - 8];
    unsigned mStreamPoolNumStreams;    // +0x0ec
    unsigned mStreamPoolBufferSize;    // +0x0f0
    unsigned mStreamPoolMaxRequests;   // +0x0f4
    char     pad_f8[0x1f8 - 0x0f8];
    void*    mpConfiguration;          // +0x1f8
    char     pad_1fc[0x200 - 0x1fc];
    int      mPerformanceLevel;        // +0x200
    unsigned mU204;                    // +0x204
    unsigned mU208;                    // +0x208
    unsigned mU20c;                    // +0x20c
    char     pad_210[0x3fd - 0x210];
    bool     mBool3fd;                 // +0x3fd
    char     pad_3fe[0x400 - 0x3fe];
    float    mFloat400;                // +0x400
    HTable_s00a2_90b0   mPrimTable;               // +0x404
    char     pad_414[0x13f4 - 0x414];
    HTable_s00a2_90b0   mUnregTable;              // +0x13f4
    char     pad_1404[0x23e4 - 0x1404];
    HTable_s00a2_90b0   mClearTable;              // +0x23e4
    char     pad_23f4[0x118a1c - 0x23f4];
    HTable_s00a2_90b0   mActiveTable;             // +0x118a1c
    char     pad_118a2c[0x118a3c - 0x118a2c];
    HTable_s00a2_90b0   mLRUTable;                // +0x118a3c
    char     pad_118a4c[0x128ae0 - 0x118a4c];
    PooledTable mPoolA;                // +0x128ae0
    PooledTable mPoolB;                // +0x12d974
    PooledTable mPoolC;                // +0x132808
    char     pad_1376a0[0x15b750 - (0x132808 + sizeof(PooledTable))];
    TexNode_s00a2_90b0* mLRUIterNode;             // +0x15b750
    TexNode_s00a2_90b0** mLRUIterBucket;          // +0x15b754
    int      mCurrentBytes;            // +0x15b758
    int      mCountMiss;               // +0x15b75c
    int      mCountHit;                // +0x15b760
    int      mTimeSliceUSec;           // +0x15b764
    double   mRemoveOlderThanSec;      // +0x15b768
    int      mCacheSizeLimit;          // +0x15b770
    bool     mbDisableCache;           // +0x15b774
    char     pad_15b775[0x15b778 - 0x15b775];
    FactoryB* mpFactoryB;              // +0x15b778

    void  AddTextureRef(Key12* key);                   // 0x00a28a20
    bool  RegisterKey(void* key);                      // 00a290b0
    bool  UnregisterKey(void* key);                    // 00a29140
    void  ClearUnregTable();                           // 00a291b0
    void  ClearClearTable();                           // 00a29230
    unsigned PopIdA();                                 // 00a292d0
    unsigned PopIdC();                                 // 00a29340
    unsigned PopIdB();                                 // 00a293e0
    bool  GetTexture(Key12* key, void** out);          // 00a29450
    bool  GetTexture2(Key12* key, void** out2, void** out);   // 00a29690
    void  RemoveTexture(TexObj* obj);                  // 00a298f0
    void  SweepLRU();                                  // 00a29a50
    bool  ReadTuningValues(const Key12* key);          // 00a29be0
};
// ---- items of slice s00a290b0 end

// ---- items of slice s00a2af30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ARef_s00a2_af30 {
    IRef* p;
    ARef_s00a2_af30() : p(0) {}
    ARef_s00a2_af30(const ARef_s00a2_af30& o) : p(o.p) { if (p) p->AddRef(); }
    ARef_s00a2_af30& operator=(const ARef_s00a2_af30& o);
};
struct AR_s00a2_af30 {
    u32  a, b, c, d;
    ARef_s00a2_af30 r;
    AR_s00a2_af30() {}
    AR_s00a2_af30(const AR_s00a2_af30& o) : a(o.a), b(o.b), c(o.c), d(o.d), r(o.r) {}
    AR_s00a2_af30& operator=(const AR_s00a2_af30& o);
};
AR_s00a2_af30* __cdecl ARUninitCopy(AR_s00a2_af30* first, AR_s00a2_af30* last, AR_s00a2_af30* dst);     // 0x00a225d0
AR_s00a2_af30* __cdecl ARCopyBackward(AR_s00a2_af30* first, AR_s00a2_af30* last, AR_s00a2_af30* dst);   // 0x00a226c0
AR_s00a2_af30* __cdecl ARCopy(AR_s00a2_af30* first, AR_s00a2_af30* last, AR_s00a2_af30* dst);           // 0x00a22730
AR_s00a2_af30* __cdecl CopyElems20(AR_s00a2_af30** out, AR_s00a2_af30* first, AR_s00a2_af30* last, AR_s00a2_af30* dst, AR_s00a2_af30* end);  // 0x00a24750
AR_s00a2_af30* __cdecl ARDestroyRange(AR_s00a2_af30* first, AR_s00a2_af30* last, AR_s00a2_af30* out);   // 0x00a22680
struct ARVector {
    AR_s00a2_af30* mpBegin;        // +0
    AR_s00a2_af30* mpEnd;          // +4
    AR_s00a2_af30* mpCap;          // +8
    u32 pad_c;
    AR_s00a2_af30* mpFixed;        // +0x10
    void DoInsertValue(AR_s00a2_af30* pos, const AR_s00a2_af30* value);   // 0xa2af30
    void assign(const AR_s00a2_af30* first, const AR_s00a2_af30* last, const AR_s00a2_af30* last2);  // 0xa2b2e0
    void Destroy(AR_s00a2_af30* first, AR_s00a2_af30* end);               // 0xa24500 (declared only)
    AR_s00a2_af30*  DoAllocate(u32 n, const AR_s00a2_af30* first, const AR_s00a2_af30* last);   // 0xa27e00
};
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
#define BSWAP(x) ((u32)((((u32)(x) >> 24) | (((u32)(x) >> 8) & 0xff00) | \
                         (((u32)(x) << 8) & 0xff0000) | ((u32)(x) << 24))))
extern void* g_pSystem_s00a2_af30;                                       // 0x0166d9f4
unsigned int __cdecl ReadLine(void* s, char* b, int n);       // 0x0093a8b0
bool __cdecl TokLine(char* a, char* b, int d, char** x, char** y, char** z); // 0x0093d110
u32  __cdecl FNV1_String8(const char* s, u32 seed, int len);  // 0x00932e80
float __cdecl ParseFloat8(const char* s);                     // 0x00838740
void* __cdecl ConvertToString8Impl(void* out, const void* w, int n); // 0x0093c440
void* __cdecl cString8Assign(void* d, const void* s);         // 0x00579c60
void  __cdecl eastlStringDtor(void* s);                       // 0x00530670
void  __cdecl RelLocal(void* p);                              // 0x007a9610
void  __cdecl fnA34d70(void* a, void* b);                     // 0x00a34d70
void  __fastcall Disconnect(void* p);                         // 0x00a21590 (arg in ecx)
struct EraseVecT { void erase(void* first, void* last); };    // 0x009e0480 (vector::erase)
struct Vec12_s00a2_af30 { void pushEmpty(); };                           // 0x00a2ab40
struct Vec18_s00a2_af30 { void pushEmpty(); };                           // 0x00a2ab80
struct ZoneVec_s00a2_af30 { void push_back(const void* z); };            // 0x00a2abe0
struct SimpleVec { void DoInsertValue(void** pos, void** value); }; // 0x00a80dd0
struct PHTable_s00a2_af30 { void FreeBuckets(void** buckets, u32 n); };  // 0x00a24480
struct SubTable_s00a2_af30 { void DoFreeNodes(void* a, void* b); };      // 0x00a1b6c0
struct VoiceContainer_s00a2_af30 {
    bool ConstructVoice(void* tmpl);                          // 0x00a12f90
    bool Create(int flag);                                    // 0x00a342c0
    void MaskPluginBindings(const void* p, int n);            // 0x00a340b0
    void CommitBoundProperties();                             // 0x00a33dc0
    void Destroy();                                           // 0x00a343e0
};
struct OutRes {
    u32 pad0, pad1;          // +0/+4
    u32 h0, h1, h2;          // +8/+0xc/+0x10
    Vec12_s00a2_af30  vecA;             // +0x14  (12-byte elements)
    u32    pad20[0x194 / 4 - 7];
    Vec18_s00a2_af30  vecB;             // +0x194 (24-byte elements)
};
bool __stdcall FactoryVoiceTemplate_ReadResource(void* obj, OutRes* out, int, int);
struct Submix_s00a2_af30 {
    bool Init(void* param);  // 0x00a2b7d0 (Submix::Init)
    bool Shutdown();
};
struct Zone_s00a2_af30 {
    u8    pad[0x2c];
    float f[6];              // +0x2c
    u32   h[6];              // +0x44
    u32   extra[3];          // +0x5c
};
struct InstOut {
    u32 pad0, pad1;          // +0/+4
    u32 h0, h1, h2;          // +8/+0xc/+0x10
    int lastId;              // +0x14
    ZoneVec_s00a2_af30 zones;           // +0x18
};
bool __stdcall FactoryInstrumentBank_ReadResource(void* obj, InstOut* out, int, int);
struct DbgObject {
    virtual void d00();
    virtual void d04();
    virtual void d08();
    virtual bool CreateObject(int* a, void** out, int c, int d, int e, int f); // +0x0c
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1c();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2c();
    virtual void d30();
    virtual void d34();
};
void* __cdecl operator new(size_t n, const char* name, int b, int c, const char* file, int line);
struct SoundNode {
    SoundNode* mpNext;                            // +0x00 next / free-list link
    SoundNode* mpPrev;                            // +0x04 previous node
    char       mPad[8];
};
struct ListHead {
    SoundNode* mpNext;                            // +0x00 first real node
    SoundNode* mpPrev;                            // +0x04 last real node
};
struct SoundList_s00a2_af30 {
    ListHead   mHead;                             // +0x00 sentinel (its address is the terminator)
    SoundNode* mpFree;                            // +0x08 free-list head
    char       mPad0c[0x0c];
    unsigned   mnNodeSize;                        // +0x18
};
struct System_s00a2_af30 {
    static DbgObject* GetObjectError();          // 0x008de1a0
    void StopAllSounds(int param);  // 0x00a2be10 (System::StopAllSounds)
    void InsertSound(void* item);
};
struct VecP { void** begin; void** end; void** cap; };
// ---- items of slice s00a2af30 end

// ---- items of slice s00a2bfa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Key_s00a2_bfa0 { u32 a, b, c; };                                  // EA::ResourceMan::Key (12 bytes)
struct HTex {                                                 // this+0x1189fc
    u32     f0;            // +0
    void**  buckets;       // +4
    u32     count;         // +8
    void find(void* iterOut, const Key_s00a2_bfa0* key);                 // 0x00833840
    void insert(void* iterOut, const void* pair, int flag);   // 0x00a26b00
};
struct HAudio {                                               // this+0x119bb8
    u32     f0;            // +0
    void**  buckets;       // +4
    u32     count;         // +8
    void find(void* iterOut, const u32* key);                 // 0x00645ed0
    void* GetOrInsert(const u32* key);                        // 0x00a2a150
};
struct CtorT { void* ctor(u32 key); };
struct Sys_s00a2_bfa0 {
    u8      pad0[0x1189fc];
    HTex    texTable;      // +0x1189fc
    u8      pad1[0x119bb8 - (0x1189fc + 0xc)];
    HAudio  audioTable;    // +0x119bb8
    u8      pad2[0x157438 - (0x119bb8 + 0xc)];
    void*   soundList;     // +0x157438 (intrusive list head)

    bool GetTextureInstance(const Key_s00a2_bfa0* key, void** out);      // 0x00a2bfa0
    void Update();                                            // 0x00a2c140
    bool GetAudioA(u32 key, u32 param);                       // 0x00a2c450
    bool GetAudioB(u32 key);                                  // 0x00a2c590
    void NotifyTex(const Key_s00a2_bfa0* key);                           // 0x00a28a20 (thiscall)
};
void** g_vecBegin;                                            // 0x0166da14
void** g_vecEnd;                                              // 0x0166da18
void** g_vecCap;                                              // 0x0166da1c
u32    g_vecInit;                                             // 0x0166da28
void __cdecl vecBoolClear(void** begin, void** end, int v);   // 0x011e0744
struct PtrVec { void DoInsertValue(void** pos, void** value); }; // 0x00a80dd0
struct ObjFn { bool check(void); int check2(void); };
void __cdecl _atexit(void (*)(void));                         // 0x011e07ef
// ---- items of slice s00a2bfa0 end

// ---- items of slice s00a2f660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  gEmptyString16[];              // 0x1667bac  eastl::gEmptyString16
extern void* gAudioSystem;                  // 0x16e61a8  rw::audio::core::System*
extern void* gEapdDebug;                    // 0x166d9f4
extern void* FUN_008de1a0();                 // EA::Audio::Eapd::Debug::ObjectError
extern void  FUN_00a248a0();                 // ProfileTimer::ProfileTimer(void*)
extern void  FUN_00a24900();                 // ProfileTimer::Accumulate
extern void  FUN_00594410(void*);            // send-plugin table begin
extern void  FUN_00645ed0();                 // eastl::hashtable::find (ICF-merged)
extern void  FUN_00a34760();                 // VoiceContainer constructor
extern void  FUN_00a34620();                 // VoiceContainer::DtorTail
extern void  FUN_00a343e0();                 // VoiceContainer::Destroy
extern void  FUN_00a34890();                 // VoiceContainer::Disconnect
extern void  FUN_00a34bf0();                 // VoiceContainer::Connect
extern void  FUN_00a342c0();                 // VoiceContainer::Create
extern void  FUN_00a340b0();                 // VoiceContainer::MaskPluginBindings
extern void  FUN_00a144c0();                 // primitives table constructor
extern void  FUN_00a24480();                 // PHTable::FreeBuckets
extern void  FUN_00a2a870();                 // registers table constructor
extern void  FUN_00a1b6c0();                 // registers table DoFreeNodes
extern void  FUN_00a2a970();                 // send-plugin table constructor
extern void  FUN_0068fb70();                 // ProfHashTable::FreeBuckets
extern void  FUN_00a16a90(void*);            // release primitive
extern void  FUN_00d2c9f0();                 // cNodeList::Erase
extern void  FUN_00a2f660();                 // eastl::hash_node<...>::~hash_node
typedef unsigned short u16;
typedef unsigned __int64 u64;
extern u8    FUN_00a24850(const char*, u8*); // ParseResman
extern u32   FUN_00a2e4c0(u32);              // audio system helper
extern u32   FUN_0093a3a0();                 // Stopwatch::GetElapsedTimeFloat (thiscall)
extern u8    FUN_0112c640(u32);              // System predicate
extern u32   FUN_0112ccc0(u32, void*);       // send-plugin table step
extern u8    FUN_00a33dc0();                 // VoiceContainer::CommitBoundProperties
extern u8    FUN_00a33ee0();                 // VoiceContainer::SetProperty
extern void* FUN_00a16d00(u32);              // PAggC::PAggC(int)
extern void* FUN_00a16ad0(u32);              // allocate PrimitiveAggregate
extern void  FUN_00a136f0(void*, void*, u32);
struct PtrString
{
	void* mpBegin;   // +0x00
	void* mpEnd;     // +0x04
	void* mpCap;     // +0x08
	char  pad0c[4];  // +0x0c

	PtrString()
	{
		mpBegin = gEmptyString16;
		mpEnd   = gEmptyString16;
		mpCap   = (char*)gEmptyString16 + 1;
	}
	~PtrString()
	{
		if ((char*)mpCap - (char*)mpBegin > 1 && mpBegin != 0)
			operator_delete(mpBegin);
	}
};
struct AllocTag { AllocTag() {} };
struct FixedHashTable
{
	char   pad00[4];        // +0x00
	void** mpBucketArray;   // +0x04
	u32    mnBucketCount;   // +0x08
	u32    mnElementCount;  // +0x0c
	char   pad10[0xc];      // +0x10
	void*  mpFreeList;      // +0x1c
	char   pad20[4];        // +0x20
	void*  mpPoolBegin;     // +0x24
	void*  mpPoolEnd;       // +0x28
	char   pad2c[4];        // +0x2c
	void*  mpPoolTail;      // +0x30

	// shared bucket-buffer release/rebind tail of the table destructor
	void ReleaseBucketBuffer()
	{
		void** pBuckets = mpBucketArray;
		mnElementCount = 0;
		if (mnBucketCount > 1 && pBuckets != (void**)mpPoolTail) {
			if (pBuckets < (void**)mpPoolBegin || pBuckets >= (void**)mpPoolEnd) {
				operator_delete(pBuckets);
			} else {
				*pBuckets = mpFreeList;
				mpFreeList = pBuckets;
			}
		}
	}
};
struct PHTable_s00a2_f660 : FixedHashTable
{
	char pad34[0x438 - 0x34];
	PHTable_s00a2_f660(const AllocTag&, const AllocTag&);
	~PHTable_s00a2_f660();
};
PHTable_s00a2_f660::PHTable_s00a2_f660(const AllocTag& h, const AllocTag& e)
{
	((void(__thiscall*)(PHTable_s00a2_f660*, const AllocTag*, const AllocTag*))FUN_00a144c0)(this, &h, &e);
}
PHTable_s00a2_f660::~PHTable_s00a2_f660()
{
	((void(__thiscall*)(PHTable_s00a2_f660*, void**, u32))FUN_00a24480)(this, mpBucketArray, mnBucketCount);
	ReleaseBucketBuffer();
}
struct RegTable : FixedHashTable
{
	char pad34[0x820 - 0x34];
	RegTable(const AllocTag&, const AllocTag&);
	~RegTable();
};
RegTable::RegTable(const AllocTag& h, const AllocTag& e)
{
	((void(__thiscall*)(RegTable*, const AllocTag*, const AllocTag*))FUN_00a2a870)(this, &h, &e);
}
RegTable::~RegTable()
{
	((void(__thiscall*)(RegTable*, void**, u32))FUN_00a1b6c0)(this, mpBucketArray, mnBucketCount);
	ReleaseBucketBuffer();
}
struct PlugTable : FixedHashTable
{
	PlugTable(const AllocTag&, const AllocTag&);
	~PlugTable();
};
PlugTable::PlugTable(const AllocTag& h, const AllocTag& e)
{
	((void(__thiscall*)(PlugTable*, const AllocTag*, const AllocTag*))FUN_00a2a970)(this, &h, &e);
}
PlugTable::~PlugTable()
{
	((void(__thiscall*)(PlugTable*, void**, u32))FUN_0068fb70)(this, mpBucketArray, mnBucketCount);
	ReleaseBucketBuffer();
}
struct VoiceContainer_s00a2_f660
{
	char pad00[0x960];

	VoiceContainer_s00a2_f660();
	~VoiceContainer_s00a2_f660();

	void Destroy()                    { ((void(__thiscall*)(VoiceContainer_s00a2_f660*))FUN_00a343e0)(this); }
	void Disconnect()                 { ((void(__thiscall*)(VoiceContainer_s00a2_f660*))FUN_00a34890)(this); }
	void Connect()                    { ((void(__thiscall*)(VoiceContainer_s00a2_f660*))FUN_00a34bf0)(this); }
	void Create(u8 mode)              { ((void(__thiscall*)(VoiceContainer_s00a2_f660*, u8))FUN_00a342c0)(this, mode); }
	void MaskPluginBindings(const void* a, u32 b)
	                                  { ((void(__thiscall*)(VoiceContainer_s00a2_f660*, const void*, u32))FUN_00a340b0)(this, a, b); }
	u8   CommitBoundProperties()      { return ((u8(__thiscall*)(VoiceContainer_s00a2_f660*))FUN_00a33dc0)(this); }
	u8   SetProperty(u32 id, u32 v)   { return ((u8(__thiscall*)(VoiceContainer_s00a2_f660*, u32, u32))FUN_00a33ee0)(this, id, v); }
};
VoiceContainer_s00a2_f660::VoiceContainer_s00a2_f660() { ((void(__thiscall*)(VoiceContainer_s00a2_f660*))FUN_00a34760)(this); }
VoiceContainer_s00a2_f660::~VoiceContainer_s00a2_f660() { ((void(__thiscall*)(VoiceContainer_s00a2_f660*))FUN_00a34620)(this); }
struct Stopwatch_s00a2_f660 { u64 mStart; };
struct ProfileTimer_s00a2_f660
{
	Stopwatch_s00a2_f660 mTimer;     // +0x00
	float     mFactor;    // +0x08
	char      pad0c[0xc]; // +0x0c
	float*    mpTarget;   // +0x18

	ProfileTimer_s00a2_f660(void* p);
	~ProfileTimer_s00a2_f660();
};
ProfileTimer_s00a2_f660::ProfileTimer_s00a2_f660(void* p)
{
	((void(__thiscall*)(ProfileTimer_s00a2_f660*, void*))FUN_00a248a0)(this, p);
}
ProfileTimer_s00a2_f660::~ProfileTimer_s00a2_f660()
{
	const u64 elapsed = ((u64(__thiscall*)(Stopwatch_s00a2_f660*))FUN_0093a3a0)(&mTimer);
	float* const pTarget = mpTarget;
	*pTarget = (float)(int64_t)elapsed * mFactor + *pTarget;
}
struct IPrimitive;
struct IPrimitiveNode
{
	u32          mKey;      // +0x00
	IPrimitive*  mpValue;   // +0x04
	IPrimitiveNode* mpNext; // +0x08
};
struct HTIter
{
	IPrimitiveNode*  mpNode;    // +0x00
	IPrimitiveNode** mpBucket;  // +0x04
};
struct RefCountTemplate
{
	virtual void OnRefCountZero();
	virtual ~RefCountTemplate() {}
	int mRefCount;   // +0x04
	RefCountTemplate() : mRefCount(0) {}
};
struct IMixable
{
	virtual void Mixable0();
	virtual void Mixable1();
	virtual void Mixable2();
};
struct SecondaryBase
{
	virtual void Secondary0();
};
struct ConstructorParams
{
	u32 mFlags0;   // +0x00
	u32 mFlags1;   // +0x04
	u8  mFlag2;    // +0x08
	u8  mFlag3;    // +0x09
	u16 pad0a;     // +0x0a
	union { u32 mStamp; u8 mStampByte; };   // +0x0c
	u8  mFlag4;    // +0x10
	char pad11[3]; // +0x11
	union { u32 mValue; u8 mValueByte; };   // +0x14

	ConstructorParams()
		: mFlags0(0), mFlags1(0), mFlag2(1), mFlag3(0)
		, mStamp(0), mFlag4(0), mValue(0) {}
};
struct HashNode0
{
	char pad00[0x1e4];
	HashNode0* mpNext;   // +0x1e4
};
struct NodeAllocator
{
	void DoFreeNodes(HashNode0** pNodeArray, u32 n);
};
struct Submix_s00a2_f660 : IMixable, SecondaryBase, RefCountTemplate
{
	VoiceContainer_s00a2_f660    mVoiceContainer;   // +0x10
	u32               mId;               // +0x970
	u32               mSendId;           // +0x974
	PtrString         mSendName;         // +0x978
	PtrString         mName;             // +0x988
	u8                mbAddedToTick;     // +0x998
	char              pad999[3];         // +0x999
	PHTable_s00a2_f660           mPrimitives;       // +0x99c
	RegTable          mRegisters;        // +0xdd4
	ConstructorParams mParams;           // +0x15f4
	PlugTable         mSendPlugins;      // +0x160c

	Submix_s00a2_f660();
	~Submix_s00a2_f660();

	u32  LoadFromResman(const char* resName, u32 flags, u32 extra);
	void Tick(u32, u32);
	u32  SetPerformanceData(int level, const void* a, u32 b);
	void SetProperty(u32 id, u32 value);
	u32  ConnectPrimitive(u32 id, IPrimitive* p);
	void DisconnectPrimitive(u32 id, IPrimitive* p);  // 0x00a301f0 (Submix::DisconnectPrimitive)
};
// ---- items of slice s00a2f660 end

// ---- items of slice s00e22860 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVec3 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
};
struct cSPUIWindow;
struct cSPUILayout_s00e2_2860 {
    u8           mPad0000[0x18];
    cSPUIWindow* FindWindowByID(int windowID, int recurse);   // 0x008105b0
};
struct cSPUIAnimator_s00e2_2860 {
    void Update();                 // 0x007f63b0
};
struct cAudioObject;
struct cAudioEntry {
    int            mField0;        // 0x00
    cAudioObject*  mpObject4;      // 0x04
};
struct cPossePart {
    u8    mPad0000[0x10];
    void* mpField10;               // 0x10
};
static inline int VT_BC_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x2f])(p);
}
struct cSPUIPosse {
    u8            mPad0000[0x50];
    void*         mpField50;               // 0x50
    u8            mPad0054[0x60 - 0x54];
    int           mField60;                // 0x60
    u8            mPad0064[0x6c - 0x64];
    int           mField6c;                // 0x6c
    cVec3         mRect70;                 // 0x70
    cSPUILayout_s00e2_2860   mLayout7c;               // 0x7c
    u8            mPad0094[0xa4 - 0x94];
    cAudioEntry*  mpAudioBeginA4;          // 0xa4
    cAudioEntry*  mpAudioEndA8;            // 0xa8
    u8            mPad00ac[0xd4 - 0xac];
    cPossePart*   mpPartD4;                // 0xd4
    u8            mPad00d8[0x1bc - 0xd8];
    cSPUILayout_s00e2_2860   mLayout1bc;              // 0x1bc
    u8            mFlag1d4;                // 0x1d4
    u8            mPad01d5[0x1d8 - 0x1d5];
    float         mField1d8;               // 0x1d8
    float         mField1dc;               // 0x1dc
    u8            mPad01e0[0x1e4 - 0x1e0];
    u8            mFlag1e4;                // 0x1e4
    u8            mPad01e5[0x1e8 - 0x1e5];
    float         mField1e8;               // 0x1e8
    u8            mFlag1ec;                // 0x1ec
    u8            mPad01ed[0x208 - 0x1ed];
    cSPUIAnimator_s00e2_2860* mpAnimator208;          // 0x208

    void  UpdateLayout(int mode);          // 0x00e22b50
    void  SetToolWindowState(int a, int b);// 0x00e21bd0
    void  RefreshToolWindow(int a);        // 0x00e21ca0

    void  SnapToPosition();                // 0x00e22a60
    void  SetScaleF(float scale);          // 0x00e23130
    bool  SetVisibility(void* window);     // 0x00e231a0
    void  SetScale(int scale);             // 0x00e23200
    int   GetAudioCount();                 // 0x00e23250
    void  SetWindowImages(void* image);    // 0x00e235e0
    int   GetWindowImageCount();           // 0x00e23670
    void  GetWindowImageRange(int* out);   // 0x00e23680
    void  ClearToolWindow(int a, int b);   // 0x00e236a0
    void  ClearToolWindowOne(int a);       // 0x00e236b0
    void  SetWindowRect(const cVec3* rect, int unused);   // 0x00e236c0
};
// ---- items of slice s00e22860 end

// @ 0x00432ad0
void* Queryable::Cast(unsigned id)
{
    switch (id) {
    case 0x2269ed1:
        return this;
    case 0xee3f516e:
        return this;
    }
    return 0;
}

// @ 0x00a0f6a0
static __declspec(noinline) void* AudioAlloc(int a, int b, int c, int d, const char* name)
{
    char buf[0x80];
    strcpy(buf, "Audio");
    if (name) {
        buf[5] = '/';
        buf[6] = 0;
        strncpy(buf + 6, name, 0x7a);
    }
    return g_memPool->LockedAlloc(a, b, 0, name, c, d);
}

// @ 0x00a0f710
static __declspec(noinline) void* AudioAligned(int a, int b, int c, int d, int e, int f, const char* name)
{
    char buf[0x80];
    strcpy(buf, "Audio");
    if (name) {
        buf[5] = '/';
        buf[6] = 0;
        strncpy(buf + 6, name, 0x7a);
    }
    return g_memPool->LockedAligned(a, b, c, d, 0, name, e, f);
}

// @ 0x00a0f790
void* __stdcall AudioAllocA(int a, const char* name, int c)
{
    return AudioAlloc(a, c, (int)g_audioAllocatorFile, 0x3c, name);
}

// @ 0x00a0f7c0
void* __stdcall AudioAlignedA(int a, const char* name, int c, int d, int e)
{
    return AudioAligned(a, d, e, c, (int)g_audioAllocatorFile, 0x42, name);
}

// @ 0x00a0f7f0
void __stdcall AudioFree(void* p, int)
{
    g_memPool->Free(p);
}

// @ 0x00a0f810
AudioBlock* __stdcall AudioBlockAlloc(AudioBlock* out, const int* in, const char* name)
{
    void* p = AudioAligned(in[0], in[1], 0, 0, (int)g_audioAllocatorFile, 0x53, name);
    out->mPtr = 0;
    out->a = 0;
    out->b = 0;
    out->c = 0;
    out->mPtr = p;
    return out;
}

// @ 0x00a0f860
void __stdcall AudioFreeBlock(void** pp)
{
    g_memPool->Free(*pp);
}

// @ 0x00a17be0
EA::Audio::ResourceConfiguration::ResourceConfiguration()
{
    uint8_t* const h = (uint8_t*)this;
    *(void**)(h + 0) = (void*)0x13ebcdc;
    _InterlockedExchange((volatile long*)(h + 4), 0);
    *(uint32_t*)(h + 8) = 0;
    *(uint32_t*)(h + 0xc) = 0;
    *(uint32_t*)(h + 0x10) = 0;
    *(void**)(h + 0x14) = (void*)0x1449248;
    *(void**)(h + 0) = (void*)0x14523e8;
    *(void**)(h + 0x14) = (void*)0x1452398;
    *(uint8_t*)(h + 0x20) = 0;
    *(uint32_t*)(h + 0x24) = 0;
    *(uint32_t*)(h + 0x28) = 0;
    *(uint32_t*)(h + 0x2c) = 0;
    *(uint32_t*)(h + 0x3c) = 0;
    *(void**)(h + 0x44) = (void*)((uint32_t)this + 0x40);
    *(void**)(h + 0x40) = (void*)((uint32_t)this + 0x40);
    *(uint16_t*)(h + 0x58) = 0;
    *(uint16_t*)(h + 0x5a) = 0;
    *(uint16_t*)(h + 0x6c) = 0;
    *(uint16_t*)(h + 0x6e) = 0;
    *(uint32_t*)(h + 0x70) = 0;
    *(uint32_t*)(h + 0x74) = 0;
    *(uint32_t*)(h + 0x78) = 0;
    *(uint32_t*)(h + 0x1c) = 0;
    *(uint32_t*)(h + 0x18) = 0;
}

// @ 0x00a207a0
int Sys::ReleaseSub()
{
    int n = --*(int*)((char*)this + 0x18);
    if (n <= 0) {
        *(int*)((char*)this + 0x18) = 1;
        char* full = (char*)this - 4;
        if (full != 0)
            ((Node*)(full + 4))->n0(1);
        return 0;
    }
    return n;
}

// @ 0x00a207d0
bool Sys::Shutdown()
{
    if (*(char*)((char*)this + 0x94) == 0)
        return false;
    Mutex* m = (Mutex*)((char*)this + 0xb8);
    *(char*)((char*)this + 0x94) = 0;
    int n;
    {
        ScopedLock guard(m, (void*)0x1452970);
        ((Sub214*)((char*)this + 0x214))->Release();
        ((Sub214*)((char*)this + 0x264))->Release();
        ((Sub214*)((char*)this + 0x304))->Release();
        ((Sub214*)((char*)this + 0x354))->Release();
        ((void (__thiscall*)(void*, int))((*(void***)this)[0x38 / 4]))(this, 0x435b26d);
        ((void (__thiscall*)(void*))((*(void***)this)[0x58 / 4]))(this);
        *(char*)((char*)this + 0x88) = 1;
        n = m->GetLocation();
        if (n > 0) {
            int k = n;
            do {
                m->Unlock();
            } while (--k != 0);
        }
        ((Sub20*)((char*)this + 0x20))->F((void*)0x1452970, 0);
        if (n > 0) {
            do {
                m->Lock((void*)0x1452970);
            } while (--n != 0);
        }
    }
    if (g_166d9f4 != 0)
        ((SubRel*)(g_166d9f4 + 4))->Rel();
    g_166d9f4 = 0;
    g_166d9f8 = 0;
    return true;
}

// @ 0x00a20910
bool Sys::Route1(u32 id, int a, int b, float c, int d)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    ((void (__thiscall*)(void*, int, int, float, int))((*(void***)o)[0x1c / 4]))(o, a, b, c, d);
    return true;
}

// @ 0x00a20950
bool Sys::Route2(u32 id, float value)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    void* s = (char*)o + 4;
    ((void (__thiscall*)(void*, int, float, int))((*(void***)s)[0xc / 4]))(
        s, 0x25df0108, value, 1);
    return true;
}

// @ 0x00a20990
bool Sys::Route3(u32 id, float a, float b, float c)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    void* s = (char*)o + 4;
    typedef void (__thiscall *Set)(void*, int, float, int);
    ((Set)((*(void***)s)[0xc / 4]))(s, 0x50c5d67, a, 1);
    ((Set)((*(void***)s)[0xc / 4]))(s, 0x50c5d66, b, 1);
    ((Set)((*(void***)s)[0xc / 4]))(s, 0x50c5d65, c, 1);
    return false;
}

// @ 0x00a20a00
bool Sys::Route4(u32 id, void* a, void* b, void* c)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    ((void (__thiscall*)(void*, void*, void*, void*))((*(void***)o)[0x64 / 4]))(o, a, b, c);
    return true;
}

// @ 0x00a20a40
void Sys::SetSlot(int idx, void* a, void* b)
{
    ((V3*)((char*)this + 0x15b6c0))[idx] = *(const V3*)a;
    ((void (__thiscall*)(void*, int))((*(void***)this)[0x38 / 4]))(this, 0x3992099);
    ((void (__thiscall*)(void*, int, int))((*(void***)this)[0x40 / 4]))(this, 0x490d2eb, idx);
    ((void (__thiscall*)(void*, int, void*))((*(void***)this)[0x50 / 4]))(this, 0x3abafae, a);
    ((void (__thiscall*)(void*, int, void*))((*(void***)this)[0x54 / 4]))(this, 0x39e41fc, b);
    ((void (__thiscall*)(void*))((*(void***)this)[0x58 / 4]))(this);
}

// @ 0x00a20ac0
void Sys::GetSlot(int idx, void* out, void* big)
{
    *(V3*)out = *(V3*)((char*)this + 0x15b6d8 + idx * 0xc);
    *(Big9*)big = *(Big9*)((char*)this + 0x15b6f0 + idx * 0x24);
}

// @ 0x00a20b20
void Sys::Add214(void* a, float b)
{
    ((Sub214*)((char*)this + 0x214))->Add(a, b);
}

// @ 0x00a20ba0
void Sys::Commit214()
{
    int x = ((Sub214*)((char*)this + 0x214))->Get();
    ((void (__thiscall*)(void*, int))((*(void***)this)[0x1e8 / 4]))(this, x);
    ((Sub214*)((char*)this + 0x214))->Reset();
}

// @ 0x00a20be0
void Sys::Flush()
{
    if (g_166d9fc == 0)
        return;
    char c = *(char*)((char*)this + 0x3f4);
    while (c != 0) {
        int t = 0;
        ThreadSleep(&t);
        c = *(char*)((char*)this + 0x3f4);
    }
    int seq;
    {
        ScopedLock guard((Mutex*)((char*)this + 0xb8), (void*)0x1452970);
        *(char*)((char*)this + 0x3f4) = 1;
        ((Sub264*)((char*)this + 0x264))->F((char*)this + 0x214);
        seq = *(int*)((char*)this + 0x3f8);
    }
    int cur = *(int*)((char*)this + 0x3f8);
    while (seq == cur) {
        int t = 0;
        ThreadSleep(&t);
        cur = *(int*)((char*)this + 0x3f8);
    }
}

// @ 0x00a20cd0
unsigned int __stdcall HashString(const void* s)
{
    return FNV1_String8(s, 0x811c9dc5, 1);
}

// @ 0x00a20cf0
void Sys::Tick119(int a, int b)
{
    (void)a;
    X119* p = *(X119**)((char*)this + 0x119ba0);
    p->m((void*)b);
}

// @ 0x00a20d10
void Sys::Tick119b()
{
    X119* p = *(X119**)((char*)this + 0x119ba0);
    p->m2();
}

// @ 0x00a20d20
void* Sys::SlotA(int idx)
{
    return (void*)((char*)this + 0x15b6c0 + idx * 0xc);
}

// @ 0x00a20d40
void* Sys::SlotB(int idx)
{
    return (void*)((char*)this + 0x15b6d8 + idx * 0xc);
}

// @ 0x00a20d60
bool __stdcall MakeSound(Sound2** out)
{
    if (out == 0)
        return false;
    Sound2* p = new ("Audio/Sound", 0, 0, 0, 0) Sound2();
    *out = p;
    p->s0();
    return true;
}

// @ 0x00a20df0
bool Less1(SoundOrd* s, bool flag, OrdInfo* info)
{
    if (s->Flag(-1, 0) && !flag)
        return true;
    if (!s->Flag(-1, 0) && flag)
        return false;
    if (s->Flags() & 0x80)
        return true;
    bool has = s->Has() != 0;
    if (!has) {
        if (info->present != 0)
            return false;
    } else if (info->present == 0) {
        return true;
    }
    float f = s->Key1();
    if (f > info->key)
        return false;
    if (info->key > f)
        return true;
    if (has && info->present != 0) {
        float d = s->Dist();
        if (d > info->dist)
            return false;
        if (info->dist > d)
            return true;
    }
    return false;
}

// @ 0x00a20eb0
bool Less2(SoundOrd* a, SoundOrd* b)
{
    bool A = a->Flag(-1, 0) && !a->Flag(3, 0) && !a->Flag(2, 0);
    bool B = b->Flag(-1, 0) && !b->Flag(3, 0) && !b->Flag(2, 0);
    if (!A) {
        if (B)
            return true;
    } else if (!B) {
        return false;
    }
    bool ca = (a->Flags() & 0x80) == 0x80;
    bool cb = (b->Flags() & 0x80) == 0x80;
    if (!ca) {
        if (cb)
            return true;
    } else if (!cb) {
        return false;
    }
    bool ha = a->Has() != 0;
    bool hb = b->Has() != 0;
    if (!ha) {
        if (hb)
            return true;
    } else if (!hb) {
        return false;
    }
    float fa = a->Key1();
    float fb = b->Key1();
    if (fa > fb)
        return true;
    if (fb > fa)
        return false;
    if (ha && hb) {
        float va = 0.0f, vb = 0.0f;
        a->props.GetFloat(0x6325c989, &va);
        b->props.GetFloat(0x6325c989, &vb);
        if (va > vb)
            return true;
        if (vb > va)
            return false;
    }
    float ga = a->Key2();
    float gb = b->Key2();
    if (ga > gb)
        return true;
    return false;
}

// @ 0x00a21070
int __stdcall audioResult_00a21070(void* unused)
{
    return 5;
}

// @ 0x00a21080
bool Sys::WithinRange(void* a, int b)
{
    Obj* o = (Obj*)a;
    if (o->Check() != 0)
        return false;
    void** vt = *(void***)this;
    unsigned int idx = ((unsigned int (__thiscall*)(void*, int))((*(void***)o)[0x44 / 4]))(o, b);
    int got = ((int (__thiscall*)(void*, unsigned int))(vt[0x15c / 4]))(this, idx);
    unsigned int d = (unsigned int)(got - b);
    unsigned int len = (unsigned int)o->Span();
    if (d < len)
        return true;
    return false;
}

// @ 0x00a210d0
void Sys::LockB8()
{
    ((Mutex*)((char*)this + 0xb8))->Lock((void*)g_1452970);
}

// @ 0x00a21100
bool Sys::HasLocation()
{
    int n = ((DPF*)((char*)this + 0xb8))->GetLocation();
    return n > 0;
}

// @ 0x00a21130
int __stdcall isVoiceShareMsg_00a21130(void* msg)
{
    unsigned* m = (unsigned*)msg;
    if (m[2] == 0x21407ee) {
        unsigned v = m[1];
        if (v == 0x1a527db || v == 0x1eef63a || v == 0x42c9cbb || v == 0x3055f61)
            return 1;
    }
    return 0;
}

// @ 0x00a21170
void AudioSystem_00a21170::RegisterBuiltInModules()
{
    void* self = this;
    void* sys = TH(*(void**)((char*)self + 0xa4))->m_0112ce00();
    if (sys != 0) {
        TH(sys)->m_0112dca0();
        TH(sys)->m_0112cd60((void*)f_00a158d0());
        TH(sys)->m_0112cd60((void*)f_00a151c0());
        TH(sys)->m_0112cd60((void*)f_00a149a0());
        TH(sys)->m_0112cd60((void*)f_00a161b0());
        TH(sys)->m_0112cd60((void*)f_00a15d30());
        TH(sys)->m_0112cd60((void*)f_00a14800());
    }
    void* reg = TH(*(void**)((char*)self + 0xa4))->m_0112dc80();
    if (reg != 0)
        TH(reg)->m_0112dbd0();
}

// @ 0x00a21200
bool __stdcall isMsg00a21200(void* msg)
{
    return *(unsigned*)((char*)msg + 4) == 0x2c9eff2;
}

// @ 0x00a21220
double globalTime_00a21220()
{
    AudioCoreSystem_s00a2_1220* p = g_16e61a8;
    if (p != 0) return p->mTime;
    return 0.0;
}

// @ 0x00a21260
void __fastcall release_00a21260(void* self)
{
    int* rc = *(int**)((char*)self + 4);
    if (rc == 0) return;
    int n = (*(volatile int*)&rc[1] += -1);
    if (n == 0) {
        rc[1] = 1;
        _ReadWriteBarrier();
        void* vt = *(void**)rc;
        ((void (__thiscall*)(void*, int))((void**)vt)[0])(rc, 1);
    }
}

// Stand-in for the intrusive-list payload: its link base starts at +0x10.
// A base-to-derived cast preserves null while recovering the payload pointer.
struct AudioListPrefix { char payload[16]; };
struct AudioListLink { void* next; };
struct AudioListPayload : AudioListPrefix, AudioListLink {};

// @ 0x00a21290
void** __fastcall resetHead_00a21290(void** self)
{
    char* v = (char*)*self;
    v = *(char**)(v + 0x10);
    *self = static_cast<AudioListPayload*>((AudioListLink*)v);
    return self;
}

// @ 0x00a212b0
void __stdcall splice_00a212b0(void* a1, void* dummy, void* pos, void* last)
{
    if (pos == last) return;
    char* p1 = (char*)a1;
    char* p3 = (char*)pos;
    char* p4 = (char*)last;
    unsigned v = *(unsigned*)(p4 + 0x14);
    char* q = (v != 0) ? (char*)(v - 0x10) : (char*)0;
    char* piVar1 = q + 0x10;
    unsigned esi = *(unsigned*)(p3 + 0x14);
    char* ecx = p3 + 0x14;
    *(unsigned*)(*(unsigned*)piVar1 + 4) = esi;
    *(unsigned*)*(unsigned*)ecx = *(unsigned*)piVar1;
    unsigned v2 = *(unsigned*)(p1 + 0x14);
    char* iVar2 = (v2 != 0) ? (char*)(v2 - 0x10) : (char*)0;
    *(unsigned*)(iVar2 + 0x10) = (unsigned)(p3 + 0x10);
    *(unsigned*)ecx = (unsigned)(iVar2 + 0x10);
    *(unsigned*)piVar1 = (unsigned)(p1 + 0x10);
    *(unsigned*)(p1 + 0x14) = (unsigned)piVar1;
}

// @ 0x00a21310
void __stdcall erase_00a21310(void* a1, void* holder)
{
    char* eax_p = (char*)holder;
    unsigned edx = *(unsigned*)eax_p;
    if (edx == (unsigned)holder) return;
    char* ecx_p = (char*)a1;
    char* ebx_p = (char*)(ecx_p + 0x14);
    unsigned c = *(unsigned*)ebx_p;
    char* ebp_p = (c != 0) ? (char*)(c - 0x10) : (char*)0;
    char* esi_0 = (edx != 0) ? (char*)(edx - 0x10) : (char*)0;
    unsigned c2 = *(unsigned*)(eax_p + 4);
    char* edi_p = (c2 != 0) ? (char*)(c2 - 0x10) : (char*)0;
    char* edx2 = (esi_0 != 0) ? (char*)(esi_0 + 0x10) : (char*)0;
    *(unsigned*)(ebp_p + 0x10) = (unsigned)edx2;
    unsigned edx3 = (unsigned)a1;
    char* ecx2 = (char*)(ebp_p + 0x10);
    *(unsigned*)(esi_0 + 0x14) = (unsigned)ecx2;
    char* ecx3 = (char*)(edi_p + 0x10);
    edx3 += 0x10;
    *(unsigned*)ecx3 = edx3;
    *(unsigned*)ebx_p = (unsigned)ecx3;
    *(unsigned*)eax_p = (unsigned)eax_p;
    *(unsigned*)(eax_p + 4) = (unsigned)eax_p;
}

// @ 0x00a21390
bool EA::Audio::Submix::DisconnectFromSubmix()
{
    AudioLockGuard guard;
    void* esi = (char*)this + 0x10;
    void* p = TH(esi)->m_00a34230(0x41695730);
    if (p != 0)
        TH(p)->m_0112ccc0(1, 0);
    TH(esi)->m_00a34890();
    return true;
}

// @ 0x00a21410
bool VoiceContainer_s00a2_1130::Connect(int a1, int a2)
{
    char* self = (char*)this;
    void* p = TH(self + 0x10)->m_00a34230(0x53747030);
    if (p == 0) return false;
    AutoAudioLock lock;
    int buf[2];
    buf[0] = a1;
    buf[1] = a2;
    TH(p)->m_0112ccc0(2, buf);
    return true;
}

// @ 0x00a214b0
bool VoiceContainer_s00a2_1130::Connect4(int a1, int a2, int a3, int a4)
{
    char* self = (char*)this;
    char cached = (*(int*)(self + 0x15f4) != 0);
    if (!cached)
        *(void**)(self + 0x15f4) = TH(self + 0x10)->m_00a34230(0x53747030);
    if (*(int*)(self + 0x15f4) == 0) return false;
    AutoAudioLock lock;
    if (!cached) {
        int buf[4];
        buf[0] = a2;
        buf[1] = a3;
        buf[2] = a4;
        buf[3] = a1;
        TH(*(void**)(self + 0x15f4))->m_0112ccc0(0, buf);
    }
    return true;
}

// @ 0x00a21590
void __fastcall disconnect_00a21590(char* self)
{
    if (*(int*)(self + 0x15f4) == 0) return;
    AudioLockGuard guard;
    TH(*(void**)(self + 0x15f4))->m_0112ccc0(1, 0);
    *(void**)(self + 0x15f4) = 0;
}

struct IObj_00a21630 {
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void Send(int a, int b);   // +0x18
};
struct ObjRef_00a21630 {
    IObj_00a21630* p;
    ObjRef_00a21630(IObj_00a21630* raw) : p(raw) { if (p) p->AddRef(); }
    ~ObjRef_00a21630() { if (p) p->Release(); }
};
struct MsgSrc_00a21630 {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
    virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
    virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75(); virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
    virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87(); virtual void s88(); virtual void s89();
    virtual void s90(); virtual void s91(); virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95(); virtual void s96(); virtual void s97(); virtual void s98(); virtual void s99();
    virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103(); virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107(); virtual void s108(); virtual void s109();
    virtual void s110(); virtual void s111(); virtual void s112(); virtual void s113(); virtual void s114(); virtual void s115(); virtual void s116();
    virtual IObj_00a21630* GetObj(int id);   // +0x1d4
};

// @ 0x00a21630
bool MsgTarget_00a21630::Handle(int a1, int a2)
{
    ObjRef_00a21630 ref(((MsgSrc_00a21630*)this)->GetObj(a1));
    if (ref.p == 0) return false;
    ref.p->Send(2, a2);
    return true;
}

// @ 0x00a216d0
void __fastcall get3_00a216d0(char* self, void* dummy, int* a, int* b, int* c)
{
    if (a != 0) *a = *(int*)(self + 0x200);
    if (b != 0) *b = *(int*)(self + 0x15bb7c);
    if (c != 0) *c = (*(int*)(self + 0x15bb80) - *(int*)(self + 0x15bb7c)) >> 2;
}

// @ 0x00a21710
bool __fastcall HandleMessage_00a21710(char* self, void* dummy, unsigned msg, void* info)
{
    char* esi = self - 4;
    void* vt;
    char* edi;

    switch (msg) {
    case 0xff0f31:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475373);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475391, *(float*)(edi + 0x10));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475395, *(float*)(edi + 0x18));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475398, *(float*)(edi + 0x20));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0xff0ed1:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475365);
        edi = (char*)info;
        if (*(unsigned*)(edi + 0x88) & 1)
            VPTR(void, esi, 0x44, unsigned, int, int)(esi, 0x347537e, *(int*)(edi + 8), 0);
        if ((*(unsigned*)(edi + 0x88) >> 1) & 1)
            VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475381, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 0x18));
        if ((*(unsigned*)(edi + 0x88) >> 8) & 1)
            VPTR(void, esi, 0x48, unsigned, int)(esi, 0x347539c, *(int*)(edi + 0x48));
        if (((*(unsigned*)(edi + 0x88) >> 5) & 1) && ((*(unsigned*)(edi + 0x88) >> 6) & 1)
            && ((*(unsigned*)(edi + 0x88) >> 7) & 1)) {
            VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475391, *(float*)(edi + 0x30));
            VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475395, *(float*)(edi + 0x38));
            VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475398, *(float*)(edi + 0x40));
            VPTR(void, esi, 0x58)(esi);
            return true;
        }
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0xff0ee1:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x347536b);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753a0, *(int*)(edi + 0x10));
        return true;
    case 0xff0f01:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x347536f);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x34753a4, *(float*)(edi + 0x10));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0x1956125:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475376);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753a7, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x34753aa, *(float*)(edi + 0x18));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753ad, *(int*)(edi + 0x20));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0x19aa8ab:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475331);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475381, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0x24255a9:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x347537a);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753a7, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x4c, unsigned, int, int)(esi, 0x34753b0, *(int*)(edi + 0x18), *(int*)(edi + 0x20));
        VPTR(void, esi, 0x58)(esi);
        return true;
    default:
        break;
    }
    return true;
}

// @ 0x00a21a60
void __fastcall forward_00a21a60(void* self)
{
    void* p = *(void**)((char*)self + 0xc);
    if (p == 0) return;
    char* q = (char*)p + 4;
    void* vt = *(void**)q;
    void* fn = *(void**)((char*)vt + 4);
    ((void (__thiscall*)(void*))fn)(q);
}

struct VoiceRef_a21a80 {
    virtual void AddRef();
    virtual void Release();
    uchar pad04[0x970 - 4];
    unsigned mTag;   // +0x970
};
struct VoicePtr_a21a80 {
    VoiceRef_a21a80* p;
    VoicePtr_a21a80(VoiceRef_a21a80* q) : p(q) { if (p) p->AddRef(); }
    ~VoicePtr_a21a80() { p->Release(); }
};

// @ 0x00a21a80
void* AudioSys_00a21a80::FindVoice(unsigned tag)
{
    char* self = (char*)this;
    if (tag == 0) tag = 0xf1cc1687;
    VoiceRef_a21a80** end = *(VoiceRef_a21a80***)(self + 0x119ba8);
    for (VoiceRef_a21a80** it = *(VoiceRef_a21a80***)(self + 0x119ba4); it != end; ++it) {
        VoicePtr_a21a80 v(*it);
        if (tag == v.p->mTag)
            return v.p;
    }
    return 0;
}

// @ 0x00a21b20
bool __fastcall command_00a21b20(char* self, void* dummy, int a1, int a2, int a3, int a4, int a5)
{
    if (a2 == 0 || a3 == 0) return false;
    void* p = VPTR(void*, self, 0x17c, int)(self, a1);
    if (p != 0) {
        if (((VoiceContainer_s00a2_1130*)p)->Connect(a2, a3)) {
            return true;
        }
    }
    if (a4 == 0) return false;
    unsigned n = (unsigned)a3;
    for (unsigned i = 0; i < n; ++i) {
        void* v = *(void**)(a2 + i * 4);
        ((void (__cdecl*)(void*, void*))a4)(v, (void*)a5);
    }
    return false;
}

// @ 0x00a21b90
bool __fastcall command4_00a21b90(char* self, void* dummy, int a1, int a2, int a3, int a4, int a5)
{
    if (a4 == 0) return false;
    void* p = VPTR(void*, self, 0x17c, int)(self, a1);
    if (p == 0) return false;
    return ((VoiceContainer_s00a2_1130*)p)->Connect4(a2, a3, a4, a5);
}

// @ 0x00a21bd0
void __fastcall command_00a21bd0(void* self, void* dummy, int a)
{
    void* p = VPTR(void*, self, 0x17c, int)(self, a);
    if (p != 0)
        disconnect_00a21590((char*)p);
}

// @ 0x00a21c00
VoiceVec_00a21c00::~VoiceVec_00a21c00()
{
    IVoice_00a21c00** end = mpEnd;
    for (IVoice_00a21c00** it = mpBegin; it < end; ++it) {
        if (*it != 0)
            (*it)->Release();
    }
}

// @ 0x00a21c70
void** __fastcall nodeToPayload_00a21c70(void* self, void* dummy, void** out)
{
    void* v = *(void**)self;
    *out = static_cast<AudioListPayload*>((AudioListLink*)v);
    return out;
}

// @ 0x00a21c90
void** __fastcall nodeToPayload_00a21c90(void* self, void* dummy, void** out)
{
    *out = static_cast<AudioListPayload*>((AudioListLink*)self);
    return out;
}

// @ 0x00a21cb0
void* __stdcall listInsert_00a21cb0(void* a1, void* holder, void* newnode)
{
    char* eax_p = (char*)holder;
    char* edx_p = (char*)(eax_p + 0x14);
    unsigned e = *(unsigned*)edx_p;
    char* esi_p = (e != 0) ? (char*)(e - 0x10) : (char*)0;
    char* ecx_p = (char*)newnode;
    char* eax2 = (ecx_p != 0) ? (char*)(ecx_p + 0x10) : (char*)0;
    *(unsigned*)edx_p = (unsigned)eax2;
    unsigned edx2 = *(unsigned*)edx_p;
    char* eax3 = (char*)(esi_p + 0x10);
    *(unsigned*)eax3 = edx2;
    *(unsigned*)(ecx_p + 0x14) = (unsigned)eax3;
    char* eax4 = (char*)(eax_p + 0x10);
    *(unsigned*)(ecx_p + 0x10) = (unsigned)eax4;
    *(unsigned*)a1 = (unsigned)ecx_p;
    return a1;
}

// @ 0x00a21d00
void* __fastcall copyRef_00a21d00(char* self, void* dummy, void* src, unsigned** ref)
{
    *(unsigned*)(self + 0) = *(unsigned*)((char*)src + 0);
    *(unsigned*)(self + 4) = *(unsigned*)((char*)src + 4);
    *(unsigned*)(self + 8) = *(unsigned*)((char*)src + 8);
    unsigned r = (unsigned)*ref;
    *(unsigned*)(self + 0xc) = r;
    if (r != 0) VPTR(void, (void*)r, 0)((void*)r);
    return self;
}

// @ 0x00a21d30
void __fastcall ringPush_00a21d30(char* self, void* dummy, unsigned* v)
{
    unsigned* p = *(unsigned**)(self + 0xfc0);
    *p = *v;
    *(unsigned*)(self + 0xfc0) += 4;
    unsigned* end = *(unsigned**)(self + 4);
    if (*(unsigned**)(self + 0xfc0) == end)
        *(unsigned*)(self + 0xfc0) = *(unsigned*)self;
    unsigned* begin = *(unsigned**)(self + 0xfbc);
    if (*(unsigned**)(self + 0xfc0) == begin) {
        begin = begin + 1;
        *(unsigned*)(self + 0xfbc) = (unsigned)begin;
        if (begin == end)
            *(unsigned*)(self + 0xfbc) = *(unsigned*)self;
        return;
    }
    ++*(unsigned*)(self + 0xfc4);
}

// @ 0x00a21d90
void* __fastcall copyRef2_00a21d90(char* self, void* dummy, unsigned** a, unsigned** b)
{
    *(unsigned*)(self + 0) = (unsigned)*a;
    unsigned r = (unsigned)*b;
    *(unsigned*)(self + 4) = r;
    if (r != 0) VPTR(void, (void*)r, 0)((void*)r);
    return self;
}

// key = {a, b, c}; compared on a, then c, then b
static __forceinline bool KeyLess_a21dc0(const unsigned* x, const unsigned* y)
{
    if (x[0] != y[0]) return x[0] < y[0];
    if (x[2] != y[2]) return x[2] < y[2];
    return x[1] < y[1];
}
static __forceinline char* LowerBound_a21dc0(RbTree_00a21dc0* t, const unsigned* k)
{
    char* node = *(char**)((char*)t + 0xc);
    char* result = (char*)t + 4;
    while (node) {
        if (!KeyLess_a21dc0((const unsigned*)(node + 0x10), k)) {
            result = node;
            node = *(char**)(node + 4);
        } else
            node = *(char**)(node + 0);
    }
    return result;
}
// @ 0x00a21dc0
void* RbTree_00a21dc0::Find(void** out, void* key)
{
    char* root = (char*)this + 4;
    const unsigned* k = (const unsigned*)key;
    char* it = LowerBound_a21dc0(this, k);
    if (it != root && !KeyLess_a21dc0(k, (const unsigned*)(it + 0x10))) {
        *out = it;
        return out;
    }
    *out = root;
    return out;
}

// @ 0x00a21eb0
void HashA_00a21eb0::Rehash(unsigned a)
{
    char* self = (char*)this;
    int count = (int)a;
    void* newTable = ((HashA_00a21eb0*)self)->Alloc(a);
    int i = 0;
    for (i = 0; (unsigned)i < *(unsigned*)(self + 8); ++i) {
        int* node = *(int**)((char*)*(void**)(self + 4) + i * 4);
        if (node == 0) continue;
        for (;;) {
            unsigned h = (unsigned)(node[2] ^ node[0]);
            unsigned bucket = h % a;
            int* next = (int*)node[4];
            *(unsigned*)((char*)*(void**)(self + 4) + i * 4) = (unsigned)next;
            int** head = (int**)((char*)newTable + bucket * 4);
            node[4] = (int)*head;
            *head = node;
            node = *(int**)((char*)*(void**)(self + 4) + i * 4);
            if (node == 0) break;
        }
    }
    if (*(unsigned*)(self + 8) > 1) {
        void* p = *(void**)(self + 4);
        if (p != *(void**)(self + 0x30)) {
            if ((char*)p >= *(char**)(self + 0x24) && (char*)p < *(char**)(self + 0x28)) {
                *(void**)p = *(void**)(self + 0x1c);
                *(void**)(self + 0x1c) = p;
            } else {
                f_00f47380(p);
            }
        }
    }
    *(void**)(self + 4) = newTable;
    *(unsigned*)(self + 8) = (unsigned)count;
}

struct Node_00a21f60 {
    unsigned a, b, c;
    void* ref;      // +0xc
    unsigned m10;   // +0x10
    Node_00a21f60(const Node_00a21f60& o) : a(o.a), b(o.b), c(o.c), ref(o.ref)
    {
        if (ref) VPTR(void, ref, 0)(ref);
        m10 = 0;
    }
};

// @ 0x00a21f60
void* __stdcall allocRef_00a21f60(void* src)
{
    Node_00a21f60* p = (Node_00a21f60*)f_00f473a0(0x14, (void*)0x13f2150, 0, 0, (void*)0x13ebb38, 0xd1);
    if (p != 0)
        new (p) Node_00a21f60(*(const Node_00a21f60*)src);
    return p;
}

// @ 0x00a22060
void HashB_00a22060::Rehash(unsigned a)
{
    char* self = (char*)this;
    int count = (int)a;
    void* newTable = ((HashB_00a22060*)self)->Alloc(a);
    int i = 0;
    for (i = 0; (unsigned)i < *(unsigned*)(self + 8); ++i) {
        int* node = *(int**)((char*)*(void**)(self + 4) + i * 4);
        if (node == 0) continue;
        for (;;) {
            unsigned bucket = (unsigned)node[0] % a;
            int* next = *(int**)((char*)node + 0x1e4);
            *(unsigned*)((char*)*(void**)(self + 4) + i * 4) = (unsigned)next;
            int** head = (int**)((char*)newTable + bucket * 4);
            *(unsigned*)((char*)node + 0x1e4) = (unsigned)*head;
            *head = node;
            node = *(int**)((char*)*(void**)(self + 4) + i * 4);
            if (node == 0) break;
        }
    }
    if (*(unsigned*)(self + 8) > 1) {
        void* p = *(void**)(self + 4);
        if (p != *(void**)(self + 0x30)
            && !((char*)p < *(char**)(self + 0x24) || (char*)p >= *(char**)(self + 0x28))) {
            f_00f47380(p);
        }
    }
    *(void**)(self + 4) = newTable;
    *(unsigned*)(self + 8) = (unsigned)count;
}

// @ 0x00a22110
void HashC_00a22110::Rehash(unsigned a)
{
    char* self = (char*)this;
    int count = (int)a;
    void* newTable = ((HashC_00a22110*)self)->Alloc(a);
    int i = 0;
    for (i = 0; (unsigned)i < *(unsigned*)(self + 8); ++i) {
        int* node = *(int**)((char*)*(void**)(self + 4) + i * 4);
        if (node == 0) continue;
        for (;;) {
            unsigned bucket = (unsigned)node[0] % a;
            int* next = *(int**)((char*)node + 0x24);
            *(unsigned*)((char*)*(void**)(self + 4) + i * 4) = (unsigned)next;
            int** head = (int**)((char*)newTable + bucket * 4);
            *(unsigned*)((char*)node + 0x24) = (unsigned)*head;
            *head = node;
            node = *(int**)((char*)*(void**)(self + 4) + i * 4);
            if (node == 0) break;
        }
    }
    if (*(unsigned*)(self + 8) > 1) {
        void* p = *(void**)(self + 4);
        if (p != *(void**)(self + 0x30)) {
            if ((char*)p >= *(char**)(self + 0x24) && (char*)p < *(char**)(self + 0x28)) {
                *(void**)p = *(void**)(self + 0x1c);
                *(void**)(self + 0x1c) = p;
            } else {
                f_00f47380(p);
            }
        }
    }
    *(void**)(self + 4) = newTable;
    *(unsigned*)(self + 8) = (unsigned)count;
}

// @ 0x00a22220
void HTable28::Rehash(u32 n)
{
    HNode28** nb = AllocBuckets(n);
    for (u32 i = 0; i < bucketCount; ++i) {
        HNode28* p = buckets[i];
        while (p != 0) {
            u32 h = p->key % n;
            buckets[i] = p->next;
            p->next = nb[h];
            nb[h] = p;
            p = buckets[i];
        }
    }
    HNode28** old = buckets;
    if (bucketCount > 1 && old != (HNode28**)inlineBuckets) {
        if ((void*)old >= poolBegin && (void*)old < poolEnd) {
            *(void**)old = freeList;
            freeList = old;
            buckets = nb;
            bucketCount = n;
            return;
        }
        op_delete(old);
    }
    buckets = nb;
    bucketCount = n;
}

// @ 0x00a222c0
void PoolList::FreeNodes()
{
    void** n = (void**)head;
    while (n != (void**)this) {
        void** cur = n;
        n = (void**)*n;
        if ((void*)cur < poolBegin || (void*)cur >= poolEnd) {
            op_delete(cur);
        } else {
            *cur = freeList;
            freeList = cur;
        }
    }
}

// @ 0x00a22370
void HTable20::Rehash(u32 n)
{
    HNode20** nb = AllocBuckets(n);
    for (u32 i = 0; i < bucketCount; ++i) {
        HNode20* p = buckets[i];
        while (p != 0) {
            u32 h = p->key % n;
            buckets[i] = p->next;
            p->next = nb[h];
            nb[h] = p;
            p = buckets[i];
        }
    }
    HNode20** old = buckets;
    if (bucketCount > 1 && old != (HNode20**)inlineBuckets) {
        if ((void*)old >= poolBegin && (void*)old < poolEnd) {
            *(void**)old = freeList;
            freeList = old;
            buckets = nb;
            bucketCount = n;
            return;
        }
        op_delete(old);
    }
    buckets = nb;
    bucketCount = n;
}

// @ 0x00a22410
void SList::merge(SList& x, bool (__cdecl* compare)(Snd*, Snd*))
{
    if (this != &x) {
        Snd* first  = Snd::FromNode(anchor.next);
        Snd* firstX = Snd::FromNode(x.anchor.next);
        Snd* last   = (Snd*)((char*)this - 0x10);
        Snd* lastX  = (Snd*)((char*)&x - 0x10);
        while (first != last && firstX != lastX) {
            if (compare(firstX, first)) {
                Snd* next = Snd::FromNode(firstX->node.next);
                if (firstX != next) {
                    Snd* nprev = Snd::FromNode(next->node.prev);
                    SNode* a = &nprev->node;
                    a->next->prev = firstX->node.prev;
                    firstX->node.prev->next = a->next;
                    Snd* pprev = Snd::FromNode(first->node.prev);
                    SNode* b = &pprev->node;
                    b->next = &firstX->node;
                    firstX->node.prev = b;
                    a->next = &first->node;
                    first->node.prev = a;
                }
                firstX = next;
            } else {
                first = Snd::FromNode(first->node.next);
            }
        }
        if (firstX != lastX) {
            splice(SIter(last), x, SIter(firstX), SIter(lastX));
        }
    }
}

// @ 0x00a225d0
AR* __cdecl ARUninitCopy(AR* first, AR* last, AR* dst)
{
    for (; first != last; ++first, ++dst)
        ::new((void*)dst) AR(*first);
    return dst;
}

// @ 0x00a226c0
AR* __cdecl ARCopyBackward(AR* first, AR* last, AR* dst)
{
    while (last != first) {
        --last;
        --dst;
        *dst = *last;
    }
    return dst;
}

// @ 0x00a22730
AR* __cdecl ARCopy(AR* first, AR* last, AR* dst)
{
    for (; first != last; ++first, ++dst)
        *dst = *first;
    return dst;
}

// @ 0x00a227a0
DrvBA22::DrvBA22(void* arg)
: DrvArgA22(arg), RefBaseA22(), mZero(0) {}

// @ 0x00a227d0
ResourceDeviceDriver* MakeRDD()
{ return new ResourceDeviceDriver; }

// @ 0x00a22820
void Subscription::UpdateOutput(Builder* b)
{
    RBNode* n = anchor.left;
    if (n != &anchor) {
        do {
            u32 key = n->key;
            float v;
            if (mpMixable->Query(key, &v)) {
                b->Begin(0x407c01d);
                b->AddInt(0x3475385, mpMixable->GetId());
                b->AddInt(0x34753a7, key);
                b->AddFloat(0x34753aa, v);
                b->Commit();
            }
            n = RBTreeIncrement(n);
        } while (n != &anchor);
    }
}

// @ 0x00a228d0
int __cdecl WorkerThread(WorkerCtx* self)
{
    g_166d9fc = GetThreadId_();
    void* sys = (void*)g_166d9f4;
    if (sys) {
        char ok = VCALL(char (__thiscall*)(void*), sys, 0x68)(sys);
        if (g_166d9f4)
            VCALL(void (__thiscall*)(void*), (void*)g_166d9f4, 0xc0)((void*)g_166d9f4);
        self->mode = (ok == 0 ? 1 : 0) + 1;
        if (g_166d9f4)
            VCALL(void (__thiscall*)(void*), (void*)g_166d9f4, 0xc4)((void*)g_166d9f4);
        self->Init(0);
        if (ok) {
            Stopwatch sw(5, 0);
            sw.Restart();
            float acc = 0.0f;
            while (self->stop == 0) {
                float dt = (float)sw.GetElapsedTimeFloat() * sw.mfStopwatchCyclesToUnitsCoefficient;
                if (0.02f <= dt) {
                    if (dt > 0.06f)
                        dt = 0.06f;
                    acc += dt;
                    sw.RestartInline();
                    VCALL(void (__thiscall*)(void*, float, float), sys, 0xd0)(sys, acc, dt);
                    VCALL(void (__thiscall*)(void*), sys, 0xd4)(sys);
                }
                float e = (float)sw.GetElapsedTimeFloat() * sw.mfStopwatchCyclesToUnitsCoefficient;
                float rem = 0.02f;
                if (!(e > 0.02f))
                    rem = 0.02f - e;
                rem *= 1000.0f;
                int ms = CeilToInt(rem);
                ThreadSleep(&ms);
            }
            VCALL(void (__thiscall*)(void*), sys, 0x6c)(sys);
        }
    }
    return 0;
}

// @ 0x00a22b00
int __stdcall MakeKeyPair(int* out, int)
{
    if (out != 0) {
        out[0] = 0x1a527db;
        out[1] = 0x42c9cbb;
    }
    return 2;
}

// @ 0x00a22b90
bool __stdcall LoadShared(IStream_* stream, Item* item, int, int)
{
    IProvider* p = (IProvider*)stream->Next();
    if (p->GetType() == 0x347223d2) {
        int blk = *(int*)((char*)p + 4);
        item->data = *(int*)(blk + 0x10);
        item->size = p->GetSize();
        item->mShared.Assign((void*)blk);
        return true;
    }
    IAlloc* alloc = GetDefaultAllocator();
    item->data = alloc->Alloc(p->GetSize(), "Audio", 1);
    item->size = p->GetSize();
    SharedPtr* sp = new ("Audio", 0, 0, 0, 0) SharedPtr(item->data, 1, alloc);
    item->mShared.Assign(sp);
    bool ok = p->Read(item->data, item->size) == item->size;
    if (!ok) {
        item->data = 0;
        item->size = 0;
        SharedBlock* old = item->mShared.p;
        if (old) {
            item->mShared.p = 0;
            old->sub.Release();
        }
    }
    return ok;
}

// @ 0x00a23360
float System::GetPosDist(float* p)
{
    float result;
    if (b15bbf0) {
        double dx = pos[0] - p[0];
        double dy = pos[1] - p[1];
        double dz = pos[2] - p[2];
        double d = dx * dx;
        d = d + dz * dz;
        d = d + dy * dy;
        result = (float)sqrt(d);
    } else {
        result = 0.0f;
    }
    return result;
}

// @ 0x00a233b0
void System::MuteAll(bool bMute, bool bParam)
{
    if (mbMuted != bMute) {
        // Walk the intrusive list anchored at &listNext (link parked at +0x10).
        u8* head = (u8*)listNext;
        u8* anchor = (u8*)&listNext;
        u8* it = head ? head - 0x10 : 0;
        u8* end = anchor - 0x10;
        while (it != end) {
            bool bFlag = false;
            void* obj = vc<void*>(it, 0x30);
            bool ok = vc<bool>(obj, 0x24, (u32)0x9d554d95, &bFlag);
            if (ok && bFlag)
                vc<void>(it, 0x1c, bMute, 0, 0, 1);
            u8* nxt = *(u8**)(it + 0x10);
            it = nxt ? nxt - 0x10 : 0;
        }

        void* container = vc<void*>(this, 0x17c, (u32)0xf1cc1687);
        if (container) {
            mbMuted = bMute;
            void* vcp = (u8*)container + 0x10;
            void* plugin = ((VoiceContainer*)vcp)->FindPlugin(0x47614630);
            if (plugin) {
                float f1 = bMute ? 0.0f : g_1485720;
                float f2 = bParam ? 0.0f : s400;
                u32 d = 0;
                if (g_16e61a8)
                    sub_112c600();
                int stackStuff = 0;
                sub_112ccc0((int)bMute, &stackStuff);
                (void)f1; (void)f2; (void)d;
            } else {
                void* plugin2 = ((VoiceContainer*)vcp)->FindPlugin(0x44616330);
                if (plugin2) {
                    if (g_16e61a8)
                        sub_112c600();
                    sub_112ccc0(bMute ? 5 : 3, 0);
                }
            }
            if (g_16e61a8)
                sub_112c620();
        }
    }
}

// @ 0x00a23830
EInsertRes* EHTable::DoInsertKey(EInsertRes* out, const int* pkey, u32 unused)
{
    (void)unused;
    int key = *pkey;
    u32 bucket = (u32)key % mnBucketCount;
    EHNode** pb = &mpBuckets[bucket];
    EHNode* p = *pb;
    while (p) {
        if (p->key == key) {
            out->node = p;
            out->bucket = pb;
            out->inserted = false;
            return out;
        }
        p = p->next;
    }
    ERehashInfo ri;
    mAllocator->RehashRequired(&ri, mnBucketCount, mnElementCount, 1);
    EHNode* n = (EHNode*)operator new(0x0c, "EASTL", 0, 0, EA_FILE, 0xd1);
    if (n) {
        n->key = *(int*)((char*)pkey);
        void* v = *(void**)((char*)pkey + 4);
        n->value = v;
        if (v)
            *(int*)((char*)v + 4) += 1;
    }
    n->next = 0;
    if (ri.bNeed) {
        bucket = (u32)key % ri.nNew;
        DoRehash(ri.nNew);
    }
    n->next = mpBuckets[bucket];
    mpBuckets[bucket] = n;
    mnElementCount += 1;
    out->node = n;
    out->bucket = &mpBuckets[bucket];
    out->inserted = true;
    return out;
}

// @ 0x00a23920
RefVec::~RefVec()
{
    RefCounted** end = mpEnd;
    RefCounted** it = mpBegin;
    for (; it < end; ++it) {
        RefCounted* p = *it;
        if (p)
            p->Release();
    }
}

inline RefVecStorage::~RefVecStorage()
{
    RefCounted** begin = mpBegin;
    if (begin) {
        if (*(int*)((char*)begin - 4) != 0)
            f_00f47380(begin);
    }
}

// @ 0x00a23d20
int PHTable::Erase(const int* pkey)
{
    int oldCount = (int)mnElementCount;
    u32 bucket = (u32)*pkey % mnBucketCount;
    PHNode** pb = &mpBuckets[bucket];
    if (*pb) {
        PHNode* p;
        do {
            p = *pb;
            if (*pkey == p->key)
                break;
            pb = &p->next;
        } while (p->next);
        while (*pb) {
            p = *pb;
            if (*pkey != p->key)
                break;
            *pb = p->next;
            if (p != (PHNode*)mpInline) {
                if ((void*)p < mpPoolBegin || (void*)p >= mpPoolEnd) {
                    operator_delete__(p);
                } else {
                    p->key = (int)mpFreeList;
                    mpFreeList = p;
                }
            }
            mnElementCount -= 1;
        }
    }
    return oldCount - (int)mnElementCount;
}

// @ 0x00a23db0
PHNode** PHTable::EraseNode(PHNode** out, PHNode* n, PHNode** pb)
{
    PHNode* nxt = (PHNode*)out[1];
    out[1] = (PHNode*)pb;
    *out = nxt;
    while (nxt == 0) {
        out[1] = (PHNode*)((char*)out[1] + 4);
        nxt = *(PHNode**)out[1];
        *out = nxt;
    }
    PHNode* head = *pb;
    if (head == n) {
        *pb = head->next;
    } else {
        for (PHNode* q = head->next; q != n; q = q->next)
            head = q;
        head->next = n->next;
    }
    if (n != (PHNode*)mpInline) {
        if ((void*)n >= mpPoolBegin && (void*)n < mpPoolEnd) {
            n->key = (int)mpFreeList;
            mpFreeList = n;
            mnElementCount -= 1;
            return out;
        }
        operator_delete__(n);
    }
    mnElementCount -= 1;
    return out;
}

// @ 0x00a24210
void ElemList::Assign(void* pCompare)
{
    if (Snd_s00a2_3360::ToNode(Snd_s00a2_3360::FromNode(anchor.next)) == &anchor)
        return;                                      // empty list
    Snd_s00a2_3360* first = Snd_s00a2_3360::FromNode(anchor.next);
    if (first == Snd_s00a2_3360::FromNode(anchor.prev))
        return;                                      // single element

    ElemList a, b;

    // Middle walk: `mid` advances from the front while `end` retreats from the
    // anchor, so [first, mid) holds ceil(n/2) elements and [mid, end) the rest.
    Snd_s00a2_3360* mid = first;
    Snd_s00a2_3360* end = Snd_s00a2_3360::FromNode(&anchor);
    while (mid != end) {
        mid = Snd_s00a2_3360::FromNode(mid->node.next);
        if (mid == end)
            break;
        end = Snd_s00a2_3360::FromNode(end->node.prev);
    }

    b.splice(b.begin(), *this, first, mid);          // b = first half
    a.spliceAll(a.begin(), *this);                   // a = second half
    b.Assign(pCompare);
    a.Assign(pCompare);
    this->spliceAll(this->begin(), b);               // this = sorted first half
    this->merge(a, (CompareFn)pCompare);             // + the sorted second half
}

// @ 0x00a243e0
void* RBTree::AllocNode2(const void* src)
{
    struct Node20 { u32 d[5]; };
    Node20* n;
    if (mpFreeList) {
        n = (Node20*)mpFreeList;
        mpFreeList = (void*)n->d[0];
    } else {
        n = (Node20*)operator new(mAllocator, "EASTL", 0, 0, EA_FILE, 0xd1);
    }
    if (n) {
        const u32* s = (const u32*)src;
        n->d[0] = s[0];
        n->d[1] = s[1];
        n->d[2] = s[2];
        void* v = (void*)s[3];
        n->d[3] = (u32)v;
        if (v)
            vc<void>((char*)v + 4, 0);
    }
    n->d[4] = 0;
    return n;
}

// @ 0x00a24480
void PHTable::FreeBuckets(PHNode** buckets, u32 count)
{
    struct FNode { u32 freeLink; void* value; FNode* next; };
    for (u32 i = 0; i < count; ++i) {
        FNode* c;
        FNode* n = (FNode*)buckets[i];
        while (n) {
            c = n;
            n = c->next;
            void* val = c->value;
            if (val)
                vc<void>(val, 4);
            if (c != (FNode*)mpInline) {
                if ((void*)c < mpPoolBegin || (void*)c >= mpPoolEnd) {
                    operator_delete__(c);
                } else {
                    c->freeLink = (u32)mpFreeList;
                    mpFreeList = (PHNode*)c;
                }
            }
        }
        buckets[i] = 0;
    }
}

// @ 0x00a24530
RBNode_s00a2_3360* __thiscall RBTree::CloneNode(RBNode_s00a2_3360* src, RBNode_s00a2_3360* parent)
{
    RBNode_s00a2_3360* dst = RB_AllocNode(src, parent);
    if (src->left)
        dst->left = CloneNode(src->left, dst);
    RBNode_s00a2_3360* r = src->right;
    if (r) {
        RBNode_s00a2_3360* prev = dst;
        do {
            RBNode_s00a2_3360* n = (RBNode_s00a2_3360*)operator new(0x18, "EASTL", 0, 0, EA_FILE, 0xd1);
            if ((char*)n + 0x10) {
                n->key0 = r->key0;
                n->key1 = r->key1;
            }
            n->left = 0;
            n->right = 0;
            n->parent = prev;
            n->color = r->color;
            prev->right = n;
            if (r->left)
                n->left = CloneNode(r->left, n);
            r = r->right;
            prev = n;
        } while (r);
    }
    return dst;
}

// @ 0x00a245e0
__declspec(noinline) RBNode_s00a2_3360* __stdcall RB_AllocNode(const RBNode_s00a2_3360* src, RBNode_s00a2_3360* parent)
{
    RBNode_s00a2_3360* n = (RBNode_s00a2_3360*)operator new(0x18, "EASTL", 0, 0, EA_FILE, 0xd1);
    u32* kv = (u32*)((char*)n + 0x10);
    if (kv) {
        kv[0] = src->key0;
        kv[1] = src->key1;
    }
    n->left = 0;
    n->right = 0;
    n->parent = parent;
    n->color = src->color;
    return n;
}

struct RefIface_a24750 { virtual void AddRef(); virtual void Release(); };
// Uninitialized copy of Elem20 ranges (0x00a24750), EASTL style: iterator objects and a placement copy per element.
struct E20_a24750_Ref {
    RefIface_a24750* p;
    E20_a24750_Ref(const E20_a24750_Ref& o) : p(o.p) { if (p) p->AddRef(); }
};
struct E20_a24750_Elem {
    uint32_t d0, d1, d2, d3;
    E20_a24750_Ref ref;   // +0x10
    static void* operator new(size_t, void* q) throw() { return q; }
    static void operator delete(void*, void*) throw() {}
};
struct E20_a24750_It {
    E20_a24750_Elem* p;
    E20_a24750_It(E20_a24750_Elem* q) : p(q) {}
    E20_a24750_Elem& operator*() const { return *p; }
    E20_a24750_It& operator++() { ++p; return *this; }
    bool operator!=(const E20_a24750_It& o) const { return p != o.p; }
};

// @ 0x00a24750
E20_a24750_It E20_a24750_UninitCopy(E20_a24750_It first, E20_a24750_It last, E20_a24750_It dest)
{
    E20_a24750_It result(dest);
    for (; first != last; ++first, ++result)
        new (&*result) E20_a24750_Elem(*first);
    return result;
}

// @ 0x00a247f0
RDDCtorView::RDDCtorView() : RDDDriverBase("resman:")
{
}

// @ 0x00a24850
u32 __cdecl ParseResman(const char* param_1, u8* param_2)
{
    if (_strnicmp(param_1, "resman:", 7) == 0)
        param_1 = param_1 + 7;
    char c = *param_1;
    while (c != 0) {
        char hi = param_1[1];
        param_1 = param_1 + 1;
        hi = (char)(hi - 0x41);
        c = (char)(c - 0x41);
        *param_2 = (u8)((hi << 4) | c);
        param_1 = param_1 + 1;
        c = *param_1;
        param_2 = param_2 + 1;
    }
    return 1;
}

// @ 0x00a248a0
ProfileTimer::ProfileTimer(void* acc)
{
    sw.ctor(4, 0);
    mpAccumulator = acc;
    if (sw.mnUnits == 1) {
        unsigned long long t = __rdtsc();
        *(unsigned int*)&sw.mnStartTime = (unsigned int)t;
        *(unsigned int*)((char*)&sw.mnStartTime + 4) = (unsigned int)(t >> 32);
    } else {
        long long c;
        QueryPerformanceCounter(&c);
        *(unsigned int*)&sw.mnStartTime = ((unsigned int*)&c)[0];
        *(unsigned int*)((char*)&sw.mnStartTime + 4) = ((unsigned int*)&c)[1];
    }
    *(unsigned int*)&sw.mnTotalElapsedTime = 0;
    *(unsigned int*)((char*)&sw.mnTotalElapsedTime + 4) = 0;
}

// @ 0x00a24900
void ProfileTimer::Accumulate()
{
    long long elapsed = sw.GetElapsedTimeFloat();
    float time = (float)elapsed * sw.mfCyclesToUnitsCoefficient;
    _ReadWriteBarrier();
    float* accumulator = (float*)mpAccumulator;
    *accumulator += time;
}

// @ 0x00a24930
bool __thiscall RDD::Tick3(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
    ProfileTimer local((void*)((char*)this + 0x5c));
    long long e = local.sw.GetElapsedTimeFloat();
    float* acc = (float*)local.mpAccumulator;
    *acc = (float)e * local.sw.mfCyclesToUnitsCoefficient + *acc;
    return false;
}

// @ 0x00a24970
void* __thiscall RDD::FindById(void* id)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    MutexGuard_s00a2_3360 guard(&mMutex, g_lockName);
    mfAccum = (float)timer.sw.GetElapsedTimeFloat() * timer.sw.mfCyclesToUnitsCoefficient + mfAccum;
    void** it = mpBegin;
    void** end = mpEnd;
    void* r;
    for (;;) {
        if (it == end)
            return 0;
        r = *it;
        if (id == r)
            break;
        ++it;
    }
    return r;
}

// @ 0x00a24a90
void* __thiscall RDD::FindAndCall1(void* id, void* a, void* b, void* c, void* d)
{
    (void)c; (void)d;
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    if (p != 0 && vc<void*>(p, 0x18) != 0)
        p = vc<void*>(vc<void*>(p, 0x18), 0x30, a, b);
    else
        p = 0;
    return p;
}

// @ 0x00a24b40
int __thiscall RDD::FindAndCall2(void* id, void* a, void* b, void* c, void* d)
{
    (void)c; (void)d;
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    int r;
    if (p != 0 && vc<void*>(p, 0x18) != 0)
        r = vc<bool>(vc<void*>(p, 0x18), 0x38, a, b);
    else
        r = 0;
    return r;
}

// @ 0x00a24bf0
long long __thiscall RDD::FindAndCall3(void* id, void* a, void* b, void* c, void* d, void* e)
{
    (void)b; (void)d; (void)e;
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    return (p != 0 && vc<void*>(p, 0x18) != 0)
        ? vc<bool>(vc<void*>(p, 0x18), 0x28, a, c) : 0;
}

// @ 0x00a24cb0
void* __thiscall RDD::FindAndCall4(void* id)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    void* r = 0;
    if (p) {
        void* q = vc<void*>(p, 0x18);
        if (q)
            r = vc<void*>(q, 0x1c);
    }
    return r;
}

// @ 0x00a24d60
long long __thiscall RDD::FindAndCall5(void* id)
{
    ScopedTimer timer((float*)((char*)this + 0x5c));
    void* p = FindById(id);
    int r = 0;
    if (p) {
        void* q = vc<void*>(p, 0x18);
        if (q)
            r = vc<int>(q, 0x24, 0);
    }
    return (long long)r;
}

// @ 0x00a24e10
void Tracker::Remove(TObj* o)
{
    ScopedTimer_s00a2_4e10 timer((float*)((char*)this + 0x5c));
    MutexGuard guard(&mMutex, g_lockName);
    mElapsed = (float)timer.sw.GetElapsedTimeFloat() * timer.sw.coeff + mElapsed;
    TObj** it = mBegin;
    for (; it != mEnd; ++it) {
        if (o == *it) {
            TObj* old = *it;
            TObj* nw = mEnd[-1];
            if (nw != old) {
                if (nw) nw->AddRef();
                *it = nw;
                if (old) old->Release();
            }
            mEnd -= 1;
            TObj* last = *mEnd;
            if (last) last->Release();
            return;
        }
    }
}

// @ 0x00a24f50
void Tracker::Process(TObj* o)
{
    ScopedTimer_s00a2_4e10 timer((float*)((char*)this + 0x5c));
    TObj* f = Find(o);
    if (f) {
        ((void (__thiscall*)(TObj*))(*(void***)f)[9])(f);
        Remove(o);
    }
}

// @ 0x00a25000
void RcMap::Release(unsigned key)
{
    RbIter it = mTree.find(key);
    int* node = it.n;
    if ((int*)((char*)this + 8) != node) {
        if ((*(volatile int*)&node[5] += -1) == 0) {
            mTree.size += -1;
            RBTreeIncrement(node);
            RBTreeErase(node, (char*)&mTree + 4);
            operator_delete__(node); // 0x00f47380
        }
    }
}

// @ 0x00a25090
bool Factory::MakeProps(const char* a, Obj_s00a2_4e10** out, int c, int d)
{
    bool ok = false;
    if (out != 0 && a != 0) {
        void* m = operator new(0x2c, "audio", 0, 0, 0, 0);
        PropList* pl = m ? new (m) PropList() : 0;
        ARC ref(pl);
        if (Create(a, pl, c, d)) {
            pl->AddRef();
            *out = pl;
            ok = true;
        }
    }
    return ok;
}

// @ 0x00a25190
bool Factory::MakeAudio(const char* a, ARC* out, int c, int id)
{
    bool ok = false;
    if (out != 0 && a != 0) {
        ARC tmp;
        switch (id) {
        case 0x1a527db: {
            void* m = operator new(0x30, "Audio", 0, 0, 0, 0);
            tmp.assign(m ? ((Obj30*)m)->Init() : 0);
            break;
        }
        case 0x42c9cbb: {
            void* m = operator new(0x30, "Audio", 0, 0, 0, 0);
            tmp.assign(m ? ((Obj30b*)m)->Init() : 0);
            break;
        }
        }
        Obj_s00a2_4e10* o = tmp.p;
        if (o && Create(a, o, c, id)) {
            o->AddRef();
            out->p = o;
            ok = true;
        }
    }
    return ok;
}

// @ 0x00a252b0
bool System_s00a2_4e10::Init()
{
    if (mbInitialized) return false;
    mbInitialized = true;
    g_tid1 = GetThreadId();
    MutexGuard guard(&mMutex, g_lockName);
    g_tid2 = GetThreadId();
    if (g_pSystem) ((IHandlerRC*)g_pSystem)->Release();
    IHandlerRC* h = (IHandlerRC*)((unsigned)this + 4);
    g_pSystem = this;
    h->AddRef();

    mpCharMap = new ("Audio/Char8Map", 0, 0, 0, 0) CharMap(0x20000, 0x134, 0, 1, 0);

    ErrIf* err = GetObjectError();
    if (err) {
        DbgObj* d = new ("Audio", 0, 0, 0, 0) DbgObj();
        err->Set(1, d, 0);
        ARC pObj;
        if (!err->Query(g_iidErr, &pObj, 0, 0, 0, 0) || pObj.p == 0) {
            return false;
        }
        mpConfiguration.assign((Obj_s00a2_4e10*)((char*)pObj.p + 0x14));
    }

    q214.Init(5000);
    q264.Init(5000);
    q304.Init(5000);
    q354.Init(5000);

    Server* srv = GetMessagingServer();
    mpServer = srv;
    mpHandler = h;
    mpIdArray = g_msgIds;
    mnIdArrayCount = 7;
    mnPriority = 0;
    if (srv && h) {
        for (unsigned i = 0; i < 0x1c; i += 4) {
            srv->Register(h, *(const unsigned*)((const char*)g_msgIds + i));
        }
    }

    ThreadParams tp;
    tp.name = "AudioSystem";
    int prio = 0;
    ((Config*)mpConfiguration.p)->Get(0x90a770d, &prio);
    tp.priority = prio;
    mbExitThread = false;
    mStarted = 0;
    Cond* cond = &mCondInit;
    unsigned aff = GetDefaultAffinity();
    mTickThread.Begin((void*)TickProc, cond, &tp, aff);
    while (mStarted == 0) {
        if (cond->Wait(&mMutex, g_lockName) != 0) break;
    }
    bool ok = (mStarted == 1);

    for (unsigned i = 1001; i <= 2000; i += 5) {
        mExternalIdsPool.Push(i);
        mExternalIdsPool.Push(i + 1);
        mExternalIdsPool.Push(i + 2);
        mExternalIdsPool.Push(i + 3);
        mExternalIdsPool.Push(i + 4);
    }
    for (unsigned i = 1; i <= 1000; i += 5) {
        mAllocatedIdsPool.Push(i);
        mAllocatedIdsPool.Push(i + 1);
        mAllocatedIdsPool.Push(i + 2);
        mAllocatedIdsPool.Push(i + 3);
        mAllocatedIdsPool.Push(i + 4);
    }

    if (!ok) {
        if (g_pSystem) ((IHandlerRC*)g_pSystem)->Release();
        g_pSystem = 0;
    }
    return ok;
}

// @ 0x00a25980
void Namer::Convert(const char* s, int a, int b, double c)
{
    StrOut out = { 0, 0, 0 };
    g_pfnString(&out, (int)ConvertToString16(s, -1).c_str(), 0, 0, 0, 0); // 0x0154c464
    Dispatch((wchar_t*)out.a, a, b, c);
}

// @ 0x00a25a40
bool AudioSys::CallPrim(unsigned id, int a, float b, int c)
{
    PIter it = mPrims.find(id);
    if (it.node == mPrims.end()) {
        return false;
    }
    it.node->val->Update(a, b, c);
    return true;
}

// @ 0x00a25aa0
void AudioSys::CallAll(int a, float b, int c)
{
    PIt it(*mPrims.mBuckets, mPrims.mBuckets);
    if (it.node == 0) it.IncrBucket();
    PIt end(mPrims.end(), 0);
    while (it.node != end.node) {
        it.node->val->Update(a, b, c);
        it.Incr();
    }
}

// @ 0x00a25b20
bool AudioSys::HasPrim(unsigned id)
{
    PNode* end = mPrims.end();
    return mPrims.find(id).node != end;
}

// @ 0x00a25b60
void AudioSys::UpdateOutput()
{
    SubIt it(*mSubs.mBuckets, mSubs.mBuckets);
    if (it.node == 0) it.IncrBucket();
    SubNode* end = mSubs.end();
    if (it.node != end) {
        do {
            ((Subscription_s00a2_4e10*)((char*)it.node + 4))->UpdateOutput(mOutputs);
            it.Incr();
        } while (it.node != end);
    }
}

// @ 0x00a25bd0
bool AudioSys::GetFloat(unsigned k1, unsigned k2, float* out)
{
    GIter it;
    mNested.find(&it, k1);
    NNode* node = (NNode*)it.node;
    if (node != mNested.end()) {
        node->inner.find(&it, k2);
        if ((FNode*)it.node != node->inner.end()) {
            *out = ((FNode*)it.node)->val;
            return true;
        }
    }
    return false;
}

// @ 0x00a25c40
void AudioSystem_s00a2_5c40::Update(float dt)
{
    if (mQueue_304.FUN_00a0f980() && mbX_3f5) {
        ((Mutex_s00a2_5c40*)mMutex)->Lock(0x1452970);
        mbX_3f5 = 0;
        mQueue_304.FUN_00a0fee0(&mQueue_354);
        ((Mutex_s00a2_5c40*)mMutex)->Unlock();
        mQueue_304.FUN_00a0fdc0();
    }
    if (!mQueue_304.FUN_00a0f980()) {
        uint limit = *(uint*)&mpX_208;   // stopwatch time limit source
        (void)limit;
        // the original builds a scoped EA::LimitStopwatch here; the observable
        // behaviour is the loop below.
        uint it = 0;
        for (;;) {
            ++it;
            if ((it & 3) == 0) {
                // timing poll (no observable result beyond loop control)
            }
            if (!mQueue_304.FUN_00a0f9a0()) break;
            void* vt = mpVtbl;
            void* arg = (void*)&mRing_1366d4;   // placeholder for the queue token
            (void)arg;
            ((void(__thiscall*)(void*, void*))((void**)(*(void**)vt))[0x12c / 4])(this, arg);
        }
        if (mQueue_304.FUN_00a0f990() == 0)
            mQueue_304.FUN_00a0fdd0();
    }
    ++mX_15b6b4;
    if (!mQueue_214.FUN_00a0f980() && !mbX_3f4) {
        uint it[2] = {0, 0};
        uint key = (uint)(size_t)this;
        mMap_13f4.find(it, &key);
        (void)it;
        ((Mutex_s00a2_5c40*)mMutex)->Lock(0x1452970);
        mbX_3f4 = 1;
        mQueue_264.FUN_00a0fee0(&mQueue_214);
        ((Mutex_s00a2_5c40*)mMutex)->Unlock();
    }
}

// @ 0x00a25ed0
void AudioSystem_s00a2_5c40::RemoveFromList(void* item)
{
    if (!item) return;
    void* header = mList_157c60;                 // intrusive list header
    for (void* cur = header; cur != mList_157c60; cur = *(void**)cur) {
        void* node = *(void**)((uchar*)cur + 8);
        if (node) ((void(__thiscall*)(void*))vc_s00a2_5c40(node, 0))(node);
        if (node == item) {
            if (mpX_158f48 == cur) mpX_158f48 = *(void**)mpX_158f48;
            void* n = *(void**)((uchar*)*(void**)cur + 4);
            // unlink
            void* a = *(void**)n;
            *(void**)((uchar*)n + 4 ? 0 : 0) = 0; (void)a;
            ((void(__thiscall*)(void*))vc_s00a2_5c40(item, 4))(item);
            return;
        }
        if (node) ((void(__thiscall*)(void*))vc_s00a2_5c40(node, 4))(node);
    }
}

// @ 0x00a25ff0
bool AudioSystem_s00a2_5c40::Lookup_25ff0(uint key, uint* out)
{
    uint it[2];
    mMap_33d4.find(it, &key);
    if (mMap_33d4.NotFound((void*)(size_t)it[0])) return false;
    *out = *(uint*)((uchar*)(size_t)it[0] + 4);
    return true;
}

// @ 0x00a26040
uint AudioSystem_s00a2_5c40::RemovePrimitiveFromUpdate(void* p)
{
    struct Str {
        char* begin; char* end; char* cap; int mAlloc;
        ~Str() { if ((cap - begin) > 1 && begin) operator_delete(begin); }
    };
    Str s;
    ConvertToString8Impl(&s, (const wchar_t*)p, 0xffffffff);
    uint id = ((uint(__thiscall*)(void*, char*))vc_s00a2_5c40(this, 0xf4))(this, s.begin);
    return id;
}

// @ 0x00a260c0
uint AudioSystem_s00a2_5c40::Lookup_260c0(uint key)
{
    uint it[2];
    mMap_11a3d8.find(it, &key);
    if (mMap_11a3d8.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// @ 0x00a26100
struct IHandler_26100 {
    virtual void AddRef();
    virtual void Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool Handle(uint arg);             // +0x2c
};
struct HIter_26100 {
    void*  mpNode;
    void** mpBucket;
    HIter_26100(void** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
};
struct HandlerRef_26100 {
    IHandler_26100* mpObject;
    HandlerRef_26100() : mpObject(0) {}
    ~HandlerRef_26100() { if (mpObject) mpObject->Release(); }
};
bool AudioSystem_s00a2_5c40::Map_26100(uint key, uint arg)
{
    HandlerRef_26100 hold;
    HTable& map = mMap_119bb8;
    struct { void* mpNode; void** mpBucket; } it;
    map.find(&it, &key);
    HIter_26100 end(map.mpBucketArray + map.mnBucketCount);
    if (it.mpNode == end.mpNode) return false;
    IHandler_26100* obj = *(IHandler_26100**)((uchar*)it.mpNode + 4);
    if (obj) { obj->AddRef(); hold.mpObject = obj; }
    if (!hold.mpObject->Handle(arg))
        return false;
    return true;
}

// eastl::hashtable_iterator over the node chain (next at +8)
struct HIt_a261c0 {
    void*  mpNode;
    void** mpBucket;
    HIt_a261c0(void** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    static HIt_a261c0 Begin(const HTable& t) {
        HIt_a261c0 i(t.mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    static HIt_a261c0 End(const HTable& t) { return HIt_a261c0(t.mpBucketArray + t.mnBucketCount); }
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment() {
        mpNode = *(void**)((uchar*)mpNode + 8);
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
// @ 0x00a261c0
void AudioSystem_s00a2_5c40::Map_261c0(uint arg)
{
    for (HIt_a261c0 it = HIt_a261c0::Begin(mMap_119bb8), itEnd = HIt_a261c0::End(mMap_119bb8);
         it.mpNode != itEnd.mpNode; it.increment()) {
        void* obj = *(void**)((uchar*)it.mpNode + 4);
        ((void(__thiscall*)(void*, uint))vc_s00a2_5c40(obj, 0x2c))(obj, arg);
    }
}

// @ 0x00a26230
struct IBroadcast_26230 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void Notify(uint a, uint b);       // +0x30
};
struct HNode_26230 { uint key; IBroadcast_26230* value; HNode_26230* next; };
struct HIter_26230 {
    HNode_26230*  mpNode;
    HNode_26230** mpBucket;
    HIter_26230(HNode_26230** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {
        if (!mpNode) {
            ++mpBucket;
            while (*mpBucket == 0) ++mpBucket;
            mpNode = *mpBucket;
        }
    }
    HIter_26230(HNode_26230* node, HNode_26230** pBucket) : mpNode(node), mpBucket(pBucket) {}
    void increment() {
        mpNode = mpNode->next;
        while (mpNode == 0) mpNode = *++mpBucket;
    }
};
void AudioSystem_s00a2_5c40::Map_26230(uint a, uint b)
{
    HIter_26230 it((HNode_26230**)mMap_119bb8.mpBucketArray);
    HIter_26230 end(((HNode_26230**)mMap_119bb8.mpBucketArray)[mMap_119bb8.mnBucketCount],
                    (HNode_26230**)mMap_119bb8.mpBucketArray + mMap_119bb8.mnBucketCount);
    for (; it.mpNode != end.mpNode; it.increment())
        it.mpNode->value->Notify(a, b);
}

// @ 0x00a262a0
bool AudioSystem_s00a2_5c40::Map_262a0(uint key, uint arg)
{
    uint it[2];
    bool result = false;
    mMap_404.find(it, &arg);
    uint node = it[0];
    if (mMap_404.End() != (void*)(size_t)node) {
        uint val = *(uint*)((uchar*)(size_t)node + 4);
        result = ((bool(__thiscall*)(void*, uint, uint))vc_s00a2_5c40(this, 0x108))(this, key, val);
    }
    return result;
}

// @ 0x00a26300
bool AudioSystem_s00a2_5c40::Map_26300(uint key, uint arg)
{
    uint it[2];
    bool result = false;
    mMap_404.find(it, &arg);
    uint node = it[0];
    if (mMap_404.End() != (void*)(size_t)node) {
        uint val = *(uint*)((uchar*)(size_t)node + 4);
        result = ((bool(__thiscall*)(void*, uint, uint))vc_s00a2_5c40(this, 0x110))(this, key, val);
    }
    return result;
}

// @ 0x00a26360
uint AudioSystem_s00a2_5c40::Lookup_26360(uint key)
{
    uint it[2];
    mMap_119bb8.find(it, &key);
    if (mMap_119bb8.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// @ 0x00a263a0
bool AudioSystem_s00a2_5c40::Map_263a0(uint key, void** out)
{
    uint it[2];
    mMap_118a78.find(it, &key);
    uint node = it[0];
    if (mMap_118a78.End() == (void*)(size_t)node) return false;
    void* fp = *(void**)((uchar*)(size_t)node + 4);
    RefObj* obj = (RefObj*)((void* (__fastcall*)(void*))fp)(fp);
    if (obj) {
        AutoRefCount<RefObj> ref(obj);
        obj->AddRef();
        *out = obj;
    }
    return true;
}

// @ 0x00a26450
void AudioSystem_s00a2_5c40::UpdateSoundStates()
{
    ((void(__thiscall*)(void*))vc_s00a2_5c40(this, 0x140))(this);
    mTree_157438.AssignLess2((void*)0xa20eb0);
    void* raw = mTree_157438.mpRoot;
    void* first = raw ? (uchar*)raw - 0x10 : 0;
    void* end = ((uchar*)&mTree_157438) - 0x10;
    while (first != end) {
        void* snd = first;
        if (!((bool(__thiscall*)(void*, int))vc_s00a2_5c40(this, 0x14c))(this, 1)) {
            if (FUN_00ef6410()) {
                if (!((bool(__thiscall*)(void*, int, int))vc_s00a2_5c40(snd, 0x20))(snd, 3, 0))
                    ((void(__thiscall*)(void*, int, int, float, int))vc_s00a2_5c40(snd, 0x1c))(snd, 1, 3, 1.0f, 1);
            } else {
                ((void(__thiscall*)(void*, int, int))vc_s00a2_5c40(snd, 0x80))(snd, 3, 1);
            }
        } else {
            if (((bool(__thiscall*)(void*, int, int))vc_s00a2_5c40(snd, 0x20))(snd, 3, 0))
                ((void(__thiscall*)(void*, int, int, float, int))vc_s00a2_5c40(snd, 0x1c))(snd, 0, 3, 1.0f, 1);
        }
        void* nxt = *(void**)((uchar*)snd + 0x10);
        first = nxt ? (uchar*)nxt - 0x10 : 0;
    }
}

// @ 0x00a26530
void AudioSystem_s00a2_5c40::Map_26530()
{
    mMap_118bb0.DoFreeNodes(mMap_118bb0.mpBucketArray, (void*)(size_t)mMap_118bb0.mnBucketCount);
    mMap_118bb0.mnElementCount = 0;
    mX_15b6b8 = 0;
    mX_15b6bc = 0;
}

// @ 0x00a26570
uint AudioSystem_s00a2_5c40::Lookup_26570(uint key)
{
    uint it[2];
    mMap_157440.find(it, &key);
    if (mMap_157440.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// @ 0x00a265b0
uint AudioSystem_s00a2_5c40::Lookup_265b0(uint key)
{
    uint it[2];
    mMap_404.find(it, &key);
    if (mMap_404.NotFound((void*)(size_t)it[0])) return 0;
    return *(uint*)((uchar*)(size_t)it[0] + 4);
}

// @ 0x00a265f0
void AudioSystem_s00a2_5c40::Map_265f0(float a, uint b)
{
    if (mbX_9b) return;
    void** ba = mMap_158f54.mpBucketArray;
    mbX_9b = 1;
    void* cur = *ba;
    if (!cur) {
        void** p = ba;
        do { ++p; cur = *p; } while (!cur);
    }
    void* end = ba[mMap_158f54.mnBucketCount];
    while (cur != end) {
        void* obj = *(void**)((uchar*)cur + 4);
        ((void(__thiscall*)(void*, float, uint))vc_s00a2_5c40(obj, 0x28))(obj, a, b);
        cur = *(void**)((uchar*)cur + 8);
        while (!cur) {
            ++ba;
            cur = *ba;
        }
    }
}

// @ 0x00a26680
bool AudioSystem_s00a2_5c40::Map_26680(uint key, void** out)
{
    if (!out) return false;
    uint it[2];
    mMap_13f4.find(it, &key);
    void* node = (void*)(size_t)it[0];
    if (mMap_13f4.NotFound(node)) return false;
    void* obj = *(void**)((uchar*)node + 4);
    ((void(__thiscall*)(void*))vc_s00a2_5c40(obj, 0))(obj);
    *out = obj;
    return true;
}

// @ 0x00a266e0
bool AudioSystem_s00a2_5c40::Map_266e0(uint key, float f)
{
    uint it[2];
    mMap_23e4.find(it, &key);
    void* node = (void*)(size_t)it[0];
    if (mMap_23e4.NotFound(node)) return false;
    uint* obj = *(uint**)((uchar*)node + 4);
    ((MapValue_s00a2_5c40*)obj)->FUN_00a16fd0(f);
    return true;
}

// @ 0x00a26730
bool AudioSystem_s00a2_5c40::Map_26730(uint key, void** out)
{
    if (!out) return false;
    uint it[2];
    mMap_23e4.find(it, &key);
    void* node = (void*)(size_t)it[0];
    if (mMap_23e4.NotFound(node)) return false;
    void* obj = *(void**)((uchar*)node + 4);
    ((void(__thiscall*)(void*))vc_s00a2_5c40(obj, 0))(obj);
    *out = obj;
    return true;
}

// @ 0x00a26790
bool AudioSystem_s00a2_5c40::Map_26790(uint arg)
{
    void* end = mMap_128ae0.End();
    uint it[2];
    uint* p = mMap_128ae0.find2(it, &arg);
    return *(void**)p != end;
}

// @ 0x00a267d0
void AudioSystem_s00a2_5c40::Map_267d0(uint id)
{
    if (id - 1 > 999) return;
    uint it[2] = {0, 0};
    mMap_132808.find2(it, &id);
    void* node = (void*)(size_t)it[0];
    if (mMap_132808.NotFound(node)) return;
    void* bucket = (void*)(size_t)it[1];
    mMap_132808.EraseNode((void**)it, node, bucket);
    void* end = mMap_128ae0.End();
    uint it2[2] = {0, 0};
    uint* p = mMap_128ae0.find2(it2, &id);
    if (*(void**)p == end) FUN_00a21d30(mRing_1366d4, &id);
}

// @ 0x00a26860
TreeOwner_00a26860::~TreeOwner_00a26860()
{
}

// @ 0x00a268b0
void AudioSystem_s00a2_5c40::Shutdown_268b0()
{
    Func_68fb70(mProfHash_13795c.mp0, mProfHash_13795c.mpBucketArray);
    mProfHash_13795c.mpPool = 0;
    ++mX_15b6b0;
    mbX_9b = 0;
    if (!mbX_3f5) {
        ((void(__thiscall*)(void*))vc_s00a2_5c40(this, 0x1e0))(this);
        if (!mQueue_3a4.FUN_00a0f980()) {
            if (DAT_0166d9f4)
                ((void(__thiscall*)(void*))vc_s00a2_5c40(DAT_0166d9f4, 0xc0))(DAT_0166d9f4);
            mQueue_3a4.FUN_00a0fee0(&mQueue_354);
            mbX_3f5 = 1;
            if (DAT_0166d9f4)
                ((void(__thiscall*)(void*))vc_s00a2_5c40(DAT_0166d9f4, 0xc4))(DAT_0166d9f4);
        }
    }
    if (mbX_3fc) {
        mbX_3fc = 0;
        ((void(__thiscall*)(void*))vc_s00a2_5c40(this, 0x6c))(this);
    }
}

// @ 0x00a26990
void* AudioSystem_s00a2_5c40::InitPool_26990()
{
    uchar* base = (uchar*)this;
    fixed_pool_with_overflow tmp(base + 0x1c, 0x12c0, 0xc, 4);
    void* mem = tmp.mpHead;
    *(void**)base = 0;
    *(void**)(base + 4) = 0;
    fixed_pool_with_overflow* pool = (fixed_pool_with_overflow*)(base + 8);
    pool->mpHead = 0;
    pool->init(mem, 0x12c0, 0xc, 4, 0);
    pool->mpPoolBegin = mem;
    pool->mpCapacity = (uchar*)mem + 0x12c0;
    pool->mnNodeSize = 0xc;
    *(void**)base = base;
    *(void**)(base + 4) = base;
    return this;
}

// @ 0x00a26be0
void AudioSystem_s00a2_5c40::Insert_26be0(void* ret, const uint* key, uint hash)
{
    // `hash` is unused by the original shape; the key value drives the bucket.
    (void)hash;
    uint k = *(uint*)key;
    HTable* t = &mProfHash_13795c;
    uint idx = k % t->mnBucketCount;
    void** bucket = &t->mpBucketArray[idx];
    void* node = *bucket;
    while (node) {
        if (k == *(uint*)node) {
            *(void**)ret = node;
            *(void**)((uchar*)ret + 4) = bucket;
            *(uint8_t*)((uchar*)ret + 8) = 0;
            return;
        }
        node = *(void**)((uchar*)node + 4);
    }
    // allocate a node
    void* n = t->mpFreeList;
    if (n) t->mpFreeList = *(void**)n;
    else n = operator_new(0x1c, kEastlAlloc, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    uint* n32 = (uint*)n;
    if (n) n32[0] = k;
    n32[1] = 0;
    n32[1] = (uint)t->mpBucketArray[idx];
    t->mpBucketArray[idx] = n;
    ++t->mnElementCount;
    *(void**)ret = n;
    *(void**)((uchar*)ret + 4) = &t->mpBucketArray[idx];
    *(uint8_t*)((uchar*)ret + 8) = 1;
}

// Element vector at 0xa26da0: 0x14-byte entries whose ref at +0x10 is released; the fixed storage frees the block
// unless it is the inline pool.
struct RefElem14_a26da0 {
    uchar pad[0x10];
    IUnk_a26da0* mpRef;   // +0x10
    ~RefElem14_a26da0() { IUnk_a26da0* r = mpRef; if (r) r->Release(); }
};
struct RefVecStorage_a26da0 {
    RefElem14_a26da0* mpBegin;   // +0
    RefElem14_a26da0* mpEnd;     // +4
    RefElem14_a26da0* mpCap;     // +8
    uint pad0c;
    void* mpPool;                // +0x10
    ~RefVecStorage_a26da0() { if (mpBegin && mpBegin != mpPool) operator_delete(mpBegin); }
};
struct RefVec_a26da0 : RefVecStorage_a26da0 {
    ~RefVec_a26da0();
};

// @ 0x00a26da0
RefVec_a26da0::~RefVec_a26da0()
{
    RefElem14_a26da0* end = mpEnd;
    for (RefElem14_a26da0* p = mpBegin; p < end; ++p)
        p->~RefElem14_a26da0();
}

// @ 0x00a26e10
InsertRes* KTable::Insert(InsertRes* out, const Key4* k, int)
{
    uint32_t h = k->a ^ k->c;
    uint32_t idx = h % mnBuckets;
    KNode** bucket = &mpBuckets[idx];
    for (KNode* n = mpBuckets[idx]; n; n = n->next) {
        if (k->a == n->key.a && k->b == n->key.b && k->c == n->key.c) {
            out->node = n;
            out->inserted = false;
            out->bucket = bucket;
            return out;
        }
    }
    RehashRes r;
    mPolicy.GetRehashRequired(&r, mnBuckets, mnElements, 1);
    KNode* nn = (KNode*)eaNew(0x14, "EASTL", 0, 0, EASTL_FILE, 0xd1);
    if (nn) {
        nn->key = *k;
    }
    nn->next = 0;
    if (r.bNeed) {
        idx = h % r.nNew;
        DoRehash(r.nNew);
    }
    nn->next = mpBuckets[idx];
    mpBuckets[idx] = nn;
    mnElements++;
    out->node = nn;
    out->inserted = true;
    out->bucket = &mpBuckets[idx];
    return out;
}

// @ 0x00a26f30
void ResTable::DoFreeNodes(ResNode** buckets, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        ResNode* node = buckets[i];
        while (node) {
            ResNode* cur = node;
            node = node->next;
            ReleaseCounted(cur->value);
            operator delete(cur);
        }
        buckets[i] = 0;
    }
}

// Pool node of 0xa27010: the payload (three words and a ref) is copy-constructed in place at node + 0x10.
struct PayloadRef_a27010 {
    RefObj* p;
    PayloadRef_a27010(const PayloadRef_a27010& o) : p(o.p) { if (p) p->AddRef(); }
    ~PayloadRef_a27010();
};
struct PayloadVal_a27010 {
    uint32_t a, b, c;
    PayloadRef_a27010 obj;
    static void* operator new(size_t, void* q) throw() { return q; }
    static void operator delete(void*, void*) throw() {}
};
inline void** NodePoolAlloc_a27010(NodePool* pool)
{
    void** node = pool->mpFree;
    if (node)
        pool->mpFree = (void**)*node;
    else
        node = (void**)eaNew(pool->mnNodeSize, "EASTL", 0, 0, EASTL_FILE, 0xd1);
    return node;
}

// @ 0x00a27010
void* NodePool::Alloc(const Payload* src)
{
    void** node = NodePoolAlloc_a27010(this);
    new (node + 4) PayloadVal_a27010(*(const PayloadVal_a27010*)src);
    return node;
}

// @ 0x00a270b0
PropList_s00a2_6e10::PropList_s00a2_6e10()
{
}

// @ 0x00a27110   scalar deleting destructor of the property list
PropList_s00a2_6e10::~PropList_s00a2_6e10()
{
    // the two fixed vectors free their heap buffers in their own destructors (v2, then v1)
}

struct PropListRef_a27170 {
    PropList_s00a2_6e10* p;
    PropListRef_a27170(PropList_s00a2_6e10* q) : p(q) { if (p) p->AddRef(); }
    ~PropListRef_a27170() { if (p) p->Release(); }
};

// @ 0x00a27170
bool FactoryVoiceTemplate::CreateResource(int key, PropList_s00a2_6e10** out, int a, int b)
{
    bool ok = false;
    if (out != 0 && key != 0) {
        PropListRef_a27170 res(new ("audio", 0, 0, 0, 0) PropList_s00a2_6e10());
        if (InitResource(key, res.p, a, b)) {
            res.p->AddRef();
            *out = res.p;
            ok = true;
        }
    }
    return ok;
}

// @ 0x00a27290
AbilityList::AbilityList()
{}

// @ 0x00a27340
bool StyleMgr::Remove(uint32_t key)
{
    StyleMgr* self = this;
    HIter_s00a2_6e10 it;
    self->mStyles.find(&it, &key);
    HIter_s00a2_6e10 end; end.node = self->mStyles.mpBuckets[self->mStyles.mnBuckets];
    if (it.node != end.node) {
        void* obj = ((StyleNode*)it.node)->value;
        ((VFn1)VSLOT(self, 0x170))(self, obj);
        bool r = ((VFnB)VSLOT(obj, 0x24))(obj);
        self->mStyles.erase(it);
        return r;
    }
    return false;
}

// @ 0x00a273d0
void StyleMgr::RemoveAll()
{
    StyleMgr* self = this;
    void** bucket = self->mStyles.mpBuckets;
    void* node = *bucket;
    if (!node) {
        bucket++;
        node = *bucket;
        while (!node) { bucket++; node = *bucket; }
        node = *bucket;
    }
    void* end = self->mStyles.mpBuckets[self->mStyles.mnBuckets];
    while (node != end) {
        void* obj = ((StyleNode*)node)->value;
        ((VFn1)VSLOT(self, 0x170))(self, obj);
        ((VFnB)VSLOT(obj, 0x24))(obj);
        HIter_s00a2_6e10 it; it.node = node; it.bucket = bucket;
        HIter_s00a2_6e10 nx = self->mStyles.erase(it);
        bucket = nx.bucket;
        node = nx.node;
    }
}

// @ 0x00a27460
void* TexMgr::Find(const void* key)
{
    TexMgr* self = this;
    HIter_s00a2_6e10 it;
    it.node = 0;
    self->mTex.find(&it, key);
    if (it.node != self->mTex.mpBuckets[self->mTex.mnBuckets]) {
        return ((TexNode*)it.node)->value;
    }
    return 0;
}

// @ 0x00a27530
CountedRes** RefMap::FindOrInsert(const uint32_t* key)
{
    MapIter it = find(*key);
    if (it.node != MapIter(mpBuckets + mnBuckets).node)
        return &it.node->value;
    return &Insert(MapValue(*key, RefSlot()), MapTrueType()).first.node->value;
}

// @ 0x00a27660
HIter_s00a2_6e10* ETable::erase(HIter_s00a2_6e10* out, ENode* node, ENode** bucket)
{
    out->bucket = (void**)bucket;
    out->node = node->next;
    while (out->node == 0) {
        out->bucket = (void**)((char*)out->bucket + 4);
        out->node = *(void**)out->bucket;
    }
    ENode* cur = *bucket;
    if (cur == node) {
        *bucket = cur->next;
    } else {
        ENode* nx = cur->next;
        while (nx != node) {
            cur = nx;
            nx = nx->next;
        }
        cur->next = nx->next;
    }
    if (node->value) node->value->Release();
    operator delete(node);
    mnElements--;
    return out;
}

// @ 0x00a276e0
void SubTable::DoFreeNodes(SubNode_s00a2_6e10** buckets, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        SubNode_s00a2_6e10* node = buckets[i];
        while (node) {
            SubNode_s00a2_6e10* cur = node;
            node = node->next;
            if (cur->sub) {
                RefObj* r = (RefObj*)(cur->sub + 4);
                r->Release();
            }
            if (cur != mpInline) {
                if ((char*)cur < mpPoolBegin || (char*)cur >= mpPoolEnd) {
                    operator delete(cur);
                } else {
                    *(SubNode_s00a2_6e10**)cur = mpFreeList;
                    mpFreeList = cur;
                }
            }
        }
        buckets[i] = 0;
    }
}

// @ 0x00a27760
void RcVector::DoInsertValue(RcPtr* pos, const RcPtr* value)
{
    if (mpEnd != mpCap) {
        const RcPtr* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        ::new (mpEnd) RcPtr(*(mpEnd - 1));
        CopyBackwardRc(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        RcPtr* pNew = nNew ? (RcPtr*)eaNew(nNew * sizeof(RcPtr), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        size_t nBefore = (char*)pos - (char*)mpBegin;
        RcPtr* pNewPos = (RcPtr*)memcpy_11e0744(pNew, mpBegin, nBefore) + nBefore / sizeof(RcPtr);
        ::new (pNewPos) RcPtr(*value);
        size_t nAfter = (char*)mpEnd - (char*)pos;
        RcPtr* pNewEnd = (RcPtr*)memcpy_11e0744(pNewPos + 1, pos, nAfter) + nAfter / sizeof(RcPtr);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNew;
        mpCap = pNew + nNew;
    }
}

// @ 0x00a27910
void Rec12Vector::DoInsertValue(Rec12* pos, const Rec12* value)
{
    if (mpEnd != mpCap) {
        const Rec12* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) *mpEnd = mpEnd[-1];
        Rec12* last = mpEnd - 1;
        Rec12* dst = mpEnd;
        while (last != pos) {
            --last;
            --dst;
            *dst = *last;
        }
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        Rec12* pNew = nNew ? (Rec12*)eaNew(nNew * sizeof(Rec12), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        Rec12* pNewEnd = RelocateRec12(mpBegin, pos, pNew);
        if (pNewEnd) *pNewEnd = *value;
        pNewEnd = RelocateRec12(pos, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpFixed) operator delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + nNew;
    }
}

// @ 0x00a27a40
void Rec24Vector::DoInsertValue(Rec24* pos, const Rec24* value)
{
    if (mpEnd != mpCap) {
        const Rec24* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) *mpEnd = mpEnd[-1];
        CopyBackwardRec24(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        Rec24* pNew = nNew ? (Rec24*)eaNew(nNew * sizeof(Rec24), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        Rec24* pNewEnd = RelocateRec24(mpBegin, pos, pNew);
        if (pNewEnd) *pNewEnd = *value;
        pNewEnd = RelocateRec24(pos, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpFixed) operator delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + nNew;
    }
}

// @ 0x00a27b90
void ZoneVector::DoInsertValue(Zone* pos, const Zone* value)
{
    if (mpEnd != mpCap) {
        const Zone* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) *mpEnd = mpEnd[-1];
        Zone* last = mpEnd - 1;
        Zone* dst = mpEnd;
        while (last != pos) {
            --last;
            --dst;
            *dst = *last;
        }
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        Zone* pNew = nNew ? (Zone*)eaNew(nNew * sizeof(Zone), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        Zone* pNewEnd = RelocateZone(mpBegin, pos, pNew);
        if (pNewEnd) *pNewEnd = *value;
        pNewEnd = RelocateZone(pos, mpEnd, pNewEnd + 1);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNew;
        mpCap = pNew + nNew;
    }
}

// @ 0x00a27e60
bool CountMap::AddRef(uint32_t key)
{    CountNode* n = (CountNode*)mTree.findv(key).node;
    if ((char*)this + 8 == (char*)n) {
        CountPair v(key, 1);
        *(unsigned char*)&key = 0;
        mTree.Insert(v, *(CountTrueType*)&key);
        return true;
    }
    n->count++;
    return true;}

// @ 0x00a27ed0
bool Submix_s00a2_6e10::ConnectToSubmix(Submix_s00a2_6e10* other)
{    if (!other) return false;
    AudioLockGuard lock;
    Plugin* plugin = (Plugin*)mVoiceContainer.FindPlugin(0x41695730);
    if (plugin) {
        EStr s;
        const char* name = mpName;
        s.sprintf("%s.aiff", name);
        plugin->SetName(0, s.c_str());
    }
    void* sub = fld<void*>(other, 0x970);
    return mVoiceContainer.ConnectToSubmix(sub, 0);
}

// @ 0x00a27ff0
bool EvOwner::Register(uint32_t a1, uint32_t a2, void* a3, double a4)
{
    EvOwner* self = this;
    HIter_s00a2_6e10 it;
    EvTable& t = self->mEvents;
    void* end = t.mpBuckets[t.mnBuckets];
    t.find(&it, &a1);
    if (it.node != end) return false;
    RefObj* created = 0;
    bool ok = ((VCreate)VSLOT(self, 0x94))(self, a1, a2, a3, 0, &created);
    if (!ok) {
        HIter_s00a2_6e10 res;
        t.Insert(&res, &a1, 0);
        ((VNotify)VSLOT(self, 0x98))(self, a2, 1);
        if (created) created->Release();
        return false;
    }
    bool fired = ((VFire)VSLOT(created, 0x14))(created, a4);
    if (fired) {
        if (created) created->Release();
        return true;
    }
    if (created) created->Release();
    return false;
}

// @ 0x00a28120
bool Sys_s00a2_8120::StartSoundFromCommand(Command& cmd, unsigned id)
{
    Snd_s00a2_8120* snd = 0;
    Snd_s00a2_8120* found = 0;
    {
        Snd_s00a2_8120* cur = FindSound(id);
        found = cur;
        Snd_s00a2_8120* hold = FindSound(id);
        while (found) {
            found = hold;
            Snd_s00a2_8120* nxt = found;
            if (nxt)
                nxt->AddRef();
            if (cur)
                cur->Release();
            found = nxt;
            break;
        }
    }
    if (snd != found)
        snd = found;
    if (!snd) {
        unsigned key = 0;
        cmd.GetUint32(0x3475381, &key);
        if (key == 0) {
            char* name = cmd.GetString8(0x347537e);
            if (!name)
                return false;
            key = SymbolToId(name);
        }
        void* last = 0;
        HIter_s00a2_8120 it2;
        {
            void** buckets = mSoundMap.mpBuckets;
            unsigned n = mSoundMap.mnBuckets;
            last = buckets[n];
            T4Find(&mSoundMap, &it2, &key);
            if (it2.node != last)
                return false;
        }
        int flag = 0;
        {
            unsigned a = 0, b = 0;
            if (cmd.GetBool(0x3475391, (bool*)&a)) {
                if (cmd.GetBool(0x3475395, (bool*)&b)) {
                    flag = 1;
                    if (!cmd.GetBool(0x3475398, (bool*)&a))
                        flag = 0;
                } else {
                    flag = 0;
                }
            } else {
                flag = 0;
            }
        }
        void* data = 0;
        cmd.GetVoidPtr(0x347539c, &data);
        if (snd)
            snd->Release();
        snd = 0;
        Vec3_s00a2_8120 pos;
        if (!StartSound(key, id, data, flag ? &pos : 0, &snd)) {
            T4Op(&mSoundMap, &it2, &key, 0);
            StopSound2(id, 1);
            if (data)
                ((SndA*)data)->Release();
            if (snd)
                snd->Release();
            return false;
        }
        if (data)
            ((SndA*)data)->Release();
    }
    {
        void* value = 0;
        unsigned type = 0;
        void* extra = 0;
        unsigned id2 = 0;
        void* node = cmd.EnumParameter(&value, &id2, &type, &extra);
        while (node) {
            if (type == 0) {
                ((SndB*)((char*)snd + 4))->PropF(0, *(float*)&node, 1);
            } else if (type == 5) {
                snd->Prop3(5, (unsigned)node, id2);
            }
            node = cmd.EnumParameter(&value, &id2, &type, &extra);
        }
    }
    float gain = 0.0f;
    cmd.GetBool(0x12c65397, (bool*)&gain);
    snd->SetGain((double)gain);
    if (snd)
        snd->Release();
    return true;
}

// @ 0x00a28450
bool Sys_s00a2_8120::TryStartSound(char* out, unsigned id, IConfig* cfg, Vec3_s00a2_8120* pos, unsigned a5)
{
    char* p = out;
    *(unsigned*)(p + 0x14) = id;
    *(unsigned*)(p + 0x18) = (unsigned)cfg;
    cfg->GetBool(0x12d2a4d4, (bool*)(p + 0));
    cfg->GetBool(0x6dd08218, (bool*)(p + 1));
    cfg->GetBool(0xba134192, (bool*)(p + 2));
    if (*(bool*)(p + 0)) {
        float window = 0.0f;
        if (!cfg->GetFloat(0xf616b72, (float*)(p + 8)))
            return false;
        if (!cfg->GetFloat(0x3593710, (float*)(p + 4)))
            return false;
        if (!pos)
            return false;
        unsigned surf = 0;
        cfg->GetUint32(0xed1f36d5, &surf);
        Vec3_s00a2_8120* listener = (Vec3_s00a2_8120*)g_audioSys->GetListenerTransform(surf);
        float dx = pos->x - listener->x;
        float dy = pos->y - listener->y;
        float dz = pos->z - listener->z;
        float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
        dist = (float)fabs((double)dist);
        if (!*(bool*)(p + 1) && dist > *(float*)(p + 4))
            return false;
        float gain = *(float*)0x01485720;
        cfg->GetFloat(0x2406a047, &gain);
        float fmax = *(float*)0x01485720;
        cfg->GetFloat(0x25df0108, &fmax);
        if (*(float*)(p + 8) > dist)
            window = gain * *(float*)0x01485720;
        else if (gain == 0.0f)
            window = *(float*)0x01485720;
        else if (dist > *(float*)(p + 4))
            window = *(float*)0x01485720;
        else {
            ResponseCurve curve;
            if (curve.InitFromConfiguration(0x1e4db1eb, cfg))
                window = gain * curve.GetOutputValue((dist - *(float*)(p + 8)) /
                                                     (*(float*)(p + 4) - *(float*)(p + 8)));
            else
                window = *(float*)0x01485720;
        }
        *(float*)(p + 0xc) = window;
    }
    *(float*)(p + 0x10) = *(float*)0x01485720;
    cfg->GetFloat(0x393f7f7d, (float*)(p + 0x10));
    *(unsigned*)(p + 0x1c) = 1;
    cfg->GetUint32(0xd9ec19d6, (unsigned*)(p + 0x1c));
    *(unsigned*)(p + 0x24) = 0xee8347b0;
    cfg->GetId(0x7f28acc, (unsigned*)(p + 0x24));
    *(unsigned*)(p + 0x28) = (unsigned)AddPlaylistRef(a5, 0);
    *(unsigned*)(p + 0x2c) = 2;
    cfg->GetUint32(0xbaf7f4f9, (unsigned*)(p + 0x2c));
    cfg->GetUint32(0x51997db2, (unsigned*)(p + 0x3c));
    unsigned* owner = (unsigned*)(p + 0x20);
    cfg->GetId(0x701ed91e, owner);
    if (*owner == 0)
        *owner = a5;
    unsigned slot = *owner;
    Key4_s00a2_8120 key;
    key.a = 0;
    key.b = slot;
    key.c = 0x3055f61;
    key.d = 0x21407ee;
    *(unsigned*)(p + 0x30) = 0xffffffff;
    if (FindPlaylistTable(&key, p + 0x38)) {
        void* o = 0;
        if (GetPlaylistOwner(&key, &o) && o)
            *(unsigned*)(p + 0x30) = *(unsigned*)((char*)o + 0x14);
        if (o)
            ((SndA*)o)->Release();
    } else {
        *(unsigned*)(p + 0x30) = (unsigned)ReleasePlaylistRef(slot);
    }
    return true;
}

// @ 0x00a28810
void Sys_s00a2_8120::MaintainLRU()
{
    HIter_s00a2_8120 res;
    void** bucket = mLRUTable.mpBuckets;
    void* node = *bucket;
    if (!node) {
        ++bucket;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    void* last = mLRUTable.mpBuckets[mLRUTable.mnBuckets];
    while (node != last) {
        Snd_s00a2_8120* snd = (Snd_s00a2_8120*)((ENode_s00a2_8120*)node)->owner;
        bool linked = false;
        if (snd->IsPlaying()) {
            void* layers = 0;
            if (snd->GetLayers(&layers)) {
                if (mTexEnabled) {
                    void** act = mActiveTable.mpBuckets;
                    HIter_s00a2_8120 it;
                    T4Find(&mActiveTable, &it, (char*)layers + 8);
                    void* expected = act[mActiveTable.mnBuckets];
                    if (*(void**)it.node == expected) {
                        mLRUBytes += *(int*)((char*)layers + 0x18);
                        Key4_s00a2_8120 pair;
                        pair.a = *(unsigned*)((char*)layers + 8);
                        pair.b = *(unsigned*)((char*)layers + 0xc);
                        pair.c = *(unsigned*)((char*)layers + 0x10);
                        pair.d = (unsigned)layers;
                        ((SndA*)layers)->AddRef();
                        HIter_s00a2_8120 it2;
                        T4Insert2(&mActiveTable, &it2, &pair, 0);
                        if (layers)
                            ((SndA*)layers)->Release();
                        mLRUIterNode = mActiveTable.mpBuckets[mActiveTable.mnBuckets];
                        mLRUIterBucket = &mActiveTable.mpBuckets[mActiveTable.mnBuckets];
                    }
                }
                linked = true;
            }
        }
        if (linked) {
            res = *PairErase(&mLRUTable, node, bucket);
            node = res.node;
            bucket = res.bucket;
        } else {
            node = ((ENode_s00a2_8120*)node)->next;
            if (!node) {
                ++bucket;
                while (!*bucket)
                    ++bucket;
                node = *bucket;
            }
        }
    }
}

// @ 0x00a28a20
void Sys_s00a2_8120::AddTextureRef(Key4_s00a2_8120* key)
{
    U32Table* map = &mTexTable;
    HIter_s00a2_8120 it;
    map->find(&it, key);
    if (it.node != map->mpBuckets[map->mnBuckets]) {
        ++((unsigned*)map->mpBuckets[map->mnBuckets])[3];
        return;
    }
    InsertRes_s00a2_8120 res;
    Key4_s00a2_8120 pair;
    pair.a = key->a;
    pair.b = key->b;
    pair.c = key->c;
    pair.d = 0;
    map->mpBuckets[map->mnBuckets] = 0;
    KInsert(&res, &pair, 1);
}

// @ 0x00a28aa0
bool Sys_s00a2_8120::GetOrRegisterVoice(unsigned key, Voice** out, int nLayers, void* layers)
{
    Voice* v = 0;
    HIter_s00a2_8120 it;
    mVoiceMap.find(&it, &key);
    if (it.node != mVoiceMap.mpBuckets[mVoiceMap.mnBuckets]) {
        v = (Voice*)((KeyNode*)it.node)->value;
        if (v)
            ++v->rc;
    } else {
        Voice* nv = (Voice*)EAAllocate(0xa0, (char*)0x140a5a0, 0, 0, 0, 0);
        if (nv) {
            nv->rc = 0;
            nv->f0c = (char*)nv + 0x20;
            nv->f08 = (char*)nv + 0x20;
            nv->f18 = (char*)nv + 0x20;
            nv->f9c = nv->f0c;
            nv->f98 = 0;
            nv->f10 = (char*)nv->f98 + 0x78;
            *(void**)nv = g_voiceVT;            ++nv->rc;
            v = nv;
        }
        if (!v->Init()) {
            if (v) {
                if (--v->rc == 0) {
                    v->rc = 1;
                    v->DestroyV(1);
                }
            }
            return false;
        }
        int n = nLayers;
        if (n > 0) {
            char* p = (char*)layers;
            do {
                v->AddLayer(*(void**)p);
                p += 0xc;
            } while (--n);
        }
        v->Reset();
        Voice** slot = RefMapFindOrInsert(&mVoiceMap, &key);
        Voice* old = *slot;
        if (v != old) {
            if (v)
                ++v->rc;
            *slot = v;
            if (old) {
                if (--old->rc == 0) {
                    old->rc = 1;
                    old->DestroyV(1);
                }
            }
        }
    }
    if (out) {
        if (v)
            ++v->rc;
        *out = v;
    }
    if (v) {
        if (--v->rc == 0) {
            v->rc = 1;
            v->DestroyV(1);
        }
    }
    return true;
}

// Object map insert at 0xa28c60: a ref-counted key/value pair goes through the map's DoInsertValue (0x00a136f0).
struct SndRef_a28c60 {
    Snd_s00a2_8120* p;
    SndRef_a28c60(Snd_s00a2_8120* q) : p(q) { if (p) p->AddRef(); }
    SndRef_a28c60(const SndRef_a28c60& o) : p(o.p) { if (p) p->AddRef(); }
    ~SndRef_a28c60() { if (p) p->Release(); }
};
struct SndPair_a28c60 {
    Snd_s00a2_8120* key;
    SndRef_a28c60 value;
    SndPair_a28c60(Snd_s00a2_8120* k, const SndRef_a28c60& v) : key(k), value(v) {}
};
struct SndInsertRes_a28c60 { HIter_s00a2_8120 it; bool inserted; };
struct TrueTag_a28c60 {};
struct SndObjMap_a28c60 {
    SndInsertRes_a28c60 DoInsertValue(const SndPair_a28c60& v, TrueTag_a28c60);   // 0x00a136f0
};

// @ 0x00a28c60
void Sys_s00a2_8120::RegisterObj(Snd_s00a2_8120* p)
{
    SndRef_a28c60 ref(p);
    SndPair_a28c60 pair(ref.p, ref);
    ((SndObjMap_a28c60*)&mObjMap)->DoInsertValue(pair, TrueTag_a28c60());
}

// @ 0x00a28d10
bool Sys_s00a2_8120::UnregisterObj(unsigned key)
{
    U32Table* map = &mObjMap;
    HIter_s00a2_8120 it;
    map->find(&it, &key);
    if (it.node != map->mpBuckets[map->mnBuckets]) {
        map->erase(&it, it);
        return true;
    }
    return false;
}

// @ 0x00a28d70
int Sys_s00a2_8120::GetCounterPlaylist(unsigned key)
{
    U32Table* map = &mCounterMap;
    HIter_s00a2_8120 it;
    map->find(&it, &key);
    if (it.node != map->mpBuckets[map->mnBuckets])
        return *(int*)((char*)it.node + 4);
    Key4_s00a2_8120 k;
    k.c = 0x1a527db;
    k.d = 0x21407ee;
    k.a = 0;
    k.b = key;
    void* owner = 0;
    int result = -1;
    if (GetPlaylistOwner2(&k, &owner)) {
        short* p = (short*)((char*)owner + 0x14);
        void* p1 = &p[1];
        p1 = PoolAlloc(&p1, 4);
        void* p2 = 0;
        p2 = PoolAlloc(&p1, 4);
        result = (int)p2;
        Key4_s00a2_8120 pair;
        pair.a = (unsigned)p1;
        pair.b = (unsigned)p2;
        HIter_s00a2_8120 it2;
        T4Insert3(&mCounterMap, &it2, &pair, 0);
    }
    if (owner)
        ((SndA*)owner)->Release();
    return result;
}

// @ 0x00a28e90
int Sys_s00a2_8120::AddCounter(unsigned key, int delta)
{
    U32Table* map = &mCounterA;
    HIter_s00a2_8120 it;
    map->find(&it, &key);
    if (it.node != map->mpBuckets[map->mnBuckets]) {
        int* p = (int*)((char*)it.node + 4);
        *p += delta;
        return *p;
    }
    Key4_s00a2_8120 pair;
    pair.a = key;
    pair.b = 0;
    pair.c = 0;
    pair.d = delta;
    HIter_s00a2_8120 it2;
    T4Insert3(map, &it2, &pair, 0);
    return delta;
}

// @ 0x00a28f10
bool Sys_s00a2_8120::TrackPlayingKey(Snd_s00a2_8120* obj)
{
    if (!obj)
        return false;
    if (!obj->IsPlaying())
        return false;
    if (!RegisterKey((char*)obj + 4))
        return false;
    obj->AddRef();                          // local AutoRefCount
    obj->AddRef();                          // pair's smart-pointer copy
    unsigned key = obj->GetKey();
    obj->AddRef();                          // map value's reference
    Key4_s00a2_8120 pair;
    pair.a = key;
    pair.b = (unsigned)obj;
    pair.c = 0;
    pair.d = 0;
    HIter_s00a2_8120 it;
    PairInsert(&mKeyMap, &it, &pair, 0);
    if (obj)
        obj->Release();
    if (obj)
        obj->Release();
    return true;
}

// @ 0x00a29000
bool Sys_s00a2_8120::UntrackPlayingKey(Snd_s00a2_8120* obj)
{
    if (!obj)
        return false;
    unsigned k = obj->GetKey();
    U32Table* map = &mKeyMap;
    HIter_s00a2_8120 it;
    map->find(&it, &k);
    if (it.node == map->mpBuckets[map->mnBuckets])
        return false;
    UnregisterKey((char*)obj + 4);
    map->erase(&it, it);
    if (obj->listNext) {
        if (obj->listPrev) {
            obj->listPrev->listNext = obj->listNext;
            obj->listNext->listPrev = obj->listPrev;
            obj->listNext = 0;
            obj->listPrev = 0;
        }
    }
    obj->listNext = 0;
    obj->listPrev = 0;
    obj->Release();
    return true;
}

// @ 0x00a290b0
bool Sys_s00a2_90b0::RegisterKey(void* key)
{
    if (!key)
        return false;
    unsigned id = ((KeyObj*)key)->GetId8();
    HIter_s00a2_90b0 it;
    mPrimTable.find(&it, &id);
    if (it.node != mPrimTable.mpBuckets[mPrimTable.mnBuckets])
        return false;
    PairU pair;
    pair.first = ((KeyObj*)key)->GetId8();
    pair.second = key;
    InsertRes_s00a2_90b0 out;
    Tag tag;
    tag.b = false;
    mPrimTable.InsertPair(&out, &pair, tag);
    return true;
}

// @ 0x00a29140
bool Sys_s00a2_90b0::UnregisterKey(void* key)
{
    if (!key)
        return false;
    unsigned id = ((KeyObj*)key)->GetId18();
    HTable_s00a2_90b0* t = &mUnregTable;
    HIter_s00a2_90b0 it;
    t->find(&it, &id);
    if (it.node == t->mpBuckets[t->mnBuckets])
        return false;
    t->erase(&it, it);
    return true;
}

// 0x00a291b0 (byte-exact lifted version: match/slices/s00a291b0/s00a291b0.cpp)
void Sys_s00a2_90b0::ClearUnregTable()
{
    HTable_s00a2_90b0* t = &mUnregTable;
    HNode** bucket = (HNode**)t->mpBuckets;
    HNode* node = *bucket;
    if (!node) {
        ++bucket;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    HNode* end = (HNode*)t->mpBuckets[t->mnBuckets];
    while (node != end) {
        ((Obj_s00a2_90b0*)node->value)->v05();
        node = node->next;
        if (!node) {
            ++bucket;
            while (!*bucket)
                ++bucket;
            node = *bucket;
        }
    }
    t->FreeBuckets(t->mpBuckets, t->mnBuckets);
    t->mnElements = 0;
}

// @ 0x00a29230
void Sys_s00a2_90b0::ClearClearTable()
{
    HTable_s00a2_90b0* t = &mClearTable;
    HNode** bucket = (HNode**)t->mpBuckets;
    HNode* node = *bucket;
    if (!node) {
        ++bucket;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    HNode* end = (HNode*)t->mpBuckets[t->mnBuckets];
    while (node != end) {
        Obj_s00a2_90b0* obj = (Obj_s00a2_90b0*)node->value;
        node->value = 0;
        obj->v05();
        obj->Release();
        node = node->next;
        if (!node) {
            ++bucket;
            while (!*bucket)
                ++bucket;
            node = *bucket;
        }
    }
    mUnregTable.FreeBuckets(mUnregTable.mpBuckets, mUnregTable.mnBuckets);
    mUnregTable.mnElements = 0;
}

// @ 0x00a292d0
unsigned Sys_s00a2_90b0::PopIdA()
{
    IdRing_s00a2_90b0* r = &mPoolA.ring;
    if (r->mBegin == r->mEnd)
        return 0;
    unsigned v = *r->mBegin;
    r->mBegin += 1;
    if (r->mBegin == r->cEnd)
        r->mBegin = r->cBegin;
    r->mSize -= 1;
    InsertRes_s00a2_90b0 out;
    Tag tag;
    tag.b = false;
    mPoolA.table.InsertKey(&out, &v, tag);
    return v;
}

// @ 0x00a29340
unsigned Sys_s00a2_90b0::PopIdC()
{
    IdRing_s00a2_90b0* r = &mPoolC.ring;
    if (r->mBegin == r->mEnd)
        return 0;
    unsigned v = *r->mBegin;
    r->mBegin += 1;
    if (r->mBegin == r->cEnd)
        r->mBegin = r->cBegin;
    r->mSize -= 1;
    InsertRes_s00a2_90b0 out;
    Tag tag;
    tag.b = false;
    mPoolC.table.InsertKey(&out, &v, tag);
    tag.b = false;
    mPoolA.table.InsertKey(&out, &v, tag);
    return v;
}

// @ 0x00a293e0
unsigned Sys_s00a2_90b0::PopIdB()
{
    IdRing_s00a2_90b0* r = &mPoolB.ring;
    if (r->mBegin == r->mEnd)
        return 0;
    unsigned v = *r->mBegin;
    r->mBegin += 1;
    if (r->mBegin == r->cEnd)
        r->mBegin = r->cBegin;
    r->mSize -= 1;
    InsertRes_s00a2_90b0 out;
    Tag tag;
    tag.b = false;
    mPoolB.table.InsertKey(&out, &v, tag);
    return v;
}

// @ 0x00a29450
bool Sys_s00a2_90b0::GetTexture(Key12* key, void** out)
{
    if (mCacheSizeLimit != 0) {
        HIter_s00a2_90b0 it;
        mActiveTable.findKey12(&it, key);
        if (it.node != mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            TexObj* obj = ((TexNode_s00a2_90b0*)it.node)->value;
            obj->time = SystemTime();
            if (out) {
                AddTextureRef(key);
                obj->AddRef();
                *out = obj;
            }
            mCountHit += 1;
            return true;
        }
    }
    mCountMiss += 1;
    TexObj* obj = 0;
    void* created = 0;
    DbObj* db = (DbObj*)FindDatabase(key);
    if (db) {
        void* info = 0;
        if (db->Create(key, &info, 1, 6, 1, 0)) {
            if (mpFactoryB->Create(info, &created, 0, key->b)) {
                obj = (TexObj*)created;
                obj->AddRef();
                obj->key = *key;
            }
        }
        if (info)
            ((DbInfo*)info)->i9();
        if (created)
            ((Obj_s00a2_90b0*)created)->Release();
        if (info)
            ((DbInfo*)info)->i2();
    }
    if (!obj)
        return false;
    obj->time = SystemTime();
    if (mCacheSizeLimit != 0) {
        mCurrentBytes += obj->size;
        Key16 pair;
        pair.a = key->a;
        pair.b = key->b;
        pair.c = key->c;
        pair.d = (unsigned)obj;
        obj->AddRef();
        InsertRes_s00a2_90b0 out2;
        Tag tag;
        tag.b = false;
        mActiveTable.InsertPair16(&out2, &pair, tag);
        obj->Release();
        mLRUIterNode = (TexNode_s00a2_90b0*)mActiveTable.mpBuckets[mActiveTable.mnBuckets];
        mLRUIterBucket = (TexNode_s00a2_90b0**)&mActiveTable.mpBuckets[mActiveTable.mnBuckets];
    }
    if (out) {
        AddTextureRef(key);
        obj->AddRef();
        *out = obj;
    }
    obj->Release();
    return true;
}

// @ 0x00a29690
bool Sys_s00a2_90b0::GetTexture2(Key12* key, void** out2, void** out)
{
    void* result = 0;
    TexObj* obj = 0;
    if (mCacheSizeLimit != 0) {
        HIter_s00a2_90b0 it;
        mActiveTable.findKey12(&it, key);
        if (it.node != mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            obj = ((TexNode_s00a2_90b0*)it.node)->value;
            obj->time = SystemTime();
            if (out2)
                *out2 = 0;
            if (out) {
                AddTextureRef(key);
                obj->AddRef();
                *out = obj;
            }
            mCountHit += 1;
            if (result)
                ((Obj_s00a2_90b0*)result)->Release();
            return true;
        }
    }
    {
        HIter_s00a2_90b0 jt;
        mLRUTable.findKey12(&jt, key);
        if (jt.node != mLRUTable.mpBuckets[mLRUTable.mnBuckets]) {
            if (out2) {
                void* v = ((TexNode_s00a2_90b0*)jt.node)->value;
                *out2 = v;
                ((Obj_s00a2_90b0*)v)->AddRef();
            }
            if (result)
                ((Obj_s00a2_90b0*)result)->Release();
            return true;
        }
    }
    mCountMiss += 1;
    void* p = FUN_008d5d00();
    if (p) {
        DbObj* db = (DbObj*)FindDatabase(key);
        if (db) {
            void* info = 0;
            if (db->Create(key, &info, 1, 6, 1, 0)) {
                void* holder = 0;
                void* effect = FUN_00a16f40(&holder, 0, info, 0, key, 0);
                ((Obj_s00a2_90b0*)p)->v04(mpFactoryB, effect);
                ((DbInfo*)info)->i9();
                void* holder2 = 0;
                void* r = FUN_00a21d00(&holder2, key, &result);
                void* res[4];
                FUN_00a27500(res, r);
                if (out) {
                    *out = result;
                    ((Obj_s00a2_90b0*)result)->AddRef();
                }
            }
            if (info)
                ((DbInfo*)info)->i2();
        }
    }
    if (result)
        ((Obj_s00a2_90b0*)result)->Release();
    return false;
}

// @ 0x00a298f0
void Sys_s00a2_90b0::RemoveTexture(TexObj* obj)
{
    if (mCacheSizeLimit != 0) {
        HIter_s00a2_90b0 it;
        mActiveTable.findKey12(&it, &obj->key);
        if (it.node == mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            mCurrentBytes += obj->size;
            obj->AddRef();
            Key16 pair;
            pair.a = obj->key.a;
            pair.b = obj->key.b;
            pair.c = obj->key.c;
            pair.d = (unsigned)obj;
            obj->AddRef();
            InsertRes_s00a2_90b0 out;
            Tag tag;
            tag.b = false;
            mActiveTable.InsertPair16(&out, &pair, tag);
            if (pair.d)
                obj->Release();
            obj->Release();
            mLRUIterNode = (TexNode_s00a2_90b0*)mActiveTable.mpBuckets[mActiveTable.mnBuckets];
            mLRUIterBucket = (TexNode_s00a2_90b0**)&mActiveTable.mpBuckets[mActiveTable.mnBuckets];
        }
        HIter_s00a2_90b0 jt;
        mLRUTable.findKey12(&jt, &obj->key);
        if (jt.node != mLRUTable.mpBuckets[mLRUTable.mnBuckets])
            mLRUTable.eraseNode(jt, &jt);
    }
}

// @ 0x00a29a50
void Sys_s00a2_90b0::SweepLRU()
{
    if (mActiveTable.mnElements == 0)
        return;
    if (mCacheSizeLimit == 0)
        return;
    Stopwatch_s00a2_90b0 sw(3, false);
    sw.Restart();
    if ((unsigned)mCurrentBytes <= (unsigned)mCacheSizeLimit)
        return;
    do {
        if (mLRUIterNode == (TexNode_s00a2_90b0*)mActiveTable.mpBuckets[mActiveTable.mnBuckets]) {
            TexNode_s00a2_90b0** b = (TexNode_s00a2_90b0**)mActiveTable.mpBuckets;
            TexNode_s00a2_90b0* n = *b;
            if (!n) {
                ++b;
                while (!*b)
                    ++b;
                n = *b;
            }
            mLRUIterNode = n;
            mLRUIterBucket = (TexNode_s00a2_90b0**)b;
        }
        TexObj* obj = mLRUIterNode->value;
        if (SystemTime() - obj->time <= mRemoveOlderThanSec) {
            TexNode_s00a2_90b0* n = mLRUIterNode->next;
            mLRUIterNode = n;
            while (!n) {
                mLRUIterBucket += 1;
                n = *mLRUIterBucket;
                mLRUIterNode = n;
            }
        } else {
            mCurrentBytes -= obj->size;
            HIter_s00a2_90b0 it;
            it.node = mLRUIterNode;
            it.bucket = (HNode**)mLRUIterBucket;
            HIter_s00a2_90b0 tmp;
            HIter_s00a2_90b0* res = mActiveTable.eraseNode(it, &tmp);
            mLRUIterNode = (TexNode_s00a2_90b0*)res->node;
            mLRUIterBucket = (TexNode_s00a2_90b0**)res->bucket;
        }
        __int64 elapsed = sw.GetElapsedTimeF();
        if ((double)elapsed * sw.coeff > (double)(unsigned)mTimeSliceUSec)
            break;
    } while ((unsigned)mCurrentBytes > (unsigned)mCacheSizeLimit);
}

// @ 0x00a29be0
bool Sys_s00a2_90b0::ReadTuningValues(const Key12* key)
{
    if (key->a != g_keyA || key->b != g_keyB || key->c != g_keyC)
        return true;
    IConfig_s00a2_90b0* cfg = (IConfig_s00a2_90b0*)mpConfiguration;
    if (!cfg)
        return false;

    cfg->GetBool(0x7188e63e, &mBool3fd);
    cfg->GetFloat(0xe8bc4932, &mFloat400);
    Slot112();

    StrList* strList = 0;
    if (cfg->GetList1(0x4b2a3424, (void**)&strList) && strList) {
        unsigned count;
        const char** base;
        if (strList->mFlags & 0x30) {
            count = strList->mnSize;
            base = (const char**)strList->mpBegin;
        } else {
            count = strList->mInlineLen != 0 ? 1 : 0;
            base = strList->mInlineLen != 0 ? (const char**)strList : 0;
        }
        for (unsigned i = 0; i < count; ++i) {
            const char* s = ((Str16_s00a2_90b0*)base)[i].mpStr;
            v058(SymbolToId(s), s);
        }
    }

    unsigned* list2 = 0;
    unsigned count2 = 0;
    if (cfg->GetList2(0x7cb81a35, (void**)&list2, (void**)&count2)) {
        for (unsigned i = 0; i < count2; ++i)
            v072(list2[i * 3]);
    }

    unsigned modeId = SymbolToId("dacoutputmode");
    void* modeStr = cfg->GetString(modeId);
    if (modeStr) {
        WString ws;
        ws.RangeInit((const wchar_t*)modeStr);
        float v;
        if (WideEquals(&ws, g_wMono))
            v = 0.0f;
        else if (WideEquals(&ws, g_wStereo))
            v = 1.0f;
        else if (WideEquals(&ws, g_wQuad))
            v = g_fQuadVal;
        else if (WideEquals(&ws, g_wSurround))
            v = g_fSurroundVal;
        else
            v = 1.0f;
        SetProperty(v, 0x435b383);
    }

    float fv;
    if (cfg->GetFloat(0x6a371e0, &fv))
        SetProperty(fv, 0x6a371e0);

    SetProperty((float)mPerformanceLevel, 0x6df5822d);

    unsigned u;
    u = SymbolToId("streampoolnumstreams");
    cfg->GetUint32(u, &mStreamPoolNumStreams);
    u = SymbolToId("streampoolbuffersize");
    cfg->GetUint32(u, &mStreamPoolBufferSize);
    u = SymbolToId("streampoolmaxrequests");
    cfg->GetUint32(u, &mStreamPoolMaxRequests);
    u = SymbolToId("RemoveMostFrequentlyUnusedTimeSliceUSec");
    cfg->GetUint32(u, (unsigned*)&mTimeSliceUSec);

    u = SymbolToId("RemoveIfOlderThanSeconds");
    if (cfg->GetFloat(u, &fv))
        mRemoveOlderThanSec = (double)fv;

    u = SymbolToId("BinaryResourceCacheSizeMB");
    unsigned cacheMB;
    if (cfg->GetUint32(u, &cacheMB))
        mCacheSizeLimit = (int)(cacheMB << 20);
    if (mbDisableCache)
        mCacheSizeLimit = 0;

    cfg->GetUint32(0xed9f3a3d, &mU20c);
    cfg->GetUint32(0xdcdf5a2d, &mU204);
    cfg->GetUint32(0xe25ce39d, &mU208);
    return true;
}

// @ 0x00a2a020
bool SysLike::ConnectSubmixTree()
{
    Submix* first = vc_s00a2_a020<Submix*>(this, 0x17c, (u32)0xf1cc1687);
    Submix** it  = *(Submix***)((char*)this + 0x119ba4);
    Submix** end = *(Submix***)((char*)this + 0x119ba8);
    int fail = 0;
    for (; it != end; ++it) {
        Submix* s = *it;
        if (s)
            ((void (__thiscall*)(void*))(*(void***)s)[0])(s);
        u32 id;
        char* nb = *(char**)((char*)s + 0x978);
        if (nb == *(char**)((char*)s + 0x97c) || nb == 0)
            id = 0xf1cc1687;
        else
            id = vc_s00a2_a020<u32>(this, 0xf4, nb);
        Submix* found = vc_s00a2_a020<Submix*>(this, 0x17c, id);
        if (found == 0) {
            ++fail;
        } else {
            ((void (__thiscall*)(void*))(*(void***)found)[0])(found);
            if (s != first) {
                s->DisconnectFromSubmix();
                if (!s->ConnectToSubmix(found))
                    ++fail;
            }
            ((void (__thiscall*)(void*))(*(void***)found)[1])(found);
        }
        if (s)
            ((void (__thiscall*)(void*))(*(void***)s)[1])(s);
    }
    return fail == 0;
}

// @ 0x00a2a150
int SmallStubs::GetOrInsert(int* key)
{
    int local_20;
    ((HashFindStub*)this)->find(&local_20, key);
    int endBucket = *(int*)(*(int*)((char*)this + 4) + *(int*)((char*)this + 8) * 4);
    if (local_20 != endBucket)
        return local_20 + 4;
    int local_18[3];
    int k = *key;
    local_18[0] = 0; local_18[1] = 0; local_18[2] = 0;
    BoolTag tag;
    tag.b = false;
    Insert(local_18, &k, tag);
    return local_18[0] + 4;
}

// @ 0x00a2aa70
void SmallStubs::Dtor()
{
    char* hb = (char*)this + 4;
    HashBase* h = (HashBase*)hb;
    h->DoFreeNodes(*(void**)(hb + 4), *(void**)(hb + 8));
    void* p = *(void**)(hb + 4);
    *(void**)(hb + 0xc) = 0;
    if (*(u32*)(hb + 8) > 1 && p != *(void**)(hb + 0x30)) {
        if (p < *(void**)(hb + 0x24) || p >= *(void**)(hb + 0x28)) {
            operator_delete__(p);
        } else {
            *(void**)p = *(void**)(hb + 0x1c);
            *(void**)(hb + 0x1c) = p;
            return;
        }
    }
}

// @ 0x00a2ab40
void Vec12::pushEmpty()
{
    if (mpEnd < mpCap) {
        ::new((void*)mpEnd++) E12();
    } else {
        E12 tmp = E12();
        DoInsertValue(mpEnd, &tmp);
    }
}

// @ 0x00a2ab80
void Vec18::pushEmpty()
{
    E18* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 1;
        if (e) {
            e->a = 0; e->b = 0; e->f = 0.0f;
            e->c = 0; e->d = 0; e->e = 0;
        }
    } else {
        E18 tmp;
        tmp.a = 0; tmp.b = 0; tmp.f = 0.0f;
        tmp.c = 0; tmp.d = 0; tmp.e = 0;
        DoInsertValue(e, &tmp);
    }
}

// @ 0x00a2abe0
void ZoneVec::push_back(const Zone_s00a2_a020* v)
{
    u8* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 0x2c;
        if (e)
            *(Zone_s00a2_a020*)e = *v;
    } else {
        DoInsertValue(e, v);
    }
}

// @ 0x00a2ac20
int* SmallStubs::VecIntInsert(int* param_2, int* param_3)
{
    int* self = (int*)this;
    int* piVar1 = (int*)self[1];
    if (piVar1 != (int*)self[2]) {
        if (param_2 <= param_3 && param_3 < piVar1)
            param_3 = param_3 + 1;
        if (piVar1 != 0) {
            int* piVar2 = (int*)piVar1[-1];
            *piVar1 = (int)piVar2;
            if (piVar2 != 0)
                ((void (__thiscall*)(void*))(*(void***)piVar2)[1])(piVar2);
        }
        memmove(param_2, (char*)self[1] - 4, (char*)self[1] - (char*)param_2);
        param_3 = (int*)*param_3;
        piVar1 = (int*)*param_2;
        if (param_3 != piVar1) {
            if (param_3 != 0)
                ((void (__thiscall*)(void*))(*(void***)param_3)[1])(param_3);
            *param_2 = (int)param_3;
            if (piVar1 != 0)
                ((void (__thiscall*)(void*))(*(void***)piVar1)[2])(piVar1);
        }
        self[1] = self[1] + 4;
        return param_2;
    }
    int local_14 = (int)piVar1 - *self >> 2;
    if (local_14 == 0) {
        local_14 = 1;
    } else {
        local_14 = local_14 * 2;
    }
    void* local_18 = 0;
    if (local_14 != 0)
        local_18 = operator new(local_14 * 4);
    int size = (int)param_2 - *self;
    char* pv = (char*)local_18 + size;
    if (pv != 0) {
        int* q = (int*)*param_3;
        *(int*)pv = (int)q;
        if (q != 0)
            ((void (__thiscall*)(void*))(*(void***)q)[1])(q);
    }
    int iVar3 = self[1];
    memmove((char*)pv + 4, param_2, iVar3 - (int)param_2);
    self[1] = (int)(pv + 4 + (iVar3 - (int)param_2));
    *self = (int)local_18;
    self[2] = (int)((char*)local_18 + local_14 * 4);
    return (int*)pv;
}

// @ 0x00a2add0
void SmallStubs::DestroyBuckets(int param_2, u32 param_3)
{
    for (u32 i = 0; i < param_3; i++) {
        void* puVar1 = *(void**)(param_2 + i * 4);
        while (puVar1) {
            void* puVar4 = puVar1;
            puVar1 = *(void**)((char*)puVar4 + 0x24);
            void* puVar3 = *(void**)((char*)puVar4 + 0x14);
            while (puVar3) {
                ((RBTreeStub*)((char*)puVar4 + 8))->DoNukeSubtree(*(void**)puVar3);
                void* next = *(void**)((char*)puVar3 + 4);
                operator_delete__(puVar3);
                puVar3 = next;
            }
            if (puVar4 != *(void**)((char*)this + 0x30)) {
                if (puVar4 < *(void**)((char*)this + 0x24) ||
                    *(void**)((char*)this + 0x28) <= puVar4) {
                    operator_delete__(puVar4);
                } else {
                    *(void**)puVar4 = *(void**)((char*)this + 0x1c);
                    *(void**)((char*)this + 0x1c) = puVar4;
                }
            }
        }
        *(void**)(param_2 + i * 4) = 0;
    }
}

// @ 0x00a2ae90
int SmallStubs::EraseRange(int param_2, int param_3)
{
    u32 u = (u32)(size_t)ARCopy((void*)param_3,
                              *(void**)((char*)this + 4), (void*)param_2);
    u32 end = *(u32*)((char*)this + 4);
    if (u < end) {
        void** p = (void**)(u + 0x10);
        int n = (int)(((end - u) - 1) / 0x14) + 1;
        do {
            if (*p != 0)
                ((void (__thiscall*)(void*))(*(void***)*p)[1])(*p);
            p += 5;
            --n;
        } while (n);
    }
    *(int*)((char*)this + 4) -= ((param_3 - param_2) / 0x14) * 0x14;
    return param_2;
}

// @ 0x00a2af30
void ARVector::DoInsertValue(AR_s00a2_af30* pos, const AR_s00a2_af30* value)
{
    if (mpEnd != mpCap) {
        const AR_s00a2_af30* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        ::new (mpEnd) AR_s00a2_af30(*(mpEnd - 1));
        ARCopyBackward(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        AR_s00a2_af30* pNew = nNew ? (AR_s00a2_af30*)eaNew(nNew * sizeof(AR_s00a2_af30), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        AR_s00a2_af30* pNewEnd = ARUninitCopy(mpBegin, pos, pNew);
        ARDestroyRange(mpBegin, pos, pNew);
        ::new (pNewEnd) AR_s00a2_af30(*value);
        pNewEnd = ARUninitCopy(pos, mpEnd, pNewEnd + 1);
        ARDestroyRange(pos, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mpFixed) operator_delete(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNew;
        mpCap = pNew + nNew;
    }
}

// @ 0x00a2b2e0
void ARVector::assign(const AR_s00a2_af30* first, const AR_s00a2_af30* last, const AR_s00a2_af30* last2)
{
    (void)last2;
    size_t n = (size_t)(last - first);
    if (n > (size_t)(mpCap - mpBegin)) {
        AR_s00a2_af30* pNew = DoAllocate((u32)n, (AR_s00a2_af30*)first, (AR_s00a2_af30*)last);
        Destroy(mpBegin, mpEnd);
        if (mpBegin && mpBegin != mpFixed) operator_delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNew + n;
        mpCap = pNew + n;
        return;
    }
    size_t size = (size_t)(mpEnd - mpBegin);
    if (n <= size) {
        AR_s00a2_af30* pNewEnd = ARCopy((AR_s00a2_af30*)first, (AR_s00a2_af30*)last, mpBegin);
        Destroy(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
        return;
    }
    AR_s00a2_af30* mid = (AR_s00a2_af30*)first + size;
    ARCopy((AR_s00a2_af30*)first, mid, mpBegin);
    AR_s00a2_af30* out;
    CopyElems20(&out, mid, (AR_s00a2_af30*)last, mpEnd, (AR_s00a2_af30*)last);
    mpEnd = out;
}

// @ 0x00a2b3e0
bool __stdcall FactoryVoiceTemplate_ReadResource(void* obj, OutRes* out, int, int)
{
    if (!obj || !out) return false;
    int stream = ((int(__thiscall*)(void*))VFN(obj, 0x18))(obj);
    if (!stream) return false;
    void* sys = g_pSystem_s00a2_af30;
    if (!sys) return false;

    u32* hdr = (u32*)((void*(__thiscall*)(void*))VFN(obj, 0x10))(obj);
    out->h0 = hdr[0];
    out->h1 = hdr[1];
    out->h2 = hdr[2];

    char buf[1024];
    if (!ReadLine((void*)stream, buf, 0x400)) return false;
    if (atol(buf) != 1) return false;
    int len = (int)ReadLine((void*)stream, buf, 0x400);
    if (!len) return false;

    char *tb = 0, *te = 0, *cur = buf;
    char* end = buf + len;
    if (TokLine(buf, end, ' ', &tb, &te, &cur)) {
        do {
            ((Vec12_s00a2_af30*)((char*)out + 0x14))->pushEmpty();
            u8* rec = *(u8**)((char*)out + 0x18) - 0xc;
            int n = (int)(te - tb);
            char tmp[1024];
            strncpy(tmp, tb, n);
            tmp[n] = 0;
            *(u32*)(rec + 4) = (u32)((int(__thiscall*)(void*, char*))VFN(sys, 0xf4))(sys, tmp);
            u32 k;
            memcpy(&k, tb, 4);
            k = BSWAP(k);
            *(u32*)(rec + 0) = k;
            *(u32*)(rec + 8) = 0;
            if (k == 0x53656e30u && (int)(te - tb) > 6) {
                int n2 = (int)(te - tb) - 6;
                strncpy(tmp, tb + 5, n2);
                tmp[n2] = 0;
                *(u32*)(rec + 8) = (u32)((int(__thiscall*)(void*, char*))VFN(sys, 0xf4))(sys, tmp);
            }
        } while (TokLine(cur, end, ' ', &tb, &te, &cur));
    }

    len = (int)ReadLine((void*)stream, buf, 0x400);
    while (len > 0) {
        char* e2 = buf + len;
        if (!TokLine(buf, e2, '=', &tb, &te, &cur)) return true;
        u32 hash;
        {
            u8 c = (u8)*te; *te = 0;
            hash = FNV1_String8(tb, 0x811c9dc5u, 1);
            *te = (char)c;
        }
        cur += 1;
        if (!TokLine(cur, e2, ':', &tb, &te, &cur)) return true;
        char tmp[1024];
        int n = (int)(te - tb);
        strncpy(tmp, tb, n);
        tmp[n] = 0;
        u32 id = (u32)((int(__thiscall*)(void*, char*))VFN(sys, 0xf4))(sys, tmp);
        u32 key;
        memcpy(&key, tmp, 4);
        key = BSWAP(key);
        cur += 1;
        if (!TokLine(cur, e2, ',', &tb, &te, &cur)) return true;
        u32 num;
        {
            u8 c = (u8)*te; *te = 0;
            num = (u32)atol(tb);
            *te = (char)c;
        }
        ((Vec18_s00a2_af30*)((char*)out + 0x194))->pushEmpty();
        u8* rec = *(u8**)((char*)out + 0x198) - 0x18;
        *(u32*)(rec + 0x00) = hash;
        *(u32*)(rec + 0x04) = num;
        *(u32*)(rec + 0x08) = key;
        *(u32*)(rec + 0x0c) = id;
        cur += 1;
        if (TokLine(cur, e2, ',', &tb, &te, &cur)) {
            u8 c = (u8)*te; *te = 0;
            *(float*)(rec + 0x10) = ParseFloat8(tb);
            *(u32*)(rec + 0x14) |= 1;
            *te = (char)c;
        }
        len = (int)ReadLine((void*)stream, buf, 0x400);
    }
    return true;
}

// @ 0x00a2b7d0
bool Submix_s00a2_af30::Init(void* param)
{
    char* self = (char*)this;
    if (!g_pSystem_s00a2_af30) return false;
    char* esi = (char*)param + 0x14;
    if (!((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x544e850b)) return false;
    if (!((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x2f8b3bf4)) return false;

    void* v = ((void*(__thiscall*)(void*))VFN(g_pSystem_s00a2_af30, 0xbc))(g_pSystem_s00a2_af30);
    if (((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0xed4c265f))
        ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x28))(esi, 0xed4c265f, &v);
    ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x28))(esi, 0xb2550953, self + 0x15f8);
    ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x24))(esi, 0x6b16ae3d, self + 0x15fc);

    void* ws = ((void*(__thiscall*)(void*, int))VFN(esi, 0x3c))(esi, 0x2f8b3bf4);
    if (ws) {
        u32 tmp[4];
        ConvertToString8Impl(tmp, ws, -1);
        cString8Assign(self + 0x988, tmp);
        eastlStringDtor(tmp);
        *(u32*)(self + 0x970) =
            ((int(__thiscall*)(void*, void*))VFN(g_pSystem_s00a2_af30, 0xf4))(g_pSystem_s00a2_af30, *(void**)(self + 0x988));
    }

    if (((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x2fe09c83)) {
        void* sid = ((void*(__thiscall*)(void*, int))VFN(esi, 0x3c))(esi, 0x2fe09c83);
        if (sid) {
            u32 tmp[4];
            ConvertToString8Impl(tmp, sid, -1);
            cString8Assign(self + 0x978, tmp);
            eastlStringDtor(tmp);
            *(u32*)(self + 0x974) =
                ((int(__thiscall*)(void*, void*))VFN(g_pSystem_s00a2_af30, 0xf0))(g_pSystem_s00a2_af30, sid);
        }
    }

    u32 arr[3] = { 0, 0, 0 };
    ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x34))(esi, 0x544e850b, arr);
    arr[1] = 0x29e333b;
    arr[2] = 0x21407ee;

    void* q = 0;
    void* err = ObjectError();
    bool ok = ((bool(__thiscall*)(void*, void**, u32*, int, int, int, int))VFN(err, 0xc))
                  (err, &q, arr, 0, 0, 0, 0);
    if (q) {
        void* r = q;
        q = 0;
        ((void(__thiscall*)(void*))VFN(r, 4))(r);
    }
    if (!ok) return false;

    VoiceContainer_s00a2_af30* vc = (VoiceContainer_s00a2_af30*)(self + 0x10);
    if (!vc->ConstructVoice(v)) {
        RelLocal(&q);
        return false;
    }
    if (*(void**)(self + 0x18) == *(void**)(self + 0x1c)) {
        RelLocal(&q);
        return false;
    }
    {
        u32 name = *(u32*)(self + 0x988);
        char* slot = self + 0x1978;
        *(u32*)slot = name;
        *(void**)(*(void**)(self + 0x18)) = slot;
    }
    fnA34d70(vc, *(void**)(self + 0x974));
    if (((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x8a69beee))
        ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x2c))(esi, 0x8a69beee, self + 0x1608);
    vc->Create(*(u8*)(self + 0x1608));
    if (*(void**)(self + 0x10) == 0) {
        RelLocal(&q);
        return false;
    }

    void* plugins[2] = { 0, 0 };
    ((void(__thiscall*)(void*, int, void**))VFN(g_pSystem_s00a2_af30, 0x184))(g_pSystem_s00a2_af30, 0, plugins);
    vc->MaskPluginBindings(plugins[0], (int)plugins[1]);
    vc->CommitBoundProperties();
    ((void(__thiscall*)(void*, void*))VFN(g_pSystem_s00a2_af30, 0x70))(g_pSystem_s00a2_af30, self + 4);
    *(u8*)(self + 0x998) = 1;
    RelLocal(&q);
    return true;
}

// @ 0x00a2bb30
bool EA::Audio::Submix::Shutdown()
{
    char* self = (char*)this;
    if (g_pSystem_s00a2_af30 && *(u8*)(self + 0x998))
        ((void(__thiscall*)(void*, void*))VFN(g_pSystem_s00a2_af30, 0x74))(g_pSystem_s00a2_af30, self + 4);
    *(u8*)(self + 0x998) = 0;
    ((EA::Audio::VoiceContainer*)(self + 0x10))->Destroy();
    ((EraseVecT*)(self + 0x18))->erase(*(void**)(self + 0x18), *(void**)(self + 0x1c));
    *(u32*)(self + 0x14) = 0;
    *(u32*)(self + 0x10) = 0;
    *(u32*)(self + 0x970) = 0;
    Disconnect(self);

    {
        int* buckets = *(int**)(self + 0x9a0);
        u32 n = *(u32*)(self + 0x9a4);
        int* p = buckets;
        int node = *p;
        if (node == 0) { do { ++p; node = *p; } while (node == 0); }
        int endNode = buckets[n];
        while (node != endNode) {
            void* obj = *(void**)(node + 4);
            if (((void*(__thiscall*)(void*))VFN(obj, 0x30))(obj) == self)
                ((void(__thiscall*)(void*))VFN(obj, 0x14))(obj);
            node = *(int*)(node + 8);
            while (node == 0) { ++p; node = *p; }
        }
    }

    ((PHTable_s00a2_af30*)(self + 0x99c))->FreeBuckets((void**)*(void**)(self + 0x9a0), *(u32*)(self + 0x9a4));
    *(u32*)(self + 0x99c + 0xc) = 0;
    ((SubTable_s00a2_af30*)(self + 0xdd4))->DoFreeNodes(*(void**)(self + 0xdd4 + 4), *(void**)(self + 0xdd4 + 8));
    *(u32*)(self + 0xde0) = 0;
    return true;
}

// @ 0x00a2bc40
bool __stdcall FactoryInstrumentBank_ReadResource(void* obj, InstOut* out, int, int)
{
    if (!obj || !out) return false;
    int stream = ((int(__thiscall*)(void*))VFN(obj, 0x18))(obj);
    if (!stream) return false;

    u32* hdr = (u32*)((void*(__thiscall*)(void*))VFN(obj, 0x10))(obj);
    out->h0 = hdr[0];
    out->h1 = hdr[1];
    out->h2 = hdr[2];

    char buf[1024];
    if (!ReadLine((void*)stream, buf, 0x400)) return false;
    if (atol(buf) != 1) return false;
    int len = (int)ReadLine((void*)stream, buf, 0x400);
    while (len > 0) {
        if (buf[0] != '#') {
            Zone_s00a2_af30 z;
            sscanf(buf, "%f %f %f %f %f %f %x %x %x %x %x %x",
                   &z.f[0], &z.f[1], &z.f[2], &z.f[3], &z.f[4], &z.f[5],
                   &z.h[0], &z.h[1], &z.h[2], &z.h[3], &z.h[4], &z.h[5]);
            z.extra[0] = z.h[0];
            z.extra[1] = 0x1a527db;
            z.extra[2] = 0x21407ee;
            if (((bool(__thiscall*)(void*, Zone_s00a2_af30*))VFN(g_pSystem_s00a2_af30, 0x188))(g_pSystem_s00a2_af30, &z)) {
                int r = ((int(__thiscall*)(void*, u32))VFN(g_pSystem_s00a2_af30, 0x1a4))(g_pSystem_s00a2_af30, z.h[0]);
                if (out->lastId == -1 && r != -1)
                    out->lastId = r;
            }
            out->zones.push_back(&z);
        }
        len = (int)ReadLine((void*)stream, buf, 0x400);
    }
    return true;
}

// @ 0x00a2be10
void EA::Audio::System::StopAllSounds(bool param)
{
    char* self = (char*)this;
    VecP v;
    v.begin = 0;
    v.end   = 0;
    v.cap   = 0;

    void** anchor = (void**)(self + 0x157438);
    char* raw  = (char*)*anchor;         // first node (+0x10 into object)
    char* stop = (char*)anchor;          // sentinel node link address
    while (raw != stop) {
        char* obj = raw - 0x10;
        if (v.end < v.cap) {
            *v.end++ = obj;
        } else {
            ((SimpleVec*)&v)->DoInsertValue(v.end, (void**)&obj);
        }
        raw = *(char**)raw;              // link field == stored node pointer
    }

    void** it = v.end;
    while (it != v.begin) {
        void* obj = *--it;
        if (obj) {
            ((void(__thiscall*)(void*))VFN(obj, 0))(obj);
            ((void(__thiscall*)(void*, int, int))VFN(obj, 0x18))(obj, 3, param);
            ((void(__thiscall*)(void*))VFN(obj, 4))(obj);
        }
    }
    if (v.begin && ((u32*)v.begin)[-1]) operator_delete(v.begin);
}

// @ 0x00a2bf30
void System_s00a2_af30::InsertSound(void* item)
{
    if (!item) return;
    ((void(__thiscall*)(void*))VFN(item, 0))(item);

    SoundList_s00a2_af30* list = (SoundList_s00a2_af30*)((char*)this + 0x157c60);
    SoundNode* node = list->mpFree;
    if (node) {
        list->mpFree = node->mpNext;
    } else {
        unsigned nNodeSize = list->mnNodeSize;
        node = (SoundNode*)::operator new(nNodeSize, "EASTL", 0, 0,
                                          EASTL_FILE, 0xd1);
    }
    void** body = (void**)((char*)node + 8);
    if (body) *body = item;
    node->mpNext = (SoundNode*)&list->mHead;      // next = sentinel address
    node->mpPrev = list->mHead.mpPrev;
    list->mHead.mpPrev->mpNext = node;            // old last -> new node
    list->mHead.mpPrev = node;
}

// @ 0x00a2bfa0
bool Sys_s00a2_bfa0::GetTextureInstance(const Key_s00a2_bfa0* key, void** out)
{
    void* iter[2];
    texTable.find(iter, key);
    if (iter[0] != texTable.buckets[texTable.count]) {
        void* val = *(void**)((char*)iter[0] + 0xc);
        if (!val) return false;
        if (out) {
            NotifyTex(key);
            ((void(__thiscall*)(void*))VFN(val, 0))(val);
            *out = val;
        }
        return true;
    }

    void* tmp = 0;
    void* err = ObjectError();
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
    bool ok = ((bool(__thiscall*)(void*, const Key_s00a2_bfa0*, void**, int, int, int, int))VFN(err, 0xc))
                  (err, key, &tmp, 0, 0, 0, 0);

    struct Pair { Key_s00a2_bfa0 k; void* v; } pair;
    pair.k = *key;
    pair.v = tmp;
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 0))(tmp);
    u32 ins[2];
    texTable.insert(ins, &pair, 0);
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);

    if (!ok) {
        if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
        return false;
    }
    if (out) {
        NotifyTex(key);
        ((void(__thiscall*)(void*))VFN(tmp, 0))(tmp);
        *out = tmp;
    }
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
    return true;
}

// @ 0x00a2c140
void Sys_s00a2_bfa0::Update()
{
    char* self = (char*)this;
    char* obj  = *(void**)(self + 0x157438) ? (char*)(*(void**)(self + 0x157438)) - 0x10 : 0;
    char* stop = self + 0x157438 - 0x10;

    while (obj != stop) {
        if (((*(u8*)(obj + 0xce4) & 0x10) != 0) &&
            ((ObjFn*)obj)->check() &&
            ((ObjFn*)obj)->check2() == 0) {
            if (!g_vecInit) {
                g_vecInit = 1;
                g_vecBegin = 0; g_vecEnd = 0; g_vecCap = 0;
                _atexit(0);                                   // 0x013c17f0
            }
            void** first = *(void***)(obj + 0xc7c);
            void** last  = *(void***)(obj + 0xc80);
            for (void** it = first; it != last; ++it) {
                void* e = *it;
                if (e) ((void(__thiscall*)(void*))VFN(e, 0))(e);
                bool keep = !((bool(__thiscall*)(void*, void*))VFN(e, 0xc4))(e, obj);
                if (keep) {
                    if (g_vecEnd < g_vecCap) {
                        *g_vecEnd++ = e;
                    } else {
                        ((PtrVec*)&g_vecBegin)->DoInsertValue(g_vecEnd, &e);
                    }
                }
                if (e) ((void(__thiscall*)(void*))VFN(e, 4))(e);
            }
            for (void** it = g_vecBegin; it != g_vecEnd; ++it) {
                void* e = *it;
                if (e) ((void(__thiscall*)(void*))VFN(e, 0))(e);
                ((void(__thiscall*)(void*))VFN(e, 0xc0))(e);
                if (e) ((void(__thiscall*)(void*))VFN(e, 4))(e);
            }
            vecBoolClear(g_vecBegin, g_vecEnd, 0);
            g_vecEnd -= (g_vecEnd - g_vecBegin);

            void* tmp = 0;
            if (((bool(__thiscall*)(void*, void**))VFN(this, 0x150))(this, &tmp)) {
                if (((*(u8*)(obj + 0xce4) & 0x20) != 0) && *(void**)(obj + 0x44)) {
                    void* p = *(void**)(obj + 0x44);
                    ((void(__thiscall*)(void*))VFN(p, 0x18))(p);
                    ((void(__thiscall*)(void*, int))VFN(p, 0x38))(p, 0);
                    if (p) { *(void**)(obj + 0x44) = 0;
                             ((void(__thiscall*)(void*))VFN(p, 4))(p); }
                    *(u32*)(obj + 0xce4) &= ~0x20u;
                }
                if ((*(u8*)(obj + 0xce4) & 8) != 0) {
                    *(u32*)(obj + 0xce4) &= ~8u;
                    ((void(__thiscall*)(void*, void*))VFN(this, 0x74))(this, obj);
                }
                void** f2 = *(void***)(obj + 0xc7c);
                void** l2 = *(void***)(obj + 0xc80);
                for (void** it = f2; it != l2; ++it) {
                    void* e = *it;
                    if (e) ((void(__thiscall*)(void*))VFN(e, 0))(e);
                    ((void(__thiscall*)(void*, int))VFN(e, 0xd4))(e, 0);
                    ((void(__thiscall*)(void*, void*))VFN(this, 0xb8))(this, e);
                    ((void(__thiscall*)(void*))VFN(e, 4))(e);
                }
                vecBoolClear(*(void***)(obj + 0xc7c), *(void***)(obj + 0xc80), 0);
                *(u32*)(obj + 0xc80) -= (*(u32*)(obj + 0xc80) - *(u32*)(obj + 0xc7c));
                ((void(__thiscall*)(void*, void*))VFN(tmp, 0xb8))(tmp, obj);
            }
            if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
        }
        obj = *(void**)(obj + 0x10) ? (char*)(*(void**)(obj + 0x10)) - 0x10 : 0;
    }
}

// @ 0x00a2c450
bool Sys_s00a2_bfa0::GetAudioA(u32 key, u32 param)
{
    void* iter[2];
    audioTable.find(iter, &key);
    void* val = 0;
    if (iter[0] != audioTable.buckets[audioTable.count]) {
        val = *(void**)((char*)iter[0] + 4);
        if (val) ((void(__thiscall*)(void*))VFN(val, 0))(val);
    } else {
        void* mem = eaNew(0x1874, "Audio", 0, 0, 0, 0);
        void* nw = mem ? ((CtorT*)mem)->ctor(key) : 0;
        if (nw) {
            ((void(__thiscall*)(void*))VFN(nw, 0))(nw);
            val = nw;
        }
        ((void(__thiscall*)(void*))VFN(val, 0x20))(val);
        void** slot = (void**)audioTable.GetOrInsert(&key);
        void* old = *slot;
        if (val != old) {
            ((void(__thiscall*)(void*))VFN(val, 0))(val);
            *slot = val;
            if (old) ((void(__thiscall*)(void*))VFN(old, 4))(old);
        }
        ((void(__thiscall*)(void*, void*))VFN(this, 0x16c))(this, val);
    }
    u8 r = ((u8(__thiscall*)(void*, u32))VFN(val, 0x28))(val, param);
    ((void(__thiscall*)(void*))VFN(val, 4))(val);
    return r != 0;
}

// @ 0x00a2c590
bool Sys_s00a2_bfa0::GetAudioB(u32 key)
{
    void* iter[2];
    audioTable.find(iter, &key);
    if (iter[0] != audioTable.buckets[audioTable.count])
        return false;

    void* mem = eaNew(0x1874, "Audio", 0, 0, 0, 0);
    void* nw = mem ? ((CtorT*)mem)->ctor(key) : 0;
    if (nw) ((void(__thiscall*)(void*))VFN(nw, 0))(nw);
    ((void(__thiscall*)(void*))VFN(nw, 0x20))(nw);
    void** slot = (void**)audioTable.GetOrInsert(&key);
    void* old = *slot;
    if (nw != old) {
        ((void(__thiscall*)(void*))VFN(nw, 0))(nw);
        *slot = nw;
        if (old) ((void(__thiscall*)(void*))VFN(old, 4))(old);
    }
    ((void(__thiscall*)(void*, void*))VFN(this, 0x16c))(this, nw);
    ((void(__thiscall*)(void*))VFN(nw, 4))(nw);
    return true;
}

// @ 0x00a2c6c0
namespace EA { namespace Audio {
bool System_s00a2_c6c0::DoCommand(Command_s00a2_c6c0* cmd)
{
    vcall<void>(this, 0x1ec, cmd);
    switch (cmd->Type()) {

    case 0x3475331: {
        u32 id, handle;
        cmd->GetUint32(0x3475381, &id);
        cmd->GetUint32(0x3475385, &handle);
        Vec3 pos;
        Vec3* ppos = 0;
        if (cmd->GetVector3(0x39e41ea, &pos.x))
            ppos = &pos;
        if (vcall<bool>(this, 0x94, id, handle, 0, ppos, 0))
            break;
        mLookup.Find(id);
        vcall<void>(this, 0x98, handle, true);
        return false;
    }

    case 0x3475365: {
        u32 handle;
        if (!cmd->GetUint32(0x3475385, &handle))
            return false;
        if (!vcall<bool>(this, 0x200, cmd, handle))
            vcall<void>(this, 0x128, 0x3a129ee, handle, 0, 0, 0);
        break;
    }

    case 0x347536b:
    case 0x3a12a81: {
        u32 handle, flag;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetUint32(0x34753a0, &flag);
        vcall<void>(this, 0x98, handle, flag != 0);
        break;
    }

    case 0x347536f: {
        u32 handle; float v;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetFloat(0x34753a4, &v);
        vcall<void>(this, 0xa0, handle, v);
        break;
    }

    case 0x3475373: {
        u32 handle; float a, b, c;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetFloat(0x3475391, &a);
        cmd->GetFloat(0x3475395, &b);
        cmd->GetFloat(0x3475398, &c);
        vcall<void>(this, 0xa4, handle, a, b, c);
        break;
    }

    case 0x3475376: {
        u32 a, b, e = 0;
        float f;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        if (cmd->SetT1(0x34753ad, 0, 0))
            cmd->GetUint32(0x34753ad, &e);
        cmd->GetFloat(0x34753aa, &f);
        vcall<void>(this, 0xac, a, b, f, e != 0);
        break;
    }

    case 0x347537a: {
        u32 a, b, size;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        void* data = cmd->GetData(0x34753b0, &size);
        vcall<void>(this, 0xa8, a, b, data, size);
        break;
    }

    case 0x399197f: {
        u32 handle;
        cmd->GetUint32(0x3475385, &handle);
        vcall<void>(this, 0xd8, handle, cmd->GetString8(0x347537e));
        break;
    }

    case 0x3991984: {
        u32 handle; float v;
        cmd->GetUint32(0x3475385, &handle);
        cmd->GetFloat(0x34753aa, &v);
        vcall<void>(this, 0xe0, handle, v);
        break;
    }

    case 0x3cdd1a9: {
        u32 a; float v;
        cmd->GetUint32(0x34753a7, &a);
        cmd->GetFloat(0x34753aa, &v);
        vcall<void>(this, 0xfc, a, v);
        break;
    }

    case 0x3992099: {
        u32 listener = 0;
        Vec3 pos;
        Mat33 mat;
        cmd->GetUint32(0x490d2eb, &listener);
        cmd->GetVector3(0x3abafae, &pos.x);
        mListenerPos[listener] = pos;
        cmd->GetMatrix33(0x39e41fc, mat.m);
        mListenerMat[listener] = mat;
        break;
    }

    case 0x407ab38: {
        u32 a, b;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        vcall<void>(this, 0x1d8, a, b);
        break;
    }

    case 0x407ab40: {
        u32 a, b;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x34753a7, &b);
        vcall<void>(this, 0x1dc, a, b);
        break;
    }

    case 0x42c8c77: {
        u32 a, b, c = 0, d = 1;
        cmd->GetUint32(0x3475385, &a);
        cmd->GetUint32(0x42c8c8b, &b);
        cmd->GetUint32(0x47fc2f4, &c);
        cmd->GetUint32(0x47fc2fa, &d);
        void* obj = vcall<void*>(this, 0x1d4, a);
        if (obj)
            vcall<void>(obj, 0x1c, b != 0, c, -1.0f, d != 0);
        break;
    }

    case 0x435b26d:
        mbFlag3fc = 1;
        break;

    case 0x436201e: {
        u32 handle;
        u32 info[3] = { 0, 0, 0 };
        cmd->GetUint32(0x4362059, &info[1]);
        cmd->GetUint32(0x3475385, &info[0]);
        cmd->GetUint32(0x4362049, &info[2]);
        vcall<void>(this, 0x1bc, info);
        cmd->GetUint32(0x3475385, &handle);
        Sound_s00a2_c6c0* s   = FromNode(mSounds.anchor.next);
        Sound_s00a2_c6c0* end = FromNode(&mSounds.anchor);
        while (s != end) {
            if (vcall<bool>(s, 0x38, handle))
                vcall<void>(s, 0x34);
            s = NextSound(s);
        }
        break;
    }

    case 0x437419c: {
        u32 a = 0, b = 0, c = 0;
        VisualEffectRef ref;
        cmd->GetUint32(0x43741f1, &a);
        cmd->GetUint32(0x43741ff, &b);
        cmd->GetUint32(0x43743cb, &c);
        if (a == 0 || b == 0 || c == 0)
            break;
        HashIter it = mStyleTable.find(b);
        if (it.node == mStyleTable.mpBucketArray[mStyleTable.mnBucketCount])
            break;
        void* style = it.node->value;
        if (vcall<bool>(this, 0xe4, a, ref.AsPPTypeParam()))
            vcall<void>(style, 0x18, c, ref.mp);
        break;
    }

    case 0x43741d8: {
        u32 a = 0, b = 0, c = 0;
        VisualEffectRef ref;
        cmd->GetUint32(0x43741f1, &a);
        cmd->GetUint32(0x43741ff, &b);
        cmd->GetUint32(0x43743cb, &c);
        if (a == 0 || b == 0 || c == 0)
            break;
        HashIter it = mStyleTable.find(b);
        if (it.node == mStyleTable.mpBucketArray[mStyleTable.mnBucketCount])
            break;
        void* style = it.node->value;
        if (vcall<bool>(this, 0xe4, a, ref.AsPPTypeParam()))
            vcall<void>(style, 0x1c, c, ref.mp);
        break;
    }

    case 0x44888b0: {
        u32 flag = 0;
        cmd->GetUint32(0x34753a0, &flag);
        vcall<void>(this, 0x80, flag != 0);
        break;
    }

    case 0x44888b5: {
        SoundIter s = mSounds.begin();
        SoundIter e = mSounds.end();
        while (s.p != e.p) {
            if (vcall<bool>(s.p, 0x20, -1, 0))
                vcall<void>(s.p, 0x80, 3, 0);
            s.p = NextSound(s.p);
        }
        break;
    }

    case 0x44f2b21: {
        u32 id, b;
        u32 c = 0, d = 1;
        cmd->GetUint32(0x3475385, &id);
        cmd->GetUint32(0x42c8c8b, &b);
        cmd->GetUint32(0x47fc2f4, &c);
        cmd->GetUint32(0x47fc2fa, &d);
        bool bB = b != 0;
        bool bD = d != 0;
        SoundIter s = mSounds.begin();
        SoundIter e = mSounds.end();
        while (s.p != e.p) {
            if (vcall<bool>(s.p, 0x3c, id))
                vcall<void>(s.p, 0x1c, bB, c, 2.0f, bD);
            s.p = NextSound(s.p);
        }
        UIntVector& v = mUIntVector;
        u32* p = v.mpBegin;
        u32* last = v.mpEnd;
        for (; p != last; ++p) {
            if (*p == id) {
                if (b == 0) {
                    *p = last[-1];
                    --v.mpEnd;
                }
                goto done;
            }
        }
        if (v.mpEnd < v.mpCapacity)
            ::new((void*)v.mpEnd++) u32(id);
        else
            v.DoInsertValue(v.mpEnd, id);
        break;
    }

    case 0x45010e7: {
        u32 a, b, c;
        void* p = 0;
        void* q = 0;
        cmd->GetUint32(0x4501144, &a);
        cmd->GetUint32(0x4502374, &b);
        cmd->GetUint32(0x4597e49, &c);
        cmd->GetVoidPtr(0x45705b8, &p);
        cmd->GetVoidPtr(0x45706c7, &q);
        vcall<void>(this, 0x1f8, a, c, b, p, q);
        break;
    }

    case 0x4503efa: {
        u32 a;
        cmd->GetUint32(0x4501144, &a);
        vcall<void>(this, 0x1fc, a);
        break;
    }

    case 0x4640907: {
        u32 a, size;
        u32 n = 0;
        void* p = 0;
        void* q = 0;
        cmd->GetUint32(0x4501144, &a);
        cmd->GetVoidPtr(0x45705b8, &p);
        cmd->GetVoidPtr(0x45706c7, &q);
        void* data = cmd->GetData(0x4501150, &size);
        if (data)
            n = size >> 2;
        vcall<void>(this, 0x1f4, a, data, n, p, q);
        break;
    }

    case 0x4fe2220: {
        u32 a;
        cmd->GetUint32(0x4362049, &a);
        vcall<void>(this, 0x120, a);
        break;
    }

    case 0x566783b: {
        u32 a, e = 0;
        float f;
        cmd->GetUint32(0x34753a7, &a);
        if (cmd->SetT1(0x34753ad, 0, 0))
            cmd->GetUint32(0x34753ad, &e);
        cmd->GetFloat(0x34753aa, &f);
        vcall<void>(this, 0xb0, a, f, e != 0);
        break;
    }

    case 0x60c62f5: {
        u32 size;
        u32* ids = (u32*)cmd->GetData(0x60c631d, &size);
        if (ids) {
            for (u32 remaining = size >> 2; remaining != 0; --remaining) {
                u32 id = *ids++;
                VisualEffectRef ref;
                if (vcall<bool>(this, 0x138, id, ref.AsPPTypeParam(), 0x21407ee)) {
                    u32 count;
                    Key* keys;
                    if (vcall<bool>(ref.mp, 0x4c, 0x701ed91e, &count, &keys) && count != 0) {
                        for (u32 i = 0; i < count; ++i) {
                            Key k = *keys++;
                            k.type = 0x1a527db;
                            k.group = 0x21407ee;
                            vcall<void>(this, 0x194, &k, 0, 0);
                        }
                    }
                } else {
                    Key k;
                    k.instance = id;
                    k.type = 0x1a527db;
                    k.group = 0x21407ee;
                    vcall<void>(this, 0x194, &k, 0, 0);
                }
            }
        }
        break;
    }

    case 0x673a543: {
        u32 a, b;
        cmd->GetUint32(0x4362049, &a);
        cmd->GetUint32(0x3475385, &b);
        vcall<void>(this, 0x104, a, b);
        break;
    }

    case 0x673a567: {
        u32 a, b;
        cmd->GetUint32(0x4362049, &a);
        cmd->GetUint32(0x3475385, &b);
        vcall<void>(this, 0x10c, a, b);
        break;
    }

    case 0x7ead55c: {
        u32 a;
        if (cmd->GetUint32(0x4362049, &a)) {
            SoundIter s = mSounds.begin();
            SoundIter e = mSounds.end();
            while (s.p != e.p) {
                if (vcall<bool>(s.p, 0x3c, a))
                    vcall<void>(s.p, 0x80, 3, 0);
                s.p = NextSound(s.p);
            }
        }
        break;
    }

    case 0x7f43dc0:
        cmd->GetVector3(0x39e41ea, &mVec15bbe4.x);
        mbHasVec15bbe4 = 1;
        break;

    case 0x7f43dd0:
        mbHasVec15bbe4 = 0;
        break;
    }
done:
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a2d790
bool EA::Audio::System::RegisterPrimitive(EA::Audio::IPrimitive * p)
{
    if (!p) return false;
    typedef char (__thiscall *F0)(void*);
    if (!((F0)vc_s00a2_d790(p, 0x10))(p)) return false;
    uint id = ((uint (__thiscall*)(void*))vc_s00a2_d790(p, 0x18))(p);
    uint key = id;
    void* it = 0;
    ((XF*)((uchar*)this + 0x13f4))->hashtable_find(&key, &it);
    if (*(uint*)it != *(uint*)(*(uint*)((uchar*)this + 0x13f8) +
                              *(int*)((uchar*)this + 0x13fc) * 4))
        return false;
    void* elem = ((XF*)((uchar*)this + 0x13f4))->FUN_00a2a150(&key);
    ((XF*)elem)->AutoRef_op(&key);
    ((void (__thiscall*)(void*, uint))vc_s00a2_d790(this, 0x38))(this, 0x399197f);
    ((void (__thiscall*)(void*, uint, uint))vc_s00a2_d790(this, 0x40))(this, 0x3475385, id);
    ((void (__thiscall*)(void*))vc_s00a2_d790(this, 0x58))(this);
    ((void (__thiscall*)(void*, uint))vc_s00a2_d790(this, 0x38))(this, 0x3991984);
    ((void (__thiscall*)(void*, uint, uint))vc_s00a2_d790(this, 0x40))(this, 0x3475385, id);
    float f = ((float (__thiscall*)(void*))vc_s00a2_d790(p, 0x1c))(p);
    ((void (__thiscall*)(void*, uint, float))vc_s00a2_d790(this, 0x3c))(this, 0x34753aa, f);
    ((void (__thiscall*)(void*))vc_s00a2_d790(this, 0x58))(this);
    return true;
}

// @ 0x00a2d880
bool AudioSystem::FUN_00a2d880(uint key, void* out)
{
    void* it[2];   // returned iterator (node + bucket count)
    ((XF*)((uchar*)this + 0x23e4))->hashtable_find(it, &key);
    if (it[0] != *(void**)(*(uint*)((uchar*)this + 0x23e8) +
                           *(int*)((uchar*)this + 0x23ec) * 4))
        return false;
    void* node = FUN_00a17090(0x1c);
    if (node) node = ((void* (__thiscall*)(void*, void*))FUN_00a17100)(node, this);
    ((void (__thiscall*)(void*))vc_s00a2_d790(node, 0))(node);
    void* slot = ((XF*)((uchar*)this + 0x23e4))->FUN_00a2a510(&key);
    *(void**)slot = node;
    return true;
}

// the constructor's view of the 0x00a2d940 object: a base (vtable 0x13eb394, restored if construction fails), its own
// vtable, and the tree at +4 built from `arg` by its out-of-line constructor (0x00a26fa0)
struct TreeObjBase_00a2d940 { virtual void Slot0(); ~TreeObjBase_00a2d940() {} };
struct TreeObjTree_00a2d940 { char d[0x1c]; TreeObjTree_00a2d940(void* arg); ~TreeObjTree_00a2d940(); };
struct TreeObj_00a2d940 : TreeObjBase_00a2d940 {
    TreeObjTree_00a2d940 mTree;   // +4
    TreeObj_00a2d940(void* arg);
};

// @ 0x00a2d940
TreeObj_00a2d940::TreeObj_00a2d940(void* arg)
    : mTree(arg)
{
}

// @ 0x00a2d990
int AudioSystem::FUN_00a2d990(void* arg)
{
    if (*(int*)((uchar*)arg + 8) == 0x21407ee) {
        void* out;
        int* r = (int*)((XF*)((uchar*)this + 4))->rbtree_find(&out, (uchar*)arg + 4);
        if ((uchar*)this + 8 != (uchar*)*r)
            return 1;
    }
    return 0;
}

// Deleting destructor of a set holder (0x00a2d9d0): no own vtable store (novtable); the rb-tree set at +4 frees its
// nodes (0x9a9600), the base restores its vtable, then the object is freed (nothrow).
void SetHolderFree_a2d9d0(void* p) throw();   // 0xf47380
struct SetTree_a2d9d0 {
    char  mAnchor[0xc];
    void* mpRoot;                              // +0x0c
    char  rest[8];
    void DoNukeSubtree(void* node);            // 0x009a9600
    ~SetTree_a2d9d0() { DoNukeSubtree(mpRoot); }
};
struct SetHolderBase_a2d9d0 { virtual void v0(); ~SetHolderBase_a2d9d0() { (void)this; } };
struct __declspec(novtable) SetHolderView_a2d9d0 : SetHolderBase_a2d9d0 {
    SetTree_a2d9d0 mSet;                       // +0x04
    ~SetHolderView_a2d9d0() {}
    void* DeletingDtor(uchar flags);
};

// @ 0x00a2d9d0
void* SetHolderView_a2d9d0::DeletingDtor(uchar flags)
{
    this->~SetHolderView_a2d9d0();
    if (flags & 1) SetHolderFree_a2d9d0(this);
    return this;
}

// @ 0x00a2da30
void AudioSystem::FUN_00a2da30()
{
    // Body skipped: 525-byte EASTL hashtable iteration with EH cleanup.
    // Kept as a compiling approximation (see partial.txt).
    return;
}

// @ 0x00a2dc40
void EA::Audio::System::SetupPropertyAggregationRules()
{
    return;
}

// @ 0x00a2de20
bool EA::Audio::System::DestroySubmixes()
{
    if (DAT_016e61a8) FUN_0112c600();
    uint* begin = *(uint**)((uchar*)this + 0x119ba4);
    uint* end = *(uint**)((uchar*)this + 0x119ba8);
    for (uint* it = begin; it != end; ++it) {
        void* o = (void*)*it;
        if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 0))(o);
        ((XF*)o)->FUN_00a21390();
        ((void (__thiscall*)(void*, void*))vc_s00a2_d790(this, 0x170))(this, o);
        if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 4))(o);
    }
    for (uint* it = *(uint**)((uchar*)this + 0x119ba4),
             * ie = *(uint**)((uchar*)this + 0x119ba8); it != ie; ++it) {
        void* o = (void*)*it;
        if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 0))(o);
        ((XF*)o)->FUN_00a2bb30();
        if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 4))(o);
    }
    // vector::erase(begin(), end()): move nothing, destroy the tail, drop the size
    uint* first = *(uint**)((uchar*)this + 0x119ba4);
    uint* last = *(uint**)((uchar*)this + 0x119ba8);
    uint* newEnd = (uint*)copy_impl(last, last, first);
    uint* tail = *(uint**)((uchar*)this + 0x119ba8);
    for (uint* p = newEnd; p < tail; ++p) {
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 4))(o);
    }
    *(uint**)((uchar*)this + 0x119ba8) = first;
    if (DAT_016e61a8) FUN_0112c620();
    return true;
}

struct Ref4_s00a2_dfe0 {
    void* p;
    Ref4_s00a2_dfe0(const Ref4_s00a2_dfe0& o) : p(o.p)
    {
        if (p) ((void (__thiscall*)(void*))vc_s00a2_d790(p, 4))(p);
    }
    static void* operator new(size_t, void* q) throw() { return q; }
    static void operator delete(void*, void*) throw() {}
};

struct Ref4Vec_a2dfe0 {
    void* mAlloc;                               // +0x00
    Ref4_s00a2_dfe0* mpEnd;                     // +0x04
    Ref4_s00a2_dfe0* mpCapacity;                // +0x08
};

// @ 0x00a2dfe0
void AudioSystem::FUN_00a2dfe0(void* p)
{
    Ref4Vec_a2dfe0* v = (Ref4Vec_a2dfe0*)this;
    if (v->mpEnd < v->mpCapacity)
        new (v->mpEnd++) Ref4_s00a2_dfe0(*(const Ref4_s00a2_dfe0*)p);
    else
        ((XF*)this)->FUN_00a2ac20(v->mpEnd, p);
}

// @ 0x00a2e060
uint& AudioSystem::FUN_00a2e060(const uint& k)
{
    struct Node { Node* left; Node* right; Node* parent; int color; uint key; uint value; };
    Node* header = (Node*)((uchar*)this + 4);
    Node* node = header->parent;
    Node* cand = header;
    while (node) {
        if (node->key < k) node = node->left;
        else { cand = node; node = node->right; }
    }
    if (cand != header && k <= cand->key) return cand->value;
    // insert (approximation of rbtree DoInsertValue)
    Node* n = (Node*)operator_new(0x18, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/rbtree.h", 0x2d1);
    n->left = n->right = n->parent = 0; n->color = 1; n->key = k; n->value = 0;
    // link as child of cand
    n->parent = cand;
    if (cand == header) header->parent = n;
    else if (k < cand->key) cand->left = n;
    else cand->right = n;
    return n->value;
}

struct E0Sub_s00a2_e0e0 { void* sub; E0Sub_s00a2_e0e0* next; };
struct E0Tree_s00a2_e0e0 { void DoNukeSubtree(void* n); };

// @ 0x00a2e0e0
int AudioSystem::FUN_00a2e0e0(uint* p)
{
    uchar* ht = (uchar*)this;
    int before = *(int*)(ht + 0xc);
    uint idx = *p % *(uint*)(ht + 8);
    uchar** bucket = (uchar**)(*(int*)(ht + 4) + idx * 4);
    while (*bucket && *(uint*)*bucket != *p) {
        uchar* n = *bucket;
        bucket = (uchar**)(n + 0x24);
    }
    while (*bucket) {
        uchar* node = *bucket;
        if (*(uint*)node != *p) break;
        *bucket = *(uchar**)(node + 0x24);
        for (E0Sub_s00a2_e0e0* s = *(E0Sub_s00a2_e0e0**)(node + 0x14); s; ) {
            ((E0Tree_s00a2_e0e0*)(node + 8))->DoNukeSubtree(s->sub);
            E0Sub_s00a2_e0e0* nx = s->next;
            EaDelete(s);
            s = nx;
        }
        if (node != *(uchar**)(ht + 0x30)) {
            if (node >= *(uchar**)(ht + 0x24) && node < *(uchar**)(ht + 0x28)) {
                *(uchar**)node = *(uchar**)(ht + 0x1c);
                *(uchar**)(ht + 0x1c) = node;
            } else {
                EaDelete(node);
            }
        }
        *(int*)(ht + 0xc) -= 1;
    }
    return before - *(int*)(ht + 0xc);
}

// @ 0x00a2e1b0
void* AudioSystem::FUN_00a2e1b0(void* out, void* node, void* parent)
{
    int* o = (int*)out;
    int* par = (int*)parent;
    int iVar1 = par[9];
    o[1] = (int)parent;
    *o = iVar1;
    while (iVar1 == 0) {
        o[1] += 4;
        iVar1 = *(int*)o[1];
        *o = iVar1;
    }
    int* puVar2 = (int*)*par;
    if (puVar2 == node) {
        *par = puVar2[9];
    } else {
        for (int* puVar3 = (int*)puVar2[9]; puVar3 != node; puVar3 = (int*)puVar3[9])
            puVar2 = puVar3;
        puVar2[9] = ((int*)node)[9];
    }
    operator_delete(node);
    *(int*)((uchar*)this + 0xc) -= 1;
    return out;
}

struct EventMsgVec_a2e260 {
    void* mAlloc;                               // +0x00
    EventMsg* mpEnd;                            // +0x04
    EventMsg* mpCapacity;                       // +0x08
};

// @ 0x00a2e260
void AudioSystem::FUN_00a2e260(void* p)
{
    EventMsgVec_a2e260* v = (EventMsgVec_a2e260*)this;
    if (v->mpEnd < v->mpCapacity)
        new (v->mpEnd++) EventMsg(*(const EventMsg*)p);
    else
        ((XF*)this)->FUN_00a2af30(v->mpEnd, p);
}

// @ 0x00a2e2f0
AudioSystem* AudioSystem::FUN_00a2e2f0(void* p)
{
    (void)p;
    return this;
}

// @ 0x00a2e420
void* AudioSystem::FUN_00a2e420(void* p)
{
    void* node = *(void**)((uchar*)this + 0x1c);
    if (node) {
        *(void**)((uchar*)this + 0x1c) = *(void**)node;
    } else {
        node = operator_new(*(uint*)((uchar*)this + 0x2c), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    if (node) {
        *(uint*)node = *(uint*)p;
        *(uint*)((uchar*)node + 4) = *(uint*)((uchar*)p + 4);
        ((XF*)((uchar*)node + 8))->FUN_00a26fa0((uchar*)p + 8);
    }
    *(uint*)((uchar*)node + 0x24) = 0;
    return node;
}

// @ 0x00a2e4c0
void* AudioSystem::FUN_00a2e4c0(void* p)
{
    RDD* self = (RDD*)this;
    ProfileTimer local((void*)((char*)this + 0x5c));
    self->mMutex.Lock((void*)0x1452970);
    {
        long long e = local.sw.GetElapsedTimeFloat();
        self->mfAccum = (float)e * local.sw.mfCyclesToUnitsCoefficient + self->mfAccum;
    }
    for (void** it = self->mpBegin; it != self->mpEnd; ++it) {
        void* elem = *it;
        if (elem == p) {
            self->mMutex.Unlock();
            long long e = local.sw.GetElapsedTimeFloat();
            float* acc = (float*)local.mpAccumulator;
            *acc = (float)e * local.sw.mfCyclesToUnitsCoefficient + *acc;
            return elem;
        }
    }
    void* tmp = p;
    if (tmp) ((void (__thiscall*)(void*))vc_s00a2_d790(tmp, 4))(tmp);
    ((AudioSystem*)((char*)this + 0x14))->FUN_00a2dfe0(&tmp);
    if (tmp) ((void (__thiscall*)(void*))vc_s00a2_d790(tmp, 8))(tmp);
    self->mMutex.Unlock();
    {
        long long e = local.sw.GetElapsedTimeFloat();
        float* acc = (float*)local.mpAccumulator;
        *acc = (float)e * local.sw.mfCyclesToUnitsCoefficient + *acc;
    }
    return p;
}

// @ 0x00a2e650
bool MgrBase::Create(unsigned name, unsigned id, void* existing, float* pos, void** out)
{
    if (name == 0 || id == 0)
        return false;

    FxRef ve;
    ve = VCALL(void*(__thiscall*)(MgrBase*, unsigned), this, 0x1d4)(this, id);
    if (ve.p) {
        if (out) {
            *out = ve.p;
            ObjAddRef(ve.p);
        }
        return true;
    }

    memset(&g_g48, 0, 0x48);
    static Props s_props;
    if (s_props.m10 == 0) {
        FxRef pl;
        bool ok = VCALL(bool(__thiscall*)(MgrBase*, unsigned, void**, unsigned), this, 0x138)(
            this, 0x25238ae2, &pl.p, 0x21407ee);
        if (ok && pl.p)
            s_props.Load(pl.p);
    }

    FxRef2 r14;
    r14.Assign(existing);
    if (r14.p == 0)
        VCALL(bool(__thiscall*)(MgrBase*, unsigned, void**, unsigned), this, 0x138)(this, name, &r14.p,
                                                                                    0x21407ee);
    s_props.Set(r14.p);

    float prob;
    if (VCALL(bool(__thiscall*)(Props*, unsigned, float*), &s_props, 0x30)(&s_props, 0x8fc9308e, &prob)) {
        if ((float)rand() * (1.0f / 32767.0f) > prob)
            return false;
    }
    int lvl;
    if (VCALL(bool(__thiscall*)(Props*, unsigned, int*), &s_props, 0x28)(&s_props, 0xb2550953, &lvl)) {
        if (AT(int, this, 0x200) < lvl)
            return false;
    }
    if (!VCALL(bool(__thiscall*)(MgrBase*, G48*, unsigned, unsigned, Props*, float*), this, 0x90)(
            this, &g_g48, name, id, &s_props, pos))
        return false;
    if (AT(bool, this, 0x95) && !g_g48.b1)
        return false;

    bool flag = false;
    int type = VCALL(int(__thiscall*)(MgrBase*, G48*), this, 0x144)(this, &g_g48);
    if (type == 1 || type == 2)
        return false;
    if (type == 3) {
        flag = true;
    } else if (type == 4) {
        if (!VCALL(bool(__thiscall*)(MgrBase*, G48*, void**), this, 0x148)(this, &g_g48, ve.AsPP()))
            return false;
        int kind = VCALL(int(__thiscall*)(void*), ve.p, 0x44)(ve.p);
        if (kind != g_g48.kind) {
            VCALL(void(__thiscall*)(void*, int, int), ve.p, 0x18)(ve.p, 3, AT(unsigned char, this, 0x3fd));
            if (ve.p) {
                void* t = ve.p;
                ve.p = 0;
                ObjRelease(t);
            }
        } else {
            unsigned key2 = VCALL(unsigned(__thiscall*)(void*), ve.p, 0x54)(ve.p);
            HT1& m1 = AT(HT1, this, 0x1277b4);
            HIter it1 = m1.find(key2);
            if (it1.node != m1.End())
                m1.erase(it1);

            HT2& m2 = AT(HT2, this, 0x157440);
            HIter it2 = m2.find(key2);
            if (it2.node != m2.End()) {
                m2.Insert(Pair2(name, (char*)it2.node + 4));
                m2.erase(it2);
            }

            HT4& m4 = AT(HT4, this, 0x404);
            HIter it4 = m4.find(key2);
            if (it4.node != m4.End()) {
                m4.Op(&id);
                HIter e;
                e.node = it4.node;
                e.bucket = *(void***)((char*)it4.node + 4);
                m4.erase(e);
            }

            VCALL(void(__thiscall*)(void*, unsigned), ve.p, 0x50)(ve.p, id);
            VCALL(void(__thiscall*)(void*), ve.p, 0x34)(ve.p);
            void* sub = ve.p ? (char*)ve.p + 4 : 0;
            VCALL(void(__thiscall*)(MgrBase*, unsigned, void*), this, 0x118)(this, key2, sub);
            VCALL(void(__thiscall*)(MgrBase*, unsigned, unsigned, int, int, int), this, 0x128)(this, 0x3a129e8,
                                                                                                key2, 1, 0, 0);
            VCALL(void(__thiscall*)(MgrBase*, unsigned, unsigned, int, int, int), this, 0x128)(this, 0x3a129ee,
                                                                                                key2, 0, 0, 0);
        }
    }

    if (ve.p == 0) {
        List3& l3 = AT(List3, this, 0x157438);
        LIter cur, end;
        l3.Begin_(&cur);
        l3.End_(&end);
        void* c = cur.p;
        void* e = end.p;
        while (c != e) {
            bool want = (flag || AT(bool, this, 0x95)) ? true : false;
            if (MatchEntry(c, want, &g_g48))
                break;
            cur.Next();
            c = cur.p;
        }
        int g38 = s_props.m0c;
        if (!VCALL(bool(__thiscall*)(MgrBase*, unsigned, unsigned, int, void**), this, 0x84)(this, name, id, g38,
                                                                                               ve.AsPP()))
            return false;
        LPair pr;
        pr.cur = c;
        pr.ve = ve.p;
        LPair* pp = &pr;
        l3.Insert(&pp);

        if (AT(bool, this, 0x95)) {
            VCALL(void(__thiscall*)(void*, int, int, float, int), ve.p, 0x1c)(ve.p, 1, 0, -1.0f, 1);
        } else if (flag) {
            VCALL(void(__thiscall*)(void*, int, int, float, int), ve.p, 0x1c)(ve.p, 1, 3, -1.0f, 1);
        } else {
            int* b = AT(int*, this, 0x13769c);
            int* e2 = AT(int*, this, 0x1376a0);
            if (b != e2) {
                for (int* q = b; q != e2; ++q) {
                    if (VCALL(bool(__thiscall*)(void*, int), ve.p, 0x3c)(ve.p, *q)) {
                        VCALL(void(__thiscall*)(void*, int, int, float, int), ve.p, 0x1c)(ve.p, 1, 0, -1.0f, 1);
                        break;
                    }
                }
            }
        }
        if (!VCALL(bool(__thiscall*)(void*, int, int), ve.p, 0x20)(ve.p, -1, 0))
            VCALL(void(__thiscall*)(MgrBase*, void*, int), this, 0x14c)(this, ve.p, 1);
    }

    if (pos) {
        void* sub = (char*)ve.p + 4;
        typedef void(__thiscall * SetF)(void*, unsigned, float, int);
        VCALL(SetF, sub, 0xc)(sub, 0x50c5d67, pos[0], 1);
        sub = (char*)ve.p + 4;
        VCALL(SetF, sub, 0xc)(sub, 0x50c5d66, pos[1], 1);
        sub = (char*)ve.p + 4;
        VCALL(SetF, sub, 0xc)(sub, 0x50c5d65, pos[2], 1);
    }
    if (out) {
        ObjAddRef(ve.p);
        *out = ve.p;
    }
    return true;
}

// @ 0x00a2edd0
void MgrBase::SetEntry(unsigned key, void* val)
{
    HT1* m = &AT(HT1, this, 0x1277b4);
    HIter it = m->find(key);
    if (it.node != m->End()) {
        EntryVal* ev = (EntryVal*)((char*)it.node + 4);
        ev->Assign(val);
        if (ev->m18 == 0)
            it = m->erase(it);
    }
}

// @ 0x00a2ee40
void MgrBase::PostEvent(unsigned a, unsigned b, unsigned c, unsigned d, void* ref)
{
    EventMsg m(a, b, c, d, ref);
    AT(EventQueue, this, 0x15b77c).Push(m);
}

// @ 0x00a2eed0
bool MgrBase::RemoveEntry(void* obj)
{
    IdObj* o = (IdObj*)obj;
    unsigned k = o->GetId();
    AT(HT1b, this, 0x1277b4).Remove(&k);
    k = o->GetId();
    HT4* m = &AT(HT4, this, 0x404);
    HIter it;
    m->findInto(&it, k);
    if (it.node == m->End())
        return false;
    m->eraseInto(&it, it);
    return true;
}

// @ 0x00a2ef60
void MgrBase::Rebuild()
{
    Stopwatch_s00a2_e650 sw(4, 0);
    void* dbg = ObjectError();
    if (dbg) {
        sw.RestartInline();
        MapUU* map = &AT(MapUU, this, 0x118a5c);
        Snap snap(map);
        EVec vec;
        vec.b = 0;
        vec.e = 0;
        vec.c = 0;
        VCALL(void(__thiscall*)(void*, EVec*, Snap*, int), dbg, 0x38)(dbg, &vec, &snap, 0);
        sw.RestartInline();
        HT5* t = &AT(HT5, this, 0x33d4);
        t->DoFreeNodes(t->mpBuckets, t->mnBuckets);
        t->mnCount = 0;
        Elem* last = vec.e;
        for (Elem* p = vec.b; p != last; ++p) {
            HIter it = t->find(p->key);
            if (it.node == t->End()) {
                P2 pr;
                pr.a = p->key;
                pr.b = p->val;
                ((HT5I*)t)->Insert(&pr, false);
            } else {
                unsigned* nv = (unsigned*)it.node + 1;
                int a = (*map)[p->val];
                if ((*map)[*nv] <= a)
                    *nv = p->val;
            }
        }
    }
}

// @ 0x00a2f180
void cTypeMapHolder::SetTypePriority(uint32_t type, uint32_t priority)
{
    mMap[type] = (int)priority;
}

// @ 0x00a2f1a0
void cTypeMapHolder::InitDefaultPriorities()
{
    mMap[0x3055f61] = 0;
    mMap[0x2b9f662] = 1;
    mMap[0x1a527db] = 2;
}

// @ 0x00a2f5d0
HNodeV* NodePool_s00a2_e650::Alloc(const SrcPair* src)
{
    HNodeV* n = (HNodeV*)mpHead;
    if (n == 0)
        n = (HNodeV*)EaNew(mnNodeSize, "EASTL", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    else
        mpHead = *(void**)n;
    if (n) {
        n->key = src->key;
        new (&n->val) MappedVal(src->val);
    }
    n->m1e4 = 0;
    return n;
}

// @ 0x00a2f6e0
void NodeAllocator::DoFreeNodes(HashNode0** pNodeArray, u32 n)
{
	for (u32 i = 0; i < n; ++i) {
		HashNode0* pNode = pNodeArray[i];
		while (pNode != 0) {
			HashNode0* const pTmp = pNode;
			pNode = pNode->mpNext;
			((void(__thiscall*)(NodeAllocator*, HashNode0*))FUN_00a2f660)(this, pTmp);
		}
		pNodeArray[i] = 0;
	}
}

// @ 0x00a2f730
u32 Submix_s00a2_f660::LoadFromResman(const char* resName, u32 flags, u32 extra)
{
	ProfileTimer_s00a2_f660 timer((char*)this + 0x5c);
	void* const pDebug = FUN_008de1a0();
	if (pDebug == 0)
		return 0;

	u8 params[0xc] = { 0 };
	if (FUN_00a24850(resName, params) == 0)
		return 0;

	void* const pHook = (*(void*(__thiscall**)(void*, void*))(*(char**)pDebug + 0x58))(pDebug, params);

	void* pRef = 0;
	if (pHook != 0) {
		(*(void(__thiscall**)(void*))(*(char**)pHook + 0x00))(pHook);

		u32 nKind = 0;
		if (flags == 0)
			nKind = 1;
		else if ((flags & 1) != 0)
			nKind = 3;

		if ((*(u8(__thiscall**)(void*, u32*, u32, u32, u32, u32))(*(char**)pHook + 0x34))
				(pHook, &extra, nKind, 6, 1, 0) != 0) {
			pRef = pHook;
			if (FUN_00a2e4c0(0) != 0) {
				(*(void(__thiscall**)(void*))(*(char**)pHook + 0x04))(pHook);
				FUN_00a24900();
				return 1;
			}
		}
	}

	if (pRef != 0)
		(*(void(__thiscall**)(void*))(*(char**)pRef + 0x04))(pRef);

	return 0;
}

// @ 0x00a2f960
Submix_s00a2_f660::Submix_s00a2_f660()
: mId(0), mSendId(0), mbAddedToTick(0)
	, mPrimitives(AllocTag(), AllocTag())
	, mRegisters(AllocTag(), AllocTag())
	, mSendPlugins(AllocTag(), AllocTag())
{
}

// @ 0x00a2fac0
void Submix_s00a2_f660::Tick(u32, u32)
{
	if (mParams.mStampByte != 0 && FUN_0112c640(mParams.mFlag2) != 0) {
		mParams.mFlag2 = 0;
		mParams.mStampByte = 0;
		mVoiceContainer.Destroy();
	}

	IPrimitiveNode** pBucket = (IPrimitiveNode**)mPrimitives.mpBucketArray;
	IPrimitiveNode* pNode = *pBucket;
	if (pNode == 0) {
		do {
			++pBucket;
			pNode = *pBucket;
		} while (pNode == 0);
	}

	IPrimitiveNode* const pEnd =
		*(IPrimitiveNode**)((char*)mPrimitives.mpBucketArray + mPrimitives.mnBucketCount * 4);

	while (pNode != pEnd) {
		IPrimitive* const pPrim = pNode->mpValue;
		const u32 nId = pNode->mKey;
		if (pPrim != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pPrim + 0x00))(pPrim);

		if ((*(u8(__thiscall**)(IPrimitive*, u32))(*(char**)pPrim + 0x20))(pPrim, 0) != 0) {
			const float fVal = (float)(*(double(__thiscall**)(IPrimitive*))(*(char**)pPrim + 0x1c))(pPrim);
			u32 v; *(float*)&v = fVal;
			mVoiceContainer.SetProperty(nId, v);
		}
		(*(void(__thiscall**)(IPrimitive*))(*(char**)pPrim + 0x04))(pPrim);

		pNode = pNode->mpNext;
		while (pNode == 0) {
			++pBucket;
			pNode = *pBucket;
		}
	}
}

// @ 0x00a2fbe0
u32 Submix_s00a2_f660::SetPerformanceData(int level, const void* a, u32 b)
{
	mVoiceContainer.MaskPluginBindings(a, b);

	const bool bUnderThreshold = level < (int)mParams.mFlags1;
	u32 nActive = (u32)bUnderThreshold;

	if (bUnderThreshold) {
		if (mParams.mFlag3 != 0)
			return nActive;

		if (mParams.mFlag2 != 0) {
			int* pInst = (int*)(*(void*(__thiscall**)(u32))(*(char**)gEapdDebug + 0x17c))(mSendId);
			if (pInst != 0) {
				void* pSend = *(void**)(pInst + 0x14);
				if (gAudioSystem != 0)
					FUN_0112c600();
				if (gAudioSystem != 0) {
					void* it;
					FUN_00594410(&it);
					IPrimitiveNode* const pItEnd = *(IPrimitiveNode**)
						((char*)mSendPlugins.mpBucketArray + mSendPlugins.mnBucketCount * 4);
					while ((IPrimitiveNode*)it != pItEnd) {
						FUN_0112ccc0(0, &pSend);
						it = *(void**)((char*)it + 4);
						while (it == 0) {
							it = *(void**)((char*)it + 4);
						}
					}
					FUN_0112c620();
				}
			}
		}
		mVoiceContainer.Disconnect();
		mParams.mStamp = *(u32*)((char*)gAudioSystem + 0xe0);
		mParams.mFlag4 = 1;
		mParams.mFlag3 = 1;
		return 1;
	}

	if (mParams.mFlag3 == 0)
		return nActive;

	mVoiceContainer.Create(mParams.mValueByte);
	mVoiceContainer.Connect();
	nActive = mVoiceContainer.CommitBoundProperties();
	if (mParams.mFlag2 != 0) {
		if (gAudioSystem != 0)
			FUN_0112c600();
		if (gAudioSystem != 0) {
			void* it;
			FUN_00594410(&it);
			IPrimitiveNode* const pItEnd = *(IPrimitiveNode**)
				((char*)mSendPlugins.mpBucketArray + mSendPlugins.mnBucketCount * 4);
			while ((IPrimitiveNode*)it != pItEnd) {
				void* pPrim = *(void**)&nActive;
				nActive = FUN_0112ccc0(0, &pPrim);
				it = *(void**)((char*)it + 4);
				while (it == 0) {
					it = *(void**)((char*)it + 4);
				}
			}
			FUN_0112c620();
		}
	}
	mParams.mFlag4 = 0;
	mParams.mFlag3 = 0;
	return nActive;
}

// @ 0x00a2fe30
void Submix_s00a2_f660::SetProperty(u32 id, u32 value)
{
	if ((value & 0x7fffffff) == 0
			|| (((value - 0x800000) & 0x7f800000) < 0x7f000000)
			|| (((value & 0x7fffffff) - 1) < 0x7fffff)) {
		void* const pPrim = (*(void*(__thiscall**)(u32))(*(char**)gEapdDebug + 0xf8))(id);
		if (pPrim == 0) {
			mVoiceContainer.SetProperty(id, value);
			return;
		}

		IPrimitiveNode* pFound;
		((void(__thiscall*)(RegTable*, u32*, IPrimitiveNode**))FUN_00645ed0)(&mRegisters, &id, &pFound);

		IPrimitive* pCreated = 0;
		IPrimitiveNode* const pEnd =
			*(IPrimitiveNode**)((char*)mRegisters.mpBucketArray + mRegisters.mnBucketCount * 4);

		if (pFound == pEnd) {
			IPrimitiveNode* const pStorage = (IPrimitiveNode*)FUN_00a17090(0x1c);
			if (pStorage != 0)
				pCreated = (IPrimitive*)FUN_00a17100(this);
			if (pCreated != 0)
				(*(void(__thiscall**)(IPrimitive*))(*(char**)pCreated + 0x00))(pCreated);

			FUN_00fccdd0(id);
			((void(__thiscall*)(IPrimitive*, u32))(void*)FUN_00a16fd0)(pCreated, value);
			((void(__thiscall*)(RegTable*, IPrimitiveNode*, u32))FUN_00a26ce0)
				(&mRegisters, (IPrimitiveNode*)&pStorage, value & 0xffffff00);
			(*(void(__thiscall**)(Submix_s00a2_f660*, u32, IPrimitive*))(*(char**)this + 0x18))(this, id, pCreated);
		} else {
			IPrimitive* const pValue = pFound->mpValue;
			if (pValue != 0) {
				(*(void(__thiscall**)(IPrimitive*))(*(char**)pValue + 0x00))(pValue);
				pCreated = pValue;
			}
			((void(__thiscall*)(IPrimitive*, u32))(void*)FUN_00a16fd0)(pCreated, value);
		}

		if (pCreated != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pCreated + 0x04))(pCreated);
	}
}

// @ 0x00a2ffe0
u32 Submix_s00a2_f660::ConnectPrimitive(u32 id, IPrimitive* p)
{
	IPrimitiveNode* pFound;
	((void(__thiscall*)(PHTable_s00a2_f660*, u32*, IPrimitiveNode**))FUN_00645ed0)(&mPrimitives, &id, &pFound);

	IPrimitiveNode* const pEnd =
		*(IPrimitiveNode**)((char*)mPrimitives.mpBucketArray + mPrimitives.mnBucketCount * 4);

	if (pFound == pEnd) {
		if (p != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)p + 0x00))(p);
		IPrimitive* const pNew = p;
		if (pNew != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pNew + 0x00))(pNew);
		FUN_00a136f0((void*)&pFound, (void*)&pFound, id & 0xffffff00);
		if (pNew != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pNew + 0x04))(pNew);
		if (p != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)p + 0x04))(p);
		return 1;
	}

	void* const pPrim = (*(void*(__thiscall**)(u32))(*(char**)gEapdDebug + 0xf8))(id);
	if (pPrim == 0)
		return 0;

	IPrimitive* pExisting = pFound->mpValue;
	IPrimitive* pMatch = 0;
	if (pExisting != 0)
		pMatch = (IPrimitive*)(*(void*(__thiscall**)(IPrimitive*, u32))(*(char**)pExisting + 0x0c))(pExisting, 0x4e73a43a);

	if (pMatch == 0
			|| (*(int(__thiscall**)(IPrimitive*))(*(char**)pMatch + 0x30))(pMatch) != (int)(long)this) {
		void* const pMem = FUN_00a16ad0(0x6c);
		IPrimitive* pAgg = 0;
		if (pMem != 0)
			pAgg = (IPrimitive*)FUN_00a16d00((u32)(long)this);
		if (pAgg != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x00))(pAgg);

		((void(__thiscall*)(IPrimitive*, void*))FUN_00a16a90)(pExisting, pPrim);
		(*(void(__thiscall**)(IPrimitive*, IPrimitive*))(*(char**)pExisting + 0x10))(pExisting, pExisting);
		(*(void(__thiscall**)(IPrimitive*, IPrimitive*))(*(char**)pAgg + 0x10))(pAgg, pAgg);
		(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x10))(pAgg);
		(*(void(__thiscall**)(IPrimitive*, u32))(*(char**)pAgg + 0x2c))(pAgg, 1);

		pExisting = pFound->mpValue;
		if (pAgg != pExisting) {
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x00))(pAgg);
			pFound->mpValue = pAgg;
			if (pExisting != 0)
				(*(void(__thiscall**)(IPrimitive*))(*(char**)pExisting + 0x04))(pExisting);
		}
		(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x04))(pAgg);
	} else {
		(*(void(__thiscall**)(IPrimitive*, u32))(*(char**)pMatch + 0x10))(pMatch, id);
	}
	return 1;
}

// @ 0x00a301f0
void Submix_s00a2_f660::DisconnectPrimitive(u32 id, IPrimitive* p)
{
	PHTable_s00a2_f660& tbl = mPrimitives;
	HTIter it;
	((void(__thiscall*)(PHTable_s00a2_f660*, IPrimitiveNode**, u32*))FUN_00645ed0)(&tbl, (IPrimitiveNode**)&it, &id);

	if (it.mpNode == (IPrimitiveNode*)tbl.mpBucketArray[tbl.mnBucketCount])
		return;

	IPrimitive* const pExisting = it.mpNode->mpValue;
	if (pExisting != 0) {
		IPrimitive* const pMatch =
			(IPrimitive*)(*(void*(__thiscall**)(IPrimitive*, u32))(*(char**)pExisting + 0x0c))(pExisting, 0x4e73a43a);
		if (pMatch != 0) {
			(*(void(__thiscall**)(IPrimitive*, IPrimitive*))(*(char**)pMatch + 0x14))(pMatch, p);
			return;
		}
	}
	if (pExisting == p) {
		((void(__thiscall*)(PHTable_s00a2_f660*, HTIter, HTIter*))FUN_00d2c9f0)(&tbl, it, &it);
	}
}

// @ 0x00a30280
EA::Audio::Submix::~Submix()
{
}

// @ 0x00a30460
void EA::Audio::System::SetProperty(unsigned int key, float value)
{
    char* s = (char*)this;
    if (key < 0x194f967d) {
        if (key == 0x194f967c) {
            s[0x97] = (value == 0.0f);
        } else if (key == 0x435b383) {
            *(float*)(s + 0xa8) = value;
            switch ((int)value) {
            case 0: *(int*)(s + 0xb0) = 1; break;
            case 2: *(int*)(s + 0xb0) = 4; break;
            case 3: *(int*)(s + 0xb0) = 6; break;
            default:
                *(float*)(s + 0xa8) = 1.0f;
            case 1: *(int*)(s + 0xb0) = 2; break;
            }
        } else if (key == 0x6a371e0) {
            *(float*)(s + 0xac) = value;
        } else if (key == 0x9cd802a) {
            s[0x98] = (value == 0.0f);
        }
    } else if (key == 0x6df5822d) {
        *(int*)(s + 0x200) = (int)value;
        void* dst = *(void**)(s + 0x15bb80);
        void* src = *(void**)(s + 0x15bb7c);
        FUN_011e0744(dst, src, 0);
        *(int*)(s + 0x15bb80) += ((int)src - (int)dst >> 2) * -4;
        int local_18 = 0;
        void* local_14 = 0;
        if (*(int*)(s + 0x200) == 1)
            vc_s00a3_0460<void>(*(void**)(s + 0x1f8), 0x48, 0xdf59188d);
        else if (*(int*)(s + 0x200) == 2)
            vc_s00a3_0460<void>(*(void**)(s + 0x1f8), 0x48, 0xb5760a90);
        (void)local_18; (void)local_14;
        // default 2-ch allocation path: FUN_0089cb60(local_18) then vector<bool>
        // DoInsertValue(local_14, local_18*4).
        void** subs = *(void***)(s + 0x119ba4);
        void** sube = *(void***)(s + 0x119ba8);
        int begin = *(int*)(s + 0x15bb7c);
        int count = (*(int*)(s + 0x15bb80) - begin) >> 2;
        for (; subs != sube; ++subs) {
            void* p = *subs;
            vc_s00a3_0460<void>(p, 0x20, *(int*)(s + 0x200));
            (void)begin; (void)count;
        }
    } else if (key == 0x899eb157) {
        s[0x99] = (value != 0.0f);
    }

    SysMap* m = (SysMap*)(s + 0x13777c);
    MapNode** buckets = m->buckets;
    u32 n = m->count;
    MapNode* node = buckets[key % n];
    while (node != 0 && node->key != key)
        node = (MapNode*)node->next;
    if (node == 0)
        m->insert(key, value);
    else
        node->val = value;
}

// @ 0x00a30790
int __cdecl FUN_00a30790(void)
{
    void* obj = vc0<void*>(0, 0x0);   // EA::Audio::Eapd::Debug::ObjectError()
    (void)obj;
    return 0;
}

// @ 0x00a30940
void EA::Audio::System::PreloadConfigurations()
{
    // fixed_map<Key,AutoRefCount<ResourceConfiguration>,20000,1,...> local at
    // the base of the frame; enumerates every ResourceMan record that exposes
    // the audio resource-configuration interface, reads it and publishes it.
    // The original allocates a ~640 KiB frame (see _chkstk).  This body keeps
    // the observable sequence of calls.
    char localmap[0x1c];
    memset(localmap, 0, sizeof(localmap));
    void* obj = 0;  // Eapd::Debug::ObjectError()
    (void)obj;
    // enumerator walk + per-record construction/Read/insert omitted (alloca frame)
}

// @ 0x00a30e10
int FixedMap30e10::ctor(void* a2, void* a3)
{
    FixedPoolBase fb;
    fb.mpHead = 0;
    fb.init((char*)this + 0x2f1c, 600000, 0x14, 4, 0);
    u32 v = FUN_00921340(0xbb9);
    ((HashBaseCD*)this)->ctor(v, a2, (void*)&a3, (void*)&a3, (u32)(size_t)a3,
                              (void*)&a3, &fb);
    *(u32*)((char*)this + 0x10) = 0x461c4000;
    *(u32*)((char*)this + 0x14) = 0x40000000;
    *(u32*)((char*)this + 0x18) = 0;
    u32 u = FUN_009213c0(*(u32*)((char*)this + 0xc));
    if (*(u32*)((char*)this + 8) < u)
        ((HashBaseCD*)this)->rehash(u);
    return (int)this;
}

// @ 0x00a30f10
int NodeMap::eraseKey(u32* key)
{
    int iVar1 = mnElementCount;
    u32 uVar3 = *key % mnBucketCount;
    u32* puVar4 = (u32*)((char*)mpBuckets + uVar3 * 4);
    if (*(int*)((char*)mpBuckets + uVar3 * 4) != 0) {
        u32* puVar2;
        do {
            puVar2 = (u32*)*puVar4;
            if (*key == *puVar2)
                break;
            puVar4 = puVar2 + 0x79;
        } while (puVar2[0x79] != 0);
        while (*puVar4 != 0 && *key == *(u32*)*puVar4) {
            u32* puVar2 = (u32*)*puVar4;
            *puVar4 = puVar2[0x79];
            FreeNode(puVar2);
            mnElementCount -= 1;
        }
    }
    return iVar1 - mnElementCount;
}

// @ 0x00a31040
FixedVec11Obj::FixedVec11Obj(int param_2)
{
    resize(param_2 + 1);
    fStart = (u32)mpBegin;
    fEnd = (u32)mpBegin;
    fCount = 0;
}

// Copy-construction view of FixedVec11b (0x00a310b0): the vector base takes the inline pool and frees on unwind;
// the elements are assigned through 0x00a2b2e0 with an uninitialized iterator tag.
struct FV11Tag_a310b0 {};
struct FV11Base_a310b0 {
    u32* mpBegin;    // +0
    u32* mpEnd;      // +4
    u32* mpCap;      // +8
    u32* f0c;        // +0xc
    u32* f10;        // +0x10
    explicit FV11Base_a310b0(u32* pool) { mpBegin = 0; mpEnd = 0; mpCap = 0; f10 = pool; }
    ~FV11Base_a310b0();
};
struct FV11Copy_a310b0 : FV11Base_a310b0 {
    u32* f14;            // +0x14
    u32  storage[250];   // +0x18
    FV11Copy_a310b0(const FV11Copy_a310b0& x);
    void DoAssign(u32* first, u32* last, FV11Tag_a310b0 tag);   // 0x00a2b2e0
};

// @ 0x00a310b0
FV11Copy_a310b0::FV11Copy_a310b0(const FV11Copy_a310b0& x) : FV11Base_a310b0(storage)
{
    mpBegin = mpEnd = storage;
    mpCap = mpBegin + 250;
    FV11Tag_a310b0 tag;
    DoAssign(x.mpBegin, x.mpEnd, tag);
}

// @ 0x00a31170
bool cSystem::InitAT()
{
    mbMuteApplied = false;
    int* slot = &((int*)mIdTable.mpBegin)[(int)mIdTable.mpEnd];
    mIterValue = *slot;
    mIterPos = slot;
    mIter8 = 0;
    mIterC = 0;
    mIter10 = 0;

    IResourceManager* mgr = GetResourceManager();
    if (mgr) {
        FactoryObj* fa = (FactoryObj*)ZoneAlloc(8, g_audioName, 0, 0, 0, 0);
        fa = fa ? fa->Init(g_vtFactoryA) : 0;
        mgr->RegisterFactory(1, (IFactory*)fa, 0);

        FactoryObj* fb = (FactoryObj*)ZoneAlloc(8, g_audioName, 0, 0, 0, 0);
        fb = fb ? fb->Init(g_vtFactoryB) : 0;
        IFactory* nb = (IFactory*)fb;
        IFactory* old = mpFactoryB;
        if (nb != old) {
            if (nb)
                nb->AddRef();
            mpFactoryB = nb;
            if (old)
                old->Release();
        }
        mgr->RegisterFactory(1, mpFactoryB, 0);

        FactoryObj* fc = (FactoryObj*)ZoneAlloc(8, g_audioName, 0, 0, 0, 0);
        fc = fc ? fc->Init(g_vtFactoryC) : 0;
        mgr->RegisterFactory(1, (IFactory*)fc, 0);
    }

    Hook1bc(g_1552da0);
    mpRWAC = CreateInstance(&mAllocator, mCommandBufferSize);
    if (!mpRWAC)
        return false;

    mPoolA.Init(5000);
    mPoolB.Init(5000);

    AutoAudioLock lock;
    mpRWAC->SetCallback((void*)0x00b1e4d0);
    Hook1b4();
    if (g_FsAllocatorManager == 0) {
        FsParams fp;
        fp.mpChannel = &mDebugChannel;
        fp.mpAllocator2 = &mAllocator2;
        fp.mA = 2;
        fp.mB = 0x400;
        FsInit(&fp);
    }
    FsManager* fs = GetFsManager();
    if (fs)
        fs->SetDriver(&mResourceDeviceDriver, 0);
    mpStreamPoolDefault = ReleaseHandler(0x2ea8fb98, mStreamPoolNumStreams, mStreamPoolBufferSize,
                                         mStreamPoolMaxRequests, mpRWAC, &mAllocator, 0);
    uint32_t emitterKey = 0x1a527db;
    mEmitterMap.At(emitterKey) = (void*)ConstructEmitterSndPlayer;
    Hook1f0();
    FUN_a2ef60();
    FUN_a2da30();
    Hook1c4();

    VoiceContainer_s00a3_1170* holder = GetVoiceHolder(0xf1cc1687);
    if (!holder)
        return false;
    VoiceContainer_s00a3_1170* container = (VoiceContainer_s00a3_1170*)((char*)holder + 0x10);
    IPluginParam* p1 = container->FindPlugin(0x53756230);
    if (!p1)
        return false;
    mpRWAC->AddPlugin(p1);
    IPluginParam* p2 = container->FindPlugin(0x44616330);
    if (!p2)
        return false;

    float mode = mDacOutputMode;
    p2->SetParam(1, &mode);
    float rate = mDacOutputSampleRate;
    p2->SetParam(2, &rate);
    p2->SetParam(3, 0);

    bool muted;
    if (mbMutedForSilence || mbMuted || mbMutedForFocus || mbMutedByProperty)
        muted = true;
    else
        muted = false;
    if (muted != mbMuteApplied)
        MuteAll(muted, true);
    Hook1c8();

    uint32_t id = 0x7d1;
    do {
        uint32_t tmp = id;
        mIdRing.push_back(tmp);
        ++id;
    } while (id <= 0xbb8);

    ResKey sysKey;
    sysKey.instance = 0;
    sysKey.type = 0x2b9f662;
    sysKey.group = 0x21407ee;
    sysKey.instance = HashName(g_systemName);
    IResourceType* rt = GetResourceManager()->GetResourceType(&sysKey);
    if (rt && rt->GetTypeID() != 0x34728492)
        PreloadConfigurations();
    SetTuning(0x6df5822d, (float)mPerformanceLevel);

    IResourceManager* mgr2 = GetResourceManager();
    if (mgr2) {
        ResKey tableKey;
        tableKey.instance = 0xa101b2c4;
        tableKey.type = 0x5bad11c;
        tableKey.group = 0x21407ee;
        DbList list;
        list.mAnchor.mpNext = list.mAnchor.mpPrev = &list.mAnchor;
        list.mpAllocator = GetDefaultAllocator_s00a3_1170();
        list.mFlags = 0;
        mgr2->GetDatabases(&list, &tableKey);
        for (ListNode_s00a3_1170* node = list.mAnchor.mpNext; node != &list.mAnchor; node = node->mpNext) {
            IResource* res = 0;
            IDatabase* db = (IDatabase*)node->mpData;
            if (db->GetResource(&tableKey, &res, 1, 6, 1, 0)) {
                IStream* stream = res->OpenStream();
                if (stream) {
                    ByteVec buf;
                    uint32_t size = stream->GetSize();
                    buf.resize(size);
                    uint8_t* data = buf.mpBegin;
                    if (size == stream->Read(data, size)) {
                        uint32_t count = size >> 3;
                        while (count != 0) {
                            uint32_t key = ((uint32_t*)data)[0];
                            uint32_t value = ((uint32_t*)data)[1];
                            --count;
                            void* end = mPolyphonyMap.mpBucketArray[mPolyphonyMap.mnBucketCount];
                            data += 8;
                            HashIter_s00a3_1170 it;
                            if (mPolyphonyMap.find(&it, key)->mpNode == end) {
                                PolyPair pr;
                                pr.first = key;
                                pr.second = value;
                                HashInsertResult ir;
                                mPolyphonyMap.insert(&ir, &pr, false);
                            }
                        }
                    }
                    stream->Close();
                }
            }
            if (res)
                res->Release();
        }
        for (ListNode_s00a3_1170* n = list.mAnchor.mpNext; n != &list.mAnchor;) {
            ListNode_s00a3_1170* next = n->mpNext;
            ((CoreAlloc*)list.mpAllocator)->Free(n, 0xc);
            n = next;
        }
    }
    return true;
}

// @ 0x00a31800
bool cSystem::ShutdownAT()
{
    mPoolA.Reset();
    Hook1b8();
    HookDC();
    Hook80(1);

    if (mPromptList.mpNext != (ListNode_s00a3_1170*)&mPromptList) {
        for (mpPromptIter = mPromptList.mpNext; mpPromptIter != (ListNode_s00a3_1170*)&mPromptList; )
        {
            ListNode_s00a3_1170* node = mpPromptIter;
            ((IPrompt*)node->mpData)->Release(kPromptReleaseTime, kPromptReleaseTime);
            mpPromptIter = node->mpNext;
        }
    }

    mFadeVolume = 0.0f;
    Hook1d0();
    Hook1cc();

    if (mpMessageHandler) {
        void* handler = mpMessageHandler;
        mpMessageHandler = 0;
        FUN_00571db0(handler, mHandlerArg0, mHandlerArg1, mHandlerArg2, mHandlerArg3);
    }

    if (mpStreamPoolDefault) {
        {
            AutoAudioLock lock;
            mpStreamPoolDefault->QueueRelease();
            mpStreamPoolDefault = 0;
        }
    }

    if (mpRWAC) {
        unsigned int ctrl = _controlfp(0, 0);
        bool restore = (ctrl & 0x30000) != 0x10000;
        if (restore)
            _controlfp(0x10000, 0x30000);
        mpRWAC->shutdown();
        mpRWAC = 0;
        if (restore)
            _controlfp(ctrl, 0x30000);
    }

    FUN_011e5d30();

    if (mPromptList.mpNext != (ListNode_s00a3_1170*)&mPromptList) {
        for (mpPromptIter = mPromptList.mpNext; mpPromptIter != (ListNode_s00a3_1170*)&mPromptList; )
        {
            ListNode_s00a3_1170* node = mpPromptIter;
            Hook74(node->mpData);
            mpPromptIter = node->mpNext;
        }
        mPromptList.FreeNodes();
        mPromptList.mpNext = (ListNode_s00a3_1170*)&mPromptList;
        mPromptList.mpPrev = (ListNode_s00a3_1170*)&mPromptList;
    }

    mHash404.DoFreeNodes(mHash404.mpBegin, mHash404.mpEnd);
    mHash404.mCount = 0;
    mHash13f4.FreeBuckets((void**)mHash13f4.mpBegin, (uint32_t)(intptr_t)mHash13f4.mpEnd);
    mHash13f4.mCount = 0;
    mHash23e4.DoFreeNodes(mHash23e4.mpBegin, mHash23e4.mpEnd);
    mHash23e4.mCount = 0;
    mHash33d4.DoFreeNodes(mHash33d4.mpBegin, mHash33d4.mpEnd);
    mHash33d4.mCount = 0;
    mHash80424.FreeSubNodes((void**)mHash80424.mpBegin, (uint32_t)(intptr_t)mHash80424.mpEnd);
    mHash80424.mCount = 0;
    mFdf1189fc.FreeFdfNodes(mFdf1189fc.mpBegin, mFdf1189fc.mpEnd);
    mFdf1189fc.mCount = 0;
    mIdTable.FreeFdfNodes(mIdTable.mpBegin, mIdTable.mpEnd);
    mIdTable.mCount = 0;
    mTree118a5c.Clear();
    mEmitterMap.FreeNodes(mEmitterMap.mpBegin, mEmitterMap.mpEnd);
    mEmitterMap.mCount = 0;
    mRes118b90.FreeResNodes((void**)mRes118b90.mpBegin, (uint32_t)(intptr_t)mRes118b90.mpEnd);
    mRes118b90.mCount = 0;
    mHash118bb0.DoFreeNodes(mHash118bb0.mpBegin, mHash118bb0.mpEnd);
    mHash118bb0.mCount = 0;

    if (mpLogReporterList) {
        FUN_00926410(mpLogReporterList);
        operator_delete_array(mpLogReporterList);
    }
    mpLogReporterList = 0;
    FUN_00e25bd0(mReporterVec.mpBegin, mReporterVec.mpEnd);

    mHash119bb8.FreeBuckets((void**)mHash119bb8.mpBegin, (uint32_t)(intptr_t)mHash119bb8.mpEnd);
    mHash119bb8.mCount = 0;
    mHash11a3d8.DoFreeNodes(mHash11a3d8.mpBegin, mHash11a3d8.mpEnd);
    mHash11a3d8.mCount = 0;
    mFloat11b3c8.FreeFloatNodes(mFloat11b3c8.mpBegin, mFloat11b3c8.mpEnd);
    mFloat11b3c8.mCount = 0;
    mMisc1277b4.FreeMiscNodes(mMisc1277b4.mpBegin, mMisc1277b4.mpEnd);
    mMisc1277b4.mCount = 0;
    mProf128ae0.FreeProfBuckets(mProf128ae0.mpBegin, (uint32_t)(intptr_t)mProf128ae0.mpEnd);
    mProf128ae0.mCount = 0;

    mRing12d968.mpBegin = mpProfPool;
    mRing12d968.mpEnd = mpProfPool;
    mRing12d968.mpCapacity = 0;
    mProf12d974.FreeProfBuckets(mProf12d974.mpBegin, (uint32_t)(intptr_t)mProf12d974.mpEnd);
    mProf12d974.mCount = 0;

    mRing1327fc.mpBegin = mIdRing.mpBegin;
    mRing1327fc.mpEnd = mIdRing.mpBegin;
    mRing1327fc.mpCapacity = 0;
    mProf132808.FreeProfBuckets(mProf132808.mpBegin, (uint32_t)(intptr_t)mProf132808.mpEnd);
    mProf132808.mCount = 0;

    mRing137690.mpBegin = mpProfPool2;
    mRing137690.mpEnd = mpProfPool2;
    mRing137690.mpCapacity = 0;
    mBits13769c.EraseAll();

    mList157438.Clear();
    mProf157440.FreeProfBuckets(mProf157440.mpBegin, (uint32_t)(intptr_t)mProf157440.mpEnd);
    mProf157440.mCount = 0;

    mBits15bb7c.EraseAll();

    mFdf118a3c.FreeFdfNodes(mFdf118a3c.mpBegin, mFdf118a3c.mpEnd);
    mFdf118a3c.mCount = 0;
    mHash13777c.DoFreeNodes(mHash13777c.mpBegin, mHash13777c.mpEnd);
    mHash13777c.mCount = 0;

    if (mpFactoryB) {
        IFactory* old = mpFactoryB;
        mpFactoryB = 0;
        old->Release();
    }

    mPolyphonyMap.FreeNodes(mPolyphonyMap.mpBucketArray, (void*)(intptr_t)mPolyphonyMap.mnBucketCount);
    mPolyphonyMap.mnNodeCount = 0;

    g_teardownFlag = 0;
    return true;
}

// @ 0x00a31dc0
bool cSystem::FUN_00a31dc0(uint32_t key, void* query)
{
    bool removed = false;
    HashIter_s00a3_1170 it;

    mMisc1277b4.FindMisc(&it, key);
    if (it.mpNode != mMisc1277b4.Sentinel())
        return ((MapNode_s00a3_1170*)it.mpNode)->mPair.Remove(query);

    mHash404.FindInt(&it, key);
    if (it.mpNode == mHash404.Sentinel())
        return removed;

    KeyValue* kv = &((MapNode_s00a3_1170*)it.mpNode)->mPair;
    uint32_t value = kv->mValue;

    EaTree temp;
    temp.mAllocator = 0;
    temp.mpHeaderNode = &temp;
    temp.mpRoot = &temp;
    temp.mpNodeChain = 0;
    temp.mbFlag = 0;
    temp.mCount = 0;

    removed = kv->Remove(query);
    if (removed) {
        PolyPair pair;
        HashIter_s00a3_1170 out;
        uint8_t flag = 0;
        pair.first = key;
        pair.second = value;
        out.Init(&flag);                        // 0x00a26fa0
        InsertMapped(&out, &pair, flag);        // 0x00a2f510
        temp.NukeSubtree(temp.mpNodeChain);
    }
    temp.NukeSubtree(temp.mpNodeChain);
    return removed;
}

// @ 0x00a31f20
bool System_s00a3_1f20::DoCommandMainThread(EA::Audio::Command_s00a3_1f20* cmd)
{
    uint8_t* self = (uint8_t*)this;
    uint type = cmd->Type();
    switch (type) {
    case 0x3a0fcce: {
        if (GetServer()) {
            uint32_t a, b, c;
            cmd->GetUint32(0x3a0fce5, &a);
            cmd->GetUint32(0x3475385, &b);
            cmd->GetUint32(0x39e3c9f, &c);
            Msg m;
            m.id = 0x3a127dc;
                        m.f8 = a;
            m.f10 = b;
            m.flags = 7;
            m.f18 = c;
            GetServer()->Send(0x3a127dc, &m.refcount, 0);
            if (a == 0x3a129ee) {
                ((ListA*)(self + 0x11b3c8))->Add(&b);
                uint32_t it[2];
                HMapRaw* map = (HMapRaw*)(self + 0x128ae0);
                map->Find(it, &b);
                uint32_t* mp = (uint32_t*)map;
                if (it[0] != *(uint32_t*)(mp[1] + mp[2] * 4)) {
                    map->Erase(it, it[0], it[1]);
                    if (b - 0x3e9 < 0x3e8) {
                        ((ListB*)(self + 0x12c9ac))->Push(&b);
                    } else if (b - 1 < 0x3e8) {
                        uint32_t* q = (uint32_t*)(self + 0x132808);
                        uint32_t endNode = *(uint32_t*)(q[1] + q[2] * 4);
                        uint32_t it2[2];
                        uint32_t* r = (uint32_t*)((HMapRaw*)q)->Find(it2, &b);
                        if (*r == endNode)
                            ((ListB*)(self + 0x1366d4))->Push(&b);
                    }
                }
            }
        }
        break;
    }
    case 0x407c01d: {
        uint32_t v1, v2;
        float v3;
        cmd->GetUint32(0x3475385, &v1);
        cmd->GetUint32(0x34753a7, &v2);
        cmd->GetBool(0x34753aa, &v3);
        typedef void (__thiscall *Fn)(System_s00a3_1f20*, uint32_t, uint32_t, float);
        ((Fn)(*(void***)this)[0x1e4 / 4])(this, v1, v2, v3);
        break;
    }
    case 0x45022f5: {
        if (GetServer()) {
            uint32_t id, a, b, c, d;
            cmd->GetUint32(0x4502316, &id);
            cmd->GetUint32(0x39e3c9f, &a);
            cmd->GetUint32(0x39e3ca6, &b);
            cmd->GetUint32(0x39e3caa, &c);
            cmd->GetUint32(0x39e3cb1, &d);
            MsgC m;
            ((MsgCtor*)&m.refcount)->Init(id);
            m.f8 = a;
            m.f10 = b;
            m.flags |= 1;
            m.flags |= 2;
            m.flags |= 4;
            m.flags |= 8;
            m.f18 = c;
            m.f20 = d;
            GetServer()->Send(id, &m.refcount, 0);
        }
            break;
    }
    }
    return true;
}

// @ 0x00a32220
FixedHashMap::FixedHashMap(uint a, uint b)
{
    fixed_pool_base pool;
    pool.mpOwner = (uint32_t)this;
    pool.mpHead = 0;
    pool.init((char*)this + 0x1cc, 4000, 0x28, 4, 0);
    pool.mpPoolBegin = (uint32_t)((char*)this + 0x1cc);
    pool.mpPoolEnd = (uint32_t)((char*)this + 0x1cc + 4000);
    pool.mnNodeSize = 0x28;
    pool.mpBuckets = (uint32_t)((char*)this + 0x34);
    void* r = FUN_00921340_s00a3_1f20(0x65);
    ((FHMapBase*)this)->Ctor(r, a, &b, &b, b, &b, &pool);
    mfMaxLoadFactor = 10000.0f;
    mfGrowthFactor = 2.0f;
    mnRehashCount = 0;
    PrimePolicy pp;
    uint n = pp.GetBucketCount(mnElementCount);
    if (n > mnBucketCount)
        ((FHMapBase*)this)->Rehash(n);
}

struct HashTmpObj {
    uint32_t t0, t1;
    char rest[0x3f8];
    HashTmpObj(uint32_t* src) { ((HashTmp*)this)->Ctor(src); }
    ~HashTmpObj() { ((HashTmp*)this)->Dtor(); }
};

struct SwapTmp_00a32320 {
    uint32_t pre;
    HashTmpObj tmp;
    SwapTmp_00a32320(uint32_t* src) : tmp(src) {}
};

// @ 0x00a32320
void FUN_00a32320(uint32_t* x, uint32_t* y)
{
    SwapTmp_00a32320 w(x);
    if (x != y) {
        ((HashDst*)x)->Clear(x[0], x[1]);
        ((HashDst*)x)->Assign(y[0], y[1], w.pre);
    }
    if (y != &w.tmp.t0) {
        ((HashDst*)y)->Clear(y[0], y[1]);
        ((HashDst*)y)->Assign(w.tmp.t0, w.tmp.t1, w.pre);
    }
}

// @ 0x00a323e0
uint32_t* OuterMap::operator_index(uint32_t* key)
{
    uint32_t it[2];
    ((OMFind*)this)->Find(it, key);
    if (it[0] != mpBuckets[mnBucketCount])
        return (uint32_t*)(it[0] + 4);
    char cmp;                                   // empty hash/equal_to temporaries
    uint32_t t[0x1e0 / 4];                      // mapped_type() (fixed_hash_map<uint,float,20,21>)
    void* pt = ((OMTmp*)t)->Make(&cmp, &cmp);
    struct { uint32_t key; char val[0x1dc - 4]; } node;     // value_type(k, t)
    node.key = *key;
    ((OMNodeCtor*)&node.val)->Ctor(pt);
    ((OMInsert*)this)->Insert(it, &node, it[0] & 0xffffff00);   // by-value true_type: low byte 0
    uint32_t* r = (uint32_t*)(it[0] + 4);
    ((OMNodeDtor*)&node)->Dtor();
    // ~t: DoFreeNodes, then release the bucket array (pool slot or heap)
    ((OMFree*)t)->DoFreeNodes(t[1], t[2]);
    uint32_t* b = (uint32_t*)t[1];
    t[3] = 0;
    if (t[2] > 1 && b != (uint32_t*)t[0xc]) {
        if (b < (uint32_t*)t[9] || (uint32_t*)t[10] <= b)
            operator_delete__(b);
        else {
            *b = t[7];
            t[7] = (uint32_t)b;
        }
    }
    return r;
}

// @ 0x00a32550
void SystemDtor::Destroy()
{
    uint32_t* d = (uint32_t*)this;
    d[0] = (uint32_t)vtbl_01452d38;
    d[1] = (uint32_t)vtbl_01452d24;
    HTBASE(0x56efe)->Key_Free(d[0x56efe], d[0x56eff]);
    NoPoolTail<0x56efe>(d);
    FixedBuf<0x56edf>(d);
    ((SimpleA*)((char*)this + 0x15b77c))->a26da0();
    if (d[0x56dde])
        (*(void (__thiscall**)(void*))(*(uint32_t*)d[0x56dde] + 8))((void*)d[0x56dde]);
    CountedBuf<0x56dce>(d);
    HTBASE(0x563d5)->F24480(d[0x563d5], d[0x563d6]);
    PoolTail<0x563d5>(d);
    ((SimpleA*)((char*)this + 0x157c60))->a222c0();
    HTBASE(0x55d11)->F24480(d[0x55d11], d[0x55d12]);
    PoolTail<0x55d11>(d);
    ((SimpleA*)((char*)this + 0x157438))->ilb();
    HTBASE(0x4dffb)->TS_Free(d[0x4dffb], d[0x4dffc]);
    PoolTail<0x4dffb>(d);
    HTBASE(0x4de58)->F68fb70(d[0x4de58], d[0x4de59]);
    PoolTail<0x4de58>(d);
    HTBASE(0x4dde0)->TS_Free(d[0x4dde0], d[0x4dde1]);
    PoolTail<0x4dde0>(d);
    FixedBuf<0x4dda7>(d);
    FixedBuf<0x4d9b5>(d);
    HTBASE(0x4ca03)->F68fb70(d[0x4ca03], d[0x4ca04]);
    PoolTail<0x4ca03>(d);
    FixedBuf<0x4c610>(d);
    HTBASE(0x4b65e)->F68fb70(d[0x4b65e], d[0x4b65f]);
    PoolTail<0x4b65e>(d);
    FixedBuf<0x4b26b>(d);
    HTBASE(0x4a2b9)->F68fb70(d[0x4a2b9], d[0x4a2ba]);
    PoolTail<0x4a2b9>(d);
    HTBASE(0x49dee)->F2add0(d[0x49dee], d[0x49def]);
    PoolTail<0x49dee>(d);
    HTBASE(0x46cf3)->F2f6e0(d[0x46cf3], d[0x46cf4]);
    PoolTail<0x46cf3>(d);
    HTBASE(0x468f7)->TS_Free(d[0x468f7], d[0x468f8]);
    PoolTail<0x468f7>(d);
    HTBASE(0x466ef)->F24480(d[0x466ef], d[0x466f0]);
    PoolTail<0x466ef>(d);
    ((SimpleA*)((char*)this + 0x119ba4))->a23920();
    HTBASE(0x462ed)->TS_Free(d[0x462ed], d[0x462ee]);
    PoolTail<0x462ed>(d);
    HTBASE(0x462e5)->F26f30(d[0x462e5], d[0x462e6]);
    NoPoolTail<0x462e5>(d);
    HTBASE(0x4629f)->TS_Free(d[0x4629f], d[0x462a0]);
    PoolTail<0x4629f>(d);
    ((HT*)&d[0x46297])->RbNuke(d[0x4629a]);
    HTBASE(0x46290)->Fb6fdf0(d[0x46290], d[0x46291]);
    NoPoolTail<0x46290>(d);
    HTBASE(0x46288)->Fb6fdf0(d[0x46288], d[0x46289]);
    NoPoolTail<0x46288>(d);
    HTBASE(0x46280)->Fb6fdf0(d[0x46280], d[0x46281]);
    NoPoolTail<0x46280>(d);
    HTBASE(0x2010a)->F276e0(d[0x2010a], d[0x2010b]);
    PoolTail<0x2010a>(d);
    HTBASE(0xcf6)->TS_Free(d[0xcf6], d[0xcf7]);
    PoolTail<0xcf6>(d);
    HTBASE(0x8fa)->TS_Free(d[0x8fa], d[0x8fb]);
    PoolTail<0x8fa>(d);
    HTBASE(0x4fe)->F24480(d[0x4fe], d[0x4ff]);
    PoolTail<0x4fe>(d);
    HTBASE(0x102)->TS_Free(d[0x102], d[0x103]);
    PoolTail<0x102>(d);
    CountedBuf<0xe9>(d);
    CountedBuf<0xd5>(d);
    CountedBuf<0xc1>(d);
    CountedBuf<0xad>(d);
    CountedBuf<0x99>(d);
    CountedBuf<0x85>(d);
    if (d[0x7e])
        (*(void (__thiscall**)(void*))(*(uint32_t*)d[0x7e] + 4))((void*)d[0x7e]);
    ((SimpleA*)((char*)this + 0x198))->a227d0();
    ((SimpleA*)((char*)this + 0xf8))->f11e64d0();
    ((SimpleA*)((char*)this + 0xb8))->mutexDtor();
    d[0x28] = (uint32_t)vt_0140de80;
    d[0x27] = (uint32_t)vt_01403934;
    ((SimpleA*)((char*)this + 0x28))->f921e40();
    ((SimpleA*)((char*)this + 0x20))->f922e10();
    if (d[2]) {
        uint32_t h = d[2];
        d[2] = 0;
        RemoveHandler(h, d[3], d[4], d[5], d[6]);
    }
    d[1] = (uint32_t)vtbl_PaintSystem;
}

// @ 0x00a32ea0
void SystemProps::SetOutputProperty(uint32_t id, uint32_t prop, float value)
{
    InnerMap* m = ((OuterIdx*)((char*)this + 0x11b3c8))->Index(&id);
    uint32_t it;
    ((InnerFind*)m)->Find(&it, &prop);
    uint32_t saved = prop;
    if (it != m->mpBuckets[m->mnBucketCount]) {
        ((float*)it)[1] = value;
        return;
    }
    prop = prop & 0xffffff00;
    uint32_t kv[2];
    kv[0] = saved;
    ((float*)kv)[1] = value;
    char out[12];
    ((InnerInsert*)m)->Insert((uint32_t*)out, kv, prop);
}

// @ 0x00a32f20
void System_s00a3_2f20::Update(void* ctx, float dt)
{
    EA::Stopwatch_s00a3_2f20 watch(4, false);
    watch.Start();

    if (q2.FunF980() && s3f4) {
        if (rt::gpCmdStub)
            ((void (__thiscall*)(void*))AVS(rt::gpCmdStub, 0xc0))(rt::gpCmdStub);
        s3f4 = 0;
        q2.FunFee0(&q1);
        if (rt::gpCmdStub)
            ((void (__thiscall*)(void*))AVS(rt::gpCmdStub, 0xc4))(rt::gpCmdStub);
        q2.FunFdc0();
    }

    if (!q2.FunF980()) {
        uint32_t spins = 0;
        EA::LimitStopwatch_s00a3_2f20 dispatchTimer(3, false);
        dispatchTimer.SetTimeLimit(cq0, true);
        do {
            ++spins;
            if ((spins & 3) == 0 && !dispatchTimer.HasTimeLeft())
                break;
            if (!q2.FunF9a0())
                break;
            ((void (__thiscall*)(System_s00a3_2f20*, void*))AVS(this, 0x130))(this, q2.GetArg());
        } while (true);
        if (q2.FunF990() == 0) {
            q2.FunFdd0();
            ++s3f8;
        }
    }

    bool muted = (mbMutedForSilence || mbMuted || mbMutedForFocus || mbMutedByProperty);
    if (muted != (b9a != 0))
        MuteAll(muted, false);

    if (mObj157c60.pNext != (void*)&mObj157c60) {
        float delta = dt - cqName;
        if (delta < 0.0f)
            delta = 0.0f;

        if (pObj == (T26990*)&mObj157c60) {
            ((void (__thiscall*)(System_s00a3_2f20*, float, uint32_t))AVS(this, 0x208))(this, delta, z6b0);
            cqName = dt;
            pObj = (T26990*)mObj157c60.pNext;
        }

        uint32_t spins = 0;
        EA::LimitStopwatch_s00a3_2f20 bindTimer(3, false);
        bindTimer.SetTimeLimit(cq2, true);
        do {
            ++spins;
            if ((spins & 3) == 0 && !bindTimer.HasTimeLeft())
                break;
            if (pObj == (T26990*)&mObj157c60)
                break;
            T26990* pCur = pObj;
            ((void (__thiscall*)(void*, float, float))AVS(pCur->pObj, 8))(pCur->pObj, dt, delta);
            if (pObj == pCur)
                pObj = (T26990*)pCur->pNext;
        } while (true);

        if (pObj == (T26990*)&mObj157c60) {
            void* it[2];
            mHT3.Begin(it);
            void* pEnd = mHT3.mpBuckets[mHT3.mBucket];
            void* pNode = it[0];
            void** ppBucket = (void**)it[1];
            while (pNode != pEnd) {
                void* pValue = *(void**)((char*)pNode + 4);
                ((void (__thiscall*)(void*, uint32_t))AVS(pValue, 0x24))(pValue, z6b0);
                pNode = *(void**)((char*)pNode + 8);
                while (pNode == 0) {
                    pNode = *++ppBucket;
                }
            }
            ((void (__thiscall*)(System_s00a3_2f20*))AVS(this, 0x13c))(this);
            MaintainLRU();
            ((void (__thiscall*)(System_s00a3_2f20*))AVS(this, 0x20c))(this);
        }
    }

    ((void (__thiscall*)(System_s00a3_2f20*))AVS(this, 0x204))(this);

    while (rb0 != rb1) {
        if (!(rt::gDeferredGuard & 1)) {
            rt::gDeferredGuard |= 1;
            rt::gDeferredCmds.mpBegin = rt::gDeferredStorage;
            rt::gDeferredCmds.mpEnd = rt::gDeferredStorage;
            rt::gDeferredCmds.mpCap = rt::gDeferredStorage;
            rt::gDeferredCmds.mpGuard = &rt::gDeferredGuard;
            atexit(DeferredListInit);
        }
        rt::gDeferredCmds.Assign(rb0, rb1);

        uint32_t* pRec = rt::gDeferredCmds.mpBegin;
        uint32_t* pEnd = rt::gDeferredCmds.mpEnd;
        if (pRec != pEnd) {
            do {
                rt::CmdRecord* pCmd = (rt::CmdRecord*)pRec;
                if (pCmd->mType == 0x3a0fd6e) {
                    rt::MsgObj* pObj2 = (rt::MsgObj*)((void* (__thiscall*)(System_s00a3_2f20*, uint32_t))AVS(this, 0x1d4))(this, pCmd->mArg1);
                    if (pObj2)
                        ((void (__thiscall*)(rt::MsgObj*))AVS(pObj2, 0))(pObj2);
                    if (pObj2)
                        ((void (__thiscall*)(rt::MsgObj*, int, int))AVS(pObj2, 0x18))(pObj2, 0, 1);
                    if (pObj2)
                        ((void (__thiscall*)(rt::MsgObj*))AVS(pObj2, 4))(pObj2);
                } else if (pCmd->mType == 0x3a129ee) {
                    if (pCmd->mArg1 >= 0x7d1 && pCmd->mArg1 <= 0xbb8) {
                        void* found;
                        mPolyB.Find(&found, &pCmd->mArg1);
                        if (found != (void*)mPolyB.mpBuckets[mPolyB.mBucket]) {
                            mPolyB.Erase(&pCmd->mArg1);
                            *mIdWrite++ = pCmd->mArg1;
                            if (mIdWrite == (uint32_t*)mPoolB.mpLimit)
                                mIdWrite = (uint32_t*)mPoolB.mpFirst;
                            if (mIdWrite == mIdRead) {
                                if (++mIdRead == (uint32_t*)mPoolB.mpLimit)
                                    mIdRead = (uint32_t*)mPoolB.mpFirst;
                            } else {
                                ++mIdDropped;
                            }
                        }
                    }
                } else if (pCmd->mType == 0x63e3de7) {
                    if (pCmd->mArg3) {
                        ((void (__thiscall*)(void*, uint32_t, int))AVS((void*)pCmd->mArg3, 0x18))((void*)pCmd->mArg3, pCmd->mArg2, pCmd->mArg2 != 0);
                        void* pRelease = (void*)pCmd->mArg3;
                        pCmd->mArg3 = 0;
                        ((void (__thiscall*)(void*))AVS(pRelease, 4))(pRelease);
                    }
                }
                q5.Fun102e0(0x3a0fcce);
                q5.Fun10120(0x3a0fce5, pCmd->mType);
                q5.Fun10120(0x3475385, pCmd->mArg1);
                q5.Fun10120(0x39e3c9f, pCmd->mArg2);
                q5.Fun10120(0x39e3ca6, pCmd->mArg3);
                q5.FunF940();
                pRec += 5;
            } while (pRec != pEnd);
        }
        rt::gDeferredCmds.EraseRange(rt::gDeferredCmds.mpBegin, rt::gDeferredCmds.mpEnd);
    }
}

// @ 0x00a33500
namespace eastl {
fixed_hash_map_u32_nested::fixed_hash_map_u32_nested(const hash_tag&, const equal_to_tag&)
{
    fixed_pool_base_s00a3_2f20 pool;
    pool.mpHead = 0;
    pool.init(mNodeStorage, sizeof(mNodeStorage), 0x1e8, 4, 0);

    node_pool_desc desc;
    desc.mpMap      = this;
    desc.mpNodes    = mNodeStorage;
    desc.mpNodesEnd = mNodeStorage + sizeof(mNodeStorage);
    desc.mnNodeSize = 0x1e8;
    BaseInit(RequestPoolBookkeeping(0x65), desc);

    mLoadFactor    = 10000.0f;
    mGrowthFactor  = 2.0f;
    mnElementCount = 0;

    uint32_t nBucketCount = BucketCount(mpBucketArray);
    if (mnBucketCount < nBucketCount)
        Rehash(nBucketCount);
}
}  // namespace eastl

// @ 0x00a33600
System_s00a3_2f20::System_s00a3_2f20()
: mAutoMsg(),
      mTickThread(),
      mTickCtx(0, 1),
      mAllocator(), mAllocator2(),
      mMutex(0, 1),
      mDebugChannel("audio filesys", 0, 0),
      mResourceDeviceDriver(),
      mpConfiguration(0),
      q0(), q1(), q2(), q3(), q4(), q5(),
      mMixables(TagA(), TagB()),
      mPrimitives(TagA(), TagB()),
      mMapA(TagA(), TagB()),
      mPrimitiveProxys(TagA(), TagB()),
      mBig(TagA(), TagB()),
      env0(), env1(), env2(),
      mEmitterConstructorMap(TagA(), TagB()),
      env3(),
      mMapB(TagA(), TagB()),
      mVecA(),
      mHT2a(TagA(), TagB()),
      mMapC(TagA(), TagB()),
      mOutputs(TagA(), TagB()),
      mSubscriptions(TagA(), TagB()),
      mPolyA(TagA(), TagB()),
      mPoolA(1000),
      mPolyB(TagA(), TagB()),
      mPoolB(1000),
      mPolyC(TagA(), TagB()),
      mPoolC(1000),
      mJ(TagA(), TagB()),
      mK(TagA(), TagB()),
      mExternalIds(TagA(), TagB()),
      mHT2b(TagA(), TagB()),
      mObj157c60(),
      mHT3(TagA(), TagB()),
      env4()
{
    mRefCount = 0;
    mCommandBufferSize = 0x1f400;
    mbInitialized = false; mbPaused = false; mbMutedForSilence = false;
    mbMutedForFocus = false; mbMutedByProperty = false; mbMuted = false;
    b9a = 0; b9b = 0;
    mDacOutputMode = 1.0f;
    mDacOutputSampleRate = 44100.0f;
    mNumOutputChannels = 2;
    mStreamPoolNumStreams = 10;
    mStreamPoolBufferSize = 0x1f400;
    mStreamPoolMaxRequests = 2;
    mMax3d = 0;
    mPerformanceLevel = 3;
    cq0 = 0x1f4; cq1 = 0x1f4; cq2 = 0x1f4; cqName = 0.0f;
    s3f4 = 0; s3f5 = 0; s3f8 = 0; s3fc = 0; s3fd = 1; s400 = 5.0f;

    lst[0] = (uint32_t)&lst; lst[1] = (uint32_t)&lst;
    lstA = 0; lstB = 0; lstC = 0;

    fv0 = fvBuf; fv1 = fvBuf; fv3 = fvBuf; fv2 = fvBuf + 50;
    listNext = (uint32_t)&listNext; listPrev = (uint32_t)&listNext;

    pObj = &mObj157c60;
    z158f4c = 0;

    z6b0 = z6b4 = z6b8 = z6bc = 0;
    z738 = z73c = z740 = 0;
    z750 = z754 = z758 = z75c = z760 = 0;
    n764 = 100;
    ageSecs = g_cacheAge;
    m770 = 0x6400000;
    b774 = 0;
    z778 = 0;

    rb0 = rb1 = rb4 = (uint32_t*)((char*)this + 0x15b794);
    rb2 = (uint32_t*)((char*)this + 0x15b794 + 0x3e8);
    sb0 = sb1 = sb4 = (uint32_t*)((char*)this + 0x15bb94);
    sb2 = (uint32_t*)((char*)this + 0x15bb94 + 0x50);

    b15bbf0 = 0;
    posA[0] = g_vec3[0]; posA[1] = g_vec3[1]; posA[2] = g_vec3[2];
    posB[0] = g_vec3[0]; posB[1] = g_vec3[1]; posB[2] = g_vec3[2];
    for (int i = 0; i < 9; ++i) { mat0[i] = (i % 4 == 0) ? 1.0f : 0.0f; }
    for (int i = 0; i < 9; ++i) { mat1[i] = (i % 4 == 0) ? 1.0f : 0.0f; }
}

// @ 0x00e23250
int cSPUIPosse::GetAudioCount()
{
    int count = 0;
    for (cAudioEntry* it = mpAudioBeginA4; it < mpAudioEndA8; ++it) {
        cAudioObject* obj = it->mpObject4;
        if (VT_BC_0(obj) == 2 || VT_BC_0(obj) == 4)
            ++count;
    }
    return count;
}
