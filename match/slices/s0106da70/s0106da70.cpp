// Slice s0106da70 -- SP::cSPUISpace constructor / destructor cluster.
//
// 0x0106da70 is the constructor of the cSPUISpace base sub-object (three inherited
// vftables at +0, +4, +0xc, an EA::Stopwatch, four EA messaging handlers);
// 0x0106db90 is its destructor, 0x0106e2d0/0x0106e380 the cSPUISpace
// constructor / deleting destructor, the rest are UI helpers of the same class.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

void operator_delete__(void* p);                                          // 0x00f47380
void EA_Messaging_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00571db0

// ---- intrusive pointer flavours ----
struct IRel1 { virtual void v0(); virtual void Release(); };              // Release at +4
struct IRel2 { virtual void v0(); virtual void v1(); virtual void Release(); };  // Release at +8

struct Arc1 { IRel1* p; Arc1() : p(0) {} ~Arc1() { if (p) p->Release(); } };
struct Arc2 { IRel2* p; Arc2() : p(0) {} ~Arc2() { if (p) p->Release(); } };

// EA messaging handler slot: handler pointer plus the four registration keys.
struct AutoHandler {
    void*    mpHandler;
    uint32_t mk1, mk2, mk3, mk4;
    AutoHandler() : mpHandler(0), mk1(0), mk2(0), mk3(0), mk4(0) {}
    ~AutoHandler()
    {
        if (mpHandler) {
            void* h = mpHandler;
            mpHandler = 0;
            EA_Messaging_RemoveHandler(h, mk1, mk2, mk3, mk4);
        }
    }
};

struct EAStopwatch {                                                       // EA::Stopwatch
    uint32_t md[9];
    EAStopwatch(int /*bStart*/, bool /*bReset*/);                          // 0x0093a560
};

struct ToolUiState {                                                       // 0x00..0x30
    uint32_t m0, m1, m2;
    ToolUiState() : m0(0), m1(0), m2(0) {}
    ~ToolUiState();                                                        // 0x0106cc00
};

struct cPlanet;

// ---- UI interfaces ----
struct IWindow {
    virtual void     v00();
    virtual void     v01();
    virtual void     v02();
    virtual IWindow* v0c(uint32_t id);                     // +0x0c
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();                                // +0x24
    virtual void     v28(int a, bool b);                   // +0x28
    virtual void     v2c();
    virtual void     v30();
    virtual void     v34(uint32_t id);                     // +0x34
    virtual bool     v38(uint32_t id);                     // +0x38
    virtual void     v3c();
    virtual void     v40();
    virtual void     v44();
    virtual void     v48();
    virtual void     v4c();
    virtual void     v50();
    virtual void     v54(const wchar_t* text);             // +0x54
    virtual void     v58();
    virtual void     v5c();
    virtual void     v60();
    virtual void     v64();
    virtual void     v68();
    virtual void     v6c();
    virtual void     v70();
    virtual void     v74();
    virtual void     v78();
    virtual void     v7c(bool show, bool flag);            // +0x7c
    virtual void     v80(const wchar_t* text);             // +0x80
    virtual void     v84();
    virtual void     v88();
    virtual void     v8c();
    virtual void     v90();                                // +0x90
};

struct cSPUIGlobalUI {
    IWindow* FindWindowByID(uint32_t id);                  // 0x00e012b0
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool searchChildren);   // 0x008105b0
};

// ---- 4-byte eastl deque (0x00502dd0 is its push_back slow path) ----
struct DeqNode {
    uint32_t*  mpCurrent;
    uint32_t*  mpBegin;
    uint32_t*  mpEnd;
    uint32_t** mpCurrentArrayPtr;
};

struct UIntDeque {
    uint32_t** mpPtrArray;
    int        mnPtrArraySize;
    DeqNode    mItBegin;
    DeqNode    mItEnd;

    void DoPushBackSlow(const uint32_t& value);            // 0x00502dd0

    __forceinline void push_back(const uint32_t& value)
    {
        uint32_t* pCurrent = mItEnd.mpCurrent;

        if ((pCurrent + 1) != mItEnd.mpEnd) {
            mItEnd.mpCurrent = pCurrent + 1;
            if (pCurrent)
                *pCurrent = value;
        } else {
            DoPushBackSlow(value);
        }
    }
};

// ---- eastl hash node / table ----
struct EaHashNode {
    uint32_t      mKey;
    void*         mpValue;
    EaHashNode*   mpNext;
};

struct EaHashTable {
    uint32_t      pad0;
    EaHashNode**  mpBuckets;
    uint32_t      mnBuckets;
    uint32_t      mnElements;

    void DoFreeNodes(EaHashNode** pBuckets, uint32_t nBuckets);   // 0x006b6570

    ~EaHashTable()
    {
        DoFreeNodes(mpBuckets, mnBuckets);
        mnElements = 0;
        if (mnBuckets > 1)
            operator_delete__(mpBuckets);
    }
};

// Same 20 bytes as an eastl hashtable, but this instance is never destroyed by cSPUISpace
// (retail's ??_G only tears down mToolStrategies), so it carries no destructor.
struct HashView {
    uint32_t      pad0;
    EaHashNode**  mpBuckets;
    uint32_t      mnBuckets;
    uint32_t      mnElements;
};

extern void* gOneBucket[1];                                // 0x0154df28

// ---- the base sub-object (ctor 0x0106da70, dtor 0x0106db90) ----
struct ITracerBase  { virtual ~ITracerBase() {} };         // vftable +0x00
struct CVSBase      { virtual ~CVSBase() {} uint32_t mValue; CVSBase() : mValue(0) {} };   // vftable +0x04, value +0x08
struct PaintBase    { virtual ~PaintBase() {} };           // vftable +0x0c

// @ 0x0106db90
// The destructor of this class is *implicit*: retail's ??1cSPUIBase@@UAE@XZ only destroys
// the members below and resets the three base vftables (it never stores its own vftable,
// which is what an explicit ~cSPUIBase() would emit), so it is generated from this
// class definition rather than written out.
class cSPUIBase : public ITracerBase, public CVSBase, public PaintBase {
public:
    uint32_t    m10, m14, m18;                    // 0x10
    Arc2        m1c;                              // 0x1c
    Arc1        m20, m24, m28, m2c;               // 0x20
    ToolUiState m30;                              // 0x30
    uint32_t    m3c, m40;                         // 0x3c (not initialised)
    uint32_t    m44, m48, m4c, m50, m54, m58, m5c, m60, m64, m68, m6c, m70, m74, m78, m7c;
    uint32_t    m80[17];                          // 0x80 (not initialised)
    uint32_t    mC4;                              // 0xc4 (not initialised)
    EAStopwatch mStopwatch;                       // 0xc8
    AutoHandler mHandler0;                        // 0xec
    AutoHandler mHandler1;                        // 0x100
    AutoHandler mHandler2;                        // 0x114
    AutoHandler mHandler3;                        // 0x128
    uint32_t    m13c;                             // 0x13c

    cSPUIBase();
};

// ---- cSPUISpace ----
// @ 0x0106e380
// Compiler-generated ??_GcSPUISpace@@UAEPAXI@Z: the class destructor is implicit too, so the
// scalar deleting destructor destroys the member hash table, calls the cSPUIBase destructor
// and then frees the object when the delete flag is set.
class cSPUISpace : public cSPUIBase {
public:
    EaHashTable mToolStrategies;                  // 0x140
    float       mf150;                            // 0x150
    float       mf154;                            // 0x154
    uint32_t    m158;                             // 0x158

    uint32_t       pad15c_178[7];                 // 0x15c .. 0x177
    cSPUILayout*   mpLayout;                      // 0x178
    uint32_t       pad17c_224[0x2a];              // 0x17c .. 0x223
    cSPUIGlobalUI* mpGlobalUI;                    // 0x224
    uint32_t       pad228_23c[5];                 // 0x228 .. 0x23b
    uint32_t       m23c;                          // 0x23c
    uint32_t*      mpIdsBegin;                    // 0x240
    uint32_t*      mpIdsEnd;                      // 0x244
    uint32_t*      mpIdsCap;                      // 0x248
    uint32_t       pad24c_25c[4];                 // 0x24c .. 0x25b
    HashView       mHash25c;                      // 0x25c
    uint32_t       pad26c_27c[4];                 // 0x26c .. 0x27b
    uint32_t*      mpSortedBegin;                 // 0x27c
    uint32_t*      mpSortedEnd;                   // 0x280
    uint32_t       pad284_594[0xc4];              // 0x284 .. 0x593
    IWindow*       mpActiveWindow;                // 0x594
    uint32_t       pad598_5a8[4];                 // 0x598 .. 0x5a7
    IWindow*       mpTipWindow;                   // 0x5a8
    uint32_t       pad5ac_5d8[0xb];               // 0x5ac .. 0x5d7
    uint32_t*      mpIdArray;                     // 0x5d8
    uint32_t*      mpIdArrayEnd;                  // 0x5dc
    uint32_t       pad5e0_5ec[3];                 // 0x5e0 .. 0x5eb
    UIntDeque      mToolWindowDeque;              // 0x5ec

    cSPUISpace();

    void UpdateTravelLine(int mode);                          // 0x0106cc70
    void UpdatePlanetRollover(cPlanet* pPlanet);              // 0x0106ba00
    void UpdateStarMapFilters();                              // 0x01068140
    void ToggleToolUI(uint32_t id);                           // 0x0106e3e0
    void FUN_0106aa10(bool b);
    void PushToolWindowId(uint32_t id);                       // 0x0106dcd0
    void FUN_0106dd10(uint32_t index, uint32_t value);
    void AddCursors();                                        // 0x0106e020
    void OnContextDeactivate();                               // 0x0106e270
    void FUN_0106e5e0();
    void FUN_0106e630();
    void FUN_0106e680(uint32_t id);
    void SetToolTipForItem(uint32_t toolId, void* pItem);     // 0x0106e720
    void FUN_0106e940(uint32_t index);
};

// @ 0x0106da70
cSPUIBase::cSPUIBase()
    : m10(0), m14(0), m18(0),
      m44(0), m48(0), m4c(0), m50(0), m54(0), m58(0), m5c(0), m60(0), m64(0),
      m68(0), m6c(0), m70(0), m74(0), m78(0), m7c(0),
      mStopwatch(0, false)
{
}



// @ 0x0106dcd0
void cSPUISpace::PushToolWindowId(uint32_t id)
{
    mToolWindowDeque.push_back(id);
}

// @ 0x0106dd10
void cSPUISpace::FUN_0106dd10(uint32_t index, uint32_t value)
{
    IWindow* pWindow;

    if (mpLayout == 0)
        return;

    pWindow = mpGlobalUI->FindWindowByID(value);
    if (pWindow == 0)
        return;

    if (index == 0)
        m23c = value;
    else
        mpIdsBegin[index] = value;
}

// @ 0x0106e020
void cSPUISpace::AddCursors()
{
    uint32_t i;

    for (i = 0; i < (uint32_t)(mpIdsEnd - mpIdsBegin); ++i) {
        if (mpIdsBegin[i] == m23c) {
            mpIdsBegin[i] = mpIdsBegin[(i + 1) % (uint32_t)(mpIdsEnd - mpIdsBegin)];
        }
    }
}

// @ 0x0106e270
void cSPUISpace::OnContextDeactivate()
{
    IWindow* pWindow;

    UpdateTravelLine(0);
    UpdatePlanetRollover(0);

    pWindow = mpGlobalUI->FindWindowByID(0x2c38ab9);
    if (pWindow)
        pWindow->v7c(true, false);

    pWindow = mpActiveWindow;
    if (pWindow)
        pWindow->v0c(1);
}

// @ 0x0106e2d0
cSPUISpace::cSPUISpace() : mf150(1.0f), mf154(2.0f)
{
    mToolStrategies.mnElements = 0;
    m158 = 0;
    mToolStrategies.mnBuckets = 1;
    mToolStrategies.mpBuckets = (EaHashNode**)gOneBucket;
}

// @ 0x0106e3e0
void cSPUISpace::ToggleToolUI(uint32_t id)
{
    IWindow* pPanel = mpGlobalUI->FindWindowByID(0x453ef531);

    if (pPanel)
        pPanel = pPanel->v0c(0x8ed27e7a);
    pPanel->v28(4, true);

    UpdateStarMapFilters();

    if (id == m23c)
        return;

    if (m23c != 0) {
        IWindow* pOld;

        pOld = mpGlobalUI->FindWindowByID(m23c);
        pOld->v7c(true, false);
        pOld = mpGlobalUI->FindWindowByID(m23c - 0x10);
        if (pOld)
            pOld = pOld->v0c(0x8ed27e7a);
        pOld->v28(4, false);
    }

    m23c = id;

    if (id != 0) {
        IWindow* pNew;

        pNew = mpGlobalUI->FindWindowByID(id);
        pNew->v7c(true, true);
        pNew = mpGlobalUI->FindWindowByID(id - 0x10);
        if (pNew)
            pNew = pNew->v0c(0x8ed27e7a);
        pNew->v28(4, true);
    }

    FUN_0106aa10(mpSortedEnd != mpSortedBegin &&
                 m23c <= mpSortedEnd[-1]);
}

// @ 0x0106e5e0
void cSPUISpace::FUN_0106e5e0()
{
    uint32_t count = (uint32_t)(mpIdsEnd - mpIdsBegin);
    uint32_t next = 0;
    uint32_t i;

    if (count != 0) {
        const uint32_t* pIds = mpIdsBegin;
        uint32_t pivot = m23c;

        for (i = 0; i < count; ++i) {
            if (pIds[i] == pivot)
                next = pIds[(i + 1) % count];
        }
    }
    ToggleToolUI(next);
}

// @ 0x0106e630
void cSPUISpace::FUN_0106e630()
{
    uint32_t count = (uint32_t)(mpIdsEnd - mpIdsBegin);
    uint32_t next = 0;
    uint32_t i;

    if (count != 0) {
        const uint32_t* pIds = mpIdsBegin;
        uint32_t pivot = m23c;

        for (i = 0; i < count; ++i) {
            if (pIds[i] == pivot)
                next = pIds[(count - 1 + i) % count];
        }
    }
    ToggleToolUI(next);
}

// @ 0x0106e680
void cSPUISpace::FUN_0106e680(uint32_t id)
{
    EaHashNode** pBucket = mHash25c.mpBuckets;
    EaHashNode*  pNode = *pBucket;
    EaHashNode*  pEnd = mHash25c.mpBuckets[mHash25c.mnBuckets];

    if (pNode == 0) {
        do
            ++pBucket;
        while (*pBucket == 0);
        pNode = *pBucket;
    }

    while (pNode != pEnd) {
        IWindow* pWindow = (IWindow*)pNode->mpValue;

        if (pWindow->v38(id)) {
            uint32_t key = pNode->mKey;

            if (key != 0) {
                ToggleToolUI(key);
                pWindow->v34(id);
            }
            return;
        }

        pNode = pNode->mpNext;
        if (pNode == 0) {
            do
                ++pBucket;
            while (*pBucket == 0);
            pNode = *pBucket;
        }
    }
}

// @ 0x0106e720
void cSPUISpace::SetToolTipForItem(uint32_t toolId, void* pItem)
{
    if (pItem == 0) {
        if (mpTipWindow)
            mpTipWindow->v00();
        return;
    }
}

// @ 0x0106e940
void cSPUISpace::FUN_0106e940(uint32_t index)
{
    if (index >= (uint32_t)(mpIdArrayEnd - mpIdArray))
        return;

    mpIdArray[index] = index;
}
