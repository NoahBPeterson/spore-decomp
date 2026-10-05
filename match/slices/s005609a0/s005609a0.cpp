// Slice s005609a0: SP::cSPObjectTemplateDB asset registration, OTDB jobs and the
// cEditorResource-backed resource wrapper emitted in this module.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

namespace SP {

void FUN_0048c720(void* p);
void FUN_00564820(void* p);
void FUN_00571680(void* p);
void FUN_00571640(void* p);
void FUN_00429360(void* p);
void FUN_005688f0(void* a, void* b, void* c, void* d);
void FUN_005643e0(void* it);
bool FUN_0055c6f0(void* a, void* b, void* c);
void FUN_0068f9b0(void* p);
void FUN_00564470(void* p);
void FUN_005156b0(void* p);
void FUN_00564960(void* out, void* val);
void FUN_0041d940();
void* FUN_0068f4d0();
void FUN_006909b0();
void FUN_005641a0(void* p);
void FUN_005631e0(void* self, void* out);
void FUN_00562280(void* self, void* c);
void FUN_004769b0(void* a, void* b);
void FUN_00555980(void* out, void* key);
void FUN_00561970(int index);
void FUN_00565040(void* out, void* val);
void* OPERATOR_NEW_OTDB(int size, const char* name, int a, int b, int c, int d);
void* FUN_005688f0_();

// @ 0x005609a0  (large OTDB driver)
bool FUN_005609a0(void* this_, void* a, char b) {
    (void)this_; (void)a; (void)b;
    return false;
}

// @ 0x00560c30
int FUN_00560c30(void* this_, void* pKey) {
    int index = -1;
    if (!((DBSub*)((char*)this_ + 0x28))->GetResType()) {
        index = **(int**)((char*)this_ + 0x28);
        FUN_0048c720(*(void**)((char*)this_ + 0x28));
    } else {
        index = (int)((*(int*)((char*)this_ + 0x18) - *(int*)((char*)this_ + 0x14)) / 0x50);
        FUN_00564820((char*)this_ + 0x14);
    }
    char* asset = (char*)(index * 0x50 + *(int*)((char*)this_ + 0x14));
    *(uint32_t*)(asset + 0) = ((uint32_t*)pKey)[0];
    *(uint32_t*)(asset + 4) = ((uint32_t*)pKey)[1];
    *(uint32_t*)(asset + 8) = ((uint32_t*)pKey)[2];
    *(uint32_t*)(asset + 0xc) = 0xffffffff;
    FUN_00571680(asset + 0x10);
    *(uint32_t*)(asset + 0x48) = 0xffffffff;
    *(uint32_t*)(asset + 0x4c) = 0xffffffff;
    return index;
}

// @ 0x00560d20
bool FUN_00560d20(void* this_, void* other) {
    if (*(uint32_t*)this_ != *(uint32_t*)other)
        return false;
    if (*(uint32_t*)((char*)this_ + 8) != *(uint32_t*)((char*)other + 8))
        return false;
    return true;
}

// @ 0x00560d60
bool FUN_00560d60(void* this_, ...) {
    return false;
}

// @ 0x00560f20
void FUN_00560f20(void* param1, void* param2, unsigned char param3) {
    void* job = (void*)FUN_0068f4d0();
    (void)job; (void)param1; (void)param2; (void)param3;
}

namespace Editor { struct cEditorResource { }; }

// @ 0x00561090
void* FUN_00561090_(void* this_) {
    *(void**)this_ = (void*)0x13eb938;
    *(void**)this_ = (void*)0x13f1ab0;
    *(void**)((char*)this_ + 4) = (void*)0x140b5a0;
    *(void**)((char*)this_ + 8) = (void*)0x13ef094;
    *(void**)((char*)this_ + 0xc) = 0;
    *(void**)this_ = (void*)0x13f4b00;
    *(void**)((char*)this_ + 4) = (void*)0x13f4afc;
    *(void**)((char*)this_ + 8) = (void*)0x13f4af8;
    *(void**)((char*)this_ + 0x10) = 0;
    *(void**)((char*)this_ + 0x14) = 0;
    *(void**)((char*)this_ + 0x18) = 0;
    *(void**)((char*)this_ + 0x1c) = 0;
    *(void**)((char*)this_ + 0x20) = 0;
    *(void**)((char*)this_ + 0x24) = 0;
    return this_;
}

// @ 0x00561150  (small virtual returning false)
struct CEditorResourceThunk {
    virtual int f(void* p);
};
int CEditorResourceThunk::f(void* p) {
    (void)p;
    return 0;
}

// @ 0x005611b0
void FUN_005611b0(void* this_) {
    *(void**)this_ = (void*)0x13f4b00;
    *(void**)((char*)this_ + 4) = (void*)0x13f4afc;
    *(void**)((char*)this_ + 8) = (void*)0x13f4af8;
    char* v = (char*)this_ + 0x1c;
    for (char* it = *(char**)v; it < *(char**)(v + 4); it += 0xc) {
    }
    FUN_005156b0(v);
    *(void**)((char*)this_ + 8) = (void*)0x13ef094;
    *(void**)this_ = (void*)0x13eb938;
}

// @ 0x00561220
bool FUN_00561220(void* this_, void* pObj) {
    (void)this_; (void)pObj;
    return false;
}

// @ 0x00561340  (large)
bool FUN_00561340(void* this_, void* a, void* b) {
    (void)this_; (void)a; (void)b;
    return false;
}

// @ 0x00561850
void FUN_00561850(int index) {
    (void)index;
}

}
