// Slice s00683f80: App/cConversationFactory + SP cube-coordinate helpers (0x00683f80-0x00684ca0).
#include "../../include/types.h"

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void* __cdecl EASTL_alloc(unsigned, const char*, int, int, const char*, int);
extern "C" void  __cdecl EASTL_dealloc_(void*);
extern "C" void* __cdecl FUN_00684420(int*);
extern "C" void* __cdecl FUN_00683480(int*);
extern "C" void* __cdecl FUN_00683560(void*, int*, int*);
extern "C" void* __cdecl FUN_00683500(void*, int*, int*, int);
extern "C" void* __cdecl FUN_00683670(void*);
extern "C" void  __cdecl FUN_006841a0(void*, void*);
extern "C" void  __cdecl FUN_00684a90(void*, void*);
extern "C" void  __cdecl FUN_00684740(void*, void*);
extern "C" void* __cdecl FUN_00683d10(void*);
extern "C" void* __cdecl FUN_00683e90();
extern "C" void* __cdecl FUN_00681250(void*, void*);
extern "C" void* __cdecl FUN_006812c0(void*, void*);
extern "C" void* __cdecl FUN_00683700(void*, void*);
extern "C" void* __cdecl FUN_00681f10(void*, void*);
extern "C" void* __cdecl FUN_00681480(void*);
extern "C" void* __cdecl FUN_00680fc0(void*, void*);
extern "C" void* __cdecl FUN_00682ca0(void*, void*);
extern "C" void* __cdecl FUN_006823f0(void*, void*);
extern "C" void* __cdecl FUN_00682e90(void*, void*);
extern "C" void* __cdecl FUN_00683ab0(void*, void*);
extern "C" void* __cdecl FUN_00683160(void*);
extern "C" void* __cdecl FUN_00681500(void*);
extern "C" void* __cdecl FUN_00682800(void*);
extern "C" void* __cdecl FUN_00680b70(void*, void*);
extern "C" void* __cdecl RBTreeIncrement(void*);
extern "C" void* __cdecl RBTreeDecrement(void*);
extern "C" void  __cdecl RBTreeInsert(void*, void*, void*, int);
extern "C" void* __cdecl ReadInt32(void*, void*, int, int);
extern "C" void* __cdecl WriteUint32(void*, void*, int, int);
extern "C" void  __cdecl StringResize(void*, int);
extern "C" void  __cdecl FUN_01667bac_dummy();
extern char g_1402d55[];

// ===========================================================================
// @ 0x00683F80  cConversationFactory-ish destructor (partial, EH)
// ===========================================================================
void dtor_683f80(void** p)
{
    FUN_00680b70(p[0x1b], p[0x1c]);
    int i = (int)p[0x1b];
    if (i && *(int*)(i - 4) != 0)
        EASTL_dealloc_((void*)i);
    FUN_00683160(p[0x17]);
    FUN_00681500(p[0x10]);
    FUN_00682800(p[9]);
    *p = (void*)0;
}

// ===========================================================================
// @ 0x00684040  factory create (partial)
// ===========================================================================
int create_684040(int* self, int* mgr, int a, int b, int c)
{
    void* mem = EASTL_alloc(0x80, "App/cConversationFactory", 0, 0, 0, 0);
    int* obj = mem ? (int*)FUN_00683e90() : 0;
    int* v = (int*)((void* (__thiscall*)(void*))VT(mgr)[0x10 / 4])(mgr);
    obj[2] = v[0];
    obj[3] = v[1];
    obj[4] = v[2];
    if (((char (__thiscall*)(void*, int*, int*, int, int))VT(self)[0x24 / 4])(self, mgr, obj, b, c)) {
        *(int**)0 = obj;
        ((void (__thiscall*)(void*))VT(obj)[0])(obj);
        return 1;
    }
    ((void (__thiscall*)(void*, int))VT(obj)[8 / 4])(obj, 1);
    return 0;
}

// ===========================================================================
// @ 0x006840D0  read collection (partial)
// ===========================================================================
void read_6840d0(void* unused, int* stream)
{
    char buf[8];
    ((void (__thiscall*)(void*, void*, int))VT(stream)[0x30 / 4])(stream, buf, 4);
    unsigned count = *(unsigned*)buf;
    for (unsigned i = 0; i < count; ++i) {
        int key;
        ((void (__thiscall*)(void*, int*, int))VT(stream)[0x30 / 4])(stream, &key, 4);
        int* node = (int*)FUN_00683d10(&key);
        if (*(char**)node != (char*)node[1]) {
            *(char*)node[0] = 0;
            node[1] = node[0];
        }
        int len;
        ReadInt32(stream, &len, 1, 0);
        if (len) {
            StringResize((void*)len, 0);
            ((void (__thiscall*)(void*, void*, int))VT(stream)[0x30 / 4])(stream, (void*)node[0], len);
        }
        FUN_00681250(node + 4, stream);
        FUN_00681250(node + 9, stream);
    }
}

// ===========================================================================
// @ 0x006841A0  write collection (partial, EH)
// ===========================================================================
void write_6841a0(int self, int* stream)
{
    int v = *(int*)(self + 0x14);
    ((void (__thiscall*)(void*, int*, int))VT(stream)[0x38 / 4])(stream, &v, 4);
    for (int n = *(int*)(self + 8); n != self + 4; n = (int)RBTreeIncrement((void*)n)) {
        FUN_00683670((void*)(n + 0x14));
        int len = 0;
        ((void (__thiscall*)(void*, int*, int))VT(stream)[0x38 / 4])(stream, &len, 4);
        WriteUint32(stream, &len, 1, 0);
        FUN_00681f10((void*)(n + 0x14), stream);
        FUN_00681480((void*)0);
    }
}

// ===========================================================================
// @ 0x006842C0  serialize app object (complete-ish)
// ===========================================================================
int ser_6842c0(int* a, int* b)
{
    int i = a ? ((int (__thiscall*)(void*, int))VT(a)[0xc / 4])(a, 0x355d6f5) : 0;
    void* u = ((void* (__thiscall*)(void*))VT(b)[0x18 / 4])(b);
    FUN_006841a0((void*)(i + 0x50), u);
    FUN_00682ca0((void*)(i + 0x18), u);
    FUN_00680fc0((void*)(i + 0x34), u);
    FUN_006823f0((void*)(i + 0x6c), u);
    return 1;
}

// ===========================================================================
// @ 0x00684330  rbtree insert-or-assign (partial)
// ===========================================================================
void insert_684330(int self, void** out, int* at, int* key)
{
    (void)self; (void)out; (void)at; (void)key;
}

// ===========================================================================
// @ 0x006844A0  rbtree insert wrapper (member)
// ===========================================================================
struct Map844 {
    char pad0[4];
    void* head;    // +0x04
    void* tail;    // +0x08
    char padc[8];
    int count;     // +0x14
    void* allocNode(int* key);   // FUN_00684420
    void insert(void** out, void* at, int* key, char flag);
};

void Map844::insert(void** out, void* at, int* key, char flag)
{
    int f = (!flag && at != (char*)this + 4 && *key >= *(int*)((char*)at + 0x10)) ? 1 : 0;
    void* node = allocNode(key);
    RBTreeInsert(node, at, (char*)this + 4, f);
    count += 1;
    *out = node;
}

// ===========================================================================
// @ 0x00684500  rbtree find-or-insert (partial)
// ===========================================================================
void insert_684500(int self, void** out, int* key)
{
    (void)self; (void)out; (void)key;
}

// ===========================================================================
// @ 0x00684610 / 0x00684980  map[] access (partial, EH)
// ===========================================================================
void* index_684610(int self, int* key)
{
    (void)self; (void)key;
    return 0;
}

// ===========================================================================
// @ 0x00684740  read records (partial)
// ===========================================================================
void read_684740(void* unused, int* stream)
{
    int count = 0;
    ((void (__thiscall*)(void*, int*, int))VT(stream)[0x30 / 4])(stream, &count, 4);
    for (int i = 0; i < count; ++i) {
        int key;
        ((void (__thiscall*)(void*, int*, int))VT(stream)[0x30 / 4])(stream, &key, 4);
        void* node = index_684610(0, &key);
        (void)node;
    }
}

// ===========================================================================
// @ 0x00684890  rbtree insert-or-assign (partial)
// ===========================================================================
void insert_684890(int self, void** out, int* at, int* key)
{
    (void)self; (void)out; (void)at; (void)key;
}

// ===========================================================================
// @ 0x00684980  map[] access (partial, EH)
// ===========================================================================
void* index_684980(int self, int* key)
{
    (void)self; (void)key;
    return 0;
}

// ===========================================================================
// @ 0x00684A90  read records (partial)
// ===========================================================================
void read_684a90(void* unused, int* stream)
{
    read_6840d0(unused, stream);
}

// ===========================================================================
// @ 0x00684B40  serialize factory (partial)
// ===========================================================================
int ser_684b40(int* a, int* b)
{
    int i = ((int (__thiscall*)(void*))VT(a)[0x1c / 4])(a);
    if (i) {
        i = ((int (__thiscall*)(void*, int))VT(*(void**)(i + 4))[0xc / 4])(*(void**)(i + 4), 0x226a1de);
        if (i) return 0;
    }
    void* u = ((void* (__thiscall*)(void*))VT(a)[0x18 / 4])(a);
    int j = b ? ((int (__thiscall*)(void*, int))VT(b)[0xc / 4])(b, 0x355d6f5) : 0;
    FUN_00684a90((void*)(j + 0x50), u);
    FUN_00684740((void*)(j + 0x18), u);
    FUN_00682e90((void*)(j + 0x34), u);
    FUN_00683ab0((void*)(j + 0x6c), u);
    return 1;
}

// ===========================================================================
// @ 0x00684BE0  float -> int
// ===========================================================================
int __cdecl TruncFloat_684be0(float p)
{
    return (int)p;
}

// ===========================================================================
// @ 0x00684BF0  SP::CoordToIndex
// ===========================================================================
int* __cdecl SP_CoordToIndex(int* out, int n, float* c)
{
    out[2] = ((int*)c)[2];
    int x = (int)((float)n * c[0]);
    out[0] = x;
    int y = (int)(c[1] * (float)n);
    out[1] = y;
    if (x == n)
        out[0] = x - 1;
    if (y == n)
        out[1] = y - 1;
    return out;
}

// ===========================================================================
// @ 0x00684C50  index -> coordinate
// ===========================================================================
void __cdecl IndexToCoord_684c50(float* out, int n, int* c)
{
    float f = (float)c[2];
    float inv = 1.0f / (float)n;
    out[0] = ((float)c[0] + 0.5f) * inv;
    out[2] = f;
    out[1] = ((float)c[1] + 0.5f) * inv;
}

// ===========================================================================
// @ 0x00684CA0  SP::WrapCubeFace
// ===========================================================================
int __cdecl SP_WrapCubeFace(int n, uint32_t* face, uint32_t* x, int* y, int* u, int* v)
{
    uint32_t p = *face & 1;
    uint32_t q = p ^ 1;
    int s = p * -2 + 1;
    uint32_t xv = *x;
    int ns = -s;
    if ((int)xv < 0) {
        *x = xv + n;
        uint32_t nm1 = n - 1;
        *x = *y * ns + nm1 * q;
        *y = nm1 * p + (xv + n) * s;
        *face = q + (uint32_t)(uint8_t)g_1402d55[((int)*face >> 1) * 4] * 2;
        if (u) {
            int t = *u;
            *u = *v * ns;
            *v = t * s;
        }
        if ((*x & ~nm1) == 0)
            return 1;
    } else if ((int)xv < n) {
        int yv = *y;
        if (yv < 0) {
            *y = yv + n;
            uint32_t xc = *x;
            *x = (yv + n) * ns + (n - 1) * q;
            *y = (n - 1) * p + xc * s;
            *face = (uint32_t)(uint8_t)g_1402d55[1 + ((int)*face >> 1) * 4] * 2 + 1;
        } else if (yv < n) {
            return 0;
        } else {
            *y = yv - n;
            uint32_t xc = *x;
            *x = (yv - n) * ns + (n - 1) * q;
            *y = (n - 1) * p + xc * s;
            *face = (uint32_t)(uint8_t)g_1402d55[1 + ((int)*face >> 1) * 4] * 2;
        }
        if (!u)
            return 1;
        int t = *u;
        *u = *v * ns;
        *v = t * s;
        return 1;
    } else {
        *x = xv - n;
        uint32_t nm1 = n - 1;
        *x = *y * s + nm1 * p;
        *y = nm1 * q + (xv - n) * ns;
        *face = p + (uint32_t)(uint8_t)g_1402d55[((int)*face >> 1) * 4] * 2;
        if (u) {
            int t = *u;
            *u = *v * s;
            *v = t * ns;
        }
        if ((*x & ~nm1) == 0)
            return 1;
    }
    return SP_WrapCubeFace(n, face, x, y, u, v) + 1;
}
