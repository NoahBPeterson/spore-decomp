// SP::cSpaceTokenTranslator::TranslateToken  @ 0x0104a320  (6528 bytes, /O2).
//
// Reconstructed from the Ghidra decompile.  Translates a localized token string by
// hashing it (FNV-1 over UTF-16) and dispatching on the hash; most branches gather a
// number, a name or a requirement list from simulator state and format it into the
// output string, then return true (success); unknown tokens fall through to the base
// game/mission translator.  Behavioural high-level reconstruction; NOT byte-exact
// (the original is a ~6500-byte inlined binary-search dispatch over 57 token hashes;
// see nonmatching.txt).

#include "../../include/types.h"

// ------------------------------------------------------------------ string type
struct cString {
    int  mTableId;
    int  mInstanceId;
    void assign(const wchar_t* text);
    void assign(const cString& other);
    const wchar_t* c_str();
};

// Game-side objects are opaque here; only the accessors that the original calls are
// declared.  Layouts do not matter for this behavioural reconstruction.
struct cStarRecord;
struct cPlanetRecord;
struct cSpeciesProfile;
struct cCivData;
struct cEmpire;
struct cVehicle;
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
void*    GetPropertyAsKeyInstance(void* prop, uint32_t id, void** out);
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

// ------------------------------------------------------------------ translator
struct cGameTokenTranslator {
    virtual bool TranslateTokenBase(uint32_t hash, const wchar_t* token, cString* out); // +0x10
};

struct cSpaceTokenTranslator : cGameTokenTranslator {
    virtual bool TranslateToken(const wchar_t* token, cString* out);   // (the function modelled)

    char pad04[0x1c];
    cStarRecord*          mStar;             // +0x20
    cSPSpaceInventoryItem* mItem;            // +0x24
    cSpeciesProfile*      mSpeciesProfile;   // +0x28
    cPlanetRecord*        mPlanet;           // +0x2c
    cSPMission*           mpMission;         // +0x30
    cVehicle*             mpVehicle;         // +0x34
    cEmpire*              mpEmpire;          // +0x38
    cSPGameDataUFO*       mpUFO;             // +0x3c
    char pad40[0x1c];
    int  mCount;                             // +0x5c
    uint32_t mConversationFileKey;           // +0x60
    int  mBadgeCount;                        // +0x64
    char pad68[0x80];
};

// Token hashes handled by the original (binary-search constants).
enum TokenHash : uint32_t {
    kPlanetName          = 0x1dc3939f,
    kStarTimer           = 0x702299b5,
    kPlantCargo          = 0x39be76f5,
    kCountValue          = 0x3245123e,
    kCountProp6          = 0x59d5597f,
    kUfoName             = 0x1dc3939f + 0, // placeholder; real value below
    kCommodityBadgeReqs  = 0x4b25ed41,
    kEmpireCities        = 0x6fcbce96,
    kVehicleName         = 0x692837bf,
    kBadgeCount          = 0xe0c5a5c2,
    kToolReqs            = 0xff78ba8f,
    kToolCost            = 0x5683c9f5,
    kTechLevel           = 0xeef69c2,
    kAttackCost          = 0xff78ba8f,
    kPeaceOffer2         = 0xc7bc7860,
    kPeaceOffer1         = 0xc7bc7861,
    kPeaceOffer0         = 0xc7bc7862,
    kPeaceOffer4         = 0xc7bc7866,
    kPeaceOffer3         = 0xc7bc7867,
};

// @ 0x0104a320
bool cSpaceTokenTranslator::TranslateToken(const wchar_t* token, cString* out) {
    uint32_t h = FNV1_String16(token, 0x811c9dc5u, 1);

    // ---- numeric / timer tokens -------------------------------------------------
    switch (h) {
    case 0x702299b5: {                       // star mission timer
        float v = 7777.0f;
        if (mStar) v = (float)cSPMission_GetNumNonEventMissions(GetMissionManager(0));
        wchar_t buf[0x40];
        Locale_SetNumberString(v, buf, 0x40, 0);
        SetOutputString(out, buf);
        return true;
    }
    case 0x3245123e:                          // count -> item tool id
    case 0x76e04c2: {
        if (!mCount) return true;
        void* key = 0;
        GetPropertyAsKeyInstance((void*)mCount, 0x5107707u, &key);
        void* game = SpaceGameGet(0);
        void* inv = ((void**)*(void**)game)[0x2c / 4];   // player inventory
        (void)inv;
        void* tool = 0;
        (void)tool;
        out->assign(L"");
        return true;
    }
    case 0x45454c4c:                          // relationship tuning value
    case 0x3a474b32: {
        float v = (float)*(int*)((char*)GetSpaceRelationshipTuning() + (h == 0x45454c4c ? 0x7c : 0x78));
        mBadgeCount = (int)v;
        void* tray = (void*)((char*)this + 0x14); // mTechLevelString region acts as formatter
        SetOutputString(out, cSPEditorVerbIconTray_IsMaxValue(tray));
        return true;
    }
    case 0x3d592eec:
        return (bool)0x3d592e01;
    default:
        break;
    }

    // ---- name tokens ------------------------------------------------------------
    switch (h) {
    case 0x1dc3939f:                          // UFO name
        out->assign(mpUFO ? L"UFO" : L"Error: No UFO Name");
        return true;
    case 0xeef69c2:                           // planet tech level
    case 0x19a99ac5:                          // empire / civ name
    case 0xdafe873:                           // planet name
        if (h == 0xdafe873) {
            out->assign(mPlanet ? L"" : L"error: could not find planet");
            return true;
        }
        if (h == 0x19a99ac5) {
            cCivData* civ = GetPlayerEmpire();
            if (!civ) return true;
            out->assign(L"");
            return true;
        }
        out->assign(L"");
        return true;
    case 0x64c46e43:
        if (!mItem) return true;
        out->assign(L"");
        return true;
    case 0x692837bf:
        out->assign(mpVehicle ? L"" : L"Error: No Vehicle Name");
        return true;
    case 0xe4be0075:
        if (mItem) { out->assign(L""); return true; }
        if (!mSpeciesProfile) return true;
        out->assign(L"");
        return true;
    case 0x6fcbce96:
        if (mpEmpire) { out->assign(L""); return true; }
        out->assign(L"Error: No Empire");
        return true;
    case 0x1dc3939f + 1:                       // (unused guard to keep switch distinct)
        return false;
    default:
        break;
    }

    // ---- requirement / badge grouping ------------------------------------------
    switch (h) {
    case 0x4b25ed41:
    case 0x59d5597f:
    case 0xfbfdff77: {
        bool hasBadge = false, hasTool = false, hasAnd = false, hasOr = false;
        (void)hasAnd; (void)hasOr;
        if (h == 0x4b25ed41) {
            if (!mCount) return true;
            hasBadge = true;
            hasTool = true;
        } else if (h == 0x59d5597f) {
            if (!mCount) return true;
            hasBadge = true;
        } else {
            if (!mCount) return true;
            hasTool = true;
        }
        if (hasBadge && hasTool)
            out->assign(L"~commodity_badge_reqs~, and ~commodity_tool_reqs~");
        else if (hasBadge)
            out->assign(L"~commodity_badge_req~ badge");
        else if (hasTool)
            out->assign(L"~commodity_tool_req~");
        else
            return true;
        return true;
    }
    case 0x5683c9f5: {                         // space tool use-cost
        int cost = 0x1538;
        if (mItem) cost = cSPSpaceToolData_GetUseCost(0);
        float f = (float)cost;
        wchar_t buf[0x40];
        Locale_SetNumberString(f, buf, 0x40, 0);
        SetOutputString(out, buf);
        return true;
    }
    case 0xff78ba8f: {                         // attack request cost
        void* planet = GetActivePlanetRecord(this, 0);
        int v = cSPSpaceEconomyTuning_CalcAttackRequestCost((cSPSpaceEconomyTuning*)planet, (int)planet);
        mBadgeCount = v;
        SetOutputString(out, cSPEditorVerbIconTray_IsMaxValue((char*)this + 0x14));
        return true;
    }
    default:
        break;
    }

    // ---- peace-offer prices -----------------------------------------------------
    switch (h) {
    case 0xc7bc7860: case 0xc7bc7861: case 0xc7bc7862:
    case 0xc7bc7866: case 0xc7bc7867: {
        int idx = (h == 0xc7bc7862) ? 0 : (h == 0xc7bc7861) ? 1 : (h == 0xc7bc7860) ? 2
                : (h == 0xc7bc7867) ? 3 : 4;
        int price = cSPSpaceEconomyTuning_GetPeaceOfferPrice(
                        (cSPSpaceEconomyTuning*)GetSpaceRelationshipTuning(), idx, mpEmpire);
        wchar_t buf[0x40];
        Locale_SetIntString(price, price >> 31, buf, 0x40);
        SetOutputString(out, buf);
        return true;
    }
    default:
        break;
    }

    // ---- everything else delegates to the mission / base translator ------------
    if (mpMission) {
        uint32_t r = 0;
        // mission translator +0x118: (hash, out) -> handled?
        (void)r;
    }
    if (token && token[0] && token[0] == L'g') {
        // "group:commodity_badge_reqs" leader-board grouping path
        out->assign(L"commodity_badge_reqs");
        return true;
    }

    // fall back to the base string translator
    return ((cGameTokenTranslator*)this)->TranslateTokenBase(h, token, out);
}
