// Slice s00c41360 — SP::cInterCityRoad: builds the road's path (mPathData, Vector3 list) from a curve
// that is routed between the two cities, trimmed to the city-wall radii and extended back to them.
// Retail layout (ModAPI): mpCity1 +0x11c, mpCity2 +0x120, mPathData +0x128 (retail sp_vector, 0x14 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module family as s00b8c330.
#include <math.h>
#include "types.h"

void __cdecl operator_delete__(void* p);   // 0xf47380 (operator delete[])

inline void* operator new(unsigned int, void* p) throw() { return p; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
struct PodVec3 {    // trivially copyable (integer-register copies)
    float x, y, z;
};
bool __cdecl Vector3Equal(const PodVec3* a, const PodVec3* b);   // 0x004232c0
extern PodVec3 g_DefaultPosition;                                 // 0x0168e690 (also the "no position" marker)

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
    void deallocate(void* p) {
        if (((uint32_t*)p)[-1])
            operator_delete__(p);
    }
};

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin) mAllocator.deallocate(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T* erase(T* first, T* last);
    T* insert(T* pos, const T& v);
    void DoInsertValue(T* pos, const T& v);
    void push_back_default();
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
};

struct cCurvePoint {          // 0x3c bytes
    Vector3 mPos;             // +0x00
    float mF0c;               // +0x0c
    int mF10;                 // +0x10
    uint32_t pad14[(0x38 - 0x14) / 4];
    bool mF38;                // +0x38
    cCurvePoint(const Vector3& p) : mPos(p), mF0c(1.0f), mF10(0), mF38(false) {}
};

typedef SpVector<Vector3> Vec3Vector;
typedef SpVector<cCurvePoint> CurveVector;

template <> cCurvePoint* CurveVector::erase(cCurvePoint* first, cCurvePoint* last);          // 0xac4570
template <> cCurvePoint* CurveVector::insert(cCurvePoint* pos, const cCurvePoint& v);        // 0xc41190
template <> void CurveVector::push_back_default();                                           // 0xc410e0
template <> Vector3* Vec3Vector::erase(Vector3* first, Vector3* last);                       // 0x50f740
template <> void Vec3Vector::DoInsertValue(Vector3* pos, const Vector3& v);                  // 0x4b5ad0

struct cCurveParams {         // 20 bytes
    const char* mpName;
    void* mpA;
    void* mpFunc;
    void* mpB;
    void* mpC;
};
extern cCurveParams g_LandAvoidCitiesParams;          // 0x1565b54 ("landAvoidCities")

struct cCurveBuilder {
    void Build(const cCurveParams& params, const PodVec3& a, const PodVec3& b,
               CurveVector& out, float t0, float t1);  // 0xac6960
};
cCurveBuilder* __cdecl GetCurveBuilder();             // 0xb3d290

struct cCityWalls {
    char pad[0x25c];
    float mOuterRadius;                               // +0x25c
    const PodVec3& GetWallPosition(Vector3& out, const Vector3& towards, int flag);   // 0xbec660 (sret)
    const PodVec3& RequestPosition(Vector3& out, int mode);                           // 0xbec2d0 (sret)
};

struct cSpatialObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();             // +0x2c
};

struct cCity {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual cCityWalls* GetCityWalls();               // +0x6c
    char pad04[0x120 - 4 - 4 * 0];
    cSpatialObject mSpatial;                          // +0x120 (secondary base)
};

class cInterCityRoad {
public:
    char pad[0x118];
    bool mbFlag118;               // +0x118
    cCity* mpCity1;               // +0x11c
    cCity* mpCity2;               // +0x120
    int mRoadType;                // +0x124
    Vec3Vector mPathData;         // +0x128
    char pad13c[4];
    float mWidth;                 // +0x13c (unused here)
    void BuildPath();             // 0x00c41360
    void SetupCities(void* city1, void* city2, int roadType, int flag);  // 0x00c41c60
};

// @ 0x00c41360
void cInterCityRoad::BuildPath()
{
    mPathData.erase(mPathData.begin(), mPathData.end());

    if (mpCity1 && mpCity1->GetCityWalls() && mpCity2 && mpCity2->GetCityWalls()) {
        CurveVector curve;

        Vector3 tmp;
        PodVec3 posA = mpCity1->GetCityWalls()->GetWallPosition(tmp, mpCity2->mSpatial.GetPosition(), 0);
        PodVec3 posB = mpCity2->GetCityWalls()->GetWallPosition(tmp, mpCity1->mSpatial.GetPosition(), 0);
        if (Vector3Equal(&posA, &g_DefaultPosition))
            posA = mpCity1->GetCityWalls()->RequestPosition(tmp, 5);
        if (Vector3Equal(&posB, &g_DefaultPosition))
            posB = mpCity2->GetCityWalls()->RequestPosition(tmp, 5);

        GetCurveBuilder()->Build(g_LandAvoidCitiesParams, posA, posB, curve, 0.0f, 1.0f);

        // drop the tail of the curve starting at the first point inside city 2's wall radius
        for (unsigned i = 0; i < (unsigned)curve.size(); ++i) {
            Vector3 d = curve[i].mPos - mpCity2->mSpatial.GetPosition();
            cCityWalls* w = mpCity2->GetCityWalls();
            float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
            if (len < w->mOuterRadius + 1.0f) {
                curve.erase(&curve[i], curve.end());
                break;
            }
        }
        // drop the head of the curve up to the last point inside city 1's wall radius
        for (int i = curve.size(); i != 0; --i) {
            Vector3 d = curve[i - 1].mPos - mpCity1->mSpatial.GetPosition();
            cCityWalls* w = mpCity1->GetCityWalls();
            float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
            if (len < w->mOuterRadius + 1.0f) {
                curve.erase(curve.begin(), &curve[i]);
                break;
            }
        }

        if (curve.begin() != curve.end()) {
            // first point too far from city 1: add a start point on the wall circle
            {
                const Vector3* p = &curve.begin()->mPos;
                Vector3 d = *p - mpCity1->mSpatial.GetPosition();
                cCityWalls* w = mpCity1->GetCityWalls();
                float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
                if (len > w->mOuterRadius + 3.0f) {
                    float r = mpCity1->GetCityWalls()->mOuterRadius + 1.0f;
                    cCurvePoint* first = curve.begin();
                    Vector3 d2 = first->mPos - mpCity1->mSpatial.GetPosition();
                    float inv = 1.0f / sqrtf(d2.x * d2.x + d2.z * d2.z + d2.y * d2.y);
                    Vector3 off = d2 * inv * r;
                    Vector3 np = mpCity1->mSpatial.GetPosition() + off;
                    curve.insert(curve.begin(), cCurvePoint(Vector3(g_DefaultPosition.x, g_DefaultPosition.y, g_DefaultPosition.z)));
                    curve.begin()->mPos = np;
                }
            }
            // last point too far from city 2: add an end point on the wall circle
            {
                cCurvePoint* last = curve.end() - 1;
                Vector3 d = last->mPos - mpCity2->mSpatial.GetPosition();
                cCityWalls* w = mpCity2->GetCityWalls();
                float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
                if (len > w->mOuterRadius + 3.0f) {
                    float r = mpCity2->GetCityWalls()->mOuterRadius + 1.0f;
                    cCurvePoint* last2 = curve.end() - 1;
                    Vector3 d2 = last2->mPos - mpCity2->mSpatial.GetPosition();
                    float inv = 1.0f / sqrtf(d2.x * d2.x + d2.z * d2.z + d2.y * d2.y);
                    Vector3 off = d2 * inv * r;
                    Vector3 np = off + mpCity2->mSpatial.GetPosition();
                    curve.push_back_default();
                    (curve.end() - 1)->mPos = np;
                }
            }
        }

        int n = curve.size();
        for (int i = 0; i < n; ++i)
            mPathData.push_back(curve[i].mPos);
    }
}

// =====================================================================
// Slice s00c41360 (continued): SP::cInterCityRoad methods
// 0x00C41B00, 0x00C41C60, 0x00C41DC0, 0x00C41ED0, 0x00C41F30,
// 0x00C41FF0, 0x00C420F0, 0x00C42140, 0x00C421F0, 0x00C42210,
// 0x00C422C0, 0x00C42310, 0x00C42350, 0x00C423C0.
// NAMING NOTE: no symbols are known for these; names are Claude-coined.
// =====================================================================

extern float g_OneThird;                     // 0x013f26dc (0.33333334f)
extern float g_HkRealZero;                   // 0x01485378 (0.0f)
extern float g_RoadDefaultScale;             // 0x0169cb58
extern wchar_t g_ListName[];                 // 0x013f58ac L"list"
extern wchar_t g_Vec3TypeName[];             // 0x0145a188 L"cSPVector3"
extern char    g_LandAvoidCitiesName[];      // 0x01565b54 "landAvoidCities"

struct cRandomGlobal { float RandomDouble(); };        // 0x009360d0 (thiscall)
struct cAvatarHolder2
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual void AddRoad(void* road);                  // +0x48
};
cAvatarHolder2* __cdecl GetAvatarHolder2();            // 0x00b3d240
cCurveBuilder*  __cdecl GetCurveBuilder2(const char* name);  // 0x00b3d290
void __cdecl BuildCurve1(cCurveBuilder* b, void* a);   // 0x00ac6a10
void __cdecl BuildCurve2(cCurveBuilder* b, void* a);   // 0x00ac65d0
int  __cdecl SerializeVec3List(void* a, int b, void* c, const wchar_t* type);  // 0x00acadb0

struct cRoad
{
    char    pad04[0x118 - 0x04];    // +0x04 (after vptr)
    bool    mbFlag118;              // +0x118
    cCity*  mpCity1;                // +0x11c
    cCity*  mpCity2;                // +0x120
    int     mRoadType;              // +0x124
    char    pad128[0x13c - 0x128];
    float   mF13c;                  // +0x13c
    char    pad140[0x1a8 - 0x140];
    Vector3 mV1a8;                  // +0x1a8
    Vector3 mV1b4;                  // +0x1b4
    float   mF1c0;                  // +0x1c0
    float   mF1c4;                  // +0x1c4
    char    pad1c8[0x1f4 - 0x1c8];
    void*   mBegin1f4;              // +0x1f4
    void*   mEnd1f8;                // +0x1f8
    char    pad1fc[0x208 - 0x1fc];
    Vector3 mV208;                  // +0x208
    char    pad214[0x250 - 0x214];
    int     mF250;                  // +0x250
    float   mF254;                  // +0x254
    char    pad258[0x260 - 0x258];
    float   mF260;                  // +0x260
    char    pad264[0x26c - 0x264];
    float   mF26c;                  // +0x26c
    int     mF270;                  // +0x270
    char    pad274[0x278 - 0x274];
    Vector3 mV278;                  // +0x278
    char    pad284[0x490 - 0x284];
    int*    mpIntBegin490;          // +0x490
    int*    mpIntEnd494;            // +0x494
    char    pad498[0x4b8 - 0x498];
    Vector3 mV4b8;                  // +0x4b8

    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vector3& GetPosition();              // +0x2c
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
    virtual char Action58();                           // +0x58
    virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62();
    virtual void v63(); virtual void v64(); virtual void v65();
    virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
    virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73();
    virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77();
    virtual void v78(); virtual void v79(); virtual void v80(); virtual void v81();
    virtual void v82(); virtual void v83(); virtual void v84(); virtual void v85();
    virtual void* LookupById(uint32_t id);             // +0xb8
    virtual void v87();
    virtual void Chain(uint32_t a, uint32_t b);        // +0xc4

    float DistSqToPos();                               // 0x00c422c0
    bool  WithinRadius(float r);                       // 0x00c42210
};

// @ 0x00c423c0
struct cRoadTail
{
    uint8_t* mpBegin;               // +0x00
    uint8_t* mpEnd;                 // +0x04
    uint8_t  pad08[0x14 - 0x08];
    uint8_t  mDefault[0x3c];        // +0x14
};

int* __fastcall FUN_00c423c0(cRoadTail* t)
{
    uint8_t* e = t->mpEnd;
    if (t->mpBegin == e)
        return (int*)t->mDefault;
    return (int*)(e - 0x3c);
}

// @ 0x00c421f0
int* __fastcall FUN_00c421f0(cRoad* this_)
{
    void* b = this_->mBegin1f4;
    if (b == this_->mEnd1f8)
        return (int*)&this_->mV208;
    return (int*)((uint32_t)this_->mEnd1f8 - 0x3c);
}

// @ 0x00c41ed0
int __fastcall FUN_00c41ed0(cRoad* this_, float a, float b)
{
    int r;
    if (b * b >= a)
        r = 1;
    else if (this_->mF260 > g_HkRealZero)
    {
        if (this_->mF254 * this_->mF254 < a)
            r = 0;
        else
            r = 1;
    }
    else
        r = 0;
    return r;
}

// @ 0x00c422c0
float __fastcall FUN_00c422c0(cRoad* this_)
{
    if (this_->mF250 == 0)
        return 0.0f;
    const Vector3& pos = this_->GetPosition();
    float dx = this_->mV208.x - pos.x;
    float dy = this_->mV208.y - pos.y;
    float dz = this_->mV208.z - pos.z;
    return dz * dz + dx * dx + dy * dy;
}

// @ 0x00c42210
bool __fastcall FUN_00c42210(cRoad* this_, float r)
{
    if (this_->mF250 == 0)
        return true;
    Vector3 p;
    if (this_->mBegin1f4 == this_->mEnd1f8)
    {
        p.x = this_->mV208.x;
        p.y = this_->mV208.y;
        p.z = this_->mV208.z;
    }
    else
    {
        float* q = (float*)((uint8_t*)this_->mEnd1f8 - 0x3c);
        p.x = q[0];
        p.y = q[1];
        p.z = q[2];
    }
    const Vector3& c = this_->GetPosition();
    float dx = p.x - c.x;
    float dy = p.y - c.y;
    float dz = p.z - c.z;
    return sqrtf(dz * dz + dx * dx + dy * dy) < r;
}

// @ 0x00c42140
void __fastcall FUN_00c42140(cRoad* this_, int value)
{
    int n = (int)(this_->mpIntEnd494 - this_->mpIntBegin490);
    if (n == 0)
        return;
    int* p = this_->mpIntBegin490;
    unsigned i = 0;
    while (value != *p)
    {
        ++i;
        ++p;
        if ((unsigned)(this_->mpIntEnd494 - this_->mpIntBegin490) <= i)
            return;
    }
    this_->mpIntBegin490[i] = this_->mpIntBegin490[n - 1];
    this_->mpIntEnd494 -= 1;
}

// @ 0x00c420f0
float __cdecl FUN_00c420f0(cRandomGlobal* r, float a, float b)
{
    float r1 = r->RandomDouble();
    float r2 = r->RandomDouble();
    float r3 = r->RandomDouble();
    return (r3 + r2 + r1) * (b - a) * g_OneThird + a;
}

// @ 0x00c42310
int __cdecl FUN_00c42310(int* param_1)
{
    if (param_1 == 0)
        return 0;
    int* p = (int*)(*(int(__thiscall**)(int*, uint32_t))(*param_1 + 0xb8))(param_1, 0x17f243b);
    if (p == 0)
        return 0;
    char c = (*(char(__thiscall**)(int*))(*p + 0x2c))(p);
    if (c == 0)
        return 0;
    return 1;
}

// --- 0x00C42310: entity lookup test -----------------------------------
struct IdLookupTarget
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual char  Test();                              // +0x2c
};
struct IdLookupSource
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual void v43(); virtual void v44(); virtual void v45();
    virtual IdLookupTarget* Lookup(uint32_t id);       // +0xb8
    IdLookupTarget* Find(uint32_t id) { return Lookup(id); }
};

// @ 0x00c42310
int __cdecl FUN_00c42310(IdLookupSource* param_1)
{
    if (param_1 != 0)
    {
        IdLookupTarget* t = param_1->Find(0x17f243b);
        if (t != 0)
        {
            if (t->Test() != 0)
                return 1;
        }
    }
    return 0;
}

// --- 0x00C42350: add the road's selection effect to the avatar holder ---
struct RoadEffectParams { float mF0c; };                // single float arg block
struct EntityRef
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void* BuildEffect(float scale, const Vector3* pos, int a, void* fn, void* id);  // +0x2c
};
struct AvatarHolder2
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual void AddEffect(void* effect);              // +0x48
};
AvatarHolder2* __cdecl GetAvatarHolder2b();            // 0x00b3d240
void __cdecl EffectCallback0(void* a);                 // 0x00d9a9c0

// @ 0x00c42350
void __fastcall FUN_00c42350(cRoad* this_)
{
    if (this_->mF26c == g_HkRealZero)
        return;
    AvatarHolder2* holder = GetAvatarHolder2b();
    void* id = 0;
    (void)id;
    void* effectId = ((IdLookupSource*)this_)->Find(0x17f243b);
    void* effect = ((EntityRef*)this_)->BuildEffect(this_->mF26c, &this_->mV278,
                                                    0, (void*)EffectCallback0, effectId);
    holder->AddEffect(effect);
}

// --- 0x00C41C60: assign the road's two cities, type and flag, then build -
struct RefCounted
{
    virtual void AddRef();                             // +0x00
    virtual void Release();                            // +0x04
};
void __cdecl RegisterCity(void* city);                 // 0x00b18550

// @ 0x00c41c60
void cInterCityRoad::SetupCities(void* city1, void* city2, int roadType, int flag)
{
    RegisterCity(city1);

    cCity* old1 = mpCity1;
    if (city2 != old1)
    {
        if (city2 != 0)
            ((RefCounted*)city2)->AddRef();
        mpCity1 = (cCity*)city2;
        if (old1 != 0)
            ((RefCounted*)old1)->Release();
    }

    cCity* old2 = mpCity2;
    if ((cCity*)roadType != old2)
    {
        if (roadType != 0)
            ((RefCounted*)roadType)->AddRef();
        mpCity2 = (cCity*)roadType;
        if (old2 != 0)
            ((RefCounted*)old2)->Release();
    }

    mRoadType = flag;
    mbFlag118 = true;
    mWidth = g_RoadDefaultScale;
    BuildPath();
}
