// slice s0063e880: cSPPlayModeSubModePhoto (photo mode of the play-mode UI).
// Module flags: /O2 /MD /Gy /TP (no /arch:SSE, no /EHsc).
#include "s0063e880.h"
#include <stdlib.h>

struct cSPPlayModeSubModeBase2 : cSPPlayModeSubModeBase {};
struct cPhotoMsg;
struct cPhotoAssetManager;
void* GetPhotoAssets();   // 0x0067DD60
struct cSPPlayModeSubModePhoto : cSPPlayModeSubModeBase, IHandler {
    uint32_t mPoseAnimIDs[6];                 // +0x18
    uint32_t mCurrPoseNum;                    // +0x30
    uint32_t mBabyEventIDs[6];                // +0x34
    cSPPlayModeUI* mUI;                       // +0x4C
    cSPPlayModePhotoBrowser mPhotoBrowser;    // +0x50
    Stopwatch mTimerA;                        // +0xF10
    uint32_t mCurrentPhotoID;                 // +0xF28
    AutoRef<IRefCounted> mFlashEffect;        // +0xF2C
    bool mbFlashA;                            // +0xF30
    bool mbFlashB;                            // +0xF31
    uint32_t pad0f34;
    Stopwatch mTimerB;                        // +0xF38
    uint32_t mUnusedF50;                      // +0xF50
    uint32_t mWriteJobCount;                  // +0xF54
    bool mbFlashC;                            // +0xF58
    uint32_t pad0f5c;
    Stopwatch mTimerC;                        // +0xF60
    bool mbFlashD;                            // +0xF78
    uint32_t pad0f7c;
    Stopwatch mTimerD;                        // +0xF80
    int mDialogInProgress;                    // +0xF98
    bool mb0f9c, mb0f9d;
    cAutoHandler mAutoMsgHandler;             // +0xFA0
    eastl::string16 mString;                  // +0xFB4

    cSPPlayModeSubModePhoto();
    virtual ~cSPPlayModeSubModePhoto();
    void FUN_0063f060();
    void SavePhoto(uint16_t a);
    void SavePhotoSimple();
    void Update(uint32_t dt);
    void ShowErrorDialog(uint32_t id, int unused);
    bool IsPhotosWriting(bool arg);
    void CloseSendPhotoWindow();
    bool IsFlashAIdle();
    static void DefaultPathA();
    static void DefaultPathB();
    void Init(void* arg);
    void Shutdown();
    bool HandleKey(uint32_t id, int unused);
    void StartCameraFlash();
};

// @ 0x0063e880
void cSPPlayModeSubModePhoto::Update(uint32_t dt)
{
    if (mbFlashA) {
        Stopwatch* sw = &mTimerA;
        if (0.5f > sw->GetElapsedTimeFloat()) {
            if (!mUI->GetItemVisible(0x46530c8))
                mUI->SetUIGroupVisible(0x46530c8, true);
        } else {
            if (mUI->GetItemVisible(0x46530c8))
                mUI->SetUIGroupVisible(0x46530c8, false);
            if (sw->GetElapsedTimeFloat() > 1.0f)
                sw->Restart();
        }
    }
    if (mbFlashB) {
        Stopwatch* sw = &mTimerB;
        if (sw->GetElapsedTimeFloat() > 0.5f) {
            sw->Stop();
            sw->Reset();
            mbFlashB = false;
            if (mUI && mUI->mbLayoutInit) {
                mUI->SetEnableTakePictureButton(true);
                mUI->SetEnableRecordMovieButton(true);
                if (!GetMovieSystem()->IsRecording()) {
                    mUI->SetEnableNewCreatureButton(true);
                    mUI->FUN_00635350(1, 1);
                }
            }
            mUI->SetUIGroupVisible(0x410cf00, true);
            mUI->SetUIGroupVisible(0x41a30c0, true);
            mUI->SetEditorUIGroupVisible(0x447c040, true);
            mUI->SetEditorUIGroupVisible(0x447c4e8, true);
            if (mUI->IsUIGroupEnabled(0x445ea18))
                mUI->SetUIGroupVisible(0x4463e78, true);
            mUI->SetUIGroupVisible(0x46530c8, false);
            mbFlashA = false;
        }
    }
    if (mbFlashC) {
        Stopwatch* sw = &mTimerC;
        if (0.5f > sw->GetElapsedTimeFloat()) {
            if (!mUI->IsCheckButtonSelected(0x445ea50))
                mUI->SetSelected(0x445ea50, true);
        } else {
            if (mUI->IsCheckButtonSelected(0x445ea50))
                mUI->SetSelected(0x445ea50, false);
            if (sw->GetElapsedTimeFloat() > 1.0f)
                sw->Restart();
        }
    }
    if (mbFlashD) {
        Stopwatch* sw = &mTimerD;
        if (sw->GetElapsedTimeFloat() > 0.5f) {
            mbFlashD = false;
            sw->Stop();
            sw->Reset();
            mPhotoBrowser.ShowImageThumbnail();
        }
    }
    mPhotoBrowser.FUN_00630580(dt);
}

extern char gMsgB[], gMsgC[], gMsgD[];   // 0x01524C24, 0x01524C30, 0x01524C3C

// @ 0x0063eb30
void cSPPlayModeSubModePhoto::ShowErrorDialog(uint32_t id, int unused)
{
    switch (id) {
    case 0x4585f1f:
        BeginProfScope(0, 1)->End();
        ShowMessageBoxEx(gMsgA, gMsgB);
        mDialogInProgress = 8;
        break;
    case 0x4585f49:
        BeginProfScope(0, 1)->End();
        ShowMessageBoxEx(gMsgA, gMsgC);
        mDialogInProgress = 8;
        break;
    }
}

// @ 0x0063eb90
bool cSPPlayModeSubModePhoto::IsPhotosWriting(bool arg)
{
    cString s;
    if (mPhotoBrowser.FUN_006304e0()) {
        BeginProfScope(0, 1)->End();
        ShowMessageBoxEx(gMsgA, gMsgD);
        mDialogInProgress = (arg == false) + 4;
        return true;
    }
    return false;
}

struct IAudioSystemAT {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual int GetValue();     // +0x20
    virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void SetMode(uint32_t id);                                                   // +0x38
    virtual void s15();
    virtual void SetParam(uint32_t id, int v);                                           // +0x40
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void Commit();                                                               // +0x58
};
IAudioSystemAT* GetSystemAT();   // 0x00A206F0

// @ 0x0063ec10
void cSPPlayModeSubModePhoto::CloseSendPhotoWindow()
{
    IAudioSystemAT* at = GetSystemAT();
    int v = at ? at->GetValue() : 0;
    at = GetSystemAT();
    if (at) {
        at->SetMode(0x3475365);
        at->SetParam(0x3475381, 0x2dd795c);
        at->SetParam(0x3475385, v);
        at->Commit();
    }
    IWindow* w = mUI->FindEditorUIWindow(0x3f67620);
    if (w) {
        w->SetFlag(1, 0);
        EndModal(w, 0, 0);
        BeginProfScope(1, 1)->End();
    }
    mPhotoBrowser.FUN_006303a0();
    mDialogInProgress = 0;
}

// @ 0x0063ecf0
bool cSPPlayModeSubModePhoto::IsFlashAIdle() { return !mbFlashA; }

void FUN_009322b0(const wchar_t* p);   // 0x009322B0 (cdecl)
void FUN_00932960(const wchar_t* p);   // 0x00932960 (cdecl)

// @ 0x0063ed00
void cSPPlayModeSubModePhoto::DefaultPathA()
{
    const wchar_t* path = (const wchar_t*)gDialogText;
    ISaveArea* sa = GetSaveArea(0x11ac196);
    if (sa && sa->GetTypeID() == 0x34728492)
        path = sa->GetPath();
    FUN_009322b0(path);
}

// @ 0x0063ed50
void cSPPlayModeSubModePhoto::DefaultPathB()
{
    const wchar_t* path = (const wchar_t*)gDialogText;
    ISaveArea* sa = GetSaveArea(0x11ac196);
    if (sa && sa->GetTypeID() == 0x34728492)
        path = sa->GetPath();
    FUN_00932960(path);
}

namespace eastl {
template <typename ForwardIterator, typename T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
{
    for (; first != last; ++first) {
        if (*first == old_value)
            *first = new_value;
    }
}
template void replace<wchar_t*, wchar_t>(wchar_t*, wchar_t*, const wchar_t&, const wchar_t&);   // 0x0063eda0
}

// @ 0x0063ee30
void cSPPlayModeSubModePhoto::Init(void* arg)
{
    cSPPlayModeSubModeBase::Init(arg);
    mFlashEffect = 0;
    cSPPlayModeUI* ui = *(cSPPlayModeUI**)((char*)arg + 0x1c);
    mUI = ui;
    mPoseAnimIDs[0] = 0x3fd1227;
    mPoseAnimIDs[1] = 0x3fd1214;
    mPoseAnimIDs[2] = 0x3fd11fb;
    mPoseAnimIDs[3] = 0x418b841;
    mPoseAnimIDs[4] = 0x3fd120a;
    mPoseAnimIDs[5] = 0x3fd1203;
    mBabyEventIDs[0] = 0x2949954d;
    mBabyEventIDs[1] = 0xd0c86c9a;
    mBabyEventIDs[2] = 0x89d6008b;
    mBabyEventIDs[3] = 0xc4b6e6e0;
    mBabyEventIDs[4] = 0xc1339ba9;
    mBabyEventIDs[5] = 0x7f034f46;
    mCurrPoseNum = 0;
    pad[1] = *(uint32_t*)((char*)arg + 0x20);
    mPhotoBrowser.Init(mUI);
    mUnusedF50 = 0;
    mWriteJobCount = 0;
    mbFlashA = false;
    mbFlashB = false;
}

// @ 0x0063eef0
void cSPPlayModeSubModePhoto::Shutdown()
{
    mPhotoBrowser.Shutdown();
    IRefCounted* e = mFlashEffect.mpObject;
    if (e) {
        e->Stop(0);
        mFlashEffect = 0;
    }
}

// @ 0x0063ef30
bool cSPPlayModeSubModePhoto::HandleKey(uint32_t id, int unused)
{
    if (id == 0x1b) {
        IWindow* w = mUI->FindEditorUIWindow(0x3f67620);
        if (w && (w->GetFlags() & 1)) {
            CloseSendPhotoWindow();
            return true;
        }
    }
    return false;
}

IRefCounted* __stdcall FUN_00401050(uint32_t id, int a);   // 0x00401050
struct cEffectFactory { IRefCounted* Create(); };          // 0x0045AE10

// @ 0x0063ef70
void cSPPlayModeSubModePhoto::StartCameraFlash()
{
    if (mFlashEffect.mpObject) {
        mFlashEffect.mpObject->Stop(0);
        mFlashEffect = 0;
    }
    mFlashEffect = ((cEffectFactory*)FUN_00401050(0x44ed103, 0))->Create();
    mbFlashD = true;
    if (mTimerD.mnUnits == 1)
        mTimerD.mnStartTime = __rdtsc();
    else {
        int64_t t;
        QueryPerformanceCounter(&t);
        mTimerD.mnStartTime = t;
    }
    mTimerD.mnTotalElapsedTime = 0;
}

// @ 0x0063f060
void cSPPlayModeSubModePhoto::FUN_0063f060()
{
    uint32_t val[2];
    uint32_t zero[2] = {0, 0};
    uint32_t* p = (uint32_t*)pad[2];
    IRangeTarget* t = *(IRangeTarget**)p;
    val[0] = p[5] | p[1];
    val[1] = p[6] | p[2];
    t->SetRange((uint64_t*)val, (uint64_t*)zero, 6);
    p = (uint32_t*)pad[2];
    val[0] = p[5] | p[1];
    val[1] = p[6] | p[2];
    ((IRangeTarget*)(*(void**)(*(char**)&pad[0] + 0x8c)))->SetRange((uint64_t*)val, (uint64_t*)zero, 6);
}

// @ 0x0063f1c0
cSPPlayModeSubModePhoto::cSPPlayModeSubModePhoto()
    : mTimerA(5, false), mFlashEffect(), mbFlashA(false), mbFlashB(false),
      mTimerB(5, false), mUnusedF50(0), mWriteJobCount(0), mbFlashC(false),
      mTimerC(5, false), mbFlashD(false), mTimerD(5, false),
      mDialogInProgress(0), mb0f9c(false), mb0f9d(false)
{
}

// @ 0x0063f2b0
cSPPlayModeSubModePhoto::~cSPPlayModeSubModePhoto()
{
}

// UI message with 32 optional ref-counted slots (8 bytes each from +8) and a presence mask at +0x18
struct cUIParamMessageBase { virtual ~cUIParamMessageBase() {} };
struct cUIParamMessage : cUIParamMessageBase {
    uint32_t pad04;
    struct Slot { IRefCounted* p; uint32_t aux; } slots[32];
    ~cUIParamMessage();
};

// @ 0x0063f0e0
cUIParamMessage::~cUIParamMessage()
{
    uint32_t bit = 1;
    Slot* s = slots;
    for (int i = 32; i; --i, ++s) {
        if (*(uint32_t*)((char*)this + 0x18) & bit) {
            if (s->p)
                s->p->Release();
        }
        bit = _rotl(bit, 1);
    }
}

// four string members at +0xC, +0x1C, +0x2C, +0x3C
struct cFourStrings {
    uint32_t pad[3];
    eastl::string s0, s1, s2, s3;
    ~cFourStrings();
};

// @ 0x0063f350
cFourStrings::~cFourStrings() {}

// ref-counted message with a deleting destructor
struct cMsgBaseA { virtual ~cMsgBaseA() {} virtual int AddRef(); virtual int Release(); int mRefCount; cMsgBaseA() : mRefCount(0) {} };

struct cPhotoMsg : cMsgBaseA {
    uint32_t mId;            // +8
    uint32_t mWidth;         // +0xC
    uint32_t mType;          // +0x10
    uint32_t mField14;       // +0x14
    uint32_t mPhotoID;       // +0x18
    uint32_t mKey1;          // +0x1C
    uint32_t mGlobal;        // +0x20
    uint32_t mPhotoID2;      // +0x24
    eastl::string16 mName;   // +0x28
    cPhotoMsg() {}
};

// @ 0x0063f3e0 (scalar deleting destructor)
// (generated from the class above)

struct cEditorResBaseX { virtual ~cEditorResBaseX() {} };
struct cEditorResBaseY { virtual ~cEditorResBaseY() {} };
struct cEditorBinding : cEditorResBaseX, cEditorResBaseY {
    uint32_t pad[6];
    void* mpData;           // +0x20
    cEditorBinding() : mpData(0) {}
    virtual ~cEditorBinding() { if (mpData) operator delete(mpData); }
};

struct cIDGenerator {
    virtual void s0();
    virtual void Generate(uint32_t* out, uint32_t type, int a, int b, int c, int d);   // +4
};
cIDGenerator* GetIDGenerator();     // 0x0067DE60
struct cMsgDispatcher {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual void Dispatch(uint32_t a, uint32_t b, uint32_t c, cPhotoMsg* msg);   // +0x24
};
cMsgDispatcher* GetMsgDispatcher();   // 0x0067DDB0
int WStr_Format(eastl::string16* dst, const wchar_t* fmt, ...);   // 0x0041E050 (cdecl)
void MakeFileNameValid(const wchar_t* p);                          // 0x00931250 (cdecl)
extern uint32_t gPhotoGlobal;          // 0x01524A10
extern const wchar_t gFmtW[];          // 0x013F5C04
struct cPhotoOwner { char pad[0x8c]; uint32_t f8c; char pad2[0x360 - 0x90]; struct { char pad[0x38]; uint32_t f38; }* p360; };
struct cPhotoCheck { bool FUN_00628940(); };   // 0x00628940

// @ 0x0063f420
void cSPPlayModeSubModePhoto::SavePhoto(uint16_t a)
{
    uint32_t key[3] = {0, 0, 0};
    wchar_t name[0x100];
    if (((cPhotoCheck*)pad[3])->FUN_00628940())
        GetIDGenerator()->Generate(key, 0x46194d0, 1, 0, 0, 0);
    else
        GetIDGenerator()->Generate(key, 0x65ea4ec, 1, 0, 0, 0);
    mCurrentPhotoID = key[0];
    cMsgDispatcher* disp = GetMsgDispatcher();
    cPhotoMsg* msg = new ("Editor", 0, 0, 0, 0) cPhotoMsg();
    if (msg)
        msg->AddRef();
    msg->mId = a;
    msg->mWidth = 0x280;
    msg->mType = 0x3eaed50;
    msg->mField14 = 0;
    msg->mPhotoID = mCurrentPhotoID;
    msg->mKey1 = key[1];
    msg->mGlobal = gPhotoGlobal;
    msg->mPhotoID2 = mCurrentPhotoID;
    MakeFileNameValid(mUI->GetPhotoName(name, 4));
    WStr_Format(&msg->mName, gFmtW, name);
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'!', L'_');
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'@', L'_');
    cPhotoOwner* owner = (cPhotoOwner*)pad[0];
    disp->Dispatch(**(uint32_t**)&pad[2], owner->f8c, owner->p360->f38, msg);
    ++mWriteJobCount;
    msg->Release();
}

struct cSimpleMsg : cMsgBaseA {
    uint32_t mGlobal;        // +8
    uint32_t mPhotoID;       // +0xC
    uint32_t mField10, mField14, mField18;
    uint32_t mPhotoID2;      // +0x1C
    eastl::string16 mName;   // +0x20
    uint32_t mField30, mField34;
    bool mb38, mb39;
    cSimpleMsg() : mField10(0), mField14(0), mField18(0), mField30(0), mField34(0) {}
};
struct cRefCountedAsset { uint32_t pad[2]; volatile long mRefCount; };
struct cPhotoAssetManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual cRefCountedAsset* Lookup(uint32_t a, uint32_t b, uint32_t c);   // +0x20
    virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual void Register(cRefCountedAsset* a);   // +0x68
};
extern "C" long _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// @ 0x0063f5c0
void cSPPlayModeSubModePhoto::SavePhotoSimple()
{
    wchar_t name[0x100];
    cSimpleMsg* msg = new ("Editor", 0, 0, 0, 0) cSimpleMsg();
    cRefCountedAsset* asset = ((cPhotoAssetManager*)GetPhotoAssets())->Lookup(mCurrentPhotoID, gPhotoGlobal, 0);
    _InterlockedExchangeAdd(&asset->mRefCount, 1);
    ((cPhotoAssetManager*)GetPhotoAssets())->Register(asset);
    msg->mPhotoID = mCurrentPhotoID;
    msg->mGlobal = gPhotoGlobal;
    msg->mb39 = true;
    msg->mb38 = false;
    msg->mPhotoID2 = mCurrentPhotoID;
    MakeFileNameValid(mUI->GetPhotoName(name, 4));
    WStr_Format(&msg->mName, gFmtW, name);
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'!', L'_');
    eastl::replace(msg->mName.mpBegin, msg->mName.mpEnd, L'@', L'_');
    cSPPlayModePhotoBrowser* b = &mPhotoBrowser;
    b->FUN_00631df0(msg);
    b->UpdatePhotoCountText();
    mUI->SetUIGroupVisible(0x410cf00, true);
    mUI->SetUIGroupVisible(0x41a30c0, true);
    mUI->SetUIGroupVisible(0x4463e78, true);
    mUI->SetEditorUIGroupVisible(0x447c040, true);
    mUI->SetEditorUIGroupVisible(0x447c4e8, true);
}

// force the cEditorBinding vtable / deleting destructor out
cEditorBinding* MakeBinding() { return new ("Editor", 0, 0, 0, 0) cEditorBinding(); }
