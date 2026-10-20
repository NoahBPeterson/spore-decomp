// Slice s00a17690 (gold2 batch).  EA::Audio ResourceConfiguration / FactoryConfiguration
// (SPAudio AudioResource*.obj), MSVC 2008 SP1 32-bit.
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//   0xa17690  FactoryConfiguration::GetSupportedTypes(uint*, int)   static
//   0xa176c0  ResourceConfiguration::IncludesConfiguration(Key)
//   0xa176f0  ResourceConfiguration::GetPropertyAsBool / Int / Uint32 / Float
//   0xa177f0  eastl::fill_imp<0>::do_fill<EA::Text::AnalysisInfo*, EA::Text::AnalysisInfo>
//   0xa17820  ResourceConfiguration: intrusive-pointer setter (list splice)
//   0xa17890  intrusive rbtree insert helper
//   0xa17910  ResourceConfiguration destructor body
//   0xa17a00  property-bag load from stream
//   0xa17be0  ResourceConfiguration::ResourceConfiguration()
//   0xa17c70  FactoryConfiguration::CreateResource
//   0xa17da0  FactoryConfiguration::WriteResource
//   0xa18470  sorted-range set operation (skip duplicates, copy first range tail)
//   0xa18520  sorted-range merge (copy both tails)
//   0xa18620  ResourceConfiguration::GetProperty
//   0xa186e0  ResourceConfiguration::GetPropertyAsChar16Ptr
//   0xa18720  ResourceConfiguration::GetPropertyAsChar8Ptr
//   0xa18760  ResourceConfiguration::GetPropertyIDs
#include "types.h"

// =====================================================================================
// Foreign callees / globals.
// =====================================================================================
void* __cdecl FUN_00f473a0(uint32_t size, const char* tag, int a, int b, const char* file, uint32_t line);  // EAAllocate
void  FUN_00f47380(void* p);                       // operator delete
void* FUN_00a206f0(void);                          // EA::Audio::GetSystemAT (returns AT*)
int   FUN_00571ef0(void);                          // variant length (returns element count)
void  FUN_00840c70(void* s, const char* fmt, ...); // eastl::SprintfAppend<string8>
void* FUN_00446ff0(void);                          // array payload pointer helper
void  FUN_0093abd0(void* dst, const void* p, int n, int kind);  // WriteString
void* FUN_00921580(void* node);                    // ?RBTreeIncrement@@YAPAURBNode@@PAU1@@Z
void  FUN_0093c570(void* out, const void* in, int n);           // EA::ConvertToString8
void  FUN_009216a0(void* node, void* parent, void* head, int side);  // eastl::RBTreeInsert
void  FUN_0093a780(void* reader, void* dst, int count, int flags);   // EA::IO::ReadInt32
void* FUN_00612db0(const void* begin, const void* end, const uint32_t* key, bool flag);  // eastl::lower_bound
void  FUN_00a17a70(void* self, const void* a, const void* b);        // 0xa17a70
void  FUN_0009a9600(void* key);                    // 0x9a9600 f(void*)

static const char* const kFile_A17890 = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// =====================================================================================
// Small helper objects reached through their own vtable.
// =====================================================================================
static __forceinline void** VtOf(void* p) { return *(void***)p; }

// eastl::basic_string<char, eastl::allocator>
struct EAString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void Resize(int n, int c);                     // 0x47bf30
};

// EA::Thread::Mutex
struct Mutex {
    void Lock(uint32_t id);                        // 0x9221b0
    void Unlock();                                 // 0x922270
};

// eastl::intrusive_list_base
struct IntrusiveList {
    void Dtor();                                   // 0x620230
};

// EA::Variant
struct Variant {
    void Destruct(bool b);                          // 0x93db80
};

// 0x685ed0
struct Helper5ed0 {
    void Call();                                    // 0x685ed0
};

// intrusive rbtree used by the property map
struct PropTree {
    void Nuke(void* node);                          // 0x9a9600
    void Insert(const void* first, const void* last, void* out);  // 0xa17a70
};

// =====================================================================================
// EA::Audio::ResourceConfiguration
//   +0x00 vtable (0x14523e8)      +0x08/+0x0c/+0x10 mKey (instance/type/group)
//   +0x14 vtable (0x1452398)      +0x18/+0x1c intrusive node (next/prev)
//   +0x24 helper object           +0x28 property-lookup interface
//   +0x3c attached property ptr   +0x40 intrusive list anchor
//   +0x58 / +0x6c Variant flags   +0x70 property tree storage
// =====================================================================================
struct ResourceConfiguration {
    uint8_t m[0x100];

    __forceinline void** Vt() { return *(void***)&m[0]; }

    void ctor();                                             // 0xa17be0
    void dtor();                                             // 0xa17910
    int  IncludesConfiguration(void* key);                   // 0xa176c0
    bool GetPropertyAsBool(uint32_t key, uint8_t* out);      // 0xa176f0
    bool GetPropertyAsInt(uint32_t key, int32_t* out);       // 0xa17730
    bool GetPropertyAsUint32(uint32_t key, uint32_t* out);   // 0xa17770
    bool GetPropertyAsFloat(uint32_t key, float* out);       // 0xa177b0
    void SetChild(void* p);                                  // 0xa17820
    void Attach(void** out, void* parent, const uint32_t* key, char flag);  // 0xa17890
    bool GetProperty(uint32_t key, void** out);              // 0xa18620
    void* GetPropertyAsChar16Ptr(uint32_t key);              // 0xa186e0
    void* GetPropertyAsChar8Ptr(uint32_t key);               // 0xa18720
    void GetPropertyIDs(void* out, bool clear);              // 0xa18760
};

// EA::Audio::FactoryConfiguration
struct FactoryConfiguration {
    uint8_t m[0x200];

    __forceinline void** Vt() { return *(void***)&m[0]; }

    static int __stdcall GetSupportedTypes(uint32_t* out, int count);   // 0xa17690
    bool CreateResource(void* stream, void** out, uint32_t a, uint32_t b);  // 0xa17c70
    bool WriteResource(void* stream, void* cfg, uint32_t a, uint32_t b);    // 0xa17da0
};

// =====================================================================================
// eastl::fill_imp
// =====================================================================================
namespace EA { namespace Text {
struct AnalysisInfo { uint32_t a, b, c; };
} }

namespace eastl {
template <int N>
struct fill_imp {
    template <class It, class T>
    static void do_fill(It first, It last, const T& value) {
        for (; first != last; ++first) *first = value;
    }
};
}

// =====================================================================================
// 12-byte sorted-range element: comparison is (a[0], a[2], a[1]).
// =====================================================================================
struct Elem12 { uint32_t a, b, c; };

static __forceinline bool ElemLess(const uint32_t* a, const uint32_t* b) {
    if (a[0] != b[0]) return a[0] < b[0];
    if (a[2] != b[2]) return a[2] < b[2];
    return a[1] < b[1];
}

// @ 0x00A17690
int __stdcall FactoryConfiguration::GetSupportedTypes(uint32_t* out, int count) {
    if (out != 0) {
        if ((uint32_t)count < 1u) return 0;
        out[0] = 0x2b9f662u;
        out[1] = 0x2c9eff2u;
    }
    return 2;
}

// @ 0x00A176C0
int ResourceConfiguration::IncludesConfiguration(void* key) {
    if (key != *(void**)(m - 0xc)) {
        void* p = *(void**)(m + 0x28);
        if (p != 0) {
            if (((bool(__thiscall*)(void*, void*))VtOf((char*)p + 0x14)[2])((char*)p + 0x14, key))
                return 1;
        }
        return 0;
    }
    return 1;
}

// @ 0x00A176F0
bool ResourceConfiguration::GetPropertyAsBool(uint32_t key, uint8_t* out) {
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 1) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(uint8_t*)src;
        return true;
    }
    return false;
}

// @ 0x00A17730
bool ResourceConfiguration::GetPropertyAsInt(uint32_t key, int32_t* out) {
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 9) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(int32_t*)src;
        return true;
    }
    return false;
}

// @ 0x00A17770
bool ResourceConfiguration::GetPropertyAsUint32(uint32_t key, uint32_t* out) {
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0xa) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(uint32_t*)src;
        return true;
    }
    return false;
}

// @ 0x00A177B0
bool ResourceConfiguration::GetPropertyAsFloat(uint32_t key, float* out) {
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0xd) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(float*)src;
        return true;
    }
    return false;
}

// @ 0x00A177F0
template void eastl::fill_imp<0>::do_fill<EA::Text::AnalysisInfo*, EA::Text::AnalysisInfo>(
    EA::Text::AnalysisInfo* first, EA::Text::AnalysisInfo* last, const EA::Text::AnalysisInfo& value);

// @ 0x00A17820
void ResourceConfiguration::SetChild(void* p) {
    if (*(void**)(m + 0x3c) != 0) {
        void* next = *(void**)(m + 0x1c);
        void* prev = *(void**)(m + 0x18);
        *(void**)next = prev;
        *(void**)((char*)prev + 4) = next;
        *(void**)(m + 0x18) = 0;
        *(void**)(m + 0x1c) = 0;
    }
    void* old = *(void**)(m + 0x3c);
    if (p != old) {
        if (p != 0) ((void(__thiscall*)(void*))VtOf(p)[0])(p);
        *(void**)(m + 0x3c) = p;
        if (old != 0) ((void(__thiscall*)(void*))VtOf(old)[1])(old);
    }
    void* np = *(void**)(m + 0x3c);
    if (np != 0) {
        *(void**)(m + 0x1c) = *(void**)((char*)np + 0x44);
        void* head = (char*)np + 0x40;
        void* node = m + 0x18;
        *(void**)node = head;
        *(void**)((char*)head + 4) = node;
        *(void**)(*(void**)(m + 0x1c)) = node;
    }
}

// @ 0x00A17890
void ResourceConfiguration::Attach(void** out, void* parent, const uint32_t* key, char flag) {
    int side = (flag == 0 && parent != (void*)(m + 4) && *key >= *(uint32_t*)((char*)parent + 0x10)) ? 1 : 0;
    void* node = FUN_00f473a0(0x14, "EASTL", 0, 0, kFile_A17890, 0xd1);
    uint32_t* dst = (uint32_t*)((char*)node + 0x10);
    if (dst != 0) *dst = *key;
    FUN_009216a0(node, parent, m + 4, side);
    *(uint32_t*)(m + 0x14) += 1;
    *out = node;
}

// @ 0x00A17910
void ResourceConfiguration::dtor() {
    *(void**)(m + 0) = (void*)0x14523e8;
    *(void**)(m + 0x14) = (void*)0x1452398;

    if (*(void**)(m + 0x3c) != 0) {
        void* next = *(void**)(m + 0x1c);
        void* prev = *(void**)(m + 0x18);
        *(void**)next = prev;
        *(void**)((char*)prev + 4) = next;
        *(void**)(m + 0x18) = 0;
        *(void**)(m + 0x1c) = 0;
    }

    void* p70 = *(void**)(m + 0x70);
    if (p70 != 0 && *(uint32_t*)((char*)p70 - 4) != 0) FUN_00f47380(p70);

    if (*(uint8_t*)(m + 0x6c) & 4) ((Variant*)(m + 0x5c))->Destruct(false);
    if (*(uint8_t*)(m + 0x58) & 4) ((Variant*)(m + 0x48))->Destruct(false);
    ((IntrusiveList*)(m + 0x40))->Dtor();
    {
        void* p = *(void**)(m + 0x3c);
        if (p != 0) ((void(__thiscall*)(void*))VtOf(p)[1])(p);
    }
    ((Helper5ed0*)(m + 0x24))->Call();

    *(void**)(m + 0) = (void*)0x13eb938;
}

// @ 0x00A17A00
bool __stdcall FUN_00a17a00(void* reader, EAString* str) {
    if (str->mpBegin != str->mpEnd) {
        *str->mpBegin = 0;
        str->mpEnd = str->mpBegin;
    }
    int32_t n;
    FUN_0093a780(reader, &n, 1, 0);
    if (n != 0) {
        str->Resize(n, 0);
        return ((int(__thiscall*)(void*, char*, int))VtOf(reader)[0xc])(reader, str->mpBegin, n) == n;
    }
    return true;
}

// @ 0x00A17BE0
void ResourceConfiguration::ctor() {
    *(void**)(m + 0) = (void*)0x13ebcdc;
    *(uint32_t*)(m + 4) = 0;
    *(uint32_t*)(m + 8) = 0;
    *(uint32_t*)(m + 0xc) = 0;
    *(uint32_t*)(m + 0x10) = 0;
    *(void**)(m + 0x14) = (void*)0x1449248;
    *(void**)(m + 0) = (void*)0x14523e8;
    *(void**)(m + 0x14) = (void*)0x1452398;
    *(uint8_t*)(m + 0x20) = 0;
    *(uint32_t*)(m + 0x24) = 0;
    *(uint32_t*)(m + 0x28) = 0;
    *(uint32_t*)(m + 0x2c) = 0;
    *(uint32_t*)(m + 0x3c) = 0;
    *(void**)(m + 0x44) = m + 0x40;
    *(void**)(m + 0x40) = m + 0x40;
    *(uint16_t*)(m + 0x58) = 0;
    *(uint16_t*)(m + 0x5a) = 0;
    *(uint16_t*)(m + 0x6c) = 0;
    *(uint16_t*)(m + 0x6e) = 0;
    *(uint32_t*)(m + 0x70) = 0;
    *(uint32_t*)(m + 0x74) = 0;
    *(uint32_t*)(m + 0x78) = 0;
    *(uint32_t*)(m + 0x1c) = 0;
    *(uint32_t*)(m + 0x18) = 0;
}

// @ 0x00A17C70
bool FactoryConfiguration::CreateResource(void* stream, void** out, uint32_t a, uint32_t b) {
    Mutex* mutex = (Mutex*)(m + 0x10);
    mutex->Lock(0x1452340u);

    ResourceConfiguration* obj = (ResourceConfiguration*)FUN_00f473a0(0x84, "audio", 0, 0, 0, 0);
    if (obj != 0) obj->ctor();

    if (obj != 0) ((void(__thiscall*)(void*))VtOf(obj)[0])(obj);

    if (obj != 0) {
        uint32_t* key = (uint32_t*)((void*(__thiscall*)(void*))VtOf(stream)[0x10 / 4])(stream);
        *(uint32_t*)(obj->m + 8) = key[0];
        *(uint32_t*)(obj->m + 0xc) = key[1];
        *(uint32_t*)(obj->m + 0x10) = key[2];
        if (((bool(__thiscall*)(void*, void*, void*, uint32_t, uint32_t))Vt()[0x24 / 4])(this, stream, obj, a, b)) {
            *out = obj;
            ((void(__thiscall*)(void*))VtOf(obj)[0])(obj);
            ((void(__thiscall*)(void*))VtOf(obj)[1])(obj);
            mutex->Unlock();
            return true;
        }
    }

    if (obj != 0) ((void(__thiscall*)(void*))VtOf(obj)[1])(obj);
    mutex->Unlock();
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0xa17da0 FactoryConfiguration::WriteResource(stream, cfg, key, kind)
//   Serialises every property of cfg (a ResourceConfiguration) into stream.  A stack
//   eastl::string accumulates the textual form of each property; the property map
//   (+0x14) is walked with the intrusive iterator protocol, and for each property the
//   variant payload is formatted by type:
//      1  bool     "prop bool(s) %s"   / " true" | " false"
//      9  int      "prop int(s) %s"    / " %d"
//      10 uint     "prop uint(s) %s"   / " %d"
//      13 float    "prop float(s) %s"  / " %.3f"
//      18 string8  "prop string8(s) %s" / " %s"
//      19 string16 "prop string(s) %s" / " %s" (converted to char8)
//      32 keys     "prop key(s) %s"    / " %s"
//      default:    nothing appended
//   Finally the accumulated buffer is handed to WriteString(dst, ptr, len, 3).
// ---------------------------------------------------------------------------------------------
struct Key3 { uint32_t a, b, c; };

// A char16 (wide) string used by the keys case; DeallocateSelf is 0x933960.
struct WString {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    void DeallocateSelf();                          // 0x933960
};

// eastl::string8 with no explicit capacity field used by SprintfAppend.
struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void Append(const char* s, int n);              // 0x455d60
};

bool FactoryConfiguration::WriteResource(void* stream, void* cfg, uint32_t a, uint32_t b) {
    Mutex* mutex = (Mutex*)(m + 0x10);
    mutex->Lock(0x1452340u);

    if (b != 0x2b9f662) {                            // [ebp+0x14]: config-format magic
        mutex->Unlock();
        return false;
    }

    // Pull the property key/id range from the stream object (vtable slots 0x18, 0x1c).
    void* keyRange = ((void*(__thiscall*)(void*))VtOf(stream)[0x18 / 4])(stream);
    uint32_t keyCount = ((uint32_t(__thiscall*)(void*))VtOf(stream)[0x1c / 4])(stream);
    (void)keyRange;
    (void)keyCount;

    char* cfgp = (char*)cfg;
    *(uint8_t*)(cfgp + 0x20) = 1;                    // mark the config as "being written"

    // Build the iterator head (an intrusive-list sentinel) and get the begin node.
    char* head = (char*)cfg + 0x14;                  // property-map object
    void* begin = ((void*(__thiscall*)(void*, void*, int))VtOf(head)[0x0c / 4])(head, 0, 1);

    bool ok = true;
    void* node = begin;

    for (;;) {
        // node == &head's sentinel ends the walk.
        if (node == 0) break;

        uint32_t propId = *(uint32_t*)((char*)node + 0x10);

        // Look up the system attribute (AT) for this property and its component.
        void* at = (void*)FUN_00a206f0();
        void* comp = ((void*(__thiscall*)(void*, uint32_t))VtOf(at)[0xec / 4])(at, propId);
        if (comp == 0) { ok = false; break; }

        // Fetch the variant payload for the property id.
        void* payload = 0;
        if (!((bool(__thiscall*)(void*, void*, uint32_t))VtOf(head)[0x20 / 4])(head, &payload, propId)) {
            ok = false;
            break;
        }

        // Accumulate the textual form into `line`.
        String8 line;
        line.mpBegin = 0; line.mpEnd = 0; line.mpCapacity = 0;

        uint32_t n = (uint32_t)FUN_00571ef0();                    // element count of the variant
        uint32_t* elems = (uint32_t*)FUN_00446ff0();              // element base

        uint16_t type = *(uint16_t*)((char*)payload + 0x12);      // variant element type
        switch (type) {
        case 1: {  // bool
            FUN_00840c70(&line, n == 1 ? "prop bool %s" : "prop bools %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                line.Append(((const char*)elems)[i] ? " true" : " false", 5);
            break;
        }
        case 9: {  // int
            FUN_00840c70(&line, n == 1 ? "prop int %s" : "prop ints %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                FUN_00840c70(&line, " %d", (int)elems[i]);
            break;
        }
        case 10: { // unsigned
            FUN_00840c70(&line, n == 1 ? "prop uint %s" : "prop uints %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                FUN_00840c70(&line, " %d", (int)elems[i]);
            break;
        }
        case 13: { // float
            FUN_00840c70(&line, n == 1 ? "prop float %s" : "prop floats %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                FUN_00840c70(&line, " %.3f", *(float*)&elems[i]);
            break;
        }
        case 18: { // char8 string(s)
            FUN_00840c70(&line, n == 1 ? "prop string8 %s" : "prop string8s %s", (const char*)node);
            char* p = (char*)elems;
            for (uint32_t i = 0; i < n; ++i, p += 0x10)
                FUN_00840c70(&line, " %s", *(char**)p);
            break;
        }
        case 19: { // char16 string(s) -> char8
            FUN_00840c70(&line, n == 1 ? "prop string %s" : "prop strings %s", (const char*)node);
            char* p = (char*)elems;
            for (uint32_t i = 0; i < n; ++i, p += 0x10) {
                String8 tmp;
                tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0;
                FUN_0093c570(&tmp, p, -1);
                FUN_00840c70(&line, " %s", tmp.mpBegin);
                if ((((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & 0xfffffffe) > 1 && tmp.mpBegin != 0)
                    FUN_00f47380(tmp.mpBegin);
            }
            break;
        }
        case 32: { // property-key list
            FUN_00840c70(&line, n == 1 ? "prop key %s" : "prop keys %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i) {
                String8 tmp;
                tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0;
                FUN_0093c570(&tmp, (char*)elems + i * 0x10, -1);
                FUN_00840c70(&line, " %s", tmp.mpBegin);
                if ((((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & 0xfffffffe) > 1 && tmp.mpBegin != 0)
                    FUN_00f47380(tmp.mpBegin);
            }
            break;
        }
        default:
            break;
        }

        // Emit the accumulated line; on failure stop and report.
        if (ok) {
            uint32_t len = (uint32_t)(line.mpEnd - line.mpBegin);
            ok = ((bool(__cdecl*)(void*, const char*, int, int))FUN_0093abd0)(stream, line.mpBegin, len, 3) != 0;
        }

        if (line.mpBegin != 0 && (line.mpEnd - line.mpBegin) > 1)
            FUN_00f47380(line.mpBegin);

        // Advance to the next property.
        node = ((void*(__cdecl*)(void*))FUN_00921580)(node);
    }

    *(uint8_t*)(cfgp + 0x20) = 0;
    mutex->Unlock();
    return ok;
}

// @ 0x00A18470
void FUN_00a18470(Elem12* first1, Elem12* last1, Elem12* first2, Elem12* last2, Elem12* out) {
    while (first1 != last1 && first2 != last2) {
        if (ElemLess((uint32_t*)first1, (uint32_t*)first2)) {
            *out = *first1;
            ++first1;
            ++out;
        } else {
            if (!ElemLess((uint32_t*)first2, (uint32_t*)first1)) ++first1;
            ++first2;
        }
    }
    while (first1 != last1) {
        *out = *first1;
        ++first1;
        ++out;
    }
}

// @ 0x00A18520
void FUN_00a18520(Elem12* first1, Elem12* last1, Elem12* first2, Elem12* last2, Elem12* out) {
    while (first1 != last1 && first2 != last2) {
        if (ElemLess((uint32_t*)first1, (uint32_t*)first2)) {
            *out = *first1;
            ++first1;
        } else if (ElemLess((uint32_t*)first2, (uint32_t*)first1)) {
            *out = *first2;
            ++first2;
        } else {
            *out = *first1;
            ++first1;
            ++first2;
        }
        ++out;
    }
    while (first1 != last1) {
        *out = *first1;
        ++first1;
        ++out;
    }
    while (first2 != last2) {
        *out = *first2;
        ++first2;
        ++out;
    }
}

// @ 0x00A18620
bool ResourceConfiguration::GetProperty(uint32_t key, void** out) {
    char local = *(char*)(m + 0xc);

    if (local == 0) {
        if (key == 0x25df0108u) {
            if (*(uint16_t*)(m + 0x46) != 0) {
                *out = m + 0x34;
                return true;
            }
        } else if (key == 0x7cb81a35u) {
            if (*(uint16_t*)(m + 0x5a) != 0) {
                *out = m + 0x48;
                return true;
            }
        }
    }

    void* begin = *(void**)(m + 0x10);
    void* end = *(void**)(m + 0x14);
    void* found = FUN_00612db0(begin, end, &key, *(bool*)(m + 0x24) != 0);
    if (found != end && !(key < *(uint32_t*)found)) {
        if (found != (char*)found + 0x18) {
            if (found != end) {
                *out = (char*)found + 4;
                return true;
            }
        }
    }

    if (local == 0) {
        void* p = *(void**)(m + 0x28);
        if (p != 0) {
            return ((bool(__thiscall*)(void*, uint32_t, void**))VtOf((char*)p + 0x14)[0x1c / 4])(
                (char*)p + 0x14, key, out);
        }
    }
    return false;
}

// @ 0x00A186E0
void* ResourceConfiguration::GetPropertyAsChar16Ptr(uint32_t key) {
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0x13) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        return *(void**)src;
    }
    return 0;
}

// @ 0x00A18720
void* ResourceConfiguration::GetPropertyAsChar8Ptr(uint32_t key) {
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0x12) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        return *(void**)src;
    }
    return 0;
}

// @ 0x00A18760
void ResourceConfiguration::GetPropertyIDs(void* out, bool clear) {
    if (clear) {
        void* node = *(void**)((char*)out + 0xc);
        ((PropTree*)out)->Nuke(node);
        *(void**)((char*)out + 4) = (char*)out + 4;
        *(void**)((char*)out + 8) = (char*)out + 4;
        *(void**)((char*)out + 0xc) = 0;
        *(uint8_t*)((char*)out + 0x10) = 0;
        *(void**)((char*)out + 0x14) = 0;
    }

    uint8_t* p = *(uint8_t**)(m + 0x10);
    uint8_t* e = *(uint8_t**)(m + 0x14);
    for (; p != e; p += 0x18) {
        uint32_t key = *(uint32_t*)p;
        ((PropTree*)out)->Insert(&key, 0, 0);
    }

    if (*(uint8_t*)(m + 0xc) == 0) {
        void* q = *(void**)(m + 0x28);
        if (q != 0) {
            ((void(__thiscall*)(void*, void*, int))VtOf((char*)q + 0x14)[3])((char*)q + 0x14, out, 0);
        }
    }
}
