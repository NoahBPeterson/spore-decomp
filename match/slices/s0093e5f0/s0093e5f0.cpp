// Slice s0093e5f0 — one function, @ 0x0093e5f0 (11,740 bytes).
//
// EA::Variant's default "type proc": the cdecl callback that EA::Variant calls
// through the global function pointer at 0x0154eb48 for its type-specific work
// (Variant::Destruct calls it with op 1; see slice s0093d740).  Three ops:
//
//   1 (destruct)  release an IUnknown32, destroy a kfCArray block (Release each
//                 interface / free each eastl string, then delete[] the block)
//                 or free an in-place eastl string; then reset the type/flags.
//   2 (construct) set type + flags from ppArgs[1]/ppArgs[2] and copy the data
//                 described by ppArgs[0] (a Variant used as {mpData, mElementSize,
//                 mElementCount}): raw pointer (AddRef), kfCArray (new[] the block
//                 "App/EAVariant/kfCArray" and copy/AddRef/copy-construct strings)
//                 or in place.  An invariant Variant of another type converts the
//                 source to its own type with op 3 instead.
//   3 (convert)   convert pThis (whose data has type ppArgs[0]->mUint16) into
//                 ppResults[0], keeping ppResults[0]'s type: bool, char8/16, the
//                 8..64-bit integers, float, double, string8 and string16 targets.
//                 Integers parse strings with EA::StdC::StrtoI64/StrtoU64 (base
//                 10), floats with strtod/wcstod wrappers, strings format numbers
//                 with _ltoa/_ultoa/I64toa/U64toa/FtoaEnglish (and the wide forms).
//
// Unknown ops return false; every other path (including unsupported type pairs)
// returns true.  The 2008 PDB has the Variant layout and its enums (eTypeId,
// eFlags), but not this function's name.
#include "types.h"

typedef unsigned int eastl_size_t;

inline void* operator new(unsigned int, void* p) { return p; }
void* operator new[](unsigned int size, const char* pName, int flags, unsigned debugFlags,
                     const char* pFile, int line);              // 0x00f473a0
void operator delete[](void* p);                               // 0x00f47380

extern "C" void* __cdecl memcpy(void* pDest, const void* pSource, unsigned int n);   // 0x011e0744
extern "C" __declspec(dllimport) char*    __cdecl _ltoa(long value, char* buffer, int base);
extern "C" __declspec(dllimport) char*    __cdecl _ultoa(unsigned long value, char* buffer, int base);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long value, wchar_t* buffer, int base);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ultow(unsigned long value, wchar_t* buffer, int base);

extern char gEmptyString[];                                    // 0x01667bac (EASTL empty-string storage)

namespace eastl {

struct allocator {};

// eastl::basic_string layout: mpBegin, mpEnd, mpCapacity, allocator (16 bytes).
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    string() : mpBegin(0), mpEnd(0), mpCapacity(0) {
        mpBegin = gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    string(const char* p, const allocator& a = allocator());                     // 0x0057ed80
    string(const char* p, eastl_size_t n, const allocator& a = allocator());     // 0x005e96a0
    string(eastl_size_t n, char c, const allocator& a = allocator());            // 0x005f8f30
    ~string();                                                                   // 0x00530670

    const char* data() const { return mpBegin; }
    eastl_size_t size() const { return (eastl_size_t)(mpEnd - mpBegin); }
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    string& assign(const char* p, eastl_size_t n);                               // 0x0060bcd0
    string& append(eastl_size_t n, char c);                                      // 0x0047bf30
};

struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;

    wstring() : mpBegin(0), mpEnd(0), mpCapacity(0) {
        mpBegin = (wchar_t*)gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    wstring(const wchar_t* p, const allocator& a = allocator());                 // 0x0041df50
    wstring(const wchar_t* p, eastl_size_t n, const allocator& a = allocator()); // 0x0093d6f0
    wstring(eastl_size_t n, wchar_t c, const allocator& a = allocator());        // 0x0084a780
    ~wstring();                                                                  // 0x00933960

    const wchar_t* data() const { return mpBegin; }
    eastl_size_t size() const { return (eastl_size_t)(mpEnd - mpBegin); }
    void clear();                                                                // 0x005726c0
    wstring& assign(const wchar_t* p, eastl_size_t n);                           // 0x006ab7e0
    wstring& append(eastl_size_t n, wchar_t c);                                  // 0x0042d2e0
};

// basic_string::DeallocateSelf, inlined into the destruct loops below.
__forceinline void DestroyString(string* s) {
    if ((s->mpCapacity - s->mpBegin) > 1 && s->mpBegin)
        delete[] s->mpBegin;
}
__forceinline void DestroyString(wstring* s) {
    if ((s->mpCapacity - s->mpBegin) > 1 && s->mpBegin)
        delete[] s->mpBegin;
}

} // namespace eastl

namespace EA {

namespace StdC {
int64_t  StrtoI64(const char* p, char** ppEnd, int base);             // 0x0092d6b0
int64_t  StrtoI64(const wchar_t* p, wchar_t** ppEnd, int base);       // 0x0092d6d0
uint64_t StrtoU64(const char* p, char** ppEnd, int base);             // 0x0092d6f0
uint64_t StrtoU64(const wchar_t* p, wchar_t** ppEnd, int base);       // 0x0092d710
char*    I64toa(int64_t value, char* buffer, int base);                // 0x0092cff0
char*    U64toa(uint64_t value, char* buffer, int base);               // 0x0092d040
wchar_t* I64tow(int64_t value, wchar_t* buffer, int base);             // 0x0092d060
wchar_t* U64tow(uint64_t value, wchar_t* buffer, int base);            // 0x0092d0d0
char*    FtoaEnglish(double value, char* buffer, int bufferLength, int precision, bool bExponentEnabled);      // 0x0092d730
wchar_t* FtoaEnglish(double value, wchar_t* buffer, int bufferLength, int precision, bool bExponentEnabled);   // 0x0092d9b0
double   Strtod(const char* p);                                        // 0x00692700 (strtod wrapper)
double   Strtod(const wchar_t* p);                                     // 0x00622f20 (wcstod wrapper)
} // namespace StdC

class IUnknown32 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct Variant {
    enum eTypeId {
        kTypeUndefined = 0, kTypeBool = 1, kTypeChar8 = 2, kTypeChar16 = 3, kTypeChar32 = 4,
        kTypeInt8 = 5, kTypeUint8 = 6, kTypeInt16 = 7, kTypeUint16 = 8, kTypeInt32 = 9,
        kTypeUint32 = 10, kTypeInt64 = 11, kTypeUint64 = 12, kTypeFloat = 13, kTypeDouble = 14,
        kTypePointer = 15, kTypeVoid = 16, kTypeIUnknown32 = 17, kTypeString8 = 18,
        kTypeString16 = 19, kTypeString32 = 20
    };
    enum eFlags {
        kfNone = 0, kfTypeConstruct = 1, kfInvariant = 2, kfDestruct = 4, kfConstruct = 8,
        kfCArray = 16, kfRawPointer = 32, kfPointerPtr = 64
    };
    struct Pointer {
        void* mpData;
        unsigned int mElementSize;
        unsigned int mElementCount;
    };

    union {
        unsigned char mGeneric[16];
        Pointer mPointer;
        unsigned short mUint16;
    };
    unsigned short mFlags;
    unsigned short mTypeId;

    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant();                                                          // 0x00571ee0
    Variant& operator=(const Variant& x);                                // 0x00542b80
    Variant& operator=(const eastl::string& x);                          // 0x004b5dd0
    Variant& operator=(const eastl::wstring& x);                         // 0x004279d0
    void Assign(int typeId, int flags, const void* pData, unsigned elementSize, unsigned elementCount);  // 0x0093dd80
    void* GetData();                                                     // 0x00446ff0
    unsigned GetCount();                                                 // 0x00571ef0
};

template <typename T>
struct VariantT : public Variant {
    VariantT(const T& value);
};

typedef bool (*TypeProc)(int op, Variant* pThis, Variant** ppArgs, int nArgs, Variant** ppResults, int nResults);
extern TypeProc gpVariantTypeProc;                                       // 0x0154eb48

enum { kOpDestruct = 1, kOpConstruct = 2, kOpConvert = 3 };

// ---- string -> scalar helpers (one per destination type) ----
__forceinline void FromString(char* pDest, const char* p)              { *pDest = p[0]; }
__forceinline void FromString(char* pDest, const wchar_t* p)           { *pDest = (char)p[0]; }
__forceinline void FromString(wchar_t* pDest, const char* p)           { *pDest = (wchar_t)p[0]; }
__forceinline void FromString(wchar_t* pDest, const wchar_t* p)        { *pDest = p[0]; }
__forceinline void FromString(int8_t* pDest, const char* p)            { *pDest = (int8_t)StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(int8_t* pDest, const wchar_t* p)         { *pDest = (int8_t)StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(uint8_t* pDest, const char* p)           { *pDest = (uint8_t)StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(uint8_t* pDest, const wchar_t* p)        { *pDest = (uint8_t)StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(int16_t* pDest, const char* p)           { *pDest = (int16_t)StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(int16_t* pDest, const wchar_t* p)        { *pDest = (int16_t)StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(uint16_t* pDest, const char* p)          { *pDest = (uint16_t)StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(uint16_t* pDest, const wchar_t* p)       { *pDest = (uint16_t)StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(int32_t* pDest, const char* p)           { *pDest = (int32_t)StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(int32_t* pDest, const wchar_t* p)        { *pDest = (int32_t)StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(uint32_t* pDest, const char* p)          { *pDest = (uint32_t)StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(uint32_t* pDest, const wchar_t* p)       { *pDest = (uint32_t)StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(int64_t* pDest, const char* p)           { *pDest = StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(int64_t* pDest, const wchar_t* p)        { *pDest = StdC::StrtoI64(p, 0, 10); }
__forceinline void FromString(uint64_t* pDest, const char* p)          { *pDest = StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(uint64_t* pDest, const wchar_t* p)       { *pDest = StdC::StrtoU64(p, 0, 10); }
__forceinline void FromString(float* pDest, const char* p)             { *pDest = (float)StdC::Strtod(p); }
__forceinline void FromString(float* pDest, const wchar_t* p)          { *pDest = (float)StdC::Strtod(p); }
__forceinline void FromString(double* pDest, const char* p)            { *pDest = StdC::Strtod(p); }
__forceinline void FromString(double* pDest, const wchar_t* p)         { *pDest = StdC::Strtod(p); }

// Convert pSrc (holding a value of type srcType) into the scalar Variant pDest
// of type T (char8/char16/integers/float/double).  Bool and IUnknown32 sources
// are handled by the bool target only; a missing source value stores 0.
template <typename T>
__forceinline bool ConvertToScalar(Variant* pDest, Variant* pSrc, unsigned short srcType)
{
    T* pResult = (T*)pDest->GetData();
    if (!pResult) {
        T value = 0;
        *pDest = VariantT<T>(value);
        pResult = (T*)pDest->GetData();
    }

    switch (srcType) {
        case Variant::kTypeBool: {
            const bool* p = (const bool*)pSrc->GetData();
            if (p) { *pResult = (T)(*(const char*)p != 0); return true; }
            break;
        }
        case Variant::kTypeChar8: {
            const char* p = (const char*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeChar16: {
            const wchar_t* p = (const wchar_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeInt8: {
            const int8_t* p = (const int8_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeUint8: {
            const uint8_t* p = (const uint8_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeInt16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeUint16: {
            const uint16_t* p = (const uint16_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeInt32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeUint32: {
            const uint32_t* p = (const uint32_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant::kTypeString8: {
            const eastl::string* p = (const eastl::string*)pSrc->GetData();
            if (p && p->size()) { FromString(pResult, p->data()); return true; }
            break;
        }
        case Variant::kTypeString16: {
            const eastl::wstring* p = (const eastl::wstring*)pSrc->GetData();
            if (p && p->size()) { FromString(pResult, p->data()); return true; }
            break;
        }
        default:
            return true;
    }

    *pResult = 0;
    return true;
}

__forceinline bool ConvertToBool(Variant* pDest, Variant* pSrc, unsigned short srcType)
{
    bool* pResult = (bool*)pDest->GetData();
    if (!pResult) {
        bool value = true;
        *pDest = VariantT<bool>(value);
        pResult = (bool*)pDest->GetData();
    }

    switch (srcType) {
        case Variant::kTypeUndefined:
            break;
        case Variant::kTypeChar8:
        case Variant::kTypeInt8:
        case Variant::kTypeUint8: {
            const char* p = (const char*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeChar16:
        case Variant::kTypeInt16:
        case Variant::kTypeUint16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeInt32:
        case Variant::kTypeUint32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p && *p != 0.0f) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p && *p != 0.0) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeIUnknown32:
            *pResult = (pSrc->GetData() != 0);
            return true;
        case Variant::kTypeString8: {
            const eastl::string* p = (const eastl::string*)pSrc->GetData();
            if (p && p->size() != 0) { *pResult = true; return true; }
            break;
        }
        case Variant::kTypeString16: {
            const eastl::wstring* p = (const eastl::wstring*)pSrc->GetData();
            if (p && p->size() != 0) { *pResult = true; return true; }
            break;
        }
        default:
            return true;
    }

    *pResult = false;
    return true;
}

__forceinline bool ConvertToString8(Variant* pDest, Variant* pSrc, unsigned short srcType)
{
    eastl::string* pResult = (eastl::string*)pDest->GetData();
    if (!pResult) {
        *pDest = VariantT<eastl::string>(eastl::string((eastl_size_t)0, (char)0));
        pResult = (eastl::string*)pDest->GetData();
    }

    char buffer[64];

    switch (srcType) {
        case Variant::kTypeBool: {
            const bool* p = (const bool*)pSrc->GetData();
            if (p) *pDest = eastl::string(1, (char)(*(const char*)p ? 'T' : 0));
            break;
        }
        case Variant::kTypeChar8:
            pResult->assign((const char*)pSrc->GetData(), pSrc->GetCount());
            break;
        case Variant::kTypeChar16: {
            const wchar_t* p = (const wchar_t*)pSrc->GetData();
            unsigned n = pSrc->GetCount();
            pResult->clear();
            for (unsigned i = 0; i < n; ++i)
                pResult->append(1, (char)p[i]);
            break;
        }
        case Variant::kTypeInt8: {
            const int8_t* p = (const int8_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ltoa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint8: {
            const uint8_t* p = (const uint8_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ultoa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeInt16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ltoa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint16: {
            const uint16_t* p = (const uint16_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ultoa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeInt32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ltoa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint32: {
            const uint32_t* p = (const uint32_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ultoa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::I64toa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::U64toa(*p, buffer, 10));
            break;
        }
        case Variant::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant::kTypeString16: {
            const eastl::wstring* p = (const eastl::wstring*)pSrc->GetData();
            if (p) {
                const eastl_size_t n = p->size();
                if (n) {
                    for (const wchar_t* pc = p->data(), *pEnd = pc + n; pc < pEnd; ++pc)
                        pResult->append(1, (char)*pc);
                }
            }
            break;
        }
    }
    return true;
}

__forceinline bool ConvertToString16(Variant* pDest, Variant* pSrc, unsigned short srcType)
{
    eastl::wstring* pResult = (eastl::wstring*)pDest->GetData();
    if (!pResult) {
        *pDest = VariantT<eastl::wstring>(eastl::wstring((eastl_size_t)0, (wchar_t)0));
        pResult = (eastl::wstring*)pDest->GetData();
    }

    wchar_t buffer[64];

    switch (srcType) {
        case Variant::kTypeBool: {
            const bool* p = (const bool*)pSrc->GetData();
            if (p) {
                const char c = *(const char*)p ? 'T' : 0;
                *pDest = eastl::wstring(1, (wchar_t)c);
            }
            break;
        }
        case Variant::kTypeChar8: {
            const char* p = (const char*)pSrc->GetData();
            unsigned n = pSrc->GetCount();
            pResult->clear();
            for (unsigned i = 0; i < n; ++i)
                pResult->append(1, (wchar_t)p[i]);
            break;
        }
        case Variant::kTypeChar16:
            pResult->assign((const wchar_t*)pSrc->GetData(), pSrc->GetCount());
            break;
        case Variant::kTypeInt8: {
            const int8_t* p = (const int8_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ltow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint8: {
            const uint8_t* p = (const uint8_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ultow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeInt16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ltow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint16: {
            const uint16_t* p = (const uint16_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ultow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeInt32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ltow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint32: {
            const uint32_t* p = (const uint32_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ultow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::I64tow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::U64tow(*p, buffer, 10));
            break;
        }
        case Variant::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant::kTypeString8: {
            const eastl::string* p = (const eastl::string*)pSrc->GetData();
            if (p) {
                const char* pc = p->mpBegin;
                const char* pEnd = p->mpEnd;
                if (pEnd - pc) {
                    for (; pc < pEnd; ++pc)
                        pResult->append(1, (wchar_t)*pc);
                }
            }
            break;
        }
    }
    return true;
}

// @ 0x0093e5f0
bool VariantDefaultTypeProc(int op, Variant* pThis, Variant** ppArgs, int nArgs,
                            Variant** ppResults, int nResults)
{
    (void)nArgs; (void)nResults;

    switch (op) {
        case kOpDestruct: {
            const unsigned short flags = pThis->mFlags;

            if (flags & Variant::kfRawPointer) {
                if (pThis->mTypeId == Variant::kTypeIUnknown32 && pThis->mPointer.mpData) {
                    if (flags & Variant::kfPointerPtr) {
                        IUnknown32* pUnknown = *(IUnknown32**)pThis->mPointer.mpData;
                        if (pUnknown) {
                            pUnknown->Release();
                            pThis->mPointer.mpData = 0;
                        }
                    } else {
                        ((IUnknown32*)pThis->mPointer.mpData)->Release();
                        pThis->mPointer.mpData = 0;
                    }
                }
            } else if (flags & Variant::kfCArray) {
                switch (pThis->mTypeId) {
                    case Variant::kTypeIUnknown32: {
                        IUnknown32** pp = (IUnknown32**)pThis->mPointer.mpData;
                        for (IUnknown32** ppEnd = pp + pThis->mPointer.mElementCount; pp < ppEnd; ++pp) {
                            if (*pp)
                                (*pp)->Release();
                        }
                        break;
                    }
                    case Variant::kTypeString8: {
                        eastl::string* p = (eastl::string*)pThis->mPointer.mpData;
                        for (eastl::string* pEnd = p + pThis->mPointer.mElementCount; p < pEnd; ++p)
                            eastl::DestroyString(p);
                        break;
                    }
                    case Variant::kTypeString16: {
                        eastl::wstring* p = (eastl::wstring*)pThis->mPointer.mpData;
                        for (eastl::wstring* pEnd = p + pThis->mPointer.mElementCount; p < pEnd; ++p)
                            eastl::DestroyString(p);
                        break;
                    }
                }
                delete[] (char*)pThis->mPointer.mpData;
                pThis->mPointer.mpData = 0;
                pThis->mPointer.mElementCount = 0;
                pThis->mFlags &= ~Variant::kfCArray;
                pThis->mFlags |= Variant::kfRawPointer;
            } else {
                switch (pThis->mTypeId) {
                    case Variant::kTypeString8:
                        eastl::DestroyString((eastl::string*)pThis);
                        break;
                    case Variant::kTypeString16:
                        eastl::DestroyString((eastl::wstring*)pThis);
                        break;
                }
            }

            if (!(pThis->mFlags & Variant::kfInvariant)) {
                pThis->mTypeId = 0;
                pThis->mFlags = 0;
            } else {
                pThis->mFlags &= ~Variant::kfDestruct;
                if (!(pThis->mFlags & Variant::kfTypeConstruct))
                    pThis->mFlags &= ~Variant::kfConstruct;
            }
            return true;
        }

        case kOpConstruct: {
            const Variant::Pointer* pSource = &ppArgs[0]->mPointer;
            const unsigned short typeId = ppArgs[1]->mUint16;
            const unsigned short flags = ppArgs[2]->mUint16;

            if ((pThis->mFlags & Variant::kfInvariant) && typeId != pThis->mTypeId) {
                // An invariant Variant keeps its own type: (re)construct it empty if
                // needed, then convert the source value into it.
                if ((pThis->mFlags & Variant::kfConstruct) && !(pThis->mFlags & Variant::kfDestruct)) {
                    VariantT<unsigned short> typeArg(pThis->mTypeId);
                    VariantT<unsigned short> flagsArg(pThis->mFlags);
                    Variant dataArg;
                    dataArg.Assign(Variant::kTypeVoid, Variant::kfRawPointer, 0, 0, 0);
                    Variant* args[3];
                    args[0] = &dataArg;
                    args[1] = &typeArg;
                    args[2] = &flagsArg;
                    gpVariantTypeProc(kOpConstruct, pThis, args, 3, 0, 0);
                }
                if (gpVariantTypeProc(kOpConvert, ppArgs[0], ppArgs + 1, 2, &pThis, 1))
                    pThis->mFlags |= Variant::kfInvariant;
                return true;
            }

            pThis->mFlags = (unsigned short)(((pThis->mFlags ^ flags) & Variant::kfInvariant) ^ flags);
            pThis->mTypeId = typeId;

            const unsigned size = pSource->mElementSize * pSource->mElementCount;
            if (!(flags & Variant::kfCArray) && size > 16)
                pThis->mFlags |= Variant::kfCArray;

            if (pThis->mFlags & Variant::kfRawPointer) {
                pThis->mPointer.mElementSize = pSource->mElementSize;
                pThis->mPointer.mElementCount = pSource->mElementCount;
                pThis->mPointer.mpData = pSource->mpData;

                if (pSource->mpData && pThis->mTypeId == Variant::kTypeIUnknown32) {
                    IUnknown32** ppUnknown = (IUnknown32**)&pThis->mPointer.mpData;
                    if (pThis->mFlags & Variant::kfPointerPtr) {
                        ppUnknown = (IUnknown32**)pThis->mPointer.mpData;
                        if (!ppUnknown)
                            return true;
                    }
                    if (*ppUnknown) {
                        (*ppUnknown)->AddRef();
                        pThis->mFlags |= Variant::kfDestruct;
                    }
                }
            } else if (pThis->mFlags & Variant::kfCArray) {
                pThis->mPointer.mElementSize = pSource->mElementSize;
                pThis->mPointer.mElementCount = pSource->mElementCount;
                pThis->mPointer.mpData = new ("App/EAVariant/kfCArray", 0, 0, 0, 0) char[size];
                pThis->mFlags |= Variant::kfDestruct;

                if (pSource->mpData) {
                    switch (pThis->mTypeId) {
                        case Variant::kTypeIUnknown32: {
                            memcpy(pThis->mPointer.mpData, pSource->mpData, size);
                            IUnknown32** pp = (IUnknown32**)pThis->mPointer.mpData;
                            for (IUnknown32** ppEnd = pp + pSource->mElementCount; pp < ppEnd; ++pp) {
                                if (*pp)
                                    (*pp)->AddRef();
                            }
                            break;
                        }
                        case Variant::kTypeString8: {
                            const eastl::string* pFrom = (const eastl::string*)pSource->mpData;
                            eastl::string* p = (eastl::string*)pThis->mPointer.mpData;
                            for (eastl::string* pEnd = p + pSource->mElementCount; p < pEnd; ++p, ++pFrom)
                                new (p) eastl::string(pFrom->data(), pFrom->size());
                            break;
                        }
                        case Variant::kTypeString16: {
                            const eastl::wstring* pFrom = (const eastl::wstring*)pSource->mpData;
                            eastl::wstring* p = (eastl::wstring*)pThis->mPointer.mpData;
                            for (eastl::wstring* pEnd = p + pSource->mElementCount; p < pEnd; ++p, ++pFrom)
                                new (p) eastl::wstring(pFrom->data(), pFrom->size());
                            break;
                        }
                        default:
                            memcpy(pThis->mPointer.mpData, pSource->mpData, size);
                            break;
                    }
                }
            } else {
                switch (pThis->mTypeId) {
                    case Variant::kTypeString8: {
                        const eastl::string* pFrom = (const eastl::string*)pSource->mpData;
                        if (pFrom)
                            new (pThis) eastl::string(pFrom->data(), pFrom->size());
                        else
                            new (pThis) eastl::string();
                        pThis->mFlags |= Variant::kfDestruct;
                        break;
                    }
                    case Variant::kTypeString16: {
                        const eastl::wstring* pFrom = (const eastl::wstring*)pSource->mpData;
                        if (pFrom)
                            new (pThis) eastl::wstring(pFrom->data(), pFrom->size());
                        else
                            new (pThis) eastl::wstring();
                        pThis->mFlags |= Variant::kfDestruct;
                        break;
                    }
                    default:
                        memcpy(pThis, pSource->mpData, size);
                        break;
                }
            }
            return true;
        }

        case kOpConvert: {
            Variant* pDest = ppResults[0];
            const unsigned short srcType = ppArgs[0]->mUint16;

            switch (pDest->mTypeId) {
                case Variant::kTypeBool:     return ConvertToBool(pDest, pThis, srcType);
                case Variant::kTypeChar8:    return ConvertToScalar<char>(pDest, pThis, srcType);
                case Variant::kTypeChar16:   return ConvertToScalar<wchar_t>(pDest, pThis, srcType);
                case Variant::kTypeInt8:     return ConvertToScalar<int8_t>(pDest, pThis, srcType);
                case Variant::kTypeUint8:    return ConvertToScalar<uint8_t>(pDest, pThis, srcType);
                case Variant::kTypeInt16:    return ConvertToScalar<int16_t>(pDest, pThis, srcType);
                case Variant::kTypeUint16:   return ConvertToScalar<uint16_t>(pDest, pThis, srcType);
                case Variant::kTypeInt32:    return ConvertToScalar<int32_t>(pDest, pThis, srcType);
                case Variant::kTypeUint32:   return ConvertToScalar<uint32_t>(pDest, pThis, srcType);
                case Variant::kTypeInt64:    return ConvertToScalar<int64_t>(pDest, pThis, srcType);
                case Variant::kTypeUint64:   return ConvertToScalar<uint64_t>(pDest, pThis, srcType);
                case Variant::kTypeFloat:    return ConvertToScalar<float>(pDest, pThis, srcType);
                case Variant::kTypeDouble:   return ConvertToScalar<double>(pDest, pThis, srcType);
                case Variant::kTypeString8:  return ConvertToString8(pDest, pThis, srcType);
                case Variant::kTypeString16: return ConvertToString16(pDest, pThis, srcType);
            }
            return true;
        }
    }
    return false;
}

} // namespace EA
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void operator=(int&); // 0x00542b80
};
}
