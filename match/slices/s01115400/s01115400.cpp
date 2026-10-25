// Slice s01115400: Havok MOPP cast virtual machine and convex-hull builder
// helpers (vector predicates, quicksort specialisations, AABB fitting).

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int  uint;

// hkBool is a one byte class with user defined copy semantics, so it comes back
// through a hidden return pointer.
struct hkBool
{
    uchar m_bool;
    hkBool(uchar b) : m_bool(b) {}
    hkBool(const hkBool& o) : m_bool(o.m_bool) {}
    operator uchar() const { return m_bool; }
};

struct hkVector4
{
    float x, y, z, w;

    hkVector4 Sub(const hkVector4& other) const;      // 011159c0
};

// ------------------------------------------------------------------ 011159c0
// @ 0x011159c0
hkVector4 hkVector4::Sub(const hkVector4& other) const
{
    hkVector4 r;
    r.x = other.x - x;
    r.y = other.y - y;
    r.z = other.z - z;
    r.w = other.w - w;
    return r;
}

struct hkGeomConvexHullBuilder
{
    static hkBool vectorLessAndMergeCoordinates(hkVector4& a, hkVector4& b);   // 01115950
    static void getAabb(const struct hkArrayVector4& verts, struct hkAabb& aabb); // 01115d00
    static void convertFromUnitCube(struct hkArrayVector4& verts, hkVector4& scale,
                                    hkVector4& translation);                   // 01116050
};

// ------------------------------------------------------------------ 01115950
// Lexicographic (x, y, z) "less or equal" used while merging duplicate hull
// vertices; equal coordinates are merged (returns false).
// @ 0x01115950
hkBool hkGeomConvexHullBuilder::vectorLessAndMergeCoordinates(hkVector4& a, hkVector4& b)
{
    if (b.x <= a.x &&
        (a.x != b.x || b.y <= a.y) &&
        (a.x != b.x || a.y != b.y || b.z <= a.z))
        return hkBool(0);
    return hkBool(1);
}

// ------------------------------------------------------------------ 011159f0
// Sort predicate on the y coordinate.
// @ 0x011159f0
hkBool sortByY(const hkVector4& a, const hkVector4& b)
{
    return hkBool(!(a.y >= b.y));
}

// ------------------------------------------------------------------ 01115a20
// Sort predicate on the w coordinate.
// @ 0x01115a20
hkBool sortByW(const hkVector4& a, const hkVector4& b)
{
    return hkBool(!(a.w >= b.w));
}

// =====================================================================
// Quicksort specialisations
// =====================================================================

typedef hkBool (*hkVector4Less)(hkVector4&, hkVector4&);

// ------------------------------------------------------------------ 011155b0
// @ 0x011155b0
void quickSortVector4(hkVector4* base, int lo, int hi, hkVector4Less less)
{
    int i;
    int j;
    do
    {
        hkVector4 pivot = base[(lo + hi) >> 1];
        i = lo;
        j = hi;
        do
        {
            while (less(base[i], pivot))
                ++i;
            while (less(pivot, base[j]))
                --j;
            if (j < i)
                break;
            if (j != i)
            {
                hkVector4 t = base[j];
                base[j] = base[i];
                base[i] = t;
            }
            --j;
            ++i;
        } while (i <= j);

        if (lo < j)
            quickSortVector4(base, lo, j, less);
        lo = i;
    } while (hi > i);
}

// 8 byte neighbour record for the hull builder's y sweep.
struct WeightedNeighbour
{
    float m_weight;
    float m_key;
};

typedef hkBool (*WeightedNeighbourLess)(const WeightedNeighbour&, const WeightedNeighbour&);

// ------------------------------------------------------------------ 01115bf0
// @ 0x01115bf0
void quickSortWeightedNeighbour(WeightedNeighbour* base, int lo, int hi,
                                WeightedNeighbourLess less)
{
    int i;
    int j;
    do
    {
        WeightedNeighbour pivot = base[(lo + hi) >> 1];
        i = lo;
        j = hi;
        do
        {
            while (less(base[i], pivot))
                ++i;
            while (less(pivot, base[j]))
                --j;
            if (j < i)
                break;
            if (j != i)
            {
                WeightedNeighbour t = base[j];
                base[j] = base[i];
                base[i] = t;
            }
            --j;
            ++i;
        } while (i <= j);

        if (lo < j)
            quickSortWeightedNeighbour(base, lo, j, less);
        lo = i;
    } while (hi > i);
}

// 20 byte plane record (plane equation plus distance) used by the merge step.
struct HullPlane
{
    hkVector4 m_plane;
    float m_dist;
};

typedef hkBool (*HullPlaneLess)(const HullPlane&, const HullPlane&);

extern hkBool hullPlaneLess(const HullPlane& a, const HullPlane& b);

// ------------------------------------------------------------------ 01115a50
// @ 0x01115a50
void quickSortHullPlane(HullPlane* base, int lo, int hi, HullPlaneLess less)
{
    int i;
    int j;
    do
    {
        HullPlane pivot = base[(lo + hi) >> 1];
        i = lo;
        j = hi;
        do
        {
            while (less(base[i], pivot))
                ++i;
            while (less(pivot, base[j]))
                --j;
            if (j < i)
                break;
            if (j != i)
            {
                HullPlane t = base[j];
                base[j] = base[i];
                base[i] = t;
            }
            --j;
            ++i;
        } while (i <= j);

        if (lo < j)
            quickSortHullPlane(base, lo, j, less);
        lo = i;
    } while (hi > i);
}

// =====================================================================
// Convex hull builder helpers
// =====================================================================

struct hkArrayVector4
{
    hkVector4* m_data;
    int m_size;
    int m_capacity;
};

struct hkAabb
{
    hkVector4 m_min;
    hkVector4 m_max;
};

// ------------------------------------------------------------------ 01115d00
// @ 0x01115d00
void hkGeomConvexHullBuilder::getAabb(const hkArrayVector4& verts, hkAabb& aabb)
{
    if (verts.m_size < 1)
        return;

    const hkVector4& first = verts.m_data[0];
    aabb.m_min = first;
    aabb.m_max = first;

    for (int i = 0; i < verts.m_size; ++i)
    {
        const hkVector4& v = verts.m_data[i];
        if (v.x < aabb.m_min.x) aabb.m_min.x = v.x;
        if (v.x > aabb.m_max.x) aabb.m_max.x = v.x;
        if (v.y < aabb.m_min.y) aabb.m_min.y = v.y;
        if (v.y > aabb.m_max.y) aabb.m_max.y = v.y;
        if (v.z < aabb.m_min.z) aabb.m_min.z = v.z;
        if (v.z > aabb.m_max.z) aabb.m_max.z = v.z;
    }
}

struct hkMatrix3
{
    hkVector4 m_row[3];

    void mul(const hkMatrix3& other);
};

extern float g_vecZero[3];

// ------------------------------------------------------------------ 01115e20
// Recentres the hull vertices on the centre of their AABB and scales them by
// the reciprocal extents, so that the builder works in a unit cube.
// @ 0x01115e20
void recentreVertices(hkArrayVector4* verts, hkVector4* extents, hkVector4* center)
{
    hkAabb aabb;
    hkGeomConvexHullBuilder::getAabb(*verts, aabb);

    center->x = aabb.m_min.x + aabb.m_max.x;
    center->y = aabb.m_min.y + aabb.m_max.y;
    center->z = aabb.m_min.z + aabb.m_max.z;
    center->w = aabb.m_min.w + aabb.m_max.w;
    center->x = center->x * 0.5f;
    center->y = center->y * 0.5f;
    center->z = center->z * 0.5f;
    center->w = center->w * 0.5f;

    extents->x = aabb.m_max.x - aabb.m_min.x;
    extents->y = aabb.m_max.y - aabb.m_min.y;
    extents->z = aabb.m_max.z - aabb.m_min.z;
    extents->w = aabb.m_max.w - aabb.m_min.w;

    hkMatrix3 inv;
    inv.m_row[0].x = 1.0f;
    if (1.1920929e-07f < extents->z)
        inv.m_row[2].z = 1.0f / extents->z;
    else
        inv.m_row[2].z = 1.0f;
    if (1.1920929e-07f < extents->y)
        inv.m_row[1].y = 1.0f / extents->y;
    else
        inv.m_row[1].y = 1.0f;
    if (1.1920929e-07f < extents->x)
        inv.m_row[0].x = 1.0f / extents->x;
    else
        inv.m_row[0].x = 1.0f;
    inv.m_row[0].y = 0.0f;
    inv.m_row[0].z = 0.0f;
    inv.m_row[0].w = 0.0f;
    inv.m_row[1].x = 0.0f;
    inv.m_row[1].z = 0.0f;
    inv.m_row[1].w = 0.0f;
    inv.m_row[2].x = 0.0f;
    inv.m_row[2].y = 0.0f;
    inv.m_row[2].w = 0.0f;

    for (int i = 0; i < verts->m_size; ++i)
    {
        hkVector4& v = verts->m_data[i];
        float ox = v.x - center->x;
        float oy = v.y - center->y;
        float oz = v.z - center->z;

        hkMatrix3 m;
        m.m_row[0].x = ox;
        m.m_row[0].y = g_vecZero[0];
        m.m_row[0].z = g_vecZero[0];
        m.m_row[0].w = 0.0f;
        m.m_row[1].x = oy;
        m.m_row[1].y = g_vecZero[1];
        m.m_row[1].z = g_vecZero[1];
        m.m_row[1].w = 0.0f;
        m.m_row[2].x = oz;
        m.m_row[2].y = g_vecZero[2];
        m.m_row[2].z = g_vecZero[2];
        m.m_row[2].w = 0.0f;

        m.mul(inv);

        v.x = m.m_row[0].x;
        v.y = m.m_row[1].x;
        v.z = m.m_row[2].x;
        v.w = 0.0f;
    }
}

// ------------------------------------------------------------------ 01116050
// Scales the unit cube vertices by the given scale vector and translates them.
// @ 0x01116050
void hkGeomConvexHullBuilder::convertFromUnitCube(hkArrayVector4& verts, hkVector4& scale,
                                                   hkVector4& translation)
{
    hkMatrix3 scaleM;
    scaleM.m_row[0].x = scale.x;
    scaleM.m_row[0].y = 0.0f;
    scaleM.m_row[0].z = 0.0f;
    scaleM.m_row[0].w = 0.0f;
    scaleM.m_row[1].x = 0.0f;
    scaleM.m_row[1].y = scale.y;
    scaleM.m_row[1].z = 0.0f;
    scaleM.m_row[1].w = 0.0f;
    scaleM.m_row[2].x = 0.0f;
    scaleM.m_row[2].y = 0.0f;
    scaleM.m_row[2].z = scale.z;
    scaleM.m_row[2].w = 0.0f;

    for (int i = 0; i < verts.m_size; ++i)
    {
        hkVector4& v = verts.m_data[i];

        hkMatrix3 m;
        m.m_row[0].x = v.x;
        m.m_row[0].y = g_vecZero[0];
        m.m_row[0].z = g_vecZero[0];
        m.m_row[0].w = 0.0f;
        m.m_row[1].x = v.y;
        m.m_row[1].y = g_vecZero[1];
        m.m_row[1].z = g_vecZero[1];
        m.m_row[1].w = 0.0f;
        m.m_row[2].x = v.z;
        m.m_row[2].y = g_vecZero[2];
        m.m_row[2].z = g_vecZero[2];
        m.m_row[2].w = 0.0f;

        m.mul(scaleM);

        v.x = m.m_row[0].x;
        v.y = m.m_row[1].x;
        v.z = m.m_row[2].x;
        v.w = 0.0f;

        v.x = v.x + translation.x;
        v.y = translation.y + v.y;
        v.z = translation.z + v.z;
        v.w = translation.w + v.w;
    }
}
// =====================================================================
// MOPP AABB cast virtual machine
// =====================================================================

struct hkCdPointCollector;

struct hkAabbCastInput
{
    hkVector4 m_aabb[2];      // 0x00 .. 0x1f
    float     m_pad[6];       // 0x20 .. 0x37
    void*     m_objA;         // 0x38
    void*     m_shape;        // 0x3c
};

struct hkMoppAabbCastVirtualMachine
{
    char      m_pad0[0x10];
    void*     m_mopp;         // 0x10
    float     m_invScale;     // 0x14
    void*     m_param18;      // 0x18
    float     m_f1c;          // 0x1c
    float     m_f20;          // 0x20
    void*     m_collector;    // 0x24
    void*     m_collector2;   // 0x28
    const hkAabbCastInput* m_input;   // 0x2c
    void*     m_mopp_at_0x20; // mopp bytecode pointer

    void aabbCast(const hkAabbCastInput& input, hkCdPointCollector& collector,
                  hkCdPointCollector* collector2);

    void m_step(const hkVector4* offset, const uchar* code, hkVector4* points); // 01114370
};

// Virtual dispatch helper: calls slot <index> of the object's vtable.
typedef void* (__thiscall* HkVtFunc)(void*);
__forceinline HkVtFunc Vt(void* obj, int index)
{
    return ((HkVtFunc*)(*(void***)obj))[index];
}

static uchar s_moppMemReady;                 // 0x016e5ac1

extern uchar hkThreadMemoryInit(int requirement);

// ------------------------------------------------------------------ 01115400
// @ 0x01115400
void hkMoppAabbCastVirtualMachine::aabbCast(const hkAabbCastInput& input,
                                            hkCdPointCollector& collector,
                                            hkCdPointCollector* collector2)
{
    if (s_moppMemReady == 0 &&
        (s_moppMemReady = hkThreadMemoryInit(4), s_moppMemReady == 0))
        return;

    m_input = &input;

    void* shape = (void*)input.m_shape;
    void* moppVt = *(void**)*(void**)((const char*)&input + 0x38);
    m_mopp = *(void**)((const char*)moppVt + 0x10);

    m_collector = &collector;
    m_collector2 = collector2;

    void* p1 = *(void**)((const char*)&input + 0x34);
    void* shapeObj = *(void**)p1;
    m_param18 = Vt(shapeObj, 2)(shapeObj);

    m_f1c = 1.0f;
    m_f20 = 1.0f;

    const char* m = (const char*)m_mopp;
    m_mopp_at_0x20 = *(void**)(m + 0x20);
    hkVector4 offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = 0.0f;
    offset.w = 0.0f;

    float w = *(float*)(m + 0x1c);
    m_invScale = 1.0f / w;

    float t = w * 2.3283064e-10f;
    hkVector4 tmp;
    tmp.x = t * input.m_aabb[1].x;
    tmp.y = t * input.m_aabb[1].y;
    tmp.z = t * input.m_aabb[1].z;
    tmp.w = t * input.m_aabb[1].w;

    float sum = (input.m_aabb[1].z + input.m_aabb[1].y + input.m_aabb[1].x) * 3.0f;

    hkVector4 pts[2];
    pts[0].x = (input.m_aabb[0].x - *(float*)(m + 0x10)) * t;
    pts[0].y = (input.m_aabb[0].y - *(float*)(m + 0x14)) * t;
    pts[0].z = (input.m_aabb[0].z - *(float*)(m + 0x18)) * t;
    pts[0].w = (input.m_aabb[0].w - *(float*)(m + 0x1c)) * t;
    pts[1].x = (input.m_aabb[1].x - *(float*)(m + 0x10)) * t;
    pts[1].y = (input.m_aabb[1].y - *(float*)(m + 0x14)) * t;
    pts[1].z = (input.m_aabb[1].z - *(float*)(m + 0x18)) * t;
    pts[1].w = (input.m_aabb[1].w - *(float*)(m + 0x1c)) * t;

    (void)shape;
    (void)sum;
    m_step(&offset, (const uchar*)(const char*)m_mopp_at_0x20, pts);
}

// ------------------------------------------------------------------ 01115730
// Edge-pair welding test for two hull triangles: reports whether the edge pair
// (a0,a1) of one face and (b0,b1) of an opposing face are shared, taking the
// four shared-endpoint / opposite-orientation permutations into account.
// @ 0x01115730
struct hkGeomEdge
{
    ushort m_vertex;   // +0
    ushort m_twin;     // +2 (index of the opposite half-edge)
    ushort m_next;     // +4
    ushort m_pad;      // +6
};

// The twin lookup: the vertex opposite e in the edge array.
#define TWIN(e) (edges[(e)->m_twin].m_vertex)

hkBool sharesEdgePair(const hkGeomEdge* edges, const hkGeomEdge* a0,
                      const hkGeomEdge* b0, const hkGeomEdge* a1,
                      const hkGeomEdge* b1)
{
    bool e0 = a0 != b0 && a0->m_vertex == b0->m_vertex && TWIN(a0) != TWIN(b0);
    bool e1 = a1 != b1 && a1->m_vertex == b1->m_vertex && TWIN(a1) != TWIN(b1);
    if (!(e0 && e1))
        return hkBool(0);

    // Block D: pairing (a0, b1) decides whether the two faces keep the edge.
    bool aPairOk = a0 == b1 || a0->m_vertex != b1->m_vertex || TWIN(a0) == TWIN(b1);
    // Block E: pairing (a1, b1).
    bool ePairAlign = a1 != b1 && a1->m_vertex == b1->m_vertex && TWIN(a1) == TWIN(b1);

    // Block F/G: fold the (a0, b1) and (a1, b1) twin pairings.
    bool t0Matches = TWIN(a0) == b1->m_vertex && TWIN(b1) == a0->m_vertex;
    bool p0AgainstB1 = &edges[a0->m_twin] == b1;
    bool t1Matches = TWIN(a1) == b1->m_vertex && TWIN(b1) == a1->m_vertex;
    bool p1AgainstB1 = &edges[a1->m_twin] == b1;
    bool t1PairOk = t1Matches && p1AgainstB1;

    bool reachedF = !aPairOk || ePairAlign == false;
    bool z;
    if (reachedF && t0Matches && !p0AgainstB1)
        z = true;
    else
        z = !t1PairOk;

    // Blocks I/J/K/M: fold the (a0, b0) and (a1, b0) pairings.
    bool m0 = a0 != b0 && a0->m_vertex == b0->m_vertex && TWIN(a0) == TWIN(b0);
    bool m1 = a1 != b0 && a1->m_vertex == b0->m_vertex && TWIN(a1) == TWIN(b0);
    bool c0a = &edges[a0->m_twin] == b0 && edges[a0->m_twin].m_vertex == b0->m_vertex
        && TWIN(b0) == a0->m_vertex;
    bool t1AgainstB0 = &edges[a1->m_twin] == b0 && TWIN(a1) == b0->m_vertex
        && TWIN(b0) == a1->m_vertex;
    bool h = z ? (m0 || !m1 ? !c0a : false) : false;

    return hkBool(h ? 1 : 0);
}

// 20 byte plane predicate stub so the instantiation has a distinct type.
hkBool hullPlaneLess(const HullPlane& a, const HullPlane& b)
{
    return hkBool(!(a.m_dist >= b.m_dist));
}
