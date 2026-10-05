#pragma once
// Slice s006a32a0: EA::ArgScript property-list commands / Variant / EASTL helpers.
#include "../../include/types.h"

// ---------------------------------------------------------------------------
// EA::Variant  (size 0x14; payload at +0, flags at +0x10, typeId at +0x12)
// ---------------------------------------------------------------------------
struct Variant {
    uint32_t d0;        // +0x00
    uint32_t d1;        // +0x04
    uint32_t d2;        // +0x08
    uint32_t d3;        // +0x0c
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12

    void Destruct(int b);                       // 0x0093db80
    void SetType(int type, int a, const void* p, int size, int b);  // 0x0093dd80

    Variant& SetVec21(const void* p);   // 0x006a34a0
    Variant& SetVec30(const void* p);   // 0x006a3510
    Variant& SetVec31(const void* p);   // 0x006a3570
    Variant& SetVec32(const void* p);   // 0x006a3610
};

// ---------------------------------------------------------------------------
// EA::ArgScript::cExprFunction
// ---------------------------------------------------------------------------
namespace EA { namespace ArgScript {
class cExprFunction {
public:
    void** vftable;     // +0x0
    int mRefCount;      // +0x4
    bool EvalBool(int a, int b);
};

class cArguments {
public:
    void* MainArguments(int b);     // 0x00838320
};
}} // namespace EA::ArgScript

// ---------------------------------------------------------------------------
// external helpers (other slices / CRT)
// ---------------------------------------------------------------------------
extern "C" unsigned int FNVHash(const char* s, unsigned int seed, int dummy); // 0x00932e80
void FNVHash1(const char* s, unsigned int seed, int dummy);
