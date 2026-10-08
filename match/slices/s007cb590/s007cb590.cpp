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
    string8& operator=(const string8& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
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


// ---------------------------------------------------------------- GatherInformation helpers
// eastl::basic_string<wchar_t,eastl::allocator> (16 bytes) returned by EA::ConvertToString16.
struct string16 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; unsigned int mAllocator;
    ~string16() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
};
namespace EA {
string16 ConvertToString16(const string8& s);                 // 0x0093c6d0
string8  ConvertToString8(const wchar_t* p, int n = -1);      // 0x0093c440
}
void string8_sprintf(string8* s, const char* fmt, ...);        // 0x00472fe0 (cdecl, string is arg 0)

// Out-of-line views of the two retail vectors (thiscall resize; the element types are plain).
struct SpStringVecView
{
    string8* mpBegin; string8* mpEnd; string8* mpCapacity; unsigned int pad[2];
    void resize(int n);   // 0x00553be0
};
struct SpFloatVecView
{
    float* mpBegin; float* mpEnd; float* mpCapacity; unsigned int pad[2];
    void resize(int n);   // 0x004afc80
};

// SP::GetSystemInfo output (9 strings, then scalars); ctor/dtor are out of line.
struct StrRaw { char* b; char* e; char* cap; unsigned int al; };
struct CBig
{
    StrRaw s[9];            // +0x00
    float  f90;             // +0x90
    int    i94;             // +0x94
    unsigned char b98, b99, b9a, b9b, b9c, pad9d[3];  // +0x98
    float  fa0, fa4, fa8, fac;                        // +0xa0
    CBig();      // 0x006b8460
    ~CBig();     // 0x005f8910
};
void GetSystemInfo(CBig* out);                         // 0x006b8680 (cdecl)

// Path object built from the system-info string (stack object, no destructor).
struct PathObj
{
    unsigned int d[0x100];
    PathObj(const wchar_t* s);   // 0x00930f60 (ret 4)
    const wchar_t* GetFirst();   // 0x00930bf0
    const wchar_t* GetSecond();  // 0x00572590
};

// rw::graphics cached D3D9 caps + adapter block (retail layout; D3DCAPS9 is the first 0x130 bytes).
struct DevCaps {
    unsigned int d00[0x98 / 4];
    unsigned int maxSimultaneousTextures;              // +0x98
    unsigned int d9c[(0xc4 - 0x9c) / 4];
    unsigned char vsMinor, vsMajor; unsigned short padc6;      // +0xc4 VertexShaderVersion
    unsigned int maxVertexShaderConst;                 // +0xc8
    unsigned char psMinor, psMajor; unsigned short padce;      // +0xcc PixelShaderVersion
    unsigned int dd0[(0xf0 - 0xd0) / 4];
    unsigned int numSimultaneousRTs;                   // +0xf0
    unsigned int df4[(0x110 - 0xf4) / 4];
    unsigned int ps20NumTemps;                         // +0x110
    unsigned int d114;
    unsigned int ps20NumInstructionSlots;              // +0x118
    unsigned int d11c[(0x128 - 0x11c) / 4];
    unsigned int maxVS30Slots;                         // +0x128
    unsigned int maxPS30Slots;                         // +0x12c
    unsigned int d130;
    unsigned int deviceId;                             // +0x134
    unsigned int vendorId;                             // +0x138
    unsigned int d13c;
    unsigned int driverLow, driverHigh;                // +0x140
    unsigned int d148[(0x1fc - 0x148) / 4];
    char         description[0x200];                   // +0x1fc
    unsigned int dispW, dispH;                         // +0x3fc
};

bool FUN_006b8250();                                   // 0x006b8250
unsigned int FUN_006b8410();                           // 0x006b8410
bool IsVistaKB940105Required();                        // 0x007c5f50
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent(void);
inline void AssignRaw(string8& dst, const StrRaw& src) {
    if ((const void*)&src != (const void*)&dst)
        dst.assign(src.b, src.e);
}
struct AppProps
{
    unsigned char GetDescription(unsigned int id);   // 0x006a25a0 (thiscall, ret 4)
};
extern AppProps* g_sAppProperties;                                    // 0x015fd918
struct IDev9 {
    struct VT { void* f0; void* f1; void* f2; void* f3;
                unsigned int (__stdcall *GetAvailableTextureMem)(IDev9*); } *vt;   // slot 4 (+0x10)
};
extern IDev9* g_pD3D9Device;                                          // 0x016f89d0
struct DispMode { unsigned int width, height, refresh, format; };
DispMode D3D9GetDesktopDisplayMode();                                 // 0x011f8270 (sret)
DevCaps* GetD3DCAPS9();                                               // 0x011f8af0

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
    void GatherInformation();
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



// @ 0x007cb590
void cConfigScriptState::GatherInformation() {
    SpStringVecView* sv = reinterpret_cast<SpStringVecView*>(&mConfigStrings);
    SpFloatVecView*  nv = reinterpret_cast<SpFloatVecView*>(&mConfigNumbers);
    sv->resize(0xe);
    nv->resize(0x21);
    DevCaps* caps = GetD3DCAPS9();
    CBig big;
    GetSystemInfo(&big);

#define str sv->mpBegin
#define num nv->mpBegin

    str[2].assign("Spore", "Spore" + 5);
    str[4].assign("1.0.0", "1.0.0" + 5);
    str[13].assign("Unknown", "Unknown" + 7);
    str[13].assign("Release", "Release" + 7);
    AssignRaw(str[1], big.s[0]);
    AssignRaw(str[0], big.s[1]);
    AssignRaw(str[7], big.s[2]);
    AssignRaw(str[5], big.s[3]);
    AssignRaw(str[6], big.s[4]);
    AssignRaw(str[8], big.s[5]);
    AssignRaw(str[9], big.s[6]);
    AssignRaw(str[4], big.s[7]);

    PathObj path(EA::ConvertToString16(*(string8*)&big.s[8]).mpBegin);
    str[2] = EA::ConvertToString8(path.GetFirst(), -1);
    str[3] = EA::ConvertToString8(path.GetSecond(), -1);

    num[0] = big.f90;
    num[1] = (float)big.i94;
    num[2] = (big.b9b && big.b9a) ? 1.0f : 0.0f;
    num[3] = big.b9b ? 1.0f : 0.0f;
    num[6] = big.fa8;
    num[7] = big.fac;
    num[8] = big.fa0;
    num[9] = big.fa4;
    num[0x1f] = !FUN_006b8250() ? 1.0f : 0.0f;
    { float* p = &num[0x20]; *p = (float)FUN_006b8410(); }
    ((unsigned short*)&caps->deviceId)[1] = 0;
    if (!mOverrideCardIDs) {
        mVendorID = caps->vendorId;
        mCardID = caps->deviceId;
    }
    DispMode dm = D3D9GetDesktopDisplayMode();
    num[10] = (float)dm.width;
    num[11] = (float)dm.height;
    num[13] = (float)dm.refresh;
    { float* p = &num[14]; *p = (float)g_sAppProperties->GetDescription(0x38d0a09); }
    num[15] = 0.0f;
    num[16] = (float)caps->dispW / (float)caps->dispH;
    { float* p = &num[17]; *p = (float)(g_pD3D9Device->vt->GetAvailableTextureMem(g_pD3D9Device) >> 20); }
    num[18] = (float)caps->maxSimultaneousTextures;
    string8_sprintf(&str[10], "0x%08x%08x", caps->driverHigh, caps->driverLow);
    {
        const char* d = caps->description;
        const char* e = d;
        while (*e++) {}
        str[11].assign(d, d + (e - (d + 1)));
    }
    string8_sprintf(&str[12], "vendor:0x%04x, card:0x%04x", caps->vendorId, caps->deviceId);
    unsigned int vsVer = (caps->vsMajor << 8) | caps->vsMinor;
    unsigned int psVer = (caps->psMajor << 8) | caps->psMinor;
    num[0x13] = (float)vsVer;
    num[0x14] = (float)psVer;
    num[0x15] = (float)caps->numSimultaneousRTs;
    num[0x16] = (float)caps->maxVertexShaderConst;
    num[0x17] = 8.0f;
    num[0x18] = 256.0f;
    num[0x19] = 96.0f;
    num[0x1b] = 12.0f;
    if (psVer >= 0x300) {
        num[0x17] = 224.0f;
        num[0x18] = (float)caps->maxVS30Slots;
        num[0x19] = (float)caps->maxPS30Slots;
        num[0x1b] = 32.0f;
    } else if (psVer >= 0x200) {
        num[0x17] = 32.0f;
        num[0x19] = (float)(int)caps->ps20NumInstructionSlots;
        num[0x1b] = (float)(int)caps->ps20NumTemps;
    }
    num[0x1c] = g_sAppProperties->GetDescription(0x668d4fa1) ? 1.0f : 0.0f;
    num[0x1d] = big.b9c ? 1.0f : 0.0f;
    num[0x1e] = IsVistaKB940105Required() ? 1.0f : 0.0f;
    unsigned int drv = caps->driverLow;
    num[4] = (float)((drv >> 16) * 10000 + (drv & 0xffff));
    num[5] = IsDebuggerPresent() ? 1.0f : 0.0f;
#undef str
#undef num
}

}  // namespace SP
