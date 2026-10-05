// Slice s0074e2b0: Editor/UI resource helpers (~0x0074e2b0-0x0074f1a0).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"

extern "C" void __cdecl FUN_006ec4a0(int* pos, const int* v);   // grow path

// ---------------------------------------------------------------------------
// @ 0x0074F1A0  add-unique to vector<int> (begin +0x4c)
// ---------------------------------------------------------------------------
struct IntVec { int* begin; int* end; int* cap; };

struct VecIntAdd {
    char pad0[0x4c];
    IntVec v;     // +0x4c
    bool add_unique(int x);
};

bool VecIntAdd::add_unique(int x)
{
    int n = (int)((char*)v.end - (char*)v.begin) >> 2;
    if (n > 0) {
        int i = 0;
        int* p = v.begin;
        do {
            if (*p == x)
                return false;
            ++i;
            ++p;
        } while (i < n);
    }
    if (v.end < v.cap) {
        int* e = v.end;
        v.end = e + 1;
        if (e)
            *e = x;
    } else {
        FUN_006ec4a0(v.end, &x);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0074F010  Editor resource destructor   (partial)
// ---------------------------------------------------------------------------
void dtor_f010(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x0074F0C0  rbtree clear + release   (partial)
// ---------------------------------------------------------------------------
bool clear_f0c0(void* self) { (void)self; return true; }

// ---------------------------------------------------------------------------
// @ 0x0074F130  rbtree find + erase   (partial)
// ---------------------------------------------------------------------------
void erase_f130(void* self, int key) { (void)self; (void)key; }

// ---------------------------------------------------------------------------
// @ 0x0074E2B0  UI helper   (partial: 2227B)
// ---------------------------------------------------------------------------
void helper_e2b0(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x0074EB70  helper   (partial)
// ---------------------------------------------------------------------------
void helper_eb70(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x0074ED00  SP::cModelWorld::FindModelsInSphere (partial)
// ---------------------------------------------------------------------------
void find_sphere_ed00(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x0074EE80  SP::cModelWorld::FindModelsInBox (partial)
// ---------------------------------------------------------------------------
void find_box_ee80(void* self) { (void)self; }
