// Slice s004b0490 — vector (re)allocation helpers.
#include "types.h"

struct V3 { float x, y, z; };
struct B24 { V3 a; V3 b; };

extern void FUN_004b2030(void* a, void** b);
extern void FUN_004b00a0(void* p);
extern void FUN_004b0180(void* p);

struct Vec24 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;

    void Wrapper(void* a, void* b);       // 0x4b0560
    B24* Erase24(B24* dst, B24* end);     // 0x4b0490
    void Other(void* a, void** b);        // 0x4b2030
};

// @ 0x004b0560
void Vec24::Wrapper(void* a, void* b)
{
    void* local[2];
    local[0] = b;
    Other(a, local);
}

// @ 0x004b0490
B24* Vec24::Erase24(B24* param_2, B24* param_3)
{
    B24* out = (B24*)mpEnd;
    B24* local_14 = param_2;
    for (B24* local_10 = param_3; local_10 != out;
         local_10 = (B24*)((char*)local_10 + 0x18)) {
        local_14->b = local_10->b;
        local_14->a = local_10->a;
        local_14 = (B24*)((char*)local_14 + 0x18);
    }
    for (B24* local_1c = local_14; local_1c < (B24*)mpEnd;
         local_1c = (B24*)((char*)local_1c + 0x18)) {
    }
    mpEnd = mpEnd + ((char*)param_3 - (char*)param_2) / 0x18 * -0x18;
    return param_2;
}

// @ 0x004b09b0
struct AutoRef {
    void* mpObject;   // +0x0
    AutoRef* Set(void* v);
};
AutoRef* AutoRef::Set(void* v)
{
    if (v != mpObject) {
        void* old = mpObject;
        if (v != 0) {
            (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)v + 4)))(v);
        }
        mpObject = v;
        if (old != 0) {
            (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)old + 8)))(old);
        }
    }
    return this;
}

// @ 0x004b0590 — 1044-byte reallocation helper (not reconstructed).
void* Grow4(void* self, int n, void** out)
{
    (void)self; (void)n; (void)out;
    return 0;
}

// @ 0x004b0a10 — 1236-byte reallocation helper (not reconstructed).
void* Grow4F(void* self, int n, void** out)
{
    (void)self; (void)n; (void)out;
    return 0;
}

// @ 0x004b0ef0 — 760-byte reallocation helper (not reconstructed).
void* GrowBbox(void* self, int n, void* elem)
{
    (void)self; (void)n; (void)elem;
    return 0;
}
