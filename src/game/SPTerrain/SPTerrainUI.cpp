// src/game/SPTerrain/SPTerrainUI.cpp -- migrated from slice(s) s0057bfb0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cEditorResource.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorUI.h"
#include <string.h>
#include <intrin.h>

// ---- items of slice s0057bfb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
namespace eastl {
class allocator_s0057_bfb0 { public:
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, 0, 0); }
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
}
namespace eastl {
template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0057_bfb0>
class basic_string_s0057_bfb0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string_s0057_bfb0() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string_s0057_bfb0(const basic_string_s0057_bfb0& x);
    struct CtorDoNotInitialize {};
    basic_string_s0057_bfb0(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string_s0057_bfb0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s0057_bfb0() { DeallocateSelf(); }

    basic_string_s0057_bfb0& operator=(const basic_string_s0057_bfb0& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string_s0057_bfb0& assign(const T* pBegin, const T* pEnd);
    basic_string_s0057_bfb0& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};
}
namespace eastl {
typedef basic_string_s0057_bfb0<char> string;
}
namespace eastl {
typedef basic_string_s0057_bfb0<wchar_t> string16_s0057_bfb0;
}
namespace EA {
eastl::string16_s0057_bfb0 ConvertToString16(const char* p, int length = -1);   // 0x0093C5A0
}
namespace EA {
eastl::string16_s0057_bfb0 ConvertToString16(const eastl::string& s);           // 0x0093C6D0
}
namespace SP {
class IXmlWriter {
public:
    virtual bool BeginElement(const wchar_t* name) = 0;
    virtual bool EndElement(const wchar_t* name) = 0;
    virtual bool WriteAttribute(const wchar_t* name, const wchar_t* value) = 0;
    virtual bool WriteCharacters(const wchar_t* text) = 0;
};
}
namespace SP {
template <typename T>
struct cTypedValueToStringT {
    static bool sbWriteType;
    static void Write(eastl::string& out, const T& value);
};
}
namespace SP {
template <typename T>
bool WriteTypedValue(IXmlWriter* writer, const char* name, const T& value, const wchar_t* typeName)
{
    bool result = true;
    eastl::string str;
    cTypedValueToStringT<T>::Write(str, value);
    if (!str.empty()) {
        eastl::string16_s0057_bfb0 name16(name ? EA::ConvertToString16(name) : eastl::string16_s0057_bfb0());
        eastl::string16_s0057_bfb0 text(EA::ConvertToString16(str));
        const wchar_t* element = name16.empty() ? typeName : name16.c_str();
        if (writer->BeginElement(element) &&
            (name16.empty() || !cTypedValueToStringT<T>::sbWriteType || writer->WriteAttribute(L"type", typeName)) &&
            writer->WriteCharacters(text.c_str()) &&
            writer->EndElement(element))
            result = true;
        else
            result = false;
    }
    return result;
}
}
// ---- items of slice s0057bfb0 end

// @ 0x0057c940
namespace SP {
template bool WriteTypedValue<float>(IXmlWriter*, const char*, const float&, const wchar_t*)
;
}  // namespace SP
