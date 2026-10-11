// Slice s0087bdc0: zlib deflate tree helpers (compress_block, build_bl_tree, gen_codes),
// the EA::Gimex import-format stream glue, and small wide-string helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

#include <string.h>
#include <wchar.h>
#include <stdlib.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// Cross-slice / imported helpers.
void* operator_new(int size, const char* name, int a, int b, int c, int d);  // 0xf473a0
void  operator_delete__(void* p);                                            // 0xf47380
__declspec(noinline) bool __stdcall gfree(void* p);
bool  FUN_0087cc80(void* file, char* out, int n);   // 0x0087cc80
void* FUN_0087cd10(const char* name);               // 0x0087cd10
void* FUN_0087cd80(const char* name);               // 0x0087cd80
namespace EA { namespace Text {
    int ConvertEncoding(const wchar_t* src, int count, int enc, char* dst, int* dstLen, int flags); // 0x93c950
} }

// ---------------------------------------------------------------------------
// zlib deflate_state / tree helpers
// ---------------------------------------------------------------------------
struct ct_data { u16 fc; u16 dl; };                 // union {Freq,Code}; union {Dad,Len}
struct tree_desc { ct_data* dyn_tree; int max_code; const void* stat_desc; };

struct deflate_state {
    char pad00[8];
    u8*  pending_buf;              // +0x08
    char pad0c[0x14 - 0x0c];
    u32  pending;                  // +0x14
    char pad18[0x94 - 0x18];
    ct_data dyn_ltree[573];        // +0x94
    ct_data dyn_dtree[61];         // +0x988
    ct_data bl_tree[39];           // +0xa7c
    tree_desc l_desc;              // +0xb18
    tree_desc d_desc;              // +0xb24
    tree_desc bl_desc;             // +0xb30
    char padB3C[0x1698 - 0xb3c];
    u8*  l_buf;                    // +0x1698
    u32  last_lit;                 // +0x16a0
    u16* d_buf;                    // +0x16a4
    u32  opt_len;                  // +0x16a8
    char pad16ac[0x16b8 - 0x16ac];
    u16  bi_buf;                   // +0x16b8
    int  bi_valid;                 // +0x16bc
};

extern const u8  g_01424b88[];   // _length_code  0x1424b88
extern const u8  g_01424988[];   // _dist_code    0x1424988
extern const int g_01424c88[];   // base_length   0x1424c88
extern const int g_01424340[];   // extra_lbits   0x1424340
extern const int g_014243c8[];   // extra_dbits   0x14243c8
extern const int g_01424d00[];   // base_dist     0x1424d00
extern const u8  g_014243a2[];   // bl_order      0x14243a2

void scan_tree(deflate_state* s, ct_data* tree, int max_code);   // 0x0087b570
void build_tree(deflate_state* s, tree_desc* desc);              // 0x0087c4f0

static void put_short(deflate_state* s, u16 w) {
    s->pending_buf[s->pending++] = (u8)w;
    s->pending_buf[s->pending++] = (u8)(w >> 8);
}

static void send_bits(deflate_state* s, int value, int length) {
    if (s->bi_valid > 16 - length) {
        s->bi_buf |= (u16)(value << s->bi_valid);
        put_short(s, s->bi_buf);
        s->bi_buf = (u16)((u32)value >> (16 - s->bi_valid));
        s->bi_valid += length - 16;
    } else {
        s->bi_buf |= (u16)(value << s->bi_valid);
        s->bi_valid += length;
    }
}

static int d_code(unsigned dist) {
    return dist < 256 ? g_01424988[dist] : g_01424988[256 + (dist >> 7)];
}

// @ 0x0087bdc0
void lib_zlib_compress_block(deflate_state* s, const ct_data* ltree, const ct_data* dtree) {
    unsigned dist;
    int lc;
    unsigned lx = 0;
    unsigned code;
    int extra;

    if (s->last_lit != 0) do {
        dist = s->d_buf[lx];
        lc = s->l_buf[lx++];
        if (dist == 0) {
            send_bits(s, ltree[lc].fc, ltree[lc].dl);
        } else {
            code = g_01424b88[lc];
            send_bits(s, ltree[code + 257].fc, ltree[code + 257].dl);
            extra = g_01424340[code];
            if (extra != 0) {
                lc -= g_01424c88[code];
                send_bits(s, lc, extra);
            }
            dist--;
            code = d_code(dist);
            send_bits(s, dtree[code].fc, dtree[code].dl);
            extra = g_014243c8[code];
            if (extra != 0) {
                dist -= g_01424d00[code];
                send_bits(s, dist, extra);
            }
        }
    } while (lx < s->last_lit);
    send_bits(s, ltree[256].fc, ltree[256].dl);
}

static unsigned bi_reverse(unsigned code, int len) {
    unsigned res = 0;
    do {
        res |= code & 1;
        code >>= 1;
        res <<= 1;
    } while (--len > 0);
    return res >> 1;
}

// @ 0x0087c470
void lib_zlib_gen_codes(ct_data* tree, int max_code, u16* bl_count) {
    u16 next_code[16];
    u16 code = 0;
    int bits, n;
    for (bits = 1; bits <= 15; bits++)
        next_code[bits] = code = (u16)((code + bl_count[bits - 1]) << 1);
    for (n = 0; n <= max_code; n++) {
        int len = tree[n].dl;
        if (len == 0) continue;
        tree[n].fc = (u16)bi_reverse(next_code[len]++, len);
    }
}

// @ 0x0087c6f0
void lib_zlib_build_bl_tree(deflate_state* s) {
    int max_blindex;

    scan_tree(s, s->dyn_ltree, s->l_desc.max_code);
    scan_tree(s, s->dyn_dtree, s->d_desc.max_code);
    build_tree(s, &s->bl_desc);
    for (max_blindex = 18; max_blindex >= 3; max_blindex--) {
        if (s->bl_tree[g_014243a2[max_blindex]].dl != 0) break;
    }
    s->opt_len += 3 * (max_blindex + 1) + 5 + 5 + 4;
}

// ---------------------------------------------------------------------------
// Gimex import layers
// ---------------------------------------------------------------------------
void* g_0165039c;   // 0x165039c  list of importer formats
void* g_01650398;   // 0x1650398  list of importer formats (B)

// An importer-format descriptor: [0]=next, [1]=id, [2]=getName fn, [3]=score fn.
struct FmtDesc;

// A reference-counted file object (C++ vtable at offset 0).
struct GzFile {
    void** vtbl;
};

// A C-style table of importer entry points (function pointers accessed directly).
struct FmtTable {
    void* f00; void* f04; void* f08;
    void* f0c; void* f10; void* f14; void* f18; void* f1c;
};

// The Gimex stream wrapper (vtable at offset 0).
struct Stream {
    void** vtbl;   // +0
    void*  file;   // +4
    void*  fmt;    // +8
    int    handle; // +0xc
    u8     open;   // +0x10

    char AttachA(void* p);                        // ce00
    char OpenA(int* pResult);                     // ce60
    bool CloseA();                                // ce90
    int  CallA(int p);                            // ced0
    bool ReadA(int a, int b, int c);              // cf00
    char AttachB(void* p);                        // cf60
    char OpenB(int arg);                          // cfc0
    bool CloseB();                                // cff0
    bool ReadB(int a, int b, int c);              // d030
    bool OpenByIdA(int type, int* pResult);       // d0b0
    char OpenByNameA(const wchar_t* name, int* pResult); // d1c0
    char OpenByIdB(int type, int arg);            // d2a0
    char OpenByNameB(const wchar_t* name, int arg);// d360
    void DestroyA();                              // d070
    void DestroyB();                              // d260
    void* ScalarDeleteA(unsigned flags);          // d400
    void* ScalarDeleteB(unsigned flags);          // d450
};

// vtables
void* g_01424e20[16];   // 0x1424e20  A vtable
void* g_01424e40[16];   // 0x1424e40  B vtable

// @ 0x0087cde0
Stream* __fastcall Stream_CtorA(Stream* self) {
    self->vtbl = g_01424e20;
    self->file = 0;
    self->fmt = 0;
    self->handle = 0;
    self->open = 0;
    return self;
}

// @ 0x0087cf40
Stream* __fastcall Stream_CtorB(Stream* self) {
    self->vtbl = g_01424e40;
    self->file = 0;
    self->fmt = 0;
    self->handle = 0;
    self->open = 0;
    return self;
}

// @ 0x0087ce00
char Stream::AttachA(void* p) {
    if (open) ((int(__thiscall*)(void*))vtbl[7])(this);
    char b = 0;
    if (p) {
        int r = ((int(__thiscall*)(void*))((void**)*(void**)p)[4])(p);
        b = (char)(r & 1);
        if (b) ((void(__thiscall*)(void*))((void**)*(void**)p)[1])(p);
        else p = 0;
    }
    if (file) ((void(__thiscall*)(void*))((void**)*(void**)file)[2])(file);
    file = p;
    return b;
}

// @ 0x0087ce60
char Stream::OpenA(int* pResult) {
    int r;
    r = ((int(__stdcall*)(int*, void*, int, int))((FmtTable*)fmt)->f10)(&handle, file, 0, 1);
    *pResult = r;
    open = (handle != 0);
    return open;
}

// @ 0x0087ce90
bool Stream::CloseA() {
    if (open) {
        if (handle && fmt) ((void(__stdcall*)(int))((FmtTable*)fmt)->f1c)(handle);
        handle = 0;
        open = 0;
        fmt = 0;
    }
    return false;
}

// @ 0x0087ced0
int Stream::CallA(int p) {
    if (fmt) return ((int(__stdcall*)(int, int))((FmtTable*)fmt)->f14)(handle, p);
    return 0;
}

// @ 0x0087cf00
bool Stream::ReadA(int a, int b, int c) {
    if (!open || !fmt) return false;
    int r = ((int(__stdcall*)(int, int, int, int))((FmtTable*)fmt)->f18)(handle, a, b, c);
    return r != 0;
}

// @ 0x0087cf60
char Stream::AttachB(void* p) {
    if (open) ((int(__thiscall*)(void*))vtbl[5])(this);
    char b = 0;
    if (p) {
        unsigned r = ((unsigned(__thiscall*)(void*))((void**)*(void**)p)[4])(p);
        b = (char)((r >> 1) & 1);
        if (b) ((void(__thiscall*)(void*))((void**)*(void**)p)[1])(p);
        else p = 0;
    }
    if (file) ((void(__thiscall*)(void*))((void**)*(void**)file)[2])(file);
    file = p;
    return b;
}

// @ 0x0087cfc0
char Stream::OpenB(int arg) {
    if (fmt) {
        int r = ((int(__stdcall*)(int*, void*, int, int))((FmtTable*)fmt)->f0c)(&handle, file, 0, arg);
        open = (r != 0);
    }
    return open;
}

// @ 0x0087cff0
bool Stream::CloseB() {
    bool r = false;
    if (open) {
        if (handle && fmt)
            r = ((int(__thiscall*)(void*, int))((FmtTable*)fmt)->f14)((void*)handle, handle) != 0;
        fmt = 0;
        handle = 0;
        open = 0;
    }
    return r;
}

// @ 0x0087d030
bool Stream::ReadB(int a, int b, int c) {
    if (open && fmt) {
        int r = ((int(__stdcall*)(int, int, int, int))((FmtTable*)fmt)->f10)(handle, a, b, c);
        return r != 0;
    }
    return false;
}

// @ 0x0087d070
void Stream::DestroyA() {
    vtbl = g_01424e20;
    if (file) {
        if (open) ((int(__thiscall*)(void*))vtbl[7])(this);
        if (file) ((void(__thiscall*)(void*))((void**)*(void**)file)[2])(file);
        file = 0;
    }
}

// @ 0x0087d260
void Stream::DestroyB() {
    vtbl = g_01424e40;
    if (file) {
        if (open) ((int(__thiscall*)(void*))vtbl[5])(this);
        if (file) ((void(__thiscall*)(void*))((void**)*(void**)file)[2])(file);
        file = 0;
    }
}

// @ 0x0087d400
void* Stream::ScalarDeleteA(unsigned flags) {
    vtbl = g_01424e20;
    if (file) {
        if (open) ((int(__thiscall*)(void*))vtbl[7])(this);
        if (file) ((void(__thiscall*)(void*))((void**)*(void**)file)[2])(file);
        file = 0;
    }
    if (flags & 1) operator_delete__(this);
    return this;
}

// @ 0x0087d450
void* Stream::ScalarDeleteB(unsigned flags) {
    vtbl = g_01424e40;
    if (file) {
        if (open) ((int(__thiscall*)(void*))vtbl[5])(this);
        if (file) ((void(__thiscall*)(void*))((void**)*(void**)file)[2])(file);
        file = 0;
    }
    if (flags & 1) operator_delete__(this);
    return this;
}

// @ 0x0087d0b0
bool Stream::OpenByIdA(int type, int* pResult) {
    if (open || !file) return false;
    if (type != 0x34 && type != 0x32 && type != 0x33) {
        for (void** e = (void**)g_0165039c; e; e = (void**)*e)
            if (e[1] == (void*)type) fmt = e;
        goto L170;
    }
    {
        void* found = 0;
        int best;
        if ((type == 0x33 || type == 0x34)) {
            u8 tmp[8];
            if (FUN_0087cc80(file, (char*)tmp, 8)) {
                found = FUN_0087cd10((char*)tmp);
                if (found) goto L16b;
            }
        }
        if (type == 0x32 || type == 0x34) {
            best = 0;
            for (void** e = (void**)g_0165039c; e; e = (void**)*e) {
                int r = ((int(__stdcall*)(void*))e[3])(file);
                if (r > best) { best = r; found = e; }
            }
            if (!found) goto L170;
        }
    L16b:
        fmt = found;
    }
L170:
    if (fmt) {
        int r = ((int(__stdcall*)(int*, void*, int, int))((FmtTable*)fmt)->f10)(&handle, file, 0, 1);
        *pResult = r;
        open = (handle != 0);
        return open;
    }
    return false;
}

// @ 0x0087d2a0
char Stream::OpenByIdB(int type, int arg) {
    if (open || !file) return false;
    if (type == 0x34 || type == 0x32) {
        if (type == 0x33 || type == 0x34) goto L2f1;
    } else {
        if (type != 0x33) {
            for (void** e = (void**)g_01650398; e; e = (void**)*e)
                if (e[1] == (void*)type) fmt = e;
            goto L31b;
        }
    L2f1:
        {
            u8 tmp[8];
            if (FUN_0087cc80(file, (char*)tmp, 8))
                fmt = FUN_0087cd80((char*)tmp);
        }
    }
    if (fmt == 0) return false;
L31b:
    if (fmt != 0) {
        int r = ((int(__stdcall*)(int*, void*, int, int))((FmtTable*)fmt)->f0c)(&handle, file, 0, arg);
        open = (r != 0);
    }
    return open;
}

// @ 0x0087d1c0
char Stream::OpenByNameA(const wchar_t* name, int* pResult) {
    if (open || !file) return 0;
    if (*name == L'.') name++;
    int n = 0x104;
    const wchar_t* p = name;
    wchar_t c;
    do { c = *p; p++; } while (c != 0);
    char buf[0x104];
    EA::Text::ConvertEncoding(name, (int)(p - (name + 1)), 0x10, buf, &n, 4);
    void* f = FUN_0087cd10(buf);
    if (!f) return 0;
    fmt = f;
    return OpenA(pResult);
}

// @ 0x0087d360
char Stream::OpenByNameB(const wchar_t* name, int arg) {
    if (open || !file) return 0;
    if (*name == L'.') name++;
    int n = 0x104;
    const wchar_t* p = name;
    wchar_t c;
    do { c = *p; p++; } while (c != 0);
    char buf[0x104];
    EA::Text::ConvertEncoding(name, (int)(p - (name + 1)), 0x10, buf, &n, 4);
    void* f = FUN_0087cd80(buf);
    if (!f) return 0;
    fmt = f;
    return OpenB(arg);
}

// @ 0x0087cc80
bool FUN_0087cc80(void* file, char* out, int n) {
    if (file) {
        if (((int(__thiscall*)(void*))((void**)*(void**)file)[3])(file) == 0x34722300) {
            char buf[0x104];
            if (((int(__thiscall*)(void*, char*, int))((void**)*(void**)file)[18])(file, buf, 0x104)) {
                char* dot = strrchr(buf, '.');
                if (dot) {
                    strncpy(out, dot + 1, n);
                    out[n - 1] = 0;
                    return out[0] != 0;
                }
            }
        }
    }
    return false;
}

// @ 0x0087cd10
void* FUN_0087cd10(const char* name) {
    for (void** e = (void**)g_0165039c; e; e = (void**)*e) {
        int p = ((int(__stdcall*)())e[2])();
        if (p) {
            int i = 0;
            char* s = (char*)(p + 0x3c);
            while (i < 8) {
                const char* s2 = s;
                if (*s == '.') s2 = s + 1;
                if (_stricmp(name, s2) == 0) {
                    gfree((void*)p);
                    return e;
                }
                i++;
                s += 8;
            }
            gfree((void*)p);
        }
    }
    return 0;
}

// @ 0x0087cd80
void* FUN_0087cd80(const char* name) {
    for (void** e = (void**)g_01650398; e; e = (void**)*e) {
        int p = ((int(__stdcall*)())e[2])();
        if (p) {
            int i = 0;
            char* s = (char*)(p + 0x3c);
            while (i < 8) {
                if (_stricmp(name, s) == 0) {
                    gfree((void*)p);
                    return e;
                }
                i++;
                s += 8;
            }
            gfree((void*)p);
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Gimex file callbacks
// ---------------------------------------------------------------------------

// @ 0x0087d4a0
void* __stdcall galloc(int size) {
    return operator_new(size, "UTF/Gimex", 0, 0, 0, 0);
}

// @ 0x0087d4c0
bool __stdcall gfree(void* p) {
    operator_delete__(p);
    return true;
}

// @ 0x0087d4e0
int __stdcall gread(void* f, void* buf, int len) {
    if (len < 0) return 0;
    return ((int(__thiscall*)(void*, void*, int))((void**)*(void**)f)[12])(f, buf, len);
}

// @ 0x0087d510
unsigned __stdcall gwrite(void* f, void* buf, unsigned len) {
    if ((int)len < 0) return 0;
    unsigned char r = (unsigned char)((int(__thiscall*)(void*, void*, unsigned))((void**)*(void**)f)[14])(f, buf, len);
    return (r != 0) ? len : 0;
}

// @ 0x0087d540
void __stdcall gseek(void* f, int offset, int origin) {
    (void)origin;
    ((void(__thiscall*)(void*, int, int))((void**)*(void**)f)[10])(f, offset, 0);
}

// @ 0x0087d560
unsigned long long __stdcall glen(void* f) {
    unsigned int r = ((unsigned int(__thiscall*)(void*))((void**)*(void**)f)[7])(f);
    return r;
}

// @ 0x0087d570
long long __stdcall gtell(void* f) {
    return ((int(__thiscall*)(void*, int))((void**)*(void**)f)[9])(f, 0);
}

// @ 0x0087d590
void EA_Gimex_AddImportFormat(void* p) {
    *(void**)p = g_0165039c;
    g_0165039c = p;
}

// @ 0x0087d5b0
void FUN_0087d5b0(void* p) {
    *(void**)p = g_01650398;
    g_01650398 = p;
}

// @ 0x0087d5d0
int FUN_0087d5d0(wchar_t* dst, int n, const wchar_t* src, const wchar_t* srcEnd) {
    wchar_t* end = dst + n - 1;
    const wchar_t* s = src;
    if (s < srcEnd) {
        do {
            if (dst < end) {
                *dst = *s;
                dst++;
            }
            s++;
        } while (s < srcEnd);
    }
    *dst = 0;
    return (int)(srcEnd - src);
}

// @ 0x0087d620
int FUN_0087d620(int limit, const wchar_t* str, wchar_t* dst, int cap, wchar_t sep) {
    int i = 0;
    short sVar3;
    short* psVar4 = (short*)str - 1;
    short* psVar1 = 0;
    do {
        sVar3 = psVar4[1];
        psVar1 = psVar4 + 1;
        psVar4 = psVar1;
        while (sVar3 != 0 && sVar3 != (short)sep) {
            short* psVar2 = psVar4 + 1;
            psVar4 = psVar4 + 1;
            sVar3 = *psVar2;
        }
        i++;
    } while (*psVar4 != 0 && i <= limit);
    i--;
    if (i != limit) return -1;
    return FUN_0087d5d0(dst, cap, (const wchar_t*)psVar1, (const wchar_t*)psVar4);
}

// @ 0x0087d690
int FUN_0087d690(int limit, const wchar_t* str, wchar_t sep) {
    wchar_t buf[128];
    FUN_0087d620(limit, str, buf, 0x80, sep);
    return (int)wcstol(buf, 0, 10);
}
