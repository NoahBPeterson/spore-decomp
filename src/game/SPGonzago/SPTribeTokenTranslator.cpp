// src/game/SPGonzago/SPTribeTokenTranslator.cpp -- migrated from slice(s) s00ce6660 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeTokenTranslator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00ce6660 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct WString {
    void     append(const wchar_t* text);        // 0x005c3d90
    WString& operator=(const WString& rhs);      // 0x0057cb60
};
}
namespace SP {
struct cProfile {
    void GetUiName(WString* out);                // 0x004da330
};
}
namespace SP {
struct cNamedObject {
    virtual void      slot00();
    virtual void      slot04();
    virtual void      slot08();
    virtual void      slot0c();
    virtual void      slot10();
    virtual void      slot14();
    virtual void      slot18();
    virtual void      slot1c();
    virtual void      slot20();
    virtual void      slot24();
    virtual void      slot28();
    virtual void      slot2c();
    virtual void      slot30();
    virtual void      slot34();
    virtual void      slot38();
    virtual void      slot3c();
    virtual void      slot40();
    virtual void      slot44();
    virtual void      slot48();
    virtual void      slot4c();
    virtual void      slot50();
    virtual void      slot54();
    virtual void      slot58();
    virtual void      slot5c();
    virtual void      slot60();
    virtual void      slot64();
    virtual void      slot68();
    virtual void      slot6c();
    virtual void      slot70();
    virtual void      slot74();
    virtual void      slot78();
    virtual WString*  GetDisplayName();          // vtable +0x7c
};
}
namespace SP {
struct cCivTokenTranslator {
    bool TranslateToken(const wchar_t* token, WString* out);   // 0x00b324f0
};
}
namespace SP {
struct cTribeTokenTranslator {
    uint8_t         mPad00[0x0c];                // +0x00
    int32_t         mValue0c;                    // +0x0c
    int32_t         mValue10;                    // +0x10
    uint8_t*        mpValue14;                   // +0x14
    cProfile*       mpProfile18;                 // +0x18
    cNamedObject*   mpNamed1c;                   // +0x1c

    bool TranslateToken(const wchar_t* token, WString* out);
};
}
extern "C" uint32_t __cdecl FNV1_String16(const wchar_t* s, uint32_t seed, int mode); // 0x00932f30
extern "C" void __cdecl SetNumberString64(long long value, wchar_t* buf, int size);    // 0x00881ae0
extern "C" void __cdecl SetNumberString(int value, int sign, wchar_t* buf, int size);  // 0x00881ae0 (value, sign form)
namespace SP {
extern "C" const wchar_t gTokenText[];                                                // 0x013ec468
}
namespace SP {
extern "C" float gTokenValue;                                                         // 0x0158133c
}
// ---- items of slice s00ce6660 end

// @ 0x00ce6660
#include "sse_helpers.h"
namespace SP { struct cSpeciesManager { cProfile* GetAvatarProfile(); }; }
namespace SP { extern "C" cSpeciesManager* __cdecl GetSpeciesManager(); }
bool SP::cTribeTokenTranslator::TranslateToken(const wchar_t* token, SP::WString* out)
{
    switch (FNV1_String16(token, 0x811c9dc5, 1)) {
    case 0x1cb36f87: {
        wchar_t buf[0x40];
        SetNumberString64(mValue0c, buf, 0x40);
        out->append(buf);
        return true;
    }
    case 0x39c16a23: {
        wchar_t buf[0x40];
        SetNumberString64(mValue0c, buf, 0x40);
        out->append(buf);
        return true;
    }
    case 0x72edb111: {
        wchar_t buf[0x40];
        float value = SP::gTokenValue;
        SetNumberString(SseTruncToInt(value), 0, buf, 0x40);
        out->append(buf);
        return true;
    }
    case 0xafd98ffd: {
        wchar_t buf[0x40];
        out->append(SP::gTokenText);
        SetNumberString64(mValue10, buf, 0x40);
        buf[0x3f] = 0;
        out->append(buf);
        return true;
    }
    case 0xb4396ad6:
        mpProfile18->GetUiName(out);
        return true;
    case 0xcb37547d:
        if (mpValue14) {
            *out = *(SP::WString*)(mpValue14 + 0xb38);
            return true;
        }
        return false;
    case 0xdf3c2bf9: {
        wchar_t buf[0x40];
        out->append(SP::gTokenText);
        SetNumberString64(mValue0c, buf, 0x40);
        buf[0x3f] = 0;
        out->append(buf);
        return true;
    }
    case 0xf7a4ad93:
        if (!mpNamed1c)
            return false;
        *out = *mpNamed1c->GetDisplayName();
        return true;
    case 0xfd26cbf8: {
        SP::cProfile* profile = SP::GetSpeciesManager()->GetAvatarProfile();
        profile->GetUiName(out);
        return true;
    }
    default:
        return ((SP::cCivTokenTranslator*)this)->TranslateToken(token, out);
    }
}
