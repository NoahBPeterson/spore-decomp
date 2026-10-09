// Slice s00eb1e80: SP::cGameCinematicsAppMode (cinematics app mode) + int-vector helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---- callees ----
int  FUN_0067dd20();                      // 0x0067dd20
int  FUN_0067dd50();                      // 0x0067dd50
int  FUN_0067de00();                      // 0x0067de00
int  FUN_0067dd80();                      // 0x0067dd80
int  FUN_0067dd20b();
int  FUN_00b3d4d0();                      // 0x00b3d4d0
void FUN_00ad7df0();                      // 0x00ad7df0
void FUN_00ad7dc0();                      // 0x00ad7dc0
int  FUN_00b3d340();                      // 0x00b3d340
int  FUN_00b26710();                      // 0x00b26710
int  FUN_00b3d350(int a, int b, int c);   // 0x00b3d350
void FUN_00b8c330();                      // 0x00b8c330 (thiscall)
void sInitMinimap(int a, int b, int c);   // 0x00b3d350/…
int  PlanetModel();
void* ModelManager();
void* LightingManager();
void* EffectsManager();
void* MessageServer();
int* FUN_006eea10();
int  FUN_00fb7bf0(int x);
int  FUN_00fb7b30(int x);
void FUN_00fbacb0(int x);
void FUN_00478930(int x);
int  FUN_0093a6c0(int a, void* b, int c);
void FUN_0093a800(int a, void* b, int c, int d);
void FUN_00eb0230(int* x);
void FUN_00eb2070(int* v, unsigned n);
void FUN_00eb1e80(int* v, int* pos, unsigned n, int* val);
void FUN_00b8c0f0();
void* cGameCinematicsAppMode_ctor_alloc();
void FUN_00b26710b();
void FUN_00b3d4d0b();

struct IVtbl10 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void m(int a);
};
struct IVtbl6 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void m(int a);
};
struct B0 { void FUN_00ad7df0(); };
struct B1 { void FUN_00b26710(); };

namespace SP {
struct cGameCinematicsAppMode {
    char pad[0x100];
    bool OnKeyDown(int k, int v);                       // 0x00eb2370
    void HandleSimulationUpdate(float a, float b);      // 0x00eb23d0
    unsigned AsInterface(int id);                       // 0x00eb2440
    void DtorBody();                                    // 0x00eb2470
    int Init(int* p);                                   // 0x00eb2520
    bool Shutdown();                                    // 0x00eb25d0
    unsigned HandleMessage(unsigned msg);               // 0x00eb2600
    cGameCinematicsAppMode* CtorBody();                 // 0x00eb28e0
    int Activate();                                     // 0x00eb2990
    void Deactivate();                                  // 0x00eb2c70
    int ReadResource(int* p);                           // 0x00eb20d0
};
}

// int vector (begin/end/capacity)
void* memmove(void* d, const void* s, unsigned n);
int   FUN_00f473a0(int sz, const char* name, int a, int b, int c, int d);
void  FUN_00eb7010();

struct VectorI {
    int* begin;
    int* end;
    int* cap;
    void insert(int* pos, unsigned n, int* val);   // 0x00eb1e80
    void resize(unsigned n);
};

// @ 0x00eb1e80
void VectorI::insert(int* pos, unsigned n, int* val)
{
    int v = *val;
    int* e = end;
    unsigned tail = (unsigned)(e - pos);
    if (n < tail) {
        memmove(pos + n, pos, (unsigned)((char*)e - (char*)pos));
        for (int* p = pos; p != pos + n; ++p) *p = v;
        return;
    }
    unsigned extra = n - tail;
    int* q = e;
    for (unsigned i = 0; i < extra; i++) *q++ = v;
    end = e + extra;
    memmove(pos + n, pos, (unsigned)((char*)e - (char*)pos));
    for (int* p = pos; p != pos + tail; ++p) *p = v;
}

// @ 0x00eb2070
void VectorI::resize(unsigned n)
{
    int* e = end;
    unsigned cur = (unsigned)(e - begin);
    if (cur < n) {
        int z = 0;
        insert(e, n - cur, &z);
        return;
    }
    end = begin + n;
}

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

// @ 0x00eb23d0
void cGameCinematicsAppMode::HandleSimulationUpdate(float a, float b)
{
    int iVar1 = (int)(b * 1000.0f);
    int iVar2 = FUN_00b3d4d0();
    (*(void(**)(int,int))(*(int*)(iVar2 + 4) + 0x38))(iVar1, (int)(a * 1000.0f));
    int* p = (int*)FUN_00b3d350(iVar1, 0, 0);
    (*(void(**)(void))(*p + 0x38))();
}

// @ 0x00eb2440
unsigned cGameCinematicsAppMode::AsInterface(int id)
{
    if (id != (int)0xae9cb0fa && id != (int)0xee3f516e && id != 0x2f009dd0)
        return 0;
    return (this != (cGameCinematicsAppMode*)4) ? (unsigned)this : 0;
}

// @ 0x00eb25d0
bool cGameCinematicsAppMode::Shutdown()
{
    int* q;
    ((IVtbl6*)ModelManager())->m(0x487b104);
    q = *(int**)((char*)this + 0x1c);
    if (q != 0) {
        *(int*)((char*)this + 0x1c) = 0;
        (*(void(**)(void))(*q + 4))();
    }
    return true;
}

// @ 0x00eb28e0
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

// @ 0x00eb2470
void cGameCinematicsAppMode::DtorBody()
{
    // vtable restoration + release of the three AutoRefCount worlds (approximate)
}

// @ 0x00eb2520
int cGameCinematicsAppMode::Init(int* param_2)
{
    int* piVar3 = (int*)(*(int(**)(void))(*param_2 + 0x50))();
    if (piVar3 != 0)
        (*(void(**)(int, void(*)(void)))(*piVar3 + 0x20))(0x40546d5, FUN_00eb7010);
    return 1;
}

// @ 0x00eb2600
unsigned cGameCinematicsAppMode::HandleMessage(unsigned msg)
{
    if (msg == 0x49102f1 || msg == 0x462ade4 || msg == 0x4065b23 || msg == 0x44f1189 ||
        msg == 0x48a74e4 || msg == 0x4ebaca5 || msg == 0x49ce8fc || msg == 0x4ebac98 ||
        msg == 0x5272ace)
        return 0;
    return 0;
}

// @ 0x00eb20d0
int cGameCinematicsAppMode::ReadResource(int* param_2)
{
    (void)param_2;
    return 0;
}

// @ 0x00eb2990
int cGameCinematicsAppMode::Activate()
{
    return 1;
}

// @ 0x00eb2c70
void cGameCinematicsAppMode::Deactivate()
{
}
}
