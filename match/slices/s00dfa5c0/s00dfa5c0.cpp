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
void* FUN_004010a0(void* self, int a);       // 0x004010a0
void* FUN_005ecf80(void* a, int b);          // 0x005ecf80
void* FUN_00b3d4d0v(int a);                  // maybe

struct UI {
    // vtable helpers via raw casts
    void FUN_a710(char on);      // 0xdfa710
    void FUN_a790(char on);      // 0xdfa790
    void FUN_a5c0(int a);        // 0xdfa5c0
    void FUN_a810();             // 0xdfa810
    void FUN_a930();             // 0xdfa930
    void FUN_ab20(int a);        // 0xdfab20
    void FUN_aca0(void* pos);    // 0xdfaca0
    void FUN_ad50(void* pos);    // 0xdfad50
    void FUN_ae00(void* other);  // 0xdfae00
    void FUN_ae50();             // 0xdfae50
    void FUN_ae90();             // 0xdfae90
    void FUN_af80();             // 0xdfaf80
    void FUN_b040(int key);      // 0xdfb040
    void FUN_b0d0();             // 0xdfb0d0
    void FUN_b130(void* o);      // 0xdfb130
    void FUN_b280(void* o);      // 0xdfb280
    void FUN_b3c0(void* o);      // 0xdfb3c0
    void FUN_b430(int a);        // 0xdfb430
    void FUN_b450(int a);        // 0xdfb450
    void FUN_b470(int a);        // 0xdfb470
    void FUN_97e0();             // 0x00df97e0 (this file's callee)
};

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
void F_dfb380(unsigned int* v)
{
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

struct CStr { void Assign(void* o); };  // 0x006b5430 thiscall ret 4

// @ 0x00dfae00
void UI::FUN_ae00(void* other)
{
    char* o = (char*)other;
    ((CStr*)this)->Assign(other);
    if ((void*)(o + 0x14) != (void*)((char*)this + 0x14))
        WString_Assign(*(void**)(o + 0x14), *(void**)(o + 0x18));
    *(int*)((char*)this + 0x24) = *(int*)(o + 0x24);
    *(int*)((char*)this + 0x28) = *(int*)(o + 0x28);
    if ((void*)(o + 0x2c) != (void*)((char*)this + 0x2c))
        WString_Assign(*(void**)(o + 0x2c), *(void**)(o + 0x30));
}

// @ 0x00dfb430
void UI::FUN_b430(int a)
{
    (void)a;
    FUN_ab20(0);
    FUN_97e0();
}

// @ 0x00dfb450
void UI::FUN_b450(int a)
{
    (void)a;
    FUN_ab20(0);
    FUN_97e0();
}

// ---- complex GUI methods (partial) -------------------------------------------
// @ 0x00dfa5c0
void UI::FUN_a5c0(int a) { (void)a; }
// @ 0x00dfa810
void UI::FUN_a810() {}
// @ 0x00dfa930
void UI::FUN_a930() {}
// @ 0x00dfab20
void UI::FUN_ab20(int a) { (void)a; }
// @ 0x00dfaca0
void UI::FUN_aca0(void* p) { (void)p; }
// @ 0x00dfad50
void UI::FUN_ad50(void* p) { (void)p; }
// @ 0x00dfae50
void UI::FUN_ae50() {}
// @ 0x00dfae90
void UI::FUN_ae90() {}
// @ 0x00dfaf80
void UI::FUN_af80() {}
// @ 0x00dfb040
void UI::FUN_b040(int k) { (void)k; }
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
