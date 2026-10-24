// Slice s00de0910: the galaxy-game-entry panel-button cluster - the tool-panel
// key lookup, the panel/page bitset, the ContentValidationSummarizer constructor,
// the editor-launch-data builders, the app-mode dispatch, the tool-panel enable
// refresh and the editor-launch request handlers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// Win32 bits
// ---------------------------------------------------------------------------------------------
union LARGE_INTEGER {
    struct { uint32_t LowPart; int32_t HighPart; } u;
    int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount);

// ---------------------------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------------------------
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
#define VTBL(x) ((void*)(&(x)))

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; comparison masks call targets)
// ---------------------------------------------------------------------------------------------
extern "C" void*    __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0 operator_new
extern "C" void*    __cdecl FUN_00a206f0(void);            // 0x00a206f0 EA::Audio::GetSystemAT
extern "C" void*    __cdecl FUN_00df5f40(void);            // 0x00df5f40
extern "C" void*    __cdecl FUN_00b3d320(void* p);         // 0x00b3d320
extern "C" void*    __cdecl FUN_00b3d410(int a, void* b, int c); // 0x00b3d410
extern "C" void*    __cdecl FUN_00dd9190(void);            // 0x00dd9190
extern "C" uint32_t* __cdecl FUN_00ef19f0(void);           // 0x00ef19f0 new 9-dword record
extern "C" void      __cdecl FUN_00de5d00(uint32_t a1, void* a2, int a3, int a4, int a5, void* a6, void* a7); // 0x00de5d00

// thiscall callees, declared as members of a host class so `this` travels in ecx
class tHost {
public:
    void*   __thiscall FindWindowByID(uint32_t id);              // 0x00e012b0 cSPUIGlobalUI::FindWindowByID
    void*   __thiscall FUN_008105b0(uint32_t id, int flag);      // 0x008105b0 cSPUILayout::FindWindowByID
    void    __thiscall FUN_00e01350(int v);                      // 0x00e01350 cSPUIGlobalUI::SetVisibility
    void*   __thiscall FUN_005a9080();                           // 0x005a9080 cEditorLaunchData::cEditorLaunchData
    void    __thiscall FUN_006b5060();                           // 0x006b5060 cString ctor
    void    __thiscall FUN_006b5240();                           // 0x006b5240 cString dtor
    void    __thiscall FUN_00de0670(uint8_t a, uint8_t b);       // 0x00de0670 cInterfaceState::BeginSequence
    void    __thiscall FUN_0093a2e0();                           // 0x0093a2e0 cDirectPropertyList::SetBoolProperty
    void    __thiscall FUN_00de53d0(uint32_t a);                 // 0x00de53d0
    void    __thiscall FUN_00de86d0(int a, int b);               // 0x00de86d0
    void    __thiscall FUN_00e00670(uint32_t a, void* b);        // 0x00e00670
    void    __thiscall FUN_00e00650(uint32_t a, void* b);        // 0x00e00650
    void    __thiscall FUN_00e00760(uint32_t a);                 // 0x00e00760 ShowContextSporepedia
    void    __thiscall FUN_00ddb760();                           // 0x00ddb760
    void    __thiscall FUN_00e3e350();                           // 0x00e3e350
    bool    __thiscall FUN_00ec5a60(void* pVec, int a, int b);   // 0x00ec5a60
    bool*   __thiscall FUN_0041e920();                           // 0x0041e920 cProperty::GetBool
    void    __thiscall FUN_00b1dee0();                           // 0x00b1dee0
};

// ---------------------------------------------------------------------------------------------
// data globals (retail addresses in comments)
// ---------------------------------------------------------------------------------------------
extern uint32_t vtbl_CVS;         // 0x013ec458 ??_7ContentValidationSummarizer@@6B@
extern uint32_t vtbl_0147dc04;    // 0x0147dc04
extern uint32_t vtbl_0149bad8;    // 0x0149bad8

extern uint32_t DAT_015da784;     // 0x015da784
extern uint32_t DAT_015da788;     // 0x015da788
extern uint32_t DAT_015da78c;     // 0x015da78c
extern uint32_t DAT_015da790;     // 0x015da790

extern uint32_t DAT_016a1848[];   // 0x016a1848 page-enable bitset
extern uint32_t DAT_016a0e58;     // 0x016a0e58
extern uint32_t DAT_01654c10;     // 0x01654c10
extern void*    g_p16c7aa4;       // 0x016c7aa4
extern void*    g_pAppPreferences;// 0x015fd91c _sAppPreferences_SP__3PAVcPropertyList_1_A

extern char k_szSporepedia[];     // 0x013fa29c "Sporepedia"
extern char k_szSimulator[];      // 0x013f09b4 "Simulator"

// ---------------------------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------------------------
class cPanelIDs {
public:
    uint8_t  mPad000[0x108];   // +0x000
    int32_t  m108;             // +0x108
    uint8_t  mPad10c[0x38];    // +0x10c
    uint8_t  m144[0x40];       // +0x144 cSPUILayout subobject
    void*    m184;             // +0x184 cSPUIGlobalUI*
    uint32_t m188;             // +0x188
    uint32_t m18c;             // +0x18c
    uint32_t m190;             // +0x190
    uint8_t  m194[4];          // +0x194
    uint8_t  m198[0x40];       // +0x198 cInterfaceState subobject
    void**   m1d8;             // +0x1d8 vector begin
    void**   m1dc;             // +0x1dc vector end
};
extern cPanelIDs* kGUI_PanelIDs;   // 0x016a1344

class cString {
public:
    uint8_t mData[0x18];
};

// Simulator::cContentValidationSummarizer (retail layout: two vfptrs + 0x0c/0x10)
class cContentValidationSummarizer {
public:
    void*    mVtbl0;     // +0x00
    volatile void* mVtbl4; // +0x04 (volatile: the ctor stores it twice, as the base then derived vfptr)
    uint32_t m08;        // +0x08
    void*    m0c;        // +0x0c
    uint8_t  m10;        // +0x10
    uint8_t  mPad11[3];
    void* __thiscall FUN_00de0a90(void* pOuter, uint8_t b);
};

// SP::Editor::cEditorLaunchData (retail layout; +0x90/+0x94/+0x98 ref-counted handles)
class cEditorLaunchData {
public:
    uint8_t  mPad00[0x0c];   // +0x000
    uint32_t m0c;            // +0x00c
    uint32_t m10;            // +0x010
    uint32_t m14;            // +0x014
    uint32_t m18;            // +0x018
    uint8_t  mPad1c[8];      // +0x01c
    uint32_t m24;            // +0x024
    uint32_t m28;            // +0x028
    uint32_t m2c;            // +0x02c
    uint32_t m30;            // +0x030
    uint8_t  m34;            // +0x034
    uint8_t  m35;            // +0x035
    uint8_t  m36;            // +0x036
    uint8_t  m37;            // +0x037
    uint8_t  m38;            // +0x038
    uint8_t  m39;            // +0x039
    uint8_t  m3a;            // +0x03a
    uint8_t  mPad3b;         // +0x03b
    uint8_t  m3c;            // +0x03c
    uint8_t  m3d;            // +0x03d
    uint8_t  mPad3e[0x26];   // +0x03e
    uint8_t  m64;            // +0x064
    uint8_t  mPad65[7];      // +0x065
    uint8_t  m6c;            // +0x06c
    uint8_t  m6d;            // +0x06d
    uint8_t  m6e;            // +0x06e
    uint8_t  m6f;            // +0x06f
    uint8_t  mPad70[0x20];   // +0x070
    void*    m90;            // +0x090
    void*    m94;            // +0x094
    void*    m98;            // +0x098
};

// Commodore: the galaxy-game-entry implementation object (retail layout != PDB).
class cGalaxyGameEntryImpl {
public:
    uint8_t  mPad00[0x20];   // +0x000
    uint8_t  m20;            // +0x020
    uint8_t  mPad21[3];      // +0x021
    uint32_t m24;            // +0x024
    uint32_t m28;            // +0x028
    uint32_t m2c;            // +0x02c
    uint32_t m30;            // +0x030
    void*    m34;            // +0x034
    uint32_t m38;            // +0x038
    uint32_t m3c;            // +0x03c
    uint8_t  mPad40[0x68];   // +0x040
    void*    ma8;            // +0x0a8
    void*    mac;            // +0x0ac
    uint8_t  mPadb0[8];      // +0x0b0
    uint32_t mb8;            // +0x0b8
    uint32_t mbc;            // +0x0bc
    uint32_t mc0;            // +0x0c0
    uint32_t mc4;            // +0x0c4
    int32_t  mc8;            // +0x0c8
    uint8_t  mPadcc[4];      // +0x0cc
    uint8_t  md0;            // +0x0d0
    uint8_t  mPadd1[3];      // +0x0d1
    uint32_t md4;            // +0x0d4
    uint32_t md8;            // +0x0d8
    uint32_t mdc;            // +0x0dc
    uint32_t me0;            // +0x0e0

    uint32_t __thiscall FUN_00de0910(uint32_t key);
    void     __thiscall FUN_00de0a30(uint32_t param_1, void* param_2);
    void     __thiscall FUN_00de0ae0(uint32_t arg);
    void     __thiscall FUN_00de0bc0(uint32_t param_2, uint32_t param_3, uint32_t param_4);
    void     __thiscall FUN_00de0e90(uint32_t param_1, uint32_t* param_2, int param_3);
    void     __thiscall FUN_00de0f90();
    bool     __thiscall FUN_00de10a0(uint32_t key, uint32_t* param_2);
    void     __thiscall FUN_00de11a0();
    void     __thiscall FUN_00de1320();
    void     __thiscall FUN_00de1330(uint32_t param_1);
    void     __thiscall FUN_00de13d0(uint32_t param_1, uint32_t param_2);
    void     __thiscall FUN_00de1600(uint32_t* param_1);
};

// ---------------------------------------------------------------------------------------------
// ref-counted handle assignment (AddRef new / Release old, at chosen vtable slots)
// ---------------------------------------------------------------------------------------------
static void AssignRef(void** ppTarget, void* pNew, int nAddSlot, int nRelSlot)
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
// 0x00de0910: pick one of the three UI color keys for the active page button
// ---------------------------------------------------------------------------------------------
// @ 0x00de0910
uint32_t __thiscall cGalaxyGameEntryImpl::FUN_00de0910(uint32_t key)
{
    uint32_t g1[3] = { 0x7d433fad, 0x8f963dcb, 0x441cd3e6 };
    uint32_t g2[3] = { 0xf670aa43, 0x2a5147a9, 0x1a4e0708 };
    uint32_t g3[3] = { 0x9ad7d4aa, 0x1f2a25b6, 0x449c040f };
    uint32_t* pSel = 0;

    void* pWnd = ((tHost*)kGUI_PanelIDs->m184)->FindWindowByID(0x614c680);
    if (pWnd != 0) {
        uint32_t u = ((uint32_t(__thiscall*)(void*))VFN(pWnd, 0x2c))(pWnd);
        if (((u >> 2) & 1) != 0)
            pSel = g1;
    }
    pWnd = ((tHost*)kGUI_PanelIDs->m184)->FindWindowByID(0x614c681);
    if (pWnd != 0) {
        uint32_t u = ((uint32_t(__thiscall*)(void*))VFN(pWnd, 0x2c))(pWnd);
        if (((u >> 2) & 1) != 0)
            pSel = g2;
    }
    pWnd = ((tHost*)kGUI_PanelIDs->m184)->FindWindowByID(0x614c682);
    if (pWnd == 0) {
        if (pSel == 0)
            return 0;
    } else {
        uint32_t u = ((uint32_t(__thiscall*)(void*))VFN(pWnd, 0x2c))(pWnd);
        if (((u >> 2) & 1) == 0) {
            if (pSel == 0)
                return 0;
        } else {
            pSel = g3;
        }
    }

    uint32_t v = m38;
    if (v == 0x1628565e)
        return pSel[0];
    if (v == 0x1628565f)
        return pSel[1];
    if (v != 0x16285660)
        return 0;
    return pSel[2];
}

// ---------------------------------------------------------------------------------------------
// 0x00de0a30: enable/disable a tool page (bitset guarded)
// ---------------------------------------------------------------------------------------------
// @ 0x00de0a30
void __thiscall cGalaxyGameEntryImpl::FUN_00de0a30(uint32_t param_1, void* param_2)
{
    if (((DAT_016a1848[param_1 >> 5] >> (param_1 & 0x1f)) & 1) == 0) {
        ((tHost*)this)->FUN_00e00670(param_1, param_2);
        if (param_1 == 0x1b)
            ((tHost*)kGUI_PanelIDs)->FUN_00de86d0(2, 0);
        ((tHost*)this)->FUN_00e00650(param_1, param_2);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00de0a90: Simulator::cContentValidationSummarizer::cContentValidationSummarizer
// ---------------------------------------------------------------------------------------------
// @ 0x00de0a90  cContentValidationSummarizer::cContentValidationSummarizer
void* __thiscall cContentValidationSummarizer::FUN_00de0a90(void* pOuter, uint8_t b)
{
    mVtbl4 = VTBL(vtbl_CVS);
    m08 = 0;
    mVtbl0 = VTBL(vtbl_0147dc04);
    mVtbl4 = VTBL(vtbl_0149bad8);
    m0c = pOuter;
    m10 = b;
    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x00de0ae0: restart the audio state for the entry panel and re-arm the frame clock
// ---------------------------------------------------------------------------------------------
// @ 0x00de0ae0
void __thiscall cGalaxyGameEntryImpl::FUN_00de0ae0(uint32_t arg)
{
    void* pAudio = FUN_00a206f0();
    uint32_t v = 0;
    if (pAudio != 0)
        v = ((uint32_t(__thiscall*)(void*))VFN(pAudio, 0x20))(pAudio);

    pAudio = FUN_00a206f0();
    if (pAudio != 0) {
        ((void(__thiscall*)(void*, uint32_t))VFN(pAudio, 0x38))(pAudio, 0x3475365);
        ((void(__thiscall*)(void*, uint32_t, uint32_t))VFN(pAudio, 0x40))(pAudio, 0x3475381, 0x41a43586);
        ((void(__thiscall*)(void*, uint32_t, uint32_t))VFN(pAudio, 0x40))(pAudio, 0x3475385, v);
        ((void(__thiscall*)(void*))VFN(pAudio, 0x58))(pAudio);
    }

    void* pObj = FUN_00df5f40();
    ((void(__thiscall*)(void*, int, int))VFN(pObj, 0x60))(pObj, 0, 1);

    m38 = arg;
    ma8 = mac;

    uint32_t nLo = 0;
    uint32_t nHi = 0;
    if (mc8 == 1) {
        __asm { rdtsc }
        __asm { mov nLo, eax }
        __asm { mov nHi, edx }
    } else {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        nLo = li.u.LowPart;
        nHi = li.u.HighPart;
    }
    mb8 = nLo;
    mc4 = 0;
    mc0 = 0;
    mbc = nHi;
}

// ---------------------------------------------------------------------------------------------
// 0x00de0bc0: queue an editor launch for the page whose id matches one of the four slots
// ---------------------------------------------------------------------------------------------
// @ 0x00de0bc0
void __thiscall cGalaxyGameEntryImpl::FUN_00de0bc0(uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    if (param_2 == md4) {
        m38 = 0x156276d1;
    } else if (param_2 == md8) {
        m38 = 0x9adf00a9;
    } else if (param_2 == mdc) {
        m38 = 0x37e82da1;
    } else {
        if (param_2 != me0)
            return;
        m38 = 0xa56567f7;
    }
    m3c = param_2;

    cEditorLaunchData* pEd1;
    {
        void* pRaw = FUN_00f473a0(0x9c, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pEd1 = 0;
        else
            pEd1 = (cEditorLaunchData*)((tHost*)pRaw)->FUN_005a9080();
    }
    pEd1->m0c = m38;
    pEd1->m90 = 0;
    {
        void* pCVS;
        void* pRaw = FUN_00f473a0(0x14, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pCVS = 0;
        else
            pCVS = ((cContentValidationSummarizer*)pRaw)->FUN_00de0a90(this, 1);
        AssignRef(&pEd1->m94, pCVS, 0, 4);
    }
    pEd1->m24 = DAT_015da784;
    pEd1->m28 = DAT_015da788;
    pEd1->m2c = DAT_015da78c;
    pEd1->m30 = DAT_015da790;
    pEd1->m34 = 0;
    pEd1->m36 = 1;
    pEd1->m37 = 1;
    pEd1->m38 = 1;
    pEd1->m3a = 1;
    pEd1->m3d = 0;
    pEd1->m3c = 1;
    pEd1->m64 = 1;
    pEd1->m6d = 0;
    pEd1->m6e = 0;
    pEd1->m6f = 1;
    pEd1->m6c = 1;

    cEditorLaunchData* pEd2;
    {
        void* pRaw = FUN_00f473a0(0x9c, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pEd2 = 0;
        else
            pEd2 = (cEditorLaunchData*)((tHost*)pRaw)->FUN_005a9080();
    }
    pEd2->m0c = 0x465c50ba;
    pEd2->m90 = 0;
    {
        void* pCVS;
        void* pRaw = FUN_00f473a0(0x14, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pCVS = 0;
        else
            pCVS = ((cContentValidationSummarizer*)pRaw)->FUN_00de0a90(this, 1);
        AssignRef(&pEd2->m94, pCVS, 0, 4);
    }
    pEd2->m24 = DAT_015da784;
    pEd2->m28 = DAT_015da788;
    pEd2->m2c = DAT_015da78c;
    pEd2->m30 = DAT_015da790;
    pEd2->m34 = 0;
    pEd2->m36 = 1;
    pEd2->m37 = 1;
    pEd2->m38 = 1;
    pEd2->m3a = 1;
    pEd2->m3d = 0;
    pEd2->m3c = 0;
    pEd2->m64 = 1;
    pEd2->m6d = 0;
    pEd2->m6e = 0;
    pEd2->m6f = 1;

    AssignRef(&pEd2->m98, pEd1, 4, 8);

    void* pCVS4;
    {
        void* pRaw = FUN_00f473a0(0x14, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pCVS4 = 0;
        else
            pCVS4 = ((cContentValidationSummarizer*)pRaw)->FUN_00de0a90(this, 1);
    }

    FUN_00de5d00(param_2, kGUI_PanelIDs, 0, param_3, param_4, pCVS4, pEd2);
}

// ---------------------------------------------------------------------------------------------
// 0x00de0e90: build and queue a plain "Simulator" editor launch record
// ---------------------------------------------------------------------------------------------
// @ 0x00de0e90
void __thiscall cGalaxyGameEntryImpl::FUN_00de0e90(uint32_t param_1, uint32_t* param_2, int param_3)
{
    kGUI_PanelIDs->m188 = param_2[0];
    kGUI_PanelIDs->m18c = param_2[1];
    kGUI_PanelIDs->m190 = param_2[2];

    cString str;
    ((tHost*)&str)->FUN_006b5060();

    cEditorLaunchData* pEd;
    {
        void* pRaw = FUN_00f473a0(0x9c, k_szSimulator, 0, 0, 0, 0);
        if (pRaw == 0) {
            pEd = 0;
        } else {
            pEd = (cEditorLaunchData*)((tHost*)pRaw)->FUN_005a9080();
            if (pEd != 0)
                ((void(__thiscall*)(void*))VFN(pEd, 4))(pEd);
        }
    }
    pEd->m0c = param_1;
    pEd->m10 = param_2[0];
    pEd->m14 = param_2[1];
    pEd->m18 = param_2[2];
    pEd->m34 = 1;
    pEd->m36 = 1;
    pEd->m38 = 1;
    pEd->m37 = 1;
    pEd->m39 = 1;
    pEd->m3a = 1;
    pEd->m3c = 0;
    pEd->m3d = 0;
    pEd->m64 = 1;
    pEd->m35 = 0;
    pEd->m24 = DAT_015da784;
    pEd->m28 = DAT_015da788;
    pEd->m2c = DAT_015da78c;
    pEd->m30 = DAT_015da790;
    pEd->m6d = 0;
    pEd->m6e = 0;
    pEd->m6f = 1;

    ((tHost*)FUN_00b3d320(pEd))->FUN_00b1dee0();
    ((void(__thiscall*)(void*))VFN(pEd, 8))(pEd);

    ((tHost*)&str)->FUN_006b5240();
}

// ---------------------------------------------------------------------------------------------
// 0x00de0f90: SP::cGalaxyGameEntryImpl::OnToolPanelButton
// ---------------------------------------------------------------------------------------------
// @ 0x00de0f90  cGalaxyGameEntryImpl::OnToolPanelButton
void __thiscall cGalaxyGameEntryImpl::FUN_00de0f90()
{
    ((tHost*)kGUI_PanelIDs->m198)->FUN_00de0670(0, 0);
    ((tHost*)((char*)this + 8))->FUN_0093a2e0();
    if (m34 != 0) {
        ((void(__thiscall*)(void*, int))VFN(m34, 0xc))(m34, 0);
        void* p = m34;
        if (p != 0) {
            m34 = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
    }

    void* pAudio = FUN_00a206f0();
    uint32_t v = 0;
    if (pAudio != 0)
        v = ((uint32_t(__thiscall*)(void*))VFN(pAudio, 0x20))(pAudio);

    pAudio = FUN_00a206f0();
    if (pAudio != 0) {
        ((void(__thiscall*)(void*, uint32_t))VFN(pAudio, 0x38))(pAudio, 0x3475365);
        ((void(__thiscall*)(void*, uint32_t, uint32_t))VFN(pAudio, 0x40))(pAudio, 0x3475381, 0xf1a5961c);
        ((void(__thiscall*)(void*, uint32_t, uint32_t))VFN(pAudio, 0x40))(pAudio, 0x3475385, v);
        ((void(__thiscall*)(void*))VFN(pAudio, 0x58))(pAudio);
    }

    void** it = kGUI_PanelIDs->m1d8;
    if (it != kGUI_PanelIDs->m1dc) {
        do {
            void* p = *it;
            ((void(__thiscall*)(void*, int))VFN(p, 0x2c))(p, 0);
            it++;
        } while (it != kGUI_PanelIDs->m1dc);
    }

    ((tHost*)kGUI_PanelIDs)->FUN_00de53d0(0);

    void* pWnd = ((tHost*)kGUI_PanelIDs->m184)->FindWindowByID(0x3685038);
    if (pWnd != 0)
        ((void(__thiscall*)(void*, int, int))VFN(pWnd, 0x7c))(pWnd, 1, 0);
}

// ---------------------------------------------------------------------------------------------
// 0x00de10a0: dispatch an app-mode message (page mode change / editor request)
// ---------------------------------------------------------------------------------------------
// @ 0x00de10a0
bool __thiscall cGalaxyGameEntryImpl::FUN_00de10a0(uint32_t key, uint32_t* param_2)
{
    if (key == 0x7c3cd3d) {
        if (param_2[2] == 2) {
            void* p = FUN_00dd9190();
            ((tHost*)p)->FUN_00ddb760();
            m20 = 0;
        }
        if (param_2[2] == 0)
            m20 = 1;
        if (param_2[2] == 3)
            ((tHost*)kGUI_PanelIDs)->FUN_00de53d0(0);
        return true;
    }
    if (key != 0xcc0bf723)
        return false;

    if (md0 != 0) {
        md0 = 0;
        uint32_t n = param_2[0];
        if (n == 2) {
            uint32_t* rec = FUN_00ef19f0();
            rec[0] = m24;
            rec[1] = m28;
            rec[2] = m2c;
            rec[3] = 0;
            rec[4] = 0;
            rec[5] = 0;
            rec[6] = 0;
            rec[7] = 0;
            rec[8] = 0;
            m30 = 10;
            void* p = FUN_00b3d410(1, &DAT_01654c10, 1);
            ((tHost*)p)->FUN_00e3e350();
            return true;
        }
        if (n != 1 && n != 3)
            return true;
        m24 = 0;
        m28 = 0;
        m38 = 0;
        m2c = 0;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x00de11a0: refresh two tool-panel buttons from the app-preferences properties
// ---------------------------------------------------------------------------------------------
// @ 0x00de11a0
void __thiscall cGalaxyGameEntryImpl::FUN_00de11a0()
{
    uint8_t b1 = 0;
    void* pPrefs = g_pAppPreferences;
    if (pPrefs != 0) {
        int local;
        bool ok = ((bool(__thiscall*)(void*, uint32_t, int*))VFN(pPrefs, 0x24))(pPrefs, 0x80d8460, &local);
        if (ok && (*(uint16_t*)((char*)local + 0x12) == 1)) {
            bool* p = ((tHost*)local)->FUN_0041e920();
            b1 = *(uint8_t*)p;
        }
    }
    void* pWnd = ((tHost*)kGUI_PanelIDs->m184)->FindWindowByID(0x7a7ee50);
    if (pWnd != 0) {
        bool bOff = (b1 == 0);
        ((void(__thiscall*)(void*, int, bool))VFN(pWnd, 0x7c))(pWnd, 1, bOff);
    }

    uint8_t b2 = 0;
    if (pPrefs != 0) {
        int local;
        bool ok = ((bool(__thiscall*)(void*, uint32_t, int*))VFN(pPrefs, 0x24))(pPrefs, 0x80d8470, &local);
        if (ok && (*(uint16_t*)((char*)local + 0x12) == 1)) {
            bool* p = ((tHost*)local)->FUN_0041e920();
            b2 = *(uint8_t*)p;
        }
    }
    pWnd = ((tHost*)kGUI_PanelIDs->m184)->FindWindowByID(0x809b111);
    if (pWnd != 0) {
        bool bOff = (b2 == 0);
        ((void(__thiscall*)(void*, int, bool))VFN(pWnd, 0x7c))(pWnd, 1, bOff);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00de1320: clear the active key and refresh the tool-panel buttons
// ---------------------------------------------------------------------------------------------
// @ 0x00de1320
void __thiscall cGalaxyGameEntryImpl::FUN_00de1320()
{
    m38 = 0;
    this->FUN_00de11a0();
}

// ---------------------------------------------------------------------------------------------
// 0x00de1330: show the sporepedia context and prime the tool panel
// ---------------------------------------------------------------------------------------------
// @ 0x00de1330
void __thiscall cGalaxyGameEntryImpl::FUN_00de1330(uint32_t param_1)
{
    ((tHost*)this)->FUN_00e00760(param_1);
    ((tHost*)kGUI_PanelIDs)->FUN_00de53d0(1);
    ma8 = 0;

    void* pWnd = ((tHost*)kGUI_PanelIDs->m144)->FUN_008105b0(0x615a5ff, 1);
    if (pWnd != 0)
        ((void(__thiscall*)(void*, int, int))VFN(pWnd, 0x7c))(pWnd, 1, 1);
    pWnd = ((tHost*)kGUI_PanelIDs->m144)->FUN_008105b0(0x615a5ff, 1);
    if (pWnd != 0)
        ((void(__thiscall*)(void*, int, int))VFN(pWnd, 0x7c))(pWnd, 1, 0);

    ((tHost*)kGUI_PanelIDs->m184)->FUN_00e01350(1);
    m38 = 0;
    this->FUN_00de11a0();
}

// ---------------------------------------------------------------------------------------------
// 0x00de13d0: map a tool-panel id to an editor-launch request
// ---------------------------------------------------------------------------------------------
// @ 0x00de13d0
void __thiscall cGalaxyGameEntryImpl::FUN_00de13d0(uint32_t param_1, uint32_t param_2)
{
    if (param_1 == 0)
        return;

    switch (param_1) {
    case 0x628565e: m38 = 0x7d433fad; break;
    case 0x625cd50: m38 = DAT_016a0e58; break;
    case 0x625cd51: m38 = 0x465c50ba; break;
    case 0x625cd52: this->FUN_00de0bc0(md4, param_2, 0); return;
    case 0x625cd53: this->FUN_00de0bc0(md8, param_2, 0); return;
    case 0x625cd54: this->FUN_00de0bc0(mdc, param_2, 0); return;
    case 0x4096dd0: m38 = 0x99e92f05; break;
    case 0x4096dd3: m38 = 0x4e3f7777; break;
    case 0x4096dd7: m38 = 0x8707be7d; break;
    case 0x4096dda: m38 = 0x72c49181; break;
    case 0x4656452: m38 = 0x96b24187; break;
    case 0x628565f: m38 = 0xf670aa43; break;
    case 0x6285660: m38 = 0x9ad7d4aa; break;
    case 0x629c446: m38 = 0x8f963dcb; break;
    case 0x629c447: m38 = 0x2a5147a9; break;
    case 0x629c448: m38 = 0x1f2a25b6; break;
    case 0x62afb0d: m38 = 0x441cd3e6; break;
    case 0x62afb1c: m38 = 0x1a4e0708; break;
    case 0x62afb2b: m38 = 0x449c040f; break;
    case 0x6526b7d: m38 = 0xe46c381e; break;
    case 0x7291fb7: this->FUN_00de0bc0(me0, param_2, 0); return;
    default:
        if (param_1 >= 0x1628565e && param_1 <= 0x16285660)
            m38 = this->FUN_00de0910(param_1);
        break;
    }

    uint32_t v = m38;
    m38 = 0;
    m3c = 0;
    uint32_t local[3];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    this->FUN_00de0e90(v, local, 1);
}

// ---------------------------------------------------------------------------------------------
// 0x00de1600: apply/commit the pending editor-launch record
// ---------------------------------------------------------------------------------------------
// @ 0x00de1600
void __thiscall cGalaxyGameEntryImpl::FUN_00de1600(uint32_t* param_1)
{
    if (m38 == 0x7a7f799) {
        if (param_1[0] == 0)
            goto clear;
        m24 = param_1[0];
        m28 = param_1[1];
        m2c = param_1[2];
        md0 = 1;
        {
            void* pObj = *(void**)((char*)g_p16c7aa4 + 0x1c);
            bool ok = ((tHost*)pObj)->FUN_00ec5a60(&m24, 1, 0);
            if (!ok) {
                m24 = 0;
                m28 = 0;
                md0 = 0;
                m2c = 0;
                goto clear;
            }
        }
    }
    if (m38 == 0x7a7f798) {
        if (param_1[0] == 0) {
clear:
            m38 = 0;
            return;
        }
        uint32_t* rec = FUN_00ef19f0();
        rec[0] = 0;
        rec[1] = 0;
        rec[2] = 0;
        rec[3] = param_1[0];
        rec[4] = param_1[1];
        rec[5] = param_1[2];
        rec[6] = 0;
        rec[7] = 0;
        rec[8] = 0;
        m24 = param_1[0];
        m28 = param_1[1];
        m2c = param_1[2];
        m30 = 10;
        void* p = FUN_00b3d410(1, &DAT_01654c10, 1);
        ((tHost*)p)->FUN_00e3e350();
    }
    if (kGUI_PanelIDs->m108 == 3 || kGUI_PanelIDs->m108 == 0xd) {
        uint32_t v = m38;
        m38 = 0;
        m3c = 0;
        if (param_1[0] != 0)
            this->FUN_00de0e90(v, param_1, 1);
    }
}