// src/game/UTFSpore_Win32/instantiate.cpp -- migrated from slice(s) s00b25c30, s0050e850, s0050d750, s0050aac0, s00509f50, s00507670, s00477930, s00454330, s0083c900, s0050c6c0, s00475d00, s004553b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/instantiate.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "SP/cCity.h"
#include "SP/cCivilization.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoSimulator.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cIGonzagoSubsystem.h"
#include "SP/cISerializableObject.h"
#include "SP/cStarManager.h"
#include "SP/cVarListSerializer.h"
#include "EA/Messaging/AutoHandler.h"

// ---- items of slice s00475d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct E8  { uint a, b; };
// ---- items of slice s00475d00 end

// ---- items of slice s0050c6c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void ea_delete(void* p);
uint32_t GrowCopy(uint32_t n, uint32_t* first, uint32_t* last);   // 0x0042e5b0
void MoveInto(void* dst, void* src, int bytes);                   // vector<bool>::DoInsertValue
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);
struct AppendTag {};
struct Elem12 { float a, b, c; };
struct Elem8 { unsigned a, b; };
struct Elem20 { unsigned w[5]; };
struct Vec12 {                           // +0x08 / +0x1c
    Elem12* mpBegin; Elem12* mpEnd; Elem12* mpCap; int mAlloc; int pad;
    void insert(Elem12* where, Elem12* first, Elem12* last) { insert(where, first, last, AppendTag()); }
    void insert(Elem12* where, Elem12* first, Elem12* last, AppendTag t);   // 0x0050f180 (ret 0x10)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct Vec8 {                            // +0x30, +0x124
    Elem8* mpBegin; Elem8* mpEnd; Elem8* mpCap; int mAlloc; int pad;
    void insert(Elem8* where, Elem8* first, Elem8* last) { insert(where, first, last, AppendTag()); }
    void insert(Elem8* where, Elem8* first, Elem8* last, AppendTag t);       // 0x0050f1b0 (ret 0x10)
    void resize(unsigned n);                                                 // 0x004cd440 (ret 4)
};
struct Vec20_s0050_c6c0 {                           // +0x44
    Elem20* mpBegin; Elem20* mpEnd; Elem20* mpCap; int mAlloc; int pad;
    void insert(Elem20* where, Elem20* first, Elem20* last) { insert(where, first, last, AppendTag()); }
    void insert(Elem20* where, Elem20* first, Elem20* last, AppendTag t);    // 0x0050f1e0 (ret 0x10)
};
struct VecU32 {                          // uint vectors: +0x58 +0x6c +0x80 +0x94 +0xa8 +0x110 +0x138 +0x1a4
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int mAlloc; int pad;
    void insert(unsigned* where, unsigned* first, unsigned* last) { insert(where, first, last, AppendTag()); }
    void insert(unsigned* where, unsigned* first, unsigned* last, AppendTag t);   // 0x004778c0 (ret 0x10)
    void resize(unsigned n);                                                 // 0x004cd3c0 (ret 4)
    void resize(unsigned n, const int& fill);                                // 0x004746c0 (ret 8)
    void push_back(const unsigned& v);                                       // 0x00454860 (ret 4)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct VecAny {                          // +0x190
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int mAlloc; int pad;
    void insert(unsigned* where, unsigned* first, unsigned* last);           // 0x0050e5c0 (ret 0xc)
};
struct SmallVec {                        // vector inside a Container piece (+0x08), out-of-line size()
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int mAlloc; int pad;
    unsigned size() const;                                                   // 0x004746a0
    unsigned& operator[](unsigned i) { return mpBegin[i]; }
};
struct Container_s0050_c6c0 {                       // 0x94-byte piece ("Skinner" allocation)
    int m00, m04;
    SmallVec m08;
    char rest[0x94 - 0x08 - sizeof(SmallVec)];
    Container_s0050_c6c0(const Container_s0050_c6c0& src);                                         // 0x00508320 (ret 4)
};
struct PieceVec {                        // +0xe4: vector of owned Container*
    Container_s0050_c6c0** mpBegin; Container_s0050_c6c0** mpEnd; Container_s0050_c6c0** mpCap; int mAlloc; int pad;
    bool empty() const;                                                      // 0x00526430
    void resize(unsigned n);                                                 // 0x004cd3c0 (ret 4)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    Container_s0050_c6c0*& operator[](unsigned i) { return mpBegin[i]; }
};
struct Skin_s0050_c6c0 {
    char pad0[8];
    Vec12 m08;          // +0x08
    Vec12 m1c;          // +0x1c
    Vec8  m30;          // +0x30
    Vec20_s0050_c6c0 m44;          // +0x44
    VecU32 m58, m6c;    // +0x58 +0x6c
    VecU32 m80, m94;    // +0x80 +0x94
    VecU32 ma8;         // +0xa8
    char padbc[0xe4 - 0xbc];
    PieceVec me4;       // +0xe4
    char padf8[0x110 - 0xf8];
    VecU32 m110;        // +0x110
    Vec8   m124;        // +0x124
    VecU32 m138;        // +0x138
    char pad14c[0x190 - 0x14c];
    VecAny m190;        // +0x190
    VecU32 m1a4;        // +0x1a4

    void Append(const Skin_s0050_c6c0& other);
};
// ---- items of slice s0050c6c0 end

// ---- items of slice s0083c900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gAppPropsMin;
extern float gAppPropsMax;
extern void* gAppPropsBuckets[];
extern void* vtbl_AppProps;   // 0x0141b5e4 (equiv t3)
struct AppPropsFields {
    void* vtbl;          // +0x00
    int   mParser;       // +0x04
    int   mRefCount;     // +0x08
    int   pad0c;         // +0x0c
    int   pad10;         // +0x10
    void* mpBucketArray; // +0x14
    int   mnBucketCount; // +0x18
    int   mnElementCount;// +0x1c
    float mMin;          // +0x20
    float mMax;          // +0x24
    int   pad28;         // +0x28
    AppPropsFields();                        // 0x0083cdd0
    AppPropsFields* VectorDtor(unsigned char flags); // 0x0083ce20
};
// ---- items of slice s0083c900 end

// ---- items of slice s00454330 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RbNode;
struct RbNodeBase {                    // rbtree node header
    RbNodeBase* mpLeft;                // +0x000
    RbNodeBase* mpRight;               // +0x004
    RbNodeBase* mpParent;              // +0x008
};
struct RbNode : RbNodeBase {           // node value: pair<const unsigned, unsigned> at +0x10
    char     mColor;                   // +0x00c
    char     pad00d[3];
    unsigned mKey;                     // +0x010
    unsigned mValue;                   // +0x014
};
struct MapValue { unsigned mKey; unsigned mValue; };
struct RbIter {                        // 1-word node iterator
    RbNode*   mpNode;
    RbIter*   assign(RbNode* node);    // 0x00566c50  *this = node; returns this
    unsigned* value();                 // 0x00564f50  &node->mKey (the stored pair)
};
struct NodeVec {
    void* mpBegin;                     // +0x000
    void* mpEnd;                       // +0x004
    void* mpCapacity;                  // +0x008
    char  mAlloc[8];                   // +0x00c
    void* mpOverflow;                  // +0x014
    char  mFixed[0x40];                // +0x018  8 inline 8-byte slots
    NodeVec* Construct();                        // 0x004727a0  default construction
    NodeVec* ConstructFrom(const NodeVec& src);  // 0x00455cf0  construction from another's allocator state
    void     Destroy();                          // 0x0045daf0  destroys the elements and frees storage
};
struct RbTree {
    char       pad000[4];
    RbNodeBase mAnchor;                // +0x004  end() sentinel node; mAnchor.mpParent (+0x00c) is the root
    RbIter* find(RbIter* out, const unsigned* key);                 // 0x004b5e90  lower_bound
    RbIter* insert(RbIter* out, RbIter position, const MapValue* value);  // 0x00455460
};
struct RbUIntMap2 : RbTree {
    unsigned* find_or_insert(const unsigned* key);
};
// ---- items of slice s00454330 end

// ---- items of slice s004553b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  FUN_0050d750(void* p);
extern void* FUN_0042dee0(void* a, int n, int sz, int z);
extern "C" void* __cdecl FUN_11e0744_memcpy(void*, const void*, unsigned int);   // 0x011e0744
__declspec(dllimport) void __cdecl memmove(void*, const void*, unsigned int);
void __cdecl FUN_00f47380_dealloc(void* block);                                  // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }
struct FixedC {
    int* InitFixed(void* p);      // 0x00455cf0
    void FUN_0050d750(void* p);   // 0x0050d750, ecx = this
};
template <typename T>
inline T* eastl_copy(const T* first, const T* last, T* result) // copy_impl<true,RA>::do_copy (memcpy path)
{
    return (T*)FUN_11e0744_memcpy(result, first, (unsigned)last - (unsigned)first) + (last - first);
}
template <typename T>
inline T* eastl_uninitialized_copy_ptr(const T* first, const T* last, T* result)
{
    const bool bA = true;
    T* p = eastl_copy(first, last, result);
    const bool bB = true;
    return p;
}
template <typename T>
inline void eastl_copy_backward_impl(const T* first, const T* last, T* result) // copy_backward_impl<true,RA>
{
    memmove((T*)result - (last - first), first, (unsigned)last - (unsigned)first);
}
template <typename T>
inline void eastl_copy_backward_chooser(const T* first, const T* last, T* result)
{
    const bool bHasTrivialCopy = true;
    eastl_copy_backward_impl(first, last, result);
}
template <typename T>
inline void eastl_copy_backward(const T* first, const T* last, T* result)
{
    const bool bInputIsGenericIterator  = false;
    const bool bOutputIsGenericIterator = false;
    eastl_copy_backward_chooser(first, last, result);
}
inline unsigned eastl_GetNewCapacity(unsigned currentCapacity) // VectorBase::GetNewCapacity
{
    // This needs to return a value of at least currentCapacity and at least 1.
    return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
}
template <typename T>
inline T* eastl_DoAllocate(void* allocator, unsigned n) // VectorBase::DoAllocate
{
    // If n is zero, then we allocate no memory and just return NULL.
    return n ? (T*)FUN_0042dee0(allocator, n * sizeof(T), 4, 0) : 0;
}
inline void eastl_sp_deallocate(void* p, unsigned n) // sp_vector_allocator::deallocate
{
    if (((int*)p)[-1]) { void* q = p; FUN_00f47380_dealloc(q); }
}
template <typename T>
inline void eastl_DoFree(T* p, unsigned n) // VectorBase::DoFree
{
    if (p) eastl_sp_deallocate(p, n * sizeof(T));
}
struct SPVecU32_s004553b0 {
    unsigned* mBegin;     // +0x00
    unsigned* mEnd;       // +0x04
    unsigned* mCapacity;  // +0x08
    void*     mAllocator; // +0x0c
    void VectorInsertU32(unsigned* position, const unsigned& value);
};
// ---- items of slice s004553b0 end

// ---- items of slice s00477930 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(memmove)
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
extern "C" void* __cdecl memcpy(void* dst, const void* src, uint n);
struct P8 { uint a, b; };
template<class T> T* UninitCopyRange(T* first, T* last, T* dest)
{
    uint bytes = (uint)((char*)last - (char*)first);
    memcpy(dest, first, bytes);
    return (T*)((char*)dest + bytes);
}
struct RefObj {
    int vptr; int mnRefCount;
    void Release();                                                      // 0x00453540 (RefCountTemplate<int>::Release)
};
struct ThreadedObject {
    void Release();                                                      // 0x00404f90
};
struct cSPTransform_s0047_7930 {                                                    // 0x38 bytes
    char d[0x38];
    cSPTransform_s0047_7930();                                                      // 0x00409930
    cSPTransform_s0047_7930(const cSPTransform_s0047_7930& o);                                 // 0x0040ce80
    cSPTransform_s0047_7930& operator=(const cSPTransform_s0047_7930& o);                      // 0x00537dc0
};
struct VirtualRefPtr {                                                   // 0x00 4 bytes
    RefObj* mp;
    VirtualRefPtr() : mp(0) {}
    VirtualRefPtr(RefObj* p);                                            // 0x0041cc20
    ~VirtualRefPtr();                                                    // 0x004a9b10 (AutoRefCount<PropertyList>::~AutoRefCount)
};
struct TargetPtr {
    RefObj* mp;
    TargetPtr() : mp(0) {}
    TargetPtr(RefObj* p) : mp(0) { Init(p); }
    ~TargetPtr() { if (mp) mp->Release(); }
    TargetPtr& Init(RefObj* p);                                          // 0x0041ccc0
};
struct PartTransform {                                                   // two 0x38 transforms
    cSPTransform_s0047_7930 a, b;
    PartTransform() {}
    PartTransform(const cSPTransform_s0047_7930& src) : b(src) {}
    void Invert();                                                       // 0x0040efa0
};
struct Elem7c {
    PartTransform t;
    int           mnIndex;
    VirtualRefPtr mRef;
    TargetPtr     mTarget;
    __forceinline Elem7c() : mnIndex(0), mRef(), mTarget() {}
    __forceinline Elem7c(const cSPTransform_s0047_7930& src, RefObj* ref, RefObj* target)
        : t(src), mnIndex(-1), mRef(ref), mTarget(target) {}
};
struct Elem7cVec {
    Elem7c* mpBegin; Elem7c* mpEnd; Elem7c* mpCap; int pad[2];
    void push_back(const Elem7c& e);                                     // 0x0041f650
};
struct UIntVec {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; int pad[2];
    void push_back(const unsigned& v);                                   // 0x00454860
};
struct DropRange { int count; int start; };
struct RangeSink {
    void Add(const DropRange* r);                                        // 0x005402c0
};
struct FixedVecRef {
    void* mpBegin; void* mpEnd;
    bool empty() const;                                                  // 0x00526430
};
template<class T> struct Vec20 { T* mpBegin; int pad[4]; };              // eastl vector, 0x14 bytes
struct HandleArrays {                                                    // lives at EditorHandles+0x14
    Vec20<ThreadedObject*> present;    // +0x00
    Vec20<float>         rects;       // +0x14 (16-byte records)
    Vec20<cSPTransform_s0047_7930>  xfA;         // +0x28
    Vec20<cSPTransform_s0047_7930>  xfB;         // +0x3c
    Vec20<ThreadedObject*> res;       // +0x50
    Vec20<RefObj*>       refs;        // +0x64
    Vec20<RefObj*>       targets;     // +0x78
};
struct ModelObj {
    char    pad0[0xc];
    unsigned* idxBegin; unsigned* idxEnd;      // +0x0c, 4-byte entries
    char    pad1[0x20 - 0x14];
    char*   triBegin; char* triEnd;            // +0x20, 12-byte entries
    char    pad2[0x5c - 0x28];
    float*  uvBegin; float* uvEnd;             // +0x5c, 8-byte entries
    char    pad3[0x70 - 0x64];
    char    obj70[0x14];                       // +0x70
    char    obj84[0x14];                       // +0x84
    int  indexCount() const { return (int)(idxEnd - idxBegin); }
    int  triCount() const { return (int)((triEnd - triBegin) / 0xc); }
    unsigned uvCount() const { return (unsigned)(((char*)uvEnd - (char*)uvBegin) >> 3); }
};
struct ShortIdx4 { short v[4]; };
struct Obj70 {
    void Set(int index, const ShortIdx4* v);                             // 0x004740f0
};
struct Obj84 {
    void Set(int index, const float* v);                                 // 0x00474450
};
struct HandleState {
    char pad[0x18];
    int  mbDone;      // +0x18
    int  mnNext;      // +0x1c
    void Continue(struct EditorHandles* h);                              // 0x00475580
    void Finish(struct EditorHandles* h);                                // 0x00478260
};
int  CountTarget(void* res, int key);                                    // 0x0071dd80
void InstantiateModel(void* res, ModelObj* m, int offset, void* x);      // 0x004600f0 (4 args)
void ApplyResource(void* res, ModelObj* m, void* xf);                    // 0x0045f5e0
struct ModelData { char pad[0x98]; char* begin; char* end; };
struct EditorHandles {
    char          pad0[0xc];
    ModelObj*     mpModel;        // +0x0c
    ModelData*    mpData;         // +0x10
    HandleArrays  arrays;         // +0x14
    FixedVecRef   fixedRef;       // +0xa0
    char          pad2[0xe4 - 0xa8];
    int           mnBase;         // +0xe4
    int           mnEnd;          // +0xe8
    UIntVec       indexCounts;    // +0xec
    char          pad3[0x124 - 0xec - sizeof(UIntVec)];
    UIntVec       triCounts;      // +0x124
    char          pad4[0x15c - 0x124 - sizeof(UIntVec)];
    RangeSink     sink;           // +0x15c
    char          pad5[0x1b4 - 0x15c - 1];
    Elem7cVec     elems;          // +0x1b4
    void Update(HandleState* st);
};
// ---- items of slice s00477930 end

// ---- items of slice s00507670 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Container;
void __fastcall VecRelease4(void* member);       // 0x00425990  stride-4 release
void __fastcall VecRelease8(void* member);       // 0x0045daf0  stride-8 release
void __fastcall VSetDestroy(void* member);       // 0x00540520
void __fastcall VecFDestroy(void* member);       // 0x004e1bf0
void __fastcall Vec24Destroy(void* member);      // 0x0041e730
void __fastcall Vec30Destroy(void* member);      // 0x004cddd0
void __fastcall ElementDestroyVectors(void* el); // 0x00507b30
void __fastcall Ptr164Destroy(void* obj);        // 0x004fdd60
void __fastcall DestroySubA(void* self);   // 0x005156b0
void __fastcall DestroySubB(void* self);   // 0x00425990
void __fastcall DestroySubC(void* self);   // 0x0050ea50
struct CSetA { char pad[0x14]; CSetA& operator=(const CSetA& o); };   // 0x0050d440
struct CSetB { char pad[0x14]; CSetB& operator=(const CSetB& o); };   // 0x0050da90
struct CSetC { char pad[0x14]; CSetC& operator=(const CSetC& o); };   // 0x00565be0
struct Container {                  // 0x94-byte element ("Skinner" allocation)
    int    m00, m04;
    CSetA  m08, m1c, m30;
    CSetB  m44;
    float  m58, m5c, m60, m64;
    int    m68;
    CSetA  m6c;
    CSetC  m80;
    ~Container();
    Container(const Container& src);      // 0x00508320 (copy constructor)
};

struct Alloc { Alloc() {} };
struct SpAlloc { char pad[8]; SpAlloc(const Alloc& a); };                 // 0x00429360
struct VSetImpl {                                            // vector_set<unsigned>, 0x14 bytes
    void* mpBegin; void* mpEnd; void* mpCap; SpAlloc mAlloc;
    VSetImpl(const Alloc& a);                                // 0x00540470
};
template <int K> struct VSetK : VSetImpl {
    VSetK(const Alloc& a) : VSetImpl(a) {}
    VSetK& operator=(const VSetK& o);       // K=0: 0x00473500, K=1: 0x00473b00, K=2: 0x0050d070
};
typedef VSetK<0> VSet;
typedef VSetK<1> VSetB;
typedef VSetK<2> VSetC;
struct VSetD : VSetImpl { VSetD() : VSetImpl(Alloc()) {} };
struct Vec {                                                 // 0x14-byte vector (4-byte elements)
    void* mpBegin; void* mpEnd; void* mpCap; SpAlloc mAlloc;
    Vec(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    Vec& operator=(const Vec& o);                            // 0x0050d4e0
    void Destroy();                                          // 0x00425990 (stride-4 release)
};
struct VecP {                                                // vector of element pointers
    Container** mpBegin; Container** mpEnd; Container** mpCap; SpAlloc mAlloc;
    VecP(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    VecP& operator=(const VecP& o);                          // 0x0050d4e0
    unsigned int size() const { return mpEnd - mpBegin; }
    Container*& operator[](unsigned int i) { return mpBegin[i]; }
    void Destroy();                                          // 0x00425990 (stride-4 release)
};
struct VecG {
    void* mpBegin; void* mpEnd; void* mpCap; SpAlloc mAlloc;
    VecG(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    VecG& operator=(const VecG& o);                          // 0x0050d750
    void Destroy();                                          // 0x0045daf0 (stride-8 release)
};
struct VecU {                                                // SP::SimpleVector<unsigned>
    unsigned int* mpBegin; unsigned int* mpEnd; unsigned int* mpCap; SpAlloc mAlloc;
    VecU(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    unsigned int* erase(unsigned int* first, unsigned int* last);   // 0x004769b0
    void clear() { erase(mpBegin, mpEnd); }
    void Destroy();                                          // 0x00425990 (stride-4 release)
};
struct VecT {                                                // member at +0x17c
    void* mpBegin; void* mpEnd; void* mpCap; SpAlloc mAlloc;
    VecT(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    void Clear();                                            // 0x004208f0
    void Destroy();                                          // 0x00425990 (stride-4 release)
};
struct BBox { char pad[0x18]; BBox() { Reset(); } void Reset(); };                     // BoundingBox_Reset 0x00409c00
struct GmeRefCount {
    int mnRefCount;
    GmeRefCount() : mnRefCount(0) {}
    virtual ~GmeRefCount();
};
struct Skin : GmeRefCount {
    VSet   m08, m1c;
    VSetB  m30;
    VSetC  m44;
    VSet   m58, m6c;
    Vec    m80, m94;
    VSet   ma8;
    Vec    mbc;
    VSetD  md0;
    VecP   me4;
    Vec    mf8;
    int    m10c;
    Vec    m110;
    VecG   m124;
    Vec    m138;
    BBox   m14c;
    void*  m164;
    VecU   m168;
    VecT   m17c;
    Vec    m190;
    VSet   m1a4;
    VecG   m1b8;
    int    m1cc;

    Skin(const Skin& o);
    virtual ~Skin();
};
__forceinline void SkinStoreVtable(Skin* self, void* vt) { *(void**)self = vt; }
__forceinline void TouchedRelease4(void* begin, void* end, void* member)
{
    for (char* p = (char*)begin; p < (char*)end; p += 4) {}
    VecRelease4(member);
}
__forceinline void TouchedRelease8(void* begin, void* end, void* member)
{
    for (char* p = (char*)begin; p < (char*)end; p += 8) {}
    VecRelease8(member);
}
// ---- items of slice s00507670 end

// ---- items of slice s00509f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const signed char gCode3[3];                            // 0x013f18d0
extern const signed char gOff3[3];                             // 0x013f18d8
extern const float kFloatMax;                                  // 0x013f18c4
struct V3 { float x, y, z; };
V3* __cdecl SubV3(V3* out, const V3* a, const V3* b);          // @ 0x0041db10  out = a - b
V3* __cdecl CrossV3(V3* out, const V3* a, const V3* b);        // @ 0x0044e460  out = a x b
int __cdecl DominantAxis(const V3* v);                          // @ 0x004fddb0  index of largest component
void operator delete(void* p);                                 // 0x00f47380
struct Pair2 {
    unsigned int first, second;
    Pair2() {}
    Pair2(unsigned int a, unsigned int b) : first(a), second(b) {}
};
struct PairSet {
    Pair2* mpBegin; Pair2* mpEnd; Pair2* mpCap; SpAlloc mAlloc;
    PairSet(const Alloc& a = Alloc());                         // 0x00540470
    ~PairSet();                                                // 0x004cddd0
    unsigned int size() const;                                 // 0x00474050
    Pair2& operator[](unsigned int i) { return mpBegin[i]; }
    void push_back(const Pair2& v);                            // 0x005402c0
    void erase(Pair2* first, Pair2* last);                     // 0x00530c80
};
struct VecU_s0050_9f50 {
    unsigned int* mpBegin; unsigned int* mpEnd; unsigned int* mpCap; SpAlloc mAlloc;
    unsigned int size() const { return mpEnd - mpBegin; }
    unsigned int& operator[](unsigned int i) { return mpBegin[i]; }
    unsigned int* erase(unsigned int* first, unsigned int* last);               // 0x004769b0
    void insert(unsigned int* pos, unsigned int n, const unsigned int& value);  // 0x004cea40
    void push_back(const unsigned int& v);                                      // @ 0x00454860
    void resize(unsigned int n)                                // 0x004cd3c0
    {
        if (n > size()) {
            unsigned int value = 0;
            unsigned int diff = n - size();
            unsigned int* pos = mpEnd;
            insert(pos, diff, value);
        } else {
            erase(mpBegin + n, mpEnd);
        }
    }
};
struct Vertex12 { float x, y, z; };
struct VecV {
    Vertex12* mpBegin; Vertex12* mpEnd; Vertex12* mpCap; SpAlloc mAlloc;
    int size() const { return mpEnd - mpBegin; }
};
struct Entry { unsigned int a, b; };
struct VecE {                                                  // 8-byte entries
    Entry* mpBegin; Entry* mpEnd; Entry* mpCap; SpAlloc mAlloc;
    Entry* begin() { return mpBegin; }
    Entry* end() { return mpEnd; }
    unsigned int size() const { return mpEnd - mpBegin; }
    Entry* erase(Entry* first, Entry* last);                   // 0x00530c80
    void insert(Entry* pos, unsigned int n, const Entry& value);   // 0x004cef00
    void resize(unsigned int n)                                // 0x0050da10
    {
        if (n > size()) {
            Entry value;
            value.a = 0;
            value.b = 0;
            unsigned int diff = n - size();
            Entry* pos = mpEnd;
            insert(pos, diff, value);
        } else {
            erase(mpBegin + n, mpEnd);
        }
    }
};
struct SkinBuildData {                                         // 0x94-byte "Skinner" element
    unsigned int mId;                                          // +0
    unsigned int mGroup;                                       // +4
    char pad08[0x58 - 8];
    float mMinU, mMaxU, mMinV, mMaxV;                          // +0x58
    int mZero;                                                 // +0x68
    char pad6c[0x94 - 0x6c];
    SkinBuildData();                                           // 0x004cbdf0
    SkinBuildData(const SkinBuildData& o);                     // 0x00508320
    ~SkinBuildData();                                          // 0x00507b30
    SkinBuildData& operator=(const SkinBuildData& o);          // 0x0050a9e0
};
struct VecP_s0050_9f50 {                                                  // vector of element pointers
    SkinBuildData** mpBegin; SkinBuildData** mpEnd; SkinBuildData** mpCap; SpAlloc mAlloc;
    unsigned int size() const { return mpEnd - mpBegin; }
    void push_back(SkinBuildData* const& v);                   // 0x00454860
};
template <int N> inline void ScratchSlots() { unsigned int slots[N]; }
inline void FillEntries(Entry* first, Entry* last, const Entry& value)
{
    for (; first != last; ++first)
        *first = value;
}
struct SlotTable {
    char pad00[8];
    VecV mVerts;            // +0x08
    char pad1c[0x58 - 0x1c];
    VecU_s0050_9f50 mIndices;          // +0x58
    VecU_s0050_9f50 mCornerVerts;      // +0x6c  per-corner vertex index, read by Adjacent
    VecU_s0050_9f50 mEdgeSlots;        // +0x80
    VecU_s0050_9f50 mAdjacent;         // +0x94
    char padA8[0xe4 - 0xa8];
    VecP_s0050_9f50 mGroups;           // +0xe4
    char padf8[0x110 - 0xf8];
    VecU_s0050_9f50 mFaceMark;         // +0x110
    char pad124[0x1b8 - 0x124];
    VecE mSlots;            // +0x1b8
    char pad1cc[0x200 - 0x1cc];

    void InsertEdge(int a, int b, uint32_t* key);          // @ 0x00509f50
    uint8_t Adjacent(int a, int b, int c, int d);          // @ 0x0050a920
    int FaceHelper(int face);                              // @ 0x0050a730

    // @ 0x0050a9e0
    void* CopyRecord(void** src);

    int Insert(int idx, SkinBuildData* key, int slot);      // @ 0x00509c80

    // @ 0x0052e640
    uint8_t Check(int face, int edge, SkinBuildData* group);

    // @ 0x0050a0a0
    void BuildFaces();
};
void SlotTable::InsertEdge(int a, int b, uint32_t* key)
{
    unsigned int av = (unsigned int)a;
    ((VecU_s0050_9f50*)((char*)key + 8))->push_back(av);
    uint32_t idx = (uint32_t)(a * 3 + b);
    signed char c = gCode3[idx % 3];
    int i = (int)(signed char)gOff3[idx % 3] + (int)idx;
    uint32_t* e = (uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + i * 4) * 8);
    if (*e == *key)
        *(uint32_t*)(*(int*)((char*)this + 0x80) + i * 4) = e[1];
    else
        Insert(i, (SkinBuildData*)key, -1);
    *(uint32_t*)(*(int*)((char*)this + 0x80) + idx * 4) =
        *(uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + idx * 4) * 8 + 4);
    *(uint32_t*)(*(int*)((char*)this + 0x80) + ((int)c + (int)idx) * 4) =
        *(uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + ((int)c + (int)idx) * 4) * 8 + 4);
    *(uint32_t*)(*(int*)((char*)this + 0x110) + a * 4) = ~*key;
}
uint8_t SlotTable::Adjacent(int a, int b, int c, int d)
{
    unsigned int x1 = (unsigned int)(a * 3 + b);
    unsigned int x2 = (unsigned int)(a * 3 + (int)(((unsigned int)b + 1u) % 3u));
    unsigned int x3 = (unsigned int)(c * 3 + d);
    unsigned int x4 = (unsigned int)(c * 3 + (int)(((unsigned int)d + 1u) % 3u));
    unsigned int* t = mCornerVerts.mpBegin;
    // Retail writes only al; the high byte of eax is whatever the last comparison left there
    // (index x4 when the first test fails, t[x2] when the second test runs).  Keep v2 in a
    // local so the /Od codegen leaves it in eax, reproducing the caller-visible eax&0xffff.
    if (t[x1] != t[x4])
        return 0;
    unsigned int v2 = t[x2];
    unsigned int r = (v2 == t[x3]) ? 1u : 0u;
    return (uint8_t)((v2 & 0xffffff00u) | r);
}
V3* __cdecl AbsV3(V3* out, const V3* in);  // 0x0050a880 (defined below; used by a stub's inline body)
int SlotTable::FaceHelper(int face)
{
    const V3* base = (const V3*)mVerts.mpBegin;
    unsigned int* tab = mIndices.mpBegin;
    const V3* p0 = base + tab[face * 3];
    const V3* p1 = base + tab[face * 3 + 1];
    const V3* p2 = base + tab[face * 3 + 2];
    V3 d2, d1, cross, abs;
    SubV3(&d2, p2, p0);
    SubV3(&d1, p1, p0);
    CrossV3(&cross, &d1, &d2);
    AbsV3(&abs, &cross);
    int idx = DominantAxis(&abs);
    float c = idx == 0 ? cross.x : (idx == 1 ? cross.y : cross.z);
    return idx * 2 + (c < 0.0f ? 1 : 0);
}
void CopyRangeA(const void* src);   // vector<float>::operator=
void CopyRangeB(const void* src);   // 0x0050db60
void CopyRangeC(const void* src);   // 0x0050dea0
void* SlotTable::CopyRecord(void** src)
{
    void** dst = (void**)this;
    dst[0] = src[0];
    dst[1] = src[1];
    CopyRangeA(src + 2);
    CopyRangeA(src + 7);
    CopyRangeA(src + 0xc);
    CopyRangeB(src + 0x11);
    dst[0x16] = src[0x16];
    dst[0x17] = src[0x17];
    dst[0x18] = src[0x18];
    dst[0x19] = src[0x19];
    dst[0x1a] = src[0x1a];
    CopyRangeA(src + 0x1b);
    CopyRangeC(src + 0x20);
    return this;
}
// ---- items of slice s00509f50 end

// ---- items of slice s0050aac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float a, float b) { x = a; y = b; }
    float& operator[](int i) { return (&x)[i]; }
};
Vector2& operator+=(Vector2& a, const Vector2& b);                   // 0x0050E570
Vector2& operator*=(Vector2& a, const float& s);                      // 0x0050D020
struct UVChart;
struct UVChartCompare;
namespace eastl {
struct sp_vector_allocator_s0050_aac0 {
    sp_vector_allocator_s0050_aac0() {}
    sp_vector_allocator_s0050_aac0(const sp_vector_allocator_s0050_aac0& x);               // 0x00429360
};
}
namespace eastl {
template <class T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace eastl {
template <class T> inline void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
}
namespace eastl {
template <class T> inline void iter_swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}
}
namespace eastl {
template <class T> inline void reverse(T* first, T* last)
{
    for (; first < --last; ++first)
        eastl::iter_swap(first, last);
}
}
namespace eastl {
template <class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}
}
namespace eastl {
void quick_sort(uint32_t* first, uint32_t* last);                    // 0x0050F0D0
}
namespace eastl {
template <class T> inline void sort(T* first, T* last) { quick_sort(first, last); }
}
namespace eastl {
void quick_sort(UVChart** first, UVChart** last, UVChartCompare compare);  // 0x0050EBE0
}
namespace eastl {
template <class T, class C> inline void sort(T* first, T* last, C compare) { quick_sort(first, last, compare); }
}
namespace eastl {
uint32_t* unique(uint32_t* first, uint32_t* last);                   // 0x0050E4B0
}
namespace eastl {
template <class T>
class vector_s0050_aac0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0050_aac0 mAllocator;

    vector_s0050_aac0(const sp_vector_allocator_s0050_aac0& allocator = sp_vector_allocator_s0050_aac0())
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
    vector_s0050_aac0(const vector_s0050_aac0& x);                                         // 0x0050D440 (UVChart*)
    ~vector_s0050_aac0()
    {
        destruct(mpBegin, mpEnd);
        DoFree();
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return *(mpBegin + n); }
    void reserve(unsigned int n);                                    // 0x004E0880
    void push_back(const T& value);                                  // 0x00454860 (uint32_t)
    T* erase(T* first, T* last);                                     // 0x004769B0 (uint32_t)
    void clear() { erase(mpBegin, mpEnd); }
    void DoFree();                                                   // 0x00425990
};
}
namespace eastl {
template <class T, int N>
class fixed_vector_s0050_aac0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[(N * sizeof(T)) / 4];

    fixed_vector_s0050_aac0();                                                  // 0x0041CFE0 (UVChart*, 16)
    fixed_vector_s0050_aac0(unsigned int n);                                    // 0x0050CEC0 (UVShelf, 16)
    ~fixed_vector_s0050_aac0();      // 4209b0 (UVChart*) / 50e290 (UVShelf): left to call alignment
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return *(mpBegin + n); }
    void push_back(const T& value);                                  // 0x0050E410 (UVShelf)
};
}
struct UVChartPoint {
    uint32_t pad00[3];
    Vector2 mUV;                                // +0xc
};
struct UVChart {
    uint32_t pad00[2];
    eastl::vector_s0050_aac0<uint32_t> mTriangles;         // +0x8  triangle numbers
    uint32_t pad18[(0x44 - 0x18) / 4];
    eastl::vector_s0050_aac0<UVChartPoint> mPoints;        // +0x44
    uint32_t pad54;
    float mLeft;                                // +0x58
    float mRight;                               // +0x5c
    float mBottom;                              // +0x60
    float mTop;                                 // +0x64
    uint32_t mFlags;                            // +0x68  bit 0: rotated by 90 degrees
    void Rotate();                                                   // 0x0050BC80
};
struct UVChartCompare {
    bool operator()(const UVChart* a, const UVChart* b) const;
};
struct UVShelf {
    eastl::fixed_vector_s0050_aac0<UVChart*, 16> mCharts;  // +0x0
    float mWidth;                               // +0x58
    float mHeight;                              // +0x5c
    float mOffset;                              // +0x60
    UVShelf() { mWidth = 0.0f; mHeight = 0.0f; mOffset = 0.0f; }
    void Add(UVChart* chart, float width);                           // 0x0050BD10
};
class cUVAtlas {
public:
    uint32_t pad00[0x30 / 4];
    eastl::vector_s0050_aac0<Vector2> mUVs;                // +0x30
    uint32_t pad40[(0x80 - 0x40) / 4];
    eastl::vector_s0050_aac0<uint32_t> mIndices;           // +0x80
    uint32_t pad90[(0xe4 - 0x90) / 4];
    eastl::vector_s0050_aac0<UVChart*> mCharts;            // +0xe4

    void PackCharts(float padding);
};
// ---- items of slice s0050aac0 end

// ---- items of slice s0050d750 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s0050_d750() { unsigned int s[N]; }
template <int N> inline void ScratchPad() { unsigned int scratch[N]; }
void EASTL_allocator_deallocate(void* p);                                                    // 0x00f47380
inline void DeleteElemConditional(void* p, int flags)
{
    if (flags & 1)
        EASTL_allocator_deallocate(p);
}
template <class In, class Out>
inline Out CopyImpl(In first, In last, Out dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}
template <class In, class Out>
inline Out Copy(In first, In last, Out result)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return CopyImpl(first, last, result);
}
struct V2 { float x, y; V2() {} V2(float a, float b) : x(a), y(b) {} };
inline int* AdjacentFind(int* first, int* last)
{
    if (first != last) {
        int* i = first;
        for (++i; i != last; ++i) {
            if (*first == *i)
                return first;
            first = i;
        }
    }
    return last;
}
struct P2 { int first; int second; };
struct Vec8_s0050_d750 {
    P2* mpBegin;      // 0x00
    P2* mpEnd;        // 0x04
    P2* mpCapacity;   // 0x08
    uint32_t mAlloc;  // 0x0c

    P2* AllocCopy(uint32_t n, const P2* first, const P2* last);   // 0x0056a0e0
    void DoInsertValues(P2* position, uint32_t n, const P2& value);  // 0x004cef00
    void insert(P2* position, uint32_t n, const P2& value) { ScratchPad<6>(); DoInsertValues(position, n, value); }
    void EraseRange(P2* first, P2* last);                            // 0x00530c80

    Vec8_s0050_d750& operator=(const Vec8_s0050_d750& x);
    P2* erase(P2* position);
    void resize(uint32_t n);
};
P2* __cdecl UninitCopy8(P2* first, P2* last, P2* dest);   // 0x004d0960
inline void DoFree8(P2* p)
{
    if (p && ((uint32_t*)p)[-1]) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}
struct T12 { uint32_t a, b, c; };
struct Vec12_s0050_d750 {
    T12* mpBegin;
    T12* mpEnd;
    T12* mpCapacity;
    uint32_t mAlloc;

    T12* AllocCopy(uint32_t n, const T12* first, const T12* last);   // 0x0056a140
    Vec12_s0050_d750& operator=(const Vec12_s0050_d750& x);
};
T12* __cdecl UninitCopy12(T12* first, T12* last, T12* dest);   // 0x0050eb40
inline void DoFree12(T12* p)
{
    if (p && ((uint32_t*)p)[-1]) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}
struct FixedVec {
    uint32_t* mpBegin;    // 0x00
    uint32_t* mpEnd;      // 0x04
    uint32_t* mpCapacity; // 0x08
    uint32_t mAlloc[3];   // 0x0c
    uint32_t mBuf[16];    // 0x18
    void Destroy();       // 0x004c0b80
    __forceinline ~FixedVec()
    {
        for (uint32_t* q = mpBegin; q < mpEnd; ++q) {}
        Destroy();
        DeleteElemConditional(this, 0);
    }
};
struct Base100 {
    FixedVec vec;         // 0x00
    Base100();            // 0x0041cfe0
    Base100(const Base100&);  // 0x0050e5f0
};
struct Elem100 : Base100 {
    float f58, f5c, f60;  // 0x58
    Elem100() : f58(0), f5c(0), f60(0) {}
    Elem100(const Elem100& x) : Base100(x), f58(x.f58), f5c(x.f5c), f60(x.f60) { ScratchSlots_s0050_d750<6>(); }
    ~Elem100() { ScratchSlots_s0050_d750<6>(); }
};
struct VecBase {
    Elem100* mpBegin;
    Elem100* mpEnd;
    Elem100* mpCapacity;
    uint32_t mAlloc;
    ~VecBase();           // 0x0050f070
};
struct Vec100 : VecBase {
    void DoInsertValues(Elem100* position, uint32_t n, const Elem100& value);  // 0x0050fc30
    void EraseRange(Elem100* first, Elem100* last);                            // 0x0050eca0
    void DoInsertValue(Elem100* position, const Elem100& value);               // 0x0050ed90

    ~Vec100();
    void resize(uint32_t n);
    void push_back(const Elem100& value);
};
// ---- items of slice s0050d750 end

// ---- items of slice s0050e850 begin (TODO(rewrite): local stubs, replace by canonical classes)
void QuickSort0E(int* first, int* last, int n, uint8_t cmp);   // 0x0050f950
void QuickSort1E(int* first, int* last, int n);                 // 0x005100c0
void InsertionSortA(int* first, int* last, uint8_t cmp);       // 0x0050fa10
void InsertionSortB(int* first, int* last, uint8_t cmp);       // 0x0050fb30
void InsertionSortC(int* first, int* last);                    // 0x00510240
void InsertionSortD(int* first, int* last);                    // 0x005102d0
// ---- items of slice s0050e850 end

// ---- items of slice s00b25c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t g_emptyString16[];        // 0x01667bac (eastl::gEmptyString16)
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)
void  __cdecl FUN_00f47380(void* pBlock);                        // 0x00f47380 operator delete[]
struct cWString {
    const wchar_t* mpBegin;             // +0x00
    const wchar_t* mpEnd;               // +0x04
    const wchar_t* mpCapacity;          // +0x08
    uint32_t       mPad0c;              // +0x0c
    cWString()
    {
        mpCapacity = g_emptyString16 + 1;
        mpBegin = g_emptyString16;
        mpEnd = g_emptyString16;
    }
    ~cWString()                          // inline in the original
    {
        if ((int)(((uint32_t)mpCapacity - (uint32_t)mpBegin) & 0xfffffffeU) > 2 && mpBegin != 0)
            FUN_00f47380((void*)mpBegin);
    }
};
class cSPUIStringConfig {
public:
    cSPUIStringConfig();
    ~cSPUIStringConfig();                                        // 0x00b26db0
    cWString mStr00;                                            // +0x00
    cWString mStr10;                                            // +0x10
    cWString mStr20;                                            // +0x20
    uint32_t mZero30[20];                                       // +0x30 (fields cleared to zero)
    uint32_t mPad80[3];                                         // +0x80
    uint32_t mAllocatorType;                                    // +0x8c (= 4)
    uint32_t mZero90;                                           // +0x90
    uint32_t mPad94[3];                                         // +0x94
    uint32_t mZeroA0;                                           // +0xa0
    uint32_t mZeroA4;                                           // +0xa4
    uint32_t mZeroA8;                                           // +0xa8
    uint8_t  mFlagAc;                                           // +0xac
    uint8_t  mFlagAd;                                           // +0xad
    uint8_t  mPadAe[2];                                         // +0xae
    uint32_t mZeroB0;                                           // +0xb0
    uint32_t mZeroB4;                                           // +0xb4
    uint32_t mZeroB8;                                           // +0xb8
};
// ---- items of slice s00b25c30 end

// @ 0x004544d0
unsigned* RbUIntMap2::find_or_insert(const unsigned* key)
{
    RbIter found;
    find(&found, key);
    RbIter end;
    end.assign((RbNode*)&mAnchor);
    if (found.mpNode == end.mpNode || *key < *found.value()) {
        // not present: build the value and insert it at the lower bound
        NodeVec scratchA;
        scratchA.Construct();
        MapValue value;
        value.mKey = *key;
        value.mValue = 0;
        NodeVec scratchB;
        scratchB.ConstructFrom(scratchA);
        RbIter out;
        insert(&out, found, &value);
        found = out;
        // the element destructors of both scratch vectors run inline (trivial 8-byte slots) before the storage is freed
        for (char* p = (char*)scratchB.mpBegin; p < (char*)scratchB.mpEnd; p += 8) {}
        scratchB.Destroy();
        for (char* p = (char*)scratchA.mpBegin; p < (char*)scratchA.mpEnd; p += 8) {}
        scratchA.Destroy();
    }
    return found.value() + 1;
}

// @ 0x004558a0
void SPVecU32_s004553b0::VectorInsertU32(unsigned* position, const unsigned& value)
{
    if (mEnd != mCapacity) // If size < capacity ...
    {
        // We need to take into account the possibility that value may come from within the vector itself.
        const unsigned* pValue = &value;
        if ((pValue >= position) && (pValue < mEnd)) // If value comes from within the range to be moved...
            ++pValue;
        ::new(mEnd) unsigned(*(mEnd - 1));
        eastl_copy_backward(position, mEnd - 1, mEnd); // We need copy_backward because of potential overlap issues.
        *position = *pValue;
        ++mEnd;
    }
    else // else (size == capacity)
    {
        const unsigned nPrevSize = (unsigned)(mEnd - mBegin);
        const unsigned nNewSize  = eastl_GetNewCapacity(nPrevSize);
        unsigned* const pNewData = eastl_DoAllocate<unsigned>(&mAllocator, nNewSize);

        unsigned* pNewEnd = eastl_uninitialized_copy_ptr(mBegin, position, pNewData);
        ::new(pNewEnd) unsigned(value);
        pNewEnd = eastl_uninitialized_copy_ptr(position, mEnd, ++pNewEnd);

        eastl_DoFree(mBegin, (unsigned)(mCapacity - mBegin));

        mBegin    = pNewData;
        mEnd      = pNewEnd;
        mCapacity = pNewData + nNewSize;
    }
}

// @ 0x00455cf0
int* FixedC::InitFixed(void* p)
{
    ((int*)this)[0] = 0;
    ((int*)this)[1] = 0;
    ((int*)this)[2] = 0;
    ((int*)this)[5] = 0;
    ((int*)this)[0] = (int)((int*)this + 6);
    ((int*)this)[1] = ((int*)this)[0];
    ((int*)this)[2] = ((int*)this)[0] + 0x40;
    FUN_0050d750(p);
    return (int*)this;
}

// @ 0x004763a0
E8* UninitCopy8Destruct(E8* first, E8* last, E8* dest)
{
    E8* result = dest;
    for (E8* p = first; p != last; ++p, ++result) {
        if (result) *result = *p;
    }
    for (E8* q = first; q != last; ++q) {}
    return result;
}

// @ 0x00477930
void EditorHandles::Update(HandleState* st)
{
    bool bTemp = false;
    ModelObj* model = mpModel;
    HandleArrays* a = &arrays;
    char* recs = mpData->begin;
    int nCount = (int)((mpData->end - mpData->begin) / 0x8c);
    int nDone = 0;
    int idx = st->mnNext;
    ShortIdx4 sv;
    float one4[4];
    while (nDone < 4 && idx < nCount * 2) {
        int bBack = 0;
        int slot = idx;
        if (slot >= nCount) {
            bBack = 1;
            slot = slot - nCount;
        }
        if (a->present.mpBegin[slot] != 0) {
            short* rec = (short*)(recs + slot * 0x8c);
            bool hasRef = a->res.mpBegin[slot] != 0;
            if (bBack == 1) {
                if (hasRef) {
                    int n = CountTarget(a->res.mpBegin[slot], 5);
                    if (n + mnBase > 0x40) {
                        DropRange r;
                        int b0 = mnBase;
                        r.count = mnEnd - mnBase;
                        r.start = b0;
                        sink.Add(&r);
                        mnBase = 0;
                        unsigned c1 = (unsigned)model->indexCount();
                        indexCounts.push_back(c1);
                        unsigned c2 = (unsigned)model->triCount();
                        triCounts.push_back(c2);
                    }
                    InstantiateModel(a->res.mpBegin[slot], model, (int)&model->obj84, (void*)mnBase);
                    RefObj* tg = a->targets.mpBegin[slot];
                    RefObj* rf = a->refs.mpBegin[slot];
                    cSPTransform_s0047_7930* xa = &a->xfA.mpBegin[slot];
                    {
                        Elem7c e(*xa, rf, tg);
                        elems.push_back(e);
                    }
                    ((cSPTransform_s0047_7930&)elems.mpEnd[-1]) = a->xfB.mpBegin[slot];
                    elems.mpEnd[-1].t.Invert();
                    mnBase = mnBase + n;
                    mnEnd = mnEnd + n;
                } else if (((char*)rec)[0xa] != 0) {
                    Elem7c e;
                    elems.push_back(e);
                }
            }
            ThreadedObject* res;
            if (bBack == 0) {
                res = hasRef ? 0 : a->present.mpBegin[slot];
            } else {
                ThreadedObject* tmp = 0;
                ThreadedObject** pp;
                if (!hasRef) {
                    bTemp = true;
                    pp = &tmp;
                } else {
                    pp = &a->res.mpBegin[slot];
                }
                res = *pp;
                if (bTemp) {
                    bTemp = false;
                    if (tmp) tmp->Release();
                }
            }
            if (res) {
                int tri0 = model->triCount();
                unsigned uv0 = model->uvCount();
                if (bBack == 0 && fixedRef.empty())
                    ApplyResource(res, model, 0);
                else if (bBack == 0)
                    ApplyResource(res, model, (char*)fixedRef.mpBegin + slot * 0x38);
                else
                    ApplyResource(res, model, &a->xfB.mpBegin[slot]);
                int tri1 = model->triCount();
                unsigned uv1 = model->uvCount();
                float* rc = (float*)((char*)a->rects.mpBegin + *rec * 0x10);
                for (unsigned j = uv0; j < uv1; ++j) {
                    float* uv = model->uvBegin + j * 2;
                    uv[0] = (rc[2] - rc[0]) * uv[0];
                    uv[1] = (rc[3] - rc[1]) * uv[1];
                    uv[0] = uv[0] + rc[0];
                    uv[1] = uv[1] + rc[1];
                }
                unsigned r = *rec;
                while (recs[r * 0x8c + 0xb] == 1)
                    r = *(short*)(recs + r * 0x8c + 4);
                int kLimit = 0x40;
                while (r >= 0x40 && *(short*)(recs + r * 0x8c + 4) != -1)
                    r = *(short*)(recs + r * 0x8c + 4);
                sv.v[0] = (short)(r * 3);
                sv.v[1] = 0; sv.v[2] = 0; sv.v[3] = 0;
                ((Obj70*)model->obj70)->Set(tri1, &sv);
                one4[0] = 1.0f; one4[1] = 0.0f; one4[2] = 0.0f; one4[3] = 0.0f;
                ((Obj84*)model->obj84)->Set(tri1, one4);
                nDone = nDone + 1;
            }
        }
        idx = idx + 1;
        st->mnNext = idx;
    }
    if (st->mnNext < nCount * 2) {
        st->Continue(this);
    } else {
        st->mbDone = 1;
        st->Finish(this);
    }
}

// @ 0x00478390
P8* InsertP8(P8* mpBegin, P8*& mpEnd, P8*& mpCapacity, int* mpFixed, P8* position, const P8& value)
{
    if (mpEnd != mpCapacity) {
        const P8* v = &value;
        if (position <= v && v < mpEnd)
            v = (P8*)((char*)v + 8);
        if (mpEnd) *mpEnd = *(mpEnd - 1);
        P8* p = mpEnd;
        P8* q = mpEnd - 1;
        while (q != position) { *--p = *--q; }
        *position = *v;
        ++mpEnd;
    } else {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint newSize = oldSize ? oldSize * 2 : 1;
        P8* pNew = newSize ? (P8*)EASTL_Allocate((char*)mpCapacity + 0xc - 0xc, newSize * 8, 4, 0) : 0;
        P8* p = UninitCopyRange(mpBegin, position, pNew);
        if (p) *p = value;
        P8* pNewEnd = UninitCopyRange(position, mpEnd, p + 1);
        (void)mpFixed;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    }
    return position;
}

// @ 0x00507670
void __fastcall FUN_00507670(Skin* self)
{
    SkinStoreVtable(self, (void*)0x013f18cc);                // derived vtable
    for (unsigned int i = 0; i < self->me4.size(); ++i) {
        Container* el = self->me4[i];
        Container* res = 0;
        if (el != 0) {
            ElementDestroyVectors(el);
            if ((1 & 1) != 0)
                ea_delete(el);
            res = el;
        }
        (void)res;
        self->me4[i] = 0;
    }
    if (self->m164 != 0) {
        void* p = self->m164;
        if (p != 0) {
            Ptr164Destroy(p);
            if ((1 & 1) != 0)
                ea_delete(p);
        }
        self->m164 = 0;
    }
    TouchedRelease8(self->m1b8.mpBegin, self->m1b8.mpEnd, &self->m1b8);
    TouchedRelease4(self->m1a4.mpBegin, self->m1a4.mpEnd, &self->m1a4);
    TouchedRelease4(self->m190.mpBegin, self->m190.mpEnd, &self->m190);
    TouchedRelease4(self->m17c.mpBegin, self->m17c.mpEnd, &self->m17c);
    TouchedRelease4(self->m168.mpBegin, self->m168.mpEnd, &self->m168);
    TouchedRelease4(self->m138.mpBegin, self->m138.mpEnd, &self->m138);
    TouchedRelease8(self->m124.mpBegin, self->m124.mpEnd, &self->m124);
    TouchedRelease4(self->m110.mpBegin, self->m110.mpEnd, &self->m110);
    TouchedRelease4(self->mf8.mpBegin, self->mf8.mpEnd, &self->mf8);
    TouchedRelease4(self->me4.mpBegin, self->me4.mpEnd, &self->me4);
    VSetDestroy(&self->md0);
    TouchedRelease4(self->mbc.mpBegin, self->mbc.mpEnd, &self->mbc);
    TouchedRelease4(self->ma8.mpBegin, self->ma8.mpEnd, &self->ma8);
    TouchedRelease4(self->m94.mpBegin, self->m94.mpEnd, &self->m94);
    TouchedRelease4(self->m80.mpBegin, self->m80.mpEnd, &self->m80);
    VecFDestroy(&self->m6c);
    VecFDestroy(&self->m58);
    Vec24Destroy(&self->m44);
    Vec30Destroy(&self->m30);
    VSetDestroy(&self->m1c);
    VSetDestroy(&self->m08);
    SkinStoreVtable(self, (void*)0x013ef094);                // base refcount vtable
}

// @ 0x00507b30
void __fastcall DestroyVectors(Container* self)
{
    char* base = (char*)self;
    for (uint32_t* p = *(uint32_t**)(base + 0x80); p < *(uint32_t**)(base + 0x84); p += 3) {}
    DestroySubA(base + 0x80);
    for (uint32_t* p = *(uint32_t**)(base + 0x6c); p < *(uint32_t**)(base + 0x70); p += 1) {}
    DestroySubB(base + 0x6c);
    for (uint32_t* p = *(uint32_t**)(base + 0x44); p < *(uint32_t**)(base + 0x48); p += 5) {}
    DestroySubC(base + 0x44);
    for (uint32_t* p = *(uint32_t**)(base + 0x30); p < *(uint32_t**)(base + 0x34); p += 1) {}
    DestroySubB(base + 0x30);
    for (uint32_t* p = *(uint32_t**)(base + 0x1c); p < *(uint32_t**)(base + 0x20); p += 1) {}
    DestroySubB(base + 0x1c);
    for (uint32_t* p = *(uint32_t**)(base + 0x08); p < *(uint32_t**)(base + 0x0c); p += 1) {}
    DestroySubB(base + 0x08);
}

// @ 0x00507c70
Skin::Skin(const Skin& o)
: m08(Alloc()), m1c(Alloc()), m30(Alloc()), m44(Alloc()), m58(Alloc()), m6c(Alloc()),
      m80(Alloc()), m94(Alloc()), ma8(Alloc()), mbc(Alloc()), md0(), me4(Alloc()),
      mf8(Alloc()), m110(Alloc()), m124(Alloc()), m138(Alloc()), m14c(), m164(0),
      m168(Alloc()), m17c(Alloc()), m190(Alloc()), m1a4(Alloc()), m1b8(Alloc())
{
    m08 = o.m08;
    m1c = o.m1c;
    m30 = o.m30;
    m44 = o.m44;
    m58 = o.m58;
    m6c = o.m6c;
    m80 = o.m80;
    m94 = o.m94;
    ma8 = o.ma8;
    mbc = o.mbc;
    m110 = o.m110;
    m138 = o.m138;
    m124 = o.m124;
    me4 = o.me4;
    for (unsigned int i = 0; i < me4.size(); ++i) {
        me4[i] = new("Skinner", 0, 0, 0, 0) Container(*me4[i]);
    }
    m10c = o.m10c;
    m1b8 = o.m1b8;
    m1cc = o.m1cc;
    m190 = o.m190;
    m168.clear();
    m17c.Clear();
}

// @ 0x0050a0a0
void SlotTable::BuildFaces()
{
    unsigned int nTris = mIndices.size() / 3;
    mEdgeSlots.resize(mIndices.size());
    mSlots.resize(mVerts.size());
    Entry tmpl;
    tmpl.a = 0xffffffff;
    FillEntries(mSlots.begin(), mSlots.end(), tmpl);
    ScratchSlots<2>();

    SkinBuildData* region = new("Skinner", 0, 0, 0, 0) SkinBuildData();
    const unsigned int none = 0x7fffffff;
    unsigned int index = mGroups.size();
    ScratchSlots<44>();
    PairSet pending;
    unsigned int qPos;
    unsigned int resume = 0;
    while (1) {
        unsigned int f;
        unsigned int grp;
        int err;
        f = resume;
        if (mFaceMark[f] > index) {
            for (f = 0; f < nTris; ++f) {
                if (mFaceMark[f] <= index)
                    break;
            }
        }
        if (f == nTris)
            break;
        grp = FaceHelper(f);
        *region = SkinBuildData();
        region->mId = index;
        region->mGroup = grp;
        region->mMinU = kFloatMax;
        region->mMaxU = -kFloatMax;
        region->mMinV = kFloatMax;
        region->mMaxV = -kFloatMax;
        region->mZero = 0;
        pending.erase(pending.mpBegin, pending.mpEnd);
        qPos = 0;
        err = Insert(f * 3, region, -1);
        err = Insert(f * 3 + 1, region, -1);
        InsertEdge(f, 0, (uint32_t*)region);
        for (unsigned int i = 0; i < 3; ++i) {
            unsigned int val;
            unsigned int edgeIdx;
            unsigned int otherFace;
            unsigned int adjEdge;
            edgeIdx = f * 3 + i;
            val = mAdjacent[edgeIdx];
            otherFace = val / 3;
            adjEdge = val % 3;
            if (mFaceMark[otherFace] <= index && FaceHelper(otherFace) == grp &&
                Adjacent(f, i, otherFace, adjEdge) && !Check(otherFace, adjEdge, region)) {
                mFaceMark[otherFace] = none;
                pending.push_back(Pair2(otherFace, adjEdge));
            }
        }
        while (qPos < pending.size()) {
            unsigned int side;
            Pair2 pair;
            unsigned int a;
            pair = pending[qPos++];
            a = pair.first;
            side = pair.second;
            InsertEdge(a, side, (uint32_t*)region);
            for (unsigned int m = 0; m < 3; ++m) {
                if (m != side) {
                    unsigned int nbr2;
                    unsigned int offset2;
                    unsigned int word2;
                    unsigned int otherEdge2;
                    offset2 = a * 3 + m;
                    word2 = mAdjacent[offset2];
                    nbr2 = word2 / 3;
                    otherEdge2 = word2 % 3;
                    if (mFaceMark[nbr2] <= index) {
                        if (FaceHelper(nbr2) == grp && Adjacent(a, m, nbr2, otherEdge2) &&
                            !Check(nbr2, otherEdge2, region)) {
                            mFaceMark[nbr2] = none;
                            pending.push_back(Pair2(nbr2, otherEdge2));
                        } else {
                            mFaceMark[nbr2] = index + 1;
                            resume = nbr2;
                        }
                    }
                }
            }
        }
        mGroups.push_back(new("Skinner", 0, 0, 0, 0) SkinBuildData(*region));
        index = index + 1;
    }
    delete region;
}

// @ 0x0050aac0
void cUVAtlas::PackCharts(float padding)
{
    unsigned int chartCount = mCharts.size();
    float totalArea = 0.0f;
    unsigned int i;
    for (i = 0; i < chartCount; ++i) {
        UVChart* chart = mCharts[i];
        chart->mRight += padding;
        chart->mLeft -= padding;
        chart->mTop += padding;
        chart->mBottom -= padding;
        float width = chart->mRight - chart->mLeft;
        float height = chart->mTop - chart->mBottom;
        totalArea += width * height;
        if (width > height) {
            chart->Rotate();
            eastl::swap(width, height);
        }
    }

    float side = sqrtf(totalArea);
    float slack = 1.1f;

    // Fill shelves left to right; a chart that does not fit makes the rest of the list fill
    // the current shelf first, then a new shelf is started.
    eastl::vector_s0050_aac0<UVChart*> charts(mCharts);
    eastl::sort(charts.begin(), charts.end(), UVChartCompare());
    eastl::fixed_vector_s0050_aac0<UVShelf, 16> shelves(1);
    UVShelf* shelf = &shelves[0];
    unsigned int index = 0;
    while (index < charts.size()) {
        UVChart* chart = charts[index];
        while (chart == 0 && index < charts.size() - 1) {
            ++index;
            chart = charts[index];
        }
        if (chart == 0)
            break;
        float width = chart->mRight - chart->mLeft;
        if (shelf->mWidth + width < side * slack) {
            shelf->Add(chart, width);
            ++index;
        } else {
            for (unsigned int j = index + 1; j < charts.size(); ++j) {
                UVChart* other = charts[j];
                if (other != 0) {
                    float otherWidth = other->mRight - other->mLeft;
                    if (shelf->mWidth + otherWidth < side * slack) {
                        shelf->Add(other, otherWidth);
                        charts[j] = 0;
                    }
                }
            }
            shelves.push_back(UVShelf());
            unsigned int shelfCount = shelves.size();
            shelf = &shelves[shelfCount - 1];
        }
    }

    // Interlock shelf pairs: the odd shelf is moved down as far as its charts allow.
    float maxWidth = 0.0f;
    float totalHeight = 0.0f;
    for (i = 0; i < shelves.size() / 2; ++i) {
        UVShelf* lower = &shelves[i * 2];
        UVShelf* upper = &shelves[i * 2 + 1];
        eastl::reverse(lower->mCharts.begin(), lower->mCharts.end());
        float offset = -(lower->mHeight + upper->mHeight);
        unsigned int lowerIndex = 0;
        unsigned int upperIndex = 0;
        float lowerUsed = 0.0f;
        float upperUsed = 0.0f;
        while (lowerIndex < lower->mCharts.size() && upperIndex < upper->mCharts.size()) {
            UVChart* lowerChart = lower->mCharts[lowerIndex];
            UVChart* upperChart = upper->mCharts[upperIndex];
            float lowerWidth = lowerChart->mRight - lowerChart->mLeft;
            float lowerHeight = lowerChart->mTop - lowerChart->mBottom;
            float upperWidth = upperChart->mRight - upperChart->mLeft;
            float upperHeight = upperChart->mTop - upperChart->mBottom;
            float needed = lowerHeight;
            float room = lower->mHeight + upper->mHeight - upperHeight + offset;
            if (needed > room)
                offset += needed - room;
            float lowerLeft = lowerWidth - lowerUsed;
            float upperLeft = upperWidth - upperUsed;
            if (upperLeft > lowerLeft) {
                ++lowerIndex;
                lowerUsed = 0.0f;
                upperUsed += lowerLeft;
            } else if (lowerLeft > upperLeft) {
                ++upperIndex;
                upperUsed = 0.0f;
                lowerUsed += upperLeft;
            } else {
                ++lowerIndex;
                ++upperIndex;
                lowerUsed = 0.0f;
                upperUsed = 0.0f;
            }
        }
        upper->mOffset = offset;
        maxWidth = eastl::max(eastl::max(upper->mWidth, lower->mWidth), maxWidth);
        totalHeight += eastl::max(lower->mHeight + upper->mHeight + upper->mOffset, lower->mHeight);
    }
    if (shelves.size() & 1) {
        unsigned int shelfCount = shelves.size();
        UVShelf* last = &shelves[shelfCount - 1];
        maxWidth = eastl::max(last->mWidth, maxWidth);
        totalHeight += last->mHeight;
    }

    // Move every chart into place and normalize to [0,1].
    eastl::vector_s0050_aac0<uint32_t> vertices;
    float scale = 1.0f / eastl::max(maxWidth, totalHeight);
    float y = 0.0f;
    for (i = 0; i < shelves.size(); ++i) {
        UVShelf* row = &shelves[i];
        float x = 0.0f;
        for (unsigned int k = 0; k < row->mCharts.size(); ++k) {
            UVChart* chart = row->mCharts[k];
            float width = chart->mRight - chart->mLeft;
            float height = chart->mTop - chart->mBottom;
            float dx = x - chart->mLeft;
            float dy = y - chart->mBottom;
            if (i & 1)
                dy += row->mHeight - height + row->mOffset;
            Vector2 delta(dx, dy);

            vertices.clear();
            vertices.reserve(chart->mTriangles.size() * 3);
            unsigned int t;
            for (t = 0; t < chart->mTriangles.size(); ++t) {
                uint32_t tri = chart->mTriangles[t];
                vertices.push_back(mIndices[tri * 3]);
                vertices.push_back(mIndices[tri * 3 + 1]);
                vertices.push_back(mIndices[tri * 3 + 2]);
            }
            eastl::sort(vertices.begin(), vertices.end());
            vertices.erase(eastl::unique(vertices.begin(), vertices.end()), vertices.end());

            bool rotated = (chart->mFlags & 1) ? true : false;
            float flip = chart->mRight + chart->mLeft;
            for (uint32_t* it = vertices.begin(); it != vertices.end(); ++it) {
                Vector2& uv = mUVs[*it];
                if (rotated) {
                    float u = uv[1];
                    uv[1] = uv[0];
                    uv[0] = flip - u;
                }
                uv += delta;
                uv *= scale;
            }
            for (t = 0; t < chart->mPoints.size(); ++t) {
                Vector2& uv = chart->mPoints[t].mUV;
                if (rotated) {
                    float u = uv[1];
                    uv[1] = uv[0];
                    uv[0] = flip - u;
                }
                uv += delta;
                uv *= scale;
            }

            chart->mLeft += dx;
            chart->mLeft *= scale;
            chart->mRight += dx;
            chart->mRight *= scale;
            chart->mBottom += dy;
            chart->mBottom *= scale;
            chart->mTop += dy;
            chart->mTop *= scale;
            chart->mFlags &= ~1u;
            x += width;
        }
        y += row->mHeight + row->mOffset;
    }
}

// @ 0x0050c6c0
void Skin_s0050_c6c0::Append(const Skin_s0050_c6c0& other)
{
    int nVerts = (int)(m08.mpEnd - m08.mpBegin);
    int nNorms = (int)(m1c.mpEnd - m1c.mpBegin);
    int nUvs = (int)(m30.mpEnd - m30.mpBegin);
    int nPieces = (int)(me4.mpEnd - me4.mpBegin);
    unsigned nIdx = (unsigned)(m58.mpEnd - m58.mpBegin);
    unsigned nTris = nIdx / 3;
    int oVerts = (int)(other.m08.mpEnd - other.m08.mpBegin);
    int oIdx = (int)(other.m58.mpEnd - other.m58.mpBegin);
    int totalIdx = (int)(m58.mpEnd - m58.mpBegin) + oIdx;

    m08.insert(m08.mpEnd, other.m08.mpBegin, other.m08.mpEnd);
    m1a4.insert(m1a4.mpEnd, other.m1a4.mpBegin, other.m1a4.mpEnd);
    m1c.insert(m1c.mpEnd, other.m1c.mpBegin, other.m1c.mpEnd);
    m30.insert(m30.mpEnd, other.m30.mpBegin, other.m30.mpEnd);
    m44.insert(m44.mpEnd, other.m44.mpBegin, other.m44.mpEnd);
    ma8.insert(ma8.mpEnd, other.ma8.mpBegin, other.ma8.mpEnd);

    m124.resize((unsigned)(m30.mpEnd - m30.mpBegin));
    for (unsigned i = 0, n = (unsigned)(other.m124.mpEnd - other.m124.mpBegin); i < n; i++) {
        m124.mpBegin[nUvs + i].a = other.m124.mpBegin[i].a + nPieces;
        m124.mpBegin[nUvs + i].b = other.m124.mpBegin[i].b + nVerts;
    }

    m58.resize(totalIdx);
    m6c.resize(totalIdx);
    m80.resize(totalIdx);
    m94.resize(totalIdx);
    for (unsigned i = 0; i < (unsigned)oIdx; i++) {
        m58.mpBegin[nIdx + i] = other.m58.mpBegin[i] + nVerts;
        m6c.mpBegin[nIdx + i] = other.m6c.mpBegin[i] + nNorms;
        m80.mpBegin[nIdx + i] = other.m80.mpBegin[i] + nUvs;
        m94.mpBegin[nIdx + i] = nIdx + other.m94.mpBegin[i];
    }

    ma8.resize((unsigned)(int)(m08.mpEnd - m08.mpBegin) + oVerts);
    for (unsigned i = 0; i < (unsigned)oVerts; i++)
        ma8.mpBegin[nVerts + i] = other.ma8.mpBegin[i] + nIdx;

    if (!other.me4.empty()) {
        int minusOne = -1;
        m138.resize(totalIdx, minusOne);
        me4.resize(other.me4.size() + nPieces);
        for (unsigned j = 0, n = other.me4.size(); j < n; j++) {
            Container_s0050_c6c0* c = new("Skinner", 0, 0, 0, 0) Container_s0050_c6c0(*other.me4.mpBegin[j]);
            for (unsigned k = 0; k < c->m08.size(); k++)
                c->m08.mpBegin[k] = c->m08.mpBegin[k] + nTris;
            c->m00 = c->m00 + nPieces;
            me4.mpBegin[nPieces + j] = c;
        }
        for (unsigned m = 0, n = (unsigned)oIdx / 3; m < n; m++) {
            unsigned v = other.m110.mpBegin[m] - nPieces;
            m110.push_back(v);
        }
    }
    m190.insert(m190.mpEnd, other.m190.mpBegin, other.m190.mpEnd);
}

// @ 0x0050d4e0
uint32_t* __fastcall FloatVec_Assign(uint32_t* self, uint32_t* x)
{
    if (x != self) {
        uint32_t n = (uint32_t)((int)x[1] - (int)*x) >> 2;
        if ((uint32_t)(((int)self[2] - (int)*self) >> 2) < n) {
            uint32_t pNew = GrowCopy(n, (uint32_t*)*x, (uint32_t*)x[1]);
            for (uint32_t p = *self; p < self[1]; p += 4) {}
            if (*self != 0 && *(int*)(*self - 4) != 0)
                ea_delete((void*)*self);
            *self = pNew;
            self[2] = *self + n * 4;
        } else if ((uint32_t)(((int)self[1] - (int)*self) >> 2) < n) {
            MoveInto((void*)*self, (void*)*x, (int)(x[1] - *x));
        } else {
            for (uint32_t d = *self, s = *x; d < self[1]; d += 4, s += 4)
                *(uint32_t*)d = *(uint32_t*)s;
        }
        self[1] = *self + n * 4;
    }
    return self;
}

// @ 0x0050d750
Vec8_s0050_d750& Vec8_s0050_d750::operator=(const Vec8_s0050_d750& x)
{
    if (this != &x) {
        uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if ((uint32_t)(mpCapacity - mpBegin) < n) {
            P2* const pNewData = AllocCopy(n, x.mpBegin, x.mpEnd);
            for (P2* p = mpBegin; p < mpEnd; ++p) {}
            DoFree8(mpBegin);
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if ((uint32_t)(mpEnd - mpBegin) < n) {
            Copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopy8(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Copy(x.mpBegin, x.mpEnd, mpBegin);
            for (P2* p = mpBegin + n; p < mpEnd; ++p) {}
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0050da10
void Vec8_s0050_d750::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), P2());
    } else {
        EraseRange(mpBegin + n, mpEnd);
    }
}

// @ 0x0050dea0
Vec12_s0050_d750& Vec12_s0050_d750::operator=(const Vec12_s0050_d750& x)
{
    if (this != &x) {
        uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if ((uint32_t)(mpCapacity - mpBegin) < n) {
            T12* const pNewData = AllocCopy(n, x.mpBegin, x.mpEnd);
            for (T12* p = mpBegin; p < mpEnd; ++p) {}
            DoFree12(mpBegin);
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if ((uint32_t)(mpEnd - mpBegin) < n) {
            Copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitCopy12(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
        } else {
            Copy(x.mpBegin, x.mpEnd, mpBegin);
            for (T12* p = mpBegin + n; p < mpEnd; ++p) {}
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0050e290
Vec100::~Vec100()
{
    ScratchSlots_s0050_d750<6>();
    for (Elem100* p = mpBegin; p < mpEnd; ++p) {
        FixedVec& v = p->vec;
        for (uint32_t* q = v.mpBegin; q < v.mpEnd; ++q) {}
        v.Destroy();
        DeleteElemConditional(p, 0);
    }
}

// @ 0x0050e410
void Vec100::push_back(const Elem100& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) Elem100(value);
    else
        DoInsertValue(mpEnd, value);
}

// @ 0x0050e4b0
int* Unique(int* first, int* last)
{
    first = AdjacentFind(first, last);
    if (first != last) {
        int* dest(first);
        for (++first; first != last; ++first) {
            if (!(*dest == *first))
                *++dest = *first;
        }
        return ++dest;
    }
    return last;
}

// @ 0x0050e570
V2* AddTo2(V2* out, const V2* a)
{
    V2 r;
    r.x = out->x + a->x;
    r.y = out->y + a->y;
    out->x = r.x;
    out->y = r.y;
    return out;
}

// @ 0x0050ebe0
void SortCmp(int* first, int* last, uint8_t cmp)
{
    if (first != last) {
        int i = 0;
        for (int n = (int)((last - first) >> 2); n != 0; n >>= 1)
            ++i;
        QuickSort0E(first, last, i * 2 - 2, cmp);
        if ((int)((last - first) >> 2) < 0x1d) {
            InsertionSortA(first, last, cmp);
        } else {
            InsertionSortA(first, first + 0x1c, cmp);
            InsertionSortB(first + 0x1c, last, cmp);
        }
    }
}

// @ 0x0050f0d0
void SortDefault(int* first, int* last)
{
    if (first != last) {
        int i = 0;
        for (int n = (int)(last - first); n != 0; n >>= 1)
            ++i;
        QuickSort1E(first, last, i * 2 - 2);
        if ((int)(last - first) < 0x1d) {
            InsertionSortC(first, last);
        } else {
            InsertionSortC(first, first + 0x1c);
            InsertionSortD(first + 0x1c, last);
        }
    }
}

// @ 0x0083cdd0
AppPropsFields::AppPropsFields()
{
    vtbl = vtbl_AppProps;
    mParser = 0;
    mRefCount = 0;
    pad0c = 0;
    mpBucketArray = gAppPropsBuckets;
    mnBucketCount = 1;
    mnElementCount = 0;
    mMin = gAppPropsMin;
    mMax = gAppPropsMax;
    pad28 = 0;
}

// @ 0x00b26d00
cSPUIStringConfig::cSPUIStringConfig()
{
    for (int i = 0; i < 20; ++i)
        mZero30[i] = 0;
    mAllocatorType = 4;
    mZero90 = 0;
    mZeroA0 = 0;
    mZeroA4 = 0;
    mZeroA8 = 0;
    mFlagAc = 0;
    mFlagAd = 0;
    mZeroB0 = 0;
    mZeroB4 = 0;
    mZeroB8 = 0;
}
