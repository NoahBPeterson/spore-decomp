// Slice s006783c0 - SPUISpace HUD widget: window anchoring, animation state machine,
// intrusive refcount-vector assignment and destructors.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"

struct VObj { void** vt; };
typedef void (__thiscall *FnV1)(void*);
void DeleteObj(void* p);   // 0x00f47380

void __fastcall FUN_008e2b20(char* p);
void __fastcall FUN_00929d50(char* p);
void __fastcall FUN_00678f70(char* p);
void __fastcall FUN_00679120(char* p);

struct Thunk1 { void One(int a); };                       // 0x006781d0
struct Thunk4 { void Init(int a, int b, int c, int d); }; // 0x00679080
struct Thunk7 { void Seven(int,int,int,int,int,int,int); }; // 0x00929e70

// ---- 0x00678ed0 : (a == b) ------------------------------------------
// @ 0x00678ed0
bool __fastcall FUN_00678ed0(char* p) {
    int v = *(int*)(p + 0x18);
    bool r = (v == *(int*)(p + 0x28));
    return r;
}

// ---- 0x00678f70 : release sub-objects + string, then base dtor -------
// @ 0x00678f70
void __fastcall FUN_00678f70(char* p) {
    unsigned short* b = *(unsigned short**)(p + 0xd8);
    if ((((char*)(*(char**)(p + 0xe0)) - (char*)b) & ~1) > 2 && b &&
        b != *(unsigned short**)(p + 0xe8))
        DeleteObj(b);
    if (*(void**)(p + 0xb8)) { void* x = *(void**)(p + 0xb8); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0xb4)) { void* x = *(void**)(p + 0xb4); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0xb0)) { void* x = *(void**)(p + 0xb0); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0xac)) { void* x = *(void**)(p + 0xac); ((FnV1)((VObj*)x)->vt[1])(x); }
    FUN_008e2b20(p + 0x14);
}

// ---- 0x00679080 : init the sub-object -------------------------------
// @ 0x00679080
void Thunk4::Init(int a, int b, int c, int d) {
    char* t = (char*)this;
    *(int*)(t + 4) = a;
    *(int*)(t + 8) = b;
    *(int*)(t + 0xc) = c;
    *(int*)(t + 0x10) = d;
    char* base = t + 0x2c;
    *(char**)(t + 0x24) = base;
    *(char**)(t + 0x18) = base;
    *(char**)(t + 0x14) = base;
    *(char**)(t + 0x1c) = t + 0xac;
    *(int*)(t + 0xac) = 0;
    *(int*)(t + 0xb0) = 0;
    *(int*)(t + 0xb4) = 0;
    *(int*)(t + 0xb8) = 0;
    float neg = -1.0f;
    *(float*)(t + 0xbc) = neg;
    *(float*)(t + 0xc0) = neg;
    *(float*)(t + 0xc4) = 0.0f;
    unsigned short* inl = (unsigned short*)(t + 0xec);
    *(unsigned short**)(t + 0xe8) = inl;
    *(unsigned short**)(t + 0xe0) = inl + 0x20;
    *(unsigned short**)(t + 0xdc) = inl;
    *(unsigned short**)(t + 0xd8) = inl;
    *inl = 0;
}

// ---- 0x00679120 : destroy all sub-objects (complete, non-matching) ---
// @ 0x00679120
void __fastcall FUN_00679120(char* p) {
    char* i = *(char**)(p + 8);
    char* end = *(char**)(p + 0x10);
    char* blockBase = *(char**)(p + 0x14);
    if (i != *(char**)(p + 0x18)) {
        do {
            FUN_00678f70(i);
            i += 0x134;
            if (i == end) {
                char* nb = *(char**)(blockBase + 4);
                blockBase += 4;
                i = nb;
                end = nb + 0x4d0;
            }
        } while (i != *(char**)(p + 0x18));
    }
    if (*(void**)p != 0) {
        char* q = *(char**)(p + 0x24);
        char* j = *(char**)(p + 0x14);
        while (j < q + 4) {
            if (*(void**)j) DeleteObj(*(void**)j);
            j += 4;
        }
        if (*(void**)p) DeleteObj(*(void**)p);
    }
}

// ---- 0x006792f0 : advance one element (destroy + recycle) ------------
// @ 0x006792f0
void __fastcall FUN_006792f0(char* p) {
    int n = *(int*)(p + 8) + 0x134;
    if (n != *(int*)(p + 0x10)) {
        *(int*)(p + 8) = n;
        FUN_00678f70(p);
        return;
    }
    FUN_00678f70(p);
    if (*(int*)(p + 0xc)) DeleteObj(*(void**)(p + 0xc));
    int* q = (int*)(*(int*)(p + 0x14) + 4);
    *(int**)(p + 0x14) = q;
    int v = *q;
    *(int*)(p + 0xc) = v;
    *(int*)(p + 0x10) = v + 0x4d0;
    *(int*)(p + 8) = *(int*)(p + 0xc);
}

// ---- 0x00679340 : assign an intrusive refcount vector (complete) -----
extern int* FUN_00679020(unsigned n, int* src, int* end);
extern void FUN_00b007f0(void* first, void* last);
extern int* FUN_006782c0(void* dst, void* src, void* end);
extern void FUN_00829110(void* out, void* a, void* b, void* c, void* d);
struct RefVec {
    int* mpBegin; int* mpEnd; int* mpCapacity; char pad[4]; int* mpInline;
    void Assign(int* first, int* last);
};
// @ 0x00679340
void RefVec::Assign(int* first, int* last) {
    int* begin = mpBegin;
    unsigned n = ((char*)last - (char*)first) >> 2;
    unsigned cap = ((char*)mpCapacity - (char*)begin) >> 2;
    if (n > cap) {
        int* nb = FUN_00679020(n, first, last);
        FUN_00b007f0(mpBegin, mpEnd);
        if (mpBegin && mpBegin != mpInline) DeleteObj(mpBegin);
        int* e = (int*)((char*)nb + n * 4);
        mpBegin = nb; mpEnd = e; mpCapacity = e;
        return;
    }
    unsigned have = ((char*)mpEnd - (char*)begin) >> 2;
    if (n <= have) {
        int* e = FUN_006782c0(begin, first, last);
        FUN_00b007f0(e, mpEnd);
        mpEnd = e;
        return;
    }
    int* mid = (int*)((char*)first + have * 4);
    int* e = FUN_006782c0(begin, first, mid);
    FUN_00829110(&last, mid, last, mpEnd, last);
    mpEnd = last;
}

// ---- 0x00679400 : destructor ----------------------------------------
// @ 0x00679400
void __fastcall FUN_00679400(char* p) {
    *(void**)p = (void*)0x14013f0;
    *(void**)(p + 8) = (void*)0x14013d4;
    *(void**)(p + 0xc) = (void*)0x14013c4;
    FUN_00929d50(p + 0x1fc);
    FUN_00929d50(p + 0x1d8);
    FUN_00929d50(p + 0x1b4);
    if (*(void**)(p + 0x1b0)) { void* x=*(void**)(p+0x1b0); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0x1ac)) { void* x=*(void**)(p+0x1ac); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0x1a8)) { void* x=*(void**)(p+0x1a8); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0x1a4)) { void* x=*(void**)(p+0x1a4); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0x194)) { void* x=*(void**)(p+0x194); ((FnV1)((VObj*)x)->vt[1])(x); }
    FUN_00678f70(p + 0x3c);
    FUN_00679120(p + 0x10);
    *(void**)(p + 0xc) = (void*)0x13eb394;
    *(void**)(p + 8) = (void*)0x13eb938;
    *(void**)p = (void*)0x13ec458;
}

// ---- 0x00679520 : constructor ---------------------------------------
// @ 0x00679520
void* __fastcall FUN_00679520(char* p) {
    *(int*)(p + 4) = 0;
    *(void**)(p + 8) = (void*)0x14426a0;
    *(void**)(p + 0xc) = (void*)0x13eb384;
    char* v = p + 0x10;
    *(void**)p = (void*)0x14013f0;
    *(void**)(p + 8) = (void*)0x14013d4;
    *(void**)(p + 0xc) = (void*)0x14013c4;
    *(int*)(v + 0x00) = 0;
    *(int*)(v + 0x04) = 0;
    *(int*)(v + 0x08) = 0;
    *(int*)(v + 0x0c) = 0;
    *(int*)(v + 0x10) = 0;
    *(int*)(v + 0x14) = 0;
    *(int*)(v + 0x18) = 0;
    *(int*)(v + 0x1c) = 0;
    *(int*)(v + 0x20) = 0;
    *(int*)(v + 0x24) = 0;
    ((Thunk1*)(p + 0x10))->One(0);
    ((Thunk4*)(p + 0x3c))->Init(0, 0, 0, 0);
    *(void**)(p + 0x170) = (void*)0x14013b4;
    *(int*)(p + 0x194) = 0;
    *(char*)(p + 0x1a1) = 0;
    *(int*)(p + 0x1a4) = 0;
    *(int*)(p + 0x1a8) = 0;
    *(int*)(p + 0x1ac) = 0;
    *(int*)(p + 0x1b0) = 0;
    ((Thunk7*)(p + 0x1b4))->Seven(0, 0, 500, 0, 2, 0, 0);
    ((Thunk7*)(p + 0x1d8))->Seven(0, 0, 0x19, 0, 2, 0, 0);
    ((Thunk7*)(p + 0x1fc))->Seven(0, 0, 1, 0, 2, 1, 0);
    return p;
}

// ---- 0x006783c0 : anchor window + animation (partial) ----------------
// @ 0x006783c0
void __fastcall FUN_006783c0(char* p) { (void)p; }

// ---- 0x00678670 : show/enable animation (partial) --------------------
// @ 0x00678670
void __fastcall FUN_00678670(char* p) { (void)p; }

// ---- 0x00678910 : update animation (partial) -------------------------
// @ 0x00678910
void __fastcall FUN_00678910(char* p, int a, int b) { (void)p; (void)a; (void)b; }
