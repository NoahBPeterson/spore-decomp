// src/game/SPEngine/SPPropertyHelpers.cpp -- migrated from slice(s) s006a11b0, s0069f950 by tools/migrate/rewrite.py
// Object file: SPEngine/SPPropertyHelpers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyList.h"
#include "EA/Variant.h"
#include "EA/IO/FileStream.h"
#include "cSPVector2.h"
#include "cSPVector3.h"
#include "cSPVector4.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cString.h"
#include "eastl/allocator.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cResourceBase.h"
#include "cSPColorRGB.h"
#include "cSPColorRGBA.h"

// ---- items of slice s006a11b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
void cStringSet(const void* src, cString* out);
}
// ---- items of slice s006a11b0 end

// @ 0x006a0920
namespace SP {
bool GetPropertyAsVector2Array(cPropertyList const * list, unsigned int id, int * count, cSPVector2 ** data)
{
    EA::Variant const * p;
    if (list && list->GetProperty(id, &p) && p->mTypeId == 0x30 && (p->mFlags & 0x10)) {
        *count = (p->mFlags & 0x30) ? p->mPointer.mElementCount : 1;
        *data = (p->mFlags & 0x30) ? (cSPVector2*)p->mPointer.mpData : (p->mTypeId ? (cSPVector2*)p : 0);
        return true;
    }
    return false;
}
}  // namespace SP


// @ 0x006a10c0
namespace SP {
bool GetPropertyAsVector2(cPropertyList const * list, unsigned int id, cSPVector2 * dst)
{
    EA::Variant const * p;
    if (list && list->GetProperty(id, &p) && p->mTypeId == 0x30) {
        *dst = *p->GetVector2();
        return true;
    }
    return false;
}
}  // namespace SP


// @ 0x006a1110
namespace SP {
bool GetPropertyAsVector3(cPropertyList const * list, unsigned int id, cSPVector3 * dst)
{
    EA::Variant const * p;
    if (list && list->GetProperty(id, &p) && p->mTypeId == 0x31) {
        *dst = *p->GetVector3();
        return true;
    }
    return false;
}
}  // namespace SP


// @ 0x006a1160
namespace SP {
bool GetPropertyAsVector4(cPropertyList const * list, unsigned int id, cSPVector4 * dst)
{
    EA::Variant const * p;
    if (list && list->GetProperty(id, &p) && p->mTypeId == 0x33) {
        *dst = *p->GetVector4();
        return true;
    }
    return false;
}
}  // namespace SP


// @ 0x006a11b0
namespace SP {
bool GetPropertyAsColorRGB(cPropertyList const * list, unsigned int key, cSPColorRGB * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x32) {
    *out = *prop->GetColorRGB();
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a1200
namespace SP {
bool GetPropertyAsColorRGBA(cPropertyList const * list, unsigned int key, cSPColorRGBA * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x34) {
    *out = *prop->GetColorRGBA();
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a1250
namespace SP {
bool GetPropertyAsKey(cPropertyList const * list, unsigned int key, EA::ResourceMan::Key * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = *prop->GetKey();
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a12a0
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList const * list, unsigned int key, unsigned int * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = prop->GetKey()->mInstance;
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a12e0
namespace SP {
bool GetPropertyAsKeyGroup(cPropertyList const * list, unsigned int key, unsigned int * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = prop->GetKey()->mGroup;
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a1320
namespace SP {
bool GetPropertyAsKeyType(cPropertyList const * list, unsigned int key, unsigned int * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = prop->GetKey()->mType;
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a1360
namespace SP {
bool GetPropertyAsText(cPropertyList const * list, unsigned int key, cString * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x22) {
    cStringSet(prop->GetText(), out);
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a13b0
namespace SP {
bool GetPropertyAsString8(cPropertyList const * list, unsigned int key, eastl::basic_string<char, eastl::allocator> * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x12) {
    eastl::basic_string<char,eastl::allocator>* src = prop->GetString8();
    if (src != out) {
      out->assign(src->mpBegin, src->mpEnd);
    }
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a1400
namespace SP {
bool GetPropertyAsString16(cPropertyList const * list, unsigned int key, eastl::basic_string<wchar_t, eastl::allocator> * out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x13) {
    eastl::basic_string<wchar_t,eastl::allocator>* src = prop->GetString16();
    if (src != out) {
      out->assign(src->mpBegin, src->mpEnd);
    }
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a1450
namespace SP {
bool GetPropertyAsChar8Ptr(cPropertyList const * list, unsigned int key, char const ** out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x12) {
    *out = prop->GetString8()->mpBegin;
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x006a1490
namespace SP {
bool GetPropertyAsChar16Ptr(cPropertyList const * list, unsigned int key, wchar_t const ** out)
{
  if (list == 0) return false;
  EA::Variant const * prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x13) {
    *out = prop->GetString16()->mpBegin;
    return true;
  }
  return false;
}
}  // namespace SP
