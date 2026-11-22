// Forward declaration for slice s0079e950's free function 0x0079f7b0.
//
// tools/migrate/rewrite.py emits a prototype of the slice's free function
// `void ReleaseAndClear(RefVec* v);` in front of the first local stub whose
// text names it.  That stub is `struct RefVec` itself (it declares a member
// `void ReleaseAndClear();`), so the prototype lands before RefVec's
// definition and the TU fails with C2065 'RefVec'.  This header is included
// from the preamble (through the manual `externs` entry for g_formatMask in
// work/migrate/renames_s0079e950.json) so the name is declared first.
// Remove it once rewrite.py skips a member declaration when it looks for a
// free function's callers.
struct RefVec;
