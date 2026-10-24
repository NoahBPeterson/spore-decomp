// Slice s00e06d90 -- SP::cSPUILoyaltyMeter (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct cSPUILayout {
    void* mpVtable;                                          // +0x00
    char IsVisible();                                        // 0x00810070
    void SetVisibility(int visible);                         // 0x00810590
};

struct cSPUILoyaltyMeter {
    void*        mpVtable;                                   // +0x00
    uint32_t     mPad04[3];                                  // +0x04 .. +0x0f
    cSPUILayout* mpLayout;                                   // +0x10
    uint32_t     mPad14[3];                                  // +0x14 .. +0x1f
    uint32_t     mValue20;                                   // +0x20
    uint32_t     mValue24;                                   // +0x24
    uint32_t     mPad28;                                     // +0x28
    void*        mpExtra2c;                                  // +0x2c

    void Show();
    void Hide();
    void ShowExpanded();
    void HideExpanded();
};

// @ 0x00e07b20
void cSPUILoyaltyMeter::ShowExpanded()
{
    if (mpExtra2c) {
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)mpExtra2c)[0x7c / 4])
            (mpExtra2c, 1, 1);
    }
    if (mpLayout && mpLayout->IsVisible())
        return;
    mpLayout->SetVisibility(1);
    ((void (__thiscall*)(cSPUILoyaltyMeter*))((void**)mpVtable)[0x24 / 4])(this);
    ((void (__thiscall*)(cSPUILoyaltyMeter*))((void**)mpVtable)[0x28 / 4])(this);
    mValue24 = mValue20;
}

// @ 0x00e07b70
void cSPUILoyaltyMeter::HideExpanded()
{
    if (mpLayout && mpLayout->IsVisible()) {
        mpLayout->SetVisibility(0);
        mValue24 = mValue20;
    }
    if (mpExtra2c) {
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)mpExtra2c)[0x7c / 4])
            (mpExtra2c, 1, 0);
    }
}

// @ 0x00e07950
void cSPUILoyaltyMeter::Show()
{
    if (mpLayout && mpLayout->IsVisible())
        return;
    mpLayout->SetVisibility(1);
    ((void (__thiscall*)(cSPUILoyaltyMeter*))((void**)mpVtable)[0x24 / 4])(this);
    ((void (__thiscall*)(cSPUILoyaltyMeter*))((void**)mpVtable)[0x28 / 4])(this);
    mValue24 = mValue20;
}

// @ 0x00e07990
void cSPUILoyaltyMeter::Hide()
{
    if (mpLayout && mpLayout->IsVisible()) {
        mpLayout->SetVisibility(0);
        mValue24 = mValue20;
    }
}

} // namespace SP
