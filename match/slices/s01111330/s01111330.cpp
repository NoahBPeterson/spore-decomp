// Slice s01111330: Havok 3.1 hk4dGsk-area simplex helper at 0x011114b0 (Simplex5::SelectVertexToDrop).
// A 5-vertex simplex (0x30-byte vertices, newest point in slot 4): picks the vertex to drop when the
// simplex is reduced. It (1) finds the vertex farthest from / closest to the newest point, (2) greedily
// marks up to four "keeper" vertices (farthest from the first keeper, then the one maximising the
// cross-product length with the first edge, then the farthest from that one), and (3) when the newest
// vertex is still free and its per-vertex scalar (+0x1c) is clearly smaller than the closest vertex's
// (scalar delta^2 * 526 > closest distance), returns the vertex whose scalar differs most relative to
// its distance (ratio test: 0.0304617 / 1e-9 constants). Otherwise the first unmarked vertex is returned.
// Havok was built with VC7.1: the manifest row carries the /vc71 pseudo-flag (x87 code shape).
// Flags: /vc71 /O2 /MD /Gy /TP.

typedef float hkReal;

class __declspec(align(16)) hkVector4
{
public:
    hkReal x, y, z, w;
    inline hkReal lengthSquared3() const { return x * x + y * y + z * z; }
    inline void setSub4(const hkVector4& a, const hkVector4& b)
    { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
    inline void setCross(const hkVector4& a, const hkVector4& b)
    {
        x = a.y * b.z - a.z * b.y;
        y = a.z * b.x - a.x * b.z;
        z = a.x * b.y - a.y * b.x;
        w = 0.0f;
    }
};

// One simplex vertex: world-space point, a second vector, and a per-vertex scalar at +0x1c.
struct SimplexVertex
{
    hkVector4 m_position;          // +0x00
    hkReal pad10[3];               // +0x10
    hkReal m_extra;                // +0x1c
    hkReal pad20[4];               // +0x20
};

#define HK_REAL_MAX 3.40282e+38f

// squared distance between two simplex points
static inline hkReal distSqPts(const hkVector4& a, const hkVector4& b)
{
    hkVector4 d;
    d.setSub4(a, b);
    return d.lengthSquared3();
}

struct Simplex5
{
    SimplexVertex m_v[5];          // 0x30 apart; v[4] is the newest point

    // @ 0x011114b0
    int SelectVertexToDrop();
};

int Simplex5::SelectVertexToDrop()
{
    bool done[5] = { false, false, false, false, false };
    hkReal minD = HK_REAL_MAX;
    hkReal maxD = 0.0f;
    int maxIdx = 0;
    int minIdx = 0;
    hkReal dist[4];

    for (int i = 0; i < 4; i++)
    {
        dist[i] = distSqPts(m_v[4].m_position, m_v[i].m_position);
        if (dist[i] > maxD) { maxD = dist[i]; maxIdx = i; }
        if (dist[i] < minD) { minD = dist[i]; minIdx = i; }
    }

    hkReal dw = m_v[4].m_extra - m_v[minIdx].m_extra;
    done[maxIdx] = true;
    maxD = maxD * 1.05f;
    int farIdx = 4;
    const hkVector4& p = m_v[maxIdx].m_position;
    for (int i = 0; i < 5; i++)
    {
        if (!done[i])
        {
            hkReal l = distSqPts(p, m_v[i].m_position);
            if (l > maxD) { maxD = l; farIdx = i; }
        }
    }
    int crossIdx = 0;
    hkVector4 e;
    e.setSub4(p, m_v[farIdx].m_position);
    done[farIdx] = true;
    hkReal maxC = 0.0f;
    for (int i = 0; i < 5; i++)
    {
        if (!done[i])
        {
            hkVector4 d;
            d.setSub4(m_v[i].m_position, p);
            hkVector4 c;
            c.setCross(d, e);
            hkReal l = c.lengthSquared3();
            if (l > maxC) { maxC = l; crossIdx = i; }
        }
    }
    done[crossIdx] = true;

    int lastIdx = 0;
    const hkVector4& q = m_v[crossIdx].m_position;
    hkReal maxL = 0.0f;
    for (int i = 0; i < 5; i++)
    {
        if (!done[i])
        {
            hkReal l = distSqPts(q, m_v[i].m_position);
            if (l > maxL) { maxL = l; lastIdx = i; }
        }
    }
    done[lastIdx] = true;

    if (!done[4] && dw < 0.0f && minD < dw * dw * 526.0f)
    {
        int idx = 4;
        hkReal w4 = m_v[4].m_extra;
        hkReal ratio = 0.030461743f;
        for (int i = 0; i < 4; i++)
        {
            hkReal t = m_v[i].m_extra - w4;
            hkReal t2 = t * t + 1e-09f;
            if (t2 > dist[i] * ratio) { idx = i; ratio = t2 / (dist[i] + 1e-09f); }
        }
        return idx;
    }
    for (int i = 0; i < 5; i++)
        if (!done[i])
            return i;
    return 0;
}
