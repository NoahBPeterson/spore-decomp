// Slice s00ac9f70: gameplay serialization / EASTL range helpers.
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void  __cdecl FUN_00829110(void* a, void* b, void* c, void* d, void* e);
void  __cdecl FUN_00b93c60(uint n, void* p);
void  __cdecl FUN_00ac0730(void* a, void* b);
void  __cdecl FUN_00ac93c0(void* a, void* b, int c);
void  __cdecl FUN_00d5ccf0(void* p);
void  __cdecl FUN_00d576d0(void* p);
void  __cdecl FUN_00d5f780(void* p);
void* __cdecl FUN_00c8e820(int a);
void* __cdecl SP_GetSpeciesProfile(void* p);
void  __cdecl FUN_00c96e80(void* p);
void  __cdecl FUN_00695010(void* a, void* b);
void  __cdecl FUN_00694c10(void* a, void* b);
void  __cdecl FUN_007c3990(void* a, void* b, void* c);
void  __cdecl FUN_00693230(void* a, void* b);
void  __cdecl FUN_0093aa70(void* a, void* b, int c, int d);
void  __cdecl FUN_0093a780(void* a, void* b, int c, int d);
void  __fastcall FUN_00ae6970(void* p);
extern "C" void* DAT_015d8b54;
extern "C" char  DAT_015d8b56;
extern "C" char  DAT_015d8b59;

// @ 0x00ac9f70
void FUN_00ac9f70(void* obj, int param) {
    int base = param;
    int v = *(int*)(param + 0xc);
    void* r = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    int val = v;
    void* w = ((void* (__thiscall*)(void*))vc(r, 0x18))(r);
    FUN_0093aa70(w, &val, 1, 0);
    int* buckets = *(int**)(base + 4);
    void* node = (void*)*buckets;
    int* pp = buckets;
    if (!node) {
        pp = buckets + 1;
        int t = buckets[1];
        while (t == 0) { pp++; t = *pp; }
        node = (void*)*pp;
    }
    void* end = (void*)buckets[*(int*)(base + 8)];
    while (node != end) {
        void* r2 = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        int k = *(int*)node;
        int tmp = k;
        void* w2 = ((void* (__thiscall*)(void*))vc(r2, 0x18))(r2);
        FUN_0093aa70(w2, &tmp, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
        void* r3 = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        tmp = *(int*)((char*)node + 4);
        void* w3 = ((void* (__thiscall*)(void*))vc(r3, 0x18))(r3);
        FUN_0093aa70(w3, &tmp, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
        node = (void*)*((int*)node + 2);
        while (node == 0) {
            pp = pp + 1;
            node = (void*)*pp;
        }
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca0c0  (heap sift-down with functor compare; approximated)
void FUN_00aca0c0(void* arr, int n, int param3, int start, void* cb, int a4, int a5, int a6) {
    (void)arr; (void)n; (void)param3; (void)start; (void)cb; (void)a4; (void)a5; (void)a6;
}

// @ 0x00aca1f0
void FUN_00aca1f0(int* begin, int* end, int* key) {
    int n = (int)((char*)end - (char*)begin) >> 5;
    if (n > 0) {
        do {
            int h = n >> 1;
            if (begin[h * 8] < *key) {
                begin = begin + h * 8 + 8;
                h = n + (-1 - h);
            }
            n = h;
        } while (n > 0);
    }
}

// @ 0x00aca2f0
int FUN_00aca2f0(uchar* p, uchar* end, int out) {
    for (; p != end; p += 0x20) {
        *(void**)(p + 4) = (void*)0x145a164;
        uchar* b = *(uchar**)(p + 0xc);
        uchar* e2 = *(uchar**)(p + 0x10);
        for (; b < e2; b += 0xc) {
            void* o = *(void**)b;
            ((void (__thiscall*)(void*, int))vc(o, 0))(o, 0);
        }
        uchar* base = *(uchar**)(p + 0xc);
        if (base && *(int*)(base - 4) != 0)
            operator_delete(base);
        out += 0x20;
    }
    return out;
}

// @ 0x00aca360  (creature interaction; complex; approximated)
void FUN_00aca360(int param_1, void* creature) {
    (void)param_1; (void)creature;
}

// @ 0x00aca620  (hashtable read; approximated)
void FUN_00aca620(int* obj, int ht) {
    FUN_00693230((void*)(ht + 4), (void*)(ht + 8));
    *(int*)(ht + 0xc) = 0;
    int count = 0;
    (void)obj; (void)count;
}

// @ 0x00aca730
void FUN_00aca730(void* obj, int* vec) {
    void* r = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    int n = (vec[1] - vec[0]) >> 2;
    void* w = ((void* (__thiscall*)(void*))vc(r, 0x18))(r);
    FUN_0093aa70(w, &n, 1, 0);
    int* b = (int*)vec[0];
    int* e = (int*)vec[1];
    for (; b != e; b++) {
        uint v = 0;
        if (*b) v = ((uint (__thiscall*)(void*, int))vc((void*)*b, 0xc))((void*)*b, 0x179c807);
        ((void (__thiscall*)(void*, uint))vc(obj, 0x2c))(obj, v);
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca7b0
void FUN_00aca7b0(uchar* p, uchar* end) {
    if (p < end) {
        uint n = (((uint)(end - p) - 1) >> 5) + 1;
        do {
            *(void**)(p + 4) = (void*)0x145a164;
            uchar* b = *(uchar**)(p + 0xc);
            uchar* e2 = *(uchar**)(p + 0x10);
            for (; b < e2; b += 0xc) {
                void* o = *(void**)b;
                ((void (__thiscall*)(void*, int))vc(o, 0))(o, 0);
            }
            uchar* base = *(uchar**)(p + 0xc);
            if (base && *(int*)(base - 4) != 0)
                operator_delete(base);
            p += 0x20;
        } while (--n);
    }
}

// @ 0x00aca820
void __stdcall FUN_00aca820(int* p, int* end) {
    for (; p < end; p += 6) {
        int* e2 = (int*)p[2];
        for (int* it = (int*)p[1]; it < e2; it++) {
            void* o = (void*)*it;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
        int b = p[1];
        if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
}

// @ 0x00aca970
int* FUN_00aca970(int* obj, int* src) {
    void* o = *(void**)src;
    *obj = (int)o;
    if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
    FUN_00b93c60((src[2] - src[1]) >> 2, src + 4);
    int* ret = 0;
    FUN_00829110(&ret, (void*)src[1], (void*)src[2], (void*)obj[1], (void*)src);
    obj[2] = (int)ret;
    return obj;
}

// @ 0x00acaab0
int* FUN_00acaab0(int* p, int* end, int* out) {
    if (p != end) {
        int* cur = out;
        do {
            if (cur) {
                void* o = (void*)*p;
                *cur = (int)o;
                if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
                int n = (p[2] - p[1]) >> 2;
                int mem = 0;
                if (n) mem = (int)operator_new(n * 4, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                cur[1] = mem;
                cur[2] = mem;
                cur[3] = mem + n * 4;
                int* r = 0;
                FUN_00829110(&r, (void*)p[1], (void*)p[2], (void*)mem, (void*)end);
                cur[2] = (int)r;
            }
            p += 6; cur += 6;
        } while (p != end);
        return cur;
    }
    return out;
}

// @ 0x00acab70
int FUN_00acab70(int* p, int* end, int out) {
    for (; p != end; p += 6) {
        int* e2 = (int*)p[2];
        for (int* it = (int*)p[1]; it < e2; it++) {
            void* o = (void*)*it;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
        int b = p[1];
        if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        out += 0x18;
    }
    return out;
}

// @ 0x00acabe0  (EASTL string serialize; approximated)
char FUN_00acabe0(int* obj, int p2, int p3, int p4) {
    (void)obj; (void)p2; (void)p3; (void)p4;
    return 1;
}

// @ 0x00acadb0  (EASTL string serialize; approximated)
char FUN_00acadb0(int* obj, int p2, int p3, int p4) {
    (void)obj; (void)p2; (void)p3; (void)p4;
    return 1;
}

// @ 0x00acaf80  (EASTL string serialize; approximated)
char FUN_00acaf80(int* obj, int p2, int p3, int p4) {
    (void)obj; (void)p2; (void)p3; (void)p4;
    return 1;
}

// @ 0x00acb150
void* FUN_00acb150(void* self, uchar flags) {
    *(void**)self = (void*)0x145a184;
    FUN_00ae6970((uchar*)self + 0x50);
    FUN_00ae6970((uchar*)self + 0x3c);
    FUN_00ae6970((uchar*)self + 0x28);
    FUN_00ae6970((uchar*)self + 0x14);
    if (flags & 1) operator_delete(self);
    return self;
}

// @ 0x00acb190
void __fastcall FUN_00acb190(void* self) {
    *(int*)((uchar*)self + 4) -= 0x18;
    uchar* v = *(uchar**)((uchar*)self + 4);
    FUN_00ae6970(v + 4);
    void* o = *(void**)v;
    if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
}
