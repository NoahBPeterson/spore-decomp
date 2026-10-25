// Slice s004ff750: nSPSkinner::cExportHelper export-joint construction and the dummy XSF writer.
//   004ff750  BuildExportJoints            (walk nodes/bones into the export-joint array)
//   004ffc40  BuildExportJointsRecursive   (emit the joints for one bone subtree)
//   005001c0  ExportDummyStaticSkeleton    (write a one-bone .xsf)
#include "types.h"
#include <stdio.h>

typedef unsigned int uint;

namespace eastl {
struct allocator {};
}

// eastl::basic_string<char> with its (empty) allocator member: 0x10 bytes.
template <typename T, typename A = eastl::allocator>
struct basic_string {
    T* mpBegin;                                        // +0x00
    T* mpEnd;                                          // +0x04
    T* mpCapacity;                                     // +0x08
    A mAllocator;                                      // +0x0c
    struct CtorSprintf {};
    basic_string(CtorSprintf tag, const T* pFormat, ...);  // 0x00472f50
    ~basic_string();                                   // 0x00530670
    const T* c_str() const { return mpBegin; }
};
typedef basic_string<char> string8;

// Three-pointer vector header (the containers in this object are eastl fixed_vectors whose
// pointer pair sits at +0/+4 and whose inline storage follows).
template <typename T>
struct SPVector {
    T* mpBegin;                                        // +0x00
    T* mpEnd;                                          // +0x04
    T* mpCapacity;                                     // +0x08
    void* mpAllocator;                                 // +0x0c
    uint size() const { return (uint)(mpEnd - mpBegin); }
    T& operator[](uint i) { return mpBegin[i]; }
    void erase(T* first, T* last);                     // 0x00501910
    void reserve(uint n);                              // 0x005015f0
    void resize(uint n);                               // 0x005014e0
    void push_back(const T& v);                        // 0x00422380
};

struct cSPVector3 {
    float x, y, z;                                     // +0x00
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};

struct cSPMatrix3 {
    float m[9];                                        // +0x00
    cSPMatrix3() {}
};

// eastl::fixed_vector<uint,16>-compatible header: the pointer pair at +0/+4 is all the
// joint-construction code reads; the inline node-child storage fills the rest.
struct node_children {
    uint* mpBegin;                                     // +0x00
    uint* mpEnd;                                       // +0x04
    uint* mpCapacity;                                  // +0x08
    char pad_0c[0x38 - 0x0c];
    uint size() const { return (uint)(mpEnd - mpBegin); }
    uint& operator[](uint i) { return mpBegin[i]; }
    void push_back(const uint& v);                     // 0x00422380
};

struct node {                                          // 0x48 bytes
    cSPVector3 p;                                      // +0x00
    node_children children;                            // +0x0c
    uint jidx;                                         // +0x44
};

struct bone {                                          // 0x54 bytes
    char pad_00[0x14];
    cSPMatrix3 abs_R;                                  // +0x14
    char pad_38[0x48 - 0x38];
    uint parent_nidx;                                  // +0x48
    uint nidx;                                         // +0x4c
    uint jidx;                                         // +0x50
};

struct export_joint {                                  // 0xd8 bytes
    uint parent_jidx;                                  // +0x00
    uint nidx;                                         // +0x04
    uint bidx;                                         // +0x08
    uint type;                                         // +0x0c
    node_children child_jidxs;                         // +0x10
    cSPVector3 abs_p;                                  // +0x48
    cSPMatrix3 abs_R;                                  // +0x54
    cSPVector3 rel_p;                                  // +0x78
    cSPMatrix3 rel_R;                                  // +0x84
    char pad_a8[0xd8 - 0xa8];
};

class cExportHelper {
public:
    void BuildExportJoints();                          // 0x004ff750
    uint BuildExportJointsRecursive(uint bidx, uint parent_jidx);  // 0x004ffc40
    void ExportDummyStaticSkeleton();                  // 0x005001c0
    const wchar_t* GetName() const { return mpName; }

    const wchar_t* mpName;                             // +0x00
    char pad_04[0x10 - 0x04];
    SPVector<node> mNodes;                             // +0x10
    char pad_20[0x24 - 0x20];
    SPVector<bone> mBones;                             // +0x24
    char pad_34[0x38 - 0x34];
    uint root_nidx;                                    // +0x38
    bool mMoveRootToOrigin;                            // +0x3c
    char pad_3d[0x54 - 0x3d];
    SPVector<export_joint> mExportJoints;              // +0x54
    char pad_64[0x68 - 0x64];
    uint num_export_joints;                            // +0x68
};

extern cSPMatrix3 gDefaultJointRotation;               // 0x015dc3c4

// Reserves N dwords of caller frame (the /Od frame of the original keeps dead scratch slots).
template <int N> inline void ScratchSlots() { uint slots[N]; }

cSPMatrix3 __cdecl Matrix33_Convert(const cSPMatrix3* m);                              // 0x0041ded0
cSPMatrix3 __cdecl Matrix33_Multiply(const cSPMatrix3* a, const cSPMatrix3* b);        // 0x0041de20
cSPVector3 __cdecl VecSubtract(const cSPVector3* a, const cSPVector3* b);              // 0x0041db10
cSPVector3 __cdecl VecTimesMatrix(const cSPVector3* v, const cSPMatrix3* m);           // 0x0041daf0
void __cdecl TransformPoint(cSPVector3* v, node* n);                                   // 0x004fc5a0

// @ 0x004ff750
void cExportHelper::BuildExportJoints()
{
    mExportJoints.erase(mExportJoints.mpBegin, mExportJoints.mpEnd);
    mExportJoints.reserve(mBones.size() * 2);
    num_export_joints = mBones.size() + 1;

    uint jidx = 0;
    mExportJoints.resize(1);
    export_joint* joint = &mExportJoints[0];
    joint->parent_jidx = (uint)-1;
    joint->nidx = root_nidx;
    joint->bidx = (uint)-1;
    joint->type = 0;
    if (mMoveRootToOrigin) {
        cSPVector3 zero(0.0f, 0.0f, 0.0f);
        joint->abs_p = zero;
    } else {
        joint->abs_p = mNodes[root_nidx].p;
    }
    joint->abs_R = gDefaultJointRotation;
    mNodes[root_nidx].jidx = jidx;

    for (uint i = 0; i < mNodes[root_nidx].children.size(); ++i) {
        uint child_nidx = mNodes[root_nidx].children[i];
        uint child_jidx = BuildExportJointsRecursive(child_nidx, jidx);
        mExportJoints[jidx].child_jidxs.push_back(child_jidx);
    }

    for (uint i = 0; i < mExportJoints.size(); ++i) {
        export_joint* j = &mExportJoints[i];
        if (j->parent_jidx == (uint)-1) {
            j->rel_R = gDefaultJointRotation;
            cSPVector3 zero(0.0f, 0.0f, 0.0f);
            j->rel_p = zero;
        } else {
            if (mMoveRootToOrigin)
                TransformPoint(&j->abs_p, &mNodes[root_nidx]);
            export_joint* parent = &mExportJoints[j->parent_jidx];
            cSPMatrix3 inv_parent_R = Matrix33_Convert(&parent->abs_R);
            j->rel_R = Matrix33_Multiply(&j->abs_R, &inv_parent_R);
            cSPVector3 delta = VecSubtract(&j->abs_p, &parent->abs_p);
            cSPMatrix3 inv_parent_R2 = Matrix33_Convert(&parent->abs_R);
            j->rel_p = VecTimesMatrix(&delta, &inv_parent_R2);
        }
    }
}

// @ 0x004ffc40
uint cExportHelper::BuildExportJointsRecursive(uint bidx, uint parent_jidx)
{
    uint nidx = mBones[bidx].parent_nidx;
    uint node_nidx = mBones[bidx].nidx;
    uint jidx = mExportJoints.size();
    mExportJoints.resize(jidx + 1);
    export_joint* joint = &mExportJoints[jidx];
    joint->parent_jidx = parent_jidx;
    joint->nidx = nidx;
    joint->bidx = bidx;
    joint->type = 1;
    joint->abs_p = mNodes[nidx].p;
    joint->abs_R = mBones[bidx].abs_R;
    mBones[bidx].jidx = jidx;

    int nchildren = (int)mNodes[node_nidx].children.size() - 1;
    if (nchildren == 0) {
        uint child_jidx = mExportJoints.size();
        mExportJoints.resize(child_jidx + 1);
        export_joint* child = &mExportJoints[child_jidx];
        child->parent_jidx = jidx;
        child->nidx = node_nidx;
        child->bidx = (uint)-1;
        child->type = 3;
        child->abs_p = mNodes[node_nidx].p;
        child->abs_R = mExportJoints[jidx].abs_R;
        mExportJoints[jidx].child_jidxs.push_back(child_jidx);
        mNodes[node_nidx].jidx = child_jidx;
    } else if (nchildren == 1) {
        nchildren = 1;
        for (uint i = 0; i < mNodes[node_nidx].children.size(); ++i) {
            uint child_bidx = mNodes[node_nidx].children[i];
            if (mBones[child_bidx].parent_nidx == node_nidx) {
                uint child_jidx = BuildExportJointsRecursive(child_bidx, jidx);
                mExportJoints[jidx].child_jidxs.push_back(child_jidx);
                mNodes[node_nidx].jidx = child_jidx;
            }
        }
    } else {
        uint fan_jidx = mExportJoints.size();
        mExportJoints.resize(fan_jidx + 1);
        export_joint* fan = &mExportJoints[fan_jidx];
        fan->parent_jidx = jidx;
        fan->nidx = node_nidx;
        fan->bidx = (uint)-1;
        fan->type = 2;
        fan->abs_p = mNodes[node_nidx].p;
        fan->abs_R = mExportJoints[jidx].abs_R;
        mExportJoints[jidx].child_jidxs.push_back(fan_jidx);
        mNodes[node_nidx].jidx = fan_jidx;
        for (uint i = 0; i < mNodes[node_nidx].children.size(); ++i) {
            uint child_bidx = mNodes[node_nidx].children[i];
            if (mBones[child_bidx].parent_nidx == node_nidx) {
                uint child_jidx = BuildExportJointsRecursive(child_bidx, fan_jidx);
                mExportJoints[fan_jidx].child_jidxs.push_back(child_jidx);
            }
        }
    }
    return jidx;
}

// @ 0x005001c0
void cExportHelper::ExportDummyStaticSkeleton()
{
    string8 path(string8::CtorSprintf(), "%ls.xsf", GetName());
    FILE* f = fopen(path.c_str(), "w");
    fprintf(f, "<SKELETON VERSION=\"1000\" NUMBONES=\"1\">\n");
    fprintf(f, "\t<BONE ID=\"0\" NAME=\"root\" NUMCHILDS=\"0\">\n");
    fprintf(f, "\t\t<TRANSLATION>0.000000 0.000000 0.000000</TRANSLATION>\n");
    fprintf(f, "\t\t<ROTATION>0.000000 0.000000 0.000000 1.000000</ROTATION>\n");
    fprintf(f, "\t\t<LOCALTRANSLATION>0.000000 0.000000 0.000000</LOCALTRANSLATION>\n");
    fprintf(f, "\t\t<LOCALROTATION>0.000000 0.000000 0.000000 1.000000</LOCALROTATION>\n");
    fprintf(f, "\t\t<PARENTID>-1</PARENTID>\n");
    fprintf(f, "\t</BONE>\n");
    fprintf(f, "</SKELETON>\n");
    fclose(f);
    ScratchSlots<3>();
}
