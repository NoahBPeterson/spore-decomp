// slice s009c32c0 -- nSPCreatureAnim::ComputeHierarchy (5993 B, /O2 + /arch:SSE, big chkstk frame).
//
// Picks the root body of a creature skeleton (an explicit "root" cap, else the spine nearest the
// origin, else the spine with the most feet below it, else a spine half way up the longest spine
// chain), re-roots the body tree there, sorts the bodies into hierarchy order, rebuilds every body's
// parent-relative rest rotation, the inverse bone rest transforms, the symmetry links, parent/child
// pointers, workspace radii and the leg-chain flags.
//
// Types: the dev-PDB nSPCreatureAnim::creature_static_data / creature_body_static_data, with the
// retail offsets read from the disassembly (retail body stride is 0x468, dev was 0x44c).
// Flags: /O2 /MD /Gy /TP /arch:SSE   (no /EHsc: the fixed_vector dtors have no EH frame)
#include "types.h"

typedef unsigned char  uint8;
typedef unsigned int   uint32;

extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744 thunk
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
void operator delete[](void* p);                                          // 0x00f47380

namespace checkerlib {
struct vector_3 { float x, y, z; };
struct vector_4 { float x, y, z, w; };
struct matrix_3x3 { float m[3][3]; };
}  // namespace checkerlib

using checkerlib::vector_3;
using checkerlib::vector_4;
using checkerlib::matrix_3x3;

namespace eastl {

template <typename T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
template <typename T> inline void swap(T& a, T& b) { T temp(a); a = b; b = temp; }

// Array storage from operator new[] with the element count in front; free only if non-empty.
struct sp_vector_allocator {
    sp_vector_allocator() {}
    void deallocate(void* p) { if (((int*)p)[-1] != 0) operator delete[](p); }
};

template <typename T> struct pair { T first; };

// eastl::fixed_vector<T, 255, true> as laid out in this build: VectorBase, then the
// fixed_vector_allocator (overflow allocator + pool begin), then the inline buffer.
template <typename T, int nodeCount>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32 mOverflowAllocator;
    T* mpPoolBegin;
    uint32 mPad;
    T mBuffer[nodeCount];

    fixed_vector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + nodeCount)
    {
        mpPoolBegin = mBuffer;
    }
    fixed_vector(unsigned n, const T& value);                    // 0x009c3210
    ~fixed_vector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }

    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](unsigned i) { return mpBegin[i]; }

    void DoInsertValue(T* position, const T& value);             // 0x00899480
    void DoInsertValues(T* position, unsigned n, const T& value);  // 0x0089a8e0

    void push_back(const T& value)                               // out of line: 0x00886db0
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p)
                *p = value;
        } else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void resize(unsigned n)                                      // out of line: 0x0089cb60
    {
        T value = T();
        unsigned s = size();
        if (n > s)
            DoInsertValues(mpEnd, n - s, value);
        else
            erase(mpBegin + n, mpEnd);
    }
};

}  // namespace eastl

namespace nSPCreatureAnim {

// Cap name FOURCCs (stored little-endian, so the bytes in memory spell the word).
enum {
    kCapNameRoot    = 0x746f6f72,   // "root"
    kCapNameFoot    = 0x746f6f66,   // "foot"
    kCapNameMouth   = 0x74756f6d,   // "mout"
    kCapNameLimb    = 0x626d696c,   // "limb"
    kCapNameSpine   = 0x6e697073,   // "spin"
    kCapNameGrasper = 0x70737267,   // "grsp"
    kCapNamePsft    = 0x74667370,   // "psft"
    kCapNameNstr    = 0x7274736e,   // "nstr"
};
enum {
    kCapRoot    = 0x01,
    kCapLimb    = 0x02,
    kCapFoot    = 0x04,
    kCapSpine   = 0x08,
    kCapPsft    = 0x10,
    kCapMouth   = 0x20,
    kCapGrasper = 0x40,
    kCapNstr    = 0x80,
};

struct creature_body_static_data {                // retail size 0x468
    char name[260];                                // 0x000
    uint32 instance_id;                            // 0x104
    uint32 group_id;                               // 0x108
    vector_3 rest_center;                          // 0x10c
    vector_4 rest_orientation_q;                   // 0x118
    vector_4 rest_parent_rel_orientation_q;        // 0x128
    uint32 pad138[3];
    vector_3 rest_joint_offset;                    // 0x144
    uint32 cap_flags;                              // 0x150  every cap present
    uint32 owned_cap_flags;                        // 0x154  caps with a non-zero value
    uint32 NameFOURCCs[32];                        // 0x158
    uint8 Values[32];                              // 0x1d8
    uint32 bidx;                                   // 0x1f8
    int parent_bidx;                               // 0x1fc
    int symmetric_bidx;                            // 0x200  -2 = not computed yet
    int first_child_bidx;                          // 0x204
    uint32 num_children;                           // 0x208
    uint32 pad20c[2];
    creature_body_static_data* parent;             // 0x214
    creature_body_static_data* first_child;        // 0x218
    uint32 bone_idx;                               // 0x21c
    uint32 pad220[73];
    vector_3 local_joint_r;                        // 0x344
    vector_3 parent_local_joint_r;                 // 0x350
    vector_3 joint_r;                              // 0x35c
    float joint_r_len;                             // 0x368
    float workspace_radius;                        // 0x36c
    uint32 pad370[61];
    bool in_leg_chain;                             // 0x464
    uint8 pad465[3];

    void CopyFrom(const creature_body_static_data& other);   // 0x009b3490
};

struct body_vector {                               // eastl::vector<creature_body_static_data, sp_vector_allocator>
    creature_body_static_data* mpBegin;
    creature_body_static_data* mpEnd;
    creature_body_static_data* mpCapacity;
    eastl::sp_vector_allocator mAllocator;

    body_vector(unsigned n, const eastl::sp_vector_allocator& allocator);   // 0x009c0bb0
    ~body_vector()
    {
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    creature_body_static_data& operator[](unsigned i) { return mpBegin[i]; }
    void swap(body_vector& other);                 // 0x009c0ed0
};

struct bone_xform {                                // eastl::pair<matrix_3x3, vector_3>
    matrix_3x3 first;
    vector_3 second;
};
struct bone_xform_vector {
    bone_xform* mpBegin;
    bone_xform* mpEnd;
    bone_xform* mpCapacity;
    uint32 mAllocator;
    void resize(unsigned n);                       // 0x009c2520
};

struct creature_static_data {
    uint8 pad0[0x37c];
    uint32 num_bones;                              // 0x37c
    uint32 pad380;
    body_vector Bodies;                            // 0x384
    uint32 pad394[6];
    uint32 spine_start_bidx;                       // 0x3ac
    uint32 spine_end_bidx;                         // 0x3b0
    uint32 pad3b4[16];
    bool mIsLegless;                               // 0x3f4
    uint8 pad3f5[3];
    bone_xform_vector inv_bone_rest_xforms;        // 0x3f8
};

typedef eastl::fixed_vector<uint32, 255> index_vector;

extern int g_bRootAtClosestSpine;      // 0x0166c004
extern int g_bRootAtMidSpine;          // 0x01550a84
extern float g_WorkspaceRadiusPad;     // 0x01550a10
extern float g_WorkspaceRadiusScale;   // 0x01550a78

void AddExtraBonesAsNecessary(creature_static_data* c, uint32 bidx);   // 0x009b5f90 (bidx in eax)
void ComputeBodyStatics(creature_static_data* c);                      // 0x009b5c50
void BuildHierarchyOrder(creature_static_data* c, index_vector* order,
                         index_vector* children, uint32 root);          // 0x009c3150

inline uint32 CapFlagFromName(uint32 name)
{
    switch (name) {
    case kCapNameSpine:   return kCapSpine;
    case kCapNameLimb:    return kCapLimb;
    case kCapNameGrasper: return kCapGrasper;
    case kCapNameNstr:    return kCapNstr;
    case kCapNamePsft:    return kCapPsft;
    case kCapNameFoot:    return kCapFoot;
    case kCapNameRoot:    return kCapRoot;
    case kCapNameMouth:   return kCapMouth;
    default:              return 0;
    }
}

// Inverse rest transform of a body: rotation = matrix of conj(q), translation = -rotate(q, center).
__forceinline void ComputeInverseRestXform(const creature_body_static_data& b, bone_xform& out)
{
    const vector_4& q = b.rest_orientation_q;
    const vector_3& p = b.rest_center;

    float nxw = -(q.x * q.w);
    float nzw = -(q.z * q.w);
    float zx = q.z * q.x;
    float nxx = -(q.x * q.x);
    float yx = q.y * q.x;
    float zy = q.z * q.y;
    float nyw = -(q.y * q.w);
    float nyy = -(q.y * q.y);
    float nzz = -(q.z * q.z);
    vector_3 t;
    t.x = -((((nzz + nyy) * p.x + (zx + nyw) * p.z) + (yx - nzw) * p.y) * 2.0f + p.x);
    t.y = -((((yx + nzw) * p.x + (zy - nxw) * p.z) + (nzz + nxx) * p.y) * 2.0f + p.y);
    t.z = -((((zx - nyw) * p.x + (nyy + nxx) * p.z) + (zy + nxw) * p.y) * 2.0f + p.z);

    float cx = -q.x, cy = -q.y, cz = -q.z, w = q.w;
    float xx = cx * cx, xy = cx * cy, yy = cy * cy, xz = cx * cz, yz = cy * cz;
    float xw = cx * w, zz = cz * cz, wy = w * cy, wz = w * cz;
    matrix_3x3 r;
    r.m[0][0] = 1.0f - (zz + yy) * 2.0f;
    r.m[0][1] = (xy - wz) * 2.0f;
    r.m[0][2] = (wy + xz) * 2.0f;
    r.m[1][0] = (wz + xy) * 2.0f;
    r.m[1][1] = 1.0f - (zz + xx) * 2.0f;
    r.m[1][2] = (yz - xw) * 2.0f;
    r.m[2][0] = (xz - wy) * 2.0f;
    r.m[2][1] = (xw + yz) * 2.0f;
    r.m[2][2] = 1.0f - (yy + xx) * 2.0f;

    matrix_3x3 rot;
    for (int i = 0; i < 3; ++i) {
        rot.m[0][i] = r.m[0][i];
        rot.m[1][i] = r.m[1][i];
        rot.m[2][i] = r.m[2][i];
    }
    out.first = rot;
    out.second = t;
}

// @ 0x009c32c0
bool ComputeHierarchy(creature_static_data* c, uint32 target)
{
    if (c->Bodies.mpBegin == c->Bodies.mpEnd)
        return false;
    if (target >= c->Bodies.size())
        return false;
    if (!(c->Bodies[target].owned_cap_flags & kCapSpine))
        return false;
    if (c->Bodies[target].parent_bidx != -1)
        return false;

    // Trailing bodies without a bone don't count as bones.
    c->num_bones = c->Bodies.size();
    while (c->num_bones != 0 && c->Bodies[c->num_bones - 1].bone_idx == (uint32)-1)
        c->num_bones--;

    // Spines carrying the most feet (counted at the nearest spine ancestor of each foot).
    index_vector bestSpines;
    uint32 zero = 0;
    index_vector footCounts(c->Bodies.size(), zero);
    int rootCapBody = -1;
    {
        uint32 maxFeet = 0;
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data& b = c->Bodies[i];
            if (b.cap_flags & kCapRoot) {
                rootCapBody = i;
                break;
            }
            if (b.owned_cap_flags & kCapFoot) {
                uint32 spine = b.parent_bidx;
                while (spine != (uint32)-1 && !(c->Bodies[spine].owned_cap_flags & kCapSpine))
                    spine = c->Bodies[spine].parent_bidx;
                footCounts[spine]++;
                uint32 feet = footCounts[spine];
                if (feet > maxFeet) {
                    bestSpines.resize(0);
                    maxFeet = feet;
                    bestSpines.push_back(spine);
                } else if (feet == maxFeet) {
                    bestSpines.push_back(spine);
                }
            }
        }
    }

    // Inverse bone rest transforms, last spine index and symmetry links.
    c->spine_end_bidx = 0;
    c->spine_start_bidx = 0;
    c->inv_bone_rest_xforms.resize(c->num_bones);
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data& b = c->Bodies[i];
            uint32 bone = b.bone_idx;
            if (bone < c->num_bones)
                ComputeInverseRestXform(b, c->inv_bone_rest_xforms.mpBegin[bone]);

            if (b.owned_cap_flags & kCapSpine)
                c->spine_end_bidx = eastl::max(c->spine_end_bidx, (uint32)i);

            if (b.symmetric_bidx == -2) {
                vector_3 mirrored;
                mirrored.x = -b.rest_center.x;
                mirrored.y = b.rest_center.y;
                mirrored.z = b.rest_center.z;
                unsigned j;
                for (j = 0; j < n; ++j) {
                    if (i == j)
                        continue;
                    creature_body_static_data& o = c->Bodies[j];
                    double dx = (double)o.rest_center.x - mirrored.x;
                    double dy = (double)o.rest_center.y - mirrored.y;
                    double dz = (double)o.rest_center.z - mirrored.z;
                    if (!((dz * dz + dy * dy) + dx * dx < 1e-05))
                        continue;
                    unsigned k;
                    for (k = 0; k < 32; ++k) {
                        if (b.NameFOURCCs[k] == 0)
                            break;
                        if (b.NameFOURCCs[k] != o.NameFOURCCs[k])
                            break;
                    }
                    if (k < 32 && b.NameFOURCCs[k] != 0)
                        continue;   // caps differ
                    b.symmetric_bidx = j;
                    break;
                }
                if (j == n)
                    b.symmetric_bidx = -1;
            }
        }
    }

    // Choose the root.
    int root = -1;
    if (g_bRootAtClosestSpine) {
        float best = 3.402823466e+38f;
        int n = (int)c->Bodies.size();
        for (int i = 0; i < n; ++i) {
            creature_body_static_data& b = c->Bodies[i];
            if (b.owned_cap_flags & kCapSpine) {
                const vector_3& p = b.rest_center;
                float d = (p.x * p.x + p.y * p.y) + p.z * p.z;
                if (d < best) {
                    best = d;
                    root = i;
                }
            }
        }
    }
    if (root == -1)
        root = rootCapBody;

    bool legless = bestSpines.empty();
    c->mIsLegless = legless;
    if (root == -1) {
        if (!legless) {
            // The highest spine among those carrying the most feet.
            float bestY = -3.402823466e+38f;
            unsigned count = bestSpines.size();
            for (unsigned k = 0; k < count; ++k) {
                uint32 idx = bestSpines[k];
                float y = c->Bodies[idx].rest_center.y;
                if (y > bestY) {
                    bestY = y;
                    root = idx;
                }
            }
        } else {
            root = 0;
            if (g_bRootAtMidSpine) {
                index_vector spines;
                unsigned n = c->Bodies.size();
                for (uint32 i = 0; i < n; ++i)
                    if (c->Bodies[i].owned_cap_flags & kCapSpine)
                        spines.push_back(i);
                unsigned numSpines = spines.size();
                if (numSpines > 2) {
                    // Child-spine counts; walk up half the spine count from a spine end.
                    index_vector childSpines;
                    childSpines.resize(n);
                    for (unsigned i = 0; i < n; ++i) {
                        creature_body_static_data& b = c->Bodies[i];
                        int p = b.parent_bidx;
                        if (p != -1 && (b.owned_cap_flags & kCapSpine))
                            childSpines[p]++;
                    }
                    for (unsigned k = 0; k < numSpines; ++k) {
                        uint32 idx = spines[k];
                        if (childSpines[idx] == 0) {
                            if (idx != (uint32)-1) {
                                for (unsigned steps = 0; steps < (numSpines >> 1); ++steps) {
                                    idx = c->Bodies[idx].parent_bidx;
                                    if (idx == (uint32)-1)
                                        break;
                                }
                                if (idx != (uint32)-1)
                                    root = idx;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    creature_body_static_data& rb = c->Bodies[root];
    if (!(rb.owned_cap_flags & kCapSpine))
        return false;

    // Give the root a "root" cap and recompute its cap flags.
    for (unsigned k = 0; k < 32; ++k) {
        if (rb.NameFOURCCs[k] == kCapNameRoot) {
            rb.Values[k] = 1;
            break;
        }
        if (rb.NameFOURCCs[k] == 0) {
            rb.NameFOURCCs[k] = kCapNameRoot;
            rb.Values[k] = 1;
            break;
        }
    }
    rb.owned_cap_flags = 0;
    rb.cap_flags = 0;
    for (unsigned k = 0; k < 32; ++k) {
        uint32 capName = rb.NameFOURCCs[k];
        if (capName == 0)
            break;
        uint32 flag = CapFlagFromName(capName);
        rb.cap_flags |= flag;
        if (rb.Values[k])
            rb.owned_cap_flags |= flag;
    }

    // Re-root: reverse the parent chain from the new root, moving the joint vectors along.
    if ((uint32)root != target) {
        vector_3 carriedLocal = rb.parent_local_joint_r;
        vector_3 carriedParent = rb.local_joint_r;
        int prev = -1;
        for (int idx = root; idx != -1;) {
            creature_body_static_data& b = c->Bodies[idx];
            int next = b.parent_bidx;
            b.parent_bidx = prev;
            vector_3 oldLocal = b.local_joint_r;
            vector_3 oldParent = b.parent_local_joint_r;
            b.local_joint_r = carriedLocal;
            b.parent_local_joint_r = carriedParent;
            if (b.cap_flags & kCapSpine) {
                b.joint_r.x = b.local_joint_r.x - b.rest_joint_offset.x;
                b.joint_r.y = b.local_joint_r.y - b.rest_joint_offset.y;
                b.joint_r.z = b.local_joint_r.z - b.rest_joint_offset.z;
            } else {
                b.joint_r = b.local_joint_r;
            }
            b.joint_r_len = (float)sqrt(((double)b.joint_r.x * b.joint_r.x +
                                         (double)b.joint_r.y * b.joint_r.y) +
                                        (double)b.joint_r.z * b.joint_r.z);
            carriedLocal = oldParent;
            carriedParent = oldLocal;
            prev = idx;
            idx = next;
        }
        c->Bodies[target].num_children--;
        rb.num_children++;
        target = root;
    }
    rb.parent_local_joint_r.x = 0.0f;
    rb.parent_local_joint_r.y = 0.0f;
    rb.parent_local_joint_r.z = 0.0f;
    rb.local_joint_r.x = 0.0f;
    rb.local_joint_r.y = 0.0f;
    rb.local_joint_r.z = 0.0f;
    rb.joint_r.x = 0.0f;
    rb.joint_r.y = 0.0f;
    rb.joint_r.z = 0.0f;
    rb.joint_r_len = 0.0f;

    // Hierarchy order: order[0] = root; footCounts is reused as the child-slot table.
    index_vector order;
    order.resize(c->Bodies.size());
    order.resize(1);
    order[0] = target;
    index_vector& children = footCounts;
    children.resize(c->Bodies.size());

    {
        unsigned n = c->Bodies.size();
        int nextSlot = 1;
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data& b = c->Bodies[i];
            b.first_child_bidx = nextSlot;
            nextSlot += b.num_children;
            b.num_children = 0;
        }
    }
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            int p = c->Bodies[i].parent_bidx;
            if (p == -1)
                continue;
            creature_body_static_data& parent = c->Bodies[p];
            uint32 slot = parent.num_children + parent.first_child_bidx;
            children[slot] = i;
            uint32 numChildren = parent.num_children;
            if (numChildren && (c->Bodies[i].cap_flags & kCapSpine)) {
                // Keep a spine child first (for the root, second if a spine is already first).
                if (parent.parent_bidx == -1) {
                    uint32& first = children[parent.first_child_bidx];
                    if (!(c->Bodies[first].cap_flags & kCapSpine))
                        eastl::swap(children[slot], first);
                    else if (numChildren > 1)
                        eastl::swap((&first)[1], children[slot]);
                } else {
                    eastl::swap(children[slot], children[parent.first_child_bidx]);
                }
            }
            parent.num_children++;
        }
    }

    BuildHierarchyOrder(c, &order, &children, target);

    // Copy the bodies into hierarchy order, remapping indices and rebuilding relative rotations.
    body_vector sorted(c->Bodies.size(), eastl::sp_vector_allocator());
    {
        unsigned n = c->Bodies.size();
        bool startRemapped = false;
        bool endRemapped = false;
        for (unsigned k = 0; k < n; ++k) {
            uint32 src = order[k];
            creature_body_static_data& old = c->Bodies[src];
            creature_body_static_data& nb = sorted[k];
            nb.CopyFrom(old);
            nb.bidx = k;
            old.parent_bidx = k;   // old index -> new index, used for the remaps below
            if (nb.parent_bidx != -1) {
                nb.parent_bidx = c->Bodies[nb.parent_bidx].parent_bidx;
                const vector_4& pq = sorted[nb.parent_bidx].rest_orientation_q;
                const vector_4& q = nb.rest_orientation_q;
                vector_4& r = nb.rest_parent_rel_orientation_q;
                r.x = ((q.x * pq.w - q.w * pq.x) + q.y * pq.z) - q.z * pq.y;
                r.y = ((q.y * pq.w - q.w * pq.y) - q.x * pq.z) + q.z * pq.x;
                r.z = ((q.x * pq.y - q.w * pq.z) - q.y * pq.x) + q.z * pq.w;
                r.w = ((q.y * pq.y + q.x * pq.x) + q.w * pq.w) + q.z * pq.z;
            }
            if (!startRemapped && c->spine_start_bidx == src) {
                c->spine_start_bidx = k;
                startRemapped = true;
            }
            if (!endRemapped && c->spine_end_bidx == src) {
                c->spine_end_bidx = k;
                endRemapped = true;
            }
        }
    }
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data& nb = sorted[i];
            if ((uint32)nb.symmetric_bidx < n)
                nb.symmetric_bidx = c->Bodies[nb.symmetric_bidx].parent_bidx;
        }
    }
    c->Bodies.swap(sorted);

    if (!c->mIsLegless) {
        AddExtraBonesAsNecessary(c, c->spine_start_bidx);
        AddExtraBonesAsNecessary(c, c->spine_end_bidx);
    }

    // Parent / first-child pointers.
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data& b = c->Bodies[i];
            b.parent = i ? &c->Bodies[b.parent_bidx] : 0;
            b.first_child = b.num_children ? &c->Bodies[b.first_child_bidx] : 0;
            b.in_leg_chain = false;
        }
    }
    // Workspace radius: parent's radius plus the padded distance to the parent.
    {
        unsigned n = c->Bodies.size();
        for (unsigned i = 0; i < n; ++i) {
            creature_body_static_data& b = c->Bodies[i];
            if (i == 0) {
                b.workspace_radius = 3.0f;
                continue;
            }
            float base = (b.parent_bidx == 0) ? 0.0f : b.parent->workspace_radius;
            const vector_3& pc = b.parent->rest_center;
            double dx = (double)pc.x - b.rest_center.x;
            float dy = pc.y - b.rest_center.y;
            float dz = pc.z - b.rest_center.z;
            double len = sqrt(((double)dy * dy + (double)dz * dz) + dx * dx);
            b.workspace_radius =
                (float)(((g_WorkspaceRadiusPad + 1.0) * len) * g_WorkspaceRadiusScale + base);
        }
    }
    // Leg chains: a body with a foot below it (or a foot itself) marks its parent.
    for (int i = (int)c->Bodies.size() - 1; i >= 0; --i) {
        creature_body_static_data& b = c->Bodies[i];
        if (b.in_leg_chain || (b.cap_flags & kCapFoot)) {
            b.in_leg_chain = true;
            if (b.parent)
                b.parent->in_leg_chain = true;
        } else {
            b.in_leg_chain = false;
        }
    }

    ComputeBodyStatics(c);
    return true;
}

}  // namespace nSPCreatureAnim
