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

// The block's distinct colours (at most 16): count, points (+4), weights (+0xc4).
class ColourSet {
public:
    int GetCount() const { return m_count; }
    Vec3 const* GetPoints() const { return m_points; }
    float const* GetWeights() const { return m_weights; }
private:
    int   m_count;
    Vec3  m_points[16];
    float m_weights[16];
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
