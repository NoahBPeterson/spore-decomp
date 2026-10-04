// Shared declarations for the play-mode UI helpers (0x00634B10..0x00635490).
#pragma once
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int size_t;

void* operator new(size_t, const char*, int, int, int, int);
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

struct IRefCountU {
    virtual int AddRef();
    virtual int Release();
};

// A UI window; only the vtable slots used by this module are named.
struct UIProc;
struct UIWin {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual struct UIProc* QueryProc(uint32_t id);
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual uint32_t GetID();
    virtual void s08();
    virtual void s09();
    virtual uint8_t GetFlags();
    virtual void s0b();
    virtual void s0c();
    virtual void s0d();
    virtual void s0e();
    virtual void s0f();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s1a();
    virtual void s1b();
    virtual void s1c();
    virtual void s1d();
    virtual void s1e();
    virtual void SetFlag(int flag, bool v);
    virtual void SetText(const wchar_t* text);
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s2a();
    virtual void s2b();
    virtual void s2c();
    virtual void s2d();
    virtual void s2e();
    virtual void s2f();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s3a();
    virtual void s3b();
    virtual UIWin* FindChild(uint32_t id, bool recurse);
    virtual void s3d();
    virtual void s3e();
    virtual void s3f();
    virtual void s40();
    virtual void SetTooltip(void* tip);
    virtual void RemoveTooltip(void* tip);
};

struct UIProc {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual UIWin* GetParent();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual uint32_t GetState();
    virtual void s09();
    virtual void SetFlags(uint32_t flags, bool v);
    virtual void s0b();
    virtual void s0c();
    virtual void SetState13(int a, int b);
};

struct UIObjVec {
    UIWin** mpBegin;
    UIWin** mpEnd;
};

struct cSPUILayout {
    uint32_t pad[6];
    cSPUILayout();                                   // 0x00810000
    UIWin* FindWindowByID(uint32_t id, bool recurse);   // 0x008105b0
    UIObjVec* GetObjects();                          // 0x008100c0
};

struct cSPEditorNaming {
    void SetTagField(uint32_t v);                    // 0x005bfc90
};
struct cSPEditorUI {
    UIWin* FindWindowByID(uint32_t id);              // 0x005dc310
    void DoCommand(uint32_t cmd);                    // 0x005dfd00
    void EnableUIButton(uint32_t id, uint32_t v);    // 0x005dc610
    void Show();                                     // 0x005dd070
    void FUN_005de690(uint32_t a, uint32_t b);       // 0x005de690
};
struct FxController;
struct cAppMode {
    FxController* FUN_00572400();                    // 0x00572400
    uint32_t pad0[0x78 / 4];
    cSPEditorUI* mEditorUI;                          // +0x78
    uint32_t pad1[(0x98 - 0x7c) / 4];
    IRefCountU* mObj98;                              // +0x98
    uint32_t pad2[(0x358 - 0x9c) / 4];
    cSPEditorNaming* mNaming;                        // +0x358
};

struct StopwatchU {
    uint32_t pad[7];
    StopwatchU(int units, int start);                // 0x0093a560
};

struct IWinProcU {
    virtual void w0();
    virtual void w1();
};
struct RefCountBaseU {
    virtual void r0();
    int mRefCount;
    RefCountBaseU() : mRefCount(0) {}
};

struct cSPPlayModeUI : IWinProcU, RefCountBaseU {
    cAppMode* mApp;            // +0x0c
    void* mPlayMode;           // +0x10
    cSPUILayout mLayout;       // +0x14
    cSPUILayout mLayout2;      // +0x2c
    uint8_t mFlag44;           // +0x44
    uint8_t mFlag45;           // +0x45
    StopwatchU mTimer;         // +0x48
    uint32_t mField64;         // +0x64
    UIWin* mField68;           // +0x68

    cSPPlayModeUI();
    void AttachWinProc();
    UIWin* FindPlayModeUIWindow(uint32_t id);
    UIWin* FindEditorUIWindow(uint32_t id);
    int FUN_00634e50();
    uint8_t IsItemVisible(uint32_t id);
    void SetHighlight(uint32_t id, bool v);
    void SetSelected(uint32_t id, bool v);
    void SetEnabled(uint32_t id, bool v);
    void SetEditorUIEnabled(uint32_t id, bool v);
    void SetHideOut(uint32_t id, bool v);
    void SetEditorText(uint32_t id, const wchar_t** text);
    void ShowToolTip(uint32_t id, uint32_t a, uint32_t b, struct cSPUITooltipWinProc* existing, float* pos);
    void ShowEditorUIToolTip(uint32_t id, uint32_t a, uint32_t b, struct cSPUITooltipWinProc* existing, float* pos);
    void RemoveTooltip(uint32_t id, void* tip);
    void DoCommand103();
    void DoCommand102();
    void SetPrompt(uint32_t v);
    void FUN_00635350(uint32_t a, uint32_t b);
    void ShowEditor();
    void ToggleNameAndDescribe(bool v);
    void SetTagField(uint32_t v);
    void SetSendEmailDialogVisibility(bool v);
    void UpdateButtonEffects(int unused);
};
extern float gBtnFx0, gBtnFx1, gBtnFx2, gBtnFx3;     // 0x013f9328, 0x013f9324, 0x013ef53c, 0x013fe744
extern float gTipDefault0, gTipDefault1;             // 0x01486110, 0x013f6ad8
struct FxController {
    void SetScaleA(float v);    // 0x00625270
    void SetScaleB(float v);    // 0x006252a0
};
struct UIHelperObj { void FUN_0067c420(); };
UIHelperObj* __stdcall FUN_0067cac0(int a, int b);
struct WinMgrHandler { void FUN_00802a30(int v); };
struct WinMgrOwner { uint32_t pad[0x2d8 / 4]; WinMgrHandler* mHandler; };
struct WinMgr { virtual void w0(); virtual void* GetCurrent(); };
WinMgr* WindowManager();
void BeginModal(UIWin* w, int a, int b);
void EndModal(UIWin* w, int a, int b);

// ---- strings used by the tooltips -------------------------------------------
struct cString {
    uint32_t pad[5];
    cString();                                                   // 0x006b5060
    ~cString();                                                  // 0x006b5240
    void Load(uint32_t id, uint32_t a, uint32_t b);              // 0x006b54b0
    const wchar_t* Format(float* pos, int a, const wchar_t* fmt, int b);   // 0x006b55c0
    const wchar_t* Format2(int len, int flag);                   // 0x006b55c0
};
struct cSPUITooltipWinProc : IRefCountU {
    uint32_t pad[0x68 / 4 - 1];
    cSPUITooltipWinProc(const wchar_t* cls, uint32_t id, const wchar_t* text);   // 0x00835e30
    void SetText(const wchar_t* t);                              // 0x00835ed0
};
void* FUN_009512c0();
void* FUN_009512d0(size_t size, int align, const char* name, void* alloc);
