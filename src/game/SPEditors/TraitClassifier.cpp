// src/game/SPEditors/TraitClassifier.cpp -- migrated from slice(s) s0056d2b0, s0056c570, s0056fb90, s0056df80, s0056b680, s0056a7b0 by tools/migrate/rewrite.py
// Object file: SPEditors/TraitClassifier.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Traits/cFeatureVector.h"
#include "SP/Traits/cID.h"
#include "SP/cPropertyManager.h"
#include "SP/cString.h"
#include <math.h>
#include <xmmintrin.h>   // switches /arch:SSE scalar float codegen to SSE at /Od
#include "SP/Traits/cAuthorClassifier.h"
#include <string.h>
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// unnamed retail callees and globals (address in the comment)
extern wchar_t g_emptyWStr[];   // 0x01667bac

// ---- items of slice s0056a7b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
struct PList {                       // cPropertyList (refcounted)
    virtual void AddRef();           // 0x00
    virtual void Release();          // 0x04
};
struct PListRefInline {
    PList* mpObject;
    PListRefInline() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    ~PListRefInline() { if (mpObject) mpObject->Release(); }
    PList* get() const { return mpObject; }
    PList** AsPointer()
    {
        if (mpObject) {
            PList* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};
class cPropertyManager_s0056_a7b0 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PList** ppList);   // 0x2c
};
namespace SP {
class cString_s0056_a7b0 {
public:
    cString_s0056_a7b0();                         // 0x006b5060
    ~cString_s0056_a7b0();                        // 0x006b5240
    const wchar_t* GetText();          // 0x006b55c0
private:
    uint32_t mData[5];
};
}
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WString() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WString() { FreeBuffer(); }
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { const wchar_t* p0 = mpBegin; return p0; }
    void FreeBuffer();                // @ 0x004237d0
    static wchar_t kEmpty[];          // 0x01667bac
};
struct WStrB {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    WStrB() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; Init(); }
    ~WStrB() { FreeBuffer(); }
    void Init();                      // @ 0x0045dac0
    void FreeBuffer();                // @ 0x004237d0
};
struct AnnotN {                       // cAnnotation with the inline default ctor
    float value;
    WStrB str;
    AnnotN() {}
};
struct Annot {
    float value;
    WString str;
    Annot() { InitEmpty(); }
    Annot(AnnotN& src);               // @ 0x0056b020 (copy)
    void InitEmpty();                 // @ 0x0056afc0
    Annot(Annot& src);                // @ 0x0056b020 (copy)
};
namespace SP {
    cPropertyManager_s0056_a7b0* PropertyManager_s0056_a7b0();                                              // 0x0067de30
}
namespace SP {
    bool GetPropertyAsKey(PList* p, uint32_t id, uint32_t* out3);                     // 0x006a1250
}
namespace SP {
    bool GetPropertyAsText(PList* p, uint32_t id, cString_s0056_a7b0* out);                      // 0x006a1360
}
struct Block { char pad[0x1d8]; };
struct Creature {
    char pad[0x98];
    Block* mpBegin;       // +0x98
    Block* mpEnd;         // +0x9c
};
struct cID { uint32_t cls; uint32_t type; };
struct FVEntry { cID id; float weight; };
struct cFeatureVector_s0056_a7b0 {
    FVEntry* mpBegin;
    FVEntry* mpEnd;
    FVEntry* mpCapacity;
    uint32_t mAllocator;
    uint32_t mPad[2];
    float mLen;                                  // +0x18
    cFeatureVector_s0056_a7b0();                            // @ 0x00571640
    ~cFeatureVector_s0056_a7b0();                           // @ 0x00564470
    float add(const cID& id, float weight);      // @ 0x00571790
};
struct AnnotPair {
    cID first;
    Annot second;
    AnnotPair(const cID& id, Annot& a) : first(id), second(a) {}
};
struct AnnotInsRes { AnnotPair* first; bool second; AnnotInsRes() {} };
struct cAnnotatedFeatureVector {
    char mMap[0x18];
    float mLen;                                                  // +0x18
    AnnotInsRes insert(const AnnotPair& p);                      // @ 0x0056e580
    float Add(const cID& id, Annot a);                           // @ 0x0056aec0
};
struct cBlockTypePercentClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector_s0056_a7b0* fv);            // @ 0x0056b080
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);  // @ 0x0056b120
};
struct V3 {
    float x, y, z;
    V3() {}
    V3(const V3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct V3C : V3 {                    // Vector3 with an out-of-line copy ctor
    V3C(const V3& v);                // @ 0x004098a0
};
V3 operator-(const V3& a, const V3& b);   // @ 0x0041db10
struct M3 { float f[9]; };           // rw::math::fpu::Matrix33Template<float>: plain copy (rep movsd)
M3 operator*(const M3& a, const M3& b);   // @ 0x0041de20
struct Xf {                          // cSPTransform
    uint16_t mFlags;
    uint16_t mModificationCount;
    V3 mTranslation;
    float mScale;
    M3 mRotation;
    Xf();                                                            // @ 0x00409930
    void SetTranslation(const V3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetRotation(M3 m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};
struct Box3 {
    V3 mn;   // +0
    V3 mx;   // +0xc
    Box3();                               // @ 0x00409c00 (BoundingBox reset)
    Box3* AddPoint(const V3& p);          // @ 0x0056aba0
    void Transform(const Xf& t);          // @ 0x00409dd0
};
struct Sizer {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void v14();
    virtual void Vfn54(unsigned inst, unsigned group, float* data, int count, V3* mn, V3* mx);   // +0x54
};
Sizer* GetSizer();                                  // 0x00401010
struct SizedPart {                   // 0x1d8-byte creature part
    uint32_t group;                  // +0
    uint32_t instance;               // +4
    char pad8[8];
    float scale;                     // +0x10
    V3 pos;                          // +0x14
    char pad20[0x38 - 0x20];
    M3 rotA;                         // +0x38
    M3 rotB;                         // +0x5c
    char pad80[0x90 - 0x80];
    int count;                       // +0x90
    float data[1];                   // +0x94
    char padEnd[0x1d8 - 0x98];
};
template <class T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }
struct cTallnessClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    virtual bool ExtractTraits(Creature* c, float** weights, cFeatureVector_s0056_a7b0* fv);      // @ 0x0056a7b0 (0x1c)
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);        // @ 0x0056ad20
};
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    void AllocateSelf(wchar_t* p, wchar_t* q);   // @ 0x00423820
};
struct WStrHolder {
    uint32_t pad0;
    WStr str;
    WStrHolder* InitEmpty();   // @ 0x0056afc0
};
struct WStrSrc {
    float value;
    WStr str;
    WStrSrc* CopyInit(WStrSrc* src);   // @ 0x0056b020
};
struct cEditorRigBlockType {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector_s0056_a7b0* fv);                   // @ 0x0056b2e0
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);        // @ 0x0056b440
};
// ---- items of slice s0056a7b0 end

// ---- items of slice s0056b680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPartCountWeight;     // 0x01473c70 (10.0f)
extern uint32_t gTextureGroup;           // 0x015e45a4

struct Alloc { Alloc() {} };

struct PListRefCall {
    PList* mpObject;
    PListRefCall() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    ~PListRefCall() { if (mpObject) mpObject->Release(); }
    PList* get() const { return mpObject; }
    PList** AsPointer();   // @ 0x0041d870
};
class cPropertyManager_s0056_b680 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PList** ppList);   // 0x2c
};
struct WStr_s0056_b680 {                         // eastl::basic_string<wchar_t>, 16 bytes
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WStr_s0056_b680() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WStr_s0056_b680() { FreeBuffer(); }
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { const wchar_t* p0 = mpBegin; return p0; }
    void FreeBuffer();                // @ 0x004237d0
    static wchar_t kEmpty[];          // 0x01667bac
};
struct WStrSrc_s0056_b680 {                      // weight + description string (by-value arg of cFeatureVector::AddDescribed)
    float value;
    WStr_s0056_b680 str;
    WStrSrc_s0056_b680() { InitEmpty(); }
    WStrSrc_s0056_b680(WStrSrc_s0056_b680& src);            // @ 0x0056b020 (copy)
    void InitEmpty();                 // @ 0x0056afc0
};
struct Feature { uint32_t id; uint32_t value; };
struct cFeatureVector {
    float add(const Feature& f, float weight);          // @ 0x00571790
    float addDescribed(const Feature& f, WStrSrc_s0056_b680 d);    // @ 0x0056aec0
};
namespace SP {
    cPropertyManager_s0056_b680* PropertyManager();                                              // 0x0067de30
}

namespace SP {
    bool GetPropertyAsString16(PList* p, uint32_t id, WStr_s0056_b680* out);                     // 0x006a1400
}
int WStr_Format(WStr_s0056_b680* s, const wchar_t* fmt, ...);                                    // 0x0041e050
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseSens);                // 0x00932f30
inline wchar_t* wfind(wchar_t* first, wchar_t* last, const char& value)
{
    while (first != last && *first != value)
        ++first;
    return first;
}

struct TextureBlock {     // element with +0xd4 key count, +0xf8 key array
    char pad[0xd4];
    uint32_t mnKeys;
    char pad2[0xf8 - 0xd8];
    uint32_t mKeys[1];
};
struct VSet {                            // eastl::vector_set<unsigned> (0x18 bytes)
    uint32_t mb, me, mc, ma, mx, my;
    VSet(const Alloc& = Alloc());        // @ 0x00540470
    VSet(const VSet& o);                 // @ 0x00564690
    ~VSet() { DoDestroyValues(); }
    void DoDestroyValues();              // @ 0x00553fb0
    struct InsRes { uint32_t* it; bool ok; InsRes() {} };
    InsRes insert(const uint32_t& v);    // @ 0x00554020
};
struct cEditorPartCount {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056b680
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056b7d0
};
struct BlockKey { uint32_t k0, k1; BlockKey(uint32_t a, uint32_t b) { k0 = a; k1 = b; } };
struct BlockEntry {                      // hashtable value_type: pair<BlockKey, vector_set<uint>>
    BlockKey first;
    VSet second;
    BlockEntry(const BlockKey& k, const VSet& v) : first(k), second(v) {}
};
struct false_type {};
struct BlockInsRes { uint32_t* node; uint32_t bucket; bool ok; BlockInsRes() {} };
struct BlockHash {                       // eastl::hashtable<BlockKey, ...> at tag+8
    BlockInsRes DoInsertValue(const BlockEntry& v, false_type);   // @ 0x0056e320
};
struct BlockSet {                        // vector_set<uint>
    uint32_t* mb; uint32_t* me;
};
struct cRigBlockTag {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    char pad[4];
    BlockHash mTable;                                                               // +8
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056b9e0
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056bd30
};
struct TexHash {                         // eastl::vector_map<uint, vector_set<uint>> at tag+8
    struct Entry { uint32_t first; VSet second; Entry(uint32_t k, const VSet& v) : first(k), second(v) {} };
    struct R { uint32_t* it; bool ok; R() { it = 0; ok = false; } };
    R insert(const Entry& e);            // @ 0x0056e4d0
};
struct cTextureTag {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    char pad[4];
    TexHash mTable;                                                                 // +8
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056bfa0
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056c2d0
};
// ---- items of slice s0056b680 end

// ---- items of slice s0056df80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int ptrdiff_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line); // 0xf473a0
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
template<int N> inline void ScratchSlots_s0056_df80() { uint32_t s[N]; }
template<> inline void ScratchSlots_s0056_df80<0>() {}
template<class T> struct declined_copy_slots { enum { value = 0 }; };
namespace eastl {
  class allocator_s0056_df80 {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };
}
namespace eastl {
  class hash_allocator {
  public:
    hash_allocator() {}
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };
}
namespace eastl {
  struct true_type {};
}
namespace eastl {
  template<class T> struct less_s0056_df80 { bool operator()(const T& a, const T& b) const { return a < b; } };
}
namespace eastl {
  template<class T> struct equal_to_s0056_df80 { bool operator()(const T& a, const T& b) const { return a == b; } };
}
namespace eastl {
  template<class P> struct use_first_s0056_df80 { const typename P::first_type& operator()(const P& x) const { return x.first; } };
}
namespace eastl {
  template<class T1, class T2> struct pair_s0056_df80 {
    typedef T1 first_type; typedef T2 second_type;
    T1 first; T2 second;
    pair_s0056_df80(const T1& x, const T2& y) : first(x), second(y) {}
    template<class U, class V> pair_s0056_df80(const pair_s0056_df80<U, V>& p) : first(p.first), second(p.second) {}
  };
}
template<class T1, class T2> struct declined_copy_slots<eastl::pair_s0056_df80<T1, T2> > { enum { value = declined_copy_slots<T2>::value }; };
namespace eastl {
  template<class T, class A = allocator_s0056_df80> struct VectorBase_s0056_df80 {
    T* mpBegin; T* mpEnd; T* mpCapacity; A mAllocator;
    VectorBase_s0056_df80() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s0056_df80()
    {
        if(mpBegin)
            EASTLFree(mpBegin, (size_t)(mpCapacity - mpBegin) * sizeof(T));
    }
    void EASTLFree(T* p, size_t n) { mAllocator.deallocate(p, n); }
  };
}
namespace eastl {
  template<class T, class A = allocator_s0056_df80> class vector_s0056_df80 : public VectorBase_s0056_df80<T, A> {
  public:
    typedef VectorBase_s0056_df80<T, A> base_type; typedef T* pointer; typedef T* iterator; typedef T value_type;
    typedef unsigned size_type; typedef vector_s0056_df80<T, A> this_type;
    using base_type::mpBegin; using base_type::mpEnd; using base_type::mpCapacity; using base_type::mAllocator;
    vector_s0056_df80() {}
    vector_s0056_df80(const this_type& x);
    ~vector_s0056_df80();
    this_type& operator=(const this_type& x);
    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    iterator insert(iterator position, const value_type& value);
    void DoInsertValue(iterator position, const value_type& value);
    void DoDestroyValues(pointer first, pointer last)
    {
        for(; first < last; ++first)
            first->~value_type();
    }
    pointer DoAllocate(size_type n) { return n ? (pointer)mAllocator.allocate(n * sizeof(T), 4, 0) : 0; }
    void DoFree(pointer p, size_type n)
    {
        if(p)
            mAllocator.deallocate(p, n);
    }
  };
}
namespace eastl {
  template<class T, class A> vector_s0056_df80<T,A>::~vector_s0056_df80()
  {
    ScratchSlots_s0056_df80<4>();
    DoDestroyValues(mpBegin, mpEnd);
  }
}
namespace eastl {
  template<class T, class A> typename vector_s0056_df80<T,A>::iterator vector_s0056_df80<T,A>::insert(iterator position, const value_type& value)
  {
    const ptrdiff_t n = position - mpBegin;
    if((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new(mpEnd++) value_type((ScratchSlots_s0056_df80<declined_copy_slots<T>::value>(), value));
    return mpBegin + n;
  }
}
namespace eastl {
  template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* result);   // 0x5702c0
}
namespace eastl {
  struct copy_backward_impl {
    template<class BI1, class BI2> static BI2 do_copy(BI1 first, BI1 last, BI2 resultEnd)
    {
        while(last != first)
            *--resultEnd = *--last;
        return resultEnd;
    }
  };
}
namespace eastl {
  template<class BI1, class BI2> inline BI2 copy_backward(BI1 first, BI1 last, BI2 resultEnd)
  {
    const bool cap = false;
    const bool count = false;
    const bool p24 = false;
    return copy_backward_impl::do_copy(first, last, resultEnd);
  }
}
namespace eastl {
  template<class T, class A> void vector_s0056_df80<T,A>::DoInsertValue(iterator position, const value_type& value)
  {
    if(mpEnd != mpCapacity)
    {
        const T* pValue = &value;
        if((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) value_type(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        ScratchSlots_s0056_df80<1>();
        *position = *pValue;
        ++mpEnd;
    }
    else
    {
        const size_type nPrevSize = size_type(mpEnd - mpBegin);
        const size_type nNewSize  = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        pointer const   pNewData  = DoAllocate(nNewSize);
        pointer pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        ScratchSlots_s0056_df80<8>();
        ::new(pNewEnd) value_type(value);
        pNewEnd = uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
        ScratchSlots_s0056_df80<12>();
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
  }
}
namespace eastl {
  template<class FI, class T, class Compare>
  FI lower_bound(FI first, FI last, const T& value, Compare compare)
  {
    int d = (int)(last - first);
    while(d > 0)
    {
        FI  i  = first;
        int d2 = d >> 1;
        i += d2;
        if(compare(*i, value))
        {
            first = ++i;
            d -= d2 + 1;
        }
        else
            d = d2;
    }
    ScratchSlots_s0056_df80<1>();
    return first;
  }
}
namespace eastl {
  template<class K, class C = less_s0056_df80<K>, class A = allocator_s0056_df80, class RAC = vector_s0056_df80<K, A> >
  class vector_set_s0056_df80 : public RAC {
  public:
    C mCompare;   // +0x14
    vector_set_s0056_df80(const vector_set_s0056_df80& x) : RAC(x) {}
    vector_set_s0056_df80& operator=(const vector_set_s0056_df80& x) { RAC::operator=(x); return *this; }
  };
}
namespace eastl {
  template<class Key, class T, class Compare = less_s0056_df80<Key>, class Allocator = allocator_s0056_df80,
           class RAC = vector_s0056_df80<pair_s0056_df80<Key, T>, Allocator> >
  class vector_map_s0056_df80 : public RAC {
  public:
    typedef RAC base_type; typedef Key key_type; typedef pair_s0056_df80<Key, T> value_type;
    typedef typename RAC::iterator iterator;
    class value_compare {
    public:
      Compare mCompare;
      bool operator()(const value_type& a, const value_type& b) const { return mCompare(a.first, b.first); }
      bool operator()(const value_type& a, const Key& b) const { return mCompare(a.first, b); }
      bool operator()(const Key& a, const value_type& b) const { return mCompare(a, b.first); }
    };
    value_compare mValueCompare;   // +0x14
    vector_map_s0056_df80() { ScratchSlots_s0056_df80<1>(); }
    using base_type::begin; using base_type::end;
    iterator lower_bound(const key_type& k) { return eastl::lower_bound(begin(), end(), k, mValueCompare); }
    pair_s0056_df80<iterator, bool> insert(const value_type& value);
    pair_s0056_df80<iterator, iterator> equal_range(const key_type& k);
  };
}
namespace eastl {
  template<class K, class T, class C, class A, class RAC>
  pair_s0056_df80<typename vector_map_s0056_df80<K,T,C,A,RAC>::iterator, bool> vector_map_s0056_df80<K,T,C,A,RAC>::insert(const value_type& value)
  {
    const iterator itLB(eastl::lower_bound(begin(), end(), value, mValueCompare));
    if((itLB != end()) && !mValueCompare(value, *itLB))
        return pair_s0056_df80<iterator, bool>(itLB, false);
    ScratchSlots_s0056_df80<5>();
    return pair_s0056_df80<iterator, bool>(base_type::insert(itLB, value), true);
  }
}
namespace eastl {
  template<class V> struct hash_node_s0056_df80 { V mValue; hash_node_s0056_df80* mpNext; };
}
namespace eastl {
  template<class V> struct hashtable_iterator_base {
    typedef hash_node_s0056_df80<V> node_type;
    node_type*  mpNode;
    node_type** mpBucket;
    hashtable_iterator_base(node_type* pNode, node_type** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
  };
}
namespace eastl {
  template<class V> struct hashtable_iterator : public hashtable_iterator_base<V> {
    typedef hashtable_iterator_base<V> base_type; typedef hash_node_s0056_df80<V> node_type;
    hashtable_iterator(node_type* pNode, node_type** pBucket) : base_type(pNode, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
  };
}
namespace eastl {
  struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
}
namespace eastl {
  struct prime_rehash_policy_s0056_df80 {
    float            mfMaxLoadFactor;
    float            mfGrowthFactor;
    mutable uint32_t mnNextResize;
    pair_s0056_df80<bool, uint32_t> GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd) const; // 0x921440
  };
}
namespace eastl {
  template<class K, class V, class H> class hashtable_s0056_df80 {
  public:
    typedef hash_node_s0056_df80<V> node_type; typedef V value_type; typedef K key_type; typedef unsigned size_type;
    typedef hashtable_iterator<V> iterator; typedef uint32_t hash_code_t;
    // hash_code_base: empty function objects (+0x0..+0x3)
    use_first_s0056_df80<V>        mExtractKey;
    equal_to_s0056_df80<K>         mEqual;
    H                   mH1;
    mod_range_hashing   mH2;
    node_type**         mpBucketArray;    // +0x4
    size_type           mnBucketCount;    // +0x8
    size_type           mnElementCount;   // +0xc
    prime_rehash_policy_s0056_df80 mRehashPolicy;    // +0x10
    hash_allocator      mAllocator;       // +0x1c

    pair_s0056_df80<iterator, bool> DoInsertValue(const value_type& value, true_type);
    node_type* DoAllocateNode(const value_type& value);
    node_type** DoAllocateBuckets(size_type n);                              // 0x567260
    void DoFreeBuckets(node_type** pBucketArray, size_type n)
    {
        if(n > 1)
            mAllocator.deallocate(pBucketArray, n);
    }
    void DoRehash(size_type nNewBucketCount);
    hash_code_t get_hash_code(const key_type& key) const { return (hash_code_t)mH1(key); }
    size_type bucket_index(hash_code_t c, uint32_t nBucketCount) const { return (size_type)mH2(c, nBucketCount); }
    size_type bucket_index(const node_type* pNode, uint32_t nBucketCount) const
    {
        const hash_code_t c = (hash_code_t)mH1(mExtractKey(pNode->mValue));
        return (size_type)mH2(c, nBucketCount);
    }
    node_type* DoFindNode(node_type* pNode, const key_type& k, hash_code_t c) const
    {
        for(; pNode; pNode = pNode->mpNext)
        {
            if(mEqual(k, mExtractKey(pNode->mValue)))
                return pNode;
        }
        return 0;
    }
  };
}
namespace eastl {
  template<class K, class V, class H>
  pair_s0056_df80<typename hashtable_s0056_df80<K,V,H>::iterator, bool> hashtable_s0056_df80<K,V,H>::DoInsertValue(const value_type& value, true_type)
  {
    const key_type&   k     = mExtractKey(value);
    const hash_code_t c     = get_hash_code(k);
    size_type         n     = bucket_index(c, (uint32_t)mnBucketCount);
    node_type* const  pNode = DoFindNode(mpBucketArray[n], k, c);

    if(pNode == 0)
    {
        const pair_s0056_df80<bool, uint32_t> bRehash = mRehashPolicy.GetRehashRequired((uint32_t)mnBucketCount, (uint32_t)mnElementCount, (uint32_t)1);
        node_type* const pNodeNew = DoAllocateNode(value);

        if(bRehash.first)
        {
            n = bucket_index(c, (uint32_t)bRehash.second);
            DoRehash(bRehash.second);
        }

        pNodeNew->mpNext = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;

        return pair_s0056_df80<iterator, bool>(iterator(pNodeNew, mpBucketArray + n), true);
    }
    return pair_s0056_df80<iterator, bool>(iterator(pNode, mpBucketArray + n), false);
  }
}
namespace eastl {
  template<class K, class T, class H> class hash_map_s0056_df80 : public hashtable_s0056_df80<K, pair_s0056_df80<const K, T>, H> {
  public:
    explicit hash_map_s0056_df80(const hash_allocator& allocator_s0056_df80 = hash_allocator());  // 0x5640f0
  };
}
namespace EA {
  template<class T> class RefCountVTemplate_s0056_df80 {
  public:
    RefCountVTemplate_s0056_df80() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s0056_df80();
    virtual int AddRef();
    virtual int Release();
    virtual int RefCount();
    T mnRefCount;   // +0x4
  };
}
namespace SP {
namespace Traits {
  using namespace eastl;
}
}
namespace SP {
namespace Traits {
  typedef vector_s0056_df80<uint32_t> UIntVector;   // copy 0x56b020 (via vector_map<cID, UIntVector>)
}
}
namespace SP {
namespace Traits {
  class cIClassifier_s0056_df80 : public EA::RefCountVTemplate_s0056_df80<int> {
  public:
    cIClassifier_s0056_df80() {}
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void v1c() = 0;
  };
}
}
namespace SP {
namespace Traits {
  typedef vector_set_s0056_df80<uint32_t> TagSet;
}
}
template<> struct declined_copy_slots<SP::Traits::TagSet> { enum { value = 18 }; };      // 0x50d440
template<> struct declined_copy_slots<SP::Traits::UIntVector> { enum { value = 2 }; };   // 0x56b020
namespace SP {
namespace Traits {
  class cRigBlockTag_s0056_df80 : public cIClassifier_s0056_df80 {
  public:
    struct BlockKey {
        unsigned int mnGroup;      // +0x0
        unsigned int mnInstance;   // +0x4
        bool operator==(const BlockKey& x) const { return (mnGroup == x.mnGroup) && (mnInstance == x.mnInstance); }
    };
    struct BlockKeyHash { uint32_t operator()(const BlockKey& k) const { return k.mnGroup ^ k.mnInstance; } };
    typedef hash_map_s0056_df80<BlockKey, TagSet, BlockKeyHash> TagsMap;

    cRigBlockTag_s0056_df80() { ScratchSlots_s0056_df80<1>(); }
    virtual ~cRigBlockTag_s0056_df80();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();

    TagsMap mTagsMap;   // +0x8
  };
}
}
namespace SP {
namespace Traits {
  class cIClassifierFactory {
  public:
    virtual cIClassifier_s0056_df80* Create() = 0;
  };
}
}
namespace SP {
namespace Traits {
  template<class T> class tClassifierFactory : public cIClassifierFactory {
  public:
    virtual cIClassifier_s0056_df80* Create();
  };
}
}
namespace SP {
namespace Traits {
  template<class T> cIClassifier_s0056_df80* tClassifierFactory<T>::Create()
  {
    return new("OTDB", 0, 0, 0, 0) T;
  }
}
}
namespace SP {
namespace Traits {
  typedef vector_map_s0056_df80<uint32_t, cIClassifierFactory*> FactoryMap;
}
}
namespace SP {
namespace Traits {
  struct cNullClassifierSource {
    void* GetClassifier();
  };
}
}
typedef eastl::hashtable_s0056_df80<SP::Traits::cRigBlockTag_s0056_df80::BlockKey, eastl::pair_s0056_df80<const SP::Traits::cRigBlockTag_s0056_df80::BlockKey, SP::Traits::TagSet>, SP::Traits::cRigBlockTag_s0056_df80::BlockKeyHash> RigTagsTable;
template RigTagsTable::node_type* RigTagsTable::DoAllocateNode(const RigTagsTable::value_type&);
template void RigTagsTable::DoRehash(unsigned);
typedef eastl::vector_s0056_df80<eastl::pair_s0056_df80<uint32_t, SP::Traits::TagSet> > TexTagsVector;
template eastl::pair_s0056_df80<SP::Traits::FactoryMap::iterator, SP::Traits::FactoryMap::iterator> SP::Traits::FactoryMap::equal_range(const uint32_t&);
// ---- items of slice s0056df80 end

// ---- items of slice s0056fb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);
struct Vec12 { uint32_t a, b, c; };
struct Vec12Alloc {
    uint32_t mpName;
    void deallocate(void* p, uint32_t n) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct FalseTag { FalseTag() {} };
Vec12* UninitCopy12(const Vec12* first, const Vec12* last, Vec12* dst);        // 0x00475ef0 (cdecl)
inline Vec12* CopyImpl12(const Vec12* first, const Vec12* last, Vec12* result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
inline Vec12* Copy12(const Vec12* first, const Vec12* last, Vec12* result)
{
    const bool bA = false, bC = false, bB = false;
    return CopyImpl12(first, last, result);
}
struct Vec12Vector {
    Vec12* mpBegin;                     // +0
    Vec12* mpEnd;                       // +4
    Vec12* mpCapacity;                  // +8
    Vec12Alloc mAllocator;              // +0xc
    Vec12* DoRealloc(uint32_t n, const Vec12* first, const Vec12* last);   // 0x00475fa0 (thiscall, ret 0xc)
    void DoFree(Vec12* p, uint32_t n)
    {
        if (p && ((int*)p)[-1] != 0)
            mAllocator.deallocate(p, n * sizeof(Vec12));
    }
    void DestroyFrom(Vec12* first)
    {
        for (Vec12* p = first; p < mpEnd; ++p)
            ;
    }
    void DoAssign(const Vec12* first, const Vec12* last, const FalseTag& tag);
};
struct Key { uint32_t a; uint32_t b; };
struct Str16 {                          // eastl::basic_string<wchar_t> (16 bytes with allocator)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    Str16(const Str16& x);              // 0x0056e2d0
};
struct MetaI {                          // float weight + description string
    float f;
    Str16 str;
    MetaI(const MetaI& s) : f(s.f), str(s.str) {}
};
struct MetaO {                          // same layout; copy ctor is the out-of-line one
    float f;
    Str16 str;
    MetaO(const MetaO& s);              // 0x0056b020 (thiscall, ret 4)
};
struct ElemO {
    Key key;
    MetaO meta;
    ElemO(const ElemO& s) : key(s.key), meta(s.meta) {}
};
struct ElemI {                          // 0x1c-byte vector element
    Key key;                            // +0
    MetaI meta;                         // +8
    ElemI(const ElemI& s) : key(s.key), meta(s.meta) {}
    ElemI& operator=(const ElemI& s);   // 0x00570140 (assign)
};
ElemI* UninitCopy(ElemI* first, ElemI* last, ElemI* dst);                 // 0x00570330 (cdecl)
inline ElemI* CopyBackwardImpl(ElemI* first, ElemI* last, ElemI* result)
{
    while (last != first)
        *--result = *--last;
    return result;
}
inline ElemI* CopyBackward(ElemI* first, ElemI* last, ElemI* result)
{
    const bool bA = false, bC = false, bB = false;
    ScratchSlots<4>();
    return CopyBackwardImpl(first, last, result);
}
struct ElemAlloc {
    uint32_t mpName;
    void deallocate(void* p, uint32_t n) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct ElemVec {
    ElemI* mpBegin;                     // +0
    ElemI* mpEnd;                       // +4
    ElemI* mpCapacity;                  // +8
    ElemAlloc mAllocator;               // +0xc
    ElemI* DoAllocate(uint32_t n)
    {
        return n ? (ElemI*)EASTL_Allocate(&mAllocator, n * sizeof(ElemI), 4, 0) : 0;
    }
    void DoFree(ElemI* p, uint32_t n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(ElemI));
    }
    void DoInsertValue(ElemI* position, const ElemI& value);
};
struct Pair8 { uint32_t a; uint32_t b; };
inline bool LessU32(uint32_t a, uint32_t b) { return a < b; }
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key);   // @ 0x005701b0
struct OuterVec {                       // eastl::vector<pair<uint, vector_set<uint>>>
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAlloc;
    void DoDestroyValues();             // 0x00553fb0
};
struct HashNode {
    Key mKey;                           // +0
    OuterVec mValue;                    // +8
    char pad18[8];                      // +0x18
    HashNode* mpNext;                   // +0x20
    ~HashNode() { mValue.DoDestroyValues(); }
};
struct NodeAlloc {
    void deallocate(void* p, uint32_t n) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct HashTable {
    NodeAlloc mAllocator;
    void DoFreeNode(HashNode* pNode)
    {
        pNode->~HashNode();
        ScratchSlots<4>();
        mAllocator.deallocate(pNode, sizeof(HashNode));
    }
    void DoFreeNodes(HashNode** pNodeArray, uint32_t n);
};
// ---- items of slice s0056fb90 end

// ---- items of slice s0056c570 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
struct Feature_s0056_c570 { uint32_t field0; uint32_t field1; };
struct WStrSrc_s0056_c570;
struct cFeatureVector_s0056_c570 {  // @ 0x00571790 / 0x0056aec0
    float add(const Feature_s0056_c570& f, float weight);  // 0x00571790 (cFeatureVector::add)
    float addDescribed(const Feature_s0056_c570& f, WStrSrc_s0056_c570 d);
};
struct PListRefInline_s0056_c570 {
    PList* mpObject;
    PListRefInline_s0056_c570() : mpObject(0) {}
    ~PListRefInline_s0056_c570() { if (mpObject) mpObject->Release(); }
    PList* get() const { return mpObject; }
    PList** AsPointer()
    {
        if (mpObject) {
            PList* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};
struct ResKey { uint32_t instance; uint32_t type; uint32_t group; };
struct IObjectService {              // returned by 0x008de1a0
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool GetResource(ResKey* key, PList** out, int a, int b, int c, int d);   // 0x0c
};
IObjectService* ObjectError();       // 0x008de1a0 (cdecl)
struct Meta {
    int64_t GetAssetKey();           // @ 0x005508a0 (thiscall, edx:eax)
    const wchar_t* GetName();        // @ 0x00550880 (thiscall)
    unsigned GetTagCount();          // @ 0x005509b0 (thiscall)
    unsigned GetCount2();            // @ 0x005508e0 (thiscall)
    const char* GetItem(unsigned i); // @ 0x00550910 (thiscall, ret 4)
    const wchar_t* GetTag(unsigned i);   // @ 0x005509e0 (thiscall, ret 4)
};
uint32_t FNV1_String8(const char* s, uint32_t seed, int caseSens);                    // 0x00932e80
struct WStr_s0056_c570 {                         // eastl::basic_string<wchar_t>, 16 bytes
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WStr_s0056_c570() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WStr_s0056_c570() { FreeBuffer(); }
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { const wchar_t* p0 = mpBegin; return p0; }
    void FreeBuffer();                // @ 0x004237d0
    static wchar_t kEmpty[];          // 0x01667bac
};
struct WStrSrc_s0056_c570 {                      // weight + description string (by-value arg of cFeatureVector::AddDescribed)
    float value;
    WStr_s0056_c570 str;
    WStrSrc_s0056_c570() { InitEmpty(); }
    WStrSrc_s0056_c570(WStrSrc_s0056_c570& src);            // @ 0x0056b020 (copy)
    void InitEmpty();                 // @ 0x0056afc0
};
int WStr_Format(WStr_s0056_c570* s, const wchar_t* fmt, ...);                                    // 0x0041e050
Meta* GetModelInfo(PListRefInline_s0056_c570* r);   // 0x00421f60 (cdecl)
uint32_t FNV1Hash(const void* data, uint32_t length, uint32_t hash);  // 0x00932E50
struct cAuthorClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool ExtractTraits(void* creature, void* weights, cFeatureVector_s0056_c570* features);  // @ 0x0056c570
    bool DescribeTraits(void* creature, void* weights, cFeatureVector_s0056_c570* features);   // @ 0x0056c670
};
struct cMetadataSummarizer {
    bool ExtractParameters(void* a, void* b, cFeatureVector_s0056_c570* features);  // @ 0x0056c7d0
};
struct cAssetMetadata {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool SetMetadata(void* creature, void* weights, cFeatureVector_s0056_c570* features);   // @ 0x0056c910
};
struct cFeedClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool ExtractTraits(void* creature, void* weights, cFeatureVector_s0056_c570* features);  // @ 0x0056cb30
    bool DescribeTraits(void* creature, void* weights, cFeatureVector_s0056_c570* features); // @ 0x0056cc50
};
struct cPropertyManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, struct PropListA** ppList);   // 0x2c
};
cPropertyManager* PropertyManager_s0056_c570();   // 0x0067de30
struct Vec3c { float x, y, z; };
struct Prop {                          // cProperty header
    void* mpData;                      // +0x00
    uint32_t pad4;
    uint32_t mCount;                   // +0x08
    uint32_t pad0c;
    uint16_t mFlags;                   // +0x10
    uint16_t mInline;                  // +0x12
    unsigned Count()
    {
        if (mFlags & 0x30) {
            return mCount;
        } else if (mInline) {
            return 1;
        }
        return 0;
    }
    struct Vec3c* Data();
};
struct PropListA {
    virtual void AddRef();             // 0x00
    virtual void Release();            // 0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool HasProperty(uint32_t id);        // 0x1c
virtual void v20();
virtual void v24();
    virtual Prop* GetProperty(uint32_t id);       // 0x28
};
struct PropListRefA {
    PropListA* mpObject;
    PropListRefA() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    ~PropListRefA() { if (mpObject) mpObject->Release(); }
    PropListA* get() const { return mpObject; }
    PropListA** AsPointer()
    {
        if (mpObject) {
            PropListA* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};
struct TagE { TagE() {} };
inline Vec3c* Prop::Data()
{
    if (mFlags & 0x30) {
        return (Vec3c*)mpData;
    } else if (mInline) {
        return (Vec3c*)this;
    }
    return 0;
}
struct SpVecV3 {
    Vec3c* mpBegin; Vec3c* mpEnd; Vec3c* mpCapacity; unsigned int mAlloc[2];
    Vec3c* erase(Vec3c* first, Vec3c* last);                  // 0x0050f740
    void assign(Vec3c* first, Vec3c* last, TagE tag);         // 0x0056fee0
    void clear() { erase(mpBegin, mpEnd); }
    void assign(Vec3c* first, Vec3c* last) { TagE e; TagE t; TagE m; TagE j; uint32_t s[6]; assign(first, last, j); }
};
struct cSwatchColorLookup {
    SpVecV3 mTabColors;
    cSwatchColorLookup() { mTabColors.mpBegin = 0; mTabColors.mpEnd = 0; mTabColors.mpCapacity = 0; }
    bool Init();   // @ 0x0056cde0
};
struct VecFloat {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    unsigned GetAllocated(const void* a);   // @ 0x0056cf70 (index of nearest colour)
};
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
const Vec3& Vec3Sub(Vec3* out, const Vec3* a, const Vec3* b);   // @ 0x0041db10 cdecl
float VectorLength(const Vec3* v);            // @ 0x0040ae50 cdecl, x87 return
struct Block_s0056_c570 {                       // creature part, 0x1d8 bytes
    char pad0[0xd4];
    uint32_t mnKeys;                 // +0xd4
    uint32_t mKeys[16];              // +0xd8
    Vec3 mColors[1];                 // +0x118
    char pad2[0x1d8 - 0x124];
};
struct Creature_s0056_c570 {
    char pad0[0x0c];
    uint32_t mType;                  // +0x0c
    char pad1[0x38 - 0x10];
    Vec3 mColor0;                    // +0x38
    Vec3 mColor1;                    // +0x44
    Vec3 mColor2;                    // +0x50
    char pad3[0x98 - 0x5c];
    Block_s0056_c570* mpBegin;                  // +0x98
    Block_s0056_c570* mpEnd;                    // +0x9c
};
extern cSwatchColorLookup* gSwatchColors;   // 0x015e4468
struct cTextureClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool ExtractTraits(Creature_s0056_c570* creature, float** weights, cFeatureVector_s0056_c570* features);  // @ 0x0056d080
};
// ---- items of slice s0056c570 end

// ---- items of slice s0056d2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cFeatureVector_s0056_d2b0 { float add(const cID& id, float weight); };   // @ 0x00571790
struct Alloc_s0056_d2b0 { char pad[1]; Alloc_s0056_d2b0() {} };
struct Alloc17 { char pad[1]; Alloc17() {} };
struct Vec3_s0056_d2b0 { float x, y, z; };
struct Block_s0056_d2b0 {                       // creature part, 0x1d8 bytes
    char pad0[0xd4];
    uint32_t mnKeys;                 // +0xd4
    uint32_t mKeys[16];              // +0xd8
    Vec3_s0056_d2b0 mColors[1];                 // +0x118
    char pad2[0x1d8 - 0x124];
};
struct Creature_s0056_d2b0 {
    char pad0[0x0c];
    uint32_t mType;                  // +0x0c
    char pad1[0x20 - 0x10];
    uint32_t mKey0, mKey1, mKey2;    // +0x20
    char pad2[0x38 - 0x2c];
    Vec3_s0056_d2b0 mColor0;                    // +0x38
    Vec3_s0056_d2b0 mColor1;                    // +0x44
    Vec3_s0056_d2b0 mColor2;                    // +0x50
    char pad3[0x98 - 0x5c];
    Block_s0056_d2b0* mpBegin;                  // +0x98
    Block_s0056_d2b0* mpEnd;                    // +0x9c
};
struct SwatchVecBase {
    Vec3_s0056_d2b0* mpBegin; Vec3_s0056_d2b0* mpEnd; Vec3_s0056_d2b0* mpCapacity; uint32_t mAlloc[2];
    SwatchVecBase() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    SwatchVecBase(const Alloc_s0056_d2b0& a);   // 0x00540470
    SwatchVecBase(const Alloc17& a);   // 0x00540470
};
struct cSwatchColorLookupB {
    SwatchVecBase mTabColors;
    cSwatchColorLookupB() {}
    cSwatchColorLookupB(const Alloc_s0056_d2b0& a) : mTabColors(a) {}
    cSwatchColorLookupB(const Alloc17& a) : mTabColors(a) {}
    bool Init();                     // @ 0x0056cde0
    unsigned GetAllocated(const void* a);   // @ 0x0056cf70
};
extern cSwatchColorLookupB* gSwatchColors_s0056_d2b0;   // 0x015e4468
struct WStrB_s0056_d2b0 {                       // eastl::basic_string<wchar_t>; ctor body out of line (0x0045dac0)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    WStrB_s0056_d2b0() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; Init(); }
    WStrB_s0056_d2b0(WStrB_s0056_d2b0& o);                 // 0x0056e2d0 (copy)
    ~WStrB_s0056_d2b0() { FreeBuffer(); }
    void Init();                     // @ 0x0045dac0
    void FreeBuffer();               // @ 0x004237d0
};
struct DescSrc {                     // weight + description (by-value arg of cAnnotatedFeatureVector::Add)
    float value;
    WStrB_s0056_d2b0 str;
    DescSrc() {}
    DescSrc(DescSrc& src);           // @ 0x0056b020 (copy)
};
struct DescSrcI {                    // same layout, implicit copy inlined
    float value;
    WStrB_s0056_d2b0 str;
    DescSrcI(DescSrcI& src) : value(src.value), str(src.str) {}
};
struct WString_s0056_d2b0 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    WString_s0056_d2b0() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WString_s0056_d2b0() { FreeBuffer(); }
    void FreeBuffer();               // @ 0x004237d0
    static wchar_t kEmpty[];         // 0x01667bac
};
struct Annot_s0056_d2b0 {
    float value;
    WString_s0056_d2b0 str;
    Annot_s0056_d2b0() { InitEmpty(); }
    Annot_s0056_d2b0(Annot_s0056_d2b0& src);               // @ 0x0056b020 (copy)
    void InitEmpty();                // @ 0x0056afc0
};
int WStr_Format(void* s, const wchar_t* fmt, ...);   // 0x0041e050
struct cAnnotatedFeatureVector_s0056_d2b0 {
    float Add(const cID& id, DescSrc a);   // @ 0x0056aec0
    float Add(const cID& id, DescSrcI a);   // @ 0x0056aec0
    float Add(const cID& id, Annot_s0056_d2b0 a);     // @ 0x0056aec0
};
struct cRegionColorClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool DescribeTraits(Creature_s0056_d2b0* c, float** weights, cAnnotatedFeatureVector_s0056_d2b0* out);   // 0x0056d2b0
};
struct cBaseColorClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool ExtractTraits(Creature_s0056_d2b0* c, float** weights, cFeatureVector_s0056_d2b0* fv);   // 0x0056d650
    bool DescribeTraits(Creature_s0056_d2b0* c, float** weights, cAnnotatedFeatureVector_s0056_d2b0* out);   // 0x0056d810
};
struct cRegionKeyClassifier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool ExtractTraits(Creature_s0056_d2b0* c, float** weights, cFeatureVector_s0056_d2b0* fv);   // 0x0056da90
};
struct cTextureClassifier_s0056_d2b0 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool DescribeTraits(Creature_s0056_d2b0* c, float** weights, cAnnotatedFeatureVector_s0056_d2b0* out);   // 0x0056dbe0
};
// ---- items of slice s0056d2b0 end

// @ 0x0056a7b0
bool cTallnessClassifier::ExtractTraits(Creature* c, float** weights, cFeatureVector_s0056_a7b0* fv)
{
    bool i = false;
    if (c) {
        Box3 offset;
        SizedPart* x = (SizedPart*)c->mpBegin;
        SizedPart* count = (SizedPart*)c->mpEnd;
        for (; x != count; x++) {
            SizedPart* g = x;
            Box3 left;
            GetSizer()->Vfn54(g->instance, g->group, g->data, g->count, &left.mn, &left.mx);
            Xf list;
            list.SetTranslation(g->pos);
            list.SetRotation(g->rotB * g->rotA);
            list.SetScale(g->scale);
            left.Transform(list);
            offset.AddPoint(left.mn);
            offset.AddPoint(left.mx);
            i = true;
        }
        ScratchSlots<36>();
        V3C item = offset.mx - offset.mn;
        float right = max_(item.x, 0.5f);
        float data = max_(item.y, 0.5f);
        float d = max_(item.z, 0.5f);
        float part, s;
        if (right > data) { part = right; s = data; }
        else { part = data; s = right; }
        cID begin;
        begin.cls = 0x227f195;
        begin.type = 0;
        fv->add(begin, d * 100.0f / part);
        begin.type = 1;
        fv->add(begin, d * 100.0f / s);
        begin.type = 2;
        fv->add(begin, s * 100.0f / part);
    }
    return i;
}

// @ 0x0056aba0
Box3* Box3::AddPoint(const V3& p)
{
    if (mn[0] > p[0]) mn[0] = p[0];
    else if (mx[0] < p[0]) mx[0] = p[0];
    if (mn[1] > p[1]) mn[1] = p[1];
    else if (mx[1] < p[1]) mx[1] = p[1];
    if (mn[2] > p[2]) mn[2] = p[2];
    else if (mx[2] < p[2]) mx[2] = p[2];
    return this;
}

// @ 0x0056ad20
bool cTallnessClassifier::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    cFeatureVector_s0056_a7b0 fv;
    ScratchSlots<32>();
    if (ExtractTraits(c, weights, &fv)) {
        FVEntry* it = fv.mpBegin;
        FVEntry* end = fv.mpEnd;
        for (; it != end; it++) {
            FVEntry* e = it;
            Annot desc;
            switch (e->id.type) {
            case 0:
                WStr_Format(&desc.str, L"(%ls) tall/wide", GetName());
                break;
            case 1:
                WStr_Format(&desc.str, L"(%ls) tall/thin", GetName());
                break;
            case 2:
                WStr_Format(&desc.str, L"(%ls) thin/wide", GetName());
                break;
            default:
                WStr_Format(&desc.str, L"(%ls) Error", GetName());
                break;
            }
            desc.value = it->weight;
            out->Add(e->id, desc);
        }
        return true;
    }
    return false;
}

// @ 0x0056afc0
WStrHolder* WStrHolder::InitEmpty()
{
    WStr* pStr = &str;
    int tmp;
    pStr->mpBegin = 0;
    pStr->mpEnd = 0;
    pStr->mpCapacity = 0;
    pStr->mpBegin = g_emptyWStr;
    pStr->mpEnd = pStr->mpBegin;
    pStr->mpCapacity = pStr->mpBegin + 1;
    return this;
}

// @ 0x0056b020
WStrSrc* WStrSrc::CopyInit(WStrSrc* src)
{
    value = src->value;
    WStr* d = &src->str;
    WStr* s = &str;
    s->mpBegin = 0;
    s->mpEnd = 0;
    s->mpCapacity = 0;
    s->AllocateSelf(d->mpBegin, d->mpEnd);
    return this;
}

// @ 0x0056b080
bool cBlockTypePercentClassifier::ExtractTraits(Creature* c, float** weights, cFeatureVector_s0056_a7b0* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* block = (uint32_t*)t32;
            cID buf;
            buf.cls = 0x1f71e85;
            buf.type = block[1];
            fv->add(buf, (*weights)[t32 - begin]);
        }
    }
    return p30;
}

// @ 0x0056b120
bool cBlockTypePercentClassifier::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* self = c->mpBegin;
        Block* pl = self;
        Block* num = c->mpEnd;
        for (; pl != num && p30; pl++) {
            uint32_t* j = (uint32_t*)pl;
            cID w;
            w.cls = 0x1f71e85;
            w.type = j[1];
            PListRefInline weight;
            bool t = SP::PropertyManager_s0056_a7b0()->GetPropertyList(j[1], j[0], weight.AsPointer());
            if (t) {
                SP::cString_s0056_a7b0 left;
                if (SP::GetPropertyAsText(weight.get(), 0x8f6fc401, &left)) {
                    Annot buf;
                    ScratchSlots<25>();
                    WStr_Format(&buf.str, L"(%ls) %ls", GetName(), left.GetText());
                    buf.value = (*weights)[pl - self];
                    out->Add(w, buf);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b2e0
bool cEditorRigBlockType::ExtractTraits(Creature* c, float** weights, cFeatureVector_s0056_a7b0* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            PListRefInline t25;
            bool p32 = SP::PropertyManager_s0056_a7b0()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                uint32_t n37[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, n37)) {
                    cID buf;
                    buf.cls = 0x4ea801f;
                    buf.type = n37[0];
                    fv->add(buf, (*weights)[t32 - begin]);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b440
bool cEditorRigBlockType::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            ScratchSlots<1>();
            PListRefInline t25;
            bool p32 = SP::PropertyManager_s0056_a7b0()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                WString n37;
                uint32_t buf[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, buf)) {
                    cID owner;
                    owner.cls = 0x4ea801f;
                    owner.type = buf[0];
                    if (n37.empty())
                        WStr_Format(&n37, L"0x%08x", buf[0]);
                    ScratchSlots<1>();
                    AnnotN n6;
                    WStr_Format(&n6.str, L"(%ls) %ls", GetName(), n37.c_str());
                    n6.value = (*weights)[t32 - begin];
                    ScratchSlots<25>();
                    out->Add(owner, n6);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b680
bool cEditorPartCount::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                uint32_t n37[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, n37)) {
                    Feature buf;
                    buf.id = 0x4eab460;
                    buf.value = n37[0];
                    fv->add(buf, kPartCountWeight);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b7d0
bool cEditorPartCount::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            ScratchSlots<1>();
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                WStr_s0056_b680 n37;
                uint32_t buf[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, buf)) {
                    Feature owner;
                    owner.id = 0x4eab460;
                    owner.value = buf[0];
                    if (n37.empty())
                        WStr_Format(&n37, L"0x%08x", buf[0]);
                    WStrSrc_s0056_b680 n6;
                    ScratchSlots<1>();
                    WStr_Format(&n6.str, L"(%ls) %ls", GetName(), n37.c_str());
                    n6.value = kPartCountWeight;
                    ScratchSlots<25>();
                    fv->addDescribed(owner, n6);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b9e0
bool cRigBlockTag::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        result = true;
        Block* first = c->mpBegin;
        Block* it = first;
        Block* last = c->mpEnd;
        for (; it != last && result; it++) {
            uint32_t* e = (uint32_t*)it;
            BlockInsRes res;
            res.node = 0;
            res.bucket = 0;
            res.ok = false;
            {
                VSet tmp;
                BlockEntry ent(BlockKey(e[0], e[1]), tmp);
                res = mTable.DoInsertValue(ent, false_type());
            }
            BlockSet* set = (BlockSet*)((char*)res.node + 8);
            if (res.ok) {
                PListRefCall pl;
                bool ok = SP::PropertyManager()->GetPropertyList(e[1], e[0], pl.AsPointer());
                if (ok) {
                    WStr_s0056_b680 s;
                    if (SP::GetPropertyAsString16(pl.get(), 0x4ebb27e, &s)) {
                        VSet* vs = (VSet*)set;
                        wchar_t* cur = s.mpBegin;
                        wchar_t* tokEnd = cur;
                        wchar_t* end = s.mpEnd;
                        do {
                            tokEnd = wfind(cur, end, '|');
                            *tokEnd = 0;
                            if (tokEnd != cur) {
                                uint32_t h = FNV1_String16(cur, 0x811c9dc5, 1);
                                vs->insert(h);
                                cur = tokEnd + 1;
                            }
                        } while (tokEnd != end && cur != end);
                    }
                }
            }
            uint32_t* p = set->mb;
            uint32_t* pe = set->me;
            for (; p != pe; p++) {
                Feature f;
                f.id = 0x4ebfebd;
                f.value = *p;
                fv->add(f, (*weights)[it - first]);
            }
        }
    }
    return result;
}

// @ 0x0056bd30
bool cRigBlockTag::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                WStr_s0056_b680 n37;
                if (SP::GetPropertyAsString16(t25.get(), 0x4ebb27e, &n37)) {
                    wchar_t* owner = n37.mpBegin;
                    wchar_t* buf = owner;
                    wchar_t* n6 = n37.mpEnd;
                    do {
                        buf = wfind(owner, n6, '|');
                        *buf = 0;
                        if (buf != owner) {
                            uint32_t n28 = FNV1_String16(owner, 0x811c9dc5, 1);
                            Feature nSize;
                            nSize.id = 0x4ebfebd;
                            nSize.value = n28;
                            WStrSrc_s0056_b680 val;
                            ScratchSlots<1>();
                            WStr_Format(&val.str, L"(%ls) %ls", GetName(), owner);
                            val.value = (*weights)[t32 - begin];
                            ScratchSlots<25>();
                            fv->addDescribed(nSize, val);
                            owner = buf + 1;
                        }
                    } while (buf != n6 && owner != n6);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056bfa0
bool cTextureTag::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        result = true;
        Block* first = c->mpBegin;
        Block* it = first;
        Block* last = c->mpEnd;
        for (; it != last && result; it++) {
            TextureBlock* blk = (TextureBlock*)it;
            uint32_t n = blk->mnKeys;
            for (uint32_t i = 0; i < n; i++) {
                TexHash::R r;
                {
                    VSet tmp;
                    uint32_t key = blk->mKeys[i];
                    TexHash::Entry ent(key, tmp);
                    r = mTable.insert(ent);
                }
                VSet* set = (VSet*)((char*)r.it + 4);
                if (r.ok) {
                    PListRefCall pl;
                    bool ok = SP::PropertyManager()->GetPropertyList(blk->mKeys[i], gTextureGroup, pl.AsPointer());
                    if (ok) {
                        WStr_s0056_b680 s;
                        if (SP::GetPropertyAsString16(pl.get(), 0x4ebb27e, &s)) {
                            wchar_t* cur = s.mpBegin;
                            wchar_t* tokEnd = cur;
                            wchar_t* end = s.mpEnd;
                            do {
                                tokEnd = wfind(cur, end, '|');
                                *tokEnd = 0;
                                if (tokEnd != cur) {
                                    uint32_t h = FNV1_String16(cur, 0x811c9dc5, 1);
                                    set->insert(h);
                                    cur = tokEnd + 1;
                                }
                            } while (tokEnd != end && cur != end);
                        }
                    }
                }
                BlockSet* bs = (BlockSet*)set;
                uint32_t* p = bs->mb;
                uint32_t* pe = bs->me;
                for (; p != pe; p++) {
                    Feature f;
                    f.id = 0x5833344;
                    f.value = *p;
                    fv->add(f, (*weights)[it - first]);
                }
            }
        }
    }
    return result;
}

// @ 0x0056c2d0
bool cTextureTag::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            TextureBlock* n31 = (TextureBlock*)t32;
            uint32_t p4 = n31->mnKeys;
            for (uint32_t v1 = 0; v1 < p4; v1++) {
                PListRefInline t25;
                bool p32 = SP::PropertyManager()->GetPropertyList(n31->mKeys[v1], gTextureGroup, t25.AsPointer());
                if (p32) {
                    WStr_s0056_b680 n37;
                    if (SP::GetPropertyAsString16(t25.get(), 0x4ebb27e, &n37)) {
                        wchar_t* owner = n37.mpBegin;
                        wchar_t* buf = owner;
                        wchar_t* n6 = n37.mpEnd;
                        do {
                            buf = wfind(owner, n6, '|');
                            *buf = 0;
                            if (buf != owner) {
                                uint32_t n28 = FNV1_String16(owner, 0x811c9dc5, 1);
                                Feature nSize;
                                nSize.id = 0x5833344;
                                nSize.value = n28;
                                WStrSrc_s0056_b680 val;
                                ScratchSlots<1>();
                            WStr_Format(&val.str, L"(%ls) %ls", GetName(), owner);
                                val.value = (*weights)[t32 - begin];
                                ScratchSlots<25>();
                            fv->addDescribed(nSize, val);
                                owner = buf + 1;
                            }
                        } while (buf != n6 && owner != n6);
                    }
                }
            }
        }
    }
    return p30;
}

// @ 0x0056c570
bool cAuthorClassifier::ExtractTraits(void* creature, void*, cFeatureVector_s0056_c570* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline_s0056_c570 ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature_s0056_c570 f;
            f.field0 = 0x518af1d;
            int64_t k = p->GetAssetKey();
            f.field1 = FNV1Hash(&k, 8, 0x811c9dc5);
            features->add(f, 100.0f);
        }
    }
    return true;
}

// @ 0x0056c670
bool cAuthorClassifier::DescribeTraits(void* creature, void*, cFeatureVector_s0056_c570* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline_s0056_c570 ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature_s0056_c570 f;
            f.field0 = 0x518af1d;
            int64_t k = p->GetAssetKey();
            f.field1 = FNV1Hash(&k, 8, 0x811c9dc5);
            WStrSrc_s0056_c570 d;
            ScratchSlots<28>();
            WStr_Format(&d.str, L"(%ls) %ls", GetName(), p->GetName());
            d.value = 100.0f;
            features->addDescribed(f, d);
        }
    }
    return true;
}

// @ 0x0056c7d0
bool cMetadataSummarizer::ExtractParameters(void* creature, void*, cFeatureVector_s0056_c570* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline_s0056_c570 ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature_s0056_c570 f;
            f.field0 = 0x68375d7;
            unsigned count = p->GetTagCount();
            for (unsigned i = 0; i < count; i++) {
                const wchar_t* str = p->GetTag(i);
                if (wcsncmp(str, L"set:", 4) == 0) {
                    f.field1 = FNV1_String16(str, 0x811c9dc5, 0);
                    features->add(f, 100.0f);
                    break;
                }
            }
        }
    }
    return true;
}

// @ 0x0056c910
bool cAssetMetadata::SetMetadata(void* creature, void*, cFeatureVector_s0056_c570* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline_s0056_c570 ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature_s0056_c570 f;
            f.field0 = 0x68375d7;
            unsigned count = p->GetTagCount();
            for (unsigned i = 0; i < count; i++) {
                const wchar_t* str = p->GetTag(i);
                if (wcscmp(str, L"set:") == 0) {
                    f.field1 = FNV1_String16(str, 0x811c9dc5, 0);
                    WStrSrc_s0056_c570 d;
                    ScratchSlots<28>();
                    WStr_Format(&d.str, L"(%ls) %ls", GetName(), str);
                    d.value = 100.0f;
                    features->addDescribed(f, d);
                    break;
                }
            }
        }
    }
    return true;
}

// @ 0x0056cb30
bool cFeedClassifier::ExtractTraits(void* creature, void*, cFeatureVector_s0056_c570* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline_s0056_c570 ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature_s0056_c570 f;
            f.field0 = 0x518b883;
            unsigned count = p->GetCount2();
            for (unsigned i = 0; i < count; i++) {
                f.field1 = FNV1_String8(p->GetItem(i), 0x811c9dc5, 0);
                features->add(f, 100.0f);
            }
        }
    }
    return true;
}

// @ 0x0056cc50
bool cFeedClassifier::DescribeTraits(void* creature, void*, cFeatureVector_s0056_c570* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline_s0056_c570 ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature_s0056_c570 f;
            f.field0 = 0x518b883;
            unsigned count = p->GetCount2();
            for (unsigned i = 0; i < count; i++) {
                f.field1 = FNV1_String8(p->GetItem(i), 0x811c9dc5, 0);
                WStrSrc_s0056_c570 d;
                ScratchSlots<28>();
                WStr_Format(&d.str, L"(%ls) %hs", GetName(), p->GetItem(i));
                d.value = 100.0f;
                features->addDescribed(f, d);
            }
        }
    }
    return true;
}

// @ 0x0056cde0
bool cSwatchColorLookup::Init()
{
    PropListRefA tmp;
    bool t14 = PropertyManager_s0056_c570()->GetPropertyList(0x2ab48add, 0x97097e36, tmp.AsPointer());
    if (t14 && tmp.get()->HasProperty(0xd29675ec)) {
        Prop* v33 = tmp.get()->GetProperty(0xd29675ec);
        Vec3c* n40;
        unsigned len;
        len = v33->Count();
        n40 = v33->Data();
        if (len > 0) {
            mTabColors.clear();
            mTabColors.assign(n40, n40 + len);
            return true;
        }
    }
    return false;
}

// @ 0x0056cf70
unsigned VecFloat::GetAllocated(const void* a)
{
    // @ 0x0056cf70: index of the element (stride 12) whose distance to the query is smallest
    int value = 0;
    float v18;
    Vec3* left;
    Vec3* v8;
    Vec3* mem;
    float j;
    left = (Vec3*)mpBegin;
    mem = (Vec3*)mpEnd;
    v8 = left;
    {
        Vec3 t14;
        Vec3 tmp = Vec3Sub(&t14, (const Vec3*)a, left);
        v18 = VectorLength(&tmp);
    }
    for (++left; left != mem; ++left) {
        ScratchSlots<1>();
        Vec3 t14;
        Vec3 tmp = Vec3Sub(&t14, (const Vec3*)a, left);
        j = VectorLength(&tmp);
        if (v18 > j)
            value = (int)(left - v8);
    }
    ScratchSlots<1>();
    return value;
}

// @ 0x0056d080
bool cTextureClassifier::ExtractTraits(Creature_s0056_c570* creature, float** weights, cFeatureVector_s0056_c570* features)
{
    bool result = false;
    if (creature) {
        if (!gSwatchColors) {
            ScratchSlots<1>();
            cSwatchColorLookup* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookup();
            if (lookup->Init())
                gSwatchColors = lookup;
            else
                return true;
        }
        result = true;
        if (creature->mType == 0x2b978c46) {
            Feature_s0056_c570 f;
            f.field0 = 0x52b27b5;
            f.field1 = ((VecFloat*)gSwatchColors)->GetAllocated(&creature->mColor0);
            features->add(f, 33.333f);
            f.field1 = ((VecFloat*)gSwatchColors)->GetAllocated(&creature->mColor1) | 0x10000;
            features->add(f, 33.333f);
            f.field1 = ((VecFloat*)gSwatchColors)->GetAllocated(&creature->mColor2) | 0x20000;
            features->add(f, 33.333f);
        } else {
            Block_s0056_c570* p15 = creature->mpBegin;
            Block_s0056_c570* n35 = p15;
            Block_s0056_c570* p12 = creature->mpEnd;
            Feature_s0056_c570 v18;
            v18.field0 = 0x52b27b5;
            for (; n35 != p12 && result; n35++) {
                Block_s0056_c570* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3* col = &t14->mColors[i];
                    v18.field1 = (t14->mKeys[i] << 16) | ((VecFloat*)gSwatchColors)->GetAllocated(col);
                    features->add(v18, (*weights)[n35 - p15]);
                }
            }
        }
    }
    return result;
}

// @ 0x0056d2b0
bool cRegionColorClassifier::DescribeTraits(Creature_s0056_d2b0* c, float** weights, cAnnotatedFeatureVector_s0056_d2b0* out)
{
    bool result = false;
    if (c) {
        if (!gSwatchColors_s0056_d2b0) {
            ScratchSlots<1>();
            cSwatchColorLookupB* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookupB(Alloc17());
            if (lookup->Init())
                gSwatchColors_s0056_d2b0 = lookup;
            else
                return true;
        }
        result = true;
        if (c->mType == 0x2b978c46) {
            cID id;
            id.cls = 0x52b27b5;
            DescSrc d;
            ScratchSlots<75>();
            d.value = 33.333f;
            id.type = gSwatchColors_s0056_d2b0->GetAllocated(&c->mColor0);
            WStr_Format(&d.str, L"(%ls) %d: swatch %d", GetName(), 0, c->mColor0);
            out->Add(id, d);
            id.type = gSwatchColors_s0056_d2b0->GetAllocated(&c->mColor1) | 0x10000;
            WStr_Format(&d.str, L"(%ls) %d: swatch %d", GetName(), 1, gSwatchColors_s0056_d2b0->GetAllocated(&c->mColor1));
            out->Add(id, d);
            id.type = gSwatchColors_s0056_d2b0->GetAllocated(&c->mColor2) | 0x20000;
            WStr_Format(&d.str, L"(%ls) %d: swatch %d", GetName(), 2, gSwatchColors_s0056_d2b0->GetAllocated(&c->mColor2));
            out->Add(id, d);
        } else {
            Block_s0056_d2b0* p15 = c->mpBegin;
            Block_s0056_d2b0* n35 = p15;
            Block_s0056_d2b0* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52b27b5;
            for (; n35 != p12 && result; n35++) {
                Block_s0056_d2b0* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3_s0056_d2b0* j = &t14->mColors[i];
                    v18.type = (t14->mKeys[i] << 16) | gSwatchColors_s0056_d2b0->GetAllocated(j);
                    Annot_s0056_d2b0 desc;
                    WStr_Format(&desc.str, L"(%ls) %d: swatch %d", GetName(), t14->mKeys[i], gSwatchColors_s0056_d2b0->GetAllocated(j));
                    desc.value = (*weights)[n35 - p15];
                    out->Add(v18, desc);
                }
            }
        }
    }
    return true;
}

// @ 0x0056d650
bool cBaseColorClassifier::ExtractTraits(Creature_s0056_d2b0* c, float** weights, cFeatureVector_s0056_d2b0* fv)
{
    bool result = false;
    if (c) {
        if (!gSwatchColors_s0056_d2b0) {
            ScratchSlots<1>();
            cSwatchColorLookupB* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookupB();
            if (lookup->Init())
                gSwatchColors_s0056_d2b0 = lookup;
            else
                return true;
        }
        result = true;
        if (c->mType == 0x2b978c46) {
            Vec3_s0056_d2b0* col = &c->mColor0;
            cID id;
            id.cls = 0x52c812a;
            id.type = gSwatchColors_s0056_d2b0->GetAllocated(col);
            fv->add(id, 100.0f);
        } else {
            Block_s0056_d2b0* p15 = c->mpBegin;
            Block_s0056_d2b0* n35 = p15;
            Block_s0056_d2b0* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c812a;
            for (; n35 != p12 && result; n35++) {
                Block_s0056_d2b0* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3_s0056_d2b0* col = &t14->mColors[i];
                    v18.type = gSwatchColors_s0056_d2b0->GetAllocated(col);
                    fv->add(v18, (*weights)[n35 - p15]);
                }
            }
        }
    }
    return result;
}

// @ 0x0056d810
bool cBaseColorClassifier::DescribeTraits(Creature_s0056_d2b0* c, float** weights, cAnnotatedFeatureVector_s0056_d2b0* out)
{
    bool result = false;
    if (c) {
        if (!gSwatchColors_s0056_d2b0) {
                        cSwatchColorLookupB* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookupB(Alloc_s0056_d2b0());
            if (lookup->Init())
                gSwatchColors_s0056_d2b0 = lookup;
            else
                return true;
        }
        result = true;
        if (c->mType == 0x2b978c46) {
            cID v18;
            v18.cls = 0x52c812a;
            Vec3_s0056_d2b0* j = &c->mColor0;
            v18.type = gSwatchColors_s0056_d2b0->GetAllocated(j);
            DescSrc item;
            ScratchSlots<42>();
            WStr_Format(&item.str, L"(%ls) swatch %d", GetName(), v18.type);
            item.value = 100.0f;
            out->Add(v18, item);
        } else {
            Block_s0056_d2b0* p15 = c->mpBegin;
            Block_s0056_d2b0* n35 = p15;
            Block_s0056_d2b0* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c812a;
            for (; n35 != p12 && result; n35++) {
                Block_s0056_d2b0* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3_s0056_d2b0* j = &t14->mColors[i];
                    v18.type = gSwatchColors_s0056_d2b0->GetAllocated(j);
                    Annot_s0056_d2b0 desc;
                    WStr_Format(&desc.str, L"(%ls) swatch %d", GetName(), v18.type);
                    desc.value = (*weights)[n35 - p15];
                    out->Add(v18, desc);
                }
            }
        }
    }
    return true;
}

// @ 0x0056da90
bool cRegionKeyClassifier::ExtractTraits(Creature_s0056_d2b0* c, float** weights, cFeatureVector_s0056_d2b0* fv)
{
    bool result = false;
    if (c) {
        result = true;
        if (c->mType == 0x2b978c46) {
            cID id;
            id.cls = 0x52c8ca5;
            id.type = c->mKey0;
            fv->add(id, 100.0f);
            id.type = c->mKey1;
            fv->add(id, 100.0f);
            id.type = c->mKey2;
            fv->add(id, 100.0f);
        } else {
            Block_s0056_d2b0* p15 = c->mpBegin;
            Block_s0056_d2b0* n35 = p15;
            Block_s0056_d2b0* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c8ca5;
            for (; n35 != p12 && result; n35++) {
                Block_s0056_d2b0* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    v18.type = t14->mKeys[8 + i];
                    fv->add(v18, (*weights)[n35 - p15]);
                }
            }
        }
    }
    return result;
}

// @ 0x0056dbe0
bool cTextureClassifier_s0056_d2b0::DescribeTraits(Creature_s0056_d2b0* c, float** weights, cAnnotatedFeatureVector_s0056_d2b0* out)
{
    bool result = false;
    if (c) {
        result = true;
        if (c->mType == 0x2b978c46) {
            DescSrc d;
            ScratchSlots<32>();
            cID id;
            id.cls = 0x52c8ca5;
            id.type = c->mKey0;
            WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), id.type);
            d.value = 33.333f;
            out->Add(id, d);
            id.type = c->mKey1;
            WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), id.type);
            d.value = 33.333f;
            out->Add(id, d);
            id.type = c->mKey2;
            WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), id.type);
            d.value = 33.333f;
            out->Add(id, *(DescSrcI*)&d);
            ScratchSlots<18>();
        } else {
            Block_s0056_d2b0* p15 = c->mpBegin;
            Block_s0056_d2b0* n35 = p15;
            Block_s0056_d2b0* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c8ca5;
            for (; n35 != p12 && result; n35++) {
                Block_s0056_d2b0* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    v18.type = t14->mKeys[8 + i];
                    DescSrc d;
                    ScratchSlots<19>();
                    WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), v18.type);
                    d.value = (*weights)[n35 - p15];
                    out->Add(v18, d);
                }
            }
        }
    }
    return true;
}

// @ 0x0056ee90
template SP::Traits::cIClassifier_s0056_df80* SP::Traits::tClassifierFactory<SP::Traits::cRigBlockTag_s0056_df80>::Create()
;

// @ 0x0056f2b0
namespace SP { namespace Traits {
void* cNullClassifierSource::GetClassifier()
{
    return 0;
  }
}}  // namespace SP::Traits

// @ 0x0056f3e0
namespace eastl {
template<class K, class T, class C, class A, class RAC> pair_s0056_df80<typename SP::Traits::vector_map_s0056_df80<K,T,C,A,RAC>::iterator, typename SP::Traits::vector_map_s0056_df80<K,T,C,A,RAC>::iterator> SP::Traits::vector_map_s0056_df80<K,T,C,A,RAC>::equal_range(const key_type& k)
{
    const iterator itLower(lower_bound(k));
    if((itLower == end()) || mValueCompare(k, *itLower))
        return pair_s0056_df80<iterator, iterator>(itLower, itLower);
    iterator itUpper(itLower);
    return pair_s0056_df80<iterator, iterator>(itLower, ++itUpper);
  }
}  // namespace eastl

// @ 0x0056f4e0
namespace eastl {
template<class K, class V, class H> typename hashtable_s0056_df80<K,V,H>::node_type* hashtable_s0056_df80<K,V,H>::DoAllocateNode(const value_type& value)
{
    node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type), 4, 0);
    ::new(&pNode->mValue) value_type((ScratchSlots_s0056_df80<declined_copy_slots<V>::value>(), value));
    pNode->mpNext = 0;
    return pNode;
  }
}  // namespace eastl

// @ 0x0056f560
namespace eastl {
template<class K, class V, class H> void hashtable_s0056_df80<K,V,H>::DoRehash(size_type nNewBucketCount)
{
    node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);

    node_type* pNode;
    for(size_type i = 0; i < mnBucketCount; ++i)
    {
        while((pNode = mpBucketArray[i]) != 0)
        {
            const size_type nNewBucketIndex = bucket_index(pNode, (uint32_t)nNewBucketCount);
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext    = pBucketArray[nNewBucketIndex];
            pBucketArray[nNewBucketIndex] = pNode;
        }
    }

    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnBucketCount = nNewBucketCount;
    mpBucketArray = pBucketArray;
  }
}  // namespace eastl

// @ 0x0056f6d0
template TexTagsVector::iterator TexTagsVector::insert(TexTagsVector::iterator, const TexTagsVector::value_type&)
;

// @ 0x0056f830
template void TexTagsVector::DoInsertValue(TexTagsVector::iterator, const TexTagsVector::value_type&)
;

// @ 0x0056fb90
void ElemVec::DoInsertValue(ElemI* position, const ElemI& value)
{
    if (mpEnd != mpCapacity) {
        const ElemI* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) ElemI(*(mpEnd - 1));
        CopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    }
    else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        ElemI* const pNewData = DoAllocate(nNewSize);
        ElemI* pNewEnd = UninitCopy(mpBegin, position, pNewData);
        ::new(pNewEnd) ElemO(*(const ElemO*)&value);
        pNewEnd = UninitCopy(position, mpEnd, ++pNewEnd);
        ScratchSlots<28>();
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x0056fee0
void Vec12Vector::DoAssign(const Vec12* first, const Vec12* last, const FalseTag& tag)
{
    const uint32_t n = (uint32_t)(last - first);
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        Vec12* const pNewData = DoRealloc(n, first, last);
        ScratchSlots<10>();
        DestroyFrom(mpBegin);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    }
    else if (n <= (uint32_t)(mpEnd - mpBegin)) {
        Vec12* const pNewEnd = Copy12(first, last, mpBegin);
        DestroyFrom(pNewEnd);
        mpEnd = pNewEnd;
    }
    else {
        const Vec12* const pMid = first + (mpEnd - mpBegin);
        Copy12(first, pMid, mpBegin);
        mpEnd = UninitCopy12(pMid, last, mpEnd);
        ScratchSlots<12>();
    }
}

// @ 0x005701b0
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key)
{
    int n = (int)(last - first);
    ScratchSlots<1>();
    while (n > 0) {
        Pair8* it = first;
        int half = n >> 1;
        it = it + half;
        if (LessU32(it->a, key->a)) {
            it = it + 1;
            first = it;
            n = n - (half + 1);
        }
        else {
            n = half;
        }
    }
    return first;
}

// @ 0x00570230
void HashTable::DoFreeNodes(HashNode** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        HashNode* pNode = pNodeArray[i];
        while (pNode) {
            HashNode* pTempNode = pNode;
            pNode = pNode->mpNext;
            DoFreeNode(pTempNode);
        }
        pNodeArray[i] = 0;
    }
}
