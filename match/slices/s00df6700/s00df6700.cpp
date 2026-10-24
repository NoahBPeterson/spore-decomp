// Slice s00df6700 -- GUI panel / layered-window helper methods
// (0x00df6700 .. 0x00df6dae, 6 functions).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <intrin.h>

#define PVN(n) virtual void pv##n();

struct MsgArg {                       // message payload passed to FUN_00df68c0
    uint32_t m00;                     // +0x00
    uint32_t m04;                     // +0x04
    int32_t  m08;                     // +0x08
};

// --------------------------------------------------------------- globals ----
extern void* g_p16a1344;              // 0x016a1344  GUI panel-id / layout manager
extern char  g_c16a0dd0[];            // 0x016a0dd0
extern const float g_f16a0da0;        // 0x016a0da0
extern void* g_p15fd91c;              // 0x015fd91c  _sAppPreferences_SP
extern const float g_f1485720;        // 0x01485720  _HK_REAL_ONE (1.0f)
extern const float g_posX;            // 0x016a1698
extern const float g_posY;            // 0x016a169c
extern const float g_posZ;            // 0x016a16a0
extern const float g_mat00;           // 0x016a1674
extern const float g_mat10;           // 0x016a1678
extern const float g_mat20;           // 0x016a167c
extern const float g_mat01;           // 0x016a1680
extern const float g_mat11;           // 0x016a1684
extern const float g_mat21;           // 0x016a1688
extern const float g_mat02;           // 0x016a168c
extern const float g_mat12;           // 0x016a1690
extern const float g_mat22;           // 0x016a1694
extern const float g_mtx16a1674[9];   // 0x016a1674  base matrix object
extern int (__stdcall *g_pQueryPerformanceCounter)(void*);  // 0x013cc2b8

// ---------------------------------------------------------- vtable shapes ---
struct NodeVt {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23)
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    virtual void v7c(int, void*);
};

struct RefVt {                        // ref-counted object stored at +0x34
    virtual void v00();
    virtual void v04();
    virtual void v08(void*);
    virtual void v0c(int);
    virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c();
    virtual void d30(); virtual void d34(); virtual void d38(); virtual void d3c();
    virtual void d40(); virtual void d44();
    virtual void v48(int, void*, int);
};

struct RetVt {                        // object produced by the panel-id lookup
    virtual void q00();
    virtual void q04();
    virtual void q08(int);
    virtual void q0c();
    virtual void q10();
    virtual void q14();
    virtual void q18(void*);
};

struct PathProp {                     // object stored at panel manager +0x15c
    virtual void p00();
    virtual void p04();
    virtual void p08(int, int, void**);
};

struct WinVt {                        // window returned by FindWindowByID
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23)
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    virtual void v7c(int, unsigned char);
};

struct PropList {                     // _sAppPreferences_SP object
    virtual void y00(); virtual void y04(); virtual void y08(); virtual void y0c();
    virtual void y10();
    virtual void y14(int, void*);
    virtual void y18(); virtual void y1c(); virtual void y20();
    virtual char y24(int, void**);
};

// ------------------------------------------------------------- data types ---
struct Vec3 { float x, y, z; };
struct Matrix33 { float m[9]; };

struct Rec {                          // 0xbc-byte element of the array at +0x08
    char    pad080[0x80];
    float   fX;                       // +0x80
    float   fY;                       // +0x84
    float   fZ;                       // +0x88
    char    pad08c[0xac - 0x8c];
    uint8_t bAC;                      // +0xac
    uint8_t bAD;                      // +0xad
    char    pad0ae[0xbc - 0xae];
};

struct Stopwatch {
    uint64_t mStart;                  // +0x00
    uint64_t mElapsed;                // +0x08
    int32_t  mUnits;                  // +0x10
    uint32_t mPad;                    // +0x14
    void SetUnits(int);
};

struct GObj {                         // object behind FUN_00b3d360()
    char FUN_00b7d4f0(void* p);
    void FUN_00b7d440(Vec3 v, void*, void*, void*, void*, void*, void*);
};

struct Banner2 {                      // banner-list holder (panel manager entry)
    char      pad000[0x7c];
    void*     mp7c;                   // +0x7c
    char      pad080[0x84 - 0x80];
    void*     mp84;                   // +0x84
    char      pad088[0xac - 0x88];
    uint8_t   bAC;                    // +0xac
    Banner2*  FUN_00de4610();         // 0x00de4610
    Banner2*  FUN_00bbaa60(int idx);  // 0x00bbaa60
    Vec3*     FUN_00b8d8e0();         // 0x00b8d8e0
};

struct GfxPoint {                     // 0x14-byte display point handed to a window
    uint16_t m00;                     // +0x00
    uint16_t m02;                     // +0x02
    float    m04;                     // +0x04
    float    m08;                     // +0x08
    float    m0c;                     // +0x0c
    float    m10;                     // +0x10
};

struct Transform34 { char m[0x38]; };

struct Variant {
    char    mData[0x10];
    uint16_t mFlagsW;                 // +0x10
    uint16_t mAuxW;                   // +0x12
    void SetChar(char* p);
    void Destruct(bool b);
};

struct Prop {                         // cProperty returned by PropList::y24
    char  pad000[0x12];
    uint16_t m12;                     // +0x12
    char* GetBool();
};

struct PanelMgr;                      // layout sub-object + property list
struct LayoutObj {
    char pad000[0x18];
    WinVt* FindWindowByID(uint32_t id, int b);   // 0x008105b0
};
struct PanelMgr {
    char       pad000[0x144];
    LayoutObj  mLayout;               // +0x144
    PathProp*  mp15c;                 // +0x15c
    void FUN_00de9ec0();              // 0x00de9ec0
    void FUN_00de5330(int v);         // 0x00de5330
};

// ------------------------------------------------------------ the objects ---
struct SW20Obj {                      // embedded object at WinA+0x20
    char  pad000[0x10];
    void* mp10;                       // +0x10  (WinA+0x30)
    void FUN_00e21260(void*, void*, void*);
    void FUN_00e20d60(void*);
    void FUN_00e20d30(float);
};

struct WinA {
    char     pad020[0x20];
    SW20Obj  m20;                     // +0x20
    RefVt*   mp34;                    // +0x34
    char     pad038[0x50 - 0x38];
    uint8_t  m50;                     // +0x50
    char     pad051[0x8c - 0x51];
    void*    mp8c;                    // +0x8c
    void FUN_00df6700(void* param);
    void FUN_00df6740();
    bool FUN_00df6850(RefVt* param);
    bool FUN_00df68c0(uint32_t msg, void* param3);
};

struct WinB {
    char      pad008[8];
    Rec*      mpBegin;                // +0x08
    Rec*      mpEnd;                  // +0x0c
    char      pad010[0x20 - 0x10];
    Stopwatch sw20;                   // +0x20
    Stopwatch sw38;                   // +0x38
    void FUN_00df6980();
    void FUN_00df6c40();
};

// ------------------------------------------------------------- externals ----
extern "C" void*   __fastcall FUN_00fc7e50(void* self);   // EA::XHTML::DOM::Node::Type
extern "C" void    __fastcall FUN_0080ea50(void* self);   // cSPUILayeredObject::RemoveAllModels
extern "C" GObj*   FUN_00b3d360();                        // 0x00b3d360 global getter
extern "C" void    __fastcall FUN_00409930(void* self);
extern "C" void    __fastcall FUN_005aa530(void* self);
extern "C" void*   __cdecl    FUN_00dd9190_0();
extern "C" void*   __stdcall  FUN_00dd9190_1(void* a);
extern "C" void*   __stdcall  FUN_00dd9190_2(void* a, void* b);
extern "C" void    __fastcall FUN_00ddab00(void* self);
extern "C" void    __fastcall FUN_00ddb760(void* self);
extern "C" void    __fastcall FUN_00dda090(void* self);
extern "C" char*   __fastcall FUN_0041e920(void* self);   // cProperty::GetBool
extern "C" void*   __cdecl    FUN_006b1f90(unsigned id);  // SP_GetSaveArea
extern "C" void    __cdecl    FUN_006b1d50(void* p, void* r, int c);  // SP_SaveResource
extern "C" void    __fastcall FUN_0041cb40(void* self, void* src);    // Matrix3::Assign
extern "C" void    __fastcall FUN_00422e20(void* self, char* p);      // Variant_SetChar

// ============================================================== functions ===
// @ 0x00df6700
void WinA::FUN_00df6700(void* param)
{
    if (mp8c != 0) {
        void* n = FUN_00fc7e50(mp8c);
        if (n != 0) {
            ((NodeVt*)FUN_00fc7e50(mp8c))->v7c(1, param);
        }
    }
}

// @ 0x00df6740
void WinA::FUN_00df6740()
{
    if (mp8c == 0) return;
    if (((Banner2*)m20.mp10)->FUN_00de4610()->bAC == 0) return;

    Vec3 v3 = *((Banner2*)m20.mp10)->FUN_00de4610()->FUN_00bbaa60(0)->FUN_00b8d8e0();
    int local18[6] = { 0, 0, 0, 0, 0, 0 };
    FUN_0080ea50(mp8c);
    if (FUN_00b3d360()->FUN_00b7d4f0(&v3) != 0) {
        FUN_00b3d360()->FUN_00b7d440(v3, 0, 0, 0, 0, &local18[0], &local18[3]);
        if (local18[0] != 0) {
            m20.FUN_00e21260(&local18[0], &local18[3], mp8c);
            m20.FUN_00e20d60(g_c16a0dd0);
            m20.FUN_00e20d30(g_f16a0da0);
        }
    }
}

// @ 0x00df6850
bool WinA::FUN_00df6850(RefVt* param)
{
    if (mp34 != 0) mp34->v0c(1);
    RefVt* old = mp34;
    if (param != old) {
        if (param != 0) param->v00();
        mp34 = param;
        if (old != 0) old->v04();
    }
    if (mp34 != 0) {
        mp34->v08(0);
        param = (RefVt*)m20.mp10;
        mp34->v48(9, &param, 1);
    }
    return true;
}

// @ 0x00df68c0
bool WinA::FUN_00df68c0(uint32_t msg, void* param3)
{
    if (msg == 0x5120263) {
        m50 = 1;
        return true;
    }
    if (msg == 0x7be7df5) {
        if (((MsgArg*)param3)->m08 == 5) {
            Transform34 tf;
            FUN_00409930(&tf);
            FUN_005aa530(&tf);
            FUN_00ddab00(FUN_00dd9190_1(&tf));
            FUN_00ddb760(FUN_00dd9190_0());
        }
        if (((MsgArg*)param3)->m08 == 4) {
            ((PanelMgr*)g_p16a1344)->FUN_00de9ec0();
            ((PanelMgr*)g_p16a1344)->FUN_00de5330(0);
        }
        return true;
    }
    if (msg == 0x7c3cd3d) {
        if (((MsgArg*)param3)->m08 == 5) {
            FUN_00dda090(FUN_00dd9190_2((void*)2, (void*)1));
        }
        return true;
    }
    return false;
}

// @ 0x00df6980
void WinB::FUN_00df6980()
{
    if (sw20.mStart != 0) return;

    int count = (int)(mpEnd - mpBegin);
    if (count != 0) {
        int i = 0;
        do {
            Rec* r = &mpBegin[i];
            if (r->bAD != 0) {
                RetVt* obj = 0;
                if (r->bAC == 0)
                    ((PanelMgr*)g_p16a1344)->mp15c->p08(0x37cf81e6, 0, (void**)&obj);
                else
                    ((PanelMgr*)g_p16a1344)->mp15c->p08(0xa77c6b11, 0, (void**)&obj);
                if (obj != 0) {
                    GfxPoint p;
                    p.m04 = (g_mat00 * r->fX + g_mat01 * r->fY) + g_mat02 * r->fZ + g_posX;
                    p.m08 = (g_mat10 * r->fX + g_mat11 * r->fY) + g_mat12 * r->fZ + g_posY;
                    p.m0c = (g_mat20 * r->fX + g_mat21 * r->fY) + g_mat22 * r->fZ + g_posZ;
                    p.m00 = 4;
                    p.m02 = 1;
                    p.m10 = g_f1485720;
                    obj->q18(&p);
                    obj->q08(0);
                    if (obj != 0) obj->q04();
                }
            }
            ++i;
        } while (i < count);
    }

    if (sw20.mUnits == 1) {
        uint64_t t = __rdtsc();
        sw20.mElapsed = 0;
        sw20.mStart = t;
        return;
    }
    uint64_t t;
    g_pQueryPerformanceCounter(&t);
    sw20.mElapsed = 0;
    sw20.mStart = t;
}

// @ 0x00df6c40
void WinB::FUN_00df6c40()
{
    PropList* pl = (PropList*)g_p15fd91c;
    unsigned char b = 0;
    union { void* p; uint64_t u; } slot;
    if (pl != 0 && pl->y24(0x80d7de1, &slot.p) != 0) {
        if (((Prop*)slot.p)->m12 == 1) b = *((Prop*)slot.p)->GetBool();
    }

    WinVt* w = ((PanelMgr*)g_p16a1344)->mLayout.FindWindowByID(0x806a310, 1);
    if (w != 0) w->v7c(1, b == 0);

    if (pl != 0 && pl->y24(0x80d97fe, &slot.p) != 0) {
        if (((Prop*)slot.p)->m12 == 1) {
            if (*((Prop*)slot.p)->GetBool() != 0) return;
        }
    }

    WinVt* w2 = ((PanelMgr*)g_p16a1344)->mLayout.FindWindowByID(0x806aa00, 1);
    if (w2 != 0) w2->v7c(1, 0);

    char flag = 1;
    Variant v;
    v.mFlagsW = 0;
    v.mAuxW = 0;
    v.SetChar(&flag);
    pl->y14(0x80d97fe, &v);
    if ((v.mFlagsW & 4) != 0) v.Destruct(false);

    FUN_006b1d50(pl, FUN_006b1f90(0x11ac192), 0);

    Stopwatch* sw = &sw38;
    sw->SetUnits(4);
    if (sw->mStart != 0) return;
    if (sw->mUnits == 1) {
        uint64_t t = __rdtsc();
        sw->mStart = t;
        return;
    }
    g_pQueryPerformanceCounter(&slot.u);
    sw->mStart = slot.u;
}