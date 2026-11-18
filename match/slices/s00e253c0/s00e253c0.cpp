// Slice s00e253c0 - cSPUIPosse heap helper (eastl::pop_heap instantiation over
// intrusive ref-counted pointer pairs).
// Reconstructed from annotated disassembly of 0x00e253c0 / 0x00e23e80 / 0x00e25240.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int u32;
typedef int          s32;

// vtable-call signature typedefs (all thiscall)
typedef void   (__thiscall *TFv)(void*);
typedef void*  (__thiscall *TFpp)(void*, void**);   // FUN_00e23e80(ecx, pair*)
typedef bool   (__cdecl   *TPred)(void*, void*);

// ---- external callees (address in comment) ------------------------------
void* __cdecl FUN_00e23e80(void* self, void** src);   // 0x00e23e80 pair assign

// Intrusive ref-counted pointer: vtable slot 0 = AddRef, slot 1 = Release.
struct IPtr {
  void* p;
  IPtr(const IPtr& o) : p(o.p) { if (p) ((TFv)(*(void***)p)[0])(p); }
  ~IPtr() { if (p) ((TFv)(*(void***)p)[1])(p); }
};

struct Pair {
  IPtr a;
  IPtr b;
};

// 0x00e25240 adjust_heap(first, holeIndex, len, topIndex, value, compare)
void  __cdecl FUN_00e25240(Pair* first, s32 holeIndex, s32 len, s32 topIndex,
                           Pair value, TPred compare);

// ======================================================================
// 0x00e253c0 - pop_heap(first, last, compare): move the last element out,
// copy the root into its slot, then sift the old root down.
// ======================================================================

// @ 0x00e253c0
void __cdecl FUN_00e253c0(Pair* first, Pair* last, TPred compare) {
  Pair* tail = last - 1;
  Pair value = *tail;
  ((TFpp)FUN_00e23e80)(tail, (void**)first);
  FUN_00e25240(first, 0, (s32)(last - first) - 1, 0, value, compare);
}
