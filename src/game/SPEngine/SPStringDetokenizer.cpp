// src/game/SPEngine/SPStringDetokenizer.cpp -- migrated from slice(s) s006b5770 by tools/migrate/rewrite.py
// Object file: SPEngine/SPStringDetokenizer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEditorsTokenTranslator.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
extern "C" unsigned __cdecl wcslen(const wchar_t* s);
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned n);                          // 0x011e0744
#pragma intrinsic(wcscmp, wcslen)

// ---- items of slice s006b5770 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short wchar16;
__declspec(dllimport) wchar16* __cdecl wcschr(const wchar16* s, wchar16 c);
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
extern "C" unsigned __cdecl wcslen(const wchar_t* s);
inline void* __cdecl operator new(unsigned int, void* p) throw() { return p; }
extern wchar16 gEmptyStringRep[2];   // 0x01667bac: eastl empty-string rep
namespace eastl {
struct string16_s006b_5770 {
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
    string16_s006b_5770& operator=(const string16_s006b_5770& o);                     // 0x0057cb60
    string16_s006b_5770& operator+=(const wchar16* s);                     // 0x00599bb0
    wchar16* FillInsert(unsigned n, unsigned ch);               // 0x00674230

    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
}
namespace eastl {
struct LocalString16 : string16_s006b_5770 {
    LocalString16() {
        mpBegin = gEmptyStringRep;
        mpEnd = gEmptyStringRep;
        mpCapacity = gEmptyStringRep + 1;
    }
    ~LocalString16();
};
}
namespace eastl {
struct HeapString16 : string16_s006b_5770 {
    HeapString16() {
        mpBegin = gEmptyStringRep;
        mpEnd = gEmptyStringRep;
        mpCapacity = gEmptyStringRep + 1;
    }
    static void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
};
}
namespace eastl {
void __cdecl operator_delete_array(void* p) throw();   // 0x00f47380
}
namespace eastl {
inline LocalString16::~LocalString16()
{
    if ((int)(((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
        operator_delete_array(mpBegin);
}
}
namespace eastl {
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
}
namespace App {
struct intrusive_ptr {
    ITokenTranslator* ptr;   // +0

    intrusive_ptr(ITokenTranslator* p);
    intrusive_ptr(ITokenTranslator* p, int) : ptr(p) {}   // adopts an existing reference
    intrusive_ptr(const intrusive_ptr& o);
    ~intrusive_ptr();
    intrusive_ptr& operator=(const intrusive_ptr& o);
};
}
namespace App {
struct TranslatorVector {
    intrusive_ptr* mpBegin;      // +0
    intrusive_ptr* mpEnd;        // +4
    intrusive_ptr* mpCapacity;   // +8

    __declspec(noinline) intrusive_ptr* erase(intrusive_ptr* pos);   // 0x006b5990
    intrusive_ptr* erase(intrusive_ptr* first, intrusive_ptr* last);   // 0x005c2170
    void push_back(const intrusive_ptr& v);                            // 0x006b5f80
    void DoInsertValue(intrusive_ptr* pos, const intrusive_ptr* pValue);
};
}
namespace App {
struct ITokenTranslator {
    virtual void Slot00();                                                     // +0x00
    virtual int  AddRef();                                                     // +0x04
    virtual int  Release();                                                    // +0x08
    virtual void* Cast(uint32_t typeID);                                       // +0x0c
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16_s006b_5770& dst);  // +0x10
    virtual void func14h(int);                                                 // +0x14

    int mnRefCount;   // +0x04
};
}
namespace App {
inline intrusive_ptr::intrusive_ptr(ITokenTranslator* p) : ptr(p)
{
    if (ptr) ptr->AddRef();
}
}
namespace App {
inline intrusive_ptr::intrusive_ptr(const intrusive_ptr& o) : ptr(o.ptr)
{
    if (ptr) ptr->AddRef();
}
}
namespace App {
inline intrusive_ptr::~intrusive_ptr()
{
    if (ptr) ptr->Release();
}
}
namespace App {
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
}
namespace App {
struct TokenEntry {
    uint32_t hash;          // +0
    eastl::string16_s006b_5770 str;    // +4
};
}
namespace App {
struct SPCString {
    void* vtbl;                  // +0x00
    eastl::string16_s006b_5770* mpOut;      // +0x04
    const wchar16* mpSrc;        // +0x08
    int pad0c;                   // +0x0c
    bool mbEnabled;              // +0x10
    bool mbDirty;                // +0x11
};
}
namespace App {
struct cStringDetokenizer : ITokenTranslator {
    virtual void func18h();                                                    // +0x18
    virtual void AddTranslator(ITokenTranslator*);                             // +0x1c
    virtual void RemoveTranslator(ITokenTranslator*);                          // +0x20
    virtual bool HasTokens(const wchar16* pStr);                               // +0x24
    virtual bool func28h(void* a, eastl::string16_s006b_5770& dst);                       // +0x28
    virtual bool ProcessString(const wchar16* pStr, eastl::string16_s006b_5770& dst);     // +0x2c
    virtual bool func30h(SPCString* s, TokenEntry* table, uint32_t count);      // +0x30
    virtual void func34h(const wchar16* pStr, uint32_t index);                 // +0x34
    virtual bool ProcessStringEx(const wchar16* pStr, eastl::string16_s006b_5770& dst, TokenEntry* table, uint32_t count); // +0x38
    virtual bool FindTokenTranslation(const wchar16* pToken, eastl::string16_s006b_5770& dst); // +0x3c
    // Override of ITokenTranslator::TranslateToken (slot +0x10).
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16_s006b_5770& dst);

    TranslatorVector mTranslators;       // +0x08 (begin/end/cap)
    uint32_t mPad14;                     // +0x14
    uint32_t mPad18;                     // +0x18
    eastl::string16_s006b_5770 mGenericTokens[4];   // +0x1c
};
}
namespace App {
void ITokenTranslator::Slot00() {}
}
namespace App {
int  ITokenTranslator::AddRef() { return 1; }
}
namespace App {
int  ITokenTranslator::Release() { return 0; }
}
namespace App {
void* ITokenTranslator::Cast(uint32_t) { return 0; }
}
namespace App {
bool ITokenTranslator::TranslateToken(const wchar16*, eastl::string16_s006b_5770&) { return false; }
}
void* __cdecl SporeAlloc(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned n);                          // 0x011e0744
void __cdecl copy_backward_ool(App::intrusive_ptr* first, App::intrusive_ptr* last, App::intrusive_ptr* destEnd); // 0x005c1dc0
uint32_t __cdecl FNV1_String16(const wchar16* s, uint32_t basis, int a);                              // 0x00932f30
static inline unsigned CharStrlen16(const wchar16* p)
{
    return wcslen((const wchar_t*)p);
}
static unsigned HandStrlen16(const wchar16* p)
{
    const wchar16* e = p;
    while (*e)
        ++e;
    return (unsigned)(e - p);
}
// ---- items of slice s006b5770 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern wchar16 gEmptyStringRep[2];   // 0x01667bac: eastl empty-string rep

// @ 0x006b5880
bool App::cStringDetokenizer::FindTokenTranslation(const wchar16* pToken, eastl::string16_s006b_5770& dst)
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

// @ 0x006b5bd0
bool App::cStringDetokenizer::ProcessString(const wchar16* pStr, eastl::string16_s006b_5770& dst)
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
bool App::cStringDetokenizer::ProcessStringEx(const wchar16* pStr, eastl::string16_s006b_5770& dst, App::TokenEntry* table, uint32_t count)
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
void TranslatorVector_pushback_stub()
{}

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

// @ 0x006b6160
bool App::cStringDetokenizer::TranslateToken(const wchar16* tok, eastl::string16_s006b_5770& dst)
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
