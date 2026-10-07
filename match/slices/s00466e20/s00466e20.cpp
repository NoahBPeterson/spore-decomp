// s00466e20 -- /Od /Ob1 region (skinner mesh export: gathers rigblock model triangles into
// flat index/position/normal/uv arrays and hands them to nSPSkinner::cExportHelper).

extern unsigned int maskTable[];   // 0x013eec84 index-format masks
extern char tableA[];              // 0x0140cf84
extern char tableB[];              // 0x0140cf90

// @ 0x00467980
// Vertex/index stream descriptor (16 bytes): count, data, format (mask index), stride.
struct ArrF {
    int pad0;                      // +0 element count
    char* data;                    // +4
    unsigned short maskIdx;        // +8
    unsigned short stride;         // +0xa
    unsigned int padc;             // +0xc
    unsigned int get(int i);       // 0x00467980
    char* at(unsigned int i);      // 0x00472640  return data + stride * i  (out of line)
    // inline twins of get()/at() (expanded in place in FUN_00466e20)
    unsigned int getI(unsigned int i) { return *(unsigned int*)(data + stride * i) & maskTable[maskIdx]; }
    char* atI(unsigned int i) { return data + stride * i; }
};

unsigned int ArrF::get(int i)
{
    return *(unsigned int*)(data + stride * i) & maskTable[maskIdx];
}

// @ 0x004679b0
// Primitive entry (0x14 bytes): primitive type, first index, end index.
struct ArrG {
    int idx;
    int pad1;
    int b;
    int a;
    int pad10;
    int f();
};

int ArrG::f()
{
    if (idx <= 0 || idx >= 10)
        return 0;
    if (idx == 9)
        return 1;
    int v9 = a - b;
    int t10 = tableA[idx];
    int cap = tableB[idx];
    return (v9 + t10) / cap;
}

// ---------------------------------------------------------------------------
// @ 0x00466e20
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Vec2 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};

struct sp_vector_allocator { sp_vector_allocator() {} };

// vectors of the export accumulator: size()/erase()/push_back() are out of line
struct VecU32 {
    unsigned int* mpBegin; unsigned int* mpEnd; unsigned int* mpCapacity; unsigned int mAlloc[2];
    unsigned int* erase(unsigned int* first, unsigned int* last);   // 0x004769b0
    unsigned int size();                                            // 0x004746a0
    void push_back(const unsigned int& v);                          // 0x00454860
    void clear() { erase(mpBegin, mpEnd); }
    unsigned int& operator[](unsigned int i) { unsigned int* p = mpBegin + i; return *p; }
};
struct VecV3 {
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCapacity; unsigned int mAlloc[2];
    Vec3* erase(Vec3* first, Vec3* last);                           // 0x0050f740
    unsigned int size();                                            // 0x004737f0
    void push_back(const Vec3& v);                                  // 0x004739d0
    void clear() { erase(mpBegin, mpEnd); }
    Vec3& operator[](unsigned int i) { Vec3* p = mpBegin + i; return *p; }
};
struct VecV2 {
    Vec2* mpBegin; Vec2* mpEnd; Vec2* mpCapacity; unsigned int mAlloc[2];
    Vec2* erase(Vec2* first, Vec2* last);                           // 0x00530c80
    unsigned int size();                                            // 0x00474050
    void push_back(const Vec2& v);                                  // 0x00473f30
    void clear() { erase(mpBegin, mpEnd); }
    Vec2& operator[](unsigned int i) { Vec2* p = mpBegin + i; return *p; }
};
struct VecInt {
    int* mpBegin; int* mpEnd; int* mpCapacity; unsigned int mAlloc;
    VecInt(const sp_vector_allocator& a);                           // 0x00540470
    ~VecInt();                                                      // 0x004e1bf0
    unsigned int size() { return mpEnd - mpBegin; }
    int& operator[](unsigned int i) { int* p = mpBegin + i; return *p; }
};

struct FormatEntry { short elts; short stream; };
struct FormatVec {
    FormatEntry* mpBegin; FormatEntry* mpEnd;
    FormatEntry& operator[](unsigned int i) { FormatEntry* p = mpBegin + i; return *p; }
};
struct StreamVec {
    ArrF* mpBegin; ArrF* mpEnd;
    bool empty();                                                   // 0x00526430
};
struct Section {                  // 0x8c bytes
    ArrF indices;                 // +0x00
    unsigned int pad10;
    FormatVec mFormat;            // +0x14
    unsigned int pad1c[(0x44 - 0x1c) / 4];
    StreamVec mStreams;           // +0x44
    unsigned int pad4c[(0x8c - 0x4c) / 4];
    bool HasStreams() { return !mStreams.empty(); }
};
struct SectionVec {
    Section* mpBegin; Section* mpEnd;
    int size();                                                     // 0x00475410
};
struct MeshEntry {                // 0x20 bytes
    unsigned int pad0[4];
    ArrF stream;                  // +0x10
};
struct Model {
    unsigned int pad0[2];
    MeshEntry* entries;           // +0x08
    unsigned int pad0c[4];
    SectionVec mSections;         // +0x1c
    unsigned int pad24[3];
    ArrG* mPrims;                 // +0x30
};
struct ModelVec {
    Model** mpBegin; Model** mpEnd;
    unsigned int size() const { return mpEnd - mpBegin; }
    Model*& operator[](unsigned int i) const { Model** p = mpBegin + i; return *p; }
};

bool __cdecl FUN_0071ded0(Model* m, int n, int* idx, int* fmts, int a, int* counts, int b);
int __cdecl FindFormatEntry(Model* m, int section, int elts);          // 0x0071e040
void __cdecl FindPrimitives(Model* m, VecInt* out, int section, int type, int aux);  // 0x0071ee10

struct NodeBone {
    int nidx; int bidx;
    NodeBone(int n, int b) : nidx(n), bidx(b) {}
};
struct cExportHelper {
    void ExportMeshAdd(NodeBone nb, float* pos, float* normals, float* uvs, unsigned int* indices,
                       unsigned int numVerts, unsigned int numFaces, int posStride, int normStride,
                       int uvStride);                              // 0x00500ef0
};

struct MeshAccum {
    VecU32 mIndices;              // +0x00
    VecV3 mPositions;             // +0x14
    VecV3 mNormals;               // +0x28
    VecV2 mUVs;                   // +0x3c
    void Export(cExportHelper* helper, const ModelVec& models);
};

void MeshAccum::Export(cExportHelper* helper, const ModelVec& models)
{
    mIndices.clear();
    mPositions.clear();
    mNormals.clear();
    mUVs.clear();
    int total = 0;
    int vert = 0;
    for (unsigned int i = 0, n = models.size(); i < n; i++) {
        int count = 0;
        Model* model = models[i];
        int fmts[4] = { 1, 2, 8, 8 };
        int counts[4] = { 3, 3, 2, 2 };
        int idx[4];
        FUN_0071ded0(model, 4, idx, fmts, 0, counts, 0);
        ArrF* sPos = &model->entries[idx[0]].stream;
        ArrF* sNrm = &model->entries[idx[1]].stream;
        ArrF* sTan = &model->entries[idx[2]].stream;
        ArrF* sUV = &model->entries[idx[3]].stream;
        for (int j = 0, nSec = model->mSections.size(); j < nSec; j++) {
            Section* sec = &model->mSections.mpBegin[j];
            int fPos = FindFormatEntry(model, j, idx[0]);
            int fNrm = FindFormatEntry(model, j, idx[1]);
            int fTan = FindFormatEntry(model, j, idx[2]);
            int fUV = FindFormatEntry(model, j, idx[3]);
            VecInt prims((sp_vector_allocator()));
            FindPrimitives(model, &prims, j, 4, -1);
            for (int k = 0, nPrims = prims.size(); k < nPrims; k++) {
                ArrG* prim = &model->mPrims[prims[k]];
                int nTri = prim->f();
                int start = prim->b;
                if (!sec->HasStreams()) {
                    for (int t = 0; t < nTri; t++) {
                        unsigned int i0 = sec->indices.getI(start++);
                        unsigned int i1 = sec->indices.getI(start++);
                        unsigned int i2 = sec->indices.getI(start++);
                        mPositions.push_back(*(Vec3*)sPos->atI(i0));
                        mPositions.push_back(*(Vec3*)sPos->atI(i1));
                        mPositions.push_back(*(Vec3*)sPos->atI(i2));
                        mNormals.push_back(*(Vec3*)sNrm->atI(i0));
                        mNormals.push_back(*(Vec3*)sNrm->atI(i1));
                        mNormals.push_back(*(Vec3*)sNrm->atI(i2));
                        mUVs.push_back(*(Vec2*)sUV->atI(i0));
                        mUVs.push_back(*(Vec2*)sUV->atI(i1));
                        mUVs.push_back(*(Vec2*)sUV->atI(i2));
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        count += 3;
                    }
                } else {
                    ArrF* tPos = &sec->mStreams.mpBegin[sec->mFormat[fPos].stream];
                    ArrF* tNrm = &sec->mStreams.mpBegin[sec->mFormat[fNrm].stream];
                    ArrF* tUV = &sec->mStreams.mpBegin[sec->mFormat[fUV].stream];
                    for (int t = 0; t < nTri; t++) {
                        unsigned int i0 = sec->indices.get(start++);
                        unsigned int i1 = sec->indices.get(start++);
                        unsigned int i2 = sec->indices.get(start++);
                        unsigned int p0 = tPos->get(i0);
                        unsigned int p1 = tPos->get(i1);
                        unsigned int p2 = tPos->get(i2);
                        unsigned int n0 = tNrm->get(i0);
                        unsigned int n1 = tNrm->get(i1);
                        unsigned int n2 = tNrm->get(i2);
                        unsigned int u0 = tUV->get(i0);
                        unsigned int u1 = tUV->get(i1);
                        unsigned int u2 = tUV->get(i2);
                        mPositions.push_back(*(Vec3*)sPos->atI(p0));
                        mPositions.push_back(*(Vec3*)sPos->at(p1));
                        mPositions.push_back(*(Vec3*)sPos->at(p2));
                        mNormals.push_back(*(Vec3*)sNrm->at(n0));
                        mNormals.push_back(*(Vec3*)sNrm->at(n1));
                        mNormals.push_back(*(Vec3*)sNrm->at(n2));
                        mUVs.push_back(*(Vec2*)sUV->at(u0));
                        mUVs.push_back(*(Vec2*)sUV->at(u1));
                        mUVs.push_back(*(Vec2*)sUV->at(u2));
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        count += 3;
                    }
                }
            }
        }
        total += count;
    }
    for (int u = 0, nUV = mUVs.size(); u < nUV; u++) {
        Vec2& uv = mUVs.mpBegin[u];
        if (uv[1] <= 0.0f)
            uv[1] += 1.0f;
    }
    int bidx = -1;
    int nidx = 0;
    helper->ExportMeshAdd(NodeBone(nidx, bidx), &mPositions[0].x, &mNormals[0].x, &mUVs[0].x, &mIndices[0],
                          mPositions.size(), mIndices.size() / 3, 0xc, 0xc, 8);
}
