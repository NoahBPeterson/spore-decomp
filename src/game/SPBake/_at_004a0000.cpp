// src/game/SPBake/_at_004a0000.cpp -- migrated from slice(s) s004ad550, s004ac610, s004ab690, s004aa760 by tools/migrate/rewrite.py
// Object file: SPBake/_at_004a0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPVector3.h"
#include "cSPMatrix3.h"
#include "cSPTransform.h"

// unnamed retail callees and globals (address in the comment)
extern void* EASTL_Allocate(void* alloc, int size, int align, int flags); // 0x42dee0
extern void  FUN_0040ce80(void* p);
#include <new>
#include "EA/ResourceMan/Key.h"
#include "SP/cISPEditorNameProvider.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include "cSPBoundingBox.h"
#include "cSPColorRGB.h"

// ---- items of slice s004aa760 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; V3(const V3& src); };            // copy ctor 0x4098a0
struct Item { float a; V3 b; };
struct DequeIt {
    uint8_t* cur;    // +0x0
    uint8_t* first;  // +0x4
    uint8_t* last;   // +0x8
    uint8_t** node;  // +0xc
    void SetSubarray(void** subarray);  // 0x569340
    DequeIt* Inc();  // 0x4ab210
};
struct DequeBase {
    void* map;        // +0x0
    uint32_t mapSize; // +0x4
    DequeIt begin_;   // +0x8
    DequeIt end_;     // +0x18
    uint32_t alloc[8];// +0x28 allocator storage
    void* AllocNode();                    // 0x4ab320
    void  DequeAlloc(unsigned int n);     // 0x4ab350
    void  ReallocNodeMap(unsigned int n, int flag);  // 0x503470
    void* DoAllocatePtrArray(int n);      // 0x56a240
    void* PushFront(void* value);         // 0x4ab130
};
extern void* EASTL_Allocate(void* alloc, int size, int align, int flags); // 0x42dee0
extern void  FUN_0040ce80(void* p);
extern void FUN_004ab5b0(Item* begin, Item* end, Item* out);
struct Big34 { uint32_t d[0xf]; };
struct M36 { char pad[0x24]; };
static inline const unsigned int& max_alt(const unsigned int& a, const unsigned int& b)
{
    return a < b ? b : a;
}
// ---- items of slice s004aa760 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void FUN_004ab5b0(Item* begin, Item* end, Item* out);

// ---- items of slice s004ab690 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];                                         // 0x01667bac
struct Vector3T {                                                        // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPVector3_s004a_b690 : Vector3T {
    cSPVector3_s004a_b690() {}
    cSPVector3_s004a_b690(float ax, float ay, float az) : Vector3T(ax, ay, az) {}
    cSPVector3_s004a_b690& operator=(const Vector3T& v) { Vector3T::operator=(v); return *this; }
};
cSPVector3_s004a_b690 operator-(const Vector3T& a, const Vector3T& b);              // 0x0041db10
cSPVector3_s004a_b690 operator*(const Vector3T& a, const float& s);                 // 0x0041dca0
cSPVector3_s004a_b690 operator/(const Vector3T& a, const float& s);                 // 0x00453880
cSPVector3_s004a_b690& operator+=(cSPVector3_s004a_b690& a, const cSPVector3_s004a_b690& b);             // 0x0041ddb0
struct cSPBoundingBox_s004a_b690 {
    cSPVector3_s004a_b690 mMin;
    cSPVector3_s004a_b690 mMax;
    cSPVector3_s004a_b690 GetCorner(uint32_t mask) const;                           // 0x0043f290
};
struct cSPColorRGB_s004a_b690 : Vector3T {                                          // user-provided empty ctor
    cSPColorRGB_s004a_b690() {}
};
extern cSPColorRGB_s004a_b690 gDefaultSkinColor;                                    // 0x015d68e8
namespace eastl {
struct sp_vector_allocator_s004a_b690 {
    sp_vector_allocator_s004a_b690() {}
    sp_vector_allocator_s004a_b690(const sp_vector_allocator_s004a_b690&);                     // 0x00429360
};
}
namespace eastl {
template <typename T, typename A = sp_vector_allocator_s004a_b690>
struct basic_string_s004a_b690 {
    T* mpBegin;                                                          // +0x00
    T* mpEnd;                                                            // +0x04
    T* mpCapacity;                                                       // +0x08
    A mAllocator;                                                        // +0x0c
    basic_string_s004a_b690() : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        mpBegin = gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
}
namespace eastl {
template <typename T, typename A = sp_vector_allocator_s004a_b690>
struct vector_s004a_b690 {
    T* mpBegin;                                                          // +0x00
    T* mpEnd;                                                            // +0x04
    T* mpCapacity;                                                       // +0x08
    A mAllocator;                                                        // +0x0c
    unsigned char mAllocatorPad[8 - sizeof(A)];
    vector_s004a_b690(const A& a = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int n) { return mpBegin[n]; }
};
}
struct BBoxVector {
    void* mpBegin;                                                       // +0x00
    void* mpEnd;                                                         // +0x04
    void* mpCapacity;                                                    // +0x08
    unsigned char mAllocatorPad[8];
    BBoxVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
};
namespace EA {
namespace ResourceMan {
struct Key_s004a_b690 {
    unsigned int mInstance;                                              // +0x00
    unsigned int mType;                                                  // +0x04
    unsigned int mGroup;                                                 // +0x08
    Key_s004a_b690() { mInstance = 0; mType = 0; mGroup = 0; }
};
}
}
namespace EA {
template <typename T>
class RefCountTemplate_s004a_b690 {
 public:
    T mCount;
    RefCountTemplate_s004a_b690() : mCount(0) {}
    virtual ~RefCountTemplate_s004a_b690();
};
}
namespace EA {
template <class T> struct AutoRefCount_s004a_b690 {
    T* mpObject;
    AutoRefCount_s004a_b690() { mpObject = 0; if (mpObject != 0) mpObject->AddRef(); }
    operator T*() const { return mpObject; }
};
}
namespace SP {
class cSPEditorModel_s004a_b690;
}
namespace SP {
class cSPEditorPhysicsWorld_s004a_b690 {
 public:
    void* mpVtbl;                                                        // +0x00
    int mRefCount;                                                       // +0x04
    void AddRef() { int c = mRefCount + 1; mRefCount = mRefCount + 1; (void)c; }
};
}
namespace SP {
class cSPEditorBlock_s004a_b690 {
 public:
    char pad0[0x48];
    Vector3T mPosition;                                                  // +0x48
    char pad1[0x33c - 0x54];
    cSPEditorBlock_s004a_b690* mLink33c;                                            // +0x33c
    char pad2[0x3e0 - 0x340];
    cSPEditorBlock_s004a_b690* mPartner;                                            // +0x3e0
    char pad3[0xdc8 - 0x3e4];
    uint32_t mFlags[4];                                                  // +0xdc8

    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
    const Vector3T& GetPosition() { return mPosition; }
    cSPEditorBlock_s004a_b690* GetPartner() { return mPartner; }
    void sub_435be0(cSPEditorModel_s004a_b690* model);                              // 0x00435be0 (thiscall on the block, one stack arg)
    void sub_449ed0();                                                   // 0x00449ed0
    bool IsInChain(cSPEditorBlock_s004a_b690* other);                               // 0x0044a9a0
    cSPBoundingBox_s004a_b690 GetBBox(int type, bool a, bool b);                    // 0x0044ae00
};
}
namespace SP {
class cISPEditorNameProvider_s004a_b690 {
 public:
    cISPEditorNameProvider_s004a_b690() {}
    virtual void SetName(wchar_t const*);
    virtual wchar_t const* GetName() const;
    virtual void SetDescription(wchar_t const*);
    virtual wchar_t const* GetDescription() const;
    virtual void slot4();
    virtual void slot5();
    virtual ~cISPEditorNameProvider_s004a_b690();
};
}
namespace SP {
extern void* g_vtbl_model_a;                                             // 0x013ef624
}
namespace SP {
extern void* g_vtbl_model_b;                                             // 0x013ef620
}
namespace SP {
extern void* g_vtbl_ability;                                             // 0x013ef094
}
namespace SP {
extern void __fastcall FUN_004ad330(void* self);                         // 0x004ad330
}
namespace SP {
extern void __fastcall FUN_004fd940(void* self);                         // 0x004fd940
}
namespace SP {
extern void __fastcall WString_FreeBuffer(void* str);                    // 0x004237d0
}
namespace SP {
extern void __fastcall FUN_453540_Release(void* obj);                    // 0x00453540
}
namespace SP {
extern void __fastcall FUN_004453eb0_vector_dtor(void* vec);             // 0x004453eb0
}
namespace SP {
class cSPEditorModel_s004a_b690 : public cISPEditorNameProvider_s004a_b690, public EA::RefCountTemplate_s004a_b690<int> {
 public:
    cSPEditorModel_s004a_b690();                                                    // 0x004ab690
    void ModelTeardown();                                                // 0x004aba00
    void AddBlock(cSPEditorBlock_s004a_b690* block, bool flag);                     // 0x004abaf0
    cSPVector3_s004a_b690 GetNearestBlockPointToPoint(cSPVector3_s004a_b690 point, cSPEditorBlock_s004a_b690* ignoreBlock,
                                           bool usePositions, bool flatten, cSPVector3_s004a_b690 axis); // 0x004abbc0
    cSPVector3_s004a_b690 GetBestBlockPointBasedOnDistance(cSPVector3_s004a_b690 point, cSPEditorBlock_s004a_b690* ignoreBlock, cSPVector3_s004a_b690 axis,
                                                bool findNearest, bool usePositions, bool flatten, bool useChain); // 0x004abc50
    cSPEditorBlock_s004a_b690* FindNearestFlag7Block(cSPVector3_s004a_b690 point);              // 0x004ac480
    void sub_4adfc0(int v);                                             // 0x004adfc0 (thiscall on the model, one stack arg)

    EA::ResourceMan::Key_s004a_b690 mKey;                                           // +0x0c
    eastl::vector_s004a_b690<EA::AutoRefCount_s004a_b690<cSPEditorBlock_s004a_b690>, eastl::sp_vector_allocator_s004a_b690> mBlockList; // +0x18
    bool mbAllBlocksLoaded;                                              // +0x2c
    EA::AutoRefCount_s004a_b690<cSPEditorPhysicsWorld_s004a_b690> mPhysicsWorld;               // +0x30
    bool mUseDynamics;                                                   // +0x34
    float mBounds;                                                       // +0x38
    float mFeetBounds;                                                   // +0x3c
    float mMinHeight;                                                    // +0x40
    float mMaxHeight;                                                    // +0x44
    float mMinimumLeglessCreatureHeight;                                 // +0x48
    bool mShowHiddenHandles;                                             // +0x4c
    bool mShowBoneLengthHandles;                                         // +0x4d
    bool mUseBoundsForDelete;                                            // +0x4e
    bool mUsingSymmetry;                                                 // +0x4f
    bool mSkinNeedsUpdating;                                             // +0x50
    bool mChanged;                                                       // +0x51
    unsigned int mModelTranslationOptions;                               // +0x54
    int mModelType;                                                      // +0x58
    eastl::basic_string_s004a_b690<wchar_t> mName;                                  // +0x5c
    eastl::basic_string_s004a_b690<wchar_t> mDescription;                           // +0x6c
    eastl::basic_string_s004a_b690<wchar_t> mCleanName;                             // +0x7c
    unsigned int mSkinEffects[3];                                        // +0x8c
    unsigned int mSkinEffectSeeds[3];                                    // +0x98
    cSPColorRGB_s004a_b690 mSkinColors[3];                                          // +0xa4
    BBoxVector mBBoxesOverride;                                          // +0xc8
};
}
// ---- items of slice s004ab690 end

// ---- items of slice s004ac610 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vector3T_s004a_c610 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s004a_c610() {}
    Vector3T_s004a_c610(const Vector3T_s004a_c610& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T_s004a_c610 xAxis, yAxis, zAxis;
};
Vector3T_s004a_c610 operator*(const Vector3T_s004a_c610& v, const Matrix33T& m);   // @ 0x41daf0
Vector3T_s004a_c610 operator-(const Vector3T_s004a_c610& v);                       // @ 0x422020
Vector3T_s004a_c610 operator+(const Vector3T_s004a_c610& a, const Vector3T_s004a_c610& b);    // @ 0x41dc10
Vector3T_s004a_c610& operator+=(Vector3T_s004a_c610& a, const Vector3T_s004a_c610& b);        // @ 0x41ddb0
template<class T> struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct CtorSlots { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount;
template<class T> struct CtorSlots<AutoRefCount<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };
template<class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots<T>::Reserve(); }
    ~VectorBase();                                           // @ 0x425990 (shared)
};
template<class T> struct vector : VectorBase<T> {
    vector() {}
    ~vector() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    T* erase(T* position);                                   // @ 0x454330
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots<T>::ReserveClear(); }
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
namespace SP {
class cSPEditorBlock_s004a_c610 { public:
    virtual void _v0();
    virtual int Release();
    char pad0[0x33c - 4];
    AutoRefCount<cSPEditorBlock_s004a_c610> mParentBlock;  // +0x33c
    vector<AutoRefCount<cSPEditorBlock_s004a_c610> > mSymmetricBlocks;   // +0x340
    char pad1[0x3e0 - 0x354];
    int mUIState;                               // +0x3e0
    char pad2[0x5e8 - 0x3e4];
    int mCost;                                  // +0x5e8
    int mComplexity;                            // +0x5ec
    int mPartType;                              // +0x5f0
    float mWeight;                              // +0x5f4
    char pad3[0xdc8 - 0x5f8];
    bitset<60> mFlags;                          // +0xdc8

    cSPEditorBlock_s004a_c610* GetParent() const { return mParentBlock; }
    int GetUIState() const { return mUIState; }
    int GetPartType() const { return mPartType; }
    bool IsPaintable();                                      // @ 0x44c030
    void OnRemoved();                                        // @ 0x451ed0
    void OnDeleted();                                        // @ 0x451400
    bool HasAnimation();                                     // @ 0x44b780
    bool IsAnimating(bool b);                                // @ 0x43e8d0
    bool IsPlaying();                                        // @ 0x43e920
    void StopAnimation();                                    // @ 0x43e9c0
    void ResetAnimation(bool b);                             // @ 0x43ea40
    void SetModelFlags(int flags);                           // @ 0x44b7b0
    void SetPhysicsGroup(int group);                         // @ 0x451e20
    void SetIndex(int index);                                // @ 0x451e50
};  // namespace SP
}
namespace EA {
template<class T> class RefCountTemplate_s004a_c610 { public:
    virtual void _v0();
    T mRefCount;                                // +0x04
    int AddRef() { T r = mRefCount + 1; mRefCount = mRefCount + 1; return r; }
    int Release();                                           // @ 0x453540
};
}
namespace SP {
class cSPEditorPhysicsWorld_s004a_c610 : public EA::RefCountTemplate_s004a_c610<int> { public:
    int GetGroup();                                          // @ 0x4b91c0
    void AttachModel(class cSPEditorModel_s004a_c610* model);          // @ 0x4b94a0
    void DetachModel(class cSPEditorModel_s004a_c610* model);          // @ 0x4b9570
};
}
namespace SP {
template<class T> struct AutoRefCountP {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCountP& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
}
namespace SP {
extern const uint32_t kDefaultName;                          // @ 0x13ec468
}
namespace SP {
template<class I, class T> inline I find(I first, I last, const T& value)
{
    while ((first != last) && (*first != value)) ++first;
    return first;
}
}
namespace SP {
class cSPEditorModel_s004a_c610 { public:
    virtual void SetName(const uint32_t* name);              // 0x00
    virtual void _v1();
    virtual void SetDescription(const uint32_t* desc);       // 0x08
    char pad0[0x18 - 4];
    vector<AutoRefCount<cSPEditorBlock_s004a_c610> > mBlockList;        // +0x18
    bool mbAllBlocksLoaded;                     // +0x2c
    AutoRefCountP<cSPEditorPhysicsWorld_s004a_c610> mPhysicsWorld;      // +0x30
    char pad1[0x50 - 0x34];
    bool mSkinNeedsUpdating;                    // +0x50

    cSPEditorBlock_s004a_c610* GetRootSpine();
    cSPEditorBlock_s004a_c610* GetUnmatchedSpine();
    void RemoveBlock(cSPEditorBlock_s004a_c610* block, bool recursive, bool notify);
    bool DeleteBlock(cSPEditorBlock_s004a_c610* block, bool recursive);
    cSPEditorBlock_s004a_c610* GetBlock(uint32_t index);
    uint32_t GetBlockCount();                                // @ 0x4accf0
    void GetStats(int* cost, int* complexity, int* count, float* weight, int* parts);
    bool IsAnyBlockAnimating();
    bool IsAnyBlockPlaying();
    void StopAnimations();
    void ResetAnimations();
    void SetModelFlags(int flags);
    void ClearBlocks();
    void Clear();
    void SetPhysicsWorld(cSPEditorPhysicsWorld_s004a_c610* world);
    void SetIndices(int index);
    void NumberBlocks();
    bool CountsForStats();                                   // @ 0x4adc40
    void SetChanged(bool b);                                 // @ 0x4adfc0
};
}
// ---- items of slice s004ac610 end

// ---- items of slice s004ad550 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s004a_d550 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s004a_d550() {}
    Vector3T_s004a_d550(const Vector3T_s004a_d550& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s004a_d550 {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T_s004a_d550 xAxis, yAxis, zAxis;
};
struct cSPMatrix3_s004a_d550 : Matrix33T_s004a_d550 {};
struct cSPVector3_s004a_d550 : Vector3T_s004a_d550 {
    cSPVector3_s004a_d550() {}
    cSPVector3_s004a_d550(const Vector3T_s004a_d550& v) : Vector3T_s004a_d550(v) {}
};
Vector3T_s004a_d550& operator*=(Vector3T_s004a_d550& v, const float& s);           // 0x41dba0
struct cSPTransform_s004a_d550 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3_s004a_d550 mTranslation;
    float mScale;
    cSPMatrix3_s004a_d550 mRotation;
    cSPTransform_s004a_d550();                                          // 0x409930
    void SetTranslation(const cSPVector3_s004a_d550& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetRotation(const cSPMatrix3_s004a_d550& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};
struct cSPBoundingBox_s004a_d550 {
    cSPVector3_s004a_d550 mMin, mMax;
    cSPBoundingBox_s004a_d550& operator=(const cSPBoundingBox_s004a_d550& b) { mMax = b.mMax; mMin = b.mMin; return *this; }
    cSPBoundingBox_s004a_d550();                                        // 0x409c00 (folded with Reset)
    cSPBoundingBox_s004a_d550(const cSPBoundingBox_s004a_d550& b);                 // 0x511140
    void Reset();                                            // 0x409c00
    void Add(const cSPBoundingBox_s004a_d550& b);                       // 0x43f050
    void Transform(const cSPTransform_s004a_d550& t);                   // 0x409dd0
};
struct cSPColorRGB_s004a_d550 {
    float r, g, b;
    cSPColorRGB_s004a_d550(const cSPColorRGB_s004a_d550& c) : r(c.r), g(c.g), b(c.b) {}
};
template<class T> struct AutoRefCount_s004a_d550 {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct AutoRefCountP_s004a_d550 {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCountP_s004a_d550& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        ScratchSlots<3>();
        return *this;
    }
};
struct false_type { false_type() {} };
struct input_iterator_tag { input_iterator_tag() {} };
struct forward_iterator_tag : input_iterator_tag { forward_iterator_tag() {} };
struct bidirectional_iterator_tag : forward_iterator_tag { bidirectional_iterator_tag() {} };
struct random_access_iterator_tag : bidirectional_iterator_tag { random_access_iterator_tag() {} };
template<class T> struct vector_s004a_d550 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    bool empty() const;                                      // 0x526430
    void DoAssignFromIterator(T* first, T* last, input_iterator_tag);  // 0x4b1cc0
    // __forceinline: plain inline is declined by /Ob1 inside GetBlockBoundingBoxes
    __forceinline void DoAssign(T* first, T* last, const false_type&) { DoAssignFromIterator(first, last, random_access_iterator_tag()); }
    void assign(T* first, T* last) { DoAssign(first, last, false_type()); }
    void resize(uint32_t n);                                 // 0x4aff80
};
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* begin() { return mpBegin; }
    wchar_t* end() { return mpEnd; }
    const wchar_t* c_str() const { return mpBegin; }
    static uint32_t CharStrlen(const wchar_t* p) { const wchar_t* pCurrent = p; while (*pCurrent) ++pCurrent; return (uint32_t)(pCurrent - p); }
    wstring& assign(const wchar_t* first, const wchar_t* last);   // 0x423650
    wstring& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
};
namespace SP {
class cSPEditorModel_s004a_d550;
}
namespace SP {
class cSPEditorBlock_s004a_d550 { public:
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3_s004a_d550 mPosition;                       // +0x48
    char pad1[0x60 - 0x54];
    cSPMatrix3_s004a_d550 mOrientation;                    // +0x60
    char pad2[0x1d8 - 0x84];
    float mUniformScale;                        // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount_s004a_d550<cSPEditorBlock_s004a_d550> mParentBlock;  // +0x33c
    char pad4[0xdc8 - 0x340];
    bitset<60> mFlags;                          // +0xdc8

    float GetUniformScale() const { return mUniformScale; }
    cSPBoundingBox_s004a_d550 GetBBox(int a, int b, int c);             // 0x44ae00
    bool IsSelectable();                                     // 0x435d40
    void ClearHighlight();                                   // 0x437890
    void SetHighlight(int state, int flags);                 // 0x437a60
    Vector3T_s004a_d550 GetSnapNormal(bool world);                      // 0x4381e0
    Vector3T_s004a_d550 GetSnapPosition(bool world);                    // 0x438120
    bool Snap(Vector3T_s004a_d550 position, Vector3T_s004a_d550 normal);           // 0x437b00
    bool Load(void* source, int group, float bounds, bool a, bool b);   // 0x450f70
};
}
namespace SP {
class cSPEditorPhysicsWorld_s004a_d550 { public:
    virtual void _v0();
    int mRefCount;                              // +0x04
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                           // 0x453540
    int GetGroup();                                          // 0x4b91c0
    void AttachModel(cSPEditorModel_s004a_d550* model);                 // 0x4b94a0
};
}
namespace SP {
class cSPEditorModel_s004a_d550 { public:
    virtual void SetName(const wchar_t* name);               // 0x00
    virtual void _v1();
    virtual void SetDescription(const wchar_t* desc);        // 0x08
    char pad0[0x18 - 4];
    vector_s004a_d550<AutoRefCount_s004a_d550<cSPEditorBlock_s004a_d550> > mBlockList;        // +0x18
    bool mbAllBlocksLoaded;                     // +0x2c
    AutoRefCountP_s004a_d550<cSPEditorPhysicsWorld_s004a_d550> mPhysicsWorld;      // +0x30
    char pad1[0x38 - 0x34];
    float mBounds;                              // +0x38
    char pad2[0x5c - 0x3c];
    wstring mName;                              // +0x5c
    wstring mDescription;                       // +0x6c
    wstring mCleanName;                         // +0x7c
    uint32_t mSkinEffects[3];                   // +0x8c
    uint32_t mSkinEffectSeeds[3];               // +0x98
    cSPColorRGB_s004a_d550 mSkinColors[3];                 // +0xa4
    vector_s004a_d550<cSPBoundingBox_s004a_d550> mBBoxesOverride;     // +0xc8

    cSPBoundingBox_s004a_d550 GetBoundingBox(bool selectableOnly);
    void GetBlockBoundingBoxes(vector_s004a_d550<cSPBoundingBox_s004a_d550>& boxes);
    void SetBBoxesOverride(const vector_s004a_d550<cSPBoundingBox_s004a_d550>& boxes);
    uint32_t GetSkinEffect(int i);
    uint32_t GetSkinEffectSeed(int i);
    cSPColorRGB_s004a_d550 GetSkinColor(int i);
    void SetSkinEffect(int i, uint32_t effect);
    void SetSkinEffectSeed(int i, uint32_t seed);
    void SetSkinColor(int i, cSPColorRGB_s004a_d550 color);
    cSPEditorBlock_s004a_d550* GetBlock(uint32_t index);                // 0x4accb0
    int GetBlockCount();                                     // 0x4accf0
    void ClearHighlights();
    void SetHighlights(int state);
    bool SnapBlocks();
    void Update();
    bool LoadBlocks(void* source, cSPEditorPhysicsWorld_s004a_d550* world, bool a, bool b);
};
}
// ---- items of slice s004ad550 end

// @ 0x004ab280
M36* CopyM36Range(M36* param_1, M36* param_2, M36* param_3)
{
    M36* local_44 = param_3;
    for (M36* local_40 = param_1; local_40 != param_2;
         local_40 = (M36*)((char*)local_40 + 0x24)) {
        if (local_44 != 0) {
            *(M36*)local_44 = *(M36*)local_40;
        }
        local_44 = (M36*)((char*)local_44 + 0x24);
    }
    for (M36* local_4c = param_1; local_4c != param_2;
         local_4c = (M36*)((char*)local_4c + 0x24)) {
    }
    return local_44;
}

// @ 0x004ab320
void* DequeBase::AllocNode()
{
    return EASTL_Allocate((char*)this + 0x28, 0x100, 4, 0);
}

// @ 0x004ab350
void DequeBase::DequeAlloc(unsigned int n)
{
    const unsigned int nNewPtrArraySize = (n >> 6) + 1;
    const unsigned int kMinPtrArraySize_ = 8;

    mapSize = max_alt(kMinPtrArraySize_, (nNewPtrArraySize + 2));
    map = DoAllocatePtrArray((int)mapSize);

    uint32_t** const pPtrArrayBegin = (uint32_t**)((char*)map + ((mapSize - nNewPtrArraySize) >> 1) * 4);
    uint32_t** const pPtrArrayEnd = pPtrArrayBegin + nNewPtrArraySize;
    uint32_t** pPtrArrayCurrent = pPtrArrayBegin;

    while (pPtrArrayCurrent < pPtrArrayEnd)
        *pPtrArrayCurrent++ = (uint32_t*)AllocNode();

    begin_.SetSubarray((void**)pPtrArrayBegin);
    begin_.cur = begin_.first;
    end_.SetSubarray((void**)(pPtrArrayEnd - 1));
    end_.cur = end_.first + (n % 0x40) * 4;
}

// @ 0x004ab450
uint32_t** FillU32(uint32_t** out, uint32_t* param_dst, int param_count, uint32_t* param_src)
{
    int count = param_count;
    uint32_t* dst = param_dst;
    uint32_t v = *param_src;
    while (count--) *dst++ = v;
    *out = dst;
    return out;
}

// @ 0x004ab4a0
void CopyItemsWrapper(Item* a, Item* b, Item* c)
{
    bool local = false;
    FUN_004ab5b0(a, b, c);
}

// @ 0x004ab530
Big34* CopyBig34Range(Big34* param_1, Big34* param_2, Big34* param_3)
{
    Big34* local_4c = param_3;
    for (Big34* local_48 = param_1; local_48 != param_2;
         local_48 = (Big34*)((char*)local_48 + 0x3c)) {
        if (local_4c != 0) {
            local_4c->d[0] = local_48->d[0];
            FUN_0040ce80((char*)local_48 + 4);
        }
        local_4c = (Big34*)((char*)local_4c + 0x3c);
    }
    return local_4c;
}

// @ 0x004ab5b0
Item* CopyItems(Item* begin, Item* end, Item* out)
{
    for (; begin != end; ++begin, ++out) {
        if (out != 0) {
            out->a = begin->a;
            out->b = begin->b;
        }
    }
    return out;
}

// @ 0x004ab690
namespace SP {
cSPEditorModel_s004a_b690::cSPEditorModel_s004a_b690()
: mbAllBlocksLoaded(false),
      mUseDynamics(false),
      mBounds(0.0f),
      mFeetBounds(0.0f),
      mMinHeight(-2.0f),
      mMaxHeight(2.0f),
      mMinimumLeglessCreatureHeight(0.0f),
      mShowHiddenHandles(false),
      mShowBoneLengthHandles(false),
      mUseBoundsForDelete(true),
      mUsingSymmetry(false),
      mSkinNeedsUpdating(false),
      mChanged(false),
      mModelTranslationOptions(0),
      mModelType(0)
{
    mName.clear();
    mDescription.clear();
    for (int i = 0; i < 3; ++i) {
        mSkinColors[i] = gDefaultSkinColor;
        mSkinEffects[i] = 0;
        mSkinEffectSeeds[i] = 0x4d2;
    }
}
}  // namespace SP

// @ 0x004aba00
namespace SP {
void cSPEditorModel_s004a_b690::ModelTeardown()
{
    *(void**)this = &g_vtbl_model_a;
    *(void**)((char*)this + 4) = &g_vtbl_model_b;
    FUN_004ad330(this);
    char* v = (char*)this + 0xc8;
    for (uint32_t i = *(uint32_t*)v; i < *(uint32_t*)(v + 4); i += 0x18) {
    }
    FUN_004fd940(v);
    WString_FreeBuffer((char*)this + 0x7c);
    WString_FreeBuffer((char*)this + 0x6c);
    WString_FreeBuffer((char*)this + 0x5c);
    void** rc = (void**)((char*)this + 0x30);
    if (*rc != 0) {
        FUN_453540_Release(*rc);
    }
    FUN_004453eb0_vector_dtor((char*)this + 0x18);
    *(void**)((char*)this + 4) = &g_vtbl_ability;
}
}  // namespace SP

// @ 0x004ac610
namespace SP {
cSPEditorBlock_s004a_c610* cSPEditorModel_s004a_c610::GetRootSpine()
{
    for (int tmp = 0, t14 = mBlockList.size(); tmp < t14; tmp++) {
        if (mBlockList[tmp]->mFlags.test(7) && !mBlockList[tmp]->GetParent())
            return mBlockList[tmp];
    }
    return 0;
}
}  // namespace SP

// @ 0x004ac710
namespace SP {
cSPEditorBlock_s004a_c610* cSPEditorModel_s004a_c610::GetUnmatchedSpine()
{
    for (int tmp = 0, t14 = mBlockList.size(); tmp < t14; tmp++) {
        if (mBlockList[tmp]->mFlags.test(7)) {
            bool bFound = false;
            vector<AutoRefCount<cSPEditorBlock_s004a_c610> >& symBlocks = mBlockList[tmp]->mSymmetricBlocks;
            for (int j = 0, m = symBlocks.size(); j < m; j++) {
                if (symBlocks[j]->mFlags.test(7)) { bFound = true; break; }
            }
            if (!bFound) return mBlockList[tmp];
        }
    }
    return 0;
}
}  // namespace SP

// @ 0x004ac8b0
namespace SP {
void cSPEditorModel_s004a_c610::RemoveBlock(cSPEditorBlock_s004a_c610* block, bool recursive, bool notify)
{
    if (recursive) {
        vector<AutoRefCount<cSPEditorBlock_s004a_c610> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++)
            RemoveBlock(syms[i], recursive, false);
    }
    AutoRefCount<cSPEditorBlock_s004a_c610>* it = find(mBlockList.begin(), mBlockList.end(), block);
    if (it != mBlockList.end()) {
        if ((block->mFlags.test(0xb) || block->mFlags.test(7)) && block->IsPaintable() && block->mFlags.test(0xa))
            mSkinNeedsUpdating = true;
        if (notify) block->OnRemoved();
        mBlockList.erase(it);
        ScratchSlots<4>();
        SetChanged(true);
    }
}
}  // namespace SP

// @ 0x004acab0
namespace SP {
bool cSPEditorModel_s004a_c610::DeleteBlock(cSPEditorBlock_s004a_c610* block, bool recursive)
{
    if (recursive) {
        vector<AutoRefCount<cSPEditorBlock_s004a_c610> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++)
            DeleteBlock(syms[i], recursive);
    }
    AutoRefCount<cSPEditorBlock_s004a_c610>* it = find(mBlockList.begin(), mBlockList.end(), block);
    if (it != mBlockList.end()) {
        if ((block->mFlags.test(0xb) || block->mFlags.test(7)) && block->IsPaintable() && block->mFlags.test(0xa))
            mSkinNeedsUpdating = true;
        block->OnDeleted();
        mBlockList.erase(it);
        ScratchSlots<4>();
        SetChanged(true);
    }
    return true;
}
}  // namespace SP

// @ 0x004acd20
namespace SP {
void cSPEditorModel_s004a_c610::GetStats(int* cost, int* complexity, int* count, float* weight, int* parts)
{
    int len = 0;
    int t24 = 0;
    int offset = 0;
    float where = 0.0f;
    int p24 = 0;
    for (int t14 = 0, tmp = mBlockList.size(); t14 < tmp; t14++) {
        cSPEditorBlock_s004a_c610* item = mBlockList[t14];
        int t26 = item->mCost;
        int nCount = item->mComplexity;
        int p15;
        if (item->GetPartType() != 2) p15 = 1; else p15 = 0;
        int hi = 1;
        float t22 = item->mWeight;
        if (CountsForStats() && !item->mFlags.test(7) && !item->mFlags.test(0x39) &&
            item->mFlags.test(0xf) && item->GetUIState() == 0) {
            t26 *= 2;
            nCount *= 2;
            p15 *= 2;
            t22 *= 2.0f;
            hi *= 2;
        }
        len += t26;
        t24 += nCount;
        offset += p15;
        where += t22;
        p24 += hi;
    }
    if (cost) *cost = len;
    if (complexity) *complexity = t24;
    if (count) *count = offset;
    if (weight) *weight = where;
    if (parts) *parts = p24;
}
}  // namespace SP

// @ 0x004acfd0
namespace SP {
bool cSPEditorModel_s004a_c610::IsAnyBlockAnimating()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        if (mBlockList[i]->HasAnimation() && mBlockList[i]->IsAnimating(true))
            return true;
    }
    return false;
}
}  // namespace SP

// @ 0x004ad070
namespace SP {
bool cSPEditorModel_s004a_c610::IsAnyBlockPlaying()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        if (mBlockList[i]->HasAnimation() && mBlockList[i]->IsPlaying())
            return true;
    }
    return false;
}
}  // namespace SP

// @ 0x004ad110
namespace SP {
void cSPEditorModel_s004a_c610::StopAnimations()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        if (mBlockList[i]->IsPlaying())
            mBlockList[i]->StopAnimation();
    }
}
}  // namespace SP

// @ 0x004ad1a0
namespace SP {
void cSPEditorModel_s004a_c610::ResetAnimations()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->ResetAnimation(true);
}
}  // namespace SP

// @ 0x004ad210
namespace SP {
void cSPEditorModel_s004a_c610::SetModelFlags(int flags)
{
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->SetModelFlags(flags);
}
}  // namespace SP

// @ 0x004ad280
namespace SP {
void cSPEditorModel_s004a_c610::ClearBlocks()
{
    SetName(&kDefaultName);
    SetDescription(&kDefaultName);
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->OnDeleted();
    mBlockList.clear();
}
}  // namespace SP

// @ 0x004ad330
namespace SP {
void cSPEditorModel_s004a_c610::Clear()
{
    ClearBlocks();
    if (mPhysicsWorld) mPhysicsWorld->DetachModel(this);
}
}  // namespace SP

// @ 0x004ad550
namespace SP {
cSPBoundingBox_s004a_d550 cSPEditorModel_s004a_d550::GetBoundingBox(bool selectableOnly)
{
    cSPBoundingBox_s004a_d550 bbox;
    bbox.Reset();
    ScratchSlots<12>();
    uint32_t count = mBlockList.size();
    if (count > 0) {
        bbox = mBlockList[0]->GetBBox(0, 0, 0);
        for (int i = 1, n = mBlockList.size(); i < n; i++) {
            if (selectableOnly && !mBlockList[i]->IsSelectable()) continue;
            bbox.Add(mBlockList[i]->GetBBox(0, 0, 0));
        }
    }
    ScratchSlots<1>();
    return bbox;
}
}  // namespace SP

// @ 0x004ad6f0
namespace SP {
void cSPEditorModel_s004a_d550::GetBlockBoundingBoxes(vector_s004a_d550<cSPBoundingBox_s004a_d550>& boxes)
{
    if (!mBBoxesOverride.empty()) {
        boxes.assign(mBBoxesOverride.begin(), mBBoxesOverride.end());
    } else {
    boxes.resize(mBlockList.size());
    ScratchSlots<9>();
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        boxes[i] = mBlockList[i]->GetBBox(2, 1, 0);
        if (mBlockList[i]->mFlags.test(10)) {
            boxes[i].mMin *= 1.1f;
            boxes[i].mMax *= 1.1f;
        }
        cSPTransform_s004a_d550 t;
        ScratchSlots<1>();
        t.SetTranslation(mBlockList[i]->mPosition);
        t.SetRotation(mBlockList[i]->mOrientation);
        t.SetScale(mBlockList[i]->GetUniformScale());
        boxes[i].Transform(t);
        ScratchSlots<41>();
    }
    }
}
}  // namespace SP

// @ 0x004ada40
namespace SP {
void cSPEditorModel_s004a_d550::SetBBoxesOverride(const vector_s004a_d550<cSPBoundingBox_s004a_d550>& boxes)
{
    mBBoxesOverride.assign(boxes.begin(), boxes.end());
}
}  // namespace SP

// @ 0x004adc60
namespace SP {
uint32_t cSPEditorModel_s004a_d550::GetSkinEffect(int i)
{
    return mSkinEffects[i];
}
}  // namespace SP

// @ 0x004adc80
namespace SP {
uint32_t cSPEditorModel_s004a_d550::GetSkinEffectSeed(int i)
{
    return mSkinEffectSeeds[i];
}
}  // namespace SP

// @ 0x004adca0
namespace SP {
cSPColorRGB_s004a_d550 cSPEditorModel_s004a_d550::GetSkinColor(int i)
{
    return mSkinColors[i];
}
}  // namespace SP

// @ 0x004adcf0
namespace SP {
void cSPEditorModel_s004a_d550::SetSkinEffect(int i, uint32_t effect)
{
    mSkinEffects[i] = effect;
}
}  // namespace SP

// @ 0x004add10
namespace SP {
void cSPEditorModel_s004a_d550::SetSkinEffectSeed(int i, uint32_t seed)
{
    mSkinEffectSeeds[i] = seed;
}
}  // namespace SP

// @ 0x004add30
namespace SP {
void cSPEditorModel_s004a_d550::SetSkinColor(int i, cSPColorRGB_s004a_d550 color)
{
    mSkinColors[i] = color;
}
}  // namespace SP
