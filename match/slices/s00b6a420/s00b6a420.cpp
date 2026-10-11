// Slice s00b6a420: floating world-label event handlers + the label manager singleton.
//
// The label (Event) is a large UI object: it carries the object it annotates (+0x04), a flag (+0x08),
// two 2-float points (+0x0c..+0x18), a block of animation floats (+0x1c..+0x4c) and a set of UI
// widgets / layout pointers (+0x50..+0xac).  FUN_00b6a420 picks a per-kind drawing routine by the
// annotated object's type id, FUN_00b6a610 does the screen-rect hit test, and the a7xx/a9xx/abxx
// routines drive the widget tree and then funnel into FUN_00b6a720 (called with the label in EDI
// and a float pair in EAX in the original -- approximated here, so the a720-family is nonmatching).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

inline void* operator new(unsigned, void* p) { return p; }

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Rect { float x, y, z, w; };

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
    VS(64) VS(65) VS(66) VS(67)
};
#undef VS

#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// ---- the annotated object (type id at vtable +0x38, Cast at +0x0c) ----
struct Obj {
    virtual void o00(); virtual void o01(); virtual void o02();
    virtual void* Cast(uint32_t id);          // +0x0c
    virtual void o04(); virtual void o05(); virtual void o06(); virtual void o07();
    virtual void o08(); virtual void o09(); virtual void o0a(); virtual void o0b();
    virtual void o0c(); virtual void o0d();
    virtual uint32_t GetType();               // +0x38
};

struct Label {
    void*   mpObj0;   // +0x00  (object whose vtable the helpers use; [label] in the original)
    Obj*    mpObj;    // +0x04
    bool    mFlag;    // +0x08
    float   mX;       // +0x0c
    float   mY;       // +0x10
    float   mX2;      // +0x14
    float   mY2;      // +0x18
    float   f1c;      // +0x1c
    float   f20;      // +0x20
    float   f24;      // +0x24
    float   f28;      // +0x28
    float   f2c;      // +0x2c
    float   f30;      // +0x30
    uint8_t b34;      // +0x34
    float   f38;      // +0x38
    float   f3c;      // +0x3c
    float   f40;      // +0x40
    float   f44;      // +0x44
    float   f48;      // +0x48
    float   f4c;      // +0x4c
    void*   p50;      // +0x50
    IV*     p54;      // +0x54
    IV*     p58;      // +0x58
    IV*     p5c;      // +0x5c
    IV*     p60;      // +0x60
    void*   p64;      // +0x64
    void*   p68;      // +0x68
    void*   p6c;      // +0x6c
    IV*     p70;      // +0x70
    IV*     p74;      // +0x74
    void*   p78;      // +0x78
    IV*     p7c;      // +0x7c
    IV*     p80;      // +0x80
    IV*     p84;      // +0x84
    IV*     p88;      // +0x88
    void*   p8c;      // +0x8c
    IV*     p90;      // +0x90
    IV*     p94;      // +0x94
    IV*     p98;      // +0x98
    IV*     p9c;      // +0x9c
    void*   pA0;      // +0xa0
    void*   pA4;      // +0xa4
    IV*     pA8;      // +0xa8
    IV*     pAc;      // +0xac
};

// ---- globals ----
extern "C" void* SP_GetCurrentGameMode(void);           // 0x00b5b800
extern "C" { extern char DAT_01654c01[], DAT_01654c02[], DAT_01654c05[], DAT_01654c10[]; }
extern float DAT_01464980;                              // FLT_MAX sentinel
extern float DAT_01485378;                              // 0.0f sentinel
extern float DAT_01473c70;                              // subtract constant in FUN_00b6a720
extern float DAT_013f2100;                              // 255.0f
extern int   DAT_0156ae80, DAT_0156ae84, DAT_0156ae88, DAT_0156ae8c, DAT_0156ae90;
extern int   DAT_0158133c;

// ---- helpers (signatures approximated; several take register inputs in the original) ----
void* __cdecl operator_new(uint32_t size, const char* name, int, int, int, int);   // 0x00f473a0
void  __fastcall FUN_00743b50(void** p);                                           // 0x00743b50
void* __cdecl GetMainWindowArea(float* out);                                        // 0x00805ea0
bool  __cdecl FUN_00b6a200(Obj* o, float* p2);                                     // 0x00b6a200
bool  __cdecl FUN_00b69cf0(void* c, float* p2, float* p3);                         // 0x00b69cf0
bool  __cdecl FUN_00b67ef0(void* c, float* p2, float* p3);                         // 0x00b67ef0
bool  __cdecl FUN_00b69010(Label* l, float a, float b);                            // 0x00b69010
void  __cdecl FUN_00b686a0(IV* p);                                                 // 0x00b686a0
int   __cdecl FUN_00b675a0(int a);                                                 // 0x00b675a0
int   __cdecl FUN_00b67530(int a, char b);                                         // 0x00b67530
int   __cdecl FUN_00b674d0(int a);                                                 // 0x00b674d0
void  __cdecl FUN_00b67440(IV* ui, int color, float a);                            // 0x00b67440
void  __cdecl FUN_00b693b0(void* src, IV* ui, float a);                            // 0x00b693b0
void  __cdecl FUN_00b6a720(Label* l, const float* pair, int v, int b1, int b2);    // 0x00b6a720
void  __cdecl SetNumberString(int value, int hi, wchar_t* buf, int count);         // 0x00881ae0
int   __cdecl WStr_Format(wchar_t* buf, const wchar_t* fmt, ...);                  // 0x0041e050
void  __cdecl SetTooltipText(IV* win, const wchar_t* text, int a, int b);          // 0x00806de0
void* __cdecl SP_cTribeModeStrategy_Instance(void);                                // 0x00cd40b0
int   __cdecl FUN_00d09660(void* p);                                               // 0x00d09660
int   __cdecl FUN_00cd5750(void* p);                                               // 0x00cd5750
IV*   __cdecl FindWindowByID(void* layout, uint32_t id, int);                      // 0x008105b0
void* __cdecl GetPlayerTribe(void);                                                // 0x00bfc5f0 chain
int   __cdecl FUN_00c8f3a0(void* tribe);                                           // 0x00c8f3a0
int   __cdecl SP_GetMaxPopulation(void* tribe);                                    // 0x00c8eae0
int   __cdecl FUN_00a1ad10(void* tribe);                                           // 0x00a1ad10

// minimal eastl::basic_string<wchar_t> + cString views (opaque: only calls are emitted)
struct eastl_string {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap; int mAlloc0; int mAlloc1;
    eastl_string& operator=(const wchar_t*);
    eastl_string& operator+=(const wchar_t*);
    const wchar_t* c_str() const { return mpBegin; }
};
struct cString {
    eastl_string mStr;
    cString(uint32_t table, uint32_t id, int flag);
    ~cString();
    const wchar_t* GetText();
};

// =====================================================================================
// @ 0x00b6a420
bool FUN_00b6a420(Obj* obj, float* p2, float* p3)
{
    int t = (int)obj->GetType();
    switch (t) {
    case 0x3a25119:
    case 0x137e8e0:
    case 0xee02c7:
    case 0xd0036e08:
    case 0x116d858:
    case 0x1b92b27:
    case 0x175cdc9:
    case 0x1a55e4d:
    case 0x2a8fe3c:
    case 0xecade42:
    case 0x629baec:
    case 0x436f315:
    case 0x4e3faaf:
    case 0x70704db:
    case 0x4f176642:
    case 0xff10521:
    case 0x1007ae63:
    case 0x4f396a66:
        break;
    case 0xb033b403:
        return FUN_00b6a200(obj, p2);
    default:
        return false;
    }
    void* c = obj->Cast(0x1186577);
    if (SP_GetCurrentGameMode() == (void*)DAT_01654c10)
        return FUN_00b69cf0(c, p2, p3);
    return FUN_00b67ef0(c, p2, p3);
}

// =====================================================================================
// @ 0x00b6a530
struct Stopwatch {
    uint64_t mnStart;
    uint64_t mnTotal;
    int      mnUnits;
    float    mfCoeff;
    void Init(int units, int coeff);                                      // 0x0093a560
};

struct Mgr {
    void*   mpPool;      // +0x00
    int     f04;         // +0x04
    int     f08;         // +0x08
    int     f0c;         // +0x0c
    int     f10;         // +0x10
    int     f14;         // +0x14
    int     f18;         // +0x18
    int     g1c;         // +0x1c
    int     g20, g24, g28, g2c;
    uint8_t b30;         // +0x30
    uint8_t pad31[7];
    Stopwatch sw;        // +0x38
    int     f50;         // +0x50
    int     f54;         // +0x54
    void InitPool(int a, int b);                                          // 0x00b72080
};

Mgr* g_pMgr;             // 0x01687348

void FUN_00b6a530(void)
{
    Mgr* p = (Mgr*)operator_new(0x58, "Simulator", 0, 0, 0, 0);
    if (p) {
        FUN_00743b50((void**)p);
        p->sw.Init(0, 0);
    }
    g_pMgr = p;
    p->InitPool(0x130, 0x20);
    Mgr* m = g_pMgr;
    m->g1c = DAT_0156ae80;
    m->g20 = DAT_0156ae84;
    m->g24 = DAT_0156ae88;
    m->g28 = DAT_0156ae8c;
    m->g2c = DAT_0156ae90;
    g_pMgr->b30 = 1;
    Stopwatch tmp;
    tmp.Init(4, 0);
    g_pMgr->sw = tmp;
    g_pMgr->f50 = -1;
}

// =====================================================================================
// @ 0x00b6a610
void FUN_00b6a610(Label* p)
{
    float lim = DAT_01464980;
    if (p->f48 == lim || p->f4c == lim) {
        p->mFlag = FUN_00b6a420(p->mpObj, &p->mX, &p->mX2);
        return;
    }
    p->mX = p->f48;
    p->mY = p->f4c;
    float fVar1 = p->mX;
    float fVar2 = p->mY;
    p->mX2 = p->mX;
    p->mY2 = p->mY;
    float local[4];
    float* r = (float*)GetMainWindowArea(local);
    if (r[0] <= fVar1 && r[1] <= fVar2 && fVar1 < r[2] && fVar2 < r[3])
        p->mFlag = true;
    else
        p->mFlag = false;
}

// =====================================================================================
// @ 0x00b6a6e0  (thiscall; returns +0x14 of the map node at +0x08)
struct FeedbackNode { char pad[0x14]; uint32_t mValue; };
struct Iterator { void* node; };
struct FeedbackMap {
    Iterator* find(Iterator* out, const uint32_t* key);   // 0x00e5c780
};
struct FeedbackMgr {
    char pad00[8];
    FeedbackMap map;                                      // +0x08
    uint32_t GetEvent(uint32_t key);
};
uint32_t FeedbackMgr::GetEvent(uint32_t key)
{
    Iterator it;
    Iterator* r = map.find(&it, &key);
    return *(uint32_t*)((char*)r->node + 0x14);
}

// =====================================================================================
// @ 0x00b6a700
struct Glyph { char pad[4]; void* a; void* b; void* c; };
Glyph* __fastcall FUN_00b6a700(Glyph* p)
{
    void* c = (void*)0x1667bac;
    p->a = c;
    p->b = c;
    p->c = (void*)0x1667bae;
    return p;
}

// =====================================================================================
// @ 0x00b6a720 -- original: EDI = label, EAX = float pair, more data on the caller's stack.
void FUN_00b6a720(Label* l, const float* pair, int v, int b1, int b2)
{
    IV* w54 = l->p54;
    float x = pair[0];
    float y = pair[1];
    ((void(__thiscall*)(IV*, float, float))VT(w54, 0x64))(w54, x, y - DAT_01473c70);

    if (!b1) {
        ((void(__thiscall*)(IV*, int, int))VT(w54, 0x7c))(w54, 1, 0);
        return;
    }
    if (l->f38 == DAT_01485378) {
        ((void(__thiscall*)(IV*, int, int))VT(w54, 0x7c))(w54, 1, 0);
    } else {
        int a = (int)(l->f38 * DAT_013f2100);
        ((void(__thiscall*)(IV*, uint32_t))VT(w54, 0x5c))(w54, ((uint32_t)a << 24) | 0xffffff);
        ((void(__thiscall*)(IV*, int, int))VT(w54, 0x7c))(w54, 1, 1);
    }
    IV* w58 = l->p58;
    if (l->f44 == DAT_01485378) {
        ((void(__thiscall*)(IV*, int, int))VT(w58, 0x7c))(w58, 1, 0);
    } else {
        int a = (int)(l->f44 * DAT_013f2100);
        ((void(__thiscall*)(IV*, uint32_t))VT(w58, 0x5c))(w58, ((uint32_t)a << 24) | 0xffffff);
        ((void(__thiscall*)(IV*, int, int))VT(w58, 0x7c))(w58, 1, 1);
    }
    if (l->p5c)
        ((void(__thiscall*)(IV*, int))VT(l->p5c, 0x80))(l->p5c, v);
    FUN_00b67440(l->p60, (int)(unsigned int)pair, 1.0f);
    if (l->p70 && !l->b34) {
        FUN_00b693b0(l->p64, l->p70, 1.0f);
        FUN_00b693b0(l->p68, l->p70, 1.0f);
        FUN_00b693b0(l->p6c, l->p70, 1.0f);
    }
    void* mode = SP_GetCurrentGameMode();
    int r = -1;
    if (mode == (void*)DAT_01654c01 || mode == (void*)DAT_01654c10) {
        r = FUN_00b67530(b2, 0);
    } else if (mode == (void*)DAT_01654c02 || mode == (void*)DAT_01654c05) {
        r = FUN_00b674d0(b2);
    }
    IV* w90 = l->p90;
    IV* q = w90 ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w90, 0x0c))(w90, 0xeeee8218)) : 0;
    if (r == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w90, 0x14))(w90, r);
    }
    if (l->p74) {
        wchar_t buf[32];
        SetNumberString(b2, b2 >> 31, buf, 0x20);
        ((void(__thiscall*)(IV*, const wchar_t*))VT(l->p74, 0x80))(l->p74, buf);
    }
}

// =====================================================================================
// @ 0x00b6a970 -- original: label in EAX.
bool FUN_00b6a970(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, Vec3 col,
                  int a, int b, float dt)
{
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return false;
    }
    FUN_00b6a720(e, (const float*)pos, a, b, (int)dt);
    return true;
}

// =====================================================================================
// @ 0x00b6a9d0 -- original: label in EAX.
void FUN_00b6a9d0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name,
                  const Vec3& v, int a, int b, int c, float dt)
{
    int m = FUN_00b675a0(a);
    IV* w = e->p94;
    IV* q = w ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w, 0x0c))(w, 0xeeee8218)) : 0;
    if (m == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w, 0x14))(w, m);
    }
    IV* w2 = e->p98;
    IV* q2 = w2 ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w2, 0x0c))(w2, 0xeeee8218)) : 0;
    ((void(__thiscall*)(IV*, int, int))VT(q2, 0x7c))(q2, 1, 1);
    ((void(__thiscall*)(IV*, int))VT(w2, 0x14))(w2, 0);
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return;
    }
    FUN_00b6a720(e, (const float*)pos, b, c, (int)dt);
}

// =====================================================================================
// @ 0x00b6aae0 -- original: label in EAX.
void FUN_00b6aae0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name,
                  const Vec3& v, int a, int b, int c, int d, float dt)
{
    int m = FUN_00b675a0(c);
    IV* w = e->p9c;
    IV* q = w ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w, 0x0c))(w, 0xeeee8218)) : 0;
    if (m == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w, 0x14))(w, m);
    }
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return;
    }
    FUN_00b6a720(e, (const float*)pos, b, d, (int)dt);
}

// =====================================================================================
// @ 0x00b6abc0 -- original: label in EAX.
static int ModeFromValue(int v)
{
    switch (v + 1) {
    case 1: return 2;
    case 2: return 0;
    case 3: return 3;
    case 5: return 1;
    default: return -1;
    }
}
void FUN_00b6abc0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v,
                  int a, int b, float f1, float f2, int c, int d, float dt)
{
    int m = ModeFromValue(c);
    IV* w = e->p9c;
    IV* q = w ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w, 0x0c))(w, 0xeeee8218)) : 0;
    if (m == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w, 0x14))(w, m);
    }
    wchar_t buf1[64];
    SetNumberString((int)f1, (int)f1 >> 31, buf1, 0x40);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->p7c, 0x80))(e->p7c, buf1);
    wchar_t buf2[64];
    SetNumberString((int)f2, (int)f2 >> 31, buf2, 0x40);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->p84, 0x80))(e->p84, buf2);

    int m2 = ModeFromValue(c);
    IV* w80 = e->p80;
    IV* q80 = w80 ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w80, 0x0c))(w80, 0xeeee8218)) : 0;
    if (m2 == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q80, 0x7c))(q80, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q80, 0x7c))(q80, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w80, 0x14))(w80, m2);
    }
    ((void(__thiscall*)(IV*, int, int))VT(e->p88, 0x7c))(e->p88, 1, 1);
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return;
    }
    FUN_00b6a720(e, (const float*)pos, b, d, (int)dt);
}

// =====================================================================================
// @ 0x00b6adf0 -- original: label in EAX.
void FUN_00b6adf0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v,
                  int a, int b, int c, int d, float dt)
{
    wchar_t buf[128];
    WStr_Format(buf, L"%d / %d", c, d);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->pA8, 0x80))(e->pA8, buf);

    if (SP_GetCurrentGameMode() == (void*)DAT_01654c02) {
        bool show = false;
        if (e->mpObj) {
            Obj* t = (Obj*)e->mpObj->Cast(0xee02c7);
            if (t && ((bool(__thiscall*)(Obj*))VT(t, 0x58))(t)) {
                void* tribe = SP_cTribeModeStrategy_Instance();
                int v2 = ((int(__thiscall*)(void*))VT(tribe, 0x70))(tribe);
                if (!FUN_00d09660((void*)v2)) {
                    show = true;
                    IV* win = FindWindowByID(e->p50, 0x625cd52, 1);
                    if (win) {
                        void* tribe2 = SP_cTribeModeStrategy_Instance();
                        char bv = (char)FUN_00cd5750(tribe2);
                        ((void(__thiscall*)(IV*, int, int))VT(win, 0x7c))(win, 2, bv);
                        eastl_string tt;
                        tt = L"";
                        cString s1(0xc0152a6d, 0x65fc366, 0);
                        tt += s1.GetText();
                        void* tr = GetPlayerTribe();
                        if (tr) {
                            if (FUN_00c8f3a0(tr) < DAT_0158133c) {
                                cString s2(0xc0152a6d, 0x65fc367, 0);
                                tt += s2.GetText();
                            } else if (FUN_00c8f3a0(tr) >= SP_GetMaxPopulation(tr)) {
                                cString s3(0xc0152a6d, FUN_00a1ad10(tr) < 2 ? 0x65fc368 : 0x65fc369, 0);
                                tt += s3.GetText();
                            }
                        }
                        SetTooltipText(win, tt.c_str(), -1, 1);
                    }
                }
            }
        }
        ((void(__thiscall*)(IV*, int, int))VT(e->pAc, 0x7c))(e->pAc, 1, show ? 1 : 0);
    }
    if (!FUN_00b69010(e, x, dt))
        FUN_00b686a0((IV*)e->mpObj0);
    else
        FUN_00b6a720(e, (const float*)pos, b, d, (int)dt);
}

// =====================================================================================
// @ 0x00b6b0a0 -- original: label in EAX.
void FUN_00b6b0a0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v,
                  int a, int b, int c, float dt)
{
    wchar_t buf[128];
    WStr_Format(buf, L"%d / %d", b, c);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->pA8, 0x80))(e->pA8, buf);
    if (SP_GetCurrentGameMode() == (void*)DAT_01654c02 && e->mpObj)
        ((void(__thiscall*)(Obj*))VT(e->mpObj, 0x20))(e->mpObj);
    if (!FUN_00b69010(e, x, dt))
        FUN_00b686a0((IV*)e->mpObj0);
    else
        FUN_00b6a720(e, (const float*)pos, a, 0, (int)dt);
}
