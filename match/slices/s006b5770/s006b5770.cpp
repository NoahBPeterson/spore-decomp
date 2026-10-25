// slice s006b5770: App::cStringDetokenizer / ITokenTranslator and
// SP::cStringTableResourceFactory.
// Flags: /O2 /MD /Gy /TP
#include "types.h"

typedef unsigned short wchar16;

__declspec(dllimport) wchar16* __cdecl wcschr(const wchar16* s, wchar16 c);
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
extern "C" unsigned __cdecl wcslen(const wchar_t* s);
#pragma intrinsic(wcscmp, wcslen)

inline void* __cdecl operator new(unsigned int, void* p) throw() { return p; }
inline void  __cdecl operator delete(void*, void*) throw() {}

// ---------------------------------------------------------------------------
// Value types.
// ---------------------------------------------------------------------------
extern wchar16 gEmptyStringRep[2];   // 0x01667bac: eastl empty-string rep

namespace eastl {
struct string16 {
    wchar16* mpBegin;      // +0
    wchar16* mpEnd;        // +4
    wchar16* mpCapacity;   // +8
    int      mAllocator;   // +0xc

    void assign(const wchar16* first, const wchar16* last);     // 0x00423650
    void append(const wchar16* first, const wchar16* last);     // 0x00429580
    void append(const wchar16* s);                              // 0x005c3d90
    void push_back(wchar16 c);                                  // 0x004f6510
    void set_capacity(unsigned n);                              // 0x0042f360
    void reserve(unsigned n);                                   // 0x0042e610
    string16& operator=(const string16& o);                     // 0x0057cb60
    string16& operator+=(const wchar16* s);                     // 0x00599bb0
    wchar16* FillInsert(unsigned n, unsigned ch);               // 0x00674230

    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};

// A default-constructed string16 on the stack (empty rep, heap if grown).
struct LocalString16 : string16 {
    LocalString16() {
        mpBegin = gEmptyStringRep;
        mpEnd = gEmptyStringRep;
        mpCapacity = gEmptyStringRep + 1;
    }
    ~LocalString16();
};

// A string16 created with the engine allocator (new (name,0,0,0,0)).
struct HeapString16 : string16 {
    HeapString16() {
        mpBegin = gEmptyStringRep;
        mpEnd = gEmptyStringRep;
        mpCapacity = gEmptyStringRep + 1;
    }
    static void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
};

void __cdecl operator_delete_array(void* p) throw();   // 0x00f47380

inline LocalString16::~LocalString16()
{
    if ((int)(((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
        operator_delete_array(mpBegin);
}

// string with a 32-character fixed buffer (fixed_vector_allocator<2,32,2,0,1>).
struct FixedString16_32 {
    wchar16* mpBegin;      // +0
    wchar16* mpEnd;        // +4
    wchar16* mpCapacity;   // +8
    int      mAllocator;   // +0xc
    wchar16* mpPool;       // +0x10
    wchar16  mBuf[32];     // +0x14

    FixedString16_32() {
        mpEnd = mBuf;
        mpPool = mBuf;
        mpBegin = mBuf;
        mpCapacity = mBuf + 32;
        mBuf[0] = 0;
    }
    ~FixedString16_32() {
        if ((int)(((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin && mpBegin != mpPool)
            operator_delete_array(mpBegin);
    }
    void assign(const wchar16* first, const wchar16* last);     // 0x00678ee0
};
}

namespace App {

struct ITokenTranslator;

// The detokenizer vtable (retail 0x01400f40).
extern void* vtbl_App_cStringDetokenizer[];

struct intrusive_ptr {
    ITokenTranslator* ptr;   // +0

    intrusive_ptr(ITokenTranslator* p);
    intrusive_ptr(ITokenTranslator* p, int) : ptr(p) {}   // adopts an existing reference
    intrusive_ptr(const intrusive_ptr& o);
    ~intrusive_ptr();
    intrusive_ptr& operator=(const intrusive_ptr& o);
};

// eastl::vector<intrusive_ptr>.
struct TranslatorVector {
    intrusive_ptr* mpBegin;      // +0
    intrusive_ptr* mpEnd;        // +4
    intrusive_ptr* mpCapacity;   // +8

    __declspec(noinline) intrusive_ptr* erase(intrusive_ptr* pos);   // 0x006b5990
    intrusive_ptr* erase(intrusive_ptr* first, intrusive_ptr* last);   // 0x005c2170
    void push_back(const intrusive_ptr& v);                            // 0x006b5f80
    void DoInsertValue(intrusive_ptr* pos, const intrusive_ptr* pValue);
};

// SEH guard for push_back: releases the slot that was appended when the AddRef
// call unwinds out of the function.
struct SlotGuard {
    intrusive_ptr* mpSlot;
    ~SlotGuard();
};

struct ITokenTranslator {
    virtual void Slot00();                                                     // +0x00
    virtual int  AddRef();                                                     // +0x04
    virtual int  Release();                                                    // +0x08
    virtual void* Cast(uint32_t typeID);                                       // +0x0c
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16& dst);  // +0x10
    virtual void func14h(int);                                                 // +0x14

    int mnRefCount;   // +0x04
};

inline intrusive_ptr::intrusive_ptr(ITokenTranslator* p) : ptr(p)
{
    if (ptr) ptr->AddRef();
}
inline intrusive_ptr::intrusive_ptr(const intrusive_ptr& o) : ptr(o.ptr)
{
    if (ptr) ptr->AddRef();
}
inline intrusive_ptr::~intrusive_ptr()
{
    if (ptr) ptr->Release();
}
inline intrusive_ptr& intrusive_ptr::operator=(const intrusive_ptr& o)
{
    ITokenTranslator* n = o.ptr;
    ITokenTranslator* old = ptr;
    if (n != old) {
        if (n) n->AddRef();
        ptr = n;
        if (old) old->Release();
    }
    return *this;
}

// Entry of a caller-supplied token table: FNV1 hash of the token -> replacement.
struct TokenEntry {
    uint32_t hash;          // +0
    eastl::string16 str;    // +4
};

// SP::cString: a source string plus a lazily created detokenized copy.
struct SPCString {
    void* vtbl;                  // +0x00
    eastl::string16* mpOut;      // +0x04
    const wchar16* mpSrc;        // +0x08
    int pad0c;                   // +0x0c
    bool mbEnabled;              // +0x10
    bool mbDirty;                // +0x11
};

struct cStringDetokenizer : ITokenTranslator {
    virtual void func18h();                                                    // +0x18
    virtual void AddTranslator(ITokenTranslator*);                             // +0x1c
    virtual void RemoveTranslator(ITokenTranslator*);                          // +0x20
    virtual bool HasTokens(const wchar16* pStr);                               // +0x24
    virtual bool func28h(void* a, eastl::string16& dst);                       // +0x28
    virtual bool ProcessString(const wchar16* pStr, eastl::string16& dst);     // +0x2c
    virtual bool func30h(SPCString* s, TokenEntry* table, uint32_t count);      // +0x30
    virtual void func34h(const wchar16* pStr, uint32_t index);                 // +0x34
    virtual bool ProcessStringEx(const wchar16* pStr, eastl::string16& dst, TokenEntry* table, uint32_t count); // +0x38
    virtual bool FindTokenTranslation(const wchar16* pToken, eastl::string16& dst); // +0x3c
    // Override of ITokenTranslator::TranslateToken (slot +0x10).
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16& dst);

    void ctor();                         // 0x006b6490 (thiscall constructor)

    TranslatorVector mTranslators;       // +0x08 (begin/end/cap)
    uint32_t mPad14;                     // +0x14
    uint32_t mPad18;                     // +0x18
    eastl::string16 mGenericTokens[4];   // +0x1c
};

} // namespace App

// @ 0x006b5810
bool App::cStringDetokenizer::HasTokens(const wchar16* pStr)
{
    if (pStr != 0) {
        return wcschr(pStr, L'~') != 0;
    }
    return false;
}

// @ 0x006b57f0
bool App::cStringDetokenizer::func28h(void* a, eastl::string16& dst)
{
    return ProcessString(*(const wchar16**)((char*)a + 8), dst);
}

// @ 0x006b5840
void App::ITokenTranslator::func14h(int arg)
{
    // The detokenizer overrides this; mTranslators lives at +0x08 of the
    // derived object, so this base view is shared with cStringDetokenizer.
    App::cStringDetokenizer* self = (App::cStringDetokenizer*)this;
    App::intrusive_ptr* it = self->mTranslators.mpBegin + 1;
    App::intrusive_ptr* end = self->mTranslators.mpEnd;
    while (it < end) {
        it->ptr->func14h(arg);
        ++it;
    }
}

// @ 0x006b5880
bool App::cStringDetokenizer::FindTokenTranslation(const wchar16* pToken, eastl::string16& dst)
{
    intrusive_ptr* it = mTranslators.mpEnd;
    intrusive_ptr* begin = mTranslators.mpBegin;
    while (it != begin) {
        if (it[-1].ptr->TranslateToken(pToken, dst))
            return true;
        --it;
    }
    return false;
}

// @ 0x006b5950
void App::cStringDetokenizer::func34h(const wchar16* pStr, uint32_t index)
{
    if (index < 4) {
        const wchar16* p = pStr;
        while (*p != 0)
            ++p;
        mGenericTokens[index].assign(pStr, pStr + (p - pStr));
    }
}

// @ 0x006b5990
App::intrusive_ptr* App::TranslatorVector::erase(App::intrusive_ptr* pos)
{
    if (pos + 1 < mpEnd) {
        void __cdecl eastl_copy(intrusive_ptr*, intrusive_ptr*, intrusive_ptr*);
        eastl_copy(pos + 1, mpEnd, pos);
    }
    mpEnd = mpEnd - 1;
    ITokenTranslator* p = mpEnd->ptr;
    if (p != 0)
        p->Release();
    return pos;
}

// @ 0x006b5b80
void App::cStringDetokenizer::RemoveTranslator(ITokenTranslator* p)
{
    intrusive_ptr* end = mTranslators.mpEnd;
    intrusive_ptr* it = mTranslators.mpBegin;
    if (it != end) {
        while (it->ptr != p) {
            ++it;
            if (it == end)
                break;
        }
        if (it != end) {
            mTranslators.erase(it);
        }
    }
}

// ---------------------------------------------------------------------------
// SP::cStringTableResourceFactory
// ---------------------------------------------------------------------------
namespace SP {

struct Factory {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
};

class cStringTableResourceFactory : public Factory { public:
    virtual int GetSupportedTypes(uint32_t* pTypes, int count);
};

} // namespace SP

// @ 0x006b6540
int SP::cStringTableResourceFactory::GetSupportedTypes(uint32_t* pTypes, int count)
{
    if (pTypes == 0)
        return 1;
    if (count != 0) {
        *pTypes = 0x2fac0b6;
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Remaining functions (see partial.txt for the ones still stubbed).
// ---------------------------------------------------------------------------
namespace App {

// TokenCursor: the caller owns the 9-byte state blob
// (valid flag + record pointer) while the array bounds come from the owner.
struct TokenCursor {
    bool Next(char* mState, int* pOut1, int* pOut2);
    // +0x18 begin / +0x1c end of the token-name buffer, +0x2c/+0x30 record array
    char pad00[0x18];
    int  mBegin;      // +0x18
    int  mEnd;        // +0x1c
    char pad20[0xc];  // +0x20..+0x2b
    int* mRecBegin;   // +0x2c
    int* mRecEnd;     // +0x30
};

// ByteStream: a reader over a pooled source buffer.
struct ByteStream {
    unsigned char ReadByte();
    char pad00[0x08]; // +0x00..+0x07
    unsigned mPool;   // +0x08 remaining pool bytes
    int  mCursor;     // +0x0c
    int  mLimit;      // +0x10
    int  mBase;       // +0x14 current read base
    void* mSource;    // +0x18 vtable-bearing source object
};

void ITokenTranslator::Slot00() {}
int  ITokenTranslator::AddRef() { return 1; }
int  ITokenTranslator::Release() { return 0; }
void* ITokenTranslator::Cast(uint32_t) { return 0; }
bool ITokenTranslator::TranslateToken(const wchar16*, eastl::string16&) { return false; }

void cStringDetokenizer_ctor(cStringDetokenizer* self);

} // namespace App

void* __cdecl SporeAlloc(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned n);                          // 0x011e0744
void __cdecl copy_backward_ool(App::intrusive_ptr* first, App::intrusive_ptr* last, App::intrusive_ptr* destEnd); // 0x005c1dc0
uint32_t __cdecl FNV1_String16(const wchar16* s, uint32_t basis, int a);                              // 0x00932f30

static inline unsigned CharStrlen16(const wchar16* p)
{
    return wcslen((const wchar_t*)p);
}

// @ 0x006b59d0
void App::TranslatorVector::DoInsertValue(App::intrusive_ptr* pos, const App::intrusive_ptr* pValue)
{
    if (mpEnd != mpCapacity) {
        const intrusive_ptr* v = pValue;
        if (pValue >= pos && pValue < mpEnd)
            ++v;
        ::new (mpEnd) intrusive_ptr(mpEnd[-1]);
        copy_backward_ool(pos, mpEnd - 1, mpEnd);
        *pos = *v;
        ++mpEnd;
    } else {
        unsigned prev = (unsigned)(mpEnd - mpBegin);
        unsigned len = prev > 0 ? prev * 2 : 1;
        intrusive_ptr* newData;
        if (len)
            newData = (intrusive_ptr*)SporeAlloc((len + len) * 2, "App", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        else
            newData = 0;
        int nbytes = (int)((char*)pos - (char*)mpBegin);
        intrusive_ptr* newPos = (intrusive_ptr*)memmove(newData, mpBegin, nbytes) + (nbytes >> 2);
        ::new (newPos) intrusive_ptr(*pValue);
        int tail = (int)((char*)mpEnd - (char*)pos);
        ++newPos;
        intrusive_ptr* newEnd = (intrusive_ptr*)memmove(newPos, pos, tail) + (tail >> 2);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            eastl::operator_delete_array(mpBegin);
        mpEnd = newEnd;
        mpBegin = newData;
        mpCapacity = newData + len;
    }
}

// @ 0x006b5770 SP::cString::ctor
// SP::cString::cString: initialise the resource slot, the lazily created
// detokenized copy (null), the "***" source literal and the token flags, then
// register with the manager's string detokenizer (vtable +4) and load the
// caller's text. Wrapped in an SEH frame because the detokenizer registration
// and Load can throw.
void* __stdcall cStringManager_StringDetokenizer();       // 0x0067de50
void  cString_Load(void* self, unsigned id, unsigned a, const wchar_t* s);  // 0x006b54b0
extern "C" const wchar_t gSourcePlaceholder[] = L"***";    // 0x01409b1c: the "***" source literal

namespace SP {
struct cString {
    void* mpTableResource;        // +0x00
    eastl::string16* mpLocalString;   // +0x04
    const wchar_t* mpSourceCStr;  // +0x08
    unsigned mPlaceholderId;      // +0x0c
    bool mbHasTokens;             // +0x10
    bool mField11;                // +0x11
    void ctor(unsigned id, unsigned arg, const wchar_t* src);
    void Load(unsigned id, unsigned arg, const wchar_t* src);
};

// SEH guard for the constructor: destroys the partially built cString when a
// throwing call (the detokenizer registration or Load) unwinds out of it.
struct CStringCtorGuard {
    cString* mpSelf;
    ~CStringCtorGuard();
};
} // namespace SP

__declspec(noinline) SP::CStringCtorGuard::~CStringCtorGuard()
{
    // EH state 0 unwinds a partially assigned table resource.
    if (mpSelf->mpTableResource) {
        (*(void(__thiscall**)(void*))((char*)*(void**)mpSelf->mpTableResource + 8))(
            mpSelf->mpTableResource);
        mpSelf->mpTableResource = 0;
    }
}

void SP::cString::ctor(unsigned id, unsigned arg, const wchar_t* src)
{
    CStringCtorGuard guard;
    guard.mpSelf = this;
    mpTableResource = 0;
    mpLocalString = 0;
    mpSourceCStr = gSourcePlaceholder;
    mPlaceholderId = 0;
    mbHasTokens = false;
    mField11 = false;
    void* detok = cStringManager_StringDetokenizer();
    if (detok != 0) {
        void* d = cStringManager_StringDetokenizer();
        (*(void(__thiscall**)(void*, void*))((char*)*(void**)d + 4))(d, this);
    }
    Load(id, arg, src);
}

void SP::cString::Load(unsigned id, unsigned arg, const wchar_t* src)
{
    cString_Load(this, id, arg, src);
}

// @ 0x006b5bd0
bool App::cStringDetokenizer::ProcessString(const wchar16* pStr, eastl::string16& dst)
{
    dst.clear();
    unsigned len = CharStrlen16(pStr);
    unsigned size = (unsigned)(dst.mpEnd - dst.mpBegin);
    const unsigned* m = len < size ? &size : &len;
    unsigned n = *m + 1;
    if (n > (unsigned)(dst.mpCapacity - dst.mpBegin))
        dst.set_capacity(n);
    return ProcessStringEx(pStr, dst, 0, 0);
}

// @ 0x006b5c50
bool App::cStringDetokenizer::func30h(App::SPCString* s, App::TokenEntry* table, uint32_t count)
{
    if (s && s->mbEnabled && table && count > 0) {
        if (!s->mpOut)
            s->mpOut = new ("UI/SP::cString", 0, 0, 0, 0) eastl::HeapString16;
        s->mbDirty = true;
        s->mpOut->clear();
        s->mpOut->reserve(CharStrlen16(s->mpSrc));
        return ProcessStringEx(s->mpSrc, *s->mpOut, table, count);
    }
    return false;
}

// @ 0x006b5d20
bool App::cStringDetokenizer::ProcessStringEx(const wchar16* pStr, eastl::string16& dst, App::TokenEntry* table, uint32_t count)
{
    bool ok = true;
    bool inToken = false;
    eastl::FixedString16_32 name;
    eastl::LocalString16 result;
    if (*pStr != 0) {
        do {
            const wchar16* tilde = wcschr(pStr, L'~');
            if (inToken) {
                if (!tilde)
                    break;
                if (tilde == pStr) {
                    dst.push_back(L'~');
                    pStr = tilde + 1;
                    inToken = false;
                } else {
                    name.assign(pStr, pStr + (tilde - pStr));
                    result.clear();
                    bool found;
                    if (table) {
                        uint32_t h = FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
                        App::TokenEntry* e = table;
                        for (uint32_t i = 0; i < count; ++i, ++e) {
                            if (h == e->hash) {
                                if (&e->str != &result)
                                    result.assign(e->str.mpBegin, e->str.mpEnd);
                                found = true;
                                goto appended;
                            }
                        }
                    }
                    found = FindTokenTranslation(name.mpBegin, result);
                appended:
                    dst.append(result.mpBegin, result.mpEnd);
                    if (!found)
                        break;
                    inToken = false;
                    pStr = tilde + 1;
                }
            } else if (tilde) {
                dst.append(pStr, pStr + (tilde - pStr));
                pStr = tilde + 1;
                inToken = true;
            } else {
                const wchar16* e = pStr;
                while (*e)
                    ++e;
                dst.append(pStr, pStr + (unsigned)(e - pStr));
                pStr += CharStrlen16(pStr);
            }
        } while (*pStr != 0);
        if (inToken)
            ok = false;
    }
    return ok;
}

// @ 0x006b5f80 App::TranslatorVector::push_back
// eastl::vector<intrusive_ptr>::push_back: when there is in-place room the value
// is copied into the next slot and AddRef'd on the freshly constructed pointer;
// otherwise DoInsertValue performs the growth. Wrapped in an SEH frame so the
// partially constructed slot is destroyed if the AddRef call throws.
__declspec(noinline) App::SlotGuard::~SlotGuard()
{
    if (mpSlot && mpSlot->ptr)
        mpSlot->ptr->Release();
}

void App::TranslatorVector::push_back(const intrusive_ptr& v)
{
    SlotGuard guard;                 // SEH: destroy the new slot if AddRef throws
    guard.mpSlot = 0;
    if (mpEnd < mpCapacity) {
        intrusive_ptr* slot = mpEnd;
        mpEnd = slot + 1;
        guard.mpSlot = slot;
        if (slot) {
            ITokenTranslator* p = v.ptr;
            slot->ptr = p;
            if (p)
                p->AddRef();
        }
    } else {
        DoInsertValue(mpEnd, &v);
    }
}

// @ 0x006b6000
void App::cStringDetokenizer::func18h()
{
    mTranslators.erase(mTranslators.mpBegin, mTranslators.mpEnd);
    if (this)
        this->AddRef();
    intrusive_ptr self(this, 0);
    mTranslators.push_back(self);
}

// @ 0x006b6080
void App::cStringDetokenizer::AddTranslator(App::ITokenTranslator* t)
{
    if (!t)
        return;
    intrusive_ptr* end = mTranslators.mpEnd;
    intrusive_ptr* it = mTranslators.mpBegin;
    for (; it != end; ++it) {
        if (it->ptr == t)
            break;
    }
    if (it == end) {
        intrusive_ptr tmp(t);
        mTranslators.push_back(tmp);
    } else {
        if (it->ptr == this)
            return;
        t->AddRef();
        mTranslators.erase(it);
        {
            intrusive_ptr tmp(t);
            mTranslators.push_back(tmp);
        }
        t->Release();
    }
}

static unsigned HandStrlen16(const wchar16* p)
{
    const wchar16* e = p;
    while (*e)
        ++e;
    return (unsigned)(e - p);
}

// @ 0x006b6160
bool App::cStringDetokenizer::TranslateToken(const wchar16* tok, eastl::string16& dst)
{
    wchar16 br[] = { 'b', 'r', 0 };
    wchar16 nl[] = { 0xa, 0 };
    if (wcscmp((const wchar_t*)tok, (const wchar_t*)br) == 0) {
        dst.assign(nl, nl + HandStrlen16(nl));
        return true;
    }
    wchar16 p[] = { 'p', 0 };
    wchar16 nlbs[] = { 0xa, 8, 0xa, 0 };
    if (wcscmp((const wchar_t*)tok, (const wchar_t*)p) == 0) {
        dst.assign(nlbs, nlbs + HandStrlen16(nlbs));
        return true;
    }
    wchar16 hs[] = { 'h', 's', 0 };
    if (wcscmp((const wchar_t*)tok, (const wchar_t*)hs) == 0) {
        dst.FillInsert(1, 0xa0);
        return true;
    }
    if (wcscmp((const wchar_t*)tok, L"blank text") == 0) {
        dst.clear();
        return true;
    }
    switch (FNV1_String16(tok, 0x811c9dc5, 1)) {
    case 0x52194810:
        dst = mGenericTokens[0];
        return true;
    case 0x52194811:
        dst = mGenericTokens[1];
        return true;
    case 0x52194812:
        dst = mGenericTokens[2];
        return true;
    case 0x52194813:
        dst = mGenericTokens[3];
        return true;
    default: {
        wchar16 unk[] = { '>', '*', 0, '*', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '<', 0 };
        dst.append(unk + 3);
        dst += tok;
        dst += unk;
        return false;
    }
    }
}

// 0x006b6490: App::cStringDetokenizer::cStringDetokenizer (see definition below).
void __cdecl WString_DeallocateSelf(void* p);       // 0x00933960
void __cdecl WString_AllocateSelf(void* p);         // 0x005e93a0
// 0x006b58c0: __thiscall member taking the table size on the stack (ecx = table).
struct InitTableFn {
    void InitTable(int n);   // 0x006b58c0
};
void __stdcall __ehvec_ctor(void* ptr, unsigned size, int count,
                             void (__thiscall* ctor)(void*), void (__thiscall* dtor)(void*));  // 0x011e0b85

// SEH guard for the constructor: unwinds the four generic tokens when the table
// init or func18h throws.
struct DetokenizerCtorGuard {
    eastl::string16* mpTokens;
    ~DetokenizerCtorGuard();
};
__declspec(noinline) DetokenizerCtorGuard::~DetokenizerCtorGuard()
{
    for (int i = 0; i < 4; ++i) {
        if (mpTokens[i].mpBegin && mpTokens[i].mpBegin != gEmptyStringRep)
            eastl::operator_delete_array(mpTokens[i].mpBegin);
    }
}

// App::cStringDetokenizer::cStringDetokenizer: set the refcount to 0 and the
// vtable, empty the translator vector at +8, run the eastl vector-constructor
// iterator over the four string16 generic tokens at +0x1c, then add the default
// translation table (10 entries) and finish with func18h.
// @ 0x006b6490 App::cStringDetokenizer::ctor
void App::cStringDetokenizer::ctor()
{
    DetokenizerCtorGuard guard;
    guard.mpTokens = mGenericTokens;
    mnRefCount = 0;
    *(void**)this = (void*)0x1400f40;      // vtbl_App::cStringDetokenizer
    mTranslators.mpBegin = 0;
    mTranslators.mpEnd = 0;
    mTranslators.mpCapacity = 0;
    __ehvec_ctor((char*)this + 0x1c, 0x10, 4,
                 (void(__thiscall*)(void*))WString_AllocateSelf,
                 (void(__thiscall*)(void*))WString_DeallocateSelf);
    ((InitTableFn*)&mTranslators)->InitTable(10);
    func18h();
}

// ---------------------------------------------------------------------------
// Token-table cursor (0x006b65d0 / 0x006b6620) and the token hashtable
// (0x006b6740 / 0x006b67b0 / 0x006b68a0).
// ---------------------------------------------------------------------------

// hashtable layout: +0 unused, +4 mpBucketArray, +8 mnBucketCount,
// +0xc mnElementCount, +0x10 rehash policy, +0x18 pooled node block, +0x2c
// hash-key bucket array (the derived temp-map field).
struct HashInsertResult {
    void* node;       // +0
    void* bucket;     // +4
    bool  inserted;   // +8
};

struct Hashtable {
    int EraseKey(unsigned* pKey);                    // 0x006b6740 (thiscall)
    void* Insert(HashInsertResult* out, unsigned* pKey, unsigned unused);  // 0x006b67b0 (thiscall)
    void* ScalarDeletingDtor(unsigned deleteFlag);   // 0x006b68a0 (thiscall)
    void Rebucket(int newBucketCount);               // 0x006b6690 (thiscall)
};

// @ 0x006b65d0 App::TokenCursor::Next
// App::TokenCursor::Next: lazily seeds the cursor (+1 = record array begin at
// this+0x2c) on first use, then advances by one 8-byte record {hash, offset} and
// hands back the hash and the decoded source pointer (this+0x18 + offset*2).
// Returns whether the read offset is still inside the token-name buffer.
bool App::TokenCursor::Next(char* mState, int* pOut1, int* pOut2)
{
    if (*mState == 0) {
        *mState = 1;
        *(int*)(mState + 1) = *(int*)((char*)this + 0x2c);
    }
    int* rec = *(int**)(mState + 1);
    if (rec != *(int**)((char*)this + 0x30)) {
        *(int**)(mState + 1) = rec + 2;
        *pOut2 = rec[0];
        *pOut1 = *(int*)((char*)this + 0x18) + rec[1] * 2;
        int len = (*(int*)((char*)this + 0x1c) - *(int*)((char*)this + 0x18)) >> 1;
        return (unsigned)rec[1] < (unsigned)len;
    }
    return 0;
}

// @ 0x006b6620 App::ByteStream::ReadByte
// App::ByteStream::ReadByte: return the byte at the read cursor (+0xc/+0x14),
// advancing it; when exhausted refill through vtable +0x30 (with the pool size
// at +8, clamped to the 0x200 fallback descriptor at 0x1400f2c) and retry once.
unsigned char App::ByteStream::ReadByte()
{
    unsigned char result = 0;
    int cur = mCursor;
    if (cur == mLimit) {
        if (mPool != 0) {
            const unsigned* desc = (mPool < 0x200) ? &mPool : (const unsigned*)0x1400f2c;
            int got = (*(int(__thiscall**)(int, unsigned))((char*)*(int**)mSource + 0x30))(
                mBase, *desc);
            mPool -= got;
            mLimit = got;
            mCursor = 0;
            if (got >= 1) {
                result = *(unsigned char*)mBase;
                mCursor = 1;
            } else {
                mLimit = 0;
                mPool = 0;
            }
        }
    } else {
        result = *(unsigned char*)(cur + mBase);
        mCursor = cur + 1;
    }
    return result;
}

// @ 0x006b6740 Hashtable::EraseKey
// eastl::hashtable<...>::erase(key): unlink and free every node in the bucket
// whose key matches, decrementing the element count, and return the number of
// nodes removed.
int Hashtable::EraseKey(unsigned* pKey)
{
    int* self = (int*)this;
    int before = self[3];           // +0xc element count
    unsigned idx = *pKey % (unsigned)self[2];   // +0x8 bucket count
    int** slot = (int**)(self[1] + idx * 4);    // +0x4 bucket array
    if (*slot != 0) {
        int* node = *slot;
        while (*pKey != (unsigned)node[0]) {
            slot = (int**)(node + 1);
            node = (int*)node[1];
            if (node == 0)
                goto done;
        }
        while (*slot != 0) {
            int* cur = *slot;
            if (*pKey != (unsigned)cur[0])
                break;
            *slot = (int*)cur[1];
            eastl::operator_delete_array(cur);
            --self[3];
        }
    }
done:
    return before - self[3];
}

// @ 0x006b67b0 Hashtable::Insert
// eastl::hashtable<...>::insert / operator[]: find the node for the key; when
// absent, grow the bucket array through the rehash policy (0x00921440), allocate
// a fresh 8-byte node, rebucket if the policy asked for it, then link the node
// and report {node, bucket, inserted}.
struct RehashResult {
    bool rebucketed;       // +0 (local_8[0])
    int  newBucketCount;   // +4 (local_4)
};
// 0x00921440: __thiscall member of the rehash policy living at hashtable +0x10.
struct RehashPolicy { void Grow(void* out, unsigned bucketCount, unsigned size, int grow);  // 0x00921440
};
void* Hashtable::Insert(HashInsertResult* out, unsigned* pKey, unsigned unused)
{
    (void)unused;
    int* self = (int*)this;
    unsigned key = *pKey;
    unsigned idx = key % (unsigned)self[2];
    int** bucket = (int**)(self[1] + idx * 4);
    int* node = *bucket;
    while (node != 0) {
        if (key == (unsigned)node[0]) {
            out->node = node;
            out->bucket = bucket;
            out->inserted = false;
            return out;
        }
        node = (int*)node[1];
    }
    RehashResult rh;
    ((RehashPolicy*)((char*)this + 0x10))->Grow(&rh, self[2], self[3], 1);
    int* fresh = (int*)SporeAlloc(8, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (fresh != 0)
        fresh[0] = (int)*pKey;
    fresh[1] = 0;
    if (rh.rebucketed) {
        idx = key % (unsigned)rh.newBucketCount;
        ((Hashtable*)this)->Rebucket(rh.newBucketCount);
    }
    int off = (int)idx * 4;
    fresh[1] = *(int*)(off + self[1]);
    *(int**)(off + self[1]) = fresh;
    ++self[3];
    out->node = fresh;
    out->bucket = (void*)(off + self[1]);
    out->inserted = true;
    return out;
}
// @ 0x006b68a0 Hashtable::ScalarDeletingDtor
// eastl::hashtable<SP::cString*>::~hashtable (scalar deleting): free the bucket
// array (+0x2c) and the pooled node block (+0x18 when it owns one), reset the
// vtable, and free `this` when the low bit of the delete flag is set.
void* Hashtable::ScalarDeletingDtor(unsigned deleteFlag)
{
    int* self = (int*)this;
    if (self[0xb] != 0)
        eastl::operator_delete_array((void*)self[0xb]);
    int pool = self[6];
    if (pool != 0 && *(int*)(pool - 4) != 0)
        eastl::operator_delete_array((void*)pool);
    *(void**)self = (void*)0x13eb938;   // ??_7ITracerBase@Trace@EA@@6B@
    if (deleteFlag & 1)
        eastl::operator_delete_array(self);
    return self;
}
