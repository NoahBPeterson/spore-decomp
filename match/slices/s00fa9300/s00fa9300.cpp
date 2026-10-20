// Slice s00fa9300 -- SP::cTerrainSphere (SPTerrain/SPTerrainSphere.obj), retail layout.
// Functions: HandleMessage (00fa9300), SetModels (00fa96d0), the background-map job completion
// (00fa9790), copy-ctor (00fa9840) / operator= (00fa99c0) of the 0x110-byte relevel-record
// container, and the background-map reset (00fa9b50).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as the other cTerrainSphere slices.
#include "types.h"
#include <new>
#include <math.h>

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

void* __cdecl operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

struct cTerrainSphere;
struct cTerrainSphereQuad;
struct cJob;
struct cTerrainStateMgr;
struct cTerrainMapSet;
struct PropList;

namespace EA { namespace ResourceMan { struct Key { uint32_t instance, type, group; }; } }
typedef EA::ResourceMan::Key Key;

// ---- globals (addresses pinned with a '// 0x...' comment so the difftest resolves them) ----------
extern cTerrainSphere* g_pTerrainSphere;      // 0x016c9e5c
extern int g_TerrainInitCount;                // 0x016c9e64
extern void* g_vtbl_BehaviorMessage;          // 0x013eb90c
extern void* g_vtbl_SlotMessage;              // 0x013eb844
extern const unsigned char kFacePerm[12];     // 0x0149040c

// ---- small framework types -----------------------------------------------------------------------
struct cMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void Post3(uint32_t id, void* msg, int a);                 // +0x14
    virtual void Post4(uint32_t id, void* msg, int a, int b);          // +0x18
};
cMessageServer* MessageServer();              // 0x0067dcc0

struct cTerrainEditor {
    bool IsModeA();                           // 0x00f678a0
    bool IsModeB();                           // 0x00f678c0
};
cTerrainEditor* TerrainEditor();              // 0x00f48a70

struct cJob { int Release(); };

struct RectT {
    float mLeft, mTop, mRight, mBottom;
    bool Test();                              // 0x0064e6b0
};

struct Vec4 { float x, y, z, w; };
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };

struct cSPTransform {
    uint16_t mFlags, mModCount;
    float mOffset[3];
    float mScale;
    float mRotation[9];
};

struct KeyVec { Key* mpBegin; Key* mpEnd; Key* mpCapacity; uint32_t mAlloc[2]; void resize(uint32_t n); };          // 0x004548d0
struct XformVec { cSPTransform* mpBegin; cSPTransform* mpEnd; cSPTransform* mpCapacity; uint32_t mAlloc[2]; void resize(uint32_t n); };  // 0x0041e3b0

struct cTerrainPlanetData {
    uint32_t pad[0x34 / 4];
    float mF34;                               // +0x34
};

// MessageBasicRC<5> / SlotMessage (0x40 bytes).
struct SlotMessage {
    void* volatile mpVftable;                 // +0x00
    uint32_t mRefCount;                       // +0x04
    uint32_t mData08;                         // +0x08
    uint32_t mData0C;                         // +0x0c
    uint32_t mData10;                         // +0x10
    uint32_t mData14;                         // +0x14
    uint32_t mData18;                         // +0x18
    uint32_t mData1C;                         // +0x1c
    uint32_t mData20;                         // +0x20
    uint32_t mData24;                         // +0x24
    uint32_t mData28;                         // +0x28
    uint32_t mData2C;                         // +0x2c
    uint32_t mMessageId;                      // +0x30
    uint32_t mData34;                         // +0x34
    uint32_t mData38;                         // +0x38
    uint32_t mData3C;                         // +0x3c
    SlotMessage* Construct(unsigned int a);   // 0x00421c80
};

inline void MsgRelease(SlotMessage* m)
{
    (*(void(__thiscall**)(SlotMessage*))(*(uint32_t volatile*)m + 8))(m);
}

struct SlotMessageRef {                       // intrusive holder for a SlotMessage (stack slot)
    SlotMessage* mpObject;
    SlotMessage* Set(SlotMessage* p);         // 0x00572620
};

// ---- the reusable 0x110-byte container (inline fixed_vector<Elem20,7> + 0x50-byte tail) ----------
struct Elem20 { uint32_t w[5]; };
struct S20 { uint32_t v[5]; };
struct U32x3 { uint32_t a, b, c; };
struct Tail50 { uint32_t d[15]; S20 s; };

struct Blob110 {
    Elem20* mpBegin;                          // +0x00
    Elem20* mpEnd;                            // +0x04
    Elem20* mpCapacity;                       // +0x08
    uint32_t mField0C;                        // +0x0c
    Elem20* mpInline;                         // +0x10
    uint32_t mField14;                        // +0x14
    Elem20 mBuffer[7];                        // +0x18 .. +0xa4
    U32x3 mU;                                 // +0xa4
    float mB0, mB4, mB8, mBC;                 // +0xb0 .. +0xbc
    Tail50 mTail;                             // +0xc0 .. +0x110
    Blob110(const Blob110& o);
    Blob110& operator=(const Blob110& o);
    void AssignRange(const Elem20* first, const Elem20* last, const Blob110* src);   // 0x00fa26e0
    void AssignFrom(const Blob110& o);                                               // 0x00fa90e0
};
// ---- cTerrainSphere (retail layout; only the fields these functions touch) ------------------------
struct cITerrainSphere {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40();
    virtual void FaceBegin(int a);            // +0x44
    virtual void FaceState(int a);            // +0x48
    virtual bool FaceVisible(int a);          // +0x4c
};

struct cTerrainSphere : cITerrainSphere {
    uint8_t mF04[0x24];                       // +0x04 .. +0x28
    PropList* mpDefinition;                   // +0x28
    cTerrainPlanetData* mpPlanet;             // +0x2c
    uint8_t mPad30[0x118 - 0x30];
    cTerrainSphereQuad* mQuadsA[6];           // +0x118
    cTerrainSphereQuad* mQuadsB[6];           // +0x130
    uint8_t mPad148[0x33c - 0x148];
    uint8_t mF33C;                            // +0x33c
    uint8_t mF33D;                            // +0x33d
    uint8_t mPad33E[0x368 - 0x33e];
    uint8_t mF368;                            // +0x368
    uint8_t mF369;                            // +0x369
    uint8_t mPad36A[0x36c - 0x36a];
    uint32_t mF36C;                           // +0x36c (0/1)
    uint8_t mF370;                            // +0x370
    uint8_t mPad371[0x374 - 0x371];
    Vec4 mVec[18];                            // +0x374 .. +0x493
    Vec4 mRectB[6];                           // +0x494 .. +0x4f3
    uint8_t mPad4F4[0x770 - 0x4f4];
    uint8_t mRelevelA[0x14];                  // +0x770
    uint8_t mRelevelB[0x14];                  // +0x784
    uint8_t mRelevelC[0x14];                  // +0x798
    int mNumModels;                           // +0x7ac
    KeyVec mModelKeys;                        // +0x7b0
    XformVec mModelTransforms;                // +0x7c4
    uint8_t mPad7D8[0x814 - 0x7d8];
    uint32_t mCamOffsetY;                     // +0x814
    uint8_t mPad818[0x81c - 0x818];
    cJob* mBackgroundJob;                     // +0x81c
    Vec4 mFaceRect[6];                        // +0x820 .. +0x87f
    uint8_t mF880;                            // +0x880
    uint8_t mPad881[0x8a0 - 0x881];
    cJob* mpImpostorJob;                      // +0x8a0
    int mImpostorJobState;                    // +0x8a4
    uint8_t mPad8A8[0xa48 - 0x8a8];
    int mState;                               // +0xa48

    bool HandleMessage(uint32_t msgId, SlotMessage* msg);
    void SetModels();
    void GenerateImpostorUpdate(void* a, void* b);           // 0x00fa8850
    void PinModelsToTerrain();                               // 0x00f99520
    void FinishBackgroundMap();                              // 0x00fa9170
    void ResetFaceState(int a);                              // 0x00f99ba0
    void ResetQuads();                                       // 0x00f96f90
    void ResetQuadsCaller();                                 // 0x00fa9b50
    void FaceSub0(int i, void* v);                           // 0x00fa0010
    void FaceSub1(int i, void* v);                           // 0x00fa0070
    void FaceSub2(int i, void* v);                           // 0x00fa00d0
};

struct cTerrainSphereQuad {
    void FaceSubA(int i, void* v);            // 0x00faf140
    void FaceSubB(int i, void* v);            // 0x00faf400
    void FaceSubC(int i, void* v);            // 0x00fb0d20
};

// The handler subobject (IHandlerRC at sphere+0x8) is what receives messages.
struct TerrainSphereHandler {
    uint8_t mPad00[0x24];
    cTerrainPlanetData* mpPlanet;             // +0x24 (= sphere+0x2c)
    uint8_t mPad28[0x368 - 0x28];
    uint8_t mF368;                            // +0x368 (sphere+0x370)
    uint8_t mPad369[0x814 - 0x369];
    cJob* mBackgroundJob;                     // +0x814 (sphere+0x81c)
    Vec4 mFaceRect[6];                        // +0x818 (sphere+0x820)
    uint8_t mPad878[0x898 - 0x878];
    cJob* mpImpostorJob;                      // +0x898 (sphere+0x8a0)
    uint8_t mPad89C[0xa40 - 0x89c];
    int mState;                               // +0xa40 (sphere+0xa48)

    cTerrainSphere* Sphere() { return (cTerrainSphere*)((char*)this - 8); }
    bool HandleMessage(uint32_t msgId, SlotMessage* msg);
};

// ---- PropList / property getters ------------------------------------------------------------------
void GetPropertyAsKeyArray(PropList* list, uint32_t id, uint32_t* count, Key** out);              // 0x006a0ae0
void GetPropertyAsTransformArray(PropList* list, uint32_t id, uint32_t* count, cSPTransform** o); // 0x006a0c30
void CopyTransforms(const cSPTransform* first, const cSPTransform* last, cSPTransform* dest);     // 0x00f339d0

struct cTerrainBackgroundMapJob {
    uint8_t mPad00[0xc];
    cTerrainSphere* mpSphere;                 // +0x0c
    uint32_t mF10;                            // +0x10
    bool Update(int a);                       // 0x00fa9790 (ret 4)
};

// =================================================================================================
// @ 0x00fa9300
bool cTerrainSphere::HandleMessage(uint32_t msgId, SlotMessage* msg)
{
    TerrainSphereHandler* h = (TerrainSphereHandler*)((char*)this + 8);
    if (g_pTerrainSphere == 0)
        return false;
    switch (msgId) {
    case 0x44edd9c:
        h->mState = 1;
        return true;
    case 0x3d5bf9a:
        if (h->mpImpostorJob == 0) {
            h->mState = -1;
            return false;
        }
        if (!TerrainEditor()->IsModeA() && !TerrainEditor()->IsModeB()) {
            h->mState = -1;
            return false;
        }
        GenerateImpostorUpdate((void*)msg->mData08, (void*)msg->mData10);
        return true;
    case 0x44edd9a:
        h->mState = -1;
        return false;
    case 0x87d5f9bf:
        break;
    default:
        return false;
    }

    if (h->mBackgroundJob) {
        cJob* j = h->mBackgroundJob;
        h->mBackgroundJob = 0;
        j->Release();
    }
    *(uint8_t*)((char*)this + 0x370) = 0;
    if (h->mState != 0)
        return false;
    if (msg->mData10 != (uint32_t)g_TerrainInitCount)
        return false;
    if ((cTerrainSphere*)msg->mData08 != this)
        return false;
    if (mpPlanet == 0)
        return false;

    float f = mpPlanet->mF34 * 3.1415927410125732f * 0.5f;
    int count = 0;
    for (int i = 0; i < 6; i++)
        if (((RectT*)&mFaceRect[i])->Test())
            count++;

    for (uint32_t i = 0; i < 6; i++) {
        Vec4* p = &mFaceRect[i];
        if (FaceVisible(1)) {
            float dx = p->z - p->x;
            float dy = p->w - p->y;
            float n0 = ((p->x + p->z) * 0.5f) * 2.0f - 1.0f;
            float n1 = ((p->y + p->w) * 0.5f) * 2.0f - 1.0f;
            float inv = 1.0f / sqrtf(n0 * n0 + n1 * n1 + 1.0f);
            float s = (i & 1) ? -inv : inv;
            float sz = sqrtf(dx * dx + dy * dy) * f * 0.5f;
            float v[3];
            unsigned k = i >> 1;
            v[kFacePerm[k * 4 + 0]] = s * n0;
            v[kFacePerm[k * 4 + 1]] = inv * n1;
            v[kFacePerm[k * 4 + 2]] = s;
            if (p->x != p->z && p->y != p->w) {
                PinModelsToTerrain();
                if (sz > 0.0f) {
                    SlotMessage* m = (SlotMessage*)operator new(0x40, "App", 0, 0, 0, 0);
                    m = m ? m->Construct(0) : 0;
                    SlotMessageRef ref;
                    ref.Set(m);
                    m = ref.mpObject;
                    m->mMessageId = 0x182c582;
                    *(float*)&m->mData08 = v[0];
                    *(float*)&m->mData10 = v[1];
                    *(float*)&m->mData18 = v[2];
                    *(float*)&m->mData20 = sz;
                    m->mData28 = msg->mData10;
                    m->mData2C = count;
                    MessageServer()->Post4(0x182c582, m, 0, 0);
                }
                FaceSub0(i, p);
                FaceSub1(i, p);
                FaceSub2(i, p);
            }
        }
        mRectB[i].x = 0.0f;
        mRectB[i].y = 0.0f;
        mRectB[i].z = 1.0f;
        mRectB[i].w = 1.0f;
        p->x = 0.0f;
        p->y = 0.0f;
        p->z = 0.0f;
        p->w = 0.0f;
    }
    FaceBegin(1);
    return true;
}

// =================================================================================================
// @ 0x00fa96d0
void cTerrainSphere::SetModels()
{
    if (mpDefinition == 0)
        return;
    Key* keys;
    GetPropertyAsKeyArray(mpDefinition, 0x3a90c57, (uint32_t*)&mNumModels, &keys);
    KeyVec* kv = (KeyVec*)((char*)this + 0x7b0);
    kv->resize(mNumModels);
    ((XformVec*)((char*)this + 0x7c4))->resize(mNumModels);
    {
        Key* dest = kv->mpBegin;
        Key* src = keys;
        Key* end = keys + mNumModels;
        while (src != end) {
            dest->instance = src->instance;
            dest->type = src->type;
            dest->group = src->group;
            ++src;
            ++dest;
        }
    }
    uint32_t n = mNumModels;
    cSPTransform* xf;
    GetPropertyAsTransformArray(mpDefinition, 0x3a90c5f, &n, &xf);
    CopyTransforms(xf, xf + mNumModels, ((XformVec*)((char*)this + 0x7c4))->mpBegin);
}

// =================================================================================================
// @ 0x00fa9790
bool cTerrainBackgroundMapJob::Update(int a)
{
    (void)a;
    mpSphere->FinishBackgroundMap();
    SlotMessage* m = (SlotMessage*)operator new(0x40, "Terrain/Sphere/kMessageEndBackgroundMapGeneration", 0, 0, 0, 0);
    if (m != 0) {
        m->mMessageId = 0;
        m->mpVftable = &g_vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)&m->mRefCount, 0);
        m->mpVftable = &g_vtbl_SlotMessage;
        m->mData38 = 0;
        (*(void(__thiscall**)(SlotMessage*))(*(uint32_t volatile*)m + 4))(m);
    }
    m->mMessageId = 0x87d5f9bf;
    m->mData08 = (uint32_t)mpSphere;
    m->mData10 = mF10;
    MessageServer()->Post4(0x87d5f9bf, m, 0, 0);
    MsgRelease(m);
    return true;
}

// =================================================================================================
// @ 0x00fa9840
Blob110::Blob110(const Blob110& o)
{
    mpInline = mBuffer;
    mpEnd = mBuffer;
    mpBegin = mBuffer;
    mpCapacity = (Elem20*)((char*)mBuffer + 0x8c);
    AssignRange(o.mpBegin, o.mpEnd, &o);
    mU = o.mU;
    mB0 = o.mB0;
    mB4 = o.mB4;
    mB8 = o.mB8;
    mBC = o.mBC;
    float* t = (float*)&mTail;
    const float* s = (const float*)&o.mTail;
    t[0] = s[0];   t[1] = s[1];   t[2] = s[2];   t[3] = s[3];   t[4] = s[4];
    t[5] = s[5];   t[6] = s[6];   t[7] = s[7];   t[8] = s[8];   t[9] = s[9];
    t[10] = s[10]; t[11] = s[11]; t[12] = s[12]; t[13] = s[13]; t[14] = s[14];
    t[15] = s[15]; t[16] = s[16]; t[17] = s[17]; t[18] = s[18]; t[19] = s[19];
}

// =================================================================================================
// @ 0x00fa99c0
Blob110& Blob110::operator=(const Blob110& o)
{
    AssignFrom(o);
    mU.a = o.mU.a;
    mU.b = o.mU.b;
    mU.c = o.mU.c;
    mB0 = o.mB0;
    mB4 = o.mB4;
    mB8 = o.mB8;
    mBC = o.mBC;
    mTail.d[0] = o.mTail.d[0];
    mTail.d[1] = o.mTail.d[1];
    mTail.d[2] = o.mTail.d[2];
    mTail.d[3] = o.mTail.d[3];
    mTail.d[4] = o.mTail.d[4];
    mTail.d[5] = o.mTail.d[5];
    mTail.d[6] = o.mTail.d[6];
    mTail.d[7] = o.mTail.d[7];
    mTail.d[8] = o.mTail.d[8];
    mTail.d[9] = o.mTail.d[9];
    mTail.d[10] = o.mTail.d[10];
    mTail.d[11] = o.mTail.d[11];
    mTail.d[12] = o.mTail.d[12];
    mTail.d[13] = o.mTail.d[13];
    mTail.d[14] = o.mTail.d[14];
    mTail.s = o.mTail.s;
    return *this;
}

// =================================================================================================
// @ 0x00fa9b50
void cTerrainSphere::ResetQuadsCaller()
{
    mF370 = 1;
    ResetFaceState(-1);
    FaceState(7);
    *(uint8_t*)((char*)this + 0x368 + mF36C) = 0;
    mF36C = 1 - mF36C;
    uint32_t idx = mF36C;
    for (int i = 0; i < 6; i++) {
        Vec4 t = mVec[i + idx * 6];
        mFaceRect[i] = t;
        mQuadsA[i]->FaceSubA(i, &t);
        mQuadsA[i]->FaceSubB(i, &t);
    }
    ResetQuads();
    mF33D = 0;
    FinishBackgroundMap();
    Vec4 u = {0.0f, 0.0f, 1.0f, 1.0f};
    for (int i = 0; i < 6; i++)
        mQuadsA[i]->FaceSubC(i, &u);

    SlotMessage* m = (SlotMessage*)operator new(0x40, "App", 0, 0, 0, 0);
    if (m != 0) {
        m->mMessageId = 0;
        m->mpVftable = &g_vtbl_BehaviorMessage;
        _InterlockedExchange((long volatile*)&m->mRefCount, 0);
        m->mpVftable = &g_vtbl_SlotMessage;
        m->mData38 = 0;
        (*(void(__thiscall**)(SlotMessage*))(*(uint32_t volatile*)m + 4))(m);
    }
    m->mMessageId = 0x87d5f9bf;
    m->mData08 = (uint32_t)this;
    m->mData10 = (uint32_t)g_TerrainInitCount;
    if (mF880) {
        MessageServer()->Post3(0x87d5f9bf, m, 0);
        MsgRelease(m);
    } else {
        MessageServer()->Post4(0x87d5f9bf, m, 0, 0);
        MsgRelease(m);
    }
}
