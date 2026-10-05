// Slice s0074c260: cModelWorld draw/occluder helpers (~0x0074c260-0x0074d2c0).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"

extern "C" void* __cdecl memmove_(void* dst, const void* src, unsigned size);

// ---------------------------------------------------------------------------
// @ 0x0074CA70  vector<int>::remove_first / erase-by-value
// ---------------------------------------------------------------------------
struct VecInt {
    char pad0[0x4c];
    int* begin;   // +0x4c
    int* end;     // +0x50
    bool remove_first(int v);
};

bool VecInt::remove_first(int v)
{
    int n = (int)((char*)end - (char*)begin) >> 2;
    if (n > 0) {
        int i = 0;
        int* p = begin;
        do {
            if (*p == v) {
                int* dst = begin + i;
                int* src = dst + 1;
                if (src < end)
                    memmove_(dst, src, (unsigned)((char*)end - (char*)src));
                end = (int*)((char*)end - 4);
                return true;
            }
            ++i;
            ++p;
        } while (i < n);
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0074CDD0  vector<E18>::push_back (element 0x18)
// ---------------------------------------------------------------------------
struct E18 {
    float a, b, c, d, e, f;
    E18& operator=(const E18& o) { a = o.a; b = o.b; c = o.c; d = o.d; e = o.e; f = o.f; return *this; }
};
struct E18Vt {
    void DoInsert(E18* pos, const E18* v);   // 0074c020
};
struct Vec18 {
    E18* begin;   // +0x00
    E18* end;     // +0x04
    E18* cap;     // +0x08
    void push_back(const E18* v);
};

void Vec18::push_back(const E18* v)
{
    E18* e = end;
    if (e < cap) {
        end = e + 1;
        if (e)
            *e = *v;
    } else {
        ((E18Vt*)this)->DoInsert(e, v);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0074C260  quick_sort_impl<cDrawModelInfo*> (partial)
// ---------------------------------------------------------------------------
void quicksort_c260(void* a, void* b, int d, void* cmp) { (void)a; (void)b; (void)d; (void)cmp; }

// ---------------------------------------------------------------------------
// @ 0x0074C370  quick_sort_impl<cDrawModelInfo*,int,cAlphaSortLessComparator> (partial)
// ---------------------------------------------------------------------------
void quicksort_c370(void* a, void* b, int d, void* cmp) { (void)a; (void)b; (void)d; (void)cmp; }

// ---------------------------------------------------------------------------
// @ 0x0074C580  eastl::get_partition<cOccluder*> (partial)
// ---------------------------------------------------------------------------
void get_partition_c580(void* a, void* b, void* c, void* d, void* e) { (void)a; (void)b; (void)c; (void)d; (void)e; }

// ---------------------------------------------------------------------------
// @ 0x0074C670  SP::cModelWorld::ModelIsResidentInMemory (partial)
// ---------------------------------------------------------------------------
void model_resident_c670(void* self, void* model) { (void)self; (void)model; }

// ---------------------------------------------------------------------------
// @ 0x0074C910  SP::cModelWorld::ScheduleForLoad (partial)
// ---------------------------------------------------------------------------
void schedule_load_c910(void* self, void* model) { (void)self; (void)model; }

// ---------------------------------------------------------------------------
// @ 0x0074CAD0  cModelWorld helper (partial)
// ---------------------------------------------------------------------------
void helper_cad0(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x0074CE20  cModelWorld helper (partial)
// ---------------------------------------------------------------------------
void helper_ce20(void* self, void* a) { (void)self; (void)a; }

// ---------------------------------------------------------------------------
// @ 0x0074D190  eastl::quick_sort_impl<cOccluder*> (partial)
// ---------------------------------------------------------------------------
void quicksort_d190(void* a, void* b, int d, void* cmp) { (void)a; (void)b; (void)d; (void)cmp; }

// ---------------------------------------------------------------------------
// @ 0x0074D2C0  SP::cModelWorld::HandleMessage (partial)
// ---------------------------------------------------------------------------
bool handle_message_d2c0(void* sender, int* msg) { (void)sender; (void)msg; return false; }
