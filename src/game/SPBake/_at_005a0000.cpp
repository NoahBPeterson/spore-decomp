// src/game/SPBake/_at_005a0000.cpp -- migrated from slice(s) s005a8d20 by tools/migrate/rewrite.py
// Object file: SPBake/_at_005a0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#include <math.h>
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s005a8d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);  // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3& SetRotation(const Quaternion& q);   // 0x0041CB40
};
Matrix3 operator*(const Matrix3& a, const Matrix3& b);   // 0x0041DE20
namespace EA {
template <typename T>
class AutoRefCount_s005a_8d20 {
public:
    T* mpObject;
    AutoRefCount_s005a_8d20() : mpObject(0) {}
    AutoRefCount_s005a_8d20(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s005a_8d20(const AutoRefCount_s005a_8d20& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s005a_8d20() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s005a_8d20& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace eastl {
class allocator_s005a_8d20 { public:};
}
namespace eastl {
struct sp_vector_allocator_s005a_8d20 {
    uint32_t mData[2];
    sp_vector_allocator_s005a_8d20() {}
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
template <typename T>
struct copy_result {
    T* mpResult;
    copy_result() {}
};
}
namespace eastl {
template <typename T, typename Tag>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest, Tag);   // 0x004E8EE0 (AutoRefCount instance)
}
namespace eastl {
struct false_type { false_type() {} };
}
namespace eastl {
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result)
{
    const copy_result<T> r = uninitialized_copy_impl(first, last, result, false_type());
    return r.mpResult;
}
}
namespace eastl {
template <typename T>
struct VectorBase_s005a_8d20 {
    T*                  mpBegin;      // +0x0
    T*                  mpEnd;        // +0x4
    T*                  mpCapacity;   // +0x8
    sp_vector_allocator_s005a_8d20 mAllocator;   // +0xc
    VectorBase_s005a_8d20() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    VectorBase_s005a_8d20(size_t n, const sp_vector_allocator_s005a_8d20& allocator_s005a_8d20);   // 0x0066AEC0 (folded)
    ~VectorBase_s005a_8d20()
    {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
    }
};
}
namespace eastl {
template <typename T>
class vector_s005a_8d20 : public VectorBase_s005a_8d20<T> {
public:
    vector_s005a_8d20() {}
    vector_s005a_8d20(const vector_s005a_8d20& x) : VectorBase_s005a_8d20<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator)
    {
        this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
    }
    ~vector_s005a_8d20() { DoDestroyValues(this->mpBegin, this->mpEnd); }
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    T* begin() { return this->mpBegin; }
    T* end() { return this->mpEnd; }
    T* DoInsertValue(T* position, const T& value);   // 0x004B6000 (AutoRefCount<cPropertyList> instance)
    void push_back(const T& value)
    {
        if (this->mpEnd < this->mpCapacity)
            ::new (this->mpEnd++) T(value);
        else
            DoInsertValue(this->mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005a_8d20 {
    T1 first;
    T2 second;
    __forceinline pair_s005a_8d20(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
struct rbtree_node_base_s005a_8d20 {
    rbtree_node_base_s005a_8d20* mpNodeRight;
    rbtree_node_base_s005a_8d20* mpNodeLeft;
    rbtree_node_base_s005a_8d20* mpNodeParent;
    char              mColor;
};
}
namespace eastl {
template <typename T>
struct rbtree_node_s005a_8d20 : public rbtree_node_base_s005a_8d20 {
    T mValue;   // +0x10
};
}
namespace eastl {
template <typename T>
struct rbtree_iterator_s005a_8d20 {
    typedef rbtree_node_s005a_8d20<T> node_type;
    node_type* mpNode;
    rbtree_iterator_s005a_8d20() : mpNode(0) {}
    explicit rbtree_iterator_s005a_8d20(const node_type* pNode) : mpNode((node_type*)pNode) {}
    rbtree_iterator_s005a_8d20(const rbtree_iterator_s005a_8d20& x) : mpNode(x.mpNode) {}
    T* operator->() const { return &mpNode->mValue; }
    bool operator==(const rbtree_iterator_s005a_8d20& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator_s005a_8d20& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template <typename T>
struct less_s005a_8d20 { bool operator()(const T& a, const T& b) const { return a < b; } };
}
namespace eastl {
template <typename Key, typename T>
class map_s005a_8d20 {
public:
    typedef pair_s005a_8d20<const Key, T>          value_type;
    typedef rbtree_node_s005a_8d20<value_type>     node_type;
    typedef rbtree_iterator_s005a_8d20<value_type> iterator;

    less_s005a_8d20<Key>        mCompare;
    rbtree_node_base_s005a_8d20 mAnchor;
    uint32_t         mnSize;
    allocator_s005a_8d20        mAllocator;

    iterator end() { return iterator((node_type*)&mAnchor); }
    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear()
    {
        DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
        reset();
    }
    iterator find(const Key& key);                                                   // 0x00E5C780 (folded)
    iterator DoInsertValue(iterator position, const value_type& value, true_type);  // 0x005A9820
    iterator insert(iterator position, const value_type& value)
    {
        return DoInsertValue(position, value, true_type());
    }
    iterator lower_bound(const Key& key)
    {
        node_type*        pCurrent  = (node_type*)mAnchor.mpNodeParent;
        rbtree_node_base_s005a_8d20* pRangeEnd = &mAnchor;
        while (pCurrent) {
            if (!mCompare(pCurrent->mValue.first, key)) {
                pRangeEnd = pCurrent;
                pCurrent  = (node_type*)pCurrent->mpNodeLeft;
            } else
                pCurrent = (node_type*)pCurrent->mpNodeRight;
        }
        return iterator((node_type*)pRangeEnd);
    }
    T& operator[](const Key& key);
    void DoFreeNode(node_type* pNode)
    {
        pNode->~node_type();
        operator delete[](pNode);
    }
    void DoNukeSubtree(node_type* pNode);
};
}
namespace SP {
class cPropertyList_s005a_8d20 {
public:
    virtual int AddRef();
    virtual int Release();
};
}
typedef eastl::vector_s005a_8d20<EA::AutoRefCount_s005a_8d20<SP::cPropertyList_s005a_8d20> > PropertyListVector;
typedef eastl::map_s005a_8d20<uint32_t, PropertyListVector> EditorPropListMap;
extern EditorPropListMap sEditorPropLists;   // 0x0151102C
template class eastl::map_s005a_8d20<uint32_t, PropertyListVector>;
// ---- items of slice s005a8d20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern EditorPropListMap sEditorPropLists;   // 0x0151102C

// @ 0x005a9050
PropertyListVector* FindEditorPropertyLists(uint32_t id)
{
    EditorPropListMap::iterator it = sEditorPropLists.find(id);
    if (it != sEditorPropLists.end())
        return &it->second;
    return 0;
}
