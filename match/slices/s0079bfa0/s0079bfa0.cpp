// slice s0079bfa0 - mesh triangle clipping against an infinite cylinder, one output (0x0079bfa0).
//
// Same structure as CylinderSlicer::Run (0x0079dce0, slice s0079dce0): each triangle of the job's
// index range gets a 0/1 bit per vertex from the cylinder test. Unlike that slice there is one
// index vector (mesh-level) and one Out builder, and the bit is inverted by the flag at this+0x28.
// Triangles whose three bits are all set are copied to the index vector; mixed ones are handled by
// the mode at this+8: 0 copies all three indices, 1 drops them, 2 copies them when two bits are set,
// 3 splits the triangle and interpolates new vertices at the cylinder crossings.
//
// Callee conventions (checked from their ret forms and call sites):
//   FUN_0071ddc0  cdecl, 5 args (add esp,0x14 at the call site)
//   vector_ushort_insert 0x6f5bc0  thiscall, ret 8
//   FUN_0079b4b0  AddVert  thiscall, ret 8
//   FUN_0079b520  AddLerp  thiscall, ret 0x10
//   Cylinder::Intersect 0x7999a0  thiscall (ECX = this, ret 8)
//
// Flags: /O2 /MD /Gy /TP
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
    void AddVert(int stream, int idx);                  // 0x79b4b0
    void AddLerp(int stream, int i, int j, float t);    // 0x79b520
    UShortVec* IdxVec() { return (UShortVec*)(vecs + cur * 0x14); }
};
struct Job {
    char pad0[4];
    int  stream;                                        // +4: index stream number (0x8c stride)
    int  start;                                         // +8
    int  end;                                           // +0xc
};

struct Cylinder {                                       // lives at CylinderClipper+0xc (esi = this+0xc at the calls)
    float cx, cy, cz;                                   // +0x0: a point on the axis
    float ax, ay, az;                                   // +0xc: unit axis direction
    float radiusSq;                                     // +0x18
    float Intersect(const float* a, const float* b);    // 0x7999a0 (x87 return): crossing parameter on a->b

    // 1 when the point's side matches keep: outside (squared distance from the axis > radius^2)
    // XOR keep == 0.
    __forceinline int Bit(const float* p, unsigned int keep) const
    {
        float dx = p[0] - cx;
        float dy = p[1] - cy;
        float dz = p[2] - cz;
        float t = (az * dz + ay * dy) + ax * dx;
        float rx = ax * t - dx;
        float ry = ay * t - dy;
        float rz = az * t - dz;
        float d2 = (rz * rz + ry * ry) + rx * rx;
        return ((radiusSq <= d2 && d2 != radiusSq) == keep) ? 1 : 0;
    }
};
struct CylinderClipper {
    char pad0[8];
    int      mode;                                      // +8
    Cylinder cyl;                                       // +0xc
    unsigned int keep;                                  // +0x28: which side the bit marks
    void Run(Mesh* mesh, Job* job, UShortVec* out, Out* clip);
};

static __forceinline void PushRaw3(UShortVec* v, const IndexStream* ib, uint i)
{
    v->push_back(ib->ReadU16(i));
    v->push_back(ib->ReadU16(i + 1));
    v->push_back(ib->ReadU16(i + 2));
}

// @ 0x0079bfa0
void CylinderClipper::Run(Mesh* mesh, Job* job, UShortVec* out, Out* clip)
{
    int sidx = FUN_0071ddc0(mesh, 1, 0, 3, 0xe);
    IndexStream* ib = (IndexStream*)(mesh->indexStreams + job->stream * 0x8c);
    Stream* vs = (Stream*)(mesh->streams + sidx * 0x20 + 0x10);
    int sIdx = job->stream;

    if (job->start < job->end) {
        int a = job->start;
        do {
            int b = a + 1;
            int c = a + 2;
            uint ia, ib_, ic;
            if (ib->remapBegin == ib->remapEnd) {
                ia = ib->Read(a);
                ib_ = ib->Read(b);
                ic = ib->Read(c);
            } else {
                Stream* rm = (Stream*)((char*)ib->remapBegin + *(short*)(ib->table + sidx * 4 + 2) * 0x10);
                ia = rm->Read(ib->Read(a));
                ib_ = rm->Read(ib->Read(b));
                ic = rm->Read(ib->Read(c));
            }
            const float* pA = (const float*)(vs->data + vs->stride * ia);
            const float* pB = (const float*)(vs->data + vs->stride * ib_);
            const float* pC = (const float*)(vs->data + vs->stride * ic);
            int bA = cyl.Bit(pA, keep);
            int bB = cyl.Bit(pB, keep);
            int bC = cyl.Bit(pC, keep);
            int sum = bA + bB + bC;

            if (sum == (sum / 3) * 3) {
                // all bits clear (0) or all set (3): only the all-set triangles are copied
                if (bA != sum % 3)
                    PushRaw3(out, ib, a);
            } else {
                switch (mode) {
                case 0:
                    PushRaw3(out, ib, a);
                    break;
                case 1:
                    break;
                case 2:
                    if (sum > 1)
                        PushRaw3(out, ib, a);
                    break;
                case 3: {
                    uint n = (uint)(clip->f8 - clip->f4) & 0xffff;
                    if (bA == 0) {
                        if (bB == 0) {
                            clip->AddLerp(sIdx, c, a, cyl.Intersect(pC, pA));
                            clip->AddLerp(sIdx, c, b, cyl.Intersect(pC, pB));
                            clip->AddVert(sIdx, c);
                        } else {
                            clip->AddLerp(sIdx, b, a, cyl.Intersect(pB, pA));
                            clip->AddVert(sIdx, b);
                            if (bC == 0) {
                                clip->AddLerp(sIdx, b, c, cyl.Intersect(pB, pC));
                            } else {
                                clip->AddVert(sIdx, c);
                                clip->AddLerp(sIdx, c, a, cyl.Intersect(pC, pA));
                            }
                        }
                    } else {
                        clip->AddVert(sIdx, a);
                        if (bB == 0) {
                            clip->AddLerp(sIdx, a, b, cyl.Intersect(pA, pB));
                            if (bC != 0) {
                                clip->AddLerp(sIdx, c, b, cyl.Intersect(pC, pB));
                                clip->AddVert(sIdx, c);
                            } else {
                                clip->AddLerp(sIdx, a, c, cyl.Intersect(pA, pC));
                            }
                        } else {
                            clip->AddVert(sIdx, b);
                            clip->AddLerp(sIdx, b, c, cyl.Intersect(pB, pC));
                            clip->AddLerp(sIdx, a, c, cyl.Intersect(pA, pC));
                        }
                    }
                    UShortVec* iv = clip->IdxVec();
                    iv->push_back((ushort)n);
                    iv->push_back((ushort)(n + 1));
                    iv->push_back((ushort)(n + 2));
                    if (sum > 1) {
                        iv = clip->IdxVec();
                        iv->push_back((ushort)n);
                        iv->push_back((ushort)(n + 2));
                        iv->push_back((ushort)(n + 3));
                    }
                    break;
                }
                }
            }
            a += 3;
        } while (a < job->end);
    }
}
