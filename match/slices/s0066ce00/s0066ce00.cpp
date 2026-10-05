// Slice s0066ce00: SP::cSPUIFeedListItem-adjacent feed/list refresh + layout builders.
// Represented in outline only (see partial.txt).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl SP_PropertyManager();               // 0x0067de30
void* __cdecl SP_GetPropertyAsKey(void* p, unsigned key, void* out); // 0x006a1250
void  __cdecl SPUIHelpers_SetWindowImage(void* w, void* key, int a); // 0x00807bb0
void  __cdecl EASTL_allocator_deallocate(void* p);
void* __cdecl cSPUILayout_FindWindow(void* self, unsigned id, int flag);

// @ 0x0066ce00
void __fastcall FUN_0066ce00(void* self) { (void)self; }
// @ 0x0066d280
void __fastcall FUN_0066d280(void* self) { (void)self; }
// @ 0x0066d430
void __fastcall FUN_0066d430(void* self) { (void)self; }
