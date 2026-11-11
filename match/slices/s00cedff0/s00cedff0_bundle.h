#ifndef MATCH_S00CEDFF0_BUNDLE_H
#define MATCH_S00CEDFF0_BUNDLE_H

#include "../../../src/game/include/EA/COM/InterfaceId.h"
#include "../../../src/game/include/EA/COM/ClassId.h"

struct cSPVector3;
namespace SP {
class cGameBundle;
class cSPCreatureBase;
class cSpatialObject;
class cIObjectDatabaseIStream;
class cIObjectDatabaseOStream;

// Only the primary reference-counting interface is needed by AutoRefCount.
class cGameData {
public:
    virtual int AddRef();
    virtual int Release();
};
}

namespace EA {
template <class T> class AutoRefCount {
public:
    T* mpObject;
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
}

namespace eastl {
class allocator {
public:
    const char* mpName;
};
struct sp_vector_allocator : allocator {};

template <class T, class Allocator> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    unsigned int mAllocatorReserved; // Retail vectors reserve eight allocator bytes.
};

template <class T, class Allocator> class vector : public VectorBase<T, Allocator> {
public:
    typedef T* iterator;
    ~vector();
    iterator erase(iterator first, iterator last);
    bool empty() const { return this->mpBegin == this->mpEnd; }
    iterator begin() { return this->mpBegin; }
    iterator end() { return this->mpEnd; }
};
}

namespace SP {
class cGameBundleContainer {
public:
    virtual ~cGameBundleContainer();
    virtual cSPVector3 GetBundlePosition(cGameBundle*) const = 0;
    virtual void OnAddItem(cGameBundle*) = 0;
    virtual void OnRemoveItem() = 0;
    virtual float GetRank(cSPCreatureBase*);
    virtual void* AsInterface(EA::COM::InterfaceId);
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual EA::COM::ClassId GetClassId() const = 0;
    virtual bool Write(cIObjectDatabaseOStream&) const;
    virtual bool Read(cIObjectDatabaseIStream&);
    virtual void Shutdown();
    virtual void SetBundlePlacement(cGameBundle*);
    virtual cSpatialObject* AsISpatialObject();
    // MSVC places overloaded virtuals in reverse declaration order.
    virtual float GetBundleCapacity() const;
    virtual float GetBundleCapacity(unsigned int) const;
    virtual float FUN_00cee290() const; // Retail slot 16; original name unconfirmed.

    typedef eastl::vector<EA::AutoRefCount<cGameBundle>, eastl::sp_vector_allocator> BundleList;
    BundleList mBundleList;                  // +0x04, including allocator state
    EA::AutoRefCount<cGameData> mpOwner;      // +0x18
    int mContainerCapacity;                  // +0x1c
    float mBundleCapacity;                   // +0x20
};
typedef char BundleListSize[(sizeof(cGameBundleContainer::BundleList) == 0x14) ? 1 : -1];
typedef char GameBundleContainerSize[(sizeof(cGameBundleContainer) == 0x24) ? 1 : -1];
}

#endif
