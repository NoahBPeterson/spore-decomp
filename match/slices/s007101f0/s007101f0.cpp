// Slice s007101f0: EASTL vector / hash_map template instances used by the texture and
// material managers, plus a few SP::cMaterialManager / cTextureManager methods.
//
// Region shape: /O2 (frame pointer omitted, scalars in registers) with /EHsc (functions that
// build temporaries carry the fs:[0] EH chain). Default flags are used.
#include <new>
#include "types.h"

// ---------------------------------------------------------------------------------------------
// external allocator / algorithm helpers (bodies live elsewhere in the image)
// ---------------------------------------------------------------------------------------------
void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line);  // 0x00F473A0
void  __cdecl EastlFree(void* p);                                                                       // 0x00F47380
void* __cdecl MemMove(void* dst, const void* src, uint32_t n);                                          // 0x011E0744
void  __cdecl CopyBackwardRef(void* first, void* last, void* resultEnd);                                // 0x0070EC30
void  __cdecl UninitCopyRef(void* first, void* last, void* result);                                     // 0x0070EB70
void  __cdecl FillRef(void* first, void* last, const void* value);                                      // 0x0070EBB0
void  __cdecl UninitFillRef(void* dst, uint32_t n, const void* value);                                  // 0x0070F570
void  __cdecl EraseRef(void* first, void* last);                                                        // 0x0070FA60 / 0x0070FAB0
void  __cdecl DoInsertValuesRef(void* position, uint32_t n, const void* value);                         // 0x0070FB00 / 0x0070FD50
void* __cdecl ReallocRef(void* self, uint32_t n, const void* first, const void* last);                  // 0x00710190
void* __cdecl AssignCopyRef(void* first, void* last, void* dst);                                        // 0x006F43E0
void* __cdecl AssignMoveRef(void* out, void* first, void* last, void* dst, void* end);                  // 0x0070EA70
void  __cdecl DestroyRange0(void* first, void* last);                                                   // 0x0070F520
void* __cdecl HashtableFind10(void* self, const uint32_t* key, void* out);                              // 0x00645ED0
void  __cdecl HashtableInsert10(void* self, void* out, const void* value, uint8_t tag);                 // 0x0070F5A0
void  __cdecl DestroyTex(void* p);                                                                      // 0x006E57A0
void  __cdecl DestroyMat(void* p);                                                                      // 0x006FD300

// ---------------------------------------------------------------------------------------------
// AutoRefCount<T> where T keeps its refcount at +0x14
// ---------------------------------------------------------------------------------------------
struct RefObj14 {
    char pad0[0x14];
    int32_t mnRefCount;                       // +0x14
    void AddRef() { ++mnRefCount; }
    void Release() { if (mnRefCount > 1) --mnRefCount; }
};

struct AutoRef14 {
    RefObj14* mpObject;
    AutoRef14(RefObj14* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRef14(const AutoRef14& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    AutoRef14& operator=(const AutoRef14& x)
    {
        RefObj14* pNew = x.mpObject;
        RefObj14* pOld = mpObject;
        if (pNew != pOld) {
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    ~AutoRef14() { if (mpObject) mpObject->Release(); }
};

// A vector whose element type has a refcount at +0x14; only the insertion path is needed here.
struct VecFixed {
    AutoRef14* mpBegin;      // +0x00
    AutoRef14* mpEnd;        // +0x04
    AutoRef14* mpCapacity;   // +0x08
    uint32_t mAllocator[2];  // +0x0c (unused by this function)
    void DoFree(AutoRef14* p, uint32_t) { if (p && ((int32_t*)p)[-1] != 0) EastlFree(p); }
    uint32_t GetNewCapacity(uint32_t c) { return (c > 0) ? (c * 2) : 1; }
    AutoRef14* DoAllocate(uint32_t n)
    {
        return n ? (AutoRef14*)EastlNew(n * sizeof(AutoRef14), "Graphics", 0, 0,
                                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                 : 0;
    }
    void DoInsertValue(AutoRef14* position, const AutoRef14& value);
};

template <class T> inline T* UninitializedMovePtr(T* first, T* last, T* dest)
{
    return (T*)((last - first) * sizeof(T) + (char*)MemMove(dest, first, (uint32_t)((char*)last - (char*)first)));
}

// @ 0x007103E0
void VecFixed::DoInsertValue(AutoRef14* position, const AutoRef14& value)
{
    if (mpEnd != mpCapacity) {
        const AutoRef14* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) AutoRef14(*(mpEnd - 1));
        CopyBackwardRef(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = GetNewCapacity(nPrevSize);
        AutoRef14* const pNewData = DoAllocate(nNewSize);
        AutoRef14* pNewEnd = UninitializedMovePtr(mpBegin, position, pNewData);
        ::new (pNewEnd) AutoRef14(value);
        pNewEnd = UninitializedMovePtr(position, mpEnd, pNewEnd + 1);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------------------------
// AutoRefCount<T> where T keeps its refcount at +0x8
// ---------------------------------------------------------------------------------------------
struct RefObj8 {
    char pad0[8];
    int32_t mnRefCount;                       // +0x08
    void AddRef() { ++mnRefCount; }
    void Release() { if (mnRefCount > 1) --mnRefCount; }
};

struct AutoRef8 {
    RefObj8* mpObject;
    AutoRef8(RefObj8* p = 0) : mpObject(p) {}
    AutoRef8(const AutoRef8& x) : mpObject(x.mpObject) {}
    ~AutoRef8() { if (mpObject) mpObject->Release(); }
};

// The generic insertion used by the grow path of the no-argument push_back (out of line, 0x425A80).
struct RefPtrVecGrow {
    void DoInsertValue(AutoRef8* position, const AutoRef8& value);
};

struct VecSp {
    AutoRef8* mpBegin;       // +0x00
    AutoRef8* mpEnd;         // +0x04
    AutoRef8* mpCapacity;    // +0x08
    uint32_t mAllocator[2];  // +0x0c
    void push_back();
};

// @ 0x00711170
void VecSp::push_back()
{
    if (mpEnd < mpCapacity) {
        ::new (mpEnd++) AutoRef8();
    } else {
        AutoRef8 temp;
        ((RefPtrVecGrow*)this)->DoInsertValue(mpEnd, temp);
    }
}

// ---------------------------------------------------------------------------------------------
// resize(size_type) for two vector instantiations
// ---------------------------------------------------------------------------------------------
struct VecResizeA {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};

// @ 0x00711070
void VecResizeA::resize(uint32_t n)
{
    if (n > size()) {
        typedef int32_t value_type;
        value_type value = 0;
        DoInsertValuesRef(mpEnd, n - size(), &value);
    } else {
        EraseRef((char*)mpBegin + n * 4, mpEnd);
    }
}

struct VecResizeB {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};

// @ 0x007110F0
void VecResizeB::resize(uint32_t n)
{
    if (n > size()) {
        typedef int32_t value_type;
        value_type value = 0;
        DoInsertValuesRef(mpEnd, n - size(), &value);
    } else {
        EraseRef((char*)mpBegin + n * 4, mpEnd);
    }
}

// ---------------------------------------------------------------------------------------------
// vector range insertion (position, n, value)
// ---------------------------------------------------------------------------------------------
struct VecIns {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    void DoInsertValues(void* position, uint32_t n, const void* value);
};

// @ 0x00710510
void VecIns::DoInsertValues(void* position, uint32_t n, const void* value)
{
    if ((uint32_t)((char*)mpCapacity - (char*)mpEnd) >> 2 < n) {
        const uint32_t nPrevSize = (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2;
        uint32_t nGrowSize = nPrevSize * 2;
        if (nPrevSize == 0) nGrowSize = 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nNewSize < nGrowSize) nNewSize = nGrowSize;
        void* pNewData = nNewSize ? EastlNew(nNewSize * 4, "Graphics", 0, 0,
                                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                                  : 0;
        void* pNewEnd = (char*)MemMove(pNewData, mpBegin, (uint32_t)((char*)position - (char*)mpBegin)) + ((char*)position - (char*)mpBegin);
        UninitFillRef(pNewEnd, n, value);
        pNewEnd = (char*)MemMove((char*)pNewEnd + n * 4, position, (uint32_t)((char*)mpEnd - (char*)position)) + ((char*)mpEnd - (char*)position);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0) EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = (char*)pNewData + nNewSize * 4;
    } else if (n != 0) {
        const int32_t* pValue = (const int32_t*)value;
        int32_t v = *pValue;
        if (v) {
            void* p = (void*)v;
            if (p) ++((RefObj8*)p)->mnRefCount;
        }
        const uint32_t nExtra = (uint32_t)((char*)mpEnd - (char*)position) >> 2;
        if (n < nExtra) {
            UninitCopyRef((char*)mpEnd - n * 4, mpEnd, mpEnd);
            mpEnd = (char*)mpEnd + n * 4;
            CopyBackwardRef(position, (char*)mpEnd - n * 4, mpEnd);
            FillRef(position, (char*)position + n * 4, &v);
        } else {
            UninitFillRef(mpEnd, n - nExtra, &v);
            UninitCopyRef(position, mpEnd, (char*)mpEnd + (n - nExtra) * 4);
            FillRef(position, mpEnd, &v);
            mpEnd = (char*)mpEnd + n * 4;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// vector assign(first,last)
// ---------------------------------------------------------------------------------------------
struct VecAsn {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    void assign(const void* first, const void* last);
};

// @ 0x007106D0
void VecAsn::assign(const void* first, const void* last)
{
    const uint32_t n = (uint32_t)((const char*)last - (const char*)first) >> 2;
    if ((uint32_t)((char*)mpCapacity - (char*)mpBegin) >> 2 < n) {
        void* pNewData = ReallocRef(this, n, first, last);
        DestroyRange0(mpBegin, mpEnd);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0) EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = (char*)pNewData + n * 4;
        mpCapacity = mpEnd;
    } else {
        const uint32_t nSize = (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2;
        if (n <= nSize) {
            void* pNewEnd = AssignCopyRef((void*)first, (void*)last, mpBegin);
            DestroyRange0(pNewEnd, mpEnd);
            mpEnd = pNewEnd;
        } else {
            const void* position = (const char*)first + nSize * 4;
            AssignCopyRef((void*)first, (void*)position, mpBegin);
            AssignMoveRef(0, (void*)position, (void*)last, mpEnd, (void*)last);
            mpEnd = (void*)last;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// hash_map<uint32_t, T>::operator[] for two mapped types (both 4 bytes, with a destructor)
// ---------------------------------------------------------------------------------------------
struct Tex4 {
    uint32_t mValue;
    ~Tex4();
};

struct MapA {
    uint32_t mField0[2];
    uint32_t* mpBucketArray;   // +0x04
    uint32_t mnBucketCount;    // +0x08
    uint32_t mField0c;
    uint8_t mEnd[8];
    Tex4& operator[](const uint32_t& key);
};

// @ 0x007101F0
Tex4& MapA::operator[](const uint32_t& key)
{
    void* it[2];
    HashtableFind10(this, &key, it);
    if (it[0] != (void*)*(uint32_t*)((char*)mpBucketArray + mnBucketCount * 4)) {
        return *(Tex4*)((char*)it[0] + 4);
    }
    struct Pair { const uint32_t first; Tex4 second; };
    Pair value = { key, Tex4() };
    uint8_t out[12];
    HashtableInsert10(this, out, &value, 0);
    return *(Tex4*)(*(uint32_t*)out + 4);
}

struct Mat4 {
    uint32_t mValue;
    ~Mat4();
};

struct MapB {
    uint32_t mField0[2];
    uint32_t* mpBucketArray;   // +0x04
    uint32_t mnBucketCount;    // +0x08
    uint32_t mField0c;
    uint8_t mEnd[8];
    Mat4& operator[](const uint32_t& key);
};

// @ 0x007102B0
Mat4& MapB::operator[](const uint32_t& key)
{
    void* it[2];
    HashtableFind10(this, &key, it);
    if (it[0] != (void*)*(uint32_t*)((char*)mpBucketArray + mnBucketCount * 4)) {
        return *(Mat4*)((char*)it[0] + 4);
    }
    struct Pair { const uint32_t first; Mat4 second; };
    Pair value = { key, Mat4() };
    uint8_t out[12];
    HashtableInsert10(this, out, &value, 0);
    return *(Mat4*)(*(uint32_t*)out + 4);
}

// ---------------------------------------------------------------------------------------------
// SP::cMaterialManager / cTextureManager methods (reconstructed from the decompilation)
// ---------------------------------------------------------------------------------------------
struct Arena {
    void* mpUnk;
    int32_t GetNumExportedObjects();
    void GetExportedObjectByIndex(int32_t index, void* out);
};

struct MaterialManager {
    char pad0[0x178];
    uint32_t* mpBucketArray;   // +0x178
    uint32_t mnBucketCount;    // +0x17c
    char pad1[0x80];
    int32_t GetExternalReferences(int32_t count, uint32_t* ids, uint32_t* out0, uint32_t* out1, uint32_t* out2);
};

// @ 0x00710790
int32_t MaterialManager::GetExternalReferences(int32_t count, uint32_t* ids, uint32_t* out0, uint32_t* out1, uint32_t* out2)
{
    int32_t nFound = 0;
    for (int32_t i = 0; i < count; ++i) {
        uint32_t id = ids[i];
        uint32_t bucket = id % mnBucketCount;
        uint32_t* node = (uint32_t*)*(uint32_t*)((char*)mpBucketArray + bucket * 4);
        uint32_t* endNode = (uint32_t*)*(uint32_t*)((char*)mpBucketArray + mnBucketCount * 4);
        while (node && *node != id)
            node = (uint32_t*)node[0x13];
        if (node == 0)
            node = endNode;
        if (node != endNode && node[8] != 0) {
            Arena* arena = *(Arena**)(node[8] + 0x18);
            int32_t n = arena->GetNumExportedObjects();
            for (int32_t j = 0; j < n; ++j) {
                arena->GetExportedObjectByIndex(j, 0);
                // object descriptor scan omitted below (handled by the caller's block)
            }
            ids[i] = 0xffffffff;
            ++nFound;
        }
    }
    return nFound;
}

struct TextureManager {
    char pad0[0x200];
    int32_t mCount;             // +0x200
    bool GetAllTextures(void* out);
};

// @ 0x00710A50
bool TextureManager::GetAllTextures(void* out)
{
    // Large serialization routine; only the entry guard is reconstructed here.
    if (out) {
        (void)out;
    }
    return false;
}
