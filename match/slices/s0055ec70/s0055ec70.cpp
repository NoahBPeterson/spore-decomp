// Slice s0055ec70: SP::cSPObjectTemplateDB save/restore of asset timestamps, group records
// and the PaintSystem block. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "../s0055ce80/s0055ce80.h"

extern "C" void EASTL_allocator_deallocate(void* p);
typedef void (__thiscall *Vfn8)(void*, void*, void**, int, int, int, int, int);
typedef void (__thiscall *Vfn2)(void*, int);
namespace EA { namespace XHTML { namespace DOM { struct Node { static int Type(void* p); }; } } }
unsigned DateTime_Set(int a);

namespace SP {

// Helpers (call targets are relocated, so signatures only fix the stack shape).
void FUN_00563e10(void* self);
void FUN_00561850(int index);
void FUN_00561970(int index);
void FUN_005631e0(void* self, void* out);
void* FUN_00566c50(void* node);
void* FUN_00564f50(void* it);
void* FUN_00564ea0(void* p);
int  FUN_00564f90(void* self);
void FUN_00555980(void* out, void* key);
void FUN_0048c720(void* it);
void FUN_00422c50(void* node);
void FUN_00564fb0(void* self);
void FUN_006926b0(void* obj);
void FUN_006913c0(int type);
void* FUN_00554020(void* out, void* val);
void FUN_00566d20(void* out, void* val, char flag);
void RBTreeErase(void* node, void* anchor);

// @ 0x0055ec70  (large PaintSystem repaint driver)
unsigned char FUN_0055ec70(void* this_, char a, char b) {
    (void)this_; (void)a; (void)b;
    return 0;
}

// @ 0x0055f7a0
unsigned char FUN_0055f7a0(void* this_) {
    if (*(int*)((char*)this_ + 0x5c) == 0) {
        FUN_00563e10(this_);
        *(unsigned char*)((char*)this_ + 0x40) = 1;
        return 1;
    }
    FUN_00566c50(*(void**)((char*)this_ + 0x50));
    void* key = FUN_00564f50(*(void**)((char*)this_ + 0x50));
    void* local_c = 0;
    void* local_8 = 0;
    void* mgr = EA::ResourceMan::GetManager();
    if (local_8) {
        void* p = local_8; local_8 = 0;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    if (local_c) {
        void* p = local_c; local_c = 0;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    ((Vfn8)(*(void***)mgr)[0x10 / 4])(mgr, key, &local_c, 0, 0, 0, 0, 0);
    void* node = FUN_00564ea0(local_c);
    if (node)
        FUN_006913c0(EA::XHTML::DOM::Node::Type(node));
    unsigned char r = (unsigned char)FUN_00564f90(this_);
    if (local_8) {
        void* p = local_8;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    if (local_c) {
        void* p = local_c;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    return r;
}

// @ 0x0055f8e0
unsigned char FUN_0055f8e0(void* this_) {
    if (*(int*)((char*)this_ + 0x5c) == 0) {
        FUN_00563e10(this_);
        *(unsigned char*)((char*)this_ + 0x40) = 1;
        return 1;
    }
    void* p = (void*)0x1;
    (void)p;
    FUN_00566c50(*(void**)((char*)this_ + 0x50));
    int value = (int)FUN_00564f50(*(void**)((char*)this_ + 0x50));
    ((Vfn2)(*(void***)this_)[0x70 / 4])(this_, value);
    FUN_00566c50(*(void**)((char*)this_ + 0x50));
    *(int*)((char*)this_ + 0x5c) -= 1;
    void* node = (void*)value;
    FUN_00422c50(&node);
    void* anchor = (char*)this_ + 0x48;
    RBTreeErase(node, anchor);
    EASTL_allocator_deallocate(node);
    return 1;
}

// @ 0x0055f9e0
void FUN_0055f9e0(void* this_) {
    if (*(char*)((char*)this_ + 0x40) == 0) {
        void* obj = *(void**)((char*)this_ + 0x44);
        if (obj != 0)
            FUN_006926b0(obj);
    }
}

// @ 0x0055fa20
unsigned char FUN_0055fa20(void* this_, void* key, char flag) {
    int index = 0;
    FUN_005631e0(this_, &index);
    ((int*)this_)[0] = 0;   // placeholder to keep `index` live
    if (index == -1)
        return 0;
    if (flag != 0) {
        char tmp[8];
        void* p = FUN_00554020(tmp, &index);
        if (*(char*)((char*)p + 4) != 0) {
            FUN_00561970(index);
            *(unsigned char*)((char*)this_ + 0x1d0) = 1;
        }
        unsigned a = DateTime_Set(1);
        (void)a;
        int base = index * 0x50 + *(int*)((char*)this_ + 0x14);
        (void)base;
    } else {
        void* itpair[2];
        FUN_00555980(itpair, &index);
        void* it = (itpair[0] != itpair[1]) ? itpair[0] : *(void**)((char*)this_ + 0x68);
        if (it != *(void**)((char*)this_ + 0x68)) {
            FUN_0048c720(it);
            FUN_00561850(index);
        }
    }
    return 1;
}

// @ 0x0055fb30
unsigned char FUN_0055fb30(void* this_, void* key) {
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index != -1) {
        void* itpair[2];
        FUN_00555980(itpair, &index);
        void* it = (itpair[0] != itpair[1]) ? itpair[0] : *(void**)((char*)this_ + 0x68);
        if (it != *(void**)((char*)this_ + 0x68))
            return 1;
    }
    return 0;
}

// @ 0x0055fbb0
unsigned char FUN_0055fbb0(void* this_, void* key) {
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index == -1)
        return 0;
    unsigned a = DateTime_Set(1);
    (void)a;
    int base = index * 0x50 + *(int*)((char*)this_ + 0x14);
    (void)base;
    return 1;
}

}
