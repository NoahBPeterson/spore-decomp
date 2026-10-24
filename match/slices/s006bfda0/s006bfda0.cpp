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
extern void* sub_9215c0(void*);                     // RBTreeDecrement  (cdecl)
extern void* sub_921580(void*);                     // RBTreeIncrement  (cdecl)
extern void  sub_921880(void*, void*);              // RBTreeErase      (cdecl)
extern void  sub_f47380(void*);                     // allocator deallocate (cdecl)
extern void  sub_9a9600(void*);                     // rbtree nuke subtree
extern void  __fastcall sub_6be890(void*, int, void*, const void*); // lowerBound (set, out, key)
extern void  __fastcall sub_8dae70(void*, int, void*, void*);       // Erase (set, out next, node)
extern void  sub_11e0744(void*, void*, u32);        // memcpy thunk (cdecl)
extern void* sub_93ba70(u32, u32, u32);             // make scratch

// rbtree set at HoleTable+8; find/insert are __thiscall(ret 8)/__thiscall(ret 0x10)
struct RBTreeOps;
RBTreeOps* g_pRBTrees_dummy( void );

// MemoryStream methods (thiscall; declared as members below)
struct MemoryStream;

// thiscall set helpers (ecx = set)
struct RBSet {
    void  Find(void* out, const void* key);                      // 0xa057f0 ret 8
    void  DoInsertValue(void* a, void* node, void* b, u32 tag);  // 0x6bf8f0 ret 0x10
};

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
    void  Init(const char* name);                 // 0x93bd50 ret 4
    void  Destroy();                              // 0x93bde0 ret
    int   Attach(const void* key, u32 pos);       // 0x93bf70 ret 8
    void  SetResize(int mode, float factor);      // 0x93bb40 ret 8
};

// embedded FileStream ctor (thiscall, ret 4)
struct FileStream {
    void Init(int flags);                         // 0x931da0 ret 4
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
    union {
        u32   mnCompressionInfo; // +0x40 (the ctors copy a whole dword)
        u16   mnCompressionType; // +0x40 low word: compression type
    };
    u32   field44;             // +0x44
    u32   mnPosition;          // +0x48
    u32   mnSize;              // +0x4c
    u8    mStreamFlags;        // +0x50
    u8    pad51[3];
    int   mnOpenCount;         // +0x54

    u32  GetSize(int type);          // 0x6c0220
    bool Seek(int off, int origin);  // 0x6c0840
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
// record info the read ctors copy their chunk descriptor from (retail offsets)
struct PFRecordSource {
    u32 pad00[0x0b];               // +0x00
    void* mpStreamVtbl;            // +0x2c (embedded stream's vtable)
    void* mpStreamData;            // +0x30
    u32 pad34[7];                  // +0x34
    u32 mnChunkOffsetLo;           // +0x50
    u32 mnChunkOffsetHi;           // +0x54
    u32 mnCompressedSize;          // +0x58
    u32 mnSizeDecompressed;        // +0x5c
    u32 mnCompressionInfo;         // +0x60 (compression type + pad)
    u32 field64;                   // +0x64
    u32 mnPosition;                // +0x68
    u32 mnSize;                    // +0x6c
    u8  mStreamFlags;              // +0x70
    u8  pad71[3];
};

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
    bool Release();            // 0x6c0980
};

// ---------------------------------------------------------------------------
// Hole table (int64 extent at +0, eastl set at +8)
// ---------------------------------------------------------------------------
struct HoleRec { u32 startLo, startHi, sizeLo, sizeHi; };
struct HoleRange { u32 lo, hi; };
struct HoleNode {
    HoleNode* parent;   // +0x00
    HoleNode* left;     // +0x04
    HoleNode* right;    // +0x08
    void*     color;    // +0x0c
    HoleRec   rec;      // +0x10
};

extern void __fastcall FUN_006bfc20(void* set, int edx, void* out, HoleNode* pos, const HoleRec* rec); // 0x6bfc20 insert hole

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
    HoleRange start = { a, b };
    HoleRange size  = { c, d };
    HoleNode* root;
    ((RBSet*)set)->Find(&root, &start);
    if (root != *(HoleNode**)(set + 4)) {
        HoleNode* prev = (HoleNode*)sub_9215c0(root);
        u32 endLo = prev->rec.startLo + prev->rec.sizeLo;
        u32 endHi = prev->rec.startHi + prev->rec.sizeHi
                  + (endLo < prev->rec.startLo ? 1 : 0);
        if (endLo == start.lo && endHi == start.hi) {
            u32 nLo = prev->rec.sizeLo + size.lo;
            u32 nHi = prev->rec.sizeHi + size.hi + (nLo < prev->rec.sizeLo ? 1 : 0);
            start.lo = prev->rec.startLo;
            start.hi = prev->rec.startHi;
            size.lo = nLo;
            size.hi = nHi;
            (*(int*)(set + 0x0c))--;
            sub_921580(prev);
            sub_921880(prev, set + 4);
            sub_f47380(prev);
        }
    }
    if (root == *(HoleNode**)(set + 4)) {
        u32 extLo = *(u32*)(base + 0);
        if (start.lo + size.lo == extLo &&
            start.hi + size.hi + (start.lo + size.lo < start.lo ? 1 : 0) == *(u32*)(base + 4)) {
            *(u32*)(base + 0) = extLo - size.lo;
            *(u32*)(base + 4) -= size.hi + (extLo < size.lo ? 1 : 0);
            return;
        }
    } else {
        u32 eLo = root->rec.startLo + root->rec.sizeLo;
        u32 eHi = root->rec.startHi + root->rec.sizeHi + (eLo < root->rec.startLo ? 1 : 0);
        if (start.lo + size.lo == eLo &&
            start.hi + size.hi + (start.lo + size.lo < start.lo ? 1 : 0) == eHi) {
            u32 carry = (start.lo + root->rec.startLo < start.lo) ? 1 : 0;
            start.lo = start.lo + root->rec.startLo;
            start.hi = start.hi + root->rec.startHi + carry;
            size.lo = root->rec.sizeLo;
            size.hi = root->rec.sizeHi;
            HoleNode* nxt = (HoleNode*)sub_921580(root);
            (*(int*)(set + 0x0c))--;
            sub_921580(root);
            sub_921880(root, set + 4);
            sub_f47380(root);
            root = nxt;
        }
    }
    ((RBSet*)set)->DoInsertValue(&size, root, &start, size.lo & 0xffffff00u);
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
bool HoleTable::FUN_006bff90(u32 startLo, u32 startHi, u32 sizeLo, u32 sizeHi)
{
    u32* base = (u32*)data;
    if ((sizeLo | sizeHi) == 0)
        return true;

    u32 endLo = startLo + sizeLo;
    u32 endHi = startHi + sizeHi + (endLo < startLo ? 1 : 0);
    u32 extLo = base[0];
    u32 extHi = base[1];
    if (endHi < extHi || (endHi == extHi && endLo <= extLo)) {
        // The range ends inside the current extent: split the hole that
        // contains `start` and re-insert the two remainder ranges around it.
        HoleRec key;
        key.startLo = startLo; key.startHi = startHi;
        key.sizeLo  = sizeLo;  key.sizeHi  = sizeHi;

        HoleNode* node;
        sub_6be890(data + 8, 0, &node, &key);               // 0x6be890 lowerBound
        if (node == *(HoleNode**)(data + 0x10))             // set.end()
            return false;

        HoleNode* prev = (HoleNode*)sub_9215c0(node);       // RBTreeDecrement
        u32 plo   = prev->rec.startLo;
        u32 phi   = prev->rec.startHi;
        u32 pEndLo = plo + prev->rec.sizeLo;
        u32 pEndHi = phi + prev->rec.sizeHi + (pEndLo < plo ? 1 : 0);

        HoleNode* erased;
        sub_8dae70(data + 8, 0, &erased, prev);             // erase prev -> next

        if (phi < startHi || (phi == startHi && plo < startLo)) {
            // [prevStart, start) stays free.
            HoleRec gap;
            gap.startLo = plo;
            gap.startHi = phi;
            gap.sizeLo  = startLo - plo;
            gap.sizeHi  = (startHi - phi) - (startLo < plo ? 1 : 0);
            FUN_006bfc20(data + 8, 0, &erased, node, &gap); // 0x6bfc20 insert
        }
        if (endHi < pEndHi || (endHi == pEndHi && endLo < pEndLo)) {
            // [end, prevEnd) stays free.
            HoleRec gap;
            gap.startLo = endLo;
            gap.startHi = endHi;
            gap.sizeLo  = pEndLo - endLo;
            gap.sizeHi  = (pEndHi - endHi) - (pEndLo < endLo ? 1 : 0);
            FUN_006bfc20(data + 8, 0, &node, node, &gap);   // 0x6bfc20 insert
        }
    } else {
        // The range extends past the current extent.
        if (startHi < extHi || (startHi == extHi && startLo < extLo))
            return false;
        base[0] = endLo;
        base[1] = endHi;
        if (startHi > extHi || (startHi == extHi && startLo > extLo))
            FUN_006bfda0(extLo, extHi, startLo - extLo,
                         (startHi - extHi) - (startLo < extLo ? 1 : 0));
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

// eastl hashtable node seen while walking the bucket array
struct HashNode {
    u32      pad00[4];         // +0x00
    u32      startLo;          // +0x10
    u32      startHi;          // +0x14
    u32      sizeLo;           // +0x18
    u32      sizeHi;           // +0x1c
    u32      pad20[2];         // +0x20
    HashNode* next;            // +0x28
};

bool PFIndexModifiable::func24h(HoleTable* holes, u32 a, u32 b, u32 c, u32 d)
{
    HashNode* node = (HashNode*)*mpBucketArray;
    void** bucketPtr = mpBucketArray;
    if (node == 0) {
        bucketPtr = mpBucketArray + 1;
        node = (HashNode*)*bucketPtr;
        while (node == 0) {
            bucketPtr = bucketPtr + 1;
            node = (HashNode*)*bucketPtr;
        }
    }
    if (node == (HashNode*)mpBucketArray[mnBucketCount])
        return true;
    for (;;) {
        u32 size = node->sizeLo;
        if (size != 0) {
            u32 sLo = node->startLo;
            u32 sHi = node->startHi;
            if (!(sHi >= b && (sHi > b || sLo >= a)))
                return false;
            if (!(sHi <= d && (sHi < d || sLo < c)))
                return false;
            u32 lenLo = c - sLo;
            u32 lenHi = d - sHi - (c < sLo ? 1u : 0u);
            if (lenHi == 0 && size > lenLo)
                return false;
            if (!holes->FUN_006bff90(sLo, sHi, size, 0))
                return false;
        }
        node = node->next;
        if (node == 0) {
            do {
                bucketPtr = bucketPtr + 1;
                node = (HashNode*)*bucketPtr;
            } while (node == 0);
        }
        if (node == (HashNode*)mpBucketArray[mnBucketCount])
            break;
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
bool StreamSub::Seek(int offset, int origin)
{
    PFRecordRead* owner = (PFRecordRead*)((char*)this - 0x20);
    if (owner->mnAccessFlags == 0)
        return false;
    owner->LoadOnDemand();
    if (mStreamFlags != 0)
        return ((bool(__thiscall*)(void*, int, int))(*(void***)&mStreamMemory)[0x28 / 4])(&mStreamMemory, offset, origin);
    if (origin == 0) {
        if (offset < 0) { mnPosition = 0; return true; }
        if ((u32)offset > mnSize) { mnPosition = mnSize; return true; }
        mnPosition = (u32)offset;
        return true;
    }
    if (origin == 1) {
        if (offset < 0 && (u32)(-offset) > mnPosition) { mnPosition = 0; return true; }
        if (offset > 0 && mnPosition + (u32)offset > mnSize) { mnPosition = mnSize; return true; }
        mnPosition += (u32)offset;
        return true;
    }
    if (origin == 2) {
        if (offset >= 0) { mnPosition = mnSize; return true; }
        if ((u32)(-offset) > mnSize) { mnPosition = 0; return true; }
        mnPosition = mnSize + (u32)offset;
        return true;
    }
    return true;
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
            u32 chunkLo = off + stream.mnChunkOffsetLo;
            u32 chunkHi = stream.mnChunkOffsetHi + (chunkLo < off ? 1u : 0u);
            bool ok = mpParent->ReadFileSpan((u32)stream.mpReadBuffer,
                                             chunkLo, chunkHi, count);
            if (!ok)
                return false;
            stream.mnBufferOffset = off;
            sub_11e0744(dst, stream.mpReadBuffer, n);
            return true;
        }
    }
    u32 spanLo = off + stream.mnChunkOffsetLo;
    u32 spanHi = stream.mnChunkOffsetHi + (spanLo < off ? 1u : 0u);
    return mpParent->ReadFileSpan((u32)dst, spanLo, spanHi, n);
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
    if (_InterlockedExchangeAdd((volatile long*)&stream.mnOpenCount, -1) == 1 && mnAccessFlags != 0) {
        return ((bool(__thiscall*)(void*, void*))(*(void***)mpParent)[0x3c / 4])(mpParent, this);
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
bool PFRecordWrite::Release()
{
    if (_InterlockedExchangeAdd((volatile long*)&mnOpenCount, 0) == 0)
        return false;
    if (_InterlockedExchangeAdd((volatile long*)&mnOpenCount, -1) == 1 && mnAccessFlags != 0) {
        return ((bool(__thiscall*)(void*, void*))(*(void***)mpParent)[0x3c / 4])(mpParent, this);
    }
    return true;
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
    stream.Destroy();
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
    stream.mStreamMemory.Init("ResourceMan/PFRecordRead");
    PFRecordSource* info = (PFRecordSource*)src;
    stream.mnChunkOffsetLo = info->mnChunkOffsetLo;
    stream.mnChunkOffsetHi = info->mnChunkOffsetHi;
    stream.mnCompressedSize = info->mnCompressedSize;
    stream.mnSizeDecompressed = info->mnSizeDecompressed;
    stream.mnCompressionInfo = info->mnCompressionInfo;
    stream.field44 = info->field64;
    stream.mnPosition = 0;
    stream.mnSize = info->mnSize;
    stream.mStreamFlags = info->mStreamFlags;
    _InterlockedExchange((volatile long*)&stream.mnOpenCount, 1);
    ((void(__thiscall*)(void*))(*(void***)&stream.mStreamMemory)[4 / 4])(&stream.mStreamMemory);
    if (stream.mStreamFlags & 2) {
        u32 pos = ((u32(__thiscall*)(void*))(*(void***)&info->mpStreamVtbl)[0x1c / 4])(&info->mpStreamVtbl);
        stream.mStreamMemory.Attach(info->mpStreamData, pos);
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
    stream.mStreamMemory.Init("ResourceMan/PFRecordRead");
    stream.mnChunkOffsetLo = info[0];
    stream.mnChunkOffsetHi = info[1];
    stream.mnCompressedSize = info[2];
    stream.mnSizeDecompressed = info[3];
    stream.mnCompressionInfo = info[4];
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
    mStreamMemory.Init("ResourceMan/PFRecordWrite");
    ((FileStream*)mStreamFile)->Init(0);
    mbTriedToCreateFile = 0;
    _InterlockedExchange((volatile long*)&mnOpenCount, 1);
    ((void(__thiscall*)(void*))(*(void***)&mStreamMemory)[4 / 4])(&mStreamMemory);
    ((void(__thiscall*)(void*))(*(void***)mStreamFile)[4 / 4])(mStreamFile);
    mStreamMemory.SetResize(1, 1.0f);
    mStreamMemory.SetResize(2, 1.5f);
    mStreamMemory.SetResize(3, 4.0f);
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
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
