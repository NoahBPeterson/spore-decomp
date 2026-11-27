// src/game/SPEngine/_at_006f0000.cpp -- migrated from slice(s) s006ff170, s006fd520, s006fc540, s006f9250, s006f8380, s006f7430, s006f6430, s006f54a0, s006f43e0, s006f3410 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_006f0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern char  g_15342b0;   // 0x15342b0
extern char  g_1619530;   // 0x1619530
#include <math.h>
#include <intrin.h>
#include "rw/graphics/EmbeddedState.h"
#include "SP/cFilterChain.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// ---- items of slice s006f3410 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl EASTL_allocator_deallocate(void* p) throw();                                  // 0xf47380
void* __cdecl EASTL_allocator_allocate(unsigned size, const char* name, int a, int b,
                                       const char* file, int line);                 // 0xf473a0
void  __cdecl memset_thunk(void* dst, int value, unsigned size);                    // 0x11e073e
void* __cdecl FUN_0067dd60();                                                       // 0x67dd60
extern char  g_15342b0;   // 0x15342b0
extern char  g_1619530;   // 0x1619530
static inline void** Vt(void* p) { return *(void***)p; }
struct cViewer {
    void Copy(void* src, int a, int b);   // 0x7c50b0
    void f3cb0(void* p);                  // 0x7c3cb0
    void f3ce0(int a, int b);             // 0x7c3ce0
    void f3c20(void* p);                  // 0x7c3c20
    void f3c50(int a);                    // 0x7c3c50
    void f4be0(void* p, int a);           // 0x7c4be0
};
class cRenderInstanceSet {
public:
    virtual bool OnMessage(int id, int arg);          // slot 0  0x6f3ec0
    virtual void v1();                                // slot 1
    virtual void v2();                                // slot 2
    virtual void v3();                                // slot 3
    virtual void v4();                                // slot 4
    virtual void v5();                                // slot 5
    virtual void v6();                                // slot 6
    virtual void v7();                                // slot 7
    virtual void v8(int count);                       // slot 8
    virtual void v9();                                // slot 9
    virtual void SetColor(int a, const float* rgb, float alpha, int b); // slot 10 0x6f4100
    virtual void v11();                               // slot 11

    char  pad04[0x110 - 0x4];
    float mColorR;       // +0x110
    float mColorG;       // +0x114
    float mColorB;       // +0x118
    float mColorA;       // +0x11c
    int   mRangeBegin;   // +0x120
    int   mRangeEnd;     // +0x124
    char  pad128[0x130 - 0x128];
    unsigned char mFlag130;                             // +0x130
    char  pad131[0x138 - 0x131];
    void* mModelArray;   // +0x138  (array of 2 model pointers)
    char  pad13c[0x154 - 0x13c];
    float mF154;         // +0x154
    char  pad158[0x168 - 0x158];
    void* mRenderer168;  // +0x168
    char  pad16c[0x174 - 0x16c];
    cViewer* mViewer174; // +0x174
    cViewer* mViewer178; // +0x178
    cViewer* mViewer17c; // +0x17c
    cViewer* mViewer180; // +0x180
    char  pad184[0x1a8 - 0x184];
    float mF1a8;         // +0x1a8
    float mF1ac;         // +0x1ac
    float mF1b0;         // +0x1b0
    int   mArr1b4[2];    // +0x1b4
    unsigned char mFlags1bc[12]; // +0x1bc
    float mValues1c8[12];        // +0x1c8

    bool CopyTo174(void* src);
    cViewer* Setup178(void* src);
    cViewer* Setup180(void* src);
    void Tick154(int dt);
    bool IsRangeEmpty() const;
    void GetRange(int* out);
    cViewer* RenderRange(void* src);
    void SetElement(int idx, float value);
    void ClearElements();
    void UpdateEffects(int dt);
};
struct cGraphicsHash {
    void* m0;            // +0x0
    void** mBuckets;     // +0x4
    unsigned int mCount; // +0x8
    void Resize(unsigned int newSize);
};
// ---- items of slice s006f3410 end

// ---- items of slice s006f43e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_App();                              // 0x0067dd10 SP::App
extern "C" void* SP_LightingManager();                  // 0x0067dd90 SP::LightingManager
extern "C" void  cSPMatrix3_Assign(void* self, const void* src);   // 0x0041cb40
extern "C" unsigned SP_ColorRGBAToU32(float* rgba);     // 0x004580c0
extern float g_16194f8;   // 0x16194f8  camera position x
extern float g_16194fc;   // 0x16194fc  camera position y
extern float g_1619500;   // 0x1619500  camera position z
extern float g_1619638[9]; // 0x1619638  Matrix33 data (row-major, 9 floats)
extern float g_1485720;   // 0x1485720  _HK_REAL_ONE = 1.0f
extern float g_13eecd4;   // 0x13eecd4  0.003921569f
extern float g_1470f1c;   // 0x1470f1c  2.0f
extern float g_16077c4;   // 0x16077c4  (small int bit pattern, treated as float)
extern float g_16077c8;   // 0x16077c8  (small int bit pattern, treated as float)
extern "C" unsigned g_16f9230;    // 0x16f9230
extern "C" unsigned g_16f922c;    // 0x16f922c
extern "C" unsigned g_16f9218;    // 0x16f9218
extern "C" unsigned g_16f9200;    // 0x16f9200
extern "C" unsigned g_16f923c;    // 0x16f923c
extern "C" unsigned g_16fa38c;    // 0x16fa38c  render-state dirty flags
void* __cdecl FUN_0067dd40();          // graphics manager (raster helpers)
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void  __cdecl FUN_007c40f0(void* a, void* b);      // 0x007c40f0
char  __cdecl FUN_006ddcc0(int a, int b, void* c, void* d);
void  __cdecl FUN_006ddd10(int a, void* b);
void  __cdecl FUN_00921440(void* out, unsigned a, unsigned b, int c);
void* __cdecl FUN_011f1120();
void* __cdecl operator_new_graphics(unsigned n, const char* name, int a, int b,
                                    const char* file, int line);
static inline void* CallSlot0(void* p, int slot) {
    return ((void* (__thiscall*)(void*))Vt(p)[slot])(p);
}
struct cImageHost {
    void GetImageResource(void* r);      // 0x576650
};
struct VecBase {
    void*  mpBegin;        // +0x00
    void*  mpEnd;          // +0x04
    void*  mpCapacityEnd;  // +0x08
    void*  mnSize;         // +0x0c
    void DestroyRange(void** first, void** last);   // 0x0070f520
};
struct HashtableHead {
    char     mHead[4];        // +0x00
    void**   mpBucketArray;   // +0x04
    unsigned mnBucketCount;   // +0x08
    unsigned mnElementCount;  // +0x0c
};
struct WideHashtable : HashtableHead {
    void DoFreeNodes(void** array, unsigned count);   // 0x00693230
};
struct ResourceHashtable : HashtableHead {
    void DoFreeNodes(void** array, unsigned count);   // 0x007611f0
};
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
void  __cdecl operator_delete_(void* p);
void  __cdecl FUN_00b84c80(int a, int b, int c);
void  __cdecl FUN_00951740(void** a, int b, int c, int d, int e);
void  __cdecl FUN_00ac4440(int a, int b, int c);
void  __cdecl FUN_00714bc0(void** a, int b, int c, int d, int e);
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
struct cState {
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
static inline void BlobCall(cState* self, int a, float b, float c, float d, float e) {
    ((cBlob*)((char*)self + 0x10))->F77ca20(a, b, c, d, e);
}
struct Elem0C { unsigned d[3]; };   // Text::AnalysisInfo, 0xc bytes
struct Vec0C {
    Elem0C* mpBegin;
    Elem0C* mpEnd;
    Elem0C* mpCapacity;
    Elem0C* AllocCopy(unsigned n, Elem0C* first, Elem0C* last);   // 0x006f4f30
    Vec0C& Assign(const Vec0C* x);
};
struct Elem8 { unsigned d[2]; };   // Text::GlyphInfo, 8 bytes
struct Vec8 {
    Elem8* mpBegin;
    Elem8* mpEnd;
    Elem8* mpCapacity;
    Elem8* AllocCopy(unsigned n, Elem8* first, Elem8* last);   // 0x006f4f90
    Vec8& Assign(const Vec8* x);
};
// ---- items of slice s006f54a0 end

// ---- items of slice s006f6430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
struct cHashtable {
    void FreeNodes(void* b, void* e);
};
void  __cdecl operator_delete_(void* p) throw();
struct cVecU16 {
    unsigned short* begin;   // +0
    unsigned short* end;     // +4
    unsigned short* cap;     // +8
    void Insert(unsigned short* pos, const unsigned short& val);   // 0x6f5bc0
    void push_back(const unsigned short& v);
};
struct cHNode { unsigned short first; int second; cHNode* mpNext; };
struct cHIter {
    cHNode* mpNode; cHNode** mpBucket;
    cHIter() {}
    cHIter(const cHIter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
};
struct cHPair { unsigned short first; int second; };
struct cHInsertResult { cHIter first; bool second; };
struct cTrue { cTrue() {} };
struct cHashMap16 {
    int pad0;
    cHNode** mpBucketArray;     // +4
    unsigned mnBucketCount;     // +8
    cHIter find(const unsigned short& k);                                           // 0x892970
    cHInsertResult DoInsertValue(const cHPair& v, cTrue);                    // 0x6f4ff0
    int& Subscript(const unsigned short& k);       // operator[] (named so the checker can find it)
};
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
struct cState_s006f_6430 {
    int pad0[4];
    cShConstBlock sh;            // +0x10 (embedded; the block's address is this+0x10)
    char pad1[0x170 - 0x14];
    float f170;                  // +0x170
    char pad2[0x188 - 0x174];
    float f188, f18c, f190;      // +0x188
    void ColorBE(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void ColorDC(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);
    void W6f6c30(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);  // 0x006f6c30 (cState::W6f6c30)
    void W6f6f40(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);  // 0x006f6f40 (cState::W6f6f40)
    void W6f71f0(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7);  // 0x006f71f0 (cState::W6f71f0)
    float GetDist();             // 0x6f4580
    void F54a0(unsigned long long flags, int p3, int p4, int p5, void* ptr, int count, int p6, int p7);  // 0x6f54a0
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
// ---- items of slice s006f6430 end

// ---- items of slice s006f7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVecBool {
    void Assign(void* src);   // 0x6f6770
};
struct HtIter_s006f_7430 { void* node; void** bucket; };
struct KeyHashtable {
    char     pad[4];
    void**   mpBuckets;     // +0x04
    unsigned mBucketCount;  // +0x08
    HtIter_s006f_7430* find(HtIter_s006f_7430* out, const unsigned short* key);   // 0x892970
};
struct ResRef {
    void* mp;
    ~ResRef();   // 0x576620
};
struct ResRefVec {
    ResRef* mpBegin;
    ResRef* mpEnd;
    void push_back(const ResRef& r);   // 0x420660
};
struct ResKey { unsigned lo, hi; };
struct KeyIndexMap {
    int* operator[](const ResKey& key);   // 0x6f6630
};
struct cFilterChain2 {
    char         pad0[0xc];
    KeyHashtable mTable;     // +0x0c
    char         pad1[0x14];
    KeyIndexMap  mIndex;     // +0x2c
    char         pad2[0x4b];
    ResRefVec    mRefs;      // +0x78

    bool __thiscall TryA(ResKey key, ResRef* out);   // 0x6f4500
    bool __thiscall TryB(ResKey key, ResRef* out);   // 0x6f44c0
    bool Resolve(ResKey key);                        // 0x6f8260
};
// ---- items of slice s006f7430 end

// ---- items of slice s006f8380 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13eb394[];
extern "C" char g_13eb938[];
extern "C" char g_13ec458[];
extern "C" char g_140b798[];
extern "C" char g_140b7a8[];
extern "C" char g_140b7b8[];
extern float g1619524, g1619528, g161952c;
extern float g13f1160, g1477fbc, g1485720, g1485544;
extern float g1534250, g1534254, g1534258;
extern float g16194f8, g16194fc, g1619500;
#pragma intrinsic(_ReadWriteBarrier)
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
class cViewer_s006f_8380;
class cViewer_s006f_8380 {
public:
  bool Copy(cViewer_s006f_8380* src, bool a, bool b);  // va 007c50b0 0x007c50b0
  void ApplyFrustum(float a, float b);      // va 007c4ad0
};
class cFilterChain {
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

  cFilterChain();
  ~cFilterChain();

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
static inline void FreeGuarded(void* p) {
  if (p != 0 && *((int*)p - 1) != 0) EASTL_allocator_deallocate(p);
}
// ---- items of slice s006f8380 end

// ---- items of slice s006f9250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_MessageServer();
extern "C" void  __cdecl EASTL_deallocate_(void* p);            // 0x00f47380 (allocator free)
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
struct EvChain {
  char pad0[0x120];
  void* m120;         // +0x120
  void* m124;         // +0x124
  char pad128[0xc];
  uint8_t m134;       // +0x134
  char pad135[0xEF];
  int m224;           // +0x224
  void SubSF(int, int);                       // 0x006f9250
  void Notify(int a0, int a1, int a2, int a3);  // 0x006f94b0
};
void* EASTL_allocate_(unsigned n, const char* name, int flags, int dbg, const char* file, int line); // 0x00f473a0
struct FilterElem28_s006f_9250 {                                  // 0x28 bytes
  FilterElem28_s006f_9250& operator=(const FilterElem28_s006f_9250&);
};
struct Vec28 {
  FilterElem28_s006f_9250* begin;   // +0
  FilterElem28_s006f_9250* end;     // +4
  FilterElem28_s006f_9250* cap;     // +8
  Vec28& operator=(const Vec28&);                      // 0x006f9730
};
extern "C" void* __cdecl CopyFilterRange_s006f_9250(void** dst, const void* first, const void* last, void* result); // 0x6f8710
FilterElem28_s006f_9250* __cdecl Vec28Realloc(Vec28* self, int count, const FilterElem28_s006f_9250* first,
                                   const FilterElem28_s006f_9250* last);   // 0x006f9430
void __cdecl DestroyFilterRange(FilterElem28_s006f_9250* first, FilterElem28_s006f_9250* last);         // 0x006f5170
FilterElem28_s006f_9250* __cdecl AssignFilterRange(FilterElem28_s006f_9250* dst, const FilterElem28_s006f_9250* first,
                                        const FilterElem28_s006f_9250* last);                // 0x006f8140
struct Vec8_s006f_9250 {                                          // generic 8-byte-element vector
  void* begin; void* end; void* cap;
  void assign(const Vec8_s006f_9250& src);                        // reserve + memmove
};
struct Vec12 {                                          // 12-byte-element vector
  void* begin; void* end; void* cap;
};
struct Vec4 {                                           // 4-byte-element vector
  void* begin; void* end; void* cap;
};
struct FilterDesc {                                     // the 0x78-byte descriptor
  Vec28  v00;   // +0x00  (vector<FilterElem28>)
  Vec8_s006f_9250   v14;   // +0x14  (8-byte elements)
  Vec4   v28;   // +0x28  (4-byte elements)
  Vec12  v3c;   // +0x3c  (12-byte elements)
  Vec8_s006f_9250   v50;   // +0x50  (8-byte elements)
  Vec8_s006f_9250   v64;   // +0x64  (8-byte elements)

  void AssignDescA(const FilterDesc* src);             // 0x006f9520
  void AssignDescB(const FilterDesc* src);             // 0x006f95e0
};
void* __cdecl VecReserve8(void* self, int n);          // 0x00799d00
void* __cdecl VecReserve4(void* self, int n);          // 0x004aa350
void* __cdecl VecReserve12(void* self, const void* src); // 0x006f50f0
void* __cdecl CopyElems8(void** outEnd, const void* first, const void* last, void* dst); // 0x0076ffd0
void* __cdecl CopyElems8f(void** outEnd, const void* first, const void* last, void* dst); // 0x00714bc0
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
struct Vec78Ins { Elem78* begin; Elem78* end; Elem78* cap; };
Elem78* __cdecl CopyRange78(Elem78* dst, const Elem78* first, const Elem78* last);   // 0x006f9880
Elem78* __cdecl AssignRange78(Elem78* dst, const Elem78* first, const Elem78* last); // 0x006f8100
Elem78* __cdecl CopyBackward78(Elem78* dstEnd, const Elem78* first, const Elem78* last); // 0x006f99e0
void  __cdecl Destroy78(Elem78* first, Elem78* last);                                // 0x006f5170
// ---- items of slice s006f9250 end

// ---- items of slice s006fc540 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00f47380(void* p);                                  // 0x00f47380 operator delete
extern "C" void* FUN_00f473a0(unsigned int n, const char* name, int flags, unsigned debugFlags,
                              const char* file, int line);               // 0x00f473a0 eastl allocator
extern "C" void  FUN_011f4200();                                         // 0x011f4200 Shader::Release
extern "C" int   FUN_00777760();                                         // 0x00777760 cShaderBase::Write
extern "C" void* FUN_00847ff0(void*, void*, void*);                      // 0x00847ff0 range move
extern "C" void  FUN_006fd220(void*, unsigned, const void*);             // 0x006fd220 construct range
extern "C" void  FUN_006fd170(void*, void*, void*, void*, void*);        // 0x006fd170
extern "C" void  FUN_006fd250(void*, void*, void*);                      // 0x006fd250
extern "C" void  FUN_006fd140(void*, void*, void*);                      // 0x006fd140
extern "C" int __cdecl FUN_0093a9a0(void* io, const void* p, int n);     // 0x0093a9a0 write block
extern "C" int __cdecl FUN_0093aa70(void* io, const void* p, int n, int f); // 0x0093aa70 write uint32
struct IO;
extern "C" IO* IOPut(IO* io, const void* p, int n);          // operator<<
extern "C" IO* IOGetB(IO* io, const void* p, int n);         // byte read
extern "C" IO* IOWriteU16(IO* io, const uint16_t* p, int n, int f);
extern "C" IO* IOWriteU32(IO* io, const uint32_t* p, int n, int f);
extern "C" IO* IOGet16(IO* io, const void* p, int n, int f);
extern "C" IO* IOGet32(IO* io, const void* p, int n, int f);
struct IO {
  IO* Put(uint8_t v)  { return IOPut(this, &v, 1); }
  IO* Put(uint16_t v) { return IOWriteU16(this, &v, 1, 0); }
  IO* Put(uint32_t v) { return IOWriteU32(this, &v, 1, 0); }
  IO* Get(uint8_t& v)  { return IOGetB(this, &v, 1); }
  IO* Get(uint16_t& v) { return IOGet16(this, &v, 1, 0); }
  IO* Get(uint32_t& v) { return IOGet32(this, &v, 1, 0); }
};
struct FragRec {
  uint8_t  pad0;
  uint8_t  m1;    // +1
  uint16_t m2;    // +2
  uint16_t m4;    // +4
  uint16_t m6;    // +6
  uint32_t m8;    // +8
  uint32_t mc;    // +0xc
  uint32_t m10;   // +0x10
  uint32_t m14;   // +0x14
  uint8_t  m18;   // +0x18
  bool Write(IO* io);                     // 0x006fceb0
  bool Read(IO* io, uint32_t version);    // 0x006fcdc0
};
static void* AllocGraphics(unsigned int n) {
  return FUN_00f473a0(n, "Graphics", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
}
struct ShaderSlot {          // 0x14 bytes
  FragRec* mpBegin;          // +0x00
  FragRec* mpEnd;            // +0x04
  FragRec* mpCap;            // +0x08
  uint32_t mField0C;         // +0x0c
  uint32_t mField10;         // +0x10
  ShaderSlot();              // 0x006e5790 (zeroes +0x0c and +0x10) - the iterator's ctor argument
  ~ShaderSlot();             // 0x007a41a0 (empty) - the iterator's dtor argument
};
struct Vec25 {
  FragRec* mpBegin;                                        // +0x00
  FragRec* mpEnd;                                          // +0x04
  FragRec* mpCap;                                          // +0x08
  void set_capacity(unsigned n);                           // 0x006fc540
  void insert_moved(void* pos, unsigned n, const void* src); // 0x006fd330
};
struct cFragmentShader {
  cFragmentShader();           // 0x006fd280: zeroes +0x38..+0x44, then constructs both slot arrays
  ~cFragmentShader();          // 0x006fd1b0: destroys both slot arrays, +0x188 first
  uint8_t    mPad00[0x38];     // +0x00..+0x37
  uint32_t   mField38;         // +0x38
  uint32_t   mRefCount;        // +0x3c
  uint32_t   mField40;         // +0x40
  uint32_t   mField44;         // +0x44
  ShaderSlot mSlotsA[0x10];    // +0x48
  ShaderSlot mSlotsB[0x10];    // +0x188
  bool Write(IO* io);          // 0x006fcf90
  int  Release();              // 0x006fd300
};
// ---- items of slice s006fc540 end

// ---- items of slice s006fd520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  g_device;            // 0x16f89d0  rw::graphics::ActiveState::m_d3d9Device
extern unsigned int g_softStateUpdated;  // 0x16f9110
extern unsigned int g_samplerDelta[];    // 0x16f8cb0
extern int    g_samplerShadow[];         // 0x16f8d08
struct CellVector {
    void erase(void* first, void* last);  // 0x00d73090
    void insert(void* pos, unsigned n, void* value);  // 0x006fd330
};
void  __cdecl FUN_0093a6c0(void* stream, const void* data, int n);
void  __cdecl FUN_0093a780(void* stream, void* data, int n, int flag);
bool  __cdecl FUN_00777840(void* stream, unsigned flag, void* arg);
void  __cdecl FUN_006fd990(void* self);
struct Vec1c {
    char* begin;   // +0x00
    char* end;     // +0x04
    int Size() const { return (int)((end - begin) / 0x1c); }
    void Resize(unsigned n);
};
struct Elem1c {
    unsigned char a;      // +0x00
    unsigned char b;      // +0x01
    unsigned short c;     // +0x02
    unsigned short d;     // +0x04
    unsigned short e;     // +0x06
    unsigned int  f;      // +0x08
    unsigned int  g;      // +0x0c
    unsigned int  h;      // +0x10
    unsigned int  i;      // +0x14
    unsigned char stream; // +0x18
    Elem1c() : a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0), i(0) {}
    // cVertDecl::WriteBinary (0x006fcdc0): emits the leading name byte(s) of
    // this declaration element plus its stream field into `stream`.
    void WriteBinary(void* stream, void* arg);
};
struct StreamCtx {
    char pad00[0x48];
    // two arrays of 0x14-byte vertex-declaration vectors (ElementVec), at
    // +0x48 and +0x188; each holds 0x1c-byte cVertDecl elements.
    bool ReadDecls(void* stream, unsigned flag, void* arg);
};
// ---- items of slice s006fd520 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int __cdecl FUN_006fd7d0();  // 0x006fd7d0 (stays in the slice: not this object's)

// ---- items of slice s006ff170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_1667bac[];
extern "C" char g_1667bad[];
extern char*      g_vs_begin;      // 0x1628c20
extern char*      g_vs_end;        // 0x1628c24
void __cdecl FUN_00777720(void* p, unsigned n, void* out);
unsigned __cdecl FUN_00777740(void* p);
int __cdecl FUN_0093a9d0(void* io, const void* p, int n, int f); // 0x0093a9d0 write uint16
int __cdecl FUN_0093a6c0(void* io, void* p, int n);              // 0x0093a6c0 read block
int __cdecl FUN_0093a780_s006f_f170(void* io, void* p, int n, int f);       // 0x0093a780 read uint32
int __cdecl FUN_0093a700(void* io, void* p, int n, int f);       // 0x0093a700 read uint16
void __cdecl FUN_006fc480(void* vec, unsigned n);   // 0x006fc480 vector<cFragmentDecl>::resize
void __cdecl FUN_004c10e0();                        // 0x004c10e0 vector<u8>::DoInsertValues
struct FragElem {                   // 0x1c
    char*    mpBegin;               // +0x00
    char*    mpEnd;                 // +0x04
    char*    mpCap;                 // +0x08
    unsigned mField0C;              // +0x0c
    unsigned short mField10;        // +0x10
    unsigned short mField12;        // +0x12
    unsigned short mField14;        // +0x14
    unsigned short mField16;        // +0x16
    unsigned mField18;              // +0x18
};
struct VsRecord {                   // 0x130
    unsigned char mBlob[0x20];      // +0x00 opaque 0x20-byte block
    void*         mpShader;         // +0x20 vertex-shader object (0x777720 / 0x777740)
    unsigned      mField24;         // +0x24
    int           mCount;           // +0x28
    FragElem*     mpElems[0x20];    // +0x2c
    unsigned      mFieldAC[0x20];   // +0xac
    int           mField12C;        // +0x12c
};
struct VecU8 {
    unsigned char* mpBegin;         // +0x00
    unsigned char* mpEnd;           // +0x04
    unsigned char* mpCap;           // +0x08
    unsigned char* erase(unsigned char* first, unsigned char* last) {
        memcpy(first, last, (unsigned)(mpEnd - last));
        mpEnd -= last - first;
        return first;
    }
    void resize(unsigned n) {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        if (n <= size) {
            erase(mpBegin + n, mpEnd);
        } else {
            unsigned char v = 0;
            ((void(__thiscall*)(void*, unsigned char*, unsigned, const void*))FUN_004c10e0)
                (this, mpEnd, (unsigned)(mpBegin - mpEnd) + n, &v);
        }
    }
    ~VecU8() {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            FUN_00f47380(mpBegin);
    }
};
struct IO_s006f_f170 {
    int Put(unsigned short v) { return FUN_0093a9d0(this, &v, 1, 0); }
    int Put(unsigned v)       { return FUN_0093aa70(this, &v, 1, 0); }
    int Put(const unsigned* p, int n) { return FUN_0093aa70(this, p, n, 0); }
    int Write(const void* p, int n)   { return FUN_0093a9a0(this, p, n); }
};
struct EStr {                       // 0x10 eastl::basic_string<char>
    char* mpBegin;                  // +0x00
    char* mpEnd;                    // +0x04
    char* mpCap;                    // +0x08
    int   mField0C;                 // +0x0c
    void append(unsigned n, char c);   // 0x0047bf30 eastl::basic_string::append
    // eastl::basic_string::resize(n, 0), inlined: shrink in place, else grow by appending.
    void resize(unsigned n) {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        if (n < size) {
            char* ne = mpBegin + n;
            if (ne != mpEnd) {
                memmove(ne, mpEnd, 1);
                mpEnd = ne;
            }
        } else if (size < n) {
            append(n - size, 0);
        }
    }
};
struct CFragDeclBase {              // 0x1c element of the record's region vector
    EStr           mName;           // +0x00
    unsigned short mField10;        // +0x10
    unsigned short mField12;        // +0x12
    unsigned short mField14;        // +0x14
    unsigned short mField16;        // +0x16
    unsigned       mField18;        // +0x18
};
struct RegionVec {                  // 0x14
    CFragDeclBase* mpBegin;         // +0x00
    CFragDeclBase* mpEnd;           // +0x04
    CFragDeclBase* mpCap;           // +0x08
    int            mField0C;        // +0x0c
    int            mField10;        // +0x10
};
struct VsTableRec {                 // 0x44 SP::cVertexFragmentInfo
    unsigned    mField00;           // +0x00
    EStr        mName;              // +0x04
    EStr        mUniform;           // +0x14
    RegionVec   mRegions;           // +0x24
    unsigned    mField38;           // +0x38
    unsigned    mField3C;           // +0x3c
    unsigned char mField40;         // +0x40
    unsigned char mField41;         // +0x41
    unsigned char mField42;         // +0x42
    unsigned char mPad43;           // +0x43
};
extern VsTableRec g_fragTable[0x100];   // 0x1624710
static void* AllocGraphics_s006f_f170(unsigned n) {
    return FUN_00f473a0(n, "Graphics", 0, 0, "allocator.h", 0xd1);
}
struct TempString {
    char* mpBegin;                  // +0x00
    char* mpEnd;                    // +0x04
    void assignFill(unsigned n) {
        if (n + 1 <= 1) {
            mpBegin = (char*)g_1667bac;
            mpEnd   = (char*)g_1667bad;
        } else {
            mpBegin = (char*)AllocGraphics_s006f_f170(n + 1);
            mpEnd   = mpBegin + n + 1;
        }
        memset(mpBegin, 0x20, n);
        mpBegin[n] = 0;
    }
    ~TempString() {
        if (mpEnd - mpBegin > 1 && mpBegin != 0)
            FUN_00f47380(mpBegin);
    }
};
static void ReadIntoEStr(void* io, EStr& s, unsigned n) {
    s.resize(n);
    FUN_0093a6c0(io, s.mpBegin, (int)n);
}
struct VertexCtx {
    void SubClip(float d);
    int  TestClip1(const float* a, const float* b);
    int  TestClip2(const float* p, float t);
};
// ---- items of slice s006ff170 end

// @ 0x006f3ec0
bool cRenderInstanceSet::OnMessage(int id, int arg)
{
    (void)arg;
    if (id == 0x044EDD9C) {
        mFlag130 = 1;
        return true;
    }
    return false;
}

// @ 0x006f3ee0
bool cRenderInstanceSet::CopyTo174(void* src)
{
    mViewer17c->Copy(src, 0, 0);
    return true;
}

// @ 0x006f3f20
cViewer* cRenderInstanceSet::Setup178(void* src)
{
    mViewer178->Copy(src, 0, 0);
    typedef void* (__thiscall* RendererFn)(void*);
    RendererFn f = *(RendererFn*)(Vt(mRenderer168) + 29);
    void* r = f(mRenderer168);
    if (((*(unsigned char*)r) & 0) == 0) {
        if (((*(unsigned char*)((char*)r + 4)) & 1) == 0) {
            void* o = FUN_0067dd60();
            (*(void (__thiscall**)(void*, void*))(Vt(o) + 13))(o, r);
        }
    }
    mViewer178->f3cb0(*(void**)r);
    mViewer178->f3ce0(0xb, 0);
    mViewer178->f3c20(&g_15342b0);
    mViewer178->f3c50(7);
    return mViewer178;
}

// @ 0x006f3fb0
cViewer* cRenderInstanceSet::Setup180(void* src)
{
    mViewer180->Copy(src, 0, 0);
    return mViewer180;
}

// @ 0x006f4020
void cRenderInstanceSet::Tick154(int dt)
{
    float old = mF154;
    float target = mF1a8;
    if (old != target) {
        mF154 = (target - old) * mF1ac + old;
        mF1ac = fabsf((float)(unsigned int)dt * mF1b0 * 0.001f) + mF1ac;
        if (mF1ac < 1.0f) return;
        mF154 = target;
    }
    mF1ac = 0.0f;
}

// @ 0x006f40b0
void cRenderInstanceSet::SetElement(int idx, float value)
{
    mFlags1bc[idx] = 1;
    mValues1c8[idx] = value;
}

// @ 0x006f40d0
void cRenderInstanceSet::ClearElements()
{
    for (unsigned int i = 0; i < 12; i++) {
        mFlags1bc[i] = 0;
        mValues1c8[i] = 0.0f;
    }
}

// @ 0x006f4100
void cRenderInstanceSet::SetColor(int a, const float* rgb, float alpha, int b)
{
    (void)a; (void)b;
    struct Color { float r, g, b; } c;
    c.r = rgb[0] * 255.0f;
    c.g = rgb[1] * 255.0f;
    c.b = rgb[2] * 255.0f;
    *(Color*)((char*)this + 0x110) = c;
    mColorA = alpha * 255.0f;
}

// @ 0x006f4170
bool cRenderInstanceSet::IsRangeEmpty() const
{
    return mRangeBegin == mRangeEnd;
}

// @ 0x006f4190
void cRenderInstanceSet::GetRange(int* out)
{
    unsigned int uVar2 = 0;
    int* piVar3 = mArr1b4;
    do {
        if (*piVar3 >= 0) {
            if ((int)uVar2 >= 0) {
                int* iVar1 = ((int**)mModelArray)[uVar2];
                unsigned short idx = *(unsigned short*)((char*)iVar1 + 8);
                void* base = *(void**)((char*)iVar1 + 0x4c);
                out[0] = *(int*)((char*)base + idx * 8);
                out[1] = *(int*)((char*)base + idx * 8 + 4);
                return;
            }
            break;
        }
        uVar2++;
        piVar3++;
    } while (uVar2 < 2);
    out[0] = -1;
    out[1] = -1;
}

// @ 0x006f41e0
cViewer* cRenderInstanceSet::RenderRange(void* src)
{
    int uVar2 = 0;
    int* piVar3 = mArr1b4;
    for (; *piVar3 < 0; ++piVar3) {
        ++uVar2;
        if (1 < (unsigned int)uVar2) return 0;
    }
    if (uVar2 < 0) return 0;
    int* m = (int*)((void**)mModelArray)[uVar2];
    if (*(unsigned short*)((char*)m + 8) == 0xffff) return 0;
    mViewer174->Copy(src, 0, 0);
    unsigned short idx = *(unsigned short*)((char*)m + 8);
    void* base = *(void**)((char*)m + 0x4c);
    mViewer174->f4be0((char*)base + idx * 8, 1);
    mViewer174->f3c20(&g_1619530);
    mViewer174->f3c50(7);
    return mViewer174;
}

// @ 0x006f4280
void cRenderInstanceSet::UpdateEffects(int dt)
{
    Tick154(dt);
    for (int i = 0; i < 2; i++) {
        float* p = ((float**)mModelArray)[i];
        if (*p > 0.0f) {
            *p = *p - (float)(unsigned int)dt * 0.001f;
            if (*p < 0.0f) {
                if (p[1] == 1) {
                    v8((mRangeEnd - mRangeBegin) / 120);
                }
                *p = 0.0f;
            }
        }
    }
}

// @ 0x006f4330
void cGraphicsHash::Resize(unsigned int newSize)
{
    unsigned int bytes = newSize * 4;
    void* p = EASTL_allocator_allocate(bytes + 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    memset_thunk(p, 0, bytes);
    *(int*)((char*)p + bytes) = -1;
    for (unsigned int i = 0; i < mCount; i++) {
        void* node = mBuckets[i];
        while (node) {
            unsigned short key = *(unsigned short*)node;
            mBuckets[i] = *(void**)((char*)node + 8);
            unsigned int idx = key % newSize;
            *(void**)((char*)node + 8) = *(void**)((char*)p + idx * 4);
            *(void**)((char*)p + idx * 4) = node;
            node = mBuckets[i];
        }
    }
    if (mCount > 1) EASTL_allocator_deallocate(mBuckets);
    mBuckets = (void**)p;
    mCount = newSize;
}

// @ 0x006f4450
void** FUN_006f4450(void** first, void** last, void** destEnd)
{
    while (last != first) {
        void* s = *--last;
        void* d = *--destEnd;
        if (s != d) {
            if (s) AddRef(s);
            *destEnd = s;
            if (d) Release(d);
        }
    }
    return destEnd;
}

// @ 0x006f44c0
bool __stdcall FUN_006f44c0(void* a, void* b, cImageHost* host)
{
    void* mgr = FUN_0067dd60();
    int r = (*(int (__thiscall**)(void*, void*, void*, int))(Vt(mgr) + 8))(mgr, a, b, 0);
    if (r != 0) {
        host->GetImageResource((void*)r);
        return true;
    }
    return false;
}

// @ 0x006f4500
bool __stdcall FUN_006f4500(unsigned int id, void* unused, cImageHost* host)
{
    (void)unused;
    if (id == 0x0F19D8D5) {
        void* mgr = FUN_0067dd40();
        void* r = ((void* (__thiscall*)(void*))(*(void***)mgr)[30])(mgr);
        host->GetImageResource(r);
        return true;
    }
    if (id == 0xFD9802C7) {
        void* mgr = FUN_0067dd40();
        void* r = ((void* (__thiscall*)(void*))(*(void***)mgr)[31])(mgr);
        host->GetImageResource(r);
        return true;
    }
    if (id == 0x9B304161) {
        void* mgr = FUN_0067dd40();
        void* r = ((void* (__thiscall*)(void*))(*(void***)mgr)[29])(mgr);
        host->GetImageResource(r);
        return true;
    }
    return false;
}

// @ 0x006f4a10
void __fastcall FUN_006f4a10(char* self, float* point, int extra, char enabled)
{
    if (enabled) {
        CamVec pos;
        float light[3];
        Camera_FetchPositions(&pos, light);

        float dx = pos.x - point[0];
        float dy = pos.y - point[1];
        float dz = pos.z - point[2];
        float v = sqrtf(dx * dx + dy * dy + dz * dz) / *(float*)(self + 0x150);
        *(float*)(self + 0x1a8) = v;
        if (v > 1.0f)
            *(float*)(self + 0x1a8) = g_1485720;
        *(float*)(self + 0x1ac) = 0.0f;
        *(float*)(self + 0x1b0) = *(float*)&extra;
    }
    *(char*)(self + 0x1a4) = enabled;
}

// @ 0x006f4b90
void __fastcall FUN_006f4b90(char* self, void* state, unsigned a, float b, float c, float d, float e)
{
    unsigned save16f9230 = g_16f9230;
    unsigned save16f922c = g_16f922c;
    unsigned save16f9218 = g_16f9218;
    unsigned save16f9200 = g_16f9200;
    bool prevNotFour = (g_16f923c != 4);

    g_16fa38c |= 2;
    g_16f9200 = 3;
    ((void (__thiscall*)(void*))0x11ee580)(state);      // rw::graphics::CompiledState::Dispatch
    g_16fa38c |= 0x10080;
    g_16f923c = 8;
    g_16f9218 = 0;

    void* p1 = FUN_011f1120();
    unsigned short w = *(unsigned short*)(*(int*)((char*)p1 + 0x40) + 0xc);
    void* p2 = FUN_011f1120();
    unsigned short h = *(unsigned short*)(*(int*)((char*)p2 + 0x40) + 0xe);

    float local14[4];
    char ok = FUN_006ddcc0(2, 4, state, local14);
    if (ok != 0) {
        float fi = (float)w;
        float saved = g_16077c8;
        float m = g_16077c4;
        float col[4];
        struct Mat { unsigned d[0x60 / 4]; };
        Mat* base = (Mat*)state;

        *(float*)&base->d[0x00 / 4] = -1.0f - (m * g_1470f1c) / fi;
        *(float*)&base->d[0x04 / 4] = 0.0f;
        *(float*)&base->d[0x08 / 4] = -1.0f - (saved * g_1470f1c) / (float)h;
        *(float*)&base->d[0x18 / 4] = 1.0f - (g_16077c4 * g_1470f1c) / fi;
        *(float*)&base->d[0x1c / 4] = 0.0f;
        *(float*)&base->d[0x20 / 4] = 1.0f - (g_16077c8 * g_1470f1c) / (float)h;
        *(float*)&base->d[0x30 / 4] = -1.0f - (g_16077c4 * g_1470f1c) / fi;
        *(float*)&base->d[0x34 / 4] = 0.0f;
        *(float*)&base->d[0x38 / 4] = -1.0f - (g_16077c8 * g_1470f1c) / (float)h;
        *(float*)&base->d[0x48 / 4] = 1.0f - (g_16077c4 * g_1470f1c) / fi;
        *(float*)&base->d[0x4c / 4] = 0.0f;
        *(float*)&base->d[0x50 / 4] = 1.0f - (g_16077c8 * g_1470f1c) / (float)h;

        *(float*)&base->d[0x0c / 4] = 1.0f;
        *(float*)&base->d[0x10 / 4] = 0.0f;
        *(float*)&base->d[0x14 / 4] = 1.0f;
        *(float*)&base->d[0x24 / 4] = 1.0f;
        *(float*)&base->d[0x28 / 4] = 1.0f;
        *(float*)&base->d[0x2c / 4] = 1.0f;
        *(float*)&base->d[0x3c / 4] = 1.0f;
        *(float*)&base->d[0x40 / 4] = 1.0f;
        *(float*)&base->d[0x44 / 4] = 1.0f;
        *(float*)&base->d[0x54 / 4] = 0.0f;
        *(float*)&base->d[0x58 / 4] = 1.0f;
        *(float*)&base->d[0x5c / 4] = 1.0f;

        col[0] = b * g_13eecd4;
        col[1] = c * g_13eecd4;
        col[2] = d * g_13eecd4;
        col[3] = e * g_13eecd4;
        unsigned packed = SP_ColorRGBAToU32(col);
        base->d[0x00 / 4] = packed;   // placeholder overwritten below by rgba store
        // The original writes the packed colour to 0x00,0x24,0x3c,0x54 of the state block.
        base->d[0x00 / 4] = packed;
        base->d[0x24 / 4] = packed;
        base->d[0x3c / 4] = packed;
        base->d[0x54 / 4] = packed;
        (void)local14;
        FUN_006ddd10(3, *(void**)(self + 0x224));
    }

    g_16f9230 = save16f9230;
    g_16f922c = save16f922c;
    g_16fa38c |= 0x13082;
    g_16f923c = (unsigned)prevNotFour * 4 + 4;
    g_16f9218 = save16f9218;
    g_16f9200 = save16f9200;
}

// @ 0x006f4ff0
void __fastcall FUN_006f4ff0(char* self, void** out, unsigned short* key)
{
    unsigned short k = *key;
    unsigned mod = *(unsigned*)(self + 8);
    unsigned idx = (unsigned)k % mod;
    unsigned* bucket = (unsigned*)(*(int*)(self + 4) + idx * 4);
    unsigned node = *bucket;

    while (node != 0) {
        if (k == *(unsigned short*)node) {
            *out = (void*)node;
            *((unsigned char*)out + 8) = 0;
            out[1] = bucket;
            return;
        }
        node = *(unsigned*)(node + 8);
    }

    char local8[4];
    unsigned local4;
    FUN_00921440(local8, *(unsigned*)(self + 8), *(unsigned*)(self + 0xc), 1);

    unsigned* fresh = (unsigned*)operator_new_graphics(0xc, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (fresh) {
        fresh[0] = *(unsigned*)key;
        fresh[1] = *(unsigned*)(key + 1);
    }
    fresh[2] = 0;
    (void)local4;

    unsigned* link = (unsigned*)(*(int*)(self + 4) + idx * 4);
    fresh[2] = *link;
    *link = (unsigned)fresh;
    ++*(unsigned*)(self + 0xc);

    *out = fresh;
    *((unsigned char*)out + 8) = 1;
    out[1] = link;
}

// @ 0x006f51b0
void __fastcall FUN_006f51b0(char* self)
{
    VecBase* vec = (VecBase*)(self + 0x78);
    vec->DestroyRange((void**)vec->mpBegin, (void**)vec->mpEnd);
    void* p = vec->mpBegin;
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = *(void**)(self + 0x60);
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = *(void**)(self + 0x4c);
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    ResourceHashtable* res = (ResourceHashtable*)(self + 0x2c);
    res->DoFreeNodes(res->mpBucketArray, res->mnBucketCount);
    res->mnElementCount = 0;
    if (res->mnBucketCount > 1) EASTL_allocator_deallocate((void*)res->mpBucketArray);
    WideHashtable* wide = (WideHashtable*)(self + 0xc);
    wide->DoFreeNodes(wide->mpBucketArray, wide->mnBucketCount);
    wide->mnElementCount = 0;
    if (wide->mnBucketCount > 1) EASTL_allocator_deallocate((void*)wide->mpBucketArray);
}

// @ 0x006f5260
void __fastcall FUN_006f5260(char* self, unsigned a2, int a3, unsigned a4, void** params)
{
    void* raw = operator_new_graphics(0x174, "Graphics", 0, 0, 0, 0);
    void* viewer;
    if (raw == 0)
        viewer = 0;
    else
        viewer = ((void* (__thiscall*)(void*))0x7c3f70)(raw);   // cViewer::cViewer

    ((bool (__thiscall*)(void*, bool))0x7c4dd0)(viewer, false);  // cViewer::Init
    ((bool (__thiscall*)(void*, void*, bool, bool))0x7c50b0)(viewer, *params, false, false); // Copy

    int local1c = -1;
    unsigned local18 = 0xffffffff;
    unsigned char kind = (unsigned char)a4;

    if (kind == 1) {
        void* mgr = FUN_0067dd40();
        if (((char (__thiscall*)(void*))Vt(mgr)[0x38 / 4])(mgr) != 0) {
            void* mgr2 = FUN_0067dd40();
            void* raster;
            ((void (__thiscall*)(void*, void*))Vt(mgr2)[0xdc / 4])(mgr2, &raster);
            ((void (__thiscall*)(void*, void*, bool))0x7c4be0)(viewer, &raster, true);
        }
    } else if ((unsigned char)(kind - 2) < 4) {
        void* mgr = FUN_0067dd40();
        ((void (__thiscall*)(void*, int, void*, bool))Vt(mgr)[0xa8 / 4])(mgr, kind - 2, &local1c, true);
        ((void (__thiscall*)(void*, void*, bool))0x7c4be0)(viewer, &local1c, true);
    } else {
        unsigned k = (unsigned)a4 & 0xff;
        void* it = ((void* (__thiscall*)(void*, unsigned*))0x892970)(self + 0xc, &k);
        unsigned nodeFirst = *(unsigned*)it;
        unsigned bucketArr = *(unsigned*)(self + 4);
        unsigned bucket = *(unsigned*)(self + 8);
        if (nodeFirst == *(unsigned*)(bucketArr + bucket * 4))
            goto after_first;
        {
            unsigned row = *(unsigned*)(nodeFirst + 4);
            int* arr = *(int**)(self + 0x4c);
            ((void (__thiscall*)(void*, int*, bool))0x7c4be0)(viewer, arr + row * 2, true);
        }
    }
after_first:
    ((void (__thiscall*)(void*, unsigned))0x7c3c50)(viewer, 7);   // cViewer::Clear

    local18 = 0xffffffff;
    local1c = -1;
    if (a2 == 0 && a3 == 0) {
        if (*(unsigned short*)(self + 8) == 0xffff)
            goto after_second;
        ((void (__thiscall*)(void*, int*, bool))0x7c4be0)(viewer, &local1c, true);
    } else {
        if ((a3 - 1 + (unsigned)(a2 > 1) == 0) && (a2 - 2 < 4)) {
            void* mgr = FUN_0067dd40();
            ((void (__thiscall*)(void*, int, void*, bool))Vt(mgr)[0xa8 / 4])(mgr,
                (int)((unsigned short)a2) - 2, &local1c, true);
            goto after_second;
        }
        unsigned k = a2 & 0xffff;
        void* it = ((void* (__thiscall*)(void*, unsigned*))0x892970)(self + 0xc, &k);
        unsigned nodeFirst = *(unsigned*)it;
        unsigned bucketArr = *(unsigned*)(self + 4);
        unsigned bucket = *(unsigned*)(self + 8);
        if (nodeFirst == *(unsigned*)(bucketArr + bucket * 4))
            goto after_second;
        unsigned row = *(unsigned*)(nodeFirst + 4);
        local1c = *(int*)(*(int*)(self + 0x4c) + row * 8);
        local18 = *(unsigned*)(*(int*)(self + 0x4c) + 4 + row * 8);
    }
after_second:
    if (local1c != -1) {
        ((void (__thiscall*)(void*, void*, bool))0x7c4be0)(viewer, &local1c, true);
        ((void (__thiscall*)(void*, unsigned))0x7c3c50)(viewer, 7);
    }
    ((void (__thiscall*)(void*))0x7c3ba0)(viewer);
    if (viewer != 0) {
        ((void (__thiscall*)(void*))0x7c4000)(viewer);
        EASTL_allocator_deallocate(viewer);
    }
}

// @ 0x006f5cd0
Vec0C& Vec0C::Assign(const Vec0C* x)
{
    if (x != this) {
        Elem0C* xBegin = x->mpBegin;
        int cap = (int)(mpCapacity - mpBegin);
        int n = (int)(x->mpEnd - xBegin);
        if ((unsigned)n > (unsigned)cap) {
            Elem0C* p = AllocCopy((unsigned)n, xBegin, x->mpEnd);
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                operator_delete_((void*)mpBegin);
            mpCapacity = p + n;
            mpBegin = p;
            mpEnd = p + n;
            return *this;
        }
        int have = (int)(mpEnd - mpBegin);
        if ((unsigned)n > (unsigned)have) {
            FUN_00b84c80((int)x->mpBegin, (int)(x->mpBegin + (int)(mpEnd - mpBegin)), (int)mpBegin);
            Elem0C* tail = x->mpEnd;
            FUN_00951740((void**)&tail, (int)(x->mpBegin + (int)(mpEnd - mpBegin)), (int)tail,
                         (int)mpEnd, (int)tail);
            mpEnd = mpBegin + n;
            return *this;
        }
        FUN_00b84c80((int)x->mpBegin, (int)x->mpEnd, (int)mpBegin);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x006f5e00
Vec8& Vec8::Assign(const Vec8* x)
{
    if (x != this) {
        Elem8* xBegin = x->mpBegin;
        int cap = (int)(mpCapacity - mpBegin);
        int n = (int)(x->mpEnd - xBegin);
        if ((unsigned)n > (unsigned)cap) {
            Elem8* p = AllocCopy((unsigned)n, xBegin, x->mpEnd);
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                operator_delete_((void*)mpBegin);
            mpCapacity = p + n;
            mpBegin = p;
            mpEnd = p + n;
            return *this;
        }
        int have = (int)(mpEnd - mpBegin);
        if ((unsigned)n > (unsigned)have) {
            FUN_00ac4440((int)x->mpBegin, (int)(x->mpBegin + (int)(mpEnd - mpBegin)), (int)mpBegin);
            Elem8* tail = x->mpEnd;
            FUN_00714bc0((void**)&tail, (int)(x->mpBegin + (int)(mpEnd - mpBegin)), (int)tail,
                         (int)mpEnd, (int)x);
            mpEnd = mpBegin + n;
            return *this;
        }
        FUN_00ac4440((int)x->mpBegin, (int)x->mpEnd, (int)mpBegin);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x006f5f80
void cState::W5f80(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7)
{
    float a = 0.0f;
    float b = 1.0f;
    int mode = 0x32;
    if (ctx->mRGB[2] != 0) mode = 0x33;
    if (ctx->mRGB[0] != 0xff) a = colors->mColors[ctx->mRGB[0]];
    if (ctx->mRGB[1] != 0xff) b = colors->mColors[ctx->mRGB[1]];
    BlobCall(this, 0, a, b, 0.0f, 0.0f);
    F54a0(mode, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6060
void cState::W6060(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7)
{
    float a = 1.0f;
    unsigned short c0 = ctx->mRGB[0];
    if (c0 != 0xff) a = colors->mColors[c0];
    BlobCall(this, 0, a, 0.0f, 0.0f, 0.0f);
    F54a0(0x50, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f60f0
void cState::W60f0(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7)
{
    float a = 1.0f;
    unsigned short c0 = ctx->mRGB[0];
    if (c0 != 0xff) a = colors->mColors[c0];
    BlobCall(this, 0, a, 0.0f, 0.0f, 0.0f);
    F54a0(0x5a, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6180
void cState::W6180(cColorCtx* colors, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7)
{
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    unsigned short c0 = ctx->mRGB[0];
    if (c0 != 0xff) r = colors->mColors[c0];
    unsigned short c1 = ctx->mRGB[1];
    if (c1 != 0xff) g = colors->mColors[c1];
    unsigned short c2 = ctx->mRGB[2];
    if (c2 != 0xff) b = colors->mColors[c2];
    BlobCall(this, 0, r, g, b, 0.0f);
    F54a0(100, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6270
void cState::W6270(int a0, cColorCtx* ctx, int p3, int p4, int p5, int p6, int p7)
{
    (void)a0;
    unsigned char* p = ctx->mRGB;
    int mode = 0x6e;
    float v14 = 1.0f, v18 = 1.0f, v1c = 1.0f, v20 = 1.0f;
    float v4 = 1.0f, v8 = 1.0f, vc = 1.0f, v10 = 1.0f;
    if (p[0] != 0) mode = 0x6f;
    unsigned short c1 = p[1];
    if (c1 != 0xff) v14 = ctx->mColors[c1];
    int m2 = mode;
    if (p[2] != 0) m2 = mode + 2;
    char* tbl = ctx->mTbl;
    unsigned short c3 = p[3];
    if (c3 != 0xff) {
        v18 = *(float*)(tbl + c3 * 0xc);
        v1c = *(float*)(tbl + c3 * 0xc + 4);
        v20 = *(float*)(tbl + c3 * 0xc + 8);
    }
    unsigned short c4 = p[4];
    if (c4 != 0xff) {
        v4 = *(float*)(tbl + c4 * 0xc);
        v8 = *(float*)(tbl + c4 * 0xc + 4);
        vc = *(float*)(tbl + c4 * 0xc + 8);
    }
    unsigned short c5 = p[5];
    if (c5 != 0xff) v10 = ctx->mColors[c5];
    BlobCall(this, 0, v14, v18, v1c, v20);
    BlobCall(this, 1, v4, v8, vc, v10);
    F54a0(m2, 0, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6430
void cState_s006f_6430::ColorBE(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    float r = 1.0f, g = 1.0f, b = 1.0f;
    unsigned short i = d->idx[0];
    if (i != 0xff) {
        cVec3 v(t->vec3s[i]);
        r = v.x; g = v.y; b = v.z;
    }
    sh.SetShConst(0, r, g, b, 0.0f);
    F54a0(0xbe, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f6500
void cState_s006f_6430::ColorDC(cTables* t, cDesc* d, int p3, int p4, int p5, int p6, int p7)
{
    float x = 0.0f, y = 1.0f;
    unsigned short i = d->idx[0];
    if (i != 0xff) x = t->floats[i];
    unsigned short j = d->idx[1];
    if (j != 0xff) y = t->floats[j];
    sh.SetShConst(0, x, y, 0.0f, 0.0f);
    F54a0(0xdc, p3, p4, p5, 0, 0, p6, p7);
}

// @ 0x006f65d0
int& cHashMap16::Subscript(const unsigned short& k)
{    cHNode* n;
    {
        cHIter it = find(k);
        if (it.mpNode != mpBucketArray[mnBucketCount]) {
            n = it.mpNode;
            goto hit;
        }
    }
    {
        cHPair v;
        v.first = k;
        v.second = 0;
        cTrue tag;
        *reinterpret_cast<unsigned char*>(&tag) = 0;
        cHInsertResult r = DoInsertValue(v, tag);
        n = r.first.mpNode;
    }
hit:
    return n->second;
}

// @ 0x006f66a0
void cVecU16::push_back(const unsigned short& v)
{
    unsigned short* e = end;
    if (e < cap) {
        end = e + 1;
        if (e != 0) { *e = v; return; }
    } else {
        Insert(e, v);
    }
}

// @ 0x006f66d0
void __fastcall FUN_006f66d0(int* self)
{
    void* p;
    p = (void*)self[0x19]; if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[0x14]; if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[0xf];  if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[10];   if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[5];    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    ((cHashtable*)self)->FreeNodes((void*)self[0], (void*)self[1]);
    p = (void*)self[0];    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
}

// @ 0x006f6770
cByteVec& cByteVec::Assign(const cByteVec& x)
{
    if (&x != this) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCap - mpBegin)) {
            unsigned char* pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1]) operator_delete_(mpBegin);
            mpBegin = pNew;
            mpEnd = mpBegin + n;
            mpCap = pNew + n;
            return *this;
        }
        if (n > (unsigned)(mpEnd - mpBegin)) {
            memcpy(mpBegin, x.mpBegin, mpEnd - mpBegin);
            memcpy(mpEnd, x.mpBegin + (mpEnd - mpBegin), x.mpEnd - (x.mpBegin + (mpEnd - mpBegin)));
            mpEnd = mpBegin + n;
            return *this;
        }
        memcpy(mpBegin, x.mpBegin, x.mpEnd - x.mpBegin);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x006f8140
char* FUN_006f8140(char* first, char* last, char* dest)
{
    if (first != last) {
        do {
            dest[0] = first[0];
            dest[1] = first[1];
            *(int*)(dest + 8) = *(int*)(first + 8);
            *(int*)(dest + 0xc) = *(int*)(first + 0xc);
            ((cVecBool*)(dest + 0x10))->Assign(first + 0x10);
            first += 0x28;
            dest += 0x28;
        } while (first != last);
    }
    return dest;
}

// @ 0x006f8260
bool cFilterChain2::Resolve(ResKey key)
{
    if ((key.lo & key.hi) == 0xffffffffu)
        return false;
    unsigned short k = (unsigned short)key.lo;
    HtIter_s006f_7430 tmp;
    HtIter_s006f_7430 it = *mTable.find(&tmp, &k);
    HtIter_s006f_7430 e;
    e.bucket = mTable.mpBuckets + mTable.mBucketCount;
    e.node = *e.bucket;
    if (it.node == e.node) {
        ResRef ref;
        ref.mp = 0;
        if (!TryA(key, &ref) && !TryB(key, &ref))
            return false;
        mRefs.push_back(ref);
        *mIndex[key] = (int)(mRefs.mpEnd - mRefs.mpBegin) - 1;
    }
    return true;
}

// @ 0x006f8710
extern "C" FilterElem28** __cdecl CopyFilterRange(FilterElem28** dst, const FilterElem28* first, const FilterElem28* last, FilterElem28* result)
{
  *dst = result;
  if (first != last) {
    for (; first != last; first = (const FilterElem28*)((const char*)first + 0x28)) {
      FilterElem28* p = *dst;
      if (p != 0) {
        p->mFlags = first->mFlags;
        p->mDest = first->mDest;
        p->mSourceLo = first->mSourceLo;
        p->mSourceHi = first->mSourceHi;
        uint32_t n = (uint32_t)((const char*)first->mBufEnd - (const char*)first->mBufBegin);
        uint8_t* buf = 0;
        if (n != 0) {
          buf = (uint8_t*)EASTL_allocator_allocate(
              n, "Graphics", 0, 0,
              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
              0xd1);
        }
        p->mBufBegin = buf;
        p->mBufEnd = buf;
        p->mBufCap = buf + n;
        memcpy(buf, first->mBufBegin, n);
        p->mBufEnd = buf + n;
      }
      *dst = (FilterElem28*)((char*)*dst + 0x28);
    }
  }
  return dst;
}

// @ 0x006f8d40
cFilterChain::cFilterChain()
{
  vtbl1 = (void*)0x13eb384;
  vtbl2 = (void*)0x13ec458;
  m00c = 0;
  mCustomSD.Init();
  vtbl0 = (void*)0x140b7b8;
  vtbl1 = (void*)0x140b7a8;
  vtbl2 = (void*)0x140b798;

  m110 = g1619524;
  m114 = g1619528;
  m118 = g161952c;
  m11c = 0.0f;
  mDescBegin = 0;
  mDescEnd = 0;
  mDescCap = 0;
  m134 = 0;
  mTexBegin = 0;
  mTexEnd = 0;
  mTexCap = 0;
  m14c = g1477fbc;
  m150 = g13f1160;
  m154 = 0.5f;      // orig reads [0x1471064] (0.5f)
  m158 = 2.0f;      // orig reads [0x1470f1c] (2.0f), not 1.0f
  m15c = 0.5f;      // orig reads [0x1471064] (0.5f)
  m160 = g1477fbc;
  m170 = g1485720;
  mViewer = 0;
  m184 = 0;
  m188 = g1534250;
  m18c = g1534254;
  m190 = g1534258;
  m194 = g16194f8;
  m198 = g16194fc;
  m19c = g1619500;
  m1a0 = 0.0f;
  m1a4 = 0;
  m1a8 = 0.5f;      // orig keeps xmm1 = [0x1471064] (0.5f) alive and stores it here
  m1ac = 0.0f;
  m1b0 = g1485544;
  m1f8 = 0;
  mBitsBegin = 0;
  mBitsEnd = 0;
  mBitsCap = 0;
  mArrBegin = 0;
  mArrEnd = 0;
  mArrCap = 0;
  m224 = 0;
}

// @ 0x006f8f60
cFilterChain::~cFilterChain()
{
  vtbl0 = (void*)g_140b7b8;
  vtbl1 = (void*)g_140b7a8;
  vtbl2 = (void*)g_140b798;
  _ReadWriteBarrier();

  FreeGuarded(mArrBegin);
  FreeGuarded(mBitsBegin);
  FreeGuarded(mTexBegin);

  uint8_t* p = mDescBegin;
  uint8_t* e = mDescEnd;
  while (p < e) {
    ((FilterDesc78*)p)->Destroy();
    p += 0x78;
  }
  FreeGuarded(mDescBegin);

  vtbl2 = (void*)g_13ec458;
  vtbl1 = (void*)g_13eb394;
  vtbl0 = (void*)g_13eb938;
}

// @ 0x006f94b0
void EvChain::Notify(int a0, int a1, int a2, int a3)
{
  m224 = a3;
  if (a1 == 0x16 && m120 != m124) {
    SubSF(a0, a2);
    if (m134) {
      m134 = 0;
      void* srv = SP_MessageServer();
      ((void(__thiscall*)(void*, int, int, int))(*(void***)srv)[5])(srv, 0x6694879, 0, 0);
    }
  }
  m224 = 0;
}

// @ 0x006f9520
void FilterDesc::AssignDescA(const FilterDesc* src)
{
  int n = (int)((src->v00.end - src->v00.begin) / 0x28);
  FilterElem28_s006f_9250* newBuf = 0;
  if (n != 0) {
    newBuf = (FilterElem28_s006f_9250*)EASTL_allocate_((unsigned)(n * 0x28), "Graphics", 0, 0,
                                            (const char*)0x013ebb38, 0xd1);
  }
  v00.begin = newBuf;
  v00.end = newBuf;
  v00.cap = (FilterElem28_s006f_9250*)((char*)newBuf + n * 0x28);
  void* endSlot = v00.end;
  CopyFilterRange_s006f_9250(&endSlot, src->v00.begin, src->v00.end, newBuf);
  v00.end = (FilterElem28_s006f_9250*)endSlot;
}

// @ 0x006f95e0
void FilterDesc::AssignDescB(const FilterDesc* src)
{
  AssignDescA(src);                                     // +0x00 vector<FilterElem28>

  {                                                     // +0x14 vector<8-byte>
    int n = (int)((char*)src->v14.end - (char*)src->v14.begin) >> 3;
    VecReserve8(&v14, n);
    void* endSlot = 0;
    CopyElems8(&endSlot, src->v14.begin, src->v14.end, v14.begin);
    v14.end = endSlot;
  }
  {                                                     // +0x28 vector<4-byte>
    int n = (int)((char*)src->v28.end - (char*)src->v28.begin) >> 2;
    VecReserve4(&v28, n);
    int bytes = (int)((char*)src->v28.end - (char*)src->v28.begin);
    memmove(v28.begin, src->v28.begin, bytes);
    v28.end = (char*)v28.begin + bytes;
  }
  {                                                     // +0x3c vector<12-byte>
    VecReserve12(&v3c, &src->v3c);
  }
  {                                                     // +0x50 vector<8-byte>
    int n = (int)((char*)src->v50.end - (char*)src->v50.begin) >> 3;
    VecReserve8(&v50, n);
    void* endSlot = 0;
    CopyElems8f(&endSlot, src->v50.begin, src->v50.end, v50.begin);
    v50.end = endSlot;
  }
  {                                                     // +0x64 vector<8-byte>
    int n = (int)((char*)src->v64.end - (char*)src->v64.begin) >> 3;
    VecReserve8(&v64, n);
    int bytes = (int)((char*)src->v64.end - (char*)src->v64.begin);
    memmove(v64.begin, src->v64.begin, bytes);
    v64.end = (char*)v64.begin + bytes;
  }
}

// @ 0x006f9730
Vec28& Vec28::operator=(const Vec28& src)
{
  if (this == &src)
    return *this;
  int srcCount = (int)(src.end - src.begin) / 0x28;
  FilterElem28_s006f_9250* curBegin = begin;
  FilterElem28_s006f_9250* curEnd = end;

  if (srcCount > (int)(cap - begin) / 0x28) {
    // grow: build a fresh buffer, tear down the old storage, install it
    FilterElem28_s006f_9250* buf = Vec28Realloc(this, srcCount, src.begin, src.end);
    DestroyFilterRange(curBegin, curEnd);
    if (curBegin != 0 && *((int*)curBegin - 1) != 0)
      EASTL_deallocate_(curBegin);
    begin = buf;
    end = (FilterElem28_s006f_9250*)((char*)buf + srcCount * 0x28);
    cap = end;
    return *this;
  }

  int curCount = (int)(curEnd - curBegin) / 0x28;
  if (srcCount > curCount) {
    // copy over the live elements, then uninitialized_copy the remainder
    const FilterElem28_s006f_9250* mid = (const FilterElem28_s006f_9250*)((const char*)src.begin + curCount * 0x28);
    FilterElem28_s006f_9250* dst = AssignFilterRange(curBegin, src.begin, mid);
    void* endSlot = curEnd;
    CopyFilterRange_s006f_9250(&endSlot, mid, src.end, dst);
    end = (FilterElem28_s006f_9250*)((char*)begin + srcCount * 0x28);
    return *this;
  }

  FilterElem28_s006f_9250* newEnd = AssignFilterRange(begin, src.begin, src.end);
  DestroyFilterRange(newEnd, curEnd);
  end = (FilterElem28_s006f_9250*)((char*)begin + srcCount * 0x28);
  return *this;
}

// @ 0x006f9910
Elem78& Elem78::operator=(const Elem78& o)
{
  m0 = o.m0;
  m1 = o.m1;
  m2 = o.m2;
  m3 = o.m3;
  m4 = o.m4;
  m5 = o.m5;
  return *this;
}

// @ 0x006f9970
extern "C" Elem78* __cdecl copy79(Elem78* first, Elem78* last, Elem78* result)
{
  for (; first != last; ++first, ++result) *result = *first;
  return result;
}

// @ 0x006f99e0
extern "C" Elem78* __cdecl copy_backward79(Elem78* first, Elem78* last, Elem78* result)
{
  while (last != first) {
    --last;
    --result;
    *result = *last;
  }
  return result;
}

// @ 0x006f9a50
Elem78* Vec78::erase(Elem78* first, Elem78* last)
{  Elem78* en = this->end;
  Elem78* newEnd = copy79(last, en, first);
  Elem78* e = this->end;
  for (Elem78* p = newEnd; p < e; ++p)
    p->~Elem78();
  this->end = this->end - (last - first);
  return first;
}

// @ 0x006f9ac0
void CFilterChain::Notify2(int a, int b)
{
  Vec78Ins* self = (Vec78Ins*)&m120;     // begin @+0x120, end @+0x124, cap @+0x128
  Elem78* where = (Elem78*)(void*)a;     // insertion position
  Elem78* src   = (Elem78*)(void*)b;     // element to copy
  if (self->end == self->cap) {
    // no spare capacity: reallocate
    int n = (int)((char*)self->end - (char*)self->begin) / 0x78;
    if (n == 0) {
      n = 1;
    } else {
      n += n;
    }
    Elem78* nb = (Elem78*)EASTL_allocate_((unsigned)(n * 0x78), (const char*)0x013ebb38,
                                          0, 0, (const char*)0x013eb8a4, 0xd1);
    Elem78* pos = CopyRange78(nb, self->begin, where);      // copy [begin, where)
    AssignRange78(pos, where, self->end);                    // copy [where, end)
    // destroy the old records and free the old buffer
    Destroy78(self->begin, self->end);
    if (self->begin != 0 && *((int*)self->begin - 1) != 0)
      EASTL_deallocate_(self->begin);
    self->end = (Elem78*)((char*)nb + ((char*)self->end - (char*)self->begin));
    self->begin = nb;
    self->cap = (Elem78*)((char*)nb + n * 0x78);
  } else {
    // spare capacity: shift the tail by one and copy the element in
    Elem78* newLast = (Elem78*)((char*)self->end + 0x78);
    CopyBackward78(newLast, where, self->end);
    AssignRange78(where, src, (const Elem78*)((const char*)src + 0x78));
    self->end = (Elem78*)((char*)self->end + 0x78);
  }
  m224 = 0;
}

// @ 0x006fcdc0
bool FragRec::Read(IO* io, uint32_t version)
{
  io->Get(m1);
  if (version <= 6) {
    uint8_t tmp;
    io->Get(tmp);
  }
  io->Get(m2);
  io->Get(m4);
  io->Get(m6);
  if (version <= 6) {
    uint16_t tmp;
    io->Get(tmp);
    io->Get(tmp);
    io->Get(tmp);
  }
  io->Get(m8);
  io->Get(mc);
  io->Get(m10);
  io->Get(m14);
  io->Get(m18);
  return true;
}

// @ 0x006fceb0
bool FragRec::Write(IO* io)
{
  io->Put(m1);
  io->Put(m2);
  io->Put(m4);
  io->Put(m6);
  io->Put(m8);
  io->Put(mc);
  io->Put(m10);
  io->Put(m14);
  io->Put(m18);
  return true;
}

// @ 0x006fcf90
bool cFragmentShader::Write(IO* io)
{
  if (((int(__thiscall*)(void*, void*))FUN_00777760)(this, io) == 0)
    return false;

  for (int i = 0; i < 0x10; ++i) {
    FragRec* aB = mSlotsA[i].mpBegin;
    FragRec* aE = mSlotsA[i].mpEnd;
    FragRec* bB = mSlotsB[i].mpBegin;
    FragRec* bE = mSlotsB[i].mpEnd;
    if (aB == aE && bB == bE)
      continue;

    char idx = (char)i;
    FUN_0093a9a0(io, &idx, 1);

    uint32_t n1 = (uint32_t)(uintptr_t)((char*)aE - (char*)aB) / 0x1c;
    FUN_0093aa70(io, &n1, 1, 0);
    for (uint32_t k = 0; k < n1; ++k) {
      aB[k].Write(io);
      char b = *(char*)&aB[k];
      FUN_0093a9a0(io, &b, 1);
    }

    uint32_t n2 = (uint32_t)(uintptr_t)((char*)bE - (char*)bB) / 0x1c;
    FUN_0093aa70(io, &n2, 1, 0);
    for (uint32_t k = 0; k < n2; ++k) {
      bB[k].Write(io);
      char b = *(char*)&bB[k];
      FUN_0093a9a0(io, &b, 1);
    }
  }

  char term = (char)0xff;
  FUN_0093a9a0(io, &term, 1);
  return true;
}

// @ 0x006fd1b0
cFragmentShader::~cFragmentShader()
{
}

// @ 0x006fd280
cFragmentShader::cFragmentShader()
: mField38(0), mRefCount(0), mField40(0), mField44(0) {
}

// @ 0x006fd300
int cFragmentShader::Release()
{
  int ref = (int)mRefCount - 1;
  ((void(__thiscall*)(void*))FUN_011f4200)(this);
  if (ref == 0) {
    this->~cFragmentShader();
    FUN_00f47380(this);
  }
  return ref;
}

// @ 0x006fd330
void Vec25::insert_moved(void* pos, unsigned n, const void* src)
{
  uint32_t cap = (uint32_t)(uintptr_t)((char*)mpCap - (char*)mpBegin) / 0x1c;
  if (n > cap) {
    uint32_t size = (uint32_t)(uintptr_t)((char*)mpEnd - (char*)mpBegin) / 0x1c;
    uint32_t newCap = size * 2;
    if (size == 0)
      newCap = 1;
    uint32_t want = size + n;
    if (want < newCap)
      want = newCap;
    char* buf = want ? (char*)AllocGraphics(want * 0x1c) : 0;
    char* e1 = (char*)FUN_00847ff0(mpBegin, pos, buf);
    FUN_006fd220(e1, n, src);
    char* e2 = (char*)FUN_00847ff0(pos, mpEnd, e1 + n * 0x1c);
    if (mpBegin != 0 && ((int*)((char*)mpBegin - 4))[0] != 0)
      FUN_00f47380(mpBegin);
    mpBegin = (FragRec*)buf;
    mpEnd = (FragRec*)e2;
    mpCap = (FragRec*)(buf + want * 0x1c);
    return;
  }

  if (n == 0)
    return;

  uint32_t seven[7];
  {
    volatile uint32_t* d7 = seven;
    const volatile uint32_t* s7 = (const volatile uint32_t*)src;
    for (int i = 0; i < 7; ++i)
      d7[i] = s7[i];
  }

  char* p = (char*)pos;
  char* end = (char*)mpEnd;
  uint32_t after = (uint32_t)(uintptr_t)(end - p) / 0x1c;

  if (n < after) {
    uint32_t nb = n * 0x1c;
    char* mid = end - nb;
    FUN_006fd170(seven, mid, end, end, p);
    FUN_006fd250(p, mid, end);
    mpEnd = (FragRec*)(end + nb);
    FUN_006fd140(p, p + nb, seven);
  } else {
    uint32_t extra = n - after;
    FUN_006fd220(end, extra, seven);
    mpEnd = (FragRec*)(end + extra * 0x1c);
    FUN_006fd170(seven, p, end, mpEnd, p);
    mpEnd = (FragRec*)((char*)mpEnd + after * 0x1c);
    FUN_006fd140(p, end, seven);
  }
}

// @ 0x006fd520
void Vec1c::Resize(unsigned n)
{
    if (n > (unsigned)Size()) {
        Elem1c temp;
        temp.stream = 0xff;
        ((CellVector*)this)->insert(end, n - Size(), &temp);
    } else {
        ((CellVector*)this)->erase(begin + n * 0x1c, end);
    }
}

// @ 0x006fd5d0
bool StreamCtx::ReadDecls(void* stream, unsigned flag, void* arg)
{
    if (!FUN_00777840(stream, flag, arg))
        return false;
    FUN_0093a6c0(stream, &flag, 1);
    while ((unsigned char)flag != 0xff) {
        unsigned count;
        FUN_0093a780(stream, &count, 1, 0);
        Vec1c* v0 = (Vec1c*)((char*)this + 0x48 + (flag & 0xff) * 0x14);
        v0->Resize(count);
        if ((int)count > 0) {
            char* base = v0->begin;
            Elem1c* e = (Elem1c*)base;
            unsigned n = count;
            do {
                e->WriteBinary(stream, arg);
                FUN_0093a6c0(stream, e, 1);
                ++e;
            } while (--n != 0);
        }
        FUN_0093a780(stream, &count, 1, 0);
        Vec1c* v1 = (Vec1c*)((char*)this + 0x188 + (flag & 0xff) * 0x14);
        v1->Resize(count);
        if ((int)count > 0) {
            char* base = v1->begin;
            Elem1c* e = (Elem1c*)base;
            unsigned n = count;
            do {
                e->WriteBinary(stream, arg);
                FUN_0093a6c0(stream, e, 1);
                ++e;
            } while (--n != 0);
        }
        FUN_0093a6c0(stream, &flag, 1);
    }
    FUN_006fd990(this);
    return true;
}

// @ 0x006fd730
void __cdecl FUN_006fd730(int stage, int type, int value)
{
    if (value != g_samplerShadow[stage * 14 + type]) {
        void* dev = g_device;
        void* fn = Vt(dev)[0x114 / 4];
        ((void(__stdcall*)(void*, int, int, int))fn)(dev, stage, type, value);
        g_softStateUpdated |= 0x2000000;
        g_samplerDelta[stage] |= (type - 1);
        g_samplerShadow[stage * 14 + type] = value;
    }
}

// @ 0x006fd990
void __cdecl FUN_006fd990(void* self)
{
    *(void**)((char*)self + 0x14) = (void*)&FUN_006fd7d0;
}

// @ 0x006ff170
void __cdecl FUN_006ff170(void* stream)
{
    IO_s006f_f170* io = (IO_s006f_f170*)stream;
    io->Put(0u);
    unsigned count = (unsigned)((g_vs_end - g_vs_begin) / 0x130);
    io->Put(count);
    VecU8 buf;
    buf.mpBegin = 0;
    buf.mpEnd = 0;
    buf.mpCap = 0;
    if ((int)count > 0) {
        unsigned off = 0;
        unsigned n = count;
        do {
            VsRecord* r = (VsRecord*)(g_vs_begin + off);
            io->Write(r->mBlob, 0x20);
            if (r->mpShader == 0) {
                io->Put(0u);
            } else {
                unsigned sz = FUN_00777740(r->mpShader);
                buf.resize(sz);
                FUN_00777720(r->mpShader, (int)sz, buf.mpBegin);
                io->Put(sz);
                io->Write(buf.mpBegin, (int)sz);
            }
            io->Put((unsigned)r->mCount);
            for (int i = 0; i < r->mCount; ++i) {
                FragElem* e = r->mpElems[i];
                io->Put(e->mField10);
                io->Put(e->mField12);
                io->Put(e->mField14);
                io->Put(e->mField16);
                io->Put(e->mField18);
            }
            io->Put(r->mFieldAC, r->mCount);
            io->Put((unsigned)r->mField12C);
            off += 0x130;
        } while (--n != 0);
    }
}

// @ 0x006ff750
void __cdecl FUN_006ff750(void* stream)
{
    IO_s006f_f170* io = (IO_s006f_f170*)stream;
    VsTableRec* rec = &g_fragTable[1];
    for (; rec < &g_fragTable[0x100]; ++rec) {
        FUN_0093a780_s006f_f170(io, &rec->mField38, 1, 0);
        FUN_0093a780_s006f_f170(io, &rec->mField3C, 1, 0);
        FUN_0093a6c0(io, &rec->mField41, 1);
        FUN_0093a6c0(io, &rec->mField42, 1);
        FUN_0093a6c0(io, &rec->mField40, 1);
        FUN_0093a780_s006f_f170(io, &rec->mField00, 1, 0);

        unsigned n1;
        if (FUN_0093a780_s006f_f170(io, &n1, 1, 0) != 0)
            ReadIntoEStr(io, rec->mName, n1);
        unsigned n2;
        if (FUN_0093a780_s006f_f170(io, &n2, 1, 0) != 0)
            ReadIntoEStr(io, rec->mUniform, n2);

        unsigned cnt;
        FUN_0093a780_s006f_f170(io, &cnt, 1, 0);
        ((void(__thiscall*)(void*, unsigned))FUN_006fc480)(&rec->mRegions, cnt);
        if ((int)cnt > 0) {
            unsigned k = cnt;
            CFragDeclBase* e = rec->mRegions.mpBegin;
            do {
                unsigned ln;
                if (FUN_0093a780_s006f_f170(io, &ln, 1, 0) != 0)
                    ReadIntoEStr(io, e->mName, ln);
                FUN_0093a700(io, &e->mField10, 1, 0);
                FUN_0093a700(io, &e->mField12, 1, 0);
                FUN_0093a700(io, &e->mField14, 1, 0);
                FUN_0093a700(io, &e->mField16, 1, 0);
                FUN_0093a780_s006f_f170(io, &e->mField18, 1, 0);
                ++e;
            } while (--k != 0);
        }

        if ((rec->mField00 & 2) != 0) {
            unsigned hl;
            FUN_0093a780_s006f_f170(io, &hl, 1, 0);
            TempString s;
            s.assignFill(hl);
            FUN_0093a6c0(io, s.mpBegin, (int)hl);
        }
    }
}

// @ 0x006ffa80
void VertexCtx::SubClip(float d)
{
    *(float*)((char*)this + 0x0c) -= d;
    *(float*)((char*)this + 0x34) -= d;
    *(float*)((char*)this + 0x5c) -= d;
    *(float*)((char*)this + 0x84) -= d;
    *(float*)((char*)this + 0xac) -= d;
    *(float*)((char*)this + 0xd4) -= d;
}
