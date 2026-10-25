// Slice s0093d740: EA::Variant value setters/destructor + EASTL hash-table bucket rebuild/find/insert,
// plus the Variant-to-string tokenizer. MSVC 2008 SP1, /O2. Names from the 2008 dev-build PDB where known
// (EA::Variant::Destruct).
#include "types.h"

extern void* g_fn154eb48;                       // 0x0154eb48: EA::Variant type-proc
extern "C" void* __cdecl FUN_00f473a0(unsigned, const char*, int, int, const char*, int); // 0x00f473a0 allocator
extern "C" void  __cdecl FUN_00f47380(void*);                                            // 0x00f47380 deallocator
extern "C" void* __cdecl FUN_011e0744(void*, const void*, unsigned);  // 0x011e0744 memcpy thunk
typedef void* (__cdecl* MoveFn)(void*, const void*, unsigned);
// 0x013cc480 is the msvcr90!memmove IAT slot: an indirect call through data, not an in-text function.

namespace EA {

struct Variant {
    union {
        unsigned int   value0;  // +0x00
        unsigned short value0w; // +0x00 low word (SetVariant8 writes only the low word)
    };
    unsigned int   value1;      // +0x04
    unsigned int   value2;      // +0x08
    unsigned int   value3;      // +0x0c
    unsigned short mFlags;      // +0x10
    unsigned short mTypeId;     // +0x12

    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() {
        if (mFlags & 4)
            ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0);
    }

    void Destruct(char bFree);
    // Real retail symbol at 0x0093dd80 (?Construct@Variant@EA@@IAE_NGGPBXII@Z). Declared only:
    // the setters must emit a real out-of-line call, so the byte diff and the call trace match.
    bool Construct(unsigned short type, unsigned short flags, const void* src, unsigned int width, unsigned int isAtomic); // 0x0093dd80
    Variant* SetBool(const unsigned char* p);
    Variant* SetUInt16(const unsigned short* p);
    Variant* SetUInt8(const unsigned char* p);
    Variant* SetInt8(const unsigned char* p);
    Variant* SetUInt16b(const unsigned short* p);
    Variant* SetU32(const unsigned int* p);
    Variant* SetDouble(const double* p);
    Variant* SetPtr(const unsigned short* p);
    Variant* SetVariant8(const unsigned short* p);
};

// The real 0x0093dd80 body (EA::Variant::Construct) is reconstructed further below.
#define VAR_PRELUDE(N, W)                                                        \
    if (mFlags & 4) {                                                            \
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0); \
        if ((mFlags & 2) == 0) { mTypeId = 0; mFlags = 0; }                      \
    }                                                                            \
    unsigned short f = mFlags & 2;                                               \
    if (f != 0 && mTypeId != (N)) { Construct((N), 0, p, (W), 1); return this; }

// @ 0x0093DF20
Variant* Variant::SetBool(const unsigned char* p) {
    VAR_PRELUDE(2, 1)
    unsigned char v = *p;
    mFlags = f; mTypeId = 2;
    *(unsigned char*)&value0 = v;
    return this;
}

// @ 0x0093DFA0
Variant* Variant::SetUInt16(const unsigned short* p) {
    VAR_PRELUDE(3, 2)
    unsigned short v = *p;
    mFlags = f;
    *(unsigned short*)&value0 = v;
    mTypeId = 3;
    return this;
}

// @ 0x0093E020
Variant* Variant::SetUInt8(const unsigned char* p) {
    VAR_PRELUDE(5, 1)
    unsigned char v = *p;
    mFlags = f;
    *(unsigned char*)&value0 = v;
    mTypeId = 5;
    return this;
}

// @ 0x0093E0A0
Variant* Variant::SetInt8(const unsigned char* p) {
    VAR_PRELUDE(6, 1)
    unsigned char v = *p;
    mFlags = f;
    *(unsigned char*)&value0 = v;
    mTypeId = 6;
    return this;
}

// @ 0x0093E120
Variant* Variant::SetUInt16b(const unsigned short* p) {
    VAR_PRELUDE(7, 2)
    unsigned short v = *p;
    mFlags = f;
    *(unsigned short*)&value0 = v;
    mTypeId = 7;
    return this;
}

// @ 0x0093E1A0
Variant* Variant::SetPtr(const unsigned short* p) {
    if (mFlags & 4) {
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0);
        if ((mFlags & 2) == 0) { mTypeId = 0; mFlags = 0; }
    }
    unsigned short f = mFlags & 2;
    if (f != 0 && mTypeId != 0xb) { Construct(0xb, 0, p, 8, 1); return this; }
    const unsigned int* q = (const unsigned int*)p;
    unsigned int a = q[0];
    unsigned int b = q[1];
    value0 = a;
    mFlags = f;
    value1 = b;
    mTypeId = 0xb;
    return this;
}

// @ 0x0093E220
Variant* Variant::SetDouble(const double* p) {
    VAR_PRELUDE(0xe, 8)
    double v = *p;
    mFlags = f;
    *(double*)&value0 = v;
    mTypeId = 0xe;
    return this;
}

// @ 0x0093DBC0  (8-size value / string header copy)
Variant* Variant::SetVariant8(const unsigned short* p) {
    Variant* v = this;
    if (v->mFlags & 4) {
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, v, 0, 0, 0, 0);
        if ((v->mFlags & 2) == 0) { v->mTypeId = 0; v->mFlags = 0; }
    }
    unsigned short f = v->mFlags & 2;
    if (f != 0 && v->mTypeId != 8) { v->Construct(8, 0, p, 2, 1); return v; }
    v->value0w = *p;
    v->mFlags = f; v->mTypeId = 8;
    return v;
}

// @ 0x0093DB80  EA::Variant::Destruct
void Variant::Destruct(char bFree) {
    if (mFlags & 4) {
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0);
    }
    if (bFree != 0 && (mFlags & 2) == 0) {
        mTypeId = 0;
        mFlags = 0;
    }
}

} // namespace EA

using EA::Variant;

// ---------------------------------------------------------------------------------------------
// EASTL hash table (bucket vector at +4, size +8, count +0xc, bucket allocator at +0x10).
// ---------------------------------------------------------------------------------------------
struct HashTable {
    unsigned int  field_0;      // +0x00
    unsigned int* mpBuckets;    // +0x04
    unsigned int  mnBucketCount;// +0x08
    unsigned int  mnElementCount;// +0x0c
    void*         mpAlloc;      // +0x10

    void Rehash(unsigned n);                       // 0x0093DCC0
    void* Find(void** out, const void* key);       // 0x0093E3F0
    void Insert(void** out, int* key);             // 0x0093E470
};

// @ 0x0093DCC0
void HashTable::Rehash(unsigned n) {
    unsigned int size = n * 4;
    char* buckets = (char*)FUN_00f473a0(size + 4, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    buckets[size] = (char)0xff;
    *(unsigned int*)(buckets + size) = 0xffffffff;
    for (unsigned i = 0; i < mnBucketCount; ++i) {
        int* node = (int*)mpBuckets[i];
        while (node) {
            unsigned b = ((unsigned)*(unsigned short*)((char*)node + 4) + (unsigned)node[0]) % n;
            mpBuckets[i] = node[3];
            node[3] = *(int*)(buckets + b * 4);
            *(int**)(buckets + b * 4) = node;
            node = (int*)mpBuckets[i];
        }
    }
    if (mnBucketCount > 1) FUN_00f47380(mpBuckets);
    mpBuckets = (unsigned int*)buckets;
    mnBucketCount = n;
}

// @ 0x0093E3F0
void* HashTable::Find(void** out, const void* key) {
    const int* k = (const int*)key;
    unsigned u = ((unsigned)*(const unsigned short*)((const char*)key + 4) + (unsigned)k[0]) % mnBucketCount;
    int* node = (int*)mpBuckets[u];
    void** slot = (void**)&mpBuckets[u];
    while (node) {
        if (*k == node[0] && *(const unsigned short*)((const char*)key + 4) == *(unsigned short*)((char*)node + 4))
            goto found;
        node = (int*)node[3];
    }
    slot = (void**)&mpBuckets[mnBucketCount];
    node = (int*)*slot;
found:
    out[0] = node;
    out[1] = slot;
    return out;
}

// @ 0x0093E470
void HashTable::Insert(void** out, int* key) {
    unsigned u = ((unsigned)*(unsigned short*)((char*)key + 4) + (unsigned)key[0]) % mnBucketCount;
    int* node = (int*)mpBuckets[u];
    while (node) {
        if (key[0] == node[0] && *(unsigned short*)((char*)key + 4) == *(unsigned short*)((char*)node + 4)) {
            *out = node; *(unsigned char*)(out + 2) = 0; out[1] = (void*)&mpBuckets[u];
            return;
        }
        node = (int*)node[3];
    }
    int* fresh = (int*)FUN_00f473a0(0x10, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    if (fresh) { fresh[0] = key[0]; fresh[1] = key[1]; fresh[2] = key[2]; }
    fresh[3] = 0;
    fresh[3] = *(int*)&mpBuckets[u];
    mpBuckets[u] = (unsigned int)fresh;
    ++mnElementCount;
    *out = fresh; *(unsigned char*)(out + 2) = 1; out[1] = (void*)&mpBuckets[u];
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093DF20 ... EA::Variant::SetBool  (defined above)
// ---------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------
// Wide-string command tokenizer (1074 bytes).
//
//   int VariantToString(const wchar_t* src, int n, wchar_t sep, void** outVec, int f)
//
// Splits src into at most f tokens separated by `sep` (spaces/tabs when sep == ' '), honouring
// double quotes, and appends each token as an EASTL wide string to *outVec (a vector<WStr>).
// Returns the number of tokens.  (Reached from the command server as ParseCmd.)
// ---------------------------------------------------------------------------------------------
struct WStr {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpEndCap;  // +0x08
    void*    mpAlloc;   // +0x0c
};
struct WStrVec {
    WStr* mpBegin;      // +0x00
    WStr* mpEnd;        // +0x04
    WStr* mpEndCap;     // +0x08
};
extern "C" wchar_t WSTR_01667bac[];                                       // 0x01667bac EASTL empty wide string
extern void __fastcall FUN_00553e60(WStrVec* self, int, unsigned n);      // 0x00553e60 vector<WStr>::resize
extern void __fastcall FUN_00423650(WStr* self, int, const wchar_t* b, const wchar_t* e); // 0x00423650 WStr::Assign
extern void __fastcall FUN_00429520(WStr* self, int, unsigned n);         // 0x00429520 WStr::Resize
extern void __fastcall FUN_004228e0(WStr* self, int, unsigned pos, unsigned n); // 0x004228e0 WStr::Erase

// basic_string::erase(pos, n): shift the tail (terminator included) left and shrink.
static void WStr_EraseRange(WStr* t, unsigned pos, unsigned n) {
    wchar_t* dest = t->mpBegin + pos;
    unsigned size = (unsigned)(t->mpEnd - t->mpBegin);
    ((MoveFn)0x13cc480)(dest, dest + n, (size - pos - n) * 2 + 2);
    t->mpEnd -= n;
}

static void WStr_StripQuotes(WStr* t) {
    if (t->mpBegin != t->mpEnd && t->mpBegin[0] == 0x22 && t->mpEnd[-1] == 0x22) {
        unsigned len = (unsigned)(t->mpEnd - t->mpBegin);
        WStr_EraseRange(t, len - 1, 1);
        WStr_EraseRange(t, 0, 1);
    }
}

// @ 0x0093D740
int VariantToString(const unsigned short* srcArg, int n, unsigned short sep, void** outVec, int f) {
    const wchar_t* src = (const wchar_t*)srcArg;
    WStrVec* out = (WStrVec*)outVec;
    int count = 0;

    const wchar_t* end;
    if (n == -1) {
        const wchar_t* q = src;
        while (*q) ++q;
        end = q;
    } else {
        end = src + n;
    }

    const wchar_t* p = src;
    while (p < end && (*p == 0x20 || *p == 9)) ++p;
    if (p == end) return 0;

    const wchar_t* e = end - 1;
    while (e >= src && (*p == 0x20 || *p == 9)) --e;
    int len = (int)(e + 1 - p);

    wchar_t* buf;
    bool allocated = (len + 1 > 1);
    if (allocated) {
        buf = (wchar_t*)FUN_00f473a0((unsigned)((len + 1) * 2), (const char*)0x13ebb38, 0, 0, (const char*)0x13f2150, 0xd1);
    } else {
        buf = WSTR_01667bac;
    }
    FUN_011e0744(buf, p, (unsigned)(len * 2));
    buf[len] = 0;

    int totalLen = len;
    int i = 0;
    int start = 0;
    int quoteCount = 0;
    int byteOffset = 0;

    if (totalLen != 0) {
        for (;;) {
            if ((unsigned)count >= (unsigned)f) goto finalEmit;
            {
                wchar_t c = buf[i];
                bool isSep = (sep == 0x20) ? (c == sep || c == 9) : (c == sep);
                if (isSep) {
                    if ((quoteCount & 1) == 0) goto emitMid;
                    // odd quote count: this separator sits inside a quoted run
                } else if (c == 0x22) {
                    ++quoteCount;
                }
            }
        advance:
            ++i;
            if (i < totalLen) continue;
            goto finalEmit;
        }

    emitMid:
        {
            // A separator boundary always yields a token (possibly empty); the
            // trailing/final emit is the only one that skips empty tokens.
            if ((unsigned)(out->mpEnd - out->mpBegin) / 16 <= (unsigned)count)
                FUN_00553e60(out, 0, (unsigned)(count + 1));
            WStr* t = &out->mpBegin[count];
            FUN_00423650(t, 0, buf + start, buf + i);
            if (sep != 0x20) {
                int tlen = (int)(t->mpEnd - t->mpBegin);
                int k = tlen - 1;
                while (k >= 0 && (t->mpBegin[k] == 0x20 || t->mpBegin[k] == 9)) --k;
                if (k < tlen - 1) FUN_00429520(t, 0, (unsigned)(k + 1));
            }
            WStr_StripQuotes(t);
            ++count;
            byteOffset += 16;
            if (i + 1 < totalLen) {
                int j = i + 1;
                while (j < totalLen && (buf[j] == 0x20 || buf[j] == 9)) ++j;
                i = j - 1;
            }
            start = i + 1;
            quoteCount = 0;
            goto advance;
        }
    }

finalEmit:
    {
        int tokenLen = i - start;
        if (tokenLen != 0 && (unsigned)count < (unsigned)f) {
            if ((unsigned)(out->mpEnd - out->mpBegin) / 16 <= (unsigned)count)
                FUN_00553e60(out, 0, (unsigned)(count + 1));
            WStr* t = &out->mpBegin[count];
            FUN_00423650(t, 0, buf + start, buf + i);
            WStr_StripQuotes(t);
            ++count;
        }
    }

    (void)byteOffset;
    if (allocated) FUN_00f47380(buf);
    return count;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093DD80  EA::Variant::Construct (414 bytes) -- conversion/construct helper.
// Declared-only callers above resolve here (real retail symbol ?Construct@Variant@EA@@IAE_NGGPBXII@Z).
// Body reconstructed; the full conversion/EH control flow is still approximate (see partial.txt).
// ---------------------------------------------------------------------------------------------
bool EA::Variant::Construct(unsigned short type, unsigned short flags, const void* src, unsigned int width, unsigned int isAtomic) {
    unsigned int f = flags;
    bool convert = false;
    if ((mFlags & 2) != 0) {
        f |= 2;
        if (mTypeId != type) convert = true;
    }
    if (!convert) {
        if ((f & 8) != 0) {
            convert = true;
        } else if ((f & 0x20) != 0) {
            mTypeId = type;
            value1 = width;
            mFlags = (unsigned short)f;
            value2 = isAtomic;
            value0 = (unsigned int)(size_t)src;
            return true;
        } else {
            if ((f & 0x10) == 0) {
                unsigned int n = width * isAtomic;
                if (n <= 0x10) {
                    FUN_011e0744(this, src, n);
                    mTypeId = type;
                    mFlags = (unsigned short)f;
                    return true;
                }
                f |= 0x10;
            }
            f |= 8;
            convert = true;
        }
    }

    // Slow path: hand the source descriptor plus the requested type/flags to the
    // global Variant type-proc as a construct (op 2) request.
    Variant typeArg;
    typeArg.SetVariant8(&type);
    Variant flagsArg;
    flagsArg.SetVariant8((const unsigned short*)&f);
    Variant dataArg;
    dataArg.Construct(0x10, 0x20, src, width, isAtomic);
    Variant* args[3];
    args[0] = &dataArg;
    args[1] = &typeArg;
    args[2] = &flagsArg;
    return ((bool(__cdecl*)(int, Variant*, Variant**, int, Variant**, int))g_fn154eb48)(2, this, args, 3, 0, 0);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
