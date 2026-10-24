// Slice s004cb340: SP::cSkinObject mesh-rebuild helpers in the editor /Od region.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
//
// 0x004CBDF0 is the default constructor of a skin-data object holding six 0x14-byte
// eastl vectors (the first one a node-weight vector whose allocator needs a tag).  Its
// byte-exact reconstruction is below.  The three large mesh builders are reconstructed
// from their annotated disassembly (their Ghidra decompiles carry lost frame locals).
#include "types.h"

#pragma pack(push, 4)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct AllocTag { AllocTag() {} };
struct NodeWeightAllocator {
    NodeWeightAllocator(const AllocTag& tag);        // 0x00429360
    uint32_t pad[2];
};
struct NodeWeightVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    NodeWeightAllocator mAllocator;
    NodeWeightVector() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(AllocTag()) { ScratchSlots<1>(); }
};
struct PlainVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    uint32_t mAlloc[2];
    PlainVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};

// @ 0x004CBDF0  (real class name not recovered; layout: +8,+0x1c,+0x30,+0x44,+0x6c,+0x80)
struct SkinBuildData {
    uint32_t mIndex;          // +0x00 (mesh-element index)
    uint32_t mf04;            // +0x04
    NodeWeightVector v1;      // +8
    PlainVector v2;           // +0x1c
    PlainVector v3;           // +0x30
    PlainVector v4;           // +0x44
    float    mf58;            // +0x58
    float    mf5c;            // +0x5c
    float    mf60;            // +0x60
    float    mf64;            // +0x64
    uint32_t mf68;            // +0x68
    PlainVector v5;           // +0x6c
    PlainVector v6;           // +0x80
    SkinBuildData();
};
SkinBuildData::SkinBuildData() {}

// ---------------------------------------------------------------------------
// Shared helpers: eastl vectors, the VSet builder and the property list.
// ---------------------------------------------------------------------------
template <class T> struct VectorT {                  // eastl::vector<T> (0x14 bytes)
    T* mpBegin; T* mpEnd; T* mpCapacity;
    uint32_t mAllocator[2];
    void FUN_00422740(int n, int fill);              // 0x00422740  resize(n, fill)
    void FUN_004c0b80();                             // 0x004c0b80  dtor
};

struct Alloc { uint32_t pad[3]; };

struct Vector3 { float x; float y; float z; };

extern "C" Vector3* FUN_0041db10(Vector3* out, Vector3* a, Vector3* b);  // 0x0041db10 a - b
extern "C" float    FUN_0040ae50(Vector3* v);                            // 0x0040ae50 VectorLength
extern "C" void*    FUN_00f473a0(uint32_t size, const char* name,
                                 int, int, int, int);                    // 0x00f473a0 operator new (editor)
extern const char   kEditorAllocName[];                                  // 0x013eb430 ?kEditorAllocName@@3QBDB
extern float g_014854c8;                                                 // 0x014854c8
extern float g_013ec434;                                                 // 0x013ec434
extern float g_013ef550;                                                 // 0x013ef550
extern float g_013f059c;                                                 // 0x013f059c

struct VectorU32 {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity;
    bool empty();                                    // 0x00526430
};

struct VSet {
    int* mpBegin;                                    // +0x00
    int* mpEnd;                                      // +0x04
    uint32_t mPad[3];                                // +0x08
    VSet(const Alloc& a);                            // 0x00540470
    void FUN_004c5e30();                             // 0x004c5e30
    void FUN_004b0560(int n, int flags);             // 0x004b0560
    void FUN_00425990();                             // 0x00425990
};

struct BoneEntry { uint32_t f0; uint32_t f4; };      // 8-byte mBones element

struct MeshElement {                                 // 0x8c-byte skin-mesh element
    uint16_t f00;                                    // +0x00
    int16_t  mParent;                                // +0x02
    int16_t  mNext;                                  // +0x04
    uint16_t f06;                                    // +0x06
    uint16_t mFlags;                                 // +0x08
    uint8_t  f0a;                                    // +0x0a
    uint8_t  mKind;                                  // +0x0b (1 = follow mNext)
    uint16_t mf0c;                                   // +0x0c  cap-code range begin
    uint8_t  mf0e;                                   // +0x0e
    uint8_t  mf0f;                                   // +0x0f
    uint8_t  mf10;                                   // +0x10  cap-code range length
    uint8_t  f11[3];                                 // +0x11
    Vector3  mPosA;                                  // +0x14
    Vector3  mPosB;                                  // +0x20
    float    mf2c;                                   // +0x2c
    uint8_t  f30[0x8c - 0x30];                       // +0x30
};

struct BoneWeightBuilder {                           // cSkinObject +0x7c
    uint32_t mPad[5];                                // +0x00 .. +0x13
    void FUN_004cd690(int count);                    // 0x004cd690
};

extern "C" uint32_t FUN_004bb860(uint32_t workid);   // 0x004bb860 ?FUN_004bb860@@YAII@Z
extern "C" void FUN_0052b340(void* p1, void* p2, void* p3, void* p4, void* vs,
                             uint32_t a6, uint32_t a7, uint32_t a8, int a9, float a10);
                                                     // 0x0052b340 SkinPaintBuildBoneWeights
extern float g_01485378;                             // 0x01485378 _HK_REAL_ZERO

namespace SP {

struct cDirectPropertyList {
    float GetFloatProperty(uint32_t key);            // 0x006a2710
    int   GetIntProperty(uint32_t key);              // 0x006a2660
};

extern cDirectPropertyList* g_015fd918;              // 0x015fd918  SP::sAppProperties

struct cRuntimeCreatureResource {
    uint8_t   pad00[0x18];                           // +0x00
    uint32_t  mf18;                                  // +0x18
    uint8_t   pad1c[0x98 - 0x1c];                    // +0x1c
    uint8_t*  mpElements;                            // +0x98  MeshElement array (0x8c bytes each)
    uint8_t*  mpElementsEnd;                         // +0x9c
    uint8_t   padA0[0xac - 0xa0];                    // +0xa0
    uint32_t* mpCapCodes;                            // +0xac  cap-code words (bone-weight keys)
};

struct PairIF;
struct VectorIF {
    void* mpBegin;                                   // +0x00
    void* mpEnd;                                     // +0x04
    PairIF* FUN_00530c80(PairIF* first, PairIF* last);// 0x00530c80 erase(first, last)
};

struct SimpleVectorU {
    uint32_t* mpBegin;                               // +0x00
    uint32_t* mpEnd;                                 // +0x04
    uint32_t* mpCapacity;                            // +0x08
    uint32_t  mAlloc[2];                             // +0x0c
    void FUN_00454860(void* v);                      // 0x00454860 push_back(const uint&)
};

struct MeshPaintTarget {                             // cSkinObject +0x34 (paint/mesh holder)
    uint32_t  f00;                                   // +0x00
    uint32_t  f04;                                   // +0x04
    uint8_t*  mpPartBegin;                           // +0x08  0xc-byte part elements
    uint8_t*  mpPartEnd;                             // +0x0c
    uint8_t   pad10[0x30 - 0x10];                    // +0x10
    VectorIF  mVec30;                                // +0x30
    uint8_t   pad44[0x58 - 0x44];                    // +0x44
    VectorU32 mVec58;                                // +0x58
    uint8_t   pad64[0x90 - 0x64];                    // +0x64
    uint32_t* mpOut90;                               // +0x90  bone-weight output records (0x10 bytes each)
    VectorU32 mVertexList;                           // +0x94
    uint8_t   padA0[0xbc - 0xa0];                    // +0xa0
    VectorU32 mIndexList;                            // +0xbc
    uint8_t   padC8[0xe4 - 0xc8];                    // +0xc8
    SimpleVectorU mParts;                            // +0xe4  built SkinBuildData* list
    uint8_t   padF8[0x124 - 0xf8];                   // +0xf8
    VectorIF  mVec124;                               // +0x124
    uint8_t   pad138[0x1cc - 0x138];                 // +0x138
    uint32_t  mState;                                // +0x1cc
    void FUN_00509450();                             // 0x00509450
    void FUN_005098a0();                             // 0x005098a0
    void FUN_00509b20();                             // 0x00509b20
    void FUN_0050a0a0();                             // 0x0050a0a0
    void FUN_0050aac0(float f);                      // 0x0050aac0
    void FUN_00508fd0();                             // 0x00508fd0
    void FUN_005087b0();                             // 0x005087b0 TangentBuilder::BuildTangents
};

struct cSkinObject {
    uint8_t   pad00[8];                              // +0x00
    cRuntimeCreatureResource* mResource;             // +0x08
    uint8_t   pad0c[0x34 - 0x0c];                    // +0x0c
    MeshPaintTarget* mMesh;                          // +0x34
    uint32_t  mf38;                                  // +0x38
    uint8_t   pad3c[0x40 - 0x3c];                    // +0x3c
    VectorT<uint32_t> mVec40;                        // +0x40
    VectorT<BoneEntry> mBones;                       // +0x54
    VectorT<uint32_t> mVec68;                        // +0x68
    BoneWeightBuilder mBuilder;                      // +0x7c
    uint32_t* mBoneWeights90;                        // +0x90  per-element bone-weight records (0x10 bytes)

    bool BuildMesh();                                // 0x004cb340
    int  BuildBones();                               // 0x004cb820
};

// @ 0x004CB340  SP::cSkinObject::BuildMesh
bool cSkinObject::BuildMesh()
{
    cRuntimeCreatureResource* res = mResource;
    MeshElement* elems = (MeshElement*)res->mpElements;
    int count = (int)(res->mpElementsEnd - res->mpElements) / 0x8c;
    if (count == 0)
        return false;

    cDirectPropertyList* props = g_015fd918;
    float fScale = props->GetFloatProperty(0xa0304059u);
    int   prop   = props->GetIntProperty(0x4f6a84fdu);
    int   boneCount = (int)(mBones.mpEnd - mBones.mpBegin) >> 3;
    int   maxIdx = elems[count - 1].mParent + 1;

    VectorT<int> map;
    map.FUN_00422740(maxIdx, -1);
    int* mapArr = map.mpBegin;
    for (int i = 0; i < count; ++i) {
        if (elems[i].mParent != -1) {
            if ((elems[i].mFlags & 2) != 0)
                mapArr[elems[i].mParent - 1] = i;
            mapArr[elems[i].mParent] = i;
        }
    }

    Alloc alloc;
    VSet vs(alloc);
    vs.FUN_004c5e30();
    vs.FUN_004b0560(boneCount, 0);
    int* out = vs.mpBegin;
    for (int i = 0; i < count; ++i) {
        int j = i;
        while (elems[j].mKind == 1)
            j = elems[j].mNext;
        out[i] = j;
    }
    for (int k = count; k < boneCount; ++k) {
        int j = elems[mapArr[mBones.mpBegin[k].f4]].mNext;
        while (elems[j].mKind == 1)
            j = elems[j].mNext;
        out[k] = j;
    }

    MeshPaintTarget* mesh = mMesh;
    if (mesh->mVertexList.empty())
        mesh->FUN_00509450();
    if (mesh->mIndexList.empty())
        mesh->FUN_005098a0();

    bool useScale = (FUN_004bb860(res->mf18) == 0x2b978c46u);
    int  meshCount = (int)(mesh->mpPartEnd - mesh->mpPartBegin) / 0xc;
    mBuilder.FUN_004cd690(meshCount);
    float param = useScale ? fScale : g_01485378;
    FUN_0052b340(&mBuilder, &mVec40, &mBones, &mVec68, &vs, mf38,
                 (uint32_t)mesh, (uint32_t)res, prop, param);
    for (int* p = vs.mpBegin; p < vs.mpEnd; ++p) {}
    vs.FUN_00425990();
    for (int* p = map.mpBegin; p < map.mpEnd; ++p) {}
    map.FUN_004c0b80();
    return true;
}

}  // namespace SP

// ---------------------------------------------------------------------------
// 0x004CB820: build the per-element bone-weight records for the paint target.
// The original also carries the /GS stack-cookie checks (with EA::Thread::
// ThreadSleep on the failure path); those are unconditional no-ops and are
// omitted here because the slice is compiled /GS-.
// ---------------------------------------------------------------------------
// @ 0x004CB820
int SP::cSkinObject::BuildBones()
{
    MeshPaintTarget* mesh = mMesh;
    if (mesh->mVertexList.empty())
        mesh->FUN_00509450();
    if (mesh->mIndexList.empty())
        mesh->FUN_005098a0();

    mesh->FUN_00509b20();

    cRuntimeCreatureResource* res = mResource;
    MeshElement* elems = (MeshElement*)res->mpElements;
    int count = (int)(res->mpElementsEnd - res->mpElements) / 0x8c;
    uint32_t* capCodes = res->mpCapCodes;

    int partCount = 0;
    for (int i = 0; i < count; ++i) {
        MeshElement& e = elems[i];
        if ((e.mFlags & 1) != 0)
            continue;

        Vector3 diff;
        FUN_0041db10(&diff, &e.mPosA, &e.mPosB);      // posA - posB
        float len = FUN_0040ae50(&diff);
        float d = len * e.mf2c;

        int jEnd = (int)e.mf0c + (int)e.mf10;
        for (int j = (int)e.mf0c; j < jEnd; ++j) {
            if (capCodes[j] == 0x74756f6du) {         // "mout"
                d *= g_014854c8;
                break;
            }
        }
        d = d * g_013ec434 + g_013ef550;

        SkinBuildData* p = (SkinBuildData*)FUN_00f473a0(0x94, kEditorAllocName, 0, 0, 0, 0);
        if (p != 0)
            p->SkinBuildData::SkinBuildData();
        p->mIndex = (uint32_t)partCount;
        p->mf04 = 0;
        p->mf58 = g_01485378;
        p->mf60 = g_01485378;
        p->mf5c = d;
        p->mf64 = d;
        p->mf68 = 0;
        mesh->mParts.FUN_00454860(&p);
        ++partCount;
    }

    mesh->mVec30.FUN_00530c80((PairIF*)mesh->mVec30.mpBegin, (PairIF*)mesh->mVec30.mpEnd);
    mesh->mVec124.FUN_00530c80((PairIF*)mesh->mVec124.mpBegin, (PairIF*)mesh->mVec124.mpEnd);

    if (!mesh->mVec58.empty()) {
        mesh->mState = 2;
        mesh->FUN_0050a0a0();
        mesh->mState = 0;
    }

    mesh->FUN_0050aac0(g_013f059c);
    mesh->FUN_005087b0();                             // TangentBuilder::BuildTangents
    mesh->mState = 3;
    mesh->FUN_00508fd0();
    mesh->mState = 0;

    int idx = 0;
    for (int k = 0; k < count; ++k) {
        MeshElement& e = elems[k];
        if ((e.mFlags & 1) != 0)
            continue;
        SkinBuildData* sb = (SkinBuildData*)mesh->mParts.mpBegin[idx];
        float* out = (float*)((uint8_t*)mBoneWeights90 + k * 0x10);
        out[0] = sb->mf58;
        out[1] = sb->mf60;
        out[2] = sb->mf5c;
        out[3] = sb->mf64;
        ++idx;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x004CBF00: append the skinned vertices of one mesh part to the editor
// dynamic-draw vertex stream.  `this` is a part-builder subobject whose owner
// (the editor skin object) begins 0x88 bytes before it.
// ---------------------------------------------------------------------------
struct EmbeddedState {
    uint32_t SetVertexDescriptor();                  // 0x011EDCD0  ?SetVertexDescriptor@EmbeddedState@graphics@rw@@QAEIXZ
};

// The object pointed to by the builder's +0x18 field; its +0x04 is the state.
struct PartStateLink {
    uint32_t        f0;                              // +0x00
    EmbeddedState*  mpEmbedded;                      // +0x04
};

// Vertex arrays of one skin part (the builder's owner +0x00 field).
struct SkinPartArrays {
    uint32_t  f00;                                   // +0x00
    uint32_t  f04;                                   // +0x04
    Vector3*  mpRestPos;                             // +0x08  rest positions, indexed by mpIndexA[]
    uint32_t  f0c;                                   // +0x0c
    uint32_t  f10;                                   // +0x10
    uint32_t  f14;                                   // +0x14
    uint32_t  f18;                                   // +0x18
    Vector3*  mpBonePos;                             // +0x1c  bone positions, indexed by mpIndexB[]
    uint32_t  f20[14];                               // +0x20 .. +0x57
    int*      mpIndexA;                              // +0x58
    int*      mpIndexAEnd;                           // +0x5c
    uint32_t  f60;                                   // +0x60
    uint32_t  f64;                                   // +0x64
    uint32_t  f68;                                   // +0x68
    int*      mpIndexB;                              // +0x6c
};

// Owner of the builder subobject; only its first field is read here.
struct SkinPartOwner {
    SkinPartArrays* mpPartArrays;                    // +0x00
    uint8_t         mPad[0x84];                      // +0x04 .. +0x87
};

// Draw-batch sink passed as the third stack argument.
struct PartCtx {
    uint32_t  mPad[8];                               // +0x00 .. +0x1f
    uint32_t  mVertexBase;                           // +0x20  running vertex count
    uint32_t  mPad24;                                // +0x24
    uint32_t  mPartCount;                            // +0x28  running part count
};

extern "C" void      FUN_00777bf0(void);                        // pushShaderDataNull
extern "C" void      FUN_00777b50(EmbeddedState*);              // 0x00777b50 SP::SetShaderData
extern "C" void      FUN_00777c10(void);                        // shader
extern "C" void      FUN_011fd7b0(EmbeddedState*, uint32_t*);   // StateCacheDispatch
extern "C" int       FUN_011fd790(EmbeddedState*);              // StateCacheVertexStride
extern "C" void      FUN_011fd7d0(void);                        // StateCacheClearCount
extern "C" void      FUN_011fd820(void);                        // StateCacheEnd
extern "C" int       FUN_004cdd70(int, void*);                  // vertex-chunk allocator
extern "C" Vector3*  FUN_0041de40(Vector3*, float*, Vector3*);  // 0x0041de40 Vector3_Scale
extern "C" Vector3*  FUN_0041dc10(Vector3*, Vector3*, Vector3*);// 0x0041dc10 combine rest+bone
extern float g_013f05ac;                                        // 0x013f05ac part draw scale

struct SkinPartBuilder {
    uint32_t        mPad[6];                         // +0x00 .. +0x17
    PartStateLink*  mpState;                         // +0x18
    uint32_t        mPad1c[21];                      // +0x1c .. +0x6f
    uint8_t         mGate;                           // +0x70
    void FUN_004cbf00(void*, void*, PartCtx*);
};

// @ 0x004CBF00
void SkinPartBuilder::FUN_004cbf00(void* a2, void* a3, PartCtx* ctx)
{
    (void)a2; (void)a3;
    // the owner begins 0x88 bytes before this subobject
    SkinPartArrays* src = ((SkinPartOwner*)((uint8_t*)this - 0x88))->mpPartArrays;
    if (this->mpState == 0 || src == 0)
        return;

    EmbeddedState* es = this->mpState->mpEmbedded;
    uint8_t* vd = (uint8_t*)es->SetVertexDescriptor();
    if (vd[0xf] != 0x18)
        return;

    FUN_00777bf0();
    FUN_00777b50(es);
    uint32_t dispatchSlot;
    FUN_011fd7b0(es, &dispatchSlot);
    int stride = FUN_011fd790(es);
    int count  = (int)(src->mpIndexAEnd - src->mpIndexA);
    int idx = 0;
    stride -= stride % 3;
    float scale = (this->mGate != 0) ? g_013f05ac : g_01485378;
    int*     indexA  = src->mpIndexA;
    int*     indexB  = src->mpIndexB;
    Vector3* restPos = src->mpRestPos;
    Vector3* bonePos = src->mpBonePos;
    ctx->mVertexBase += (uint32_t)count;

    while (count > 0) {
        int chunk = (count < stride) ? count : stride;
        struct Chunk { int mCount; int mPad; Vector3* mpOut; } rec;
        rec.mCount = chunk;
        rec.mPad = 0;
        rec.mpOut = 0;
        if (FUN_004cdd70(chunk, &rec)) {
            int end = idx + chunk;
            Vector3* w = rec.mpOut;
            for (int i = idx; i < end; ++i) {
                Vector3 scaled;
                Vector3* s = FUN_0041de40(&scaled, &scale, &bonePos[indexB[i]]);
                Vector3 res;
                Vector3* r = FUN_0041dc10(&res, &restPos[indexA[i]], s);
                *w = *r; ++w;
                *w = bonePos[indexB[i]]; ++w;
            }
            rec.mpOut = w;
            FUN_011fd820();
            ctx->mPartCount += 1;
        }
        idx += chunk;
        count -= chunk;
    }
    FUN_011fd7d0();
    FUN_00777c10();
}