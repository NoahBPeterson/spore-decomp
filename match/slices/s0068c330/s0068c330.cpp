// Slice s0068c330 — free-list queue + resource name/key helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;
typedef unsigned __int64 uint64;

// ---------------------------------------------------------------------------
// CRT imports
// ---------------------------------------------------------------------------
extern "C" {
__declspec(dllimport) int   __cdecl iswctype(unsigned short c, unsigned t);
__declspec(dllimport) int   __cdecl isdigit(int c);
__declspec(dllimport) int   __cdecl isxdigit(int c);
__declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
__declspec(dllimport) void* __cdecl memcpy(void* dst, const void* src, unsigned n);
__declspec(dllimport) char* __cdecl strchr(const char* s, int c);
__declspec(dllimport) void* __cdecl memchr(const void* s, int c, unsigned n);
__declspec(dllimport) unsigned long __cdecl strtoul(const char* s, char** e, int base);
}

// ---------------------------------------------------------------------------
// externals (masked relocations)
// ---------------------------------------------------------------------------
void* EAAllocate(unsigned size, const char* area, int a, int b, const char* file, int line); // 0x00F473A0
void  EAFree(void* p);                                                                        // 0x00F47380
void* GetManager();                                                                           // 0x0067DCD0
void  WStr_Format(void* out, const wchar_t* fmt, ...);                                        // 0x0041E050
void  Str_Format(void* out, const char* fmt, ...);                                            // 0x00472FE0
void  Str_AppendFormat(void* out, const char* fmt, ...);                                      // 0x005F9450
void  StrFormatKey(void* out, const wchar_t* fmt, ...);                                       // 0x004E0850 (cdecl vararg)
uint64 __fastcall AtomicRead64(volatile uint64* p);                                           // 0x0068C140
void   __fastcall FreeListDrain(void* self);                                                  // 0x0068C220

struct ResKey {
    uint32 mInstance;   // +0x00
    uint32 mType;       // +0x04
    uint32 mGroup;      // +0x08
};

struct Atomic64 {
    void Exchange(uint64 v);       // 0x0068C1B0 (thiscall)
};

struct PopOut {
    void* a;
    void* b;
};

struct PendingVec {
    void DoInsertValue(void* pos, void* v);   // 0x007E1340 (thiscall)
};

// ===========================================================================
// @ 0x0068C6D0  SP::SetKeyKind
// ===========================================================================
void SetKeyKind(ResKey* key, uint8 hi, uint8 lo)
{
    uint32 v = ((uint32)hi << 8) | (uint32)lo;
    key->mGroup = v | (key->mGroup & 0xffff0000u);
}

// ===========================================================================
// @ 0x0068C700  InvalidEditorModelKey
// ===========================================================================
ResKey* InvalidEditorModelKey(ResKey* key, uint32 v)
{
    uint32 bits = (v << 0x18) ^ key->mGroup;
    bits &= 0x1f000000u;
    *(volatile uint32*)&key->mGroup ^= bits;
    return key;
}

// ===========================================================================
// @ 0x0068C720  find last wide char
// ===========================================================================
wchar_t* FindLastCharW(wchar_t* first, wchar_t* last, const wchar_t* c)
{
    if (last != first) {
        do {
            --last;
            if (*last == *c)
                return last;
        } while (last != first);
    }
    return 0;
}

// ===========================================================================
// @ 0x0068C750  find last narrow char
// ===========================================================================
char* FindLastCharA(char* first, char* last, const char* c)
{
    if (last != first) {
        do {
            --last;
            if (*last == *c)
                return last;
        } while (last != first);
    }
    return 0;
}

// ===========================================================================
// @ 0x0068C770  GetExplicitIdStart (wide)
// ===========================================================================
wchar_t* GetExplicitIdStartW(wchar_t* first, wchar_t* last, uint8 flag3, uint8 flag4)
{
    wchar_t* start = first;
    if (flag3 != 0) {
        if (last != first) {
            wchar_t* p = last;
            do {
                --p;
                if (*p == 0x5f) {
                    start = p + 1;
                    break;
                }
            } while (p != first);
        }
    }
    if (((int)((char*)last - (char*)start) & ~1) < 0x10)
        return 0;
    if (*start == 0x30 && (start[1] == 0x78 || start[1] == 0x58)) {
        start += 2;
    } else {
        if (iswctype(*start, 4) == 0)
            return 0;
    }
    {
        wchar_t* p = start;
        int n = 0;
        while (p != last) {
            if (iswctype(*p, 0x80) == 0)
                return 0;
            ++p;
            ++n;
        }
        if (n == 8)
            return start;
        if (n == 0x10 && flag4 != 0)
            return start;
    }
    return 0;
}

// ===========================================================================
// @ 0x0068C820  GetExplicitIdStart (narrow)
// ===========================================================================
char* GetExplicitIdStartA(char* first, char* last, uint8 flag3, uint8 flag4)
{
    char* start = first;
    if (flag3 != 0) {
        if (last != first) {
            char* p = last;
            do {
                --p;
                if (*p == 0x5f) {
                    start = p + 1;
                    break;
                }
            } while (p != first);
        }
    }
    if ((int)(last - start) < 8)
        return 0;
    if (*start == 0x30 && (start[1] == 0x78 || start[1] == 0x58)) {
        start += 2;
    } else {
        if (isdigit((unsigned char)*start) == 0)
            return 0;
    }
    {
        char* p = start;
        int n = 0;
        while (p != last) {
            if (isxdigit((unsigned char)*p) == 0)
                return 0;
            ++p;
            ++n;
        }
        if (n == 8)
            return start;
        if (n == 0x10 && flag4 != 0)
            return start;
    }
    return 0;
}

// ===========================================================================
// @ 0x0068CD40  packed string insert C-string (thiscall)
// ===========================================================================
struct PackStr {
    char* mpBegin;    // +0x00
    char* mpEnd;      // +0x04
    char* mpCapacity; // +0x08
    void* mAllocator; // +0x0c (EASTL allocator; the empty string leaves this null)
    void* mEmptyRef;  // +0x10 (copied by the copy ctor; equals mpBegin for the shared empty string)

    PackStr* InsertCStr(uint32 id, const char* s);                  // 0x0068CD40
    void __declspec(noinline) Insert(char* pos, const char* first, const char* last);  // 0x0068C9E0

    void Swap(PackStr& other);                                     // 0x0068D1C0 (thiscall, ret 4)
    void reserve(unsigned n);                                       // 0x0068D480 (thiscall, ret 4)
};

PackStr* PackStr::InsertCStr(uint32 id, const char* s)
{
    const char* e = s;
    while (*e++)
        ;
    Insert(mpBegin + id, s, e - 1);
    return this;
}

// ===========================================================================
// @ 0x0068D1A0  SPNameFromKey callback thunk
// ===========================================================================
void SPNameFromKeyW(const ResKey* key, void* out, const wchar_t* name);
void SPNameFromKeyA(const ResKey* key, void* out, const char* name);

void SPNameFromKeyThunk(const ResKey* key, void* out, int a3, int a4, const char* name)
{
    SPNameFromKeyA(key, out, name);
}

// ===========================================================================
// @ 0x0068D420  hash bucket clear
// ===========================================================================
void __stdcall HashClearBuckets(void** buckets, uint32 n)
{
    for (uint32 i = 0; i < n; ++i) {
        void* node = buckets[i];
        while (node != 0) {
            void* b = *(void**)((char*)node + 4);
            void* c = *(void**)((char*)node + 0xc);
            void* next = *(void**)((char*)node + 0x14);
            if ((((char*)c - (char*)b) & ~1) > 2 && b != 0)
                EAFree(b);
            EAFree(node);
            node = next;
        }
        buckets[i] = 0;
    }
}

// ===========================================================================
// @ 0x0068C520  FreeQueue::Create
// ===========================================================================
struct FreeQueue {
    uint64 mPop;      // +0x00
    uint64 mPush;     // +0x08
    void*  mPending;  // +0x10
    void*  mPendingEnd;//+0x14
    void*  mCapacity; // +0x18
    char   pad1c[8];
    uint32 m24;       // +0x24
    uint32 m28;       // +0x28
    uint32 m2c;       // +0x2c
    uint32 m30;       // +0x30

    bool __declspec(noinline) TryPop(void** out);
    void Drain();
    void Shutdown();
    void Flush();
    void DrainList();
};

FreeQueue* FreeQueueCreate()
{
    FreeQueue* q = (FreeQueue*)EAAllocate(0x38, "App", 0, 0, 0, 0);
    if (q != 0) {
        ((Atomic64*)q)->Exchange(0);
        ((Atomic64*)((char*)q + 8))->Exchange(0);
        q->mPending = 0;
        q->mPendingEnd = 0;
        q->mCapacity = 0;
        q->m24 = 1;
        q->m28 = 5;
        q->m2c = 2;
        q->m30 = 0x32;
        return q;
    }
    return 0;
}

// ===========================================================================
// @ 0x0068C4E0  FreeQueue::Shutdown
// ===========================================================================
void FreeQueue::Shutdown()
{
    void* p = mPending;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        EAFree(p);
    {
        PopOut v;
        while (TryPop((void**)&v)) {
        }
    }
    return DrainList();
}

// ===========================================================================
// @ 0x0068C460  FreeQueue::Drain
// ===========================================================================
void FreeQueue::Drain()
{
    while (mPending != mPendingEnd) {
        void* item = ((void**)mPendingEnd)[-2];
        void (__cdecl* f)(void*) = ((void(__cdecl**)(void*))mPendingEnd)[-1];
        f(item);
        mPendingEnd = (char*)mPendingEnd - sizeof(uint64);
    }
    PopOut v;
    while (TryPop((void**)&v))
        ((void (__cdecl*)(void*))v.b)(v.a);
}

// ===========================================================================
// @ 0x0068C590  FreeQueue::Flush
// ===========================================================================
void FreeQueue::Flush()
{
    PopOut v;
    while (TryPop((void**)&v)) {
        void** end = (void**)mPendingEnd;
        if (end < (void**)mCapacity) {
            mPendingEnd = end + 2;
            if (end != 0) {
                end[0] = v.a;
                end[1] = 0;
            }
        } else {
            ((PendingVec*)((char*)this + 0x10))->DoInsertValue(end, &v);
        }
    }
    uint32* propsRoot = *(uint32**)0x015fd918;
    uint32 n = m24;
    uint32 d = m28;
    uint32 a = m2c;
    uint32 b = m30;
    if (propsRoot != 0) {
        uint32* p = *(uint32**)((char*)propsRoot + 0x3c);
        n = *(uint32*)((char*)p + 0x134);
        d = *(uint32*)((char*)p + 0x138);
        a = *(uint32*)((char*)p + 0x13c);
        b = *(uint32*)((char*)p + 0x140);
    }
    uint32 count = (uint32)(((char*)mPendingEnd - (char*)mPending) >> 3);
    uint32 target = count;
    if (d != 0) {
        uint32 t = (count * n) / d + a;
        if (t <= count)
            target = t;
    }
    if (count - target > b)
        target = count - b;
    while (target != 0) {
        void* item = *(void**)((char*)mPendingEnd - 8);
        void (__cdecl* f)(void*) = *(void(__cdecl**)(void*))((char*)mPendingEnd - 4);
        mPendingEnd = (char*)mPendingEnd - 8;
        f(item);
        --target;
    }
}

// ===========================================================================
// @ 0x0068D0D0  SPNameFromKey (wide output)
// ===========================================================================
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;

    void Insert(wchar_t* pos, const wchar_t* first, const wchar_t* last); // 0x005F7DA0
    void resize(unsigned n);                                              // 0x00429520
};

void SPNameFromKeyW(const ResKey* key, void* out, const wchar_t* name)
{
    WStr_Format(out, L"0x%08x", key->mGroup);
    if (name != 0) {
        const wchar_t* pref = (const wchar_t*)0x013fe614;
        const wchar_t* e = pref;
        do {
            ++e;
        } while (*e);
        ((WStr*)out)->Insert(*(wchar_t**)out, pref, e);
        const wchar_t* n = name;
        const wchar_t* ne = n;
        while (*ne)
            ++ne;
        ((WStr*)out)->Insert(*(wchar_t**)out, n, ne);
    }
    void* mgr = GetManager();
    uint32 res = ((uint32(__thiscall*)(void*, uint32))(*(void***)mgr)[0x8c / 4])(mgr, key->mType);
    if (res != 0)
        StrFormatKey(out, L"!0x%08x.%ls", key->mInstance, res);
    else
        StrFormatKey(out, L"!0x%08x.0x%08x", key->mInstance, key->mType);
}

// ===========================================================================
// @ 0x0068D290  SPNameFromKey (narrow output)
// ===========================================================================
void SPNameFromKeyA(const ResKey* key, void* out, const char* name)
{
    Str_Format(out, "0x%08x", key->mGroup);
    if (name != 0) {
        ((PackStr*)out)->Insert(*(char**)out, (const char*)0x1403550, (const char*)0x1403551);
        const char* n = name;
        const char* ne = n;
        while (*ne)
            ++ne;
        ((PackStr*)out)->Insert(*(char**)out, n, ne);
    }
    void* mgr = GetManager();
    uint32 res = ((uint32(__thiscall*)(void*, uint32))(*(void***)mgr)[0x8c / 4])(mgr, key->mType);
    if (res != 0)
        Str_AppendFormat(out, "!0x%08x.%ls", key->mInstance, res);
    else
        Str_AppendFormat(out, "!0x%08x.0x%08x", key->mInstance, key->mType);
    if (name != 0)
        Str_Format(out, "%hs_%hs", name, *(char**)out);
}

// ---------------------------------------------------------------------------
// additional callees (masked)
// ---------------------------------------------------------------------------
void* FUN_0068C680(const char* s, unsigned n);          // Resource::HashNameN
void  FUN_0068CF00(void* dst, void* src);               // packed copy ctor
void  FUN_0068CF60(void* s, const char* b, const char* e); // packed assign
void  FUN_0068CBB0(void* self, unsigned n);             // packed erase
void  FUN_0068D0B0(void* out, const void* tpl, const char* s); // fixed wstring ctor
struct PairUW {                                        // eastl::pair<unsigned const, WStr>
    void ctor(const uint32* pKey, const void* src);     // 0x00688760 (thiscall; constructs into ecx)
};
void* FUN_0068CFF0(void* ht, void* a, void* b, void* c);
void  FUN_0068C280(uint32 lo, uint32 hi);               // tagged-head release helper

extern "C" __int64 _InterlockedCompareExchange64(volatile __int64* dest, __int64 exch,
                                                 __int64 comp);

struct FreeList;                                        // 0x0068C280 Push is a thiscall member

// thiscall helpers reached with an explicit ecx (same addresses as the free decls above).
struct PackStrOps {                                     // packed string (EASTL string) members
    void Ctor(PackStr* src);                            // 0x0068CF00  copy ctor
    void Assign(const char* first, const char* last);   // 0x0068CF60  assign/append range
    void Erase(unsigned n);                             // 0x0068CBB0  erase tail down to n
};
struct HashMapOps {                                     // eastl::hashtable member
    void* Insert(void* itOut, void* pair, int flag);    // 0x0068CFF0  insert(pair)
    void  Find(void** itOut, uint32 key);               // 0x00A3B2C0  find(key)
};
struct FreeQueueOps {                                   // FreeList::Push(uint32, uint32) thiscall
    void Push(uint32 lo, uint32 hi);                    // 0x0068C280
};
inline void FreeListPush(void* self, uint32 lo, uint32 hi)
{
    ((FreeQueueOps*)self)->Push(lo, hi);
}

// ===========================================================================
// @ 0x0068C330  FreeQueue::TryPop
// ===========================================================================
bool FreeQueue::TryPop(void** out)
{
    // Tagged-head CAS loop on the push side (+0x08): the popped node stores the next
    // tagged head at node+0x08, and the ABA tag (high dword) is bumped on every pop.
    uint64 raw = mPush;
    uint64 head = AtomicRead64(&raw);
    if ((uint32)head == 0)
        return false;
    for (;;) {
        uint64 headCopyRaw = head;
        uint64 headCopy = AtomicRead64(&headCopyRaw);
        uint64 nextRaw = *(volatile uint64*)((unsigned)headCopy + 8);
        uint64 next = AtomicRead64(&nextRaw);
        uint64 headCopy2Raw = headCopy;
        uint64 headCopy2 = AtomicRead64(&headCopy2Raw);
        uint64 desired = (uint64)(uint32)next | ((uint64)((uint32)(headCopy2 >> 32) + 1) << 32);
        if ((uint64)_InterlockedCompareExchange64((volatile __int64*)&mPush, (__int64)desired,
                                                  (__int64)headCopy2) == headCopy2) {
            uint64 nodeRaw = (uint64)(uint32)headCopy;
            uint64 node = AtomicRead64(&nodeRaw);
            out[0] = (void*)*(uint32*)(unsigned)node;
            out[1] = (void*)*(uint32*)((unsigned)node + 4);
            FreeListPush(this, (uint32)headCopy, (uint32)(headCopy >> 32));
            return true;
        }
        uint64 raw2 = mPush;
        head = AtomicRead64(&raw2);
        if ((uint32)head == 0)
            return false;
    }
}

// ===========================================================================
// @ 0x0068C9E0  packed string insert (pos, first, last)
// ===========================================================================
void PackStr::Insert(char* pos, const char* first, const char* last)
{
    // eastl::string::insert(pos, first, last), inlined body (SSO or heap buffer).
    const unsigned n = (unsigned)(last - first);
    if (n == 0)
        return;
    const unsigned size = (unsigned)(mpEnd - mpBegin);
    const unsigned cap = (unsigned)(mpCapacity - mpBegin);
    const bool roomInBuffer = (n + 1) <= (cap - size);
    const bool overlap = !(last <= mpBegin || pos > mpEnd);
    if (roomInBuffer && !overlap) {
        const unsigned tail = (unsigned)(mpEnd - pos);
        if (n <= tail) {
            memmove(mpEnd + 1, mpEnd - n + 1, n);
            mpEnd += n;
            memmove(pos + n, pos, (tail - n) + 1);
        } else {
            const char* front = first + (tail + 1);
            memmove(mpEnd + 1, front, (unsigned)(last - front));
            mpEnd += n - tail;
            memmove(mpEnd, pos, (tail + 1));
            mpEnd += tail;
        }
        return;
    }
    unsigned newCap;
    if (roomInBuffer) {
        newCap = size + n + (1 - 0);
    } else {
        const unsigned need = size + n;
        const unsigned grow = (size > 8) ? size * 2 : 8;
        newCap = (need > grow ? need : grow) + 1;
    }
    char* dst = (char*)EAAllocate(newCap, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                          "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                          "EASTL/allocator.h",
                                  0, 0, 0, 0xd1);
    const char* oldBegin = mpBegin;
    const unsigned head = (unsigned)(pos - oldBegin);
    memmove(dst, oldBegin, head);
    char* mid = dst + head;
    memmove(mid, first, n);
    memmove(mid + n, pos, size - head);
    mid[size - head + n] = 0;
    const char* newEnd = mid + (size - head) + n;
    if ((unsigned)(mpCapacity - oldBegin) > 1 && oldBegin != 0)
        EAFree((void*)oldBegin);
    mpBegin = dst;
    mpEnd = (char*)newEnd;
    mpCapacity = dst + newCap;
}

// ===========================================================================
// @ 0x0068D1C0  packed string swap (thiscall, ret 4)
// ===========================================================================
void PackStr::Swap(PackStr& other)
{
    // Both sides are SSO (their inline buffers live at +0x0c): just swap the three pointers.
    if ((char*)this + 0xc == (char*)&other + 0xc) {
        char* a = (char*)this;
        char* b = (char*)&other;
        for (int i = 0; i < 3; ++i) {
            void* t = *(void**)(a + i * 4);
            *(void**)(a + i * 4) = *(void**)(b + i * 4);
            *(void**)(b + i * 4) = t;
        }
        return;
    }
    PackStr tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    ((PackStrOps*)&tmp)->Ctor(this);
    if (&other != this)
        ((PackStrOps*)this)->Assign(other.mpBegin, other.mpEnd);
    if (&other != &tmp)
        ((PackStrOps*)&other)->Assign(tmp.mpBegin, tmp.mpEnd);
    if ((unsigned)(tmp.mpCapacity - tmp.mpBegin) > 2 && tmp.mpBegin != 0)
        EAFree(tmp.mpBegin);
}

// ===========================================================================
// eastl::hash_map<unsigned, WStr>
// ===========================================================================
struct HashMap {
    void  Find(void** itOut, const uint32* key);        // 0x00A3B2C0  (thiscall, ret 8)
    void* Insert(void* itOut, void* pair, int flag);    // 0x0068CFF0

    void* Lookup(const uint32* pKey);                   // stands in for operator[](uint32)
};

struct Pair {                                           // eastl::pair<unsigned const, WStr>
    uint32 mKey;
    WStr   mValue;
};

// ===========================================================================
// @ 0x0068D340
// eastl::hash_map<unsigned, WStr>::operator[] (thiscall, ret 4)
// ===========================================================================
void* HashMap::Lookup(const uint32* pKey)
{
    // eastl::hash_map<unsigned, WStr>::operator[]: find, else insert an empty WStr.
    char* map = (char*)this;
    char* it;
    this->Find((void**)&it, pKey);
    char** buckets = *(char***)(map + 4);
    const uint32 nBucket = *(uint32*)(map + 8);
    char* sentinel = buckets[nBucket];
    if (it != sentinel)
        return it + 4;

    WStr empty;
    empty.mpBegin = (wchar_t*)0x01667bac;
    empty.mpEnd = (wchar_t*)0x01667bac;
    empty.mpCapacity = (wchar_t*)0x01667bae;
    empty.mAllocator = 0;

    Pair pair;
    pair.mKey = *pKey;
    ((PairUW*)&pair)->ctor(pKey, &empty);

    void* ins = 0;
    this->Insert(&ins, &pair, (int)(unsigned)pKey);

    if (((unsigned)((char*)pair.mValue.mpCapacity - (char*)pair.mValue.mpBegin) & 0xfffffffeu) > 2 &&
        pair.mValue.mpBegin != 0)
        EAFree(pair.mValue.mpBegin);
    return (char*)ins + 4;
}

// ===========================================================================
// @ 0x0068D480  packed string reserve/capacity (thiscall, ret 4)
// ===========================================================================
void PackStr::reserve(unsigned n)
{
    // eastl::string::reserve(n).
    PackStr* self = this;
    if (n != 0xffffffffu && (unsigned)((self->mpEnd - self->mpBegin) >> 1) < n) {
        const unsigned newBytes = n * 2;
        char* dst = (char*)EAAllocate(newBytes, "App", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                      "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                      "EASTL/allocator.h",
                                      0xd1);
        const unsigned oldBytes = (unsigned)((self->mpEnd - self->mpBegin) >> 1) * 2;
        memcpy(dst, self->mpBegin, oldBytes);
        char* newEnd = dst + oldBytes;
        *(unsigned short*)newEnd = 0;
        char* old = self->mpBegin;
        if ((unsigned)(self->mpCapacity - old) > 2 && old != 0 && old != (char*)self->mEmptyRef)
            EAFree(old);
        self->mpBegin = dst;
        self->mpCapacity = dst + newBytes;
        self->mpEnd = newEnd;
        return;
    }
    PackStr tmp;
    if (n < (unsigned)((self->mpEnd - self->mpBegin) >> 1))
        ((PackStrOps*)self)->Erase(n);
    ((PackStrOps*)&tmp)->Ctor(self);
    self->Swap(tmp);
    char* b = tmp.mpBegin;
    if ((unsigned)((char*)tmp.mpCapacity - b) > 2 && b != 0 && b != (char*)tmp.mEmptyRef)
        EAFree(b);
}

// ===========================================================================
// @ 0x0068D5A0  SPKeyFromName
// ===========================================================================
bool SPKeyFromName(ResKey* key, const char* name, uint32 type, uint32 defGroup)
{
    if (name == 0 || *name == 0)
        return false;
    key->mType = type;
    const char* dot = strchr(name, '.');
    const char* ext = 0;
    const char* end;
    if (dot != 0) {
        ext = dot + 1;
        end = dot;
    } else {
        end = name;
        while (*end)
            ++end;
        dot = end;
    }
    const char* bang = (const char*)memchr(name, '!', (unsigned)(dot - name));
    key->mGroup = (bang != 0) ? 0xffffffff : defGroup;
    const char* start = (bang != 0) ? bang + 1 : name;
    // memchr miss: the original folds the delimiter onto `name`, which skips the group block.
    const char* bangEnd = (bang != 0) ? bang : name;
    if (start == dot) {
        key->mInstance = 0xffffffff;
    } else {
        const char* hexs = GetExplicitIdStartA((char*)start, (char*)dot, 1, 1);
        if (hexs == 0)
            key->mInstance = (uint32)FUN_0068C680(start, (unsigned)(dot - start));
        else
            key->mInstance = (uint32)strtoul(hexs, 0, 16);
    }
    if (name != bangEnd) {
        const char* p = bangEnd;
        const char* at = 0;
        do {
            --p;
            if (*p == '@') {
                at = p;
                break;
            }
        } while (p != name);
        if (at != 0) {
            key->mGroup = 0;
        } else {
            char underscore = '_';
            const char* us = FindLastCharA((char*)name, (char*)bangEnd, &underscore);
            const char* s2 = name;
            if (us != 0)
                s2 = us + 1;
            const char* hexs = GetExplicitIdStartA((char*)s2, (char*)bangEnd, 0, 0);
            if (hexs == 0) {
                key->mGroup = (uint32)FUN_0068C680(name, (unsigned)(bangEnd - name));
                // cache the group name string (wide) in the global group->name map
                HashMap* groupNames = (HashMap*)0x0152C864;
                WStr* cached = (WStr*)groupNames->Lookup(&key->mGroup);
                cached->resize((unsigned)(bangEnd - name));
                wchar_t* dst = cached->mpBegin;
                for (const char* q = name; q != bangEnd; ++q)
                    *dst++ = (wchar_t)(signed char)*q;
            } else {
                key->mGroup = (uint32)strtoul(hexs, 0, 16);
            }
        }
    }
    if (ext != 0) {
        key->mType = 0xffffffff;
        if (*ext == 0)
            return true;
        const char* e = ext;
        while (*e)
            ++e;
        const char* hexs = GetExplicitIdStartA((char*)ext, (char*)e, 0, 0);
        if (hexs != 0) {
            key->mType = (uint32)strtoul(hexs, 0, 16);
            return true;
        }
        unsigned short tmp[16];
        tmp[0] = 0;
        FUN_0068D0B0(tmp, (const void*)0x013F3DA0, ext);
        void* mgr = GetManager();
        int id = ((int(__thiscall*)(void*, void*))(*(void***)mgr)[0x88 / 4])(mgr, tmp);
        if (id == -1)
            id = (int)FUN_0068C680(ext, (unsigned)(e - ext));
        key->mType = (uint32)id;
    }
    (void)end;
    return true;
}
