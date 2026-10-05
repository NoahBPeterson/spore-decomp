// Slice s004cf770: eastl hashtable / fixed-pool internals in the editor code.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
// These are template/hashtable dispatchers whose Ghidra decompiles carry lost locals;
// only compilable skeletons were produced in this pass (partial.txt).
#include "types.h"
#pragma pack(push, 4)

// @ 0x004CF770
void HashtableOp1(uint32_t* self) { (void)self; }
// @ 0x004CFC00
void HashtableOp2(uint32_t* self) { (void)self; }
// @ 0x004D0080
void HashtableOp3(uint32_t* self) { (void)self; }
// @ 0x004D0430
void HashtableFreeBuckets(uint32_t* self, void** buckets, uint32_t count) { (void)self; (void)buckets; (void)count; }
// @ 0x004D04A0
void* PoolAllocate(uint32_t* pool, int size, uint32_t align) { (void)pool; (void)size; (void)align; return 0; }
// @ 0x004D04F0
void HashtableOp4(uint32_t* self) { (void)self; }
