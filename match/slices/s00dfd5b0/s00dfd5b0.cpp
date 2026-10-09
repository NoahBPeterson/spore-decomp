// Slice s00dfd5b0 -- editor mission UI helpers (continuation of s00dfa5c0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

void  operator_delete_(void* p);            // 0x00f47380
void* FindWindowByID(void* lay, int id, int a); // 0x008105b0 thiscall ret8
void  FUN_d3a0(void* p);                    // 0x00dfd3a0
void  FUN_e0e0(void* self, void* p);        // 0x00dfdfe0
struct F28 { void M(); };                   // 0x00f280f0 thiscall
struct VecC { void F(unsigned a, unsigned b); }; // 0x00dfc600 thiscall ret8
struct Obj4 { void F_bba0(); };             // 0x00dfbba0 thiscall
struct VecB { void F_b850(); };             // 0x00dfb850 thiscall
struct UI2 {
    void M_d8a0();              // 0x00dfd8a0 thiscall
    void F_de90();              // 0xdfde90
    void* F_e170(int* p);       // 0xdfe170
};

// @ 0x00dfde90
void UI2::F_de90()
{
    char* base = (char*)this + 0xe0;
    for (unsigned int i = 0; i < 3; ++i) {
        if (base[i * 0x38] == 0) {
            *(int*)((char*)this + 0x34) = i;
            M_d8a0();
        }
    }
    *(unsigned char*)((char*)this + 0x7e) = 1;
    int local = 0;
    if (*(int*)((char*)this + 0x30) != 0) {
        char* p = base;
        int n = *(int*)((char*)this + 0x30);
        do {
            if (*p == 0) local = 1;
            p += 0x38;
            --n;
        } while (n != 0);
    }
    void* w = FindWindowByID((char*)this + 0x48, 0x7ccc115, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 2, local);
}

// @ 0x00dfdf10
void __stdcall F_df10(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x534) {
        ((VecC*)(a + 0x84))->F(*(unsigned*)(a + 0x84), *(unsigned*)(a + 0x88));
        int p = *(int*)(a + 0x84);
        if (p != 0 && *(int*)(p - 4) != 0)
            operator_delete_((void*)p);
        ((F28*)(a + 0x3c))->M();
        ((F28*)a)->M();
    }
}

// @ 0x00dfdf70
void __stdcall F_df70(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x27e0) {
        ((F28*)(a + 0x2788))->M();
        unsigned end = *(unsigned*)(a + 0x74);
        for (unsigned p = *(unsigned*)(a + 0x70); p < end; p += 0x4e0)
            ((Obj4*)p)->F_bba0();
        int q = *(int*)(a + 0x70);
        if (q != 0 && *(int*)(q - 4) != 0)
            operator_delete_((void*)q);
    }
}

// @ 0x00dfe170
void* UI2::F_e170(int* p)
{
    if ((*p < 0) && (-1 < *(int*)this)) {
        int v = *(int*)((char*)this + 0x210);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_delete_((void*)v);
        ((VecB*)((char*)this + 0x2c))->F_b850();
        int w = *(int*)((char*)this + 0x2c);
        if (w != 0 && *(int*)(w - 4) != 0) {
            operator_delete_((void*)w);
            *(int*)this = *p;
            return this;
        }
    } else if (-1 < *p) {
        if (*(int*)this < 0) {
            if (this != (UI2*)0xfffffffc) {
                FUN_e0e0((char*)this + 4, p + 1);
                *(int*)this = *p;
                return this;
            }
        } else {
            FUN_d3a0(p + 1);
        }
    }
    *(int*)this = *p;
    return this;
}

// ---- copy-ctor / big UI setup (partial) --------------------------------------
// @ 0x00dfd5b0
void F_dfd5b0(void* self, void* a) { (void)self; (void)a; }
// @ 0x00dfd8a0
void F_dfd8a0(void* self) { (void)self; }
// @ 0x00dfda50
void F_dfda50(void* self, void* out) { (void)self; (void)out; }
// @ 0x00dfdc50
void F_dfdc50(void* self, void* a) { (void)self; (void)a; }
// @ 0x00dfdfe0
void F_dfdfe0(void* self, void* a) { (void)self; (void)a; }
// @ 0x00dfe220
void F_dfe220(void* self) { (void)self; }