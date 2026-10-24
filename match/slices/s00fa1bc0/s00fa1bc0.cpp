// Slice s00fa1bc0: SP::cTerrainSphere::cTerrainSphere (0x00fa1bc0, 1974 bytes).
// Retail layout (the 2008 PDB layout is shifted); only the dwords the constructor stores to are declared, and the
// asserts after the class pin every offset. Five bases: cITerrainSphere(+0) cILayer(+4) cIDecalManager(+8)
// IHandlerRC(+0xC) and the refcounted Resource(+0x10), whose atomic refcount is zeroed with an xchg.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (movss/xorps float stores, no EH frame).
#include "types.h"
#include <stddef.h>

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

extern "C" void* __cdecl FUN_011e073e(void* dst, int zero, unsigned size);   // 0x011e073e memset thunk

struct Vec4 {
    float x, y, z, w;
};

inline void Clear(Vec4& v)
{
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 0.0f;
}

// ---- bases -----------------------------------------------------------------------------------
struct IBase0 { virtual void v0(); };
struct IBase1 { virtual void v0(); };
struct IBase2 { virtual void v0(); };
struct IBase3 { virtual void v0(); };

struct ResourceBase {            // refcounted resource at +0x10
    virtual void v0();
    volatile long mnRefCount;
    uint32_t mField18, mField1C, mField20;
    ResourceBase()
    {
        _InterlockedExchange(&mnRefCount, 0);
        mField18 = 0;
        mField1C = 0;
        mField20 = 0;
    }
};

struct ResourceBaseB : ResourceBase {   // one derived level that only re-stores the vptr and +0x24
    uint32_t mField24;
    ResourceBaseB() { mField24 = 0; }
    virtual void v0();
};

// ---- members built by out-of-line constructors -------------------------------------------------
struct GenSteps0 {
    uint32_t mPad[0x44 / 4];
    void Init();    // 0x00fc17e0
};
struct GenSteps1 {
    uint32_t mPad[0x44 / 4];
    void Init();    // 0x00fc18c0
};
struct GenSteps2 {
    uint32_t mPad[0x44 / 4];
    void Init();    // 0x00fc16b0
};

struct AllocTag {
    AllocTag() {}
};

struct Matrix3 {
    float m[9];
    void Assign(const Matrix3* src);    // 0x0041cb40 (thiscall, ret 4)
};

struct Obj7C4 {                         // 0x14 bytes, built by 0x006a5ea0 (thiscall, ret 8)
    uint32_t mPad[5];
    void Init(int zero, const AllocTag& tag);   // 0x006a5ea0
};

extern float g_Float016c9e98[4];        // 0x016c9e98 .. 0x016c9ea4
extern float g_Float016c9e8c[3];        // 0x016c9e8c .. 0x016c9e94
extern float g_Float015b117c[4];        // 0x015b117c .. 0x015b1188
extern int   g_TerrainSphereCount;      // 0x016c9e88
struct cTerrainSphere;
extern cTerrainSphere* g_pTerrainSphere;    // 0x016c9e5c
extern Matrix3 g_IdentityMatrix;        // 0x016c9f24

// ---- decal bookkeeping ------------------------------------------------------------------------
struct cSPTransform;

struct RefCounted {                     // 8-byte smart-pointer target (slot 0 = addref)
    virtual void AddRef();              // slot 0
    virtual void Release();             // slot 4
};

struct DecalPtr {                       // element of the decal smart-pointer vector (8 bytes)
    RefCounted* mPtr;                   // +0
    uint32_t    mField4;                // +4
};

struct DecalPtrVec {                    // SPVector<smart_ptr> at offset 0 of its owner
    DecalPtr* mBegin;                   // +0
    DecalPtr* mEnd;                     // +4
    DecalPtr* mCapacity;                // +8
    void Insert(DecalPtr* pos, DecalPtr* value);        // 0x00fa2440
    void EraseRange(DecalPtr* first, DecalPtr* last);   // 0x00fa25c0
};

struct LayerVec {                       // SPVector<uint> slot, 0x14-byte stride
    uint32_t* mBegin;                   // +0
    uint32_t* mEnd;                     // +4
    uint32_t* mCapacity;                // +8
    uint32_t  mPad[2];                  // +0xc
    void AppendKey4(uint32_t* pos, const uint32_t& v);      // 0x00b96600
    void AppendValueI(uint32_t* pos, const uint32_t& v);    // 0x004558a0
};

struct cTerrainSphereDecal {            // 0x12c bytes; only the refcount is read here
    virtual void Destroy(int flags);    // slot 0
    virtual void Release();             // slot 4
    uint32_t mRef;                      // +4
    cTerrainSphereDecal* InitDecal();   // 0x00fad730 (returns this)
    void SetupDecal(uint32_t index, uint32_t a, cTerrainSphere* sphere,
                    const cSPTransform* xform, float f, bool flag);   // 0x00faec70
    void Unlink();                      // 0x00fadac0
};

struct cTerrainSphere : IBase0, IBase1, IBase2, IBase3, ResourceBaseB {
    uint32_t mF28, mF2C;
    GenSteps0 mSteps0;                  // +0x30
    GenSteps1 mSteps1;                  // +0x74
    GenSteps2 mSteps2;                  // +0xb8
    uint32_t mFC, mF100, mF104;
    bool mF108;
    float mF10C;
    bool mF110, mF111;
    uint32_t mF114;
    uint32_t mA118[12];                 // +0x118 .. +0x147
    uint32_t mF148[21];                 // +0x148 .. +0x198
    uint32_t mPad19C[2];
    uint32_t mF1A4[3];
    uint32_t mPad1B0[2];
    uint32_t mF1B8;                     // +0x1b8
    uint32_t* mListBegin;               // +0x1bc
    uint32_t* mListEnd;                 // +0x1c0
    uint32_t* mListCapacity;            // +0x1c4
    uint32_t mPad1C8;                   // +0x1c8
    uint32_t mF1CC, mF1D0;              // +0x1cc, +0x1d0
    union { uint32_t d; uint8_t b; } mF1D4;     // +0x1d4 (dword init, byte dirty store)
    float mF1D8, mF1DC, mF1E0, mF1E4;
    bool mF1E8;
    float mF1EC[8];                     // +0x1ec .. +0x208
    union {
        struct {                        // constructor view: individually zeroed vectors
            uint32_t mF20C[6];
            uint32_t mPad224[2];
            uint32_t mF22C[3];
            uint32_t mPad238[2];
            uint32_t mF240[3];
            uint32_t mPad24C[2];
            uint32_t mF254[3];
            uint32_t mPad260[2];
            uint32_t mF268[3];
            uint32_t mPad274[2];
            uint32_t mF27C[3];
            uint32_t mPad288[2];
            uint32_t mF290[3];
            uint32_t mPad29C[2];
            uint32_t mF2A4[3];
            uint32_t mPad2B0[2];
        };
        struct {                        // layer view used by the decal code
            uint32_t mPad20C[3];        // +0x20c .. +0x217
            LayerVec mDecalLayer[4];    // +0x218, stride 0x14
            LayerVec mFreeLayer[4];     // +0x268, stride 0x14
        };
    };
    uint32_t mF2B8[3];
    uint32_t mPad2C4[2];
    uint32_t mF2CC[3];
    uint32_t mPad2D8[2];
    uint32_t mF2E0[3];
    uint32_t mPad2EC[2];
    uint32_t mF2F4[3];
    uint32_t mPad300[2];
    uint32_t mF308;
    float mF30C[12];                    // +0x30c .. +0x338
    bool mF33C, mF33D;
    uint32_t mF340, mF344;
    bool mF348;
    float mF34C[5];                     // +0x34c .. +0x35c
    float mF360, mF364;
    bool mF368, mF369;
    uint32_t mF36C;
    bool mF370;
    Vec4 mVec[18];                      // +0x374 .. +0x493
    uint32_t mPad494[(0x4f4 - 0x494) / 4];
    bool mF4F4, mF4F5;
    uint32_t mPad4F6[(0x6d8 - 0x4f8) / 4];
    uint32_t mMemset6D8[0x80 / 4];      // +0x6d8
    uint32_t mF758[3];
    uint32_t mPad764[2];
    bool mF76C;
    uint32_t mF770[3];
    uint32_t mPad77C[2];
    uint32_t mF784[3];
    uint32_t mPad790[2];
    uint32_t mF798[3];
    uint32_t mPad7A4[2];
    uint32_t mF7AC, mF7B0, mF7B4, mF7B8;
    uint32_t mPad7BC[2];
    Obj7C4 mObj7C4;
    uint32_t mF7D8[3];
    uint32_t mPad7E4[2];
    uint32_t mF7EC[3];
    uint32_t mPad7F8[2];
    uint32_t mF800[3];
    uint32_t mPad80C[2];
    uint32_t mF814[3];
    uint32_t mPad820[(0x880 - 0x820) / 4];
    bool mF880;
    uint32_t mF884[5];
    int mF898, mF89C;
    uint32_t mF8A0;
    int mF8A4;
    uint32_t mF8A8;
    bool mF8AC;
    uint32_t mF8B0[3];
    uint32_t mPad8BC[2];
    uint32_t mF8C4[3];
    uint32_t mPad8D0[2];
    uint32_t mF8D8[4];
    uint16_t mF8E8, mF8EA;
    float mF8EC[3];
    float mF8F8;
    Matrix3 mMat8FC;
    int mF920;
    uint32_t mF924, mF928;
    uint32_t mPad92C[(0xa1c - 0x92c) / 4];
    float mFA1C[7];
    float mFA38[4];
    uint32_t mFA48, mFA4C;

    cTerrainSphere();
    void InitSubObjects();              // 0x00f97130
    void RemoveListEntry(uint32_t value);                       // 0x00fa23d0
    uint32_t AllocDecalIndex(uint32_t layer);                   // 0x00fa27d0
    void FreeDecalIndex(uint32_t packed);                       // 0x00fa2850
    cTerrainSphereDecal* NewDecal(uint32_t a, const cSPTransform* xform, float f);   // 0x00fa28b0
    cTerrainSphereDecal* NewDecalLayer(uint32_t a, const cSPTransform* xform,
                                       float f, uint32_t layer);                     // 0x00fa2920
    void ReleaseDecal(uint32_t packed);                         // 0x00fa29b0
    virtual void v0();
};

#define CHK(name, off) typedef char chk_##name[(offsetof(cTerrainSphere, name) == (off)) ? 1 : -1]
CHK(mF28, 0x28);
CHK(mSteps0, 0x30);
CHK(mSteps2, 0xb8);
CHK(mFC, 0xfc);
CHK(mF10C, 0x10c);
CHK(mA118, 0x118);
CHK(mF148, 0x148);
CHK(mF1A4, 0x1a4);
CHK(mF1B8, 0x1b8);
CHK(mListBegin, 0x1bc);
CHK(mListEnd, 0x1c0);
CHK(mListCapacity, 0x1c4);
CHK(mF1CC, 0x1cc);
CHK(mF1D4, 0x1d4);
CHK(mDecalLayer, 0x218);
CHK(mFreeLayer, 0x268);
CHK(mF1D8, 0x1d8);
CHK(mF1EC, 0x1ec);
CHK(mF20C, 0x20c);
CHK(mF22C, 0x22c);
CHK(mF2F4, 0x2f4);
CHK(mF308, 0x308);
CHK(mF30C, 0x30c);
CHK(mF33C, 0x33c);
CHK(mF34C, 0x34c);
CHK(mF360, 0x360);
CHK(mF36C, 0x36c);
CHK(mVec, 0x374);
CHK(mF4F4, 0x4f4);
CHK(mMemset6D8, 0x6d8);
CHK(mF758, 0x758);
CHK(mF7AC, 0x7ac);
CHK(mObj7C4, 0x7c4);
CHK(mF7D8, 0x7d8);
CHK(mF814, 0x814);
CHK(mF880, 0x880);
CHK(mF8B0, 0x8b0);
CHK(mF8D8, 0x8d8);
CHK(mF8E8, 0x8e8);
CHK(mF8EC, 0x8ec);
CHK(mMat8FC, 0x8fc);
CHK(mF920, 0x920);
CHK(mFA1C, 0xa1c);
CHK(mFA4C, 0xa4c);

// @ 0x00fa1bc0
cTerrainSphere::cTerrainSphere()
{
    mF28 = 0;
    mSteps0.Init();
    mF2C = 0;
    mSteps1.Init();
    mSteps2.Init();
    mF10C = 5.0f;
    mFC = 0;
    mF100 = 0;
    mF104 = 0;
    mF108 = true;
    mF110 = false;
    mF111 = false;
    mF114 = 0;
    mF148[0] = 0;
    mF148[1] = 0;
    mF148[2] = 0;
    mF148[3] = 0;
    mF148[4] = 0;
    mF148[5] = 0;
    mF148[6] = 0;
    mF148[7] = 0;
    mF148[8] = 0;
    mF148[9] = 0;
    mF148[10] = 0;
    mF148[11] = 0;
    mF148[12] = 0;
    mF148[13] = 0;
    mF148[14] = 0;
    mF148[15] = 0;
    mF148[16] = 0;
    mF148[17] = 0;
    mF148[18] = 0;
    mF148[19] = 0;
    mF148[20] = 0;
    mF1A4[0] = 0;
    mF1A4[1] = 0;
    mF1A4[2] = 0;
    mF1B8 = 0;
    mListBegin = 0;
    mListEnd = 0;
    mF1CC = 0;
    mF1D0 = 4;
    mF1D4.d = 16;
    mF1D8 = 25.0f;
    mF1DC = 100.0f;
    mF1E0 = 1.0f;
    mF1E4 = 1.0f;
    mF1E8 = true;
    mF1EC[0] = 1.0f;
    mF1EC[1] = 1.0f;
    mF1EC[2] = 1.0f;
    mF1EC[3] = 1.0f;
    mF1EC[4] = 1.0f;
    mF1EC[5] = 1.0f;
    mF1EC[6] = 1.0f;
    mF1EC[7] = 1.0f;
    mF20C[0] = 0;
    mF20C[1] = 0;
    mF20C[2] = 0;
    mF20C[3] = 0;
    mF20C[4] = 0;
    mF20C[5] = 0;
    mF22C[0] = 0;
    mF22C[1] = 0;
    mF22C[2] = 0;
    mF240[0] = 0;
    mF240[1] = 0;
    mF240[2] = 0;
    mF254[0] = 0;
    mF254[1] = 0;
    mF254[2] = 0;
    mF268[0] = 0;
    mF268[1] = 0;
    mF268[2] = 0;
    mF27C[0] = 0;
    mF27C[1] = 0;
    mF27C[2] = 0;
    mF290[0] = 0;
    mF290[1] = 0;
    mF290[2] = 0;
    mF2A4[0] = 0;
    mF2A4[1] = 0;
    mF2A4[2] = 0;
    mF2B8[0] = 0;
    mF2B8[1] = 0;
    mF2B8[2] = 0;
    mF2CC[0] = 0;
    mF2CC[1] = 0;
    mF2CC[2] = 0;
    mF2E0[0] = 0;
    mF2E0[1] = 0;
    mF2E0[2] = 0;
    mF2F4[0] = 0;
    mF2F4[1] = 0;
    mF2F4[2] = 0;
    mF308 = 0;
    mF30C[0] = g_Float016c9e98[0];
    mF30C[1] = g_Float016c9e98[1];
    mF30C[2] = g_Float016c9e98[2];
    mF30C[3] = g_Float016c9e98[3];
    mF30C[4] = g_Float016c9e98[0];
    mF30C[5] = g_Float016c9e98[1];
    mF30C[6] = g_Float016c9e98[2];
    mF30C[7] = g_Float016c9e98[3];
    mF30C[8] = g_Float016c9e98[0];
    mF30C[9] = g_Float016c9e98[1];
    mF30C[10] = g_Float016c9e98[2];
    mF30C[11] = g_Float016c9e98[3];
    mF34C[0] = 1.0f;
    mF34C[1] = 1.0f;
    mF34C[2] = 1.0f;
    mF34C[3] = 1.0f;
    mF34C[4] = 1.0f;
    mF33C = false;
    mF33D = false;
    mF340 = 0;
    mF344 = 0;
    mF348 = false;
    mF360 = -1.0f;
    mF364 = -1.0f;
    mF36C = 0;
    mF370 = false;
    mF4F4 = false;
    mF4F5 = true;
    mF758[0] = 0;
    mF758[1] = 0;
    mF758[2] = 0;
    mF76C = false;
    mF770[0] = 0;
    mF770[1] = 0;
    mF770[2] = 0;
    mF784[0] = 0;
    mF784[1] = 0;
    mF784[2] = 0;
    mF798[0] = 0;
    mF798[1] = 0;
    mF798[2] = 0;
    mF7AC = 0;
    AllocTag tag;
    mF7B0 = 0;
    mF7B8 = 0;
    mF7B4 = 0;
    mObj7C4.Init(0, tag);
    mF7D8[0] = 0;
    mF7D8[1] = 0;
    mF7D8[2] = 0;
    mF7EC[0] = 0;
    mF7EC[1] = 0;
    mF7EC[2] = 0;
    mF800[0] = 0;
    mF800[1] = 0;
    mF800[2] = 0;
    mF814[0] = 0;
    mF814[1] = 0;
    mF814[2] = 0;
    mF880 = false;
    mF884[0] = 0;
    mF884[1] = 0;
    mF884[2] = 0;
    mF884[3] = 0;
    mF884[4] = 0;
    mF898 = -1;
    mF89C = -1;
    mF8A0 = 0;
    mF8A4 = -1;
    mF8A8 = 0;
    mF8AC = false;
    mF8B0[0] = 0;
    mF8B0[1] = 0;
    mF8B0[2] = 0;
    mF8C4[0] = 0;
    mF8C4[1] = 0;
    mF8C4[2] = 0;
    mF8D8[0] = 0;
    mF8D8[1] = 0;
    mF8D8[2] = 0;
    mF8D8[3] = 0;
    mF8EA = 0;
    mF8E8 = 0;
    mF8EC[0] = g_Float016c9e8c[0];
    mF8EC[1] = g_Float016c9e8c[1];
    mF8EC[2] = g_Float016c9e8c[2];
    mF8F8 = 1.0f;
    mMat8FC.Assign(&g_IdentityMatrix);
    mF920 = -1;
    mF924 = 0;
    mF928 = 0;
    ++g_TerrainSphereCount;
    mFA1C[0] = 0.0f;
    mFA1C[1] = 0.0f;
    mFA1C[2] = 0.0f;
    mFA1C[3] = 0.0f;
    mFA1C[4] = 0.0f;
    mFA1C[5] = 0.0f;
    mFA1C[6] = 0.0f;
    mFA38[0] = g_Float015b117c[0];
    mFA38[1] = g_Float015b117c[1];
    mFA38[2] = g_Float015b117c[2];
    mFA38[3] = g_Float015b117c[3];
    mFA48 = 0;
    mFA4C = 0;
    g_pTerrainSphere = this;
    FUN_011e073e(mMemset6D8, 0, 0x80);
    InitSubObjects();
    for (int i = 0; i < 6; ++i) {
        mVec[i].x = 0.0f; mVec[i].y = 0.0f; mVec[i].z = 0.0f; mVec[i].w = 0.0f;
        mVec[i + 6].x = 0.0f; mVec[i + 6].y = 0.0f; mVec[i + 6].z = 0.0f; mVec[i + 6].w = 0.0f;
        mA118[i] = 0;
        mA118[i + 6] = 0;
    }
    Clear(mVec[12]);
    Clear(mVec[13]);
    Clear(mVec[14]);
    Clear(mVec[15]);
    Clear(mVec[16]);
    Clear(mVec[17]);
    mF344 = 0;
    mF368 = false;
    mF369 = false;
    mF36C = 0;
}

// ===============================================================================================
// Decal bookkeeping helpers (slice additions)
// ===============================================================================================
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned size);  // 0x011e0744 memcpy
extern "C" void  __cdecl FUN_00f47380(void* p);                                     // 0x00f47380 operator delete
extern "C" void* __cdecl FUN_00f473a0(unsigned size, const char* name, int a, int b,
                                      const char* file, int line);                   // 0x00f473a0 allocator new
extern "C" void* __cdecl FUN_00f9aff0(void* first, void* last, void* dst);           // 0x00f9aff0
extern "C" void* __cdecl FUN_00f9adf0(void* first, void* pos, void* dst);            // 0x00f9adf0
extern "C" void  __cdecl FUN_00f9ae40(void* first, void* pos, void* dst);            // 0x00f9ae40
extern "C" void* __cdecl FUN_00f9ae80(void* first, void* last, void* dst);           // 0x00f9ae80
extern "C" void* __cdecl FUN_00f9f8f0(const void* a, const void* b, const void* c,
                                      const void* d, const void* e);                 // 0x00f9f8f0
extern "C" void* __cdecl FUN_00951bf0(const void* first, const void* last, void* dst); // 0x00951bf0 copy_Rec20

struct Rec20 {                          // 0x14-byte response-curve element
    uint32_t m[5];
};

struct Rec20Vector {
    Rec20*   mBegin;                    // +0
    Rec20*   mEnd;                      // +4
    Rec20*   mCapacity;                 // +8
    uint32_t mPad0C;                    // +0xc
    Rec20*   mInline;                   // +0x10
    Rec20*   Realloc(uint32_t n, const Rec20* first, const Rec20* last);   // 0x00fa1b60
    void     assign(const Rec20* first, const Rec20* last, const Rec20& value);
};

struct DecalArrayElem {                 // 0x110-byte array element (own + inline buffers)
    void*    mPtr;                      // +0
    uint32_t mPad04[3];                 // +4
    void*    mAlt;                      // +0x10
    uint32_t mPad14[(0x110 - 0x14) / 4];
};

// ---- function bodies --------------------------------------------------------------------------

// @ 0x00fa23d0
void cTerrainSphere::RemoveListEntry(uint32_t value)
{
    int n = (int)(mListEnd - mListBegin);
    if (n <= 0)
        return;
    int i = 0;
    while (mListBegin[i] != value) {
        if (++i >= n)
            return;
    }
    uint32_t* dst = mListBegin + i;
    uint32_t* src = dst + 1;
    if (src < mListEnd)
        FUN_011e0744(dst, src, (unsigned)((char*)mListEnd - (char*)src));
    --mListEnd;
    mF1D4.b = 1;
}

// @ 0x00fa2440
void DecalPtrVec::Insert(DecalPtr* pos, DecalPtr* value)
{
    DecalPtr* e = mEnd;
    if (e != mCapacity) {
        if (value >= pos && value < e)
            ++value;
        if (e) {
            RefCounted* p = e[-1].mPtr;
            e->mPtr = p;
            if (p)
                p->AddRef();
            e->mField4 = e[-1].mField4;
        }
        FUN_00f9aff0(pos, e - 1, e);
        RefCounted* src = value->mPtr;
        RefCounted* old = pos->mPtr;
        if (src != old) {
            if (src)
                src->AddRef();
            pos->mPtr = src;
            if (old)
                old->Release();
        }
        pos->mField4 = value->mField4;
        mEnd = e + 1;
        return;
    }

    int n = (int)(e - mBegin);
    int cap;
    if (n == 0)
        cap = 1;
    else {
        cap = n * 2;
        if (cap == 0) {
            n = 0;
            goto alloc_done;
        }
    }
    n = (int)FUN_00f473a0((unsigned)(cap * 8), "Simulator", 0, 0,
                          (const char*)0x013ebb38, 0xd1);
alloc_done:
    {
        DecalPtr* oldBegin = mBegin;
        DecalPtr* p = (DecalPtr*)FUN_00f9adf0(oldBegin, pos, (DecalPtr*)n);
        FUN_00f9ae40(oldBegin, pos, (DecalPtr*)n);
        if (p) {
            RefCounted* src = value->mPtr;
            p->mPtr = src;
            if (src)
                src->AddRef();
            p->mField4 = value->mField4;
        }
        DecalPtr* oldEnd = mEnd;
        DecalPtr* q = (DecalPtr*)FUN_00f9adf0(pos, oldEnd, p + 1);
        FUN_00f9ae40(pos, oldEnd, p + 1);
        if (mBegin && ((int*)mBegin)[-1] != 0)
            FUN_00f47380(mBegin);
        mBegin = (DecalPtr*)n;
        mEnd = q;
        mCapacity = (DecalPtr*)n + cap;
    }
}

// @ 0x00fa25c0
void DecalPtrVec::EraseRange(DecalPtr* first, DecalPtr* last)
{
    DecalPtr* p = (DecalPtr*)FUN_00f9ae80(last, mEnd, first);
    DecalPtr* e = mEnd;
    for (; p < e; ++p) {
        RefCounted* o = p->mPtr;
        if (o)
            o->Release();
    }
    mEnd -= last - first;
}

// @ 0x00fa2620
void __stdcall FUN_00fa2620(DecalArrayElem* first, DecalArrayElem* last)
{
    for (; first < last; ++first) {
        void* p = first->mPtr;
        if (p != 0 && p != first->mAlt)
            FUN_00f47380(p);
    }
}

// @ 0x00fa26e0
void Rec20Vector::assign(const Rec20* first, const Rec20* last, const Rec20& value)
{
    uint32_t n = (uint32_t)(last - first);
    if ((uint32_t)(mCapacity - mBegin) < n) {
        Rec20* buf = Realloc(n, first, last);
        if (mBegin && mBegin != mInline)
            FUN_00f47380(mBegin);
        mBegin = buf;
        mEnd = buf + n;
        mCapacity = buf + n;
        return;
    }
    uint32_t have = (uint32_t)(mEnd - mBegin);
    if (n <= have) {
        mEnd = (Rec20*)FUN_00951bf0(first, last, mBegin);
        return;
    }
    Rec20* mid = (Rec20*)first + have;
    FUN_00951bf0(first, mid, mBegin);
    FUN_00f9f8f0(&value, mid, last, mEnd, last);
    mEnd = (Rec20*)last;
}

// @ 0x00fa27d0
uint32_t cTerrainSphere::AllocDecalIndex(uint32_t layer)
{
    LayerVec& dec = mDecalLayer[layer];
    LayerVec& fr = mFreeLayer[layer];
    if (fr.mBegin == fr.mEnd) {
        uint32_t n = (uint32_t)(dec.mEnd - dec.mBegin);
        uint32_t zero = 0;
        uint32_t* p = dec.mEnd;
        if (p < dec.mCapacity) {
            dec.mEnd = p + 1;
            if (p)
                *p = zero;
        } else
            dec.AppendKey4(p, zero);
        return n;
    }
    uint32_t idx = fr.mEnd[-1];
    --fr.mEnd;
    return idx;
}

// @ 0x00fa2850
void cTerrainSphere::FreeDecalIndex(uint32_t packed)
{
    uint32_t layer = (uint32_t)((int32_t)packed >> 24);
    uint32_t idx = packed & 0xffffff;
    mDecalLayer[layer].mBegin[idx] = 0;
    LayerVec& fr = mFreeLayer[layer];
    uint32_t* p = fr.mEnd;
    uint32_t v = idx;
    if (p < fr.mCapacity) {
        fr.mEnd = p + 1;
        if (p)
            *p = v;
    } else
        fr.AppendValueI(p, v);
}

// @ 0x00fa28b0
cTerrainSphereDecal* cTerrainSphere::NewDecal(uint32_t a, const cSPTransform* xform, float f)
{
    uint32_t idx = AllocDecalIndex(0);
    cTerrainSphereDecal* p = (cTerrainSphereDecal*)FUN_00f473a0(
        300, "Terrain/Sphere/cTerrainSphereDecal", 0, 0, 0, 0);
    cTerrainSphereDecal* d;
    if (p != 0)
        d = p->InitDecal();
    else
        d = 0;
    ++d->mRef;
    d->SetupDecal(idx, a, this, xform, f, false);
    mDecalLayer[0].mBegin[idx] = (uint32_t)d;
    return d;
}

// @ 0x00fa2920
cTerrainSphereDecal* cTerrainSphere::NewDecalLayer(uint32_t a, const cSPTransform* xform,
                                                   float f, uint32_t layer)
{
    uint32_t idx = AllocDecalIndex(layer);
    uint32_t packed = (layer << 24) | idx;
    cTerrainSphereDecal* p = (cTerrainSphereDecal*)FUN_00f473a0(
        300, "Terrain/Sphere/cTerrainSphereDecal", 0, 0, 0, 0);
    cTerrainSphereDecal* d;
    if (p != 0)
        d = p->InitDecal();
    else
        d = 0;
    ++d->mRef;
    d->SetupDecal(packed, a, this, xform, f, true);
    mDecalLayer[layer].mBegin[idx] = (uint32_t)d;
    return d;
}

// @ 0x00fa29b0
void cTerrainSphere::ReleaseDecal(uint32_t packed)
{
    uint32_t layer = packed >> 24;
    uint32_t idx = packed & 0xffffff;
    LayerVec& dec = mDecalLayer[layer];
    if (idx < (uint32_t)(dec.mEnd - dec.mBegin)) {
        cTerrainSphereDecal* d = (cTerrainSphereDecal*)dec.mBegin[idx];
        if (d) {
            d->Unlink();
            int ref = d->mRef - 1;
            d->mRef = ref;
            if (ref == 0) {
                d->mRef = 1;
                d->Destroy(1);
            }
            FreeDecalIndex(packed);
        }
    }
}
