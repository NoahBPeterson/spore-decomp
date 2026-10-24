// Slice s009bd340 -- nSPCreatureAnim: keep bodies above the ground plane (0x009bd6f0, 2641 bytes).
//
// FloorBodies(creature_instance_data* c)   (cdecl; name Claude-coined)
//
// When the creature's floor pass is enabled, the creature's ground plane (ground_normal and
// ground_pos, world space) is brought into creature space. Then for every body whose static
// floor height is not negative (and, when the creature's static data says so, that is not
// flagged with caps bits 3/4), the body's plane is either its own stored ground plane
// (known_ground_pos) or the creature's (raised by floor_height * scale for caps bit 2).
// A body whose center lies below its plane gets floored_weight = min((plane - depth) * rate, 1)
// and is pushed back:
//   * a body with a parent, no children and neither caps bit 2 nor 5 is moved so that its
//     joint to the parent stays on the parent's joint while its center reaches the plane
//     (ray / sphere intersection), and its orientation is turned by the shortest arc between
//     the old and new joint vectors;
//   * any other body is tilted towards the plane normal (shortest arc from its local up axis,
//     scaled by the weight, nlerped with the identity) and then translated onto the plane.
//
// Layouts: retail offsets from the disassembly. ground_pos / ground_normal / floored_weight /
// known_ground_pos / center / orientation are dev-PDB names at retail offsets; floor_height,
// floored, floor_check_caps and floor_enabled are Claude-coined.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <intrin.h>

namespace checkerlib {
class vector_3 { public:
    float x, y, z;
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
class vector_4 { public:
    float x, y, z, w;
    vector_4& operator=(const vector_4& o);   // 0x00572600 (EA::RectT<float>::operator= by COMDAT folding)
};

vector_3* QuaternionVectorTransform(vector_3* out, const vector_4* q, const vector_3* v);         // 0x0099c1a0
vector_3* QuaternionVectorTransformInverse(vector_3* out, const vector_4* q, const vector_3* v);  // 0x0099c310
vector_4* QuaternionProduct(vector_4* out, const vector_4* a, const vector_4* b);                // 0x0099c0b0
vector_4 Normalize(const vector_4& q, float* pLength);                                            // 0x0099cae0
}  // namespace checkerlib

using namespace checkerlib;

vector_4* QuaternionFromTwoVectors(vector_4* out, const vector_3* a, const vector_3* b, int flag);  // 0x009ac7a0

extern float g_IKFloorWeightRate;   // 0x01550d88 (20.0)

namespace eastl {
template <typename T>
inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }

struct sp_vector_allocator { int mFlags; };

template <typename T, typename Allocator = sp_vector_allocator>
class vector {
public:
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T& operator[](size_type n) { return *(mpBegin + n); }
};
}  // namespace eastl

namespace nSPCreatureAnim {

struct creature_static_data {
    uint32_t pad_000[0x3f4 / 4];
    bool     floor_check_caps;                  // +0x3f4
};

struct creature_body_static_data {
    uint32_t      pad_000[0x114 / 4];
    float         floor_height;                 // +0x114
    uint32_t      pad_118[(0x150 - 0x118) / 4];
    unsigned long caps_flags;                   // +0x150

    bool HasCap(unsigned int bit) const { return ((caps_flags >> bit) & 1) != 0; }
    uint8_t       field_154;                    // +0x154
    uint8_t       pad_155[3];
    uint32_t      pad_158[(0x344 - 0x158) / 4];
    vector_3      ik_joint_r__SCALABLE;         // +0x344 (name guessed)
    vector_3      parent_local_joint_r__SCALABLE;  // +0x350 (name guessed)
};

struct creature_deform {                        // 0x14 bytes
    int32_t key;                                // +0x00
    int32_t flags;                              // +0x04
    float   value8;                             // +0x08
    int32_t field_0c;                           // +0x0c
    float   value10;                            // +0x10
};

struct creature_body_instance_data {            // size 0x2bc (retail)
    creature_body_static_data*   static_data;   // +0x000
    void*                        creature;      // +0x004
    creature_body_instance_data* parent;        // +0x008
    creature_body_instance_data* first_child;   // +0x00c
    vector_3                     center;        // +0x010
    vector_4                     orientation;   // +0x01c
    vector_3                     velocity;      // +0x02c
    bool                         floored;       // +0x038
    uint8_t                      pad_039[3];
    vector_3                     blended_center; // +0x03c
    int32_t                      field_048;     // +0x048
    int32_t                      field_04c;     // +0x04c
    int32_t                      field_050;     // +0x050
    uint8_t                      field_054;     // +0x054
    uint8_t                      field_055;     // +0x055
    uint8_t                      pad_056[2];
    float                        reset_floats[18]; // +0x058..+0x09f
    uint32_t                     field_0a0;     // +0x0a0
    creature_deform              deforms[11];  // +0x0a4..+0x17f
    uint32_t                     pad_180[4];   // +0x180..+0x18f
    vector_3                     saved_center; // +0x190
    vector_4                     saved_orientation; // +0x19c
    uint32_t                     pad_1ac[(0x29c - 0x1ac) / 4];
    float                        floored_weight;     // +0x29c
    bool                         known_ground_pos;   // +0x2a0
    uint8_t                      pad_2a1[3];
    vector_3                     ground_pos;         // +0x2a4
    vector_3                     ground_normal;      // +0x2b0
};

struct creature_instance_data {
    creature_static_data* static_data;          // +0x000
    uint32_t pad_004[3];                        // +0x004
    int32_t  reset_counter;                     // +0x010
    uint32_t pad_014;                           // +0x014
    vector_3 position;                          // +0x018
    uint32_t pad_024[(0x3c - 0x24) / 4];
    vector_4 orientation;                       // +0x03c
    uint32_t pad_04c[(0x70 - 0x4c) / 4];
    float    requested_scale;                   // +0x070
    uint32_t pad_074[(0xe8 - 0x74) / 4];
    vector_3 ground_pos;                        // +0x0e8
    vector_3 ground_normal;                     // +0x0f4
    uint32_t pad_100[4];                        // +0x100
    float    reset_110;                         // +0x110
    float    reset_114;                         // +0x114
    uint32_t pad_118[(0x13c - 0x118) / 4];
    float    reset_floats[27];                  // +0x13c..+0x1a7
    uint8_t  reset_1a8;                         // +0x1a8
    uint8_t  reset_1a9;                         // +0x1a9
    uint8_t  pad_1aa[0x1b8 - 0x1aa];
    uint8_t  reset_mask;                        // +0x1b8
    uint8_t  pad_1b9[0x262 - 0x1b9];
    uint8_t  reset_262;                         // +0x262
    uint8_t  pad_263[0x2e4 - 0x263];
    eastl::vector<creature_body_instance_data, eastl::sp_vector_allocator> Bodies;  // +0x2e4
    uint32_t pad_2f4[(0x168c - 0x2f4) / 4];
    uint8_t  pad_168c;
    bool     floor_enabled;                     // +0x168d
};

// @ 0x009bd6f0
void FloorBodies(creature_instance_data* c)
{
    if (!c->floor_enabled)
        return;

    // creature ground plane in creature space
    vector_3 normal;
    QuaternionVectorTransformInverse(&normal, &c->orientation, &c->ground_normal);
    vector_3 rel;
    rel.x = c->ground_pos.x - c->position.x;
    rel.y = c->ground_pos.y - c->position.y;
    rel.z = c->ground_pos.z - c->position.z;
    vector_3 lground;
    QuaternionVectorTransformInverse(&lground, &c->orientation, &rel);

    const float scale = c->requested_scale;
    const unsigned int count = c->Bodies.size();
    const float planeDist = (lground.z * normal.z + normal.y * lground.y) + normal.x * lground.x;

    for (unsigned int i = 0; i < count; ++i) {
        creature_body_instance_data& b = c->Bodies[i];
        creature_body_static_data* sd = b.static_data;
        b.floored_weight = 0.0f;
        if (sd->floor_height < 0.0f)
            continue;

        const bool raised = sd->HasCap(2);
        if (c->static_data->floor_check_caps) {
            if (sd->HasCap(4))
                continue;
            if (sd->HasCap(3))
                continue;
        }

        vector_3 dir;
        float plane;
        if (b.known_ground_pos) {
            dir = b.ground_normal;
            plane = (b.ground_pos.z * dir.z + b.ground_pos.y * dir.y) + b.ground_pos.x * dir.x;
        } else {
            dir = normal;
            plane = planeDist;
            if (raised)
                plane = sd->floor_height * scale + planeDist;
        }

        float depth = (b.center.z * dir.z + b.center.y * dir.y) + b.center.x * dir.x;
        if (!(plane > depth))
            continue;

        float one = 1.0f;
        float w = (plane - depth) * g_IKFloorWeightRate;
        const float weight = eastl::min(w, one);
        b.floored_weight = weight;

        creature_body_instance_data* parent = b.parent;
        if (parent != 0 && b.first_child == 0 && !raised && !sd->HasCap(5)) {
            // keep the joint on the parent's joint, put the center on the plane
            vector_3 v, r;
            v.x = sd->parent_local_joint_r__SCALABLE.x * scale;
            v.y = sd->parent_local_joint_r__SCALABLE.y * scale;
            v.z = sd->parent_local_joint_r__SCALABLE.z * scale;
            const vector_3* pr = QuaternionVectorTransform(&r, &parent->orientation, &v);
            vector_3 joint;
            joint.x = pr->x + parent->center.x;
            joint.y = pr->y + parent->center.y;
            joint.z = pr->z + parent->center.z;

            if (parent->floored_weight > 0.0f) {
                vector_3 v2, r2;
                v2.x = sd->ik_joint_r__SCALABLE.x * scale;
                v2.y = sd->ik_joint_r__SCALABLE.y * scale;
                v2.z = sd->ik_joint_r__SCALABLE.z * scale;
                const vector_3* pr2 = QuaternionVectorTransform(&r2, &b.orientation, &v2);
                const float inv = 1.0f - weight;
                joint.x = (b.center.x + pr2->x) * inv + joint.x * weight;
                joint.y = (b.center.y + pr2->y) * inv + joint.y * weight;
                joint.z = (b.center.z + pr2->z) * inv + joint.z * weight;
            }

            vector_3 v3, r3;
            v3.x = sd->ik_joint_r__SCALABLE.x * scale;
            v3.y = sd->ik_joint_r__SCALABLE.y * scale;
            v3.z = sd->ik_joint_r__SCALABLE.z * scale;
            const vector_3* pr3 = QuaternionVectorTransform(&r3, &b.orientation, &v3);
            vector_3 arm;   // joint -> center
            arm.x = -pr3->x;
            arm.y = -pr3->y;
            arm.z = -pr3->z;
            const float armLen2 = (arm.y * arm.y + arm.z * arm.z) + arm.x * arm.x;
            if (armLen2 > 0.0f) {
                const float k = ((arm.z + joint.z) * dir.z + (arm.y + joint.y) * dir.y) + (arm.x + joint.x) * dir.x;
                vector_3 proj;
                proj.x = dir.x * k;
                proj.y = dir.y * k;
                proj.z = dir.z * k;
                vector_3 a;
                a.x = (dir.x * plane + arm.x) - proj.x;
                float ay = dir.y * plane + arm.y;
                a.y = ay - proj.y;
                a.z = (dir.z * plane + arm.z) - proj.z;
                const float m = (arm.z * dir.z + arm.y * dir.y) + arm.x * dir.x;
                vector_3 bv;
                bv.x = arm.x - dir.x * m;
                bv.y = arm.y - dir.y * m;
                bv.z = arm.z - dir.z * m;
                const float bb = (bv.x * bv.x + bv.y * bv.y) + bv.z * bv.z;
                const float ab = (bv.z * a.z + bv.y * a.y) + bv.x * a.x;
                const float aa = (a.y * a.y + a.z * a.z) + a.x * a.x;
                const float disc = ab * ab - (aa - armLen2) * bb;
                float root;
                if (disc > 0.0f)
                    root = sqrtf(disc);
                else
                    root = 0.0f;
                const float t = (float)(((double)root - ab) / (bb + 1e-08));
                vector_3 newArm;
                newArm.x = bv.x * t + a.x;
                newArm.y = bv.y * t + a.y;
                newArm.z = bv.z * t + a.z;
                b.center.x = newArm.x + joint.x;
                b.center.y = newArm.y + joint.y;
                b.center.z = newArm.z + joint.z;
                vector_4 q, qr;
                b.orientation = *QuaternionProduct(&qr, QuaternionFromTwoVectors(&q, &arm, &newArm, 0),
                                                   &b.orientation);
            }
        } else {
            // tilt the body's up axis towards the plane normal, then put it on the plane
            const vector_4& o = b.orientation;
            vector_3 up;
            up.x = (o.x * o.z + o.y * o.w) * 2.0f;
            up.y = (o.z * o.y - o.x * o.w) * 2.0f;
            up.z = 1.0f - (o.x * o.x + o.y * o.y) * 2.0f;
            if ((up.x * dir.x + up.z * dir.z) + up.y * dir.y < 0.0f) {
                up.x = -up.x;
                up.y = -up.y;
                up.z = -up.z;
            }
            vector_4 arc;
            const vector_4* pa = QuaternionFromTwoVectors(&arc, &up, &dir, 0);
            vector_4 s;
            s.x = pa->x * weight;
            s.y = pa->y * weight;
            s.z = pa->z * weight;
            const float sw = pa->w * weight;
            s.w = (sw < 0.0f ? weight - 1.0f : 1.0f - weight) + sw;
            const vector_4 r = Normalize(s, 0);

            const float qx = b.orientation.x, qy = b.orientation.y;
            const float qz = b.orientation.z, qw = b.orientation.w;
            const float nx = ((qx * r.w + r.x * qw) - qy * r.z) + qz * r.y;
            const float ny = ((r.z * qx + qy * r.w) + r.y * qw) - qz * r.x;
            const float nz = ((r.z * qw - r.y * qx) + qz * r.w) + qy * r.x;
            const float nw = ((r.w * qw - qx * r.x) - r.y * qy) - qz * r.z;
            b.orientation.w = nw;
            b.orientation.x = nx;
            b.orientation.y = ny;
            b.orientation.z = nz;

            const float d = depth - plane;
            b.center.x = b.center.x - dir.x * d;
            b.center.y = b.center.y - dir.y * d;
            b.center.z = b.center.z - dir.z * d;
        }
        b.floored = true;
    }
}

}  // namespace nSPCreatureAnim

extern "C" void* memset(void* dst, int value, unsigned int size);

namespace nSPCreatureAnim {

// @ 0x009bd340
void ResetBodies(creature_instance_data* c)
{
    int count = (int)(c->Bodies.mpEnd - c->Bodies.mpBegin);
    if (count != 0) {
        int offset = 0;
        int remaining = count;
        do {
            creature_body_instance_data* b =
                (creature_body_instance_data*)((char*)c->Bodies.mpBegin + offset);
            b->reset_floats[0] = 0.0f;
            b->reset_floats[1] = 0.0f;
            b->reset_floats[2] = 0.0f;
            b->reset_floats[3] = 0.0f;
            b->reset_floats[4] = 0.0f;
            b->reset_floats[5] = 0.0f;
            b->reset_floats[6] = 0.0f;
            b->reset_floats[7] = 0.0f;
            b->reset_floats[8] = 0.0f;
            b->reset_floats[9] = 0.0f;
            b->reset_floats[10] = 0.0f;
            b->reset_floats[11] = 0.0f;
            b->reset_floats[12] = 0.0f;
            b->reset_floats[13] = 0.0f;
            b->reset_floats[14] = 0.0f;
            b->reset_floats[15] = 0.0f;
            b->reset_floats[16] = 0.0f;
            b->reset_floats[17] = 0.0f;
            b->field_0a0 = 0;
            b->field_048 = 0;
            b->field_04c = 0;
            b->field_050 = 0;
            _ReadWriteBarrier();
            offset += (int)sizeof(creature_body_instance_data);
            remaining--;
            b->field_054 = 0;
            b->field_055 = 0;
            b->known_ground_pos = 0;
            b->floored = 0;
        } while (remaining != 0);
    }

    c->reset_114 = 0.0f;
    c->reset_110 = 0.0f;
    c->reset_floats[0] = 0.0f;
    c->reset_floats[1] = 0.0f;
    c->reset_floats[2] = 0.0f;
    c->reset_floats[3] = 0.0f;
    c->reset_floats[4] = 0.0f;
    c->reset_floats[5] = 0.0f;
    c->reset_floats[6] = 0.0f;
    c->reset_floats[7] = 0.0f;
    c->reset_floats[8] = 0.0f;
    c->reset_floats[9] = 0.0f;
    c->reset_floats[10] = 0.0f;
    c->reset_floats[11] = 0.0f;
    c->reset_floats[12] = 0.0f;
    c->reset_floats[13] = 0.0f;
    c->reset_floats[14] = 0.0f;
    c->reset_floats[15] = 0.0f;
    c->reset_floats[16] = 0.0f;
    c->reset_floats[17] = 0.0f;
    c->reset_floats[18] = 0.0f;
    c->reset_floats[19] = 0.0f;
    c->reset_floats[20] = 0.0f;
    c->reset_floats[21] = 0.0f;
    c->reset_floats[22] = 0.0f;
    c->reset_floats[23] = 0.0f;
    c->reset_floats[24] = 0.0f;
    c->reset_floats[25] = 0.0f;
    const unsigned int maskSize = ((unsigned int)(count * 2 + 7)) >> 3;
    _ReadWriteBarrier();
    c->reset_floats[26] = 0.0f;
    _ReadWriteBarrier();
    memset((c->reset_1a8 = 0, c->reset_1a9 = 0, c->reset_262 = 1, &c->reset_mask),
           0, maskSize);
    c->reset_counter++;
}

}  // namespace nSPCreatureAnim

namespace nSPCreatureAnim {

// @ 0x009bd550
void BlendBodyPoses(float dt, float blend, creature_instance_data* c, bool keep_pose)
{
    int count = (int)(c->Bodies.mpEnd - c->Bodies.mpBegin);
    if (count == 0)
        return;

    float invBlend = 1.0f - blend;
    int offset = 0;
    int remaining = count;
    do {
        creature_body_instance_data* b =
            (creature_body_instance_data*)((char*)c->Bodies.mpBegin + offset);

        if (!keep_pose) {
            vector_3 velocity;
            if (dt <= 1e-06f) {
                velocity.x = 0.0f;
                velocity.y = 0.0f;
                velocity.z = 0.0f;
            } else {
                float invDt = 1.0f / dt;
                velocity.x = (b->saved_center.x - b->center.x) * invDt;
                velocity.y = (b->saved_center.y - b->center.y) * invDt;
                velocity.z = (b->saved_center.z - b->center.z) * invDt;
            }
            b->velocity = velocity;
            b->center = b->saved_center;
            b->orientation.x = b->saved_orientation.x;
            b->orientation.y = b->saved_orientation.y;
            b->orientation.z = b->saved_orientation.z;
            b->orientation.w = b->saved_orientation.w;
            b->floored = 1;
        }

        b->blended_center.x = b->center.x * invBlend + b->blended_center.x * blend;
        b->blended_center.y = b->center.y * invBlend + b->blended_center.y * blend;
        b->blended_center.z = b->center.z * invBlend + b->blended_center.z * blend;

        offset += (int)sizeof(creature_body_instance_data);
        remaining--;
    } while (remaining != 0);
}

// @ 0x009be150
void UpdateDeforms(creature_instance_data* c)
{
    int count = (int)(c->Bodies.mpEnd - c->Bodies.mpBegin);
    if (count == 0)
        return;

    int offset = 0;
    int remaining = count;
    do {
        creature_body_instance_data* b =
            (creature_body_instance_data*)((char*)c->Bodies.mpBegin + offset);

        if ((b->static_data->field_154 & 0x20) != 0) {
            uint32_t n = b->field_0a0;
            uint32_t first = 0;
            if (n != 0) {
                creature_deform* p = &b->deforms[0];
                do {
                    if (p->key == 0x4d5bf589)
                        goto found_first;
                    first++;
                    p++;
                } while (first < n);
            }
            first = 0xffffffffu;
        found_first:
            if (first < n) {
                creature_deform* src = &b->deforms[first];
                uint32_t second = 0;
                if (n != 0) {
                    creature_deform* p = &b->deforms[0];
                    do {
                        if (p->key == 0x89e06a31)
                            goto found_second;
                        second++;
                        p++;
                    } while (second < n);
                }
                second = 0xffffffffu;
            found_second:
                if (second < n) {
                    creature_deform* dst = &b->deforms[second];
                    dst->value8 = src->value8 + dst->value8;
                    dst->value10 = src->value10 + dst->value10;
                } else {
                    src->flags &= ~1;
                    src->key = 0x89e06a31;
                }
            }
        }

        offset += (int)sizeof(creature_body_instance_data);
        remaining--;
    } while (remaining != 0);
}

}  // namespace nSPCreatureAnim
