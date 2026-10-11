// slice s009fb8e0 -- SP creature-graphics / effects utilities and eastl container helpers.
//
//   VA 009fb8e0  ResetBodyRenderState
//   VA 0x009fbb80  AdvanceTimer
//   VA 0x009fbc50  AudioSetListener3
//   VA 0x009fbcd0  AudioSetEvent9
//   VA 0x009fbcf0  AudioSetEvent10
//   VA 0x009fbd10  AudioSetFlag
//   VA 0x009fbd30  AudioSetEvent5
//   VA 0x009fbd50  AudioSetEvent1
//   VA 0x009fbd70  AudioSetListener2
//   VA 0x009fbdd0  AudioQueryA
//   VA 0x009fbe00  AudioQueryB
//   VA 0x009fbe20  AudioQueryC
//   VA 0x009fbe50  AudioSetListener3v
//   VA 0x009fbe80  EffectsEmitEvent
//   VA 0x009fbfc0  EffectsSpawn
//   VA 0x009fc050  EffectsSpawnThunk
//   VA 0x009fc090  PackFourCC
//   VA 0x009fc0f0  FeedbackLookupName
//   VA 0x009fc140  BehaviorTableExpand
//   VA 0x009fc220  BehaviorTableDedup
//   VA 0x009fc310  BehaviorLookup
//   VA 0x009fc3e0  cCommandBase::InitDeform
//   VA 0x009fc440  ElemCtor
//   VA 0x009fc4a0  RBTreeInsertIdx
//   VA 0x009fc5b0  ElemConstructRange
//   VA 0x009fc680  ElemAssignFrom
//   VA 0x009fc6c0  ElemFill
//   VA 0x009fc8b0  ElemCopyRange
//   VA 0x009fc970  ElemMove
//   VA 0x009fc9c0  ElemHeapSiftUp
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// ---------------------------------------------------------------- imported helpers
extern void*  EA_Audio_GetSystemAT();                 // 0x00a206f0
extern void*  SP_AudioSystem();                       // 0x0067cb00
extern void*  SP_EffectsManager();                    // 0x0067ddd0
extern void   FUN_009fb830(void* self, float v);      // 0x009fb830
extern void   FUN_009b3010(void* self);               // 0x009b3010
extern void   Matrix3_Assign(void* dst, void* src);   // 0x0041cb40
extern uint32 EA_Hash_FNV1_String8(const char* s, uint32 seed, int len);   // 0x00932e80
extern void*  eastl_rbtree_find(void* tree, void* key, void* node);        // 0x00e5c780
extern void*  operator_new(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern void   operator delete[](void* p);             // 0x00f47380
extern void   DoInsertValue(void* dst, void* src, int size);   // 0x011e0744
extern void   RBTreeInsert(void* node, void* where, void* head, int left);  // 0x009216a0

// globals
extern float  g_166c978;   // 0x0166c978  timer max
extern float  g_166c974;   // 0x0166c974  timer period
extern float  g_13ec4b8;   // 0x013ec4b8  epsilon
extern void*  g_166c074;   // 0x0166c074
extern void*  g_166c078;   // 0x0166c078
extern void*  g_166c07c;   // 0x0166c07c
extern void*  g_166c080;   // 0x0166c080
extern uint8  g_166cb6c;   // 0x0166cb6c  matrix literal
extern float  g_166ca38;   // 0x0166ca38
extern float  g_166ca3c;   // 0x0166ca3c
extern float  g_166ca40;   // 0x0166ca40
extern void*  g_1551774;   // 0x01551774  "deform"
extern void*  g_14487f4;   // 0x014487f4  vftable
extern uint8  g_1667bac;   // 0x01667bac  empty-string sentinel

// the vtables of the audio/effects interfaces (slots indexed in dwords)
typedef void  (__thiscall *vt_v0)(void*);
typedef void  (__thiscall *vt_v_i)(void*, int);
typedef void  (__thiscall *vt_v_ii)(void*, int, int);
typedef void  (__thiscall *vt_v_iii)(void*, int, int, int);
typedef int   (__thiscall *vt_i_i)(void*, int);
typedef float (__thiscall *vt_f_i)(void*, int);
typedef void  (__thiscall *vt_v_ff)(void*, int, float);
typedef void  (__thiscall *vt_v_if)(void*, int, float);
typedef void  (__thiscall *vt_v_pi)(void*, int*, int);

#define VT(obj, off)  (*(void***)(obj))[(off) / 4]

// ================================================================== @ 0x009fb8e0

// @ 0x009fb8e0
void ResetBodyRenderState(int inst)
{
    char* base = *(char**)(inst + 0x2e4);
    int count = (int)((*(char**)(inst + 0x2e8) - base) / 700);
    for (int i = 0; i < count; ++i) {
        char* e = base + i * 700;
        *(float*)(e + 0x164) = 0.0f;
        *(float*)(e + 0x168) = 0.0f;
        *(float*)(e + 0x16c) = 0.0f;
        *(float*)(e + 0x170) = *(float*)(e + 0x190);
        *(float*)(e + 0x174) = *(float*)(e + 0x194);
        *(float*)(e + 0x178) = *(float*)(e + 0x198);
        *(float*)(e + 0x17c) = *(float*)(e + 0x19c);
        *(float*)(e + 0x180) = *(float*)(e + 0x1a0);
        *(float*)(e + 0x184) = *(float*)(e + 0x1a4);
        *(float*)(e + 0x188) = *(float*)(e + 0x1a8);
        *(float*)(e + 0x420) = 0.0f;
        *(float*)(e + 0x424) = 0.0f;
        *(float*)(e + 0x428) = 0.0f;
        *(float*)(e + 0x42c) = *(float*)(e + 0x44c);
        *(float*)(e + 0x430) = *(float*)(e + 0x450);
        *(float*)(e + 0x434) = *(float*)(e + 0x454);
        *(float*)(e + 0x438) = *(float*)(e + 0x458);
        *(float*)(e + 0x43c) = *(float*)(e + 0x45c);
        *(float*)(e + 0x440) = *(float*)(e + 0x460);
        *(float*)(e + 0x444) = *(float*)(e + 0x464);
        *(float*)(e + 0x6dc) = 0.0f;
        *(float*)(e + 0x6e0) = 0.0f;
        *(float*)(e + 0x6e4) = 0.0f;
        *(float*)(e + 0x6e8) = *(float*)(e + 0x708);
        *(float*)(e + 0x6ec) = *(float*)(e + 0x70c);
        *(float*)(e + 0x6f0) = *(float*)(e + 0x710);
        *(float*)(e + 0x6f4) = *(float*)(e + 0x714);
        *(float*)(e + 0x6f8) = *(float*)(e + 0x718);
        *(float*)(e + 0x6fc) = *(float*)(e + 0x71c);
        *(float*)(e + 0x700) = *(float*)(e + 0x720);
        *(float*)(e + 0x998) = 0.0f;
        *(float*)(e + 0x99c) = 0.0f;
        *(float*)(e + 0x9a0) = 0.0f;
        *(float*)(e + 0x9a4) = *(float*)(e + 0x9c4);
        *(float*)(e + 0x9a8) = *(float*)(e + 0x9c8);
        *(float*)(e + 0x9ac) = *(float*)(e + 0x9cc);
        *(float*)(e + 0x9b0) = *(float*)(e + 0x9d0);
        *(float*)(e + 0x9b4) = *(float*)(e + 0x9d4);
        *(float*)(e + 0x9b8) = *(float*)(e + 0x9d8);
        *(float*)(e + 0x9bc) = *(float*)(e + 0x9dc);
        *(float*)(e + 0x9c0) = *(float*)(e + 0x9e0);
    }
}

// ================================================================== @ 0x009fbb80

// @ 0x009fbb80
void AdvanceTimer(void* self, float dt)
{
    if (!self)
        return;
    if (*(uint8*)((char*)self + 0x1794) == 0)
        return;

    float* pf = (float*)((char*)self + 0x1798);
    float v = *pf + dt;
    *pf = v;
    if (v > g_166c978)
        v = g_166c978;
    *pf = v;

    int n;
    float carry;
    if (g_166c974 > v) {
        n = 1;
        carry = v;
        *pf = 0.0f;
    } else {
        n = (int)(v / (g_166c974 + g_13ec4b8));
        carry = (float)(v - (float)n * g_166c974);
        *pf = carry;
    }
    for (int i = 0; i < n; ++i) {
        FUN_009fb830(self, carry);
        ResetBodyRenderState((int)self);
    }
}

// ================================================================== @ 0x009fbc50

// @ 0x009fbc50
void AudioSetListener3(float x, float y, float z, int p4)
{
    void* s = EA_Audio_GetSystemAT();
    if (!s)
        return;
    ((vt_v_i)VT(s, 0x38))(s, 0x3475373);
    ((vt_v_if)VT(s, 0x40))(s, 0x3475385, x);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475391, y);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475395, z);
    ((vt_v_i)VT(s, 0x3c))(s, 0x3475398);
    ((vt_v0)VT(s, 0x58))(s);
}

// ================================================================== @ 0x009fbcd0

// @ 0x009fbcd0
void AudioSetEvent9(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x40))(p, 9, v, 1);
}

// @ 0x009fbcf0
void AudioSetEvent10(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x44))(p, 10, (int)&v, 1);
}

// @ 0x009fbd10
void AudioSetFlag(void* p, char v)
{
    if (p)
        ((vt_v_i)VT(p, 0xc))(p, v == 0);
}

// @ 0x009fbd30
void AudioSetEvent5(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x40))(p, 5, v, 1);
}

// @ 0x009fbd50
void AudioSetEvent1(void* p, int v)
{
    if (p)
        ((vt_v_iii)VT(p, 0x44))(p, 1, (int)&v, 1);
}

// ================================================================== @ 0x009fbd70

// @ 0x009fbd70
void AudioSetListener2(int v)
{
    void* s = EA_Audio_GetSystemAT();
    if (!s)
        return;
    ((vt_v_i)VT(s, 0x38))(s, 0x347536b);
    ((vt_v_i)VT(s, 0x40))(s, 0x3475385);
    ((vt_v_i)VT(s, 0x40))(s, 0x34753a0);
    ((vt_v0)VT(s, 0x58))(s);
}

// ================================================================== @ 0x009fbdd0

// @ 0x009fbdd0
char AudioQueryA(int x)
{
    void* s = EA_Audio_GetSystemAT();
    if (s)
        return ((vt_i_i)VT(s, 0x28))(s, x);
    return 0;
}

// @ 0x009fbe00
void AudioQueryB(int x)
{
    void* s = EA_Audio_GetSystemAT();
    if (s)
        ((vt_v_i)VT(s, 0x2c))(s, x);
}

// @ 0x009fbe20
float AudioQueryC(int x)
{
    if (!SP_AudioSystem())
        return 0.0f;
    void* s = SP_AudioSystem();
    return ((vt_f_i)VT(s, 0x44))(s, x);
}

// @ 0x009fbe50
void AudioSetListener3v(int a1, float* v)
{
    AudioSetListener3(v[0], v[1], v[2], a1);
}

// ================================================================== @ 0x009fbe80

// @ 0x009fbe80
void EffectsEmitEvent(void* self, int group, void* pos, void* mat)
{
    if (!self)
        return;

    uint8 buf[0x60];
    *(float*)(buf + 0x2c) = g_166ca38;
    *(float*)(buf + 0x30) = g_166ca3c;
    *(float*)(buf + 0x34) = g_166ca40;
    *(uint16*)(buf + 0x04) = 0;
    *(uint16*)(buf + 0x06) = 0;
    *(float*)(buf + 0x08) = 1.0f;
    Matrix3_Assign(buf + 0x1c, &g_166cb6c);

    ((vt_v_pi)VT(self, 0x20))(self, (int*)(buf + 0x04), 0);

    if (group) {
        *(uint16*)(buf + 0x04) |= 4;
        *(uint16*)(buf + 0x06) += 1;
        *(uint32*)(buf + 0x08) = *(uint32*)group;
        *(uint32*)(buf + 0x0c) = *(uint32*)((char*)group + 4);
        *(uint32*)(buf + 0x10) = *(uint32*)((char*)group + 8);
    }
    if (mat) {
        *(float*)(buf + 0x00) = *(float*)((char*)mat + 0x00);
        *(float*)(buf + 0x0c) = *(float*)((char*)mat + 0x04);
        *(float*)(buf + 0x18) = *(float*)((char*)mat + 0x08);
        *(float*)(buf + 0x04) = *(float*)((char*)mat + 0x0c);
        *(float*)(buf + 0x10) = *(float*)((char*)mat + 0x10);
        *(float*)(buf + 0x1c) = *(float*)((char*)mat + 0x14);
        *(float*)(buf + 0x08) = *(float*)((char*)mat + 0x18);
        *(float*)(buf + 0x14) = *(float*)((char*)mat + 0x1c);
        *(float*)(buf + 0x20) = *(float*)((char*)mat + 0x20);
        *(uint16*)(buf + 0x04) |= 2;
        *(uint16*)(buf + 0x06) += 1;
    }
    ((vt_v_pi)VT(self, 0x18))(self, (int*)(buf + 0x04), 0);
}

// ================================================================== @ 0x009fbfc0

// @ 0x009fbfc0
int EffectsSpawn(void* a, int b, void* c, int d, int e, void** out)
{
    int local = 0;
    if (!out)
        out = (void**)&local;
    if (!SP_EffectsManager())
        goto fail;
    {
        void* mgr = a;
        if (!mgr)
            mgr = (void*)0;   // (original: default effects manager)
        if (b)
            return 0;
        if (((char(__thiscall*)(void*, void*, int, void**))VT(mgr, 8))(mgr, c, 0, out)) {
            EffectsEmitEvent(*out, (int)c, 0, 0);
            return 1;
        }
    }
fail:
    *out = 0;
    return 0;
}

// @ 0x009fc050
int EffectsSpawnThunk(int a, int b, int c, int d, int e)
{
    return EffectsSpawn((void*)a, 0, (void*)b, c, d, (void**)e);
}

// ================================================================== @ 0x009fc090

// @ 0x009fc090
uint32 PackFourCC(const char* p)
{
    char buf[4] = {0, 0, 0, 0};
    if (p) {
        for (int i = 0; i < 4; ++i) {
            char ch = p[i];
            if (ch == 0)
                break;
            buf[i] = ch;
        }
    }
    return (uint32)(uint8)buf[3] << 24 | (uint32)(uint8)buf[2] << 16
         | (uint32)(uint8)buf[1] << 8  | (uint32)(uint8)buf[0];
}

// ================================================================== @ 0x009fc0f0

// @ 0x009fc0f0
int FeedbackLookupName(const char* name)
{
    if (!name)
        return 0;
    uint32 h = EA_Hash_FNV1_String8(name, 0x811c9dc5, 1);
    void* tree = g_166c074;
    void* node = eastl_rbtree_find(tree, &h, (char*)tree + 4);
    if (node == (char*)tree + 4)
        return 0;
    return *(int*)((char*)node + 0x14);
}

// ================================================================== @ 0x009fc140

// @ 0x009fc140
void BehaviorTableExpand(int self)
{
    char* p = (char*)self;
    int i = 0;
    while (i < 0x20 && *(int*)(p + 8 + i * 4) != 0)
        ++i;
    int dst = 0;
    char* flags = p + 0x88;
    while (dst < 0x20) {
        uint32 key = *(uint32*)(p + 8 + dst * 4);
        if (key == 0)
            break;
        void* head = (void*)((char*)g_166c080 + 4);
        void* node = *(void**)((char*)g_166c080 + 0xc);
        void* parent = head;
        while (node) {
            if (*(uint32*)((char*)node + 0x10) < key) {
                node = *(void**)node;
            } else {
                parent = node;
                node = *(void**)((char*)node + 4);
            }
        }
        if (parent == head || key < *(uint32*)((char*)parent + 0x10))
            parent = head;
        if (parent != head) {
            uint32 cnt = (uint32)((*(char**)((char*)parent + 0x18) - *(char**)((char*)parent + 0x14)) >> 2);
            for (uint32 k = 0; k < cnt; ++k) {
                *(uint32*)(p + 8 + i * 4) = *(uint32*)(*(char**)((char*)parent + 0x14) + k * 4);
                *(char*)(p + 0x88 + i) = flags[dst];
                ++i;
            }
        }
        ++dst;
    }
    FUN_009b3010(p);
}

// ================================================================== @ 0x009fc220

// @ 0x009fc220
void BehaviorTableDedup(int self)
{
    char* p = (char*)self;
    BehaviorTableExpand(self);
    int* slots = (int*)(p + 8);
    char* flags = p + 0x88;
    for (int n = 0; n < 0x20; ++n) {
        int v = slots[n];
        if (v == 0)
            break;
        for (int k = n + 1; k < 0x20; ++k) {
            if (slots[k] != 0 && slots[k] == v) {
                slots[k] = 0;
                if (flags[k] < flags[n])
                    flags[n] = flags[k];
            }
        }
    }
    // compact empty slots
    int hi = 0x1f;
    for (int lo = 0; lo < hi; ++lo) {
        if (slots[lo] == 0 && lo < hi) {
            while (hi > lo && slots[hi] == 0)
                --hi;
            if (hi > lo) {
                slots[lo] = slots[hi];
                flags[lo] = flags[hi];
                slots[hi] = 0;
                --hi;
            }
        }
    }
    FUN_009b3010(p);
}

// ================================================================== @ 0x009fc310

// @ 0x009fc310
int BehaviorLookup(uint32* p)
{
    uint32 key = p[0] & 0x100003;
    if (key == 0) {
        key = p[1];
    } else if (key != 1) {
        return (int)(size_t)g_166c07c;
    } else {
        key = 0x746f6f72;
    }
    uint32 sel = p[0] & 0x801c00;
    if (sel == 0x1800 || sel == 0x1c00 || sel == 0x800400)
        key = p[2];
    if (key) {
        void* tree = g_166c078;
        void* node = eastl_rbtree_find(tree, &key, (char*)tree + 4);
        if (node != (char*)tree + 4)
            return *(int*)((char*)node + 0x14);
    }
    return (int)(size_t)g_166c07c;
}

// ================================================================== @ 0x009fc3e0

// @ 0x009fc3e0
void cCommandBase_InitDeform(void* self, int a, int b)
{
    *(int*)((char*)self + 0x30) = b;
    // FUN_0083c780(a, b)
    extern void FUN_0083c780(int, int);      // 0x0083c780
    FUN_0083c780(a, b);
    void* cmd = operator_new(0x10, "ArgScript/Deform", 0, 0, 0, 0);
    if (cmd)
        *(void**)cmd = &g_14487f4;
    ((vt_v_ii)VT(self, 0x18))(self, (int)(size_t)g_1551774, (int)(size_t)cmd);
}

// ================================================================== @ 0x009fc440

struct Elem14 {
    void* b;
    void* e;
    void* c;
    uint32 pad;
    uint32 val;
    void assign(void* begin, void* end);   // 0x00454cb0
    void RangeInitialize(int n);           // 0x00475ab0
};

static void construct14(Elem14* d, const Elem14* s)
{
    d->b = d->e = d->c = 0;
    int n = (int)((char*)s->e - (char*)s->b);
    int n1 = n + 1;
    if (n1 < 2) {
        d->b = &g_1667bac;
        d->e = &g_1667bac;
        d->c = (char*)&g_1667bac + 1;
    } else {
        char* buf = (char*)operator_new((uint32)n1, "Anim/partscaps/untagged", 0, 0, 0, 0xd1);
        d->b = buf;
        d->e = buf;
        d->c = buf + n1;
    }
    char* dst = (char*)d->b;
    for (int i = 0; i < n; ++i)
        dst[i] = ((char*)s->b)[i];
    dst[n] = 0;
    d->e = dst + n;
    d->val = s->val;
}

// @ 0x009fc440
Elem14* ElemCtor(Elem14* self, const Elem14* src)
{
    construct14(self, src);
    return self;
}

// ================================================================== @ 0x009fc4a0

// @ 0x009fc4a0
void RBTreeInsertIdx(void* self, void** out, void* where, uint32* key, int hint)
{
    int left = (hint == 0 && where != (char*)self + 4 && *(uint32*)((char*)where + 0x10) <= *key) ? 1 : 0;
    void* node = operator_new(0x1c, "Anim/partscaps/untagged", 0, 0, 0, 0xd1);
    *(uint32*)((char*)node + 0x10) = key[0];
    *(uint32*)((char*)node + 0x14) = key[1];
    *(uint32*)((char*)node + 0x18) = key[2];
    RBTreeInsert(node, where, (char*)self + 4, left);
    ++*(int*)((char*)self + 0x14);
    *out = node;
}

// ================================================================== @ 0x009fc5b0

// @ 0x009fc5b0
void ElemConstructRange(Elem14** out, Elem14* begin, Elem14* end, Elem14* dst0)
{
    Elem14* d = dst0;
    for (Elem14* s = begin; s != end; s = (Elem14*)((char*)s + 0x14))
        construct14(d, s), d = (Elem14*)((char*)d + 0x14);
    *out = d;
}

// ================================================================== @ 0x009fc680

// @ 0x009fc680
void ElemAssignFrom(Elem14* a, Elem14* b, Elem14* c)
{
    for (Elem14* p = a; p != b; p = (Elem14*)((char*)p + 0x14)) {
        if (c != p)
            p->assign(c->b, c->e);
        p->val = c->val;
    }
}

// ================================================================== @ 0x009fc6c0

// @ 0x009fc6c0
void ElemFill(Elem14* dst, int n, Elem14* src)
{
    for (int i = 0; i < n; ++i)
        construct14((Elem14*)((char*)dst + i * 0x14), src);
}

// ================================================================== @ 0x009fc8b0

// @ 0x009fc8b0
Elem14* ElemCopyRange(Elem14* a, Elem14* b, Elem14* c)
{
    for (; a != b; a = (Elem14*)((char*)a + 0x14), c = (Elem14*)((char*)c + 0x14))
        construct14(c, a);
    return c;
}

// ================================================================== @ 0x009fc970

// @ 0x009fc970
Elem14* ElemMove(Elem14* a, Elem14* b, Elem14* c)
{
    for (; a != b; a = (Elem14*)((char*)a + 0x14), c = (Elem14*)((char*)c + 0x14)) {
        if (a != c)
            c->assign(a->b, a->e);
        c->val = a->val;
    }
    return c;
}

// ================================================================== @ 0x009fc9c0

// @ 0x009fc9c0
void ElemHeapSiftUp(int base, int pos, int end, uint8* value, int (*cmp)(void*, void*))
{
    while (pos < end) {
        int parent = (end - 1) >> 1;
        Elem14* pe = (Elem14*)(base + parent * 0x14);
        if (!cmp(pe, value))
            break;
        Elem14* endE = (Elem14*)(base + end * 0x14);
        if (pe != endE)
            endE->assign(pe->b, pe->e);
        endE->val = pe->val;
        end = parent;
    }
    Elem14* slot = (Elem14*)(base + end * 0x14);
    Elem14* v = (Elem14*)value;
    if (v != slot)
        slot->assign(v->b, v->e);
    slot->val = v->val;
    if ((int)((char*)v->e - (char*)v->b) > 1 && v->b)
        operator delete[](v->b);
}
