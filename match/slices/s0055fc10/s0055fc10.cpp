// Slice s0055fc10: SP::cSPObjectTemplateDB key/asset queries and matching helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

namespace SP {

void FUN_00540470(void* p);
void FUN_00547240(void* key);
void FUN_00565040(void* out, void* val);
void FUN_00564960(void* out, void* val);
void FUN_005631e0(void* self, void* out);
void FUN_00562280(void* self, void* c);
void FUN_0041e4d0(int n);
void FUN_00564fd0(void* p);
void FUN_004769b0(void* a, void* b);
void FUN_00561cc0(void* self);
void FUN_00565040b();

// @ 0x0055fc10
void FUN_0055fc10(void* this_, unsigned maxCount, void* pOut, int param4) {
    char tmp[64];
    FUN_00540470(&tmp);
    FUN_00547240(this_);
    unsigned count = 0;
    void* mgr = EA::ResourceMan::GetManager();
    char* begin = *(char**)((char*)this_ + 0x14);
    char* end = *(char**)((char*)this_ + 0x18);
    char* it = begin;
    for (;;) {
        if (it == end) {
            // copy(pOut->begin, pOut->end)
            uint32_t* v = (uint32_t*)pOut;
            FUN_0041e4d0(0);
            (void)v;
            FUN_00564fd0(&tmp);
            return;
        }
        char* entry = it;
        bool take;
        if (param4 == 0)
            take = true;
        else
            take = ((bool(__thiscall*)(void*, char*, int, int))(*(void***)mgr)[0x30 / 4])(mgr, it, 0, param4) != 0;
        if (take) {
            if (count < maxCount) {
                int idx = (int)(it - begin) / 0x50;
                struct { int a, b, c; } rec;
                rec.a = *(int*)(entry + 0x48);
                rec.b = *(int*)(entry + 0x4c);
                rec.c = idx;
                char out[16];
                FUN_00565040(out, &rec);
                count++;
            }
        }
        it += 0x50;
    }
}

// @ 0x0055fe60
void FUN_0055fe60(void* this_, unsigned key, unsigned value) {
    char tmp[8];
    unsigned two[2];
    two[0] = key;
    two[1] = 0;
    FUN_00564960(tmp, two);
    eastl::vector_map<uint32_t, uint32_t>* map =
        (eastl::vector_map<uint32_t, uint32_t>*)((char*)this_ + 0xc4);
    map->operator[](key) = value;
}

// @ 0x0055fed0
void FUN_0055fed0(void* this_) {
    FUN_004769b0(*(void**)((char*)this_ + 0x64), *(void**)((char*)this_ + 0x68));
    FUN_00561cc0(this_);
}

// @ 0x0055ff10  (large matching driver)
bool FUN_0055ff10(void* this_, void* key, void* out) {
    (void)this_; (void)key; (void)out;
    return false;
}

// @ 0x00560470  (large action driver)
bool FUN_00560470(void* this_, void* key, int flags) {
    (void)this_; (void)key; (void)flags;
    return false;
}

// @ 0x00560880
bool FUN_00560880(void* this_, void* key, unsigned* out) {
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index == -1)
        return false;
    char* asset = (char*)(index * 0x50 + *(int*)((char*)this_ + 0x14));
    *out = *(unsigned*)(asset + 0xc);
    return true;
}

// @ 0x005608d0
bool FUN_005608d0(void* this_, uint32_t* key, void* c) {
    FUN_004769b0(*(void**)((char*)this_ + 0x144), *(void**)((char*)this_ + 0x148));
    FUN_00562280((char*)this_ + 0x144, c);
    uint32_t* it = *(uint32_t**)((char*)this_ + 0x144);
    uint32_t* end = *(uint32_t**)((char*)this_ + 0x148);
    for (; it != end; ++it) {
        uint32_t* asset = (uint32_t*)(*it * 0x50 + *(int*)((char*)this_ + 0x14));
        if (asset[0] == key[0] && asset[1] == key[1] && asset[2] == key[2])
            return true;
    }
    return false;
}

}
