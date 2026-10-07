// Slice s00919620: EA-text style binary container parser (stream header + string tables), small string helpers,
// EA::Callstack symbol database helpers.
#include "types.h"

// ---- CRT / runtime ----
extern "C" void* __cdecl memcpy_thunk(void* dst, const void* src, unsigned n);        // 0x011e0744
extern "C" void* __cdecl memset(void* dst, int v, unsigned n);                          // 0x011e073e
__declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" __declspec(dllimport) char* __cdecl strstr(const char*, const char*);
void __cdecl EA_free(void* p);                                                          // 0x00f47380 operator delete[]
extern "C" __declspec(dllimport) void* __stdcall GetModuleHandleA(const char*);
extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess();
extern "C" int __stdcall GetModuleInformation(void*, void*, void*, unsigned);          // PSAPI thunk

// ---- eastl::basic_string<char, fixed_vector_allocator<1,256,...>>: 0x14 header + 0x100 inline buffer ----
struct StrBase {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAllocator; char* mpPoolBegin;
    StrBase() {}
    StrBase(const StrBase& o);                       // 0x00886780
    void DeallocateSelf()                            // 0x00919a40
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != mpPoolBegin)
            EA_free(mpBegin);
    }
    ~StrBase() { DeallocateSelf(); }
    StrBase& assign(const char* first, const char* last);  // 0x009199c0
    char* erase(char* f, char* l) { if (f != l) { memmove(f, l, (mpEnd - l) + 1); mpEnd -= (l - f); } return f; }
    void append(const char* first, const char* last);  // 0x00942e50
    StrBase& append(uint32_t c);                       // 0x00924c60
    StrBase* AppendRet(uint32_t c);                    // 0x00919c10
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void reserve(unsigned n);                          // 0x00886560
    StrBase& operator=(const StrBase& o) { if (&o != this) assign(o.mpBegin, o.mpEnd); return *this; }
};
struct FixedString : StrBase {
    char mBuf[0x100];
    FixedString();                                   // 0x00919a60
    void swap(FixedString& o);                       // 0x00919a80
};
struct StrPair {
    FixedString a;     // +0
    FixedString b;     // +0x114
    StrPair();         // 0x00919b20
    ~StrPair();        // 0x00919b70
};
struct Ctx : StrPair {
    uint64_t f228;
    uint64_t f230;
    uint64_t f238;
};

// 0x009199c0: assign(first,last) on the fixed string
StrBase& StrBase::assign(const char* first, const char* last)
{
    const unsigned n = last - first;
    if (n <= (unsigned)(mpEnd - mpBegin)) {
        memcpy_thunk(mpBegin, first, n);
        erase(mpBegin + n, mpEnd);
    } else {
        memcpy_thunk(mpBegin, first, mpEnd - mpBegin);
        append(first + (mpEnd - mpBegin), last);
    }
    return *this;
}

// @ 0x00919a60
FixedString::FixedString()
{
    char* p = mBuf;
    mpPoolBegin = p;
    mpEnd = p;
    mpBegin = p;
    mpCapacity = mpPoolBegin + 0x100;
    *p = 0;
}

// @ 0x00919a80
void FixedString::swap(FixedString& o)
{
    if (&mAllocator == &o.mAllocator) {
        char* t;
        t = mpBegin; mpBegin = o.mpBegin; o.mpBegin = t;
        t = mpEnd; mpEnd = o.mpEnd; o.mpEnd = t;
        t = mpCapacity; mpCapacity = o.mpCapacity; o.mpCapacity = t;
        return;
    }
    StrBase temp(*this);
    StrBase::operator=(o);
    o.StrBase::operator=(temp);
}

// @ 0x00919b20
StrPair::StrPair()
{
}

// 0x00919b70
StrPair::~StrPair()
{
}

// ---- stream ----
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual int  GetSize();                       // 0x1c
    virtual int  s8();                            // 0x20
    virtual int  GetPosition(int mode);           // 0x24
    virtual bool SetPosition(int pos, int mode);  // 0x28
    virtual int  s11();                           // 0x2c
    virtual int  Read(void* buf, int n);          // 0x30
};

struct Seg {
    uint64_t a;      // +0
    uint64_t b;      // +8  (record count)
    uint64_t c;      // +0x10
    uint8_t  d;      // +0x18
    uint8_t  pad[7];
};

struct Info {        // 0x38 bytes
    uint32_t flags;
    uint32_t f4;
    uint32_t f8;
    uint32_t fc, f10, f14, f18, f1c;
    uint64_t size;   // +0x20
    uint32_t f28, f2c, f30, f34;
    bool F918c50(void* a1);                       // 0x00918c50
};

// memory stream used for scanning (0x30 bytes)
struct MemStream : IStream {
    MemStream(int a, int b, const char* name);    // 0x0093c270
    ~MemStream();                                 // 0x0093bde0
    int  Pos(int mode);                           // 0x0093b920
    int  Size();                                  // 0x00fc7e50
    bool F918620(void* holder);                   // 0x00918620
    bool F918c70(void* holder, MemStream* other); // 0x00918c70
    bool F918200(uint64_t* out);                  // 0x00918200
    bool F918cf0(uint32_t lo, uint32_t hi, void* arg);  // 0x00918cf0
    bool F918260(uint64_t* out);                  // 0x00918260
    virtual void vslot();
    char pad[0x20];
};
struct MemStreamBase30 : MemStream {
    uint32_t m24, m28, m2c;
    MemStreamBase30() : MemStream(0, 0, "UTF/MemoryStream") { m24 = 0; m28 = 0; m2c = 0; }
    virtual void vslot();
};
struct MemStream2 : MemStreamBase30 {
    MemStream2() {}
    virtual void vslot();
};
struct MemStream3 : MemStreamBase30 {
    MemStream3() {}
    virtual void vslot();
};

struct Parser : MemStream2 {
    uint32_t f30;
    uint16_t f34;
    uint16_t pad36;
    uint32_t f38;
    uint8_t  f3c, f3d, f3e, f3f, f40;
    uint8_t  pad41[7];
    Seg      seg;           // +0x48
    int64_t  f68;
    uint64_t f70;
    int64_t  f78;
    uint8_t  f80;
    uint8_t  pad81[7];
    uint8_t  f88;
    uint8_t  pad89[3];
    int      f8c;
    Parser();                                    // 0x00919270
    bool F919750(void* a1, Seg* out);
    bool F919ca0(void* a1, Ctx* ctx);
    bool F919090(void* a1);                      // 0x00919090
    bool F9192c0(void* a1, uint32_t tag);        // 0x009192c0
    bool F9193d0(void* a1, uint32_t b, uint32_t lo, uint32_t hi);  // 0x009193d0
    bool F918ff0(void* holder, Info* info);      // 0x00918ff0
};

struct Holder {
    int vptr0;
    IStream sub4;                                // stream at +4 (vtable only used)
    char pad[0x280 - 8];
    uint8_t f280;
    char pad281[0x2a8 - 0x281];
    struct Sub { bool F918350(void* a1, void* out); } f2a8;   // 0x00918350
    char pad2a9[0x2d8 - 0x2a8 - 1];
    char f2d8[0x10];
    bool F919620(void* a1, Info* info);          // 0x00919620
    bool F919bc0(StrPair* p, FixedString* out);  // 0x00919bc0
    bool F919c30(Info* p, FixedString* out);     // 0x00919c30
    uint32_t F91a010(uint8_t flags, void* a2, StrPair* out, uint32_t* arg4);
    bool F919c10dummy();
};

// @ 0x00919620
bool Holder::F919620(void* a1, Info* info)
{
    if (!f2a8.F918350(a1, f2d8))
        return false;
    MemStream2 s1;
    if (!s1.F918620(this))
        return false;
    MemStream3 s2;
    if (!s2.F918c70(this, &s1))
        return false;
    bool ok = false;
    for (;;) {
        if (!(s1.Pos(0) < s1.Size()))
            break;
        uint64_t v;
        if (!s1.F918200(&v))
            break;
        if (v == 0)
            continue;
        if (!s2.F918cf0((uint32_t)v, (uint32_t)(v >> 32), info))
            break;
        if (info->F918c50(a1)) {
            ok = true;
            break;
        }
    }
    return ok;
}

// @ 0x00919750
bool Parser::F919750(void* a1, Seg* out)
{
    if (!SetPosition(f38 + 6, 0))
        return false;
    seg.a = 0;
    seg.b = 1;
    seg.c = 1;
    seg.d = 0;
    f68 = 0;
    f70 = 1;
    f78 = 1;
    f80 = 1;
    f88 = 0;
    if (!(GetPosition(0) < GetSize()))
        return false;
    for (;;) {
        uint32_t tag;
        if (Read(&tag, 1) != 1)
            return false;
        bool good = true;
        switch ((uint8_t)tag) {
        case 0: {
            uint64_t t;
            if (!F918200(&t)) return false;
            if (Read(&tag, 1) != 1) return false;
            good = F9193d0(a1, tag, (uint32_t)t, (uint32_t)(t >> 32));
            if (!good) return false;
            break;
        }
        case 1:
            F919090(a1);
            break;
        case 2: {
            uint64_t t;
            if (!F918200(&t)) return false;
            f68 += (int64_t)f3c * (int64_t)t;
            break;
        }
        case 3: {
            uint64_t t2;
            if (!F918260(&t2)) return false;
            f78 += t2;
            break;
        }
        case 4: {
            uint64_t t;
            if (!F918200(&t)) return false;
            f70 = t;
            break;
        }
        case 5: {
            uint64_t t;
            if (!F918200(&t)) return false;
            break;
        }
        case 6:
        case 7:
            break;
        case 8:
            f68 += ((255 - f40) / f3f) * f3c;
            break;
        case 9: {
            uint16_t w;
            if (Read(&w, 2) != 2) return false;
            f68 += w;
            break;
        }
        default:
            if (!F9192c0(a1, tag)) return false;
            break;
        }
        if (f88 != 0) {
            *out = seg;
            return true;
        }
        if (!(GetPosition(0) < GetSize()))
            return false;
    }
}
// 0x00919bc0 .. see above


// 0x00919bc0
bool Holder::F919bc0(StrPair* p, FixedString* out)
{
    out->assign(p->b.mpBegin, p->b.mpEnd);
    out->append("/", "/" + 1);
    out->append(p->a.mpBegin, p->a.mpEnd);
    return true;
}

// 0x00919c10
StrBase* StrBase::AppendRet(uint32_t c)
{
    append(c);
    return this;
}

// 0x00919c30
bool Holder::F919c30(Info* p, FixedString* out)
{
    if (!(p->flags & 1))
        return false;
    IStream* st = &sub4;
    if (!st->SetPosition(p->f8, 0))
        return false;
    uint32_t c;
    do {
        if (st->Read(&c, 1) != 1)
            return false;
        if ((uint8_t)c == 0)
            break;
        out->append(c);
    } while ((uint8_t)c != 0);
    return true;
}

// @ 0x00919ca0
bool Parser::F919ca0(void* a1, Ctx* ctx)
{
    ctx->a.clear();
    ctx->b.clear();
    ctx->f228 = 0;
    ctx->f230 = 0;
    ctx->f238 = 0;
    if (!SetPosition(0, 0)) return false;
    if (Read(&f34, 2) != 2 || f34 != 2) return false;
    if (Read(&f38, 4) != 4) return false;
    if (Read(&f3c, 1) != 1) return false;
    if (Read(&f3d, 1) != 1) return false;
    if (Read(&f3e, 1) != 1) return false;
    if (Read(&f3f, 1) != 1) return false;
    if (Read(&f40, 1) != 1) return false;
    if (!SetPosition(f40 - 1, 1)) return false;
    uint32_t ch;
    if (Read(&ch, 1) != 1) return false;
    while ((uint8_t)ch != 0) {
        do {
            if (Read(&ch, 1) != 1) return false;
        } while ((uint8_t)ch != 0);
        if (Read(&ch, 1) != 1) return false;
    }
    f8c = GetPosition(0);
    Seg sg;
    if (!F919750(a1, &sg)) return false;
    if (!SetPosition(f8c, 0)) return false;
    uint64_t t = 0;
    uint32_t i = 0;
    if (sg.b > 0) {
        do {
            ctx->a.clear();
            do {
                if (Read(&ch, 1) != 1) return false;
                if ((uint8_t)ch == 0) break;
                ctx->a.AppendRet(ch);
            } while ((uint8_t)ch != 0);
            if (!F918200(&t)) return false;
            if (!F918200(&ctx->f228)) return false;
            if (!F918200(&ctx->f230)) return false;
            i++;
        } while (i < sg.b);
    }
    if (!SetPosition(f40 + 10, 0)) return false;
    i = 0;
    if (t > 0) {
        do {
            ctx->b.clear();
            do {
                if (Read(&ch, 1) != 1) return false;
                if ((uint8_t)ch == 0) break;
                ctx->b.AppendRet(ch);
            } while ((uint8_t)ch != 0);
            i++;
        } while (i < t);
    }
    ctx->f238 = sg.c;
    return true;
}

// @ 0x0091a010
uint32_t Holder::F91a010(uint8_t flags, void* a2, StrPair* out, uint32_t* arg4)
{
    if (f280 == 0)
        return 0;
    Info info;
    info.flags = 0; info.f8 = 0; info.fc = 0; info.f10 = 0; info.f14 = 0;
    info.f18 = 0; info.f1c = 0; info.size = 0; info.f28 = 0; info.f2c = 0; info.f30 = 0; info.f34 = 0;
    if (!F919620(a2, &info) || info.size == 0)
        return 0;
    uint32_t r;
    if (flags & 1) {
        Parser p;
        if (!p.F918ff0(this, &info))
            return 0;
        Ctx c;
        if (!p.F919ca0(a2, &c)) {
            return 0;
        }
        out->a.clear();
        arg4[0] = (uint32_t)c.f238;
        r = F919bc0(&c, &out->a) ? 1 : 0;
    } else {
        r = 0;
    }
    if (flags & 2) {
        out->b.clear();
        arg4[1] = 0;
        if (F919c30(&info, &out->b))
            r |= 2;
    }
    return r;
}

// 0x0091a1d0
int64_t GetModuleSizeInfo()
{
    struct { void* base; unsigned size; void* entry; } mi;
    GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(0), &mi, 12);
    return (int)mi.base;
}

// ---- EA::IO / Callstack ----
struct FileStream {
    FileStream(const wchar_t* path);                 // 0x00931e10
    ~FileStream();                                   // 0x00931e70
    bool Open(int a, int b, int c, int d);           // 0x009318f0
    virtual unsigned Read(void* buf, unsigned n);    // 0x00931ce0
    char pad[0x228];
};
void __cdecl SplitPathPtrs(const wchar_t* path, const wchar_t** a, const wchar_t** b, const wchar_t** c);  // 0x00930070

// 0x0091a200
int GetSymbolInfoTypeFromDatabase(const wchar_t* path)
{
    FileStream fs(path);
    if (fs.Open(1, 6, 1, 0)) {
        char buf[256];
        memset(buf, 0, 0x100);
        if (fs.Read(buf, 0xff) != (unsigned)-1) {
            const wchar_t* dir;
            const wchar_t* name;
            const wchar_t* ext = 0;
            SplitPathPtrs(path, &dir, &name, &ext);
            const wchar_t* e = ext;
            if (_wcsicmp(e, L".map") == 0) {
                if (strstr(buf, "Timestamp is"))
                    return 1;
                return 2;
            }
            if (_wcsicmp(e, L".pdb") == 0) {
                if (strstr(buf, "Microsoft C/C++ MSF 7.00") == buf)
                    return 3;
                if (strstr(buf, "Microsoft C/C++ MSF 8.00") == buf)
                    return 4;
            }
        }
    }
    return 0;
}

// ---- EA::Callstack::AddressRepLookupSet ----
struct IAddressRepLookup {
    virtual ~IAddressRepLookup();                    // slot 0 (deleting dtor)
    virtual void v1();
    virtual void Shutdown();                         // 0x8
    virtual void v3();
    virtual unsigned GetAddressRep(unsigned type, uint32_t a, uint32_t b, uint32_t c);  // 0x10
};
struct LNode { LNode* mpNext; LNode* mpPrev; IAddressRepLookup* mValue; };
struct AddressRepLookupSet {
    int pad0;
    LNode mNode;               // +4: list sentinel (next, prev)
    char pad1[0x1c - 0x10];
    int mnSourceCodeFailureCount;   // +0x1c
    bool Shutdown();                                 // 0x0091a430
    unsigned GetAddressRepFromSet(unsigned type, uint32_t a, uint32_t b, uint32_t c);  // 0x0091a490
};

// 0x0091a430
bool AddressRepLookupSet::Shutdown()
{
    LNode* end = &mNode;
    for (LNode* n = mNode.mpNext; n != end; n = n->mpNext) {
        IAddressRepLookup* p = n->mValue;
        p->Shutdown();
        delete p;
    }
    LNode* nn = end->mpNext;
    while (nn != end) {
        LNode* cur = nn;
        nn = nn->mpNext;
        EA_free(cur);
    }
    end->mpNext = end;
    end->mpPrev = end;
    mnSourceCodeFailureCount = 0;
    return true;
}

// 0x0091a490
unsigned AddressRepLookupSet::GetAddressRepFromSet(unsigned type, uint32_t a, uint32_t b, uint32_t c)
{
    unsigned result = 0;
    type &= 0xfffffff3;
    for (LNode* n = mNode.mpNext; type != 0 && n != &mNode; n = n->mpNext) {
        unsigned r = n->mValue->GetAddressRep(type, a, b, c);
        result |= r;
        type &= ~result;
    }
    return result;
}

// 0x0091a4f0: destroy four fixed strings in reverse (array of 4 x 0x10)
struct StrHdr16 { char* b; char* e; char* c; int alloc; };
struct StrArray4 {
    StrHdr16 s[4];
    void DestroyAll();
};
void StrArray4::DestroyAll()
{
    StrHdr16* p = &s[4];
    int i = 3;
    do {
        --p;
        if ((p->c - p->b) > 1 && p->b)
            EA_free(p->b);
    } while (--i >= 0);
}

// 0x0091a530: append formatted text (vsnprintf with growth)
int __cdecl Vsnprintf8(char* buf, unsigned cap, const char* fmt, void* args);
extern char g_emptyString[];       // 0x01667bac shared empty buffer
struct VString {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void reserve(unsigned n);                          // 0x00886560
    VString* AppendVSprintf(const char* fmt, void* args);
};
template <class T> inline const T& vmax(const T& a, const T& b) { return b < a ? a : b; }
// @ 0x0091a530
VString* VString::AppendVSprintf(const char* fmt, void* args)
{
    int len = mpEnd - mpBegin;
    int n;
    if (mpBegin == g_emptyString)
        n = Vsnprintf8(mpEnd, 0, fmt, args);
    else
        n = Vsnprintf8(mpEnd, mpCapacity - mpEnd, fmt, args);
    if (n >= (mpCapacity - mpEnd)) {
        reserve(n + len);
        n = Vsnprintf8(mpBegin + len, n + 1, fmt, args);
    } else if (n < 0) {
        unsigned seven = 7;
        unsigned cur = (mpEnd - mpBegin) * 2;
        unsigned cap = vmax(cur, seven);
        do {
            if (cap >= 1000000)
                break;
            reserve(cap);
            n = Vsnprintf8(mpBegin + len, (cap - len) + 1, fmt, args);
            cap *= 2;
        } while (n < 0);
    }
    if (n >= 0)
        mpEnd = mpBegin + n + len;
    return this;
}

// 0x0091a620: copy-construct a 0x48-byte record: id, 4 strings (vector copy-ctor iterator), bitfields
inline void* __cdecl operator new(unsigned int, void* p) { return p; }
struct Str16 {
    char* b; char* e; char* c; int alloc;
    Str16(const Str16& o);                             // 0x0057cb10
};
struct StrRec {
    uint32_t id;
    Str16 strs[4];
    int      a : 4;
    unsigned b : 12;
    int      c : 16;
};
#pragma inline_depth(0)
StrRec* CopyStrRec(StrRec* d, const StrRec* s)
{
    return new (d) StrRec(*s);
}
#pragma inline_depth()
