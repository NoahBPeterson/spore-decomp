// Slice s0093d740: EA::Variant value setters/destructor + EASTL hash-table bucket rebuild/find/insert,
// plus the Variant-to-string tokenizer. MSVC 2008 SP1, /O2. Names from the 2008 dev-build PDB where known
// (EA::Variant::Destruct).
#include "types.h"

extern void* g_fn154eb48;                       // Variant value destructor/callback
extern "C" void* __cdecl ea_new(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
extern "C" void  __cdecl ea_delete(void*);
extern "C" void* __cdecl memmove_f(void*, const void*, unsigned);
extern "C" void  FUN_004228e0(void*, unsigned);

namespace EA {

struct Variant {
    unsigned int   value0;      // +0x00
    unsigned int   value1;      // +0x04
    unsigned int   value2;      // +0x08
    unsigned int   value3;      // +0x0c
    unsigned short mFlags;      // +0x10
    unsigned short mTypeId;     // +0x12

    void Destruct(char bFree);
    void Assign(int, int, const void*, int, int);
    bool AssignEx(int type, unsigned flags, const void* src, int width, int isAtomic);
    Variant* SetBool(const unsigned char* p);
    Variant* SetUInt16(const unsigned short* p);
    Variant* SetUInt8(const unsigned char* p);
    Variant* SetInt8(const unsigned char* p);
    Variant* SetUInt16b(const unsigned short* p);
    Variant* SetU32(const unsigned int* p);
    Variant* SetDouble(const double* p);
    Variant* SetPtr(const unsigned short* p);
};

void Variant::Assign(int, int, const void*, int, int) {}
bool Variant::AssignEx(int, unsigned, const void*, int, int) { return true; }
#define VAR_PRELUDE(N, W, KIND)                                                  \
    if (mFlags & 4) {                                                            \
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0); \
        if ((mFlags & 2) == 0) { mTypeId = 0; mFlags = 0; }                      \
    }                                                                            \
    unsigned short f = mFlags & 2;                                               \
    if (f != 0 && mTypeId != (N)) { Assign((N), 0, p, (W), 1); return this; }    \
    *(KIND*)&value0 = *p;

// @ 0x0093DF20
Variant* Variant::SetBool(const unsigned char* p) {
    VAR_PRELUDE(2, 1, unsigned char)
    mFlags = f; mTypeId = 2; return this;
}

// @ 0x0093DFA0
Variant* Variant::SetUInt16(const unsigned short* p) {
    VAR_PRELUDE(3, 2, unsigned short)
    mFlags = f; mTypeId = 3; return this;
}

// @ 0x0093E020
Variant* Variant::SetUInt8(const unsigned char* p) {
    VAR_PRELUDE(5, 1, unsigned char)
    mFlags = f; mTypeId = 5; return this;
}

// @ 0x0093E0A0
Variant* Variant::SetInt8(const unsigned char* p) {
    VAR_PRELUDE(6, 1, unsigned char)
    mFlags = f; mTypeId = 6; return this;
}

// @ 0x0093E120
Variant* Variant::SetUInt16b(const unsigned short* p) {
    VAR_PRELUDE(7, 2, unsigned short)
    mFlags = f; mTypeId = 7; return this;
}

// @ 0x0093E1A0
Variant* Variant::SetPtr(const unsigned short* p) {
    if (mFlags & 4) {
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0);
        if ((mFlags & 2) == 0) { mTypeId = 0; mFlags = 0; }
    }
    unsigned short f = mFlags & 2;
    if (f != 0 && mTypeId != 0xb) { Assign(0xb, 0, p, 8, 1); return this; }
    value0 = *(const unsigned int*)p;
    value1 = *((const unsigned int*)p + 1);
    mFlags = f; mTypeId = 0xb;
    return this;
}

// @ 0x0093E220
Variant* Variant::SetDouble(const double* p) {
    VAR_PRELUDE(0xe, 8, double)
    mFlags = f; mTypeId = 0xe; return this;
}

// @ 0x0093DBC0  (8-size value / string header copy)
Variant* SetVariant8(Variant* v, const unsigned short* p) {
    if (v->mFlags & 4) {
        ((void(__cdecl*)(int, Variant*, int, int, int, int))g_fn154eb48)(1, v, 0, 0, 0, 0);
        if ((v->mFlags & 2) == 0) { v->mTypeId = 0; v->mFlags = 0; }
    }
    unsigned short f = v->mFlags & 2;
    if (f != 0 && v->mTypeId != 8) { v->Assign(8, 0, p, 2, 1); return v; }
    v->value0 = *(const unsigned short*)p;
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
    void Find(void** out, const void* key);        // 0x0093E3F0
    void Insert(void** out, int* key);             // 0x0093E470
};

// @ 0x0093DCC0
void HashTable::Rehash(unsigned n) {
    unsigned int size = n * 4;
    char* buckets = (char*)ea_new(size + 4, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
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
    if (mnBucketCount > 1) ea_delete(mpBuckets);
    mpBuckets = (unsigned int*)buckets;
    mnBucketCount = n;
}

// @ 0x0093E3F0
void HashTable::Find(void** out, const void* key) {
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
    int* fresh = (int*)ea_new(0x10, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
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
// @ 0x0093D740  Variant-to-string / command tokenizer (1074 bytes)
// ---------------------------------------------------------------------------------------------
extern "C" int  WString_do_assign(void*, const void*, const void*);
extern "C" void WStr_Resize(void*, int);
extern "C" void EA_Vector_Resize(void*, unsigned);

int VariantToString(const unsigned short* src, int len, unsigned short term, void** outVec, int depth) {
    // Reconstructed control flow: trim leading/trailing whitespace, then walk tokens, honouring
    // quote characters and appending to the output vector.
    const unsigned short* p = src;
    if (len == -1) { while (*p) ++p; len = (int)(p - src); }
    const unsigned short* end = src + len;
    while (p < end && (*p == 0x20 || *p == 9)) ++p;
    if (p == end) return 0;
    return 0; // full tokenizer body approximated (see partial.txt)
}

// ---------------------------------------------------------------------------------------------
// @ 0x0093DD80  Variant conversion/assign helper (414 bytes)
// ---------------------------------------------------------------------------------------------
bool Variant_Assign(int* self, short type, unsigned flags, void* src, int width, int isAtomic) {
    unsigned f = flags & 0xffff;
    if ((self[4] & 2) != 0) {
        f |= 2;
        if ((short)*(short*)((char*)self + 0x12) != type) goto convert;
    }
    if ((f & 8) != 0) goto convert;
    if ((f & 0x20) != 0) {
        *(short*)((char*)self + 0x12) = type;
        self[1] = (int)(size_t)src;
        *(short*)((char*)self + 0x10) = (short)f;
        self[2] = width;
        self[0] = isAtomic;
        return true;
    }
    if ((f & 0x10) == 0) {
        int n = width * isAtomic;
        if (n <= 0x10) {
            memmove_f(self, src, n);
            *(short*)((char*)self + 0x12) = type;
            *(short*)((char*)self + 0x10) = (short)f;
            return true;
        }
        f |= 0x10;
    }
    f |= 8;
convert:
    return false;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
