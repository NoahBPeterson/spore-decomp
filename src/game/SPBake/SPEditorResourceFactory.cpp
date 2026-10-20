// src/game/SPBake/SPEditorResourceFactory.cpp -- migrated from slice(s) s004bf430, s004bd850, s005002d0, s004be5d0, s004bcc50, s004bbfb0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorResourceFactory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorResourceFactory.h"
#include "EA/Allocator/FixedBufferAllocator.h"
#include "EA/XML/XmlTextWriter.h"
#include <stdio.h>
#include <wchar.h>

// unnamed retail callees and globals (address in the comment)
extern void* GetManager();  // 0x67dcd0
extern uint32_t EA_Hash_FNV1_String16(const void* s, uint32_t hash, int);  // 0x932f30
extern void FUN_004c07e0(void* begin, void* end, char flag);               // 0x4c07e0
extern void FUN_006adc60(int, int);                                        // 0x6adc60
extern bool g_typeTableInit;                                               // 0x15d8600
extern int* FUN_004c0500(uint32_t key);                            // 0x4c0500
extern void FUN_006ac0a0(int type, uint32_t key, char flag, int);  // 0x6ac0a0
extern bool FUN_004bdc00(int n);                                   // 0x4bdc00
extern bool FUN_004bdae0();                                        // 0x4bdae0
extern int FUN_004bd9f0(int);                                      // 0x4bd9f0
extern bool FUN_004bdc60(int a, int b, bool c);                    // 0x4bdc60
extern bool FUN_004be5d0();                                        // 0x4be5d0
extern int ReadRuntimeCreatureData(int data);                      // 0x4bf430
extern bool WriteRuntimeCreatureData(int* data);                   // 0x4bf770
extern int WriteBinaryEditorModel(int data);                       // 0x4b0010
extern bool ReadBinaryEditorModel(int* a, int b);                  // 0x4bf9f0
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
struct StreamObject;
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
    bool CreateResource(StreamObject* obj, int* out, uint32_t param_4, int typeHash);   // 004bc300
    bool ReadResource(StreamObject* stream, uint32_t param_2, uint32_t param_3, int typeHash);   // 004bc540
    bool WriteResource(StreamObject* stream, uint32_t param_1, uint32_t param_2, int typeHash);  // 004bc620
    bool ReadResourceFromStream(StreamObject* stream, uint32_t key, int typeHash);               // 004bc6d0
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
};
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
struct EditorCreature : RefCounted_s004b_bfb0 {
    uint32_t pad4;
    uint32_t f8, fC, f10;
};
extern RefCounted_s004b_bfb0* FUN_004b9c70(void* self);                       // 0x4b9c70
extern RefCounted_s004b_bfb0* FUN_004b9da0(void* self);                       // 0x4b9da0
static inline void ReleaseRef(RefCounted_s004b_bfb0* p) {
    if (p)
        p->Release();
}
namespace EA {
namespace Allocator {
struct FixedBufferAllocator_s004b_bfb0 {
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
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ultow(unsigned long value, wchar_t* buf, int radix);
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
#pragma intrinsic(wcscmp, wcscpy)
struct Vector3_s004b_e5d0 {
    float x, y, z;
    float LengthSquared() const { return x * x + y * y + z * z; }
};
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
class IStream_s004b_e5d0 {
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
extern void FUN_00903550(void* parser, int arg);   // 0x903550 (XML_StopParser-style, cdecl)
extern int FUN_00903400(void* parser, int param);                       // 0x903400
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
__declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
struct ParserBlockOps {
    void AddBlock(int index);                      // 0x004be420 (thiscall, ret 4)
};
struct ParserModelBlocks {
    void Reserve(uint32_t count);                  // 0x004c0250 (thiscall, ret 4)
};
// ---- items of slice s004bd850 end

// ---- items of slice s004bf430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchangeAdd(volatile long* Addend, long Value);
extern int FUN_004afd00(int n);                                  // 0x4afd00
extern void operator_new__(void* p, int a, int n);               // in-place new
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
#define FBA_MASK 0x3fffffff
#define FBA_INUSE 0x80000000
#define FBA_TRAILER 0x40000000
void FixedBufferAllocatorStub::Free(void* p) {
    (void)p;
}
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
bool cSPEditorResourceFactory::CreateResource(StreamObject* obj, int* out, uint32_t param_4, int typeHash)
{
    RefCounted_s004b_bfb0* local_8 = 0;
    if (!SetAssetData((uint32_t)typeHash, 0)) {
        if (typeHash != 0xf43029a)
            return false;
        EditorCreature* c = (EditorCreature*)EditorAlloc(0x128, "Editor", 0, 0, 0, 0);
        if (c)
            c = (EditorCreature*)FUN_004b9da0(c);
        if (c)
            c->v0();
        local_8 = c;
    } else {
        RefCounted_s004b_bfb0* local_28 = (RefCounted_s004b_bfb0*)EditorAlloc(0xac, "Editor", 0, 0, 0, 0);
        if (local_28)
            local_28 = FUN_004b9c70(local_28);
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
bool cSPEditorResourceFactory::ReadResource(StreamObject* stream, uint32_t param_2, uint32_t param_3, int typeHash)
{
    if (typeHash != 0xf43029a) {
        if (typeHash != 0x3d97a8e4 && typeHash != 0x2b978c46 && typeHash != 0x2399be55 &&
            typeHash != 0x24682294 && typeHash != 0x476a98c7 && typeHash != 0x438f6347)
            return false;
        int* p = stream->v10();
        int data = stream->v18(p[1], 0);
        bool ok = ReadBinaryEditorModel((int*)data, typeHash);
        return ok;
    }
    int handle = (int)FUN_004c0500(param_2);
    bool ok = false;
    if (handle != 0) {
        int data = stream->v18(handle, 0);
        if (ReadRuntimeCreatureData(data))
            ok = true;
    }
    FUN_006ac0a0(0xb, param_2, ok, 0);
    return ok;
}

// @ 0x004bc620
bool cSPEditorResourceFactory::WriteResource(StreamObject* stream, uint32_t param_1, uint32_t param_2, int typeHash)
{
    if (typeHash != 0xf43029a) {
        bool bakeable = SetAssetData((uint32_t)typeHash, 0);
        if (!bakeable && typeHash != 0x1a99b06b)
            return false;
        int data = stream->v18((int)param_1, typeHash);
        return WriteRuntimeCreatureData((int*)data) != 0;
    }
    int handle = (int)FUN_004c0500(param_1);
    if (handle != 0) {
        int data = stream->v18(handle, 0);
        if (WriteRuntimeCreatureData((int*)data))
            return true;
    }
    return false;
}

// @ 0x004bc6d0
bool cSPEditorResourceFactory::ReadResourceFromStream(StreamObject* stream, uint32_t key, int typeHash)
{
    int data = WriteBinaryEditorModel(key);
    if (data == 0)
        return false;
    if (typeHash == 0x1a99b06b)
        return ReadBinaryEditorModel((int*)data, key);
    char buffer[17076];
    EA::Allocator::FixedBufferAllocator_s004b_bfb0 fba;
    fba.mpBufferInfo = 0;
    fba.Create(((EA::Allocator::FixedBufferAllocator_s004b_bfb0::buffer_info*)buffer), 15000, 0);
    FUN_004bd9f0(data);
    bool ok = true;
    bool done = false;
    while (ok && !done) {
        int n = FUN_004bdc00(0x200);
        if (n == 0) {
            ok = false;
        } else {
            int got = stream->v30((int*)n, 0x200);
            done = got != 0x200;
            if (got == -1 || !FUN_004bdc60(n, got, done))
                ok = false;
        }
    }
    if (ok)
        ok = FUN_004be5d0();
    FUN_004bdae0();
    if (fba.mpBufferInfo != 0 && (fba.mpBufferInfo[1].mSignature & 0x40000000) != 0)
        DestroyFixedBufferShared(&fba);
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
bool EA::Allocator::FixedBufferAllocator::IsValid()
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

// @ 0x004bca10
void EA::Allocator::FixedBufferAllocator::destroy_shared()
{
    for (uint32_t* p = (uint32_t*)((char*)&mpBufferInfo[1] + (mpBufferInfo[1].mSignature & 0x3fffffff));
         p < (uint32_t*)((char*)&mpBufferInfo[1] + mpBufferInfo->mSize);
         p = (uint32_t*)((*p & 0x3fffffff) + (char*)p)) {
        if ((int)*p < 0) {
            FixedBufferAllocator* owner;
            if ((*p & 0x40000000) == 0)
                owner = 0;
            else
                owner = *(FixedBufferAllocator**)((char*)p + (*p & 0x3fffffff) - 4);
            if (owner == this)
                Free(p + 2);
        }
    }
}

// @ 0x004bcab0
void EA::Allocator::FixedBufferAllocator::Free(void * p)
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
        FixedBufferAllocator* owner;
        if ((*h & 0x40000000) == 0)
            owner = 0;
        else
            owner = *(FixedBufferAllocator**)((char*)h + (*h & 0x3fffffff) - 4);
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

// @ 0x004bdc00
int cEditorModelParser::FUN_004bdc00(int param)
{
    g_pCurrentParser = this;
    int result = FUN_00903400(mpXMLParser, param);
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

// @ 0x004be420
void FUN_004be420(void* self, int index)
{
    (void)self; (void)index;
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
    (void)stream; (void)data;
    return false;
}

// @ 0x004bf770
bool FUN_004bf770(int* stream, int data)
{
    (void)stream; (void)data;
    return false;
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
