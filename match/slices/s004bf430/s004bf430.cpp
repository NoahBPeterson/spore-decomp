// Slice s004bf430 (editor model (de)serialization + EA allocator + editor UI helpers).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long* Addend, long Value);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---------------------------------------------------------------------------
// 004c0190  Resource::ResourceObject::GetReferenceCount
// ---------------------------------------------------------------------------
struct SPMemPoolStub {
    void* LockedAlloc(uint32_t size, int a, int b, int c, int d, int e);                      // 0x009289f0 (ret 0x18)
    void* LockedAligned(uint32_t size, uint32_t align, int a, int b, int c, int d, int e, int f);  // 0x00928a30 (ret 0x20)
};
extern SPMemPoolStub* g_pSPMemPool;     // 0x016c8b44

struct FixedBufferAllocatorStub {
    struct buffer_info { int32_t mSignature, mSize, mSizeFree; void* mpFirstFree; };
    struct block_header { uint32_t mSize; block_header* mpPrev; };
    buffer_info* mpBufferInfo;
    bool IsInitialized() const { return mpBufferInfo != 0; }
    void* Malloc(uint32_t nSize, uint32_t nAlignment);   // 0x4bfc40
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

#define FBA_MASK 0x3fffffff
#define FBA_INUSE 0x80000000
#define FBA_TRAILER 0x40000000
// @ 0x004bfc40
void* FixedBufferAllocatorStub::Malloc(uint32_t nSize, uint32_t nAlignment) {
    char* i;
    int n40;
    block_header* n1;
    int n16;
    block_header* v40;
    block_header* list;
    block_header* g;
    int p23;
    int owner;
    uint32_t t33;
    int node;
    block_header* alloc;

    n40 = ((nSize + 3) & 0xfffffffc) + 8 + ((mpBufferInfo[1].mSignature & FBA_TRAILER) ? 4 : 0);
    if (IsInitialized() && mpBufferInfo->mSizeFree >= n40) {
        i = (char*)mpBufferInfo + 0x10 + mpBufferInfo->mSize;
        if (n40 > 8) {
            n1 = (block_header*)mpBufferInfo->mpFirstFree;
            n16 = 0;
            while ((char*)n1 < i && n16 + n40 < mpBufferInfo->mSizeFree) {
                if ((int)n1->mSize >= 0) {
                    list = (block_header*)((char*)n1 + (n1->mSize & FBA_MASK));
                    if ((char*)list < i && (int)list->mSize >= 0) {
                        g = (block_header*)((char*)list + (list->mSize & FBA_MASK));
                        if ((char*)g < i)
                            g->mpPrev = n1;
                        n1->mSize = n1->mSize + list->mSize;
                        continue;
                    }
                    n16 = (n1->mSize & FBA_MASK) + n16;
                    v40 = (block_header*)(((uint32_t)n1 + nAlignment + 7 & ~(nAlignment - 1)) - 8);
                    if ((char*)v40 + n40 < (char*)n1 + (n1->mSize & FBA_MASK)) {
                        owner = (int)((char*)v40 - (char*)n1);
                        if (owner > 0) {
                            if (!(mpBufferInfo[1].mSignature & FBA_TRAILER)) {
                                v40->mpPrev = n1->mpPrev;
                                v40->mSize = (n1->mSize & FBA_MASK) - owner;
                                v40->mpPrev->mSize = (v40->mpPrev->mSize & 0xc0000000) | (((v40->mpPrev->mSize & FBA_MASK) + owner) & FBA_MASK);
                            } else {
                                t33 = (n1->mpPrev->mSize & FBA_TRAILER)
                                    ? *(uint32_t*)((n1->mpPrev->mSize & FBA_MASK) + (char*)n1->mpPrev - 4) : 0;
                                v40->mpPrev = n1->mpPrev;
                                v40->mSize = (n1->mSize & FBA_MASK) - owner;
                                v40->mpPrev->mSize = (v40->mpPrev->mSize & 0xc0000000) | (((v40->mpPrev->mSize & FBA_MASK) + owner) & FBA_MASK);
                                if ((int)v40->mpPrev->mSize < 0 || v40->mpPrev == (block_header*)(mpBufferInfo + 1))
                                    mpBufferInfo->mSizeFree = mpBufferInfo->mSizeFree - owner;
                                *(uint32_t*)((v40->mpPrev->mSize & FBA_MASK) + (char*)v40->mpPrev - 4) = t33;
                            }
                        }
                        p23 = (v40->mSize & FBA_MASK) - n40;
                        if (p23 >= 0x28) {
                            v40->mSize = (v40->mSize & 0xc0000000) | ((uint32_t)n40 & FBA_MASK);
                            alloc = (block_header*)((char*)v40 + (v40->mSize & FBA_MASK));
                            alloc->mSize = p23;
                            alloc->mpPrev = v40;
                        }
                        if (mpBufferInfo->mpFirstFree == n1)
                            mpBufferInfo->mpFirstFree = (char*)v40 + (v40->mSize & FBA_MASK);
                        mpBufferInfo->mSizeFree = mpBufferInfo->mSizeFree - (v40->mSize & FBA_MASK);
                        v40->mSize = v40->mSize | FBA_INUSE;
                        if (mpBufferInfo[1].mSignature & FBA_TRAILER) {
                            v40->mSize = v40->mSize | FBA_TRAILER;
                            *(FixedBufferAllocatorStub**)((char*)v40 + (v40->mSize & FBA_MASK) - 4) = this;
                        }
                        return (char*)v40 + 8;
                    }
                }
                n1 = (block_header*)((char*)n1 + (n1->mSize & FBA_MASK));
            }
        } else {
            return (char*)mpBufferInfo + 0x18;
        }
    }
    if (nAlignment < 8)
        return g_pSPMemPool->LockedAlloc(n40, 0, 0, 0, 0, 0);
    return g_pSPMemPool->LockedAligned(n40, nAlignment, 0, 0, 0, 0, 0, 0);
}
void FixedBufferAllocatorStub::Free(void* p) {
    (void)p;
}

// 004bfc10
// @ 0x004bfc10
void FUN_004bfc10(void* p) {
    FixedBufferAllocatorStub* fba = (FixedBufferAllocatorStub*)g_tls_current;
    fba->Malloc((uint32_t)p, 4);
}

extern void* FUN_00928a80(void* p, uint32_t size, int zero);   // 0x928a80
extern void* memcpy_impl(void* dst, const void* src, uint32_t n);  // 0x11e0744

// 004c0020  `anonymous namespace'::LocalExpatRealloc
// @ 0x004c0020
void* FUN_004c0020(void* p, uint32_t size) {
    FixedBufferAllocatorStub* fba = (FixedBufferAllocatorStub*)g_tls_current;
    if (p >= (void*)(fba->mpBufferInfo + 1) &&
        p < (void*)((char*)&fba->mpBufferInfo[1] + fba->mpBufferInfo->mSize)) {
        void* dst = fba->Malloc((uint32_t)p, 4);
        uint32_t oldSize = *(uint32_t*)((char*)p - 8) & 0x3fffffff;
        uint32_t n = size < oldSize ? size : oldSize;
        memcpy_impl(dst, p, n);
        fba->Free(p);
        return dst;
    }
    return FUN_00928a80(p, size, 0);
}

// ---------------------------------------------------------------------------
// Runtime creature block (magic 0xabb455b7): an 8-byte header, a 0x10-byte count
// block, an RLE-compressed blob and six parallel arrays. Version 9 stops after
// the first three counts, version 10 appends a 0x38-byte bone array.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl memset(void* dst, int value, uint32_t size);

// Byte stream: Read is vtable slot 12 (+0x30) and returns the byte count,
// Write is vtable slot 14 (+0x38) and returns whether all bytes went out.
struct IStream {
    virtual void Unk00(); virtual void Unk04(); virtual void Unk08(); virtual void Unk0C();
    virtual void Unk10(); virtual void Unk14(); virtual void Unk18(); virtual void Unk1C();
    virtual void Unk20(); virtual void Unk24(); virtual void Unk28(); virtual void Unk2C();
    virtual int  Read(void* dst, uint32_t size);              // +0x30
    virtual void Unk34();
    virtual bool Write(const void* src, uint32_t size);       // +0x38
};

struct ChunkHeader {              // 8-byte block header
    uint32_t mMagic;              // 0xabb455b7
    uint32_t mVersion;            // 9 or 10
};

struct ChunkCounts {              // 0x10-byte element counts (0xc at version 9)
    uint32_t mNumElements;        // 0x8c-byte element records
    uint32_t mNumValues;          // 4-byte values, plus one byte each
    uint32_t mNumFloats;          // floats, spread over three arrays
    uint32_t mNumBones;           // 0x38-byte bone records (version 10 only)
};

struct Element8c { uint32_t mData[0x8c / 4]; };
struct Bone38    { uint32_t mData[0x38 / 4]; };

// Stack-frame filler: the original reserved a slot block at each resize() call site
// for locals of the inlined helper cl declined (0x28 bytes per call).
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

// Growable three-pointer vector; resize() is out of line for every element type.
template <class T> struct SpVector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    T* begin() const { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }
    void resize(uint32_t n);
};
template <> void SpVector<Element8c>::resize(uint32_t n);   // 0x4c0350
template <> void SpVector<uint32_t>::resize(uint32_t n);    // 0x4cd3c0
template <> void SpVector<uint8_t>::resize(uint32_t n);     // 0x4c0410
template <> void SpVector<float>::resize(uint32_t n);       // 0x4afc80
template <> void SpVector<Bone38>::resize(uint32_t n);      // 0x4c0480

struct CreatureData {
    uint32_t mPad00[6];                  // 0x00
    uint8_t  mPayload[0x80];             // 0x18 RLE-compressed block
    SpVector<Element8c> mElements;       // 0x98
    uint32_t mPadA4[2];                  // 0xa4
    SpVector<uint32_t>  mValues;         // 0xac
    uint32_t mPadB8[2];                  // 0xb8
    SpVector<uint8_t>   mValueBytes;     // 0xc0
    uint32_t mPadCC[2];                  // 0xcc
    SpVector<uint32_t>  mScalars;        // 0xd4
    uint32_t mPadE0[2];                  // 0xe0
    SpVector<float>     mFloats0;        // 0xe8
    uint32_t mPadF4[2];                  // 0xf4
    SpVector<float>     mFloats1;        // 0xfc
    uint32_t mPad108[2];                 // 0x108
    uint32_t mFlags;                     // 0x110
    SpVector<Bone38>    mBones;          // 0x114
};

extern bool ReadRLE(IStream* stream, uint8_t* data, uint32_t size);        // 0x4bf2a0
extern bool WriteRLE(IStream* stream, const uint8_t* data, uint32_t size); // 0x4bf0a0

// @ 0x004bf430
bool FUN_004bf430(int* stream, int data)
{
    ChunkHeader header;
    uint32_t nPayload;
    ChunkCounts counts;

    if (((IStream*)stream)->Read(&header, 8) != 8
        || header.mMagic != 0xabb455b7 || header.mVersion < 9 || header.mVersion > 10)
        return false;
    if (header.mVersion >= 10) {
        if (((IStream*)stream)->Read(&counts, 0x10) != 0x10)
            return false;
    } else {
        if (((IStream*)stream)->Read(&counts, 0xc) != 0xc)
            return false;
        counts.mNumBones = 0;
    }
    if (counts.mNumElements > 0x100 || counts.mNumValues > 0x1000 || counts.mNumFloats > 0x400)
        return false;
    ScratchSlots<10>();
    ((CreatureData*)data)->mElements.resize(counts.mNumElements);
    ScratchSlots<10>();
    ((CreatureData*)data)->mValues.resize(counts.mNumValues);
    ScratchSlots<10>();
    ((CreatureData*)data)->mValueBytes.resize(counts.mNumValues);
    ScratchSlots<10>();
    ((CreatureData*)data)->mScalars.resize(counts.mNumFloats);
    ScratchSlots<10>();
    ((CreatureData*)data)->mFloats0.resize(counts.mNumFloats);
    ScratchSlots<10>();
    ((CreatureData*)data)->mFloats1.resize(counts.mNumFloats);
    ScratchSlots<10>();
    ((CreatureData*)data)->mBones.resize(counts.mNumBones);
    memset(((CreatureData*)data)->mPayload, 0, 0x80);
    nPayload = 0x80;
    if (header.mVersion < 8)
        nPayload -= 0x3c;
    if (!ReadRLE((IStream*)stream, ((CreatureData*)data)->mPayload, nPayload))
        return false;
    if (((IStream*)stream)->Read(((CreatureData*)data)->mElements.begin(),
                                 counts.mNumElements * 0x8c) != counts.mNumElements * 0x8c)
        return false;
    if (((IStream*)stream)->Read(((CreatureData*)data)->mValues.begin(),
                                 counts.mNumValues * 4) != counts.mNumValues * 4)
        return false;
    if (((IStream*)stream)->Read(((CreatureData*)data)->mValueBytes.begin(),
                                 counts.mNumValues) != counts.mNumValues)
        return false;
    if (((IStream*)stream)->Read(((CreatureData*)data)->mScalars.begin(),
                                 counts.mNumFloats * 4) != counts.mNumFloats * 4)
        return false;
    if (((IStream*)stream)->Read(((CreatureData*)data)->mFloats0.begin(),
                                 counts.mNumFloats * 4) != counts.mNumFloats * 4)
        return false;
    if (((IStream*)stream)->Read(((CreatureData*)data)->mFloats1.begin(),
                                 counts.mNumFloats * 4) != counts.mNumFloats * 4)
        return false;
    if (((IStream*)stream)->Read(&((CreatureData*)data)->mFlags, 4) != 4)
        return false;
    if (header.mVersion >= 10) {
        if (((IStream*)stream)->Read(((CreatureData*)data)->mBones.begin(),
                                     counts.mNumBones * 0x38) != counts.mNumBones * 0x38)
            return false;
    }
    return true;
}

// @ 0x004bf770
bool FUN_004bf770(int* stream, int data)
{
    ChunkHeader header;
    ChunkCounts counts;

    header.mMagic = 0xabb455b7;
    header.mVersion = 10;
    counts.mNumElements = ((CreatureData*)data)->mElements.size();
    counts.mNumValues = ((CreatureData*)data)->mValues.size();
    counts.mNumFloats = ((CreatureData*)data)->mFloats0.size();
    counts.mNumBones = ((CreatureData*)data)->mBones.size();
    if (!((IStream*)stream)->Write(&header, 8)
        || !((IStream*)stream)->Write(&counts, 0x10))
        return false;
    if (!WriteRLE((IStream*)stream, ((CreatureData*)data)->mPayload, 0x80))
        return false;
    if (!((IStream*)stream)->Write(((CreatureData*)data)->mElements.begin(),
                                   counts.mNumElements * 0x8c))
        return false;
    if (!((IStream*)stream)->Write(((CreatureData*)data)->mValues.begin(),
                                   counts.mNumValues * 4))
        return false;
    if (!((IStream*)stream)->Write(((CreatureData*)data)->mValueBytes.begin(),
                                   counts.mNumValues))
        return false;
    if (!((IStream*)stream)->Write(((CreatureData*)data)->mScalars.begin(),
                                   counts.mNumFloats * 4))
        return false;
    if (!((IStream*)stream)->Write(((CreatureData*)data)->mFloats0.begin(),
                                   counts.mNumFloats * 4))
        return false;
    if (!((IStream*)stream)->Write(((CreatureData*)data)->mFloats1.begin(),
                                   counts.mNumFloats * 4))
        return false;
    if (!((IStream*)stream)->Write(&((CreatureData*)data)->mFlags, 4))
        return false;
    if (!((IStream*)stream)->Write(((CreatureData*)data)->mBones.begin(),
                                   counts.mNumBones * 0x38))
        return false;
    return true;
}

// ---------------------------------------------------------------------------
// Editor model (de)serialization entry points.
// ---------------------------------------------------------------------------
extern int WriteBinaryEditorModel(int data);   // 0x4b0010

// 004bfb20 (near-complete; stream header + two data segments)
struct StreamWriter {
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vC();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34();
    virtual bool v38(void* buf, int n);   // +0x38
};
extern bool FUN_004bf0a0(StreamWriter* w, int addr, int n);   // 0x4bf0a0

// @ 0x004bfb20
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

// @ 0x004bf9f0
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
// Both helpers are thiscall entries on the array owner (ecx = this).
struct GrowOps {
    void FUN_004c0bd0(void* end, uint32_t n, void* out);   // 0x4c0bd0
    void FUN_004c0680(void* newBegin, void* end);          // 0x4c0680
};
struct Vec1d8 { int m[4]; void FUN_004c0250(uint32_t count); };
struct Vec8c { int m[4]; void FUN_004c0350(uint32_t count); };
// One 0x8c-byte element worth of scratch (a struct, not a char buffer: retail
// has no /GS cookie here).
struct Elem8cSpare { float f[0x8c / 4]; };
// @ 0x004c0250
void Vec1d8::FUN_004c0250(uint32_t count) {
    int* self = (int*)this;
    if ((uint32_t)((self[2] - self[0]) / 0x1d8) >= count)
        return;
    int* p = count ? (int*)FUN_0042dee0(self + 3, count * 0x1d8, 4, 0) : 0;
    FUN_004b03f0((void*)self[0], (void*)self[1], p);
    int* oldBegin = (int*)self[0];
    self[0] = (int)p;
    self[1] = ((self[1] - (int)oldBegin) / 0x1d8) * 0x1d8 + (int)p;
    self[2] = count * 0x1d8 + self[0];
}

// @ 0x004c0350
void Vec8c::FUN_004c0350(uint32_t count) {
    int* self = (int*)this;
    uint32_t size = (uint32_t)((self[1] - self[0]) / 0x8c);
    if (count > size) {
        // Not enough room: grow into a scratch element first.
        Elem8cSpare spare;
        ((GrowOps*)this)->FUN_004c0bd0((void*)self[1], count - size, &spare);
    } else {
        // Already big enough: only relocate the new tail into place.
        ((GrowOps*)this)->FUN_004c0680((void*)(count * 0x8c + self[0]), (void*)self[1]);
    }
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
