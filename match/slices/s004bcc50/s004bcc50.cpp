// Slice s004bcc50: SP::cSPEditorResourceFactory::WriteResourceToStream (3069 bytes).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (unoptimized editor module, no
// C++ EH: the writer/vector/string locals have destructors but no EH frame).
//
// Serializes an editor model to XML ("sporemodel"): model properties, then one <blockref> per
// block with its transform, paint list, child list (built from two parent/sibling index
// arrays), symmetry partner and handle weights. Models of type 0x1a99b06b take a separate path
// (FUN_004bfb20).
#include "types.h"

// ---------------------------------------------------------------------------------------
// math helpers (inline accessors: the original indexes rows/elements through them, which
// is where the `xor r,r; shl r,2` / `mov r,k; imul r,0xc` address computations come from)
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

// ---------------------------------------------------------------------------------------
// editor model data (result of WriteBinaryEditorModel)
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

// ---------------------------------------------------------------------------------------
// containers (EA headers are built with 4-byte packing: these locals are not 8-aligned)
#pragma pack(push, 4)
struct IStream;

namespace EA { namespace XML {
class XmlTextWriter
{
public:
    uint32_t mData[8];
    XmlTextWriter(int a, int b);                                        // 0x00901a10
    ~XmlTextWriter();                                                   // 0x00901a50
    void SetOutputStream(IStream* stream, int a);                       // 0x00901d30
    void WriteXmlHeader();                                              // 0x00901960
    void BeginElement(const wchar_t* name);                             // 0x00901b30
    bool EndElement(const wchar_t* name);                               // 0x00901b90
    void AppendAttributeF(const wchar_t* name, const wchar_t* fmt, ...);   // 0x009017d0
    void WriteCharData(const wchar_t* text);                            // 0x009018a0
};
}}
using EA::XML::XmlTextWriter;

// fixed wide string with a 0x100-byte inline buffer
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

// Reserved frames of the inline helpers cl declined (FixedWString/fixed_vector ctors and the
// VectorBase dtor are out of line here): /Od keeps their locals' slots in this frame.
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// eastl::fixed_vector<int, 256>
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

#pragma pack(pop)

// ---------------------------------------------------------------------------------------
// XML helpers (other TUs / anonymous namespace)
EditorModelData* WriteBinaryEditorModel(int model);                                 // 0x004b0010
bool FUN_004bfb20(IStream* stream, int model);                                      // 0x004bfb20
bool XmlWriteElement(XmlTextWriter* w, const wchar_t* name, const wchar_t* text);   // 0x004bede0
bool XmlWriteBool(XmlTextWriter* w, const wchar_t* name, bool value);               // 0x004bee50
bool XmlWriteUInt(XmlTextWriter* w, const wchar_t* name, uint32_t value);           // 0x004bee90
bool XmlWriteHex(XmlTextWriter* w, const wchar_t* name, uint32_t value);            // 0x004beec0
bool XmlWriteFloat(XmlTextWriter* w, const wchar_t* name, float value);             // 0x004bef40
bool XmlWriteVector3(XmlTextWriter* w, const wchar_t* name, const float* v);        // 0x004bef80
wchar_t* FormatFloat(wchar_t* buf, float value);                                    // 0x004beca0

namespace SP {
class cSPEditorResourceFactory
{
public:
    static bool WriteResourceToStream(IStream* stream, int model, int modelTypeHash);
};

// 004bcc50
bool cSPEditorResourceFactory::WriteResourceToStream(IStream* stream, int model, int modelTypeHash)
{
    EditorModelData* data = WriteBinaryEditorModel(model);
    if (!data)
        return false;

    bool ok = true;
    if (modelTypeHash == 0x1a99b06b) {
        ok = FUN_004bfb20(stream, model);
    } else {
        FixedWString blockId;
        ScratchSlots<3>();
        XmlTextWriter xml(1, 0);
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
