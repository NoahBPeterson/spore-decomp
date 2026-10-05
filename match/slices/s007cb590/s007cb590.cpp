// Slice s007cb590: cConfigScriptState / cConfigManager + eastl vector<vector_map> helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

#include "../s007ca950/s007ca950.h"

// ---------------------------------------------------------------- masked callees
namespace EA { namespace ArgScript {
struct cArguments {
    void** MainArguments(int n);
    void** OptionArguments(const char* pName, int n);
};
}}

extern char gEmptyChar;   // 0x01667bac
void FUN_006a4950(void*, void*);

// SP's heap vector allocator (8 bytes, keeps a header word before the block).
struct sp_vector_allocator {
    unsigned int mData[2];
    void deallocate(void* p, unsigned int) {
        if (p && ((unsigned int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
};

// eastl::basic_string<char,eastl::allocator> (16 bytes).
struct string8 {
    char* mpBegin;        // +0
    char* mpEnd;          // +4
    char* mpCapacity;     // +8
    unsigned int mAllocator;  // +0xc
    string8() : mpBegin(&gEmptyChar), mpEnd(&gEmptyChar), mpCapacity(&gEmptyChar + 1), mAllocator(0) {}
    ~string8() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
    string8& assign(const char* first, const char* last);
    string8& operator=(const string8& x);
};

typedef eastl::pair<uint64, EA::AutoRefCount<SP::cPropertyList> > PropPair;
typedef eastl::vector<PropPair, eastl::allocator>                PropVec;
typedef eastl::vector_map<uint64, EA::AutoRefCount<SP::cPropertyList>,
                          eastl::less<uint64>, eastl::allocator, PropVec> PropMap;
typedef eastl::vector<PropMap, eastl::fixed_vector_allocator<sizeof(PropMap), 4, 4, 0, 1> > MapFixVec;

namespace eastl {
template <typename T>
T* uninitialized_fill_n_ptr(T* first, unsigned int n, const T& value) {
    T* d = first;
    for (unsigned int i = 0; i < n; ++i, ++d)
        ::new ((void*)d) T(value);
    return d;
}
}  // namespace eastl

// ---------------------------------------------------------------- vector<vector_map> members
namespace eastl {

template <typename T, typename A>
T* vector<T, A>::erase(T* first, T* last) {
    T* const pFirst = first;
    T* const pLast = last;
    T* const position = copy_impl<0, std::random_access_iterator_tag>::do_copy(pLast, this->mpEnd, pFirst);
    DoDestroyValues(position, this->mpEnd);
    this->mpEnd -= (pLast - pFirst);
    return pFirst;
}

template <typename T, typename A>
void vector<T, A>::resize(size_type n) {
    if (n > (size_type)(this->mpEnd - this->mpBegin)) {
        T value;
        insert(this->mpEnd, n - (size_type)(this->mpEnd - this->mpBegin), value);
    } else {
        erase(this->mpBegin + n, this->mpEnd);
    }
}

template <typename T, typename A>
void vector<T, A>::insert(T* position, size_type n, const T& value) {
    if (n <= (size_type)(this->mpCapacity - this->mpEnd)) {
        if (n > 0) {
            const T temp = value;
            const size_type nExtra = (size_type)(this->mpEnd - position);
            if (n < nExtra) {
                uninitialized_copy_ptr(this->mpEnd - n, this->mpEnd, this->mpEnd);
                copy_backward_impl<0, std::random_access_iterator_tag>::do_copy(position, this->mpEnd - n, this->mpEnd);
                fill(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(this->mpEnd, n - nExtra, temp);
                uninitialized_copy_ptr(position, this->mpEnd, this->mpEnd + n - nExtra);
                fill(position, this->mpEnd, temp);
            }
            this->mpEnd += n;
        }
    } else {
        const size_type nPrevSize = size();
        const size_type nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const size_type nNewSize = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        T* const pNewData = DoAllocate(nNewSize);
        T* pNewEnd = uninitialized_copy_ptr(this->mpBegin, position, pNewData);
        pNewEnd = uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = uninitialized_copy_ptr(position, this->mpEnd, pNewEnd + n);
        DoDestroyValues(this->mpBegin, this->mpEnd);
        DoFree(this->mpBegin, capacity());
        this->mpBegin = pNewData;
        this->mpEnd = pNewEnd;
        this->mpCapacity = pNewData + nNewSize;
    }
}

template <typename T, typename A>
template <typename It>
void vector<T, A>::DoAssignFromIterator(It first, It last, std::random_access_iterator_tag) {
    const size_type n = (size_type)(last - first);
    if (n > capacity()) {
        T* const pNewData = DoRealloc(n, first, last);
        DoDestroyValues(this->mpBegin, this->mpEnd);
        DoFree(this->mpBegin, capacity());
        this->mpBegin = pNewData;
        this->mpEnd = this->mpBegin + n;
        this->mpCapacity = this->mpEnd;
    } else if (n <= size()) {
        T* const pNewEnd = copy_impl<0, std::random_access_iterator_tag>::do_copy(first, last, this->mpBegin);
        DoDestroyValues(pNewEnd, this->mpEnd);
        this->mpEnd = pNewEnd;
    } else {
        It position = first + size();
        copy_impl<0, std::random_access_iterator_tag>::do_copy(first, position, this->mpBegin);
        this->mpEnd = uninitialized_copy_ptr(position, last, this->mpEnd);
    }
}

}  // namespace eastl

// ---------------------------------------------------------------- explicit instantiations
// @ 0x007cbd60
template PropMap* MapFixVec::erase(PropMap*, PropMap*);
// @ 0x007cbdc0
template void MapFixVec::insert(PropMap*, MapFixVec::size_type, const PropMap&);
// @ 0x007cc000
template void MapFixVec::DoAssignFromIterator<const PropMap*>(const PropMap*, const PropMap*, std::random_access_iterator_tag);
// @ 0x007cc3c0
template void MapFixVec::resize(MapFixVec::size_type);
// @ 0x007cc580
template eastl::fixed_vector<PropMap, 4, 1>::fixed_vector(const eastl::fixed_vector<PropMap, 4, 1>&);

// ---------------------------------------------------------------- SP::cConfigScriptState / Manager
namespace SP {

struct cOption {
    unsigned int mID;              // +0x00
    unsigned int mDefaultSetting;  // +0x04
    unsigned int mCurrentSetting;  // +0x08
    eastl::fixed_vector<EA::AutoRefCount<cPropertyList>, 4, 1> mPropertySettings;  // +0x0c
    eastl::fixed_vector<PropMap, 4, 1>                         mExternalSettings;  // +0x34
    ~cOption();
};

struct cConfigScriptState {
    void* mpVtable;                       // +0x00
    unsigned int mVendorID;               // +0x04
    unsigned int mCardID;                 // +0x08
    bool mOverrideCardIDs;                // +0x0c
    bool mFoundCard;                      // +0x0d
    char pad0e[2];
    string8 mCurrentCardVendor;           // +0x10
    string8 mCardVendor;                  // +0x20
    string8 mCardName;                    // +0x30
    bool mFirstRun;                       // +0x40
    bool mAbortApp;                       // +0x41
    bool mPad42;                          // +0x42
    bool mPad43;                          // +0x43
    eastl::vector<cOption, sp_vector_allocator> mOptions;     // +0x44
    int mCurrentOptionID;                 // +0x58
    unsigned int mCurrentOptionSetting;   // +0x5c
    eastl::vector<string8, sp_vector_allocator> mConfigStrings;  // +0x60
    eastl::vector<float, sp_vector_allocator>   mConfigNumbers;  // +0x74

    cConfigScriptState();
    ~cConfigScriptState();
    void GatherInformation() {}   // see partial.txt
};

struct IConfigUnknown {
    virtual void AddRef();
    virtual void Release();
};

struct cConfigManager {
    void* mpVtable0;                      // +0x00
    void* mpVtable1;                      // +0x04
    unsigned int mRefCount;               // +0x08
    EA::AutoRefCount<IConfigUnknown> mpPad0c;  // +0x0c
    EA::AutoRefCount<IConfigUnknown> mpPad10;  // +0x10
    unsigned int mPad14;                  // +0x14
    unsigned int mPad18;                  // +0x18
    int mPad1c;                           // +0x1c
    cConfigScriptState mState;            // +0x20
    char padA0[8];
    int mPadA8;                           // +0xa8
    bool mPadAC;                          // +0xac
    bool mPadAD;                          // +0xad
    char padAE[2];
    EA::AutoRefCount<IConfigUnknown> mpPadB0;  // +0xb0

    cConfigManager();
    ~cConfigManager();
};

// @ 0x007cc110
cConfigScriptState::cConfigScriptState()
    : mpVtable(0), mVendorID(0), mCardID(0), mOverrideCardIDs(false), mFoundCard(false),
      mFirstRun(false), mAbortApp(false), mPad42(false), mPad43(true),
      mCurrentOptionID(0), mCurrentOptionSetting(0) {}

// @ 0x007cc190
cConfigScriptState::~cConfigScriptState() {}

// @ 0x007cc310
cConfigManager::cConfigManager()
    : mpVtable0(0), mpVtable1(0), mRefCount(0), mpPad0c(0), mpPad10(0),
      mPad14(0x9a06678c), mPad18(0x24a0e52), mPad1c(0),
      mPadA8(-1), mPadAC(false), mPadAD(false), mpPadB0(0) {}

// @ 0x007cc260
cConfigManager::~cConfigManager() {}

// @ 0x007cc480
namespace {
struct SettingSource {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
    virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1A(); virtual void v1B();
    virtual void v1C(); virtual void v1D(); virtual void v1E(); virtual void v1F();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual unsigned int GetSetting(void* p);   // +0xa0
};

struct OptionTable2 {
    char pad00[0x44];
    char* mBase;    // +0x44
    char pad48[0x10];
    int   mCount;   // +0x58
    int   mIndex;   // +0x5c
};

struct SettingCommand {
    void* mp0;               // +0x0
    SettingSource* mpSource; // +0x4
    void* mp8;               // +0x8
    OptionTable2* mpTable;   // +0xc
    void Execute(EA::ArgScript::cArguments* pArgs);
};
}  // anonymous namespace

// @ 0x007cc480
void SettingCommand::Execute(EA::ArgScript::cArguments* pArgs) {
    void** main = pArgs->MainArguments(1);
    unsigned int setting = mpSource->GetSetting(main[0]);
    OptionTable2* t = mpTable;
    t->mIndex = setting;
    char* p = t->mBase + t->mCount * 0xac;
    SP::cOption* pOption = (SP::cOption*)p;
    unsigned int size = (unsigned int)(pOption->mPropertySettings.mpEnd - pOption->mPropertySettings.mpBegin);
    if (size <= (unsigned int)t->mIndex) {
        pOption->mPropertySettings.resize((size_t)t->mIndex + 1);
        pOption->mExternalSettings.resize((size_t)t->mIndex + 1);
    }
    EA::AutoRefCount<SP::cPropertyList>* pSlot = pOption->mPropertySettings.mpBegin + t->mIndex;
    if (pSlot->mpObject == 0) {
        SP::cPropertyList* pList = new ("App", 0, 0, 0, 0) Editor::cPropertyList();
        *pSlot = pList;
    }
}


}  // namespace SP
