// SPUIHelpers rollover-frame helpers and supporting UI utilities.
// Reconstructed from the retail disassembly + Ghidra decompile.  The window interface is a
// stub: only the vtable slot offsets that the original calls are meaningful.  Every call
// target/global is a byte-masked relocation, so exact callee identities are not required for
// the byte-exact functions.
#include "types.h"

// ------------------------------------------------------------------ external helpers (stubs)
struct IWin;
struct Mat;
extern "C" void* op_new(unsigned size, int align, const char* name, void* alloc);   // 0x009512d0 (cdecl)
extern "C" void* GetUIAllocator();                                                   // 0x009512c0
struct WinButtonCtor { void* ctor(); };                                              // 0x00966f90 (thiscall, returns this)
extern "C" void  SetWindowImage(IWin* w, const void* image, int state);              // 0x00807bb0
struct Pt;
extern "C" void  FUN_00806610(void* w, int a, int b, const Pt* v, void* c);          // 0x00806610 (cdecl)
extern "C" void  VisitWindowTreeDepthFirst(IWin* w, void* cb, void* user);
extern "C" void  WindowAreaCB(IWin* w, void* user);
extern "C" Mat*  SetWindowSPShader(IWin* w, int shader, int zero);
extern "C" void  UpdateRolloverFrame(IWin* w, float a, float b, float c, float d, int e, float f);
extern "C" void  AnchorWindowToScreen(float* rect, IWin* child, int flags, IWin* parent);  // 0x008070d0
extern "C" void  AnchorWindowToWindow(IWin* parent, IWin* child, int flags, int zero);  // 0x00807340
extern "C" void  GetMainWindowArea(float* out);  // 0x00805ea0
extern "C" IWin* FindWindowByID(void* layout, uint32_t id, int recurse);
extern "C" void  DestroyRolloverFrame(IWin* w);   // 0x008074a0
extern "C" bool  UpdateRolloverFrameB(IWin* w, float a, float b, float c, float d, int e, float f);   // 0x00808d40 (returns al)

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
struct LayoutTemp {                                  // temporary layout description, 0x18 bytes
    LayoutTemp();                                    // 0x00810000 (returns this)
    ~LayoutTemp();                                   // 0x00811fe0
    int pad[6];
};
struct cSPUILayout {
    cSPUILayout(const LayoutTemp& x);                // 0x00810020
    virtual void lv0();
    int pad[5];
    bool Init(const wchar_t* name, int group, bool b, unsigned id);   // 0x00812160 (thiscall)
    IWin* FindWindowByID(uint32_t id, int recurse);  // 0x008105b0 (thiscall)
};
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
    T** AsPPTypeParam() { *this = 0; return &p; }
};
extern float gRolloverMinScale;                    // 0x01485378 (reads 0.0)

// A generic UTFWin window / layout.  Only slots actually referenced below are typed; the rest
// are placeholders so the vtable indices line up.
struct IWin {
    virtual void AddRef(); virtual void Release(); virtual void s02(); virtual void* Cast(unsigned iid);   // +0x0c (index 3)
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
    virtual IWin* GetDrawable();                    // +0xa8 (index 42)
    virtual void FnAc(bool a);                      // +0xac (index 43)
    virtual void s44();
    virtual IWinOwner* GetOwnerByID(uint32_t id);   // +0xb4 (index 45)
    virtual void FnB8(unsigned id, void* obj);      // +0xb8 (index 46)
    virtual void s47();
    virtual void FnC0(void* pt, Pt p);              // +0xc0 (index 48)
    virtual void FnC4(void* pt, Pt p);              // +0xc4 (index 49)
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
// @ 0x008087f0
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
// SPUIHelpers::SetButtonImages: creates a WinButton, assigns the 8 state images from an array of
// resource keys (a 9th key, at +0x60, names a button-drawable resource that is attached to the
// button's drawable), then forwards the remaining layout parameters.
struct ResKey { unsigned instance, type, group; };
struct ButtonImages { ResKey state[8]; ResKey extra; };

struct IRefObject {                                  // refcounted resource returned by the resource manager
    virtual int AddRef();
    virtual int Release();
    virtual void r2();
    virtual void* Cast(unsigned iid);                // +0x0c
};
struct IButtonDrawable {                             // what IWin::GetDrawable()->Cast(0x103c1908) returns
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12();
    virtual void SetResource(void* res);             // +0x34
};
struct IResourceManager {
    virtual void m0(); virtual void m1(); virtual void m2();
    virtual bool GetResource(const ResKey* key, IRefObject** out, int a, int b, int c, int d);   // +0x0c
};
extern "C" IResourceManager* GetResourceManager();   // 0x008de1a0

// @ 0x00808930
IWin* SPUIHelpers_SetButtonImages(ButtonImages* images, int a, int b, Pt v, void* c)
{
    if (images == 0)
        return 0;

    void* mem = op_new(0x888, 4, "UI/WinButton", GetUIAllocator());
    IWin* btn;
    void* o;
    if (mem != 0 && (o = ((WinButtonCtor*)mem)->ctor()) != 0)
        btn = (IWin*)((char*)o + 0x20c);
    else
        btn = 0;
    IWin* area = (IWin*)btn->GetArea();
    SetWindowImage(area, &images->state[0], 0);
    SetWindowImage(area, &images->state[1], 1);
    SetWindowImage(area, &images->state[2], 2);
    SetWindowImage(area, &images->state[3], 3);
    SetWindowImage(area, &images->state[4], 4);
    SetWindowImage(area, &images->state[5], 5);
    SetWindowImage(area, &images->state[6], 6);
    SetWindowImage(area, &images->state[7], 7);
    FUN_00806610(btn, a, b, &v, c);

    IWin* drawable = area->GetDrawable();
    if (drawable != 0) {
        IButtonDrawable* bd = (IButtonDrawable*)drawable->Cast(0x103c1908);
        if (bd != 0) {
            ResKey key = images->extra;
            key.type = 0x19aef76;
            Ref<IRefObject> res;
            IResourceManager* rm = GetResourceManager();
            if (rm->GetResource(&key, res.AsPPTypeParam(), 0, 0, 0, 0) && res.p != 0) {
                void* r = res.p->Cast(0xf074e1c8);
                if (r != 0)
                    bd->SetResource(r);
            }
        }
    }
    return btn;
}

// ------------------------------------------------------------------ 0x00808ad0
// @ 0x00808ad0
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
// SPUIHelpers rollover-frame placement: positions window `w` next to `anchor` (the window it
// describes). The requested top-left is the anchor's bounding screen rect corner; when the frame
// would run past the right edge of the main window area it is shifted back (never left of 0), and
// when it would leave the top it is moved below the anchor (also when the anchor is in the lower
// half of the main area and `useChildren` is set).
extern "C" int ExpandRect(int* a, float* b);   // 0x00805660 (visitor callback)

// @ 0x00808b20
void FUN_00808b20(IWin* anchor, IWin* w, char useChildren)
{
    if (anchor == 0 || w == 0)
        return;
    IWin* area = (IWin*)w->GetArea();
    if (area != 0) {

        float M[4];
        GetMainWindowArea(M);
        float R[4];
        FUN_008087f0(R, anchor, useChildren);

        float* p;
        float c[4];
        if (useChildren != 0) {
            float r[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            VisitWindowTreeDepthFirst(w, (void*)&ExpandRect, r);
            c[0] = r[0];
            c[1] = r[1];
            c[2] = r[2];
            c[3] = r[3];
            p = c;
        } else {
            p = w->GetRect();
        }
        float right = (p[2] - p[0]) + R[0];
        float y = (R[1] - (p[3] - p[1])) - 5.0f;
        float x = R[0];
        if (right > M[2]) {
            float* q = M[2] > R[2] ? &R[2] : &M[2];
            x = *q - (right - R[0]);
        } else if (R[0] < 0.0f) {
            x = 0.0f;
        }
        if ((useChildren != 0 && (R[3] + R[1]) * 0.5f < (M[3] + M[1]) * 0.5f) || y < 0.0f)
            y = R[3] + 5.0f;

        Pt in;
        in.x = x;
        in.y = y;
        Pt out;
        area->FnC4(&out, in);
        w->Fn70(out.x, out.y);
    }
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

// @ 0x00808ce0
RolloverFrameLayout::~RolloverFrameLayout()
{
    mLayout.Shutdown(true);
}

// ------------------------------------------------------------------ 0x00808d20
// @ 0x00808d20
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
// @ 0x00809370
void FUN_00809370(IWin* w, float a, float b, int c, float d)
{
    UpdateRolloverFrame(w, a, b, -1.0f, -1.0f, c, d);
}

// ------------------------------------------------------------------ 0x008093b0
// SPUIHelpers::CreateRolloverFrame: loads the boxed rollover layout (UI/RolloverFrameBoxedLayout),
// places the frame with UpdateRolloverFrame, moves the children of its content slot into the
// root window and returns the root window; the content window is returned through `outContent`.
struct RolloverFrameLayoutBase {
    virtual int AddRef();                  // 0x00804910
    virtual int Release();                 // 0x00623070
    virtual ~RolloverFrameLayoutBase();    // 0x008087c0
    virtual void Slot3();                  // 0x008087a0
    int mRefCount;                         // +4
    cSPUILayout mLayout;                   // +8
    int mPad[8];
    RolloverFrameLayoutBase() : mRefCount(0), mLayout(LayoutTemp()) {}
};
struct RolloverFrameBoxedLayout : RolloverFrameLayoutBase {
    virtual ~RolloverFrameBoxedLayout();   // 0x00808ce0
};
void* __cdecl operator_new_f473a0(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);

// @ 0x008093b0
IWin* SPUIHelpers_CreateRolloverFrame(const wchar_t* layoutName, float a, float b, float c, float d,
                                      IWin** outContent, char showAll, int flag, float scale,
                                      unsigned id)
{
    Ref<RolloverFrameBoxedLayout> layout(new ("UI/RolloverFrameBoxedLayout", 0, 0, 0, 0) RolloverFrameBoxedLayout);
    if (layout->mLayout.Init(layoutName, 0x40464100, true, id)
        && layout->mLayout.FindWindowByID(0x4aa0748, 0)
        && layout->mLayout.FindWindowByID(0x4a61af0, 1)
        && layout->mLayout.FindWindowByID(0x4a612b0, 1)) {
        Ref<IWin> root(layout->mLayout.FindWindowByID(0x4aa0748, 0));
        root->FnB8(0x4a61af0, layout);
        if (!UpdateRolloverFrameB(root, a, b, c, d, flag, scale)) {
            DestroyRolloverFrame(root);
            return 0;
        }
        Ref<IWin> frame(layout->mLayout.FindWindowByID(0x4a61af0, 1));
        Ref<IWin> content(layout->mLayout.FindWindowByID(0x4a612b0, 1));
        *outContent = content;
        content->AddRef();
        root->SetVisible(true, false);
        IWin* slot = frame->FnF0(0x4a9c6b8, 1);
        Ref<IWin> next(slot->Fn10C(0));
        while (next) {
            Ref<IWin> child(next);
            next = slot->Fn10C(child);
            slot->Fn108(child);
            root->Fn104(child);
        }
        if (showAll)
            root->SetVisible(true, true);
        content->FnAc(false);
        return root;
    }
    return 0;
}

// ------------------------------------------------------------------ 0x00809670
// Constructor of a list whose nodes (12 bytes) come from a fixed_node_allocator pool: two
// 0x600-byte pools are initialised (a temporary one first, then the allocator's own member from the
// temporary's head) and the list sentinel is linked to itself.
struct FixedPool {
    void* mpHead;
    void* mpPad;
    void* mpNext;
    void* mpCapacity;
    unsigned mnNodeSize;
    void init(void* mem, unsigned size, unsigned nodeSize, unsigned align, unsigned off);   // 0x00921260 (thiscall, ret 0x14)
    void Setup(void* mem) {                // fixed_node_allocator constructor (inlined)
        mpHead = 0;
        init(mem, 0x600, 0xc, 4, 0);
        mpNext = mem;
        mpCapacity = (char*)mem + 0x600;
        mnNodeSize = 0xc;
    }
};
struct FixedNodeList {
    FixedNodeList* mpNext;                 // +0 sentinel
    FixedNodeList* mpPrev;                 // +4
    FixedPool mPool;                       // +8
    char mBuffer[0x600];                   // +0x1c
    FixedNodeList* ctor();
};

// @ 0x00809670
FixedNodeList* FixedNodeList::ctor()
{
    FixedPool tmp;
    tmp.Setup(mBuffer);
    mpNext = 0;
    mpPrev = 0;
    mPool.Setup(tmp.mpHead);
    mpNext = this;
    mpPrev = this;
    return this;
}
