// Slice s00967d40 -- EA::UTFWinControls::WinComboBox and its drawables (0x00967d40..0x00968c86).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (UTFWin UI module: no /EHsc)
#include "types.h"

// ---------------------------------------------------------------- vtable dispatch helpers
// A virtual call in the original is "load the object's vptr, load the slot, call it" with `this`
// in ecx and the arguments on the stack.  __fastcall with a dummy second parameter gives exactly
// that ABI (ecx = this, edx = dummy, the rest pushed), without needing an interface declaration.
typedef void  (__fastcall* F0)(void*, void*);typedef void  (__fastcall* F1)(void*, void*, int);
typedef void  (__fastcall* F2)(void*, void*, int, int);
typedef void  (__fastcall* F3)(void*, void*, int, int, int);
typedef void  (__fastcall* FF1)(void*, void*, float);
typedef void  (__fastcall* FF4)(void*, void*, float, float, float, float);
typedef void  (__fastcall* FP)(void*, void*, void*);
typedef void* (__fastcall* P0)(void*, void*);
typedef void* (__fastcall* P1)(void*, void*, uint32_t);
typedef void* (__fastcall* PP)(void*, void*, void*);
typedef int   (__fastcall* I2)(void*, void*, int, int);
typedef int   (__fastcall* I4)(void*, void*, int, int, int, int);
typedef int   (__fastcall* IP)(void*, void*, void*);
typedef int   (__fastcall* IPP)(void*, void*, void*, void*);

#define VS(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
#define VSO(p, off) (*(void**)((char*)(p) + (off)))

// An object whose slot 0xc is "void* GetProp(u32 id)" -- a plain __thiscall virtual call
// (ecx = this, the id pushed), which is what the original emits here.
struct IWinPropA {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* GetProp(uint32_t id);   // +0x0c
};

// A view of the IWindow vtable: only the slots this slice calls are named; the rest are
// placeholders that fix the layout.  A virtual call emits exactly "ecx = this, args pushed,
// call [vptr+slot]" -- no dummy edx register, which the original does not have.
struct IWnd {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual int GetState(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30();
    virtual void OnPropValue(int, int);   // +0x7c
    virtual void d32(); virtual void d33(); virtual void d34();
    virtual void SetAlignment(int);       // +0x8c
    virtual void Update();                // +0x90
    virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40();
    virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
    virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48();
    virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52();
    virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56();
    virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60();
    virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64();
    virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68();
    virtual void HandleMsg(void* msg);    // +0x114
};

// ---------------------------------------------------------------- retail WinComboBox layout
// Member offsets read straight from the disassembly (the 2008 dev PDB drifted); `this` is the
// real object base.  Fields named by their offset.
struct WC {
    uint32_t vptr0;              // +0x000 (Window primary vtable)
    uint32_t vptr1;              // +0x004 (IWindow subobject vtable)
    uint32_t pad_008[0xb];       // +0x008..0x033
    void*    p034;               // +0x034
    void*    p038;               // +0x038
    uint32_t pad_03c[0x11];      // +0x03c..0x07f
    void*    p080;               // +0x080
    void*    p084;               // +0x084
    float    f088;               // +0x088
    float    f08c;               // +0x08c
    float    f090;               // +0x090
    float    f094;               // +0x094
    uint32_t pad_098[0xa];       // +0x098..0x0bf
    uint32_t u0c0;               // +0x0c0
    uint32_t pad_0c4[0x45];      // +0x0c4..0x1d7
    int32_t  i1d8;               // +0x1d8
    int32_t  i1dc;               // +0x1dc
    void*    p1e0;               // +0x1e0 (IDrawable*)
    uint32_t pad_1e4[0xb];       // +0x1e4..0x20f
    int32_t  i210;               // +0x210
    int32_t  i214;               // +0x214
    int32_t  i218;               // +0x218
    int32_t  i21c;               // +0x21c
    uint32_t u220;               // +0x220 (mnColor[0])
    uint32_t u224;               // +0x224
    uint32_t u228;               // +0x228
    uint32_t u22c;               // +0x22c
    uint32_t u230;               // +0x230
    uint32_t u234;               // +0x234
    uint32_t u238;               // +0x238
    uint32_t u23c;               // +0x23c
    int32_t  i240;               // +0x240
    uint8_t  b244;               // +0x244
    uint8_t  b245;               // +0x245
    uint16_t pad_246;            // +0x246
    void*    p248;               // +0x248 (mValueList begin)
    void*    p24c;               // +0x24c (mValueList end)
    uint32_t pad_250;            // +0x250
    uint32_t pad_254;            // +0x254
    uint32_t pad_258;            // +0x258
    void*    p25c;               // +0x25c
    float    f260, f264, f268, f26c;   // +0x260 mrComponentArea[0]
    float    f270, f274, f278, f27c;   // +0x270 mrComponentArea[1]
    float    f280, f284, f288, f28c;   // +0x280 mrComponentArea[2]

    void OnPropValue(uint32_t value);                  // 0x00967d40
    void RenderComponent(void* pRenderCtx, uint32_t component);  // 0x00968230
    int  PickComponent(float x, float y);              // 0x00968350
    void Refresh();                                    // 0x00968400
    void ShowListBox();                                // 0x009686b0
};

// `this` of this group points at real+0x20c (the IWinComboBox subobject).
struct WCB {
    void OnModalWindowEnd(void* pModal);               // 0x00967d80
    void SetColor(uint32_t index, uint32_t color);     // 0x00967e20
    uint32_t GetColor(uint32_t index);                 // 0x00967e40
    void SetAlignment(uint32_t value);                 // 0x00967e80
    void* GetDrawable();                               // 0x00968210
    uint32_t GetValue(uint32_t index);                 // 0x00968c10
    void SetCurrentSelection(int index, uint8_t notify);  // 0x00968c50
};

static __forceinline WC* Real(void* p) { return (WC*)((char*)p - 0x20c); }

// ---------------------------------------------------------------- allocator / new (UTFWin)
void* GetUTFWinAllocator();                                                              // 0x009512c0
void* operator new(unsigned int size, int align, const char* name, void* alloc);          // 0x009512d0
struct WinGrid;
WinGrid* WinGrid_Ctor(void* p);                                                          // 0x009770e0
void* RenderContext_Begin2D(void* renderCtx, int mode);                                   // 0x0095bc10

// ---------------------------------------------------------------- drawables
struct Image { uint32_t pad0[7]; int32_t mSizeX; int32_t mSizeY; };   // +0x1c / +0x20
struct AutoRefCountIface { virtual int AddRef(); virtual int Release(); };

// p1e0 (the IDrawable of this combo box): slot 0x10 renders one component.
struct IDrawable3 {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void Render(void* ctx, void* area, void* info);   // +0x10
};

// The batch object returned by RenderContext_Begin2D.
struct IBatch {
    virtual void d0();
    virtual void Attach(void* p);                             // +0x04
    virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
    virtual void Rect(float x, float y, float w, float h);    // +0x38
};

struct CBD {                                       // ComboBoxDrawable-ish drawable
    uint32_t pad_000[4];                           // +0x00..0x0f
    AutoRefCountIface* mComponentImage[3];         // +0x10

    bool GetNaturalSize(float* out, uint32_t a, uint32_t which);   // 0x00967f00
    void* GetComponentImage(uint32_t index);                       // 0x00967f40
};

struct CBD2 {                                      // `this` = the owning object (array at +4)
    uint32_t pad_00;                               // +0x00
    AutoRefCountIface* mComponentImage[3];         // +0x04
    void SetComponentImage(uint32_t index, AutoRefCountIface* image);   // 0x00967f60
};

// ---------------------------------------------------------------- function bodies
// @ 0x00967d40
void WC::OnPropValue(uint32_t value)
{
    if (b244 != (uint8_t)value) {
        b244 = (uint8_t)value;
        ((IWnd*)((char*)this + 4))->OnPropValue(8, (int)value);
    }
}

// @ 0x00967d80
void WCB::OnModalWindowEnd(void* pModal)
{
    Real(this)->b245 = 0;
    if (pModal) {
        void* p = ((P1)VS(pModal, 0x0c))(pModal, 0, 0xaf1ee902);
        if (p) {
            float f[2];
            if (((IPP)VS(p, 0xa4))(p, 0, &f[0], &f[1])) {
                void* self = (char*)this - 0x20c;
                ((F2)VS(self, 0x44))(self, 0, *(int*)&f[1], 1);
            }
        }
        void* q = ((P0)VS(pModal, 0x10))(pModal, 0);
        if (q) {
            void* r = ((P0)VS(pModal, 0x10))(pModal, 0);
            ((FP)VS(r, 0xe0))(r, 0, pModal);
        }
    }
    void* self = (char*)this - 0x20c;
    Real(this)->i210 = -1;
    Real(this)->i214 = -1;
    ((F0)VS(self, 0x90))(self, 0);
}

// @ 0x00967e20
void WCB::SetColor(uint32_t index, uint32_t color)
{
    if (index < 6)
        *(uint32_t*)((char*)Real(this) + 0x220 + index * 4) = color;
}

// @ 0x00967e40
uint32_t WCB::GetColor(uint32_t index)
{
    if (index < 6)
        return *(uint32_t*)((char*)Real(this) + 0x220 + index * 4);
    return 0;
}

// @ 0x00967e80
void WCB::SetAlignment(uint32_t value)
{
    Real(this)->i240 = (int32_t)value;
    ((IWnd*)Real(this))->SetAlignment(1);
}extern float g_kOneQuarter;                                   // 0x013eb8a0

// @ 0x00967f00
bool CBD::GetNaturalSize(float* out, uint32_t a, uint32_t which)
{
    (void)a;
    if (which != 2)
        return false;
    Image* im = (Image*)mComponentImage[2];
    if (!im)
        return false;
    out[0] = (float)im->mSizeX * g_kOneQuarter;
    out[1] = (float)im->mSizeY;
    return true;
}

// @ 0x00967f40
void* CBD::GetComponentImage(uint32_t index)
{
    if (index < 3)
        return mComponentImage[index];
    return 0;
}

// @ 0x00967f60
void CBD2::SetComponentImage(uint32_t index, AutoRefCountIface* image)
{
    if (index < 3) {
        AutoRefCountIface* old = mComponentImage[index];
        if (old != image) {
            if (old)
                old->Release();
            mComponentImage[index] = image;
            if (image)
                image->AddRef();
        }
    }
}

// @ 0x009680f0
void __cdecl WinComboBox_TransformComponent(void* pDst, void* pFrom, void* pUnused, float* pRect)
{
    (void)pUnused;
    float in0 = pRect[0], in1 = pRect[1], in3 = pRect[3];
    float outA[2];
    ((FP)VS(pFrom, 0xc0))(pFrom, 0, outA);
    float* r = (float*)((PP)VS(pDst, 0xc4))(pDst, 0, &outA[0]);
    float outB[2];
    outB[0] = r[0];
    outB[1] = r[1];
    ((FP)VS(pFrom, 0xc0))(pFrom, 0, outB);
    float* q = (float*)((PP)VS(pDst, 0xc4))(pDst, 0, &outB[0]);
    float* dst = (float*)(uint32_t)in3;
    dst[0] = in0;
    dst[1] = in1;
    dst[2] = q[0];
    dst[3] = q[1];
}

// @ 0x00968210
void* WCB::GetDrawable()
{
    IWinPropA* obj = (IWinPropA*)Real(this)->p1e0;
    if (obj)
        return obj->GetProp(0xef552a8d);
    return 0;
}

// @ 0x00968230
void WC::RenderComponent(void* pRenderCtx, uint32_t component)
{
    if (p1e0) {
        if (component >= 3)
            return;
        struct Info { int state; uint32_t component; void* p1dc; int32_t i1d8; } info;
        info.state = 0;
        info.component = component;
        info.p1dc = (void*)i1dc;
        info.i1d8 = i1d8;
        int flags = ((IWnd*)((char*)this + 4))->GetState();
        if (!(flags & 2))
            info.state = 1;
        else if (i218 == (int)component)
            info.state = 3;
        else if (i214 == (int)component)
            info.state = 2;
        ((IDrawable3*)p1e0)->Render(pRenderCtx, (char*)this + 0x260 + component * 16, &info);
        return;
    }
    if (component != 0)
        return;
    if (!i1dc)
        return;
    IBatch* batch = (IBatch*)RenderContext_Begin2D(pRenderCtx, 0);
    batch->Attach((void*)i1dc);
    batch->Rect(0.0f, 0.0f, f090 - f088, f094 - f08c);
}

// @ 0x00968350
int WC::PickComponent(float x, float y)
{
    if (f280 <= x && f284 <= y && x < f288 && y < f28c)
        return 2;
    if (f270 <= x && f274 <= y && x < f278 && y < f27c)
        return 1;
    if (f260 <= x && f264 <= y && x < f268 && y < f26c)
        return 0;
    return -1;
}

extern float g_kTwoThirds;                                   // 0x01470f1c
extern float g_kHalf;                                        // 0x01471064
extern float g_kOne;                                         // 0x01485720

// @ 0x00968400
void WC::Refresh()
{
    void* drawable = 0;
    if (p1e0)
        drawable = ((P1)VS(p1e0, 0x0c))(p1e0, 0, 0xef552a8d);
    if (!b245 || !drawable)
        return;

    ((F1)VS(this, 0x8c))(this, 0, 0);

    float fPad = (u23c & 1) ? g_kOne : 0.0f;

    float aSize[3][2];
    for (int i = 0; i < 3; ++i) {
        float w, h;
        if (!((I4)VS(p1e0, 0x18))(p1e0, 0, (int)&w, 0, i, 0)) {
            void* wnd = (char*)this + 4;
            float* r = (float*)((P0)VS(wnd, 0x38))(wnd, 0);
            w = r[2] - r[0];
            h = r[3] - r[1];
            if (i == 2) {
                float lim = w * g_kTwoThirds;
                if (!(h > lim))
                    w = h;
            }
        }
        aSize[i][0] = w;
        aSize[i][1] = h;
    }

    if (i240 == 1) {
        float w0 = f090 - f088;
        f280 = w0 - aSize[2][0] - fPad;
        f288 = w0 - aSize[2][0];
        f278 = f094 - f08c;
        float t = (f094 - f08c - aSize[2][1] - fPad * g_kTwoThirds) * g_kHalf + fPad;
        f284 = t;
        f28c = t + aSize[2][1];
        f270 = 0.0f;
    } else {
        f280 = fPad;
        f288 = aSize[2][0] + fPad;
        float t = (f094 - f08c - aSize[2][1] - fPad * g_kTwoThirds) * g_kHalf + fPad;
        f284 = t;
        f28c = t + aSize[2][1];
        f270 = aSize[2][0] + fPad;
        f278 = f090 - f088;
    }
    f274 = 0.0f;
    f27c = f094 - f08c;
    f260 = 0.0f;
    f264 = 0.0f;
    f268 = aSize[0][0];
    f26c = aSize[0][1];
    ((F0)VS(this, 0x90))(this, 0);
}

// @ 0x009686b0
void WC::ShowListBox()
{
    if (p248 == p24c)
        return;
    if (!p034)
        return;
    if (!((P0)VS(p034, 4))(p034, 0))
        return;

    void* grid = operator new(0xa90, 8, "UTFWin/WinGrid", GetUTFWinAllocator());
    if (grid)
        grid = WinGrid_Ctor(grid);
    void* gridIface = grid ? (char*)grid + 0x20c : 0;

    ((F0)VSO((char*)this + 4, 0x114))((void*)((char*)this + 4), 0);

    if (!gridIface)
        return;

    static const int kFlags[18] = { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x200, 0x400, 0x800,
                                    0x2000, 0x2000, 0x4000, 0x1000, 0x8000, 0x10000, 0x20000 };
    for (int i = 0; i < 18; ++i) {
        int v = 0;
        if (i == 2 || i == 7 || i == 9 || i == 11 || i == 12)
            v = 1;
        else if (i == 8)
            v = (int)(u23c & 1);
        ((F2)VS(gridIface, 0x2c))(gridIface, 0, kFlags[i], v);
    }

    float one = (u23c & 1) ? 1.0f : 0.0f;
    ((FF4)VS(gridIface, 0x58))(gridIface, 0, one, one, one, one);
    ((FF4)VS(gridIface, 0x60))(gridIface, 0, g_kTwoThirds, g_kTwoThirds, g_kTwoThirds, g_kTwoThirds);
    ((F2)VS(gridIface, 0xbc))(gridIface, 0, 1, 0);
    ((F2)VS(gridIface, 0x98))(gridIface, 0, 1, 1);
    {
        void* wnd = (char*)this + 4;
        float* r = (float*)((P0)VS(wnd, 0x38))(wnd, 0);
        ((FF1)VS(gridIface, 0xe4))(gridIface, 0, r[2] - r[0]);
    }
    if (p25c)
        ((FP)VS(gridIface, 0x208))(gridIface, 0, p25c);
    ((FP)VS(gridIface, 0x34))(gridIface, 0, p25c ? p25c : (void*)0);
    ((F2)VS(gridIface, 0x3c))(gridIface, 0, 0, (int)u220);
    ((F2)VS(gridIface, 0x3c))(gridIface, 0, 1, (int)u224);
    ((F2)VS(gridIface, 0x3c))(gridIface, 0, 5, (int)u22c);
    ((F2)VS(gridIface, 0x3c))(gridIface, 0, 4, (int)u228);
    ((F2)VS(gridIface, 0x3c))(gridIface, 0, 7, (int)u234);
    ((F2)VS(gridIface, 0x3c))(gridIface, 0, 6, (int)u230);
    {
        void* w2 = ((P0)VS(gridIface, 0x10))(gridIface, 0);
        ((F1)VS(w2, 0xac))(w2, 0, (int)u224);
        ((FP)VS(w2, 0x50))(w2, 0, this);
    }

    uint32_t count = (uint32_t)(((char*)p24c - (char*)p248) >> 4);
    for (uint32_t i = 0; i < count; ++i) {
        void* label = *(void**)((char*)p248 + i * 16);
        ((F3)VS(gridIface, 0x1a4))(gridIface, 0, 0, (int)i, (int)label);
    }

    ((F2)VS(gridIface, 0xa8))(gridIface, 0, 0, i21c);
    {
        void* w3 = ((P0)VS(gridIface, 0x10))(gridIface, 0);
        void* prev = p25c;
        if (((IP)VS(prev, 0xd8))(prev, 0, 0)) {
            float* r1 = (float*)((P0)VS(prev, 0x34))(prev, 0);
            void* parent = p038 ? (char*)p038 + 4 : 0;
            float tmp[4];
            float src[4];
            src[0] = f088; src[1] = f08c; src[2] = f090; src[3] = f094;
            WinComboBox_TransformComponent(tmp, parent, prev, src);
            (void)w3;
        }
    }
}

// @ 0x00968c10
uint32_t WCB::GetValue(uint32_t index)
{
    WC* s = Real(this);
    if (index < (uint32_t)(((char*)s->p24c - (char*)s->p248) >> 4))
        return *(uint32_t*)((char*)s->p248 + index * 16);
    return 0;
}

// @ 0x00968c50
void WCB::SetCurrentSelection(int index, uint8_t notify)
{
    WC* s = Real(this);
    if (index == s->i21c)
        return;
    uint32_t count = (uint32_t)(((char*)s->p24c - (char*)s->p248) >> 4);
    if ((uint32_t)index >= count)
        index = (int)count - 1;
    s->i21c = index;
    if (notify) {
        struct Msg { uint32_t pad0[2]; uint32_t key; void* value; int idx; } msg;
        msg.key = 0x4f5527e8;
        void* p = s->p084;
        if (!p)
            p = s->p080;
        msg.value = p;
        msg.idx = index;
        ((IWnd*)((char*)s + 4))->HandleMsg(&msg);
    }
    ((IWnd*)((char*)s + 4))->Update();
}
