// Slice s00dfe460 (batch bfs3, slice 12). Region 0xdfe460-0xdff7ff.
// EASTL vector helpers over large element types (0x188, 0x238, 0x4e0, 0x27e8,
// 0x2788) plus a big UI message handler and a large destructor.
// Optimised: /O2 /MD /Gy /TP /arch=SSE.
#include "types.h"

extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                       // 0xf47380
extern "C" void  __cdecl FUN_00f280f0(void*);
extern "C" void  __cdecl FUN_00dfbba0(void*);
extern "C" void  __cdecl FUN_00dfdfe0(void*);
extern "C" void  __cdecl FUN_00dfdf70(void*, void*);
extern "C" void  __cdecl FUN_00dfd300(void*, void*);
extern "C" void  __cdecl FUN_00dfdf10(void*, void*);
extern "C" void* __cdecl FUN_00dfd250(void*, void*, void*);
extern "C" void* __cdecl FUN_00dfd2c0(void*, void*, void*);
extern "C" void  __cdecl FUN_00dfd4e0(void*, void*, void*, void*, void*);
// thiscall stub classes (receiver in ECX)
struct V188 {
    void* b; void* e; void* cap;
    V188* Assign(V188* other);                       // 0x00dfeb00 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dfe9e0 ret 0xc
    void  Destroy(void* f, void* l);                 // 0x00dfc600 ret 8
};
struct V4e0 {
    void* b; void* e; void* cap;
    V4e0* Assign(V4e0* other);                       // 0x00dfec50 ret 4
    V4e0* AssignWrap(V4e0* other);                   // 0x00dfed90 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dfea40 ret 0xc
    void  Destroy(void* f, void* l);                 // 0x00dfc660 ret 8
};
struct CStr {
    void Assign(void* o);                            // 0x006b5430 thiscall ret 4
};
struct ElemA {                                       // 0x2788-class
    void* CopyAssign(void* o);                       // 0x00dfedb0 ret 4
    void* CopyCtor(void* o);                         // 0x00dff1a0 ret 4
};
struct ElemB {                                       // 0x27e8-class
    void* CopyCtor(void* o);                         // 0x00dfee80 ret 4
    void* Init(void* o);                             // 0x00dff130 ret 4
};
struct Buf3c {
    void Copy(void* o);                              // 0x00dfb280 thiscall ret 4
};
extern "C" void __stdcall WStr_Assign(void*, void*); // 0x00423650 ret 8
extern "C" void  __cdecl FUN_00df9990();
extern "C" void  __cdecl FUN_00df9ef0();
extern "C" void  __cdecl FUN_00df9e60();
extern "C" void  __cdecl FUN_00dfae50();
extern "C" void  __cdecl FUN_00dfab20();
extern "C" void  __cdecl FUN_00dfa460();
extern "C" void  __cdecl FUN_00685a30(void*, void*);
extern "C" void* __cdecl FUN_00435e90();        // GetRecorderState
extern "C" void  __cdecl FUN_00435ed0();

// ===========================================================================
//  0x00dfe460  SP::cSPUISpace message/command handler (big prologue switch)
// ===========================================================================
// @ 0x00dfe460
char UISpace_Handle(void* self, void* msg, int arg2) {
    // Large switch over hashed command ids; see partial.txt.
    (void)self; (void)msg; (void)arg2;
    return 1;
}

// ===========================================================================
//  0x00dfe910  destroy a range of 0x27e8-stride elements
// ===========================================================================
struct Elem27e8 { char pad[0x78]; void* mp; };   // vector member at +0x78
// @ 0x00dfe910
void DestroyRange27e8(Elem27e8* first, Elem27e8* last) {
    while (first < last) {
        FUN_00f280f0((char*)first + 0x2718);
        void** begin = *(void***)((char*)first + 0x78);
        void** end = *(void***)((char*)first + 0x7c);
        while (begin < end) {
            FUN_00dfbba0(begin);
            begin = (void**)((char*)begin + 0x4e0);
        }
        void* p = *(void**)((char*)first + 0x78);
        if (p != 0 && *((int*)p - 1) != 0) {
            EA_Free(p);
        }
        first = (Elem27e8*)((char*)first + 0x27e8);
    }
}

// ===========================================================================
//  0x00dfeaa0  uninitialized_copy, stride 0x238
// ===========================================================================
// @ 0x00dfeaa0
void** UninitCopy238(void** dstp, int* first, int* last, int val) {
    *dstp = (void*)val;
    while (first != last) {
        char* d = (char*)*dstp;
        if (d != 0) {
            *(int*)d = *first;
            if (*first >= 0) {
                d += 4;
                if (d != 0) {
                    FUN_00dfdfe0(first + 1);
                }
            }
        }
        *dstp = (char*)*dstp + 0x238;
        first = (int*)((char*)first + 0x238);
    }
    return dstp;
}

// ===========================================================================
//  0x00dfeb00  vector assign, stride 0x188
// ===========================================================================
// @ 0x00dfeb00
V188* V188::Assign(V188* other_) {
    void** self = (void**)this; int* other = (int*)other_;
    if (other == (int*)self) {
        return this;
    }
    int iVar1 = *other;
    uint32_t uVar2 = (uint32_t)((other[1] - iVar1) / 0x188);
    int iVar5 = (int)*self;
    if ((uint32_t)(((int*)self)[2] - iVar5) / 0x188 < uVar2) {
        iVar5 = (int)Alloc(uVar2, (void*)iVar1, (void*)other[1]);
        Destroy(*self, (void*)((int*)self)[1]);
        int p = (int)*self;
        if (p != 0 && *(int*)(p - 4) != 0) {
            EA_Free((void*)p);
        }
        ((int*)self)[1] = uVar2 * 0x188 + iVar5;
        *self = (void*)iVar5;
        ((int*)self)[2] = uVar2 * 0x188 + iVar5;
        return this;
    }
    uint32_t uVar3 = (uint32_t)(((int*)self)[1] - iVar5) / 0x188;
    if (uVar3 < uVar2) {
        FUN_00dfd250((void*)iVar1, (void*)(uVar3 * 0x188 + iVar1), (void*)iVar5);
        other = (int*)other[1];
        FUN_00dfd4e0(&other, (void*)((((int*)self)[1] - (int)*self) / 0x188 * 0x188 + *other),
                     other, (void*)((int*)self)[1], other);
        ((int*)self)[1] = uVar2 * 0x188 + (int)*self;
        return this;
    }
    void* uVar6 = FUN_00dfd250((void*)iVar1, (void*)other[1], (void*)iVar5);
    Destroy(uVar6, (void*)((int*)self)[1]);
    ((int*)self)[1] = uVar2 * 0x188 + (int)*self;
    return this;
}

// ===========================================================================
//  0x00dfec50  vector resize/assign, stride 0x4e0
// ===========================================================================
// @ 0x00dfec50
V4e0* V4e0::Assign(V4e0* other_) {
    void** self = (void**)this; int* other = (int*)other_;
    if (other == (int*)self) {
        return this;
    }
    int iVar1 = *other;
    uint32_t uVar2 = (uint32_t)((other[1] - iVar1) / 0x4e0);
    int ebp0 = (int)*self;
    if ((uint32_t)(((int*)self)[2] - ebp0) / 0x4e0 < uVar2) {
        int iVar5 = (int)Alloc(uVar2, (void*)iVar1, (void*)other[1]);
        Destroy(*self, (void*)((int*)self)[1]);
        int p = (int)*self;
        if (p != 0 && *(int*)(p - 4) != 0) {
            EA_Free((void*)p);
        }
        *self = (void*)iVar5;
        ((int*)self)[2] = uVar2 * 0x4e0 + iVar5;
        ((int*)self)[1] = uVar2 * 0x4e0 + iVar5;
        return this;
    }
    uint32_t uVar3 = (uint32_t)(((int*)self)[1] - ebp0) / 0x4e0;
    if (uVar3 < uVar2) {
        FUN_00dfd2c0((void*)iVar1, (void*)(uVar3 * 0x4e0 + iVar1), (void*)ebp0);
        other = (int*)other[1];
        FUN_00dfd4e0(&other, (void*)((((int*)self)[1] - (int)*self) / 0x4e0 * 0x4e0 + *other),
                     other, (void*)((int*)self)[1], other);
        ((int*)self)[1] = uVar2 * 0x4e0 + (int)*self;
        return this;
    }
    void* uVar6 = FUN_00dfd2c0((void*)iVar1, (void*)other[1], (void*)ebp0);
    Destroy(uVar6, (void*)((int*)self)[1]);
    ((int*)self)[1] = uVar2 * 0x4e0 + (int)*self;
    return this;
}

// @ 0x00dfed90  wrapper calling 00dfec50
V4e0* V4e0::AssignWrap(V4e0* other) {
    Assign(other);
    return this;
}

// ===========================================================================
//  0x00dfedb0  copy-assign for the 0x2788 element class
// ===========================================================================
// @ 0x00dfedb0
void* ElemA::CopyAssign(void* o) {
    void* s = this;
    ((CStr*)s)->Assign(o);
    if ((void*)((char*)o + 0x14) != (void*)((char*)s + 0x14)) {
        WStr_Assign(*(void**)((char*)o + 0x14), *(void**)((char*)o + 0x18));
    }
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    *(uint32_t*)((char*)s + 0x28) = *(uint32_t*)((char*)o + 0x28);
    if ((void*)((char*)o + 0x2c) != (void*)((char*)s + 0x2c)) {
        WStr_Assign(*(void**)((char*)o + 0x2c), *(void**)((char*)o + 0x30));
    }
    ((CStr*)((char*)s + 0x3c))->Assign((char*)o + 0x3c);
    if ((void*)((char*)o + 0x50) != (void*)((char*)s + 0x50)) {
        WStr_Assign(*(void**)((char*)o + 0x50), *(void**)((char*)o + 0x54));
    }
    *(uint32_t*)((char*)s + 0x60) = *(uint32_t*)((char*)o + 0x60);
    *(uint32_t*)((char*)s + 0x64) = *(uint32_t*)((char*)o + 0x64);
    if ((void*)((char*)o + 0x68) != (void*)((char*)s + 0x68)) {
        WStr_Assign(*(void**)((char*)o + 0x68), *(void**)((char*)o + 0x6c));
    }
    *(uint32_t*)((char*)s + 0x78) = *(uint32_t*)((char*)o + 0x78);
    *(uint8_t*)((char*)s + 0x7c) = *(uint8_t*)((char*)o + 0x7c);
    *(uint32_t*)((char*)s + 0x80) = *(uint32_t*)((char*)o + 0x80);
    ((V188*)((char*)s + 0x84))->Assign((V188*)((char*)o + 0x84));
    return s;
}

// ===========================================================================
//  0x00dfee80  copy-ctor for the 0x27e8 element class
// ===========================================================================
// @ 0x00dfee80
void* ElemB::CopyCtor(void* o) {
    void* s = this;
    for (int i = 0; i < 8; ++i) ((uint32_t*)s)[i] = ((uint32_t*)o)[i];
    *(uint8_t*)((char*)s + 0x20) = *(uint8_t*)((char*)o + 0x20);
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x28))[i] = ((uint32_t*)((char*)o + 0x28))[i];
    *(uint32_t*)((char*)s + 0x48) = *(uint32_t*)((char*)o + 0x48);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x50))[i] = ((uint32_t*)((char*)o + 0x50))[i];
    ((V4e0*)((char*)s + 0x70))->Assign((V4e0*)((char*)o + 0x70));
    ((CStr*)((char*)s + 0x2788))->Assign((char*)o + 0x2788);
    if ((void*)((char*)o + 0x2788 + 0x14) != (void*)((char*)s + 0x2788 + 0x14)) {
        WStr_Assign(*(void**)((char*)o + 0x2788 + 0x14), *(void**)((char*)o + 0x2788 + 0x18));
    }
    *(uint32_t*)((char*)s + 0x27c4) = *(uint32_t*)((char*)o + 0x27c4);
    *(uint32_t*)((char*)s + 0x27c8) = *(uint32_t*)((char*)o + 0x27c8);
    if ((void*)((char*)o + 0x27d0) != (void*)((char*)s + 0x27d0)) {
        WStr_Assign(*(void**)((char*)o + 0x27d0), *(void**)((char*)o + 0x27d4));
    }
    *(uint32_t*)((char*)s + 0x27e0) = *(uint32_t*)((char*)o + 0x27e0);
    *(uint32_t*)((char*)s + 0x27e4) = *(uint32_t*)((char*)o + 0x27e4);
    return s;
}

// ===========================================================================
//  0x00dfef70  large destructor
// ===========================================================================
// @ 0x00dfef70
void UISpace_Dtor(void* s) {
    // Large destructor; see partial.txt.
    *(void**)((char*)s + 0x18) = (void*)0x13eb938;
    *(void**)s = (void*)0x13eb938;
}

// ===========================================================================
//  0x00dff130  element-wise assign for the 0x27e8 class (from a fresh object)
// ===========================================================================
// @ 0x00dff130
void* ElemB::Init(void* o) {
    void* s = this;
    ((Buf3c*)s)->Copy(o);
    ((Buf3c*)((char*)s + 0x3c))->Copy((char*)o + 0x3c);
    *(uint32_t*)((char*)s + 0x78) = *(uint32_t*)((char*)o + 0x78);
    *(uint8_t*)((char*)s + 0x7c) = *(uint8_t*)((char*)o + 0x7c);
    *(uint32_t*)((char*)s + 0x80) = *(uint32_t*)((char*)o + 0x80);
    *(void**)((char*)s + 0x84) = (char*)s + 0x9c;
    *(void**)((char*)s + 0x88) = (char*)s + 0x9c;
    *(void**)((char*)s + 0x98) = 0;
    *(void**)((char*)s + 0x8c) = (char*)s + 0x534;
    ((V188*)((char*)s + 0x84))->Assign((V188*)((char*)o + 0x84));
    return s;
}

// ===========================================================================
//  0x00dff1a0  copy-ctor for the 0x2788 element class
// ===========================================================================
// @ 0x00dff1a0
void* ElemA::CopyCtor(void* o) {
    void* s = this;
    for (int i = 0; i < 8; ++i) ((uint32_t*)s)[i] = ((uint32_t*)o)[i];
    *(uint8_t*)((char*)s + 0x20) = *(uint8_t*)((char*)o + 0x20);
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x28))[i] = ((uint32_t*)((char*)o + 0x28))[i];
    *(uint32_t*)((char*)s + 0x48) = *(uint32_t*)((char*)o + 0x48);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x50))[i] = ((uint32_t*)((char*)o + 0x50))[i];
    *(void**)((char*)s + 0x70) = (char*)s + 0x88;
    *(void**)((char*)s + 0x74) = (char*)s + 0x88;
    *(void**)((char*)s + 0x78) = (char*)s + 0x2788;
    *(void**)((char*)s + 0x84) = 0;
    ((V4e0*)((char*)s + 0x70))->Assign((V4e0*)((char*)o + 0x70));
    ((Buf3c*)((char*)s + 0x2788))->Copy((char*)o + 0x2788);
    *(uint32_t*)((char*)s + 0x27c4) = *(uint32_t*)((char*)o + 0x27c4);
    *(uint32_t*)((char*)s + 0x27c8) = *(uint32_t*)((char*)o + 0x27c8);
    *(uint32_t*)((char*)s + 0x27cc) = *(uint32_t*)((char*)o + 0x27cc);
    *(uint32_t*)((char*)s + 0x27d0) = *(uint32_t*)((char*)o + 0x27d0);
    *(uint32_t*)((char*)s + 0x27d8) = *(uint32_t*)((char*)o + 0x27d8);
    *(uint32_t*)((char*)s + 0x27dc) = *(uint32_t*)((char*)o + 0x27dc);
    return s;
}

// ===========================================================================
//  0x00dff330  (see partial.txt)
// ===========================================================================
// @ 0x00dff330
void UISpace_330(void* s) {
    (void)s;
}

// ===========================================================================
//  0x00dff4e0  uninitialized_copy, stride 0x27e8
// ===========================================================================
// @ 0x00dff4e0
void** UninitCopy27e8(void** dstp, int* first, int* last, int val) {
    *dstp = (void*)val;
    while (first != last) {
        char* d = (char*)*dstp;
        if (d != 0) {
            *(int*)d = *first;
            ((ElemA*)(d + 8))->CopyCtor(first + 2);
        }
        *dstp = (char*)*dstp + 0x27e8;
        first = (int*)((char*)first + 0x27e8);
    }
    return dstp;
}

// ===========================================================================
//  0x00dff650  (see partial.txt)
// ===========================================================================
// @ 0x00dff650
void UISpace_650(void* s) {
    (void)s;
}
