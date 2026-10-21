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
#include <math.h>

typedef unsigned char uint8;
typedef unsigned int  uint32;

namespace checkerlib {
class vector_3 { public: float x, y, z; };
class vector_4 { public: float x, y, z, w; };
class matrix_3x3 { public: float m[3][3]; };
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
    vector_3 v1c;                        // +0x1c
    vector_3 v28;                        // +0x28
    float s34;                           // +0x34
    uint8 flag;                          // +0x38
    uint8 pad_39[3];
    wiggle_static_data()
    {
        v1c.z = 0.0f; v1c.y = 0.0f; v1c.x = 0.0f;
        v28.z = 0.0f; v28.y = 0.0f; v28.x = 0.0f;
        s34 = 1.0f;
    }
    wiggle_static_data& operator=(const wiggle_static_data& o);   // 0x009b3ab0 (retail CopyBlock::operator=)
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

wiggle_static_data* CopyWiggles(wiggle_static_data* first, wiggle_static_data* last, wiggle_static_data* result);   // 0x009b43f0 cdecl

struct wiggle_vec : vec3p<wiggle_static_data> {
    void DoInsert(wiggle_static_data* pos, const wiggle_static_data& v);   // 0x009c10c0 ret 8
    void erase(wiggle_static_data* first, wiggle_static_data* last)
    {
        CopyWiggles(last, mpEnd, first);
        mpEnd -= (last - first);
    }
    void erase(wiggle_static_data* position)
    {
        if ((position + 1) < mpEnd)
            CopyWiggles(position + 1, mpEnd, position);
        --mpEnd;
    }
};

struct bone_xform {                      // pair<matrix_3x3, vector_3>, size 0x30
    matrix_3x3 first;
    vector_3   second;
    bone_xform()
    {
        first.m[0][1] = 0.0f; first.m[0][2] = 0.0f;
        first.m[1][0] = 0.0f; first.m[1][2] = 0.0f;
        first.m[2][0] = 0.0f; first.m[2][1] = 0.0f;
        first.m[2][2] = 1.0f; first.m[1][1] = 1.0f; first.m[0][0] = 1.0f;
        second.z = 0.0f; second.y = 0.0f; second.x = 0.0f;
    }
};

bone_xform* CopyBoneXforms(bone_xform* first, bone_xform* last, bone_xform* result);   // 0x009b4550 cdecl

struct bone_xform_vec : vec3p<bone_xform> {
    void resize(unsigned n);             // 0x009c2520
    void DoInsertValues(bone_xform* pos, unsigned n, const bone_xform& v);   // 0x009c11e0 ret 0xc
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
    uint8      pad_200[0x268];           // +0x200 .. 0x468
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
    wiggle_vec     mWiggles;             // +0x3b4
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
    uint8   flag4;                       // +0x04
    uint8   flag5;                       // +0x05
    uint8   pad_006a;
    uint8   pad_006b;
    vector_3 zero;                       // +0x08
    vector_3 pos;                        // +0x14
    vector_3 pos_copy;                   // +0x20
    wiggle_instance_data()
    {
        zero.z = 0.0f; zero.y = 0.0f; zero.x = 0.0f;
        pos.z = 0.0f; pos.y = 0.0f; pos.x = 0.0f;
        pos_copy.z = 0.0f; pos_copy.y = 0.0f; pos_copy.x = 0.0f;
    }
};

void DestroyWiggleInstances(void* first, void* last, void* result);   // 0x009b4a20 cdecl

struct wiggle_instance_vec : vec3p<wiggle_instance_data> {
    void resize(unsigned n);             // 0x009c25f0
    void DoInsertValues(wiggle_instance_data* pos, unsigned n, const wiggle_instance_data& v);   // 0x009c13a0 ret 0xc
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
    wiggle_instance_data inst_a;         // +0x1700
    wiggle_static_data desc_b;           // +0x172c
    wiggle_instance_data inst_b;         // +0x1768

    void BuildBodyList();
    void InitWiggles();
};

// ------------------------------------------------------------------ eastl fixed containers (local copies)

struct FixedNodePool {                   // eastl::fixed_node_pool<20,...>, size 0x14
    void*    mpHead;                     // +0x00
    uint32   pad04;
    void*    mpNext;                     // +0x08
    void*    mpCapacity;                 // +0x0c
    uint32   mnNodeSize;                 // +0x10
    void init(void* mem, unsigned memSize, unsigned nodeSize, unsigned align, unsigned alignOffset);   // 0x00921260 (eastl::fixed_pool_base::init) ret 0x14
};

struct RBNodeU32 {                       // rbtree node: right, left, parent, color, then the value
    RBNodeU32* mpNodeRight;
    RBNodeU32* mpNodeLeft;
    RBNodeU32* mpNodeParent;
    uint32     mColor;
    uint32     mKey;                     // +0x10
    void*      mValue;                   // +0x14
};
RBNodeU32* RBTreeIncrementU32(RBNodeU32* node);                         // 0x00921580 cdecl

struct KVPair { uint32 first; void* second; };
struct RbInsertResult { RBNodeU32* mpNode; int mbInserted; };
struct RbTrueType {};

struct FixedMapU32 {                     // eastl::fixed_map<unsigned, void*, 255>, size 0x2c
    uint32      mCompare;                // +0x00 (empty class slot)
    RBNodeU32*  mpNodeRight;             // +0x04  (anchor)
    RBNodeU32*  mpNodeLeft;              // +0x08
    RBNodeU32*  mpNodeParent;            // +0x0c
    uint32      mColor;                  // +0x10
    uint32      mnSize;                  // +0x14
    FixedNodePool mAllocator;            // +0x18

    RBNodeU32* anchor() { return (RBNodeU32*)&mpNodeRight; }
    RbInsertResult insert(const KVPair& v, RbTrueType t);               // 0x009c1700 (sret, ret 0xc)
    void DoNukeSubtree(RBNodeU32* pNode);                               // 0x00d3b370 ret 4
};

struct FixedVecU32 {                     // eastl::fixed_vector<unsigned, 255, true>
    uint32* mpBegin;                     // +0x00
    uint32* mpEnd;                       // +0x04
    uint32* mpCapacity;                  // +0x08
    uint32  mAllocPad;                   // +0x0c
    uint32* mpBuffer;                    // +0x10
    uint32  mPad14;                      // +0x14
    uint32  mBuffer[255];                // +0x18
    void DoInsertValue(uint32* pos, const uint32& v);                   // 0x00899480 ret 8
    void push_back(const uint32& v)
    {
        if (mpEnd < mpCapacity) {
            uint32* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

bool CreateWiggle(creature_static_data* c, int index, wiggle_static_data* desc,
                  int a, int b, int c2, int d, int e, int f);           // 0x009ba4c0
void AddWiggle(creature_static_data* c, wiggle_static_data* w);         // 0x009ba590
bool FUN_009b3150(const void* a, const void* b);                        // 0x009b3150
void FUN_009b4550(void* p0, void* p1, void* p2);                        // 0x009b4550
void FUN_009b4a20(void* p0, void* p1, void* p2);                        // 0x009b4a20
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

static inline float PickGait(const wiggle_static_data* w, int g)
{
    float v;
    switch (g) {
    case 0:  v = w->vx; break;
    case 1:  v = w->vy; break;
    case 2:  v = w->vz; break;
    default: v = 0.0f;  break;
    }
    return v;
}

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
                bool sameParent = bodies[w->body].parent_bidx == bodies[o->body].parent_bidx;
                int g = g_gait_channel;
                float oVal = PickGait(o, g);
                float wVal = PickGait(w, g);

                if (keep && o->channel == w->channel && fabs((double)oVal - (double)wVal) < 0.01f &&
                    FUN_009b3150(&bodies[o->body].cap_flags, &bodies[w->body].cap_flags)) {
                    w->flag = 1;
                    o->flag = 1;
                }
                if ((!sym || !sameParent) && (!keep || w->flag == 0)) {
                    if ((unsigned)o->channel < (unsigned)w->channel || wVal > oVal)
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
    mWiggles.DoInsert(mWiggles.mpEnd, *w);
    return true;
}

// ------------------------------------------------------------------ @ 0x009c2520

// @ 0x009c2520
void bone_xform_vec::resize(unsigned n)
{
    unsigned s = (unsigned)(mpEnd - mpBegin);
    if (n > s) {
        bone_xform value;
        DoInsertValues(mpEnd, n - s, value);
    } else {
        bone_xform* first = mpBegin + n;
        bone_xform* last = mpEnd;
        CopyBoneXforms(last, mpEnd, first);
        mpEnd -= (last - first);
    }
}

// ------------------------------------------------------------------ @ 0x009c25f0

// @ 0x009c25f0
void wiggle_instance_vec::resize(unsigned n)
{
    unsigned s = (unsigned)(mpEnd - mpBegin);
    if (n > s) {
        wiggle_instance_data value;
        DoInsertValues(mpEnd, n - s, value);
    } else {
        wiggle_instance_data* first = mpBegin + n;
        wiggle_instance_data* last = mpEnd;
        DestroyWiggleInstances(last, mpEnd, first);
        mpEnd -= (last - first);
    }
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
    const bool legless = mIsLegless != 0;
    const bool keep = !legless;

    {
        wiggle_static_data* first = mWiggles.mpBegin;
        wiggle_static_data* last = mWiggles.mpEnd;
        mWiggles.erase(first, last);
    }

    unsigned n = (unsigned)(Bodies.mpEnd - Bodies.mpBegin);
    for (unsigned i = 0; i < n; ++i) {
        wiggle_static_data w;
        if (CreateWiggle(this, (int)i, &w, 0, 1, 1, legless, 0, 0))
            FilterAndAddWiggle(&w, keep, true);
    }

    // temporary pool + fixed_map<unsigned, void*, 255> (parents of the dropped symmetric pairs)
    uint32 poolBuf[0x13ec / 4];
    FixedNodePool pool;
    pool.mpHead = 0;
    pool.init(poolBuf, 0x13ec, 0x14, 4, 0);
    pool.mpNext = poolBuf;
    pool.mpCapacity = (char*)poolBuf + 0x13ec;
    pool.mnNodeSize = 0x14;

    FixedMapU32 map;
    map.mpNodeRight = 0;
    map.mpNodeLeft = 0;
    map.mpNodeParent = 0;
    map.mColor = 0;
    map.mnSize = 0;
    map.mAllocator.mpHead = 0;
    map.mAllocator.init(pool.mpHead, 0x13ec, 0x14, 4, 0);
    map.mAllocator.mpNext = pool.mpHead;
    map.mAllocator.mpCapacity = (char*)pool.mpHead + 0x13ec;
    map.mpNodeRight = map.anchor();
    map.mpNodeLeft = map.anchor();
    map.mpNodeParent = 0;
    map.mColor = 0;
    map.mnSize = 0;
    map.mAllocator.mnNodeSize = 0x14;

    FixedVecU32 list;
    list.mpBegin = list.mBuffer;
    list.mpEnd = list.mBuffer;
    list.mpCapacity = list.mBuffer + 255;
    list.mpBuffer = list.mBuffer;

    unsigned wcount = (unsigned)(mWiggles.mpEnd - mWiggles.mpBegin);
    for (unsigned a = 0; a < wcount; ++a) {
        wiggle_static_data* wa = &mWiggles.mpBegin[a];
        creature_body_static_data* bodies = Bodies.mpBegin;
        creature_body_static_data* bodyA = &bodies[wa->body];
        int waParent = bodyA->parent_bidx;
        float waVal = PickGait(wa, g_gait_channel);

        wiggle_static_data* wb = mWiggles.mpBegin;
        for (unsigned b = 0; b < wcount; ++b, ++wb) {
            if (a == b)
                continue;
            if (waParent != bodies[wb->body].parent_bidx)
                continue;
            float wbVal = PickGait(wb, g_gait_channel);
            if (!keep || wa->flag == 0) {
                if (wb->flag == 0 && ((unsigned)wa->channel < (unsigned)wb->channel || waVal < wbVal)) {
                    list.push_back(a);
                    break;
                }
            } else if (!((bodyA->cap_flags >> 2) & 1)) {
                KVPair kv;
                kv.first = (uint32)waParent;
                kv.second = 0;
                map.insert(kv, RbTrueType());
                list.push_back(a);
                break;
            }
        }
    }

    // Erase the marked wiggles, highest index first.
    for (int idx = (int)(list.mpEnd - list.mpBegin) - 1; idx >= 0; --idx)
        mWiggles.erase(mWiggles.mpBegin + list.mpBegin[idx]);

    // Symmetry pass over the collected parents.
    if (g_wiggle_symmetry != 0) {
        RBNodeU32* node = map.mpNodeLeft;
        if (node != map.anchor()) {
            do {
                wiggle_static_data w;
                if (CreateWiggle(this, (int)node->mKey, &w, 0, 0, 1, legless, 0, 0))
                    FilterAndAddWiggle(&w, false, false);
                node = RBTreeIncrementU32(node);
            } while (node != map.anchor());
        }
    }

    if (list.mpBegin && list.mpBegin != list.mpBuffer)
        operator delete[](list.mpBegin);
    map.DoNukeSubtree(map.mpNodeParent);
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
        float Y = bsd->rest_center.y * scale;
        float X = scale * bsd->rest_center.x;
        float Z = bsd->rest_center.z * scale;
        e->zero.x = e->zero.y = e->zero.z = 0.0f;

        float q0 = orientation.x, q1 = orientation.y, q2 = orientation.z, q3 = orientation.w;
        float q1q3 = q1 * q3;
        float q0q3 = q0 * q3;
        float q2q3 = q2 * q3;
        float nq0q0 = -(q0 * q0);
        float q1q0 = q1 * q0;
        float q2q0 = q2 * q0;
        float nq1q1 = -(q1 * q1);
        float q2q1 = q2 * q1;
        float nq2q2 = -(q2 * q2);

        float A = nq2q2 + nq0q0;
        float B = nq2q2 + nq1q1;
        float C = q2q0 + q1q3;
        float D = q1q0 - q2q3;
        float E = q1q0 + q2q3;
        float F = q2q1 - q0q3;
        float G = q2q0 - q1q3;
        float H = nq1q1 + nq0q0;
        float J = q2q1 + q0q3;

        float T1 = ((B * X + C * Z) + D * Y) * 2.0f + X;
        float T2 = ((E * X + A * Y) + F * Z) * 2.0f + Y;
        float T3 = ((G * X + H * Z) + J * Y) * 2.0f + Z;

        e->pos.x = position.x + T1;
        e->pos.y = position.y + T2;
        e->pos.z = position.z + T3;
        e->pos_copy = e->pos;
    }

    f_16a8 = 0.0f;
    inst_a.flag4 = 0;
    inst_a.flag5 = 1;
    inst_a.wiggle = &desc_a;
    CreateWiggle(static_data, 0, &desc_b, 1, 0, 0, 0, 0, 0);
    inst_b.wiggle = &desc_b;
    inst_b.flag4 = 0;
    inst_b.flag5 = 1;
    flag_168e = 1;
    f_1690 = 0.0f;
}

}  // namespace nSPCreatureAnim
