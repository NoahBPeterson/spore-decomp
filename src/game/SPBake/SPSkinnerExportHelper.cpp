// src/game/SPBake/SPSkinnerExportHelper.cpp -- migrated from slice(s) s005002d0, s004ff750 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinnerExportHelper.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPSkinner/cExportHelper.h"
#include <stdio.h>
#include "cSPQuaternion.h"

// ---- items of slice s005002d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
namespace eastl {
struct allocator_s0050_02d0 {};
}
namespace eastl {
template <typename T, typename A = allocator_s0050_02d0>
struct basic_string_s0050_02d0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    struct CtorSprintf {};
    basic_string_s0050_02d0(CtorSprintf, const T* pFormat, ...);   // 0x00472f50 (char)
    ~basic_string_s0050_02d0();                                    // 0x00530670
    const T* c_str() const { return mpBegin; }
};
}
typedef eastl::basic_string_s0050_02d0<char> string8;
template <typename T>
struct SPVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int mAllocator;
    uint size() const { return (uint)(mpEnd - mpBegin); }
    T& operator[](uint i) { return mpBegin[i]; }
    bool empty() const;                                  // 0x00526430 (out of line)
};
struct rwVector3 { float v[3]; rwVector3() {} };
struct rwMatrix33 { float m[9]; rwMatrix33() {} };
struct cSPVector3_s0050_02d0 {
    float v[3];
    cSPVector3_s0050_02d0() { v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; }
    cSPVector3_s0050_02d0(const rwVector3& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
    cSPVector3_s0050_02d0(const cSPVector3_s0050_02d0& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
    const float& operator[](int i) const { return v[i]; }
};
struct cSPMatrix3_s0050_02d0 {
    rwMatrix33 rw;
    cSPMatrix3_s0050_02d0(const rwMatrix33& o) { rw = o; }
};
struct rwQuaternion { float q[4]; rwQuaternion() {} };
struct cSPQuaternion_s0050_02d0 {
    float q[4];
    cSPQuaternion_s0050_02d0(const rwQuaternion& rw);               // 0x00501290
    const float& operator[](int i) const { return q[i]; }
};
struct node {                                            // 0x48 bytes
    cSPVector3_s0050_02d0 p;                                        // +0
    char pad[0x44 - 0xc];
    uint jidx;                                           // +0x44
};
struct bone {                                            // 0x54 bytes
    char pad[0x44];
    bool mIsConnectorBone;                               // +0x44
    char pad2[0x50 - 0x45];
    uint jidx;                                           // +0x50
};
struct export_joint {                                    // 0xd8 bytes
    uint parent_jidx;                                    // +0
    uint nidx;                                           // +4
    uint bidx;                                           // +8
    uint type;                                           // +0xc
    SPVector<uint> child_jidxs;                          // +0x10 (fixed_vector header)
    char pad[0x48 - 0x20];
    cSPVector3_s0050_02d0 abs_p;                                    // +0x48
    cSPMatrix3_s0050_02d0 abs_R;                                    // +0x54
    cSPVector3_s0050_02d0 rel_p;                                    // +0x78
    cSPMatrix3_s0050_02d0 rel_R;                                    // +0x84
    char pad2[0xd8 - 0xa8];
};
struct cMeshVertexRef { uint vertex; uint pad; uint uv; };            // 12 bytes
struct cSubMesh {
    char pad[0x6c];
    SPVector<uint> indices;                              // +0x6c
    char pad2[0x80 - 0x7c];
    SPVector<cMeshVertexRef> verts;                      // +0x80
};
struct cVec2 {
    float x, y;
    cVec2() { x = 0.0f; y = 0.0f; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cMeshData {
    char pad[8];
    cSPVector3_s0050_02d0* mpPositions;                             // +8
    char pad1[0x1c - 0xc];
    cSPVector3_s0050_02d0* mpNormals;                               // +0x1c
    char pad2[0x30 - 0x20];
    SPVector<cVec2> uvs;                                 // +0x30
    char pad3[0x58 - 0x40];
    SPVector<uint> indices;                              // +0x58
    char pad4[0xe4 - 0x68];
    SPVector<cSubMesh*> submeshes;                       // +0xe4
    char pad5[0x10c - 0xf4];
    uint material;                                       // +0x10c
};
struct cSkinWeights { unsigned char bone[4]; float weight[4]; uint pad; };   // 0x14 bytes per vertex
rwQuaternion __cdecl QuaternionFromMatrix33(const cSPMatrix3_s0050_02d0* m, float eps);   // 0x00472b80
rwMatrix33 __cdecl MatrixInverse(const cSPMatrix3_s0050_02d0* m);                           // 0x0041ded0
rwVector3 __cdecl VecTimesMatrix(const cSPVector3_s0050_02d0* v, const cSPMatrix3_s0050_02d0* m);     // 0x0041daf0
rwVector3 __cdecl Vector3_Negate(const cSPVector3_s0050_02d0* v);                          // 0x00422020
cSPQuaternion_s0050_02d0 __cdecl QuatFromAbsMatrix(const cSPMatrix3_s0050_02d0* m);                    // 0x0046d660
void __cdecl TransformPoint(cSPVector3_s0050_02d0* v, node* n);                             // 0x004fc5a0
class cExportHelper {
public:
    void ExportSkeleton();                               // 0x005002d0
    void ExportMeshBegin(uint numSubmeshes, bool ascii); // 0x00500880
    void ExportSubmesh(cMeshData* mesh, cSkinWeights* weights);   // 0x00500920
    void ExportMeshAdd(int nidx, int bidx, float* pos, float* normals, float* uvs, uint* indices,
                       uint numVerts, uint numFaces, int posStride, int normStride, int uvStride);   // 0x00500ef0
    void ExportMeshEnd();                                // 0x00501200

    const wchar_t* mpName;                               // +0x00
    const wchar_t* GetName() const { return mpName; }
    char pad04[0x0c];
    SPVector<node> mNodes;                               // +0x10
    char pad20[4];
    SPVector<bone> mBones;                               // +0x24 (retail)
    char pad34[0x38 - 0x34];
    uint root_nidx;                                      // +0x38
    bool mMoveRootToOrigin;                              // +0x3c
    char pad3d[0x54 - 0x3d];
    SPVector<export_joint> mExportJoints;                // +0x54
    char pad64[0x6c - 0x64];
    FILE* export_mesh_FILE;                              // +0x6c
    bool export_ascii_mesh;                              // +0x70
    uint export_num_meshes;                              // +0x74
    uint export_submesh_idx;                             // +0x78
};
// ---- items of slice s005002d0 end

// @ 0x005001c0
void FUN_005001c0()
{}

// @ 0x005002d0
void cExportHelper::ExportSkeleton()
{
    string8 list(string8::CtorSprintf(), "%ls.xsf", GetName());
    FILE* t2 = fopen(list.c_str(), "w");
    fprintf(t2, "<SKELETON VERSION=\"1000\" NUMBONES=\"%d\">\n", mExportJoints.size());
    for (uint i = 0; i < mExportJoints.size(); ++i) {
        export_joint* v27 = &mExportJoints[i];
        char q55[200];
        switch (v27->type) {
        case 0:
            sprintf(q55, "joint_rootnode_%d", v27->nidx);
            break;
        case 1:
            if (!mBones[v27->bidx].mIsConnectorBone)
                sprintf(q55, "joint_bone_%d", v27->bidx);
            else
                sprintf(q55, "joint_connbone_%d", v27->bidx);
            break;
        case 2:
            sprintf(q55, "joint_eenode_%d", v27->nidx);
            break;
        case 3:
            sprintf(q55, "joint_fakenode_%d", v27->nidx);
            break;
        case 4:
            sprintf(q55, "joint_rigblock_%d", i);
            break;
        }
        fprintf(t2, "\t<BONE ID=\"%d\" NAME=\"%s\" NUMCHILDS=\"%d\">\n", i, q55, v27->child_jidxs.size());
        fprintf(t2, "\t\t<TRANSLATION>%f %f %f</TRANSLATION>\n", v27->rel_p[0], v27->rel_p[1], v27->rel_p[2]);
        cSPQuaternion_s0050_02d0 p18(QuaternionFromMatrix33(&v27->rel_R, 0.0f));
        fprintf(t2, "\t\t<ROTATION>%f %f %f %f</ROTATION>\n", p18[0], p18[1], p18[2], -p18[3]);
        cSPMatrix3_s0050_02d0 v20(MatrixInverse(&v27->abs_R));
        cSPVector3_s0050_02d0 m41(VecTimesMatrix(&v27->abs_p, &v20));
        cSPVector3_s0050_02d0 n16(Vector3_Negate(&m41));
        fprintf(t2, "\t\t<LOCALTRANSLATION>%f %f %f</LOCALTRANSLATION>\n", n16[0], n16[1], n16[2]);
        cSPQuaternion_s0050_02d0 p30 = QuatFromAbsMatrix(&v27->abs_R);
        fprintf(t2, "\t\t<LOCALROTATION>%f %f %f %f</LOCALROTATION>\n", p30[0], p30[1], p30[2], p30[3]);
        fprintf(t2, "\t\t<PARENTID>%d</PARENTID>\n", v27->parent_jidx);
        uint p14;
        for (p14 = 0; p14 < v27->child_jidxs.size(); ++p14)
            fprintf(t2, "\t\t<CHILDID>%d</CHILDID>\n", v27->child_jidxs[p14]);
        fprintf(t2, "\t</BONE>\n");
    }
    fprintf(t2, "</SKELETON>\n");
    fclose(t2);
}

// @ 0x00500ef0
void cExportHelper::ExportMeshAdd(int nidx, int bidx, float* pos, float* normals, float* uvs, uint* indices, uint numVerts, uint numFaces, int posStride, int normStride, int uvStride)
{
    FILE* p31 = export_mesh_FILE;
    uint t13 = numVerts;
    uint q34 = numFaces;
    fprintf(p31,
            "\t<SUBMESH MATERIAL=\"%d\" NUMVERTICES=\"%d\" NUMFACES=\"%d\" NUMLODSTEPS=\"0\" NUMSPRINGS=\"0\" "
            "NUMTEXCOORDS=\"1\">\n",
            export_submesh_idx, t13, q34);
    uint m36 = 0;
    if (!mNodes.empty() || !mBones.empty())
        m36 = (nidx != -1) ? mNodes[nidx].jidx : mBones[bidx].jidx;
    for (uint i = 0; i < t13; ++i) {
        cSPVector3_s0050_02d0 t33(*(cSPVector3_s0050_02d0*)(i * posStride + (char*)pos));
        cSPVector3_s0050_02d0* t4 = (cSPVector3_s0050_02d0*)(i * normStride + (char*)normals);
        cVec2* q7 = (cVec2*)(i * uvStride + (char*)uvs);
        fprintf(p31, "\t\t<VERTEX ID=\"%d\" NUMINFLUENCES=\"%d\">\n", i, 1);
        if (mMoveRootToOrigin)
            TransformPoint(&t33, &mNodes[root_nidx]);
        fprintf(p31, "\t\t\t<POS>%f %f %f</POS>\n", t33[0], t33[1], t33[2]);
        fprintf(p31, "\t\t\t<NORM>%f %f %f</NORM>\n", (*t4)[0], (*t4)[1], (*t4)[2]);
        fprintf(p31, "\t\t\t<TEXCOORD>%f %f</TEXCOORD>\n", (*q7)[0], 1.0 - (*q7)[1]);
        fprintf(p31, "\t\t\t<INFLUENCE ID=\"%d\">1.0</INFLUENCE>\n", m36);
        fprintf(p31, "\t\t</VERTEX>\n");
    }
    for (uint face = 0; face < q34; ++face) {
        fprintf(p31, "\t\t<FACE VERTEXID=\"");
        for (uint c = 0; c < 3; ++c) {
            uint idx = indices[face * 3 + c];
            fprintf(p31, "%d%s", idx, (c == 2) ? "" : " ");
        }
        fprintf(p31, "\"/>\n");
    }
    fprintf(p31, "\t</SUBMESH>\n");
    ++export_submesh_idx;
}
