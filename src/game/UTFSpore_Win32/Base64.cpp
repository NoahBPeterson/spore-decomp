// src/game/UTFSpore_Win32/Base64.cpp -- migrated from slice(s) s009413d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Base64.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s009413d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static const char kBase64Chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// ---- items of slice s009413d0 end

// @ 0x009415f0
namespace EA {
namespace Internet {
bool EncodeBase64(char const * src, unsigned int len, char * dst, unsigned int & outLen)
{
    int in = 0;
    int out = 0;
    int line = 0;
    for (int n = len / 3; n != 0; n--) {
        uint8_t b0 = src[in];
        uint8_t b1 = src[in + 1];
        uint8_t b2 = src[in + 2];
        dst[out] = kBase64Chars[(int)b0 >> 2];
        dst[out + 1] = kBase64Chars[((int)(unsigned)b1 >> 4) | ((b0 & 3) << 4)];
        dst[out + 2] = kBase64Chars[((int)(unsigned)b2 >> 6) | ((b1 & 0xf) << 2)];
        dst[out + 3] = kBase64Chars[b2 & 0x3f];
        line += 4;
        in += 3;
        int next = out + 4;
        if (line > 0x48) {
            dst[next] = '\n';
            next = out + 5;
            line = 0;
        }
        out = next;
    }
    switch (len % 3) {
    case 1: {
        uint8_t b0 = src[in];
        dst[out] = kBase64Chars[(int)b0 >> 2];
        dst[out + 1] = kBase64Chars[(b0 & 3) << 4];
        dst[out + 2] = '=';
        dst[out + 3] = '=';
        outLen = out + 4;
        return true;
    }
    case 2: {
        uint8_t b0 = src[in];
        uint8_t b1 = src[in + 1];
        dst[out] = kBase64Chars[(int)b0 >> 2];
        dst[out + 1] = kBase64Chars[((int)(unsigned)b1 >> 4) | ((b0 & 3) << 4)];
        dst[out + 2] = kBase64Chars[(b1 & 0xf) << 2];
        dst[out + 3] = '=';
        outLen = out + 4;
        return true;
    }
    }
    outLen = out;
    return true;
}
}
}  // namespace EA::Internet

// @ 0x00941790
bool DecodeBase64Core(const uint8_t* src, int len, char* dst, int* outLen)
{
    int out = 0;
    int i = 0;
    (void)src;
    (void)len;
    *outLen = out;
    (void)i;
    return true;
}
