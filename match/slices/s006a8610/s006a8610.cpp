// Slice s006a8610 — `anonymous namespace'::GetVariantValueDescription.
// Module flags: /O2 /MD /Gy /EHsc /TP /Oy (16-byte-aligned frame: `and esp,-0x40`).
//
// Produces a human-readable, type-tagged description of an EA::Variant into an
// eastl::basic_string<char>.  A giant jump-table switch over the variant type tag
// (scalar tags 1/9/10/0xd/0x12/... and the 0x80000000|tag array forms); for each tag it
// formats the value with the appropriate conversion and appends it.  ~3.7 KB.
//
// PARTIAL: dispatch and output plumbing only; the per-type formatted arms are not
// reconstructed.  Intentionally NOT counted as matched.
#include "types.h"

struct EAString {
    void*  mpBegin;      // +0
    void*  mpEnd;        // +4
    void*  mpCapacity;   // +8
    void*  mAllocator;   // +0xc

    void assign(const char* s);
};

struct EA_Variant {
    char     mValue[0x10];
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12
};

// @ 0x006a8610
// `anonymous namespace'::GetVariantValueDescription
void GetVariantValueDescription(const EA_Variant* variant, EAString* out)
{
    uint32_t type = variant->mTypeId;
    if (variant->mFlags & 0x80)
        type |= 0x80000000u;

    // The original resets *out to empty before switching (assign/erase to mpBegin).
    out->mpEnd = out->mpBegin;
    if (out->mpBegin)
        *(char*)out->mpBegin = 0;

    switch (type) {
    case 1:  out->assign("bool");    break;
    case 9:  out->assign("int");     break;
    case 10: out->assign("uint");    break;
    case 0xd: out->assign("float");  break;
    case 0x12: out->assign("string"); break;
    case 0x13: out->assign("string16"); break;
    case 0x20: out->assign("key");   break;
    case 0x30: out->assign("vec2");  break;
    case 0x31: out->assign("vec3");  break;
    default:   out->assign("unknown"); break;
    }
}
