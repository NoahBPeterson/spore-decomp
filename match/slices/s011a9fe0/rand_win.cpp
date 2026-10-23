// crypto/rand/rand_win.c (OpenSSL 0.9.8g), compiled verbatim.
//
//   // @ 0x011aa2e0 RAND_poll
//
// The one deviation from the shipped 0.9.8g text is the message-queue mask.
// The original was built against a Platform SDK whose QS_ALLEVENTS covered
// QS_RAWINPUT (0x400), i.e. 0x04bf; the SDK shipped with this toolchain
// defines it as 0x00bf. Re-define it before the translation unit is pulled in
// so the emitted `push` immediate matches the original.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011b8e10_inc /Iwork/third_party/build/openssl-0.9.8g-d2110920/crypto/rand
#include <windows.h>
#undef QS_ALLEVENTS
#define QS_ALLEVENTS 0x04bf
#include "../../../work/third_party/build/openssl-0.9.8g-d2110920/crypto/rand/rand_win.c"
