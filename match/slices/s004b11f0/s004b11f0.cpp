// Slice s004b11f0 — vector element (de)allocation helpers.
#include "types.h"

struct AutoRef {
    void* mpObject;   // +0x0
    AutoRef* Set(void* v);
};

// @ 0x004b22b0
void FillAutoRef(AutoRef* first, AutoRef* last, void** value)
{
    void* old;
    for (; first != last; ++first) {
        void* v = *value;
        if (v != first->mpObject) {
            old = first->mpObject;
            if (v != 0) {
                (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)v + 4)))(v);
            }
            first->mpObject = v;
            if (old != 0) {
                (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)old + 8)))(old);
            }
        }
    }
}

// @ 0x004b2220
void** UninitCopyAutoRef(void** out, void** first, void** last, void** dest)
{
    for (; first != last; ++first) {
        if (dest != 0) {
            *dest = *first;
            if (*dest != 0) {
                (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)*dest + 4)))(*dest);
            }
        }
        ++dest;
    }
    *out = dest;
    return out;
}

// @ 0x004b11f0 — 1293-byte reallocation helper (not reconstructed).
void* Grow194(void* self, int n, void* elem)
{
    (void)self; (void)n; (void)elem;
    return 0;
}

// @ 0x004b1800 — 1211-byte reallocation helper (not reconstructed).
void* Grow24(void* self, int n, void* elem)
{
    (void)self; (void)n; (void)elem;
    return 0;
}

// @ 0x004b1cc0 — 656-byte reallocation helper (not reconstructed).
void* GrowRef(void* self, int n, void* elem)
{
    (void)self; (void)n; (void)elem;
    return 0;
}

// @ 0x004b2030 — 484-byte helper (not reconstructed).
void* CopyRefRange(void* self, void** args)
{
    (void)self; (void)args;
    return 0;
}
