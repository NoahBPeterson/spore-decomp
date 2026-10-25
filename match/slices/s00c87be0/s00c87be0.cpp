// Slice s00c87be0 -- Simulator cGameData/cCommunity/cSpatialObject view helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);

// ============================================================ Serialisables
struct Ser {
    char pad00[0xbc];
    int  mBC;   // 0xbc
    void Inc(int a);
    void Dec(int a);
};
// @ 0x00c88480
void Ser::Inc(int a) { (void)a; mBC++; }
// @ 0x00c88490
void Ser::Dec(int a) { (void)a; mBC--; }

// ============================================================ Spatial flags
struct VObj84 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual void v84();
};
struct SpatialA {
    char    pad00[0x64];
    float   f64;   // 0x64
    char    pad68[0x76 - 0x68];
    uint8_t b76;   // 0x76
    char    pad77[0x7c - 0x77];
    float   f7c;   // 0x7c
    char    pad80[0x88 - 0x80];
    float   f88;   // 0x88
    char    pad8c[0xa6 - 0x8c];
    uint8_t bA6;   // 0xa6
    uint8_t bA7;   // 0xa7
    void SetValue(float v);
    void Sync(int v);
    void MaybeCall();
};
// @ 0x00c88530
void SpatialA::SetValue(float v) { f7c = v; f88 = 0.0f; }
// @ 0x00c88550
void SpatialA::Sync(int v) { (void)v; if (f64 != f7c) f64 = f7c; }
// @ 0x00c88510
void SpatialA::MaybeCall() { if (bA7 || bA6) ((VObj84*)this)->v84(); }

// ============================================================ cGameData
struct ObjA0 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
    virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
    virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
    virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
    virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
    virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
    virtual void v88();
    virtual void v89();
};

struct GameData {
    char    pad00[0x68];
    float   f68;    // 0x68
    char    pad6c;
    uint8_t m6d;    // 0x6d
    char    pad6e[0x76 - 0x6e];
    uint8_t b76;    // 0x76
    char    pad77[0x9c - 0x77];
    char*   mp9c;   // 0x9c
    void*   mpA0;   // 0xa0
    char    padA4[0xc0 - 0xa4];
    char*   mpBegin; // 0xc0
    char*   mpEnd;   // 0xc4

    void RemoveOwner(bool b);
    float GetValue();
    int  HasFlag();
    int  FindEntry(int id);
    bool HasEffect(int id);
};

// @ 0x00c88790
void GameData::RemoveOwner(bool b) {
    m6d = b;
    if (mpA0 && b)
        ((ObjA0*)mpA0)->v89();
}
// @ 0x00c887c0
float GameData::GetValue() {
    if (mp9c)
        return *(float*)(mp9c + 0x88);
    return f68;
}
// @ 0x00c887e0  (complete, near miss: block ordering / byte-vs-dword return)
int GameData::HasFlag() {
    if (mp9c == 0)
        return b76;
    if (*(float*)(mp9c + 0x8c) > 0.0f)
        return 0;
    return 1;
}
// @ 0x00c888e0
int GameData::FindEntry(int id) {
    for (char* p = mpBegin; p != mpEnd; p += 0x3c) {
        if (*(int*)p == id)
            return *(int*)(p + 0x38);
    }
    return 0;
}
// @ 0x00c88910
bool GameData::HasEffect(int id) {
    char* p = mpBegin;
    char* end = mpEnd;
    while (p != end) {
        if (*(int*)p == id)
            goto found;
        p += 0x3c;
    }
    p = 0;
found:
    return p != 0;
}

// ============================================================ effect list
struct EffObj3 { virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(int a); };
struct EffObj17 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual void v17(int a, int* b, int c);
};
struct Effects {
    char  pad00[0xc0];
    char* mpBegin;   // 0xc0
    char* mpEnd;     // 0xc4
    int   F40(int id);
    void  StartEffect(int id, int b);
    void  StopEffect(int id, int a);
    void  F00(int id, float v);
    void  F30(int id, int* v);
};
// @ 0x00c88940
int Effects::F40(int id) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        goto none;
    do {
        if (*(int*)p == id) {
            if (p[8] == 0)
                goto none;
            return 1;
        }
        p += 0x3c;
    } while (p != end);
none:
    return 0;
}
// @ 0x00c88980
void Effects::StartEffect(int id, int b) {
    (void)b;
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            if (p[8] == 0) {
                p[8] = 1;
                p[0xa] = 1;
            }
            return;
        }
        p += 0x3c;
    } while (p != end);
}
// @ 0x00c889c0
void Effects::StopEffect(int id, int a) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            p[8] = 0;
            EffObj3* obj = *(EffObj3**)(p + 0x38);
            if (obj)
                obj->v03(a);
            return;
        }
        p += 0x3c;
    } while (p != end);
}
// @ 0x00c88a00
void Effects::F00(int id, float v) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            *(float*)(p + 0xc) = v;
            return;
        }
        p += 0x3c;
    } while (p != end);
}
// @ 0x00c88a30
void Effects::F30(int id, int* v) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            p[0x28] = 1;
            *(int*)(p + 0x2c) = v[0];
            *(int*)(p + 0x30) = v[1];
            *(int*)(p + 0x34) = v[2];
            EffObj17* obj = *(EffObj17**)(p + 0x38);
            if (obj)
                obj->v17(5, v, 3);
            return;
        }
        p += 0x3c;
    } while (p != end);
}

// ============================================================ model key
struct VObj8c {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual void v8c(int a);
};
struct SpatialModel {
    char     pad00[0x90];
    uint32_t m90;   // 0x90
    uint32_t m94;   // 0x94
    uint32_t m98;   // 0x98
    void SetModelKey3(uint32_t* key);
};
// @ 0x00c88810  (complete, near miss: load scheduling of the key comparison)
void SpatialModel::SetModelKey3(uint32_t* key) {
    if (m90 == key[0] && m94 == key[1] && m98 == key[2])
        return;
    m90 = key[0];
    m94 = key[1];
    m98 = key[2];
    ((VObj8c*)this)->v8c(1);
}

// ============================================================ spatial model refresh
void* SP_PlanetModel();            // 0x00b3d350
void* FUN_00b3d310(void* self);    // 0x00b3d310
struct PlanetCall { void v(); };   // 0x00b3e810

struct SpatialPos {
    char  pad00[4];
    float x;   // 0x04
    float y;   // 0x08
    float z;   // 0x0c
    void Fn();
};
// @ 0x00c88870  (complete, near miss)
void SpatialPos::Fn() {
    if (SP_PlanetModel()) {
        float x = this->x;
        float y = this->y;
        float z = this->z;
        if (x * x + y * y + z * z > 0.001f) {
            void* r = FUN_00b3d310(this);
            ((PlanetCall*)r)->v();
        }
    }
}

// ============================================================ vector compare/copy
struct VecThing {
    char     pad00[4];
    float    x;    // 0x04
    float    y;    // 0x08
    float    z;    // 0x0c
    float    w;    // 0x10
    float    x2;   // 0x14
    float    y2;   // 0x18
    float    z2;   // 0x1c
    char     pad20[0x50 - 0x20];
    uint32_t f50;  // 0x50
    char     pad54[0x74 - 0x54];
    uint8_t  b74;  // 0x74
    void Set3(float* v);
    void Set4(float* v);
};
// @ 0x00c88670  (complete, near miss: float compare operand order)
extern "C" void* memcpy(void*, const void*, unsigned int);
void VecThing::Set3(float* v) {
    bool changed = !(x == v[0] && y == v[1] && z == v[2]);
    memcpy(&x, v, 12);
    if (changed) {
        f50 |= 1;
        b74 = 1;
    }
}
// @ 0x00c886d0  (complete, near miss)
void VecThing::Set4(float* v) {
    bool changed = !(w == v[0] && x2 == v[1] && y2 == v[2] && z2 == v[3]);
    memcpy(&w, v, 16);
    if (changed) {
        f50 |= 1;
        b74 = 1;
    }
}

// =====================================================================
// cSpaceInventory / cSpaceInventoryItem / cCommunity / cSpatialObject.
// =====================================================================

struct ResourceKey {
    uint32_t mInstanceID;   // 0x00
    uint32_t mTypeID;       // 0x04
    uint32_t mGroupID;      // 0x08
};
extern ResourceKey kDefaultItemID;              // 0x01694cc4
extern void*       kSpaceInventorySerializerList; // 0x01579ed8
extern void*       kSpatialObjectSerializerList;  // 0x0157a1f8

// ---- serialisable resource / manager
struct cResource {
    virtual void v00();     // 0x00
    virtual void AddRef();  // 0x04
    virtual void Release(); // 0x08
};

struct IResourceManager {
    virtual void v0();      // 0x00
    virtual void v1();      // 0x04
    virtual void v2();      // 0x08
    virtual bool IsLoaded(const ResourceKey& key, void* a, void* b, void* c, void* d, void* e); // 0x0c
};
IResourceManager* GetManager();                 // 0x0067dcd0

// ---- tool-data helpers
struct ToolMethods {
    bool ToolCheck();               // 0x0104cbc0
    int  ToolCount();               // 0x00a02d30
    void ToolSetCount(int n);       // 0x0104cc00
    void ToolSetCount2(int n);      // 0x0104cbd0
};
void FUN_00ba57f0(const ResourceKey& key, int action);  // 0x00ba57f0
void FUN_00ba5650(const ResourceKey& key, int action);  // 0x00ba5650

// ---- generic engine object (vtable slots are the byte offsets)
struct VObj174 {
    virtual void     v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void     v010(); virtual void v014(); virtual VObj174* v018(); virtual VObj174* v01c();
    virtual VObj174* v020(); virtual void v024(); virtual void v028(); virtual float* v02c();
    virtual void     v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void     v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual VObj174* v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void     v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void     v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void     v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual bool     v090(void** out); virtual void v094(); virtual bool v098(void* r); virtual void v09c();
    virtual void     v0a0(); virtual void v0a4(); virtual void v0a8(); virtual unsigned int v0ac();
    virtual void     v0b0(); virtual void v0b4(); virtual VObj174* v0b8(uint32_t id, uint32_t arg);
    virtual bool     v0bc(); virtual void v0c0(); virtual void v0c4();
    void GetCameraLocationInfo(void* pos, void* a, void* b, void* c);   // 0x007c3d30
};
VObj174* SP_App();                              // 0x0067dd10
void     FUN_00b48770(void* self);              // 0x00b48770
// calling-convention-accurate aliases (same targets) for func60h
void* __stdcall FUN_00b3d310_sc(void* self);    // 0x00b3d310
void  __fastcall FUN_00b48770_tc(void* self);   // 0x00b48770

namespace EA { namespace IO {
bool WriteUint32(void* pStream, const uint32_t* pData, uint32_t nCount, int endian);  // 0x0093aa70
bool ReadInt32(void* pStream, uint32_t* pData, uint32_t nCount, int endian);          // 0x0093a780
}}

// ---- intrusive auto reference
struct cSpaceInventoryItem;
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) throw() : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() throw() { T* p = mpObject; if (p) p->Release(); }
    AutoRefCount* Reset();                  // 0x00c463d0
};

template <class T> struct RefPtr {
    T* mPtr;
    RefPtr() : mPtr(0) {}
    RefPtr(T* p) : mPtr(p) { if (mPtr) mPtr->AddRef(); }
    ~RefPtr() { T* p = mPtr; if (p) p->Release(); }
    RefPtr& operator=(T* p) {
        T* pOld = mPtr;
        if (p != pOld) {
            if (p) p->AddRef();
            mPtr = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

// ---- inventory item (multiple inheritance: ItemRefCount/ItemHandler/cItemSerializable)
struct ItemRefCount {
    virtual ~ItemRefCount();                                    // 0x00
    virtual void AddRef() throw();                              // 0x04
    virtual void Release() throw();                             // 0x08
    virtual int  GetReferenceCount();                           // 0x0c
    virtual uint32_t GetType();                                 // 0x10
    virtual void SetItemID(const ResourceKey& key) throw();     // 0x14
    virtual const ResourceKey& GetItemID();                     // 0x18
    virtual void v1c();                                         // 0x1c
    virtual bool IsCargoType();                                 // 0x20
    virtual void Duplicate(AutoRefCount<cSpaceInventoryItem>* pDst); // 0x24
    int32_t mRefCount;                                          // 0x04
};

struct ItemHandler {
    virtual void h00();                                         // 0x00
    virtual bool HandleMessage(uint32_t msgId, void* msg);      // 0x04
};

struct cItemSerializable {
    virtual void v00(); virtual void v04(); virtual void v08(); // 0x00..0x08
    virtual void* Cast(uint32_t typeID);                        // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); // 0x10..0x18
    virtual bool Write(void* pStream);                          // 0x1c
    virtual bool Read(void* pStream);                           // 0x20
};

class cSpaceInventoryItem : public ItemRefCount, public ItemHandler, public cItemSerializable {
public:
    uint32_t mItemCount;                       // 0x10
    uint32_t mItemType;                        // 0x14
    uint32_t mItemCost;                        // 0x18
    bool     mbIsUnique;                       // 0x1c
    uint32_t mPoliticalId;                     // 0x20
    uint32_t mItemPosition;                    // 0x24
    bool     mbIsActive;                       // 0x28
    RefPtr<cResource> mpCargoSlot;             // 0x2c
    void*    mpPropList;                       // 0x30
    char     pad34[0x7c - 0x34];               // 0x34..0x7c (mItemID key lives at 0x5c)
    cSpaceInventoryItem() throw();
};

// ---- inventory vector
struct InvVec {
    cSpaceInventoryItem** mpBegin;   // 0x00
    cSpaceInventoryItem** mpEnd;     // 0x04
    cSpaceInventoryItem** mpCapacity;// 0x08
    struct Alloc { char* mpName; uint32_t mFlags; } mAllocator;  // 0x0c
    ~InvVec() throw();                                      // 0x005c7f10
    void InsertAt(cSpaceInventoryItem** p, void* v) throw(); // 0x00f14270
    cSpaceInventoryItem** Erase(cSpaceInventoryItem** first, cSpaceInventoryItem** last); // 0x005c2170
    __forceinline void push_back(cSpaceInventoryItem* p) {
        AutoRefCount<cSpaceInventoryItem> value(p);
        if (mpEnd < mpCapacity) {
            AutoRefCount<cSpaceInventoryItem>* pSlot = (AutoRefCount<cSpaceInventoryItem>*)mpEnd++;
            pSlot->mpObject = p;
            if (p) p->AddRef();
        } else {
            InsertAt(mpEnd, &value);
        }
    }
};

cSpaceInventoryItem** VecDoCopy(cSpaceInventoryItem** first, cSpaceInventoryItem** last,
                                cSpaceInventoryItem** result);   // 0x0062ffd0

// destructor-free intrusive ref used where the original has no EH frame
struct ItemPtrRef {
    cSpaceInventoryItem* mpObject;
    ItemPtrRef(cSpaceInventoryItem* p) throw() { mpObject = p; p->AddRef(); }
};

// ---- cGameData / cSpaceInventory
struct cISerializableObject {
    virtual ~cISerializableObject();                            // 0x00
    virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050();
};

struct cRefCountV {
    virtual ~cRefCountV();                                      // 0x00
    virtual void r04();                                         // 0x04
};

struct cGameData : cISerializableObject, cRefCountV {
    virtual ~cGameData();                                       // 0x00b184c0
    bool Read(void* pStream);                                   // 0x00b18600
    bool Write(void* pStream);                                  // 0x00b18590
};

class cSpaceInventory : public cGameData {
public:
    char    pad08[0x34 - 0x08];
    InvVec  mInventoryItems;            // 0x34
    int32_t mMaxItemCountPerItem;       // 0x48

    virtual ~cSpaceInventory();
    virtual void func54h();                                        // 0x54
    virtual void SetMaxCargoAmount(int amount);                    // 0x58
    virtual uint32_t GetItemCount();                               // 0x5c
    virtual cSpaceInventoryItem* GetItem(uint32_t index);          // 0x60
    virtual int  IndexOf(uint32_t type, const ResourceKey& id);    // 0x64
    virtual cSpaceInventoryItem* GetTool(const ResourceKey& id);   // 0x68
    virtual int  IndexOfNthItem(uint32_t type, uint32_t nth);      // 0x6c
    virtual bool HasItem(uint32_t type, const ResourceKey& id);    // 0x70
    virtual bool HasTool(const ResourceKey& id);                   // 0x74
    virtual bool RemoveItem(cSpaceInventoryItem* pItem);           // 0x78
    virtual bool func7Ch();                                        // 0x7c
    virtual bool AddItem(cSpaceInventoryItem* pItem, cResource* pResource, bool bAdd); // 0x80
    virtual cSpaceInventoryItem* GetItemByCargoSlot(cSpaceInventoryItem* pSlot);// 0x84
    virtual uint32_t GetCargoSlotsCount();                         // 0x88
    virtual uint32_t GetAvailableCargoSlotsCount();                // 0x8c
    virtual bool GetFreeCargoSlot(cSpaceInventoryItem*& pDst);     // 0x90
    virtual void AddCargoSlots(int count);                         // 0x94
    virtual bool CargoSlotIsFree(void* pSlot);                     // 0x98

    bool func40h();
    bool TakeFromInventory(uint32_t index, AutoRefCount<cSpaceInventoryItem>* pOut, int amount);
    bool Read(void* pStream);
};

struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    cVarListSerializer(void* pObject, void** pList, uint32_t version);  // 0x00692f90
    bool Serialize(void* pStream);                                      // 0x00692900
    bool Read(void* pStream);                                           // 0x00693e10
};

// =====================================================================
// cCommunity
// =====================================================================
struct cCommunity {
    virtual void     c000(); virtual void c004(); virtual void c008(); virtual void c00c();
    virtual void     c010(); virtual void c014(); virtual void c018(); virtual void c01c();
    virtual void     c020(); virtual void c024(); virtual void c028(); virtual void c02c();
    virtual void     c030(); virtual void c034(); virtual void c038(uint32_t a); virtual void c03c(uint32_t a);
    virtual void     c040(); virtual void c044(); virtual void c048(); virtual void c04c();
    virtual void     c050(); virtual void c054(); virtual void c058(); virtual void c05c();
    virtual void     c060(); virtual void c064(void* p, float value); virtual void c068();
    virtual void     c06c(); virtual void c070(); virtual void c074(); virtual void c078();
    virtual void     c07c(); virtual void c080(); virtual void c084(); virtual void c088();
    virtual void     c08c(); virtual void c090(); virtual void c094(); virtual void c098();
    virtual void     c09c(); virtual void c0a0(); virtual void c0a4(); virtual void c0a8();
    virtual void     c0ac(); virtual void c0b0(); virtual void c0b4(); virtual VObj174* c0b8(uint32_t a, uint32_t b);

    char     pad04[0x20 - 0x04];
    char     m20;                       // 0x20
    char     pad21[0x50 - 0x21];
    uint32_t mFlags50;                  // 0x50
    char     pad54[0x64 - 0x54];
    float    m64;                       // 0x64
    char     pad68[0x74 - 0x68];
    uint8_t  m74;                       // 0x74
    char     pad75[0x7c - 0x75];
    float    m7c;                       // 0x7c

    void func5Ch(float value);
    void func60h(uint32_t a, uint32_t b);
};

// =====================================================================
// cSpatialObject
// =====================================================================
struct cSpatialObject {
    void Write(void* pStream);
};

// =====================================================================
// tool data
// =====================================================================
struct ToolSub {
    virtual void AddRef();      // 0x00
    virtual void Release();     // 0x04
};

// intrusive pointer whose assignment mirrors the original (compare/AddRef/Release)
struct ToolRef {
    ToolSub* mpObject;
    ToolRef& operator=(const ToolRef& src) throw() {
        ToolSub* pNew = src.mpObject;
        ToolSub* pOld = mpObject;
        if (pNew != pOld) {
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

// fields copied as float in the copy ctor and as integer dwords in operator=
union ToolF {
    float    f;
    uint32_t i;
};

struct ToolData {
    uint32_t f00;   // 0x00
    uint32_t f04;   // 0x04
    uint8_t  b08;   // 0x08
    uint8_t  b09;   // 0x09
    uint8_t  b0a;   // 0x0a
    float    f0c;   // 0x0c
    uint8_t  b10;   // 0x10
    float    f14;   // 0x14
    float    f18;   // 0x18
    ToolF    f1c;   // 0x1c
    ToolF    f20;   // 0x20
    ToolF    f24;   // 0x24
    uint8_t  b28;   // 0x28
    ToolF    f2c;   // 0x2c
    ToolF    f30;   // 0x30
    ToolF    f34;   // 0x34
    ToolRef  m38;   // 0x38

    ToolData(const ToolData& src);
    ToolData& operator=(const ToolData& src);
};

struct SPVec3 { float x, y, z; };

// =====================================================================
// implementations
// =====================================================================

// @ 0x00c87be0
cSpaceInventory::~cSpaceInventory()
{
}
// @ 0x00c87c80  compiler-generated scalar deleting destructor ??_GcSpaceInventory

// @ 0x00c87cc0
bool cSpaceInventory::func40h()
{
    cSpaceInventoryItem** p = mInventoryItems.mpBegin;
    if (p == mInventoryItems.mpEnd)
        return true;
    cSpaceInventoryItem** next = p + 1;
    for (;;) {
        cSpaceInventoryItem* pItem = *p;
        const ResourceKey& key = pItem->GetItemID();
        if (key.mTypeID != 0 && key.mGroupID != 0 && key.mInstanceID != 0) {
            IResourceManager* pManager = GetManager();
            if (!pManager->IsLoaded(pItem->GetItemID(), 0, 0, 0, 0, 0)) {
                if (next < mInventoryItems.mpEnd)
                    VecDoCopy(next, mInventoryItems.mpEnd, p);
                mInventoryItems.mpEnd--;
                cSpaceInventoryItem* pLast = *mInventoryItems.mpEnd;
                if (pLast)
                    pLast->Release();
                if (p == mInventoryItems.mpEnd)
                    break;
                continue;
            }
        }
        p = next;
        next = p + 1;
        if (p == mInventoryItems.mpEnd)
            break;
    }
    return true;
}

// @ 0x00c87d80
bool cSpaceInventory::RemoveItem(cSpaceInventoryItem* pItem)
{
    cSpaceInventoryItem** p = mInventoryItems.mpBegin;
    cSpaceInventoryItem** end = mInventoryItems.mpEnd;
    while (p != end) {
        if (*p == pItem)
            goto found;
        ++p;
    }
    return false;
found:
    {
        cSpaceInventoryItem* pFound = *p;
        pFound->mpCargoSlot = 0;
        if (p + 1 < mInventoryItems.mpEnd)
            VecDoCopy(p + 1, mInventoryItems.mpEnd, p);
        mInventoryItems.mpEnd--;
        cSpaceInventoryItem* pLast = *mInventoryItems.mpEnd;
        if (pLast)
            pLast->Release();
    }
    return true;
}

// @ 0x00c87df0
bool cSpaceInventory::TakeFromInventory(uint32_t index, AutoRefCount<cSpaceInventoryItem>* pOut, int amount)
{
    if (index >= (uint32_t)(mInventoryItems.mpEnd - mInventoryItems.mpBegin))
        return false;
    cSpaceInventoryItem* pItem = mInventoryItems.mpBegin[index];
    if (pItem->mItemType == 2 && amount != -1) {
        cSpaceInventoryItem* pTool = 0;
        if (pItem)
            pTool = (cSpaceInventoryItem*)static_cast<cItemSerializable*>(pItem)->Cast(0x707459f0);
        cSpaceInventoryItem* pOutItem = 0;
        if (pOut->mpObject)
            pOutItem = (cSpaceInventoryItem*)static_cast<cItemSerializable*>(pOut->mpObject)->Cast(0x707459f0);
        if (((ToolMethods*)pTool)->ToolCheck()) {
            int n = ((ToolMethods*)pTool)->ToolCount();
            if (n >= amount)
                ((ToolMethods*)pTool)->ToolSetCount(amount);
            if (pOutItem)
                ((ToolMethods*)pOutItem)->ToolSetCount2(amount);
            return true;
        }
    }
    pItem = mInventoryItems.mpBegin[index];
    if (!pItem->mbIsUnique && amount != -1 && pItem->mItemCount != (uint32_t)amount) {
        if ((int)pItem->mItemCount > amount) {
            pItem->Duplicate(pOut->Reset());
            pOut->mpObject->mItemCount = amount;
            mInventoryItems.mpBegin[index]->mItemCount -= amount;
            return true;
        }
        return false;
    }
    cSpaceInventoryItem* pOld = pOut->mpObject;
    if (pItem != pOld) {
        if (pItem) pItem->AddRef();
        pOut->mpObject = pItem;
        if (pOld) pOld->Release();
    }
    pOut->mpObject->mpCargoSlot = 0;
    {
        cSpaceInventoryItem** p = mInventoryItems.mpBegin + index;
        if (p + 1 < mInventoryItems.mpEnd)
            VecDoCopy(p + 1, mInventoryItems.mpEnd, p);
        mInventoryItems.mpEnd--;
        cSpaceInventoryItem* pLast = *mInventoryItems.mpEnd;
        if (pLast)
            pLast->Release();
    }
    return true;
}

// @ 0x00c88060
bool cSpaceInventory::AddItem(cSpaceInventoryItem* pItem, cResource* pResource, bool bAdd)
{
    cSpaceInventoryItem** pp = mInventoryItems.mpBegin;
    while (pp != mInventoryItems.mpEnd) {
        if (*pp == pItem)
            break;
        ++pp;
    }
    if (pp != mInventoryItems.mpEnd)
        return false;
    int count = (int)(mInventoryItems.mpEnd - mInventoryItems.mpBegin);
    for (int i = 0; i < count; i++) {
        cSpaceInventoryItem* p = mInventoryItems.mpBegin[i];
        const ResourceKey& kB = pItem->GetItemID();
        const ResourceKey& kA = p->GetItemID();
        if (kA.mInstanceID == kB.mInstanceID && kA.mTypeID == kB.mTypeID &&
            kA.mGroupID == kB.mGroupID && p->mItemType == pItem->mItemType) {
            if (p->mItemType == 2) {
                cSpaceInventoryItem* pToolA = (cSpaceInventoryItem*)static_cast<cItemSerializable*>(p)->Cast(0x707459f0);
                cSpaceInventoryItem* pToolB = (cSpaceInventoryItem*)static_cast<cItemSerializable*>(pItem)->Cast(0x707459f0);
                if (((ToolMethods*)pToolA)->ToolCheck()) {
                    if (!bAdd)
                        return true;
                    int n = ((ToolMethods*)pToolB)->ToolCount();
                    ((ToolMethods*)pToolA)->ToolSetCount2(n);
                    return true;
                }
            }
            if (p->mbIsUnique)
                return false;
            if (mMaxItemCountPerItem != -1 && (int)p->mItemCount >= mMaxItemCountPerItem)
                return false;
            if (!bAdd)
                return true;
            p->mItemCount += pItem->mItemCount;
            if (mMaxItemCountPerItem != -1 && (int)p->mItemCount > mMaxItemCountPerItem) {
                pItem->mItemCount += mMaxItemCountPerItem - p->mItemCount;
                p->mItemCount = mMaxItemCountPerItem;
            }
            return true;
        }
    }
    if (pItem->mItemType == 0 || pItem->mItemType == 1 || pItem->mItemType == 6 ||
        pItem->mItemType == 4 || pItem->mItemType == 5) {
        if (pResource != 0) {
            if (!CargoSlotIsFree(pResource))
                return false;
            pItem->mpCargoSlot = pResource;
        } else {
            cSpaceInventoryItem* pOut;
            if (!GetFreeCargoSlot(pOut))
                return false;
            pItem->mpCargoSlot = (cResource*)pOut;
        }
    }
    if (bAdd) {
        ItemPtrRef ref(pItem);
        if (mInventoryItems.mpEnd < mInventoryItems.mpCapacity) {
            AutoRefCount<cSpaceInventoryItem>* pSlot = (AutoRefCount<cSpaceInventoryItem>*)mInventoryItems.mpEnd++;
            if (pSlot) {
                pSlot->mpObject = pItem;
                pItem->AddRef();
            }
        } else {
            mInventoryItems.InsertAt(mInventoryItems.mpEnd, &ref);
        }
        ref.mpObject->Release();
        if (mMaxItemCountPerItem != -1 && (int)pItem->mItemCount > mMaxItemCountPerItem)
            pItem->mItemCount = mMaxItemCountPerItem;
        if (pItem->mItemType == 0)
            FUN_00ba57f0(pItem->GetItemID(), 3);
        else if (pItem->mItemType == 1)
            FUN_00ba5650(pItem->GetItemID(), 3);
    }
    return true;
}

// @ 0x00c88310
void cSpaceInventory::AddCargoSlots(int count)
{
    if (count > 0) {
        InvVec* pVec = &mInventoryItems;
        int local = count;
        do {
            cSpaceInventoryItem* pItem = new ("Simulator/cSpaceInventoryItem", 0, 0, 0, 0) cSpaceInventoryItem;
            pItem->mItemType = 3;
            pItem->SetItemID(kDefaultItemID);
            pItem->mItemCount = 1;
            cSpaceInventoryItem* pKeep = pItem;
            pItem->AddRef();
            if (pVec->mpEnd < pVec->mpCapacity) {
                AutoRefCount<cSpaceInventoryItem>* pSlot = (AutoRefCount<cSpaceInventoryItem>*)pVec->mpEnd++;
                if (pSlot) {
                    pSlot->mpObject = pItem;
                    pItem->AddRef();
                }
            } else {
                pVec->InsertAt(pVec->mpEnd, &pKeep);
                pItem = pKeep;
            }
            if (pItem)
                pItem->Release();
        } while (--local);
    }
}

// @ 0x00c883d0
bool cSpaceInventory::Read(void* pStream)
{
    InvVec* pVec = &mInventoryItems;
    cSpaceInventoryItem** pBegin = pVec->mpBegin;
    cSpaceInventoryItem** pEnd = pVec->mpEnd;
    pVec->Erase(pBegin, pEnd);
    uint32_t version;
    VObj174* pIo = ((VObj174*)pStream)->v020()->v018();
    EA::IO::ReadInt32(pIo, &version, 1, 0);
    bool ok = cGameData::Read(pStream);
    cVarListSerializer serializer(this, &kSpaceInventorySerializerList, 0x1a80d26);
    if (ok) {
        if (serializer.Read(pStream))
            return true;
    }
    return false;
}

// @ 0x00c884a0
void cCommunity::func5Ch(float value)
{
    if (value != m64) {
        m64 = value;
        m7c = value;
        c064(&m20, value);
        mFlags50 |= 1;
        m74 = 1;
    }
}

// @ 0x00c885b0
VObj174* FUN_00c885b0(VObj174* pObj, uint32_t* pData)
{
    VObj174* pIo = pObj->v020()->v018();
    EA::IO::WriteUint32(pIo, pData, 3, 0);
    pIo = pObj->v020()->v018();
    EA::IO::WriteUint32(pIo, pData + 3, 3, 0);
    return pObj;
}

// @ 0x00c88610
VObj174* FUN_00c88610(VObj174* pObj, uint32_t* pData)
{
    VObj174* pIo = pObj->v020()->v018();
    EA::IO::ReadInt32(pIo, pData, 3, 0);
    pIo = pObj->v020()->v018();
    EA::IO::ReadInt32(pIo, pData + 3, 3, 0);
    return pObj;
}

// @ 0x00c88740
void cCommunity::func60h(uint32_t a, uint32_t b)
{
    c038(a);
    c03c(b);
    VObj174* p = c0b8(0x17f243b, 0);
    FUN_00b48770_tc(FUN_00b3d310_sc(p));
}

// @ 0x00c88a90
void cSpatialObject::Write(void* pStream)
{
    uint32_t type = 0x1186577;
    VObj174* pIo = ((VObj174*)pStream)->v020()->v018();
    EA::IO::WriteUint32(pIo, &type, 1, 0);
    cVarListSerializer serializer(this, &kSpatialObjectSerializerList, 0x1a80d26);
    serializer.Serialize(pStream);
}

// @ 0x00c88ba0
ToolData::ToolData(const ToolData& src)
{
    f00 = src.f00;
    f04 = src.f04;
    b08 = src.b08;
    b09 = src.b09;
    b0a = src.b0a;
    f0c = src.f0c;
    b10 = src.b10;
    f14 = src.f14;
    f18 = src.f18;
    f1c.f = src.f1c.f;
    f20.f = src.f20.f;
    f24.f = src.f24.f;
    b28 = src.b28;
    f2c.f = src.f2c.f;
    f30.f = src.f30.f;
    f34.f = src.f34.f;
    m38.mpObject = src.m38.mpObject;
    if (m38.mpObject)
        m38.mpObject->AddRef();
}

// @ 0x00c88c30
ToolData& ToolData::operator=(const ToolData& src)
{
    f00 = src.f00;
    f04 = src.f04;
    b08 = src.b08;
    b09 = src.b09;
    b0a = src.b0a;
    f0c = src.f0c;
    b10 = src.b10;
    f14 = src.f14;
    f18 = src.f18;
    f1c.i = src.f1c.i;
    f20.i = src.f20.i;
    f24.i = src.f24.i;
    b28 = src.b28;
    f2c.i = src.f2c.i;
    f30.i = src.f30.i;
    f34.i = src.f34.i;
    m38 = src.m38;
    return *this;
}

// @ 0x00c88d90
struct CamInfo {
    char     pad00[4];
    uint32_t mFlags;    // 0x04
    char     pad08[0x88 - 0x08];
    float    mDist;     // 0x88
};

long double FUN_00c88d90(VObj174* pObj)
{
    CamInfo* p = (CamInfo*)pObj->v0ac();
    if (p != 0) {
        unsigned char b = (unsigned char)((p->mFlags >> 15) & 1);
        if (b != 0) {
            float d = p->mDist;
            return d;
        }
    }
    VObj174* pViewer = SP_App()->v050()->v01c();
    SPVec3 pos;
    pViewer->GetCameraLocationInfo(&pos, 0, 0, 0);
    float* loc = pObj->v02c();
    long double dx = (long double)loc[0] - (long double)pos.x;
    long double dy = (long double)loc[1] - (long double)pos.y;
    long double dz = (long double)loc[2] - (long double)pos.z;
    return sqrtl(dz * dz + dy * dy + dx * dx);
}
