// src/game/SPEngine/SPStringDetokenizer.cpp -- migrated from slice(s) s006b5770 by tools/migrate/rewrite.py
// Object file: SPEngine/SPStringDetokenizer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s006b5770 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short wchar16;
namespace eastl {
struct string16_s006b_5770 {
    wchar16* mpBegin;      // +0
    wchar16* mpEnd;        // +4
    wchar16* mpCapacity;   // +8
    int      mAllocator;   // +0xc

    void assign(const wchar16* first, const wchar16* last);
};
}
namespace App {
struct ITokenTranslator;
}
namespace App {
struct intrusive_ptr {
    ITokenTranslator* ptr;   // +0
};
}
namespace App {
struct TranslatorVector {
    intrusive_ptr* mpBegin;   // +0
    intrusive_ptr* mpEnd;     // +4

    intrusive_ptr* erase(intrusive_ptr* pos);
};
}
namespace App {
struct ITokenTranslator {
    virtual int  AddRef();                                                     // +0x00
    virtual int  Release();                                                    // +0x04
    virtual void Destroy();                                                    // +0x08
    virtual void* Cast(uint32_t typeID);                                       // +0x0c
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16_s006b_5770& dst);  // +0x10
    virtual void func14h(int);                                                 // +0x14

    int mnRefCount;   // +0x04
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
    virtual bool func30h(void*, void*, void*);                                 // +0x30
    virtual void func34h(const wchar16* pStr, uint32_t index);                 // +0x34
    virtual bool ProcessStringEx(const wchar16* pStr, eastl::string16_s006b_5770& dst);   // +0x38
    virtual bool FindTokenTranslation(const wchar16* pToken, eastl::string16_s006b_5770& dst); // +0x3c

    TranslatorVector mTranslators;       // +0x08 (begin/end/cap; cap at +0x10)
    intrusive_ptr* mpTranslatorsCap;     // +0x10
    uint32_t mPad14;                     // +0x14
    uint32_t mPad18;                     // +0x18
    eastl::string16_s006b_5770 mGenericTokens[4];   // +0x1c
};
}
namespace App {
int  ITokenTranslator::AddRef() { return 1; }
}
namespace App {
int  ITokenTranslator::Release() { return 0; }
}
namespace App {
void ITokenTranslator::Destroy() {}
}
namespace App {
void* ITokenTranslator::Cast(uint32_t) { return 0; }
}
namespace App {
bool ITokenTranslator::TranslateToken(const wchar16*, eastl::string16_s006b_5770&) { return false; }
}
namespace App {
void cStringDetokenizer::func18h() {}
}
namespace App {
void cStringDetokenizer::AddTranslator(ITokenTranslator*) {}
}
namespace App {
bool cStringDetokenizer::ProcessString(const wchar16*, eastl::string16_s006b_5770&) { return false; }
}
namespace App {
bool cStringDetokenizer::func30h(void*, void*, void*) { return false; }
}
namespace App {
bool cStringDetokenizer::ProcessStringEx(const wchar16*, eastl::string16_s006b_5770&) { return false; }
}
void TranslatorVector_pushback_stub();
// ---- items of slice s006b5770 end

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

// @ 0x006b5f80
void TranslatorVector_pushback_stub()
{}
