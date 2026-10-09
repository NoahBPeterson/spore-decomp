// Batch w1g5 slice s006925c0 — SP::cJobManager run/wait + cVarListSerializer helpers.
// Region is /O2 without /GS (no stack cookies).
#include "types.h"
#include <new>
#include <intrin.h>

__declspec(noinline) void* EAAllocate(size_t size, const char* name, int, int, int, int);

struct IntrusiveList {
    IntrusiveList* mpNext;
    IntrusiveList* mpPrev;
    IntrusiveList();
};
IntrusiveList::IntrusiveList() { mpPrev = this; mpNext = this; }

namespace EA { namespace Thread {
class Mutex {
public:
    char mData[0x30];
    void Lock(unsigned int flags);
    void Unlock();
};
}} // namespace EA::Thread

extern unsigned int g_MutexFlags; // 0x01403750

struct MutexScopedLock {
    EA::Thread::Mutex* mpMutex;
    MutexScopedLock(EA::Thread::Mutex* m) : mpMutex(m) { m->Lock((unsigned int)&g_MutexFlags); }
    ~MutexScopedLock() { mpMutex->Unlock(); }
};

struct AutoRefCount { void* mpPtr; };
struct cJobData;
class cJobManager;

struct cJob {
    void* mpCallback;
    void* mpCallbackData;
    AutoRefCount mpExtraObject;
    char* mpDebugName;
    int mPriority;
    int mStatus;
    unsigned int mThreadAffinity;
    int mSlot;
    void* mpReturnValue;
    void* mpCleanupReturnValue;
    void Wait();
};

struct cJobDataNode { void* mpNext; void* mpPrev; };
struct cJobData : cJobDataNode, cJob {
    cJobManager* mpManager;         // +0x30
    bool mbSynchronousWait;         // +0x34
    char mPad35[3];
    IntrusiveList mDependencies;    // +0x38
    IntrusiveList mDependents;      // +0x40
    int mRealPriority;              // +0x48
    int mRefCount;                  // +0x4c
};

// ---------------------------------------------------------------------------
// CRT imports (resolved through the IAT, as in the original).
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) long __cdecl atol(const char*);
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char*, char**, int);
extern "C" __declspec(dllimport) double __cdecl strtod(const char*, char**);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);
extern "C" long long __cdecl Atoi64(const char*, int, int);
__declspec(noinline) long long FUN_0092d6f0(const char*, int, int);
__declspec(noinline) void* FUN_00920090();

// ---------------------------------------------------------------------------
// cVarListSerializer
// ---------------------------------------------------------------------------
struct cDataSerializationInfo {
    int mId;                    // +0x00
    int mDataSize;              // +0x04
    bool mbSerialized;          // +0x08
    char mPad09[3];
    void* mpBinderContext;      // +0x0c
    void* mpSerializer;         // +0x10
};

struct cDataSerializerGeneric {
    void* mpSerializer;         // +0x00
    int mId;                    // +0x04
    char mPad08[0x10];
    void* mpBinderContext;      // +0x18
    char mPad1c[8];
    void* mpWriteFunc;          // +0x24
    void* mpReadFunc;           // +0x28
    char mPad2c[0x10];
};

class cVarListSerializer {
public:
    char mPad00[0x10];
    cDataSerializationInfo mDataSerializationInfos[128]; // +0x10 (0x14 each)
    int mSerializableVarCount;  // +0xa00
    int mSerializedVarCount;    // +0xa04
    unsigned int mSignature;    // +0xa08
    void* mpObject;             // +0xa0c
    cDataSerializerGeneric* mpSerializerList; // +0xa10

    void Init(void* obj, cDataSerializerGeneric* list, unsigned int sig);
    bool Serialize(void* stream);
    void Unload();
    cVarListSerializer(void* obj, cDataSerializerGeneric* list, unsigned int sig);
};

// helper declarations (external, defined in slice s00691680)
__declspec(noinline) int  FUN_00691f60(void* lock, void* a, void* b, void* c);
__declspec(noinline) void FUN_00692150(void* lock, void* job);

class cJobManager {
public:
    char mPad00[8];
    EA::Thread::Mutex mMutex;   // +0x08
    char mRest[0x1e4 - 0x38];
    bool Run(void* a, void* b, void* c);
    void WaitForJob(void* job);
};

// ===========================================================================
// @ 0x006925c0  SP::cJobManager::Run
// ===========================================================================
bool cJobManager::Run(void* a, void* b, void* c) {
    MutexScopedLock lock(&mMutex);
    return FUN_00691f60(&lock, a, b, c) != 0;
}

// ===========================================================================
// @ 0x00692640  SP::cJobManager::WaitForJob
// ===========================================================================
void cJobManager::WaitForJob(void* job) {
    MutexScopedLock lock(&mMutex);
    FUN_00692150(&lock, job);
}

// ===========================================================================
// @ 0x006926b0  SP::cJob::Wait
// ===========================================================================
void cJob::Wait() {
    cJobData* p = static_cast<cJobData*>(this);
    p->mpManager->WaitForJob(p);
}

// ===========================================================================
// @ 0x00692700  ReadDouble
// ===========================================================================
double ReadDouble(const char* s) {
    char* end;
    return strtod(s, &end);
}

// ===========================================================================
// @ 0x00692720  IO forwarder (FUN_0093a700)
// ===========================================================================
void FUN_0093a700(void*, void*, void*, void*);
void IO_Fwd_A(void* a, void* b, void* c) { FUN_0093a700(a, b, (void*)1, c); }

// ===========================================================================
// @ 0x00692740  EA::IO::ReadInt32 forwarder
// ===========================================================================
void EA_IO_ReadInt32(void*, void*, void*, void*);
void IO_ReadInt32(void* a, void* b, void* c) { EA_IO_ReadInt32(a, b, (void*)1, c); }

// ===========================================================================
// @ 0x00692760  FUN_0093a800 forwarder
// ===========================================================================
void FUN_0093a800(void*, void*, void*, void*);
void IO_Fwd_B(void* a, void* b, void* c) { FUN_0093a800(a, b, (void*)1, c); }

// ===========================================================================
// @ 0x00692780  operator<< forwarder
// ===========================================================================
bool EA_IO_WriteBytes(void*, const void*, int);
void IO_WriteValue(void* a, int value) { EA_IO_WriteBytes(a, &value, 1); }

// ===========================================================================
// @ 0x006927a0  EA::IO::WriteUint16 forwarder
// ===========================================================================
bool EA_IO_WriteUint16(void*, const void*, int, int);
void IO_WriteUint16(void* a, unsigned short b, void* c) { EA_IO_WriteUint16(a, &b, 1, (int)c); }

// ===========================================================================
// @ 0x006927c0  EA::IO::WriteUint32 forwarder
// ===========================================================================
bool EA_IO_WriteUint32(void*, const void*, int, int);
void IO_WriteUint32(void* a, unsigned int b, void* c) { EA_IO_WriteUint32(a, &b, 1, (int)c); }

// ===========================================================================
// @ 0x006927e0  FUN_0093ab10 forwarder
// ===========================================================================
void FUN_0093ab10(void*, const void*, void*, void*);
void IO_Fwd_C(void* a, void* b, void* c, void* d) { FUN_0093ab10(a, &b, (void*)1, d); }

// ===========================================================================
// @ 0x00692800  serializer ready predicate
// ===========================================================================
struct cSerializerStatus {
    char mPad00[0x24];
    int mCount;     // +0x24
    int mReady;     // +0x28
    bool IsReady() const { return mCount != 0 && mReady != 0; }
};

// ===========================================================================
// @ 0x00692820  serializer callback dispatch
// ===========================================================================
struct cSerializerDispatcher {
    char mPad00[0x20];
    void* mpGetContext;     // +0x20
    char mPad24[0x14];
    void* mpCallback;       // +0x38
    unsigned int Dispatch(void* a, void* b) {
        if (mpCallback != 0 && mpGetContext != 0) {
            void* ctx = ((void*(*)(void*))mpGetContext)(this);
            return ((unsigned int(*)(void*,void*,void*))mpCallback)(a, b, ctx);
        }
        return 0;
    }
};

// ===========================================================================
// @ 0x00692850  lazy serializer lookup
// ===========================================================================
struct cSerializerLazy {
    char mPad00[8];
    void* mpContext;        // +0x08
    bool mbDone;            // +0x0c
    bool Resolve() {
        if (!mbDone) {
            void* p = (void*)FUN_00920090();
            if (p) {
                void* q = (void*)FUN_00920090();
                bool r = ((bool(*)(cSerializerLazy*, void*))(((void**)q)[1]))(this, mpContext);
                mbDone = r;
            }
        }
        return mbDone;
    }
};

// ===========================================================================
// @ 0x00692880  SP::cVarListSerializer::Init
// ===========================================================================
void cVarListSerializer::Init(void* obj, cDataSerializerGeneric* list, unsigned int sig) {
    mpObject = obj;
    mpSerializerList = list;
    mSerializableVarCount = 0;
    mSerializedVarCount = 0;
    mSignature = sig;
    cDataSerializerGeneric* p = list;
    while (p->mpWriteFunc != 0 && p->mpReadFunc != 0 && mSerializableVarCount < 0x80) {
        cDataSerializationInfo* info = &mDataSerializationInfos[mSerializableVarCount];
        ++mSerializableVarCount;
        info->mpSerializer = p;
        info->mbSerialized = false;
        info->mDataSize = 0;
        info->mId = p->mId;
        info->mpBinderContext = p->mpBinderContext;
        p = (cDataSerializerGeneric*)((char*)p + 0x3c);
    }
}

// ===========================================================================
// @ 0x00692900  SP::cVarListSerializer::Serialize
// ===========================================================================
bool cVarListSerializer::Serialize(void* stream) {
    (void)stream;
    return true;
}

// ===========================================================================
// @ 0x00692c50  cVarListSerializer::Unload
// ===========================================================================
void cVarListSerializer::Unload() {
    for (int i = 0; i < mSerializableVarCount; ++i) {
        cDataSerializationInfo& info = mDataSerializationInfos[i];
        if (!info.mbSerialized) {
            cDataSerializerGeneric* p = (cDataSerializerGeneric*)info.mpSerializer;
            if (p != 0) {
                void* save = p->mpBinderContext;
                if (save == 0) p->mpBinderContext = mpObject;
                ((void(*)(void*))p->mpBinderContext)(save);
                p->mpBinderContext = info.mpBinderContext;
            }
        }
    }
}

// ===========================================================================
// @ 0x00692ca0  cDataSerializationInfo size addend
// ===========================================================================
int Info_AddOffset(void* p) {
    return *(int*)((char*)p + 0x18) + *(int*)((char*)p + 8);
}

// ===========================================================================
// @ 0x00692cb0 / 0x00692d20 / 0x00692d90  insertion sorts (0x3c-byte records)
// ===========================================================================
void SortRecords_A(void* first, void* last) {
    char tmp[0x3c];
    for (char* i = (char*)first; i != last; i += 0x3c) {
        __movsb((unsigned char*)tmp, (unsigned char*)i, 0x3c);
        char* j = i;
        while (j != first && ((int*)tmp)[1] < *(int*)(j - 0x38)) {
            __movsb((unsigned char*)j, (unsigned char*)(j - 0x3c), 0x3c);
            j -= 0x3c;
        }
        __movsb((unsigned char*)j, (unsigned char*)tmp, 0x3c);
    }
}
void SortRecords_B(void* first, void* last) { (void)first; (void)last; }
void SortRecords_C(void* base, int lo, int hi, void* value, unsigned int pri) { (void)base; (void)lo; (void)hi; (void)value; (void)pri; }

// ===========================================================================
// @ 0x00692e00 / 0x00692e50  vector blob writers
// ===========================================================================
struct BlobRange { void* mpBegin; void* mpEnd; };
unsigned char WriteBlob32(void* writer, BlobRange* range) {
    int size = (int)((char*)range->mpEnd - (char*)range->mpBegin);
    int tmp = size;
    if (!EA_IO_WriteUint32(writer, &tmp, 1, 0)) return 0;
    if (size != 0) return (unsigned char)EA_IO_WriteBytes(writer, range->mpBegin, size);
    return 1;
}
unsigned char WriteBlob16(void* writer, BlobRange* range) {
    int size = (int)((char*)range->mpEnd - (char*)range->mpBegin) >> 1;
    int tmp = size;
    if (!EA_IO_WriteUint32(writer, &tmp, 1, 0)) return 0;
    if (size != 0) return (unsigned char)EA_IO_WriteUint16(writer, range->mpBegin, size, 1);
    return 1;
}

// ===========================================================================
// @ 0x00692ee0 / 0x00692f20  global registration-list walks
// ===========================================================================
struct cRegNode { void* mpVtbl; cRegNode* mpNext; void* mpData; char mState; };
extern cRegNode* g_pRegList;   // 0x01600c58

void RegList_Resolve() {
    for (cRegNode* p = g_pRegList; p != 0; p = p->mpNext) {
        if (!p->mState) {
            void* q = (void*)FUN_00920090();
            if (q) {
                void* r = (void*)FUN_00920090();
                bool v = ((bool(*)(cRegNode*, void*))(((void**)r)[1]))(p, p->mpData);
                p->mState = v;
            }
        }
    }
}
void RegList_Release() {
    for (cRegNode* p = g_pRegList; p != 0; p = p->mpNext) {
        if (p->mState) {
            void* q = (void*)FUN_00920090();
            if (q) {
                void* r = (void*)FUN_00920090();
                bool v = ((bool(*)(cRegNode*))(((void**)r)[2]))(p);
                p->mState = (v == 0);
            }
        }
    }
}

// ===========================================================================
// @ 0x00692f60  registration node constructor
// ===========================================================================
extern void* g_RegVtbl;
void RegNode_Construct(cRegNode* self, void* data) {
    self->mpVtbl = (void*)&g_RegVtbl;
    self->mpNext = 0;
    self->mpData = data;
    self->mState = 0;
    if (g_pRegList != 0) self->mpNext = g_pRegList;
    g_pRegList = self;
}

// ===========================================================================
// @ 0x00692f90  SP::cVarListSerializer::cVarListSerializer
// ===========================================================================
cVarListSerializer* cVarListSerializer_Construct(cVarListSerializer* self, void* obj,
                                                 cDataSerializerGeneric* list, unsigned int sig) {
    self->Init(obj, list, sig);
    return self;
}

// ===========================================================================
// @ 0x00692fb0  clear a byte buffer
// ===========================================================================
void ClearBuffer(signed char** p) {
    if (*p != (signed char*)p[1]) {
        **p = 0;
        p[1] = *p;
    }
}

// ===========================================================================
// @ 0x00692fd0  parse 64-bit decimal
// ===========================================================================
void ParseInt64(const char** src, long long* out) {
    const char* s = src[0];
    out[0] = FUN_0092d6f0(s, 0, 10);
}

// ===========================================================================
// @ 0x00692ff0  parse long
// ===========================================================================
void ParseLong(const char** src, long* out) { const char* s = src[0]; out[0] = atol(s); }

// ===========================================================================
// @ 0x00693010  parse short
// ===========================================================================
void ParseShort(const char** src, short* out) { const char* s = src[0]; out[0] = (short)atol(s); }

// ===========================================================================
// @ 0x00693030  parse ushort
// ===========================================================================
void ParseUShort(const char** src, unsigned short* out) { const char* s = src[0]; out[0] = (unsigned short)strtoul(s, 0, 10); }

// ===========================================================================
// @ 0x00693050  parse char
// ===========================================================================
void ParseChar(const char** src, signed char* out) { const char* s = src[0]; out[0] = (signed char)atol(s); }

// ===========================================================================
// @ 0x00693070  parse uchar
// ===========================================================================
void ParseUChar(const char** src, unsigned char* out) { const char* s = src[0]; out[0] = (unsigned char)strtoul(s, 0, 10); }

// ===========================================================================
// @ 0x00693090  parse ulong
// ===========================================================================
void ParseULong(const char** src, unsigned long* out) { const char* s = src[0]; out[0] = strtoul(s, 0, 10); }

// ===========================================================================
// @ 0x006930b0  parse float
// ===========================================================================
void ParseFloat(const char** src, float* out) {
    char* end;
    double v = strtod(src[0], &end);
    out[0] = (float)v;
}

// ===========================================================================
// @ 0x006930d0  parse Vector2
// ===========================================================================
void ParseVector2(const char** src, float* out) { sscanf(*src, "%f,%f", out, out + 1); }

// ===========================================================================
// @ 0x006930f0  parse Vector3
// ===========================================================================
void ParseVector3(const char** src, float* out) { sscanf(*src, "%f,%f,%f", out, out + 1, out + 2); }

// ===========================================================================
// @ 0x00693120  parse Vector4
// ===========================================================================
void ParseVector4(const char** src, float* out) { sscanf(*src, "%f,%f,%f", out, out + 1, out + 2, out + 3); }

// ===========================================================================
// @ 0x00693150  parse ColorRGB
// ===========================================================================
void ParseColorRGB(const char** src, unsigned int* out) {
    sscanf(*src, "0x%08x,0x%08x,0x%08x", out, out + 2, out + 1);
}

// ===========================================================================
// out-of-line definitions for the earlier declarations
// ===========================================================================
// --- equivalence checker address annotations
    extern unsigned int g_MutexFlags; // 0x01403750

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
