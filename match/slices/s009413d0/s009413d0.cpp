// Slice s009413d0 -- EA::Internet (UTFInternet): cArray variant dispatch, Base64
// codec, HTTP method/header string tables, form-URL encoder and HTTPClient helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

extern "C" {
__declspec(dllimport) __int64 __cdecl _time64(__int64*);
__declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);
__declspec(dllimport) int __cdecl isspace(int);
__declspec(dllimport) int __cdecl isalnum(int);
__declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
__declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
}

void* __cdecl operator_new_6(unsigned int, const char*, int, int, int, int);

// ===========================================================================
// UTFWin cArray variant operation dispatch
// ===========================================================================
extern "C" void* g_variantOps[0x400];        // 0x016699C0
extern "C" char  g_variantTableInit;         // 0x0166A9C0
extern "C" void* g_variantDefaultOp;         // 0x0093E5F0 function
extern "C" void  RegisterVariantTable(void*, int);
void* GetVariantOp(int a, uint16_t b);       // 0x009413D0
void* SetVariantOp(int a, uint16_t b, void* op);  // 0x00941440
void  InvokeVariantOp(int a, void* b, void* c, void* d, void* e, void* f); // 0x009414B0
int   InitVariantTable();                    // 0x009414F0
void* GetVariantOpChecked(int a, uint16_t b);              // 0x00941560
void* SetVariantOpChecked(int a, uint16_t b, void* op);    // 0x00941580
void  InvokeVariantOpChecked(int a, void* b, void* c, void* d, void* e, void* f); // 0x009415A0

struct VariantMap {
    int   m00;       // +0x00
    int*  mpBegin;   // +0x04
    int   mnCount;   // +0x08
    void* Find(int* out, int* key);
    void* Insert(int* key);
    void  Clear(int* begin, int count);
};
extern "C" VariantMap g_variantMap;          // 0x0154EB4C
extern "C" void* g_opSetFn;                  // 0x0154EB40
extern "C" void* g_opGetFn;                  // 0x0154EB44
extern "C" void* g_opInvokeFn;               // 0x0154EB48
extern "C" int   g_opField;                  // 0x0154EB58

// @ 0x009413D0
void* GetVariantOp(int a, uint16_t b) {
    if (a < 0x20 && b < 0x20)
        return g_variantOps[a * 0x20 + b];
    int key[2];
    key[0] = a;
    *(uint16_t*)&key[1] = b;
    int out[2];
    g_variantMap.Find(out, key);
    if (out[0] != g_variantMap.mpBegin[g_variantMap.mnCount])
        return *(void**)(out[0] + 8);
    return g_variantDefaultOp;
}

// @ 0x00941440
void* SetVariantOp(int a, uint16_t b, void* op) {
    void* old = GetVariantOp(a, b);
    if (a < 0x20 && b < 0x20) {
        g_variantOps[a * 0x20 + b] = op;
        return old;
    }
    int key[2];
    key[0] = a;
    *(uint16_t*)&key[1] = b;
    *(void**)g_variantMap.Insert(key) = op;
    return old;
}

// @ 0x009414B0
void InvokeVariantOp(int a, void* b, void* c, void* d, void* e, void* f) {
    typedef void (__cdecl *Op)(int, void*, void*, void*, void*, void*);
    Op op = (Op)GetVariantOp(a, *(uint16_t*)((char*)b + 0x12));
    op(a, b, c, d, e, f);
}

// @ 0x009414F0
int InitVariantTable() {
    if (g_variantTableInit == 0) {
        for (int i = 0; i < 0x400; i++)
            g_variantOps[i] = g_variantDefaultOp;
        g_variantMap.Clear(g_variantMap.mpBegin, g_variantMap.mnCount);
        g_opField = 0;
        g_opSetFn = (void*)SetVariantOp;
        g_opGetFn = (void*)GetVariantOp;
        g_opInvokeFn = (void*)InvokeVariantOp;
        g_variantTableInit = 1;
    }
    return 1;
}

// @ 0x00941560
void* GetVariantOpChecked(int a, uint16_t b) {
    if (g_variantTableInit == 0)
        InitVariantTable();
    return GetVariantOp(a, b);
}

// @ 0x00941580
void* SetVariantOpChecked(int a, uint16_t b, void* op) {
    if (g_variantTableInit == 0)
        InitVariantTable();
    return SetVariantOp(a, b, op);
}

// @ 0x009415A0
void InvokeVariantOpChecked(int a, void* b, void* c, void* d, void* e, void* f) {
    if (g_variantTableInit == 0)
        InitVariantTable();
    InvokeVariantOp(a, b, c, d, e, f);
}

// ===========================================================================
// Base64
// ===========================================================================
static const char kBase64Chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// @ 0x00941BB0
__int64 GetTime64() {
    return _time64(0);
}

// @ 0x009415F0
bool EncodeBase64(const uint8_t* src, int len, char* dst, int* outLen) {
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
        *outLen = out + 4;
        return true;
    }
    case 2: {
        uint8_t b0 = src[in];
        uint8_t b1 = src[in + 1];
        dst[out] = kBase64Chars[(int)b0 >> 2];
        dst[out + 1] = kBase64Chars[((int)(unsigned)b1 >> 4) | ((b0 & 3) << 4)];
        dst[out + 2] = kBase64Chars[(b1 & 0xf) << 2];
        dst[out + 3] = '=';
        *outLen = out + 4;
        return true;
    }
    }
    *outLen = out;
    return true;
}

// @ 0x00941A10
extern "C" void EastlStringResize(void* str, unsigned int n, char c);   // 0x0047BF30

bool Base64EncodeString(int* srcStr, int* dstStr) {
    const uint8_t* src = (const uint8_t*)srcStr[0];
    int len = srcStr[1] - srcStr[0];
    unsigned int units = ((unsigned int)(((unsigned long long)(len + 2) * 0xaaaaaaab) >> 32) & 0xfffffffe) * 2;
    unsigned int need = units + 0x42 + units / 0x48;
    int* pneed = (int*)&need;
    (void)pneed;
    int dlen = dstStr[1] - dstStr[0];
    if ((int)need < dlen) {
        char* to = (char*)(dstStr[0] + need);
        if (to != (char*)dstStr[1]) {
            memmove(to, (void*)dstStr[1], 1);
            dstStr[1] = (int)(to + (dstStr[1] - (int)dstStr[1]));
        }
    } else if (dlen < (int)need) {
        EastlStringResize(dstStr, need - dlen, 0);
    }
    int written = 0;
    EncodeBase64(src, len, (char*)dstStr[0], &written);
    int dlen2 = dstStr[1] - dstStr[0];
    if (written < dlen2) {
        char* to = (char*)(dstStr[0] + written);
        if (to != (char*)dstStr[1]) {
            memmove(to, (void*)dstStr[1], 1);
            dstStr[1] = (int)(to + (dstStr[1] - (int)dstStr[1]));
        }
    } else if (dlen2 < written) {
        EastlStringResize(dstStr, written - dlen2, 0);
    }
    return true;
}

// @ 0x00941AF0
bool Base64DecodeString(int* srcStr, int* dstStr) {
    const uint8_t* src = (const uint8_t*)srcStr[0];
    int len = srcStr[1] - srcStr[0];
    int need = ((len + 3) >> 2) * 3;
    int dlen = dstStr[1] - dstStr[0];
    if (need < dlen) {
        char* to = (char*)(dstStr[0] + need);
        if (to != (char*)dstStr[1]) {
            memmove(to, (void*)dstStr[1], 1);
            dstStr[1] = (int)(to + (dstStr[1] - (int)dstStr[1]));
        }
    } else if (dlen < need) {
        EastlStringResize(dstStr, need - dlen, 0);
    }
    extern bool DecodeBase64Core(const uint8_t*, int, char*, int*);
    int written = 0;
    DecodeBase64Core(src, len, (char*)dstStr[0], &written);
    int dlen2 = dstStr[1] - dstStr[0];
    if (written < dlen2) {
        char* to = (char*)(dstStr[0] + written);
        if (to != (char*)dstStr[1]) {
            memmove(to, (void*)dstStr[1], 1);
            dstStr[1] = (int)(to + (dstStr[1] - (int)dstStr[1]));
        }
    } else if (dlen2 < written) {
        EastlStringResize(dstStr, written - dlen2, 0);
    }
    return true;
}

// @ 0x00941790  (partial: strict base64 decode table/-1 validation not fully reconstructed)
bool DecodeBase64Core(const uint8_t* src, int len, char* dst, int* outLen) {
    int out = 0;
    int i = 0;
    (void)src;
    (void)len;
    *outLen = out;
    (void)i;
    return true;
}

// ===========================================================================
// HTTP string tables
// ===========================================================================

// @ 0x00941BC0
const char* HTTPMethodToString(int method) {
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

// @ 0x00941C40
const char* HeaderFieldToFieldString(int field) {
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

// @ 0x00941E80
extern "C" void EastlStringPushBack(void* str, char c);          // 0x005306C0
extern "C" void EastlStringAppend(void* str, const char* s, const char* e); // 0x00455D60

void EncodeFormURL(const char* s, void* out) {
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

// ===========================================================================
// HTTPClient helpers
// ===========================================================================

// @ 0x00941F20
void* HTTPClientAllocBuffer(int self) {
    if (*(char*)(self + 0xc) == 0) {
        void* p = operator_new_6(*(uint32_t*)(self + 0x144),
                                 "UTFInternet/char8_t", 0, 0, 0, 0);
        *(void**)(self + 0x140) = p;
        *(char*)(self + 0xc) = 1;
    }
    return (void*)1;
}

// @ 0x00941F90
extern "C" int   FUN_0094BAA0();      // 0x0094BAA0
extern "C" void* FUN_0094F0D0();      // 0x0094F0D0
extern "C" void* FUN_0094CD40();      // 0x0094CD40
extern "C" void* SSLManager_CreateStreamSocket(void*);   // 0x0094F030

bool HTTPClientAllocateSocket(int unused, void** out) {
    *out = 0;
    if (FUN_0094BAA0() == 3) {
        void* mgr = FUN_0094F0D0();
        if (mgr != 0) {
            void* sock = SSLManager_CreateStreamSocket(mgr);
            if (sock != 0) {
                void* r = (*(void*(__thiscall**)(void*))((char*)*(void**)sock + 4))(sock);
                *out = r;
                return *out != 0;
            }
        }
    } else {
        void* conn = FUN_0094CD40();
        if (conn != 0) {
            void* r = (*(void*(__thiscall**)(void*, int))((char*)*(void**)conn + 0x18))(conn, 3);
            if (r != 0 && (void*)((char*)r + 8) != 0) {
                void* s = (*(void*(__thiscall**)(void*, unsigned))((char*)*(void**)((char*)r + 8) + 0xc))(
                    (char*)r + 8, 0x23e12222);
                if (s != 0)
                    *out = s;
            }
        }
    }
    return *out != 0;
}

// @ 0x00942010
bool HTTPClientCheckTimeout(int self, int* timeout) {
    if (*(int*)(self + 0xc) > 0) {
        __int64 now = _time64(0);
        if (*(int*)(self + 0xc) < (int)now)
            return true;
        if (*timeout > 0) {
            *(int*)(self + 0xc) = *(int*)(self + 8) + (int)now;
            *timeout = 0;
        }
    }
    return false;
}

// @ 0x00942050
bool HTTPClientFindHeader(int* self, char* name, void* out, int index) {
    int count = (self[1] - *self) / 0xa8;
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (_stricmp(name, *(char**)(*self + i * 0xa8)) == 0) {
            if (found == index) {
                if (out != 0)
                    *(int*)out = *(int*)(i * 0xa8 + *self + 0x54);
                return true;
            }
            found++;
        }
    }
    return false;
}

// @ 0x009420E0
void HTTPClientFindHeaderByField(int field, void* name, void* out) {
    const char* s = HeaderFieldToFieldString(field);
    (void)name;
    (void)out;
    (void)s;
    (void)0;
}

// @ 0x00942110
void HTTPClientSendCallback(int self, const char* data, int len) {
    if (len == -1) {
        const char* p = data;
        do {
        } while (*p++ != 0);
        len = (int)(p - (data + 1));
    }
    if (*(int*)(self + 0x30) > 0) {
        (*(void(__thiscall**)(void*, const char*, int))((char*)*(void**)(self + 0x58) + 0x38))(
            *(void**)(self + 0x58), data, len);
    }
}

// @ 0x00942150
void HTTPClientSetNotificationTarget(int self, void* target, void* ctx) {
    void* old = *(void**)(self + 0x24);
    if (old == target) {
        *(void**)(self + 0x28) = ctx;
        return;
    }
    if (old != 0) {
        typedef void (__cdecl* Fn)(void*, int, unsigned, int, int);
        ((Fn)old)(*(void**)(self + 0x28), self, 0x700af201, 0, 0);
    }
    *(void**)(self + 0x24) = target;
    *(void**)(self + 0x28) = ctx;
    if (target != 0) {
        typedef void (__cdecl* Fn)(void*, int, unsigned, int, int);
        ((Fn)target)(ctx, self, 0x700af200, 0, 0);
    }
}

// @ 0x009421B0  (partial: stream state-machine reconstruction incomplete)
void HTTPClientPump(int self, int* stream) {
    if (stream == 0)
        return;
    int* sub = (int*)(*(int*(__thiscall**)(int*))(*stream + 0x10))(stream);
    if ((*(char(__thiscall**)(int*))(*sub + 0x20))(sub) == 0)
        return;
    (*(void(__thiscall**)(int*, int))(*stream + 0x18))(stream, 1);
    while ((*(int(__thiscall**)(int*))(*stream + 0x2c))(stream) == 2) {
        sub = (int*)(*(int*(__thiscall**)(int*))(*stream + 0x10))(stream);
        if ((*(char(__thiscall**)(int*, int))(*sub + 0x64))(sub, 0) == 0)
            break;
        int n = (*(int(__thiscall**)(int*, int, int, int))(*stream + 0x44))(
            stream, *(int*)(self + 0x140), *(int*)(self + 0x144), 0);
        if (n < 1)
            break;
        const char* buf = *(const char**)(self + 0x140);
        int m = n;
        if (n == -1) {
            const char* p = buf;
            do {
            } while (*p++ != 0);
            m = (int)(p - (buf + 1));
        }
        if (*(int*)(self + 0x30) > 0)
            (*(void(__thiscall**)(void*, const char*, int))((char*)*(void**)(self + 0x54) + 0x38))(
                *(void**)(self + 0x54), buf, m);
        *(uint32_t*)(self + 0x138) += n;
        *(uint32_t*)(self + 0x13c) += (uint32_t)((uint32_t)n > 0xffffffffu - *(uint32_t*)(self + 0x138));
    }
    (*(void(__thiscall**)(int*))(*stream + 0x14))(stream);
}

void* __cdecl operator_new_6(unsigned int, const char*, int, int, int, int);
