// Slice s009c8a90: cBlockBlockCommand::OnEndBlock (0x009c8a90, 1600 bytes), the creature
// "block" ArgScript command (anim world block definitions).
//
// When the block definition ends (arg == 0): the box [min,max] kept in the command state is
// turned into the block's center (box middle rotated by the block orientation, plus the state
// anchor), its half extents (clamped to 0.5 when not positive), and its local offset. If the block
// has a parent block, the offsets are rotated into the parent's frame (inlined quaternion
// rotations). Finally the hash id is computed from the block name when still unset, and the
// block's local vector is scaled and offset.
//
// Layouts are retail offsets read from the disassembly; field names are Claude-coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

namespace checkerlib {
class vector_3 { public:
    float x, y, z;
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
class vector_4 { public:
    float x, y, z, w;
};
inline vector_3 operator+(const vector_3& a, const vector_3& b) { vector_3 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
inline vector_3 operator-(const vector_3& a, const vector_3& b) { vector_3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
inline vector_3 operator*(const vector_3& a, float s) { vector_3 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }
vector_3* QuaternionVectorTransform(vector_3* out, const vector_4* q, const vector_3* v);         // 0x0099c1a0
vector_3* QuaternionVectorTransformInverse(vector_3* out, const vector_4* q, const vector_3* v);  // 0x0099c310
}  // namespace checkerlib

using namespace checkerlib;

namespace EA { namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t nInitialValue, int charCase);   // 0x00932e80
} }

struct BlockFlags;
void __cdecl FUN_009fc220(BlockFlags*);                                  // 0x009fc220
struct BlockDef;
vector_3* __cdecl ScaledOffset(vector_3* out, BlockDef* b, float t);      // 0x009b53f0

// One block definition (0x468 bytes, array element of the owner's block table).
struct BlockDef {
    char      name[0x104];       // +0x000
    uint32_t  hash;              // +0x104
    uint32_t  pad_108;
    vector_3  center;            // +0x10c
    vector_4  orient;            // +0x118
    uint32_t  pad_128[(0x138 - 0x128) / 4];
    vector_3  half;              // +0x138
    vector_3  local;             // +0x144
    BlockFlags* flags() { return (BlockFlags*)((char*)this + 0x150); }
    uint32_t  pad_150[(0x1fc - 0x150) / 4];
    int       parent;            // +0x1fc
    uint32_t  pad_200;
    int       childMark;         // +0x204
    int       refCount;          // +0x208
    uint32_t  pad_20c[(0x330 - 0x20c) / 4];
    vector_3  offset;            // +0x330
    uint32_t  pad_33c[(0x344 - 0x33c) / 4];
    vector_3  parentLocal;       // +0x344
    vector_3  parentOffset;      // +0x350
    vector_3  scaled;            // +0x35c
    float     scaledLen;         // +0x368
    float     limit;             // +0x36c
    uint32_t  pad_370[(0x378 - 0x370) / 4];
    float     scale;             // +0x378
    uint32_t  pad_37c[(0x468 - 0x37c) / 4];
};

struct BlockOwner {
    uint32_t  pad_000[0x384 / 4];
    BlockDef* blocks;            // +0x384
};

struct CreatureCommandState {
    uint32_t     pad_000;
    int          count;          // +0x04
    uint32_t     pad_008[2];
    vector_3     anchor;         // +0x10
    vector_3     anchor2;        // +0x1c
    vector_3     boxMin;         // +0x28
    vector_3     boxMax;         // +0x34
    BlockDef*    block;          // +0x40
    BlockOwner*  owner;          // +0x44
};


// Rotates v by the inverse of the unit quaternion q.           (out of line: 0x0099c310)
__forceinline vector_3 QuaternionVectorTransformInverse(const vector_4& q, const vector_3& v)
{
    vector_3 r;
    float nxw = -(q.x * q.w), nzw = -(q.z * q.w), nxx = -(q.x * q.x);
    float yx = q.y * q.x, zy = q.z * q.y, yw = q.y * q.w, zx = q.z * q.x;
    float nyy = -(q.y * q.y), nzz = -(q.z * q.z);
    r.x = (((yx - nzw) * v.y + (zx + -yw) * v.z) + (nzz + nyy) * v.x) * 2.0f + v.x;
    r.y = (((nzz + nxx) * v.y + (zy - nxw) * v.z) + (yx + nzw) * v.x) * 2.0f + v.y;
    r.z = (((nyy + nxx) * v.z + (zy + nxw) * v.y) + (zx - -yw) * v.x) * 2.0f + v.z;
    return r;
}

namespace {

struct cBlockBlockCommand {
    uint32_t              pad_000[12];
    CreatureCommandState* mState;       // +0x30

    void OnEndBlock(bool bCancel);      // 0x009c8a90
};

// @ 0x009c8a90
void cBlockBlockCommand::OnEndBlock(bool bCancel)
{
    if (bCancel)
        return;

    CreatureCommandState* s = mState;
    BlockDef* b = s->block;
    vector_3 tmp;
    vector_3 mid = (s->boxMax + s->boxMin) * 0.5f;

    const vector_3* r = QuaternionVectorTransform(&tmp, &b->orient, &mid);
    s = mState;
    vector_3 c = *r + s->anchor;
    b->center.x = c.x; b->center.y = c.y; b->center.z = c.z;

    vector_3 d = s->anchor - c;
    r = QuaternionVectorTransformInverse(&tmp, &b->orient, &d);
    b->local = *r;

    s = mState;
    b->half = (s->boxMax - s->boxMin) * 0.5f;
    if (b->half.x <= 0.0f) b->half.x = 0.5f;
    if (b->half.y <= 0.0f) b->half.y = 0.5f;
    if (b->half.z <= 0.0f) b->half.z = 0.5f;

    FUN_009fc220(b->flags());
    int parentIdx = b->parent;
    b->childMark = -1;
    b->refCount = 0;

    if (parentIdx != -1) {
        BlockDef* p = mState->owner->blocks + parentIdx;
        p->refCount++;
        s = mState;
        // anchor2 relative to the parent block / this block, rotated by that block's orientation
        vector_3 vp, vb;
        vp.x = s->anchor2.x - p->center.x; vp.y = s->anchor2.y - p->center.y; vp.z = s->anchor2.z - p->center.z;
        vector_3 rp = QuaternionVectorTransformInverse(p->orient, vp);
        b->parentOffset.x = rp.x; b->parentOffset.y = rp.y; b->parentOffset.z = rp.z;
        vb.x = s->anchor2.x - b->center.x; vb.y = s->anchor2.y - b->center.y; vb.z = s->anchor2.z - b->center.z;
        vector_3 rb = QuaternionVectorTransformInverse(b->orient, vb);
        b->parentLocal.x = rb.x; b->parentLocal.y = rb.y; b->parentLocal.z = rb.z;
        r = ScaledOffset(&tmp, b, 1.0f);
        b->scaled = *r;
        b->scaledLen = (float)sqrt(b->scaled.x * b->scaled.x + b->scaled.y * b->scaled.y
                                   + b->scaled.z * b->scaled.z);
    }

    b->limit = FLT_MAX;
    if (b->hash == (uint32_t)-1) {
        if (b->name[0] == '0' && b->name[1] == 'x')
            b->hash = strtol(b->name, 0, 16);
        else
            b->hash = EA::Hash::FNV1_String8(b->name, 0x811c9dc5, 1);
    }

    float sc = b->scale;
    CreatureCommandState* st = mState;
    b->offset.x = b->offset.x * sc;
    b->offset.y = sc * b->offset.y;
    b->offset.z = b->offset.z * sc;
    b->offset.x = b->local.x + b->offset.x;
    b->offset.y = b->local.y + b->offset.y;
    b->offset.z = b->local.z + b->offset.z;
    st->count++;
}

}  // namespace

// =====================================================================
// Creature effect ArgScript block command (0x009c90d0 .. 0x009c9650).
//
// this+0x04 = EA::ArgScript::cIParser, this+0x0c = command state whose
// +0x40 slot holds the effect definition being filled in. Every command
// handler is a thiscall taking the cArguments* as its only stack argument.
// =====================================================================

#define SPVJOIN_(a, b) a##b
#define SPVJOIN(a, b) SPVJOIN_(a, b)
#define SPPV virtual void SPVJOIN(vfn_, __COUNTER__)();
#define SPPV2 SPPV SPPV
#define SPPV4 SPPV2 SPPV2
#define SPPV8 SPPV4 SPPV4

namespace EA { namespace ArgScript {

class cArguments {
 public:
    char const* const* MainArguments(int count) const;          // 0x00838320
};

// cIParser: retail numbering has one more slot before ParseBool than the dev
// PDB header, so the three string converters sit at +0x94/+0x98/+0x9c.
class cIParser {
 public:
    SPPV8 SPPV8 SPPV8 SPPV8 SPPV4 SPPV            // +0x00 .. +0x90
    virtual bool  ParseBool(const char* s);       // +0x94
    virtual float ParseFloat(const char* s);      // +0x98
    virtual int   ParseInt(const char* s);        // +0x9c
};

} }  // namespace EA::ArgScript

// Entry table stored at EffectDef+0x380 (element stride 0x14).
struct EffectEntryTable {
    unsigned long mCount;                                                          // +0x000
    unsigned char pad_004[0xa0];
    bool FUN_0099c4a0(unsigned long id, unsigned long value, float a, float b);    // 0x0099c4a0
};

// Effect definition filled in by the command block (retail offsets).
struct EffectDef {
    char          mName[0x1c];                                 // +0x000
    vector_3      mVec01c;                                     // +0x01c
    unsigned char pad_028[0x118 - 0x028];
    float         mQuat[4];                                    // +0x118
    unsigned char pad_128[0x158 - 0x128];
    unsigned long mIds[0x20];                                  // +0x158
    unsigned char mFlags[0x20];                                // +0x1d8
    unsigned char pad_1f8[0x220 - 0x1f8];
    char          mName2[0x104];                               // +0x220
    vector_3      mVec324;                                     // +0x324
    vector_3      mVec330;                                     // +0x330
    unsigned char pad_33c[4];
    unsigned char mBool340;                                    // +0x340
    unsigned char pad_341[0x380 - 0x341];
    EffectEntryTable mEntries;                                 // +0x380
};

struct EffectCommandState {
    unsigned char pad_000[8];
    int           mCount;                                      // +0x008
    unsigned char pad_00c[4];
    vector_3      mVec10;                                      // +0x010
    vector_3      mVec1c;                                      // +0x01c
    vector_3      mVec28;                                      // +0x028
    vector_3      mVec34;                                      // +0x034
    EffectDef*    mpDef;                                       // +0x040
};

struct cEffectBlockCommand {
    unsigned char             pad_000[4];
    EA::ArgScript::cIParser*  mpParser;                        // +0x004
    unsigned char             pad_008[4];
    EffectCommandState*       mpState;                         // +0x00c

    void FUN_009c90d0(EA::ArgScript::cArguments* a);            // 0x009c90d0
    void FUN_009c9130(EA::ArgScript::cArguments* a);            // 0x009c9130
    void FUN_009c9170(EA::ArgScript::cArguments* a);            // 0x009c9170
    void FUN_009c9200(EA::ArgScript::cArguments* a);            // 0x009c9200
    void FUN_009c9230(EA::ArgScript::cArguments* a);            // 0x009c9230
    void FUN_009c9260(EA::ArgScript::cArguments* a);            // 0x009c9260
    void FUN_009c92e0(EA::ArgScript::cArguments* a);            // 0x009c92e0
    void FUN_009c9340(EA::ArgScript::cArguments* a);            // 0x009c9340
    void FUN_009c93c0(EA::ArgScript::cArguments* a);            // 0x009c93c0
    void FUN_009c9460(EA::ArgScript::cArguments* a);            // 0x009c9460
    void FUN_009c94c0(EA::ArgScript::cArguments* a);            // 0x009c94c0
    void FUN_009c95e0(EA::ArgScript::cArguments* a);            // 0x009c95e0
    void FUN_009c9650(EA::ArgScript::cArguments* a);            // 0x009c9650
};

unsigned long __cdecl FeedbackLookupName(const char* name);     // 0x009fc0f0

// @ 0x009c90d0
void cEffectBlockCommand::FUN_009c90d0(EA::ArgScript::cArguments* a)
{
    strcpy(mpState->mpDef->mName, *a->MainArguments(1));
}

// @ 0x009c9130
void cEffectBlockCommand::FUN_009c9130(EA::ArgScript::cArguments* a)
{
    a->MainArguments(1);
}

// @ 0x009c9170
void cEffectBlockCommand::FUN_009c9170(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec1c.x = mpParser->ParseFloat(v[0]);
    mpState->mVec1c.y = mpParser->ParseFloat(v[1]);
    mpState->mVec1c.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c9200
void cEffectBlockCommand::FUN_009c9200(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(1);
    mpState->mpDef->mBool340 = mpParser->ParseBool(v[0]);
}

// @ 0x009c9230
void cEffectBlockCommand::FUN_009c9230(EA::ArgScript::cArguments* a)
{
    strcpy(mpState->mpDef->mName2, *a->MainArguments(1));
}

// @ 0x009c9260
void cEffectBlockCommand::FUN_009c9260(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(3);
    {   // the destination subobject is re-bound (address taken) for every component
        vector_3* dst = &mpState->mpDef->mVec324;
        dst->x = mpParser->ParseFloat(v[0]);
    }
    {
        vector_3* dst = &mpState->mpDef->mVec324;
        dst->y = mpParser->ParseFloat(v[1]);
    }
    {
        vector_3* dst = &mpState->mpDef->mVec324;
        dst->z = mpParser->ParseFloat(v[2]);
    }
}

// @ 0x009c92e0
void cEffectBlockCommand::FUN_009c92e0(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec10.x = mpParser->ParseFloat(v[0]);
    mpState->mVec10.y = mpParser->ParseFloat(v[1]);
    mpState->mVec10.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c9340
void cEffectBlockCommand::FUN_009c9340(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(3);
    {
        vector_3* dst = &mpState->mpDef->mVec330;
        dst->x = mpParser->ParseFloat(v[0]);
    }
    {
        vector_3* dst = &mpState->mpDef->mVec330;
        dst->y = mpParser->ParseFloat(v[1]);
    }
    {
        vector_3* dst = &mpState->mpDef->mVec330;
        dst->z = mpParser->ParseFloat(v[2]);
    }
}

// @ 0x009c93c0
void cEffectBlockCommand::FUN_009c93c0(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(4);
    float q[4];
    q[0] = mpParser->ParseFloat(v[0]);
    q[1] = mpParser->ParseFloat(v[1]);
    q[2] = mpParser->ParseFloat(v[2]);
    q[3] = mpParser->ParseFloat(v[3]);
    float* dst = mpState->mpDef->mQuat;
    dst[0] = q[0];
    dst[1] = q[1];
    dst[2] = q[2];
    dst[3] = q[3];
}

// @ 0x009c9460
void cEffectBlockCommand::FUN_009c9460(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec28.x = mpParser->ParseFloat(v[0]);
    mpState->mVec28.y = mpParser->ParseFloat(v[1]);
    mpState->mVec28.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c94c0
void cEffectBlockCommand::FUN_009c94c0(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(3);
    mpState->mVec34.x = mpParser->ParseFloat(v[0]);
    mpState->mVec34.y = mpParser->ParseFloat(v[1]);
    mpState->mVec34.z = mpParser->ParseFloat(v[2]);
}

// @ 0x009c95e0
void cEffectBlockCommand::FUN_009c95e0(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(2);
    if (mpState->mCount < 0x20) {
        mpState->mpDef->mIds[mpState->mCount] = FeedbackLookupName(v[0]);
        mpState->mpDef->mFlags[mpState->mCount] = (unsigned char)mpParser->ParseInt(v[1]);
        ++mpState->mCount;
    }
}

// @ 0x009c9650
void cEffectBlockCommand::FUN_009c9650(EA::ArgScript::cArguments* a)
{
    char const* const* v = a->MainArguments(2);
    mpState->mpDef->mEntries.FUN_0099c4a0(mpParser->ParseInt(v[0]), 0,
                                          mpParser->ParseFloat(v[1]), 1.0f);
}

// =====================================================================
// nSPCreatureAnim::creature_effect (retail size 0xac)
// =====================================================================
namespace nSPCreatureAnim {

struct cMWModel;

struct IUnknown {
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(unsigned long type);
};
struct cIVisualEffect : IUnknown {};

struct creature_instance_data {
    int AddRef();                                               // 0x00a17060
    int Release();                                              // 0x009c4cc0
};

struct IModelWorld {
    SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV8 SPPV4   // +0x000 ..
    virtual void DestroyModel(cMWModel* model, bool flag);                     // +0x170
};

struct cMWModel {
    IModelWorld*  mpWorld;                                      // +0x000
    unsigned long mFlags;                                       // +0x004
    unsigned char pad_008[0x40 - 0x008];
    int           mnRefCount;                                   // +0x040

    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        if (mnRefCount > 1) {
            mnRefCount = mnRefCount - 1;
            return mnRefCount;
        }
        mpWorld->DestroyModel(this, (bool)((mFlags >> 31) & 1));
        return 0;
    }
};

// Intrusive pointer: assignment expands to the retail
// "compare / AddRef new / store / Release old" sequence.
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
};

struct creature_effect {
    unsigned long key;                                          // 0x000
    unsigned long id;                                           // 0x004
    unsigned long bidx;                                         // 0x008
    vector_3      local_pos;                                    // 0x00c
    vector_4      local_rot;                                    // 0x018
    bool          f28;                                          // 0x028
    bool          f29;                                          // 0x029
    unsigned char pad_2a[2];
    float         f2c;                                          // 0x02c
    bool          f30;                                          // 0x030
    unsigned char pad_31[3];
    unsigned long d34;                                          // 0x034
    unsigned long d38;                                          // 0x038
    unsigned long d3c;                                          // 0x03c
    unsigned long d40;                                          // 0x040
    unsigned long d44;                                          // 0x044
    union {
        long  i;                                                // 0x048
        float f;
    } data48;
    AutoRefCount<creature_instance_data> ref4c;                 // 0x04c
    AutoRefCount<creature_instance_data> ref50;                 // 0x050
    AutoRefCount<creature_instance_data> ref54;                 // 0x054
    unsigned long d58;                                          // 0x058
    unsigned long d5c;                                          // 0x05c
    unsigned long d60;                                          // 0x060
    vector_3      src_pos_rand;                                 // 0x064
    unsigned long d70;                                          // 0x070
    unsigned long d74;                                          // 0x074
    AutoRefCount<creature_instance_data> ref78;                 // 0x078
    unsigned long d7c;                                          // 0x07c
    vector_3      dst_pos_rand;                                 // 0x080
    AutoRefCount<cIVisualEffect> effect;                        // 0x08c
    AutoRefCount<cMWModel>       model;                         // 0x090
    unsigned long sound_id;                                     // 0x094
    vector_3      last_sound_pos;                               // 0x098
    AutoRefCount<IUnknown>       unknown;                       // 0x0a4
    unsigned long da8;                                          // 0x0a8

    void SetWorldState();                                       // 0x009c8890 (creature_mesh_instance_data)
    void Dispose();                                             // 0x009c8460 (creature_mesh_instance_data)
    void Clear(bool bAll);                                      // 0x009c96b0
    ~creature_effect();                                         // 0x009c9870
};

// @ 0x009c96b0
void creature_effect::Clear(bool bAll)
{
    if (!bAll) {
        SetWorldState();
        Dispose();
        model = 0;
        unknown = 0;
        da8 = 0;
    }
    id = 0;
    bidx = 0;
    f29 = false;
    f2c = 1.0f;
    f30 = false;
    d34 = 0;
    d40 = 0;
    d3c = 0;
    d38 = 0;
    data48.i = 0;
    ref54 = 0;
    ref50 = ref54.mpObject;
    ref4c = ref50.mpObject;
    d58 = d5c = d60 = 0xffffffff;
    ref78 = 0;
    d7c = 0xffffffff;
    local_pos.x = 0.0f;
    local_pos.y = 0.0f;
    local_pos.z = 0.0f;
    local_rot.x = 0.0f;
    local_rot.y = 0.0f;
    local_rot.z = 0.0f;
    local_rot.w = 1.0f;
    unknown = 0;
    da8 = 0;
    effect = 0;
    model = 0;
    sound_id = 0;
}

// @ 0x009c9870
creature_effect::~creature_effect()
{
    key = 0xffffffff;
    Clear(false);
}

}  // namespace nSPCreatureAnim

#undef SPPV8
#undef SPPV4
#undef SPPV2
#undef SPPV
#undef SPVJOIN
#undef SPVJOIN_
