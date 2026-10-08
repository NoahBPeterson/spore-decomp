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
