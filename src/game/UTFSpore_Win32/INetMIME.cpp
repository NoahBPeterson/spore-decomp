// src/game/UTFSpore_Win32/INetMIME.cpp -- migrated from slice(s) s00949cc0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/INetMIME.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/MIMEType.h"
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>

// @ 0x00949dc0
unsigned int FNVHash8Lower(const char* p, const char* end)
{
    unsigned int hash = 0x811c9dc5;
    unsigned char c = (unsigned char)*p;
    while (c != 0 && p != end) {
        hash = hash * 0x1000193 ^ (unsigned int)tolower(c);
        ++p;
        c = (unsigned char)*p;
    }
    return hash;
}

// @ 0x00949e10
namespace EA {
namespace Internet {
MIMEType MIMETypeStringToMIMEType(char const * begin, bool b, unsigned int len)
{
    unsigned int h = FNVHash8Lower(begin, begin + len);
    if (b) {
        switch (h) {
        case 0x9e7c75bf: return (EA::Internet::MIMEType)(2);
        case 0x527ffacd: return (EA::Internet::MIMEType)(4);
        case 0x2954e734: return (EA::Internet::MIMEType)(8);
        case 0x3fc40859: return (EA::Internet::MIMEType)(6);
        case 0x9e0b246c: return (EA::Internet::MIMEType)(5);
        case 0xb12bfa38: return (EA::Internet::MIMEType)(1);
        case 0xb1cc1af6: return (EA::Internet::MIMEType)(7);
        case 0xdbfffa2a: return (EA::Internet::MIMEType)(3);
        default: break;
        }
        return (EA::Internet::MIMEType)(0);
    }
    switch (h) {
        case 0x5b865ed7: return (EA::Internet::MIMEType)(0x1d);
        case 0x37ff7999: return (EA::Internet::MIMEType)(0x1e);
        case 0x1e639c34: return (EA::Internet::MIMEType)(0x10);
        case 0x14f8d92a: return (EA::Internet::MIMEType)(0x43);
        case 0x0dd5cf93: return (EA::Internet::MIMEType)(9);
        case 0x0e3280e9: return (EA::Internet::MIMEType)(0xf);
        case 0x0f9793fe: return (EA::Internet::MIMEType)(0xe);
        case 0x1a8ce475: return (EA::Internet::MIMEType)(0x35);
        case 0x1c099b80: return (EA::Internet::MIMEType)(0x1a);
        case 0x2c978db6: return (EA::Internet::MIMEType)(0x12);
        case 0x2550ebdc: return (EA::Internet::MIMEType)(0x1f);
        case 0x2b72bb3f: return (EA::Internet::MIMEType)(0x11);
        case 0x2ce51530: return (EA::Internet::MIMEType)(0xd);
        case 0x35943f2c: return (EA::Internet::MIMEType)(0x22);
        case 0x465dcb52: return (EA::Internet::MIMEType)(0x33);
        case 0x390d80e9: return (EA::Internet::MIMEType)(0x24);
        case 0x386cbfc3: return (EA::Internet::MIMEType)(0x36);
        case 0x3872cfb2: return (EA::Internet::MIMEType)(0x39);
        case 0x38f65389: return (EA::Internet::MIMEType)(0x1c);
        case 0x3caa495a: return (EA::Internet::MIMEType)(0x31);
        case 0x41775b4e: return (EA::Internet::MIMEType)(0x38);
        case 0x52c9da9e: return (EA::Internet::MIMEType)(0x15);
        case 0x477764fd: return (EA::Internet::MIMEType)(0x2b);
        case 0x4a0b828e: return (EA::Internet::MIMEType)(0x1b);
        case 0x575d15bd: return (EA::Internet::MIMEType)(0x19);
        case 0x5831000d: return (EA::Internet::MIMEType)(0x30);
        case 0x7cf2ac0e: return (EA::Internet::MIMEType)(10);
        case 0x604d8fc8: return (EA::Internet::MIMEType)(0x17);
        case 0xbac63b5a: return (EA::Internet::MIMEType)(0x14);
        case 0x9ec736df: return (EA::Internet::MIMEType)(0x42);
        case 0x883807a2: return (EA::Internet::MIMEType)(0x40);
        case 0x7db6b69b: return (EA::Internet::MIMEType)(0x27);
        case 0x80ffa9f7: return (EA::Internet::MIMEType)(0xb);
        case 0x88d95348: return (EA::Internet::MIMEType)(0x18);
        case 0x9dd66363: return (EA::Internet::MIMEType)(0x2a);
        case 0xae6c4306: return (EA::Internet::MIMEType)(0x4a);
        case 0xa736778c: return (EA::Internet::MIMEType)(0x37);
        case 0xac75ecec: return (EA::Internet::MIMEType)(0x20);
        case 0xaf4060dc: return (EA::Internet::MIMEType)(0x29);
        case 0xb4829beb: return (EA::Internet::MIMEType)(0x28);
        case 0xdca43ae7: return (EA::Internet::MIMEType)(0x32);
        case 0xc718e10d: return (EA::Internet::MIMEType)(0x3e);
        case 0xbd85000a: return (EA::Internet::MIMEType)(0x2c);
        case 0xc6620ff5: return (EA::Internet::MIMEType)(0x23);
        case 0xcb0e0d45: return (EA::Internet::MIMEType)(0x16);
        case 0xdb3cc501: return (EA::Internet::MIMEType)(0x21);
        case 0xe88db35f: return (EA::Internet::MIMEType)(0x34);
        case 0xdd6233d6: return (EA::Internet::MIMEType)(0xc);
        case 0xe480a535: return (EA::Internet::MIMEType)(0x44);
        case 0xe919578e: return (EA::Internet::MIMEType)(0x49);
        case 0xfc19f3e8: return (EA::Internet::MIMEType)(0x13);
        default: break;
        }
    return (EA::Internet::MIMEType)(0);
}
}
}  // namespace EA::Internet

// @ 0x0094a1b0
namespace EA {
namespace Internet {
int MIMETypesToFileExtension(MIMEType type, MIMEType sub, wchar_t * out, unsigned int outLen)
{
    const wchar_t* ext = 0;
    switch (type) {
    case 1:
        switch (sub) {
        case 9: ext = L".txt"; break;
        case 0xc: case 0xd: case 0x10: ext = L".html"; break;
        case 0x11: ext = L".rtf"; break;
        case 0x12: ext = L".css"; break;
        case 0x13: ext = L".js"; break;
        default: return 0;
        }
        break;
    case 4:
        switch (sub) {
        case 0x26: ext = L".bin"; break;
        case 0x28: ext = L".xls"; break;
        case 0x29: ext = L".doc"; break;
        case 0x2b: ext = L".pdf"; break;
        case 0x30: ext = L".tar"; break;
        case 0x32: ext = L".exe"; break;
        case 0x33: ext = L".zip"; break;
        default: return 0;
        }
        break;
    case 5:
        switch (sub) {
        case 0x34: ext = L".jpeg"; break;
        case 0x35: ext = L".gif"; break;
        case 0x36: ext = L".tga"; break;
        case 0x37: ext = L".tiff"; break;
        case 0x38: ext = L".png"; break;
        case 0x3d: ext = L".bmp"; break;
        default: return 0;
        }
        break;
    case 6:
        if (sub != 0x40) return 0;
        ext = L".wav";
        break;
    case 7:
        switch (sub) {
        case 0x42: ext = L".mpg"; break;
        case 0x43: ext = L".qts"; break;
        case 0x44: ext = L".avi"; break;
        case 0x48: ext = L".tgq"; break;
        default: return 0;
        }
        break;
    default:
        return 0;
    }
    if (outLen > 0) {
        wcsncpy(out, ext, outLen);
        out[outLen - 1] = 0;
    }
    return (int)wcslen(ext);
}
}
}  // namespace EA::Internet
