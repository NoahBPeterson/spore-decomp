// Slice s006a5690: EA::ArgScript command-variant helpers (type names, property
// lookup, hashtable/vector instantiation helpers). /O2, /arch:SSE.
#include "../../include/types.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static const char kAllocPath[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
extern "C" void* EA_Alloc(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  EA_Dealloc(void* p);                                                                 // 0x00f47380

struct Variant {
    uint32_t d0, d1, d2, d3;
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12
};

struct String {
    void*   mpBegin;    // +0
    void*   mpEnd;      // +4
    void*   mpCapacity; // +8
    void*   mAlloc;     // +0xc
    String& assign(const char* p);
    void    append(const char* pBegin, const char* pEnd);
};

namespace EA { namespace ArgScript {
void MakeCaseInsensitive(const char* src, char* dst);   // 0x00840cc0
}}

// hashtable / hash_map helpers (external, thiscall)
struct HashTable {
    void Find(void* out, const void* key);              // 0x007e2ea0
    void Find2(void* out, const void* key);             // 0x0041fb20
};
struct HashMapKey8 {
    void* operator[](const void* key);                 // 0x0041cd60
};
extern "C" int  DoInsertValue(void* dst, const void* src, int n);           // 0x011e0744
extern "C" void UninitFillN56(void* dst, int n, const void* value, const void* m);  // 0x0042e680
extern "C" void UninitFillN16(void* dst, int n, const void* value, const void* m);  // 0x00555b40
extern "C" void Matrix3Assign(void* dst, const void* src);                  // 0x0041cb40
extern "C" void VariantRelease(int* p);                                     // 0x006ad050
extern "C" void VariantHold(int* p);                                        // 0x006ad010

// ---------------------------------------------------------------------------
// 006a5690  void GetVariantTypeDescription(const Variant& v, String& out)
// ---------------------------------------------------------------------------
void GetVariantTypeDescription(const Variant& v, String& out)
{
    switch (v.mTypeId) {
    case 0x00: out.assign("unknown"); break;
    case 0x01: out.assign("bool"); break;
    case 0x02: out.assign("char8"); break;
    case 0x03: out.assign("char16"); break;
    case 0x05: out.assign("int8"); break;
    case 0x06: out.assign("uint8"); break;
    case 0x07: out.assign("int16"); break;
    case 0x08: out.assign("uint16"); break;
    case 0x09: out.assign("int32"); break;
    case 0x0a: out.assign("uint32"); break;
    case 0x0b: out.assign("int64"); break;
    case 0x0c: out.assign("uint64"); break;
    case 0x0d: out.assign("float"); break;
    case 0x0e: out.assign("double"); break;
    case 0x0f: out.assign("void*"); break;
    case 0x10: out.assign("void"); break;
    case 0x11: out.assign("IUnknownRC"); break;
    case 0x12: out.assign("string8"); break;
    case 0x13: out.assign("string16"); break;
    case 0x20: out.assign("key"); break;
    case 0x21: out.assign("flags"); break;
    case 0x22: out.assign("text"); break;
    case 0x30: out.assign("vector2"); break;
    case 0x31: out.assign("vector3"); break;
    case 0x32: out.assign("colorRGB"); break;
    case 0x33: out.assign("vector4"); break;
    case 0x34: out.assign("colorRGBA"); break;
    case 0x35: out.assign("matrix2"); break;
    case 0x36: out.assign("matrix3"); break;
    case 0x37: out.assign("matrix4"); break;
    case 0x38: out.assign("transform"); break;
    case 0x39: out.assign("bbox"); break;
    default: goto append_array;
    }
append_array:
    if (v.mFlags & 0x80)
        out.append(" array", "");
}

// ---------------------------------------------------------------------------
// ArgMgr: the property-list manager object that owns the hashtables.
// ---------------------------------------------------------------------------
struct ArgMgr {
    bool FUN_006a58a0(int msg, int* v);            // ret 8
    void FUN_006a59f0(int* v);                     // ret 4
    void FUN_006a5a90(int a, int count, int* p);   // ret 0xc
    void FUN_006a5b80(int count, int* p);          // ret 8
    void FUN_006a5c50(int* out, void* key);        // ret 0xc
    bool FUN_006a5f70(const char* name, uint32_t* out);
    bool FUN_006a5fd0(const char* name, uint32_t* out);
    bool FUN_006a60b0(int a, int b, int* out);
    void FUN_006a61c0(int a, int b);
    bool FUN_006a6240(const char* name, uint32_t* out);
};

// ---------------------------------------------------------------------------
// 006a58a0
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a58a0(int msg, int* v)
{
    void* server = (void*)0;    // SP::MessageServer(); (masked call)
    if (msg != 0xf62ade)
        return false;
    if (v[2] == 0xb1b104) {
        char key[0x10];
        *(uint32_t*)key = v[6];
        *(uint32_t*)(key + 4) = v[4];
        void* iter = 0;
        ((HashTable*)((char*)this + 0x74))->Find2(&iter, key);
        if (*(void**)&iter != *(void**)(*(int*)((char*)this + 0x78) + *(int*)((char*)this + 0x7c) * 4)) {
            if (*(int*)(*(int*)&iter + 8))
                FUN_006a60b0(0, 0, 0);
        }
        (*(void (__thiscall**)(void*, int, int*, int))(*(int*)server + 0x14))(server, 0xf62def, v, 0);
        (*(void (__thiscall**)(void*, void*, int*, int, int))(*(int*)server + 0x18))(server, server, v, 0, 0);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 006a59f0
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a59f0(int* v)
{
    int tmp = 0;
    char ok = (*(char (__thiscall**)(void*, int, int*))(**(int**)((char*)this + 0x18) + 0x14))(
        *(void**)((char*)this + 0x18), (int)v + 8, &tmp);
    if (ok)
        VariantRelease(&tmp);
    char key[0x10];
    *(uint32_t*)key = *(uint32_t*)((char*)v + 0x10);
    *(uint32_t*)(key + 4) = *(uint32_t*)((char*)v + 0x18);
    ((HashTable*)((char*)this + 0x74))->Find2(&key[0], key);
    VariantRelease(&tmp);
}

// ---------------------------------------------------------------------------
// 006a5a90
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a5a90(int a, int count, int* p)
{
    (void)a;
    int* held = 0;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            int val = p[i];
            if (held) {
                int* h = held;
                held = 0;
                (*(void (__thiscall**)(int*))(*h + 4))(h);
            }
            char ok = (*(char (__thiscall**)(void*, int*, int**))(**(int**)((char*)this + 0x18) + 0x14))(
                *(void**)((char*)this + 0x18), &val, &held);
            if (ok)
                VariantRelease(held);
            char key[0x10];
            *(uint32_t*)key = val;
            *(uint32_t*)(key + 4) = 0xb1b104;
            ((HashTable*)((char*)this + 0x74))->Find2(&key[0], key);
        }
    }
    if (held) {
        int* h = held;
        (*(void (__thiscall**)(int*))(*h + 4))(h);
    }
}

// ---------------------------------------------------------------------------
// 006a5b80
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a5b80(int count, int* p)
{
    int* held = 0;
    if (count > 0) {
        do {
            if (held) {
                int* h = held;
                held = 0;
                (*(void (__thiscall**)(int*))(*h + 4))(h);
            }
            char ok = (*(char (__thiscall**)(void*, int*, int**))(**(int**)((char*)this + 0x18) + 0x14))(
                *(void**)((char*)this + 0x18), p, &held);
            if (ok)
                VariantRelease(held);
            char key[0x10];
            *(uint32_t*)key = p[0];
            *(uint32_t*)(key + 4) = p[2];
            ((HashTable*)((char*)this + 0x74))->Find2(&key[0], key);
            p += 3;
        } while (--count);
    }
    if (held) {
        int* h = held;
        (*(void (__thiscall**)(int*))(*h + 4))(h);
    }
}

// ---------------------------------------------------------------------------
// 006a5c50
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a5c50(int* out, void* key)
{
    (void)key;
    out[0] = 0;
    out[1] = 0;
    *((uint8_t*)(out + 2)) = 0;
}

// ---------------------------------------------------------------------------
// 006a5f70
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a5f70(const char* name, uint32_t* out)
{
    char buf[0x10];
    EA::ArgScript::MakeCaseInsensitive(name, (char*)this + 0x168);
    ((HashTable*)((char*)this + 0x94))->Find(buf, (char*)this + 0x168);
    if (*(void**)buf != *(void**)(*(int*)((char*)this + 0x98) + *(int*)((char*)this + 0x9c) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006a5fd0
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a5fd0(const char* name, uint32_t* out)
{
    unsigned n = (unsigned)(strlen(name) + 1);
    char* p;
    unsigned cap;
    if (n < 2) {
        p = (char*)0x01667bac;
        cap = 0x01667bad;
    } else {
        p = (char*)EA_Alloc(n, "App", 0, 0, kAllocPath, 0xd1);
        cap = (unsigned)(p + n);
    }
    char* first = p;
    DoInsertValue(p, name, (int)strlen(name));
    p[strlen(name)] = 0;
    char buf[0x10];
    buf[0] = 0;
    ((HashTable*)((char*)this + 0xd4))->Find(buf, p);
    if (1 < (int)(cap - (unsigned)first) && first)
        EA_Dealloc(first);
    if (*(void**)buf != *(void**)(*(int*)((char*)this + 0xd8) + *(int*)((char*)this + 0xdc) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006a60b0
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a60b0(int a, int b, int* out)
{
    char key[0x10];
    *(uint32_t*)key = a;
    *(uint32_t*)(key + 4) = b;
    *(uint32_t*)(key + 8) = 0xb1b104;
    void* iter = 0;
    ((HashTable*)((char*)this + 0x74))->Find2(&iter, key);
    if (*(void**)&iter == *(void**)(*(int*)((char*)this + 0x78) + *(int*)((char*)this + 0x7c) * 4)) {
        char ok = (*(char (__thiscall**)(void*, void*, int*, int, int))(**(int**)((char*)this + 0x18) + 0xc))(
            *(void**)((char*)this + 0x18), key, out, 0, 0);
        return ok != 0;
    }
    *out = *(int*)(*(int*)&iter + 8);
    return true;
}

// ---------------------------------------------------------------------------
// 006a61c0
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a61c0(int a, int b)
{
    char* self = (char*)this;
    *(uint32_t*)(self + 8) = a;
    *(uint32_t*)(self + 0xc) = 0xb1b104;
    *(uint32_t*)(self + 0x10) = b;
    VariantHold((int*)self);
    char key[0x10];
    *(uint32_t*)key = a;
    *(uint32_t*)(key + 4) = b;
    void** slot = (void**)((HashMapKey8*)(self + 0x74))->operator[](key);
    void* old = *slot;
    if (self != old) {
        (*(void (__thiscall**)(char*))(*(int*)self))(self);
        *slot = self;
        if (old)
            (*(void (__thiscall**)(void*))(*(int*)old + 4))(old);
    }
}

// ---------------------------------------------------------------------------
// 006a6240
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a6240(const char* name, uint32_t* out)
{
    char* self = (char*)this;
    EA::ArgScript::MakeCaseInsensitive(name, self + 0x168);
    if (isdigit((unsigned char)*name)) {
        *out = (uint32_t)strtoul(name, 0, 0);
        return true;
    }
    char buf[0x10];
    ((HashTable*)(self + 0x128))->Find(buf, self + 0x168);
    if (*(void**)buf != *(void**)(*(int*)(self + 0x12c) + *(int*)(self + 0x130) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    ((HashTable*)(self + 0x94))->Find(buf, self + 0x168);
    if (*(void**)buf != *(void**)(*(int*)(self + 0x98) + *(int*)(self + 0x9c) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006a5e10  vector<basic_string>: element 0x10
// ---------------------------------------------------------------------------
struct Vec10s {
    void* begin; void* end; void* cap;
    Vec10s* Init(unsigned n, const void* value);
    void Alloc(unsigned n, const void* value);   // 0x007c7a40
};
Vec10s* Vec10s::Init(unsigned n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    tmp[0] = 0x01667bac;
    tmp[1] = 0x01667bac;
    tmp[2] = 0x01667bad;
    tmp[3] = 0;
    UninitFillN16(begin, n, tmp, value);
    *(void**)((char*)this + 4) = (char*)begin + n * 0x10;
    return this;
}

// ---------------------------------------------------------------------------
// 006a5ea0  vector<0x38>: element 0x38
// ---------------------------------------------------------------------------
struct Vec38b {
    void* begin; void* end; void* cap;
    Vec38b* Init(unsigned n, const void* value);
    void Alloc(unsigned n, const void* value);   // 0x006a4130
};
Vec38b* Vec38b::Init(unsigned n, const void* value)
{
    Alloc(n, value);
    uint8_t tmp[0x38];
    uint32_t m[4];
    Matrix3Assign(m, 0);
    UninitFillN56(begin, n, tmp, value);
    *(void**)((char*)this + 4) = (char*)begin + n * 0x38;
    return this;
}

// ---------------------------------------------------------------------------
// 006a6310  vector<uint32_t>: element 4
// ---------------------------------------------------------------------------
struct VecU32 {
    void* begin; void* end; void* cap;
    VecU32* Init(unsigned n, const void* alloc);
    void Alloc(unsigned n, const void* alloc);   // 0x004aa350
};
VecU32* VecU32::Init(unsigned n, const void* alloc)
{
    Alloc(n, alloc);
    uint32_t* p = (uint32_t*)begin;
    for (unsigned i = 0; i < n; i++)
        p[i] = 0;
    *(uint32_t*)((char*)this + 4) = (uint32_t)begin + n * 4;
    return this;
}
