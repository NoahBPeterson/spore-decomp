// Slice s00b694a0 -- 0x00b694a0..0x00b6a200: the floating world-label "event" UI module.
// 0xb694a0/0xb69890/0xb69930/0xb69990/0xb69aa0/0xb69b30 manage the pooled label entries
// (Label/Event objects) of the UI manager at 0x01687348: create them for a world object,
// show/hide the per-kind widget rows, and refresh them.  0xb69bd0 and 0xb69cf0 are
// file-static geometry helpers (register conventions chosen by cl), 0xb6a200 is PostLoad.
// Names are Claude-coined; the layout follows the neighbouring slices s00b66aa0 / s00b6a420 /
// s00b6d3c0.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"
#include <math.h>
#include <string.h>

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// ---- generic vtable-bearing UI object; slot n sits at byte offset 4*n ----
#define VS(n) virtual void vs##n();
struct IV {
    VS(0)  VS(1)  VS(2)  VS(3)  VS(4)  VS(5)  VS(6)  VS(7)
    VS(8)  VS(9)  VS(10) VS(11) VS(12) VS(13) VS(14) VS(15)
    VS(16) VS(17) VS(18) VS(19) VS(20) VS(21) VS(22) VS(23)
    VS(24) VS(25) VS(26) VS(27) VS(28) VS(29) VS(30) VS(31)
    VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47)
    VS(48) VS(49) VS(50) VS(51) VS(52) VS(53) VS(54) VS(55)
    VS(56) VS(57) VS(58) VS(59) VS(60) VS(61) VS(62) VS(63)
    VS(64) VS(65) VS(66)
};
#undef VS

#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// ---- a pool entry (the label/event object); layout from s00b6a420 + the +0x120 block ----
struct Label {
    int     mLink;      // +0x000  pool handle of the annotated object
    IV*     mpObj;      // +0x004
    char    mFlag;      // +0x008
    float   mX;         // +0x00c
    float   mY;         // +0x010
    float   mX2;        // +0x014
    float   mY2;        // +0x018
    float   f1c;        // +0x01c
    float   f20;        // +0x020
    float   f24;        // +0x024
    float   f28;        // +0x028
    float   f2c;        // +0x02c
    float   f30;        // +0x030
    uint8_t b34;        // +0x034
    char    pad35[3];
    float   f38;        // +0x038
    float   f3c;        // +0x03c
    float   f40;        // +0x040
    float   f44;        // +0x044
    float   f48;        // +0x048
    float   f4c;        // +0x04c
    void*   p50;        // +0x050
    void*   p54;        // +0x054
    void*   p58;        // +0x058
    void*   p5c;        // +0x05c
    void*   p60;        // +0x060
    void*   p64;        // +0x064
    void*   p68;        // +0x068
    void*   p6c;        // +0x06c
    void*   p70;        // +0x070
    void*   p74;        // +0x074
    void*   p78;        // +0x078
    void*   p7c;        // +0x07c
    void*   p80;        // +0x080
    void*   p84;        // +0x084
    void*   p88;        // +0x088
    void*   p8c;        // +0x08c
    void*   p90;        // +0x090
    void*   p94;        // +0x094
    void*   p98;        // +0x098
    void*   p9c;        // +0x09c
    void*   pA0;        // +0x0a0
    void*   pA4;        // +0x0a4
    void*   pA8;        // +0x0a8
    void*   pAc;        // +0x0ac
    uint32_t padB0[0x1c];
    IV*     mpWidget;   // +0x120  ref-counted widget (AddRef vt[0], Release vt[4])
    IV*     mpWidget2;  // +0x124
    int     mSel;       // +0x128
    int     mSel2;      // +0x12c
};

// ---- the pooled-entry manager singleton at 0x01687348 ----
struct Mgr {
    char    pad00[0x10];
    int     mCount;                         // +0x10
    int     mStride;                        // +0x14
    int     pad18;                          // +0x18
    float   f1c;                            // +0x1c  (label lifetime)
    float   f20;                            // +0x20
    int     GetPriority();                  // 0x00e31100
    Label*  Next(int* cookie);              // 0x00b72230  (ret 4)
    Label*  Find(int handle);               // 0x00b721d0  (ret 4)
    Label*  At(int handle);                 // 0x00b72210  (ret 4)
};
Mgr* g_pMgr;                                // 0x01687348

// ---- callees ----
void*  __cdecl GetTriggerMgr();             // 0x00b3d4d0
void*  __cdecl FUN_00b3d230();              // 0x00b3d230
struct Checkable { unsigned char Check(); };// 0x00b5ca60
void*  __cdecl WindowManager();             // 0x0067caa0
int    __cdecl GetRecorderState();          // 0x00435e90
void   __cdecl KillSetiEffects(uint32_t id, int state);   // 0x00435ed0
int    __cdecl FUN_00b67c70(IV* o);         // 0x00b67c70
Label* __cdecl FUN_00b68aa0(IV* o, int kind, float f);   // 0x00b68aa0
void*  __cdecl FUN_00b676e0(IV* o);         // 0x00b676e0
int    __cdecl FUN_00b687d0(int handle);    // 0x00b687d0
bool   __cdecl FUN_00b67ef0(void* ctx, Vec2* out, Vec2* out2);  // 0x00b67ef0
void*  __cdecl GetUniverseContext();        // 0x01021080
void*  __cdecl App();                       // 0x0067dd10
Vec2*  __cdecl FUN_007c4180(Vec2* out, const Vec3* p);       // 0x007c4180
Vec4*  __cdecl GetMainWindowArea(Vec4* out);                 // 0x00805ea0
void   __cdecl AnchorWindowToScreen(Vec4* out, void* win, int flags, void* parent);  // 0x008070d0
bool   __cdecl CtxE30(IV* ctx);             // 0x00c88e30
bool   __cdecl ProjectPoint(const Vec3* p, Vec2* out);   // 0x00b67dc0
void*  __cdecl GetLayoutManager();          // 0x00805070
struct LayoutMgr { void* GetWorldMainWindow(uint32_t id); };  // 0x00810620
struct Layout { bool SetParentWin(void* win, int a, uint32_t b); };  // 0x008121b0

extern "C" const void* __cdecl GetCurrentGameMode();         // 0x00b5b800
extern "C" const char DAT_01654c01[], DAT_01654c02[], DAT_01654c10[];

// ---- data ----
extern int   g_idsA[4];                     // 0x0156ae94
extern int   g_idsB[4];                     // 0x0156aea4
extern int   g_widgetIds[4];                // 0x0156aeb4
extern int   g_layout[16];                  // 0x0156aec8
extern float g_1687940, g_1687944, g_1687948;
extern const Vec3 kDir;                     // 0x0156af14 = (0,0,1)
extern float g_20000;                       // 0x01464c14 = 20000.0f
extern float g_half;                        // 0x01471064 = 0.5f
extern float g_0f;                          // 0x01485378 = 0.0f
extern float g_1f;                          // 0x01485720 = 1.0f
extern float g_neg05;                       // 0x013ec488 = -0.5f
extern float g_11f;                         // 0x0140c7a4 = 11.0f
extern float g_neg1;                        // 0x013eb1bc = -1.0f
extern float g_n0;                          // 0x013eb8b0 = -0.0f
extern float g_eps;                         // 0x01464984 = 1.5258789e-05f
extern float g_fltmax;                      // 0x01464980
extern float g_09f;                         // 0x013ec4b4 = 0.9f

// the entry object used by 0xb69aa0/0xb694a0: a widget container
struct WidgetThing {
    IV* mpWidget;                           // +0x120
    IV* mpWidget2;                          // +0x124
    int mSel;                               // +0x128
    int mSel2;                              // +0x12c
};

// the object reached through obj->Cast(0xb033b403): a spatial object with a vtable at +0x34
struct Sub34 { IV mIV; };                   // vtable at object + 0x34

// =====================================================================================
// @ 0x00b694a0
static void FUN_00b694a0(Label* e)
{
    int sel = e->mSel;
    float bx0 = e->mX, by0 = e->mY, bx1 = e->mX, by1 = e->mY;
    IV* w = e->mpWidget;
    if (!e->mFlag) { bx0 = by0 = bx1 = by1 = g_20000; }
    float box[4];
    box[0] = bx0 - g_half;
    box[1] = by0 - g_half;
    box[2] = bx1 + g_half;
    box[3] = by1 + g_half;

    IV* wa = 0;
    IV* wb = 0;
    for (int i = 0; i < 4; i++) {
        IV* a = (IV*)((void*(__thiscall*)(IV*, int, int))VT(w, 0xf0))(w, g_idsA[i], 1);
        ((void(__thiscall*)(IV*, int, int))VT(a, 0x7c))(a, 1, 0);
        if (i == sel) wb = a;
        IV* b = (IV*)((void*(__thiscall*)(IV*, int, int))VT(w, 0xf0))(w, g_idsB[i], 1);
        ((void(__thiscall*)(IV*, int, int))VT(b, 0x7c))(b, 1, 0);
        if (i == sel) wa = b;
    }
    ((void(__thiscall*)(IV*, int, int))VT(wa, 0x7c))(wa, 1, 1);
    ((void(__thiscall*)(IV*, int, int))VT(wb, 0x7c))(wb, 1, 1);
    IV* last;
    if (wa == wb) {
        for (unsigned o = 0; o < 0x10; o += 4) {
            IV* q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wb, 0xf0))(wb, *(int*)((char*)g_widgetIds + o), 1);
            ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        }
        last = w;
    } else {
        int idx = 0;
        for (int i = 0; i < 4; i++) {
            IV* q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wa, 0xf0))(wa, g_widgetIds[g_layout[i * 4]], 1);
            IV* t = (IV*)((void*(__thiscall*)(IV*, int, int))VT(q, 0xf0))(q, 0x7392bd8, 0);
            ((void(__thiscall*)(IV*, int, int))VT(t, 0x7c))(t, 1, 0);
            AnchorWindowToScreen((Vec4*)box, t, 0x300, w);

            Vec4 r1 = *(Vec4*)(((void*(__thiscall*)(IV*))VT(w, 0x38))(w));
            IV* par = (IV*)(((void*(__thiscall*)(IV*))VT(w, 0x10))(w));
            Vec4* r2 = (Vec4*)(((void*(__thiscall*)(IV*))VT(par, 0x38))(par));
            if (r1.x >= r2->x && r1.y >= r2->y && r1.x < r2->z && r1.y < r2->w &&
                r1.z >= r2->x && r1.w >= r2->y && r1.z < r2->z && r1.w < r2->w) {
                idx = i;
                break;
            }
        }
        e->mSel2 = idx;
        int* row = g_layout + idx * 4;
        last = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wa, 0xf0))(wa, g_widgetIds[row[0]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(last, 0x7c))(last, 1, 1);
        IV* q;
        q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wa, 0xf0))(wa, g_widgetIds[row[1]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
        q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wa, 0xf0))(wa, g_widgetIds[row[2]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
        q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wa, 0xf0))(wa, g_widgetIds[row[3]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);

        q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wb, 0xf0))(wb, g_widgetIds[row[0]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wb, 0xf0))(wb, g_widgetIds[row[1]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wb, 0xf0))(wb, g_widgetIds[row[2]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        q = (IV*)((void*(__thiscall*)(IV*, int, int))VT(wb, 0xf0))(wb, g_widgetIds[row[3]], 1);
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
    }
    IV* win = (IV*)((void*(__thiscall*)(IV*, int, int))VT(last, 0xf0))(last, 0x7392bd8, 0);
    e->mpWidget2 = win;
    AnchorWindowToScreen((Vec4*)box, win, 0x300, w);
}

// =====================================================================================
// @ 0x00b69890
void FUN_00b69890(void)
{
    int cookie = g_pMgr->GetPriority();
    Label* e = g_pMgr->Next(&cookie);
    while (e) {
        IV* w = e->mpWidget;
        if (w) {
            if ((((unsigned char(__thiscall*)(IV*))VT(w, 0x28))(w) & 1) == 0) {
                Label* t = g_pMgr->Find(e->mLink);
                if (t) {
                    if (t->mpWidget) {
                        IV* r = t->mpWidget;
                        if (r) {
                            t->mpWidget = 0;
                            ((void(__thiscall*)(IV*))VT(r, 4))(r);
                        }
                    }
                }
            } else {
                FUN_00b694a0(e);
            }
        }
        e = g_pMgr->Next(&cookie);
    }
}

// =====================================================================================
// @ 0x00b69930
void FUN_00b69930(IV* o, float f, char b)
{
    Label* e = FUN_00b68aa0(o, FUN_00b67c70(o), f);
    if (!e) return;
    e->f40 = g_pMgr->f1c;
    if (b) {
        e->f3c = g_fltmax;
        return;
    }
    memcpy(&e->f3c, &g_pMgr->f20, 4);
}

// =====================================================================================
// @ 0x00b69990
void FUN_00b69990(IV* o)
{
    if (!o) return;
    void* trig = GetTriggerMgr();
    int st = *(int*)((char*)trig + 0x2c);
    if (st == 1 || st == 2) return;
    Checkable* c = (Checkable*)FUN_00b3d230();
    if (c->Check()) {
        IV* wm = (IV*)WindowManager();
        IV* win = (IV*)((void*(__thiscall*)(IV*, int))VT(wm, 0x48))(wm, 1);
        if (GetCurrentGameMode() != DAT_01654c02 && GetCurrentGameMode() != DAT_01654c01)
            return;
        if (!win) return;
        int t = ((int(__thiscall*)(IV*))VT(win, 0x1c))(win);
        if (t != 0x36ad4a4 && ((int(__thiscall*)(IV*))VT(win, 0x1c))(win) != 0x625cd52)
            return;
    }
    Label* e = FUN_00b68aa0(o, FUN_00b67c70(o), g_neg1);
    if (!e) return;
    if (GetCurrentGameMode() == DAT_01654c02 && e->f44 == g_0f) {
        void* t = FUN_00b676e0(o);
        if (t && ((bool(__thiscall*)(void*))VT((char*)t + 0x34, 0x58))((char*)t + 0x34)) {
            int r = GetRecorderState();
            KillSetiEffects(0xa47319c2, r);
        }
    }
    e->f44 = g_11f;
}

// =====================================================================================
// @ 0x00b69aa0
void FUN_00b69aa0(IV* o, float x, float y, uint32_t layoutId)
{
    if (!o) return;
    void* trig = GetTriggerMgr();
    int st = *(int*)((char*)trig + 0x2c);
    if (st == 1 || st == 2) return;
    Label* e = FUN_00b68aa0(o, FUN_00b67c70(o), g_neg1);
    if (!e) return;
    if (layoutId) {
        void* win = ((LayoutMgr*)GetLayoutManager())->GetWorldMainWindow(layoutId);
        if (win)
            ((Layout*)e->p50)->SetParentWin(win, 1, 0x5b598fa);
    }
    e->f44 = g_11f;
    e->f48 = x;
    e->f4c = y;
}

// =====================================================================================
// @ 0x00b69b30
void FUN_00b69b30(int handle, IV* widget, int sel)
{
    int h = FUN_00b687d0(handle);
    Label* e = g_pMgr->At(h);
    if (!e) return;
    IV* old = *(IV* volatile*)&e->mpWidget;
    if (e->mpWidget == 0) {
        if (widget != old) {
            if (widget)
                ((void(__thiscall*)(IV*))VT(widget, 0))(widget);
            e->mpWidget = widget;
            if (old)
                ((void(__thiscall*)(IV*))VT(old, 4))(old);
        }
        IV* cur = e->mpWidget;
        if (cur)
            ((void(__thiscall*)(IV*, float, float))VT(cur, 0x70))(cur, g_20000, g_20000);
    }
    e->mSel = sel;
    e->mpWidget2 = 0;
}

// =====================================================================================
// @ 0x00b69bd0  (register convention: result in ECX, point in EAX, out in ESI)
static Vec2* FUN_00b69bd0(Vec2* result, const Vec2* pt, const Vec2* a)
{
    result->x = a->x;
    result->y = a->y;
    float px = pt->x;
    float py = pt->y;
    Vec4 area;
    GetMainWindowArea(&area);
    if (result->y > py) {
        float ox = result->x, oy = result->y;
        result->x = px; result->y = py;
        px = ox; py = oy;
    }
    float dx = result->x - px;
    if (fabsf(dx) >= g_eps) {
        float dy = result->y - py;
        if (fabsf(dy) > g_eps) {
            float slope = dy / dx;
            float nx = -result->y / slope + result->x;
            result->x = nx;
            result->y = 0.0f;
            if (nx < 0.0f) {
                result->y = -nx * slope;
                result->x = 0.0f;
            } else if (nx > area.z) {
                result->y = (area.z - nx) * slope;
                result->x = area.z;
            }
        }
    } else {
        result->y = 0.0f;
    }
    return result;
}

// =====================================================================================
// @ 0x00b69cf0
static bool FUN_00b69cf0(IV* ctx, Vec2* out, Vec2* out2)
{
    if (CtxE30(ctx)) return 0;
    float r[6];
    r[0] = g_neg05; r[1] = g_neg05; r[2] = 0.0f; r[3] = g_half; r[4] = g_half; r[5] = g_1f;
    unsigned flags = *(unsigned*)((char*)ctx + 0x50);
    float* pv;
    if ((flags & 0x10) && !(flags & 0x20))
        pv = r;
    else
        pv = (float*)((void*(__thiscall*)(IV*))VT(ctx, 0x68))(ctx);
    float h = pv[5];

    Vec3* d = (Vec3*)((void*(__thiscall*)(IV*))VT(ctx, 0x2c))(ctx);
    float dx = d->x, dy = d->y, dz = d->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    float ux = dx * inv, uy = dy * inv, uz = dz * inv;
    Vec3 dir; dir.x = ux; dir.y = uy; dir.z = uz;
    Vec3 pos;
    pos.x = ux * h + dx;
    pos.y = uy * h + dy;
    pos.z = uz * h + dz;

    Vec2 cur;
    bool vis = ProjectPoint(&pos, &cur);
    float step = h * 0.14285715f;
    h -= step;
    char cv = vis;
    for (;;) {
        if (cv) {
            Vec4 area;
            GetMainWindowArea(&area);
            out->x = ((cur.x + g_1f) * area.z) * g_half;
            out->y = ((g_1f - cur.y) * area.w) * g_half;
            if (out2) { out2->x = out->x; out2->y = out->y; }
            if (!vis) {
                pos.x = ux * h + dx;
                pos.y = uy * h + dy;
                pos.z = uz * h + dz;
                vis = ProjectPoint(&pos, &cur);
                if (vis) {
                    Vec4 a2;
                    GetMainWindowArea(&a2);
                    Vec2 t;
                    t.x = ((out->x + g_1f) * a2.z) * g_half;
                    t.y = ((g_1f - out->y) * a2.w) * g_half;
                    Vec2* q = FUN_00b69bd0(&t, &cur, (Vec2*)out);
                    out->x = q->x;
                    out->y = q->y;
                }
            }
            if (out2) {
                pos.x = ux * step + dx;
                pos.y = uy * step + dy;
                pos.z = uz * step + dz;
                vis = ProjectPoint(&pos, &cur);
                if (vis) {
                    Vec4 a3;
                    GetMainWindowArea(&a3);
                    out2->x = ((cur.x + g_1f) * a3.z) * g_half;
                    out2->y = ((g_1f - cur.y) * a3.w) * g_half;
                }
            }
            return cv;
        }
        if (h <= 0.0f) return 0;
        pos.x = ux * h + dx;
        pos.y = uy * h + dy;
        pos.z = uz * h + dz;
        void* app = App();
        char* cam = (char*)((void*(__thiscall*)(void*))VT(app, 0x58))(app);
        float z = (((*(float*)(cam + 0x48) * pos.x + *(float*)(cam + 0x68) * pos.z) +
                    *(float*)(cam + 0x58) * pos.y) + *(float*)(cam + 0x78)) * g_1687948;
        float y = (((*(float*)(cam + 0x44) * pos.x + *(float*)(cam + 0x64) * pos.z) +
                    *(float*)(cam + 0x54) * pos.y) + *(float*)(cam + 0x74)) * g_1687944;
        float x = (((*(float*)(cam + 0x40) * pos.x + *(float*)(cam + 0x60) * pos.z) +
                    *(float*)(cam + 0x50) * pos.y) + *(float*)(cam + 0x70)) * g_1687940;
        float s = z + y + x;
        if (0.0f > s) { cv = 0; continue; }
        Vec2 t;
        FUN_007c4180(&t, &pos);
        if (!(g_1f >= t.x && t.x >= g_neg1 && g_1f >= t.y && t.y >= g_neg1)) { cv = 0; continue; }
        cur = t;
        cv = 1;
    }
}

// =====================================================================================
// @ 0x00b6a200
bool FUN_00b6a200(IV* o, Vec2* out)
{
    IV* c;
    if (o)
        c = (IV*)((void*(__thiscall*)(IV*, uint32_t))VT(o, 0xc))(o, 0xb033b403);
    else
        c = 0;
    if (!GetUniverseContext()) {
        char* p = c ? (char*)c + 0x34 : 0;
        if (GetCurrentGameMode() == DAT_01654c10)
            return FUN_00b69cf0((IV*)p, out, 0);
        return FUN_00b67ef0(p, out, 0);
    }
    char* s = (char*)c + 0x34;
    float h = *(float*)((char*)((void*(__thiscall*)(char*))VT(s, 0x68))(s) + 0x14) * g_09f;
    Vec3* d = (Vec3*)((void*(__thiscall*)(char*))VT(s, 0x2c))(s);
    Vec3 pos;
    pos.x = kDir.x * h + d->x;
    pos.y = kDir.y * h + d->y;
    pos.z = kDir.z * h + d->z;
    void* app = App();
    char* cam = (char*)((void*(__thiscall*)(void*))VT(app, 0x58))(app);
    Vec2 q;
    FUN_007c4180(&q, &pos);
    float f0 = (((*(float*)(cam + 0x68) * pos.z + *(float*)(cam + 0x58) * pos.y) +
                 *(float*)(cam + 0x48) * pos.x) + *(float*)(cam + 0x78)) * g_1687948;
    float f1 = (((*(float*)(cam + 0x60) * pos.z + *(float*)(cam + 0x50) * pos.y) +
                 *(float*)(cam + 0x40) * pos.x) + *(float*)(cam + 0x70)) * g_1687940;
    float f2 = (((*(float*)(cam + 0x64) * pos.z + *(float*)(cam + 0x54) * pos.y) +
                 *(float*)(cam + 0x44) * pos.x) + *(float*)(cam + 0x74)) * g_1687944;
    float sum = f0 + f1 + f2;
    if (sum < 0.0f) return false;
    Vec4 area;
    GetMainWindowArea(&area);
    out->x = ((q.x + g_1f) * area.z) * g_half;
    out->y = ((g_1f - q.y) * area.w) * g_half;
    return true;
}
