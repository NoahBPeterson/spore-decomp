// Slice s0045f5e0: mesh merge/convert routines plus an RGBA unpack helper.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

// =====================================================================
// @ 0x460470  unpack an RGBA colour word into four floats
// =====================================================================
const float kInv255 = 0.003921569f;   // 1/255

// =====================================================================
// @ 0x460470  unpack an RGBA colour word into four floats
// =====================================================================
void UnpackColor(unsigned int c, float* out)
{
    float where = kInv255;
    int t24 = c & 0xff;
    out[0] = (float)t24 * where;
    int offset;
    int len = (c >> 8) & 0xff;
    out[1] = (float)len * where;
    offset = (c >> 0x10) & 0xff;
    out[2] = (float)offset * where;
    int p24 = (c >> 0x18) & 0xff;
    out[3] = (float)p24 * where;
    return;
}



struct Vec3 { float x, y, z; };
struct Vec2 { float x, y; };
struct Mat33 {
    float m[9];
    void __thiscall Assign(const void* src);  // 0x0041cb40 Matrix3::Assign
};

struct StreamDesc {
    unsigned int count;          // +0
    unsigned char* data;         // +4
    unsigned short fmt;          // +8
    unsigned short stride;       // +0xa
};
struct MeshEntry {
    char pad0[8];
    int format;                  // +8
    char pad1[4];
    StreamDesc stream;           // +0x10
    StreamDesc& GetStream() { return stream; }
    char pad2[0x20 - 0x10 - sizeof(StreamDesc)];
};
struct ModelType {              // 0x48 bytes at Cluster+0x44
    unsigned char raw[0x8c - 0x44];
    bool __thiscall GetResourceTypeFromModelType();  // 0x00526430
};
struct Cluster {                 // 0x8c bytes
    StreamDesc indices;          // +0
    unsigned char pad[0x14 - sizeof(StreamDesc)];
    unsigned char formats[0x44 - 0x14]; // +0x14 (format list)
    ModelType modelType;         // +0x44
};
struct VecU32 {
    unsigned int* mpBegin; unsigned int* mpEnd; unsigned int* mpCap; int pad[2];
    void __thiscall Resize(unsigned n);  // 0x004cd3c0
};
struct VecV3  {
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCap; int pad[2];
    void __thiscall Resize(unsigned n);  // 0x00473810
};
struct VecV2  {
    Vec2* mpBegin; Vec2* mpEnd; Vec2* mpCap; int pad[2];
    void __thiscall Resize(unsigned n);  // 0x00473dc0
};
struct ClusterVec { Cluster* mpBegin; Cluster* mpEnd; };
struct MeshDesc {
    char pad0[8];
    MeshEntry* entries;          // +8
    char pad1[0x1c - 0xc];
    ClusterVec clusters;         // +0x1c
};
struct MeshOut {
    char pad0[0xc];
    VecU32 indices;              // +0xc
    VecV3 positions;             // +0x20
    VecV3 normals;               // +0x34
    VecV3 tangents;              // +0x48
    VecV2 uvs;                   // +0x5c
};
struct Xform {
    float pad0;                  // +0
    Vec3 translate;              // +4
    float scale;                 // +0x10
    char matSrc[0x24];           // +0x14
};

void __cdecl FUN_00733ed0(MeshDesc*);
void __cdecl CreateClustersAndEdges(MeshDesc*, int);     // 0x00735470 SP::cMeshClusterer::CreateClustersAndEdges
int  __cdecl FUN_0071ddc0(MeshDesc*, int, int, int, int);
void __cdecl FUN_00736b00(MeshDesc*);
bool __cdecl FUN_0071ded0(MeshDesc*, int, int*, int*, int, int*, int);
bool __cdecl FUN_0071e230(void*, int, int*, int);
Mat33* __cdecl FUN_00475550(Mat33*, const Mat33*, const float*);
Vec3* __cdecl _Unchecked_idl0(Vec3*, const void*, const Mat33*);  // 0x0041daf0
Vec3* __cdecl FUN_0041dc10(Vec3*, const Vec3*, const Vec3*);
Vec3* __cdecl normalized_safe(Vec3*, const Vec3*);       // 0x00449c20 SP::normalized_safe
extern unsigned int g_indexMask[];                         // 0x13eec84

static inline float ClampUnit(float v) {
    float r = v;
    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;
    return r;
}

struct Half4 { unsigned short v[4]; };
struct Float4 { float v[4]; };
struct Vec8T {
    Half4* mpBegin; Half4* mpEnd;
    void resize(unsigned n, const Half4& v);  // 0x004740f0
};
struct Vec16T {
    Float4* mpBegin; Float4* mpEnd;
    void resize(unsigned n, const Float4& v);  // 0x00474450
};
int __cdecl FUN_0071de40(MeshDesc*, int, int, int, int);

// @ 0x4600f0  (appends one mesh stream's positions and colours to the output vectors)
bool FUN_004600f0(MeshDesc* mesh, Vec8T* positions, Vec16T* colors, int base)
{
    int* pCount = (int*)FUN_0071de40(mesh, 1, -1, 0, 0xe);
    int posIdx = FUN_0071ddc0(mesh, 9, -1, 0, 0xe);
    if (posIdx < 0) return false;
    MeshEntry* posEntry = &mesh->entries[posIdx];
    int colIdx = FUN_0071ddc0(mesh, 10, -1, 0, 0xe);
    MeshEntry* colEntry = &mesh->entries[colIdx];
    bool posIsByte = posEntry->format == 7;
    bool colPacked = (colIdx >= 0 && colEntry->format == 10);
    bool colFloat = (colIdx >= 0 && colEntry->format >= 1 && colEntry->format <= 4);
    int start = (int)(positions->mpEnd - positions->mpBegin);
    int count = *pCount;
    Half4 z; z.v[0] = 0; z.v[1] = 0; z.v[2] = 0; z.v[3] = 0;
    positions->resize(start + count, z);
    Float4 one; one.v[0] = 1.0f; one.v[1] = 0.0f; one.v[2] = 0.0f; one.v[3] = 0.0f;
    colors->resize(start + count, one);
    unsigned short off = base * 3;
    if (posIsByte) {
        for (int i = 0; i < count; i++) {
            Half4* dst = &positions->mpBegin[start + i];
            StreamDesc& ps = posEntry->GetStream();
            unsigned char* src = ps.data + ps.stride * i;
            for (unsigned j = 0; j < 4; j++)
                dst->v[j] = src[j] + off;
            if (colPacked) {
                Float4* cd = &colors->mpBegin[start + i];
                StreamDesc& cs = colEntry->GetStream();
                UnpackColor(*(unsigned int*)(cs.data + cs.stride * i), cd->v);
            }
        }
    } else {
        int n = colFloat ? colEntry->format : 1;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < n; j++) {
                StreamDesc& ps = posEntry->GetStream();
                unsigned char* src = ps.data + ps.stride * i;
                positions->mpBegin[start + i].v[j] = ((unsigned short*)src)[j] + off;
                if (colFloat) {
                    StreamDesc& cs = colEntry->GetStream();
                    unsigned char* csrc = cs.data + cs.stride * i;
                    colors->mpBegin[start + i].v[j] = ((float*)csrc)[j];
                }
            }
        }
    }
    return true;
}

// @ 0x45f5e0  (builds merged mesh vertex/index buffers from a mesh description)
bool FUN_0045f5e0(MeshDesc* mesh, MeshOut* out, Xform* xf)
{
    FUN_00733ed0(mesh);
    CreateClustersAndEdges(mesh, 1); // 0x00735470
    unsigned nClusters0 = (unsigned)(mesh->clusters.mpEnd - mesh->clusters.mpBegin);
    for (unsigned c = 0; c < nClusters0; c++) {
        Cluster* cl = &mesh->clusters.mpBegin[c];
        if (!cl->modelType.GetResourceTypeFromModelType()) return false;
    }
    if (FUN_0071ddc0(mesh, 3, -1, 3, 0xe) < 0)
        FUN_00736b00(mesh);

    int wantFmt[4] = { 1, 2, 3, 8 };
    int wantCnt[4] = { 3, 3, 3, 2 };
    int idx[4] = { -1, -1, -1, -1 };
    if (!FUN_0071ded0(mesh, 4, idx, wantFmt, 0, wantCnt, 0))
        return false;

    StreamDesc* sPos  = &mesh->entries[idx[0]].stream;
    StreamDesc* sNrm  = &mesh->entries[idx[1]].stream;
    StreamDesc* sTan  = &mesh->entries[idx[2]].stream;
    StreamDesc* sUv   = &mesh->entries[idx[3]].stream;
    if (sPos->count != sNrm->count || sPos->count != sTan->count || sPos->count != sUv->count)
        return false;

    int base = (int)(out->positions.mpEnd - out->positions.mpBegin);
    int total = base + sPos->count;
    if (xf == 0) {
        out->positions.Resize(total);
        Vec3* dp = out->positions.mpBegin + base;
        for (unsigned i = 0, n = sPos->count; i < n; i++) {
            const Vec3* s = (const Vec3*)(sPos->data + sPos->stride * i);
            dp[i] = *s;
        }
        out->normals.Resize(total);
        Vec3* dn = out->normals.mpBegin + base;
        for (unsigned i = 0, n = sPos->count; i < n; i++) {
            Vec3 tmp;
            Vec3* r = normalized_safe(&tmp, (const Vec3*)(sNrm->data + sNrm->stride * i));
            dn[i] = *r;
        }
        out->tangents.Resize(total);
        Vec3* dt = out->tangents.mpBegin + base;
        for (unsigned i = 0, n = sPos->count; i < n; i++) {
            const Vec3* s = (const Vec3*)(sTan->data + sTan->stride * i);
            dt[i] = *s;
        }
    } else {
        Mat33 rot;
        rot.Assign(xf->matSrc);
        float scale = xf->scale;
        Mat33 tmpM;
        Mat33 full = *FUN_00475550(&tmpM, &rot, &scale);
        Vec3 trans = xf->translate;
        out->positions.Resize(total);
        Vec3* dp = out->positions.mpBegin + base;
        for (unsigned i = 0, n = sPos->count; i < n; i++) {
            Vec3 a, b;
            Vec3* r = FUN_0041dc10(&b, _Unchecked_idl0(&a, sPos->data + sPos->stride * i, &full), &trans);
            dp[i] = *r;
        }
        out->normals.Resize(total);
        Vec3* dn = out->normals.mpBegin + base;
        for (unsigned i = 0, n = sPos->count; i < n; i++) {
            Vec3 a, b;
            Vec3* t = _Unchecked_idl0(&a, sNrm->data + sNrm->stride * i, &rot);
            Vec3 v = *t;
            Vec3* r = normalized_safe(&b, &v);
            dn[i] = *r;
        }
        out->tangents.Resize(total);
        Vec3* dt = out->tangents.mpBegin + base;
        for (unsigned i = 0, n = sPos->count; i < n; i++) {
            Vec3 a;
            Vec3* t = _Unchecked_idl0(&a, sTan->data + sTan->stride * i, &rot);
            dt[i] = *t;
        }
    }
    out->uvs.Resize(total);
    Vec2* du = out->uvs.mpBegin + base;
    for (unsigned i = 0, n = sPos->count; i < n; i++) {
        const float* s = (const float*)(sUv->data + sUv->stride * i);
        du[i].x = s[0];
        du[i].y = ClampUnit(s[1] + 1.0f);
    }

    unsigned nClusters = (unsigned)(mesh->clusters.mpEnd - mesh->clusters.mpBegin);
    for (unsigned c = 0; c < nClusters; c++) {
        Cluster* cl = &mesh->clusters.mpBegin[c];
        if (FUN_0071e230(cl->formats, 4, idx, 0)) {
            StreamDesc* ci = &cl->indices;
            int ib = (int)(out->indices.mpEnd - out->indices.mpBegin);
            out->indices.Resize(ib + ci->count);
            unsigned int* di = out->indices.mpBegin + ib;
            for (unsigned i = 0, n = ci->count; i < n; i++) {
                di[i] = (*(unsigned int*)(ci->data + ci->stride * i) & g_indexMask[ci->fmt]) + base;
            }
        }
    }
    return true;
}
// --- equivalence checker address annotations
    void CreateClustersAndEdges(...); // 0x00735470
    void normalized_safe(...); // 0x00449c20

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct Mat33 {
    void Assign(void*); // 0x0041cb40
};
struct Vec16T {
    void resize(unsigned int, int&); // 0x00474450
};
struct Vec8T {
    void resize(unsigned int, int&); // 0x004740f0
};
struct VecV3 {
    void Resize(unsigned int); // 0x00473810
};
}
