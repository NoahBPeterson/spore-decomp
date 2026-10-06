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
};
#define MGR()  (*(Mgrs**)((char*)DAT_016c7aa4 + 0x74))

#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VC3(p,off,a,b,c)(((int (__thiscall*)(void*,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c)))
#define VCP0(p,off)     (((void*(__thiscall*)(void*))     VTP(p)[(off)/4])((void*)(p)))
#define VCP1(p,off,a)   (((void*(__thiscall*)(void*,int)) VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VCP2(p,off,a,b) (((void*(__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))

struct cString {
    void Load(int, int, int);
    void* GetText();
    void assign(void*, void*);
};

struct Lay {
    char pad[4];
    bool IsVisible();
    void SetVisibility(int);
    void* FindWindowByID(int, int);
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

extern "C" int  FUN_00efc520();
extern "C" int  FUN_00efc520_i(int);
extern "C" int  FUN_00f0bea0();
extern "C" int  FUN_00ecb730();
extern "C" int  FUN_00ee1630(int);
extern "C" int  FUN_00ee16f0();
extern "C" int  FUN_00ee2960(int);
extern "C" int  FUN_00ee3020_(void*);
extern "C" int  FUN_00ee31d0_(void*);
extern "C" int  FUN_00ed8a30(int);
extern "C" int  FUN_00edc0e0(void*, int);
extern "C" int  FUN_00ee31d0_tail(void*);
struct Ed14 { void F6c0200(); };
extern "C" void* SP_MessageServer();
extern "C" void  SPUIHelpers_RemoveWindowCallback(void*, void*);
extern "C" void  SPUIHelpers_CreateCallbackWinProc(void*, void*, int, int, void*);
bool __cdecl f00edf370(int p1, int* p2, int p3);

struct Beh {
    char pad[0x300];
    void F3020();
    void F30D0();
    void F3140(int);
    void F31D0();
    void F3230();
    void F3540(int);
    void F3630();
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
            int u = FUN_00efc520_i(*(int*)(t + 0x20));
            FUN_00ed8a30(u);
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

// ============================================================ 0x00ee3020  (partial)
// @ 0x00ee3020
void Beh::F3020()
{
    (void)this;   // full palette-item loop not reconstructed (see partial.txt)
}

// ============================================================ 0x00ee2860  (partial)
// @ 0x00ee2860
void __cdecl f00ee2860(int p1, int p2, cString* p3)
{
    (void)p1; (void)p2; (void)p3;   // string/tooltip construction not reconstructed
}

// ============================================================ 0x00ee2960  (partial)
// @ 0x00ee2960
void __cdecl f00ee2960(int a)
{
    (void)a;   // 1722-byte item-refresh handler not reconstructed
}

// ============================================================ 0x00ee3230  (partial)
// @ 0x00ee3230
void Beh::F3230()
{
    (void)this;   // 454-byte list rebuild not reconstructed
}

// ============================================================ 0x00ee3430  (partial)
// @ 0x00ee3430
void __cdecl f00ee3430(int a, void* b)
{
    (void)a; (void)b;   // 260-byte tutorial/index handler not reconstructed
}

// ============================================================ 0x00ee3540  (partial)
// @ 0x00ee3540
void Beh::F3540(int a)
{
    (void)this; (void)a;   // 233-byte handler not reconstructed
}

// ============================================================ 0x00ee3630  (partial)
// @ 0x00ee3630
void Beh::F3630()
{
    (void)this;   // 213-byte handler not reconstructed
}

