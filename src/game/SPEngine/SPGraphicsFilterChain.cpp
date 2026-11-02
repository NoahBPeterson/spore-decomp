// src/game/SPEngine/SPGraphicsFilterChain.cpp -- migrated from slice(s) s006f9250, s006f8380, s006f54a0, s006f43e0, s006f7430, s006f6430 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFilterChain.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cFilterChain.h"
#include <intrin.h>
#include <math.h>
#include "rw/graphics/EmbeddedState.h"
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);

// ---- items of slice s006f6430 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete_(void* p) throw();
struct cShConstBlock {
    void SetShConst(int idx, float a, float b, float c, float d);   // 0x77ca20 (thiscall)
};
struct cVec3 {
    float x, y, z;
    cVec3(float a, float b, float c) : x(a), y(b), z(c) {}
    cVec3(const cVec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cTables {                 // arg1 of the wrappers: lookup tables
    int pad0[10];
    float* floats;               // +0x28
    int pad1[4];
    cVec3* vec3s;                // +0x3c
    int pad2[4];
    float* vec2s;                // +0x50
    int pad3[4];
    float* vec2b;                // +0x64
};
struct cDesc {                   // arg2: descriptor, +0x10 -> byte array of table indices
    int pad0[4];
    unsigned char* idx;          // +0x10
};
struct cState {
    int pad0[4];
    cShConstBlock sh;            // +0x10 (embedded; the block's address is this+0x10)
    char pad1[0x170 - 0x14];
    float f170;                  // +0x170
    char pad2[0x188 - 0x174];
    float f188, f18c, f190;      // +0x188
    void ColorBE(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void ColorDC(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void W6f6c30(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void W6f6f40(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void W6f71f0(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    float GetDist();             // 0x6f4580
    void F54a0(unsigned long long flags, int p3, int p4, int p5, void* ptr, int count, int p6, int p7);  // 0x6f54a0
};
inline void* operator new(unsigned, void* p) { return p; }
struct cVec2 { int a; int b; cVec2() {} cVec2(const cVec2& o) : a(o.a), b(o.b) {} };
struct cFixedVec2 {              // eastl::fixed_vector<cVec2, 8> with overflow allocation
    cVec2* mpBegin; cVec2* mpEnd; cVec2* mpCap;
    int pad0; void* mpPool; int pad1;
    __declspec(align(8)) cVec2 buf[8];
    cFixedVec2() { mpPool = buf; mpBegin = mpEnd = buf; mpCap = buf + 8; }
    ~cFixedVec2() { if (mpBegin && mpBegin != mpPool) operator_delete_(mpBegin); }
    void DoInsertValue(cVec2* pos, const cVec2& v);    // 0x595870
    void push_back(const cVec2& v) {
        if (mpEnd < mpCap) { cVec2* e = mpEnd++; if (e) ::new (e) cVec2(v); }
        else DoInsertValue(mpEnd, v);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cByteVec {
    unsigned char* mpBegin;   // +0
    unsigned char* mpEnd;     // +4
    unsigned char* mpCap;     // +8
    unsigned char* DoAllocateAndCopy(unsigned n, const unsigned char* f, const unsigned char* l);   // 0x426950
    void DoInsertValue(unsigned char* pos, const unsigned char& v);                                  // 0x426730
    cByteVec& Assign(const cByteVec& x);           // operator= (named so the checker can find it)
    void erase(unsigned char* first, unsigned char* last) {
        memcpy(first, last, mpEnd - last);
        mpEnd -= (last - first);
    }
    void push_back(unsigned char v) {
        if (mpEnd < mpCap) { unsigned char* e = mpEnd++; if (e) *e = v; }
        else DoInsertValue(mpEnd, v);
    }
};
struct cRectID { int a; int b; };
struct cRttMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual int  Alloc(cRectID* out, int w, int h, int fmt, int p5, int p6, int p7);   // +0x10
    virtual void Free(int a, int b);                                                    // +0x14
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual void Register(int a, int b, const char* name);                              // +0x48
};
cRttMgr* __cdecl GetRttMgr();   // 0x67dda0 (FUN_0067dda0)
struct cRectVec {
    cRectID* mpBegin;     // +0x4c in the chain
    cRectID* mpEnd;
    cRectID* mpCap;
    void DoInsertValue(cRectID* pos, const cRectID& v);   // 0x6ec390
    void erase(cRectID* first, cRectID* last) {
        cRectID* e = mpEnd;
        cRectID* d = first;
        for (cRectID* src = last; src != e; ++src, ++d) *d = *src;
        mpEnd -= (last - first);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    void push_back(const cRectID& v) {
        if (mpEnd < mpCap) { cRectID* e = mpEnd++; if (e) *e = v; }
        else DoInsertValue(mpEnd, v);
    }
};
struct cFilterChain {
    char pad0[0x4c];
    cRectVec rects;                  // +0x4c
    char pad1[0x60 - 0x58];
    cByteVec flags;                  // +0x60
    bool AddCameraTexture(unsigned short w, unsigned short h, int* pIndex);
    void RemoveCameraTextures();
};
void* __cdecl operator new(unsigned sz, const char* tag, int a, int b, int c, int d);
struct cStateRec {
    cStateRec();                       // 0x6f5ed0
    char pad0[0x74];
    int f74;
    char pad1[0x8c - 0x78];
};
struct cViewer174 {
    cViewer174();                      // 0x7c3f70
    void Init(int a);                  // 0x7c4dd0
    char pad[0x174];
};
struct cStatePtrVec {
    cStateRec** mpBegin; cStateRec** mpEnd; cStateRec** mpCap;
    void DoInsertValue(cStateRec** pos, cStateRec* const& v);   // 0x6ec4a0
    void push_back(cStateRec* const& v) {
        if (mpEnd < mpCap) { cStateRec** e = mpEnd++; if (e) *e = v; }
        else DoInsertValue(mpEnd, v);
    }
};
struct cSvc1 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
               virtual void v5(); virtual void v6(); virtual void Reset(); };          // +0x1c
struct cMsgSrv { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                 virtual void v5(); virtual void v6(); virtual void v7(); virtual void Register(void* who, int msgId); };  // +0x20
cSvc1*   __cdecl GetSvc1();            // 0x67dd50
void*    __cdecl GetSvc2();            // 0x67dda0
void*    __cdecl GetSvc3();            // 0x67dd40
cMsgSrv* __cdecl GetMessageServer();   // 0x67dcc0
struct cVec3f {
    float x, y, z;
    cVec3f(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct cFilterChainInit {
    char pad0[4];
    int msgSlot;                       // +4 (address registered with the message server)
    char pad1[0x110 - 8];
    cVec3f color;                      // +0x110
    float alpha;                       // +0x11c
    char pad2[0x138 - 0x120];
    cStatePtrVec states;               // +0x138
    char pad3[0x164 - 0x144];
    void* svc2;                        // +0x164
    void* svc3;                        // +0x168
    char pad4[0x174 - 0x16c];
    cViewer174* viewers[4];            // +0x174
    char pad5[0x1b4 - 0x184];
    int stateIdx[2];                   // +0x1b4
    unsigned char bytes[12];           // +0x1bc
    float floats[12];                  // +0x1c8
    bool Init();
};
// ---- items of slice s006f6430 end

// ---- items of slice s006f7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_006f43e0(void* a, void* b, void* c);
struct cRefPtrVec {
    void ReleaseRange(void* b, void* e);    // 0x0070f520
};
struct cFilterChainSelf {
    void RemoveCameraTextures();            // 0x006f6910
};
struct cHashtableStr {
    void DoFreeNodes(void* b, void* e);     // 0x00693230
};
struct cHashtableKey {
    void DoFreeNodes(void* b, void* e);     // 0x007611f0
};
typedef unsigned long long u64;
void __cdecl FreeBlock(void* p) throw();   // 0xf47380 operator delete[]
struct Vec2 { float x, y; Vec2() {} Vec2(float a, float b) : x(a), y(b) {} Vec2(const Vec2& o) : x(o.x), y(o.y) {} };
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
struct FilterTables {
    char   pad0[0x28];
    float* floats;   // +0x28
    char   pad1[0x10];
    Vec3*  vec3s;    // +0x3c
    char   pad2[0x10];
    Vec2*  vec2s;    // +0x50
    char   pad3[0x10];
    u64*   keys;     // +0x64
};
struct FilterOp {
    char                  pad[0x10];
    const unsigned char*  s;   // +0x10 script bytes
};
struct ShaderConsts {
    void __thiscall SetShConst(int index, float a, float b, float c, float d);  // 0x77ca20
};
struct FixedVec64 {
    u64*     mpBegin;
    u64*     mpEnd;
    u64*     mpCap;
    uint32_t mPad;
    void*    mpPool;
    uint32_t mAlloc;
    __declspec(align(8)) u64 mBuf[8];

    FixedVec64() { mpPool = mBuf; mpBegin = mpEnd = mBuf; mpCap = mBuf + 8; }
    ~FixedVec64() {
        if (mpBegin && mpBegin != mpPool) FreeBlock(mpBegin);
    }
    void DoInsertValue(u64* pos, const u64& v);   // 0x595870
    void push_back(const u64& v) {
        u64 x = v;
        if (mpEnd < mpCap) { u64* p = mpEnd; mpEnd = p + 1; if (p) *p = x; }
        else DoInsertValue(mpEnd, x);
    }
};
struct cFilterChain_s006f_7430 {
    char         pad0[0x10];
    ShaderConsts mShader;            // +0x10
    char         pad1[0x127];
    float**      mpStrength;         // +0x138
    char         pad2[0x14];
    float        mOut150;            // +0x150
    char         pad3[4];
    float        mOut158;            // +0x158
    char         pad4[0x14];
    float        mf170;              // +0x170
    char         pad5[0x10];
    unsigned char mbOut184;          // +0x184
    char         pad6[0x1f];
    unsigned char mbF1a4;            // +0x1a4
    char         pad7[3];
    float        mOut1a8;            // +0x1a8
    char         pad8[0x10];
    unsigned char mbFlags[12];       // +0x1bc
    float        mVals[12];          // +0x1c8
    unsigned char mbLoaded;          // +0x1f8

    // 0x6f54a0: submit one filter pass with its key and the packed key array.
    void __thiscall Submit(u64 mode, int a, int b, int c, const u64* keys, int nKeys, int d, short e);
    float __thiscall GetDistanceToPlane();   // 0x6f4580
    float __thiscall DistanceQuery();        // 0x6f46f0
    float __thiscall GetPositionLength();    // 0x6f4930

    void Wrapper8c(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e);   // 0x6f7430
    void Wrapper200(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e);  // 0x6f7680
    void Dispatch(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e);    // 0x6f79a0
    void ApplyStrengthFilter(FilterTables* t, FilterOp* op, int a, int b, int c, int d, short e); // 0x6f7f70
};
// ---- items of slice s006f7430 end

// ---- items of slice s006f43e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_App();                              // 0x0067dd10 SP::App
extern "C" void* SP_LightingManager();                  // 0x0067dd90 SP::LightingManager
extern "C" void  cSPMatrix3_Assign(void* self, const void* src);   // 0x0041cb40
extern float g_16194f8;   // 0x16194f8  camera position x
extern float g_16194fc;   // 0x16194fc  camera position y
extern float g_1619500;   // 0x1619500  camera position z
extern float g_1619638[9]; // 0x1619638  Matrix33 data (row-major, 9 floats)
extern float g_1485720;   // 0x1485720  _HK_REAL_ONE = 1.0f
extern float g_13ec4b8;   // 0x13ec4b8  1e-08f
extern float g_1471064;   // 0x1471064  0.5f
extern float g_1486374;   // 0x1486374  0.8f
extern float g_13eecd8;   // 0x13eecd8  20.0f
extern float g_13ef580;   // 0x13ef580  0.02f
extern float g_13f56a4;   // 0x13f56a4  1.15f
extern float g_13ef74c;   // 0x13ef74c  0.15f
void  __cdecl FUN_007c40f0(void* a, void* b);      // 0x007c40f0
static inline void** Vt(void* p) { return *(void***)p; }
static inline void* CallSlot0(void* p, int slot) {
    return ((void* (__thiscall*)(void*))Vt(p)[slot])(p);
}
static void AddRef(void* p) { _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1); }
static void Release(void* p) {
    volatile long* rc = (volatile long*)((char*)p + 8);
    _InterlockedExchangeAdd(rc, -1);
    long c = _InterlockedExchangeAdd(rc, 0);
    if (c < 1) _InterlockedExchangeAdd(rc, 1);
}
struct CamVec { float x, y, z; float w; };   // 4 floats; w doubles as the homogeneous term
static void Camera_FetchPositions(CamVec* pos, float* light) {
    pos->x = g_16194f8;
    pos->y = g_16194fc;
    pos->z = g_1619500;
    pos->w = 0.0f;

    float mat[9];
    cSPMatrix3_Assign(mat, g_1619638);
    for (int i = 0; i < 9; ++i) mat[i] = g_1619638[i];

    pos->x = g_16194f8;
    pos->y = g_16194fc;
    pos->z = g_1619500;
    pos->w = g_1485720;

    void* app = SP_App();
    void* a2 = CallSlot0(app, 0x50 / 4);
    (*(void (__thiscall**)(void*, CamVec*))(Vt(a2)[0x1c / 4]))(a2, pos);
    FUN_007c40f0(pos, 0);

    void* lm = SP_LightingManager();
    (*(void (__thiscall**)(void*, float*))(Vt(lm)[0x24 / 4]))(lm, light);
}
// ---- items of slice s006f43e0 end

// ---- items of slice s006f54a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_0154df28[];          // shared empty-bucket sentinel stored at +0x10/+0x30 of the state struct
void  __cdecl FUN_00761dc0();
void* __cdecl FUN_0067dd60();
struct cColorCtx {
    char pad0[0x10];
    unsigned char* mRGB;   // +0x10
    char pad14[0x28 - 0x14];
    float* mColors;        // +0x28
    char pad2c[0x3c - 0x2c];
    char*  mTbl;           // +0x3c
};
struct Vec4f;
struct cBlob {
    void F77ca20(int a, float b, float c, float d, float e);
    void F77ca20v(int a, Vec4f v);       // same function, Vec4 passed by value
};
struct RKey { unsigned lo, hi; };
struct Vec4f {
    float x, y, z, w;
    Vec4f(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    Vec4f(const Vec4f& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct cViewer {
    void SetRaster(const RKey* key, int a);   // 0x007c4be0
    void F3c50(int a);                        // 0x007c3c50
    bool Update();                            // 0x007c4fd0
    void F3c10();                             // 0x007c3c10
};
struct EmbState {                             // rw::graphics::EmbeddedState
    char pad0[0x10];
    unsigned char mDirty;                     // +0x10
    void SetRaster(int slot, void* raster);   // 0x011ee6b0
};
struct HtNode { void* mpNext; int mIdx; int mIdx2; };
struct HtIter { HtNode* mpNode; void* mpBucket; };
struct HtU16 {                                // hashtable keyed by a 16-bit id
    int mpad0;
    HtNode** mpBuckets;                       // +4
    unsigned mnBuckets;                       // +8
    HtIter* find(HtIter* out, const unsigned* key);   // 0x00892970
};
struct HtKey64 {                              // hashtable keyed by a 64-bit RKey
    int mpad0;
    HtNode** mpBuckets;
    unsigned mnBuckets;
    HtIter* find(HtIter* out, const void* key);        // 0x00a7bf40
};
struct TexRef {
    void* mpRaster;                           // +0
    unsigned mFlags;                          // +4
    void* GetRaster();                        // 0x0046f260
};
struct cRaster { char pad0[0xc]; unsigned short w, h; };
struct cStateObj {                            // per-state resource record (0x7c+ bytes)
    char pad0[8];
    unsigned short mDefaultKey;               // +0x08 (index into mKeys, 0xffff = none)
    HtU16 mById;                              // +0x0c
    char pad18[0x2c - 0x18];
    HtKey64 mByKey;                           // +0x2c
    char pad38[0x4c - 0x38];
    RKey* mKeys;                              // +0x4c
    char pad50[0x60 - 0x50];
    unsigned char* mSeen;                     // +0x60
    char pad64[0x74 - 0x64];
    unsigned char mKindSeen[4];               // +0x74
    TexRef** mTex;                            // +0x78
};
struct MatNode { int pad0; EmbState* mpState; };
struct cState_s006f_54a0 {
    char pad00[0x10];
    char pad10[0x28 - 0x10];
    float* mColors;        // +0x28
    char pad2c[0x3c - 0x2c];
    char* mTbl;            // +0x3c
    char pad40[0x110 - 0x40];
    float mV[4];           // +0x110
    char pad120[0x138 - 0x120];
    cStateObj** mObjs;     // +0x138
    char pad13c[0x164 - 0x13c];
    void* mp164;           // +0x164
    void* mp168;           // +0x168

    void F54a0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, short a9);
    void Setup(EmbState* st, int n, Vec4f v);      // 0x006f4b90
    void W5f80(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6060(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W60f0(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6180(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
    void W6270(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7);
};
typedef void* (__thiscall *FnRes18)(void*, unsigned, unsigned);                      // mp164 +0x18
typedef void  (__thiscall *FnRes24)(void*, unsigned, unsigned, int*, int*, int*, int*); // mp164 +0x24
typedef void  (__thiscall *FnRes28)(void*, unsigned, unsigned, void*, void*);        // mp164 +0x28
typedef bool  (__thiscall *FnQ38)(void*);                                            // mp168 +0x38
typedef void* (__thiscall *FnQ50)(void*, int, int);                                  // mp168 +0x50
typedef void  (__thiscall *FnQA8)(void*, int, RKey*, int);                           // mp168 +0xa8
typedef void  (__thiscall *FnQDC)(void*, RKey*);                                     // mp168 +0xdc
typedef MatNode* (__thiscall *FnMat28)(void*, int);                                  // MaterialManager +0x28
typedef void  (__thiscall *FnMgr34)(void*, void*);                                   // manager at 0x67dd60 +0x34
static inline void** vtbl(void* p) { return *(void***)p; }
void* __cdecl MaterialManager();   // 0x0067dd70
static __forceinline void SetSizeConst(cState_s006f_54a0* self, float w, float h) {
    float iw = 1.0f / w;
    float ih = 1.0f / h;
    ((cBlob*)((char*)self + 0x10))->F77ca20v(2, Vec4f(w, h, iw, ih));
}
// ---- items of slice s006f54a0 end

// ---- items of slice s006f8380 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_ReadWriteBarrier)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
class cShaderDataCustom {
public:
  char pad[0x100];
  void Init();  // 0x0077d170
};
struct FilterElem28 {
  uint8_t  mFlags;      // +0x00
  uint8_t  mDest;       // +0x01
  uint8_t  pad02[6];    // +0x02
  uint32_t mSourceLo;   // +0x08
  uint32_t mSourceHi;   // +0x0c
  uint8_t* mBufBegin;   // +0x10
  uint8_t* mBufEnd;     // +0x14
  uint8_t* mBufCap;     // +0x18
  uint32_t mTail[4];    // +0x1c
};
struct cTexIndexBlock {
  uint8_t mIdx0;   // +0x00
  uint8_t mIdx1;   // +0x01
  uint8_t mIdx2;   // +0x02
  uint8_t mIdx3;   // +0x03
  uint8_t mIdx4;   // +0x04
  uint8_t pad05;   // +0x05
  uint8_t mIdx6;   // +0x06
};
struct FilterDesc78 {
  FilterElem28* mBegin;     // +0x00
  FilterElem28* mEnd;       // +0x04
  uint8_t  pad08[0xc];      // +0x08
  int32_t* mScaleTable;     // +0x14  (8-byte entries, biased backward by 0x100)
  uint8_t  pad18[0x10];     // +0x18
  float*   mStrengthTable;  // +0x28
  uint8_t  pad2c[0x38];     // +0x2c
  int32_t* mTextureTable;   // +0x64  (8-byte entries)
  uint8_t  pad68[0x10];     // +0x68
  void Destroy();           // va 006f66d0
};
struct cSlotNode {          // one slot->texture hash node
  uint16_t  mKey;           // +0x00
  uint8_t   pad02[6];       // +0x02
  cSlotNode* mNext;         // +0x08
};
struct cSlotHash {
  uint8_t   pad00[4];       // +0x0c
  cSlotNode** mArray;       // +0x10
  int32_t   mCount;         // +0x14
  int32_t   mField18;       // +0x18
  int32_t*  FindOrInsert(uint16_t* key);           // va 006f65d0
  void      ReleaseBuckets(void* array, int n);    // va 00693230
};
class cScreenFilter {
public:
  float      mStrength;     // +0x00
  int32_t    mField04;      // +0x04
  uint16_t   mSlot;         // +0x08
  uint16_t   pad0a;         // +0x0a
  cSlotHash  mHash;         // +0x0c
  uint8_t    pad1c[0x58];   // +0x1c
  int32_t    mField74;      // +0x74

  void RemoveCameraTextures();                        // va 006f6910
  bool AddCameraTexture(unsigned a, unsigned b, int* out); // va 006f6830
  void Apply(int a, int b, int c, void* d);           // va 006f5260
  void Resolve(uint32_t a, int b);                    // va 006f8260
  bool CreateScreenFilterInternal(FilterDesc78* d);   // va 006f87f0
};
class cViewer_s006f_8380;
class cRenderSystem {
public:
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void v0c();
  virtual void v10();
  virtual void v14();
  virtual void v18();
  virtual uint16_t* GetViewportInfo();       // +0x1c
  virtual void v20();
  virtual void v24();
  virtual void v28();
  virtual void v2c();
  virtual void v30();
  virtual void v34();
  virtual void v38();
  virtual void v3c();
  virtual void v40();
  virtual void v44();
  virtual void v48();
  virtual void AttachRenderTarget(void* obj, int a, int b);   // +0x4c
};
extern "C" cRenderSystem* GetRenderSystem(); // va 0067dd50
class cViewer_s006f_8380 {
public:
  bool Copy(cViewer_s006f_8380* src, bool a, bool b);  // va 007c50b0 0x007c50b0
  void ApplyFrustum(float a, float b);      // va 007c4ad0
};
class cFilterChain_s006f_8380 {
public:
  void*  vtbl0;                 // +0x000
  void*  vtbl1;                 // +0x004
  void*  vtbl2;                 // +0x008
  int32_t m00c;                 // +0x00c
  cShaderDataCustom mCustomSD;  // +0x010
  float  m110, m114, m118;      // +0x110
  float  m11c;                  // +0x11c
  uint8_t* mDescBegin;          // +0x120
  uint8_t* mDescEnd;            // +0x124
  uint8_t* mDescCap;            // +0x128
  uint8_t pad12c[8];            // +0x12c
  uint8_t m134;                 // +0x134
  uint8_t pad135[3];            // +0x135
  void**  mTexBegin;            // +0x138
  void**  mTexEnd;              // +0x13c
  void**  mTexCap;              // +0x140
  uint8_t pad144[8];            // +0x144
  float  m14c, m150, m154, m158, m15c, m160;
  uint8_t pad164[0xc];          // +0x164
  float  m170;                  // +0x170
  uint8_t pad174[8];            // +0x174
  cViewer_s006f_8380* mViewer;             // +0x17c
  uint8_t pad180[4];            // +0x180
  uint8_t m184;                 // +0x184
  uint8_t pad185[3];            // +0x185
  float  m188, m18c, m190, m194, m198, m19c, m1a0;
  uint8_t m1a4;                 // +0x1a4
  uint8_t pad1a5[3];            // +0x1a5
  float  m1a8, m1ac, m1b0;
  int32_t mIndex[17];           // +0x1b4
  uint8_t m1f8;                 // +0x1f8
  uint8_t pad1f9[3];            // +0x1f9
  uint8_t* mBitsBegin;          // +0x1fc
  uint8_t* mBitsEnd;            // +0x200
  uint8_t* mBitsCap;            // +0x204
  uint8_t pad208[8];            // +0x208
  uint16_t* mArrBegin;          // +0x210
  uint16_t* mArrEnd;            // +0x214
  uint16_t* mArrCap;            // +0x218
  uint8_t pad21c[8];            // +0x21c
  int32_t m224;                 // +0x224

  cFilterChain_s006f_8380();
  ~cFilterChain_s006f_8380();

  // thiscall callees (bodies live elsewhere in the binary).
  void Op0(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6c30
  void Op1(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f5f80
  void Op2(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6f40
  void Op3(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f71f0
  void Op4(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6060
  void Op5(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f60f0
  void Op6(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6180
  void Op7(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f6270
  void Op8(void* d, void* e, int a, int b, int c, int viewer, int p5);   // va 006f7430
  void Op12(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f6430
  void Op13(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f7680
  void Op15(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f6500
  void Op16(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f79a0
  void Op17(void* d, void* e, int a, int b, int c, int viewer, int p5);  // va 006f7f70
  void OpBig(int a0, int a1, int a, int b, int c, int a5, int a6, int viewer, int p5); // va 006f54a0
  void RemoveAt(int idx);
  void ApplyFilters(FilterDesc78* d, uint16_t count, int* p4, int p5);
};
// ---- items of slice s006f8380 end

// ---- items of slice s006f9250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl EASTL_deallocate_(void* p);            // 0x00f47380 (allocator free)
extern "C" int   __cdecl ReportCleanup();                       // 0x0067dcc0
struct Elem14 { char pad[0x14]; Elem14& operator=(const Elem14&); ~Elem14(); };
struct Elem78 {
  Elem14 m0, m1, m2, m3, m4, m5;
  Elem78& operator=(const Elem78&);
};
struct Vec78 {
  Elem78* begin;
  Elem78* end;
  Elem78* cap;
  Elem78* erase(Elem78* first, Elem78* last);  // 0x006f9a50
};
struct FilterElem28_s006f_9250 {                                  // 0x28 bytes
  FilterElem28_s006f_9250& operator=(const FilterElem28_s006f_9250&);
};
struct Vec28 {
  FilterElem28_s006f_9250* begin;   // +0
  FilterElem28_s006f_9250* end;     // +4
  FilterElem28_s006f_9250* cap;     // +8
  Vec28& operator=(const Vec28&);                      // 0x006f9730
};
struct Vec8 {                                          // generic 8-byte-element vector
  void* begin; void* end; void* cap;
  void assign(const Vec8& src);                        // reserve + memmove
};
struct Vec12 {                                          // 12-byte-element vector
  void* begin; void* end; void* cap;
};
struct Vec4 {                                           // 4-byte-element vector
  void* begin; void* end; void* cap;
};
struct FilterDesc {                                     // the 0x78-byte descriptor
  Vec28  v00;   // +0x00  (vector<FilterElem28>)
  Vec8   v14;   // +0x14  (8-byte elements)
  Vec4   v28;   // +0x28  (4-byte elements)
  Vec12  v3c;   // +0x3c  (12-byte elements)
  Vec8   v50;   // +0x50  (8-byte elements)
  Vec8   v64;   // +0x64  (8-byte elements)

  void AssignDescA(const FilterDesc* src);             // 0x006f9520
  void AssignDescB(const FilterDesc* src);             // 0x006f95e0
};
struct CFilterChain {
  char pad0[0x120];
  Vec78* m120;             // +0x120  vector<0x78-byte filter records> begin
  Vec78* m124;             // +0x124  end
  char pad128[0x8];
  void* m130;              // +0x130
  char pad134[4];
  void** m138;             // +0x138  texture-object table (2 entries)
  char pad13c[0x38];
  int m174;                // +0x174
  int m178;                // +0x178
  int m17c;                // +0x17c
  int m180;                // +0x180
  char pad184[0x74];
  uint8_t m1f8;            // +0x1f8
  char pad1f9[3];
  uint8_t* m1fc;           // +0x1fc  vector<bool> begin
  uint8_t* m200;           // +0x200  end
  uint8_t* m204;           // +0x204  cap
  char pad208[8];
  uint16_t* m210;          // +0x210  vector<u16> begin
  uint16_t* m214;          // +0x214  end
  uint16_t* m218;          // +0x218  cap
  int mIndex[17];          // +0x1b4  (overlaps the block above; per-filter state)
  int m224;                // +0x224

  bool AddFilterChain(int a, int b);            // 0x006f9250
  void Notify2(int a, int b);                   // 0x006f9ac0
  void Shutdown();                              // 0x006f9cf0
  void Notify3(int a, int* out, unsigned short c); // 0x006f9e20
  void ApplyFilters(FilterDesc* d, uint16_t count, int* p4, int p5); // 0x006f8380
  void SubSF(int a, int b);                     // 0x006f9c70
};
// ---- items of slice s006f9250 end

// @ 0x006f43e0
void FUN_006f43e0(void** first, void** last, void** dest)
{
    for (; first != last; ++first, ++dest) {
        void* s = *first;
        void* d = *dest;
        if (s != d) {
            if (s) AddRef(s);
            *dest = s;
            if (d) Release(d);
        }
    }
}

// @ 0x006f4580
float FUN_006f4580()
{
    CamVec pos;
    float light[3];
    Camera_FetchPositions(&pos, light);

    float len = sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + g_13ec4b8);
    float inv = 1.0f / len;

    float nx = pos.x * inv;
    float ny = pos.y * inv;
    float nz = pos.z * inv;

    return 1.0f - ((nx * light[0] + nz * light[2] + ny * light[1]) + 1.0f) * g_1471064;
}

// @ 0x006f46f0
float __fastcall FUN_006f46f0(char* self)
{
    CamVec pos;
    float light[3];
    Camera_FetchPositions(&pos, light);

    float dx = pos.x - *(float*)(self + 0x194);
    float dy = pos.y - *(float*)(self + 0x198);
    float dz = pos.z - *(float*)(self + 0x19c);
    float dist = fabsf(sqrtf(dx * dx + dy * dy + dz * dz));

    float cachedRadius = *(float*)(self + 0x1a0);

    float scale = (dist <= cachedRadius) ? 1.0f : g_1486374;

    float camLen = fabsf(sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) -
                         sqrtf(*(float*)(self + 0x194) * *(float*)(self + 0x194) +
                               *(float*)(self + 0x198) * *(float*)(self + 0x198) +
                               *(float*)(self + 0x19c) * *(float*)(self + 0x19c)) + dist);
    float v = (camLen - cachedRadius) * scale + cachedRadius;

    float result;
    if (g_13eecd8 <= v)
        result = g_13f56a4 - v * g_13ef580;
    else
        result = 1.0f;

    if (result < g_13ef74c) result = g_13ef74c;
    if (result > 1.0f) result = 1.0f;

    *(float*)(self + 0x194) = pos.x;
    *(float*)(self + 0x198) = pos.y;
    *(float*)(self + 0x19c) = pos.z;
    *(float*)(self + 0x1a0) = dist;
    return result;
}

// @ 0x006f4930
float FUN_006f4930()
{
    CamVec pos;
    float light[3];
    Camera_FetchPositions(&pos, light);
    return sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
}

// @ 0x006f54a0
void cState_s006f_54a0::F54a0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, short a9)
{
    (void)a2;
    cViewer* viewer = (cViewer*)a8;
    RKey* table = (RKey*)a6;
    cStateObj* o = mObjs[(short)a9];
    unsigned char kind = (unsigned char)a5;

    if (kind == 1) {
        if (((FnQ38)vtbl(mp168)[0x38 / 4])(mp168)) {
            RKey key;
            key.lo = key.hi = 0xffffffff;
            ((FnQDC)vtbl(mp168)[0xdc / 4])(mp168, &key);
            viewer->SetRaster(&key, 1);
        }
    } else if ((unsigned char)(kind - 2) <= 3) {
        int n = kind - 2;
        void* r = ((FnQ50)vtbl(mp168)[0x50 / 4])(mp168, n, 0);
        if (r) {
            RKey key;
            key.lo = key.hi = 0xffffffff;
            ((FnQA8)vtbl(mp168)[0xa8 / 4])(mp168, n, &key, 1);
            viewer->SetRaster(&key, 1);
            if (o->mKindSeen[n] == 0) {
                viewer->F3c50(1);
                o->mKindSeen[n] = 1;
            }
        }
    } else if (kind == 0x41) {
        if ((unsigned short)a9 == 0) {
            cStateObj* o1 = mObjs[1];
            RKey key;
            key.lo = key.hi = 0xffffffff;
            unsigned short d = o1->mDefaultKey;
            if (d != 0xffff)
                key = o1->mKeys[d];
            if (((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, key.lo, key.hi))
                viewer->SetRaster(&key, 1);
        }
    } else {
        unsigned kk = kind;
        HtIter itBuf;
        HtIter* it = o->mById.find(&itBuf, &kk);
        HtNode* node = it->mpNode;
        if (node != o->mById.mpBuckets[o->mById.mnBuckets]) {
            RKey* ent = &o->mKeys[node->mIdx];
            if (((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, ent->lo, ent->hi)) {
                viewer->SetRaster(ent, 1);
                if (o->mSeen[node->mIdx] == 0) {
                    viewer->F3c50(1);
                    o->mSeen[node->mIdx] = 1;
                }
            }
        }
    }

    if (!viewer->Update())
        return;

    FUN_00761dc0();
    void* mgr = MaterialManager();
    EmbState* st = ((FnMat28)vtbl(mgr)[0x28 / 4])(mgr, a1)->mpState;

    unsigned long long key64 = ((unsigned long long)(unsigned)a4 << 32) | (unsigned)a3;
    if ((a3 | a4) == 0) {
        if (st->mDirty & 1) {
            RKey key;
            key.lo = key.hi = 0xffffffff;
            unsigned short d = o->mDefaultKey;
            if (d != 0xffff)
                key = o->mKeys[d];
            void* r = ((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, key.lo, key.hi);
            if (r) {
                int u, v, s1, s2;
                st->SetRaster(0, r);
                ((FnRes24)vtbl(mp164)[0x24 / 4])(mp164, key.lo, key.hi, &s2, &s1, &u, &v);
                SetSizeConst(this, (float)u, (float)v);
            }
        }
    } else if (key64 - 2 < 4) {
        if (st->mDirty & 1) {
            int n = (unsigned short)a3 - 2;
            cRaster* r = (cRaster*)((FnQ50)vtbl(mp168)[0x50 / 4])(mp168, n, 0);
            RKey key2;
            key2.lo = key2.hi = 0xffffffff;
            ((FnQA8)vtbl(mp168)[0xa8 / 4])(mp168, n, &key2, 1);
            if (r) {
                st->SetRaster(0, r);
                SetSizeConst(this, (float)r->w, (float)r->h);
            }
        }
    } else {
        unsigned kk = (unsigned short)a3;
        HtIter itBuf;
        HtIter* it = o->mById.find(&itBuf, &kk);
        HtNode* node = it->mpNode;
        if (node != o->mById.mpBuckets[o->mById.mnBuckets]) {
            RKey* ent = &o->mKeys[node->mIdx];
            unsigned lo = ent->lo, hi = ent->hi;
            void* r = ((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, lo, hi);
            if (r) {
                int u, v, s1, s2;
                st->SetRaster(0, r);
                ((FnRes24)vtbl(mp164)[0x24 / 4])(mp164, lo, hi, &s1, &s2, &u, &v);
                SetSizeConst(this, (float)u, (float)v);
            }
        } else {
            HtIter itBuf2;
            HtIter* it2 = o->mByKey.find(&itBuf2, &key64);
            HtNode* node2 = it2->mpNode;
            if (node2 != o->mByKey.mpBuckets[o->mByKey.mnBuckets]) {
                TexRef* t = o->mTex[node2->mIdx2];
                cRaster* r = (cRaster*)t->GetRaster();
                st->SetRaster(0, r);
                SetSizeConst(this, (float)r->w, (float)r->h);
            }
        }
    }

    unsigned count = (unsigned)a7;
    if (count - 1 < 4 && count > 0) {
        for (unsigned short k = 0; k < count; ++k) {
            RKey* e = &table[k];
            unsigned kk = (unsigned short)e->lo;
            HtIter itBuf;
            HtIter* it = o->mById.find(&itBuf, &kk);
            HtNode* node = it->mpNode;
            if (node != o->mById.mpBuckets[o->mById.mnBuckets]) {
                RKey* ent = &o->mKeys[node->mIdx];
                unsigned lo = ent->lo, hi = ent->hi;
                void* r = ((FnRes18)vtbl(mp164)[0x18 / 4])(mp164, lo, hi);
                int i0, i1, i2, i3, j0, j1;
                ((FnRes24)vtbl(mp164)[0x24 / 4])(mp164, lo, hi, &i0, &i1, &i2, &i3);
                ((FnRes28)vtbl(mp164)[0x28 / 4])(mp164, lo, hi, &j0, &j1);
                st->SetRaster(k + 1, r);
            } else {
                unsigned long long ek = *(unsigned long long*)e;
                if (ek > 1 && ek < 6) {
                    void* r = ((FnQ50)vtbl(mp168)[0x50 / 4])(mp168, (int)kk - 2, 0);
                    if (r)
                        st->SetRaster(k + 1, r);
                } else {
                    HtIter itBuf2;
                    HtIter* it2 = o->mByKey.find(&itBuf2, e);
                    HtNode* node2 = it2->mpNode;
                    if (node2 != o->mByKey.mpBuckets[o->mByKey.mnBuckets]) {
                        TexRef* t = o->mTex[node2->mIdx2];
                        if (!(t->mFlags & 1)) {
                            void* m = FUN_0067dd60();
                            ((FnMgr34)vtbl(m)[0x34 / 4])(m, t);
                        }
                        st->SetRaster(k + 1, t->mpRaster);
                    }
                }
            }
        }
    }

    Setup(st, 2, Vec4f(mV[0], mV[1], mV[2], mV[3]));
    viewer->F3c10();
}

// @ 0x006f5ed0
int* __fastcall FUN_006f5ed0(int* self)
{
    self[0] = 0;
    self[1] = 0;
    *(unsigned short*)(self + 2) = 0xffff;
    self[7] = 0x3f800000;
    self[8] = 0x40000000;
    self[5] = 1;
    self[4] = (int)g_0154df28;
    self[6] = 0;
    self[9] = 0;
    self[0xf] = 0x3f800000;
    self[0x10] = 0x40000000;
    self[0xe] = 0;
    self[0x11] = 0;
    self[0xd] = 1;
    self[0xc] = (int)g_0154df28;
    self[0x13] = 0;
    self[0x14] = 0;
    self[0x15] = 0;
    self[0x18] = 0;
    self[0x19] = 0;
    self[0x1a] = 0;
    self[0x1e] = 0;
    self[0x1f] = 0;
    self[0x20] = 0;
    return self;
}

// @ 0x006f6830
bool cFilterChain::AddCameraTexture(unsigned short w, unsigned short h, int* pIndex)
{
    cRectID id;
    GetRttMgr()->Alloc(&id, w, h, 0x15, 0, -1, 0);
    if (id.a != -1) {
        GetRttMgr()->Register(id.a, id.b, "FilterChain");
        rects.push_back(id);
        flags.push_back(0);
        *pIndex = rects.size() - 1;
        return true;
    }
    return false;
}

// @ 0x006f6910
void cFilterChain::RemoveCameraTextures()
{
    if (rects.mpBegin != rects.mpEnd) {
        unsigned short n = (unsigned short)(rects.mpEnd - rects.mpBegin);
        int off = 0;
        for (unsigned short i = 0; i < n; ++i) {
            GetRttMgr()->Free(*(int*)((char*)rects.mpBegin + off), *(int*)((char*)rects.mpBegin + off + 4));
            off += 8;
        }
        rects.erase(rects.mpBegin, rects.mpEnd);
        flags.erase(flags.mpBegin, flags.mpEnd);
    }
}

// @ 0x006f69c0
bool cFilterChainInit::Init()
{
    cStateRec* p;
    for (int i = 0; i < 2; ++i) {
        stateIdx[i] = -1;
        p = new ("Graphics", 0, 0, 0, 0) cStateRec();
        p->f74 = 0;
        states.push_back(p);
    }
    GetSvc1()->Reset();
    color = cVec3f(255.0f, 255.0f, 255.0f);
    alpha = 255.0f;
    svc2 = GetSvc2();
    svc3 = GetSvc3();
    viewers[0] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[0]->Init(0);
    viewers[1] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[1]->Init(0);
    viewers[2] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[2]->Init(0);
    viewers[3] = new ("Graphics", 0, 0, 0, 0) cViewer174();
    viewers[3]->Init(0);
    for (unsigned i = 0; i < 12; ++i) {
        bytes[i] = 0;
        floats[i] = 0.0f;
    }
    GetMessageServer()->Register(&msgSlot, 0x44edd9c);
    return true;
}

// @ 0x006f6c30
void cState::W6f6c30(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    unsigned char* ix = d->idx;
    float c0x = 1.0f, c0y = 1.0f, c0z = 1.0f, c0w = 0.5f;
    float c1x = 0.0f, c1y = 1.0f, c1z = 1.0f, c1w = 0.0f;
    float c3x = 0.0f, c3y = 0.0f;
    unsigned long long flags = 0x28;
    if (ix[0]) flags = 0x2a;
    else if (ix[1]) flags = 0x2c;
    else if (ix[2]) flags = 0x2e;
    else if (ix[6] != 0xff) flags = 0x30;
    if (ix[9]) { c1w = 1.0f; flags = 0xe8; }
    if (ix[3]) flags += 1;
    unsigned short u;
    u = ix[4]; if (u != 0xff) c0w = t->floats[u];
    u = ix[5]; if (u != 0xff) { cVec3 v(t->vec3s[u]); c0x = v.x; c0y = v.y; c0z = v.z; }
    u = ix[7]; if (u != 0xff) c1x = t->floats[u];
    u = ix[8]; if (u != 0xff) { c1y = ((float*)t->vec2s)[u * 2]; c1z = ((float*)t->vec2s)[u * 2 + 1]; }
    u = ix[10]; if (u != 0xff) { c3x = ((float*)t->vec2s)[u * 2]; c3y = ((float*)t->vec2s)[u * 2 + 1]; }
    sh.SetShConst(0, c0x, c0y, c0z, c0w);
    sh.SetShConst(1, c1x, c1y, c1z, c1w);
    sh.SetShConst(3, c3x, c3y, 0.0f, 0.0f);
    cFixedVec2 vec;
    u = d->idx[6]; if (u != 0xff) vec.push_back(((cVec2*)t->vec2b)[u]);
    F54a0(flags, p3, p4, p5, vec.mpBegin, vec.size(), p6, p7);
}

// @ 0x006f6f40
void cState::W6f6f40(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    unsigned char* ix = d->idx;
    float a = 1.0f, b = 1.0f, c = 1.0f, e = 1.0f, g = 0.0f;
    unsigned long long flags = 0x3c;
    if (ix[2]) flags = 0x3e;
    if (ix[1]) flags += 1;
    unsigned short u;
    u = ix[3]; if (u != 0xff) a = t->floats[u];
    u = ix[4]; if (u != 0xff) b = t->floats[u];
    u = ix[5]; if (u != 0xff) { c = ((float*)t->vec2s)[u * 2]; e = ((float*)t->vec2s)[u * 2 + 1]; }
    u = ix[7]; if (u != 0xff) g = t->floats[u];
    sh.SetShConst(0, a, b, c, e);
    sh.SetShConst(1, g, 0.0f, 0.0f, 0.0f);
    cFixedVec2 vec;
    u = d->idx[0]; if (u != 0xff) vec.push_back(((cVec2*)t->vec2b)[u]);
    u = d->idx[6];
    if (u != 0xff) {
        cVec2 v = ((cVec2*)t->vec2b)[u];
        vec.push_back(v);
        flags += 4;
    }
    if (d->idx[8]) flags += 8;
    F54a0(flags, p3, p4, p5, vec.mpBegin, vec.size(), p6, p7);
}

// @ 0x006f71f0
void cState::W6f71f0(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    unsigned char* ix = d->idx;
    float c0w = 0.5f;
    float c0x = 1.0f, c0y = 1.0f, c0z = 1.0f;
    unsigned long long flags = 0x46;
    float f2 = 0.5f;
    unsigned short u;
    u = ix[1]; if (u != 0xff) c0w = t->floats[u];
    u = ix[0]; if (u != 0xff) { cVec3 v(t->vec3s[u]); c0x = v.x; c0y = v.y; c0z = v.z; }
    cFixedVec2 vec;
    u = ix[2];
    if (u != 0xff) {
        vec.push_back(((cVec2*)t->vec2b)[u]);
        flags = 0x47;
        f2 = GetDist();
        if (f170 == 1.0f) f170 = 1.1f;
    } else if (ix[3]) {
        flags = 0x48;
    }
    sh.SetShConst(0, c0x, c0y, c0z, c0w);
    sh.SetShConst(1, f2, f170, 0.0f, 0.0f);
    sh.SetShConst(3, f188, f18c, f190, 0.0f);
    F54a0(flags, p3, p4, p5, vec.mpBegin, vec.size(), p6, p7);
}

// @ 0x006f7430
void cFilterChain_s006f_7430::Wrapper8c(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e)
{
    const unsigned char* s = op->s;
    float f1 = 0.0f, f2 = 0.0f;
    float px = 0.0f, py = 0.0f;
    float qx = 1.0f, qy = 1.0f;
    float f3 = 10.0f;
    unsigned short i;
    i = s[1]; if (i != 0xff) f1 = t->floats[i];
    i = s[2]; if (i != 0xff) f2 = t->floats[i];
    i = s[3]; if (i != 0xff) f3 = t->floats[i];
    i = s[4]; if (i != 0xff) { Vec2 w = t->vec2s[i]; px = w.x; py = w.y; }
    i = s[5]; if (i != 0xff) { Vec2 w = t->vec2s[i]; qx = w.x; qy = w.y; }
    mShader.SetShConst(0, f1, f2, f3, f3);
    mShader.SetShConst(1, px, py, qx, qy);
    FixedVec64 v;
    i = op->s[0];
    if (i != 0xff) v.push_back(t->keys[i]);
    Submit(0x8c, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// @ 0x006f7680
void cFilterChain_s006f_7430::Wrapper200(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e)
{
    const unsigned char* s = op->s;
    float g1 = 1.0f, g2 = 1.0f;
    float px = 1.0f, py = 1.0f;
    float vx = 1.0f, vy = 1.0f, vz = 1.0f;
    float wx = 0.0f, wy = 0.0f;
    float g3 = 0.0f, g4 = 0.0f;
    u64 mode = 200;
    unsigned short i;
    i = s[1]; if (i != 0xff) g1 = t->floats[i];
    i = s[2]; if (i != 0xff) g2 = t->floats[i];
    i = s[7]; if (i != 0xff) g3 = t->floats[i];
    i = s[8]; if (i != 0xff) g4 = t->floats[i];
    i = s[3]; if (i != 0xff) { Vec2 w = t->vec2s[i]; px = w.x; py = w.y; }
    i = s[4];
    if (i != 0xff) {
        mode = 201;
        Vec3 w = t->vec3s[i];
        vx = w.x; vy = w.y; vz = w.z;
    }
    if (s[5]) mode++;
    i = s[6]; if (i != 0xff) { Vec2 w = t->vec2s[i]; wx = w.x; wy = w.y; }
    mShader.SetShConst(0, g1, g2, px, py);
    mShader.SetShConst(1, vx, vy, vz, 0.0f);
    mShader.SetShConst(3, wx, wy, g3, g4);
    FixedVec64 v;
    i = op->s[0];
    if (i != 0xff) v.push_back(t->keys[i]);
    Submit(mode, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// @ 0x006f79a0
void cFilterChain_s006f_7430::Dispatch(FilterTables* t, FilterOp* op, int a, int b, int c, int d, int e)
{
    float lo, hi;
    float f[12];
    f[0] = 0.0f;
    f[1] = 0.0f;
    f[2] = 0.0f;
    f[3] = 0.0f;
    f[4] = 0.0f;
    f[5] = 0.0f;
    f[6] = 0.0f;
    f[7] = 0.0f;
    f[8] = 0.0f;
    f[9] = 0.0f;
    f[10] = 0.0f;
    f[11] = 0.0f;
    u64 mode = 0;
    const unsigned char* s = op->s;
    unsigned short i = s[0];
    if (i != 0xff) mode = t->keys[i];
    for (int k = 0; k < 8; k++) {
        i = s[5 + k];
        if (i != 0xff) f[k] = t->floats[i];
    }
    if (s[0xf]) {
        f[8] = GetDistanceToPlane();
        if (mf170 == 1.0f) mf170 = 1.1f;
        f[9] = mf170;
    }
    if (op->s[0x10]) f[10] = DistanceQuery();
    if (op->s[0x11] && !mbLoaded) {
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 6; k++)
                if (mbFlags[j * 6 + k]) f[j * 6 + k] = mVals[j * 6 + k];
        mbLoaded = 1;
    }
    mShader.SetShConst(0, f[0], f[1], f[2], f[3]);
    mShader.SetShConst(1, f[4], f[5], f[6], f[7]);
    mShader.SetShConst(3, f[8], f[9], f[10], f[11]);
    FixedVec64 v;
    i = op->s[1];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    i = op->s[2];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    i = op->s[3];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    i = op->s[4];
    if (i != 0xff) { u64 k = t->keys[i]; v.push_back(k); }
    if (op->s[0xd]) {
        mbOut184 = 1;
        s = op->s;
        float x;
        i = s[0xe];
        if (i != 0xff) {
            x = t->floats[i];
        } else {
            lo = 500.0f; hi = 1800.0f;
            if (s[9] != 0xff) lo = f[4];
            if (s[0xa] != 0xff) hi = f[5];
            float r = (GetPositionLength() - lo) / hi;
            x = f[2] + r * (f[3] - f[2]);
        }
        mOut150 = x;
        if (!mbF1a4) mOut1a8 = f[0];
        mOut158 = f[1];
    }
    Submit(mode, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// @ 0x006f7f70
void cFilterChain_s006f_7430::ApplyStrengthFilter(FilterTables* t, FilterOp* op, int a, int b, int c, int d, short e)
{
    const unsigned char* s = op->s;
    float scale = 1.0f;
    unsigned short i = s[0];
    if (i != 0xff) scale = t->floats[i];
    float strength = *mpStrength[e] / scale;
    if (s[1]) strength = 1.0f - strength;
    mShader.SetShConst(0, strength, 0.0f, 0.0f, 0.0f);
    mShader.SetShConst(1, 0.0f, 0.0f, 0.0f, 0.0f);
    mShader.SetShConst(3, 0.0f, 0.0f, 0.0f, 0.0f);
    FixedVec64 v;
    i = op->s[3];
    if (i != 0xff) v.push_back(t->keys[i]);
    Submit(0xa399efc5ULL, a, b, c, v.mpBegin, (int)(v.mpEnd - v.mpBegin), d, e);
}

// @ 0x006f8190
void __fastcall FUN_006f8190(int self)
{
    ((cFilterChainSelf*)self)->RemoveCameraTextures();
    int* v = (int*)(self + 0x78);
    unsigned i = 0;
    if ((*(int*)(self + 0x7c) - *v) >> 2 != 0) {
        do {
            int* p = (int*)(*v + i * 4);
            int obj = *p;
            if (obj != 0) {
                *p = 0;
                volatile long* rc = (volatile long*)(obj + 8);
                _InterlockedExchangeAdd(rc, -1);
                long c = _InterlockedExchangeAdd(rc, 0);
                if (c < 1) _InterlockedExchangeAdd(rc, 1);
            }
            i++;
        } while (i < (unsigned)(*(int*)(self + 0x7c) - *v >> 2));
    }
    int begin = *v;
    int end = *(int*)(self + 0x7c);
    void* r = FUN_006f43e0((void*)end, (void*)end, (void*)begin);
    ((cRefPtrVec*)v)->ReleaseRange(r, *(void**)(self + 0x7c));
    *(int*)(self + 0x7c) = *(int*)(self + 0x7c) + (end - begin >> 2) * -4;
    ((cHashtableStr*)(self + 0xc))->DoFreeNodes(*(void**)(self + 0x10), *(void**)(self + 0x14));
    *(void**)(self + 0x18) = 0;
    ((cHashtableKey*)(self + 0x2c))->DoFreeNodes(*(void**)(self + 0x30), *(void**)(self + 0x34));
    *(void**)(self + 0x38) = 0;
}

// @ 0x006f8380
void cFilterChain_s006f_8380::ApplyFilters(FilterDesc78* d, uint16_t count, int* p4, int p5)
{
  if (count == 0) return;
  int last = (int)count - 1;
  for (int i = 0; i < (int)count; ++i) {
    FilterElem28* e = (FilterElem28*)((char*)d->mBegin + i * 0x28);
    uint8_t dest = e->mDest;
    int srcLo = (int)e->mSourceLo;
    int srcHi = (int)e->mSourceHi;
    if (m134) {
      ((cScreenFilter*)mTexBegin[(int)(int16_t)p5])->Apply(srcLo, srcHi, dest, p4);
    }
    mViewer->Copy((cViewer_s006f_8380*)*p4, false, false);
    mViewer->ApplyFrustum(0.0f, 0.0f);
    if (i < last) {
      FilterElem28* nxt = (FilterElem28*)((char*)d->mBegin + i * 0x28 + 0x28);
      if (nxt->mFlags == 0x11) {
        cScreenFilter* f = (cScreenFilter*)mTexBegin[(int)(int16_t)p5];
        if (!(0.0f < f->mStrength) && f->mField04 == 0) {
          dest = nxt->mDest;
        }
      }
    }
    switch (e->mFlags) {
      case 0:  Op0(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 1:  Op1(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 2:  Op2(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 3:  Op3(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 4:  Op4(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 5:  Op5(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 6:  Op6(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 7:  Op7(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 8:  OpBig(0x78, 0, srcLo, srcHi, dest, 0, 0, (int)mViewer, p5); break;
      case 9:  OpBig(0x82, 0, srcLo, srcHi, dest, 0, 0, (int)mViewer, p5); break;
      case 10: Op8(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 12: Op12(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 13: Op13(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 14: OpBig(0xd2, 0, srcLo, srcHi, dest, 0, 0, (int)mViewer, p5); break;
      case 15: Op15(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 16: Op16(d, e, srcLo, srcHi, dest, (int)mViewer, p5); break;
      case 17: {
        cScreenFilter* f = (cScreenFilter*)mTexBegin[(int)(int16_t)p5];
        if (0.0f < f->mStrength)
          Op17(d, e, srcLo, srcHi, dest, (int)mViewer, p5);
        break;
      }
      default: break;
    }
  }
}

// @ 0x006f87f0
bool cScreenFilter::CreateScreenFilterInternal(FilterDesc78* d)
{
  RemoveCameraTextures();
  mHash.ReleaseBuckets(mHash.mArray, mHash.mCount);
  mHash.mField18 = 0;
  mField74 = 0;

  uint16_t* info = GetRenderSystem()->GetViewportInfo();
  uint16_t uVar2 = info[0];
  uint16_t uVar3 = info[2];

  int out = 0;
  if (!AddCameraTexture(uVar2, uVar3, &out)) {
    mSlot = 0xffff;
  } else {
    mSlot = (uint16_t)out;
  }

  char* base = (char*)d->mBegin;
  if (d->mBegin == d->mEnd)
    return true;
  uint16_t counter = (uint16_t)(uint32_t)(((char*)d->mEnd - (char*)d->mBegin) / 0x28);
  if (counter == 0)
    return true;

  int off = 0;
  do {
    FilterElem28* e = (FilterElem28*)(base + off);
    uint8_t dest = e->mDest;
    uint32_t srcLo = e->mSourceLo;
    int srcHi = (int)e->mSourceHi;
    cTexIndexBlock* tb = (cTexIndexBlock*)e->mBufBegin;

    // ---- look the source slot up in this filter's hash table.
    cSlotNode* node = mHash.mArray[(srcLo & 0xffff) % (uint32_t)mHash.mCount];
    cSlotNode* endNode = mHash.mArray[mHash.mCount];
    while (node != 0) {
      if ((uint16_t)srcLo == node->mKey) break;
      node = node->mNext;
    }
    bool sourceKnown = ((node ? node : endNode) != endNode);

    // ---- and the destination slot too.
    cSlotNode* dnode = mHash.mArray[((uint32_t)dest) % (uint32_t)mHash.mCount];
    while (dnode != 0) {
      if ((uint16_t)dest == dnode->mKey) break;
      dnode = dnode->mNext;
    }
    bool destKnown = ((dnode ? dnode : endNode) != endNode);

    if (!sourceKnown) {
      uint64_t v = ((uint64_t)(uint32_t)srcHi << 32) | (uint32_t)srcLo;
      if ((v - 0x20) < 0x20) {
        int* entry = (int*)((char*)d->mScaleTable + (srcLo & 0xffff) * 8 - 0x100);
        int scale = entry[0];
        int tex = entry[1];
        int created = 0;
        if (scale != 0) {
          if (AddCameraTexture((int)(uVar2 / scale), (int)(uVar3 / scale), &created)) {
            uint16_t key = (uint16_t)srcLo;
            *mHash.FindOrInsert(&key) = created;
          }
        } else {
          if (AddCameraTexture((unsigned)tex, (unsigned)tex, &created)) {
            uint16_t key = (uint16_t)srcLo;
            *mHash.FindOrInsert(&key) = created;
          }
        }
      } else {
        if (srcHi > 0 || srcLo >= 0x40) {
          Resolve(srcLo, srcHi);
        }
      }
    }

    if (!destKnown && (uint8_t)(dest - 0x20) < 0x20) {
      int* entry = (int*)((char*)d->mScaleTable + (uint32_t)dest * 8 - 0x100);
      int scale = entry[0];
      int tex = entry[1];
      int created = 0;
      if (scale != 0) {
        if (AddCameraTexture((int)(uVar2 / scale), (int)(uVar3 / scale), &created)) {
          uint16_t key = dest;
          *mHash.FindOrInsert(&key) = created;
        }
      } else {
        if (AddCameraTexture((unsigned)tex, (unsigned)tex, &created)) {
          uint16_t key = dest;
          *mHash.FindOrInsert(&key) = created;
        }
      }
    }

    // ---- per-filter-type fixups.
    int32_t* texTable = d->mTextureTable;
    switch (e->mFlags) {
      case 0: {
        int idx = tb->mIdx6;
        if (idx != 0xff) {
          int a = texTable[idx * 2];
          int b = texTable[idx * 2 + 1];
          if (!(b == 0 && a <= 5)) Resolve((uint32_t)a, b);
        }
        break;
      }
      case 2: {
        int idx = tb->mIdx0;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx6;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 3: {
        int idx = tb->mIdx2;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 10:
      case 13: {
        int idx = tb->mIdx0;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 16: {
        int idx = tb->mIdx1;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx2;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx3;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        idx = tb->mIdx4;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      case 17: {
        int idx = tb->mIdx0;
        if (idx != 0xff) mStrength = d->mStrengthTable[idx];
        if (tb->mIdx1 != 0) {
          mField04 = 0;
        } else if (tb->mIdx2 != 0) {
          mField04 = 1;
        }
        idx = tb->mIdx3;
        if (idx != 0xff) Resolve((uint32_t)texTable[idx * 2], texTable[idx * 2 + 1]);
        break;
      }
      default: break;
    }

    off += 0x28;
  } while (--counter != 0);

  return true;
}

// @ 0x006f9020
void cFilterChain_s006f_8380::RemoveAt(int idx)
{
  int n = (int)((mDescEnd - mDescBegin) / 0x78) + 0xc;
  if (idx == n) {
    int slot = (int)*(int16_t*)(mArrEnd - 1);
    cScreenFilter* f = (cScreenFilter*)mTexBegin[slot];
    mIndex[slot] = -1;
    f->RemoveCameraTextures();
    f->mHash.ReleaseBuckets(f->mHash.mArray, f->mHash.mCount);
    f->mHash.mField18 = 0;
    if (mDescBegin != mDescEnd) {
      mDescEnd -= 0x78;
      ((FilterDesc78*)mDescEnd)->Destroy();
      mBitsEnd -= 1;
      mArrEnd -= 1;
    }
    m184 = 0;
    void* p = operator new(0xc, "Graphics", 0, 0, 0, 0);
    void* obj = 0;
    if (p != 0) {
      ((int*)p)[2] = 0;
      ((int*)p)[1] = 0x13ef094;
      ((int*)p)[0] = 0x140b778;
      ((int*)p)[1] = 0x14188c0;
      obj = p;
    }
    GetRenderSystem()->AttachRenderTarget(obj, 0, 0);
    cScreenFilter* f2 = (cScreenFilter*)mTexBegin[slot];
    if (0.0f < f2->mStrength) f2->mStrength = 0.0f;
    while (mBitsBegin != mBitsEnd && mBitsEnd[-1] == 0) {
      mDescEnd -= 0x78;
      ((FilterDesc78*)mDescEnd)->Destroy();
      mBitsEnd -= 1;
      mArrEnd -= 1;
    }
    if (mDescBegin != mDescEnd) {
      int i = (int)((mDescEnd - mDescBegin) / 0x78) - 1;
      for (; i >= 0; --i) {
        if (mArrBegin[i] == (uint16_t)slot) {
          ((cScreenFilter*)mTexBegin[slot])
              ->CreateScreenFilterInternal((FilterDesc78*)(mDescBegin + i * 0x78));
          mIndex[slot] = i;
        }
      }
    }
  } else {
    uint32_t s = (uint32_t)(idx - 0xd);
    if (s < (uint32_t)((mDescEnd - mDescBegin) / 0x78) && s < (uint32_t)(mBitsEnd - mBitsBegin)) {
      mBitsBegin[s] = 0;
    }
  }
}

// @ 0x006f9250
bool CFilterChain::AddFilterChain(int a, int b)
{
  m1f8 = 0;
  int count = (int)((char*)m124 - (char*)m120) / 0x78;
  int n = count - 1;
  bool flagA = false;       // [esp+0x13]
  bool flagB = false;       // bl
  int idxA = -1;            // ebp
  int idxB = -1;            // edi
  for (int i = n; i >= 0; --i) {
    if (m210[i] == 1 && m1fc[i] == 1) {
      flagA = true;
      idxA = i;
    } else if (m210[i] == 0 && m1fc[i] == 1) {
      flagB = true;
      idxB = i;
    }
  }
  char* base = (char*)m120;
  if (flagA && flagB) {
    FilterDesc* eA = (FilterDesc*)(base + idxB * 0x78);
    FilterDesc* eB = (FilterDesc*)(base + idxA * 0x78);
    int cB = (int)((char*)eB->v00.end - (char*)eB->v00.begin) / 0x28;
    ((char*)eB->v00.begin)[cB * 0x28 - 0x27] = 0x41;
    ApplyFilters(eA, (uint16_t)((int)((char*)eA->v00.end - (char*)eA->v00.begin) / 0x28), &b, 0);
    ApplyFilters(eB, (uint16_t)cB, &b, 1);
  } else if (flagA) {
    FilterDesc* eB = (FilterDesc*)(base + idxA * 0x78);
    int cB = (int)((char*)eB->v00.end - (char*)eB->v00.begin) / 0x28;
    ApplyFilters(eB, (uint16_t)cB, &a, 1);
  } else if (flagB) {
    FilterDesc* eA = (FilterDesc*)(base + idxB * 0x78);
    int cA = (int)((char*)eA->v00.end - (char*)eA->v00.begin) / 0x28;
    ((char*)eA->v00.begin)[cA * 0x28 - 0x27] = 1;
    ApplyFilters(eA, (uint16_t)cA, &b, 0);
  }
  return false;
}

// @ 0x006f9cf0
void CFilterChain::Shutdown()
{
  void* rs = (void*)ReportCleanup();
  void* ctx = (this != 0) ? (void*)((char*)this + 4) : 0;
  ((void(__thiscall*)(void*, void*, int, int))(*(void***)rs)[0x2c / 4])(rs, ctx, 0x44edd9c, -0x270f);
  for (int i = 0; i < 2; ++i) {
    void* obj = *(void**)((char*)m138 + i * 4);
    ((void(__thiscall*)(void*))0x006f8190)(obj);
    if (obj != 0) {
      ((void(__thiscall*)(void*))0x006f51b0)(obj);
      EASTL_deallocate_(obj);
    }
  }
  {  // clear the +0x120 vector
    void* end = m124;
    ((void(__cdecl*)(void*, void*))0x006f9a50)(m120, end);
  }
  void* p;
  p = (void*)m174; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
  p = (void*)m178; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
  p = (void*)m17c; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
  p = (void*)m180; if (p) { ((void(__thiscall*)(void*))0x007c3ba0)(p); ((void(__thiscall*)(void*))0x007c4000)(p); EASTL_deallocate_(p); }
}

// @ 0x006f9e20
void CFilterChain::Notify3(int a, int* out, unsigned short c)
{
  ((void(__thiscall*)(void*, int))0x006f9c70)((char*)this + 0x120, a);   // append filter record
  // append a 'true' to the +0x1fc vector<bool>
  if (m200 < m204) {
    *m200++ = 1;
  } else {
    uint8_t tmp = 1;
    ((void(__cdecl*)(void*, void*))0x00426730)(m200, &tmp);
  }
  // append c to the +0x210 vector<u16>
  if (m214 < m218) {
    *m214++ = c;
  } else {
    ((void(__cdecl*)(void*, void*))0x006f5bc0)(m214, &c);
  }
  int cnt = (int)((char*)m124 - (char*)m120) / 0x78;
  *out = cnt + 0xc;
  int idx = (int)(short)c;
  *(int*)((char*)this + 0x1b4 + idx * 4) = cnt - 1;
  void* filter = *(void**)((char*)m138 + idx * 4);
  ((void(__thiscall*)(void*, int))0x006f87f0)(filter, a);
}
