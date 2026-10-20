// Slice s0094cac0 -- EA::Sockets::Manager dialup tail, the UI-layout string
// cache (unattributed COMDAT cluster), EA::Sockets::Socket option helpers and
// wait helpers.
// Objects: UTFSpore_Win32/manager1.obj (0094cac0..0094cd60),
//          an unattributed template/COMDAT cluster (0094cdb0..0094d2f0),
//          UTFSpore_Win32/Socket_imp.obj (0094d300..0094db60).
// Module flags: /O2 /MD /Gy /TP /GS-
#include "game/types.h"
#include "EA/Sockets/Manager.h"
#include <string.h>
#include <new>

// ===========================================================================
// Windows / wsock32 imports
// ===========================================================================
extern "C" {
__declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);       // kernel32
__declspec(dllimport) void* __stdcall GetProcAddress(void* mod, const char* name); // kernel32
__declspec(dllimport) void* __stdcall GlobalAlloc(unsigned int flags, unsigned int bytes);   // kernel32
__declspec(dllimport) void* __stdcall GlobalFree(void* hMem);              // kernel32
__declspec(dllimport) unsigned long __stdcall FreeLibrary(void* mod);      // kernel32
__declspec(dllimport) char* __cdecl strncpy(char* d, const char* s, unsigned int n);  // msvcr90
__declspec(dllimport) int   __cdecl tolower(int c);                        // msvcr90
__declspec(dllimport) long long __cdecl _time64(long long* timer);         // msvcr90

__declspec(dllimport) int __stdcall WSAGetLastError(void);                 // wsock32
__declspec(dllimport) int __stdcall WSACleanup(void);                      // wsock32
__declspec(dllimport) int __stdcall closesocket(unsigned s);               // wsock32
__declspec(dllimport) int __stdcall shutdown(unsigned s, int how);         // wsock32
__declspec(dllimport) int __stdcall ioctlsocket(unsigned s, long cmd, unsigned long* argp);  // wsock32
__declspec(dllimport) int __stdcall select(int nfds, void* rd, void* wr, void* ex, void* to);
__declspec(dllimport) int __stdcall setsockopt(unsigned s, int level, int optname, const char* optval, int optlen);
__declspec(dllimport) int __stdcall getsockopt(unsigned s, int level, int optname, char* optval, int* optlen);
__declspec(dllimport) int __stdcall getpeername(unsigned s, void* name, int* namelen);
__declspec(dllimport) unsigned __stdcall socket(int af, int type, int protocol);  // wsock32
__declspec(dllimport) int __stdcall bind(unsigned s, const char* name, int namelen);  // wsock32
}

void __cdecl operator_delete__(void* p);                                   // 0x00f47380
void* __cdecl EAAllocate(unsigned int size, const char* pName, int a, int b, const char* file, int line); // 0x00f473a0
extern const char DAT_013f2150[];   // "EASTL"
extern const char DAT_013ebb38[];   // allocator.h source path

// ===========================================================================
// manager1.obj
// ===========================================================================
static EA::Sockets::Manager* spManagerForDial;   // 0x0166aa78

typedef unsigned int (__stdcall* RasEnumConnections_t)(void*, unsigned int*, unsigned int*);
typedef unsigned int (__stdcall* RasGetProjectionInfo_t)(void*, unsigned int, void*, unsigned int*);
typedef unsigned int (__stdcall* RasHangUp_t)(void*);
typedef unsigned int (__stdcall* RasEnumEntries_t)(const char*, const char*, void*, unsigned int*, unsigned int*);

// @ 0x0094cac0
bool EA::Sockets::Manager::CloseManualDialup()
{
    // 0x387c bytes of RASCONN[] scratch (0x3840) plus the RASPROJECTION and
    // HRASCONN result slots.
    char connBuf[0x387c];

    if (mRASData.mpRasEnumConnections == 0 || mRASData.mpRasHangUp == 0)
        return false;

    unsigned int nBuf = 0x3840;       // byte size handed in
    unsigned int nConn = 0x14;        // capacity in entries
    if (((RasEnumConnections_t)mRASData.mpRasEnumConnections)(connBuf, &nBuf, &nConn) != 0)
        return false;

    for (unsigned int i = 0; i < nConn; ++i) {
        char* entry = connBuf + i * 0x2d0;
        unsigned int sz = 0x30;       // sizeof(RASPROJECTION)
        unsigned int info = 0x8021;   // RASPROJECTION type -> overwritten below
        (void)info;
        unsigned int r = ((RasGetProjectionInfo_t)mRASData.mpRasGetProjectionInfo)(
            *(void**)entry, 0x8021, &nBuf, &sz);
        if (r != 0 || nBuf != 0 || *(void**)entry == 0)
            continue;
        if (((RasHangUp_t)mRASData.mpRasHangUp)(*(void**)entry) != 0)
            continue;
        long long t = _time64(0) + 3;
        long long now;
        do { now = _time64(0); } while (now < t);
        if (*(void**)(connBuf + i * 0x2d0) == mRASData.mhRASConn)
            mRASData.mhRASConn = 0;
        return true;
    }
    return false;
}

// @ 0x0094cc00
bool EA::Sockets::Manager::GetDialupEntries(char (*const entries)[32], unsigned int& count)
{
    unsigned int n = count;
    for (unsigned int i = 0; i < n; ++i)
        entries[i][0] = 0;

    unsigned int numEntries = 0;
    if (mRASData.mpRasEnumEntries == 0) {
        count = 0;
        return false;
    }

    unsigned int cb = 0x214;
    void* buf = GlobalAlloc(0x40, 0x214);
    if (buf == 0) {
        count = numEntries;
        return false;
    }
    *(unsigned int*)buf = 0x214;
    unsigned int r = ((RasEnumEntries_t)mRASData.mpRasEnumEntries)(0, 0, buf, &cb, &numEntries);
    if (r == 0x25b) {
        GlobalFree(buf);
        buf = GlobalAlloc(0x40, cb);
        *(unsigned int*)buf = 0x214;
    }
    r = ((RasEnumEntries_t)mRASData.mpRasEnumEntries)(0, 0, buf, &cb, &numEntries);
    bool ok;
    if (r == 0) {
        char* src = (char*)buf + 4;
        for (unsigned int i = 0; i < cb; ++i, src += 0x214) {
            if (i >= count)
                break;
            strncpy(entries[i], src, 0x20);
            numEntries++;
            entries[i][31] = 0;
        }
        ok = true;
    } else {
        ok = false;
    }
    GlobalFree(buf);
    count = numEntries;
    return ok;
}

// @ 0x0094cd60
EA::Sockets::Manager::~Manager()
{
    if (mRASData.mhRASAPI32 != 0)
        FreeLibrary((void*)mRASData.mhRASAPI32);
    if (mbInitialized) {
        mbInitialized = false;
        if (WSACleanup() != 0)
            mnLastError = WSAGetLastError();
    }
}

// ===========================================================================
// unattributed string-keyed layout cache (COMDAT cluster 0094cdb0..0094d2f0)
//   +0x00 int     (0)
//   +0x04 int     (10000)
//   +0x08 int     (1800000)
//   +0x0c rbtree anchor (left,right,parent), size/count at +0x18
//   +0x1c byte
//   +0x20 int
//   +0x28 EA::Thread::Mutex
// ===========================================================================
struct CacheNode {
    CacheNode* left;      // +0x00
    CacheNode* right;     // +0x04
    CacheNode* parent;    // +0x08
    char*      str;       // +0x10  (key: string begin)
    char*      strEnd;    // +0x14
    unsigned   value;     // +0x20
    unsigned   deadline;  // +0x24
};

struct MutexLike {
    void Lock(unsigned id);                         // 0x9221b0
    void Unlock();                                  // 0x922270
    MutexLike(const void* name, bool recursive);    // 0x9222a0
    ~MutexLike();                                   // 0x922130
};

struct LayoutCache {
    int        m0;               // +0x00
    unsigned   mDefaultTimeout;  // +0x04
    unsigned   mSetTimeout;      // +0x08
    unsigned   mC0c;             // +0x0c
    void*      m10;              // +0x10
    void*      m14;              // +0x14
    unsigned   mCount;           // +0x18
    unsigned char b1c;           // +0x1c
    unsigned   m20;              // +0x20
    unsigned   m24;              // +0x24
    MutexLike  mMutex;           // +0x28

    void  FindInsert(void** out, void* key, unsigned value, unsigned timeout);     // 0x0094ce40
    void  Dtor();                                                                  // 0x0094cf40
    bool  SetEntry(const char* name, unsigned value, unsigned timeout);            // 0x0094cf60
    CacheNode* Find(const char* name);                                             // 0x0094d0e0
    void* Ctor();                                                                  // 0x0094d230
    void  Erase(const char* name);                                                 // 0x0094d270
};

// external EASTL / Spore string-map helpers (real addresses in comments)
bool __cdecl FUN_00812210(void* keyA, void* keyB);          // 0x00812210  VecView less-than
void* __cdecl eastl_RBTreeDecrement(void* node);             // 0x009215c0
void* __cdecl eastl_RBTreeIncrement_(void* node);            // 0x00921580
int   __cdecl eastl_Compare_(void* a, void* b, int n);       // 0x005f7870
void  __cdecl RBTreeInsert(void* node, void* hint, void* anchor, int side);  // 0x009216a0
void  __cdecl RBTree1_eraseSys(void** out, void* node);      // 0x00812310
void  __cdecl FUN_00e84850(void* key);                       // 0x00e84850  rbtree node-value ctor
void* __cdecl FUN_00e847f0_(void* a, void* b);               // 0x00e847f0
void  __cdecl MapStrFind_Find(void** out, void* key);        // 0x00b20930
struct NukeHelper { void __thiscall Do(void* node); };          // 0x00e84940
#define LayoutMap_DoNukeSubtree(h, n) ((NukeHelper*)(h))->Do(n)
void  __cdecl eastl_DoInsertValue(void* dst, const char* src, unsigned n);  // 0x011e0744
void* __cdecl EAThread_GetThreadTime();                      // 0x0094d340
void* __cdecl operator_new(unsigned size);                   // 0x00f473a0
void* __cdecl FUN_0094cdb0(void** out, void* hint, void* key, unsigned char right);  // 0x0094cdb0 (other object)
extern char g_eastlEmptyString[];                            // 0x01667bac

// @ 0x0094ce40
void LayoutCache::FindInsert(void** out, void* key, unsigned value, unsigned timeout)
{
    CacheNode* last = 0;
    unsigned char less = 1;
    CacheNode* node = *(CacheNode**)((char*)this + 0x0c);
    unsigned kl = ((unsigned*)key)[1] - ((unsigned*)key)[0];
    if (node != 0) {
        do {
            last = node;
            unsigned nl = *(unsigned*)((char*)node + 0x14) - *(unsigned*)((char*)node + 0x10);
            unsigned len = kl <= nl ? kl : nl;
            int r = eastl_Compare_((void*)(unsigned)((unsigned*)key)[0],
                                   *(void**)((char*)node + 0x10), (int)len);
            if (r == 0)
                r = (kl < nl) ? -1 : (int)(nl < kl);
            less = (r < 0);
            node = less ? *(CacheNode**)((char*)node + 0x04) : *(CacheNode**)node;
        } while (node != 0);
    }
    CacheNode* cand = last;
    bool useUpper = false;
    if (less) {
        if (last == *(CacheNode**)((char*)this + 0x08)) {
            useUpper = true;
        } else {
            cand = (CacheNode*)eastl_RBTreeDecrement(last);
        }
    }
    if (!useUpper) {
        if (!FUN_00812210((char*)cand + 0x10, (void*)key)) {
            *out = cand;
            *((unsigned char*)out + 4) = 0;
            return;
        }
    }
    FUN_0094cdb0(out, cand, key, 0);
    *((unsigned char*)out + 4) = 1;
}

// @ 0x0094cf40
void LayoutCache::Dtor()
{
    mMutex.~MutexLike();
    NukeHelper* h = (NukeHelper*)((char*)this + 0xc);
    h->Do(*(void**)((char*)this + 0x18));
}

// @ 0x0094cf60
bool LayoutCache::SetEntry(const char* name, unsigned value, unsigned timeout)
{
    mMutex.Lock(0x143f9c4);
    if (timeout == 0)
        timeout = *(unsigned*)((char*)this + 0x08);
    unsigned deadline = timeout + (unsigned)EAThread_GetThreadTime();

    const char* e = name;
    while (*e) ++e;
    unsigned len = (unsigned)(e - name);

    char* dst;
    if (len + 1 < 2) {
        dst = g_eastlEmptyString;
    } else {
        dst = (char*)operator_new(len + 1);
    }
    eastl_DoInsertValue(dst, name, len);
    char* mid = dst + (e - name);
    *mid = 0;

    for (char* p = dst; p < mid; ++p)
        *p = (char)tolower((unsigned char)*p);

    void* it = 0;
    MapStrFind_Find(&it, dst);
    if (it == (void*)((char*)this + 0x10)) {
        unsigned* pair = (unsigned*)FUN_00e847f0_(&value, &it);
        FindInsert((void**)((char*)this + 0x0c), pair, value, deadline);
    } else {
        *(unsigned*)((char*)it + 0x20) = value;
        *(unsigned*)((char*)it + 0x24) = deadline;
    }
    mMutex.Unlock();
    return true;
}

// @ 0x0094d0e0
CacheNode* LayoutCache::Find(const char* name)
{
    mMutex.Lock(0x143f9c4);
    const char* e = name;
    while (*e) ++e;
    unsigned len = (unsigned)(e - name);

    char* dst;
    if (len + 1 < 2) {
        dst = g_eastlEmptyString;
    } else {
        dst = (char*)operator_new(len + 1);
    }
    eastl_DoInsertValue(dst, name, len);
    char* mid = dst + (e - name);
    *mid = 0;
    for (char* p = dst; p < mid; ++p)
        *p = (char)tolower((unsigned char)*p);

    void* it = 0;
    MapStrFind_Find(&it, dst);
    if (it == (void*)((char*)this + 0x10))
        goto notFound;

    if ((unsigned)EAThread_GetThreadTime() < *(unsigned*)((char*)it + 0x24)) {
        mMutex.Unlock();
        return (CacheNode*)((char*)it + 0x20);
    }
    RBTree1_eraseSys(&it, it);
notFound:
    mMutex.Unlock();
    return 0;
}

// @ 0x0094d230
void* LayoutCache::Ctor()
{
    char* s = (char*)this;
    *(int*)(s + 0x00) = 0;
    *(unsigned*)(s + 0x04) = 0x2710;
    *(unsigned*)(s + 0x08) = 0x1b7740;
    *(void**)(s + 0x10) = s + 0x10;
    *(void**)(s + 0x14) = s + 0x10;
    *(int*)(s + 0x18) = 0;
    *(unsigned char*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(void**)(s + 0x0c) = s + 0x10;
    MutexLike* m = new ((void*)(s + 0x28)) MutexLike(0, true);
    (void)m;
    return s;
}

// @ 0x0094d270
void LayoutCache::Erase(const char* name)
{
    mMutex.Lock(0x143f9c4);
    const char* e = name;
    while (*e) ++e;
    unsigned len = (unsigned)(e - name);

    char* dst;
    if (len + 1 < 2) {
        dst = g_eastlEmptyString;
    } else {
        dst = (char*)operator_new(len + 1);
    }
    eastl_DoInsertValue(dst, name, len);
    char* mid = dst + (e - name);
    *mid = 0;
    for (char* p = dst; p < mid; ++p)
        *p = (char)tolower((unsigned char)*p);

    void* it = 0;
    MapStrFind_Find(&it, dst);
    if (it != (void*)((char*)this + 0x10))
        RBTree1_eraseSys(&it, it);
    mMutex.Unlock();
}

// @ 0x0094d2f0
void __fastcall Fn0094d2f0(void** self)
{
    void (__thiscall* f)(void*) = *(void(__thiscall**)(void*))((char*)*self + 0x2c);
    f(self + 2);
}

// ===========================================================================
// Socket_imp.obj -- EA::Sockets::Socket / ISocket helpers
//
// These methods are reached with `ecx` = the ISocket sub-object at obj+8; the
// owning Socket's vptr is at [ecx-8] and slot 1 is DoError(int). The socket
// handle lives at [ecx+4].
// ===========================================================================
struct Address {
    unsigned short sa_family;    // +0x00
    char           sa_data[26];  // +0x02
};                               // size 0x1c

struct Error {
    int  mErrorType;             // +0x00
    char mErrorString[32];       // +0x04
};                               // size 0x24

struct Owner {                   // the owning Socket seen from -8
    virtual void o00();
    virtual void DoError(int err);          // slot 1 (+0x4)
};

#define REPORT_ERROR(self)                                                    \
    do {                                                                     \
        void** vt_ = *(void***)((char*)(self) - 8);                           \
        ((void(__thiscall**)(void*, int))vt_)[1]((char*)(self) - 8,           \
            ((int(__stdcall*)(int))WSAGetLastError)(0));                     \
    } while (0)

struct Socket {
    char           mPad00[4];    // -0x08 owner vptr lives one object earlier
    char           mPad04[4];    // +0x00
    unsigned       hSocket;      // +0x04 (socket handle) ... reached as ecx+4
    unsigned short mFamily;      // +0x08 (7 dwords copied by SetAddressRaw)
    unsigned char  mPad75;       // +0x75
    unsigned char  mPad77;       // +0x77

    void Destroy2();                                        // 0x0094d300
    unsigned QueryInterface(int iid);                       // 0x0094d360
    bool Create();                                          // 0x0094d3c0
    bool Bind(const void* addr);                            // 0x0094d410
    bool Fn0094d470(int how);                               // 0x0094d470
    __declspec(noinline) bool Fn0094d4b0();                // 0x0094d4b0
    bool SetLingerRaw(int a, int b, int c);                 // 0x0094d500
    bool SetAddressRaw(const void* a);                      // 0x0094d520
    bool GetPeerNameRaw(void* addr, unsigned* len);         // 0x0094d550
    bool SetPeerAddressRaw(const void* a);                  // 0x0094d5a0
    int  GetWaitingDataSize(unsigned timeout);              // 0x0094d5c0
    bool WaitReadable(unsigned timeout);                    // 0x0094d690
    bool WaitWritable(unsigned timeout);                    // 0x0094d730
    unsigned WaitMulti(unsigned mode, unsigned timeout);    // 0x0094d7d0
    bool SetOptInt(unsigned char v);                       // 0x0094d960
    bool SetOptInt2(unsigned char v);                      // 0x0094da20
    bool GetOptInt(unsigned char* out, unsigned* val);     // 0x0094da70
    bool SetLingerOpt(unsigned char on, unsigned short level); // 0x0094daf0
    bool GetNonBlocking(unsigned char* out);                // 0x0094db50
    bool SetNonBlockingOption(unsigned char b);             // 0x0094db60
private:
    void ReportError(char scratch) {                        // edx = [self-8], eax = WSAGetLastError()
        void** vt = *(void***)((char*)this - 8);
        int ec = ((int(__stdcall*)(int))WSAGetLastError)(0);
        (void)scratch;
        ((void(__thiscall*)(void*, int))vt[1])((char*)this - 8, ec);
    }
    void SetOpt(uint32_t optname, int value) {              // edx/ecx = hSocket
        unsigned h = *(unsigned*)((char*)this + 4);
        int r = setsockopt(h, 0xffff, (int)optname, (const char*)&value, 4);
        (void)h;
        if (r != 0) {
            ReportError(0);
        }
    }
};

static inline Owner* OwnerOf(Socket* s) { return (Owner*)s; }

struct TimeVal { long tv_sec; long tv_usec; };
struct FdSet  { unsigned fd_count; unsigned fd_array[64]; };

// @ 0x0094d300
void Socket::Destroy2()
{
    *(void**)((char*)this + 0x7c) = 0;
    Fn0094d4b0();
}

// @ 0x0094d310
void __fastcall Socket_ForwardError(char* self, void* edx, int a, int b)
{
    Owner* owner = *(Owner**)(self - 0x78);
    (*(void(__thiscall**)(void*, int))((char*)owner + 0x54))(owner, a);
    (*(void(__thiscall**)(char*, int, int))((char*)*(void**)self + 0x28))(self, a, b);
}

// @ 0x0094d350
void __cdecl Socket_CloseRaw(unsigned s)
{
    closesocket(s);
}

// @ 0x0094d360
unsigned Socket::QueryInterface(int iid)
{
    if (iid == 0x23e12220)
        return ((unsigned)this - 8) ? (unsigned)this : 0;
    if (iid == 0x23e12230)
        return (unsigned)this - 8;
    if (iid == 0xee3f516e)
        return ((unsigned)this - 8) ? (unsigned)this : 0;
    return 0;
}

// @ 0x0094d3c0
bool Socket::Create()
{
    if ((*(unsigned char(__thiscall**)(void*))((char*)*(void**)this + 0x20))(this) == 0) {
        unsigned h = socket(*(int*)((char*)this + 0x40), *(int*)((char*)this + 0x44),
                            *(int*)((char*)this + 0x48));
        *(unsigned*)((char*)this + 4) = h;
        if (h == 0xffffffffu) {
            REPORT_ERROR(this);
            return false;
        }
        return true;
    }
    return false;
}

// @ 0x0094d410
bool Socket::Bind(const void* addr)
{
    memcpy((char*)this + 8, (const char*)addr, 7 * 4);
    if (bind(*(unsigned*)((char*)this + 4), (const char*)this + 8, 0x10) != 0) {
        *(unsigned char*)((char*)this + 0x75) = 0;
        REPORT_ERROR(this);
        return false;
    }
    *(unsigned char*)((char*)this + 0x75) = 1;
    return true;
}

// @ 0x0094d470
bool Socket::Fn0094d470(int how)
{
    unsigned h = *(unsigned*)((char*)this + 4);
    if (h != 0xffffffffu) {
        if (shutdown(h, how) != 0) {
            REPORT_ERROR(this);
            return false;
        }
    }
    return true;
}

// @ 0x0094d4b0
bool Socket::Fn0094d4b0()
{
    unsigned h = *(unsigned*)((char*)this + 4);
    *(unsigned char*)((char*)this + 0x75) = 0;
    if (h != 0xffffffffu) {
        int r = closesocket(h);
        *(unsigned*)((char*)this + 4) = 0xffffffffu;
        if (r != 0) {
            REPORT_ERROR(this);
            return false;
        }
    }
    return true;
}

// @ 0x0094d500
bool Socket::SetLingerRaw(int a, int b, int c)
{
    *(int*)((char*)this + 0x48) = c;
    *(int*)((char*)this + 0x44) = b;
    *(int*)((char*)this + 0x40) = a;
    return true;
}


// @ 0x0094d520
bool Socket::SetAddressRaw(const void* a)
{
    if (*(unsigned char*)((char*)this + 0x75) == 0) {
        memcpy((char*)this + 8, (const char*)a, 7 * 4);
        return true;
    }
    return false;
}

// @ 0x0094d550
bool Socket::GetPeerNameRaw(void* addr, unsigned* len)
{
    int local = 0x1c;
    unsigned h = *(unsigned*)((char*)this + 4);
    if (getpeername(h, addr, &local) != 0) {
        REPORT_ERROR(this);
        return false;
    }
    if (len) *len = (unsigned)local;
    return true;
}

// @ 0x0094d5a0
bool Socket::SetPeerAddressRaw(const void* a)
{
    memcpy((char*)this + 0x24, (const char*)a, 7 * 4);
    return true;
}

// @ 0x0094d5c0
int Socket::GetWaitingDataSize(unsigned timeout)
{
    unsigned long avail = 0xffffffffu;
    unsigned h = *(unsigned*)((char*)this + 4);

    if (timeout != 0) {
        TimeVal tv;
        TimeVal* ptv = 0;
        if (timeout != 0xffffffffu) {
            tv.tv_sec  = timeout / 1000;
            tv.tv_usec = (timeout % 1000) * 1000;
            ptv = &tv;
        }
        FdSet rd;
        rd.fd_count = 1;
        rd.fd_array[0] = h;
        int r = select(1, &rd, 0, 0, ptv);
        if (r == -1) {
            REPORT_ERROR(this);
            return -1;
        }
        if (r == 0)
            return 0;
    }
    if (ioctlsocket(h, 0x4004667f, &avail) != 0) {
        avail = 0;
        REPORT_ERROR(this);
        return -1;
    }
    return (int)avail;
}

// @ 0x0094d690
bool Socket::WaitReadable(unsigned timeout)
{
    TimeVal tv;
    TimeVal* ptv = 0;
    if (timeout != 0xffffffffu) {
        tv.tv_sec  = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
        ptv = &tv;
    }
    FdSet rd;
    rd.fd_count = 1;
    rd.fd_array[0] = *(unsigned*)((char*)this + 4);
    int r = select(1, &rd, 0, 0, ptv);
    if (r == -1) {
        REPORT_ERROR(this);
        return false;
    }
    return (bool)(r != 0);
}

// @ 0x0094d730
bool Socket::WaitWritable(unsigned timeout)
{
    TimeVal tv;
    TimeVal* ptv = 0;
    if (timeout != 0xffffffffu) {
        tv.tv_sec  = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
        ptv = &tv;
    }
    FdSet wr;
    wr.fd_count = 1;
    wr.fd_array[0] = *(unsigned*)((char*)this + 4);
    int r = select(1, 0, &wr, 0, ptv);
    if (r == -1) {
        REPORT_ERROR(this);
        return false;
    }
    return (bool)(r != 0);
}

// @ 0x0094d7d0
unsigned Socket::WaitMulti(unsigned mode, unsigned timeout)
{
    TimeVal tv;
    TimeVal* ptv = 0;
    if (timeout != 0xffffffffu) {
        tv.tv_sec  = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
        ptv = &tv;
    }
    FdSet rd;
    rd.fd_count = 0;
    if (mode & 1) {
        rd.fd_count = 1;
        rd.fd_array[0] = *(unsigned*)((char*)this + 4);
    }
    FdSet wr;
    wr.fd_count = 0;
    if (mode & 2) {
        wr.fd_count = 1;
        wr.fd_array[0] = *(unsigned*)((char*)this + 4);
    }
    int r = select(1, (mode & 1) ? &rd : 0, (mode & 2) ? &wr : 0, 0, ptv);
    if (r == -1) {
        REPORT_ERROR(this);
        return 0x80;
    }
    unsigned result = 0;
    if (select(1, &rd, 0, 0, ptv) != 0) result |= 1;
    if (select(1, 0, &wr, 0, ptv) != 0) result |= 2;
    return result;
}

// @ 0x0094d960
bool Socket::SetOptInt(unsigned char v)
{
    SetOpt(0x20, v);
    return true;
}

// @ 0x0094da20
bool Socket::SetOptInt2(unsigned char v)
{
    SetOpt(1, v);
    return true;
}

// @ 0x0094da70
bool Socket::GetOptInt(unsigned char* out, unsigned* val)
{
    struct { unsigned short on; unsigned short sec; } opts;
    opts.on = 0;
    opts.sec = 0;
    unsigned h = *(unsigned*)((char*)this + 4);
    int len = 4;
    if (getsockopt(h, 0xffff, 0x80, (char*)&opts, &len) != 0) {
        REPORT_ERROR(this);
        return false;
    }
    *out = (opts.on != 0);
    *val = opts.sec;
    return true;
}

// @ 0x0094daf0
bool Socket::SetLingerOpt(unsigned char on, unsigned short level)
{
    struct { unsigned short on; unsigned short sec; } opts;
    opts.on = (unsigned short)(on != 0);
    opts.sec = level;
    unsigned h = *(unsigned*)((char*)this + 4);
    int r = setsockopt(h, 0xffff, 0x80, (const char*)&opts, 4);
    (void)h;
    if (r != 0) {
        ReportError(0);
        return false;
    }
    return true;
}

// @ 0x0094db50
bool Socket::GetNonBlocking(unsigned char* out)
{
    *out = *(unsigned char*)((char*)this + 0x77);
    return true;
}

// @ 0x0094db60
bool Socket::SetNonBlockingOption(unsigned char b)
{
    unsigned long value = (unsigned long)(b != 0);
    unsigned h = *(unsigned*)((char*)this + 4);
    int r = ioctlsocket(h, 0x8004667e, &value);
    (void)h;
    if (r != 0) {
        REPORT_ERROR(this);
        return false;
    }
    *(unsigned char*)((char*)this + 0x77) = b;
    return true;
}
