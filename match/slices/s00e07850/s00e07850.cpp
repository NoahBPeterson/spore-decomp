// Slice s00e07850 -- SP::cSPUILoyaltyMeter rollover helper.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct IWin;
extern "C" bool UpdateRolloverFrameB(IWin* w, float a, float b, float c, float d, int e, float f); // 0x00808d40

namespace SP {

struct cSPUILayout {
    void* mpVtable;                                             // +0x00
    void* FindWindowByID(uint32_t id, int flag);                // 0x008105b0
};

struct cSPUILoyaltyMeter {
    void*        mpVtable;                                      // +0x00
    uint32_t     mPad04[3];                                     // +0x04 .. +0x0f
    cSPUILayout* mpLayout;                                      // +0x10
    uint32_t     mPad14;                                        // +0x14
    uint32_t     mRolloverId;                                   // +0x18
    uint32_t     mPad1c[3];                                     // +0x1c .. +0x27
    void*        mpMeterWindow;                                 // +0x28
    IWin*        mpOwnerWindow;                                 // +0x2c

    void UpdateRollover();
};

// @ 0x00e07850
void cSPUILoyaltyMeter::UpdateRollover()
{
    if (!mpLayout)
        return;
    if (!mpMeterWindow)
        return;

    IWin* target = (IWin*)mpLayout->FindWindowByID(mRolloverId, 1);
    if (!target)
        return;

    float rect[4];
    float* pr = ((float* (__thiscall*)(IWin*))((void**)*(void**)target)[0x38 / 4])(target);
    rect[0] = pr[0];
    rect[1] = pr[1];
    rect[2] = pr[2];
    rect[3] = pr[3];

    float out[2];
    if (!((bool (__thiscall*)(void*, int, float*))((void**)*(void**)((char*)mpMeterWindow + 0x34))[0x7c / 4])
            ((char*)mpMeterWindow + 0x34, 1, out))
        return;

    // both window pointers are read before the meter field query: retail loads them back to back
    // (mpMeterWindow to a scratch register, mpOwnerWindow into the saved `this` register)
    void* pMeter = mpMeterWindow;
    IWin* pOwner = mpOwnerWindow;
    float value = ((float (__thiscall*)(void*))((void**)*(void**)((char*)pMeter + 0x34))[0x70 / 4])
        ((char*)pMeter + 0x34);
    UpdateRolloverFrameB(pOwner, out[0], out[1], rect[2] - rect[0], rect[3] - rect[1], 1, value);
}

} // namespace SP
