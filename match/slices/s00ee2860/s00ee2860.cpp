// Slice s00ee2860 -- 0x00ee2860..0x00ee3760  (/O2 /MD /Gy /TP /fp:fast)
//
// Scenario-edit-mode behaviour palette UI (same editor object as slice
// s00edcfc0: layout at +0x10, selected behaviour at +0x20, embedded list at
// +0x4c, pie-menu proc at +0xbc, flags at +0xc6/+0xc8).
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void* DAT_016c7aa4;

struct Mgrs {
    char pad00[0x10];
    int  f10;
    int  F3be60(int);
    int  F45970();
    int  F45a80();
    int  F3e8a0(int);                       // 0x00f3e8a0  TutorialManager::Find
    int* F3bf00(int, int);                  // 0x00f3bf00
    int  F43a10(int, int, int, int);        // 0x00f43a10
    void F427c0();                          // 0x00f427c0
};
#define MGR()  (*(Mgrs**)((char*)DAT_016c7aa4 + 0x74))
#define GD4()  (*(ChecklistUI**)((char*)DAT_016c7aa4 + 0xd4))
#define G7C()  (*(TipObj**)((char*)DAT_016c7aa4 + 0x7c))

#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VC3(p,off,a,b,c)(((int (__thiscall*)(void*,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c)))
#define VCP0(p,off)     (((void*(__thiscall*)(void*))     VTP(p)[(off)/4])((void*)(p)))
#define VCP1(p,off,a)   (((void*(__thiscall*)(void*,int)) VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VCP2(p,off,a,b) (((void*(__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))

struct cString {
    cString();                              // 0x006b5060
    ~cString();                             // 0x006b5240
    void Load(u32 tableId, u32 instanceId, int def);   // 0x006b54b0
    const wchar_t* GetText();               // 0x006b55c0
    u32 mData[5];                           // retail size 0x14
};

// eastl::basic_string<wchar_t>
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocator;
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

// tooltip provider object (global at 0x016c7aa4 + 0x7c)
struct TipObj {
    char    pad00[0x24];       // +0x00
    WString mHint;             // +0x24
    WString mText;             // +0x34
};

// eastl::CharStrlen for wchar_t (element count)
inline int CharStrlen(const wchar_t* p) throw()
{
    const wchar_t* p0 = p;
    while (*p)
        ++p;
    return (int)(p - p0);
}

extern const u32     kTutorialTypeTable[12];   // 0x0148a544
extern const u32     kTooltipIds[26];          // 0x0148a6a0
extern const wchar_t kEmptyStr[];              // 0x013ec468

extern "C" __declspec(dllimport) long __cdecl _wtol(const wchar_t*);   // 0x13cc4ec
extern "C" int wcscmp(const wchar_t*, const wchar_t*);

struct Lay {
    char pad[4];
    bool IsVisible();
    void SetVisibility(int);
    void* FindWindowByID(int, int);
    void* At(int);                         // 0x00e09c90 (ret 4)
};
struct Sub48 {
    char pad[4];
    void F9990(int);
    void FC0E0(int);
};
struct Pie {
    char pad[4];
    void Hide();
};
struct Win16 { char pad[4]; void F16F0(); };

struct Tut { bool F254D0(); };                              // 0x00f254d0 IsLocked
struct ChecklistUI {
    bool HasIndex();                       // 0x00ef72a0
    void ToggleHint(int, int);             // 0x00efbbe0
    void F67C8C0(u32, int);                // 0x0067c8c0 (ret 8)
    void F67C830(u32);                     // 0x0067c830 (ret 8)
};
struct NounMgr { void* GetAvatar(); };                      // 0x00b1fdb0
struct IWin {                                              // vtable-only window
    virtual void* GetText();               // slot 0x3c
};
// window text accessor (vtable slot 0x3c; retail: IWindow::GetText)
#define WGETTEXT(p) (((const wchar_t* (__thiscall*)(void*))VTP((p))[0x3c / 4])((void*)(p)))

extern "C" int  FUN_00efc520();
extern "C" int  FUN_00efc520_i(int);
extern "C" int  FUN_00f0bea0();
extern "C" int  FUN_00ecb730();
extern "C" int  FUN_00ee1630(int);
extern "C" int  FUN_00ee16f0();
extern "C" int  FUN_00ee3020_(void*);
extern "C" int  FUN_00ee31d0_(void*);
extern "C" int  FUN_00edc0e0(void*, int);
extern "C" int  FUN_00ee31d0_tail(void*);
struct Ed14 { void F6c0200(); };
extern "C" void* SP_MessageServer();
extern "C" void  SPUIHelpers_RemoveWindowCallback(void*, void*);
extern "C" void  SPUIHelpers_CreateCallbackWinProc(void*, void*, int, int, void*);
bool __cdecl f00edf370(int p1, int* p2, int p3);

// scenario-edit behaviour palette helpers
extern "C" void* FUN_00a206f0();                  // EA::Audio::GetSystemAT
extern "C" void  FUN_00ed8a30(int, int);          // cdecl 2
extern "C" int   FUN_00efc910();                  // ScenarioTutorials_GetObjectA
extern "C" int   FUN_00efe5c0();
extern "C" int   FUN_00ed9990();                  // thiscall (obj, int)
extern "C" int   FUN_00ece300();                  // thiscall (obj)
extern "C" int   FUN_00dfbb60();                  // thiscall (obj)
extern "C" int   FUN_00f2bd10();                  // thiscall (obj)
extern "C" int   FUN_00f0bc80(int*);
extern "C" int   FUN_00ecb730();
extern "C" int   FUN_00edd310(void*, int, int);           // cdecl 3
extern "C" char  FUN_00edd370(void*, int, int);           // cdecl 3
extern "C" void* FUN_0067cac0();                          // 0x15fcc54 getter
extern "C" void* FUN_00edca20(void*);                     // cdecl 1
extern "C" void* SP_NounManager();                        // 0x00b3d300
extern "C" int   FUN_00efe930();                          // thiscall (0x15ad328, int)
extern "C" int   FUN_00ef72a0();                          // thiscall () -> bool
extern "C" int   FUN_00f254d0();                          // thiscall () -> bool
extern "C" int   FUN_007f54d0();                          // thiscall () -> int

void __cdecl f00ee2860(int p1, cString* p2, cString* p3);

struct TextBuf { u32 m[5]; };                             // text container (retail frame 0x19c, object at +0x14)
extern "C" int  FUN_00e09c90();                           // thiscall (int) -> layout
extern "C" int  FUN_008105b0();                           // thiscall (id, bool) -> window

// 0x00ee2960 is defined in s00ee2860_pal.h (second TU, same names/signature)
class IWindow;
struct PaletteItem;
void __cdecl f00ee2960(IWindow*, PaletteItem*, bool, bool);

struct Beh {
    char pad[0x300];
    void F3020();
    void F30D0();
    void F3140(int);
    void F31D0();
    void F3540(void* item, void* list);
    void F3630(int arg);
    void F3710(int);
    void F3760(int*);
    void FEDD810();
    void FEDDA20();
    void FEDF240();
    void FEDF410();
    void FEDF4C0();
    void FEDF510();
    void FEE16F0();
    void FEDFBF0(int*);
    void FEDF2C0(int, int);
};

// ============================================================ 0x00ee30d0
// @ 0x00ee30d0
void Beh::F30D0()
{
    char* t = (char*)this;
    if (!((Lay*)*(void**)(t + 0x10))->IsVisible())
        return;
    FUN_00f0bea0();
    FUN_00ecb730();
    FUN_00ee1630(*(int*)(t + 0x20));
    FEDF240();
    FEDF410();
    *(int*)(t + 0x28) = 0;
    ((Lay*)*(void**)(t + 0x10))->SetVisibility(0);
    void* w = *(void**)(t + 0x18);
    if (w != 0)
        VC2(w, 0x7c, 1, 0);
    FEE16F0();
    FEDF4C0();
}

// ============================================================ 0x00ee3140
// @ 0x00ee3140
void Beh::F3140(int param)
{
    char* t = (char*)this;
    if (*(int*)(t + 0x20) == param)
        return;
    if (((Lay*)*(void**)(t + 0x10))->IsVisible()) {
        if (param == -1) {
            ((Sub48*)(t + 0x48))->F9990(0);
            FUN_00ed8a30(FUN_00efc520(), *(int*)(t + 0x20));
            return;
        }
        if (param == -2) {
            F30D0();
            return;
        }
        FUN_00ee1630(*(int*)(t + 0x20));
        *(int*)(t + 0x20) = param;
        *(int*)(t + 0x28) = 0;
        FEDF4C0();
        FEE16F0();
        FEDF510();
        return;
    }
    *(int*)(t + 0x20) = param;
    FEE16F0();
}

// ============================================================ 0x00ee31d0
// @ 0x00ee31d0
void Beh::F31D0()
{
    char* t = (char*)this;
    Mgrs* m = MGR();
    if (m == 0)
        return;
    int u = FUN_00efc520();
    FEDD810();
    ((Win16*)*(void**)(t + 0x18))->F16F0();
    ((Sub48*)*(void**)(t + 0x48))->FC0E0(u);
    F3020();
    int o = m->F3be60(u);
    if (o != 0) {
        *(int*)(t + 0x2c) = *(int*)(o + 0x80);
        FEDDA20();
    }
}

// ============================================================ 0x00ee3400
// @ 0x00ee3400
void __cdecl f00ee3400(void* self)
{
    char* t = (char*)self;
    ((Pie*)*(void**)(t + 0xbc))->Hide();
    *(char*)(t + 0xc6) = 0;
    *(int*)(t + 0xc8) = -1;
    ((Beh*)self)->F31D0();
}

// ============================================================ 0x00ee3710
// @ 0x00ee3710
void Beh::F3710(int param)
{
    char* t = (char*)this;
    if (!((Lay*)*(void**)(t + 0x10))->IsVisible()) {
        *(int*)(t + 0x20) = param;
        ((Lay*)*(void**)(t + 0x10))->SetVisibility(1);
        FEE16F0();
        FEDF510();
        return;
    }
    F3140(param);
}

// ============================================================ 0x00ee3760
// @ 0x00ee3760
void Beh::F3760(int* arg)
{
    char* t = (char*)this;
    void* edi = (this != 0) ? (void*)(t + 4) : 0;
    void* ms = SP_MessageServer();
    VC3(ms, 0x2c, (int)edi, 0x30c11c7, 0xffffd8f1);
    if (*arg == 0) {
        void* g = *(void**)((char*)DAT_016c7aa4 + 0x14);
        ((Ed14*)g)->F6c0200();
        if ((void*)g == 0)
            return;
        ((Beh*)g)->F31D0();
        return;
    }
    FEDFBF0(arg);
    void* c = *(void**)(t + 0xc);
    VC1(c, 0x1c, *(int*)(t + 8));
    int ebx = *(int*)(t + 0x10);
    if (ebx == 0)
        return;
    int esi2 = *(int*)(t + 0xc);
    FEDF2C0(ebx, 0);
    SPUIHelpers_CreateCallbackWinProc((void*)ebx, (void*)&f00edf370, 2, 0, (void*)esi2);
}

// ============================================================ 0x00ee2860
// @ 0x00ee2860
void __cdecl f00ee2860(int p1, cString* p2, cString* p3)
{
    TipObj* tip = G7C();
    if (tip == 0)
        return;

    cString s;
    s.Load(0x21851ebe, 0x7d91076, 0);

    u32 k = *(u32*)((char*)p1 + 0x184);
    if ((int)k > -1 && k < 0x1a)
    {
        if (k == 0x15)
            s.Load(0xf3108302, 0x7ec7659, 0);
        else
            s.Load(0x21851ebe, kTooltipIds[k], 0);
    }

    const wchar_t* a = s.GetText();
    tip->mText.assign(a, a + CharStrlen(a));

    u32 id;
    if (p2 != 0)
    {
        const wchar_t* c = p2->GetText();
        tip->mHint.assign(c, c + CharStrlen(c));
        id = 0x7d91137;
    }
    else
        id = 0x7d91139;

    p3->Load(0x21851ebe, id, 0);
}

// ============================================================ 0x00ee3020
// @ 0x00ee3020
void Beh::F3020()
{
    Mgrs* m = MGR();
    char* t = (char*)this;
    if (m == 0)
        return;

    int o = m->F3be60(FUN_00efc520());
    int count = (*(int*)(o + 0x88) - *(int*)(o + 0x84)) / 0x188;

    int i = 0, off = 0;
    do
    {
        int p = (i < count) ? (*(int*)(o + 0x84) + off) : 0;
        f00ee2960(
            (IWindow*)((Lay*)((Lay*)(t + 0x4c))->At(i))->FindWindowByID(i + 0x715cde0, 1),
            (PaletteItem*)p, i == count, *(bool*)(t + 0xc6));
        off += 0x188;
        ++i;
    } while (off < 0x498);
}

// ============================================================ 0x00ee3230
// @ 0x00ee3230
void __cdecl f00ee3230(int key, void* self)
{
    char* t = (char*)self;
    MGR()->F45970();
    int active = FUN_00efc520();

    int idx = -1;
    for (int i = 0; i < 0xc; ++i)
    {
        if (key == (int)kTutorialTypeTable[i])
        {
            idx = i;
            break;
        }
    }

    int pid = *(int*)(t + 0xc8);
    int other = -1;
    int found = MGR()->F3e8a0(pid);
    int keep = pid;
    if (idx == 9 && found != 0 && !((Tut*)found)->F254D0())
    {
        keep = -1;
        other = pid;
    }

    int res = MGR()->F43a10(active, idx, keep, other);
    MGR()->F45a80();

    int vol = 0;
    void* au = FUN_00a206f0();
    if (au != 0)
        vol = VC0(au, 0x20);
    void* au2 = FUN_00a206f0();
    if (au2 != 0)
    {
        VC1(au2, 0x38, 0x3475365);
        VC2(au2, 0x40, 0x3475381, 0xcfe8f73d);
        VC2(au2, 0x40, 0x3475385, vol);
        VC0(au2, 0x58);
    }

    int* r = MGR()->F3bf00(active, res);
    if (*r == 2)
        GD4()->ToggleHint(0x6a, 0x6b);
    if (*r == 6)
    {
        if (MGR()->F3e8a0(r[1]) != 0)
            GD4()->ToggleHint(0x7b, 0x7c);
    }

    ((Pie*)*(void**)(t + 0xbc))->Hide();
    t[0xc6] = 0;
    *(int*)(t + 0xc8) = -1;
    ((Beh*)self)->F31D0();
    MGR()->F427c0();

    if (*r == 2)
    {
        FUN_00ecb730();
        FUN_00f0bc80(r);
    }

    void* av = ((NounMgr*)SP_NounManager())->GetAvatar();
    if (av != 0)
    {
        void* q = (char*)av + 0x5a8;
        void* sel = (void*)((int (__thiscall*)(void*))VTP(q)[3])(q);
        ((void (__thiscall*)(void*, int))FUN_00efe930)((void*)0x15ad328, (int)sel);
    }
}

// ============================================================ 0x00ee3430
// @ 0x00ee3430
void __cdecl f00ee3430(int key, void* self, char flag)
{
    char* t = (char*)self;
    if (((ChecklistUI*)GD4())->HasIndex())
        return;

    if (!flag)
    {
        GD4()->F67C8C0(0xf81dec23, 0);
        return;
    }

    int pid = *(int*)(t + 0xc8);

    TextBuf s;
    ((void (__thiscall*)(void*))FUN_00f2bd10)(&s);

    int idx = -1;
    for (int i = 0; i < 0xc; ++i)
    {
        if (key == (int)kTutorialTypeTable[i])
        {
            idx = i;
            break;
        }
    }

    FUN_00edd310(&s, idx, pid);
    char ok = FUN_00edd370(&s, *(int*)(t + 0xcc), *(int*)(t + 0xd0));

    GD4()->F67C8C0(0xf81dec23, 0);

    if (!ok)
    {
        cString s2;
        f00ee2860((int)&s, 0, &s2);
        GD4()->F67C830(0xf81dec23);
        s2.~cString();
    }

    ((void (__thiscall*)(void*))FUN_00dfbb60)(&s);
}

// ============================================================ 0x00ee3540
// @ 0x00ee3540
void Beh::F3540(void* item, void* list)
{
    char* t = (char*)this;
    if (list == 0)
        return;

    int n = (int)_wtol(WGETTEXT(item));
    if (wcscmp(WGETTEXT(item), kEmptyStr) == 0 || n == 0)
        n = 1;

    void* pv = FUN_00edca20(item);
    int slot;
    if (pv != 0)
        slot = ((int (__thiscall*)(void*))VTP(pv)[0x1c / 4])(pv) - 0x715cde0;
    else
        slot = 0;

    int* cell = (int*)(slot * 0x188 + 0xc + *(int*)((char*)list + 0x84));
    if (*cell != n)
    {
        MGR()->F45970();
        *cell = n;
        MGR()->F45a80();
    }

    F31D0();
    MGR()->F427c0();
}

// ============================================================ 0x00ee3630
// @ 0x00ee3630
void Beh::F3630(int arg)
{
    char* t = (char*)this;
    int* o = (int*)FUN_00efc910();
    if (o != 0)
    {
        F3140(*o);
    }
    else if (*(int*)(t + 0x20) != -1)
    {
        if (((Lay*)*(void**)(t + 0x10))->IsVisible())
        {
            ((Sub48*)(t + 0x48))->F9990(0);
            FUN_00ed8a30(FUN_00efc520(), *(int*)(t + 0x20));
        }
        else
        {
            *(int*)(t + 0x20) = -1;
            FEE16F0();
        }
    }

    if (FUN_00efe5c0() != 0)
    {
        FUN_00ed8a30(FUN_00efc520(), *(int*)(t + 0x20));
        ((Sub48*)(t + 0x48))->F9990(1);
    }

    if (*(int*)(t + 0x14) != 0)
    {
        if (*(int*)(t + 0x20) != ((int (__thiscall*)(void*))FUN_007f54d0)(*(void**)(t + 0x14)))
            ((void (__thiscall*)(void*, int))VTP(*(void**)(t + 0x14))[0x1c / 4])(*(void**)(t + 0x14), *(int*)(t + 0x20));
        void* inner = *(void**)((char*)*(void**)(t + 0x14) + 0x24);
        ((void (__thiscall*)(void*, int))VTP(inner)[0x18 / 4])(inner, arg);
        ((void (__thiscall*)(void*))FUN_00ece300)(*(void**)(t + 0x14));
    }

    for (u32 i = 0; i < 6; ++i)
    {
        void* p = ((void**)*(void***)(t + 0x1c))[i];
        if (p != 0)
            ((void (__thiscall*)(void*, int))VTP(p)[0x18 / 4])(p, arg);
    }
}


// ============================================================ 0x00ee2960
// The palette item refresh lives in its own header (compiled here with the module's /EHsc flags,
// which adds an EH frame; the best byte comparison was with /O2 /MD /Gy /TP /GS-).
#include "s00ee2860_pal.h"
