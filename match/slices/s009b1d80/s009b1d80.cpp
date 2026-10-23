// Slice s009b1d80 -- FUN_009b1d80, the message-driven visible-set traversal.
//
// The function switches on the low message bits (*msg & 0x801c00) and, for each
// handled code, walks the intrusive chain (Elem::f1fc / Elem::f1f8 /
// Elem::f214) of a 0x468-byte element array (base at mgr+0x384, end at
// mgr+0x388) and appends the surviving element indices to a caller-supplied
// unique array (out/count).  The predicate that decides whether an element is
// appended is the __thiscall helper at 0x9b30e0, which searches the 0x20-entry
// array at elem+0x158 for the message's handle.  The "append if absent" step is
// a helper that MSVC sometimes inlined and sometimes left as an out-of-line
// call (FUN_009b0320), which is why both spellings appear below.
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (default /GS on).
//
// NOTE: this routine (and the callees it drives) were built with whole-program
// optimisation, so the helpers use a register-only calling convention
// ("append unique" takes its three operands in edi/edx/esi) that the stock
// toolchain cannot reproduce; byte-exactness is therefore out of reach and the
// slice is recorded as nonmatching.

#include "types.h"

struct Elem;

// The element collection manager (param_3): a contiguous 0x468-byte element
// array delimited by the base/end pointers at +0x384 / +0x388.
struct Mgr {
    uint8_t pad000[0x384];
    char*   base384;   // +0x384  (element array base)
    char*   end388;    // +0x388  (element array end)
};

// The triggering message (param_5).  Only the low bits of code and the handle
// word are used here.
struct Msg {
    uint32_t code;     // +0x00  (message code, only & 0x801c00 matters)
    uint32_t f04;      // +0x04
    int      handle;   // +0x08
};

// The object at elem+0x150 that owns the 0x20-entry handle array at
// elem+0x158.  Only the __thiscall predicate is exercised.
struct Arr {
    bool FUN_009b30e0(int handle);
};

// A 0x468-byte element of the collection.
struct Elem {
    uint8_t pad000[0x150];
    uint8_t pad150[0x04];
    uint8_t flags154;                 // +0x154  (bit 3 = "already handled")
    uint8_t pad155[0x1f8 - 0x155];
    int     f1f8;                     // +0x1f8
    int     f1fc;                     // +0x1fc  (chain link)
    uint8_t pad200[0x204 - 0x200];
    int     f204;                     // +0x204  (range start)
    int     f208;                     // +0x208  (range count)
    int     f20c;                     // +0x20c  (range count, secondary)
    int     f210;                     // +0x210  (owner id)
    Elem*   f214;                     // +0x214  (linked element)
    uint8_t pad218[0x468 - 0x218];
};

// Out-of-line helper: append `value` to arr/count when not already present.
// Original operand convention: edi = arr, edx = count, esi = value.
extern "C" void FUN_009b0320(int* arr, uint32_t* count, int value);

// Re-entrant sub-traversal for the "nested range" message codes.
extern "C" void FUN_009b05b0(void* elem, int* out, uint32_t* count);

// The inlined spelling of FUN_009b0320 used at the sites MSVC chose to expand.
static __inline void push_unique(int* arr, uint32_t* count, int value)
{
    uint32_t c = *count;
    uint32_t k = 0;
    if (c != 0) {
        do {
            if (arr[k] == value) return;
            k++;
        } while (k < c);
    }
    arr[c] = value;
    ++*count;
}

// ---------------------------------------------------------------------------
// @ 0x009b1d80
// ---------------------------------------------------------------------------
void FUN_009b1d80(int* param_1, uint32_t* param_2, Mgr* param_3, Elem* param_4, Msg* param_5)
{
    Elem* elem = param_4;
    int* out = param_1;
    uint32_t* count = param_2;
    int n = (int)((param_3->end388 - param_3->base384) / 0x468);
    int first = elem->f1f8;

    switch (param_5->code & 0x801c00) {

    case 0x800: {
        // Append the 3rd-from-last (or last) unflagged element.
        int i = elem->f1fc;
        if (i >= 0 && i < n) {
            --*count;
            int a = i;
            int b = i;
            int c = 0;
            do {
                if (i >= n) break;
                Elem* e = (Elem*)(param_3->base384 + i * 0x468);
                if (e->flags154 & 8) break;
                b = a;
                a = i;
                i = e->f1fc;
                c++;
            } while (i >= 0);
            if (c >= 3) {
                FUN_009b0320(out, count, b);
            } else {
                FUN_009b0320(out, count, a);
            }
        }
        return;
    }

    case 0x400: {
        // Append a parity-selected element of the chain.
        int i = first;
        if (i >= 0 && i < n) {
            --*count;
            int a = i;
            int b = i;
            int c = 0;
            do {
                if (i >= n) break;
                Elem* e = (Elem*)(param_3->base384 + i * 0x468);
                if (e->flags154 & 8) break;
                if (c % 2 != 0) {
                    b = a;
                    a = ((Elem*)(param_3->base384 + a * 0x468))->f1fc;
                }
                i = e->f1fc;
                c++;
            } while (i >= 0);
            if (c % 2 == 0) a = b;
            FUN_009b0320(out, count, a);
        }
        return;
    }

    case 0xc00: {
        // Append the last unflagged element of the chain.
        int i = elem->f1fc;
        if (i >= 0 && i < n) {
            --*count;
            int a = i;
            do {
                if (i >= n) break;
                Elem* e = (Elem*)(param_3->base384 + i * 0x468);
                if (e->flags154 & 8) break;
                a = i;
                i = e->f1fc;
            } while (i >= 0);
            FUN_009b0320(out, count, a);
        }
        return;
    }

    case 0x1000: {
        // Append the chain terminus (first flagged / negative link).
        int i = elem->f1fc;
        if (i >= 0 && i < n) {
            --*count;
            do {
                if (i >= n) break;
                Elem* e = (Elem*)(param_3->base384 + i * 0x468);
                if (e->flags154 & 8) break;
                i = e->f1fc;
            } while (i >= 0);
            FUN_009b0320(out, count, i);
        }
        return;
    }

    case 0x1400: {
        // Append every unflagged element of the whole chain.
        int i = elem->f1fc;
        if (i >= 0) {
            for (;;) {
                if (i >= n) return;
                Elem* e = (Elem*)(param_3->base384 + i * 0x468);
                if (e->flags154 & 8) return;
                uint32_t c = *count;
                uint32_t k = 0;
                if (c != 0) {
                    do {
                        if (out[k] == i) goto L1400_next;
                        k++;
                    } while (k < c);
                }
                out[c] = i;
                ++*count;
            L1400_next:
                i = e->f1fc;
                if (i < 0) return;
            }
        }
        return;
    }

    case 0x1800: {
        // Walk the target element's primary range and append the entries the
        // message predicate accepts.
        --*count;
        Elem* t = elem;
        Elem* p = elem->f214;
        if (p != 0 && p->f210 == elem->f210) {
            t = p;
        } else if (((Arr*)((char*)elem + 0x150))->FUN_009b30e0(param_5->handle)) {
            FUN_009b0320(out, count, elem->f1f8);
        }
        int i = t->f204;
        int end = t->f20c + i;
        if (i == end) return;
        int off = i * 0x468;
        do {
            Elem* e = (Elem*)(param_3->base384 + off);
            if (((Arr*)((char*)e + 0x150))->FUN_009b30e0(param_5->handle)) {
                push_unique(out, count, i);
            }
            i++;
            off += 0x468;
        } while (i != end);
        return;
    }

    case 0x800000: {
        // Hand the owning (or linked) element to the sub-traversal.
        --*count;
        Elem* t = elem;
        Elem* p = elem->f214;
        if (p != 0 && p->f210 == elem->f210) t = p;
        FUN_009b05b0(t, out, count);
        return;
    }

    case 0x1c00:
    case 0x800400: {
        // Nested traversal over the grandchild element's chain and (for
        // 0x800400) its secondary ranges.
        --*count;
        Elem* p = elem->f214;
        if (p == 0) return;
        Elem* g = p->f214;
        if (g == 0) return;
        int next = g->f1f8;
        int prev = elem->f1fc;
        bool deep = ((param_5->code & 0x801c00) == 0x800400);
        if (next == -1) return;
        for (;;) {
            int i = next;
            Elem* e = (Elem*)(param_3->base384 + i * 0x468);
            if (((Arr*)((char*)e + 0x150))->FUN_009b30e0(param_5->handle)) {
                push_unique(out, count, i);
            }
            int r0 = e->f204;
            int r1 = e->f208 + r0;
            int cur = r0;
            if (r0 != r1) {
                int off = r0 * 0x468;
                do {
                    if (cur != prev) {
                        Elem* f = (Elem*)(param_3->base384 + off);
                        if (((Arr*)((char*)f + 0x150))->FUN_009b30e0(param_5->handle)) {
                            push_unique(out, count, cur);
                        }
                        if (deep) {
                            int s0 = f->f204;
                            int s1 = f->f20c + s0;
                            int j = s0;
                            if (s0 != s1) {
                                int off2 = s0 * 0x468;
                                do {
                                    Elem* h = (Elem*)(param_3->base384 + off2);
                                    if (((Arr*)((char*)h + 0x150))->FUN_009b30e0(param_5->handle)) {
                                        push_unique(out, count, j);
                                    }
                                    j++;
                                    off2 += 0x468;
                                } while (j != s1);
                            }
                        }
                    }
                    cur++;
                    off += 0x468;
                } while (cur != r1);
            }
            Elem* link = (Elem*)(param_3->base384 + i * 0x468);
            prev = i;
            next = link->f1fc;
            if (next == -1) return;
        }
    }

    default:
        return;
    }
}
