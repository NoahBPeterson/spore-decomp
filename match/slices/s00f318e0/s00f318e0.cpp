// Slice s00f318e0 -- Simulator scenario property object (bfs2 slice 12).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- helpers / globals
void* __cdecl MessageServer();                                   // 0x0067DCC0
void  __cdecl FUN_00fa92f0(void*);                               // 0x00FA92F0
extern int* g_16065fc;                                           // 0x016065FC
extern unsigned char g_16065f8;                                  // 0x016065F8

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};

struct Sub190 { char pad[0x1c]; void fn(); };                    // 0x00FA92F0 thiscall

struct Sub {
    char pad[0x58];
    float f58;
    float f5c;
    void setOne(int v);
    void fn1(Vector3);
    void fn2(Vector3);
    void fn3(Vector3);
    void fn4(Vector3);
    void setUV(float a, float b);          // 0x00FBD880
    void SetTerraformValues(float a, float b, int c);   // 0x00FBDDB0
    void GetRange(float* lo, float* hi);                // 0x00FB7C50
    void QuadSetHeight(float h);                        // 0x00FB7BF0
};

struct Msg {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual void s6(int, int, int, int);
};

struct Vec4 { int x, y, z; float w; Vec4* Set(); };

struct E12 { int key; int a; int b; };
struct Ent { void* p; char pad[12]; };
struct Ent16;
struct Node { void RefreshAll(); };
struct Param3;

struct Obj {
    char pad0[4];
    Sub* m4;                       // +0x004
    char pad8[0xc-8];
    float mC;                      // +0x00c
    char pad10[0x14-0x10];
    char* m14;                     // +0x014  (vector begin)
    char* m18;                     // +0x018  (vector end)
    char pad1c[0x28-0x1c];
    char* m28;                     // +0x028  (fill table)
    char pad2c[0xa0-0x2c];
    char* mA0;                     // +0x0a0  (vector begin)
    char* mA4;                     // +0x0a4  (vector end)
    char padA8[0xb4-0xa8];
    char* mB4;                     // +0x0b4  (fill table)
    char padB8[0xc8-0xb8];
    float mC8;                     // +0x0c8
    float mCC;                     // +0x0cc
    float mD0;                     // +0x0d0
    float mD4;                     // +0x0d4
    char padD8[0xdc-0xd8];
    float mDC;                     // +0x0dc
    float mE0;                     // +0x0e0
    float mE4;                     // +0x0e4
    char padE8[0xec-0xe8];
    int  mEC;                      // +0x0ec
    int  mF0;                      // +0x0f0
    char padF4[0x100-0xf4];
    void* m100;                    // +0x100
    unsigned char m104;            // +0x104
    char pad105[0x130-0x105];
    Vector3 v130;                  // +0x130
    Vector3 v13c;                  // +0x13c
    Vector3 v148;                  // +0x148
    Vector3 v154;                  // +0x154
    char pad160[0x178-0x160];
    int  m178;                     // +0x178
    int  m17C;                     // +0x17c
    int  m180;                     // +0x180
    int  m184;                     // +0x184
    int  m188;                     // +0x188
    char pad18C[0x190-0x18c];
    void*    m190;                 // +0x190
    Sub*     m194;                 // +0x194
    Node*    m198;                 // +0x198
    char*    m19C;                 // +0x19c
    char*    m1A0;                 // +0x1a0
    char pad1A4[0x1bc-0x1a4];
    float m1BC;                    // +0x1bc
    float m1C0;                    // +0x1c0
    float m1C4;                    // +0x1c4
    float m1C8;                    // +0x1c8

    float lerp();
    void  set104(int v);
    void  setE0(unsigned v);
    void  setE4(unsigned v);
    void  setEC(int v);
    void  setF0(int v);
    void  set148(const Vector3& v);
    void  set154(const Vector3& v);
    void  set130(const Vector3& v);
    void  set13c(const Vector3& v);
    char  onMsg(int a, int b);
    void  release100();
    void  setCC(float v);          // 0x00F31D80
    void  setD0(float v);          // 0x00F31DE0
    float ratio();                 // 0x00F31E60
    void  fit(float t);            // 0x00F32240
    void  tick(char force);        // 0x00F32440
    float weight();                // 0x00F325B0
    void  fill(Param3* p);         // 0x00F32710
    Ent16* findEnt(void* p);       // 0x00F32790
    char  anyValid();              // 0x00F327F0
};

struct X100 {
    virtual void s0(); virtual void Release(); virtual void s2();
    virtual void f0c(int); virtual char f10();
};

// @ 0x00F31B70
float Obj::lerp() { return m4->f58 + (m4->f5c - m4->f58) * mC; }

// @ 0x00F31C20
void Obj::set104(int v) { m104 = (unsigned char)v; m194->setOne(v); }

// @ 0x00F31D20
void Obj::setEC(int v) { if ((unsigned)(v-1) <= 0xe) { mEC = v; m194->setOne(v); } }

// @ 0x00F31D50
void Obj::setF0(int v) { if ((unsigned)(v-1) <= 0xe) { mF0 = v; m194->setOne(v); } }

// @ 0x00F31EA0
void MsgSend() { ((Msg*)MessageServer())->s6(0x36b154d8, 0, 0, 0); }

// @ 0x00F31FD0
Vec4* Vec4::Set() { x = 0; y = 0; z = 0; w = 1.0f; return this; }

// @ 0x00F32100
void Obj::set148(const Vector3& v) { v148 = v; m194->fn1(v148); }
// @ 0x00F32150
void Obj::set154(const Vector3& v) { v154 = v; m194->fn2(v154); }
// @ 0x00F321A0
void Obj::set130(const Vector3& v) { v130 = v; m194->fn3(v130); }
// @ 0x00F321F0
void Obj::set13c(const Vector3& v) { v13c = v; m194->fn4(v13c); }

// @ 0x00F32410
void ReleaseGlobal() { int* p = g_16065fc; if (p) { g_16065fc = 0; (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p); } g_16065f8 = 1; }

// @ 0x00F326F0
char Obj::onMsg(int a, int b) { if (a == 0x36b154d8 && m190 != 0) ((Sub190*)m190)->fn(); return 0; }

// @ 0x00F323C0
void Obj::release100()
{
    if (m100) {
        if (((X100*)m100)->f10()) {
            ((X100*)m100)->f0c(1);
            if (m100) {
                X100* p = (X100*)m100;
                m100 = 0;
                p->Release();
            }
        }
    }
}

// @ 0x00F326D0
struct C {
    char pad0[0x14];
    char* m14;                     // +0x014
    char* m18;                     // +0x018
    char pad1c[0xa0-0x1c];
    char* mA0;                     // +0x0a0
    char* mA4;                     // +0x0a4
    float f325b0();
    int below(int dummy);
};

struct Val { char pad[0x74]; float f74; };

static __forceinline float ClampUnit(float v)
{
    float lo = 0.0f;
    float hi = 1.0f;
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

// @ 0x00F326D0
int C::below(int dummy) { float r = f325b0(); if (r < 1.0f) return 1; return 0; }

// ---------------------------------------------------------------- active planet record
struct T { virtual void AddRef(); virtual void Release(); void AssignCopy(void*); };
struct SubG { void fn(T* p); };
void* __cdecl GetActivePlanetRecord();           // 0x010212A0
extern void* g_16c8750;                          // 0x016C8750
extern SubG  g_16c85a0;                          // 0x016C85A0

// @ 0x00F31F80
void SelectPlanetRecord()
{
    T* p = (T*)GetActivePlanetRecord();
    if (p != (T*)g_16c8750) {
        T* old = (T*)g_16c8750;
        if (p) p->AddRef();
        g_16c8750 = p;
        if (old) old->Release();
    }
    T* q = (T*)g_16c8750;
    if (q) g_16c85a0.fn(q);
}

// ---------------------------------------------------------------- scenario object helpers
#define NOINLINE __declspec(noinline)

void* __cdecl FUN_01021260();                    // 0x01021260  GetActivePlanet
void* __cdecl FUN_00b18e00(int key);             // 0x00B18E00
int   __cdecl FUN_00ecc100(int key);             // 0x00ECC100
unsigned __cdecl FUN_010c7aa0();                 // 0x010C7AA0
void  __cdecl FUN_00c2e4e0(int v);               // 0x00C2E4E0  sys_gui
void* __cdecl SP_PlanetModel();                  // 0x00B3D350
void* __cdecl SP_App();                          // 0x0067DD10
void* __cdecl SP_NounManager();                  // 0x00B3D300
void* __cdecl SP_TimeOfDayInstance();            // 0x00BC30B0
void* __cdecl GetManager();                      // 0x0067DCD0
void  __cdecl RemoveHandler(int, int, int, int, int);   // 0x00571DB0

extern float g_16c84f8;                          // 0x016C84F8
extern float g_16c84fc;                          // 0x016C84FC
extern float g_16c8500;                          // 0x016C8500
extern unsigned char g_16c84f4;                  // 0x016C84F4
extern int g_15b0150;                            // 0x015B0150

struct WorldGlobals {
    char pad74[0x74];
    Node* m74;                                   // +0x074
    char pad78[0xd0-0x78];
    int mD0;                                     // +0x0d0
};
extern WorldGlobals* g_16c7aa4;                  // 0x016C7AA4

struct TerrainApi { void SetCC(float v); void SetD0(float v); };
struct PlanetModelApi { void Shutdown(); void ComputeContinents(); };
struct NounMgr { void* GetAvatar(); };
struct Tod { char pad[0x24]; float f24; void fn(float, Vector3*); };

struct XInner {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual int v1c();
};
struct XApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual XInner* v50();
};
struct XSub {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual Vector3* v2c();
};
struct Avatar { char pad[0xc0]; XSub sub; };

struct V2C {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int v20();
    virtual void v24(); virtual void v28(); virtual Vector3* v2c();
};
struct X34 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual float v34();
};

struct P2 { int key; Sub* s; };
struct Sub2 { char pad[0x60]; float f60; float f64; };
struct Cnt { int* data; char pad[0x10]; int count; };

struct SrcBase { char pad[0x68]; unsigned char b68; };
struct Param3 { int key; char* base; int idx; };
struct FillEnt { unsigned short flags; unsigned short count; int x, y, z; char rest[0x28]; };
struct Ent16 { void* p; char pad[12]; };

static __forceinline void FillOne(FillEnt* e, Vector3* v)
{
    int* b = (int*)v;
    e->x = b[0];
    e->y = b[1];
    int z = b[2];
    e->flags |= 4;
    e->count++;
    e->z = z;
}

struct C0C { virtual void v00(); virtual void Release(); };
struct C10 { virtual void v00(int); int count; };
struct ObjD {
    char pad0[0xc];
    C0C* m0C;                                    // +0x00c
    C10* m10;                                    // +0x010
    char pad14[0x178-0x14];
    int m178;                                    // +0x178
    int m17C;                                    // +0x17c
    int m180;                                    // +0x180
    int m184;                                    // +0x184
    int m188;                                    // +0x188
};

struct ResourceKey { int mInstanceID; int mTypeID; int mGroupID; };
struct ScenarioObj;
struct ResourceObject {
    virtual void v00(); virtual void Release(); virtual void v08();
    virtual ScenarioObj* v0c(int id);
};
struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey& key, ResourceObject** out, int, int, int, int);
};
template<class T> struct AutoPtr {
    T* mp;
    AutoPtr() : mp(0) {}
    ~AutoPtr() { if (mp) { T* p = mp; mp = 0; p->Release(); } }
    T** AsPP() { return &mp; }
    T* get() const { return mp; }
};
struct ScenarioObj {
    char pad0[0x78];
    int m78;                                     // +0x078
    char pad7c[0x150-0x7c];
    float m150;                                  // +0x150
    float m154;                                  // +0x154
    float m158;                                  // +0x158
    char pad15c[0x175-0x15c];
    unsigned char m175;                          // +0x175
    char pad176[0x2c2c-0x176];
    unsigned char m2c2c;                         // +0x2c2c
    char pad2c2d[0x2ca8-0x2c2d];
    unsigned int m2ca8;                          // +0x2ca8
    char f25af0();
    char f2b270(int v);
    char f262e0();
};
struct DeclareParam {
    int mKey; int mType; int mValue;
    NOINLINE DeclareParam(unsigned k, int v) : mKey((int)k), mType(0x2e1a75d), mValue(v) {}
};
struct Params { void push_back(const DeclareParam&); };

// ---------------------------------------------------------------- 0x2cb0 helpers
// @ 0x00F31B90
float __fastcall FUN_00f31b90(Sub* s, float t)
{
    float a = s->f58;
    float b = s->f5c;
    if (b <= a)
        return 1.0f;
    float r = (t - a) / (b - a);
    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;
    return r;
}

// @ 0x00F31D80
void Obj::setCC(float v)
{
    mCC = v;
    void* planet = FUN_01021260();
    if (planet && m194) {
        ((TerrainApi*)planet)->SetCC(v);
        m194->SetTerraformValues(mD0, v, 0);
    }
}

// @ 0x00F31DE0
void Obj::setD0(float v)
{
    mD0 = v;
    void* planet = FUN_01021260();
    if (planet && m194) {
        ((TerrainApi*)planet)->SetD0(v);
        m194->SetTerraformValues(v, mCC, 0);
    }
}

// @ 0x00F31E60
float Obj::ratio()
{
    float lo, hi;
    m194->GetRange(&lo, &hi);
    return (mC8 - lo) / (hi - lo);
}

// @ 0x00F31EE0
int __fastcall FUN_00f31ee0(Cnt* c)
{
    return c->count ? c->data[c->count - 1] : 0;
}

struct Variant {
    int m0, m4, m8, mC;
    unsigned short w10;
    unsigned short w12;
    Variant() : w10(0), w12(0) {}
    void Construct(unsigned short, unsigned short, const void*, unsigned int, unsigned int);
    void Destruct(int);
};
struct IFace14 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(int, Variant*);
};

// @ 0x00F31F20
void FUN_00f31f20(IFace14* self, int p2, int p3, int p4)
{
    Variant v;
    v.Construct(0x20, 0x98, (const void*)p4, 0xc, (unsigned int)p3);
    self->v14(p2, &v);
    if (v.w10 & 4)
        v.Destruct(0);
}

// @ 0x00F31FF0
float __fastcall FUN_00f31ff0(P2* p)
{
    X34* x = (X34*)FUN_00b18e00(p->key);
    Sub2* s = (Sub2*)p->s;
    return (s->f64 - s->f60) * (x->v34() - 3.0f) + s->f60;
}

// @ 0x00F32030
void __fastcall FUN_00f32030(ObjD* self)
{
    C0C* p0 = self->m0C;
    if (p0) {
        self->m0C = 0;
        p0->Release();
    }
    C10* p = self->m10;
    if (p) {
        self->m10 = 0;
        int c = p->count;
        --c;
        p->count = c;
        if (c == 0) {
            p->count = 1;
            p->v00(1);
        }
    }
    ((PlanetModelApi*)SP_PlanetModel())->Shutdown();
    GetActivePlanetRecord();
    if (g_16c7aa4->mD0 == 2 && g_16c8750) {
        ((T*)g_16c8750)->AssignCopy(&g_16c85a0);
        T* q = (T*)g_16c8750;
        if (q) {
            g_16c8750 = 0;
            q->Release();
        }
    }
    FUN_00c2e4e0(0);
    int h = self->m178;
    if (h) {
        self->m178 = 0;
        RemoveHandler(h, self->m17C, self->m180, self->m184, self->m188);
    }
}

// @ 0x00F32240
void Obj::fit(float t)
{
    if (!FUN_01021260() || !m194)
        return;
    float lo, hi;
    m194->GetRange(&lo, &hi);
    float r = (hi - lo) * t + lo;
    if (r < 0.0f) r = 0.0f;
    else if (r > 1.0f) r = 1.0f;
    mC8 = r;
    m194->QuadSetHeight(r);
    ((PlanetModelApi*)SP_PlanetModel())->ComputeContinents();
    m198 = g_16c7aa4->m74;
    if (m198)
        m198->RefreshAll();
}

// @ 0x00F32440
void Obj::tick(char force)
{
    if (mDC == 0.0f && !force)
        return;
    XInner* o = ((XApp*)SP_App())->v50();
    if (!o->v1c())
        return;
    Vector3 v;
    v.x = 1.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    void* av = ((NounMgr*)SP_NounManager())->GetAvatar();
    if (av) {
        Vector3* q = ((Avatar*)av)->sub.v2c();
        v = *q;
    }
    bool changed;
    if (m1BC == v.x && m1C0 == v.y && m1C4 == v.z && m1C8 == mD4)
        changed = false;
    else {
        m1BC = v.x;
        m1C0 = v.y;
        m1C4 = v.z;
        m1C8 = mD4;
        changed = true;
    }
    Tod* tod = (Tod*)SP_TimeOfDayInstance();
    if (tod && changed)
        tod->fn(tod->f24 * mD4, &v);
}

// @ 0x00F325B0
NOINLINE float C::f325b0()
{
    float sum = 0.0f;
    int n = (int)((m18 - m14) / 12);
    for (int i = 0; i != n; i++) {
        E12& e = ((E12*)(m14 + i * 12))[0];
        int q = FUN_00ecc100(e.key);
        sum += q ? ((Val*)q)->f74 : 1.0f;
    }
    n = (int)((mA4 - mA0) / 12);
    for (int i = 0; i != n; i++) {
        E12& e = ((E12*)(mA0 + i * 12))[0];
        int q = FUN_00ecc100(e.key);
        sum += q ? ((Val*)q)->f74 : 1.0f;
    }
    return ClampUnit(sum * 0.002f);
}
// @ 0x00F31C40
void Obj::setE0(unsigned v) {
    if (v - 1 <= 0x3f) {
        float f = (float)v;
        mE0 = f;
        m194->setUV((f - 0.5f) * 0.015625f, (mE4 - 0.5f) * 0.015625f);
    }
}

// @ 0x00F31CB0
void Obj::setE4(unsigned v) {
    if (v - 1 <= 0x3f) {
        float f = (float)v;
        mE4 = f;
        m194->setUV((mE0 - 0.5f) * 0.015625f, (f - 0.5f) * 0.015625f);
    }
}
// @ 0x00F32710
void Obj::fill(Param3* p)
{
    SrcBase* b = (SrcBase*)p->base;
    int idx = p->idx;
    V2C* x = (V2C*)FUN_00b18e00(p->key);
    if (b->b68) {
        FillEnt* e = (FillEnt*)(mB4 + idx * 0x38);
        FillOne(e, x->v2c());
    } else {
        FillEnt* e = (FillEnt*)(m28 + idx * 0x38);
        FillOne(e, x->v2c());
    }
}

// @ 0x00F32790
Ent16* Obj::findEnt(void* p)
{
    if (!p)
        return 0;
    if (((V2C*)p)->v20() != g_15b0150)
        return 0;
    unsigned n = (unsigned)((m1A0 - m19C) >> 4);
    Ent16* e = (Ent16*)m19C;
    for (unsigned i = 0; i < n; i++)
        if (p == e[i].p)
            return &e[i];
    return 0;
}

// @ 0x00F327F0
char Obj::anyValid()
{
    unsigned n = (unsigned)((m18 - m14) / 12);
    for (unsigned i = 0; i < n; i++)
        if (FUN_00ecc100(((E12*)(m14 + i * 12))->key))
            return 1;
    n = (unsigned)((mA4 - mA0) / 12);
    for (unsigned i = 0; i < n; i++)
        if (FUN_00ecc100(((E12*)(mA0 + i * 12))->key))
            return 1;
    return 0;
}

// @ 0x00F318E0
bool __stdcall FUN_00f318e0(ResourceKey* key, Params* params)
{
    if (key->mTypeID != 0x366a930d)
        return false;
    AutoPtr<ResourceObject> obj;
    IResourceManager* mgr = (IResourceManager*)GetManager();
    if (!mgr->GetResource(*key, obj.AsPP(), 0, 0, 0, 0))
        return false;
    if (obj.get() == 0)
        return false;
    ScenarioObj* o = obj.get()->v0c(0xe742574a);
    if (o == 0)
        return false;
    int id = o->m78;
    if (o->m150 == g_16c84f8 && o->m154 == g_16c84fc && o->m158 == g_16c8500)
        id = 0x24720859;
    int bA = 1;
    if (id == 0x24720859)
        bA = 0;
    if (o->f25af0())
        bA = 0;
    int flag2c2c = (o->m2c2c != 0);
    int bB = (id != 0x24720859);
    if (flag2c2c && !g_16c84f4)
        bB = 0;
    int flag175 = (o->m175 != 0);
    int uVar16 = 0;
    if (o->f2b270(0x800)) {
        uVar16 = 1;
        bA = 0;
    }
    int uVar15 = 0;
    if (!o->f262e0()) {
        uVar15 = 1;
        bA = 0;
    }
    unsigned a = o->m2ca8;
    unsigned b = FUN_010c7aa0();
    int bC = 0;
    if (a > b) {
        bA = 0;
        bC = 1;
        bB = 0;
    }
    params->push_back(DeclareParam(0x2dc9d1e, id));
    params->push_back(DeclareParam(0x54a32960, bA));
    params->push_back(DeclareParam(0x665f917, 1));
    params->push_back(DeclareParam(0x67b82d8, bB));
    params->push_back(DeclareParam(0x15e8afc8, flag2c2c));
    params->push_back(DeclareParam(0xb91fba14, uVar15));
    params->push_back(DeclareParam(0xd22f5e35, uVar16));
    params->push_back(DeclareParam(0x5a3584a7, flag175));
    params->push_back(DeclareParam(0xdb4675dd, bC));
    return true;
}

