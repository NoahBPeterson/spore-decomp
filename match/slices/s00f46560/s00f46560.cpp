// Slice s00f46560: Spore UI/editor module (SporeApp, /O2 /MD).
//
// The tail of this slice (0x00F47380..0x00F475B0) is the shared-allocator / OS-global
// plumbing and matches byte-for-byte. The leading 18 entries are large UTFWin/editor
// UI message handlers (cSPUIAssetComments, cOnlineTab, cXHTMLFrameSet-derived screens);
// they need the full window/class layouts and are left as documented skeletons here.
// See partial.txt / nonmatching.txt.
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall GetProcessHeap();
extern "C" __declspec(dllimport) void* __stdcall HeapAlloc(void*, unsigned long, unsigned int);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void*, unsigned long, void*);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);

struct Method { void M(); };
struct Method1 { void M(void*); };
struct Method6 { void M(int, int, int, int, int, int); };
struct Method8 { void M(int, int, int, int, int, int, int, int); };
struct V2 { virtual void a(); virtual void b(); };
struct VBig0 {
    virtual char v0();  virtual char v1();  virtual char v2();  virtual char v3();
    virtual char v4();  virtual char v5();  virtual char v6();  virtual char v7();
    virtual char v8();  virtual char v9();  virtual char v10(); virtual char v11();
    virtual char v12(); virtual char v13(); virtual char v14(); virtual char v15();
    virtual char v16(); virtual char v17(); virtual char v18(); virtual char v19();
    virtual char v20(); virtual char v21(); virtual char v22(); virtual char v23();
    virtual char v24(); virtual char v25(); virtual char v26(); virtual char v27();
    virtual char v28(); virtual char v29(); virtual char v30(); virtual char v31();
    virtual char v32(); virtual char v33(); virtual char v34();
};

extern void __cdecl cdecl_free(void*);
extern char __cdecl cdecl_f935ad0(void*);
extern void* __cdecl cdecl_f935c80(int, void*);
extern void* __cdecl cdecl_f67dd10();
extern void __cdecl cdecl_fddde80(void*);
extern void __cdecl cdecl_f57f3e0(void*);
extern void __cdecl cdecl_feb2e70(void*);
extern void __cdecl cdecl_fef1950(void*);
extern void* __cdecl cdecl_Canvas();

extern char* g_16c8b40;
extern char* g_16c8b44;

void* f_47480();
void f_47430();

// =====================================================================
// UI message handlers — documented skeletons (partial).
// @ 0x00F46560 SP::cSPUIAssetComments-ish message handler (167 bytes)
void ui_f46560(int a1) { (void)a1; }

// @ 0x00F46630 SP::cUI...::OnActivate (607 bytes)
int ui_f46630(int a1, int* a2) { (void)a1; (void)a2; return 0; }

// @ 0x00F468C0 SP::cSPUIAssetComments::DoMessage (93 bytes)
unsigned int ui_f468c0(int a1, int a2, int* a3) { (void)a1; (void)a2; (void)a3; return 0; }

// @ 0x00F46920 SP::cOnlineTab::Shutdown (277 bytes)
unsigned int ui_f46920(char* self, void* p) { (void)self; (void)p; return 0; }

// @ 0x00F46A40 cOnlineTab teardown (111 bytes)
char ui_f46a40(char* self) { (void)self; return 1; }

// @ 0x00F46AB0 cOnlineTab::SetFrame (147 bytes)
void ui_f46ab0(char* self, int a2) { (void)self; (void)a2; }

// @ 0x00F46B50 cOnlineTab ctor (133 bytes)
void* ui_f46b50(char* self) { (void)self; return self; }

// @ 0x00F46C00 cOnlineTab dtor (170 bytes)
void ui_f46c00(char* self) { (void)self; }

// @ 0x00F46CD0 message predicate (32 bytes)
struct MsgProc { void Sub(int); char Handler(int, int); };
char MsgProc::Handler(int a, int b) {
    if (a == 0x44db12e && b) ((MsgProc*)((char*)this - 4))->Sub(1);
    return 0;
}

// @ 0x00F46CF0 cOnlineTab URL builder (109 bytes)
void ui_f46cf0(char* self, int a2, int a3, int a4, int a5) {
    (void)self; (void)a2; (void)a3; (void)a4; (void)a5;
}

// @ 0x00F46D60 cOnlineTab::DoMessage (112 bytes)
unsigned int ui_f46d60(char* self, int a2, int* a3) { (void)self; (void)a2; (void)a3; return 0; }

// @ 0x00F46DD0 screen ctor (71 bytes)
void* ui_f46dd0(char* self) { (void)self; return self; }

// @ 0x00F46E30 screen dtor (95 bytes)
void ui_f46e30(char* self) { (void)self; }

// @ 0x00F46EB0 screen::SetFrame (386 bytes)
unsigned int ui_f46eb0(char* self, void* p) { (void)self; (void)p; return 0; }

// @ 0x00F47040 screen teardown (54 bytes)
char ui_f47040(char* self) { (void)self; return 1; }

// @ 0x00F47080 screen::SetVisible (157 bytes)
void ui_f47080(char* self, int a2) { (void)self; (void)a2; }

// @ 0x00F47120 screen::ResetFrames (75 bytes)
void ui_f47120(char* self) { (void)self; }

// @ 0x00F47170 screen::Refresh (523 bytes)
int ui_f47170(char* self, int a2, int a3) { (void)self; (void)a2; (void)a3; return 0; }

// =====================================================================
// Tail: shared allocator / OS global plumbing (byte-exact subset).
// @ 0x00F47380
void f_47380(int p) {
    if (p) ((Method1*)g_16c8b44)->M((void*)p);
}

// @ 0x00F473A0
void f_473a0(int a1, int a2, int a3, int a4, int a5, int a6) {
    ((Method6*)g_16c8b44)->M(a1, a3, a4, a2, a5, a6);
}

// @ 0x00F473D0
void f_473d0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    ((Method8*)g_16c8b44)->M(a1, a2, a3, a5, a6, a4, a7, a8);
}

// @ 0x00F47410
void f_47410(int p) { ((Method1*)g_16c8b44)->M((void*)p); }

// @ 0x00F47430
void f_47430() {
    char* p = g_16c8b40;
    if (p) {
        char ok = cdecl_f935ad0(p);
        p = g_16c8b40;
        if (ok && p) {
            ((Method*)(p + 0x18))->M();
            HeapFree(GetProcessHeap(), 0, p);
        }
        g_16c8b40 = 0;
    }
}

// @ 0x00F47480
void* f_47480() {
    char* p = (char*)HeapAlloc(GetProcessHeap(), 0, 0x530);
    if (p) {
        *(int*)(p + 4) = 0;
        *(int*)p = 0;
        *(int*)(p + 0x10) = 0x2b5c;
        *(p + 0x14) = 0;
        ((Method6*)(p + 0x18))->M(0, 0, 1, 0, 0, 0);
    }
    return p;
}

// @ 0x00F474D0
char f_474d0() {
    if (!g_16c8b40) {
        g_16c8b40 = (char*)cdecl_f935c80(0xee9b7413, (void*)f_47480);
        if (!g_16c8b40) return 0;
    }
    if (*(int*)(g_16c8b40 + 0x10) == 0x2b5c && *(g_16c8b40 + 0x14) == 0) {
        g_16c8b44 = g_16c8b40 + 0x18;
        return 1;
    }
    f_47430();
    return 0;
}

// @ 0x00F47550
void f_47550() {
    void* a = cdecl_f67dd10();
    cdecl_fddde80(a);
    cdecl_f57f3e0(a);
    cdecl_feb2e70(a);
    cdecl_fef1950(a);
}

// @ 0x00F47580
struct CanvasProc { char pad[0xd]; char flag; void Run(); };
void CanvasProc::Run() {
    char c = flag;
    while (true) {
        if (!c) return;
        void* cv = cdecl_Canvas();
        if (!((VBig0*)cv)->v33()) break;
        c = flag;
    }
}

// @ 0x00F475B0
struct Timer { char pad[0x10]; long long last; float freq; int Elapsed(); };
int Timer::Elapsed() {
    long long t;
    QueryPerformanceCounter(&t);
    long long d = t - last;
    return (int)((float)d * freq);
}
