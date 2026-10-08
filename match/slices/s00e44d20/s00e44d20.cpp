// Slice s00e44d20 -- SP::EditorValidity::AddCellUpgradeParts (0x00E44D20, 1844 bytes).
// Flags: /O2 /MD /Gy /TP /GS- (no /EHsc: the constraint vector local gets no EH frame).
//
// Given an upgrade-part category (message id 0x1654c00..0x1654c05, 0x1654c03 unused) the function
//   1. asks one of four helpers to add the category's fixed parts to the key list at +0x460 and
//      picks the number of query rounds (1, 2 or 3);
//   2. seeds a FunctionalMatch constraint list (parameter 0x2dc9d1e / 0x2dd90af equals a hashed
//      part-group id) when the list still has fewer than 15 entries;
//   3. fills the list up to 15 keys: every round asks the object-template database for up to
//      (15 - size) objects matching the constraints (plus the generic 0x3cc89b1 constraint), appends
//      the hits, and rebuilds the constraints for the next round (categories 2, 4 and 5 only);
//   4. sorts the key list, removes duplicates and clears the second list at +0x474.
// Class/member names are Claude-coined; the layout comes from the retail disassembly.
#include "types.h"

typedef unsigned int size_t;

void operator delete[](void* p);                                  // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }

struct ResourceKey {
    uint32_t mInstance;   // +0x0
    uint32_t mType;       // +0x4
    uint32_t mGroup;      // +0x8
    ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
};

namespace eastl {
struct sp_vector_allocator {
    uint32_t mData[2];
    __forceinline void deallocate(void* p, size_t) {
        if (((uint32_t*)p)[-1]) operator delete[](p);
    }
};
template <typename T>
class vector {
 public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    __forceinline vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~vector() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
    }
    void DoDestroyValues(T* first, T* last) {                     // 0x004e39a0 for ConstraintNode
        for (; first < last; ++first) first->~T();
    }
    T* DoInsertValue(T* position, const T& value);                // 0x004e39d0 / 0x004e3e10
    T* erase(T* first, T* last);                                  // 0x0050f740 (Key vector)
    __forceinline void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void push_back_call(const T& value);                          // 0x004e18e0 (out-of-line copy)
    vector(const vector& x);                                      // 0x004e38d0 (out of line)
    void clear();
    __forceinline size_t size() const { return (size_t)(mpEnd - mpBegin); }
};
}  // namespace eastl

namespace SP {
namespace FunctionalMatch {
enum EqualConstraint { kEquals = 0 };
struct Constraint {
    uint32_t mParameter;
    int mType;
    int mMin, mMax;
};
struct ConstraintNode {
    Constraint mConstraint;                    // +0x0
    eastl::vector<ConstraintNode> mChildren;   // +0x10
    ConstraintNode(uint32_t parameter, EqualConstraint eq, int value);   // 0x00558960
    ConstraintNode(const ConstraintNode& x);                              // 0x00606880
    ~ConstraintNode();                                                    // 0x006066f0 (recursive, out of line)
};
// Same layout as ConstraintNode, but its destructor is expanded inline at the use site (the
// original's loop bodies inline it while the switch seeds and the category-5 rebuild call 0x006066f0).
struct ConstraintTemp {
    Constraint mConstraint;                    // +0x0
    eastl::vector<ConstraintNode> mChildren;   // +0x10
    ConstraintTemp(uint32_t parameter, EqualConstraint eq, int value);   // 0x00558960
    operator const ConstraintNode&() const { return *(const ConstraintNode*)this; }
    // Inline copy construction (the category-2 rebuild expands it in place).
    void CopyFrom(const ConstraintTemp& o) {
        mConstraint.mParameter = o.mConstraint.mParameter;
        mConstraint.mType = o.mConstraint.mType;
        mConstraint.mMin = o.mConstraint.mMin;
        mConstraint.mMax = o.mConstraint.mMax;
        mConstraint.mMin = o.mConstraint.mMin;
        mConstraint.mMax = o.mConstraint.mMax;
        ::new (&mChildren) eastl::vector<ConstraintNode>(o.mChildren);
    }
};
}  // namespace FunctionalMatch
using FunctionalMatch::ConstraintNode;
using FunctionalMatch::ConstraintTemp;
using FunctionalMatch::kEquals;
}  // namespace SP

template <> eastl::vector<SP::ConstraintNode>::vector(const vector& x);   // 0x004e38d0
template <> void eastl::vector<SP::ConstraintNode>::push_back_call(const SP::ConstraintNode& value);   // 0x004e18e0
template <> void eastl::vector<SP::ConstraintNode>::DoDestroyValues(SP::ConstraintNode* first, SP::ConstraintNode* last);   // 0x004e39a0
template <> SP::ConstraintNode* eastl::vector<SP::ConstraintNode>::DoInsertValue(SP::ConstraintNode* position, const SP::ConstraintNode& value);   // 0x004e39d0
template <> ResourceKey* eastl::vector<ResourceKey>::DoInsertValue(ResourceKey* position, const ResourceKey& value);   // 0x004e3e10
template <> ResourceKey* eastl::vector<ResourceKey>::erase(ResourceKey* first, ResourceKey* last);   // 0x0050f740

namespace eastl {
SP::ConstraintNode* __cdecl copy_impl(SP::ConstraintNode* first, SP::ConstraintNode* last, SP::ConstraintNode* dest);   // 0x004e4fd0
void __cdecl sort_keys(ResourceKey* first, ResourceKey* last);             // 0x004f6b70 (eastl::sort<ResourceMan::Key*>)
ResourceKey* __cdecl unique_keys(ResourceKey* first, ResourceKey* last);   // 0x004f6830 (eastl::unique<ResourceMan::Key*>)
}

// vector::clear() = erase(begin, end): copy the (empty) tail down, destroy, shrink.
template <> __forceinline void eastl::vector<SP::ConstraintNode>::clear()
{
    SP::ConstraintNode* first = mpBegin;
    SP::ConstraintNode* last = mpEnd;
    SP::ConstraintNode* position = copy_impl(last, mpEnd, first);   // 0x004e4fd0
    DoDestroyValues(position, mpEnd);
    mpEnd -= (last - first);
}

namespace SP {

struct IObjectTemplateDB {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();  virtual void v4();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();
    // Appends up to maxCount objects that satisfy every constraint to 'keys'.
    virtual void FindObjects(eastl::vector<ResourceKey>& keys, int maxCount,
                             const eastl::vector<ConstraintNode>& constraints);   // +0x24
};
IObjectTemplateDB* ObjectTemplateDB();                                     // 0x0067cb40

// The four per-category key adders (cdecl, take the key list at this+0x460).
void __cdecl AddPartsCategoryA(eastl::vector<ResourceKey>* keys);          // 0x00e434a0 (0x1654c00, 0x1654c01)
void __cdecl AddPartsCategoryB(eastl::vector<ResourceKey>* keys);          // 0x00e435c0 (0x1654c02)
void __cdecl AddPartsCategoryC(eastl::vector<ResourceKey>* keys);          // 0x00e3ede0 (0x1654c04)
void __cdecl AddPartsCategoryD(eastl::vector<ResourceKey>* keys);          // 0x00e43710 (0x1654c05)

class cEditorValidity {
 public:
    uint32_t pad000[0x460 / 4];
    eastl::vector<ResourceKey> mPartKeys;       // +0x460
    eastl::vector<ResourceKey> mOtherKeys;      // +0x474

    void AddCellUpgradeParts(uint32_t category);
};

// @ 0x00E44D20
void cEditorValidity::AddCellUpgradeParts(uint32_t category)
{
    eastl::vector<ConstraintNode> constraints;
    constraints.clear();

    int rounds;
    switch (category) {
    case 0x1654c00:
        AddPartsCategoryA(&mPartKeys);
        if (mPartKeys.size() < 15)
            constraints.push_back_call(ConstraintNode(0x2dc9d1e, kEquals, 0xdfad9f51));
        rounds = 1;
        break;
    case 0x1654c01:
        AddPartsCategoryA(&mPartKeys);
        if (mPartKeys.size() < 15)
            constraints.push_back_call(ConstraintNode(0x2dc9d1e, kEquals, 0x9ea3031a));
        rounds = 1;
        break;
    case 0x1654c02:
        AddPartsCategoryB(&mPartKeys);
        if (mPartKeys.size() < 15)
            constraints.push_back_call(ConstraintNode(0x2dc9d1e, kEquals, 0x372e2c04));
        rounds = 2;
        break;
    case 0x1654c04:
        AddPartsCategoryC(&mPartKeys);
        if (mPartKeys.size() < 15)
            constraints.push_back_call(ConstraintNode(0x2dd90af, kEquals, 0x24682294));
        rounds = 3;
        break;
    case 0x1654c05:
        AddPartsCategoryD(&mPartKeys);
        if (mPartKeys.size() < 15)
            constraints.push_back_call(ConstraintNode(0x2dd90af, kEquals, 0x476a98c7));
        rounds = 3;
        break;
    default:
        return;
    }

    int missing = 15 - (int)mPartKeys.size();
    if (missing > 0 && rounds != 0) {
        for (int round = 0; round < rounds; ++round) {
            {
                ConstraintTemp seed(0x3cc89b1, kEquals, 0x913b23be);
                constraints.push_back(seed);
            }

            eastl::vector<ResourceKey> found;
            ObjectTemplateDB()->FindObjects(found, missing, constraints);
            for (ResourceKey* key = found.mpBegin; key != found.mpEnd; ++key)
                mPartKeys.push_back(*key);

            if (category == 0x1654c02) {
                constraints.clear();
                if (round == 0) {
                    ConstraintTemp rebuilt(0x2dc9d1e, kEquals, 0x372e2c04);
                    if (constraints.mpEnd < constraints.mpCapacity) {
                        ConstraintTemp* slot = (ConstraintTemp*)constraints.mpEnd++;
                        if (slot)
                            slot->CopyFrom(rebuilt);
                    } else {
                        constraints.DoInsertValue(constraints.mpEnd, rebuilt);
                    }
                }
            } else if (category == 0x1654c04) {
                constraints.clear();
                if (round == 0) {
                    ConstraintTemp rebuilt(0x2dc9d1e, kEquals, 0xccc35c46);
                    constraints.push_back(rebuilt);
                } else if (round == 1) {
                    ConstraintTemp rebuilt(0x2dd90af, kEquals, 0x2399be55);
                    constraints.push_back(rebuilt);
                }
            } else if (category == 0x1654c05) {
                constraints.clear();
                if (round == 0)
                    constraints.push_back(ConstraintNode(0x2dc9d1e, kEquals, 0x65672ade));
                else if (round == 1)
                    constraints.push_back(ConstraintNode(0x2dd90af, kEquals, 0x2399be55));
            }
        }
    }

    eastl::sort_keys(mPartKeys.mpBegin, mPartKeys.mpEnd);
    mPartKeys.erase(eastl::unique_keys(mPartKeys.mpBegin, mPartKeys.mpEnd), mPartKeys.mpEnd);
    mOtherKeys.erase(mOtherKeys.mpBegin, mOtherKeys.mpEnd);
}

}  // namespace SP
