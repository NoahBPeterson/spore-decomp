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
struct Mutex { uint32_t _[12]; void Lock(void*); void Unlock(); };

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
// @ 0x0068f0b0  swap/replace a cJob under mutex
// =====================================================================
struct CJobHolder {
    uint32_t pad0[2];
    Mutex mMutex;           // +0x08 (0x30 bytes)
    void* mJob;             // +0x38
    void SetJob(void* job, void* arg2);
};
void CJobHolder::SetJob(void* job, void* arg2) {
    (void)arg2;
    mMutex.Lock((void*)0x014036f0);
    void* old = mJob;
    if (old) FUN_0068f950(old);
    if (job != mJob) {
        if (job) FUN_0068f950(job);
        mJob = job;
        if (mJob) GetStatus(mJob);
    }
    mMutex.Unlock();
    FUN_006913c0(old);
    if (old) GetStatus(old);
}

// =====================================================================
// @ 0x0068f180  set job + continuation if it succeeded
// =====================================================================
struct CJob180 { void* Continuation(void* fn, void* arg); };
struct CJobHolder2 {
    uint32_t f0, f4, f8;
    CJobHolder* mHolder;    // +0x0c
    void* mArg;             // +0x10
    bool Attach(void* job);
};
bool CJobHolder2::Attach(void* job) {
    mHolder->SetJob(job, mArg);
    if (mHolder != 0) {
        ((CJob180*)job)->Continuation((void*)0x00753fb0, this);
        return true;
    }
    return false;
}

// =====================================================================
// @ 0x0068f1d0  ctor of a job-lock object (partial: vtables/refcounts)
// =====================================================================
struct JobLock {
    void* vtbl0;            // +0x00
    void* vtbl1;            // +0x04
    void* f08;              // +0x08
    void* mRefObj;          // +0x0c
    void* mJob;             // +0x10
    JobLock(void* a, int b, void* c);
};
JobLock::JobLock(void* a, int b, void* c) {
    (void)a; (void)b; (void)c;
}

// =====================================================================
// @ 0x0068f2b0  dtor of the job-lock object (partial)
// =====================================================================
extern "C" void Dtor_68F2B0(JobLock* p) {
    if (p->mJob) GetStatus(p->mJob);
    void* r = p->mRefObj;
    if (r) {
        long* rc = (long*)((char*)r + 4);
        long n = _InterlockedExchangeAdd(rc, -1);
        if (n == 1) {
            _InterlockedExchange(rc, 1);
            ((void (__thiscall*)(void*, int))VT(r)[0])(r, 1);
        }
    }
}

// =====================================================================
// @ 0x0068f350  try-lock two jobs; on success create a JobLock (partial)
// =====================================================================
extern "C" int TryLockJobs(void* a, void* b, JobLock** out) {
    (void)a; (void)b; (void)out;
    int* p = FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, b)) return 0;
    p = FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, b)) return 0;
    return 1;
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
// @ 0x0068f4e0  ctor/dtor helper (partial, EH)
// =====================================================================
extern "C" void FUN_68F4E0(void* p) {
    void* o = *(void**)((char*)p + 0x20);
    (void)o;
    *(uint32_t*)((char*)p + 8) = 0;
    *(uint32_t*)((char*)p + 0xc) = 0;
}

// =====================================================================
// @ 0x0068f540  lock mutex @+8 and ++count @+0x38
// =====================================================================
struct ClsF540 { uint32_t f0, f4; Mutex m; int count; void Acquire(); void Release(); };
void ClsF540::Acquire() {
    m.Lock((void*)0x01403750);
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
extern "C" void FUN_68F5A0(void* a, Callable68F5A0* b) {
    b->f(a);
}

// =====================================================================
// @ 0x0068f5b0  replace pointer, release old
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
// @ 0x0068f5d0  drain a list posting a semaphore for each detached node
// =====================================================================
struct ListNode { ListNode* next; ListNode* prev; uint32_t pad[2]; };
struct SemHolder { uint32_t pad[2]; };
extern "C" void FUN_68F5D0(ListNode* h) {
    while (h->next != h) {
        ListNode* n = h->next;
        ListNode* p = n->next;
        if (p != n) {
            ListNode* q = n->prev;
            p->prev = q;
            q->next = p;
            n->next = n;
            n->prev = n;
            SemaphorePost((char*)n + 0x10, 1);
        }
    }
}

// =====================================================================
// @ 0x0068f600  ctor of a semaphore-list container (partial, EH)
// =====================================================================
extern "C" void* FUN_68F600(void* p) {
    *(uint32_t*)((char*)p + 4) = 0;
    *(uint32_t*)((char*)p + 0) = 0;
    char* s = (char*)p + 8;
    *(uint32_t*)(s + 4) = 0;
    *(uint32_t*)(s + 0) = 0;
    *(void**)(s) = s;
    *(void**)(s + 4) = s;
    return p;
}
