// UpdateVehicleButtons @ 0x00E2B9D0 (2052 bytes, __thiscall, no args): cSPUIRolloverCivCityHall's refresh of the three
// "buy vehicle" buttons (windows 0x62d6902 / 0x62d6908 / 0x62d690f). For each button it works out whether the
// vehicle is available (the city's vehicle model key is non-null, and for button 1 the city has a target
// position) and affordable (player money >= cost), enables / shades the button and builds the tooltip text.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct Vector3 { float x, y, z; };

extern Vector3 gZeroVector;                                // 0x016ac548
extern wchar_t gEmptyStringBuf[2];                         // 0x01667bac (shared empty eastl string storage)
bool __cdecl Vector3_NotEqual(const Vector3* a, const Vector3* b);                // 0x0041dd30
bool __cdecl ResourceKey_Equal(const ResourceKey* a, const ResourceKey* b);        // 0x004eb930
void __cdecl ea_delete(void* p);                           // 0x00f47380

// eastl::basic_string<wchar_t> as the game uses it (the allocator member is never initialised here)
struct string16
{
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    string16() { mpBegin = gEmptyStringBuf; mpEnd = gEmptyStringBuf; mpCapacity = gEmptyStringBuf + 1; }
    ~string16()
    {
        if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            ea_delete(mpBegin);
    }
    void append(const wchar_t* b, const wchar_t* e);       // 0x00429580 (ret 8)
    string16& operator+=(const wchar_t* s);                // 0x00599bb0 (ret 4)
};

struct cString   // SP::cString, 0x14 bytes
{
    uint32_t d[5];
    cString();                                                                      // 0x006b5060
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* defaultText);   // 0x006b5770 (ret 0xc)
    ~cString();                                                                    // 0x006b5240
    const wchar_t* GetText();                                                      // 0x006b55c0
};

struct IWindow
{
    PV8 PV2
    virtual int IsVisible();                        // +0x28 (slot 10)
    PV8 PV4
    virtual void SetShade(uint32_t color);          // +0x5c (slot 23)
    PV4 PV2 PV
    virtual void SetFlag(int flag, bool on);        // +0x7c (slot 31)
};

class cSPUILayout
{ public:
    char data[0x9c];
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0 (ret 8)
};

struct cCity
{
    char pad000[0x32c];
    Vector3 mTarget;                                        // +0x32c (0x00fa0e00 returns its address)
    int GetVehicleSpecialty();                              // 0x00bd81d0
    Vector3* FUN_00fa0e00();                                // 0x00fa0e00
};

struct cCivilization
{
    int FUN_00bf2100(int specialty);                        // 0x00bf2100 (ret 4): vehicles available
    float FUN_00bf2170(int specialty, int index);           // 0x00bf2170 (ret 8): cost
    float GetMoney();                                       // 0x00bef6d0
    const ResourceKey* GetModelTypeKey(int modelType);      // 0x00bf9770 (ret 4)
    int FUN_00bf0c50();                                     // 0x00bf0c50: vehicle count
    int FUN_0113ab90();                                     // 0x0113ab90: returns 0x24 (capacity)
};

struct cGameNounManager { cCivilization* GetPlayerCivilization(); };   // 0x00b25fb0
cGameNounManager* __cdecl NounManager();                                // 0x00b3d300
int __cdecl FUN_00c9e6d0(int specialty, int index);                     // 0x00c9e6d0

struct IAudioSystem { PV8 virtual int GetPatch(); };                    // +0x20
IAudioSystem* __cdecl GetSystemAT();                                    // 0x00a206f0
void __cdecl KillSetiEffects(uint32_t id, int arg);                     // 0x00435ed0
void __cdecl SetTooltipText(IWindow* w, const wchar_t* text, uint32_t color, int flag);   // 0x00806de0
void __cdecl UpdateMouseFocus(int flag);                                // 0x00804f50

struct cCivModeStrategy
{
    static cCivModeStrategy* Get();                         // 0x00cf74c0
    bool CanBuildAirVehicles();                             // 0x00cf7600
};

class cSPUIRolloverCivCityHall
{ public:
    char pad000[0xc];
    cSPUILayout mLayout;                                    // +0x0c
    cCity* mpCity;                                          // +0xa8
    void UpdateVehicleButtons();
};

static __forceinline bool Vector3_Equal(const Vector3& a, const Vector3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
static __forceinline bool IsNonZero(const ResourceKey* k) { return k->instanceID != 0 || k->typeID != 0 || k->groupID != 0; }

#define APPEND_FILL_LINE() \
    do { \
        if (civ->FUN_00bf0c50() >= civ->FUN_0113ab90()) { cString line(0xc0152a6d, 0x65cd6f2, 0); text += line.GetText(); } \
        else { cString line(0xc0152a6d, 0x6562784, 0); text += line.GetText(); } \
    } while (0)

#define APPEND_LINE(ID) \
    do { cString line(0xc0152a6d, (ID), 0); text += line.GetText(); } while (0)

enum { kRed = 0xffff0000, kWhite = 0xffffffff };

void cSPUIRolloverCivCityHall::UpdateVehicleButtons()   // @ 0x00E2B9D0
{
    bool affordable;
    cCivilization* civ = NounManager()->GetPlayerCivilization();
    if (!civ || !mpCity)
        return;

    // ---- the city hall button: make sure the space music is not playing ----
    IWindow* w = mLayout.FindWindowByID(0x62d5618, true);
    if (!(w->IsVisible() & 1))
    {
        IAudioSystem* at = GetSystemAT();
        KillSetiEffects(0xa47319c2, at ? at->GetPatch() : 0);
    }
    w->SetFlag(1, true);

    // ---- vehicle button 0 ----
    ResourceKey zeroKey = { 0, 0, 0 };
    w = mLayout.FindWindowByID(0x62d6902, true);
    w->SetFlag(1, true);
    bool available = civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) > 0 &&
                     IsNonZero(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 0)));
    affordable = civ->FUN_00bf2170(mpCity->GetVehicleSpecialty(), 0) <= civ->GetMoney();
    w->SetFlag(2, available && affordable);
    if (available && !affordable) w->SetShade(kRed); else w->SetShade(kWhite);
    {
        string16 text;
        cString header(0xc0152a6d, 0x64a7064, 0);
        const wchar_t* p = header.GetText();
        const wchar_t* e = p; while (*e) ++e;
        text.append(p, p + (e - p));
        if (civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) == 0)
        {
            APPEND_FILL_LINE();
        }
        else
        {
            const ResourceKey* key = civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 0));
            if (key->instanceID == 0 && key->typeID == 0 && key->groupID == 0)
                APPEND_LINE(0x657690b);
            else if (!affordable)
                APPEND_LINE(0x671fb71);
        }
        uint32_t color;
        if (available && !affordable) color = kRed; else color = kWhite;
        SetTooltipText(w, text.mpBegin, color, 1);
    }

    // ---- vehicle button 1: also needs a target position ----
    w = mLayout.FindWindowByID(0x62d6908, true);
    w->SetFlag(1, true);
    available = civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) > 0 &&
                IsNonZero(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 1))) &&
                Vector3_NotEqual(mpCity->FUN_00fa0e00(), &gZeroVector);
    affordable = civ->FUN_00bf2170(mpCity->GetVehicleSpecialty(), 1) <= civ->GetMoney();
    w->SetFlag(2, available && affordable);
    if (available && !affordable) w->SetShade(kRed); else w->SetShade(kWhite);
    {
        string16 text;
        cString header(0xc0152a6d, 0x64a705d, 0);
        const wchar_t* p = header.GetText();
        const wchar_t* e = p; while (*e) ++e;
        text.append(p, p + (e - p));
        const Vector3* t = mpCity->FUN_00fa0e00();
        if (Vector3_Equal(*t, gZeroVector))
            APPEND_LINE(0x65767b3);
        else if (civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) == 0)
        {
            APPEND_FILL_LINE();
        }
        else
        {
            if (ResourceKey_Equal(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 1)), &zeroKey))
                APPEND_LINE(0x657690c);
            else if (!affordable)
                APPEND_LINE(0x671fb71);
        }
        uint32_t color;
        if (available && !affordable) color = kRed; else color = kWhite;
        SetTooltipText(w, text.mpBegin, color, 1);
    }

    // ---- vehicle button 2: air vehicle, needs CanBuildAirVehicles ----
    w = mLayout.FindWindowByID(0x62d690f, true);
    w->SetFlag(1, true);
    available = civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) > 0 &&
                     IsNonZero(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 2)));
    affordable = civ->FUN_00bf2170(mpCity->GetVehicleSpecialty(), 2) <= civ->GetMoney();
    w->SetFlag(2, available && affordable);
    if (available && !affordable) w->SetShade(kRed); else w->SetShade(kWhite);
    {
        string16 text;
        cString header(0xc0152a6d, 0x64a7057, 0);
        const wchar_t* p = header.GetText();
        const wchar_t* e = p; while (*e) ++e;
        text.append(p, p + (e - p));
        if (!cCivModeStrategy::Get()->CanBuildAirVehicles())
            APPEND_LINE(0x65767bb);
        else if (civ->FUN_00bf2100(mpCity->GetVehicleSpecialty()) == 0)
            APPEND_FILL_LINE();
        else if (ResourceKey_Equal(civ->GetModelTypeKey(FUN_00c9e6d0(mpCity->GetVehicleSpecialty(), 2)), &zeroKey))
            APPEND_LINE(0x657690d);
        else if (!affordable)
            APPEND_LINE(0x671fb71);
        uint32_t color;
        if (available && !affordable) color = kRed; else color = kWhite;
        SetTooltipText(w, text.mpBegin, color, 1);
    }

    UpdateMouseFocus(1);
}

// ============================================================================
// Slice s00e2b9d0 (continued): cSPUIRolloverCivCityVehicle / cSPUIRolloverCiv-
// Relationship and the rollover feedback grid (0x00e2c1e0 .. 0x00e2ca70).
// ============================================================================
namespace civroll {

// ---- eastl allocator / cString vector primitives ---------------------------
void* ea_operator_new(uint32_t size, const char* name, int flags, int align, const char* file, int line);  // 0x00f473a0

cString* F_e2a6f0(cString* a, cString* b, cString* c);                                  // 0x00e2a6f0
void     F_e2aad0(cString** out, cString* first, cString* last, cString* init, cString* extra);  // 0x00e2aad0
void     F_e2aaa0(cString* first, cString* last, cString* src);                         // 0x00e2aaa0
void     F_e2ad70(cString* dst, uint32_t n, const cString* src);                        // 0x00e2ad70
cString* F_aed430(cString* first, cString* last, cString* dst);                         // 0x00aed430
cString* F_aed510(cString* first, cString* last, cString* dst);                         // 0x00aed510
cString* F_aed470(cString* first, cString* last, cString* dst);                         // 0x00aed470

// eastl vector<SP::cString> (stride 0x14): begin/end/capacity triple
struct cStringVec
{
    cString* mpBegin;      // +0x00
    cString* mpEnd;        // +0x04
    cString* mpCapacity;   // +0x08
    ~cStringVec()
    {
        cString* end = mpEnd;
        for (cString* p = mpBegin; p < end; p = (cString*)((char*)p + 0x14))
            p->~cString();
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            ea_delete(mpBegin);
    }
    cString* Erase(cString* first, cString* last);                    // 0x00e2c290
    void     Insert(cString* pos, uint32_t n, const cString* value);  // 0x00e2c2f0
    void     Index(uint32_t i);                                       // 0x00e2ca70
};

// @ 0x00e2c290
cString* cStringVec::Erase(cString* first, cString* last)
{
    cString* p = F_e2a6f0(last, mpEnd, first);
    cString* end = mpEnd;
    while (p < end)
    {
        p->~cString();
        p = (cString*)((char*)p + 0x14);
    }
    const int count = (int)((char*)last - (char*)first) / 20;
    mpEnd = (cString*)((char*)mpEnd + count * 20);
    return first;
}

// @ 0x00e2c2f0
void cStringVec::Insert(cString* pos, uint32_t n, const cString* value)
{
    const uint32_t room = (uint32_t)((int)((char*)mpCapacity - (char*)mpEnd) / 20);
    if (room < n)
    {
        const int size = (int)((char*)mpEnd - (char*)mpBegin) / 20;
        uint32_t newCapacity = (uint32_t)size * 2;
        if (size == 0)
            newCapacity = 1;
        uint32_t total = (uint32_t)size + n;
        if (total < newCapacity)
            total = newCapacity;
        cString* buf = total ? (cString*)ea_operator_new(total * 20, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        cString* p = F_aed430(mpBegin, pos, buf);
        F_aed510(mpBegin, pos, buf);
        F_e2ad70(p, n, value);
        cString* after = (cString*)((char*)p + n * 20);
        cString* end = mpEnd;
        cString* q = F_aed430(pos, end, after);
        F_aed510(pos, end, after);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            ea_delete(mpBegin);
        mpEnd = q;
        mpBegin = buf;
        mpCapacity = (cString*)((char*)buf + total * 20);
    }
    else if (n != 0)
    {
        cString tmp;
        cString* end = mpEnd;
        const uint32_t room2 = (uint32_t)((int)((char*)end - (char*)pos) / 20);
        if (n < room2)
        {
            cString* m = (cString*)((char*)end - n * 20);
            cString* out = 0;
            F_e2aad0(&out, m, end, end, 0);
            cString* p = pos;
            mpEnd = (cString*)((char*)mpEnd + n * 20);
            F_aed470(p, m, end);
            F_e2aaa0(p, (cString*)((char*)p + n * 20), &tmp);
        }
        else
        {
            F_e2ad70(end, n - room2, &tmp);
            cString* p = pos;
            mpEnd = (cString*)((char*)mpEnd + (n - room2) * 20);
            F_e2aad0(&p, pos, end, mpEnd, 0);
            mpEnd = (cString*)((char*)mpEnd + room2 * 20);
            F_e2aaa0(pos, end, &tmp);
        }
        tmp.~cString();
    }
}

// @ 0x00e2ca70
void cStringVec::Index(uint32_t i)
{
    if (i > (uint32_t)((int)((char*)mpEnd - (char*)mpBegin) / 20))
    {
        cString tmp;
        Insert(mpEnd, i - (uint32_t)((int)((char*)mpEnd - (char*)mpBegin) / 20), &tmp);
    }
    else
    {
        Erase((cString*)((char*)mpBegin + i * 20), mpEnd);
    }
}

// ---- cSPUIRolloverCivCityVehicle -------------------------------------------
struct Variant;

struct CPL
{
    void*  mpVftable;      // +0x00
    void*  mpVftable2;     // +0x04
    char   pad008[0x3c];   // +0x08
    bool   mFlag44;        // +0x44
    char   pad045[0x33];   // +0x45..0x78
    CPL();                                                      // 0x008286d0
    ~CPL();                                                     // 0x00828670
    bool   Init();                                              // 0x00828250
    void*  GetRootWindow();                                     // 0x00828100
    void   SetKey(const wchar_t* key, uint32_t flags);          // 0x00827fc0 (ret 8)
    void   SetRootWindowId(uint32_t id);                        // 0x00c87bc0 (ret 4)
    bool   func24h();                                           // 0x00828be0
    void   SetProp(uint32_t id, Variant* v, int a, int b);      // 0x00828c30 (ret 0x10)
};

struct cSPUIRolloverCivCityVehicle : CPL
{
    void SetPurposeIcon(uint32_t icon);                          // 0x00e2b4f0
    bool Initialize();                                           // @ 0x00e2c1e0
};

// @ 0x00e2c1e0
bool cSPUIRolloverCivCityVehicle::Initialize()
{
    if (Init())
    {
        SetPurposeIcon(0x338babf);
        return true;
    }
    return false;
}

// ---- rollover feedback grid (rbtree<uint32, FeedbackEvent>) ----------------
struct FeedbackEvent { int mField00, mField04, mField08, mField0c; };

struct FeedbackNode
{
    void*           mpLeft;    // +0x00
    void*           mpRight;   // +0x04
    void*           mpParent;  // +0x08
    uint32_t        mColor;    // +0x0c
    uint32_t        mKey;      // +0x10
    FeedbackEvent   mValue;    // +0x14
};

struct IdMap
{
    void*           mpField00;   // +0x00
    FeedbackNode*   mpAnchor;    // +0x04 (sentinel node: right/parent/color follow)
    FeedbackNode*   mpAnchorEnd; // +0x08
    FeedbackNode*   mpRoot;      // +0x0c
    uint32_t        mnColor;     // +0x10
    uint32_t        mnSize;      // +0x14
    uint32_t        mField18;    // +0x18
    void Find(FeedbackNode** out, const uint32_t* key);                       // 0x00e5c780
    void Insert(FeedbackNode** out, const FeedbackEvent* value, uint32_t key); // 0x00e2c200
};

class cSPUIRolloverFeedbackGrid
{
public:
    void*           mpVftable;   // +0x00
    char            pad004[0x74];// +0x04
    IdMap           mMap;        // +0x78
    int             mCounter94;  // +0x94
    int             mField98;    // +0x98
    int             mField9c;    // +0x9c
    int             mPerRowA0;   // +0xa0
    bool  FUN_00e2c840(uint32_t key, int a, int b);   // 0x00e2c840
    void  FUN_00e2ab10(uint32_t key);                 // 0x00e2ab10
};

// @ 0x00e2c840
bool cSPUIRolloverFeedbackGrid::FUN_00e2c840(uint32_t key, int a, int b)
{
    int page = (mPerRowA0 + a - 1) / mPerRowA0;
    if (!(page > 0))
        page = 1;

    FeedbackNode* node;
    mMap.Find(&node, &key);
    if ((void*)node == (void*)&mMap.mpAnchor)
    {
        FeedbackEvent value;
        value.mField00 = 0;
        value.mField04 = 0;
        value.mField08 = 0;
        value.mField0c = 0;
        value.mField08 = (int)key;
        const uint32_t maskedKey = key & 0xffffff00u;
        mMap.Insert(&node, &value, maskedKey);
        if (key != (uint32_t)mField9c)
            node->mValue.mField08 = ++mCounter94;
        else
            node->mValue.mField08 = 0;
    }

    node->mValue.mField04 = page;
    node->mValue.mField0c = b;
    node->mValue.mField00 = a;

    if (key == (uint32_t)mField9c &&
        (node->mValue.mField08 > 0 || mField98 != b))
        FUN_00e2ab10(key);
    return true;
}

// ---- cSPUIRolloverCivRelationship ------------------------------------------
struct RBTree
{
    void*     mpField00;   // +0x00
    void*     mpAnchor;    // +0x04
    void*     mpAnchorEnd; // +0x08
    void*     mpRoot;      // +0x0c
    union { uint32_t mnColor; uint8_t mbColor; };   // +0x10
    uint32_t  mnSize;      // +0x14
    uint32_t  mField18;    // +0x18
    uint32_t  mFieldF8;    // +0x1c
    void DoNukeSubtree(void* node);                     // 0x00e2b680 (this = tree)
};

struct cSPUIRolloverCivRelationship : CPL
{
    cString      mString78;    // +0x78
    cString      mString8c;    // +0x8c
    cString      mStringA0;    // +0xa0
    cString      mStringB4;    // +0xb4
    cStringVec   mVecC8;       // +0xc8
    char         padD4[8];     // +0xd4..0xdb
    RBTree       mMapDC;       // +0xdc

    cSPUIRolloverCivRelationship();
    ~cSPUIRolloverCivRelationship();
    void Shutdown();
};

// @ 0x00e2c920
cSPUIRolloverCivRelationship::cSPUIRolloverCivRelationship()
{
    mpVftable = (void*)0x148175c;
    mpVftable2 = (void*)0x148174c;
    mVecC8.mpBegin = 0;
    mVecC8.mpEnd = 0;
    mVecC8.mpCapacity = 0;
    mMapDC.mpAnchorEnd = 0;
    mMapDC.mpRoot = 0;
    mMapDC.mnColor = 0;
    mMapDC.mpRoot = 0;
    mMapDC.mbColor = 0;
    mMapDC.mnSize = 0;
    mMapDC.mpAnchor = &mMapDC.mpAnchor;
    mMapDC.mpAnchorEnd = &mMapDC.mpAnchor;
    mMapDC.mFieldF8 = 0;
    SetKey(L"CivCommRollover", 0x40464100);
    SetRootWindowId(0x4d18738);
}

// @ 0x00e2c4f0
cSPUIRolloverCivRelationship::~cSPUIRolloverCivRelationship()
{
    mpVftable = (void*)0x148175c;
    mpVftable2 = (void*)0x148174c;
    mMapDC.DoNukeSubtree(mMapDC.mpRoot);
}

// ---- IWindow with the wider virtual table used by the rollover code --------
class IWindowEx
{
public:
    PV2 PV                                              // slots 0-2
    virtual void* GetChildByID(uint32_t id);            // slot 3  (+0x0c)
    PV4 PV2                                             // slots 4-9
    virtual void  SetColor(uint32_t color);             // slot 10 (+0x28)
    PV8 PV4                                             // slots 11-22
    virtual void  SetShade(uint32_t color);             // slot 23 (+0x5c)
    PV4 PV2 PV                                          // slots 24-30
    virtual void  SetFlag(int flag, bool on);           // slot 31 (+0x7c)
    PV8 PV8 PV4 PV2 PV                                  // slots 32-54
    virtual void  DisposeWindow(void* w);               // slot 55 (+0xdc)
    PV4                                                 // slots 56-59
    virtual IWindowEx* FindWindow(uint32_t id, int recurse);   // slot 60 (+0xf0)
};

struct cSPUILayoutManager
{
    void* GetWorldMainWindow();                 // 0x00810620
};

cSPUILayoutManager* __stdcall SPUIHelpers_GetLayoutManager(uint32_t id);   // 0x00805070

// @ 0x00e2c9f0
void cSPUIRolloverCivRelationship::Shutdown()
{
    if (mFlag44)
    {
        cSPUILayoutManager* lm = SPUIHelpers_GetLayoutManager(0x5b598f6);
        IWindowEx* world = (IWindowEx*)lm->GetWorldMainWindow();
        world->DisposeWindow(GetRootWindow());
    }
    mMapDC.DoNukeSubtree(mMapDC.mpRoot);
    mMapDC.mpAnchor = &mMapDC.mpAnchor;
    mMapDC.mpAnchorEnd = &mMapDC.mpAnchor;
    mMapDC.mpRoot = 0;
    mMapDC.mbColor = 0;
    mMapDC.mnSize = 0;
    mVecC8.Erase(mVecC8.mpBegin, mVecC8.mpEnd);
    func24h();
}

// ---- SetValueTextForRollover -----------------------------------------------
struct WStr
{
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    void RangeInitialize(const wchar_t* s);                  // 0x00579a90 (this = string)
    void assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
};

struct Variant
{
    char     mData[0x10];   // +0x00
    uint16_t mFlags;        // +0x10
    uint16_t mTypeId;       // +0x12
    void Set(uint32_t type, uint32_t kind, void* p, uint32_t size, uint32_t copy);  // 0x0093dd80
    void Destruct(int a);                                                          // 0x0093db80
};

void   __cdecl SetNumberString(long long v, wchar_t* buffer, int n);   // 0x00881ae0
WStr*  eastl_operator_plus(WStr* out, const wchar_t* prefix, WStr* self);  // 0x006309e0
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

static __forceinline void WStr_Free(WStr& s)
{
    if (((int)((char*)s.mpCapacity - (char*)s.mpBegin) & ~1) > 2 && s.mpBegin)
        ea_delete(s.mpBegin);
}

// eastl string concat: allocate into a temporary, copy back into text if a new buffer was made.
extern const wchar_t gwPlus[];    // 0x01419de8
extern const wchar_t gwMinus[];   // 0x013faf54

// @ 0x00e2c590
void SetValueTextForRollover(cSPUIRolloverCivRelationship* layout, uint32_t id, float value)
{
    wchar_t number[64];
    IWindowEx* root = (IWindowEx*)layout->GetRootWindow();
    IWindowEx* w = root->FindWindow(id, 1);
    if (!w)
        return;
    IWindowEx* child = (IWindowEx*)w->GetChildByID(0xf15f4bd);
    if (!child)
        return;

    SetNumberString((long long)fabs((double)(value * 100.0f)), number, 0x40);

    Variant var;
    WStr text;
    text.mpBegin = 0;
    text.mpEnd = 0;
    text.mpCapacity = 0;
    text.RangeInitialize(number);

    if (value > 0.0f)
    {
        {
            WStr tmp;
            WStr* r = eastl_operator_plus(&tmp, gwPlus, &text);
            if (r != &text)
                text.assign(r->mpBegin, r->mpEnd);
            WStr_Free(tmp);
        }
        child->SetColor(0xff00ff00);
    }
    if (value < 0.0f)
    {
        {
            WStr tmp;
            WStr* r = eastl_operator_plus(&tmp, gwMinus, &text);
            if (r != &text)
                text.assign(r->mpBegin, r->mpEnd);
            WStr_Free(tmp);
        }
        child->SetColor(0xffff0000);
    }

    var.mFlags = 0;
    var.mTypeId = 0;
    var.Set(0x13, 9, &text, 0x10, 1);
    layout->SetProp(id, &var, 1, 0);
    if (var.mFlags & 4)
        var.Destruct(0);
    WStr_Free(text);
}

}  // namespace civroll
