// Slice s008387c0 (w2g7 #41), 32-bit MSVC 2008 SP1.
// EA::ArgScript argument spec + eastl string/vector copy helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"
#include <string.h>

void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);                          // 0x00f47380
void  __cdecl DoInsertValue(char*, const char*, uint32_t);   // 0x11e0744
void  __cdecl RangeInitRaw(void*, uint32_t);                 // 0x475ab0
char* __cdecl SearchStr(void*, void*, void*, void*);         // 0x609d50
template <typename T> static const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }

// ---------------------------------------------------------------------------
// eastl::basic_string<char>
// ---------------------------------------------------------------------------
struct RawStr {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;

    void RangeInitialize(uint32_t n);                 // 0x475ab0
    void Assign(const char* first, const char* last); // 0x454cb0
    RawStr() {}
    RawStr(const RawStr& s, uint32_t pos, uint32_t n); // 0x8389f0
    int  Find(const char* p, uint32_t pos);           // 0x838a60
    void AssignSub(const RawStr& s, uint32_t pos, uint32_t n); // 0x838de0
    RawStr* CopyCtor(const RawStr& s);                // 0x57cb10
    void AppendRange(const char* first, const char* last); // 0x455d60
    void Erase(uint32_t pos, uint32_t n);             // 0x61e200
    RawStr* AppendStr(const char* s);                 // 0x60c4e0
};

// @ 0x008389f0
RawStr::RawStr(const RawStr& s, uint32_t pos, uint32_t n) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    uint32_t rem = (uint32_t)(s.mpEnd - s.mpBegin) - pos;
    const uint32_t& cnt = min_alt(rem, n);
    char* src = s.mpBegin + pos;
    char* end = src + cnt;
    uint32_t len = (uint32_t)(end - src);
    RangeInitialize(len + 1);
    char* dst = mpBegin;
    DoInsertValue(dst, src, len);
    mpEnd = dst + len;
    *mpEnd = 0;
}

// @ 0x00838a60
int RawStr::Find(const char* p, uint32_t pos) {
    const char* e = p;
    while (*e) ++e;
    char* begin = mpBegin;
    char* end = mpEnd;
    if (pos < (uint32_t)(end - begin)) {
        char* r = SearchStr(begin + pos, end, (void*)p, (void*)e);
        if (r != end) return (int)(r - begin);
    }
    return -1;
}

// ---------------------------------------------------------------------------
// structured element types
// ---------------------------------------------------------------------------
struct Ent {                 // 0x20 bytes
    int    field0;           // +0
    RawStr name;             // +4
    int    field14;          // +0x14
    bool   field18;          // +0x18
    char   pad[3];
    int    field1c;          // +0x1c
    Ent* CopyFrom(const Ent* src);
};

struct Ent2 {                // 0x18 bytes
    RawStr name;             // +0
    int    field10;          // +0x10
    int    field14;          // +0x14
};

struct Vec2 {
    float x, y;
    Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; }
};

// @ 0x00838ab0
Ent* Ent::CopyFrom(const Ent* src) {
    Ent* dst = this;
    dst->field0 = src->field0;
    dst->name.mpBegin = 0;
    dst->name.mpEnd = 0;
    dst->name.mpCapacity = 0;
    uint32_t size = (uint32_t)(src->name.mpEnd - src->name.mpBegin);
    dst->name.RangeInitialize(size + 1);
    char* dstp = dst->name.mpBegin;
    DoInsertValue(dstp, src->name.mpBegin, size);
    dst->name.mpEnd = dstp + (src->name.mpEnd - src->name.mpBegin);
    *dst->name.mpEnd = 0;
    dst->field14 = src->field14;
    dst->field18 = src->field18;
    dst->field1c = src->field1c;
    return dst;
}

// @ 0x00838b90
Vec2* CopyVec2(Vec2* first, Vec2* last, Vec2* dst) {
    if (first != last) {
        int off = (int)((char*)first - (char*)dst);
        do {
            if (dst) *dst = *(Vec2*)(off + (char*)dst);
            ++dst;
        } while ((Vec2*)(off + (char*)dst) != last);
    }
    return dst;
}

// @ 0x00838e80
Ent* DestroyEnts(Ent* first, Ent* last, Ent* dst) {
    if (first != last) {
        do {
            char* b = first->name.mpBegin;
            if ((first->name.mpCapacity - b) > 1 && b) operator_delete__(b);
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}

// @ 0x00838f20
Ent* CopyEntsFwd(Ent* first, Ent* last, Ent* dst) {
    if (first != last) {
        do {
            dst->field0 = first->field0;
            if (&first->name != &dst->name) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field14 = first->field14;
            dst->field18 = first->field18;
            dst->field1c = first->field1c;
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}

// @ 0x00838f80
Ent* CopyEntsBwd(Ent* first, Ent* last, Ent* dst) {
    if (first != last) {
        do {
            first -= 1;
            dst -= 1;
            dst->field0 = first->field0;
            if (&first->name != &dst->name) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field14 = first->field14;
            dst->field18 = first->field18;
            dst->field1c = first->field1c;
        } while (first != last);
    }
    return dst;
}

// @ 0x00838ff0
Ent2* CopyEnts2Fwd(Ent2* first, Ent2* last, Ent2* dst) {
    if (first != last) {
        do {
            if (first != dst) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field10 = first->field10;
            dst->field14 = first->field14;
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}

// @ 0x00839040
Ent2* CopyEnts2Bwd(Ent2* first, Ent2* last, Ent2* dst) {
    if (first != last) {
        do {
            first -= 1;
            dst -= 1;
            if (first != dst) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field10 = first->field10;
            dst->field14 = first->field14;
        } while (first != last);
    }
    return dst;
}

// @ 0x00838de0  (assign sub-range of s into this)
void RawStr::AssignSub(const RawStr& s, uint32_t pos, uint32_t n) {
    char* begin = s.mpBegin;
    uint32_t rem = (uint32_t)(s.mpEnd - begin) - pos;
    const uint32_t& cnt = min_alt(rem, n);
    Assign(begin + pos, begin + pos + cnt);
}

// ---------------------------------------------------------------------------
// complex / partial bodies
// ---------------------------------------------------------------------------
bool __cdecl StrEqualI(const char*, const char*);                    // 0x838760
bool __cdecl StrNEqualI(const char*, const char*, unsigned int);     // 0x838780
bool __cdecl StrEqualI2(const char**, const char*);                  // 0x8387a0

struct ArgumentSpec {        // EA::ArgScript::cArgumentSpec (retail layout, 0xb0)
    char  pad0[0x58];
    Ent2* mEnumBegin;        // +0x58
    Ent2* mEnumEnd;          // +0x5c
    unsigned int ArgTypeFromName(const char* name);   // 0x8387c0
    void NameFromArgType(unsigned int type, RawStr* out);   // 0x8397a0
    void FindNameAndTypeFromOption(RawStr* option, unsigned int* typeOut, RawStr* nameOut);   // 0x839540
};

// @ 0x008387c0
unsigned int ArgumentSpec::ArgTypeFromName(const char* name) {
    unsigned int flags = 0;
    unsigned int len = (unsigned int)strlen(name);
    if (len > 2 && name[len - 2] == '[' && name[len - 1] == ']') {
        flags = 0x4000;
        len -= 2;
    }
    if (_strnicmp(name, "bool", len) == 0) return flags | 1;
    if (_strnicmp(name, "int", len) == 0) return flags | 2;
    if (_strnicmp(name, "float", len) == 0) return flags | 3;
    if (_strnicmp(name, "double", len) == 0) return flags | 4;
    if (_strnicmp(name, "string", len) == 0) return flags | 6;
    if (StrNEqualI(name, "cstr", len) || StrNEqualI(name, "cstring", len)) return flags | 5;
    if (StrNEqualI(name, "vector2", len)) return flags | 7;
    if (StrNEqualI(name, "vector3", len)) return flags | 8;
    if (StrNEqualI(name, "vector4", len)) return flags | 9;
    if (StrEqualI(name, "colorRGB, typeLen")) return flags | 10;
    if (StrNEqualI(name, "colorRGBA", len)) return flags | 11;
    for (unsigned int i = 0; i < (unsigned int)(mEnumEnd - mEnumBegin); ++i) {
        if (StrEqualI2((const char**)&mEnumBegin[i], name)) return (i + 12) | flags;
    }
    return 0;
}
extern char gEmptyString[];   // 0x1667bac
inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}
// eastl::allocator::allocate (operator_new6 args: size, name, 0, 0, file, line)
void* __cdecl AllocArgScript(uint32_t, const char*, int, int, const char*, int); // 0xf473a0

struct StrPOD { char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator; };
struct Ent2C {               // Ent2 with copy-ctor / dtor (0x18 bytes)
    StrPOD name;
    int    field10;
    int    field14;
    __forceinline Ent2C(const Ent2C& o) {
        name.mpBegin = 0; name.mpEnd = 0; name.mpCapacity = 0;
        char* last = o.name.mpEnd;
        char* first = o.name.mpBegin;
        uint32_t n = (uint32_t)(last - first);
        uint32_t cap = n + 1;
        if (cap > 1) {
            char* p = (char*)AllocArgScript(cap, "ArgScript", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            name.mpBegin = p; name.mpEnd = p; name.mpCapacity = p + cap;
        } else {
            name.mpBegin = gEmptyString; name.mpEnd = gEmptyString; name.mpCapacity = gEmptyString + 1;
        }
        char* dst = name.mpBegin;
        DoInsertValue(dst, first, n);
        name.mpEnd = dst + (last - first);
        *name.mpEnd = 0;
        field10 = o.field10;
        field14 = o.field14;
    }
    ~Ent2C() {
        char* b = name.mpBegin;
        if ((name.mpCapacity - b) > 1 && b) operator_delete__(b);
    }
};

// @ 0x00838cd0
Ent2C* UninitCopyEnts2(Ent2C* first, Ent2C* last, Ent2C* dest) {
    for (; first != last; ++first, ++dest)
        ::new (dest) Ent2C(*first);
    return dest;
}
extern char gStrG[];                                                  // 0x13ec47c
char* __cdecl FindFirstOf(char*, char*, const char*, const char*);   // 0x609d50

struct LocalStr : RawStr {
    __forceinline void AllocateSelf(uint32_t n) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        char* d;
        if (n > 1) {
            d = (char*)AllocArgScript(n, "ArgScript", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            mpCapacity = d + n;
        } else {
            d = gEmptyString;
            mpCapacity = gEmptyString + 1;
        }
        mpBegin = d;
        mpEnd = d;
    }
    __forceinline LocalStr(const RawStr* src) {
        char* last = src->mpEnd;
        char* first = src->mpBegin;
        uint32_t n = (uint32_t)(last - first);
        AllocateSelf(n + 1);
        char* d = mpBegin;
        DoInsertValue(d, first, n);
        mpEnd = d + (last - first);
        *mpEnd = 0;
    }
    ~LocalStr() {
        char* b = mpBegin;
        if ((mpCapacity - b) > 1 && b) operator_delete__(b);
    }
    LocalStr substr(uint32_t pos, uint32_t n) const;   // 0x6082a0
    LocalStr() {}
    LocalStr& operator=(const RawStr& x) {
        if (&x != this) Assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};
void __cdecl SprintfAppend(RawStr* dst, const char* fmt, ...);       // 0x840c70

// @ 0x00839090  (cFileParser::AddFilePath: split the first token (delimited by any char of delims) off *path)
RawStr* AddFilePath(RawStr* out, RawStr* path, const char* delims) {
    uint32_t one = 0;
    LocalStr L(path);

    path->Assign(gStrG, gStrG);
    if (delims) {
        if (strlen(delims) != 0) {
            int pos = L.Find(delims, 0);
            if (pos == 0) {
                one = 1;
                do {
                    char* b = L.mpBegin;
                    char* en = L.mpEnd;
                    uint32_t sz = (uint32_t)(en - b);
                    const uint32_t& cnt = (sz < one) ? sz : one;
                    char* p = b + cnt;
                    if (b != p) {
                        memmove(b, p, en - p + 1);
                        L.mpEnd += b - p;
                    }
                    b = L.mpBegin;
                    en = L.mpEnd;
                    const char* dl = delims + strlen(delims);
                    if (en - b == 0) {
                        pos = -1;
                    } else {
                        char* r = FindFirstOf(b, en, delims, dl);
                        pos = (r == en) ? -1 : (int)(r - b);
                    }
                } while (pos == 0);
            }
            if (pos != -1) {
                path->AssignSub(L, pos + 1, (uint32_t)-1);
                L.AssignSub(L, 0, pos);
            }
            out->CopyCtor(L);
            goto done;
        }
    }
    out->mpBegin = 0; out->mpEnd = 0; out->mpCapacity = 0;
    char* lb = L.mpBegin;
    char* le = L.mpEnd;
    out->RangeInitialize((uint32_t)(le - lb) + 1);
    char* od = out->mpBegin;
    DoInsertValue(od, lb, (uint32_t)(le - lb));
    out->mpEnd = od + (le - lb);
    *out->mpEnd = 0;
done:
    return out;
}
// @ 0x008392b0  (anonymous namespace)::AddDocString: append each line of s to out as "<prefix><line>\n"
void AddDocString(RawStr* out, const char* prefix, LocalStr s) {
    uint32_t pos = 0;
    for (;;) {
        int idx;
        if (pos < (uint32_t)(s.mpEnd - s.mpBegin)) {
            for (char* p = s.mpBegin + pos; p != s.mpEnd; ++p) {
                if (*p == '\n') {
                    if (p != s.mpEnd) {
                        idx = (int)(p - s.mpBegin);
                        goto found;
                    }
                    break;
                }
            }
        }
        idx = -1;
    found:
        SprintfAppend(out, "%s%s\n", prefix, s.substr(pos, idx - pos).mpBegin);
        pos = idx + 1;
        if (idx == -1) return;
    }
}
extern char gDocSep[];   // 0x1401b70 (1-char separator)

struct EnumVal1 { const char* name; int x; };                       // stride 8
struct EnumVal2 { const char* name; int x; const char* desc; };     // stride 0xc
struct EnumSpec {            // EA::ArgScript::cEnumSpec (0x18)
    const char* name;        // +0
    char        pad[0xc];
    EnumVal1*   vals;        // +0x10
    EnumVal2*   descVals;    // +0x14
};
struct EnumVec { EnumSpec* mpBegin; EnumSpec* mpEnd; };

// @ 0x008393a0  (anonymous namespace)::AddEnumDocs
void AddEnumDocs(RawStr* out, const char* prefix, EnumVec* v, int mode) {
    out->AppendRange(gDocSep, gDocSep + 1);
    for (uint32_t i = 0; i < (uint32_t)(v->mpEnd - v->mpBegin); ++i) {
        if (v->mpBegin[i].vals != 0) {
            if (mode == 2) SprintfAppend(out, "<p><b>%s</b></p><blockquote><i>", v->mpBegin[i].name);
            else SprintfAppend(out, "%s%s:\n", prefix, v->mpBegin[i].name);
            for (EnumVal1* p = v->mpBegin[i].vals; p->name; ++p) {
                if (mode == 2) SprintfAppend(out, "%s</br>\n", p->name);
                else SprintfAppend(out, "%s   %s\n", prefix, p->name);
            }
        } else {
            if (mode == 2) SprintfAppend(out, "<p><b>%s</b></p><blockquote><i>", v->mpBegin[i].name);
            else SprintfAppend(out, "%s%s:\n", prefix, v->mpBegin[i].name);
            for (EnumVal2* p = v->mpBegin[i].descVals; p->name; ++p) {
                if (mode == 2) SprintfAppend(out, "%s: %s</br>\n", p->name, p->desc);
                else SprintfAppend(out, "%s   %s: %s\n", prefix, p->name, p->desc);
            }
        }
        if (mode == 2) SprintfAppend(out, "</i></blockquote>");
    }
}
struct TmpStr : RawStr {
    TmpStr(const RawStr& s, uint32_t pos, uint32_t n) : RawStr(s, pos, n) {}
    ~TmpStr() {
        char* b = mpBegin;
        if ((mpCapacity - b) > 1 && b) operator_delete__(b);
    }
};

// @ 0x00839540  cArgumentSpec::FindNameAndTypeFromOption
void ArgumentSpec::FindNameAndTypeFromOption(RawStr* option, unsigned int* typeOut, RawStr* nameOut) {
    nameOut->Assign(gStrG, gStrG);
    char* b = option->mpBegin;
    if (b != option->mpEnd) {
        if ((uint32_t)(option->mpEnd - b) <= 1 || *b != '%') {
            LocalStr L;
            L.CopyCtor(*option);
            if (*L.mpBegin == '<' && L.mpEnd[-1] == '>') {
                L.Erase((uint32_t)(L.mpEnd - L.mpBegin) - 1, 1);
                L.Erase(0, 1);
            }
            char* begin = L.mpBegin;
            char* end = L.mpEnd;
            if (end - begin != 0) {
                for (char* p = begin; p != end; ++p) {
                    if (*p == ':') {
                        if (p != end) {
                            uint32_t pos = (uint32_t)(p - begin);
                            if (pos != (uint32_t)-1) {
                                nameOut->Assign(begin, begin + min_alt(pos, (uint32_t)(end - begin)));
                                L = TmpStr(L, pos + 1, (uint32_t)-1);
                            }
                        }
                        break;
                    }
                }
            }
            *typeOut = ArgTypeFromName(L.mpBegin);
            return;
        }
        switch (b[1]) {
        case 'f':
        case 'g': *typeOut = 3; return;
        case 'd': *typeOut = 2; return;
        case 'b': *typeOut = 1; return;
        case 's': *typeOut = 5; return;
        }
    }
    *typeOut = 0;
}

// @ 0x008397a0  cArgumentSpec::NameFromArgType
void ArgumentSpec::NameFromArgType(unsigned int type, RawStr* out) {
    unsigned int n = type & 0x3fff;
    switch (n) {
    case 1:  out->AppendStr("bool"); break;
    case 2:  out->AppendStr("int"); break;
    case 3:  out->AppendStr("float"); break;
    case 4:  out->AppendStr("double"); break;
    case 5:
    case 6:  out->AppendStr("string"); break;
    case 7:  out->AppendStr("vector2"); break;
    case 8:  out->AppendStr("vector3"); break;
    case 9:  out->AppendStr("vector4"); break;
    case 10: out->AppendStr("rgb"); break;
    case 11: out->AppendStr("rgba"); break;
    case 0:  out->AppendStr("invalid"); break;
    default:
        if (n - 0xc <= 0xff && n - 0xc < (unsigned int)(mEnumEnd - mEnumBegin)) {
            Ent2* e = &mEnumBegin[n - 0xc];
            out->AppendRange(e->name.mpBegin, e->name.mpEnd);
        } else {
            out->AppendRange("unknown", "unknown" + 7);
        }
    }
    if ((type & 0xc000) == 0x4000) out->AppendRange("[]", "[]" + 2);
}
