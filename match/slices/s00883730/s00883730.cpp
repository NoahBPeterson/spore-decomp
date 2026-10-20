// flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 /fp:fast
// Slice s00883730 - EA::Locale boot (Init / MakeLocaleAvailable fallback) followed by
// EA::Messaging::Server + MessageQueue / Deque functions (SporeApp.exe).
//
// Self-contained (no project headers): every type is modelled here so the compiler emits
// the same member offsets the original used.

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// external helpers (defined elsewhere in the binary)
// ---------------------------------------------------------------------------
extern void* e_opnew(int size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern void  e_opdel(void* p);                       // 0xf47380
extern void* e_copyov(void* dst, void* first, void* last);   // 0x11e0744
extern "C" __declspec(dllimport) void* memmove(void* dst, const void* src, unsigned int n);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* out);

extern int g_1427918;         // 0x1427918  (mutex Lock user-data tag)

static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ===========================================================================
// EA::Locale
// ===========================================================================
struct LocString {                     // eastl::fixed_string<wchar_t,16,1>
    wchar_t* mpBegin;                  // +0x00
    wchar_t* mpEnd;                    // +0x04
    char     _pad[0x2c];               // -> 0x34

    void AppendElement(const wchar_t* begin, const wchar_t* end);   // 0x68cc10
    LocString& operator=(const LocString& o)
    {
        if (this != &o) {
            if (mpBegin != mpEnd) {
                *mpBegin = 0;
                mpEnd = mpBegin;
            }
            AppendElement(o.mpBegin, o.mpEnd);
        }
        return *this;
    }
};

extern LocString       gLocale;        // 0x1650408
extern const LocString kSystemLocale;  // 0x15490e4

extern bool Locale_MakeLocaleAvailable(const LocString* name, const LocString* system); // 0x87d9a0
extern int  Locale_GetLocaleInfoInt(const wchar_t* language, const wchar_t* country);   // 0x881220
extern void Locale_SetLocale(const LocString* locale, int a, int b);                    // 0x882b30

struct LocMap {                        // eastl::map<fixed_string,fixed_string>
    void*         f00;                 // +0x00
    void*         f04;                 // +0x04
    void*         f08;                 // +0x08
    void*         root;                // +0x0c
    unsigned char color;               // +0x10
    unsigned char _p[3];
    int           count;               // +0x14
    int           f18;                 // +0x18

    void Clear(void* node);            // 0x87fe10
    void clear()
    {
        Clear(root);
        f04 = (void*)&f04;
        f08 = (void*)&f04;
        root = 0;
        color = 0;
        count = 0;
    }
};

extern LocMap gLanguageMap;            // 0x1549180
extern LocMap gCountryMap;             // 0x154919c

// @ 0x00883730
bool EA_Locale_Init(void)
{
    if (Locale_MakeLocaleAvailable(&gLocale, &kSystemLocale)) {
        Locale_GetLocaleInfoInt(
            L"en^English^English^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Mon.,Tue.,Wed.,Thur.,Fri.,Sat.,Sun.^January,February,March,April,May,June,July,August,September,October,November,December^Jan.,Feb.,Mar.,Apr.,May,June,July,Aug.,Sept.,Oct.,Nov.,Dec.^0^%f %l^",
            L"us^United States^United States^R^E^AM,PM^%h:%<02M:%<02S %<A^%#02m/%#02d/%02y^%>+m %<#d, %<y^$^,^.^%$%W%?p%?02F^%$-%W%?p%?02F^USA^840^%N%?p%?02F^%N%?p%?02F%%");
        Locale_GetLocaleInfoInt(
            L"en^English^English^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Mon.,Tue.,Wed.,Thur.,Fri.,Sat.,Sun.^January,February,March,April,May,June,July,August,September,October,November,December^Jan.,Feb.,Mar.,Apr.,May,June,July,Aug.,Sept.,Oct.,Nov.,Dec.^0^%f %l^",
            L"gb^United Kingdom^United Kingdom^L^E^^%02H:%02M:%<02S^%#02d/%#02m/%02y^%>#d %+m %<y^\xA3^,^.^%$%W%?p%?02F^-%$%W%?p%?02F^GBR^826^%N%?p%?02F^%N%?p%?02F%%");
        Locale_SetLocale(&kSystemLocale, 0, 0);
    }
    return true;
}

// @ 0x00883780
char EA_Locale_InstallFallback(void)
{
    if (!Locale_MakeLocaleAvailable(&gLocale, &kSystemLocale)) {
        Locale_SetLocale(&kSystemLocale, 0, 0);
        gLocale = kSystemLocale;
        gCountryMap.clear();
        gLanguageMap.clear();
    }
    return 1;
}

// ===========================================================================
// EA::Messaging
// ===========================================================================
struct Message {
    int   mId;                      // +0x00
    void* mpMessageRC;              // +0x04
    void* mpHandlerRC;              // +0x08
    int   mnPriority;               // +0x0c
    void* mpHandlerFunction;        // +0x10
    void* mpHandlerFunctionContext; // +0x14

    Message() {}
    Message& operator=(const Message& o)
    {
        mId = o.mId;
        mpMessageRC = o.mpMessageRC;
        mpHandlerRC = o.mpHandlerRC;
        mnPriority = o.mnPriority;
        mpHandlerFunction = o.mpHandlerFunction;
        mpHandlerFunctionContext = o.mpHandlerFunctionContext;
        return *this;
    }
    Message(const Message& o)
    {
        mId = o.mId;
        mpMessageRC = o.mpMessageRC;
        mpHandlerRC = o.mpHandlerRC;
        mnPriority = o.mnPriority;
        mpHandlerFunction = o.mpHandlerFunction;
        mpHandlerFunctionContext = o.mpHandlerFunctionContext;
    }
};

struct HObj {                       // handler object vtbl: [1]=invoke, [2]=addref, [3]=release
    virtual void v0();
    virtual void v1(uint id, void* rc);   // +4
    virtual void v2();                    // +8
    virtual void v3();                    // +0xc
};
struct RCObj {
    virtual void v0();
    virtual void v1();
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

struct DequeIter {
    Message* cur;                   // +0x00
    Message* beg;                   // +0x04
    Message* end;                   // +0x08
    void**   arr;                   // +0x0c

    DequeIter& operator=(const DequeIter& o)
    {
        cur = o.cur;
        beg = o.beg;
        end = o.end;
        arr = o.arr;
        return *this;
    }
    DequeIter(const DequeIter& o)
    {
        cur = o.cur;
        beg = o.beg;
        end = o.end;
        arr = o.arr;
    }
    DequeIter& advanceBy(int n);
    DequeIter& inc()
    {
        cur = (Message*)((char*)cur + 0x18);
        if (cur == end) {
            ++arr;
            cur = (Message*)arr[0];
            end = (Message*)((char*)cur + 0xc0);
            beg = cur;
        }
        return *this;
    }
    DequeIter  add(int n) const;
};

struct Deque {
    void*     mpPtrArray;           // +0x00
    int       mnPtrArraySize;       // +0x04
    DequeIter itBegin;              // +0x08
    DequeIter itEnd;                // +0x18

    int  count() const
    {
        return (int)(itBegin.end - itBegin.cur) / 0x18
             + ((int)((char*)itEnd.arr - (char*)itBegin.arr) >> 2) * 8
             + (int)(itEnd.cur - itEnd.beg) / 0x18
             - 8;
    }
    void init(int n);                       // 0x883f10
    void grow(uint n, int side);            // 0x883de0
    void pushFrontAux(const Message* v);    // 0x8842e0
    void pushBackAux(const Message* v);     // 0x884390
    void pushFront(const Message* v);       // 0x8848a0
    void pushBack(const Message* v);        // 0x8848e0
    DequeIter* insertNode(DequeIter* out, HandlerListNode* list, const HandlerInfo* info); // 0x884260
};

struct MessageQueue {
    Deque mQueue;                   // +0x00
    int   _pad[2];                  // +0x28
    bool  GetNextMessage(Message* out);     // 0x884550
};

struct Hashtable {
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

struct Mutex {
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

struct Server {
    void**       vftable;                   // +0x00
    int          _pad04;                    // +0x04
    MessageQueue mQueue;                    // +0x08
    Mutex        mQueueMutex;               // +0x38
    long long    mnQueueProcessedMessageCount; // +0x68
    Hashtable    mHandlerInfoMap;           // +0x70
    Mutex        mHandlerInfoMapMutex;      // +0x90
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

// @ 0x00883880
int Server::GetOption(int option) const
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
void Server::SetOption(int option, int value)
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
void Server::AddHandlerObj(void* handler, uint id)
{
    if (handler != 0) {
        HandlerInfo info;
        info.mpHandler = handler;
        info.mnPriority = 0;
        info.mbRefCounted = 0;
        info.mpHandlerFunction = 0;
        info.mpHandlerFunctionContext = 0;
        typedef void (__thiscall* Fn)(Server*, HandlerInfo*, uint);
        ((Fn)this->vftable[0x44 / 4])(this, &info, id);
    }
}

// @ 0x008839e0
void Server::AddHandlerRC(void* handler, uint id)
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
        typedef void (__thiscall* Fn)(Server*, HandlerInfo*, uint);
        ((Fn)this->vftable[0x44 / 4])(this, &info, id);
    }
}

// @ 0x00883a30
void Server::AddHandlerFn(void* fn, void* ctx, uint id, char refcounted, int priority)
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
        typedef void (__thiscall* Fn)(Server*, HandlerInfo*, uint);
        ((Fn)this->vftable[0x44 / 4])(this, &info, id);
    }
}

// @ 0x00883ab0
int Server::LockMutexes(bool lock)
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

// @ 0x00884550
bool MessageQueue::GetNextMessage(Message* out)
{
    Message* p = this->mQueue.itBegin.cur;
    if (p == this->mQueue.itEnd.cur)
        return false;
    *out = *p;
    Message* next = p + 1;
    if (next != this->mQueue.itBegin.end) {
        this->mQueue.itBegin.cur = next;
        return true;
    }
    if (this->mQueue.itBegin.beg != 0)
        e_opdel(this->mQueue.itBegin.beg);
    ++this->mQueue.itBegin.arr;
    Message* nb = (Message*)this->mQueue.itBegin.arr[0];
    this->mQueue.itBegin.beg = nb;
    this->mQueue.itBegin.end = nb + 8;
    this->mQueue.itBegin.cur = nb;
    return true;
}

// @ 0x00884700
int Server::ProcessQueueRun(void)
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
        Message msg;
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
            ((HObj*)msg.mpHandlerRC)->v1((uint)msg.mId, msg.mpMessageRC);
            if (this->mbRefCountEnabled != 0)
                ((HObj*)msg.mpHandlerRC)->v3();
        } else if (msg.mpHandlerFunction != 0) {
            ((void(*)(int, void*, void*))msg.mpHandlerFunction)(
                msg.mId, msg.mpMessageRC, msg.mpHandlerFunctionContext);
            if (this->mbRefCountEnabled != 0)
                ((void(*)(int, int, void*))msg.mpHandlerFunction)(
                    2, 0, msg.mpHandlerFunctionContext);
        } else {
            typedef void (__thiscall* Fn)(Server*, uint, void*, int);
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

// @ 0x00884100
int Server::ProcessQueueTimeout(uint threshold, uint maxCount, uint timeout)
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
                typedef int (__thiscall* Fn)(Server*);
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

// ===========================================================================
// Deque internals
// ===========================================================================

// @ 0x00883b00
DequeIter& DequeIter::advanceBy(int n)
{
    unsigned int u = (unsigned int)((int)(this->cur - this->beg) + n);
    if (u < 8) {
        this->cur = this->cur + n;
        return *this;
    }
    int d = (int)(u + 0x1000000);
    int idx = ((d + ((d >> 31) & 7)) >> 3) - 0x200000;
    this->arr = this->arr + idx;
    Message* base = (Message*)this->arr[0];
    this->beg = base;
    this->end = (Message*)((char*)base + 0xc0);
    this->cur = base + (int)(u - (unsigned)(idx * 8));
    return *this;
}

// @ 0x00883d90
DequeIter DequeIter::add(int n) const
{
    DequeIter tmp = *this;
    return tmp.advanceBy(n);
}

// @ 0x00883b80
DequeIter* DequeCopyForward(DequeIter* out, DequeIter first, DequeIter last, DequeIter result)
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
void DequeCopyBackward(DequeIter* out, DequeIter first, DequeIter last, DequeIter result)
{
    while (first.cur != last.cur) {
        if (first.cur == first.beg) {
            --first.arr;
            first.beg = (Message*)first.arr[0];
            first.end = first.beg + 8;
            first.cur = first.end;
        }
        --first.cur;
        if (result.cur == result.beg) {
            --result.arr;
            result.beg = (Message*)result.arr[0];
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

// @ 0x00884260
DequeIter* Deque::insertNode(DequeIter* out, HandlerListNode* list, const HandlerInfo* info)
{
    HandlerListNode* node = (HandlerListNode*)e_opnew(0x1c, "EASTL", 0, 0, kAllocFile, 0xd1);
    if (&node->info != 0)
        node->info = *info;
    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
    out->cur = (Message*)node;
    return out;
}

// @ 0x008842e0
void Deque::pushFrontAux(const Message* value)
{
    Message v = *value;
    if (this->itBegin.arr == (void**)this->mpPtrArray)
        this->grow(1, 0);
    Message* node = (Message*)e_opnew(0xc0, "EASTL", 0, 0, kAllocFile, 0xd1);
    this->itBegin.arr[-1] = node;
    --this->itBegin.arr;
    Message* base = (Message*)this->itBegin.arr[0];
    this->itBegin.beg = base;
    this->itBegin.end = (Message*)((char*)base + 0xc0);
    this->itBegin.cur = (Message*)((char*)base + 0xc0 - 0x18);
    if (this->itBegin.cur != 0)
        *this->itBegin.cur = v;
}

// @ 0x00884390
void Deque::pushBackAux(const Message* value)
{
    Message v = *value;
    if (((int)((char*)this->itEnd.arr - (char*)this->mpPtrArray) >> 2) + 1 >= this->mnPtrArraySize)
        this->grow(1, 1);
    Message* node = (Message*)e_opnew(0xc0, "EASTL", 0, 0, kAllocFile, 0xd1);
    this->itEnd.arr[1] = node;
    Message* cur = this->itEnd.cur;
    if (cur != 0)
        *cur = v;
    ++this->itEnd.arr;
    Message* base = (Message*)this->itEnd.arr[0];
    this->itEnd.beg = base;
    this->itEnd.end = (Message*)((char*)base + 0xc0);
    this->itEnd.cur = this->itEnd.beg;
}

// @ 0x008848a0
void Deque::pushFront(const Message* value)
{
    Message* cur = this->itBegin.cur;
    if (cur != this->itBegin.beg) {
        Message* p = cur - 1;
        this->itBegin.cur = p;
        if (p != 0)
            *p = *value;
        return;
    }
    this->pushFrontAux(value);
}

// @ 0x008848e0
void Deque::pushBack(const Message* value)
{
    Message* cur = this->itEnd.cur;
    Message* next = cur + 1;
    if (next != this->itEnd.end) {
        this->itEnd.cur = next;
        if (cur != 0)
            *cur = *value;
        return;
    }
    this->pushBackAux(value);
}

// @ 0x00883de0
void Deque::grow(uint n, int side)
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
    Message* bbase = (Message*)dest[0];
    this->itBegin.beg = bbase;
    this->itBegin.end = (Message*)((char*)bbase + 0xc0);
    this->itEnd.arr = dest + (oldCount - 1);
    Message* ebase = (Message*)this->itEnd.arr[0];
    this->itEnd.beg = ebase;
    this->itEnd.end = (Message*)((char*)ebase + 0xc0);
}

// @ 0x00883f10
void Deque::init(int n)
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
    Message* bbase = (Message*)p[0];
    this->itBegin.beg = bbase;
    this->itBegin.end = (Message*)((char*)bbase + 0xc0);
    this->itBegin.cur = this->itBegin.beg;
    this->itEnd.arr = pe - 1;
    Message* ebase = (Message*)this->itEnd.arr[0];
    this->itEnd.beg = ebase;
    this->itEnd.end = (Message*)((char*)ebase + 0xc0);
    this->itEnd.cur = (Message*)((char*)ebase + (n & 7) * 0x18);
}

// @ 0x008845d0
bool Server::RemoveHandlerInternal(void* handler, uint id, int priority)
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
