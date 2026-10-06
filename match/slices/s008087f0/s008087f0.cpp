// SPUIHelpers rollover-frame helpers and supporting UI utilities.
// Reconstructed from the retail disassembly + Ghidra decompile.  The window interface is a
// stub: only the vtable slot offsets that the original calls are meaningful.  Every call
// target/global is a byte-masked relocation, so exact callee identities are not required for
// the byte-exact functions.
#include "types.h"

// ------------------------------------------------------------------ external helpers (stubs)
struct IWin;
struct Mat;
extern "C" void* op_new(unsigned size, int align, const char* name, int a);
extern "C" void* WinButton_ctor(void* self);
extern "C" void  SetWindowImage(IWin* w, void* image, int state);
extern "C" void  FUN_00806610(void* w, void* a, void* b, void* c, void* d);
extern "C" void  VisitWindowTreeDepthFirst(IWin* w, void* cb, void* user);
extern "C" void  WindowAreaCB(IWin* w, void* user);
extern "C" Mat*  SetWindowSPShader(IWin* w, int shader, int zero);
extern "C" void  UpdateRolloverFrame(IWin* w, float a, float b, float c, float d, int e, float f);
extern "C" void  AnchorWindowToScreen(float* rect, IWin* child, IWin* parent);
extern "C" void  AnchorWindowToWindow(IWin* parent, IWin* child, int flags, int zero);
extern "C" void  GetMainWindowArea(float* out);
extern "C" IWin* FindWindowByID(void* layout, uint32_t id, int recurse);
extern "C" void  DestroyRolloverFrame(IWin* w);

// ------------------------------------------------------------------ UI stub types
struct Mat {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    void UseMaterial(int x);                       // FUN_0082f9a0 (thiscall)
};

struct MatContainer {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual Mat* FindMaterial(uint32_t id);        // vtable +0x0c
};

struct Pt { float x, y; };

// A generic UTFWin window / layout.  Only slots actually referenced below are typed; the rest
// are placeholders so the vtable indices line up.
struct IWin {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void* GetArea();                       // +0x10 (index 4)
    virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual float* GetRect();                      // +0x38 (index 14)
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual MatContainer* GetSPMaterial();         // +0x4c (index 19)
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25();
    virtual void Fn68(float a, float b);           // +0x68 (index 26)
    virtual void s27();
    virtual void Fn70(float a, float b);           // +0x70 (index 28)
    virtual void s29(); virtual void s30();
    virtual void SetVisible(bool a, bool b);       // +0x7c (index 31)
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41();
    virtual void FnAc(bool a);                      // +0xac (index 43)
    virtual void s44(); virtual void s45();
    virtual IWin* FnB4();                           // +0xb4 (index 45)
    virtual void FnB8(void* a, int b);              // +0xb8 (index 46)
    virtual void s47();
    virtual void FnC0(void* pt, Pt p);              // +0xc0 (index 48)
    virtual void FnC4(void* pt, float x, float y);  // +0xc4 (index 49)
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59();
    virtual IWin* FnF0(int a, int b);               // +0xf0 (index 60)
    virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
    virtual IWin* Fn104(void* a);                   // +0x104 (index 65)
    virtual void Fn108(void* a);                    // +0x108 (index 66)
    virtual IWin* Fn10C(void* a);                   // +0x10c (index 67)
};

// ------------------------------------------------------------------ 0x008087f0
// Computes the bounding screen rectangle of a window.  If useChildren, the union of the
// window's children (via the depth-first visitor) is used, otherwise the two opposite corners
// are obtained by mapping (0,0) and (area width,height) through the window.
void FUN_008087f0(float* out, IWin* w, char useChildren)
{
    if (useChildren != 0) {
        float r[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        VisitWindowTreeDepthFirst(w, (void*)&WindowAreaCB, r);
        out[0] = r[0];
        out[1] = r[1];
        out[2] = r[2];
        out[3] = r[3];
    } else {
        float* p = w->GetRect();
        float a[4];
        a[0] = p[0]; a[1] = p[1]; a[2] = p[2]; a[3] = p[3];
        Pt q0;
        w->FnC0(&q0, Pt());
        Pt in;
        in.x = a[2] - a[0];
        in.y = a[3] - a[1];
        Pt q1;
        w->FnC0(&q1, in);
        out[0] = q0.x;
        out[1] = q0.y;
        out[2] = q1.x;
        out[3] = q1.y;
    }
}

// ------------------------------------------------------------------ 0x00808930
// Creates a WinButton, assigns 8 image states from an image array, copies the remaining
// parameters into it and forwards the requested resource object.  Partial.
void* FUN_00808930(void* images, void* a, void* b, void* c, void* d)
{
    if (images == 0)
        return 0;

    void* alloc = op_new(0x888, 4, "UI/WinButton", 0);
    IWin* wb = 0;
    if (alloc != 0) {
        wb = (IWin*)WinButton_ctor(alloc);
        if (wb != 0)
            wb = (IWin*)((char*)wb + 0x20c);
    }
    if (wb == 0)
        return 0;

    SetWindowImage(wb, images, 0);
    SetWindowImage(wb, (char*)images + 0xc, 1);
    SetWindowImage(wb, (char*)images + 0x18, 2);
    SetWindowImage(wb, (char*)images + 0x24, 3);
    SetWindowImage(wb, (char*)images + 0x30, 4);
    SetWindowImage(wb, (char*)images + 0x3c, 5);
    SetWindowImage(wb, (char*)images + 0x48, 6);
    SetWindowImage(wb, (char*)images + 0x54, 7);

    FUN_00806610(wb, a, b, c, d);
    IWin* res = wb->Fn104(0);
    if (res != 0 && res->Fn10C((void*)0x103c1908) != 0) {
        // attach the found sub-object to the button
    }
    return wb;
}

// ------------------------------------------------------------------ 0x00808ad0
void SPUIHelpers_SetWindowSPMaterial(IWin* w, int material, int shader)
{
    MatContainer* c = w->GetSPMaterial();
    Mat* m;
    if (c != 0 && (m = c->FindMaterial(0x5234b49)) != 0) {
        // use the existing material
    } else {
        m = (Mat*)SetWindowSPShader(w, shader, 0);
    }
    m->UseMaterial(material);
}

// ------------------------------------------------------------------ 0x00808b20
// Complex rollover-frame placement: computes the requested rect and, when the frame would
// leave the screen, clamps it and shifts the companion label.  Partial.
void FUN_00808b20(int* p1, IWin* w, char useChildren)
{
    if (p1 == 0 || w == 0)
        return;
    IWin* child = (IWin*)w->GetArea();
    if (child == 0)
        return;

    float main[4];
    GetMainWindowArea(main);
    float rect[4];
    FUN_008087f0(rect, (IWin*)p1, useChildren);

    float frame[4];
    if (useChildren) {
        frame[0] = 0.0f; frame[1] = 0.0f; frame[2] = 0.0f; frame[3] = 0.0f;
        VisitWindowTreeDepthFirst(w, (void*)&WindowAreaCB, frame);
    } else {
        float* r = w->GetRect();
        frame[0] = r[0]; frame[1] = r[1]; frame[2] = r[2]; frame[3] = r[3];
    }
    (void)main;
    (void)frame;
}

// ------------------------------------------------------------------ 0x00808ce0
struct cSPUILayoutStub {
    void Shutdown(bool b);
    ~cSPUILayoutStub();
};

struct EditorResourceBase {
    int mPad;
    virtual ~EditorResourceBase();
};

struct RolloverFrameLayout : EditorResourceBase {
    cSPUILayoutStub mLayout;       // +8
    virtual ~RolloverFrameLayout();
};

RolloverFrameLayout::~RolloverFrameLayout()
{
    mLayout.Shutdown(true);
}

// ------------------------------------------------------------------ 0x00808d20
float* SPUIHelpers_GetBoundingScreenRect(float* out, IWin* w, char useChildren)
{
    FUN_008087f0(out, w, useChildren);
    return out;
}

// ------------------------------------------------------------------ 0x00808d40
// Places the boxed rollover frame (9-slice) around a window; returns true when it was updated.
// Large function; partial reconstruction of the placement loop.
bool SPUIHelpers_UpdateRolloverFrame(IWin* w, float f2, float f3, float f4, float f5, int b7, float f8)
{
    if (w == 0)
        return false;
    IWin* frame = (IWin*)w->FnB4();
    if (frame == 0)
        return false;
    IWin* box = (IWin*)frame->Fn10C((void*)0x4a61af0);
    if (box == 0)
        return false;
    (void)f2; (void)f3; (void)f4; (void)f5; (void)b7; (void)f8;
    return true;
}

// ------------------------------------------------------------------ 0x00809370
void FUN_00809370(IWin* w, float a, float b, int c, float d)
{
    UpdateRolloverFrame(w, a, b, -1.0f, -1.0f, c, d);
}

// ------------------------------------------------------------------ 0x008093b0
// Creates the boxed rollover layout, initialises it and places it.  Partial.
IWin* SPUIHelpers_CreateRolloverFrame(void* p1, void* p2, void* p3, void** p4,
                                      void* p5, void* p6, void* p7, void* p8,
                                      void* p9, void* p10)
{
    void* mem = op_new(0x40, 4, "UI/RolloverFrameBoxedLayout", 0);
    if (mem == 0)
        return 0;
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7; (void)p8; (void)p9; (void)p10;
    return (IWin*)mem;
}

// ------------------------------------------------------------------ 0x00809670
// Initialises a fixed_node_pool-backed list (two inline 0x600-byte node buffers).
// Partial: the eastl template instantiation is not reproduced.
void* FUN_00809670(void* self)
{
    return self;
}
