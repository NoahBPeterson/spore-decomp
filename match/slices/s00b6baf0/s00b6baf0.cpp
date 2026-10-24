// Slice s00b6baf0: tooltip/UI text-variable resolver. Given an object, switches on its variable id
// (obj->vt[0x38]) and builds a cBuildXHTMLDetokenizer::cVar from the matching string (species and
// nest names, empire/city names, a per-civilization string table keyed by id).
// Flags: /O2 /MD /Gy /TP (no /EHsc in this module).
#include "types.h"

void  EAFree(void* p);                                                    // 0x00F47380

extern const wchar_t gEmptyStr[];       // 0x013EC468 (L"")
extern void* gEmptyRep;                 // 0x01667BAC (shared empty string rep)

// ---------------------------------------------------------------------------
// text variable (wide-string inline buffer); 0x006743F0 takes the source text
// ---------------------------------------------------------------------------
struct cVar {
    uint32_t mData[0x58 / 4];
    cVar(const wchar_t* psz);            // 0x006743F0
};

// 12-byte eastl wide string with the shared empty rep (dtor frees a heap buffer)
struct Str12 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacityEnd;
    Str12() {
        mpBegin = (wchar_t*)&gEmptyRep;
        mpEnd = (wchar_t*)&gEmptyRep;
        mpCapacityEnd = (wchar_t*)((char*)&gEmptyRep + 2);
    }
    ~Str12() {
        if ((((int)((char*)mpCapacityEnd - (char*)mpBegin)) & -2) > 2 && mpBegin)
            EAFree(mpBegin);
    }
};

class cString {
public:
    cString();                                                                  // 0x006B5060
    cString(uint32_t tableID, int instanceID, const wchar_t* defaultText);      // 0x006B5770
    ~cString();                                                                 // 0x006B5240
    bool Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006B54B0
    const wchar_t* GetText();                                                   // 0x006B55C0
private:
    uint32_t mData[5];
};

// ---------------------------------------------------------------------------
// objects (only the vtable slots / fields used here)
// ---------------------------------------------------------------------------
struct NameSub {                         // sub-object with a vtable at +0x34 of "named" things
    virtual void n0();
    virtual const wchar_t* GetName();    // +0x04
};
struct Named {
    char pad[0x34];
    NameSub sub;
};

struct City;
struct VObj {                            // generic interface object
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual VObj* Cast(uint32_t id);     // +0x0c
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0A(); virtual void s0B();
    virtual void s0C(); virtual void s0D();
    virtual int GetVarID();              // +0x38
    virtual void s0F(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual int GetID();                 // +0x4c
    virtual void s14(); virtual void s15();
    virtual int GetIndex();              // +0x58
    virtual Named* GetNamed();           // +0x5c
    virtual void s18(); virtual void s19(); virtual void s1A(); virtual void s1B();
    virtual void s1C();
    virtual const wchar_t* GetText();    // +0x74
    virtual void s1E(); virtual void s1F(); virtual void s20();
    virtual void* Get84();               // +0x84 (a City* or a Named*, depending on the object)
    City* GetCityMember();               // 0x00BCE5C0
};

struct Civ {                             // civilization (vtable object with a name and a string table)
    virtual void c0(); virtual void c1(); virtual void c2();
    virtual struct TableOwner* Cast(uint32_t id);   // +0x0c
    char pad[0x38 - 4 - 12 + 0];
    const wchar_t* mpName;               // +0x3c
    const wchar_t** GetNamePtr();        // 0x005C65E0 (returns &mpName)
};
struct StarMgr {
    Civ* GetEmpireByID(int id);                 // 0x00BA9370
};
StarMgr* StarManager();                                         // 0x00B3D2A0

struct StrNode {
    char pad[0x14]; const wchar_t* value;       // key at +0x10, value at +0x14
};
struct StrIter { StrNode* node; StrIter() {} StrIter(const StrIter& o) { node = o.node; } };
struct StrMap {
    StrIter find(const uint32_t& key);                          // 0x00E5C780
};
struct TableOwner {
    char pad[8];
    StrMap map;
};

struct Species {
    char pad[0x51c]; const wchar_t* mpName;
};

struct Herd {
    char pad[0x84];
    uint8_t b84;
    char pad2[0x1f];
    Species* ma4;                         // +0xa4
};
struct Creature {
    char pad0[0x124];
    uint8_t b124;
    char pad2[3];
    Herd* m128;
    char pad3[0x714 - 0x12c];
    int m714;
};

struct SpeciesMgr {
    Species* GetAvatarProfile();             // 0x004DF420
};
SpeciesMgr* GetSetting9();                                      // 0x00401090

struct Terrain {
    bool Check(uint32_t id, uint32_t* out);     // 0x00C77380
};
struct NounMgr {
    Terrain* GetTerrain();                                      // 0x00F67D90
    Named* FindNamed(int id);                                   // 0x00B25F40
};
NounMgr* NounManager();                                         // 0x00B3D300

struct City {
    Civ* GetCivilization();                        // 0x00BD9BF0
};

struct Rec {
    bool Get(Str12* out);                           // 0x00F28B80
};
struct RecMgr {
    Rec* Find(VObj* obj);                        // 0x00F3E900
};
struct Globals {
    char pad[0x74]; RecMgr* m74;
};
extern Globals* gGlobals16c7aa4;                                // 0x016C7AA4

struct TableRow {
    char pad[0x68]; cString str;
};
TableRow* LookupRow(int idx);                                   // 0x00C9CEC0

struct Planet {
    int GetState();                              // 0x00C70E00
};
struct UniCtx;
int GetCurrentGameMode();                                       // 0x00B5B800
UniCtx* GetUniverseContext();                                   // 0x01021080
Planet* GetActivePlanet();                                      // 0x01021260
Herd* GetDesiredAvatarHerd(bool b);                             // 0x00D40B40

// helper casts / siblings (cdecl)
VObj*   CastB033(VObj* obj);                                    // 0x00B67740
VObj*   CastEE02(VObj* obj);                                    // 0x00B676E0
VObj*   CastE9CB(VObj* obj);                                    // 0x00B67720
Creature* CastB92(VObj* obj);                                   // 0x00B1FC00
Named*  CastEE9B(VObj* obj);                                    // 0x00AC86D0
Named*  CheckType(VObj* obj, uint32_t type);                    // 0x00AC80D0
cVar    ResolveRollover(VObj* obj);                             // 0x00B6B4C0
cVar    ResolveB6BA50(VObj* obj);                               // 0x00B6BA50
cVar    ResolveB6B810(VObj* obj);                               // 0x00B6B810
VObj*   CityOf(VObj* obj);                                      // 0x00BCE5C0

// @ 0x00B6BAF0
cVar ResolveVar(VObj* obj)
{
    if (GetCurrentGameMode() == 0x1654c10)
    {
        Rec* rec = gGlobals16c7aa4->m74->Find(obj);
        Str12 v;
        if (rec && rec->Get(&v))
            return cVar(v.mpBegin);
    }

    Named* x;
    int key;
    switch (obj->GetVarID())
    {
        case 0xd0036e08:
            return ResolveRollover(obj);

        case 0xb033b403:
        {
            VObj* p = CastB033(obj);
            int id = p->GetID();
            Civ* e = StarManager()->GetEmpireByID(id);
            if (e)
                return cVar(*e->GetNamePtr());
            cString s;
            if ((((Creature*)p)->m714 == 0xb && s.Load(0x2db6dad3, 0x6749c10, 0)) ||
                s.Load(0x2db6dad3, 0x678cddf, 0))
                return cVar(s.GetText());
            return cVar(gEmptyStr);
        }

        case 0xee9b2232:
            x = CastEE9B(obj);
            goto chk;

        case 0xee02c7:
            x = CastEE02(obj)->GetNamed();
            goto chk;

        case 0x116d858:
        {
            VObj* a = obj->Cast(0x116d858);
            TableRow* r = LookupRow(a->GetIndex());
            return cVar(r->str.GetText());
        }

        case 0x137e8e0:
        {
            int id = obj->GetID();
            Named* n = NounManager()->FindNamed(id);
            obj->Cast(0x137e8e0);
            if (n)
                return cVar(n->sub.GetName());
            goto dflt;
        }

        case 0x1a55e4d:
            key = 9;
            goto lookup;

        case 0x1b92b27:
        {
            Creature* c = CastB92(obj);
            if (!c) goto dflt;
            Herd* h = c->m128;
            if (!h) goto dflt;
            if (h->ma4 == GetSetting9()->GetAvatarProfile())
            {
                uint32_t k;
                if (NounManager()->GetTerrain()->Check(0x514a219, &k))
                {
                    if (GetDesiredAvatarHerd(false) == c->m128)
                        return cVar(cString(0xad56080c, 0x658f2d1, L"~New Nest").GetText());
                    if (c->m128->b84)
                        return cVar(cString(0xad56080c, 0x658f2d2, L"~Old Nest").GetText());
                }
                else if (c->m128->b84)
                    return cVar(cString(0xad56080c, 0x658f2d0, L"~Home Nest").GetText());
            }
            if (!(c->b124 & 1))
                return cVar(cString(0xad56080c, 0x658f2d3, L"~Unknown Species").GetText());
            return cVar(c->m128->ma4->mpName);
        }

        case 0x436f315:
            key = 0xa;
            goto lookup;

        case 0x4e3faaf:
            return ResolveB6BA50(obj);

        case 0x70704db:
        {
            VObj* p = CastE9CB(obj);
            if (!p) goto dflt;
            return cVar(p->GetText());
        }

        case 0xff10521:
            key = 7;
            goto lookup;

        case 0xecade42:
            key = 8;
            goto lookup;

        case 0x1007ae63:
            if (GetCurrentGameMode() == 0x1654c05)
            {
                VObj* a = obj->Cast(0x1007ae63);
                if (a)
                {
                    x = (Named*)a->Get84();
                    goto nochk;
                }
                key = 0xc;
            }
            else
                key = 6;
            goto lookup;

        case 0x4f176642:
            return ResolveB6B810(obj);

        case 0x4f396a66:
            x = CheckType(obj, 0x18c6d19);
            goto chk;

        default:
            goto dflt;
    }

chk:
    if (!x) goto dflt;
nochk:
    return cVar(x->sub.GetName());

lookup:
    {
        VObj* bld = obj->Cast(0xe9cb8ba);
        VObj* oth = obj->Cast(0x436f315);
        int mode = GetCurrentGameMode();
        Civ* civ = 0;
        City* city;
        switch (mode)
        {
            case 4:
            cityPath:
                if (bld)
                    city = (City*)bld->Get84();
                else if (oth)
                    city = oth->GetCityMember();
                else
                    break;
                civ = city->GetCivilization();
                break;
            case 5:
            {
                if (!GetUniverseContext() && GetActivePlanet()->GetState() == 4)
                    goto cityPath;
                int id = -1;
                if (bld)
                    id = bld->GetID();
                else if (oth)
                    id = oth->GetID();
                civ = StarManager()->GetEmpireByID(id);
                break;
            }
            default:
                __assume(0);
        }
        bool bNoCiv = (civ == 0);
        TableOwner* t = civ ? civ->Cast(0x5593a1a) : 0;
        const wchar_t* text;
        if (bNoCiv)
            text = gEmptyStr;
        else
        {
            uint32_t k = key;
            text = t->map.find(k).node->value;
        }
        return cVar(text);
    }

dflt:
    return cVar(gEmptyStr);
}

// ===========================================================================
// Simulator tooltip / health-bar UI records (0x00B6C180 - 0x00B6CA0E)
//
// 0x01687348 holds the global UI manager.  It maps a 32-bit record key to a
// UICtx (one per tooltip target), can look records up, and walks the live ones
// with Next(&key).  A record owns a cSPUILayout, the windows found in it, and
// the timer that drives the tooltip fade-out.
// ===========================================================================
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);

struct UICtx;
struct SimState;

// 3D point returned by the position helper (through a hidden return pointer)
struct Vec3 {
    float x, y, z;
};

// ---------------------------------------------------------------------------
// window / simulator object interface: only the vtable slots this unit calls
// are named, the rest keep the offsets.
// ---------------------------------------------------------------------------
struct SimView {
    virtual void w00(); virtual void Release(); virtual void w02();
    virtual SimView* Cast(uint32_t id);                          // +0x0c
    virtual void w04(); virtual void SetLayoutIndex(int index);  // +0x14
    virtual void w06(); virtual int GetIndex();                  // +0x1c
    virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual int GetVarID();   // +0x38
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18();
    virtual void w19(); virtual void w20(); virtual void w21(); virtual void w22();
    virtual void w23(); virtual void w24(); virtual void w25(); virtual void w26();
    virtual void w27(); virtual void w28(); virtual void w29(); virtual void w30();
    virtual void SetVisible(int a, int b);                       // +0x7c
    virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
    virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
    virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43();
    virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47();
    virtual void w48(); virtual void w49(); virtual void w50(); virtual void w51();
    virtual bool IsBlockedPrimary();                             // +0xd0
    virtual bool IsBlockedSecondary();                           // +0xd4
    virtual void w54(); virtual void w55(); virtual void w56(); virtual void w57();
    virtual void w58(); virtual void w59();
    virtual SimView* FindWindow(int id, int flags);              // +0xf0
    virtual void w61(); virtual void w62(); virtual void w63(); virtual void w64();
    virtual void w65();
    virtual void OnLayoutChange(void* pData);                    // +0x108
    virtual void w67();

    char mPad00[0xb58 - 4];
    uint32_t mFlags;                                             // +0xb58

    bool CheckActive();                                          // 0x00C0B770
    SimState* GetState();                                        // 0x00C0C1A0
};

struct SimState {
    char mPad00[0x32c];
    int mCount;                                                  // +0x32c
};

// eastl 3-pointer vector (the only operations this unit performs on it)
struct UIPtrVector {
    SimView** mpBegin;                                           // +0x00
    SimView** mpEnd;                                             // +0x04
    SimView** mpCapacityEnd;                                     // +0x08

    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }

    void push_back(SimView* const& value)
    {
        if (mpEnd < mpCapacityEnd)
        {
            SimView** pSlot = mpEnd++;
            if (pSlot)
                *pSlot = value;
        }
        else
            DoInsertValue(mpEnd, value);
    }

    void erase(SimView** first, SimView** last)
    {
        memcpy(first, last, (unsigned int)((char*)mpEnd - (char*)last));
        mpEnd -= last - first;
    }

    void DoInsertValue(SimView** pPosition, SimView* const& value);   // 0x00CD0550
};

struct RefObj {
    virtual void r00();
    virtual void Release();                                      // +0x04
    virtual void Destroy();                                      // +0x08
};

struct cSPUILayoutBase {
    virtual void l00();
    virtual void AddRef();                                       // +0x04
    virtual void Release();                                      // +0x08
};

struct cSPUILayout : cSPUILayoutBase {
    cSPUILayout* ctor();                                                          // 0x00810000
    bool Init(const wchar_t* pName, int scale, bool bFlag, unsigned int key);     // 0x00812160
    SimView* FindWindowByID(int windowID, int flags);                             // 0x008105B0
    void Shutdown(unsigned int flags);                                            // 0x00811AD0
};

// cTribeModeStrategy: the +0x04 sub-object is what the tooltip layout wants
struct TribeStrategyData {
    int mValue;                                                  // +0x00
};
struct TribeModeStrategy {
    char mPad00[4];
    TribeStrategyData mData;                                     // +0x04
};
TribeModeStrategy* TribeModeStrategyInstance();                  // 0x00CD40B0

// ---------------------------------------------------------------------------
// one tooltip/health-bar UI record
// ---------------------------------------------------------------------------
struct UICtx {
    int mID;                                                     // +0x000
    VObj* mObj;                                                  // +0x004
    bool mVisible;                                               // +0x008
    char mPad09[3];
    float mX;                                                    // +0x00c
    float mY;                                                    // +0x010
    char mPad14[0x3c];
    cSPUILayout* mSubLayout;                                     // +0x050
    char mPad54[0x24];
    SimView* mMainWindow;                                        // +0x078
    char mPad7C[0x24];
    SimView* mStateWindow;                                       // +0x0a0
    VObj* mOwnerObj;                                             // +0x0a4
    char mPadA8[4];
    SimView* mSubWindow;                                         // +0x0ac
    char mPadB0[8];
    cSPUILayout* mLayout;                                        // +0x0b8
    SimView* mWindow;                                            // +0x0bc
    UIPtrVector mWindows;                                        // +0x0c0
    char mPadCC[0x4c];
    int mIndex;                                                  // +0x118
    float mTimer;                                                // +0x11c
    RefObj* mRef;                                                // +0x120

    void ClearWindows() { mWindows.erase(mWindows.mpBegin, mWindows.mpEnd); }

    // register-argument helpers of the original TU (record arrives in esi)
    bool UpdateSimulatorAnim(float value, float elapsed);        // 0x00B69010
    void ShowSimulatorText(float* pOffset, int a2, const void* pText,
                           Vec3* pPos, int a4, int a5);          // 0x00B6A720
};

// ---------------------------------------------------------------------------
// the UI manager at 0x01687348
// ---------------------------------------------------------------------------
struct UIMgr {
    UICtx* Find(int key);                                        // 0x00B721D0
    UICtx* GetSlot(int key);                                     // 0x00B72210
    UICtx* Next(int* pKey);                                      // 0x00B72230
    void   Remove(int key);                                      // 0x00B72260
    int    CurrentKey();                                         // 0x00E31100
};
extern UIMgr* gUIMgr;                                            // 0x01687348

void* SporeAlloc(int size, const wchar_t* pName, int a, int b, int c, int d);   // 0x00F473A0
int   FindOrCreateKey(int key);                                                  // 0x00B687D0
void  AnchorWindowToScreen(float* pRect, SimView* pWindow, int flags, int arg);  // 0x008070D0
Vec3  GetSimulatorPos(VObj* pObj);                                               // 0x00B677E0
float GetSimulatorFloat(VObj* pObj);                                             // 0x00B685E0
int   GetSimulatorInt1(VObj* pObj);                                              // 0x00B682A0
int   GetSimulatorInt2(VObj* pObj);                                              // 0x00B67B90

static void CleanupUICtx(int key);                               // 0x00B6C180 (key in eax)
static void RemoveUISlot(int key);                               // 0x00B686A0 (key in eax)
static void SetCtxWindow(SimView* pObj, int index);              // 0x00B69460
static UICtx* ShowHealthBar(int key);                            // 0x00B6C2D0 (key in eax)

// 0x00B686A0: shut down and release the layout a record keeps at +0x50
__declspec(noinline) static void RemoveUISlot(int key)
{
    UICtx* pCtx = gUIMgr->Find(key);
    if (!pCtx || !pCtx->mSubLayout)
        return;

    if (GetCurrentGameMode() == 0x1654c02 && pCtx->mObj->GetVarID() == 0xee02c7)
    {
        TribeModeStrategy* pStrategy = TribeModeStrategyInstance();
        pCtx->mSubWindow->OnLayoutChange(pStrategy ? &pStrategy->mData : 0);
    }

    pCtx->mSubLayout->Shutdown(1);

    cSPUILayout* pLayout = pCtx->mSubLayout;
    if (pLayout)
    {
        pCtx->mSubLayout = 0;
        pLayout->Release();
    }
}

// 0x00B69460: show/hide the window the object casts to, and select its entry
static void SetCtxWindow(SimView* pObj, int index)
{
    SimView* pView = pObj ? pObj->Cast(0xeeee8218) : 0;

    if (index == -1)
    {
        pView->SetVisible(1, 0);
        return;
    }

    pView->SetVisible(1, 1);
    pObj->SetLayoutIndex(index);
}

// @ 0x00B6C180
__declspec(noinline) static void CleanupUICtx(int key)
{
    UICtx* pCtx = gUIMgr->Find(key);
    if (!pCtx)
        return;
    if (!pCtx->mLayout)
        return;

    pCtx->mLayout->Shutdown(1);

    cSPUILayout* pLayout = pCtx->mLayout;
    if (pLayout)
    {
        pCtx->mLayout = 0;
        pLayout->Release();
    }

    pCtx->ClearWindows();
}

// releases a ref-counted slot and clears it (inlined at the call site in the original)
static void ReleaseRefSlot(RefObj*& pSlot)
{
    RefObj* pRef = pSlot;
    if (pRef)
    {
        pSlot = 0;
        pRef->Release();
    }
}

// @ 0x00B6C200
__declspec(noinline) void RemoveUICtx(int key)
{
    UICtx* pCtx = gUIMgr->Find(key);
    if (!pCtx)
        return;

    RemoveUISlot(key);
    CleanupUICtx(key);

    UICtx* pRefCtx = gUIMgr->Find(key);
    if (pRefCtx && pRefCtx->mRef)
        ReleaseRefSlot(pRefCtx->mRef);

    if (pCtx->mObj)
    {
        VObj* pObj = pCtx->mObj;
        pCtx->mObj = 0;
        pObj->s01();
    }

    gUIMgr->Remove(key);
}

// @ 0x00B6C280
void RefreshUITooltips()
{
    if (!gUIMgr)
        return;

    int key = gUIMgr->CurrentKey();
    UICtx* pCtx = gUIMgr->Next(&key);
    while (pCtx)
    {
        RemoveUICtx(pCtx->mID);
        pCtx = gUIMgr->Next(&key);
    }
}

// @ 0x00B6C2D0
__declspec(noinline) static UICtx* ShowHealthBar(int key)
{
    int slotKey = FindOrCreateKey(key);
    UICtx* pCtx = gUIMgr->GetSlot(slotKey);

    if (!pCtx->mLayout)
    {
        void* pMem = SporeAlloc(0x18, L"Simulator/HealthBar", 0, 0, 0, 0);
        cSPUILayout* pLayout = pMem ? ((cSPUILayout*)pMem)->ctor() : 0;
        cSPUILayout* pOld = pCtx->mLayout;

        if (pLayout != pOld)
        {
            if (pLayout)
                pLayout->AddRef();
            pCtx->mLayout = pLayout;
            if (pOld)
                pOld->Release();
        }

        pCtx->mLayout->Init(L"GoalIcons", 0x40464100, true, 0xe9f70df9);

        pCtx->mWindow = pCtx->mLayout->FindWindowByID(0x75de460, 1);

        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x75f3ea8, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x75de461, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37790, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37793, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37794, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37799, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c3779d, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a1, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a5, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a6, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a9, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377ad, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377b1, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377b6, 0));

        if (!pCtx->mWindow)
            CleanupUICtx(slotKey);
    }

    return pCtx;
}

// stand-in caller: gives ShowHealthBar the register argument convention the
// original TU used (the record key arrives in eax).
UICtx* ShowHealthBarFromKey(int key)
{
    return ShowHealthBar(key);
}

// @ 0x00B6C710
void UpdateUIContexts(float dt)
{
    int key = gUIMgr->CurrentKey();
    UICtx* pCtx = gUIMgr->Next(&key);
    if (!pCtx)
        return;

    do
    {
        if (pCtx->mLayout)
        {
            float timeLeft = pCtx->mTimer - dt;
            pCtx->mTimer = timeLeft;

            if (timeLeft >= 0)
            {
                for (unsigned int i = 0; i < pCtx->mWindows.size(); ++i)
                {
                    SimView* pChild = pCtx->mWindows.mpBegin[i];
                    if (pChild)
                    {
                        if (pChild->GetIndex() == pCtx->mIndex)
                            pChild->SetVisible(1, 1);
                        else
                            pChild->SetVisible(1, 0);
                    }
                }

                pCtx->mWindow->SetVisible(1, pCtx->mVisible);

                if (pCtx->mVisible)
                {
                    float x = pCtx->mX;
                    float y = pCtx->mY;
                    float rect[4];
                    rect[0] = x - 0.5f;
                    rect[1] = y - 0.5f;
                    rect[2] = x + 0.5f;
                    rect[3] = y + 0.5f;
                    AnchorWindowToScreen(rect, pCtx->mWindow, 0x102, 0);
                }
            }
            else
                CleanupUICtx(pCtx->mID);
        }

        pCtx = gUIMgr->Next(&key);
    } while (pCtx);
}

// @ 0x00B6C870
void UpdateSimulatorUI(UICtx* pCtx, int a2, float* pOffset, int a4, float a5)
{
    int mode = GetCurrentGameMode();

    if (mode == 0x1654c01)
    {
        pCtx->mMainWindow->SetVisible(1, a4);

        VObj* pSimObj = pCtx->mObj;
        SimView* pSim = pSimObj ? (SimView*)pSimObj->Cast(0xd0036e08) : 0;

        if (pSim->CheckActive() &&
            (pSim->mFlags & 2) == 0 &&
            (pSim->mFlags & 1) != 0 &&
            !pSim->IsBlockedPrimary() &&
            !pSim->IsBlockedSecondary())
        {
            pCtx->mStateWindow->SetVisible(1, 1);

            SimState* pState = pSim->GetState();
            int index = pState->mCount - 1;
            if (index < 0)
                index = 0;

            SetCtxWindow((SimView*)pCtx->mOwnerObj, index);
        }
        else
            pCtx->mStateWindow->SetVisible(1, 0);
    }
    else if (mode == 0x1654c10)
        pCtx->mMainWindow->SetVisible(1, 0);

    VObj* pObj = pCtx->mObj;
    cVar text = ResolveVar(pObj);
    int textID = (int)text.mData[0];
    Vec3 pos = GetSimulatorPos(pObj);
    float value = GetSimulatorFloat(pObj);
    int i1 = GetSimulatorInt1(pObj);
    int i2 = GetSimulatorInt2(pObj);

    if (pCtx->UpdateSimulatorAnim(value, a5))
        pCtx->ShowSimulatorText(pOffset, a2, (const void*)textID, &pos, i1, i2);
    else
        RemoveUISlot(pCtx->mID);
}
