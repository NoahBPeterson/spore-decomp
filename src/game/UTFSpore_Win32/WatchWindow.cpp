// src/game/UTFSpore_Win32/WatchWindow.cpp -- migrated from slice(s) s00992480 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/WatchWindow.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float g_negMask;        // 0x013eb8b0  (-x sign flip); 0x013ec4d8 for WatchWindow ctor

// ---- items of slice s00992480 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
char* GetStyleManager(int a);                                        // 0x00885bd0
const void* GetStyle(char* mgr, u32 id, void* base);                 // 0x00894670
float GetTextLayoutMetrics(char* layout, const void* a, int len,
                           const void* style, void* out);            // 0x00890cc0
void  Obj962a10_f(char* p);                                          // 0x00962a10  base ctor
void  Obj962740_f(char* p);                                          // 0x00962740  base dtor
void  RenderCtx_End2D(char* ctx);                                    // 0x0095bb20
char* RenderCtx_Begin2D(char* ctx, void* mode);                      // 0x0095bc10
void  StyleManager_RemoveStyle(char* mgr, const void* st);           // 0x00894970 family
void  WindowLayoutInit(char* layout);                                // 0x00890f50
void  Win_SetFlag(char* win, u32 flag, u8 on);                       // 0x00961760  ?SetFlag@Win
void  Layout_SetStyle(char* layout, const void* style, int a, int b); // 0x0088ffa0
void  TextStyle_ctor(void* ts);                                      // 0x008941d0
void  TextStyle_AssignFamily(void* ts, const u16* family);           // family-name copy
void  StyleManager_AddStyle(char* mgr, u32 id, const void* style);   // 0x00894970
struct TextStyleLocal { u8 raw[0x278];
    float& mfSize()   { return *(float*)(raw + 0x4); }      // base_FontStyle.mfSize
    float& mfWeight() { return *(float*)(raw + 0x8); }      // base_FontStyle.mfWeight
    u32&   mHAlign()  { return *(u32*)(raw + 0x200); }
    u32&   mSmooth()  { return *(u32*)(raw + 0x21c); }
    u32&   mTextWrap(){ return *(u32*)(raw + 0x24c); }
    u32&   mColor()   { return *(u32*)(raw + 0x258); }
};
extern float g_negMask;        // 0x013eb8b0  (-x sign flip); 0x013ec4d8 for WatchWindow ctor
// ---- items of slice s00992480 end

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
