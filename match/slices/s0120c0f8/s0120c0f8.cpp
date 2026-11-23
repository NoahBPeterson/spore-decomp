// @ 0x0120c0f8
extern void ThunkJmp_11e090c();          // 0x011e090c: jmp dword ptr [0x13cc4c4]
struct Thunk_0120c0f8 { void* f_0_0120c0f8(); };     // opaque: out-of-TU callee
void* FUN_0120c0f8() { return Thunk_0120c0f8().f_0_0120c0f8(); }  // closest C++: still folds or grows
