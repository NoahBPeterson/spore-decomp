// Slice s00b29820: save-game message handler (0x00b29820, 2260 bytes), anonymous-namespace class.
// Handles four messages (HandleMessage(messageID, data), thiscall ret 8, always returns false):
//   0x62d91c2   forwards to this->FUN_00b26790
//   0x1cd20f0   "global save" request (sOnButtonSaveClick posts it): when idle and enabled, starts the
//               save timer, shows the busy cursor (0x1003), re-posts 0x685dbfa and pauses the game
//   0x685dbfa   timer tick: waits for the two stopwatches (1500 ms / 1000 ms), then restores the cursor,
//               un-pauses, builds the save name (home planet name + L".spo" suffix, '/' and '\\' -> '_'),
//               announces it (message 0x680c633), updates star/planet state, saves and reports the result
//   0x689c9b9   same save without the timers (quick save); only shows the callout when data == 0 on success
// Flags: /O2 /MD /Gy /EHsc /TP (default).
#include "types.h"
#include <stddef.h>

// ------------------------------------------------------------------------------------------------
// EA operator new / delete
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void  operator delete[](void* p);                                                                            // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }

// ------------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t> (16 bytes: begin/end/capacity + allocator)
struct wstringO;
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;

    wstring& assign(const wchar_t* b, const wchar_t* e);          // 0x00423650
    wstring  substr(unsigned pos, unsigned n) const;              // 0x00453d20 (sret, thiscall, ret 0xc)
    wstringO substrO(unsigned pos, unsigned n) const;             // 0x00453d20 (same function)
    wstring& assignO(const wstring& x);                           // 0x0057cb60 (operator=, out of line)
    wstring& assignO(const wstringO& x);                          // 0x0057cb60
    ~wstring() {
        if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            operator delete[](mpBegin);
    }
    wstring& operator=(const wstring& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    __forceinline wstring& operator=(const wchar_t* p) {
        const wchar_t* e = p;
        while (*e)
            ++e;
        return assign(p, p + (e - p));
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    wchar_t& operator[](unsigned i) { return mpBegin[i]; }
    const wchar_t* c_str() const { return mpBegin; }
};
wstring operator+(const wstring& l, const wchar_t* r);             // 0x0057cba0 (cdecl, sret)

// Same 16-byte string, but with the destructor and operator= left out of line. cl's inliner ran out
// of budget at the first (timer) site of the original, so there the string temporaries call the
// shared copies at 0x00933960 / 0x0057cb60 instead of expanding them.
struct wstringO {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    ~wstringO() { DeallocateSelf(); }
    void DeallocateSelf();                                         // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};
wstringO PlusO(const wstring& l, const wchar_t* r);                // 0x0057cba0 (cdecl, sret)

extern wstring sDefaultSavedGameFilename;                          // 0x0167df60
extern const wchar_t* const sSaveExtension;                        // 0x015689a8 (L".spo")
extern char gSaveEnabled;                                          // 0x015689ac
extern int  gSavedCursor;                                          // 0x0167df10

// ------------------------------------------------------------------------------------------------
// EA::Stopwatch (see s004cc190): 8+8+4+4 bytes
namespace EA {
class Stopwatch {
public:
    uint64_t GetElapsedCycles() const;                             // 0x0093a3a0 (PDB name uncertain)
    float GetElapsedTimeFloat() const { return (float)(int64_t)GetElapsedCycles() * mfStopwatchCyclesToUnitsCoefficient; }
    void Restart();                                                // 0x00571e80
    void Stop();                                                   // 0x0093a2e0
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
};
}
extern EA::Stopwatch gSaveTimer;                                   // 0x0167df70 (1000 ms, ticks until the save)
extern EA::Stopwatch gSaveDelayTimer;                              // 0x0167df88 (1500 ms)

// ------------------------------------------------------------------------------------------------
// game objects (stubs)
struct cPlanetRecord {
    uint32_t pad00[6];
    wstring  mName;                                                // +0x18 (what 0x00ecdba0 returns)
    uint32_t pad28;
    uint32_t mFlags;                                               // +0x2c
    const wstring& GetName() const;                                // 0x00ecdba0
};

struct cSPLivingUniverse {
    static cPlanetRecord* GetPlayerHomePlanet();                   // 0x01021370
    static void* GetUniverseContext();                             // 0x01021080
};

uint32_t GetCurrentGameMode();                                     // 0x00b5b800

class cUIManager {
public:
    int  FUN_008013b0();                                           // current cursor
    void SetGlobalCursor(int cursor);                              // 0x00801b60
};
cUIManager* UIManagerAccessor();                                   // 0x0067cab0

class cGameTimeManager {
public:
    void IncPauseGate(uint32_t id);                                // 0x00b32220
    void DecPauseGate(uint32_t id);                                // 0x00b32250
};
cGameTimeManager* GameTimeManager();                               // 0x00b3d380

struct IMessageServer {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void Send(uint32_t id, const void* data, int flags);   // +0x14
    virtual void Post(uint32_t id, int a, int b, int c);           // +0x18
};
IMessageServer* MessageServer();                                   // 0x0067dcc0

struct cEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);   // 0x00dd8640 (ret 0x18)
};
cEventLog* EventLog();                                             // 0x00b3d3e0

struct cStarRecord {
    void FUN_00bb9ad0(int mode);                                   // ret 4
    void FUN_00bb9b00(uint32_t flag, bool set);                    // ret 8
};
struct cStarManager {
    bool FUN_00baad00();
    cStarRecord* FUN_00bb9950();
};
cStarManager* StarManager();                                       // 0x00b3d2a0

struct GameDataPtrVector { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; };
struct tGameDataVector { uint32_t pad0; GameDataPtrVector mData; };   // vector at +4
class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* create, void* f2, void* filter, void* f4, uint32_t typeID);  // 0x00b21340 (ret 0x14)
    void RemoveNoun(void* noun);                                                                          // 0x00b225d0 (ret 4)
};
cGameNounManager* NounManager();                                   // 0x00b3d300
void FUN_00cd7d10();
void FUN_00d3d420();
void FUN_00acdff0();
void FUN_00b1e500();

#define V(n) virtual void s##n();
struct IPlanetObject {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
    V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32)
    virtual void Refresh();                                        // slot 33 (+0x84)
};
#undef V
struct cPlanetModelObj {
    uint32_t pad0[9];
    IPlanetObject* mpObject;                                       // +0x24
};
cPlanetModelObj* PlanetModel();                                    // 0x00b3d350

namespace Simulator {
class SimSingleton {
public:
    uint32_t pad[50];                                              // 0xc8 bytes
    SimSingleton();                                                // 0x00ae5c30
    void FUN_00ae5930();
    static SimSingleton* sInstance;                                // 0x0167a60c
};
}
void FUN_006b2350();
void FUN_006b4840();

struct ICaptionService {                                            // 0x0067de40 result's vslot 8 result
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10(); virtual void c11(); virtual void c12();
    virtual void SetText(const wchar_t* text, int flag);           // +0x34
};
struct IServiceRoot {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4();
    virtual void r5(); virtual void r6(); virtual void r7();
    virtual ICaptionService* GetCaptionService();                  // +0x20
};
IServiceRoot* FUN_0067de40();

struct tCalloutConfig;
struct tResultKey;
extern tCalloutConfig gCalloutConfigTimer;                         // 0x01568a7c
extern tCalloutConfig gCalloutConfigQuick;                         // 0x01568a84
extern tResultKey gResultOk;                                       // 0x01568a64
extern tResultKey gResultFail;                                     // 0x01568a70
namespace UI { void CalloutMessageBox(tCalloutConfig* cfg, tResultKey* key); }   // 0x00809db0

namespace {

class cSaveGameHandler {
public:
    uint8_t pad00[0x45];
    bool    mbBusy;                                                // +0x45
    bool    mbLastSaveFailed;                                      // +0x46

    void FUN_00b26790();                                           // 0x00b26790
    bool FUN_00b282e0();                                           // 0x00b282e0
    bool FUN_00b28750();                                           // 0x00b28750
    void FUN_00b28ec0(const wchar_t* name, bool flag);             // 0x00b28ec0 (ret 8)

    static __forceinline unsigned CountGameData() {
        cGameNounManager* nm = NounManager();
        GameDataPtrVector& v = nm->GetGameDataVector(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0, (void*)FUN_00b1e500,
            0x018c43e8)->mData;
        return (unsigned)(v.mpEnd - v.mpBegin);
    }

    // Builds the save name from the home planet's name and appends the extension.
    static __forceinline void SetNameFromPlanet(cPlanetRecord* planet) {
        sDefaultSavedGameFilename = planet->GetName();
        sDefaultSavedGameFilename = sDefaultSavedGameFilename + sSaveExtension;
    }

    // Everything between the busy-cursor restore and the result callout; returns true when saved.
    __forceinline bool PerformSave() {
        const wchar_t* name = sDefaultSavedGameFilename.c_str();
        bool saved;
        if (StarManager()->FUN_00baad00() && FUN_00b282e0()) {
            if (name == 0)
                SetNameFromPlanet(cSPLivingUniverse::GetPlayerHomePlanet());
            else
                sDefaultSavedGameFilename = name;
            for (unsigned i = 0; i < sDefaultSavedGameFilename.size(); ++i) {
                if (sDefaultSavedGameFilename[i] == L'\\' || sDefaultSavedGameFilename[i] == L'/')
                    sDefaultSavedGameFilename[i] = L'_';
            }
            MessageServer()->Send(0x680c633, sDefaultSavedGameFilename.c_str(), 0);
            if (GetCurrentGameMode() != 0x1654c04 || CountGameData() > 1) {
                if (!Simulator::SimSingleton::sInstance)
                    Simulator::SimSingleton::sInstance =
                        new ("Simulator/SimSingleton", 0, 0, 0, 0) Simulator::SimSingleton();
                Simulator::SimSingleton::sInstance->FUN_00ae5930();
            }
            FUN_006b2350();
            cStarRecord* star = StarManager()->FUN_00bb9950();
            switch (GetCurrentGameMode()) {
            case 0x1654c00:
                star->FUN_00bb9ad0(1);
                star->FUN_00bb9b00(0x80, true);
                break;
            case 0x1654c01:
                star->FUN_00bb9ad0(1);
                star->FUN_00bb9b00(0x80, false);
                break;
            case 0x1654c02:
                star->FUN_00bb9ad0(2);
                star->FUN_00bb9b00(0x80, false);
                break;
            case 0x1654c04:
                star->FUN_00bb9ad0(4);
                star->FUN_00bb9b00(0x80, false);
                break;
            case 0x1654c05:
                star->FUN_00bb9ad0(5);
                star->FUN_00bb9b00(0x80, false);
                break;
            }
            star->FUN_00bb9b00(2, true);
            cPlanetRecord* home = cSPLivingUniverse::GetPlayerHomePlanet();
            if (home)
                home->mFlags |= 1;
            FUN_006b4840();
            if (PlanetModel()->mpObject) {
                cPlanetModelObj* pm = PlanetModel();
                IPlanetObject* obj = pm->mpObject;
                obj->Refresh();
            }
            FUN_00b28ec0(sDefaultSavedGameFilename.c_str(), true);
            FUN_006b4840();
            saved = StarManager()->FUN_00baad00() ? FUN_00b28750() : false;
        } else {
            saved = false;
        }
        return saved;
    }

    // @ 0x00b29820
    bool HandleMessage(uint32_t messageID, void* data) {
        switch (messageID) {
        case 0x62d91c2:
            FUN_00b26790();
            return false;
        case 0x1cd20f0:
            if (gSaveTimer.mnStartTime == 0 && gSaveEnabled && !mbBusy) {
                if (GetCurrentGameMode() == 0x1654c05 && !cSPLivingUniverse::GetUniverseContext())
                    goto postFeedback;
                gSaveEnabled = 0;
                gSaveTimer.Restart();
                gSavedCursor = UIManagerAccessor()->FUN_008013b0();
                UIManagerAccessor()->SetGlobalCursor(0x1003);
                MessageServer()->Post(0x685dbfa, 0, 0, 0);
                { cGameTimeManager* gtm = GameTimeManager(); gtm->IncPauseGate(0x4bf38a7); }
                return false;
            }
            return false;
        case 0x685dbfa: {
            if (gSaveDelayTimer.mnStartTime != 0) {
                if (gSaveDelayTimer.GetElapsedTimeFloat() < 1500.0f) {
                    MessageServer()->Post(0x685dbfa, 0, 0, 0);
                    return false;
                }
                gSaveDelayTimer.Stop();
                gSaveEnabled = 1;
            }
            if (gSaveTimer.mnStartTime == 0)
                return false;
            if (gSaveTimer.GetElapsedTimeFloat() < 1000.0f) {
                MessageServer()->Post(0x685dbfa, 0, 0, 0);
                return false;
            }
            gSaveTimer.Stop();
            UIManagerAccessor()->SetGlobalCursor(gSavedCursor);
            { cGameTimeManager* gtm = GameTimeManager(); gtm->DecPauseGate(0x4bf38a7); }
            if (cSPLivingUniverse::GetPlayerHomePlanet()) {
                sDefaultSavedGameFilename.assignO(cSPLivingUniverse::GetPlayerHomePlanet()->GetName());
                sDefaultSavedGameFilename.assignO(PlusO(sDefaultSavedGameFilename, sSaveExtension));
            }
            bool saved = PerformSave();
            wstringO shown = sDefaultSavedGameFilename.substrO(0, sDefaultSavedGameFilename.size() - 4);
            FUN_0067de40()->GetCaptionService()->SetText(shown.c_str(), 0);
            if (saved) {
                mbLastSaveFailed = false;
                UI::CalloutMessageBox(&gCalloutConfigTimer, &gResultOk);
            } else {
                mbLastSaveFailed = true;
                UI::CalloutMessageBox(&gCalloutConfigTimer, &gResultFail);
            }
            return false;
        }
        case 0x689c9b9: {
            if (GetCurrentGameMode() == 0x1654c05 && !cSPLivingUniverse::GetUniverseContext()) {
            postFeedback:
                EventLog()->PostFeedbackEvent(0x6251278c, 0x131a9f54, 0, 0, 1, 0);
                return false;
            }
            if (cSPLivingUniverse::GetPlayerHomePlanet())
                SetNameFromPlanet(cSPLivingUniverse::GetPlayerHomePlanet());
            bool saved = PerformSave();
            wstring shown = sDefaultSavedGameFilename.substr(0, sDefaultSavedGameFilename.size() - 4);
            FUN_0067de40()->GetCaptionService()->SetText(shown.c_str(), 0);
            if (saved) {
                mbLastSaveFailed = false;
                if (data == 0)
                    UI::CalloutMessageBox(&gCalloutConfigQuick, &gResultOk);
            } else {
                mbLastSaveFailed = true;
                UI::CalloutMessageBox(&gCalloutConfigQuick, &gResultFail);
            }
            return false;
        }
        }
        return false;
    }
};


// Keeps the internal-linkage method alive in the object (the original is reached through a vtable).
bool (cSaveGameHandler::*gKeepHandleMessage)(uint32_t, void*) = &cSaveGameHandler::HandleMessage;

}  // namespace

// ================================================================================================
// Claimed functions 00b2a100..00b2a880 (same save-game module).
// ================================================================================================

// --- external helpers ---------------------------------------------------------------------------
void __stdcall FUN_00b294c0(const wchar_t* name, int flag);                 // 0x00b294c0 (ret 8)
void  __cdecl   SgMemset(void* dst, int value, unsigned size);             // 0x011e073e
void* __cdecl   RBTreeIncrement(void* node);                               // 0x00921580
extern int      g167e09c;                                                  // 0x0167e09c

struct SgTarget;
struct SgVec3 {
    float x, y, z;
    int IsCloser(const SgTarget& a, const SgTarget& b) const;              // 0x00b2a540 (ret 8)
};
extern SgVec3   gVec167e0a0;                                               // 0x0167e0a0

struct SgModel;
struct SgPlanet {
    SgModel* FUN_008414c0();                                               // 0x008414c0
};
SgPlanet* __cdecl FUN_01021260();                                          // 0x01021260
void*     __cdecl FUN_00b3d3b0();                                          // 0x00b3d3b0
void*     __cdecl FUN_00b3d3c0();                                          // 0x00b3d3c0

struct SgObstacleMgr {
    uint64_t FUN_00b72410(uint32_t a, uint32_t b);                         // 0x00b72410 (ret 8)
    void*    FindById(uint32_t a, uint32_t b, uint32_t c);                 // 0x00b74e90 (ret 0xc)
    void     FUN_00b74ef0(void* obj);                                      // 0x00b74ef0 (ret 4)
};

struct SgObstacle {
    char     pad[0x64];
    uint32_t m64;                                                          // +0x64
    void FUN_00b73de0(int v);                                              // 0x00b73de0 (ret 4)
    void FUN_00b725e0(int v);                                              // 0x00b725e0 (ret 4)
};

struct SgNoun {
    char     pad[0x13c];
    uint32_t m13c;                                                         // +0x13c
    uint32_t m140;                                                         // +0x140
};

// The mask owner updated by FUN_00b2a110: a 16-bit slot mask per (row, block, column).
struct SgMaskOwner {
    char     pad[0x258];
    int      m258;                                                         // +0x258 changed-cell counter
    char     pad25c[0x2c0 - 0x25c];
    uint16_t mMask[6][4][4];                                               // +0x2c0 (0xc0 bytes)
    void FUN_00b2a110();
};

struct SgIface35e0 {
    void FUN_00ff35e0(int v);                                              // 0x00ff35e0 (ret 4)
};

struct SgHandler750 {
    char         pad[0x3c];
    SgIface35e0* m3c;                                                      // +0x3c
    SgMaskOwner* m40;                                                      // +0x40
    void FUN_00b2a750(uint32_t flags);                                     // 0x00b2a750 (ret 4)
};

// --- reference-counted object and the 0x18-byte entry used by the list --------------------------
struct SgRefObj {
    virtual void AddRef();
    virtual void Release();
};

struct SgSmartPtr {
    SgRefObj* p;
    SgSmartPtr() : p(0) {}
    SgSmartPtr(SgRefObj* q) : p(q) { if (p) p->AddRef(); }
    ~SgSmartPtr() { if (p) p->Release(); }
    void Reset() { if (SgRefObj* q = p) { p = 0; q->Release(); } }
};

struct SgEntry {
    uint32_t   m0;                                                         // +0x00
    uint32_t   m4;                                                         // +0x04
    uint32_t   m8;                                                         // +0x08
    uint32_t   mC;                                                         // +0x0c
    SgSmartPtr mObj;                                                       // +0x10
    uint32_t   m14;                                                        // +0x14
    SgEntry(uint32_t a, uint32_t b, uint32_t c, SgRefObj* o);
    ~SgEntry();
};

struct SgEntryList {
    char     pad[0x15c];
    SgEntry* mBegin;                                                       // +0x15c
    SgEntry* mEnd;                                                         // +0x160
    SgEntry* FUN_00b2a690(uint32_t a, uint32_t b, uint32_t c);             // 0x00b2a690 (ret 0xc)
};

// --- 0x24-byte element copied by the two eastl vector helpers ----------------------------------
struct SgElement24 {
    virtual ~SgElement24();                                                // scalar deleting dtor 0x00b2a4b0
    SgElement24(const SgElement24& o);                                     // 0x00b2a460 (ret 4)
    SgElement24& operator=(const SgElement24& o);
    int   m4, m8, mC;
    float f10, f14, f18;
    int   m1c, m20;
};

SgElement24* FUN_00b2a3b0(SgElement24* first, SgElement24* last, SgElement24* dst);   // 0x00b2a3b0
SgElement24* FUN_00b2a400(SgElement24* first, SgElement24* last, SgElement24* dst);   // 0x00b2a400

// --- geometry ----------------------------------------------------------------------------------
struct SgIPoint {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10();
    virtual const SgVec3* GetPoint() const;                                // +0x2c
};

struct SgTarget {
    char     pad[0x34];
    SgIPoint m34;                                                          // +0x34 embedded object (vptr at +0x34)
};

struct SgProjectile {
    void GetEndPoints(SgVec3* a, SgVec3* b);                               // 0x00cb8ba0 (ret 8)
};

struct SgTool {
    char          pad[0x124];
    SgProjectile* m124;                                                    // +0x124
    bool  FUN_0104cd50();                                                  // 0x0104cd50
    void* GetStrategy();                                                   // 0x0104f930
};

struct SgInventoryObj {
    char     pad[0x34];
    SgIPoint m34;                                                          // +0x34 embedded object (vptr at +0x34)
    SgTool* FUN_00ff3f00();                                                // 0x00ff3f00
};

struct SgSpaceGame {
    SgInventoryObj* GetPlayerInventory();                                  // 0x00a1ad60
};

SgSpaceGame* __cdecl SP_SpaceGameGet();                                    // 0x01002bd0
SgSpaceGame* __cdecl SP_GetUFOSimulator();                                 // 0x00ffbe50

struct SgNode {
    char     pad[0x10];
    uint32_t m10;                                                          // +0x10
    void*    m14;                                                          // +0x14
};
struct SgVal {
    char     pad[0x120];
    uint32_t m120;                                                         // +0x120
    uint32_t m124;                                                         // +0x124
};

// --- functions ---------------------------------------------------------------------------------

// @ 0x00b2a100
void FUN_00b2a100()
{
    FUN_00b294c0(L"snapshot.spo", 0);
}

// @ 0x00b2a110
void SgMaskOwner::FUN_00b2a110()
{
    SgPlanet* planet = FUN_01021260();
    if (planet)
        planet = (SgPlanet*)planet->FUN_008414c0();
    if (!planet)
    {
        SgMemset((char*)this + 0x2c0, 0, 0xc0);
        return;
    }
    char* candBase = (char*)FUN_00b3d3b0() + 0x4c;
    char* cell = (char*)planet + 0x54;
    unsigned short* out = &mMask[0][0][0];
    for (int a = 0; a < 6; ++a)
    {
        int changed = 0;
        for (int b = 0; b < 4; ++b)
        {
            for (int c = 0; c < 4; ++c)
            {
                unsigned mask = 0;
                char* g = cell;
                char* cand = candBase;
                for (int i = 0; i < 9; i += 3)
                {
                    if (*(int*)(g + 0xc) > 0)
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            int* e = (int*)(cand + j * 0x1c - 8);
                            if (e[0] == *(int*)g && e[1] == *(int*)(g + 4) && e[2] == *(int*)(g + 8))
                            {
                                mask |= 1u << (i + j);
                                break;
                            }
                        }
                    }
                    g += 0x10;
                    cand += 0x54;
                }
                if ((unsigned short)(out[c] & 0x7fff) != (unsigned short)mask)
                {
                    out[c] = (unsigned short)(mask | 0x8000);
                    ++changed;
                }
                cell += 0x54;
            }
            out += 4;
        }
        if (changed)
            ++m258;
    }
}

// @ 0x00b2a2a0
void __stdcall FUN_00b2a2a0(SgNoun* noun, char flag)
{
    if (flag)
    {
        SgObstacle* o = (SgObstacle*)((SgObstacleMgr*)FUN_00b3d3c0())->FindById(noun->m13c, 0, noun->m140);
        if (o)
        {
            o->FUN_00b73de0(0);
            if (o->m64 == 0)
                o->FUN_00b725e0(1);
        }
    }
    NounManager()->RemoveNoun(noun);
}

// @ 0x00b2a3b0
SgElement24* FUN_00b2a3b0(SgElement24* first, SgElement24* last, SgElement24* dst)
{
    for (; first != last; ++first, ++dst)
        *dst = *first;
    return dst;
}

// @ 0x00b2a400
SgElement24* FUN_00b2a400(SgElement24* first, SgElement24* last, SgElement24* dst)
{
    while (last != first)
    {
        --last;
        --dst;
        *dst = *last;
    }
    return dst;
}

// @ 0x00b2a460
SgElement24::SgElement24(const SgElement24& o)
{
    m20 = 0;
    *this = o;
}

// @ 0x00b2a4b0
SgElement24::~SgElement24()
{
    m4 = 0;
    m8 = 0;
    mC = 0;
    f10 = 0.0f;
    f14 = 0.0f;
    f18 = 0.0f;
    m1c = 0;
    m20 = 0;
}

SgElement24& SgElement24::operator=(const SgElement24& o)
{
    m4 = o.m4;
    m8 = o.m8;
    mC = o.mC;
    f10 = o.f10;
    f14 = o.f14;
    f18 = o.f18;
    m1c = o.m1c;
    m20 = o.m20;
    return *this;
}

// @ 0x00b2a540
int SgVec3::IsCloser(const SgTarget& a, const SgTarget& b) const
{
    const SgVec3* pa = a.m34.GetPoint();
    SgVec3 da;
    da.x = x - pa->x;
    da.y = y - pa->y;
    da.z = z - pa->z;
    const SgVec3* pb = b.m34.GetPoint();
    SgVec3 db;
    db.z = z - pb->z;
    db.y = y - pb->y;
    db.x = x - pb->x;
    return da.y * da.y + da.x * da.x + da.z * da.z
        < db.z * db.z + db.y * db.y + db.x * db.x;
}

// @ 0x00b2a620
SgEntry::SgEntry(uint32_t a, uint32_t b, uint32_t c, SgRefObj* o)
    : m0(a), m8(b), mC(c), mObj(o)
{
}

// @ 0x00b2a650
SgEntry::~SgEntry()
{
    m0 = 0xffffffff;
    m8 = 0;
    mC = 0;
    mObj.Reset();
}

// @ 0x00b2a690
SgEntry* SgEntryList::FUN_00b2a690(uint32_t a, uint32_t b, uint32_t c)
{
    SgEntry* result = 0;
    uint64_t key = ((SgObstacleMgr*)FUN_00b3d3c0())->FUN_00b72410(a, b);
    for (SgEntry* e = mBegin; e != mEnd; ++e)
    {
        uint32_t v = e->m8;
        if (v == (uint32_t)key && (v = e->mC) == (uint32_t)(key >> 32) && e->m0 == c)
        {
            result = e;
            break;
        }
    }
    return result;
}

// @ 0x00b2a6f0
void __stdcall FUN_00b2a6f0(SgEntry* e)
{
    SgObstacleMgr* mgr = (SgObstacleMgr*)FUN_00b3d3c0();
    SgObstacle* o = (SgObstacle*)mgr->FindById(e->m8, e->mC, e->m0);
    if (o)
        mgr->FUN_00b74ef0(o);
    if (e->mObj.p)
    {
        NounManager()->RemoveNoun(e->mObj.p);
        e->mObj.Reset();
    }
}

// @ 0x00b2a750
void SgHandler750::FUN_00b2a750(uint32_t flags)
{
    SgHandler750* self = this;
    uint32_t f = flags & 0xf;
    if (f)
        g167e09c = 0;
    SgIface35e0* p = self->m3c;
    if ((flags & 8) && p)
        p->FUN_00ff35e0(1);
    if (self->m40 && f)
        self->m40->FUN_00b2a110();
}

// @ 0x00b2a790
SgVec3 __stdcall FUN_00b2a790()
{
    SgTool* tool = ((SgSpaceGame*)SP_SpaceGameGet())->GetPlayerInventory()->FUN_00ff3f00();
    if (tool && tool->FUN_0104cd50() && tool->GetStrategy() && tool->m124)
    {
        SgVec3 a, b;
        tool->m124->GetEndPoints(&a, &b);
        return a;
    }
    if (((SgSpaceGame*)SP_GetUFOSimulator())->GetPlayerInventory())
    {
        SgInventoryObj* inv = ((SgSpaceGame*)SP_GetUFOSimulator())->GetPlayerInventory();
        const SgVec3* p = inv->m34.GetPoint();
        return *p;
    }
    return gVec167e0a0;
}

// @ 0x00b2a880
void FUN_00b2a880(void** out, void* begin, void* end, uint32_t idLo, uint32_t idHi)
{
    while (begin != end)
    {
        SgVal* v = (SgVal*)((SgNode*)begin)->m14;
        if (v->m120 == idLo && v->m124 == idHi)
            break;
        begin = RBTreeIncrement(begin);
    }
    *out = begin;
}
