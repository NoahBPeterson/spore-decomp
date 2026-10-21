// Slice s00f07c90 - cSPUINewProgressBar (tribe progress bar) and its helpers.
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast region.
//
// 0x00f07fd0 is the per-frame progress update; 0xf084b0..0xf08750 index "days"
// (0x4e0-byte day records, each a pair of 0x44-byte entry lists at +4 and +0x170)
// via a counter measured as day*1000 + slot; the 0xf08850..0xf08b70 group drives
// the five list panels through the g_16c7d90 UI state block.
#include "types.h"
#include <math.h>

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

// ---------------------------------------------------------------------------
// UI window interface: vtable slots by byte offset (matches slice s00f0ac40).
// ---------------------------------------------------------------------------
struct Wnd {
    virtual void p00();                     // 0x00
    virtual void p04();                     // 0x04
    virtual void p08();                     // 0x08
    virtual Wnd* QueryInterface(uint id);   // 0x0c
    virtual Wnd* GetParent();               // 0x10
    virtual void p14();                     // 0x14
    virtual void p18();                     // 0x18
    virtual void p1c();                     // 0x1c
    virtual void p20();                     // 0x20
    virtual bool GetProp(uint id, void** o);// 0x24
    virtual int  Slot28();                  // 0x28
    virtual void* Query();                  // 0x2c
    virtual void p30();                     // 0x30
    virtual float* GetArea();               // 0x34
    virtual void p38();                     // 0x38
    virtual void p3c();                     // 0x3c
    virtual void p40();                     // 0x40
    virtual void p44();                     // 0x44
    virtual char Flag48();                  // 0x48
    virtual void p4c();                     // 0x4c
    virtual void p50();                     // 0x50
    virtual void p54();                     // 0x54
    virtual void p58();                     // 0x58
    virtual float* Slot5c(void* a);         // 0x5c (Dir or SetFlags)
    virtual void SetText(const void* s, int b);  // 0x60
    virtual void SetPos(float x, float y);  // 0x64
    virtual void SetFontStyle(uint v);      // 0x68
    virtual void GetRect(float* out);       // 0x6c
    virtual void p70();                     // 0x70
    virtual void p74();                     // 0x74
    virtual void p78();                     // 0x78
    virtual void SetVisible(int a, int b);  // 0x7c
    virtual void SetImage(const void* p);   // 0x80
    virtual void TextExtent(float* out, int a, int b);  // 0x84 (used as (out,0,1))
    virtual void p88();                     // 0x88
    virtual void p8c();                     // 0x8c
    virtual void p90();                     // 0x90
    virtual void p94();                     // 0x94
    virtual void p98();                     // 0x98
    virtual void p9c();                     // 0x9c
    virtual void pa0();                     // 0xa0
    virtual void pa4();                     // 0xa4
    virtual void pa8();                     // 0xa8
    virtual void pac();                     // 0xac
    virtual void pb0();                     // 0xb0
    virtual void pb4();                     // 0xb4
    virtual Wnd* GetUIWindow(uint id);      // 0xb8
    virtual void AddRef();                  // 0xbc
    virtual void Release();                 // 0xc0
    virtual void GetLocalPos(float* out);   // 0xc4
    virtual void pC8();                     // 0xc8
    virtual void pCc();                     // 0xcc
    virtual void pD0();                     // 0xd0
    virtual void pD4();                     // 0xd4
    virtual void pD8();                     // 0xd8
    virtual void pDc();                     // 0xdc
    virtual void pE0();                     // 0xe0
    virtual void pE4();                     // 0xe4
    virtual void pE8(void* p);              // 0xe8
};

struct IRef { virtual void dtor(); };       // 0x04
struct Animator { void AddAnimation(void* target, void* ref, int a); };   // 0x7f8d10
extern Animator g_animator;                 // 0x16c7f30

// Same object as Wnd, but through an interface whose slot 0x28 is a setter
// taking two integers (used by ResetPanels on the QueryInterface result).
struct QIface {
    virtual void q00(); virtual void q04(); virtual void q08(); virtual void q0c();
    virtual void q10(); virtual void q14(); virtual void q18(); virtual void q1c();
    virtual void q20(); virtual int  q24();
    virtual void SetVisible(int a, int b);   // 0x28
};

// A "day" record: 0x4e0 bytes holding two parallel entry lists.
struct DayVec { char* begin; char* end; };
struct Day { char pad[4]; DayVec entries; char pad2[0x164]; DayVec alt; };

// Record entry: kind (int), sub-record (0x3c bytes), icon (int).
struct Sub {                                // 0x3c bytes at entry+4
    void* Name();                           // 0xf26360
    void* Flags();                          // 0xf26380
    char  Same(Sub* other);                 // 0xf263b0
};
struct Rec {
    int  kind;                              // +0x00
    Sub  sub;                               // +0x04
    int  icon;                              // +0x40
};

// A container of 0x4e0-byte day records at +0x70.
struct RecDB { char pad[0x70]; char* days; char* daysEnd; };

struct Ctx : RecDB {                        // g_16c7aa4->ctx74 / g_16c7d90->ctx
    char pad70[0x40];
    uint countB8;                           // +0xb8
    RecDB* GetRec(int kind);                // 0xf3e8a0
    char Check();                           // 0xf25670
};

struct Entry { Wnd* win; int idx; int savedA; int savedB; };  // 0x10 bytes
struct UIState {
    void* layout;                           // +0x00
    Ctx*  ctx;                              // +0x04
    char* owner;                            // +0x08
    int   mode;                             // +0x0c
    Entry entries[5];                       // +0x10 .. +0x60
    int   pad60[4];                         // +0x60 .. +0x70
    int   field70;                          // +0x70
    Wnd*  listWin;                          // +0x74
    float cursorX;                          // +0x78
    float cursorY;                          // +0x7c
    void* tool;                             // +0x80
};
extern UIState* g_16c7d90;                  // 0x16c7d90
extern UIState* g_16c7d90b;                 // 0x16c7d94

struct PBEntry {                            // 0x20-byte slot
    void* layout;                           // +0x00
    Wnd*  win;                              // +0x04
    float startTime;                        // +0x08
    int   record;                           // +0x0c
    char  active;                           // +0x10
    char  pad11[3];
    int   day;                              // +0x14
    int   pad18;
    int   sel;                              // +0x1c
};
extern PBEntry g_pbEntries[16];             // 0x16c7df0 .. 0x16c7f30

struct Global7aa4 { char pad[0x74]; Ctx* ctx74; char* day78; };
extern Global7aa4* g_16c7aa4;               // 0x16c7aa4

struct Layout { Wnd* FindWindowByID(uint id, int recurse); };  // 0x008105b0

// ---------------------------------------------------------------------------
// Globals and helpers.
// ---------------------------------------------------------------------------
float g_pbAlpha;            // 0x15ad4e0
float g_pbFade;             // 0x15ad4e4
float g_pbLag;              // 0x15ad4e8
float g_pbPad;              // 0x15ad4ec
float g_pbMinX;             // 0x15ad4f0
float g_pbMinY;             // 0x15ad4f4
int   g_pbMode;             // 0x15ad4f8
int   g_pbSub;              // 0x15ad4fc
char  g_pbBypass;           // 0x16c7d8c

extern "C" Wnd*  FUN_00b3d320();
extern "C" Wnd*  FUN_00b1de80();            // TerrainMgr::Fn2
extern "C" RecDB* FUN_00b18530();           // SP::cGameData
extern "C" void* FUN_006c0200(Wnd* ui);
extern "C" char  FUN_00f3e6d0(Wnd* o, void* rec, void* cookie, void* arg);
extern "C" int   FUN_00f078b0(void* out, float h);
extern "C" char  FUN_00c04750(Wnd* o);
extern "C" int   FUN_008e7f80(Wnd* o);
extern "C" char  FUN_008d2f30(int* x, int* y);   // GetCursorPosition
extern "C" float SPUIHelpers_GetElapsedSeconds(); // 0x805080
extern "C" void* SPUICreateWindowAnimationTargetShadeAlphaW(void* out, void* w, uint a, uint b, float c, int d);
extern "C" void* FUN_0067cad0(Wnd* panel, int a, int b);   // AddBoundingBox
extern "C" void  FUN_0080d710(void* bb);                   // BBox::Renderer
extern "C" unsigned int __cdecl wcscspn(const wchar_t* s, const wchar_t* set);

struct Avatar;
struct NounMgr { Avatar* GetAvatar(); };    // 0xb1fdb0
extern NounMgr* NounManager();              // 0xb3d300

extern const wchar_t kPBNewline[];          // 0x148ba08 "\n\r"
extern const wchar_t kPBEmpty[];            // 0x13ec468 ""

extern "C" float* GetPropertyAsFloat();     // 0x41ea70
extern "C" uint*  GetPropertyAsUInt();      // 0x41ea00
extern "C" int*   GetPropertyAsInt();       // 0x41e990

// ---------------------------------------------------------------------------
// 0x00f07c90: read the progress-bar tuning properties off the config object.
// ---------------------------------------------------------------------------
// @ 0x00f07c90
void ReadProgressTuning(void)
{
    void* v;
    FUN_00b3d320();
    Wnd* sink = FUN_00b1de80();
    if (sink == 0)
        return;
    if (sink->GetProp(0xa714aa6a, &v) && *(ushort*)((char*)v + 0x12) == 13)
        g_pbAlpha = *GetPropertyAsFloat();
    if (sink->GetProp(0xf6b5c7ca, &v) && *(ushort*)((char*)v + 0x12) == 13)
        g_pbFade = *GetPropertyAsFloat();
    if (sink->GetProp(0x775bb479, &v) && *(ushort*)((char*)v + 0x12) == 13)
        g_pbLag = *GetPropertyAsFloat();
    if (sink->GetProp(0x73237784, &v) && *(ushort*)((char*)v + 0x12) == 13)
        g_pbPad = *GetPropertyAsFloat();
    if (sink->GetProp(0x04ad8a3b, &v) && *(ushort*)((char*)v + 0x12) == 10)
        g_pbMode = *(int*)GetPropertyAsUInt();
    if (sink->GetProp(0xdee37e5e, &v) && *(ushort*)((char*)v + 0x12) == 9)
        g_pbSub = *GetPropertyAsInt();
    if (g_pbBypass) {
        g_pbAlpha = 2.0f;
        g_pbFade  = 0.0f;
        g_pbLag   = 0.0f;
        g_pbMode  = 2;
    }
}

// ---------------------------------------------------------------------------
// 0x00f07e10: is the player free to open the progress panel?
// (the game-state object arrives in ESI)
// ---------------------------------------------------------------------------
// @ 0x00f07e10
bool CanOpenProgressPanel(Wnd* o)
{
    if (o == 0)
        return true;
    Wnd* a = o->GetUIWindow(0x17f243b);
    if (a != 0 && a->Query() != 0)
        return false;
    Wnd* b = o->GetUIWindow(0xd0036e08);
    if (b != 0) {
        Wnd* c = (Wnd*)FUN_00c04750(b);
        if (c != 0 && FUN_00c04750(b) != 0 && *(char*)((char*)c + 2) != 0)
            return true;
    }
    Wnd* d = o->GetUIWindow(0x13f94d4);
    if (d != 0 && FUN_008e7f80(d) == 2)
        return false;
    return true;
}

// ---------------------------------------------------------------------------
// 0x00f07e90: does the panel show at least one flagged entry?
// (thiscall: the window is `this`; the day index comes from the global count)
// ---------------------------------------------------------------------------
// @ 0x00f07e90
bool PanelHasFlaggedEntry(Wnd* self)
{
    Ctx* ctx = g_16c7aa4->ctx74;
    Wnd* panel = self ? self->GetUIWindow(0x17f243b) : 0;
    void* ex = FUN_006c0200(panel);
    if (ex == 0)
        return false;
    RecDB* r = ctx->GetRec(*(int*)ex);
    if (r == 0)
        return false;
    int dayIdx = *(int*)(g_16c7aa4->day78 + 0xb8);
    Day* day = (Day*)(r->days + dayIdx * 0x4e0);
    Rec* beg = (Rec*)day->entries.begin;
    Rec* end = (Rec*)day->entries.end;
    int count = (int)((char*)end - (char*)beg) / 0x44;
    for (int i = 0; i < count; i++) {
        if (beg[i].sub.Flags())
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00f07f50: resolve (counter -> 0x44-byte entry) inside cGameData.
// (counter arrives in EAX, the panel in ECX)
// ---------------------------------------------------------------------------
// @ 0x00f07f50
Rec* GetCounterEntry(Wnd* self, int counter, char alt)
{
    Wnd* panel = self ? self->GetUIWindow(0x17f243b) : 0;
    RecDB* gd = FUN_00b18530();
    (void)panel;
    if (gd == 0)
        return 0;
    int dayNo = counter / 1000 - 1;
    int slot  = counter % 1000;
    Day* day = (Day*)(gd->days + dayNo * 0x4e0);
    if (alt)
        return (Rec*)(day->alt.begin + slot * 0x44);
    return (Rec*)(day->entries.begin + slot * 0x44);
}

// ---------------------------------------------------------------------------
// 0x00f07fd0: per-frame progress-bar update.
// ---------------------------------------------------------------------------
struct RawAnim { char pad[0x28]; void* vtblA; char pad2[4]; void* vtblB; IRef* ref; };

// @ 0x00f07fd0
bool SetPercentage(Wnd* panel, uint day, char flag)
{
    Wnd* win = 0;                            // ebx
    float t = SPUIHelpers_GetElapsedSeconds();
    PBEntry* sel = 0;                        // edi
    PBEntry* matched = 0;                    // [esp+0x10]
    PBEntry* it = &g_pbEntries[0];
    do {
        if (it->win == panel) {
            matched = it;
            sel = it;
            break;
        }
        Wnd* w = ((Layout*)it->layout)->FindWindowByID(0x73926f8, 1);
        if ((w->Slot28() & 1) == 0)
            sel = it;
        it++;
    } while (it < &g_pbEntries[16]);
    if (sel == 0)
        sel = &g_pbEntries[0];
    win = ((Layout*)sel->layout)->FindWindowByID(0x73926f8, 1);
    if (sel == matched && (flag == 0 || sel->sel == (int)day)) {
        sel->active = 0;
    } else {
        Rec* entry = GetCounterEntry(panel, (int)day, flag);
        sel->active = 1;
        sel->startTime = g_pbAlpha + t;
        Wnd* old = sel->win;
        if (panel != old) {
            if (panel != 0)
                panel->AddRef();
            sel->win = panel;
            if (old != 0)
                old->Release();
        }
        sel->record = entry->kind;
        sel->sel = flag ? (int)day : 0;
        if (sel->win != 0) {
            Wnd* s = sel->win->GetUIWindow(0xd0036e08);
            if (s != 0) {
                if (entry->icon == 5) {
                    *(float*)((char*)s + 0x1660) = 0.0f;
                    *(int*)((char*)s + 0x1664) = 5;
                    *(int*)((char*)s + 0x1668) = 0;
                    *(char*)((char*)s + 0x166c) = flag;
                } else {
                    *(float*)((char*)s + 0x1660) = g_pbAlpha;
                    *(int*)((char*)s + 0x1664) = entry->icon;
                    *(int*)((char*)s + 0x1668) = entry->kind;
                    *(char*)((char*)s + 0x166c) = flag;
                    Wnd* av = (Wnd*)NounManager()->GetAvatar();
                    if (flag && av != 0)
                        s->TextExtent((float*)((char*)av + 0x5a8), 1, 0);
                }
            }
        }
        Wnd* w2 = ((Layout*)sel->layout)->FindWindowByID(0x7392dd8, 1);
        win->SetVisible(1, 1);
        void* name = entry->sub.Name();
        w2->SetImage(name);
        Wnd* text = w2->QueryInterface(0xf15f4bd);
        float ext[2];
        text->TextExtent(ext, 0, 1);
        wchar_t* np = (wchar_t*)name;
        int len = (int)wcscspn(np, kPBEmpty);
        float rect[2];
        float dx = ext[0] - g_pbMinX;
        float dy = ext[1] - g_pbMinY;
        if (wcscspn(np, kPBNewline) < (uint)len || 0.0f < dy) {
            win->GetRect(rect);
            Wnd* text2 = w2->QueryInterface(0xf15f4bd);
            text2->TextExtent(ext, 1, 1);
        }
        win->GetRect(rect);
    }
    if (sel != matched) {
        RawAnim raw;
        float lag = g_pbLag;
        float f = 0.0f;
        SPUICreateWindowAnimationTargetShadeAlphaW(&raw, win, 0xff, *(uint*)&f, lag, 0);
        g_animator.AddAnimation(&raw, win, 0x73cf0d8);
        raw.vtblA = (void*)0x13f6400;
        raw.vtblB = (void*)0x13f63fc;
        if (raw.ref)
            raw.ref->dtor();
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00f08350: score how well `a` faces `b` (x87 dot product, -1e7 when bad).
// ---------------------------------------------------------------------------
// @ 0x00f08350
float ScoreFacing(Wnd* a, Wnd* b)
{
    float tmp[3];
    float* dir = b->Slot5c(tmp);
    float inv = (float)(1.0 / sqrt((double)(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2])));
    float nx = dir[0] * inv;
    float ny = dir[1] * inv;
    float nz = dir[2] * inv;
    float* pa = a->GetArea();
    float* pb = b->GetArea();
    float dx = pb[0] - pa[0];
    float dy = pb[1] - pa[1];
    float dz = pb[2] - pa[2];
    float dot = dz * nz + dx * nx + dy * ny;
    if (dot >= 0.0f && a->Flag48()) {
        float d2 = dx * dx + dy * dy + dz * dz;
        float px = nx * dot;
        float py = ny * dot;
        float pz = nz * dot;
        return (py * py + pz * pz + px * px) - d2 - d2 * 0.25f;
    }
    return -1e7f;
}

// ---------------------------------------------------------------------------
// 0x00f084b0: is the counter inside the valid day/entry range, and flagged?
// ---------------------------------------------------------------------------
// @ 0x00f084b0
bool IsCounterValid(RecDB* a, int counter)
{
    int dayNo = counter / 1000 - 1;
    if (dayNo < (int)((a->daysEnd - a->days) / 0x4e0)) {
        Day* day = (Day*)(a->days + dayNo * 0x4e0);
        if (counter % 1000 < (int)((day->alt.end - day->alt.begin) / 0x44)) {
            Rec* r = (Rec*)(day->alt.begin + (counter % 1000) * 0x44);
            return r->sub.Flags() != 0;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00f08550: do days i and j have the same first five entry names?
// ---------------------------------------------------------------------------
// @ 0x00f08550
bool SameDayEntries(RecDB* a, int j, int i)
{
    for (int off = 0; off < 0x154; off += 0x44) {
        Rec* r3 = (Rec*)(((Day*)(a->days + i * 0x4e0))->alt.begin + off);
        Rec* r2 = (Rec*)(((Day*)(a->days + j * 0x4e0))->alt.begin + off);
        if (!r2->sub.Same(&r3->sub))
            return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00f085b0: advance a counter by one day, wrapping past the last day.
// The value left in EAX is captured by the callers, so model it explicitly.
// ---------------------------------------------------------------------------
// @ 0x00f085b0
int AdvanceCounter(RecDB* a, int* counter)
{
    int c = *counter;
    int dayNo = c / 1000;
    if (dayNo - 1 == (int)((a->daysEnd - a->days) / 0x4e0) - 1) {
        *counter = -1;
        return dayNo - 1;
    }
    if (SameDayEntries(a, dayNo - 1, dayNo)) {
        *counter = c + 1000;
        return 1;
    }
    *counter = (c + 1000) & 0xfffffff0;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f08630: step a counter forward, skipping to the next valid day.
// ---------------------------------------------------------------------------
// @ 0x00f08630
int StepCounter(void* a, int* counter)
{
    int v = *counter;
    if (v == 0) {
        *counter = 1000;
        return 0;
    }
    v = v + 1;
    *counter = v;
    int res = v / 1000;
    while (v % 1000 > 4) {
        res = AdvanceCounter((RecDB*)a, counter);
        if (*counter == -1)
            break;
        v = *counter;
        res = v / 1000;
    }
    return res;
}

// ---------------------------------------------------------------------------
// 0x00f08680: pull a counter back until it names an existing day.
// ---------------------------------------------------------------------------
// @ 0x00f08680
void CoerceCounter(RecDB* a, int* counter)
{
    if (*counter == 0)
        return;
    int maxDay = *(int*)(g_16c7aa4->day78 + 0xb8);
    while (*counter != -1 && *counter / 1000 - 1 < maxDay) {
        AdvanceCounter(a, counter);
    }
}

// ---------------------------------------------------------------------------
// 0x00f086d0: advance a counter to the next entry that exists.
// ---------------------------------------------------------------------------
// @ 0x00f086d0
int NextValidCounter(void* a, int* counter)
{
    CoerceCounter((RecDB*)a, counter);
    int res = StepCounter(a, counter);
    if (*counter != -1) {
        while (!IsCounterValid((RecDB*)a, *counter)) {
            if (*counter == 0) {
                *counter = 1000;
                res = 0;
            } else {
                int v = *counter + 1;
                *counter = v;
                while (v % 1000 > 4) {
                    res = AdvanceCounter((RecDB*)a, counter);
                    if (*counter == -1)
                        return res;
                    v = *counter;
                    res = v / 1000;
                }
            }
            if (*counter == -1)
                return res;
        }
    }
    return res;
}

// ---------------------------------------------------------------------------
// 0x00f08750: pick the entry in `list` that best matches the record.
// ---------------------------------------------------------------------------
// @ 0x00f08750
Wnd* FindBestEntry(Rec* rec, int id, void* cookie, void* list, void* avatarObj)
{
    Ctx* ctx = g_16c7aa4->ctx74;
    Wnd* best = 0;
    float bestScore = -1e6f;
    void** it = ((void***)list)[0];
    void** end = ((void***)list)[1];
    while (it != end) {
        Wnd* w = (Wnd*)*it;
        void* a = w ? w->GetUIWindow(0x17f243b) : 0;
        void* ex = FUN_006c0200((Wnd*)a);
        Wnd* e = w ? w->GetUIWindow(0x17f243b) : 0;
        if (ex != 0 && e != 0 && *(int*)ex == id && FUN_00b18530() != 0 &&
            FUN_00f3e6d0(e, (char*)rec + 0x24, cookie, ctx)) {
            float s = ScoreFacing(w, (Wnd*)avatarObj);
            if (bestScore < s) {
                bestScore = s;
                best = e;
            }
        }
        it++;
    }
    return best;
}

// ---------------------------------------------------------------------------
// 0x00f08850: address of the day list selected by mode.
// ---------------------------------------------------------------------------
// @ 0x00f08850
char* GetDayList(int index, int mode)
{
    UIState* g = g_16c7d90;
    char* base = g->ctx->days + index * 0x4e0;
    int m = mode;
    switch (m) {
    case 1: return base + 0x170;
    case 2: return base + 4;
    case 3: return g->owner + 0x18;
    default: return 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00f08890: set or clear the 0x400 window flag.
// ---------------------------------------------------------------------------
// @ 0x00f08890
void SetWindowFlag(uint v)
{
    if (g_16c7d90 == g_16c7d90b) {
        Wnd* w = ((Layout*)g_16c7d90->layout)->FindWindowByID(0x7de6960, 1);
        w->SetVisible(0x400, (int)v);
    }
}

// ---------------------------------------------------------------------------
// 0x00f088c0: move a panel from its parent's local position.
// ---------------------------------------------------------------------------
// @ 0x00f088c0
void MovePanel(Wnd* self, float* p)
{
    Wnd* parent = self->GetParent();
    float xy[2];
    parent->GetLocalPos(xy);
    self->SetPos(xy[1], xy[0]);
}

// ---------------------------------------------------------------------------
// 0x00f08920: tear down the active list panel.
// ---------------------------------------------------------------------------
// @ 0x00f08920
void ResetPanels(void)
{
    UIState* g = g_16c7d90;
    Wnd* lw = g->listWin;
    if (lw != 0) {
        QIface* q = (QIface*)lw->QueryInterface(0x8ed27e7a);
        if (q != 0)
            q->SetVisible(4, 0);
        g_16c7d90->listWin = 0;
    }
    Wnd* w1 = ((Layout*)g->layout)->FindWindowByID(0x1742be59, 1);
    w1->SetVisible(1, 0);
    Wnd* w2 = ((Layout*)g_16c7d90->layout)->FindWindowByID(0x1742be58, 1);
    w2->SetVisible(1, 0);
    g_16c7d90->field70 = 0;
}

// ---------------------------------------------------------------------------
// 0x00f089a0: drag the list panels with the cursor.
// ---------------------------------------------------------------------------
// @ 0x00f089a0
void DragPanels(void* arg)
{
    int gx, gy;
    FUN_008d2f30(&gy, &gx);
    float px = (float)gx;
    float py = (float)gy;
    Wnd* w = *(Wnd**)arg;
    float cur[2];
    cur[0] = px;
    cur[1] = py;
    float local[2];
    w->GetLocalPos(local);
    int saveX = (int)g_16c7d90->cursorX;
    int saveY = (int)g_16c7d90->cursorY;
    float ext[2];
    w->GetLocalPos(ext);
    float* area = w->GetArea();
    float x = area[0] - (cur[0] - local[0]);
    float y = area[1] - (cur[1] - ext[0]);
    w->SetPos(x, y);
    g_16c7d90->cursorX = (float)saveX;
    g_16c7d90->cursorY = (float)saveY;
    float* area2 = w->GetArea();
    int oldIdx = ((int*)arg)[1];
    float rh = area2[3] - area2[1];
    int newIdx = FUN_00f078b0(cur, rh);
    w->Slot5c((void*)(newIdx == -1 ? 0x77ff0000 : -1));
    for (int i = 0; i < 5; i++) {
        int* slot = &g_16c7d90->entries[i].idx;
        if (*slot > oldIdx && oldIdx != -1)
            (*slot)--;
        if (*slot >= newIdx && newIdx != -1)
            (*slot)++;
    }
    ((int*)arg)[1] = newIdx;
}

// ---------------------------------------------------------------------------
// 0x00f08b70: select one of the five list panels by its window pointer.
// ---------------------------------------------------------------------------
// @ 0x00f08b70
bool SelectPanel(Wnd* w)
{
    UIState* g = g_16c7d90;
    for (int i = 0; i < 5; i++) {
        Entry* e = &g->entries[i];
        if (e->win == w) {
            Wnd* parent = e->win->GetParent();
            parent->pE8(e->win);
            void* bb = FUN_0067cad0(e->win, 1, 1);
            FUN_0080d710(bb);
            if (g_16c7d90 == g_16c7d90b) {
                Wnd* win = ((Layout*)g_16c7d90->layout)->FindWindowByID(0x7de6960, 1);
                win->SetVisible(0x400, 0);
            }
            FUN_008d2f30((int*)&g_16c7d90->cursorX, (int*)&g_16c7d90->cursorY);
            g_16c7d90->tool = e;
            return true;
        }
    }
    return false;
}
