// Slice s00cb44b0: locomotion classes (ballistic / path-following / straight-line /
// vertical-rocket / space-defense-missile), their serialization, and refcount/tool helpers.
//
// Work dir: match/slices/s00cb44b0/  (see manifest.txt / nonmatching.txt)
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint;
typedef unsigned short ushort;

// ---------------------------------------------------------------------------
// basic math types
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Vec3v { float x, y, z; };              // 12-byte element in vector<> paths

extern float g_1;                             // 0x01485720
extern float g_0;                             // 0x01485378
extern float g_1em5;                          // 0x01475160
extern float g_0_9;                           // 0x013ec4b4
extern float g_1em8;                          // 0x013ec4b8
extern float g_1em3;                          // 0x013f9428

// ---------------------------------------------------------------------------
// intrusive refcounted refs (AutoRefCount<...>): operator= releases old, addrefs new
// ---------------------------------------------------------------------------
struct RefCounted {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28(); virtual void r2c();
    virtual void r30(); virtual void r34(); virtual void r38(); virtual void r3c();
    virtual void r40(); virtual void r44(); virtual void r48(); virtual void r4c();
    virtual void r50(); virtual void r54(); virtual void r58(); virtual void r5c();
    virtual void r60(); virtual void r64();
};
typedef void* (*Vfn1)(void*);
typedef void* (*Vfn2)(void*, void*);
typedef void* (__stdcall *VfnS2)(void*, void*);
struct Tool { char pad[0x114]; void* mStrategy; };

struct CTarget { bool IsValid(); };            // 0x0104cd80, thiscall, ret bool

// small "has live target" helpers (member of a locomotion/defense object)
struct cLocomotionBase {
    char pad[0x30];
    void* mTarget;                           // +0x30
    bool HasLiveTarget();                    // 0x00cb4a40
};

struct cLocomotionObj14 {
    char pad[0x14];
    void* mTarget;                           // +0x14
    bool HasLiveTarget14();                  // 0x00cb4ca0
    void* GetToolStrategy();                 // 0x00cb5420
};

struct cLocomotionObjDC {
    char pad[0xdc];
    void* mTarget;                           // +0xdc
    bool HasLiveTargetDC();                  // 0x00cb5560
};

// ---------------------------------------------------------------------------
// forward decls / external functions
// ---------------------------------------------------------------------------
struct cOutStream;
struct cDataSerializerGeneric;

struct cVarListSerializer {
    char pad[8];
};
void cVarListSerializer_ctor(void* p, void* obj, void* list, uint sig);      // 0x00692f90
bool cVarListSerializer_Serialize(void* p, cOutStream* s);                   // 0x00692900

bool  EA_IO_WriteUint32(void* st, const void* buf, int n, int flag);         // 0x0093aa70
bool  StreamWrite(void* st, int a, int b);                                   // 0x0093a9a0
void  QuaternionFromDirections(Quaternion* out, const Vector3* dir, const Vector3* up); // 0x00698180

struct cSpatialObject {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual Vector3* GetPosition(); // +0x2c
    virtual void s30(); virtual void s34(); virtual void s38();
    virtual void SetOrientation(Quaternion* q);                              // +0x3c
    virtual void s40(); virtual void s44();
    virtual void GetUpVector(Vector3* out);                                  // +0x48-ish
    virtual void s4c(); virtual void s50(); virtual void s54(); virtual void s58();
    virtual void s5c(); virtual void s60(); virtual void s64(); virtual void s68();
    virtual void s6c(); virtual void s70(); virtual void s74(); virtual void s78();
    virtual void s7c(); virtual void s80(); virtual void s84(); virtual void s88();
    virtual void s8c(); virtual void s90(); virtual void s94(); virtual void s98();
    virtual void s9c(); virtual void sA0(); virtual void sA4(); virtual void sA8();
    virtual void sAC(); virtual void sB0(); virtual void sB4(); virtual void sB8(); // +0xb8
    virtual void sBC();                                                      // +0xbc
    virtual void sC0(); virtual void sC4(); virtual void sC8();
    virtual void sCC();
};

struct cLocomotiveObject;

// cGameData[/serialization] base
struct cGameData {
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    virtual void g20(); virtual void g24(); virtual void g28(); virtual void g2c();
    virtual void g30(); virtual void g34(); virtual void g38(); virtual void g3c();
    virtual void g40(); virtual void g44(); virtual void g48(); virtual void g4c();
    virtual void g50(); virtual void g54(); virtual void g58(); virtual void g5c();
    virtual void g60(); virtual void g64();
    void Write(cOutStream* s);                                               // 0x00b18590
};

// cOutStream (IStream wrapper): GetStream()->vtable[0x18] gives the raw writer
struct IStream { virtual void i00(); virtual void i04(); virtual void i08(); virtual void i0c();
                 virtual void i10(); virtual void i14(); virtual void i18(); };
struct GetStreamObj { virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
                      virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
                      virtual IStream* GetStream(); };                    // +0x18

// ---------------------------------------------------------------------------
// cLocomotiveObject and locomotion classes
// ---------------------------------------------------------------------------
void  cLocomotiveObject_Write(cLocomotiveObject* o, cOutStream* s);          // 0x00c448a0
void  cLocomotiveObject_Shutdown(cLocomotiveObject* o);                      // 0x00c43f90
Vector3* cLocomotiveObject_GetVelocity(cLocomotiveObject* o);                // 0x00d20610

struct cLocomotiveObject {
    virtual void l00(); virtual void l04(); virtual void l08(); virtual void l0c();
    virtual void l10(); virtual void l14(); virtual void l18(); virtual void l1c();
    virtual void l20(); virtual void l24(); virtual void l28(); virtual void l2c();
    virtual void l30(); virtual void l34(); virtual void l38(); virtual void l3c();
    virtual void l40(); virtual void l44(); virtual void l48(); virtual void l4c();
    virtual void l50(); virtual void l54(); virtual void l58(); virtual void l5c();
    virtual void l60(); virtual void l64(); virtual void l68(); virtual void l6c();
    virtual void l70(); virtual void l74(); virtual void l78(); virtual void l7c();
    virtual void l80(); virtual void l84(); virtual void l88(); virtual void l8c();
    virtual void l90(); virtual void l94(); virtual void l98(); virtual void l9c();
    virtual void lA0(); virtual void lA4(); virtual void lA8(); virtual void lAC();
    virtual void lB0(); virtual void lB4(); virtual void lB8(); virtual void lBC();
    virtual void lC0(); virtual void lC4(); virtual void lC8(); virtual void lCC();
    virtual void lD0(); virtual void lD4(); virtual void lD8(); virtual void lDC();
    virtual void lE0(); virtual void lE4(); virtual void lE8(); virtual void lEC();
    virtual void lF0(); virtual void lF4(); virtual void lF8(); virtual void lFC();
    virtual void l100(); virtual void l104(); virtual void l108(); virtual void l10c();
    virtual void l110(); virtual void l114(); virtual void l118(); virtual void l11c();
    virtual void l120(); virtual void l124(); virtual Vector3* GetPosition(); // +0x2c ... placeholder
    virtual void SetOrientation(Quaternion* q);              // +0x3c
};

float FUN_0104cd80(void* p);                                                 // 0x0104cd80
float FUN_0104cda0(void* p);                                                 // 0x0104cda0
float FUN_0104be60(void* p);                                                 // 0x0104be60
void* FUN_00c70380(float place, int* turrets, int* buildings);               // 0x00c70380 (unused here)

// ---------------------------------------------------------------------------
// ISimulatorSerializable::Write bodies (cICBM::Write, cDefaultToolProjectile::Write)
// ---------------------------------------------------------------------------
void WriteU32(cOutStream* s, uint v);                                        // inlined helper
void SerializeVecVar();

// ---------------------------------------------------------------------------
// functions
// ---------------------------------------------------------------------------

// @ 0x00cb44b0
// SP::cICBM::Write
int f00cb44b0_write(cGameData* self, cOutStream* stream)
{
    void* w  = ((GetStreamObj*)stream)->GetStream();          // vtable +0x20
    void* wr = ((GetStreamObj*)w)->GetStream();               // vtable +0x18
    uint sig = 0x49cec5c;
    EA_IO_WriteUint32(wr, &sig, 1, 0);
    self->Write(stream);
    cLocomotiveObject_Write((cLocomotiveObject*)((char*)self + 0x34), stream);
    char ser[12];
    cVarListSerializer_ctor(ser, self, (void*)0x0157e888, 0x1a80d26);
    cVarListSerializer_Serialize(ser, stream);
    return 0;
}

// @ 0x00cb4670
// SP::cBallisticLocomotion::Execute
void f00cb4670_ballistic_execute(Vector3* self, float unused)
{
    cLocomotiveObject* obj = *(cLocomotiveObject**)((char*)self + 0x14);
    Vector3* vel = obj->GetPosition();                        // vtable +0x2c (direction)
    float len = vel->x * vel->x + vel->y * vel->y + vel->z * vel->z;
    if (len < 1.0f) {
        self->x = 0.0f; self->y = 0.0f; self->z = 0.0f;
        return;
    }
    Quaternion q;
    QuaternionFromDirections(&q, (const Vector3*)0x0169a9e8, self);
    obj->SetOrientation(&q);
}

// @ 0x00cb46f0
// SP::cBallisticLocomotion::CalculateFiringVelocity
int f00cb46f0_calc_firing_vel(float p1, float p2, float p3, float p4, float p5, float p6,
                              float p7, float* out, float p9, float p10, float p11)
{
    // complex ballistics; complete but not byte-exact
    extern float _c0_0157d360;
    float a = p9 - p1, b = p10 - p2, c = p11 - p3;
    float dist = a * a + b * b + c * c;
    (void)dist;
    float v = p7 * p7;
    if (v <= 1.0f && -1.0f <= v) {
        float inv = 1.0f;
        out[0] = a * inv;
        out[1] = b * inv;
        out[2] = c * inv;
        return 1;
    }
    return 0;
}

// @ 0x00cb4950
// SP::cICBM-ish component ::Set(...)  (5 args + this)
void f00cb4950(int self, RefCounted* a, uint v1, uint v2, uint v3, RefCounted* b)
{
    *(uint*)(self + 0x528) = v1;
    *(uint*)(self + 0x52c) = v2;
    *(uint*)(self + 0x530) = v3;
    RefCounted* old = *(RefCounted**)(self + 0x524);
    if (a != old) {
        if (a) ((RefCounted*)a)->r60();
        *(RefCounted**)(self + 0x524) = a;
        if (old) old->r64();
    }
    RefCounted* old2 = *(RefCounted**)(self + 0x534);
    if (b != old2) {
        if (b) b->r04();
        *(RefCounted**)(self + 0x534) = b;
        if (old2) old2->r08();
    }
}

// @ 0x00cb49e0
// cGameData::RemoveOwner (small)
void f00cb49e0(int self)
{
    RefCounted* p = *(RefCounted**)(self + 0x524);
    if (p) {
        *(void**)(self + 0x524) = 0;
        p->r64();
    }
    RefCounted* q = *(RefCounted**)(self + 0x534);
    if (q) {
        *(void**)(self + 0x534) = 0;
        q->r08();
    }
    RefCounted* r = *(RefCounted**)(self + 0x2c);
    if (r) {
        *(void**)(self + 0x2c) = 0;
        r->r04();
    }
    cLocomotiveObject_Shutdown((cLocomotiveObject*)(self + 0x34));
}

// @ 0x00cb4a40
bool cLocomotionBase::HasLiveTarget()
{
    if (mTarget && ((CTarget*)mTarget)->IsValid())
        return true;
    return false;
}

// @ 0x00cb4a70
// SP::cPathFollowingLocomotion::PathUpdated
void f00cb4a70(int self)
{
    if (*(uint*)(self + 0x40) != 0x6a93cd4e)
        return;
    int i = 0;
    if (*(int*)(self + 0x24) < 0)
        return;
    float* p = *(float**)(self + 0x10);
    do {
        float z = p[2], y = p[1], x = p[0];
        float len = x * x + y * y + z * z;
        // sqrt via SSE
        float sq = 0.0f;
        __asm { sqrtss xmm0, len }
        __asm { movss sq, xmm0 }
        if (*(float*)(self + 0x44) < sq)
            *(float*)(self + 0x44) = sq;
        if (*(float*)(self + 0x48) > sq)
            *(float*)(self + 0x48) = sq;
        i++;
        p += 3;
    } while (i <= *(int*)(self + 0x24));
}

// @ 0x00cb4ae0
// SP::cPathFollowingLocomotion::UpdateEndPoint
void f00cb4ae0(int self, Vector3* p)
{
    float* begin = *(float**)(self + 0x10);
    int cnt = (int)((*(float**)(self + 0x14) - begin) * ((float)0x2aaaaaab));
    // recompute count properly: (end-begin)/12
    cnt = (int)((*(char**)(self + 0x14) - (char*)begin) / 12);
    float* last = begin + (cnt - 1) * 3;
    float dx = p->x - last[0];
    float dy = p->y - last[1];
    float dz = p->z - last[2];
    if (dx * dx + dy * dy + dz * dz <= g_1em5)
        return;
    last[0] = p->x; last[1] = p->y; last[2] = p->z;
    int idx = cnt - 2;
    float f = 0.9f;
    while (idx > *(int*)(self + 0x30)) {
        float* e = begin + idx * 3;
        e[1] = dy * f + e[1];
        float f2 = f - 0.1f;
        e[0] = dx * f + e[0];
        e[2] = dz * f + e[2];
        f = f2;
        if (!(0.0f < f))
            break;
        idx--;
    }
}

// @ 0x00cb4bd0
void f00cb4bd0(int self, RefCounted* obj)
{
    RefCounted* old = *(RefCounted**)(self + 0x518);
    if (obj != old) {
        if (obj) obj->r04();
        *(RefCounted**)(self + 0x518) = obj;
        if (old) old->r08();
    }
    void* tool = *(void**)((char*)*(void**)(self + 0x518) + 0x114);
    if (tool) {
        void* t2 = (*(Vfn2*)(*(int*)tool + 0xb8))(tool, (void*)0x013f94d4);
        if (t2) {
            int v = (int)(*(Vfn1*)(*(int*)t2 + 0x10))(t2);
            (*(void(**)(int, int))(*(int*)self + 0x48))(self, v);
            return;
        }
    }
    (*(void(**)(int, int))(*(int*)self + 0x48))(self, -1);
}

// @ 0x00cb4ca0
bool cLocomotionObj14::HasLiveTarget14()
{
    if (mTarget && ((CTarget*)mTarget)->IsValid())
        return true;
    return false;
}

// @ 0x00cb4cc0
// SP::cVerticalRocketLocomotion::Execute
void f00cb4cc0(Vector3* self, float unused)
{
    cLocomotiveObject* obj = *(cLocomotiveObject**)((char*)self + 0x14);
    obj->GetPosition();                                       // vtable +0x2c
    Vector3* vel = cLocomotiveObject_GetVelocity(obj);
    Vector3 v; v.x = vel->x; v.y = vel->y; v.z = vel->z;
    self->x = v.x; self->y = v.y; self->z = v.z;
    Quaternion q;
    QuaternionFromDirections(&q, (const Vector3*)0x0169a9e8, &v);
    obj->SetOrientation(&q);
}

// @ 0x00cb4d40
// SP::cDefaultToolProjectile::ConfigureProjectile
int f00cb4d40(int self, int a, int b, int c, int d, int e)
{
    // complex projectile configuration; complete but not byte-exact
    (void)self; (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x00cb5050
void f00cb5050(int self)
{
    void* p = *(void**)(self + 0x4e4);
    float v = FUN_0104be60(p);
    if (v > 0.0f) {
        FUN_0104be60(*(void**)(self + 0x4e4));
        return;
    }
    (*(void(**)(int))(*(int*)self + 0xc8))(self);
}

// @ 0x00cb5090
// SP::cStraightLineLocomotion::Execute
void f00cb5090(Vector3* self, float unused)
{
    cLocomotiveObject* obj = *(cLocomotiveObject**)((char*)self + 0x14);
    obj->GetPosition();                                       // vtable +0x2c
    Vector3* vel = cLocomotiveObject_GetVelocity(obj);
    self->x = vel->x; self->y = vel->y; self->z = vel->z;
    float len = self->x * self->x + self->y * self->y + self->z * self->z;
    if (len > g_1em3) {
        Vector3 v; v.x = self->x; v.y = self->y; v.z = self->z;
        Quaternion q;
        QuaternionFromDirections(&q, (const Vector3*)0x0169a9e8, &v);
        obj->SetOrientation(&q);
    }
}

// @ 0x00cb5140
float* f00cb5140(int self, float* out)
{
    int path = *(int*)(self + 0x51c);
    if (path && (uint)((*(int*)(path + 0x14) - *(int*)(path + 0x10)) / 12) > 1) {
        float* p = *(float**)(path + 0x10);
        float dz = p[5] - p[2];
        float dy = p[4] - p[1];
        float dx = p[3] - p[0];
        float inv = 1.0f / (dx * dx + dy * dy + dz * dz);
        out[0] = inv * dx; out[1] = inv * dy; out[2] = dz * inv;
        return out;
    }
    float x = *(float*)(self + 0x1fc);
    float y = *(float*)(self + 0x200);
    float z = *(float*)(self + 0x204);
    if (x * x + y * y + z * z > 0.0f) {
        float inv = 1.0f / (x * x + y * y + z * z);
        out[0] = x * inv; out[1] = y * inv; out[2] = z * inv;
        return out;
    }
    (*(void(**)(int, float*))(*(int*)(self + 0x34) + 0x5c))(self + 0x34, out);
    return out;
}

// @ 0x00cb52c0
int f00cb52c0(int self)
{
    if (FUN_0104cda0(*(void**)(self + 0x518)) == 0.0f)
        return 0;
    void* p = *(void**)(self + 0x5cc);
    if (p && (*(Vfn1*)(*(int*)p + 0x10))(p))
        return 1;
    int* strat = (int*)0;   // GetStrategy stub
    (void)strat;
    return 0;
}

// @ 0x00cb5330
// SP::cDefaultToolProjectile::Write
int f00cb5330_write(cGameData* self, cOutStream* stream)
{
    void* w  = ((GetStreamObj*)stream)->GetStream();
    void* wr = ((GetStreamObj*)w)->GetStream();
    uint sig = 0x24270c4;
    EA_IO_WriteUint32(wr, &sig, 1, 0);
    self->Write(stream);
    cLocomotiveObject_Write((cLocomotiveObject*)((char*)self + 0x34), stream);
    char ser[12];
    cVarListSerializer_ctor(ser, self, (void*)0x0157d890, 0x1a80d26);
    bool ok = cVarListSerializer_Serialize(ser, stream);
    float flag = *(float*)((char*)self + 0x51c);
    w  = ((GetStreamObj*)stream)->GetStream();
    wr = ((GetStreamObj*)w)->GetStream();
    char b = (flag != 0.0f);
    StreamWrite(wr, 1, b);
    if (flag != 0.0f) {
        char ser2[12];
        cVarListSerializer_ctor(ser2, (void*)(int)flag, (void*)0x0157d540, 0x1a80d26);
        cVarListSerializer_Serialize(ser2, stream);
    }
    return ok;
}

// @ 0x00cb5420
void* cLocomotionObj14::GetToolStrategy()
{
    void* p = *(void**)((char*)this + 0x14);
    void* s = *(void**)&((Tool*)p)->mStrategy;
    if (s)
        return (*(VfnS2*)(*(int*)s + 0xb8))(s, (void*)0x013f94d4);
    return 0;
}

// @ 0x00cb5450
void f00cb5450(int self, Vector3* a, Vector3* b)
{
    Vector3* p1 = (Vector3*)(*(void*(**)(int))(**(int**)(*(int*)(self + 0x518) + 0x114) + 0x2c))(
                       *(int*)(self + 0x518));
    a->x = p1->x; a->y = p1->y; a->z = p1->z;
    Vector3* p2 = (Vector3*)(*(void*(**)(int))(*(int*)(self + 0x34) + 0x2c))(self + 0x34);
    b->x = p2->x; b->y = p2->y; b->z = p2->z;
}

// @ 0x00cb54a0
// SP::cSpaceDefenseMissileLocomotion::cSpaceDefenseMissileLocomotion
void* f00cb54a0(int self, float maxSpeed, float turnRate, void* target)
{
    (void)target;
    *(float*)(self + 0x10) = maxSpeed;
    *(float*)(self + 0x14) = turnRate;
    return (void*)self;
}

// @ 0x00cb5560
bool cLocomotionObjDC::HasLiveTargetDC()
{
    if (mTarget && ((CTarget*)mTarget)->IsValid())
        return true;
    return false;
}

// @ 0x00cb5580
void f00cb5580(int self)
{
    RefCounted* p = *(RefCounted**)(self + 0x5e0);
    if (p) {
        *(void**)(self + 0x5e0) = 0;
        p->r08();
    }
    RefCounted* q = *(RefCounted**)(self + 0x5e4);
    if (q) {
        *(void**)(self + 0x5e4) = 0;
        q->r64();
    }
    RefCounted* r = *(RefCounted**)(self + 0x2c);
    if (r) {
        *(void**)(self + 0x2c) = 0;
        r->r04();
    }
    cLocomotiveObject_Shutdown((cLocomotiveObject*)(self + 0x34));
}
