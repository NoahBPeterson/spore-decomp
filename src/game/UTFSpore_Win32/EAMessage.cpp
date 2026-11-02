// src/game/UTFSpore_Win32/EAMessage.cpp -- migrated from slice(s) s010678e0, s00883730, s00884a20 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAMessage.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/MessageQueue.h"
#include "EA/Thread/Mutex.h"
#include "EA/Messaging/Server.h"
#include "EA/Stopwatch.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetRecord.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern void* e_opnew(int size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern void  e_opdel(void* p);                       // 0xf47380
extern void* e_951bb0(void* first, void* last, void* dst);  // 0x951bb0
extern void  e_c50ad0(void* dst, void* first, void* last);  // 0xc50ad0
extern int   g_1427918;         // 0x1427918  (mutex Lock user-data tag)
extern void* g_1427920;         // 0x1427920  Server vftable
extern void* g_154df28;         // 0x154df28  default (empty) bucket array
extern float g_1485720;         // 0x1485720  (1.0f)
extern float g_1470f1c;         // 0x1470f1c  (2.0f)

// ---- items of slice s00884a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
extern void* e_opnew(int size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern void  e_opdel(void* p);                       // 0xf47380
extern void* e_951bb0(void* first, void* last, void* dst);  // 0x951bb0
extern void  e_c50ad0(void* dst, void* first, void* last);  // 0xc50ad0
extern int   g_1427918;         // 0x1427918  (mutex Lock user-data tag)
extern void* g_1427920;         // 0x1427920  Server vftable
extern void* g_154df28;         // 0x154df28  default (empty) bucket array
extern float g_1485720;         // 0x1485720  (1.0f)
extern float g_1470f1c;         // 0x1470f1c  (2.0f)
struct Mutex {
    int  _pad[0xc];                 // 0x30
    void ctor(int, int);            // 0x9222a0
    void dtor();                    // 0x922130
    int  Lock(int*);                // 0x9221b0
    int  Unlock();                  // 0x922270
};
struct RCObj {
    virtual void v0();      // vtable[0]
    virtual void v1();      // vtable[1] (+4)
    virtual void v2();      // vtable[2] (+8)
    virtual void v3();      // vtable[3] (+0xc)
};
struct Message {
    int   mId;                      // +0x00
    void* mpMessageRC;              // +0x04
    void* mpHandlerRC;              // +0x08
    int   mnPriority;               // +0x0c
    void* mpHandlerFunction;        // +0x10
    void* mpHandlerFunctionContext; // +0x14
};
struct V4 { int a, b, c, d; V4() {} V4(const V4& o) : a(o.a), b(o.b), c(o.c), d(o.d) {} };
struct DequeIter {
    int cur, beg, end, arr;
    DequeIter add(int idx) const;                       // 0x883d90
};
struct C_884ed0 {
    V4 v;
    void* f(void* r, const V4* a, const V4* b, int u);  // 0x884ed0
};
struct C_884f40 {
    V4 v;
    void M(const V4* a, const V4* b, int c);            // 0x884f40
};
struct Deque {
    void*    mpPtrArray;            // +0x00
    int      mnPtrArraySize;        // +0x04
    Message* itBeginCur;            // +0x08
    Message* itBeginBegin;          // +0x0c
    Message* itBeginEnd;            // +0x10
    void**   itBeginArr;            // +0x14
    Message* itEndCur;              // +0x18
    Message* itEndBegin;            // +0x1c
    Message* itEndEnd;              // +0x20
    void**   itEndArr;              // +0x24

    void      init(int);                                                    // 0x883f10
    void      zero() { mpPtrArray = 0; mnPtrArraySize = 0; itBeginCur = 0; itBeginBegin = 0;
                       itBeginEnd = 0; itBeginArr = 0; itEndCur = 0; itEndBegin = 0;
                       itEndEnd = 0; itEndArr = 0; }
    void      clearB();                                                     // 0x996460
    void      FUN_008842e0(Message*);                                       // 0x8842e0
    void      FUN_00884390(Message*);                                       // 0x884390
    void      FUN_008848a0(Message*);                                       // 0x8848a0
    void      FUN_008848e0(Message*);                                       // 0x8848e0
    Message** insert(Message** out, Message* pos, Message* pb, Message* pe, void** pa, Message* val); // 0x885610
    Message** DoInsertValue(Message** out, Message* pos, Message* pb, Message* pe, void** pa, Message* val); // 0x885010
    void      dtor();                                                       // 0x8841f0
};
struct MessageQueue {               // 0x30
    Deque mQueue;                   // +0x00
    int   _pad[2];                  // +0x28
    void InsertMessage(Message* msg);// 0x885710
};
struct Hashtable {
    void*  f00;                     // +0x00
    void** mpBucketArray;           // +0x04
    unsigned int mnBucketCount;     // +0x08
    int    mnElementCount;          // +0x0c
    float  mfMaxLoadFactor;         // +0x10
    float  mfGrowthFactor;          // +0x14
    int    mnNextResize;            // +0x18
    int    _pad1c;                  // +0x1c

    void  find(void* out, int* key);                    // 0x645ed0
    void  eraseEntry(void* out, void* it0, void* it1);  // 0x1068380
    void  allocateBuckets(void** mpBucketArray, int n); // 0x693230
    void  insertNode(void* a, void* b, void* c);        // 0x902290
};
struct HandlerListBase {
    void* next;                                         // +0x00
    void* prev;                                         // +0x04
    void  init(void* a, void* b);                       // 0x883d30
    void  insert(int* key, void* node, void* info);     // 0x884260
};
struct Server {
    void**  vftable;                        // +0x00
    int     _pad04;                         // +0x04
    MessageQueue mQueue;                    // +0x08
    Mutex   mQueueMutex;                    // +0x38
    int     mnQueueProcessedMessageCount;   // +0x68
    int     field_6c;                       // +0x6c
    Hashtable mHandlerInfoMap;              // +0x70
    Mutex   mHandlerInfoMapMutex;           // +0x90
    char    mbThreadSafetyEnabled;          // +0xc0
    char    mbReentrantSafetyEnabled;       // +0xc1
    char    mbQueueProcessingEnabled;       // +0xc2
    char    mbClearQueueEnabled;            // +0xc3
    char    mbRefCountEnabled;              // +0xc4
    char    mbTraceEnabled;                 // +0xc5
    char    _padc6[2];

    Server* ctor_init();                                                    // 00884a20
    bool Shutdown();                                                        // 00884ae0
    void AddHandlerInternal(void* info, unsigned int key);                  // 00884c80
    void MessageSend(uint id, uint arg, int* rc);                           // 008853b0
    void MessagePost(int a, void* rc, int b, void* hf);                     // 00885890
    void MessagePostFunction(int a, void* rc, int b, void* fn, void* ctx);  // 00885930
    void dtor_impl();                                                       // 00884fb0
};
struct Vec14 {
    unsigned char* begin;   // +0x00
    unsigned char* end;     // +0x04
    unsigned char* cap;     // +0x08
    unsigned char* base;    // +0x0c
    unsigned char* alloc;   // +0x10
    void insertAt(unsigned char* pos, unsigned char* val); // 00884d90
};
struct HObj {                       // handler object vtbl: [1]=invoke, [2]/[3]=release
    virtual void v0();
    virtual void v1(uint, uint);
    virtual void v2();
    virtual void v3();
};
struct HRec {                       // collected handler record (5 ints)
    void* obj;                      // +0x00
    int   f1;                       // +0x04 (unused)
    int   flagword;                 // +0x08 (low byte = release flag)
    void* fn;                       // +0x0c
    void* ctx;                      // +0x10
};
// ---- items of slice s00884a20 end

// ---- items of slice s00883730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* e_copyov(void* dst, void* first, void* last);   // 0x11e0744
extern "C" __declspec(dllimport) void* memmove(void* dst, const void* src, unsigned int n);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* out);
static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct Message_s0088_3730 {
    int   mId;                      // +0x00
    void* mpMessageRC;              // +0x04
    void* mpHandlerRC;              // +0x08
    int   mnPriority;               // +0x0c
    void* mpHandlerFunction;        // +0x10
    void* mpHandlerFunctionContext; // +0x14

    Message_s0088_3730() {}
    Message_s0088_3730& operator=(const Message_s0088_3730& o)
    {
        mId = o.mId;
        mpMessageRC = o.mpMessageRC;
        mpHandlerRC = o.mpHandlerRC;
        mnPriority = o.mnPriority;
        mpHandlerFunction = o.mpHandlerFunction;
        mpHandlerFunctionContext = o.mpHandlerFunctionContext;
        return *this;
    }
    Message_s0088_3730(const Message_s0088_3730& o)
    {
        mId = o.mId;
        mpMessageRC = o.mpMessageRC;
        mpHandlerRC = o.mpHandlerRC;
        mnPriority = o.mnPriority;
        mpHandlerFunction = o.mpHandlerFunction;
        mpHandlerFunctionContext = o.mpHandlerFunctionContext;
    }
};
struct HObj_s0088_3730 {                       // handler object vtbl: [1]=invoke, [2]=addref, [3]=release
    virtual void v0();
    virtual void v1(uint id, void* rc);   // +4
    virtual void v2();                    // +8
    virtual void v3();                    // +0xc
};
struct HandlerInfo {
    void*         mpHandler;                 // +0x00
    int           mnPriority;                // +0x04
    unsigned char mbRefCounted;              // +0x08
    unsigned char _pad[3];
    void*         mpHandlerFunction;         // +0x0c
    void*         mpHandlerFunctionContext;  // +0x10

    HandlerInfo& operator=(const HandlerInfo& o)
    {
        mpHandler = o.mpHandler;
        mnPriority = o.mnPriority;
        *(int*)&mbRefCounted = *(const int*)&o.mbRefCounted;
        mpHandlerFunction = o.mpHandlerFunction;
        mpHandlerFunctionContext = o.mpHandlerFunctionContext;
        return *this;
    }
};
struct HandlerListNode {
    HandlerListNode* next;                   // +0x00
    HandlerListNode* prev;                   // +0x04
    HandlerInfo      info;                   // +0x08
};
struct DequeIter_s0088_3730 {
    Message_s0088_3730* cur;                   // +0x00
    Message_s0088_3730* beg;                   // +0x04
    Message_s0088_3730* end;                   // +0x08
    void**   arr;                   // +0x0c

    DequeIter_s0088_3730& operator=(const DequeIter_s0088_3730& o)
    {
        cur = o.cur;
        beg = o.beg;
        end = o.end;
        arr = o.arr;
        return *this;
    }
    DequeIter_s0088_3730(const DequeIter_s0088_3730& o)
    {
        cur = o.cur;
        beg = o.beg;
        end = o.end;
        arr = o.arr;
    }
    DequeIter_s0088_3730& advanceBy(int n);
    DequeIter_s0088_3730& inc()
    {
        cur = (Message_s0088_3730*)((char*)cur + 0x18);
        if (cur == end) {
            ++arr;
            cur = (Message_s0088_3730*)arr[0];
            end = (Message_s0088_3730*)((char*)cur + 0xc0);
            beg = cur;
        }
        return *this;
    }
    DequeIter_s0088_3730  add(int n) const;
};
struct Deque_s0088_3730 {
    void*     mpPtrArray;           // +0x00
    int       mnPtrArraySize;       // +0x04
    DequeIter_s0088_3730 itBegin;              // +0x08
    DequeIter_s0088_3730 itEnd;                // +0x18

    int  count() const
    {
        return (int)(itBegin.end - itBegin.cur) / 0x18
             + ((int)((char*)itEnd.arr - (char*)itBegin.arr) >> 2) * 8
             + (int)(itEnd.cur - itEnd.beg) / 0x18
             - 8;
    }
    void init(int n);                       // 0x883f10
    void grow(uint n, int side);            // 0x883de0
    void pushFrontAux(const Message_s0088_3730* v);    // 0x8842e0
    void pushBackAux(const Message_s0088_3730* v);     // 0x884390
    void pushFront(const Message_s0088_3730* v);       // 0x8848a0
    void pushBack(const Message_s0088_3730* v);        // 0x8848e0
    DequeIter_s0088_3730* insertNode(DequeIter_s0088_3730* out, HandlerListNode* list, const HandlerInfo* info); // 0x884260
};
struct MessageQueue_s0088_3730 {
    Deque_s0088_3730 mQueue;                   // +0x00
    int   _pad[2];                  // +0x28
    bool  GetNextMessage(Message_s0088_3730* out);     // 0x884550
};
struct Hashtable_s0088_3730 {
    void*        f00;               // +0x00
    void**       mpBucketArray;     // +0x04
    unsigned int mnBucketCount;     // +0x08
    int          mnElementCount;    // +0x0c
    float        mfMaxLoadFactor;   // +0x10
    float        mfGrowthFactor;    // +0x14
    int          mnNextResize;      // +0x18
    int          f1c;               // +0x1c

    void find(void* out, int* key); // 0x645ed0
    void erase(int* key);           // 0xa460d0
};
struct Mutex_s0088_3730 {
    char _pad[0x30];                // 0x30 bytes
    int  Lock(int* user);           // 0x9221b0
    int  Unlock();                  // 0x922270
};
struct StopwatchHolder {            // EA::LimitStopwatch (0x20 bytes)
    long long    mnStartTime;          // +0x00
    long long    mnTotalElapsedTime;   // +0x08
    unsigned int mnUnits;              // +0x10
    float        mfCoeff;              // +0x14
    long long    mnEndTime;            // +0x18

    StopwatchHolder(int units, bool b);                    // 0x93a560
    void SetTimeLimit(unsigned int timeLimit, bool b);     // 0x93a480
};
struct Server_s0088_3730 {
    void**       vftable;                   // +0x00
    int          _pad04;                    // +0x04
    MessageQueue_s0088_3730 mQueue;                    // +0x08
    Mutex_s0088_3730        mQueueMutex;               // +0x38
    long long    mnQueueProcessedMessageCount; // +0x68
    Hashtable_s0088_3730    mHandlerInfoMap;           // +0x70
    Mutex_s0088_3730        mHandlerInfoMapMutex;      // +0x90
    unsigned char mbThreadSafetyEnabled;    // +0xc0
    unsigned char mbReentrantSafetyEnabled; // +0xc1
    unsigned char mbQueueProcessingEnabled; // +0xc2
    unsigned char mbClearQueueEnabled;      // +0xc3
    unsigned char mbRefCountEnabled;        // +0xc4
    unsigned char mbTraceEnabled;           // +0xc5

    int  GetOption(int option) const;                       // 0x883880
    void SetOption(int option, int value);                  // 0x883910
    void AddHandlerObj(void* handler, uint id);             // 0x8839a0
    void AddHandlerRC(void* handler, uint id);              // 0x8839e0
    void AddHandlerFn(void* fn, void* ctx, uint id, char refcounted, int priority); // 0x883a30
    int  LockMutexes(bool lock);                            // 0x883ab0
    int  ProcessQueueTimeout(uint threshold, uint maxCount, uint timeout); // 0x884100
    bool RemoveHandlerInternal(void* handler, uint id, int priority);      // 0x8845d0
    int  ProcessQueueRun();                                 // 0x884700
};
// ---- items of slice s00883730 end

// ---- items of slice s010678e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
typedef unsigned int  u32;
void  SP_DeleteArray(void* p);             // 0x00f47380 operator delete[]
struct DeqNode {
    void*    m00;       // +0x00
    void*    m04;       // +0x04
    DeqNode* m08;       // +0x08
};
struct Deque_s0106_78e0 {
    void* m00; void* m04; void* m08; u32 m0c;
    int* clear(int* out, DeqNode* self, DeqNode* root); // 0x01068380
};
// ---- items of slice s010678e0 end

// @ 0x00883880
int EA::Messaging::Server::GetOption(int option) const
{
    switch (option) {
    case 1: return this->mbThreadSafetyEnabled != false;
    case 2: return this->mbReentrantSafetyEnabled != false;
    case 3: return this->mbQueueProcessingEnabled != false;
    case 4: return this->mbClearQueueEnabled != false;
    case 5: return this->mbRefCountEnabled != false;
    case 6: return this->mbTraceEnabled != false;
    default: return 0;
    }
}

// @ 0x00883910
void EA::Messaging::Server::SetOption(int option, int value)
{
    switch (option) {
    case 1: this->mbThreadSafetyEnabled = value != 0; return;
    case 2: this->mbReentrantSafetyEnabled = value != 0; return;
    case 3: this->mbQueueProcessingEnabled = value != 0; return;
    case 4: this->mbClearQueueEnabled = value != 0; return;
    case 5: this->mbRefCountEnabled = value != 0; return;
    case 6: this->mbTraceEnabled = value != 0; return;
    }
}

// @ 0x008839a0
void Server_s0088_3730::AddHandlerObj(void* handler, uint id)
{
    if (handler != 0) {
        HandlerInfo info;
        info.mpHandler = handler;
        info.mnPriority = 0;
        info.mbRefCounted = 0;
        info.mpHandlerFunction = 0;
        info.mpHandlerFunctionContext = 0;
        typedef void (__thiscall* Fn)(Server_s0088_3730*, HandlerInfo*, uint);
        ((Fn)this->vftable[0x44 / 4])(this, &info, id);
    }
}

// @ 0x008839e0
void Server_s0088_3730::AddHandlerRC(void* handler, uint id)
{
    if (handler != 0) {
        HandlerInfo info;
        info.mpHandler = handler;
        info.mnPriority = 0;
        info.mbRefCounted = 1;
        info.mpHandlerFunction = 0;
        info.mpHandlerFunctionContext = 0;
        if (this->mbRefCountEnabled != 0)
            ((RCObj*)handler)->v2();
        typedef void (__thiscall* Fn)(Server_s0088_3730*, HandlerInfo*, uint);
        ((Fn)this->vftable[0x44 / 4])(this, &info, id);
    }
}

// @ 0x00883a30
void Server_s0088_3730::AddHandlerFn(void* fn, void* ctx, uint id, char refcounted, int priority)
{
    if (fn != 0) {
        HandlerInfo info;
        info.mnPriority = priority;
        info.mpHandler = 0;
        info.mpHandlerFunction = fn;
        info.mpHandlerFunctionContext = ctx;
        info.mbRefCounted = refcounted;
        if (this->mbRefCountEnabled != 0 && refcounted != 0)
            ((void(*)(int, int, void*))fn)(1, 0, info.mpHandlerFunctionContext);
        typedef void (__thiscall* Fn)(Server_s0088_3730*, HandlerInfo*, uint);
        ((Fn)this->vftable[0x44 / 4])(this, &info, id);
    }
}

// @ 0x00883ab0
int Server_s0088_3730::LockMutexes(bool lock)
{
    if (this->mbThreadSafetyEnabled != 0) {
        if (lock != 0) {
            this->mHandlerInfoMapMutex.Lock(&g_1427918);
            return this->mQueueMutex.Lock(&g_1427918);
        }
        this->mHandlerInfoMapMutex.Unlock();
        return this->mQueueMutex.Unlock();
    }
    return 0;
}

// @ 0x00883b00
DequeIter_s0088_3730& DequeIter_s0088_3730::advanceBy(int n)
{
    unsigned int u = (unsigned int)((int)(this->cur - this->beg) + n);
    if (u < 8) {
        this->cur = this->cur + n;
        return *this;
    }
    int d = (int)(u + 0x1000000);
    int idx = ((d + ((d >> 31) & 7)) >> 3) - 0x200000;
    this->arr = this->arr + idx;
    Message_s0088_3730* base = (Message_s0088_3730*)this->arr[0];
    this->beg = base;
    this->end = (Message_s0088_3730*)((char*)base + 0xc0);
    this->cur = base + (int)(u - (unsigned)(idx * 8));
    return *this;
}

// @ 0x00883b80
DequeIter_s0088_3730* DequeCopyForward(DequeIter_s0088_3730* out, DequeIter_s0088_3730 first, DequeIter_s0088_3730 last, DequeIter_s0088_3730 result)
{
    while (first.cur != last.cur) {
        *result.cur = *first.cur;
        result.inc();
        first.inc();
    }
    *out = result;
    return out;
}

// @ 0x00883c60
void DequeCopyBackward(DequeIter_s0088_3730* out, DequeIter_s0088_3730 first, DequeIter_s0088_3730 last, DequeIter_s0088_3730 result)
{
    while (first.cur != last.cur) {
        if (first.cur == first.beg) {
            --first.arr;
            first.beg = (Message_s0088_3730*)first.arr[0];
            first.end = first.beg + 8;
            first.cur = first.end;
        }
        --first.cur;
        if (result.cur == result.beg) {
            --result.arr;
            result.beg = (Message_s0088_3730*)result.arr[0];
            result.end = result.beg + 8;
            result.cur = result.end;
        }
        --result.cur;
        *result.cur = *first.cur;
    }
    *out = result;
}

// @ 0x00883d30
void __stdcall HandlerList_Init(HandlerListNode* list, const HandlerInfo* info)
{
    HandlerListNode* node = (HandlerListNode*)e_opnew(0x1c, "EASTL", 0, 0, kAllocFile, 0xd1);
    if (&node->info != 0)
        node->info = *info;
    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
}

// @ 0x00883d90
DequeIter_s0088_3730 DequeIter_s0088_3730::add(int n) const
{
    DequeIter_s0088_3730 tmp = *this;
    return tmp.advanceBy(n);
}

// @ 0x00883de0
void Deque_s0088_3730::grow(uint n, int side)
{
    int oldCount = (int)((char*)this->itEnd.arr - (char*)this->itBegin.arr) / 4 + 1;
    uint newCount = (uint)oldCount + n;
    uint cap = (uint)this->mnPtrArraySize;
    void** first = this->itBegin.arr;
    void** last = this->itEnd.arr + 1;
    void** dest;

    if (newCount * 2 < cap) {
        int extra = (side == 0) ? (int)n : 0;
        dest = (void**)((char*)this->mpPtrArray + (((cap - newCount) >> 1) + extra) * 4);
        if (dest < first)
            e_copyov(dest, first, last);
        else
            memmove(dest + (oldCount - (int)((char*)last - (char*)first) / 4),
                    first, (unsigned int)oldCount * 4);
    } else {
        uint maxv = cap > n ? cap : n;
        uint newCap = maxv + cap + 2;
        void** arr = (void**)e_opnew((int)(newCap * 4), "EASTL", 0, 0, kAllocFile, 0xd1);
        int extra = (side == 0) ? (int)n : 0;
        dest = arr + ((int)((char*)first - (char*)this->mpPtrArray) >> 2) + extra;
        if (this->mpPtrArray != 0)
            e_copyov(dest, first, last);
        if (this->mpPtrArray != 0)
            e_opdel(this->mpPtrArray);
        this->mpPtrArray = arr;
        this->mnPtrArraySize = (int)newCap;
    }

    this->itBegin.arr = dest;
    Message_s0088_3730* bbase = (Message_s0088_3730*)dest[0];
    this->itBegin.beg = bbase;
    this->itBegin.end = (Message_s0088_3730*)((char*)bbase + 0xc0);
    this->itEnd.arr = dest + (oldCount - 1);
    Message_s0088_3730* ebase = (Message_s0088_3730*)this->itEnd.arr[0];
    this->itEnd.beg = ebase;
    this->itEnd.end = (Message_s0088_3730*)((char*)ebase + 0xc0);
}

// @ 0x00883f10
void Deque_s0088_3730::init(int n)
{
    int k = (n >> 3) + 1;
    int c = (n >> 3) + 3;
    unsigned int cap = (unsigned int)((c > 8) ? c : 8);
    this->mnPtrArraySize = (int)cap;

    void** arr = (void**)e_opnew((int)(cap * 4), "EASTL", 0, 0, kAllocFile, 0xd1);
    void** p = arr + ((cap - (unsigned int)k) >> 1);
    void** pe = p + k;
    for (void** q = p; q < pe; ++q)
        *q = e_opnew(0xc0, "EASTL", 0, 0, kAllocFile, 0xd1);

    this->mpPtrArray = arr;
    this->itBegin.arr = p;
    Message_s0088_3730* bbase = (Message_s0088_3730*)p[0];
    this->itBegin.beg = bbase;
    this->itBegin.end = (Message_s0088_3730*)((char*)bbase + 0xc0);
    this->itBegin.cur = this->itBegin.beg;
    this->itEnd.arr = pe - 1;
    Message_s0088_3730* ebase = (Message_s0088_3730*)this->itEnd.arr[0];
    this->itEnd.beg = ebase;
    this->itEnd.end = (Message_s0088_3730*)((char*)ebase + 0xc0);
    this->itEnd.cur = (Message_s0088_3730*)((char*)ebase + (n & 7) * 0x18);
}

// @ 0x00884100
int Server_s0088_3730::ProcessQueueTimeout(uint threshold, uint maxCount, uint timeout)
{
    int total = 0;
    unsigned int count = 0;
    if (this->mbQueueProcessingEnabled != 0) {
        StopwatchHolder sw(4, false);
        sw.SetTimeLimit(timeout, true);
        if (maxCount != 0) {
            do {
                if (this->mQueue.mQueue.count() == 0)
                    return total;
                typedef int (__thiscall* Fn)(Server_s0088_3730*);
                total += ((Fn)this->vftable[0x38 / 4])(this);
                if (threshold < count) {
                    long long now;
                    QueryPerformanceCounter(&now);
                    long long remain = sw.mnEndTime - now;
                    if (remain < 0)
                        return total;
                }
                ++count;
            } while (count < maxCount);
        }
    }
    return total;
}

// @ 0x00884260
DequeIter_s0088_3730* Deque_s0088_3730::insertNode(DequeIter_s0088_3730* out, HandlerListNode* list, const HandlerInfo* info)
{
    HandlerListNode* node = (HandlerListNode*)e_opnew(0x1c, "EASTL", 0, 0, kAllocFile, 0xd1);
    if (&node->info != 0)
        node->info = *info;
    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
    out->cur = (Message_s0088_3730*)node;
    return out;
}

// @ 0x008842e0
void Deque_s0088_3730::pushFrontAux(const Message_s0088_3730* value)
{
    Message_s0088_3730 v = *value;
    if (this->itBegin.arr == (void**)this->mpPtrArray)
        this->grow(1, 0);
    Message_s0088_3730* node = (Message_s0088_3730*)e_opnew(0xc0, "EASTL", 0, 0, kAllocFile, 0xd1);
    this->itBegin.arr[-1] = node;
    --this->itBegin.arr;
    Message_s0088_3730* base = (Message_s0088_3730*)this->itBegin.arr[0];
    this->itBegin.beg = base;
    this->itBegin.end = (Message_s0088_3730*)((char*)base + 0xc0);
    this->itBegin.cur = (Message_s0088_3730*)((char*)base + 0xc0 - 0x18);
    if (this->itBegin.cur != 0)
        *this->itBegin.cur = v;
}

// @ 0x00884390
void Deque_s0088_3730::pushBackAux(const Message_s0088_3730* value)
{
    Message_s0088_3730 v = *value;
    if (((int)((char*)this->itEnd.arr - (char*)this->mpPtrArray) >> 2) + 1 >= this->mnPtrArraySize)
        this->grow(1, 1);
    Message_s0088_3730* node = (Message_s0088_3730*)e_opnew(0xc0, "EASTL", 0, 0, kAllocFile, 0xd1);
    this->itEnd.arr[1] = node;
    Message_s0088_3730* cur = this->itEnd.cur;
    if (cur != 0)
        *cur = v;
    ++this->itEnd.arr;
    Message_s0088_3730* base = (Message_s0088_3730*)this->itEnd.arr[0];
    this->itEnd.beg = base;
    this->itEnd.end = (Message_s0088_3730*)((char*)base + 0xc0);
    this->itEnd.cur = this->itEnd.beg;
}

// @ 0x00884550
bool MessageQueue_s0088_3730::GetNextMessage(Message_s0088_3730* out)
{
    Message_s0088_3730* p = this->mQueue.itBegin.cur;
    if (p == this->mQueue.itEnd.cur)
        return false;
    *out = *p;
    Message_s0088_3730* next = p + 1;
    if (next != this->mQueue.itBegin.end) {
        this->mQueue.itBegin.cur = next;
        return true;
    }
    if (this->mQueue.itBegin.beg != 0)
        e_opdel(this->mQueue.itBegin.beg);
    ++this->mQueue.itBegin.arr;
    Message_s0088_3730* nb = (Message_s0088_3730*)this->mQueue.itBegin.arr[0];
    this->mQueue.itBegin.beg = nb;
    this->mQueue.itBegin.end = nb + 8;
    this->mQueue.itBegin.cur = nb;
    return true;
}

// @ 0x008845d0
bool Server_s0088_3730::RemoveHandlerInternal(void* handler, uint id, int priority)
{
    unsigned char found = 0;
    if (this->mbThreadSafetyEnabled != 0)
        this->mHandlerInfoMapMutex.Lock(&g_1427918);

    int it[2];
    this->mHandlerInfoMap.find(it, (int*)&id);
    void** ba = this->mHandlerInfoMap.mpBucketArray;
    if ((void*)it[0] != (void*)ba[this->mHandlerInfoMap.mnBucketCount]) {
        HandlerListNode* list = (HandlerListNode*)*(void**)((char*)it[0] + 4);
        for (HandlerListNode* p = list->next; p != list; p = p->next) {
            HandlerInfo* h = &p->info;
            if ((h->mpHandler == handler || h->mpHandlerFunction == handler) &&
                (priority == -9999 || h->mnPriority == priority)) {
                if (this->mbRefCountEnabled != 0 && h->mbRefCounted != 0) {
                    if (h->mpHandler != 0)
                        (*(void(**)(void))(*(unsigned int*)((char*)h->mpHandler + 0xc)))();
                    else
                        ((void(*)(int, int, void*))h->mpHandlerFunction)(
                            2, 0, h->mpHandlerFunctionContext);
                }
                found = 1;
                if (p != list) {
                    p->next->prev = p->prev;
                    p->prev->next = p->next;
                    e_opdel(p);
                    if (list->next == list) {
                        HandlerListNode* q = list->next;
                        while (q != list) {
                            HandlerListNode* nx = q->next;
                            e_opdel(q);
                            q = nx;
                        }
                        e_opdel(list);
                        this->mHandlerInfoMap.erase((int*)&id);
                    }
                }
                break;
            }
        }
    }

    if (this->mbThreadSafetyEnabled != 0)
        this->mHandlerInfoMapMutex.Unlock();
    return found != 0;
}

// @ 0x00884700
int Server_s0088_3730::ProcessQueueRun(void)
{
    int processed = 0;
    if (this->mbThreadSafetyEnabled != 0)
        this->mQueueMutex.Lock(&g_1427918);

    unsigned int size = (unsigned int)this->mQueue.mQueue.count();
    unsigned long long target =
        (unsigned long long)size + (unsigned long long)this->mnQueueProcessedMessageCount;

    if (this->mbThreadSafetyEnabled != 0)
        this->mQueueMutex.Unlock();

    for (;;) {
        if (this->mbThreadSafetyEnabled != 0)
            this->mQueueMutex.Lock(&g_1427918);
        Message_s0088_3730 msg;
        bool got = this->mQueue.GetNextMessage(&msg);
        if (got) {
            ++this->mnQueueProcessedMessageCount;
            ++processed;
        }
        if (this->mbThreadSafetyEnabled != 0)
            this->mQueueMutex.Unlock();
        if (!got)
            return processed;

        if (msg.mpHandlerRC != 0) {
            ((HObj_s0088_3730*)msg.mpHandlerRC)->v1((uint)msg.mId, msg.mpMessageRC);
            if (this->mbRefCountEnabled != 0)
                ((HObj_s0088_3730*)msg.mpHandlerRC)->v3();
        } else if (msg.mpHandlerFunction != 0) {
            ((void(*)(int, void*, void*))msg.mpHandlerFunction)(
                msg.mId, msg.mpMessageRC, msg.mpHandlerFunctionContext);
            if (this->mbRefCountEnabled != 0)
                ((void(*)(int, int, void*))msg.mpHandlerFunction)(
                    2, 0, msg.mpHandlerFunctionContext);
        } else {
            typedef void (__thiscall* Fn)(Server_s0088_3730*, uint, void*, int);
            ((Fn)this->vftable[0x14 / 4])(this, (uint)msg.mId, msg.mpMessageRC, 0);
        }

        if (msg.mpMessageRC != 0 && this->mbRefCountEnabled != 0)
            ((RCObj*)msg.mpMessageRC)->v2();

        if (this->mbClearQueueEnabled != 0)
            continue;
        if ((unsigned long long)this->mnQueueProcessedMessageCount >= target)
            return processed;
    }
}

// @ 0x008848a0
void Deque_s0088_3730::pushFront(const Message_s0088_3730* value)
{
    Message_s0088_3730* cur = this->itBegin.cur;
    if (cur != this->itBegin.beg) {
        Message_s0088_3730* p = cur - 1;
        this->itBegin.cur = p;
        if (p != 0)
            *p = *value;
        return;
    }
    this->pushFrontAux(value);
}

// @ 0x008848e0
void Deque_s0088_3730::pushBack(const Message_s0088_3730* value)
{
    Message_s0088_3730* cur = this->itEnd.cur;
    Message_s0088_3730* next = cur + 1;
    if (next != this->itEnd.end) {
        this->itEnd.cur = next;
        if (cur != 0)
            *cur = *value;
        return;
    }
    this->pushBackAux(value);
}

// @ 0x00884a20
Server* Server::ctor_init()
{
    this->vftable = (void**)&g_1427920;
    this->mQueue.mQueue.zero();
    this->mQueue.mQueue.init(0);
    this->mQueueMutex.ctor(0, 1);
    this->mnQueueProcessedMessageCount = 0;
    this->field_6c = 0;
    this->mHandlerInfoMap.mfMaxLoadFactor = g_1485720;
    this->mHandlerInfoMap.mfGrowthFactor = g_1470f1c;
    this->mHandlerInfoMap.mnBucketCount = 1;
    this->mHandlerInfoMap.mpBucketArray = (void**)&g_154df28;
    this->mHandlerInfoMap.mnElementCount = 0;
    this->mHandlerInfoMap.mnNextResize = 0;
    this->mHandlerInfoMapMutex.ctor(0, 1);
    this->mbThreadSafetyEnabled = 1;
    this->mbReentrantSafetyEnabled = 1;
    this->mbQueueProcessingEnabled = 1;
    this->mbClearQueueEnabled = 1;
    this->mbRefCountEnabled = 1;
    this->mbTraceEnabled = 1;
    return this;
}

// @ 0x00884ae0
bool Server::Shutdown()
{
    int* g = &g_1427918;
    if (this->mbThreadSafetyEnabled != 0)
        this->mHandlerInfoMapMutex.Lock(g);

    while (this->mHandlerInfoMap.mnElementCount != 0) {
        void** buckets = this->mHandlerInfoMap.mpBucketArray;
        int bc = this->mHandlerInfoMap.mnBucketCount;
        void* node = buckets[0];
        if (node == 0) {
            void** b = buckets + 1;
            node = *b;
            while (node == 0) {
                ++b;
                node = *b;
            }
            node = *b;
        }
        // (node->mValue).second = the HandlerInfo list for this key
        unsigned char* list = (unsigned char*)((void**)((char*)node + 4))[0];
        (void)bc;
        int itbuf[4];
        this->mHandlerInfoMap.eraseEntry(itbuf, node, (void*)buckets);

        if (list != 0) {
            unsigned char* head = list;
            unsigned char* p = *(unsigned char**)head;
            while (p != head) {
                unsigned char* n0 = *(unsigned char**)(p + 0xc);
                unsigned char* n1 = *(unsigned char**)(p + 0x18);
                unsigned char* n2 = *(unsigned char**)(p + 8);
                unsigned char* n3 = *(unsigned char**)(p + 0x10);
                unsigned char* n4 = *(unsigned char**)(p + 0x14);
                void** pp = (void**)*(unsigned int*)(p + 4);
                *pp = (void*)*(unsigned int*)p;
                void** pq = (void**)*(unsigned int*)p;
                pq[1] = (void*)*(unsigned int*)(p + 4);
                e_opdel(p);
                if (this->mbRefCountEnabled != 0 && (char)(unsigned)n3 != 0) {
                    if (n2 == 0)
                        ((void(*)(int, int, void*))n4)(2, 0, (void*)n1);
                    else
                        (*(void(**)(void))(*(unsigned int*)(n2 + 0xc)))();
                }
                (void)n0;
                p = *(unsigned char**)head;
            }
            unsigned char* q = *(unsigned char**)head;
            while (q != head) {
                unsigned char* nx = *(unsigned char**)q;
                e_opdel(q);
                q = nx;
            }
            e_opdel(head);
        }
    }

    if (this->mbThreadSafetyEnabled != 0) {
        this->mHandlerInfoMapMutex.Unlock();
        this->mQueueMutex.Lock(g);
    }

    Message* e = this->mQueue.mQueue.itEndCur;
    Message* b = this->mQueue.mQueue.itBeginCur;
    Message* en = this->mQueue.mQueue.itBeginEnd;
    void** arr = this->mQueue.mQueue.itBeginArr;
    if (b != e) {
        for (;;) {
            if (b->mpMessageRC != 0) {
                (*(void(**)(void))(*(unsigned int*)b->mpMessageRC + 8))();
                b->mpMessageRC = 0;
            }
            b = b + 1;
            if (b == en) {
                b = (Message*)arr[1];
                ++arr;
                en = b + 8;
            }
            if (b == e)
                break;
        }
    }
    this->mQueue.mQueue.clearB();

    if (this->mbThreadSafetyEnabled != 0)
        this->mQueueMutex.Unlock();
    return 1;
}

// @ 0x00884c80
void Server::AddHandlerInternal(void* info, unsigned int key)
{
    if (this->mbThreadSafetyEnabled != 0)
        this->mHandlerInfoMapMutex.Lock(&g_1427918);

    int itbuf[4];
    this->mHandlerInfoMap.find(itbuf, (int*)&key);
    void** ba = this->mHandlerInfoMap.mpBucketArray;
    unsigned int bc = this->mHandlerInfoMap.mnBucketCount;
    if ((void*)itbuf[0] == (void*)ba[bc]) {
        unsigned char* list = (unsigned char*)e_opnew(0xc, "Messaging/HIList", 0, 0, 0, 0);
        if (list != 0) {
            *(void**)list = list;
            *(void**)(list + 4) = list;
        } else {
            list = 0;
        }
        ((HandlerListBase*)list)->init(list, info);
        void* listLocal = list;
        unsigned int keyLocal = key;
        this->mHandlerInfoMap.insertNode(&listLocal, &keyLocal, (void*)(key & 0xffffff00));
    } else {
        HandlerListBase* list = (HandlerListBase*)*(void**)((char*)itbuf[0] + 4);
        unsigned char* p = (unsigned char*)*(void**)list;
        while (p != (unsigned char*)list) {
            if (*(int*)((char*)info + 4) >= *(int*)(p + 0xc)) {
                list->insert((int*)&key, p, info);
                goto done;
            }
            p = *(unsigned char**)p;
        }
        list->insert((int*)&key, p, info);
    }
done:
    if (this->mbThreadSafetyEnabled != 0)
        this->mHandlerInfoMapMutex.Unlock();
}

// @ 0x00884d90
void Vec14::insertAt(unsigned char* pos, unsigned char* val)
{
    unsigned char* e = this->end;
    if (e != this->cap) {
        if (pos <= val && val < e)
            val += 0x14;
        if (e != 0) {
            *(void**)e = *(void**)(e - 0x14);
            *(void**)(e + 4) = *(void**)(e - 0x10);
            *(void**)(e + 8) = *(void**)(e - 0x0c);
            *(void**)(e + 0x0c) = *(void**)(e - 8);
            *(void**)(e + 0x10) = *(void**)(e - 4);
        }
        e_c50ad0(pos, this->end - 0x14, this->end);
        *(void**)pos = *(void**)val;
        *(void**)(pos + 4) = *(void**)(val + 4);
        *(void**)(pos + 8) = *(void**)(val + 8);
        *(void**)(pos + 0x0c) = *(void**)(val + 0x0c);
        *(void**)(pos + 0x10) = *(void**)(val + 0x10);
        this->end += 0x14;
        return;
    }
    long n = (long)(e - this->begin) / 0x14;
    int count;
    unsigned char* fresh;
    if (n == 0) {
        count = 1;
    } else {
        count = (int)(n * 2);
        if (count == 0) {
            fresh = 0;
            goto alloc_done;
        }
    }
    fresh = (unsigned char*)e_opnew(count * 0x14, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
alloc_done:
    {
        unsigned char* mid = (unsigned char*)e_951bb0(this->begin, pos, fresh);
        if (mid != 0) {
            *(void**)mid = *(void**)val;
            *(void**)(mid + 4) = *(void**)(val + 4);
            *(void**)(mid + 8) = *(void**)(val + 8);
            *(void**)(mid + 0x0c) = *(void**)(val + 0x0c);
            *(void**)(mid + 0x10) = *(void**)(val + 0x10);
        }
        unsigned char* nend = (unsigned char*)e_951bb0(pos, this->end, mid + 0x14);
        if (this->begin != 0 && this->begin != this->alloc)
            e_opdel(this->begin);
        this->begin = fresh;
        this->end = nend;
        this->cap = fresh + count * 0x14;
    }
}

// @ 0x00884fb0
void Server::dtor_impl()
{
    this->vftable = (void**)&g_1427920;
    this->Shutdown();
    this->mHandlerInfoMapMutex.dtor();
    Hashtable* ht = &this->mHandlerInfoMap;
    ht->allocateBuckets(ht->mpBucketArray, ht->mnBucketCount);
    ht->mnElementCount = 0;
    if (ht->mnBucketCount > 1)
        e_opdel(ht->mpBucketArray);
    this->mQueueMutex.dtor();
    this->mQueue.mQueue.dtor();
}

// @ 0x00885010
Message** Deque::DoInsertValue(Message** out, Message* pos, Message* pb, Message* pe, void** pa, Message* val)
{
    int* vi = (int*)val;
    int v0 = vi[0], v1 = vi[1], v2 = vi[2], v3 = vi[3], v4 = vi[4], v5 = vi[5];
    (void)pe;

    int off = (int)((char*)this->itBeginEnd - (char*)this->itBeginCur) / 0x18
            + (((int)pa - (int)this->itBeginArr) >> 2) * 8
            + ((int)pos - (int)pb) / 0x18
            + (-8);
    int size = (int)((char*)this->itEndCur - (char*)this->itEndBegin) / 0x18 + (-8)
             + (((int)this->itEndArr - (int)this->itBeginArr) >> 2) * 8;

    int p3i = 0, p4i = 0, p5i = 0, p6i = 0;

    if (off < (int)((unsigned)(size + (int)((char*)this->itBeginEnd - (char*)this->itBeginCur) / 0x18) >> 1)) {
        Message* cur = this->itBeginCur;
        if (cur == this->itBeginBegin) {
            this->FUN_008842e0(cur);
        } else {
            int* pv = (int*)cur;
            int* d = pv - 6;
            this->itBeginCur = (Message*)d;
            if (d != 0) {
                d[0] = pv[0]; d[1] = pv[1]; d[2] = pv[2];
                d[3] = pv[3]; d[4] = pv[4]; d[5] = pv[5];
            }
        }
        DequeIter buf = ((DequeIter*)((char*)this + 8))->add(off);
        p3i = buf.cur; p4i = buf.beg; p5i = buf.end; p6i = buf.arr;

        int l58 = p3i + 0x18, l54 = p4i, l50 = p5i, l4c = p6i;
        if (l58 == p5i) {
            l4c = p6i + 4;
            l58 = *(int*)l4c;
            l50 = l58 + 0xC0;
            l54 = l58;
        }
        int l30 = (int)this->itBeginEnd;
        int* l2c = (int*)this->itBeginArr;
        int l38 = (int)this->itBeginCur + 0x18;
        int l34 = (int)this->itBeginBegin;
        if (l38 == l30) {
            l38 = l2c[1];
            l2c = l2c + 1;
            l30 = l38 + 0xC0;
            l34 = l38;
        }
        int l48 = l38 + 0x18, l44 = l34, l40 = l30;
        int* l3c = l2c;
        if (l48 == l30) {
            l3c = l2c + 1;
            l48 = *l3c;
            l40 = l48 + 0xC0;
            l44 = l48;
        }
        V4 v58; v58.a = l58; v58.b = l54; v58.c = l50; v58.d = l4c;
        V4 v48; v48.a = l48; v48.b = l44; v48.c = l40; v48.d = (int)l3c;
        V4 v38; v38.a = l38; v38.b = l34; v38.c = l30; v38.d = (int)l2c;
        int ret28[4];
        ((C_884ed0*)&v38)->f(ret28, &v48, &v58, size);
    } else {
        int iVar6 = (int)this->itEndCur;
        if (iVar6 == (int)this->itEndBegin)
            iVar6 = ((int*)this->itEndArr)[-1] + 0xC0;
        int* curEnd = (int*)this->itEndCur;
        if (curEnd + 6 == (int*)this->itEndEnd) {
            this->FUN_00884390((Message*)(iVar6 - 0x18));
        } else {
            this->itEndCur = (Message*)(curEnd + 6);
            if (curEnd != 0) {
                int* sv = (int*)(iVar6 - 0x18);
                curEnd[0] = sv[0]; curEnd[1] = sv[1]; curEnd[2] = sv[2];
                curEnd[3] = sv[3]; curEnd[4] = sv[4]; curEnd[5] = sv[5];
            }
        }
        DequeIter buf = ((DequeIter*)((char*)this + 8))->add(off);
        p3i = buf.cur; p4i = buf.beg; p5i = buf.end; p6i = buf.arr;

        int l44 = (int)this->itEndBegin;
        int l48 = (int)this->itEndCur;
        int* l3c = (int*)this->itEndArr;
        int l40 = (int)this->itEndEnd;
        if (l48 == l44) {
            l44 = l3c[-1];
            l3c = l3c - 1;
            l48 = l44 + 0xC0;
            l40 = l48;
        }
        l48 = l48 - 0x18;
        int l38 = l48, l34 = l44, l30 = l40;
        int* l2c = l3c;
        if (l48 == l44) {
            l2c = l3c - 1;
            l34 = *l2c;
            l38 = l34 + 0xC0;
            l30 = l38;
        }
        l38 = l38 - 0x18;
        V4 p3v; p3v.a = p3i; p3v.b = p4i; p3v.c = p5i; p3v.d = p6i;
        V4 v38; v38.a = l38; v38.b = l34; v38.c = l30; v38.d = (int)l2c;
        V4 v48; v48.a = l48; v48.b = l44; v48.c = l40; v48.d = (int)l3c;
        ((C_884f40*)&v48)->M(&p3v, &v38, size);
    }

    int* wp = (int*)p3i;
    wp[0] = v0; wp[1] = v1; wp[2] = v2; wp[3] = v3; wp[4] = v4; wp[5] = v5;
    out[0] = (Message*)p3i;
    out[1] = (Message*)p4i;
    out[2] = (Message*)p5i;
    out[3] = (Message*)p6i;
    return out;
}

// @ 0x008853b0
void Server::MessageSend(uint id, uint arg, int* rc)
{
    if (rc != 0) {
        ((HObj*)rc)->v1(id, arg);
        return;
    }

    HRec array[128];                                    // 0xa00 bytes
    Vec14 handlers;
    handlers.begin = (unsigned char*)&array;
    handlers.end   = (unsigned char*)&array;
    handlers.cap   = (unsigned char*)&array[128];
    handlers.base  = (unsigned char*)&array;            // +0x0c (unused)
    handlers.alloc = (unsigned char*)&array;            // +0x10 = stack base

    if (this->mbThreadSafetyEnabled != 0)
        this->mHandlerInfoMapMutex.Lock(&g_1427918);

    unsigned int uid = 0xffffffff;
    for (;;) {
        unsigned int bc = this->mHandlerInfoMap.mnBucketCount;
        void** ba = this->mHandlerInfoMap.mpBucketArray;
        void* endNode = ba[bc];
        unsigned int idx = uid % bc;
        void* found = 0;
        for (void* n = ba[idx]; n != 0; n = *(void**)((char*)n + 8)) {
            if (uid == *(unsigned int*)n) { found = n; break; }
        }

        if (found != 0 && found != endNode) {
            void* list = *(void**)((char*)found + 4);
            for (char* p = *(char**)list; p != list; p = *(char**)p) {
                char* h = p + 8;
                void* obj = *(void**)(h + 0);
                int   f1  = *(int*)(h + 4);
                int   flag = *(int*)(h + 8);
                void* fn  = *(void**)(h + 0xc);
                void* ctx = *(void**)(h + 0x10);

                if (this->mbReentrantSafetyEnabled == 0 && this->mbThreadSafetyEnabled == 0) {
                    if (obj == 0)
                        ((void(*)(uint, uint, void*))fn)(id, arg, ctx);
                    else
                        ((HObj*)obj)->v1(id, arg);
                } else {
                    if (handlers.end != handlers.cap) {
                        HRec* r = (HRec*)handlers.end;
                        handlers.end += 0x14;
                        if (r != 0) {
                            r->obj = obj; r->f1 = f1; r->flagword = flag;
                            r->fn = fn; r->ctx = ctx;
                        }
                    } else {
                        handlers.insertAt(handlers.end, (unsigned char*)h);
                    }
                    if (this->mbRefCountEnabled != 0 && (char)flag != 0) {
                        if (obj == 0)
                            ((void(*)(int, int, void*))fn)(1, 0, ctx);
                        else
                            ((HObj*)obj)->v2();
                    }
                }
            }
        }

        int done = (uid == id);
        uid = id;
        if (done) {
            if (this->mbThreadSafetyEnabled != 0)
                this->mHandlerInfoMapMutex.Unlock();

            for (HRec* r = (HRec*)handlers.begin; r != (HRec*)handlers.end; ++r) {
                if (r->obj == 0)
                    ((void(*)(uint, uint, void*))r->fn)(id, arg, r->ctx);
                else
                    ((HObj*)r->obj)->v1(id, arg);

                if (this->mbRefCountEnabled != 0 && (char)r->flagword != 0) {
                    if (r->obj == 0)
                        ((void(*)(int, int, void*))r->fn)(2, 0, r->ctx);
                    else
                        ((HObj*)r->obj)->v3();
                }
            }
            if (handlers.begin != 0 && handlers.begin != (unsigned char*)&array)
                e_opdel(handlers.begin);
            return;
        }
    }
}

// @ 0x00885610
Message** Deque::insert(Message** out, Message* pos, Message* pb, Message* pe, void** pa, Message* val)
{
    Message* e = this->itEndCur;
    if (pos == e) {
        if (e + 1 == this->itEndEnd) {
            this->FUN_00884390(val);
        } else {
            this->itEndCur = e + 1;
            if (e != 0)
                *e = *val;
        }
        *out = this->itEndCur;
        out[1] = this->itEndBegin;
        out[2] = this->itEndEnd;
        void** a = this->itEndArr;
        out[3] = (Message*)a;
        if (*out == out[1]) {
            --a;
            out[3] = (Message*)a;
            Message* b = (Message*)a[0];
            out[1] = b;
            out[2] = b + 8;
            *out = b + 8;
        }
        *out = *out - 1;
        return out;
    }
    if (pos == this->itBeginCur) {
        this->FUN_008848a0(val);
        *out = this->itBeginCur;
        out[1] = this->itBeginBegin;
        out[2] = this->itBeginEnd;
        out[3] = (Message*)this->itBeginArr;
        return out;
    }
    return DoInsertValue(out, pos, pb, pe, pa, val);
}

// @ 0x00885710
void MessageQueue::InsertMessage(Message* msg)
{
    Deque& d = this->mQueue;
    Message* e = d.itEndCur;
    Message* b = d.itBeginCur;
    if (b != e) {
        Message* pe = d.itEndBegin;
        Message* last = e;
        if (e == pe)
            last = (Message*)d.itEndArr[-1] + 8;
        int prio = msg->mnPriority;
        if (last[-1].mnPriority < prio) {
            if (prio <= b->mnPriority) {
                if (prio > 0) {
                    Message* cur = d.itBeginBegin;
                    void** arr = d.itBeginArr;
                    Message* be = d.itBeginEnd;
                    while (b != e) {
                        if (b->mnPriority < prio) {
                            Message* o[4];
                            d.insert(o, b, cur, be, arr, msg);
                            return;
                        }
                        b = b + 1;
                        if (b == be) {
                            b = (Message*)arr[1];
                            ++arr;
                            be = b + 8;
                            cur = b;
                        }
                    }
                    d.FUN_008848e0(msg);
                    return;
                }
                Message* ee = d.itEndEnd;
                void** arr2 = d.itEndArr;
                Message* pb2 = d.itEndBegin;
                while (e != d.itBeginCur) {
                    Message* last2 = e;
                    if (e == pb2)
                        last2 = (Message*)arr2[-1] + 8;
                    if (prio <= last2[-1].mnPriority) {
                        Message* o[4];
                        d.insert(o, e, pb2, ee, arr2, msg);
                        return;
                    }
                    if (e == pb2) {
                        pb2 = (Message*)arr2[-1];
                        --arr2;
                        e = pb2 + 8;
                        ee = e;
                    }
                    e = e - 1;
                }
            }
            d.FUN_008848a0(msg);
            return;
        }
    }
    if (e + 1 == d.itEndEnd) {
        d.FUN_00884390(msg);
    } else {
        d.itEndCur = e + 1;
        if (e != 0) {
            e->mId = msg->mId;
            e->mpMessageRC = msg->mpMessageRC;
            e->mpHandlerRC = msg->mpHandlerRC;
            e->mnPriority = msg->mnPriority;
            e->mpHandlerFunction = msg->mpHandlerFunction;
            e->mpHandlerFunctionContext = msg->mpHandlerFunctionContext;
        }
    }
}

// @ 0x00885890
void Server::MessagePost(int a, void* rc, int b, void* hf)
{
    if (this->mbRefCountEnabled != 0) {
        if (rc != 0)
            ((RCObj*)rc)->v1();
        if (hf != 0)
            ((RCObj*)hf)->v2();
    }
    if (this->mbThreadSafetyEnabled != 0)
        this->mQueueMutex.Lock(&g_1427918);
    Message msg;
    msg.mId = a;
    msg.mpMessageRC = rc;
    msg.mpHandlerRC = hf;
    msg.mnPriority = b;
    msg.mpHandlerFunction = 0;
    msg.mpHandlerFunctionContext = 0;
    this->mQueue.InsertMessage(&msg);
    if (this->mbThreadSafetyEnabled != 0)
        this->mQueueMutex.Unlock();
}

// @ 0x00885930
void Server::MessagePostFunction(int a, void* rc, int b, void* fn, void* ctx)
{
    if (this->mbRefCountEnabled != 0) {
        if (rc != 0)
            ((RCObj*)rc)->v1();
        if (fn != 0)
            ((void(*)(int, int, void*))fn)(1, 0, ctx);
    }
    if (this->mbThreadSafetyEnabled != 0)
        this->mQueueMutex.Lock(&g_1427918);
    Message msg;
    msg.mId = a;
    msg.mpMessageRC = rc;
    msg.mpHandlerRC = 0;
    msg.mnPriority = b;
    msg.mpHandlerFunction = fn;
    msg.mpHandlerFunctionContext = ctx;
    this->mQueue.InsertMessage(&msg);
    if (this->mbThreadSafetyEnabled != 0)
        this->mQueueMutex.Unlock();
}

// @ 0x01068380
int* Deque_s0106_78e0::clear(int* out, DeqNode* self, DeqNode* root)
{
    DeqNode* n = self->m08;
    out[1] = (int)root;
    out[0] = (int)n;
    while (n == 0) {
        out[1] += 4;
        n = *(DeqNode**)out[1];
        out[0] = (int)n;
    }
    DeqNode* r = (DeqNode*)root->m00;
    if (r == self) {
        root->m00 = r->m08;
        SP_DeleteArray(self);
        m0c = m0c - 1;
        return out;
    }
    DeqNode* e = r->m08;
    while (e != self) {
        r = e;
        e = r->m08;
    }
    r->m08 = e->m08;
    SP_DeleteArray(self);
    m0c = m0c - 1;
    return out;
}
