// Slice s0055fc10: SP::cSPObjectTemplateDB asset-list and save-data helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

namespace SP {

// --------------------------------------------------------------------------
// Helper call targets still used by the pre-existing sibling functions below.
void FUN_00564960(void* out, void* val);
void FUN_005631e0(void* self, void* out);
void FUN_00562280(void* self, void* c);
void FUN_004769b0(void* a, void* b);
void FUN_00561cc0(void* self);

struct EcxStubFc {
    void FUN_0055fed0();
    bool FUN_00560880(void* key, unsigned* out);
    bool FUN_005608d0(uint32_t* key, void* c);
};

// --------------------------------------------------------------------------
// cSPObjectTemplateDB layout view (retail offsets); only the members the three
// reworked functions read or write are declared, gaps are pad arrays.
struct AssetEntry {                          // sizeof 0x50 == stride of mAssetList
    ResourceKey mKey;                        // 0x00
    char        pad0c[0x48 - 0x0c];          // 0x0c  (parameters key / feature vector / parameters)
    uint64_t    mnTimeStamp;                 // 0x48  (low dword 0x48, high dword 0x4c)
};

struct KeySel {                              // element of the local selection set (0x10)
    uint64_t mnTimeStamp;                    // 0x00
    uint32_t mIndex;                         // 0x08
    uint32_t pad0c;                          // 0x0c
};

// eastl::vector_set<KeySel> (0x18 bytes): the members slot25 calls.
struct KeySelSet {
    KeySel* mpBegin;                         // 0x00
    KeySel* mpEnd;                           // 0x04
    KeySel* mpCapacity;                      // 0x08
    eastl::sp_vector_allocator mAllocator;   // 0x0c
    uint32_t mComparePad;                    // 0x14
    void FUN_00540470(const eastl::allocator& a);              // ctor
    void FUN_00547240(size_t n);                               // reserve
    void FUN_00565040(void* pResult, const KeySel& value);     // insert
    void FUN_00564fd0();                                       // dtor
};

// eastl::vector_set<unsigned int> (0x18 bytes): the mPopulation / mRefill id sets.
struct UIntSet {
    uint32_t* mpBegin;                       // 0x00
    uint32_t* mpEnd;                         // 0x04
    uint32_t* mpCapacity;                    // 0x08
    eastl::sp_vector_allocator mAllocator;   // 0x0c
    uint32_t mComparePad;                    // 0x14
    uint32_t* FUN_004769b0(uint32_t* first, uint32_t* last);       // erase
    void FUN_00554020(void* pResult, const uint32_t& value);       // insert
};

// eastl::vector<AssetEntry*> (0x14 bytes): the caller-provided result vector.
struct AssetPtrVec {
    AssetEntry** mpBegin;                    // 0x00
    AssetEntry** mpEnd;                      // 0x04
    AssetEntry** mpCapacity;                 // 0x08
    eastl::sp_vector_allocator mAllocator;   // 0x0c
    AssetEntry** FUN_0050f740(AssetEntry** first, AssetEntry** last);   // erase
    void FUN_0041e4d0(size_t n);                                        // reserve
    void FUN_004e19a0(AssetEntry* const& value);                        // push_back
};

// ResourceMan view: only vtable slot 12 (0x30), the per-asset filter callback.
struct IAssetFilterMgr {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual bool IsBannedAsset(AssetEntry* entry, int a, int filter);   // slot 12 (0x30)
};
IAssetFilterMgr* FUN_0067dcd0();             // ResourceMan::GetManager

// --------------------------------------------------------------------------
// Save-file I/O view shared by LoadDatabase and FUN_00560470.
struct TimeStamp {                           // 8-byte timestamp value
    uint64_t mValue;
    void FUN_0092e3d0(int v);                // Set(int)
};

struct IOStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual int  ReadBlock(void* p, int n);  // slot 12 (0x30) -> count of bytes read
    virtual void v0d();
    virtual bool ReadBytes(void* p, int n);  // slot 14 (0x38) -> bool
};

struct DBResource {                          // intrusive resource held by an AutoRef
    virtual void v00(); virtual void v01();
    virtual void Release();                  // slot 2 (0x08)
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual IOStream* GetStream();           // slot 6 (0x18)
    virtual void v07(); virtual void v08();
    virtual void CloseStream();              // slot 9 (0x24)
};

struct IDBPackedFile {                       // the save area returned by GetSaveArea
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c();
    virtual bool GetResource(void* iid, DBResource** ppOut, int a, int b, int c, int d);   // slot 13 (0x34)
};
IDBPackedFile* FUN_006b1f90(uint32_t groupID);   // SP::GetSaveArea

namespace io {
template<typename T> struct AutoRef {        // EA::AutoRefCount<T>
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    T** operator&() {
        if (mpObject) { T* p = mpObject; mpObject = 0; p->Release(); }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}

// cSPObjectTemplateDB layout view: the members LoadDatabase / FUN_00560470 touch.
struct DBView {
    char pad00[0x14];
    eastl::vector<AssetEntry, eastl::sp_vector_allocator> mAssetList;   // 0x14
    char pad28[0x64 - 0x28];
    UIntSet mPopulation;                                                 // 0x64
    UIntSet mRefill;                                                     // 0x7c
    int  FUN_005631e0(const ResourceKey& key);                           // FindAssetIndex
    void FUN_00561970(uint32_t index);                                   // DecreasePopulation
};

// Stub carrying the three reworked cSPObjectTemplateDB methods; members keep the
// original __thiscall ABI (ECX receiver) so the equivalence harness can drive them.
struct DBMethods {
    void slot25(unsigned int maxCount, AssetPtrVec* pOut, int param4);
    bool LoadDatabase();
    bool FUN_00560470();
};

// @ 0x0055fc10
void DBMethods::slot25(unsigned int maxCount, AssetPtrVec* pOut, int param4) {
    DBView* db = (DBView*)this;

    // Local set keeping the maxCount selected entries with the smallest mnTimeStamp.
    eastl::allocator alloc;
    KeySelSet set;
    set.FUN_00540470(alloc);
    set.FUN_00547240(maxCount);

    unsigned int count = 0;
    IAssetFilterMgr* mgr = FUN_0067dcd0();

    AssetEntry* begin = db->mAssetList.mpBegin;
    AssetEntry* end   = db->mAssetList.mpEnd;
    for (AssetEntry* it = begin; it != end; ++it) {
        if (param4 != 0 && !mgr->IsBannedAsset(it, 0, param4))
            continue;

        if (count < maxCount) {
            KeySel value;
            value.mnTimeStamp = it->mnTimeStamp;
            value.mIndex = (uint32_t)(it - begin);
            void* result;
            set.FUN_00565040(&result, value);
            ++count;
        } else if (it->mnTimeStamp < (set.mpEnd - 1)->mnTimeStamp) {
            --set.mpEnd;                     // drop the largest selected entry
            KeySel value;
            value.mnTimeStamp = it->mnTimeStamp;
            value.mIndex = (uint32_t)(it - begin);
            void* result;
            set.FUN_00565040(&result, value);
        }
    }

    pOut->FUN_0050f740(pOut->mpBegin, pOut->mpEnd);
    pOut->FUN_0041e4d0((size_t)(set.mpEnd - set.mpBegin));
    for (KeySel* i = set.mpBegin; i != set.mpEnd; ++i)
        pOut->FUN_004e19a0(&db->mAssetList.mpBegin[i->mIndex]);
    set.FUN_00564fd0();
}

// @ 0x0055ff10
bool DBMethods::LoadDatabase() {
    DBView* db = (DBView*)this;

    TimeStamp defaultStamp;
    defaultStamp.FUN_0092e3d0(1);

    bool ok = true;
    IDBPackedFile* saveArea = FUN_006b1f90(0x11ac19c);
    io::AutoRef<DBResource> ref;
    IOStream* stream = 0;
    if (saveArea) {
        if (!saveArea->GetResource((void*)0x15e3f18, &ref, 1, 3, 1, 0))
            return true;
        stream = ref->GetStream();
        ok = (stream != 0);
    }
    if (!ok)
        return ok;

    int nVersion = 0;
    ok = (stream->ReadBlock(&nVersion, 4) == 4);
    ok = (nVersion <= 4);

    int nCount = 0;
    ok = ok && (stream->ReadBlock(&nCount, 4) == 4);
    if (ok) {
        db->mPopulation.FUN_004769b0(db->mPopulation.mpBegin, db->mPopulation.mpEnd);
        for (; ok && nCount != 0; --nCount) {
            ResourceKey key;
            key.mInstanceID = 0; key.mTypeID = 0; key.mGroupID = 0;
            ok = ok && (stream->ReadBlock(&key.mTypeID, 4) == 4);
            ok = ok && (stream->ReadBlock(&key.mGroupID, 4) == 4);
            ok = ok && (stream->ReadBlock(&key.mInstanceID, 4) == 4);
            if (ok) {
                int index = db->FUN_005631e0(key);
                if (index != -1) {
                    void* result;
                    db->mPopulation.FUN_00554020(&result, (uint32_t)index);
                    db->FUN_00561970((uint32_t)index);
                    if (nVersion < 3) {
                        db->mAssetList.mpBegin[index].mnTimeStamp = defaultStamp.mValue;
                    } else if (ok) {
                        ok = (stream->ReadBlock(&db->mAssetList.mpBegin[index].mnTimeStamp, 8) == 8);
                    }
                }
            }
        }
    }

    if (ok) {
        db->mRefill.FUN_004769b0(db->mRefill.mpBegin, db->mRefill.mpEnd);
        if (nVersion >= 4) {
            ok = (stream->ReadBlock(&nCount, 4) == 4);
            for (; ok && nCount != 0; --nCount) {
                ResourceKey key;
                key.mInstanceID = 0; key.mTypeID = 0; key.mGroupID = 0;
                ok = ok && (stream->ReadBlock(&key.mTypeID, 4) == 4);
                ok = ok && (stream->ReadBlock(&key.mGroupID, 4) == 4);
                ok = ok && (stream->ReadBlock(&key.mInstanceID, 4) == 4);
                if (ok) {
                    int index = db->FUN_005631e0(key);
                    if (index != -1) {
                        void* result;
                        db->mRefill.FUN_00554020(&result, (uint32_t)index);
                    }
                }
            }
        }
    }

    ref->CloseStream();
    return ok;
}

// @ 0x00560470
bool DBMethods::FUN_00560470() {
    DBView* db = (DBView*)this;

    bool ok = false;
    IDBPackedFile* saveArea = FUN_006b1f90(0x11ac19c);
    io::AutoRef<DBResource> ref;
    IOStream* stream = 0;
    if (saveArea) {
        if (saveArea->GetResource((void*)0x15e3f18, &ref, 2, 2, 1, 0)) {
            stream = ref->GetStream();
            ok = (stream != 0);
        }
    }
    if (!ok)
        return ok;

    int nCount = 4;
    ok = stream->ReadBytes(&nCount, 4);
    if (ok) {
        int nPopulation = db->mPopulation.mpEnd - db->mPopulation.mpBegin;
        ok = stream->ReadBytes(&nPopulation, 4);
        for (uint32_t* it = db->mPopulation.mpBegin; ok && it != db->mPopulation.mpEnd; ++it) {
            AssetEntry* a = &db->mAssetList.mpBegin[*it];
            ok = stream->ReadBytes(&a->mKey.mTypeID, 4);
            if (ok) ok = stream->ReadBytes(&a->mKey.mGroupID, 4);
            if (ok) ok = stream->ReadBytes(&a->mKey.mInstanceID, 4);
            if (ok) ok = stream->ReadBytes(&a->mnTimeStamp, 8);
        }
    }
    if (ok) {
        int nRefill = db->mRefill.mpEnd - db->mRefill.mpBegin;
        ok = stream->ReadBytes(&nRefill, 4);
        for (uint32_t* it = db->mRefill.mpBegin; ok && it != db->mRefill.mpEnd; ++it) {
            AssetEntry* a = &db->mAssetList.mpBegin[*it];
            ok = stream->ReadBytes(&a->mKey.mTypeID, 4);
            if (ok) ok = stream->ReadBytes(&a->mKey.mGroupID, 4);
            if (ok) ok = stream->ReadBytes(&a->mKey.mInstanceID, 4);
        }
    }

    ref->CloseStream();
    return ok;
}

// @ 0x0055fe60
void FUN_0055fe60(void* this_, unsigned key, unsigned value) {
    char tmp[8];
    unsigned two[2];
    two[0] = key;
    two[1] = 0;
    FUN_00564960(tmp, two);
    eastl::vector_map<uint32_t, uint32_t>* map =
        (eastl::vector_map<uint32_t, uint32_t>*)((char*)this_ + 0xc4);
    map->operator[](key) = value;
}

// @ 0x0055fed0
void EcxStubFc::FUN_0055fed0() {
    void* this_ = this;
    FUN_004769b0(*(void**)((char*)this_ + 0x64), *(void**)((char*)this_ + 0x68));
    FUN_00561cc0(this_);
}

// @ 0x00560880
bool EcxStubFc::FUN_00560880(void* key, unsigned* out) {
    void* this_ = this;
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index == -1)
        return false;
    char* asset = (char*)(index * 0x50 + *(int*)((char*)this_ + 0x14));
    *out = *(unsigned*)(asset + 0xc);
    return true;
}

// @ 0x005608d0
bool EcxStubFc::FUN_005608d0(uint32_t* key, void* c) {
    void* this_ = this;
    FUN_004769b0(*(void**)((char*)this_ + 0x144), *(void**)((char*)this_ + 0x148));
    FUN_00562280((char*)this_ + 0x144, c);
    uint32_t* it = *(uint32_t**)((char*)this_ + 0x144);
    uint32_t* end = *(uint32_t**)((char*)this_ + 0x148);
    for (; it != end; ++it) {
        uint32_t* asset = (uint32_t*)(*it * 0x50 + *(int*)((char*)this_ + 0x14));
        if (asset[0] == key[0] && asset[1] == key[1] && asset[2] == key[2])
            return true;
    }
    return false;
}

}