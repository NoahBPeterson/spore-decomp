// EA::Locale helpers from Slice s0087e510.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

// --- external runtime / engine entry points (calls are relocation-masked) ---
extern "C" int        iswctype(int, int);
extern "C" wchar_t*   wcsncpy(wchar_t*, const wchar_t*, unsigned int);
extern "C" wchar_t*   _wcslwr(wchar_t*);
void operator_delete__(void*);

// LocaleFormatter::AppendElement(this, begin, end) lives at 0x68cc10.
// It is a thiscall with `this` in ecx and two stack args; declared but not
// defined here, exactly like the real out-of-line member.
template <int N>
struct LocT {
    wchar_t* f00;
    wchar_t* f04;
    wchar_t* f08;
    int      f0C;
    wchar_t* f10;
    wchar_t  buf[N];
    void AppendElement(const wchar_t* begin, const wchar_t* end);
};

typedef LocT<16>  Loc16;
typedef LocT<512> Loc512;

// The 0x112c-byte language-prefix object built by FUN_0087e510 / torn down by
// FUN_0087e8f0: 22 small string members, one small member with 16 trailing
// padding bytes, then three 512-wchar members.
struct LangPrefixObj {
    Loc16 m0,  m1,  m2,  m3,  m4,  m5,  m6,  m7;
    Loc16 m8,  m9,  m10, m11, m12, m13, m14, m15;
    Loc16 m16, m17, m18, m19, m20, m21;
    Loc16 m22; char pad22[0x10];
    Loc16 m23;
    Loc512 m24, m25, m26;
};

// A smaller language-format object built by FUN_0087f100: three 512-wchar
// string members followed by four 16-wchar members after a leading dword.
struct LocaleFormatObj {
    int    f0;
    Loc512 big[3];
    Loc16  small[4];
};

// --- globals referenced by the 2-char language fallbacks ---
extern wchar_t* g_01549118;
extern wchar_t* g_0154911c;
extern wchar_t* g_0154914c;
extern wchar_t* g_01549150;

// @ 0x0087e510
void __fastcall FUN_0087e510(LangPrefixObj* self) {
    wchar_t* b;
#define INIT16(m) do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 16; b[0] = 0; } while (0)
#define INIT512(m) do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 512; b[0] = 0; } while (0)
    INIT16(self->m0);  INIT16(self->m1);  INIT16(self->m2);  INIT16(self->m3);
    INIT16(self->m4);  INIT16(self->m5);  INIT16(self->m6);  INIT16(self->m7);
    INIT16(self->m8);  INIT16(self->m9);  INIT16(self->m10); INIT16(self->m11);
    INIT16(self->m12); INIT16(self->m13); INIT16(self->m14); INIT16(self->m15);
    INIT16(self->m16); INIT16(self->m17); INIT16(self->m18); INIT16(self->m19);
    INIT16(self->m20); INIT16(self->m21); INIT16(self->m22); INIT16(self->m23);
    INIT512(self->m24); INIT512(self->m25); INIT512(self->m26);
#undef INIT16
#undef INIT512
}

// @ 0x0087e8f0
void __fastcall FUN_0087e8f0(LangPrefixObj* self) {
#define DESTROY(m) do { wchar_t* s = (m).f00; int d = (int)((char*)(m).f08 - (char*)s); \
        if (2 < (d & -2) && s != 0 && s != (m).f10) operator_delete__(s); } while (0)
    DESTROY(self->m26); DESTROY(self->m25); DESTROY(self->m24);
    DESTROY(self->m23); DESTROY(self->m22);
    DESTROY(self->m21); DESTROY(self->m20); DESTROY(self->m19); DESTROY(self->m18);
    DESTROY(self->m17); DESTROY(self->m16); DESTROY(self->m15); DESTROY(self->m14);
    DESTROY(self->m13); DESTROY(self->m12); DESTROY(self->m11); DESTROY(self->m10);
    DESTROY(self->m9);  DESTROY(self->m8);  DESTROY(self->m7);  DESTROY(self->m6);
    DESTROY(self->m5);  DESTROY(self->m4);  DESTROY(self->m3);  DESTROY(self->m2);
    DESTROY(self->m1);  DESTROY(self->m0);
#undef DESTROY
}

// @ 0x0087f100
void __fastcall FUN_0087f100(LocaleFormatObj* self) {
    wchar_t* b;
#define INIT16(m)  do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 16;  b[0] = 0; } while (0)
#define INIT512(m) do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 512; b[0] = 0; } while (0)
    INIT512(self->big[0]);
    INIT512(self->big[1]);
    INIT512(self->big[2]);
    INIT16(self->small[0]);
    INIT16(self->small[1]);
    INIT16(self->small[2]);
    INIT16(self->small[3]);
#undef INIT16
#undef INIT512
}

// @ 0x0087ed70
void* FUN_0087ed70(Loc16* dst, int* src) {
    int iVar2 = src[0];
    int iVar3 = src[1];
    wchar_t* p = dst->buf;
    dst->f10 = p;
    dst->f04 = p;
    dst->f00 = p;
    if ((unsigned)((iVar3 - iVar2) >> 1) >= 2) {
        dst->f08 = p + 16;
        *p = 0;
        dst->AppendElement((const wchar_t*)iVar2, (const wchar_t*)(iVar2 + 4));
        return dst;
    }
    dst->f08 = p + 16;
    *p = 0;
    dst->AppendElement(g_01549118, g_0154911c);
    return dst;
}

// @ 0x0087edd0
void* FUN_0087edd0(Loc16* dst, int* src) {
    int begin = src[0];
    unsigned len = (unsigned)((src[1] - begin) >> 1);
    wchar_t* p;
    if (len >= 5) {
        p = dst->buf;
        dst->f10 = p;
        begin += 6;
        dst->f04 = p;
        dst->f00 = p;
    } else {
        p = dst->buf;
        dst->f10 = p;
        dst->f04 = p;
        dst->f00 = p;
        if (len < 2) {
            dst->f08 = p + 16;
            *p = 0;
            dst->AppendElement(g_0154914c, g_01549150);
            return dst;
        }
    }
    dst->f08 = p + 16;
    *p = 0;
    dst->AppendElement((const wchar_t*)begin, (const wchar_t*)(begin + 4));
    return dst;
}

// @ 0x0087f210
void* FUN_0087f210(Loc16* dst, const wchar_t* src) {
    wchar_t buf[6] = {0};
    const wchar_t* p = src;
    wchar_t c;
    do { c = *p; p++; } while (c != 0);
    unsigned count = (unsigned)((int)p - (int)(src + 1)) >> 1;
    if (count != 0) {
        if (count == 2 || count == 5) {
            wcsncpy(buf, src, count);
            buf[count] = 0;
        } else if (count > 2) {
            if (src[2] == L'-') {
                if (count > 4 && iswctype(src[3], 0x103) != 0 &&
                    iswctype(src[4], 0x103) != 0) {
                    wcsncpy(buf, src, 5);
                    buf[5] = 0;
                }
            } else {
                wcsncpy(buf, src, 2);
                buf[2] = 0;
            }
        }
    }
    if (buf[0] != 0) _wcslwr(buf);
    wchar_t* b = dst->buf;
    dst->f10 = b;
    dst->f04 = b;
    dst->f00 = b;
    dst->f08 = b + 16;
    *b = 0;
    const wchar_t* q = buf;
    while (*q != 0) q++;
    dst->AppendElement(buf, q);
    return dst;
}

// @ 0x0087f350
void* FUN_0087f350(Loc16* dst, wchar_t** src) {
    FUN_0087f210(dst, *src);
    return dst;
}

// --- eastl rbtree lookup used by GetClosestLanguageId ---
struct RbtIter { void* node; };
struct RbtTree { RbtIter find(int* key); };  // out-of-line, at 0x5e96f0
struct RbtNodeHeader { void* f00; void* f04; void* f08; void* f0C; void* f10; void* f14; };

extern RbtTree g_rbtree_01549180;             // tree object
extern char    g_sentinel_01549184[];         // end() sentinel node
extern void*   g_root_01549188;               // root node pointer
extern "C" void* RBTreeIncrement(void*);      // eastl::RBTreeIncrement

// @ 0x0087ee50  (EA::Locale::GetClosestLanguageId)
namespace EA { namespace Locale {
void* GetClosestLanguageId(void* dst_, int* key) {
    Loc16* dst = (Loc16*)dst_;
    wchar_t empty[16];
    empty[0] = 0;
    RbtIter it = g_rbtree_01549180.find(key);
    if (it.node == (void*)g_sentinel_01549184) {
        if (((key[1] - key[0]) & -2) == 4) {
            wchar_t* b = dst->buf;
            dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
            dst->AppendElement((const wchar_t*)key[0], (const wchar_t*)key[1]);
        } else {
            Loc16 tmp;
            FUN_0087ed70(&tmp, key);
            void* node = g_root_01549188;
            while (node != (void*)g_sentinel_01549184) {
                Loc16 s;
                wchar_t* sb = s.buf;
                s.f10 = sb; s.f04 = sb; s.f00 = sb; s.f08 = sb + 16; *sb = 0;
                s.AppendElement((const wchar_t*)((void**)node)[4], (const wchar_t*)((void**)node)[5]);
                if (s.buf[0] == ((wchar_t*)tmp.f00)[0] && s.buf[1] == ((wchar_t*)tmp.f00)[1]) {
                    { int d=(int)((char*)s.f08-(char*)s.f00); if (2<(d&-2)&&s.f00&&s.f00!=s.f10) operator_delete__(s.f00); }
                    if (node != (void*)g_sentinel_01549184) {
                        wchar_t* b = dst->buf;
                        dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
                        dst->AppendElement((const wchar_t*)((void**)node)[4], (const wchar_t*)((void**)node)[5]);
                        { int d=(int)((char*)tmp.f08-(char*)tmp.f00); if (2<(d&-2)&&tmp.f00&&tmp.f00!=tmp.f10) operator_delete__(tmp.f00); }
                        return dst;
                    }
                    break;
                }
                { int d=(int)((char*)s.f08-(char*)s.f00); if (2<(d&-2)&&s.f00&&s.f00!=s.f10) operator_delete__(s.f00); }
                node = RBTreeIncrement(node);
            }
            wchar_t* b = dst->buf;
            dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
            dst->AppendElement(empty, empty);
            { int d=(int)((char*)tmp.f08-(char*)tmp.f00); if (2<(d&-2)&&tmp.f00&&tmp.f00!=tmp.f10) operator_delete__(tmp.f00); }
        }
    } else {
        wchar_t* b = dst->buf;
        dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
        dst->AppendElement((const wchar_t*)key[0], (const wchar_t*)key[1]);
    }
    return dst;
}
}}
