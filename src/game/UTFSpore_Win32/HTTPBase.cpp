// src/game/UTFSpore_Win32/HTTPBase.cpp -- migrated from slice(s) s009413d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/HTTPBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPMethod.h"
#include "EA/Internet/HTTPHeaderField.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
extern "C" __declspec(dllimport) int __cdecl isalnum(int);
extern "C" void EastlStringPushBack(void* str, char c);          // 0x005306C0
extern "C" void EastlStringAppend(void* str, const char* s, const char* e); // 0x00455D60

// ---- items of slice s009413d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
extern "C" __declspec(dllimport) int __cdecl isalnum(int);
extern "C" void EastlStringPushBack(void* str, char c);          // 0x005306C0
extern "C" void EastlStringAppend(void* str, const char* s, const char* e); // 0x00455D60
// ---- items of slice s009413d0 end

// @ 0x00941bc0
namespace EA {
namespace Internet {
char const * HTTPMethodToString(HTTPMethod method)
{
    switch (method) {
    case 2: return "GET";
    case 3: return "HEAD";
    case 4: return "POST";
    case 5: return "PUT";
    case 6: return "DELETE";
    case 7: return "TRACE";
    case 8: return "PATCH";
    case 9: return "LINK";
    case 10: return "UNLINK";
    default: return "OPTIONS";
    }
}
}
}  // namespace EA::Internet

// @ 0x00941c40
namespace EA {
namespace Internet {
char const * HeaderFieldToFieldString(HTTPHeaderField field)
{
    switch (field) {
    case 1: return "Cache-Control";
    case 2: return "Connection";
    case 3: return "Date";
    case 4: return "Pragma";
    case 5: return "Transfer-Encoding";
    case 6: return "Upgrade";
    case 7: return "Via";
    case 8: return "Accept";
    case 9: return "Accept-Charset";
    case 10: return "Accept-Encoding";
    case 0xb: return "Accept-Language";
    case 0xc: return "Authorization";
    case 0xd: return "From";
    case 0xe: return "Host";
    case 0xf: return "If-Modified-Since";
    case 0x10: return "If-Match";
    case 0x11: return "If-None-Match";
    case 0x12: return "If-Range";
    case 0x13: return "If-Unmodified-Since";
    case 0x14: return "Max-Forwards";
    case 0x15: return "Proxy-Authorization";
    case 0x16: return "Range";
    case 0x17: return "Referer";
    case 0x18: return "User-Agent";
    case 0x19: return "Age";
    case 0x1a: return "Location";
    case 0x1b: return "Proxy-Authenticate";
    case 0x1c: return "Public";
    case 0x1d: return "Retry-After";
    case 0x1e: return "Server";
    case 0x1f: return "Vary";
    case 0x20: return "Warning";
    case 0x21: return "WWW-Authenticate";
    case 0x22: return "Allow";
    case 0x23: return "Content-Base";
    case 0x24: return "Content-Encoding";
    case 0x25: return "Content-Language";
    case 0x26: return "Content-Length";
    case 0x27: return "Content-Location";
    case 0x28: return "Content-MD5";
    case 0x29: return "Content-Range";
    case 0x2a: return "Content-Type";
    case 0x2b: return "ETag";
    case 0x2c: return "Expires";
    case 0x2d: return "Last-Modified";
    case 0x2e: return "Alternates";
    case 0x2f: return "Content-Version";
    case 0x30: return "Derived-From";
    case 0x31: return "Link";
    case 0x32: return "URI";
    case 0x33: return "Keep-Alive";
    case 0x34: return "Set-Cookie";
    case 0x35: return "Set-Cookie2";
    case 0x36: return "Cookie";
    default: return "Unknown";
    }
}
}
}  // namespace EA::Internet

// @ 0x00941e80
void EncodeFormURL(const char* s, void* out)
{
    for (const uint8_t* p = (const uint8_t*)s; *p != 0; p++) {
        if (isspace(*p)) {
            EastlStringPushBack(out, '+');
        } else if (isalnum(*p)) {
            EastlStringPushBack(out, (char)*p);
        } else {
            char buf[8];
            sprintf(buf, "%%%2X", *p);
            const char* q = buf;
            while (*q)
                q++;
            EastlStringAppend(out, buf, q);
        }
    }
}
