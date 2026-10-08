// Slice s00a99640: constructor of a Swarm-style effect parameter block (retail size ~0x2c0, vtable 0x01458aec)
// @ 0x00a99b20 (Claude-coined name: cEffectParams::cEffectParams).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc), same as the Swarm region 0xa77c80-0xa7c5xx.
//
// Sets ~170 members to their defaults (0, +-1, 2.0, 5.0, +-10000, -1e9, 0.25, ... and the three words of
// two global Vec3 constants), then seeds six one-element curve vectors (SimpleVector<float>, 0x14 bytes in retail)
// and one Vec3 vector.
#include "types.h"
inline void* operator new(size_t, void* p) { return p; }

struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
};
extern Vec3f g_vec3_01678e1c;     // 0x01678e1c (runtime-initialised constant, copied per word)
extern Vec3f g_vec3_01678dd0;     // 0x01678dd0

// eastl::vector<float, sp_vector_allocator> as laid out in retail (5 words)
struct FloatVec {
    float* mpBegin; float* mpEnd; float* mpCapacity; const char* mpName; int mpExtra;
    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void DoInsertValue(float* pos, const float& v);     // 0x00455660 (ret 8)
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { float* p = mpEnd; mpEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mpEnd, v);
    }
};

struct Vec3Vec {
    Vec3f* mpBegin; Vec3f* mpEnd; Vec3f* mpCapacity; const char* mpName; int mpExtra;
    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void DoInsertValue(Vec3f* pos, const Vec3f& v);     // 0x007ed1b0 (ret 8)
    void push_back(const Vec3f& v)
    {
        if (mpEnd < mpCapacity) { Vec3f* p = mpEnd; mpEnd = p + 1; if (p) new (p) Vec3f(v); }
        else DoInsertValue(mpEnd, v);
    }
};

struct cRefBase {
    virtual ~cRefBase();
    int   mRefCount;                    // +0x04
    cRefBase() : mRefCount(0) {}
};

struct cEffectParams : cRefBase {
    virtual ~cEffectParams();
    int   i08, i0c;
    float f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c, f40;
    float f44, f48, f4c, f50, f54, f58, f5c, f60, f64;
    FloatVec v68;                       // +0x68
    float f7c;
    int   i80;
    FloatVec v84;                       // +0x84
    float f98;
    FloatVec v9c;                       // +0x9c
    FloatVec vb0;                       // +0xb0
    FloatVec vc4;                       // +0xc4
    float fd8, fdc, fe0, fe4, fe8, fec;
    Vec3Vec vf0;                        // +0xf0
    Vec3f v104;                         // +0x104
    FloatVec v110;                      // +0x110
    float f124;
    int   i128, i12c, i130;
    char  b134;
    char  pad135[3];
    Vec3f v138, v144;
    float f150, f154, f158;
    Vec3f v15c;
    float f168, f16c;
    int   i170, i174, i178;
    char  pad17c[8];
    char  b184, b185, b186, b187;
    int   i188, i18c, i190;
    char  pad194[8];
    int   i19c, i1a0, i1a4;
    char  pad1a8[8];
    int   i1b0, i1b4, i1b8;
    char  pad1bc[8];
    float f1c4, f1c8, f1cc, f1d0, f1d4, f1d8, f1dc, f1e0, f1e4;
    int   i1e8, i1ec, i1f0, i1f4, i1f8, i1fc;
    float f200, f204, f208, f20c, f210, f214, f218;
    int   i21c, i220, i224;
    char  pad228[8];
    char  b230;
    char  pad231[3];
    float f234, f238, f23c, f240, f244, f248, f24c;
    int   i250, i254, i258;
    char  pad25c[8];
    char  b264;
    char  pad265[3];
    Vec3f v268;
    float f274, f278, f27c;
    Vec3f v280;
    int   i28c, i290, i294;
    char  pad298[8];
    float f2a0, f2a4;
    int   i2a8, i2ac, i2b0;
    char  pad2b4[8];
    float f2bc;

    cEffectParams();
};

// @ 0x00a99b20
cEffectParams::cEffectParams()
{
    i08 = 0; i0c = 0;
    f10 = 2.0f; f14 = 2.0f; f18 = 0.0f;
    f1c = -1.0f; f20 = -1.0f; f24 = -1.0f; f28 = -1.0f;
    f2c = 0.0f; f30 = 0.0f; f34 = 1.0f; f38 = 0.0f; f3c = 0.0f; f40 = 1.0f;
    f44 = 0.0f; f48 = 0.0f; f4c = 0.0f; f50 = 0.0f; f54 = 0.0f; f58 = 0.0f; f5c = 0.0f; f60 = 0.0f;
    f64 = -1.0f;
    v68.Init();
    f7c = 1.0f;
    i80 = 0;
    v84.Init();
    f98 = 0.0f;
    v9c.Init(); vb0.Init(); vc4.Init();
    fd8 = 0.0f; fdc = 0.0f; fe0 = 0.0f; fe4 = 0.0f; fe8 = 0.0f; fec = 0.0f;
    vf0.Init();
    v104.x = g_vec3_01678e1c.x; v104.y = g_vec3_01678e1c.y; v104.z = g_vec3_01678e1c.z;
    v110.Init();
    f124 = 0.0f;
    i128 = -1; i12c = 0; i130 = -1;
    b134 = 0;
    v138.x = g_vec3_01678e1c.x; v138.y = g_vec3_01678e1c.y; v138.z = g_vec3_01678e1c.z;
    v144.x = g_vec3_01678e1c.x; v144.y = g_vec3_01678e1c.y; v144.z = g_vec3_01678e1c.z;
    f150 = 0.0f; f154 = 0.0f; f158 = 0.0f;
    v15c.x = g_vec3_01678e1c.x; v15c.y = g_vec3_01678e1c.y; v15c.z = g_vec3_01678e1c.z;
    f168 = 0.0f; f16c = 0.0f;
    i170 = 0; i174 = 0; i178 = 0;
    b184 = 0; b185 = (char)0xff; b186 = 0; b187 = (char)0xff;
    i188 = 0; i18c = 0; i190 = 0;
    i19c = 0; i1a0 = 0; i1a4 = 0;
    i1b0 = 0; i1b4 = 0; i1b8 = 0;
    f1d8 = -1000000000.0f;
    f1c4 = 1.0f; f1c8 = 0.0f; f1cc = 0.0f; f1d0 = 0.0f; f1d4 = 0.0f;
    f1dc = 0.0f; f1e0 = -10000.0f; f1e4 = 10000.0f;
    i1e8 = -1; i1ec = -1; i1f0 = -1; i1f4 = -1; i1f8 = -1; i1fc = -1;
    f200 = 5.0f; f204 = 5.0f; f208 = 0.0f; f20c = 0.0f; f210 = 0.25f; f214 = 0.0f; f218 = 0.0f;
    i21c = 0; i220 = 0; i224 = 0;
    f234 = 5.0f; f238 = 5.0f;
    b230 = 2;
    f23c = 0.0f; f240 = 0.0f; f244 = 0.25f; f248 = 0.0f; f24c = 0.0f;
    i250 = 0; i254 = 0; i258 = 0;
    b264 = 2;
    v268.x = g_vec3_01678e1c.x; v268.y = g_vec3_01678e1c.y; v268.z = g_vec3_01678e1c.z;
    f274 = 0.0f; f278 = 0.0f; f27c = 0.0f;
    v280.x = g_vec3_01678e1c.x; v280.y = g_vec3_01678e1c.y; v280.z = g_vec3_01678e1c.z;
    i28c = 0; i290 = 0; i294 = 0;
    f2a0 = 1.0f; f2a4 = 0.0f;
    i2a8 = 0; i2ac = 0; i2b0 = 0;
    f2bc = 0.0f;

    v68.push_back(30.0f);
    Vec3f d = g_vec3_01678dd0;
    vf0.push_back(d);
    v110.push_back(1.0f);
    v84.push_back(1.0f);
    v9c.push_back(0.0f);
    vb0.push_back(0.0f);
    vc4.push_back(0.0f);
}
