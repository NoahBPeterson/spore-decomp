// Slice s00ed0b70 -- Scenario::AvatarPaletteItemUI and swatch/item UI glue.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- globals
extern void*         g_16c7aa4;      // 0x016c7aa4
extern void*         g_1440aec;      // 0x01440aec (arena byte offset the list nodes are addressed with)
extern void*         g_15ac028;      // 0x015ac028 (pointer constant)
extern float         g_15abf5c;      // 0x015abf5c
extern float         g_13ec4d0;      // 0x013ec4d0 (100.0f)
extern int           g_15ac028i;

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00b3d320(void);                       // 0x00b3d320
void  __cdecl FUN_006a1400(int, unsigned, void*);       // 0x006a1400
void* __cdecl FUN_008050f0(void*);                      // 0x008050f0
void* __cdecl FUN_00807dc0(void*, int, int);            // 0x00807dc0
void* __cdecl FUN_005ff6a0(void*);                      // 0x005ff6a0
void* __cdecl FUN_00a206f0(void);                       // 0x00a206f0
void  __cdecl FUN_00435ed0(int, void*);                 // 0x00435ed0
void  __cdecl FUN_00edfa30(void*, void*, void*, void*, void*);  // 0x00edfa30
void* __cdecl FUN_00401090(void*);                      // 0x00401090
int   __cdecl FUN_00c028b0(void*, int);                 // 0x00c028b0
float __cdecl FUN_004d12a0(int);                        // 0x004d12a0
void  __cdecl FUN_00881ae0(int, int, void*, int);       // 0x00881ae0
void  __cdecl FUN_00edf830(void*, float, int, int, void*, void*);   // 0x00edf830
void  __cdecl FUN_00eeea50(void*, void*);               // 0x00eeea50
void* __cdecl FUN_0067dcc0(void);                       // 0x0067dcc0
void  __cdecl EA_RemoveHandler(int, int, int, int, int);    // 0x00571db0
void* __stdcall FUN_00ece3f0(int);                      // 0x00ece3f0
void  __fastcall FUN_00ece300(char*);                   // 0x00ece300
void* __stdcall FUN_00401020(void*);                    // 0x00401020
void  __fastcall FUN_005f0ca0(void*);                   // 0x005f0ca0
void  __fastcall FUN_005f7380(void*);                   // 0x005f7380
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);  // 0x00f473a0
void  __cdecl EA_Free(void*);                           // 0x00f47380
void  __cdecl FUN_00805fe0(float*, int);                // 0x00805fe0
int   __cdecl FUN_005f3060(void);                       // 0x005f3060
int   __cdecl FUN_00efc9c0(void);                       // 0x00efc9c0
void  __fastcall FUN_00ecf150(void*);                   // 0x00ecf150

// Callees that pop their own stack arguments are reached through a one-method struct so the
// receiving object travels in ecx.
struct Fn00b1de80 {
    void* fn();         // 0x00b1de80
};
struct Fn005f22f0 {
    void fn(float);     // 0x005f22f0
};
struct Fn00644b60 {
    void fn();          // 0x00644b60
};
struct Fn00929c60 {
    void fn();          // 0x00929c60
};
struct Fn0092a7a0 {
    void fn(int);       // 0x0092a7a0
};
struct Fn00929e70 {
    void fn(int, int, int, int, int, int, int);     // 0x00929e70
};
struct Fn00929da0 {
    void fn(void*, void*, int);     // 0x00929da0
};
struct Fn00ecf000 {
    void fn();          // 0x00ecf000
};
struct Fn00ecf940 {
    void fn();          // 0x00ecf940
};
struct Fn00ecf320 {
    void fn(int, int, int, int);    // 0x00ecf320
};
struct Fn00ecf400 {
    bool fn(int, void*);            // 0x00ecf400
};
struct Fn00f3bcb0 {
    void* fn();         // 0x00f3bcb0
};
struct Fn00f42580 {
    void fn(void*);     // 0x00f42580
};
struct Fn00f45970 {
    void fn();          // 0x00f45970
};
struct Fn00f45a80 {
    void fn();          // 0x00f45a80
};
struct Fn0082f9a0 {
    void fn(void*);     // 0x0082f9a0
};
struct Fn004df550 {
    void* fn(void*);    // 0x004df550
};
struct Fn0041ea70 {
    float* fn();        // 0x0041ea70
};

typedef void* (__thiscall *FV_1)(void*);
typedef void* (__thiscall *FV_i)(void*, int);
typedef void* (__thiscall *FV_pii)(void*, int, int);
typedef void  (__thiscall *FV_ff)(void*, float, float);
typedef unsigned (__thiscall *FV_u)(void*);
typedef int   (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_v)(void*);
typedef void  (__thiscall *FV_vi)(void*, int);
typedef void  (__thiscall *FV_vii)(void*, int, int);
typedef bool  (__thiscall *FB_i)(void*, int, void*);
struct ILayout {
    void* FindWindowByID(unsigned, int);   // 0x008105b0
};

// ---------------------------------------------------------------- 0x00ed0c30
struct ObjC30 { void f(int, int); };
void ObjC30::f(int a, int b)
{
    (void)a;
    int* p = *(int**)((char*)this + 0x18);
    if (p != 0) {
        char* o = (char*)p + 8;
        char* q = (char*)((FV_i)(*(void***)o)[0xc / 4])(o, 0x722e9c1);
        ((FV_i)(*(void***)(q + 0x24))[0x18 / 4])(q + 0x24, b);
    }
}

// ---------------------------------------------------------------- 0x00ed0c60
struct ObjC60 { unsigned f(unsigned, int*); };
// @ 0x00ed0c60
unsigned ObjC60::f(unsigned a, int* b)
{
    if (a == 0x30c11c7) {
        if (*(char*)((char*)this + 4) != 0) {
            int* old = *(int**)((char*)this + 0x2c);
            if (b != old) {
                if (b) a = ((FV_u)(*(void***)b)[4 / 4])(b);
                *(int**)((char*)this + 0x2c) = b;
                if (old) a = ((FV_u)(*(void***)old)[8 / 4])(old);
            }
        }
    } else if (a == 0x72bdb11) {
        a = ((FV_u)(*(void***)(*(int**)((char*)this + 0x10)))[0x14 / 4])(*(int**)((char*)this + 0x10));
    }
    return a & 0xffffff00u;
}

// ---------------------------------------------------------------- 0x00ed0cc0
void* __stdcall FUN_00ed0cc0(char flag)
{
    if (flag != 0)
        return g_15ac028;
    return (void*)FUN_00ece3f0(0);
}

// ---------------------------------------------------------------- 0x00ed12d0
struct Obj12D0 { void f(int); };
void Obj12D0::f(int a)
{
    if (a == -2)
        ((FV_v)(*(void***)this)[0x14 / 4])(this);
}

// ---------------------------------------------------------------- 0x00ed1350
void FUN_00ed1350(int* p, int arg)
{
    if (p != 0) {
        char* q = (char*)((FV_i)(*(void***)p)[0xc / 4])(p, 0x8ed27e7a);
        if (q != 0)
            ((FV_ii)(*(void***)q)[0x28 / 4])(q, 4, arg);
    }
}

// ---------------------------------------------------------------- 0x00ed1500
unsigned char FUN_00ed1500(void)
{
    return *(unsigned char*)(*(int*)(*(int*)((char*)g_16c7aa4 + 0x74) + 0x10) + 0x14c);
}

// ---------------------------------------------------------------- 0x00ed1250
void* __fastcall FUN_00ed1250(void* self)
{
    char* p = (char*)self;
    FUN_00ecf150(self);
    *(void**)p = (void*)0x1489a50;
    *(void**)(p + 8) = (void*)0x1489a3c;
    *(void**)(p + 0x24) = (void*)0x1489a0c;
    *(void**)(p + 0x30) = (void*)0x14899f0;
    *(void**)(p + 0x34) = (void*)0x14899e0;
    *(void**)(p + 0x44) = (void*)0x14897d0;
    *(void**)(p + 0x6c) = (void*)0x1489960;
    *(void**)(p + 0x70) = (void*)0x1489948;
    *(int*)(p + 0x10) = (int)0xfffffffe;
    *(int*)(p + 0x14) = (int)0xe34e8a60;
    return self;
}

// ---------------------------------------------------------------- 0x00ed14c0
struct Obj14C0 { void f(int*); };
void Obj14C0::f(int* param)
{
    int* p = *(int**)((char*)this + 0x4c);
    if (p != 0) {
        ((FV_i)(*(void***)p)[0x24 / 4])(p, (int)param);
        FUN_00ece300((char*)this);
    }
    *(int*)((char*)this + 0x18) = param[0];
    *(int*)((char*)this + 0x1c) = param[1];
    *(int*)((char*)this + 0x20) = param[2];
}

// ---------------------------------------------------------------- 0x00ed1460
// @ 0x00ed1460
void FUN_00ed1460(void)
{
    char* p = (char*)EA_New(0x1c8, "Editor", 0, 0, 0, 0);
    if (p != 0) {
        FUN_005f7380(p);
        *(void**)p = (void*)0x1489aa0;
        *(void**)(p + 4) = (void*)0x13f9ea4;
        *(void**)(p + 0xc) = (void*)0x1489590;
        void* q = FUN_00401020(p);
        FUN_005f0ca0(q);
    } else {
        void* q = FUN_00401020(0);
        FUN_005f0ca0(q);
    }
}

// ---------------------------------------------------------------- 0x00ed1380
// @ 0x00ed1380
bool __fastcall FUN_00ed1380(void* self)
{
    if (FUN_005f3060() == 0)
        return false;
    float bounds[2];
    FUN_00805fe0(bounds, *(int*)((char*)self + 0x18c));
    if ((*(float*)((char*)self + 0x84) <= bounds[1] && bounds[1] != *(float*)((char*)self + 0x84)) ||
        (*(float*)((char*)self + 0x88) <= bounds[0] && bounds[0] != *(float*)((char*)self + 0x88))) {
        if (FUN_00efc9c0() != 0)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------- 0x00ed13e0
// @ 0x00ed13e0
bool __fastcall FUN_00ed13e0(void* self, int dummy, int id, float scale)
{
    char* w = (char*)((ILayout*)*(void**)((char*)self + 0x50))->FindWindowByID(id, 1);
    if (w == 0)
        return false;
    char* q = (char*)((FV_pii)(*(void***)w)[0xf0 / 4])(w, 0x665fe90, 0);
    if (q == 0)
        return false;
    float* f = (float*)((FV_1)(*(void***)q)[0x38 / 4])(q);
    ((FV_ff)(*(void***)w)[0x74 / 4])(w, (f[2] - f[0]) * scale, f[3] - f[1]);
    return true;
}

// ---------------------------------------------------------------- 0x00ed0b70
struct ObjB70 {
    char  pad00[0x10];      // +0x00
    void* p10;              // +0x10  released through vtable slot 1
    void* p14;              // +0x14  released through vtable slot 1
    void* p18;              // +0x18  indirection released through its vtable slot 2
    void* p1c;              // +0x1c  destroyed with FUN_00644b60, then freed
    void* h20;              // +0x20  first message handler id
    int   h24;              // +0x24  the other four handler ids
    int   h28;              // +0x28
    int   h2c;              // +0x2c
    int   h30;              // +0x30
    char  pad34[4];         // +0x34
    void* cb38;             // +0x38  callback cancelled before it is released
};
// @ 0x00ed0b70
void __fastcall FUN_00ed0b70(void* self)
{
    ObjB70* o = (ObjB70*)self;
    if (o->h20 != 0) {
        void* handler = o->h20;
        o->h20 = 0;
        EA_RemoveHandler((int)handler, o->h24, o->h28, o->h2c, o->h30);
    }
    if (o->cb38 != 0) {
        ((Fn00929c60*)o->cb38)->fn();
        if (o->cb38 != 0)
            ((FV_vi)(*(void***)o->cb38)[0])(o->cb38, 1);
    }
    void* p18 = o->p18;
    if (p18 != 0) {
        void* q = (void*)((FV_i)(*(void***)((char*)p18 + 8))[0xc / 4])((char*)p18 + 8, 0x722e9c1);
        ((FV_v)(*(void***)((char*)q + 0x24))[8 / 4])((char*)q + 0x24);
    }
    ((FV_v)(*(void***)o->p18)[8 / 4])(o->p18);
    o->p18 = 0;
    void* p1c = o->p1c;
    if (p1c != 0) {
        ((Fn00644b60*)p1c)->fn();
        EA_Free(p1c);
        o->p1c = 0;
    }
    void* p10 = o->p10;
    if (p10 != 0) {
        o->p10 = 0;
        ((FV_v)(*(void***)p10)[4 / 4])(p10);
    }
    void* p14 = o->p14;
    if (p14 != 0) {
        o->p14 = 0;
        ((FV_v)(*(void***)p14)[4 / 4])(p14);
    }
}

// ---------------------------------------------------------------- 0x00ed0ce0
struct MsgCE0 {                 // the message the handler is handed
    void*    p00;               // +0x00
    int      f04;               // +0x04
    unsigned id;                // +0x08
    int      kind;              // +0x0c
    int      f10;               // +0x10
    int      f14;               // +0x14
};
struct ProfileSlot {            // the slot the profile manager's ids resolve to
    char          pad000[0x170];    // +0x000
    float         f170;         // +0x170
    unsigned char b174;         // +0x174
    unsigned char b175;         // +0x175
};
struct SpeciesProfile {         // what the 0x004df550 lookup hands back
    char  pad000[0x56c];        // +0x000
    float f56c;                 // +0x56c
    char  pad570[0xd4];         // +0x570
    float f644;                 // +0x644
};
struct ObjCE0 {
    char  pad00[0x20];          // +0x00
    void* layout;               // +0x20  cSPUILayout
    bool  f(int, MsgCE0*);
};
// @ 0x00ed0ce0
bool ObjCE0::f(int arg, MsgCE0* msg)
{
    unsigned id = msg->id;
    if (id == 0x7be2444) {
        if (((Fn00ecf400*)this)->fn(arg, msg)) {
            void* w = ((ILayout*)layout)->FindWindowByID(0x757acb8, 1);
            if (w != 0)
                ((Fn0082f9a0*)FUN_00807dc0(w, 1, 0))->fn((void*)0x13f9c70);
            return true;
        }
    } else if (id == 0x7a44749) {
        if (msg->kind == 0x742cd10 && FUN_008050f0(msg->p00) == (void*)0x7c8b2a0) {
            ((Fn00f45a80*)*(void**)((char*)g_16c7aa4 + 0x74))->fn();
            return true;
        }
    } else if (id == 0x7a4489c) {
        if (msg->kind == 0x742cd10 && FUN_008050f0(msg->p00) == (void*)0x7c8b2a0) {
            ((Fn00f45970*)*(void**)((char*)g_16c7aa4 + 0x74))->fn();
            return true;
        }
    } else if (id == 0x287259f6) {
        if (msg->kind == 0x770b540) {
            ((Fn00f45970*)*(void**)((char*)g_16c7aa4 + 0x74))->fn();
            void* m = *(void**)((char*)g_16c7aa4 + 0x74);
            ((ProfileSlot*)*(void**)((char*)m + 0x10))->b175 = (unsigned char)(msg->f14 != 0);
            ((Fn00f45a80*)*(void**)((char*)g_16c7aa4 + 0x74))->fn();
            void* m2 = *(void**)((char*)g_16c7aa4 + 0x74);
            unsigned char on = ((ProfileSlot*)*(void**)((char*)m2 + 0x10))->b175;
            void* sys = FUN_00a206f0();
            if (sys != 0)
                sys = ((FV_1)(*(void***)sys)[0x20 / 4])(sys);
            FUN_00435ed0(on != 0 ? 0x9316596c : 0x72b10481, sys);
            return true;
        }
    } else if (id == 0xef00a884) {
        if (msg->kind == 0x742cd10 && FUN_008050f0(msg->p00) == (void*)0x7c8b2a0) {
            void* item = 0;
            void* w = FUN_005ff6a0(msg->p00);
            if (w != 0)
                item = ((FV_1)(*(void***)w)[0x20 / 4])(w);
            ProfileSlot* p = (ProfileSlot*)*(void**)((char*)*(void**)((char*)g_16c7aa4 + 0x74) + 0x10);
            char text[0x40];
            text[0] = 0;
            FUN_00edfa30(item, &p->f170, text, &p->b174, (void*)0x7c8d5f4);
            float f = -1.0f;
            void* mgr = ((Fn00f3bcb0*)*(void**)((char*)g_16c7aa4 + 0x74))->fn();
            SpeciesProfile* prof = (SpeciesProfile*)((Fn004df550*)FUN_00401090(mgr))->fn(mgr);
            if (prof != 0) {
                float v = FUN_004d12a0(FUN_00c028b0(prof, 1)) + prof->f56c;
                int i = (int)v;
                if ((float)i < v)
                    i++;
                f = (float)i * p->f170;
            }
            int n = (int)f;
            if ((float)n < f)
                n++;
            FUN_00881ae0(n, n >> 31, text, 0x20);
            FUN_00edf830(((ILayout*)layout)->FindWindowByID(0x7c8b2a0, 1), p->f170, 0, p->b174,
                         (void*)0x7c8d5f4, text);
            return true;
        }
    }
    if (((Fn00ecf400*)this)->fn(arg, msg))
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x00ed1030
struct Property {               // what the slot-0x24 lookup writes back
    char           pad00[0x12];     // +0x00
    unsigned short type;        // +0x12
};
// reads the current shape's width into the shared float the window setter consumes
// @ 0x00ed1030
void FUN_00ed1030(void)
{
    void* p = ((Fn00b1de80*)FUN_00b3d320())->fn();
    if (p != 0) {
        Property* prop;
        if (((FB_i)(*(void***)p)[0x24 / 4])(p, 0xce54bfcd, &prop) && prop->type == 0xd)
            g_15abf5c = *((Fn0041ea70*)prop)->fn();
    }
    FUN_006a1400((int)p, 0x475f894d, (void*)&g_15ac028);
}

// ---------------------------------------------------------------- 0x00ed10b0
struct Obj10B0 {
    char  pad00[0x28];      // +0x00
    void* cb28;             // +0x28  object asked for the window through vtable slot 3
    void  f(int, int, int, int);
};
// @ 0x00ed10b0
void Obj10B0::f(int a1, int a2, int a3, int a4)
{
    ((Fn00ecf320*)this)->fn(a1, a2, a3, a4);
    FUN_00ed1030();
    void* cb = cb28;
    void* w = 0;
    if (cb != 0)
        w = (void*)((FV_i)(*(void***)cb)[0xc / 4])(cb, 0x3349c94);
    ((Fn005f22f0*)w)->fn(g_15abf5c);
}

// ---------------------------------------------------------------- 0x00ed1120
struct Obj1120 {
    void* vtbl;             // +0x00  set to the callback vtable
    char  pad04[0x20];      // +0x04
    void* f24;              // +0x24
    void* f28;              // +0x28
    void* f2c;              // +0x2c
    void* f(int, int, int, int, int, int, int);
};
// @ 0x00ed1120
void* Obj1120::f(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    ((Fn00929e70*)this)->fn(0, 0, a4, a5, a6, a7, 0);
    f28 = (void*)a1;
    vtbl = (void*)0x13fcab8;
    f2c = (void*)a2;
    f24 = (void*)a3;
    ((Fn00929da0*)this)->fn((void*)0xed1cf0, this, 0);
    return this;
}

// ---------------------------------------------------------------- 0x00ed1180
struct Obj1180 {
    char  pad00[0x0c];      // +0x00
    char  f0c;              // +0x0c
    char  pad0d[3];         // +0x0d
    void* list10;           // +0x10  intrusive list, walked through its 0xcc/0xd0 slots
    char  pad14[4];         // +0x14
    void* f18;              // +0x18  released through vtable slot 5
    char  pad1c[0x18];      // +0x1c
    void* f34;              // +0x34
    void* cb38;             // +0x38
    void  f(int);
};
struct ListNode {               // the arena node the list walks
    char  pad00[0x18];      // +0x00
    void* f18;              // +0x18  handed to the 0x74 manager when the node is torn down
    char  pad1c[0x28];      // +0x1c
    char  b44;              // +0x44
};
struct ListPayload {            // what the arena node's owner points at
    char   pad00[0x7c];     // +0x00
    FV_vii handler;         // +0x7c  called as handler(owner, 1, arg)
};
// @ 0x00ed1180
void Obj1180::f(int arg)
{
    if (list10 != 0) {
        void* first;
        void* last;
        void* l1 = list10;
        ((FV_vi)(*(void***)l1)[0xcc / 4])(l1, (int)&first);
        void* l2 = list10;
        ((FV_vi)(*(void***)l2)[0xd0 / 4])(l2, (int)&last);
        char* node = (char*)first;
        while (node != (char*)last) {
            char* next = *(char**)node;
            char* owner = (char*)g_1440aec + (int)node;
            ListPayload* obj = *(ListPayload**)owner;
            obj->handler(owner, 1, arg);
            node = next;
        }
    }
    void* cb = cb38;
    if ((char)arg != 0) {
        ((Fn0092a7a0*)cb)->fn(0);
        if (f0c != 0) {
            ListNode* p34 = (ListNode*)f34;
            if (p34->b44 == 0)
                ((Fn00f42580*)*(void**)((char*)g_16c7aa4 + 0x74))->fn((void*)&p34->f18);
            ListNode* old = (ListNode*)f34;
            if (old != 0) {
                f34 = 0;
                ((FV_v)(*(void***)old)[8 / 4])(old);
            }
            f0c = 0;
        }
        void* f18 = this->f18;
        ((FV_v)(*(void***)f18)[0x14 / 4])(f18);
        return;
    }
    ((Fn00929c60*)cb)->fn();
}

// ---------------------------------------------------------------- 0x00ed1550
struct Obj1550 {
    char  pad00[0x50];      // +0x00
    void* layout;           // +0x50  cSPUILayout
    char  pad54[0x14];      // +0x54
    char  b68;              // +0x68
};
struct Range3 {                 // three ids, or an array with an inline sentinel
    void* p0;               // +0x00
    void* p1;               // +0x04
    void* p2;               // +0x08
};
// @ 0x00ed1550
void __fastcall FUN_00ed1550(void* self)
{
    Obj1550* o = (Obj1550*)self;
    int* ids = (int*)((Fn00f3bcb0*)*(void**)((char*)g_16c7aa4 + 0x74))->fn();
    Range3 one;
    Range3 two;
    Range3 list;
    one.p0 = (void*)ids[0];
    one.p1 = (void*)ids[1];
    one.p2 = (void*)ids[2];
    two.p0 = (void*)ids[0];
    two.p1 = (void*)ids[1];
    two.p2 = (void*)ids[2];
    list.p0 = (void*)0x1667bac;
    list.p1 = (void*)0x1667bac;
    list.p2 = (void*)0x1667bae;
    FUN_00eeea50(&one, &list);
    ((FV_vi)(*(void***)self)[0x30 / 4])(self, (int)&one);
    ((FV_vii)(*(void***)self)[0x38 / 4])(self, (int)&one, 0);
    one.p1 = (void*)0x2f7d0004;
    ((FV_vii)(*(void***)self)[0x3c / 4])(self, (int)&one, 0);
    ((FV_vi)(*(void***)self)[0x40 / 4])(self, (int)list.p0);
    void* key = &two;
    void* prof = ((Fn004df550*)FUN_00401090(key))->fn(key);
    ((Fn00ecf000*)self)->fn();
    ((Fn00ecf940*)self)->fn();
    ProfileSlot* p = (ProfileSlot*)*(void**)((char*)*(void**)((char*)g_16c7aa4 + 0x74) + 0x10);
    unsigned char on = p->b175;
    void* w = ((ILayout*)o->layout)->FindWindowByID(0x770b540, 1);
    if (w != 0) {
        void* e = (void*)((FV_i)(*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
        if (e != 0)
            ((FV_vii)(*(void***)e)[0x28 / 4])(e, 4, (int)on);
    }
    float f = -1.0f;
    int units = 0;
    if (prof != 0) {
        float v = FUN_004d12a0(FUN_00c028b0(prof, 1)) + ((SpeciesProfile*)prof)->f56c;
        int i = (int)v;
        if ((float)i < v)
            i++;
        units = i;
        f = (float)i * p->f170;
    }
    int n = (int)f;
    if ((float)n < f)
        n++;
    char text[0x20];
    FUN_00881ae0(n, n >> 31, text, 0x20);
    FUN_00edf830(((ILayout*)o->layout)->FindWindowByID(0x7c8b2a0, 1), p->f170, 0, p->b174,
                 (void*)0x7c8d5f4, text);
    if (prof != 0) {
        ((bool (__thiscall*)(void*, int, float))FUN_00ed13e0)(self, 0x18ac46e, g_13ec4d0);
        ((bool (__thiscall*)(void*, int, float))FUN_00ed13e0)(self, 0x73a95a0, g_13ec4d0);
        float v2 = ((SpeciesProfile*)prof)->f644;
        int j = (int)v2;
        if ((float)j < v2)
            j++;
        void* w2 = ((ILayout*)o->layout)->FindWindowByID(0x4d039a8, 1);
        if (w2 != 0) {
            FUN_00881ae0(units, units >> 31, text, 0x20);
            ((FV_vi)(*(void***)w2)[0x80 / 4])(w2, (int)text);
        }
        void* w3 = ((ILayout*)o->layout)->FindWindowByID(0x73a9570, 1);
        if (w3 != 0) {
            FUN_00881ae0(j, j >> 31, text, 0x20);
            ((FV_vi)(*(void***)w3)[0x80 / 4])(w3, (int)text);
        }
    }
    void* ms = FUN_0067dcc0();
    ((void (__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, (int)0x796d3a0, -2, 0);
    o->b68 = 1;
    unsigned count = (unsigned)((char*)list.p2 - (char*)list.p0) & 0xfffffffeu;
    if (count > 2 && list.p0 != 0)
        EA_Free(list.p0);
}
