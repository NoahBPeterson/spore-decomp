// slice s006414e0: cSPAssetDataOTDB helpers and a few asset-slot window helpers.
// Module flags: /O2 /MD /Gy /TP (no /arch:SSE, no /EHsc).
#include "s006414e0.h"
extern "C" void* memmove(void*, const void*, size_t);

struct cSPAssetData {
    virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03(); virtual int v04();
    virtual int v05(); virtual int v06(); virtual int v07(); virtual int v08();
    virtual uint32_t GetAssetType();   // +0x24
};

struct cSPAssetDataOTDB : cSPAssetData {
    uint32_t mKeyInstance;       // +4
    uint32_t mTypeID;            // +8
    uint32_t mKeyGroup;          // +0xC
    uint32_t pad10[3];
    cAssetMetadata* mMetadata;   // +0x1C

    ResourceKey* GetKey(ResourceKey* out);
    int FUN_00641780();
    bool GetMetadataKey(uint64_t* out);
    uint64_t FUN_00641830();
    uint64_t FUN_00641870();
    uint64_t FUN_00641890();
    bool FUN_006418b0();
    int FUN_006418e0();
    ResourceKey* GetThumbnailBackdrop(ResourceKey* out);
};

// @ 0x006414e0
ResourceKey* cSPAssetDataOTDB::GetKey(ResourceKey* out)
{
    out->instanceID = mKeyInstance;
    out->groupID = mKeyGroup;
    out->typeID = 0x2f7d0004;
    return out;
}

// @ 0x00641780
int cSPAssetDataOTDB::FUN_00641780()
{
    if (v04()) {
        if (v03())
            return 1;
    }
    return 0;
}

// @ 0x006417d0
bool cSPAssetDataOTDB::GetMetadataKey(uint64_t* out)
{
    if (mMetadata) {
        uint32_t* p = (uint32_t*)mMetadata->FUN_005507a0();
        if (p[0] != 0xffffffff || p[1] != 0xffffffff) {
            uint32_t* q = (uint32_t*)mMetadata->FUN_005507a0();
            ((uint32_t*)out)[0] = q[0];
            ((uint32_t*)out)[1] = q[1];
            return true;
        }
    }
    return false;
}

// @ 0x00641830
uint64_t cSPAssetDataOTDB::FUN_00641830()
{
    if (mMetadata)
        return mMetadata->FUN_005508a0();
    return 0;
}

// @ 0x00641870
uint64_t cSPAssetDataOTDB::FUN_00641870()
{
    if (mMetadata)
        return *mMetadata->FUN_00550840();
    return 0;
}

// @ 0x00641890
uint64_t cSPAssetDataOTDB::FUN_00641890()
{
    if (mMetadata)
        return *mMetadata->FUN_00550860();
    return 0;
}

// @ 0x006418b0
bool cSPAssetDataOTDB::FUN_006418b0()
{
    if (mMetadata) {
        if (mTypeID == 0x3d97a8e4 || mTypeID == 0x04f684a4)
            return false;
        return mMetadata->FUN_00550970();
    }
    return false;
}

// @ 0x006418e0
int cSPAssetDataOTDB::FUN_006418e0()
{
    if (mMetadata) {
        uint64_t v = mMetadata->FUN_005508a0();
        if (v == (uint64_t)-1)
            return 1;
    }
    return 0;
}

// @ 0x00641900
bool GetCreatorType(const ResourceKey* key)
{
    AutoRef<IResource> spRes;
    IResourceManager* mgr = GetManager();
    spRes = 0;
    ResourceKey k(key->instanceID, 0x30bdee3, key->groupID);
    if (mgr->GetResource(&k, &spRes, 0, 0, 0, 0)) {
        AutoRef<cAssetMetadata> md;
        md.mpObject = spRes.mpObject ? (cAssetMetadata*)spRes.mpObject->Cast(0x30bdee3) : 0;
        if (md.mpObject)
            md.mpObject->AddRef();
        md.mpObject->FUN_005507a0();
        uint64_t* p = md.mpObject->FUN_005507a0();
        if (*p != (uint64_t)-1)
            return true;
    }
    return false;
}

// @ 0x006419f0
bool GetCreatorTypeEx(const ResourceKey* key)
{
    AutoRef<IResource> spRes;
    IResourceManager* mgr = GetManager();
    spRes = 0;
    ResourceKey k(key->instanceID, 0x30bdee3, key->groupID);
    if (mgr->GetResource(&k, &spRes, 0, 0, 0, 0)) {
        AutoRef<cAssetMetadata> md;
        md.mpObject = spRes.mpObject ? (cAssetMetadata*)spRes.mpObject->Cast(0x30bdee3) : 0;
        if (md.mpObject)
            md.mpObject->AddRef();
        md.mpObject->FUN_005507a0();
        uint64_t* p = md.mpObject->FUN_005507a0();
        if (*p == (uint64_t)-1 && md.mpObject->FUN_00550970())
            return true;
    }
    return false;
}


struct cColor4 { uint32_t a, b, c, d; };
struct cRecordList {   // begin/end/cap of 12-byte records
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
};
struct cRecordSource : IRefCounted {
    cRecordList* FUN_005507a0x();
};
struct cBlueprintB : IRefCounted {
    uint32_t pad[5];
    uint32_t mField18;                                  // +0x18
    void FUN_004babe0(cColor4* out, int a);             // 0x004BABE0
};
struct TmpVec {   // small pooled array with a size header at [-1]
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    TmpVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~TmpVec() { if (mpBegin && mpBegin[-1]) operator delete[](mpBegin); }
};
bool FUN_004f5720(cBlueprintB* b, TmpVec* out);          // 0x004F5720 (cdecl)
char FUN_004f3d60(cColor4 a, cColor4 b);                 // 0x004F3D60 (cdecl, two 16-byte structs by value)
extern cColor4 gColorA, gColorB, gColorC;                // 0x015DA8E0, 0x015DAB18, 0x015DA80C
void* FUN_0067dea0();                                    // 0x0067DEA0 (cdecl)
struct cInfoRec { uint32_t pad; int mValue; };           // +4: int
struct cInfoMgr { cInfoRec* FUN_007db5e0(); };           // 0x007DB5E0
cInfoMgr* FUN_0067dea0(uint32_t x);
void* operator new[](size_t);
void operator delete[](void* p);

// ---------------------------------------------------------------------------------------------
// UI::TimelineSporepediaCardData
struct __declspec(novtable) cCardBaseA {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual bool Slot68(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual bool Slot90(uint32_t* out); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void Slot0xb0(IRefCounted* p); virtual void Slot0xb4(uint32_t p);
    uint32_t mKey[3];                // +4: instance, type, group
    cCardBaseA() { mKey[0] = 0; mKey[1] = 0; mKey[2] = 0; }
    ~cCardBaseA();                   // 0x006412A0
};
struct cCardBaseB { virtual void b0(); };
struct cCardBaseC { virtual void c0(); uint32_t mC4; cCardBaseC() : mC4(0) {} };

struct FixedVec5 {   // eastl::fixed_vector<T*, 5> (0x2C bytes)
    void** mpBegin;       // +0x00
    void** mpEnd;         // +0x04
    void** mpCapacity;    // +0x08
    uint32_t pad0c;
    void* mpPool;         // +0x10
    uint32_t pad14;
    void* mBuffer[5];     // +0x18
    FixedVec5()
    {
        mpPool = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mpBegin + 5;
    }
    ~FixedVec5()
    {
        if (mpBegin && mpBegin != mpPool)
            operator delete(mpBegin);
    }
    void DoInsertValue(void** pos, void** val);   // 0x0060A600
    void clear()
    {
        void** first = mpBegin;
        void** last = mpEnd;
        memmove(first, last, (size_t)((char*)last - (char*)last));
        mpEnd += -(last - first);
    }
};

struct cTimelineSporepediaCardData : cCardBaseA, cCardBaseB, cCardBaseC {
    AutoRef<IRefCounted> mText;       // +0x1C
    AutoRef<IRefCounted> mRes20;      // +0x20
    bool mb24, mb25, mb26;            // +0x24
    int mField28;                     // +0x28
    int mField2c;                     // +0x2C
    uint32_t pad30[3];
    AutoRef<IRefCounted> mRes3c;      // +0x3C
    FixedVec5 mVec;                   // +0x40
    int mField6c;                     // +0x6C
    AutoRef<ILoadSlot> mA;            // +0x70
    AutoRef<ILoadSlot> mB;            // +0x74

    cTimelineSporepediaCardData();
    ~cTimelineSporepediaCardData();
    int FUN_00641af0();
    void FUN_00641bf0();
    void FUN_00641cd0(bool arg);
    void FUN_00641e10();
    void FUN_00641e40(bool arg);
    bool FUN_00641fa0();
    IRefCounted* FUN_00641fd0();   // returns the loaded resource (0x30 key)
    void FUN_00642230(IResource* res);
    void ReserveVec(int n);   // 0x00642070
};

// @ 0x00642100
cTimelineSporepediaCardData::cTimelineSporepediaCardData()
    : mb24(false), mb25(false), mb26(false), mField28(0), mField2c(2), mField6c(0)
{
}

// @ 0x00642190
cTimelineSporepediaCardData::~cTimelineSporepediaCardData() {}

struct AutoRefExt { void assign(IRefCounted* p); };   // 0x00B5F950 (out-of-line AutoRefCount<IWinText>::operator=)
void FUN_006ac0a0(int a, IRefCounted* p);              // 0x006AC0A0 (cdecl)
void FUN_005bf0e0(void* key, void* slot);              // 0x005BF0E0 (cdecl)

// @ 0x00641af0
int cTimelineSporepediaCardData::FUN_00641af0()
{
    ILoadSlot* a = mA.mpObject;
    if (a && a->IsReady()) {
        AutoRef<IResource> tmp;
        if (mA.mpObject->GetResult(&tmp)) {
            IRefCounted* c = tmp.mpObject ? tmp.mpObject->Cast(0x30bdee3) : 0;
            ((AutoRefExt*)&mText)->assign(c);
        }
        mA = 0;
    }
    ILoadSlot* b = mB.mpObject;
    if (b && b->IsReady()) {
        AutoRef<IResource> tmp;
        if (mB.mpObject->GetResult(&tmp)) {
            FUN_006ac0a0(1, tmp.mpObject);
            Slot0xb0(tmp.mpObject);
        }
        mB = 0;
    }
    if (!mA.mpObject && !mB.mpObject)
        return 1;
    return 0;
}

// @ 0x00641bf0
void cTimelineSporepediaCardData::FUN_00641bf0()
{
    ILoadSlot* a = mA.mpObject;
    if (a) {
        AutoRef<IResource> tmp;
        if (a->GetResult(&tmp))
            mText = tmp.mpObject ? tmp.mpObject->Cast(0x30bdee3) : 0;
        mA = 0;
    }
    ILoadSlot* b = mB.mpObject;
    if (b) {
        AutoRef<IResource> tmp;
        if (b->GetResult(&tmp))
            Slot0xb0(tmp.mpObject);
        mB = 0;
    }
}

// @ 0x00641cd0
void cTimelineSporepediaCardData::FUN_00641cd0(bool arg)
{
    ResourceKey k;
    k = *(ResourceKey*)&mKey[0];
    k.typeID = 0x30bdee3;
    AutoRef<IResource> tmp;
    IResourceManager* mgr = GetManager();
    if (arg) {
        tmp = 0;
        mA = 0;
        if (mgr->GetResourceEx(&k, &mA, &tmp, 0, 0, 0, 0, 0)) {
            if (tmp.mpObject)
                ((AutoRefExt*)&mText)->assign(tmp.mpObject->Cast(0x30bdee3));
        }
    } else {
        tmp = 0;
        if (mgr->GetResource(&k, &tmp, 0, 0, 0, 0))
            mText = tmp.mpObject ? tmp.mpObject->Cast(0x30bdee3) : 0;
    }
}

// @ 0x00641e10
void cTimelineSporepediaCardData::FUN_00641e10()
{
    mRes20 = 0;
    FUN_005bf0e0(&mKey[0], &mRes20);
}

// @ 0x00641fa0
bool cTimelineSporepediaCardData::FUN_00641fa0()
{
    if (mText.mpObject) {
        if (GetCreatorType((ResourceKey*)&mKey[0])) {
            if (Slot68())
                return true;
        }
    }
    return false;
}

// @ 0x00641e40
void cTimelineSporepediaCardData::FUN_00641e40(bool arg)
{
    ResourceKey* key = (ResourceKey*)&mKey[0];
    if (key->instanceID) {
        ResourceKey k;
        k = *key;
        k.typeID = 0x2d5c9af;
        AutoRef<IResource> tmp;
        IResourceManager* mgr = GetManager();
        if (arg) {
            tmp = 0;
            mB = 0;
            if (!mgr->GetResourceEx(&k, &mB, &tmp, 0, 0, 0, 0, 0)) {
                mgr = GetManager();
                tmp = 0;
                mB = 0;
                mgr->GetResourceEx(key, &mB, &tmp, 0, 0, 0, 0, 0);
            }
        } else {
            tmp = 0;
            if (!mgr->GetResource(&k, &tmp, 0, 0, 0, 0)) {
                mgr = GetManager();
                tmp = 0;
                mgr->GetResource(key, &tmp, 0, 0, 0, 0);
            }
        }
        if (tmp.mpObject)
            Slot0xb0(tmp.mpObject);
    }
}

struct cThumbOwner { char pad[0x5c]; struct cThumbMgr* pMgr; };
struct cThumbMgr {
    bool FUN_00613860(uint32_t type);                                             // 0x00613860
    bool FUN_00612f50(uint32_t a, uint32_t b, AutoRef<IRefCounted>* out, int c);  // 0x00612F50
};
cThumbOwner* FUN_0067cb30();   // 0x0067CB30

// @ 0x00641fd0
IRefCounted* cTimelineSporepediaCardData::FUN_00641fd0()
{
    if (mRes3c.mpObject)
        return mRes3c.mpObject;
    uint32_t id[2] = {0xffffffff, 0xffffffff};
    if (Slot90(id)) {
        cThumbMgr* m = FUN_0067cb30()->pMgr;
        if (m) {
            if (m->FUN_00613860(mKey[1])) {
                AutoRef<IRefCounted> tmp;
                if (m->FUN_00612f50(id[0], id[1], &tmp, 0))
                    return tmp.mpObject;
            }
        }
    }
    return 0;
}

// @ 0x00641500
ResourceKey* cSPAssetDataOTDB::GetThumbnailBackdrop(ResourceKey* out)
{
    out->instanceID = 0;
    out->typeID = 0x2f7d0004;
    out->groupID = 0xca14de92;
    switch (GetAssetType()) {
    case 0x2090a11b:
        out->instanceID = 0x14585a1f;
        break;
    case 0x1f2a25b6:
        out->instanceID = 0x71981adc;
        break;
    case 0x1a4e0708:
        out->instanceID = 0x188ebff2;
        break;
    case 0x2a5147a9:
        out->instanceID = 0x062b8bc1;
        break;
    case 0x37148141:
        out->instanceID = 0xda273036;
        break;
    case 0x372e2c04:
        out->instanceID = 0x3f185edb;
        break;
    case 0x4178b8e8:
        out->instanceID = 0x5983fbdf;
        break;
    case 0x449c040f:
        out->instanceID = 0xe4d0e7f3;
        break;
    case 0x441cd3e6:
        out->instanceID = 0xe7792790;
        break;
    case 0x47c10953:
        out->instanceID = 0x62e861d9;
        break;
    case 0x4e3f7777:
    case 0xbdd15f3d:
        out->instanceID = 0x8c1f0aa3;
        break;
    case 0x65672ade:
        out->instanceID = 0x89b74761;
        break;
    case 0x72c49181:
        out->instanceID = 0xd1376095;
        break;
    case 0xbc1041e6:
        out->instanceID = 0xa0cc166e;
        break;
    case 0x8f963dcb:
        out->instanceID = 0xc2d3ce6f;
        break;
    case 0x98e03c0d:
        out->instanceID = 0x7609745a;
        break;
    case 0x99e92f05:
        out->instanceID = 0xb390f699;
        break;
    case 0x9ad7d4aa:
        out->instanceID = 0xb6dc61a6;
        break;
    case 0x9ea3031a:
        out->instanceID = 0xe04dd8b1;
        break;
    case 0xb8669ec9:
        out->instanceID = 0x9fe7f178;
        break;
    case 0x7d433fad:
    case 0xc0b74287:
        out->instanceID = 0x6920384d;
        break;
    case 0xbcd73e89:
        out->instanceID = 0xf56244d2;
        break;
    case 0xc15695da:
        out->instanceID = 0xf6eb7174;
        break;
    case 0xccc35c46:
        out->instanceID = 0xdc1b3879;
        break;
    case 0xdfad9f51:
        out->instanceID = 0xb49e7fb2;
        break;
    case 0xf670aa43:
        out->instanceID = 0xf5f1b0d7;
        break;
    }
    return out;
}

// @ 0x00642230
void cTimelineSporepediaCardData::FUN_00642230(IResource* res)
{
    mField2c = 2;
    mVec.clear();
    AutoRef<cAssetMetadata> aRef;
    AutoRef<cBlueprintB> bRef;
    if (res) {
        aRef.mpObject = (cAssetMetadata*)res->Cast(0x670da17);
        if (aRef.mpObject)
            aRef.mpObject->AddRef();
        bRef.mpObject = (cBlueprintB*)res->Cast(0x3c609f8);
        if (bRef.mpObject)
            bRef.mpObject->AddRef();
        if (!aRef.mpObject) {
            if (bRef.mpObject) {
                mField28 = bRef.mpObject->mField18;
                cColor4 col;
                bRef.mpObject->FUN_004babe0(&col, 1);
                mb25 = FUN_004f3d60(col, gColorA);
                mb24 = FUN_004f3d60(col, gColorB);
                mb26 = FUN_004f3d60(col, gColorC);
                TmpVec vec;
                if (FUN_004f5720(bRef.mpObject, &vec)) {
                    ReserveVec((int)(vec.mpEnd - vec.mpBegin));
                    for (uint32_t i = 0; i < (uint32_t)(vec.mpEnd - vec.mpBegin); ++i) {
                        void** pos = mVec.mpEnd;
                        void* v = (void*)vec.mpBegin[i];
                        if (pos < mVec.mpCapacity) {
                            mVec.mpEnd = pos + 1;
                            if (pos)
                                *pos = v;
                        } else
                            mVec.DoInsertValue(pos, &v);
                    }
                }
            }
        } else {
            uint32_t it = ((uint32_t*)aRef.mpObject->FUN_005507a0())[0];
            uint32_t end = ((uint32_t*)aRef.mpObject->FUN_005507a0())[1];
            for (; it != end; it += 12)
                Slot0xb4(it);
        }
    }
    mField6c = 0;
    if (FUN_0067dea0()) {
        for (uint32_t i = 0; i < (uint32_t)(mVec.mpEnd - mVec.mpBegin); ++i) {
            uint32_t x = (uint32_t)mVec.mpBegin[i];
            cInfoRec* r = FUN_0067dea0(x)->FUN_007db5e0();
            if (r) {
                int* q = &r->mValue;
                if (r->mValue < mField6c)
                    q = &mField6c;
                mField6c = *q;
            }
        }
    }
}
