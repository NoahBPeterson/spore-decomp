#include "types.h"

// Slice s005dec10: SP::cSPEditorUI dialog/save helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.

struct Layout { void* FindWindowByID(int, int); char pad[0x18]; };
struct Widget {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual char Slot10();         // +0x28
};
__forceinline Widget* FindWindowRaw(void* base, int id)
{
    Widget* w = (Widget*)((Layout*)((char*)base + 0x14))->FindWindowByID(id, 1);
    if (!w)
        w = (Widget*)((Layout*)((char*)base + 0x2c))->FindWindowByID(id, 1);
    return w;
}
void __cdecl FUN_004a88d0(int);

// ---------------------------------------------------------------------------------------------
struct EditorFrame {
    char pad[0xcc];
    int mcc;              // +0xcc
    void FUN_005df470(int a, int b);
    void FUN_005df8d0();
};
// @ 0x005df8d0
void EditorFrame::FUN_005df8d0()
{
    mcc = 0x103;
    FUN_005df470(0x103, 1);
}

// ---------------------------------------------------------------------------------------------
struct DialogTarget { void DoDialogEnd(int code); };
struct EditorFrame2 {
    char pad[4];
    DialogTarget* mpTarget;   // +0x04
    void FUN_005dfb30(int a, int b);
};
// @ 0x005dfb30
void EditorFrame2::FUN_005dfb30(int a, int b)
{
    mpTarget->DoDialogEnd(b);
}

// ---------------------------------------------------------------------------------------------
struct EditorUI2 {
    char pad[0x5c];
    void* m5c;                // +0x5c
    char pad60[0x18];
    void* m78;                // +0x78
    char pad7c[0x50];
    int mcc;                  // +0xcc
    void FUN_005df470(int a, int b);
    void DoSaveAndExit();
};
// @ 0x005dfb40  SP::cSPEditorUI::DoSaveAndExit (complete; see nonmatching.txt)
void EditorUI2::DoSaveAndExit()
{
    void* a = m5c;
    char* b = *(char**)((char*)a + 0x7c);
    char* c = *(char**)(b + 0xc);
    if (c[0x44]) {
        void* base = *(void**)((char*)a + 0x78);
        Widget* w = FindWindowRaw(base, 0x3f67620);
        if ((w->Slot10() & 1) != 0)
            return;
    }
    FUN_004a88d0(0xf515d2c3);
    mcc = 0x102;
    FUN_005df470(0x102, 1);
}

// ---------------------------------------------------------------------------------------------
// Not reconstructed (large /O2 dialog code).  See partial.txt.

// @ 0x005dec10
void FUN_005dec10(void* self, int a) { (void)self; (void)a; }

// @ 0x005dee70
int FUN_005dee70(void* self, int msg, int data) { (void)self; (void)msg; (void)data; return 0; }

// @ 0x005def30
void FUN_005def30(void* self, int code) { (void)self; (void)code; }

// @ 0x005df470
void FUN_005df470(void* self, int a, int b) { (void)self; (void)a; (void)b; }

// @ 0x005df8f0
void FUN_005df8f0(void* self, int a) { (void)self; (void)a; }
