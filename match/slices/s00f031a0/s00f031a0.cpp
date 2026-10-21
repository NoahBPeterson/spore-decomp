// Slice s00f031a0 -- SP::ScenarioTutorialsPlacement (vtable 0x148b788) virtual methods
// plus UI::cScenarioTutorialsChecklistUI callout/step helpers.
// Region flags: /O2 /MD /Gy /TP
#include "types.h"

extern void*    g_mgr;          // 0x016c7b88 (singleton pointer variable)
extern void*    g_Simulator;    // 0x016c7aa4
extern void*    g_15f7cf4;      // 0x015f7cf4
extern uint8_t  g_015acb40;     // 0x015acb40
extern uint8_t  g_016c7b34[];   // 0x016c7b34
extern uint8_t  g_15ad328[];    // 0x015ad328 (PL instance)
extern uint8_t  g_16c7c08[];    // 0x016c7c08
extern uint8_t  g_015ad45c[];   // 0x015ad45c
extern uint8_t  g_015ad468[];   // 0x015ad468
extern uint8_t  g_015ad450[];   // 0x015ad450

extern "C" void  __cdecl operator_delete_(void*);              // 0x00f47380
extern "C" void* __cdecl FUN_00eec0d0(void*);                  // 0x00eec0d0
extern "C" void* __cdecl FUN_00eebf80(void*);                  // 0x00eebf80
extern "C" void* __cdecl FUN_00b18e00(void*);                  // 0x00b18e00
extern "C" void* __cdecl FUN_00eeca30(void*);                  // 0x00eeca30
extern "C" void* __cdecl FUN_00ae66d0(void*);                  // 0x00ae66d0
extern "C" void  __cdecl FUN_00efcec0(void*, void*);           // 0x00efcec0
extern "C" void  __cdecl FUN_00eef4b0(void*);                  // 0x00eef4b0
extern "C" void  __cdecl FUN_00eef7d0(void*);                  // 0x00eef7d0
extern "C" void* __cdecl FUN_0067dd60();                       // 0x0067dd60
extern "C" void* __cdecl FUN_0067dd10();                       // 0x0067dd10
extern "C" void* __cdecl FUN_00b3d240();                       // 0x00b3d240
extern "C" void* __cdecl FUN_00b3d300();                       // 0x00b3d300
extern "C" void  __cdecl FUN_00809db0(void*, void*);           // 0x00809db0
extern "C" void  __cdecl SPUI_UpdateMouseFocus(int);           // 0x00804f50
extern "C" void* __cdecl EA_ConvertToString16(void*, int);     // 0x0093c6d0
extern "C" void  __cdecl SPUI_AutoSizeWindowForText(void*, int, int); // 0x00806e40
extern "C" void  __cdecl EA_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
extern "C" bool  __cdecl GetYTPrompt();                        // 0x0063b890

// ------------------------------------------------------------------ classes

struct Big {
    char  pad0[0x28];
    char* begin;        // +0x28
    char* end;          // +0x2c
    char  pad2[0x1dc];  // +0x30 .. +0x20b
    int*  p20c;         // +0x20c
    char  pad3[0x24];   // size 0x234
    Big*  init();                 // 0x00f2aac0
    Big*  copyFrom(Big*);         // 0x00dfdfe0
    Big*  assign(Big*);           // 0x00dfd3a0
};

struct Vec {
    void destroy(void* b, void* e);   // 0x00dfb850
};

struct GObj;

struct GObj {
    void*   vtable;     // +0x00
    char pad4[0x0c];
    void* f10;          // +0x10
    char pad14[0x5a];   // -> +0x6e
    uint8_t b6e;        // +0x6e
    void InitThing();                 // 0x00f3c060
    void KillThing();                 // 0x00f3c0b0
    void* GetAt(void*);               // 0x00f3cb30 ret 4
    void f401a0();                    // 0x00f401a0
    void f40370();                    // 0x00f40370
    void f414b0();                    // 0x00f414b0
    void f427c0();                    // 0x00f427c0
    void f42a00(void*);               // 0x00f42a00 ret 4
    void f45a80();                    // 0x00f45a80
    char ScenarioNode_Load(void*);    // 0x00f3ff70 ret 4
    void f32880(void*);               // 0x00f32880 ret 4
    void f347e0();                    // 0x00f347e0
    void f3da90(void*, int);          // 0x00f3da90 ret 8
    void f3bbd0(void*, int);          // 0x00f3bbd0 ret 8
    void* f3e8a0(void*);              // 0x00f3e8a0 ret 4
    void f_ed4e90();                  // 0x00ed4e90
    void f_ed4f00(int);               // 0x00ed4f00 ret 4
};

struct Tut {
    void f_eeff80();                  // 0x00eeff80
};

struct HintObj {
    void ToggleHint(int, int);        // 0x00efbbe0 ret 8
};

struct RefObj {
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void v0c(int);
};

struct NounMgr {
    void RemoveNoun(void*);           // 0x00b225d0 ret 4
};

struct MgrB {
    void f33ce0(int);                 // 0x00b33ce0 ret 4
    void f33cf0(int);                 // 0x00b33cf0 ret 4
};

struct Mgr {
    int   f0;           // +0x00
    void* f4;           // +0x04
    void* f8;           // +0x08
    void* fC;           // +0x0c
    void* f10;          // +0x10
    void* f14;          // +0x14
    void* f18;          // +0x18
    void* f1c;          // +0x1c
    void* f20;          // +0x20
    void* f24;          // +0x24
    void* f28;          // +0x28
    void* f2c;          // +0x2c
    char  vec30[0x24];  // +0x30
    void* f54;          // +0x54
    void* f58;          // +0x58
    void* f5c;          // +0x5c
    void* f60;          // +0x60
    char  pad64[4];
    int   f68;          // +0x68
    char  pad6c[0x20];  // +0x6c .. +0x8b
    char  vec8c[0x18];  // +0x8c
    uint8_t fA4;        // +0xa4
};

#define MGR ((Mgr*)g_mgr)

// ScenarioTutorialsPlacement (vtable 0x148b788)
struct PL {
    void** vtable;      // +0x00
    uint8_t b4;         // +0x04
    uint8_t b5;         // +0x05
    uint8_t b6;         // +0x06
    uint8_t b7;         // +0x07
    GObj*  pGame;       // +0x08
    Big*   pC;          // +0x0c
    void*  p10;         // +0x10

    void f031a0();
    void f031d0();
    void f03290();
    bool f03320();
    void f03440();
    bool f036f0();
    int  f03890(int, int, float);   // ret 0xc
    void f00610(void*, float);      // 0x00f00610 ret 8
    char f00850(void*);             // 0x00f00850 ret 4
    void f02670();                  // 0x00f02670
    void f_efec90(void*);           // 0x00efec90 ret 4
    void f_efee60(void*);           // 0x00efee60 ret 4
    char Scenario_CheckObj(void*);  // 0x00efeae0 ret 8
    void f_efebb0(void*);           // 0x00efebb0 ret 4
};

struct Vec30 {
    void add(void*);                  // 0x00c68190 ret 4
    void check(void*, bool*);         // 0x00c688a0 ret 8
    void clear();                     // 0x00c68840
};

struct CamObj {
    float* f_b10260();                // 0x00b10260
    float* f_644a70();                // 0x00644a70
    float  f_c37540();                // 0x00c37540
};

// Generic UTFWin window interface: one virtual per 4-byte vtable slot.
struct IW {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c(unsigned);
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28(int);
    virtual void* v2c();
    virtual void* v30();
    virtual void* v34(int, bool);
    virtual float* v38();
    virtual void* v3c();
    virtual void* v40();
    virtual void* v44();
    virtual void* v48();
    virtual void* v4c();
    virtual void* v50();
    virtual void* v54();
    virtual void* v58();
    virtual void* v5c();
    virtual void* v60();
    virtual void* v64();
    virtual void* v68();
    virtual void* v6c();
    virtual void  v70(float, float);
    virtual void* v74();
    virtual void* v78();
    virtual void  v7c(int, int);
    virtual void  v80(void*);
    virtual void* v84();
    virtual void* v88();
    virtual void* v8c();
    virtual void* v90();
    virtual void* v94();
    virtual void* v98();
    virtual void* v9c();
    virtual void* va0();
    virtual void* va4();
    virtual void* va8();
    virtual void* vac();
    virtual void* vb0();
    virtual void* vb4();
    virtual void* vb8(unsigned);
    virtual void* vbc();
    virtual void* vc0();
    virtual void* vc4();
    virtual void* vc8();
    virtual void* vcc();
    virtual void* vd0();
    virtual void* vd4();
    virtual void* vd8();
    virtual void* vdc();
    virtual void* ve0();
    virtual void* ve4();
    virtual void* ve8();
    virtual void* vec();
    virtual void* vf0(unsigned, bool);
    virtual void* vf4();
    virtual void* vf8();
    virtual void* vfc();
};

struct Layout {
    IW* FindWindowByID(unsigned, bool);   // 0x008105b0 ret 8
};

struct V3 { float x, y, z; };

struct Q2c {
    virtual void* d00();
    virtual void* d04();
    virtual void* d08();
    virtual void* d0c();
    virtual void* d10();
    virtual void* d14();
    virtual void* d18();
    virtual void* d1c();
    virtual void* d20();
    virtual void* d24();
    virtual void* d28();
    virtual V3*   v2c(V3* out, void* id);
};

struct Str16 { void* begin; void* pad4; void* end; void* padC; };

// UI::cScenarioTutorialsChecklistUI (extended retail layout)
struct UI {
    void*   vtable;     // +0x00
    uint8_t f4;         // +0x04
    uint8_t b5;         // +0x05
    uint8_t b6;         // +0x06
    uint8_t b7;         // +0x07
    void*   p8;         // +0x08
    void*   pC;         // +0x0c
    void*   p10;        // +0x10
    void*   h14;        // +0x14
    void*   h18;        // +0x18
    void*   h1c;        // +0x1c
    void*   h20;        // +0x20
    void*   h24;        // +0x24
    int     step;       // +0x28
    Layout* layout;     // +0x2c
    IW*     w30;        // +0x30
    IW*     w34;        // +0x34
    IW*     w38;        // +0x38
    char    pad3c[0x18];
    int     f54;        // +0x54
    char    pad58[0x0c];
    int     f64;        // +0x64
    char    pad68[0x11];
    uint8_t b79;        // +0x79
    char    pad7a[0x52];
    RefObj* rcc;        // +0xcc
    void**  vD0;        // +0xd0
    void**  vD4;        // +0xd4
    char    padD8[0x0c];
    void**  vE4;        // +0xe4

    void f03d20();
    void f03d50();
    void f03d80();
    void f03de0();
    void f03e20();
    void f03e40();
    void f03e90();
    void f03fa0();
    void f03fc0(int);
    bool f03ff0(unsigned, V3*, char);
    void f04070(char);
    void f040e0(int);
};

struct AppObj {
    void* v50();
    void* v38();
};

// ------------------------------------------------------------------ group A

// @ 0x00f031a0
void PL::f031a0()
{
    if (g_mgr) {
        Big* o = (Big*)FUN_00eebf80(*(void**)((char*)g_mgr + 4));
        if (o)
            pC->assign(o);
    }
}

// @ 0x00f031d0
void PL::f031d0()
{
    Big* o = (Big*)FUN_00eebf80(*(void**)((char*)g_mgr + 4));
    if (o) {
        Big tmp;
        tmp.copyFrom(o);
        pGame->InitThing();
        void* v = pGame->GetAt(&tmp);
        void* w = FUN_00eec0d0(v);
        void** slot = (void**)((char*)vtable + 0x20);
        (*(void (__thiscall**)(PL*, void*))slot)(this, w);

        if (tmp.p20c && tmp.p20c[-1])
            operator_delete_(tmp.p20c);
        ((Vec*)&tmp.begin)->destroy(tmp.begin, tmp.end);
        if (tmp.begin && ((int*)tmp.begin)[-1])
            operator_delete_(tmp.begin);
    } else {
        pGame->InitThing();
    }
}

// @ 0x00f03290
void PL::f03290()
{
    pGame = g_Simulator ? (GObj*)*(void**)((char*)g_Simulator + 0x74) : 0;
    (*(void (__thiscall**)(PL*, int))((char*)vtable + 0x18))(this, 0);
    b5 = 0;
    b6 = 0;
    b7 = 0;

    Big tmp;
    pC->assign(tmp.init());

    if (tmp.p20c && tmp.p20c[-1])
        operator_delete_(tmp.p20c);
    ((Vec*)&tmp.begin)->destroy(tmp.begin, tmp.end);
    if (tmp.begin && ((int*)tmp.begin)[-1])
        operator_delete_(tmp.begin);
}

// @ 0x00f03320
bool PL::f03320()
{
    if (!b5) {
        if (g_015acb40 && MGR->f4)
            pGame->f3bbd0(MGR->f4, 1);
        return true;
    }
    ((Tut*)g_016c7b34)->f_eeff80();
    Big* o = (Big*)FUN_00eebf80(MGR->f4);
    GObj* g = (GObj*)FUN_00eeca30(o);
    void* w = FUN_00ae66d0(g);
    if (!o) {
        b5 = 0;
        return false;
    }
    pGame->f3da90(o, 1);
    GObj* p = (GObj*)*(void**)((char*)g_Simulator + 0x74);
    bool notok = ((PL*)g_15ad328)->Scenario_CheckObj(w) == 0;
    p->f3bbd0(w, notok);

    if (g->b6e) {
        FUN_00efcec0(MGR->f4, g);
        f031d0();
        pGame->f401a0();
    } else {
        pGame->f45a80();
        pGame->f427c0();
        GObj* q = (GObj*)*(void**)((char*)g_Simulator + 0x18);
        q->f32880((void*)o);
        q->f347e0();
        pGame->f401a0();
    }
    b5 = 0;
    return true;
}

// @ 0x00f03440
void PL::f03440()
{
    void* h = MGR->fC;
    void* o = FUN_00eebf80(h);
    GObj* g = (GObj*)FUN_00b18e00(h);

    if (h) {
        IW* q = (IW*)((IW*)h)->v0c(0x074e0069);
        if (q) {
            *(uint8_t*)((char*)q + 0x12b) = 1;
            *(uint8_t*)((char*)q + 0x128) = 0;
            (*(void (__thiscall**)(char*, void*))((char*)*(void**)((char*)q + 0x34) + 0x3c))((char*)q + 0x34, (char*)q + 0x44);
        }
    }

    if (MGR->f10) {
        IW* r = (IW*)((IW*)MGR->f10)->v0c(0x076c67df);
        if (r) {
            if ((void*)r == MGR->f28) {
                r->v64();
            } else {
                ((Vec30*)((char*)MGR + 0x30))->add(r);
                Big* b = (Big*)FUN_00eebf80(MGR->f4);
                GObj* q = (GObj*)pGame->f3e8a0(*(void**)b);
                if (*(uint8_t*)((char*)q + 0x20) == 0) {
                    bool ok;
                    ((Vec30*)((char*)MGR + 0x30))->check(b->begin + MGR->f0 * 0x34 + 0x1c, &ok);
                    if (ok)
                        *(int*)(b->begin + MGR->f0 * 0x34 + 0x30) = 2;
                } else {
                    int n = (int)((b->end - b->begin) / 0x34);
                    for (int i = 0; i < n; ++i) {
                        char* e = b->begin + i * 0x34;
                        bool ok;
                        ((Vec30*)((char*)MGR + 0x30))->check(e + 0x1c, &ok);
                        if (ok)
                            *(int*)(e + 0x30) = 2;
                    }
                }
                ((HintObj*)*(void**)((char*)g_Simulator + 0xd4))->ToggleHint(0x61, 0x62);
            }
        }
    }

    if (g) {
        if (g->b6e) {
            FUN_00efcec0(MGR->fC, g);
            f031d0();
            pGame->f414b0();
        } else {
            pGame->f45a80();
            pGame->f414b0();
        }
    } else if (g_015acb40 && MGR->f4) {
        pGame->f3bbd0(MGR->f4, 1);
    }

    IW* p = (IW*)FUN_00b3d240();
    void* pvt = *(void**)p;
    void* cur = ((void* (__thiscall*)(void*))*(void**)((char*)pvt + 0x34))(p);
    if (cur != MGR->f10) {
        GObj* q = (GObj*)FUN_00b18e00(MGR->f10);
        if (q) {
            void* x = FUN_00ae66d0(q);
            ((IW*)q)->v28(0);
            if (x == MGR->f8 && MGR->f8) {
                void* y = MGR->f8;
                MGR->f8 = 0;
                (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
            }
            IW* z = (IW*)((IW*)q)->vac();
            if (z)
                *(uint32_t*)((char*)z + 4) &= 0xfffffff7;
        }
    }

    if (MGR->fC) {
        void* y = MGR->fC;
        MGR->fC = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
    }
    if (MGR->f10) {
        void* y = MGR->f10;
        MGR->f10 = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
    }
}

// @ 0x00f036f0
bool PL::f036f0()
{
    Big* o = (Big*)FUN_00eebf80(MGR->fC);
    GObj* g = (GObj*)FUN_00b18e00(MGR->fC);
    uint8_t b6e = g->b6e;
    if (b6e)
        FUN_00efcec0(MGR->fC, g);

    bool bb = (b6 != 0) || (b7 != 0);
    bool result = false;
    if (b6e) {
        if (bb) {
            pGame->f42a00(o);
            pGame->f414b0();
            pGame->KillThing();
            (*(void (__thiscall**)(PL*, int))((char*)vtable + 0x20))(this, 0);
            ((GObj*)*(void**)((char*)g_Simulator + 0x14))->f_ed4e90();
            result = true;
            goto done_reg;
        }
        if (!MGR->fA4) {
            f031d0();
            goto done;
        }
    }

    if (b6)
        FUN_00eef7d0(o);
    if (!pGame->ScenarioNode_Load(o))
        *(uint32_t*)((char*)o + 0x224) |= 2;
    else
        *(uint32_t*)((char*)o + 0x224) &= ~2;

    if (b6e && MGR->fA4)
        pGame->f40370();
    else
        pGame->f414b0();

    pGame->f401a0();
    pGame->f45a80();
    pGame->f427c0();
    f_efebb0(o);
    {
        IW* q = (IW*)((IW*)g)->vb8(0x074e0069);
        if (q) {
            *(uint8_t*)((char*)q + 0x12b) = 1;
            *(uint8_t*)((char*)q + 0x128) = 0;
            (*(void (__thiscall**)(char*, void*))((char*)*(void**)((char*)q + 0x34) + 0x3c))((char*)q + 0x34, (char*)q + 0x44);
        }
    }
    {
        GObj* q = (GObj*)*(void**)((char*)g_Simulator + 0x18);
        q->f32880(o);
        q->f347e0();
    }

done:
    result = false;
done_reg:
    if (MGR->fC) {
        void* y = MGR->fC;
        MGR->fC = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
    }
    return result;
}

// @ 0x00f03890
int PL::f03890(int msg, int, float c)
{
    void* f4 = MGR->f4;
    switch (msg) {
    case 0:
        {
            bool b = false;
            if (MGR->f10 == 0) {
                if (MGR->fC != 0 && f036f0())
                    b = true;
            } else {
                f03440();
            }
            MGR->f68 = 0;
            b6 = 0;
            b7 = 0;
            (*(void (__thiscall**)(PL*, int))((char*)vtable + 0x18))(this, 0);
            if (b)
                return 2;
            return 1;
        }
    case 1:
        if (!b4)
            return 0;
        if (MGR->f10 != 0) {
            if (MGR->fC != 0)
                return 0;
            if (MGR->f10 != 0) {
                f_efec90(f4);
                return 1;
            }
        }
        f_efee60(f4);
        return 1;
    case 6:
        f00610(f4, c);
        return 1;
    case 0xb:
        if (!b4)
            return 0;
        return (int)(unsigned char)f00850(f4);
    default:
        return 1;
    }
}

// @ 0x00f039a0
void __cdecl ScenarioTutorials_Teardown(char teardown)
{
    ((MgrB*)FUN_00b3d240())->f33ce0(0);
    ((MgrB*)FUN_00b3d240())->f33cf0(0);

    { void* p = MGR->f8;  if (p) { MGR->f8  = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }
    { void* p = MGR->f4;  if (p) { MGR->f4  = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }
    { void* p = MGR->f10; if (p) { MGR->f10 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }
    { void* p = MGR->fC;  if (p) { MGR->fC  = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }

    ((PL*)g_16c7c08)->f02670();
    ((PL*)g_15ad328)->f03290();
    FUN_00eef4b0((char*)g_mgr + 0x8c);

    { void* n = MGR->f24; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f24) { void* p = MGR->f24; MGR->f24 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f18; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f18) { void* p = MGR->f18; MGR->f18 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f1c; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f1c) { void* p = MGR->f1c; MGR->f1c = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f20; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f20) { void* p = MGR->f20; MGR->f20 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f14; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f14) { void* p = MGR->f14; MGR->f14 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f28; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f28) { void* p = MGR->f28; MGR->f28 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f2c; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f2c) { void* p = MGR->f2c; MGR->f2c = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }

    ((Vec30*)((char*)MGR + 0x30))->clear();

    { void* n = MGR->f5c; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f5c) { void* p = MGR->f5c; MGR->f5c = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f60; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f60) { void* p = MGR->f60; MGR->f60 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f54; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f54) { void* p = MGR->f54; MGR->f54 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR->f58; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR->f58) { void* p = MGR->f58; MGR->f58 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }

    if (teardown == 0) {
        IW* app = (IW*)FUN_0067dd10();
        IW* a = (IW*)app->v50();
        IW* b = (IW*)a->v38();
        if (b) {
            IW* c = (IW*)b->v0c(0x011966ed);
            if (c) {
                void* g = (void*)*(void**)((char*)g_Simulator + 0x74);
                void* cam = *(void**)((char*)g + 0x10);
                float* p1 = ((CamObj*)c)->f_b10260();
                *(float*)((char*)cam + 0x2c30) = p1[0];
                *(float*)((char*)cam + 0x2c34) = p1[1];
                *(float*)((char*)cam + 0x2c38) = p1[2];
                float* p2 = ((CamObj*)c)->f_644a70();
                *(float*)((char*)cam + 0x2c3c) = p2[0];
                *(float*)((char*)cam + 0x2c40) = p2[1];
                *(float*)((char*)cam + 0x2c44) = p2[2];
                *(float*)((char*)cam + 0x2c48) = p2[3];
                *(float*)((char*)cam + 0x2c4c) = ((CamObj*)c)->f_c37540();
            }
        }
    }
}

// ------------------------------------------------------------------ UI group

// @ 0x00f03d20
void UI::f03d20()
{
    FUN_00809db0(this ? (void*)((char*)this + 4) : 0, g_015ad45c);
    step = 2;
}

// @ 0x00f03d50
void UI::f03d50()
{
    FUN_00809db0(this ? (void*)((char*)this + 4) : 0, g_015ad468);
    step = 4;
}

// @ 0x00f03d80
void UI::f03d80()
{
    RefObj* r = rcc;
    if (r) {
        r->v0c(0);
        r = rcc;
        if (r) {
            rcc = 0;
            r->v4();
        }
    }
    void* h = h14;
    if (h) {
        h14 = 0;
        EA_RemoveHandler(h, h18, h1c, h20, h24);
    }
}

// @ 0x00f03de0
void UI::f03de0()
{
    ((int*)g_15f7cf4)[6] = f54;
    ((int*)g_15f7cf4)[7] = f64;
    FUN_00809db0(&f4, g_015ad450);
    step = 1;
}

// @ 0x00f03e20
void UI::f03e20()
{
    IW* w = layout->FindWindowByID(0x5b5ef50, true);
    w->v7c(1, false);
}

// @ 0x00f03e40
void UI::f03e40()
{
    char b = b79 == 0;
    b79 = b;
    w30->v7c(1, *(int*)&b);
    w34->v7c(1, b == 0);
    SPUI_UpdateMouseFocus(1);
}

// @ 0x00f03e90
void UI::f03e90()
{
    IW* w1 = layout->FindWindowByID(0x5baefc8, true);
    SPUI_AutoSizeWindowForText(w1, 0, 0);
    IW* w2 = layout->FindWindowByID(0x5652348, true);
    SPUI_AutoSizeWindowForText(w2, 1, 0);
    IW* w3 = layout->FindWindowByID(0x5b5bd80, true);
    SPUI_AutoSizeWindowForText(w3, 1, 0);
    if (w2 && w3) {
        float* a = w2->v38();
        float* b = w3->v38();
        w3->v70(a[0] - (b[2] - b[0]), b[1]);
    }
    IW* w4 = layout->FindWindowByID(0x5650568, true);
    w4->v7c(1, true);
    IW* w5 = layout->FindWindowByID(0x5665f58, true);
    IW* o = w5 ? (IW*)w5->v0c(0x8ed27e7a) : 0;
    o->v34(4, !GetYTPrompt());
    step = 3;
}

// @ 0x00f03fa0
void UI::f03fa0()
{
    IW* w = layout->FindWindowByID(0x5650568, true);
    w->v7c(1, false);
}

// @ 0x00f03fc0
void UI::f03fc0(int b)
{
    IW* w = layout->FindWindowByID(0x3f67620, true);
    w->v7c(1, b);
}

// @ 0x00f03ff0
bool UI::f03ff0(unsigned idx, V3* out, char alt)
{
    bool ok = idx < (unsigned)(vD4 - vD0);    if (ok) {
        void** base = alt ? vE4 : vD0;
        void* h = base[idx];
        V3 tmp;
        V3* r = ((Q2c*)FUN_0067dd60())->v2c(&tmp, h);
        *out = *r;
    }
    return ok;
}

// @ 0x00f04070
void UI::f04070(char b)
{
    int raw = *(int*)&b;
    int v = 0;
    if (b)
        v = ((unsigned)(vD4 - vD0) < 0x32) ? 1 : 0;
    int arg = (raw & ~0xff) | v;
    if (w38) {
        IW* q = (IW*)w38->vf0(0x78d57d8, true);
        if (q)
            q->v7c(2, arg);
    }
    GObj* s = (GObj*)*(void**)((char*)g_Simulator + 0x14);
    if (s)
        s->f_ed4f00(arg);
}

// @ 0x00f040e0
void UI::f040e0(int param)
{
    IW* w = layout->FindWindowByID(0x5650498, true);
    Str16 local;
    void* r = EA_ConvertToString16(&local, param);
    w->v80(*(void**)r);
    char* begin = (char*)local.begin;
    char* end = (char*)local.end;
    int n = (int)(end - begin) & ~1;
    if (n > 2 && begin)
        operator_delete_(begin);
}
