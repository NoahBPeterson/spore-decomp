/* Coverage runtime for the hybrid build (tools/hybrid/build.py --coverage).
 *
 * build.py plants a one-shot `int3` at every function entry, keeps the original byte in a table,
 * points the PE entry at cov_entry, and makes the code sections writable. On each breakpoint the
 * vectored handler restores the byte, records the first-hit time, and resumes at the same address;
 * a thread writes the table to a file every few seconds. No CRT: every API goes through the
 * image's own IAT slots (absolute addresses below) or GetProcAddress.
 *
 * Compiled with the project's cl (VC9) as a plain object; build.py places it like a slice. */

typedef unsigned int u32;
typedef unsigned char u8;

#define IAT_GetProcAddress   0x013cc0bc
#define IAT_GetModuleHandleA 0x013cc0c0
#define IAT_CloseHandle      0x013cc0c4
#define IAT_CreateFileA      0x013cc0cc
#define IAT_GetTickCount     0x013cc130
#define IAT_CreateThread     0x013cc1b0
#define IAT_WriteFile        0x013cc23c
#define IAT_Sleep            0x013cc284

typedef void *(__stdcall *PFN_GetProcAddress)(void *, const char *);
typedef void *(__stdcall *PFN_GetModuleHandleA)(const char *);
typedef int (__stdcall *PFN_CloseHandle)(void *);
typedef void *(__stdcall *PFN_CreateFileA)(const char *, u32, u32, void *, u32, u32, void *);
typedef u32 (__stdcall *PFN_GetTickCount)(void);
typedef void *(__stdcall *PFN_CreateThread)(void *, u32, void *, void *, u32, u32 *);
typedef int (__stdcall *PFN_WriteFile)(void *, const void *, u32, u32 *, void *);
typedef void (__stdcall *PFN_Sleep)(u32);
typedef void *(__stdcall *PFN_AddVEH)(u32, void *);

#define API(T, slot) (*(T *)(slot))

struct ExcRecord { u32 code, flags; void *record, *address; };
struct ExcPointers { struct ExcRecord *rec; u8 *ctx; };
#define CTX_EIP 0xB8

/* Filled by build.py after placement (all pointers into .hybd). The header is also the file
 * header of the dump: magic, n, t0 and hits, followed by tick[n]. */
struct CovTab {
    u32 magic;      /* 'SCOV' */
    u32 n;          /* number of breakpoints */
    u32 t0;         /* GetTickCount at entry */
    u32 hits;       /* breakpoints hit so far */
    u32 *bp;        /* sorted breakpoint addresses */
    u8 *orig;       /* original first byte of each */
    u32 *tick;      /* first-hit time (ms since t0, +1 so 0 means never) */
    u32 oep;        /* where to continue after init */
    u32 period_ms;  /* flush interval */
    char path[64];  /* output file (relative to the game's cwd) */
};

struct CovTab g_cov = { 0x564F4353 };   /* initialised so it lands in .data (-> .hybd), not COMMON; build.py pokes the fields */

static long __stdcall cov_handler(struct ExcPointers *ep)
{
    u32 a, lo, hi, mid;
    if (ep->rec->code != 0x80000003)
        return 0;                                   /* EXCEPTION_CONTINUE_SEARCH */
    a = (u32)ep->rec->address;
    lo = 0; hi = g_cov.n;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        if (g_cov.bp[mid] < a) lo = mid + 1; else hi = mid;
    }
    if (lo >= g_cov.n || g_cov.bp[lo] != a)
        return 0;                                   /* somebody else's int3 */
    *(u8 *)a = g_cov.orig[lo];                      /* code sections are writable in this build */
    if (!g_cov.tick[lo]) {
        g_cov.tick[lo] = API(PFN_GetTickCount, IAT_GetTickCount)() - g_cov.t0 + 1;
        g_cov.hits++;
    }
    *(u32 *)(ep->ctx + CTX_EIP) = a;
    return -1;                                      /* EXCEPTION_CONTINUE_EXECUTION */
}

static void cov_flush(void)
{
    void *h = API(PFN_CreateFileA, IAT_CreateFileA)(g_cov.path, 0x40000000u /*GENERIC_WRITE*/, 1 /*FILE_SHARE_READ*/,
                                                    0, 2 /*CREATE_ALWAYS*/, 0x80 /*NORMAL*/, 0);
    u32 w;
    if (h == (void *)-1)
        return;
    API(PFN_WriteFile, IAT_WriteFile)(h, &g_cov, 16, &w, 0);
    API(PFN_WriteFile, IAT_WriteFile)(h, g_cov.tick, g_cov.n * 4, &w, 0);
    API(PFN_CloseHandle, IAT_CloseHandle)(h);
}

static u32 __stdcall cov_thread(void *arg)
{
    u32 last = (u32)-1;
    (void)arg;
    for (;;) {
        API(PFN_Sleep, IAT_Sleep)(g_cov.period_ms);
        if (g_cov.hits != last) {
            last = g_cov.hits;
            cov_flush();
        }
    }
}

void __cdecl cov_entry(void)
{
    void *k32 = API(PFN_GetModuleHandleA, IAT_GetModuleHandleA)("kernel32.dll");
    PFN_AddVEH add = (PFN_AddVEH)API(PFN_GetProcAddress, IAT_GetProcAddress)(k32, "AddVectoredExceptionHandler");
    g_cov.t0 = API(PFN_GetTickCount, IAT_GetTickCount)();
    if (add)
        add(1, (void *)cov_handler);
    API(PFN_CreateThread, IAT_CreateThread)(0, 0, (void *)cov_thread, 0, 0, 0);
    ((void (*)(void))g_cov.oep)();
}
