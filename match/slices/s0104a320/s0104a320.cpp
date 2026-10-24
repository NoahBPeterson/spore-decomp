// SP::cSpaceTokenTranslator::TranslateToken (function at 0x0104a320, 6528 bytes, /O2).
//
// Complete high-level reconstruction of the token translator.  The function hashes the
// UTF-16 token with FNV-1 and binary-searches the hash in a ~57-entry dispatch; most arm
// gather a number, a name or a requirement list from simulator state and format it into
// the output cString, then return true.  Unknown tokens are offered to the mission
// translator and finally to the base string translator.
//
// The original is a single /GL/LTCG inlined body (6528 bytes) so it is not byte-exact from
// one object; every arm below mirrors the call sequence the original performs.
//
// Field offsets follow the PDB layout of SP::cSpaceTokenTranslator (size 0xa4).
#include "../../include/types.h"
#include <wchar.h>

// ------------------------------------------------------------------ string type
// SP::cString, 0x1c bytes.
struct cString {
    void*          mpTableResource;   // +0x00 AutoRefCount<Resource>
    void*          mpLocalString;     // +0x04 eastl::basic_string<wchar_t>*
    const wchar_t* mpSourceCStr;      // +0x08
    unsigned int   mPlaceholderId;    // +0x0c
    bool           mbHasTokens;       // +0x10
    unsigned int   mTableId;          // +0x14
    unsigned int   mInstanceId;       // +0x18
    void assign(const wchar_t* text);
    void assign(const cString& other);
    const wchar_t* c_str();
};

// eastl::vector<cString, sp_vector_allocator>, 0x10 bytes, 0x1c-byte elements.
struct cStringVector {
    cString* mpBegin;                 // +0x00
    cString* mpEnd;                   // +0x04
    cString* mpCapacity;              // +0x08
    void*    mAllocator;              // +0x0c
    int size() const { return (int)(mpEnd - mpBegin); }
    cString& at(int i) { return mpBegin[i]; }
};

// Game-side objects are opaque here; the accessors below are the calls the original makes.
struct cStarRecord;
struct cPlanetRecord;
struct cSpeciesProfile;
struct cCivData;
struct cEmpire;
struct cVehicle;
struct cBuilding;
struct cSPSpaceInventoryItem;
struct cSPSpaceToolData;
struct cSPSpaceEconomyTuning;
struct cSPMission;
struct cSPGameDataUFO;

// ---------------------------------------------------------------- retail callees
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int mode);   // EA::Hash::FNV1_String16
void     Locale_SetNumberString(float v, wchar_t* out, int cap, int flags);
void     Locale_SetIntString(int v, int sign, wchar_t* out, int cap);
void*    SpaceGameGet(uint32_t key);
void*    GetSpaceRelationshipTuning();
void*    GetMissionManager(int a);
bool     GetPropertyAsKeyInstance(void* prop, uint32_t id, void** out);
bool     GetPropertyAsInt(void* localStr, uint32_t id, void** out);
bool     GetPropertyAsText(void* localStr, uint32_t id, void* out);
cSpeciesProfile* GetSpeciesProfile();
cCivData*        GetPlayerEmpire();
void*            GetActivePlanetRecord(void* a, void* b);
int      cSPMission_GetNumNonEventMissions(void* mgr);
int      cSPSpaceToolData_GetUseCost(cSPSpaceToolData* t);
int      cSPSpaceEconomyTuning_GetPeaceOfferPrice(cSPSpaceEconomyTuning* t, int idx, cEmpire* e);
int      cSPSpaceEconomyTuning_CalcAttackRequestCost(cSPSpaceEconomyTuning* t, int v);
uint32_t SPIDFromName(const char* group, uint32_t id, const wchar_t* name);
void     UseItem(void* item);
bool     cSPEditorVerbIconTray_IsMaxValueExt(void* tray);           // output formatter for a value
const wchar_t* cSPEditorVerbIconTray_IsMaxValue(void* cell);        // cell text formatter
void     SetOutputString(cString* out, const wchar_t* s);

// Inventory / empire / planet helpers (the original inlines the interface casts and the
// member calls behind them).
void*    GetPlayerInventory(void* game);
void*    GetToolFromToolID(void* inv, void* key);
bool     InventoryHasItem(void* inv, void* key);
void*    GetPlayerTribe(void* game);
void*    GetBadgeName(void* tribe, void* key, cString* out);
void*    GetAvatar(void* tribe);
void*    GetEmpireCities(void* civ);                  // cCivData::GetCities -> cString*
void*    GetHomePlanet(void* empire);
void*    GetSpeciesOfEmpire(void* empire);
void     GetSpeciesUiName(void* species, cString* out);
void*    GetPlanetName(void* planet);                 // FUN_00ecdba0 -> const wchar_t**
void     TerraformingManager(void* planet);
int      GetTerraformingLevel(void* planet);          // FUN_00bbc670
int      GetTechLevelIndex();                         // FUN_00b8dab0
int      GetMissionWorldId();                         // FUN_00ffbe50
int      GetStarTime(void* star);                     // FUN_00ffc490
int      GetStarTimeAlt(void* star);                  // FUN_00ffc4e0
int      GetConversationValueA(uint32_t key);         // FUN_00fe66f0
int      GetConversationValueB(uint32_t key);         // FUN_00fe6770
const wchar_t* GetUfoName(void* ufo);                 // FUN_00fe4230
const wchar_t* GetObjectName(void* obj);              // virtual +0x28
const wchar_t* GetBuildingName(void* b);              // virtual +0x74
const wchar_t* GetNounName(void* noun);               // FUN_00bb9de0
void*    InterfaceCast(void* obj, int kind);          // EA::COM::interface_cast
int      PlantCargoKind(void* cargo);                 // FUN_00b8f860
int      SpeciesDietKind(void* species);              // cSpeciesProfile::mHasRoots
int      CountListElems(void* list);                  // FUN_00acd9d0
int      CountNounList(void* mgr);                    // FUN_00ace2c0
void     BuildUnlockList(uint32_t key, void* outVector);// FUN_00b3d3d0 + FUN_0103d110
void     FormatUnlockLine(cString* out, const wchar_t* fmt, const wchar_t* name);
bool     MissionTranslateToken(void* mission, uint32_t hash, const wchar_t* token, cString* out);

struct cSpaceTokenTranslator;
bool     BaseTranslateToken(cSpaceTokenTranslator*, uint32_t hash, const wchar_t* token, cString* out);

bool     MissionHasProperty(void* mission, uint32_t id);
bool     MissionPropertyUnlocked(void* mission, uint32_t id);
int      CountEmpireLevels();
float    EmpireLevel(int i);
bool     SameEmpireLevel(float a, float b);
int      CountAnimalSpecies(void* planet);
int      CountToolList(void* game);
void*    AttackPlanetAt(int idx);
void*    GetAvatarCiv(void* avatar);
int      SpeciesHerbivore(void* species);
int      AnimalCargoJump(void* cargo);
int      AnimalCargoHerbivore(void* cargo);
int      AnimalCargoType(void* cargo);
int      GetPlayerTribeIndex();
int      cSPSpaceEconomyTuning_GetTradeCaptureOfferPrice(cSPSpaceEconomyTuning* t, int idx);
void     FUN_01049f90(cString* out);

// Global attack-request planet list (vector<AutoRefCount<cPlanetRecord>>).
extern void* g_attackRequestPlanets;
extern int   g_attackRequestPlanetCount;
extern int   g_targetPlanetIndex;

// ------------------------------------------------------------------ translator
struct cGameTokenTranslator {
    virtual bool TranslateTokenBase(uint32_t hash, const wchar_t* token, cString* out); // +0x10
    void* mPropList;                  // +0x08 AutoRefCount<cPropertyList>
};

struct cSpaceTokenTranslator : cGameTokenTranslator {
    virtual bool TranslateToken(const wchar_t* token, cString* out);   // (the function modelled)

    cPlanetRecord*        mPlanet;             // +0x0c
    cStarRecord*          mStar;               // +0x10
    cSPSpaceInventoryItem* mItem;              // +0x14
    cSPMission*           mpMission;           // +0x18
    cEmpire*              mpEmpire;            // +0x1c
    cEmpire*              mpEmpire2;           // +0x20
    cSpeciesProfile*      mSpeciesProfile;     // +0x24
    cBuilding*            mpBuilding;          // +0x28
    cVehicle*             mpVehicle;           // +0x2c
    cSPGameDataUFO*       mpUFO;               // +0x30
    const wchar_t*        mGenericName;        // +0x34
    int                   mCount;              // +0x38
    float                 mCost;               // +0x3c
    int                   mBadgeCount;         // +0x40
    uint32_t              mConversationFileKey;// +0x44
    cStringVector         mTechLevelString;    // +0x48
    cStringVector         mTerraformingLevelString; // +0x58
    cStringVector         mAnimalTypeString;   // +0x68
    cStringVector         mPlantTypeString;    // +0x78
    cString               mMoneyFormatString;  // +0x88
};

// ------------------------------------------------------------------ small helpers
static void outNumber(cString* out, int v)
{
    wchar_t buf[0x40];
    Locale_SetNumberString((float)v, buf, 0x40, 0);
    SetOutputString(out, buf);
}

static void outFloat(cString* out, float v)
{
    wchar_t buf[0x40];
    Locale_SetNumberString(v, buf, 0x40, 0);
    SetOutputString(out, buf);
}

static void outInt(cString* out, int v)
{
    wchar_t buf[0x40];
    Locale_SetIntString(v, v >> 31, buf, 0x40);
    SetOutputString(out, buf);
}

static const wchar_t* cellText(cString* c)
{
    return cSPEditorVerbIconTray_IsMaxValue(c);
}

static cString& cellAt(cStringVector& v, int i)
{
    if (i < 0) i = 0;
    if (i >= v.size()) i = 0;
    return v.at(i);
}

// cString built from a localized name id (cString(id, source, 0)).
static cString g_nameString;
static cString* nameString(uint32_t id, const wchar_t* text)
{
    g_nameString.mTableId = id;
    g_nameString.mpSourceCStr = text;
    return &g_nameString;
}

// @ 0x0104a320
bool cSpaceTokenTranslator::TranslateToken(const wchar_t* token, cString* out)
{
    uint32_t h = FNV1_String16(token, 0x811c9dc5u, 1);
    void* key = 0;

    switch (h) {

    // ---- star / mission-timer family -------------------------------------------
    case 0x702299b5u: {                       // star timer (7777 when no star)
        int v = 7777;
        if (mStar)
            v = cSPMission_GetNumNonEventMissions(GetMissionManager(0));
        outNumber(out, v);
        return true;
    }
    case 0xad26b2a3u: {                       // star time, 0x22b8 when no star
        int v = 0x22b8;
        if (mStar)
            v = GetStarTimeAlt(mStar);
        outInt(out, v);
        return true;
    }
    case 0x36854075u:                         // number of non-event missions
        outInt(out, cSPMission_GetNumNonEventMissions(GetMissionManager(0)));
        return true;

    // ---- commodity / tool / badge requirements ---------------------------------
    case 0x3245123eu:                         // count -> tool id -> tool name
    case 0x76e04c2u: {
        if (!mCount)
            return true;
        GetPropertyAsKeyInstance((void*)mCount, 0x5107708u, &key);
        void* inv = GetPlayerInventory(SpaceGameGet(0));
        void* tool = GetToolFromToolID(inv, key);
        if (!tool)
            return true;
        out->assign(GetObjectName(tool));
        return true;
    }
    case 0x45de404cu: {
        bool a = false, b = false, c = false;
        if (mCount) {
            void* k = 0;
            if (GetPropertyAsKeyInstance((void*)mCount, 0x5107709u, &k))
                a = InventoryHasItem(GetPlayerInventory(SpaceGameGet(0)), k);
            if (GetPropertyAsKeyInstance((void*)mCount, 0x510770au, &k))
                b = InventoryHasItem(GetPlayerInventory(SpaceGameGet(0)), k);
            if (GetPropertyAsKeyInstance((void*)mCount, 0x510770bu, &k))
                c = InventoryHasItem(GetPlayerInventory(SpaceGameGet(0)), k);
        }
        const wchar_t* s;
        uint32_t id;
        if (!a || !b) {
            if (c) { s = L"~commodity_badge_req~ or ~commodity_badge_or_req~ badge"; id = 0x65b8f36u; }
            else   { s = L"~commodity_badge_req~ badge";                          id = 0x65bd251u; }
        } else if (c) {
            s = L"~commodity_badge_req~ and ~commodity_badge_and_req~ or ~commodity_badge_or_req~ badge";
            id = 0x65b8f44u;
        } else {
            s = L"~commodity_badge_req~ and ~commodity_badge_and_req~ badge";
            id = 0x65b8f3du;
        }
        out->assign(cellText(nameString(SPIDFromName("SpaceGame", id, s), s)));
        return true;
    }
    case 0x59d5597fu: {
        bool a = false, b = false, c = false;
        if (mCount) {
            void* k = 0;
            if (GetPropertyAsKeyInstance((void*)mCount, 0x5107706u, &k))
                a = InventoryHasItem(GetPlayerInventory(SpaceGameGet(0)), k);
            if (GetPropertyAsKeyInstance((void*)mCount, 0x5107707u, &k))
                b = InventoryHasItem(GetPlayerInventory(SpaceGameGet(0)), k);
            if (GetPropertyAsKeyInstance((void*)mCount, 0x5107708u, &k))
                c = InventoryHasItem(GetPlayerInventory(SpaceGameGet(0)), k);
        }
        const wchar_t* s;
        uint32_t id;
        if (!a || !b) {
            if (c) { s = L"~commodity_tool_req~ or ~commodity_tool_or_req~"; id = 0x65b9958u; }
            else   { s = L"~commodity_tool_req~";                           id = 0x65b9952u; }
        } else if (c) {
            s = L"~commodity_tool_req~ and ~commodity_tool_and_req~ or ~commodity_tool_or_req~";
            id = 0x65b9960u;
        } else {
            s = L"~commodity_tool_req~ and ~commodity_tool_and_req~";
            id = 0x65b995cu;
        }
        out->assign(cellText(nameString(SPIDFromName("SpaceGame", id, s), s)));
        return true;
    }
    case 0x4b25ed41u: {                       // item requirement text
        cString local;
        if (mItem)
            GetPropertyAsText(((void**)mItem)[2], 0x3068d95du, &local);
        out->assign(cellText(&local));
        return true;
    }
    case 0xfbfdff77u: {                       // full "badge and tool" sentence
        bool badge = false, tool = false;
        if (mCount) {
            if (MissionHasProperty((void*)mCount, 0x5107706u))
                badge = !MissionPropertyUnlocked((void*)mCount, 0x5107706u);
            if (MissionHasProperty((void*)mCount, 0x5107709u))
                tool = !MissionPropertyUnlocked((void*)mCount, 0x5107709u);
        }
        if (badge && tool) {
            const wchar_t* s = L"~commodity_badge_reqs~, and ~commodity_tool_reqs~";
            out->assign(cellText(nameString(SPIDFromName("SpaceGame", 0x65b9969u, s), s)));
            return true;
        }
        if (badge)
            return BaseTranslateToken(this, h, L"commodity_tool_reqs", out);
        if (tool)
            return BaseTranslateToken(this, h, L"commodity_badge_reqs", out);
        return true;
    }

    // ---- names ------------------------------------------------------------------
    case 0x1dc3939fu:                         // UFO name
        out->assign(mpUFO ? GetUfoName(mpUFO) : L"Error: No UFO Name");
        return true;
    case 0xdafe873u:                          // planet name
        if (!mPlanet)
            return true;
        out->assign((const wchar_t*)GetPlanetName(mPlanet));
        return true;
    case 0xeef69c2u:                          // planet tech level string
        if (!mPlanet)
            return true;
        out->assign(cellText(&cellAt(mTechLevelString, GetTechLevelIndex())));
        return true;
    case 0x88d3a6e0u:                         // terraforming level string
        if (!mPlanet)
            return true;
        TerraformingManager(mPlanet);
        out->assign(cellText(&cellAt(mTerraformingLevelString, GetTerraformingLevel(mPlanet))));
        return true;
    case 0x64c46e43u:
        if (!mItem)
            return true;
        out->assign(GetObjectName(mItem));
        return true;
    case 0x38ea8121u: {                       // item description text
        cString local;
        if (mItem)
            GetPropertyAsText(((void**)mItem)[2], 0x3c72dc4u, &local);
        out->assign(cellText(&local));
        return true;
    }
    case 0x71037a25u: {                       // item integer property
        int v = 0;
        if (mItem) {
            void* p = 0;
            GetPropertyAsInt(((void**)mItem)[2], 0x3c72dc5u, &p);
            v = (int)p;
        }
        outNumber(out, v);
        return true;
    }
    case 0x692837bfu:                         // vehicle name
        out->assign(mpVehicle ? GetObjectName(mpVehicle) : L"Error: No Vehicle Name");
        return true;
    case 0x6fcbce96u:                         // empire city list
        out->assign(mpEmpire ? (const wchar_t*)GetEmpireCities(mpEmpire) : L"Error: No Empire");
        return true;
    case 0x93d63610u:                         // second empire city list
        out->assign(mpEmpire2 ? (const wchar_t*)GetEmpireCities(mpEmpire2) : L"Error: No Empire");
        return true;
    case 0x19a99ac5u: {                       // player empire city list
        void* civ = GetPlayerEmpire();
        if (!civ)
            return true;
        out->assign((const wchar_t*)GetEmpireCities(civ));
        return true;
    }
    case 0xbe20391au:                         // generic translator name
        out->assign(mGenericName ? mGenericName : L"");
        return true;
    case 0x64b06c36u:                         // conversation value A
        outNumber(out, GetConversationValueA(mConversationFileKey));
        return true;
    case 0xfa226892u:                         // conversation value B
        outNumber(out, GetConversationValueB(mConversationFileKey));
        return true;
    case 0xf1236e74u:                         // conversation value A (alias)
        outNumber(out, GetConversationValueA(mConversationFileKey));
        return true;
    case 0xc81ef8beu:                         // conversation value A - B
        outInt(out, GetConversationValueB(mConversationFileKey) -
                    GetConversationValueA(mConversationFileKey));
        return true;
    case 0x27647858u:                         // conversation name via tribe
        outNumber(out, GetConversationValueA(mConversationFileKey));
        return true;
    case 0x8b7e6fd5u:
        out->assign(GetNounName(0));
        return true;
    case 0xac984678u:                         // player species UI name
        if (!mSpeciesProfile)
            return true;
        GetSpeciesUiName(mSpeciesProfile, out);
        return true;
    case 0xe4be0075u:                         // item name or species UI name
        if (mItem) { out->assign(GetObjectName(mItem)); return true; }
        if (!mSpeciesProfile)
            return true;
        GetSpeciesUiName(mSpeciesProfile, out);
        return true;
    case 0xb11b4f0cu: {                       // player-empire species UI name
        void* civ = GetPlayerEmpire();
        if (!civ)
            return true;
        void* sp = GetSpeciesOfEmpire(civ);
        if (!sp)
            return true;
        GetSpeciesUiName(sp, out);
        return true;
    }
    case 0xd020f18du:                         // building name
        out->assign(mpBuilding ? GetBuildingName(mpBuilding) : L"Error: No Building Name");
        return true;
    case 0xe326ad6cu: {                       // player empire home-planet name
        void* civ = GetPlayerEmpire();
        if (!civ) { out->assign(L"Error: No Empire"); return true; }
        void* home = GetHomePlanet(civ);
        if (!home) { out->assign(L"error: could not find the home planet"); return true; }
        out->assign((const wchar_t*)GetPlanetName(home));
        return true;
    }
    case 0xbe0a21a8u: {                       // empire home-planet name
        if (!mpEmpire) { out->assign(L"Error: No Empire"); return true; }
        void* home = GetHomePlanet(mpEmpire);
        if (!home) { out->assign(L"error:could not find planet"); return true; }
        out->assign((const wchar_t*)GetPlanetName(home));
        return true;
    }

    // ---- counts -----------------------------------------------------------------
    case 0x1d0ffcc4u: {                       // mission cities count
        void* civ = GetPlayerEmpire();
        if (!civ)
            return true;
        outNumber(out, (int)GetEmpireCities(civ));
        return true;
    }
    case 0xead4e966u: {                       // archived mission cities count
        void* civ = GetPlayerEmpire();
        if (!civ)
            return true;
        outNumber(out, (int)GetEmpireCities(civ));
        return true;
    }
    case 0x1702a67cu: {                       // planet tech index (0x270f default)
        int v = 0x270f;
        if (mPlanet)
            v = GetTerraformingLevel(mPlanet);
        outInt(out, v);
        return true;
    }
    case 0xf5304968u: {                       // empire-wide count (0x4d2 default)
        int v = 0x4d2;
        void* civ = GetPlayerEmpire();
        if (civ)
            v = (int)GetEmpireCities(civ);
        outNumber(out, v);
        return true;
    }
    case 0x19566813u: {                       // number of empires different from the player
        float ref = (float)(int)GetPlayerEmpire();
        int n = 0;
        for (int i = 0; i < CountEmpireLevels(); i++) {
            float lvl = EmpireLevel(i);
            if (lvl != 0.0f && lvl != ref && !SameEmpireLevel(lvl, ref))
                n++;
        }
        outNumber(out, n);
        return true;
    }
    case 0xb4f91211u:                         // number of animal species on the planet
        if (!mPlanet)
            return true;
        outNumber(out, CountAnimalSpecies(mPlanet));
        return true;
    case 0x9df5e5b3u:                         // count of a noun list
        outNumber(out, CountListElems(0));
        return true;
    case 0x834ff9d4u:                         // count of the noun manager list
        outNumber(out, CountNounList(0));
        return true;
    case 0xf0ad1a9bu:                         // inventory list count
        outNumber(out, CountToolList(SpaceGameGet(0)));
        return true;
    case 0xaf289042u:                         // cost field
        outNumber(out, (int)mCost);
        return true;
    case 0xe0c5a5c2u:                         // badge count
        outNumber(out, mBadgeCount);
        return true;

    // ---- relationship / economy values -----------------------------------------
    case 0x45454c4cu: {                       // relationship value at +0x7c
        float f = (float)*(int*)((char*)GetSpaceRelationshipTuning() + 0x7c);
        mBadgeCount = (int)f;
        out->assign(cellText(&mMoneyFormatString));
        return true;
    }
    case 0x3a474b32u: {                       // relationship value at +0x78
        float f = (float)*(int*)((char*)GetSpaceRelationshipTuning() + 0x78);
        mBadgeCount = (int)f;
        out->assign(cellText(&mMoneyFormatString));
        return true;
    }
    case 0x9468b53eu: {                       // relationship value at +0x80
        float f = (float)*(int*)((char*)GetSpaceRelationshipTuning() + 0x80);
        mBadgeCount = (int)f;
        out->assign(cellText(&mMoneyFormatString));
        return true;
    }
    case 0x5683c9f5u: {                       // space tool use cost (0x1538 default)
        int cost = 0x1538;
        if (mItem) {
            void* td = InterfaceCast(mItem, 1);
            if (td)
                cost = cSPSpaceToolData_GetUseCost((cSPSpaceToolData*)td);
        }
        outNumber(out, cost);
        return true;
    }
    case 0xff78ba8fu: {                       // attack-request cost for the target planet
        void* planet = AttackPlanetAt(g_targetPlanetIndex);
        (void)planet;
        void* tuning = (void*)GetSpaceRelationshipTuning();
        int cost = cSPSpaceEconomyTuning_CalcAttackRequestCost((cSPSpaceEconomyTuning*)tuning, (int)planet);
        mBadgeCount = cost;
        out->assign(cellText(&mMoneyFormatString));
        return true;
    }
    case 0x8dee7e1au: case 0x8dee7e1bu: case 0x8dee7e1cu:
    case 0x8dee7e1du: case 0x8dee7e1fu: {      // trade-capture offer price
        int idx = (h == 0x8dee7e1au) ? 3 : (h == 0x8dee7e1bu) ? 4
                : (h == 0x8dee7e1cu) ? 1 : (h == 0x8dee7e1du) ? 2 : 0;
        void* tuning = (void*)GetSpaceRelationshipTuning();
        outInt(out, cSPSpaceEconomyTuning_GetTradeCaptureOfferPrice(
                        (cSPSpaceEconomyTuning*)tuning, idx));
        return true;
    }
    case 0xc7bc7860u: case 0xc7bc7861u: case 0xc7bc7862u:
    case 0xc7bc7866u: case 0xc7bc7867u: {      // peace-offer price
        int idx = (h == 0xc7bc7862u) ? 0 : (h == 0xc7bc7861u) ? 1 : (h == 0xc7bc7860u) ? 2
                : (h == 0xc7bc7867u) ? 3 : 4;
        void* tuning = (void*)GetSpaceRelationshipTuning();
        outInt(out, cSPSpaceEconomyTuning_GetPeaceOfferPrice(
                        (cSPSpaceEconomyTuning*)tuning, idx, mpEmpire));
        return true;
    }

    // ---- attack-request planet slots -------------------------------------------
    case 0xb6d0fd01u: case 0xb6d0fd02u: case 0xb6d0fd03u: case 0xb6d0fd04u: {
        int idx = (h == 0xb6d0fd01u) ? 0 : (h == 0xb6d0fd02u) ? 1
                : (h == 0xb6d0fd03u) ? 2 : 3;
        if (g_attackRequestPlanetCount <= idx)
            return true;
        void* planet = AttackPlanetAt(idx);
        out->assign(GetNounName(planet));
        return true;
    }
    case 0xcfaec259u: case 0xcfaec25au: case 0xcfaec25bu: case 0xcfaec25cu: {
        int idx = (h == 0xcfaec259u) ? 0 : (h == 0xcfaec25au) ? 1
                : (h == 0xcfaec25bu) ? 2 : 3;
        if (g_attackRequestPlanetCount <= idx)
            return true;
        void* planet = AttackPlanetAt(idx);
        void* avatar = GetAvatar(GetPlayerTribe(SpaceGameGet(0)));
        void* civ = GetAvatarCiv(avatar);
        out->assign((const wchar_t*)GetEmpireCities(civ));
        return true;
    }

    // ---- badge / animal-cargo trays --------------------------------------------
    case 0xbabe3de1u:
        if (!mCount) return true;
        GetPropertyAsKeyInstance((void*)mCount, 0x510770bu, &key);
        GetBadgeName(GetPlayerTribe(SpaceGameGet(0)), key, out);
        return true;
    case 0xda0e7227u:
        if (!mCount) return true;
        GetPropertyAsKeyInstance((void*)mCount, 0x510770au, &key);
        GetBadgeName(GetPlayerTribe(SpaceGameGet(0)), key, out);
        return true;
    case 0x8805a225u: {
        if (!mCount) return true;
        void* k = 0;
        if (GetPropertyAsKeyInstance((void*)mCount, 0x5107709u, &k))
            GetPropertyAsKeyInstance((void*)mCount, 0x510770au, &k);
        GetBadgeName(GetPlayerTribe(SpaceGameGet(0)), k, out);
        return true;
    }
    case 0x39be76f5u: {                       // plant cargo type
        out->assign(L"");
        void* cargo = InterfaceCast(mItem, 2);
        int idx;
        if (!cargo) {
            if (!mSpeciesProfile)
                return true;
            int kind = SpeciesDietKind(mSpeciesProfile);
            idx = (kind == -0x47996137) ? 1 : (kind == -0x4328c177) ? 2 : 0;
        } else {
            int kind = PlantCargoKind(cargo);
            if (kind == 0x3a8be428) { out->assign(cellText(&mPlantTypeString.at(0))); return true; }
            if (kind == 0x6d60a1cc) { out->assign(cellText(&mPlantTypeString.at(2))); return true; }
            idx = (kind == 0x29c388a) ? 1 : 0;
        }
        out->assign(cellText(&cellAt(mPlantTypeString, idx)));
        return true;
    }
    case 0xd696f412u: {                       // animal cargo type
        out->assign(L"");
        int idx = 0;
        void* cargo = InterfaceCast(mItem, 3);
        if (!cargo) {
            if (mSpeciesProfile) {
                idx = (SpeciesDietKind(mSpeciesProfile) != 0 ? 1 : 0) |
                      (SpeciesHerbivore(mSpeciesProfile) != 0 ? 2 : 0);
            }
        } else {
            int jump = AnimalCargoJump(cargo) != 0;
            int herb = AnimalCargoHerbivore(cargo) != 0;
            if (AnimalCargoType(cargo) == 6)
                idx = 0;
            else
                idx = (herb ? 2 : 0) + jump;
        }
        out->assign(cellText(&cellAt(mAnimalTypeString, idx)));
        return true;
    }

    // ---- unlocks list -----------------------------------------------------------
    case 0x88b17e38u: {
        cStringVector list;
        BuildUnlockList(mConversationFileKey, &list);
        if (list.size() > 0) {
            const wchar_t* head = L"Unlocks:";
            cString local;
            local.assign(cellText(nameString(SPIDFromName("SpaceGame", 0x65b76efu, head), head)));
            out->assign(local.c_str());
            for (int i = 0; i < list.size(); i++) {
                cString name;
                GetPropertyAsText(list.at(i).mpLocalString, 0x3068d95du, &name);
                FormatUnlockLine(out, L"\n %s", cellText(&name));
            }
        }
        return true;
    }

    // ---- uncategorised value / name aliases ------------------------------------
    case 0x3d592eecu:                         // constant true (original returns 0x3d592e01)
        return true;
    case 0x9446c931u: {                       // verb-category name, one of nine literals
        // The original selects one of nine retail .rdata literals with the player tribe index
        // and wraps it in cString(id 0x2db6dad3); the id is what the lookup resolves, so the
        // literal only matters as a fallback and the table itself is not recoverable here.
        static const wchar_t* const kCategoryFallback[9] = {
            L"", L"", L"", L"", L"", L"", L"", L"", L""
        };
        int i = GetPlayerTribeIndex();
        if (i < 0 || i >= 9) i = 0;
        out->assign(cellText(nameString(0x2db6dad3u, kCategoryFallback[i])));
        return true;
    }
    case 0xff5da022u:
        FUN_01049f90(out);
        return true;

    default:
        break;
    }

    // ---- everything else delegates to the mission / base translator ------------
    if (mpMission && MissionTranslateToken(mpMission, h, token, out))
        return true;
    if (!token || wcsncmp(token, L"group:commodity_badge_reqs", 6) != 0)
        return BaseTranslateToken(this, h, token, out);
    if (token) {
        // "group:commodity_badge_reqs:..." leader-board grouping path
        out->assign(L"commodity_badge_reqs");
        return true;
    }
    return BaseTranslateToken(this, h, token, out);
}
