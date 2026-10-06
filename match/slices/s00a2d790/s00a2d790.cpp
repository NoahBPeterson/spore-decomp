// Slice s00a2d790: EA::Audio::System and its EASTL containers.
// Retail layout offsets taken from the disassembly. The 2008 PDB gives real
// names for several members (mPrimitives, ...); unknown gaps are byte pads.
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

struct XF;           // generic stub for external __thiscall callees
struct AudioSystem;

// --- generic thiscall callees: ecx = object, rest on stack ---
struct XF {
    void* hashtable_find(void* key, void* out);      // 0x645ed0
    void* rbtree_find(void* out, void* key);         // 0xe5c780
    void* FUN_00a2a150(void* out);
    void* FUN_00a2a510(void* out);
    void  FUN_00a276e0(void* a, void* b);
    void  FUN_00a2b230(void* a, void* b, void* c, void* d);
    void  FUN_00a26a20(void* a, void* b, void* c);
    void  FUN_00a26ce0(void* a, void* b, void* c);
    void  FUN_00a26fa0(void* a);
    void  FUN_00a2ac20(void* a, void* b);
    void  FUN_00a2af30(void* a, void* b);
    void  FUN_00a22220(uint n);
    void  FUN_00a2bb30();
    void  FUN_00a21390();
    void  AutoRef_op(uint* p);
    void* DoInsertValue(void* a, void* b, void* c);
    int   DoFreeNodes(void* a, void* b);
    void  DoNukeSubtree(void* a);
    void  StopwatchCtor(void* a, void* b);
    void  Noop();
};

// --- external cdecl/free callees ---
void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void* __cdecl FUN_00a17090(uint size);
void* __cdecl FUN_00a17100(void* p);
uint  __cdecl FUN_00921340(uint n);
uint  __cdecl FUN_009213c0(uint n);
void* __cdecl FUN_00a248a0(void* a);
void  __cdecl FUN_00921340_dummy();
void* __cdecl eastl_copy(void*, void*, void*);
extern "C" void* DAT_016e61a8;
extern "C" void  FUN_0112c600();
extern "C" void  FUN_0112c620();
extern "C" int   FUN_00a26fa0_c;

struct AudioSystem {
    uchar pad[0x140000];

    // 00a2d790
    bool RegisterPrimitive(void* p);
    // 00a2d880
    void* FUN_00a2d880(uint key, void* out);
    // 00a2d940 : ctor
    void* FUN_00a2d940(void* arg);
    // 00a2d990
    int FUN_00a2d990(void* arg);
    // 00a2d9d0 : dtor
    void* FUN_00a2d9d0(uchar flags);
    // 00a2da30
    void FUN_00a2da30();
    // 00a2dc40
    void SetupPropertyAggregationRules();
    // 00a2de20
    bool DestroySubmixes();
    // 00a2dfe0
    void FUN_00a2dfe0(void* p);
    // 00a2e060
    uint& FUN_00a2e060(const uint& k);
    // 00a2e0e0
    int FUN_00a2e0e0(uint* p);
    // 00a2e1b0
    void* FUN_00a2e1b0(void* out, void* node, void* parent);
    // 00a2e260
    void FUN_00a2e260(void* p);
    // 00a2e2f0
    AudioSystem* FUN_00a2e2f0(void* p);
    // 00a2e420
    void* FUN_00a2e420(void* p);
    // 00a2e4c0
    void* FUN_00a2e4c0(void* p);
};

// helper: virtual call at vtable byte offset
static void* vc(void* obj, int off) {
    return ((void**)*(void**)obj)[off / 4];
}

// @ 0x00a2d790
bool AudioSystem::RegisterPrimitive(void* p) {
    if (!p) return false;
    typedef char (__thiscall *F0)(void*);
    if (!((F0)vc(p, 0x10))(p)) return false;
    uint id = ((uint (__thiscall*)(void*))vc(p, 0x18))(p);
    uint key = id;
    void* it = 0;
    ((XF*)((uchar*)this + 0x13f4))->hashtable_find(&key, &it);
    if (*(uint*)it != *(uint*)(*(uint*)((uchar*)this + 0x13f8) +
                              *(int*)((uchar*)this + 0x13fc) * 4))
        return false;
    void* elem = ((XF*)((uchar*)this + 0x13f4))->FUN_00a2a150(&key);
    ((XF*)elem)->AutoRef_op(&key);
    ((void (__thiscall*)(void*, uint))vc(this, 0x38))(this, 0x399197f);
    ((void (__thiscall*)(void*, uint, uint))vc(this, 0x40))(this, 0x3475385, id);
    ((void (__thiscall*)(void*))vc(this, 0x58))(this);
    ((void (__thiscall*)(void*, uint))vc(this, 0x38))(this, 0x3991984);
    ((void (__thiscall*)(void*, uint, uint))vc(this, 0x40))(this, 0x3475385, id);
    float f = ((float (__thiscall*)(void*))vc(p, 0x1c))(p);
    ((void (__thiscall*)(void*, uint, float))vc(this, 0x3c))(this, 0x34753aa, f);
    ((void (__thiscall*)(void*))vc(this, 0x58))(this);
    return true;
}

// @ 0x00a2d880
void* AudioSystem::FUN_00a2d880(uint key, void* out) {
    void* it;
    ((XF*)((uchar*)this + 0x23e4))->hashtable_find(&key, &it);
    if (*(uint*)it != *(uint*)(*(uint*)((uchar*)this + 0x23e8) +
                              *(int*)((uchar*)this + 0x23ec) * 4))
        return 0;
    void* node = FUN_00a17090(0x1c);
    if (node) node = FUN_00a17100(this);
    ((void (__thiscall*)(void*))vc(node, 0))(node);
    void* slot = ((XF*)((uchar*)this + 0x23e4))->FUN_00a2a510(out);
    *(void**)slot = node;
    return (void*)1;
}

// @ 0x00a2d940
void* AudioSystem::FUN_00a2d940(void* arg) {
    *(void**)this = (void*)0x1452cb0;
    ((XF*)((uchar*)this + 4))->FUN_00a26fa0(arg);
    return this;
}

// @ 0x00a2d990
int AudioSystem::FUN_00a2d990(void* arg) {
    if (*(int*)((uchar*)arg + 8) == 0x21407ee) {
        void* out;
        int* r = (int*)((XF*)((uchar*)this + 4))->rbtree_find(&out, (uchar*)arg + 4);
        if ((uchar*)this + 8 != (uchar*)*r)
            return 1;
    }
    return 0;
}

// @ 0x00a2d9d0
void* AudioSystem::FUN_00a2d9d0(uchar flags) {
    ((XF*)((uchar*)this + 4))->DoNukeSubtree(*(void**)((uchar*)this + 0x10));
    *(void**)this = (void*)0x13eb394;
    if (flags & 1) operator_delete(this);
    return this;
}

// @ 0x00a2da30  (PickRandomKey; EASTL hashtable + EH; approximated)
void AudioSystem::FUN_00a2da30() {
    // Body skipped: 525-byte EASTL hashtable iteration with EH cleanup.
    // Kept as a compiling approximation (see partial.txt).
    return;
}

// @ 0x00a2dc40  (SetupPropertyAggregationRules; EASTL + EH; approximated)
void AudioSystem::SetupPropertyAggregationRules() {
    return;
}

// @ 0x00a2de20  (DestroySubmixes)
bool AudioSystem::DestroySubmixes() {
    if (DAT_016e61a8) FUN_0112c600();
    uint* begin = *(uint**)((uchar*)this + 0x119ba4);
    uint* end = *(uint**)((uchar*)this + 0x119ba8);
    for (uint* it = begin; it != end; ++it) {
        void* o = (void*)*it;
        if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        ((XF*)o)->FUN_00a21390();
        ((void (__thiscall*)(void*, void*))vc(this, 0x170))(this, o);
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
    for (uint* it = begin; it != end; ++it) {
        void* o = (void*)*it;
        if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        ((XF*)o)->FUN_00a2bb30();
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
    // compact the vector
    uint* p = begin;
    for (; p != end; ++p) {
        if (*p) {
            void* o = (void*)*p;
            ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
    }
    uint count = (uint)(end - begin);
    *(uint**)((uchar*)this + 0x119ba8) = begin - count;
    if (DAT_016e61a8) FUN_0112c620();
    return true;
}

// @ 0x00a2dfe0
void AudioSystem::FUN_00a2dfe0(void* p) {
    uchar* vec = (uchar*)this;
    void** cur = *(void***)(vec + 4);
    if (cur < *(void***)(vec + 8)) {
        *(void***)(vec + 4) = cur + 1;
        if (cur) {
            void* o = *(void**)p;
            *cur = o;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
    } else {
        ((XF*)vec)->FUN_00a2ac20(cur, p);
    }
}

// @ 0x00a2e060  (eastl::map<unsigned long,unsigned long>::operator[])
uint& AudioSystem::FUN_00a2e060(const uint& k) {
    struct Node { Node* left; Node* right; Node* parent; int color; uint key; uint value; };
    Node* header = (Node*)((uchar*)this + 4);
    Node* node = header->parent;
    Node* cand = header;
    while (node) {
        if (node->key < k) node = node->left;
        else { cand = node; node = node->right; }
    }
    if (cand != header && k <= cand->key) return cand->value;
    // insert (approximation of rbtree DoInsertValue)
    Node* n = (Node*)operator_new(0x18, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/rbtree.h", 0x2d1);
    n->left = n->right = n->parent = 0; n->color = 1; n->key = k; n->value = 0;
    // link as child of cand
    n->parent = cand;
    if (cand == header) header->parent = n;
    else if (k < cand->key) cand->left = n;
    else cand->right = n;
    return n->value;
}

// @ 0x00a2e0e0
int AudioSystem::FUN_00a2e0e0(uint* p) {
    uchar* ht = (uchar*)this;
    int before = *(int*)(ht + 0xc);
    uint idx = *p % *(uint*)(ht + 8);
    uint* bucket = (uint*)(*(int*)(ht + 4) + idx * 4);
    if (*bucket) {
        uint* node;
        for (;;) {
            node = (uint*)*bucket;
            if (*p == *node) break;
            bucket = node + 9;
            if (!node[9]) break;
        }
        uint v = *bucket;
        while (v != 0 && (node = (uint*)*bucket, *p == *node)) {
            *bucket = node[9];
            operator_delete(node);
            *(int*)(ht + 0xc) -= 1;
            v = *bucket;
        }
    }
    return before - *(int*)(ht + 0xc);
}

// @ 0x00a2e1b0
void* AudioSystem::FUN_00a2e1b0(void* out, void* node, void* parent) {
    int* o = (int*)out;
    int* par = (int*)parent;
    int iVar1 = par[9];
    o[1] = (int)parent;
    *o = iVar1;
    while (iVar1 == 0) {
        o[1] += 4;
        iVar1 = *(int*)o[1];
        *o = iVar1;
    }
    int* puVar2 = (int*)*par;
    if (puVar2 == node) {
        *par = puVar2[9];
    } else {
        for (int* puVar3 = (int*)puVar2[9]; puVar3 != node; puVar3 = (int*)puVar3[9])
            puVar2 = puVar3;
        puVar2[9] = ((int*)node)[9];
    }
    operator_delete(node);
    *(int*)((uchar*)this + 0xc) -= 1;
    return out;
}

// @ 0x00a2e260
void AudioSystem::FUN_00a2e260(void* p) {
    uchar* vec = (uchar*)this;
    uchar* cur = *(uchar**)(vec + 4);
    if (cur < *(uchar**)(vec + 8)) {
        *(uchar**)(vec + 4) = cur + 0x14;
        if (cur) {
            memcpy(cur, p, 0x10);
            void* o = *(void**)((uchar*)p + 0x10);
            *(void**)(cur + 0x10) = o;
            if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        }
    } else {
        ((XF*)vec)->FUN_00a2af30(cur, p);
    }
}

// @ 0x00a2e2f0  (hashtable ctor; approximated)
AudioSystem* AudioSystem::FUN_00a2e2f0(void* p) {
    (void)p;
    return this;
}

// @ 0x00a2e420
void* AudioSystem::FUN_00a2e420(void* p) {
    void* node = *(void**)((uchar*)this + 0x1c);
    if (node) {
        *(void**)((uchar*)this + 0x1c) = *(void**)node;
    } else {
        node = operator_new(0x28, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    if (node) {
        *(uint*)node = *(uint*)p;
        *(uint*)((uchar*)node + 4) = *(uint*)((uchar*)p + 4);
        ((XF*)((uchar*)node + 8))->FUN_00a26fa0((uchar*)p + 8);
    }
    *(uint*)((uchar*)node + 0x24) = 0;
    return node;
}

// @ 0x00a2e4c0  (timing; approximated)
void* AudioSystem::FUN_00a2e4c0(void* p) {
    (void)p;
    return p;
}
