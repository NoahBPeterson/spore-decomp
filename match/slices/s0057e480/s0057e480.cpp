// slice s0057e480 — editor helpers (mix of implemented small helpers and oversized stubs).
#include "types.h"

typedef unsigned int size_t;
void __cdecl operator_delete_array(void* p);                                                    // 0x00F47380

// ---------------------------------------------------------------------------------------------
// 0x0057ed80 — init a 12-byte object from a source
struct cUnkEd80 {
    void* m0;
    void* m4;
    void* m8;
    void FUN_0057cc10(void* p);
    void* Init(void* p, void* unused);
};

// @ 0x0057ed80
void* cUnkEd80::Init(void* p, void* unused)
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    FUN_0057cc10(p);
    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x0057edf0 — erase the element after `pos`
void DoInsertValue(void* dst, void* src, int n);   // 0x011e0744 (cdecl)

struct cVec16 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* EraseAfter(void* pos);
};

// @ 0x0057edf0
void* cVec16::EraseAfter(void* pos)
{
    char* src = (char*)pos + 4;
    if (src < (char*)mpEnd)
        DoInsertValue(pos, src, (int)((char*)mpEnd - src));
    mpEnd = (char*)mpEnd - 4;
    return pos;
}

// ---------------------------------------------------------------------------------------------
// 0x0057eda0 — eastl::basic_string<wchar_t>::trim
namespace eastl {
struct allocator {};

template <typename T, typename Alloc = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Alloc mAlloc;

    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(0); }
    basic_string(const basic_string& x);                // 0x0056e2d0
    ~basic_string()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_array(mpBegin);
        }
    }
    void RangeInitialize(const T* p);                   // 0x00579a90
    size_t find_first_not_of(const T* s, size_t pos);   // 0x00579af0
    basic_string& erase(size_t pos, size_t n);          // 0x004228e0
    void rtrim();                                       // 0x005541e0

    // @ 0x0057eda0
    void trim()
    {
        {
            T ws[3] = { (T)0x20, (T)9, (T)0 };
            erase(0, find_first_not_of(ws, 0));
        }
        return rtrim();
    }
};

template class basic_string<wchar_t, allocator>;
} // namespace eastl

// ---------------------------------------------------------------------------------------------
// Editor mode (cAppModeEditorBase, retail layout) and EASTL vector instances.
// Fields are reached through At<T>(off) so the retail offsets stay explicit.
#pragma pack(push, 4)

void* __cdecl operator new(unsigned int, const char*, int, unsigned int, const char*, int);   // 0x00F473A0

template <class T> inline T& At(void* base, int off) { return *(T*)((char*)base + off); }

struct RC0 { virtual int AddRef(); virtual int Release(); };                        // slots at +0 / +4
struct RC1 { virtual void s0(); virtual int AddRef(); virtual int Release(); };     // slots at +4 / +8

template <class T> struct VtRef {                                                   // AutoRefCount, AddRef at +4, Release at +8
    T* p;
    VtRef(T* o) : p(o) { if (p) p->AddRef(); }
    ~VtRef() { if (p) p->Release(); }
};

// ---- eastl::vector<T> -----------------------------------------------------------------------
namespace eastl {
struct false_type {};
struct EASTLAllocator { const char* mpName; EASTLAllocator() {} };

template <class T> struct generic_iterator {
    T mIterator;
    explicit generic_iterator(const T& x) : mIterator(x) {}
    const T& base() const { return mIterator; }
};
template <class T> struct value_of;
template <class T> struct value_of<T*> { typedef T type; };
template <class T> struct value_of<const T*> { typedef T type; };
template <class T> struct has_trivial_relocate : public false_type {};

template <class In, class Out>
generic_iterator<Out> uninitialized_copy_impl(generic_iterator<In> first, generic_iterator<In> last,
                                              generic_iterator<Out> dest, false_type);
template <class It, class T>
void uninitialized_fill_n_impl(generic_iterator<It> first, uint32_t n, const T& value, false_type);

template <class First, class Last, class Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    const generic_iterator<Result> i(uninitialized_copy_impl(generic_iterator<First>(first),
                                                             generic_iterator<Last>(last),
                                                             generic_iterator<Result>(result),
                                                             has_trivial_relocate<typename value_of<Result>::type>()));
    return i.base();
}
template <class T>
inline void uninitialized_fill_n_ptr(T* first, uint32_t n, const T& value)
{
    uninitialized_fill_n_impl(generic_iterator<T*>(first), n, value, has_trivial_relocate<T>());
}

template <class Bi1, class Bi2>
inline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
template <class T>
inline T* copy_backward_inl(T* first, T* last, T* resultEnd)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, resultEnd);
}

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    EASTLAllocator mAllocator;

    inline uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    inline T* DoAllocate(uint32_t n)
    {
        return n ? (T*)::operator new(n * sizeof(T), "Editor", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL\\allocator.h", 0xd1)
                 : 0;
    }
    inline void DoFree(T* p, uint32_t)
    {
        if (p) {
            if (*((uint32_t*)p - 1))
                operator_delete_array(p);
        }
    }
    T* DoRealloc(uint32_t n, const T* first, const T* last);
    void DoInsertValue(T* position, const T& value);
    void DoInsertValues(T* position, uint32_t n, const T& value);
    vector& operator=(const vector& x);
};
} // namespace eastl

struct Rec30 {                                   // 0x30-byte element: user copy ctor, trivial assignment
    uint32_t d[12];
    Rec30(const Rec30& o);                       // 0x00576900
};
inline void* operator new(unsigned int, void* p) { return p; }
struct Rec18 { uint32_t d[6]; };                 // 0x18-byte POD element

namespace eastl {

template <class T> T* copy_ool(const T* first, const T* last, T* dest);        // out of line
template <class T> T* uninitialized_copy_ool(T* first, T* last, T* dest);      // out of line (0x00576A10)
template <> Rec18* vector<Rec18>::DoRealloc(uint32_t n, const Rec18* first, const Rec18* last);   // 0x0050E750

// @ 0x0057ee20
template <> vector<Rec18>& vector<Rec18>::operator=(const vector<Rec18>& x)
{
    if (&x != this) {
        const uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            Rec18* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpCapacity = pNewData + n;
            mpBegin = pNewData;
            mpEnd = mpBegin + n;
        } else if (n > (uint32_t)(mpEnd - mpBegin)) {
            const uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
            copy_ool(x.mpBegin, x.mpBegin + nSize, mpBegin);
            uninitialized_copy_ptr((const Rec18*)(x.mpBegin + (uint32_t)(mpEnd - mpBegin)), (const Rec18*)x.mpEnd, mpEnd);
            mpEnd = mpBegin + n;
        } else {
            copy_ool(x.mpBegin, x.mpEnd, mpBegin);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// @ 0x0057f0f0
template <> void vector<Rec30>::DoInsertValue(Rec30* position, const Rec30& value)
{
    if (mpEnd != mpCapacity) {
        const Rec30* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) Rec30(*(mpEnd - 1));
        copy_backward_impl(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = GetNewCapacity(nPrevSize);
        Rec30* const pNewData = DoAllocate(nNewSize);
        Rec30* pNewEnd = uninitialized_copy_ool(mpBegin, position, pNewData);
        ::new (pNewEnd) Rec30(value);
        pNewEnd = uninitialized_copy_ool(position, mpEnd, pNewEnd + 1);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

} // namespace eastl

// ---- refcounted-pointer element vector (insert n copies) ------------------------------------
struct RefElem {                                 // intrusive pointer, AddRef at vtbl+4, Release at vtbl+8
    RC1* p;
    RefElem(const RefElem& o) : p(o.p) { if (p) p->AddRef(); }
    ~RefElem() { if (p) p->Release(); }
};
void* __cdecl MoveMem(void* dst, const void* src, uint32_t n);                  // 0x011E0744

namespace eastl {
template <class T> void fill_ool(T* first, T* last, const T& v);               // 0x00657F20
template <class T> void copy_backward_ool(T* first, T* last, T* resultEnd);    // 0x005C1DC0

// @ 0x0057f220
template <> void vector<RefElem>::DoInsertValues(RefElem* position, uint32_t n, const RefElem& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const RefElem temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            RefElem* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_ool(position, pEnd - n, pEnd);
                fill_ool(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ptr(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill_ool(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        RefElem* const pNewData = DoAllocate(nNewSize);
        RefElem* pNewEnd = (RefElem*)MoveMem(pNewData, mpBegin, (uint32_t)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = (RefElem*)MoveMem(pNewEnd + n, position, (uint32_t)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
} // namespace eastl

// ---- editor mode --------------------------------------------------------------------------------
struct Block;
struct EditorUI {
    void UpdateUIBasedOnModelSaveability();                       // 0x005DD7A0
    char F5dc450();                                                // 0x005DC450
    void F5dd090(int);                                             // 0x005DD090
    void EnableBasicEditorButtons(int, int);                       // 0x005DE690
    void* F5dc2b0();                                               // 0x005DC2B0
    void* F5dc2c0();                                               // 0x005DC2C0
};
struct MsgServer { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
                   virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
                   virtual void PostMessage4(uint32_t id, int a, int b, int c); };  // +0x18
MsgServer* __cdecl GetMessageServer();                             // 0x0067DCC0

struct SetNameMsg { void* src; uint32_t pad4; const wchar_t* name; uint32_t pad2; uint32_t zero; uint32_t pad3;
                  SetNameMsg(void* s, const wchar_t* n) { zero = 0; src = s; name = n; } };

// ---------------------------------------------------------------------------------------------
struct Block : RC1 {                             // cSPEditorBlock
    uint32_t pad[0x371];
    uint32_t mFlags;                             // +0xDC8
    bool FlagBit(int n) const { return ((mFlags >> n) & 1) != 0; }
    void F43ce40();                              // 0x0043CE40
    void F43a9a0(int, uint32_t);                 // 0x0043A9A0
    char HasAnyBlockFlag();                      // 0x00435D40
    void F43c710();                              // 0x0043C710
    void F43cad0();                              // 0x0043CAD0
};
struct BlockRef {                                // AutoRefCount<Block>
    Block* p;
    void Set(Block* b);                          // 0x004B09B0
};
struct Handle { Block* GetRigblock(); };         // 0x0047E6C0
struct SkinMgr { void* GetSkin(int); };          // 0x004C49E0
struct PaletteUI { char IsPaintByNumber(); };    // 0x005CA920
struct AnimMgr { char IsPlayingAnimation(int); };   // 0x0059CD20
struct Flagged { uint32_t pad[7]; char mFlag; }; // byte at +0x1c
Flagged* __cdecl AssetBrowser();                 // 0x00401030
Flagged* __cdecl SporeGuide();                   // 0x00401040

struct EventInfo : RC1 {                         // cSPEditorAnimatedEventInfo, 0x30 bytes
    uint32_t pad[11];
    EventInfo();                                 // 0x0059D960
    void MessagePost(uint32_t id, int a, void* model, int b, int c, float f0, int d, int e, float f1);   // 0x0059D840
};
struct EventRef {                                // AutoRefCount<EventInfo> built from a raw pointer
    EventInfo* p;
    EventRef(EventInfo* e);                      // 0x0061DF40
};

struct Mask16 { uint32_t d[4]; Mask16() {} };
struct cEditorBase {
    char IsMousedOverModel(float x, float y);    // 0x00573A60
    char HasSkin();                              // 0x00577620
    void F57e340(int);                           // 0x0057E340
    void F573970();                              // 0x00573970
    void SomeLoader();                           // 0x00577DD0
    void F5724a0();                              // 0x005724A0
    void RemoveTorsoFromEffectsMask();           // 0x005772B0
    void SetRolloverHandle(int, int);            // 0x00573D70
    void UpdateBaker();                          // 0x0057E8A0
    void UpdateIdleAnimations(float x, float y, uint32_t dt);   // 0x0057E480
    void SetSelectedBlock(Block* b, uint32_t p);                // 0x0057E790
    void SaveMetadata();                         // 0x0057EA30
    void BakerInit();                            // 0x0057EBF0
    void SetModelName(const wchar_t* name);      // 0x0057ED00
    Mask16 BuildPartMask(int, int, int);         // 0x0057AC00
};

struct IModel { virtual void v0(); virtual uint32_t V1(); virtual void v2(); virtual uint32_t V3(); };
struct IMeta : RC0 { void Fill(uint32_t, uint32_t, const wchar_t*); };   // 0x005519D0
struct IRes : RC0 { virtual void v2(); virtual IMeta* QueryMeta(uint32_t type); };
inline IMeta* QueryAddRef(IRes* r)
{
    IMeta* m = r->QueryMeta(0x30bdee3);
    if (m)
        m->AddRef();
    return m;
}
struct IResMan { virtual void m0(); virtual void m1(); virtual void m2();
                 virtual bool GetResource(void* key, IRes** out, int, int, int, int);   // +0x0c
                 virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
                 virtual void SaveResource(IMeta*, int, int, int, int); };              // +0x20
IResMan* __cdecl GetManager();                                      // 0x0067DCD0
int __cdecl GetSaveArea(int);                                       // 0x006B1F90
struct Thumb { void UpdateExportThumb(void* key); };                // 0x005FB430
Thumb* __cdecl GetThumb();                                          // 0x005F7930
struct TokTrans { void SetOldModelName(const wchar_t*); };          // 0x005D6090
extern TokTrans* gTokTrans;                                         // 0x015EEBEC
struct Hints { void F67c420(); };                                   // 0x0067C420
Hints* __stdcall GetHints(int, int);                                // 0x0067CAC0
struct INameProv { virtual void v0(); virtual const wchar_t* GetName(); virtual void v2(); virtual void v3(); virtual void v4();
                   virtual const wchar_t* GetName5(); };
struct WStr16 { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t a;
                void Assign(const wchar_t* b, const wchar_t* e); };   // 0x00423650
struct IUnk { virtual void* v0(); virtual void* V1(int); };

struct ResKey { uint32_t instance, type, group;
                ResKey() {}
                ResKey(const ResKey& o) : instance(o.instance), type(o.type), group(o.group) {} };
struct ResHolder { IRes* p; ResHolder() : p(0) {} ~ResHolder() { if (p) p->Release(); } };
struct EditorModel {                             // cSPEditorModel
    virtual void v0(); virtual uint32_t V1(); virtual void v2(); virtual uint32_t V3();
    uint32_t pad[2];
    ResKey mKey;                                 // +0x0C
    uint32_t pad2[16];
    uint32_t m58;                                // +0x58
    char F4acfd0();                              // 0x004ACFD0
    void F4ad1a0();                              // 0x004AD1A0
};
struct LaunchData { uint32_t pad[0x19]; char pad1[1]; char m65; char pad2[2]; uint32_t pad3[0x24 - 0x1a]; uint32_t m90; RC0* m94; };
struct BakerData : RC1 {                         // 0x48 bytes
    uint32_t pad[2];
    uint32_t mField0c;                           // +0x0C
    RC0* mRef10;                                 // +0x10
    uint32_t mField14;
    ResKey mKey;                                 // +0x18
    WStr16 mName;                                // +0x24
    uint32_t mField34, mField38, mField3c, mField40;
    char mByte44, mByte45;
    BakerData();                                 // 0x00579C80
    void SetField34(uint32_t v) { mField34 = v; }
    void SetField3c(uint32_t v) { mField3c = v; }
    void SetField40(uint32_t v) { mField40 = v; }
};
struct BakerMsg { uint32_t id; short a; short b; BakerMsg() {} };
struct BakerSvc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void Post(void* key, void* msg); };   // +0x4c
BakerSvc* __cdecl GetBakerSvc();                                   // 0x00401010
struct cEditorBase;
void __cdecl InvalidEditorModelKey(ResKey* k, int);                 // 0x0068C700


struct GAppProps { uint32_t pad[15]; void* p3c; };
extern GAppProps* gAppProperties;                                   // 0x015FD918

// @ 0x0057ed00
void cEditorBase::SetModelName(const wchar_t* name)
{
    const wchar_t* e = name;
    while (*e) ++e;
    At<WStr16>(this, 0xa4).Assign(name, name + (e - name));
    At<char>(this, 0x4a8) = 1;
    At<EditorUI*>(this, 0x6c)->UpdateUIBasedOnModelSaveability();
    SetNameMsg m(((char*)this - 0xc) ? (void*)this : 0, At<WStr16>(this, 0xa4).mpBegin);
    GetMessageServer()->PostMessage(0x73127e6, &m, 0);
}

// @ 0x0057e790
void cEditorBase::SetSelectedBlock(Block* b, uint32_t p)
{
    if (b) {
        if (At<char>(this, 0xe8))
            At<char>(this, 0xe8) = 0;
        if (At<char>(this, 0xe9)) {
            RemoveTorsoFromEffectsMask();
            At<char>(this, 0xe9) = 0;
        }
        if (At<char>(this, 0x470) == 0)
            b->F43ce40();
    }
    BlockRef& ref = At<BlockRef>(this, 0xd4);
    Block* old = ref.p;
    if (b != old) {
        if (old && !old->FlagBit(1)) {
            if (At<Handle*>(this, 0xe4) && At<Handle*>(this, 0xe4)->GetRigblock() == old)
                SetRolloverHandle(0, 1);
            ref.p->F43a9a0(0, p);
        }
        if (b) {
            if (b->FlagBit(10) && b->HasAnyBlockFlag())
                return;
            ref.Set(b);
            if (!ref.p)
                return;
            ref.p->F43a9a0(1, 1);
            if (ref.p != At<Block*>(this, 0xd8)) {
                ref.p->F43c710();
                return;
            }
            ref.p->F43cad0();
            return;
        } else {
            Block* cur = ref.p;
            if (!cur)
                return;
            ref.p = 0;
            cur->Release();
            return;
        }
    }
    if (old)
        old->F43cad0();
}

// @ 0x0057e480
void cEditorBase::UpdateIdleAnimations(float x, float y, uint32_t dt)
{
    if (At<int>(At<void*>(gAppProperties, 0x3c), 0xdc) == 0)
        return;
    bool bHasSkin = false;
    if (At<int>(this, 0x360) && At<SkinMgr*>(this, 0x150) && At<SkinMgr*>(this, 0x150)->GetSkin(1))
        bHasSkin = true;
    if (AssetBrowser()->mFlag)
        return;
    if (SporeGuide()->mFlag)
        return;
    int queued = At<int>(this, 0x31c);
    if (queued != 0 && queued != 1)
        return;
    bool bAnyState = false;
    bool bIdle = false;
    if (bHasSkin) {
        if (At<char>(this, 0xe9) != 0 || At<char>(this, 0xe8) != 0)
            bAnyState = true;
    }
    if (At<int>(this, 0x148) == 0 && At<int>(this, 0xcc) == 0 && At<int>(this, 0xe4) == 0 &&
        At<int>(this, 0xd4) == 0 && !bAnyState && (queued != 0 || !IsMousedOverModel(x, y)))
        bIdle = true;
    if (At<int>(this, 0x31c) == 1 && At<PaletteUI*>(this, 0x3c4) && At<PaletteUI*>(this, 0x3c4)->IsPaintByNumber())
        bIdle = false;
    if (At<char>(this, 0x385) == 0) {
        if (!bIdle)
            return;
        float t = (float)dt + At<float>(this, 0x68);
        At<float>(this, 0x68) = t;
        if (!(At<float>(this, 0x6c) < t))
            return;
        EventInfo* raw = new ("Editor", 0, 0, 0, 0) EventInfo();
        EventRef info(raw);
        EventInfo* ev = info.p;
        ev->MessagePost(0x65d3b051, 0, At<void*>(this, 0x98), 0, 0, 0.0f, 1, -1, 1.0f);
        if (!HasSkin() && !At<EditorModel*>(this, 0x98)->F4acfd0() && At<EditorModel*>(this, 0x98)) {
            At<EditorModel*>(this, 0x98)->F4ad1a0();
            At<char>(this, 0x385) = 1;
        }
        if (ev)
            ev->Release();
        return;
    }
    if (HasSkin()) {
        if (At<AnimMgr*>(this, 0x360)->IsPlayingAnimation(At<int>(this, 0x364)))
            return;
        if (At<int>(this, 0x380) != 0)
            return;
        float cur = At<float>(this, 0x70);
        if (cur > 0.0f) {
            float t = cur - (float)dt;
            At<float>(this, 0x70) = t;
            if (t > 0.0f)
                return;
            At<float>(this, 0x70) = 0.0f;
            F57e340(0);
            return;
        }
        if (!bIdle) {
            F573970();
            return;
        }
        EventInfo* raw = new ("Editor", 0, 0, 0, 0) EventInfo();
        EventRef info(raw);
        EventInfo* ev = info.p;
        ev->MessagePost(0x65d3b051, 0, At<void*>(this, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
        if (ev)
            ev->Release();
        return;
    }
    if (bIdle)
        return;
    if (At<EditorModel*>(this, 0x98)->F4acfd0()) {
        SomeLoader();
        F5724a0();
    }
}

// @ 0x0057e8a0
void cEditorBase::UpdateBaker()
{
    if (!At<void*>(this, 0x1cc))
        return;
    BakerData* o = new ("Editor", 0, 0, 0, 0) BakerData();
    BakerData* old = At<BakerData*>(this, 0x4bc);
    if (o != old) {
        if (o) o->AddRef();
        At<BakerData*>(this, 0x4bc) = o;
        if (old) old->Release();
    }
    At<BakerData*>(this, 0x4bc)->mField0c = At<LaunchData*>(this, 0x1cc)->m90;
    BakerData* b = At<BakerData*>(this, 0x4bc);
    RC0* src = At<LaunchData*>(this, 0x1cc)->m94;
    RC0*& ref = b->mRef10;
    RC0* cur = ref;
    if (src != cur) {
        if (src) src->AddRef();
        ref = src;
        if (cur) cur->Release();
    }
    At<BakerData*>(this, 0x4bc)->mByte45 = At<LaunchData*>(this, 0x1cc)->m65;
    EditorModel* m = At<EditorModel*>(this, 0x98);
    BakerData* d = At<BakerData*>(this, 0x4bc);
    d->mKey = m->mKey;
    At<BakerData*>(this, 0x4bc)->mField14 = At<EditorModel*>(this, 0x98)->m58;
    At<BakerData*>(this, 0x4bc)->mByte44 = 0;
    BakerData* d1 = At<BakerData*>(this, 0x4bc);
    const wchar_t* n = At<INameProv>(this, 0xc).GetName();
    const wchar_t* e = n;
    while (*e) ++e;
    d1->mName.Assign(n, n + (e - n));
    BakerData* d2 = At<BakerData*>(this, 0x4bc);
    d2->mField34 = (uint32_t)At<IUnk*>(this, 0x434)->V1(0);
    At<BakerData*>(this, 0x4bc)->mField38 = At<uint32_t>(this, 0x34c);
    BakerData* d3 = At<BakerData*>(this, 0x4bc);
    d3->mField3c = (uint32_t)At<EditorUI*>(this, 0x78)->F5dc2b0();
    BakerData* d4 = At<BakerData*>(this, 0x4bc);
    d4->mField40 = (uint32_t)At<EditorUI*>(this, 0x78)->F5dc2c0();
}

// @ 0x0057ea30
void cEditorBase::SaveMetadata()
{
    IResMan* rm = GetManager();
    EditorModel* model = At<EditorModel*>(this, 0x98);
    ResKey key;
    key = model->mKey;
    key.type = 0x30bdee3;
    ResHolder out;
    if (rm->GetResource(&key, &out.p, 0, 0, 0, 0)) {
        IMeta* meta;
        if (out.p == 0)
            meta = 0;
        else
            meta = QueryAddRef(out.p);
        IModel* mdl = At<IModel*>(this, 0x98);
        const wchar_t* nm = At<INameProv>(this, 0xc).GetName5();
        meta->Fill(mdl->V1(), mdl->V3(), nm);
        int area = GetSaveArea(At<int>(this, 0x2ac));
        GetManager()->SaveResource(meta, 0, area, 0, 0);
        Thumb* t = GetThumb();
        if (t)
            t->UpdateExportThumb(&At<EditorModel*>(this, 0x98)->mKey);
        if (meta)
            meta->Release();
    }
    gTokTrans->SetOldModelName(At<INameProv>(this, 0xc).GetName());
    UpdateBaker();
    At<char>(this, 0x4b4) = 0;
    At<char>(this, 0x4b2) = 1;
    IModel* mdl2 = At<IModel*>(this, 0x98);
    int undoCount = At<int*>(this, 0x178)[-1];
    int modelType = (int)mdl2->V1();
    At<Mask16>(this, 0x48) = BuildPartMask(undoCount, modelType, 1);
    At<EditorUI*>(this, 0x78)->UpdateUIBasedOnModelSaveability();
    if (At<EditorUI*>(this, 0x78)->F5dc450() != 1) {
        At<EditorUI*>(this, 0x78)->F5dd090(1);
        At<EditorUI*>(this, 0x78)->EnableBasicEditorButtons(1, 1);
    }
    GetHints(1, 1)->F67c420();
}

// @ 0x0057ebf0
void cEditorBase::BakerInit()
{
    BakerMsg msg1;
    BakerMsg msg2;
    ResKey k;
    switch (At<int>(this, 0x388)) {
    case 3:
        At<int>(this, 0x1a8) = 2;
        GetMessageServer()->PostMessage4(0x153c326, 0, 0, 0);
        return;
    case 2:
        if (At<void*>(this, 0x1cc)) {
            UpdateBaker();
            EditorModel* m = At<EditorModel*>(this, 0x98);
            if (m->mKey.type == 0x3d97a8e4) {
                msg1.id = 0x2ea8fb98;
                msg1.a = 1;
                msg1.b = 4;
                GetBakerSvc()->Post(&At<EditorModel*>(this, 0x98)->mKey, &msg1);
                return;
            }
            if (m->mKey.type == 0x2b978c46) {
                k.instance = m->mKey.instance;
                k.type = m->mKey.type;
                k.group = m->mKey.group;
                InvalidEditorModelKey(&k, 0);
                msg2.id = 0x2ea8fb98;
                msg2.a = 1;
                msg2.b = 4;
                GetBakerSvc()->Post(&k, &msg2);
            }
        }
        break;
    }
}

// ---- 0x0057efa0 ------------------------------------------------------------------------------------
namespace EA { eastl::basic_string<wchar_t> ConvertToString16(const char* s, int len); }   // 0x0093C5A0
struct ListUI { virtual void BeginList(const wchar_t*); virtual void EndList(const wchar_t*); };
bool __cdecl UpdateEffectsAndObjectsStats(ListUI* ui, int, char* entry, const wchar_t* type);   // 0x0057C940
struct CharVec { char* mpBegin; char* mpEnd; };

// @ 0x0057efa0
bool __cdecl PopulateScriptList(ListUI* ui, const char* name, CharVec* v)
{
    bool ok = true;
    if (v->mpBegin == v->mpEnd)
        return ok;
    const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
    ui->BeginList(s.mpBegin == s.mpEnd ? L"list" : s.mpBegin);
    char* const end = v->mpEnd;
    for (char* it = v->mpBegin; it != end; ++it)
        ok = ok && UpdateEffectsAndObjectsStats(ui, 0, it, L"bool");
    ui->EndList(s.mpBegin == s.mpEnd ? L"list" : s.mpBegin);
    return ok;
}
