// @ 0x0121577b
extern void ThunkJmp_11e090c();          // 0x011e090c: jmp dword ptr [0x13cc4c4]
struct Thunk_0121577b { void* f_0_0121577b(); };     // opaque: out-of-TU callee
void* FUN_0121577b() { return Thunk_0121577b().f_0_0121577b(); }  // closest C++: still folds or grows
