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
extern "C" void  AnchorWindowToScreen(float* rect, IWin* child, int flags, IWin* parent);  // 0x008070d0
extern "C" void  AnchorWindowToWindow(IWin* parent, IWin* child, int flags, int zero);  // 0x00807340
extern "C" void  GetMainWindowArea(float* out);  // 0x00805ea0
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

struct IWinOwner;
struct cSPUILayout { IWin* FindWindowByID(uint32_t id, int recurse); };   // 0x008105b0 (thiscall)
struct IUILayoutHolder {
    virtual void AddRef(); virtual void Release();
    int pad;
    cSPUILayout layout;                            // +8
};
struct IWinOwner {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IUILayoutHolder* GetLayoutHolder(uint32_t id);   // +0x0c
};
template <class T> struct Ref {
    T* p;
    Ref() : p(0) {}
    Ref(T* q) : p(q) { if (p) p->AddRef(); }
    ~Ref() { if (p) p->Release(); }
    Ref& operator=(T* q) {
        if (q != p) { T* old = p; if (q) q->AddRef(); p = q; if (old) old->Release(); }
        return *this;
    }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};
extern float gRolloverMinScale;                    // 0x01485378 (reads 0.0)

// A generic UTFWin window / layout.  Only slots actually referenced below are typed; the rest
// are placeholders so the vtable indices line up.
struct IWin {
    virtual void AddRef(); virtual void Release(); virtual void s02(); virtual void s03();
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
    virtual IWinOwner* GetOwnerByID(uint32_t id);   // +0xb4 (index 45)
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
struct RolloverSlot { int idx; int flags; float fx, fy; };

static __forceinline void AnchorTo(IWin* parent, IWin* child, int f)
{
    AnchorWindowToWindow(parent, child, f, 0);
}

// @ 0x00808D40
bool SPUIHelpers_UpdateRolloverFrame(IWin* w, float p2, float p3, float p4, float p5, bool showAll, float scale)
{
    if (w == 0)
        return false;
    IWinOwner* owner = w->GetOwnerByID(0x4a61af0);
    IUILayoutHolder* h;
    if (owner == 0 || (h = owner->GetLayoutHolder(0x4a61af0)) == 0)
        return false;
    Ref<IUILayoutHolder> holder(h);
    cSPUILayout* lay = &h->layout;

    float rect[4];
    rect[0] = p2 - 0.5f;
    rect[2] = p2 + 0.5f;
    rect[1] = p3 - 0.5f;
    rect[3] = p3 + 0.5f;
    Ref<IWin> win1(lay->FindWindowByID(0x4aa0748, 0));
    win1->Fn68(1.0f, 1.0f);
    AnchorWindowToScreen(rect, win1, 0x300, 0);
    Ref<IWin> win2(lay->FindWindowByID(0x4a61af0, 1));
    Ref<IWin> win3(lay->FindWindowByID(0x4a612b0, 1));

    float A[4];
    float* r2 = win2->GetRect();
    A[0] = r2[0]; A[1] = r2[1]; A[2] = r2[2]; A[3] = r2[3];
    float* r3 = win3->GetRect();
    float b0 = r3[0], b1 = r3[1], b2 = r3[2], b3 = r3[3];
    float dw = 0.0f, dh = 0.0f;
    if (p4 > 0.0f) dw = p4 - (b2 - b0);
    if (p5 > 0.0f) dh = p5 - (b3 - b1);
    win2->Fn68((A[2] - A[0]) + dw, (A[3] - A[1]) + dh);

    float M[4];
    GetMainWindowArea(M);
    win2->FnF0(1, 1)->SetVisible(true, false);
    win2->FnF0(2, 1)->SetVisible(true, false);
    win2->FnF0(3, 1)->SetVisible(true, false);
    win2->FnF0(4, 1)->SetVisible(true, false);
    win2->FnF0(5, 1)->SetVisible(true, false);
    win2->FnF0(6, 1)->SetVisible(true, false);
    win2->FnF0(7, 1)->SetVisible(true, false);
    win2->FnF0(8, 1)->SetVisible(true, false);

    RolloverSlot tbl[8] = {
        { 7, 0x102, -1.0f, 0.0f },
        { 8, 0x22, -0.707107f, 0.707107f },
        { 6, 0x42, -0.707107f, -0.707107f },
        { 1, 0x220, 0.0f, 1.0f },
        { 5, 0x240, 0.0f, -1.0f },
        { 3, 0x104, 1.0f, 0.0f },
        { 2, 0x24, 0.707107f, 0.707107f },
        { 4, 0x44, 0.707107f, -0.707107f },
    };
    Ref<IWin> cur;
    for (int i = 0; i < 8; ++i) {
        cur = win2->FnF0(tbl[i].idx, 1);
        switch (tbl[i].idx) {
        case 3: case 7:
            AnchorTo(win2, cur, 0x900);
            break;
        case 1: case 5:
            AnchorTo(win2, cur, 0x600);
            break;
        default:
            break;
        }
        if (scale > gRolloverMinScale) {
            float x = p4 - scale * tbl[i].fy;
            float y = tbl[i].fx * scale + p5;
            rect[0] = x - 0.5f;
            rect[1] = y - 0.5f;
            rect[2] = x + 0.5f;
            rect[3] = y + 0.5f;
        }
        AnchorWindowToScreen(rect, cur, tbl[i].flags, win2);
        FUN_008087f0(A, win2, 0);
        float r0 = A[0] > M[0] ? M[0] : A[0];
        float r1 = A[1] > M[1] ? M[1] : A[1];
        float r2v = M[2] > A[2] ? M[2] : A[2];
        float r3v = M[3] > A[3] ? M[3] : A[3];
        if (r0 == M[0] && r1 == M[1] && r2v == M[2] && r3v == M[3])
            break;
    }
    if (showAll)
        cur->SetVisible(true, true);
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
