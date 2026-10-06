// Slice s00f43a10 -- unnamed action/vector helpers, slice 7 of bfs1.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* __cdecl eastl_alloc(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl eastl_free(void* p);                                                                   // 0x00f47380

// ---------------------------------------------------------------- element stride 0x534
struct Sub534 { void destroy() throw(); };                 // 0x00f280f0
struct SubVec534 {
    char* begin;                                           // +0x00
    char* end;                                             // +0x04
    void destroyRange(char* first, char* last) throw();    // 0x00dfc600
};
struct T534 {
    Sub534 m0;                                             // +0x000 (empty, size 1)
    char   pad001[0x3c - 0x01];
    Sub534 m3c;                                            // +0x03c
    char   pad03d[0x84 - 0x3d];
    SubVec534 mvec;                                        // +0x084
    char   pad8c[0x534 - 0x8c];
    void Construct(const T534&) throw();
    void ConstructDefault() throw();
};
void __cdecl eastl_copy534(T534* first, T534* last, T534* dest);  // 0x00dfd2c0

struct Vec534 {
    T534* mpBegin; T534* mpEnd; T534* mpCapacity; char alloc[4];
    T534* insert(T534* pos, const T534& value);   // 0x00f44780
    void  DoInsert(T534* pos, const T534& value); // 0x00f2f050
    T534* pushBackDefault();                      // 0x00f446f0
    T534* erase(T534* pos);                       // 0x00f44190
};

// @ 0x00f44780
T534* Vec534::insert(T534* pos, const T534& value)
{
    int index = pos - mpBegin;
    if (pos == mpEnd && mpEnd != mpCapacity) {
        T534* p = mpEnd++;
        if (p != 0)
            p->Construct(value);
    } else {
        DoInsert(pos, value);
    }
    return mpBegin + index;
}

// @ 0x00f44190
T534* Vec534::erase(T534* pos)
{
    if ((char*)pos + 0x534 < (char*)mpEnd)
        eastl_copy534(pos + 1, mpEnd, pos);
    mpEnd = (T534*)((char*)mpEnd - 0x534);
    T534* last = mpEnd;
    last->mvec.destroyRange(last->mvec.begin, last->mvec.end);
    if (last->mvec.begin != 0 && *(int*)(last->mvec.begin - 4) != 0)
        eastl_free(last->mvec.begin);
    last->m3c.destroy();
    last->m0.destroy();
    return pos;
}

// @ 0x00f446f0  push_back() (default-constructed value)
T534* Vec534::pushBackDefault()
{
    if (mpEnd < mpCapacity) {
        T534* p = mpEnd++;
        if (p != 0)
            p->ConstructDefault();
        return p;
    }
    T534 temp;
    temp.ConstructDefault();
    DoInsert(mpEnd, temp);
    temp.mvec.destroyRange(temp.mvec.begin, temp.mvec.end);
    if (temp.mvec.begin != 0 && *(int*)(temp.mvec.begin - 4) != 0)
        eastl_free(temp.mvec.begin);
    temp.m3c.destroy();
    temp.m0.destroy();
    return mpEnd;
}

// ---------------------------------------------------------------- skeleton stubs (partial)
// @ 0x00f43a10
int f_43a10(int a, int b, int c, int d)
{
    (void)a; (void)b; (void)c; (void)d;
    return -1;
}

// @ 0x00f43af0
void f_43af0(void* self, int a, void* b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x00f43bf0
int f_43bf0(void* self, int a, int b, int c)
{
    (void)self; (void)a; (void)b; (void)c;
    return 0;
}

// @ 0x00f43f20
int f_43f20(void* self)
{
    (void)self;
    return 0;
}

// @ 0x00f440b0
int f_440b0(void* self, unsigned msg, int arg)
{
    (void)self; (void)msg; (void)arg;
    return 0;
}

// @ 0x00f44210
void f_44210(void* self, int idx)
{
    (void)self; (void)idx;
}

// @ 0x00f44370
void* f_44370(void* self, int a, void* b, void* c, float d)
{
    (void)self; (void)a; (void)b; (void)c; (void)d;
    return 0;
}

// @ 0x00f445c0
void* f_445c0(void* self, int* a)
{
    (void)self; (void)a;
    return 0;
}
