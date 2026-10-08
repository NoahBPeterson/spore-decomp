// SP::cSPUISpace::UpdateTerraformingSlots (0x01071d70): refreshes the terraforming slot icons,
// lock states and counters of the space UI from the terraforming manager.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc: the fixed string local has no EH frame in the original).
#include "types.h"

struct Key {                                           // 12-byte resource key (memory order)
    uint32_t a, b, c;
    bool operator==(const Key& o) const { return a == o.a && b == o.b && c == o.c; }
};
extern Key gNullKey;                                   // 0x016e224c
extern const Key kSlotImages[9];                       // 0x015b93b4 (3 triples of window images)
extern const float kRefreshInterval;                   // 0x016e2230
extern bool gDebugFlag6ec;                             // 0x016e06ec
extern bool gDebugFlag6ed;                             // 0x016e06ed
extern bool gDebugFlag6ee;                             // 0x016e06ee

struct Elem {
    Key GetKey();                                      // 0x00c3e1e0 (sret, ret 4)
};
struct ElemVector {
    uint32_t mUnused;
    Elem** mpBegin;                                    // +4
    Elem** mpEnd;                                      // +8
};

struct PlanetRecord {
    char pad0[0x2c];
    uint32_t mFlags;                                   // +0x2c
    char pad1[0xd0 - 0x30];
    char* mpKeysBegin;                                 // +0xd0
    char* mpKeysEnd;                                   // +0xd4
};
struct Planet {
    char pad[0x13c];
    PlanetRecord* mpRecord;                            // +0x13c
    bool SetSpeciesAsScanned(const Key* key);          // 0x00c73ea0 (thiscall, ret 4)
};

struct TerraformMgr {
    int F670(PlanetRecord* rec);                       // 0x00bbc670 (ret 4)
    int GetUnlockedCount(PlanetRecord* rec);           // 0x00bbe470 (ret 4)
    Key GetKeyA();                                     // 0x00bbc4f0 (sret, ret 4)
    Key GetKeyB();                                     // 0x00bbc510 (sret, ret 4)
    bool F6a0(int index, PlanetRecord* rec);           // 0x00bbc6a0 (ret 8)
    bool F850(int index, int which, PlanetRecord* rec);// 0x00bbe850 (ret 0xc)
    Key F870(int index, uint32_t id, PlanetRecord* rec);   // 0x00bbc870 (sret, ret 0x10)
    Key F950(int index, int which, PlanetRecord* rec);     // 0x00bbc950 (sret, ret 0x10)
    Key Fa30(int index, PlanetRecord* rec);                // 0x00bbca30 (sret, ret 0xc)
};

struct UIWindow {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30();
    virtual void SetFlag(int flag, bool value);        // slot 31 (+0x7c)
    virtual void SetCaption(const wchar_t* text);      // slot 32 (+0x80)
};
struct GlobalUI {
    UIWindow* FindWindowByID(uint32_t id);             // 0x00e012b0 (thiscall, ret 4)
};

struct Property {
    char pad[0x12];
    uint16_t mType;                                    // +0x12
    int* GetData();                                    // 0x0041e990 (thiscall)
};
struct PropertyHolder {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool GetProperty(uint32_t id, Property** out);   // slot 9 (+0x24)
};

struct NounManager {
    ElemVector* GetGameDataVector(void* a, void* b, void* c, void* d, uint32_t e);   // 0x00b21340 (ret 0x14)
};

// Minimal wchar_t fixed_string<16> (retail layout: begin, end, capacity, allocator, pool, buffer).
extern void __cdecl operator_delete__(void* p);        // 0x00f47380
struct FixedStr16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* mpPool;
    wchar_t mBuf[16];
    FixedStr16() {
        mpBegin = mBuf;
        mpEnd = mBuf;
        mpPool = mBuf;
        mpCapacity = mBuf + 16;
        mBuf[0] = 0;
    }
    __forceinline ~FixedStr16() {
        wchar_t* p = mpBegin;
        if (((int)((char*)mpCapacity - (char*)p) & ~1) > 2 && p != 0 && p != mpPool)
            operator_delete__(p);
    }
    void sprintf(const wchar_t* fmt, ...);             // 0x0068d0b0 (variadic, this pushed)
};

struct true_type {};
struct InsertResult { void* it; bool inserted; };
struct KeySet {                                        // eastl::set<Key> (rbtree, retail layout)
    uint32_t mCompare;
    void* mpNodeRight;
    void* mpNodeLeft;
    void* mpNodeParent;
    char mColor;
    uint32_t mnSize;
    KeySet() {
        mpNodeRight = &mpNodeRight;
        mpNodeLeft = &mpNodeRight;
        mpNodeParent = 0;
        mColor = 0;
        mnSize = 0;
    }
    ~KeySet() { DoNuke(mpNodeParent); }
    void DoNuke(void* node);                           // 0x004e8a30
    InsertResult DoInsertValue(const Key& value, true_type);   // 0x004290c0 (sret, ret 0xc)
    InsertResult insert(const Key& value) { return DoInsertValue(value, true_type()); }
};

float SPUIHelpers_GetElapsedSeconds();                 // 0x00805080 (cdecl, returns st0)
TerraformMgr* GetTerraformingManager();                // 0x00b3d430
void* GetB3d420();                                     // 0x00b3d420
void* GetB3d450();                                     // 0x00b3d450
NounManager* GetNounManager();                         // 0x00b3d300
Planet* GetActivePlanet();                             // 0x01021260
PlanetRecord* GetActivePlanetRecord();                 // 0x010212a0
PropertyHolder** GetPropertyHolder();                  // 0x01049a10
void SetWindowImageResource(UIWindow* w, const Key* res, int index);   // 0x00807cb0 (cdecl)
// Game-data vector generators passed to GetGameDataVector.
extern void FUN_00cd7d10();   // 0x00cd7d10
extern void FUN_00d3d420();   // 0x00d3d420
extern void FUN_00acdff0();   // 0x00acdff0
extern void FUN_00b1e500();   // 0x00b1e500
extern void FUN_00b2d9d0();   // 0x00b2d9d0

namespace SP {
class cSPUISpace {
public:
    void UpdateTerraformingSlots();
    void SetSlot(uint32_t id, bool locked, const Key* key, bool scanned, bool flagA, bool same);   // 0x01068d30 (ret 0x18)
    char pad[0x224];
    GlobalUI* mGlobalLayout;                           // +0x224
};
}

// @ 0x01071d70
void SP::cSPUISpace::UpdateTerraformingSlots()
{
    {
    uint32_t idsLock[4] = { 0, 0x36969ff, 0x3696a10, 0x3696a1a };
    uint32_t idsTool[4] = { 0, 0x3693f49, 0x3693f3e, 0x3693f23 };
    uint32_t idsIcon[4] = { 0, 0x535cbd8, 0x535cbd9, 0x535cbda };

    if (SPUIHelpers_GetElapsedSeconds() > kRefreshInterval) {
        TerraformMgr* tm = GetTerraformingManager();
        if (tm->F670(0) == -1)
            return;
        NounManager* nm = GetNounManager();
        ElemVector* dataVec = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                    (void*)FUN_00acdff0, (void*)FUN_00b1e500, 0x18c43e8);
        int count1 = (int)(dataVec->mpEnd - dataVec->mpBegin);
        int count2 = tm->GetUnlockedCount(0);
        Planet* planet = GetActivePlanet();
        PlanetRecord* rec = planet->mpRecord;
        Key keyA = tm->GetKeyA();
        Key keyB = tm->GetKeyB();
        Key k = gNullKey;
        int i = 1;
        int c4 = 0x37e89da;
        int d0 = 0x37e89d2;
        do {
            UIWindow* w = mGlobalLayout->FindWindowByID(idsIcon[i]);
            if (w) {
                if (count1 >= i) {
                    SetWindowImageResource(w, &kSlotImages[0], 0);
                    SetWindowImageResource(w, &kSlotImages[1], 2);
                    SetWindowImageResource(w, &kSlotImages[2], 3);
                } else if (count2 < i) {
                    SetWindowImageResource(w, &kSlotImages[6], 0);
                    SetWindowImageResource(w, &kSlotImages[7], 2);
                    SetWindowImageResource(w, &kSlotImages[8], 3);
                } else {
                    SetWindowImageResource(w, &kSlotImages[3], 0);
                    SetWindowImageResource(w, &kSlotImages[4], 2);
                    SetWindowImageResource(w, &kSlotImages[5], 3);
                }
            }
            bool locked = !tm->F6a0(i, rec);
            UIWindow* w1 = mGlobalLayout->FindWindowByID(idsLock[i]);
            UIWindow* w2 = mGlobalLayout->FindWindowByID(idsTool[i]);
            if (w1 && w2) {
                w1->SetFlag(1, locked);
                w2->SetFlag(1, !locked);
            }
            bool same, flagA, scanned;

            flagA = locked || !tm->F850(i, 1, rec);
            k = tm->F870(i, 0x6d60a1cc, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey == keyA) && k == keyA;
            SetSlot(d0 - 2, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 2, rec);
            k = tm->F870(i, 0x29c388a, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey == keyA) && k == keyA;
            SetSlot(d0 - 1, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 3, rec);
            k = tm->F870(i, 0x3a8be428, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey == keyA) && k == keyA;
            SetSlot(d0, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 4, rec);
            k = tm->F950(i, 0, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey == keyB) && k == keyB;
            SetSlot(c4 - 1, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 5, rec);
            k = tm->F950(i, 1, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey == keyB) && k == keyB;
            SetSlot(c4, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 6, rec);
            k = tm->Fa30(i, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey == keyB) && k == keyB;
            SetSlot(i + 0x37e89de, locked, &k, scanned, flagA, same);
            d0 += 3;
            c4 += 2;
            ++i;
        } while (c4 <= 0x37e89de);
        bool bit = (GetActivePlanetRecord()->mFlags >> 11) & 1;
        UIWindow* wb = mGlobalLayout->FindWindowByID(0x52c2948);
        if (wb)
            wb->SetFlag(1, bit);
        if (bit) {
            UIWindow* wc = mGlobalLayout->FindWindowByID(0x680d440);
            if (wc) {
                int v = 100;
                PropertyHolder* holder = *GetPropertyHolder();
                Property* prop;
                if (holder && holder->GetProperty(0x5469bf8, &prop) && prop->mType == 9)
                    v = *prop->GetData();
                FixedStr16 s;
                s.sprintf(L"%d/%d", (rec->mpKeysEnd - rec->mpKeysBegin) / 12, v);
                wc->SetCaption(s.mpBegin);
            }
        }
    }
    }
    if (gDebugFlag6ee && !gDebugFlag6ec && !gDebugFlag6ed) {
        GetTerraformingManager();
        GetB3d420();
        GetB3d450();
        GetActivePlanet();
        KeySet set;
        NounManager* nm = GetNounManager();
        ElemVector* dataVec = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                    (void*)FUN_00b2d9d0, (void*)FUN_00b1e500, 0x18c84a9);
        int n = (int)(dataVec->mpEnd - dataVec->mpBegin);
        for (int i = 0; i < n; ++i)
            set.insert(dataVec->mpBegin[i]->GetKey());
    }
}
