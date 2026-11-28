// Variant-op table, name-cache and socket helpers for the EA internet/socket
// layer, plus a few URL and string utilities.
//
// Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1667bac[];
extern "C" char g_1667bad[];

#include "game/types.h"
#include <string.h>
#include <stdlib.h>
#include "EA/Sockets/Address.h"
#include "EA/Sockets/NameLookup.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern "C" void* g_variantOps[0x400];        // 0x016699C0
extern "C" char  g_variantTableInit;         // 0x0166A9C0
extern "C" void  FUN_0093E5F0();             // 0x0093E5F0 default variant op
extern "C" void* g_opSetFn;                  // 0x0154EB40
extern "C" void* g_opGetFn;                  // 0x0154EB44
extern "C" void* g_opInvokeFn;               // 0x0154EB48
extern "C" int   g_opField;                  // 0x0154EB58

void* GetVariantOp(int a, uint16_t b);       // 0x009413D0
void* SetVariantOp(int a, uint16_t b, void* op);  // 0x00941440
void  InvokeVariantOp(int a, void* b, void* c, void* d, void* e, void* f); // 0x009414B0
bool  InitVariantTable();                    // 0x009414F0
void* GetVariantOpChecked(int a, uint16_t b);              // 0x00941560
void* SetVariantOpChecked(int a, uint16_t b, void* op);    // 0x00941580
void  InvokeVariantOpChecked(int a, void* b, void* c, void* d, void* e, void* f); // 0x009415A0

// Variant ops for (a, b) with a or b >= 0x20 live in a sparse map keyed by
// the 6-byte pair; the dense table covers the common small pairs.
struct VariantMap {
    int   m00;       // +0x00
    int*  mpBegin;   // +0x04
    int   mnCount;   // +0x08
    void* Find(int* out, int* key);
    void* Insert(int* key);
    void  Clear(int* begin, int count);
};
extern "C" VariantMap g_variantMap;          // 0x0154EB4C

void  __cdecl operator delete(void*) throw();
struct StrVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void PushEmpty();                            // 0x009473a0
    void DoInsertValue(char* pos, void* value);  // 0x00554820
};

namespace eastl {
class allocator_s0094_9cc0 { public: int mAlloc; };

template <class T> struct EmptyString { static T s[8]; };
template <class T> T EmptyString<T>::s[8];

template <class T>
struct basic_string_s0094_9cc0 {
    T* mpBegin;                 // +0
    T* mpEnd;                   // +4
    T* mpCapacity;              // +8
    allocator_s0094_9cc0 mAllocator;       // +0xc

    basic_string_s0094_9cc0() {
        mpBegin = EmptyString<T>::s;
        mpEnd = mpBegin;
        mpCapacity = EmptyString<T>::s + 1;
    }
    basic_string_s0094_9cc0& operator=(const basic_string_s0094_9cc0& o) {
        if (&o != this) assign(o.mpBegin, o.mpEnd);
        return *this;
    }
    basic_string_s0094_9cc0& assign(const T* first, const T* last);
    const T* c_str() const { return mpBegin; }
};
typedef basic_string_s0094_9cc0<char>    string;
}
using eastl::string;

// Local stand-in for EA::Internet::URL used only to place GetPort's receiver;
// the canonical header declares url layout identically (see EA/Internet/URL.h).
namespace EA {
namespace Internet {
class URL_s0094_9cc0 {
public:
    bool   mbStrictConformance;      // +0x00
    int    mnMaxComponentLength;     // +0x04
    bool   mbParsed;                 // +0x08
    int    mURLType;                 // +0x0c
    string msURL;                    // +0x10
    string msComponent[9];           // +0x20

    URL_s0094_9cc0();
    URL_s0094_9cc0(const char* p);
    URL_s0094_9cc0& operator=(const URL_s0094_9cc0& o);
    unsigned int GetPort();
};

URL_s0094_9cc0::URL_s0094_9cc0()
    : mbStrictConformance(true), mnMaxComponentLength(0x80), mbParsed(false), mURLType(0) {
}

URL_s0094_9cc0::URL_s0094_9cc0(const char* p)
    : mbStrictConformance(true), mnMaxComponentLength(0x80), mbParsed(false), mURLType(0) {
    if (p) msURL.assign(p, p + strlen(p));
}

URL_s0094_9cc0& URL_s0094_9cc0::operator=(const URL_s0094_9cc0& o) {
    if (&o != this) {
        mbStrictConformance = o.mbStrictConformance;
        mnMaxComponentLength = o.mnMaxComponentLength;
        mbParsed = o.mbParsed;
        mURLType = o.mURLType;
        msURL = o.msURL;
        for (int i = 0; i < 9; ++i)
            msComponent[i] = o.msComponent[i];
    }
    return *this;
}
}
}

// inet_addr and closesocket are the wsock32 entry points; tolower is msvcr90.
extern "C" __declspec(dllimport) unsigned long __stdcall inet_addr(const char* cp);          // wsock32!inet_addr
extern "C" __declspec(dllimport) int   __cdecl tolower(int c);                        // msvcr90
extern "C" __declspec(dllimport) int __stdcall closesocket(unsigned s);               // wsock32
extern char g_eastlEmptyString[];                            // 0x01667bac
struct CacheNode {
    CacheNode* left;      // +0x00
    CacheNode* right;     // +0x04
    CacheNode* parent;    // +0x08
    char*      str;       // +0x10  (key: string begin)
    char*      strEnd;    // +0x14
    unsigned   value;     // +0x20
    unsigned   deadline;  // +0x24
};
struct MutexLike {
    EAMutexData mData;
    void Lock(unsigned id);                         // 0x9221b0
    void Unlock();                                  // 0x922270
    MutexLike(const void* name, bool recursive);    // 0x9222a0
    ~MutexLike();                                   // 0x922130
};
// NameLookup owns its cache tree before its mutex. The tree cleanup helper
// is kept inline so destruction retains the member's receiver boundary.
struct NameLookupCacheMap_s0094cac0 : eastl::map<eastl::basic_string<char, eastl::allocator>,
    EA::Sockets::NameLookup::CacheEntry> {
    void DoNukeSubtree(node_type* node);  // 0x00e84940
    __forceinline ~NameLookupCacheMap_s0094cac0() {
        DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
    }
};
struct LayoutCache {
    int        m0;               // +0x00
    unsigned   mDefaultTimeout;  // +0x04
    unsigned   mSetTimeout;      // +0x08
    NameLookupCacheMap_s0094cac0 mCacheEntryMap; // +0x0c, 0x1c bytes
    MutexLike  mMutex;           // +0x28

    ~LayoutCache();                                                               // 0x0094cf40
    void  Erase(const char* name);                                                 // 0x0094d270
};
void  __cdecl RBTree1_eraseSys(void** out, void* node);      // 0x00812310
void  __cdecl MapStrFind_Find(void** out, void* key);        // 0x00b20930
void  __cdecl eastl_DoInsertValue(void* dst, const char* src, unsigned n);  // 0x011e0744
void* __cdecl operator_new(unsigned size);                   // 0x00f473a0
struct Owner {                   // the owning Socket seen from -8
    virtual void o00();
    virtual void DoError(int err);          // slot 1 (+0x4)
};

// @ 0x009413d0
// Look up the op for (a, b). Small pairs sit in the dense 0x20x0x20 table; the
// rest are keyed by the 6-byte (int a, uint16 b) pair in g_variantMap, with the
// op stored at map-node + 8. A miss returns the default op.
void* GetVariantOp(int a, uint16_t b)
{
    if (a < 0x20 && b < 0x20)
        return g_variantOps[a * 0x20 + b];
    int key[2];
    key[0] = a;
    *(uint16_t*)&key[1] = b;
    int out[2];
    g_variantMap.Find(out, key);
    if (out[0] != g_variantMap.mpBegin[g_variantMap.mnCount])
        return *(void**)(out[0] + 8);
    return (void*)FUN_0093E5F0;
}

// @ 0x00941440
void* SetVariantOp(int a, uint16_t b, void* op)
{
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

// @ 0x009414b0
void InvokeVariantOp(int a, void* b, void* c, void* d, void* e, void* f)
{
    typedef void (__cdecl *Op)(int, void*, void*, void*, void*, void*);
    Op op = (Op)GetVariantOp(a, *(uint16_t*)((char*)b + 0x12));
    op(a, b, c, d, e, f);
}

// @ 0x009414f0
bool InitVariantTable()
{
    if (g_variantTableInit == 0) {
        for (int i = 0; i < 0x400; i++)
            g_variantOps[i] = (void*)FUN_0093E5F0;
        g_variantMap.Clear(g_variantMap.mpBegin, g_variantMap.mnCount);
        g_opField = 0;
        g_opSetFn = (void*)SetVariantOp;
        g_opGetFn = (void*)GetVariantOp;
        g_opInvokeFn = (void*)InvokeVariantOp;
        g_variantTableInit = true;
    }
    return true;
}

// @ 0x00941560
void* GetVariantOpChecked(int a, uint16_t b)
{
    if (g_variantTableInit == 0)
        InitVariantTable();
    return GetVariantOp(a, b);
}

// @ 0x00941580
void* SetVariantOpChecked(int a, uint16_t b, void* op)
{
    if (g_variantTableInit == 0)
        InitVariantTable();
    return SetVariantOp(a, b, op);
}

// @ 0x009415a0
void InvokeVariantOpChecked(int a, void* b, void* c, void* d, void* e, void* f)
{
    if (g_variantTableInit == 0)
        InitVariantTable();
    InvokeVariantOp(a, b, c, d, e, f);
}

// @ 0x00941bb0
__int64 GetTime64()
{
    return _time64(0);
}

// @ 0x009473a0
void StrVec::PushEmpty()
{
    // 0x1667bac is eastl's global empty string (g_eastlEmptyString): an empty
    // string's begin and end point at it, its capacity one past.
    char* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 0x10;
        if (end) {
            *(char**)end = (char*)g_1667bac;
            *(char**)(end + 4) = (char*)g_1667bac;
            *(char**)(end + 8) = (char*)g_1667bad;
        }
        return;
    }
    {
        char tmp[16];
        *(char**)tmp = (char*)g_1667bac;
        *(char**)(tmp + 4) = (char*)g_1667bac;
        *(char**)(tmp + 8) = (char*)g_1667bad;
        DoInsertValue(end, tmp);
        if (*(char**)(tmp + 8) - *(char**)tmp > 1 && *(char**)tmp)
            operator delete(*(char**)tmp);
    }
}

// @ 0x0094a4a0
namespace EA { namespace Internet {
unsigned int URL_s0094_9cc0::GetPort()
{
    return (unsigned int)strtoul(msComponent[4].c_str(), 0, 10);
}
}}  // namespace EA::Internet

// @ 0x0094c130
unsigned int Sockets_ParseAddress(char* s)
{
    char c = *s;
    char* p = s;
    while (c != 0) {
        if (c == '.')
            return inet_addr(s);
        if (c < '0')
            return (unsigned int)-1;
        if (c > '9')
            return (unsigned int)-1;
        c = p[1];
        ++p;
    }
    unsigned int v = (unsigned int)atoi(s);
    return ((v & 0x00ff0000u | v >> 0x10) >> 8) | ((v & 0x0000ff00u | v << 0x10) << 8);
}

// @ 0x0094c190
bool Sockets_IPIsValid(const char* cp)
{
    return inet_addr(cp) != (unsigned long)-1;
}

// @ 0x0094cf40
LayoutCache::~LayoutCache()
{
}

// 0x0094d270: not byte-exact; the byte-exact version is the lifted one in match/slices/s0094d270/s0094d270.cpp
void LayoutCache::Erase(const char* name)
{
    mMutex.Lock(0x143f9c4);
    const char* e = name;
    while (*e) ++e;
    unsigned len = (unsigned)(e - name);

    char* dst;
    if (len + 1 < 2) {
        dst = g_eastlEmptyString;
    } else {
        dst = (char*)operator_new(len + 1);
    }
    eastl_DoInsertValue(dst, name, len);
    char* mid = dst + (e - name);
    *mid = 0;
    for (char* p = dst; p < mid; ++p)
        *p = (char)tolower((unsigned char)*p);

    void* it = 0;
    MapStrFind_Find(&it, dst);
    if (it != (void*)((char*)this + 0x10))
        RBTree1_eraseSys(&it, it);
    mMutex.Unlock();
}

// Retail ISocket subobject prefix. The generated Socket hierarchy has different
// slot/field offsets here; keep the native receiver at this interface boundary.
class SocketBindingView_s0094_d2f0 {
public:
    virtual void V0(); virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9();
    virtual bool Bind();
    virtual bool BindAddress(const EA::Sockets::Address&);
    unsigned mSocketId;                         // interface +0x04
    EA::Sockets::Address mAddress;               // interface +0x08
};

// @ 0x0094d2f0
bool SocketBindingView_s0094_d2f0::Bind()
{
    return BindAddress(mAddress);
}

// @ 0x0094d310
struct SockOwner_s0094d310 {
    virtual void f00();
    virtual void f04();
    virtual void f08();
    virtual void f0c();
    virtual void f10();
    virtual void f14();
    virtual void f18();
    virtual void f1c();
    virtual void f20();
    virtual void f24();
    virtual void f28();
    virtual void f2c();
    virtual void f30();
    virtual void f34();
    virtual void f38();
    virtual void f3c();
    virtual void f40();
    virtual void f44();
    virtual void f48();
    virtual void f4c();
    virtual void f50();
    virtual void OnError(int code);                 // +0x54
};
struct SockIface_s0094d310 {
    virtual void f00();
    virtual void f04();
    virtual void f08();
    virtual void f0c();
    virtual void f10();
    virtual void f14();
    virtual void f18();
    virtual void f1c();
    virtual void f20();
    virtual void f24();
    virtual void ForwardError(int a, int b);        // +0x28
    void Forward(int code, int a, int b);
};
void SockIface_s0094d310::Forward(int code, int a, int b)
{
    ((SockOwner_s0094d310*)((char*)this - 0x78))->OnError(code);
    ForwardError(a, b);
}

// @ 0x0094d350
void __cdecl Socket_CloseRaw(unsigned s)
{
    closesocket(s);
}
