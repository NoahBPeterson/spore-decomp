// @ 0x0120be3a
extern void ThunkJmp_11e090c();          // 0x011e090c: jmp dword ptr [0x13cc4c4]
struct Thunk_0120be3a { void* f_0_0120be3a(); };     // opaque: out-of-TU callee
void* FUN_0120be3a() { return Thunk_0120be3a().f_0_0120be3a(); }  // closest C++: still folds or grows
