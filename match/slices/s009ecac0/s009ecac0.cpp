// Slice s009ecac0 -- 0x009ecac0, 2214 bytes (thiscall, ret 4).
//
// nSPCreatureAnim IK solver, per-bone finish pass (retail-only function, name guessed:
// IkSolver::UpdateBone).  Called on a bone and recursed over its children:
//
//  1. Distance clamp.  An "anchored" bone (+0x234) remembers its position (+0x1d4) and is pulled back
//     towards the end bone of its constraint (+0x240) when it is further away than
//     (kStretch + 1.0) * constraint.reach; a free bone with mode 0 is pulled towards its previous
//     position (+0x1bc) when it moved further than 0.01.
//  2. Recurse over the child bones [def->firstChild, +childCount) of the shared bone array.
//  3. Orientation.  A free bone only refreshes its pivot position.  An anchored bone either copies a
//     stored quaternion (+0x68, when +0x78 > 0), or (mode != 0) re-aims itself along its constraints:
//       - constraints at +0x240 and +0x244: quat = fromTwoVectors(v248, end-of-0x240 - start-of-0x244)
//         * solver rotation * def rotation, applied with the register helper 0x009ec360;
//       - only +0x240: Hermite tangent frame built from the end bone's rest vectors and positions
//         (damped by count/kMinCount when below the spline threshold), same product and helper;
//       - only +0x244: parent quat * def rotation applied with the +0x244 constraint's tangent/up;
//       - neither: quat = stored quat at +0x200.
//  4. pivotPos = pos - quat.Rotate(def->pivot * solver scale); dirty = 1.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (x87 fsqrt/fcompi for the lengths, SSE for the rest).
//
// @ 0x009ecac0

#include <math.h>
#pragma intrinsic(sqrt)

typedef unsigned char u8;
typedef unsigned int  u32;

struct Vec3 {
    float x, y, z;
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quat {
    float x, y, z, w;
    Quat& operator=(const Quat& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};

struct Bone;
struct Ctx;

struct BoneDef {                // *bone (static data of the bone)
    u8   pad000[0x118];
    Quat q118;                  // +0x118
    Quat q128;                  // +0x128
    u8   pad138[0x150 - 0x138];
    u8   flags150;              // +0x150 (bit 3 = enabled)
    u8   pad151[0x204 - 0x151];
    u32  firstChild;            // +0x204
    u32  childCount;            // +0x208
    u8   pad20c[0x344 - 0x20c];
    Vec3 pivot;                 // +0x344
};

struct Ctx {                    // IK constraint (spline context)
    Bone* end;                  // +0x00
    Bone* start;                // +0x04
    u8   pad08[0x10 - 0x8];
    float reach;                // +0x10
    u8   pad14[0x34 - 0x14];
    Vec3 endTan;                // +0x34
    Vec3 endUp;                 // +0x40
    u8   pad4c[0x64 - 0x4c];
    Vec3 startTan;              // +0x64
    Vec3 startUp;               // +0x70
    u8   pad7c[0xc8 - 0x7c];
    float length;               // +0xc8
    int  count;                 // +0xcc
};

struct Bone {                   // 0x2bc bytes
    BoneDef* def;               // +0x000
    u8   pad004[4];
    Bone* ref8;                 // +0x008 (object whose +0x19c / +0x200 hold quaternions)
    u8   pad00c[0x38 - 0xc];
    u8   dirty;                 // +0x038
    u8   pad039[0x68 - 0x39];
    Quat storedQuat;            // +0x068
    float storedWeight;         // +0x078
    u8   pad07c[0x190 - 0x7c];
    Vec3 pivotPos;              // +0x190
    Quat quat;                  // +0x19c
    u8   mode;                  // +0x1ac (low 3 bits)
    u8   pad1ad[3];
    Vec3 pos;                   // +0x1b0
    Vec3 prevPos;               // +0x1bc
    u8   pad1c8[0x1d4 - 0x1c8];
    Vec3 lastPos;               // +0x1d4
    u8   pad1e0[0x200 - 0x1e0];
    Quat restQuat;              // +0x200
    u8   pad210[0x234 - 0x210];
    u8   anchored;              // +0x234
    u8   pad235[0x23c - 0x235];
    float f23c;
    Ctx* ctxA;                  // +0x240
    Ctx* ctxB;                  // +0x244
    Vec3 v248;                  // +0x248
    u8   pad254[0x2bc - 0x254];
};

struct Anim {
    u8   pad00[0x70];
    float scale;                // +0x70
    u8   pad74[0x2e4 - 0x74];
    Bone* bones;                // +0x2e4
};

extern "C" {
    Vec3* __cdecl FUN_0099c1a0(Vec3* out, const Quat* q, const Vec3* v);                  // QuaternionVectorTransform
    Quat* __cdecl FUN_0099c0b0(Quat* out, const Quat* a, const Quat* b);                  // QuaternionProduct
    void  __cdecl FUN_009ac7a0(Quat* out, const Vec3* a, const Vec3* b, int flag);        // QuaternionFromTwoVectors
    Vec3* __cdecl FUN_009a49d0(Vec3* out, const Vec3* v, float* lengthOut);               // NormalizeVec3
    // 0x009ec360: register convention in the original (EAX = bone, ESI = quaternion); modeled as
    // ordinary leading arguments.
    void  __cdecl FUN_009ec360(Bone* bone, const Quat* q, const Vec3* tan, const Vec3* up);
}
extern float g_stretch;         // 0x01550a10 (0.2)
extern float g_tension;         // 0x01550a64 (1.5)
extern int   g_splineMinCount;  // 0x01550a3c (3)

struct QuatRect {               // EA::RectT<float> used as a 16-byte copy
    float v[4];
    QuatRect& operator=(const QuatRect& o);     // 0x00572600
};

struct Vec4 {
    float x, y, z, w;
    Vec4* Normalize(float* lengthOut);          // 0x0099c020
};

static __forceinline Vec3 operator-(const Vec3& a, const Vec3& b)
{
    Vec3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

static __forceinline float Sqrt(float v) { return (float)sqrt((double)v); }

struct IkSolver {
    Anim* anim;                 // +0
    Quat* rootQuat;             // +4
    void UpdateBone(Bone* b);   // 0x009ecac0
};

// pivotPos = pos - quat.Rotate(def->pivot * scale); dirty = 1
static __forceinline void UpdatePivot(IkSolver* s, Bone* b)
{
    float scale = s->anim->scale;
    Vec3 v;
    v.x = b->def->pivot.x * scale;
    v.y = b->def->pivot.y * scale;
    v.z = b->def->pivot.z * scale;
    Vec3 tmp;
    Vec3* r = FUN_0099c1a0(&tmp, &b->quat, &v);
    b->pivotPos.x = b->pos.x - r->x;
    b->pivotPos.y = b->pos.y - r->y;
    b->pivotPos.z = b->pos.z - r->z;
    b->dirty = 1;
}

void IkSolver::UpdateBone(Bone* b)
{
    if ((b->mode & 7) == 4)
        return;
    if ((b->def->flags150 & 8) == 0)
        return;

    if (b->anchored != 0) {
        b->lastPos = b->pos;
        Ctx* c = b->ctxA;
        if (c != 0) {
            Bone* e = c->end;
            Vec3 d = b->pos - e->pos;
            float dx = d.x, dy = d.y, dz = d.z;
            float limit = (g_stretch + 1.0f) * c->reach;
            float dist = Sqrt((dx * dx + dy * dy) + dz * dz) + 1e-08f;
            if (dist > limit) {
                float s = limit / dist;
                b->pos.x = e->pos.x + dx * s;
                b->pos.y = e->pos.y + dy * s;
                b->pos.z = e->pos.z + dz * s;
            }
        }
    } else if ((b->mode & 7) == 0) {
        Vec3 d = b->pos - b->prevPos;
        float dx = d.x, dy = d.y, dz = d.z;
        float dist = Sqrt((dx * dx + dy * dy) + dz * dz) + 1e-08f;
        if (dist > 0.01f) {
            float s = 0.01f / dist;
            b->pos.x = dx * s + b->prevPos.x;
            b->pos.y = b->prevPos.y + dy * s;
            b->pos.z = b->prevPos.z + dz * s;
        }
    }

    for (u32 i = 0; i < b->def->childCount; i++)
        UpdateBone(&anim->bones[b->def->firstChild + i]);

    if (b->anchored == 0) {
        UpdatePivot(this, b);
        return;
    }

    if (b->storedWeight > 0.0f) {
        b->quat = b->storedQuat;
    } else if ((b->mode & 7) != 0) {
        Ctx* a = b->ctxA;
        if (a != 0) {
            if (b->ctxB != 0) {
                Bone* s2 = b->ctxB->start;
                Bone* e = a->end;
                Vec3 d;
                d.x = e->pos.x - s2->pos.x;
                d.y = e->pos.y - s2->pos.y;
                d.z = e->pos.z - s2->pos.z;
                Quat q, t1, t2;
                FUN_009ac7a0(&q, &b->v248, &d, 0);
                Quat* m = FUN_0099c0b0(&t1, &q, rootQuat);
                FUN_0099c0b0(&t2, m, &b->def->q118);
                FUN_009ec360(b, &t2, &b->ctxA->startTan, &b->ctxA->startUp);
            } else {
                Bone* e = a->end;
                Vec3 bPrev = b->prevPos;
                Vec3 ePrev = e->prevPos;
                Vec3 bPos = b->pos;
                Vec3 ePos = e->pos;
                Vec3 x;
                Vec3* dir;
                Vec3 tmp;
                if (e->ctxA != 0) {
                    x = e->v248;
                    Vec3 diff;
                    diff.x = e->ctxA->end->pos.x - b->pos.x;
                    diff.y = e->ctxA->end->pos.y - b->pos.y;
                    diff.z = e->ctxA->end->pos.z - b->pos.z;
                    dir = FUN_009a49d0(&tmp, &diff, 0);
                } else {
                    Vec3* r = FUN_0099c1a0(&tmp, &e->ref8->restQuat, &a->endTan);
                    x = *r;
                    dir = FUN_0099c1a0(&tmp, &e->ref8->quat, &a->endTan);
                }
                Vec3 d0;
                d0.x = dir->x; d0.y = dir->y; d0.z = dir->z;
                float f = a->length * g_tension;
                float dx = ePos.x - bPos.x;
                float dy = ePos.y - bPos.y;
                float dz = ePos.z - bPos.z;
                Vec3 T;
                T.x = (ePrev.x - bPrev.x) * 1.5f - (f * x.x) * 0.5f;
                T.y = (ePrev.y - bPrev.y) * 1.5f - (x.y * f) * 0.5f;
                T.z = (ePrev.z - bPrev.z) * 1.5f - (x.z * f) * 0.5f;
                float len = Sqrt((dy * dy + dz * dz) + dx * dx) * g_tension;
                d0.x = d0.x * len;
                d0.y = d0.y * len;
                d0.z = d0.z * len;
                Vec3 U;
                U.x = dx * 1.5f - d0.x * 0.5f;
                U.y = dy * 1.5f - d0.y * 0.5f;
                U.z = dz * 1.5f - d0.z * 0.5f;
                Quat q;
                FUN_009ac7a0(&q, &T, &U, 0);
                if (a->count < g_splineMinCount) {
                    float r = (float)a->count / (float)g_splineMinCount;
                    r = r * r;
                    q.x = q.x * r;
                    q.y = q.y * r;
                    q.z = q.z * r;
                    float w = q.w * r;
                    float one = 1.0f - r;
                    if (w >= 0.0f)
                        q.w = one + w;
                    else
                        q.w = w - one;
                    ((Vec4*)&q)->Normalize(0);
                }
                Quat t1, t2;
                Quat* m = FUN_0099c0b0(&t1, &q, rootQuat);
                FUN_0099c0b0(&t2, m, &b->def->q118);
                FUN_009ec360(b, &t2, &a->startTan, &a->startUp);
            }
        } else {
            Ctx* c2 = b->ctxB;
            if (c2 != 0) {
                Quat t;
                FUN_0099c0b0(&t, &b->ref8->quat, &b->def->q128);
                FUN_009ec360(b, &t, &c2->endTan, &c2->endUp);
            } else {
                ((QuatRect*)&b->quat)->operator=(*(QuatRect*)&b->restQuat);
            }
        }
    }

    UpdatePivot(this, b);
}

// ============================================================================================
// 0x009ed370 / 0x009ed560 -- two IK-solver helpers that MSVC gave an internal register ABI
// (they are static helpers in ik_solver.cpp; the caller at 0x009f3af0 passes the record in EAX and
// keeps its other arguments in registers).  Both are reconstructed here as ordinary functions with
// the same arguments in a natural order; the register assignment itself is not reproducible from C++
// source, so neither is byte-exact.
// ============================================================================================

// creature_body_static_data, the two fields the helpers read (same record as BoneDef above).
struct IkBodyDef {
    u8   pad000[0x150];
    u32  flags;                       // +0x150 (bit 2 = "heavy" weight)
};

// creature_body_instance_data (700 bytes) seen through its particle fields
// (same record as Bone above, +0x1b0 .. +0x1fc).
struct IkBody {
    IkBodyDef* def;                   // +0x000
    u8   pad004[0x1b0 - 4];
    Vec3 pos;                         // +0x1b0 current particle position
    Vec3 rest;                        // +0x1bc rest particle position
    Vec3 goal;                        // +0x1c8 goal particle position
    u8   pad1d4[0x1fc - 0x1d4];
    u8   valid;                       // +0x1fc particle has a valid current position
};

extern float g_ikHeavyWeight;         // 0x01550a04 (same constant as slice s009f09a0)

// @ 0x009ed370
void AccumulateReference(IkBody* other, IkBody* self, float* ratio,
                         Vec3* sumGoal, Vec3* sumCur, float* weight)
{
    Vec3 g;
    g.x = other->goal.x - self->goal.x;
    g.y = other->goal.y - self->goal.y;
    g.z = other->goal.z - self->goal.z;
    Vec3 c;
    if (other->valid == 0) {
        c.x = other->rest.x - self->rest.x;
        c.y = other->rest.y - self->rest.y;
        c.z = other->rest.z - self->rest.z;
    } else {
        c.x = other->pos.x - self->pos.x;
        c.y = other->pos.y - self->pos.y;
        c.z = other->pos.z - self->pos.z;
    }
    float invC = 1.0f / (float)(sqrt(c.x * c.x + (c.y * c.y + c.z * c.z)) + 1e-08);
    float lenG = sqrtf(g.x * g.x + (g.z * g.z + g.y * g.y));
    float invG = 1.0f / (float)(lenG + 1e-08);
    float w = (other->def->flags & 4) ? g_ikHeavyWeight : 1.0f;
    float k = w * invG;
    sumGoal->x += g.x * k;
    sumGoal->y += g.y * k;
    sumGoal->z += g.z * k;
    k = w * invC;
    sumCur->z = c.z * k + sumCur->z;
    sumCur->x += c.x * k;
    sumCur->y += c.y * k;
    *ratio = (w * lenG) * invC + *ratio;
    *weight += w;
}

// creature_instance_data, the fields 0x009ed560 reads.  The full record is the "world" of
// IKContext (see slice s009f1990): scale at +0x70, particle array at +0x2e4, enabled at +0x168c.
struct IkWorldInfo {
    u8   pad000[0x18];
    Vec3 offset;                      // +0x18
    u8   pad024[0x3c - 0x24];
    Quat orientation;                 // +0x3c (world -> local rotation, applied inverted)
    u8   pad04c[0xe8 - 0x4c];
    Vec3 position;                    // +0xe8
    Vec3 up;                          // +0xf4 (world-space plane normal)
};

// Filled by 0x009ed560 and handed to IKSolveParticles (0x009f2a00); the layout is that of the
// IKContext of slice s009f1990 (world +0, rootQuat +4, plane normal +8, plane offset +0x20).
struct IkContext {
    IkWorldInfo* world;               // +0x00
    Quat*        rootQuat;            // +0x04
    Vec3         planeNormal;         // +0x08
    Vec3         planePoint;          // +0x14
    float        d;                   // +0x20 (planeNormal . planePoint)
};

// Rotate v by the inverse of q.  The original keeps the expanded form
// 2 * (off-diagonal terms) + v instead of folding the identity into the diagonal.
static __forceinline Vec3 RotateByInverse(const Quat& q, const Vec3& v)
{
    float x = q.x, y = q.y, z = q.z, w = q.w;
    Vec3 r;
    r.x = 2.0f * (-(y * y + z * z) * v.x + (x * y + z * w) * v.y + (x * z - y * w) * v.z) + v.x;
    r.y = 2.0f * ((x * y - z * w) * v.x - (x * x + z * z) * v.y + (y * z + x * w) * v.z) + v.y;
    r.z = 2.0f * ((x * z + y * w) * v.x + (y * z - x * w) * v.y - (x * x + y * y) * v.z) + v.z;
    return r;
}

// @ 0x009ed560
IkContext* BuildIKContext(IkContext* ctx, IkWorldInfo* world, Quat* rootQuat)
{
    ctx->world = world;
    ctx->rootQuat = rootQuat;

    ctx->planeNormal.x = 0.0f;
    ctx->planeNormal.y = 0.0f;
    ctx->planeNormal.z = 0.0f;
    ctx->planePoint.x = 0.0f;
    ctx->planePoint.y = 0.0f;
    ctx->planePoint.z = 0.0f;

    // Plane normal: the world up direction in the creature's frame.
    ctx->planeNormal = RotateByInverse(world->orientation, world->up);

    // Plane point: where the creature's frame sits, in the same frame.
    Vec3 delta;
    delta.x = world->position.x - world->offset.x;
    delta.y = world->position.y - world->offset.y;
    delta.z = world->position.z - world->offset.z;
    ctx->planePoint = RotateByInverse(world->orientation, delta);

    ctx->d = (ctx->planeNormal.z * ctx->planePoint.z
              + ctx->planeNormal.y * ctx->planePoint.y)
             + ctx->planeNormal.x * ctx->planePoint.x;
    return ctx;
}
