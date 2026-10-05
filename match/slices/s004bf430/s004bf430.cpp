// Slice s004bf430 (editor model (de)serialization + EA allocator + editor UI helpers).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long* Addend, long Value);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---------------------------------------------------------------------------
// 004c0190  Resource::ResourceObject::GetReferenceCount
// ---------------------------------------------------------------------------
struct FixedBufferAllocatorStub {
    struct buffer_info { int32_t mSignature, mSize, mSizeFree; void* mpFirstFree; };
    buffer_info* mpBufferInfo;
    void* Malloc(void* p, int n);       // 0x4bfc40
    void Free(void* p);                 // 0x4bcab0
};
__declspec(thread) void* g_tls_current;

struct ResourceObject {
    void* vptr;          // +0
    int32_t mnRefCount;  // +4
    int GetReferenceCount();
};

int ResourceObject::GetReferenceCount() {
    return _InterlockedExchangeAdd((volatile long*)&mnRefCount, 0);
}

void* FixedBufferAllocatorStub::Malloc(void* p, int n) {
    (void)p; (void)n;
    return 0;
}
void FixedBufferAllocatorStub::Free(void* p) {
    (void)p;
}

// 004bfc10
void FUN_004bfc10(void* p) {
    FixedBufferAllocatorStub* fba = (FixedBufferAllocatorStub*)g_tls_current;
    fba->Malloc(p, 4);
}

extern void* FUN_00928a80(void* p, uint32_t size, int zero);   // 0x928a80
extern void* memcpy_impl(void* dst, const void* src, uint32_t n);  // 0x11e0744

// 004c0020  `anonymous namespace'::LocalExpatRealloc
void* FUN_004c0020(void* p, uint32_t size) {
    FixedBufferAllocatorStub* fba = (FixedBufferAllocatorStub*)g_tls_current;
    if (p >= (void*)(fba->mpBufferInfo + 1) &&
        p < (void*)((char*)&fba->mpBufferInfo[1] + fba->mpBufferInfo->mSize)) {
        void* dst = fba->Malloc(p, 4);
        uint32_t oldSize = *(uint32_t*)((char*)p - 8) & 0x3fffffff;
        uint32_t n = size < oldSize ? size : oldSize;
        memcpy_impl(dst, p, n);
        fba->Free(p);
        return dst;
    }
    return FUN_00928a80(p, size, 0);
}

// ---------------------------------------------------------------------------
// (De)serialization entry points: reproduced as skeletons (see partial.txt).
// ---------------------------------------------------------------------------
extern int WriteBinaryEditorModel(int data);   // 0x4b0010

// 004bf430  `anonymous namespace'::ReadRuntimeCreatureData (PARTIAL skeleton)
bool FUN_004bf430(int* stream, int data) {
    (void)stream; (void)data;
    return false;
}

// 004bf770  `anonymous namespace'::WriteRuntimeCreatureData (PARTIAL skeleton)
bool FUN_004bf770(int* stream, int data) {
    (void)stream; (void)data;
    return false;
}

// 004bfb20 (near-complete; stream header + two data segments)
struct StreamWriter {
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vC();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34();
    virtual bool v38(void* buf, int n);   // +0x38
};
extern bool FUN_004bf0a0(StreamWriter* w, int addr, int n);   // 0x4bf0a0

bool FUN_004bfb20(StreamWriter* w, int data) {
    int buf = WriteBinaryEditorModel(data);
    if (buf != 0) {
        int header[2];
        header[0] = 0x48657ed3;
        header[1] = 5;
        int local_c[2];
        local_c[0] = (*(int*)(buf + 0x9c) - *(int*)(buf + 0x98)) / 0x1d8;
        local_c[1] = 0;
        if (w->v38(header, 8) && w->v38(local_c, 8)) {
            if (!FUN_004bf0a0(w, buf + 0x18, 0x80))
                return false;
            if (!FUN_004bf0a0(w, *(int*)(buf + 0x98), local_c[0] * 0x1d8))
                return false;
            return true;
        }
    }
    return false;
}

// 004bf9f0  `anonymous namespace'::ReadBinaryEditorModel
extern int FUN_004afd00(int n);                                  // 0x4afd00
extern void operator_new__(void* p, int a, int n);               // in-place new
struct StreamReader {
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vC();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual int v30(void* buf, int n);   // +0x30
};
extern bool FUN_004bf2a0(StreamReader* r, int addr, int n);      // 0x4bf2a0

bool FUN_004bf9f0(StreamReader* r, int data) {
    int buf = WriteBinaryEditorModel(data);
    if (buf == 0)
        return false;
    int local_1c;
    uint32_t local_18;
    if (r->v30(&local_1c, 8) != 8)
        return false;
    if (local_1c != 0x48657ed3 || local_18 <= 2 || local_18 >= 6)
        return false;
    uint32_t local_c, local_8;
    if (r->v30(&local_c, 8) != 8)
        return false;
    if (local_c >= 0x401 || local_8 >= 0x81)
        return false;
    FUN_004afd00(local_c);
    operator_new__((void*)(buf + 0x18), 0, 0x80);
    int n = (local_18 < 5) ? 0x44 : 0x80;
    if (!FUN_004bf2a0(r, buf + 0x18, n))
        return false;
    if (!FUN_004bf2a0(r, *(int*)(buf + 0x98), local_c * 0x1d8))
        return false;
    return true;
}

// 004c0250 / 004c0350  grow fixed-stride arrays (PARTIAL skeletons).
extern void* FUN_0042dee0(void* alloc, int n, int align, int zero);  // 0x42dee0
extern void FUN_004b03f0(void* first, void* last, void* dst);          // 0x4b03f0
extern void FUN_004c0bd0(void* dst, int n, void* out);                 // 0x4c0bd0
extern void FUN_004c0680(void* dst, void* srcEnd);                     // 0x4c0680
void FUN_004c0250(int* self, uint32_t count) {
    if ((uint32_t)((self[2] - self[0]) / 0x1d8) >= count)
        return;
    int* p = count ? (int*)FUN_0042dee0(self + 3, count * 0x1d8, 4, 0) : 0;
    FUN_004b03f0((void*)self[0], (void*)self[1], p);
    int* oldBegin = (int*)self[0];
    self[0] = (int)p;
    self[1] = ((self[1] - (int)oldBegin) / 0x1d8) * 0x1d8 + (int)p;
    self[2] = count * 0x1d8 + self[0];
}

void FUN_004c0350(int* self, uint32_t count) {
    if ((uint32_t)((self[1] - self[0]) / 0x8c) >= count)
        return;
    char local_90[140];
    FUN_004c0bd0((void*)self[1], count - (self[1] - self[0]) / 0x8c, local_90);
    FUN_004c0680((void*)(count * 0x8c + self[0]), (void*)self[1]);
}

// ---------------------------------------------------------------------------
// 004c0130  create an 8-byte editor resource factory and run its init vcall.
// ---------------------------------------------------------------------------
struct FactoryObject {
    void* vptr;
    int32_t mnRefCount;
};
extern void* ZoneObject_operator_new(uint32_t size, const char* name, int, int, int, int);  // 0x926020
struct FactoryCtor {
    FactoryObject* Init();   // 0x4bbfb0
};
struct FactoryVtbl {
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vC();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
};

FactoryObject* FUN_004c0130() {
    FactoryObject* n40 = (FactoryObject*)ZoneObject_operator_new(8, "Editor", 0, 0, 0, 0);
    FactoryObject* len;
    if (n40)
        len = ((FactoryCtor*)n40)->Init();
    else
        len = 0;
    FactoryObject* v33 = len;
    ((FactoryVtbl*)v33)->v10();
    return v33;
}

// ---------------------------------------------------------------------------
// 004c01b0  initialize an XML text writer (inline 0x100 buffer at +0x14).
// ---------------------------------------------------------------------------
struct XmlTextWriter {
    int* mpBuffer;      // +0
    int* mpBufferEnd;   // +4
    int* mpCapacity;    // +8
    int pad0c;          // +0xc
    int pad10;          // +0x10
    void FUN_00422c80(void* out);   // 0x422c80
    int* Init();
};

void XmlTextWriter::FUN_00422c80(void* out) {
    (void)out;
}

int* XmlTextWriter::Init() {
    int* v33 = (int*)this + 5;
    int n40;
    int len;
    FUN_00422c80(&n40);
    mpBufferEnd = (int*)this + 5;
    mpBuffer = mpBufferEnd;
    mpCapacity = (int*)((char*)mpBuffer + 0x100);
    *(uint16_t*)mpBuffer = 0;
    (void)v33;
    (void)len;
    return (int*)this;
}
