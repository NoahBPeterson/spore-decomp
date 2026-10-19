// Slice s009f2970: 0x009f2a00 (2443 bytes), the IK solver's per-frame orientation pass
// (name guessed: IKSolveParticles). Signature from the asm: __stdcall, two stack args
// (ecx is never read at entry), ret 8; the eax at the return carries no meaning.
//
// 1. For every child particle of the root particle's body, run IKContext::Update (0x009f1990).
// 2. For particles 1..n-1 whose state is "driven" (low 3 bits == 4) rebuild the particle's
//    orientation from its parent's and the body's quaternions (mode 0: plain product, mode 2: product
//    blended with the previous orientation by a global factor, then normalised), then, when the
//    particle is not held back (counter at +0x144 == 0), derive its position (parent pivot plus the
//    rotated body velocity * dt) and pivot (position minus the rotated body offset * dt).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s009f1990).
#include "types.h"
#include <math.h>

struct IKParticle;

struct IKBody {
    uint32_t pad000[0x128 / 4];
    float    q[4];                // +0x128 orientation
    uint32_t pad138[(0x204 - 0x138) / 4];
    uint32_t childStart;          // +0x204
    uint32_t childCount;          // +0x208
    uint32_t pad20c[(0x344 - 0x20c) / 4];
    float    offset[3];           // +0x344
    float    velocity[3];         // +0x350
};

struct IKWorld {
    uint32_t pad000[0x70 / 4];
    float    dt;                  // +0x70
    uint32_t pad074[(0x2e4 - 0x74) / 4];
    char*    particlesBegin;      // +0x2e4 (700-byte IKParticle array)
    char*    particlesEnd;        // +0x2e8
    uint32_t pad2ec[(0x1794 - 0x2ec) / 4];
    char     hold;                // +0x1794
};

struct IKParticle {
    IKBody*     body;             // +0x000
    uint32_t    pad004;
    IKParticle* parent;           // +0x008
    uint32_t    pad00c[11];
    uint8_t     dirty;            // +0x038
    uint8_t     pad039[0x144 - 0x39];
    int         holdCount;        // +0x144
    uint32_t    pad148[(0x190 - 0x148) / 4];
    float       pivot[3];         // +0x190
    float       q[4];             // +0x19c
    uint8_t     state;            // +0x1ac (low 3 bits = mode)
    uint8_t     pad1ad[3];
    float       pos[3];           // +0x1b0
    uint32_t    pad1bc[(0x238 - 0x1bc) / 4];
    int         solveMode;        // +0x238
};

struct IKContext {
    IKWorld* world;               // +0x00
    void __thiscall Update(IKParticle* p);   // 0x009f1990
};

extern int   g_holdEnabled;       // DAT_01550ad4
extern float g_blend;             // DAT_0166c000

// @ 0x009f2a00
void __stdcall IKSolveParticles(IKContext* ctx, IKParticle* root)
{
    uint32_t count = root->body->childCount;
    for (uint32_t i = 0; i < count; i++)
        ctx->Update((IKParticle*)(ctx->world->particlesBegin + (root->body->childStart + i) * 700));

    unsigned int n = (unsigned int)((ctx->world->particlesEnd - ctx->world->particlesBegin) / 700);
    if (n <= 1)
        return;
    n -= 1;
    int off = 700;
    do {
        IKParticle* P = (IKParticle*)(ctx->world->particlesBegin + off);
        if ((P->state & 7) == 4) {
            IKBody* bone = P->body;
            IKParticle* Q = P->parent;
            int mode = P->solveMode;
            bool compute = true;
            if (mode == 0) {
                if (g_holdEnabled != 0 && ctx->world->hold != 0) {
                    P->holdCount++;
                    compute = false;
                } else {
                    float b0 = bone->q[0], b1 = bone->q[1], b2 = bone->q[2], b3 = bone->q[3];
                    float q0 = Q->q[0], q1 = Q->q[1], q2 = Q->q[2], q3 = Q->q[3];
                    float r0 = ((q0 * b3 + b0 * q3) - q2 * b1) + q1 * b2;
                    float r1 = ((q1 * b3 + q2 * b0) + b1 * q3) - b2 * q0;
                    float r2 = ((q2 * b3 - q1 * b0) + b1 * q0) + b2 * q3;
                    float r3 = ((b3 * q3 - q0 * b0) - q1 * b1) - b2 * q2;
                    P->q[3] = r3;
                    P->q[0] = r0;
                    P->q[1] = r1;
                    P->q[2] = r2;
                    P->holdCount = 0;
                }
            } else if (mode == 2) {
                float b0 = bone->q[0], b1 = bone->q[1], b2 = bone->q[2], b3 = bone->q[3];
                float q0 = Q->q[0], q1 = Q->q[1], q2 = Q->q[2], q3 = Q->q[3];
                if (g_blend <= 0.0f) {
                    float r0 = ((b0 * q3 + q0 * b3) - b1 * q2) + b2 * q1;
                    float r1 = ((q2 * b0 + b1 * q3) + q1 * b3) - b2 * q0;
                    float r2 = ((q2 * b3 - q1 * b0) + b2 * q3) + b1 * q0;
                    float r3 = ((q3 * b3 - b0 * q0) - q1 * b1) - b2 * q2;
                    P->q[3] = r3;
                    P->q[0] = r0;
                    P->q[1] = r1;
                    P->q[2] = r2;
                } else {
                    float s = 1.0f - g_blend;
                    float n1 = (((b3 * q1 + q3 * b1) + q2 * b0) - q0 * b2) * s;
                    float n2 = (((q2 * b3 - b0 * q1) + q0 * b1) + q3 * b2) * s;
                    float n3 = (((q3 * b3 - b0 * q0) - q1 * b1) - q2 * b2) * s;
                    float n0 = (((b0 * q3 + q0 * b3) - q2 * b1) + b2 * q1) * s;
                    float p0 = P->q[0] * g_blend;
                    float p1 = P->q[1] * g_blend;
                    float p2 = P->q[2] * g_blend;
                    float p3 = P->q[3] * g_blend;
                    if (0.0f <= ((p0 * n0 + p3 * n3) + p2 * n2) + p1 * n1) {
                        p2 = p2 + n2;
                        p3 = p3 + n3;
                        p0 = p0 + n0;
                        p1 = p1 + n1;
                    } else {
                        p2 = p2 - n2;
                        p3 = p3 - n3;
                        p0 = p0 - n0;
                        p1 = p1 - n1;
                    }
                    float len = sqrtf(p1 * p1 + (p2 * p2 + (p3 * p3 + p0 * p0)));
                    if (len != 0.0f) {
                        len = 1.0f / len;
                        p0 = len * p0;
                        p1 = p1 * len;
                        p2 = p2 * len;
                        p3 = p3 * len;
                    }
                    P->q[0] = p0;
                    P->q[1] = p1;
                    P->q[2] = p2;
                    P->q[3] = p3;
                }
                P->holdCount = 0;
            }
            if (compute && P->holdCount == 0) {
                IKBody* body = P->body;
                IKWorld* w = ctx->world;
                float dt = w->dt;
                float q3 = Q->q[3];
                float q1 = Q->q[1];
                float vx = body->velocity[0] * dt;
                float vy = body->velocity[1] * dt;
                float vz = body->velocity[2] * dt;
                float q0 = Q->q[0];
                float q2 = Q->q[2];
                float px = Q->pivot[0];
                float py = Q->pivot[1];
                P->pos[2] = Q->pivot[2] +
                    ((((-(q1 * q1) + -(q0 * q0)) * vz + (q2 * q1 + q0 * q3) * vy) +
                      (q2 * q0 - q1 * q3) * vx) * 2.0f + vz);
                P->pos[1] = py + ((((-(q2 * q2) + -(q0 * q0)) * vy + (q2 * q1 - q0 * q3) * vz) +
                                   (q1 * q0 + q2 * q3) * vx) * 2.0f + vy);
                P->pos[0] = ((((q2 * q0 + q1 * q3) * vz + (q1 * q0 - q2 * q3) * vy) +
                              (-(q2 * q2) + -(q1 * q1)) * vx) * 2.0f + vx) + px;

                body = P->body;
                float dt2 = w->dt;
                float s3 = P->q[3];
                float s1 = P->q[1];
                float wx = body->offset[0] * dt2;
                float wy = body->offset[1] * dt2;
                float wz = body->offset[2] * dt2;
                float s0 = P->q[0];
                float s2 = P->q[2];
                P->pivot[0] = P->pos[0] -
                    ((((s2 * s0 + s1 * s3) * wz + (s1 * s0 - s2 * s3) * wy) +
                      (-(s2 * s2) + -(s1 * s1)) * wx) * 2.0f + wx);
                P->pivot[1] = P->pos[1] -
                    ((((-(s2 * s2) + -(s0 * s0)) * wy + (s2 * s1 - s0 * s3) * wz) +
                      (s1 * s0 + s2 * s3) * wx) * 2.0f + wy);
                P->pivot[2] = P->pos[2] -
                    ((((-(s1 * s1) + -(s0 * s0)) * wz + (s2 * s1 + s0 * s3) * wy) +
                      (s2 * s0 - s1 * s3) * wx) * 2.0f + wz);
                P->dirty = 1;
            }
        } else {
            P->holdCount = 0;
        }
        off += 700;
        n -= 1;
    } while (n != 0);
}
