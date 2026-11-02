// src/game/UTFSpore_Win32/_at_008a0000.cpp -- migrated from slice(s) s008a7400, s008a6430, s008a5700, s008a47f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_008a0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <float.h>
#include <math.h>
#include <intrin.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern const float kScale31;      // 0x014321FC (31.0f)
extern const float kScale63;      // 0x014321F8 (63.0f)
extern const float kRoundHalf;    // 0x01471064 (0.5f)

// ---- items of slice s008a47f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
static inline Vec3 Load(const Vec3* a, int i) { return a[i]; }
static inline Vec3 Scale(const Vec3& a, float s) { Vec3 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }
static inline Vec3 AddScaled(const Vec3& a, const Vec3& p, float s) { Vec3 r; r.x = p.x * s + a.x; r.y = p.y * s + a.y; r.z = p.z * s + a.z; return r; }
static inline Vec3 Sub(const Vec3& a, float x, float y, float z) { Vec3 r; r.x = a.x - x; r.y = a.y - y; r.z = a.z - z; return r; }
extern const float kScale31;      // 0x014321FC (31.0f)
extern const float kScale63;      // 0x014321F8 (63.0f)
extern const float kRoundHalf;    // 0x01471064 (0.5f)
// ---- items of slice s008a47f0 end

// ---- items of slice s008a5700 begin (TODO(rewrite): local stubs, replace by canonical classes)
class Vec3_s008a_5700 {
public:
    typedef Vec3_s008a_5700 const& Arg;
    Vec3_s008a_5700() {}
    explicit Vec3_s008a_5700(float s) { m_x = s; m_y = s; m_z = s; }
    Vec3_s008a_5700(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }
    float X() const { return m_x; }
    float Y() const { return m_y; }
    float Z() const { return m_z; }
    Vec3_s008a_5700& operator+=(Arg v) { m_x += v.m_x; m_y += v.m_y; m_z += v.m_z; return *this; }
    Vec3_s008a_5700& operator*=(Arg v) { m_x *= v.m_x; m_y *= v.m_y; m_z *= v.m_z; return *this; }
    Vec3_s008a_5700& operator*=(float s) { m_x *= s; m_y *= s; m_z *= s; return *this; }
    friend Vec3_s008a_5700 operator+(Arg left, Arg right) { Vec3_s008a_5700 copy(left); return copy += right; }
    friend Vec3_s008a_5700 operator*(Arg left, Arg right) { Vec3_s008a_5700 copy(left); return copy *= right; }
    friend Vec3_s008a_5700 operator*(Arg left, float right) { Vec3_s008a_5700 copy(left); return copy *= right; }
    friend Vec3_s008a_5700 operator*(float left, Arg right) { Vec3_s008a_5700 copy(right); return copy *= left; }
    friend float Dot(Arg left, Arg right)
    {
        return left.m_x * right.m_x + left.m_y * right.m_y + left.m_z * right.m_z;
    }
private:
    float m_x, m_y, m_z;
};
class Sym3x3 {
public:
    Sym3x3() {}
    explicit Sym3x3(float s) { for (int i = 0; i < 6; ++i) m_x[i] = s; }
private:
    float m_x[6];
};
class ColourSet {
public:
    ColourSet(unsigned char const* source, int pitch, int count);   // 0x008A5A40
    int GetCount() const { return m_count; }
    Vec3_s008a_5700 const* GetPoints() const { return m_points; }
    float const* GetWeights() const { return m_weights; }
private:
    int   m_count;
    Vec3_s008a_5700  m_points[16];
    float m_weights[16];
    int   m_remap[16];
    unsigned char m_transparent;
};
Sym3x3 ComputeWeightedCovariance(int n, Vec3_s008a_5700 const* points, float const* weights);   // 0x008A4A20
Vec3_s008a_5700 ComputePrincipleComponent(Sym3x3 const& matrix);                                // 0x008A53E0
class ColourFit {
public:
    ColourFit(ColourSet const* colours) : m_colours(colours) {}
    virtual ~ColourFit() {}
protected:
    ColourSet const* m_colours;   // +4
    int m_pad8[4];                // +8
};
class ClusterFit : public ColourFit {
public:
    ClusterFit(ColourSet const* colours);                  // 0x008A5BA0
    virtual ~ClusterFit();
private:
    Vec3_s008a_5700  m_weighted[16];        // +0x18   weights[i] * point
    Vec3_s008a_5700  m_unweighted[16];      // +0xd8   points in sorted order
    float m_weights[16];         // +0x198
    Vec3_s008a_5700  m_metric;              // +0x1d8
    float m_alpha[16];           // +0x1e4
    float m_beta[16];            // +0x224
    Vec3_s008a_5700  m_xxsum;               // +0x264
    float m_besterror;           // +0x270
    int   m_order[16];           // +0x274
};
struct ColorRows
{
    unsigned char* mpRows[3];        // +0x00 red/green/blue byte rows
};
class AxisFit
{
public:
    void Select(int count, ColorRows const* rows);   // 0x008A5700
private:
    int   m_pad0[3];                 // +0x00
    unsigned char m_axis0;           // +0x0c
    unsigned char m_axis1;           // +0x0d
    unsigned char m_axis2;           // +0x0e
    unsigned char m_pad0f;
    Vec3_s008a_5700  m_color0;                  // +0x10
    Vec3_s008a_5700  m_color1;                  // +0x1c
    unsigned char m_index;           // +0x28
    unsigned char m_pad29[3];
    int   m_error;                   // +0x2c
};
int __fastcall FUN_008a4900(Vec3_s008a_5700 const* colour);   // 0x008A4900
class RangeFit
{
public:
    RangeFit(ColourSet const* colours);   // 0x008A5920
private:
    void* mpVtable;                   // +0x00
    ColourSet const* mpColours;       // +0x04
    int   m_pad8;
    unsigned char m_start0;           // +0x0c
    unsigned char m_start1;           // +0x0d
    unsigned char m_start2;           // +0x0e
    unsigned char m_pad0f[0x30 - 0x0f];
    int   m_error;                    // +0x30
};
// ---- items of slice s008a5700 end

// ---- items of slice s008a6430 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline const float& fmin_(const float& l, const float& r) { return (r < l) ? r : l; }
inline const float& fmax_(const float& l, const float& r) { return (l < r) ? r : l; }
class Vec3_s008a_6430 {
public:
    typedef Vec3_s008a_6430 const& Arg;
    Vec3_s008a_6430() {}
    explicit Vec3_s008a_6430(float s) { m_x = s; m_y = s; m_z = s; }
    Vec3_s008a_6430(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }
    float X() const { return m_x; }
    float Y() const { return m_y; }
    float Z() const { return m_z; }
    Vec3_s008a_6430& operator+=(Arg v) { m_x += v.m_x; m_y += v.m_y; m_z += v.m_z; return *this; }
    Vec3_s008a_6430& operator-=(Arg v) { m_x -= v.m_x; m_y -= v.m_y; m_z -= v.m_z; return *this; }
    Vec3_s008a_6430& operator*=(Arg v) { m_x *= v.m_x; m_y *= v.m_y; m_z *= v.m_z; return *this; }
    Vec3_s008a_6430& operator*=(float s) { m_x *= s; m_y *= s; m_z *= s; return *this; }
    Vec3_s008a_6430& operator/=(float s) { float t = 1.0f / s; m_x *= t; m_y *= t; m_z *= t; return *this; }
    friend Vec3_s008a_6430 operator+(Arg left, Arg right) { Vec3_s008a_6430 copy(left); return copy += right; }
    friend Vec3_s008a_6430 operator-(Arg left, Arg right) { Vec3_s008a_6430 copy(left); return copy -= right; }
    friend Vec3_s008a_6430 operator*(Arg left, Arg right) { Vec3_s008a_6430 copy(left); return copy *= right; }
    friend Vec3_s008a_6430 operator*(Arg left, float right) { Vec3_s008a_6430 copy(left); return copy *= right; }
    friend Vec3_s008a_6430 operator*(float left, Arg right) { Vec3_s008a_6430 copy(right); return copy *= left; }
    friend Vec3_s008a_6430 operator/(Arg left, float right) { Vec3_s008a_6430 copy(left); return copy /= right; }
    friend Vec3_s008a_6430 Min(Arg left, Arg right)
    {
        return Vec3_s008a_6430(fmin_(left.m_x, right.m_x), fmin_(left.m_y, right.m_y), fmin_(left.m_z, right.m_z));
    }
    friend Vec3_s008a_6430 Max(Arg left, Arg right)
    {
        return Vec3_s008a_6430(fmax_(left.m_x, right.m_x), fmax_(left.m_y, right.m_y), fmax_(left.m_z, right.m_z));
    }
    friend float Dot(Arg left, Arg right)
    {
        return left.m_x * right.m_x + left.m_y * right.m_y + left.m_z * right.m_z;
    }
    friend Vec3_s008a_6430 Floor(Arg v)
    {
        return Vec3_s008a_6430((float)floor(v.m_x), (float)floor(v.m_y), (float)floor(v.m_z));
    }
private:
    float m_x, m_y, m_z;
};
struct ColorSet { int m_count; };
struct ColorFit {
    uint32_t  pad0;
    ColorSet* m_colours;   // 0x04
    uint32_t  pad1[4];     // 0x08
    Vec3_s008a_6430      m_points[37];// 0x18
    float     pad2;        // 0x1d4
    Vec3_s008a_6430      m_metric;    // 0x1d8
    float     m_alpha[16]; // 0x1e4
    float     m_beta[16];  // 0x224
    Vec3_s008a_6430      m_xxsum;     // 0x264
    float     __thiscall Fit(Vec3_s008a_6430* start, Vec3_s008a_6430* end);
};
// ---- items of slice s008a6430 end

// ---- items of slice s008a7400 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* (__cdecl *ff_alloc_t)(unsigned);
typedef void  (__cdecl *ff_free_t)(void*);
typedef void* (__cdecl *ff_realloc_t)(void*, unsigned);
ff_alloc_t   g_ff_malloc;
ff_free_t    g_ff_free;
ff_realloc_t g_ff_realloc;
// ---- items of slice s008a7400 end

// @ 0x008a4900
unsigned __fastcall FUN_008a4900(const float* rgb)
{
    int r = (int)(rgb[0] * kScale31 + kRoundHalf);
    if (r < 0)
        r = 0;
    else if (r > 0x1f)
        r = 0x1f;

    int g = (int)(rgb[1] * kScale63 + kRoundHalf);
    if (g < 0)
        g = 0;
    else if (g > 0x3f)
        g = 0x3f;

    int b = (int)(rgb[2] * kScale31 + kRoundHalf);
    if (b < 0)
        b = 0;
    else if (b > 0x1f)
        b = 0x1f;

    return ((unsigned)(r << 6 | g) << 5) | (unsigned)b;
}

// @ 0x008a4a20
void WeightedCovariance(float* cov, int n, const Vec3* pts, const float* w)
{
    Vec3 mean; mean.x = 0.0f; mean.y = 0.0f; mean.z = 0.0f;
    float sw = 0.0f;
    for (int i = 0; i < n; ++i) {
        Vec3 p = Load(pts, i);
        float wi = w[i];
        sw += wi;
        mean = AddScaled(mean, p, wi);
    }
    float inv = 1.0f / sw;
    float mx = mean.x * inv, my = mean.y * inv, mz = mean.z * inv;
    for (int k = 0; k < 6; ++k) cov[k] = 0.0f;
    for (int i = 0; i < n; ++i) {
        Vec3 p = Load(pts, i);
        Vec3 d = Sub(p, mx, my, mz);
        Vec3 dw = Scale(d, w[i]);
        cov[0] += dw.x * d.x;
        cov[1] += dw.y * d.x;
        cov[2] += dw.z * d.x;
        cov[3] += dw.y * d.y;
        cov[4] += dw.z * d.y;
        cov[5] += dw.z * d.z;
    }
}

// @ 0x008a5700
void AxisFit::Select(int count, ColorRows const* rows)
{
    m_error = 0x7fffffff;
    if (count <= 0)
        return;

    for (int i = 0; i < count; ++i) {
        unsigned char* p0 = rows->mpRows[0] + (i + m_axis0 * 4) * 3;
        unsigned char* p1 = rows->mpRows[1] + (i + m_axis1 * 4) * 3;
        unsigned char* p2 = rows->mpRows[2] + (i + m_axis2 * 4) * 3;

        int error = p0[2] * p0[2] + p1[2] * p1[2] + p2[2] * p2[2];
        if (error < m_error) {
            m_color0 = Vec3_s008a_5700((float)p0[0] * 0.032258064f,
                            (float)p1[0] * 0.015873017f,
                            (float)p2[0] * 0.032258064f);
            m_color1 = Vec3_s008a_5700((float)p0[1] * 0.032258064f,
                            (float)p1[1] * 0.015873017f,
                            (float)p2[1] * 0.032258064f);
            m_index = (unsigned char)i;
            m_error = error;
        }
    }
}

// @ 0x008a5880
void FUN_008a5880(Vec3_s008a_5700 const* color0, Vec3_s008a_5700 const* color1, unsigned char const* indices, void* block)
{
    int code0 = FUN_008a4900(color0);
    int code1 = FUN_008a4900(color1);

    unsigned char local[16];
    int outLow = code0;
    int outHigh = code1;
    if (code0 < code1) {
        for (int i = 0; i < 16; ++i)
            local[i] = (indices[i] ^ 1) & 3;
        outLow = code1;
        outHigh = code0;
    } else if (code0 == code1) {
        for (int i = 0; i < 16; ++i)
            local[i] = 0;
    } else {
        for (int i = 0; i < 16; ++i)
            local[i] = indices[i];
    }

    unsigned char* out = (unsigned char*)block;
    out[0] = (unsigned char)outLow;
    out[1] = (unsigned char)(outLow >> 8);
    out[2] = (unsigned char)outHigh;
    out[3] = (unsigned char)(outHigh >> 8);
    for (int i = 0; i < 4; ++i) {
        out[4 + i] = (unsigned char)(((local[i * 4 + 3] << 2 | local[i * 4 + 2]) << 2 |
                                      local[i * 4 + 1]) << 2 | local[i * 4 + 0]);
    }
}

// @ 0x008a5920
RangeFit::RangeFit(ColourSet const* colours)
{
    mpColours = colours;
    mpVtable = (void*)0x01432218;

    Vec3_s008a_5700 const& first = colours->GetPoints()[0];

    int c0 = (int)(first.X() * 255.0f + 0.5f);
    if (c0 < 0) c0 = 0; else if (c0 > 255) c0 = 255;
    m_start0 = (unsigned char)c0;

    int c1 = (int)(first.Y() * 255.0f + 0.5f);
    if (c1 < 0) c1 = 0; else if (c1 > 255) c1 = 255;
    m_start1 = (unsigned char)c1;

    int c2 = (int)(first.Z() * 255.0f + 0.5f);
    if (c2 < 0) c2 = 0; else if (c2 > 255) c2 = 255;
    m_start2 = (unsigned char)c2;

    m_error = 0x7fffffff;
}

// @ 0x008a5a40
ColourSet::ColourSet(unsigned char const* source, int pitch, int count)
{
    m_count = 0;
    m_transparent = 0;

    unsigned char bytes[64];
    int offset = 0;
    unsigned limit = (unsigned)count * 4u;
    for (int row = 0; row < 4; ++row) {
        for (int i = 0; i < 16; ++i) {
            int n = row * 16 + i;
            bytes[n] = ((unsigned)(offset + i) < limit) ? source[offset + i] : 0;
        }
        offset += pitch;
    }

    for (int i = 0; i < 16; ++i) {
        int j;
        for (j = 0; j < i; ++j) {
            if (bytes[i * 4] == bytes[j * 4] &&
                bytes[i * 4 + 1] == bytes[j * 4 + 1] &&
                bytes[i * 4 + 2] == bytes[j * 4 + 2]) {
                int index = m_remap[j];
                m_weights[index] += 1.0f;
                m_remap[i] = index;
                break;
            }
        }
        if (j != i)
            continue;

        int index = m_count;
        m_points[index] = Vec3_s008a_5700((float)bytes[i * 4 + 2] * 0.003921569f,
                               (float)bytes[i * 4 + 1] * 0.003921569f,
                               (float)bytes[i * 4] * 0.003921569f);
        m_weights[index] = 1.0f;
        m_remap[i] = index;
        ++m_count;
    }
}

// @ 0x008a5ba0
ClusterFit::ClusterFit(ColourSet const* colours)
: ColourFit(colours)
{
    m_besterror = FLT_MAX;
    m_metric = Vec3_s008a_5700(0.2126f, 0.7152f, 0.0722f);

    int const count = m_colours->GetCount();
    Vec3_s008a_5700 const* values = m_colours->GetPoints();
    float const* weights = m_colours->GetWeights();

    Vec3_s008a_5700 principle;
    {
        Sym3x3 covariance = ComputeWeightedCovariance(count, values, weights);
        Vec3_s008a_5700 p = ComputePrincipleComponent(covariance);
        principle = p;
    }

    // projection of every colour onto the principal axis, and the smallest one
    float dps[16];
    float next = FLT_MAX;
    for (int i = 0; i < count; ++i) {
        dps[i] = Dot(values[i], principle);
        if (dps[i] < next)
            next = dps[i];
    }

    // order by ascending projection: each pass appends every colour equal to the current value and finds the
    // next larger one
    int n = 0;
    while (n < count) {
        float lowest = next;
        next = FLT_MAX;
        for (int i = 0; i < count; ++i) {
            if (dps[i] == lowest)
                m_order[n++] = i;
            else if (dps[i] > lowest && dps[i] < next)
                next = dps[i];
        }
    }

    // weight all the points
    ColourSet const* cs = m_colours;
    m_xxsum = Vec3_s008a_5700(0.0f);
    for (int i = 0; i < count; ++i) {
        int j = m_order[i];
        m_unweighted[i] = cs->GetPoints()[j];
        m_weights[i] = cs->GetWeights()[j];
        m_weighted[i] = cs->GetWeights()[j] * cs->GetPoints()[j];
        m_xxsum += m_weighted[i] * m_weighted[i];
    }
}

// @ 0x008a6430
float ColorFit::Fit(Vec3_s008a_6430* start, Vec3_s008a_6430* end)
{
    int const count = m_colours->m_count;
    float alpha2_sum = 0.0f;
    float beta2_sum = 0.0f;
    float alphabeta_sum = 0.0f;
    Vec3_s008a_6430 alphax_sum(0.0f);
    Vec3_s008a_6430 betax_sum(0.0f);
    for (int i = 0; i < count; ++i) {
        float alpha = m_alpha[i];
        float beta = m_beta[i];
        Vec3_s008a_6430 const& x = m_points[i];
        alpha2_sum += alpha * alpha;
        beta2_sum += beta * beta;
        alphabeta_sum += alpha * beta;
        alphax_sum += alpha * x;
        betax_sum += beta * x;
    }
    Vec3_s008a_6430 a, b;
    if (beta2_sum == 0.0f) {
        a = alphax_sum / alpha2_sum;
        b = Vec3_s008a_6430(0.0f);
    } else if (alpha2_sum == 0.0f) {
        a = Vec3_s008a_6430(0.0f);
        b = betax_sum / beta2_sum;
    } else {
        float factor = 1.0f / (alpha2_sum * beta2_sum - alphabeta_sum * alphabeta_sum);
        a = (alphax_sum * beta2_sum - betax_sum * alphabeta_sum) * factor;
        b = (betax_sum * alpha2_sum - alphax_sum * alphabeta_sum) * factor;
    }
    Vec3_s008a_6430 const one(1.0f);
    Vec3_s008a_6430 const zero(0.0f);
    a = Min(one, Max(zero, a));
    b = Min(one, Max(zero, b));
    Vec3_s008a_6430 const grid(31.0f, 63.0f, 31.0f);
    Vec3_s008a_6430 const gridrcp(1.0f / 31.0f, 1.0f / 63.0f, 1.0f / 31.0f);
    Vec3_s008a_6430 const half(0.5f);
    a = Floor(grid * a + half) * gridrcp;
    b = Floor(grid * b + half) * gridrcp;
    Vec3_s008a_6430 e1 = a * a * alpha2_sum + b * b * beta2_sum + m_xxsum
            + 2.0f * (a * b * alphabeta_sum - a * alphax_sum - b * betax_sum);
    float error = Dot(e1, m_metric);
    *start = a;
    *end = b;
    return error;
}

// @ 0x008a76e0
void FUN_008a76e0(int a1, void* a2, int a3, int a4, int a5)
{
    // PARTIAL: dispatch wrapper building a 0x430-byte scratch record and branching on
    // a tag field, then calling the setup passes.
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5;
}

// @ 0x008a7790
void ff_set_memfuncs(ff_alloc_t a, ff_free_t f, ff_realloc_t r)
{
    g_ff_malloc = a;
    g_ff_free = f;
    g_ff_realloc = r;
}
