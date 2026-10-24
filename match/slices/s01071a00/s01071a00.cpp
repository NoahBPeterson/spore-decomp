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

struct Elem;
struct ElemVector {
    uint32_t mUnused;
    Elem** mpBegin;                                    // +4
    Elem** mpEnd;                                      // +8
};

struct Sim {                                            // Sim sub-object at Elem+0x508
    char pad[0x20c];
    float NodeRatio();                                 // 0x00bfc490
};

struct Elem {
    char pad0[0x508];
    Sim mSim;                                          // +0x508
    int mType;                                         // +0x714
    Key GetKey();                                      // 0x00c3e1e0 (sret, ret 4)
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

// Fixed-slot vtable calls (retail classes have no matching header in this slice).
#define VT1(R, o, off, a) \
    ((R (__thiscall*)(void*, void*))(*(void***)(o))[(off) / 4])((o), (void*)(a))
#define VT4F(R, o, off, k, v, a, b) \
    ((R (__thiscall*)(void*, uint32_t, float, int, int))(*(void***)(o))[(off) / 4])((o), (k), (v), (a), (b))

extern void* __cdecl rt_memcpy(void* dst, const void* src, unsigned size);   // 0x011e0744
extern const float kRatioScale;                        // 0x013ec4d0

namespace SP { class cSPUISpace; }

struct UIWindow;
struct UILayout {                                      // cSPUILayout (windows owned by a layout)
    UIWindow* FindWindowByID(uint32_t id, int flag);   // 0x008105b0 (ret 8)
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

struct TerrainEditor;
struct NounManager {
    ElemVector* GetGameDataVector(void* a, void* b, void* c, void* d, uint32_t e);   // 0x00b21340 (ret 0x14)
    TerrainEditor* GetCurrentTerrainSphere();          // 0x00f67d90
};

struct TerrainEditor {
    char pad0[0x124c];
    int mField;                                        // +0x124c
};

// ---- foodweb slot table (vector at cSPUISpace+0x530, element 0x28) ----
struct FoodwebSlotInfo {                               // SP::cSPUISpace::cFoodwebSlotInfo
    UIWindow* mpWindow;                                // +0x00 (refcounted: v00 add, v01 release)
    char pad04[0xc];
    int mKind;                                         // +0x10
    uint32_t mKey;                                     // +0x14
    char pad18[8];
    int mIndex;                                        // +0x20
    int mFlag;                                         // +0x24
};
struct FoodwebSlotVector {                             // eastl::vector<cFoodwebSlotInfo> at +0x530
    FoodwebSlotInfo* mpBegin;                          // +0x00
    FoodwebSlotInfo* mpEnd;                            // +0x04
    FoodwebSlotInfo* mpCapacity;                       // +0x08
    void resize(int n);                                // 0x01070af0 (ret 4)
};

struct Key12 { uint32_t a, b, c; };

struct WindowSet {                                     // UI window set at cSPUISpace+0x620
    void RefreshWindows();                                     // 0x00e0a5c0
    void AttachWindow(UIWindow* w, const Key12* desc);       // 0x00e0a4c0 (ret 8)
    void SetFlags(const Key12* key, int count);          // 0x00e0a780 (ret 8)
    void* GetSlotLayout(int i);                               // 0x00e09c90 (ret 4)
};

struct FlagVector {                                    // vector<uint32_t> at cSPUISpace+0x5d8
    uint32_t* mpBegin;                                 // +0x00
    uint32_t* mpEnd;                                   // +0x04
    void SetValues(int arg, const int* value);           // 0x004746c0 (ret 8)
    void erase(uint32_t* first, uint32_t* last) {
        // The retail inline counts the moved tail in elements (the only caller passes an empty range).
        rt_memcpy(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= last - first;
    }
};

struct PosseEntry { uint32_t a, b; };

struct Posse {                                         // cSPUIPosse (at cSPUISpace+0x5c4)
    char pad0[0xa4];
    PosseEntry* mpBegin;                               // +0xa4
    PosseEntry* mpEnd;                                 // +0xa8
    Elem* FindItem(Elem* noun);                        // 0x00e24c90 (ret 4)
};

struct UfoItem {                                       // item returned by cSPUIPosse::FindItem
    void V80(uint32_t key, float ratio, int a, int b); // slot 0x80 (ret 0x10)
};

struct UfoNode {
    UfoNode* mpNext;                                   // +0x00
    char pad04[4];
    int mValue;                                        // +0x08
};
struct UfoList : UfoNode {                             // sentinel node embedded at +0x00
    char pad0c[0x10];
};

struct Ufo {
    UfoList* GetList();                              // 0x0108db30
};

struct PosseItemSpace {
    void* Construct(int a);                            // 0x00e259d0 (ctor-shaped, ret 4)
};

Ufo* GetUFOSimulator();                                // 0x00ffbe50
int GetPlayerEmpireID();                               // 0x01021090 (cdecl)
int FUN_0106b860(int arg);                             // 0x0106b860 (cdecl, 1 arg)
void* FUN_009512c0();                                  // 0x009512c0 (cdecl)
void* FUN_009512d0(int size, int align, const char* name, void* src);   // 0x009512d0 (cdecl, ret 0x10)
extern void FUN_00ad48b0();                            // 0x00ad48b0 (game-data vector filter)

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
    void InitFoodwebInfo();                            // 0x01071a00
    void SetupFoodwebWindows(int arg);                 // 0x01071c20 (ret 4)
    void RefreshPosseItems();                          // 0x01072680
    void SetSlot(uint32_t id, bool locked, const Key* key, bool scanned, bool flagA, bool same);   // 0x01068d30 (ret 0x18)
    void SetSlotValue(int index, uint32_t value);         // 0x0106dd10 (ret 8)
    char pad[0x224];
    GlobalUI* mGlobalLayout;                           // +0x224
    char pad228[0x258 - 0x228];
    UILayout* mpLayout;                                // +0x258
    char pad25c[0x530 - 0x25c];
    FoodwebSlotVector mFoodwebSlots;                   // +0x530
    char pad53c[0x5c4 - 0x53c];
    Posse* mpPosse;                                    // +0x5c4
    char pad5c8[0x5d8 - 0x5c8];
    FlagVector mFlags;                                 // +0x5d8
    char pad5e0[0x620 - 0x5e0];
    WindowSet mWindowSet;                              // +0x620
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

// @ 0x01071a00
void SP::cSPUISpace::InitFoodwebInfo()
{
    mFoodwebSlots.resize(0x12);
    for (int i = 0; i < 9; i++) {
        FoodwebSlotInfo& slot = mFoodwebSlots.mpBegin[i];
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(i + 0x37e89d0));
        UIWindow* old = slot.mpWindow;
        if (w != old) {
            if (w != 0)
                w->v00();
            slot.mpWindow = w;
            if (old != 0)
                old->v01();
        }
        slot.mKind = 0;
        if (i == 0 || i == 3 || i == 6)
            slot.mKey = 0x6d60a1cc;
        else if (i == 1 || i == 4 || i == 7)
            slot.mKey = 0x29c388a;
        else
            slot.mKey = 0x3a8be428;
        slot.mIndex = (int)((unsigned)i / 3) + 1;
        VT1(void, slot.mpWindow, 0x104, this);
    }
    for (int i = 0; i < 6; i++) {
        FoodwebSlotInfo& slot = mFoodwebSlots.mpBegin[9 + i];
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(i + 0x37e89d9));
        UIWindow* old = slot.mpWindow;
        if (w != old) {
            if (w != 0)
                w->v00();
            slot.mpWindow = w;
            if (old != 0)
                old->v01();
        }
        slot.mIndex = (int)((unsigned)i >> 1) + 1;
        slot.mFlag = i & 1;
        slot.mKind = 1;
        VT1(void, slot.mpWindow, 0x104, this);
    }
    // Rows 15..17 hold the three crop slots; the retail build counts them down.
    int row = 1;
    for (int remaining = 3; remaining != 0; --remaining) {
        FoodwebSlotInfo& slot = mFoodwebSlots.mpBegin[14 + row];
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(row + 0x37e89de));
        UIWindow* old = slot.mpWindow;
        if (w != old) {
            if (w != 0)
                w->v00();
            slot.mpWindow = w;
            if (old != 0)
                old->v01();
        }
        slot.mKind = 2;
        slot.mIndex = row;
        VT1(void, slot.mpWindow, 0x104, this);
        ++row;
    }
    for (int i = 0; i < 3; i++) {
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(i + 0x535cbd8));
        VT1(void, w, 0x104, this);
    }
}

// @ 0x01071c20
void SP::cSPUISpace::SetupFoodwebWindows(int arg)
{
    int count = FUN_0106b860(arg);
    mFlags.erase(mFlags.mpBegin, mFlags.mpEnd);
    int empire = GetPlayerEmpireID();
    mFlags.SetValues(count, &empire);
    mWindowSet.RefreshWindows();
    UIWindow* w = mpLayout->FindWindowByID(0x755f9b8, 1);
    Key12 desc;
    desc.a = 0;
    desc.b = 0;
    desc.c = 0;
    mWindowSet.AttachWindow(w, &desc);
    Key12 key;
    key.a = 0x1879822f;
    key.b = 0x510a95b;
    key.c = 0x40464100;
    mWindowSet.SetFlags(&key, 3);
    Ufo* ufo = GetUFOSimulator();
    UfoList* list = ufo->GetList();
    UfoNode* it = list->mpNext;
    for (int i = 0; i < 3; i++) {
        if (i < count) {
            if (it != list) {
                mFlags.mpBegin[i] = (uint32_t)it->mValue;
                it = it->mpNext;
            }
            SetSlotValue(i, mFlags.mpBegin[i]);
        } else {
            void* p = mWindowSet.GetSlotLayout(i);
            if (p == 0)
                return;
            UIWindow* w2 = ((UILayout*)p)->FindWindowByID(0x7eb2ea0, 1);
            if (w2 != 0)
                w2->SetFlag(1, 1);
        }
    }
}

// @ 0x01072680
void SP::cSPUISpace::RefreshPosseItems()
{
    if (mpPosse == 0)
        return;
    ElemVector* v = GetNounManager()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                        (void*)FUN_00ad48b0, (void*)FUN_00b1e500,
                                                        0x18ebadc);
    Elem** it = v->mpBegin;
    Elem** end = v->mpEnd;
    while (it != end) {
        Elem* noun = *it;
        if (noun->mType == 3) {
            UfoItem* item = (UfoItem*)mpPosse->FindItem(noun);
            if (item != 0)
                VT4F(void, item, 0x80, 0x3d99162, noun->mSim.NodeRatio() * kRatioScale, 1, 1);
        }
        ++it;
    }
    TerrainEditor* te = GetNounManager()->GetCurrentTerrainSphere();
    int n = te->mField;
    while ((int)(mpPosse->mpEnd - mpPosse->mpBegin) < n) {
        void* raw = FUN_009512d0(0x14c, 4, "UI/PosseItem", FUN_009512c0());
        void* item = raw != 0 ? ((PosseItemSpace*)raw)->Construct(0) : 0;
        VT1(void, mpPosse, 0xa4, item);
        VT1(void, mpPosse, 0xc0, 1);
    }
}
