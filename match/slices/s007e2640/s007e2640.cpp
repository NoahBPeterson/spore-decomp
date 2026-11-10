// Slice s007e2640 -- console command: take the first main argument of a
// console command (cConsoleCommandArgs::MainArguments(1)[0]) and assign it to the
// string field at this->m0c + 0x68.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)

// ---- callees ---------------------------------------------------------------
struct ConsoleCommandArgs_007e2640 {
    const char** MainArguments(int index);          // 0x00838320 (thiscall, ret 4)
};

struct StringAssign_007e2640 {                      // 0x00454cb0 (thiscall, ret 8)
    void assign(const char* first, const char* last);
};

struct Self_007e2640 {
    char pad[0x0c];
    char* m0c;                                      // +0x0c
    void SetArg(ConsoleCommandArgs_007e2640* args);
};

// @ 0x007e2640
void Self_007e2640::SetArg(ConsoleCommandArgs_007e2640* args)
{
    const char* s = args->MainArguments(1)[0];
    const char* end = s + strlen(s);
    ((StringAssign_007e2640*)(m0c + 0x68))->assign(s, end);
}
