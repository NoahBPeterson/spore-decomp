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

// ===========================================================================================
// Packed simplex row table (the Havok helper that sits directly in front of
// Simplex5::SelectVertexToDrop).  A table holds `m_count` 8-byte rows -- four vertex ids
// followed by four packed-value indices -- and, right after the rows, the 16-bit value table
// those indices address: value(i) = *(uint16_t*)(table + 4 + m_count*8 + (row.m_values[i] >> 3)).
// A key describes the simplex being looked up: its two vertex-count halves, the sum of which is
// the number of vertices in the simplex, and one packed value per vertex.
// ===========================================================================================
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

struct hkSimplexRow
{
    uint8_t m_ids[4];       // +0x00 vertex ids of the row
    uint8_t m_values[4];    // +0x04 packed value indices
};

struct hkSimplexKey
{
    uint16_t m_values[4];   // +0x00 packed values, one per vertex
    signed char m_ids[2];   // +0x08 vertex-count halves (their sum is the vertex count)
};

struct hkSimplexTable
{
    uint16_t m_flags;       // +0x00
    uint8_t  m_count;       // +0x02 number of rows
    uint8_t  m_pad03;       // +0x03

    const hkSimplexRow* rows() const { return (const hkSimplexRow*)((const uint8_t*)this + 4); }
    hkSimplexRow* rows() { return (hkSimplexRow*)((uint8_t*)this + 4); }

    uint16_t value(uint8_t packedIndex) const
    {
        const uint8_t* pValues = (const uint8_t*)this + 4;
        return *(const uint16_t*)(pValues + m_count * 8u + (packedIndex >> 3));
    }
};

// @ 0x01111330
// Looks the key up in the table.  On a hit the row is moved to the front (rows are kept in
// most-recently-used order) and the call reports true.  On a miss, a single-vertex key that
// names a row which was reduced away has that row's ids cleared.
bool hkSimplexTable_FindRow(hkSimplexTable* pTable, const hkSimplexKey& key)
{
    int idx;
    int numVertices;
    const int count = pTable->m_count;

    for (idx = 0; idx < count; ++idx)
    {
        const hkSimplexRow* pRow = &pTable->rows()[idx];
        if (key.m_ids[0] != pRow->m_ids[0] || key.m_ids[1] != pRow->m_ids[1])
            continue;
        numVertices = key.m_ids[0] + key.m_ids[1];
        if (key.m_values[0] != pTable->value(pRow->m_values[0]))
            continue;
        if (key.m_values[1] != pTable->value(pRow->m_values[1]))
            continue;
        if (numVertices > 2 && key.m_values[2] != pTable->value(pRow->m_values[2]))
            continue;
        if (numVertices > 3 && key.m_values[3] != pTable->value(pRow->m_values[3]))
            continue;
        goto found;
    }

    if (key.m_ids[0] == 1 || key.m_ids[1] == 1)
    {
        for (idx = 0; idx < count; ++idx)
        {
            uint8_t* pRow = (uint8_t*)&pTable->rows()[idx];
            if (key.m_ids[0] == 1 && pRow[0] == 1 &&
                pTable->value(pRow[4]) == key.m_values[0])
            {
                pRow[0] = 0;
                pRow[1] = 0;
                return false;
            }
            if (key.m_ids[1] == 1 && pRow[1] == 1 &&
                pTable->value(pRow[4 + pRow[0]]) == key.m_values[key.m_ids[0]])
            {
                pRow[0] = 0;
                pRow[1] = 0;
                return false;
            }
        }
    }
    return false;

found:
    if (idx > 0)
    {
        hkSimplexRow* pRows = pTable->rows();
        hkSimplexRow moved = pRows[idx];
        pRows[idx] = pRows[0];
        pRows[0] = moved;
    }
    return true;
}

// ===========================================================================================
// 0x01111d90 / 0x011120a0: the GSK simplex-maintenance and contact-solving helpers that share
// this code cluster.  Both are Havok 3.1 routines with dense bit-packed state / x87 maths; the
// reconstructions below keep retail's callee order and field offsets.
// ===========================================================================================
#define HK_REAL_ZERO 0.0f
#define HK_REAL_ONE  1.0f

struct hkPackedRow
{
    uint8_t  m_ids[2];      // +0x00 the two ids the row was built from
    uint16_t m_value;       // +0x02 packed value written by the manifold
    uint8_t  m_payload[4];  // +0x04
};

// Working simplex: a 4-slot, most-recently-used-first table of rows.  The byte at +0x08 (the
// payload of row 0) doubles as the packed per-vertex values of the simplex.
struct hkPackedSimplex
{
    uint8_t     m_numVerticesA;   // +0x00
    uint8_t     m_numVerticesB;   // +0x01
    uint8_t     m_numRows;        // +0x02, at most 4
    uint8_t     m_pad03;          // +0x03
    hkPackedRow m_rows[4];        // +0x04

    uint8_t* valueBytes() { return (uint8_t*)this + 8; }
};

// The manifold-side interface the routines call through.
struct hkGskInterface
{
    virtual void     v00();
    virtual void     v04();
    virtual uint16_t v08(void* a, void* b, void* c, const void* d);   // +0x08 index lookup / append
    virtual void     v0c();
    virtual void     v10(uint16_t index);                        // +0x10 note a dropped vertex
};

struct hkGskSolveBody
{
    hkReal  m_pad00[0x40];
    hkReal  m_p0[3];        // +0x40 segment start
    hkReal  m_start;        // +0x4c
    hkReal  m_p1[3];        // +0x50 segment end
    hkReal  m_invRange;     // +0x5c
};

struct hkGskFrame              // two basis vectors, a 4-float stride apart
{
    hkReal m_u0[4];            // +0x00
    hkReal m_u1[4];            // +0x10
};

// Sign-dependent scale factors of the contact solve (0x013eb1c0 / 0x01488694).
extern const hkReal gGskPositiveScale;
extern const hkReal gGskNegativeScale;

void hkGskManifold_removeUnusedVertices(hkPackedSimplex* pSimplex);          // 0x0110fc50
void __fastcall SimplexVertex_setFrom(SimplexVertex* pVertex, const hkVector4* pSource); // 0x01103af0

// @ 0x01111d90
// Inserts a vertex into the working simplex.  With four rows present the oldest row is dropped
// through Simplex5::SelectVertexToDrop and the manifold is asked for the new index; otherwise the
// new row is prepended and the packed per-vertex values are recorded.  Returns 4 when the simplex
// was updated, 5 when no vertex could be dropped and 6 after a manifold-level replacement.
int __cdecl hkPackedSimplex_InsertVertex(hkPackedSimplex* pSimplex, const void* pUnused,
                                         hkGskInterface* pInterface, void* a3, void* a4,
                                         void* a5, uint16_t* pOutIndex, Simplex5* pSimplex5,
                                         const hkSimplexKey* pKey, int bReplace)
{
    int result = 4;
    uint16_t packedIndex = 0xffff;
    if (pSimplex->m_numRows == 4)
    {
        int dropped = pSimplex5->SelectVertexToDrop();
        if (dropped == 4)
            return 5;

        pInterface->v10(pSimplex->m_rows[dropped].m_value);

        // the dropped slot takes over the newest row; slot 0 takes row 1
        if (dropped != 0)
        {
            *(uint32_t*)&pSimplex->m_rows[dropped] = *(uint32_t*)&pSimplex->m_rows[0];
            *(uint32_t*)&pSimplex->m_rows[dropped].m_payload[0] =
                *(uint32_t*)&pSimplex->m_rows[0].m_payload[0];
        }
        else
        {
            *(uint32_t*)&pSimplex->m_rows[0] = *(uint32_t*)&pSimplex->m_rows[1];
            *(uint32_t*)&pSimplex->m_rows[0].m_payload[0] =
                *(uint32_t*)&pSimplex->m_rows[1].m_payload[0];
        }

        hkGskManifold_removeUnusedVertices(pSimplex);

        uint16_t index = pInterface->v08(a3, a4, a5, &pSimplex5[0]);
        if (index == 0xffff)
        {
            // the manifold replaced the vertex instead: drop the last simplex vertex and shift
            pSimplex->m_rows[0].m_payload[0] = (uint8_t)(pSimplex->m_rows[0].m_payload[0] & 0xff);
            uint8_t newCount = (uint8_t)(pSimplex->m_numRows - 1);
            pSimplex->m_numRows = newCount;
            uint8_t* pDst = (uint8_t*)pSimplex + newCount * 8 + 8;
            uint8_t* pSrc = (uint8_t*)pSimplex + newCount * 8 + 0x10;
            int n = (pSimplex->m_numVerticesA + pSimplex->m_numVerticesB - 1) >> 1;
            for (int i = n; i >= 0; --i)
            {
                *(uint32_t*)pDst = *(uint32_t*)pSrc;
                pDst += 4;
                pSrc += 4;
            }
            SimplexVertex_setFrom((SimplexVertex*)((uint8_t*)pSimplex5 + dropped * 0x30),
                                  (const hkVector4*)((uint8_t*)a5 + 0x90));
            return 6;
        }

        *(uint16_t*)((uint8_t*)a5 + 0x20) = index;
        packedIndex = index;
        result = dropped;
        SimplexVertex_setFrom((SimplexVertex*)((uint8_t*)pSimplex5 + dropped * 0x30),
                              (const hkVector4*)a5);
    }
    else
    {
        if (!bReplace || pKey->m_ids[1] == 3)
        {
            uint16_t index = pInterface->v08(a3, a4, a5, pKey);
            if (index == 0xffff)
                return 5;
            packedIndex = index;
            *(uint16_t*)((uint8_t*)a5 + 0x20) = packedIndex;
        }
        else
        {
            *(uint16_t*)((uint8_t*)a5 + 0x20) = packedIndex;

            // make room in the middle of the packed-value bytes
            int half = (pSimplex->m_numVerticesA + pSimplex->m_numVerticesB - 1) >> 1;
            int slot = half + pSimplex->m_numRows * 2;
            uint8_t* pDst = (uint8_t*)pSimplex + slot * 4 + 0xc;
            uint8_t* pSrc = (uint8_t*)pSimplex + slot * 4 + 4;
            for (int i = half; i >= 0; --i)
            {
                *(uint32_t*)pDst = *(uint32_t*)pSrc;
                pDst -= 4;
                pSrc -= 4;
            }

            // append the old row 0 as row m_numRows
            hkPackedRow* pTail = &pSimplex->m_rows[pSimplex->m_numRows];
            *(uint32_t*)&pTail->m_ids[0] = *(uint32_t*)&pSimplex->m_rows[0];
            *(uint32_t*)&pTail->m_payload[0] = *(uint32_t*)&pSimplex->m_rows[0].m_payload[0];
            ++pSimplex->m_numRows;
        }
    }

    // fill row 0 from the key
    pSimplex->m_rows[0].m_ids[0] = (uint8_t)pKey->m_ids[0];
    pSimplex->m_rows[0].m_ids[1] = (uint8_t)pKey->m_ids[1];
    pSimplex->m_rows[0].m_value = packedIndex;
    *(uint32_t*)&pSimplex->m_rows[0].m_payload[0] = 0;

    // record one packed byte per simplex vertex; the 16-bit values live right after the rows
    uint16_t* pWordValues =
        (uint16_t*)((uint8_t*)pSimplex + 4 + (int)pSimplex->m_numRows * 8);
    uint8_t* pValues = pSimplex->valueBytes();
    int offset = 0;
    for (int a = 0; a < (int)pKey->m_ids[0]; ++a)
    {
        uint16_t v = pKey->m_values[a];
        int found = 0;
        int i = 0;
        for (; i < pSimplex->m_numVerticesA; ++i)
            if (pWordValues[i] == v) { found = 1; break; }
        if (!found)
        {
            int n = pSimplex->m_numVerticesA + pSimplex->m_numVerticesB;
            for (int j = n; j > i; --j)
                pWordValues[j] = pWordValues[j - 1];
            pWordValues[i] = v;
            ++pSimplex->m_numVerticesA;
            offset += 0x10;
        }
        pValues[a] = (uint8_t)(i << 4);
    }
    if (offset)
    {
        for (int r = 1; r < pSimplex->m_numRows; ++r)
        {
            uint8_t* pRow = (uint8_t*)&pSimplex->m_rows[r];
            int n = pRow[0] + pRow[1];
            for (int i = pRow[0]; i < n; ++i)
                pRow[4 + i] = (uint8_t)(pRow[4 + i] + offset);
        }
    }
    for (int b = 0; b < (int)pKey->m_ids[1]; ++b)
    {
        uint16_t v = pKey->m_values[pKey->m_ids[0] + b];
        int i = 0;
        int n = pSimplex->m_numVerticesA + pSimplex->m_numVerticesB;
        for (; i < n; ++i)
            if (pWordValues[i] == v) break;
        if (i == n)
        {
            pWordValues[i] = v;
            ++pSimplex->m_numVerticesB;
        }
        pValues[pSimplex->m_numVerticesA + b] = (uint8_t)(i << 4);
    }
    return result;
}

// @ 0x011120a0
// Signed offset of a contact along the separating direction, for one body: the segment point
// p0..p1 is interpolated at t, the vector from it to the given point is crossed with the body's
// basis vector and dotted with the separating axis, and the negative result is scaled by the
// sign-dependent constant.  The routine is x87 and keeps its two point arguments in ebx / edi,
// which no x86 calling convention provides; they are passed explicitly here.
static hkReal __forceinline GskContactOffset(const hkGskSolveBody* pBody, hkReal t,
                                             const hkVector4& point, const hkReal* pBasis,
                                             const hkVector4& axis)
{
    hkReal s = (t - pBody->m_start) * pBody->m_invRange;
    hkReal inv = HK_REAL_ONE - s;

    hkVector4 centre;
    centre.x = inv * pBody->m_p0[0] + s * pBody->m_p1[0];
    centre.y = inv * pBody->m_p0[1] + s * pBody->m_p1[1];
    centre.z = inv * pBody->m_p0[2] + s * pBody->m_p1[2];

    hkVector4 d;
    d.x = point.x - centre.x;
    d.y = point.y - centre.y;
    d.z = point.z - centre.z;

    hkVector4 cross;
    cross.x = d.y * pBasis[2] - d.z * pBasis[1];
    cross.y = d.z * pBasis[0] - d.x * pBasis[2];
    cross.z = d.x * pBasis[1] - d.y * pBasis[0];

    hkReal v = cross.x * axis.x + cross.y * axis.y + cross.z * axis.z;
    if (!(v < HK_REAL_ZERO))
        v *= gGskPositiveScale;
    else
        v *= gGskNegativeScale;
    return v;
}

hkReal __fastcall hkGsk_ContactDistance(const hkGskFrame* pFrame, const hkVector4* pAxis,
                                        const hkGskSolveBody* pBodyA, const hkGskSolveBody* pBodyB,
                                        hkReal t, const hkVector4* pPointA, const hkVector4* pPointB)
{
    hkReal a = GskContactOffset(pBodyA, t, *pPointA, pFrame->m_u0, *pAxis);
    hkReal b = GskContactOffset(pBodyB, t, *pPointB, pFrame->m_u1, *pAxis);
    return a - b;
}
