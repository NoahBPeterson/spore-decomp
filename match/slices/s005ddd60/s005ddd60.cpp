#include "types.h"

// Slice s005ddd60: SP::cSPEditorUI (init / update / shutdown / dialog helpers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.

struct Widget {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void* GetChild(int);                 // slot 3  (+0x0c)
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual void SetState(int, int);             // slot 10 (+0x28)
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36();
    virtual void Notify();                       // slot 37 (+0x94)
};
struct Layout { void* FindWindowByID(int, int); char pad[0x18]; };
struct AppMode { void NewModel(int); };
struct EditorUI {
    char pad0[0x14];
    Layout mLayout;      // +0x14
    Layout mCamera;      // +0x2c
    char pad44[0x18];
    AppMode* m5c;        // +0x5c
    void SetMode(int);
    void FUN_005de9e0();
};
__forceinline Widget* FindWindow(EditorUI* p, int id)
{
    Widget* w = (Widget*)p->mLayout.FindWindowByID(id, 1);
    if (!w)
        w = (Widget*)p->mCamera.FindWindowByID(id, 1);
    return w;
}

// @ 0x005de9e0
// Complete; 101 bytes off: cl keeps `this` in edi and w in esi (original reuses esi for
// both, leaving edi for the child widget).  Behaviour identical.
void EditorUI::FUN_005de9e0()
{
    SetMode(0);
    m5c->NewModel(0);
    Widget* w = FindWindow(this, 0xf019c2e7);
    if (w) {
        Widget* p = (Widget*)w->GetChild(0x8ed27e7a);
        p->SetState(4, 1);
        p->SetState(0x20, 1);
        w->Notify();
    }
}

// ---------------------------------------------------------------------------------------------
// Not reconstructed (large /O2 UI code).  See partial.txt.

// @ 0x005ddd60
void FUN_005ddd60(void* self) { (void)self; }

// @ 0x005de450
void FUN_005de450(void* self, int dt) { (void)self; (void)dt; }

// @ 0x005de690
void FUN_005de690(void* self, int a, char b) { (void)self; (void)a; (void)b; }

// @ 0x005de870
void FUN_005de870(void* self) { (void)self; }

// @ 0x005dea60
void FUN_005dea60(void* self) { (void)self; }
