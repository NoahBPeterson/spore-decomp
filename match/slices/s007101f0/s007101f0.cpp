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
void  __cdecl UninitCopyRef(void** out, void* first, void* last, void* dst);                            // 0x0070EB70
void  __cdecl FillRef(void* first, void* last, const void* value);                                      // 0x0070EBB0
void  __cdecl UninitFillRef(void* dst, uint32_t n, const void* value);                                  // 0x0070F570
// THISCALL: the original passes the vector in ECX and the remaining args on the stack.
void  __fastcall VecA_Shrink(void* self, int, void* first, void* last);                              // 0x0070FA60
void  __fastcall VecB_Shrink(void* self, int, void* first, void* last);                              // 0x0070FAB0
void  __fastcall VecA_Insert(void* self, int, void* position, uint32_t n, const void* value);        // 0x0070FB00
void  __fastcall VecB_Insert(void* self, int, void* position, uint32_t n, const void* value);        // 0x0070FD50
void* __fastcall ReallocRef(void* self, int, uint32_t n, const void* first, const void* last);       // 0x00710190
void* __cdecl AssignCopyRef(void* first, void* last, void* dst);                                     // 0x006F43E0
void* __cdecl AssignMoveRef(void* out, void* first, void* last, void* dst, void* end);               // 0x0070EA70
void  __fastcall DestroyRange0(void* self, int, void* first, void* last);                            // 0x0070F520
void  __fastcall HashtableFind10(void* self, int, void* out, const uint32_t* key);                   // 0x00645ED0
void  __fastcall HashtableInsert10(void* self, int, void* out, const void* value, const void* key);  // 0x0070F5A0
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
    int32_t size() const { return (int32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};

// @ 0x00711070
void VecResizeA::resize(uint32_t n)
{
    if (n > (uint32_t)size()) {
        typedef int32_t value_type;
        value_type value = 0;
        VecA_Insert(this, 0, mpEnd, n - (uint32_t)size(), &value);
    } else {
        VecA_Shrink(this, 0, (char*)mpBegin + n * 4, mpEnd);
    }
}

struct VecResizeB {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    int32_t size() const { return (int32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};

// @ 0x007110F0
void VecResizeB::resize(uint32_t n)
{
    if (n > (uint32_t)size()) {
        typedef int32_t value_type;
        value_type value = 0;
        VecB_Insert(this, 0, mpEnd, n - (uint32_t)size(), &value);
    } else {
        VecB_Shrink(this, 0, (char*)mpBegin + n * 4, mpEnd);
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
    if (n > (uint32_t)((int32_t)((char*)mpCapacity - (char*)mpEnd) >> 2)) {
        const uint32_t nPrevSize = (uint32_t)((int32_t)((char*)mpEnd - (char*)mpBegin) >> 2);
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
        // The value is copied into a local slot first, so the count is bumped even if the
        // caller's AutoRef goes away while the helpers run. Done with a raw pointer so the
        // release at the end stays inline (the original has no EH frame).
        RefObj14* tmp = *(RefObj14**)value;
        if (tmp) ++tmp->mnRefCount;
        void* const oldEnd = mpEnd;
        const uint32_t nExtra = (uint32_t)((char*)oldEnd - (char*)position) >> 2;
        if (n < nExtra) {
            RefObj14* tail = 0;                                 // scratch out-slot for the helper
            UninitCopyRef((void**)&tail, (char*)oldEnd - n * 4, oldEnd, oldEnd);
            mpEnd = (char*)oldEnd + n * 4;
            CopyBackwardRef(position, (char*)oldEnd - n * 4, mpEnd);
            FillRef(position, (char*)position + n * 4, (void**)&tmp);
        } else {
            UninitFillRef(oldEnd, n - nExtra, (void**)&tmp);
            void* const midEnd = (char*)oldEnd + (n - nExtra) * 4;
            mpEnd = midEnd;
            RefObj14* moved = 0;                                // scratch out-slot for the helper
            UninitCopyRef((void**)&moved, position, oldEnd, midEnd);
            mpEnd = (char*)midEnd + nExtra * 4;
            FillRef(position, oldEnd, (void**)&tmp);
        }
        if (tmp && tmp->mnRefCount > 1) --tmp->mnRefCount;
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
    void assign(const void* first, const void* last, const void* allocator);
};

// @ 0x007106D0
void VecAsn::assign(const void* first, const void* last, const void* allocator)
{
    (void)allocator;
    const uint32_t n = (uint32_t)((const char*)last - (const char*)first) >> 2;
    if ((uint32_t)((char*)mpCapacity - (char*)mpBegin) >> 2 < n) {
        void* pNewData = ReallocRef(this, 0, n, first, last);
        DestroyRange0(this, 0, mpBegin, mpEnd);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0) EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = (char*)pNewData + n * 4;
        mpCapacity = mpEnd;
    } else {
        const uint32_t nSize = (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2;
        if (n <= nSize) {
            void* pNewEnd = AssignCopyRef((void*)first, (void*)last, mpBegin);
            DestroyRange0(this, 0, pNewEnd, mpEnd);
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
    uint32_t mField0;          // +0x00
    uint32_t* mpBucketArray;   // +0x04
    uint32_t mnBucketCount;    // +0x08
    uint32_t mField0c;         // +0x0c
    uint8_t mEnd[8];           // +0x10
    Tex4& operator[](const uint32_t& key);
};

// @ 0x007101F0
Tex4& MapA::operator[](const uint32_t& key)
{
    // The original reuses the find-iterator buffer as the insert value (it.first/it.second).
    void* it[2];
    HashtableFind10(this, 0, it, &key);
    if (it[0] != (void*)*(uint32_t*)((char*)mpBucketArray + mnBucketCount * 4)) {
        return *(Tex4*)((char*)it[0] + 4);
    }
    uint32_t* value = (uint32_t*)it;
    value[0] = key;
    value[1] = 0;
    uint8_t out[12];
    HashtableInsert10(this, 0, out, value, (const void*)&key);
    return *(Tex4*)(*(uint32_t*)out + 4);
}

struct Mat4 {
    uint32_t mValue;
    ~Mat4();
};

struct MapB {
    uint32_t mField0;          // +0x00
    uint32_t* mpBucketArray;   // +0x04
    uint32_t mnBucketCount;    // +0x08
    uint32_t mField0c;         // +0x0c
    uint8_t mEnd[8];           // +0x10
    Mat4& operator[](const uint32_t& key);
};

// @ 0x007102B0
Mat4& MapB::operator[](const uint32_t& key)
{
    // The original reuses the find-iterator buffer as the insert value (it.first/it.second).
    void* it[2];
    HashtableFind10(this, 0, it, &key);
    if (it[0] != (void*)*(uint32_t*)((char*)mpBucketArray + mnBucketCount * 4)) {
        return *(Mat4*)((char*)it[0] + 4);
    }
    uint32_t* value = (uint32_t*)it;
    value[0] = key;
    value[1] = 0;
    uint8_t out[12];
    HashtableInsert10(this, 0, out, value, (const void*)&key);
    return *(Mat4*)(*(uint32_t*)out + 4);
}

// ---------------------------------------------------------------------------------------------
// SP::cMaterialManager / cTextureManager methods (reconstructed from the decompilation)
// ---------------------------------------------------------------------------------------------
struct Arena {
    void* mpUnk;
    int32_t GetNumExportedObjects();                             // 0x011E23A0 (thiscall)
    void GetExportedObjectByIndex(int32_t index, void* out);     // 0x011E28E0 (thiscall)
};

// A 16-byte descriptor: the exported-object record that the material map stores and that this
// function appends to the caller's vector.
struct RefRecord {
    uint32_t mId;          // +0
    uint32_t mFlags;       // +4 (low word is the exported-object index)
    uint32_t mField8;      // +8
    uint32_t mFieldC;      // +0xc
};

struct Record16 {
    RefRecord* mpBegin;    // +0
    RefRecord* mpEnd;      // +4
    RefRecord* mpCapacity; // +8
};

// A 16-byte record vector push_back (out of line, the grow helper for the caller's array).
void __fastcall AppendRecord(Record16* self, int, const RefRecord* value);   // 0x0079ACE0

// Arena export-object scratch record: 4 elements of 8 bytes, constructed and destroyed by the
// compiler's vector ctor/dtor iterators.
struct ExportRecord {
    uint32_t mType;        // +0
    uint32_t mKey;         // +4
    uint32_t mField8;      // +8
    uint32_t mFieldC;      // +0xc
};
void __cdecl BaseResDescCtor(void* p);                                   // 0x006C0FA0
void __cdecl ExportRecordDtor(void* p);                                  // 0x00C2E4E0
void __stdcall __ehvec_ctor(void* ptr, unsigned size, int count,
                            void (__thiscall* ctor)(void*), void (__thiscall* dtor)(void*));  // 0x011E0B85
void __stdcall __ehvec_dtor(void* ptr, unsigned size, int count,
                            void (__thiscall* dtor)(void*));                              // 0x011E0B22

namespace EA { namespace ResourceMan { struct Database; } }

struct MaterialManager {
    char pad0[0x178];
    uint32_t* mpBucketArray;   // +0x178
    uint32_t mnBucketCount;    // +0x17c
    char pad1[0x80];
    int32_t mCount;            // +0x200
    int32_t GetExternalReferences(int32_t count, uint32_t* ids, Record16* pOut, RefRecord* pFilter);
};

// @ 0x00710790
int32_t MaterialManager::GetExternalReferences(int32_t count, uint32_t* ids, Record16* pOut, RefRecord* pFilter)
{
    int32_t nFound = 0;
    for (int32_t i = 0; i < count; ++i) {
        const uint32_t id = ids[i];

        // Locate the material entry for this id, using the bucket-list walk.
        const uint32_t bucket = id % mnBucketCount;
        uint32_t* node = (uint32_t*)mpBucketArray[bucket];
        while (node != 0) {
            if (id == *node)
                break;
            node = (uint32_t*)node[0x13];
        }
        uint32_t* endNode = (uint32_t*)mpBucketArray[mnBucketCount];
        if (node == 0)
            node = endNode;

        if (node == endNode || node[8] == 0)
            continue;

        // Skip the arena walk when this id is already present in the caller's output vector.
        // Note the index-based test: a zero/negative existing count means "not present" only
        // when it is exactly zero (matches the original's `iVar9 == iVar8` check).
        const int32_t nExisting = (int32_t)((char*)pOut->mpEnd - (char*)pOut->mpBegin) >> 4;
        int32_t k = 0;
        for (; k < nExisting; ++k) {
            if (pOut->mpBegin[k].mId == id)
                break;
        }
        if (k == nExisting) {
            uint32_t* pRes = (uint32_t*)node[8];             // the material resource object
            Arena* arena = *(Arena**)((char*)pRes + 0x18);
            const int32_t nObjects = arena->GetNumExportedObjects();
            for (int32_t j = 0; j < nObjects; ++j) {
                ExportRecord rec;
                rec.mType = 0;
                rec.mKey = 0;
                rec.mField8 = 0;
                rec.mFieldC = 0;
                __ehvec_ctor(&rec, 8, 4, (void(__thiscall*)(void*))BaseResDescCtor, (void(__thiscall*)(void*))ExportRecordDtor);
                arena->GetExportedObjectByIndex(j, &rec);
                if (rec.mType == 0x2000b && rec.mKey == node[2]) {
                    RefRecord out;
                    out.mId = id;
                    out.mFlags = (uint32_t)(uint16_t)j;
                    out.mField8 = *(uint32_t*)((char*)pRes + 0x10);
                    out.mFieldC = *(uint32_t*)((char*)pRes + 8);
                    if (pFilter != 0) {
                        if (out.mField8 == pFilter->mField8) {
                            out.mField8 = 0xffffffff;
                            if (out.mFieldC == pFilter->mId)
                                out.mFieldC = 0xffffffff;
                        }
                    }
                    if (pOut->mpEnd < pOut->mpCapacity) {
                        *pOut->mpEnd++ = out;
                    } else {
                        AppendRecord(pOut, 0, &out);
                    }
                    __ehvec_dtor(&rec, 8, 4, (void(__thiscall*)(void*))ExportRecordDtor);
                    break;
                }
                __ehvec_dtor(&rec, 8, 4, (void(__thiscall*)(void*))ExportRecordDtor);
            }
            ids[i] = 0xffffffff;
        }
        ++nFound;
    }
    return nFound;
}

struct TextureManager {
    char pad0[0x200];
    int32_t mCount;             // +0x200
    bool GetAllTextures(void* out);
};

// ---------------------------------------------------------------------------------------------
// SP::cMaterialManager::WriteMaterials(EA::ResourceMan::Database*)
// Serialises the material map into a resource: writes a header through the database, opens the
// stream, emits one record per material, saves the resource, then re-applies the raster states.
// ---------------------------------------------------------------------------------------------
struct IOStream;
bool __cdecl StreamWrite(IOStream* s, int a, int b);                  // 0x0093A9A0 (stream, ptr, n)
bool __cdecl WriteUint32(IOStream* s, const void* p, int n, int flags);  // 0x0093AA70
void __cdecl SetCachingType(int type, void* p);                       // 0x006AC040
void __cdecl SaveResourceWe(void* p, uint32_t id, uint32_t type);     // 0x006B1D50
bool __fastcall SetRaster(void* pEmbeddedState, int, int index, int raster);  // 0x011EE6B0
void* __cdecl MakeFixedArray(void* dst, const void* src);             // 0x0070E480
void* __cdecl MaterialFactory();                                      // 0x0067DD60
unsigned __cdecl BuildMaterialRecord(void* a, void* b, int c, int d, int e, const char* name);  // 0x006C24B0
void __fastcall RecordVectorGrow(void* self, int, void* value);       // 0x006C13F0
void __cdecl FreeArray(void* p);                                      // 0x00F47380
void __cdecl ExportRecordVecDtor(void* p, unsigned size, int count, void* dtor);  // 0x011E0B22

namespace EA { namespace ResourceMan {
class Database {
    public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual IOStream* GetStream();                              // +0x18
    virtual void Slot1c();
    virtual void Slot20();
    virtual void ReleaseStream();                               // +0x24
    virtual void Slot28();
    virtual void Slot2c();
    virtual void Slot30();
    virtual bool WriteHeader(void* holder, void* desc, int a, int b, int c, int d);  // +0x34
};
} }

// 0x38-byte serialized material record: a 0x2000b header dword followed by 13 further dwords.
struct MatRecord {
    uint32_t mData[0x0e];
};
struct MatRecordVec {
    MatRecord* mpBegin;     // +0
    MatRecord* mpEnd;       // +4
    MatRecord* mpCapacity;  // +8
};

// One entry of the material hash table.
struct MatEntry {
    uint32_t mField00;
    uint8_t  mFlag04;       // +0x04  (also the raster count / has-state flag)
    char     pad05[3];
    void*    mpState08;     // +0x08  (EmbeddedState*)
    char     pad0c[0x10];
    uint32_t mField1c;      // +0x1c
    void*    mpField20;     // +0x20  (non-null entries are skipped)
    void**   mppBegin24;    // +0x24
    void**   mppEnd28;      // +0x28
    char     pad2c[0x20];
    MatEntry* mpNext4c;     // +0x4c
};

// SP::cMaterialManager shares the material-manager layout.
namespace SP {
struct cMaterialManager {
    char pad0[0x178];
    uint32_t* mpBucketArray;   // +0x178
    uint32_t mnBucketCount;    // +0x17c
    char pad1[0x80];
    int32_t mCount;            // +0x200
    virtual bool WriteMaterials(EA::ResourceMan::Database* pDb);   // 0x00710A50
};
}

// @ 0x00710A50
bool SP::cMaterialManager::WriteMaterials(EA::ResourceMan::Database* pDb)
{
    // Descriptor handed to the database: {count, 0x469a3f7, gResourceType, ...}.
    struct Desc { uint32_t mCount; uint32_t mMagic; uint32_t mType; uint32_t mPad[2]; };
    Desc desc;
    desc.mCount = (uint32_t)mCount;          // +0x200
    desc.mMagic = 0x469a3f7;
    desc.mType = *(uint32_t*)0x01535F60;
    desc.mPad[0] = 0;
    desc.mPad[1] = 0;

    // The database creates a resource holder and opens the write stream.
    void* holder = 0;
    if (!pDb->WriteHeader(&holder, &desc, 2, 6, 1, 0)) {
        if (holder != 0)
            (*(void***)holder)[2] ? ((void(__thiscall*)(void*))(*(void***)holder)[2])(holder) : (void)0;
        return false;
    }

    IOStream* stream = pDb->GetStream();

    uint32_t nCount0 = 0;
    WriteUint32(stream, &nCount0, 1, 0);

    // Output vector of 0x38-byte records, plus the scratch header record.
    MatRecordVec vec;
    void* vecStorage = 0;
    MatRecord* vecSentinel = (MatRecord*)&vec;    // the original's inline sentinel slot
    vec.mpBegin = (MatRecord*)&vecStorage;
    vec.mpEnd = (MatRecord*)&vecStorage;
    vec.mpCapacity = (MatRecord*)((char*)&vecStorage + 4);
    void* factory = MaterialFactory();

    // Walk the material hash table.
    MatEntry* node = (MatEntry*)mpBucketArray[0];
    uint32_t* pSlot = mpBucketArray;
    if (node == 0) {
        pSlot = mpBucketArray + 1;
        while (*pSlot == 0)
            ++pSlot;
        node = (MatEntry*)*pSlot;
    }
    MatEntry* end = (MatEntry*)mpBucketArray[mnBucketCount];

    while (node != end) {
        if (node->mpField20 == 0) {
            uint32_t id = node->mField1c;
            WriteUint32(stream, &id, 1, 0);

            uint8_t flag = node->mFlag04;
            StreamWrite(stream, (int)&flag, 1);

            int count = (int)((char*)node->mppEnd28 - (char*)node->mppBegin24) >> 2;
            StreamWrite(stream, (int)&count, 1);

            for (int i = 0; i < count; ++i) {
                void* elem = node->mppBegin24[i];
                uint32_t v0 = 0xffffffff, v1 = 0xffffffff;
                if (elem != 0) {
                    // factory->vtable[0x2c](&v0, elem): resolve the element to a pair of ids.
                    void* vfp = (*(void***)factory)[0x2c / 4];
                    ((void(__thiscall*)(void*, void*, void*))vfp)(factory, elem, &v0);
                    v1 = *(uint32_t*)((char*)&v0 + 4);
                }
                WriteUint32(stream, &v0, 1, 0);
                WriteUint32(stream, &v1, 1, 0);
            }

            if (node->mFlag04 != 0) {
                int n = (int)((char*)node->mppEnd28 - (char*)node->mppBegin24) >> 2;
                for (int i = 0; i < n; ++i)
                    SetRaster(node->mpState08, 0, i, 0);
            }

            if (node->mFlag04 != 0) {
                MatRecord rec;
                for (int i = 0; i < (int)(uint32_t)node->mFlag04; ++i) {
                    void* elem = node->mppBegin24[i];
                    // The record is a 0x2000b header, the element id, a copied fixed array
                    // (8 dwords) and the element's own first dword.
                    rec.mData[0] = 0x2000b;
                    rec.mData[1] = (uint32_t)(uintptr_t)elem;
                    rec.mData[2] = 0;
                    rec.mData[3] = 0;
                    rec.mData[4] = 0;
                    rec.mData[5] = 0;
                    MakeFixedArray((char*)rec.mData + 0x18, elem);
                    if (vec.mpEnd < vec.mpCapacity) {
                        *vec.mpEnd++ = rec;
                    } else {
                        RecordVectorGrow(&vec, 0, &rec);
                    }
                }
            }
        }
        if (node->mpNext4c != 0) {
            node = node->mpNext4c;
        } else {
            pSlot = (uint32_t*)node + 1;
            while (*pSlot == 0)
                ++pSlot;
            node = (MatEntry*)*pSlot;
        }
    }

    uint32_t terminator = 0xffffffff;
    WriteUint32(stream, &terminator, 1, 0);
    pDb->ReleaseStream();

    // Save the assembled resource.
    void* res = 0;
    int nRecords = (int)((char*)vec.mpEnd - (char*)vec.mpBegin) / 0x38;
    BuildMaterialRecord(&res, 0, (int)vec.mpBegin, (int)vec.mpEnd, nRecords, "RenderAsset/Materials");
    *(uint32_t*)((char*)res + 8) = (uint32_t)mCount;
    *(uint32_t*)((char*)res + 0xc) = 0x2f4e681b;
    *(uint32_t*)((char*)res + 0x10) = *(uint32_t*)0x01535F64;
    SetCachingType(2, res);
    SaveResourceWe(res, 0, 0);

    // Re-apply the raster states now that the resource is saved.
    uint32_t* pSlot2 = mpBucketArray;
    MatEntry* n2 = (MatEntry*)mpBucketArray[0];
    if (n2 == 0) {
        pSlot2 = mpBucketArray + 1;
        while (*pSlot2 == 0)
            ++pSlot2;
        n2 = (MatEntry*)*pSlot2;
    }
    for (; n2 != end; ) {
        if (n2->mpField20 == 0) {
            int n = (int)((char*)n2->mppEnd28 - (char*)n2->mppBegin24) >> 2;
            for (int i = 0; i < n; ++i) {
                void* elem = n2->mppBegin24[i];
                if (elem != 0)
                    SetRaster(n2->mpState08, 0, i, *(int*)elem);
            }
        }
        if (n2->mpNext4c != 0) {
            n2 = n2->mpNext4c;
        } else {
            pSlot2 = (uint32_t*)n2 + 1;
            while (*pSlot2 == 0)
                ++pSlot2;
            n2 = (MatEntry*)*pSlot2;
        }
    }

    if (res != 0 && (*(void***)res)[1] != 0)
        ((void(__thiscall*)(void*))(*(void***)res)[1])(res);

    // Release the record vector's storage (each record's tail array is torn down first).
    MatRecord* p = vec.mpBegin;
    if ((char*)p < (char*)vec.mpEnd) {
        while ((char*)p < (char*)vec.mpEnd) {
            ExportRecordVecDtor((char*)p + 0x18, 4, sizeof(void*) * 4, (void*)0x00C2E4E0);
            ++p;
            if ((char*)p < (char*)vec.mpEnd)
                continue;
            break;
        }
    }
    if (vecStorage != 0 && vec.mpBegin != (MatRecord*)&vecStorage)
        FreeArray(vec.mpBegin);
    (void)vecSentinel;

    if (holder != 0)
        (*(void***)holder)[2] ? ((void(__thiscall*)(void*))(*(void***)holder)[2])(holder) : (void)0;

    return true;
}
