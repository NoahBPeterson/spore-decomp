// Slice s007ca950: SP::cOption property-command module.
// eastl::vector_map<unsigned __int64, EA::AutoRefCount<SP::cPropertyList>> instances,
// fixed_vector helpers, the option Execute() commands and SP::cOption's destructor.
// Flags: /O2 /MD /Gy /EHsc /TP

#include "s007ca950.h"

// ---------------------------------------------------------------- masked callees
extern "C" bool __cdecl SPKeyFromName(void* pOutKey, const wchar_t* pName, int a, int b);  // 0x0068d5a0
int GetPropID(const char* pName);                                                          // 0x007c8bb0

namespace EA { namespace ArgScript {
struct cArguments {
    void** MainArguments(int n);
    void** OptionArguments(const char* pName, int n);
};
}}

typedef eastl::pair<uint64, EA::AutoRefCount<SP::cPropertyList> > PropPair;
typedef eastl::vector<PropPair, eastl::allocator>                PropVec;
typedef eastl::vector_map<uint64, EA::AutoRefCount<SP::cPropertyList>,
                          eastl::less<uint64>, eastl::allocator, PropVec> PropMap;
typedef eastl::vector<EA::AutoRefCount<SP::cPropertyList>,
                      eastl::fixed_vector_allocator<4, 4, 4, 0, 1> > PropFixVec;
typedef eastl::vector<PropMap,
                      eastl::fixed_vector_allocator<sizeof(PropMap), 4, 4, 0, 1> > MapFixVec;

// ---------------------------------------------------------------- vector / map template members
namespace eastl {

template <typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector& x) {
    if (&x != this) {
        const size_type n = x.size();
        if (n > capacity()) {
            T* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            DoDestroyValues(this->mpBegin, this->mpEnd);
            DoFree(this->mpBegin, capacity());
            this->mpBegin = pNewData;
            this->mpEnd = pNewData + n;
            this->mpCapacity = pNewData + n;
        } else if (n <= size()) {
            T* const pNewEnd =
                copy_impl<0, std::random_access_iterator_tag>::do_copy(x.mpBegin, x.mpEnd, this->mpBegin);
            DoDestroyValues(pNewEnd, this->mpEnd);
            this->mpEnd = pNewEnd;
        } else {
            T* const position = x.mpBegin + size();
            copy_impl<0, std::random_access_iterator_tag>::do_copy(x.mpBegin, position, this->mpBegin);
            this->mpEnd = uninitialized_copy_ptr(position, x.mpEnd, this->mpEnd);
        }
    }
    return *this;
}

template <typename T, typename A>
T* vector<T, A>::insert(T* position, const T& value) {
    const int n = (int)(position - this->mpBegin);
    if ((position == this->mpEnd) && (this->mpEnd != this->mpCapacity)) {
        ::new (this->mpEnd++) T(value);
    } else {
        DoInsertValue(position, value);
    }
    return this->mpBegin + n;
}

template <typename T, typename A>
void vector<T, A>::resize(size_type n) {
    if (n > size()) {
        insert(this->mpEnd, n - size(), T());
    } else {
        erase(this->mpBegin + n, this->mpEnd);
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
// @ 0x007ca950
template PropPair* PropVec::insert(PropPair*, const PropPair&);
// @ 0x007ca9f0
template PropMap::iterator PropMap::insert(PropMap::iterator, const PropMap::value_type&);
// @ 0x007cab40
template void PropFixVec::resize(PropFixVec::size_type);
// @ 0x007cabc0
template eastl::pair<PropMap::iterator, bool> PropMap::insert(const PropMap::value_type&);
// @ 0x007cac20
template EA::AutoRefCount<SP::cPropertyList>& PropMap::operator[](const PropMap::key_type&);
// @ 0x007caac0
template PropMap* eastl::copy_backward_impl<0, std::random_access_iterator_tag>::do_copy<PropMap*, PropMap*>(PropMap*, PropMap*, PropMap*);
// @ 0x007cab00
template PropMap* eastl::copy_impl<0, std::random_access_iterator_tag>::do_copy<const PropMap*, PropMap*>(const PropMap*, const PropMap*, PropMap*);
// @ 0x007cb450
template void eastl::fill<PropMap*, PropMap>(PropMap*, PropMap*, const PropMap&);
// @ 0x007cb3e0
template eastl::fixed_vector<EA::AutoRefCount<SP::cPropertyList>, 4, 1>::fixed_vector(const eastl::fixed_vector<EA::AutoRefCount<SP::cPropertyList>, 4, 1>&);
// @ 0x007ca060 (vector<pair<u64,AR>>::operator=, callee)
template PropVec& PropVec::operator=(const PropVec&);

// ---------------------------------------------------------------- SP::cOption
namespace SP {

struct cOption {
    unsigned int mID;              // +0x00
    unsigned int mDefaultSetting;  // +0x04
    unsigned int mCurrentSetting;  // +0x08
    eastl::fixed_vector<EA::AutoRefCount<cPropertyList>, 4, 1> mPropertySettings;  // +0x0c
    eastl::fixed_vector<PropMap, 4, 1>                         mExternalSettings;  // +0x34
    ~cOption();
};

// @ 0x007cb390
cOption::~cOption() {}

typedef eastl::vector<cOption, eastl::fixed_vector_allocator<sizeof(cOption), 4, 4, 0, 1> > cOptionVec;

}  // namespace SP

// @ 0x007cb510
template void SP::cOptionVec::DoDestroyValues(SP::cOption*, SP::cOption*);
// @ 0x007cb480
template SP::cOption* eastl::uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_commit<SP::cOption*, SP::cOption*>(SP::cOption*, SP::cOption*, SP::cOption*);

// ---------------------------------------------------------------- option command classes
namespace {

struct cPropertySource {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
    virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1A(); virtual void v1B();
    virtual void v1C(); virtual void v1D(); virtual void v1E(); virtual void v1F();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    virtual bool  GetBool(void* p);    // +0x94
    virtual float GetFloat(void* p);   // +0x98
    virtual int   GetInt(void* p);     // +0x9c
};

struct OptionTable {
    char pad00[0x44];
    char* mBase;    // +0x44
    char pad48[0x10];
    int   mCount;   // +0x58
    int   mIndex;   // +0x5c
};

struct CommandBase {
    void* mp0;                // +0x0
    cPropertySource* mpSource; // +0x4
    void* mp8;                // +0x8
    OptionTable* mpTable;     // +0xc
};

void __cdecl ThrowBadPropListName();

SP::cPropertyList* GetPropListSettings(const void* pName, PropMap* pMap);

// Duplicated (inlined) prologue shared by the five commands.
static inline SP::cPropertyList* GetTargetList(CommandBase* pThis, void** pOption) {
    if (pOption) {
        OptionTable* t = pThis->mpTable;
        char* p = t->mBase + t->mCount * 0xac;
        return GetPropListSettings(pOption[0], (PropMap*)(*(char**)(p + 0x34) + t->mIndex * 0x18));
    }
    OptionTable* t = pThis->mpTable;
    char* p = t->mBase + t->mCount * 0xac;
    return (*(SP::cPropertyList***)(p + 0xc))[t->mIndex];
}

class cOptionBoolPropertyCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments* pArgs);
};
class cOptionIntPropertyCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments* pArgs);
};
class cOptionFloatPropertyCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments* pArgs);
};
class cOptionPropertiesCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments* pArgs);
};
class SomeOptionPropertiesCommand : public CommandBase {
public:
    void Execute(EA::ArgScript::cArguments* pArgs);
};

// @ 0x007cae30
void cOptionBoolPropertyCommand::Execute(EA::ArgScript::cArguments* pArgs) {
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList* pList = GetTargetList(this, opt);
    if (pList) {
        bool b = mpSource->GetBool(main[1]);
        EA::Variant v;
        v = b;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007caf40
void cOptionIntPropertyCommand::Execute(EA::ArgScript::cArguments* pArgs) {
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList* pList = GetTargetList(this, opt);
    if (pList) {
        int i = mpSource->GetInt(main[1]);
        EA::Variant v;
        v = i;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007cb050
void cOptionFloatPropertyCommand::Execute(EA::ArgScript::cArguments* pArgs) {
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList* pList = GetTargetList(this, opt);
    if (pList) {
        float f = mpSource->GetFloat(main[1]);
        EA::Variant v;
        v = f;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007cb160
void cOptionPropertiesCommand::Execute(EA::ArgScript::cArguments* pArgs) {
    void** main = pArgs->MainArguments(2);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList* pList = GetTargetList(this, opt);
    if (pList) {
        EA::ResourceMan::Key key;
        key.mInstance = 0; key.mType = 0; key.mGroup = 0; key.mPad = 0;
        SPKeyFromName(&key, (const wchar_t*)main[1], 0, 0);
        EA::Variant v;
        v = key;
        pList->SetProperty(GetPropID((const char*)main[0]), v);
    }
}

// @ 0x007cb270
void SomeOptionPropertiesCommand::Execute(EA::ArgScript::cArguments* pArgs) {
    void** main = pArgs->MainArguments(1);
    void** opt = pArgs->OptionArguments("list", 1);
    SP::cPropertyList* pList = GetTargetList(this, opt);
    EA::ResourceMan::Key key;
    key.mInstance = 0; key.mType = 0; key.mGroup = 0; key.mPad = 0;
    SPKeyFromName(&key, (const wchar_t*)main[0], 0, 0);
    SP::IPropertyManager* pm = SP::PropertyManager();
    EA::AutoRefCount<SP::cPropertyList> result;
    if (pm->GetPropertyList(key.mInstance, key.mGroup, result) && pList)
        pList->v30(result.mpObject);
}

// @ 0x007cace0
SP::cPropertyList* GetPropListSettings(const void* pName, PropMap* pMap) {
    EA::ResourceMan::Key key;
    key.mInstance = 0; key.mType = 0; key.mGroup = 0; key.mPad = 0;
    if (!SPKeyFromName(&key, (const wchar_t*)pName, 0, 0))
        ThrowBadPropListName();
    uint64 id = ((uint64)key.mInstance) | ((uint64)key.mGroup << 32);
    eastl::pair<PropMap::iterator, bool> result =
        pMap->insert(PropMap::value_type(id, EA::AutoRefCount<SP::cPropertyList>(0)));
    if (result.second) {
        SP::IPropertyManager* pm = SP::PropertyManager();
        pm->HasPropertyList(key.mInstance, key.mGroup);
        Editor::cPropertyList* pList = new ("App", 0, 0, 0, 0) Editor::cPropertyList();
        result.first->second = pList;
    }
    return result.first->second.mpObject;
}

}  // anonymous namespace
