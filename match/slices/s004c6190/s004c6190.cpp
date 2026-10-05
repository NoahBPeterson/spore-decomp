// Slice s004c6190: EASTL vector<bool>/allocator helpers and editor tasks (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"
#pragma pack(push, 4)

// @ 0x004c6190  PARTIAL: vector<bool> reallocation/assign (822B).
void Editor_VecBool6190(void* self) { (void)self; }
// @ 0x004c64d0  PARTIAL: allocator-free helper (72B).
void Editor_Free64d0(void* p) { (void)p; }
// @ 0x004c6520  PARTIAL: helper (64B).
void Editor_Do6520(void* self) { (void)self; }
// @ 0x004c6560  PARTIAL: vector<bool>::insert (1093B).
void Editor_VecBoolInsert6560(void* self) { (void)self; }
// @ 0x004c69b0  PARTIAL: 3-arg trampoline (34B).
void Editor_Tramp69b0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x004c69e0  PARTIAL: helper (135B).
void Editor_Do69e0(void* self) { (void)self; }
// @ 0x004c6a70  PARTIAL: allocator-free helper (104B).
void Editor_Free6a70(void* p) { (void)p; }
// @ 0x004c6ae0  PARTIAL: uninitialized-fill helper (78B).
void Editor_Fill6ae0(void* a, void* b, void* c, void* d) { (void)a;(void)b;(void)c;(void)d; }
// @ 0x004c6b30  PARTIAL: uninitialized-copy helper (79B).
void Editor_Copy6b30(void* a, void* b, void* c, void* d) { (void)a;(void)b;(void)c;(void)d; }
// @ 0x004c6ba0  PARTIAL: refcounted release (540B).
void Editor_Release6ba0(void* self) { (void)self; }

#pragma pack(pop)
