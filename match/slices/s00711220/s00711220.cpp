// Slice s00711220: SP::cMaterialManager serialization/cache helpers and a few EASTL container
// helpers (vector::resize, hashtable::DoFreeNodes, hashtable erase). /O2 /MD /Gy /EHsc /TP /GS-.
#include <new>
#include <intrin.h>
#include "types.h"

void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line);  // 0xF473A0
void  __cdecl EastlFree(void* p) throw();                                                                     // 0xF47380
void* __cdecl AssignCopyRef(void* first, void* last, void* dst);                                        // 0x006F43E0
void  __cdecl ReleaseObject(void* p);                                                                   // 0x00761170

// ---------------------------------------------------------------------------------------------
// vector<AutoRefCount<T>>::resize(uint32_t): inlined resize(n, value_type())
// ---------------------------------------------------------------------------------------------
struct VecResize {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    uint32_t size() const {
        return (uint32_t)(((int32_t)((char*)mpEnd - (char*)mpBegin)) >> 2);
    }
    void resize(uint32_t n);
    void DestroyRange(void** first, void** last);   // 0x0070F520 (thiscall, ret 8)
    void DoInsertValuesRef(void* position, uint32_t n, const void* value); // 0x0070FFA0 (ecx=vector, ret 0xc)
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
        DestroyRange((void**)pNewEnd, (void**)mpEnd);
        void** pEnd = (void**)mpEnd;
        void** pFirst = (void**)first;
        mpEnd = (void*)(pEnd - (pEnd - pFirst));
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
struct VecBase {
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCapacity; // +0x08
    void DestroyRange(void** first, void** last);   // 0x0070F520
};
struct FixedClear {
    uint8_t mCount;            // +0x00
    char pad0[3];
    void* mItems[6];           // +0x04 .. +0x1b
    int32_t mFlag1c;           // +0x1c
    VecBase mTail;             // +0x20
    void clear();
};

// @ 0x00711380
void FixedClear::clear()
{
    if (mFlag1c != 0) {
        mFlag1c = 0;
    } else {
        for (int i = 0; i < (int)mCount; ++i) {
            ReleaseObject(mItems[i]);
            mItems[i] = 0;
        }
    }
    VecBase* tail = &mTail;
    void** first = tail->mpBegin;
    void** last = tail->mpEnd;
    void* pNewEnd = AssignCopyRef(last, last, first);
    tail->DestroyRange((void**)pNewEnd, tail->mpEnd);
    tail->mpEnd -= (int32_t)(last - first);
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
// SP::cMaterialManager serialization helpers (guarded by mMutex at +0x258)
// ---------------------------------------------------------------------------------------------
struct Stream;
void WriteUint32(Stream* s, const uint32_t* v, uint32_t n, int flags);   // 0x0093AA70 (cdecl)
void WriteUint16(Stream* s, const uint32_t* v, uint32_t n, int flags);   // 0x0093A9D0 (cdecl)
bool ReadUint32(Stream* s, uint32_t* v, uint32_t n, int flags);          // 0x0093A780 (cdecl)
bool ReadUint16(Stream* s, uint16_t* v, uint32_t n, int flags);          // 0x0093A700 (cdecl)

struct Mutex {
    int Lock(const void* params);    // 0x009221B0 (thiscall, ret 4)
    int Unlock();                    // 0x00922270 (thiscall)
};
extern const char kMutexParams[];    // 0x0140C860

// Scoped lock: ctor Lock(), dtor Unlock() (EH state 0).
struct MutexGuard {
    Mutex* m;
    MutexGuard(Mutex* mu) : m(mu) { m->Lock(kMutexParams); }
    ~MutexGuard() { m->Unlock(); }
};

struct Arena;
struct ExportedObject;
struct Resource;

struct ExternalRef {          // 0x10 bytes: SP::cMaterialManager::cExternalRef
    uint32_t mSourceID;       // +0x00
    uint16_t mIndex;          // +0x04
    uint32_t mGroup;          // +0x08
    uint32_t mInstance;       // +0x0c
};

// sp_fixed_vector<cExternalRef,16>: begin/end/cap, flag at +0x14 (non-zero = heap-owned), buffer +0x18.
struct SpFixedRefVec {
    ExternalRef* mpBegin;     // +0x00
    ExternalRef* mpEnd;       // +0x04
    ExternalRef* mpCapacity;  // +0x08
    uint32_t pad0c;           // +0x0c
    uint32_t pad10;           // +0x10
    uint32_t mHeap;           // +0x14
    ExternalRef mBuffer[16];  // +0x18
    SpFixedRefVec() : mHeap(0) {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 16;
    }
    ~SpFixedRefVec() {
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0)
            EastlFree(mpBegin);
    }
};

// fixed_vector<cExternalRef,16> with overflow pointer at +0x10, buffer +0x18 (ctor 0x00711010 takes n).
struct FixedRefVec {
    ExternalRef* mpBegin;     // +0x00
    ExternalRef* mpEnd;       // +0x04
    ExternalRef* mpCapacity;  // +0x08
    uint32_t pad0c;           // +0x0c
    ExternalRef* mpFixed;     // +0x10
    uint32_t pad14;           // +0x14
    ExternalRef mBuffer[16];  // +0x18
    FixedRefVec(uint32_t n);  // 0x00711010 (thiscall, ret 4, returns this)
    ~FixedRefVec() {
        if (mpBegin && mpBegin != mpFixed)
            EastlFree(mpBegin);
    }
};

struct ResKey {               // EA::ResourceMan::Key
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
    ResKey() {}
    ResKey(uint32_t inst, uint32_t grp) : mInstance(inst), mType(0x2F4E681B), mGroup(grp) {}
};

struct KeyVec {               // eastl::vector<ResKey, sp_vector_allocator>
    ResKey* mpBegin;
    ResKey* mpEnd;
    ResKey* mpCapacity;
    void DoInsertValue(ResKey* pos, const ResKey& v);   // 0x004E3E10 (thiscall, ret 8)
};

// eastl hashtable iterator over the material map: node pointer + bucket pointer.
struct MatIter {
    uint32_t* mpNode;
    uint32_t** mpBucket;
    void increment() {
        mpNode = (uint32_t*)mpNode[0x4c / 4];
        while (mpNode == 0) {
            ++mpBucket;
            mpNode = (uint32_t*)*mpBucket;
        }
    }
};

struct VMHash { uint32_t erase(const uint32_t& key); };   // 0x00A460D0 (thiscall, ret 4)

struct MaterialManagerBig {
    char pad0[0x178];
    uint32_t* mpBucketArray;     // +0x178
    uint32_t mnBucketCount;      // +0x17c
    char pad1[0x34];
    uint32_t mInvalidState;      // +0x1b4
    char pad2[0x4c];
    uint32_t mFlag204;           // +0x204
    char pad3[0x50];
    Mutex mMutex;                // +0x258
    int32_t GetExternalReferences(int32_t n, uint32_t* ids, void* vec, void* extra);   // 0x00710790 (thiscall, ret 0x10)
    int32_t WriteExternalReferences(int32_t n, uint32_t* ids, Stream* stream, void* extra);
    int32_t GetExternalReferenceKeys(int32_t n, uint32_t* ids, KeyVec* out, void* extra);
    int32_t ReadMaterials(Stream* stream, int32_t count, uint32_t* ids, void** pAutoList, ResKey* defKey);
    void UnregisterArenaContents(void* arena);
    void RemoveAllRegisteredMaterials();
};

// @ 0x00711490
int32_t MaterialManagerBig::WriteExternalReferences(int32_t n, uint32_t* ids, Stream* stream, void* extra)
{
    MutexGuard guard(&mMutex);
    SpFixedRefVec refs;
    int32_t result = GetExternalReferences(n, ids, &refs, extra);
    uint32_t tmp = (uint32_t)(refs.mpEnd - refs.mpBegin);
    WriteUint32(stream, &tmp, 1, 0);
    int32_t cnt = refs.mpEnd - refs.mpBegin;
    for (int32_t i = 0; i < cnt; ++i) {
        tmp = refs.mpBegin[i].mSourceID;
        WriteUint32(stream, &tmp, 1, 0);
        uint32_t v16 = refs.mpBegin[i].mIndex;
        WriteUint16(stream, &v16, 1, 0);
        uint32_t g = refs.mpBegin[i].mGroup;
        WriteUint32(stream, &g, 1, 0);
        uint32_t inst = refs.mpBegin[i].mInstance;
        WriteUint32(stream, &inst, 1, 0);
    }
    return result;
}

// @ 0x00711630
int32_t MaterialManagerBig::GetExternalReferenceKeys(int32_t n, uint32_t* ids, KeyVec* out, void* extra)
{
    MutexGuard guard(&mMutex);
    SpFixedRefVec refs;
    int32_t result = GetExternalReferences(n, ids, &refs, extra);
    int32_t cnt = refs.mpEnd - refs.mpBegin;
    for (int32_t i = 0; i < cnt; ++i) {
        ResKey k(refs.mpBegin[i].mInstance, refs.mpBegin[i].mGroup);
        if (out->mpEnd < out->mpCapacity) {
            ResKey* p = out->mpEnd;
            out->mpEnd = p + 1;
            if (p) new (p) ResKey(k);
        } else {
            out->DoInsertValue(out->mpEnd, k);
        }
    }
    return result;
}

// ReadMaterials helper types
struct Resource {
    virtual void AddRef();       // slot 0
    virtual void Release();      // slot 1
    char pad[0x14];
    Arena* mpArena;              // +0x18
};
struct ResPtr {
    Resource* p;
    ResPtr() : p(0) {}
    ~ResPtr() { if (p) p->Release(); }
};
struct ResourceManager {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual bool GetResource(ResKey* key, ResPtr* out, int a, int b, int c, int d);   // slot 3
};
ResourceManager* GetManager();                      // 0x0067DCD0
bool SetCachingType(int type, void* res);           // 0x006AC040 (cdecl)

struct SubDesc {
    uint32_t a, b;
    SubDesc();                                      // 0x006C0FA0
    ~SubDesc();                                     // 0x00C2E4E0
};
struct ExportDesc {
    int32_t type;           // 0x2000b = material
    int32_t object;
    int32_t f2, f3, f4, f5;
    SubDesc subs[4];
    ExportDesc(int32_t x) : type(0), object(0), f2(0), f3(0), f4(0), f5(0) { subs[0].a = 0; subs[0].b = x + 1; }
};
struct Arena {
    int32_t GetNumExportedObjects();                                // 0x011E23A0
    void GetExportedObjectByIndex(int32_t i, ExportDesc* out);      // 0x011E28E0 (thiscall, ret 8)
};

struct ArenaHolder { char pad[0x18]; Arena* mpArena; };

struct AutoList {
    AutoList();                                     // 0x00713F90
    virtual void AddRef();
    void Add(Resource* r);                          // 0x00714050 (thiscall, ret 4)
};
void* operator new(size_t n, const char* name, int a, int b, int c, int d);     // 0x00F473A0
void operator delete(void* p, const char* name, int a, int b, int c, int d);

// @ 0x00711780
int32_t MaterialManagerBig::ReadMaterials(Stream* stream, int32_t count, uint32_t* ids, void** pAutoList, ResKey* defKey)
{
    MutexGuard guard(&mMutex);
    uint32_t n = 0;
    if (!ReadUint32(stream, &n, 1, 0) || n >= 200)
        return -1;
    if (n == 0)
        return 0;
    FixedRefVec refs(n);
    for (uint32_t i = 0; i < n; ++i) {
        ExternalRef* r = &refs.mpBegin[i];
        if (!ReadUint32(stream, &r->mSourceID, 1, 0) ||
            !ReadUint16(stream, &r->mIndex, 1, 0) ||
            !ReadUint32(stream, &r->mGroup, 1, 0) ||
            !ReadUint32(stream, &r->mInstance, 1, 0))
            return -1;
    }
    int32_t found = 0;
    ResourceManager* mgr = GetManager();
    for (uint32_t j = 0; j < n; ++j) {
        ResKey key;
        key.mInstance = refs.mpBegin[j].mInstance;
        key.mType = 0x2F4E681B;
        key.mGroup = refs.mpBegin[j].mGroup;
        if (defKey && key.mGroup == 0xFFFFFFFF) {
            key.mGroup = defKey->mGroup;
            if (key.mInstance == 0xFFFFFFFF)
                key.mInstance = defKey->mInstance;
        }
        int32_t resolved = -1;
        ResPtr res;
        if (mgr->GetResource(&key, &res, 0, 0, 0, 0) && res.p->mpArena) {
            SetCachingType(2, res.p);
            uint32_t idx = refs.mpBegin[j].mIndex & 0xFF;
            ExportDesc desc(0);
            res.p->mpArena->GetExportedObjectByIndex(idx, &desc);
            if (desc.type == 0x2000B && desc.object != 0) {
                // virtual slot 0x40/4 of the manager: (object, resource)
                resolved = ((int32_t (__thiscall*)(MaterialManagerBig*, int32_t, Resource*))
                            (*(void***)this)[0x40 / 4])(this, desc.object, res.p);
                if (pAutoList) {
                    if (*pAutoList == 0) {
                        AutoList* l = new ("Graphics", 0, 0, 0, 0) AutoList;
                        *pAutoList = l;
                        l->AddRef();
                    }
                    ((AutoList*)*pAutoList)->Add(res.p);
                }
            }
        }
        for (int32_t k = 0; k < count; ++k) {
            if (ids[k] == refs.mpBegin[j].mSourceID) {
                ++found;
                ids[k] = (uint32_t)resolved;
            }
        }
    }
    return found;
}

// @ 0x00711b80
void MaterialManagerBig::UnregisterArenaContents(void* arenaArg)
{
    MutexGuard guard(&mMutex);
    ArenaHolder* arena = (ArenaHolder*)arenaArg;
    MatIter it;
    it.mpBucket = (uint32_t**)mpBucketArray;
    it.mpNode = *it.mpBucket;
    if (it.mpNode == 0) {
        ++it.mpBucket;
        while (*it.mpBucket == 0)
            ++it.mpBucket;
        it.mpNode = *it.mpBucket;
    }
    _ReadWriteBarrier();
    MatIter end;
    end.mpBucket = (uint32_t**)mpBucketArray + mnBucketCount;
    end.mpNode = *end.mpBucket;
    while (it.mpNode != end.mpNode) {
        if (it.mpNode[0x20 / 4] == (uint32_t)arena) {
            ((FixedClear*)(it.mpNode + 1))->clear();
            it.mpNode[8 / 4] = mInvalidState;
        }
        it.increment();
    }
    int32_t cnt = arena->mpArena->GetNumExportedObjects();
    for (int32_t i = 0; i < cnt; ++i) {
        ExportDesc desc(i);
        arena->mpArena->GetExportedObjectByIndex(i, &desc);
        if (desc.type == 0x2000B) {
            uint32_t key = (uint32_t)desc.object;
            ((VMHash*)((char*)this + 0x194))->erase(key);
        }
    }
}

// @ 0x00711D10
void MaterialManagerBig::RemoveAllRegisteredMaterials()
{
    MutexGuard guard(&mMutex);
    MatIter it;
    it.mpBucket = (uint32_t**)mpBucketArray;
    it.mpNode = *it.mpBucket;
    if (it.mpNode == 0) {
        ++it.mpBucket;
        while (*it.mpBucket == 0)
            ++it.mpBucket;
        it.mpNode = *it.mpBucket;
    }
    _ReadWriteBarrier();
    MatIter end;
    end.mpBucket = (uint32_t**)mpBucketArray + mnBucketCount;
    end.mpNode = *end.mpBucket;
    while (it.mpNode != end.mpNode) {
        if (it.mpNode[0x20 / 4] == 0) {
            if (mFlag204 == 0)
                ((FixedClear*)(it.mpNode + 1))->clear();
            it.mpNode[8 / 4] = mInvalidState;
        }
        it.increment();
    }
}
