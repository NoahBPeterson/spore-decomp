// Slice s004ce310: out-of-line EASTL vector insert/DoInsertValue instances used by the
// creature-editor skin code.  Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
//
// These are template instantiations (vector insert relocation paths for 4-, 1- and
// 8-byte element types).  Their Ghidra decompiles reference eastl::vector::DoInsertValue
// with lost locals; the correct reconstruction is literal EASTL source, which was not
// completed in this pass.  Skeletons only -> partial.txt.
#include "types.h"
#pragma pack(push, 4)

// @ 0x004CE310  eastl::vector<uint32_t>::insert(pos, value)
void VectorInsertU32(uint32_t* vec, void* pos, uint32_t* value)
{
    (void)vec; (void)pos; (void)value;
}

// @ 0x004CE550  eastl::vector<uint8_t>::insert(pos, value)
void VectorInsertU8(uint32_t* vec, void* pos, uint8_t* value)
{
    (void)vec; (void)pos; (void)value;
}

// @ 0x004CEF00  eastl::vector<T>::DoInsertValues / insert(n, value)
void VectorInsertN(uint32_t* vec, uint32_t* pos, uint32_t count, uint32_t* value)
{
    (void)vec; (void)pos; (void)count; (void)value;
}

// @ 0x004CF2C0  eastl::vector<T>::insert(first, last)
void VectorInsertRange(uint32_t* vec, uint32_t* pos, uint32_t count, int value)
{
    (void)vec; (void)pos; (void)count; (void)value;
}
