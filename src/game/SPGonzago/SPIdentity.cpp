// src/game/SPGonzago/SPIdentity.cpp -- migrated from slice(s) s01320f20, s00687c20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPIdentity.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern wchar_t gEmptyWString[];                       // 0x1667bac shared empty string
extern "C" void EASTL_allocator_deallocate(void* p);  // 0xf47380
extern "C" void* memcpy(void*, const void*, unsigned);  // E8 call (non-dllimport thunk)
extern const char g_allocFile[];                      // 0x13ebb38 EASTL/allocator.h path
extern "C" void* __cdecl FUN_009309b0(void* dest, const wchar_t* src, int a3, int a4);  // 0x9309b0
#include <stdlib.h>   // atol, strtoul, wcstol (msvcr90 imports)
#include <ctype.h>    // tolower
#include <intrin.h>   // _ReadWriteBarrier

// ---- items of slice s00687c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[];                       // 0x1667bac shared empty string
extern "C" void EASTL_allocator_deallocate(void* p);  // 0xf47380
extern "C" void* memcpy(void*, const void*, unsigned);  // E8 call (non-dllimport thunk)
extern const char g_allocFile[];                      // 0x13ebb38 EASTL/allocator.h path
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* pFile, int line);      // 0xf473a0 EA 6-arg operator new
extern "C" void* __cdecl FUN_009309b0(void* dest, const wchar_t* src, int a3, int a4);  // 0x9309b0
struct WStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void* mAllocUnused;   // stateless allocator member (never stored)

  WStr() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
  WStr(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  WStr(const WStr& x) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(x.mpBegin, x.mpEnd);
  }
  WStr(const wchar_t* pBegin, const wchar_t* pEnd)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(pBegin, pEnd);
  }
  struct InlineTag { InlineTag() {} };
  // Same as the range ctor but with the allocation (EA operator new "App") expanded inline.
  __forceinline WStr(const wchar_t* pBegin, const wchar_t* pEnd, const InlineTag&)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const int n = (int)(pEnd - pBegin);
    const int cap = n + 1;
    if (cap > 1) {
      mpBegin = (wchar_t*)operator new(cap * 2, "App", 0, 0, g_allocFile, 0xd1);
      mpCapacity = mpBegin + cap;
    } else {
      mpBegin = gEmptyWString;
      mpCapacity = gEmptyWString + 1;
    }
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  ~WStr() {
    if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  WStr& operator=(const WStr& x);                  // 0x5c3d90
  void Assign(const wchar_t* b, const wchar_t* e); // 0x423650
  void push_back(wchar_t c);                       // 0x4f6510
  void AllocateSelf(int n);                        // 0x429760
  void RangeInitialize(const wchar_t* p);          // 0x579a90
  void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
    const int n = (int)(pEnd - pBegin);
    AllocateSelf(n + 1);
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
};
struct WStrRange { const wchar_t* begin; const wchar_t* end; };
struct PairUW {
  unsigned key;
  WStr str;
  PairUW(const unsigned* k, const WStr& src);
  PairUW(const PairUW& o);
};
struct IterPair { void* first; void* second; };
struct DirMap {
  char pad0[4];
  void Find(void** out, const unsigned* key);   // 0xe5c780 (hidden out-ptr)
  WStr* OpBr(const unsigned* key);              // @ 0x688ad0
  IterPair Insert(void* pos, PairUW* p, const void* keyTag);  // 0x6889e0 (sret)
};
extern DirMap g_dirMap;                          // 0x152ba34
// ---- items of slice s00687c20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern DirMap g_dirMap;                          // 0x152ba34

// ---- items of slice s01320f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0132_0f20; 
}
typedef eastl::string8_s0132_0f20 string8_s0132_0f20;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0132_0f20&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute
{
    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);    // 0x00572810
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
}
namespace Simulator {
void ReadText_00693090(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Read_00bb9cd0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bb9d00(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00693050(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694f60(char* pBuffer, void* pData);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00693150(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);
}
namespace Simulator {
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
struct TShort{}; struct TU64{}; struct TFloat{}; struct TDouble{}; struct TU8{}; struct TKey{}; struct TSpecies{}; struct TName{}; struct TRotAxis{}; struct TStamps{};
}
namespace Simulator {
template<typename T> bool Valid();      // 0x00b1fbf0
}
namespace Simulator {
template<typename T> bool ToXmlT(void* pData, const char* pName, int depth);
}
namespace Simulator {
#define U32_ATTR   Read4<uint64_t>, Write4<uint64_t>, ReadText_00692ff0, WriteText_00694ee0, Valid<TU64>, ToXmlT<TU64>
}
namespace Simulator {
#define S16_ATTR   Read4<int16_t>, Write4<int16_t>, ReadText_00693090, WriteText_00694f00, Valid<TShort>, ToXmlT<TShort>
}
namespace Simulator {
#define FLOAT_ATTR Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0, Valid<TFloat>, ToXmlT<TFloat>
}
namespace Simulator {
#define DOUBLE_ATTR Read4<double>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXmlT<TDouble>
}
namespace Simulator {
#define U8_ATTR    Read_00bb9cd0, Write_00bb9d00, ReadText_00693050, WriteText_00694f60, Valid<TU8>, ToXmlT<TU8>
}
namespace Simulator {
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, Valid<TKey>, ToXmlT<TKey>
}
namespace Simulator {
#define SPECIES_ATTR Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TSpecies>, ToXmlT<TSpecies>
}
namespace Simulator {
void FUN_00b6e230(Attribute* pAttr);                 // 0x00b6e230  setDefault of mIDColorID
}
namespace Simulator {
extern Attribute sColorAttributes[2];      // 0x0156b0d8  cIDColor records
}
namespace Simulator {
extern int   g_1687980;                    // 0x01687980  cached colour attribute id
}
// ---- items of slice s01320f20 end

// @ 0x00688760
PairUW::PairUW(const unsigned* k, const WStr& src)
: key(*k), str(src.mpBegin, src.mpEnd) {}

// @ 0x00688ad0
WStr* DirMap::OpBr(const unsigned* key)
{
  void* anchor = (char*)this + 4;
  void* pos = anchor;
  void* n = *(void**)((char*)this + 0xc);
  if (n) {
    do {
      if (*(unsigned*)((char*)n + 0x10) < *(unsigned*)key)
        n = *(void**)n;
      else {
        pos = n;
        n = *(void**)((char*)n + 4);
      }
    } while (n);
  }
  if (pos == anchor || *key < *(unsigned*)((char*)pos + 0x10)) {
    WStr tmp;
    PairUW p(key, tmp);
    const void* keyTag = (const void*)((uintptr_t)key & 0xffffff00u);
    IterPair res = Insert(pos, &p, keyTag);
    pos = res.first;
  }
  return (WStr*)((char*)pos + 0x14);
}

// @ 0x00688bb0
void RegisterDirectory(unsigned key, const wchar_t* path)
{
  wchar_t buf[260];
  const wchar_t* src = path;
  if (FUN_009309b0(buf, path, 0, 4))
    src = buf;
  WStr s(src);
  int n = (int)((char*)s.mpEnd - (char*)s.mpBegin) >> 1;
  for (int i = 0; i < n; i++) {
    if (s.mpBegin[i] == 0x5c)
      s.mpBegin[i] = 0x2f;
  }
  if (*(wchar_t*)((char*)s.mpBegin + n * 2 - 2) != 0x2f)
    s.push_back(0x2f);
  WStr* v = g_dirMap.OpBr(&key);
  if ((WStrRange*)&s != (WStrRange*)v)
    v->Assign((const wchar_t*)s.mpBegin, (const wchar_t*)s.mpEnd);
}

// @ 0x01320f20
namespace Simulator {
void InitIDColorAttributes()
{
    {
        Attribute a("mIDColorID", 0x5594700, 4, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0,
                    FUN_00b6e230);
        sColorAttributes[0] = a;
    }
    {
        Attribute a("mCachedColor", 0x6cf7f50, 0x24, Read_00b6e3a0, Write_00ac88c0,
                    ReadText_00c2e4e0, WriteText_00692fb0, Valid<TRotAxis>, ToXml_00ac8050);
        sColorAttributes[1] = a;
    }
    g_1687980 = 0x53dbcf2;
}
}  // namespace Simulator
