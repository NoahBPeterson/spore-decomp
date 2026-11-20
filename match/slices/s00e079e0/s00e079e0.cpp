// s00e079e0 -- default constructor of the SPUI loyalty meter widget: it runs the
// meter base constructor with a fixed layout name/ids, then rebinds the owner
// window to the window the base resolved and places the created meter window.
// Second (retail-only) copy of the meter family that the destructor at 0x00e07750,
// SetSpatialObject at 0x00e077d0 and UpdateRollover at 0x00e07850 belong to.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_0147f51c[];
extern "C" unsigned char g_0147f548[];

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// Refcounted interface handed back by the widget factory: AddRef = vt[0],
// Release = vt[1].
struct IFace {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
};

// A layout window.  Slot +0x10 is the decorator, +0x64 positions the window,
// +0xd8 attaches an owner and +0xdc attaches a child (the slots the meter calls).
struct IWindow {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void V08();                                 // +0x08
    virtual void V0c();                                 // +0x0c
    virtual IWindow* GetDecorator();                    // +0x10
    PV16 PV4                                            // 0x14 .. 0x60
    virtual void SetPosition(float fX, float fY);       // +0x64
    PV16 PV8 PV4                                        // 0x68 .. 0xd4
    virtual void AttachOwner(IWindow* pOwner);          // +0xd8
    virtual void AttachChild(IWindow* pChild);          // +0xdc
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t nID, bool bRecursive);   // 0x008105b0
};

// Two polymorphic roots, so the most derived object carries the primary table at
// +0x00 and the second base's table at +0x04 -- the two vtable stores this
// constructor and the destructor at 0x00e07750 make.
class cSPUIMeterBaseA {
public:
    virtual void V00();                                 // +0x00
    PV8                                                 // 0x04 .. 0x20
    ~cSPUIMeterBaseA() {}
};

class cSPUIMeterBaseB {
public:
    virtual void V00();                                 // +0x00
    ~cSPUIMeterBaseB() {}
};

class cSPUIMeter : public cSPUIMeterBaseA, public cSPUIMeterBaseB {
public:
    cSPUIMeter(int32_t nRootID, uint32_t nFlags, const wchar_t* pName,
               uint32_t nLayoutFlags);                  // 0x00e06790
    virtual void OnValueChanged();                      // +0x24
    virtual void OnLayoutChanged();                     // +0x28

    uint32_t     m_nFlags08;                            // +0x08
    bool         m_bRangeType;                          // +0x0c
    uint8_t      m_pad00d[3];                           // +0x0d
    cSPUILayout* mLayout;                               // +0x10
    void*        m_pSource;                             // +0x14
    uint32_t     m_nRootID;                             // +0x18
    uint32_t     m_nLayoutFlags;                        // +0x1c
    uint32_t     m_nStart;                              // +0x20
    uint32_t     m_nNext;                               // +0x24
};

// Widget factory: type id, rectangle, an out slot that receives the created
// window, two flags, a float and the shared layout type id.
extern IFace* CreateMeterWidget(const void* pType, float fX, float fY,
                                float fWidth, float fHeight, IWindow** ppOut,
                                int32_t nFlagA, int32_t nFlagB, float fValue,
                                uint32_t nTypeId);      // 0x008093b0

// The meter.  Layout as the destructor at 0x00e07750 and UpdateRollover at
// 0x00e07850 read it.
class cSPUILoyaltyMeter : public cSPUIMeter {
public:
    cSPUILoyaltyMeter();
    virtual void Update(int32_t nDelta, void* pMessage);

    IWindow* mpMeterWindow;                             // +0x28
    IFace*   mpOwnerWindow;                             // +0x2c
    IWindow* mpCreated;                                 // +0x30
};

// @ 0x00e079e0
cSPUILoyaltyMeter::cSPUILoyaltyMeter()
    : cSPUIMeter(0x26f1f20, 0x26e0df0, (const wchar_t*)g_0147f548, 0xe9f70df9)
    , mpMeterWindow(0)
    , mpOwnerWindow(0)
{
    // the original stores the three window slots first and only then reads
    // mLayout; the +0x30 slot keeps its address in a register across the read
    _ReadWriteBarrier();
    mpCreated = 0;
    _ReadWriteBarrier();

    if (mLayout != 0) {
        IWindow* pWindow = mLayout->FindWindowByID(m_nRootID, true);
        if (pWindow != 0) {
            if (mpCreated != 0) {
                IWindow* pOld = mpCreated;
                mpCreated = 0;
                pOld->Release();
            }

            IFace* pNew = CreateMeterWidget((const void*)g_0147f51c, 0.0f, 0.0f, 1.0f,
                                            1.0f, &mpCreated, 1, 1, 0.0f,
                                            (uint32_t)0xe9f70df9);
            IFace* pOldOwner = mpOwnerWindow;
            if (pNew != pOldOwner) {
                if (pNew != 0)
                    pNew->AddRef();
                mpOwnerWindow = pNew;
                if (pOldOwner != 0)
                    pOldOwner->Release();
            }

            if (pWindow->GetDecorator() != 0)
                pWindow->GetDecorator()->AttachChild(pWindow);

            mpCreated->AttachOwner(pWindow);
            pWindow->SetPosition(0.0f, 0.0f);
        }
    }
}
