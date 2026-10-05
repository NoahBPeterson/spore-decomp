// w1g1 slice s004f85b0 -- Skinner aligned-allocator helpers and creature
// ability destructors.  Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
void* Alloc(uint32_t size, const char* name, int, int, int, int);
void  Dealloc(void* p);

// ===========================================================================
// @ 0x004f8750  (MATCH)
// Aligned allocation wrapper: 16-byte-aligns the block and stamps a header.
// ===========================================================================
void* FUN_004f8750(int size, int param2)
{
    int v33, n40, len;
    v33 = (int)Alloc((uint32_t)(size + 0x1f), "Skinner/AlignedAlloc", 0, 0, 0, 0);
    len = (v33 + 0xf) & 0xfffffff0;
    n40 = len;
    *(int*)(n40) = 0xd6d6d6d6;
    *(int*)(n40 + 4) = v33;
    *(int*)(n40 + 8) = param2;
    *(int*)(n40 + 0xc) = 0x29292929;
    n40 += 0x10;
    return (void*)n40;
}

// ===========================================================================
// @ 0x004f87f0  (complete; not byte-exact)  creature-ability destructor tail.
// ===========================================================================
void FUN_004fc320(void* p, int);
void FUN_004f80b0(void* p);
void FUN_004c0b80(void* p);
extern int g_vtbl_13f1140;
extern int g_vtbl_13ef094;

void __fastcall FUN_004f87f0(int* self)
{
    self[0] = (int)&g_vtbl_13f1140;
    FUN_004fc320(self, 1);
    Dealloc((void*)self[0x15]);
    FUN_004f80b0((void*)self[0x12]);
    FUN_004f80b0((void*)self[7]);
    for (uint32_t i = (uint32_t)self[0x16]; i < (uint32_t)self[0x17]; i += 4) {
    }
    FUN_004c0b80(&self[0x16]);
    self[0] = (int)&g_vtbl_13ef094;
}

// ===========================================================================
// @ 0x004f8880  (complete; not byte-exact)  aligned pool allocator.
// ===========================================================================
void* FUN_00928a30(int, int, int, int, int, int, int, int);
void FUN_004fc610(void* pool, int* p);

void* __fastcall FUN_004f8880(int* self, int, int size, int param3)
{
    size = (size + 0x10 + 0xf) & 0xfffffff0;
    int local8 = self[0xf0 / 4];
    if ((uint32_t)self[0xf4 / 4] < (uint32_t)size) {
        int chunk = (size > 0x8000) ? size : 0x8000;
        local8 = (int)FUN_00928a30(chunk, 0x10, 0, 0, 0, 0, 0, 0);
        FUN_004fc610((char*)self + 0x58, &local8);
        self[0xf0 / 4] = local8;
        self[0xf4 / 4] = chunk;
    }
    self[0xf0 / 4] += size;
    self[0xf4 / 4] -= size;
    int* p = (int*)((local8 + 0xf) & 0xfffffff0);
    p[0] = 0xd6d6d6d6;
    p[1] = local8;
    p[2] = param3;
    p[3] = 0x29292929;
    return p + 4;
}

// ===========================================================================
// @ 0x004f89a0  (complete; not byte-exact)  local-light vector destructor.
// ===========================================================================
void FUN_004769b0(void* first, void* last);
extern void* g_16c8b44;
struct Light { void Destroy(); };

void __fastcall FUN_004f89a0(int self)
{
    int i;
    int count = (*(int*)(self + 0x5c) - *(int*)(self + 0x58)) >> 2;
    for (i = 0; i < count; i++) {
        int* p = *(int**)(self + 0x58);
        ((Light*)g_16c8b44)->Destroy();
        (void)p;
    }
    FUN_004769b0(*(void**)(self + 0x58), *(void**)(self + 0x5c));
    *(int*)(self + 0xf0) = 0;
    *(int*)(self + 0xf4) = 0;
}

// ===========================================================================
// @ 0x004f8d80  (complete; not byte-exact)  weighted distance sum.
// ===========================================================================
float FUN_004f8e20(int, void*);
void* FUN_004f8f70(int this_, int p2);

void __fastcall FUN_004f8d80(int self, int, int p2, float* out)
{
    float sum = -*(float*)(self + 0xc);
    void* table = FUN_004f8f70(self, p2);
    if (table != 0) {
        uint32_t n = *(uint32_t*)((char*)table - 8);
        for (uint32_t i = 0; i < n; i++)
            sum += FUN_004f8e20((int)((char*)table + (i << 7)), (void*)p2);
    }
    *out = sum;
}

// ===========================================================================
// @ 0x004f85b0  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f85b0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f8e20  (INCOMPLETE skeleton)
// ===========================================================================
float FUN_004f8e20(int a, void* b)
{
    (void)a; (void)b;
    return 0.0f;
}

// ===========================================================================
// @ 0x004f8f70  (INCOMPLETE skeleton)
// ===========================================================================
void* FUN_004f8f70(int a, int b)
{
    (void)a; (void)b;
    return 0;
}

// ===========================================================================
// @ 0x004f90a0  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f90a0(int a, int b)
{
    (void)a; (void)b;
}

// ===========================================================================
// @ 0x004f9180  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f9180(int a, int b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f9250  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f9250(int a, int b)
{
    (void)a; (void)b;
}

// ===========================================================================
// @ 0x004f9360  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f9360(int a, int b, void* c)
{
    (void)a; (void)b; (void)c;
}
