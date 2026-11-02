// src/game/SPGonzago/SPCreatureTokenTranslator.cpp -- migrated from slice(s) s00d48010 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureTokenTranslator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern const wchar_t kTokenError[];      // 0x0147ae78 L"*TOKEN ERROR*"
extern const wchar_t kTokenNumberSep[];  // 0x013ec468 number prefix text

// ---- items of slice s00d48010 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WString
{
    wchar_t* mpBegin;        // +0
    wchar_t* mpEnd;          // +4
    wchar_t* mpCapacity;     // +8

    WString& assign(const wchar_t* s);                            // 0x005c3d90 (ret 4)
    WString& Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650 (ret 8)
};
class cSpeciesProfile
{
public:
    void GetUiName(WString* out);            // 0x004da330 (ret 4)
};
class cCivTokenTranslator
{
public:
    cCivTokenTranslator();                                           // 0x00b32470
    virtual bool TranslateToken(const wchar_t* token, WString* out); // 0x00b324f0 (ret 8)
    uint32_t pad04[2];                                               // +0x04 .. +0x0b
};
class cCreatureTokenTranslator : public cCivTokenTranslator
{
public:
    cCreatureTokenTranslator();                                      // 0x00d486f0

    uint32_t mValueC;                // +0x0c
    uint32_t mValue10;               // +0x10
    uint32_t mValue14;               // +0x14
    uint32_t mValue18;               // +0x18
    cSpeciesProfile* mpProfile;      // +0x1c
    int32_t mValue20;                // +0x20
    int32_t mValue24;                // +0x24
    const wchar_t* mpText;           // +0x28 (null = no token)
    float mValue2c;                  // +0x2c

    bool TranslateToken(const wchar_t* token, WString* out);         // 0x00d48750
};
extern const wchar_t kTokenError[];      // 0x0147ae78 L"*TOKEN ERROR*"
extern const wchar_t kTokenNumberSep[];  // 0x013ec468 number prefix text
uint32_t __cdecl FNV1_String16(const wchar_t* s, uint32_t seed, int fold);   // 0x00932f30
void __cdecl SetNumberString(int64_t value, wchar_t* buf, int cch);          // 0x00881ae0
void __cdecl FormatNumberDouble(double value, wchar_t* buf, int cch, int flags); // 0x00881ea0
static inline void AssignWideLiteral(WString* out, const wchar_t* s)
{
    const wchar_t* end = s;
    while (*end != 0)
        ++end;
    out->Assign(s, end);
}
// ---- items of slice s00d48010 end

// @ 0x00d48750
bool cCreatureTokenTranslator::TranslateToken(const wchar_t* token, WString* out)
{
    wchar_t buf[64];
    switch (FNV1_String16(token, 0x811c9dc5, 1))
    {
    case 0x7142102a:                        // species profile name
        AssignWideLiteral(out, kTokenError);
        if (mpProfile == 0)
            return true;
        mpProfile->GetUiName(out);
        return true;

    case 0x4276d4e:                         // signed count
        out->assign(kTokenError);
        SetNumberString((int64_t)mValue20, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x171f9d3:                         // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValue18, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x5edec022:                        // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValueC, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x801ac859:                        // unsigned count
        out->assign(kTokenNumberSep);
        SetNumberString((int64_t)mValue24, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0xe976268a:                        // float value
        out->assign(kTokenNumberSep);
        FormatNumberDouble((double)mValue2c, buf, 0x40, 0);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x548c1df2:                        // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValue10, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0xe37cf60f:                        // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValue14, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x485fc991:                        // literal text
    case 0xdb8f7823:
    case 0xd004e927:
        if (mpText == 0)
            return true;
        out->assign(mpText);
        return true;

    default:
        return cCivTokenTranslator::TranslateToken(token, out);
    }
}
