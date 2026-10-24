// Slice s0064fa20 -- SP::cSPUIAssetGrid scrolling / card-layout / message handling.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <xmmintrin.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned int uint32;

static const float kZero = 0.0f;
static const float kOne  = 1.0f;

#define VT(p) (*(void***)(p))

// SSE scalar clamp (maxss/minss) -- the original uses this pattern for every
// scroll-target saturation in the module.
// SSE scalar clamp (maxss/minss) -- the original uses this pattern for every
// scroll-target saturation in the module.
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

// IWindow -- only the vtable slots this slice reaches are named.
struct IWindow {
    virtual void     slot00();
    virtual void     slot04();
    virtual void     slot08();
    virtual void     slot0c();
    virtual void     slot10();
    virtual void     slot14();
    virtual void     slot18();
    virtual void     slot1c();
    virtual void     slot20();
    virtual void     slot24();
    virtual void     slot28();
    virtual void     slot2c();
    virtual void     slot30();
    virtual void     slot34();
    virtual float*   GetArea();          // +0x38
    virtual void     slot3c();
    virtual int      GetVisibleCount();  // +0x40  (typed by role)
    virtual void     slot44();
    virtual void     slot48();
    virtual void     slot4c();
    virtual void     slot50();
    virtual void     slot54();
    virtual void     slot58();
    virtual void     slot5c();
    virtual void     slot60();
    virtual void     slot64();
    virtual void     slot68();
    virtual void     SetArea(float* rect); // +0x6c
};

// Inner object reached through cScrollFrame::mpInner (+0x20); used for scroll sync.
struct IWindow_Inner {
    virtual void     i00();
    virtual void     i04();
    virtual void     i08();
    virtual void     i0c();
    virtual void     i10();
    virtual void     i14();
    virtual void     i18();
    virtual void     i1c();
    virtual void     i20();
    virtual void     SetRange(int v, int flag);   // +0x24
    virtual int      GetContentHeight();          // +0x28
    virtual void     i2c();
    virtual void     i30();
    virtual void     i34();
    virtual void     i38();
    virtual void     i3c();
    virtual int      GetColumns();                // +0x40
    virtual void     i44();
    virtual void     i48();
    virtual void     SetMin(int v);               // +0x4c
    virtual void     i50();
    virtual void     SetMax(int v);               // +0x54
};

// A scrollbar child; the object queried in DoMessage type 6 / 9 lives at +0x18,
// the range/scroll target window at +0x20.
struct IWindow18 {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual int  GetId();   // +0x10
};
struct cScrollFrame {
    uint32_t        pad00[0x4];
    int             mId;       // +0x10
    uint32_t        pad14;
    IWindow18*      mpChild;   // +0x18
    uint32_t        pad1c;
    IWindow_Inner*  mpInner;   // +0x20
};

// Property owner reached through GetSetting3()->mpObject (+0x18).
struct cPropOwner {
    uint32_t pad00[0x6];
    void*    mpProps;   // +0x18
};

// Asset-view object (SP::cSPAssetView); vtable slots and the direct (non-virtual)
// helper methods this slice reaches are named by role.
struct AssetView {
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotc();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void NotifyReady();      // +0x30
    virtual void slot34();           // +0x34 (called with (int) from FUN_64fc40)

    bool IsReady();                  // 0x00657dd0
    bool FUN_00659270();             // 0x00659270
    void FUN_00659340();             // 0x00659340
    void SetPos(float x, float y, bool flag);  // 0x00658e00
    void FUN_00658e80();             // 0x00658e80

    uint32_t pad04[0x3c];            // +0x04 .. +0xf3
    uint8_t  mFlagF4;                // +0xf4
    uint8_t  mFlagF5;                // +0xf5
};

// Grid entry: same stride (0x20) as the source entry vector; the card object is at +0x10.
struct GridEntry {
    uint32_t    mKey0;    // +0x00
    uint32_t    mKey4;    // +0x04
    uint32_t    mKey8;    // +0x08
    uint32_t    mOrder;   // +0x0c
    AssetView*  mpCard;   // +0x10
    float       mPosX;    // +0x14
    float       mPosY;    // +0x18
    uint32_t    pad1c;    // +0x1c
};

// Message: first dword is the "object" handle, +4 an id, +8 the message type, +0xc a sub id.
struct GridMessage {
    uint32_t mObj;       // +0x00
    uint32_t mId;        // +0x04
    uint32_t mType;      // +0x08
    uint32_t mSub;       // +0x0c
    uint32_t pad10;      // +0x10
    uint32_t mCount;     // +0x14
    uint32_t mIndex;     // +0x18
};

// EA-facing audio system + message server; used in DoMessage.
struct IAudioSystem {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual int SetAudioState();           // +0x20
};
struct IMessageServer {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10();
    virtual void Post(uint32_t type, void* payload, int flag);   // +0x14
};
// Small event payload allocated in DoMessage's type-6 arm. Non-polymorphic:
// the function stores its vtable pointers as data at exact offsets.
struct EventPayload {
    void*    mpVtbl0;   // +0x00
    void*    mpVtbl4;   // +0x04
    uint32_t mField8;   // +0x08
    uint32_t mFieldC;   // +0x0c
    uint8_t  mField10;  // +0x10
    uint32_t mField14;  // +0x14
    uint8_t  mField18;  // +0x18
    uint8_t  mField19;  // +0x19
};

// ---------------------------------------------------------------------------
// External callees and globals (addresses from the call sites).
// ---------------------------------------------------------------------------
extern "C" cPropOwner* GetSetting3();                     // 0x00401030
extern "C" float  GetPropertyT_float(void* props, uint32_t id, float def);  // 0x004e1c70
extern "C" int    GetTutorialToolPrice(void* props, uint32_t id, int def);  // 0x004e1c30
extern "C" float  GetGlobal_15f9f40();                    // 0x006573e0
extern "C" void   FUN_0065aed0(int n);                    // 0x0065aed0
extern "C" IAudioSystem* Audio_GetSystemAT();             // 0x00a206f0
extern "C" IMessageServer* SP_MessageServer();            // 0x0067dcc0
extern "C" void   SP_KillSetiEffects(int a, uint32_t id); // 0x00435ed0
extern "C" void*  operator_new_1c(uint32_t n, const char* name, int a, uint32_t b,
                                  const char* file, int c); // 0x00f473a0
extern "C" void   UpdateMouseFocus(int flag);             // 0x00804f50
extern "C" int    FUN_0064f350(void* props, uint32_t id, int flag);  // 0x0064f350

extern uint32_t g_GridWinIDs[24];   // 0x01400420

// ---------------------------------------------------------------------------
// SP::cSPUIAssetGrid (retail member offsets; names by role).
// ---------------------------------------------------------------------------
struct cSPUIAssetGrid {
    virtual void iwproc00();   // +0x00
    virtual void iwproc04();   // +0x04
    virtual void ihandler0(); // +0x08
    virtual void ihandler1(); // +0x0c
    virtual void refcount0(); // +0x10
    virtual void refcount1(); // +0x14
    uint32_t    pad04[10];    // +0x04 .. +0x2b
    IWindow*    mpWinFeedHeader;      // +0x2c
    uint32_t    pad30[11];    // +0x30 .. +0x5b
    IWindow*    mpWin_5c;             // +0x5c
    uint32_t    pad60[34];    // +0x60 .. +0xe7
    GridEntry*  mpGridBegin;          // +0xe8
    GridEntry*  mpGridEnd;            // +0xec
    uint32_t    padf0[3];     // +0xf0 .. +0xfb
    GridEntry*  mpPendingEntry;       // +0xfc
    bool        mbPendingReady;       // +0x100
    uint8_t     pad101[3];    // +0x101 .. +0x103
    float       mfCellSpacingX;       // +0x104
    float       mfCellSpacingY;       // +0x108
    uint32_t    pad10c;       // +0x10c
    int         mnColumns;            // +0x110
    int         mnRows;               // +0x114
    float       mfCardStepX;          // +0x118
    float       mfCardStepY;          // +0x11c
    float       mfOriginX;            // +0x120
    float       mfOriginY;            // +0x124
    float       mfCardExtra;          // +0x128
    uint32_t    pad12c[21];   // +0x12c .. +0x17f
    float       mfScrollTarget;       // +0x180
    float       mfScrollActual;       // +0x184
    float       mfScrollMax;          // +0x188
    cScrollFrame* mpScrollFrame;      // +0x18c
    bool        mbMouseFocusSet;      // +0x190
    uint8_t     pad191[3];    // +0x191 .. +0x193
    int         mnScrollDir;          // +0x194
    int         mnRefreshState;       // +0x198

    void UpdateScrolling(int delta);            // 0x0064fa20
    void FUN_64fc40();                          // 0x0064fc40
    bool FUN_64fd00();                          // 0x0064fd00
    bool FUN_64fde0(int* pState);               // 0x0064fde0
    void ComputeCardLayoutParameters();         // 0x00650020
    bool FUN_650190(uint32_t msg, GridMessage* m);  // 0x00650190
    void FUN_650470();                          // 0x00650470
    GridEntry* Find(AssetView* card);           // 0x006505d0 (card 0: the first entry)

    bool FUN_64e7d0(uint32_t idx);              // 0x0064e7d0 (this = grid)
    void FUN_64eb60(int idx, bool state);       // 0x0064eb60 (this = grid)
};

// Helpers implemented elsewhere (same TU); called through their member types.

// ---------------------------------------------------------------------------
// @ 0x0064fa20
// ---------------------------------------------------------------------------
void cSPUIAssetGrid::UpdateScrolling(int delta) {
    float step = 6.0f;
    int minArg = 0x96;
    int maxArg = 8;

    cPropOwner* br = GetSetting3();
    if (br && br->mpProps) {
        cPropOwner* b2 = GetSetting3();
        step = GetPropertyT_float(b2->mpProps, 0xac40f7e5u, 6.0f);
        cPropOwner* b3 = GetSetting3();
        minArg = GetTutorialToolPrice(b3->mpProps, 0xdfcb730eu, 0x96);
        cPropOwner* b4 = GetSetting3();
        maxArg = GetTutorialToolPrice(b4->mpProps, 0xdf8c884du, 8);
    }

    float v = Clamp(mfScrollTarget, kZero, mfScrollMax);
    mfScrollTarget = v;

    if (mpWinFeedHeader == 0) goto tail;
    if (mpGridBegin == mpGridEnd) goto tail;
    if (v == mfScrollActual) goto tail;

    {
        float d = (float)delta;
        if (delta < 0) d += 4294967296.0f;
        float f = (d * step) * 0.001f;
        float c = Clamp(f, kZero, kOne);

        mnScrollDir = (mfScrollTarget > mfScrollActual) ? 1 : 0;
        cScrollFrame* sf = mpScrollFrame;
        float x = mfScrollActual;
        float na = (mfScrollTarget - x) * c + x;
        mfScrollActual = na;
        if (sf) {
            sf->mpInner->SetRange((int)na, 1);
        }
        if (mnRefreshState == 0) mnRefreshState = 2;
        if (fabs(mfScrollTarget - mfScrollActual) < 0.5f) {
            mfScrollActual = mfScrollTarget;
        }
    }

tail:
    if (mfScrollActual == mfScrollTarget) {
        mbMouseFocusSet = 0;
    }
    if (mpScrollFrame) {
        mpScrollFrame->mpInner->SetMin(minArg);
        mpScrollFrame->mpInner->SetMax(maxArg);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0064fc40
// ---------------------------------------------------------------------------
void cSPUIAssetGrid::FUN_64fc40() {
    int idx, end, step;
    if (mnScrollDir == 0) {
        idx = (int)(mpGridEnd - mpGridBegin) - 1;
        end = -1;
        step = -1;
    } else {
        idx = 0;
        end = (int)(mpGridEnd - mpGridBegin);
        step = 1;
    }
    for (; idx != end; idx += step) {
        GridEntry* e = &mpGridBegin[idx];
        AssetView* card = e->mpCard;
        if (FUN_64e7d0((uint32_t)idx)) continue;
        if (card == 0) continue;
        if (card->mFlagF5 == 0) continue;
        if (&mpGridBegin[idx] == mpPendingEntry) continue;
        (*(void(__thiscall**)(AssetView*, int))VT(card)[0x34 / 4])(card, idx);
        return;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0064fd00
// ---------------------------------------------------------------------------
bool cSPUIAssetGrid::FUN_64fd00() {
    int idx, end, step;
    if (mnScrollDir == 0) {
        idx = (int)(mpGridEnd - mpGridBegin) - 1;
        end = -1;
        step = -1;
    } else {
        idx = 0;
        end = (int)(mpGridEnd - mpGridBegin);
        step = 1;
    }
    for (; idx != end; idx += step) {
        AssetView* card = mpGridBegin[idx].mpCard;
        if (!FUN_64e7d0((uint32_t)idx)) continue;
        if (card == 0) continue;
        if (card->mFlagF4 == 0) continue;
        if (card->mFlagF5 != 0) continue;
        if (card->IsReady()) continue;
        mbPendingReady = (bool)(card->FUN_00659270() == 0);
        mpPendingEntry = &mpGridBegin[idx];
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0064fde0
// ---------------------------------------------------------------------------
bool cSPUIAssetGrid::FUN_64fde0(int* pState) {
    if (mpPendingEntry == 0) goto tail;
    if (mpPendingEntry->mpCard == 0) return false;
    if (!mpPendingEntry->mpCard->IsReady() && !mbPendingReady) return false;

    {
        GridEntry* saved = mpPendingEntry;
        mpPendingEntry = 0;
        mbPendingReady = 0;
        if (saved == 0) goto tail;

        AssetView* view = saved->mpCard;
        int extra = 4;
        {
            cPropOwner* br = GetSetting3();
            if (br && br->mpProps) {
                cPropOwner* b2 = GetSetting3();
                extra = GetTutorialToolPrice(b2->mpProps, 0x93bfdfa9u, 4);
            }
        }
        int total = (mnRows + extra) * mnColumns;
        FUN_0065aed0(total + 1);
        view->NotifyReady();
        view->FUN_00659340();

        if (*pState == 2) {
            cPropOwner* br = GetSetting3();
            if (!(br && br->mpProps && FUN_0064f350(GetSetting3()->mpProps, 0x49ff89ddu, 1))) {
                goto layout;
            }
            view->SetPos(saved->mPosX, saved->mPosY, false);
            view->FUN_00658e80();
        } else {
layout:
            float d = mfScrollActual - mfCellSpacingY;
            float v = (d > 0.0f) ? d : 0.0f;
            view->SetPos(0.0f, v, false);
        }
        if (total < GetGlobal_15f9f40()) {
            FUN_64fc40();
        }
    }

tail:
    if (!FUN_64fd00()) {
        *pState = 0;
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0064ff90
// ---------------------------------------------------------------------------
struct IRefDtor {
    virtual void r0();
    virtual void Release();   // +0x04
};
// An owner whose ref-counted sub-object sits at +0x10.
struct Holder10 {
    uint32_t pad[4];
    IRefDtor obj;   // +0x10
};

// Entry comparator. The original pops 0x40 bytes of stack arguments, so this is
// a __stdcall with sixteen dword-sized parameters (most of them unused); the
// live ones are a1..a3 (left key + its validity flag in a2), a4/a5 (left
// holders), a9..a11 (right key, valid when a12 != 0) and a12/a13 (right holders).
bool __stdcall CompareGridKeys(uint32_t a1, uint32_t a2, uint32_t a3,
                               Holder10* a4, IRefDtor* a5,
                               uint32_t a6, uint32_t a7, uint32_t a8,
                               uint32_t a9, uint32_t a10, uint32_t a11,
                               Holder10* a12, IRefDtor* a13,
                               uint32_t a14, uint32_t a15, uint32_t a16) {
    (void)a6; (void)a7; (void)a8; (void)a14; (void)a15; (void)a16;
    uint32_t l1 = 0, l2 = 0, l3 = 0;
    uint32_t r1 = 0, r2 = 0, r3 = 0;
    if (a4 != 0) { l1 = a1; l2 = a2; l3 = a3; }
    if (a12 != 0) { r1 = a9; r2 = a10; r3 = a11; }

    bool less;
    if (l1 != r1) {
        less = l1 < r1;
    } else if (l3 != r3) {
        less = l3 < r3;
    } else {
        less = l2 < r2;
    }

    if (a5)  a5->Release();
    if (a4)  a4->obj.Release();
    if (a13) a13->Release();
    if (a12) a12->obj.Release();
    return less;
}

// ---------------------------------------------------------------------------
// @ 0x00650020
// ---------------------------------------------------------------------------
void cSPUIAssetGrid::ComputeCardLayoutParameters() {
    if (mpWinFeedHeader == 0) return;

    cPropOwner* br = GetSetting3();
    if (br && br->mpProps) {
        cPropOwner* b2 = GetSetting3();
        mfOriginX = GetPropertyT_float(b2->mpProps, 0xce9d3dfau, 5.0f);
        cPropOwner* b3 = GetSetting3();
        mfCardStepY = GetPropertyT_float(b3->mpProps, 0x419d8685u, 3.0f);
        cPropOwner* b4 = GetSetting3();
        mfCardExtra = GetPropertyT_float(b4->mpProps, 0xf0de9b7fu, 0.0f);
    }

    mfOriginY = mfCardStepY;

    float* area = mpWinFeedHeader->GetArea();
    float x0 = area[0];
    float x1 = area[2];

    float span = x1 - x0;
    int cols = (int)(span / mfCellSpacingX);
    mnColumns = cols;
    if (cols < 1) mnColumns = 1;

    float d = (span - (float)mnColumns * mfCellSpacingX) / (float)(mnColumns + 1);
    mfCardStepX = d;
    mfOriginX = d;

    if (mpScrollFrame && mpScrollFrame->mpInner) {
        int vis = mpScrollFrame->mpInner->GetColumns();
        float f = (float)vis / (mfCellSpacingY + mfCardStepY);
        int n = (int)f;
        if ((float)n < f) n = n + 1;
        mnRows = n + 1;
    } else {
        mnRows = 1;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00650190
// ---------------------------------------------------------------------------
bool cSPUIAssetGrid::FUN_650190(uint32_t msg, GridMessage* m) {
    (void)msg;
    uint32_t type = m->mType;
    if (type > 0x287259f6u) {
        if (type != 0x8ef0c8ddu) return false;
        cScrollFrame* sf = mpScrollFrame;
        if (sf == 0) return false;
        if (m->mId != (uint32_t)sf->mId) return false;
        if (!mbMouseFocusSet) {
            float fv = (float)sf->mpInner->GetContentHeight();
            mnScrollDir = (fv > mfScrollActual) ? 1 : 0;
            mfScrollActual = fv;
            mfScrollTarget = fv;
        }
        if (mnRefreshState == 0) mnRefreshState = 2;
        return false;
    }

    if (type == 0x287259f6u) {
        if (m->mSub == 0x14580f81u) {
            IAudioSystem* a = Audio_GetSystemAT();
            int first = 0;
            if (a) first = (int)a->SetAudioState();
            SP_KillSetiEffects(first, 0xbbc12fc8u);
            IMessageServer* s = SP_MessageServer();
            s->Post(0xbf7280e2u, 0, 0);
            return true;
        }
        for (int i = 0; i < 0x18; ++i) {
            if (m->mSub == g_GridWinIDs[i]) {
                IAudioSystem* a = Audio_GetSystemAT();
                int first = 0;
                if (a) first = (int)a->SetAudioState();
                SP_KillSetiEffects(first, 0x3e89cd9eu);
                FUN_64eb60(i, false);
                return true;
            }
        }
        return false;
    }

    if (type == 6) {
        bool hit = (m->mId == (uint32_t)mpWinFeedHeader);
        if (!hit) {
            cScrollFrame* sf = mpScrollFrame;
            if (sf && sf->mpChild)
                hit = (m->mId == (uint32_t)sf->mpChild->GetId());
        }
        if (hit) {
            EventPayload* ev = (EventPayload*)operator_new_1c(0x1c, (const char*)0x13f6b3c, 0, 0, 0, 0);
            if (ev) {
                ev->mpVtbl4 = (void*)0x13ef094;
                ev->mField8 = 0;
                ev->mpVtbl0 = (void*)0x13ff800;
                ev->mpVtbl4 = (void*)0x13ff7fc;
                ev->mFieldC = 0;
                ev->mField10 = 0;
                ev->mField14 = 0;
                ev->mField18 = 0;
                ev->mField19 = 0;
                (*(void(__thiscall**)(void*))VT(ev)[1])(ev);
            }
            IMessageServer* s = SP_MessageServer();
            s->Post(0x94174b89u, ev, 0);
            if (ev) {
                (*(void(__thiscall**)(void*))VT(ev)[2])(ev);
            }
        }
        return false;
    }

    if (type == 9) {
        uint32_t id = m->mId;
        if (id != (uint32_t)mpWinFeedHeader &&
            id != (uint32_t)mpScrollFrame->mpChild &&
            id != (uint32_t)mpWin_5c) return false;
        float pct = 0.8f;
        cPropOwner* br = GetSetting3();
        if (br && br->mpProps) {
            cPropOwner* b2 = GetSetting3();
            pct = GetPropertyT_float(b2->mpProps, 0xfd92843du, 0.8f);
        }
        float v = mfScrollTarget - (float)(int)m->mIndex * pct;
        mfScrollTarget = v;
        if (v < 0.0f) v = 0.0f;
        if (v > mfScrollMax) v = mfScrollMax;
        mfScrollTarget = v;
        mbMouseFocusSet = true;
        UpdateMouseFocus(1);
        return true;
    }

    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00650470
// ---------------------------------------------------------------------------
void cSPUIAssetGrid::FUN_650470() {
    ComputeCardLayoutParameters();

    int count = (int)(mpGridEnd - mpGridBegin);
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            GridEntry* e = &mpGridBegin[i];
            if (mnColumns > 0) {
                e->mPosX = (float)(int)((mfCardStepX + mfCellSpacingX) *
                                        (float)(i % mnColumns)) + mfOriginX;
                e->mPosY = (float)(int)((mfCardStepY + mfCellSpacingY) *
                                        (float)(i / mnColumns)) + mfOriginY;
            }
        }
    }

    float lastY = 0.0f;
    if (mpGridBegin != mpGridEnd) {
        lastY = mpGridEnd[-1].mPosY;
    }

    struct Rect { float x, y, w, h; } rect;
    IWindow* s = mpWinFeedHeader;
    float* a = s->GetArea();
    rect.x = a[0];
    rect.y = a[1];
    rect.w = a[2];
    rect.h = mfCellSpacingY + lastY;
    mpWinFeedHeader->SetArea((float*)&rect);
}

// ---------------------------------------------------------------------------
// @ 0x006505d0
// ---------------------------------------------------------------------------
// Entry whose card is `card`, or 0; a null card selects entry 0 (index form kept: the original tests the found
// index against -1 before scaling it).
GridEntry* cSPUIAssetGrid::Find(AssetView* card) {
    int index = -1;
    if (card == 0) {
        index = 0;
    } else {
        const int n = (int)(mpGridEnd - mpGridBegin);
        for (int i = 0; i < n; ++i) {
            if (mpGridBegin[i].mpCard == card) {
                index = i;
                break;
            }
        }
    }
    if (index == -1)
        return 0;
    return &mpGridBegin[index];
}
