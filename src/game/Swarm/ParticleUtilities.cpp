// src/game/Swarm/ParticleUtilities.cpp -- migrated from slice(s) s00a7a580, s00a798d0, s00a78ce0, s00a7b370 by tools/migrate/rewrite.py
// Object file: Swarm/ParticleUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>
#include "EA/Swarm/cTransform.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/ArgScript/cIParser.h"

// ---- items of slice s00a7b370 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct FloatVec {          // eastl::vector<float> (begin, end, capacity)
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    void PushSlow(float* pEnd, const float* v);   // 0x00455660 (thiscall)
    void push_back(const float& v) {
        float* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            PushSlow(p, &v);
        }
    }
};
struct Vec3Vec { Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCapacity; };
struct Vertex {            // 0x1c bytes: position, direction, parameter
    Vec3 pos;
    Vec3 dir;
    float param;
};
struct VertexVec {
    Vertex* mpBegin;
    Vertex* mpEnd;
    Vertex* mpCapacity;
    void PushSlow(Vertex* pEnd, const Vertex* v);   // 0x00a7a9d0
    Vertex* erase(Vertex* first, Vertex* last);    // 0x00d73090 (thiscall, ret 8)
};
extern const Vec3 kDefaultDir;                      // 0x016770dc
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template<class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
struct PathBuilder {
    char       pad00[0x38];
    Vec3Vec    mPoints;       // +0x38
    char       pad44[0x4c - 0x44];
    FloatVec   mWidths;       // +0x4c
    char       pad58[0x60 - 0x58];
    Vec3Vec    mTangents;     // +0x60
    char       pad6c[0x74 - 0x6c];
    FloatVec   mParams;       // +0x74
    char       pad80[0x88 - 0x80];
    bool*      mpDone;        // +0x88
    char       pad8c[0x90 - 0x8c];
    VertexVec* mpOut;         // +0x90
    void Build(bool skip);    // 0x00a7b370
};
static inline float SegLen(const Vec3& a, const Vec3& b)
{
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
// ---- items of slice s00a7b370 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const Vec3 kDefaultDir;                      // 0x016770dc

// ---- items of slice s00a78ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)
struct Xform {                                                    // 0x38
    unsigned flags;              // +0x00
    Vec3     translation;        // +0x04
    float    scale;              // +0x10
    float    m[9];               // +0x14
    void InverseTransformDir(Vec3* v) const;
    void TransformDir(Vec3* v) const;
};
// ---- items of slice s00a78ce0 end

// ---- items of slice s00a798d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_007d0250(void* stream, void* obj);                       // 0x7d0250
extern "C" void EA_WriteUint32(void* stream, const void* data, int count, int flags); // 0x93aa70
extern "C" void EA_StreamWrite(void* stream, const void* data, int count);   // 0x93a9a0
extern "C" void operator_delete__(void* p);   // 0xf47380
extern const unsigned vtbl_ArgScript_Path[];
struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) { x = a; y = b; z = c; } };
struct HKey {              // 0x1c bytes
    V3 p;                  // +0x00 position
    V3 t;                  // +0x0c tangent
    float time;            // +0x18
};
struct HKeyVec { HKey* mpBegin; HKey* mpEnd; };
struct HXform {            // Transform: flags / offset / scale / rotation
    unsigned short flags;  // bit 1 = rotation present
    unsigned short pad;
    float off[3];          // +0x04
    float scale;           // +0x10
    float m[9];            // +0x14
    void Transform(V3* v);       // 0x7cdee0
    void TransformDir(V3* v);    // 0xa797f0
};
struct HState {
    float time;            // +0x00
    float defaultEnd;      // +0x04
    V3 pos;                // +0x08
    V3 vel;                // +0x14
};
__forceinline HKey* FindAfter(HKey* cur, HKey* last, float t)
{
    if (cur < last)
    {
        int n = ((int)((char*)last - (char*)cur) + 0x1b) / 0x1c;
        if (n >= 4)
        {
            do
            {
                if (!(cur[0].time <= t)) return cur;
                if (!(cur[1].time <= t)) return cur + 1;
                if (!(cur[2].time <= t)) return cur + 2;
                if (!(cur[3].time <= t)) return cur + 3;
                cur += 4;
            } while ((int)cur < (int)(last - 3));
        }
        for (; cur < last; ++cur)
            if (!(cur->time <= t)) return cur;
    }
    return cur;
}
__forceinline V3 Rotate(const HXform* xf, const V3& v)
{
    V3 r;
    r.x = (xf->m[6] * v.z + xf->m[3] * v.y) + xf->m[0] * v.x;
    r.y = (xf->m[7] * v.z + xf->m[4] * v.y) + xf->m[1] * v.x;
    r.z = (xf->m[8] * v.z + xf->m[5] * v.y) + xf->m[2] * v.x;
    return r;
}
struct PathCmdStream {
    unsigned mField00;      // +0x00
    unsigned mField04;      // +0x04
    unsigned mField08;      // +0x08
    unsigned mField0c;      // +0x0c
    float    mField10;      // +0x10
    float    mField14;      // +0x14
    float    mField18;      // +0x18
    char     mField1c[0x14];// +0x1c..0x2f (tail)
    unsigned char mField30; // +0x30
};
typedef void (__thiscall* StreamWriteFn)(void* self, void* data, int size);
struct PathCmdTail {
    char  mPad00[0x14];     // +0x00..0x13
    float mField14;         // +0x14
    float mField18;         // +0x18
};
struct RefCountHeader {
    unsigned mRefCount;     // stored immediately before the payload
};
static inline unsigned RefCountOf(void* payload)
{
    return reinterpret_cast<RefCountHeader*>(payload)[-1].mRefCount;
}
struct PathCommandObj {
    void* mField00;         // +0x00
    void* mField04;         // +0x04
    char  mPad08[0x10];     // +0x08..0x17
    void* mField18;         // +0x18
    char  mPad1c[0x10];     // +0x1c..0x2b
    void* mField2c;         // +0x2c
    char  mPad30[0x10];     // +0x30..0x3f
    void* mField40;         // +0x40
};
struct AppPropsFields {
    void ctor();            // 0x83cdd0
};
struct PathObj {
    void*    mVtbl;         // +0x00
    char     mBase[0x30];   // +0x04..0x33
    unsigned mField34;      // +0x34
    void*    mField38;      // +0x38
    void*    mField3c;      // +0x3c
    void*    mField40;      // +0x40
    char     mPad44[0x08];  // +0x44..0x4b
    void*    mField4c;      // +0x4c
    void*    mField50;      // +0x50
    void*    mField54;      // +0x54
    char     mPad58[0x08];  // +0x58..0x5f
    void*    mField60;      // +0x60
    void*    mField64;      // +0x64
    void*    mField68;      // +0x68
    char     mPad6c[0x08];  // +0x6c..0x73
    void*    mField74;      // +0x74
    void*    mField78;      // +0x78
    void*    mField7c;      // +0x7c
    char     mPad80[0x08];  // +0x80..0x87
    unsigned mField88;      // +0x88
    unsigned mField8c;      // +0x8c
    unsigned mField90;      // +0x90
};
// ---- items of slice s00a798d0 end

// ---- items of slice s00a7a580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void*, const void*, unsigned int);
extern const char* kPath_01554af4;
extern const char* kPath_01554af8;
extern const char* kPath_01554afc;
extern const char* kPath_01554b00;
extern const char* kPath_01554b04;
extern const char* kPath_01554b08;
extern const char* kPath_01554b0c;
extern const char* kPath_01554b10;
extern const char* kPath_01554b14;
extern const char* kPath_01554b18;
extern const char* kPath_01554b1c;
extern const char* kPath_01554b20;
extern const char* kPath_01554b24;
struct Vector3 { float x, y, z; };
inline Vector3 operator-(const Vector3& a, const Vector3& b) {
    Vector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r;
}
inline Vector3 operator+(const Vector3& a, const Vector3& b) {
    Vector3 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r;
}
void* operator new(unsigned int size, const char* name, int, int, int, int);   // 0x00f473a0
void* operator new(unsigned int size, const char* name, int, int, const char*, int);
void  operator delete(void*);                                                 // 0x00f47380
void* operator_new_array(void*, int, unsigned int);                            // 0x011e073e
namespace EA {
namespace ArgScript {
class cArguments_s00a7_a580;
}
}
namespace EA {
namespace ArgScript {
class cIParser_s00a7_a580;
}
}
namespace EA {
namespace ArgScript {
struct cState_s00a7_a580;
}
}
namespace EA {
namespace ArgScript {
class cICommand_s00a7_a580;
}
}
namespace EA {
namespace ArgScript {
class cIBlockCommand_s00a7_a580;
}
}
namespace EA {
namespace ArgScript {
class cICommand_s00a7_a580 {
 public:
    virtual void Execute(cArguments_s00a7_a580*);
    virtual const char* Description(int) const;
    virtual void OnRegister(cIParser_s00a7_a580*, cState_s00a7_a580*);
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
namespace ArgScript {
class cCommandBase_s00a7_a580 : public cICommand_s00a7_a580 {
 public:
    cCommandBase_s00a7_a580();                              // 0x0083c800
    virtual ~cCommandBase_s00a7_a580();
    cIParser_s00a7_a580* mParser;                           // +0x04
    int mRefCount;                               // +0x08
};
}
}
namespace EA {
namespace ArgScript {
class cBlockCommandBase : public cCommandBase_s00a7_a580 {
 public:
    cState_s00a7_a580* mChildState;                         // +0x0c
    char mMap[0x20];                             // +0x10
    virtual void OnRegister(cIParser_s00a7_a580*, cState_s00a7_a580*); // 0x0083c780
    void SetChildState(cState_s00a7_a580*);                 // 0x00fd9450
    virtual void AddCommand(const char*, cICommand_s00a7_a580*);  // +0x18
    virtual void vAfter();                       // +0x1c
};
}
}
namespace EA {
namespace ArgScript {
template <typename State, typename Base>
struct cCommandStateT_s00a7_a580 : Base {
    State* mState;                               // +0x0c for Base=cCommandBase
};
}
}
namespace EA {
namespace ArgScript {
class cArguments_s00a7_a580 {
 public:
    char const* const* MainArguments(int) const; // 0x00838320
    bool HasFlag(const char*);                   // 0x008380b0
};
}
}
namespace EA {
namespace ArgScript {
class cIParser_s00a7_a580 {
 public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
    virtual void StartBlock(class cIBlockCommand_s00a7_a580*);              // slot 35 = +0x8c
virtual void v36();
virtual void v37();
    virtual float ParseFloat(const char*) const;                 // slot 38 = +0x98
virtual void v39();
virtual void v40();
virtual void v41();
    virtual Vector3 ParseVector3(const char*) const;             // slot 42 = +0xa8
};
}
}
namespace {

template <typename T>
struct Vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAlloc[2];
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    void erase(T* first, T* last);                   // out of line
    void DoInsertValue(T* position, const T& value); // out of line
    void push_back(const T& value) {
        T* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) { e->x = value.x; e->y = value.y; e->z = value.z; }
        } else {
            DoInsertValue(e, value);
        }
    }
};

struct VecF {
    float* mpBegin; float* mpEnd; float* mpCapacity; uint32_t mAlloc[2];
    float* begin() { return mpBegin; }
    float* end() { return mpEnd; }
    float* erase(float* first, float* last) {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd -= last - first;
        return first;
    }
    void DoInsertValue(float* position, const float& value);   // out of line 0x00455660
    void push_back(const float& value) {
        float* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) *e = value;
        } else {
            DoInsertValue(e, value);
        }
    }
};

}  // namespace
namespace SwarmImpl {
struct cPathState {
    uint32_t mStateID;            // +0x00
    Vec<Vector3> mPositions;      // +0x04
    VecF mSpeeds;                 // +0x18
    Vec<Vector3> mDeltaPositions; // +0x2c
    VecF mTimes;                  // +0x40
    int mField54;                 // +0x54
    bool* mTractor;               // +0x58
    int mField5c;                 // +0x5c
    ~cPathState();                // 0x00a7a4a0 (frees the four vectors)
};
}
namespace SwarmImpl {
struct cPathPointCommand : EA::ArgScript::cCommandStateT_s00a7_a580<cPathState, EA::ArgScript::cCommandBase_s00a7_a580> {
    virtual void Execute(EA::ArgScript::cArguments_s00a7_a580*);
};
}
namespace SwarmImpl {
struct cPathDeltaPointCommand : EA::ArgScript::cCommandStateT_s00a7_a580<cPathState, EA::ArgScript::cCommandBase_s00a7_a580> {
    virtual void Execute(EA::ArgScript::cArguments_s00a7_a580*);
};
}
namespace SwarmImpl {
struct cPathVelocityCommand : EA::ArgScript::cCommandStateT_s00a7_a580<cPathState, EA::ArgScript::cCommandBase_s00a7_a580> {
    virtual void Execute(EA::ArgScript::cArguments_s00a7_a580*);
};
}
namespace SwarmImpl {
struct cPathSpeedCommand : EA::ArgScript::cCommandStateT_s00a7_a580<cPathState, EA::ArgScript::cCommandBase_s00a7_a580> {
    virtual void Execute(EA::ArgScript::cArguments_s00a7_a580*);
};
}
namespace SwarmImpl {
struct cPathTimeCommand : EA::ArgScript::cCommandStateT_s00a7_a580<cPathState, EA::ArgScript::cCommandBase_s00a7_a580> {
    virtual void Execute(EA::ArgScript::cArguments_s00a7_a580*);
};
}
namespace SwarmImpl {
struct cPathDeltaTimeCommand : EA::ArgScript::cCommandStateT_s00a7_a580<cPathState, EA::ArgScript::cCommandBase_s00a7_a580> {
    virtual void Execute(EA::ArgScript::cArguments_s00a7_a580*);
};
}
namespace SwarmImpl {
struct cPathCommand : EA::ArgScript::cCommandStateT_s00a7_a580<cPathState, EA::ArgScript::cBlockCommandBase> {
    cPathCommand(int a, bool* b, int c);
    virtual void Execute(EA::ArgScript::cArguments_s00a7_a580*);
    virtual void OnRegister(EA::ArgScript::cIParser_s00a7_a580*, EA::ArgScript::cState_s00a7_a580*);
    cPathState mChildState;       // +0x34
};
}
using EA::ArgScript::cArguments_s00a7_a580;
using EA::ArgScript::cIParser_s00a7_a580;
using EA::ArgScript::cState_s00a7_a580;
using EA::ArgScript::cICommand_s00a7_a580;
using EA::ArgScript::cIBlockCommand_s00a7_a580;
using EA::ArgScript::cBlockCommandBase;
using SwarmImpl::cPathState;
using SwarmImpl::cPathCommand;
using SwarmImpl::cPathPointCommand;
using SwarmImpl::cPathDeltaPointCommand;
using SwarmImpl::cPathVelocityCommand;
using SwarmImpl::cPathSpeedCommand;
using SwarmImpl::cPathTimeCommand;
using SwarmImpl::cPathDeltaTimeCommand;
namespace EA {
namespace Swarm {
void RegisterPathCommand(cBlockCommandBase* owner, int a, bool* b, int c);   // 0x00a7a8d0
}
}
namespace EA {
namespace Swarm {
void* cResourceOverridesParam_Create(int n);                                 // 0x00a7a960
}
}
namespace {

struct cPathSample { Vector3 pos; Vector3 dir; float dist; };   // 0x1c

struct SampleVec {
    cPathSample* mpBegin; cPathSample* mpEnd; cPathSample* mpCapacity; uint32_t mAlloc[2];
    cPathSample* begin() { return mpBegin; }
    cPathSample* end() { return mpEnd; }
    void DoInsertValue(cPathSample* position, const cPathSample& value);  // 0x00a7a9d0
    void erase(cPathSample* first, cPathSample* last);                    // 0x00d73090
    void push_back(const cPathSample& value) {
        cPathSample* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) *e = value;
        } else {
            DoInsertValue(e, value);
        }
    }
};

cPathSample* vec_copy(const cPathSample*, const cPathSample*, cPathSample*);   // 0x00a78e30

struct cPathOpts {
    uint16_t mFlags;              // +0x00
    char mPad02[2];
    Vector3 mOffset;              // +0x04
    float mScale;                 // +0x10
    Vector3 mRow0;                // +0x14
    Vector3 mRow1;                // +0x20
    Vector3 mRow2;                // +0x2c
};

extern const float kOne_01485720;     // 1.0f
extern const float kEps_013f11c8;
extern const float gDirDef_016770dc;
extern const float gDirDef_016770e0;
extern const float gDirDef_016770e4;

}  // namespace
// ---- items of slice s00a7a580 end

// @ 0x00a797f0
void Xform::TransformDir(Vec3* v) const
{
    if (flags & 2) {
        float y = v->y;
        float z = v->z;
        float x = v->x;
        Vec3 t;
        t.x = (m[3] * y + m[6] * z) + m[0] * x;
        t.y = (m[1] * x + m[4] * y) + m[7] * z;
        t.z = (m[2] * x + m[5] * y) + m[8] * z;
        *v = t;
    }
    float s = scale;
    v->x = v->x * s;
    v->y = v->y * s;
    v->z = s * v->z;
}

// @ 0x00a798d0
void HermiteStep(HState* s, float dt, HKeyVec* keys, float maxSpeed, HXform* xf)
{
    float t = s->time;
    HKey* first = keys->mpBegin;
    HKey* last = keys->mpEnd - 1;
    HKey* cur = FindAfter(first, last, t);
    float tk = cur->time;
    if (tk == 0.0f)
        tk = s->defaultEnd;
    else if (tk < t)
    {
        s->pos.x = s->vel.x * dt + s->pos.x;
        s->pos.y = s->vel.y * dt + s->pos.y;
        s->pos.z = s->vel.z * dt + s->pos.z;
        return;
    }
    float T = (tk - t) + dt;
    V3 rp = cur->p;
    if (xf->flags & 2)
        rp = Rotate(xf, cur->p);
    float sc = xf->scale;
    float px = sc * rp.x + xf->off[0];
    float py = xf->off[1] + sc * rp.y;
    float pz = xf->off[2] + sc * rp.z;
    V3 rt = cur->t;
    if (xf->flags & 2)
        rt = Rotate(xf, cur->t);
    sc = xf->scale;
    float qx = rt.x * sc, qy = rt.y * sc, qz = rt.z * sc;
    float dx = s->pos.x - px, dy = s->pos.y - py, dz = s->pos.z - pz;
    if (maxSpeed != 0.0f)
    {
        if (T * maxSpeed < sqrt(dx * dx + dz * dz + dy * dy))
        {
            float prev = 0.0f;
            if (first < cur)
                prev = cur[-1].time;
            float d = t - prev;
            T = d + T;
            s->time = t - d;
        }
    }
    float inv = 1.0f / T;
    float u = inv * dt;
    float u2 = u * u;
    float A = u2 * u - u2;
    float u2x = u * 2.0f;
    float h1 = u2 - A * 2.0f;
    float h0 = 1.0f - h1;
    float d1 = u2 * 3.0f - u2x;
    float d2 = (d1 - u2x) + 1.0f;
    float d3 = u2x - d1 * 2.0f;
    float m1 = ((A - u2) + u) * T;
    float m2 = A * T;
    float dn = -d3 * inv;
    float dp = d3 * inv;
    float vx = s->vel.x, vy = s->vel.y, vz = s->vel.z;
    float ox = s->pos.x, oy = s->pos.y, oz = s->pos.z;
    V3 np(((ox * h0 + h1 * px) + vx * m1) + m2 * qx,
          ((oy * h0 + h1 * py) + vy * m1) + m2 * qy,
          ((oz * h0 + h1 * pz) + vz * m1) + m2 * qz);
    V3 nv(((ox * dn + dp * px) + vx * d2) + d1 * qx,
          ((oy * dn + dp * py) + vy * d2) + d1 * qy,
          ((oz * dn + dp * pz) + vz * d2) + d1 * qz);
    s->pos = np;
    s->vel = nv;
}

// @ 0x00a79f60
bool SnapParticleToPath(HState* s, float dt, HKeyVec* keys, V3* defPos, V3* defTan, HXform* xf)
{
    float newTime = s->time + dt;
    float endTime = s->defaultEnd;
    s->time = newTime;
    if (endTime <= newTime)
        return false;

    HKey* first = keys->mpBegin;
    HKey* last = keys->mpEnd - 1;
    HKey* cur = FindAfter(first, last, newTime);

    float px = cur->p.x, py = cur->p.y, pz = cur->p.z;
    float tx = cur->t.x, ty = cur->t.y, tz = cur->t.z;
    float keyTime = cur->time;
    float segEnd;
    if (keyTime != 0.0f) {
        if (keyTime < newTime)
            return false;
        segEnd = keyTime;
    } else {
        segEnd = endTime;
    }

    float ppx, ppy, ppz, ptx, pty, ptz, prevTime;
    if (cur > first) {
        HKey* prev = cur - 1;
        ppx = prev->p.x; ppy = prev->p.y; ppz = prev->p.z;
        ptx = prev->t.x; pty = prev->t.y; ptz = prev->t.z;
        prevTime = prev->time;
    } else {
        ppx = defPos->x; ppy = defPos->y; ppz = defPos->z;
        ptx = defTan->x; pty = defTan->y; ptz = defTan->z;
        prevTime = 0.0f;
    }

    float T = segEnd - prevTime;
    if (T > 1e-6f) {
        float inv = 1.0f / T;
        float u = (newTime - prevTime) * inv;
        float u2 = u * u;
        float A = u2 * u - u2;
        float u2x = u * 2.0f;
        float h1 = u2 - A * 2.0f;
        float h0 = 1.0f - h1;
        float d1 = u2 * 3.0f - u2x;
        float d2 = (d1 - u2x) + 1.0f;
        float d3 = u2x - d1 * 2.0f;
        float m1 = ((A - u2) + u) * T;
        float m2 = A * T;
        float dn = -d3 * inv;
        float dp = d3 * inv;
        s->pos.x = ((h0 * ppx + h1 * px) + m1 * ptx) + m2 * tx;
        s->pos.y = ((h0 * ppy + h1 * py) + m1 * pty) + m2 * ty;
        s->pos.z = ((h0 * ppz + h1 * pz) + m1 * ptz) + m2 * tz;
        s->vel.x = ((dn * ppx + dp * px) + d2 * ptx) + d1 * tx;
        s->vel.y = ((dn * ppy + dp * py) + d2 * pty) + d1 * ty;
        s->vel.z = ((dn * ppz + dp * pz) + d2 * ptz) + d1 * tz;
        xf->Transform(&s->pos);
        xf->TransformDir(&s->vel);
    }
    return true;
}

// @ 0x00a7a3b0
void FUN_00a7a3b0(void* stream, PathCmdStream* obj)
{
    ((StreamWriteFn)(*(void***)stream)[0x38 / 4])(stream, obj, 8);
    ((StreamWriteFn)(*(void***)stream)[0x38 / 4])(stream, &obj->mField08, 8);
    float v = obj->mField10;
    EA_WriteUint32(stream, &v, 1, 0);
    v = obj->mField14;
    EA_WriteUint32(stream, &v, 1, 0);
    v = obj->mField18;
    EA_WriteUint32(stream, &v, 1, 0);
    FUN_007d0250(stream, &obj->mField1c);
    *(unsigned char*)&v = obj->mField30;
    EA_StreamWrite(stream, &v, 1);
}

// @ 0x00a7a450
void FUN_00a7a450(void* stream, PathCmdTail* obj)
{
    FUN_007d0250(stream, obj);
    float v = obj->mField14;
    EA_WriteUint32(stream, &v, 1, 0);
    v = obj->mField18;
    EA_WriteUint32(stream, &v, 1, 0);
}

// @ 0x00a7a4a0
void __fastcall FUN_00a7a4a0(PathCommandObj* self, void* dummy)
{
    void* p = self->mField40;
    if (p != 0 && RefCountOf(p) != 0)
        operator_delete__(p);
    p = self->mField2c;
    if (p != 0 && RefCountOf(p) != 0)
        operator_delete__(p);
    p = self->mField18;
    if (p != 0 && RefCountOf(p) != 0)
        operator_delete__(p);
    p = self->mField04;
    if (p != 0 && RefCountOf(p) != 0)
        operator_delete__(p);
}

// @ 0x00a7a500
PathObj* __fastcall FUN_00a7a500(PathObj* self, void* dummy, unsigned a, unsigned b, unsigned c)
{
    ((AppPropsFields*)self)->ctor();
    *(volatile void**)&self->mVtbl = (void*)vtbl_ArgScript_Path;
    *(volatile unsigned*)&self->mField34 = 0xad5c3612;
    self->mField38 = 0;
    self->mField3c = 0;
    self->mField40 = 0;
    self->mField4c = 0;
    self->mField50 = 0;
    self->mField54 = 0;
    self->mField60 = 0;
    self->mField64 = 0;
    self->mField68 = 0;
    self->mField74 = 0;
    self->mField78 = 0;
    self->mField7c = 0;
    self->mField88 = a;
    self->mField8c = b;
    self->mField90 = c;
    return self;
}

// @ 0x00a7a580
void SwarmImpl::cPathCommand::OnRegister(cIParser_s00a7_a580* parser, cState_s00a7_a580* state)
{
    mState = (cPathState*)state;
    cBlockCommandBase::OnRegister(parser, state);
    SetChildState((cState_s00a7_a580*)&mChildState);
    AddCommand(kPath_01554af8, new ("ArgScript/PathPoint", 0, 0, 0, 0) cPathPointCommand());
    AddCommand(kPath_01554b00, new ("ArgScript/PathDeltaPoint", 0, 0, 0, 0) cPathDeltaPointCommand());
    AddCommand(kPath_01554b08, new ("ArgScript/PathVelocity", 0, 0, 0, 0) cPathVelocityCommand());
    AddCommand(kPath_01554b10, new ("ArgScript/PathSpeed", 0, 0, 0, 0) cPathSpeedCommand());
    AddCommand(kPath_01554b18, new ("ArgScript/PathTime", 0, 0, 0, 0) cPathTimeCommand());
    AddCommand(kPath_01554b20, new ("ArgScript/PathDeltaTime", 0, 0, 0, 0) cPathDeltaTimeCommand());
    AddCommand(kPath_01554afc, new ("ArgScript/PathPointLong", 0, 0, 0, 0) cPathPointCommand());
    AddCommand(kPath_01554b04, new ("ArgScript/PathDeltaPointLong", 0, 0, 0, 0) cPathDeltaPointCommand());
    AddCommand(kPath_01554b0c, new ("ArgScript/PathVelocityLong", 0, 0, 0, 0) cPathVelocityCommand());
    AddCommand(kPath_01554b14, new ("ArgScript/PathSpeedLong", 0, 0, 0, 0) cPathSpeedCommand());
    AddCommand(kPath_01554b1c, new ("ArgScript/PathTimeLong", 0, 0, 0, 0) cPathTimeCommand());
    AddCommand(kPath_01554b24, new ("ArgScript/PathDeltaTimeLong", 0, 0, 0, 0) cPathDeltaTimeCommand());
}

// @ 0x00a7a8a0
__declspec(noinline) SwarmImpl::cPathCommand::cPathCommand(int a, bool* b, int c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x00a7a8d0
void EA::Swarm::RegisterPathCommand(cBlockCommandBase* owner, int a, bool* b, int c)
{
    owner->AddCommand(kPath_01554af4, new ("ArgScript/Path", 0, 0, 0, 0) cPathCommand(a, b, c));
}

// @ 0x00a7a960
void* EA::Swarm::cResourceOverridesParam_Create(int n)
{
    int size = n * 0x10;
    uint32_t* p = (uint32_t*)operator new(size + 0x10, "Swarm/ResourceOverrides", 0, 0, 0, 0);
    uint32_t* q;
    if (p) {
        ((volatile uint32_t*)p)[1] = 0x13ef094;
        ((volatile uint32_t*)p)[2] = 0;
        ((volatile uint32_t*)p)[0] = 0x14582ec;
        ((volatile uint32_t*)p)[1] = 0x14188c0;
        q = p;
    } else {
        q = 0;
    }
    q[3] = (uint32_t)n;
    operator_new_array(q + 4, 0, (uint32_t)size);
    return q;
}

// @ 0x00a7a9d0
void SampleVec::DoInsertValue(cPathSample* position, const cPathSample& value)
{
    cPathSample* e = mpEnd;
    if (e != mpCapacity) {
        const cPathSample* v = &value;
        if (v >= position && v < e)
            v = v + 1;
        if (e) {
            e->pos.x = e[-1].pos.x; e->pos.y = e[-1].pos.y; e->pos.z = e[-1].pos.z;
            e->dir.x = e[-1].dir.x; e->dir.y = e[-1].dir.y; e->dir.z = e[-1].dir.z;
            e->dist  = e[-1].dist;
        }
        cPathSample* dst = mpEnd;
        cPathSample* src = dst - 1;
        while (src != position) {
            --src;
            --dst;
            *dst = *src;
        }
        *position = *v;
        mpEnd += 1;
        return;
    }
    uint32_t count = (uint32_t)(e - mpBegin);
    uint32_t newCap = count ? count * 2 : 1;
    cPathSample* p = newCap ? (cPathSample*)operator new(newCap * sizeof(cPathSample), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cPathSample* oldBegin = mpBegin;
    cPathSample* mid = vec_copy(oldBegin, position, p);
    if (mid) {
        mid->pos.x = value.pos.x; mid->pos.y = value.pos.y; mid->pos.z = value.pos.z;
        mid->dir.x = value.dir.x; mid->dir.y = value.dir.y; mid->dir.z = value.dir.z;
        mid->dist  = value.dist;
    }
    cPathSample* oldEnd = mpEnd;
    cPathSample* ne = vec_copy(position, oldEnd, mid + 1);
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
    mpBegin = p;
    mpEnd = ne;
    mpCapacity = p + newCap;
}

// @ 0x00a7ab40
void BuildPath(int count, Vector3* pts, float spdScale, cPathOpts* opts, SampleVec* out)
{
    out->erase(out->begin(), out->end());
    float dist = 0.0f;
    if (count <= 0) return;

    int lastIdx = count - 1;
    for (int i = 1; i <= count; i++) {
        int idxA = (i - 2 >= 0) ? (i - 2) : 0;
        int idxB = (i <= lastIdx) ? i : lastIdx;
        Vector3 d;
        d.x = pts[idxB].x - pts[idxA].x;
        d.y = pts[idxB].y - pts[idxA].y;
        d.z = pts[idxB].z - pts[idxA].z;
        float sc = opts->mScale;
        if (sc != kOne_01485720) {
            float inv = kOne_01485720 / sc;
            d.x *= inv; d.y *= inv; d.z *= inv;
        }
        if (opts->mFlags & 2) {
            Vector3 t;
            t.x = d.x * opts->mRow0.x + d.y * opts->mRow0.y + d.z * opts->mRow0.z;
            t.y = d.x * opts->mRow1.x + d.y * opts->mRow1.y + d.z * opts->mRow1.z;
            t.z = d.x * opts->mRow2.x + d.y * opts->mRow2.y + d.z * opts->mRow2.z;
            d = t;
        }
        Vector3 delta;
        delta.x = pts[i - 1].x - opts->mOffset.x;
        delta.y = pts[i - 1].y - opts->mOffset.y;
        delta.z = pts[i - 1].z - opts->mOffset.z;
        float len = (float)sqrt(d.y * d.y + d.z * d.z + d.x * d.x);
        if (sc != kOne_01485720) {
            float inv = kOne_01485720 / sc;
            delta.x *= inv; delta.y *= inv; delta.z *= inv;
        }
        if (opts->mFlags & 2) {
            Vector3 t;
            t.x = delta.x * opts->mRow0.x + delta.y * opts->mRow0.y + delta.z * opts->mRow0.z;
            t.y = delta.x * opts->mRow1.x + delta.y * opts->mRow1.y + delta.z * opts->mRow1.z;
            t.z = delta.x * opts->mRow2.x + delta.y * opts->mRow2.y + delta.z * opts->mRow2.z;
            delta = t;
        }
        Vector3 dir;
        dir.x = gDirDef_016770dc;
        dir.y = gDirDef_016770e0;
        dir.z = gDirDef_016770e4;
        if (len > kEps_013f11c8) {
            float s = spdScale / len;
            dir.x = d.x * s;
            dir.y = d.y * s;
            dir.z = d.z * s;
        }
        if (i != 1) {
            Vector3 dd;
            dd.x = pts[i - 1].x - pts[i - 2].x;
            dd.y = pts[i - 1].y - pts[i - 2].y;
            dd.z = pts[i - 1].z - pts[i - 2].z;
            dist += (float)sqrt(dd.z * dd.z + dd.y * dd.y + dd.x * dd.x) / spdScale;
        }
        cPathSample s;
        s.pos = delta;
        s.dir = dir;
        s.dist = dist;
        out->push_back(s);
    }
}

// @ 0x00a7af50
namespace SwarmImpl {
void cPathPointCommand::Execute(cArguments_s00a7_a580* args)
{
    mState->mPositions.push_back(mParser->ParseVector3(args->MainArguments(1)[0]));
}
}  // namespace SwarmImpl

// @ 0x00a7afc0
namespace SwarmImpl {
void cPathDeltaPointCommand::Execute(cArguments_s00a7_a580* args)
{
    Vector3 v = mParser->ParseVector3(args->MainArguments(1)[0]);
    Vec<Vector3>& pos = mState->mPositions;
    if (pos.begin() == pos.end()) {
        pos.push_back(v);
    } else {
        const Vector3& last = pos.end()[-1];
        Vector3 t;
        t.x = last.x + v.x;
        t.y = last.y + v.y;
        t.z = last.z + v.z;
        pos.push_back(t);
    }
}
}  // namespace SwarmImpl

// @ 0x00a7b0d0
namespace SwarmImpl {
void cPathVelocityCommand::Execute(cArguments_s00a7_a580* args)
{
    mState->mDeltaPositions.push_back(mParser->ParseVector3(args->MainArguments(1)[0]));
}
}  // namespace SwarmImpl

// @ 0x00a7b140
namespace SwarmImpl {
void cPathSpeedCommand::Execute(cArguments_s00a7_a580* args)
{
    float v = mParser->ParseFloat(args->MainArguments(1)[0]);
    mState->mSpeeds.push_back(v);
}
}  // namespace SwarmImpl

// @ 0x00a7b1a0
namespace SwarmImpl {
void cPathTimeCommand::Execute(cArguments_s00a7_a580* args)
{
    float v = mParser->ParseFloat(args->MainArguments(1)[0]);
    mState->mTimes.push_back(v);
}
}  // namespace SwarmImpl

// @ 0x00a7b200
namespace SwarmImpl {
void cPathDeltaTimeCommand::Execute(cArguments_s00a7_a580* args)
{
    float v = mParser->ParseFloat(args->MainArguments(1)[0]);
    VecF& times = mState->mTimes;
    if (times.begin() == times.end()) {
        times.push_back(0.0f);
        times.push_back(v);
    } else {
        float t = times.end()[-1] + v;
        times.push_back(t);
    }
}
}  // namespace SwarmImpl

// @ 0x00a7b2d0
void SwarmImpl::cPathCommand::Execute(cArguments_s00a7_a580* args)
{
    args->MainArguments(0);
    *mChildState.mTractor = args->HasFlag("tractor");
    mChildState.mPositions.erase(mChildState.mPositions.begin(), mChildState.mPositions.end());
    mChildState.mDeltaPositions.erase(mChildState.mDeltaPositions.begin(), mChildState.mDeltaPositions.end());
    mChildState.mSpeeds.erase(mChildState.mSpeeds.begin(), mChildState.mSpeeds.end());
    mChildState.mTimes.erase(mChildState.mTimes.begin(), mChildState.mTimes.end());
    mParser->StartBlock((cIBlockCommand_s00a7_a580*)this);
}

// @ 0x00a7b370
void PathBuilder::Build(bool skip)
{
    if (skip) return;
    int n = (int)(mPoints.mpEnd - mPoints.mpBegin);
    int nTan = (int)(mTangents.mpEnd - mTangents.mpBegin);
    int nWidth = (int)(mWidths.mpEnd - mWidths.mpBegin);
    int nParam = (int)(mParams.mpEnd - mParams.mpBegin);
    bool normalize = false;

    if (nParam == 0) {
        if (nWidth == 1) {
            float total = 0.0f;
            for (int i = 1; i < n; ++i)
                total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
            float v = total / mWidths.mpBegin[0];
            mParams.push_back(v);
            normalize = true;
        } else {
            float zero = 0.0f;
            mParams.push_back(zero);
            float acc = 0.0f;
            for (int i = 1; i < n; ++i) {
                Vec3 d;
                d.x = mPoints.mpBegin[i].x - mPoints.mpBegin[i - 1].x;
                d.y = mPoints.mpBegin[i].y - mPoints.mpBegin[i - 1].y;
                d.z = mPoints.mpBegin[i].z - mPoints.mpBegin[i - 1].z;
                float w = (mWidths.mpBegin[i - 1] + mWidths.mpBegin[i]) * 0.5f;
                if (w > 0.0f)
                    acc = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) / w + acc;
                mParams.push_back(acc);
            }
        }
    } else if (nParam == 1) {
        normalize = true;
    }

    if (normalize && n > 1) {
        float last = mParams.mpEnd[-1];
        float total = 0.0f;
        for (int i = 1; i < n; ++i)
            total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
        mParams.mpBegin[0] = 0.0f;
        float acc = 0.0f;
        float inv = 1.0f / total;
        for (int i = 1; i < n; ++i) {
            acc += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
            float v = inv * acc * last;
            mParams.push_back(v);
        }
    }

    if (nWidth == 0 && nTan == 0) {
        float last = mParams.mpEnd[-1];
        float total = 0.0f;
        for (int i = 1; i < n; ++i)
            total += SegLen(mPoints.mpBegin[i], mPoints.mpBegin[i - 1]);
        float w;
        if (last > 0.0f) w = total / last;
        else w = 0.0f;
        mWidths.push_back(w);
        nWidth = 1;
    }

    mpOut->erase(mpOut->mpBegin, mpOut->mpEnd);
    for (int i = 0; i < n; ++i) {
        Vertex v;
        v.pos = mPoints.mpBegin[i];
        v.param = mParams.mpBegin[i];
        if (nWidth > 0) {
            float w = (nWidth > 1) ? mWidths.mpBegin[i] : mWidths.mpBegin[0];
            int ia = Max(i - 1, 0);
            int ib = Min(i + 1, n - 1);
            Vec3 d;
            d.x = mPoints.mpBegin[ib].x - mPoints.mpBegin[ia].x;
            d.y = mPoints.mpBegin[ib].y - mPoints.mpBegin[ia].y;
            d.z = mPoints.mpBegin[ib].z - mPoints.mpBegin[ia].z;
            float len = sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
            if (len > 1e-6f) {
                float s = w / len;
                v.dir.x = d.x * s;
                v.dir.y = d.y * s;
                v.dir.z = d.z * s;
            } else {
                v.dir = kDefaultDir;
            }
        } else if (nTan > 0) {
            const Vec3& t = (nTan > 1) ? mTangents.mpBegin[i] : mTangents.mpBegin[0];
            v.dir = t;
        }
        VertexVec* out = mpOut;
        Vertex* p = out->mpEnd;
        if (p < out->mpCapacity) {
            out->mpEnd = p + 1;
            if (p) *p = v;
        } else {
            out->PushSlow(p, &v);
        }
    }
    *mpDone = true;
}
