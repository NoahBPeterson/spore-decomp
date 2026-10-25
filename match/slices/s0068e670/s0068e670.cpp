// Slice s0068e670: Simulator/EA job-lock, thread-mutex and small utility helpers
// (0x0068e670..0x0068f600). Module compiled /O2 /MD /Gy /EHsc /TP (no SSE).
#include "types.h"
#include <intrin.h>
#include <string.h>

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void* MemcpyT(void*, const void*, uint32_t);           // 0x011e0744
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];
extern "C" char  g_fileEASTL[];
extern "C" char __cdecl ReadInt32(void*, void*, int, int);        // 0x093a780
extern "C" void* __cdecl MutexLock(void* self, void* name);       // 0x09221b0
extern "C" void* __cdecl MutexUnlock(void* self);                 // 0x0922270
extern "C" void  __cdecl HandleClose(void* h);                    // 0x0922610
extern "C" void* __cdecl SemaphorePost(void* self, int n);        // 0x0922740

// ---- global job-lock singleton accessors / callees (out-of-slice) ----
extern "C" int* __cdecl GetStatus(void* p);                       // 0x0690120
extern "C" void* __cdecl FUN_0068f950(void* p);                   // 0x068f950
extern "C" void* __cdecl FUN_006913c0(void* p);                   // 0x06913c0
extern "C" int*  __cdecl FUN_0068f4d0();                          // 0x068f4d0
extern "C" void* __cdecl FUN_0068f9f0(void* p, void* fn, void* a); // 0x068f9f0
extern "C" void* __cdecl FUN_0068f9b0(void* p);                   // 0x068f9b0
extern "C" void  __cdecl FUN_00753fb0(void* p);                   // 0x0753fb0

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// ---- out-of-slice callees / globals (relocation-masked) ----
extern "C" u32 __cdecl CRC32(const void* data, u32 n, u32 seed, int flag);      // 0x0932da0
extern "C" u64 __cdecl CRC64(const void* data, u32 n, u32 lo, u32 hi, u32 x);   // 0x0932df0

extern "C" u32 gFmtTag;        // 0x140369c  "spOr" serialised-stream id
extern "C" u8  gMagicA[];      // 0x14036a0
extern "C" u8  gMagicB[];      // 0x14036a8
extern "C" u32 gTailTag;       // 0x14036b4
extern "C" u32 gHNMagic;       // 0x152ca8c  CRC32 name-hash seed

// non-target member of the job-lock helper class (still referenced below)
namespace EA { namespace Thread {
struct Mutex {
    uint32_t _[12];
    void Lock(unsigned int nameId);   // ?Lock@Mutex@Thread@EA@@QAEXI@Z   0x09221b0
    void Unlock();                    // ?Unlock@Mutex@Thread@EA@@QAEXXZ 0x0922270
};
}}
typedef EA::Thread::Mutex Mutex;

// =====================================================================
// eastl byte vector (begin/end/capacity)
// =====================================================================
struct VecU8 {
    u8* mpBegin;                                                             // +0x00
    u8* mpEnd;                                                               // +0x04
    u8* mpCap;                                                               // +0x08

    u32 size() const { return (u32)(mpEnd - mpBegin); }

    u8* erase(u8* first, u8* last) {
        MemcpyT(first, last, (u32)(mpEnd - last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }

    void DoInsertValues(u8* pos, u32 n, const void* value);                  // 0x004c10e0
    void resize(u32 n);                                                      // 0x004c0410
    void eraseAll();                                                         // 0x00631dc0

    void AssignFill(u32 count, const void* pval);
};

// =====================================================================
// EA::IO reader interface (only vtable slot offsets matter)
// =====================================================================
struct IReader {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual char Seek(int offset, int whence);                               // +0x28
    virtual void v11();
    virtual int  Read(void* dst, int n);                                     // +0x30
};

// =====================================================================
// image / serialised stream entry + reader object used by OpenData
// =====================================================================
struct Entry {
    u32 type;                                                                // +0x00
    u32 pad04[3];                                                            // +0x04
    u32 width;                                                               // +0x10
    u32 height;                                                              // +0x14
    u32 bits;                                                                // +0x18
    u8  pad1c[0x438 - 0x1c];
    u32 f438;                                                                // +0x438
};

struct Hinter {
    u32 mRaw[5];
    Hinter();                                                                // 0x87cde0
    ~Hinter();                                                               // 0x87d070
    void   Open(const char* path);                                           // 0x87ce00
    char   GetFrame(int kind, u32* out);                                     // 0x87d0b0
    Entry* GetEntry(int idx);                                                // 0x87ced0
    char   Read(Entry* e, void* dst, int n);                                 // 0x87cf00
    void   Free(Entry* e);                                                   // 0x87cef0
};

// =====================================================================
// the range-coder object these helpers belong to
// =====================================================================
struct Coder {
    VecU8 mData;                                                             // +0x00
    u32 f0c;                                                                 // +0x0c
    u32 f10;                                                                 // +0x10
    u32 mWidth;                                                              // +0x14
    u32 mHeight;                                                             // +0x18
    u32 mStride;                                                             // +0x1c
    u8  mFlag;                                                               // +0x20
    u8  pad20[3];
    u32 mState;                                                              // +0x24
    u32 mHashLo;                                                             // +0x28
    u32 mHashHi;                                                             // +0x2c
    u32 f30;                                                                 // +0x30
    u32 f34;                                                                 // +0x34
    u32 f38;                                                                 // +0x38
    u32 f3c;                                                                 // +0x3c
    u32 f40;                                                                 // +0x40
    u32 f44;                                                                 // +0x44
    u32 f48;                                                                 // +0x48
    u32 f4c;                                                                 // +0x4c
    u32 f50;                                                                 // +0x50
    u8  pad54;                                                               // +0x54
    u8  f55;                                                                 // +0x55
    u8  f56;                                                                 // +0x56
    u8  pad57;
    VecU8 mStream;                                                           // +0x58
    u32 f64;                                                                 // +0x64
    u32 f68;                                                                 // +0x68
    u32 f6c;                                                                 // +0x6c

    void InitMask();                                                         // 0x068ddc0
    char EncodeBit(u8 b);                                                    // 0x068de20
    void Flush();                                                            // 0x068df00
    int  Read(void* dst, u32 n);                                             // 0x068e3b0

    char ReadHeader(int* out);
    int  InitBitmap(int width, int height, int bits, u8 flag);
    char ReadData(void* io);
    char OpenData(const char* path);
    char WriteData(const u8* data, u32 n);
    char Finalize(char flag);
    char Begin(char external);
};

// =====================================================================
// 0x0068eff0  refcounted base + threaded mutex holder used by the job system
// =====================================================================
struct ThreadMutex {
    u32 mRaw[12];                                                            // 0x30 bytes
    ThreadMutex(const void* name, bool b);                                   // 0x09222a0
    ~ThreadMutex();                                                          // 0x0922130
};

struct GmeRefCount {
    volatile long mRef;                                                      // +0x04 (vptr at +0x00 is implicit)
    GmeRefCount() { volatile long* pRef = &mRef; _InterlockedExchange(pRef, 0); }
    virtual ~GmeRefCount() {}
};

struct CJob {
    int Release();                                                           // 0x0690120
};

struct RefObj : GmeRefCount {
    ThreadMutex mMutex;                                                      // +0x08
    void* mJob;                                                              // +0x38
    RefObj();
    virtual ~RefObj();
};

// =====================================================================
// read the serialised-stream / range-coder header
// =====================================================================
// @ 0x0068e670
char Coder::ReadHeader(int* out) {
    u32 hdr[2];
    if (f55 != 0) {
        f56 = 0;
        if (mState != 1) return 0;
        if (mData.mpBegin == mData.mpEnd) return 0;
        const u8* p = mStream.mpBegin;
        bool a = (memcmp(p, gMagicA, 8) == 0);
        bool b = (memcmp(p, gMagicB, 8) == 0);
        u32 n = (u32)(mStream.mpEnd - mStream.mpBegin);
        if (n < 0x10 || (!a && !b)) { mState = 1; return 0; }
        f6c = 8;
        if (out) *out = (int)(n - 0x10);
        if (b) return 1;
        u32 m = n - 0x14;
        if (m == 0) return 0;
        if (out) *out = (int)m;
        f56 = 1;
        return 1;
    }
    if (mState != 1) return 0;
    if (mData.mpBegin == mData.mpEnd) return 0;
    if ((u32)(mData.mpEnd - mData.mpBegin) != f40) return 0;
    InitMask();
    f34 = 0xffffffff;
    mState = 3;
    if (Read(hdr, 8) == 0) { mState = 1; return 0; }
    if (hdr[0] != 0x02450d16) {
        InitMask();
        f48 = ~f44;
        f34 = 0xffffffff;
        mState = 3;
        if (Read(hdr, 8) == 0) { mState = 1; return 0; }
        if (hdr[0] != 0x02450d16) { mState = 1; return 0; }
    }
    f34 = hdr[1];
    f38 = 0;
    mHashLo = 0xffffffff;
    mHashHi = 0xffffffff;
    if (out) *out = (int)hdr[1];
    return 1;
}

// =====================================================================
// grow-or-shrink fill (eastl vector assign(count, value))
// =====================================================================
// @ 0x0068e8a0
void VecU8::AssignFill(u32 count, const void* pval) {
    u8* e = mpEnd;
    if (count > (u32)(e - mpBegin)) {
        DoInsertValues(e, (u32)(mpBegin - e) + count, pval);
        return;
    }
    erase(mpBegin + count, mpEnd);
}

// =====================================================================
// bitmap allocation / reset
// =====================================================================
// @ 0x0068e8f0
int Coder::InitBitmap(int width, int height, int bits, u8 flag) {
    mStride = (u32)(bits / 8);
    u32 total = mStride * (u32)width * (u32)height;
    mHeight = (u32)height;
    mData.clear();
    mWidth = (u32)width;
    mFlag = flag;
    if (total > mData.size()) {
        u8 zero = 0;
        mData.DoInsertValues(mData.mpEnd, (u32)(mData.mpBegin - mData.mpEnd) + total, &zero);
    } else {
        mData.erase(mData.mpBegin + total, mData.mpEnd);
    }
    f40 = total;
    mState = 1;
    return (int)mData.mpBegin;
}

// =====================================================================
// read a serialised range-coded stream back out of a file
// =====================================================================
// @ 0x0068e9a0
char Coder::ReadData(void* io) {
    mStream.clear();
    if (!io) return 0;
    IReader* r = (IReader*)io;
    u32 hdr[2];
    u32 crcStored;
    u32 size;
    u32 magic;
    if (!r->Seek(-0xc, 2)) return 0;
    if (r->Read(hdr, 8) != 8) return 0;
    if (hdr[1] != 0xe6adc7ce && hdr[1] != 0xe6f1a35c) return 0;
    if (hdr[0] == 0) return 0;
    if (!ReadInt32(r, &crcStored, 1, 0)) return 0;
    if (!r->Seek(-(int)(hdr[0] + 0x1c), 2)) return 0;
    if (!ReadInt32(r, &size, 1, 0)) return 0;
    if (size != hdr[0] + 0x10) return 0;
    if (r->Read(&magic, 4) != 4) return 0;
    if (magic != gFmtTag) return 0;
    mStream.resize(size);
    if ((u32)r->Read(mStream.mpBegin, (int)size) != size) goto erase_fail;
    {
        u32* p = (u32*)mStream.mpBegin;
        u32* tail = (u32*)(mStream.mpEnd - 8);
        if (p[0] != 0xe6adc7ce && p[0] != 0xe6f1a35c) goto erase_fail;
        if (p[1] != 0) goto erase_fail;
        if (tail[0] != hdr[0]) goto erase_fail;
        if (tail[1] != 0xe6adc7ce && tail[1] != 0xe6f1a35c) goto erase_fail;
        u32 crc = CRC32(&gFmtTag, 4, 0xffffffff, 0);
        crc = CRC32(mStream.mpBegin, (u32)(mStream.mpEnd - mStream.mpBegin), crc, 1);
        if (crc != crcStored) goto erase_fail;
    }
    return 1;
erase_fail:
    mStream.eraseAll();
    return 0;
}

// =====================================================================
// open a file, load its first entry and decode the stream
// =====================================================================
// @ 0x0068eb50
char Coder::OpenData(const char* path) {
    f55 = 0;
    if (!path) return 0;
    u32 frame;
    Hinter q;
    q.Open(path);
    char ok = q.GetFrame(0x32, &frame);
    if (ok && frame != 0) {
        Entry* e = q.GetEntry(0);
        if (e) {
            if (e->bits == 0x18 || e->bits == 0x20) {
                mWidth = e->width;
                mHeight = e->height;
                mStride = e->bits / 8;
                mFlag = (e->f438 == 8);
                u32 total = mStride * mHeight * e->width;
                mData.resize(total);
                f40 = 0;
                mState = 0;
                ok = q.Read(e, mData.mpBegin, (int)(mStride * mWidth));
                if (ok) {
                    f40 = total;
                    if (e->type == 0x504e47 && ReadData((void*)path))
                        f55 = 1;
                    mState = 1;
                }
                q.Free(e);
            } else {
                ok = 0;
            }
        }
    }
    return ok;
}

// =====================================================================
// write raw bytes into the coder (copy or entropy-code)
// =====================================================================
// @ 0x0068eca0
char Coder::WriteData(const u8* data, u32 n) {
    if (f55) {
        if (mState != 2) return 0;
        mStream.resize((u32)(mStream.mpEnd - mStream.mpBegin) + n);
        MemcpyT(mStream.mpEnd - n, data, n);
        return 1;
    }
    if (mState != 2) return 0;
    char ok = 1;
    const u8* p = data;
    const u8* end = data + n;
    while (p != end) {
        if (!ok) break;
        ok = EncodeBit(*p++);
    }
    if (ok) {
        f34 += n;
        u64 h = CRC64(data, n, mHashLo, mHashHi, 0);
        mHashLo = (u32)h;
        mHashHi = (u32)(h >> 32);
    }
    mState = ok ? mState : 1;
    return ok;
}

// =====================================================================
// finish / flush the coder into its destination stream
// =====================================================================
// @ 0x0068ed70
char Coder::Finalize(char flag) {
    if (f55) {
        if (mState != 2) return 0;
        if ((u32)(mStream.mpEnd - mStream.mpBegin) < 8) return 0;
        if (f56) {
            u32 crc = CRC32(mData.mpBegin, (u32)(mData.mpEnd - mData.mpBegin), gHNMagic, 0);
            crc = CRC32(mStream.mpBegin + 8, (u32)(mStream.mpEnd - mStream.mpBegin) - 8, crc, 1);
            mStream.resize((u32)(mStream.mpEnd - mStream.mpBegin) + 4);
            *(u32*)(mStream.mpEnd - 4) = crc;
        }
        u32 n = (u32)(mStream.mpEnd - mStream.mpBegin);
        mStream.resize(n + 8);
        *(u32*)(mStream.mpEnd - 8) = n - 8;
        *(u32*)(mStream.mpEnd - 4) = gTailTag;
        mState = 1;
        return 1;
    }
    if (mState != 2) return 0;
    u32 saved = f34;
    u32 buf[3];
    buf[0] = 0x02450d16;
    buf[1] = mHashLo;
    buf[2] = mHashHi;
    char ok = WriteData((u8*)buf, 4);
    if (ok) ok = WriteData((u8*)&buf[1], 8);
    if (ok && flag) Flush();
    InitMask();
    u32 tail[2];
    tail[0] = 0x02450d16;
    tail[1] = saved;
    if (ok && WriteData((u8*)tail, 8)) {
        mState = 1;
        return 1;
    }
    mState = 1;
    return 0;
}

// =====================================================================
// start a coder pass (either external passthrough or coded)
// =====================================================================
// @ 0x0068eef0
char Coder::Begin(char external) {
    f55 = external;
    if (external) {
        f56 = 0;
        if (mState != 1) return 0;
        if (mData.mpBegin == mData.mpEnd) return 0;
        mState = 2;
        mStream.resize(8);
        ((u32*)mStream.mpBegin)[0] = ((u32*)gMagicB)[0];
        ((u32*)mStream.mpBegin)[1] = ((u32*)gMagicB)[1];
        f56 = 1;
        return 1;
    }
    mStream.clear();
    if (mState != 1) return 0;
    if (mData.mpBegin == mData.mpEnd) return 0;
    if ((u32)(mData.mpEnd - mData.mpBegin) != f40) return 0;
    InitMask();
    u32 local[2];
    local[0] = 0x02450d16;
    local[1] = 0xffffffff;
    mState = 2;
    if (WriteData((u8*)local, 8)) {
        mHashLo = 0xffffffff;
        mHashHi = 0xffffffff;
        f34 = 0;
        return 1;
    }
    mState = 1;
    return 0;
}

// =====================================================================
// ctor: refcounted base + ThreadMutex @+8 + job @+0x38
// =====================================================================
// @ 0x0068eff0
RefObj::RefObj() : mMutex(0, true), mJob(0) {
}

// =====================================================================
// dtor
// =====================================================================
// @ 0x0068f050
RefObj::~RefObj() {
    if (mJob)
        ((CJob*)mJob)->Release();
}

// =====================================================================
// @ 0x0068f0b0  swap/replace a cJob under mutex  (CJobHolder::SetJob)
// =====================================================================
extern "C" int  AddRef_68F950(void* job);          // 0x068f950  cJob::AddRef
extern "C" int  Release_690120(void* job);         // 0x0690120  cJob::Release
extern "C" void AddWeakDependency_6913C0(void* self, void* other); // 0x06913c0

typedef int (__thiscall *FnAddRef)(void*);
typedef int (__thiscall *FnRelease)(void*);
typedef void (__thiscall *FnAddWeak)(void*, void*);

// small smart-pointer that holds a strong reference to a cJob and releases it on
// scope exit (the source of the SEH unwind state in the original).
struct CJobHolder {
    uint32_t pad0[2];
    Mutex mMutex;           // +0x08 (0x30 bytes)
    void* mJob;             // +0x38
    bool SetJob(void* target, void* job);
};
bool CJobHolder::SetJob(void* target, void* job) {
    struct JobPtr {
        void* mJob;
        __forceinline JobPtr(void* p) : mJob(p) {
            if (mJob) ((FnAddRef)AddRef_68F950)(mJob);
        }
        __forceinline ~JobPtr() {
            if (mJob) ((FnRelease)Release_690120)(mJob);
        }
    };
    mMutex.Lock((unsigned)0x014036f0);
    void* old = mJob;
    JobPtr held(old);                                   // strong ref to the old job
    if (job != mJob) {
        JobPtr add(job);                                // (acquire, freed below)
        mJob = job;
        if (old) ((FnRelease)Release_690120)(old);
    }
    mMutex.Unlock();
    ((FnAddWeak)AddWeakDependency_6913C0)(target, old);
    return true;
}

// =====================================================================
// @ 0x0068f180  set job + continuation if it succeeded  (CJobHolder2::Attach)
// =====================================================================
extern "C" bool Continuation_68F9F0(void* job, void* fn, void* arg);  // 0x068f9f0
typedef bool (__thiscall *FnContinuation)(void*, void*, void*);
struct CJobHolder2 {
    uint32_t f0, f4, f8;
    CJobHolder* mHolder;    // +0x0c
    void* mArg;             // +0x10
    bool Attach(void* job);
};
bool CJobHolder2::Attach(void* job) {
    CJobHolder* holder = mHolder;
    if (holder->SetJob(mArg, job)) {
        return ((FnContinuation)Continuation_68F9F0)(job, (void*)0x00753fb0, this);
    }
    return false;
}

// =====================================================================
// @ 0x0068f1d0  ctor of a job-lock object  (JobLock::JobLock)
// =====================================================================
extern "C" int  LockDec_68F9B0(void* lock);        // 0x068f9b0
typedef int (__thiscall *FnLockDec)(void*);
struct JobLock {
    void* vtbl0;            // +0x00
    void* vtbl1;            // +0x04
    volatile long mRef;     // +0x08 refcount (lock xchg/xadd)
    void* mRefObj;          // +0x0c intrusive refcounted object
    void* mJob;             // +0x10
    JobLock(void* out, void* job, void* refObj);
    ~JobLock();
};
JobLock::JobLock(void* out, void* job, void* refObj) {
    vtbl0 = (void*)0x013f1ab0;
    vtbl1 = (void*)0x013ef094;
    _InterlockedExchange(&mRef, 0);
    vtbl0 = (void*)0x014036fc;
    vtbl1 = (void*)0x014036f8;
    mRefObj = refObj;
    if (refObj)
        _InterlockedIncrement((volatile long*)((char*)refObj + 4));
    mJob = job;
    if (job) ((FnAddRef)AddRef_68F950)(job);
    *(void**)out = (void*)0x0068f1c0;
    *((void**)out + 1) = this;
    ((FnLockDec)LockDec_68F9B0)(this);
}

// =====================================================================
// @ 0x0068f2b0  dtor of the job-lock object  (JobLock::~JobLock)
// =====================================================================
JobLock::~JobLock() {
    if (mJob) ((FnRelease)Release_690120)(mJob);
    void* r = mRefObj;
    if (r) {
        volatile long* rc = (volatile long*)((char*)r + 4);
        long n = _InterlockedDecrement(rc);
        if (n == 0) {
            _InterlockedExchange(rc, 1);
            ((void (__thiscall*)(void*, int))VT(r)[0])(r, 1);
        }
    }
    vtbl0 = (void*)0x013eb938;
    vtbl1 = (void*)0x013ef094;
}

// =====================================================================
// @ 0x0068f350  try-lock two jobs; on success create a JobLock  (TryLockJobs)
// =====================================================================
extern "C" void* NewJobLock(unsigned size, const char* name, int a, int b, const char* f, int l); // 0x0f473a0

// The original takes its receiver in ecx (__thiscall). Model it as a member of the
// singleton it operates on so the calling convention survives.
struct JobLockTable {
    bool TryLockJobs(void* a, void* b);
};
bool JobLockTable::TryLockJobs(void* a, void* b) {
    int* p = (int*)FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, a)) return false;
    p = (int*)FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, b)) return false;
    void* mem = NewJobLock(0x14, "App/JobLock", 0, 0, 0, 0);
    JobLock* lock = 0;
    if (mem) {
        // JobLock(out=*a, job=*b, refObj=this)
        lock = (JobLock*)mem;
        lock->JobLock::JobLock(*(void**)a, *(void**)b, this);
    }
    if (lock) {
        ((void (__thiscall*)(void*))VT(lock)[0])(lock);
        ((void (__thiscall*)(void*))VT(lock)[1])(lock);
    }
    return true;
}

// =====================================================================
// @ 0x0068f450  EA::GetHighestBitPowerOf2
// =====================================================================
namespace EA {
int GetHighestBitPowerOf2(unsigned int v) {
    int n = 0;
    if (v & 0xffff0000) { n = 0x10; v >>= 0x10; }
    if (v & 0xff00) { n += 8; v >>= 8; }
    if (v & 0xf0) { n += 4; v >>= 4; }
    if (v & 0xc) { n += 2; v >>= 2; }
    if (v & 2) { n += 1; }
    return n;
}
}

// =====================================================================
// @ 0x0068f4a0  clear words and close handle at +8
// =====================================================================
struct HObj { void Close(); };
struct ClsF4A0 { uint32_t f0; uint32_t f4; HObj h; void Reset(); };
void ClsF4A0::Reset() {
    f0 = 0;
    f4 = 0;
    h.Close();
}

// =====================================================================
// @ 0x0068f4e0  mutex/semaphore member ctor helper
// =====================================================================
extern "C" void FUN_00922e10(void* p);             // 0x0922e10
extern "C" void FUN_00922610(void* p);             // 0x0922610
// Two member subobjects: a Thread mutex at +0x10 (ctor 0x922610) and a
// semaphore-ish object at +0x20 (ctor 0x922e10). The original builds +0x20 first
// (EH-guarded) then zeroes the +8/+0xc words then builds +0x10.
struct ClsF4E0Ctor {
    uint32_t f0, f4;
    uint32_t f8;            // +0x08
    uint32_t fc;            // +0x0c
    char     m10[0x10];     // +0x10
    char     m20[0x10];     // +0x20
    void ctorHelper();      // 0x0068f4e0
};
// The +0x20 subobject is built first; the EH arm covers the +0x10 one.
void ClsF4E0Ctor::ctorHelper() {
    ((void (__thiscall*)(void*))FUN_00922e10)(m20);
    f8 = 0;
    fc = 0;
    ((void (__thiscall*)(void*))FUN_00922610)(m10);
}

// =====================================================================
// @ 0x0068f540  lock mutex @+8 and ++count @+0x38
// =====================================================================
struct ClsF540 { uint32_t f0, f4; Mutex m; int count; void Acquire(); void Release(); };
void ClsF540::Acquire() {
    m.Lock((unsigned)0x01403750);
    ++count;
}

// =====================================================================
// @ 0x0068f560  --count and unlock
// =====================================================================
void ClsF540::Release() {
    --count;
    m.Unlock();
}

// =====================================================================
// @ 0x0068f570  notify + virtual teardown call
// =====================================================================
struct Inner570 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(void*, int, int);       // slot 7 (0x1c)
};
struct Outer570 { uint32_t pad[10]; Inner570* mInner; };  // inner ptr at +0x28
extern "C" int FUN_68F570(Outer570* p) {
    void (*fn)(void*) = *(void (**)(void*))((char*)p->mInner + 0x1e0);
    if (fn)
        fn(p);
    ((Inner570*)p->mInner)->v7(p, 0, 0);
    return 0;
}

// =====================================================================
// @ 0x0068f5a0  invoke slot 0 of *b with a
// =====================================================================
struct Callable68F5A0 { virtual void f(void* a); };
extern "C" void _FUN_68F5A0(void* a, Callable68F5A0* b) {
    b->f(a);
}

// =====================================================================
// @ 0x0068f5b0  replace pointer, release old  (ClsF5B0::Set)
// =====================================================================
struct VObj { virtual void v0(); virtual void v1(); };
struct ClsF5B0 { VObj* m; void Set(VObj* p); };
void ClsF5B0::Set(VObj* p) {
    VObj* old = m;
    m = p;
    if (old)
        old->v1();
}

// =====================================================================
// @ 0x0068f5d0  SP::JobCondition::Signal - drain the node list, posting each
// =====================================================================
extern "C" int SemaphorePost_922740(void* sem, int n);   // 0x0922740
typedef int (__thiscall *FnSemPost)(void*, int);
namespace SP {
struct JobCondition {
    void* mHead;                    // +0x00
    void* mTail;                    // +0x04
    void Signal();
};
}
void SP::JobCondition::Signal() {
    int* self = (int*)this;
    int* n = (int*)self[1];
    while (n != self) {
        n = (int*)self[0];
        int* pNext = (int*)n[1];
        if (pNext != n) {
            int* q = (int*)n[0];
            *pNext = (int)q;
            *(int**)((char*)q + 4) = pNext;
            void* sem = (char*)n + 8;
            *n = (int)n;
            n[1] = (int)n;
            ((FnSemPost)SemaphorePost_922740)(sem, 1);
        }
        n = (int*)self[1];
    }
}

// =====================================================================
// @ 0x0068f600  ctor of a semaphore-list container  (_FUN_68F600)
// =====================================================================
extern "C" void  Semaphore_ctor_922880(void* sem, int n);  // 0x0922880
extern "C" void  FUN_00743b50(void* p);                    // 0x0743b50
typedef void (__thiscall *FnSemCtor)(void*, int);

// The +0x10 subobject is an EA::Thread::Semaphore built by the external ctor at
// 0x00922880. Declaring (not defining) ctor+dtor makes the compiler emit an
// external call plus an EH unwind arm without any local COMDAT.
struct EA_Semaphore {
    char raw[0x10];
    EA_Semaphore(int n);                          // 0x00922880 (external)
    ~EA_Semaphore();                              // external
};
struct ClsF600 {
    uint32_t f0, f4;        // +0x00, +0x04
    void*    listNext;      // +0x08 (self-referential list head)
    void*    listPrev;      // +0x0c
    EA_Semaphore sem;       // +0x10
    char     vec[0x10];     // +0x20
    ClsF600();
};
ClsF600::ClsF600() : sem(0) {
    f0 = 0;
    f4 = 0;
    listNext = 0;
    listPrev = 0;
    listNext = &listNext;
    listPrev = &listNext;
    FUN_00743b50(vec);
}
extern "C" ClsF600* FUN_68F600(ClsF600* p) {
    p->ClsF600::ClsF600();
    return p;
}
