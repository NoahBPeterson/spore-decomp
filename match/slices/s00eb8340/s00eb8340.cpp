// SP::cSPUIAssetView / UI::cSPAdventureCreatureLargeView family (slice s00eb8340):
// vtable + refcount plumbing and the message/layout wiring of the adventure UI asset views.
// Built with VS2008 SP1 (cl 15.00.30729.01) /O2 /MD /Gy /TP (no float code in this slice).
// Flags: /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------------------
// Callees modelled as member functions (ecx = this) or plain cdecl helpers.
// ---------------------------------------------------------------------------
extern uint32_t g_015a9518;   // 0x015a9518
extern uint32_t g_015a951c;   // 0x015a951c
extern uint32_t g_015a9520;   // 0x015a9520
extern uint32_t g_015a9524;   // 0x015a9524
extern uint32_t g_015a95e4;   // 0x015a95e4

struct Base8   { void __thiscall Init(void*, void*, void*, void*); };       // 0x006582f0
struct BaseTail { void __thiscall Close(); };                               // 0x006580b0
struct BaseC   { void __thiscall Init4(void*); };                            // 0x00657460
struct Base10  { void __thiscall Init0(int); };                             // 0x006580b0
struct Base14  { void __thiscall Done(); };                                 // 0x006593c0
struct Base18  { void __thiscall OnMsg(void*); };                           // 0x006589d0
struct Base1C  { void __thiscall Reset(); };                                // 0x00658440
struct V3      { uint32_t a, b, c; };
struct B16     { uint32_t a, b, c, d; };
struct B64     { B16 a, b, c, d; };
struct Buf256  { B64 a, b, c, d; };
struct Base20  { void __thiscall Do(V3, V3, void*, void*, void*); };        // 0x00657640
struct Base24  { void __thiscall Tail(); };                                 // 0x0066c370
struct Base28  { void __thiscall Init0(int); };                             // 0x0066cbd0
struct Base2C  { void __thiscall Init(); };                                 // 0x0066f200
struct Base30  { void __thiscall Do(); };                                  // 0x0065a070
struct Base34  { void __thiscall Do(void*); };                              // 0x0066ee50
struct Base38  { void __thiscall Do(void*, int); };                          // 0x0066ee30
struct Base3C  { void __thiscall Do(void*, void*, void*, void*, void*); };  // 0x00571db0
struct Layout  { void* __thiscall FindWindow(int id, int one); };           // 0x008105b0
struct Win18   { void* __thiscall Ctor(); };                                // 0x00810000
struct Win1C   { void  __thiscall SetReload(void*, void*, int); };          // Inserted below if needed
struct EvtA    { void __thiscall Do(); };                                    // 0x00834e30

extern void* __cdecl FUN_008061c0(void* layout, int id);                    // 0x008061c0
extern void* __cdecl FUN_00b5f950(void* out, void* src);                    // 0x00b5f950
extern void  __cdecl FUN_008068d0(void* win, void* img, int zero);          // 0x008068d0
struct Fn120d { void __thiscall F(void* id, int one, int two); };             // 0x008120d0
struct Fn121b { void __thiscall F(void* p, int one, int two); };              // 0x008121b0
struct Fn10090{ void __thiscall F(void* fn, void* self); };                   // 0x00810090
extern void __cdecl FUN_0066ee30(void* self, void* win, int one);            // 0x0066ee30
struct Fn59a3b0 { void __thiscall F(); };                                    // 0x0059a3b0
struct Fn59a980 { void __thiscall F(void* a, void* b, void* c); };           // 0x0059a980
extern void  __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0
struct FnF47040 { void __thiscall F(); };                                    // 0x00f47040
struct FnF16260 { void __thiscall F(); };                                    // 0x00f16260
struct FnF16fd0 { void __thiscall F(); };                                    // 0x00f16fd0
extern void  __cdecl FUN_00834a00(void);                                    // 0x00834a00
extern void  __cdecl FUN_00834c60(void);                                    // 0x00834c60
extern void* __cdecl FUN_00435e90(void);                                    // 0x00435e90
extern void  __cdecl FUN_00435ed0(void* a, void* b);                        // 0x00435ed0
struct Fn4d3dd0 { void __thiscall F(void* a, int b); };                      // 0x004d3dd0
struct Fn4d4f10 { char __thiscall F(void* p); };                             // 0x004d4f10
extern void* __cdecl FUN_004d1370(void* p);                                 // 0x004d1370
struct Fn4d44e0 { void __thiscall F(); };                                    // 0x004d44e0
struct FnF12680 { void __thiscall F(void* a); };                             // 0x00f12680
struct Ctor8c { void* __thiscall Ctor(); };                                  // 0x00f13890
struct Ctor5c { void* __thiscall Ctor(); };                                  // 0x00f13810
struct Fn120  { char  __thiscall F(void* w); };                              // 0x00f120c0
struct Fn150d0 { void __thiscall Load(uint32_t a); };                       // 0x00f150d0
struct Fn17b  { void  __thiscall F(void* w, void* a); };                     // 0x00f17b00
struct Fn5c1ce0 { void* __thiscall F(int idx); };                            // 0x005c1ce0
struct Fn885d10 { void  __thiscall F(); };                                   // 0x00885d10
extern void* __cdecl FUN_011e0810(void);                                    // 0x011e0810
extern void* __cdecl FUN_00881ae0(int lo, int hi, void* buf, int len);      // 0x00881ae0
struct FnA42730 { void* __thiscall F(); };                                   // 0x00a42730
struct Fn605930 { int   __thiscall F(); };                                   // 0x00605930

extern void* __cdecl operator_new(int size, const char* name, int a, int b, int c, int d);
extern void  __cdecl operator_delete__(void* p);                            // 0x00f47380

// ---------------------------------------------------------------------------
// Object layout: 0x138-byte UI asset view.
// ---------------------------------------------------------------------------
struct Obj
{
    void*  vt0;          // 0x00
    void*  vt4;          // 0x04
    void*  vt8;          // 0x08
    void*  vtC;          // 0x0c
    void*  vt10;         // 0x10
    uint8_t pad14[0x18 - 0x14];
    void*  f18;          // 0x18
    void*  f1c;          // 0x1c
    void*  f20;          // 0x20
    uint8_t pad24[0x44 - 0x24];
    void*  f44;          // 0x44
    uint8_t pad48[0x5c - 0x48];
    void*  f5c;          // 0x5c
    uint8_t pad60[0x64 - 0x60];
    void*  f64;          // 0x64
    void*  f68;          // 0x68
    uint8_t pad6c[0x88 - 0x6c];
    void*  f88;          // 0x88
    uint8_t pad8c[0x90 - 0x8c];
    void*  f90;          // 0x90
    uint8_t pad94[0x9f - 0x94];
    uint8_t f9f;         // 0x9f
    uint8_t padA0[0xd0 - 0xa0];
    void*  fD0;          // 0xd0
    uint8_t padD4[0xdc - 0xd4];
    void*  fDC;          // 0xdc
    void*  fE0;          // 0xe0
    void*  fE4;          // 0xe4
    void*  fE8;          // 0xe8
    void*  fEC;          // 0xec
    void*  fF0;          // 0xf0
    void*  fF4;          // 0xf4
    void*  fF8;          // 0xf8
    void*  fFC;          // 0xfc
    void*  f100;         // 0x100
    void*  f104;         // 0x104
    void*  f108;         // 0x108
    void*  f10C;         // 0x10c
    void*  f110;         // 0x110
    void*  f114;         // 0x114
    void*  f118;         // 0x118
    void*  f11C;         // 0x11c
    void*  f120;         // 0x120
    void*  f124;         // 0x124
    void*  f128;         // 0x128
    void*  f12C;         // 0x12c
    void*  f130;         // 0x130
    uint8_t f134;        // 0x134
    uint8_t f135;        // 0x135

    void __fastcall Dtor();
    void __thiscall Ctor4(void*, void*, void*, void*);
    void __thiscall GetBlob(void* out);
    void __thiscall OnMsg(void*);
    void __fastcall ClearAll();
    void __thiscall OnShow(void*);
    void __fastcall Update();
    void* __thiscall ScalarDtor(uint8_t);
    void __fastcall Reload();
    void __fastcall FillList();
    void __fastcall Activate();
    void __fastcall MakeLayout();
    uint8_t __thiscall Dispatch2(void*, void*);
    void __fastcall ReleaseAll();
    void __thiscall OnSetTitle(void*);
    void __thiscall MakeLargeView(void*);
    void __thiscall MakeSmallView(void*);
    void* __fastcall Ctor2();
};

// Wnd: the generic window interface the vtable slots live on.
struct Wnd
{
    void* __thiscall AddRef();
    void* __thiscall Release();
    void  __thiscall ShowE(int a, int b)
    {
        int* vt = *(int**)this;
        ((void (__thiscall*)(void*, int, int))vt[0x7c / 4])(this, a, b);
    }
    void  __thiscall Show(int a, void* b);
    void* __thiscall GetChild(void* after);
    void* __thiscall GetLayout();
    void* __thiscall GetSlot0x38();
    void* __thiscall QueryId(void* id);
    void* __thiscall CastTo(int id);
    uint32_t __thiscall TypeFlags();
    void* __thiscall SubObj();
    void* __thiscall ScriptSelf();
    void* __thiscall GetFrame();
    void  __thiscall SetPtr(void* p);
    void* __thiscall GetId();
};

extern uint8_t g_01488728[];
extern uint8_t g_01488718[];
extern uint8_t g_01488828[];
extern uint8_t g_01488818[];
extern uint8_t g_0148880c[];
extern uint8_t g_014887f4[];
extern uint8_t g_014887e4[];
extern uint8_t g_0140085c[];

typedef void* (__thiscall *VF0)(void*);

// ---------------------------------------------------------------------------
// @ 0x00eb8340
// ---------------------------------------------------------------------------
void __fastcall Obj::Dtor()
{
    char* p = (char*)this;
    char* e = p + 0x130;
    *(void**)(p) = (void*)0x01488728;
    *(void**)(p + 4) = (void*)0x01488718;
    {
        void* o = *(void**)e;
        if (o) { void** vt = *(void***)o; ((VF0)vt[1])(o); }
    }
    {
        int n = 4;
        do {
            e -= 4;
            void* o = *(void**)e;
            if (o) { void** vt = *(void***)o; ((VF0)vt[1])(o); }
            n = n - 1;
        } while (n >= 0);
    }
    {
        void* o = f118;
        if (o) { void** vt = *(void***)o; ((VF0)vt[1])(o); }
    }
    {
        void* o = f114;
        if (o) { void** vt = *(void***)o; ((VF0)vt[1])(o); }
    }
    {
        void* o = f110;
        if (o) { void** vt = *(void***)o; ((VF0)vt[1])(o); }
    }
    {
        void* o = f10C;
        if (o) { void** vt = *(void***)o; ((VF0)vt[1])(o); }
    }
    {
        char* o = (char*)f108;
        if (o) { char* s = o + 0x10; void** vt = *(void***)s; ((VF0)vt[1])(s); }
    }
    ((BaseTail*)this)->Close();
}

// ---------------------------------------------------------------------------
// @ 0x00eb83f0
// ---------------------------------------------------------------------------
void __thiscall Obj::Ctor4(void* a, void* b, void* c, void* d)
{
    ((Base8*)this)->Init(a, b, c, d);
    void* iv2;
    if (b != 0)
    {
        void* s = (char*)b + 0x10;
        iv2 = (*(void* (__thiscall**)(void*, int))((char*)*(void**)s + 0xc))(s, 0x5cd3f947);
    }
    else
    {
        iv2 = 0;
    }
    void* iv1 = f108;
    if (iv2 != iv1)
    {
        if (iv2) { void* s = (char*)iv2 + 0x10; (*(void (__thiscall**)(void*))((char*)*(void**)s + 0x0))(s); }
        f108 = iv2;
        if (iv1) { void* s = (char*)iv1 + 0x10; (*(void (__thiscall**)(void*))((char*)*(void**)s + 0x4))(s); }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00eb8490
// ---------------------------------------------------------------------------
void __thiscall Obj::GetBlob(void* out)
{
    uint32_t v = *(volatile uint32_t*)&g_015a9518;
    uint32_t* o = (uint32_t*)out;
    ((volatile uint32_t*)o)[0] = 0xe0c972f4;
    ((volatile uint32_t*)o)[1] = 0x0510a95b;
    ((volatile uint32_t*)o)[2] = v;
}

// ---------------------------------------------------------------------------
// @ 0x00eb84b0
// ---------------------------------------------------------------------------
void __thiscall Obj::OnMsg(void* msg)
{
    ((BaseC*)this)->Init4(msg);
    if (*(uint8_t*)&fF4 == 0 && f130 != 0)
    {
        void* o = f130;
        void** vt = *(void***)o;
        ((void* (__thiscall*)(void*))vt[6])(o);

        void* o2 = f130;
        if (o2)
        {
            f130 = 0;
            void** vt2 = *(void***)o2;
            ((VF0)vt2[1])(o2);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00eb8500
// ---------------------------------------------------------------------------
void __fastcall Obj::ClearAll()
{
    if (f10C) { void* o = f10C; f10C = 0; void** vt = *(void***)o; ((VF0)vt[1])(o); }
    if (f110) { void* o = f110; f110 = 0; void** vt = *(void***)o; ((VF0)vt[1])(o); }
    if (f114) { void* o = f114; f114 = 0; void** vt = *(void***)o; ((VF0)vt[1])(o); }
    if (f118) { void* o = f118; f118 = 0; void** vt = *(void***)o; ((VF0)vt[1])(o); }
    {
        void** q = &f11C;
        int n = 5;
        do {
            void* o = *q;
            if (o) { *q = 0; void** vt = *(void***)o; ((VF0)vt[1])(o); }
            q += 1;
            n = n - 1;
        } while (n != 0);
    }
    ((Base14*)this)->Done();
}

// ---------------------------------------------------------------------------
// @ 0x00eb85a0
// ---------------------------------------------------------------------------
void __thiscall Obj::OnShow(void* msg)
{
    if (f118 != 0 && f64 != 0)
    {
        Wnd* verb = (Wnd*)f64;
        if (f135 != 0)
            ((Wnd*)f64)->ShowE(1, 1);
        ((Wnd*)f118)->ShowE(1, 0);
    }
    ((Base18*)this)->OnMsg(msg);
}

// ---------------------------------------------------------------------------
// @ 0x00eb85f0
// ---------------------------------------------------------------------------
void __fastcall Obj::Update()
{
    int iVar1 = 0;
    char cVar3 = 0;
    if (f108 != 0)
    {
        cVar3 = *(char*)((char*)f108 + 0x78);
        iVar1 = *(int*)((char*)f108 + 0x7c);
    }
    if (f110 != 0 && f114 != 0)
    {
        if (cVar3 == 0)
        {
            ((Wnd*)f110)->ShowE(1, 0);
            return;
        }
        if (iVar1 < 0)
            iVar1 = 0;
        else if (iVar1 > 10)
            iVar1 = 10;
        void* img = ((Layout*)f20)->FindWindow(iVar1 + 0x7d21870, 0);
        void* tmp = 0;
        FUN_00b5f950(&tmp, img);
        if (tmp != 0)
        {
            FUN_008068d0(f114, tmp, 0);
            ((Wnd*)f110)->ShowE(1, 1);
            ((Wnd*)tmp)->Release();
        }
        else
        {
            FUN_008068d0(f114, 0, 0);
            ((Wnd*)f110)->ShowE(1, 0);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00eb86e0  (scalar deleting destructor)
// ---------------------------------------------------------------------------
void* __thiscall Obj::ScalarDtor(uint8_t flags)
{
    Dtor();
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00eb8700
// ---------------------------------------------------------------------------
void __fastcall Obj::Reload()
{
    ((Base30*)this)->Do();
    uint8_t bl;
    if (f108 != 0 && *(char*)((char*)f108 + 0x78) != 0)
        bl = 1;
    else
        bl = 0;

    {
        void* w = ((Layout*)f20)->FindWindow(0x53d6fe30, 1);
        void* old = f10C;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f10C = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    {
        Wnd* w = (Wnd*)f10C;
        if (w)
        {
            w->ShowE(1, 0);
            if (f44 && bl)
            {
                ((Wnd*)f44)->ShowE(1, 0);
                ((Wnd*)f10C)->ShowE(1, 1);
                void* arg = ((Wnd*)f44)->GetFrame();
                ((Wnd*)f10C)->SetPtr(arg);
            }
        }
    }
    {
        void* w = ((Layout*)f20)->FindWindow(0x7ce01f8, 1);
        void* old = f110;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f110 = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    {
        void* w = ((Layout*)f20)->FindWindow(0x7ce0158, 1);
        void* old = f114;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f114 = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    Update();
    {
        void* w = ((Layout*)f20)->FindWindow(0x7ce6b98, 1);
        void* old = f118;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f118 = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    if (f118)
        ((Wnd*)f118)->ShowE(1, 0);
    {
        void* w = ((Layout*)f20)->FindWindow(0x7ce1c3e, 1);
        void* old = f11C;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f11C = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    {
        void* w = ((Layout*)f20)->FindWindow(0x76b8598, 1);
        void* old = f120;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f120 = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    {
        void* w = ((Layout*)f20)->FindWindow(0x7ee1060, 1);
        void* old = f124;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f124 = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    {
        void* w = ((Layout*)f20)->FindWindow(0x797c930, 1);
        void* old = f128;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f128 = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    {
        void* w = ((Layout*)f20)->FindWindow(0x7ee1050, 1);
        void* old = f12C;
        if (w != old)
        {
            if (w) { void** vt = *(void***)w; ((VF0)vt[0])(w); }
            f12C = w;
            if (old) { void** vt = *(void***)old; ((VF0)vt[1])(old); }
        }
    }
    f135 = 0;
    {
        Wnd* o = (Wnd*)f64;
        if (o)
        {
            if (o->TypeFlags() & 1)
                f135 = 1;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00eb89d0
// ---------------------------------------------------------------------------
void __fastcall Obj::FillList()
{
    if (f118 == 0)
        return;
    void* piVar8 = f90;
    if (piVar8 == 0)
        return;
    void** slot = &f130;
    if (*slot != 0)
        return;

    {
        void* o = *(void* volatile*)slot;
        if (o) { *slot = 0; void** vt = *(void***)o; ((VF0)vt[1])(o); }
    }
    void* uVar3 = f118;
    void* uVar4 = (*(void* (__thiscall**)(void*))((char*)*(void**)piVar8 + 0x24))(piVar8);
    V3 v1;
    v1.a = 0; v1.b = 0; v1.c = 0;
    V3 v2;
    v2.a = g_015a951c; v2.b = g_015a9520; v2.c = g_015a9524;
    ((Base20*)this)->Do(v2, v1, uVar3, slot, uVar4);

    if (*slot != 0)
    {
        Buf256 auStack_100;
        int iVar9 = 0;
        void** cur = &f11C;
        do {
            void* iVar5 = ((Fn5c1ce0*)*slot)->F(iVar9);
            int iVar6 = 0;
            if (iVar5 != 0)
            {
                ((Fn885d10*)iVar5)->F();
                iVar6 = (int)FUN_011e0810();
            }
            if (*cur != 0)
            {
                FUN_00881ae0(iVar6, iVar6 >> 31, &auStack_100, 0x80);
                (*(void (__thiscall**)(void*, void*))((char*)*(void**)*cur + 0x80))(*cur, &auStack_100);
            }
            iVar9 = iVar9 + 1;
            cur += 1;
        } while (iVar9 < 5);
    }
    if (f88 != 0)
    {
        int iVar9 = ((Fn605930*)f88)->F();
        int iVar5 = 0;
        if (0 < iVar9)
        {
            do {
                void* pDVar7 = ((Fn5c1ce0*)f88)->F(iVar5);
                void* iVar6 = ((FnA42730*)pDVar7)->F();
                if (iVar6 != 0 && *(int*)((char*)iVar6 + 0x24) == 0x5ce214c5)
                {
                    void* piVar8c = (*(void* (__thiscall**)(void*))((char*)*(void**)pDVar7 + 0x30))(pDVar7);
                    if (piVar8c != 0)
                        ((Wnd*)piVar8c)->ShowE(1, 0);
                }
                iVar5 = iVar5 + 1;
            } while (iVar5 < iVar9);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00eb8b30
// ---------------------------------------------------------------------------
void __fastcall Obj::Activate()
{
    ((Base1C*)this)->Reset();
    void* p = f90;
    char cVar1 = (*(char (__thiscall**)(void*))((char*)*(void**)p + 0x64))(p);
    if (cVar1 == 0)
        return;
    if (f118 != 0 && f64 != 0)
    {
        void* w = f64;
        (*(void (__thiscall**)(void*, int, int))((char*)*(void**)w + 0x7c))(w, 1, 0);
        void* w2 = f118;
        (*(void (__thiscall**)(void*, int, int))((char*)*(void**)w2 + 0x7c))(w2, 1, 1);
    }
    FillList();
}

// ---------------------------------------------------------------------------
// @ 0x00eb8b90
// ---------------------------------------------------------------------------
void __fastcall Obj::MakeLayout()
{
    void* obj = operator_new(0x18, (const char*)0x013fa29c, 0, 0, 0, 0);
    void* piVar3;
    if (obj != 0)
        piVar3 = ((Win18*)obj)->Ctor();
    else
        piVar3 = 0;
    void* old = f18;
    if (piVar3 != old)
    {
        if (piVar3) { void** vt = *(void***)piVar3; ((VF0)vt[1])(piVar3); }
        f18 = piVar3;
        if (old) { void** vt = *(void***)old; ((VF0)vt[2])(old); }
    }
    uint32_t g = g_015a95e4;
    uint32_t id[3];
    id[0] = 0x925c9c2d;
    id[1] = 0x0510a95b;
    id[2] = g;
    ((Fn120d*)f18)->F(id, 1, 0x5b598fa);
    ((Fn121b*)f18)->F(f1c, 1, 0x5b598fa);
    ((Fn10090*)f18)->F((void*)0x0066ee30, this);
    FUN_0066ee30(this, f18, 1);
}

// ---------------------------------------------------------------------------
// @ 0x00eb8c50
// ---------------------------------------------------------------------------
// A UI event dispatcher: switches on the message id at +8 and the sub-id at
// +0xc, toggling the "Sporepedia open" flag and re-showing windows.
struct Dispatcher { void __thiscall Dispatch(void* a, void* b); };   // 0x0066d430

uint8_t __thiscall Obj::Dispatch2(void* a, void* b)
{
    char* ebx = (char*)this;
    char* esi = (char*)a;
    void* arg1 = b;
    uint32_t eax = *(uint32_t*)(esi + 8);

    if (eax >= 0x1b && eax <= 0x1c)
        goto Lrange;
    if (eax != 0x287259f6)
        goto Ltail;

    {
        uint32_t sub = *(uint32_t*)(esi + 0xc);
        if (sub == 0x7b69998)
        {
            ((Wnd*)(ebx + 0xd0))->ShowE(1, (int)(void*)0x7ccce30);
            return 1;
        }
        if (sub != 0x7cce570)
            goto Ltail;

        {
            uint8_t al = (*(uint8_t*)(ebx + 0x11c) == 0) ? 1 : 0;
            *(uint8_t*)(ebx + 0x11c) = al;
            if (al)
            {
                FUN_00435e90();
                FUN_00435ed0((void*)0x6e649e21, (void*)0);
            }
            else
            {
                FUN_00435e90();
                FUN_00435ed0((void*)0xcc089e57, (void*)0);
            }
            Wnd* win = (Wnd*)((Layout*)f18)->FindWindow(0x7cd29e8, 1);
            if (win != 0)
            {
                void* sub2 = win->GetChild(0);
                while (sub2 != 0)
                {
                    void* ebp = ((Wnd*)sub2)->QueryId((void*)0xef2b293b);
                    if (ebp != 0)
                    {
                        void* ea = win->GetSlot0x38();
                        float f0 = *(float*)((char*)ea + 0xc) - *(float*)((char*)ea + 4);
                        float loc[2];
                        loc[0] = 0.0f;
                        loc[1] = -f0;
                        ((void (__thiscall*)(void*, float*))((void**)*(void**)ebp)[0x18 / 4])(ebp, loc);
                        break;
                    }
                    sub2 = win->GetChild(sub2);
                }
                win->Show(1, (void*)(uint32_t)*(uint8_t*)(ebx + 0x11c));
            }
            {
                Wnd* w2 = (Wnd*)((Layout*)f18)->FindWindow(0x3fbba82, 1);
                if (w2 != 0)
                    w2->Show(1, (void*)(uint32_t)((*(uint8_t*)(ebx + 0x11c) == 0) ? 1 : 0));
            }
            {
                void* o = *(void**)(ebx + 0x5c);
                if (o != 0)
                {
                    void* ea = ((Wnd*)o)->GetLayout();
                    ((Wnd*)ea)->Show(1, (void*)(uint32_t)((*(uint8_t*)(ebx + 0x11c) == 0) ? 1 : 0));
                }
            }
            return 1;
        }
    }

Lrange:
    {
        void* id = ((Wnd*)esi)->GetId();
        uint32_t idv = (uint32_t)id;
        void* ctx;
        if (idv > 0x7fb2ed0)
        {
            if (idv != 0xb456a47a)
                goto Ltail;
            ctx = fFC;
        }
        else
        {
            if (idv == 0x7fb2ed0 || idv == 0x7fb1c78)
                ctx = f100;
            else if (idv == 0x7cce580)
                ctx = f104;
            else
                goto Ltail;
        }
        if (ctx == 0)
            goto Ltail;
        if (*(uint32_t*)(esi + 8) == 0x1b)
            FUN_00834a00();
        else
            FUN_00834c60();
        ((Dispatcher*)this)->Dispatch(arg1, esi);
        return 1;
    }

Ltail:
    ((Dispatcher*)this)->Dispatch(arg1, esi);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00eb8e70
// ---------------------------------------------------------------------------
void __fastcall Obj::ReleaseAll()
{
    {
        void* p = fFC;
        if (p)
        {
            fFC = 0;
            FUN_00571db0(p, f100, f104, f108, f10C);
        }
    }
    if (fDC)
    {
        void* q = *(void* volatile*)&fDC;
        if (q != 0)
        {
            void* s = (char*)q + 0x10;
            fDC = 0;
            void** vt = *(void***)s;
            ((VF0)vt[1])(s);
        }
    }
    {
        void* o1 = fEC;
        if (o1 != 0)
        {
            ((Fn59a3b0*)o1)->F();
            void* o2 = fEC;
            if (o2 != 0) { fEC = 0; void** vt = *(void***)o2; ((VF0)vt[1])(o2); }
        }
    }
    {
        void* o1 = fE8;
        if (o1 != 0)
        {
            ((FnF47040*)o1)->F();
            void* o2 = fE8;
            if (o2 != 0) { fE8 = 0; void** vt = *(void***)o2; ((VF0)vt[1])(o2); }
        }
    }
    {
        void* o1 = fE4;
        if (o1 != 0)
        {
            ((FnF16260*)o1)->F();
            void* o2 = fE4;
            if (o2 != 0) { fE4 = 0; void** vt = *(void***)o2; ((VF0)vt[2])(o2); }
        }
    }
    {
        void* o1 = fE0;
        if (o1 != 0)
        {
            ((FnF16fd0*)o1)->F();
            void* o2 = fE0;
            if (o2 != 0)
            {
                void* s = (char*)o2 + 4;
                fE0 = 0;
                void** vt = *(void***)s;
                ((VF0)vt[2])(s);
            }
        }
    }
    {
        void* o1 = fF0;
        if (o1 != 0)
        {
            ((EvtA*)o1)->Do();
            void* o2 = fF0;
            if (o2 != 0) { fF0 = 0; void** vt = *(void***)o2; ((VF0)vt[2])(o2); }
        }
    }
    {
        void* o1 = fF4;
        if (o1 != 0)
        {
            ((EvtA*)o1)->Do();
            void* o2 = fF4;
            if (o2 != 0) { fF4 = 0; void** vt = *(void***)o2; ((VF0)vt[2])(o2); }
        }
    }
    {
        void* o1 = fF8;
        if (o1 != 0)
        {
            ((EvtA*)o1)->Do();
            void* o2 = fF8;
            if (o2 != 0) { fF8 = 0; void** vt = *(void***)o2; ((VF0)vt[2])(o2); }
        }
    }
    ((uint8_t*)&f110)[0] = 0;
    ((Base24*)this)->Tail();
}

// ---------------------------------------------------------------------------
// @ 0x00eb8ff0
// ---------------------------------------------------------------------------
struct D16  { uint32_t a,b,c,d; };
struct D64  { D16 a,b,c,d; };
struct D256 { D64 a,b,c,d; };
struct D1024{ D256 a,b,c,d; };
struct Local
{
    uint32_t z0, z4, z8;
    D1024 b0, b1;
    D256  b2, b3;
    uint32_t r0, r1, r2, r3, r4, r5;
};

void __thiscall Obj::OnSetTitle(void* a)
{
    if (fE0 != 0)
        ((FnF12680*)fE0)->F(a);
    if (fEC != 0 && f68 != 0 && f9f != 0)
    {
        Local L;
        L.z0 = 0; L.z4 = 0; L.z8 = 0;
        void* obj = (char*)&L + 0xc;
        ((Fn4d3dd0*)obj)->F(&L.z0, 0);
        void* p68 = f68;
        void* uVar2 = (*(void* (__thiscall**)(void*))((char*)*(void**)p68 + 0x40))(p68);
        char cVar1 = ((Fn4d4f10*)obj)->F(uVar2);
        if (cVar1 != 0)
        {
            void* puVar3 = FUN_004d1370(*(void**)((char*)&L + 0x588));
            ((Fn59a980*)fEC)->F(a, obj, puVar3);
        }
        else
        {
            ((Fn59a980*)fEC)->F(a, 0, 0);
        }
        ((Fn4d44e0*)obj)->F();
    }
    ((Base34*)this)->Do(a);
}

// ---------------------------------------------------------------------------
// @ 0x00eb90c0
// ---------------------------------------------------------------------------
void __thiscall Obj::MakeLargeView(void* a)
{
    void* obj = operator_new(0x8c, (const char*)0x014887b8, 0, 0, 0, 0);
    void* piVar4;
    if (obj != 0)
        piVar4 = ((Ctor8c*)obj)->Ctor();
    else
        piVar4 = 0;

    void* old = fF0;
    if (piVar4 != old)
    {
        if (piVar4) { void** vt = *(void***)piVar4; ((VF0)vt[1])(piVar4); }
        fF0 = piVar4;
        if (old) { void** vt = *(void***)old; ((VF0)vt[2])(old); }
    }
    void* view = fF0;
    char cVar2 = ((Fn120*)view)->F(((Layout*)f18)->FindWindow(0x7cd2938, 1));
    void* t = fF0;
    if (cVar2 == 0)
    {
        if (t)
        {
            fF0 = 0;
            void** vt = *(void***)t;
            ((VF0)vt[2])(t);
        }
    }
    else
    {
        ((Fn150d0*)view)->Load((uint32_t)a);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00eb9170
// ---------------------------------------------------------------------------
void __thiscall Obj::MakeSmallView(void* a)
{
    void* obj = operator_new(0x5c, (const char*)0x014887b8, 0, 0, 0, 0);
    void* iVar2;
    if (obj != 0)
        iVar2 = ((Ctor5c*)obj)->Ctor();
    else
        iVar2 = 0;

    void* iVar1 = fEC;
    if (iVar2 != iVar1)
    {
        if (iVar2) { void* s = (char*)iVar2 + 4; void** vt = *(void***)s; ((VF0)vt[1])(s); }
        fEC = iVar2;
        if (iVar1) { void* s = (char*)iVar1 + 4; void** vt = *(void***)s; ((VF0)vt[2])(s); }
    }
    void* lay = f18;
    void* view = fEC;
    ((Fn17b*)view)->F(((Layout*)lay)->FindWindow(0x7cc9018, 1), a);
}

// ---------------------------------------------------------------------------
// @ 0x00eb9200
// ---------------------------------------------------------------------------
void* __fastcall Obj::Ctor2()
{
    ((Base28*)this)->Init0(0);
    ((Base2C*)((char*)this + 0xd0))->Init();
    // volatile pins the store order: the original emits the five vfptr stores
    // right after the base constructors, then the member initialisers.
    *(void* volatile*)((char*)this + 0x00) = (void*)0x01488828;
    *(void* volatile*)((char*)this + 0x04) = (void*)0x01488818;
    *(void* volatile*)((char*)this + 0x08) = (void*)0x0148880c;
    *(void* volatile*)((char*)this + 0x0c) = (void*)0x014887f4;
    *(void* volatile*)((char*)this + 0x10) = (void*)0x014887e4;
    *(void* volatile*)((char*)this + 0xd0) = (void*)0x0140085c;
    *(void* volatile*)((char*)this + 0xe8) = 0;
    *(void* volatile*)((char*)this + 0xec) = 0;
    *(void* volatile*)((char*)this + 0xf0) = 0;
    *(void* volatile*)((char*)this + 0xf4) = 0;
    *(void* volatile*)((char*)this + 0xf8) = 0;
    *(void* volatile*)((char*)this + 0xfc) = 0;
    *(void* volatile*)((char*)this + 0x100) = 0;
    *(void* volatile*)((char*)this + 0x104) = 0;
    *(void* volatile*)((char*)this + 0x108) = 0;
    *(void* volatile*)((char*)this + 0x10c) = 0;
    *(void* volatile*)((char*)this + 0x110) = 0;
    *(void* volatile*)((char*)this + 0x114) = 0;
    *(void* volatile*)((char*)this + 0x118) = 0;
    *(uint8_t volatile*)((char*)this + 0x11c) = 0;
    return this;
}
