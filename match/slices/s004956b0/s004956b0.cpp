// Slice s004956b0 (batch w1g0, slice 92), 0x004956b0..0x004962f1.
// /Od editor-region code: mostly hkArray/hkThreadMemory-style helpers plus a
// vector "save transform" routine. 004956b0 is a large skeleton.

#include "types.h"

struct Vector3 {
    float x, y, z;
};

// ---- memory manager stubs ---------------------------------------------------
struct MemMgr {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void Deallocate(void* p, int a, int b);
};

extern MemMgr* g_mem;                         // 0x016e4178

struct HkThreadMemory {
    void DeallocateChunk(void* p, int size, int cls);
};

extern void* g_tls_slot;                      // 0x016e4174
extern void* __stdcall TlsGetValue(uint32_t index);

extern void* g_vtbl_13ef554;
extern void* g_vtbl_13ef534;
extern void* g_vtbl_13ef55c;

// @ 0x00495f90
struct D95 {
    void* vptr;
    void* Del(unsigned flags);
};
void* D95::Del(unsigned flags) {
    this->vptr = &g_vtbl_13ef554;
    this->vptr = &g_vtbl_13ef534;
    if (flags & 1) {
        MemMgr* z = g_mem;
        z->Deallocate(this, 8, 0x1c);
    }
    return this;
}

// @ 0x004960d0
struct D960 {
    void* vptr;
    char pad[0xc];
    void* data;                               // 0x10
    char pad2[4];
    int cap;                                  // 0x18
    void Dtor();
    void* Del(unsigned flags);
};

void D960::Dtor() {
    this->vptr = &g_vtbl_13ef55c;
    int c = *(int*)((char*)this + 0x18);
    if ((c & 0x80000000) == 0) {
        void* mem = TlsGetValue(*(uint32_t*)&g_tls_slot);
        ((HkThreadMemory*)mem)->DeallocateChunk(*(void**)((char*)this + 0x10),
                                                 (c & 0x3fffffff) * 0x30, 0x14);
    }
    this->vptr = &g_vtbl_13ef534;
}

// @ 0x00496090
void* D960::Del(unsigned flags) {
    this->Dtor();
    if (flags & 1) {
        MemMgr* z = g_mem;
        z->Deallocate(this, 8, 0x1c);
    }
    return this;
}

// @ 0x00495fe0
struct D95fe0 {
    void* vptr;
    char pad[0x200];
    void* Ctor();
};
void* D95fe0::Ctor() {
    // reconstructed skeleton: vtable stores + inplace-buffer init
    this->vptr = &g_vtbl_13ef55c;
    *(int*)((char*)this + 4) = 0x7f7fffee;
    void** buf = (void**)((char*)this + 0x10);
    buf[0] = (void*)((char*)this + 0x30);
    buf[1] = 0;
    buf[2] = (void*)0x80000008;
    for (int i = 8; i > 0; --i) {
    }
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 4) = 0x7f7fffee;
    return this;
}

// @ 0x00496140
struct D961 {
    char pad[0x4c];
    void** data;                              // 0x4c
    int count;                                // 0x50
    int* Find(int* out, int key);
};
int* D961::Find(int* out, int key) {
    int i = 0;
    while (true) {
        if (this->count <= i) {
            out[0] = 0;
            out[1] = 0;
            return out;
        }
        if (*(int*)((char*)this->data + i * 0x10) == key)
            break;
        ++i;
    }
    out[0] = *(int*)((char*)this->data + i * 0x10 + 8);
    out[1] = *(int*)((char*)this->data + i * 0x10 + 0xc);
    return out;
}

// @ 0x004961d0
struct Vec {
    void** begin;
    void** end;
};
void FUN_004961d0(char* save, Vec* vec) {
    if (save != 0) {
        *(Vector3*)(save + 0x54) = *(Vector3*)(save + 0x48);
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0x84))[k] = ((float*)(save + 0x60))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0xcc))[k] = ((float*)(save + 0xa8))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0x114))[k] = ((float*)(save + 0xf0))[k];
    }
    int n = (int)(vec->end - vec->begin);
    for (int i = 0; i < n; ++i) {
        char* b = (char*)vec->begin[i];
        *(Vector3*)(b + 0x54) = *(Vector3*)(b + 0x48);
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0x84))[k] = ((float*)(b + 0x60))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0xcc))[k] = ((float*)(b + 0xa8))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0x114))[k] = ((float*)(b + 0xf0))[k];
    }
}

// @ 0x004956b0
void FUN_004956b0(void* p, void* a, void* b) {
    (void)p;
    (void)a;
    (void)b;
}
