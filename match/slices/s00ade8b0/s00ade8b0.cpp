// Slice s00ade8b0 -- SP::cCinematicManager::Initialize (cGonzagoSubsystem slot 2, entered with
// `this` = the cGonzagoSubsystem subobject at +4). Registers the 33 cinematic ArgScript
// commands, the message handlers, creates the tutorial text panel and the viewer copy, loads
// the cinematic scripts, and picks the English-locale effects setting.
// Built /O2 /MD /Gy /TP /GS- (no EH frame for the locale string local, no /GS cookie).
// Layout: ModAPI Simulator::cCinematicManager (IMessageListener + cStrategy) and the 2008 PDB
// SP::cCinematicManager (IHandlerRC + cGonzagoSubsystem); retail is shifted +4 after +0x10c.
typedef unsigned int u32;

void* __cdecl operator_new(unsigned, const char*, int, int, int, int);   // 0xf473a0
inline void* operator new(unsigned n, const char* name, int a, int b, int c, int d) {
    return operator_new(n, name, a, b, c, d);
}
inline void operator delete(void*, const char*, int, int, int, int) {}
void __cdecl operator_delete_arr(void*);                                // 0xf47380 (operator delete[])

// ---- ArgScript commands --------------------------------------------------------------
namespace ArgScript {
struct cCommandBase {
    int mData[3];
    cCommandBase();                                                     // 0x83c800
    virtual ~cCommandBase() {}
};
}

#define CINEMATIC_COMMAND(Name) \
    struct Name : ArgScript::cCommandBase { virtual void ParseLine(); }

namespace Cinematic {
CINEMATIC_COMMAND(cLetterboxCmd);
CINEMATIC_COMMAND(cStartCameraCmd);
CINEMATIC_COMMAND(cPathCameraCmd);
CINEMATIC_COMMAND(cStopCameraCmd);
CINEMATIC_COMMAND(cTextCmd);
CINEMATIC_COMMAND(cTextUpperCmd);
CINEMATIC_COMMAND(cTextFromCodeCmd);
CINEMATIC_COMMAND(cScrollingTextCmd);
CINEMATIC_COMMAND(cStartEffectCmd);
CINEMATIC_COMMAND(cStopEffectCmd);
CINEMATIC_COMMAND(cSendMessageCmd);
CINEMATIC_COMMAND(cWaitCmd);
CINEMATIC_COMMAND(cStateDurationCmd);
CINEMATIC_COMMAND(cNextStateCmd);
CINEMATIC_COMMAND(cNextStateIfCmd);
CINEMATIC_COMMAND(cPauseGameCmd);
CINEMATIC_COMMAND(cUnpauseGameCmd);
CINEMATIC_COMMAND(cLetAIRunCmd);
CINEMATIC_COMMAND(cStartSoundCmd);
CINEMATIC_COMMAND(cStopSoundCmd);
CINEMATIC_COMMAND(cMixEventCmd);
CINEMATIC_COMMAND(cShowTimelineCmd);
CINEMATIC_COMMAND(cDisableEscExitCmd);
CINEMATIC_COMMAND(cEnableEscExitCmd);
CINEMATIC_COMMAND(cSetExitStateCmd);
CINEMATIC_COMMAND(cDisableDuringDemoCmd);
CINEMATIC_COMMAND(cPreserveCinematicCamViewCmd);
CINEMATIC_COMMAND(cShowUICmd);
CINEMATIC_COMMAND(cClearAreaAroundObjectCmd);
CINEMATIC_COMMAND(cBlackScreenCmd);
CINEMATIC_COMMAND(cAlphaObstaclesCmd);
CINEMATIC_COMMAND(cStopCinematicCmd);
CINEMATIC_COMMAND(cSwitchToExitStateCmd);

// Command keywords (const char* globals 0x15663f4..0x156647c).
extern const char* kLetterbox;                 // "letterbox"
extern const char* kStartCamera;               // "startCamera"
extern const char* kPathCamera;                // "pathCamera"
extern const char* kStopCamera;                // "stopCamera"
extern const char* kText;                      // "text"
extern const char* kTextUpper;                 // "textUpper"
extern const char* kTextFromCode;              // "textFromCode"
extern const char* kScrollingText;             // "scrollingText"
extern const char* kStartEffect;               // "startEffect"
extern const char* kStopEffect;                // "stopEffect"
extern const char* kSendMessage;               // "sendMessage"
extern const char* kStateDuration;             // "stateDuration"
extern const char* kWait;                      // "wait"
extern const char* kNextState;                 // "nextState"
extern const char* kNextStateIf;               // "nextStateIf"
extern const char* kPauseGame;                 // "pauseGame"
extern const char* kUnpauseGame;               // "unpauseGame"
extern const char* kLetAIRun;                  // "letAIRun"
extern const char* kStartSound;                // "startSound"
extern const char* kStopSound;                 // "stopSound"
extern const char* kMixEvent;                  // "mixEvent"
extern const char* kShowTimeline;              // "showTimeline"
extern const char* kDisableEscExit;            // "disableEscExit"
extern const char* kEnableEscExit;             // "enableEscExit"
extern const char* kSetExitState;              // "setExitState"
extern const char* kDisableDuringDemo;         // "disableDuringDemo"
extern const char* kPreserveCinematicCamView;  // "preserveCinematicCamView"
extern const char* kShowUI;                    // "showUI"
extern const char* kClearAreaAroundObject;     // "clearAreaAroundObject"
extern const char* kBlackScreen;               // "blackScreen"
extern const char* kAlphaObstacles;            // "alphaObstacles"
extern const char* kStopCinematic;             // "stopCinematic"
extern const char* kSwitchToExitState;         // "switchToExitState"

void __cdecl InitCinematicActions();           // 0xad6f40
}

// ---- collaborators -------------------------------------------------------------------
namespace EA { namespace Messaging {
struct IHandler {
    virtual bool HandleMessage(u32 messageID, void* msg) = 0;
};
struct IHandlerRC : IHandler {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~IHandlerRC() {}
};
struct IMessageServer {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void AddListener(IHandler* handler, u32 messageID);   // 0x20
    virtual void AddHandler(IHandler* handler, u32 messageID);    // 0x24
};
}}

// Objects whose vtable has AddRef/Release at slots 2/3 (camera manager, tutorial text).
struct RC23 {
    virtual void v0(); virtual void v1();
    virtual int AddRef();     // 0x08
    virtual int Release();    // 0x0c
};
// Objects with AddRef/Release at slots 0/1.
struct RC01 {
    virtual int AddRef();     // 0x00
    virtual int Release();    // 0x04
};

struct cICameraManager : RC23 {};
struct cAppStateManager : RC01 {
    virtual void v2(); virtual void v3();
    virtual void Init(int);   // 0x10
};

struct cTextWindow {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
    virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void w28(); virtual void w29(); virtual void w30();
    virtual void SetFlag(int flag, int value);   // 0x7c
};
struct cSPTutorialText : RC23 {
    int pad04[0xb];
    cTextWindow* mWindow0;    // +0x30
    cTextWindow* mWindow1;    // +0x34
    int pad38[8];
    cSPTutorialText();        // 0xad8280
    void Setup();             // 0xad8300
    void SetVisible(int);     // 0xad87d0
};

struct cViewer {
    u32 pad[0x174 / 4];
    cViewer();                // 0x7c3f70
    void Init(int);           // 0x7c4dd0
};

struct cSPApp {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13();
    virtual u32 GetCurrentModeID();               // 0x38
    virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18();
    virtual void a19();
    virtual cICameraManager* GetCameraManager();  // 0x50
};

struct WString {   // the locale's (begin, end) pair
    const wchar_t* mpBegin;
    const wchar_t* mpEnd;
};
struct cLocaleManager {
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3(); virtual void l4();
    virtual const WString* GetLocale();           // 0x14
};
struct cEffectsManager {
    virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
    virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
    virtual void e08(); virtual void e09(); virtual void e10(); virtual void e11();
    virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
    virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
    virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23();
    virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27();
    virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31();
    virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35();
    virtual void e36(); virtual void e37();
    virtual void SetOption(int option, int value);   // 0x98
};

namespace SP {
cSPApp* __cdecl App();                                  // 0x67dd10
EA::Messaging::IMessageServer* __cdecl MessageServer(); // 0x67dcc0
cEffectsManager* __cdecl EffectsManager();              // 0x67ddd0
cLocaleManager* __cdecl LocaleManager();                // 0x67de40
cAppStateManager* __cdecl AppStateManager();            // 0x7e57c0
}

// eastl::fixed_string<wchar_t, 16, true>
struct string16f {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocName;
    wchar_t* mpPoolBegin;
    wchar_t  mBuffer[16];

    string16f(const WString& x) {
        mpPoolBegin = mBuffer;
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + 16;
        *mpBegin = 0;
        append(x.mpBegin, x.mpEnd);
    }
    ~string16f() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != mpPoolBegin)
            operator_delete_arr(mpBegin);
    }
    void append(const wchar_t* first, const wchar_t* last);   // 0x68cc10
};
bool __cdecl operator==(const string16f& a, const wchar_t* b);   // 0x6ab760

// AutoRefCount assignment.
template <class T> struct AutoRef {
    T* mp;
    AutoRef& operator=(T* p) {
        if (p != mp) {
            T* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};

struct AutoHandler {
    EA::Messaging::IMessageServer* mpServer;
    EA::Messaging::IHandler* mpHandler;
    const u32* mpIdArray;
    u32 mnIdArrayCount;
    int mnPriority;

    void Init(EA::Messaging::IMessageServer* server, EA::Messaging::IHandler* handler,
              const u32* ids, u32 count) {
        mpServer = server;
        mpHandler = handler;
        mpIdArray = ids;
        mnIdArrayCount = count;
        mnPriority = 0;
        if (server && handler)
            for (u32 i = 0; i < count; i++)
                server->AddHandler(handler, ids[i]);
    }
};

extern const u32 kCinematicMessages[0x27];   // 0x145b238

namespace SP {
struct cIGonzagoSubsystem {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void Initialize() = 0;
};
struct cGonzagoSubsystem : cIGonzagoSubsystem {
    u32 mBase[6];   // RefCountTemplate vptr, refcount, mode/transition state (size 0x1c)
};

class cCinematicManager : public EA::Messaging::IHandlerRC, public cGonzagoSubsystem {
public:
    virtual void AddCommand(const char* keyword, ArgScript::cCommandBase* cmd);   // 0x10
    virtual void Initialize();
    void LoadScripts();                                                           // 0xaddd20

    void* mGetReferencedObjectDataCallback;  // +0x20
    float mTimer;                            // +0x24
    bool mLetAIRun;                          // +0x28
    bool mLetAvatarAIRun;                    // +0x29
    bool mCameraInited;                      // +0x2a
    bool mEscExitDisabled;                   // +0x2b
    int mStatus;                             // +0x2c
    float mDuration;                         // +0x30
    float mWaitSecs;                         // +0x34
    bool mWaiting;                           // +0x38
    bool mUseRealTime;                       // +0x39
    bool mWaitingForContinue;                // +0x3a
    bool mWaitingForButton;                  // +0x3b
    bool mForceStateSwitch;                  // +0x3c
    cViewer* mViewerCopy;                    // +0x40
    AutoRef<cSPTutorialText> mTextPanel;     // +0x44
    AutoHandler mAutoMessages;               // +0x48
    u32 pad5c[(0x13c - 0x5c) / 4];
    AutoRef<cICameraManager> mCameraManager;   // +0x13c
    AutoRef<cAppStateManager> mStateManager;   // +0x140
    u32 pad144[5];
    u32 mCurrentModeID;                        // +0x158
};

// @ 0x00ade8b0
void cCinematicManager::Initialize()
{
    using namespace Cinematic;

    mCameraManager = App()->GetCameraManager();
    mStateManager = AppStateManager();
    mStateManager->Init(0);

    AddCommand(kLetterbox, new("Simulator", 0, 0, 0, 0) cLetterboxCmd());
    AddCommand(kStartCamera, new("Simulator", 0, 0, 0, 0) cStartCameraCmd());
    AddCommand(kPathCamera, new("Simulator", 0, 0, 0, 0) cPathCameraCmd());
    AddCommand(kStopCamera, new("Simulator", 0, 0, 0, 0) cStopCameraCmd());
    AddCommand(kText, new("Simulator", 0, 0, 0, 0) cTextCmd());
    AddCommand(kTextUpper, new("Simulator", 0, 0, 0, 0) cTextUpperCmd());
    AddCommand(kTextFromCode, new("Simulator", 0, 0, 0, 0) cTextFromCodeCmd());
    AddCommand(kScrollingText, new("Simulator", 0, 0, 0, 0) cScrollingTextCmd());
    AddCommand(kStartEffect, new("Simulator", 0, 0, 0, 0) cStartEffectCmd());
    AddCommand(kStopEffect, new("Simulator", 0, 0, 0, 0) cStopEffectCmd());
    AddCommand(kSendMessage, new("Simulator", 0, 0, 0, 0) cSendMessageCmd());
    AddCommand(kWait, new("Simulator", 0, 0, 0, 0) cWaitCmd());
    AddCommand(kStateDuration, new("Simulator", 0, 0, 0, 0) cStateDurationCmd());
    AddCommand(kNextState, new("Simulator", 0, 0, 0, 0) cNextStateCmd());
    AddCommand(kNextStateIf, new("Simulator", 0, 0, 0, 0) cNextStateIfCmd());
    AddCommand(kPauseGame, new("Simulator", 0, 0, 0, 0) cPauseGameCmd());
    AddCommand(kUnpauseGame, new("Simulator", 0, 0, 0, 0) cUnpauseGameCmd());
    AddCommand(kLetAIRun, new("Simulator", 0, 0, 0, 0) cLetAIRunCmd());
    AddCommand(kStartSound, new("Simulator", 0, 0, 0, 0) cStartSoundCmd());
    AddCommand(kStopSound, new("Simulator", 0, 0, 0, 0) cStopSoundCmd());
    AddCommand(kMixEvent, new("Simulator", 0, 0, 0, 0) cMixEventCmd());
    AddCommand(kShowTimeline, new("Simulator", 0, 0, 0, 0) cShowTimelineCmd());
    AddCommand(kDisableEscExit, new("Simulator", 0, 0, 0, 0) cDisableEscExitCmd());
    AddCommand(kEnableEscExit, new("Simulator", 0, 0, 0, 0) cEnableEscExitCmd());
    AddCommand(kSetExitState, new("Simulator", 0, 0, 0, 0) cSetExitStateCmd());
    AddCommand(kDisableDuringDemo, new("Simulator", 0, 0, 0, 0) cDisableDuringDemoCmd());
    AddCommand(kPreserveCinematicCamView, new("Simulator", 0, 0, 0, 0) cPreserveCinematicCamViewCmd());
    AddCommand(kShowUI, new("Simulator", 0, 0, 0, 0) cShowUICmd());
    AddCommand(kClearAreaAroundObject, new("Simulator", 0, 0, 0, 0) cClearAreaAroundObjectCmd());
    AddCommand(kBlackScreen, new("Simulator", 0, 0, 0, 0) cBlackScreenCmd());
    AddCommand(kAlphaObstacles, new("Simulator", 0, 0, 0, 0) cAlphaObstaclesCmd());
    AddCommand(kStopCinematic, new("Simulator", 0, 0, 0, 0) cStopCinematicCmd());
    AddCommand(kSwitchToExitState, new("Simulator", 0, 0, 0, 0) cSwitchToExitStateCmd());

    InitCinematicActions();

    mAutoMessages.Init(SP::MessageServer(), this, kCinematicMessages, 0x27);
    SP::MessageServer()->AddListener(this, 0x2319915);
    SP::MessageServer()->AddListener(this, 0xe11331);
    SP::MessageServer()->AddListener(this, 0x2800a7f);

    mTextPanel = new("Simulator", 0, 0, 0, 0) cSPTutorialText();
    if (mTextPanel) {
        mTextPanel->Setup();
        mTextPanel->SetVisible(0);
        cSPTutorialText* text = mTextPanel;
        text->mWindow0->SetFlag(1, 0);
        text->mWindow1->SetFlag(1, 0);
    }

    mViewerCopy = new("Simulator", 0, 0, 0, 0) cViewer();
    mViewerCopy->Init(0);

    LoadScripts();
    mCameraInited = false;
    mCurrentModeID = App()->GetCurrentModeID();

    string16f locale(*LocaleManager()->GetLocale());
    if (locale == L"en-us" || locale == L"en-gb")
        EffectsManager()->SetOption(4, 1);
    else
        EffectsManager()->SetOption(4, 0);
}
}
