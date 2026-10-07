// Slice s0045c350: Collada export writers built on the string writer FUN_0045cd90,
// plus a date formatter.  /Od /Ob1 /MD /Gy /TP.
#include "types.h"

// ---- out-of-slice / masked callees ----
extern "C" int Sprintf8(char* buf, const char* fmt, ...);        // 0x938470
extern "C" void Sprintf8V(char* buf, unsigned int n, const char* fmt, void* args); // 0x938400 used by ResetAndFormat
extern "C" void WriterFmt(int out, const char* fmt, ...);        // 0x45cd90 (defined below)
void WriterStr(int out, const char* s);                          // 0x45cd40 (defined below)
void WriteVec3Array(int out, const char* name, const float* data, unsigned int count);   // 0x45ce80
void WriteVec2Array(int out, const char* name, const float* data, unsigned int count);   // 0x45cf40
void WriteNameArray(int out, const char* name, const int* data, unsigned int count);     // 0x45cfe0

// =====================================================================
// writer object: vtbl slot 0x38 = Write(ptr, len)
// =====================================================================
struct IByteSink {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual unsigned char Write(const char* p, int len);   // +0x38 (slot 14)
};

// =====================================================================
// @ 0x45cd40  write a NUL-terminated string through the sink
// =====================================================================
void WriterStr(int out, const char* s)
{
    const char* p = s;
    const char* start = p + 1;
    char c;
    do {
        c = *p++;
    } while (c != 0);
    int len = (int)(p - start);
    ((IByteSink*)out)->Write(s, len);
    return;
}

// =====================================================================
// BigStr: SSO string with inline buffer at +0x14 (used by WriterFmt)
// =====================================================================
struct BigStr {
    char* begin;
    char* end;
    char* cap;
    char  pad[8];
    char  buf[0x300];
    void  Ctor();                                   // 0x45d6f0
    void  ResetAndFormat(const char* fmt, void* args); // 0x45da50
    void  ReleaseHeap();                            // 0x429300
};

// =====================================================================
// @ 0x45cd90  formatted write through the sink (varargs)
// =====================================================================
int WriterFmtSink(int out, const char* fmt, ...)
{
    BigStr s;
    s.Ctor();
    void* args = (void*)(&fmt + 1);
    s.ResetAndFormat(fmt, args);
    unsigned char r = ((IByteSink*)out)->Write(s.begin, (int)(s.end - s.begin));
    s.ReleaseHeap();
    return r;
}

// =====================================================================
// @ 0x45ce20  format an EA::DateTime as an ISO-8601 UTC timestamp
// =====================================================================
struct DateTime {
    uint32_t mData[3];
    DateTime(int timeFrame);       // 0x92e3d0 thiscall
    int GetParameter(int which);   // 0x92df80 thiscall
};

void FormatDate(char* out, DateTime* t)
{
    Sprintf8(out, "%04d-%02d-%02dT%02d:%02d:%02dZ",
             t->GetParameter(1), t->GetParameter(2), t->GetParameter(6),
             t->GetParameter(8), t->GetParameter(9), t->GetParameter(10));
    return;
}

// =====================================================================
// @ 0x45ce80  write a Vector3 float array source block
// =====================================================================
void WriteVec3Array(int out, const char* name, const float* data, unsigned int count)
{
    WriterFmt(out, "      <source id=\"%s\">\n        <float_array id=\"%s-array\" count=\"%d\">\n          ",
              name, name, count * 3);
    for (unsigned int i = 0; i < count; i = i + 1) {
        WriterFmt(out, "%f %f %f ", data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
    }
    WriterFmt(out,
        "\n        </float_array>\n        <technique_common>\n          <accessor source=\"#%s-array\" count=\"%d\" stride=\"3\">\n            <param name=\"X\" type=\"float\"/>\n            <param name=\"Y\" type=\"float\"/>\n            <param name=\"Z\" type=\"float\"/>\n          </accessor>\n        </technique_common>\n      </source>\n",
        name, count);
    return;
}

// =====================================================================
// @ 0x45cf40  write a Vector2 float array source block
// =====================================================================
void WriteVec2Array(int out, const char* name, const float* data, unsigned int count)
{
    WriterFmt(out, "      <source id=\"%s\">\n        <float_array id=\"%s-array\" count=\"%d\">\n          ",
              name, name, count << 1);
    for (unsigned int i = 0; i < count; i = i + 1) {
        WriterFmt(out, "%f %f ", data[i * 2], data[i * 2 + 1]);
    }
    WriterFmt(out,
        "\n        </float_array>\n        <technique_common>\n          <accessor source=\"#%s-array\" count=\"%d\" stride=\"2\">\n            <param name=\"S\" type=\"float\"/>\n            <param name=\"T\" type=\"float\"/>\n          </accessor>\n        </technique_common>\n      </source>\n",
        name, count);
    return;
}

// =====================================================================
// @ 0x45cfe0  write a bone-name (Name_array) source block
// =====================================================================
void WriteNameArray(int out, const char* name, const int* data, unsigned int count)
{
    WriterFmt(out, "    <source id=\"%s\">\n      <Name_array id=\"%s-array\" count=\"%d\">\n        ",
              name, name, count);
    for (unsigned int i = 0; i < count; i = i + 1) {
        WriterFmt(out, "%s%d ", data[i], i);
    }
    WriterFmt(out,
        "\n      </Name_array>\n      <technique_common>\n        <accessor source=\"#%s-array\" count=\"%d\" stride=\"1\">\n          <param name=\"JOINT\" type=\"Name\"/>\n        </accessor>\n      </technique_common>\n    </source>\n",
        name, count);
    return;
}

// =====================================================================
// @ 0x45d060  write the inverse-bind-pose matrix array  (PARTIAL)
// =====================================================================
void WriteInvBindPose(int out, const char* name, const void* mats, unsigned int count)
{
    (void)out; (void)name; (void)mats; (void)count;
    return;
}

// =====================================================================
// @ 0x45c350  top-level Collada scene writer
// =====================================================================
void WriteWeightArray(int out, const char* name, const void* data, unsigned int count);   // 0x45d2c0
void WriteJointNodes(int out, const void* names, const void* parents, const void* xforms, unsigned int count);   // 0x45d3b0

template <typename T>
struct ExportVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T* data() { return mpBegin; }
    T& operator[](unsigned int i) { return mpBegin[i]; }
};
struct ExportString16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    const wchar_t* c_str() const { return mpBegin; }
};
struct ExportVec2 { float x, y; };
struct ExportVec3 { float x, y, z; };
struct ExportVec4 { float x, y, z, w; };
struct ExportMatrix4 { float m[16]; };
struct ExportBoneIndices { int16_t j[4]; };

struct cColladaExporter {
    ExportString16 mName;                        // +0x00
    ExportVector<ExportVec3> mPositions;         // +0x10
    ExportVector<ExportVec3> mNormals;           // +0x24
    ExportVector<ExportVec2> mTexCoords;         // +0x38
    ExportVector<ExportVec3> mTangents;          // +0x4C
    ExportVector<ExportVec3> mBitangents;        // +0x60
    ExportVector<ExportBoneIndices> mBoneIndices; // +0x74
    ExportVector<ExportVec4> mBoneWeights;       // +0x88
    ExportVector<int> mPosIndices;               // +0x9C
    ExportVector<int> mNormalIndices;            // +0xB0
    ExportVector<int> mTexIndices;               // +0xC4
    ExportVector<const char*> mJointNames;       // +0xD8
    ExportVector<int> mJointParents;             // +0xEC
    ExportVector<int> mUnused100;                // +0x100
    ExportVector<ExportMatrix4> mInvBindPoses;   // +0x114
    ExportVector<ExportMatrix4> mJointXforms;    // +0x128

    bool Write(int out);
};

// Local names are chosen for the /Od slot order (cl orders locals by a hash of the name):
// v_other = date string, v_n25 = current time, v_p36/v_n3/v_k = the three loop counters.
bool cColladaExporter::Write(int out)
{
    DateTime v_n25(1);
    char v_other[64];
    unsigned int v_p36;
    unsigned int v_n3;
    unsigned int v_k;
    FormatDate(v_other, &v_n25);
    WriterFmt(out, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<COLLADA xmlns=\"http://www.collada.org/2005/11/COLLADASchema\" version=\"1.4.1\">\n\n<asset>\n  <created>%s</created>\n  <modified>%s</modified>\n  <up_axis>Z_UP</up_axis>\n</asset>\n\n",
              v_other, v_other);
    WriterFmt(out, "<library_images>\n  <image id=\"diffuse-image\" name=\"diffuse\">\n    <init_from>./%ls__diffuse.tga</init_from>\n  </image>\n  <image id=\"normal-image\" name=\"normal\">\n    <init_from>./%ls__normal.tga</init_from>\n  </image>\n  <image id=\"specular-image\" name=\"specular\">\n    <init_from>./%ls__specular.tga</init_from>\n  </image>\n</library_images>\n\n",
              mName.c_str(), mName.c_str(), mName.c_str());
    WriterFmt(out, "<library_materials>\n  <material id=\"Asset_Material\">\n    <instance_effect url=\"#Asset-fx\"/>\n  </material>\n</library_materials>\n\n");
    WriterFmt(out,
        "<library_effects>\n  <effect id=\"Asset-fx\">\n    <profile_COMMON>\n"
        "      <newparam sid=\"diffuse-surface\">\n        <surface type=\"2D\">\n          <init_from>diffuse-image</init_from>\n          <format>A8R8G8B8</format>\n        </surface>\n      </newparam>\n"
        "      <newparam sid=\"diffuse-sampler\">\n        <sampler2D>\n          <source>diffuse-surface</source>\n          <minfilter>LINEAR_MIPMAP_LINEAR</minfilter>\n          <magfilter>LINEAR</magfilter>\n        </sampler2D>\n      </newparam>\n"
        "      <newparam sid=\"normal-surface\">\n        <surface type=\"2D\">\n          <init_from>normal-image</init_from>\n          <format>A8R8G8B8</format>\n        </surface>\n      </newparam>\n"
        "      <newparam sid=\"normal-sampler\">\n        <sampler2D>\n          <source>normal-surface</source>\n          <minfilter>LINEAR_MIPMAP_LINEAR</minfilter>\n          <magfilter>LINEAR</magfilter>\n        </sampler2D>\n      </newparam>\n"
        "      <newparam sid=\"specular-surface\">\n        <surface type=\"2D\">\n          <init_from>specular-image</init_from>\n          <format>A8</format>\n        </surface>\n      </newparam>\n"
        "      <newparam sid=\"specular-sampler\">\n        <sampler2D>\n          <source>specular-surface</source>\n          <minfilter>LINEAR_MIPMAP_LINEAR</minfilter>\n          <magfilter>LINEAR</magfilter>\n        </sampler2D>\n      </newparam>\n"
        "      <technique sid=\"common\">\n        <phong>\n"
        "          <emission><color>0 0 0 1</color></emission>\n"
        "          <ambient><color>0 0 0 1</color></ambient>\n"
        "          <diffuse><texture texture=\"diffuse-sampler\" texcoord=\"TEX0\"/></diffuse>\n"
        "          <specular><texture texture=\"specular-sampler\" texcoord=\"TEX0\"/></specular>\n"
        "          <shininess><float>80</float></shininess>\n"
        "          <reflective><color>0 0 0 1</color></reflective>\n"
        "          <reflectivity><float>0</float></reflectivity>\n"
        "          <transparent><color>0 0 0 1</color></transparent>\n"
        "          <transparency><float>1</float></transparency>\n"
        "          <index_of_refraction><float>0</float></index_of_refraction>\n"
        "        </phong>\n        <extra>\n          <technique profile=\"FCOLLADA\">\n            <bump>\n"
        "              <texture texture=\"normal-sampler\" texcoord=\"TEX0\">\n                <extra>\n                  <technique profile=\"MAYA\">\n"
        "                    <wrapU>1</wrapU>\n                    <wrapV>1</wrapV>\n"
        "                    <mirrorU>0</mirrorU>\n                    <mirrorV>0</mirrorV>\n"
        "                    <coverageU>1</coverageU>\n                    <coverageV>1</coverageV>\n"
        "                    <translateFrameU>0</translateFrameU>\n                    <translateFrameV>0</translateFrameV>\n"
        "                    <rotateFrame>0</rotateFrame>\n                    <stagger>0</stagger>\n                    <fast>0</fast>\n"
        "                    <repeatU>1</repeatU>\n                    <repeatV>1</repeatV>\n"
        "                    <offsetU>0</offsetU>\n                    <offsetV>0</offsetV>\n"
        "                    <rotateUV>0</rotateUV>\n                    <noiseU>0</noiseU>\n                    <noiseV>0</noiseV>\n"
        "                    <blend_mode>NONE</blend_mode>\n                  </technique>\n"
        "                  <technique profile=\"MAX3D\">\n                    <amount>0.1</amount>\n                    <bumpInterp>1</bumpInterp>\n                  </technique>\n"
        "                </extra>\n              </texture>\n            </bump>\n          </technique>\n        </extra>\n      </technique>\n"
        "    </profile_COMMON>\n  </effect>\n</library_effects>\n\n");
    WriterFmt(out, "<library_geometries>\n  <geometry id=\"mesh\" name=\"mesh\">\n    <mesh>\n", v_other, v_other);
    WriteVec3Array(out, "position", (const float*)mPositions.data(), mPositions.size());
    WriteVec3Array(out, "normal", (const float*)mNormals.data(), mNormals.size());
    WriteVec2Array(out, "texcoord", (const float*)mTexCoords.data(), mTexCoords.size());
    WriteVec3Array(out, "tangent", (const float*)mTangents.data(), mTangents.size());
    WriteVec3Array(out, "bitangent", (const float*)mBitangents.data(), mBitangents.size());
    WriterFmt(out, "      <vertices id=\"verts\">\n        <input semantic=\"POSITION\" source=\"#position\"/>\n      </vertices>\n      <triangles material=\"Asset_Body\" count=\"%d\">\n",
              mPosIndices.size() / 3);
    WriterStr(out,
        "        <input semantic=\"VERTEX\" source=\"#verts\" offset=\"0\"/>\n"
        "        <input semantic=\"NORMAL\" source=\"#normal\" offset=\"1\"/>\n"
        "        <input semantic=\"TEXCOORD\" source=\"#texcoord\" offset=\"2\"/>\n"
        "        <input semantic=\"TEXTANGENT\" source=\"#tangent\" offset=\"2\"/>\n"
        "        <input semantic=\"TEXBINORMAL\" source=\"#bitangent\" offset=\"2\"/>\n");
    WriterFmt(out, "        <p>\n          ");
    for (v_p36 = 0; v_p36 + 2 < mPosIndices.size(); v_p36 += 3) {
        WriterFmt(out, "%d %d %d %d %d %d %d %d %d ",
                  mPosIndices[v_p36], mNormalIndices[v_p36], mTexIndices[v_p36],
                  mPosIndices[v_p36 + 1], mNormalIndices[v_p36 + 1], mTexIndices[v_p36 + 1],
                  mPosIndices[v_p36 + 2], mNormalIndices[v_p36 + 2], mTexIndices[v_p36 + 2]);
    }
    WriterStr(out, "\n        </p>\n      </triangles>\n    </mesh>\n  </geometry>\n</library_geometries>\n\n<library_controllers>\n  <controller id=\"skin\" name=\"skin\">\n    <skin source=\"#mesh\">\n");
    WriteNameArray(out, "jointnames", (const int*)mJointNames.data(), mInvBindPoses.size());
    WriteInvBindPose(out, "invbindpose", mInvBindPoses.data(), mInvBindPoses.size());
    WriteWeightArray(out, "weights", mBoneWeights.data(), mBoneWeights.size() * 4);
    WriterStr(out, "      <joints>\n        <input semantic=\"JOINT\" source=\"#jointnames\"/>\n        <input semantic=\"INV_BIND_MATRIX\" source=\"#invbindpose\"/>\n      </joints>\n");
    WriterFmt(out, "      <vertex_weights count=\"%d\">\n", mPositions.size());
    WriterStr(out, "        <input semantic=\"JOINT\" source=\"#jointnames\" offset=\"0\"/>\n        <input semantic=\"WEIGHT\" source=\"#weights\" offset=\"1\"/>\n        <vcount>\n          ");
    for (v_n3 = 0; v_n3 < mBoneIndices.size(); v_n3++) {
        if (mBoneIndices[v_n3].j[0] == -1)
            WriterStr(out, "0 ");
        else if (mBoneIndices[v_n3].j[1] == -1)
            WriterStr(out, "1 ");
        else if (mBoneIndices[v_n3].j[2] == -1)
            WriterStr(out, "2 ");
        else if (mBoneIndices[v_n3].j[3] == -1)
            WriterStr(out, "3 ");
        else
            WriterStr(out, "4 ");
    }
    WriterStr(out, "\n        </vcount>\n        <v>\n          ");
    for (v_k = 0; v_k < mBoneIndices.size(); v_k++) {
        if (mBoneIndices[v_k].j[0] == -1)
            WriterStr(out, " ");
        else if (mBoneIndices[v_k].j[1] == -1)
            WriterFmt(out, "%d %d ", mBoneIndices[v_k].j[0], v_k * 4);
        else if (mBoneIndices[v_k].j[2] == -1)
            WriterFmt(out, "%d %d %d %d ", mBoneIndices[v_k].j[0], v_k * 4, mBoneIndices[v_k].j[1], v_k * 4 + 1);
        else if (mBoneIndices[v_k].j[3] == -1)
            WriterFmt(out, "%d %d %d %d %d %d ", mBoneIndices[v_k].j[0], v_k * 4, mBoneIndices[v_k].j[1], v_k * 4 + 1,
                      mBoneIndices[v_k].j[2], v_k * 4 + 2);
        else
            WriterFmt(out, "%d %d %d %d %d %d %d %d ", mBoneIndices[v_k].j[0], v_k * 4, mBoneIndices[v_k].j[1], v_k * 4 + 1,
                      mBoneIndices[v_k].j[2], v_k * 4 + 2, mBoneIndices[v_k].j[3], v_k * 4 + 3);
    }
    WriterStr(out, "\n        </v>\n      </vertex_weights>\n    </skin>\n  </controller>\n</library_controllers>\n\n<library_visual_scenes>\n  <visual_scene id=\"scene\">\n    <node id=\"sroot\" type=\"JOINT\">\n");
    WriteJointNodes(out, mJointNames.data(), mJointParents.data(), mJointXforms.data(), mJointParents.size());
    WriterStr(out,
        "    </node>\n    <node>\n      <instance_controller url=\"#skin\">\n        <skeleton>#sroot</skeleton>\n"
        "        <bind_material>\n          <technique_common>\n"
        "            <instance_material symbol=\"Asset_Body\" target=\"#Asset_Material\">\n"
        "              <bind_vertex_input semantic=\"TEX0\" input_semantic=\"TEXCOORD\" input_set=\"0\"/>\n"
        "            </instance_material>\n          </technique_common>\n        </bind_material>\n"
        "      </instance_controller>\n    </node>\n  </visual_scene>\n</library_visual_scenes>\n\n"
        "<scene>\n  <instance_visual_scene url=\"#scene\"/>\n</scene>\n\n</COLLADA>\n");
    return true;
}
