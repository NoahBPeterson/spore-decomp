// slice s009c1f60 -- nSPCreatureAnim creature_static_data lifecycle and wiggle construction.
//
//   @ 0x009c1f60  creature_static_data::creature_static_data()
//   @ 0x009c2050  creature_static_data::~creature_static_data()
//   @ 0x009c20e0  creature_instance_data::BuildBodyList()
//   @ 0x009c2300  creature_static_data::FilterAndAddWiggle(wiggle*, keep, sym)
//   @ 0x009c2520  resize_bone_xforms()
//   @ 0x009c25f0  resize_wiggle_instances()
//   @ 0x009c26a0  creature_static_data::Release()
//   @ 0x009c26f0  creature_static_data::InitWiggles()
//   @ 0x009c2c20  creature_instance_data::InitWiggles()
//
// Layouts are the retail ones read from the disassembly (the dev PDB predates this build);
// creature_static_data runs to at least 0x408, creature_instance_data to 0x1770.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

namespace checkerlib {
struct vector_3 { float x, y, z; };
struct vector_4 { float x, y, z, w; };
struct matrix_3x3 { float m[3][3]; };
}
using checkerlib::vector_3;
using checkerlib::vector_4;
using checkerlib::matrix_3x3;

void operator delete[](void* p);   // 0x00f47380

namespace nSPCreatureAnim {

// ------------------------------------------------------------------ types

struct creature_body_static_data;
struct creature_body_instance_data;

struct wiggle_static_data {              // body wiggle descriptor, size 0x3c
    int   body;                          // +0x00
    int   cap_a;                         // +0x04
    int   cap_b;                         // +0x08
    int   channel;                       // +0x0c
    float vx, vy, vz;                    // +0x10
    int   pad_1c[7];                     // +0x1c .. 0x38
    uint8 flag;                          // +0x38
    uint8 pad_39[3];
};

struct unk_pair {                        // element of the 0x3cc vector, stride 8
    creature_body_static_data* body;     // +0x00
    uint32 pad;
};

template <typename T>
struct vec3p {
    T*     mpBegin;
    T*     mpEnd;
    T*     mpCapacity;
    uint32 mAllocator;
};

struct bone_xform {                      // pair<matrix_3x3, vector_3>, size 0x30
    matrix_3x3 first;
    vector_3   second;
};

struct bone_xform_vec : vec3p<bone_xform> {
    void resize(unsigned n);             // 0x009c2520
};

struct body_entry {                      // element of the built body list, size 0x30
    void*                        static_pair;   // +0x00
    creature_body_instance_data* body;          // +0x04
    float                        m[6];          // +0x08
    float                        w0;             // +0x20
    float                        w1;             // +0x24
    float                        w2;             // +0x28
    float                        w3;             // +0x2c
};

struct body_entry_list {
    body_entry* mpBegin;
    body_entry* mpEnd;
    body_entry* mpCapacity;
    void* Resize(int n);                                       // 0x009c0b00
    void  Append(body_entry* at, const body_entry& v);         // 0x009c0f60
};

struct cBuilding {
    body_entry_list* func8Ch();          // 0x00ad2800
};

struct creature_body_static_data {       // retail size 0x468
    uint8      pad_000[0x10c];
    vector_3   rest_center;              // +0x10c
    vector_4   rest_orientation_q;       // +0x118
    uint8      pad_128[0x18];            // +0x128 .. 0x140
    float      unk_140;                  // +0x140
    uint8      pad_144[0xc];             // +0x144 .. 0x150
    uint32     cap_flags;                // +0x150
    uint8      pad_154[0xa4];            // +0x154 .. 0x1f8
    uint32     bidx;                     // +0x1f8
    int        parent_bidx;              // +0x1fc
};

struct creature_body_instance_data {     // retail size 0x2bc
    creature_body_static_data* static_data;   // +0x00
    uint8      pad_004[0x2bc - 4];
};

struct creature_static_data {            // retail size >= 0x408
    uint8          pad_000[0x324];
    vector_3       skin_colors[3];       // +0x324
    int            RefCount;             // +0x348
    uint8          pad_34c[0xc];         // +0x34c .. 0x358
    vector_3       local_aabb_origin;    // +0x358
    vector_3       local_aabb_extent;    // +0x364
    uint8          pad_370[0x14];        // +0x370 .. 0x384
    vec3p<creature_body_static_data> Bodies;      // +0x384
    uint8          pad_394[4];           // +0x394 .. 0x398
    vec3p<creature_body_static_data> mUnk398;     // +0x398
    uint8          pad_3a8[4];           // +0x3a8 .. 0x3ac
    uint32         spine_start_bidx;     // +0x3ac
    uint32         spine_end_bidx;       // +0x3b0
    vec3p<wiggle_static_data> mWiggles;  // +0x3b4
    uint8          pad_3c4[8];           // +0x3c4 .. 0x3cc
    vec3p<unk_pair> mUnk3cc;             // +0x3cc
    uint8          pad_3dc[0x18];        // +0x3dc .. 0x3f4
    bool           mIsLegless;           // +0x3f4
    bool           mIgnoreGait;          // +0x3f5
    uint8          pad_3f6[2];           // +0x3f6 .. 0x3f8
    vec3p<bone_xform> inv_bone_rest_xforms;       // +0x3f8

    creature_static_data();
    ~creature_static_data();
    int  Release();
    bool FilterAndAddWiggle(wiggle_static_data* w, bool keep, bool sym);
    void InitWiggles();
    void Clear(int flag);                // 0x009c1dc0
};

struct wiggle_instance_data {            // element of instance mWiggles, size 0x2c
    wiggle_static_data* wiggle;          // +0x00
    uint8   pad_004;
    uint8   flag4;                       // +0x04
    uint8   flag5;                       // +0x05
    uint8   pad_006[2];
    vector_3 zero;                       // +0x08
    vector_3 pos;                        // +0x14
    vector_3 pos_copy;                   // +0x20
};

struct wiggle_instance_vec : vec3p<wiggle_instance_data> {
    void resize(unsigned n);             // 0x009c25f0
};

struct creature_instance_data {
    creature_static_data* static_data;   // +0x000
    uint8      pad_004[0x18 - 0x4];
    vector_3   position;                 // +0x018
    uint8      pad_024[0x3c - 0x24];
    vector_4   orientation;              // +0x03c
    uint8      pad_04c[0x70 - 0x4c];
    float      requested_scale;          // +0x070
    uint8      pad_074[0x2e4 - 0x74];
    vec3p<creature_body_instance_data> Bodies;    // +0x2e4
    uint8      pad_2f4[0x15b8 - 0x2f4];
    cBuilding  building;                 // +0x15b8 (size 1)
    uint8      pad_15b9[0x1640 - 0x15b9];
    int        last_joint_index;         // +0x1640
    uint8      pad_1644[0x168e - 0x1644];
    uint8      flag_168e;                // +0x168e
    uint8      pad_168f;
    float      f_1690;                   // +0x1690
    wiggle_instance_vec mWiggles;        // +0x1694
    uint8      pad_16a4[0x16a8 - 0x16a4];
    float      f_16a8;                   // +0x16a8
    uint8      pad_16ac[0x16c4 - 0x16ac];
    wiggle_static_data desc_a;           // +0x16c4
    uint8      pad_1700[0x172c - 0x1700];
    wiggle_static_data desc_b;           // +0x172c
    uint8      pad_1768[8];

    void BuildBodyList();
    void InitWiggles();
};

// ------------------------------------------------------------------ helpers

bool CreateWiggle(creature_static_data* c, int index, wiggle_static_data* desc,
                  int a, int b, int c2, int d, int e, int f);           // 0x009ba4c0
void AddWiggle(creature_static_data* c, wiggle_static_data* w);         // 0x009ba590
bool FUN_009b3150(const void* a, const void* b);                        // 0x009b3150
void FUN_009b43f0(void* p0, void* p1, void* p2);                        // 0x009b43f0
void FUN_009b4550(void* p0, void* p1, void* p2);                        // 0x009b4550
void FUN_009b4a20(void* p0, void* p1, void* p2);                        // 0x009b4a20
void FUN_009c10c0(void* at, const wiggle_static_data* v);               // 0x009c10c0
void DoInsertValues30(void* end, unsigned n, const void* value);        // 0x009c11e0
void DoInsertValues2c(void* end, unsigned n, const void* value);        // 0x009c13a0
int  FUN_009d7d10(creature_instance_data* c, float* pos, float* rot);   // 0x009d7d10
void* FUN_00a09f50();                                                   // 0x00a09f50

extern int   g_gait_channel;               // 0x0166c130
extern uint8 g_wiggle_symmetry;            // 0x01550c2d

static inline float wiggle_abs(float v) { return v < 0.0f ? -v : v; }

// ------------------------------------------------------------------ @ 0x009c1f60

// @ 0x009c1f60
creature_static_data::creature_static_data()
{
    Bodies.mpBegin = 0;
    Bodies.mpEnd = 0;
    Bodies.mpCapacity = 0;
    mUnk398.mpBegin = 0;
    mUnk398.mpEnd = 0;
    mUnk398.mpCapacity = 0;
    skin_colors[0].x = skin_colors[0].y = skin_colors[0].z = 0.0f;
    skin_colors[1].x = skin_colors[1].y = skin_colors[1].z = 0.0f;
    skin_colors[2].x = skin_colors[2].y = skin_colors[2].z = 0.0f;
    mWiggles.mpBegin = 0;
    mWiggles.mpEnd = 0;
    mWiggles.mpCapacity = 0;
    local_aabb_origin.x = local_aabb_origin.y = local_aabb_origin.z = 0.0f;
    mUnk3cc.mpBegin = 0;
    mUnk3cc.mpEnd = 0;
    mUnk3cc.mpCapacity = 0;
    local_aabb_extent.x = local_aabb_extent.y = local_aabb_extent.z = 0.0f;
    inv_bone_rest_xforms.mpBegin = 0;
    inv_bone_rest_xforms.mpEnd = 0;
    inv_bone_rest_xforms.mpCapacity = 0;
    RefCount = 0;
    Clear(1);
}

// @ 0x009c2050
creature_static_data::~creature_static_data()
{
    Clear(0);
    if (inv_bone_rest_xforms.mpBegin && ((int*)inv_bone_rest_xforms.mpBegin)[-1] != 0)
        operator delete[](inv_bone_rest_xforms.mpBegin);
    if (mUnk3cc.mpBegin && ((int*)mUnk3cc.mpBegin)[-1] != 0)
        operator delete[](mUnk3cc.mpBegin);
    if (mWiggles.mpBegin && ((int*)mWiggles.mpBegin)[-1] != 0)
        operator delete[](mWiggles.mpBegin);
    if (mUnk398.mpBegin && ((int*)mUnk398.mpBegin)[-1] != 0)
        operator delete[](mUnk398.mpBegin);
    if (Bodies.mpBegin && ((int*)Bodies.mpBegin)[-1] != 0)
        operator delete[](Bodies.mpBegin);
}

// ------------------------------------------------------------------ @ 0x009c20e0

// @ 0x009c20e0
void creature_instance_data::BuildBodyList()
{
    body_entry_list* list = building.func8Ch();
    unsigned count = (unsigned)(static_data->mUnk3cc.mpEnd - static_data->mUnk3cc.mpBegin);
    list->Resize((int)count);
    if (count == 0)
        return;

    unsigned k = 0;
    do {
        creature_body_static_data* sd0 = static_data->mUnk3cc.mpBegin[k].body;
        uint32 bidx = sd0->bidx;
        creature_body_instance_data* body = &Bodies.mpBegin[bidx];

        body_entry tmp;
        tmp.static_pair = &static_data->mUnk3cc.mpBegin[k];
        tmp.body = body;
        tmp.m[0] = tmp.m[1] = tmp.m[2] = tmp.m[3] = tmp.m[4] = tmp.m[5] = 0.0f;
        tmp.w0 = 1.0f;
        tmp.w1 = 0.0f;
        tmp.w2 = 0.0f;
        tmp.w3 = 1.0f;

        if (list->mpEnd < list->mpCapacity) {
            body_entry* p = list->mpEnd++;
            if (p)
                *p = tmp;
        } else {
            list->Append(list->mpEnd, tmp);
        }

        body_entry* e = &list->mpBegin[k];
        const creature_body_static_data* sd = e->body->static_data;
        float scale = requested_scale;
        e->m[0] = sd->rest_center.x * scale;
        e->m[1] = sd->rest_center.y * scale;
        e->m[2] = sd->rest_center.z * scale;
        if (!static_data->mIgnoreGait)
            e->m[2] = sd->unk_140 * scale;
        e->m[3] = sd->rest_orientation_q.x;
        e->m[4] = sd->rest_orientation_q.y;
        e->m[5] = sd->rest_orientation_q.z;
        e->w0 = sd->rest_orientation_q.w;

        if (body->static_data->cap_flags & 0x10) {
            int joint = FUN_009d7d10(this, &e->m[0], &e->m[3]);
            last_joint_index = joint + 1;
            void* table = *(void**)FUN_00a09f50();
            *(int*)((char*)table + joint * 0x108 + 0x58) = (int)bidx;
        }
        ++k;
    } while (k < count);
}

// ------------------------------------------------------------------ @ 0x009c2300

// @ 0x009c2300
bool creature_static_data::FilterAndAddWiggle(wiggle_static_data* w, bool keep, bool sym)
{
    unsigned count = (unsigned)(mWiggles.mpEnd - mWiggles.mpBegin);
    int found = -1;
    unsigned i = 0;
    if (count != 0) {
        do {
            wiggle_static_data* o = &mWiggles.mpBegin[i];
            if (w->cap_a == o->cap_a && w->cap_b == o->cap_b) {
                creature_body_static_data* bodies = Bodies.mpBegin;
                int oParent = bodies[o->body].parent_bidx;
                int wParent = bodies[w->body].parent_bidx;
                float oVal, wVal;
                if (g_gait_channel == 0)      oVal = o->vx;
                else if (g_gait_channel == 1) oVal = o->vy;
                else if (g_gait_channel == 2) oVal = o->vz;
                else                          oVal = 0.0f;
                if (g_gait_channel == 0)      wVal = w->vx;
                else if (g_gait_channel == 1) wVal = w->vy;
                else if (g_gait_channel == 2) wVal = w->vz;
                else                          wVal = 0.0f;

                if (keep && o->channel == w->channel && wiggle_abs(oVal - wVal) < 0.01f &&
                    FUN_009b3150(&bodies[o->body].cap_flags, &bodies[w->body].cap_flags)) {
                    w->flag = 1;
                    o->flag = 1;
                }
                if ((!keep || oParent != wParent) && (!sym || w->flag == 0)) {
                    if (w->channel < o->channel || wVal > oVal)
                        found = (int)i;
                    else
                        return false;
                }
            }
            ++i;
        } while (i < count);
    }

    AddWiggle(this, w);
    if (found != -1) {
        mWiggles.mpBegin[found] = *w;
        return true;
    }
    if (mWiggles.mpEnd < mWiggles.mpCapacity) {
        wiggle_static_data* p = mWiggles.mpEnd++;
        if (p)
            *p = *w;
        return true;
    }
    FUN_009c10c0(mWiggles.mpEnd, w);
    return true;
}

// ------------------------------------------------------------------ @ 0x009c2520

// @ 0x009c2520
void bone_xform_vec::resize(unsigned n)
{
    unsigned s = (unsigned)(mpEnd - mpBegin);
    if (s < n) {
        bone_xform value;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                value.first.m[r][c] = (r == c) ? 1.0f : 0.0f;
        value.second.x = value.second.y = value.second.z = 0.0f;
        DoInsertValues30(mpEnd, n - s, &value);
        return;
    }
    bone_xform* newEnd = mpBegin + n;
    FUN_009b4550(mpEnd, mpEnd, newEnd);
    mpEnd -= (s - n);
}

// ------------------------------------------------------------------ @ 0x009c25f0

// @ 0x009c25f0
void wiggle_instance_vec::resize(unsigned n)
{
    unsigned s = (unsigned)(mpEnd - mpBegin);
    if (s < n) {
        wiggle_instance_data value;
        value.wiggle = 0;
        value.pad_004 = 0;
        value.flag4 = 0;
        value.flag5 = 0;
        value.pad_006[0] = value.pad_006[1] = 0;
        value.zero.x = value.zero.y = value.zero.z = 0.0f;
        value.pos.x = value.pos.y = value.pos.z = 0.0f;
        value.pos_copy.x = value.pos_copy.y = value.pos_copy.z = 0.0f;
        DoInsertValues2c(mpEnd, n - s, &value);
        return;
    }
    wiggle_instance_data* newEnd = mpBegin + n;
    FUN_009b4a20(mpEnd, mpEnd, newEnd);
    mpEnd -= (s - n);
}

// ------------------------------------------------------------------ @ 0x009c26a0

// @ 0x009c26a0
int creature_static_data::Release()
{
    int n = RefCount - 1;
    if (n < 1)
        n = 0;
    RefCount = n;
    if (n < 1) {
        RefCount = 1;
        this->~creature_static_data();
        operator delete[](this);
        return 0;
    }
    return n;
}

// ------------------------------------------------------------------ @ 0x009c26f0

// @ 0x009c26f0
void creature_static_data::InitWiggles()
{
    // Clear the wiggle list.
    FUN_009b43f0(mWiggles.mpBegin, mWiggles.mpEnd, mWiggles.mpEnd);
    mWiggles.mpEnd = mWiggles.mpBegin;

    const int legless = mIsLegless ? 1 : 0;
    const int keep = mIsLegless ? 0 : 1;

    unsigned n = (unsigned)(Bodies.mpEnd - Bodies.mpBegin);
    for (unsigned i = 0; i < n; ++i) {
        wiggle_static_data w;
        w.body = 0; w.cap_a = 0; w.cap_b = 0; w.channel = 0;
        w.vx = 0.0f; w.vy = 0.0f; w.vz = 0.0f;
        w.flag = 0;
        if (CreateWiggle(this, (int)i, &w, 0, 1, 1, legless, 0, 0))
            FilterAndAddWiggle(&w, keep != 0, true);
    }

    // Candidate symmetric-pair indices (the original keeps these in an eastl rbtree/fixed_pool;
    // the plain index list below reproduces which wiggles are dropped).
    uint32 list[0x400];
    unsigned listN = 0;

    unsigned wcount = (unsigned)(mWiggles.mpEnd - mWiggles.mpBegin);
    for (unsigned a = 0; a < wcount && listN < 0x400; ++a) {
        wiggle_static_data* wa = &mWiggles.mpBegin[a];
        creature_body_static_data* bodies = Bodies.mpBegin;
        int waParent = bodies[wa->body].parent_bidx;
        float waVal;
        if (g_gait_channel == 0) waVal = wa->vx;
        else if (g_gait_channel == 1) waVal = wa->vy;
        else if (g_gait_channel == 2) waVal = wa->vz;
        else waVal = 0.0f;

        for (unsigned b = 0; b < wcount; ++b) {
            if (a == b)
                continue;
            wiggle_static_data* wb = &mWiggles.mpBegin[b];
            if (waParent != bodies[wb->body].parent_bidx)
                continue;
            float wbVal;
            if (g_gait_channel == 0) wbVal = wb->vx;
            else if (g_gait_channel == 1) wbVal = wb->vy;
            else if (g_gait_channel == 2) wbVal = wb->vz;
            else wbVal = 0.0f;

            if (keep == 0 || wa->flag == 0) {
                if (wb->flag == 0 && (wa->channel < wb->channel || waVal < wbVal)) {
                    list[listN++] = a;
                    break;
                }
            } else if (!(bodies[wa->body].cap_flags & 4)) {
                list[listN++] = a;
                break;
            }
        }
    }

    // Erase the marked wiggles, highest index first.
    for (int idx = (int)listN - 1; idx >= 0; --idx) {
        uint32 wi = list[idx];
        wiggle_static_data* e = &mWiggles.mpBegin[wi];
        if (e + 1 < mWiggles.mpEnd)
            FUN_009b43f0(e, mWiggles.mpEnd, e + 1);
        mWiggles.mpEnd -= 1;
    }

    // Symmetry pass.
    for (unsigned i = 0; i < wcount; ++i) {
        wiggle_static_data w;
        w.body = 0; w.cap_a = 0; w.cap_b = 0; w.channel = 0;
        w.vx = 0.0f; w.vy = 0.0f; w.vz = 0.0f; w.flag = 0;
        if (CreateWiggle(this, (int)mWiggles.mpBegin[i].body, &w, 0, 0, 1, legless, 0, 0))
            FilterAndAddWiggle(&w, false, false);
    }
}

// ------------------------------------------------------------------ @ 0x009c2c20

// @ 0x009c2c20
void creature_instance_data::InitWiggles()
{
    unsigned n = (unsigned)(static_data->mWiggles.mpEnd - static_data->mWiggles.mpBegin);
    mWiggles.resize(n);

    unsigned count = (unsigned)(mWiggles.mpEnd - mWiggles.mpBegin);
    for (unsigned i = 0; i < count; ++i) {
        wiggle_instance_data* e = &mWiggles.mpBegin[i];
        wiggle_static_data* sw = &static_data->mWiggles.mpBegin[i];
        e->flag4 = 0;
        e->flag5 = 0;
        e->wiggle = sw;

        creature_body_static_data* bsd = Bodies.mpBegin[sw->body].static_data;
        float scale = requested_scale;
        float X = scale * bsd->rest_center.x;
        float Y = scale * bsd->rest_center.y;
        float Z = scale * bsd->rest_center.z;
        e->zero.x = e->zero.y = e->zero.z = 0.0f;

        float q0 = orientation.x, q1 = orientation.y, q2 = orientation.z, q3 = orientation.w;

        // q1..q3 are the vector part; q0 the scalar part. The original inlines this exact
        // operation order, reproduced component by component below.
        float xm4 = -(q1 * q1 + q2 * q2) * X;
        xm4 += (q2 * q0 + q1 * q3) * Z;
        xm4 += (q1 * q0 - q2 * q3) * Y;
        xm4 = 2.0f * xm4 + X;

        float xm0 = (q1 * q0 + q2 * q3) * X;
        xm0 += -(q0 * q0 + q2 * q2) * Y;
        xm0 += (q1 * q2 - q0 * q3) * Z;
        xm0 = 2.0f * xm0 + Y;

        float xm1 = (q0 * q2 - q1 * q3) * X;
        xm1 += -(q0 * q0 + q1 * q1) * Z;
        xm1 += (q1 * q2 + q0 * q3) * Y;
        xm1 = 2.0f * xm1 + Z;

        e->pos.x = position.x + xm4;
        e->pos.y = position.y + xm0;
        e->pos.z = position.z + xm1;
        e->pos_copy = e->pos;
    }

    char* base = (char*)this;
    *(float*)(base + 0x16a8) = 0.0f;
    *(uint8*)(base + 0x1704) = 0;
    *(uint8*)(base + 0x1705) = 1;
    *(void**)(base + 0x1700) = &desc_a;
    CreateWiggle(static_data, 0, &desc_b, 1, 0, 0, 0, 0, 0);
    *(void**)(base + 0x1768) = &desc_b;
    *(uint8*)(base + 0x176c) = 0;
    *(uint8*)(base + 0x176d) = 1;
    *(uint8*)(base + 0x168e) = 1;
    *(float*)(base + 0x1690) = 0.0f;
}

}  // namespace nSPCreatureAnim
