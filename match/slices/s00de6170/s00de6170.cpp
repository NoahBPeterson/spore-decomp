// Slice s00de6170 -- 0x0dex region (intrusive list / container helpers).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (default /GS on).

// Local declarations used to reproduce the thiscall/cdecl call shapes of the
// eastl red-black-tree helpers this translation unit calls into.
class CFind70 {
public:
    void* find(void* out, void* key);
};
class CFind1c {
public:
    void* find(void* out, void* key);
};
class CInsert {
public:
    void* insert(void* out, void* key, unsigned int v);
};
void* __cdecl RBTreeIncrement(void* node);
void __cdecl RBTreeErase(void* a, void* b);
void __cdecl freeNode(void* p);

// @ 0x00de67b0 -- FUN_00de67b0 (__fastcall, this in ecx)
// Initialises the five intrusive list headers embedded in the object: three
// zero dwords + a flag byte + a trailing dword per list, plus the self-linked
// head pointers at +0x04, +0x20, +0x3c, +0x58 and +0x74.
int* __fastcall FUN_00de67b0(int param_1) {
    int zero = 0;
    int* p = (int*)param_1;
    p[2] = zero;
    p[3] = zero;
    p[4] = zero;
    p[3] = zero;
    *(char*)(param_1 + 0x10) = (char)zero;
    p[5] = zero;
    int* iVar1 = (int*)(param_1 + 4);
    *iVar1 = (int)iVar1;
    p[2] = (int)iVar1;
    p[9] = zero;
    p[10] = zero;
    p[0xb] = zero;
    p[10] = zero;
    *(char*)(param_1 + 0x2c) = (char)zero;
    p[0xc] = zero;
    iVar1 = (int*)(param_1 + 0x20);
    *iVar1 = (int)iVar1;
    p[9] = (int)iVar1;
    p[0x10] = zero;
    p[0x11] = zero;
    p[0x12] = zero;
    p[0x11] = zero;
    *(char*)(param_1 + 0x48) = (char)zero;
    p[0x13] = zero;
    iVar1 = (int*)(param_1 + 0x3c);
    *iVar1 = (int)iVar1;
    p[0x10] = (int)iVar1;
    p[0x17] = zero;
    p[0x18] = zero;
    p[0x19] = zero;
    iVar1 = (int*)(param_1 + 0x58);
    *iVar1 = (int)iVar1;
    p[0x17] = (int)iVar1;
    p[0x18] = zero;
    *(char*)(param_1 + 0x64) = (char)zero;
    p[0x1a] = zero;
    iVar1 = (int*)(param_1 + 0x74);
    iVar1[1] = zero;
    iVar1[2] = zero;
    iVar1[3] = zero;
    *iVar1 = (int)iVar1;
    p[0x1e] = (int)iVar1;
    p[0x1f] = zero;
    *(char*)(param_1 + 0x80) = (char)zero;
    p[0x21] = zero;
    return p;
}

// @ 0x00de6e80 -- FUN_00de6e80 (__thiscall: this in ecx, one stack argument)
// Removes the entry for `param_2` from the resource-manager rbtree at +0x70
// (inserting a fresh record if the key is unknown) and then unlinks the same
// key from the feedback-event rbtree at +0x1c.
struct S00de6e80 {
    void FUN_00de6e80(int param_2);
};

void S00de6e80::FUN_00de6e80(int param_2) {
    void* out[2];
    struct Key {
        unsigned int id;
        unsigned int h;
        unsigned int f;
    } key;
    key.id = (unsigned int)param_2;
    key.h = 0x011989b7u;
    key.f = 0x4084a100u;
    int* p = (int*)((CFind70*)((char*)this + 0x70))->find(out, &key);
    if (*p != (int)((char*)this + 0x74)) {
        *(unsigned char*)&out[0] = 0;
        ((CInsert*)this)->insert(out, &param_2, (unsigned int)(unsigned long)out[0]);
    }
    CFind1c* t = (CFind1c*)((char*)this + 0x1c);
    t->find(out, &param_2);
    unsigned int node = (unsigned int)(unsigned long)out[0];
    if (node != (unsigned int)(unsigned long)((char*)t + 4)) {
        *(int*)((char*)t + 0x14) -= 1;
        RBTreeIncrement((void*)(unsigned long)node);
        RBTreeErase((void*)(unsigned long)node, (void*)((char*)t + 4));
        freeNode((void*)(unsigned long)node);
    }
}