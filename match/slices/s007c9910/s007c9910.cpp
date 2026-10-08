// Slice s007c9910 -- SP::cConfigManager option-list / eastl vector helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <string.h>
#pragma intrinsic(strlen)

// ---------------------------------------------------------------- masked externs
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
void  __cdecl EA_Free(void*);        // 0x00f47380
void  __cdecl RegisterConfigScriptCommands(void*);   // 0x007c8530
void  __cdecl InsertAutoRef(void* dest, void* src);  // 0x007c8af0
void* __cdecl VecDoInsertValue(void);                // 0x011e0744
void* __cdecl VecAllocGrow(int n, void*, void*);     // 0x007c98b0
void  __cdecl VecDestroyRange16(void*, void*);       // 0x00b007f0
void* __cdecl VecCopyImpl(void*, void*, void*);      // 0x006782c0
void  __cdecl VecUninitCopy(void*, void*, void*, void*, void*); // 0x007c7d70
void  __cdecl VecDestroyRange(void*, void*);         // 0x007c8130
void* __cdecl VecCopyRange(void*, void*, void*);      // 0x007c7e10
void* __cdecl VecReserve(int n, void*, void*);       // 0x007c8210
void  __cdecl UIntVecPushSlow(void*, unsigned*);     // 0x004558a0
void  __cdecl UIntVecReserve(void*, unsigned);       // 0x004e0880

inline void* operator new(size_t size, const char* n, int f, unsigned d, const char* fi, int l)
{ return EA_New((unsigned)size, n, f, (int)d, fi, l); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

struct RC { virtual void AddRef(); virtual void Release(); };
struct AutoRef { uint32_t m0; uint32_t m4; RC* mRC; uint32_t mPad; };

// ---------------------------------------------------------------- vector stubs
struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void reserve(unsigned n);
    void push_back(uint32_t v) {
        if (mpEnd < mpCap) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            UIntVecPushSlow(this, &v);
        }
    }
};

struct AutoRefVec {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCap;
    AutoRef  mInline[4];
    void DoAssignFromIterator(AutoRef* first, AutoRef* last);  // 0x007c9fa0
    void InsertOne(AutoRef* pos, AutoRef* value);              // 0x007c9dc0
};

struct Pair16 { uint64_t key; AutoRef val; };
struct PairVec {
    Pair16* mpBegin;
    Pair16* mpEnd;
    Pair16* mpCap;
    PairVec& operator=(const PairVec&);                        // 0x007ca060
};

struct Vec4 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void InsertOne(uint32_t* pos, uint32_t* value);            // 0x007c99e0
    void InsertN(uint32_t* pos, int n, uint32_t* value);       // 0x007c9bc0
};

struct MapVec {                                                // 0x007ca8e0
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void Destroy();
};

// ---------------------------------------------------------------- Initialize() support types
struct ResourceKey { uint32_t instanceID, typeID, groupID; };

struct Property {                                   // 0x14 bytes (ModAPI App::Property)
    uint32_t d0, d1, d2, d3;
    int16_t  flags;                                 // +0x10 (bit 2: owns data)
    uint16_t type;                                  // +0x12
    Property() : flags(0), type(0) {}
    ~Property() { if (flags & 4) Clear(false); }
    void Set(int type, int flags, const void* data, int itemSize, int count);   // 0x0093dd80
    void Clear(bool b);                                                         // 0x0093db80
    void SetKey(const ResourceKey& k) { d0 = k.instanceID; d1 = k.typeID; d2 = k.groupID; type = 0x20; }
};

struct PropList : RC {                              // App::PropertyList (Editor::cPropertyList)
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, const Property* p);                   // +0x14
    char pad04[0x08 - 0x04];
    ResourceKey mKey;                               // +0x08
};
struct cPropertyList : PropList {
    char pad14[0x38 - 0x14];
    cPropertyList();                                // 0x006a1c40
};

struct IParser : RC {
    virtual void v2(); virtual void v3();
    virtual void AddState(void* p);                 // +0x10
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void Reset(int a, int b);               // +0x24
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
    virtual void v45(); virtual void v46();
    virtual void SetFlags(int v);                   // +0xbc
};
struct IFileParser : RC {
    virtual void v2(); virtual void v3();
    virtual void SetParser(IParser* p);             // +0x10
    virtual void v5();
    virtual void Begin();                           // +0x18
    virtual void SetPath(const char* path, int mode);   // +0x1c
    virtual bool Run();                             // +0x20
};
IFileParser* __cdecl CreateFileParser();            // 0x00840940
IParser*     __cdecl CreateParser();                // 0x008408d0

struct IResAreaMgr {                                // vtable +0x20 used to register a property list
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Register(PropList* pl, int a, void* area, int b, int c);       // +0x20
};
struct ICheatSub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                   virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                   virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
                   virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
                   virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
                   virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
                   virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
                   virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
                   virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
                   virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
                   virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
                   virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
                   virtual void v48();
                   virtual int GetValue(); };                                     // +0xc4
struct ICheat { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
                virtual void v12(); virtual void v13();
                virtual ICheatSub* GetSub(); };                                   // +0x38
ICheat*       __cdecl GetCheatManager();            // 0x0067de20
IResAreaMgr*  __cdecl GetResMgr();                  // 0x0067dcd0
void*         __cdecl GetSaveArea(uint32_t id);       // 0x006b1f90

// eastl::basic_string<char, eastl::allocator> (12 bytes); only the pieces Initialize needs.
extern char gEmptyString[2];                        // 0x01667bac
struct EaString {
    char* mpBegin; char* mpEnd; char* mpCap;
    EaString() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCap(gEmptyString + 1) {}
    ~EaString() { if (mpCap - mpBegin > 1 && mpBegin) EA_Free(mpBegin); }
    void assign(const char* b, const char* e);       // 0x00454cb0
    void append(const char* b, const char* e);       // 0x00455d60
};

// SP::SimpleVector<unsigned int> with the sp_vector_allocator
struct SpUIntVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    SpUIntVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~SpUIntVec() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EA_Free(mpBegin); }
    void DoInsertValue(uint32_t* pos, const uint32_t& v);                  // 0x004558a0
    void push_back(const uint32_t& v) {
        if (mpEnd < mpCap) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

struct MapElem {                                    // vector_map<u64, PropertyListPtr> element, 0x18 bytes
    struct Entry { uint32_t a, b; PropList* pl; uint32_t pad; };
    Entry* mpBegin; Entry* mpEnd;
    char pad[0x10];
};

struct cOption {
    uint32_t id; uint32_t def; uint32_t cur;
    PropList** resBegin;                            // +0x0c fixed_vector<PropertyListPtr,4>
    PropList** resEnd;                              // +0x10
    char pad14[0x34 - 0x14];
    MapElem* mapBegin;                              // +0x34 fixed_vector<vector_map<..>,4>
    MapElem* mapEnd;                                // +0x38
    char pad3c[0xac - 0x3c];
};
struct cConfigManager {
    char pad00[0x0c];
    IFileParser* mFileParser; // +0x0c
    IParser* mParser;         // +0x10
    char pad14[0x20 - 0x14];
    char mState[0x44];        // +0x20
    cOption* mOptionsBegin;   // +0x64
    cOption* mOptionsEnd;     // +0x68
    char pad6c[0x80 - 0x6c];
    void* mStrings;           // +0x80
    void* mStringsEnd;        // +0x84

    void GetOptionIDs(UIntVec* out);          // 0x007ca150
    void Initialize(const char* path);        // 0x007ca1c0
};

// @ 0x007c9910
void* __cdecl CopyAutoRefRange(void* first, void* last, void* dest)
{
    while (first != last) {
        if (dest) {
            InsertAutoRef(dest, first);
            ((char*)dest)[0x14] = ((char*)first)[0x14];
        }
        first = (char*)first + 0x18;
        dest = (char*)dest + 0x18;
    }
    return dest;
}

// @ 0x007c99e0
void Vec4::InsertOne(uint32_t* pos, uint32_t* value)
{
    uint32_t* end = mpEnd;
    if (end != mpCap) {
        if (pos <= value && value < end)
            value++;
        uint32_t last = 0;
        if (end)
            last = *(end - 1);
        if (end) {
            *end = last;
            if (last)
                ((RC*)last)->AddRef();
        }
        VecCopyRange(pos, end - 1, end);
        uint32_t old = *value;
        uint32_t cur = *pos;
        if (old != cur) {
            if (old)
                ((RC*)old)->AddRef();
            *pos = old;
            if (cur)
                ((RC*)cur)->Release();
        }
        mpEnd = end + 1;
        return;
    }
    int count = (int)(end - mpBegin) >> 2;
    unsigned cap = count ? (unsigned)count * 2 : 1;
    uint32_t* buf = cap ? (uint32_t*)EA_New(cap * 4, "App", 0, 0, 0, 0xd1) : 0;
    (void)VecDoInsertValue();
    (void)value;
    mpBegin = buf;
}

// @ 0x007c9bc0
void Vec4::InsertN(uint32_t* pos, int n, uint32_t* value)
{
    int size = (int)(mpCap - mpEnd) >> 2;
    if ((unsigned)size < (unsigned)n) {
        int count = (int)(mpEnd - mpBegin) >> 2;
        unsigned cap = count * 2;
        if (count == 0) cap = 1;
        unsigned need = (unsigned)count + n;
        if (need < cap) need = cap;
        uint32_t* buf = need ? (uint32_t*)EA_New(need * 4, "App", 0, 0, 0, 0xd1) : 0;
        (void)VecDoInsertValue();
        mpBegin = buf;
    }
    (void)pos; (void)value;
}

// @ 0x007c9dc0
void AutoRefVec::InsertOne(AutoRef* pos, AutoRef* value)
{
    AutoRef* end = mpEnd;
    if (end != mpCap) {
        if (pos <= value && value < end)
            value++;
        if (end) {
            end->m0 = end[-1].m0;
            end->m4 = end[-1].m4;
            end->mRC = end[-1].mRC;
            if (end->mRC)
                end->mRC->AddRef();
        }
        VecCopyRange(pos, end - 1, end);
        pos->m0 = value->m0;
        pos->m4 = value->m4;
        RC* s = value->mRC;
        RC* d = pos->mRC;
        if (s != d) {
            if (s) s->AddRef();
            pos->mRC = s;
            if (d) d->Release();
        }
        mpEnd = end + 1;
        return;
    }
    int count = (int)(end - mpBegin);
    unsigned cap = count ? (unsigned)count * 2 : 1;
    AutoRef* buf = cap ? (AutoRef*)EA_New(cap * 0x10, "App", 0, 0, 0, 0xd1) : 0;
    (void)VecDoInsertValue();
    (void)value;
    mpBegin = buf;
}

// @ 0x007c9fa0
void AutoRefVec::DoAssignFromIterator(AutoRef* first, AutoRef* last)
{
    AutoRef* b = mpBegin;
    int n = (int)(last - first);
    if (n > (int)(mpCap - b)) {
        AutoRef* nb = (AutoRef*)VecAllocGrow(n, first, last);
        VecDestroyRange16(b, mpEnd);
        if (b != 0 && b != mInline)
            EA_Free(b);
        mpBegin = nb;
        mpEnd = nb + n;
        mpCap = nb + n;
        return;
    }
    if (n <= (int)(mpEnd - b)) {
        AutoRef* e = (AutoRef*)VecCopyImpl(first, last, b);
        VecDestroyRange16(e, mpEnd);
        mpEnd = e;
        return;
    }
    AutoRef* mid = first + (mpEnd - b);
    VecCopyImpl(first, mid, b);
    VecUninitCopy(0, mid, last, mpEnd, 0);
    mpEnd = mpBegin + n;
}

// @ 0x007ca060
PairVec& PairVec::operator=(const PairVec& x)
{
    if (&x != this) {
        int n = (int)(x.mpEnd - x.mpBegin);
        if (n > (int)(mpCap - mpBegin)) {
            Pair16* nb = (Pair16*)VecReserve(n, x.mpBegin, x.mpEnd);
            VecDestroyRange(mpBegin, mpEnd);
            if (mpBegin) EA_Free(mpBegin);
            mpBegin = nb;
            mpEnd = nb + n;
            mpCap = nb + n;
            return *this;
        }
        if (n <= (int)(mpEnd - mpBegin)) {
            Pair16* e = (Pair16*)VecCopyRange(x.mpBegin, x.mpEnd, mpBegin);
            VecDestroyRange(e, mpEnd);
            mpEnd = mpBegin + n;
            return *this;
        }
        VecCopyRange(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
        VecUninitCopy(0, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, 0);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x007ca150
void cConfigManager::GetOptionIDs(UIntVec* out)
{
    out->reserve((unsigned)((int)((char*)mOptionsEnd - (char*)mOptionsBegin) / 0xac));
    cOption* p = mOptionsBegin;
    while (p != mOptionsEnd) {
        out->push_back(p->id);
        p++;
    }
}

// @ 0x007ca1c0
void cConfigManager::Initialize(const char* path)
{
    if (!mFileParser) {
        IFileParser* fp = CreateFileParser();
        IFileParser* oldFp = mFileParser;
        if (fp != oldFp) {
            if (fp)
                fp->AddRef();
            mFileParser = fp;
            if (oldFp)
                oldFp->Release();
        }
        mFileParser->v2();
        IParser* pa = CreateParser();
        IParser* oldPa = mParser;
        if (pa != oldPa) {
            if (pa)
                pa->AddRef();
            mParser = pa;
            if (oldPa)
                oldPa->Release();
        }
        mFileParser->SetParser(mParser);
        mParser->Reset(0, 0);
        mParser->AddState(mState);
        mParser->SetFlags(GetCheatManager()->GetSub()->GetValue());
        RegisterConfigScriptCommands(mParser);
    }
    mFileParser->Begin();

    EaString str;
    str.assign(path, path + strlen(path));
    str.append("Options.txt", "Options.txt" + 11);
    mFileParser->SetPath(str.mpBegin, 5);
    if (!mFileParser->Run())
        return;

    IResAreaMgr* mgr = GetResMgr();
    void* area = GetSaveArea(0x11ac19e);
    SpUIntVec ids;
    SpUIntVec firsts;
    SpUIntVec counts;
    int numOptions = (int)(mOptionsEnd - mOptionsBegin);
    for (int oi = 0; oi != numOptions; oi++) {
        cOption* o = &mOptionsBegin[oi];
        if (o->id == 0x46170a2 || o->id == 0x46170a1)
            continue;
        int n = (int)(o->resEnd - o->resBegin);
        int first = 0;
        if (n > 0) {
            PropList** pp = o->resBegin;
            while (*pp == 0) {
                first++;
                pp++;
                if (first >= n)
                    break;
            }
        }
        ids.push_back(o->id);
        firsts.push_back((uint32_t)first);
        counts.push_back((uint32_t)n);
        uint32_t id = o->id;
        for (int k = first; k < n; k++) {
            PropList* pl = o->resBegin[k];
            if (pl) {
                pl->mKey.instanceID = id;
                pl->mKey.typeID = 0xb1b104;
                pl->mKey.groupID = (k & 0xff) | 0x40470100;
                mgr->Register(o->resBegin[k], 0, area, 0, 0);
            }
            MapElem* me = &o->mapBegin[k];
            if (me->mpBegin != me->mpEnd) {
                int m = 1;
                for (MapElem::Entry* e = me->mpBegin; e != me->mpEnd; e++) {
                    ResourceKey key;
                    key.instanceID = e->a;
                    key.typeID = 0xb1b104;
                    key.groupID = e->b;
                    PropList* epl = e->pl;
                    {
                        Property p;
                        p.SetKey(key);
                        epl->SetProperty(0x5daaffe, &p);
                    }
                    epl->mKey.instanceID = id;
                    epl->mKey.typeID = 0xb1b104;
                    epl->mKey.groupID = ((((m & 0x1f) << 24) | 0x40470100) & 0xffffff00) | (k & 0xff);
                    m++;
                    mgr->Register(epl, 0, area, 0, 0);
                }
            }
        }
    }

    cPropertyList* list = new ("App/ConfigManager", 0, 0, 0, 0) cPropertyList();
    {
        Property p;
        p.Set(10, 0x98, ids.mpBegin, 4, (int)(ids.mpEnd - ids.mpBegin));
        list->SetProperty(0x5daafff, &p);
    }
    {
        Property p;
        p.Set(10, 0x98, firsts.mpBegin, 4, (int)(firsts.mpEnd - firsts.mpBegin));
        list->SetProperty(0x5dab000, &p);
    }
    {
        Property p;
        p.Set(10, 0x98, counts.mpBegin, 4, (int)(counts.mpEnd - counts.mpBegin));
        list->SetProperty(0x5dab001, &p);
    }
    list->mKey.instanceID = 0;
    list->mKey.typeID = 0xb1b104;
    list->mKey.groupID = 0x40470000;
    mgr->Register(list, 0, area, 0, 0);
}

// @ 0x007ca8e0
void MapVec::Destroy()
{
    // element-wise teardown of vector_map<u64,AutoRef> then free (see partial.txt)
}
