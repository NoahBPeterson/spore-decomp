// slice s00992480 -- EA UTFWinControls / UTFWinExtras widget glue:
//   WatchGraph::OnTick / scalar-deleting-dtor, WatchWindow (Clear / ctor / UpdateSize / OnTick),
//   WinXHTML (dtor / DoMessage / OnCtrlValueChanged / OnRebuild / SetScrollPosition) and the
//   small offset-based accessor/mutator helpers between them.
//
// This range is VS2008 (cl 15.00) UTFWin code.  Objects are modelled as a raw byte base plus a
// fixed offset, exactly as the original does; UTFWin's IWindow/IScrollbarDrawable interfaces are
// called through their vtable slots (offsets noted inline).  Members that the original reaches at
// large offsets (e.g. +0xa84c, +0xa8b4) are the WinXHTML scrollbar/scroll-position state.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;

static inline u32  ld32(char* b, u32 off) { return *(u32*)(b + off); }
static inline void st32(char* b, u32 off, u32 v) { *(u32*)(b + off) = v; }
static inline u8   ld8 (char* b, u32 off) { return *(u8*)(b + off); }
static inline void st8 (char* b, u32 off, u8 v) { *(u8*)(b + off) = v; }
static inline float ldf(char* b, u32 off) { return *(float*)(b + off); }
static inline void stf (char* b, u32 off, float v) { *(float*)(b + off) = v; }

// ---- callees -------------------------------------------------------------------------------------
char* GetStyleManager(int a);                                        // 0x00885bd0
const void* GetStyle(char* mgr, u32 id, void* base);                 // 0x00894670
float GetTextLayoutMetrics(char* layout, const void* a, int len,
                           const void* style, void* out);            // 0x00890cc0
void  IntrusiveList_dtor(char* list);                                // 0x00620230
void  Obj962a10_f(char* p);                                          // 0x00962a10  base ctor
void  Obj962740_f(char* p);                                          // 0x00962740  base dtor
void  MultiHeapObject_delete(void* p);                               // 0x00951330
void  FUN_00991f90(char* p);                                         // WatchGraph::Clear
void  FUN_00950bb0(char* p);                                         // base message handler
void  DestroyFormControls(char* doc);                                // 0x008e2890
void  RemoveAllChildren(char* doc);                                  // 0x008e2930
void  Page_dtor(char* page);                                         // 0x008ec810
void  Page_NotifyImagesAbandoned(char* page);                        // 0x008eb7a0
void  Page_Render(char* page, char* batch, const void* a, const void* b); // 0x008eb870
void  RenderCtx_End2D(char* ctx);                                    // 0x0095bb20
char* RenderCtx_Begin2D(char* ctx, void* mode);                      // 0x0095bc10
void  FUN_00571e80(char* sw);                                        // Stopwatch::Restart
float Stopwatch_GetElapsedTimeFloat(char* sw);                       // 0x005ff1a0
void  RefObj_release(char* p);                                       // an IRefCount::Release (vt+4)
void  StyleManager_RemoveStyle(char* mgr, const void* st);           // 0x00894970 family
void  WindowLayoutInit(char* layout);                                // 0x00890f50
void  Win_SetFlag(char* win, u32 flag, u8 on);                       // 0x00961760  ?SetFlag@Win
void  Layout_SetStyle(char* layout, const void* style, int a, int b); // 0x0088ffa0
void  TextStyle_ctor(void* ts);                                      // 0x008941d0
void  TextStyle_AssignFamily(void* ts, const u16* family);           // family-name copy
void  StyleManager_AddStyle(char* mgr, u32 id, const void* style);   // 0x00894970

// Backing storage for the local TextStyle built in the WatchWindow ctor (local_278 == 0x278 bytes).
struct TextStyleLocal { u8 raw[0x278];
    float& mfSize()   { return *(float*)(raw + 0x4); }      // base_FontStyle.mfSize
    float& mfWeight() { return *(float*)(raw + 0x8); }      // base_FontStyle.mfWeight
    u32&   mHAlign()  { return *(u32*)(raw + 0x200); }
    u32&   mSmooth()  { return *(u32*)(raw + 0x21c); }
    u32&   mTextWrap(){ return *(u32*)(raw + 0x24c); }
    u32&   mColor()   { return *(u32*)(raw + 0x258); }
};

// Global "negate" float used to build the negative span in the XHTML render rects.
extern float g_negMask;        // 0x013eb8b0  (-x sign flip); 0x013ec4d8 for WatchWindow ctor

// thiscall-ABI helper prototypes for the vtable slots and Page methods reached with `this` in ecx
// and their real arguments pushed on the stack.
struct PageOps        { void __thiscall SetSelectionRange(int a, int b); };
struct StyleOps       { void __thiscall AddStyle(u32 id, const void* style); };

// Plain __thiscall slot prototypes used with an explicit `this` (keeps ecx/edx free exactly like the
// original, which uses `this` in ecx and the value pushed on the stack).
typedef void (__thiscall *SlotSetInt)(char* self, int v);
typedef int  (__thiscall *SlotGetInt)(char* self);

// ==================================================================================================
// 0x00992480  EA::UTFWinControls::WatchGraph::OnTick
// ==================================================================================================
// @ 0x00992480
u8 __fastcall WatchGraph_OnTick(char* self, int)
{
    // Rings the history buffer: for each live history node, sample the graph value into the ring
    // at index mRingIndex (self+0x224), then advance the ring and repaint.
    char* head = (char*)ld32(self, 0x20c);
    char* node = head ? head - 4 : 0;
    char* end  = (self + 0x20c) ? self + 0x20c - 4 : 0;
    while (node != end) {
        if (ld32(node, 0x14) != 0) {
            float v = (*(float(__fastcall**)(char*))(*(u32*)node + 4))(node);
            float* dest = (float*)ld32(node, 0x14);
            dest[ld32(self, 0x224)] = v;
        }
        char* next = (char*)ld32(node, 4);
        node = next ? next - 4 : 0;
    }
    u32 idx = ld32(self, 0x224) + 1;
    st32(self, 0x224, idx);
    if (idx >= ld32(self, 0x220)) st32(self, 0x224, 0);
    (*(void(__fastcall**)(char*))(*(u32*)(self + 4) + 0x90))(self + 4);
    return 1;
}

// ==================================================================================================
// 0x00992550  EA::UTFWinControls::WatchGraph::`scalar deleting destructor'
// ==================================================================================================
// @ 0x00992550
void* __fastcall WatchGraph_scalarDtor(char* self, int, u8 flags)
{
    st32(self, 0, 0x1446078u);            // vtbl WatchGraph
    st32(self, 4, 0x1445f58u);
    FUN_00991f90(self);
    IntrusiveList_dtor(self + 0x20c);
    Obj962740_f(self);
    if (flags & 1) MultiHeapObject_delete(self);
    return self;
}

// ==================================================================================================
// 0x00992600  EA::UTFWinControls::WatchWindow::Clear
// ==================================================================================================
// @ 0x00992600
void __fastcall WatchWindow_Clear(char* self)
{
    char* sentinel = self + 0x20c;
    char* cur = *(char**)sentinel;
    while (*(char**)(sentinel + 4) != sentinel) {
        char* obj = cur ? cur - 4 : 0;
        char* link = *(char**)cur;
        *(char**)(link + 4) = sentinel;
        *(char**)sentinel = *(char**)link;
        if (cur != sentinel) {
            *(char**)(cur + 4) = 0;
            *(char**)cur = 0;
        }
        if (obj) (*(void(__fastcall**)(char*))(*(u32*)obj + 0))(obj);
        cur = *(char**)sentinel;
    }
}

// ==================================================================================================
// 0x00992650  EA::UTFWinControls::WatchWindow::WatchWindow  (constructor)
// ==================================================================================================
// @ 0x00992650
void* __fastcall WatchWindow_ctor(char* self, int)
{
    Obj962a10_f(self);                                  // UTFWin::Window::Window()
    char* win = self + 4;
    char* ring = self + 0x20c;
    st32(self, 0, 0x14462b0u);                          // vtbl WatchWindow
    st32(win, 0, 0x1446190u);
    *(char**)(ring + 4) = ring;                         // sentinel self-link
    *(char**)ring = ring;
    stf(self, 0x214, 0.0f);
    stf(self, 0x218, 0.0f);
    stf(self, 0x21c, g_negMask);                        // [0x13ec4d8]
    *(u8*)(self + 0x220) = 1;
    WindowLayoutInit(self + 0x224);                     // FUN_00890f50
    WindowLayoutInit(self + 0x5a0);                     // FUN_00890f50
    st32(self, 0x91c, 0x863d517fu);
    st32(self, 0x920, 0x6e8a9dc4u);
    Win_SetFlag(win, 0x10, 1);
    char* mgr = GetStyleManager(1);
    if (mgr) {
        TextStyleLocal ts;                              // local_278 (TextStyle)
        TextStyle_ctor(&ts);
        TextStyle_AssignFamily(&ts, (const u16*)0x1441ca0);   // L"Trebuchet MS"
        ts.mfSize()   = 9.0f;      // [0x13f8734]
        ts.mHAlign()  = 2;
        ts.mfWeight() = 700.0f;    // [0x142eae0]
        ts.mSmooth()  = 1;
        ts.mTextWrap() = 0;
        ts.mColor()   = 0xffa7b8ffu;
        if (!GetStyle(mgr, 0x6fb342b7u, 0)) StyleManager_AddStyle(mgr, 0x6fb342b7u, &ts);
        ts.mHAlign() = 0;
        ts.mColor()  = 0xffffffffu;
        if (!GetStyle(mgr, 0x6fb342b8u, 0)) StyleManager_AddStyle(mgr, 0x6fb342b8u, &ts);
        Layout_SetStyle(self + 0x224, GetStyle(mgr, 0x6fb342b7u, 0), 0, 0);   // FUN_0088ffa0
        Layout_SetStyle(self + 0x5a0, GetStyle(mgr, 0x6fb342b8u, 0), 0, 0);
    }
    Win_SetFlag(win, 8, 1);
    return self;
}

// ==================================================================================================
// 0x00992830  WatchWindow teardown helper (vtable reset + Clear + style unregister + base dtor)
// ==================================================================================================
// @ 0x00992830
void __fastcall FUN_00992830(char* self, int)
{
    st32(self, 0, 0x14462b0u);
    st32(self, 4, 0x1446190u);
    WatchWindow_Clear(self);
    char* mgr = GetStyleManager(1);
    if (mgr) {
        const void* st = GetStyle(mgr, 0x6fb342b7u, 0);
        if (st) StyleManager_RemoveStyle(mgr, st);
    }
    Obj962740_f(self);
}

// ==================================================================================================
// 0x009928c0  EA::UTFWinControls::WatchWindow::UpdateSize
// ==================================================================================================
// @ 0x009928c0
void __fastcall WatchWindow_UpdateSize(char* self)
{
    char* mgr = GetStyleManager(1);
    if (!mgr) return;

    char* win = self + 4;
    float* r = (float*)(*(void*(__fastcall**)(char*))(*(u32*)win + 0x34))(win);
    float rx = r[0], ry = r[1];
    (void)rx;

    const void* style = GetStyle(mgr, 0x6fb342b7u, 0);
    u8 metrics[16];
    GetTextLayoutMetrics(self + 0x224, (const void*)0x13fa1d4, 1, style, metrics);
    stf(self, 0x214, *(float*)(metrics + 0xc) - *(float*)(metrics + 0x10));

    u32 count = 0;
    for (char* p = *(char**)(self + 0x20c); p != self + 0x20c; p = *(char**)p) ++count;
    float total = (float)(i32)count * (*(float*)(metrics + 0xc) - *(float*)(metrics + 0x10))
                + *(float*)(metrics + 0x10) + 10.0f;
    stf(self, 0x218, 0.0f);
    float maxW = 0.0f;
    for (;;) {
        char* node = *(char**)(self + 0x20c);
        char* obj = node ? node - 4 : 0;
        char* lim = (self + 0x20c) ? self + 0x20c - 4 : 0;
        if (obj == lim) break;
        u16* s = (u16*)ld32(obj, 0xc);
        u16* q = s;
        while (*q) ++q;
        float w = GetTextLayoutMetrics(self + 0x224, s, (int)(q - s), style, metrics);
        if (w > maxW) maxW = w;
        char* nx = *(char**)(obj + 4);
        (void)nx;
        break;
    }
    stf(self, 0x218, maxW);

    float fw = (float)(i32)(maxW < 0 ? maxW - 0.5f : maxW + 0.5f);
    float fh = (float)(i32)(total < 0 ? total - 0.5f : total + 0.5f);
    float sz[2];
    sz[0] = rx + fw + 15.0f;
    sz[1] = ry + fh;
    (*(void(__fastcall**)(char*, void*))(*(u32*)win + 0x60))(win, sz);
}

// ==================================================================================================
// 0x00992aa0  WatchWindow::OnRebuild -- Begin2D, draw the two label rows, End2D
// ==================================================================================================
// @ 0x00992aa0
u8 __fastcall FUN_00992aa0(char* self, int, char* ctx)
{
    char* batch = RenderCtx_Begin2D(ctx, 0);
    (*(void(__fastcall**)(char*, u32))(*(u32*)batch + 4))(batch, ld32(self, 0x91c));

    float dy = ldf(self, 0xa4) - ldf(self, 0x9c);
    float dx = ldf(self, 0xa0) - ldf(self, 0x98);
    (*(void(__fastcall**)(char*, float, float, int))(*(u32*)batch + 0x38))
        (batch, dx, dy, 0);
    (*(void(__fastcall**)(char*, u32))(*(u32*)batch + 4))(batch, ld32(self, 0x920));

    float ndy = -dy;
    float ndx = -dx;
    (*(void(__fastcall**)(char*, float, float, float, int))(*(u32*)batch + 0x1c))
        (batch, ndx, ndy, 1.0f, 0);
    (*(void(__fastcall**)(char*, int))(*(u32*)batch + 4))(batch, -1);

    char* mgr = GetStyleManager(1);
    if (mgr) {
        const void* st1 = GetStyle(mgr, 0x6fb342b7u, 0);
        const void* st2 = GetStyle(mgr, 0x6fb342b8u, 0);
        float rowH = ldf(self, 0x214);
        float gap  = 10.0f;    // [0x1486110]
        char* ring = self + 0x20c;
        char* cur  = *(char**)ring;
        char* endp = ring ? ring - 4 : 0;
        char* node;
        while ((node = cur ? cur - 4 : 0) != endp) {
            u16* s = (u16*)ld32(node, 0xc);
            u16* q = s;
            while (*q) ++q;
            (*(void(__fastcall**)(char*, float, float, float, float, u16*, void*, int))
                (*(u32*)batch + 0x28))(batch, rowH + gap, ldf(self, 0x218) + gap,
                                       rowH, ldf(self, 0x21c) + rowH, s, (void*)st1, 0);
            float rx = ldf(self, 0x218);
            float base = ldf(self, 0x21c);
            float top = rowH;
            (*(void(__fastcall**)(char*, float, void*, void*, void*, int))
                (*(u32*)node + 4))(node, rowH + base, (void*)st2, (void*)batch,
                                   (void*)(size_t)0, 0);
            (void)rx; (void)top;
            char* nx = *(char**)(node + 4);
            cur = nx ? nx : 0;
            if (cur) cur += 4;
        }
    }
    RenderCtx_End2D(ctx);
    return 1;
}

// ==================================================================================================
// 0x00992d10  EA::UTFWinControls::WatchWindow::OnTick
// ==================================================================================================
// @ 0x00992d10
u8 __fastcall WatchWindow_OnTick(char* self, int)
{
    if (ld8(self, 0x220)) {
        WatchWindow_UpdateSize(self);
        st8(self, 0x220, 0);
    }
    char* win = self + 4;
    (*(void(__fastcall**)(char*))(*(u32*)win + 0x90))(win);
    return 1;
}

// ==================================================================================================
// 0x00992dc0  WinXHTML set/clear a bit in the flags word at +0xa84c
// ==================================================================================================
// @ 0x00992dc0
void __fastcall FUN_00992dc0(char* self, int, u32 mask, u8 set)
{
    if (set) st32(self, 0xa84c, ld32(self, 0xa84c) | mask);
    else     st32(self, 0xa84c, ld32(self, 0xa84c) & ~mask);
}

// ==================================================================================================
// 0x00992e00  WinXHTML set the selection range (+0xa858/+0xa85c) and repaint
// ==================================================================================================
// @ 0x00992e00
void __fastcall FUN_00992e00(char* self, int, i32 a, i32 b)
{
    if (a != (i32)ld32(self, 0xa858) || b != (i32)ld32(self, 0xa85c)) {
        st32(self, 0xa85c, (u32)b);
        st32(self, 0xa858, (u32)a);
        ((PageOps*)(self + 0x218))->SetSelectionRange(a, b);
        char* win = self + 4;
        (*(void(__fastcall**)(char*))(*(u32*)win + 0x90))(win);
    }
}

// ==================================================================================================
// 0x00992e60  WinXHTML set horizontal scroll value (+0xa8dc) via the scrollbar drawable
// ==================================================================================================
// @ 0x00992e60
void __fastcall FUN_00992e60(char* self, int, i32 v)
{
    if (v != (i32)ld32(self, 0xa8dc)) {
        char* win = self + 4;
        i32 cur = ((SlotGetInt)(*(u32*)win + 0x24))(win);
        if (cur == (i32)ld32(self, 0xa8dc)) {
            ((SlotSetInt)(*(u32*)win + 0x78))(win, v);
        }
        st32(self, 0xa8dc, (u32)v);
    }
}

// ==================================================================================================
// 0x00992ea0  WinXHTML set vertical scroll value (+0xa8e0) via the scrollbar drawable
// ==================================================================================================
// @ 0x00992ea0
void __fastcall FUN_00992ea0(char* self, int, i32 v)
{
    if (v != (i32)ld32(self, 0xa8e0)) {
        char* win = self + 4;
        i32 cur = ((SlotGetInt)(*(u32*)win + 0x24))(win);
        if (cur == (i32)ld32(self, 0xa8e0)) {
            ((SlotSetInt)(*(u32*)win + 0x78))(win, v);
        }
        st32(self, 0xa8e0, (u32)v);
    }
}

// ==================================================================================================
// 0x00992ee0  WinXHTML show/hide a helper window (dispatch message 0x051a1a2e)
// ==================================================================================================
// @ 0x00992ee0
void __fastcall FUN_00992ee0(char* self, int, i32 show)
{
    if (show != 0 || ld8(self, 0xa8e4) != 0) {
        char* win = self + 4;
        u32 fn = ld32(win, 0x114);
        void* msg[5];
        msg[0] = 0; msg[1] = 0; msg[2] = 0; msg[3] = 0; msg[4] = (void*)(size_t)show;
        ((void(__fastcall*)(char*, void*))fn)(win, msg);
        st8(self, 0xa8e4, show != 0);
    }
}

// ==================================================================================================
// 0x00993000  EA::UTFWinExtras::WinXHTML::~WinXHTML
// ==================================================================================================
// @ 0x00993000
void __fastcall WinXHTML_dtor(char* self, int)
{
    char* doc = (char*)ld32(self, 0x23c);
    st32(self, 0, 0x1446590u);                  // vtbl WinXHTML
    st32(self, 4, 0x1446470u);
    st32(self, 0x20c, 0x1446440u);
    st32(self, 0x210, 0x144642cu);
    if (doc) {
        DestroyFormControls(doc);
        st32(doc, 0x38, 0);
        st32(doc, 0x3c, 0);
    }
    // release two lists of intrusive objects (two 0x14-stride slots below +0xa8b4)
    char* p = self + 0xa8b4;
    for (int i = 1; i >= 0; --i) {
        char* a = *(char**)(p - 0x10);
        p -= 0x14;
        if (a) RefObj_release(a);
        char* b = *(char**)p;
        if (b) RefObj_release(b);
    }
    char* s1 = (char*)ld32(self, 0xa888);
    if (s1) RefObj_release(s1);
    char* q = self + 0xa878;
    for (int i = 4; i >= 0; --i) {
        char* a = *(char**)(q - 4);
        q -= 4;
        if (a) RefObj_release(a);
    }
    Page_dtor(self + 0x218);
    st32(self, 0x210, 0x13eb938u);              // GmeEditorResBase vtable
    st32(self, 0x20c, 0x13eb938u);
    Obj962740_f(self);
}

// ==================================================================================================
// 0x00993130  EA::UTFWinExtras::WinXHTML::DoMessage
// ==================================================================================================
// @ 0x00993130
u8 __fastcall WinXHTML_DoMessage(char* self, int, char* msg)
{
    if (ld32(msg, 8) != (i32)0x8ef0c8dd) {
        FUN_00950bb0(msg);
        return 0;
    }
    float nv;
    char* a = (char*)ld32(self, 0xa88c);
    if (a) nv = (float)(*(i32(__fastcall**)(char*))(*(u32*)a + 0x28))(a);
    else   nv = 0.0f;
    float nh;
    char* b = (char*)ld32(self, 0xa8a0);
    if (b) nh = (float)(*(i32(__fastcall**)(char*))(*(u32*)b + 0x28))(b);
    else   nh = 0.0f;

    if (nv != ldf(self, 0xa8b4) || nh != ldf(self, 0xa8b8)) {
        char* sb = (char*)ld32(self, 0xa888);
        stf(self, 0xa8b4, nv);
        stf(self, 0xa8b8, nh);
        // +0x64: thiscall, takes -nv and -nh pushed as two floats.
        (*(void(__fastcall**)(char*, int, float, float))(*(u32*)sb + 0x64))(sb, 0, -nv, -nh);
        char* win = self + 4;
        (*(void(__fastcall**)(char*))(*(u32*)win + 0x90))(win);
    }
    return 1;
}

// ==================================================================================================
// 0x00993200  WinXHTML vertical-scroll helper (pass sub-line offset to the scrollbar drawable)
// ==================================================================================================
// @ 0x00993200
u8 __fastcall FUN_00993200(char* self, int, i32, i32, i32, i32 lineOffset)
{
    char* sb = (char*)ld32(self, 0xa8a0);
    if (sb) {
        u32 vt = *(u32*)sb;
        i32 range = (*(i32(__fastcall**)(char*, int))(vt + 0x28))(sb, 1);
        i32 v = lineOffset + ((lineOffset >> 31) & 3);
        (*(void(__fastcall**)(char*, int))(vt + 0x24))(sb, range - (v >> 2));
    }
    return 1;
}

// ==================================================================================================
// 0x00993240  EA::UTFWinExtras::WinXHTML::OnCtrlValueChanged
// ==================================================================================================
// @ 0x00993240
u8 __fastcall WinXHTML_OnCtrlValueChanged(char* self, int, u32 id, char* ctrl)
{
    if (id == 0x344a712u) {
        char* o = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)ctrl + 0xb4))(ctrl, 0x344a0b7u, 0);
        if (o) {
            char* p = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)o + 0xc))(o, 0x344a654u, 0);
            if (p) {
                char* t = (char*)ld32(p, 8);
                if (t) {
                    (*(void(__fastcall**)(char*, int, void*))(*(u32*)t + 0x24))(t, 5, (void*)0);
                }
            }
        }
        return 1;
    }
    if (id >= 0xcf454afau && id <= 0xcf454afbu) return 1;
    return 0;
}

// ==================================================================================================
// 0x009932c0  WinXHTML control-click handler (0x344a710/0x344a711 -> scroll notification)
// ==================================================================================================
// @ 0x009932c0
u8 __fastcall FUN_009932c0(char* self, int, char* ctrl, u32 id)
{
    char* o = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)ctrl + 0xb4))(ctrl, 0x344a0b7u, 0);
    if (!o) return 0;
    char* p = (char*)(*(void*(__fastcall**)(char*, u32, int))(*(u32*)o + 0xc))(o, 0x344a654u, 0);
    if (!p) return 0;
    char* t = (char*)ld32(p, 8);
    if (!t) return 0;
    if (id != 0x344a710u && id != 0x344a711u) return 0;
    int which = (id == 0x344a710u) ? 2 : 3;
    if (!((ld8(self, 0xa84c) & which) && (i32)ld32(self, 0xa8d8) == (i32)(size_t)t
          && Stopwatch_GetElapsedTimeFloat(self + 0xa8c0) <= 0.75f)) {
        (*(void(__fastcall**)(char*, int, void*))(*(u32*)t + 0x24))(t, which, (void*)0);
    }
    st32(self, 0xa8d8, (u32)(size_t)t);
    FUN_00571e80(self + 0xa8c0);
    return 1;
}

// ==================================================================================================
// 0x00993390  WinXHTML drop all children and abandon images
// ==================================================================================================
// @ 0x00993390
void __fastcall FUN_00993390(char* self, int)
{
    typedef void (__fastcall *Fn)(char*);
    char* doc = *(char**)(self + 0x23c);
    if (doc) ((Fn)RemoveAllChildren)(doc);
    ((Fn)Page_NotifyImagesAbandoned)(self + 0x218);
}

// ==================================================================================================
// 0x009933b0  EA::UTFWinExtras::WinXHTML::OnRebuild
// ==================================================================================================
// @ 0x009933b0
u8 __fastcall WinXHTML_OnRebuild(char* self, int, char* ctx)
{
    char* batch = RenderCtx_Begin2D(ctx, 0);

    float neg = g_negMask;                     // [0x13eb8b0]
    float w = ldf(self, 0x90) - ldf(self, 0x88);
    float h = ldf(self, 0x94) - ldf(self, 0x8c);

    float src[4];                              // first local rect: 0,0,w,h
    src[0] = 0.0f;
    src[1] = 0.0f;
    src[2] = ldf(self, 0x90) - ldf(self, 0x88);
    src[3] = ldf(self, 0x94) - ldf(self, 0x8c);

    float sx = ldf(self, 0xa8b4) * -1.0f;
    float sy = ldf(self, 0xa8b8) * -1.0f;
    (void)neg;

    float dst[4];                              // second local rect: sx,sy,sx+w,sy+h
    dst[0] = sx;
    dst[1] = sy;
    dst[2] = w + sx;
    dst[3] = h + sy;

    Page_Render(self + 0x218, batch, dst, src);
    RenderCtx_End2D(ctx);
    return 1;
}

// ==================================================================================================
// 0x00993490  EA::UTFWinExtras::WinXHTML::SetScrollPosition
// ==================================================================================================
// @ 0x00993490
void __fastcall WinXHTML_SetScrollPosition(char* self, int, float* pos)
{
    if (ldf(self, 0xa8b4) != pos[0] || ldf(self, 0xa8b8) != pos[1]) {
        char* vb = (char*)ld32(self, 0xa8a0);
        stf(self, 0xa8b4, pos[0]);
        stf(self, 0xa8b8, pos[1]);
        if (vb) (*(void(__fastcall**)(char*, int, int))(*(u32*)vb + 0x24))(vb, (i32)pos[1], 0);
        char* hb = (char*)ld32(self, 0xa88c);
        if (hb) (*(void(__fastcall**)(char*, int, int))(*(u32*)hb + 0x24))(hb, (i32)pos[0], 0);
        char* win = self + 4;
        (*(void(__fastcall**)(char*))(*(u32*)win + 0x90))(win);
    }
}
