// Audio setup (0xea8160, 2156 bytes, __thiscall, no args, returns true): creates the mix mode manager, then
// registers every creature-ability handler with the audio system and finally the layer object.
#include "types.h"
#include <stddef.h>
#include <math.h>

void* __cdecl operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0xf473a0

struct IRefCounted {
    virtual void v0();
    virtual void v1();
    virtual void AddRef();                  // +8
    virtual void Release();                 // +0xc
};

struct cMixModeManager : IRefCounted {
    uint32_t pad04[(0x6c - 4) / 4];
    cMixModeManager();                      // 0xeaa7c0
    void Shutdown();                        // 0xea9c70
    void Init();                            // 0xeaa9a0
};

// Intrusive smart pointer exactly as the engine's AutoRefCount: assignment adds the new reference first.
struct MixModeRef {
    cMixModeManager* mp;
    cMixModeManager* operator->() const { return mp; }
    operator bool() const { return mp != 0; }
    MixModeRef& operator=(cMixModeManager* p)
    {
        cMixModeManager* old = mp;
        if (p != old) {
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    void reset()
    {
        cMixModeManager* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
    }
};

// Creature-ability / audio handler objects; only their sizes and constructors matter here.
#define HANDLER(va, size) struct C_##va { uint32_t pad[(size) / 4]; C_##va(); };
HANDLER(00ea5b30, 0x38)   // 0xea5b30
HANDLER(00ea5cd0, 0x38)
HANDLER(00ea5db0, 0x38)
HANDLER(00ea5e90, 0x38)
HANDLER(00ea5f50, 0x38)
HANDLER(00ea5830, 0x3c)
HANDLER(00ea6010, 0x38)
HANDLER(00ea61a0, 0x38)
HANDLER(00ea59b0, 0x44)
HANDLER(00ea62b0, 0x38)
HANDLER(00ea55b0, 0x48)
HANDLER(00ea6360, 0x38)
HANDLER(00ea6580, 0x38)
HANDLER(00ea66d0, 0x38)
HANDLER(00ea6840, 0x38)
HANDLER(00ea6950, 0x38)
HANDLER(00ea6a50, 0x38)
HANDLER(00ea6bb0, 0x38)
HANDLER(00ea6d40, 0x38)
HANDLER(00ea6e90, 0x38)
HANDLER(00ea6f90, 0x38)
HANDLER(00ea7100, 0x38)
HANDLER(00ea7210, 0x38)
HANDLER(00ea7310, 0x4c)
HANDLER(00ea73a0, 0x4c)
HANDLER(00ea7440, 0x4c)
HANDLER(00ea74d0, 0x4c)
HANDLER(00ea7560, 0x4c)
HANDLER(00ea7600, 0x40)
HANDLER(00ea76d0, 0x40)
HANDLER(00ea77a0, 0x44)
HANDLER(00ea7910, 0x38)
HANDLER(00ea7a20, 0x38)
HANDLER(00ea7b50, 0x38)
HANDLER(00ea7c40, 0x38)
HANDLER(00ea7d20, 0x38)
HANDLER(00ea7e00, 0x38)
HANDLER(00ea7ee0, 0x38)
HANDLER(00ea8010, 0x38)

struct C_00e9e750 {                         // 0x7dc bytes, has a vtable
    virtual void v0();
    virtual void v1();
    virtual void vf2();                     // +8
    uint32_t pad04[(0x7dc - 4) / 4];
    C_00e9e750();                           // 0xe9e750
};
struct C_00ea4fd0 { uint32_t pad[3]; C_00ea4fd0(); };   // 0xea4fd0

// EA::Audio system (GetSystemAT): handlers are registered at slot 6.
struct cAudioAT {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual float* GetListenerPos(int flag);  // +0x10
    virtual void s5();
    virtual void Register(void* handler);   // +0x18
};
// SP::AudioSystem
struct cAudioSystem {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7();
    virtual void RegisterLayer(C_00e9e750* o);   // +0x20
    virtual void s9();
    virtual void SetObject(void* o);        // +0x28
};

cAudioAT* __cdecl GetSystemAT();            // 0xa206f0
cAudioSystem* __cdecl AudioSystem();        // 0x67cb00

struct AudioSetup {
    uint32_t pad00[3];
    MixModeRef mMixMgr;                     // +0xc
    bool Setup();
    bool FUN_00ea8a90(int id, int unused);
    bool FUN_00ea8ad0();
};

#define REGISTER(T) at->Register(new ("Audio", 0, 0, 0, 0) T())

// @ 0x00ea8160
bool AudioSetup::Setup()
{
    cAudioAT* at = GetSystemAT();
    cAudioSystem* sys = AudioSystem();
    if (at != 0 && sys != 0) {
        if (mMixMgr) {
            mMixMgr->Shutdown();
            mMixMgr.reset();
        }
        mMixMgr = new ("Audio", 0, 0, 0, 0) cMixModeManager();
        mMixMgr->Init();
        REGISTER(C_00ea5b30);
        REGISTER(C_00ea5cd0);
        REGISTER(C_00ea5db0);
        REGISTER(C_00ea5e90);
        REGISTER(C_00ea5f50);
        REGISTER(C_00ea5830);
        REGISTER(C_00ea6010);
        REGISTER(C_00ea61a0);
        REGISTER(C_00ea59b0);
        REGISTER(C_00ea62b0);
        REGISTER(C_00ea55b0);
        REGISTER(C_00ea6360);
        REGISTER(C_00ea6580);
        REGISTER(C_00ea66d0);
        REGISTER(C_00ea6840);
        REGISTER(C_00ea6950);
        REGISTER(C_00ea6a50);
        REGISTER(C_00ea6bb0);
        REGISTER(C_00ea6d40);
        REGISTER(C_00ea6e90);
        REGISTER(C_00ea6f90);
        REGISTER(C_00ea7100);
        REGISTER(C_00ea7210);
        REGISTER(C_00ea7310);
        REGISTER(C_00ea73a0);
        REGISTER(C_00ea7440);
        REGISTER(C_00ea74d0);
        REGISTER(C_00ea7560);
        REGISTER(C_00ea7600);
        REGISTER(C_00ea76d0);
        REGISTER(C_00ea77a0);
        REGISTER(C_00ea7910);
        REGISTER(C_00ea7a20);
        REGISTER(C_00ea7b50);
        REGISTER(C_00ea7c40);
        REGISTER(C_00ea7d20);
        REGISTER(C_00ea7e00);
        REGISTER(C_00ea7ee0);
        REGISTER(C_00ea8010);
        C_00e9e750* layer = new ("Audio", 0, 0, 0, 0) C_00e9e750();
        sys->RegisterLayer(layer);
        layer->vf2();
        sys->SetObject(new ("Audio", 0, 0, 0, 0) C_00ea4fd0());
    }
    return true;
}

// ---------------------------------------------------------------------------
// Additional AudioSetup / audio-helper entry points in this slice.
// ---------------------------------------------------------------------------
void __cdecl FUN_00f47380(void* p);          // 0xf47380 operator delete

struct DtorA {
    void* vtbl0;                             // +0x00
    void* vtbl4;                             // +0x04
    void* vtbl8;                             // +0x08
    char pad0c[0x0c];
    IRefCounted* obj18;                      // +0x18
    char pad1c[0x1c];
    char* begin38;                           // +0x38
    char gap3c[4];
    char* end40;                             // +0x40
    DtorA* FUN_00ea89d0(unsigned char flags);
};

// @ 0x00ea89d0
DtorA* DtorA::FUN_00ea89d0(unsigned char flags)
{
    if (end40 - begin38 > 1 && begin38 != 0)
        FUN_00f47380(begin38);
    if (obj18 != 0)
        obj18->v1();
    vtbl8 = (void*)0x013ef094;
    vtbl4 = (void*)0x013eb394;
    vtbl0 = (void*)0x013eb938;
    if ((flags & 1) != 0)
        FUN_00f47380(this);
    return this;
}

struct DtorB {
    void* vtbl0;                             // +0x00
    void* vtbl4;                             // +0x04
    void* vtbl8;                             // +0x08
    char pad0c[0x0c];
    IRefCounted* obj18;                      // +0x18
    char pad1c[0x10];
    char* begin2c;                           // +0x2c
    char gap30[4];
    char* end34;                             // +0x34
    DtorB* FUN_00ea8a30(unsigned char flags);
};

// @ 0x00ea8a30
DtorB* DtorB::FUN_00ea8a30(unsigned char flags)
{
    if (end34 - begin2c > 1 && begin2c != 0)
        FUN_00f47380(begin2c);
    if (obj18 != 0)
        obj18->v1();
    vtbl8 = (void*)0x013ef094;
    vtbl4 = (void*)0x013eb394;
    vtbl0 = (void*)0x013eb938;
    if ((flags & 1) != 0)
        FUN_00f47380(this);
    return this;
}

struct MsgServerIface {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4();
    virtual void Send14(int id, int a, int b);       // +0x14
    virtual void m6(); virtual void m7();
    virtual void Send20(void* self, int id);         // +0x20
};

extern MsgServerIface* FUN_0067dcc0();       // 0x67dcc0
extern MsgServerIface* FUN_00883860();       // 0x883860

// @ 0x00ea8a90
bool AudioSetup::FUN_00ea8a90(int id, int unused)
{
    bool ok = (id == 0x0578f803);
    if (ok) {
        Setup();
        MsgServerIface* m = FUN_0067dcc0();
        m->Send14(0x07c7686f, 0, 0);
    }
    return ok;
}

// @ 0x00ea8ad0
bool AudioSetup::FUN_00ea8ad0()
{
    MsgServerIface* m = FUN_0067dcc0();
    m->Send20(this, 0x0578f803);
    return Setup();
}

struct RefHolder {
    char pad00[0x14];
    IRefCounted sub;                         // +0x14
};

struct ManagerIface {
    virtual void m0(); virtual void m1(); virtual void m2();
    virtual void V0c(void* outField, void** outObj, int a, int b, int c, int d); // +0xc
};

extern ManagerIface* FUN_0067dcd0();         // 0x67dcd0

struct AudioObj {
    virtual void a0();  virtual void a1();  virtual void a2();  virtual void a3();
    virtual void a4();  virtual void a5();  virtual void a6();  virtual void a7();
    virtual void a8();  virtual void a9();  virtual void a10(); virtual void a11();
    virtual void a12();
    virtual void SetVolume(float volume);    // +0x34
    virtual void v38();                      // +0x38
    int field04;                             // +0x04
    char pad08[0x18 - 0x08];
    IRefCounted* field18;                    // +0x18
    char pad1c[0x20 - 0x1c];                 // +0x1c..+0x1f
    int  m20;                                // +0x20
    float f24;                               // +0x24
    float f28;                               // +0x28
    float f2c;                               // +0x2c
    float f30;                               // +0x30
    float f34;                               // +0x34
    void FUN_00a16ed0(float f, int a);       // 0x00a16ed0
    bool FUN_00ea8ed0();
    void FUN_00ea8af0(float f, int a);
    void FUN_00ea8c30(float f, int a);
};

// @ 0x00ea8ed0
bool AudioObj::FUN_00ea8ed0()
{
    SetVolume(0.0f);
    MsgServerIface* server = FUN_00883860();
    if (server != 0)
        server->Send20(&field04, 0x02b0c259);

    void* local = 0;
    ManagerIface* mgr = FUN_0067dcd0();
    if (local != 0) {
        void* tmp = local;
        local = 0;
        ((IRefCounted*)tmp)->v1();
    }
    mgr->V0c(&f28, &local, 0, 0, 0, 0);

    IRefCounted* nw = local != 0 ? &((RefHolder*)local)->sub : 0;
    IRefCounted* old = field18;
    if (nw != old) {
        if (nw != 0) nw->v0();
        field18 = nw;
        if (old != 0) old->v1();
    }
    v38();
    if (local != 0)
        ((IRefCounted*)local)->v1();
    return true;
}

// ---------------------------------------------------------------------------
// Listener-distance helpers (0xea8af0 / 0xea8c30)
// ---------------------------------------------------------------------------
// The original inlines an x87 fsqrt for the distance reductions.
#pragma intrinsic(sqrt)
static inline float Sqrt(float x) { return (float)sqrt((double)x); }

// A three-component difference: the by-value return makes the compiler
// materialise the components (SSE subtracts) before the x87 reduction.
struct Vec3f { float x, y, z; };
static Vec3f SubVec(const Vec3f& a, const Vec3f& b)
{
    Vec3f r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
static float LengthVec(Vec3f v)
{
    return (float)sqrt((double)v.x * v.x + ((double)v.y * v.y + (double)v.z * v.z));
}

void __cdecl FUN_00cd7d10();          // 0x00cd7d10
void __cdecl FUN_00d3d420();          // 0x00d3d420
void __cdecl FUN_00acdff0();          // 0x00acdff0
void __cdecl FUN_00bf6e00();          // 0x00bf6e00
void __cdecl FUN_00b1e500();          // 0x00b1e500

extern const char g_GameModeTribe;    // 0x01654c04
extern const char g_LocationTribe;    // 0x01654c05
extern const char g_Mode2;            // 0x01654c02

// sApp (0x15fd8b0): the virtual at +0x38 returns the current location/mode tag.
struct IApp {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34();
    virtual const void* GetLocation();          // +0x38
};
IApp* __cdecl App();                            // 0x0067dd10

// An object whose vtable slot +0x2c returns its world position.
struct IPositioned {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28();
    virtual float* GetPos();                    // +0x2c
};

struct cTribe {
    char pad00[0x120];                          // +0x00..+0x11f
    IPositioned mPos;                           // +0x120
    int GetAdultPopulation();                   // 0x00c8f370
};

struct cRelationshipManager {
    float RelationshipBetween(void* a, void* b, void* c);   // 0x00d00d60
};
cRelationshipManager* __cdecl RelationshipManager();        // 0x00b3d2c0

struct cGameNounManager {
    int* GetGameDataVector(void (*a)(), void (*b)(), void (*c)(), void (*d)(), const void* tag);   // 0x00b21340
    cTribe* GetPlayerTribe();                   // 0x00bfc5f0
};
cGameNounManager* __cdecl NounManager();        // 0x00b3d300

// Ability object returned by the 0xea7040 lookup (position sub-object at +0x120).
struct AbilityA {
    char pad00[0x120];                          // +0x00..+0x11f
    IPositioned mPos;                           // +0x120
};
// Ability object returned by the 0xea5440 lookup (own vtable + a position sub-object at +0x34).
struct IAbilityB {
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0c();
    virtual void b10(); virtual void b14(); virtual void b18(); virtual void b1c();
    virtual void b20(); virtual void b24(); virtual void b28(); virtual void b2c();
    virtual void b30(); virtual void b34(); virtual void b38(); virtual void b3c();
    virtual void b40(); virtual void b44(); virtual void b48(); virtual void b4c();
    virtual void b50(); virtual void b54(); virtual void b58();
    virtual cTribe* GetTribe();                 // +0x5c
};
struct AbilityB : IAbilityB {
    char pad04[0x30];                           // +0x04..+0x33
    IPositioned mPos;                           // +0x34
};

AbilityA* __cdecl Ability_7040(int* vec, float* pos, int id);   // 0x00ea7040
AbilityB* __cdecl Ability_5440(int* vec, float* pos, int id);   // 0x00ea5440

// @ 0x00ea8af0
void AudioObj::FUN_00ea8af0(float f, int a)
{
    FUN_00a16ed0(f, a);

    float volume = 3.402823466e38f;             // FLT_MAX
    const void* loc = App()->GetLocation();
    if (loc == (const void*)&g_GameModeTribe || loc == (const void*)&g_LocationTribe) {
        float* p = GetSystemAT()->GetListenerPos(0);
        float pos[3];
        pos[0] = p[0];
        pos[1] = p[1];
        pos[2] = p[2];

        cGameNounManager* nm = NounManager();
        int* vec = nm->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420,
                                         FUN_00acdff0, FUN_00b1e500,
                                         (const void*)0x018c43e8);
        AbilityA* ab = Ability_7040(vec + 1, pos, 0x00ea7020);
        if (ab != 0) {
            float* q = ab->mPos.GetPos();
            Vec3f pv = { pos[0], pos[1], pos[2] };
            Vec3f qv = { q[0], q[1], q[2] };
            Vec3f d = SubVec(qv, pv);
            volume = LengthVec(d);
        }
    }
    SetVolume(volume);
}

// @ 0x00ea8c30
void AudioObj::FUN_00ea8c30(float f, int a)
{
    FUN_00a16ed0(f, a);

    if (App()->GetLocation() != (const void*)&g_Mode2)
        return;

    cGameNounManager* nm = NounManager();
    cRelationshipManager* rel = RelationshipManager();
    if (nm == 0 || rel == 0)
        return;

    float* p = GetSystemAT()->GetListenerPos(0);
    float pos[3];
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];

    int* vec = nm->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420,
                                     FUN_00bf6e00, FUN_00b1e500,
                                     (const void*)0x01e4daae);
    AbilityB* ab = Ability_5440(vec + 1, pos, 0x00ea5420);
    cTribe* owner = nm->GetPlayerTribe();
    if (ab == 0 || owner == 0)
        return;

    f2c = (float)(unsigned)owner->GetAdultPopulation();

    float* q1 = owner->mPos.GetPos();
    float dx1 = pos[0] - q1[0];
    float dy1 = pos[1] - q1[1];
    float dz1 = pos[2] - q1[2];
    f24 = Sqrt(dx1 * dx1 + dy1 * dy1 + dz1 * dz1);

    cTribe* other = ab->GetTribe();
    f30 = (float)(unsigned)other->GetAdultPopulation();

    float* q2 = ab->mPos.GetPos();
    float dx2 = pos[0] - q2[0];
    float dy2 = pos[1] - q2[1];
    float dz2 = pos[2] - q2[2];
    f28 = Sqrt(dx2 * dx2 + dy2 * dy2 + dz2 * dz2);

    f34 = rel->RelationshipBetween(ab->GetTribe(), owner, (void*)1);
}
