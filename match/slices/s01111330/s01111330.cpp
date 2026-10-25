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

    void setFrom(const hkVector4* pSource);              // 0x01103af0
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
    union                                           // +0x00 the two ids the row was built from
    {
        struct { uint8_t m_id0, m_id1; uint16_t m_value; };
        uint32_t m_head;                            // +0x00 both ids and the value as one word
    };
    union                                           // +0x04 packed per-vertex byte offsets
    {
        uint8_t  m_payload[4];
        uint32_t m_tail;                            // +0x04 the same four bytes as one word
    };
};

// Working simplex: a 4-slot, most-recently-used-first table of rows.  The packed 16-bit values
// follow the live rows directly, and the 4 bytes at +0x08 (row 0's payload) double as the packed
// per-vertex value indices of the simplex.
struct hkPackedSimplex
{
    uint8_t     m_numVerticesA;   // +0x00
    uint8_t     m_numVerticesB;   // +0x01
    uint8_t     m_numRows;        // +0x02, at most 4
    uint8_t     m_pad03;          // +0x03
    hkPackedRow m_rows[4];        // +0x04

    uint16_t* wordValues() { return (uint16_t*)((uint8_t*)this + 4 + m_numRows * 8u); }
    uint8_t*  valueBytes() { return (uint8_t*)this + 8; }
    void      removeUnusedVertices();                           // 0x0110fc50
};

// One candidate vertex handed to the insert routine: a position vector plus the packed index the
// manifold assigned to it.
struct hkGskInsertPoint
{
    hkVector4 m_position;         // +0x00
    unsigned  m_pad10[4];         // +0x10
    uint16_t  m_index;            // +0x20
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

// @ 0x01111d90
// Inserts a vertex into the working simplex.  With four rows present the oldest row is dropped
// through Simplex5::SelectVertexToDrop and the manifold is asked for the new index; otherwise the
// new row is prepended and the packed per-vertex values are recorded.  Returns 4 when the simplex
// was updated, 5 when no vertex could be dropped and 6 after a manifold-level replacement.
int __cdecl hkPackedSimplex_InsertVertex(hkPackedSimplex* pSimplex, void* a2, void* a3, void* a4,
                                         const hkSimplexKey* pKey, hkGskInsertPoint* pPoint,
                                         Simplex5* pSimplex5, hkGskInterface* pInterface,
                                         int bReplace)
{
    int result = 4;
    uint16_t packed;
    if (pSimplex->m_numRows == 4)
    {
        int dropped = pSimplex5->SelectVertexToDrop();
        if (dropped == 4)
            return 5;

        pInterface->v10(pSimplex->m_rows[dropped].m_value);

        // the dropped slot takes over the newest row; slot 0 takes row 1
        hkPackedRow* pDropped = &pSimplex->m_rows[dropped];
        if (dropped != 0)
            *pDropped = pSimplex->m_rows[0];
        else
            *pDropped = pSimplex->m_rows[1];

        pSimplex->removeUnusedVertices();

        uint16_t index = pInterface->v08(a2, a3, a4, pPoint);
        packed = index;
        if (index == 0xffff)
        {
            // the manifold replaced the vertex instead: drop the last simplex row and shift
            pSimplex->m_rows[0].m_tail = pSimplex->m_rows[3].m_tail;
            uint8_t  count = (uint8_t)(pSimplex->m_numRows - 1);
            pSimplex->m_numRows = count;
            pSimplex->m_rows[0].m_head = pSimplex->m_rows[3].m_head;
            uint8_t*  pBase = (uint8_t*)pSimplex + count * 8;
            uint32_t* pDst = (uint32_t*)(pBase + 4);
            uint32_t* pSrc = (uint32_t*)(pBase + 0xc);
            int n = ((int)pSimplex->m_numVerticesB + (int)pSimplex->m_numVerticesA - 1) >> 1;
            for (int i = 0; i <= n; ++i)
            {
                *pDst = *pSrc;
                ++pDst;
                ++pSrc;
            }
            pSimplex5->m_v[dropped].setFrom(&pSimplex5->m_v[3].m_position);
            return 6;
        }

        pPoint->m_index = index;
        pSimplex5->m_v[dropped].setFrom(&pPoint->m_position);
        result = dropped;
    }
    else
    {
        if (bReplace != 0 && pKey->m_ids[1] != 3)
        {
            packed = 0xffff;
        }
        else
        {
            packed = pInterface->v08(a2, a3, a4, pPoint);
            if (packed == 0xffff)
                return 5;
        }
        pPoint->m_index = packed;

        // make room in the middle of the packed-value words and append the old row 0
        int n = ((int)pSimplex->m_numVerticesB + (int)pSimplex->m_numVerticesA - 1) >> 1;
        int slot = n + (int)pSimplex->m_numRows * 2;
        uint32_t* pDst = (uint32_t*)((uint8_t*)pSimplex + slot * 4 + 4);
        uint32_t* pSrc = (uint32_t*)((uint8_t*)pSimplex + slot * 4 + 0xc);
        for (int i = n; i >= 0; --i)
        {
            *pDst = *pSrc;
            --pDst;
            --pSrc;
        }
        pSimplex->m_rows[pSimplex->m_numRows] = pSimplex->m_rows[0];
        ++pSimplex->m_numRows;
    }

    // fill row 0 from the key
    pSimplex->m_rows[0].m_id0 = (uint8_t)pKey->m_ids[0];
    pSimplex->m_rows[0].m_id1 = (uint8_t)pKey->m_ids[1];
    pSimplex->m_rows[0].m_value = packed;
    pSimplex->m_rows[0].m_tail = 0;

    // record one packed byte per simplex vertex; the 16-bit values live right after the rows
    uint16_t* pWordValues = pSimplex->wordValues();
    uint8_t* pValues = pSimplex->valueBytes();
    int offset = 0;
    for (int a = 0; a < pKey->m_ids[0]; ++a)
    {
        uint16_t v = pKey->m_values[a];
        int i = 0;
        for (; i < (int)pSimplex->m_numVerticesA; ++i)
            if (pWordValues[i] == v)
                goto foundA;

        {
            int n = (int)pSimplex->m_numVerticesA + (int)pSimplex->m_numVerticesB;
            for (int j = n; j > i; --j)
                pWordValues[j] = pWordValues[j - 1];
            pWordValues[i] = v;
            ++pSimplex->m_numVerticesA;
            offset += 0x10;
        }
    foundA:
        pValues[a] = (uint8_t)(i << 4);
    }
    if (offset)
    {
        for (int r = 1; r < (int)pSimplex->m_numRows; ++r)
        {
            hkPackedRow* pRow = &pSimplex->m_rows[r];
            for (int i = (int)pRow->m_id0; i < (int)pRow->m_id0 + (int)pRow->m_id1; ++i)
            {
                uint8_t value = pRow->m_payload[i];
                value = (uint8_t)(value + (uint8_t)offset);
                pRow->m_payload[i] = value;
            }
        }
    }
    for (int b = 0; b < pKey->m_ids[1]; ++b)
    {
        uint16_t v = pKey->m_values[pKey->m_ids[0] + b];
        int i = (int)pSimplex->m_numVerticesA;
        int n = (int)pSimplex->m_numVerticesA + (int)pSimplex->m_numVerticesB;
        for (; i < n; ++i)
            if (pWordValues[i] == v)
                goto foundB;

        pWordValues[i] = v;
        ++pSimplex->m_numVerticesB;
    foundB:
        pValues[pKey->m_ids[0] + b] = (uint8_t)(i << 4);
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
