// Slice s00cd68d0 - SporeApp 0x00cd68d0
// SP::cTribeModeStrategy teardown/cleanup helper.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <intrin.h>

typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cSPTimer {
    void Reset();                       // 0x00bc3170
};

// An object released through its virtual table (slot 1 and slot 3).  The slots are spelled
// without overloads: MSVC moves overloaded virtuals out of declaration order, which shifted
// the calls to +4/+8 instead of +0xc/+4.
struct cRefObj {
    virtual void v00();                 // 0x00
    virtual void Release();             // 0x04
    virtual void v02();                 // 0x08
    virtual void ReleaseWith(int flags); // 0x0c
};

struct cHintMgr {
    void Shutdown();                    // 0x0067a120
};

struct cAimSource {
    void Stop(int);                     // 0x00b33ce0
    void Clear(int);                    // 0x00b33cf0
};

struct cCameraCtl {
    u8   mPad000[0x390];
    bool mFlag390;                      // 0x390
};

extern "C" cCameraCtl*  GetCameraCtl();     // 0x00b3d280
extern "C" cAimSource*  GetAimSource();     // 0x00b3d240

// ---------------------------------------------------------------------------------------------
// SP::cTribeModeStrategy
// ---------------------------------------------------------------------------------------------
struct cTribeModeStrategy {
    u8            mPad000[0x1a8];
    cSPTimer      mTimer;               // 0x1a8
    u8            mPad1a9[0x24a - 0x1a9];
    bool          mFlag24a;             // 0x24a
    u8            mPad24b[0x250 - 0x24b];
    cRefObj*      mObj250;              // 0x250
    u8            mPad254[0x398 - 0x254];
    cRefObj*      mObj398;              // 0x398

    cHintMgr* GetHintMgr();             // 0x0067caf0

    void Teardown();
};

// @ 0x00cd68d0
void cTribeModeStrategy::Teardown()
{
    GetHintMgr()->Shutdown();
    mTimer.Reset();

    if (GetCameraCtl())
        GetCameraCtl()->mFlag390 = false;

    if (mObj398 != 0) {
        mObj398->ReleaseWith(1);

        if (mObj398 != 0) {
            cRefObj* p = mObj398;
            mObj398 = 0;
            p->Release();
        }
    }

    GetAimSource()->Stop(0);
    GetAimSource()->Clear(0);

    if (GetCameraCtl())
        GetCameraCtl();

    mFlag24a = false;
    _ReadWriteBarrier();            // keep the flag store ahead of the mObj250 load

    if (mObj250) {
        cRefObj* q = mObj250;
        mObj250 = 0;
        q->Release();
    }
}
