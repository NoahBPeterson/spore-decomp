// Slice s00fe76d0 (batch gold5) -- SP UI asset-browser / terrain-brush helpers.
// Module "Spore" (VS2008 SP1, cl 15.00.30729.01).  Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast
//
// UI window objects are UTFWin::IWindow instances; only the slots the slice
// touches are modelled.  FUN_010666a0() returns the SpaceGame editor object.
// Two window flavours appear: layout windows (cSPUILayout::FindWindowByID via
// *(o+0x258)) and global-UI windows (cSPUIGlobalUI::FindWindowByID via *(o+0x224)).

#include "types.h"
#include <math.h>

typedef unsigned int uint;

extern "C" {
float        DAT_01485720;   // 0x1485720   1.0f
float        DAT_015b44f8;   // 0x15b44f8   1.5707964f (pi/2)
float        DAT_013eb8a0;   // 0x13eb8a0   0.25f
float        DAT_01471064;   // 0x1471064   0.5f
float        DAT_013f9428;   // 0x13f9428   0.001f
float        DAT_013ef56c;   // 0x13ef56c  -0.001f
float        DAT_013f89bc;   // 0x13f89bc   1e-05f
float        DAT_01477fbc;   // 0x1477fbc   200.0f
unsigned int DAT_015b444c;   // 0x15b444c
unsigned int DAT_015da7c4;   // 0x15da7c4
unsigned int DAT_015da7c8;   // 0x15da7c8
unsigned int DAT_015da7cc;   // 0x15da7cc
unsigned int DAT_015da7d0;   // 0x15da7d0
unsigned int DAT_01488848;   // 0x1488848
char         DAT_013ebc58[]; // 0x13ebc58  "App"
unsigned int DAT_016c7aa4;   // 0x16c7aa4  Simulator singleton
}

// ------------------------------------------------------------------ callees
void* FUN_010666a0(void);                                              // 0x10666a0
void* FUN_00b3d490(void);                                              // 0xb3d490
void* FUN_00b3d380();                                                 // 0xb3d380 GameTimeManager (0-arg getter)
void* FUN_010212a0(void);                                              // 0x10212a0
void* FUN_01021300(void);                                              // 0x1021300
void* FUN_00aed4d0(void);                                              // 0xaed4d0
void* FUN_00b3d320();                                                 // 0xb3d320 (0-arg getter)
void* FUN_00b3d300(void);                                              // 0xb3d300 SP_NounManager
void* SP_MessageServer(void);                                          // 0x67dcc0
void* SP_App(void);                                                    // 0x67dd10
void* FUN_00f473a0(unsigned sz, const char* f, int l, int a, int b, int c); // 0xf473a0 EAAllocate
void  FUN_00fe7590(int a, int b);                                      // 0xfe7590
void  FUN_00fe72b0();                                                  // 0xfe72b0
void  FUN_00fe73c0();                                                  // 0xfe73c0
void  FUN_00fe74a0();                                                  // 0xfe74a0
void  FUN_00fe7d70();                                                  // 0xfe7d70
void  FUN_00fe7b80();                                                  // 0xfe7b80
void* FUN_00eec580(int a);                                             // 0xeec580
int   FUN_005bf0e0(void* owner, void** out);                           // 0x5bf0e0 GetEditorPropertyList
int   FUN_00410370(void* list, unsigned key, unsigned* out);           // 0x410370 TryGetUIntProperty
void  FUN_00eb96a0(void* out, const void* src, const wchar_t* in);     // 0xeb96a0
void  FUN_00881ae0(int value, int sign, wchar_t* buf, unsigned n);     // 0x881ae0 Locale::SetNumberString
void  FUN_00807c70(void* a, void* b, int c, int d);                    // 0x807c70
void  FUN_00806de0(void* w, void* text, int a, int b);                  // 0x806de0 SetTooltipText
void* EA_COM_interface_cast(void* p);                                  // 0xfe7290 interface_cast

// thiscall callees: modelled as member functions of an opaque object so that
// `self` lands in ECX and the callee cleans its stack arguments (ret N).
struct Fns {
    void  f1067f60(int x);                       // 0x1067f60
    void  ae8ea0();                              // 0xae8ea0 CommHost::ResetSlots
    void  b32220(unsigned tag);                  // 0xb32220 GameTimeManager::IncPauseGate
    void  b32250(unsigned tag);                  // 0xb32250 GameTimeManager::DecPauseGate
    void  f16fd0();                              // 0xf16fd0
    void* c30f90();                              // 0xc30f90 GetPlayerEmpire
    void* f67d90();                              // 0xf67d90 cTerrainEditor::GetCurrentTerrainSphere
    void  f12680(unsigned a);                    // 0xf12680
    void  f16260();                              // 0xf16260
    void  f14980();                              // 0xf14980
    void  f120c0(void* w);                       // 0xf120c0
    void  f150d0(void* v);                       // 0xf150d0 Owner::Load
    void  f17b00(void* v);                       // 0xf17b00
    void* g5a9080();                             // 0x5a9080 ctor (returns this)
    void  g6b5770(unsigned a, unsigned b, const wchar_t* c); // 0x6b5770 cString ctor
    void  g6b5240();                             // 0x6b5240 cString dtor
    const wchar_t* g6b55c0();                    // 0x6b55c0 cString::GetText
    void  g6ec1c0(void* src);                    // 0x6ec1c0
    void  g57cb80();                             // 0x57cb80 eastl::fixed_string dtor
    void  gb1dee0(void* obj);                    // 0xb1dee0
    void* b8d9b0();                              // 0xb8d9b0
    char  ec5a60(void* ctx, int a, int b);       // 0xec5a60
    void  ae7e10(unsigned a, unsigned b, int c, int d);  // 0xae7e10
    void  g93a2e0();                             // 0x93a2e0 SetBoolProperty
    long long g93a3a0();                         // 0x93a3a0 GetElapsedTimeTicks
};

// UI layout / global-ui: FindWindowByID wrappers.
struct Layout  { void* FindWindowByID(unsigned int id, int flag); };   // 0x8105b0
struct GlobUI  { void* FindWindowByID(unsigned int id); };             // 0xe012b0

// UTFWin::IWindow vtable slices (only the slots touched in this slice).
// Layout windows: slot 0x28 is a no-arg boolean getter, 0x38 a vector getter.
struct IWinL {
    virtual void  a00(); virtual void a04(); virtual void a08();
    virtual void* a0c(unsigned int id);
    virtual void  a10(); virtual void a14(); virtual void a18();
    virtual void  a1c(); virtual void a20(); virtual void a24();
    virtual char  a28();
    virtual void  a2c(); virtual void a30(); virtual void a34();
    virtual float* a38();
    virtual void  a3c(); virtual void a40(); virtual void a44();
    virtual void  a48(); virtual void a4c(); virtual void a50();
    virtual void  a54(); virtual void a58(); virtual void a5c();
    virtual void  a60(); virtual void a64(); virtual void a68();
    virtual void  a6c(void* p);
    virtual void  a70(); virtual void a74(); virtual void a78();
    virtual void  a7c(int a, int b);
    virtual char  a80(const void* s);
};

// Global-UI windows: slot 0x0c GetComponent(id), 0x28 setter(int,int).
struct IWinG {
    virtual void  a00(); virtual void a04(); virtual void a08();
    virtual void* a0c(unsigned int id);
    virtual void  a10(); virtual void a14(); virtual void a18();
    virtual void  a1c(); virtual void a20(); virtual void a24();
    virtual void  a28(int a, int b);
};

// Terrain brush / crater math object shared by 8260/8380/8450.
struct Brush {
    unsigned char b00;
    char  pad01[3];
    float f04, f08, f0c, f10, f14, f18, f1c, f20;
    float f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;

    void f8450();
};

// ------------------------------------------------------------------ support
struct NewObj {                      // freshly constructed editor-launch object
    virtual void  n00(); virtual void n04(); virtual void* n08();
};

struct SimpleVec {
    unsigned* begin; unsigned* end; unsigned* cap;
    void  DoInsertValue(void* pos, const void* val);    // 0x4558a0 eastl::vector::DoInsertValue
};

static void vecPush(SimpleVec* v, unsigned val)
{
    unsigned* p = v->end;
    if (p < v->cap) {
        v->end = p + 1;
        if (p != 0)
            *p = val;
    } else {
        v->DoInsertValue(p, &val);
    }
}

// Message payload: msg[0] -> object, msg[2] -> message id.
struct MsgObj { virtual void m00(); virtual void m04(); virtual void m08();
                virtual void m0c(); virtual void m10(); virtual void m14();
                virtual void m18(); virtual unsigned m1c(); };

struct MsgSrv { virtual void m00(); virtual void m04(); virtual void m08();
                virtual void m0c(); virtual void m10(); virtual void m14();
                virtual void m18(); virtual void m1c();
                virtual void v20(void* a, unsigned b);
                virtual void m24(); virtual void m28();
                virtual void v2c(void* a, unsigned b, int c); };

struct AppV { virtual void a00(); virtual void a04(); virtual void a08();
              virtual void a0c(); virtual void a10(); virtual void a14();
              virtual void a18(); virtual void a1c(); virtual void a20();
              virtual void a24(); virtual void a28(); virtual void a2c();
              virtual void a30(); virtual void a34(); virtual void a38();
              virtual void a3c(); virtual void a40(); virtual void a44();
              virtual void a48(); virtual void a4c();
              virtual void* a50(); };

struct AppCam { virtual void c00(); virtual void c04(); virtual void c08();
                virtual void c0c(); virtual void c10(); virtual void c14();
                virtual void c18(); virtual void c1c(); virtual void c20();
                virtual void c24(); virtual void c28(); virtual void c2c();
                virtual void c30(); virtual void c34(); virtual void* c38();
                virtual void c3c(); virtual void c40(); virtual void c44();
                virtual void c48(); virtual void c4c(); virtual void c50();
                virtual void c54(); virtual void c58(); virtual void c5c();
                virtual void c60();
                virtual void c64(int a); };

struct AedV { virtual void a00(); virtual void a04(); virtual void a08();
              virtual void a0c(); virtual void a10(); virtual void a14();
              virtual void a18(); virtual void a1c(); virtual void a20();
              virtual void a24(); virtual void a28(unsigned, unsigned, void*, void*); };

// ================================================================== 0x00fe76d0
// void FUN_00fe76d0(int p)
// @ 0x00fe76d0
struct CBr {
    char   pad00[4];
    void*  f04;
    unsigned f08;
    char   pad0c[4];
    char   f10[8];
    char   pad18[0xc];
    float  f24;
    unsigned char f28;
    char   pad29[3];
    void*  f2c;
    char   f30[0x8c];
    unsigned char fbc;
    char   padbd[0x43];

    void  f76d0(int p);
    void  f7d70();
    void* f7b80();
    void  f7e10();
    char  f7e60(unsigned p2, void** msg);
};

void CBr::f76d0(int p)
{
    void* o = FUN_010666a0();
    Layout* lay = (Layout*)*(void**)((char*)o + 0x258);
    IWinL* w0 = (IWinL*)lay->FindWindowByID(0x7550880, 1);
    if (w0 == 0)
        return;
    IWinL* w1 = (IWinL*)lay->FindWindowByID(0x7550881, 1);
    if (w1 == 0)
        return;

    FUN_00fe7590(4, 1);

    if (p == 1) {
        w0->a7c(1, 1);
        w1->a7c(1, 0);
        IWinL* w2 = (IWinL*)lay->FindWindowByID(0x7551618, 1);
        if (w2 != 0)
            w2->a7c(1, 0);
        ((Fns*)f2c)->f16fd0();
        return;
    }

    w0->a7c(1, 0);
    w1->a7c(1, 1);
    IWinL* w2 = (IWinL*)lay->FindWindowByID(0x7551618, 1);
    if (w2 != 0)
        w2->a7c(1, 1);

    unsigned* empire = (unsigned*)((Fns*)FUN_01021300())->c30f90();

    IWinL* wA = (IWinL*)lay->FindWindowByID(0x7cf6498, 1);
    if (wA != 0) {
        unsigned char* ed = (unsigned char*)*(void**)((char*)DAT_016c7aa4 + 0x7c);
        *(unsigned*)(ed + 0x14) = empire[0];
        *(unsigned*)(ed + 0x18) = empire[1];
        *(unsigned*)(ed + 0x1c) = empire[2];
        *(unsigned*)(ed + 0x20) = 0xffffffffu;
        char s1[0x1c];
        char s2[0x1c];
        ((Fns*)s1)->g6b5770(0x623d2fc0, 0x7ceb16a, 0);
        ((Fns*)s2)->g6b5770(0x623d2fc0, 0x7ceb16b, 0);
        wA->a80(((Fns*)s1)->g6b55c0());
        ((Fns*)s2)->g6b5240();
        ((Fns*)s1)->g6b5240();
    }

    IWinL* wTool = (IWinL*)lay->FindWindowByID(0x755e358, 1);

    void* prop = 0;
    FUN_005bf0e0(empire, &prop);
    unsigned out1 = 0;
    FUN_00410370(prop, 0x5888ef41, &out1);
    unsigned out2 = 0;
    FUN_00410370(prop, 0xcf837237, &out2);
    int count = (int)FUN_00eec580((int)(out1 + 1));

    wchar_t buf[0x20];
    IWinL* wB = (IWinL*)lay->FindWindowByID(0x7cd1550, 1);
    if (wB != 0) {
        FUN_00881ae0((int)out1, (int)out1 >> 31, buf, 0x20);
        wB->a80(buf);
    }
    FUN_00881ae0((int)out2, (int)out2 >> 31, buf, 0x20);
    char cstr[0x1c];
    FUN_00eb96a0(cstr, &DAT_01488848, buf);
    FUN_00881ae0(count, count >> 31, buf, 0x20);
    ((Fns*)cstr)->g6ec1c0(buf);
    FUN_00806de0(wTool, *(void**)cstr, -1, 1);
    FUN_00807c70(wTool, lay, 0x7d10de0 + (int)out1, 0xffffffff);

    IWinL* wC = (IWinL*)lay->FindWindowByID(0x7cf8048, 1);
    if (wC != 0) {
        float hi = (float)count - DAT_01485720;
        float lo = (float)(int)FUN_00eec580((int)out1);
        float base = (lo < hi) ? lo : hi;
        float frac = ((float)(int)out2 - base) / ((float)count - base);
        float t = (frac > DAT_01485720) ? DAT_01485720 : frac;
        float* pv = wC->a38();
        float vals[4];
        vals[0] = pv[0];
        vals[1] = pv[1];
        vals[2] = pv[2];
        vals[3] = pv[3];
        void* o2 = FUN_010666a0();
        vals[3] = (*(float*)((char*)o2 + 0x690) - vals[1]) * (DAT_01485720 - t) + vals[1];
        wC->a6c(vals);
    }

    IWinL* wD = (IWinL*)lay->FindWindowByID(0x7cc9018, 1);
    if (wD != 0) {
        unsigned* emp = (unsigned*)((Fns*)FUN_01021300())->c30f90();
        unsigned v[3];
        v[0] = emp[0];
        v[1] = emp[1];
        v[2] = emp[2];
        ((Fns*)f2c)->f17b00(v);
    }
    ((Fns*)this)->f16fd0();
    FUN_00fe72b0();
    FUN_00fe73c0();
    FUN_00fe74a0();

    IWinL* wE = (IWinL*)lay->FindWindowByID(0x7cded28, 1);
    if (wE != 0) {
        IWinL* wF = (IWinL*)lay->FindWindowByID(0x7cded29, 1);
        if (wF != 0) {
            if (p == 0) {
                wF->a7c(1, 1);
                wE->a7c(1, 0);
            } else {
                wF->a7c(1, 0);
                wE->a7c(1, 1);
            }
        }
    }
}

// ================================================================== 0x00fe7b80
// void* FUN_00fe7b80(void)
// @ 0x00fe7b80
void* CBr::f7b80()
{
    void* mem = FUN_00f473a0(0x9c, DAT_013ebc58, 0, 0, 0, 0);
    void* obj = 0;
    if (mem != 0) {
        obj = ((Fns*)mem)->g5a9080();
        if (obj != 0)
            ((NewObj*)obj)->n04();
    }

    unsigned* e = (unsigned*)((Fns*)FUN_01021300())->c30f90();
    unsigned* od = (unsigned*)obj;
    od[4] = e[0];
    od[5] = e[1];
    od[6] = e[2];
    od[3] = 0xa56567f7u;

    void* r = *(void**)((char*)obj + 0x94);
    if (r != 0) {
        *(void**)((char*)obj + 0x94) = 0;
        void** vt = *(void***)r;
        ((void(*)(void))vt[1])();
    }
    od[9]  = DAT_015da7c4;
    od[10] = DAT_015da7c8;
    od[0xb] = DAT_015da7cc;
    od[0xc] = DAT_015da7d0;
    *(unsigned char*)((char*)obj + 0x35) = 0;
    *(unsigned char*)((char*)obj + 0x34) = 0;
    *(unsigned char*)((char*)obj + 0x36) = 0;
    *(unsigned char*)((char*)obj + 0x38) = 0;
    *(unsigned char*)((char*)obj + 0x37) = 0;
    *(unsigned char*)((char*)obj + 0x39) = 0;
    *(unsigned char*)((char*)obj + 0x3c) = 1;
    *(unsigned char*)((char*)obj + 0x6d) = 1;

    void* ts = ((Fns*)FUN_00b3d300())->f67d90();
    if (ts != 0) {
        SimpleVec* v = (SimpleVec*)((char*)obj + 0x70);
        vecPush(v, *(unsigned*)((char*)ts + 0x10fc));
        vecPush(v, *(unsigned*)((char*)ts + 0x1100));
        vecPush(v, *(unsigned*)((char*)ts + 0x1104));
        vecPush(v, *(unsigned*)((char*)ts + 0x1108));
        vecPush(v, *(unsigned*)((char*)ts + 0x110c));
    }
    *(unsigned*)((char*)obj + 0x90) = f08;
    *(unsigned char*)((char*)obj + 0x3d) = 1;
    *(unsigned char*)((char*)obj + 0x64) = 1;

    ((Fns*)FUN_00b3d320())->gb1dee0(obj);
    return ((NewObj*)obj)->n08();
}

// ================================================================== 0x00fe7d70
// void FUN_00fe7d70(void)
// @ 0x00fe7d70
void CBr::f7d70()
{
    void* o = FUN_010666a0();
    Layout* lay = (Layout*)*(void**)((char*)o + 0x258);
    IWinL* w = (IWinL*)lay->FindWindowByID(0x755f180, 1);
    if (w != 0)
        w->a7c(1, 0);

    ((Fns*)FUN_010666a0())->f1067f60(0);
    ((Fns*)FUN_00b3d490())->ae8ea0();
    f76d0(1);

    IWinG* w2 = (IWinG*)((GlobUI*)*(void**)((char*)FUN_010666a0() + 0x224))->FindWindowByID(0x7bb7790);
    if (w2 != 0) {
        IWinG* x = (IWinG*)w2->a0c(0x8ed27e7a);
        if (x != 0)
            x->a28(4, 0);
    }
    ((Fns*)FUN_00b3d380())->b32250(0x7e9e4b7);
}

// ================================================================== 0x00fe7e10
// void FUN_00fe7e10(void)
// @ 0x00fe7e10
void CBr::f7e10()
{
    f7d70();

    IWinG* w = (IWinG*)((GlobUI*)*(void**)((char*)FUN_010666a0() + 0x224))->FindWindowByID(0x7bb7790);
    if (w != 0) {
        IWinG* x = (IWinG*)w->a0c(0x8ed27e7a);
        if (x != 0)
            x->a28(4, 0);
    }
    f28 = 0;
}

// ================================================================== 0x00fe7e60
// char FUN_00fe7e60(unsigned p2, void** msg)
// @ 0x00fe7e60
char CBr::f7e60(unsigned p2, void** msg)
{
    (void)p2;
    void* o = FUN_010666a0();
    Layout* lay = (Layout*)*(void**)((char*)o + 0x258);
    unsigned m2 = (unsigned)msg[2];

    if (m2 == 0x287259f6u) {
        unsigned id = ((MsgObj*)*msg)->m1c();
        f08 = id;

        switch (id) {
        case 0x755e358: {
            IWinL* w1 = (IWinL*)lay->FindWindowByID(0x7cccbd0, 1);
            if (w1 == 0)
                break;
            IWinL* w2 = (IWinL*)lay->FindWindowByID(0x7cc9000, 1);
            if (w2 == 0)
                break;
            char b1 = (char)(w1->a28() & 1);
            char b2 = (char)(w2->a28() & 1);
            if ((b1 ^ b2) == 0)
                break;
            if (b1 != 0) {
                w1->a7c(1, 0);
                w2->a7c(1, 1);
                break;
            }
            w1->a7c(1, 1);
            w2->a7c(1, 0);
            void* self30 = (char*)this + 0x30;
            ((Fns*)self30)->f16260();
            ((Fns*)self30)->f14980();
            IWinL* w3 = (IWinL*)lay->FindWindowByID(0x7da1928, 1);
            if (w3 != 0)
                ((Fns*)self30)->f120c0(w3);
            unsigned* emp = (unsigned*)((Fns*)FUN_01021300())->c30f90();
            unsigned v[3];
            v[0] = emp[0];
            v[1] = emp[1];
            v[2] = emp[2];
            ((Fns*)self30)->f150d0(v);
            break;
        }
        case 0x5e4f788: {
            f7d70();
            void* planet = FUN_010212a0();
            if (planet == 0)
                break;
            void* x = ((Fns*)planet)->b8d9b0();
            if (x == 0)
                break;
            ((Fns*)FUN_00b3d380())->b32220(0x7e9e4b7);
            unsigned ctx[3];
            ctx[0] = (unsigned)x;
            ctx[1] = 0x366a930du;
            ctx[2] = DAT_015b444c;
            fbc = 1;
            ((MsgSrv*)SP_MessageServer())->v20((char*)this + 4, 0xcc0bf723);
            void* ec = *(void**)((char*)DAT_016c7aa4 + 0x1c);
            char r = ((Fns*)ec)->ec5a60(ctx, 0, 0);
            if (r != 0)
                break;
            fbc = 0;
            ((MsgSrv*)SP_MessageServer())->v2c((char*)this + 4, 0xcc0bf723, 0xffffd8f1);
            ((Fns*)FUN_00b3d380())->b32250(0x7e9e4b7);
            break;
        }
        case 0x5e4f770:
        case 0x75dd100: {
            f7d70();
            AppV* app = (AppV*)SP_App();
            void* c = app->a50();
            void* ic = EA_COM_interface_cast(((AppCam*)c)->c38());
            ((AppCam*)ic)->c64(1);
            break;
        }
        case 0x7ce1750:
        case 0x7ce3cb0:
            f7d70();
            f7b80();
            break;
        case 0x770996a:
            f76d0(1);
            break;
        case 0x7bb9fc8:
            f7d70();
            FUN_00fe7590(4, 0);
            f28 = 0;
            break;
        case 0x75dd108: {
            f76d0(2);
            void* s = FUN_01021300();
            AedV* g = (AedV*)FUN_00aed4d0();
            unsigned l1, l2;
            g->a28(0x55125425u, *(unsigned*)((char*)s + 0x58), &l1, &l2);
            ((Fns*)FUN_00b3d490())->ae7e10(l1, l2, 0, 1);
            break;
        }
        default:
            break;
        }
        return 0;
    }

    if (m2 == 0x0cu) {
        void* self2c = *(void**)((char*)this + 0x2c);
        ((Fns*)self2c)->f12680(0x14);
        if (*(unsigned*)((char*)this + 0x10) == 0 && *(unsigned*)((char*)this + 0x14) == 0)
            return 0;
        long long ticks = ((Fns*)((char*)this + 0x10))->g93a3a0();
        double elapsed = (double)ticks * (double)f24;
        if (elapsed <= (double)DAT_01477fbc)
            return 0;
        ((Fns*)((char*)this + 0x10))->g93a2e0();
        IWinL* w = (IWinL*)lay->FindWindowByID(0x7551618, 1);
        if (w != 0)
            w->a7c(1, 1);
    }
    return 0;
}

// ================================================================== 0x00fe8260
// float FUN_00fe8260(Brush* p, float p1, float p2, float p3)
// register ABI: p arrives in EAX -- modelled as a leading pointer parameter.
// @ 0x00fe8260
float f8260(const Brush* p, float p1, float p2, float p3)
{
    float sa = sinf(p1);
    float ca = cosf(p1);
    float sb = sinf(p2);
    float cb = cosf(p2);

    float t1 = sqrtf((DAT_01485720 - p->f3c) /
                     (DAT_01485720 - (p->f3c * cb) * cb)) * p->f24;
    float x1 = t1 * sb;
    float t2 = sqrtf((DAT_01485720 - p->f3c) /
                     (DAT_01485720 - (p->f3c * ca) * ca)) * p->f24;
    float x2 = t2 * sa;

    float d = (t2 * ca) * x1 - (t1 * cb) * x2;

    float a = ((p->f28 - p->f30) * (ca * sa - cb * sb) +
               (p->f28 + p->f30) * (p1 - p2)) * DAT_013eb8a0;
    float b = ((x2 - x1) * p->f34 + d) * DAT_01471064;

    return (fabsf(a) - fabsf(d) * DAT_01471064) + fabsf(b) -
           (p->f40 / p->f20) * fabsf(p3);
}

// ================================================================== 0x00fe8380
// int FUN_00fe8380(float* value, Brush* p, float p1, float p2)
// register ABI: value in ESI, Brush* in EDX, two float stack args.
// @ 0x00fe8380
int f8380(float* value, const Brush* p, float p1, float p2)
{
    for (int i = 0; i < 10; i++) {
        float delta = (p2 < 0.0f) ? DAT_013ef56c : DAT_013f9428;
        float v = *value;
        float f1 = f8260(p, v, p1, p2);
        float f2 = f8260(p, v + delta, p1, p2);
        float step = f1 / ((f2 - f1) / delta);
        *value = v - step;
        if (fabsf(step) < DAT_013f89bc)
            return 1;
    }
    return 0;
}

// ================================================================== 0x00fe8450
// void FUN_00fe8450(void)
// @ 0x00fe8450
void Brush::f8450()
{
    if (b00 != 0)
        return;

    float v10 = f10;
    f3c = v10 * v10;

    float mag = sqrtf(f14 * f14 + f18 * f18 + f1c * f1c);
    float r   = mag / (DAT_01485720 - v10);
    f24 = r;

    float r2 = r * r;
    float rv = r * v10;
    f34 = rv;
    f38 = rv * rv;
    f28 = r2;

    float side = sqrtf(r2 - rv * rv);
    f2c = side;
    f30 = side * side;
    f40 = (side * side + r2) * DAT_015b44f8;

    float inv = DAT_01485720 / mag;
    float nx = f14 * inv;
    float ny = f18 * inv;
    float nz = f1c * inv;
    f44 = nx;
    f48 = ny;
    f4c = nz;

    f50 = f4c * f08 - f48 * f0c;
    f54 = f44 * f0c - f04 * f4c;
    f58 = f04 * f48 - f44 * f08;

    float q = f34;
    f5c = q * (f14 * inv);
    f60 = q * (f18 * inv);
    f64 = q * (f1c * inv);
}
