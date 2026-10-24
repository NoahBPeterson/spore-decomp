// Slice s00eceab0 (bfs3 slice 24) -- SP editor dev/scenario swatch UI helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

#define C0(p, off)      ((void(__thiscall*)(void*))((*(void***)(p))[(off) / 4]))(p)
#define C1(p, off, a)   ((void(__thiscall*)(void*, int))((*(void***)(p))[(off) / 4]))(p, a)
#define C2(p, off, a, b) ((void(__thiscall*)(void*, int, int))((*(void***)(p))[(off) / 4]))(p, a, b)
#define K0(p, off)      ((int(__thiscall*)(void*))((*(void***)(p))[(off) / 4]))(p)
#define K1(p, off, a)   ((int(__thiscall*)(void*, int))((*(void***)(p))[(off) / 4]))(p, a)

extern char vtbl_Async[];
extern char vtbl_AddRef[];
extern char vtbl_cSPScenarioSwatchEditItemUI[];
extern char vtbl_TextZoomName[];

void* __cdecl FUN_00401020();
void  __cdecl FUN_005f0c60(int a, int b);
void  __cdecl FUN_005f0a60(int a);

// cSPUILayout::FindWindowByID(unsigned, bool) const -- the layout pointer is the `this`
// of the call, not a stack argument.
class cSPUILayout {
public:
    void* FindWindowByID(unsigned id, bool flag) const;   // @ 0x008105b0
};

// Direct thiscall callee 0x005f0c60: (this = manager from FUN_00401020, value object, float).
struct ValueSink {
    void SetValue(int v, float f);                        // @ 0x005f0c60
};
void  __cdecl FUN_00834fa0(int a, int b, int c, int d, int e, int f, int g);
int*  __cdecl cSPUILayout_FindWindowByID3(void* l, int id);
void  __cdecl FUN_00808230(int a, void* b);
int   __cdecl FUN_00834c60(int a);
int   __cdecl FUN_00834e30();
int   __cdecl FUN_00ece410(void* a);
int   __cdecl FUN_00ece3b0(int a);
void  __cdecl FUN_00ecf000();
void  __cdecl FUN_00ecf320(int a, int b, int c, int d, int e);
void  __cdecl FUN_00ecd9a0();
void  __cdecl FUN_00ecd9c0();
void  __cdecl SPUIHelpers_VisitWindowTreeDepthFirst(int a, void* f, int b);
float __cdecl SPUIHelpers_GetElapsedSeconds();
void  __cdecl FUN_00ece140(int a);
void  __cdecl FUN_00ef0b30();
void  __cdecl FUN_00ecda00();
int   __cdecl SP_PropertyManager();
int*  __cdecl FUN_0113ae10();
int   __cdecl FUN_00b3d320();
void* __cdecl UI_TextZoomName_ctor();

// ============================================================ 0x00eceab0 (LoadLayout, big)
void FUN_00eceab0(int param_1, int param_2)
{
    // reference-counted palette-item assignment + property push; partial.
    int* cur = *(int**)(param_1 + 4);
    if ((int*)param_2 != cur) {
        if (param_2)
            ((void(__thiscall*)(void*))(((void**)(param_2))[1]))((void*)param_2);
        *(int*)(param_1 + 4) = param_2;
        if (cur)
            ((void(__thiscall*)(void*))(((void**)cur)[2]))(cur);
    }
    int* pm = (int*)SP_PropertyManager();
    C1(pm, 0x2c, 0);
}

// ============================================================ 0x00ecefc0
// Value object reachable from SwatchRecvUI::mpValue (+0x4c) at +0x118, and the flag word
// at +0x4 of that object.
struct SwatchInner {
    unsigned char pad00[0x4];
    unsigned int  mFlags;        // +0x4
};
struct SwatchValue {
    unsigned char pad00[0x118];
    SwatchInner*  mpInner;       // +0x118
};

// Message record passed as the second stack argument to 0x00ecf0f0.
struct SwatchMessage {
    unsigned char pad00[0x10];
    void*         mpValue;       // +0x10
    unsigned char pad14[0x4];
    int           mnArg18;       // +0x18
    unsigned char pad1c[0x4];
    void*         mpOwner;       // +0x20
};

struct SwatchRecvUI {
    unsigned char pad00[0x48];
    void*         mpOwner;       // +0x48
    void*         mpValue;       // +0x4c
    cSPUILayout*  mpLayout;      // +0x50
    unsigned char pad54[0x8];
    void*         mpTargetA;     // +0x5c
    void*         mpTargetB;     // +0x60
    unsigned char pad64[0x4];
    unsigned char mbFlag;        // +0x68
    unsigned char pad69[0x10];
    unsigned char mbHidden;      // +0x79

    void M_00ecefc0(int, int);
    void M_00ecf910(int, int);
    void FUN_00ecf000_fn();
    void Notify(int);        // @ 0x00ece140  (thiscall, ret 4)
    void Refresh();          // @ 0x00ecf000  (thiscall, no args)
};

// 0x00ecf0f0 receives an interior pointer: its object base (the one whose first field is
// the vtable) sits 0x44 bytes lower.
struct SwatchMsgTarget {
    bool FUN_00ecf0f0(int param_2, int param_3);
};
// @ 0x00ecefc0
void SwatchRecvUI::M_00ecefc0(int param_2, int param_3)
{
    if (mpValue != 0) {
        C1(mpValue, 0x24, param_2);
        void* v = mpValue;              // reload: the slot-0x24 call may write it
        void* manager = FUN_00401020();
        ((ValueSink*)manager)->SetValue((int)v, 5.0f);
    }
    (void)param_3;
}

// ============================================================ 0x00ecf000
// @ 0x00ecf000
void SwatchRecvUI::FUN_00ecf000_fn()
{
    SwatchValue* val = (SwatchValue*)mpValue;
    SwatchInner* inner = val->mpInner;
    char c;
    if (inner == 0 || ((inner->mFlags >> 0xe & 1) == 0) || ((inner->mFlags >> 0x12 & 1) != 0))
        c = 1;
    else
        c = 0;
    void* p = mpTargetA;
    mbFlag = c;
    if (c == 0) {
        if (p) {
            int u = K0(p, 0x30);
            C1(mpTargetA, 0x5c, (u & 0xffffff) - 0x1000000);
        }
        if (mpTargetB)
            C2(mpTargetB, 0x7c, 1, 0);
    } else {
        if (p) {
            int u = K0(p, 0x30);
            C1(mpTargetA, 0x5c, (u & 0xffffff) + 0x50000000);
        }
        if (mpTargetB) {
            C2(mpTargetB, 0x7c, 1, 1);
            float f = -(SPUIHelpers_GetElapsedSeconds() * 2.0f);
            float local[4];
            local[0] = 0.0f; local[1] = 0.0f; local[2] = 1.0f; local[3] = f;
            FUN_00808230((int)mpTargetB, local);
        }
    }
    Notify(mbFlag == 0);
}

// ============================================================ 0x00ecf0f0
// @ 0x00ecf0f0
bool SwatchMsgTarget::FUN_00ecf0f0(int param_2, int param_3)
{
    SwatchRecvUI*  self = (SwatchRecvUI*)((char*)this - 0x44);
    SwatchMessage* msg = (SwatchMessage*)param_3;
    if (param_2 != 0x72304d0)
        return false;
    if (msg->mpOwner != 0 && *(int*)msg->mpValue != 0 && msg->mpOwner == self->mpOwner) {
        C1(self, 0x30, (int)msg->mpValue);
        self->Refresh();
        C2(self, 0x3c, msg->mnArg18, 0);
        return true;
    }
    return false;
}

// ============================================================ 0x00ecf150 (ctor)
int* __fastcall FUN_00ecf150(int* param_1)
{
    param_1[0x1c] = (int)vtbl_Async;
    param_1[0x1b] = (int)vtbl_AddRef;
    param_1[0x1c] = (int)vtbl_Async;
    param_1[0x1d] = 0;
    param_1[0] = (int)vtbl_cSPScenarioSwatchEditItemUI;
    param_1[2] = (int)vtbl_Async;
    param_1[9] = (int)vtbl_Async;
    param_1[0xc] = (int)vtbl_Async;
    param_1[0xd] = (int)vtbl_Async;
    param_1[0x11] = (int)vtbl_Async;
    param_1[0x1b] = (int)vtbl_Async;
    param_1[0x1c] = (int)vtbl_Async;
    *((char*)param_1 + 0x78) = 0;
    *((char*)param_1 + 0x79) = 0;
    param_1[0x1f] = 0;
    return param_1;
}

// ============================================================ 0x00ecf320 (ReloadCallback)
// @ 0x00ecf320
void FUN_00ecf320(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    FUN_00eceab0(param_2, param_3);
    if (*(int*)(param_1 + 0x1c) != 0) {
        int iVar2 = (param_1 == 0x24) ? 0 : param_1 + 0x48;
        SPUIHelpers_VisitWindowTreeDepthFirst(*(int*)(param_1 + 0x1c), (void*)&FUN_00ecd9a0, iVar2);
    }
    int* nw = (int*)operator new(0x78);
    if (nw == 0)
        nw = 0;
    else
        nw = (int*)UI_TextZoomName_ctor();
    int* cur = *(int**)(param_1 + 0x58);
    if (nw != cur) {
        if (nw)
            ((void(__thiscall*)(void*))(((void**)nw)[1]))(nw);
        *(int**)(param_1 + 0x58) = nw;
        if (cur)
            ((void(__thiscall*)(void*))(((void**)cur)[2]))(cur);
    }
    int* w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x2c), 0x79591e0);
    int u = 0;
    if (w)
        u = K1(w, 0xc, 0xf15f4bd);
    FUN_00834fa0(u, 0, 0, 0, 0, 0, 0);
    (void)param_4; (void)param_5;
}

// ============================================================ 0x00ecf400
int FUN_00ecf400(int param_1, int param_2, int* param_3)
{
    int iVar5 = param_3[6];
    switch (param_3[2]) {
    case 0x7be2442: {
        int iVar6 = FUN_00ece3b0(*(int*)(iVar5 + 0x1c));
        if (iVar6 == 0)
            return 1;
        int u = *(int*)(iVar6 + 0x4c);
        FUN_00401020();
        FUN_005f0c60(u, 0x42f00000);
        if (iVar6 == param_1 - 0x30)
            return 1;
        if (!FUN_00ece410((void*)(param_1 - 0x30)))
            return 1;
        int w = (int)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x20), 0x4a1cb70);
        (void)w;
        *(char*)(*(int*)(iVar5 + 0x14) + 0x10) = 0;
        return 1;
    }
    case 0x7be2444:
        iVar5 = FUN_00ece3b0(*(int*)(iVar5 + 0x1c));
        if (iVar5 != 0) {
            int u = *(int*)(iVar5 + 0x4c);
            FUN_00401020();
            FUN_005f0c60(u, 0x42f00000);
        }
        FUN_00ef0b30();
        if (iVar5 == 0 || iVar5 != param_1 - 0x30) {
            cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x20), 0x4a1cb70);
            FUN_00ece410((void*)(param_1 - 0x30));
        }
        return 1;
    default:
        return 0;
    }
    (void)param_2;
}

// ============================================================ 0x00ecf6d0
unsigned FUN_00ecf6d0(int param_1, int* param_2)
{
    int iVar2 = K0(param_2, 0x1c);
    if (iVar2 == 0x4a1cb6e) {
        int u = *(int*)(param_1 - 0x20);
        FUN_00401020();
        FUN_005f0c60(u, 0x5368d4a5);
    }
    unsigned b = 1;
    iVar2 = K0(*(int**)(param_1 - 0x6c), 0x28);
    int flag = (iVar2 == (int)0x867a9ee9) ? 1 : 0;
    int iVar1 = *(int*)(param_1 - 0x5c);
    if (*(char*)(param_1 + 0xd) == 0) {
        int* w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 - 0x1c), 0x7b6b2cd);
        if (w) C2(w, 0x7c, 1, iVar1 != -1);
    }
    int iVar2b = *(int*)(param_1 - 0x5c);
    if (*(char*)(param_1 + 0xd) == 0) {
        int* w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 - 0x1c), 0x4a1cb6d);
        if (w) C2(w, 0x7c, 1, iVar2b != -1);
        if (*(char*)(param_1 + 0xd) == 0) {
            w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 - 0x1c), 0x73272b0);
            if (w) C2(w, 0x7c, 1, flag);
        }
    }
    b = (*(int*)(param_1 - 0x5c) != -1);
    return b;
}

// ============================================================ 0x00ecf800
// @ 0x00ecf800
unsigned FUN_00ecf800(int param_1, int* param_2)
{
    int iVar1 = K0(param_2, 0x1c);
    if (iVar1 == 0x4a1cb6e) {
        int u = *(int*)(param_1 - 0x20);
        FUN_00401020();
        FUN_005f0c60(u, 0x40a00000);
    }
    int* mgr = (int*)FUN_0113ae10();
    iVar1 = K1(mgr, 0x48, 1);
    if (iVar1 != 0) {
        int r = K1(*(int**)(param_1 - 0x2c), 0xf8, iVar1);
        if ((char)r != 0)
            return r & 0xffffff00;
    }
    if (*(char*)(param_1 + 0xd) == 0) {
        int* w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 - 0x1c), 0x7b6b2cd);
        if (w) C2(w, 0x7c, 1, 0);
        if (*(char*)(param_1 + 0xd) == 0) {
            w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 - 0x1c), 0x4a1cb6d);
            if (w) C2(w, 0x7c, 1, 0);
            if (*(char*)(param_1 + 0xd) == 0) {
                w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 - 0x1c), 0x73272b0);
                if (w) C2(w, 0x7c, 1, 0);
                if (*(char*)(param_1 + 0xd) == 0) {
                    w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 - 0x1c), 0x7464588);
                    if (w) C2(w, 0x7c, 1, 0);
                }
            }
        }
    }
    unsigned r = FUN_00834c60(0);
    *(char*)(param_1 + 0xc) = 0;
    return r & 0xffffff00;
}

// ============================================================ 0x00ecf910
// @ 0x00ecf910
void SwatchRecvUI::M_00ecf910(int param_2, int param_3)
{
    if (mbHidden == 0) {
        cSPUILayout* layout = mpLayout;
        int* w = (int*)layout->FindWindowByID((unsigned)param_2, true);
        if (w)
            C2(w, 0x7c, 1, param_3);
    }
}

// ============================================================ 0x00ecf940
// @ 0x00ecf940
void __fastcall FUN_00ecf940_fn(int param_1)
{
    bool b = *(int*)(param_1 + 0x10) == -1;
    if (*(char*)(param_1 + 0x79) == 0) {
        int* w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x4a1cb6e);
        if (w) C2(w, 0x7c, 1, !b);
        if (*(char*)(param_1 + 0x79) == 0) {
            w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x73d54a0);
            if (w) C2(w, 0x7c, 1, b);
        }
    }
    if (b) {
        if (*(char*)(param_1 + 0x79) == 0) {
            int* w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x7b6b2cd);
            if (w) C2(w, 0x7c, 1, 0);
            if (*(char*)(param_1 + 0x79) == 0) {
                w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x4a1cb6d);
                if (w) C2(w, 0x7c, 1, 0);
                if (*(char*)(param_1 + 0x79) == 0) {
                    w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x7464588);
                    if (w) C2(w, 0x7c, 1, 0);
                }
            }
        }
    } else if (*(char*)(param_1 + 0x78) == 0) {
        if (*(int*)(param_1 + 0x10) != -1) {
            if (*(char*)(param_1 + 0x79) == 0) {
                int* w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x7b6b2cd);
                if (w) C2(w, 0x7c, 1, 1);
                if (*(char*)(param_1 + 0x79) == 0) {
                    w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x4a1cb6d);
                    if (w) C2(w, 0x7c, 1, 1);
                    if (*(char*)(param_1 + 0x79) == 0) {
                        w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x7464588);
                        if (w) C2(w, 0x7c, 1, 1);
                        if (*(char*)(param_1 + 0x79) == 0) {
                            w = (int*)cSPUILayout_FindWindowByID3(*(void**)(param_1 + 0x50), 0x7b6b2cd);
                            if (w) C2(w, 0x7c, 1, 1);
                        }
                    }
                }
            }
        }
    }
}
