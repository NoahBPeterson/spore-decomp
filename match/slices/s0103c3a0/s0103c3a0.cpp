// Slice 34: named float-vector serializer wrapper (0x0103c3a0).
// Builds a wide name string (or "list" when there is none), opens it on the archive
// (vtable slot 0), serializes each float through FUN_00acabe0, closes it (slot 1).
#include "types.h"

// eastl::basic_string<wchar_t> layout as used here: {begin, end, capacity}, no allocator bytes.
struct WStrObj {
    wchar_t* b;
    wchar_t* e;
    wchar_t* c;
    WStrObj() {}
    WStrObj(const WStrObj& o);             // 0x0056e2d0 (thiscall, ret 4)
    void RangeInitialize(const wchar_t* p); // 0x00579a90 (thiscall, ret 4)
};

struct E4 { char d[4]; };
struct FloatVec { E4* b; E4* e; };

extern "C" {
void __cdecl FUN_00f47380(void* p);                                     // 0x00f47380 operator delete
WStrObj* __cdecl FUN_0093c5a0(WStrObj* out, const char* s, int n);      // 0x0093c5a0 EA::ConvertToString16
bool __cdecl FUN_00acabe0(void* ar, int z, E4* e, const wchar_t* tn);   // 0x00acabe0 element serializer
}

typedef void (__thiscall *ArStrFn)(void* self, const wchar_t* s);

static inline void ArCall(void* ar, int slot, const wchar_t* s)
{
    void** vt = *(void***)ar;
    ((ArStrFn)vt[slot])(ar, s);
}

// Heap-owned buffer check used by the inline string teardown: (cap - begin) & ~1 > 2 and begin != 0.
static inline void StrFree(const WStrObj& s)
{
    int n = (int)((char*)s.c - (char*)s.b) & ~1;
    if (n > 2 && s.b) FUN_00f47380(s.b);
}

// @ 0x0103c3a0
bool FUN_0103c3a0(void* ar, const char* name, FloatVec* v)
{
    bool ok = true;
    if (v->b != v->e) {
        WStrObj tmp;
        WStrObj w;
        WStrObj* piVar5;
        if (name == 0) {
            tmp.b = 0;
            tmp.e = 0;
            tmp.c = 0;
            tmp.RangeInitialize(0);
            piVar5 = &tmp;
        } else {
            piVar5 = FUN_0093c5a0(&w, name, -1);
        }
        WStrObj D(*piVar5);
        if (name == 0)
            StrFree(tmp);
        else
            StrFree(w);

        wchar_t* pwVar2 = D.b;
        ArCall(ar, 0, pwVar2 == D.e ? L"list" : pwVar2);

        E4* end = v->e;
        for (E4* p = v->b; p != end; p = p + 1)
            ok = ok && FUN_00acabe0(ar, 0, p, L"float");

        ArCall(ar, 1, pwVar2 == D.e ? L"list" : pwVar2);
        StrFree(D);
    }
    return ok;
}
