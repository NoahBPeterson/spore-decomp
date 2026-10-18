// src/game/SPAudio/AudioSystem.cpp -- migrated from slice(s) s00a32f20, s00a31f20, s00a31170, s00a30460, s00a2e650, s00a2d790, s00a2c6c0, s00a2a020, s00a24e10, s00a23360, s00a22220, s00a20060, s00432830 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

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
struct PropSet {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void GetFloat(u32 key, float* out);   // +0x10
};
struct SoundOrd {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual bool Flag(int which, int z);          // +0x20
    virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
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
struct DrvBA22 : RefBaseA22 {
    u32   pad[0x1e];       // +8 .. +0x80
    void* mArg;            // +0x80
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
extern int   g_16e61a8;
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
struct RefVec {
    RefCounted** mpBegin;   // +0
    RefCounted** mpEnd;     // +4
    void Destroy();         // 0x00a23920
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
struct RBTree {
    void   Assign(void* arg);                   // 0x00a24210 (opaque rbtree assignment)
    void*  AllocNode2(const void* src, void* parent); // 0x00a243e0
    RBNode_s00a2_3360* CloneNode(RBNode_s00a2_3360* src, RBNode_s00a2_3360* parent);   // 0x00a24530
};
void __cdecl sub_00a212b0();
void __cdecl sub_00a21310();
void __cdecl sub_00a22410();
struct Elem20 { u32 d0, d1, d2, d3; void* ref; };
struct DeviceDriver { void ctor(const char* name); };           // 0x011e5d80
struct Mutex_s00a2_3360 {
    u32 a;
    void ctor(int a, int b);     // 0x009222a0
    int  Lock(void* p);          // 0x009221b0
    int  Unlock();               // 0x00922270
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
    void*   FindById(void* id, void* a, void* b, void* c);  // 0x00a24970
    void*   FindAndCall1(void* id, void* a, void* b, void* c, void* d); // 0x00a24a90
    bool    FindAndCall2(void* id, void* a, void* b, void* c, void* d); // 0x00a24b40
    int     FindAndCall3(void* id, void* a, void* b, void* c, void* d); // 0x00a24bf0
    void*   FindAndCall4(void* id);  // 0x00a24cb0
    long long FindAndCall5(void* id); // 0x00a24d60

    bool    Tick3(void* a, void* b, void* c);   // 0x00a24930
};
// ---- items of slice s00a23360 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
RBNode_s00a2_3360* __cdecl RB_AllocNode(const RBNode_s00a2_3360* src, RBNode_s00a2_3360* parent);   // defined at 0x00a245e0, called earlier in the TU

// ---- items of slice s00a24e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_lockName[];   // 0x01452970
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
struct ARC {
    Obj_s00a2_4e10* p;
    ARC() : p(0) {}
    ARC(Obj_s00a2_4e10* o) : p(o) { if (p) p->AddRef(); }
    ARC& assign(Obj_s00a2_4e10* o);        // 0x00b5f950 (out of line)
    ~ARC() { if (p) p->Release(); }
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
    ~Str16() { if ((int)(((char*)cap - (char*)b) & ~1) > 2 && b) operator_delete__(b); }
};
Str16 ConvertToString16(const char* s, int n);   // 0x0093c5a0
struct StrOut { int a, b, c; };
typedef void (__cdecl* StringFn)(StrOut*, int, int, int, int, int);
extern StringFn g_pfnString;                     // 0x0154c464
struct Obj30 {
    Obj_s00a2_4e10* Init();                       // 0x00a22cf0
};
struct Obj30b {
    Obj_s00a2_4e10* Init();                       // 0x00a22cf0 (identical code folded)
};
struct Factory {
    virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
    virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
    virtual void f08();
    virtual bool Create(const char* a, Obj_s00a2_4e10* o, int c, int d);   // +0x24
    bool MakeProps(const char* a, Obj_s00a2_4e10** out, int c, int d);     // 00a25090
    bool MakeAudio(const char* a, ARC* out, int c, int id);     // 00a25190
};
struct Namer {
    virtual void n00(); virtual void n01(); virtual void n02(); virtual void n03();
    virtual void n04(); virtual void n05(); virtual void n06(); virtual void n07();
    virtual void n08(); virtual void n09(); virtual void n0a(); virtual void n0b();
    virtual void n0c(); virtual void n0d(); virtual void n0e(); virtual void n0f();
    virtual void n10(); virtual void n11(); virtual void n12(); virtual void n13();
    virtual void n14(); virtual void n15(); virtual void n16(); virtual void n17();
    virtual void n18(); virtual void n19(); virtual void n1a(); virtual void n1b();
    virtual void n1c(); virtual void n1d(); virtual void n1e(); virtual void n1f(); virtual void n20(); virtual void n21();
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
    GIter    find(const unsigned& key);   // 0x00645ed0 (pair<uint,float>)
    FNode*   end() { return mBuckets[mBucketCount]; }
};
struct NNode { unsigned key; FHT inner; };
struct NHT {
    int      pad;
    NNode**  mBuckets;
    unsigned mBucketCount;
    GIter    find(const unsigned& key);   // 0x00a23b00
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
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
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
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c0a();
    virtual void Get(unsigned key, int* out);                 // +0x2c
};
struct DbgObj {
    static void* operator new(unsigned size, const char* n, int a, int b, int c, int d);   // 0x00926020
    static void operator delete(void* p, const char* n, int a, int b, int c, int d);
    DbgObj();                                                                               // 0x00a19d60
    char pad[0x70];
};
struct ErrIf {
    virtual void e0(); virtual void e1(); virtual void e2();
    virtual bool Query(const void* iid, ARC* out, int a, int b, int c, int d);   // +0xc
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11();
    virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
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
void __cdecl FUN_00a136f0(void*, void*, void*);                  // 0x00a136f0
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
struct SmallStubs {
    int  GetOrInsert(int* key);
    void Dtor();
    void DestroyBuckets(int param_2, u32 param_3);
    int  EraseRange(int param_2, int param_3);
    int* VecIntInsert(int* param_2, int* param_3);
};
struct ArrOwner { void* FindInsertPos(void*, void*, void*); };  // 0x00a22730
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
struct XF {
    void* hashtable_find(void* key, void* out);      // 0x645ed0
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
void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void* __cdecl FUN_00a17090(uint size);
void* __cdecl FUN_00a17100(void* p);
struct AudioSystem {
    uchar pad[0x140000];

    // 00a2d790
    bool RegisterPrimitive(void* p);
    // 00a2d880
    void* FUN_00a2d880(uint key, void* out);
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
    // 00a2dfe0
    void FUN_00a2dfe0(void* p);
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
void __cdecl EaDelete(void* p);                                                                    // 0xf47380
struct MapUU {
    int& operator[](const uint32_t& key);  // 0x00a2e060
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
struct EventMsg {
    unsigned a, b, c, d;
    void* ref;
    EventMsg(unsigned a_, unsigned b_, unsigned c_, unsigned d_, void* r) : a(a_), b(b_), c(c_), d(d_), ref(r)
    {
        if (ref)
            ObjAddRef(ref);
    }
    ~EventMsg()
    {
        if (ref)
            ObjRelease(ref);
    }
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
    FixedVec11* ctor(int param_2);
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
// ---- items of slice s00a30460 end

// ---- items of slice s00a31170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtRefBase[];             // 0x013effa8
extern void* g_vtFactoryA[];            // 0x01452a44
extern void* g_vtFactoryB[];            // 0x01452a78
extern void* g_vtFactoryC[];            // 0x01452ac0
extern const char g_audioName[];        // 0x0140a5a0 "Audio"
extern int g_FsAllocatorManager;                            // 0x016f4b10
extern char g_1552da0[];                // 0x01552da0
extern const char g_systemName[];       // 0x01452d1c "system"
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
class IStream {
public:
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vc();
    virtual void v10(); virtual void v14();
    virtual void Close();                                   // +0x18
    virtual uint32_t GetSize();                             // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual uint32_t Read(void* buf, uint32_t size);        // +0x30
};
class IResource {
public:
    virtual void v0(); virtual void v4();
    virtual int Release();                                  // +0x08
    virtual void vc(); virtual void v10(); virtual void v14();
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
    virtual void v0(); virtual void v4(); virtual void v8();
    virtual uint32_t GetTypeID();                           // +0x0c
};
class IResourceManager {
public:
    V16(m1)
    V1(m40)
    virtual void RegisterFactory(int kind, IFactory* factory, int flags);   // +0x44
    virtual void m48(); virtual void m4c(); virtual void m50(); virtual void m54();
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
};
struct StreamPool;
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
    HashIter_s00a3_1170* find(HashIter_s00a3_1170* out, const uint32_t& key);                      // 0x00645ed0
    void insert(HashInsertResult* out, const PolyPair* value, bool b);       // 0x00a26ce0
};
struct EmitterMap {                     // fixed_hash_map<uint32_t, IEmitter*(*)()>
    uint32_t mData;
    void*& At(const uint32_t& key);     // 0x00a2a510 operator[]
};
struct IdRing {                         // ring buffer of ids
    uint32_t mData;
    void push_back(const uint32_t& id); // 0x00a21d30
};
struct IdPool {
    uint32_t mData[0xf0 / 4];
    void Init(unsigned capacity);       // 0x00a102a0
};
void* __cdecl ConstructEmitterSndPlayer();                  // 0x00a20700
struct IntArrayRef {                    // {int* base; int index} at +0x118a20
    int* mpBase;
    int mIndex;
};
template<int N> struct Gap { uint32_t pad[N]; };
class cSystem {
public:
    V16(a)                              // slots 0x00..0x3c
    V16(b)                              // 0x40..0x7c
    V16(c)                              // 0x80..0xbc
    V4(d)                               // 0xc0..0xcc
    V4(e)                               // 0xd0..0xdc
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
    V1(t)                               // 0x1b8
    virtual void Hook1bc(const char* p);                        // +0x1bc
    V1(u)                               // 0x1c0
    virtual void Hook1c4();                                     // +0x1c4
    virtual void Hook1c8();                                     // +0x1c8
    V4(v) V4(w) V1(x)                   // 0x1cc..0x1ec
    virtual void Hook1f0();                                     // +0x1f0

    Gap<(0x90 - 4) / 4> pad04;
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
    Gap<(0x2b4 - 0x204) / 4> pad204;
    IdPool mPoolA;                      // +0x2b4
    IdPool mPoolB;                      // +0x3a4
    Gap<(0x118a20 - 0x494) / 4> pad494;
    IntArrayRef mIdArray;               // +0x118a20
    Gap<(0x118a78 - 0x118a28) / 4> pad118a28;
    EmitterMap mEmitterMap;             // +0x118a78
    Gap<(0x131840 - 0x118a7c) / 4> pad118a7c;
    IdRing mIdRing;                     // +0x131840
    Gap<(0x137fe8 - 0x131844) / 4> pad131844;
    PolyphonyMap mPolyphonyMap;         // +0x137fe8
    Gap<(0x15b750 - 0x137ff4) / 4> pad137ff4;
    uint32_t mIterValue;                // +0x15b750
    void* mIterPos;                     // +0x15b754
    uint32_t mIter8, mIterC, mIter10;   // +0x15b758..0x15b760
    Gap<(0x15b778 - 0x15b764) / 4> pad15b764;
    IFactory* mpFactoryB;               // +0x15b778

    void MuteAll(bool mute, bool immediate);        // 0x00a233b0
    void PreloadConfigurations();                   // 0x00a30940
    void FUN_a2ef60();                              // 0x00a2ef60
    void FUN_a2da30();                              // 0x00a2da30
    bool InitAT();
};
// ---- items of slice s00a31170 end

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
    bool DoCommandMainThread(EA::Audio::Command_s00a3_1f20* cmd);
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
    ~T570(); uint32_t d;
};
struct T1040
{
    T1040(int n); // 0xa31040
    ~T1040(); uint32_t d;
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
    ~T26990(); uint32_t d;
};
struct TF410
{
    TF410(const TagA&, const TagB&); // 0xa2f410
    ~TF410(); uint32_t d;
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
struct IHandler {
    IHandler() {}
    virtual void HandleMsg();
    virtual ~IHandler();
};
struct IHandlerRC_s00a3_2f20 : IHandler {
    IHandlerRC_s00a3_2f20() {}
    virtual void HandleMsg();
    virtual ~IHandlerRC_s00a3_2f20();
};
struct AutoHandler {
    void* mpServer; void* mpHandler; uint32_t* mpIdArray; uint32_t mnIdArrayCount; uint32_t mnPriority;
    AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
    ~AutoHandler();
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
    System_s00a3_2f20();
    virtual void Init();
    virtual ~System_s00a3_2f20();
    virtual void HandleMsg();

    AutoHandler       mAutoMsg;          // +0x08
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
    PAD(pad_s, 0x128ae0 + 4, 0x12c9ac);
    T1040          mPoolA;            // +0x12c9ac
    PAD(pad_t, 0x12c9ac + 4, 0x12d974);
    T570          mPolyB;            // +0x12d974
    PAD(pad_u, 0x12d974 + 4, 0x131840);
    T1040          mPoolB;            // +0x131840
    PAD(pad_v, 0x131840 + 4, 0x132808);
    T570          mPolyC;            // +0x132808
    PAD(pad_w, 0x132808 + 4, 0x1366d4);
    T1040          mPoolC;            // +0x1366d4
    PAD(pad_x, 0x1366d4 + 4, 0x13769c);
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
    PAD(pad_ad, 0x157c60 + 4, 0x158f48);
    T26990*         pObj;              // +0x158f48
    uint32_t          z158f4c;
    TF410          mHT3;              // +0x158f50
    PAD(pad_ae, 0x158f50 + 4, 0x15b6b0);
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
// ---- items of slice s00a32f20 end

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
    u32* dst = (u32*)((char*)this + 0x15b6c0 + idx * 0xc);
    const u32* src = (const u32*)a;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
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
    ((Mutex*)((char*)this + 0xb8))->Lock((void*)0x1452970);
}












// @ 0x00a21100
bool Sys::HasLocation()
{
    int n = ((DPF*)((char*)this + 0xb8))->GetLocation();
    return n > 0;
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
: mArg(arg), mZero(0) {}











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
    if (!b15bbf0)
        return 0.0f;
    float dx = pos[0] - p[0];
    float dy = pos[1] - p[1];
    float dz = pos[2] - p[2];
    return (float)sqrt((double)(dy * dy + (dz * dz + dx * dx)));
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
void RefVec::Destroy()
{
    RefCounted** it = mpBegin;
    RefCounted** end = mpEnd;
    for (; it < end; ++it) {
        RefCounted* p = *it;
        if (p)
            p->Release();
    }
    RefCounted** begin = mpBegin;
    if (begin) {
        if (*(int*)((char*)begin - 4) != 0)
            operator_delete__(begin);
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
void RBTree::Assign(void* arg)
{
    // Opaque eastl rbtree range-copy helper: rebuild the tree from the source range.
    (void)arg;
    sub_00a212b0();
    sub_00a21310();
    sub_00a22410();
}










// @ 0x00a243e0
void* RBTree::AllocNode2(const void* src, void* parent)
{
    (void)parent;
    struct Node20 { u32 d[5]; };
    Node20* n = (Node20*)operator new(0x14, "EASTL", 0, 0, EA_FILE, 0xd1);
    if (n) {
        const u32* s = (const u32*)src;
        n->d[0] = s[0];
        n->d[1] = s[1];
        n->d[2] = s[2];
        n->d[3] = s[3];
        void* v = (void*)s[4];
        n->d[4] = (u32)v;
        if (v) {
            void*** vt = (void***)v;
            vc<void>(v, 0);
            (void)vt;
        }
    }
    return n;
}










// @ 0x00a24480
void PHTable::FreeBuckets(PHNode** buckets, u32 count)
{
    for (u32 i = 0; i < count; ++i) {
        PHNode* p = buckets[i];
        while (p) {
            PHNode* nxt = p->next;
            if (p->key || p->next) {
                // release the value pointer stored at +0 (the value is the node payload)
            }
            if (p != (PHNode*)mpInline) {
                if ((void*)p < mpPoolBegin || (void*)p >= mpPoolEnd) {
                    operator_delete__(p);
                } else {
                    p->key = (int)mpFreeList;
                    mpFreeList = p;
                }
            }
            p = nxt;
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
RBNode_s00a2_3360* __cdecl RB_AllocNode(const RBNode_s00a2_3360* src, RBNode_s00a2_3360* parent)
{
    RBNode_s00a2_3360* n = (RBNode_s00a2_3360*)operator new(0x18, "EASTL", 0, 0, EA_FILE, 0xd1);
    if (n) {
        n->key0 = src->key0;
        n->key1 = src->key1;
    }
    n->left = 0;
    n->right = 0;
    n->parent = parent;
    n->color = src->color;
    return n;
}










// @ 0x00a24750
Elem20* __cdecl CopyElems20(Elem20** out, Elem20* first, Elem20* last)
{
    *out = last;
    for (; first != last; first += 1) {
        Elem20* dst = *out;
        if (dst) {
            dst->d0 = first->d0;
            dst->d1 = first->d1;
            dst->d2 = first->d2;
            dst->d3 = first->d3;
            void* v = first->ref;
            dst->ref = v;
            if (v)
                vc<void>(v, 0);
        }
        *out += 1;
    }
    return *out;
}










// @ 0x00a247f0
void RDD::Construct()
{
    ((DeviceDriver*)this)->ctor("resman:");
    vftable = (void*)0x1452b00;
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mMutex.ctor(0, 1);
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
        *(unsigned int*)&sw.mnStartTime = (unsigned int)c;
        *(unsigned int*)((char*)&sw.mnStartTime + 4) = (unsigned int)(c >> 32);
    }
    *(unsigned int*)&sw.mnTotalElapsedTime = 0;
    *(unsigned int*)((char*)&sw.mnTotalElapsedTime + 4) = 0;
}










// @ 0x00a24900
void ProfileTimer::Accumulate()
{
    long long e = sw.GetElapsedTimeFloat();
    float* acc = (float*)mpAccumulator;
    *acc = (float)e * sw.mfCyclesToUnitsCoefficient + *acc;
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
    g_pfnString(&out, (int)ConvertToString16(s, -1).b, 0, 0, 0, 0); // 0x0154c464
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
    GIter it = mNested.find(k1);
    NNode* node = (NNode*)it.node;
    if (node != mNested.end()) {
        GIter jt = node->inner.find(k2);
        if ((FNode*)jt.node != node->inner.end()) {
            *out = ((FNode*)jt.node)->val;
            return true;
        }
    }
    return false;
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
    FUN_00a136f0(local_18, &k, 0);
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








// @ 0x00a2ae90
int SmallStubs::EraseRange(int param_2, int param_3)
{
    u32 u = (u32)(size_t)((ArrOwner*)this)->FindInsertPos((void*)param_3,
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
    *(int*)((char*)this + 4) += ((param_3 - param_2) / 0x14) * 0x14;
    return param_2;
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
void* AudioSystem::FUN_00a2d880(uint key, void* out)
{
    void* it;
    ((XF*)((uchar*)this + 0x23e4))->hashtable_find(&key, &it);
    if (*(uint*)it != *(uint*)(*(uint*)((uchar*)this + 0x23e8) +
                              *(int*)((uchar*)this + 0x23ec) * 4))
        return 0;
    void* node = FUN_00a17090(0x1c);
    if (node) node = FUN_00a17100(this);
    ((void (__thiscall*)(void*))vc_s00a2_d790(node, 0))(node);
    void* slot = ((XF*)((uchar*)this + 0x23e4))->FUN_00a2a510(out);
    *(void**)slot = node;
    return (void*)1;
}






// @ 0x00a2d940
void* AudioSystem::FUN_00a2d940(void* arg)
{
    *(void**)this = (void*)0x1452cb0;
    ((XF*)((uchar*)this + 4))->FUN_00a26fa0(arg);
    return this;
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






// @ 0x00a2d9d0
void* AudioSystem::FUN_00a2d9d0(uchar flags)
{
    ((XF*)((uchar*)this + 4))->DoNukeSubtree(*(void**)((uchar*)this + 0x10));
    *(void**)this = (void*)0x13eb394;
    if (flags & 1) operator_delete(this);
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
    for (uint* it = begin; it != end; ++it) {
        void* o = (void*)*it;
        if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 0))(o);
        ((XF*)o)->FUN_00a2bb30();
        if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 4))(o);
    }
    // compact the vector
    uint* p = begin;
    for (; p != end; ++p) {
        if (*p) {
            void* o = (void*)*p;
            ((void (__thiscall*)(void*))vc_s00a2_d790(o, 4))(o);
        }
    }
    uint count = (uint)(end - begin);
    *(uint**)((uchar*)this + 0x119ba8) = begin - count;
    if (DAT_016e61a8) FUN_0112c620();
    return true;
}






// @ 0x00a2dfe0
void AudioSystem::FUN_00a2dfe0(void* p)
{
    uchar* vec = (uchar*)this;
    void** cur = *(void***)(vec + 4);
    if (cur < *(void***)(vec + 8)) {
        *(void***)(vec + 4) = cur + 1;
        if (cur) {
            void* o = *(void**)p;
            *cur = o;
            if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 4))(o);
        }
    } else {
        ((XF*)vec)->FUN_00a2ac20(cur, p);
    }
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






// @ 0x00a2e0e0
int AudioSystem::FUN_00a2e0e0(uint* p)
{
    uchar* ht = (uchar*)this;
    int before = *(int*)(ht + 0xc);
    uint idx = *p % *(uint*)(ht + 8);
    uint* bucket = (uint*)(*(int*)(ht + 4) + idx * 4);
    if (*bucket) {
        uint* node;
        for (;;) {
            node = (uint*)*bucket;
            if (*p == *node) break;
            bucket = node + 9;
            if (!node[9]) break;
        }
        uint v = *bucket;
        while (v != 0 && (node = (uint*)*bucket, *p == *node)) {
            *bucket = node[9];
            operator_delete(node);
            *(int*)(ht + 0xc) -= 1;
            v = *bucket;
        }
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






// @ 0x00a2e260
void AudioSystem::FUN_00a2e260(void* p)
{
    uchar* vec = (uchar*)this;
    uchar* cur = *(uchar**)(vec + 4);
    if (cur < *(uchar**)(vec + 8)) {
        *(uchar**)(vec + 4) = cur + 0x14;
        if (cur) {
            memcpy(cur, p, 0x10);
            void* o = *(void**)((uchar*)p + 0x10);
            *(void**)(cur + 0x10) = o;
            if (o) ((void (__thiscall*)(void*))vc_s00a2_d790(o, 0))(o);
        }
    } else {
        ((XF*)vec)->FUN_00a2af30(cur, p);
    }
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
        node = operator_new(0x28, "EASTL", 0, 0,
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
    (void)p;
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
    HIter it = m->find(k);
    if (it.node == m->End())
        return false;
    it = m->erase(it);
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
FixedVec11* FixedVec11::ctor(int param_2)
{
    u32* p = storage;
    f10 = p;
    mpEnd = p;
    mpBegin = p;
    mpCap = p + 1001;
    resize(param_2 + 1);
    fStart = (u32)mpBegin;
    fEnd = (u32)mpBegin;
    fCount = 0;
    return this;
}




// @ 0x00a310b0
FixedVec11b* FixedVec11b::ctor(u32* param_2)
{
    u32* p = storage;
    f10 = p;
    mpEnd = p;
    mpBegin = p;
    mpCap = p + 250;
    InitRange(param_2[0], param_2[1], param_2);
    return this;
}



// @ 0x00a31170
bool cSystem::InitAT()
{
    mbMuteApplied = false;
    int* slot = &mIdArray.mpBase[mIdArray.mIndex];
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


// @ 0x00a32320
void FUN_00a32320(uint32_t* x, uint32_t* y)
{
    struct { uint32_t pre; uint32_t t0, t1; char rest[0x3f0]; } tmp;
    ((HashTmp*)&tmp.t0)->Ctor(x);
    if (x != y) {
        ((HashDst*)x)->Clear(x[0], x[1]);
        ((HashDst*)x)->Assign(y[0], y[1], tmp.pre);
    }
    if (y != &tmp.t0) {
        ((HashDst*)y)->Clear(y[0], y[1]);
        ((HashDst*)y)->Assign(tmp.t0, tmp.t1, tmp.pre);
    }
    ((HashTmp*)&tmp.t0)->Dtor();
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
