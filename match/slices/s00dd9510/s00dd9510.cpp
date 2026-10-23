// Slice s00dd9510 -- 0x0ddxxxx region: the Swarm boid container and its Boid
// elements.  A Swarm is a vector<Boid*> (mpBegin/mpEnd) plus a manager pointer;
// each Boid carries position/orientation vectors, a 5-row matrix at +0x48, a
// Stopwatch at +0xb0 and assorted state words.
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (default /GS on).

#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Vec4 { float x, y, z, w; };

union LARGE_INTEGER {
    struct { unsigned int LowPart; int HighPart; } u;
    long long QuadPart;
};

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount);
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// acos helper (0x011e08c8), argument and result in st0.
extern "C" double __cdecl acos(double);                          // 0x011e08c8
// 0x00571f80 (cdecl): (soundId, objectId, x, y, z) -- name/vol first, then position.
extern "C" void __cdecl Start3dSoundByName(unsigned int soundId, unsigned int objectId,
                                           float x, float y, float z);
// 0x00dd91b0 -- rotation builder: axis in ecx, vector in eax, out written through esi (register
// ABI, not expressible in C, so FUN_00dd9c10 cannot be byte-exact).
extern "C" Vec4* MakeRotation(const Vec3* axis, const Vec3* in, Vec4* out);

// Tuning globals copied by the Boid constructor / used by the update methods.
extern float gf_15a2d2c, gf_15a2d30, gf_15a2d34, gf_15a2d38;
extern Vec4  g_m48;                                              // 0x015a2d2c (aliases the four above)
extern char  g_16a0b04;                                          // 0x016a0b04
extern float g_16a1078;                                          // 0x016a1078
extern float g_15a2cec;                                          // 0x015a2cec
extern float g_16a0ba4, g_16a0ba8, g_16a0bac;                    // 0x016a0ba4 (Vec3 axis)
extern float g_16a0b0c, g_16a0b10, g_16a0b14;                    // 0x016a0b0c (Vec3)

// Timer block embedded at +0xb0 of every Boid; overlaps EA::Stopwatch.
struct Timer {
    unsigned int mLo;      // +0x00 (element +0xb0)
    unsigned int mHi;      // +0x04
    unsigned int mZ1;      // +0x08
    unsigned int mZ2;      // +0x0c
    int mMode;             // +0x10 (element +0xc0)
    float mfCoef;          // +0x14 (element +0xc4)
};

// EA::Stopwatch overlaps the timer block; only the elapsed-time accessor and the
// restart entry point are modelled.
namespace EA {
class Stopwatch {
public:
    unsigned __int64 mnStartTime;                // +0x00
    unsigned __int64 mnTotalElapsedTime;         // +0x08
    int mnUnits;                                 // +0x10
    float mfCoefficient;                         // +0x14
    Stopwatch(int units, bool useCycles);        // 0x0093a560
    void Restart();                              // 0x00571e80
    long long GetElapsedTimeFloat();
};
}

// Element object (0x100 bytes).
struct Boid {
    void*  mResA;          // +0x00
    void*  mResB;          // +0x04
    void*  mEffect;        // +0x08
    Vec3   mPos;           // +0x0c
    Vec3   mV18;           // +0x18
    Vec3   mV24;           // +0x24
    Vec3   mV30;           // +0x30
    Vec3   mV3C;           // +0x3c
    Vec4   mM48[5];        // +0x48
    float  m98;            // +0x98
    float  m9C;            // +0x9c
    float  mA0;            // +0xa0
    float  mA4;            // +0xa4
    float  mA8;            // +0xa8
    int    mAC;            // +0xac
    Timer  mTimer;         // +0xb0
    int    mC8;            // +0xc8
    int    mCC;            // +0xcc
    int    mD0;            // +0xd0
    char   mD4;            // +0xd4
    char   mD5;            // +0xd5
    char   mD6;            // +0xd6
    char   mD7;            // +0xd7
    char   mD8;            // +0xd8
    char   mD9[3];         // +0xd9
    float  mDC;            // +0xdc
    float  mE0;            // +0xe0
    float  mE4;            // +0xe4
    float  mE8;            // +0xe8
    float  mEC;            // +0xec
    float  mF0;            // +0xf0
    int    mF4;            // +0xf4
    int    mF8;            // +0xf8
    int    mFC;            // +0xfc

    Boid();                                                          // 0x00dd9510
};

// Container: vector<Boid*> with a manager pointer at +0x14.
struct Swarm {
    Boid** mpBegin;        // +0x00
    Boid** mpEnd;          // +0x04
    Boid** mpCapacity;     // +0x08
    int    pad0C[2];       // +0x0c
    void*  mpMgr;          // +0x14

    int   FUN_00dda060(int id);                                      // 0x00dda060
    void  FUN_00dda090(int id, char v);                              // 0x00dda090
    void  FUN_00dda0d0(int id);                                      // 0x00dda0d0
    void  FUN_00dd9750(Boid* e);                                     // 0x00dd9750
    int   FUN_00dda380();                                            // 0x00dda380
    bool  FUN_00dd97a0(Boid* p, int unused);                         // 0x00dd97a0
    bool  FUN_00dd9860(Boid* b, int unused);                         // 0x00dd9860
    void  FUN_00dd9a10(Boid* b);                                     // 0x00dd9a10
    bool  FUN_00dd9c10(Boid* b, int unused);                         // 0x00dd9c10
    float FUN_00dda160(const Vec3* p, int group);                    // 0x00dda160
};

// @ 0x00dda060 -- FUN_00dda060
// Counts the elements whose +0xfc field equals `id`.
int Swarm::FUN_00dda060(int id) {
    int n = 0;
    Boid** p = mpBegin;
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    if (c > 0) {
        do {
            if ((*p)->mFC == id) {
                ++n;
            }
            ++p;
            --c;
        } while (c != 0);
    }
    return n;
}

// @ 0x00dda380 -- FUN_00dda380
// Counts the elements whose +0xc8 field equals 100.
int Swarm::FUN_00dda380() {
    int n = 0;
    Boid** p = mpBegin;
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    if (c > 0) {
        do {
            if ((*p)->mC8 == 100) {
                ++n;
            }
            ++p;
            --c;
        } while (c != 0);
    }
    return n;
}

// @ 0x00dda090 -- FUN_00dda090
// Writes the byte `v` to +0xd8 of every element whose +0xfc field equals `id`.
void Swarm::FUN_00dda090(int id, char v) {
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    unsigned int i = 0;
    if (c > 0) {
        do {
            Boid* e = mpBegin[i];
            if (e->mFC == id) {
                e->mD8 = v;
            }
            ++i;
        } while (i < c);
    }
}

// @ 0x00dda0d0 -- FUN_00dda0d0
// For every element whose +0xfc field equals `id`: sets +0xd5, restarts its
// timer block (CPU cycles or QueryPerformanceCounter depending on +0xc0) and
// clears the two trailing dwords.
void Swarm::FUN_00dda0d0(int id) {
    int zero = 0;
    unsigned int i = 0;
    unsigned int c = (unsigned int)(mpEnd - mpBegin);
    if (c > zero) {
        do {
            Boid* e = mpBegin[i];
            if (e->mFC == id) {
                e->mD5 = 1;
                Timer* w = &mpBegin[i]->mTimer;
                if (w->mMode == 1) {
                    unsigned long long t = __rdtsc();
                    w->mLo = (unsigned int)t;
                    w->mHi = (unsigned int)(t >> 32);
                } else {
                    LARGE_INTEGER li;
                    QueryPerformanceCounter(&li);
                    w->mLo = li.u.LowPart;
                    w->mHi = (unsigned int)li.u.HighPart;
                }
                w->mZ1 = zero;
                w->mZ2 = zero;
            }
            ++i;
        } while (i < c);
    }
}

// @ 0x00dd9750 -- FUN_00dd9750
// Restarts the timer block of `e` (low word plus the trailing dwords), keeping
// the high word for the store after the two zeroing stores.
void Swarm::FUN_00dd9750(Boid* e) {
    LARGE_INTEGER li;
    if (e->mTimer.mMode == 1) {
        li.QuadPart = (long long)__rdtsc();
        e->mTimer.mLo = li.u.LowPart;
    } else {
        QueryPerformanceCounter(&li);
        e->mTimer.mLo = li.u.LowPart;
    }
    e->mTimer.mZ2 = 0;
    e->mTimer.mZ1 = 0;
    e->mTimer.mHi = (unsigned int)li.u.HighPart;
}

// @ 0x00dd97a0 -- FUN_00dd97a0
// Initialises the six float slots at +0x18 and the four copied dwords at +0x68,
// then raises the shared byte flag once the scaled stopwatch reading passes
// one second.
bool Swarm::FUN_00dd97a0(Boid* p, int unused) {
    bool r = true;
    p->mV18 = Vec3(0.0f, 0.0f, 0.0f);
    p->mV24 = Vec3(0.0f, 0.0f, 0.0f);
    p->mM48[2] = g_m48;
    EA::Stopwatch* w = (EA::Stopwatch*)&p->mTimer;
    if ((double)w->GetElapsedTimeFloat() * w->mfCoefficient > 1.0) {
        g_16a0b04 = r;
    }
    return r;
}

// @ 0x00dd9510 -- Boid::Boid
// Element constructor: clears the leading pointers and the fifteen-float block,
// stamps five copies of the four tuning globals over +0x48, starts the stopwatch
// and finishes with the trailing scalars.  Returns `this`.
Boid::Boid() {
    int zero = 0;
    mResA = (void*)zero;
    mResB = (void*)zero;
    mEffect = (void*)zero;
    mPos.x = 0.0f; mPos.y = 0.0f; mPos.z = 0.0f;
    mV18.x = 0.0f; mV18.y = 0.0f; mV18.z = 0.0f;
    mV24.x = 0.0f; mV24.y = 0.0f; mV24.z = 0.0f;
    mV30.x = 0.0f; mV30.y = 0.0f; mV30.z = 0.0f;
    mV3C.x = 0.0f; mV3C.y = 0.0f; mV3C.z = 0.0f;
    mM48[0].x = gf_15a2d2c;
    mM48[0].y = gf_15a2d30;
    mM48[0].z = gf_15a2d34;
    mM48[0].w = gf_15a2d38;
    mM48[1].x = gf_15a2d2c;
    mM48[1].y = gf_15a2d30;
    mM48[1].z = gf_15a2d34;
    mM48[1].w = gf_15a2d38;
    mM48[2].x = gf_15a2d2c;
    mM48[2].y = gf_15a2d30;
    mM48[2].z = gf_15a2d34;
    mM48[2].w = gf_15a2d38;
    mM48[3].x = gf_15a2d2c;
    mM48[3].y = gf_15a2d30;
    mM48[3].z = gf_15a2d34;
    mM48[3].w = gf_15a2d38;
    mM48[4].x = gf_15a2d2c;
    mM48[4].y = gf_15a2d30;
    mM48[4].z = gf_15a2d34;
    mM48[4].w = gf_15a2d38;
    float one = 1.0f;
    m98 = one;
    m9C = 0.0f;
    mA0 = 0.0f;
    mA4 = 0.0f;
    mA8 = one;
    ((EA::Stopwatch*)&mTimer)->Stopwatch::Stopwatch(zero, false);
    mC8 = zero;
    mCC = zero;
    mD0 = zero;
    mD4 = (char)zero;
    mD5 = (char)zero;
    mD6 = (char)zero;
    mD7 = (char)zero;
    mD8 = (char)zero;
    mDC = 0.0f;
    mE0 = 0.0f;
    mE4 = 0.0f;
    mE8 = 0.0f;
    mEC = one;
    mF0 = 0.0f;
    mF4 = zero;
    mF8 = zero;
    mFC = 3;
}

// @ 0x00dd9860 -- FUN_00dd9860
// Distance/heading update for one boid.  Restarts the stopwatch and returns
// false while the boid is closer than 10 units to its +0x30 anchor; otherwise
// refreshes the +0x24 offset, the +0x98 gain and returns true.
bool Swarm::FUN_00dd9860(Boid* b, int unused) {
    bool r = true;
    float dx = b->mV30.x - b->mPos.x;
    float dy = b->mV30.y - b->mPos.y;
    float dz = b->mV30.z - b->mPos.z;
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
    if (10.0f > dist) {
        b->mC8 = 3;
        ((EA::Stopwatch*)&b->mTimer)->Restart();
        r = false;
    }
    float f = 0.5f;
    if (b->mFC == 0) {
        f = 0.2f;
    }
    b->mV24.x = ((b->mV3C.x + b->mV30.x) * 0.5f - b->mPos.x) * f;
    b->mV24.y = ((b->mV3C.y + b->mV30.y) * 0.5f - b->mPos.y) * f;
    b->mV24.z = ((b->mV3C.z + b->mV30.z) * 0.5f - b->mPos.z) * f;

    float ax = b->mV3C.x - b->mV30.x;
    float ay = b->mV3C.y - b->mV30.y;
    float az = b->mV3C.z - b->mV30.z;
    float t = 1.0f - dist / sqrtf((az * az + ay * ay) + ax * ax);

    if (b->mFC != 0) {
        float f3 = g_16a1078;
        if (b->mD6 != b->mD7) {
            f3 = 0.05f;
        }
        b->m98 = 1.0f;
        if (f3 <= t) {
            if ((1.0f - f3 < t) && b->mD7 != 0) {
                b->m98 = (1.0f - (t - (1.0f - f3)) / f3) * 0.8f + 0.2f;
            }
        } else if (b->mD6 != 0) {
            b->m98 = (t / f3) * 0.8f + 0.2f;
            b->m98 = b->m98 * 5.0f;
            return r;
        }
        t = b->m98;
    }
    b->m98 = t * 5.0f;
    return r;
}

// @ 0x00dd9a10 -- FUN_00dd9a10
// Recomputes the two vector lengths at +0x9c/+0xa0 and the heading angle at
// +0xa4, clamps the angle away from zero, then fires the 3D sound.
void Swarm::FUN_00dd9a10(Boid* b) {
    b->m9C = sqrtf((b->mV3C.x * b->mV3C.x + b->mV3C.y * b->mV3C.y) + b->mV3C.z * b->mV3C.z);
    b->mA0 = sqrtf((b->mV30.x * b->mV30.x + b->mV30.y * b->mV30.y) + b->mV30.z * b->mV30.z);

    float px = b->mPos.x, py = b->mPos.y, pz = b->mPos.z;
    float ax = b->mV30.x, ay = b->mV30.y, az = b->mV30.z;
    float inv1 = 1.0f / sqrtf((px * px + py * py) + pz * pz + 1e-08f);
    float inv2 = 1.0f / sqrtf((ax * ax + ay * ay) + az * az + 1e-08f);
    float nx1 = px * inv1, ny1 = py * inv1, nz1 = pz * inv1;
    float nx2 = ax * inv2, ny2 = ay * inv2, nz2 = az * inv2;

    float cross = nx1 * ny2 - ny1 * nx2;
    float dot = (nx1 * nx2 + ny1 * ny2) + nz1 * nz2;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    float ang = (float)acos(dot);
    b->mA4 = ang;
    if (cross < 0.0f) {
        b->mA4 = -ang;
    }
    if (fabsf(b->mA4) < 0.01f) {
        b->mA4 = (b->mA4 >= 0.0f) ? 0.01f : -0.01f;
    }

    Start3dSoundByName(0x44f21a5d, (unsigned int)b->mD0, b->mPos.x, b->mPos.y, b->mPos.z);
}

// @ 0x00dd9c10 -- FUN_00dd9c10
// Full boid orientation update: normalises the position and anchor vectors,
// computes the heading, blends the position along the anchor direction, rebuilds
// the rotation from the axis pair, then refreshes the +0x98 gain.  Returns
// false when the heading is far out of range.
bool Swarm::FUN_00dd9c10(Boid* b, int unused) {
    b->mV24.x = g_16a0b0c;
    b->mV24.y = g_16a0b10;
    b->mV24.z = g_16a0b14;

    float px = b->mPos.x, py = b->mPos.y, pz = b->mPos.z;
    float inv1 = 1.0f / sqrtf((px * px + py * py) + pz * pz + 1e-08f);
    float ux = px * inv1;
    float uy = py * inv1;
    float uz = pz * inv1;

    float ax = b->mV30.x, ay = b->mV30.y, az = b->mV30.z;
    float inv2 = 1.0f / sqrtf((az * az + ay * ay) + ax * ax + 1e-08f);
    float wx = ax * inv2;
    float wy = ay * inv2;
    float wz = az * inv2;

    float cross = wy * ux - uy * wx;
    float dot = (wx * ux + wy * uy) + wz * uz;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    float ang = (float)acos(dot);
    if (cross < 0.0f) {
        ang = -ang;
    }

    float t = 1.0f - ang / b->mA4;
    float blend = (b->mA0 - b->m9C) * t + b->m9C;
    b->mPos.x = ux * blend;
    b->mPos.y = uy * blend;
    b->mPos.z = uz * blend;

    float e = b->mA4 * 0.5f;
    e = (ang - e) / e;
    if (e > 0.99f) {
        e = 0.99f;
    } else if (e < -1.0f) {
        b->mV18.x = g_16a0b0c;
        b->mV18.y = g_16a0b10;
        b->mV18.z = g_16a0b14;
        return false;
    }
    float s = 1.0f - fabsf(e);
    s = (s > 0.0f) ? sqrtf(s) : -sqrtf(-s);
    if (s >= 0.0f && s < 0.1f) {
        s = 0.1f;
    } else if (s <= 0.0f && -0.1f < s) {
        s = -0.1f;
    }

    float c1 = uz * g_16a0ba8 - uy * g_16a0bac;
    float c2 = uy * g_16a0ba4 - ux * g_16a0ba8;
    float c3 = ux * g_16a0bac - uz * g_16a0ba4;
    float inv3 = 1.0f / sqrtf((c3 * c3 + c2 * c2) + c1 * c1 + 1e-08f);
    float r1 = c1 * inv3;
    float r2 = c2 * inv3;
    float r3 = c3 * inv3;
    if (cross < 0.0f) {
        r1 = -r1;
        r2 = -r2;
        r3 = -r3;
    }
    b->mV18.x = (r1 * g_15a2cec) * s;
    b->mV18.y = (r3 * g_15a2cec) * s;
    b->mV18.z = (r2 * g_15a2cec) * s;

    Vec4 out;
    Vec4* q = MakeRotation((const Vec3*)&g_16a0ba4, &b->mV18, &out);
    b->mM48[0] = *q;

    if (g_16a1078 <= t) {
        float g = 1.0f;
        if (1.0f - g_16a1078 < t) {
            g = 1.0f - (t - (1.0f - g_16a1078)) / g_16a1078;
        }
        b->m98 = g;
    } else {
        b->m98 = t / g_16a1078;
    }
    b->m98 = b->m98 * 5.0f;
    return true;
}

// @ 0x00dda160 -- FUN_00dda160
// Nearest squared distance from `p` to a boid whose +0xfc field equals `group`.
float Swarm::FUN_00dda160(const Vec3* p, int group) {
    float best = -1.0f;
    unsigned int n = (unsigned int)(mpEnd - mpBegin);
    unsigned int i = 0;
    for (; i < n; ++i) {
        Boid* e = mpBegin[i];
        if (e->mFC == group) {
            float dy = e->mPos.y - p->y;
            float dx = e->mPos.x - p->x;
            float dz = e->mPos.z - p->z;
            float d2 = (dx * dx + dy * dy) + dz * dz;
            if (d2 < best || best < 0.0f) {
                best = d2;
            }
        }
    }
    return sqrtf(best);
}
