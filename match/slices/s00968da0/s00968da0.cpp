// Slice s00968da0: UTFSpore_Win32/utfwin-combobox.obj -- UTFWin ComboBoxDrawable and
// EA::UTFWinControls::WinComboBox.
//
//   00968da0            UTFWin::IDrawable::Paint / ComboBoxDrawable::CreateRenderables
//   00969000..00969060  UI::ComboBoxDrawable ctor + UTFWinControls BasicFactory::CreateInstance
//   009690c0            WinComboBox::OnRebuild
//   00969360            WinComboBox::FindValue
//   00969450..00969a60  WinComboBox ctor/dtor/CalcSize/SetValue/RemoveValue/AddValue/
//                       InsertValue/RemoveAllValues
//   00969ac0..00969b10  scrollbar-drawable ctor and two tiny property setters
//   00969b90..00969d40  ConsoleWindow::Shutdown / LayoutLine / Draw
//
// Class layouts come straight from this slice's disassembly (offsets given per field).
//
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

// ---------------------------------------------------------------------------
// External helpers (real addresses).
// ---------------------------------------------------------------------------
extern "C" void* f_Begin2D(void* ctx, void* mode);                      // 0x95bc10
extern "C" void  f_DrawStdButton(void* batch, void* a, void* b, unsigned c, unsigned d, float e); // 0x95d780
extern "C" void  f_DrawStdButton1(void* batch, void* a, unsigned c, unsigned d, float e);           // 0x95d780
extern "C" void* f_GetStyleManager(int b);                              // 0x885bd0
extern "C" void* f_GetStyle(void* mgr, unsigned id, void* base);        // 0x894670
extern "C" void  f_Typesetter_ctor(void* self, int a);                  // 0x89d820
extern "C" void  f_LineLayout_ctor(void* self, int a);                  // 0x898bd0
extern "C" void  f_LineLayout_Clear(void* self, int a);                 // 0x89cbc0
extern "C" void* f_LayoutParagraph(void* text, int len, float x, float y, float w, float h,
                                   void* style, void* layout, int flags); // 0x89dc00
extern "C" void  f_LineLayout_dtor(void* self);                         // 0x8323d0
extern "C" void  f_Typesetter_dtor(void* self);                         // 0x89c540
extern "C" void  f_MemsetT(void* dst, int val, uint32_t size);          // 0x11e073e
extern "C" void  f_0096e740(void* a, void* b, void* c, void* d, void* e, void* f, int g); // 0x96e740
extern "C" void  f_RangeInitialize(void* self, const wchar_t* s);       // 0x579a90
extern "C" void  f_StrCopyCtor(void* self, void* src);                  // 0x56e2d0
extern "C" void* f_VecDoInsertValue(void* self, void* pos, void* val);  // 0x554c30
extern "C" void* f_VecInsert(void* self, void* pos, void* val);         // 0x92b750
extern "C" void  f_VecDoDestroyValues(void* begin, void* end);          // 0x84aad0
extern "C" void* f_CopyWStrings(void* dst, void* begin, void* end);     // 0x84ab40
extern "C" void* f_VecErase(void* pos);                                 // 0x92b700
extern "C" void  f_WStringAssign(void* dst, const wchar_t* b, const wchar_t* e); // 0x423650
extern "C" void  f_operator_delete(void* p);                            // 0xf47380
extern "C" void* f_FactoryAllocCtx(void);                               // 0x9512c0
extern "C" void* f_FactoryAlloc(int size, int align, const char* name, void* ctx); // 0x9512d0
extern "C" void  f_operator_delete_array(void* p);                      // 0x951330
extern "C" void  f_00962a10(void* self);                                // base ctor 0x962a10
extern "C" void  f_00962740(void* self);                                // base dtor 0x962740
extern "C" void  f_00968d10(void* self);                                // UI::Drawable dtor 0x968d10
extern "C" void  f_009838a0(void* self);                                // ScrollbarDrawable ctor 0x9838a0

// Globals of this object file.
extern float g_166b1bc;            // 0x166b1bc

// ---------------------------------------------------------------------------
// 0x00969ae0  -- tiny float property setter (clamp to [0,1]).
// ---------------------------------------------------------------------------
// @ 0x00969ae0
void SetComboAlpha(float v)
{
    if (v >= 0.0f && v <= 1.0f)
        g_166b1bc = v;
}

// ---------------------------------------------------------------------------
// 0x00969b10  -- tiny size query.
// ---------------------------------------------------------------------------
// @ 0x00969b10
bool __stdcall GetComboSize(float* out, unsigned a, unsigned b)
{
    if (b == 3) {
        out[0] = 20.0f;
        out[1] = 12.0f;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// UI::ComboBoxDrawable  (0x1c bytes; vptrs at +0, +4, +0xc)
// ---------------------------------------------------------------------------
extern uint8_t g_vtbl_ResourceAsync[];         // 0x13fa72c
extern uint8_t g_vtbl_ComboBoxDrawable0[];     // 0x14416a0
extern uint8_t g_vtbl_ComboBoxDrawable1[];     // 0x1441688
extern uint8_t g_vtbl_ComboBoxDrawable2[];     // 0x1441670

struct ResAsyncBase {
    virtual void r0();
    virtual void r1();
};

struct CbdPart1 : ResAsyncBase {
    int m08;
};

struct CbdPart2 : ResAsyncBase {
};

struct ComboBoxDrawable : ResAsyncBase, CbdPart1, CbdPart2 {
    int m10;
    int m14;
    int m18;

    ComboBoxDrawable();                                    // 0x969000
    static void* __stdcall CreateInstance(void* unused, void* ctx); // 0x969060
};

// @ 0x00969000
ComboBoxDrawable::ComboBoxDrawable()
{
    *(void**)((char*)this + 4) = (void*)g_vtbl_ResourceAsync;
    m08 = 0;
    *(void**)((char*)this + 0xc) = (void*)g_vtbl_ResourceAsync;
    *(void**)((char*)this + 0) = g_vtbl_ComboBoxDrawable0;
    *(void**)((char*)this + 4) = g_vtbl_ComboBoxDrawable1;
    *(void**)((char*)this + 0xc) = g_vtbl_ComboBoxDrawable2;
    m10 = 0;
    m14 = 0;
    m18 = 0;
}

extern const char g_szComboBoxDrawable[];  // "UTFWin/EA::UTFWinControls::ComboBoxDrawable"

// @ 0x00969060
void* __stdcall ComboBoxDrawable::CreateInstance(void* unused, void* ctx)
{
    if (ctx == 0)
        ctx = f_FactoryAllocCtx();
    ComboBoxDrawable* p = (ComboBoxDrawable*)f_FactoryAlloc(0x1c, 4, g_szComboBoxDrawable, ctx);
    if (p) {
        *(void**)((char*)p + 4) = g_vtbl_ResourceAsync;
        p->m08 = 0;
        *(void**)((char*)p + 0xc) = g_vtbl_ResourceAsync;
        *(void**)((char*)p + 0) = g_vtbl_ComboBoxDrawable0;
        *(void**)((char*)p + 4) = g_vtbl_ComboBoxDrawable1;
        *(void**)((char*)p + 0xc) = g_vtbl_ComboBoxDrawable2;
        p->m10 = 0;
        p->m14 = 0;
        p->m18 = 0;
    }
    return p;
}

// ---------------------------------------------------------------------------
// 0x00968da0  -- ComboBoxDrawable::CreateRenderables
// ---------------------------------------------------------------------------
extern "C" void f_BatchSetColor(void* batch, unsigned color);           // vtbl+4
extern "C" void f_BatchDrawSprite(void* batch, void* xform, void* drawable, void* uvs); // vtbl+0x58
extern "C" void f_BatchDrawCmd(void* batch, void* a, void* b, void* c, void* d, void* e); // vtbl+0x3c
extern "C" void f_BatchDrawCmd1(void* batch, void* a, void* b, void* c, void* d); // vtbl+0x3c

// Spritesheet / UV quad used by the "no drawable" branch.
struct UvQuad { float u0; float v; float u1; float w; float x; };

// @ 0x00968da0
bool CreateRenderables(void* self, void* param_2, unsigned* param_3)
{
    void* batch = f_Begin2D(param_2, 0);
    f_BatchSetColor(batch, 0xffffffff);

    int mode = param_3[1] - 1;
    void* draw = *(void**)((char*)self + mode * 4 + 0x14);

    if (mode == 0) {
        if (draw != 0) {
            f_BatchDrawCmd1(batch, *(void**)((char*)param_2 + 0x0),
                            *(void**)((char*)param_2 + 0x4), draw, 0);
            return true;
        }
        f_DrawStdButton1(batch, param_2, param_3[2], *param_3 & 0xf, 2.0f);
        return true;
    }
    if (mode != 1)
        return true;

    if (draw != 0) {
        unsigned flags = *param_3;
        float f = 0.0f;
        switch (flags & 7) {
        case 0:  f = (flags & 8) ? 0.75f : 0.25f; break;
        case 1:  f = 0.0f;  break;
        case 2:  f = 0.5f;  break;
        case 3:  f = 0.75f; break;
        }
        UvQuad uv;
        uv.u0 = f;
        uv.v  = 0.0f;
        uv.u1 = f + 0.25f;
        uv.w  = 1.0f;
        uv.x  = 0.0f;
        f_BatchDrawSprite(batch, param_2, draw, &uv);
        return true;
    }

    unsigned flags = *param_3;
    f_DrawStdButton1(batch, param_2, param_3[2], flags & 0xf, 1.0f);
    f_BatchSetColor(batch, (flags & 7) == 1 ? 0xffc0c0c0 : 0xff000000);

    const float* rc = (const float*)param_2;   // clip rect / xform blob
    float x0 = rc[0];
    float y0 = rc[1];
    float x1 = rc[2];
    float y1 = rc[3];
    float dx = x1 - x0;
    float dy = y1 - y0;
    float t  = (flags & 3) == 3 ? 1.0f : 0.0f;

    float a9  = dx * 0.2857143f;
    float a10 = dy * 0.2857143f;
    float midx = (x1 - x0) * 0.5f + x0;
    float dx2 = dx * 0.5f;

    float p[8];
    p[0] = x0 + 0.0f;
    p[1] = y0 + 0.0f;
    p[2] = midx + t;
    p[3] = y1 - dy + t;
    p[4] = x1 - dx + t;
    p[5] = y0 + dx2 + 0.0f;
    p[6] = y0 + 0.0f;
    p[7] = x0 + 0.0f;

    void* tmp[3];
    f_BatchDrawCmd(batch, &p[1], &p[5], &p[2], &p[3], &p[4]);
    (void)a9; (void)a10; (void)tmp;
    return true;
}

// ---------------------------------------------------------------------------
// 0x009690c0  -- WinComboBox::OnRebuild  (large object, layout from disasm)
// ---------------------------------------------------------------------------
extern "C" void* f_StyleManager_Get(int b);                                 // 0x885bd0
extern "C" void* f_StyleManager_GetStyle(void* mgr, unsigned id, void* base); // 0x894670
extern "C" void  f_Typesetter_ctor2(void* self, int a);                     // 0x89d820
extern "C" void  f_LineLayout_ctor3(void* self);                            // 0x898bd0
extern "C" void  f_LineLayout_Clear4(void* self, int a);                    // 0x89cbc0
extern "C" void* f_LayoutParagraph5(void* text, int len, float x, float y,
                                    float w, float h, void* style, void* ll, int flags); // 0x89dc00
extern "C" void  f_LineLayout_dtor6(void* self);                            // 0x8323d0
extern "C" void  f_Typesetter_dtor7(void* self);                            // 0x89c540
extern "C" void  f_0096e740_2(void* a, void* b, void* c, void* d, void* e, void* f, int g); // 0x96e740

// Virtual-slot wrappers (offsets are relative to the object's vftable).
struct IRefCounted {                              // minimal COM shape (vtable slots)
    virtual void slot0();
    virtual void Release();                       // slot 1 (vtbl+4)
};
struct CustomWindowBase { void Ctor(); };       // 0x962a10  CustomWindow::CustomWindow
struct DropShadowDesc   { void SetMode(int); }; // 0x830150  cDropShadowDescriptor::SetMode

struct WinComboBox {
    // Generic virtual slots used by this slice; concrete offsets are modelled
    // with byte arithmetic below because the class hierarchy is only known
    // partially (see disassembly notes).
    char _pad[0x300];

    bool OnRebuild(void* ctx);      // 0x9690c0
    unsigned FindValue(const wchar_t* s);   // 0x969360
    WinComboBox();                  // 0x969450
    ~WinComboBox();                 // 0x9695d0
    bool CalcSize(void* unused, float* out);    // 0x969650
    bool SetValue(unsigned idx, const wchar_t* s);   // 0x969870
    bool RemoveValue(unsigned idx); // 0x969920
    void AddValue(const wchar_t* s);        // 0x969950
    bool InsertValue(unsigned idx, const wchar_t* s); // 0x9699d0
    void RemoveAllValues();         // 0x969a60
};

// The value list at +0x3c is an eastl::vector<sp_vector_allocator> of 16-byte
// wstring objects; only size()/data() are needed here.
struct WString {
    void assign(const wchar_t* first, const wchar_t* last);   // 0x423650
    void RangeInitialize(const wchar_t* s);                   // 0x579a90
    void CopyCtor(WString* src);                              // 0x56e2d0
    int  length_bytes() const;                                // sizeof data area
};

struct WStringVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* erase(void* pos);                 // 0x92b700
    void* insert(void* pos, void* val);     // 0x92b750
    void* DoInsertValue(void* pos, void* val);   // 0x554c30
    void  DoDestroyValues(void* begin, void* end); // 0x84aad0
};

extern "C" void f_009690c0_virt(void* self, void* ctx);  // vtbl+0x98
extern "C" void f_00963740(void* self);                  // 0x963740

extern uint8_t g_vtbl_WinComboBox0[];          // 0x1441890
extern uint8_t g_vtbl_WinComboBox1[];          // 0x1441770
extern uint8_t g_vtbl_WinComboBox2[];          // 0x1440fe8
extern uint8_t g_vtbl_WinComboBox3[];          // 0x1441700
extern uint8_t g_vtbl_WinComboBox4[];          // 0x14416f4
extern uint8_t g_vtbl_GmeEditorResBase[];      // 0x13eb938
extern uint8_t g_vtbl_ScrollbarDrawable0[];    // 0x1441a44
extern uint8_t g_vtbl_ScrollbarDrawable1[];    // 0x144485c
extern uint8_t g_vtbl_ScrollbarDrawable2[];    // 0x1441a2c

// @ 0x009690c0
bool WinComboBox::OnRebuild(void* ctx)
{
    char* self = (char*)this;
    // (**(code**)(*this + 0x98))(ctx, 0) and (.. , 1)
    void** vt = *(void***)self;
    ((void (*)(void*, void*, int))vt[0x98 / 4])(self, ctx, 0);
    ((void (*)(void*, void*, int))vt[0x98 / 4])(self, ctx, 1);

    if ((*(unsigned char*)(self + 0x23c) & 1) != 0 &&
        (*(int*)(self + 0x218) != -1 || *(int*)(self + 0x214) != -1)) {
        void* batch = f_Begin2D(ctx, 0);
        void** bt = *(void***)batch;
        ((void (*)(void*, unsigned))bt[1])(batch, 0xff000000);
        float y0 = 0.0f;
        float x0 = 0.0f;
        float w  = *(float*)(self + 0x94) - *(float*)(self + 0x8c);
        float h  = *(float*)(self + 0x90) - *(float*)(self + 0x88);
        ((void (*)(void*, float, float, float, float, float))bt[0x1c / 4])
            (batch, x0, y0, w, h, 1.0f);
    }

    int idx = *(int*)(self + 0x21c);
    unsigned count = ((*(int*)(self + 0x24c) - *(int*)(self + 0x248)) >> 4);
    bool ok = true;
    if ((unsigned)idx < count) {
        char* entry = (char*)*(void**)(self + 0x248) + idx * 16;
        if (*(void**)entry != *(void**)(entry + 4)) {
            void* mgr = f_GetStyleManager(1);
            if (mgr) {
                void* style = f_GetStyle(mgr, *(unsigned*)(self + 0xc0), 0);
                if (style) {
                    unsigned saved = *(unsigned*)((char*)style + 0x224);
                    *(unsigned*)((char*)style + 0x224) = *(unsigned*)(self + 0x220);

                    float a = *(float*)(self + 0x270);
                    float b = *(float*)(self + 0x274);
                    float c = *(float*)(self + 0x278);
                    float d = *(float*)(self + 0x27c);
                    float inset, delta;
                    if ((*(unsigned char*)(self + 0x23c) & 1) != 0) {
                        inset = 4.0f;
                        a += 4.0f;
                        delta = 2.0f;
                    } else {
                        inset = 3.0f;
                        a += 3.0f;
                        delta = 1.0f;
                    }
                    c -= inset;
                    d -= delta;
                    b += delta;

                    f_Typesetter_ctor((char*)self + 0x0, 0);  // placeholder stack obj
                    f_LineLayout_ctor((char*)self + 0x0, 0);
                    f_LineLayout_Clear((char*)self + 0x0, 1);

                    void* para = f_LayoutParagraph(*(void**)entry,
                                                   (*(int*)(entry + 4) - *(int*)*(void**)entry) >> 1,
                                                   a, b, c, d, style, 0, 0x7f);
                    f_0096e740(f_0096e740, para, 0, 0, 0, 0, 0);
                    *(unsigned*)((char*)style + 0x224) = saved;
                }
            }
        }
    }
    vt = *(void***)self;
    ((void (*)(void*, void*, int))vt[0x98 / 4])(self, ctx, 2);
    (void)ok;
    return true;
}

// @ 0x00969360
unsigned WinComboBox::FindValue(const wchar_t* s)
{
    if (s == 0)
        return 0xffffffffu;
    char* self = (char*)this;
    unsigned count = (unsigned)((*(int*)(self + 0x40) - *(int*)(self + 0x3c)) >> 4);
    if (count == 0)
        return 0xffffffffu;

    char* base = (char*)*(void**)(self + 0x3c);
    for (unsigned i = 0; i < count; i++) {
        char* e = base + i * 16;
        const wchar_t* a = *(const wchar_t**)e;
        const wchar_t* b = (const wchar_t*)*(void**)(e + 4);
        int la = (int)(b - a);
        int lb = 0;
        while (s[lb]) lb++;
        int n = la < lb ? la : lb;
        int cmp = 0;
        for (int k = 0; k < n; k++) {
            if (a[k] != s[k]) { cmp = a[k] < s[k] ? -1 : 1; break; }
        }
        if (cmp == 0)
            cmp = (la > lb) - (la < lb);
        if (cmp == 0)
            return i;
    }
    return 0xffffffffu;
}

// @ 0x00969450
WinComboBox::WinComboBox()
{
    char* self = (char*)this;
    ((CustomWindowBase*)this)->Ctor();

    // Base subobject vtable, then the derived overrides (separate stores).
    *(unsigned*)(self + 0x20c) = (unsigned)(size_t)g_vtbl_WinComboBox2;
    *(void**)(self + 0x000) = (void*)g_vtbl_WinComboBox0;
    *(void**)(self + 0x004) = (void*)g_vtbl_WinComboBox1;
    *(unsigned*)(self + 0x20c) = (unsigned)(size_t)g_vtbl_WinComboBox3;
    *(void**)(self + 0x210) = (void*)g_vtbl_WinComboBox4;

    *(int*)(self + 0x21c) = 0;
    *(char*)(self + 0x244) = 0;
    *(char*)(self + 0x245) = 0;
    *(int*)(self + 0x214) = -1;
    *(int*)(self + 0x218) = -1;
    *(int*)(self + 0x238) = -1;
    *(int*)(self + 0x23c) = 1;
    *(int*)(self + 0x240) = 1;
    *(int*)(self + 0x248) = 0;
    *(int*)(self + 0x24c) = 0;
    *(int*)(self + 0x250) = 0;
    *(int*)(self + 0x25c) = 0;

    char* area = self + 0x290;
    *(int*)(area + 0) = 0;
    *(int*)(area + 4) = 2;
    *(int*)(area + 8) = 3;
    *(float*)(area + 0xc) = 0.0f;
    *(float*)(area + 0x10) = 0.0f;
    *(float*)(area + 0x14) = 0.0f;
    *(float*)(area + 0x18) = 0.0f;
    *(int*)(area + 0x24) = 0;

    ((DropShadowDesc*)(self + 0x290))->SetMode(2);

    *(unsigned*)(self + 0x224) = 0xffece9d8;
    *(unsigned*)(self + 0x228) = 0xffece9d8;
    *(int*)(self + 0x230) = -1;
    *(unsigned*)(self + 0x220) = 0xff000000;
    *(unsigned*)(self + 0x22c) = 0xff737163;
    *(unsigned*)(self + 0x234) = 0xff000000;
}

// @ 0x009695d0
WinComboBox::~WinComboBox()
{
    char* self = (char*)this;
    *(void**)(self + 0x000) = g_vtbl_WinComboBox0;
    *(void**)(self + 0x004) = g_vtbl_WinComboBox1;
    *(void**)(self + 0x20c) = g_vtbl_WinComboBox3;
    *(void**)(self + 0x210) = g_vtbl_WinComboBox4;
    IRefCounted* p = *(IRefCounted**)(self + 0x25c);
    if (p)
        p->Release();
    char* vec = self + 0x248;
    f_VecDoDestroyValues(*(void**)vec, *(void**)(vec + 4));
    void* begin = *(void**)vec;
    if (begin && *(int*)((char*)begin - 4) != 0)
        f_operator_delete(begin);
    *(void**)(self + 0x20c) = g_vtbl_GmeEditorResBase;
    f_00962740(self);
}

// @ 0x00969650
bool WinComboBox::CalcSize(void* unused, float* out)
{
    char* self = (char*)this;
    float minW = 40.0f;
    float minH = 10.0f;
    float w = 40.0f;
    float h = 10.0f;
    (void)unused;

    if (*(void**)(self + 0x248) == *(void**)(self + 0x24c))
        goto done;

    {
        void* mgr = f_GetStyleManager(1);
        if (!mgr)
            return false;
        void* style = f_GetStyle(mgr, *(unsigned*)(self + 0xc0), 0);
        if (*(unsigned*)(self + 0xc0) == 0)
            goto done;

        f_Typesetter_ctor(0, 0);
        f_LineLayout_ctor(0, 0);
        {
            int n = (*(int*)(self + 0x24c) - *(int*)(self + 0x248)) >> 4;
            if (n > 0) {
                for (int i = 0; i < n; i++) {
                    char* e = (char*)*(void**)(self + 0x248) + i * 16;
                    f_LineLayout_Clear(0, 1);
                    f_LayoutParagraph(*(void**)e,
                                      (*(int*)(e + 4) - *(int*)*(void**)e) >> 1,
                                      0.0f, 0.0f, 100000.0f, 100000.0f, style, 0, 0);
                    float ew = 0.0f;   /* layout width */
                    float eh = 0.0f;   /* layout height */
                    w = w > ew ? w : ew;
                    h = h > eh ? h : eh;
                }
            }
        }
        f_LineLayout_dtor(0);
        f_Typesetter_dtor(0);
    }

done:
    out[1] = h + 6.0f;
    if (w * 0.33333334f > minH) {
        float a = (h + w) + 4.0f;
        *out = a > 30.0f ? a : 30.0f;
    } else {
        float a = w * 2.0f + 4.0f;
        *out = a > 30.0f ? a : 30.0f;
    }
    return true;
}

extern "C" void* f_VecDoInsertValue2(void* self, void* pos, void* val);     // 0x554c30
extern "C" void* f_VecInsert2(void* self, void* pos, void* val);            // 0x92b750
extern "C" void* f_VecErase2(void* pos);                                    // 0x92b700
extern "C" void  f_RangeInitialize2(void* self, const wchar_t* s);          // 0x579a90
extern "C" void  f_WStringAssign2(void* dst, const wchar_t* b, const wchar_t* e); // 0x423650
extern "C" void  f_StrCopyCtor2(void* self, void* src);                     // 0x56e2d0
extern "C" void* f_CopyWStrings2(void* dst, void* begin, void* end);        // 0x84ab40

// @ 0x00969870
bool WinComboBox::SetValue(unsigned idx, const wchar_t* s)
{
    char* self = (char*)this;
    if (idx >= (unsigned)((*(int*)(self + 0x40) - *(int*)(self + 0x3c)) >> 4))
        return false;
    void* dst = (char*)*(void**)(self + 0x3c) + idx * 16;
    const wchar_t* p = s;
    while (*p) p++;
    ((WString*)dst)->assign(s, p);
    return true;
}

// @ 0x00969920
bool WinComboBox::RemoveValue(unsigned idx)
{
    char* self = (char*)this;
    unsigned count = (unsigned)((*(int*)(self + 0x40) - *(int*)(self + 0x3c)) >> 4);
    if (idx >= count)
        return false;
    void* p = (char*)*(void**)(self + 0x3c) + idx * 16;
    ((WStringVec*)(self + 0x3c))->erase(p);
    return true;
}

// @ 0x00969950
void WinComboBox::AddValue(const wchar_t* s)
{
    char* self = (char*)this;
    int pad = 0; (void)pad;
    struct { void* a; void* b; void* c; } tmp;
    tmp.a = 0; tmp.b = 0; tmp.c = 0;
    ((WString*)&tmp)->RangeInitialize(s);

    WStringVec* vec = (WStringVec*)(self + 0x3c);
    void* end = vec->mpEnd;
    if ((unsigned)end < (unsigned)vec->mpCapacity) {
        vec->mpEnd = (char*)end + 16;
        if (end)
            ((WString*)end)->CopyCtor((WString*)&tmp);
    } else {
        vec->DoInsertValue(end, &tmp);
    }
    if (((int)((char*)tmp.c - (char*)tmp.a) & 0xfffffffe) > 2 && tmp.a)
        f_operator_delete(tmp.a);
}

// @ 0x009699d0
bool WinComboBox::InsertValue(unsigned idx, const wchar_t* s)
{
    char* self = (char*)this;
    unsigned count = (unsigned)((*(int*)(self + 0x40) - *(int*)(self + 0x3c)) >> 4);
    if (idx > count)
        return false;

    struct { void* a; void* b; void* c; } tmp;
    tmp.a = 0; tmp.b = 0; tmp.c = 0;
    ((WString*)&tmp)->RangeInitialize(s);

    WStringVec* vec = (WStringVec*)(self + 0x3c);
    void* pos = (char*)vec->mpBegin + idx * 16;
    vec->insert(pos, &tmp);
    if (((int)((char*)tmp.c - (char*)tmp.a) & 0xfffffffe) > 2 && tmp.a)
        f_operator_delete(tmp.a);
    return true;
}

// @ 0x00969a60
void WinComboBox::RemoveAllValues()
{
    char* self = (char*)this;
    WStringVec* vec = (WStringVec*)(self + 0x3c);
    WString* begin = (WString*)vec->mpBegin;
    WString* end = (WString*)vec->mpEnd;
    WString* dst = (WString*)f_CopyWStrings(end, end, begin);
    vec->DoDestroyValues(dst, vec->mpEnd);
    vec->mpEnd = (char*)vec->mpEnd - (((char*)end - (char*)begin) >> 4) * 16;
}

// ---------------------------------------------------------------------------
// 0x00969ac0  -- scrollbar-drawable-derived ctor
// ---------------------------------------------------------------------------
struct ScrollbarBase {
    void BaseCtor();                // 0x9838a0 UI::ScrollbarDrawable::ScrollbarDrawable
};
struct ScrollbarDrawable : ScrollbarBase {
    ScrollbarDrawable();            // 0x969ac0
};

// @ 0x00969ac0
ScrollbarDrawable::ScrollbarDrawable()
{
    ((ScrollbarBase*)this)->BaseCtor();
    *(void**)((char*)this + 0x0) = g_vtbl_ScrollbarDrawable0;
    *(void**)((char*)this + 0x4) = g_vtbl_ScrollbarDrawable1;
    *(void**)((char*)this + 0xc) = g_vtbl_ScrollbarDrawable2;
}

// ---------------------------------------------------------------------------
// 0x00969b90..0x00969d40  -- EA::UTFWinControls::ConsoleWindow
// ---------------------------------------------------------------------------
extern "C" int   f_00961e80(void* self);                 // 0x961e80 Window::Shutdown
extern "C" void* f_LayoutParagraph_3(void* text, int len, float x, float y,
                                     float w, float h, void* style, void* ll, int flags); // 0x89dc00

struct ConsoleLine {            // the object handed to LayoutLine/Draw
    char* mpText;               // +0x00
    char pad04[0x0c - 0x04];
    int   mnField0c;            // +0x0c
    int   mnLen;                // +0x10
    float mPosX;                // +0x14
};

struct ConsoleWindow {
    bool Shutdown();                        // 0x969b90
    void LayoutLine(ConsoleLine* line);     // 0x969bf0
    void Draw();                            // 0x969d40
};

// @ 0x00969b90
bool ConsoleWindow::Shutdown()
{
    char* s = (char*)this;
    void* p = *(void**)(s + 0x864);
    if (p) {
        void** vt = *(void***)p;
        void* r = ((void* (*)(void*))vt[0x10 / 4])(p);
        void** wt = *(void***)(s + 4);
        ((void (*)(void*, void*))wt[0xe0 / 4])(s + 4, r);
        p = *(void**)(s + 0x864);
        if (p) {
            *(void**)(s + 0x864) = 0;
            ((IRefCounted*)p)->Release();
        }
    }
    *(char*)(s + 0x860) = 0;
    return f_00961e80(s) != 0;
}

// @ 0x00969bf0
void ConsoleWindow::LayoutLine(ConsoleLine* line)
{
    char* s = (char*)this;
    if (*(char*)(s + 0x860) == 0) {
        *(char*)(s + 0x861) = 1;
        return;
    }
    float x = *(float*)(s + 0x84c);
    float y = *(float*)(s + 0x850);
    float w = (*(float*)(s + 0x90) - *(float*)(s + 0x88)) -
              (*(float*)(s + 0x854) - 3.0f);

    if (*(char*)(s + 0x868) != 0) {
        void* p = *(void**)(s + 0x864);
        void** vt = *(void***)p;
        void* inner = ((void* (*)(void*))vt[0x10 / 4])(p);
        void** it = *(void***)inner;
        float* r = (float*)((void* (*)(void*))it[0x34 / 4])(inner);
        w = (r[2] - r[0]) + w;
    }

    void* mgr = f_GetStyleManager(1);
    void* style = f_GetStyle(mgr, 0xefe945b2u, 0);
    if (!style)
        return;

    char* ll = s + 0x788;
    f_LineLayout_Clear(ll, 1);
    f_LayoutParagraph_3((char*)line + 0x14, line->mnLen, x, y, w, 100000.0f,
                        style, ll, 0);
    float f = (float)*(int*)(s + 0x830);
    if (*(int*)(s + 0x830) < 0)
        f += 4294967296.0f;
    long long v = (long long)(f * (*(float*)(s + 0x828) - *(float*)(s + 0x82c)));
    line->mnField0c = (int)v;
}

// @ 0x00969d40
void ConsoleWindow::Draw()
{
    char* s = (char*)this;
    if (*(void**)(s + 0x864) == 0)
        return;

    float quad[3];
    quad[0] = 20.0f;
    quad[1] = 20.0f;

    void** vt = *(void***)(s + 4);
    void* r = ((void* (*)(void*))vt[0x14 / 4])(s + 4);

    struct { int a; int b; float c; int d; int e; } item;
    item.a = 0x16;
    item.b = 0;
    (void)item;

    if (r) {
        void* p = *(void**)(s + 0x864);
        void** objvt = *(void***)p;
        void* inner = ((void* (*)(void*))objvt[0x10 / 4])(p);
        void** ivt = *(void***)inner;
        ((void (*)(void*, void*))ivt[0x10 / 4])(inner, (void*)&item.c);
    }

    float w = *(float*)(s + 0x90) - *(float*)(s + 0x88);
    float h = *(float*)(s + 0x94) - *(float*)(s + 0x8c);

    float rect[5];
    rect[0] = w;
    rect[1] = 0.0f;
    rect[2] = h;
    rect[3] = 0.0f;
    rect[4] = w;

    void* p = *(void**)(s + 0x864);
    void** pvt = *(void***)p;
    void* inner = ((void* (*)(void*))pvt[0x10 / 4])(p);
    void** ivt = *(void***)inner;
    ((void (*)(void*, float*))ivt[0x60 / 4])(inner, &rect[2]);
    (void)quad;
}
