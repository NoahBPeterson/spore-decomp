// Slice s00d18df0 (part b): the four calls that follow DoSaveSelectedFile in the level editor.
//
//   0x00d19460  SP::cGameEditInputStrategy::Copy                  thiscall
//   0x00d194c0  SP::cGameEditInputStrategy::PopulateLoadPlanetDialogGrid  thiscall
//   0x00d19610  eastl::partial_sort<uint32_t*, cPropertyListNameSort>      cdecl
//   0x00d196f0  SP::cPropertyListNameSort::cPropertyListNameSort(uint32_t) thiscall, ret 4
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

void operator delete(void* p);                           // 0x00f47380

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// ---------------------------------------------------------------- EASTL strings
template <class T> inline const T& EastlMax(const T& a, const T& b) { return (a < b) ? b : a; }

namespace eastl {
extern wchar_t gEmptyString16[];                         // 0x01667bac

class allocator {
public:
    void deallocate(void* p, unsigned int) { operator delete(p); }
};

template <class T> struct basic_string {
    T* mpBegin;                                          // +0x0
    T* mpEnd;                                            // +0x4
    T* mpCapacity;                                       // +0x8
    allocator mAllocator;                                // +0xc

    basic_string() { AllocateSelf(); }
    basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string() { DeallocateSelf(); }

    void AllocateSelf() {
        mpBegin = (T*)gEmptyString16;
        mpEnd = (T*)gEmptyString16;
        mpCapacity = (T*)gEmptyString16 + 1;
    }
    void RangeInitialize(const T* p);                    // 0x00579a90
    void SetCapacity(unsigned int n);                    // 0x0042f360
    void reserve(unsigned int n) {
        unsigned int size = (unsigned int)(mpEnd - mpBegin);
        n = EastlMax(n, size) + 1;
        if (n > (unsigned int)(mpCapacity - mpBegin))
            SetCapacity(n);
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    const T* c_str() const { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
typedef basic_string<wchar_t> string16;
}

// ---------------------------------------------------------------- resource keys
namespace EA { namespace ResourceMan {
class Manager;

struct Key {
    uint32_t instance;                                   // +0x00
    uint32_t type;                                       // +0x04
    uint32_t group;                                      // +0x08
};

struct KeyVector {
    Key* mpBegin;                                        // +0x00
    Key* mpEnd;                                          // +0x04
    Key* mpCapacity;                                     // +0x08
    uint32_t mAllocator;                                 // +0x0c

    void erase(Key* first, Key* last);                   // 0x0050f740
    void clear() { erase(mpBegin, mpEnd); }
};

struct IResourceFilter {                                 // vtable 0x013eb898
    PV
};

struct PlanetKeyFilter : IResourceFilter {
    uint32_t mInstanceID;                                // +0x04
    uint32_t mGroupID;                                   // +0x08
    uint32_t mTypeID;                                    // +0x0c
    uint32_t mFlags;                                     // +0x10
    PlanetKeyFilter()
    {
        mInstanceID = 0xffffffff;
        mTypeID = 0xb1b104;
        mGroupID = 0x40840000;
        mFlags = 0xdfff0000;
    }
};

struct IResourceManager {
    PV8 PV4 PV2
    virtual int GetResourceKeyList(KeyVector* pKeys, IResourceFilter* pFilter, int flags);  // +0x38
    PV16
    virtual bool GetFileName(const Key* pKey, eastl::string16* pName);                     // +0x7c
};
} }
EA::ResourceMan::IResourceManager* GetManager();         // 0x008de1a0

// ---------------------------------------------------------------- UTFWin grid
namespace EA { namespace UTFWinControls {
class IWinGrid {
public:
    PV16 PV16 PV2                                        // +0x00..+0x84
    virtual void v88(int a);                             // +0x88
    virtual void v8c(int a);                             // +0x8c
    PV4 PV2                                              // +0x90..+0xa4
    virtual void va8(int a, int b);                      // +0xa8
    PV16 PV16 PV16                                       // +0xac..+0x168
    virtual void v16c();                                 // +0x16c
    PV8 PV4 PV                                           // +0x170..+0x1a0
    virtual void v1a4(int a, int row, const wchar_t* pName, int b, int c, int d);  // +0x1a4
};
} }

namespace SP {
class cGameEditInputStrategy {
public:
    void Copy();                                                         // 0x00d19460
    void PopulateLoadPlanetDialogGrid();                                 // 0x00d194c0
    void DoSaveSelectedFile(eastl::string16* pName);                     // 0x00d18df0

    char pad00[0x8c];
    EA::UTFWinControls::IWinGrid* mPlanetGridFileList;                   // +0x8c
    EA::ResourceMan::KeyVector mPlanetKeys;                              // +0x90
};
}

// @ 0x00d19460
void SP::cGameEditInputStrategy::Copy()
{
    eastl::string16 name(L"Clipboard");
    DoSaveSelectedFile(&name);
}

// @ 0x00d194c0
void SP::cGameEditInputStrategy::PopulateLoadPlanetDialogGrid()
{
    mPlanetGridFileList->v16c();
    EA::ResourceMan::IResourceManager* pMgr = GetManager();
    EA::ResourceMan::KeyVector* pKeys = &mPlanetKeys;
    EA::ResourceMan::PlanetKeyFilter filter;
    pKeys->clear();
    pMgr->GetResourceKeyList(pKeys, &filter, 0);
    int count = (int)(pKeys->mpEnd - pKeys->mpBegin);
    for (int i = 0; i < count; i++) {
        eastl::string16 name;
        pMgr->GetFileName(&pKeys->mpBegin[i], &name);
        mPlanetGridFileList->v1a4(0, i, name.c_str(), 0, 1, 0);
    }
    mPlanetGridFileList->v8c(0);
    mPlanetGridFileList->v88(0);
    mPlanetGridFileList->va8(0, 0);
}

// ---------------------------------------------------------------- property-name sort
namespace SP {
struct cPropertyListNameSort {
    uint32_t mGroupId;                                   // +0x00
    EA::ResourceMan::Manager* mpResourceManager;         // +0x04
    eastl::string16 aName;                               // +0x08
    eastl::string16 bName;                               // +0x18

    cPropertyListNameSort(uint32_t groupID);             // 0x00d196f0
    cPropertyListNameSort(const cPropertyListNameSort& x);  // 0x00d18000
    bool operator()(uint32_t a, uint32_t b) const;       // 0x00d16760
};
}

namespace eastl {
void make_heap(uint32_t* first, uint32_t* last, SP::cPropertyListNameSort compare);            // 0x00d18cd0
void adjust_heap(uint32_t* first, int top, int count, int hole, uint32_t value,
                 SP::cPropertyListNameSort compare);                                            // 0x00d180c0
void sort_heap(uint32_t* first, uint32_t* last, SP::cPropertyListNameSort compare);            // 0x00d18d60

// @ 0x00d19610
void partial_sort(uint32_t* first, uint32_t* middle, uint32_t* last, SP::cPropertyListNameSort compare)
{
    make_heap(first, middle, compare);
    for (uint32_t* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            uint32_t value = *i;
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, value, compare);
        }
    }
    sort_heap(first, middle, compare);
}
}

// @ 0x00d196f0
SP::cPropertyListNameSort::cPropertyListNameSort(uint32_t groupID)
{
    mGroupId = groupID;
    aName.reserve(0x104);
    bName.reserve(0x104);
    mpResourceManager = (EA::ResourceMan::Manager*)GetManager();
}
