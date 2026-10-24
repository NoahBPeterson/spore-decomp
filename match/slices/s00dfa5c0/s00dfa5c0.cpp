// Slice s00dfa5c0 -- editor/asset-browser GUI helper methods.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern void* g_panels;        // 0x016a1344
extern void* g_lay;           // 0x015a4318
extern void* g_editor;        // 0x016c7aa4
extern float g_one;           // 0x013ec468 (wstring empty)

void  operator_delete_(void* p);            // 0x00f47380
void  WString_Assign(void* a, void* b);     // 0x00423650
struct F28 { void M(); };                   // 0x00f280f0 thiscall
void* operator_new(unsigned int n, const char* cat, int a, int b, const char* file, int line); // 0x00f473a0
void* FUN_00dfa460(void* self, void* a, int b); // 0x00dfa460
void  FUN_00df97e0(void* self);             // 0x00df97e0
void  FUN_00df9990(void* self);             // 0x00df9990
void  FUN_00df9a00(void* self);             // 0x00df9a00
void  FUN_00df9a70(void* self);             // 0x00df9a70
void  FUN_00df9ad0(void* self);             // 0x00df9ad0
void  FUN_00df9be0(void* self);             // 0x00df9be0
void  FUN_00dfa370(void* self);             // 0x00dfa370
void  FUN_00dfa3c0(void* a, void* b, void* c, void* d, int e); // 0x00dfa3c0
void  FUN_00dfa5c0(void* self, int a);      // 0x00dfa5c0
void  FUN_00dfab20(void* self, int a);      // 0x00dfab20
unsigned char FUN_00ec4320(void* a);        // 0x00ec4320
unsigned char FUN_00ec5a60(void* a, int b, int c); // 0x00ec5a60
void* FUN_00ef19f0(void);                   // 0x00ef19f0
void  FUN_00b3d410(int a, void* b, int c);  // 0x00b3d410
void  FUN_00e3e350(int a, void* b, int c);  // 0x00e3e350
void  FUN_00de0890(void* a);                // 0x00de0890
void  FUN_00de86d0(void* a, int b, int c);  // 0x00de86d0
void  FUN_00de5330(void* a, int b);         // 0x00de5330
void  FUN_00de07a0(float f);                // 0x00de07a0
void  FUN_00de5470(void* a, int b);         // 0x00de5470
void  FUN_00dd9190();                       // 0x00dd9190
void  FUN_00ddb760(void* a);                // 0x00ddb760
void* GetSaveArea(int a, int b);            // 0x006b1f90
void  SaveResource(void* a, void* b);       // 0x006b1d50
void  GetPropertyAsKeyArray2();
void  cString_ctor(void* self, int a, int b, int c); // 0x006b5770
void* cString_GetText(void* self);          // 0x006b55c0
void  SetTooltipText(void* w, void* txt, int a, int b); // 0x00806de0
void* AssetBrowser();                        // 0x00401030
void  cSPUIAssetBrowser_Update(void* a);    // 0x0064ab20
void  KillSetiEffects2(void* a, int b);     // 0x00435ed0
void* GetSystemAT();                         // 0x00a206f0
void* AppSystem();                           // 0x0067dd00
void* FUN_004010a0();                        // 0x004010a0
void* FUN_005ecf80(void* a, int b);          // 0x005ecf80
void* FUN_00b3d4d0v(int a);                  // maybe

struct UI {
    // vtable helpers via raw casts
    void FUN_a710(char on);      // 0xdfa710
    void FUN_a790(char on);      // 0xdfa790
    void FUN_a5c0(int a);        // 0xdfa5c0
    void FUN_a810();             // 0xdfa810
    void FUN_a930();             // 0xdfa930
    void FUN_ab20(bool enable);  // 0xdfab20
    void FUN_aca0(int* pos);     // 0xdfaca0
    void FUN_ad50(int* pos);     // 0xdfad50
    UI*  FUN_ae00(void* other);  // 0xdfae00
    void FUN_ae50();             // 0xdfae50
    void FUN_ae90();             // 0xdfae90
    void FUN_af80();             // 0xdfaf80
    void FUN_b040(int key, int arg2); // 0xdfb040
    void FUN_b0d0();             // 0xdfb0d0
    void FUN_b130(void* o);      // 0xdfb130
    void FUN_b280(void* o);      // 0xdfb280
    void FUN_b3c0(void* o);      // 0xdfb3c0
    void FUN_b430(int a);        // 0xdfb430
    void FUN_b450();             // 0xdfb450
    void FUN_b470(int a);        // 0xdfb470
    void FUN_97e0();             // 0x00df97e0 (this file's callee)
    void FUN_9ad0();             // 0x00df9ad0
    void FUN_9be0();             // 0x00df9be0
};

// direct-call stubs; ecx = implied this (address in comment)
struct Obj {
    void  M_de53d0(int a);                          // 0x00de53d0
    void  M_de5470(int a);                          // 0x00de5470
    void  M_de5330(int a);                          // 0x00de5330
    void  M_de86d0(int a, int b);                   // 0x00de86d0
    void  M_de0890();                               // 0x00de0890
    void  M_de07a0(float f);                        // 0x00de07a0
    void  M_e01350(int v);                          // 0x00e01350
    unsigned char M_ec4320();                       // 0x00ec4320
    unsigned char M_ec5a60(int* pos, int a, int b); // 0x00ec5a60
    void* M_8105b0(int id, int flag);               // 0x008105b0
    unsigned char M_810590(int v);                  // 0x00810590
    void  M_e3e350(int a, void* b, int c);          // 0x00e3e350
    void  M_93db80(int a);                          // 0x0093db80
    void  M_422e20(void* p);                        // 0x00422e20
    char* M_41e920();                               // 0x0041e920
    void  M_6b5770(int a, int b, int c);            // 0x006b5770
    void  M_6b5240();                               // 0x006b5240
    wchar_t* M_6b55c0();                            // 0x006b55c0
    void* M_5ecf80(void* out, int key);             // 0x005ecf80
    void* M_644b10();                               // 0x00644b10
    void  M_644b60();                               // 0x00644b60
};

struct Eff9 { int f[9]; };                          // 0x15accc8 singleton

extern int  g_arr15a4318[];      // 0x015a4318 (32 panel ids)
extern int  g_15da7c4;           // 0x015da7c4
extern int  g_15da7c8;           // 0x015da7c8
extern int  g_15da7cc;           // 0x015da7cc
extern int  g_15da7d0;           // 0x015da7d0
extern char g_d1654c10[];        // 0x01654c10
extern void* g_appPrefs;         // 0x015fd91c

void* __cdecl F_ef19f0(void);        // 0x00ef19f0
void* __cdecl F_b3d410(void);        // 0x00b3d410
void  __cdecl F_6447c0(int a, void** out); // 0x006447c0
void  __cdecl F_64a990(void* p);     // 0x0064a990
void* __cdecl F_4010a0();            // 0x004010a0
void* __cdecl AppSystem();           // 0x0067dd00
void* __cdecl GetSaveArea(unsigned int a); // 0x006b1f90
void  __cdecl SaveResource(void* a, unsigned int b, char c); // 0x006b1d50

// @ 0x00dfaa40
int F_dfa40(int a, int b, int c)
{
    if (a == b) return c;
    do {
        int p = *(int*)(a + 0x10);
        if ((2 < (int)(*(int*)(a + 0x18) - p & 0xfffffffeU)) && p != 0)
            operator_delete_((void*)p);
        a += 0x24;
        c += 0x24;
    } while (a != b);
    return c;
}

// @ 0x00dfaa90
int F_dfa90(int a, int b, int c)
{
    if (b == a) return c;
    do {
        int src = b - 0x24;
        int dst = c - 0x24;
        *(int*)dst = *(int*)src;
        *(int*)(dst + 4) = *(int*)(src + 4);
        *(int*)(dst + 8) = *(int*)(src + 8);
        *(unsigned char*)(dst + 0xc) = *(unsigned char*)(src + 0xc);
        if ((void*)(src + 0x10) != (void*)(dst + 0x10))
            WString_Assign(*(void**)(src + 0x10), *(void**)(src + 0x14));
        *(int*)(dst + 0x20) = *(int*)(src + 0x20);
        b = src;
        c = dst;
    } while (b != a);
    return c;
}

// @ 0x00dfaaf0
void __stdcall F_dfaf0(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x44)
        ((F28*)(a + 4))->M();
}

// @ 0x00dfb240
void __stdcall F_dfb240(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x24) {
        int p = *(int*)(a + 0x10);
        if ((2 < (int)(*(int*)(a + 0x18) - p & 0xfffffffeU)) && p != 0)
            operator_delete_((void*)p);
    }
}

// @ 0x00dfb380
struct Vec44 { unsigned int b, e; void Dtor(); };
void Vec44::Dtor()
{
    unsigned int* v = (unsigned int*)this;
    unsigned int end = v[1];
    for (unsigned int p = *v; p < end; p += 0x44)
        ((F28*)(p + 4))->M();
    unsigned int b = *v;
    if (b != 0 && *(int*)(b - 4) != 0)
        operator_delete_((void*)b);
}

// @ 0x00dfa710
void UI::FUN_a710(char on)
{
    void* vt = (char*)this + 0x84;
    if (*(int*)vt != 0) {
        void* o = *(void**)vt;
        ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
        o = *(void**)vt;
        if (o != 0) {
            *(int*)vt = 0;
            ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
        }
    }
    if (on != 0) {
        void* mgr = *(void**)((char*)g_panels + 0x15c);
        if (mgr != 0) {
            void* o = *(void**)vt;
            if (o != 0) {
                *(int*)vt = 0;
                ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
            }
            unsigned char ok = ((unsigned char(__thiscall*)(void*, int, int, void*))(*(void***)mgr)[8 / 4])(mgr, 0x4827b9d4, 0, vt);
            if (ok) {
                void* p = *(void**)vt;
                ((void(__thiscall*)(void*, int))(*(void***)p)[8 / 4])(p, 0);
            }
        }
    }
}

// @ 0x00dfa790
void UI::FUN_a790(char on)
{
    void* vt = (char*)this + 0x88;
    if (*(int*)vt != 0) {
        void* o = *(void**)vt;
        ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
        o = *(void**)vt;
        if (o != 0) {
            *(int*)vt = 0;
            ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
        }
    }
    if (on != 0) {
        void* mgr = *(void**)((char*)g_panels + 0x15c);
        if (mgr != 0) {
            void* o = *(void**)vt;
            if (o != 0) {
                *(int*)vt = 0;
                ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
            }
            unsigned char ok = ((unsigned char(__thiscall*)(void*, int, int, void*))(*(void***)mgr)[8 / 4])(mgr, 0x139f4a74, 0, vt);
            if (ok) {
                void* p = *(void**)vt;
                ((void(__thiscall*)(void*, int))(*(void***)p)[8 / 4])(p, 0);
            }
        }
    }
}

struct CStr {
    void Assign(void* o);   // 0x006b5430 thiscall ret 4
};
struct WStrAssign {
    void assign(void* b, void* e);   // 0x00423650 thiscall ret 8
};

// @ 0x00dfae00
UI* UI::FUN_ae00(void* other)
{
    char* o = (char*)other;
    ((CStr*)this)->Assign(other);
    if ((void*)(o + 0x14) != (void*)((char*)this + 0x14))
        ((WStrAssign*)((char*)this + 0x14))->assign(*(void**)(o + 0x14), *(void**)(o + 0x18));
    *(int*)((char*)this + 0x24) = *(int*)(o + 0x24);
    *(int*)((char*)this + 0x28) = *(int*)(o + 0x28);
    if ((void*)(o + 0x2c) != (void*)((char*)this + 0x2c))
        ((WStrAssign*)((char*)this + 0x2c))->assign(*(void**)(o + 0x2c), *(void**)(o + 0x30));
    return this;
}

// @ 0x00dfb430
void UI::FUN_b430(int a)
{
    (void)a;
    FUN_ab20(0);
    FUN_97e0();
}

// @ 0x00dfb450
void UI::FUN_b450()
{
    FUN_ab20(0);
    FUN_97e0();
}

// ---- complex GUI methods -----------------------------------------------------
struct cSPUILayoutX {
    void* FindWindowByID(unsigned int id, char flag);   // 0x8105b0
    unsigned char SetVisibility(char v);                // 0x810590
};
struct cSPUIGlobalUIX {
    void SetVisibility(int v);                          // 0xe01350
};
struct WStrX {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* mAlloc;       // +0x0c
    void assign(const void* b, const void* e);          // 0x423650
};
struct cStringX {
    int f[5];                                           // 0x14 bytes
    void  Ctor(unsigned int a, unsigned int b, const wchar_t* c); // 0x6b5770
    void  Dtor();                                       // 0x6b5240
    const void* GetText();                              // 0x6b55c0
};
struct VariantX {
    int f[4];                    // +0x00..0x0f
    unsigned short mFlags;       // +0x10
    unsigned short mTypeId;      // +0x12
    void SetBool(const bool* b); // 0x422e20
};

struct LaunchInfo {
    unsigned int type;          // +0x00
    void* self;                 // +0x04
    unsigned int pad8;          // +0x08
    void* obj;                  // +0x0c
    unsigned char f10, f11, f12, f13, f14;  // +0x10..0x14
    unsigned char p15, p16, p17;
    int v18, v1c, v20;          // +0x18,0x1c,0x20
    unsigned char b24;          // +0x24
    unsigned char p25, p26, p27;
    unsigned int f28;           // +0x28
    unsigned char b2c;          // +0x2c
    unsigned char p2d, p2e, p2f;
    void* fn;                   // +0x30
    unsigned int f34;           // +0x34
    void* f38;                  // +0x38
    unsigned int f3c;           // +0x3c
    void* sp40;                 // +0x40
    void* sp44;                 // +0x44
};
struct LaunchInfoOps { void Ctor(); void Dtor(); };
extern char vtbl_147dc04, vtbl_149bad8, vtbl_13ec458, LAB_ad0e52;

struct RefCountBase { void* vtbl; unsigned int count; };
static __forceinline void PtrAssign(void*& slot, void* p)
{
    if (p != slot) {
        void* old = slot;
        if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        slot = p;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
    }
}

// @ 0x00dfa5c0
void UI::FUN_a5c0(int a)
{
    *(int*)((char*)this + 0x34) = a;
    ((Obj*)g_panels)->M_de53d0(0);
    void* out = 0;
    F_6447c0(0, &out);
    *(unsigned int*)((char*)out + 0x24) = (unsigned int)g_15da7c4;
    *(unsigned int*)((char*)out + 0x28) = (unsigned int)g_15da7c8;
    *(unsigned int*)((char*)out + 0x2c) = (unsigned int)g_15da7cc;
    *(unsigned int*)((char*)out + 0x30) = (unsigned int)g_15da7d0;
    *(unsigned char*)((char*)out + 0x34) = 0;
    LaunchInfo data;
    ((LaunchInfoOps*)&data)->Ctor();
    data.self = this;
    void* obj = operator_new(0x14, "Sporepedia", 0, 0, 0, 0);
    if (obj) {
        RefCountBase* b = (RefCountBase*)((char*)obj + 4);
        *(void* volatile*)&b->vtbl = &vtbl_13ec458;
        b->count = 0;
        *(void**)((char*)obj + 0x00) = &vtbl_147dc04;
        *(void**)((char*)obj + 0x04) = &vtbl_149bad8;
        *(void**)((char*)obj + 0x0c) = g_panels;
        *(unsigned char*)((char*)obj + 0x10) = 0;
    }
    data.obj = obj;
    data.f38 = (char*)this + 8;
    char* p = (char*)this + *(int*)((char*)this + 0x34) * 0x38 + 0xc0;
    data.type = 0xf25aef31;
    data.fn = &LAB_ad0e52;
    data.v18 = *(int*)p;
    data.v1c = *(int*)(p + 4);
    data.v20 = *(int*)(p + 8);
    data.b24 = 0;
    PtrAssign(data.sp44, out);
    F_64a990(&data);
    ((LaunchInfoOps*)&data)->Dtor();
    if (out) ((void(__thiscall*)(void*))(*(void***)out)[2])(out);
}
struct V3 { int x, y, z; };
// @ 0x00dfa810
void UI::FUN_a810()
{
    ((Obj*)g_panels)->M_de5470(1);
    char* lay = (char*)this + 0x48;
    for (unsigned int i = 0; i < 0x80; i += 4) {
        void* w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
        if (w != 0) {
            void* cb = g_panels ? (char*)g_panels + 4 : 0;
            w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
            ((void(__thiscall*)(void*, void*))(*(void***)w)[0x108 / 4])(w, cb);
        }
    }
    switch (*(int*)((char*)this + 0x20)) {
    case 1: case 2: case 4: case 5: case 7:
        break;
    default:
        if (*(int*)((char*)this + 0x84) != 0) {
            void* o = *(void**)((char*)this + 0x84);
            ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
            o = *(void**)((char*)this + 0x84);
            if (o != 0) {
                *(int*)((char*)this + 0x84) = 0;
                ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
            }
        }
        V3 zero = { 0, 0, 0 };
        *(V3*)((char*)this + 0x8c) = zero;
        *(V3*)((char*)this + 0x98) = zero;
        *(V3*)((char*)this + 0xa4) = zero;
        *(V3*)((char*)this + 0xb0) = zero;
    }
}
// @ 0x00dfa930
void UI::FUN_a930()
{
    void* prefs = g_appPrefs;
    char value = 1;
    if (prefs != 0) {
        int prop;
        if (((unsigned char(__thiscall*)(void*, int, int*))(*(void***)prefs)[0x24 / 4])(prefs, 0x806dbba, &prop) &&
            *(short*)(prop + 0x12) == 1)
            value = *(char*)((Obj*)prop)->M_41e920();
    }
    bool saved = false;
    if (*(int*)((char*)g_panels + 0x1f8) == 1 && value != 0) {
        saved = true;
        VariantX v;
        v.mFlags = 0;
        v.mTypeId = 0;
        bool b = false;
        v.SetBool(&b);
        ((void(__thiscall*)(void*, int, void*))(*(void***)prefs)[0x14 / 4])(prefs, 0x806dbba, &v);
        if (v.mFlags & 4)
            ((Obj*)&v)->M_93db80(0);
        SaveResource(prefs, (unsigned int)GetSaveArea(0x11ac192), 0);
    }
    void* lay = (char*)this + 0x48;
    void* w = ((cSPUILayoutX*)lay)->FindWindowByID(0x806e700, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, saved);
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x806e720, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, saved);
}
// @ 0x00dfab20
void UI::FUN_ab20(bool enable)
{
    if (((Obj*)*(void**)((char*)g_editor + 0x1c))->M_ec4320())
        enable = false;
    char* lay = (char*)this + 0x48;
    void* w;
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x733ebd5, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, enable);
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x7c4f832, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, enable);
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x73bba58, 1);
    int buf[5];
    ((cStringX*)buf)->Ctor(0x3dade1bb, 0x7eb5184, 0);
    if (w != 0) {
        bool on;
        if (*(int*)((char*)g_panels + 0x1f8) == 0) {
            void* app = AppSystem();
            on = ((unsigned char(__thiscall*)(void*))(*(void***)app)[0x54 / 4])(app);
        } else {
            on = true;
        }
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 2, on);
        const void* text = on ? (const void*)&g_one : ((cStringX*)buf)->GetText();
        SetTooltipText(w, (void*)text, -1, 1);
    }
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x74d0932, 1);
    if (w != 0) {
        bool on;
        if (*(int*)((char*)g_panels + 0x1f8) == 0) {
            void* app = AppSystem();
            on = ((unsigned char(__thiscall*)(void*))(*(void***)app)[0x54 / 4])(app);
        } else {
            on = true;
        }
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 2, on);
        const void* text = on ? (const void*)&g_one : ((cStringX*)buf)->GetText();
        SetTooltipText(w, (void*)text, -1, 1);
    }
    if (enable)
        FUN_a930();
    ((cStringX*)buf)->Dtor();
}
// @ 0x00dfaca0
void UI::FUN_aca0(int* pos)
{
    *(int*)((char*)this + 0x20) = 8;
    *(int*)((char*)this + 0x24) = 9;
    *(V3*)((char*)this + 0x98) = *(V3*)pos;
    V3 zero = { 0, 0, 0 };
    *(V3*)((char*)this + 0xb0) = zero;
    FUN_ab20(0);
    void* ed = *(void**)((char*)g_editor + 0x1c);
    unsigned char ok = ((Obj*)ed)->M_ec5a60(pos, 1, 0);
    if (ok == 0) {
        V3 z = { 0, 0, 0 };
        *(V3*)((char*)this + 0x8c) = z;
        *(V3*)((char*)this + 0x98) = z;
        *(int*)((char*)this + 0x20) = 0;
        FUN_ab20(1);
        *(unsigned char*)((char*)this + 0x7e) = 1;
    }
}
// @ 0x00dfad50
void UI::FUN_ad50(int* pos)
{
    *(int*)((char*)this + 0x20) = 9;
    FUN_ab20(0);
    *(V3*)((char*)this + 0xb0) = *(V3*)pos;
    V3 zero = { 0, 0, 0 };
    *(V3*)((char*)this + 0x8c) = zero;
    *(int*)((char*)this + 0x28) = 10;
    Eff9* e = (Eff9*)F_ef19f0();
    e->f[0] = *(int*)((char*)this + 0x8c);
    e->f[1] = *(int*)((char*)this + 0x90);
    e->f[2] = *(int*)((char*)this + 0x94);
    e->f[3] = pos[0];
    e->f[4] = pos[1];
    e->f[5] = pos[2];
    V3 z6 = { 0, 0, 0 };
    *(V3*)&e->f[6] = z6;
    ((Obj*)F_b3d410())->M_e3e350(1, (void*)g_d1654c10, 1);
}
// @ 0x00dfae50
void UI::FUN_ae50()
{
    FUN_9ad0();
    FUN_ab20(0);
    *(int*)((char*)this + 0x20) = 10;
    *(unsigned char*)((char*)this + 0x80) = 1;
    *(int*)((char*)this + 0x28) = 10;
    ((cSPUILayoutX*)((char*)g_panels + 0x144))->SetVisibility(0);
    FUN_9be0();
}
// @ 0x00dfae90
void UI::FUN_ae90()
{
    char* lay = (char*)this + 0x48;
    for (unsigned int i = 0; i < 0x80; i += 4) {
        void* w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
        if (w != 0) {
            void* cb = g_panels ? (char*)g_panels + 4 : 0;
            w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
            ((void(__thiscall*)(void*, void*))(*(void***)w)[0x104 / 4])(w, cb);
        }
    }
    void* gui = *(void**)((char*)g_panels + 0x184);
    ((cSPUIGlobalUIX*)gui)->SetVisibility(0);
    void* w = ((cSPUILayoutX*)((char*)g_panels + 0x144))->FindWindowByID(0x615a5ff, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, 0);
    FUN_a930();
    switch (*(int*)((char*)this + 0x20)) {
    case 1: case 2: case 4: case 5: case 7:
        break;
    default:
        *(int*)((char*)this + 0x24) = 9;
        *(int*)((char*)this + 0x20) = 0xb;
        ((Obj*)*(void**)((char*)g_panels + 0x198))->M_de07a0(1.0f);
    }
}
// @ 0x00dfaf80
void UI::FUN_af80()
{
    WStrX buf;
    void* q = ((Obj*)FUN_004010a0())->M_5ecf80(&buf, 0x51aa76bb);
    if (q != (char*)this + 0x168)
        ((WStrX*)((char*)this + 0x168))->assign(*(void**)q, *(void**)((char*)q + 4));
    if ((2 < ((int)((char*)buf.mpCapacity - (char*)buf.mpBegin) & (int)0xfffffffe)) && buf.mpBegin != 0)
        operator_delete_(buf.mpBegin);
    char* lay = (char*)this + 0x48;
    void* w = ((cSPUILayoutX*)lay)->FindWindowByID(0x5400fa5, 1);
    if (w != 0) {
        void* t = ((void*(__thiscall*)(void*, int))(*(void***)w)[0xc / 4])(w, 0xcf428691);
        if (t != 0)
            ((void(__thiscall*)(void*, void*, int))(*(void***)t)[0x60 / 4])(t, *(void**)((char*)this + 0x168), 0);
    }
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x7cce848, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, void*))(*(void***)w)[0x80 / 4])(w, *(void**)((char*)this + 0x168));
    *(unsigned char*)((char*)this + 0x7e) = 1;
}
// @ 0x00dfb040
void UI::FUN_b040(int key, int arg2)
{
    (void)arg2;
    if (*(unsigned char*)((char*)this + 0x80) != 0)
        return;
    if (key != 0x1b)
        return;
    if (*(int*)((char*)this + 0x20) == 0) {
        FUN_ab20(0);
        void* au = GetSystemAT();
        int r;
        if (au != 0) {
            r = ((int(__thiscall*)(void*))(*(void***)au)[0x20 / 4])(au);
        } else {
            r = 0;
        }
        KillSetiEffects2((void*)0xebadb118, r);
        ((Obj*)*(void**)((char*)g_panels + 0x198))->M_de0890();
        ((Obj*)g_panels)->M_de86d0(2, 0);
        ((Obj*)g_panels)->M_de5330(1);
    } else {
        FUN_9ad0();
        *(int*)((char*)this + 0x20) = 0;
    }
}
// @ 0x00dfb0d0
void UI::FUN_b0d0() {}
// @ 0x00dfb130
void UI::FUN_b130(void* o) { (void)o; }
// @ 0x00dfb280
void UI::FUN_b280(void* o) { (void)o; }
// @ 0x00dfb3c0
void UI::FUN_b3c0(void* o) { (void)o; }
// @ 0x00dfb470
void UI::FUN_b470(int a) { (void)a; }
