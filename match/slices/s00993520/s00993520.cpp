// Slice s00993520 -- EA::UTFWinExtras::WinXHTML scrollbar / form-control / lifetime
// methods.  Object file: UTFSpore_Win32/XHTMLFrameSet.obj (closure).
#include "types.h"

// ---- runtime helpers (address in the comment) ----
extern "C" void* FUN_009512c0(void);                                    // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void* WinScrollbar_ctor(void* mem);                          // 0x983790
extern "C" void* ScrollbarDrawable_ctor(void* mem);                     // 0x9838a0
extern "C" void* WinWindow_ctor(void* mem);                             // 0x962a10
extern "C" void* FrameDrawable_ctor(void* mem);                         // 0x96fe30
extern "C" void* StdDrawable_ctor(void* mem);                           // 0x988420
extern "C" void* ComboBoxDrawable_ctor(void* mem);                      // 0x969000
extern "C" void  Window_Initialize(void* self);                         // 0xb1fbf0
extern "C" void  Window_Shutdown(void* self);                           // 0x961e80
extern "C" void  Win_SerUpdate(void* self);                             // 0x9614a0
extern "C" void  FUN_008ec790(void* a);                                 // 0x8ec790
extern "C" void  Page_FUN_008eb830(void* page, void* a);                // 0x8eb830
extern "C" void  Page_NotifyImagesAbandoned(void* page);                // 0x8eb7a0
extern "C" void* XHTML_Style_CreateDefaultStylesheet(void);             // 0x8fa050
extern "C" void* Text_GetStyleManager(int flag);                        // 0x885bd0
extern "C" int   Text_StyleManagerAddStyle(void* mgr, int key, void* style, unsigned* out); // 0x894970
extern "C" void  Text_StyleManagerRemoveStyle(void* mgr, int key);       // 0x894700
extern "C" void* XHTML_DOM_Element_GetAttrValue(void* elem, const wchar_t* name); // 0x8e45b0
extern "C" void  XHTML_DOM_FormControl_SetControl(void* fc, void* ctl);  // 0x8e4b60
extern "C" void  DocX_RemoveAllChildren(void* doc);                     // 0x8e2930
extern "C" void  Stopwatch_ctor(void* self, int a, int b);              // 0x93a560
extern "C" long  wcstol(const wchar_t* s, wchar_t** end, int base);
extern "C" double wcstod(const wchar_t* s, wchar_t** end);
extern "C" int   _wcsicmp(const wchar_t* a, const wchar_t* b);

// ---- globals (address in the comment) ----
extern float  g_kScrollbarSize;                                         // 0x13eecd8
extern float  g_kRowsToPixels;                                          // 0x14763b0
extern float  g_kColsToPixels;                                          // 0x13f6b68
extern float  g_kDefaultWidth;                                          // 0x1470f1c
extern float  g_kSelectPadPixels;                                       // 0x1446660
extern float  g_kOne;                                                   // 0x1485720
extern float  g_kFormCtrlDefaultSize;                                   // 0x1473c70
extern wchar_t* g_pAttr_rows;                                           // 0x1550130
extern wchar_t* g_pAttr_cols;                                           // 0x1550134
extern wchar_t* g_pAttr_type;                                           // 0x1550108
extern wchar_t* g_pAttr_size;                                           // 0x1550128
extern wchar_t* g_pAttr_text;                                           // 0x155013c
extern wchar_t* g_pAttr_password;                                       // 0x1550140

#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])

// ---- WinXHTML as seen from these methods (retail offsets) ----
struct WinXHTML {
    void* mVtbl0;                   // 0x000
    void* mIWindow;                 // 0x004   (IWindow interface sub-object)
    char  pad[0x200 - 8];
    unsigned char mbRefresh;        // 0x200
    char  pad2[0x23c - 0x201];
    void* mDoc;                     // 0x23c
    void* mPageRoot;                // 0x240
    char  pad3[0x850 - 0x244];
    void* mFormCtrlDrawable[5];     // 0xa850
    float mVisibleArea[4];          // 0xa864  (left/top/right/bottom)
    void* mContentWindow;           // 0xa874
    void* mScrollbar0;              // 0xa878
    void* mDrawable0;               // 0xa87c
    int   mEnabled0;                // 0xa880
    float mPref0X;                  // 0xa884
    float mPref0Y;                  // 0xa888
    void* mScrollbar1;              // 0xa88c
    void* mDrawable1;               // 0xa890
    int   mEnabled1;                // 0xa894
    float mPref1X;                  // 0xa898
    float mPref1Y;                  // 0xa89c
    void* mScrollPosish;            // 0xa8a0
    void* mField_a8a4;              // 0xa8a4

    void CreateScrollbar(int which);
    void DestroyFormControl(void* fc);
    void SetFormControlStyle(void* fc, void* style);
    void GetFormControlSize(void* fc, void* out);
    void SetFormControlArea(void* fc, void* area);
    void SetFormControlDrawable(int which, void* drawable);
    void SerUpdate();
    WinXHTML();
    bool Init();
    bool Shutdown();
    void CalculateVisibleArea();
    void SetScrollbarDrawable(int which, void* drawable);
};

// @ 0x00993520
void WinXHTML::CreateScrollbar(int param_2)
{
    char* self = (char*)this;
    char* st = self + param_2 * 0x14 + 0xa88c;   // &mScrollbars[param_2+1]
    void** ppScrollbar = (void**)st;                       // +0 mScrollbar
    void** ppDrawable  = (void**)(st + 4);                 // +4 mDrawable
    int*   pEnabled    = (int*)(st + 8);                   // +8 mEnabled
    float* pPref       = (float*)(st + 0xc);               // +0xc mPreferredSize

    if (*pEnabled == 0) {
        // kScrollbarNever: tear the scrollbar down
        void* sb = *ppScrollbar;
        if (sb == 0)
            return;
        void* iface = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(self + 4, 0xe0, void(__thiscall*)(void*, void*))(self + 4, iface);
        void* old = *ppScrollbar;
        if (old == 0)
            return;
        *ppScrollbar = 0;
        VF(old, 4, void(__thiscall*)(void*))(old);
        return;
    }

    // create the scrollbar if absent
    if (*ppScrollbar == 0) {
        void* mem = FUN_009512d0(0x2d0, 8, "UTFWin/WinXHTML/Scrollbar", FUN_009512c0());
        void* sb = 0;
        if (mem != 0) {
            void* c = ((void*(__thiscall*)(void*))WinScrollbar_ctor)(mem);
            if (c != 0)
                sb = (char*)c + 0x20c;
        }
        void* old = *ppScrollbar;
        if (sb != old) {
            if (sb != 0)
                VF(sb, 0, void(__thiscall*)(void*))(sb);
            *ppScrollbar = sb;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        void* iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(iface, 0x7c, void(__thiscall*)(void*, int, int))(iface, 0x200, 1);
        iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(iface, 0x7c, void(__thiscall*)(void*, int, int))(iface, 0x40, 1);
        iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(iface, 0x14, void(__thiscall*)(void*, int))(iface, param_2 == 1 ? 2 : 1);
        iface = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(self + 4, 0xd8, void(__thiscall*)(void*, void*))(self + 4, iface);
    }

    // choose the drawable
    if (*ppDrawable == 0) {
        void* mem = FUN_009512d0(0x2c, 4, "UTFWin/WinXHTML/ScrollbarDrawable", FUN_009512c0());
        void* d = 0;
        if (mem != 0)
            d = ScrollbarDrawable_ctor(mem);
        VF(*ppScrollbar, 0x5c, void(__thiscall*)(void*, void*))(*ppScrollbar, d);
    } else {
        void* r;
        if (*ppDrawable != 0)
            r = VF(*ppDrawable, 0xc, void*(__thiscall*)(void*, unsigned))(*ppDrawable, 0x6ec581fd);
        else
            r = 0;
        VF(*ppScrollbar, 0x5c, void(__thiscall*)(void*, void*))(*ppScrollbar, r);
    }

    // size hints + attach to the parent window
    float sz = g_kScrollbarSize;
    pPref[0] = sz;
    pPref[1] = sz;
    int rel[5];
    rel[0] = 0x16; rel[1] = 0; rel[2] = 0; rel[3] = 0; rel[4] = 0;
    if (VF(self + 4, 0x14, void*(__thiscall*)(void*))(self + 4) != 0) {
        void* dw = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        void* win = VF(self + 4, 0x14, void*(__thiscall*)(void*))(self + 4);
        void* a = VF(dw, 0x10, void*(__thiscall*)(void*, void*, void*, int))(dw, win, rel, 0);
        void* b = VF(*ppScrollbar, 0x10, void*(__thiscall*)(void*))(*ppScrollbar);
        VF(a, 0x10, void(__thiscall*)(void*, void*))(a, b);
    }
}

// @ 0x00993720
void WinXHTML::DestroyFormControl(void* param_2)
{
    char* self = (char*)this;
    void* ctl = *(void**)((char*)param_2 + 0x44);
    if (ctl == 0)
        return;
    void* piVar2 = VF(ctl, 0xc, void*(__thiscall*)(void*, unsigned))(ctl, 0xeeee8218);
    if (piVar2 == 0)
        return;
    int iVar3 = VF(piVar2, 0x40, int(__thiscall*)(void*))(piVar2);
    if (iVar3 != 1) {
        void* mgr = Text_GetStyleManager(1);
        if (mgr != 0)
            ((void(__thiscall*)(void*, int))Text_StyleManagerRemoveStyle)(mgr, iVar3);
    }
    if (VF(piVar2, 0x10, int(__thiscall*)(void*))(piVar2) != 0)
        VF(*(void**)(self + 0xa67c), 0xe0, void(__thiscall*)(void*, void*))(*(void**)(self + 0xa67c), piVar2);
    ((void(__thiscall*)(void*, void*))XHTML_DOM_FormControl_SetControl)(param_2, 0);
}

// @ 0x009937a0
void WinXHTML::SetFormControlStyle(void* param_2, void* param_3)
{
    char* self = (char*)this;
    void* pfc = *(void**)((char*)param_2 + 0x44);
    if (pfc == 0)
        return;
    void* piVar1 = VF(pfc, 0xc, void*(__thiscall*)(void*, unsigned))(pfc, 0xeeee8218);
    if (piVar1 == 0)
        return;
    void* mgr = Text_GetStyleManager(1);
    if (mgr != 0) {
        unsigned key = ((int(__thiscall*)(void*, int, void*))Text_StyleManagerAddStyle)(mgr, -2, (char*)param_3 + 0xc);
        VF(piVar1, 0x84, void(__thiscall*)(void*, unsigned))(piVar1, key);
        void* q = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0xaf1ee902);
        if (q != 0)
            VF(q, 0x34, void(__thiscall*)(void*, unsigned))(q, key);
    }
    void* r = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0x8ed27e7a);
    if (r != 0) {
        VF(r, 0x4c, void(__thiscall*)(void*, int, unsigned))(r, 0, *(unsigned*)(self + 0x28c));
    } else {
        r = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0x2f5528d9);
        if (r != 0) {
            VF(r, 0x48, void(__thiscall*)(void*, int, unsigned))(r, 0, *(unsigned*)(self + 0x28c));
            VF(r, 0x48, void(__thiscall*)(void*, int, unsigned))(r, 1, *(unsigned*)(self + 0x2bc));
        } else {
            r = VF(piVar1, 0xc, void*(__thiscall*)(void*, unsigned))(piVar1, 0xaf1ee902);
            if (r != 0) {
                VF(r, 0x3c, void(__thiscall*)(void*, unsigned, int))(r, *(unsigned*)(self + 0x28c), 0);
                VF(r, 0x3c, void(__thiscall*)(void*, unsigned, int))(r, *(unsigned*)(self + 0x2bc), 1);
                VF(r, 0x4c, void(__thiscall*)(void*, int))(r, 0);
            }
        }
    }
    void* s = VF(piVar1, 0xa8, void*(__thiscall*)(void*))(piVar1);
    if (s != 0) {
        void* t = VF(s, 0xc, void*(__thiscall*)(void*, unsigned))(s, 0x30d54ac);
        if (t != 0) {
            *(unsigned*)((char*)t + 0x10) = *(unsigned*)(self + 0x2c0);
            return;
        }
    }
    VF(piVar1, 0xac, void(__thiscall*)(void*, unsigned))(piVar1, *(unsigned*)(self + 0x2c0));
}

// @ 0x00993900
void WinXHTML::GetFormControlSize(void* param_2, void* param_3)
{
    char* self = (char*)this;
    void* pfc = *(void**)((char*)param_2 + 0x28 + 0x1c);   // +0x44
    if (pfc == 0)
        return;
    void* si = VF(pfc, 0xc, void*(__thiscall*)(void*, unsigned))(pfc, 0xeeee8218);
    if (si == 0)
        return;
    float* out = (float*)param_3;
    int* elem = (int*)param_2;
    out[0] = g_kFormCtrlDefaultSize;
    out[1] = g_kFormCtrlDefaultSize;
    void* pIWin = *(void**)(self - 0x208 + 0x208);         // self
    (void)pIWin;
    int rel[2] = { 0x16, 0 };
    void* w = VF(self, 0x14, void*(__thiscall*)(void*))(self);
    if (w != 0)
        VF(w, 0x10, void(__thiscall*)(void*, void*, int*, int))(w, si, rel, 0);

    if (elem[1] == 0x1a) {          // Element_Textarea
        wchar_t* rows = (wchar_t*)XHTML_DOM_Element_GetAttrValue(param_2, g_pAttr_rows);
        wchar_t* cols = (wchar_t*)XHTML_DOM_Element_GetAttrValue(param_2, g_pAttr_cols);
        if (rows != 0) {
            int n = (int)wcstol(rows, 0, 0);
            if (n < 1) n = 1;
            out[1] = (float)n * g_kRowsToPixels;
        }
        if (cols == 0)
            return;
        int n = (int)wcstol(cols, 0, 0);
        if (n < 1) n = 1;
        out[0] = (float)n * g_kColsToPixels;
        return;
    }
    if (elem[1] == 0x18) {          // Element_Select
        void* r = VF(si, 0xc, void*(__thiscall*)(void*, unsigned))(si, 0xaf1ee902);
        if (r == 0)
            return;
        VF(r, 0x18, void(__thiscall*)(void*, int, int, float, float))(r, -1, -1, 0.0f, 0.0f);
        float* a = (float*)VF(si, 0x34, void*(__thiscall*)(void*))(si);
        out[0] = a[2] - a[0];
        float* b = (float*)VF(si, 0x34, void*(__thiscall*)(void*))(si);
        out[1] = b[3] - b[1];
        wchar_t* sz = (wchar_t*)XHTML_DOM_Element_GetAttrValue(param_2, g_pAttr_size);
        if (sz == 0)
            return;
        double d = wcstod(sz, 0);
        float f = (float)d;
        if (f > 0.0f) {
            out[1] = f * g_kSelectPadPixels;
            out[0] = out[0] + g_kRowsToPixels;
        }
        return;
    }
    // default path
    wchar_t* type = (wchar_t*)XHTML_DOM_Element_GetAttrValue(param_2, g_pAttr_type);
    wchar_t* sz = (wchar_t*)XHTML_DOM_Element_GetAttrValue(param_2, g_pAttr_size);
    if (sz == 0)
        return;
    float f = (float)wcstod(sz, 0);
    if (type != 0 && (_wcsicmp(type, g_pAttr_text) == 0 || _wcsicmp(type, g_pAttr_password) == 0)) {
        if (f < g_kOne)
            return;
        out[0] = f * g_kColsToPixels;
        return;
    }
    if (f < out[0])
        return;
    out[0] = f;
}

// @ 0x00993b70
void WinXHTML::SetFormControlArea(void* param_2, void* param_3)
{
    char* page = (char*)this;
    void* pfc = *(void**)((char*)param_2 + 0x44);
    if (pfc == 0)
        return;
    void* piVar1 = VF(pfc, 0xc, void*(__thiscall*)(void*, unsigned))(pfc, 0xeeee8218);
    if (piVar1 == 0)
        return;
    VF(piVar1, 0x60, void(__thiscall*)(void*, void*))(piVar1, param_3);
}

// @ 0x00993ba0
void WinXHTML::SetFormControlDrawable(int param_2, void* param_3)
{
    char* self = (char*)this;
    if ((unsigned)param_2 > 4)
        return;
    void** slot = (void**)(self + param_2 * 4 + 0xa864);   // mFormCtrlDrawable[param_2]
    void* old = *slot;
    if (param_3 == old)
        return;
    if (param_3 != 0)
        VF(param_3, 0, void(__thiscall*)(void*))(param_3);
    *slot = param_3;
    if (old != 0)
        VF(old, 4, void(__thiscall*)(void*))(old);
}

// @ 0x00993bf0
void WinXHTML::SerUpdate()
{
    CreateScrollbar(1);
    CreateScrollbar(0);
    ((void(__thiscall*)(void*))Win_SerUpdate)(this);
}

// @ 0x00993c10
WinXHTML::WinXHTML()
{
    char* self = (char*)this;
    ((void(__thiscall*)(void*))WinWindow_ctor)(self);
    *(void**)(self + 0x20c) = (void*)0x14463ec;
    *(void**)(self + 0x210) = (void*)0x1446418;
    char* page = self + 0x218;
    *(void**)self = (void*)0x1446590;
    *(void**)(self + 4) = (void*)0x1446470;
    *(void**)(self + 0x20c) = (void*)0x1446440;
    *(void**)(self + 0x210) = (void*)0x144642c;
    *(unsigned char*)(self + 0x214) = 0;
    ((void(__thiscall*)(void*))FUN_008ec790)(page);
    *(int*)(self + 0xa84c) = 3;
    *(void**)(self + 0xa850) = 0;
    *(void**)(self + 0xa854) = 0;
    *(void**)(self + 0xa860) = 0;
    *(void**)(self + 0xa864) = 0;
    *(void**)(self + 0xa868) = 0;
    *(void**)(self + 0xa86c) = 0;
    *(void**)(self + 0xa870) = 0;
    *(void**)(self + 0xa874) = 0;
    *(void**)(self + 0xa888) = 0;
    *(void**)(self + 0xa88c) = 0;
    *(float*)(self + 0xa878) = 0.0f;
    *(float*)(self + 0xa87c) = 0.0f;
    *(float*)(self + 0xa880) = 0.0f;
    *(float*)(self + 0xa884) = 0.0f;
    *(void**)(self + 0xa890) = 0;
    *(void**)(self + 0xa8a0) = 0;
    *(void**)(self + 0xa8a4) = 0;
    *(float*)(self + 0xa8b4) = 0.0f;
    *(float*)(self + 0xa8b8) = 0.0f;
    // Stopwatch::Stopwatch(self+0xa8c0, 5, 1)
    ((void(__thiscall*)(void*, int, int))Stopwatch_ctor)(self + 0xa8c0, 5, 1);
    *(void**)(self + 0xa8d8) = 0;
    *(int*)(self + 0xa8dc) = 0x1002;
    *(int*)(self + 0xa8e0) = 0x1006;
    *(unsigned char*)(self + 0xa8e4) = 0;
    void* ss = XHTML_Style_CreateDefaultStylesheet();
    ((void(__thiscall*)(void*, void*))Page_FUN_008eb830)(page, ss);
    void* root = *(void**)(self + 0x240);
    VF(root, 4, void(__thiscall*)(void*))(root);
    void* a4 = *(void**)(self + 0xa8a4);
    if (a4 != 0) {
        *(void**)(self + 0xa8a4) = 0;
        VF(a4, 4, void(__thiscall*)(void*))(a4);
    }
    void* a0 = *(void**)(self + 0xa8a0);
    if (a0 != 0) {
        *(void**)(self + 0xa8a0) = 0;
        VF(a0, 4, void(__thiscall*)(void*))(a0);
    }
    *(void**)(self + 0xa8a8) = (void*)1;
    void* sb1 = *(void**)(self + 0xa890);
    if (sb1 != 0) {
        *(void**)(self + 0xa890) = 0;
        VF(sb1, 4, void(__thiscall*)(void*))(sb1);
    }
    void* dr1 = *(void**)(self + 0xa88c);
    if (dr1 != 0) {
        *(void**)(self + 0xa88c) = 0;
        VF(dr1, 4, void(__thiscall*)(void*))(dr1);
    }
    *(void**)(self + 0xa894) = (void*)1;
    // ContentWindow
    {
        void* mem = FUN_009512d0(0x20c, 4, "UTFWin/WinXHTML/ContentWindow", FUN_009512c0());
        void* cw = 0;
        if (mem != 0) {
            void* c = ((void*(__thiscall*)(void*))WinWindow_ctor)(mem);
            if (c != 0)
                cw = (char*)c + 4;
        }
        void* old = *(void**)(self + 0xa888);
        if (cw != old) {
            if (cw != 0)
                VF(cw, 0, void(__thiscall*)(void*))(cw);
            *(void**)(self + 0xa888) = cw;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
    // FrameDrawable
    {
        void* mem = FUN_009512d0(0x60, 4, "UTFWin/WinXHTML/FrameDrawable", FUN_009512c0());
        char* fd = 0;
        if (mem != 0)
            fd = (char*)((void*(__thiscall*)(void*))FrameDrawable_ctor)(mem);
        float w = g_kDefaultWidth;
        *(int*)(fd + 0xc) = 5;
        *(float*)(fd + 0x58) = w;
        *(float*)(fd + 0x50) = w;
        *(float*)(fd + 0x54) = w;
        *(float*)(fd + 0x4c) = w;
        *(int*)(fd + 0x10) = (int)0xffccccee;
        void* old = *(void**)(self + 0xa868);
        if (fd != old) {
            VF(fd, 0, void(__thiscall*)(void*))(fd);
            *(void**)(self + 0xa868) = fd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
    // StdDrawable -> drawables 0xa864, 0xa86c, 0xa870, content window
    {
        void* mem = FUN_009512d0(0x7c, 4, "UTFWin/WinXHTML/StdDrawable", FUN_009512c0());
        void* sd = 0;
        if (mem != 0)
            sd = ((void*(__thiscall*)(void*))StdDrawable_ctor)(mem);
        void* old = *(void**)(self + 0xa864);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa864) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        old = *(void**)(self + 0xa86c);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa86c) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        old = *(void**)(self + 0xa870);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa870) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
        old = *(void**)(self + 0xa874);
        if (sd != old) {
            if (sd != 0)
                VF(sd, 0, void(__thiscall*)(void*))(sd);
            *(void**)(self + 0xa874) = sd;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
    // ComboBoxDrawable
    {
        void* mem = FUN_009512d0(0x1c, 4, "UTFWin/WinXHTML/ComboBoxDrawable", FUN_009512c0());
        void* cb = 0;
        if (mem != 0)
            cb = ((void*(__thiscall*)(void*))ComboBoxDrawable_ctor)(mem);
        void* old = *(void**)(self + 0xa878);
        if (cb != old) {
            if (cb != 0)
                VF(cb, 0, void(__thiscall*)(void*))(cb);
            *(void**)(self + 0xa878) = cb;
            if (old != 0)
                VF(old, 4, void(__thiscall*)(void*))(old);
        }
    }
}

// @ 0x00993fa0
bool WinXHTML::Init()
{
    char* self = (char*)this;
    VF(self + 4, 0x7c, void(__thiscall*)(void*, int, int))(self + 4, 0x400, 1);
    void* sb = *(void**)(self + 0xa888);
    if (sb != 0)
        VF(self + 4, 0xd8, void(__thiscall*)(void*, void*))(self + 4, sb);
    CreateScrollbar(1);
    CreateScrollbar(0);
    return ((bool(__thiscall*)(void*))Window_Initialize)(this);
}

// @ 0x00993ff0
bool WinXHTML::Shutdown()
{
    char* self = (char*)this;
    if (*(void**)(self + 0x23c) != 0)
        ((void(__thiscall*)(void*))DocX_RemoveAllChildren)(*(void**)(self + 0x23c));
    ((void(__thiscall*)(void*))Page_NotifyImagesAbandoned)(self + 0x218);
    void* p;
    p = *(void**)(self + 0xa8a0);
    if (p != 0) { *(void**)(self + 0xa8a0) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa8a4);
    if (p != 0) { *(void**)(self + 0xa8a4) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa88c);
    if (p != 0) { *(void**)(self + 0xa88c) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa890);
    if (p != 0) { *(void**)(self + 0xa890) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    p = *(void**)(self + 0xa888);
    if (p != 0)
        VF(self + 4, 0xdc, void(__thiscall*)(void*, void*))(self + 4, p);
    p = *(void**)(self + 0xa888);
    if (p != 0) { *(void**)(self + 0xa888) = 0; VF(p, 4, void(__thiscall*)(void*))(p); }
    if (*(unsigned char*)(self + 0xa8e4) != 0) {
        int msg[5];
        msg[0] = 0x51a1a2e; msg[1] = 0; msg[2] = 0; msg[3] = 0; msg[4] = 0;
        VF(self + 4, 0x114, void(__thiscall*)(void*, int*))(self + 4, msg);
        *(unsigned char*)(self + 0xa8e4) = 0;
    }
    return ((bool(__thiscall*)(void*))Window_Shutdown)(this);
}

// @ 0x009940f0
void WinXHTML::CalculateVisibleArea()
{
    char* self = (char*)this;
    float w = *(float*)(self + 0x90) - *(float*)(self + 0x88);
    float h = *(float*)(self + 0x94) - *(float*)(self + 0x8c);
    *(float*)(self + 0xa878) = 0.0f;
    *(float*)(self + 0xa87c) = 0.0f;
    *(float*)(self + 0xa880) = w;
    *(float*)(self + 0xa884) = h;
    void* sb0 = *(void**)(self + 0xa8a0);
    if (sb0 != 0) {
        void* iface = VF(sb0, 0x10, void*(__thiscall*)(void*))(sb0);
        if ((VF(iface, 0x28, unsigned(__thiscall*)(void*))(iface) & 1) != 0)
            *(float*)(self + 0xa880) = *(float*)(self + 0xa880) - *(float*)(self + 0xa8ac);
    }
    void* sb1 = *(void**)(self + 0xa88c);
    if (sb1 != 0) {
        void* iface = VF(sb1, 0x10, void*(__thiscall*)(void*))(sb1);
        if ((VF(iface, 0x28, unsigned(__thiscall*)(void*))(iface) & 1) != 0)
            *(float*)(self + 0xa884) = *(float*)(self + 0xa884) - *(float*)(self + 0xa89c);
    }
    if (*(float*)(self + 0xa880) < *(float*)(self + 0xa878)
        || *(float*)(self + 0xa884) < *(float*)(self + 0xa87c)) {
        *(float*)(self + 0xa880) = *(float*)(self + 0xa878);
        *(float*)(self + 0xa884) = *(float*)(self + 0xa87c);
    }
}

// @ 0x009941e0
void WinXHTML::SetScrollbarDrawable(int param_2, void* param_3)
{
    char* self = (char*)this;
    void** slot = (void**)(self + param_2 * 0x14 + 0xa890);
    void* old = *slot;
    if (param_3 != old) {
        if (param_3 != 0)
            VF(param_3, 0, void(__thiscall*)(void*))(param_3);
        *slot = param_3;
        if (old != 0)
            VF(old, 4, void(__thiscall*)(void*))(old);
    }
    CreateScrollbar(1);
    CreateScrollbar(0);
}
