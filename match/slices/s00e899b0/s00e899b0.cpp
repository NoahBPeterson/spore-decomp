// Slice s00e899b0 -- Simulator/city view classes: sound-loop view update, city-walls
// deleting destructor, turret/building/cultural-target allocation helpers and the
// cultural-target sound map maintenance.
//
// The retail cSpatialObjectView base is 0x34 bytes (its constructor 0x00e92af0 stops at
// +0x32); every derived field therefore sits at +0x34 and above.  The eastl hash_map
// member of cCulturalTargetView at +0x34 is laid out as {u32, bucket array, bucket count,
// element count}.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)
#pragma warning(disable : 4244)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;

struct Float3 {
    float x, y, z;
    Float3() {}
    Float3(float a, float b, float c) : x(a), y(b), z(c) {}
};

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);
};

// ---------------------------------------------------------------------------------------------
// retail globals
// ---------------------------------------------------------------------------------------------
extern float   g_1485720;        // 0x01485720  1.0f
extern float   g_1470f1c;        // 0x01470f1c  0.4f
extern float   g_1486344;        // 0x01486344  -12.0f (effect offset scale)
extern float   g_13eb95c;        // 0x013eb95c   3.0f
extern float   g_14861d0;        // 0x014861d0   1.5258789e-05f (axis epsilon)
extern u32     g_bucketSentinel; // 0x0154df28  static empty bucket array
extern Matrix3 g_mtx_16c4b98;    // 0x016c4b98  default orientation
extern float   g_f_16c4bbc;      // 0x016c4bbc  unit vector x
extern float   g_f_16c4bc0;      // 0x016c4bc0  unit vector y
extern float   g_f_16c4bc4;      // 0x016c4bc4  unit vector z

extern void* vtbl_citywalls[];   // 0x01486290
extern void* vtbl_turret[];      // 0x014608ec
extern void* vtbl_cultural[];    // 0x01486310

void* operator new(unsigned int, const char*, int, int, int, int);
void  operator delete(void*);
void  operator delete[](void*);

extern void*         EffectsManagerPtr();     // 0x0067ddd0
extern void*         GetSystemAT();           // 0x00a206f0
extern void          Start3dSoundByName(u32, u32, float, float, float);  // 0x00571f80
extern void          FUN_00572020(u32, u8);   // 0x00572020  audio effect dispatch thunk

// ---------------------------------------------------------------------------------------------
// virtual interface used by the objects reached through the retail vtables
// ---------------------------------------------------------------------------------------------
struct IObj {
    virtual void   v00();
    virtual void   v04();
    virtual void   v08(u32);
    virtual void   v0C();
    virtual void   v10(u32);
    virtual void   v14();
    virtual void   v18(void*);
    virtual void   v1C();
    virtual u32    v20();
    virtual void   v24(u32);
    virtual void   v28();
    virtual void   v2C(u32, u32, void*);
    virtual void   v30();
    virtual void   v34();
    virtual void   v38();
    virtual void   v3C();
    virtual void   v40();
    virtual void   v44();
    virtual void   v48();
    virtual void   v4C();
    virtual void   v50();
    virtual void   v54();
    virtual float* v58();
    virtual int    v5C();
    virtual void   v60();
    virtual void   v64();
    virtual void   v68();
    virtual void   v6C();
    virtual void   v70();
    virtual void   v74();
    virtual void   v78();
    virtual void   v7C();
    virtual void   v80();
    virtual void   v84();
    virtual void   v88();
    virtual void   v8C();
    virtual void   v90();
    virtual void   v94();
    virtual void   v98();
    virtual void   v9C();
    virtual void   vA0();
    virtual void   vA4();
    virtual void   vA8();
    virtual void   vAC();
    virtual void   vB0();
    virtual void   vB4();
    virtual void*  vB8(u32);
};

// ---------------------------------------------------------------------------------------------
// interfaces used by cCulturalTargetView::HandleSimulationUpdate
// ---------------------------------------------------------------------------------------------
struct ITarget {                    // the object stored in cSpatialObjectView::mpObject
    virtual void   a00(); virtual void a04(); virtual void a08(); virtual void a0C();
    virtual void   a10(); virtual void a14(); virtual void a18(); virtual void a1C();
    virtual void   a20(); virtual void a24(); virtual void a28(); virtual void a2C();
    virtual void*  a30(); virtual void a34(); virtual void a38(); virtual void a3C();
    virtual void   a40(); virtual void a44(); virtual void a48(); virtual void a4C();
    virtual void   a50(); virtual void a54(); virtual void a58(); virtual void a5C();
    virtual void   a60(); virtual void a64(); virtual void a68(); virtual void a6C();
    virtual void   a70(); virtual void a74(); virtual void a78(); virtual void a7C();
    virtual void   a80(); virtual void a84(); virtual void a88(); virtual void a8C();
    virtual void   a90(); virtual void a94(); virtual void a98(); virtual void a9C();
    virtual void   aA0(); virtual void aA4(); virtual void aA8(); virtual void aAC();
    virtual void   aB0(); virtual void aB4(); virtual void* aB8(u32);
};

struct IEmb {                       // embedded object at ITarget + 0x100
    virtual void   e00(); virtual void e04(); virtual void e08(); virtual void e0C();
    virtual void   e10(); virtual void e14(); virtual void e18(); virtual void e1C();
    virtual void   e20(); virtual void e24(); virtual void e28(); virtual Float3* e2C();
    virtual void   e30(); virtual void e34(); virtual void e38(); virtual void e3C();
    virtual void   e40(); virtual void e44(); virtual void e48(); virtual void e4C();
    virtual void   e50(); virtual void e54(); virtual void e58(); virtual Float3* e5C(Float3* out);
};

struct IObj0C {                     // object with a v0C(u32) accessor
    virtual void  x00(); virtual void x04(); virtual void x08(); virtual void* x0C(u32);
};

struct IEffect {                    // reference-counted visual effect handle
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0C();
    virtual void b10(); virtual void b14(); virtual void b18(void* msg);
    virtual void b1C(); virtual void b20(); virtual void b24(); virtual void b28();
    virtual void b2C(u32); virtual void b30(u32);
};

struct IP70 {                       // vehicle-ish object reached through cCrowdObj::mp70
    virtual void   p00(); virtual void p04(); virtual void p08(); virtual void p0C();
    virtual void   p10(); virtual void p14(); virtual void p18(); virtual void p1C();
    virtual void   p20(); virtual void p24(); virtual void p28(); virtual Float3* p2C();
    virtual void   p30(); virtual void p34(); virtual void p38(); virtual void p3C();
    virtual void   p40(); virtual void p44(); virtual void p48(); virtual void p4C();
    virtual void   p50(); virtual void p54(); virtual void p58(); virtual void p5C();
    virtual void   p60(); virtual void p64(); virtual void p68(); virtual void p6C();
    virtual void   p70(); virtual void p74(); virtual void p78(); virtual void p7C();
    virtual void   p80(); virtual void p84(); virtual void p88(); virtual void p8C();
    virtual void   p90(); virtual void p94(); virtual void p98(); virtual void p9C();
    virtual void   pA0(); virtual void pA4(); virtual void pA8(); virtual void pAC();
    virtual void   pB0(); virtual void pB4(); virtual void* pB8(u32);
};

// object returned by IP70::pB8 -- vehicle class word at +0xb1c (1 and 2 pick effect ids)
struct VehicleLike {
    u8  pad00[0xb1c];
    int m1c;                                        // +0xb1c
};

// world / simulation object owning the effect lookup helpers
class CWorld {
public:
    void* Get(u32 id);                              // 0x00c888e0
    void  Create(u32 a, u32 b, u32 c);              // 0x00c8b130
    void  Remove(u32 a, u32 b);                     // 0x00c8ad30
    void  Measure(float* outF, int* outN);          // 0x00bd85c0
};

class CCrowdMaker {
public:
    void* Make(u32 flag);                           // 0x00bd9e80
    u8    pad04[0x192 - 0x04];
    u8    m192;                                     // +0x192
};

class cCrowdObj {
public:
    u8     pad00[0x70];
    IP70*  m70;                                     // +0x70
    u8     m74;                                     // +0x74
};

class cVehicle {
public:
    void ContinueAngryCrowdAttack(u32 v);           // 0x00ca8120
};

class cPlanetModel {
public:
    void* BuildSurfaceOrientation2();               // 0x00b7f250
};

void* __stdcall PlanetModel(Float3* a, Float3* b, Float3* c);      // 0x00b3d350
Matrix3* __cdecl Matrix3FromQuaternion(Matrix3* dst, void* q);      // 0x0059c190
void __cdecl RecordEvent4(u32 a, u32 b, float c, u32 d);            // 0x00435f40
extern "C" double fabs(double);
extern "C" double ceil(double);

// ---------------------------------------------------------------------------------------------
// eastl hash_map used for the cultural-target sound table (at cCulturalTargetView + 0x34)
// ---------------------------------------------------------------------------------------------
struct MapIter { void* mpNode; void* mpBucket; };

struct SoundMap {
    u32     m00;              // +0x00
    void**  mpBucketArray;    // +0x04
    u32     mnBucketCount;    // +0x08
    u32     mnElementCount;   // +0x0c

    MapIter find(const u32& key);       // 0x00645ed0
    u32*    lookup(const u32& key);     // 0x00ad3da0
    MapIter erase(MapIter it);          // 0x01068380
    void    DoFreeNodes(void* p, u32 n);
};

// ---------------------------------------------------------------------------------------------
// message passed to a visual effect (0x38 bytes, built on the stack)
// ---------------------------------------------------------------------------------------------
struct XformMsg {
    u16    mFlags;      // +0x00
    u16    mRefs;       // +0x02
    Float3 mPos;        // +0x04
    float  mScale;      // +0x10
    Matrix3 mRot;       // +0x14

    XformMsg();                                     // 0x00434040
    __forceinline XformMsg(const Matrix3& rot)
        : mFlags(0), mRefs(0), mPos(g_f_16c4bbc, g_f_16c4bc0, g_f_16c4bc4), mScale(g_1485720), mRot(rot) {
    }                                               // inlined rotation flavour
};

namespace SP {

struct EAutoRef {
    void* mp;                       // +0x00
    void* AsPPTypeParam();          // 0x00a16f40
};

// ---------------------------------------------------------------------------------------------
// SP::cCitySoundLoopView
// ---------------------------------------------------------------------------------------------
class cCitySoundLoopView {
public:
    void**   mpVtbl;                // +0x00
    u8       pad04[0x0c - 0x04];
    void*    mpObject;              // +0x0c
    u8       pad10[0x34 - 0x10];
    EAutoRef mEffectRef;            // +0x34
    u8       pad38[0x44 - 0x38];

    void HandleSimulationUpdate(u32 a, u32 b);   // 0x00e899b0
};

// ---------------------------------------------------------------------------------------------
// SP::cCityWallsView
// ---------------------------------------------------------------------------------------------
class cCityWallsView {
public:
    void** mpVtbl;                  // +0x00
    u8     pad04[0x34 - 0x04];
    void*  mEffect;                 // +0x34

    cCityWallsView* scalar_deleting_destructor(u8 f);   // 0x00e89c20
    void BaseDtor();
};

// ---------------------------------------------------------------------------------------------
// turret view (allocated by FUN_00e89c60)
// ---------------------------------------------------------------------------------------------
class cTurretView {
public:
    void** mpVtbl;                  // +0x00
    u8     pad04[0x34 - 0x04];
    float  m34;                     // +0x34
    float  m38;                     // +0x38
    float  m3c;                     // +0x3c
    float  m40;                     // +0x40
    u32    m44;                     // +0x44
    void*  m48;                     // +0x48
    void*  m4c;                     // +0x4c

    cTurretView();                  // inlined at the allocation site
    void   BaseCtor();              // 0x00e92af0 cSpatialObjectView
};

// object owning DestroyAllEffects (0x00c8b0a0)
class CSpatialObject {
public:
    void DestroyAllEffects(u32 flag);
};

// ---------------------------------------------------------------------------------------------
// building view (allocated by FUN_00e89d10)
// ---------------------------------------------------------------------------------------------
class cBuildingView {
public:
    void** mpVtbl;                  // +0x00
    u8     pad04[0x88 - 0x04];

    cBuildingView();                // 0x00e87b70
    void init(u32 param);           // 0x00e88e10
};

// ---------------------------------------------------------------------------------------------
// SP::cCulturalTargetView
// ---------------------------------------------------------------------------------------------
class cCulturalTargetView {
public:
    void**   mpVtbl;                // +0x00
    u8       pad04[0x0c - 0x04];
    void*    mpObject;              // +0x0c
    u8       pad10[0x34 - 0x10];
    SoundMap mSoundMap;             // +0x34
    float    m44;                   // +0x44
    float    m48;                   // +0x48
    u32      m4c;                   // +0x4c
    u8       pad50[0x54 - 0x50];

    cCulturalTargetView();                          // 0x00e89d60
    ~cCulturalTargetView();                         // 0x00e89f20
    u32  FUN_00e89e50(u32 id, u32 key, Float3* p);  // 0x00e89e50
    void FUN_00e89eb0(u32 key, u8 val);             // 0x00e89eb0
    void HandleSimulationUpdate(u32 a, u32 b);      // 0x00e89f80
    void BaseCtor();
    void BaseDtor();
    void BaseUpdate(u32 a, u32 b);                  // 0x00e92ca0
};

// simulation object layout used by cCulturalTargetView::HandleSimulationUpdate
struct cSimTargetData {
    u8     pad000[0x100];
    IEmb   mEmb;                                    // +0x100
    u8     pad104[0x1d4 - 0x104];
    u8     m1d4;                                    // +0x1d4
    u8     pad1d5[0x1d8 - 0x1d5];
    int    m1d8;                                    // +0x1d8
    u8     pad1dc[0x20c - 0x1dc];
    float  m20c;                                    // +0x20c
    float  m210;                                    // +0x210
    int    m214;                                    // +0x214
};

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// SP::cCitySoundLoopView::HandleSimulationUpdate
// ---------------------------------------------------------------------------------------------
// @ 0x00e899b0 SP::cCitySoundLoopView::HandleSimulationUpdate
void SP::cCitySoundLoopView::HandleSimulationUpdate(u32, u32) {
    void* obj = mpObject;
    if (obj == 0)
        return;

    IObj* fx = (IObj*)((IObj*)obj)->vB8(0x903c3ea3);
    if (fx == 0)
        return;

    fx->v00();

    EAutoRef* ref = &mEffectRef;
    if (ref->mp == 0) {
        switch (fx->v5C()) {
        case 1:
            ((IObj*)EffectsManagerPtr())->v2C(0xf78fa47a, 0, ref->AsPPTypeParam());
            break;
        case 2:
            ((IObj*)EffectsManagerPtr())->v2C(0xced4a9a6, 0, ref->AsPPTypeParam());
            break;
        case 3:
            ((IObj*)EffectsManagerPtr())->v2C(0xf1910322, 0, ref->AsPPTypeParam());
            break;
        case 4:
            ((IObj*)EffectsManagerPtr())->v2C(0xbd61f72b, 0, ref->AsPPTypeParam());
            break;
        case 5:
            ((IObj*)EffectsManagerPtr())->v2C(0xef2700b6, 0, ref->AsPPTypeParam());
            break;
        case 6:
            ((IObj*)EffectsManagerPtr())->v2C(0x62019f3a, 0, ref->AsPPTypeParam());
            break;
        case 7:
            ((IObj*)EffectsManagerPtr())->v2C(0x60d7cad6, 0, ref->AsPPTypeParam());
            break;
        }

        if (ref->mp != 0) {
            XformMsg msg;
            msg.mPos = *(Float3*)fx->v58();
            msg.mFlags |= 4;
            msg.mRefs++;
            ((IObj*)ref->mp)->v18(&msg);
            ((IObj*)ref->mp)->v08(0);
        }
    } else {
        XformMsg msg(g_mtx_16c4b98);
        msg.mPos = *(Float3*)fx->v58();
        msg.mFlags |= 4;
        msg.mRefs++;
        ((IObj*)ref->mp)->v18(&msg);
    }

    fx->v04();
}

// @ 0x00e89c20 SP::cCityWallsView::scalar_deleting_destructor
SP::cCityWallsView* SP::cCityWallsView::scalar_deleting_destructor(u8 f) {
    mpVtbl = vtbl_citywalls;
    if (mEffect != 0)
        ((IObj*)mEffect)->v04();
    BaseDtor();
    if (f & 1)
        operator delete(this);
    return this;
}

// @ 0x00e89c60 FUN_00e89c60
SP::cTurretView* __stdcall FUN_00e89c60(u32 param) {
    SP::cTurretView* v = new ("Simulator/cTurretView", 0, 0, 0, 0) SP::cTurretView();
    ((IObj*)v)->v24(param);
    v->m44 = 0;
    v->m34 = 0.0f;
    v->m38 = 0.0f;
    v->m3c = 0.0f;
    v->m40 = g_1485720;
    if (v->m48 != 0) {
        void* o = v->m48;
        v->m48 = 0;
        ((IObj*)o)->v04();
    }
    if (v->m4c != 0) {
        void* o = v->m4c;
        v->m4c = 0;
        ((IObj*)o)->v04();
    }
    return v;
}

// @ 0x00e89d10 FUN_00e89d10
SP::cBuildingView* __stdcall FUN_00e89d10(u32 param) {
    SP::cBuildingView* v = new ("Simulator/cBuildingView", 0, 0, 0, 0) SP::cBuildingView();
    v->init(param);
    return v;
}

// @ 0x00e89d60 SP::cCulturalTargetView::cCulturalTargetView
SP::cCulturalTargetView::cCulturalTargetView() {
    BaseCtor();
    m44 = g_1485720;
    mpVtbl = vtbl_cultural;
    m48 = g_1470f1c;
    u32 zero = 0;
    mSoundMap.mnElementCount = zero;
    m4c = zero;
    mSoundMap.mnBucketCount = 1;
    mSoundMap.mpBucketArray = (void**)&g_bucketSentinel;
}

// @ 0x00e89db0 FUN_00e89db0
SP::cCulturalTargetView* __stdcall FUN_00e89db0(u32 param) {
    SP::cCulturalTargetView* v = new ("Simulator/cCulturalTargetView", 0, 0, 0, 0) SP::cCulturalTargetView();
    ((IObj*)v)->v24(param);
    return v;
}

// @ 0x00e89e50 FUN_00e89e50
u32 SP::cCulturalTargetView::FUN_00e89e50(u32 id, u32 key, Float3* p) {
    IObj* sys = (IObj*)GetSystemAT();
    u32 snd;
    if (sys != 0)
        snd = sys->v20();
    else
        snd = 0;
    *mSoundMap.lookup(key) = snd;
    Start3dSoundByName(id, snd, p->x, p->y, p->z);
    return snd;
}

// @ 0x00e89eb0 FUN_00e89eb0
void SP::cCulturalTargetView::FUN_00e89eb0(u32 key, u8 val) {
    SoundMap* map = &mSoundMap;
    MapIter it = map->find(key);
    if (it.mpNode != map->mpBucketArray[map->mnBucketCount]) {
        u32* slot = map->lookup(key);
        FUN_00572020(*slot, val);
        it = map->erase(it);
    }
}

// @ 0x00e89f20 SP::cCulturalTargetView::~cCulturalTargetView
SP::cCulturalTargetView::~cCulturalTargetView() {
    mpVtbl = vtbl_cultural;
    ((CSpatialObject*)mpObject)->DestroyAllEffects(1);
    FUN_00e89eb0(0x3f69195, 1);
    SoundMap* map = &mSoundMap;
    map->DoFreeNodes(map->mpBucketArray, map->mnBucketCount);
    map->mnElementCount = 0;
    if (map->mnBucketCount > 1)
        operator delete[](map->mpBucketArray);
    BaseDtor();
}

// ---------------------------------------------------------------------------------------------
// turret view constructor (inlined at FUN_00e89c60)
// ---------------------------------------------------------------------------------------------
SP::cTurretView::cTurretView() {
    BaseCtor();
    mpVtbl = vtbl_turret;
    m48 = 0;
    m4c = 0;
}

// ---------------------------------------------------------------------------------------------
// SP::cCulturalTargetView::HandleSimulationUpdate
// ---------------------------------------------------------------------------------------------
// @ 0x00e89f80 SP::cCulturalTargetView::HandleSimulationUpdate
void SP::cCulturalTargetView::HandleSimulationUpdate(u32 a, u32 b) {
    void* obj = mpObject;
    ITarget* target = 0;
    if (obj != 0)
        target = (ITarget*)((IObj*)obj)->vB8(0x3d5c477);

    BaseUpdate(a, b);
    ((CWorld*)obj)->Get(0x3df43f4);
    ((CWorld*)obj)->Get(0x3df43f5);

    cSimTargetData* td = (cSimTargetData*)target;
    int flag = 2;
    if (td->m1d8 == 2) {
        if (fabs((double)td->m20c) < (double)g_14861d0) {
            flag = !(fabs((double)td->m20c) > fabs((double)td->m210));
            target->a4C();
        }

        MapIter it = mSoundMap.find(0x3f69195);
        if (it.mpNode == mSoundMap.mpBucketArray[mSoundMap.mnBucketCount]) {
            Float3* p = td->mEmb.e2C();
            FUN_00e89e50(0x2873c7ee, 0x3f69195, p);
        }

        it = mSoundMap.find(0x3f69195);
        if (it.mpNode != mSoundMap.mpBucketArray[mSoundMap.mnBucketCount]) {
            float fv = 0.0f;
            int   n = 0;
            ((CWorld*)obj)->Measure(&fv, &n);
            float v;
            if (n > 0)
                v = (float)ceil((double)((fv * 3.0f) / (float)n));
            else
                v = 1.0f;
            if (v < 1.0f)
                v = 1.0f;
            if (v > 3.0f)
                v = 3.0f;
            float dmg = (flag == 2) ? 1.0f : g_1470f1c;
            u32 key = 0x3f69195;
            RecordEvent4(*mSoundMap.lookup(key), 0x187ffedd, v, 0);
            RecordEvent4(*mSoundMap.lookup(key), 0xffb10599, dmg, 0);
        }
    } else {
        FUN_00e89eb0(0x3f69195, 0);
    }

    u32 b1d4 = td->m1d4;
    void* w = target->a30();
    void* w2 = (w != 0) ? ((IObj0C*)w)->x0C(0xee9b2232) : 0;
    cCrowdObj* crowd = (cCrowdObj*)((CCrowdMaker*)w2)->Make(b1d4);
    IP70* p70 = crowd->m70;
    void* veh = (p70 != 0) ? p70->pB8(0x137e8e0) : 0;
    u8 proceed = crowd->m74;
    bool active = (td->m214 > 0) && (p70 != 0);

    void* eff = ((CWorld*)obj)->Get(0x4af5ae2);
    if (!active) {
        if (eff != 0)
            ((CWorld*)obj)->Remove(0x4af5ae2, 1);
        return;
    }
    if (eff == 0) {
        u32 id = 0x251bc7a8;
        int t = ((VehicleLike*)veh)->m1c;
        if (t == 1)
            id = 0xa1185324;
        else if (t == 2)
            id = 0xa8eb404d;
        ((CWorld*)obj)->Create(id, 0, 0x4af5ae2);
        eff = ((CWorld*)obj)->Get(0x4af5ae2);
        if (eff == 0)
            return;
        proceed = 1;
    }

    void* w3 = target->a30();
    void* w4 = (w3 != 0) ? ((IObj0C*)w3)->x0C(0xee9b2232) : 0;
    u32 on = (((CCrowdMaker*)w4)->m192 != 0) ? 1 : 0;
    ((IEffect*)eff)->b2C(on);
    ((IEffect*)eff)->b30(on);

    if (proceed == 0)
        return;

    ((cVehicle*)veh)->ContinueAngryCrowdAttack(1);

    Float3* pa = p70->p2C();
    Float3 dir;
    td->mEmb.e5C(&dir);
    float ox = dir.x * g_1486344;
    float oy = dir.y * g_1486344;
    float oz = dir.z * g_1486344;
    Float3* pb = td->mEmb.e2C();
    Float3 pos(pb->x + ox, pb->y + oy, pb->z + oz);

    XformMsg msg(g_mtx_16c4b98);
    msg.mFlags |= 4;
    msg.mPos = pos;
    msg.mRefs++;

    Float3 d(pa->x - pos.x, pa->y - pos.y, pa->z - pos.z);
    cPlanetModel* pm = (cPlanetModel*)PlanetModel(&dir, &pos, &d);
    void* quat = pm->BuildSurfaceOrientation2();
    Matrix3 mtx;
    Matrix3FromQuaternion(&mtx, quat);
    msg.mRot = mtx;
    msg.mFlags |= 2;
    msg.mRefs++;
    ((IEffect*)eff)->b18(&msg);
}
