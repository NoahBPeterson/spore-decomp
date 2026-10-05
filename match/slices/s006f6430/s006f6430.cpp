// Slice s006f6430: cFilterChain helpers (camera-texture registration), small vector/hashtable
// helpers and state wrappers.
// Region 0x6f6430-0x6f7430. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---- external callees -------------------------------------------------------------------
void  __cdecl FUN_0077ca20(int a, float b, float c, float d, float e);
void  __cdecl FUN_00892970();
void  __cdecl FUN_006f4ff0(void* out, void* a, void* b);
void  __cdecl FUN_006f5170(void* b, void* e);
struct cHashtable {
    void FreeNodes(void* b, void* e);
};
void  __cdecl FUN_006ec390(void* p, void* v);
void  __cdecl FUN_00426730(void* p, void* v);
void  __cdecl FUN_006ec4a0(void* p, void* v);
void  __cdecl operator_delete_(void* p);
void  __cdecl EASTL_allocator_deallocate(void* p);
void* __cdecl operator_new(unsigned sz, const char* name, int a, int b, int c, int d);
void* __cdecl FUN_0067dda0();
void* __cdecl FUN_0067dd40();
void* __cdecl FUN_0067dd50();
void* __cdecl SP_MessageServer();
void* __cdecl FUN_007c3f70();
void  __cdecl cSPEditorPhysicsWorld_Init(void* p, int a);
void  __cdecl FUN_00426950();

void __fastcall FUN_006f54a0_(void* self, int p2, int p3, int p4, int p5,
                               int p6, int p7, int p8, int p9, int p10);

// ---- small vector/hashtable helpers ------------------------------------------------------
struct cVecU16 {
    unsigned short* begin;   // +0
    unsigned short* end;     // +4
    unsigned short* cap;     // +8
    void Insert(unsigned short* pos, const unsigned short& val);   // 0x6f5bc0
    void push_back(const unsigned short& v);
};

// @ 0x006f66a0
void cVecU16::push_back(const unsigned short& v) {
    unsigned short* e = end;
    if (e < cap) {
        end = e + 1;
        if (e != 0) { *e = v; return; }
    } else {
        Insert(e, v);
    }
}

// @ 0x006f66d0
void __fastcall FUN_006f66d0(int* self) {
    void* p;
    p = (void*)self[0x19]; if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[0x14]; if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[0xf];  if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[10];   if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = (void*)self[5];    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    ((cHashtable*)self)->FreeNodes((void*)self[0], (void*)self[1]);
    p = (void*)self[0];    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
}

// @ 0x006f65d0  (hashtable find-or-insert; see nonmatching.txt)
int __fastcall FUN_006f65d0(int self, unsigned short* key) {
    int local_14[5];
    FUN_00892970();
    (void)self; (void)key; (void)local_14;
    return 0;
}

// ---- cFilterChain pieces: skeletons (see partial.txt) ------------------------------------
// @ 0x006f6430
void FUN_006f6430(void* self, void* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)self; (void)ctx; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
}
// @ 0x006f6500
void FUN_006f6500(void* self, void* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)self; (void)ctx; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
}
// @ 0x006f6770
void* FUN_006f6770(void* self, void* other) { (void)other; return self; }
// @ 0x006f6830
unsigned SP_cFilterChain_AddCameraTexture(void* self, unsigned short a, unsigned short b) {
    (void)self; (void)a; (void)b; return 0;
}
// @ 0x006f6910
void __fastcall FUN_006f6910(int self) { (void)self; }
// @ 0x006f69c0
int __fastcall FUN_006f69c0(int self) { (void)self; return 1; }
// @ 0x006f6c30
void FUN_006f6c30(void* self, void* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)self; (void)ctx; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
}
// @ 0x006f6f40
void FUN_006f6f40(void* self) { (void)self; }
// @ 0x006f71f0
void FUN_006f71f0(void* self) { (void)self; }
