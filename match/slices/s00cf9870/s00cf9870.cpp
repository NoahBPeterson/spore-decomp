// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>

extern char g_1478994[];          // 0x01478994
extern void* vtbl_01478948;       // 0x01478948

void* operator_new_dbg(unsigned n, const char* tag, int a, int b, int c, int d); // 0x00f473a0

struct cCommandBase {
    void** mpVtbl;
    int m4;
    int m8;
    cCommandBase();               // 0x0083c800
};

struct Cmd : cCommandBase {
    int mC;
    Cmd() { mpVtbl = &vtbl_01478948; }
};

void* CheatManager();             // 0x0067de20
void LoadFormulas();              // 0x00ceec60

// @ 0x00cf9870
void FUN_00cf9870()
{
    void* raw = operator_new_dbg(0x10, g_1478994, 0, 0, 0, 0);
    if (raw)
        new (raw) Cmd();
    (void)CheatManager();
    LoadFormulas();
}
