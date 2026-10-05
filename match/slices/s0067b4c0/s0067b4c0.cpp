// Slice s0067b4c0 - cUIHints (on-screen hint controller): hint list parsing,
// teardown, per-hint state transitions and visibility toggling.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-.
#include "types.h"

struct VObj { void** vt; };
typedef void (__thiscall *FnV1)(void*);
typedef void (__thiscall *FnV1i)(void*, int);
void DeleteObj(void* p);              // 0x00f47380
void* __cdecl GetCheatManager();      // 0x0067de20
extern char g_killallhints[];         // 0x01401520 "killallhints"
extern char g_14014b4[];              // command vtable-ish

// ---- external callees -------------------------------------------------
struct EStrSoA { void push_back(int ch); };        // 0x004f6510
struct Layout  { void Shutdown(int); };            // 0x00811ad0
int* __cdecl FUN_00d3b3c0(int a, int b, int c);    // 0x00d3b3c0
struct Vec20 { void Insert(int* r, int* end); };    // 0x00a693f0 (member at this+0x20)
void __cdecl FUN_00816990(char* p);                // 0x00816990

struct cUIHints {
    char pad[0x4c];
    int* mpCurrent;  // +0x4c

    __declspec(noinline) char ParseHints();            // 0x0067b4c0
    void InitHints();                                  // 0x0067ba10
    void Destroy2();                                   // 0x0067bb80
    int  Insert(int a, int b);                         // 0x0067bbf0
    int  Forward(int a, int b);                        // 0x0067b030 (defined elsewhere)
    void SetVisibilityImpl(int b, void* c);            // 0x0067bc30 (defined elsewhere)
    __declspec(noinline) void UpdateHints(char b, char c); // 0x0067c350
    void Next(int a, char b);                          // 0x0067c3b0
    void SetFlag(char a, int b);                       // 0x0067c420
};

// ---- 0x0067b4c0 : cUIHints::ParseHints (partial skeleton) ------------
// @ 0x0067b4c0
char cUIHints::ParseHints() { return 0; }

// ---- 0x0067ba10 : cUIHints::InitHints (partial skeleton) -------------
// @ 0x0067ba10
void cUIHints::InitHints() { }

// ---- 0x0067bb80 : teardown hints list + layout -----------------------
// @ 0x0067bb80
void cUIHints::Destroy2() {
    char* p = (char*)this;
    int* begin = *(int**)(p + 0x20);
    int* end = *(int**)(p + 0x24);
    int* r = FUN_00d3b3c0((int)end, (int)end, (int)begin);
    ((Vec20*)(p + 0x20))->Insert(r, end);
    *(int*)(p + 0x24) += (end - begin) * -4;
    if (*(void**)(p + 0x3c)) {
        ((Layout*)*(void**)(p + 0x3c))->Shutdown(1);
        if (*(void**)(p + 0x3c)) {
            void* x = *(void**)(p + 0x3c);
            ((FnV1i)((VObj*)x)->vt[0])(x, 1);
        }
        *(int*)(p + 0x3c) = 0;
    }
    void* cm = GetCheatManager();
    ((FnV1i)((VObj*)cm)->vt[0x1c / 4])(cm, (int)g_killallhints);
}

// ---- 0x0067bbf0 : insert at end / forward to FUN_0067b030 -------------
// @ 0x0067bbf0
int cUIHints::Insert(int a, int b) {
    if (a == *(int*)((char*)this + 4)) {
        ((EStrSoA*)this)->push_back(b);
        return *(int*)((char*)this + 4) - 2;
    }
    return Forward(a, b);
}

// ---- 0x0067bc30 : cUIHints::SetVisibility (partial skeleton) ---------
// @ 0x0067bc30
void cUIHints_SetVisibilitySkeleton(cUIHints* self, int b, void* c) { (void)self; (void)b; (void)c; }

// ---- 0x0067c350 : cUIHints::UpdateHints ------------------------------
// @ 0x0067c350
void cUIHints::UpdateHints(char b, char c) {
    char* e = *(char**)((char*)this + 0x4c);
    if (e) {
        char v;
        if (c == 0 || *(int*)(e + 0x70) != 0x1f9e21e8) v = b; else v = 1;
        *(int*)(e + 0x90) = (v == 0);
        char* e2 = *(char**)((char*)this + 0x4c);
        *(float*)(e2 + 0x94) = 0.0f;
        SetVisibilityImpl(0, *(char**)((char*)this + 0x4c));
    }
    *(int*)((char*)this + 0x4c) = 0;
}

// ---- 0x0067c3b0 : next hint (complete, non-matching) -----------------
// @ 0x0067c3b0
void cUIHints::Next(int a, char b) {
    char* p = (char*)this;
    int** it = *(int***)(p + 0x20);
    int** end = *(int***)(p + 0x24);
    if (it != end) {
        int* e;
        while ((e = *it, *(int*)((char*)e + 8) != a)) {
            ++it;
            if (it == end) return;
        }
        if (b == 0) {
            if (*(int*)((char*)e + 0x90) == 0) return;
            if ((int*)*(int*)(p + 0x4c) == e) UpdateHints(0, 1);
            *(int*)((char*)e + 0x90) = 0;
        } else {
            if (*(int*)((char*)e + 0x90) == 1) return;
            *(int*)((char*)e + 0x90) = 1;
        }
        *(int*)((char*)e + 0x94) = 0;
    }
}

// ---- 0x0067c420 : cUIHints::SetFlag ----------------------------------
// @ 0x0067c420
void cUIHints::SetFlag(char a, int b) {
    if (*(unsigned*)((char*)this + 0x48) > 2) return;
    if (a != 0) {
        *(int*)((char*)this + 0x48) = 0;
    } else {
        *(int*)((char*)this + 0x48) = 2;
        UpdateHints(0, (char)b);
    }
}
