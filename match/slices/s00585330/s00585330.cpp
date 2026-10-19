// slice s00585330 — editor input dispatch helpers + stubs.
#include "types.h"

// ---- callee / data stubs (real address in comment) --------------------------
struct cSPEditorBlock;
struct cEditorLaunchData;

struct cLocalInputState {
    void OnKeyDown(int a, int b);   // 0x00697a50
    void OnKeyUp(int a, int b);     // 0x00697a80
    uint32_t mKeys[8];              // +0x00
    uint32_t mModifiers;            // +0x20
    unsigned char mMouseButtons[5]; // +0x24
    char pad29[3];
    float mMouseX;                  // +0x2c
    float mMouseY;                  // +0x30
    uint32_t mDragButton;           // +0x34
    float mMouseStartX;             // +0x38
    float mMouseStartY;             // +0x3c
    uint32_t mMouseDownModifiers;   // +0x40
    uint32_t mMouseWheelDelta;      // +0x44
};

struct cSPEditorAnimatedEventInfo {
    virtual void vf0();
    virtual int  AddRef();
    char pad04[8];
    uint32_t mAnimatedCreatureID;   // +0xc
    void*    mSourceBlock;          // +0x10
    void*    mpSourceModel;         // +0x14
    uint32_t mEvent;                // +0x18
    char pad1c[4];
    float    mDelayTime;            // +0x20
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
};

struct cSPEditorSkinManager {
    void* GetSkin(int id);          // 0x004c49e0
};
struct cSPPaletteUI {
    bool IsPaintByNumber();         // 0x005ca920
};
struct cSPEditorAnimatedCreatureManager {
    void AddDelayedEvent(AutoRefCount<cSPEditorAnimatedEventInfo> info); // 0x0059cb80
    bool HandleAnimatedEvent(cSPEditorAnimatedEventInfo* info);          // 0x0059d300
    bool IsAnimationDone(uint32_t id);                                   // 0x0059cdb0
    void RemoveCreature(uint32_t id);                                    // 0x0059c6e0
};
struct cRefObj {
    void Method();                      // 0x004ad330
};
struct cTexObj {
    void Method();                      // 0x004c4eb0
};
struct cSPEditorBlock {
    char pad00[0x33c];
    cSPEditorBlock* mpParent;           // +0x33c
    char pad340[0xdc8 - 0x340];
    uint32_t mFlagsDC8;                 // +0xdc8
    uint32_t mFlagsDCC;                 // +0xdcc
};
struct cSPEditorHandle {
    cSPEditorBlock* GetEditorBlock();   // 0x0047e6c0
};
struct cRayObj {
    void Method();                      // 0x007c4510
};
extern "C" void* App();                                        // 0x0067dd10
extern "C" void* ModelManager();                               // 0x0067dd80
extern "C" bool FUN_00435c80(cSPEditorBlock* b);               // 0x00435c80
extern "C" void FUN_00448d60(cSPEditorBlock* b);               // 0x00448d60
extern "C" cSPEditorBlock* InterfaceCast(void** p);            // 0x004aa2a0
struct cPropertyList {
    bool GetDescription(uint32_t id);   // 0x006a25a0
};
struct cBlk {
    bool B780();                        // 0x0044b780
};
struct cDevGlobal {
    void Method();                      // 0x0067c830
};
struct cObjA {
    void* Get();                        // 0x00801920
};
struct cObjB {
    void Hide();                        // 0x005ed6c0
};

// globals (addresses in comments)
extern void* g_15fd918;                 // 0x015fd918
extern float g_k1485378;                // 0x01485378
extern float g_k13ec480;                // 0x013ec480

// cdecl helpers
extern "C" float CalculateModelSize(void* model);                             // 0x0048ca10
extern "C" void  RecordEvent4(uint32_t a, uint32_t b, float c, uint32_t d);   // 0x00435f40
extern "C" bool  FUN_004a0ac0(void* model);                                   // 0x004a0ac0
extern "C" void* __stdcall FUN_0067cac0(uint32_t id);                         // 0x0067cac0
extern "C" void* WindowManager();                                             // 0x0067caa0
extern "C" int*  GetSetting6();                                               // 0x00401060
extern "C" void* FUN_00401020();                                              // 0x00401020

struct cAppModeEditorBase {
    char pad0[0x28];
    float mX;                        // +0x28
    float mY;                        // +0x2c
    int mCurrentMouseDown;           // +0x30
    char pad34[0x3c - 0x34];
    uint32_t mControlModifierMode;   // +0x3c
    uint32_t mEyeDropperModiferMode; // +0x40
    uint32_t mModelValidity0;        // +0x44
    char pad48[0x20];
    float mIdleTarget;               // +0x68
    char pad6c[0xc];
    void* mpDevUI;                   // +0x78
    void* mLightingWorld;            // +0x7c
    char pad80[4];
    void* mpSaveModelWorld;          // +0x84
    char pad88[0x10];
    void* mpEditorSaveModel;         // +0x98
    void* mpPedastalModel;           // +0x9c
    char padA0[0x2c];
    void* mpManipulatedBlock;        // +0xcc
    char padD0[4];
    void* mpPreviousSelectedBlock;   // +0xd4
    char padD8[0xc];
    void* mpTorsoHandle;             // +0xe4
    char padE8[0x10];
    cLocalInputState mInput;         // +0xf8 (size 0x48)
    char pad140[3];
    uint8_t mFlag143;                // +0x143
    char pad144[4];
    void* mpActiveManipulator;       // +0x148
    char pad14c[4];
    void* mpSkinManager;             // +0x150
    void* mpTextureFactory;          // +0x154
    char pad158[0x74];
    void* mpLaunchData;              // +0x1cc
    char pad1d0[0x3e];
    uint8_t mByte20e;                // +0x20e
    char pad20f[0xa6];
    uint8_t mIsSkinAllowed;          // +0x2b5
    char pad2b6[0x3e];
    uint8_t mBudgetFlag0;            // +0x2f4
    uint8_t mBudgetFlag1;            // +0x2f5
    char pad2f6[0x26];
    int mQueuedAnim;                 // +0x31c
    char pad320[0x40];
    void* mpAnimCreatureManager;     // +0x360
    uint32_t mAnimatingCreatureID;   // +0x364
    uint32_t mAnimThumbID;           // +0x368
    char pad36c[0x19];
    uint8_t mbModelBalanced;         // +0x385
    char pad386[6];
    uint32_t mSaveInProgress;        // +0x38c
    char pad390[7];
    uint8_t mFlag397;                // +0x397
    char pad398[0x2c];
    void* mpPaintCategoriesUI;       // +0x3c4
    char pad3c8[0xaa];
    uint8_t mFlag472;                // +0x472
    char pad473[1];
    float mFloat474;                 // +0x474
    char pad478[8];
    float mFloat480;                 // +0x480
    float mFloat484;                 // +0x484
    char pad488[4];
    void* mpBlock48c;                // +0x48c
    void* mpHandle490;               // +0x490
    char pad494[0x1d];
    uint8_t mFlag4b1;                // +0x4b1
    char pad4b2[0x22];
    uint8_t mFlag4d4;                // +0x4d4
    char pad4d5[3];
    void* mpConfigData;              // +0x4d8
    char pad4dc[0x2c];
    struct ConfigEntry { void* p; char pad[16]; } mConfigData[6]; // +0x508

    cLocalInputState* Input() { return &mInput; }

    void FUN_00585830(int a, int b);
    void FUN_00585860(int a, int b);
    bool OnKeyUp(uint32_t key, uint32_t mods);          // 0x00585890
    bool HandleAnimatedEvent(cSPEditorAnimatedEventInfo* info); // 0x00585330
    void SetModeModifiers();                            // 0x005855b0
    void SetEyeDropperMode(int mode);                   // 0x005857c0
    bool OnMouseWheel(int a, float b, float c, int d, char e);  // 0x005858f0
    bool OnMouseWheelThunk(int a, float b, float c, int d);     // 0x00585d10
    void FUN_00585c10();                                        // 0x00585c10

    // callees (addresses in comments)
    void SetSoundBlockAdded(void* block);              // 0x00577130
    void SetSoundBlockRemoved(void* block);            // 0x005771f0
    void ShowCreature();                               // 0x00573390
    void HideCreature();                               // 0x00573330
    int  GetCurrentConfig();                           // 0x00576140
    bool RunSkinPaintOnEditorModel(int a, void* b);    // 0x00582fe0
    void FUN_0057e340(int a);                          // 0x0057e340
    void FUN_00572330(void* block);                    // 0x00572330
    void FUN_005820a0();                               // 0x005820a0
    void FUN_0057c530(uint32_t a, bool b);             // 0x0057c530
    void SetModelLocked(bool b);                       // 0x00573780
    void ShowBlockAbilities(void* block);              // 0x00573520
    bool OnBlockWheel(void* block, void* handle, int a); // 0x00582250
    bool HasId(uint32_t id);                           // 0x005740e0
    void FUN_0057e220(float f1, float f2, void* block, void* handle); // 0x0057e220
    void SetActiveBlock(void* block, int a);           // 0x00573c00
};

// @ 0x00585830
void cAppModeEditorBase::FUN_00585830(int a, int b)
{
    Input()->OnKeyDown(a, b);
    SetModeModifiers();
}

// @ 0x00585860
void cAppModeEditorBase::FUN_00585860(int a, int b)
{
    Input()->OnKeyUp(a, b);
    SetModeModifiers();
}

// @ 0x00585890
bool cAppModeEditorBase::OnKeyUp(uint32_t key, uint32_t mods)
{
    Input()->OnKeyUp(key, mods);
    SetModeModifiers();
    if (mQueuedAnim == 2) {
        typedef void (__thiscall *Fn)(void*, uint32_t, uint32_t);
        Fn fn = *(Fn*)(*(char**)mLightingWorld + 0x20);
        fn(mLightingWorld, key, mods);
    }
    SetModeModifiers();
    if (key > 0xf) {
        if (key < 0x13)
            mCurrentMouseDown = mods;
    }
    return false;
}

// @ 0x00585330
bool cAppModeEditorBase::HandleAnimatedEvent(cSPEditorAnimatedEventInfo* info)
{
    uint32_t ev = info->mEvent;
    if (ev == 0x8e04ce1a)
        SetSoundBlockAdded(info->mSourceBlock);
    else if (ev == 0x8fea0db4) {
        if (mByte20e != 0) {
            float f = CalculateModelSize(mpEditorSaveModel);
            RecordEvent4(0x1d6253c0, 0xdef22b96, f, 0);
        }
    }
    else if (ev == 0x428e920)
        SetSoundBlockRemoved(info->mSourceBlock);

    if (*(int*)(*(char**)((char*)g_15fd918 + 0x3c) + 0xdc) == 0)
        return true;

    ev = info->mEvent;
    if (ev == 0x8e04ce1a) {
        if (FUN_004a0ac0(mpEditorSaveModel) && mIsSkinAllowed != 0)
            ShowCreature();
    }
    else if (ev == 0x428e920) {
        if (!FUN_004a0ac0(mpEditorSaveModel) && mIsSkinAllowed != 0)
            HideCreature();
        ((unsigned char*)mpConfigData)[1] = 1;
        int cfg = GetCurrentConfig();
        if (cfg < 6 && mpLaunchData != 0 && ((unsigned char*)mpLaunchData)[0x6e] != 0)
            ((unsigned char*)mConfigData[cfg].p)[1] = 1;
    }

    if (mpAnimCreatureManager != 0 && mpSkinManager != 0 &&
        ((cSPEditorSkinManager*)mpSkinManager)->GetSkin(1) != 0) {
        if (info->mDelayTime > g_k1485378 && info->mAnimatedCreatureID != 0) {
            ((cSPEditorAnimatedCreatureManager*)mpAnimCreatureManager)
                ->AddDelayedEvent(AutoRefCount<cSPEditorAnimatedEventInfo>(info));
            return true;
        }
        RunSkinPaintOnEditorModel(0, 0);
        if (info->mAnimatedCreatureID == 0)
            info->mAnimatedCreatureID = mAnimatingCreatureID;
        if (((cSPEditorAnimatedCreatureManager*)mpAnimCreatureManager)->HandleAnimatedEvent(info)) {
            FUN_0057e340(1);
            if (mQueuedAnim != 0)
                return true;
            if (((cSPEditorAnimatedCreatureManager*)mpAnimCreatureManager)->IsAnimationDone(mAnimatingCreatureID))
                return true;
            WindowManager();
            void* wm = WindowManager();
            void* o = (*(void*(__thiscall**)(void*))(*(char**)wm + 4))(wm);
            if ((*(bool(__thiscall**)(void*, int))(*(char**)o + 0xfc))(o, 1)) {
                mFloat480 = mX;
                mFloat484 = mY;
                int* s = GetSetting6();
                if (s)
                    (*(void(__thiscall**)(int*, uint32_t, float, float, int))(*(char**)s + 0x1c))(
                        s, 0x1012, 1.0f, g_k13ec480, 1);
                mFlag4d4 = 1;
            }
            return true;
        }
        FUN_0057e340(mbModelBalanced);
        return true;
    }

    if (info->mEvent == 0x8e04ce1a && ((cBlk*)info->mSourceBlock)->B780())
        FUN_00572330(info->mSourceBlock);
    return true;
}

// @ 0x005855b0
void cAppModeEditorBase::SetModeModifiers()
{
    uint32_t old = mControlModifierMode;
    mControlModifierMode &= 1;

    uint32_t k0 = mInput.mKeys[0];
    unsigned char k17 = (k0 >> 17) & 1;
    unsigned char k18 = (k0 >> 18) & 1;
    unsigned char k16 = (k0 >> 16) & 1;
    unsigned char k9  = (k0 >> 9) & 1;

    unsigned char b0 = 0;
    if (((cPropertyList*)g_15fd918)->GetDescription(0x68df418))
        b0 = (mInput.mKeys[2] >> 9) & 1;

    bool cl = false;
    if (((mInput.mKeys[2] >> 1) & 1) && mBudgetFlag0 != 0 && mBudgetFlag1 != 0)
        cl = true;

    if (k9 != 0) {
        ((unsigned char*)mpConfigData)[0xe] = 1;
        int cfg = GetCurrentConfig();
        if (cfg < 6 && mpLaunchData != 0 && ((unsigned char*)mpLaunchData)[0x6e] != 0)
            ((unsigned char*)mConfigData[cfg].p)[0xe] = 1;
        mControlModifierMode += 0x80;
    }
    else if (cl) {
        if (k16 == 0 && k18 == 0 && b0 == 0) {
            FUN_0057c530(0x22, true);
            mControlModifierMode += 0x200;
        }
    }

    SetModelLocked((mControlModifierMode >> 7) & 1);

    if (b0 != 0 && k17 == 0 && k16 == 0 && k18 == 0 && k9 == 0)
        mControlModifierMode += 0x100;

    if (mQueuedAnim == 0) {
        if (mControlModifierMode & 0x100)
            ShowBlockAbilities(mpManipulatedBlock);
        else {
            void* p = FUN_00401020();
            void* q = ((cObjA*)p)->Get();
            if (q != 0)
                ((cObjB*)q)->Hide();
        }
    }

    if (mQueuedAnim == 1 && mpPaintCategoriesUI != 0 &&
        ((cSPPaletteUI*)mpPaintCategoriesUI)->IsPaintByNumber()) {
        if (k18 != 0) {
            mControlModifierMode += 0x10;
            switch (mModelValidity0) {
            case 0: mControlModifierMode += 0x60; break;
            case 1: mControlModifierMode += 0x20; break;
            case 2: mControlModifierMode += 0x40; break;
            }
        }
        else if (k17 != 0) {
            switch (mEyeDropperModiferMode) {
            case 0: mControlModifierMode += 8; break;
            case 1: mControlModifierMode += 4; break;
            }
        }
        if (k16 != 0)
            mControlModifierMode += 2;
    }

    if (old != mControlModifierMode)
        FUN_005820a0();
}

// @ 0x005857c0
void cAppModeEditorBase::SetEyeDropperMode(int mode)
{
    if (mpPaintCategoriesUI != 0 &&
        ((cSPPaletteUI*)mpPaintCategoriesUI)->IsPaintByNumber()) {
        if (mode != (int)mEyeDropperModiferMode) {
            mEyeDropperModiferMode = mode;
            FUN_005820a0();
        }
        if (mpDevUI != 0) {
            switch (mode) {
            case 0: {
                void* p = FUN_0067cac0(0x52ae2253);
                ((cDevGlobal*)p)->Method();
                break;
            }
            case 1: {
                void* p = FUN_0067cac0(0x33feea3);
                ((cDevGlobal*)p)->Method();
                break;
            }
            }
        }
    }
}

// @ 0x00585d10
bool cAppModeEditorBase::OnMouseWheelThunk(int a, float b, float c, int d)
{
    return OnMouseWheel(a, b, c, d, 0);
}

// @ 0x00585c10
void cAppModeEditorBase::FUN_00585c10()
{
    if (mpAnimCreatureManager != 0 && mAnimThumbID != 0) {
        ((cSPEditorAnimatedCreatureManager*)mpAnimCreatureManager)->RemoveCreature(mAnimThumbID);
        mAnimThumbID = 0;
    }
    if (mpPedastalModel != 0) {
        ((cRefObj*)mpPedastalModel)->Method();
        void* p = mpPedastalModel;
        if (p != 0) {
            int* q = (int*)((char*)p + 4);
            mpPedastalModel = 0;
            int n = q[1];
            --n;
            q[1] = n;
            if (n == 0) {
                q[1] = 1;
                (*(void(__thiscall**)(void*, int))(*(void**)q))(q, 1);
            }
        }
    }
    if (mpTextureFactory != 0) {
        ((cTexObj*)mpTextureFactory)->Method();
        void* p = mpTextureFactory;
        if (p != 0) {
            mpTextureFactory = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
        }
    }
    mFlag4b1 = 0;
    mSaveInProgress = 6;
}

// @ 0x005858f0
bool cAppModeEditorBase::OnMouseWheel(int a, float b, float c, int d, char e)
{
    if (mFlag397 != 0)
        return false;
    mIdleTarget = 0.0f;
    if ((d & 1) != 0 && mQueuedAnim != 2) {
        ((unsigned char*)mpConfigData)[0xd] = 1;
        int cfg = GetCurrentConfig();
        if (cfg < 6 && mpLaunchData != 0 && ((unsigned char*)mpLaunchData)[0x6e] != 0)
            ((unsigned char*)mConfigData[cfg].p)[0xd] = 1;
    }
    if ((d & 1) != 0 || mQueuedAnim == 2)
        return false;
    if (mQueuedAnim != 0)
        return true;
    if (mpActiveManipulator != 0)
        return true;
    if (mFlag472 != 0) {
        OnBlockWheel(mpBlock48c, mpHandle490, a);
        mFloat480 = b;
        mFloat484 = c;
        mFloat474 = 0.0f;
        return true;
    }
    cSPEditorBlock* blk = (e != 0) ? (cSPEditorBlock*)mpPreviousSelectedBlock
                                   : (cSPEditorBlock*)mpManipulatedBlock;
    if (mFlag143 != 0) {
        bool fromTorso = false;
        cSPEditorBlock* cc = blk;
        bool have = (cc != 0);
        if (!have) {
            if (mpTorsoHandle != 0 &&
                (*(uint32_t(__thiscall**)(void*))(*(char**)mpTorsoHandle + 0x10))(mpTorsoHandle) == 0x50e8e23 &&
                ((cSPEditorHandle*)mpTorsoHandle)->GetEditorBlock() != 0) {
                cc = ((cSPEditorHandle*)mpTorsoHandle)->GetEditorBlock();
                fromTorso = true;
                have = (cc != 0);
            }
        }
        if (have) {
            uint32_t f = cc->mFlagsDCC;
            if ((((f >> 0xc) & 1) != 0) || (((f >> 0xd) & 1) != 0) || fromTorso) {
                cSPEditorBlock* parent = cc->mpParent;
                if (parent != 0 && ((parent->mFlagsDC8 >> 7) & 1) == 0)
                    cc = parent;
            }
            if (!FUN_00435c80(cc) && ((cc->mFlagsDC8 >> 7) & 1) == 0)
                FUN_00448d60(cc);
        }
    }
    if (OnBlockWheel(blk, mpTorsoHandle, a)) {
        FUN_0057e220(b, c, blk, mpTorsoHandle);
        return true;
    }
    if (!HasId(0x7ad67439))
        return true;
    void* app = App();
    void* v1 = 0;
    void* v2 = 0;
    void* ray = (*(void*(__thiscall**)(void*, float, float, void*, void*))(*(char**)app + 0x58))(app, b, c, &v1, &v2);
    ((cRayObj*)ray)->Method();
    uint32_t bits[5] = { 0, 0, 0, 0, 0 };
    unsigned char tag1 = 1;
    void* mm = ModelManager();
    int idx = (*(int(__thiscall**)(void*, uint32_t, int))(*(char**)mm + 0x28))(mm, 0x9138fd8d, 0);
    if ((uint32_t)idx < 0x40) bits[idx >> 5] |= 1u << (idx & 0x1f);
    mm = ModelManager();
    idx = (*(int(__thiscall**)(void*, uint32_t, int))(*(char**)mm + 0x28))(mm, 0x513cdfc1, 0);
    if ((uint32_t)idx < 0x40) bits[idx >> 5] |= 1u << (idx & 0x1f);
    void* smw = mpSaveModelWorld;
    cSPEditorBlock* res = (cSPEditorBlock*)(*(void*(__thiscall**)(void*, void*, void*, int, int, int, void*, int, int))(*(char**)smw + 0x24))(
        smw, &v1, bits, 0, 0, 0, &tag1, 0, 0);
    if (res != 0) {
        void** p = (void**)((char*)res + 0x64);
        if (*p != 0) {
            cSPEditorBlock* sel = InterfaceCast(p);
            if (((sel->mFlagsDC8 >> 7) & 1) != 0) {
                if (e == 0)
                    SetActiveBlock(sel, -1);
                OnBlockWheel(sel, 0, a);
                FUN_0057e220(b, c, sel, 0);
            }
        }
    }
    return true;
}
