// Slice s00acb1b0: vector/EASTL range helpers (0x145a184 class).
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void  __cdecl FUN_00829110(void* a, void* b, void* c, void* d, void* e);
void* __cdecl FUN_00ac96b0(void* a, void* b, void* c);
void* __cdecl FUN_00f9b050(void* a, void* b, void* c);
void  __cdecl FUN_00c50ad0(void* a, void* b, void* c);
void* __cdecl FUN_00ac9740(void* a, void* b, void* c);
void* __cdecl FUN_00ac89e0(void* a, void* b, void* c);
void* __cdecl FUN_00acaa50(uint n, void* a, void* b);
void  __cdecl FUN_00ac8930(void* a, void* b);
void  __cdecl FUN_00ac94c0(void* a, void* b, void* c, void* d, void* e);
void  __cdecl FUN_00ac9200(void* a);

// generic thiscall stubs
struct XC {
    void  FUN_00aca9d0(void*);
    void  FUN_00b93c60(uint, void*);
    void  FUN_00a05270();
    void  FUN_00a02c30();
};

// thiscall member functions of the vector-owner class
struct VO {
    int* v;                       // +0 begin
    void* FUN_00acb490(int* src); // 00acb490
    void  FUN_00acb680(uchar* pos, uchar* val);
    void  FUN_00acb7c0(void* a2, void* a3);
    void  FUN_00acb810(uchar* pos, uchar* val);
    void  FUN_00acb930(int a2, int a3, int a4);
    void* FUN_00acbaf0(int* src);
    int*  FUN_00acbd90(int* other);
    int   FUN_00acbed0(int a2, int a3);
    void  FUN_00acbf30(int a2, uint a3, int a4);
};

// free (cdecl) functions
char FUN_00acb1b0(int* obj, int p2, int p3);          // 00acb1b0
char FUN_00acb340(int* obj, int p2, int* p3);         // 00acb340
void* FUN_00acbb20(uchar* p, uchar* end, uchar* out); // 00acbb20
char FUN_00acbc10(int* obj, int p2, int p3);          // 00acbc10

// @ 0x00acb490
void* VO::FUN_00acb490(int* src) {
    int* p = (int*)this;
    p[0] = 0x145a184;
    p[1] = src[1];
    p[2] = src[2];
    p[3] = src[3];
    p[4] = src[4];
    ((XC*)((uchar*)p + 0x14))->FUN_00b93c60((src[6] - src[5]) >> 2, (uchar*)src + 0x20);
    int* tmp = 0;
    FUN_00829110(&tmp, (void*)src[5], (void*)src[6], (void*)p[5], (void*)src);
    p[6] = (int)tmp;
    ((XC*)((uchar*)p + 0x28))->FUN_00b93c60((src[10] - src[9]) >> 2, (uchar*)src + 0x34);
    tmp = 0;
    FUN_00829110(&tmp, (void*)src[9], (void*)src[10], (void*)p[10], (void*)src);
    p[0xb] = (int)tmp;
    ((XC*)((uchar*)p + 0x3c))->FUN_00b93c60((src[0x10] - src[0xf]) >> 2, (uchar*)src + 0x48);
    tmp = 0;
    FUN_00829110(&tmp, (void*)src[0xf], (void*)src[0x10], (void*)p[0xf], (void*)src);
    p[0x10] = (int)tmp;
    ((XC*)((uchar*)p + 0x50))->FUN_00b93c60((src[0x15] - src[0x14]) >> 2, (uchar*)src + 0x5c);
    tmp = 0;
    FUN_00829110(&tmp, (void*)src[0x14], (void*)src[0x15], (void*)p[0x14], (void*)src);
    p[0x15] = (int)tmp;
    return p;
}

// @ 0x00acb680
void VO::FUN_00acb680(uchar* pos, uchar* val) {
    int* v = (int*)this;
    uchar* cur = (uchar*)v[1];
    if (cur != (uchar*)v[2]) {
        if (pos <= val && val < cur) val += 0x14;
        if (cur) memcpy(cur, cur - 0x14, 0x14);
        FUN_00c50ad0(pos, (void*)(v[1] - 0x14), (void*)v[1]);
        memcpy(pos, val, 0x14);
        v[1] += 0x14;
        return;
    }
    int n = (int)(cur - (uchar*)v[0]) / 0x14;
    int cap = n ? n * 2 : 1;
    uchar* mem = cap ? (uchar*)operator_new(cap * 0x14, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    uchar* p1 = (uchar*)FUN_00f9b050((void*)v[0], pos, mem);
    if (p1) memcpy(p1, val, 0x14);
    uchar* p2 = (uchar*)FUN_00f9b050(pos, (void*)v[1], p1 + 0x14);
    void* old = (void*)v[0];
    if (old && *(int*)((char*)old - 4) != 0) operator_delete(old);
    v[0] = (int)mem;
    v[1] = (int)p2;
    v[2] = (int)(mem + cap * 0x14);
}

// @ 0x00acb7c0
void VO::FUN_00acb7c0(void* a2, void* a3) {
    int* p = (int*)this;
    int* it = (int*)FUN_00ac89e0(a3, *(void**)((uchar*)p + 4), a2);
    int* end = *(int**)((uchar*)p + 4);
    for (; it < end; it++) {
        if (*it) ((XC*)*it)->FUN_00a05270();
    }
    int n = (int)((char*)a3 - (char*)a2) >> 2;
    *(int*)((uchar*)p + 4) -= n * 4;
}

// @ 0x00acb810  (vector<0x2c> insert; approximated)
void VO::FUN_00acb810(uchar* pos, uchar* val) {
    (void)pos; (void)val;
}

// @ 0x00acb930  (vector ctor/assign; approximated)
void VO::FUN_00acb930(int a2, int a3, int a4) {
    (void)a2; (void)a3; (void)a4;
}

// @ 0x00acbaf0
void* VO::FUN_00acbaf0(int* src) {
    uchar* d = (uchar*)this;
    *(int*)d = *src;
    *(void**)(d + 4) = (void*)0x145a164;
    *(d + 8) = *(uchar*)((uchar*)src + 8);
    *(d + 9) = *(uchar*)((uchar*)src + 9);
    ((XC*)(d + 0xc))->FUN_00aca9d0((uchar*)src + 0xc);
    return d;
}

// @ 0x00acbd90
int* VO::FUN_00acbd90(int* other) {
    int* v = (int*)this;
    if (other != v) {
        int src0 = *other;
        uint n2 = (other[1] - src0) / 0xc;
        int dst0 = *v;
        if ((uint)((v[2] - dst0) / 0xc) < n2) {
            int mem = (int)FUN_00acaa50(n2, (void*)src0, (void*)other[1]);
            FUN_00ac8930((void*)*v, (void*)v[1]);
            int old = *v;
            if (old && *(int*)(old - 4) != 0) operator_delete((void*)old);
            v[2] = mem + n2 * 0xc;
            *v = mem;
            v[1] = mem + n2 * 0xc;
            return v;
        }
        uint u3 = (v[1] - dst0) / 0xc;
        if (u3 < n2) {
            FUN_00ac9740((void*)src0, (void*)(src0 + u3 * 0xc), (void*)dst0);
            int p = other[1];
            int tmp = p;
            FUN_00ac94c0(&tmp, (void*)(*other + ((v[1] - *v) / 0xc) * 0xc), (void*)p, (void*)v[1], (void*)p);
            v[1] = *v + n2 * 0xc;
            return v;
        }
        int r = (int)FUN_00ac9740((void*)src0, (void*)other[1], (void*)dst0);
        FUN_00ac8930((void*)r, (void*)v[1]);
        v[1] = *v + n2 * 0xc;
    }
    return v;
}

// @ 0x00acbed0
int VO::FUN_00acbed0(int a2, int a3) {
    int* p = (int*)this;
    int* it = (int*)FUN_00ac9740((void*)a3, *(void**)((uchar*)p + 4), (void*)a2);
    int* end = *(int**)((uchar*)p + 4);
    for (; it < end; it += 3) {
        void* o = (void*)*it;
        ((void (__thiscall*)(void*, int))vc(o, 0))(o, 0);
    }
    int n = (a3 - a2) / 0xc;
    *(int*)((uchar*)p + 4) += n * 0xc;
    return a2;
}

// @ 0x00acbf30  (vector<0x18> insert; approximated)
void VO::FUN_00acbf30(int a2, uint a3, int a4) {
    (void)a2; (void)a3; (void)a4;
}

// @ 0x00acb1b0  (serialize map<string,int>; approximated)
char FUN_00acb1b0(int* obj, int p2, int p3) {
    (void)obj; (void)p2; (void)p3;
    return 1;
}

// @ 0x00acb340  (serialize vector; approximated)
char FUN_00acb340(int* obj, int p2, int* p3) {
    (void)obj; (void)p2; (void)p3;
    return 1;
}

// @ 0x00acbb20
void* FUN_00acbb20(uchar* p, uchar* end, uchar* out) {
    if (p != end) {
        uchar* o = out;
        do {
            if (o) {
                *(int*)o = *(int*)p;
                *(void**)(o + 4) = (void*)0x145a164;
                *(o + 8) = *(p + 8);
                *(o + 9) = *(p + 9);
                ((XC*)(o + 0xc))->FUN_00aca9d0(p + 0xc);
            }
            p += 0x20; o += 0x20;
        } while (p != end);
        return o;
    }
    return out;
}

// @ 0x00acbc10  (serialize hashtable; approximated)
char FUN_00acbc10(int* obj, int p2, int p3) {
    (void)obj; (void)p2; (void)p3;
    return 1;
}
