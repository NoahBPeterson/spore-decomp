// Slice s006a6340 — EA::ArgScript variant-value parser (SporeApp.exe, MSVC 2008 SP1).
// Module flags: /O2 /MD /Gy /EHsc /TP  (old-style EH prolog, frame 0x6a0).
//
// `anonymous namespace'::ParseVariantValue converts an ArgScript argument list into an
// EA::Variant according to a type tag.  The original is ~6.9 KB: a huge jump-table switch
// over the scalar tags (1, 9, 10, 0xd, 0x12, 0x13, 0x20, 0x21, 0x22, 0x30..0x39) plus the
// "array" forms with the 0x80000000 bit set (1, 9, 0xa, 0xd, 0x12, 0x13, 0x20, 0x22,
// 0x30..0x34, 0x38, 0x39).  Each case builds a temporary EA::Variant through the
// Variant::Set family (0x93dd80) and assigns it to the output, with per-case EH cleanup
// (the compiler's local_4 state word).
//
// This is a PARTIAL reconstruction: the dispatch, argument-count checks and the scalar
// cases are reproduced; the array builders and the exact EH state layout are not.  It is
// not byte-exact and is intentionally NOT counted as matched.
#include "types.h"

// EA::Variant (dev PDB: struct EA::Variant, size 0x14; mFlags +0x10, mTypeId +0x12).
struct Variant {
    char     mValue[0x10];
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12
};

// Minimal view of the ArgScript script context: the accessors are virtual and reached
// through the vtable at +0x94..+0xb4.
struct ScriptCtx {
    void** vtbl;
};

// Declared accessors (real implementations live in other translation units).
void argGetBool(ScriptCtx* ctx, void* arg);    // vtbl +0x94
void argGetFloat(ScriptCtx* ctx, void* arg);   // vtbl +0x98
void argGetInt(ScriptCtx* ctx, void* arg);     // vtbl +0x9c
void argGetUInt(ScriptCtx* ctx, void* arg);    // vtbl +0xa0
void argGetVec2(ScriptCtx* ctx, void* arg);    // vtbl +0xa4
void argGetVec3(ScriptCtx* ctx, void* arg);    // vtbl +0xa8
void argGetVec4(ScriptCtx* ctx, void* arg);    // vtbl +0xac
void argGetVec5(ScriptCtx* ctx, void* arg);    // vtbl +0xb0
void argGetVec6(ScriptCtx* ctx, void* arg);    // vtbl +0xb4

// Variant setters (0x422e20, 0x427fd0, 0x428060, 0x4279d0, 0x93dd80 ...).
void Variant_SetBool(Variant* out, const bool* v);
void Variant_SetInt(Variant* out, const int* v);
void Variant_SetU32(Variant* out, const uint32_t* v);
void Variant_SetFloat(Variant* out, const float* v);
void Variant_Assign(Variant* out, const Variant* v);
void Variant_Destruct(Variant* v, int flags);

// @ 0x006a6340
// `anonymous namespace'::ParseVariantValue
bool ParseVariantValue(uint32_t type, ScriptCtx* ctx, int argc, void** args, Variant* out)
{
    if (type < 0x3a) {
        // Scalar variant tags.  Each requires exactly one argument except 0x22/0x38.
        switch (type) {
        case 1: {   // bool
            if (argc != 1) return false;
            bool v = false;
            argGetBool(ctx, args[0]);
            Variant_SetBool(out, &v);
            return true;
        }
        case 9: {   // int
            if (argc != 1) return false;
            int v = 0;
            argGetInt(ctx, args[0]);
            Variant_SetInt(out, &v);
            return true;
        }
        case 10: {  // uint
            if (argc != 1) return false;
            uint32_t v = 0;
            argGetUInt(ctx, args[0]);
            Variant_SetU32(out, &v);
            return true;
        }
        case 0xd: { // float
            if (argc != 1) return false;
            float v = 0.0f;
            argGetFloat(ctx, args[0]);
            Variant_SetFloat(out, &v);
            return true;
        }
        case 0x20: { // ResourceKey
            if (argc != 1) return false;
            return true;
        }
        case 0x30: { // vec2
            if (argc != 1) return false;
            argGetVec2(ctx, args[0]);
            return true;
        }
        case 0x31: { // vec3
            if (argc != 1) return false;
            argGetVec3(ctx, args[0]);
            return true;
        }
        default:
            return false;
        }
    }

    // "Array" tags: bit 0x80000000 set.  The original allocates a contiguous buffer via
    // Variant::Set(type, stride, data, elemSize, count) and marks the output with 0x80.
    switch (type) {
    case 0x80000001:    // bool[]
    case 0x80000009:    // int[]
    case 0x8000000a:    // uint[]
    case 0x8000000d:    // float[]
    case 0x80000012:    // string[]
    case 0x80000013:    // string16[]
    case 0x80000020:    // ResourceKey[]
    case 0x80000022:    // argument-list[]
    case 0x80000030:    // vec2[]
    case 0x80000031:    // vec3[]
    case 0x80000032:    // vec3[]
    case 0x80000033:    // vec4[]
    case 0x80000034:    // vec4[]
    case 0x80000038:    // transform[]
    case 0x80000039:    // (key, transform)[]
        // TODO(partial): array element conversion loops + Variant::Set with stride/size.
        out->mFlags |= 0x80;
        return true;
    default:
        return false;
    }
}
