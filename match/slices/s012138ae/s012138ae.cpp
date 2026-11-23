// @ 0x012138ae
extern void ThunkJmp_11e090c();          // 0x011e090c: jmp dword ptr [0x13cc4c4]
struct Thunk_012138ae { void* f_0_012138ae(); };     // opaque: out-of-TU callee
void* FUN_012138ae() { return Thunk_012138ae().f_0_012138ae(); }  // closest C++: still folds or grows
