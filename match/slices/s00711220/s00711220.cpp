// Slice s00711220: SP::cMaterialManager serialization/cache helpers and a few EASTL container
// helpers (vector::resize, hashtable::DoFreeNodes, hashtable erase). /O2 /MD /Gy /EHsc /TP /GS-.
#include <new>
#include "types.h"

void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line);  // 0xF473A0
void  __cdecl EastlFree(void* p);                                                                       // 0xF47380
void* __cdecl AssignCopyRef(void* first, void* last, void* dst);                                        // 0x006F43E0
void  __cdecl DestroyRange(void* first, void* last);                                                    // 0x0070F520
void  __cdecl DoInsertValuesRef(void* position, uint32_t n, const void* value);                         // 0x0070FFA0
void  __cdecl WriteUint32(void* out, const void* value, int n, int flags);                              // 0x0093AA70
void  __cdecl WriteUint16(void* out, const void* value, int n, int flags);                              // 0x0093A9D0
int   __cdecl ReadInt32(void* in, void* out, int n, int flags);                                         // 0x0093A700 area
void  __cdecl MutexLock(void* mutex, const void* params);                                               // 0x009221B0
void  __cdecl MutexUnlock(void* mutex);                                                                 // 0x00922270
void  __cdecl ReleaseObject(void* p);                                                                   // 0x00761170

// ---------------------------------------------------------------------------------------------
// vector<AutoRefCount<T>>::resize(uint32_t): inlined resize(n, value_type())
// ---------------------------------------------------------------------------------------------
struct VecResize {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};

// @ 0x00711220
void VecResize::resize(uint32_t n)
{
    if (n > size()) {
        int32_t value = 0;
        DoInsertValuesRef(mpEnd, n - size(), &value);
    } else {
        void* first = (char*)mpBegin + n * 4;
        void* pNewEnd = AssignCopyRef(mpEnd, mpEnd, first);
        DestroyRange(pNewEnd, mpEnd);
        mpEnd = (char*)mpEnd - (uint32_t)((char*)mpEnd - (char*)first);
    }
}

// ---------------------------------------------------------------------------------------------
// hashtable::DoFreeNodes
// ---------------------------------------------------------------------------------------------
struct FreeNode {
    int32_t m0;            // +0x00
    int32_t m4;            // +0x04
    int32_t m8;            // +0x08
    char pad[0x20 - 0x0c];
    FreeNode* mpNext;      // +0x20
};

// @ 0x007112C0
void __stdcall DoFreeNodes(FreeNode** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        FreeNode* pNode = pNodeArray[i];
        while (pNode) {
            FreeNode* pNext = pNode->mpNext;
            if (pNode->m8 - pNode->m0 > 1 && pNode->m0 != 0)
                EastlFree((void*)pNode->m0);
            EastlFree(pNode);
            pNode = pNext;
        }
        pNodeArray[i] = 0;
    }
}

// ---------------------------------------------------------------------------------------------
// container clear helper (fixed array of pointers + tail vector), returns to a zeroed state
// ---------------------------------------------------------------------------------------------
struct FixedClear {
    uint8_t mCount;            // +0x00
    char pad0[3];
    void* mItems[6];           // +0x04 .. +0x1b
    int32_t mFlag1c;           // +0x1c
    void* mpBegin;             // +0x20
    void* mpEnd;               // +0x24
    void clear();
};

// @ 0x00711380
void FixedClear::clear()
{
    if (mFlag1c == 0) {
        for (int i = 0; i < (int)mCount; ++i) {
            ReleaseObject(mItems[i]);
            mItems[i] = 0;
        }
    } else {
        mFlag1c = 0;
    }
    void* pNewEnd = AssignCopyRef(mpEnd, mpEnd, mpBegin);
    DestroyRange(pNewEnd, mpEnd);
    mpEnd = (char*)mpEnd - ((char*)mpEnd - (char*)mpBegin);
    mCount = 0;
}

// ---------------------------------------------------------------------------------------------
// SP::cMaterialManager::GetTexturesFromMaterial(material, outVec, filter)
// ---------------------------------------------------------------------------------------------
struct TextureVec {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    void* DoInsertValue();           // 0x00711170: appends a null element
};
struct TextureRef {
    char pad0[8];
    int32_t mnRefCount;             // +0x08
};

// @ 0x00711400
void __stdcall GetTexturesFromMaterial(void* material, TextureVec* outVec, bool (__cdecl* filter)(void*))
{
    void** it = *(void***)((char*)material + 0x20);
    void** end = *(void***)((char*)material + 0x24);
    while (it != end) {
        TextureRef* tex = (TextureRef*)*it;
        if (tex != 0 && (filter == 0 || filter(tex))) {
            outVec->DoInsertValue();
            TextureRef** slot = (TextureRef**)((char*)outVec->mpEnd - 4);
            TextureRef* old = *slot;
            if (tex != old)
                *slot = tex;
        }
        ++it;
    }
}

// ---------------------------------------------------------------------------------------------
// SP::cMaterialManager serialization helpers (reconstructed; large, guarded by the mMutex)
// ---------------------------------------------------------------------------------------------
struct Arena {
    int32_t GetNumExportedObjects();
    void GetExportedObjectByIndex(int32_t index, void* out);
};

struct MaterialManagerBig {
    char pad0[0x178];
    uint32_t* mpBucketArray;     // +0x178
    uint32_t mnBucketCount;      // +0x17c
    char pad1[0x78];
    char mMutex[0x40];           // +0x258
    int32_t GetExternalReferences(int32_t n, uint32_t* ids, void* out0, void* out1, void* out2);
    int32_t WriteExternalReferences(void* stream, int32_t n, uint32_t* ids);
    int32_t GetExternalReferenceKeys(void* stream, int32_t n, uint32_t* ids, TextureVec* out);
    int32_t ReadMaterials(void* stream, int32_t n, uint32_t* ids, void* out0, void* out1);
    void UnregisterArenaContents(void* arena);
    void RemoveAllRegisteredMaterials();
};

// @ 0x00711490
int32_t MaterialManagerBig::WriteExternalReferences(void* stream, int32_t n, uint32_t* ids)
{
    MutexLock(mMutex, 0);
    uint8_t buffer[0x100];
    uint8_t* p = buffer;
    int32_t count = GetExternalReferences(n, ids, &p, 0, 0);
    WriteUint32(stream, &count, 1, 0);
    int32_t cnt = (int32_t)((uint8_t*)p - buffer) >> 4;
    for (int32_t i = 0; i < cnt; ++i) {
        WriteUint32(stream, buffer + i * 16, 1, 0);
        uint32_t v16 = *(uint16_t*)(buffer + i * 16 + 4);
        WriteUint16(stream, &v16, 1, 0);
        WriteUint32(stream, buffer + i * 16 + 8, 1, 0);
        WriteUint32(stream, buffer + i * 16 + 12, 1, 0);
    }
    EastlFree(buffer);
    MutexUnlock(mMutex);
    return count;
}

// @ 0x00711630
int32_t MaterialManagerBig::GetExternalReferenceKeys(void* stream, int32_t n, uint32_t* ids, TextureVec* out)
{
    MutexLock(mMutex, 0);
    uint8_t buffer[0x100];
    uint8_t* p = buffer;
    int32_t count = GetExternalReferences(n, ids, &p, 0, 0);
    int32_t cnt = (int32_t)((uint8_t*)p - buffer) >> 4;
    for (int32_t i = 0; i < cnt; ++i) {
        uint32_t a = *(uint32_t*)(buffer + i * 16 + 12);
        uint32_t b = *(uint32_t*)(buffer + i * 16 + 8);
        (void)out; (void)a; (void)b;
    }
    EastlFree(buffer);
    MutexUnlock(mMutex);
    return count;
}

// @ 0x00711780
int32_t MaterialManagerBig::ReadMaterials(void* stream, int32_t n, uint32_t* ids, void* out0, void* out1)
{
    MutexLock(mMutex, 0);
    int32_t count = 0;
    if (ReadInt32(stream, &count, 1, 0) == 0 || count > 199) {
        MutexUnlock(mMutex);
        return -1;
    }
    if (count == 0) {
        MutexUnlock(mMutex);
        return 0;
    }
    int32_t result = 0;
    for (int32_t i = 0; i < count; ++i) {
        uint32_t a = 0, b = 0, c = 0, d = 0;
        if (ReadInt32(stream, &a, 1, 0) == 0) { result = -1; break; }
        if (ReadInt32(stream, &b, 1, 0) == 0) { result = -1; break; }
        if (ReadInt32(stream, &c, 1, 0) == 0) { result = -1; break; }
        if (ReadInt32(stream, &d, 1, 0) == 0) { result = -1; break; }
    }
    (void)ids; (void)out0; (void)out1;
    MutexUnlock(mMutex);
    return result;
}

// @ 0x00711b80
void MaterialManagerBig::UnregisterArenaContents(void* arena)
{
    MutexLock(mMutex, 0);
    int32_t n = ((Arena*)arena)->GetNumExportedObjects();
    for (int32_t i = 0; i < n; ++i) {
        (void)i;
    }
    MutexUnlock(mMutex);
}

// @ 0x00711D10
void MaterialManagerBig::RemoveAllRegisteredMaterials()
{
    MutexLock(mMutex, 0);
    uint32_t* node = (uint32_t*)*mpBucketArray;
    uint32_t* pRangeEnd = (uint32_t*)mpBucketArray[mnBucketCount];
    if (node == 0) {
        uint32_t* bucket = mpBucketArray;
        do { ++bucket; } while (*bucket == 0);
        node = (uint32_t*)*bucket;
    }
    while (node != pRangeEnd) {
        if (node[0x20 / 4] == 0) {
            if (mpBucketArray[0x204 / 4 - 0x178 / 4] == 0)
                ((FixedClear*)(node + 1))->clear();
            node[8 / 4] = mpBucketArray[0x1b4 / 4 - 0x178 / 4];
        }
        node = (uint32_t*)node[0x4c / 4];
        while (node == 0) {
            ++mpBucketArray;
            node = (uint32_t*)*mpBucketArray;
        }
    }
    MutexUnlock(mMutex);
}
