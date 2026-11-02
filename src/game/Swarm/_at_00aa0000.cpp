// src/game/Swarm/_at_00aa0000.cpp -- migrated from slice(s) s00aa2f00, s00aa1f40, s00aa0030 by tools/migrate/rewrite.py
// Object file: Swarm/_at_00aa0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl op_new(int a, int b, int size);   // 0x11e073e
extern "C" void __cdecl operator_delete(void* p);          // ??3@YAXPAX@Z
extern "C" void __cdecl spherical_dir(const void* v, float* out1, float* out2);  // FUN_00a78fd0
extern "C" void __cdecl ins_vec(int begin, int end, int count);            // 0x11e0744
extern "C" void __cdecl build_tables(void* mgr, void* src, void* vec, void* out,
                                     void* p1fc, void* p214);              // 0x00a7fc10
extern "C" void* g_free_list;             // 0x1678fd8
extern "C" const float  g_axis_x[3];      // 0x1678f44
extern "C" const float  g_axis_y[3];      // 0x1678f48
extern "C" const float  g_one;            // 0x1485720
extern "C" const float  g_vec_a[3];       // 0x1678ef0
extern "C" const float  g_vec_b[3];       // 0x1678f20
extern "C" const float  g_minf;           // 0x13f0620
extern "C" const float  g_maxf;           // 0x1418f90
extern "C" const float  g_half;           // 0x1565420
extern "C" const double g_neg_one;        // 0x1454410

// ---- items of slice s00aa0030 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct GObj;
typedef void (__thiscall* VFn)(void*);
typedef void (__thiscall* VFnI)(void*, int);
typedef void (__thiscall* VFnVP)(void*, void*);
struct RefNode {
    RefNode* next;      // 0x00
    RefNode* prev;      // 0x04
};
struct Vec250   { void destroy(); void erase(void* a, void* b); };  // 0x4b5440 / 0x533500
struct SpVec    { void destroy(); void clear(int a, int b); };       // 0xa8c440 / 0xa8d020
struct ListHead { void destroy(); };                                 // 0x620230
struct BoolVec  { void resize(int n); };                             // 0x4c0410
struct PoolAlloc{ int add(void* a, uint b); };                       // 0x926650
struct MatDst   { void assign(const void* src); };                   // 0x41cb40
struct EffVec   { void push(void* p); };                             // 0xa7f430
extern "C" void* __cdecl op_new(int a, int b, int size);   // 0x11e073e
extern "C" void __cdecl operator_delete(void* p);          // ??3@YAXPAX@Z
extern "C" void __cdecl spherical_dir(const void* v, float* out1, float* out2);  // FUN_00a78fd0
extern "C" void __cdecl ins_vec(int begin, int end, int count);            // 0x11e0744
extern "C" void __cdecl build_tables(void* mgr, void* src, void* vec, void* out,
                                     void* p1fc, void* p214);              // 0x00a7fc10
struct TextSvc { void* find(int a, int b, int c); };      // FUN_00a71410
struct TextRef { int* assign(void* p); };                 // FUN_00b5f950
struct MsgSelf { void notify(void* m); };                 // FUN_00a9ef80
struct Quat { void to_matrix(void* dst, void* q); };      // FUN_004a9b40
struct IntVec { void insert(void* pos, void* val); };     // FUN_004558a0
struct XformMsg {                                         // ctor 0x434040, 0x40 bytes
    ushort flags;        // 0x00
    ushort seq;          // 0x02
    float  pos[3];       // 0x04
    int    pad0[3];      // 0x10
    float  mtx[9];       // 0x1c
    XformMsg();
};
extern "C" uchar g_alloc_pool[0x40];      // 0x1678fc8
extern "C" void* g_free_list;             // 0x1678fd8
extern "C" const float  g_axis_x[3];      // 0x1678f44
extern "C" const float  g_axis_y[3];      // 0x1678f48
extern "C" const float  g_one;            // 0x1485720
extern "C" const float  g_vec_a[3];       // 0x1678ef0
extern "C" const float  g_vec_b[3];       // 0x1678f20
extern "C" const float  g_minf;           // 0x13f0620
extern "C" const float  g_maxf;           // 0x1418f90
extern "C" const uchar  g_ident_mat[0x30]; // 0x1679010
extern "C" const float  g_half;           // 0x1565420
extern "C" const double g_neg_one;        // 0x1454410
struct GObj {
    // 0x000 vtable ptr
    // 0x004 vtable ptr (second base)
    // 0x008..0x023 scalars
    RefNode     head;       // 0x024 (next/prev), count at 0x02c

    GObj* ctor(int a, int b);
    void  dtor();
    void  compact();
    void  node_destroy(void* e);
    void  clear_list();
    void* pool_alloc();
    void  set_target(int t);
    void  bind_cfg(void* mgr);
    void  on_msg(void* m);
};
inline char* op(GObj* o, int off) { return (char*)o + off; }
template<class T> inline T& at(void* p, int off) { return *(T*)((char*)p + off); }
template<class T> inline T& at(int p, int off) { return *(T*)((char*)(long)p + off); }
inline char* op(int o, int off) { return (char*)(long)o + off; }
// ---- items of slice s00aa0030 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" uchar g_alloc_pool[0x40];      // 0x1678fc8
extern "C" const uchar  g_ident_mat[0x30]; // 0x1679010

// ---- items of slice s00aa1f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_eastlName[];                                                 // 0x013f2150 "EASTL"
extern const char g_eastlFile[];                                                 // 0x013ebb38 allocator.h
extern const float g_one;                                                              // 0x01485720 1.0f
extern float g_identityMatrix[9];                                                // 0x01679250
extern char g_vtbl_GmeIComponent[];                                               // 0x013f21d4
extern char g_vtbl_GmeRefCount[];                                                 // 0x013ef094
extern char g_vtbl_cModelEffect[];                                                // 0x01458ce8
extern char g_vtbl_cModelEffectRefCount[];                                        // 0x01458ce4
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
void* __cdecl EAAllocate(uint32_t size, const char* name, int flags, int align,
                         const char* file, int line);                            // 0x00f473a0
extern Vector3 g_defaultTranslation;                                             // 0x016791a4
struct cAnimationCurve;
struct sp_float_vector {
    float* mpBegin; float* mpEnd; float* mpCapacity; int mAllocator[2];
    void Allocate(int n, const int* alloc);                        // 0x004aa350
    sp_float_vector& operator=(const sp_float_vector& src);        // 0x0050d4e0
};
struct cAnimationCurveVector {
    cAnimationCurve* mpBegin;      // 0x00
    cAnimationCurve* mpEnd;        // 0x04
    cAnimationCurve* mpCapacity;   // 0x08
    int mAllocator[2];             // 0x0c
    void DoInsertValues(cAnimationCurve* position, uint32_t n, const cAnimationCurve& value); // 0x00aa1f40
    void resize(uint32_t n);                                                                  // 0x00aa2150
    void Erase(cAnimationCurve* first, cAnimationCurve* last);                                // 0x00aa1ef0
};
struct cAnimationCurve {                                   // size 0x28
    Vector2 mLengthRange;              // 0x00
    sp_float_vector mCurve;            // 0x08
    float mCurveVary;                  // 0x1c
    float mSpeedScale;                 // 0x20
    char mChannel;                     // 0x24
    char mMode;                        // 0x25
    cAnimationCurve() { mLengthRange.x = 0.0f; mLengthRange.y = 0.0f;
                        mCurve.mpBegin = 0; mCurve.mpEnd = 0; mCurve.mpCapacity = 0;
                        mCurveVary = 0.0f; mSpeedScale = 0.0f; mChannel = 0; mMode = 0; }
    cAnimationCurve(const cAnimationCurve& src) { CopyFrom(src); }
    cAnimationCurve* CopyFrom(const cAnimationCurve& src);     // 0x00aa1cc0
};
cAnimationCurve* __cdecl uninit_copy_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest);  // 0x00aa1d70
cAnimationCurve* __cdecl destroy_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest);      // 0x00aa1bf0
void __cdecl uninit_fill_n_curves(cAnimationCurve* first, uint32_t n, const cAnimationCurve* value);               // 0x00aa1ec0
cAnimationCurve* __cdecl copy_backward_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* destEnd); // 0x00aa1e60
void __cdecl fill_curves(cAnimationCurve* first, cAnimationCurve* last, const cAnimationCurve* value);             // 0x00aa1e10
cAnimationCurve** __cdecl uninit_copy_it_curves(cAnimationCurve** destSlot, cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest, cAnimationCurve* extra); // 0x00aa1d30
inline cAnimationCurve* uninitialized_move_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest)
{
    cAnimationCurve* d = uninit_copy_curves(first, last, dest);
    destroy_curves(first, last, dest);
    return d;
}
struct IOStream {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
    virtual void* Read(void* dst, int size);      // slot 12 (+0x30)
};
bool __cdecl ReadInt32(IOStream* is, void* dst, int count, int flag);   // 0x0093a780
bool __cdecl ReadInt64(IOStream* is, void* dst, int count, int flag);   // 0x0093a800
bool __cdecl ReadByte(IOStream* is, void* dst, int count);              // 0x0093a6c0
IOStream* __cdecl ReadFloatVector(IOStream* is, sp_float_vector* v); // 0x007d27d0
long double __cdecl RandomCurveLength(cAnimationCurve* curve);          // 0x007cdb90
struct cModelDescription {
    void* mpVtbl;                     // 0x00
    uint32_t mPad04;                  // 0x04
    uint32_t mFlags;                  // 0x08
    uint32_t mPad0c;                  // 0x0c
    union {
        struct { uint32_t mResourceIDLo; uint32_t mResourceIDHi; };
        unsigned long long mResourceID;
    };                                // 0x10
    float mSize;                      // 0x18
    Vector3 mColour;                  // 0x1c
    float mAlpha;                     // 0x28
    cAnimationCurveVector mAnimationCurves; // 0x2c
    union {
        struct { uint32_t mMaterialIDLo; uint32_t mMaterialIDHi; };
        unsigned long long mMaterialID;
    };                                // 0x40
    char mOverrideSet;                // 0x48
};
struct Matrix3 {
    float m[9];
    void* Assign(const void* src);                                 // 0x0041cb40
};
struct cTransform {
    unsigned short mFlags;             // 0x00
    unsigned short mModCount;          // 0x02
    Vector3 mTranslation;              // 0x04
    float mScale;                      // 0x10
    Matrix3 mRotation;                 // 0x14
    void PreTransformBy(const cTransform& src);                    // 0x00537f40
    void* Assign(const void* src);                                 // 0x00537dc0
};
struct cSPTransform_s00aa_1f40 : cTransform {
    cSPTransform_s00aa_1f40(const cTransform& src);                           // 0x00538000
};
struct cIRenderer {
    virtual void AddRef();                                                     // 0x00
    virtual void Release();                                                    // 0x04
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual cIRenderer* GetRenderer();                                         // 0x20 (slot 8)
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
    virtual bool BindModel(uint32_t lo, uint32_t hi, int* outID, float size);  // 0x40 (slot 16)
    virtual void ReleaseModel(int id);                                         // 0x44 (slot 17)
    virtual void SetVisible(int id, char visible);                             // 0x48 (slot 18)
    virtual void SetTransform(int id, const cTransform* xform);                // 0x4c (slot 19)
    virtual void SetColor(int id, const Vector3* colour, float alpha);         // 0x50 (slot 20)
    virtual void SetAnimParam(int id, int channel, float value);               // 0x54 (slot 21)
    virtual void SetOverride(int id, uint32_t lo, uint32_t hi);                // 0x58 (slot 22)
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
    virtual bool OverrideX(int a, int id, int b, int c, float* args);          // 0x74 (slot 29)
};
struct CRandom { double RandomDoubleUniform(); };                              // 0x009360d0
extern CRandom g_sRandom_Swarm;                                                // 0x016778dc
struct cEffectsWorld {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
    virtual cIRenderer* GetRenderer();                                         // slot 8 (+0x20)
};
struct cEffectParams {
    char pad[0x20];
    int mCounter;                      // 0x20
};
struct cLODScales { float v0; float v1; float v2; };
struct cLODScalesVector {
    cLODScales* mpBegin; cLODScales* mpEnd; cLODScales* mpCapacity; int mAllocator[2];
    void resize(uint32_t n);           // 0x00a6f010
};
struct cModelEffect {
    void* mpVtbl;                      // 0x00
    void* mpRefCountVtbl;              // 0x04
    int mRefCount;                     // 0x08
    cModelDescription* mDesc;          // 0x0c
    char mActive;                      // 0x10
    char mIsVisible;                   // 0x11
    char pad12[2];
    cIRenderer* mRenderer;             // 0x14
    int mModelID;                      // 0x18
    char mModelDirty;                  // 0x1c
    char pad1d[3];
    Vector3 mModelColor;               // 0x20
    float mModelAlpha;                 // 0x2c
    float mModelScale;                 // 0x30
    cTransform mComponentXform;        // 0x34
    Vector3 mLastLocation;             // 0x6c
    char mHasLOD;                      // 0x78
    char pad79[3];
    Vector2 mLODSizeScale;             // 0x7c
    Vector2 mLODAlphaScale;            // 0x84
    cLODScalesVector mAnimationInfo;   // 0x8c
    union {
        struct { uint32_t mModelOverrideLo; uint32_t mModelOverrideHi; };
        long long mModelOverride;
    };                                 // 0xa0

    void Init(cEffectsWorld* world, int unused2, int unused3);              // 0x00aa23a0
    void Shutdown();                                                       // 0x00aa2470
    void Stop(int unused);                                                 // 0x00aa24b0
    bool SetIntParams(int flag, int* args, int nargs);                     // 0x00aa24e0
    bool SetFloatParams(int param, float* args, int unused);               // 0x00aa25f0
    void SetIsVisible(char visible);                                       // 0x00aa2800
    void ApplyEffect(float dt, float lerp, cEffectParams* params);         // 0x00aa2840
    cModelEffect(cModelDescription* desc);                                 // 0x00aa2b60
    void* Destroy(uint32_t flags);                                         // 0x00aa2c60
    void SetTransforms(const cTransform& parent, const cTransform& src);   // 0x00aa2cc0
    void Start(int unused);                                                // 0x00aa2d80
};
inline void CallVirtualStop(cModelEffect* self, int x)
{
    typedef void (__thiscall* Fn)(cModelEffect*, int);
    Fn fn = (Fn)(*(void***)self)[3];
    fn(self, x);
}
// ---- items of slice s00aa1f40 end

// @ 0x00aa0030
GObj* GObj::ctor(int a, int b)
{
    at<int>(this, 4) = (int)0x13ef094;
    at<int>(this, 8) = 0;
    at<int>(this, 0xc) = a;
    at<int>(this, 0x10) = b;
    at<int>(this, 0) = (int)0x1458c3c;
    at<int>(this, 4) = (int)0x1458c38;
    at<int>(this, 0x14) = 0;
    at<int>(this, 0x18) = 0;
    at<int>(this, 0x1c) = 0;
    at<uchar>(this, 0x20) = 0;
    at<uchar>(this, 0x21) = 0;
    at<uchar>(this, 0x22) = 1;
    *(int*)op(this, 0x28) = (int)op(this, 0x24);
    *(int*)op(this, 0x24) = (int)op(this, 0x24);
    at<int>(this, 0x2c) = 0;
    at<ushort>(this, 0x30) = 0;
    at<ushort>(this, 0x32) = 0;
    at<float>(this, 0x34) = g_axis_x[0];
    at<float>(this, 0x38) = g_axis_y[0];
    at<float>(this, 0x3c) = g_axis_x[2];
    at<float>(this, 0x40) = g_one;
    ((MatDst*)op(this, 0x44))->assign(g_ident_mat);
    at<ushort>(this, 0x68) = 0;
    at<ushort>(this, 0x6a) = 0;
    at<float>(this, 0x6c) = g_axis_x[0];
    at<float>(this, 0x70) = g_axis_y[0];
    at<float>(this, 0x74) = g_axis_x[2];
    at<float>(this, 0x78) = g_one;
    ((MatDst*)op(this, 0x7c))->assign(g_ident_mat);
    at<double>(this, 0xa0) = 0.0;
    at<double>(this, 0xb0) = 0.0;
    at<uchar>(this, 0xa8) = 0;
    at<int>(this, 0xb8) = 0;
    at<double>(this, 0xc0) = g_neg_one;
    at<float>(this, 0xc8) = 0.0f;
    at<float>(this, 0xcc) = g_axis_x[0];
    at<float>(this, 0xd0) = g_axis_y[0];
    at<float>(this, 0xd4) = g_axis_x[2];
    at<uchar>(this, 0x108) = 0;
    at<float>(this, 0x10c) = 0.0f;
    at<float>(this, 0x110) = 0.0f;
    at<float>(this, 0x114) = g_axis_x[0];
    at<float>(this, 0x118) = g_axis_y[0];
    at<float>(this, 0x11c) = g_axis_x[2];
    at<float>(this, 0x120) = 0.0f;
    at<int>(this, 0x124) = 1;
    at<int>(this, 0x128) = 1;
    at<float>(this, 0x12c) = 0.0f;
    at<float>(this, 0x130) = g_axis_x[0];
    at<float>(this, 0x134) = g_axis_y[0];
    at<float>(this, 0x138) = g_axis_x[2];
    at<float>(this, 0x13c) = g_one;
    at<float>(this, 0x140) = g_one;
    at<float>(this, 0x144) = g_one;
    at<float>(this, 0x148) = g_one;
    at<float>(this, 0x14c) = g_one;
    at<float>(this, 0x150) = g_vec_a[0];
    at<float>(this, 0x154) = g_vec_a[1];
    at<float>(this, 0x158) = g_vec_a[2];
    at<float>(this, 0x15c) = g_maxf;
    at<float>(this, 0x160) = g_minf;
    at<float>(this, 0x164) = g_vec_b[0];
    at<float>(this, 0x168) = g_vec_b[1];
    at<float>(this, 0x16c) = g_vec_b[0];
    at<float>(this, 0x170) = g_vec_b[1];
    at<float>(this, 0x174) = g_vec_b[0];
    at<float>(this, 0x178) = g_vec_b[1];
    at<float>(this, 0x17c) = g_one;
    at<float>(this, 0x180) = g_one;
    at<float>(this, 0x184) = g_one;
    at<float>(this, 0x188) = g_vec_a[0];
    at<float>(this, 0x18c) = g_vec_a[1];
    at<int>(this, 0x194) = 0;
    at<int>(this, 0x198) = 0;
    at<int>(this, 0x19c) = 0;
    at<float>(this, 0x190) = g_vec_a[2];
    at<uchar>(this, 0x1a0) = 0;
    at<uchar>(this, 0x1a1) = 0;
    at<uchar>(this, 0x1a2) = 0;
    at<float>(this, 0x1a4) = g_half;
    at<float>(this, 0x1a8) = g_half;
    at<float>(this, 0x1ac) = g_half;
    at<float>(this, 0x1b0) = -g_half;
    at<float>(this, 0x1b4) = -g_half;
    at<float>(this, 0x1b8) = -g_half;
    at<int>(this, 0x1bc) = 0;
    at<int>(this, 0x1c0) = 0;
    at<int>(this, 0x1c4) = 0;
    at<uchar>(this, 0x1d0) = 0;
    at<int>(this, 0x1d4) = 0;
    at<int>(this, 0x1d8) = 0;
    at<int>(this, 0x1dc) = 0;
    at<int>(this, 0x1e8) = 0;
    at<int>(this, 0x1ec) = 0;
    at<int>(this, 0x1f0) = 0;
    at<int>(this, 0x1fc) = 0;
    at<int>(this, 0x200) = 0;
    at<int>(this, 0x204) = 0;
    at<int>(this, 0x208) = 0;
    at<uchar>(this, 0x214) = 0;
    at<int>(this, 0x218) = 0;
    at<int>(this, 0x21c) = 0;
    at<int>(this, 0x220) = 0;
    at<uchar>(this, 0x22c) = 0;
    at<int>(this, 0x230) = 0;
    at<int>(this, 0x234) = -1;
    at<int>(this, 0x238) = -1;
    at<int>(this, 0x23c) = -1;
    at<int>(this, 0x240) = -1;
    at<int>(this, 0x244) = -1;
    at<int>(this, 0x248) = 0;
    at<uchar>(this, 0x24c) = 0;
    at<int>(this, 0x250) = 0;
    at<int>(this, 0x254) = 0;
    at<int>(this, 0x258) = 0;
    return this;
}

// @ 0x00aa04a0
void GObj::dtor()
{
    at<int>(this, 0) = (int)0x1458c3c;
    at<int>(this, 4) = (int)0x1458c38;
    ((Vec250*)op(this, 0x250))->destroy();
    void* p;
    p = at<void*>(this, 0x248);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[0x38 / 4])(p);
    p = at<void*>(this, 0x230);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    p = at<void*>(this, 0x218);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    p = at<void*>(this, 0x200);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    p = at<void*>(this, 0x1e8);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    p = at<void*>(this, 0x1d4);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    ((SpVec*)op(this, 0x1bc))->destroy();
    p = at<void*>(this, 0x19c);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    p = at<void*>(this, 0x198);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    p = at<void*>(this, 0x194);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    ((ListHead*)op(this, 0x24))->destroy();
    at<int>(this, 0) = (int)0x13f21d4;
    at<int>(this, 4) = (int)0x13ef094;
}

// @ 0x00aa0600
void GObj::compact()
{
    int* vec = (int*)op(this, 0x250);
    unsigned i = 0;
    unsigned j = 0;

    if (((vec[1] - vec[0]) >> 2) != 0) {
        do {
            void* e = ((void**)vec[0])[i];
            if (((uchar (__thiscall*)(void*))((void**)*(void**)e)[0x10 / 4])(e)) {
                if (i > j) {
                    void* a = ((void**)vec[0])[i];
                    void* b = ((void**)vec[0])[j];
                    if (a != b) {
                        if (a != 0)
                            ((VFn)((void**)*(void**)a)[0 / 4])(a);
                        ((void**)vec[0])[j] = a;
                        if (b != 0)
                            ((VFn)((void**)*(void**)b)[4 / 4])(b);
                    }
                }
                j++;
            }
            i++;
        } while (i < (unsigned)((vec[1] - vec[0]) >> 2));
    }
    ((Vec250*)vec)->erase((void*)((int*)vec[0] + j), (void*)vec[1]);
}

// @ 0x00aa06b0
void GObj::on_msg(void* msg)
{
    int* m = (int*)msg;
    int* comp = (int*)at<int>(this, 0x248);

    if (comp != 0 && at<int>(comp, 0xc) != 0) {
        uint fl = *(uint*)(at<int>(this, 0xc) + 0xc);
        if ((fl >> 6 & 1) != 0 ||
            (uint)(fl >> 7 & 1) != (uint)(at<float>(m, 8) >= at<float>(m, 0xc))) {
            ((MsgSelf*)this)->notify(m);
            goto done;
        }
    }
    if (at<int>(m, 0x7c) != 0) {
        void* sp = (void*)at<int>(m, 0x7c);
        ((VFnI)((void**)*(void**)sp)[0xc / 4])(sp, at<int>(this, 0x128));
        if (*(int*)(at<int>(this, 0xc) + 0x12c) == 0) {
            if (at<int>(this, 0x128) == 0 &&
                ((uchar (__thiscall*)(void*))((void**)*(void**)sp)[0x10 / 4])(sp)) {
                void* tmp = (void*)((int*)sp - 1);
                if (tmp != 0)
                    ((VFn)((void**)*(void**)tmp)[0 / 4])(tmp);
                ((EffVec*)op(this, 0x250))->push(&tmp);
                if (tmp != 0)
                    ((VFn)((void**)*(void**)tmp)[4 / 4])(tmp);
            }
        } else {
            ((VFn)((void**)*(void**)sp)[4 / 4])(sp);
        }
        sp = (void*)at<int>(m, 0x7c);
        if (sp != 0) {
            at<int>(m, 0x7c) = 0;
            ((VFn)((void**)*(void**)sp)[0x38 / 4])(sp);
        }
    }

    int local = 0;
    int idx = *(int*)(at<int>(this, 0xc) + 0x130);
    if (idx >= 0 && at<int>(this, 0x128) == 0 && at<uchar>(this, 0x22) != 0) {
        void* txt = ((TextSvc*)at<void*>(this, 0x14))->find(idx, at<int>(this, 0x10),
                                                           at<int>(this, 0x1c));
        int* arc = ((TextRef*)&local)->assign(txt);
        if (arc[0] != 0) {
            XformMsg xf;
            xf.flags |= 4;
            xf.seq++;
            xf.pos[0] = at<float>(m, 0x10);
            xf.pos[1] = at<float>(m, 0x14);
            xf.pos[2] = at<float>(m, 0x18);
            if ((*(uint*)(at<int>(this, 0xc) + 0xc) >> 2 & 1) != 0) {
                float mt[9];
                ((Quat*)((char*)m + 0x80))->to_matrix(mt, (char*)m + 0x80);
                for (int k = 0; k < 9; k++)
                    xf.mtx[k] = mt[k];
                xf.flags |= 2;
                xf.seq++;
            }
            void* txtobj = (void*)arc[0];
            ((VFnVP)((void**)*(void**)txtobj)[0x14 / 4])(txtobj, op(this, 0x68));
            if ((*(uint*)(at<int>(this, 0xc) + 0xc) >> 5 & 1) == 0 || at<int>(m, 0x7c) == 0) {
                ((VFnVP)((void**)*(void**)txtobj)[0x18 / 4])(txtobj, &xf);
            } else {
                XformMsg xf2;
                void* blk = (void*)((int*)at<int>(m, 0x7c) - 1);
                ((VFnVP)((void**)*(void**)blk)[0x20 / 4])(blk, &xf2);
                ((VFnVP)((void**)*(void**)txtobj)[0x18 / 4])(txtobj, &xf2);
            }
            if (at<uchar>(this, 0x22c) != 0)
                ((void (__thiscall*)(void*, int, int))
                 ((void**)*(void**)txtobj)[0x4c / 4])(txtobj, 0, at<int>(this, 0x230));
            ((VFnI)((void**)*(void**)txtobj)[0x30 / 4])(txtobj, at<uchar>(this, 0x22) == 0);
            ((VFnI)((void**)*(void**)txtobj)[8 / 4])(txtobj, 0);
            ((EffVec*)op(this, 0x250))->push(&local);
        }
    }

    if (at<int>(this, 0x1fc) != 0) {
        int i = at<int>(m, 0x24);
        int* p = (int*)at<int>(this, 0x1bc);
        int base = at<int>(this, 0x1e8);
        while (p != (int*)at<int>(this, 0x1c0)) {
            if (p[4] != 0)
                ((VFnI)((void**)*(void**)p[0])[0x30 / 4])((void*)p[0],
                                                           p[5] + i * at<int>(this, 0x1fc) + base);
            p += 6;
        }
        int* dst = (int*)at<int>(this, 0x204);
        if (dst < (int*)at<int>(this, 0x208)) {
            at<int>(this, 0x204) = (int)(dst + 1);
            if (dst != 0)
                *dst = at<int>(m, 0x24);
        } else {
            ((IntVec*)op(this, 0x200))->insert(dst, (char*)m + 0x90);
        }
    }
    m[0] = *(int*)&g_free_list;
    g_free_list = m;
    if (local != 0)
        ((VFn)((void**)*(void**)local)[4 / 4])((void*)local);

done:
    if (at<int>(this, 0x248) != 0 && at<int>(this, 0x2c) == 0 &&
        at<uchar>(this, 0x21) != 0)
        ((VFnI)((void**)*(void**)at<int>(this, 0x248))[0xc / 4])((void*)at<int>(this, 0x248), 0);
}

// @ 0x00aa09e0
void* GObj::pool_alloc()
{
    void* p;
    uchar ok;

    p = g_free_list;
    while (p == 0) {
        ok = (uchar)((PoolAlloc*)g_alloc_pool)->add(0, 0);
        if (!ok)
            break;
        p = g_free_list;
    }
    if (p != 0)
        g_free_list = *(void**)p;
    void* obj = op_new((int)p, 0, 0xa0);
    if (at<int>(this, 0x1fc) != 0) {
        if (at<int>(this, 0x200) != at<int>(this, 0x204)) {
            at<int>(obj, 0x90) = *(int*)(at<int>(this, 0x204) - 4);
            at<int>(this, 0x204) -= 4;
            return obj;
        }
        at<int>(obj, 0x90) = (at<int>(this, 0x1ec) - at<int>(this, 0x1e8)) / at<int>(this, 0x1fc);
        ((BoolVec*)op(this, 0x1e8))->resize(
            (at<int>(this, 0x1ec) - at<int>(this, 0x1e8)) + at<int>(this, 0x1fc));
    }
    return obj;
}

// @ 0x00aa0a90
void GObj::clear_list()
{
    RefNode* head = (RefNode*)op(this, 0x24);
    RefNode* p = head->next;

    while (p != head) {
        RefNode* prev = p->prev;
        RefNode* next = p->next;
        prev->next = next;
        next->prev = prev;
        p->next = 0;
        p->prev = 0;
        node_destroy(p);
        at<int>(this, 0x2c)--;
        p = next;
    }
    RefNode* q = head->next;
    while (q != head) {
        RefNode* next = q->next;
        q->prev = 0;
        q->next = 0;
        q = next;
    }
    head->next = head;
    head->prev = head;
}

// @ 0x00aa0b00
void GObj::set_target(int t)
{
    if (at<uchar>(this, 0x20) != 0) {
        void* c = at<void*>(this, 0x248);
        if (c != 0 && at<int>(this, 0x2c) == 0)
            ((VFnI)((void**)*(void**)c)[0xc / 4])(c, t);
        uchar zero = (uchar)(t == 0);
        at<int>(this, 0x128) = t;
        at<uchar>(this, 0x21) = zero;
        if (!zero) {
            at<uchar>(this, 0x20) = zero;
            clear_list();
            unsigned i = 0;
            if (((at<int>(this, 0x254) - at<int>(this, 0x250)) >> 2) != 0) {
                do {
                    void* e = ((void**)at<int>(this, 0x250))[i];
                    if (((uchar (__thiscall*)(void*))((void**)*(void**)e)[0x10 / 4])(e)) {
                        void* e2 = ((void**)at<int>(this, 0x250))[i];
                        ((VFnI)((void**)*(void**)e2)[0xc / 4])(e2, t);
                    }
                    i++;
                } while (i < (unsigned)((at<int>(this, 0x254) - at<int>(this, 0x250)) >> 2));
            }
            ((Vec250*)op(this, 0x250))->erase((void*)at<int>(this, 0x250), (void*)at<int>(this, 0x254));
        }
    }
}

// @ 0x00aa0ba0
void GObj::bind_cfg(void* mgr)
{
    int cfg = at<int>(this, 0xc);
    float* pf = (float*)((char*)cfg + 0x7c);
    float tiny = 1e-06f;

    if (!(at<float>(cfg, 0x7c) > 1e-06f))
        pf = &tiny;
    at<double>(this, 0xc0) = 1.0 / (double)*pf;
    at<int>(this, 0x1b0) = at<int>(cfg, 0x58);
    at<int>(this, 0x1b4) = at<int>(cfg, 0x5c);
    at<int>(this, 0x1b8) = at<int>(cfg, 0x60);
    at<int>(this, 0x1a4) = at<int>(cfg, 0x4c);
    at<int>(this, 0x1a8) = at<int>(cfg, 0x50);
    at<int>(this, 0x1ac) = at<int>(cfg, 0x54);
    cfg = at<int>(this, 0xc);
    uchar diff = (uchar)(at<float>(cfg, 0x268) != g_axis_x[0] ||
                         at<float>(cfg, 0x26c) != g_axis_y[0] ||
                         at<float>(cfg, 0x270) != g_axis_x[2]);
    at<uchar>(this, 0x108) = diff;
    if (diff)
        spherical_dir(op(cfg, 0x268), (float*)op(this, 0x10c), (float*)op(this, 0x110));

    for (int k = 0; k < 3; k++) {
        int offs[3] = { 0x1e8, 0x1f0, 0x1f8 };
        int dst[3] = { 0x194, 0x198, 0x19c };
        int cfgo = at<int>(this, 0xc);
        uint a = at<uint>(cfgo, offs[k]);
        uint b = at<uint>(cfgo, offs[k] + 4);
        if ((a & b) != 0xffffffffu) {
            void* np = ((void* (__thiscall*)(void*, uint, uint))
                        ((void**)*(void**)mgr)[0x8c / 4])(mgr, a, b);
            void* old = at<void*>(this, dst[k]);
            if (np != old) {
                if (np != 0)
                    ((VFn)((void**)*(void**)np)[0 / 4])(np);
                at<void*>(this, dst[k]) = np;
                if (old != 0)
                    ((VFn)((void**)*(void**)old)[4 / 4])(old);
            }
        }
    }

    cfg = at<int>(this, 0xc);
    at<int>(this, 0x15c) = at<int>(cfg, 0x1e0);
    at<int>(this, 0x160) = at<int>(cfg, 0x1e4);
    for (int k = 0; k < 3; k++) {
        int dst[3] = { 0x194, 0x198, 0x19c };
        void* p = at<void*>(this, dst[k]);
        if (p != 0) {
            ((VFn)((void**)*(void**)p)[8 / 4])(p);
            at<uchar>(this, 0x1a0 + k) =
                ((uchar (__thiscall*)(void*))((void**)*(void**)p)[0x1c / 4])(p);
        }
    }
    ((SpVec*)op(this, 0x1bc))->clear(at<int>(this, 0x1bc), at<int>(this, 0x1c0));

    int e0 = at<int>(this, 0x1d4);
    int b0 = at<int>(this, 0x1d8);
    ins_vec(e0, b0, 0);
    at<int>(this, 0x1d8) += (e0 - b0);

    at<int>(this, 0x1fc) = 0;

    int e1 = at<int>(this, 0x1e8);
    int b1 = at<int>(this, 0x1ec);
    ins_vec(e1, b1, 0);
    at<int>(this, 0x1ec) += (e1 - b1);

    cfg = at<int>(this, 0xc);
    at<uchar>(this, 0x214) = 0;
    if (at<int>(cfg, 0x1b0) != at<int>(cfg, 0x1b4)) {
        float n = 0.0f;
        at<int>(this, 0x1fc) = 0;
        build_tables(mgr, op(cfg, 0x1b0), op(this, 0x1bc), &n,
                     op(this, 0x1fc), op(this, 0x214));
        at<uchar>(this, 0x1d0) = 0;
        ((BoolVec*)op(this, 0x1d4))->resize(*(int*)&n);
    }
}

// @ 0x00aa1f40
void cAnimationCurveVector::DoInsertValues(cAnimationCurve* position, uint32_t n, const cAnimationCurve& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const cAnimationCurve temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            cAnimationCurve* const pEnd = mpEnd;
            if (n < nExtra) {
                cAnimationCurve* newEnd;
                uninit_copy_it_curves(&newEnd, mpEnd - n, mpEnd, mpEnd, position);
                mpEnd += n;
                copy_backward_curves(position, pEnd - n, pEnd);
                fill_curves(position, position + n, &temp);
            } else {
                uninit_fill_n_curves(mpEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                uninit_copy_curves(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill_curves(position, pEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        cAnimationCurve* const pNewData = (cAnimationCurve*)EAAllocate(nNewSize * 0x28, g_eastlName, 0, 0, g_eastlFile, 0xd1);
        cAnimationCurve* pNewEnd = uninitialized_move_curves(mpBegin, position, pNewData);
        uninit_fill_n_curves(pNewEnd, n, &value);
        pNewEnd = uninitialized_move_curves(position, mpEnd, pNewEnd + n);
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            operator_delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00aa2150
void cAnimationCurveVector::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        cAnimationCurve temp;
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), temp);
        if (temp.mCurve.mpBegin != 0 && *(int*)((char*)temp.mCurve.mpBegin - 4) != 0)
            operator_delete(temp.mCurve.mpBegin);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00aa2210
IOStream* __cdecl ReadAnimationCurves(IOStream* is, cAnimationCurveVector* curves)
{
    uint32_t count;
    ReadInt32(is, &count, 1, 0);
    curves->resize(count);
    for (uint32_t i = 0; i < count; ++i) {
        cAnimationCurve* c = curves->mpBegin + i;
        is->Read(&c->mLengthRange, 8);
        ReadFloatVector(is, &c->mCurve);
        ReadInt32(is, &c->mCurveVary, 1, 0);
        ReadInt32(is, &c->mSpeedScale, 1, 0);
        ReadByte(is, &c->mChannel, 1);
        ReadByte(is, &c->mMode, 1);
    }
    return is;
}

// @ 0x00aa22b0
void __cdecl ReadModelDescription(IOStream* is, int unused, cModelDescription* desc)
{
    int flags;
    ReadInt32(is, &flags, 1, 0);
    desc->mFlags = (uint32_t)flags & 3;
    ReadInt64(is, &desc->mResourceIDLo, 1, 0);
    ReadInt32(is, &desc->mSize, 1, 0);
    is->Read(&desc->mColour, 0xc);
    ReadInt32(is, &desc->mAlpha, 1, 0);
    ReadAnimationCurves(is, &desc->mAnimationCurves);
    ReadInt64(is, &desc->mMaterialIDLo, 1, 0);
    ReadByte(is, &desc->mOverrideSet, 1);
}

// @ 0x00aa2340
int __cdecl CollectModelRefs(int unused, cModelDescription* desc, uint32_t* out, int maxCount)
{
    int count = 0;
    unsigned long long resID = desc->mResourceID;
    if (resID != 0xffffffffffffffffull) {
        count = 1;
        if (maxCount > 0) {
            *(unsigned long long*)out = resID;
            out[2] = 2;
            out += 4;
            maxCount--;
        }
    }
    unsigned long long matID = desc->mMaterialID;
    if (matID != 0xffffffffffffffffull) {
        count++;
        if (maxCount > 0) {
            *(unsigned long long*)out = matID;
            out[2] = 1;
        }
    }
    return count;
}

// @ 0x00aa23a0
void cModelEffect::Init(cEffectsWorld* world, int unused2, int unused3)
{
    cIRenderer* r = world->GetRenderer();
    if (r != mRenderer) {
        if (r != 0)
            r->AddRef();
        cIRenderer* old = mRenderer;
        mRenderer = r;
        if (old != 0)
            old->Release();
    }
    cModelDescription* d = mDesc;
    mModelColor = d->mColour;
    mModelAlpha = d->mAlpha;
    if (mRenderer != 0) {
        if (mRenderer->BindModel(d->mResourceIDLo, d->mResourceIDHi, &mModelID, d->mSize)) {
            mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
            if (d->mMaterialID != 0xffffffffffffffffull)
                mRenderer->SetOverride(mModelID, d->mMaterialIDLo, d->mMaterialIDHi);
        } else {
            cIRenderer* old = mRenderer;
            mRenderer = 0;
            old->Release();
        }
    }
}

// @ 0x00aa2470
void cModelEffect::Shutdown()
{
    if (mRenderer != 0) {
        if (mModelID >= 0)
            mRenderer->ReleaseModel(mModelID);
        if (mRenderer != 0) {
            cIRenderer* old = mRenderer;
            mRenderer = 0;
            old->Release();
        }
    }
}

// @ 0x00aa24b0
void cModelEffect::Stop(int unused)
{
    if (mActive) {
        mActive = 0;
        if (mRenderer != 0)
            mRenderer->SetVisible(mModelID, 0);
    }
}

// @ 0x00aa24e0
bool cModelEffect::SetIntParams(int flag, int* args, int nargs)
{
    if (flag != 0)
        return false;
    if (nargs >= 2 && (uint32_t)args[1] != (uint32_t)(unsigned char)mDesc->mOverrideSet)
        return true;
    int id = args[0];
    if (mModelOverride != (long long)id) {
        mModelOverrideLo = (uint32_t)id;
        mModelOverrideHi = 0;
        if (mRenderer != 0) {
            if (mModelID >= 0)
                mRenderer->ReleaseModel(mModelID);
            if (mRenderer->BindModel(mModelOverrideLo, mModelOverrideHi, &mModelID, mDesc->mSize)) {
                mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
                mRenderer->SetVisible(mModelID, mIsVisible);
                mRenderer->SetTransform(mModelID, &mComponentXform);
                unsigned long long matID = mDesc->mMaterialID;
                if (matID != 0xffffffffffffffffull)
                    mRenderer->SetOverride(mModelID, (uint32_t)matID, (uint32_t)(matID >> 32));
            } else {
                mModelID = -1;
            }
        }
    }
    return true;
}

// @ 0x00aa25f0
bool cModelEffect::SetFloatParams(int param, float* args, int unused)
{
    if (param == 4) {
        mModelAlpha = mDesc->mAlpha * args[0];
        mModelDirty = 1;
        return true;
    }
    if (param == 5) {
        mModelColor.x = mDesc->mColour.x * args[0];
        mModelColor.y = mDesc->mColour.y * args[1];
        mModelColor.z = mDesc->mColour.z * args[2];
        mModelDirty = 1;
        return true;
    }
    if (param == 1) {
        if (mRenderer != 0) {
            if (mModelID >= 0)
                mRenderer->ReleaseModel(mModelID);
            if (mRenderer->BindModel(mDesc->mResourceIDLo, mDesc->mResourceIDHi, &mModelID, mDesc->mSize * args[0])) {
                mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
                mRenderer->SetVisible(mModelID, mIsVisible);
                mRenderer->SetTransform(mModelID, &mComponentXform);
                if (mDesc->mMaterialID != 0xffffffffffffffffull)
                    mRenderer->SetOverride(mModelID, mDesc->mMaterialIDLo, mDesc->mMaterialIDHi);
            } else {
                mModelID = -1;
            }
        }
        return false;
    }
    if (param == 0xe) {
        if (mModelID >= 0)
            return mRenderer->OverrideX(2, mModelID, 0, unused, args);
        return false;
    }
    if (param == 0x101) {
        mLODSizeScale.x = args[1];
        mLODAlphaScale.x = args[2];
        mLODSizeScale.y = args[4];
        mLODAlphaScale.y = args[5];
        if (mLODAlphaScale.x == 1.0f && mLODAlphaScale.y == 1.0f &&
            mLODSizeScale.x == 1.0f && mLODSizeScale.y == 1.0f) {
            mHasLOD = 0;
            mModelDirty = 1;
            return true;
        }
        mHasLOD = 1;
        mModelDirty = 1;
        return true;
    }
    return false;
}

// @ 0x00aa2800
void cModelEffect::SetIsVisible(char visible)
{
    mIsVisible = visible;
    if (mActive && mRenderer != 0)
        mRenderer->SetVisible(mModelID, visible);
}

// @ 0x00aa2840
void cModelEffect::ApplyEffect(float dt, float lerp, cEffectParams* params)
{
    if (mRenderer == 0)
        return;
    if (mHasLOD) {
        if (mLODSizeScale.x != mLODSizeScale.y || mModelDirty) {
            cSPTransform_s00aa_1f40 xform(mComponentXform);
            xform.mFlags |= 1;
            xform.mModCount++;
            xform.mScale = ((mLODSizeScale.y - mLODSizeScale.x) * lerp + mLODSizeScale.x) * xform.mScale;
            mRenderer->SetTransform(mModelID, &xform);
        }
        mRenderer->SetColor(mModelID, &mModelColor,
                            ((mLODAlphaScale.y - mLODAlphaScale.x) * lerp + mLODAlphaScale.x) * mModelAlpha);
    } else {
        if (mModelDirty) {
            mRenderer->SetTransform(mModelID, &mComponentXform);
            mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
        } else {
            goto anims;
        }
    }
    mModelDirty = 0;

anims:
    if (mAnimationInfo.mpBegin != mAnimationInfo.mpEnd) {
        float dx = mLastLocation.x - mComponentXform.mTranslation.x;
        float dy = mLastLocation.y - mComponentXform.mTranslation.y;
        float dz = mLastLocation.z - mComponentXform.mTranslation.z;
        float dist = (float)(sqrt((double)dx * dx + (double)dy * dy + (double)dz * dz) / (double)mComponentXform.mScale);
        uint32_t n = (uint32_t)(mAnimationInfo.mpEnd - mAnimationInfo.mpBegin);
        for (uint32_t i = 0; i < n; ++i) {
            cLODScales* info = mAnimationInfo.mpBegin + i;
            cAnimationCurve* curve = mDesc->mAnimationCurves.mpBegin + i;
            float step = dt;
            if (curve->mSpeedScale > 0.0f)
                step = curve->mSpeedScale * dist;
            float v = step * info->v1 + info->v0;
            info->v0 = v;
            if (v > 1.0f) {
                if (curve->mMode == 1) {
                    info->v0 = 1.0f;
                } else if (curve->mMode == 2) {
                    CallVirtualStop(this, 0);
                    return;
                } else {
                    info->v0 = 0.0f;
                    long double r = RandomCurveLength(curve);
                    if (r <= 0.0)
                        info->v1 = 0.0f;
                    else
                        info->v1 = 1.0f / (float)r;
                }
            }
            float sample;
            int nseg = (int)(curve->mCurve.mpEnd - curve->mCurve.mpBegin) - 1;
            if (nseg == 0) {
                sample = curve->mCurve.mpBegin[0];
            } else {
                float u = (float)nseg * info->v0;
                int idx = (int)u;
                float frac = u - (float)idx;
                if (frac <= 0.0f)
                    sample = curve->mCurve.mpBegin[idx];
                else
                    sample = (curve->mCurve.mpBegin[idx + 1] - curve->mCurve.mpBegin[idx]) * frac + curve->mCurve.mpBegin[idx];
            }
            mRenderer->SetAnimParam(mModelID, (int)curve->mChannel, info->v2 * sample);
        }
        mLastLocation = mComponentXform.mTranslation;
    }
    params->mCounter++;
}

// @ 0x00aa2b60
cModelEffect::cModelEffect(cModelDescription* desc)
{
    float one = g_one;
    mpRefCountVtbl = g_vtbl_GmeRefCount;
    mRefCount = 0;
    mpVtbl = g_vtbl_cModelEffect;
    mpRefCountVtbl = g_vtbl_cModelEffectRefCount;
    mDesc = desc;
    mActive = 0;
    mIsVisible = 1;
    mRenderer = 0;
    mModelID = -1;
    mModelDirty = 0;
    mModelColor.x = one; mModelColor.y = one; mModelColor.z = one;
    mModelAlpha = one;
    mModelScale = one;
    mComponentXform.mFlags = 0;
    mComponentXform.mModCount = 0;
    mComponentXform.mTranslation.x = g_defaultTranslation.x;
    mComponentXform.mTranslation.y = g_defaultTranslation.y;
    mComponentXform.mTranslation.z = g_defaultTranslation.z;
    mComponentXform.mScale = one;
    mComponentXform.mRotation.Assign(g_identityMatrix);
    mHasLOD = 0;
    float one2 = g_one;
    mLODSizeScale.x = one2; mLODSizeScale.y = one2;
    mAnimationInfo.mpBegin = 0; mAnimationInfo.mpEnd = 0; mAnimationInfo.mpCapacity = 0;
    mLODAlphaScale.x = one2; mLODAlphaScale.y = one2;
    mModelOverrideLo = 0xffffffffu;
    mModelOverrideHi = 0xffffffffu;
}

// @ 0x00aa2c60
void* cModelEffect::Destroy(uint32_t flags)
{
    mpVtbl = g_vtbl_cModelEffect;
    mpRefCountVtbl = g_vtbl_cModelEffectRefCount;
    _ReadWriteBarrier();
    if (mAnimationInfo.mpBegin != 0 && *(int*)((char*)mAnimationInfo.mpBegin - 4) != 0)
        operator_delete(mAnimationInfo.mpBegin);
    if (mRenderer != 0)
        mRenderer->Release();
    _ReadWriteBarrier();
    mpVtbl = g_vtbl_GmeIComponent;
    mpRefCountVtbl = g_vtbl_GmeRefCount;
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00aa2cc0
void cModelEffect::SetTransforms(const cTransform& parent, const cTransform& src)
{
    cTransform tmp;
    tmp.mFlags = src.mFlags;
    tmp.mModCount = src.mModCount;
    tmp.mTranslation.x = src.mTranslation.x;
    tmp.mTranslation.y = src.mTranslation.y;
    tmp.mTranslation.z = src.mTranslation.z;
    tmp.mScale = src.mScale;
    tmp.mRotation.Assign(src.mRotation.m);
    tmp.PreTransformBy(parent);
    mComponentXform.Assign(&tmp);
    cIRenderer* r = mRenderer;
    if (r != 0)
        r->SetTransform(mModelID, &mComponentXform);
}

// @ 0x00aa2d80
void cModelEffect::Start(int unused)
{
    if (mActive)
        return;
    mActive = 1;
    int n = (int)((mDesc->mAnimationCurves.mpEnd - mDesc->mAnimationCurves.mpBegin) / 0x28);
    mAnimationInfo.resize((uint32_t)n);
    for (int i = 0; i < n; ++i) {
        cLODScales* info = mAnimationInfo.mpBegin + i;
        cAnimationCurve* curve = mDesc->mAnimationCurves.mpBegin + i;
        info->v0 = 0.0f;
        float lo = curve->mLengthRange.x;
        float hi = curve->mLengthRange.y;
        double r = g_sRandom_Swarm.RandomDoubleUniform();
        double v = r * (hi - lo) + lo;
        if (v < hi) {
            hi = (float)v;
            if (v < lo)
                hi = lo;
        }
        if (hi <= 0.0f)
            info->v1 = 0.0f;
        else
            info->v1 = 1.0f / hi;
        float cv = curve->mCurveVary;
        double r2 = g_sRandom_Swarm.RandomDoubleUniform();
        double v2 = r2 * ((cv + 1.0) - (1.0 - cv)) + (1.0 - cv);
        float out = (float)v2;
        if (v2 < (cv + 1.0)) {
            out = (float)v2;
            if (v2 < (1.0 - cv))
                out = (float)(1.0 - cv);
        }
        info->v2 = out;
    }
    mLastLocation = mComponentXform.mTranslation;
    if (mRenderer != 0)
        mRenderer->SetVisible(mModelID, mIsVisible);
}

// @ 0x00aa2fd0
void SetKeywordName(int index, const char* name)
{
    ((const char**)0x01565550)[index * 2] = name;
}
