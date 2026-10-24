// slice s00f38330 -- Simulator / cSPUISpace UI-object helpers (0x00f38330..0x00f39220).
//
// cSPUISpace "seti" panel: object create/destroy, message handling, a 4-digit
// clock display, a cCivTokenTranslator and its string members.  Module flags
// /O2 /MD /Gy /TP.
#include "types.h"

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;

void  EAFree(void* p);                                                            // 0x00F47380
void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00F473A0
void* __cdecl operator_new(int n, const char* name, int a, int b, int c, int d);   // 0x00F473A0
void  __cdecl operator_del(void* p);                                              // 0x00F47380

// Names handed to the EA allocator by the UI objects in this slice.
static const char* const kpUIAllocName = (const char*)0x013F6B3C;

// ---------------------------------------------------------------------------
// Virtual dispatch.  Every UI object in this slice is called through its
// vtable with the receiver in ecx, so the slot wrappers use __thiscall.
// ---------------------------------------------------------------------------
typedef void  (__thiscall *TV0)(void*);                     // slot()
typedef void* (__thiscall *TV0i)(void*, int);               // slot(int) -> void*
typedef int   (__thiscall *TV0r)(void*);                    // slot() -> int
typedef void* (__thiscall *TV0p)(void*);                    // slot() -> void*
typedef void  (__thiscall *TV1p)(void*, void*);             // slot(void*)
typedef void  (__thiscall *TV2ii)(void*, int, int);         // slot(int, int)
typedef char  (__thiscall *TV1p_c)(void*, void*);           // slot(void*) -> bool
typedef void  (__thiscall *TV3)(void*, int, void*, int);    // slot(int, void*, int)
typedef void* (__thiscall *TV1f)(void*, float);             // slot(float) -> void*
typedef void* (__thiscall *TV2f)(void*, float, float);      // slot(float, float) -> void*
typedef void* (__thiscall *TV1p_p)(void*, void*);           // slot(void*) -> void*
typedef float (__thiscall *TVf)(void*);                     // slot() -> float

template <class T> static inline T Slot(void* pObj, int nOffset)
{
    return (T)(*(void**)((char*)*(void**)pObj + nOffset));
}

static inline void CallSlot0(void* pObj, int nOffset)
{
    Slot<TV0>(pObj, nOffset)(pObj);
}
static inline void CallSlot1(void* pObj, int nOffset, void* pArg)
{
    Slot<TV1p>(pObj, nOffset)(pObj, pArg);
}
static inline void CallSlot1i(void* pObj, int nOffset, int nArg)
{
    Slot<TV0i>(pObj, nOffset)(pObj, nArg);
}

// AddRef (+0x00) / Release (+0x04) on the reference-counted UI objects.
static inline void AddRefObj(void* pObj)  { CallSlot0(pObj, 0x00); }
static inline void ReleaseObj(void* pObj) { CallSlot0(pObj, 0x04); }

// "new == AddRef(slotN), old == Release(slotM)" pointer assignment used by
// every UI field of this slice.
static inline void AssignObj(void** ppField, void* pNew, int nAddSlot, int nRelSlot)
{
    void* pOld = *ppField;
    if (pNew == pOld)
        return;
    if (pNew != 0)
        CallSlot0(pNew, nAddSlot);
    *ppField = pNew;
    if (pOld != 0)
        CallSlot0(pOld, nRelSlot);
}

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t, eastl::allocator> (empty-string shared buffer).
// ---------------------------------------------------------------------------
extern wchar_t gEmptyString16[];       // 0x01667BAC
struct TWString16 {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCap;      // +0x08
    void InitEmpty()
    {
        mpBegin = gEmptyString16;
        mpEnd   = gEmptyString16;
        mpCap   = gEmptyString16 + 1;
    }
    void Release()
    {
        // capacity sentinel is one wchar past the shared empty buffer; the size is
        // masked to an even byte count and compared *signed* (retail uses jle).
        if (((char*)mpCap - (char*)mpBegin & ~1) > 2 && mpBegin != 0)
            EAFree(mpBegin);
    }
};
void __cdecl WStrFormat(TWString16* pOut, const wchar_t* pFmt, int nValue);   // 0x0041E050

// ---------------------------------------------------------------------------
// Free callees (signatures from the retail call sites).
// ---------------------------------------------------------------------------
extern void* g_15ad298;                     // 0x015ad298: UI system object pointer

void  __cdecl   FUN_00f373a0(int, int, void*, int, float, float);
void  __cdecl   FUN_00f372b0(int, int, int, float);
void* __cdecl   FUN_00b18e00(void*);
char  __cdecl   FUN_00edc9e0(void*, int);
int   __cdecl   FUN_00435e90();             // GetRecorderState
void  __cdecl   KillSetiEffects(int nEffect, int nValue);            // 0x00435ED0
void* __cdecl   AudioGetSystemAT();                                  // 0x00A206F0
void* __cdecl   WindowManager();                                     // 0x0067CAA0
void* __cdecl   MessageServer();                                     // 0x0067DCC0
void* __cdecl   CenterWindowInRect();                                // 0x00810000 (layout ctor)
void  __cdecl   EA_Messaging_RemoveHandler(int, int, int, int, int); // 0x00571DB0
char  __cdecl   FUN_005bf0e0(const void* pKey, void** ppList);       // 0x005BF0E0
char  __cdecl   FUN_005bf1e0(void* pList, void** ppItems);           // 0x005BF1E0

struct cSPUILayout {
    cSPUILayout* ctor();                                    // 0x00810000
    char  Init(const void* pKey, char bFlag, int nFlags);   // 0x008120D0
    char  SetParentWin(void* pParent, char bFlag, int nFlags); // 0x008121B0
    void* FindWindowByID(int nID, char bFlag);              // 0x008105B0
    void  Shutdown(unsigned int nFlags);                    // 0x00811AD0
    char  mPad00[0x18];
};

struct cCollectableItems {
    void  Load(const void* pKey);                           // 0x00595A90
    unsigned char GetValue(unsigned char* pOut);            // 0x00595230
};

struct cMessageServer {
    void Send(int nID, void* pMessage, int nFlags);         // +0x14
    void RegisterHandler(void* pHandler, int nID);          // +0x24
};

struct cAutoRefVec {                    // eastl::vector<EA::AutoRefCount<T>>
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCap;      // +0x08
    void DoInsertPtr(void** pPos, const void** pValue);     // 0x00AEA5D0
    void erase(void** pFirst, void** pLast);                // 0x00E25BD0
    void Clear();                                           // 0x00AE6970 (~vector)
};

struct cBehaviorMessage {              // SP::MessageBasicRC<5> (0x40 bytes)
    void*    mpVtbl;      // +0x00
    volatile int mnRefCount; // +0x04
    void*    mpData0;     // +0x08
    char     mPad0c[0x24];
    int      mnID;        // +0x30
    int      mPad34;
    int      mnFlags;     // +0x38
    char     mPad3c[4];
};
void  __cdecl MessageSetIRefCount(cBehaviorMessage* p, int nCount, void* pOwner); // 0x005726E0

// ---------------------------------------------------------------------------
// Matrix / transform helpers used by 0x00f38330.
// ---------------------------------------------------------------------------
struct Matrix33 {
    float m[9];
    void Assign(const void* pSource);           // 0x0041CB40 (Matrix3::Assign)
};
struct cSPTransformOps {
    uint16_t mFlags;      // +0x00  component mask (4 = rotation axis, 2 = matrix)
    uint16_t mCount;      // +0x02  component count
    int      mAxis[3];    // +0x04
    float    mScale;      // +0x10
    Matrix33 mMatrix;     // +0x14
    cSPTransformOps* Assign(const void* pSource);   // 0x00537DC0
};
float* __cdecl Matrix3FromQuaternion(Matrix33* pOut, const void* pQuat);   // 0x0059C190

// ---------------------------------------------------------------------------
// Member contexts.
// ---------------------------------------------------------------------------
struct Ctx { void f32bf0(int); void f37b60(); };
struct SpaceObj {
    int  f385a0(int k); int f38890(char del); int f38b30(int k);
    void f38b60(int v); void f38b90(int v); void f38bc0(int v);
    int  f38d70(char del); char f38e80(int* win); char f38930(int msg, int* d);
    void f38ac0(char show); char f38d90(int msg, void* d); void f388b0(int v);
    void f38330(char bRefresh);
    void PublishProperties();      // 0x00F32D10
    void RefreshProperties();      // 0x00F37B60
    void f373a0(int nID, int nZero, void* pA, void* pB);  // 0x00F373A0
    void f372b0(int nID, void* pMesh);                    // 0x00F372B0
};
struct BaseTranslator {
    void ctor();   // 0x00B32470
    void dtor();   // 0x00B32490
};

// Vtables of the UI objects, stored verbatim (they live in the retail image).
static void* const kpSetiVtbl0        = (void*)0x0148D0BC;
static void* const kpSetiVtbl4        = (void*)0x0148D0AC;
static void* const kpBaseVtbl4        = (void*)0x013EC458;
static void* const kpBaseVtbl0DTor    = (void*)0x013EB938;
static void* const kpBigVtbl0         = (void*)0x0148D114;
static void* const kpBigVtbl4         = (void*)0x0148D0F8;
static void* const kpBigVtbl8         = (void*)0x0148D0E8;
static void* const kpBigBaseVtbl4     = (void*)0x014426A0;
static void* const kpBigBaseVtbl0DTor = (void*)0x013EB394;
static void* const kpTranslatorVtbl   = (void*)0x0148D140;
static void* const kpBigHandler       = (void*)0x0148D134;

// UI keys / ids.
static const void* const kpSetiLayoutKey = (const void*)0x015B01BC;
static const void* const kpAssetLayoutKey = (const void*)0x015B01E8;
static const int  knUIKeyFlags = 0x5b598fa;
static const int  knWindowA = 0x7c3eca1;
static const int  knWindowB = 0x7c3ed43;
static const int  knWindowC = 0x7c3edb7;
static const int  knDigitBase = 0x7c40930;
static const int  knBehaviorID = 0x7c41aea;
static const int  knToggleID = 0x7c41aeb;
static const int  knValueMessage = 0x7c41ae9;

// ===========================================================================
// 0x00f38330 -- per-tile transform / mesh update
// ===========================================================================
// The +0x1b0 tile record and the two node objects it points at.
struct TileNode {                       // *(tile+4)
    char mPad00[0x30];
    int  mnID;         // +0x30
    char mPad34[0x24];
    float mfOffsetA;   // +0x58  unblended offset
    float mfOffsetB;   // +0x5c  blended offset
    float mfHeightA;   // +0x60  unblended height
    float mfHeightB;   // +0x64  blended height
    char mbFlat;       // +0x68
};
struct TileRecord {                     // *(this+0x1b0)
    void* mpMesh;       // +0x00
    TileNode* mpNode;   // +0x04
    int   mnIndex;      // +0x08
    float mfBlend;      // +0x0c
};
struct TileMeshView {                    // object returned by FUN_00b18e00
    char mPad00[0x60];
    float mfTop;        // +0x60
    float mfBottom;     // +0x64
};
struct TileObject {                      // the simulated tile object
    char  mPad00[0x28];
    void* mpTransforms;      // +0x28
    char  mPad2c[0x10];
    void* mpHeights;         // +0x3c
    char  mPad40[0x74];
    void* mpShadowTransforms; // +0xb4
    char  mPadB8[0xf8];
    TileRecord* mpTile;      // +0x1b0
    char  mbShadowed;        // +0x1b8
    char  mPadB9;
    char  mbUpdated;         // +0x1ba
};

// @ 0x00f38330
void SpaceObj::f38330(char bRefresh)
{
    TileObject* pThis = (TileObject*)this;
    TileRecord* pTile = pThis->mpTile;
    if (pTile == 0)
        return;
    TileMeshView* pMeshA = (TileMeshView*)FUN_00b18e00(pTile->mpMesh);
    int           nIndex = pTile->mnIndex;
    TileMeshView* pMeshB = (TileMeshView*)FUN_00b18e00(pTile->mpMesh);

    TileNode* pNode   = pTile->mpNode;
    float     fHeight = pNode->mfHeightA;
    float     fScale  = Slot<TVf>(pMeshB, 0x34)(pMeshB);
    fHeight = (pNode->mfHeightB - fHeight) * (fScale - 3.0f) + fHeight;

    float fOffset = pNode->mfOffsetA;
    fOffset = (pNode->mfOffsetB - fOffset) * pTile->mfBlend + fOffset;

    if (pThis->mbShadowed == 0) {
        cSPTransformOps op;
        op.mMatrix.Assign((const void*)0x016C8538);
        void* pAxis = Slot<TV0p>(pMeshA, 0x2c)(pMeshA);
        op.mAxis[0] = ((int*)pAxis)[0];
        op.mAxis[1] = ((int*)pAxis)[1];
        op.mAxis[2] = ((int*)pAxis)[2];
        op.mFlags |= 4;
        op.mCount += 1;
        void* pQuat = Slot<TV0p>(pMeshA, 0x30)(pMeshA);
        Matrix3FromQuaternion(&op.mMatrix, pQuat);
        op.mFlags |= 2;
        op.mCount += 2;
        op.mScale = fHeight;
        if (pNode->mbFlat == 0) {
            ((cSPTransformOps*)((char*)pThis->mpTransforms + nIndex * 0x38))->Assign(&op);
            *(float*)((char*)pThis->mpHeights + nIndex * 4) = fOffset;
        } else {
            ((cSPTransformOps*)((char*)pThis->mpShadowTransforms + nIndex * 0x38))->Assign(&op);
        }
    } else {
        int nID = pNode->mnID;
        if (pNode->mbFlat == 0) {
            void* pA = Slot<TV2f>(pMeshA, 0x30)(pMeshA, fHeight, fOffset);
            void* pB = Slot<TV1p_p>(pMeshA, 0x2c)(pMeshA, pA);
            f373a0(nID, 0, pB, pA);
        } else {
            void* pA = Slot<TV1f>(pMeshA, 0x30)(pMeshA, fHeight);
            void* pB = Slot<TV1p_p>(pMeshA, 0x2c)(pMeshA, pA);
            f372b0(nID, pB);
        }
    }
    PublishProperties();
    pThis->mbUpdated = 1;
    if (bRefresh)
        RefreshProperties();
}

// ===========================================================================
// 0x00f38540 / 0x00f38570 -- close a sub-window and refresh
// ===========================================================================
struct V20 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
             virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
             virtual void q(int); };
void __fastcall FUN_00f38540(int* self) {
    int v = *(int*)((char*)self + 0xc);
    ((V20*)g_15ad298)->q(0);
    (*(Ctx**)((char*)self + 0x3c))->f32bf0(v);
    return (*(Ctx**)((char*)self + 0x3c))->f37b60();
}
void __fastcall FUN_00f38570(int* self) {
    int v = *(int*)((char*)self + 0x24);
    ((V20*)g_15ad298)->q(0);
    (*(Ctx**)((char*)self + 0x3c))->f32bf0(v);
    return (*(Ctx**)((char*)self + 0x3c))->f37b60();
}

// ===========================================================================
// 0x00f385a0 -- query-interface style filter
// ===========================================================================
int SpaceObj::f385a0(int k) {
    int self = (int)this;
    if (k == (int)0xee3f516e || k == 0x7c3ea9f) return self;
    return self & ((k != 0x2f009dd0) - 1);
}

// ===========================================================================
// 0x00f385d0 -- construct the seti panel object (0x2c bytes, two vtables)
// ===========================================================================
struct SetiPanel {
    void* mpVtbl0;      // +0x00
    void* mpVtbl4;      // +0x04
    void* mpField08;    // +0x08
    void* mpParentWin;  // +0x0c
    void* mpChildA;     // +0x10
    void* mpChildB;     // +0x14
    void* mpChildC;     // +0x18
    int   mnValue;      // +0x1c
    int   mnMax;        // +0x20
    char  mbVisible;    // +0x24
    char  mPad25[3];
    void* mpLayout;     // +0x28
};
// @ 0x00f385d0
SetiPanel* __fastcall FUN_00f385d0(SetiPanel* p)
{
    *(void* volatile*)&p->mpVtbl4 = kpBaseVtbl4;   // base-class constructor vptr
    p->mpField08  = 0;
    p->mpVtbl0    = kpSetiVtbl0;
    p->mpVtbl4    = kpSetiVtbl4;
    p->mpParentWin = 0;
    p->mpChildA   = 0;
    p->mpChildB   = 0;
    p->mpChildC   = 0;
    p->mpLayout   = 0;
    return p;
}

// ===========================================================================
// 0x00f38600 -- adjustor thunk (derived -> base at -4)
// ===========================================================================
int __fastcall FUN_00f38600(int p) { return p; }

// ===========================================================================
// 0x00f38610 -- destruct the seti panel object
// ===========================================================================
// @ 0x00f38610
void __fastcall FUN_00f38610(SetiPanel* p)
{
    p->mpVtbl0 = kpSetiVtbl0;
    p->mpVtbl4 = kpSetiVtbl4;
    if (p->mpLayout)   CallSlot0(p->mpLayout, 0x08);
    if (p->mpChildC)   ReleaseObj(p->mpChildC);
    if (p->mpChildB)   ReleaseObj(p->mpChildB);
    if (p->mpChildA)   ReleaseObj(p->mpChildA);
    if (p->mpParentWin) ReleaseObj(p->mpParentWin);
    p->mpVtbl0 = kpBaseVtbl0DTor;
    p->mpVtbl4 = kpBaseVtbl4;
}

// ===========================================================================
// 0x00f38680 -- initialise the seti panel layout
// ===========================================================================
// @ 0x00f38680
char __fastcall FUN_00f38680(SetiPanel* p, int, void* pParentWin, int nMax)
{
    AssignObj(&p->mpParentWin, pParentWin, 0x00, 0x04);

    p->mbVisible = 0;
    p->mnValue   = 0;
    p->mnMax     = nMax;

    if (p->mpParentWin == 0)
        return 1;

    void* pMem = operator_new(0x18, kpUIAllocName, 0, 0, 0, 0);
    void* pLayout = pMem ? ((cSPUILayout*)pMem)->ctor() : 0;
    AssignObj(&p->mpLayout, pLayout, 0x04, 0x08);

    cSPUILayout* pWin = (cSPUILayout*)p->mpLayout;
    if (!pWin->Init(kpSetiLayoutKey, 0, knUIKeyFlags)) {
        pWin->Shutdown(1);
        void* pOld = p->mpLayout;
        if (pOld != 0) {
            p->mpLayout = 0;
            CallSlot0(pOld, 0x08);
        }
        return 0;
    }

    pWin->SetParentWin(p->mpParentWin, 1, knUIKeyFlags);

    AssignObj(&p->mpChildA, pWin->FindWindowByID(knWindowA, 1), 0x00, 0x04);
    AssignObj(&p->mpChildB, pWin->FindWindowByID(knWindowB, 1), 0x00, 0x04);
    AssignObj(&p->mpChildC, pWin->FindWindowByID(knWindowC, 1), 0x00, 0x04);

    for (int i = 0; i < 10; ++i) {
        void* pChild = pWin->FindWindowByID(i + knDigitBase, 1);
        if (pChild != 0) {
            pChild = pWin->FindWindowByID(i + knDigitBase, 1);
            Slot<TV2ii>(pChild, 0x7c)(pChild, 1, i <= p->mnMax);
        }
    }
    return 1;
}

// ===========================================================================
// 0x00f38850 -- shutdown the seti panel
// ===========================================================================
// @ 0x00f38850
void __fastcall FUN_00f38850(SetiPanel* p)
{
    CallSlot1i(p, 0x28, 0);                 // hide the panel
    if (p->mpParentWin != 0) {
        void* pOld = p->mpParentWin;
        p->mpParentWin = 0;
        ReleaseObj(pOld);
    }
    if (p->mpLayout != 0)
        ((cSPUILayout*)p->mpLayout)->Shutdown(1);
}

// ===========================================================================
// 0x00f38890 -- scalar deleting destructor
// ===========================================================================
int SpaceObj::f38890(char del) {
    int p = (int)this;
    FUN_00f38610((SetiPanel*)p);
    if (del & 1) operator_del((void*)p);
    return p;
}

// ===========================================================================
// 0x00f388b0 -- set the displayed number
// ===========================================================================
// @ 0x00f388b0
void SpaceObj::f388b0(int v)
{
    int self = (int)this;
    *(int*)(self + 0x1c) = v;
    if (*(int*)(self + 0x18)) {
        TWString16 strText;
        strText.InitEmpty();
        WStrFormat(&strText, (const wchar_t*)0x013F08B8, v);
        CallSlot1i(*(void**)(self + 0x18), 0x80, (int)strText.mpBegin);
        strText.Release();
    }
}

// ===========================================================================
// 0x00f38930 -- message handler
// ===========================================================================
struct SPUIMessage {
    char     mPad00[0x08];
    int      mnType;    // +0x08
    int      mnKey;     // +0x0c
};
// @ 0x00f38930
char SpaceObj::f38930(int msg, int* d)
{
    int self = (int)this;
    SPUIMessage* pMessage = (SPUIMessage*)d;
    if (pMessage->mnType == 0x1c) {
        if (pMessage->mnKey == 0) {
            void* pWindowManager = WindowManager();
            void* pWindow = Slot<TV0i>(pWindowManager, 0x48)(pWindowManager, 0);
            if (FUN_00edc9e0(pWindow, knWindowB) == 0 && *(int**)(self + 0x14) != 0) {
                Slot<TV2ii>(*(void**)(self + 0x14), 0x7c)(*(void**)(self + 0x14), 1, 0);
                *(char*)(self + 0x24) = 0;
                void* pAudio = AudioGetSystemAT();
                int nValue = pAudio ? Slot<TV0r>(pAudio, 0x20)(pAudio) : 0;
                KillSetiEffects(0xcc089e57, nValue);
            }
        }
    } else if (pMessage->mnType == 0x287259f6) {
        if (pMessage->mnKey == knWindowC) {
            if (*(int**)(self + 0x14) != 0) {
                bool bVisible = *(char*)(self + 0x24) == 0;
                Slot<TV2ii>(*(void**)(self + 0x14), 0x7c)(*(void**)(self + 0x14), 1, bVisible);
                *(char*)(self + 0x24) = bVisible;
                void* pAudio = AudioGetSystemAT();
                int nValue = pAudio ? Slot<TV0r>(pAudio, 0x20)(pAudio) : 0;
                KillSetiEffects(bVisible ? 0x6e64e21 : 0xcc089e57, nValue);
            }
            cMessageServer* pServer = (cMessageServer*)MessageServer();
            Slot<TV3>(pServer, 0x14)(pServer, knToggleID, *(void**)(self + 0xc), 0);
            return 1;
        }
        int nIndex = pMessage->mnKey - knDigitBase;
        if (nIndex >= 0 && nIndex <= *(int*)(self + 0x20)) {
            ((SpaceObj*)self)->f388b0(nIndex);
            if (*(int**)(self + 0x14) != 0) {
                Slot<TV2ii>(*(void**)(self + 0x14), 0x7c)(*(void**)(self + 0x14), 1, 0);
                *(char*)(self + 0x24) = 0;
            }
            int nState = FUN_00435e90();
            KillSetiEffects(0xe76c9b4f, nState);
            cMessageServer* pServer = (cMessageServer*)MessageServer();
            Slot<TV3>(pServer, 0x14)(pServer, knBehaviorID, *(void**)(self + 0xc), 0);
            return 0;
        }
    }
    return 0;
}

// ===========================================================================
// 0x00f38ac0 -- show / hide the panel
// ===========================================================================
// @ 0x00f38ac0
void SpaceObj::f38ac0(char show)
{
    int self = (int)this;
    if (show)
        ((SpaceObj*)self)->f388b0(*(int*)(self + 0x1c));
    if (*(int*)(self + 0x28) != 0) {
        int nSlot = show ? 0x104 : 0x108;
        if (*(int**)(self + 0x18) != 0)
            Slot<TV1p>(*(void**)(self + 0x18), nSlot)(*(void**)(self + 0x18), (void*)self);
        if (*(int**)(self + 0x14) != 0)
            Slot<TV1p>(*(void**)(self + 0x14), nSlot)(*(void**)(self + 0x14), (void*)self);
    }
}

// ===========================================================================
// 0x00f38b30 -- query-interface style filter (variant)
// ===========================================================================
int SpaceObj::f38b30(int k) {
    int self = (int)this;
    if (k != (int)0xee3f516e) {
        if (k == 0x7c3e995) return self - 4;
        if (k != 0x2f009dd0) return 0;
    }
    return -(int)(self != 4) & self;
}

// ===========================================================================
// 0x00f38b60 / 0x00f38b90 -- broadcast to child widgets
// ===========================================================================
struct V28 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
             virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
             virtual void p8(); virtual void p9(); virtual void q(int); };
struct V24v { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual void q(int); };
void SpaceObj::f38b60(int v) {
    int self = (int)this;
    int* p = *(int**)(self + 0x2c);
    if (p == *(int**)(self + 0x30)) return;
    do { ((V28*)*p)->q(v); p++; } while (p != *(int**)(self + 0x30));
}
void SpaceObj::f38b90(int v) {
    int self = (int)this;
    int* p = *(int**)(self + 0x2c);
    if (p == *(int**)(self + 0x30)) return;
    do { ((V24v*)*p)->q(v); p++; } while (p != *(int**)(self + 0x30));
}

// ===========================================================================
// 0x00f38bc0 -- set a hh:mm clock from a second count
// ===========================================================================
// @ 0x00f38bc0
void SpaceObj::f38bc0(int v) {
    int self = (int)this;
    if (((*(int*)(self + 0x30) - *(int*)(self + 0x2c)) & 0xfffffffc) != 0x10)
        return;
    int* pDigits = *(int**)(self + 0x2c);
    int nSeconds = v % 0x3c;
    int nMinutes = v / 0x3c;
    ((SpaceObj*)pDigits[0])->f388b0(nSeconds % 10);
    ((SpaceObj*)pDigits[1])->f388b0(nSeconds / 10);
    ((SpaceObj*)pDigits[2])->f388b0(nMinutes % 10);
    ((SpaceObj*)pDigits[3])->f388b0(nMinutes / 10);
}

// ===========================================================================
// 0x00f38c70 -- construct the large-asset-view object (0x44 bytes, three vtables)
// ===========================================================================
struct BigAssetView {
    void* mpVtbl0;       // +0x00
    void* mpVtbl4;       // +0x04
    void* mpVtbl8;       // +0x08
    char  mPad0c[0x04];
    void* mpParentWin;   // +0x10
    void* mpLayout;      // +0x14
    void* mpServer;      // +0x18
    void* mpHandler;     // +0x1c
    void* mpHandlerData; // +0x20
    int   mnHandlerArg;  // +0x24
    int   mnHandlerArg2; // +0x28
    cAutoRefVec mChildren; // +0x2c
    int   mPad38;        // +0x38
    int   mPad3c;        // +0x3c
    void* mpExtra;       // +0x40
};
// @ 0x00f38c70
BigAssetView* __fastcall FUN_00f38c70(BigAssetView* p)
{
    *(void* volatile*)&p->mpVtbl4 = kpBigBaseVtbl4;   // base-class constructor vptrs
    *(void* volatile*)&p->mpVtbl8 = kpBaseVtbl4;
    void* pNull = 0;
    *(int*)p->mPad0c = (int)pNull;
    p->mpVtbl0 = kpBigVtbl0;
    p->mpVtbl4 = kpBigVtbl4;
    p->mpVtbl8 = kpBigVtbl8;
    p->mpParentWin  = pNull;
    p->mpLayout     = pNull;
    p->mpServer     = pNull;
    p->mpHandler    = pNull;
    p->mpHandlerData = pNull;
    p->mnHandlerArg  = (int)pNull;
    p->mnHandlerArg2 = (int)pNull;
    p->mChildren.mpBegin = (void**)pNull;
    p->mChildren.mpEnd   = (void**)pNull;
    p->mChildren.mpCap   = (void**)pNull;
    // +0x38 / +0x3c are left uninitialised by the original constructor
    p->mpExtra = 0;
    return p;
}

// ===========================================================================
// 0x00f38cc0 / 0x00f38cd0 -- adjustor thunks
// ===========================================================================
int __fastcall FUN_00f38cc0(int p) { return p; }
int __fastcall FUN_00f38cd0(int p) { return p; }

// ===========================================================================
// 0x00f38ce0 -- destruct the large-asset-view object
// ===========================================================================
// @ 0x00f38ce0
void __fastcall FUN_00f38ce0(BigAssetView* p)
{
    p->mpVtbl0 = kpBigVtbl0;
    p->mpVtbl4 = kpBigVtbl4;
    p->mpVtbl8 = kpBigVtbl8;
    if (p->mpExtra) ReleaseObj(p->mpExtra);
    p->mChildren.Clear();
    if (p->mpServer != 0) {
        void* pHandler = p->mpServer;
        p->mpServer = 0;
        EA_Messaging_RemoveHandler((int)pHandler, (int)p->mpHandler, (int)p->mpHandlerData,
                                   p->mnHandlerArg, p->mnHandlerArg2);
    }
    if (p->mpLayout)    CallSlot0(p->mpLayout, 0x08);
    if (p->mpParentWin) ReleaseObj(p->mpParentWin);
    p->mpVtbl8 = kpBaseVtbl4;
    p->mpVtbl4 = kpBaseVtbl0DTor;
    p->mpVtbl0 = kpBigBaseVtbl0DTor;
}

// ===========================================================================
// 0x00f38d70 -- scalar deleting destructor
// ===========================================================================
int SpaceObj::f38d70(char del) {
    int p = (int)this;
    FUN_00f38ce0((BigAssetView*)p);
    if (del & 1) operator_del((void*)p);
    return p;
}

// ===========================================================================
// 0x00f38d90 -- post a UI behavior message carrying the clock digits
// ===========================================================================
// @ 0x00f38d90
char SpaceObj::f38d90(int msg, void* d)
{
    int self = (int)this;
    if (msg != knBehaviorID)
        return 0;
    if (((*(int*)(self + 0x30) - *(int*)(self + 0x2c)) & 0xfffffffc) != 0x10)
        return 0;
    if (Slot<TV1p_c>(*(void**)(self + 0x10), 0xf8)(*(void**)(self + 0x10), d) == 0)
        return 0;

    int* pDigits = *(int**)(self + 0x2c);
    int nMinuteHigh = *(int*)(pDigits[3] + 0x1c);
    int nMinuteLow  = *(int*)(pDigits[2] + 0x1c);
    int nSecondHigh = *(int*)(pDigits[1] + 0x1c);
    int nSecondLow  = *(int*)(pDigits[0] + 0x1c);
    int nValue = nSecondLow + 10 * (nSecondHigh + 6 * (nMinuteLow + 10 * nMinuteHigh));

    cBehaviorMessage* pMessage = (cBehaviorMessage*)operator_new(0x40, kpUIAllocName, 0, 0, 0, 0);
    if (pMessage != 0) {
        pMessage->mnID       = 0;
        pMessage->mpVtbl     = (void*)0x013EB90C;     // base message vtable
        pMessage->mnRefCount = 0;
        pMessage->mpVtbl     = (void*)0x013EB844;     // behavior-message vtable
        pMessage->mnFlags    = 0;
        CallSlot0(pMessage, 0x04);                    // AddRef
        pMessage->mnID       = knValueMessage;
        pMessage->mpData0    = (void*)nValue;
        MessageSetIRefCount(pMessage, 1, (char*)self + 4);
        cMessageServer* pServer = (cMessageServer*)MessageServer();
        Slot<TV3>(pServer, 0x14)(pServer, pMessage->mnID, pMessage, 0);
        CallSlot0(pMessage, 0x08);                    // Release
    }
    return 0;
}

// ===========================================================================
// 0x00f38e80 -- initialise the large-asset-view UI
// ===========================================================================
// @ 0x00f38e80
char SpaceObj::f38e80(int* win)
{
    BigAssetView* p = (BigAssetView*)this;
    AssignObj(&p->mpParentWin, win, 0x00, 0x04);

    if (p->mpExtra != 0) {
        void* pOld = p->mpExtra;
        p->mpExtra = 0;
        ReleaseObj(pOld);
    }

    if (p->mpParentWin != 0) {
        void* pMem = operator_new(0x18, kpUIAllocName, 0, 0, 0, 0);
        void* pLayoutNew = pMem ? ((cSPUILayout*)pMem)->ctor() : 0;
        AssignObj(&p->mpLayout, pLayoutNew, 0x04, 0x08);

        cSPUILayout* pLayout = (cSPUILayout*)p->mpLayout;
        if (!pLayout->Init(kpAssetLayoutKey, 0, knUIKeyFlags)) {
            pLayout->Shutdown(1);
            void* pOld = p->mpLayout;
            if (pOld != 0) {
                p->mpLayout = 0;
                CallSlot0(pOld, 0x08);
            }
            return 0;
        }

        pLayout->SetParentWin(p->mpParentWin, 1, knUIKeyFlags);

        int nID = 0x7c3ebe0;
        for (int i = 4; i != 0; --i, ++nID) {
            void* pMemChild = operator_new(0x2c, kpUIAllocName, 0, 0, 0, 0);
            void* pChild = pMemChild ? (void*)FUN_00f385d0((SetiPanel*)pMemChild) : 0;
            int nColumns = (nID == 0x7c3ebe1 || nID == 0x7c3ebe3) ? 5 : 9;
            void* pWindow = pLayout->FindWindowByID(nID, 1);
            Slot<TV2ii>(pChild, 0x1c)(pChild, (int)pWindow, nColumns);
            AddRefObj(pChild);

            if (p->mChildren.mpEnd != p->mChildren.mpCap) {
                void** pSlot = p->mChildren.mpEnd;
                p->mChildren.mpEnd = pSlot + 1;
                if (pSlot != 0) {
                    *pSlot = pChild;
                    AddRefObj(pChild);
                }
            } else {
                void* pTemp = pChild;
                AddRefObj(pChild);
                p->mChildren.DoInsertPtr(p->mChildren.mpEnd, (const void**)&pTemp);
            }
            if (pChild != 0)
                ReleaseObj(pChild);
        }
    }

    void* pServer = MessageServer();
    p->mpServer      = pServer;
    p->mpHandler     = p;
    p->mpHandlerData = kpBigHandler;
    p->mnHandlerArg  = 1;
    p->mnHandlerArg2 = 0;
    if (pServer != 0)
        Slot<TV2ii>(pServer, 0x24)(pServer, (int)p, knBehaviorID);
    return 1;
}

// ===========================================================================
// 0x00f39080 -- shutdown the large-asset-view UI
// ===========================================================================
// @ 0x00f39080
void __fastcall FUN_00f39080(BigAssetView* p)
{
    CallSlot1i(p, 0x1c, 0);
    for (void** ppChild = p->mChildren.mpBegin; ppChild != p->mChildren.mpEnd; ++ppChild)
        CallSlot0(*ppChild, 0x20);
    p->mChildren.erase(p->mChildren.mpBegin, p->mChildren.mpEnd);

    if (p->mpServer != 0) {
        void* pHandler = p->mpServer;
        p->mpServer = 0;
        EA_Messaging_RemoveHandler((int)pHandler, (int)p->mpHandler, (int)p->mpHandlerData,
                                   p->mnHandlerArg, p->mnHandlerArg2);
    }
    if (p->mpParentWin != 0) {
        void* pOld = p->mpParentWin;
        p->mpParentWin = 0;
        ReleaseObj(pOld);
    }
    if (p->mpLayout != 0)
        ((cSPUILayout*)p->mpLayout)->Shutdown(1);
}

// ===========================================================================
// 0x00f39110 -- construct a cString
// ===========================================================================
// @ 0x00f39110
struct CString { void* p; };
struct CStringCls { void ctor(int, int, int); };
CString* __cdecl FUN_00f39110(CString* out) {
    ((CStringCls*)out)->ctor(0x8b1a2341, 0x7c4093a, 0);
    return out;
}

// ===========================================================================
// 0x00f39130 -- read a value out of a property
// ===========================================================================
// @ 0x00f39130
unsigned char __cdecl FUN_00f39130(const void* pKey) {
    void* pList = 0;
    unsigned char r = 0;
    if (FUN_005bf0e0(pKey, &pList)) {
        void* pItems = 0;
        if (FUN_005bf1e0(pList, &pItems)) {
            ((cCollectableItems*)pItems)->Load(pKey);
            unsigned char out[8];
            r = ((cCollectableItems*)pItems)->GetValue(out);
        }
        if (pItems != 0)
            ReleaseObj(pItems);
    }
    if (pList != 0)
        ReleaseObj(pList);
    return r;
}

// ===========================================================================
// 0x00f391c0 -- construct a cCivTokenTranslator
// ===========================================================================
// @ 0x00f391c0
void* __fastcall FUN_00f391c0(void* p)
{
    ((BaseTranslator*)p)->ctor();
    *(void**)p = kpTranslatorVtbl;
    *(int*)((char*)p + 0x0c) = 0;
    *(int*)((char*)p + 0x10) = 0;
    *(int*)((char*)p + 0x14) = 0;
    *(int*)((char*)p + 0x18) = 0;
    *(int*)((char*)p + 0x1c) = 0;
    *(int*)((char*)p + 0x20) = -1;
    *(wchar_t**)((char*)p + 0x24) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x28) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x2c) = gEmptyString16 + 1;
    *(wchar_t**)((char*)p + 0x34) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x38) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x3c) = gEmptyString16 + 1;
    *(wchar_t**)((char*)p + 0x44) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x48) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x4c) = gEmptyString16 + 1;
    *(wchar_t**)((char*)p + 0x54) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x58) = gEmptyString16;
    *(wchar_t**)((char*)p + 0x5c) = gEmptyString16 + 1;
    return p;
}

// ===========================================================================
// 0x00f39220 -- destruct a cCivTokenTranslator
// ===========================================================================
// @ 0x00f39220
void __fastcall FUN_00f39220(int* p)
{
    *(void**)p = kpTranslatorVtbl;
    wchar_t* pBegin;
    pBegin = *(wchar_t**)((char*)p + 0x54);
    if (((*(char**)((char*)p + 0x5c) - (char*)pBegin) & ~1) > 2 && pBegin != 0) operator_del(pBegin);
    pBegin = *(wchar_t**)((char*)p + 0x44);
    if (((*(char**)((char*)p + 0x4c) - (char*)pBegin) & ~1) > 2 && pBegin != 0) operator_del(pBegin);
    pBegin = *(wchar_t**)((char*)p + 0x34);
    if (((*(char**)((char*)p + 0x3c) - (char*)pBegin) & ~1) > 2 && pBegin != 0) operator_del(pBegin);
    pBegin = *(wchar_t**)((char*)p + 0x24);
    if (((*(char**)((char*)p + 0x2c) - (char*)pBegin) & ~1) > 2 && pBegin != 0) operator_del(pBegin);
    ((BaseTranslator*)p)->dtor();
}
