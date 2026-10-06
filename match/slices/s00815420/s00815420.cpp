// Slice s00815420 (w2g7 #3), 32-bit MSVC 2008 SP1.
// UI cheats / text-style loading / cSPUIMainWin::InitFonts.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

static inline void** Vtbl(void* o) { return *(void***)o; }

extern "C" void* __cdecl SP_ConfigManager();
extern "C" void* __cdecl SP_WindowManager();
extern "C" void* __cdecl EA_Text_GetFontServer(int);
extern "C" void* __cdecl EA_Text_GetStyleManager(int);
extern "C" void* __cdecl FUN_00805510(int);

void* __cdecl EAlloc(int size, int tag, int a, int b, int c, int d);   // 0xf473a0
void  __cdecl ArgScript_Output(void* parser, const char* fmt);          // 0x841000

// ---------------------------------------------------------------------------
// cSPUILayoutZoom-like outer object for the tiny wrappers
// ---------------------------------------------------------------------------
struct Inner { void Method(int, int); };   // 0x83b9d0
struct Outer {
    char pad0[0x4];
    int f4;                 // +0x4
    char pad1[0x10 - 0x8];
    Inner inner;            // +0x10
    void Wrap(int);         // 0x815b30
    void ExecuteColor(int); // 0x815a50
    char pad2[0xd8 - 0x10 - sizeof(Inner)];
    uint8_t bD8;            // +0xd8
};

// @ 0x00815b30
void Outer::Wrap(int arg) {
    inner.Method(arg, f4);
}

// @ 0x00815a50
void  __cdecl cString_SetColorLocalized(int);   // 0x6b5030
void Outer::ExecuteColor(int arg) {
    inner.Method(arg, f4);
    void* wm = SP_WindowManager();
    if (wm) {
        ((void(__thiscall*)(void*, int))Vtbl(wm)[0x90 / 4])(wm, bD8);
        cString_SetColorLocalized(bD8);
    }
}

// ---------------------------------------------------------------------------
// ConfigManager-backed cheat Execute
// ---------------------------------------------------------------------------
struct Mgr {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m0a();
    virtual void v2c(int, int);         // 0x2c
    virtual int  v30(int);              // 0x30
    virtual void p34(); virtual void p38();
    virtual void v3c();                 // 0x3c
};
struct Args {
    void MainArguments(void*, int, int);
};

struct Cheat {
    char pad0[0x4];
    void* mParser;          // +0x4
    void Execute(Args* args);   // 0x815990
};

// @ 0x00815990
void Cheat::Execute(Args* args) {
    int captured;
    args->MainArguments(&captured, 0, 0x7fffffff);
    Mgr* cm = (Mgr*)SP_ConfigManager();
    int v = cm->v30(0x631621a);
    cm = (Mgr*)SP_ConfigManager();
    cm->v2c(0x631621a, v == 0);
    cm = (Mgr*)SP_ConfigManager();
    cm->v3c();
    if (v != 0) {
        ArgScript_Output(mParser, "capture UI is off\n");
        return;
    }
    ArgScript_Output(mParser, "capture UI is on (captures at game resolution)\n");
}

// ---------------------------------------------------------------------------
// Text style loading + InitFonts
// ---------------------------------------------------------------------------
struct FontServer {
    virtual void f00(); virtual void f04();
    virtual void f08(int, int);
    virtual void f0c(); virtual void f10(); virtual void f14(); virtual void f18();
    virtual void f1c(); virtual void f20(); virtual void f24(); virtual void f28();
    virtual void f2c(); virtual void f30(); virtual void f34();
    virtual void f38(const wchar_t*, const wchar_t*);
    void* Init(void*);
};
struct StyleManager {
    void* Init(void*);
};
void __cdecl FUN_00885b00(void*);   // 0x885b00
void __cdecl FUN_00885af0(void*);   // 0x885af0
void __cdecl FUN_00885b50(void*);   // 0x885b50 (unused)
bool __cdecl LoadTextStyles(int, int);   // 0x815bd0

extern void* g_164d348;   // 0x164d348

// @ 0x00815ce0
bool cSPUIMainWin_InitFonts() {
    FontServer* fs = (FontServer*)EAlloc(0x2fd0, 0x13f6b3c, 0, 0, 0, 0);
    if (fs) fs = (FontServer*)fs->Init(FUN_00805510(1));
    else fs = 0;
    fs->f04();
    fs->f08(2, 1);
    FUN_00885b00(fs);
    fs->f38(L"web-default", L"Palatino Sans Infl Com");
    fs->f38(L"monospace", L"Lucida Console");
    StyleManager* sm = (StyleManager*)EAlloc(0x120, 0x13f6b3c, 0, 0, 0, 0);
    void* smp;
    if (sm) smp = sm->Init(FUN_00805510(1));
    else smp = 0;
    *(void**)((char*)g_164d348 + 0x10) = smp;
    FUN_00885af0(smp);
    LoadTextStyles(0x94da47e5, 0);
    LoadTextStyles(0x94da47e5, 1);
    return true;
}

// ---------------------------------------------------------------------------
// TextStyleReader bits (approximate)
// ---------------------------------------------------------------------------
void __cdecl EastlDealloc(void*);          // 0xf47380

// @ 0x00815aa0
void HashtableDoFreeNodes(void* self, void** buckets, unsigned n) {
    char* s = (char*)self;
    for (unsigned i = 0; i < n; ++i) {
        char* node = (char*)buckets[i];
        while (node) {
            char* next = *(char**)(node + 0x24);
            void* str = *(void**)node;
            int cap = *(int*)(node + 8) - *(int*)node;
            if (cap > 1 && str && str != *(void**)(node + 0x10))
                EastlDealloc(str);
            if (node != *(char**)(s + 0x30)) {
                if (node < *(char**)(s + 0x24) || node >= *(char**)(s + 0x28))
                    EastlDealloc(node);
                else { *(void**)node = *(void**)(s + 0x1c); *(void**)(s + 0x1c) = node; }
            }
            node = next;
        }
        buckets[i] = 0;
    }
}

// @ 0x00815b50
void TextStyleReader_Dtor(char* t) {
    HashtableDoFreeNodes(t + 0x44, *(void***)(t + 0x48), *(unsigned*)(t + 0x4c));
    void* b = *(void**)(t + 0x48);
    *(int*)(t + 0x50) = 0;
    if (*(int*)(t + 0x4c) > 1 && b && b != *(void**)(t + 0x60))
        EastlDealloc(b);
    void* v = *(void**)(t + 0x34);
    if (*(int*)(t + 0x3c) - (int)v > 1 && v) EastlDealloc(v);
    void* m = *(void**)(t + 0x10);
    if (*(int*)(t + 0x18) - (int)m > 1 && m) EastlDealloc(m);
}

// @ 0x00815bd0 (partial: CSS stream load)
__declspec(noinline) bool LoadTextStyles(int resId, int mode) {
    EA_Text_GetFontServer(1);
    void* sm = EA_Text_GetStyleManager(1);
    (void)sm; (void)resId; (void)mode;
    return true;
}

// ---------------------------------------------------------------------------
// 0x815420 (huge CSS/text style parser) - partial
// ---------------------------------------------------------------------------
void __cdecl FUN_00815420_partial() {
}
