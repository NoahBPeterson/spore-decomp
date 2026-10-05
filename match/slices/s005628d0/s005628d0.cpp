// Slice s005628d0: SP::cSPObjectTemplateDB matching/priority-constraint driver methods.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

namespace SP {

void FUN_004769b0(void* a, void* b);
void FUN_00562280(void* self, void* c);
void FUN_005625a0(void* self, int flag);
bool FUN_00562510(void* self, void* out);
void FUN_00565380(void* out, void* a, void* b, void* c, void* d, void* e, void* f);
void FUN_00565410(void* out, void* a, void* b, void* c, void* d, void* e, void* f);
void FUN_00565df0(void* self);
void FUN_00565500(void* self, void* first, int count);
void FUN_00565560(void* self);
void FUN_00554020(void* out, void* val);
void FUN_0055c2e0(void* a, void* b);

// @ 0x005628d0  (large reassignment driver)
void FUN_005628d0(void* this_, void* pList) {
    (void)this_; (void)pList;
}

// @ 0x00562b80
void FUN_00562b80(void* this_, void* out, void* pRange) {
    FUN_004769b0(*(void**)((char*)this_ + 0x12c), *(void**)((char*)this_ + 0x130));
    int* r = (int*)pRange;
    FUN_00565500((char*)this_ + 0x12c, (void*)*r, (r[1] - *r) / 0x24);
    FUN_00562510((char*)this_ + 0x12c, out);
}

// @ 0x00562c00
bool FUN_00562c00(void* this_, void* out) {
    (void)this_; (void)out;
    return false;
}

// @ 0x00562ca0
bool FUN_00562ca0(void* this_, void* a, void* b, void* pRange) {
    FUN_004769b0(*(void**)((char*)this_ + 0x12c), *(void**)((char*)this_ + 0x130));
    int* r = (int*)pRange;
    FUN_00565500((char*)this_ + 0x12c, (void*)*r, (r[1] - *r) / 0x24);
    if (!FUN_00562510((char*)this_ + 0x12c, a))
        return false;
    FUN_0055c2e0(a, b);
    return true;
}

// @ 0x00562d50
bool FUN_00562d50(void* this_, void* a) {
    (void)this_; (void)a;
    return false;
}

// @ 0x00562de0
bool FUN_00562de0(void* this_, void* a) {
    (void)this_; (void)a;
    return false;
}

// @ 0x00562e90
bool FUN_00562e90(void* this_, void* a) {
    (void)this_; (void)a;
    return false;
}

// @ 0x00562f50
bool FUN_00562f50(void* this_, void* a, void* b) {
    (void)this_; (void)a; (void)b;
    return false;
}

// @ 0x00563090
bool FUN_00563090(void* this_, void* a, void* b) {
    (void)this_; (void)a; (void)b;
    return false;
}

// @ 0x005631e0  (asset lookup used by the timestamp helpers)
int FUN_005631e0(void* this_, void* pOut) {
    int index = -1;
    for (char* it = *(char**)((char*)this_ + 0x14); it != *(char**)((char*)this_ + 0x18); it += 0x50) {
        if (*(uint32_t*)it == *(uint32_t*)pOut) {
            index = (int)(it - *(char**)((char*)this_ + 0x14)) / 0x50;
            break;
        }
    }
    (void)index;
    return -1;
}

// @ 0x005632d0
bool FUN_005632d0(void* this_, void* a) {
    (void)this_; (void)a;
    return false;
}

// @ 0x00563370
bool FUN_00563370(void* this_, void* a, void* b) {
    (void)this_; (void)a; (void)b;
    return false;
}

}
