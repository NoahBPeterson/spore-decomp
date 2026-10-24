// Slice s00bdde70: SP::cCity::UpdateCityHallRollover (0x00bdde70), __thiscall ret 4.
//
// Fills the civ-stage city rollover (cSPUIRolloverCivCityHall) with this city's data:
//   * the allegiance bar: one entry per empire that owns part of the city, in the empire's color,
//     the city's own civilization selected;
//   * the title text (string 0x68c71fb / 0x653ea92 of table 0xdc351566) into property 0x2cf2f74;
//   * the income number's text color: green while the party is on (happiness above 50), red during
//     a riot (below 50), cyan otherwise, white when the income is not positive;
//   * five happiness bars (properties 0x4fe1aa0..) and five healthy-citizen bars (0x4fe38f0..);
//   * the relationship value toward the player (0x46adf86) and the housing count (0x199a7d2);
//   * the city name (0x2cf2f44), the vehicle specialty icon and the player-city button state.
// Every callee/global is a masked relocation; the stub classes below fix calling conventions,
// argument lists, vtable slots and field offsets only.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0
void __cdecl operator delete[](void* p);                                   // 0x00F47380

enum
{
    kGameModeCiv   = 0x01654c04,
    kGameModeSpace = 0x01654c05,
};

struct WStr {  // eastl::basic_string<wchar_t> (begin, end, capacity-end)
    wchar_t *b, *e, *cap;
};

struct Variant {  // EA::Variant
    char data[0x10];
    unsigned short mFlags;
    unsigned short mTypeId;
    void Set(int type, int kind, const void* p, int size, int copy);   // 0x0093dd80
    void Destruct(int);                                                // 0x0093db80
};

struct cString {  // SP::cString
    char d[0x14];
    cString();                                                         // 0x006b5060
    ~cString();                                                        // 0x006b5240
    void Load(unsigned int tableId, unsigned int instanceId, int flag); // 0x006b54b0 (ret 0xc)
    const wchar_t* GetText();                                          // 0x006b55c0
};

struct IColorable {  // interface cast out of a window (typeID 0xf15f4bd)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void SetColor(unsigned int argb);                          // +0x28
};

struct IWindow {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual IColorable* Cast(unsigned int typeID);                     // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindow(unsigned int id, int recurse);         // +0xf0
};

// rollover UI
class cSPUIRolloverCivCityHall
{ public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Refresh();                                            // +0x20
    char pad04[0x78 - 0x4];
    IWindow* GetRootWindow();                                          // 0x00828100
    void ClearEntries();                                               // 0x00e2adb0
    void AddEntry(int slot, int count, unsigned int argb);             // 0x00e2c840 (ret 0xc)
    void SelectEntry(int slot);                                        // 0x00e2ab10 (ret 4)
    void SetProp(unsigned int id, Variant* v, int a, int b);           // 0x00828c30 (ret 0x10)
    void SetSpecialtyIcon(unsigned int id);                            // 0x00e2a7b0 (ret 4)
    void SetOwnerButtonState(bool b);                                  // 0x00e2a600 (ret 4)
};

struct cColor3c { unsigned int GetARGB(); };                           // 0x00b6f310 (on civ+0x3c)

struct cCivilization
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetRelationshipEmpire(int empireId);                   // +0x4c
    char pad04[0x3c - 0x4];
    cColor3c mColor;                                                   // +0x3c
};

struct cGameNounManager
{
    cCivilization* FindCivilization(unsigned int empireId);            // 0x00b25f40 (ret 4)
    cCivilization* GetPlayerCivilization();                            // 0x00b25fb0
    int GetPlayerEmpireOrMinus1();                                     // 0x00b1f9d0 (does not use this)
};

struct cCivModeStrategy { void SetSelectedCity(void* city); };         // 0x00cfe780 (ret 4)
extern cCivModeStrategy* gCivModeStrategy;                             // 0x0169d3c8

struct ICityName
{
    virtual void v00();
    virtual const wchar_t* GetName();                                  // +0x4
};

struct RBNode { RBNode* mpRight; RBNode* mpLeft; RBNode* mpParent; int mColor; unsigned int mKey; int mValue; };
RBNode* RBTreeIncrement(RBNode* p);                                    // 0x00921580 (cdecl)

struct cCombatant { int GetDamageState(); };                           // 0x008e7f80
struct cCitizen { char pad[0x588]; cCombatant mCombatant; };           // +0x588

cGameNounManager* NounManager();                                       // 0x00b3d300
int GetCurrentGameMode();                                              // 0x00b5b800
float GetRelationshipValue(int otherEmpire, int myEmpire);             // 0x00d00d00 (cdecl, float in st0)
extern wchar_t gEmptyW[2];                                             // 0x01667bac

static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct cSPTimer {
    long long GetElapsedTime();               // 0x00bc3190 (returns edx:eax)
    void Restart();                           // 0x00bc3130
};

struct cCity
{
    char pad000[0x34];
    ICityName mName;                                                   // +0x34 (embedded, own vtable)
    char pad038[0x120 - 0x38];
    void* mpSpaceGame;                                                 // +0x120 (Simulator space-game object)
    char pad124[0x304 - 0x124];
    float mfHappiness;                                                 // +0x304
    char pad308[0x32c - 0x308];
    float mPosX;                                                       // +0x32c (Vector3 position)
    float mPosY;                                                       // +0x330
    float mPosZ;                                                       // +0x334
    char pad338[0x33c - 0x338];
    bool mbIsPlayerCity;                                               // +0x33c
    char pad33d[0x354 - 0x33d];
    cCitizen** mCitizensBegin;                                         // +0x354
    cCitizen** mCitizensEnd;                                           // +0x358
    char pad35c[0x540 - 0x35c];
    int mVehicleSpecialty;                                             // +0x540
    char pad544[0x590 - 0x544];
    cCivilization* mpCivilization;                                     // +0x590
    char pad594[0x5a4 - 0x594];
    RBNode* mAllegianceAnchorRight;                                    // +0x5a4 (map<uint,int> anchor)
    RBNode* mAllegianceBegin;                                          // +0x5a8
    char pad5ac[0x668 - 0x5ac];
    int mHappyCount;                                                   // +0x668
    int mUnhappyCount;                                                 // +0x66c
    char pad670[0x678 - 0x670];
    int mFinalIncome;                                                  // +0x678
    char pad67c[0x698 - 0x67c];
    bool mPartyOn;                                                     // +0x698
    char pad699[0x6c0 - 0x699];
    bool mRiotOn;                                                      // +0x6c0
    char pad6c1[0x708 - 0x6c1];
    cSPTimer mTimer;                                                   // +0x708

    int GetHousingAmount();                                            // 0x00bd8960
    void UpdateCityHallRollover(cSPUIRolloverCivCityHall* pUI);
    int* FUN_00bde4a0();                                               // 0x00bde4a0 (__fastcall, this in ecx)
};

// Inline-constructed wstring from a zero-terminated buffer (eastl basic_string(const T*) inlined).
static __forceinline int CharStrlen(const wchar_t* p)
{
    const wchar_t* q = p;
    while (*q)
        ++q;
    return (int)(q - p);
}

static __forceinline void MakeWStr(WStr& s, const wchar_t* p)
{
    s.b = s.e = s.cap = 0;
    const wchar_t* pEnd = p + CharStrlen(p);
    int n = (int)(pEnd - p);
    unsigned int sz = n + 1;
    wchar_t* buf;
    if (sz > 1) {
        buf = (wchar_t*)operator new(sz * 2, "Simulator", 0, 0, kEastlFile, 0xd1);
        s.b = buf;
        s.cap = (wchar_t*)((char*)buf + sz * 2);
    } else {
        buf = gEmptyW;
        s.b = gEmptyW;
        s.cap = gEmptyW + 1;
    }
    s.e = buf;
    memcpy(buf, p, n * 2);
    s.e = buf + n;
    *s.e = 0;
}

static __forceinline void FreeWStr(WStr& s)
{
    if ((int)(((char*)s.cap - (char*)s.b) & ~1) > 2 && s.b)
        operator delete[](s.b);
}

static __forceinline void SetStringProp(cSPUIRolloverCivCityHall* pUI, unsigned int id, WStr& s)
{
    Variant v;
    v.mFlags = 0;
    v.mTypeId = 0;
    v.Set(0x13, 9, &s, 0x10, 1);
    pUI->SetProp(id, &v, 1, 0);
    if (v.mFlags & 4)
        v.Destruct(0);
}

static __forceinline void SetFloatProp(cSPUIRolloverCivCityHall* pUI, unsigned int id, float f)
{
    Variant v;
    v.mTypeId = 0xd;
    v.mFlags = 0;
    *(float*)v.data = f;
    pUI->SetProp(id, &v, 2, 0);
    if (v.mFlags & 4)
        v.Destruct(0);
}

// @ 0x00bdde70
void cCity::UpdateCityHallRollover(cSPUIRolloverCivCityHall* pUI)
{
    IWindow* pRoot = pUI->GetRootWindow();
    int slot = 0;
    pUI->ClearEntries();
    for (RBNode* pNode = mAllegianceBegin; pNode != (RBNode*)&mAllegianceAnchorRight; pNode = RBTreeIncrement(pNode)) {
        int count = pNode->mValue;
        unsigned int empireId = pNode->mKey;
        if (count > 0) {
            cCivilization* pCiv = NounManager()->FindCivilization(empireId);
            if (pCiv) {
                pUI->AddEntry(slot, count, pCiv->mColor.GetARGB());
                if (pCiv == mpCivilization)
                    pUI->SelectEntry(slot);
                ++slot;
            }
        }
    }

    int mode = GetCurrentGameMode();
    unsigned int titleId = mode == kGameModeSpace ? 0x68c71fb : 0x653ea92;
    gCivModeStrategy->SetSelectedCity(this);
    cString title;
    title.Load(0xdc351566, titleId, 0);
    WStr titleText;
    MakeWStr(titleText, title.GetText());
    SetStringProp(pUI, 0x2cf2f74, titleText);

    IWindow* pWindow = pRoot->FindWindow(0x2cf2f74, 1);
    IColorable* pIncomeText = pWindow ? pWindow->Cast(0xf15f4bd) : 0;

    int income = mFinalIncome;
    if (GetCurrentGameMode() != kGameModeSpace) {
        if (mPartyOn && mfHappiness > 50.0f)
            income = income * 2;
        if (mRiotOn && mfHappiness < 50.0f)
            income = income / 2;
    }
    if (income > 0) {
        if (mPartyOn && mfHappiness > 50.0f)
            pIncomeText->SetColor(0xff00ff00);
        else if (mRiotOn && mfHappiness < 50.0f)
            pIncomeText->SetColor(0xffff0000);
        else
            pIncomeText->SetColor(0xff00ffff);
    } else {
        pIncomeText->SetColor(0xffffffff);
    }

    int diff = mHappyCount - mUnhappyCount;
    for (int i = 0; i < 5; ++i) {
        float f = 0.0f;
        if (diff > 0) {
            if (i < diff)
                f = 100.0f;
        } else if (diff < 0) {
            if (i < -diff)
                f = 50.0f;
        }
        SetFloatProp(pUI, i + 0x4fe1aa0, f);
    }

    int healthy = 0;
    for (cCitizen** it = mCitizensBegin; it != mCitizensEnd; ++it) {
        if ((*it)->mCombatant.GetDamageState() == 0)
            ++healthy;
    }
    for (int i = 0; i < 5; ++i) {
        float f = 0.0f;
        if (i < healthy)
            f = 100.0f;
        SetFloatProp(pUI, i + 0x4fe38f0, f);
    }

    cCivilization* pCiv = mpCivilization;
    float relation;
    if (pCiv == NounManager()->GetPlayerCivilization()) {
        relation = 50.0f;
    } else {
        int myEmpire = NounManager()->GetPlayerEmpireOrMinus1();
        relation = GetRelationshipValue(pCiv->GetRelationshipEmpire(myEmpire), myEmpire);
    }
    SetFloatProp(pUI, 0x46adf86, relation);

    {
        Variant v;
        v.mTypeId = 9;
        v.mFlags = 0;
        *(int*)v.data = GetHousingAmount();
        pUI->SetProp(0x199a7d2, &v, 1, 0);
        if (v.mFlags & 4)
            v.Destruct(0);
    }

    {
        WStr nameText;
        MakeWStr(nameText, mName.GetName());
        SetStringProp(pUI, 0x2cf2f44, nameText);
        FreeWStr(nameText);
    }

    if (GetCurrentGameMode() == kGameModeCiv) {
        unsigned int icon;
        switch (mVehicleSpecialty) {
        case 0: icon = 0x2cf2f38; break;
        case 1: icon = 0x2cf2f34; break;
        case 2: icon = 0x2cf2f30; break;
        default: icon = 0; break;
        }
        pUI->SetSpecialtyIcon(icon);
    } else if (GetCurrentGameMode() == kGameModeSpace) {
        pUI->SetSpecialtyIcon(0);
    }

    pUI->SetOwnerButtonState(!mbIsPlayerCity);
    pUI->Refresh();
    FreeWStr(titleText);
}

// ================================================================ s00bdde70 additions
// eastl vector<T,A> growth helpers for SP::cCity's containers, plus the cCity
// "rollover update" tick.  Elements are plain POD copies, so the helpers are
// written in terms of named element structs.

struct EmptyBubble {                // SP::cEmptyBubble  (0x14): 4 floats + an id
    float f00, f04, f08, f0c;
    int   f10;
};
struct EmptyBubbleRaw { int f00, f04, f08, f0c, f10; };   // trivial-view for eastl::copy

struct CityBubble {                 // 0x50-byte element (Simulator bubble)
    int f00, f04, f08, f0c, f10, f14, f18, f1c;
    int f20, f24, f28, f2c, f30, f34, f38, f3c;
    int f40, f44, f48, f4c;
};

struct RunInfo {                    // EA::Text::Typesetter::RunInfo (0x10)
    float a, b, c, d;
};
struct RunInfoRaw { int a, b, c, d; };   // trivial-view for eastl::copy

// generic eastl vector header: begin, end, capacity-end
template <class T> struct Vec3 { T* b; T* e; T* cap; void DoInsertValue(T* pos, T* value); };

extern char* gAllocator;            // 0x013ebb38 (eastl allocator instance)
extern void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00F473A0

void __cdecl FUN_00c50ad0(void* first, void* last, void* dst);      // 0x00c50ad0 (copy_backward, 0x14 elems)
void* __cdecl FUN_00bda850(void* src, void* dst, void* out);        // 0x00bda850 (uninitialized_copy, 0x14 elems)
void __cdecl FUN_00bda7d0(void* elem);                              // 0x00bda7d0 (copy-construct, 0x50 elems)
void* __cdecl FUN_00bdaa00(void* src, void* dst, void* out);        // 0x00bdaa00 (uninitialized_copy, 0x50 elems)
void* __cdecl FUN_00b115c0(void* src, void* dst, void* out);        // 0x00b115c0 (uninitialized_copy, 0x10 elems)
void __cdecl FUN_00edba80(void* first, void* last, void* dst);      // 0x00edba80 (copy_backward, RunInfo)

// @ 0x00bde910 -- eastl::vector<SP::cEmptyBubble,A>::DoInsertValue(pos, value)
template <> void Vec3<EmptyBubble>::DoInsertValue(EmptyBubble* pos, EmptyBubble* value)
{
    EmptyBubble* end = e;
    if (end != cap) {
        if (pos <= value && value < end)
            value = value + 1;
        if (end) {
            end->f00 = end[-1].f00;
            end->f04 = end[-1].f04;
            end->f08 = end[-1].f08;
            end->f0c = end[-1].f0c;
            end->f10 = end[-1].f10;
        }
        FUN_00c50ad0(pos, e - 1, e);
        *(EmptyBubbleRaw*)pos = *(EmptyBubbleRaw*)value;        ++e;
        return;
    }
    unsigned n = (unsigned)((char*)end - (char*)b) / 0x14;
    EmptyBubble* nb = 0;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0)
            nb = 0;
    }
    if (nb == 0 && n != 0)
        nb = (EmptyBubble*)operator new(n * 0x14, "Simulator", 0, 0, kEastlFile, 0xd1);
    EmptyBubble* p = (EmptyBubble*)FUN_00bda850(b, pos, nb);
    if (p) {
        p->f00 = value->f00; p->f04 = value->f04; p->f08 = value->f08;
        p->f0c = value->f0c; p->f10 = value->f10;
    }
    EmptyBubble* ne = (EmptyBubble*)FUN_00bda850(pos, e, p + 1);
    if (b && *(int*)((char*)b - 4) != 0)
        operator delete[](b);
    b = nb;
    e = ne;
    cap = nb + n;
}

// @ 0x00bdeb10 -- eastl::copy_backward for 0x50-byte elements: copies [src,end)
// into [dst,...) and advances the vector end by (src-dst).  Returns dst.
struct CityVec50 { char pad[4]; CityBubble* e; CityBubble* cap;
    CityBubble* CopyBack(CityBubble* dst, CityBubble* src); };
CityBubble* CityVec50::CopyBack(CityBubble* dst, CityBubble* src)
{
    CityBubble* end = e;
    CityBubble* d = dst;
    CityBubble* s = src;
    while (s != end) {
        *d = *s;
        d = (CityBubble*)((char*)d + 0x50);
        s = (CityBubble*)((char*)s + 0x50);
    }
    e = (CityBubble*)((char*)e + ((int)((char*)dst - (char*)src) / (int)0x50) * 0x50);
    return dst;
}

// @ 0x00bdecb0 -- destroy a range of 0x60-byte elements: free the two owned
// buffers at +0x40 and +0x50.
struct CityElem60 { char pad[0x60]; };
void __stdcall FUN_00bdecb0(CityElem60* b, CityElem60* e)
{
    for (; b < e; b = (CityElem60*)((char*)b + 0x60)) {
        char* p = *(char**)((char*)b + 0x50);
        if (*(int*)((char*)b + 0x58) - (int)p > 1 && p)
            operator delete[](p);
        char* q = *(char**)((char*)b + 0x40);
        if (*(int*)((char*)b + 0x48) - (int)q > 1 && q)
            operator delete[](q);
    }
}

// 0x50-byte and 0x10-byte element vectors' growth helpers.
typedef void (__thiscall *CopyCtorFn)(void* self, const void* src);   // 0x00bda7d0, ret 4

struct Vec50 { CityBubble* b; CityBubble* e; CityBubble* cap;
    void DoInsertValue(CityBubble* pos, CityBubble* value); };

struct Vec10 { RunInfo* b; RunInfo* e; RunInfo* cap;
    void DoInsertValue(RunInfo* pos, RunInfo* value); };

// @ 0x00bdeb80 -- eastl::vector<CityBubble,A>::DoInsertValue(pos, value)
void Vec50::DoInsertValue(CityBubble* pos, CityBubble* value)
{
    CityBubble* end = e;
    if (end != cap) {
        if (pos <= value && value < end)
            value = value + 1;
        if (end)
            ((CopyCtorFn)0x00bda7d0)(end, end - 1);
        CityBubble* s = end - 1;
        CityBubble* d = end - 1;
        while (s != pos) {
            s = s - 1;
            d = d - 1;
            *d = *s;
        }
        *pos = *value;
        ++e;
        return;
    }
    unsigned n = (unsigned)((char*)end - (char*)b) / 0x50;
    CityBubble* nb = 0;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0)
            nb = 0;
    }
    if (nb == 0 && n != 0)
        nb = (CityBubble*)operator new(n * 0x50, "Simulator", 0, 0, kEastlFile, 0xd1);
    CityBubble* p = (CityBubble*)FUN_00bdaa00(b, pos, nb);
    if (p)
        ((CopyCtorFn)0x00bda7d0)(p, value);
    CityBubble* ne = (CityBubble*)FUN_00bdaa00(pos, e, p + 1);
    if (b && *(int*)((char*)b - 4) != 0)
        operator delete[](b);
    b = nb;
    e = ne;
    cap = nb + n;
}

// @ 0x00bded00 -- eastl::vector<RunInfo,A>::DoInsertValue(pos, value)
void Vec10::DoInsertValue(RunInfo* pos, RunInfo* value)
{
    RunInfo* end = e;
    if (end != cap) {
        if (pos <= value && value < end)
            value = value + 1;
        if (end) {
            end->a = end[-1].a;
            end->b = end[-1].b;
            end->c = end[-1].c;
            end->d = end[-1].d;
        }
        FUN_00edba80(pos, e - 1, e);
        *(RunInfoRaw*)pos = *(RunInfoRaw*)value;
        ++e;
        return;
    }
    unsigned n = (unsigned)((char*)end - (char*)b) / 0x10;
    RunInfo* nb = 0;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0)
            nb = 0;
    }
    if (nb == 0 && n != 0)
        nb = (RunInfo*)operator new(n * 0x10, "Simulator", 0, 0, kEastlFile, 0xd1);
    RunInfo* p = (RunInfo*)FUN_00b115c0(b, pos, nb);
    if (p)
        *p = *value;
    RunInfo* ne = (RunInfo*)FUN_00b115c0(pos, e, p + 1);
    if (b && *(int*)((char*)b - 4) != 0)
        operator delete[](b);
    b = nb;
    e = ne;
    cap = nb + n;
}

// ================================================================ 0x00bde4a0
// SP::cCity's periodic "city hall rollover" tick.  __fastcall (ecx=this),
// returns the selected city (or 0).  Field views keep every offset named.

struct Key3  { int a, b, c; };
struct CivVec { void** b; void** e; };
struct CivView {                         // SP::cCivilization field view
    char   pad000[0xb0];
    CivVec cities;                       // +0xb0 (vector of city pointers)
    char   pad0b8[0x298 - 0xb8];
    int    field298;                     // +0x298
    char   pad29c[0x4b0 - 0x29c];
    float  field4b0;                     // +0x4b0
};
struct CityObj {                         // SP::city field view (generic)
    char   pad000[0x32c];
    float  posX;                         // +0x32c
    float  posY;                         // +0x330
    float  posZ;                         // +0x334
    char   pad338[0x540 - 0x338];
    int    specialty;                    // +0x540
    char   pad544[0xb1c - 0x544];
    int    fieldb1c;                     // +0xb1c
    int    fieldb20;                     // +0xb20
};
struct CityKind {                        // result of FUN_00ca71d0
    void*  owner;                        // +0x00
    char   pad04[0x10 - 0x4];
    int    kind;                         // +0x10
};
struct SpaceObj {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
};

struct RandomLCG { unsigned RandomUint32Uniform(unsigned n); };   // 0x00a68fb0
struct cTerrainEditor { void* GetCurrentTerrainSphere(); };       // 0x00f67d90

extern RandomLCG* gMathRandom;            // 0x01601760
extern char       gAppNameTag;            // 0x01654c05
extern float      kTickLimit;             // 0x013ec5b4
extern float      kEmpty3[3];             // 0x0168bd70
extern float      kC1, kC2;               // 0x0156e15c / 0x013ec4d0

bool   __cdecl FUN_00bef870(void* civ);                                  // 0x00bef870
bool   __cdecl Vector3_NotEqual(const float* a, const float* b);         // 0x0041dd30
int    __cdecl FUN_00c75420(void* sphere);                               // 0x00c75420
bool   __cdecl FUN_00c004c0(void* city, int which);                      // 0x00c004c0
CityKind* __cdecl FUN_00ca71d0(void* obj);                               // 0x00ca71d0
CivVec* __cdecl FUN_00bef6c0(void* civ);                                 // 0x00bef6c0
void*  __cdecl PlanetModel(void* pos);                                   // 0x00b3d350
int    __cdecl FUN_00b88590(void* planet);                               // 0x00b88590
float  __cdecl FUN_00b81470(void* planet, void* a, void* b);             // 0x00b81470
float  __cdecl FUN_00b7e4d0(void* planet);                               // 0x00b7e4d0
bool   __cdecl FUN_00bdb880(int which);                                  // 0x00bdb880
float  __cdecl FUN_00bf2170(void* civ, int specialty, int which);        // 0x00bf2170
int    __cdecl FUN_00bf2100(void* civ, int specialty);                   // 0x00bf2100
int    __cdecl FUN_00c9e6d0(int specialty, int which);                   // 0x00c9e6d0
int*   __cdecl FUN_00bf9770(void* civ, void* keyPos);                    // 0x00bf9770
int*   __cdecl FUN_00bddda0(void* city, int specialty, int which, Key3 key, int isTag); // 0x00bddda0
void*  __cdecl FUN_00cac000(void* obj, int a, int b);                    // 0x00cac000

// @ 0x00bde4a0 -- cCity tick: pick the city whose model the player is near
// and, when a rollover condition holds, hand it to SpaceTelemetry_Add.
int* cCity::FUN_00bde4a0()
{
    CivView* civ = (CivView*)mpCivilization;
    if (civ->field4b0 < kTickLimit)
        return (int*)civ;

    if (NounManager() && NounManager()->GetPlayerCivilization()) {
        if (!FUN_00bef870(NounManager()->GetPlayerCivilization()))
            return 0;
    }

    long long t = mTimer.GetElapsedTime();
    unsigned lo = (unsigned)(t & 0xffffffffu);
    unsigned hi = (unsigned)((unsigned long long)t >> 32);
    if (hi != 0 || lo > 90000) {
        mTimer.Restart();
        return (int*)this;
    }

    cTerrainEditor* te = (cTerrainEditor*)NounManager();
    int tkind = FUN_00c75420(te->GetCurrentTerrainSphere());
    if (tkind == 0) {
        if (gMathRandom->RandomUint32Uniform(100) != 0)
            return 0;
    } else if (tkind == 1) {
        if (gMathRandom->RandomUint32Uniform(10) != 0)
            return 0;
    }

    unsigned n;
    if (!FUN_00c004c0(this, 0) && !FUN_00c004c0(this, 1))
        n = 0x3c;
    else
        n = 0x14;
    if (gMathRandom->RandomUint32Uniform(n) != 0)
        return 0;

    // scan the civilization's city list for the viewer city
    bool bVar2 = false, bVar16 = false;
    CityKind* chosen = 0;
    void** pb = civ->cities.b;
    void** pe = civ->cities.e;
    for (void** it = pb; it != pe; ++it) {
        CityObj* c = (CityObj*)*it;
        if (!c)
            continue;
        if (c->fieldb20 != 0 && c->fieldb20 != 1)
            continue;
        CityKind* k = FUN_00ca71d0(c);
        if (k->kind != 7)
            continue;
        k = FUN_00ca71d0(c);
        if (k->owner != this)
            continue;
        if (c->fieldb1c == 0)
            bVar2 = true;
        else if (c->fieldb1c == 1)
            bVar16 = true;
    }
    if (bVar2) {
        if (bVar16)
            return (int*)chosen;
        if (!Vector3_NotEqual(&mPosX, kEmpty3))
            return 0;
    }
    bool flag2 = !bVar2;
    bool flag16 = bVar16;
    CityObj* local_30 = 0;
    float local_2c = 0.0f;
    if (flag2 && !flag16) {
        if (Vector3_NotEqual(&mPosX, kEmpty3) &&
            gMathRandom->RandomUint32Uniform(3) == 0)
            flag2 = false;
    }

    CivVec* list = FUN_00bef6c0(mpCivilization);
    int count = (int)((char*)list->e - (char*)list->b) / 4;
    for (int i = 0; i < count; ++i) {
        CityObj* c = (CityObj*)list->b[i];
        int spec = c->specialty;
        if (spec != 0 && spec != 1)
            continue;
        bool near;
        if (flag2) {
            SpaceObj* a = (SpaceObj*)this;
            SpaceObj* b = (SpaceObj*)c;
            void* pa = 0; void* pb2 = 0;
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)a)[0x58 / 4])(a, &pa);
            int ca = FUN_00b88590(PlanetModel(pa));
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)b)[0x58 / 4])(b, &pb2);
            int cb = FUN_00b88590(PlanetModel(pb2));
            near = (ca == cb);
        } else {
            near = !(c->posX == kEmpty3[0] && c->posY == kEmpty3[1] &&
                     c->posZ == kEmpty3[2]);
        }
        if (near) {
            void* outa = 0;
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)((SpaceObj*)this))[0x2c / 4])((SpaceObj*)this, &outa);
            void* outb = 0;
            ((void(__thiscall*)(SpaceObj*, void*))(*(void***)((SpaceObj*)c))[0x2c / 4])((SpaceObj*)c, &outb);
            float d = FUN_00b81470(PlanetModel(outb), outb, outa);
            float scale = FUN_00b7e4d0(PlanetModel(outa));
            float score = (2.0f - d / (scale * kC1)) * kC2;
            if (local_2c < score) {
                local_30 = c;
                local_2c = score;
            }
        }
    }

    if (local_30) {
        int rank = civ->field298;
        int which;
        if (rank >= 2 && !flag2) {
            which = 1;
        } else {
            if (rank < 1)
                return 0;
            if (!flag2)
                return 0;
            which = 0;
        }
        int spec = local_30->specialty;
        if (spec != 4 && spec != -1) {
            if (!FUN_00bdb880(which))
                return 0;
        }
        float fv = FUN_00bf2170(mpCivilization, spec, which);
        if (civ->field4b0 < fv)
            return 0;
        int add = FUN_00bf2100(mpCivilization, local_30->specialty);
        if (add <= 0)
            return 0;
        int spec2 = local_30->specialty;
        Key3 key;
        int* kp = FUN_00bf9770(mpCivilization, (void*)(long)FUN_00c9e6d0(spec2, which));
        key.a = kp[0]; key.b = kp[1]; key.c = kp[2];
        int isTag = (GetCurrentGameMode() == (int)(long)&gAppNameTag);
        int* city = FUN_00bddda0(local_30, spec2, which, key, isTag);
        if (!city)
            return 0;
        FUN_00cac000(city, 7, 0);
        civ->field4b0 -= (float)(int)local_2c;
    }
    return (int*)local_30;
}

