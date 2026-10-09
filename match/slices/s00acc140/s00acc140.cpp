// Slice s00acc140: SP::cCityVisualizer helpers + vector copy/erase utilities.
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void  __cdecl FUN_00ac97f0(void* a, void* b, void* c);
void  __cdecl FUN_00ac89a0(void* a, void* b, void* c);
void* __cdecl FUN_00ac95a0(void* a, void* b, void* c);
void  __cdecl FUN_00ac94c0(void* a, void* b, void* c, void* d, void* e);
void* __cdecl FUN_00ac89e0(void* a, void* b, void* c);
void* __cdecl FUN_00aca1f0(int* a, int* b, int* k, int c);
void* __cdecl FUN_00b33f40();
void* __cdecl FUN_00b3d310();
void  __cdecl FUN_00b48770(void* a, int b);
void  __cdecl FUN_00c0cff0(int a);
void  __cdecl FUN_00a02b00(int a);
extern "C" void* DAT_01654c04;
extern "C" void* DAT_01654c02;

struct XC {
    void  FUN_00acbd90();
    void  FUN_01011cc0(void*);
    void  FUN_00ac97f0(void*, void*);
    void  FUN_00ac89a0(void*, void*);
    void* FUN_00ac95a0(void*);
    void  FUN_00acb680(void*);
    void  FUN_00acb810(void*);
    void  FUN_00acb930(int, void*);
    void  FUN_00acb7c0(void*, void*);
    void  FUN_00c232b0();
    void  FUN_00c232c0();
    int   FUN_00c0c0e0();
    void* FUN_00c0bc00();
    void  FUN_00a05270();
};

// thiscall member functions of the vector owner
struct VO {
    int* v;
    void  FUN_00acc140(uchar* pos, uchar* val);
    void  FUN_00acc610(int* p);
    void  FUN_00acc700(void* p, float a, float b);
    void  FUN_00acc770();
    void  FUN_00acc9b0(uint n);
    void  FUN_00accf80(int* p);
    void  FUN_00acd2d0(int* p);
    void  FUN_00acd410(int* p);
};

// free functions
void  FUN_00acc800(int* v);
void  FUN_00acc390(int p);
void  FUN_00accd70(int arr, uint n);
int*  FUN_00acc2d0(int* p, int* end, int* out);
int*  FUN_00acc330(int end, int begin, int* out);
void* FUN_00accec0(uchar* p, uchar* end, uchar* out);
void* FUN_00accf20(int end, int begin, int out);
char  FUN_00acca00(int* vec, int* val);

// @ 0x00acc2d0
int* FUN_00acc2d0(int* p, int* end, int* out) {
    if (p == end) return out;
    do {
        int* a = (int*)*p;
        int* b = (int*)*out;
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *out = (int)a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        ((XC*)(p + 1))->FUN_01011cc0(out + 1);
        p += 6; out += 6;
    } while (p != end);
    return out;
}

// @ 0x00acc330
int* FUN_00acc330(int end, int begin, int* out) {
    if (begin == end) return out;
    int nxt;
    do {
        int* a = *(int**)(end - 0x18);
        int* b = (int*)out[-6];
        int nxt = end - 0x18;
        out -= 6;
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *out = (int)a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        ((XC*)(end - 0x14))->FUN_01011cc0(out + 1);
        end = nxt;
    } while (nxt != begin);
    return out;
}

// @ 0x00accec0
void* FUN_00accec0(uchar* p, uchar* end, uchar* out) {
    if (p != end) {
        uchar* o = out;
        do {
            *(int*)o = *(int*)p;
            *(o + 8) = *(p + 8);
            *(o + 9) = *(p + 9);
            ((XC*)(o + 0xc))->FUN_00acbd90();
            p += 0x20; o += 0x20;
        } while (p != end);
        return o;
    }
    return out;
}

// @ 0x00accf20
void* FUN_00accf20(int end, int begin, int out) {
    if (end != begin) {
        uchar* s = (uchar*)(end + 9);
        uchar* d = (uchar*)(out + 9);
        do {
            *(int*)(out - 0x20) = *(int*)(end - 0x20);
            end -= 0x20; out -= 0x20;
            d[-0x21] = s[-0x21];
            d[-0x20] = s[-0x20];
            ((XC*)(d - 0x1d))->FUN_00acbd90();
            s -= 0x20; d -= 0x20;
        } while (end != begin);
        return d;
    }
    return (void*)out;
}

// @ 0x00acca00
char FUN_00acca00(int* vec, int* val) {
    int* p = (int*)*vec;
    int* end = (int*)vec[1];
    if (p != end) {
        do {
            if (*p == *val) {
                if (p + 1 < end) {
                    // shift left
                    int* d = p;
                    int* s = p + 1;
                    for (; s < end; s++, d++) *d = *s;
                }
                vec[1] -= 4;
                int* last = (int*)vec[1];
                if (*last) ((void (__thiscall*)(void*))vc((void*)*last, 4))((void*)*last);
                return 1;
            }
            p++;
        } while (p != end);
    }
    return 0;
}

// @ 0x00acc140
void VO::FUN_00acc140(uchar* pos, uchar* val) {
    int* p = (int*)this;
    uchar* cur = (uchar*)p[1];
    if (cur != (uchar*)p[2]) {
        if (pos <= val && val < cur) val += 0xc;
        if (cur) {
            *(void**)cur = (void*)0x145a158;
            *(cur + 4) = *(cur - 8);
            void* o = *(void**)(cur - 4);
            *(void**)(cur + 8) = o;
            if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        }
        FUN_00ac97f0(pos, (void*)(p[1] - 0xc), (void*)p[1]);
        *(pos + 4) = *(val + 4);
        void* a = *(void**)(val + 8);
        void* b = *(void**)(pos + 8);
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *(void**)(pos + 8) = a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        p[1] += 0xc;
        return;
    }
    int n = (int)(cur - (uchar*)p[0]) / 0xc;
    int cap = n ? n * 2 : 1;
    uchar* mem = cap ? (uchar*)operator_new(cap * 0xc, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    int old = p[0];
    void* e1 = FUN_00ac95a0((void*)old, pos, mem);
    FUN_00ac89a0((void*)old, pos, mem);
    if (e1) {
        *(void**)e1 = (void*)0x145a158;
        *(uchar*)((uchar*)e1 + 4) = *(uchar*)(val + 4);
        void* o = *(void**)(val + 8);
        *(void**)((uchar*)e1 + 8) = o;
        if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
    }
    int oldend = p[1];
    void* e2 = FUN_00ac95a0(pos, (void*)oldend, (uchar*)e1 + 0xc);
    FUN_00ac89a0(pos, (void*)oldend, (uchar*)e1 + 0xc);
    if (old && *(int*)(old - 4) != 0) operator_delete((void*)old);
    p[1] = (int)e2;
    p[0] = (int)mem;
    p[2] = (int)(mem + cap * 0xc);
}

// @ 0x00acc610  (remove from vector of 0x18 blocks)
void VO::FUN_00acc610(int* p) {
    if (!p) return;
    if (((void* (__thiscall*)(void*))vc(p, 0x20))(p) != (void*)0x18eb4b7) return;
    int n = (*(int*)((uchar*)this + 0xac) - *(int*)((uchar*)this + 0xa8)) / 0x18;
    int i = 0;
    if (n <= 0) return;
    uchar* base = *(uchar**)((uchar*)this + 0xa8);
    while (i < n) {
        uchar* b = base + i * 0x18;
        int* a = *(int**)(b + 4);
        int* e = *(int**)(b + 8);
        for (; a != e; a++) if (*a == (int)p) break;
        if (a != e) {
            // remove and call vcall
            if (a + 1 < e) {
                int* d = a;
                for (int* s = a + 1; s < e; s++, d++) *d = *s;
            }
            *(int*)(b + 8) -= 4;
            void* o = *(void**)(b + 8);
            if (*(int*)o) ((void (__thiscall*)(void*))vc((void*)*(int*)o, 9))((void*)*(int*)o);
            return;
        }
        i++;
    }
}

// @ 0x00acc700
void VO::FUN_00acc700(void* p, float a, float b) {
    int* v = (int*)this;
    uchar* cur = (uchar*)v[9];
    if (cur < (uchar*)v[10]) {
        v[9] = (int)(cur + 0x14);
    } else {
        ((XC*)(v + 8))->FUN_00acb680(cur);
    }
    uchar* e = (uchar*)(*(int*)((uchar*)this + 0x24) - 0x14);
    *(int*)e = *(int*)p;
    *(int*)(e + 4) = *(int*)((uchar*)p + 4);
    *(int*)(e + 8) = *(int*)((uchar*)p + 8);
    *(float*)(e + 0xc) = a * a;
    *(float*)(e + 0x10) = b * b;
}

// @ 0x00acc770
void VO::FUN_00acc770() {
    uchar* p = (uchar*)this;
    int n = (*(int*)(p + 0x11c) - *(int*)(p + 0x118)) >> 2;
    for (int i = 0; i < n; i++) {
        int* o = (int*)FUN_00b33f40();
        ((void (__thiscall*)(void*, int))vc(o, 0x3c))(o, *(int*)(*(int*)(p + 0x118) + i * 4));
    }
    int b = *(int*)(p + 0x118);
    int e = *(int*)(p + 0x11c);
    int* it = (int*)FUN_00ac89e0((void*)e, (void*)e, (void*)b);
    int* end = *(int**)(p + 0x11c);
    for (; it < end; it++) if (*it) ((XC*)*it)->FUN_00a05270();
    *(int*)(p + 0x11c) -= (e - b) >> 2 << 2;
}

// @ 0x00acc800  (LoadSelector; approximated)
void FUN_00acc800(int* v) {
    (void)v;
}

// @ 0x00acc9b0
void VO::FUN_00acc9b0(uint n) {
    int* v = (int*)this;
    int* b = (int*)v[0];
    int* e = (int*)v[1];
    if ((uint)(e - b) < n) {
        int add = n - (int)(e - b);
        int z = 0;
        ((XC*)(v + 1))->FUN_00acb930(add, &z);
        return;
    }
    ((XC*)(v + 1))->FUN_00acb7c0(b + n, e);
}

// @ 0x00accf80  (SetupCultureStages; complex; approximated)
void VO::FUN_00accf80(int* p) {
    (void)p;
}

// @ 0x00acd210
void FUN_00acd210(void* self) {
    (void)self;
}

// @ 0x00acd2d0  (property handler; approximated)
void VO::FUN_00acd2d0(int* p) {
    (void)p;
}

// @ 0x00acd410  (property handler; approximated)
void VO::FUN_00acd410(int* p) {
    (void)p;
}

// @ 0x00acc390  (sGetClosestRare; approximated)
void FUN_00acc390(int p) {
    (void)p;
}

// @ 0x00accd70
void FUN_00accd70(int arr, uint n) {
    for (uint i = 0; i < n; i++) {
        int node = *(int*)(arr + i * 4);
        while (node != 0) {
            int next = *(int*)(node + 0x68);
            *(void**)(node + 4) = (void*)0x145a184;
            int* e = *(int**)(node + 0x58);
            for (int* it = *(int**)(node + 0x54); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            int b = *(int*)(node + 0x54);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x44);
            for (int* it = *(int**)(node + 0x40); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x40);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x30);
            for (int* it = *(int**)(node + 0x2c); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x2c);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x1c);
            for (int* it = *(int**)(node + 0x18); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x18);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            operator_delete((void*)node);
            node = next;
        }
        *(int*)(arr + i * 4) = 0;
    }
}
// --- equivalence checker address annotations
    void operator_delete(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
