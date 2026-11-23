// @ 0x00a272e0
// tail-call thunk: jmp 0xa26da0 (?VecDtor_26da0@AudioSystem_s00a2_5c40@@QAEXXZ), ecx passes through
struct AudioSystem_s00a2 {
  static void __stdcall VecDtor_00a26da0();   // 0xa26da0 __thiscall in retail; spelled static so a member
};                                            // call passes ecx untouched and the name claims the address
void AudioSystemThunk_00a272e0() { AudioSystem_s00a2::VecDtor_00a26da0(); }
