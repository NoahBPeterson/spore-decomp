// src/game/SPBake/SPEditorBudget.cpp -- migrated from slice(s) s004575d0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorBudget.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorBudget.h"
#include "SP/cSPEditorEconomy.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "EA/COM/IUnknown32.h"

// unnamed retail callees and globals (address in the comment)
extern const char kEditorAllocName[];                                 // 0x013eb430
extern float kBudgetColor[3];                                         // 0x015d2998
extern void* SP_MessageServer();                    // 0x0067dcc0
extern int   FUN_00458b80(int id);                  // 0x00458b80
extern float kOne;                                  // 0x01485720
#include <xmmintrin.h>
#include <math.h>

// ---- items of slice s004575d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Float4 { float x, y, z, w; };
struct cSPEditorEconomy {                  // refcounted, vptr +0, count +4
    virtual void v0();
    virtual int GetWealth(int arg);        // +4
    int mRefCount;
    void AddRef() { int r = mRefCount + 1; mRefCount = mRefCount + 1; (void)r; }
    void Release();                        // 0x00453540 (RefCountTemplate<int>::Release)
};
struct cSPUILayout_s0045_75d0 {                       // vtable: +4 AddRef, +8 Release
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    cSPUILayout_s0045_75d0* Construct();              // 0x00810000 (thiscall, returns this)
    bool Init(const void* key, bool b, unsigned int id);                  // 0x008120d0 (ret 0xc)
    bool SetParentWin(void* parent, bool b, unsigned int id);             // 0x008121b0 (ret 0xc)
    void* FindWindowByID(unsigned int id, bool recursive) const;          // 0x008105b0 (ret 8)
};
struct IWinX {                             // EA::UTFWin::IWindow slots used here
    virtual int AddRef();                  // +0
    virtual int Release();                 // +4
virtual void p02();
virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void p08();
virtual void p09();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
    virtual void p22();
    virtual void SetTextColor(unsigned int rgba);        // +0x5c
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
    virtual void SetFlag(int flag, bool value);          // +0x7c
    virtual void SetCaption(const wchar_t* text);        // +0x80
    virtual void SetTextFontID(unsigned int id);         // +0x84
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
virtual void p47();
virtual void p48();
virtual void p49();
virtual void p50();
virtual void p51();
virtual void p52();
virtual void p53();
virtual void p54();
virtual void p55();
virtual void p56();
virtual void p57();
virtual void p58();
virtual void p59();
virtual void p60();
virtual void p61();
virtual void p62();
virtual void p63();
    virtual void p64();
    virtual void AddWinProc(void* proc);                 // +0x104
};
struct cSPUITooltipWinProc_s0045_75d0 {               // 0x68 bytes, vtable: +0 AddRef, +4 Release
    virtual int AddRef();
    virtual int Release();
    char pad[0x68 - 4];
    cSPUITooltipWinProc_s0045_75d0* Construct();      // 0x00835cc0 (thiscall, returns this)
    void SetText(const wchar_t* text, void* x, char flag);                // 0x00835ed0
};
template <class T>
struct ARCv {                              // intrusive pointer calling vtable AddRef/Release
    T* mpObject;
    ARCv() : mpObject(0) {}
    ARCv(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~ARCv() { if (mpObject) mpObject->Release(); }
    ARCv& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
};
struct EconomyPtr {                        // AddRef inline, Release out of line
    cSPEditorEconomy* mpObject;
    EconomyPtr& operator=(cSPEditorEconomy* p) {
        if (p != mpObject) {
            cSPEditorEconomy* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct WinList {
    void Add(ARCv<IWinX>* p);   // 0x004b54b0 (thiscall, ret 4)
};
struct SimpleVectorU {
    void push_back(const unsigned int& v);   // 0x00454860 (thiscall, ret 4)
};
IWinX* CreateTextWindow(IWinX* parent);                               // 0x008064c0 (cdecl)
void* GetAllocContext();                                              // 0x009512c0
void* AllocNamed(unsigned int size, int align, const char* name, void* ctx);   // 0x009512d0 (cdecl)
void SetMoneyString(double value, wchar_t* buf, int n, const wchar_t* fmt, const wchar_t* sym);   // 0x008822e0 (cdecl)
void* operator_new_named(unsigned int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 (cdecl)
extern const char kEditorAllocName[];                                 // 0x013eb430
extern float kBudgetColor[3];                                         // 0x015d2998
struct cSPEditorBudget {
    char pad0[0x14];
    unsigned short mCurrencyChar;           // +0x14
    char pad16[2];
    int mActualWealth;                      // +0x18
    char pad1c[0x34 - 0x1c];
    ARCv<cSPUILayout_s0045_75d0> mLayout;              // +0x34
    EconomyPtr mEconomy;                    // +0x38
    ARCv<IWinX> mWinBudget;                 // +0x3c
    ARCv<cSPUITooltipWinProc_s0045_75d0> mTooltip;     // +0x40
    WinList mDisplayWindows;                // +0x44
    char pad48[0x58 - 0x48];
    SimpleVectorU mWealthHistory;           // +0x58

    void* AsInterface(unsigned int id);   // 0x00457950
    void  Shutdown();                     // 0x004581d0
    void  Init(const void* key, cSPEditorEconomy* economy, unsigned short currency, IWinX* parent, const wchar_t* tooltipText);   // 0x00457af0
};
extern void* SP_MessageServer();                    // 0x0067dcc0
extern int   FUN_00458b80(int id);                  // 0x00458b80
extern float kOne;                                  // 0x01485720
struct MessageServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void RegisterHandler(void* self, unsigned int msg);   // slot 8 (+0x20)
virtual void v9();
virtual void v10();
    virtual void Send(void* self, unsigned int msg, int flags);   // slot 11 (+0x2c)
};
// ---- items of slice s004575d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void  FUN_00811ad0(void* layout, int one);   // cSPUILayout::Shutdown

// callees this slice defines outside this object (rewrite.py held_callee_protos)
unsigned int ColorRGBAToU32(const float* c);  // 0x004580c0 (stays in the slice: not this object's)

// @ 0x00457950
void * SP::cSPEditorBudget::AsInterface(EA::COM::InterfaceId id)
{
    unsigned int iid = id;
    void* result;
    if (iid == 0xee3f516e) {
        if (this == 0)
            result = 0;
        else
            result = static_cast<EA::COM::IUnknown32 *>(this);
    } else if (iid == 0x726ecf35) {
        result = this;
    } else {
        result = 0;
    }
    return result;
}

// @ 0x004579a0
char __fastcall FUN_004579a0(int* self, int, int msg, int* data)
{
    switch (msg) {
    case 0x3150c27:
        if (data[4] == *(int*)((char*)self + 0x38)) {
            void* o = (void*)self[0xe];
            int r = (*(int(__thiscall**)(void*, int))((*(char**)o) + 4))(o, 0);
            *(int*)((char*)self + 0x18) = r;
            float d = (float)(*(int*)((char*)self + 0x58) - r);
            *(float*)((char*)self + 0x10) = fabsf(d) / kOne;
        }
        return 1;
    case 0x522f9cd: {
        int r = FUN_00458b80(*data);
        if (r != 0) {
            void* o = (void*)self[0xe];
            int q = (*(int(__thiscall**)(void*, int*, int))((*(char**)o) + 0x10))(o, (int*)(r + 0x40), 0);
            *((unsigned char*)self + 0x70) = (q == 2) ? 1 : 0;
        }
        return 1;
    }
    case 0x522f9ce:
        *((unsigned char*)self + 0x70) = 0;
        return 1;
    }
    return 0;
}

// @ 0x00457af0
void cSPEditorBudget::Init(const void* key, cSPEditorEconomy* economy, unsigned short currency, IWinX* parent, const wchar_t* tooltipText)
{
    mEconomy = economy;
    mCurrencyChar = currency;
    ((MessageServer*)SP_MessageServer())->RegisterHandler(this, 0x3150c27);
    ((MessageServer*)SP_MessageServer())->RegisterHandler(this, 0x522f9cd);
    ((MessageServer*)SP_MessageServer())->RegisterHandler(this, 0x522f9ce);
    cSPUILayout_s0045_75d0* raw = (cSPUILayout_s0045_75d0*)operator_new_named(0x18, kEditorAllocName, 0, 0, 0, 0);
    mLayout = raw ? raw->Construct() : 0;
    mLayout.get()->Init(key, true, 0x5b598fa);
    mLayout.get()->SetParentWin(parent, true, 0x5b598fa);
    mWinBudget = (IWinX*)mLayout.get()->FindWindowByID(0x41e98c3, true);
    mActualWealth = mEconomy.mpObject->GetWealth(0);
    mDisplayWindows.Add(&mWinBudget);
    mWealthHistory.push_back((unsigned int&)mActualWealth);
    for (int i = 1; i < 5; i++) {
        IWinX* w = CreateTextWindow(mWinBudget.get());
        if (w) {
            unsigned int fontID = 0x323b4096;
            w->SetTextFontID(fontID);
            Float4 col;
            col.x = kBudgetColor[0];
            col.y = kBudgetColor[1];
            col.z = kBudgetColor[2];
            col.w = (float)(5 - i) / 5.0f;
            w->SetTextColor(ColorRGBAToU32(&col.x));
            w->SetFlag(2, false);
            w->SetFlag(0x10, true);
            ARCv<IWinX> held(w);
            mDisplayWindows.Add(&held);
            mWealthHistory.push_back((unsigned int&)mActualWealth);
            wchar_t sym[2];
            sym[0] = mCurrencyChar;
            sym[1] = 0;
            wchar_t buf[40];
            SetMoneyString((double)mActualWealth, buf, 0x28, L"%-F%-p", sym);
            w->SetCaption(buf);
        }
    }
    if (tooltipText) {
        IWinX* win = (IWinX*)mLayout.get()->FindWindowByID(0x6526734, true);
        if (win) {
            cSPUITooltipWinProc_s0045_75d0* raw2 = (cSPUITooltipWinProc_s0045_75d0*)AllocNamed(0x68, 4, "UI/Tooltip", GetAllocContext());
            mTooltip = raw2 ? raw2->Construct() : 0;
            mTooltip.get()->SetText(tooltipText, (void*)-1, 1);
            win->AddWinProc(mTooltip.get());
        }
    }
}

// @ 0x004581d0
void SP::cSPEditorBudget::Shutdown()
{
    if (mLayout.mpObject != 0) {
        FUN_00811ad0(mLayout.mpObject, 1);
        if (mLayout.mpObject != 0) {
            void* old = mLayout.mpObject;
            mLayout.mpObject = 0;
            ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
        }
    }
    MessageServer* ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x522f9ce, 0xffffd8f1);
    ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x522f9cd, 0xffffd8f1);
    ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x3150c27, 0xffffd8f1);
}
