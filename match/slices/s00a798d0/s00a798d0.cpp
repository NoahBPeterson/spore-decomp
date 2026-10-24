// Slice s00a798d0: Hermite keyframe-spline step. Finds the first key whose time is after the
// state's time (4x-unrolled search over keys[0 .. n-1)), transforms the key position and tangent
// by an optional Transform (rotation flag 2, scale, offset), optionally rewinds the state when the
// remaining distance is too large for the max speed, and advances position/velocity by dt along
// the cubic Hermite basis.  Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (to be confirmed by chk).
#include <math.h>
#include "types.h"

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

// @ 0x00A798D0
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

// =====================================================================
// 0x00a79f60  EA::Swarm::SnapParticleToPath
// =====================================================================
// @ 0x00a79f60
bool SnapParticleToPath(HState* s, float dt, HKeyVec* keys, V3* defPos,
                        V3* defTan, HXform* xf)
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

// =====================================================================
// 0x00a7a3b0  path-command serializer (two 8-byte blocks + 3 floats + tail)
// =====================================================================
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

extern "C" void FUN_007d0250(void* stream, void* obj);                       // 0x7d0250
extern "C" void EA_WriteUint32(void* stream, const void* data, int count, int flags); // 0x93aa70
extern "C" void EA_StreamWrite(void* stream, const void* data, int count);   // 0x93a9a0

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

// =====================================================================
// 0x00a7a450  path-command serializer (tail + two floats)
// =====================================================================
struct PathCmdTail {
    char  mPad00[0x14];     // +0x00..0x13
    float mField14;         // +0x14
    float mField18;         // +0x18
};

// @ 0x00a7a450
void FUN_00a7a450(void* stream, PathCmdTail* obj)
{
    FUN_007d0250(stream, obj);
    float v = obj->mField14;
    EA_WriteUint32(stream, &v, 1, 0);
    v = obj->mField18;
    EA_WriteUint32(stream, &v, 1, 0);
}

// =====================================================================
// 0x00a7a4a0  cPathCommand destructor (release four ref-counted blocks)
// =====================================================================
struct RefCountHeader {
    unsigned mRefCount;     // stored immediately before the payload
};

static inline unsigned RefCountOf(void* payload)
{
    return reinterpret_cast<RefCountHeader*>(payload)[-1].mRefCount;
}

extern "C" void operator_delete__(void* p);   // 0xf47380

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

// =====================================================================
// 0x00a7a500  ArgScript::Path / cPathCommand::cPathState constructor
// =====================================================================
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

extern const unsigned vtbl_ArgScript_Path[];

// @ 0x00a7a500
PathObj* __fastcall FUN_00a7a500(PathObj* self, void* dummy,
                                 unsigned a, unsigned b, unsigned c)
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
