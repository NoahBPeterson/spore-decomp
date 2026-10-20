// src/game/UTFSpore_Win32/Base64.cpp -- migrated from slice(s) s009413d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Base64.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" const unsigned char g_base64DecodeTable[256];   // 0x143EE70

// ---- items of slice s009413d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static const char kBase64Chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
extern "C" const unsigned char g_base64DecodeTable[256];   // 0x143EE70
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
    unsigned n = len;
    int needed = ((n + 3) >> 2) * 3;
    if ((unsigned)*outLen < (unsigned)needed)
        return false;
    unsigned i = 0;
    unsigned out = 0;
    bool invalid = false;
    bool padding = false;
    if (n > 0) {
        for (;;) {
            uint32_t group[4] = { 0, 0, 0, 0 };
            unsigned m = 4;
            uint32_t* p = group;
            do {
                while (i < n) {
                    unsigned c = src[i++];
                    *p = c;
                    if (c < 0x80 && g_base64DecodeTable[c] != 0xff)
                        break;
                    if (c == '=') {
                        padding = true;
                        break;
                    }
                    if (c != '\r' && c != '\n' && c != ' ' && c != '\t')
                        invalid = true;
                }
                p++;
            } while (--m);

            unsigned c0 = group[0], c1 = group[1], c2 = group[2], c3 = group[3];
            if (c0 < 0x80 && g_base64DecodeTable[c0] != 0xff &&
                c1 < 0x80 && g_base64DecodeTable[c1] != 0xff &&
                c2 < 0x80 && g_base64DecodeTable[c2] != 0xff &&
                c3 < 0x80 && g_base64DecodeTable[c3] != 0xff) {
                unsigned a0 = g_base64DecodeTable[c0], a1 = g_base64DecodeTable[c1];
                unsigned a2 = g_base64DecodeTable[c2], a3 = g_base64DecodeTable[c3];
                dst[out]     = (char)(((a0 & 0x3f) << 2) | ((a1 >> 4) & 3));
                dst[out + 1] = (char)(((a1 & 0xf) << 4) | ((a2 >> 2) & 0xf));
                dst[out + 2] = (char)(((a2 & 3) << 6) | (a3 & 0x3f));
                out += 3;
                if (padding || i >= n)
                    break;
                continue;
            }
            if (c0 < 0x80 && g_base64DecodeTable[c0] != 0xff &&
                c1 < 0x80 && g_base64DecodeTable[c1] != 0xff &&
                c2 < 0x80 && g_base64DecodeTable[c2] != 0xff &&
                c3 == '=') {
                unsigned a0 = g_base64DecodeTable[c0], a1 = g_base64DecodeTable[c1];
                unsigned a2 = g_base64DecodeTable[c2];
                dst[out]     = (char)(((a0 & 0x3f) << 2) | ((a1 >> 4) & 3));
                dst[out + 1] = (char)(((a1 & 0xf) << 4) | ((a2 >> 2) & 0xf));
                out += 2;
                break;
            }
            if (c0 < 0x80 && g_base64DecodeTable[c0] != 0xff &&
                c1 < 0x80 && g_base64DecodeTable[c1] != 0xff &&
                c2 == '=' && c3 == '=') {
                unsigned a0 = g_base64DecodeTable[c0], a1 = g_base64DecodeTable[c1];
                dst[out] = (char)(((a0 & 0x3f) << 2) | ((a1 >> 4) & 3));
                out += 1;
                break;
            }
            break;
        }
    }
    *outLen = out;
    return !invalid;
}
