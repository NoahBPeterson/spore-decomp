// Slice s01062ce0 -- SP::cUFOLocomotion::UpdateLocomotion + movement command helpers, and
// SP::cUIBadgeCard (vtable 0x149c070) init/shutdown/feed update helpers.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// EA FloatToInt64: a 1-instruction inline-asm helper. 0x01062ce0's original converts its
// float delta-time to integer milliseconds with an x87 `fld [slot]; fistp qword [slot]`
// (no fldcw), which neither a plain (int) cast (/arch:SSE -> call __ftol2_sse) nor an
// `__int64` cast (/arch:SSE -> call __ftol2) reproduces; see the s01062ce0 papercut.
__forceinline __int64 FloatToInt64(float f)
{
    __declspec(align(8)) __int64 result;
    __asm {
        fld f
        fistp result
    }
    return result;
}

extern uint8_t* g_1440aec;      // 0x01440aec  noun table base pointer
extern uint8_t  g_149c008[];    // 0x0149c008  badge id table (10 dwords)
extern float    g_16e2114[3];   // 0x016e2114  zero velocity vector
extern char     g_1654c10;      // 0x01654c10  space game mode singleton
extern uint16_t g_1667bac[];    // 0x01667bac  eastl::gEmptyString16

// ---------------------------------------------------------------- callees
extern "C" void* __cdecl GetCurrentGameMode();                  // 0x00b5b800
extern "C" void* __cdecl GetUniverseContext();                  // 0x01021080
extern "C" void* __cdecl NounManager();                         // 0x00b3d300
extern "C" void* __cdecl ConfigManager();                       // 0x0067dd30
extern "C" void* __cdecl GetPanelMgr();                         // 0x00b3d3f0
extern "C" void* __cdecl SpaceGameGet();                        // 0x01002bd0
extern "C" void  __cdecl EA_Messaging_RemoveHandler(void*, int, int, int, int); // 0x00571db0
extern "C" void* __cdecl EAAllocate(unsigned, const char*, int, int, int, int); // 0x00f473a0
extern "C" void  __cdecl operator_delete_(void*);               // 0x00f47380
extern "C" void  __cdecl SetWindowImage(void*, void*, int);     // 0x00807bb0
extern "C" void  __cdecl Fun_00807cb0(void*, void*, int);       // 0x00807cb0

struct Layout {
    void* FindWindowByID(unsigned id, bool flag);               // 0x008105b0
};

struct Config {
    int f01067dd30(int id);                                     // vtable +0x30
};

struct TerrainEditor {
    void* GetCurrentTerrainSphere();                            // 0x00f67d90
};

struct Sphere {
    char f010c772c0(int id);                                    // 0x00c772c0
};

struct Panel {
    void f010e18dd0(int, int);                                  // 0x00e18dd0
};

struct V3i { int a, b, c; };
struct Vec3 { float x, y, z; };
struct Rect { float x, y, z, w; };

// ---------------------------------------------------------------- commands
struct UFCmd {
    int   type;     // +0x00
    int   target;   // +0x04
    float x;        // +0x08
    float y;        // +0x0c
    float z;        // +0x10
    float t;        // +0x14

    void  f01062e60(int);
    void  f01062e70(int, const float*, float);
    bool  f01062ea0(int*, float*, float*);
    UFCmd* f01062ee0();
};

struct UfoSub {
    virtual void   v00();
    virtual void   v04();
    virtual void   v08();
    virtual void   v0c();
    virtual void   v10();
    virtual void   v14();
    virtual void   v18();
    virtual void   v1c();
    virtual void   v20();
    virtual void   v24();
    virtual void   v28();
    virtual float* v2c();
    virtual void   v30();
    virtual void   v34();
    virtual void   v38();
    virtual void   v3c(void*);
};

struct UfoCraft {
    char    pad0[0x34];
    UfoSub  sub;            // +0x34
    char    pad38[0x718 - 0x38];
    float   ax, ay, az;     // +0x718
    char    pad724[0x0c];
    char    obj730[0x10];   // +0x730
    float   bx, by, bz;     // +0x740
};

struct UfoMove {
    float x, y, z;          // +0x00
    float pad0c;
    float dt;               // +0x10
    void* link;             // +0x14  points at craft+0x34
};

struct UF {
    void f01062ce0(UfoMove*);
    void f01060df0(UfoMove*, int);      // 0x01060df0
    void f0105f2d0(UfoMove*, int);      // 0x0105f2d0
};

// ---------------------------------------------------------------- badge UI
struct Str16 { uint16_t* begin; uint16_t* end; uint16_t* cap; };

struct FeedItem {
    void  f010666630(int* a, void** b);                         // 0x00666630
    void  f0106666c0(uint16_t* s);                              // 0x006666c0
    void  f010667690(bool);                                     // 0x00667690
};

struct Feed {
    Feed* ctor();                                               // 0x00663040
    void  f0106628d0();                                         // 0x006628d0
    void  f010662920(bool);                                     // 0x00662920
    void* FindItem(void* key);                                  // 0x00662960
    void  f010663350(int);                                      // 0x00663350
    void  f010663860(void*, int, int, int);                     // 0x00663860
};

struct Tribe {
    int      f010fe45f0(int, int);                              // 0x00fe45f0
    unsigned f010fe4660(int);                                   // 0x00fe4660
    bool     f010fe4180(int);                                   // 0x00fe4180
    void     f010fe6800(int, Str16*);                           // 0x00fe6800
    void*    f010fe5520(void* out, int id);                     // 0x00fe5520
    void     f010fe4710(int, Str16*);                           // 0x00fe4710
    void     f010fe4830(int, Str16*);                           // 0x00fe4830
    void*    f010fe3e50(int);                                   // 0x00fe3e50
    unsigned f010fe3f50(void*);                                 // 0x00fe3f50
    void*    f010fe3f80(void*, unsigned);                       // 0x00fe3f80
    float    f010fe6690(int);                                   // 0x00fe6690
};

struct Sim {
    Tribe* GetPlayerTribe();                                    // 0x00bfc5f0
};

struct NounMgr {
    void f010e30e20(void*, int, int, int, int);                 // 0x00e30e20
};

struct S3 { int a, b, c; };
struct Key { int a, b, c; };

struct Sub44 {
    void    f010e0a390();                                       // 0x00e0a390
    void    f010e0a400();                                       // 0x00e0a400
    void    f010e0a4c0(void*, void*);                           // 0x00e0a4c0
    void    f010e0a5c0();                                       // 0x00e0a5c0
    void    f010e0a640();                                       // 0x00e0a640
    char    data[0x70];
};

struct SubB4 {
    void    f010e0a390();                                       // 0x00e0a390
    void    f010e0a400();                                       // 0x00e0a400
    void    f010e0a4c0(void*, void*);                           // 0x00e0a4c0
    void    f010e0a5c0();                                       // 0x00e0a5c0
    void    f010e0a640();                                       // 0x00e0a640
    uint8_t f010e0a780(void*, unsigned);                        // 0x00e0a780
    void*   f010e09c90(int);                                    // 0x00e09c90
    char    data[0x74];
};

struct TT {
    void  f010e36480();                                         // 0x00e36480
    void  f010e364d0();                                         // 0x00e364d0
    void  f010e36500();                                         // 0x00e36500
    void  f010e36540();                                         // 0x00e36540
    void* f010e36650(unsigned, bool);                           // 0x00e36650
    void  f010e36b30(S3, int, int, int);                        // 0x00e36b30
    char  data[0x60];
};

struct SFV {
    SFV* ctor();                                                // 0x0082a040
    bool f01082a140(unsigned, int, int);                        // 0x0082a140
    float GetScrollOffset();                                    // 0x0082a4e0
    void  Shutdown();                                           // 0x0082a450
    void  Update(int);                                          // 0x0082a500
};

struct UB {
    void*   v0;         // +0x00
    char    p04[4];
    void*   v8;         // +0x08
    void*   vC;         // +0x0c
    void*   f10;        // +0x10
    void*   f14;        // +0x14
    void*   layout;     // +0x18
    char    p1c[0x34 - 0x1c];
    void*   head;       // +0x34
    char    p38[0x40 - 0x38];
    uint8_t active;     // +0x40
    char    p41[3];
    Sub44   f44;        // +0x44
    SubB4   fB4;        // +0xb4
    TT      f128;       // +0x128
    float   f188;       // +0x188
    SFV*    sfv;        // +0x18c
    void*   handler;    // +0x190
    int     h194;       // +0x194
    int     h198;       // +0x198
    int     h19c;       // +0x19c
    int     h1a0;       // +0x1a0
    Feed*   feed;       // +0x1a4
    void*   f1a8;       // +0x1a8

    void f01062f80();
    void f01062ff0(int, int, int, int);
    void f010632b0();
    void f01063330(void*);
    UB*  f01063360();
    void f01063400();
    void f010634b0(void*, int, int);
    void f010635d0();
    void f01063740(int);
    void f01063350(int);            // 0x00663350 (unused helper slot)
    void f01062920(bool);           // 0x00662920
    void f0106628d0();              // 0x006628d0
    void f010e18bb0();
    void f010e186d0(int, int, int, int);
    void f010e18810();
    void f010e18980();
    void f010e18a30();
    void f01010829f0(void*);
};

// ---------------------------------------------------------------- UF bodies
// @ 0x01062ce0
void UF::f01062ce0(UfoMove* m)
{
    UfoCraft* c;
    if (m->link) c = (UfoCraft*)((char*)m->link - 0x34); else c = 0;
    float dt = m->dt * 1000.0f;
    int ms = (int)FloatToInt64(dt);
    if (GetCurrentGameMode() != &g_1654c10) {
        if (GetUniverseContext() == 0) {
            f01060df0(m, ms);
        } else {
            f0105f2d0(m, ms);
        }
    }
    if (!(dt > 1.5258789e-05f)) {                 // comiss; jbe (the stores are scheduled above it)
        m->x = g_16e2114[0];
        m->y = g_16e2114[1];
        m->z = g_16e2114[2];
        c->sub.v3c(c->obj730);
        return;
    }
    m->x = g_16e2114[0];
    m->y = g_16e2114[1];
    m->z = g_16e2114[2];
    {
        float ax = c->ax + c->bx;
        float ay = c->ay + c->by;
        float az = c->az + c->bz;
        float* p = c->sub.v2c();
        float dx = ax - p[0];
        float dy = ay - p[1];
        float dz = az - p[2];
        if (dz * dz + dy * dy + dx * dx > 1.5258789e-05f) {
            float inv = 1.0f / dt;                // fld1; fdivrp
            m->x = dx * inv;
            m->y = dy * inv;
            m->z = dz * inv;
        }
    }
    c->sub.v3c(c->obj730);
}

// ---------------------------------------------------------------- UF command helpers
// @ 0x01062e60
void UFCmd::f01062e60(int v) { type = v; }

// @ 0x01062e70
void UFCmd::f01062e70(int id, const float* p, float t)
{
    target = id;
    *(Vec3*)&x = *(const Vec3*)p;
    this->t = t;
}

// @ 0x01062ea0
bool UFCmd::f01062ea0(int* id, float* p, float* t)
{
    if (target != -1) {
        *id = target;
        *(Vec3*)p = *(Vec3*)&x;
        *t = this->t;
        target = -1;
        return true;
    }
    return false;
}

// @ 0x01062ee0
UFCmd* UFCmd::f01062ee0()
{
    type = 0;
    target = -1;
    return this;
}

// ---------------------------------------------------------------- free helper
// @ 0x01062f30
void f01062f30()
{
    void* te = NounManager();
    void* sphere = ((TerrainEditor*)te)->GetCurrentTerrainSphere();
    Config* cfg = (Config*)ConfigManager();
    if ((*(int (__thiscall**)(void*, int))((char*)*(void**)cfg + 0x30))(cfg, 0x4ea96cb) && sphere) {
        if (!((Sphere*)sphere)->f010c772c0(0x65e611d)) {
            ((Panel*)GetPanelMgr())->f010e18dd0(-11, 0);
        }
    }
}

// ---------------------------------------------------------------- UB bodies
// @ 0x01062f80
void UB::f01062f80()
{
    if (active) {
        void* h = handler;
        if (h) {
            handler = 0;
            EA_Messaging_RemoveHandler(h, h194, h198, h19c, h1a0);
        }
        feed->f010662920(false);
        f44.f010e0a640();
        fB4.f010e0a640();
        active = 0;
        f010e18a30();
    }
}

// @ 0x01062ff0
void UB::f01062ff0(int a1, int a2, int a3, int a4)
{
    f010e186d0(a1, a2, a3, a4);
    active = 0;
    V3i d1 = { 0, 0, 0 };
    f44.f010e0a4c0(((Layout*)layout)->FindWindowByID(0x5f00928, true), &d1);
    V3i d2 = { 0, 0, 0 };
    fB4.f010e0a4c0(((Layout*)layout)->FindWindowByID(0x5fc9a00, true), &d2);
    S3 s = { 0x39858c9, 0x510a95b, 0x40464100 };
    f128.f010e36b30(s, 0x5fd4ce0, 0xc8, 0xfa);
    void* w = f128.f010e36650(0x51a37b8, true);
    float* r = (float*)(*(void* (__thiscall**)(void*))((char*)*(void**)w + 0x38))(w);
    f188 = r[2] - r[0];

    void* mem = EAAllocate(0x48, "UI/cSPUIScrollFrameVertical", 0, 0, 0, 0);
    SFV* nw = mem ? ((SFV*)mem)->ctor() : 0;
    SFV* old = sfv;
    if (nw != old) {
        if (nw) (*(void (__thiscall**)(void*))((char*)*(void**)nw))(nw);
        sfv = nw;
        if (old) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    sfv->f01082a140(0xaef7d6ba, 1, 0);

    void* win = ((Layout*)layout)->FindWindowByID(0x51a37b9, true);
    if (win) {
        (*(void (__thiscall**)(void*))((char*)*(void**)win))(win);
        void* sa = *(void**)((char*)sfv + 0x10);
        void* sb = *(void**)((char*)sfv + 0x18);
        void* mid = (*(void* (__thiscall**)(void*))((char*)*(void**)win + 0x10))(win);
        (*(void (__thiscall**)(void*, void*))((char*)*(void**)mid + 0xd8))(mid, sa);
        float* wr = (float*)(*(void* (__thiscall**)(void*))((char*)*(void**)win + 0x38))(win);
        Rect rect;
        rect.x = wr[0];
        rect.y = wr[1];
        rect.z = wr[2];
        rect.w = wr[3];
        rect.z += sfv->GetScrollOffset();
        (*(void (__thiscall**)(void*, Rect*))((char*)*(void**)sa + 0x6c))(sa, &rect);
        (*(void (__thiscall**)(void*, void*))((char*)*(void**)mid + 0xdc))(mid, win);
        (*(void (__thiscall**)(void*, void*))((char*)*(void**)sb + 0xd8))(sb, win);
        (*(void (__thiscall**)(void*, float, float))((char*)*(void**)win + 0x70))(win, 0.0f, 0.0f);
    }

    void* mem2 = EAAllocate(0x6c, "UI/cSPUIFeedList", 0, 0, 0, 0);
    Feed* nf = mem2 ? ((Feed*)mem2)->ctor() : 0;
    Feed* oldf = feed;
    if (nf != oldf) {
        if (nf) (*(void (__thiscall**)(void*))((char*)*(void**)nf))(nf);
        feed = nf;
        if (oldf) (*(void (__thiscall**)(void*))((char*)*(void**)oldf + 4))(oldf);
    }
    feed->f010663860(((Layout*)layout)->FindWindowByID(0x5f00660, true), 0x625a25dc, 0, 0);
    feed->f010663350(0);
    feed->f010662920(false);
    if (win) (*(void (__thiscall**)(void*))((char*)*(void**)win + 4))(win);
}

// @ 0x010632b0
void UB::f010632b0()
{
    if (feed) {
        feed->f0106628d0();
        if (feed) {
            Feed* p = feed;
            feed = 0;
            (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
        }
    }
    f44.f010e0a5c0();
    fB4.f010e0a5c0();
    f128.f010e36500();
    if (sfv) {
        sfv->Shutdown();
        if (sfv) {
            SFV* p = sfv;
            sfv = 0;
            (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
        }
    }
    f010e18810();
}

// @ 0x01063330
void UB::f01063330(void* wp)
{
    f01010829f0(wp);
    if (active) {
        f128.f010e36540();
        feed->f010663350((int)wp);
    }
}

// @ 0x01063360
UB* UB::f01063360()
{
    f010e18bb0();
    v0 = (void*)0x149c070;
    v8 = (void*)0x149c054;
    vC = (void*)0x149c04c;
    active = 0;
    f44.f010e0a390();
    fB4.f010e0a390();
    f128.f010e36480();
    sfv = 0;
    handler = 0;
    h194 = 0;
    h198 = 0;
    h19c = 0;
    h1a0 = 0;
    feed = 0;
    f1a8 = 0;
    return this;
}

// @ 0x01063400
void UB::f01063400()
{
    v0 = (void*)0x149c070;
    v8 = (void*)0x149c054;
    vC = (void*)0x149c04c;
    if (f1a8) (*(void (__thiscall**)(void*))((char*)*(void**)f1a8 + 4))(f1a8);
    if (feed) (*(void (__thiscall**)(void*))((char*)*(void**)feed + 4))(feed);
    if (handler) {
        void* h = handler;
        handler = 0;
        EA_Messaging_RemoveHandler(h, h194, h198, h19c, h1a0);
    }
    if (sfv) (*(void (__thiscall**)(void*))((char*)*(void**)sfv + 4))(sfv);
    f128.f010e364d0();
    fB4.f010e0a400();
    f44.f010e0a400();
    f010e18980();
}

// @ 0x010634b0
void UB::f010634b0(void* w, int key, int unused)
{
    void* tribe = ((Sim*)SpaceGameGet())->GetPlayerTribe();
    int first = ((Tribe*)tribe)->f010fe45f0(key, 0);
    unsigned n = ((Tribe*)tribe)->f010fe4660(key);
    unsigned half = n < 5 ? (5 - n) >> 1 : 0;
    unsigned total = n + half;
    void* win = w;
    int* pcur = &key;
    void** pend = &w;
    (*(void (__thiscall**)(void*, int*))((char*)*(void**)win + 0xcc))(win, pcur);
    (*(void (__thiscall**)(void*, void**))((char*)*(void**)win + 0xd0))(win, pend);
    unsigned i = 0;
    int cur = key;
    while (cur != (int)w) {
        uint8_t* node = g_1440aec + cur;
        if (node) {
            void* item = (*(void* (__thiscall**)(void*, int))((char*)*(void**)node + 0xc))(node, 0x106f146);
            if (item) {
                void* sub = (char*)item + 4;
                if (i < half || total <= i) {
                    (*(void (__thiscall**)(void*, int, int))((char*)*(void**)sub + 0x7c))(sub, 1, 0);
                } else {
                    (*(void (__thiscall**)(void*, int, int))((char*)*(void**)sub + 0x7c))(sub, 1, 1);
                    void* sub2 = (char*)item + 0x20c;
                    (*(void (__thiscall**)(void*, int))((char*)*(void**)sub2 + 0x14))(sub2,
                        i < half + (unsigned)first ? 3 : 1);
                }
                i++;
            }
        }
        cur = *(int*)cur;
    }
}

// @ 0x010635d0
void UB::f010635d0()
{
    void* tribe = ((Sim*)SpaceGameGet())->GetPlayerTribe();
    uint8_t flag = 1;
    for (int off = 0; off < 0x28; off += 4) {
        void* item = feed->FindItem(*(void**)(g_149c008 + off));
        if (!item) continue;
        int cnt = 0;
        void* vec = 0;
        ((FeedItem*)item)->f010666630(&cnt, &vec);
        if (cnt != 1) continue;
        int key = *(int*)vec;

        void* sent = (char*)this + 0x34;
        void* node = *(void**)((char*)this + 0x34);
        while (node != sent) {
            if (*(int*)((char*)node + 8) == key) break;
            node = *(void**)node;
        }
        if (node != sent) {
            void* a = *(void**)((char*)item + 0xa0);
            (*(void (__thiscall**)(void*, unsigned))((char*)*(void**)a + 0x50))(a, *(unsigned*)((char*)item + 0x17c));
            void* a2 = *(void**)((char*)item + 0xa0);
            void* mgr = GetPanelMgr();
            int extra = *(int*)((char*)this + 0x14);
            void* m = *(void**)((char*)mgr + 0x5c);
            void* r = (*(void* (__thiscall**)(void*))((char*)*(void**)a2 + 0x1c))(a2);
            ((NounMgr*)m)->f010e30e20(r, extra, 0x2c765c39, 0, 0);
        }

        Str16 s;
        s.begin = s.end = g_1667bac;
        s.cap = g_1667bac + 1;
        ((Tribe*)tribe)->f010fe6800(key, &s);
        ((FeedItem*)item)->f0106666c0(s.begin);
        bool inserted = ((Tribe*)tribe)->f010fe4180(key);
        bool val = false;
        if (!inserted) {
            val = !flag;
            flag = 0;
        }
        ((FeedItem*)item)->f010667690(val);
        int d = ((int)s.cap - (int)s.begin) & ~1;
        if (d > 2 && s.begin) operator_delete_(s.begin);
    }
}

// @ 0x01063740
void UB::f01063740(int id)
{
    void* w1 = ((Layout*)layout)->FindWindowByID(0x5f00928, true);
    (*(void (__thiscall**)(void*, int, int))((char*)*(void**)w1 + 0x7c))(w1, 1, 0);
    void* w2 = ((Layout*)layout)->FindWindowByID(0x5fc9978, true);
    (*(void (__thiscall**)(void*, int, int))((char*)*(void**)w2 + 0x7c))(w2, 1, 1);

    Tribe* tribe = ((Sim*)SpaceGameGet())->GetPlayerTribe();
    void* wImg = ((Layout*)layout)->FindWindowByID(0x5fc9a70, true);
    Key key;
    SetWindowImage(wImg, tribe->f010fe5520(&key, id), -1);

    Str16 s;
    s.begin = s.end = g_1667bac;
    s.cap = g_1667bac + 1;
    tribe->f010fe4710(id, &s);
    void* wName = ((Layout*)layout)->FindWindowByID(0x51a37b8, true);
    (*(void (__thiscall**)(void*, uint16_t*))((char*)*(void**)wName + 0x80))(wName, s.begin);

    tribe->f010fe4830(id, &s);
    void* wHint = ((Layout*)layout)->FindWindowByID(0x51a37b9, true);
    (*(void (__thiscall**)(void*, uint16_t*))((char*)*(void**)wHint + 0x80))(wHint, s.begin);

    void* act = (*(void* (__thiscall**)(void*, int))((char*)*(void**)wHint + 0xc))(wHint, 0xf15f4bd);
    (*(void (__thiscall**)(void*, int))((char*)*(void**)act + 0x14))(act, 1);

    sfv->Update(1);
    tribe->f010fe6800(id, &s);
    void* wCount = ((Layout*)layout)->FindWindowByID(0x5fca1a8, true);
    (*(void (__thiscall**)(void*, uint16_t*))((char*)*(void**)wCount + 0x80))(wCount, s.begin);

    void* wList = (*(void* (__thiscall**)(void*, int, int))((char*)*(void**)w2 + 0xf0))(w2, 0x5fca190, 1);
    void* inner = (*(void* (__thiscall**)(void*))((char*)*(void**)wList + 0x10))(wList);
    float* r = (float*)(*(void* (__thiscall**)(void*))((char*)*(void**)inner + 0x38))(inner);
    float width = r[2] - r[0];
    float scale = tribe->f010fe6690(id);
    float* r2 = (float*)(*(void* (__thiscall**)(void*))((char*)*(void**)wList + 0x38))(wList);
    (*(void (__thiscall**)(void*, float, float))((char*)*(void**)wList + 0x74))(wList,
        scale * width, r2[3] - r2[1]);

    void* u = tribe->f010fe3e50(id);
    unsigned cnt = tribe->f010fe3f50(u);
    if (fB4.f010e0a780((void*)0x15b8f88, cnt) && cnt > 0) {
        unsigned i = 0;
        do {
            void* data = tribe->f010fe3f80(u, i);
            Layout* lay = (Layout*)fB4.f010e09c90(i);
            void* w = lay->FindWindowByID(0x5ee04c0, true);
            (*(void (__thiscall**)(void*, void*))((char*)*(void**)w + 0x50))(w, data);
            (*(void (__thiscall**)(void*, int))((char*)*(void**)w + 0x54))(w, 0x5fce2d8);
            Fun_00807cb0(w, tribe->f010fe5520(&key, (int)data), 0);
            this->f010634b0(lay->FindWindowByID(0x5fca1f0, true), (int)data, 0);
            i++;
        } while (i < cnt);
    }

    int d = ((int)s.cap - (int)s.begin) & ~1;
    if (d > 2 && s.begin) operator_delete_(s.begin);
}
