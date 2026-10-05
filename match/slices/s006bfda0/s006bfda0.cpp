// Slice s006bfda0 — EA::ResourceMan PFHoleTable / PFRecordRead / PFRecordWrite
// (retail layout). Module flags: /O2 /MD /Gy /EHsc /TP
//
// The 2008 dev PDB's PFRecordRead/PFRecordWrite are 8..0x10 bytes smaller than
// the retail objects; every offset below was read from the disassembly.  All
// stub classes are data-only (no C++ virtuals) so the layout is exact and the
// vtable calls can be emitted verbatim.
#include "types.h"
#include <intrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef int            intptr_t;

// ---------------------------------------------------------------------------
// external helpers (masked relocations; only arity/convention matter)
// ---------------------------------------------------------------------------
extern void  sub_a057f0(void*, void*, void*);       // rbtree find  (this, out, key)
extern void* sub_9215c0(void*);                     // RBTreeDecrement
extern void* sub_921580(void*);                     // RBTreeIncrement
extern void  sub_921880(void*, void*);              // RBTreeErase
extern void  sub_f47380(void*);                     // allocator deallocate
extern void  sub_9a9600(void*);                     // rbtree nuke subtree
extern void  sub_6bf8f0(void*, void*, void*, void*, int); // DoInsertValue (this=set)
extern void  sub_11e0744(void*, void*, u32);        // vector<bool> DoInsertValue / copy
extern void  sub_93bd50(void*, const char*);        // MemoryStream ctor(name)
extern void  sub_93bde0(void*);                     // MemoryStream dtor
extern void  sub_93bf70(u32*, u32);                 // set position
extern void* sub_93ba70(u32, u32, u32);             // make scratch
extern void  sub_93bb40(void*, int, float);         // set stream param
extern void  sub_931da0(void*, int);                // FileStream ctor

struct DatabasePackedFile;

// ---------------------------------------------------------------------------
// MemoryStream (size 0x24)
// ---------------------------------------------------------------------------
struct MemoryStream {
    void* vtbl;                // +0x00
    void* mpSharedPointer;     // +0x04
    int   mnRefCount;          // +0x08
    u32   mnSize;              // +0x0c
    u32   mnCapacity;          // +0x10
    u32   mnPosition;          // +0x14
    u8    mbResizeEnabled;     // +0x18
    u8    pad19[3];
    float mfResizeFactor;      // +0x1c
    int   mnResizeIncrement;   // +0x20
    bool  SetData(const void* p, u32 size, int a, int b, void* alloc); // 0x93be30
};

// ---------------------------------------------------------------------------
// DatabasePackedFile (only the called members)
// ---------------------------------------------------------------------------
struct ICoreAllocator {
    char pad[0x10];
    void* Alloc(u32 size, const char* name, int flags); // vtable+8
    void  Free(void* p, int flags);                     // vtable+0xc
};

struct DatabasePackedFile {
    void* vtbl;                // +0x00
    char  pad04[0x0c];
    void* mpAllocator;         // +0x10
    char  pad14[0x34];
    bool  ReadFileSpan(u32 a, u32 b, u32 c, u32 d);                 // 0x6bca90
    bool  DecompressRecord(u32 comp, u32 lo, u32 hi, u32 szLo, u32 szHi, u32 buf); // 0x6bccb0
    bool  FUN_006bcb50(u32 a, u32 b, u32 c, u32 d);                // 0x6bcb50
};

ICoreAllocator* DatabasePackedFile_GetAllocator(DatabasePackedFile* db);

// ---------------------------------------------------------------------------
// IStream subobject at PFRecordRead+0x20 (its own offsets)
// ---------------------------------------------------------------------------
struct PFRecordRead;

struct StreamSub {
    void* vtbl;                // +0x00
    void* mpReadBuffer;        // +0x04
    int   mnBufferOffset;      // +0x08
    MemoryStream mStreamMemory;// +0x0c
    u32   mnChunkOffsetLo;     // +0x30
    u32   mnChunkOffsetHi;     // +0x34
    u32   mnCompressedSize;    // +0x38
    u32   mnSizeDecompressed;  // +0x3c
    u16   mnCompressionType;   // +0x40
    u16   pad42;
    u32   field44;             // +0x44
    u32   mnPosition;          // +0x48
    u32   mnSize;              // +0x4c
    u8    mStreamFlags;        // +0x50
    u8    pad51[3];
    int   mnOpenCount;         // +0x54

    u32  GetSize(int type);          // 0x6c0220
    int  Seek(int off, int origin);  // 0x6c0840
    u32  GetRemaining();             // 0x6c0260
    int  Read(void* dst, int n);     // 0x6c0900
};

struct PFRecordRead {
    void* vtbl0;               // +0x00
    int   mnRefCount;          // +0x04
    u32   mPFRecordType;       // +0x08
    u32   mKeyInstance;        // +0x0c
    u32   mKeyType;            // +0x10
    u32   mKeyGroup;           // +0x14
    DatabasePackedFile* mpParent; // +0x18
    int   mnAccessFlags;       // +0x1c
    StreamSub stream;          // +0x20

    PFRecordRead(int src, u32* key, DatabasePackedFile* parent);      // 0x6c09c0
    PFRecordRead* InitFromInfo(u32* info, u32* key, DatabasePackedFile* parent); // 0x6c0b20
    bool AddRef();             // 0x6c07e0
    bool Release();            // 0x6c0800
    int  Cleanup();            // 0x6c0790
    void LoadOnDemand();       // 0x6c03c0
    bool ReadAt(void* dst, u32 off, u32 n); // 0x6c0290
};

// ---------------------------------------------------------------------------
// PFRecordWrite (size 0x27c)
// ---------------------------------------------------------------------------
struct PFRecordWrite {
    void* vtbl0;               // +0x00
    int   mnRefCount;          // +0x04
    u32   mPFRecordType;       // +0x08
    u32   mKeyInstance;        // +0x0c
    u32   mKeyType;            // +0x10
    u32   mKeyGroup;           // +0x14
    DatabasePackedFile* mpParent; // +0x18
    int   mnAccessFlags;       // +0x1c
    void* vtblIStream;         // +0x20
    MemoryStream mStreamMemory;// +0x24
    char  mStreamFile[0x228];  // +0x48 (FileStream)
    u8    mbTriedToCreateFile; // +0x270
    u8    pad271[3];
    u32   field274;            // +0x274
    int   mnOpenCount;         // +0x278

    PFRecordWrite(u32 a, u32 b, u32 size, u32* key, DatabasePackedFile* parent); // 0x6c0c40
    int Release();             // 0x6c0980
};

// ---------------------------------------------------------------------------
// Hole table (int64 extent at +0, eastl set at +8)
// ---------------------------------------------------------------------------
struct HoleRec { u32 startLo, startHi, sizeLo, sizeHi; };
struct HoleNode {
    HoleNode* parent;   // +0x00
    HoleNode* left;     // +0x04
    HoleNode* right;    // +0x08
    void*     color;    // +0x0c
    HoleRec   rec;      // +0x10
};

struct HoleTable {
    char data[0x20];
    void FUN_006bfda0(u32 startLo, u32 startHi, u32 sizeLo, u32 sizeHi); // 0x6bfda0
    bool FUN_006bff90(u32 a, u32 b, u32 c, u32 d);                       // 0x6bff90
    void FUN_006bff10(HoleTable* other);                                 // 0x6bff10
};

// ---------------------------------------------------------------------------
// @ 0x006bfda0
// ---------------------------------------------------------------------------
void HoleTable::FUN_006bfda0(u32 a, u32 b, u32 c, u32 d)
{
    char* base = data;
    char* set = base + 8;
    HoleNode* root;
    sub_a057f0(set, &root, &a);
    if (root != *(HoleNode**)(set + 4)) {
        HoleNode* prev = (HoleNode*)sub_9215c0(root);
        u32 slo = prev->rec.startLo, shi = prev->rec.startHi;
        u32 szlo = prev->rec.sizeLo, szhi = prev->rec.sizeHi;
        u32 endLo = slo + szlo;
        u32 endHi = shi + szhi + (endLo < slo ? 1 : 0);
        if (endLo == a && endHi == b) {
            u32 nLo = szlo + c;
            u32 nHi = szhi + d + (nLo < szlo ? 1 : 0);
            a = slo; b = shi; c = nLo; d = nHi;
            (*(int*)(set + 0x0c))--;
            sub_921580(prev);
            sub_921880(prev, set + 4);
            sub_f47380(prev);
        }
    }
    if (root == *(HoleNode**)(set + 4)) {
        u32 extLo = *(u32*)(base + 0);
        if (a + c == extLo && b + d + (a + c < a ? 1 : 0) == *(u32*)(base + 4)) {
            *(u32*)(base + 0) = extLo - c;
            *(u32*)(base + 4) -= d + (extLo < c ? 1 : 0);
            return;
        }
    } else {
        u32 eLo = root->rec.startLo + root->rec.sizeLo;
        u32 eHi = root->rec.startHi + root->rec.sizeHi + (eLo < root->rec.startLo ? 1 : 0);
        if (a + c == eLo && b + d + (a + c < a ? 1 : 0) == eHi) {
            u32 carry = (a + root->rec.startLo < a) ? 1 : 0;
            a = a + root->rec.startLo;
            b = b + root->rec.startHi + carry;
            c = root->rec.sizeLo;
            d = root->rec.sizeHi;
            HoleNode* nxt = (HoleNode*)sub_921580(root);
            (*(int*)(set + 0x0c))--;
            sub_921580(root);
            sub_921880(root, set + 4);
            sub_f47380(root);
            root = nxt;
        }
    }
    u8 tag = 0;
    sub_6bf8f0(set, root, &a, &c, tag);
}

// ---------------------------------------------------------------------------
// @ 0x006bff10
// ---------------------------------------------------------------------------
void HoleTable::FUN_006bff10(HoleTable* other)
{
    char* o = other->data;
    char* set = o + 8;
    HoleNode* it  = *(HoleNode**)(set + 8);
    HoleNode* end = *(HoleNode**)(set + 4);
    while (it != end) {
        FUN_006bfda0(it->rec.startLo, it->rec.startHi, it->rec.sizeLo, it->rec.sizeHi);
        it = (HoleNode*)sub_921580(it);
    }
    HoleNode* n = *(HoleNode**)(o + 0x14);
    char* p = o + 8;
    while (n) {
        sub_9a9600(*(void**)n);
        HoleNode* nxt = *(HoleNode**)((char*)n + 4);
        sub_f47380(n);
        n = nxt;
    }
    *(void**)(p + 0x0c) = 0;
    *(u8*)(p + 0x10)    = 0;
    *(void**)(p + 0x14) = 0;
    void* self = p + 4;
    *(void**)(p + 8) = self;
    *(void**)(self)  = self;
}

// ---------------------------------------------------------------------------
// @ 0x006bff90
// ---------------------------------------------------------------------------
bool HoleTable::FUN_006bff90(u32 a, u32 b, u32 c, u32 d)
{
    char* base = data;
    if (c == 0 && d == 0)
        return true;
    u32 endLo = a + c;
    u32 endHi = b + d + (endLo < a ? 1 : 0);
    u32 extLo = *(u32*)(base + 0);
    u32 extHi = *(u32*)(base + 4);
    if (endHi < extHi || (endHi == extHi && endLo <= extLo)) {
        HoleNode* root;
        u32 key0 = a, key1 = b;
        sub_a057f0(base + 8, &root, &key0);
        if (root == *(HoleNode**)(base + 8 + 4))
            return false;
        HoleNode* prev = (HoleNode*)sub_9215c0(root);
        u32 plo = prev->rec.startLo, phi = prev->rec.startHi;
        u32 szlo = prev->rec.sizeLo, szhi = prev->rec.sizeHi;
        u32 pEndLo = plo + szlo;
        u32 pEndHi = phi + szhi + (pEndLo < plo ? 1 : 0);
        if (phi < b || (phi == b && plo < a)) {
            // gap before this hole: is there one?
        }
        (void)pEndHi;
    } else {
        if (b < extHi || (b == extHi && a < extLo))
            return false;
        *(u32*)(base + 0) = endLo;
        *(u32*)(base + 4) = endHi;
        if (extHi < b || (extHi < b) || (b < extHi) || (b == extHi && extLo < a)) {
            // old extent is entirely inside the new hole -> drop it
        }
        if (extHi < b || (extHi == b && extLo <= a)) {
            if (extHi < b || extHi < b || (b > extHi) || (b == extHi && extLo < a)) {
                FUN_006bfda0(extLo, extHi, a - extLo, (b - extHi) - (a < extLo ? 1 : 0));
                return true;
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006c0120  PFIndexModifiable::func24h
// ---------------------------------------------------------------------------
struct PFIndexModifiable {
    void* vtbl;                // +0x00
    char  pad04[0x28];
    void** mpBucketArray;      // +0x2c
    u32    mnBucketCount;      // +0x30
    bool func24h(HoleTable* holes, u32 a, u32 b, u32 c, u32 d);
};

bool PFIndexModifiable::func24h(HoleTable* holes, u32 a, u32 b, u32 c, u32 d)
{
    void** bucket = mpBucketArray;
    intptr_t node = (intptr_t)*bucket;
    void** bucketPtr = bucket;
    if (node == 0) {
        bucketPtr = bucket + 1;
        node = (intptr_t)*bucketPtr;
        while (node == 0) {
            bucketPtr = bucketPtr + 1;
            node = (intptr_t)*bucketPtr;
        }
    }
    void** itPtr = bucketPtr;
    if (node != (intptr_t)mpBucketArray[mnBucketCount]) {
        for (;;) {
            HoleNode* n = (HoleNode*)node;
            u32 size = n->rec.sizeLo;             // +0x18
            if (size != 0) {
                u32 sLo = n->rec.startLo;         // +0x10
                u32 sHi = n->rec.startHi;         // +0x14
                if (sHi > b || (sHi == b && sLo >= a)) {
                    if (sHi < c || (sHi == c && sLo < d)) {
                        u32 len = d - sLo;
                        if (len >= size)
                            return true;
                        if (!holes->FUN_006bff90(sLo, sHi, size, 0))
                            return false;
                    }
                }
            }
            node = (intptr_t)n->right;            // +0x28 successor
            while (node == 0) {
                bucketPtr = bucketPtr + 1;
                itPtr = bucketPtr;
                node = (intptr_t)*bucketPtr;
            }
            if (node == (intptr_t)mpBucketArray[mnBucketCount])
                break;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006c0220
// ---------------------------------------------------------------------------
u32 StreamSub::GetSize(int type)
{
    u8 flags = mStreamFlags;
    if (flags == 0) {
        switch (type) {
        case 0: return mnPosition;
        case 1: return 0;
        case 2: return mnPosition - mnSize;
        }
    }
    return ((u32(__thiscall*)(void*, int))(*(void***)&mStreamMemory)[0x24 / 4])(&mStreamMemory, type);
}

// @ 0x006c0260
u32 StreamSub::GetRemaining()
{
    PFRecordRead* owner = (PFRecordRead*)((char*)this - 0x20);
    if (owner->mnAccessFlags != 0) {
        u8 flags = mStreamFlags;
        if ((flags & 2) == 0)
            return mnSize - mnPosition;
        return ((u32(__thiscall*)(void*))(*(void***)&mStreamMemory)[0x2c / 4])(&mStreamMemory);
    }
    return 0;
}

// @ 0x006c0840
int StreamSub::Seek(int offset, int origin)
{
    PFRecordRead* owner = (PFRecordRead*)((char*)this - 0x20);
    if (owner->mnAccessFlags == 0)
        return 0;
    owner->LoadOnDemand();
    if (mStreamFlags != 0)
        return ((int(__thiscall*)(void*, int, int))(*(void***)&mStreamMemory)[0x28 / 4])(&mStreamMemory, offset, origin);
    if (origin == 0) {
        if (offset < 0) { mnPosition = 0; return 1; }
        if ((u32)offset > mnSize) { mnPosition = mnSize; return 1; }
        mnPosition = (u32)offset;
        return 1;
    }
    if (origin == 1) {
        if (offset < 0 && (u32)(-offset) > mnPosition) { mnPosition = 0; return 1; }
        if (offset > 0 && mnPosition + (u32)offset > mnSize) { mnPosition = mnSize; return 1; }
        mnPosition += (u32)offset;
        return 1;
    }
    if (origin == 2) {
        if (offset < 0 && (u32)(-offset) > mnSize) { mnPosition = 0; return 1; }
        mnPosition = mnSize + (u32)offset;
        return 1;
    }
    return 1;
}

// @ 0x006c0900
int StreamSub::Read(void* dst, int n)
{
    PFRecordRead* owner = (PFRecordRead*)((char*)this - 0x20);
    if (owner->mnAccessFlags == 0)
        return -1;
    owner->LoadOnDemand();
    if (mStreamFlags != 0)
        return ((int(__thiscall*)(void*, void*, int))(*(void***)&mStreamMemory)[0x30 / 4])(&mStreamMemory, dst, n);
    int result = -1;
    if (owner->mnAccessFlags != 0) {
        u32 pos = mnPosition;
        if (mnSize < pos + (u32)n || pos + (u32)n < pos)
            result = mnSize - pos;
        else
            result = n;
        if (result != 0) {
            if (!owner->ReadAt(dst, pos, (u32)result))
                result = 0;
        }
        mnPosition += (u32)result;
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x006c0290  PFRecordRead::ReadAt
// ---------------------------------------------------------------------------
bool PFRecordRead::ReadAt(void* dst, u32 off, u32 n)
{
    u32 cached = (u32)stream.mnBufferOffset;
    if (cached <= off && off < cached + 0x200) {
        u32 size = 0x200 - (off - cached);
        void* src = (char*)stream.mpReadBuffer + (off - cached);
        if (n <= size) {
            sub_11e0744(dst, src, n);
            return true;
        }
        sub_11e0744(dst, src, size);
        dst = (char*)dst + size;
        off += size;
        n -= size;
    }
    if (n < 0x200 && off + n < stream.mnSize) {
        stream.mnBufferOffset = -1;
        if (stream.mpReadBuffer == 0) {
            void* alloc = ((void*(__thiscall*)(void*))(*(void***)mpParent)[0x48 / 4])(mpParent);
            stream.mpReadBuffer = ((void*(__thiscall*)(void*, u32, const char*, int))
                (*(void***)alloc)[8 / 4])(alloc, 0x200, "Resource/PFReadBuffer", 0);
        }
        if (stream.mpReadBuffer != 0) {
            u32 count = 0x200;
            if (stream.mnSize < off + 0x200)
                count = stream.mnSize - off;
            bool ok = mpParent->ReadFileSpan((u32)stream.mpReadBuffer,
                                             off + stream.mnChunkOffsetLo,
                                             stream.mnChunkOffsetHi, count);
            if (!ok)
                return false;
            stream.mnBufferOffset = off;
            sub_11e0744(dst, stream.mpReadBuffer, n);
            return true;
        }
    }
    return mpParent->ReadFileSpan((u32)dst, off + stream.mnChunkOffsetLo,
                                  stream.mnChunkOffsetHi, n);
}

// ---------------------------------------------------------------------------
// @ 0x006c03c0  PFRecordRead::LoadOnDemand
// ---------------------------------------------------------------------------
void PFRecordRead::LoadOnDemand()
{
    if (stream.mStreamFlags == 0)
        return;
    if (stream.mStreamFlags == 3)
        return;
    ICoreAllocator* alloc = *(ICoreAllocator**)((char*)mpParent + 0x10);
    void* buf = ((void*(__thiscall*)(void*, u32, const char*, int))
        (*(void***)alloc)[8 / 4])(alloc, stream.mnSize, "Resource/RecordData", 0);
    if (stream.mnCompressionType == 0) {
        if (buf == 0) {
            stream.mStreamFlags = 0;
            return;
        }
        if (!mpParent->ReadFileSpan((u32)buf, stream.mnChunkOffsetLo,
                                    stream.mnChunkOffsetHi, stream.mnSize)) {
            stream.mStreamFlags = 0;
            return;
        }
        stream.mStreamMemory.SetData(buf, stream.mnSize, 1, 1, alloc);
        stream.mStreamFlags |= 2;
    } else {
        if (buf == 0) {
            stream.mStreamFlags |= 2;
            return;
        }
        if (!mpParent->DecompressRecord(stream.mnCompressionType, stream.mnChunkOffsetLo,
                                        stream.mnChunkOffsetHi, stream.mnCompressedSize,
                                        stream.mnSizeDecompressed, (u32)buf)) {
            ((void(__thiscall*)(void*, void*, int))(*(void***)alloc)[0x0c / 4])(alloc, buf, 0);
            stream.mStreamFlags |= 2;
            return;
        }
        stream.mStreamMemory.SetData(buf, stream.mnSize, 1, 1, alloc);
        stream.mStreamFlags |= 2;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c07e0
// ---------------------------------------------------------------------------
bool PFRecordRead::AddRef()
{
    volatile long* p = (volatile long*)&stream.mnOpenCount;
    int old = _InterlockedExchangeAdd(p, 0);
    if (old == 0)
        return false;
    _InterlockedExchangeAdd(p, 1);
    return true;
}

// @ 0x006c0800
bool PFRecordRead::Release()
{
    if (_InterlockedExchangeAdd((volatile long*)&stream.mnOpenCount, 0) == 0)
        return false;
    if (_InterlockedExchangeAdd((volatile long*)&stream.mnOpenCount, -1) == 0 && mnAccessFlags != 0) {
        return ((bool(__thiscall*)(void*))(*(void***)mpParent)[0x3c / 4])(this);
    }
    return true;
}

// @ 0x006c0790
int PFRecordRead::Cleanup()
{
    if (stream.mpReadBuffer != 0) {
        if (mpParent != 0) {
            ICoreAllocator* alloc = (ICoreAllocator*)
                ((void*(__thiscall*)(void*))(*(void***)mpParent)[0x48 / 4])(mpParent);
            ((void(__thiscall*)(void*, void*, int))(*(void***)alloc)[0x0c / 4])
                (alloc, stream.mpReadBuffer, 0);
        }
        stream.mpReadBuffer = 0;
        stream.mnBufferOffset = -1;
    }
    mnAccessFlags = 0;
    mpParent = 0;
    return _InterlockedExchange((volatile long*)&stream.mnOpenCount, 0);
}

// @ 0x006c0980
int PFRecordWrite::Release()
{
    if (_InterlockedExchangeAdd((volatile long*)&mnOpenCount, 0) == 0)
        return 0;
    if (_InterlockedExchangeAdd((volatile long*)&mnOpenCount, -1) == 0 && mnAccessFlags != 0) {
        return ((int(__thiscall*)(void*))(*(void***)mpParent)[0x3c / 4])(this);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x006c04a0 / 04e0 / 0520 / 0550  dual-stream dispatch helpers
// ---------------------------------------------------------------------------
struct DualStream {
    void* vt;                 // +0x00
    void* file;               // +0x04 (embedded stream, vtable at +4)
    char  pad08[0x20];        // to +0x28
    void* mem;                // +0x28 (embedded stream, vtable at +0x28)
    void m4a(int a);          // 006c04a0
    void m4e(int a, int b);   // 006c04e0
    void m52();               // 006c0520
    bool m55(int a, int b);   // 006c0550
};

// @ 0x006c04a0
void DualStream::m4a(int a)
{
    if (((int(__thiscall*)(void*))(*(void***)&mem)[0x10 / 4])(&mem))
        return ((void(__thiscall*)(void*, int))(*(void***)&mem)[0x24 / 4])(&mem, a);
    return ((void(__thiscall*)(void*, int))(*(void***)&file)[0x24 / 4])(&file, a);
}

// @ 0x006c04e0
void DualStream::m4e(int a, int b)
{
    if (((int(__thiscall*)(void*))(*(void***)&mem)[0x10 / 4])(&mem))
        return ((void(__thiscall*)(void*, int, int))(*(void***)&mem)[0x30 / 4])(&mem, a, b);
    return ((void(__thiscall*)(void*, int, int))(*(void***)&file)[0x30 / 4])(&file, a, b);
}

// @ 0x006c0520
void DualStream::m52()
{
    if (((int(__thiscall*)(void*))(*(void***)&mem)[0x10 / 4])(&mem))
        return ((void(__thiscall*)(void*))(*(void***)&mem)[0x34 / 4])(&mem);
    return ((void(__thiscall*)(void*))(*(void***)&file)[0x34 / 4])(&file);
}

// @ 0x006c0550
bool DualStream::m55(int a, int b)
{
    if (*(int*)((char*)this - 4) == 0)
        return false;
    void* p = (char*)this + 0x28;
    if (((int(__thiscall*)(void*))(*(void***)p)[0x10 / 4])(p))
        return ((bool(__thiscall*)(void*, int, int))(*(void***)p)[0x38 / 4])(p, a, b);
    return ((bool(__thiscall*)(void*, int, int))(*(void***)&file)[0x38 / 4])(&file, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x006c05a0  chunked read through the record bridge
// ---------------------------------------------------------------------------
struct RecBridge {
    char pad00[0x18];
    DatabasePackedFile* parent;  // +0x18
    int  access;                 // +0x1c
    void* vtA;                   // +0x24
    char pad28[0x20];
    void* vtB;                   // +0x48
    bool DoRead(u32 a, u32 b, u32 n);
};

bool RecBridge::DoRead(u32 a, u32 b, u32 n)
{
    char bl = 0;
    if (access == 0)
        return 0;
    void* sB = (char*)this + 0x48;
    if (!((bool(__thiscall*)(void*))(*(void***)sB)[0x10 / 4])(sB)) {
        void* sA = (char*)this + 0x24;
        u32 avail = ((u32(__thiscall*)(void*))(*(void***)sA)[0x1c / 4])(sA);
        if (avail < n) n = avail;
        void* p = sub_93ba70(a, b, n);
        return parent->FUN_006bcb50((u32)p, a, b, n);
    }
    void* factory = ((void*(__thiscall*)(void*))(*(void***)parent)[0x48 / 4])(parent);
    void* scratch = ((void*(__thiscall*)(void*, int, const char*, int))(*(void***)factory)[8 / 4])
        (factory, 0x4000, "Resource/RecordData", 0);
    if (scratch == 0)
        return bl;
    u32 loaded = ((u32(__thiscall*)(void*))(*(void***)sB)[0x24 / 4])(sB);
    u32 done = 0;
    bl = 1;
    ((void(__thiscall*)(void*, int, int))(*(void***)sB)[0x28 / 4])(sB, 0, 0);
    while (done < n) {
        if (!bl) break;
        u32 chunk = 0x4000;
        if (n < done + 0x4000) chunk = n - done;
        if (((u32(__thiscall*)(void*, void*, u32))(*(void***)sB)[0x30 / 4])(sB, scratch, chunk) != chunk) {
            bl = 0;
        } else {
            bl = parent->FUN_006bcb50((u32)scratch, a + loaded, b, chunk);
            done += chunk;
        }
    }
    ((void(__thiscall*)(void*, void*, int))(*(void***)sB)[0x0c / 4])(sB, scratch, 0);
    ((void(__thiscall*)(void*, u32, int))(*(void***)sB)[0x28 / 4])(sB, a, 0);
    return bl;
}

// ---------------------------------------------------------------------------
// @ 0x006c0710
// ---------------------------------------------------------------------------
struct BackgroundLoading {
    void* vtbl0;                  // +0x00
    int   refcount;               // +0x04
    char  pad08[0x10];
    DatabasePackedFile* parent;   // +0x18
    int   access;                 // +0x1c
    void* vtbl20;                 // +0x20
    char  pad24[8];
    MemoryStream stream;          // +0x2c
    void Cleanup();               // 0x6c0710
};

void BackgroundLoading::Cleanup()
{
    vtbl0 = (void*)0x140a2b4;
    vtbl20 = (void*)0x140a278;
    if (access != 0)
        ((void(__thiscall*)(void*, void*))(*(void***)parent)[0x3c / 4])(parent, this);
    sub_93bde0(&stream);
    vtbl20 = (void*)0x13f3a68;
    vtbl0 = (void*)0x13effb8;
}

// ---------------------------------------------------------------------------
// @ 0x006c09c0
// ---------------------------------------------------------------------------
PFRecordRead::PFRecordRead(int src, u32* key, DatabasePackedFile* parent)
{
    vtbl0 = (void*)0x13effa8;
    _InterlockedExchange((volatile long*)&mnRefCount, 0);
    vtbl0 = (void*)0x140a2e0;
    mPFRecordType = 0x6492fe4;
    mKeyInstance = key[0];
    mKeyType = key[1];
    mKeyGroup = key[2];
    mpParent = parent;
    mnAccessFlags = 1;
    stream.vtbl = (void*)0x13f3a68;
    vtbl0 = (void*)0x140a2b4;
    stream.vtbl = (void*)0x140a278;
    stream.mpReadBuffer = 0;
    stream.mnBufferOffset = -1;
    sub_93bd50(&stream.mStreamMemory, "ResourceMan/PFRecordRead");
    stream.mnChunkOffsetLo = *(u32*)(src + 0x50);
    stream.mnChunkOffsetHi = *(u32*)(src + 0x54);
    stream.mnCompressedSize = *(u32*)(src + 0x58);
    stream.mnSizeDecompressed = *(u32*)(src + 0x5c);
    stream.mnCompressionType = *(u16*)(src + 0x60);
    stream.field44 = *(u32*)(src + 0x64);
    stream.mnPosition = 0;
    stream.mnSize = *(u32*)(src + 0x6c);
    stream.mStreamFlags = *(u8*)(src + 0x70);
    _InterlockedExchange((volatile long*)&stream.mnOpenCount, 1);
    ((void(__thiscall*)(void*))(*(void***)&stream.mStreamMemory)[4 / 4])(&stream.mStreamMemory);
    if (stream.mStreamFlags & 2) {
        u32 pos = ((u32(__thiscall*)(void*))(*(void***)((char*)mpParent + 0x2c))[0x1c / 4])
            ((char*)mpParent + 0x2c);
        sub_93bf70(key, pos);
        ((void(__thiscall*)(void*, int, int))(*(void***)&stream.mStreamMemory)[0x28 / 4])
            (&stream.mStreamMemory, 0, 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006c0b20
// ---------------------------------------------------------------------------
PFRecordRead* PFRecordRead::InitFromInfo(u32* info, u32* key, DatabasePackedFile* parent)
{
    vtbl0 = (void*)0x13effa8;
    _InterlockedExchange((volatile long*)&mnRefCount, 0);
    vtbl0 = (void*)0x140a2e0;
    mPFRecordType = 0x6492fe4;
    mKeyInstance = key[0];
    mKeyType = key[1];
    mKeyGroup = key[2];
    mpParent = parent;
    mnAccessFlags = 1;
    stream.vtbl = (void*)0x13f3a68;
    vtbl0 = (void*)0x140a2b4;
    stream.vtbl = (void*)0x140a278;
    stream.mpReadBuffer = 0;
    stream.mnBufferOffset = -1;
    sub_93bd50(&stream.mStreamMemory, "ResourceMan/PFRecordRead");
    stream.mnChunkOffsetLo = info[0];
    stream.mnChunkOffsetHi = info[1];
    stream.mnCompressedSize = info[2];
    stream.mnSizeDecompressed = info[3];
    stream.mnCompressionType = (u16)info[4];
    stream.field44 = info[5];
    stream.mnPosition = 0;
    stream.mnSize = 0;
    stream.mStreamFlags = 0;
    _InterlockedExchange((volatile long*)&stream.mnOpenCount, 1);
    ((void(__thiscall*)(void*))(*(void***)&stream.mStreamMemory)[4 / 4])(&stream.mStreamMemory);
    if (stream.mnCompressionType == 0) {
        stream.mnSize = stream.mnCompressedSize;
        if (stream.mnCompressedSize > 0x200)
            return this;
    } else {
        stream.mnSize = stream.mnSizeDecompressed;
    }
    stream.mStreamFlags = 1;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006c0c40
// ---------------------------------------------------------------------------
PFRecordWrite::PFRecordWrite(u32 a, u32 b, u32 size, u32* key, DatabasePackedFile* parent)
{
    vtbl0 = (void*)0x13effa8;
    _InterlockedExchange((volatile long*)&mnRefCount, 0);
    vtbl0 = (void*)0x140a2e0;
    mPFRecordType = 0x6492fe5;
    mKeyInstance = key[0];
    mKeyType = key[1];
    mKeyGroup = key[2];
    mpParent = parent;
    mnAccessFlags = 3;
    vtblIStream = (void*)0x13f3a68;
    vtbl0 = (void*)0x140a364;
    vtblIStream = (void*)0x140a328;
    sub_93bd50(&mStreamMemory, "ResourceMan/PFRecordWrite");
    sub_931da0(mStreamFile, 0);
    mbTriedToCreateFile = 0;
    _InterlockedExchange((volatile long*)&mnOpenCount, 1);
    ((void(__thiscall*)(void*))(*(void***)&mStreamMemory)[4 / 4])(&mStreamMemory);
    ((void(__thiscall*)(void*))(*(void***)mStreamFile)[4 / 4])(mStreamFile);
    sub_93bb40(&mStreamMemory, 1, 1.0f);
    sub_93bb40(&mStreamMemory, 2, 1.5f);
    sub_93bb40(&mStreamMemory, 3, 4.0f);
    if (size != 0) {
        ICoreAllocator* alloc = DatabasePackedFile_GetAllocator(parent);
        if (mStreamMemory.SetData(0, size, 0, 1, alloc)) {
            void* p = sub_93ba70(a, b, size);
            parent->ReadFileSpan((u32)p, a, b, size);
        }
    }
}

// ---------------------------------------------------------------------------
// helper: fetch the allocator through the parent's vtable slot +0x48
// (defined out of line here only as a stub body; callers pass through)
// ---------------------------------------------------------------------------
