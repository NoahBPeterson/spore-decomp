// Slice s0052b340: skin-paint bone-weight builder (one 3756-byte /Od function).
//
// For every point of the paint mesh it asks the weight source for (segment, weight) candidates, spreads the
// weights over the 64 (max) skeleton influences along each segment, optionally biases the choice towards the
// bones near the strongest segment (param_10 > 0), keeps the four strongest influences and writes them as
// four bone bytes + four normalised weights per point (20-byte rows).  Finally it runs `param_9` smoothing
// passes (SkinBoneWeights), ping-ponging between the output buffer and a scratch buffer.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (no EH frame in the original).
#include "types.h"

struct Vec3 { float x, y, z; };

// 00 41 db 10: Vector3 operator-(a, b), returned through a hidden pointer (cdecl).
Vec3 __cdecl Vec3Sub(const Vec3& a, const Vec3& b);                 // 0041db10
float __cdecl VectorLength(const Vec3* v);                          // 0040ae50
void __cdecl MakeBoneTip(Vec3* out, const Vec3* p, const Vec3* q, float r);   // 004a5c70
float __cdecl GetExactSkinRadiusFromVertebra(float v);              // 004a5b70 (SP::EditorUtils)

struct Row {                       // one output row: four bone bytes and four weights (0x14 bytes)
    unsigned char bone[4];
    float         weight[4];
};

struct PairIF { int index; float weight; };

struct Joint {                     // 0x34 bytes
    Vec3      pos;                 // +0x00
    unsigned* childBegin;          // +0x0c
    unsigned* childEnd;            // +0x10
    unsigned* childCap;            // +0x14
    char      pad[0x34 - 0x18];
};

struct Bone {                      // 0x8c bytes
    char  pad0[0xb];
    unsigned char kind;            // +0x0b
    char  pad1[0x2c - 0xc];
    float radius;                  // +0x2c
    char  pad2[0x48 - 0x30];
    Vec3  a;                       // +0x48
    Vec3  b;                       // +0x54
    char  pad3[0x8c - 0x60];
};

struct Segment { int a, b; };

struct SkeletonObj { char pad[0x98]; Bone* boneBegin; Bone* boneEnd; };            // +0x98 / +0x9c
struct PointSet    { char pad[8]; Vec3* ptBegin; Vec3* ptEnd; };                    // +8 / +0xc
struct SegVec      { Segment* begin; Segment* end; };
struct JointVec    { Joint* begin; };
struct RemapTable  { unsigned* table; };

struct SpAllocator { char c; SpAllocator(const char* name); };                      // 00429360

// Local container shapes (begin/end/cap + allocator, 16 bytes) with out-of-line helpers.
struct RowVec {                                                                     // vector<Row>
    Row* mpBegin; Row* mpEnd; Row* mpCap; SpAllocator mAlloc;
    RowVec(const char* n) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(n) {}
    void resize(unsigned n);                                                        // 004cd690
    void Free();                                                                    // 0050ea50
    ~RowVec() { for (Row* p = mpBegin; p < mpEnd; ++p) {} Free(); }
};
struct FloatVec {                                                                   // vector<float>
    float* mpBegin; float* mpEnd; float* mpCap; char mAlloc[4];
    void Construct(const char* n);                                                  // 00540470
    void Init();                                                                    // 0052c1f0
    void resize(unsigned n, const float* v);                                        // 0052c380
    void Free();                                                                    // 00425990
    ~FloatVec() { for (float* p = mpBegin; p < mpEnd; ++p) {} Free(); }
};
struct PairVec {                                                                    // vector<PairIF>
    PairIF* mpBegin; PairIF* mpEnd; PairIF* mpCap; char mAlloc[4];
    void Construct(const char* n);                                                  // 00540470
    void Init();                                                                    // 004c5e70
    void erase(PairIF* first, PairIF* last);                                        // 00530c80
    void resize(unsigned n, const PairIF* v);                                       // 0052c570
    void insert(PairIF* pos, const PairIF* v);                                      // 0052c2e0
    void Free();                                                                    // 0045daf0
    ~PairVec() { for (PairIF* p = mpBegin; p < mpEnd; ++p) {} Free(); }
};
struct ScratchVec {                                                                 // vector of 8-byte items
    char* mpBegin; char* mpEnd; char* mpCap; char mAlloc[4];
    void Construct(unsigned n, const char* a);                                      // 0052c230
    void Free();                                                                    // 0045daf0
    ~ScratchVec() { for (char* p = mpBegin; p < mpEnd; p += 8) {} Free(); }
};

struct WeightSource { void Query(const Vec3* pt, PairVec* out); };                  // 004f9570

void __cdecl SkinBoneWeights(Row* src, Row* dst, ScratchVec* tmp, PointSet* pts, float f);   // 0052aeb0
extern float g_150cb04;                                                             // 0150cb04

// @ 0x0052b340
void SkinPaintBuild(Row** ppOut, JointVec* joints, SegVec* segs, int unused4, RemapTable* remap,
                    WeightSource* src, PointSet* pts, SkeletonObj* skel, int passes, float biasDist)
{
    (void)unused4;
    // leading run of bones with kind == 5
    Bone* bones = skel->boneBegin;
    int   nBones = (int)(skel->boneEnd - skel->boneBegin);
    int   nLead;
    for (nLead = 0; nLead < nBones && bones[nLead].kind == 5; ++nLead) {
    }
    unsigned nSegs   = (unsigned)(segs->end - segs->begin);
    unsigned nPoints = (unsigned)(pts->ptEnd - pts->ptBegin);

    char dummyAlloc;
    RowVec scratch(&dummyAlloc);
    Row* bufA;     // result rows being produced
    Row* bufB;     // other ping-pong buffer
    if (passes < 1) {
        bufA = *ppOut;
    } else {
        scratch.resize(nPoints);
        bufA = (passes % 2 == 0) ? *ppOut : scratch.mpBegin;
    }

    char dummyA, dummyB;
    FloatVec segWeight;
    segWeight.Construct(&dummyA);
    segWeight.Init();
    PairVec cand;
    cand.Construct(&dummyB);
    cand.Init();

    for (unsigned p = 0; p < nPoints; ++p) {
        cand.erase(cand.mpBegin, cand.mpEnd);
        Vec3* pt = &pts->ptBegin[p];
        src->Query(pt, &cand);
        float zero = 0.0f;
        segWeight.resize(nSegs, &zero);

        unsigned nCand = (unsigned)(cand.mpEnd - cand.mpBegin);
        for (unsigned j = 0; j < nCand; ++j) {
            unsigned idx = (unsigned)cand.mpBegin[j].index;
            float    wgt = cand.mpBegin[j].weight;
            if ((idx & 0x80000000) == 0) {
                Segment* seg = &segs->begin[idx];
                Vec3 a = joints->begin[seg->a].pos;
                Vec3 b = joints->begin[seg->b].pos;
                unsigned origIdx = idx;
                Vec3 ab = Vec3Sub(b, a);
                Vec3 pa = Vec3Sub(*pt, a);
                float num = (pa.x * ab.x + pa.y * ab.y) + pa.z * ab.z;
                float den = (ab.x * ab.x + ab.y * ab.y) + ab.z * ab.z;
                float one = 1.0f;
                float t = 0.0f;
                if (0.0f <= num / den)
                    t = num / den;
                if (one <= t)
                    t = one;
                int   endJoint;
                float near;
                if (t > 0.5f) {
                    endJoint = seg->b;
                    near = 1.0f - t;
                } else {
                    endJoint = seg->a;
                    near = t;
                }
                near = near * 2.0f;
                if (0.0f < wgt * near) {
                    if (remap != 0)
                        origIdx = remap->table[origIdx];
                    float* slot = &segWeight.mpBegin[origIdx];
                    *slot = wgt * near + *slot;
                }
                Joint* ej = &joints->begin[endJoint];
                unsigned nChild = (unsigned)(ej->childEnd - ej->childBegin);
                float share = ((1.0f - near) * wgt) / (float)nChild;
                if (0.0f < share) {
                    for (unsigned c = 0; c < nChild; ++c) {
                        Joint* j2 = &joints->begin[endJoint];
                        unsigned bi = j2->childBegin[c];
                        if (remap != 0)
                            bi = remap->table[bi];
                        unsigned limit = 0x40;
                        if (bi < limit) {
                            float* s2 = &segWeight.mpBegin[bi];
                            *s2 = *s2 + share;
                        }
                    }
                }
            } else {
                unsigned ji = idx & 0x7fffffff;
                Joint* jt = &joints->begin[ji];
                unsigned nChild = (unsigned)(jt->childEnd - jt->childBegin);
                float share = wgt / (float)nChild;
                for (unsigned c = 0; c < nChild; ++c) {
                    unsigned bi = jt->childBegin[c];
                    if (remap != 0)
                        bi = remap->table[bi];
                    unsigned limit = 0x40;
                    if (bi < limit) {
                        float* s2 = &segWeight.mpBegin[bi];
                        *s2 = *s2 + share;
                    }
                }
            }
        }

        if (0.0f < biasDist) {
            unsigned best = 0;
            for (unsigned s = 0; s < nSegs; ++s) {
                float* cur = &segWeight.mpBegin[s];
                float* top = &segWeight.mpBegin[best];
                if (*top < *cur)
                    best = s;
            }
            if ((int)best < nLead && 1 < nLead) {
                float zero2 = 0.0f;
                segWeight.resize(nSegs, &zero2);
                int first = ((int)best < 3) ? 0 : (int)best - 2;
                for (int b = first; b <= (int)(best + 2) && b < nLead; ++b) {
                    Bone* bone = &bones[b];
                    Vec3 tip;
                    MakeBoneTip(&tip, &bone->b, &bone->a, bone->radius);
                    float skinRadius = GetExactSkinRadiusFromVertebra(bone->radius);
                    Vec3 rel = Vec3Sub(*pt, tip);
                    Vec3 relCopy = rel;
                    float dist = VectorLength(&relCopy) - skinRadius;
                    if (0.0f <= dist)
                        segWeight.mpBegin[b] = biasDist / (biasDist + dist);
                    else
                        segWeight.mpBegin[b] = 1.0f;
                }
            }
        }

        // keep the four strongest segments, sorted by weight (insertion into a 4-entry list)
        PairIF init = { 0, 0.0f };
        cand.resize(4, &init);
        for (unsigned s = 0; s < nSegs; ++s) {
            PairIF* it = cand.mpBegin;
            while (it != cand.mpEnd) {
                float cur = segWeight.mpBegin[s];
                if (it->weight < cur) {
                    PairIF entry;
                    entry.index = (int)s;
                    entry.weight = segWeight.mpBegin[s];
                    cand.insert(it, &entry);
                    cand.mpEnd = cand.mpEnd - 1;
                    break;
                }
                ++it;
            }
        }

        PairIF* e0 = &cand.mpBegin[0];
        PairIF* e1 = &cand.mpBegin[1];
        PairIF* e2 = &cand.mpBegin[2];
        float total = ((e0->weight + e1->weight) + e2->weight) + cand.mpBegin[3].weight;
        Row* row = &bufA[p];
        for (unsigned k = 0; k < 4; ++k) {
            row->bone[k] = (unsigned char)cand.mpBegin[k].index;
            PairIF* pk = &cand.mpBegin[k];
            row->weight[k] = pk->weight / total;
        }
    }

    if (passes > 0) {
        char dummyC;
        ScratchVec tmp;
        tmp.Construct(0x40, &dummyC);
        bufB = (passes % 2 == 0) ? scratch.mpBegin : *ppOut;
        for (int k = 0; k < passes; ++k) {
            SkinBoneWeights(bufA, bufB, &tmp, pts, g_150cb04);
            Row* sw = bufA;
            bufA = bufB;
            bufB = sw;
        }
    }
}
