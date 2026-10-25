// slice s0058ac10 -- SP::cAppModeEditorBase::OnKeyDown / OnMouseUp.
// Large input handlers. Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Member offsets are taken from the disassembly (retail differs from the 2008 PDB
// by +4 on the early members).
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV3 PV2 PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// ---------------------------------------------------------------------------
// External helpers (bodies live elsewhere; only their addresses matter here).
// Declared variadic so every call site compiles regardless of exact arity.
// ---------------------------------------------------------------------------
extern "C" {
void  FUN_00697a50(...);   // cLocalInputState::OnKeyDown
void  FUN_005855b0(...);   // SetModeModifiers
void  FUN_005858f0(...);   // OnMouseWheel
void  FUN_0057c530(...);   // SetTrayState
void  FUN_00573480(...);   // SetSymmetryMode
void  FUN_005857c0(...);
void  FUN_005725d0(...);
void  FUN_0057e790(...);   // SetSelectedBlock
void  FUN_00573c00(...);   // SetActiveBlock
void  FUN_00573d70(...);   // SetRolloverHandle
void  FUN_0057e160(...);   // SetTorsoIsSelected
void  FUN_005772b0(...);   // RemoveTorsoFromEffectsMask
void  FUN_00577520(...);   // UpdateBlockState
void  FUN_0057af00(...);   // Pick
void  FUN_00586410(...);
void  FUN_0058a5a0(...);   // Undo
void  FUN_0058a950(...);
int   FUN_005ca920(...);   // cSPPaletteUI::IsPaintByNumber
void  FUN_005dfd00(...);   // cSPEditorUI::DoCommand
void  FUN_005dc2e0(...);
void  FUN_005dc300(...);
void  FUN_005dc2d0(...);
void  FUN_005dd070(...);
void  FUN_006288c0(...);
void  FUN_006284a0(...);
void  FUN_00628930(...);
void  FUN_0067cac0(...);
void  FUN_0067c830(...);
void  FUN_006a17e0(...);
void* FUN_0067cab0(...);
void  FUN_008013d0(...);
void* FUN_004accb0(...);   // cSPEditorModel::GetBlock
void  FUN_004abaf0(...);   // cSPEditorModel::AddBlock
void  FUN_0044e980(...);   // cSPEditorBlock::SetSymmetrySign
void  FUN_0044f420(...);   // cSPEditorBlock::Split
void  FUN_00435a10(...);   // cSPEditorBlock::SetFlag
void  FUN_00438700(...);   // cSPEditorBlock::AddChild
void  FUN_00438a40(...);   // cSPEditorBlock::RemoveChild
void  FUN_00449420(...);   // cSPEditorBlock::SetOrientation
void  FUN_00448e90(...);   // cSPEditorBlock::SetPosition
void  FUN_0043eb50(...);   // cSPEditorBlock::SetMuscleScale
void  FUN_0044efb0(...);   // cSPEditorBlock::RecursiveFlagC
void  FUN_0048fde0(...);
void  FUN_004a1020(...);
void  FUN_004a88d0(...);
void* FUN_004a0b70(int, int);
void* FUN_004a5e10(...);   // EditorUtils::GetLimbRoot
void* FUN_004a6310(...);   // EditorUtils::GetSymmetryRoot
int   FUN_004a6120(...);   // EditorUtils::IsBlockLocked
void  FUN_004a6640(...);   // EditorUtils::RebuildLimbSkins
void  FUN_004a6f10(...);   // EditorUtils::DeleteInvalidBlocks
void  FUN_004a7f30(...);   // EditorUtils::SetSymmetricBlocksUIState
void* FUN_004aa030(...);   // EditorUtils::GetBoneForHandle
void  FUN_0048c790(...);   // BuildPileList
void  FUN_0049dd20(...);
void  FUN_00453eb0(...);   // eastl::vector dtor
void  FUN_00438f20(...);
void  FUN_00439110(...);   // cSPEditorBlock::SetModelBasedOnSymmetrySign
void* FUN_0047e6c0(...);   // cSPEditorHandle::GetEditorBlock
float FUN_0043eed0(...);
void  FUN_004adaa0(...);
void  FUN_004511d0(...);
uint32_t FUN_0044e830(...);
uint32_t FUN_004accf0(...);
void  FUN_005a5a00(...);
int   FUN_00575eb0(...);   // cAppModeEditorBase::SomeBool (not a virtual; direct call)
}

// Factories returning objects whose vtables we poke.
struct IWindowManager { PV16 PV8 PV4 PV2 PV PV virtual int GetActiveUI(); };  // +0x84
struct IAssetBrowser  { char pad0[0x1c]; char mbActive; };
struct IMovieSystem   { PV8 PV4 virtual int IsMovieActive(); };              // +0x30
struct IAppSystem     { PV8 PV4 PV virtual int IsSomething(); };             // +0x34
struct IMessageServer { PV4 PV virtual void Post(uint32_t, int, int); };     // +0x14
struct ISporeGuide    { char pad0[0x1c]; char mbActive; };
struct IEditorUI {                                                           // [this+0x7c]
    PV4 PV
    virtual void HandleMouse(uint32_t, float, float, uint32_t);  // +0x14
    PV
    virtual bool HandleKey(uint32_t, uint32_t);                  // +0x1c
};
struct ISkinManager {                                                        // [this+0x148]
    PV4
    virtual bool OnMouseUp(uint32_t, float, float, uint32_t);    // +0x10
    PV4 PV2 PV
    virtual void Stop();                                         // +0x30
    virtual int  IsSymmetryEnabled();                            // +0x34
};
struct IRefObj { PV2 virtual void Release(); };                              // +0x08
struct ISpEditorHandle { PV4 virtual int GetHandleType(); };                 // +0x10

IWindowManager* __cdecl WindowManager();     // 0x67caa0
IAssetBrowser*  __cdecl AssetBrowser();      // 0x401030
IMovieSystem*   __cdecl MovieSystem();       // 0x67cb10
IAppSystem*     __cdecl AppSystem();         // 0x67dd00
IMessageServer* __cdecl MessageServer();     // 0x67dcc0
ISporeGuide*    __cdecl SporeGuide();        // 0x6288c0 factory

// ---------------------------------------------------------------------------
// Named view of the SP editor object (offsets from the disassembly).
// ---------------------------------------------------------------------------
struct cEditorBlock {                        // SP::cSPEditorBlock (partial)
    PV2 virtual void Release();              // +0x08
    char     padC[0x18 - 0x0c];
    uint32_t mInstance;                      // +0x18
    char     pad1[0x33c - 0x1c];
    void*    mChild;                         // +0x33c
    char     pad2[0x3e0 - 0x340];
    void*    mPile;                          // +0x3e0
    int      mFlags3ec;                      // +0x3ec
    char     pad3[0xdc8 - 0x3f0];
    uint32_t mFlagWord;                      // +0xdc8
    uint32_t mFlagWord2;                     // +0xdcc
};

struct cLocalInputState { void OnKeyDown(uint32_t key, uint32_t mods); };

namespace SP {
class cAppModeEditorBase {
public:
    char            pad0[0x28];
    float           mX;                      // +0x28
    float           mY;                      // +0x2c
    uint32_t        mCurrentMouseDown;       // +0x30
    uint32_t        mPreviousKey;            // +0x34
    uint32_t        mControlModifierMode;    // +0x3c
    char            pad40[0x44 - 0x40];
    int             mMode44;                 // +0x44
    char            pad48[0x78 - 0x48];
    void*           mpLightingWorld;         // +0x78 (dev UI, used for DoCommand)
    IEditorUI*      mpEditorUI;              // +0x7c
    char            pad80[0x98 - 0x80];
    void*           mpEditorModel;           // +0x98
    char            pad9c[0xd0 - 0x9c];
    cEditorBlock*   mpSelectedBlock;         // +0xd0
    cEditorBlock*   mpPreviousBlock;         // +0xd4
    char            padD8[0xdc - 0xd8];
    cEditorBlock*   mpToBeSelected;          // +0xdc
    unsigned char   mTorsoSelected;          // +0xe0
    char            padE1[0xe9 - 0xe1];
    unsigned char   mTorsoInEffectsMask;     // +0xe9
    char            padEA[0xf8 - 0xea];
    cLocalInputState mLocalInputState;       // +0xf8
    char            pad124[0x140 - 0x124];
    unsigned char   mManipulatorFlag;        // +0x140
    char            pad141[0x148 - 0x141];
    ISkinManager*   mpSkinManager;           // +0x148
    void*           mpSaveLoadFactory;       // +0x150
    char            pad154[0x2b1 - 0x154];
    unsigned char   mFlag2b1;                // +0x2b1
    char            pad2b2[0x2b3 - 0x2b2];
    unsigned char   mFlag2b3;                // +0x2b3
    unsigned char   mFlag2b4;                // +0x2b4
    char            pad2b5[0x31c - 0x2b5];
    int             mCameraMode;             // +0x31c
    char            pad320[0x397 - 0x320];
    unsigned char   mFlag397;                // +0x397
    char            pad398[0x3bc - 0x398];
    void*           mpPaletteUI;             // +0x3bc
    char            pad3c0[0x3c4 - 0x3c0];
    void*           mpPaletteUI2;            // +0x3c4
    char            pad3c8[0x472 - 0x3c8];
    unsigned char   mFlag472;                // +0x472
    char            mTail[0x600 - 0x473];

public:
    virtual bool OnKeyDown(uint32_t key, uint32_t modifiers);                  // 0x0058ac10
    virtual bool OnMouseUp(uint32_t button, float x, float y, uint32_t flags); // 0x0058b650
};
}
using SP::cAppModeEditorBase;

// ---------------------------------------------------------------------------
// OnKeyDown (0x58ac10) -- key handler; returns true when the key was consumed.
// ---------------------------------------------------------------------------
// @ 0x0058ac10
bool cAppModeEditorBase::OnKeyDown(uint32_t key, uint32_t modifiers)
{
    mLocalInputState.OnKeyDown(key, modifiers);
    FUN_005855b0();
    FUN_005855b0();
    if (mFlag397 != 0)
        return false;

    int  activeUI = WindowManager()->GetActiveUI();
    bool abActive = AssetBrowser()->mbActive != 0;

    if (mCameraMode == 2) {
        if (mpEditorUI->HandleKey(key, modifiers))
            return true;
    }

    uint32_t low = key & 7;

    if ((key & 0x40) != 0)
        return false;

    switch (key) {
    case 0x8:
    case 0x2e:
        if (activeUI == 0 && !abActive) {
            cEditorBlock* prev = mpPreviousBlock;
            if (prev != 0 &&
                mpSkinManager == 0 &&
                ((prev->mFlagWord >> 7) & 1) == 0 &&
                mFlag472 == 0) {
                FUN_005725d0(this, &mpPreviousBlock);
                FUN_0057e790(this, 0, 1);
                FUN_00573c00(this, 0, -1);
                FUN_00573d70(this, 0, 1);
                if (mpSelectedBlock != 0) {
                    cEditorBlock* b = mpSelectedBlock;
                    mpSelectedBlock = 0;
                    b->Release();
                }
                // duplicate the pile/limb-root rebuild on the previous block
                if (prev->mFlags3ec != 0 &&
                    ((prev->mFlagWord >> 5) & 1) != 0) {
                    void* child = prev->mChild;
                    if (child != 0 && ((cEditorBlock*)child)->mFlagWord != 0) {
                        void* limb = FUN_004a5e10(child);
                        int n = (int)FUN_004accf0(mpEditorModel);
                        void* newBlk = FUN_004a0b70(n, (int)(int)(long)limb);
                        if (newBlk != 0) {
                            FUN_004abaf0(mpEditorModel, newBlk, 1);
                            FUN_00435a10(newBlk, 0xc, 1);
                            FUN_0044f420(newBlk, 3);
                        }
                    }
                }
                FUN_00435a10(prev, 1, 1);
                FUN_0048c790(prev, 0, 0);
                FUN_004a6f10(prev, 0);
                FUN_00586410(this, 1, 0);
                return true;
            }
        }
        break;

    case 0xd:
        if (activeUI == 0 && !abActive && FUN_00575eb0(this, 0)) {
            FUN_005dfd00(mpLightingWorld, 0x10d);
            return true;
        }
        break;

    case 0x10:
    case 0x11:
    case 0x12:
        mCurrentMouseDown = modifiers;
        return false;

    case 0x1b:
        if (activeUI == 0 && !abActive && FUN_00575eb0(this, 0)) {
            if (mpPreviousBlock == 0 && mFlag2b3 == 0) {
                FUN_005dfd00(mpLightingWorld, 0x10d);
                return true;
            }
            if (mpSkinManager == 0) {
                FUN_0057e790(this, 0, 1);
                if (mTorsoInEffectsMask != 0) {
                    FUN_005772b0(this);
                    mTorsoInEffectsMask = 0;
                }
            }
            return true;
        }
        break;

    case 0x26:
        if (activeUI == 0 && !abActive) {
            FUN_005858f0(this, 0x78, mX, mY, (float)mCurrentMouseDown, 1);
            return true;
        }
        break;

    case 0x28:
        if (activeUI == 0 && !abActive) {
            FUN_005858f0(this, -0x78, mX, mY, (float)mCurrentMouseDown, 1);
            return true;
        }
        break;

    case 0x31:
        if ((mControlModifierMode & 1) != 1) {
            FUN_005857c0(this, 0);
            FUN_0057c530(this, 0x13, 1);
            return true;
        }
        break;

    case 0x32:
        if ((mControlModifierMode & 1) != 1) {
            FUN_005857c0(this, 1);
            FUN_0057c530(this, 0x14, 1);
            return true;
        }
        break;

    case 0x33:
        if ((mControlModifierMode & 1) != 1) {
            FUN_00573480(this, 1);
            FUN_0057c530(this, 0x16, 1);
            return true;
        }
        break;

    case 0x34:
        if ((mControlModifierMode & 1) != 1) {
            if (FUN_005ca920(mpPaletteUI2)) {
                if (mpLightingWorld != 0 && mMode44 != 2)
                    mMode44 = 2;
                FUN_0067cac0(0x33c35a06);
                FUN_0067c830(0x33c35a06);
                mControlModifierMode = (mControlModifierMode & 0xffffffdf) + 0x40;
            }
            FUN_0057c530(this, 0x17, 1);
            return true;
        }
        break;

    case 0x35:
        if ((mControlModifierMode & 1) != 1) {
            FUN_00573480(this, 0);
            FUN_0057c530(this, 0x18, 1);
            return true;
        }
        break;

    case 0x42:
        if (low == 0)
            FUN_006a17e0(0x36, true);
        if (modifiers == 0 && SporeGuide()->mbActive == 0) {
            FUN_005dc2e0();
        }
        break;

    case 0x46:
        if ((mCurrentMouseDown & 2) != 0 && low != 6) {
            cEditorBlock* p = mpPreviousBlock;
            if (p != 0 &&
                ((p->mFlagWord2 >> 0x19) & 1) != 0 &&
                ((p->mFlagWord >> 5) & 1) == 0) {
                uint32_t btype = (uint32_t)p->mInstance;
                FUN_00435a10(p, 0x39, 0);
                uint32_t sign = FUN_0044e830(p);
                if (sign != 0) {
                    uint32_t nsign = (uint32_t)(-(int)sign);
                    uint32_t tmp = 0;
                    FUN_00438f20(&tmp, (int)nsign, 0);
                    if (tmp != btype)
                        FUN_00439110(p, (int)nsign, 0, 0, 0, 0);
                    if (tmp != p->mInstance)
                        FUN_00439110(p, (int)sign, 0, 0, 0, 0);
                }
                FUN_00435a10(p, 0x39, 1);
                FUN_00586410(this, 1, 0);
                return false;
            }
        }
        break;

    case 0x48:
        if (low == 2 && activeUI == 0 && !abActive) {
            FUN_005dc300();
            return false;
        }
        if (modifiers == 0 && MovieSystem()->IsMovieActive() == 0) {
            FUN_0057e160(this, 1);
            return false;
        }
        break;

    case 0x4e:
        if (AppSystem()->IsSomething() == 0 && activeUI == 0 && !abActive &&
            MovieSystem()->IsMovieActive() == 0) {
            if (low == 0) {
                FUN_006a17e0(0x34, true);
                return false;
            } else if (low == 2) {
                FUN_005dc2e0();
            }
        }
        break;

    case 0x53:
        if (low == 2) {
            FUN_005dc2d0();
            if (MovieSystem()->IsMovieActive() == 0) {
                FUN_005dfd00(mpLightingWorld, 0x101);
                return false;
            }
        }
        break;

    case 0x59:
        if (low == 2 && mCameraMode != 2) {
            FUN_0058a950();
            return false;
        }
        break;

    case 0x5a:
        if (low == 2 && mCameraMode != 2) {
            FUN_0058a5a0(this, 1, 1);
            return false;
        }
        break;

    case 0xbf:
        if (modifiers == 0 || modifiers == 1) {
            if (MovieSystem()->IsMovieActive() == 0) {
                FUN_0057e160(this, 1);
                return false;
            }
        }
        break;
    }
    return false;
}

// ---------------------------------------------------------------------------
// OnMouseUp (0x58b650) -- mouse button release; returns whether the editor UI
// consumed the event.
// ---------------------------------------------------------------------------
struct EditorPickResult {                    // SP::EditorUtils::cPickResult (partial)
    void*    mpBlockA;                       // +0x00
    char     pad4[0x0c];
    void*    mpBlockB;                       // +0x10
};

// @ 0x0058b650
bool cAppModeEditorBase::OnMouseUp(uint32_t button, float x, float y, uint32_t flags)
{
    if (button != mPreviousKey)
        return false;
    mPreviousKey = 0;

    int mode = mCameraMode;
    if (mode != 0) {
        if (mode != 2)
            return false;
        mpEditorUI->HandleMouse(button, x, y, flags);
        return false;
    }

    MessageServer()->Post(0x48e5912, 0, 0);

    if (button == 0x3e9 || (button == 0x3e8 && mpSkinManager == 0)) {
        FUN_008013d0(FUN_0067cab0(1), 1);
        mFlag2b3 = 1;
        if (mFlag2b4 == 0)
            return false;
        if (mTorsoInEffectsMask != 0) {
            FUN_005772b0(this);
            mTorsoInEffectsMask = 0;
        }
        FUN_0057e790(this, 0, 1);
        return false;
    }

    if (button != 0x3e8 && button != 0x3ea)
        return false;
    if (mpSkinManager == 0)
        return false;

    if (mpSelectedBlock != 0 && mpSelectedBlock->mFlags3ec != 0)
        FUN_004a5e10(mpSelectedBlock);

    int n = (int)FUN_004accf0(mpEditorModel);
    for (int i = 0; i < n; ++i) {
        void* blk = FUN_004accb0(mpEditorModel, i);
        FUN_0044e980(blk, -2);
    }

    if (mpSelectedBlock != 0)
        FUN_004a7f30(mpSelectedBlock, 0, 0);

    bool r = mpSkinManager->OnMouseUp(button, x, y, flags);

    if (mpSkinManager->IsSymmetryEnabled() && mpSelectedBlock != 0)
        FUN_004a88d0(0x3bbdccca);

    FUN_004a1020(mpEditorModel);

    if (mTorsoSelected != 0) {
        FUN_0057e160(this, 1);
    } else {
        cEditorBlock* sel = mpSelectedBlock;
        cEditorBlock* tgt = mpToBeSelected;
        void* arg;
        if (sel != tgt) {
            arg = tgt;
        } else if (sel != 0 &&
                   (sel->mFlagWord & 4) == 0 &&
                   (sel->mFlagWord & 2) == 0) {
            arg = sel;
        } else {
            arg = 0;
        }
        FUN_0057e790(this, arg, 1);
    }

    bool bl = false;
    cEditorBlock* sel = mpSelectedBlock;
    if (sel != 0) {
        if (((sel->mFlagWord >> 2) & 1) != 0) {
            if (sel->mChild != 0)
                FUN_00438a40(sel->mChild, sel);
            bl = true;
        } else if (((sel->mFlagWord >> 1) & 1) == 0) {
            FUN_0044efb0(sel);
            cEditorBlock* p = mpSelectedBlock;
            void* root = FUN_004a6310(p);
            if (p != 0 && FUN_004a6120(p) && mFlag2b1 == 0)
                root = FUN_004a5e10(p);
            cEditorBlock* q = mpSelectedBlock;
            if (q != 0 && q->mFlags3ec != 0)
                root = FUN_004a5e10(q);
            FUN_0048fde0(root);
        }
    }

    mpSkinManager->Stop();
    if (mpSkinManager != 0) {
        ISkinManager* skin = mpSkinManager;
        mpSkinManager = 0;
        ((IRefObj*)skin)->Release();
    }

    FUN_00577520(this);

    EditorPickResult out;
    FUN_0057af00(this, &out, mY, mX, false);

    void* ebp = 0;
    bool wentThroughHandle = false;
    void* blk = out.mpBlockA;
    if (blk != 0 && *(void**)((char*)blk + 0x64) != 0) {
        void* handle = FUN_004aa030((char*)blk + 0x64);
        ebp = FUN_0047e6c0(handle);
        if (handle != 0) {
            int ht = ((ISpEditorHandle*)handle)->GetHandleType();
            if (ht == 0x50e8e23) {
                FUN_004a6640(FUN_0047e6c0(mpSaveLoadFactory),
                             FUN_0047e6c0(handle));
                ht = ((ISpEditorHandle*)handle)->GetHandleType();
            }
            if (ht == 0x50a993c)
                mManipulatorFlag = 0;
            FUN_00573d70(this, handle, 1);
            wentThroughHandle = true;
        }
    }

    if (!wentThroughHandle) {
        if (blk == 0)
            ebp = out.mpBlockB;   // 0x58b971
        if (ebp != 0 && FUN_004a6120(ebp))
            FUN_004a6640(ebp, mpSaveLoadFactory);
        FUN_00573c00(this, ebp, -1);
    }

    {
        void* model = mpEditorModel;
        if (*(unsigned char*)((char*)model + 0x51) != 0 &&
            (mFlag2b1 == 0 ||
             (mpSelectedBlock != 0 && ((mpSelectedBlock->mFlagWord >> 1) & 1) == 0))) {
            FUN_00586410(this, 1, 0);
        }
    }

    if (mpSelectedBlock != 0) {
        cEditorBlock* b = mpSelectedBlock;
        mpSelectedBlock = 0;
        b->Release();
    }

    if (bl)
        FUN_0058a5a0(this, 0, 0);

    return r;
}

