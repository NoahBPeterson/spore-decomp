// src/game/UTFSpore_Win32/ComboBox.cpp -- migrated from slice(s) s00968da0, s00967d40, s00966b20 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ComboBox.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_00957f30();                                   // 0x957f30

// ---- items of slice s00966b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define F(o, off)  (*(uint32_t*)((uint8_t*)(o) + (off)))
#define FB(o, off) (*(uint8_t*)((uint8_t*)(o) + (off)))
struct S_9614a0 { void __thiscall m(); };                                  // 0x9614a0 SerUpdate
struct S_9609b0 { void __thiscall m(); };                                  // 0x9609b0 InvalidateLayout
struct S_961e80 { bool __thiscall m(); };                                  // 0x961e80
struct S_830150 { void __thiscall m(uint32_t); };                          // 0x830150 SetMode2
struct S_830280 { void __thiscall m(uint32_t); };                          // 0x830280 SetMode1
extern "C" void* __cdecl FUN_00957f30();                                   // 0x957f30
static inline void VCALL0(void* o, int off) {
    ((void (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline uint32_t VCALL0R(void* o, int off) {
    return ((uint32_t (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline void VCALL1(void* o, int off, uint32_t a) {
    ((void (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
static inline uint32_t VCALL1R(void* o, int off, uint32_t a) {
    return ((uint32_t (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
static inline uint32_t VCALL2R(void* o, int off, uint32_t a, uint32_t b) {
    return ((uint32_t (__thiscall*)(void*, uint32_t, uint32_t))(*(void***)o)[off / 4])(o, a, b);
}
struct S_967980 { void     __thiscall m(); };
struct S_9679c0 { bool     __thiscall m(); };
struct S_967a60 { void     __thiscall m(uint32_t); };
struct S_967d20 { void     __thiscall m(); };
struct S_967ac0 { void     __thiscall m(void*); };
struct S_967b10 { bool     __thiscall m(uint32_t, uint32_t, uint32_t, int); };
struct S_967bc0 { bool     __thiscall m(uint32_t, uint32_t, uint32_t, uint8_t); };
struct S_967c90 { uint8_t  __thiscall m(float, float, uint32_t); };
struct S_967cd0 { uint8_t  __thiscall m(int, void*); };
struct S_967d10 { uint8_t  __thiscall m(); };
// ---- items of slice s00966b20 end

// ---- items of slice s00967d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_kTwoThirds;                                   // 0x01470f1c
extern float g_kHalf;                                        // 0x01471064
extern float g_kOne;                                         // 0x01485720
typedef void  (__fastcall* F0)(void*, void*);typedef void  (__fastcall* F1)(void*, void*, int);
typedef void  (__fastcall* F2)(void*, void*, int, int);
typedef void  (__fastcall* F3)(void*, void*, int, int, int);
typedef void  (__fastcall* FF1)(void*, void*, float);
typedef void  (__fastcall* FF4)(void*, void*, float, float, float, float);
typedef void  (__fastcall* FP)(void*, void*, void*);
typedef void* (__fastcall* P0)(void*, void*);
typedef void* (__fastcall* P1)(void*, void*, uint32_t);
typedef void* (__fastcall* PP)(void*, void*, void*);
typedef int   (__fastcall* I4)(void*, void*, int, int, int, int);
typedef int   (__fastcall* IP)(void*, void*, void*);
typedef int   (__fastcall* IPP)(void*, void*, void*, void*);
#define VS(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
#define VSO(p, off) (*(void**)((char*)(p) + (off)))
struct IWinPropA {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* GetProp(uint32_t id);   // +0x0c
};
struct IWnd {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual int GetState();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
    virtual void OnPropValue(int, int);   // +0x7c
virtual void d32();
virtual void d33();
virtual void d34();
    virtual void SetAlignment(int);       // +0x8c
    virtual void Update();                // +0x90
virtual void d37();
virtual void d38();
virtual void d39();
virtual void d40();
virtual void d41();
virtual void d42();
virtual void d43();
virtual void d44();
virtual void d45();
virtual void d46();
virtual void d47();
virtual void d48();
virtual void d49();
virtual void d50();
virtual void d51();
virtual void d52();
virtual void d53();
virtual void d54();
virtual void d55();
virtual void d56();
virtual void d57();
virtual void d58();
virtual void d59();
virtual void d60();
virtual void d61();
virtual void d62();
virtual void d63();
virtual void d64();
virtual void d65();
virtual void d66();
virtual void d67();
virtual void d68();
    virtual void HandleMsg(void* msg);    // +0x114
};
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
void* GetUTFWinAllocator();                                                              // 0x009512c0
void* operator new(unsigned int size, int align, const char* name, void* alloc);          // 0x009512d0
struct WinGrid;
WinGrid* WinGrid_Ctor(void* p);                                                          // 0x009770e0
void* RenderContext_Begin2D(void* renderCtx, int mode);                                   // 0x0095bc10
struct Image { uint32_t pad0[7]; int32_t mSizeX; int32_t mSizeY; };   // +0x1c / +0x20
struct AutoRefCountIface { virtual int AddRef(); virtual int Release(); };
struct IDrawable3 {
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
    virtual void Render(void* ctx, void* area, void* info);   // +0x10
};
struct IBatch {
    virtual void d0();
    virtual void Attach(void* p);                             // +0x04
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
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
void WCB::SetAlignment(uint32_t value)
{
    Real(this)->i240 = (int32_t)value;
    ((IWnd*)Real(this))->SetAlignment(1);
}extern float g_kOneQuarter;                                   // 0x013eb8a0
// ---- items of slice s00967d40 end

// ---- items of slice s00968da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* f_Begin2D(void* ctx, void* mode);                      // 0x95bc10
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
extern "C" void  f_0096e740(void* a, void* b, void* c, void* d, void* e, void* f, int g); // 0x96e740
extern "C" void  f_VecDoDestroyValues(void* begin, void* end);          // 0x84aad0
extern "C" void* f_CopyWStrings(void* dst, void* begin, void* end);     // 0x84ab40
extern "C" void  f_operator_delete(void* p);                            // 0xf47380
extern "C" void* f_FactoryAllocCtx(void);                               // 0x9512c0
extern "C" void* f_FactoryAlloc(int size, int align, const char* name, void* ctx); // 0x9512d0
extern "C" void  f_00962740(void* self);                                // base dtor 0x962740
extern uint8_t g_vtbl_ResourceAsync[];         // 0x13fa72c
extern uint8_t g_vtbl_ComboBoxDrawable0[];     // 0x14416a0
extern uint8_t g_vtbl_ComboBoxDrawable1[];     // 0x1441688
extern uint8_t g_vtbl_ComboBoxDrawable2[];     // 0x1441670
extern const char g_szComboBoxDrawable[];  // "UTFWin/EA::UTFWinControls::ComboBoxDrawable"
extern "C" void f_BatchSetColor(void* batch, unsigned color);           // vtbl+4
extern "C" void f_BatchDrawSprite(void* batch, void* xform, void* drawable, void* uvs); // vtbl+0x58
extern "C" void f_BatchDrawCmd(void* batch, void* a, void* b, void* c, void* d, void* e); // vtbl+0x3c
extern "C" void f_BatchDrawCmd1(void* batch, void* a, void* b, void* c, void* d); // vtbl+0x3c
extern uint8_t g_vtbl_WinComboBox0[];          // 0x1441890
extern uint8_t g_vtbl_WinComboBox1[];          // 0x1441770
extern uint8_t g_vtbl_WinComboBox2[];          // 0x1440fe8
extern uint8_t g_vtbl_WinComboBox3[];          // 0x1441700
extern uint8_t g_vtbl_WinComboBox4[];          // 0x14416f4
extern uint8_t g_vtbl_GmeEditorResBase[];      // 0x13eb938
struct ResAsyncBase {
    virtual void r0();
    virtual void r1();
};
struct CbdPart1 : ResAsyncBase {
    int m08;
};
struct CbdPart2 : ResAsyncBase {
};
struct ComboBoxDrawable {
    int m00;
    int m04;
    int m08;
    int m0c;
    int m10;
    int m14;
    int m18;

    ComboBoxDrawable();                                    // 0x969000
    static void* __stdcall CreateInstance(void* unused, void* ctx); // 0x969060
};
struct UvQuad { float u0; float v; float u1; float w; float x; };
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
// ---- items of slice s00968da0 end

// @ 0x00967890
extern "C" uint8_t __cdecl FUN_00967890(uint32_t param_1, uint32_t param_2)
{
    uint32_t obj = F(param_1, 4);
    if (obj != 0) {
        uint8_t* sub = (uint8_t*)(obj + 0x20c);
        VCALL0(sub, 0x2c);
        uint32_t arr = F(param_2, 4);
        if (arr != 0) {
            for (uint32_t i = 0; i < F(param_2, 8); i++)
                VCALL1(sub, 0x20, *(uint32_t*)(arr + i * 4));
        }
        return 1;
    }
    return 0;
}

// @ 0x009678f0
extern "C" uint8_t __cdecl FUN_009678f0(uint32_t* param_1, uint32_t param_2, uint32_t param_3, uint32_t* param_4)
{
    uint32_t obj = F(param_2, 4);
    if (obj != 0) {
        uint8_t* sub = (uint8_t*)(obj + 0x20c);
        uint32_t n = VCALL0R(sub, 0x3c);
        param_1[2] = n;

        uint32_t* arr = (uint32_t*)((void* (__thiscall*)(void*, uint32_t, int))
            ((void**)*(void**)param_4)[0])(param_4, n * 4, 4);
        param_1[1] = (uint32_t)arr;

        uint32_t kind = (*(uint16_t*)(param_3 + 0xc)) & 0xfff;
        param_1[0] = ((uint32_t*)0x154eea0)[kind];

        if (arr != 0) {
            uint32_t* dst = arr;
            for (uint32_t i = 0; i < n; i++, dst++)
                *dst = VCALL1R(sub, 0x34, i);
        }
        return 1;
    }
    return 0;
}

// @ 0x00967980
void S_967980::m()
{
    void* this_ = this;
    VCALL1(this_, 0x8c, 1);
    uint8_t* cb = (uint8_t*)this_ + 0x290;
    ((S_830280*)cb)->m(F(this_, 0x290));
    ((S_830150*)cb)->m(F(this_, 0x294));
    ((S_9614a0*)this_)->m();
}

// @ 0x009679c0
bool S_9679c0::m()
{
    void* this_ = this;
    void* mgr = FUN_00957f30();
    if (mgr != 0) {
        void* m2 = FUN_00957f30();
        void* combo = (void*)VCALL0R(m2, 0x84);
        if (combo != 0) {
            if (VCALL1R(combo, 0x0c, 0xaf1ee902)) {
                if (VCALL0R(combo, 0x1c) == (uint32_t)this_) {
                    void* m3 = FUN_00957f30();
                    ((void (__thiscall*)(void*, void*, int))
                        (*(void***)m3)[0x78 / 4])(m3, combo, 0);
                }
            }
        }
    }
    return ((S_961e80*)this_)->m();
}

// @ 0x00967a60
void S_967a60::m(uint32_t param_2)
{
    uint32_t* v = *(uint32_t**)((uint8_t*)this - 0x20c);
    F(this, 0x30) = param_2;
    ((void (__thiscall*)(void*, int))(void*)v[0x8c / 4])((uint8_t*)this - 0x20c, 1);
}

// @ 0x00967ac0
void S_967ac0::m(void* param_2)
{
    void* this_ = this;
    uint32_t arg = param_2 ? VCALL0R(param_2, 0x10) : 0;
    VCALL1((uint8_t*)this_ - 0x208, 0xb0, arg);
    VCALL1((uint8_t*)this_ - 0x20c, 0x8c, 1);
}

// @ 0x00967b10
bool S_967b10::m(uint32_t a, uint32_t b, uint32_t param_4, int param_5)
{
    void* this_ = this;
    if (param_5 != 8)
        return 0;
    uint8_t* s4 = (uint8_t*)this_ + 4;
    uint32_t u = VCALL0R(s4, 0x28);
    if ((u & 2) == 0)
        return 1;

    uint32_t r = VCALL2R(this_, 0x9c, a, b);
    F(this_, 0x218) = r;
    if (r != 0xffffffff) {
        uint8_t* list = (uint8_t*)F(this_, 0x34);
        void** lvt = *(void***)list;
        if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 1) != s4)
            ((void (__thiscall*)(void*, int, void*))lvt[0x58 / 4])(list, 1, s4);
        if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 0) != s4)
            ((void (__thiscall*)(void*, int, void*))lvt[0x58 / 4])(list, 0, s4);
        VCALL0(this_, 0x94);
        VCALL0(s4, 0x90);
    }
    return 1;
}

// @ 0x00967bc0
bool S_967bc0::m(uint32_t a, uint32_t b, uint32_t param_4, uint8_t flags)
{
    void* this_ = this;
    if ((flags & 8) != 0)
        return 0;

    uint8_t* s4 = (this_ != 0) ? (uint8_t*)this_ + 4 : 0;
    uint8_t* list = (uint8_t*)F(this_, 0x34);
    void** lvt = *(void***)list;

    if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 1) == s4)
        ((void (__thiscall*)(void*, int, void*))lvt[0x5c / 4])(list, 1, (uint8_t*)this_ + 4);
    if ((void*)((void* (__thiscall*)(void*, int))lvt[0x54 / 4])(list, 0) == (uint8_t*)this_ + 4)
        ((void (__thiscall*)(void*, int, void*))lvt[0x5c / 4])(list, 0, (uint8_t*)this_ + 4);

    void** vt = *(void***)this_;
    void* fn = vt[0x9c / 4];
    uint8_t* self4 = (uint8_t*)this_ + 4;

    if (FB(this_, 0x245) != 0) {
        uint32_t r = ((uint32_t (__thiscall*)(void*, uint32_t, uint32_t))fn)(this_, a, b);
        F(this_, 0x218) = r;
        F(this_, 0x214) = 0xffffffff;
        VCALL0(self4, 0x90);
        return 1;
    }
    F(this_, 0x218) = 0xffffffff;
    uint32_t r = ((uint32_t (__thiscall*)(void*, uint32_t, uint32_t))fn)(this_, a, b);
    F(this_, 0x214) = r;
    VCALL0(self4, 0x90);
    return 1;
}

// @ 0x00967c90
uint8_t S_967c90::m(float a, float b, uint32_t)
{
    void* this_ = this;
    uint32_t r = ((uint32_t (__thiscall*)(void*, float, float))
        (*(void***)this_)[0x9c / 4])(this_, a, b);
    if (F(this_, 0x214) != r) {
        uint8_t* s4 = (uint8_t*)this_ + 4;
        F(this_, 0x214) = r;
        VCALL0(s4, 0x90);
    }
    return 1;
}

// @ 0x00967cd0
uint8_t S_967cd0::m(int param_2, void* param_3)
{
    void* this_ = this;
    if (param_2 == 1) {
        void* s4 = (this_ != 0) ? (uint8_t*)this_ + 4 : 0;
        if (param_3 != s4 && F(this_, 0x214) != 0xffffffff) {
            F(this_, 0x214) = 0xffffffff;
            VCALL0((uint8_t*)this_ + 4, 0x90);
        }
    }
    return 1;
}

// @ 0x00967d10
uint8_t S_967d10::m()
{
    void* this_ = this;
    VCALL0(this_, 0x90);
    return 1;
}

// @ 0x00967d20
void S_967d20::m()
{
    void* this_ = this;
    uint8_t* base = (uint8_t*)this_ - 4;
    void** vt = *(void***)base;
    void (__thiscall* fn)(void*, int) = (void (__thiscall*)(void*, int))vt[0x8c / 4];
    fn(base, 1);
    ((S_9609b0*)this_)->m();
}

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

// @ 0x00969000
ComboBoxDrawable::ComboBoxDrawable()
{
    *(volatile uint32_t*)((char*)this + 4) = 0x13fa72c;
    _ReadWriteBarrier();
    m08 = 0;
    *(uint32_t*)((char*)this + 0xc) = 0x13fa72c;
    _ReadWriteBarrier();
    *(uint32_t*)((char*)this + 0) = 0x14416a0;
    *(uint32_t*)((char*)this + 4) = 0x1441688;
    *(uint32_t*)((char*)this + 0xc) = 0x1441670;
    m10 = 0;
    m14 = 0;
    m18 = 0;
}

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
    struct { void* a; void* b; void* c; void* d; } tmp;
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
    if (((int)((char*)tmp.c - (char*)tmp.a) & -2) > 2 && tmp.a)
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
