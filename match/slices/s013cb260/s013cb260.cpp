// Slice s013cb260: tail of the engine shutdown module (MSVC 2008 SP1, /O2):
// TLS cleanup, refcounted-singleton destructor thunks and small static teardowns.
#include "types.h"

extern "C" __declspec(dllimport) int __stdcall TlsFree(unsigned long);
typedef int(__stdcall* TlsFreeFn)(unsigned long);

extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void*);

struct Method { void M(); };
struct MethodI { void M(int); };

extern void __cdecl cdecl_f11eaa80();
extern void __cdecl cdecl_f11eaad0();

extern int g_16e42b4;   // TLS slot array (last element)
extern int g_16e42b8;
extern int g_16f2974;
extern int g_16f2978;
extern int* g_16f4998;
extern char g_16f4e18[];
extern char g_16f4e98[];
extern char g_15d07c0[];
extern char g_170a6b9[];
extern char g_170a79c[];

// @ 0x013CB260
void f_013cb260() {
    TlsFreeFn pf = TlsFree;
    int* p = &g_16e42b4;
    unsigned n = 5;
    do {
        p--;
        pf(*p);
    } while (--n);
}

// @ 0x013CB290
void f_013cb290() { TlsFree(g_16e42b8); }

// @ 0x013CB300
void f_013cb300() {
    int n = g_16f2974;
    --n;
    g_16f2974 = n;
    if (n == 0) cdecl_f11eaa80();
}

// @ 0x013CB320
void f_013cb320() {
    int n = g_16f2978;
    --n;
    g_16f2978 = n;
    if (n == 0) cdecl_f11eaad0();
}

// @ 0x013CB370
// Clears a global dynamic array: stores -1 and 0 in its first two slots, memmoves the
// remaining (count*2 - 2) dwords down by two, then zeroes the table's live count.
void f_013cb370() {
    int* p = g_16f4998;
    if (p) {
        int* d = (int*)p[0];
        int n = p[1];
        if (d < d + n * 2) {
            int* end = d + n * 2;
            d[0] = -1;
            d[1] = 0;
            unsigned cnt = (unsigned)((char*)end - (char*)d - 1) >> 2 & 0x3ffffffe;
            int* q = d + 2;
            while (cnt--) *q++ = *d++;
        }
        p[2] = 0;
    }
}

// @ 0x013CB620
void f_013cb620() {
    ((MethodI*)g_16f4e18)->M(1);
    DeleteCriticalSection(g_16f4e98);
}

// @ 0x013CB780
struct S8 { int a; unsigned char b; char pad[3]; };

void f_013cb780() {
    S8* p = (S8*)g_15d07c0;
    unsigned n = 2;
    do {
        p--;
        p->a = 0;
        p->b = 0;
    } while (--n);
}

// @ 0x013CB7D0
void f_013cb7d0() { ((Method*)g_170a6b9)->M(); }

// @ 0x013CB850
void f_013cb850() { ((Method*)g_170a79c)->M(); }
