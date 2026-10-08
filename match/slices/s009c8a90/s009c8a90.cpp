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

namespace checkerlib {
struct vector_3 {
    float x, y, z;
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct vector_4 {
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
