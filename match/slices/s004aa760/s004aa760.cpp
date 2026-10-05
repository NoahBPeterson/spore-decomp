// Slice s004aa760 — Spore editor container/iterator helpers (x87, /Od /Ob1).
#include "types.h"
#include <new>

// ---------- shared stub types ----------
struct V3 { float x, y, z; };
struct Item { float a; V3 b; };

struct Matrix3Like { char pad[0x24]; Matrix3Like(const Matrix3Like&); };

struct DequeIt {
    uint8_t* cur;    // +0x0
    uint8_t* first;  // +0x4
    uint8_t* last;   // +0x8
    uint8_t** node;  // +0xc
    DequeIt* Inc();  // 0x4ab210
};

struct DequeBase {
    void* p0;      // +0x0
    uint32_t p1;   // +0x4
    void* p2;      // +0x8
    void* p3;      // +0xc
    char pad[0x18 - 0x10];
    char* p18;     // +0x18
    char* p1c;     // +0x1c
    char pad2[0x28 - 0x20];
    char alloc[8]; // +0x28
    void* AllocNode();  // 0x4ab320
    void* DequeAlloc(unsigned int n);  // 0x4ab350
};

extern void* FUN_0056a240(unsigned int n);
extern void* FUN_00569340(void* p);
extern void* FUN_0042dee0(void* p, int size, int align, int flags);
extern void FUN_00503470(int a, int b);
extern void FUN_0040ce80(void* p);
extern void FUN_004aa2f0(void* dst, void* src);

// @ 0x004ab210
DequeIt* DequeIt::Inc()
{
    cur += 4;
    if (cur == last) {
        node += 1;
        first = *node;
        last = first + 0x100;
        cur = first;
    }
    return this;
}

// @ 0x004ab320
void* DequeBase::AllocNode()
{
    return FUN_0042dee0((char*)this + 0x28, 0x100, 4, 0);
}

// @ 0x004ab450
uint32_t** FillU32(uint32_t** out, uint32_t* param_dst, int param_count, uint32_t* param_src)
{
    int count = param_count;
    uint32_t* dst = param_dst;
    uint32_t v = *param_src;
    while (count--) *dst++ = v;
    *out = dst;
    return out;
}

// @ 0x004ab4a0
extern void FUN_004ab5b0(Item* begin, Item* end, Item* out);
void CopyItemsWrapper(Item* a, Item* b, Item* c)
{
    bool local = false;
    FUN_004ab5b0(a, b, c);
}

// @ 0x004ab5b0
Item* CopyItems(Item* begin, Item* end, Item* out)
{
    for (; begin != end; ++begin, ++out) {
        if (out != 0) {
            out->a = begin->a;
            out->b = begin->b;
        }
    }
    return out;
}

// @ 0x004ab4d0
Matrix3Like* CopyMatrixRange(Matrix3Like* param_1, Matrix3Like* param_2, Matrix3Like* param_3)
{
    Matrix3Like* local_48 = param_3;
    for (Matrix3Like* local_44 = param_1; local_44 != param_2;
         local_44 = (Matrix3Like*)((char*)local_44 + 0x34)) {
        if (local_48 != 0) {
            new (local_48) Matrix3Like(*local_44);
        }
        local_48 = (Matrix3Like*)((char*)local_48 + 0x34);
    }
    return local_48;
}

// @ 0x004ab530
struct Big34 { uint32_t d[0xf]; };
Big34* CopyBig34Range(Big34* param_1, Big34* param_2, Big34* param_3)
{
    Big34* local_4c = param_3;
    for (Big34* local_48 = param_1; local_48 != param_2;
         local_48 = (Big34*)((char*)local_48 + 0x3c)) {
        if (local_4c != 0) {
            local_4c->d[0] = local_48->d[0];
            FUN_0040ce80((char*)local_48 + 4);
        }
        local_4c = (Big34*)((char*)local_4c + 0x3c);
    }
    return local_4c;
}

// @ 0x004ab280
struct M36 { char pad[0x24]; };
M36* CopyM36Range(M36* param_1, M36* param_2, M36* param_3)
{
    M36* local_44 = param_3;
    for (M36* local_40 = param_1; local_40 != param_2;
         local_40 = (M36*)((char*)local_40 + 0x24)) {
        if (local_44 != 0) {
            *(M36*)local_44 = *(M36*)local_40;
        }
        local_44 = (M36*)((char*)local_44 + 0x24);
    }
    for (M36* local_4c = param_1; local_4c != param_2;
         local_4c = (M36*)((char*)local_4c + 0x24)) {
    }
    return local_44;
}

// @ 0x004ab130
struct RefC {
    void* p0;    // +0x0
    char pad0[4];
    void* p8;    // +0x8
    void* p10;   // +0x10
    void* p14;   // +0x14
    void* p18;   // +0x18
    void* p1c;   // +0x1c
    void* AllocNode();  // 0x4ab320
    void* Func(void* param_2);
};
void* RefC::Func(void* param_2)
{
    void* v = *(void**)param_2;
    if (p14 == p0) {
        FUN_00503470(1, 0);
    }
    void* a = AllocNode();
    *(void**)((char*)p14 - 4) = a;
    FUN_00569340((char*)p14 - 4);
    p8 = (char*)p10 - 4;
    void* r = p8;
    if (r != 0) {
        *(void**)r = v;
    }
    return r;
}

// @ 0x004ab350
void* DequeBase::DequeAlloc(unsigned int param_2)
{
    unsigned int local_18 = (param_2 >> 6) + 1;
    unsigned int local_8 = 8;
    unsigned int local_1c = (param_2 >> 6) + 3;
    unsigned int* local_28;
    if (local_1c < 9) local_28 = &local_8;
    else local_28 = &local_1c;
    p1 = *local_28;
    void* node = FUN_0056a240(p1);
    p0 = node;
    uint32_t* local_10 = (uint32_t*)((char*)node + (((p1 - local_18) >> 1) * 4));
    uint32_t* local_14 = local_10 + local_18;
    for (uint32_t* local_c = local_10; local_c < local_14; ++local_c) {
        *local_c = (uint32_t)AllocNode();
    }
    FUN_00569340(local_10);
    p2 = p3;
    FUN_00569340(local_14 - 1);
    p18 = p1c + (param_2 % 0x40) * 4;
    return this;
}

// ---------- large routines (not reconstructed) ----------
void FUN_004aa760(void* a) { (void)a; }
void FUN_004aaac0(void* a) { (void)a; }
void FUN_004aae30(void* a) { (void)a; }
