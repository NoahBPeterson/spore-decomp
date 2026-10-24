// Slice s00c0fa70 - cAnimatable / cAnimationRemapping helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

void* __cdecl FUN_009ff6f0(void*, void*);   // 0x009ff6f0
void  __cdecl FUN_0093aa70(void*, void*, int, int);  // 0x0093aa70 WriteUint32
void  __cdecl FUN_0093a780(void*, void*, int, int);  // 0x0093a780 ReadInt32
void  __cdecl FUN_0093ac80(void*);                   // 0x0093ac80 ReadBool
void  __cdecl FUN_0093a9a0(void*, void*, int);       // 0x0093a9a0 operator<<
void  __cdecl FUN_00c0b030(void*, void*);            // 0x00c0b030
void  __cdecl FUN_00bca810(int, int, void*, float, void*, int); // 0x00bca810
void* __cdecl FUN_0067de30();                        // 0x0067de30 SP::PropertyManager
void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int); // 0x00f473a0 operator_new
void  __cdecl FUN_00c10050(uint32_t, int, int, int, char); // 0x00c10050
void  __cdecl FUN_00c10230(int, int, int, int);      // 0x00c10230

struct F_a01f10 { void  __thiscall f(int, int); };   // 0x00a01f10
struct F_a047d0 { void  __thiscall f(int); };        // 0x00a047d0
struct F_f9b0   { char* __thiscall f(int, void*); }; // 0x00c0f9b0

#define G32(a)  (*(uint32_t*)(a))
#define GF(a)   (*(float*)(a))

// One binding slot of the cAnimatable binding array (0x24 bytes).
struct AnimBinding {
    uint32_t id;        // +0x00
    int32_t  maskBit;   // +0x04  bit index into the lookup mask (0 = empty slot)
    uint32_t f08;       // +0x08
    uint32_t f0c;       // +0x0c
    uint32_t f10;       // +0x10
    float    weight;    // +0x14
    char     flags;     // +0x18
    int32_t  handle;    // +0x1c
    void*    target;    // +0x20
};

struct CAN {
    char         _pad0[0xb48];
    void*        playCtx;    // +0xb48  animation play context (thiscall receiver)
    char         _pad2[8];
    void*        animCtx;    // +0xb54  animation subsystem context
    char         _pad1[0xe40 - 0xb58];
    AnimBinding* bindBegin;  // +0xe40
    AnimBinding* bindEnd;    // +0xe44
    void* __thiscall fa70(uint32_t, uint32_t*);
    void  __thiscall fae0(int);
    void  __thiscall fb40(int);
    void  __thiscall fb80(int, int);
    __declspec(noinline) void* __thiscall fe30(void*);
};

// Binding-cleanup receiver reached through CAN::animCtx at +0x184.
struct CANCtx {
    char  _pad0[0x17c];
    void* remapTable;   // +0x17c
    char  _pad1[4];
    void* bindingDst;   // +0x184  -> F_a01f10 receiver
};

// Play context at CAN+0xb48: starts a named animation.
struct AnimPlayCtx {
    void __thiscall Play(int, int, void*, float, void*, int);   // 0x00bca810
};

// One animation-remap descriptor (0x2bc bytes) with a duration/weight at +0x10c.
struct AnimSlotSrc {
    char  _pad0[0x10c];
    float weight;       // +0x10c
};

// Pointer chain walked by FUN_00c10050 from its object argument.
struct AnimParamObj {   // the caller's animation-object argument
    char  _pad0[0xfbc];
    void* sub;          // +0xfbc
};
struct AnimFbcObj {     // *(AnimParamObj+0xfbc)
    char  _pad0[0x2c0];
    void* sub;          // +0x2c0
};
struct Anim2c0Obj {     // *(AnimFbcObj+0x2c0)
    char  _pad0[8];
    void* sub;          // +0x08
};
struct Anim08Obj {      // *(Anim2c0Obj+0x08)
    char  _pad0[0x64];
    void* finder;       // +0x64  object with the +0xc lookup method
};

// @ 0x00c0fa70
void* __thiscall CAN::fa70(uint32_t mask, uint32_t* pIndex) {
    int n = (int)((char*)this->bindEnd - (char*)this->bindBegin);
    unsigned count = (unsigned)(n / 0x24);
    if (count == 0) return 0;
    AnimBinding* e = this->bindBegin;
    unsigned i = 0;
    do {
        int b = e->maskBit;
        if (b != 0 && (mask & (1u << b)) != 0) {
            if (pIndex != 0) *pIndex = i;
            return e;
        }
        ++i;
        ++e;
    } while (i < count);
    return 0;
}

// @ 0x00c0fae0
void __thiscall CAN::fae0(int param_2) {
    if (param_2 == 0) return;
    AnimBinding* b = (AnimBinding*)param_2;
    int v = b->handle;
    if (v != 0) {
        void* c = this->animCtx;
        if (c != 0) ((F_a01f10*)((CANCtx*)c)->bindingDst)->f(v, 0);
        b->handle = 0;
    }
    b->maskBit = 0;
    b->f08 = 0;
    b->f0c = 0;
    b->f10 = 0;
    b->weight = 0.0f;
    void* q = b->target;
    if (q != 0) {
        b->target = 0;
        ((void (__thiscall *)(void*))(*(int**)q)[0xc0 / 4])(q);
    }
}

// @ 0x00c0fb40
void __thiscall CAN::fb40(int param_2) {
    if (param_2 == 0) return;
    AnimBinding* b = (AnimBinding*)param_2;
    int v = b->handle;
    if (v == 0) return;
    void* c = this->animCtx;
    if (c == 0) return;
    ((F_a01f10*)((CANCtx*)c)->bindingDst)->f(v, 0);
    b->handle = 0;
}

// @ 0x00c0fb80
void __thiscall CAN::fb80(int, int) {
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0) ((F_a047d0*)c)->f(1);
}

// @ 0x00c0fba0
void __cdecl FUN_00c0fba0(int* self, int* vec) {
    int count = (vec[1] - vec[0]) >> 4;
    int* o = (int*)(*(void*(__thiscall**)(int*))((*(int**)self)[0x20 / 4]))(self);
    void* s = (*(void*(__thiscall**)(void*))((*(void***)o)[0x18 / 4]))(o);
    FUN_0093aa70(s, &count, 1, 0);
    int* p = (int*)vec[0];
    int* end = (int*)vec[1];
    while (p != end) {
        FUN_00c0b030(self, p);
        p += 4;
    }
    (*(void(__thiscall**)(int*))((*(int**)self)[0x1c / 4]))(self);
}

// @ 0x00c0fc10
char __cdecl FUN_00c0fc10(int param_1, int* param_2) {
    AnimBinding* p = (AnimBinding*)param_2[0];
    AnimBinding* end = (AnimBinding*)param_2[1];
    while (p != end) {
        if (p != 0) {
            void* q = p->target;
            void (__thiscall *fn)(void*, int) =
                (void (__thiscall *)(void*, int))(*(int**)q)[0x1c / 4];
            fn(q, param_1);
        }
        ++p;
    }
    return 1;
}

// @ 0x00c0fc40
int* __cdecl FUN_00c0fc40(int* first, int* last) {
    if (first != last) {
        int* prev;
        do {
            prev = first;
            ++first;
            if (first == last) return last;
        } while (*prev != *first);
        int* dst = prev;
        int* cur = dst;
        while (++cur != last) {
            int* v = (int*)*cur;
            if ((int*)*dst != v) {
                int* old = (int*)dst[1];
                ++dst;
                if (v != old) {
                    if (v != 0) (*(void(__thiscall**)(void*))((*(void***)v)[0xbc / 4]))((void*)v);
                    *dst = (int)v;
                    if (old != 0) (*(void(__thiscall**)(void*))((*(void***)old)[0xc0 / 4]))((void*)old);
                }
            }
        }
        return dst + 1;
    }
    return last;
}

// @ 0x00c0fcf0
int* __cdecl FUN_00c0fcf0(int* iface, int param_2) {
    int count = 0;
    int* o = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
    void* s = (*(void*(__thiscall**)(void*))((*(void***)o)[0x18 / 4]))(o);
    FUN_0093a780(s, &count, 1, 0);
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            char b = 0;
            int* o2 = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
            void* s2 = (*(void*(__thiscall**)(void*, void*))((*(void***)o2)[0x18 / 4]))(o2, &b);
            FUN_0093ac80(s2);
            if (i < 0x58) {
                uint32_t* pu = (uint32_t*)(param_2 + (i >> 5) * 4);
                if (b == 0) *pu &= ~(1u << (i & 0x1f));
                else *pu |= 1u << (i & 0x1f);
            }
        }
    }
    return iface;
}

// @ 0x00c0fda0
int* __cdecl FUN_00c0fda0(int* iface, int param_2) {
    int n = 0x58;
    int* o = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
    void* s = (*(void*(__thiscall**)(void*))((*(void***)o)[0x18 / 4]))(o);
    FUN_0093aa70(s, &n, 1, 0);
    uint32_t bit = 1;
    for (int i = 0; i < 0x58; ++i) {
        char b = ((*(uint32_t*)(param_2 + (i >> 5) * 4) & bit) != 0);
        int* o2 = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
        void* s2 = (*(void*(__thiscall**)(void*))((*(void***)o2)[0x18 / 4]))(o2);
        FUN_0093a9a0(s2, &b, 1);
        bit = (bit << 1) | (bit >> 31);
    }
    return iface;
}

// @ 0x00c0fe30
void* __thiscall CAN::fe30(void* src) {
    AnimBinding* d = (AnimBinding*)this;
    AnimBinding* s = (AnimBinding*)src;
    d->id = s->id;
    d->maskBit = s->maskBit;
    d->f08 = s->f08;
    d->f0c = s->f0c;
    d->f10 = s->f10;
    d->weight = s->weight;
    d->flags = s->flags;
    d->handle = s->handle;
    void* old = d->target;
    void* nw = s->target;
    if (nw != old) {
        if (nw != 0) ((void (__thiscall *)(void*))(*(int**)nw)[0xbc / 4])(nw);
        d->target = nw;
        if (old != 0) ((void (__thiscall *)(void*))(*(int**)old)[0xc0 / 4])(old);
    }
    return this;
}

// @ 0x00c0fea0
void __cdecl FUN_00c0fea0(int* src, int* dst) {
    int local[9];
    for (int i = 0; i < 9; ++i) local[i] = src[i];
    void* p = (void*)src[8];
    if (p != 0) (*(void(__thiscall**)(void*))((*(void***)p)[0xbc / 4]))(p);
    ((CAN*)src)->fe30(dst);
    ((CAN*)dst)->fe30(local);
    if (p != 0) (*(void(__thiscall**)(void*))((*(void***)p)[0xc0 / 4]))(p);
}

// @ 0x00c0ffc0
void* __cdecl FUN_00c0ffc0(int param_1, int param_2, int* param_3) {
    if (param_2 == param_1) return param_3;
    int* dst;
    do {
        param_2 -= 0x24;
        param_3 -= 9;
        dst = param_3;
        dst[0] = *(int*)(param_2 + 0x00);
        dst[1] = *(int*)(param_2 + 0x04);
        dst[2] = *(int*)(param_2 + 0x08);
        dst[3] = *(int*)(param_2 + 0x0c);
        dst[4] = *(int*)(param_2 + 0x10);
        dst[5] = *(int*)(param_2 + 0x14);
        *(char*)(dst + 6) = *(char*)(param_2 + 0x18);
        dst[7] = *(int*)(param_2 + 0x1c);
        int* piVar1 = *(int**)(param_2 + 0x20);
        int* piVar2 = (int*)dst[8];
        if (piVar1 != piVar2) {
            if (piVar1 != 0) (*(void(__thiscall**)(void*))((*(void***)piVar1)[0xbc / 4]))((void*)piVar1);
            dst[8] = (int)piVar1;
            if (piVar2 != 0) (*(void(__thiscall**)(void*))((*(void***)piVar2)[0xc0 / 4]))((void*)piVar2);
        }
    } while (param_2 != param_1);
    return dst;
}

// @ 0x00c10050
void __cdecl FUN_00c10050(uint32_t param_1, int param_2, int param_3, int param_4, char param_5) {
    if (param_3 == 0) return;
    AnimFbcObj* a = (AnimFbcObj*)((AnimParamObj*)param_3)->sub;
    if (a == 0) return;
    Anim2c0Obj* b = (Anim2c0Obj*)a->sub;
    if (b == 0) return;
    Anim08Obj* c = (Anim08Obj*)b->sub;
    if (c == 0) return;
    void* finder = c->finder;
    CAN* ctx;
    if (finder == 0) ctx = 0;
    else ctx = (CAN*)((int (__thiscall *)(void*, int))(*(int**)finder)[0xc / 4])(finder, 0xce9f6639);

    uint32_t local_40[16];
    local_40[0] = 0; local_40[1] = 1;
    local_40[2] = 0; local_40[3] = 2;
    local_40[4] = 0; local_40[5] = 3;
    local_40[6] = 0; local_40[7] = 4;
    uint32_t uVar7 = 0;
    if (param_1 != 0xffffffff) {
        uint32_t uVar4 = param_1;
        do {
            local_40[uVar7 * 2] = uVar4 & 0xff;
            ++uVar7;
            if (uVar7 >= 4) break;
            uint32_t t = uVar4 >> 8;
            uVar4 = uVar4 >> 8;
            if ((char)t == -1) break;
        } while (1);
    }
    uint32_t uVar6 = 0;
    int* piVar3 = (int*)FUN_009ff6f0((void*)param_3, (void*)param_4);
    if (piVar3 != 0 && *piVar3 != 0) {
        int iVar5 = *(int*)(*piVar3 + 8);
        if (iVar5 != 0 && uVar7 != 0) {
            if (*(uint32_t*)(iVar5 + 0x18) < 2) {
                if (*(int*)(iVar5 + 0x14) == 2) {
                    CANCtx* cc = (CANCtx*)ctx->animCtx;
                    int remap = (int)cc->remapTable;
                    int arr = *(int*)(remap + 0x2e4);
                    AnimSlotSrc* elem = (AnimSlotSrc*)*(void**)(arr + local_40[0] * 700);
                    if (0.0f < elem->weight) uVar6 = 1;
                } else {
                    uVar6 = 0;
                }
            } else {
                void* c2 = ctx->animCtx;
                char* extra = 0;
                uint32_t rr = ((uint32_t (__thiscall *)(void*, int, uint32_t*, uint32_t, void*))
                               (*(int**)c2)[0x68 / 4])(c2, param_4, local_40, uVar7, &extra);
                if (rr < *(uint32_t*)(*(int*)(*piVar3 + 8) + 0x14)) uVar6 = rr;
            }
        }
    }
    void* c3 = ctx->animCtx;
    ((void (__thiscall *)(void*, int, uint32_t))(*(int**)c3)[0x3c / 4])(c3, param_4, uVar6);
    if (param_5 == 0 && param_2 != -1) {
        uint32_t val = (uint32_t)param_2;
        for (int i = 0; i < 4; ++i) {
            uint32_t local = 0;
            char* e = ((F_f9b0*)ctx)->f((int)(val & 0xff), &local);
            if (e != 0 && *(int*)(e + 4) != 0) {
                local_40[6] = local;
                local_40[7] = (uint32_t)param_4;
                local_40[8] = 0;
                ((AnimPlayCtx*)ctx->playCtx)->Play(5, 0, (void*)ctx, GF(0x146a32c), &local_40[6], 0);
            }
            uint32_t t = val >> 8;
            val = val >> 8;
            if ((char)t == -1) break;
        }
    }
}

// @ 0x00c10210
void __cdecl FUN_00c10210(int a1, int a2, int a3, int a4) {
    FUN_00c10050((uint32_t)a1, a2, a3, a4, 1);
}

// @ 0x00c10230
void __cdecl FUN_00c10230(int a1, int a2, int a3, int a4) {
    FUN_00c10050((uint32_t)a1, a2, a3, a4, 0);
}

// @ 0x00c10250
void __cdecl FUN_00c10250(int param_1, int param_2, uint32_t param_3, int param_4) {
    CAN* self = (CAN*)param_1;
    if (*(int*)(param_4 + 0x24) != 0) {
        uint32_t u = 0xffffffff;
        char* p = (char*)self->fa70(*(uint32_t*)(param_4 + 0x24), 0);
        if (p != 0) u = *(uint32_t*)p;
        if (u != param_3 && u != 0xffffffff) param_3 = u;
    }
    char* c = *(char**)(param_1 + 0xb54);
    int iVar1 = *(int*)(c + 0x17c);
    uint32_t cnt = (uint32_t)((*(int*)(iVar1 + 0x2e8) - *(int*)(iVar1 + 0x2e4)) / 700);
    if (cnt <= param_3) param_3 = 0xffffffff;
    uint32_t u2 = 0xffffffff;
    if (*(int*)(param_4 + 0x20) != 0) {
        char* p2 = (char*)self->fa70(*(uint32_t*)(param_4 + 0x20), 0);
        if (p2 != 0 && *(uint32_t*)p2 != 0xffffffff) u2 = *(uint32_t*)p2 | 0xffffff00;
    }
    param_3 |= 0xffffff00;
    char* c2 = *(char**)(param_1 + 0xb54);
    void* vt = *(void**)c2;
    (*(void(__thiscall**)(void*, int, void*))((char*)vt + 0x48))(c2, param_2, (void*)FUN_00c10230);
    (*(void(__thiscall**)(void*, int, uint32_t, uint32_t))((char*)vt + 0x4c))(c2, param_2, param_3, u2);
}

// @ 0x00c10330
void __cdecl FUN_00c10330(int param_1, int param_2, int param_3, uint32_t param_4,
                           int param_5, uint32_t param_6) {
    uint32_t uVar8 = 0xffffffff;
    uint32_t local_4 = 4;
    uint32_t* pu = &local_4;
    if (param_4 < 5) pu = &param_4;
    uint32_t uVar5 = 0;
    if (*pu != 0) {
        char bVar6 = 0;
        do {
            int iVar1 = (int)(uVar5 * 4);
            char bVar2 = bVar6 & 0x1f;
            char bVar3 = bVar6 & 0x1f;
            ++uVar5;
            bVar6 = (char)(bVar6 + 8);
            uVar8 = ((uint32_t)*(uint8_t*)(param_3 + iVar1) << bVar3) | (~(0xffu << bVar2) & uVar8);
        } while (uVar5 < *pu);
    }
    uint32_t uVar7 = 0xffffffff;
    uVar5 = 0;
    if (param_6 != 0) {
        char bVar6 = 0;
        do {
            int iVar1 = (int)(uVar5 * 4);
            char bVar2 = bVar6 & 0x1f;
            char bVar3 = bVar6 & 0x1f;
            ++uVar5;
            bVar6 = (char)(bVar6 + 8);
            uVar7 = ((uint32_t)*(uint8_t*)(param_5 + iVar1) << bVar3) | (~(0xffu << bVar2) & uVar7);
        } while (uVar5 < param_6);
    }
    char* c = *(char**)(param_1 + 0xb54);
    void* vt = *(void**)c;
    (*(void(__thiscall**)(void*, int, void*))((char*)vt + 0x48))(c, param_2, (void*)FUN_00c10230);
    (*(void(__thiscall**)(void*, int, uint32_t, uint32_t))((char*)vt + 0x4c))(c, param_2, uVar8, uVar7);
}

// @ 0x00c103f0
void __cdecl FUN_00c103f0(void) {
    void* a = FUN_00f473a0(0x20, "Simulator/cAnimationRemapping", 0, 0, 0, 0);
    G32(0x168d900) = (uint32_t)(uintptr_t)a;
    if (a != 0) {
        for (int i = 0; i < 8; ++i) *(int*)((char*)a + i * 4) = 0;
    } else {
        G32(0x168d900) = 0;
    }
    int* pm = (int*)FUN_0067de30();
    intptr_t base = (intptr_t)G32(0x168d900);
    uint32_t uVar5 = 0;
    int iVar3 = 0;
    do {
        if (G32(0x1572008 + uVar5) != 0) {
            int* piVar1 = *(int**)(base + iVar3);
            int* puVar4 = (int*)(base + iVar3);
            if (piVar1 != 0) {
                *puVar4 = 0;
                (*(void(__thiscall**)(void*))((*(void***)piVar1)[1]))((void*)piVar1);
            }
            (*(void(__thiscall**)(void*, int, int, void*))((char*)*(void**)pm + 0x2c))(
                pm, (int)G32(0x1572008 + uVar5), (int)G32(0x157200c + uVar5), puVar4);
        }
        uVar5 += 8;
        iVar3 += 4;
    } while (uVar5 < 0x38);
    intptr_t base2 = (intptr_t)G32(0x168d900);
    int* piVar1 = *(int**)(base2 + 0x1c);
    int* puVar4 = (int*)(base2 + 0x1c);
    if (piVar1 != 0) {
        *puVar4 = 0;
        (*(void(__thiscall**)(void*))((*(void***)piVar1)[1]))((void*)piVar1);
    }
    (*(void(__thiscall**)(void*, uint32_t, uint32_t, void*))((char*)*(void**)pm + 0x2c))(
        pm, 0x3bd27948u, 0x623d3400u, puVar4);
}
