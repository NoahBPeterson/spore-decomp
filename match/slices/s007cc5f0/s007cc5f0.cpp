// Slice s007cc5f0: SP::cOption and the cOption vector + config option commands.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

#include "../s007ca950/s007ca950.h"

namespace EA { namespace ArgScript {
struct cArguments {
    void** MainArguments(int n);
    void** OptionArguments(const char* pName, int n);
};
}}

// SP's heap vector allocator (8 bytes, header word before the block).
struct sp_vector_allocator {
    unsigned int mData[2];
    void deallocate(void* p, unsigned int) {
        if (p && ((unsigned int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
};

// eastl::basic_string<char,eastl::allocator> (16 bytes).
extern char gEmptyChar;
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; unsigned int mAllocator;
    string8() : mpBegin(&gEmptyChar), mpEnd(&gEmptyChar), mpCapacity(&gEmptyChar + 1), mAllocator(0) {}
    ~string8() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin); }
    void clear() {
        if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; }
    }
};

typedef eastl::pair<uint64, EA::AutoRefCount<SP::cPropertyList> > PropPair;
typedef eastl::vector<PropPair, eastl::allocator>                PropVec;
typedef eastl::vector_map<uint64, EA::AutoRefCount<SP::cPropertyList>,
                          eastl::less<uint64>, eastl::allocator, PropVec> PropMap;
typedef eastl::vector<PropMap, eastl::fixed_vector_allocator<sizeof(PropMap), 4, 4, 0, 1> > MapFixVec;

namespace SP {
struct cOption {
    unsigned int mID;              // +0x00
    unsigned int mDefaultSetting;  // +0x04
    unsigned int mCurrentSetting;  // +0x08
    eastl::fixed_vector<EA::AutoRefCount<cPropertyList>, 4, 1> mPropertySettings;  // +0x0c
    eastl::fixed_vector<PropMap, 4, 1>                         mExternalSettings;  // +0x34
    cOption();
    cOption(const cOption& x);
    cOption& operator=(const cOption& x);
    ~cOption();
};

typedef eastl::vector<cOption, sp_vector_allocator> cOptionVec;
}  // namespace SP

// ---------------------------------------------------------------- vector<cOption> members
namespace eastl {

template <typename T, typename A>
void vector<T, A>::DoInsertValue(T* position, const T& value) {
    if (this->mpEnd != this->mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < this->mpEnd))
            ++pValue;
        ::new (this->mpEnd) T(*(this->mpEnd - 1));
        copy_backward_impl<0, std::random_access_iterator_tag>::do_copy(position, this->mpEnd - 1, this->mpEnd);
        *position = *pValue;
        ++this->mpEnd;
    } else {
        const size_type nPrevSize = size();
        const size_type nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        T* const pNewData = DoAllocate(nNewSize);
        T* pNewEnd = uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_start(this->mpBegin, position, pNewData);
        uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_commit(this->mpBegin, position, pNewData);
        ::new (pNewEnd) T(value);
        ++pNewEnd;
        T* const pNewEnd2 = uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_start(position, this->mpEnd, pNewEnd);
        uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_commit(position, this->mpEnd, pNewEnd);
        DoFree(this->mpBegin, capacity());
        this->mpBegin = pNewData;
        this->mpEnd = pNewEnd2;
        this->mpCapacity = pNewData + nNewSize;
    }
}

template <typename T, typename A>
void vector<T, A>::push_back() {
    if (this->mpEnd != this->mpCapacity)
        ::new (this->mpEnd++) T();
    else
        DoInsertValue(this->mpEnd, T());
}

template <typename T, typename A>
T* vector<T, A>::erase(T* first, T* last) {
    T* const position = copy_impl<0, std::random_access_iterator_tag>::do_copy(last, this->mpEnd, first);
    DoDestroyValues(position, this->mpEnd);
    this->mpEnd -= (last - first);
    return first;
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

}  // namespace eastl

// @ 0x007cc5f0
SP::cOption& SP::cOption::operator=(const SP::cOption& x) {
    mID = x.mID;
    mDefaultSetting = x.mDefaultSetting;
    mCurrentSetting = x.mCurrentSetting;
    mPropertySettings = x.mPropertySettings;
    mExternalSettings = x.mExternalSettings;
    return *this;
}

// @ 0x007cc6f0
SP::cOption::cOption(const cOption& x)
    : mID(x.mID), mDefaultSetting(x.mDefaultSetting), mCurrentSetting(x.mCurrentSetting),
      mPropertySettings(x.mPropertySettings), mExternalSettings(x.mExternalSettings) {}

// @ 0x007ccc30
void cConfigScriptStateReset(void* pThis) {
    char* p = (char*)pThis;
    *(int*)(p + 0x58) = -1;
    *(int*)(p + 0x5c) = -1;
    SP::cOptionVec* pOptions = (SP::cOptionVec*)(p + 0x44);
    pOptions->erase(pOptions->mpBegin, pOptions->mpEnd);
    *(char*)(p + 0xd) = 0;
    string8* pS0 = (string8*)(p + 0x10); pS0->clear();
    string8* pS1 = (string8*)(p + 0x20); pS1->clear();
    string8* pS2 = (string8*)(p + 0x30); pS2->clear();
}

// ---------------------------------------------------------------- explicit instantiations
// @ 0x007cc7f0
template void SP::cOptionVec::DoInsertValue(SP::cOption*, const SP::cOption&);
// @ 0x007cc9a0
template void SP::cOptionVec::push_back();
// @ 0x007ccc30 (vector<cOption>::erase, callee)
template SP::cOption* SP::cOptionVec::erase(SP::cOption*, SP::cOption*);

// ---------------------------------------------------------------- remaining commands (partial)
// @ 0x007ccb10
void cOptionBlockCommandExecute(void*, EA::ArgScript::cArguments*) {}
// @ 0x007cccc0
void cConfigManagerAddResolutionOption(void*) {}
// @ 0x007cce50
void cConfigManagerLoadResolutionOptions(void*) {}
// @ 0x007cd340
void cConfigManagerLoadOptionSetup(void*) {}

