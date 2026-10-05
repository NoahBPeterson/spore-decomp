// slice s006b5770: App::cStringDetokenizer / ITokenTranslator and
// SP::cStringTableResourceFactory.
// Flags: /O2 /MD /Gy /TP
#include "types.h"

typedef unsigned short wchar16;

__declspec(dllimport) wchar16* __cdecl wcschr(const wchar16* s, wchar16 c);

// ---------------------------------------------------------------------------
// Value types.
// ---------------------------------------------------------------------------
namespace eastl {
struct string16 {
    wchar16* mpBegin;      // +0
    wchar16* mpEnd;        // +4
    wchar16* mpCapacity;   // +8
    int      mAllocator;   // +0xc

    void assign(const wchar16* first, const wchar16* last);
};
}

namespace App {

struct ITokenTranslator;

struct intrusive_ptr {
    ITokenTranslator* ptr;   // +0
};

// Iterator over eastl::vector<intrusive_ptr>.
struct TranslatorVector {
    intrusive_ptr* mpBegin;   // +0
    intrusive_ptr* mpEnd;     // +4

    intrusive_ptr* erase(intrusive_ptr* pos);
};

struct ITokenTranslator {
    virtual int  AddRef();                                                     // +0x00
    virtual int  Release();                                                    // +0x04
    virtual void Destroy();                                                    // +0x08
    virtual void* Cast(uint32_t typeID);                                       // +0x0c
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16& dst);  // +0x10
    virtual void func14h(int);                                                 // +0x14

    int mnRefCount;   // +0x04
};

struct cStringDetokenizer : ITokenTranslator {
    virtual void func18h();                                                    // +0x18
    virtual void AddTranslator(ITokenTranslator*);                             // +0x1c
    virtual void RemoveTranslator(ITokenTranslator*);                          // +0x20
    virtual bool HasTokens(const wchar16* pStr);                               // +0x24
    virtual bool func28h(void* a, eastl::string16& dst);                       // +0x28
    virtual bool ProcessString(const wchar16* pStr, eastl::string16& dst);     // +0x2c
    virtual bool func30h(void*, void*, void*);                                 // +0x30
    virtual void func34h(const wchar16* pStr, uint32_t index);                 // +0x34
    virtual bool ProcessStringEx(const wchar16* pStr, eastl::string16& dst);   // +0x38
    virtual bool FindTokenTranslation(const wchar16* pToken, eastl::string16& dst); // +0x3c

    TranslatorVector mTranslators;       // +0x08 (begin/end/cap; cap at +0x10)
    intrusive_ptr* mpTranslatorsCap;     // +0x10
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
        p->Destroy();
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
// Partial reconstructions of the remaining functions (see partial.txt).
// ---------------------------------------------------------------------------
namespace App {

int  ITokenTranslator::AddRef() { return 1; }
int  ITokenTranslator::Release() { return 0; }
void ITokenTranslator::Destroy() {}
void* ITokenTranslator::Cast(uint32_t) { return 0; }
bool ITokenTranslator::TranslateToken(const wchar16*, eastl::string16&) { return false; }

void cStringDetokenizer::func18h() {}
void cStringDetokenizer::AddTranslator(ITokenTranslator*) {}
bool cStringDetokenizer::ProcessString(const wchar16*, eastl::string16&) { return false; }
bool cStringDetokenizer::func30h(void*, void*, void*) { return false; }
bool cStringDetokenizer::ProcessStringEx(const wchar16*, eastl::string16&) { return false; }

void cStringDetokenizer_ctor(cStringDetokenizer* self);

} // namespace App

// @ 0x006b5770
namespace SP {
struct cString {
    cString();
};
}
SP::cString::cString() {}

// @ 0x006b59d0
void TranslatorVector_pushback_stub();

// @ 0x006b5bd0
// ProcessString is defined above as App::cStringDetokenizer::ProcessString.

// @ 0x006b5c50
// func30h is defined above.

// @ 0x006b5d20
// ProcessStringEx is defined above.

// @ 0x006b5f80
void TranslatorVector_pushback_stub() {}

// @ 0x006b6000
// func18h is defined above.

// @ 0x006b6080
// AddTranslator is defined above.

// @ 0x006b6160
// TranslateToken is defined above.

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
