// slice s0079dce0 - mesh triangle clipping against an infinite cylinder (0x0079dce0, 3180 bytes).
//
// The cylinder twin of the sphere clipper at 0x0079e950 (slice s0079e950); the stream/output
// helper types follow that slice. For every triangle of the job's index range it classifies the
// three vertices as inside/outside the cylinder (squared distance from the axis > radius^2 means
// outside). Triangles entirely on one side are copied to the matching index list; straddling ones
// are handled by the clipper's mode: 0/1 copy to one list, 2 copies to the majority side, 3 splits
// the triangle into two output meshes, interpolating new vertices at the cylinder crossings.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;
typedef unsigned short ushort;

// ---------------------------------------------------------------- vector<ushort>
struct UShortVec {
    ushort* mpBegin; ushort* mpEnd; ushort* mpCap;
    void DoInsert(ushort* pos, const ushort* val);      // 0x6f5bc0
    void PushBackOOL(const ushort* val);                // 0x6f66a0 (cVecU16::push_back)
    void push_back(ushort v) {
        ushort tmp = v;
        if (mpEnd < mpCap) {
            ushort* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsert(mpEnd, &tmp);
        }
    }
};

// ---------------------------------------------------------------- mesh streams
extern const uint g_formatMask[];                       // 0x140f544

struct Stream {                                         // vertex / index stream view
    uint  pad0;
    char* data;                                         // +4
    ushort fmt;                                         // +8
    ushort stride;                                      // +0xa
    uint  Read(uint i) const { return *(uint*)(data + stride * i) & g_formatMask[fmt]; }
    ushort ReadU16(uint i) const { return (ushort)(*(ushort*)(data + stride * i) & (ushort)g_formatMask[fmt]); }
};
struct IndexStream : Stream {                           // 0x8c bytes
    char pad1[0x14 - 0xc];
    char* table;                                        // +0x14: 4-byte entries, short at +2
    char pad2[0x44 - 0x18];
    Stream* remapBegin;                                 // +0x44 (0x10-byte records)
    Stream* remapEnd;                                   // +0x48
};
struct Mesh {
    char pad0[8];
    char* streams;                                      // +8: 0x20-byte stream descriptors, view at +0x10
    char pad1[0x1c - 0xc];
    char* indexStreams;                                 // +0x1c
};

extern "C" int FUN_0071ddc0(Mesh* m, int a, int b, int c, int d);   // find vertex stream (position)

struct VertRecord { uint v[4]; };                       // 16-byte output vertex record

struct Out {                                            // clip output builder
    char pad0[4];
    VertRecord* f4;                                     // +4: vertex records begin
    VertRecord* f8;                                     // +8: vertex records end
    char pad1[0x18 - 0xc];
    char* vecs;                                         // +0x18: 0x14-byte ushort vectors
    char pad2[0x30 - 0x1c];
    int  cur;                                           // +0x30
    void AddVert(void* src, int idx);                   // 0x79b4b0
    void AddLerp(void* src, int i, int j, float t);     // 0x79b520
    void AddTri(int idx);                               // 0x79b590
    UShortVec* IdxVec() { return (UShortVec*)(vecs + cur * 0x14); }
};
struct Job {
    char pad0[4];
    void* src;                                          // +4
    int  start;                                         // +8
    int  end;                                           // +0xc
};

struct Cylinder {
    float cx, cy, cz;                                   // +0x0: a point on the axis
    float ax, ay, az;                                   // +0xc: unit axis direction
    float radiusSq;                                     // +0x18
    float Intersect(const float* a, const float* b);    // 0x7999a0 (x87 return): crossing parameter on a->b

    // Squared distance of p from the axis, compared with the radius.
    bool IsOutside(const float* p) const
    {
        float dx = p[0] - cx;
        float dy = p[1] - cy;
        float dz = p[2] - cz;
        float t = (az * dz + ay * dy) + ax * dx;
        float rx = ax * t - dx;
        float ry = ay * t - dy;
        float rz = az * t - dz;
        return (rz * rz + ry * ry) + rx * rx > radiusSq;
    }
};
struct CylinderSlicer {
    char pad0[8];
    int      mode;                                      // +8
    Cylinder cyl;                                       // +0xc
    void Run(Mesh* mesh, Job* job, UShortVec* vecAllOut, UShortVec* vecAllIn, Out* out6, Out* out7);
};

// @ 0x0079dce0
void CylinderSlicer::Run(Mesh* mesh, Job* job, UShortVec* vecAllOut, UShortVec* vecAllIn, Out* out6, Out* out7)
{
    int sidx = FUN_0071ddc0(mesh, 1, 0, 3, 0xe);
    IndexStream* ib = (IndexStream*)(mesh->indexStreams + *(int*)((char*)job + 4) * 0x8c);
    Stream* vs = (Stream*)(mesh->streams + sidx * 0x20 + 0x10);

    for (int a = job->start; a < job->end; a += 3) {
        int b = a + 1;
        int c = a + 2;
        uint ia, ib_, ic;
        if (ib->remapBegin != ib->remapEnd) {
            Stream* rm = (Stream*)((char*)ib->remapBegin + *(short*)(ib->table + sidx * 4 + 2) * 0x10);
            ia = rm->Read(ib->Read(a));
            ib_ = rm->Read(ib->Read(b));
            ic = rm->Read(ib->Read(c));
        } else {
            ia = ib->Read(a);
            ib_ = ib->Read(b);
            ic = ib->Read(c);
        }
        const float* pA = (const float*)(vs->data + vs->stride * ia);
        const float* pB = (const float*)(vs->data + vs->stride * ib_);
        const float* pC = (const float*)(vs->data + vs->stride * ic);
        int fA = cyl.IsOutside(pA) ? 1 : 0;
        int fB = cyl.IsOutside(pB) ? 1 : 0;
        int fC = cyl.IsOutside(pC) ? 1 : 0;
        int sum = fC + fB + fA;

        if (sum == (sum / 3) * 3) {
            // all inside (0) or all outside (3): copy the triangle's indices
            UShortVec* v = (fA == sum % 3) ? vecAllIn : vecAllOut;
            v->push_back(ib->ReadU16(a));
            v->push_back(ib->ReadU16(b));
            v->push_back(ib->ReadU16(c));
        } else {
            switch (mode) {
            case 0:
                vecAllOut->push_back(ib->ReadU16(a));
                vecAllOut->push_back(ib->ReadU16(b));
                vecAllOut->push_back(ib->ReadU16(c));
                break;
            case 1:
                vecAllIn->push_back(ib->ReadU16(a));
                vecAllIn->push_back(ib->ReadU16(b));
                vecAllIn->push_back(ib->ReadU16(c));
                break;
            case 2: {
                ushort va = ib->ReadU16(a);
                UShortVec* v;
                if (sum > 1) {
                    vecAllOut->PushBackOOL(&va);
                    v = vecAllOut;
                } else {
                    vecAllIn->PushBackOOL(&va);
                    v = vecAllIn;
                }
                ushort vb = ib->ReadU16(b);
                v->PushBackOOL(&vb);
                ushort vc = ib->ReadU16(c);
                v->PushBackOOL(&vc);
                break;
            }
            case 3: {
                int n6 = out6->f8 - out6->f4;
                int n7 = out7->f8 - out7->f4;
                if (fA != 0) {
                    out6->AddVert(job->src, a);
                    if (fB != 0) {
                        float t1 = cyl.Intersect(pB, pC);
                        float t2 = cyl.Intersect(pA, pC);
                        out6->AddVert(job->src, b);
                        out6->AddLerp(job->src, b, c, t1);
                        out6->AddLerp(job->src, a, c, t2);
                        out7->AddLerp(job->src, c, a, 1.0f - t2);
                        out7->AddLerp(job->src, c, b, 1.0f - t1);
                        out7->AddVert(job->src, c);
                    } else {
                        float t = cyl.Intersect(pA, pB);
                        out6->AddLerp(job->src, a, b, t);
                        out7->AddLerp(job->src, b, a, 1.0f - t);
                        out7->AddVert(job->src, b);
                        if (fC != 0) {
                            float tt = cyl.Intersect(pC, pB);
                            out6->AddLerp(job->src, c, b, tt);
                            out6->AddVert(job->src, c);
                            out7->AddLerp(job->src, b, c, 1.0f - tt);
                        } else {
                            float tt = cyl.Intersect(pA, pC);
                            out6->AddLerp(job->src, a, c, tt);
                            out7->AddVert(job->src, c);
                            out7->AddLerp(job->src, c, a, 1.0f - tt);
                        }
                    }
                } else {
                    out7->AddVert(job->src, a);
                    if (fB != 0) {
                        float u = cyl.Intersect(pB, pA);
                        out6->AddLerp(job->src, b, a, u);
                        out6->AddVert(job->src, b);
                        out7->AddLerp(job->src, a, b, 1.0f - u);
                        if (fC != 0) {
                            float w = cyl.Intersect(pC, pA);
                            out6->AddVert(job->src, c);
                            out6->AddLerp(job->src, c, a, w);
                            out7->AddLerp(job->src, a, c, 1.0f - w);
                        } else {
                            float z = cyl.Intersect(pB, pC);
                            out6->AddLerp(job->src, b, c, z);
                            out7->AddLerp(job->src, c, b, 1.0f - z);
                            out7->AddVert(job->src, c);
                        }
                    } else {
                        float p = cyl.Intersect(pC, pA);
                        float q = cyl.Intersect(pC, pB);
                        out6->AddLerp(job->src, c, a, p);
                        out6->AddLerp(job->src, c, b, q);
                        out6->AddVert(job->src, c);
                        out7->AddVert(job->src, b);
                        out7->AddLerp(job->src, b, c, 1.0f - q);
                        out7->AddLerp(job->src, a, c, 1.0f - p);
                    }
                }
                UShortVec* i6 = out6->IdxVec();
                i6->push_back((ushort)n6);
                i6 = out6->IdxVec();
                i6->push_back((ushort)(n6 + 1));
                i6 = out6->IdxVec();
                i6->push_back((ushort)(n6 + 2));
                UShortVec* i7 = out7->IdxVec();
                i7->push_back((ushort)n7);
                i7 = out7->IdxVec();
                i7->push_back((ushort)(n7 + 1));
                i7 = out7->IdxVec();
                i7->push_back((ushort)(n7 + 2));
                Out* t = out7;
                int base = n7;
                if (sum > 1) {
                    base = n6;
                    t = out6;
                }
                t->AddTri(base);
                t->AddTri(base + 2);
                t->AddTri(base + 3);
                break;
            }
            }
        }
    }
}
