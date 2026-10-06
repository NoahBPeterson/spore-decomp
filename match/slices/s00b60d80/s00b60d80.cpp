// Slice s00b60d80 — 0x00b60d80, 10061 bytes.
//
// Simulator::cSimulatorSystem::Initialize()  (ModAPI SimulatorSystem.h vtable slot 0x10).
// The PDB candidate `SP::cTribeTool::TakeHit` is wrong.  Identification: `this`+0x0d is the
// "initialized" flag, `this`+0x5c is mSubSystems (eastl::vector<intrusive_ptr<
// ISimulatorStrategy>>), and the body creates every "Simulator/SubSystem/*" singleton,
// initializes it and appends it to mSubSystems, then registers game-mode strategies,
// messages, cheats, summarizers and Sporepedia large views.
//
// Module flags: /O2 without /EHsc (a local with a non-trivial dtor gets no EH frame).
// BYTE-EXACT.  The key lever: vector::DoInsertValue must have its real (EASTL) body in the TU
// (still called out of line).  With only a declaration cl treats the push_back temporary as
// escaped and reloads it after every AddRef (ecx instead of esi); with the body visible it
// keeps the temporary in esi and reloads only after DoInsertValue, like the original.
// Many callee labels in the card are ICF-folded names (e.g. 0x83c800 is the
// ArgScript::cCommandBase ctor, 0x646e40 is a cAssetBrowser method).
//
// @ 0x00b60d80

typedef unsigned int size_t;
typedef unsigned int uint32_t;

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

// EA global operator new (0x00f473a0): new(pName) T  ==  operator new(sizeof(T), pName, 0, 0, 0, 0)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete(void* p, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) throw() { return p; }
inline void  operator delete(void*, void*) throw() {}

#define SP_NEW(name) new(name, 0, 0, 0, 0)

// ---------------------------------------------------------------------------------------
// EASTL pieces
namespace eastl {
    template <typename T>
    class intrusive_ptr {
    public:
        T* mpObject;
        intrusive_ptr(T* p) : mpObject(p) { if (p) p->AddRef(); }
        intrusive_ptr(const intrusive_ptr& ip) : mpObject(ip.mpObject) { if (mpObject) mpObject->AddRef(); }
        ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
        intrusive_ptr& operator=(T* pObject)
        {
            if (pObject != mpObject) {
                T* const pTemp = mpObject;
                if (pObject)
                    pObject->AddRef();
                mpObject = pObject;
                if (pTemp)
                    pTemp->Release();
            }
            return *this;
        }
        intrusive_ptr& operator=(const intrusive_ptr& ip) { return operator=(ip.mpObject); }
        T* get() const { return mpObject; }
        T* operator->() const { return mpObject; }
    };

    template <typename T>
    class vector {
    public:
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        uint32_t mAllocator;

        void push_back(const T& value)
        {
            if (mpEnd < mpCapacity)
                ::new(mpEnd++) T(value);
            else
                DoInsertValue(mpEnd, value);
        }
        void DoInsertValue(T* position, const T& value);   // 0x00aea5d0
        T*   DoAllocate(uint32_t n);
        void DoFree(T* p, uint32_t n);
        uint32_t GetNewCapacity(uint32_t currentCapacity);
    };

    template <typename T>
    T* uninitialized_copy_ptr(T* first, T* last, T* dest)
    {
        T* pCurrent = dest;
        for (; first != last; ++first, ++pCurrent)
            ::new(pCurrent) T(*first);
        return pCurrent;
    }

    template <typename T>
    void vector<T>::DoInsertValue(T* position, const T& value)
    {
        if (mpEnd != mpCapacity) {
            const T* pValue = &value;
            if ((pValue >= position) && (pValue < mpEnd))
                ++pValue;
            ::new(mpEnd) T(*(mpEnd - 1));
            for (T* p = mpEnd - 1; p != position; --p)
                *p = *(p - 1);
            *position = *pValue;
            ++mpEnd;
        } else {
            const uint32_t nPosSize  = uint32_t(position - mpBegin);
            const uint32_t nPrevSize = uint32_t(mpEnd - mpBegin);
            const uint32_t nNewSize  = GetNewCapacity(nPrevSize);
            T* const pNewData = DoAllocate(nNewSize);
            T* pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
            ::new(pNewEnd) T(value);
            pNewEnd = uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
            for (T* p = mpBegin; p != mpEnd; ++p)
                p->~T();
            DoFree(mpBegin, uint32_t(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        }
    }
}

// ---------------------------------------------------------------------------------------
// Simulator subsystems (ISimulatorStrategy, ModAPI cStrategy.h)
namespace Simulator {

struct ISimulatorStrategy {
    virtual int  AddRef();
    virtual int  Release();
    virtual void Initialize();
    virtual void Dispose();
};

// Polymorphic prefixes used to place the ISimulatorStrategy subobject at +4/+8/+0xc.
struct cPrefix4  { virtual void PrefixFn(); };
struct cPrefix8  { virtual void PrefixFn(); uint32_t mPad; };
struct cPrefixC  { virtual void PrefixFn(); uint32_t mPad[2]; };

#define SUBSYS0(Name, Size) \
    struct Name : ISimulatorStrategy { Name(); uint32_t mData[((Size) - 4) / 4]; }
#define SUBSYSN(Name, Size, Prefix, Off) \
    struct Name : Prefix, ISimulatorStrategy { Name(); uint32_t mData[((Size) - (Off) - 4) / 4]; }

SUBSYS0(cGameTimeManager,            0x80);     // ctor 0x00b31ea0
SUBSYSN(cGonzagoPhysics,           0x14f0, cPrefix4, 4);   // 0x00b4d220
SUBSYSN(cGameViewManager,           0x1a8, cPrefix8, 8);   // 0x00b379f0
SUBSYSN(cPlanetModel,             0x13208, cPrefix4, 4);   // 0x00b863e0
SUBSYS0(cAnimalSpeciesManager,       0x1c);     // 0x00ac0c70
SUBSYSN(cFruitManager,           0x1ba198, cPrefix4, 4);   // 0x00b0bdb0
SUBSYSN(cObstacleManager,          0x56e0, cPrefix4, 4);   // 0x00b79740
SUBSYS0(cPlantSpeciesManager,        0x3c);     // 0x00b8ff90
SUBSYSN(cGameInputManager,          0x114, cPrefixC, 0xc); // 0x00b1c2c0
SUBSYSN(cAStar,                      0x70, cPrefix4, 4);   // 0x00ac4c20
SUBSYSN(cGameBehaviorManager,        0xa4, cPrefix4, 4);   // 0x00b0d8d0
SUBSYSN(cGameNounManager,           0x11c, cPrefix4, 4);   // 0x00b232b0
SUBSYS0(cBundleManager,              0x20);     // 0x00ac78a0
SUBSYS0(cStarManager,               0x22c);     // 0x00bae490
SUBSYS0(cGameModeManager,            0x9c);     // 0x00b1d870
SUBSYS0(cSimTicker,                  0x44);     // 0x00ba2250
SUBSYSN(cGamePersistenceManager,     0x4c, cPrefix4, 4);   // 0x00b26e10
SUBSYS0(cToolManager,               0x29c);     // 0x0104f960
SUBSYSN(cCheatObjectManager,         0x38, cPrefix4, 4);   // 0x00bd7010
SUBSYS0(cTerraformingManager,        0x94);     // 0x00bbf1f0
SUBSYSN(cGamePlantManager,          0x1e8, cPrefix4, 4);   // 0x00b2d480
SUBSYS0(cSpaceGfx,                  0x140);     // 0x010378f0
SUBSYS0(cCommGraphicsManager,        0x98);     // 0x00ae7f00
SUBSYS0(cCommManager,                0x78);     // 0x00aebde0
SUBSYS0(cSpaceTrading,               0xf8);     // 0x0103b690
SUBSYSN(cUIEventLog,                 0x70, cPrefix4, 4);   // 0x00dd7020
SUBSYSN(cUITimeline,                0x708, cPrefix8, 8);   // 0x00e43830 (dtor 0x00e3dca0)
SUBSYS0(cCastingManager,            0x194);     // 0x00acf230
SUBSYSN(cSpeciesRelationshipManager, 0x60, cPrefix4, 4);   // 0x00ba3ef0
SUBSYSN(cPlanetImpostorManager,      0x38, cPrefix4, 4);   // 0x00b7df80
SUBSYS0(cBlobShadowManager,          0x58);     // 0x00ac6b90
SUBSYSN(cCinematicManager,          0x3c8, cPrefix4, 4);   // 0x00adf420
SUBSYS0(cEventLogCommManager,        0x30);     // 0x00cfecc0
SUBSYS0(cVignetteManager,            0x74);     // 0x00bc7380
SUBSYS0(cNPCCityMusicManager,        0xc0);     // 0x00b5e260
SUBSYSN(cUIMissionLogManager,        0x80, cPrefix4, 4);   // 0x00e19680
SUBSYS0(cUIAssetDiscoveryManager,    0xa8);     // 0x00e30c60
SUBSYS0(cUIMissionCardPanel,         0x64);     // 0x00e173d0
SUBSYS0(cNanoDroneManager,           0x38);     // 0x00b71dc0
SUBSYS0(cScenarioVehicleTicker,      0x1c);     // 0x00f39df0

// "LivingUniverse": cGonzagoSubsystem (two vptrs) with an inline derived ctor.
struct cRefCountedPrefix { virtual void RcFn(); };
struct cGonzagoSubsystem : ISimulatorStrategy, cRefCountedPrefix {
    cGonzagoSubsystem();                      // 0x00b5b960
    uint32_t mData[(0x1c - 8) / 4];
};
struct cLivingUniverse : cGonzagoSubsystem {
    cLivingUniverse() {}
    virtual void Dispose();                   // vtable 0x01461850
    virtual void RcFn();                      // vtable 0x0146184c
};

// The local object constructed/destroyed around the subsystem creation (same class
// as the UITimeline subsystem: ctor 0x00e43830, dtor 0x00e3dca0).
struct cUITimelineLocal : cPrefix8, ISimulatorStrategy {
    cUITimelineLocal();                       // 0x00e43830
    ~cUITimelineLocal();                      // 0x00e3dca0
    uint32_t mData[(0x708 - 8 - 4) / 4];
};

// Singleton holder returned by 0x00b3d220.
struct cSimulatorSubSystems {
    uint32_t                      field_00;
    cGameViewManager*             mpGameViewManager;            // +04
    uint32_t                      field_08[2];
    cGameInputManager*            mpGameInputManager;           // +10
    cAStar*                       mpAStar;                      // +14
    cGameBehaviorManager*         mpGameBehaviorManager;        // +18
    cBundleManager*               mpBundleManager;              // +1c
    cGameNounManager*             mpGameNounManager;            // +20
    cStarManager*                 mpStarManager;                // +24
    cGonzagoPhysics*              mpGonzagoPhysics;             // +28
    cGameModeManager*             mpGameModeManager;            // +2c
    cSimTicker*                   mpSimTicker;                  // +30
    cGamePersistenceManager*      mpGamePersistenceManager;     // +34
    cPlanetModel*                 mpPlanetModel;                // +38
    cPlanetImpostorManager*       mpPlanetImpostorManager;      // +3c
    cBlobShadowManager*           mpBlobShadowManager;          // +40
    cGameTimeManager*             mpGameTimeManager;            // +44
    cToolManager*                 mpToolManager;                // +48
    cCheatObjectManager*          mpCheatObjectManager;         // +4c
    cGamePlantManager*            mpGamePlantManager;           // +50
    cObstacleManager*             mpObstacleManager;            // +54
    cSpaceGfx*                    mpSpaceGfx;                   // +58
    cLivingUniverse*              mpLivingUniverse;             // +5c
    cSpaceTrading*                mpSpaceTrading;               // +60
    cUIEventLog*                  mpUIEventLog;                 // +64
    cUITimeline*                  mpUITimeline;                 // +68
    cPlantSpeciesManager*         mpPlantSpeciesManager;        // +6c
    cTerraformingManager*         mpTerraformingManager;        // +70
    cFruitManager*                mpFruitManager;               // +74
    cAnimalSpeciesManager*        mpAnimalSpeciesManager;       // +78
    cCastingManager*              mpCastingManager;             // +7c
    cCommGraphicsManager*         mpCommGraphicsManager;        // +80
    cCommManager*                 mpCommManager;                // +84
    cEventLogCommManager*         mpEventLogCommManager;        // +88
    cSpeciesRelationshipManager*  mpSpeciesRelationshipManager; // +8c
    cCinematicManager*            mpCinematicManager;           // +90
    cVignetteManager*             mpVignetteManager;            // +94
    cNPCCityMusicManager*         mpNPCCityMusicManager;        // +98
    cUIMissionLogManager*         mpUIMissionLogManager;        // +9c
    cUIMissionCardPanel*          mpUIMissionCardPanel;         // +a0
    cUIAssetDiscoveryManager*     mpUIAssetDiscoveryManager;    // +a4
    cNanoDroneManager*            mpNanoDroneManager;           // +a8
    cScenarioVehicleTicker*       mpScenarioVehicleTicker;      // +ac
};
cSimulatorSubSystems* GetSubSystems();        // 0x00b3d220

// Game-mode strategies: singletons whose ISimulatorStrategy sits at +8/+0xc/+4.
struct cStrategyAt8 : cPrefix8, ISimulatorStrategy {};
struct cStrategyAtC : cPrefixC, ISimulatorStrategy {};
struct cStrategyAt4 : cPrefix4, ISimulatorStrategy {};
cStrategyAt8* GetCellModeStrategy();          // 0x00d1bf00
cStrategyAt8* GetCreatureModeStrategy();      // 0x00d38840
cStrategyAtC* GetTribeModeStrategy();         // 0x00cd40b0
cStrategyAt4* GetCivModeStrategy();           // 0x00cf74c0
cStrategyAt8* GetSpaceModeStrategy();         // 0x00fd9c60

// Content-validation summarizer installed in field_1C.
struct __declspec(novtable) IContentValidator {
    virtual void Fn0() = 0;
    virtual void Fn1() = 0;
    virtual int  AddRef() = 0;
    virtual int  Release() = 0;
};
struct cContentValidationSummarizer {
    virtual void SummarizerFn();
    uint32_t mField;
    cContentValidationSummarizer() : mField(0) {}
};
struct cSimContentValidator : IContentValidator, cContentValidationSummarizer {
    uint32_t mField2;
    cSimContentValidator() : mField2(0) {}
    virtual void Fn0();
    virtual void Fn1();
    virtual int  AddRef();
    virtual int  Release();
    virtual void SummarizerFn();
    void Setup();                             // 0x00ea8ad0
};

// Tuning / misc singletons
struct cGlobal167ea80   { void Init(); };     // 0x00b3cf40
struct cCityGameTuning  { void Init(); };     // 0x00cef050
struct cMotiveTuning    { void Init(int); };  // 0x00b71480
struct cBuildingTuning  { void SetValues(); };// 0x00cedfd0
extern cGlobal167ea80  g_167ea80;
extern cCityGameTuning g_CityGameTuning;      // 0x0169ca60
extern cMotiveTuning   g_MotiveTuning;        // 0x01687a00
extern cBuildingTuning g_BuildingTuning;      // 0x0169c078

struct cInitA { void Init(); };               // 0x01049a20
struct cInitB { void Init(); };               // 0x01030b10
struct cInitC { void Init(); };               // 0x010297e0
struct cInitD { void Init(); };               // 0x00c3b7f0
struct cInitE { void Init(); };               // 0x0107bed0
struct cSpaceCombatTuning       { void Init(); };   // 0x0102b190
struct cSpaceRelationshipTuning { void Init(); };   // 0x01041090
struct cInitF { void Init(); };               // 0x01041bc0
cInitA* GetInitA();                           // 0x01049a10
cInitB* GetInitB();                           // 0x0102f810
cInitC* GetInitC();                           // 0x01029790
cInitD* GetInitD();                           // 0x00c37360
cInitE* GetInitE();                           // 0x0107bcb0
cSpaceCombatTuning*       GetSpaceCombatTuning();        // 0x01029940
cSpaceRelationshipTuning* GetSpaceRelationshipTuning();  // 0x010407c0
cInitF* GetInitF();                           // 0x010408b0

struct cSimObj1bc { cSimObj1bc(); uint32_t mData[0x1bc / 4]; };  // 0x00c38c50
struct cSimObj30  { cSimObj30();  uint32_t mData[0x30 / 4]; };   // 0x0107bcc0
extern cSimObj1bc* g_168df68;
extern cSimObj30*  g_16e394c;

void InitMisc_b6eee0();                       // 0x00b6eee0
void InitMisc_b5cc80();                       // 0x00b5cc80

// Function-local static registrations (base 0x14 bytes).
struct cSimRegistrationBase {
    cSimRegistrationBase(int);                // 0x00692f60
    virtual ~cSimRegistrationBase();
    bool IsRegistered();                      // 0x00ab30c0
    void Register();                          // 0x00692850
    uint32_t mData[4];
};
template <int N>
struct cSimRegistration : cSimRegistrationBase {
    cSimRegistration() : cSimRegistrationBase(0) {}
    virtual ~cSimRegistration();
};

}  // namespace Simulator

// ---------------------------------------------------------------------------------------
// Resources
namespace EA { namespace Allocator {
struct ZoneObject {
    static void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00926020
    static void  operator delete(void* p, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
};
}}
namespace Resource {
struct IResourceFactory {
    virtual void Fn0();
};
struct cResourceFactoryBase : IResourceFactory, EA::Allocator::ZoneObject {
    volatile long mnRefCount;
    cResourceFactoryBase() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cFactoryCityMusic : cResourceFactoryBase {
    cFactoryCityMusic() {}
    virtual void Fn0();
};
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual bool RegisterFactory(bool add, IResourceFactory* pFactory, uint32_t typeID);  // +0x44
};
IResourceManager* GetManager();               // 0x0067dcd0
}

// ---------------------------------------------------------------------------------------
// Messaging
namespace App {
struct IMessageListener {
    virtual int AddRef();
    virtual int Release();
};
struct IMessageNames {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void AddMessageName(uint32_t id, const wchar_t* name, int flags);   // +0x1c
};
struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual bool AddListener(IMessageListener* pListener, uint32_t messageID);  // +0x20
};
IMessageNames*  GetMessageNames();            // 0x006895b0
IMessageServer* MessageServer();              // 0x0067dcc0
}

// ---------------------------------------------------------------------------------------
// Cheats (ArgScript)
namespace ArgScript {
struct ICommand { virtual void Fn0(); };
struct cCommandBase : ICommand {
    cCommandBase();                           // 0x0083c800
    uint32_t mData[3];
};
struct cArgumentSpec {
    cArgumentSpec(int);                       // 0x0083a9f0
    void ConstructSpec(const char* pDescription, ...);   // 0x0083bcd0 (cdecl, this pushed)
    uint32_t mData[0xc8 / 4];
};
}
namespace App {
struct ICheatManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void AddCheat(const char* keyword, ArgScript::ICommand* pCommand, bool bNotCheat);  // +0x18
    // compiled out in this build (the arguments are still evaluated)
    void AddDebugCheat(ArgScript::ICommand*) {}
};
ICheatManager* CheatManager();                // 0x0067de20

extern const char* kLanguageNames[];          // 0x01569d50
extern const char* kLocaleNames[];            // 0x01569e18

struct cGonzagoSystemCommand : ArgScript::cCommandBase {   // vtable 0x014623b4
    cGonzagoSystemCommand() {}
    virtual void Fn0();
};
struct cLanguageCommand : ArgScript::cCommandBase {        // vtable 0x014635a0, 0xe0 bytes
    ArgScript::cArgumentSpec mSpec;
    bool     mbLanguage;
    uint32_t mValue;
    cLanguageCommand(bool bLanguage) : mSpec(1)
    {
        mbLanguage = bLanguage;
        if (bLanguage)
            mSpec.ConstructSpec("Sets the current language and related locale for the game.",
                                ":language", kLanguageNames, "<languageString:language>",
                                &mValue, "the language", 0);
        else
            mSpec.ConstructSpec("Sets the current locale and related language for the game.",
                                ":locale", kLocaleNames, "<localeString:locale>",
                                &mValue, "the locale", 0);
    }
    virtual void Fn0();
};
struct cSuperPowersCommand : ArgScript::cCommandBase {     // 0xdc, ctor 0x00b5f620
    cSuperPowersCommand(); uint32_t mData[(0xdc - 0x10) / 4];
};
struct cStyleFilter : ArgScript::cCommandBase {            // 0xdc, ctor 0x00b604a0
    cStyleFilter(); uint32_t mData[(0xdc - 0x10) / 4];
};
struct cPauseUIVisibleCommand : ArgScript::cCommandBase {  // 0xd8, ctor 0x00b60350
    cPauseUIVisibleCommand(); uint32_t mData[(0xd8 - 0x10) / 4];
};
struct cAdventureLook : ArgScript::cCommandBase {          // 0xd8, ctor 0x00b60870
    cAdventureLook(); uint32_t mData[(0xd8 - 0x10) / 4];
};
struct cAntiAliasGIF : ArgScript::cCommandBase {           // 0x10, vtable 0x014623cc
    cAntiAliasGIF() {}
    virtual void Fn0();
};
// Simple commands: cCommandBase + cArgumentSpec(1) + a description.
struct cAllSuperPowersCommand : ArgScript::cCommandBase {  // 0xdc, vtable 0x01462bcc
    ArgScript::cArgumentSpec mSpec; uint32_t mExtra;
    cAllSuperPowersCommand() : mSpec(1) { mSpec.ConstructSpec("Unlocks all superweapons for your Civilization type.", 0); }
    virtual void Fn0();
};
struct cCapturePlanetGIF : ArgScript::cCommandBase {       // 0xd8, vtable 0x01462d58
    ArgScript::cArgumentSpec mSpec;
    cCapturePlanetGIF() : mSpec(1) { mSpec.ConstructSpec("Captures a spinning GIF of the planet you are on and dumps to AnimatedAvatars directory", 0); }
    virtual void Fn0();
};
struct cRefillMotivesCommand : ArgScript::cCommandBase {   // 0xdc, vtable 0x01462c14
    ArgScript::cArgumentSpec mSpec; uint32_t mExtra;
    cRefillMotivesCommand() : mSpec(1) { mSpec.ConstructSpec("Replenishes depleted health and other motives.", 0); }
    virtual void Fn0();
};
struct cToolChargeCommand : ArgScript::cCommandBase {      // 0xdc, vtable 0x01462c6c
    ArgScript::cArgumentSpec mSpec; uint32_t mExtra;
    cToolChargeCommand() : mSpec(1) { mSpec.ConstructSpec("unlocks and recharges creation tools while playing in space.", 0); }
    virtual void Fn0();
};
struct cFreeCamCommand : ArgScript::cCommandBase {         // 0xd8, vtable 0x01463464
    ArgScript::cArgumentSpec mSpec;
    cFreeCamCommand() : mSpec(1) { mSpec.ConstructSpec("Toggles free camera mode.", 0); }
    virtual void Fn0();
};
struct cMoreMoneyCommand : ArgScript::cCommandBase {       // 0xd8, vtable 0x014634ac
    ArgScript::cArgumentSpec mSpec;
    cMoreMoneyCommand() : mSpec(1) { mSpec.ConstructSpec("Increases your money in Civilization or Space", 0); }
    virtual void Fn0();
};
}

// ---------------------------------------------------------------------------------------
// Object template DB summarizers
namespace Simulator {
struct ISummarizer { virtual void Fn0(); };
struct cSummarizerBase : ISummarizer {
    uint32_t mField;
    cSummarizerBase() : mField(0) {}
};
struct cGrobModelSummarizer : ISummarizer {     // 0x74, ctor 0x005570d0
    cGrobModelSummarizer(); uint32_t mData[(0x74 - 4) / 4];
};
struct cCellSpeciesSummarizer : cSummarizerBase { // vtable 0x014626f0
    cCellSpeciesSummarizer() {}
    virtual void Fn0();
};
struct cCityMusicSummarizer : cSummarizerBase {   // vtable 0x01462714
    cCityMusicSummarizer() {}
    virtual void Fn0();
};
struct cGameDataSummarizer : ISummarizer {      // 8, ctor 0x005bf380
    cGameDataSummarizer(); uint32_t mField;
};
struct cObjectTemplateDB {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual void SetEnabled(int, bool);                 // +0x18
    virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void AddSummarizer(ISummarizer* pSummarizer);   // +0x7c
};
cObjectTemplateDB* ObjectTemplateDB();          // 0x0067cb40
}

// ---------------------------------------------------------------------------------------
// Sporepedia / asset browser
typedef void (*AssetBrowserCallback)();
void AB_b5df40();   // 0x00b5df40
void AB_dd0c50();   // 0x00dd0c50
void AB_dd0d50();   // 0x00dd0d50
void AB_dd0dc0();   // 0x00dd0dc0
void AB_ef45f0();   // 0x00ef45f0
void AB_ec4250();   // 0x00ec4250
void AB_ecc7d0();   // 0x00ecc7d0
void AB_ef3df0();   // 0x00ef3df0
void AB_eb8460();   // 0x00eb8460

namespace Sporepedia {
struct ILargeAssetView { virtual void Fn0(); };
struct IAssetViewSource { virtual void Fn0(); };
struct cAssetFilterRegistry {
    void AddFilter(uint32_t id, AssetBrowserCallback cb);    // 0x00644510
    void AddFilter2(uint32_t id, AssetBrowserCallback cb);   // 0x00644530
};
struct cAssetBrowser {
    uint32_t mData[0xb8 / 4];
    cAssetFilterRegistry* mpFilters;                         // +0xb8
    void AddKey118(uint32_t id, AssetBrowserCallback cb);    // 0x00646dc0
    void AddKey0F8(uint32_t id, AssetBrowserCallback cb);    // 0x00646e00
    void AddLargeView(uint32_t id, ILargeAssetView* pView);  // 0x00646e40
    void AddViewSource(uint32_t id, IAssetViewSource* pSrc); // 0x00646ec0
    void Finish();                                           // 0x00646ae0
};
cAssetBrowser* AssetBrowser();                  // 0x00401030

struct cCityMusicLargeAssetView : ILargeAssetView {          // 0x40, ctor 0x00ea1900
    cCityMusicLargeAssetView(); uint32_t mData[(0x40 - 4) / 4];
};
struct cUISporepediaPlanetLargeAssetView : ILargeAssetView { // 0x50, ctor 0x00e33de0
    cUISporepediaPlanetLargeAssetView(); uint32_t mData[(0x50 - 4) / 4];
};
struct cRefCountedView { virtual int AddRef(); virtual int Release(); uint32_t mPad[(0x24 - 4) / 4]; };
struct cSPScenarioModeSporepediaLargeAssetView : cRefCountedView, ILargeAssetView {  // 0x108, ctor 0x00ef64e0
    cSPScenarioModeSporepediaLargeAssetView(); uint32_t mData[(0x108 - 0x28) / 4];
};
struct cAdvPrefix { virtual void Fn(); uint32_t mPad[2]; };
struct cSPAdventureCreatureLargeView : cAdvPrefix, ILargeAssetView {  // 0x120, ctor 0x00eb9200
    cSPAdventureCreatureLargeView(); uint32_t mData[(0x120 - 0x10) / 4];
};
struct cViewSrcPrefix { virtual void Fn(); uint32_t mPad[4]; };
struct cViewSourceImpl : cViewSrcPrefix, IAssetViewSource {};
struct cSporepediaGlobals { uint32_t mPad[7]; cViewSourceImpl* mpViewSource; };   // +0x1c
extern cSporepediaGlobals* g_16c7aa4;
}

struct cStarManagerUI { void Setup(); };        // 0x00c2e4e0
cStarManagerUI* GetStarManagerUI();             // 0x00b3d2a0

// ---------------------------------------------------------------------------------------
namespace Simulator {

class cSimulatorSystem : public App::IMessageListener {
public:
    uint32_t field_04;
    uint32_t mnRefCount;                                       // +08
    bool     field_0C;
    bool     mbInitialized;                                    // +0d
    bool     field_0E;
    float    field_10;
    float    field_14;
    uint32_t field_18;
    eastl::intrusive_ptr<cSimContentValidator> mpValidator;    // +1c
    uint32_t field_20[(0x5c - 0x20) / 4];
    eastl::vector<eastl::intrusive_ptr<ISimulatorStrategy> > mSubSystems;  // +5c

    bool Initialize();
};

#define STATIC_REGISTRATION(N) \
    static cSimRegistration<N> sRegistration##N; \
    if (!sRegistration##N.IsRegistered()) sRegistration##N.Register();

// @ 0x00b60d80
bool cSimulatorSystem::Initialize()
{
    if (mbInitialized)
        return true;
    mbInitialized = true;

    mpValidator = SP_NEW("Audio") cSimContentValidator();
    mpValidator->Setup();

    Resource::GetManager()->RegisterFactory(true, new("Audio", 0, 0, 0, 0) Resource::cFactoryCityMusic(), 0);

    STATIC_REGISTRATION(0)
    STATIC_REGISTRATION(1)
    STATIC_REGISTRATION(2)
    STATIC_REGISTRATION(3)
    STATIC_REGISTRATION(4)
    STATIC_REGISTRATION(5)
    STATIC_REGISTRATION(6)
    STATIC_REGISTRATION(7)
    STATIC_REGISTRATION(8)
    STATIC_REGISTRATION(9)
    STATIC_REGISTRATION(10)
    STATIC_REGISTRATION(11)
    STATIC_REGISTRATION(12)
    STATIC_REGISTRATION(13)
    STATIC_REGISTRATION(14)
    STATIC_REGISTRATION(15)
    STATIC_REGISTRATION(16)
    STATIC_REGISTRATION(17)
    STATIC_REGISTRATION(18)
    STATIC_REGISTRATION(19)
    STATIC_REGISTRATION(20)
    STATIC_REGISTRATION(21)

    g_167ea80.Init();
    g_CityGameTuning.Init();
    g_MotiveTuning.Init(0);
    g_BuildingTuning.SetValues();
    GetInitA()->Init();
    GetInitB()->Init();
    GetInitC()->Init();

    g_168df68 = SP_NEW("Simulator") cSimObj1bc();
    GetInitD()->Init();
    g_16e394c = SP_NEW("Simulator") cSimObj30();
    GetInitE()->Init();
    GetSpaceCombatTuning()->Init();
    GetSpaceRelationshipTuning()->Init();
    GetInitF()->Init();

    cSimulatorSubSystems* pSub = GetSubSystems();
    cUITimelineLocal timeline;

    pSub->mpGameTimeManager = SP_NEW("Simulator/SubSystem/GameTimeManager") cGameTimeManager();
    pSub->mpGameTimeManager->Initialize();
    mSubSystems.push_back(pSub->mpGameTimeManager);

    pSub->mpGonzagoPhysics = SP_NEW("Simulator/SubSystem/GonzagoPhysics") cGonzagoPhysics();
    pSub->mpGonzagoPhysics->Initialize();
    mSubSystems.push_back(pSub->mpGonzagoPhysics);

    pSub->mpGameViewManager = SP_NEW("Simulator/SubSystem/GameViewManager") cGameViewManager();
    pSub->mpGameViewManager->Initialize();
    mSubSystems.push_back(pSub->mpGameViewManager);

    pSub->mpPlanetModel = SP_NEW("Simulator/SubSystem/PlanetModel") cPlanetModel();
    pSub->mpPlanetModel->Initialize();
    mSubSystems.push_back(pSub->mpPlanetModel);

    pSub->mpAnimalSpeciesManager = SP_NEW("Simulator/SubSystem/AnimalSpeciesManager") cAnimalSpeciesManager();
    pSub->mpAnimalSpeciesManager->Initialize();
    mSubSystems.push_back(pSub->mpAnimalSpeciesManager);

    pSub->mpFruitManager = SP_NEW("Simulator/SubSystem/FruitManager") cFruitManager();
    pSub->mpFruitManager->Initialize();
    mSubSystems.push_back(pSub->mpFruitManager);

    pSub->mpObstacleManager = SP_NEW("Simulator/SubSystem/ObstacleManager") cObstacleManager();
    pSub->mpObstacleManager->Initialize();
    mSubSystems.push_back(pSub->mpObstacleManager);

    pSub->mpPlantSpeciesManager = SP_NEW("Simulator/SubSystem/PlantSpeciesManager") cPlantSpeciesManager();
    pSub->mpPlantSpeciesManager->Initialize();
    mSubSystems.push_back(pSub->mpPlantSpeciesManager);

    pSub->mpGameInputManager = SP_NEW("Simulator/SubSystem/GameInputManager") cGameInputManager();
    pSub->mpGameInputManager->Initialize();
    mSubSystems.push_back(pSub->mpGameInputManager);

    pSub->mpAStar = SP_NEW("Simulator/SubSystem/AStar") cAStar();
    pSub->mpAStar->Initialize();
    mSubSystems.push_back(pSub->mpAStar);

    pSub->mpGameBehaviorManager = SP_NEW("Simulator/SubSystem/GameBehaviorManager") cGameBehaviorManager();
    pSub->mpGameBehaviorManager->Initialize();
    mSubSystems.push_back(pSub->mpGameBehaviorManager);

    pSub->mpGameNounManager = SP_NEW("Simulator/SubSystem/GameNounManager") cGameNounManager();
    pSub->mpGameNounManager->Initialize();
    mSubSystems.push_back(pSub->mpGameNounManager);

    pSub->mpBundleManager = SP_NEW("Simulator/SubSystem/BundleManager") cBundleManager();
    pSub->mpBundleManager->Initialize();
    mSubSystems.push_back(pSub->mpBundleManager);

    pSub->mpStarManager = SP_NEW("Simulator/SubSystem/StarManager") cStarManager();
    pSub->mpStarManager->Initialize();
    mSubSystems.push_back(pSub->mpStarManager);

    pSub->mpGameModeManager = SP_NEW("Simulator/SubSystem/GameModeManager") cGameModeManager();
    pSub->mpGameModeManager->Initialize();
    mSubSystems.push_back(pSub->mpGameModeManager);

    pSub->mpSimTicker = SP_NEW("Simulator/SubSystem/SimTicker") cSimTicker();
    pSub->mpSimTicker->Initialize();
    mSubSystems.push_back(pSub->mpSimTicker);

    pSub->mpGamePersistenceManager = SP_NEW("Simulator/SubSystem/GamePersistenceManager") cGamePersistenceManager();
    pSub->mpGamePersistenceManager->Initialize();
    mSubSystems.push_back(pSub->mpGamePersistenceManager);

    pSub->mpToolManager = SP_NEW("Simulator/SubSystem/ToolManager") cToolManager();
    pSub->mpToolManager->Initialize();
    mSubSystems.push_back(pSub->mpToolManager);

    pSub->mpCheatObjectManager = SP_NEW("Simulator/SubSystem/CheatObjectManager") cCheatObjectManager();
    pSub->mpCheatObjectManager->Initialize();
    mSubSystems.push_back(pSub->mpCheatObjectManager);

    pSub->mpTerraformingManager = SP_NEW("Simulator/SubSystem/TerraformingManager") cTerraformingManager();
    pSub->mpTerraformingManager->Initialize();
    mSubSystems.push_back(pSub->mpTerraformingManager);

    pSub->mpGamePlantManager = SP_NEW("Simulator/SubSystem/GamePlantManager") cGamePlantManager();
    pSub->mpGamePlantManager->Initialize();
    mSubSystems.push_back(pSub->mpGamePlantManager);

    pSub->mpSpaceGfx = SP_NEW("Simulator/SubSystem/SpaceGfx") cSpaceGfx();
    pSub->mpSpaceGfx->Initialize();
    mSubSystems.push_back(pSub->mpSpaceGfx);

    pSub->mpCommGraphicsManager = SP_NEW("Simulator/SubSystem/CommGraphicsManager") cCommGraphicsManager();
    pSub->mpCommGraphicsManager->Initialize();
    mSubSystems.push_back(pSub->mpCommGraphicsManager);

    pSub->mpCommManager = SP_NEW("Simulator/SubSystem/CommManager") cCommManager();
    pSub->mpCommManager->Initialize();
    mSubSystems.push_back(pSub->mpCommManager);

    pSub->mpLivingUniverse = SP_NEW("Simulator/SubSystem/LivingUniverse") cLivingUniverse();
    pSub->mpLivingUniverse->Initialize();
    mSubSystems.push_back(pSub->mpLivingUniverse);

    pSub->mpSpaceTrading = SP_NEW("Simulator/SubSystem/SpaceTrading") cSpaceTrading();
    pSub->mpSpaceTrading->Initialize();
    mSubSystems.push_back(pSub->mpSpaceTrading);

    pSub->mpUIEventLog = SP_NEW("Simulator/SubSystem/UIEventLog") cUIEventLog();
    pSub->mpUIEventLog->Initialize();
    mSubSystems.push_back(pSub->mpUIEventLog);

    pSub->mpUITimeline = SP_NEW("Simulator/SubSystem/UITimeline") cUITimeline();
    pSub->mpUITimeline->Initialize();
    mSubSystems.push_back(pSub->mpUITimeline);

    pSub->mpCastingManager = SP_NEW("Simulator/SubSystem/CastingManager") cCastingManager();
    pSub->mpCastingManager->Initialize();
    mSubSystems.push_back(pSub->mpCastingManager);

    pSub->mpSpeciesRelationshipManager = SP_NEW("Simulator/SubSystem/SpeciesRelationshipManager") cSpeciesRelationshipManager();
    pSub->mpSpeciesRelationshipManager->Initialize();
    mSubSystems.push_back(pSub->mpSpeciesRelationshipManager);

    pSub->mpPlanetImpostorManager = SP_NEW("Simulator/SubSystem/PlanetImpostorManager") cPlanetImpostorManager();
    pSub->mpPlanetImpostorManager->Initialize();
    mSubSystems.push_back(pSub->mpPlanetImpostorManager);

    pSub->mpBlobShadowManager = SP_NEW("Simulator/SubSystem/BlobShadowManager") cBlobShadowManager();
    pSub->mpBlobShadowManager->Initialize();
    mSubSystems.push_back(pSub->mpBlobShadowManager);

    pSub->mpCinematicManager = SP_NEW("Simulator/SubSystem/CinematicManager") cCinematicManager();
    pSub->mpCinematicManager->Initialize();
    mSubSystems.push_back(pSub->mpCinematicManager);

    pSub->mpEventLogCommManager = SP_NEW("Simulator/SubSystem/EventLogCommManager") cEventLogCommManager();
    pSub->mpEventLogCommManager->Initialize();
    mSubSystems.push_back(pSub->mpEventLogCommManager);

    pSub->mpVignetteManager = SP_NEW("Simulator/SubSystem/VignetteManager") cVignetteManager();
    pSub->mpVignetteManager->Initialize();
    mSubSystems.push_back(pSub->mpVignetteManager);

    pSub->mpNPCCityMusicManager = SP_NEW("Simulator/SubSystem/NPCCityMusicManager") cNPCCityMusicManager();
    pSub->mpNPCCityMusicManager->Initialize();
    mSubSystems.push_back(pSub->mpNPCCityMusicManager);

    pSub->mpUIMissionLogManager = SP_NEW("Simulator/SubSystem/UIMissionLogManager") cUIMissionLogManager();
    pSub->mpUIMissionLogManager->Initialize();
    mSubSystems.push_back(pSub->mpUIMissionLogManager);

    pSub->mpUIAssetDiscoveryManager = SP_NEW("Simulator/SubSystem/UIAssetDiscoveryManager") cUIAssetDiscoveryManager();
    pSub->mpUIAssetDiscoveryManager->Initialize();
    mSubSystems.push_back(pSub->mpUIAssetDiscoveryManager);

    pSub->mpUIMissionCardPanel = SP_NEW("Simulator/SubSystem/UIMissionCardPanel") cUIMissionCardPanel();
    pSub->mpUIMissionCardPanel->Initialize();
    mSubSystems.push_back(pSub->mpUIMissionCardPanel);

    pSub->mpNanoDroneManager = SP_NEW("Simulator/SubSystem/NanoDroneManager") cNanoDroneManager();
    pSub->mpNanoDroneManager->Initialize();
    mSubSystems.push_back(pSub->mpNanoDroneManager);

    pSub->mpScenarioVehicleTicker = SP_NEW("Simulator/SubSystem/ScenarioVehicleTicker") cScenarioVehicleTicker();
    pSub->mpScenarioVehicleTicker->Initialize();
    mSubSystems.push_back(pSub->mpScenarioVehicleTicker);

    GetCellModeStrategy()->Initialize();
    GetCreatureModeStrategy()->Initialize();
    GetTribeModeStrategy()->Initialize();
    GetCivModeStrategy()->Initialize();
    GetSpaceModeStrategy()->Initialize();

    InitMisc_b6eee0();

    App::IMessageNames* pNames = App::GetMessageNames();
    pNames->AddMessageName(0x223f8c5, L"GameCommand", 0);
    pNames->AddMessageName(0x472daaf, L"WaitForGonzagoGameMode", 0);
    App::MessageServer()->AddListener(this, 0x223f8c5);
    App::MessageServer()->AddListener(this, 0x472daaf);
    App::MessageServer()->AddListener(this, 0xf8b1a2af);

    App::CheatManager()->AddDebugCheat(SP_NEW("App/cGonzagoSystemCommand") App::cGonzagoSystemCommand());
    App::CheatManager()->AddDebugCheat(SP_NEW("App/cGonzagoSystemCommand") App::cLanguageCommand(true));
    App::CheatManager()->AddDebugCheat(SP_NEW("App/cGonzagoSystemCommand") App::cLanguageCommand(false));
    App::CheatManager()->AddCheat("setConsequenceTrait", SP_NEW("App/cSuperPowersCommand") App::cSuperPowersCommand(), true);
    App::CheatManager()->AddCheat("unlockSuperWeapons", SP_NEW("App/cAllSuperPowersCommand") App::cAllSuperPowersCommand(), true);
    App::CheatManager()->AddCheat("capturePlanetGIF", SP_NEW("App/cCapturePlanetGIF") App::cCapturePlanetGIF(), false);
    App::CheatManager()->AddCheat("styleFilter", SP_NEW("App/cStyleFilter") App::cStyleFilter(), false);
    App::CheatManager()->AddCheat("antiAliasGIF", SP_NEW("App/cAntiAliasGIF") App::cAntiAliasGIF(), false);
    App::CheatManager()->AddCheat("refillMotives", SP_NEW("App/cRefillMotivesCommand") App::cRefillMotivesCommand(), true);
    App::CheatManager()->AddCheat("spaceCreate", SP_NEW("App/cToolChargeCommand") App::cToolChargeCommand(), true);
    App::CheatManager()->AddCheat("pauseUIVisible", SP_NEW("App/cPauseUIVisibleCommand") App::cPauseUIVisibleCommand(), false);
    App::CheatManager()->AddCheat("freeCam", SP_NEW("App/cFreeCamCommand") App::cFreeCamCommand(), false);
    App::CheatManager()->AddCheat("moreMoney", SP_NEW("App/cMoreMoneyCommand") App::cMoreMoneyCommand(), true);
    App::CheatManager()->AddCheat("adventureLook", SP_NEW("App/cAdventureLook") App::cAdventureLook(), false);

    InitMisc_b5cc80();

    cObjectTemplateDB* pDB = ObjectTemplateDB();
    if (pDB) {
        ObjectTemplateDB()->AddSummarizer(SP_NEW("Simulator/cGrobModelSummarizer") cGrobModelSummarizer());
        ObjectTemplateDB()->AddSummarizer(SP_NEW("Simulator/cCellSpeciesSummarizer") cCellSpeciesSummarizer());
        ObjectTemplateDB()->AddSummarizer(SP_NEW("Simulator/cCityMusicSummarizer") cCityMusicSummarizer());
        ObjectTemplateDB()->AddSummarizer(SP_NEW("Simulator/cGameDataSummarizer") cGameDataSummarizer());
        pDB->SetEnabled(0, true);
    }

    Sporepedia::cAssetBrowser* pBrowser = Sporepedia::AssetBrowser();
    if (pBrowser) {
        Sporepedia::cAssetFilterRegistry* pFilters = pBrowser->mpFilters;
        if (pFilters) {
            pFilters->AddFilter(0x4f684a4, AB_b5df40);
            pFilters->AddFilter(0xf4c9dc5a, AB_dd0c50);
            pFilters->AddFilter(1, AB_dd0d50);
            pFilters->AddFilter(0, AB_dd0dc0);
            pFilters->AddFilter(0xb1b104, AB_ef45f0);
            pFilters->AddFilter(0x366a930d, AB_ec4250);
            pFilters->AddFilter2(0x4178b8e8, AB_ecc7d0);
        }
        pBrowser->AddKey118(0x366a930d, AB_ef3df0);
        pBrowser->AddKey0F8(0x4178b8e8, AB_eb8460);

        pBrowser->AddLargeView(0x4f684a4, SP_NEW("Simulator/cCityMusicLargeAssetView") Sporepedia::cCityMusicLargeAssetView());
        pBrowser->AddLargeView(0xf4c9dc5a, SP_NEW("UI/cUISporepediaPlanetLargeAssetView") Sporepedia::cUISporepediaPlanetLargeAssetView());

        eastl::intrusive_ptr<Sporepedia::cSPScenarioModeSporepediaLargeAssetView> pScenarioView =
            SP_NEW("Simulator/cSPScenarioModeSporepediaLargeAssetView") Sporepedia::cSPScenarioModeSporepediaLargeAssetView();
        pBrowser->AddLargeView(0x24720859, pScenarioView.get());
        pBrowser->AddLargeView(0x20790816, pScenarioView.get());
        pBrowser->AddLargeView(0x27818fe6, pScenarioView.get());
        pBrowser->AddLargeView(0x287adcdc, pScenarioView.get());
        pBrowser->AddLargeView(0xc34c5e14, pScenarioView.get());
        pBrowser->AddLargeView(0xfb734cd1, pScenarioView.get());
        pBrowser->AddLargeView(0x37fd4e0d, pScenarioView.get());
        pBrowser->AddLargeView(0xc422519e, pScenarioView.get());
        pBrowser->AddLargeView(0xb4707f8f, pScenarioView.get());
        pBrowser->AddLargeView(0x25a6ea6e, pScenarioView.get());
        pBrowser->AddLargeView(0xe27ddad4, pScenarioView.get());

        pBrowser->AddLargeView(0x4178b8e8, SP_NEW("UI/cSPAdventureCreatureLargeView") Sporepedia::cSPAdventureCreatureLargeView());
        pBrowser->AddViewSource(0x366a930d, Sporepedia::g_16c7aa4->mpViewSource);
        pBrowser->Finish();
    }

    GetStarManagerUI()->Setup();
    return true;
}

}  // namespace Simulator
