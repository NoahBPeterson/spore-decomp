// Slice s00de41b0: 00de4e70, a property lookup that reads two int properties
// from a property list returned by the property manager.

typedef unsigned int uint32;

struct Property {
    char pad[0x12];
    short type;                 // +0x12, 9 = int
    int* GetInt();              // thiscall, returns int& (asm: Property::GetInt)
};

struct PropertyList {
    virtual void v0();
    virtual void Release();     // slot 1
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool GetProperty(uint32 id, Property** out);  // slot 9 (+0x24)
};

// Intrusive reference to a PropertyList (AutoRefCount-style, Release at slot 1).
struct PropertyListRef {
    PropertyList* p;
    PropertyListRef() : p(0) {}
    void Reset() {
        PropertyList* old = p;
        p = 0;
        if (old) old->Release();
    }
};

struct PropertyManager {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32 a, uint32 b, PropertyListRef* out);  // slot 11 (+0x2c)
};

PropertyManager* GetPropertyManager();   // free function, no args (SP::PropertyManager)

// @ 0x00de4e70
int ReadIntPropertyPair(uint32 a1, uint32 a2) {
    int ret = 0;
    int v1 = 0;
    PropertyListRef list;
    PropertyManager* mgr = GetPropertyManager();
    list.Reset();
    if (mgr->GetPropertyList(a1, a2, &list)) {
        Property* tmp;
        if (list.p && list.p->GetProperty(0x22e7847, &tmp)) {
            if (tmp->type == 9) {
                v1 = *tmp->GetInt();
            }
        }
        int v2 = 0;
        if (list.p && list.p->GetProperty(0x22e785c, &tmp)) {
            if (tmp->type == 9) {
                v2 = *tmp->GetInt();
            }
        }
        if (v1 > 0) {
            ret = (v2 <= 0) ? 4 : 2;
        } else if (v2 > 0) {
            ret = 1;
        }
    }
    if (list.p) {
        list.p->Release();
    }
    return ret;
}

// =====================================================================================================
// Slice s00de41b0 (continuation).  The galaxy game-entry implementation (cGalaxyGameEntryImpl):
// the galaxy-layout refresh, the game-mode / entry-state flags, the effects-world and download-dialog
// plumbing, the save-game serializer round-trip and the simulator-property filter.
//
// Callees live at their retail addresses (relative calls show up as selrefs in the object); the classes
// below declare the real data layout this code walks.
// =====================================================================================================
#include "types.h"

#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))

// ---------------------------------------------------------------------------------------------
// ambient / global callees
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl FUN_00f473a0(uint32_t nSize, const char* szName, int nA, int nB, int nC, int nD);  // 0x00f473a0 operator new
extern "C" void  __cdecl FUN_00f47380(void* pBlock);                                       // 0x00f47380 operator delete
extern "C" void  __cdecl FUN_00806e40(void* pWindow, int nA, int nB);                      // 0x00806e40 AutoSizeWindowForText
extern "C" void  __cdecl FUN_00806ee0(void* pWindow, float fDelta);                        // 0x00806ee0
extern "C" void  __cdecl FUN_0093aa70(void* pStream, void* pValue, int nCount, int nEndian); // 0x0093aa70 EA::IO::WriteUint32
extern "C" void  __cdecl FUN_00ae2e40(void* pStream, void* pValue);                        // 0x00ae2e40
extern "C" void* __cdecl FUN_00921580(void* pNode);                                        // 0x00921580 RBTreeIncrement
extern "C" bool  __cdecl FUN_00685520(int nFlag);                                          // 0x00685520 IsWorldLayoutFlagSet
extern "C" char  __cdecl FUN_00809db0(void* pA, void* pB);                                 // 0x00809db0 UI::CalloutMessageBox
extern "C" void* __cdecl FUN_00688fa0(const wchar_t* szName);                              // 0x00688fa0 open file
extern "C" void  __cdecl FUN_006891f0(const wchar_t* szFrom, const wchar_t* szTo);          // 0x006891f0 commit/rename
extern "C" void* __cdecl FUN_009512c0();                                                   // 0x009512c0 heap
extern "C" void* __cdecl FUN_009512d0(int nSize, int nAlign, const char* szTag, void* pHeap); // 0x009512d0 allocate
extern "C" void* __cdecl FUN_00b3d2a0();                                                   // 0x00b3d2a0 SP::StarManager
extern "C" void* __cdecl FUN_00b3d230();                                                   // 0x00b3d230
extern "C" void* __cdecl FUN_00b3d4d0();                                                   // 0x00b3d4d0 trigger manager
extern "C" void* __cdecl FUN_0067dd10();                                                   // 0x0067dd10 SP::App
extern "C" void* __cdecl FUN_0067ddd0();                                                   // 0x0067ddd0 SP::EffectsManager
extern "C" void* __cdecl FUN_0067cb10();                                                   // 0x0067cb10 SP::MovieSystem
extern "C" void* __cdecl FUN_0067cad0();                                                   // 0x0067cad0 SP::AddBoundingBox

// ---------------------------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------------------------
class cGalaxyGameEntryImpl;
class cSPUILayout;
class cSPUIGlobalUI;
class tGUIObject;
class cDownloadDialog;

class tRefObj {                                        // reference-counted object: 0 AddRef / 4 Release
public:
    virtual void AddRef();
    virtual void Release();
};

class cPanelIDs {                                      // 0x016a1344
public:
    uint8_t  mPad000[0xc8];
    bool     mb0c8;                                    // +0x0c8
    bool     mb0c9;                                    // +0x0c9
    uint8_t  mPad0ca[0x108 - 0xca];
    int32_t  mn108;                                    // +0x108
};
extern cPanelIDs*      kGUI_PanelIDs;                  // 0x016a1344
extern uint8_t         g_bGalaxyActive;                // 0x016a1348
extern void*           g_p16a0d18;                     // 0x016a0d18
extern cDownloadDialog* g_pDownloadDialogA;            // 0x016a15f8
extern cDownloadDialog* g_pDownloadDialogB;            // 0x016a15f4
extern uint32_t        g_dw1897c18;                    // 0x01897c18
extern uint32_t        g_dw15a38b8;                    // 0x015a38b8
extern uint32_t        g_dw15a41d4;                    // 0x015a41d4
extern uint32_t        g_dw15a3860;                    // 0x015a3860

// ---------------------------------------------------------------------------------------------
// interfaces (only their vtable slots are entered)
// ---------------------------------------------------------------------------------------------
class tGUIObject {                                     // an SPUI window / widget
public:
    virtual void        v00();
    virtual void        v04();
    virtual void        v08();
    virtual tGUIObject* v0c(uint32_t nID);             // +0x0c
    virtual void        v10();
    virtual void        v14();
    virtual void        v18();
    virtual void        v1c();
    virtual void        v20();
    virtual void        v24();
    virtual void        v28(int nID, bool bState);              // +0x28
    virtual void        v2c();
    virtual void        v30();
    virtual void        v34();
    virtual float*      v38();                          // +0x38  returns the window rect
    virtual void        v3c();
    virtual void        v40();
    virtual void        v44();
    virtual void        v48();
    virtual void        v4c();
    virtual void        v50();
    virtual void        v54();
    virtual void        v58();
    virtual void        v5c();
    virtual void        v60();
    virtual void        v64();
    virtual void        v68();
    virtual void        v6c(float* pRect);              // +0x6c
    virtual void        v70();
    virtual void        v74(float fA, float fB);        // +0x74
};

class cSPUIGlobalUI {                                  // the global UI
public:
    tGUIObject* __thiscall FindWindowByID(uint32_t nID);           // 0x00e012b0
};

class cSPUILayout {                                     // a named SPUI layout
public:
    uint8_t     mPad00[0x18];
    tGUIObject* __thiscall FindWindowByID(uint32_t nID, int nFlag); // 0x008105b0
};

class tEntryIface38 {                                   // the entry's UI-forwarding interface at +0x38
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual bool v18(uint32_t a, uint32_t b);                       // +0x18
    virtual bool v1c(uint32_t a, uint32_t b);                       // +0x1c
    virtual bool v20(float fA, float fB, int c);                    // +0x20
    virtual bool v24(uint32_t a, float fB, float fC, uint32_t d);   // +0x24
    virtual bool v28(uint32_t a, float fB, float fC, uint32_t d);   // +0x28
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40(uint32_t a);                                   // +0x40
};

class tEntryIface2c {                                   // the entry's notification sink at +0x2c
public:
    virtual void v0(uint32_t nArg);                                 // +0x00
    virtual void v4(void* pObj, uint32_t nArg);                     // +0x04
};

class tGameMode {                                       // the game-mode object at +0xf0
public:
    uint8_t mPad00[0x3c];
    int32_t mn3c;                                       // +0x3c
    uint8_t mPad40[4];
    uint8_t mObj44[0x10];                               // +0x44  handed to the download dialog
    bool __thiscall FUN_00e205d0();                     // 0x00e205d0
    void __thiscall FUN_00e20860();                     // 0x00e20860
};

class tTriggerMgr {                                     // the trigger manager (0x00b3d4d0)
public:
    uint8_t mPad00[0x2c];
    int32_t mn2c;                                       // +0x2c
    void __thiscall FUN_00ad7dc0();                     // 0x00ad7dc0
    void __thiscall FUN_00ad7d40();                     // 0x00ad7d40
    void __thiscall FUN_00adffd0();                     // 0x00adffd0
};

class tBannerList {
public:
    int __thiscall FUN_00ba6d80(uint32_t nID);          // 0x00ba6d80
};

class tBBoxOwner {
public:
    uint32_t __thiscall FUN_0080dc90();                 // 0x0080dc90
    void     __thiscall FUN_0080dc50(void* pArg);       // 0x0080dc50
};

class tBoundObj {                                       // the object at +0x168
public:
    uint8_t mPad00[0x0c];
    void __thiscall FUN_00b5cde0(uint32_t nTag);        // 0x00b5cde0
};

class cDownloadDialog {
public:
    uint8_t mPad00[0x2c];
    int32_t mn2c;                                       // +0x2c
    void __thiscall FUN_00df5540();                     // 0x00df5540
    bool __thiscall FUN_00df5830(void* pArg);           // 0x00df5830
    void __thiscall FUN_00df58f0();                     // 0x00df58f0
    bool __thiscall FUN_00df59c0(void* pArg);           // 0x00df59c0
    void __thiscall FUN_00df55b0(int nArg);             // 0x00df55b0
    void __thiscall FUN_00df5670(char bFlag);           // 0x00df5670
    uint32_t __thiscall FUN_00df5aa0(char bFlag);       // 0x00df5aa0
    bool __thiscall FUN_00df5420();                     // 0x00df5420
    cDownloadDialog* __thiscall ctor5c80();             // 0x00df5c80
    cDownloadDialog* __thiscall ctor5940();             // 0x00df5940
};

// ---------------------------------------------------------------------------------------------
// the file / stream / serializer side (save-game round trip)
// ---------------------------------------------------------------------------------------------
class tFileStream {
public:
    virtual void s00();  virtual void s04();  virtual void s08();  virtual void s0c();
    virtual void s10();  virtual void s14();  virtual void s18();
    virtual void s1c();                                 // +0x1c
};

class tFile {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();
    virtual void v2c();                                 // +0x2c
    tFileStream mStream;                                // +0x04
};

class cVarListSerializer {
public:
    uint8_t m00[0x14];
    void __thiscall ctor(void* pOwner, void* pName, uint32_t nSig);     // 0x00692f90
    void __thiscall Serialize(void* pValue);                            // 0x00692900
};

class C3 {                                              // the archive stream used to write the save
public:
    void* mpVtbl;                                       // +0x00
    void* mpState;                                      // +0x04
    void* mpSerialized;                                 // +0x08
    cVarListSerializer mSerializer;                     // +0x0c
    uint8_t mWork[0xa00];                               // +0x20
    C3*  __thiscall ctorB(tFile* pFile, void* pA, void* pB, void* pC);  // 0x00693d60
    void __thiscall FUN_00692ea0();                     // 0x00692ea0
    void __thiscall FUN_00693900();                     // 0x00693900
};

// ---------------------------------------------------------------------------------------------
// the property tree serialised by 00de4c80 / 00de4d90
// ---------------------------------------------------------------------------------------------
class tRBNode {
public:
    uint32_t m00, m04, m08, m0c;
    uint32_t mKey;                                      // +0x10
    uint32_t m14, m18;
    uint32_t mValue;                                    // +0x1c
};

class tRBTree {
public:
    uint32_t  m00;
    tRBNode*  mEnd;                                     // +0x04
    tRBNode*  mBegin;                                   // +0x08
    uint32_t  m0c, m10;
    uint32_t  mCount;                                   // +0x14
};

class tArchive {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();
    virtual void* v18();                                // +0x18
    virtual void  v1c();                                // +0x1c
    virtual tArchive* v20();                            // +0x20
};

// ---------------------------------------------------------------------------------------------
// simulator filter helpers (00de4e20 / 00de4f50)
// ---------------------------------------------------------------------------------------------
class tSimData {
public:
    uint32_t m00, m04, m08, m0c, m10, m14;
};

struct tSimAlloc {                                      // 0x28-byte allocation: 0x10 header + data
    uint8_t  mHead[0x10];
    tSimData mData;
};

class tSimElem {
public:
    uint32_t m0;                                        // +0x00
    uint32_t m4;                                        // +0x04
};

struct tSimVec {
    tSimElem* begin;
    tSimElem* end;
    tSimElem* cap;
};

struct tSimBuffer {                                     // the vector's buffer: a 4-byte refcount head
    uint32_t mnRefs;                                    // +0x00, i.e. buffer[-1]
    tSimElem maElems[1];                                // +0x04
};

class tSimContainer {
public:
    void __thiscall Init(void* pOut, int nA, int nB);           // 0x00596900
    void __thiscall Add(uint32_t a, uint32_t b, int nC);        // 0x00596da0
    void __thiscall Query(void* pOut, uint32_t nKey);           // 0x00596fc0
    void __thiscall Insert(uint32_t a, uint32_t b);             // 0x00596d70
    void __thiscall Clear();                                    // 0x005942e0
};

extern "C" uint32_t __cdecl FUN_00de4e70(uint32_t a, uint32_t b);

// ---------------------------------------------------------------------------------------------
// ref-counted handle assignment (AddRef the new object / Release the old one)
// ---------------------------------------------------------------------------------------------
static __forceinline void AssignRef(void** ppTarget, void* pNew, int nAddSlot, int nRelSlot)
{
    void* pOld = *ppTarget;
    if (pNew != pOld) {
        if (pNew != 0)
            ((void(__thiscall*)(void*))VFN(pNew, nAddSlot))(pNew);
        *ppTarget = pNew;
        if (pOld != 0)
            ((void(__thiscall*)(void*))VFN(pOld, nRelSlot))(pOld);
    }
}

// ---------------------------------------------------------------------------------------------
// the entry object itself (only the fields this slice touches are named)
// ---------------------------------------------------------------------------------------------
class tList2 {                                          // a two-pointer list header
public:
    tList2* mpNext;                                     // +0x00
    tList2* mpPrev;                                     // +0x04
};

class cGalaxyGameEntryImpl {
public:
    uint8_t mPad00[0x20];
    tList2  m20;                                        // +0x20
    uint8_t mPad28[0x04];
    tEntryIface2c* mp2c;                                // +0x2c
    uint8_t mPad30[0x04];
    void*   mp34;                                       // +0x34
    tEntryIface38* mp38;                                // +0x38
    uint8_t mPad3c[0x7c - 0x3c];
    uint32_t m7c;                                       // +0x7c
    uint8_t mPad80[0xcc - 0x80];
    uint32_t mcc;                                       // +0xcc
    uint8_t mPadD0[0xe8 - 0xd0];
    int32_t me8;                                        // +0x0e8
    uint8_t mec;                                        // +0x0ec
    uint8_t med;                                        // +0x0ed
    uint8_t mee;                                        // +0x0ee
    uint8_t mef;                                        // +0x0ef
    tGameMode* mf0;                                     // +0x0f0
    uint8_t mPadF4[0xfc - 0xf4];
    int32_t mfc;                                        // +0x0fc
    int32_t m100;                                       // +0x100
    uint8_t mPad104[0x108 - 0x104];
    int32_t m108;                                       // +0x108
    int32_t m10c;                                       // +0x10c
    uint8_t mPad110[0x144 - 0x110];
    cSPUILayout mLayout144;                             // +0x144
    void*   m15c;                                       // +0x15c
    uint8_t mPad160[0x168 - 0x160];
    tBoundObj* m168;                                    // +0x168
    int32_t m16c;                                       // +0x16c
    uint8_t mPad170[0x178 - 0x170];
    void*   m178;                                       // +0x178
    uint8_t mPad17c[0x184 - 0x17c];
    cSPUIGlobalUI* mpGlobalUI184;                       // +0x184
    uint8_t mPad188[0x198 - 0x188];
    void*   m198;                                       // +0x198
    uint8_t mPad19c[0x1ec - 0x19c];
    int32_t m1ec;                                       // +0x1ec
    uint8_t mPad1f0;
    uint8_t m1f1;                                       // +0x1f1
    uint8_t mPad1f2[0x24c - 0x1f2];
    uint8_t m24c;                                       // +0x24c

    void   __thiscall FUN_00de41b0();
    uint32_t __thiscall FUN_00de4360(uint32_t nID);
    void   __thiscall FUN_00de43b0(uint32_t nArg);
    bool   __thiscall FUN_00de43d0(uint32_t a, uint32_t b);
    bool   __thiscall FUN_00de4410(uint32_t a, uint32_t b);
    bool   __thiscall FUN_00de4450(uint32_t a, float fB, float fC, uint32_t d);
    bool   __thiscall FUN_00de44a0(uint32_t a, float fB, float fC, uint32_t d);
    bool   __thiscall FUN_00de44f0(float fA, float fB, uint32_t c);
    void   __thiscall FUN_00de4570(uint32_t nArg);
    void   __thiscall FUN_00de4590(void* pObj, uint32_t nArg);
    uint32_t __thiscall FUN_00de4610();
    void   __thiscall FUN_00de4630();
    int    __thiscall FUN_00de46e0();
    void   __thiscall OnActivate();
    void   __thiscall FUN_00de4850();
    void   __thiscall FUN_00de4910();
    void   __thiscall FUN_00de4a70();
    void   __thiscall FUN_00de4b30();
    void   __thiscall FUN_00de4c20(char bFlag);
    void   __thiscall FUN_00ddd970();
};

// @ 0x00de41b0
void __thiscall cGalaxyGameEntryImpl::FUN_00de41b0()
{
    if (mpGlobalUI184 == 0)
        return;
    tGUIObject* pWindow = mpGlobalUI184->FindWindowByID(0x469975e);
    if (pWindow == 0)
        return;

    float* pRect = pWindow->v38();
    float fOldW = pRect[2] - pRect[0];
    float fOldH = pRect[3] - pRect[1];
    FUN_00806e40(pWindow, 0, 0);
    float fNewW = pRect[2] - pRect[0];
    float fDelta = fNewW - fOldW;
    pWindow->v74(fOldW, fOldH);
    if (fDelta > 0.0f) {
        tGUIObject* pOther = mpGlobalUI184->FindWindowByID(0x10ed874);
        if (pOther != 0) {
            float* pR2 = pOther->v38();
            float afRect[4];
            afRect[0] = pR2[0] - fDelta * 0.5f;
            afRect[1] = pR2[1];
            afRect[2] = (pR2[2] - pR2[0]) + afRect[0] + fDelta;
            afRect[3] = pR2[3];
            pOther->v6c(afRect);
        }
        float fHalf = fDelta * -0.5f;
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x447060a), fHalf);
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x469975e), fHalf);
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x43b72d0), fHalf);
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x10f366d), fHalf);
    }
}

// @ 0x00de4360
uint32_t __thiscall cGalaxyGameEntryImpl::FUN_00de4360(uint32_t nID)
{
    if (nID == 0x2f009dd0)
        return ((uint32_t)this - 4 != 0) ? (uint32_t)this : 0;
    return 0;
}

// @ 0x00de4380
bool __cdecl FUN_00de4380()
{
    if (kGUI_PanelIDs->mb0c9 == false)
        return true;
    if (kGUI_PanelIDs->mn108 != 2)
        return true;
    return kGUI_PanelIDs->mb0c8 ? false : true;
}

// @ 0x00de43b0
void __thiscall cGalaxyGameEntryImpl::FUN_00de43b0(uint32_t nArg)
{
    m24c = 0;
    if (mp38 != 0)
        ((void(__thiscall*)(void*, uint32_t))VFN(mp38, 0x40))(mp38, nArg);
}

// @ 0x00de43d0
bool __thiscall cGalaxyGameEntryImpl::FUN_00de43d0(uint32_t a, uint32_t b)
{
    int32_t nCur = m108;
    if ((m10c == nCur || nCur == 0) && mp38 != 0)
        mp38->v1c(a, b);
    return false;
}

// @ 0x00de4410
bool __thiscall cGalaxyGameEntryImpl::FUN_00de4410(uint32_t a, uint32_t b)
{
    int32_t nCur = m108;
    if (m10c == nCur || nCur == 0) {
        if (m178 != 0)
            return true;
        if (mp38 != 0)
            mp38->v18(a, b);
    }
    return false;
}

// @ 0x00de4450
bool __thiscall cGalaxyGameEntryImpl::FUN_00de4450(uint32_t a, float fB, float fC, uint32_t d)
{
    if (m10c != m108)
        return false;
    if (mp38 != 0)
        mp38->v28(a, fB, fC, d);
    return true;
}

// @ 0x00de44a0
bool __thiscall cGalaxyGameEntryImpl::FUN_00de44a0(uint32_t a, float fB, float fC, uint32_t d)
{
    if (m10c != m108)
        return false;
    if (mp38 != 0)
        mp38->v24(a, fB, fC, d);
    return true;
}

// @ 0x00de44f0
bool __thiscall cGalaxyGameEntryImpl::FUN_00de44f0(float fA, float fB, uint32_t c)
{
    if (m10c != m108)
        return false;
    if (mp38 != 0)
        mp38->v20(fA, fB, c);
    int32_t nState = ((tTriggerMgr*)FUN_00b3d4d0())->mn2c;
    if (nState != 1 && nState != 2) {
        void* pMovie = FUN_0067cb10();
        if (((char(__thiscall*)(void*))VFN(pMovie, 0x14))(pMovie) == 0 && m1ec != 1)
            return false;
    }
    return true;
}

// @ 0x00de4570
void __thiscall cGalaxyGameEntryImpl::FUN_00de4570(uint32_t nArg)
{
    m16c = nArg;
    if (mp2c != 0)
        mp2c->v0(nArg);
}

// @ 0x00de4590
void __thiscall cGalaxyGameEntryImpl::FUN_00de4590(void* pObj, uint32_t nArg)
{
    m16c = 0;
    if (pObj != 0) {
        void* pQ = ((void*(__thiscall*)(void*))VFN(pObj, 0x10))(pObj);
        if (pQ != 0) {
            pQ = ((void*(__thiscall*)(void*))VFN(pObj, 0x10))(pObj);
            ((void(__thiscall*)(void*, void*))VFN(pQ, 0xe0))(pQ, pObj);
        }
    }
    if (mfc == 0) {
        mfc = 1;
        m100 = 2;
        return;
    }
    if (mp2c != 0)
        ((void(__thiscall*)(void*, void*, uint32_t))VFN(mp2c, 4))(mp2c, pObj, nArg);
}

// @ 0x00de4610
uint32_t __thiscall cGalaxyGameEntryImpl::FUN_00de4610()
{
    return ((tBannerList*)FUN_00b3d2a0())->FUN_00ba6d80(m7c);
}

// @ 0x00de4630
void __thiscall cGalaxyGameEntryImpl::FUN_00de4630()
{
    if (!mf0->FUN_00e205d0())
        return;
    char c = mef;
    if (c != 0) {
        med = 1;
    } else if (m1f1 == c) {
        mec = 1;
        me8 = 2;
        FUN_00809db0(&g_dw15a41d4, &g_dw15a3860);
    } else if (c != 0) {
        med = 1;
    } else if (m1f1 != 0) {
        mee = 1;
    }
}

// @ 0x00de46e0
int __thiscall cGalaxyGameEntryImpl::FUN_00de46e0()
{
    if (m20.mpNext == &m20 && mp34 == 0)
        return 1;
    return 0;
}

// @ 0x00de4720
void __thiscall cGalaxyGameEntryImpl::OnActivate()
{
    FUN_00ddd970();
    g_bGalaxyActive = 1;
    if (m15c == 0) {
        void* pEM = FUN_0067ddd0();
        void* pWorld = ((void*(__thiscall*)(void*, uint32_t, const char*))VFN(pEM, 0x4c))(pEM, 0x2dda976, "GGE effects world");
        AssignRef(&m15c, pWorld, 0, 4);
    }
    {
        void* pEM = FUN_0067ddd0();
        ((void(__thiscall*)(void*, int, int))VFN(pEM, 0x98))(pEM, 10, 1);
    }
    mcc = ((tBBoxOwner*)FUN_0067cad0())->FUN_0080dc90();
    ((tBBoxOwner*)FUN_0067cad0())->FUN_0080dc50(g_p16a0d18);
    if (m168 != 0)
        ((void(__thiscall*)(void*, int))VFN(m168, 0x0c))(m168, 1);
    ((tBoundObj*)FUN_00b3d230())->FUN_00b5cde0(0x780786fd);
    if (m198 == 0) {
        void* pApp = FUN_0067dd10();
        void* pQ = ((void*(__thiscall*)(void*))VFN(pApp, 0x50))(pApp);
        void* pR = ((void*(__thiscall*)(void*))VFN(pQ, 0x38))(pQ);
        AssignRef(&m198, pR, 0, 4);
    }
    ((tTriggerMgr*)FUN_00b3d4d0())->FUN_00ad7dc0();
    ((tTriggerMgr*)FUN_00b3d4d0())->FUN_00ad7d40();
    ((tTriggerMgr*)FUN_00b3d4d0())->FUN_00adffd0();
}

// @ 0x00de4850
void __thiscall cGalaxyGameEntryImpl::FUN_00de4850()
{
    C3 archive;
    tFile* pFile = (tFile*)FUN_00688fa0(L"GGEUserData.dat.tmp");
    if (pFile != 0) {
        pFile->v00();
        archive.ctorB(pFile, &g_dw1897c18, &g_dw1897c18, &g_dw1897c18);
        archive.FUN_00692ea0();
        archive.mSerializer.ctor(this, &g_dw15a38b8, 0x1a80d26);
        archive.mSerializer.Serialize(archive.mpSerialized);
        archive.FUN_00693900();
    }
    pFile->v2c();
    pFile->mStream.s1c();
    pFile->mStream.s08();
    FUN_006891f0(L"GGEUserData.dat.tmp", L"GGEUserData.dat");
    pFile->v04();
}

// @ 0x00de4910
void __thiscall cGalaxyGameEntryImpl::FUN_00de4910()
{
    uint32_t nKey = 0x61dd69b;
    switch (m108) {
    case 5:  nKey = 0x615b966; break;
    case 6:  return;
    case 0xd: nKey = 0x70d74e7; break;
    }

    uint32_t aIDs[5] = { 0x61dd69b, 0x615b966, 0x615b616, 0x70d74e7, 0x70d7509 };
    unsigned i = 0;
    cSPUILayout* pLayout = &mLayout144;
    for (; i < 3; i++) {
        tGUIObject* pWindow = pLayout->FindWindowByID(aIDs[i], 1);
        if (pWindow != 0) {
            tGUIObject* pWidget = pWindow->v0c(0x8ed27e7a);
            if (pWidget != 0) {
                pWidget->v28(4, nKey == aIDs[i]);
                pWidget->v28(2, 0);
                pWidget->v28(8, 0);
                pWidget->v28(0x10, 0);
            }
        }
    }
    if (FUN_00685520(2)) {
        for (i = 3; i < 5; i++) {
            tGUIObject* pWindow = pLayout->FindWindowByID(aIDs[i], 1);
            if (pWindow != 0) {
                tGUIObject* pWidget = pWindow->v0c(0x8ed27e7a);
                if (pWidget != 0) {
                    pWidget->v28(4, nKey == aIDs[i]);
                    pWidget->v28(2, 0);
                    pWidget->v28(8, 0);
                    pWidget->v28(0x10, 0);
                }
            }
        }
    }
}

// @ 0x00de4a70
void __thiscall cGalaxyGameEntryImpl::FUN_00de4a70()
{
    cDownloadDialog* pObj = (cDownloadDialog*)FUN_009512d0(0x28, 4, "UI/cDownloadDialog", FUN_009512c0());
    cDownloadDialog* pDlg = pObj ? pObj->ctor5c80() : 0;
    AssignRef((void**)&g_pDownloadDialogA, pDlg, 0, 4);
    if (g_pDownloadDialogA->FUN_00df5830(&mf0->mObj44))
        g_pDownloadDialogA->FUN_00df5540();
}

// @ 0x00de4b00
void __cdecl FUN_00de4b00()
{
    if (g_pDownloadDialogA != 0) {
        g_pDownloadDialogA->FUN_00df58f0();
        if (g_pDownloadDialogA != 0) {
            cDownloadDialog* pOld = g_pDownloadDialogA;
            g_pDownloadDialogA = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 4))(pOld);
        }
    }
}

// @ 0x00de4b30
void __thiscall cGalaxyGameEntryImpl::FUN_00de4b30()
{
    cDownloadDialog* pObj = (cDownloadDialog*)FUN_009512d0(0x6c, 4, "UI/cDownloadDialog", FUN_009512c0());
    cDownloadDialog* pDlg = pObj ? pObj->ctor5940() : 0;
    AssignRef((void**)&g_pDownloadDialogB, pDlg, 0, 4);
    if (g_pDownloadDialogB->FUN_00df59c0(mf0))
        g_pDownloadDialogB->FUN_00df55b0(0);
}

// @ 0x00de4bc0
void __stdcall FUN_00de4bc0(char bFlag)
{
    if (g_pDownloadDialogB != 0) {
        g_pDownloadDialogB->FUN_00df5aa0(bFlag);
        if (g_pDownloadDialogB != 0) {
            cDownloadDialog* pOld = g_pDownloadDialogB;
            g_pDownloadDialogB = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 4))(pOld);
        }
    }
}

// @ 0x00de4c00
bool __cdecl FUN_00de4c00()
{
    if (g_pDownloadDialogB != 0)
        return g_pDownloadDialogB->FUN_00df5420();
    return true;
}

// @ 0x00de4c20
void __thiscall cGalaxyGameEntryImpl::FUN_00de4c20(char bFlag)
{
    if (g_pDownloadDialogB == 0)
        return;
    g_pDownloadDialogB->FUN_00df5670(bFlag);
    if (bFlag != 0) {
        if (mf0->mn3c != 5)
            mf0->mn3c = 4;
    } else {
        if (mf0->mn3c != 2)
            mf0->mn3c = 6;
    }
    mf0->FUN_00e20860();
}

// @ 0x00de4c80
void __cdecl FUN_00de4c80(tArchive* pSer, tRBTree* pTree)
{
    uint32_t nCount = pTree->mCount;
    FUN_0093aa70(pSer->v20()->v18(), &nCount, 1, 0);
    tRBNode* pEnd = (tRBNode*)&pTree->mEnd;
    for (tRBNode* pNode = pTree->mBegin; pNode != pEnd; pNode = (tRBNode*)FUN_00921580(pNode)) {
        uint32_t nKey = pNode->mKey;
        FUN_0093aa70(pSer->v20()->v18(), &nKey, 1, 0);
        pSer->v1c();
    }
    pSer->v1c();
}

// @ 0x00de4d90
void __cdecl FUN_00de4d90(tArchive* pSer, tRBTree* pTree)
{
    uint32_t nCount = pTree->mCount;
    FUN_0093aa70(pSer->v20()->v18(), &nCount, 1, 0);
    tRBNode* pEnd = (tRBNode*)&pTree->mEnd;
    for (tRBNode* pNode = pTree->mBegin; pNode != pEnd; pNode = (tRBNode*)FUN_00921580(pNode)) {
        FUN_00ae2e40(pSer, &pNode->mKey);
        pSer->v1c();
        FUN_00ae2e40(pSer, &pNode->mValue);
        pSer->v1c();
    }
    pSer->v1c();
}

// @ 0x00de4e20
void __stdcall FUN_00de4e20(const tSimData* pSrc)
{
    tSimAlloc* pAlloc = (tSimAlloc*)FUN_00f473a0(0x28, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    tSimData* pData = &pAlloc->mData;
    if (pData != 0)
        *pData = *pSrc;
}

// @ 0x00de4f50
void __cdecl FUN_00de4f50(tSimContainer* pObj, uint32_t nMask)
{
    tSimVec v = { 0, 0, 0 };
    pObj->Init(&v, 0, 0);
    for (int i = 0; i < v.end - v.begin; i++)
        pObj->Add(v.begin[i].m0, v.begin[i].m4, 0);
    pObj->Query(&v, 0x887c91bb);
    for (int i = 0; i < v.end - v.begin; i++) {
        uint64_t nKey = *(uint64_t*)&v.begin[i];
        uint32_t nHi = (uint32_t)(nKey >> 32);
        uint32_t nRes = FUN_00de4e70((uint32_t)nKey, nHi);
        if ((nMask & nRes) != 0)
            pObj->Insert((uint32_t)nKey, nHi);
    }
    pObj->Clear();
    if (v.begin != 0 && ((tSimBuffer*)v.begin - 1)->mnRefs != 0)
        FUN_00f47380(v.begin);
}
