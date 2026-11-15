// src/game/SPGonzago/SPGameCinematics.cpp -- migrated from slice(s) s00eb1e80 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameCinematics.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __fastcall FUN_00fb7b30(void* self, int dummy);                    // 0x00fb7b30 QuadSetSplit
extern "C" int   __fastcall FUN_00fb7bf0(void* self, int dummy);                    // 0x00fb7bf0 QuadSetHeight
extern "C" int   __fastcall FUN_00fbcc20(void* self, int dummy, float f);           // 0x00fbcc20 SetTemperature (declared int so eax survives the call)
extern "C" int   __fastcall FUN_00fbacb0(void* self, int dummy);                    // 0x00fbacb0 (declared int so eax survives the call)
extern "C" void  __fastcall FUN_006a1910(void* self, int dummy, int key, float v);  // 0x006a1910 SetFloatProperty
extern "C" float __fastcall FUN_006a2710(void* self, int dummy, int key);           // 0x006a2710 GetFloatProperty
extern void* g_015fd918;                      // 0x015fd918 app-properties list (cDirectPropertyList*)

// ---- items of slice s00eb1e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
int  FUN_0067dd20();                          // 0x0067dd20
int  FUN_0067dd50();                          // 0x0067dd50
int  FUN_0067de00();                          // 0x0067de00
int  FUN_0067dd80();                          // 0x0067dd80 ModelManager
int  FUN_0067dd90();                          // 0x0067dd90 LightingManager
int  FUN_0067ddd0();                          // 0x0067ddd0 EffectsManagerPtr
int  FUN_0067dcc0();                          // 0x0067dcc0 MessageServer
int  FUN_00b3d4d0();                          // 0x00b3d4d0 GetTriggerMgr
int  FUN_00b3d340();                          // 0x00b3d340
int  FUN_00b26710();                          // 0x00b26710
void FUN_00ad7df0();                          // 0x00ad7df0
void FUN_00ad7dc0();                          // 0x00ad7dc0
int  FUN_00b3d350(int a, int b, int c);       // 0x00b3d350 (PlanetModel; 3-arg form kept for HandleSimulationUpdate)
void FUN_00b8c0f0();                          // 0x00b8c0f0
void FUN_00eb7010();                          // 0x00eb7010
void* FUN_00449c20(void* out, void* in);             // 0x00449c20 normalized_safe
void* ModelManager();
extern "C" void  __fastcall FUN_00fb7b30(void* self, int dummy);                    // 0x00fb7b30 QuadSetSplit
extern "C" int   __fastcall FUN_00fb7bf0(void* self, int dummy);                    // 0x00fb7bf0 QuadSetHeight
extern "C" int   __fastcall FUN_00fbcc20(void* self, int dummy, float f);           // 0x00fbcc20 SetTemperature (declared int so eax survives the call)
extern "C" int   __fastcall FUN_00fbacb0(void* self, int dummy);                    // 0x00fbacb0 (declared int so eax survives the call)
extern "C" void  __fastcall FUN_006a1910(void* self, int dummy, int key, float v);  // 0x006a1910 SetFloatProperty
extern "C" float __fastcall FUN_006a2710(void* self, int dummy, int key);           // 0x006a2710 GetFloatProperty
extern void* g_015fd918;                      // 0x015fd918 app-properties list (cDirectPropertyList*)
struct IVtbl10 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void m(int a);
};
struct IVtbl6 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void m(int a);
};
struct B0    { void FUN_00ad7df0(); };
struct B1    { int FUN_00b26710(); };
struct BStop { void FUN_00ad7dc0(); };
struct B8    { void FUN_00b8c0f0(); };
namespace SP {
class cGameCinematicsAppMode { public:
    char pad[0x100];
    bool OnKeyDown(int k, int v);                       // 0x00eb2370
    void HandleSimulationUpdate(float a, float b);      // 0x00eb23d0
    unsigned AsInterface(int id);                       // 0x00eb2440
    void DtorBody();                                    // 0x00eb2470
    bool Init(int* p);                                  // 0x00eb2520
    bool Shutdown();                                    // 0x00eb25d0
    unsigned HandleMessage(unsigned msg, unsigned a2);  // 0x00eb2600
    cGameCinematicsAppMode* CtorBody();                 // 0x00eb28e0
    bool Activate();                                    // 0x00eb2990
    void Deactivate();                                  // 0x00eb2c70
    bool ReadResource(void* a1, void* a2, int a3, int a4); // 0x00eb20d0
};
}
typedef void*  (__thiscall *FP0)(void*);
typedef void*  (__thiscall *FP1)(void*, int);
typedef void*  (__thiscall *FP2)(void*, int, int);
typedef void*  (__thiscall *FP3)(void*, int, int, int);
typedef void*  (__thiscall *FPf)(void*, float);
typedef int    (__thiscall *FI0)(void*);
typedef int    (__thiscall *FI3)(void*, int, int, void*);
typedef void   (__thiscall *FV0)(void*);
typedef void   (__thiscall *FV1)(void*, int);
typedef void   (__thiscall *FV2)(void*, int, int);
typedef void   (__thiscall *FV3)(void*, int, int, int);
#define VT(o)         (*(void***)(o))
#define PLANETMODEL() ((int(*)())FUN_00b3d350)()
// ---- items of slice s00eb1e80 end

// @ 0x00eb2370
namespace SP {
bool cGameCinematicsAppMode::OnKeyDown(int k, int v)
{
    if (k == 0x4d) {
        if (v == 2) {
            int* p = (int*)FUN_0067dd20();
            ((IVtbl10*)p)->m(0x2b7a0311);
            return true;
        }
    } else if (k == 0x1b && v == 0) {
        ((B0*)FUN_00b3d4d0())->FUN_00ad7df0();
        ((B1*)FUN_00b3d340())->FUN_00b26710();
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x00eb23d0
namespace SP {
void cGameCinematicsAppMode::HandleSimulationUpdate(float a, float b)
{
    int iVar1 = (int)(b * 1000.0f);
    int iVar2 = FUN_00b3d4d0();
    (*(void(**)(int,int))(*(int*)(iVar2 + 4) + 0x38))(iVar1, (int)(a * 1000.0f));
    int* p = (int*)FUN_00b3d350(iVar1, 0, 0);
    (*(void(**)(void))(*p + 0x38))();
}
}  // namespace SP

// @ 0x00eb2440
namespace SP {
unsigned cGameCinematicsAppMode::AsInterface(int id)
{
    if (id != (int)0xae9cb0fa && id != (int)0xee3f516e && id != 0x2f009dd0)
        return 0;
    return (this != (cGameCinematicsAppMode*)4) ? (unsigned)this : 0;
}
}  // namespace SP

// @ 0x00eb2470
namespace SP {
void cGameCinematicsAppMode::DtorBody()
{
    char* s = (char*)this;
    *(unsigned*)(s + 0x00) = 0x14885c0;
    *(unsigned*)(s + 0x04) = 0x14885a0;
    *(unsigned*)(s + 0x08) = 0x1488590;
    *(unsigned*)(s + 0x0c) = 0x1488580;
    *(unsigned*)(s + 0x10) = 0x1488570;
    void* p20 = *(void**)(s + 0x20);
    if (p20) ((FV0)VT(p20)[1])(p20);
    void* p1c = *(void**)(s + 0x1c);
    if (p1c) ((FV0)VT(p1c)[1])(p1c);
    void* p18 = *(void**)(s + 0x18);
    if (p18) ((FV0)VT(p18)[1])(p18);
    *(unsigned*)(s + 0x10) = 0x13ec458;
    *(unsigned*)(s + 0x0c) = 0x13eb394;
    *(unsigned*)(s + 0x08) = 0x13eb938;
    *(unsigned*)(s + 0x04) = 0x13eb938;
    *(unsigned*)(s + 0x00) = 0x13eb938;
}
}  // namespace SP

// @ 0x00eb2520
namespace SP {
bool cGameCinematicsAppMode::Init(int* p)
{
    int* q = (int*)((FP0)VT(p)[0x50 / 4])(p);
    if (q)
        ((FV2)VT(q)[0x20 / 4])(q, 0x40546d5, (int)FUN_00eb7010);

    int* mm = (int*)FUN_0067dd80();
    void* newM = (void*)((FP3)VT(mm)[0x14 / 4])(mm, 0x487b104, 0, 0);
    void* oldM = *(void**)((char*)this + 0x1c);
    if (newM != oldM) {
        if (newM) ((FV0)VT(newM)[0])(newM);
        *(void**)((char*)this + 0x1c) = newM;
        if (oldM) ((FV0)VT(oldM)[1])(oldM);
    }

    int* lm = (int*)FUN_0067dd90();
    void* newL = (void*)((FP3)VT(lm)[0x18 / 4])(lm, 0x487b104, 0, 0);
    void* oldL = *(void**)((char*)this + 0x20);
    if (newL != oldL) {
        if (newL) ((FV0)VT(newL)[0])(newL);
        *(void**)((char*)this + 0x20) = newL;
        if (oldL) ((FV0)VT(oldL)[1])(oldL);
    }
    return true;
}
}  // namespace SP

// @ 0x00eb25d0
namespace SP {
bool cGameCinematicsAppMode::Shutdown()
{
    int* q;
    ((IVtbl6*)ModelManager())->m(0x487b104);
    q = *(int**)((char*)this + 0x1c);
    if (q != 0) {
        *(int*)((char*)this + 0x1c) = 0;
        ((IVtbl6*)q)->v1();
    }
    return true;
}
}  // namespace SP

// @ 0x00eb2600
namespace SP {
unsigned cGameCinematicsAppMode::HandleMessage(unsigned msg, unsigned a2)
{
    (void)a2;
    if (msg == 0x49102f1 || msg == 0x462ade4) {
        float f = (msg == 0x49102f1) ? 0.5f : *(float*)0x13f9990;
        int* pm = (int*)PLANETMODEL();
        int* obj = *(int**)((char*)pm + 0x24);
        void* t = (void*)((FPf)VT(obj)[0x10 / 4])(obj, f);
        int u = FUN_00fbcc20(t, 0, f);
        return (unsigned)u & 0xffffff00u;
    }
    if (msg == 0x4065b23) {
        FUN_006a1910(g_015fd918, 0, 0x13d7382, *(float*)((char*)this + 0x38));
        int* pm = (int*)PLANETMODEL();
        int* obj = *(int**)((char*)pm + 0x24);
        int u = FUN_0067dd50();
        void* fp = *(void**)((char*)(*obj) + 0x90);
        ((FV1)fp)(obj, u);
        ((BStop*)FUN_00b3d4d0())->FUN_00ad7dc0();
        int ur = ((B1*)FUN_00b3d340())->FUN_00b26710();
        return (unsigned)ur & 0xffffff00u;
    }
    if (msg == 0x44f1189) {
        int uv = ((B1*)FUN_00b3d340())->FUN_00b26710();
        return (unsigned)uv & 0xffffff00u;
    }
    if (msg == 0x48a74e4) {
        float f = FUN_006a2710(g_015fd918, 0, 0x13d7382);
        *(float*)((char*)this + 0x38) = f;
        FUN_006a1910(g_015fd918, 0, 0x13d7382, *(float*)0x13ec4d0);
        int* pm = (int*)PLANETMODEL();
        int* obj = *(int**)((char*)pm + 0x24);
        void* t = (void*)((FPf)VT(obj)[0x10 / 4])(obj, *(float*)0x13ef480);
        int u = FUN_00fb7bf0(t, 0);
        return (unsigned)u & 0xffffff00u;
    }
    if (msg == 0x4ebaca5) {
        int* pm = (int*)PLANETMODEL();
        int* obj = *(int**)((char*)pm + 0x24);
        float vec[3]; vec[0] = 1.0f; vec[1] = 1.0f; vec[2] = 0.0f;
        float out[3];
        void* r = FUN_00449c20(out, vec);
        void* cr = (void*)((FP1)VT(obj)[0x10 / 4])(obj, (int)r);
        (void)cr;
        FUN_00fbacb0(r, 0);
        void* v14 = *(void**)((char*)this + 0x14);
        int u = (int)((FP1)VT(v14)[0x30 / 4])(v14, 0x4b123339);
        return (unsigned)u & 0xffffff00u;
    }
    if (msg == 0x49ce8fc) {
        void* obj = *(void**)((char*)this + 0xc);
        if (obj) {
            int b = ((FI0)VT(obj)[0x10 / 4])(obj);
            if ((unsigned char)b) {
                int u = (int)((FP1)VT(obj)[0xc / 4])(obj, 1);
                return (unsigned)u & 0xffffff00u;
            }
            return (unsigned)b & 0xffffff00u;
        }
        return msg & 0xffffff00u;
    }
    if (msg == 0x4ebac98) {
        int* pm = (int*)PLANETMODEL();
        int* obj = *(int**)((char*)pm + 0x24);
        float vec[3]; vec[0] = 0.0f; vec[1] = 0.5f; vec[2] = 1.0f;
        float out[3];
        void* r = FUN_00449c20(out, vec);
        void* cr = (void*)((FP1)VT(obj)[0x10 / 4])(obj, (int)r);
        (void)cr;
        FUN_00fbacb0(r, 0);
        void* v14 = *(void**)((char*)this + 0x14);
        int u = (int)((FP1)VT(v14)[0x30 / 4])(v14, 0x4b123338);
        return (unsigned)u & 0xffffff00u;
    }
    if (msg == 0x5272ace) {
        int* pm = (int*)PLANETMODEL();
        int* obj = *(int**)((char*)pm + 0x24);
        float vec[3]; vec[0] = 0.0f; vec[1] = *(float*)0x13ec4b0; vec[2] = 1.0f;
        float out[3];
        void* r = FUN_00449c20(out, vec);
        void* cr = (void*)((FP1)VT(obj)[0x10 / 4])(obj, (int)r);
        (void)cr;
        int u = FUN_00fbacb0(r, 0);
        return (unsigned)u & 0xffffff00u;
    }
    return msg & 0xffffff00u;
}
}  // namespace SP

// @ 0x00eb28e0
namespace SP {
cGameCinematicsAppMode* cGameCinematicsAppMode::CtorBody()
{
    float f0 = *(float*)0x1486374;
    float f1 = *(float*)0x1471064;
    int* p = (int*)this;
    p[1] = 0x14426a0;
    p[2] = 0x13f1ab0;
    p[3] = 0x13eb384;
    p[4] = 0x13ec458;
    p[5] = 0;
    p[0] = 0x14885c0;
    p[1] = 0x14885a0;
    p[2] = 0x1488590;
    p[3] = 0x1488580;
    p[4] = 0x1488570;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    *(float*)(p + 9) = f0;
    *(float*)(p + 10) = f0;
    *(float*)(p + 11) = 0.0f;
    *(float*)(p + 12) = 0.0f;
    *(float*)(p + 13) = f1;
    *(float*)(p + 14) = f1;
    *(float*)(p + 15) = 0.0f;
    *(float*)(p + 16) = 0.0f;
    *(float*)(p + 17) = 0.0f;
    return this;
}
}  // namespace SP

// @ 0x00eb2990
namespace SP {
bool cGameCinematicsAppMode::Activate()
{
    char* s = (char*)this;
    *(float*)(s + 0x34) = 0.5f;
    *(float*)(s + 0x38) = 0.5f;
    *(float*)(s + 0x3c) = 0.0f;
    *(float*)(s + 0x40) = 0.0f;
    *(float*)(s + 0x24) = 0.5f;
    *(float*)(s + 0x28) = 0.5f;
    *(float*)(s + 0x2c) = 0.0f;
    *(float*)(s + 0x30) = 0.0f;

    void** slot = (void**)(s + 0x18);
    void* old = *slot;
    if (old) {
        *slot = 0;
        ((FV0)VT(old)[1])(old);
    }
    int em = FUN_0067ddd0();
    int hr = ((FI3)VT(em)[0x2c / 4])((void*)em, (int)0xa1b0293d, 0, (void*)slot);
    if ((unsigned char)hr) {
        void* nw = *slot;
        ((FV1)VT(nw)[8 / 4])(nw, 1);
    }

    int* pm = (int*)PLANETMODEL();
    int* terr = *(int**)((char*)pm + 0x24);
    void* q = (void*)((FPf)VT(terr)[0x10 / 4])(terr, 0.5f);
    FUN_00fb7b30(q, 0);

    pm = (int*)PLANETMODEL();
    terr = *(int**)((char*)pm + 0x24);
    void* r = (void*)((FPf)VT(terr)[0x10 / 4])(terr, *(float*)(s + 0x28));
    FUN_00fbcc20(r, 0, *(float*)(s + 0x28));

    pm = (int*)PLANETMODEL();
    terr = *(int**)((char*)pm + 0x24);
    float vec[3]; vec[0] = 0.0f; vec[1] = 1.0f; vec[2] = 0.5f;
    void* w = (void*)((FP1)VT(terr)[0x10 / 4])(terr, (int)vec);
    FUN_00fbacb0(w, 0);

    pm = (int*)PLANETMODEL();
    int* ebx = *(int**)((char*)pm + 0x24);
    void* fp = *(void**)((char*)(*ebx) + 0x8c);
    int u = FUN_0067dd50();
    ((FV1)fp)(ebx, u);

    int mmgr = FUN_0067dd80();
    void* p1 = (void*)((FP1)VT(mmgr)[0x1c / 4])((void*)mmgr, 0x3fbae24);
    ((FV1)VT(p1)[0xbc / 4])(p1, *(float*)0x1488874);

    void* lw = *(void**)(s + 0x20);
    ((FV1)VT(lw)[0x30 / 4])(lw, 0x75ab8f0e);

    int d = FUN_0067de00();
    ((FV1)VT(d)[0x88 / 4])((void*)d, *(int*)(s + 0x20));

    void* mw = *(void**)(s + 0x1c);
    ((FV3)VT(mw)[0x140 / 4])(mw, *(int*)(s + 0x20), 0, 1);

    void* mw2 = *(void**)(s + 0x1c);
    int p50 = FUN_0067dd50();
    void* fp2 = *(void**)((char*)(*(int*)p50) + 0x4c);
    int r2 = (int)((FP2)VT(mw2)[0x13c / 4])(mw2, 0xd, 0);
    ((FV1)fp2)((void*)p50, r2);

    void* mw3 = *(void**)(s + 0x1c);
    ((FV1)VT(mw3)[0x134 / 4])(mw3, 1);

    int em2 = FUN_0067ddd0();
    int ef = (int)((FP0)VT(em2)[0xa0 / 4])((void*)em2);
    *(unsigned*)(ef + 0xd8) = *(unsigned*)0x16c725c;
    *(unsigned*)(ef + 0xdc) = *(unsigned*)0x16c7260;
    *(unsigned*)(ef + 0xe0) = *(unsigned*)0x16c7264;
    *(float*)(ef + 0xe4) = 1.0f;
    *(unsigned*)(ef + 0xe8) = *(unsigned*)0x16c725c;
    *(unsigned*)(ef + 0xec) = *(unsigned*)0x16c7260;
    *(unsigned*)(ef + 0xf0) = *(unsigned*)0x16c7264;

    void* rc = (void*)(s + 0xc);
    static const unsigned kMsg[9] = {
        0x4065b23, 0x49ce8fc, 0x462ade4, 0x49102f1, 0x4ebac98,
        0x4ebaca5, 0x5272ace, 0x44f1189, 0x48a74e4
    };
    for (int i = 0; i < 9; ++i) {
        int ms = FUN_0067dcc0();
        ((FV2)VT(ms)[0x20 / 4])((void*)ms, (int)rc, (int)kMsg[i]);
    }
    return true;
}
}  // namespace SP

// @ 0x00eb2c70
namespace SP {
void cGameCinematicsAppMode::Deactivate()
{
    char* s = (char*)this;
    void* old = *(void**)(s + 0x18);
    if (old) {
        ((FV1)VT(old)[0xc / 4])(old, 1);
        void* y = *(void**)(s + 0x18);
        if (y) {
            *(void**)(s + 0x18) = 0;
            ((FV0)VT(old)[1])(old);
        }
    }

    int mmgr = FUN_0067dd80();
    void* p1 = (void*)((FP1)VT(mmgr)[0x1c / 4])((void*)mmgr, 0x3fbae24);
    ((FV1)VT(p1)[0xbc / 4])(p1, 1.0f);

    void* rc = (void*)(s + 0xc);
    static const unsigned kMsg[9] = {
        0x4065b23, 0x49ce8fc, 0x462ade4, 0x49102f1, 0x4ebac98,
        0x4ebaca5, 0x5272ace, 0x44f1189, 0x48a74e4
    };
    for (int i = 0; i < 9; ++i) {
        int ms = FUN_0067dcc0();
        ((FV3)VT(ms)[0x2c / 4])((void*)ms, (int)rc, (int)kMsg[i], 0xffffd8f1);
    }

    int d = FUN_0067de00();
    ((FV1)VT(d)[0x88 / 4])((void*)d, 0);

    ((B8*)PLANETMODEL())->FUN_00b8c0f0();

    int em = FUN_0067ddd0();
    int e1 = (int)((FP0)VT(em)[0x5c / 4])((void*)em);
    ((FV0)VT(e1)[0x34 / 4])((void*)e1);

    int p50 = FUN_0067dd50();
    ((FV1)VT(p50)[0x50 / 4])((void*)p50, 0xd);

    int em2 = FUN_0067ddd0();
    int ef = (int)((FP0)VT(em2)[0xa0 / 4])((void*)em2);
    *(unsigned*)(ef + 0xd8) = *(unsigned*)0x16c7268 ^ 0x80000000u;
    *(unsigned*)(ef + 0xdc) = *(unsigned*)0x16c726c ^ 0x80000000u;
    *(unsigned*)(ef + 0xe0) = *(unsigned*)0x16c7270 ^ 0x80000000u;
    *(unsigned*)(ef + 0xe4) = 0;
}
}  // namespace SP
