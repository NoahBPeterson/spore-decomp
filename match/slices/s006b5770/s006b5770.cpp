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

struct cStringTableResourceFactory : Factory {
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

// @ 0x006b5770
namespace SP {
struct cString {
    cString();
};
}
SP::cString::cString() {}

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

// @ 0x006b5f80
void TranslatorVector_pushback_stub() {}

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

// @ 0x006b6490
void App::cStringDetokenizer_ctor(App::cStringDetokenizer* self) { (void)self; }

// @ 0x006b65d0
void FUN_006b65d0() {}

// @ 0x006b6620
void FUN_006b6620() {}

// @ 0x006b6740
void FUN_006b6740() {}

// @ 0x006b67b0
void FUN_006b67b0() {}

// @ 0x006b68a0
void FUN_006b68a0() {}
