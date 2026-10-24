// Slice s008a5700: 0x008A5BA0, squish::ClusterFit::ClusterFit(ColourSet const*) from EA's EATextSquish
// (DXT compressor in EAWebKit/EAText). The metric is always the perceptual one (0.2126, 0.7152, 0.0722), the
// ordering is a selection by ascending projection onto the principal component (ties are all appended).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame).
#include "types.h"
#include <float.h>

class Vec3 {
public:
    typedef Vec3 const& Arg;
    Vec3() {}
    explicit Vec3(float s) { m_x = s; m_y = s; m_z = s; }
    Vec3(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }
    float X() const { return m_x; }
    float Y() const { return m_y; }
    float Z() const { return m_z; }
    Vec3& operator+=(Arg v) { m_x += v.m_x; m_y += v.m_y; m_z += v.m_z; return *this; }
    Vec3& operator*=(Arg v) { m_x *= v.m_x; m_y *= v.m_y; m_z *= v.m_z; return *this; }
    Vec3& operator*=(float s) { m_x *= s; m_y *= s; m_z *= s; return *this; }
    friend Vec3 operator+(Arg left, Arg right) { Vec3 copy(left); return copy += right; }
    friend Vec3 operator*(Arg left, Arg right) { Vec3 copy(left); return copy *= right; }
    friend Vec3 operator*(Arg left, float right) { Vec3 copy(left); return copy *= right; }
    friend Vec3 operator*(float left, Arg right) { Vec3 copy(right); return copy *= left; }
    friend float Dot(Arg left, Arg right)
    {
        return left.m_x * right.m_x + left.m_y * right.m_y + left.m_z * right.m_z;
    }
private:
    float m_x, m_y, m_z;
};

// Symmetric 3x3 matrix, stored as its 6 unique elements (0x18 bytes).
class Sym3x3 {
public:
    Sym3x3() {}
    explicit Sym3x3(float s) { for (int i = 0; i < 6; ++i) m_x[i] = s; }
private:
    float m_x[6];
};

// The block's distinct colours (at most 16): count, points (+4), weights (+0xc4),
// the source-pixel remap (+0x104) and the transparency flag (+0x144).
class ColourSet {
public:
    ColourSet(unsigned char const* source, int pitch, int count);   // 0x008A5A40
    int GetCount() const { return m_count; }
    Vec3 const* GetPoints() const { return m_points; }
    float const* GetWeights() const { return m_weights; }
private:
    int   m_count;
    Vec3  m_points[16];
    float m_weights[16];
    int   m_remap[16];
    unsigned char m_transparent;
};

Sym3x3 ComputeWeightedCovariance(int n, Vec3 const* points, float const* weights);   // 0x008A4A20
Vec3 ComputePrincipleComponent(Sym3x3 const& matrix);                                // 0x008A53E0

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
    Vec3  m_weighted[16];        // +0x18   weights[i] * point
    Vec3  m_unweighted[16];      // +0xd8   points in sorted order
    float m_weights[16];         // +0x198
    Vec3  m_metric;              // +0x1d8
    float m_alpha[16];           // +0x1e4
    float m_beta[16];            // +0x224
    Vec3  m_xxsum;               // +0x264
    float m_besterror;           // +0x270
    int   m_order[16];           // +0x274
};

// @ 0x008A5BA0
ClusterFit::ClusterFit(ColourSet const* colours)
    : ColourFit(colours)
{
    m_besterror = FLT_MAX;
    m_metric = Vec3(0.2126f, 0.7152f, 0.0722f);

    int const count = m_colours->GetCount();
    Vec3 const* values = m_colours->GetPoints();
    float const* weights = m_colours->GetWeights();

    Vec3 principle;
    {
        Sym3x3 covariance = ComputeWeightedCovariance(count, values, weights);
        Vec3 p = ComputePrincipleComponent(covariance);
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
    m_xxsum = Vec3(0.0f);
    for (int i = 0; i < count; ++i) {
        int j = m_order[i];
        m_unweighted[i] = cs->GetPoints()[j];
        m_weights[i] = cs->GetWeights()[j];
        m_weighted[i] = cs->GetWeights()[j] * cs->GetPoints()[j];
        m_xxsum += m_weighted[i] * m_weighted[i];
    }
}

// ---------------------------------------------------------------------------
// Endpoint/row selector used by the range fitter.
// ---------------------------------------------------------------------------

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
    Vec3  m_color0;                  // +0x10
    Vec3  m_color1;                  // +0x1c
    unsigned char m_index;           // +0x28
    unsigned char m_pad29[3];
    int   m_error;                   // +0x2c
};

// @ 0x008A5700
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
            m_color0 = Vec3((float)p0[0] * 0.032258064f,
                            (float)p1[0] * 0.015873017f,
                            (float)p2[0] * 0.032258064f);
            m_color1 = Vec3((float)p0[1] * 0.032258064f,
                            (float)p1[1] * 0.015873017f,
                            (float)p2[1] * 0.032258064f);
            m_index = (unsigned char)i;
            m_error = error;
        }
    }
}

// ---------------------------------------------------------------------------
// Colour code quantization and block packing.
// ---------------------------------------------------------------------------

int __fastcall FUN_008a4900(Vec3 const* colour);   // 0x008A4900

// @ 0x008A5880
void FUN_008a5880(Vec3 const* color0, Vec3 const* color1,
                  unsigned char const* indices, void* block)
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

// ---------------------------------------------------------------------------
// Range fit object: vtable + colours pointer, the first colour as bytes, and
// the running error bound.
// ---------------------------------------------------------------------------

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

// @ 0x008A5920
RangeFit::RangeFit(ColourSet const* colours)
{
    mpColours = colours;
    mpVtable = (void*)0x01432218;

    Vec3 const& first = colours->GetPoints()[0];

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

// @ 0x008A5A40
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
        m_points[index] = Vec3((float)bytes[i * 4 + 2] * 0.003921569f,
                               (float)bytes[i * 4 + 1] * 0.003921569f,
                               (float)bytes[i * 4] * 0.003921569f);
        m_weights[index] = 1.0f;
        m_remap[i] = index;
        ++m_count;
    }
}
