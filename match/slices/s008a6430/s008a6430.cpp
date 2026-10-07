// Least-squares endpoint fit for a 565 colour block (BC1-style): squish's
// ClusterFit::SolveLeastSquares. Finds two endpoint colours (weights m_alpha/m_beta per sample)
// quantised to 5/6/5 bits and returns the metric-weighted error.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (the loop's split partial sums need /fp:fast).
#include "types.h"
#include <math.h>

// std::min / std::max: return a reference to the selected argument
inline const float& fmin_(const float& l, const float& r) { return (r < l) ? r : l; }
inline const float& fmax_(const float& l, const float& r) { return (l < r) ? r : l; }

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
    Vec3& operator-=(Arg v) { m_x -= v.m_x; m_y -= v.m_y; m_z -= v.m_z; return *this; }
    Vec3& operator*=(Arg v) { m_x *= v.m_x; m_y *= v.m_y; m_z *= v.m_z; return *this; }
    Vec3& operator*=(float s) { m_x *= s; m_y *= s; m_z *= s; return *this; }
    Vec3& operator/=(float s) { float t = 1.0f / s; m_x *= t; m_y *= t; m_z *= t; return *this; }
    friend Vec3 operator+(Arg left, Arg right) { Vec3 copy(left); return copy += right; }
    friend Vec3 operator-(Arg left, Arg right) { Vec3 copy(left); return copy -= right; }
    friend Vec3 operator*(Arg left, Arg right) { Vec3 copy(left); return copy *= right; }
    friend Vec3 operator*(Arg left, float right) { Vec3 copy(left); return copy *= right; }
    friend Vec3 operator*(float left, Arg right) { Vec3 copy(right); return copy *= left; }
    friend Vec3 operator/(Arg left, float right) { Vec3 copy(left); return copy /= right; }
    friend Vec3 Min(Arg left, Arg right)
    {
        return Vec3(fmin_(left.m_x, right.m_x), fmin_(left.m_y, right.m_y), fmin_(left.m_z, right.m_z));
    }
    friend Vec3 Max(Arg left, Arg right)
    {
        return Vec3(fmax_(left.m_x, right.m_x), fmax_(left.m_y, right.m_y), fmax_(left.m_z, right.m_z));
    }
    friend float Dot(Arg left, Arg right)
    {
        return left.m_x * right.m_x + left.m_y * right.m_y + left.m_z * right.m_z;
    }
    friend Vec3 Floor(Arg v)
    {
        return Vec3((float)floor(v.m_x), (float)floor(v.m_y), (float)floor(v.m_z));
    }
private:
    float m_x, m_y, m_z;
};

struct ColorSet { int m_count; };

struct ColorFit {
    uint32_t  pad0;
    ColorSet* m_colours;   // 0x04
    uint32_t  pad1[4];     // 0x08
    Vec3      m_points[37];// 0x18
    float     pad2;        // 0x1d4
    Vec3      m_metric;    // 0x1d8
    float     m_alpha[16]; // 0x1e4
    float     m_beta[16];  // 0x224
    Vec3      m_xxsum;     // 0x264
    float     __thiscall Fit(Vec3* start, Vec3* end);
};

// @ 0x008A6430
// squish::ClusterFit::SolveLeastSquares
float ColorFit::Fit(Vec3* start, Vec3* end)
{
    int const count = m_colours->m_count;
    float alpha2_sum = 0.0f;
    float beta2_sum = 0.0f;
    float alphabeta_sum = 0.0f;
    Vec3 alphax_sum(0.0f);
    Vec3 betax_sum(0.0f);
    for (int i = 0; i < count; ++i) {
        float alpha = m_alpha[i];
        float beta = m_beta[i];
        Vec3 const& x = m_points[i];
        alpha2_sum += alpha * alpha;
        beta2_sum += beta * beta;
        alphabeta_sum += alpha * beta;
        alphax_sum += alpha * x;
        betax_sum += beta * x;
    }
    Vec3 a, b;
    if (beta2_sum == 0.0f) {
        a = alphax_sum / alpha2_sum;
        b = Vec3(0.0f);
    } else if (alpha2_sum == 0.0f) {
        a = Vec3(0.0f);
        b = betax_sum / beta2_sum;
    } else {
        float factor = 1.0f / (alpha2_sum * beta2_sum - alphabeta_sum * alphabeta_sum);
        a = (alphax_sum * beta2_sum - betax_sum * alphabeta_sum) * factor;
        b = (betax_sum * alpha2_sum - alphax_sum * alphabeta_sum) * factor;
    }
    Vec3 const one(1.0f);
    Vec3 const zero(0.0f);
    a = Min(one, Max(zero, a));
    b = Min(one, Max(zero, b));
    Vec3 const grid(31.0f, 63.0f, 31.0f);
    Vec3 const gridrcp(1.0f / 31.0f, 1.0f / 63.0f, 1.0f / 31.0f);
    Vec3 const half(0.5f);
    a = Floor(grid * a + half) * gridrcp;
    b = Floor(grid * b + half) * gridrcp;
    Vec3 e1 = a * a * alpha2_sum + b * b * beta2_sum + m_xxsum
            + 2.0f * (a * b * alphabeta_sum - a * alphax_sum - b * betax_sum);
    float error = Dot(e1, m_metric);
    *start = a;
    *end = b;
    return error;
}
