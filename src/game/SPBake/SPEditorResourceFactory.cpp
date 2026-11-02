// src/game/SPBake/SPEditorResourceFactory.cpp -- migrated from slice(s) s01244f50, s004b11f0, s004af210, s004bf430, s004bd850, s005002d0, s004be5d0, s004bcc50, s004bbfb0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorResourceFactory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorResourceFactory.h"
#include "EA/Allocator/FixedBufferAllocator.h"
#include "EA/XML/XmlTextWriter.h"
#include <stdio.h>
#include <wchar.h>
#include "SP/cEditorModelParser.h"
#include <stddef.h>
#include <math.h>

// unnamed retail callees and globals (address in the comment)
struct StreamObject;
extern void* GetManager();  // 0x67dcd0
extern uint32_t EA_Hash_FNV1_String16(const void* s, uint32_t hash, int);  // 0x932f30
extern void FUN_004c07e0(void* begin, void* end, char flag);               // 0x4c07e0
extern void FUN_006adc60(int, int);                                        // 0x6adc60
extern bool g_typeTableInit;                                               // 0x15d8600
extern int* FUN_004c0500(uint32_t key);                            // 0x4c0500
extern void FUN_006ac0a0(int type, uint32_t key);                  // 0x6ac0a0
extern bool FUN_004bdc00(int n);                                   // 0x4bdc00
extern bool FUN_004bdae0();                                        // 0x4bdae0
extern int FUN_004bd9f0(int);                                      // 0x4bd9f0
extern bool FUN_004bdc60(int a, int b, bool c);                    // 0x4bdc60
extern bool FUN_004be5d0();                                        // 0x4be5d0
extern bool ReadRuntimeCreatureData(int data, uint32_t handle);    // 0x4bf430
extern bool WriteRuntimeCreatureData(int* data, int handle);       // 0x4bf770
extern int WriteBinaryEditorModel(int data);                       // 0x4b0010
extern bool ReadBinaryEditorModel(StreamObject* stream, uint32_t key); // 0x4bf9f0
extern bool SetAssetData(uint32_t type, uint8_t flag);             // 0x4bbe20
extern void SetCachingType2(int, void*);                           // 0x6ac040
extern void DestroyFixedBufferShared(void*);                       // 0x4bca10
extern void* EditorAlloc(uint32_t size, const char* name, int, int, int, int);  // 0xf473a0
extern char g_vtbl_Anim_BackgroundLoading[];
extern char g_vtbl_Resource_PFRecordRead[];
extern char g_vtbl_scalar_deleting_dtor[];
extern "C" void FreeMemory(void* p);   // 0x926060
extern "C" long _InterlockedExchange(volatile long* Target, long Value);
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s004bbfb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct StreamObject {
virtual void v0();
virtual void v4();
virtual void v8();
virtual void vC();
    virtual int* v10();                                  // +0x10
    virtual void v14();
    virtual int v18(int a, int b);                       // +0x18
    virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
    virtual int v30(int* buf, int n);                    // +0x30
};
extern bool WriteResourceToStream(int* data, int stream, int typeHash); // 0x4bcc50
struct StreamObject_s004b_bfb0;
struct cSPEditorResourceFactory {
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void vC();
    virtual void* v10();
    virtual void v14();
    virtual void v18(int a, int b);
    virtual void v1C();
    virtual void v20();
    virtual bool v24(int* a, int* b, int c, int d);
    virtual void v28();
    virtual void v2C();
    virtual bool v30(int a, int b);

    int GetSupportedTypes(uint32_t* types, uint32_t count);  // 004bc210
    bool CanConvert(int inType, int outType);                // 004bc290
    int Init();                                              // 004bc080
    bool CreateResource(StreamObject_s004b_bfb0* obj, int* out, uint32_t param_4, int typeHash);   // 004bc300
    bool ReadResource(StreamObject_s004b_bfb0* stream, uint32_t param_2, uint32_t param_3, int typeHash);   // 004bc540
    bool WriteResource(StreamObject_s004b_bfb0* stream, uint32_t param_1, uint32_t param_2, int typeHash);  // 004bc620
    static bool ReadResourceFromStream(StreamObject_s004b_bfb0* stream, uint32_t key, int typeHash);               // 004bc6d0
};
struct TypeEntry {
    uint32_t mHash;        // +0
    const void* mName;     // +4
    uint32_t pad[4];
};
struct IResourceManager2 {
virtual void v0();
virtual void v4();
virtual void v8();
    virtual void vC();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
    virtual void v20();
    virtual void Register(uint32_t type, uint32_t* pair, int count);  // +0x24
};
struct RefCounted_s004b_bfb0 {
    virtual void v0();       // +0
    virtual void Release();  // +4
    RefCounted_s004b_bfb0* FUN_004b9c70();  // 0x4b9c70 (thiscall ctor, ecx = raw allocation)
    RefCounted_s004b_bfb0* FUN_004b9da0();  // 0x4b9da0 (thiscall ctor, ecx = raw allocation)
};
struct StreamObject_s004b_bfb0 {
virtual void v0();
virtual void v4();
virtual void v8();
virtual void vC();
    virtual int* v10();                                  // +0x10
    virtual void v14();
    virtual int v18(int a, int b);                       // +0x18
    virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
    virtual int v30(int* buf, int n);                    // +0x30
};
struct WriteTarget {
virtual void w0();
virtual void w4();
virtual void w8();
virtual void wC();
virtual void w10();
virtual void w14();
    virtual int v18(int a, ...);                         // +0x18
};
struct EditorCreature : RefCounted_s004b_bfb0 {
    uint32_t pad4;
    uint32_t f8, fC, f10;
};
extern bool ReadBinaryEditorModel(StreamObject_s004b_bfb0* stream, uint32_t key); // 0x4bf9f0
static inline void ReleaseRef(RefCounted_s004b_bfb0* p) {
    if (p)
        p->Release();
}
namespace EA {
namespace Allocator {
class FixedBufferAllocator_s004b_bfb0 { public:
    struct buffer_info {
        int32_t mSignature;   // +0x0
        int32_t mSize;        // +0x4
        int32_t mSizeFree;    // +0x8
        void*   mpFirstFree;  // +0xc
    };

    buffer_info* mpBufferInfo;   // +0x0

    FixedBufferAllocator_s004b_bfb0* Create(void* pBuffer, uint32_t size, uint8_t bShared);  // 004bc8a0
    bool IsValid();                                                           // 004bc990 0x004bc990
    void destroy_shared();                                                    // 004bca10 0x004bca10
    void Free(void* p);                                                       // 004bcab0 0x004bcab0
};
}
}
namespace EA {
namespace Allocator {
struct GlobalAllocator {
    void Free(void* p);
};
}
}
namespace EA {
namespace Allocator {
extern GlobalAllocator* g_pGlobalAllocator;  // 0x016c8b44
}
}
struct cEditorModelParser_s004b_bfb0 : EA::Allocator::FixedBufferAllocator_s004b_bfb0 {
    char mBuffer[0x3a98];       // +0x04 .. +0x3a9b
    void* mpXMLParser;          // +0x3a9c
    int m3aa0;                  // +0x3aa0
    int m3aa4;                  // +0x3aa4
    int m3aa8;                  // +0x3aa8
    int m3aac;                  // +0x3aac
    uint16_t mBuffer2[0x400];   // +0x3ab0
    int mLength;                // +0x42b0
    int mCursor;                // +0x42b4

    void FUN_004bd9f0(int data);                 // 0x4bd9f0
    int  FUN_004bdc00(int n);                    // 0x4bdc00
    bool FUN_004bdc60(int* buf, int n, int done); // 0x4bdc60
    bool FUN_004be5d0();                         // 0x4be5d0
    void FUN_004bdae0();                         // 0x4bdae0
};
struct FactoryObject {
    void* vptr;          // +0x0
    int32_t mnRefCount;  // +0x4

    FactoryObject* Init();                 // 004bbfb0
    FactoryObject* Destroy(uint32_t p);    // 004bc030
};
extern TypeEntry g_typeTable[];                                            // 0x150c518
extern TypeEntry g_typeTableEnd[];                                         // 0x150c878
// ---- items of slice s004bbfb0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s004bcc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
#pragma pack(pop)
struct Vector3
{
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct Matrix3
{
    Vector3 m[3];
    Vector3& operator[](int i) { return m[i]; }
};
bool operator!=(const Matrix3& a, const Matrix3& b);   // 0x0041dd90 (operator!=<>)
extern Matrix3 g_UserOrientationIdentity;   // 0x015d88c0
struct ModelProperties
{
    uint32_t mModelType;          // +0x00
    int      mZCorpScore;         // +0x04
    uint32_t mSkinEffect[3];      // +0x08 (0xcdcdcdcd = unset)
    int      mSkinEffectSeed[3];  // +0x14
    Vector3  mSkinColor1;         // +0x20
    Vector3  mSkinColor2;         // +0x2c
    Vector3  mSkinColor3;         // +0x38
};
struct EditorBlock   // 0x1d8 bytes
{
    uint32_t mBlockID[2];         // +0x000
    uint32_t mParent;             // +0x008
    uint32_t mSymmetric;          // +0x00c
    float    mScale;              // +0x010
    Vector3  mPosition;           // +0x014
    Vector3  mTriangleDirection;  // +0x020
    Vector3  mTrianglePickOrigin; // +0x02c
    Matrix3  mOrientation;        // +0x038
    Matrix3  mUserOrientation;    // +0x05c
    uint8_t  mbSnapped;           // +0x080
    uint8_t  mbIsAsymmetric;      // +0x081
    uint8_t  pad82[2];
    int      mLimbType;           // +0x084
    float    mMuscleScale;        // +0x088
    float    mBaseMuscleScale;    // +0x08c
    uint32_t mHandleCount;        // +0x090
    float    mHandleWeights[8];   // +0x094
    int      mHandleChannels[8];  // +0x0b4
    uint32_t mPaintCount;         // +0x0d4
    uint32_t mPaintRegions[8];    // +0x0d8
    uint32_t mPaintIDs[8];        // +0x0f8
    Vector3  mPaintColor1[8];     // +0x118
    Vector3  mPaintColor2[8];     // +0x178
};
struct BlockVector
{
    EditorBlock* mpBegin;
    EditorBlock* mpEnd;
    int size() { return mpEnd - mpBegin; }
    EditorBlock& operator[](int i) { return mpBegin[i]; }
};
struct EditorModelData
{
    uint32_t        pad00[0x18 / 4];
    ModelProperties mProperties;  // +0x18
    uint32_t        pad5c[(0x98 - 0x5c) / 4];
    BlockVector     mBlocks;      // +0x98
};
struct IStream;
namespace EA {
namespace XML {
class XmlTextWriter_s004b_cc50
{
public:
    uint32_t mData[8];
    XmlTextWriter_s004b_cc50(int a, int b);                                        // 0x00901a10
    ~XmlTextWriter_s004b_cc50();                                                   // 0x00901a50
    void SetOutputStream(IStream* stream, int a);                       // 0x00901d30
    void WriteXmlHeader();                                              // 0x00901960
    void BeginElement(const wchar_t* name);                             // 0x00901b30
    bool EndElement(const wchar_t* name);                               // 0x00901b90
    void AppendAttributeF(const wchar_t* name, const wchar_t* fmt, ...);   // 0x009017d0
    void WriteCharData(const wchar_t* text);                            // 0x009018a0
};
}
}
using EA::XML::XmlTextWriter_s004b_cc50;
struct FixedWString
{
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator[2];
    wchar_t  mBuffer[0x80];
    uint32_t mOverflow[2];
    FixedWString();                                    // 0x004c01b0
    ~FixedWString();                                   // 0x004292a0
    void sprintf(const wchar_t* fmt, ...);             // 0x004c0530
    const wchar_t* c_str() { return mpBegin; }
};
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
template<class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}
struct IntVectorBase
{
    int*     mpBegin;
    int*     mpEnd;
    int*     mpCapacity;
    uint32_t mAllocator;
    int*     mpPoolBegin;
    uint32_t pad14;
    ~IntVectorBase();                                  // 0x004c0b80
};
struct IntFixedVector : IntVectorBase
{
    int mBuffer[256];
    IntFixedVector(uint32_t n, int value);      // 0x004c0570
    ~IntFixedVector() { destruct(mpBegin, mpEnd); ScratchSlots<3>(); }
    int& operator[](int i) { return mpBegin[i]; }
};
EditorModelData* WriteBinaryEditorModel_s004b_cc50(int model);                                 // 0x004b0010
bool FUN_004bfb20(IStream* stream, int model);                                      // 0x004bfb20
bool XmlWriteElement(XmlTextWriter_s004b_cc50* w, const wchar_t* name, const wchar_t* text);   // 0x004bede0
bool XmlWriteBool(XmlTextWriter_s004b_cc50* w, const wchar_t* name, bool value);               // 0x004bee50
bool XmlWriteUInt(XmlTextWriter_s004b_cc50* w, const wchar_t* name, uint32_t value);           // 0x004bee90
bool XmlWriteHex(XmlTextWriter_s004b_cc50* w, const wchar_t* name, uint32_t value);            // 0x004beec0
bool XmlWriteFloat(XmlTextWriter_s004b_cc50* w, const wchar_t* name, float value);             // 0x004bef40
bool XmlWriteVector3(XmlTextWriter_s004b_cc50* w, const wchar_t* name, const float* v);        // 0x004bef80
wchar_t* FormatFloat(wchar_t* buf, float value);                                    // 0x004beca0
namespace SP {
class cSPEditorResourceFactory_s004b_cc50
{
public:
    static bool WriteResourceToStream(IStream* stream, int model, int modelTypeHash);  // 0x004bcc50 (SP::cSPEditorResourceFactory::WriteResourceToStream)
};  // namespace SP
}
// ---- items of slice s004bcc50 end

// ---- items of slice s004be5d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ultow(unsigned long value, wchar_t* buf, int radix);
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
#pragma intrinsic(wcscmp, wcscpy)
struct Vector3_s004b_e5d0 {
    float x, y, z;
    float LengthSquared() const { return x * x + y * y + z * z; }
};
template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct ParseElem {
    int mKind;              // 0x00
    int mType;              // 0x04
    int mParent;            // 0x08
    int mPartner;           // 0x0C (mirror element, -1 if none)
    float mScale;           // 0x10
    uint32_t pad14[9];      // 0x14
    Vector3_s004b_e5d0 mAxes[3];       // 0x38
    uint32_t pad5c[13];     // 0x5C
    uint32_t mNumValues;    // 0x90
    float mValues[8];       // 0x94
    int mValueIds[8];       // 0xB4
    uint32_t mNumSlots;     // 0xD4
    uint32_t padD8[64];     // 0xD8

    const Vector3_s004b_e5d0& GetAxis(int k) const { return mAxes[k]; }
};
struct ParseData {
    uint32_t pad0[38];          // 0x00
    vector<ParseElem> mElems;   // 0x98
};
class XmlParseContext {
public:
    bool Validate();
    bool ParseFloat(float* out);       // 0x004BE2E0
    bool ParseUInt(uint32_t* out);     // 0x004BE380
    void SelectElement(uint32_t index);// 0x004BE420

    uint32_t pad0[0x3AA0 / 4];
    ParseData* mpData;      // 0x3AA0
    int mCurrent;           // 0x3AA4
    int m3AA8;              // 0x3AA8
    int mCurrentId;         // 0x3AAC
    wchar_t mText[256];     // 0x3AB0
};
int MapKind(uint32_t value);   // 0x004BD850
int MapType(uint32_t value);   // 0x004BD9C0
wchar_t* FtoaEnglish16(double value, wchar_t* buf, int bufSize, int precision, bool trim);
class IXmlWriter {
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual bool BeginElement(const wchar_t* name);
    virtual bool EndElement(const wchar_t* name);
    virtual void Unk4();
    virtual void Unk5();
    virtual void Unk6();
    virtual void Unk7();
    virtual bool WriteText(const wchar_t* text);
};
inline bool IsNaN(float f) { return (*(uint32_t*)&f & 0x7FFFFFFF) > 0x7F800000; }
inline bool IsInf(float f) { return (*(uint32_t*)&f & 0x7FFFFFFF) == 0x7F800000; }
union FloatBits {
    float f;
    uint32_t u;
};
struct IStream_s004b_e5d0 { private:
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual void Unk2();
    virtual void Unk3();
    virtual void Unk4();
    virtual void Unk5();
    virtual void Unk6();
    virtual void Unk7();
    virtual void Unk8();
    virtual void Unk9();
    virtual void Unk10();
    virtual void Unk11();
    virtual int Read(void* dst, uint32_t size);
    virtual void Unk13();
    virtual bool Write(const void* src, uint32_t size);
};
// ---- items of slice s004be5d0 end

// ---- items of slice s005002d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
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

// ---- items of slice s004bd850 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* FUN_0090aed0(int a, void* table, int b);            // 0x90aed0
extern void FUN_009032e0(void* parser, void* thiz);              // 0x9032e0
extern void FUN_00903300(void* parser, void* start, void* end);  // 0x903300
extern void FUN_00903320(void* parser, void* cb);                // 0x903320
extern char PTR_FUN_0150c50c[];
extern void StartElementCb();   // 0x4bdcd0
extern void EndElementCb();     // 0x4be100
extern void CharDataCb();       // 0x4be070
extern void FUN_009055d0(void* parser);   // XML_ParserFree, 0x9055d0
extern void FUN_00903550(void* parser, int arg);   // 0x903550 (XML_StopParser-style, cdecl)
extern "C" void* __cdecl memset_impl(void* dst, int value, uint32_t n);   // 0x11e073e
extern float HK_REAL_ONE;   // 0x1485720  (_HK_REAL_ONE, Havok's 1.0f)
extern int FUN_00903400(void* parser, int param);                       // 0x903400
extern int FUN_00905740(void* parser, int a, int b, int c);             // 0x905740
extern float FUN_0092ddc0(const wchar_t*, wchar_t**);   // 0x92ddc0
extern int FUN_00903b40(void* parser);   // 0x903b40
extern "C" void* __cdecl memcpy_impl(void* dst, const void* src, uint32_t n);  // 0x11e0744
#pragma intrinsic(wcscmp)
struct cEditorModelParser;
__declspec(thread) cEditorModelParser* g_pCurrentParser;
struct cEditorModelParser {
    char pad[0x3a9c];
    void* mpXMLParser;        // +0x3a9c
    int m3aa0;                // +0x3aa0
    int m3aa4;                // +0x3aa4
    int m3aa8;                // +0x3aa8
    int m3aac;                // +0x3aac
    uint16_t mBuffer[0x400];  // +0x3ab0
    int mLength;              // +0x42b0
    int mCursor;              // +0x42b4

    int FUN_004bdbd0();
    void FUN_004bdae0();                            // 004bdae0
    void FUN_004bd9f0(int param);                   // 004bd9f0
    int FUN_004bdc00(int param);                    // 004bdc00
    bool FUN_004bdc60(int a, int b, uint8_t c);     // 004bdc60
    bool ReadULong(unsigned long* out);   // 004be380
    bool ReadFloat(float* out);           // 004be2e0
};
struct FBAStub {
    void* mpBufferInfo;
    FBAStub* Create(void* pBuffer, uint32_t size, uint8_t bShared);
    void destroy_shared();
};
FBAStub* FBAStub::Create(void* pBuffer, uint32_t size, uint8_t bShared) {
    (void)pBuffer; (void)size; (void)bShared;
    return this;
}
void FBAStub::destroy_shared() {
}
__declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
struct ParserBlockOps {
    void AddBlock(int index);                      // 0x004be420 (thiscall, ret 4)
};
struct ParserModelBlocks {
    void Reserve(uint32_t count);                  // 0x004c0250 (thiscall, ret 4)
};
struct EditorModelElem {
    uint32_t        mHash;      // +0x00  FNV1 hash of the element name
    const wchar_t*  mpName;     // +0x04
    int             mKind;      // +0x08  0 = index-based target
    bool (__cdecl*  mpFn)(void* self, void* target, void* arg);   // +0x0c
    int             mOffset;    // +0x10  added to the resolved target
    void*           mpArg;      // +0x14
};
extern EditorModelElem g_editorModelElems[];    // 0x150c518, 36 entries
extern EditorModelElem* FUN_004c0600(EditorModelElem* first, EditorModelElem* last,
                                     const uint32_t* value, uint8_t ordered);  // 0x4c0600
struct ModelBlock {                  // 0x1d8 bytes
    int   mField00;                  // +0x00
    int   mField04;                  // +0x04
    int   mField08;                  // +0x08
    int   mField0C;                  // +0x0c
    uint8_t mPad10[0x5c - 0x10];
    float mMatrix[3][3];             // +0x5c  (diagonal set to 1.0f)
    uint8_t mPad80[0x84 - 0x80];
    int   mField84;                  // +0x84
    uint8_t mPad88[0x1d8 - 0x88];
};
struct ModelBlockVec {
    int mpBegin;                     // +0x00  (first block address)
    int mpEnd;                       // +0x04
    int mpCapacity;                  // +0x08
    uint8_t mPad0C[0x14 - 0x0c];
    void Reserve(uint32_t count);    // 0x004afd00 (thiscall, ret 4)
};
// ---- items of slice s004bd850 end

// ---- items of slice s004bf430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchangeAdd(volatile long* Addend, long Value);
extern void* FUN_00928a80(void* p, uint32_t size, int zero);   // 0x928a80
extern int FUN_004afd00(int n);                                  // 0x4afd00
extern void operator_new__(void* p, int a, int n);               // in-place new
extern void* ZoneObject_operator_new(uint32_t size, const char* name, int, int, int, int);  // 0x926020
#pragma intrinsic(_InterlockedExchangeAdd)
struct SPMemPoolStub {
    void* LockedAlloc(uint32_t size, int a, int b, int c, int d, int e);                      // 0x009289f0 (ret 0x18)
    void* LockedAligned(uint32_t size, uint32_t align, int a, int b, int c, int d, int e, int f);  // 0x00928a30 (ret 0x20)
};
extern SPMemPoolStub* g_pSPMemPool;     // 0x016c8b44
struct FixedBufferAllocatorStub {
    struct buffer_info { int32_t mSignature, mSize, mSizeFree; void* mpFirstFree; };
    struct block_header { uint32_t mSize; block_header* mpPrev; };
    buffer_info* mpBufferInfo;
    bool IsInitialized() const { return mpBufferInfo != 0; }
    void* Malloc(uint32_t nSize, uint32_t nAlignment);   // 0x4bfc40
    void Free(void* p);                 // 0x4bcab0
};
__declspec(thread) void* g_tls_current;
struct ResourceObject {
    void* vptr;          // +0
    int32_t mnRefCount;  // +4
    int GetReferenceCount();
};
#define FBA_MASK 0x3fffffff
#define FBA_INUSE 0x80000000
#define FBA_TRAILER 0x40000000
void FixedBufferAllocatorStub::Free(void* p) {
    (void)p;
}
struct IStream_s004b_f430 {
virtual void Unk00();
virtual void Unk04();
virtual void Unk08();
virtual void Unk0C();
virtual void Unk10();
virtual void Unk14();
virtual void Unk18();
virtual void Unk1C();
virtual void Unk20();
virtual void Unk24();
virtual void Unk28();
virtual void Unk2C();
    virtual int  Read(void* dst, uint32_t size);              // +0x30
    virtual void Unk34();
    virtual bool Write(const void* src, uint32_t size);       // +0x38
};
struct ChunkHeader {              // 8-byte block header
    uint32_t mMagic;              // 0xabb455b7
    uint32_t mVersion;            // 9 or 10
};
struct ChunkCounts {              // 0x10-byte element counts (0xc at version 9)
    uint32_t mNumElements;        // 0x8c-byte element records
    uint32_t mNumValues;          // 4-byte values, plus one byte each
    uint32_t mNumFloats;          // floats, spread over three arrays
    uint32_t mNumBones;           // 0x38-byte bone records (version 10 only)
};
struct Element8c { uint32_t mData[0x8c / 4]; };
struct Bone38    { uint32_t mData[0x38 / 4]; };
template <int N> inline void ScratchSlots_s004b_f430() { uint32_t slots[N]; }
template <class T> struct SpVector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    T* begin() const { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }
    void resize(uint32_t n);
};
template <> void SpVector<Element8c>::resize(uint32_t n);   // 0x4c0350
template <> void SpVector<uint32_t>::resize(uint32_t n);    // 0x4cd3c0
template <> void SpVector<uint8_t>::resize(uint32_t n);     // 0x4c0410
template <> void SpVector<float>::resize(uint32_t n);       // 0x4afc80
template <> void SpVector<Bone38>::resize(uint32_t n);      // 0x4c0480
struct CreatureData {
    uint32_t mPad00[6];                  // 0x00
    uint8_t  mPayload[0x80];             // 0x18 RLE-compressed block
    SpVector<Element8c> mElements;       // 0x98
    uint32_t mPadA4[2];                  // 0xa4
    SpVector<uint32_t>  mValues;         // 0xac
    uint32_t mPadB8[2];                  // 0xb8
    SpVector<uint8_t>   mValueBytes;     // 0xc0
    uint32_t mPadCC[2];                  // 0xcc
    SpVector<uint32_t>  mScalars;        // 0xd4
    uint32_t mPadE0[2];                  // 0xe0
    SpVector<float>     mFloats0;        // 0xe8
    uint32_t mPadF4[2];                  // 0xf4
    SpVector<float>     mFloats1;        // 0xfc
    uint32_t mPad108[2];                 // 0x108
    uint32_t mFlags;                     // 0x110
    SpVector<Bone38>    mBones;          // 0x114
};
extern bool ReadRLE(IStream_s004b_f430* stream, uint8_t* data, uint32_t size);        // 0x4bf2a0
extern bool WriteRLE(IStream_s004b_f430* stream, const uint8_t* data, uint32_t size); // 0x4bf0a0
struct StreamWriter {
virtual void v0();
virtual void v4();
virtual void v8();
virtual void vC();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
virtual void v30();
virtual void v34();
    virtual bool v38(void* buf, int n);   // +0x38
};
extern bool FUN_004bf0a0(StreamWriter* w, int addr, int n);   // 0x4bf0a0
struct StreamReader {
virtual void v0();
virtual void v4();
virtual void v8();
virtual void vC();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
    virtual int v30(void* buf, int n);   // +0x30
};
extern bool FUN_004bf2a0(StreamReader* r, int addr, int n);      // 0x4bf2a0
struct FactoryObject_s004b_f430 {
    void* vptr;
    int32_t mnRefCount;
};
struct FactoryCtor {
    FactoryObject_s004b_f430* Init();   // 0x4bbfb0
};
struct FactoryVtbl {
virtual void v0();
virtual void v4();
virtual void v8();
virtual void vC();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
};
struct XmlTextWriter {
    int* mpBuffer;      // +0
    int* mpBufferEnd;   // +4
    int* mpCapacity;    // +8
    int pad0c;          // +0xc
    int pad10;          // +0x10
    void FUN_00422c80(void* out);   // 0x422c80
    int* Init();
};
void XmlTextWriter::FUN_00422c80(void* out) {
    (void)out;
}
// ---- items of slice s004bf430 end

// ---- items of slice s004af210 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Block194 { uint32_t d[0x76]; };
struct VecBase {
    char* mpBegin;      // +0x0
    char* mpEnd;        // +0x4
    char* mpCapacity;   // +0x8
    char* mpAllocName;  // +0xc (eastl allocator name passed to EASTL_Allocate)

    void Resize4(unsigned int n);     // 0x4afbf0
    void Resize4F(unsigned int n);    // 0x4afc80
    void Resize24(unsigned int n);    // 0x4aff80
    void Resize1d8(unsigned int n);   // 0x4afd00
    void Reserve194(unsigned int n);  // 0x4afdd0
    Block194* Erase194(Block194* dst, Block194* end);  // 0x4b0340
    void* Init8();                    // 0x4b0040

    // out-of-line vector primitives: thiscall, ecx is the vector base, the callee pops the stack args
    void FUN_00454280(char* first, char* last);            // 0x454280
    void FUN_004b0590(char* end, int n, void** out);       // 0x4b0590
    void FUN_004b0a10(char* end, int n, void** out);       // 0x4b0a10
    void FUN_004b1800(char* end, int n, void* elem);       // 0x4b1800
    void FUN_004b11f0(char* end, int n, void* elem);       // 0x4b11f0
    void FUN_004b0490(char* first, char* last);            // 0x4b0490
    char* FUN_004769b0(char* first, char* last);           // 0x4769b0
    void FUN_004b0180(void* local);                        // 0x4b0180
};
// ---- items of slice s004af210 end

// ---- items of slice s004b11f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s004b_11f0() { uint32_t s[N]; }
void EASTLFree(void* p);                                                         // 0x00F47380 operator delete[]
void* EASTLAlloc(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042DEE0
namespace eastl {
struct false_type {};
}
namespace eastl {
struct EASTLAllocator { const char* mpName; EASTLAllocator() {} };
}
namespace eastl {
struct random_access_iterator_tag { random_access_iterator_tag() {} };
}
namespace eastl {
struct Big {                                   // 0x1d8-byte element, out-of-line copy ctor (0x004721E0)
    uint32_t d[0x76];
    Big(const Big& o);
};
}
namespace eastl {
template <class T> class generic_iterator { public:
    T mIterator;
    explicit generic_iterator(const T& x) : mIterator(x) {}
    const T& base() const { return mIterator; }
};
}
namespace eastl {
template <class T> struct value_of;
}
namespace eastl {
template <class T> struct value_of<T*> { typedef T type; };
}
namespace eastl {
template <class T> struct value_of<const T*> { typedef T type; };
}
namespace eastl {
template <class T> struct has_trivial_relocate : public false_type {};
}
namespace eastl {
template <class T> T* uninitialized_move(T* first, T* last, T* dest);              // out of line
}
namespace eastl {
template <class In, class Out>
generic_iterator<Out> uninitialized_copy_impl(generic_iterator<In> first, generic_iterator<In> last,
                                              generic_iterator<Out> dest, false_type);
}
namespace eastl {
template <class It, class T>
void uninitialized_fill_n_impl(generic_iterator<It> first, uint32_t n, const T& value, false_type);
}
namespace eastl {
template <class First, class Last, class Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    const generic_iterator<Result> i(uninitialized_copy_impl(generic_iterator<First>(first),
                                                             generic_iterator<Last>(last),
                                                             generic_iterator<Result>(result),
                                                             has_trivial_relocate<typename value_of<Result>::type>()));
    return i.base();
}
}
namespace eastl {
template <class T>
inline void uninitialized_fill_n_ptr(T* first, uint32_t n, const T& value)
{
    uninitialized_fill_n_impl(generic_iterator<T*>(first), n, value, has_trivial_relocate<T>());
}
}
namespace eastl {
template <class Bi1, class Bi2>
__forceinline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
}
namespace eastl {
template <class T>
__forceinline T* copy_backward_loop(T* first, T* last, T* resultEnd)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, resultEnd);
}
}
namespace eastl {
template <class T>
inline void fill(T* first, T* last, const T& value)
{
    for (; first != last; ++first)
        *first = value;
}
}
namespace eastl {
template <class T>
class vector_s004b_11f0 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    EASTLAllocator mAllocator;

    inline uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    inline T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    inline void DoFree(T* p, uint32_t n) { if (p) deallocate(p, n * sizeof(T)); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    void DoInsertValues(T* position, uint32_t n, const T& value);
    T* DoRealloc(uint32_t n, const T* first, const T* last);                      // 0x0050E750 (S24)
    void DoAssignFromIterator(const T* first, const T* last, random_access_iterator_tag);
    void DoAssignValues(uint32_t n, const T& value);
    vector_s004b_11f0() {}
    vector_s004b_11f0(uint32_t n, const EASTLAllocator& a);                                  // 0x004AA350
    ~vector_s004b_11f0();                                                                    // 0x004E1BF0
    void swap(vector_s004b_11f0& o);                                                         // 0x0052C730
    void erase_ool(T* first, T* last);                                            // 0x004769B0
};
}
// ---- items of slice s004b11f0 end

// ---- items of slice s01244f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_004be950(void);   // 0x4be950
extern void FUN_004bead0(void);   // 0x4bead0
extern void FUN_004beb70(void);   // 0x4beb70
extern void FUN_004bebd0(void);   // 0x4bebd0
extern void FUN_004bec30(void);   // 0x4bec30
extern void FUN_004bec80(void);   // 0x4bec80
extern void FUN_004be8d0(void);   // 0x4be8d0
extern void FUN_004be820(void);   // 0x4be820
#pragma intrinsic(log)
struct Vec3 { float x, y, z; };
struct ViewRowsA { int paintregion; char pad[0x34]; Vec3 rows[3]; };  // rows at 0x38
struct ViewRowsB { char pad[0x5c]; Vec3 rows[3]; };                    // rows at 0x5c
struct ViewPaintId { char pad[0xd8]; int paintid; };
struct ViewColor1 { char pad[0xf8]; int color1; };
struct ViewColor2 { char pad[0x118]; Vec3 color2; };
struct ViewPaintBlob { char pad[0x178]; Vec3 paint; };
#define FLD(i, m) (*(uint32_t*)(0x150c720 + (i) * 0xc + (m)))
#define OFF(S, m) ((uint32_t)offsetof(S, m))
// ---- items of slice s01244f50 end

// @ 0x004afd00
void VecBase::Resize1d8(unsigned int n)
{
    int count = (int)((mpEnd - mpBegin) / 0x1d8);
    if ((unsigned int)count < n) {
        char tmp[0x1d8];
        void* elem = ((VecBase*)tmp)->Init8();
        FUN_004b11f0(mpEnd, (int)(n - (unsigned int)count), elem);
    }
    else {
        Erase194((Block194*)(mpBegin + n * 0x1d8), (Block194*)mpEnd);
    }
}

// @ 0x004b0040
void* VecBase::Init8()
{
    int local_8 = 8;
    char* local_4 = (char*)this + 0x118;
    while (true) {
        local_8 = local_8 - 1;
        if (local_8 < 0) break;
        local_4 += 0xc;
    }
    int local_10 = 8;
    char* local_c = (char*)this + 0x178;
    while (true) {
        local_10 = local_10 - 1;
        if (local_10 < 0) break;
        local_c += 0xc;
    }
    return this;
}

// @ 0x004b0340
Block194* VecBase::Erase194(Block194* dst, Block194* end)
{
    Block194* out = (Block194*)mpEnd;
    Block194* local_14 = dst;
    for (Block194* local_10 = end; local_10 != out; ++local_10) {
        *local_14 = *local_10;
        ++local_14;
    }
    for (Block194* local_1c = local_14; local_1c < (Block194*)mpEnd; ++local_1c) {
    }
    mpEnd = (char*)mpEnd + ((char*)end - (char*)dst) / 0x1d8 * -0x1d8;
    return dst;
}

// @ 0x004b11f0
namespace eastl {
template <> void vector_s004b_11f0<Big>::DoInsertValues(Big* position, uint32_t n, const Big& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Big temp(value);
            ScratchSlots_s004b_11f0<1>();
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Big* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_loop(position, pEnd - n, pEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ptr(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Big* const pNewData = DoAllocate(nNewSize);
        Big* pNewEnd = uninitialized_move(mpBegin, position, pNewData);
        ScratchSlots_s004b_11f0<8>();
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_move(position, mpEnd, pNewEnd + n);
        ScratchSlots_s004b_11f0<8>();
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
}  // namespace eastl

// @ 0x004bc030
FactoryObject* FactoryObject::Destroy(uint32_t param_2)
{
    vptr = g_vtbl_scalar_deleting_dtor;
    vptr = g_vtbl_Resource_PFRecordRead;
    vptr = g_vtbl_Anim_BackgroundLoading;
    if (param_2 & 1)
        FreeMemory(this);
    return this;
}

// @ 0x004bc080
bool SP::cSPEditorResourceFactory::Init()
{
    if (!g_typeTableInit) {
        for (TypeEntry* e = g_typeTable; e != g_typeTableEnd;
             e = (TypeEntry*)((char*)e + 0x18)) {
            e->mHash = EA_Hash_FNV1_String16(e->mName, 0x811c9dc5, 0);
        }
        FUN_004c07e0(g_typeTable, g_typeTableEnd, 0);
        g_typeTableInit = true;
    }
    IResourceManager2* mgr = (IResourceManager2*)GetManager();
    uint32_t local_c = 0x1a99b06b;
    uint32_t local_8;
    local_8 = 0x2399be55; mgr->Register(0x2399be55, &local_c, 2);
    local_8 = 0x2b978c46; mgr->Register(0x2b978c46, &local_c, 2);
    local_8 = 0x3d97a8e4; mgr->Register(0x3d97a8e4, &local_c, 2);
    local_8 = 0x438f6347; mgr->Register(0x438f6347, &local_c, 2);
    local_8 = 0x24682294; mgr->Register(0x24682294, &local_c, 2);
    local_8 = 0x476a98c7; mgr->Register(0x476a98c7, &local_c, 2);
    FUN_006adc60(10, 0x14);
    FUN_006adc60(9, 0x20);
    return 1;
}

// @ 0x004bc210
unsigned int SP::cSPEditorResourceFactory::GetSupportedTypes(unsigned int * types, unsigned int count)
{
    int unused = 8;
    if (types != 0) {
        if (count < 8)
            return 0;
        types[0] = 0x2b978c46;
        types[1] = 0x2399be55;
        types[2] = 0x24682294;
        types[3] = 0x476a98c7;
        types[4] = 0x438f6347;
        types[5] = 0x3d97a8e4;
        types[6] = 0xf43029a;
        types[7] = 0x1a99b06b;
    }
    return 8;
}

// @ 0x004bc290
bool SP::cSPEditorResourceFactory::CanConvert(unsigned int inType, unsigned int outType) const
{
    if (inType == 0x1a99b06b)
        return outType == 0x2b978c46 || outType == 0x2399be55 ||
               outType == 0x24682294 || outType == 0x476a98c7 ||
               outType == 0x438f6347 || outType == 0x3d97a8e4;
    return false;
}

// @ 0x004bc300
bool cSPEditorResourceFactory::CreateResource(StreamObject_s004b_bfb0* obj, int* out, uint32_t param_4, int typeHash)
{
    RefCounted_s004b_bfb0* local_8 = 0;
    if (!SetAssetData((uint32_t)typeHash, 0)) {
        if (typeHash != 0xf43029a)
            return false;
        EditorCreature* c = (EditorCreature*)EditorAlloc(0x128, "Editor", 0, 0, 0, 0);
        if (c)
            c = (EditorCreature*)c->FUN_004b9da0();
        if (c)
            c->v0();
        local_8 = c;
    } else {
        RefCounted_s004b_bfb0* local_28 = (RefCounted_s004b_bfb0*)EditorAlloc(0xac, "Editor", 0, 0, 0, 0);
        if (local_28)
            local_28 = local_28->FUN_004b9c70();
        if (local_28)
            local_28->v0();
        SetCachingType2(10, local_28);
        if (local_28) {
            local_28->v0();
            local_8 = local_28;
        }
        ReleaseRef(local_28);
    }
    if (this->v24((int*)obj, (int*)local_8, param_4, typeHash)) {
        int* p = obj->v10();
        ((EditorCreature*)local_8)->f8 = p[0];
        ((EditorCreature*)local_8)->fC = typeHash;
        ((EditorCreature*)local_8)->f10 = p[2];
        *out = (int)local_8;
        return true;
    }
    ReleaseRef(local_8);
    return false;
}

// @ 0x004bc540
bool cSPEditorResourceFactory::ReadResource(StreamObject_s004b_bfb0* stream, uint32_t param_2, uint32_t param_3, int typeHash)
{
    if (typeHash != 0xf43029a) {
        if (typeHash != 0x3d97a8e4 && typeHash != 0x2b978c46 && typeHash != 0x2399be55 &&
            typeHash != 0x24682294 && typeHash != 0x476a98c7 && typeHash != 0x438f6347)
            return false;
        int* p = stream->v10();
        int data = stream->v18(param_2, p[1]);
        bool ok = ReadResourceFromStream((StreamObject_s004b_bfb0*)data, param_2, p[1]);
        return ok;
    }
    int handle = (int)FUN_004c0500(param_2);
    bool ok = false;
    if (handle != 0) {
        int data = stream->v18(handle, 0);
        if (ReadRuntimeCreatureData(data, handle))
            ok = true;
    }
    FUN_006ac0a0(0xb, param_2);
    return ok;
}

// @ 0x004bc620
bool cSPEditorResourceFactory::WriteResource(StreamObject_s004b_bfb0* stream, uint32_t param_1, uint32_t param_2, int typeHash)
{
    (void)param_2;
    WriteTarget* target = (WriteTarget*)(uint32_t)param_1;
    if (typeHash == 0xf43029a) {
        int handle = (int)FUN_004c0500((uint32_t)stream);
        bool ok = false;
        if (handle != 0) {
            int data = target->v18(handle);
            if (WriteRuntimeCreatureData((int*)data, handle))
                ok = true;
        }
        return ok;
    }
    bool bakeable = SetAssetData((uint32_t)typeHash, 0);
    if (!bakeable && typeHash != 0x1a99b06b)
        return false;
    int data = target->v18((int)stream, typeHash);
    return WriteResourceToStream((int*)data, (int)stream, typeHash) != 0;
}

// @ 0x004bc6d0
bool cSPEditorResourceFactory::ReadResourceFromStream(StreamObject_s004b_bfb0* stream, uint32_t key, int typeHash)
{
    int data = WriteBinaryEditorModel(key);
    if (data == 0)
        return false;
    if (typeHash == 0x1a99b06b)
        return ReadBinaryEditorModel(stream, key);
    cEditorModelParser_s004b_bfb0 parser;
    parser.mpBufferInfo = 0;
    parser.Create(parser.mBuffer, 15000, 0);
    parser.FUN_004bd9f0(data);
    bool ok = true;
    bool done = false;
    while (ok && !done) {
        int n = parser.FUN_004bdc00(0x200);
        if (n == 0) {
            ok = false;
        } else {
            int got = stream->v30((int*)n, 0x200);
            done = got != 0x200;
            if (got == -1 || !parser.FUN_004bdc60((int*)n, got, done))
                ok = false;
        }
    }
    if (ok)
        ok = parser.FUN_004be5d0();
    parser.FUN_004bdae0();
    if (parser.mpBufferInfo != 0 && (parser.mpBufferInfo[1].mSignature & 0x40000000) != 0)
        parser.destroy_shared();
    parser.mpBufferInfo = 0;
    return ok;
}

// @ 0x004bc8a0
namespace EA { namespace Allocator {
FixedBufferAllocator_s004b_bfb0* FixedBufferAllocator_s004b_bfb0::Create(void* pBuffer, uint32_t size, uint8_t bShared)
{
    mpBufferInfo = (buffer_info*)pBuffer;
    if (mpBufferInfo != 0 && size >= 0x24) {
        if (bShared == 0 || !IsValid()) {
            mpBufferInfo->mSignature = 0x86421357;
            mpBufferInfo->mSize = size - 0x10;
            int* tmp;
            buffer_info* t14 = (buffer_info*)((char*)mpBufferInfo + 0x10);
            t14->mSignature = 8;
            t14->mSize = 0;
            if (bShared != 0)
                t14->mSignature |= 0x40000000;
            tmp = (int*)((t14->mSignature & 0x3fffffff) + (char*)t14);
            *tmp = mpBufferInfo->mSize - 8;
            tmp[1] = (int)t14;
            mpBufferInfo->mSizeFree = mpBufferInfo->mSize - 8;
            mpBufferInfo->mpFirstFree = tmp;
        }
    } else {
        mpBufferInfo = 0;
    }
    return this;
}
}}  // namespace EA::Allocator

// @ 0x004bc990
namespace EA { namespace Allocator {
bool FixedBufferAllocator_s004b_bfb0::IsValid()
{
    if (mpBufferInfo->mSignature == 0x86421357 &&
        mpBufferInfo->mSizeFree < mpBufferInfo->mSize &&
        mpBufferInfo->mSizeFree > 0 &&
        mpBufferInfo->mSize > 0 &&
        (uint32_t)mpBufferInfo->mpFirstFree > (uint32_t)((char*)mpBufferInfo + 0x10) &&
        (uint32_t)mpBufferInfo->mpFirstFree < (uint32_t)((char*)mpBufferInfo + 0x10 + mpBufferInfo->mSize))
        return true;
    return false;
}
}}  // namespace EA::Allocator

// @ 0x004bca10
namespace EA { namespace Allocator {
void FixedBufferAllocator_s004b_bfb0::destroy_shared()
{
    for (uint32_t* p = (uint32_t*)((char*)&mpBufferInfo[1] + (mpBufferInfo[1].mSignature & 0x3fffffff));
         p < (uint32_t*)((char*)&mpBufferInfo[1] + mpBufferInfo->mSize);
         p = (uint32_t*)((*p & 0x3fffffff) + (char*)p)) {
        if ((int)*p < 0) {
            FixedBufferAllocator_s004b_bfb0* owner;
            if ((*p & 0x40000000) == 0)
                owner = 0;
            else
                owner = *(FixedBufferAllocator_s004b_bfb0**)((char*)p + (*p & 0x3fffffff) - 4);
            if (owner == this)
                Free(p + 2);
        }
    }
}
}}  // namespace EA::Allocator

// @ 0x004bcab0
namespace EA { namespace Allocator {
void FixedBufferAllocator_s004b_bfb0::Free(void* p)
{
    if (mpBufferInfo == 0) {
        g_pGlobalAllocator->Free(p);
        return;
    }
    bool inRange =
        !((char*)p < (char*)mpBufferInfo + 0x10) &&
        (char*)p < (char*)mpBufferInfo + 0x10 + mpBufferInfo->mSize;
    if (!inRange) {
        g_pGlobalAllocator->Free(p);
        return;
    }
    int* h = (int*)((char*)p - 8);
    if (*h < 0) {
        FixedBufferAllocator_s004b_bfb0* owner;
        if ((*h & 0x40000000) == 0)
            owner = 0;
        else
            owner = *(FixedBufferAllocator_s004b_bfb0**)((char*)h + (*h & 0x3fffffff) - 4);
        if (owner == this) {
            *h &= 0x3fffffff;
            if ((char*)mpBufferInfo->mpFirstFree > (char*)h)
                mpBufferInfo->mpFirstFree = h;
            mpBufferInfo->mSizeFree += (*h & 0x3fffffff);
        }
    }
    int* first = (int*)((char*)mpBufferInfo + 0x10);
    if ((*first & 0x3fffffff) > 0x30) {
        int* next = (int*)((char*)first + (*first & 0x3fffffff));
        int* block = (int*)((char*)first + 8);
        *block = (*first & 0x3fffffff) - 8;
        *first = (*first & 0xc0000000) | 8;
        next[1] = (int)block;
        block[1] = (int)first;
        mpBufferInfo->mpFirstFree = block;
        mpBufferInfo->mSizeFree += *block;
    }
}
}}  // namespace EA::Allocator

// @ 0x004bcc50
namespace SP {
bool cSPEditorResourceFactory_s004b_cc50::WriteResourceToStream(IStream* stream, int model, int modelTypeHash)
{
    EditorModelData* data = WriteBinaryEditorModel_s004b_cc50(model);
    if (!data)
        return false;

    bool ok = true;
    if (modelTypeHash == 0x1a99b06b) {
        ok = FUN_004bfb20(stream, model);
    } else {
        FixedWString blockId;
        ScratchSlots<3>();
        XmlTextWriter_s004b_cc50 xml(1, 0);
        xml.SetOutputStream(stream, 1);
        xml.WriteXmlHeader();
        xml.BeginElement(L"sporemodel");
        XmlWriteUInt(&xml, L"formatversion", 0x12);

        xml.BeginElement(L"properties");
        ModelProperties* props = &data->mProperties;
        XmlWriteHex(&xml, L"modeltype", props->mModelType);
        if (props->mSkinEffect[0] != 0xcdcdcdcd &&
            (props->mSkinEffect[0] != 0 || props->mSkinEffect[1] != 0 || props->mSkinEffect[2] != 0))
        {
            XmlWriteHex(&xml, L"skineffect1", props->mSkinEffect[0]);
            XmlWriteHex(&xml, L"skineffect2", props->mSkinEffect[1]);
            XmlWriteHex(&xml, L"skineffect3", props->mSkinEffect[2]);
            XmlWriteUInt(&xml, L"skineffectseed1", props->mSkinEffectSeed[0]);
            XmlWriteUInt(&xml, L"skineffectseed2", props->mSkinEffectSeed[1]);
            XmlWriteUInt(&xml, L"skineffectseed3", props->mSkinEffectSeed[2]);
            XmlWriteVector3(&xml, L"skincolor1", &props->mSkinColor1[0]);
            XmlWriteVector3(&xml, L"skincolor2", &props->mSkinColor2[0]);
            XmlWriteVector3(&xml, L"skincolor3", &props->mSkinColor3[0]);
        }
        XmlWriteUInt(&xml, L"zcorpscore", props->mZCorpScore);
        xml.EndElement(L"properties");

        int count = data->mBlocks.size();
        xml.BeginElement(L"blocks");
        xml.AppendAttributeF(L"count", L"%d", count);

        // first[parent] / next[child] index lists (-1 terminated)
        IntFixedVector first(count, -1);
        IntFixedVector next(count, -1);
        ScratchSlots<8>();
        for (int i = 0; i < count; i++) {
            EditorBlock* block = &data->mBlocks[i];
            uint32_t parent = block->mParent;
            if (parent < (uint32_t)count && parent != (uint32_t)i) {
                next[i] = first[parent];
                first[parent] = i;
            }
        }

        for (int blockIndex = 0; blockIndex < count; blockIndex++) {
            EditorBlock* pBlock = &data->mBlocks[blockIndex];
            xml.BeginElement(L"blockref");
            blockId.sprintf(L"0x%08x, 0x%08x", pBlock->mBlockID[0], pBlock->mBlockID[1]);
            XmlWriteElement(&xml, L"blockid", blockId.c_str());

            xml.BeginElement(L"transform");
            if (pBlock->mLimbType != 3) {
                XmlWriteUInt(&xml, L"limbtype", pBlock->mLimbType);
                XmlWriteFloat(&xml, L"musclescale", pBlock->mMuscleScale);
            }
            if (pBlock->mBaseMuscleScale != 0.0f)
                XmlWriteFloat(&xml, L"basemusclescale", pBlock->mBaseMuscleScale);
            XmlWriteFloat(&xml, L"scale", pBlock->mScale);
            XmlWriteVector3(&xml, L"position", &pBlock->mPosition[0]);
            XmlWriteVector3(&xml, L"triangledirection", &pBlock->mTriangleDirection[0]);
            XmlWriteVector3(&xml, L"trianglepickorigin", &pBlock->mTrianglePickOrigin[0]);
            xml.BeginElement(L"orientation");
            XmlWriteVector3(&xml, L"row0", &pBlock->mOrientation[0][0]);
            XmlWriteVector3(&xml, L"row1", &pBlock->mOrientation[1][0]);
            XmlWriteVector3(&xml, L"row2", &pBlock->mOrientation[2][0]);
            xml.EndElement(L"orientation");
            if (pBlock->mUserOrientation != g_UserOrientationIdentity) {
                xml.BeginElement(L"userorientation");
                XmlWriteVector3(&xml, L"userorientation_row0", &pBlock->mUserOrientation[0][0]);
                XmlWriteVector3(&xml, L"userorientation_row1", &pBlock->mUserOrientation[1][0]);
                XmlWriteVector3(&xml, L"userorientation_row2", &pBlock->mUserOrientation[2][0]);
                xml.EndElement(L"userorientation");
            }
            xml.EndElement(L"transform");
            XmlWriteBool(&xml, L"snapped", pBlock->mbSnapped != 0);

            if (pBlock->mPaintCount > 0) {
                xml.BeginElement(L"paintlist");
                xml.AppendAttributeF(L"count", L"%d", pBlock->mPaintCount);
                for (int pi = 0, nPaint = pBlock->mPaintCount; pi < nPaint; pi++) {
                    xml.BeginElement(L"paint");
                    XmlWriteHex(&xml, L"paintregion", pBlock->mPaintRegions[pi]);
                    XmlWriteHex(&xml, L"paintid", pBlock->mPaintIDs[pi]);
                    XmlWriteVector3(&xml, L"color1", &pBlock->mPaintColor1[pi][0]);
                    XmlWriteVector3(&xml, L"color2", &pBlock->mPaintColor2[pi][0]);
                    xml.EndElement(L"paint");
                }
                xml.EndElement(L"paintlist");
            }

            int nChildren = 0;
            for (int child = first[blockIndex]; nChildren < count && child != -1; child = next[child])
                nChildren++;
            if (nChildren > 0 && nChildren < count) {
                xml.BeginElement(L"childlist");
                xml.AppendAttributeF(L"count", L"%d", nChildren);
                for (int c = first[blockIndex]; c != -1; c = next[c])
                    XmlWriteUInt(&xml, L"childid", c);
                xml.EndElement(L"childlist");
            }

            uint32_t nSym = pBlock->mSymmetric;
            if (nSym < (uint32_t)count && nSym != (uint32_t)blockIndex)
                XmlWriteUInt(&xml, L"symmetric", nSym);

            if (pBlock->mHandleCount > 0) {
                xml.BeginElement(L"handles");
                xml.AppendAttributeF(L"count", L"%d", pBlock->mHandleCount);
                for (int h = 0; h < (int)pBlock->mHandleCount; h++) {
                    wchar_t buf[64];
                    FormatFloat(buf, pBlock->mHandleWeights[h]);
                    int value = pBlock->mHandleChannels[h];
                    xml.BeginElement(L"weight");
                    if (value != 0)
                        xml.AppendAttributeF(L"channel", L"0x%08x", value);
                    xml.WriteCharData(buf);
                    xml.EndElement(L"weight");
                }
                xml.EndElement(L"handles");
            }

            XmlWriteBool(&xml, L"isasymmetric", pBlock->mbIsAsymmetric != 0);
            xml.EndElement(L"blockref");
        }

        xml.EndElement(L"blocks");
        ok = xml.EndElement(L"sporemodel");
    }
    return ok;
}
}  // namespace SP

// @ 0x004bd9c0
int FUN_004bd9c0(int param)
{
    switch (param) {
    case 0x5e49ce2c: return 0xd05c53a3;
    default: return param;
    }
}

// @ 0x004bd9f0
void cEditorModelParser::FUN_004bd9f0(int param)
{
    g_pCurrentParser = this;
    mpXMLParser = FUN_0090aed0(0, PTR_FUN_0150c50c, 0);
    FUN_009032e0(mpXMLParser, this);
    FUN_00903300(mpXMLParser, (void*)StartElementCb, (void*)EndElementCb);
    FUN_00903320(mpXMLParser, (void*)CharDataCb);
    g_pCurrentParser = 0;
    m3aa0 = param;
    m3aa4 = -1;
    m3aa8 = 0;
    mLength = 0;
    mCursor = 0;
}

// @ 0x004bdae0
void cEditorModelParser::FUN_004bdae0()
{
    if (mpXMLParser != 0) {
        g_pCurrentParser = this;
        FUN_009055d0(mpXMLParser);
        mpXMLParser = 0;
        g_pCurrentParser = 0;
        FBAStub* fba = (FBAStub*)this;
        if (fba->mpBufferInfo != 0 &&
            (*(int*)((char*)fba->mpBufferInfo + 0x10) & 0x40000000) != 0)
            fba->destroy_shared();
        fba->mpBufferInfo = 0;
        fba->Create((char*)this + 4, 0x3a98, 0);
    }
    m3aa0 = 0;
}

// @ 0x004bdbd0
int cEditorModelParser::FUN_004bdbd0()
{
    if (mpXMLParser)
        return FUN_00903b40(mpXMLParser);
    return -1;
}

// @ 0x004bdc00
int cEditorModelParser::FUN_004bdc00(int param)
{
    g_pCurrentParser = this;
    int result = FUN_00903400(mpXMLParser, param);
    g_pCurrentParser = 0;
    return result;
}

// @ 0x004bdc60
bool cEditorModelParser::FUN_004bdc60(int a, int b, uint8_t c)
{
    g_pCurrentParser = this;
    bool result = FUN_00905740(mpXMLParser, a, b, c) == 1;
    g_pCurrentParser = 0;
    return result;
}

// @ 0x004bdcd0
void cEditorModelParser_StartElement(void* userData, const wchar_t* name, const wchar_t** atts)
{
    cEditorModelParser* nCount = (cEditorModelParser*)userData;
    unsigned long p15;
    const wchar_t** hi;
    const wchar_t* t22;
    const wchar_t* t26;
    const wchar_t** item;

    nCount->mBuffer[0] = 0;
    nCount->mLength = 0;
    nCount->mCursor = 0;
    if (wcscmp(name, L"blockref") == 0) {
        if (nCount->m3aa8 < 0x100) {
            nCount->m3aa4 = nCount->m3aa8;
            nCount->m3aa8 = nCount->m3aa8 + 1;
            ((ParserBlockOps*)nCount)->AddBlock(nCount->m3aa4);
        } else {
            FUN_00903550(nCount->mpXMLParser, 0);
        }
    } else if (wcscmp(name, L"blocks") == 0) {
        t22 = L"0";
        do {
            for (hi = atts; hi[0] && hi[1]; hi += 2) {
                if (wcscmp(hi[0], L"p15") == 0) {
                    t22 = hi[1];
                    break;
                }
            }
        } while (0);
        p15 = wcstoul(t22, 0, 0);
        if (p15 <= 0x100)
            ((ParserModelBlocks*)((char*)nCount->m3aa0 + 0x98))->Reserve(p15);
        else
            FUN_00903550(nCount->mpXMLParser, 0);
    } else if (wcscmp(name, L"weight") == 0) {
        t26 = L"0";
        do {
            for (item = atts; item[0] && item[1]; item += 2) {
                if (wcscmp(item[0], L"channel") == 0) {
                    t26 = item[1];
                    break;
                }
            }
        } while (0);
        nCount->m3aac = wcstoul(t26, 0, 0);
    }
}

// @ 0x004be070
void FUN_004be070(void* self, const void* src, int n)
{
    void* p = self;
    if ((uint32_t)(*(int*)((char*)p + 0x42b0) + n) > 0x3ff)
        n = 0x3ff - *(int*)((char*)p + 0x42b0);
    void* dst = (char*)p + *(int*)((char*)p + 0x42b0) * 2 + 0x3ab0;
    memcpy_impl(dst, src, n * 2);
    *(int*)((char*)p + 0x42b0) = *(int*)((char*)p + 0x42b0) + n;
    *(uint16_t*)((char*)p + *(int*)((char*)p + 0x42b0) * 2 + 0x3ab0) = 0;
}

// @ 0x004be100
void FUN_004be100(void* userData, const wchar_t* name)
{
    cEditorModelParser* self = (cEditorModelParser*)userData;
    uint32_t hash = EA_Hash_FNV1_String16(name, 0x811c9dc5, 0);

    EditorModelElem* data = g_editorModelElems;
    EditorModelElem* end  = data + 36;
    bool ordered = false;
    bool ok;
    int  target;
    EditorModelElem* item = FUN_004c0600(data, end, &hash, ordered);

    for (; item != end && item->mHash == hash; ++item) {
        if (wcscmp(item->mpName, name) == 0) {
            target = 0;
            if (item->mKind == 0) {
                if (self->m3aa4 == -1)
                    target = self->m3aa0 + 0x18;
            } else {
                if (self->m3aa4 != -1)
                    target = self->m3aa4 * 0x1d8 + *(int*)(self->m3aa0 + 0x98);
            }
            ok = (target != 0) && (item->mpFn(self, (char*)target + item->mOffset, item->mpArg) != 0);
            if (!ok) {
                FUN_00903550(self->mpXMLParser, 0);
                return;
            }
            break;
        }
    }
    self->mBuffer[0] = 0;
    self->mLength = 0;
    self->mCursor = 0;
}

// @ 0x004be2e0
bool cEditorModelParser::ReadFloat(float* out)
{
    wchar_t* local_4 = (wchar_t*)((char*)mBuffer + mCursor * 2);
    *out = FUN_0092ddc0((wchar_t*)((char*)mBuffer + mCursor * 2), &local_4);
    if (local_4 == (wchar_t*)((char*)mBuffer + mCursor * 2))
        return false;
    if (*local_4 == L',')
        local_4++;
    mCursor = (int)((char*)local_4 - (char*)mBuffer) >> 1;
    return true;
}

// @ 0x004be380
bool cEditorModelParser::ReadULong(unsigned long* out)
{
    wchar_t* local_8 = (wchar_t*)((char*)mBuffer + mCursor * 2);
    *out = wcstoul((wchar_t*)((char*)mBuffer + mCursor * 2), &local_8, 0);
    if (local_8 == (wchar_t*)((char*)mBuffer + mCursor * 2))
        return false;
    if (*local_8 == L',')
        local_8++;
    mCursor = (int)((char*)local_8 - (char*)mBuffer) >> 1;
    return true;
}

// @ 0x004be420
void ParserBlockOps::AddBlock(int index)
{
    ModelBlockVec* pVec = (ModelBlockVec*)(((cEditorModelParser*)this)->m3aa0 + 0x98);
    int count = (pVec->mpEnd - pVec->mpBegin) / 0x1d8;
    if (count <= index) {
        int newCount = index + 1;
        pVec->Reserve(newCount);
        ModelBlock* base = (ModelBlock*)pVec->mpBegin;
        memset_impl((char*)base + count * 0x1d8, 0, (newCount - count) * 0x1d8);
        for (int i = count; i < newCount; ++i) {
            ModelBlock* e = &base[i];
            e->mField00 = -1;
            e->mField04 = -1;
            e->mField08 = -1;
            e->mField0C = -1;
            e->mMatrix[0][0] = HK_REAL_ONE;
            e->mMatrix[1][1] = HK_REAL_ONE;
            e->mMatrix[2][2] = HK_REAL_ONE;
            e->mField84 = 3;
        }
    }
}

// @ 0x004be5d0
bool XmlParseContext::Validate()
{
    ParseElem* data = mpData->mElems.mpBegin;
    int count = mpData->mElems.size();
    bool foundRoot = false;
    for (int j = 0; j < count; j++) {
        if (data[j].mType == -1)
            return false;
        if (data[j].mParent == -1)
            foundRoot = true;
        if (data[j].mPartner == j)
            return false;
        if (data[j].mPartner != -1 && data[data[j].mPartner].mPartner != j)
            return false;
        if (data[j].mScale < 1.5258789e-05f)
            return false;
        if (data[j].GetAxis(0).LengthSquared() < 0.9f)
            return false;
        if (data[j].GetAxis(1).LengthSquared() < 0.9f)
            return false;
        if (data[j].GetAxis(2).LengthSquared() < 0.9f)
            return false;
    }
    if (!foundRoot)
        return false;
    return true;
}

// @ 0x004be820
bool ParseBoolAttr(XmlParseContext* ctx, void* out, int size)
{
    int value = wcscmp(ctx->mText, L"true") == 0;
    if (size == 4)
        *(int*)out = value;
    else if (size == 1)
        *(uint8_t*)out = (uint8_t)value;
    else
        return false;
    return true;
}

// @ 0x004be8d0
bool ParseUIntAttr(XmlParseContext* ctx, void* out, int size)
{
    return size == 4 && ctx->ParseUInt((uint32_t*)out);
}

// @ 0x004be910
bool ParseFloatAttr(XmlParseContext* ctx, void* out, int size)
{
    return size == 4 && ctx->ParseFloat((float*)out);
}

// @ 0x004be950
bool ParseVector3Attr(XmlParseContext* ctx, void* out, int size)
{
    float* v = (float*)out;
    return size == 12 && ctx->ParseFloat(v) && ctx->ParseFloat(v + 1) && ctx->ParseFloat(v + 2);
}

// @ 0x004be9c0
bool ParseKindAndType(XmlParseContext* ctx)
{
    ParseElem* node = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    uint32_t kind = (uint32_t)-1;
    uint32_t type = (uint32_t)-1;
    if (!ctx->ParseUInt(&kind) || !ctx->ParseUInt(&type))
        return false;
    node->mKind = MapKind(kind);
    node->mType = MapType(type);
    return true;
}

// @ 0x004bea50
bool ParseChild(XmlParseContext* ctx)
{
    uint32_t index = (uint32_t)-1;
    if (!ctx->ParseUInt(&index) || index >= 0x100)
        return false;
    ctx->SelectElement(index);
    ParseElem* child = &ctx->mpData->mElems.mpBegin[index];
    if (child->mParent != -1)
        return false;
    child->mParent = ctx->mCurrent;
    return true;
}

// @ 0x004bead0
bool ParseValue(XmlParseContext* ctx)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumValues >= 8)
        return false;
    if (!ctx->ParseFloat(&elem->mValues[elem->mNumValues]))
        return false;
    elem->mValueIds[elem->mNumValues] = ctx->mCurrentId;
    elem->mNumValues++;
    return true;
}

// @ 0x004beb70
bool ParseSlotUInt(XmlParseContext* ctx, char* out, int stride)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumSlots >= 8)
        return false;
    return ParseUIntAttr(ctx, out + stride * elem->mNumSlots, stride);
}

// @ 0x004bebd0
bool ParseSlotVector3(XmlParseContext* ctx, char* out, int stride)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumSlots >= 8)
        return false;
    return ParseVector3Attr(ctx, out + stride * elem->mNumSlots, stride);
}

// @ 0x004bec30
bool EndSlot(XmlParseContext* ctx)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumSlots >= 8)
        return false;
    elem->mNumSlots++;
    return true;
}

// @ 0x004beca0
wchar_t* FormatFloat(wchar_t* buf, float value)
{
    FloatBits bits;
    bits.f = value;
    if (IsNaN(value))
        wcscpy(buf, (bits.u & 0x80000000) ? L"-nan" : L"nan");
    else if (IsInf(value))
        wcscpy(buf, (bits.u & 0x80000000) ? L"-inf" : L"inf");
    else
        FtoaEnglish16(value, buf, 64, 6, true);
    return buf;
}

// @ 0x004bede0
bool XmlWriteElement(IXmlWriter* writer, const wchar_t* name, const wchar_t* text)
{
    return writer->BeginElement(name) && writer->WriteText(text) && writer->EndElement(name);
}

// @ 0x004bee50
bool XmlWriteBool(IXmlWriter* writer, const wchar_t* name, bool value)
{
    return XmlWriteElement(writer, name, value ? L"true" : L"false");
}

// @ 0x004bee90
bool XmlWriteUInt(IXmlWriter* writer, const wchar_t* name, unsigned long value)
{
    wchar_t buf[20];
    return XmlWriteElement(writer, name, _ultow(value, buf, 10));
}

// @ 0x004beec0
bool XmlWriteHex(IXmlWriter* writer, const wchar_t* name, uint32_t value)
{
    wchar_t buf[11];
    buf[0] = L'0';
    buf[1] = L'x';
    buf[10] = 0;
    for (int i = 9; i >= 2; i--, value >>= 4)
        buf[i] = (wchar_t)(((value & 0xF) < 10 ? L'0' : L'a' - 10) + (value & 0xF));
    return XmlWriteElement(writer, name, buf);
}

// @ 0x004bef40
bool XmlWriteFloat(IXmlWriter* writer, const wchar_t* name, float value)
{
    wchar_t buf[64];
    return XmlWriteElement(writer, name, FormatFloat(buf, value));
}

// @ 0x004bef80
bool XmlWriteVector3(IXmlWriter* writer, const wchar_t* name, const Vector3_s004b_e5d0& v)
{
    wchar_t buf[64];
    return writer->BeginElement(name) &&
           writer->WriteText(FormatFloat(buf, v.x)) && writer->WriteText(L" ") &&
           writer->WriteText(FormatFloat(buf, v.y)) && writer->WriteText(L" ") &&
           writer->WriteText(FormatFloat(buf, v.z)) &&
           writer->EndElement(name);
}

// @ 0x004bf0a0
bool WriteRLE(IStream_s004b_e5d0* stream, const uint8_t* data, uint32_t size)
{
    uint8_t buffer[2048];
    uint8_t* dst = buffer;
    const uint8_t* p = data;
    const uint8_t* end = data + size;
    uint8_t lastByte = 0;
    while (p < end) {
        if (dst + 2 > buffer + sizeof(buffer)) {
            uint16_t len = (uint16_t)(dst - buffer);
            if (!stream->Write(&len, 2) || !stream->Write(buffer, dst - buffer))
                return false;
            dst = buffer;
        }
        uint32_t repeat = 0;
        uint32_t maxRun = end - p < 0xFF ? end - p : 0xFF;
        while (repeat < maxRun && p[repeat] == lastByte)
            repeat++;
        if (repeat > 2) {
            *dst = 0xFE;
            dst++;
            *dst = (uint8_t)repeat;
            dst++;
            p += repeat;
        } else {
            *dst = *p;
            lastByte = *dst;
            dst++;
            p++;
            if (lastByte == 0xFE) {
                *dst = 0;
                dst++;
            }
        }
    }
    if (dst > buffer) {
        uint16_t len = (uint16_t)(dst - buffer);
        if (!stream->Write(&len, 2) || !stream->Write(buffer, dst - buffer))
            return false;
    }
    return true;
}

// @ 0x004bf2a0
bool ReadRLE(IStream_s004b_e5d0* stream, uint8_t* data, uint32_t size)
{
    uint8_t buf[2048];
    uint8_t* in = buf + sizeof(buf);
    uint8_t* dst = data;
    uint8_t* limit = data + size;
    uint8_t fill = 0;
    while (dst < limit) {
        if (in == buf + sizeof(buf)) {
            uint16_t len;
            if (stream->Read(&len, 2) != 2)
                return false;
            if (len < 1 || len > sizeof(buf))
                return false;
            in = buf + sizeof(buf) - len;
            if (stream->Read(in, len) != len)
                return false;
        }
        if (*in == 0xFE) {
            in++;
            if (in >= buf + sizeof(buf))
                return false;
            if (*in != 0) {
                uint8_t n = *in;
                if (n > limit - dst)
                    return false;
                memset(dst, fill, n);
                dst += n;
            } else {
                *dst = 0xFE;
                fill = 0xFE;
                dst++;
            }
        } else {
            *dst = *in;
            fill = *dst;
            dst++;
        }
        in++;
    }
    return true;
}

// @ 0x004bf430
bool FUN_004bf430(int* stream, int data)
{
    ChunkHeader header;
    uint32_t nPayload;
    ChunkCounts counts;

    if (((IStream_s004b_f430*)stream)->Read(&header, 8) != 8
        || header.mMagic != 0xabb455b7 || header.mVersion < 9 || header.mVersion > 10)
        return false;
    if (header.mVersion >= 10) {
        if (((IStream_s004b_f430*)stream)->Read(&counts, 0x10) != 0x10)
            return false;
    } else {
        if (((IStream_s004b_f430*)stream)->Read(&counts, 0xc) != 0xc)
            return false;
        counts.mNumBones = 0;
    }
    if (counts.mNumElements > 0x100 || counts.mNumValues > 0x1000 || counts.mNumFloats > 0x400)
        return false;
    ScratchSlots_s004b_f430<10>();
    ((CreatureData*)data)->mElements.resize(counts.mNumElements);
    ScratchSlots_s004b_f430<10>();
    ((CreatureData*)data)->mValues.resize(counts.mNumValues);
    ScratchSlots_s004b_f430<10>();
    ((CreatureData*)data)->mValueBytes.resize(counts.mNumValues);
    ScratchSlots_s004b_f430<10>();
    ((CreatureData*)data)->mScalars.resize(counts.mNumFloats);
    ScratchSlots_s004b_f430<10>();
    ((CreatureData*)data)->mFloats0.resize(counts.mNumFloats);
    ScratchSlots_s004b_f430<10>();
    ((CreatureData*)data)->mFloats1.resize(counts.mNumFloats);
    ScratchSlots_s004b_f430<10>();
    ((CreatureData*)data)->mBones.resize(counts.mNumBones);
    memset(((CreatureData*)data)->mPayload, 0, 0x80);
    nPayload = 0x80;
    if (header.mVersion < 8)
        nPayload -= 0x3c;
    if (!ReadRLE((IStream_s004b_f430*)stream, ((CreatureData*)data)->mPayload, nPayload))
        return false;
    if (((IStream_s004b_f430*)stream)->Read(((CreatureData*)data)->mElements.begin(),
                                 counts.mNumElements * 0x8c) != counts.mNumElements * 0x8c)
        return false;
    if (((IStream_s004b_f430*)stream)->Read(((CreatureData*)data)->mValues.begin(),
                                 counts.mNumValues * 4) != counts.mNumValues * 4)
        return false;
    if (((IStream_s004b_f430*)stream)->Read(((CreatureData*)data)->mValueBytes.begin(),
                                 counts.mNumValues) != counts.mNumValues)
        return false;
    if (((IStream_s004b_f430*)stream)->Read(((CreatureData*)data)->mScalars.begin(),
                                 counts.mNumFloats * 4) != counts.mNumFloats * 4)
        return false;
    if (((IStream_s004b_f430*)stream)->Read(((CreatureData*)data)->mFloats0.begin(),
                                 counts.mNumFloats * 4) != counts.mNumFloats * 4)
        return false;
    if (((IStream_s004b_f430*)stream)->Read(((CreatureData*)data)->mFloats1.begin(),
                                 counts.mNumFloats * 4) != counts.mNumFloats * 4)
        return false;
    if (((IStream_s004b_f430*)stream)->Read(&((CreatureData*)data)->mFlags, 4) != 4)
        return false;
    if (header.mVersion >= 10) {
        if (((IStream_s004b_f430*)stream)->Read(((CreatureData*)data)->mBones.begin(),
                                     counts.mNumBones * 0x38) != counts.mNumBones * 0x38)
            return false;
    }
    return true;
}

// @ 0x004bf770
bool FUN_004bf770(int* stream, int data)
{
    ChunkHeader header;
    ChunkCounts counts;

    header.mMagic = 0xabb455b7;
    header.mVersion = 10;
    counts.mNumElements = ((CreatureData*)data)->mElements.size();
    counts.mNumValues = ((CreatureData*)data)->mValues.size();
    counts.mNumFloats = ((CreatureData*)data)->mFloats0.size();
    counts.mNumBones = ((CreatureData*)data)->mBones.size();
    if (!((IStream_s004b_f430*)stream)->Write(&header, 8)
        || !((IStream_s004b_f430*)stream)->Write(&counts, 0x10))
        return false;
    if (!WriteRLE((IStream_s004b_f430*)stream, ((CreatureData*)data)->mPayload, 0x80))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(((CreatureData*)data)->mElements.begin(),
                                   counts.mNumElements * 0x8c))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(((CreatureData*)data)->mValues.begin(),
                                   counts.mNumValues * 4))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(((CreatureData*)data)->mValueBytes.begin(),
                                   counts.mNumValues))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(((CreatureData*)data)->mScalars.begin(),
                                   counts.mNumFloats * 4))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(((CreatureData*)data)->mFloats0.begin(),
                                   counts.mNumFloats * 4))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(((CreatureData*)data)->mFloats1.begin(),
                                   counts.mNumFloats * 4))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(&((CreatureData*)data)->mFlags, 4))
        return false;
    if (!((IStream_s004b_f430*)stream)->Write(((CreatureData*)data)->mBones.begin(),
                                   counts.mNumBones * 0x38))
        return false;
    return true;
}

// @ 0x004bf9f0
bool FUN_004bf9f0(StreamReader* r, int data)
{
    int buf = WriteBinaryEditorModel(data);
    if (buf == 0)
        return false;
    int local_1c;
    uint32_t local_18;
    if (r->v30(&local_1c, 8) != 8)
        return false;
    if (local_1c != 0x48657ed3 || local_18 <= 2 || local_18 >= 6)
        return false;
    uint32_t local_c, local_8;
    if (r->v30(&local_c, 8) != 8)
        return false;
    if (local_c >= 0x401 || local_8 >= 0x81)
        return false;
    FUN_004afd00(local_c);
    operator_new__((void*)(buf + 0x18), 0, 0x80);
    int n = (local_18 < 5) ? 0x44 : 0x80;
    if (!FUN_004bf2a0(r, buf + 0x18, n))
        return false;
    if (!FUN_004bf2a0(r, *(int*)(buf + 0x98), local_c * 0x1d8))
        return false;
    return true;
}

// @ 0x004bfb20
bool FUN_004bfb20(StreamWriter* w, int data)
{
    int buf = WriteBinaryEditorModel(data);
    if (buf != 0) {
        int header[2];
        header[0] = 0x48657ed3;
        header[1] = 5;
        int local_c[2];
        local_c[0] = (*(int*)(buf + 0x9c) - *(int*)(buf + 0x98)) / 0x1d8;
        local_c[1] = 0;
        if (w->v38(header, 8) && w->v38(local_c, 8)) {
            if (!FUN_004bf0a0(w, buf + 0x18, 0x80))
                return false;
            if (!FUN_004bf0a0(w, *(int*)(buf + 0x98), local_c[0] * 0x1d8))
                return false;
            return true;
        }
    }
    return false;
}

// @ 0x004bfc10
void FUN_004bfc10(void* p)
{
    FixedBufferAllocatorStub* fba = (FixedBufferAllocatorStub*)g_tls_current;
    fba->Malloc((uint32_t)p, 4);
}

// @ 0x004bfc40
void* FixedBufferAllocatorStub::Malloc(uint32_t nSize, uint32_t nAlignment)
{
    char* i;
    int n40;
    block_header* n1;
    int n16;
    block_header* v40;
    block_header* list;
    block_header* g;
    int p23;
    int owner;
    uint32_t t33;
    int node;
    block_header* alloc;

    n40 = ((nSize + 3) & 0xfffffffc) + 8 + ((mpBufferInfo[1].mSignature & FBA_TRAILER) ? 4 : 0);
    if (IsInitialized() && mpBufferInfo->mSizeFree >= n40) {
        i = (char*)mpBufferInfo + 0x10 + mpBufferInfo->mSize;
        if (n40 > 8) {
            n1 = (block_header*)mpBufferInfo->mpFirstFree;
            n16 = 0;
            while ((char*)n1 < i && n16 + n40 < mpBufferInfo->mSizeFree) {
                if ((int)n1->mSize >= 0) {
                    list = (block_header*)((char*)n1 + (n1->mSize & FBA_MASK));
                    if ((char*)list < i && (int)list->mSize >= 0) {
                        g = (block_header*)((char*)list + (list->mSize & FBA_MASK));
                        if ((char*)g < i)
                            g->mpPrev = n1;
                        n1->mSize = n1->mSize + list->mSize;
                        continue;
                    }
                    n16 = (n1->mSize & FBA_MASK) + n16;
                    v40 = (block_header*)(((uint32_t)n1 + nAlignment + 7 & ~(nAlignment - 1)) - 8);
                    if ((char*)v40 + n40 < (char*)n1 + (n1->mSize & FBA_MASK)) {
                        owner = (int)((char*)v40 - (char*)n1);
                        if (owner > 0) {
                            if (!(mpBufferInfo[1].mSignature & FBA_TRAILER)) {
                                v40->mpPrev = n1->mpPrev;
                                v40->mSize = (n1->mSize & FBA_MASK) - owner;
                                v40->mpPrev->mSize = (v40->mpPrev->mSize & 0xc0000000) | (((v40->mpPrev->mSize & FBA_MASK) + owner) & FBA_MASK);
                            } else {
                                t33 = (n1->mpPrev->mSize & FBA_TRAILER)
                                    ? *(uint32_t*)((n1->mpPrev->mSize & FBA_MASK) + (char*)n1->mpPrev - 4) : 0;
                                v40->mpPrev = n1->mpPrev;
                                v40->mSize = (n1->mSize & FBA_MASK) - owner;
                                v40->mpPrev->mSize = (v40->mpPrev->mSize & 0xc0000000) | (((v40->mpPrev->mSize & FBA_MASK) + owner) & FBA_MASK);
                                if ((int)v40->mpPrev->mSize < 0 || v40->mpPrev == (block_header*)(mpBufferInfo + 1))
                                    mpBufferInfo->mSizeFree = mpBufferInfo->mSizeFree - owner;
                                *(uint32_t*)((v40->mpPrev->mSize & FBA_MASK) + (char*)v40->mpPrev - 4) = t33;
                            }
                        }
                        p23 = (v40->mSize & FBA_MASK) - n40;
                        if (p23 >= 0x28) {
                            v40->mSize = (v40->mSize & 0xc0000000) | ((uint32_t)n40 & FBA_MASK);
                            alloc = (block_header*)((char*)v40 + (v40->mSize & FBA_MASK));
                            alloc->mSize = p23;
                            alloc->mpPrev = v40;
                        }
                        if (mpBufferInfo->mpFirstFree == n1)
                            mpBufferInfo->mpFirstFree = (char*)v40 + (v40->mSize & FBA_MASK);
                        mpBufferInfo->mSizeFree = mpBufferInfo->mSizeFree - (v40->mSize & FBA_MASK);
                        v40->mSize = v40->mSize | FBA_INUSE;
                        if (mpBufferInfo[1].mSignature & FBA_TRAILER) {
                            v40->mSize = v40->mSize | FBA_TRAILER;
                            *(FixedBufferAllocatorStub**)((char*)v40 + (v40->mSize & FBA_MASK) - 4) = this;
                        }
                        return (char*)v40 + 8;
                    }
                }
                n1 = (block_header*)((char*)n1 + (n1->mSize & FBA_MASK));
            }
        } else {
            return (char*)mpBufferInfo + 0x18;
        }
    }
    if (nAlignment < 8)
        return g_pSPMemPool->LockedAlloc(n40, 0, 0, 0, 0, 0);
    return g_pSPMemPool->LockedAligned(n40, nAlignment, 0, 0, 0, 0, 0, 0);
}

// @ 0x004c0020
void* FUN_004c0020(void* p, uint32_t size)
{
    FixedBufferAllocatorStub* fba = (FixedBufferAllocatorStub*)g_tls_current;
    if (p >= (void*)(fba->mpBufferInfo + 1) &&
        p < (void*)((char*)&fba->mpBufferInfo[1] + fba->mpBufferInfo->mSize)) {
        void* dst = fba->Malloc((uint32_t)p, 4);
        uint32_t oldSize = *(uint32_t*)((char*)p - 8) & 0x3fffffff;
        uint32_t n = size < oldSize ? size : oldSize;
        memcpy_impl(dst, p, n);
        fba->Free(p);
        return dst;
    }
    return FUN_00928a80(p, size, 0);
}

// @ 0x004c0130
FactoryObject_s004b_f430* FUN_004c0130()
{
    FactoryObject_s004b_f430* n40 = (FactoryObject_s004b_f430*)ZoneObject_operator_new(8, "Editor", 0, 0, 0, 0);
    FactoryObject_s004b_f430* len;
    if (n40)
        len = ((FactoryCtor*)n40)->Init();
    else
        len = 0;
    FactoryObject_s004b_f430* v33 = len;
    ((FactoryVtbl*)v33)->v10();
    return v33;
}

// @ 0x004c0190
int ResourceObject::GetReferenceCount()
{
    return _InterlockedExchangeAdd((volatile long*)&mnRefCount, 0);
}

// @ 0x004c01b0
int* XmlTextWriter::Init()
{
    int* v33 = (int*)this + 5;
    int n40;
    int len;
    FUN_00422c80(&n40);
    mpBufferEnd = (int*)this + 5;
    mpBuffer = mpBufferEnd;
    mpCapacity = (int*)((char*)mpBuffer + 0x100);
    *(uint16_t*)mpBuffer = 0;
    (void)v33;
    (void)len;
    return (int*)this;
}

// @ 0x00501200
void cExportHelper::ExportMeshEnd()
{
    FILE* f = export_mesh_FILE;
    fprintf(f, "</MESH>\n");
    fclose(f);
    export_mesh_FILE = 0;
}

// @ 0x01244f50
void init_150c720()
{
    FLD(0, 0) = OFF(ViewRowsA, rows[0]);
    FLD(0, 4) = 12;
    FLD(0, 8) = 0;
    FLD(0, 12) = (uint32_t)L"row1";
    FLD(0, 16) = 1;
    FLD(0, 20) = (uint32_t)FUN_004be950;

    FLD(1, 0) = OFF(ViewRowsA, rows[1]);
    FLD(1, 4) = 12;
    FLD(1, 8) = 0;
    FLD(1, 12) = (uint32_t)L"row2";
    FLD(1, 16) = 1;
    FLD(1, 20) = (uint32_t)FUN_004be950;

    FLD(2, 0) = OFF(ViewRowsA, rows[2]);
    FLD(2, 4) = 12;
    FLD(2, 8) = 0;
    FLD(2, 12) = (uint32_t)L"userorientation_row0";
    FLD(2, 16) = 1;
    FLD(2, 20) = (uint32_t)FUN_004be950;

    FLD(3, 0) = OFF(ViewRowsB, rows[0]);
    FLD(3, 4) = 12;
    FLD(3, 8) = 0;
    FLD(3, 12) = (uint32_t)L"userorientation_row1";
    FLD(3, 16) = 1;
    FLD(3, 20) = (uint32_t)FUN_004be950;

    FLD(4, 0) = OFF(ViewRowsB, rows[1]);
    FLD(4, 4) = 12;
    FLD(4, 8) = 0;
    FLD(4, 12) = (uint32_t)L"userorientation_row2";
    FLD(4, 16) = 1;
    FLD(4, 20) = (uint32_t)FUN_004be950;

    FLD(5, 0) = OFF(ViewRowsB, rows[2]);
    FLD(5, 4) = 12;
    FLD(5, 8) = 0;
    FLD(5, 12) = (uint32_t)L"weight";
    FLD(5, 16) = 1;
    FLD(5, 20) = (uint32_t)FUN_004bead0;

    FLD(6, 0) = 0;
    FLD(6, 4) = 4;
    FLD(6, 8) = 0;
    FLD(6, 12) = (uint32_t)L"paintregion";
    FLD(6, 16) = 1;
    FLD(6, 20) = (uint32_t)FUN_004beb70;

    FLD(7, 0) = OFF(ViewPaintId, paintid);
    FLD(7, 4) = 4;
    FLD(7, 8) = 0;
    FLD(7, 12) = (uint32_t)L"paintid";
    FLD(7, 16) = 1;
    FLD(7, 20) = (uint32_t)FUN_004beb70;

    FLD(8, 0) = OFF(ViewColor1, color1);
    FLD(8, 4) = 4;
    FLD(8, 8) = 0;
    FLD(8, 12) = (uint32_t)L"color1";
    FLD(8, 16) = 1;
    FLD(8, 20) = (uint32_t)FUN_004bebd0;

    FLD(9, 0) = OFF(ViewColor2, color2);
    FLD(9, 4) = 12;
    FLD(9, 8) = 0;
    FLD(9, 12) = (uint32_t)L"color2";
    FLD(9, 16) = 1;
    FLD(9, 20) = (uint32_t)FUN_004bebd0;

    FLD(10, 0) = OFF(ViewPaintBlob, paint);
    FLD(10, 4) = 12;
    FLD(10, 8) = 0;
    FLD(10, 12) = (uint32_t)L"paint";
    FLD(10, 16) = 1;
    FLD(10, 20) = (uint32_t)FUN_004bec30;

    FLD(11, 0) = 0;
    FLD(11, 4) = 4;
    FLD(11, 8) = 0;
    FLD(11, 12) = (uint32_t)L"blockref";
    FLD(11, 16) = 1;
    FLD(11, 20) = (uint32_t)FUN_004bec80;

    FLD(12, 0) = 0;
    FLD(12, 4) = 4;
    FLD(12, 8) = 0;
    FLD(12, 12) = (uint32_t)L"zcorpscore";
    FLD(12, 16) = 0;
    FLD(12, 20) = (uint32_t)FUN_004be8d0;

    FLD(13, 0) = 4;
    FLD(13, 4) = 4;
    FLD(13, 8) = 0;
    FLD(13, 12) = (uint32_t)L"isasymmetric";
    FLD(13, 16) = 1;
    FLD(13, 20) = (uint32_t)FUN_004be820;

    FLD(28, 0) = 0x81;
    FLD(28, 4) = 1;
}
