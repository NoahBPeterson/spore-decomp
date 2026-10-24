// slice s00ca3030 - 0x00ca3770: find the point on the planet surface nearest to the camera that lies on
// a ring of directions around a ray (spiral search outward in 16-unit radius steps).
// Also holds six Simulator::cGameData methods: 0x00ca3030, 0x00ca31f0, 0x00ca3350,
// 0x00ca33b0, 0x00ca3410 and 0x00ca3660.
// Compile with /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include <math.h>
#include <float.h>
#include "types.h"

struct Vector3 {
    float x, y, z;
};
struct Quaternion { float x, y, z, w; };

#pragma intrinsic(sin, cos, sqrt)

extern Vector3 gNoPoint;     // 0x01699b08: the "no result" vector
extern float gTwoPi;         // 0x0169a280
extern const float gMinSearchStep;  // 0x014763b0 (16.0)

namespace SP {
class cPlanetModel {
public:
    int GetContinent(const Vector3* p);           // 0x00b88590 (thiscall)
    float GetRadius();                            // 0x00b7e4d0 (thiscall, returns float in st0)
    uint32_t GetTerrainFlags(const Vector3* p);   // 0x00b7e840 (thiscall, ret 4)
    void Project(Vector3* out, const Vector3* in);   // 0x00b81630 (thiscall, ret 8)
};
cPlanetModel* PlanetModel();                      // 0x00b3d350 (cdecl)
}
using SP::cPlanetModel;

Vector3 __cdecl QuatRotate(const Vector3& v, const Quaternion& q);   // 0x0059aed0 (sret first)

struct ICamera {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10();
    virtual const Vector3* GetPosition();     // +0x2c
};

static inline float InvLength(float x, float y, float z) {
    return 1.0f / (float)sqrt(x * x + (y * y + z * z) + 1e-8f);
}

class cSurfaceSearcher {
public:
    char pad0[0x34];
    ICamera mCamera;              // +0x34 (embedded interface subobject)
    char pad38[0xb1c - 0x38];
    int mMode;                    // +0xb1c
    Vector3* FindNearestSurfacePoint(Vector3* out, const Vector3* dir, float dist);   // 0x00ca3770
};

Vector3* cSurfaceSearcher::FindNearestSurfacePoint(Vector3* out, const Vector3* dir, float dist) {
    cPlanetModel* pm = SP::PlanetModel();
    if (!pm || (dir->x == gNoPoint.x && dir->y == gNoPoint.y && dir->z == gNoPoint.z)) {
        out->x = gNoPoint.x;
        out->y = gNoPoint.y;
        out->z = gNoPoint.z;
        return out;
    }
    const Vector3* c = mCamera.GetPosition();
    Vector3 cam;
    cam.x = c->x; cam.y = c->y; cam.z = c->z;

    const float* pr = &gMinSearchStep;
    if (!(gMinSearchStep > dist)) pr = &dist;
    float radius = *pr;
    const int continent = pm->GetContinent(&cam);
    const float planetRadius = pm->GetRadius();
    const float invR = 1.0f / planetRadius;
    float angle = invR * radius;

    float dx = dir->x, dy = dir->y, dz = dir->z;
    float sd = InvLength(dx, dy, dz);
    float sc = InvLength(cam.x, cam.y, cam.z);
    float ax = (cam.y * sc) * (dz * sd) - (cam.z * sc) * (dy * sd);
    float ay = (cam.z * sc) * (dx * sd) - (dz * sd) * (sc * cam.x);
    float az = (dy * sd) * (sc * cam.x) - (cam.y * sc) * (dx * sd);
    float sa = InvLength(ax, ay, az);
    Vector3 axis;
    axis.y = ay * sa;
    axis.z = az * sa;
    axis.x = sa * ax;

    Vector3 best = gNoPoint;
    float bestDist = FLT_MAX;
    while (angle < gTwoPi) {
        Vector3 start = *dir;
        float s = (float)sin(angle * 0.5f);
        float co = (float)cos(angle * 0.5f);
        Quaternion q;
        q.x = s * axis.x;
        q.y = axis.y * s;
        q.z = axis.z * s;
        q.w = co;
        Vector3 pt = QuatRotate(start, q);

        int n = (int)(gTwoPi * radius * 0.0625f);
        float step = gTwoPi / (float)n;
        float t = 0.0f;
        float rx = dir->x, ry = dir->y, rz = dir->z;
        float sr = InvLength(rx, ry, rz);
        float ux = sr * rx, uy = sr * ry, uz = sr * rz;
        for (int i = n; i > 0; --i) {
            float sn = (float)sin(t * 0.5f);
            float cs = (float)cos(t * 0.5f);
            float qz = uz * sn;
            float qy = uy * sn;
            float qx = sn * ux;
            float yy = qy * qy;
            float zy = qz * qy;
            float yx = qy * qx;
            float wy = cs * qy;
            Vector3 r;
            r.x = ((wy + qz * qx) * pt.z + (yx - cs * qz) * pt.y) * 2.0f + (1.0f - (qz * qz + yy) * 2.0f) * pt.x;
            r.y = ((cs * qz + yx) * pt.x + (zy - cs * qx) * pt.z) * 2.0f + (1.0f - (qz * qz + qx * qx) * 2.0f) * pt.y;
            r.z = ((qz * qx - wy) * pt.x + (cs * qx + zy) * pt.y) * 2.0f + (1.0f - (qx * qx + yy) * 2.0f) * pt.z;
            if (pm->GetContinent(&r) == continent) {
                int mode = mMode;
                cPlanetModel* pm2 = SP::PlanetModel();
                bool ok;
                if (mode == 0) {
                    ok = (pm2->GetTerrainFlags(&r) & 0x98000000) == 0;
                } else if (mode == 1) {
                    ok = (pm2->GetTerrainFlags(&r) & 0x58000000) == 0;
                } else if (mode == 2) {
                    ok = (~(pm2->GetTerrainFlags(&r) >> 29) & 1) != 0;
                } else {
                    ok = true;
                }
                if (ok) {
                    float ey = r.y - cam.y;
                    float ex = r.x - cam.x;
                    float ez = r.z - cam.z;
                    float d = ez * ez + ey * ey + ex * ex;
                    if (bestDist > d) {
                        best = r;
                        bestDist = d;
                    }
                }
            }
            t += step;
        }
        if (best.x != gNoPoint.x || best.y != gNoPoint.y || best.z != gNoPoint.z) {
            pm->Project(out, &best);
            return out;
        }
        radius += gMinSearchStep;
        angle = invR * radius;
    }
    out->x = gNoPoint.x;
    out->y = gNoPoint.y;
    out->z = gNoPoint.z;
    return out;
}

// ===========================================================================
// Simulator::cGameData family (0x00ca3030 .. 0x00ca3660).
//
// 0x00ca3030  is entered with ecx = cGameData + 0x508 (the embedded sub-object)
//             and recovers the base through the negative offsets -0x508/-0x438/
//             -0x4d4; it is modelled as a cGameDataSub method.
// 0x00ca31f0, 0x00ca3350, 0x00ca33b0 and 0x00ca3660 use ecx = cGameData.
// 0x00ca3410  uses ecx = cGameData + 0x34 and recovers the base as this - 0x34.
// ===========================================================================

// The +0x34 spatial sub-object (a cSpatialObject; only the slots we call are
// named, with filler slots keeping the retail vtable offsets: +0x2c, +0x34,
// +0x48, +0x50, +0x74 and +0xac).
struct cSpatialObject {
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10();
    virtual const Vector3* GetPosition();       // +0x2c  (slot 11)
    virtual void s12();                         // +0x30
    virtual float GetScale();                   // +0x34  (slot 13, returns float in st0)
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual bool GetFlag48();                   // +0x48  (slot 18)
    virtual void s19();                         // +0x4c
    virtual bool GetFlag50();                   // +0x50  (slot 20)
    virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual float GetRadius();                  // +0x74  (slot 29, returns float in st0)
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42();                         // +0xa8
    virtual void* GetTransform();               // +0xac  (slot 43)
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48();                         // +0xc0
    virtual void ApplyRadius(float r, int zero); // +0xc4  (slot 49)
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54();                         // +0xd8
    virtual void SubmitGoal(const void* block); // +0xdc  (slot 55)
    void FUN_00ca3410(const Vector3* p, float a, float b, char useCam);   // 0x00ca3410
};
class cGameData;

// The +0x508 sub-object: owns the -0x508/-0x438/-0x4d4 negative-offset view.
class cGameDataSub {
public:
    cGameData& Owner();                          // enclosing object (one named cast)
    Vector3* GetGameDataOwner(Vector3* out);     // 0x00ca3030
    uint8_t pad500[0x500];
};

// Simulator::cGameData.  Only fields the six functions touch are named.
class cGameData {
public:
    bool mBaseIsSpecial();                       // the base object's vtable slot +0x2c
    virtual void vBase();                        // gives cGameData its vptr at +0

    // +0x000 vtable
    uint8_t pad004[0x34 - 0x04];
    cSpatialObject mSpatial;                     // +0x34
    uint8_t pad038[0xa0 - 0x38];
    uint8_t mCivMode;                            // +0xa0  (written by 0x00ca3350)
    uint8_t pad0a1[0xab - 0xa1];
    uint8_t mSpatialFlag;                        // +0xab  (read by 0x00ca31f0)
    uint8_t pad0ac[0xd0 - 0xac];
    // +0xd0: the property-owning sub-object; its +0x90 pointer is handed to
    // SP::GetPropertyAsTransformArray.
    uint8_t pad0d0[0x90];
    uint32_t mPropertyList;                      // +0x160
    uint8_t pad164[0x218 - 0x164];
    uint32_t mCameraScale;                       // +0x218 (multiplied by the mode scale)
    uint8_t pad21c[0x270 - 0x21c];
    uint32_t m270;                               // +0x270
    uint8_t pad274[0x2a4 - 0x274];
    uint32_t m2a4;                               // +0x2a4  (cleared by 0x00ca3410)
    uint8_t pad2a8[0x508 - 0x2a8];
    cGameDataSub mSub;                           // +0x508 (0x500 bytes)
    uint8_t pad_a08[0xaf0 - 0xa08];
    uint32_t mpFlagHolder;                       // +0xaf0
    uint32_t mReadValue;                         // +0xaf4
    uint8_t pad_af8[0xb20 - 0xaf8];
    uint32_t mSubFlag618;                        // +0xb20
    uint32_t mMode;                              // +0xb24
    uint8_t pad_b28[0xb68 - 0xb28];
    uint32_t mListBegin;                         // +0xb68
    uint32_t mListEnd;                           // +0xb6c
    uint8_t pad_b70[0xb80 - 0xb70];
    Vector3 mMarkerPos;                          // +0xb80
    uint8_t pad_b8c[0xc64 - 0xb8c];
    uint32_t mPointBegin;                        // +0xc64
    uint32_t mPointEnd;                          // +0xc68
    uint8_t pad_c6c[0xc78 - 0xc6c];
    uint32_t mPointIndex;                        // +0xc78

    void FUN_00ca31f0();                         // 0x00ca31f0
    void FUN_00ca3350(char enable);              // 0x00ca3350
    void FUN_00ca33b0(const Vector3* p);         // 0x00ca33b0
    uint8_t FUN_00ca3660(void* stream);          // 0x00ca3660
    void FUN_00c9fb40(float x, float y, float z, float zero, float radius);   // 0x00c9fb40
    void FUN_00c9f6c0();                         // 0x00c9f6c0
};

// The recursive owner lookup reached by 0x00ca3030's non-taken paths is the
// same function entered on the enclosing object (0x00bfc8a0).
Vector3* GetGameDataOwner2(cGameData* self, Vector3* out);      // 0x00bfc8a0

// The base object's own vtable slots reached through negative offsets.
inline bool cGameData::mBaseIsSpecial() {
    typedef char (__thiscall *Fn)(cGameData*);
    Fn fn = *(Fn*)((char*)*(void**)this + 0x2c);
    return fn(this) != 0;
}

// The object at base+0x34 is the one 0x00ca3410 is entered through; it is the
// same cSpatialObject the family reaches as cGameData::mSpatial, so the
// recovered base is this - 0x34.
inline cGameData& cSpatial_Owner(cSpatialObject* self) {
    return *(cGameData*)((char*)self - 0x34);
}

cGameData& cGameDataSub::Owner() {
    return *(cGameData*)((char*)this - 0x508);
}

// ---------------------------------------------------------------------------
// Constants and callees.
// ---------------------------------------------------------------------------
extern const float g_1485720;   // 0x01485720  _HK_REAL_ONE
extern const float g_14853e0;   // 0x014853e0
extern const float g_1486114;   // 0x01486114
extern const float g_13ec4b4;   // 0x013ec4b4
extern const float g_13ec4b8;   // 0x013ec4b8
extern const float g_14749a8;   // 0x014749a8

// 0x00b3d370 -> the world/game descriptor whose +0x20 byte gates 0x00ca31f0.
struct cWorldDesc { uint8_t mFlagAt20; };
cWorldDesc* FUN_00b3d370();                                     // 0x00b3d370

// 0x00cf74c0 returns the civ-mode strategy singleton; 0x00cf7830 tests a
// tutorial id on it; 0x00c9f6c0 / 0x00c9e5d0 refresh the tutorial state.
void* FUN_00cf74c0();                                           // 0x00cf74c0
struct cCivModeStrategy {
    uint8_t pad000[0x148];
    uint8_t mFlag148;                            // +0x148
    bool HasCivTutorialOccurred(uint32_t id);    // 0x00cf7830 (thiscall, ret 4)
};
bool HasCivTutorialOccurred(void* self, uint32_t id);           // 0x00cf7830
void FUN_00c9f6c0(cGameData* self);                             // 0x00c9f6c0
void TryCivModeTutorial();                                      // 0x00c9e5d0
void FUN_00c9fb40(cGameData* self, float x, float y, float z, float a, float b);  // 0x00c9fb40

// 0x00b5b800 -> the current game mode singleton (compared with 0x01654c10).
void* GetCurrentGameMode();                                     // 0x00b5b800
void* FUN_00f3f950(void* a, void* b);                           // 0x00f3f950

// Transform / planet helpers used by 0x00ca3030 and 0x00ca31f0.
bool GetPropertyAsTransformArray(uint32_t list, uint32_t name, void* out, uint32_t* count);  // 0x006a0c30
void Transform_Ctor(void* transform);                           // 0x00409930
void AssignTransformOps(void* transform, const void* src);      // 0x00537dc0
void LocalToWorldTransform(const void* self, void* out);        // 0x00c897e0
void FUN_0044d4f0(void* transform);                             // 0x0044d4f0
void FUN_00b7e3b0(void* self, Vector3* out, const Vector3* in); // 0x00b7e3b0
void MatOwner_SetB(void* self, const Vector3* p, const Vector3* q);   // 0x006ba840
Vector3* DirectionToSurfacePosition(cPlanetModel* pm, Vector3* out, const Vector3* in);  // 0x00b815a0
void cNavigationGoal_InitToward(void* goal, const Vector3* p, const Vector3* dir, float a, float b);  // 0x00ad2a50
struct cGroundLayer { void addInterpolated(const void* desc, float blend); };   // 0x00ac7680

// Serializer helpers used by 0x00ca3660.
bool ReadInt32(void* stream, int* value);                       // 0x0093a780
bool cGameData_Read(cGameData* self, void* stream);             // 0x00b18600
bool FUN_00bfc540(void* stream);                                // 0x00bfc540
bool FUN_00c43c10(void* self, void* stream);                    // 0x00c43c10
void cVarListSerializer_Ctor(void* self, cGameData* data, const void* schema, uint32_t id);  // 0x00692f90
bool cVarListSerializer_Read(void* self, void* stream);         // 0x00693e10
void FUN_00ca2e80(cGameData* self);                             // 0x00ca2e80
void FUN_00dc4b70(cGameData* self);                             // 0x00dc4b70
void FUN_00c9f7c0(cGameData* self);                             // 0x00c9f7c0

// ---------------------------------------------------------------------------
// Shared value types.
// ---------------------------------------------------------------------------
// cSPTransform: flags/modcount word pair at +0, translation at +8, scale at +0x14.
struct cSPTransform {
    uint16_t mFlags;                    // +0x00
    uint16_t mModificationCount;        // +0x02
    uint16_t pad04;
    Vector3 mTranslation;               // +0x08
    float mScale;                       // +0x14
};

// 0x00ca3410's navigation goal block.  Retail builds it at esp+0x20 and spans
// 0x78 bytes; the first and last words are heap pointers that are freed after
// the submit call (the `test bl,2 / and ebx,~2 / operator delete` tail).
struct cNavGoalBlock {
    uint32_t* mpBuffer0;                // +0x00  (freed after submit)
    uint32_t mWord04;                   // +0x04
    uint32_t mWord08;                   // +0x08
    uint32_t mWord0c;                   // +0x0c
    uint32_t mWord10;                   // +0x10
    Vector3 mDirect;                    // +0x14
    uint32_t mWord20;                   // +0x20
    uint32_t mWord24;                   // +0x24
    uint32_t pad28[0x24 / 4];           // +0x28
    uint32_t mWord4c;                   // +0x4c
    uint32_t mWord50;                   // +0x50
    uint32_t mWord54;                   // +0x54
    uint32_t mWord58;                   // +0x58
    uint32_t mWord5c;                   // +0x5c
    uint32_t mWord60;                   // +0x60
    uint32_t mWord64;                   // +0x64
    uint32_t mWord68;                   // +0x68
    uint32_t mWord6c;                   // +0x6c
    uint32_t mWord70;                   // +0x70
    uint32_t* mpBuffer74;               // +0x74  (freed after submit)
};

// ---------------------------------------------------------------------------
// The six entry points.
// ---------------------------------------------------------------------------

// @ 0x00ca3030
Vector3* cGameDataSub::GetGameDataOwner(Vector3* out) {
    cGameData& g = Owner();

    // The base object's own vtable slot +0x2c is consulted first, then the
    // +0x618 mode byte (0 or 1) and the empty point-array check; any of them
    // forwards to the (recursive) owner lookup.
    if (g.mBaseIsSpecial())
        return GetGameDataOwner(out);
    if (g.mSubFlag618 != 0 && g.mSubFlag618 != 1)
        return GetGameDataOwner(out);
    if (g.mPointBegin == g.mPointEnd)
        return GetGameDataOwner(out);

    // The point array is indexed by +0x770, clamped to its length.
    int count = (int)((char*)g.mPointEnd - (char*)g.mPointBegin) / 0x10;
    if (g.mPointIndex >= count)
        g.mPointIndex = 0;

    uint32_t prop = g.mPropertyList;          // base +0xd0's +0x90
    uint32_t start = 0;
    uint32_t array = 0;
    if (!GetPropertyAsTransformArray(prop, 0xf1fae963, &start, &array))
        return GetGameDataOwner2(&g, out);

    int elem = *(int*)(g.mPointBegin + g.mPointIndex * 0x10 + 4);
    if (elem >= (int)start)
        return GetGameDataOwner2(&g, out);

    const void* src = (const void*)(array + elem * 0x38);
    Vector3 v;
    v.x = *(float*)((const char*)src + 4);
    v.y = *(float*)((const char*)src + 8);
    v.z = *(float*)((const char*)src + 0xc);

    cSPTransform transform;
    Transform_Ctor(&transform);

    cSpatialObject* sp = &g.mSpatial;
    void* t = sp->GetTransform();
    if (t != 0) {
        AssignTransformOps(&transform, (const char*)t + 8);
    } else {
        LocalToWorldTransform(sp, &transform);
        transform.mScale = sp->GetScale();
        transform.mModificationCount = (uint16_t)(transform.mModificationCount + 1);
    }

    FUN_0044d4f0(&v);
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    return out;
}

// @ 0x00ca31f0
void cGameData::FUN_00ca31f0() {
    cWorldDesc* wd = FUN_00b3d370();
    const Vector3* pos = mSpatial.GetPosition();
    if (wd->mFlagAt20 == 0 || pos == 0)
        return;
    uint32_t flags = *(uint32_t*)((char*)pos + 4);
    if (((flags >> 0xe) & 1) == 0)
        return;
    if (((flags >> 0x12) & 1) != 0)
        return;
    if (!mSpatial.GetFlag48())
        return;

    cSPTransform transform;
    Transform_Ctor(&transform);

    const Vector3* p = mSpatial.GetPosition();
    Vector3 normal;
    FUN_00b7e3b0(SP::PlanetModel(), &normal, p);

    Vector3 zero;
    zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
    Vector3 zAxis;
    zAxis.x = 0.0f; zAxis.y = 0.0f; zAxis.z = g_1485720;
    MatOwner_SetB(&transform, &zero, &zAxis);

    const Vector3* target;
    if (mSpatialFlag == 0) {
        Vector3 tmp;
        target = DirectionToSurfacePosition(SP::PlanetModel(), &tmp, mSpatial.GetPosition());
    } else {
        target = mSpatial.GetPosition();
    }
    Vector3 dst;
    dst.x = target->x; dst.y = target->y; dst.z = target->z;
    transform.mFlags |= 4;
    transform.mModificationCount = (uint16_t)(transform.mModificationCount + 1);
    transform.mTranslation = dst;
    transform.mModificationCount = (uint16_t)(transform.mModificationCount + 1);
    float radius = mSpatial.GetRadius() * g_1486114;
    ((cGroundLayer*)wd)->addInterpolated(&transform, radius);
}

// @ 0x00ca3350
void cGameData::FUN_00ca3350(char enable) {
    cCivModeStrategy* civ = (cCivModeStrategy*)FUN_00cf74c0();
    if (civ->mFlag148 != 0) {
        if (!((cCivModeStrategy*)FUN_00cf74c0())->HasCivTutorialOccurred(0x64e6678))
            return;
    }
    if (enable != 0 && !mSpatial.GetFlag50())
        FUN_00c9f6c0();
    mCivMode = (uint8_t)enable;
    if (enable != 0)
        TryCivModeTutorial();
}

// @ 0x00ca33b0
void cGameData::FUN_00ca33b0(const Vector3* p) {
    mMarkerPos = *p;
    float radius = mSpatial.GetRadius();
    FUN_00c9fb40(p->x, p->y, p->z, 0.0f, radius * g_14853e0);
}

// @ 0x00ca3410
void cSpatialObject::FUN_00ca3410(const Vector3* p, float a, float b, char useCam) {
    cGameData& g = cSpatial_Owner(this);
    cNavGoalBlock block;
    unsigned flags = 0;
    if (useCam != 0) {
        const Vector3* c = GetPosition();
        float dx = p->x - c->x;
        float dy = p->y - c->y;
        float dz = p->z - c->z;
        float inv = 1.0f / sqrtf((dx * dx + (dz * dz + dy * dy)) + g_13ec4b8);
        Vector3 dir;
        dir.x = dx * inv;
        dir.y = dy * inv;
        dir.z = dz * inv;
        cNavigationGoal_InitToward(&block, p, &dir, a, b);
        flags |= 2;
    } else {
        block.mWord04 = 0;
        block.mWord08 = 0;
        block.mWord0c = 0;
        block.mWord10 = 0;
        block.mDirect.x = p->x;
        block.mDirect.y = p->y;
        block.mDirect.z = p->z;
        block.mWord20 = (uint32_t&)b;
        block.mWord24 = 0;
        block.mWord4c = 0;
        block.mWord50 = 0;
        block.mWord54 = 0;
        block.mWord58 = 0;
        block.mWord5c = 1;
        block.mWord60 = (uint32_t&)a;
        block.mWord64 = (uint32_t&)g_13ec4b4;
        block.mWord68 = (uint32_t&)g_14749a8;
        block.mWord6c = 0;
        block.mWord70 = 0;
        flags |= 1;
    }
    SubmitGoal(&block);
    if (flags & 2) {
        flags &= ~2u;
    } else {
        if (block.mpBuffer0 != 0)
            operator delete(block.mpBuffer0);
        if (block.mpBuffer74 != 0)
            operator delete(block.mpBuffer74);
    }
    float scale = g_1485720;
    void* mode = GetCurrentGameMode();
    if (mode == (void*)0x01654c10) {
        void* w = FUN_00f3f950((char*)this - 0x34, 0);
        if (w != 0)
            scale = *(float*)((char*)w + 0x490);
    }
    ApplyRadius(g.mCameraScale * scale, 0);
    g.m2a4 = 0;
}

// @ 0x00ca3660
uint8_t cGameData::FUN_00ca3660(void* stream) {
    void* s1 = (*(void*(__thiscall**)(void*))*(void**)stream)(stream);
    void* s2 = (*(void*(__thiscall**)(void*))*(void**)s1)(s1);
    ReadInt32(s2, (int*)&mReadValue);
    uint8_t ok = 0;
    if (cGameData_Read(this, stream)) {
        if (FUN_00bfc540(stream)) {
            if (FUN_00c43c10(&mSpatial, stream))
                ok = 1;
        }
    }
    uint8_t serializer[0x14];
    cVarListSerializer_Ctor(serializer, this, 0, 0);
    uint8_t result = 0;
    if (cVarListSerializer_Read(serializer, stream) && ok)
        result = 1;
    FUN_00ca2e80(this);
    FUN_00dc4b70(this);
    *(uint32_t*)(mpFlagHolder + 0x5fc) &= 0xfffffcff;
    if (mMode == 0)
        *(uint32_t*)(mpFlagHolder + 0x5fc) |= 0x100;
    else if (mMode == 1)
        *(uint32_t*)(mpFlagHolder + 0x5fc) |= 0x200;
    if (mListBegin != mListEnd)
        FUN_00c9f7c0(this);
    return result;
}
