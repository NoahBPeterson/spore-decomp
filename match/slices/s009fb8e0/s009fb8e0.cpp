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
#include <math.h>

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// ---------------------------------------------------------------- imported helpers
extern void*  EA_Audio_GetSystemAT();                 // 0x00a206f0
extern void*  SP_AudioSystem();                       // 0x0067cb00
extern void*  SP_EffectsManager();                    // 0x0067ddd0
extern void   FUN_009fb830(void* self, float v);      // 0x009fb830
struct FUN_009b3010 { void reset(); };                // 0x009b3010 (thiscall)
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
extern float  g_1485720;   // 0x01485720 (1.0f)
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
typedef void  (__thiscall *vt_v_p)(void*, void*);
typedef void  (__thiscall *vt_v_pi)(void*, int*, int);
typedef char  (__thiscall *vt_c_pii)(void*, void*, int, void**);
typedef void* (__thiscall *vt_p0)(void*);

#define VT(obj, off)  (*(void***)(obj))[(off) / 4]

// ================================================================== @ 0x009fb8e0

// @ 0x009fb8e0
void ResetBodyRenderState(int inst)
{
    float* base = (float*)*(void**)(inst + 0x2e4);
    int count = (int)(((char*)*(void**)(inst + 0x2e8) - (char*)base) / 700);
    for (int i = 0; i < count; ++i) {
        float* e = base + i * 175;
        float* z = e + (0x164 / 4);
        float* d = e + (0x170 / 4);
        float* s = e + (0x190 / 4);
        z[0] = 0.0f;
        z[1] = 0.0f;
        z[2] = 0.0f;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d[4] = s[4];
        d[5] = s[5];
        d[6] = s[6];
    }
}

static const float& minf(const float& a, const float& b) { return a > b ? b : a; }

// ================================================================== @ 0x009fbb80

// @ 0x009fbb80
void AdvanceTimer(void* self, float dt)
{
    if (!self)
        return;
    if (*(uint8*)((char*)self + 0x1794) == 0)
        return;

    float* pf = (float*)((char*)self + 0x1798);
    *pf = *pf + dt;
    *pf = minf(*pf, g_166c978);
    float v = *pf;

    int n;
    float step;
    if (g_166c974 > v) {
        n = 1;
        step = v;
        *pf = 0.0f;
    } else {
        step = g_166c974;
        *pf = fmod(v, step);
        n = (int)(v / (step + g_13ec4b8));
    }
    for (int i = 0; i < n; ++i) {
        FUN_009fb830(self, step);
        ResetBodyRenderState((int)self);
    }
}

// ================================================================== @ 0x009fbc50

// @ 0x009fbc50
void AudioSetListener3(int a1, float b, float c, float d)
{
    void* s = EA_Audio_GetSystemAT();
    if (!s)
        return;
    ((vt_v_i)VT(s, 0x38))(s, 0x3475373);
    ((vt_v_ii)VT(s, 0x40))(s, 0x3475385, a1);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475391, b);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475395, c);
    ((vt_v_if)VT(s, 0x3c))(s, 0x3475398, d);
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
void AudioSetListener2(int p2, char v)
{
    void* s = EA_Audio_GetSystemAT();
    if (!s)
        return;
    ((vt_v_i)VT(s, 0x38))(s, 0x347536b);
    ((vt_v_ii)VT(s, 0x40))(s, 0x3475385, p2);
    ((vt_v_ii)VT(s, 0x40))(s, 0x34753a0, v == 0);
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
    float r;
    if (SP_AudioSystem()) {
        void* s = SP_AudioSystem();
        r = ((vt_f_i)VT(s, 0x44))(s, x);
    } else r = 0.0f;
    return r;
}

// @ 0x009fbe50
void AudioSetListener3v(int a1, float* v)
{
    AudioSetListener3(a1, v[0], v[1], v[2]);
}

// ================================================================== @ 0x009fbe80

// @ 0x009fbe80
struct FUN_0041cb40 { void ctor(void* src); };   // 0x0041cb40 (thiscall, ret 4)

struct EventDesc {
    uint16 flags;      // +0x00
    uint16 count;      // +0x02
    float  f04;        // +0x04
    float  f08;        // +0x08
    float  f0c;        // +0x0c
    float  f10;        // +0x10
    float  m[9];       // +0x14
};

struct V3 { float x, y, z; };
struct M9 { float m[9]; };

void EffectsEmitEvent(void* self, int group, void* mat)
{
    if (!self)
        return;

    M9 tmp;
    EventDesc desc;
    desc.flags = 0;
    desc.count = 0;
    desc.f04 = g_166ca38;
    desc.f08 = g_166ca3c;
    desc.f0c = g_166ca40;
    desc.f10 = g_1485720;
    ((FUN_0041cb40*)desc.m)->ctor(&g_166cb6c);

    ((vt_v_p)VT(self, 0x20))(self, &desc);

    if (group) {
        desc.flags |= 4;
        desc.count += 1;
        *(V3*)&desc.f04 = *(V3*)group;
    }
    if (mat) {
        float* s = (float*)mat;
        tmp.m[0] = s[0]; tmp.m[3] = s[1]; tmp.m[6] = s[2];
        tmp.m[1] = s[3]; tmp.m[4] = s[4]; tmp.m[7] = s[5];
        tmp.m[2] = s[6]; tmp.m[5] = s[7]; tmp.m[8] = s[8];
        *(M9*)desc.m = tmp;
        desc.flags |= 2;
        desc.count += 1;
    }
    ((vt_v_p)VT(self, 0x18))(self, &desc);
}

// ================================================================== @ 0x009fbfc0

__declspec(noinline)
// @ 0x009fbfc0
bool EffectsSpawn(void* a, int b, void* c, int d, int e, void** out)
{
    void* local = 0;
    if (!out)
        out = &local;
    if (!SP_EffectsManager())
        goto fail;
    {
        void* mgr = a;
        if (!mgr) {
            void* sys = SP_EffectsManager();
            mgr = ((vt_p0)VT(sys, 0x5c))(sys);
        }
        if (b)
            return false;
        if (((vt_c_pii)VT(mgr, 8))(mgr, c, 0, out)) {
            EffectsEmitEvent(*out, d, (void*)e);
            ((vt_v_i)VT(*out, 8))(*out, 0);
            if (local)
                ((vt_v0)VT(local, 4))(local);
            return true;
        }
    }
fail:
    *out = 0;
    return false;
}

// @ 0x009fc050
bool EffectsSpawnThunk(int a, int b, int c, int d, int e)
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
            if (p[i] == 0)
                break;
            buf[i] = p[i];
        }
    }
    return (uint32)(uint8)buf[3] << 24 | (uint32)(uint8)buf[2] << 16
         | (uint32)(uint8)buf[1] << 8  | (uint32)(uint8)buf[0];
}

// ================================================================== @ 0x009fc0f0

struct RBFind { void find(uint32* out, const uint32* key); };   // 0x00e5c780 (thiscall, ret 8)

// @ 0x009fc0f0
int FeedbackLookupName(const char* name)
{
    if (!name)
        return 0;
    uint32 out;
    uint32 h = EA_Hash_FNV1_String8(name, 0x811c9dc5, 1);
    RBFind* tree = (RBFind*)g_166c074;
    tree->find(&out, &h);
    if ((void*)out != (char*)tree + 4)
        return *(int*)(out + 0x14);
    return 0;
}

// ================================================================== @ 0x009fc140

// @ 0x009fc140
void BehaviorTableExpand(int self)
{
    char* p = (char*)self;
    int i = 0;
    while (*(int*)(p + 8 + i * 4) != 0) {
        ++i;
        if (i >= 0x20)
            break;
    }
    int j = 0;
    char* flags = p + 0x88;
    for (; j < 0x20; ++j) {
        uint32 key = *(uint32*)(p + 8 + j * 4);
        if (key == 0)
            break;
        char* tree = (char*)g_166c080;
        char* head = tree + 4;
        char* node = *(char**)(tree + 0xc);
        char* parent = head;
        while (node) {
            if (*(uint32*)(node + 0x10) < key) {
                node = *(char**)node;
            } else {
                parent = node;
                node = *(char**)(node + 4);
            }
        }
        if (parent == head || key < *(uint32*)(parent + 0x10))
            parent = head;
        if (parent != head) {
            uint32 cnt = (uint32)((*(char**)(parent + 0x18) - *(char**)(parent + 0x14)) >> 2);
            char* vb = *(char**)(parent + 0x14);
            for (uint32 k = 0; k < cnt; ++k) {
                *(uint32*)(p + 8 + i * 4) = *(uint32*)(vb + k * 4);
                *(char*)(p + 0x88 + i) = flags[j];
                ++i;
            }
        }
    }
    ((FUN_009b3010*)p)->reset();
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
            continue;
        for (int k = n + 1; k < 0x20; ++k) {
            if (slots[k] != 0 && slots[k] == v) {
                slots[k] = 0;
                if ((uint8)flags[n] < (uint8)flags[k])
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
    ((FUN_009b3010*)p)->reset();
}

// ================================================================== @ 0x009fc310

// @ 0x009fc310
int BehaviorLookup(uint32* p)
{
    uint32 key = p[0] & 0x100003;
    uint32 sel = p[0] & 0x801c00;
    if (key == 0) {
        key = p[1];
    } else if (key == 1) {
        key = 0x746f6f72;
    } else {
        return (int)(size_t)g_166c07c;
    }
    if (sel == 0x1800 || sel == 0x1c00 || sel == 0x800400)
        key = p[2];
    if (!key)
        return (int)(size_t)g_166c07c;
    uint32 out;
    RBFind* tree = (RBFind*)g_166c078;
    tree->find(&out, &key);
    if ((void*)out == (char*)tree + 4)
        return (int)(size_t)g_166c07c;
    return *(int*)(out + 0x14);
}

// ================================================================== @ 0x009fc3e0

extern void FUN_0083c780(int, int);           // 0x0083c780

struct CmdNew { void mctor(); };              // 0x0083c800 cCommandBase::cCommandBase

struct cCmdObj {
    void** vtbl;
    char pad[0x2c];
    int f30;
    void SetAB(int a, int b);                 // 0x0083c780 (thiscall, ret 8)
    void InitDeform(int a, int b);
};

// @ 0x009fc3e0
void cCmdObj::InitDeform(int a, int b)
{
    this->f30 = b;
    this->SetAB(a, b);
    void* cmd = operator_new(0x10, "ArgScript/Deform", 0, 0, 0, 0);
    if (cmd) {
        ((CmdNew*)cmd)->mctor();
        *(void**)cmd = &g_14487f4;
    } else {
        cmd = 0;
    }
    ((vt_v_ii)this->vtbl[0x18 / 4])(this, (int)(size_t)g_1551774, (int)(size_t)cmd);
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
    Elem14* ElemCopy(const Elem14* src);
};

// @ 0x009fc440
Elem14* Elem14::ElemCopy(const Elem14* src)
{
    this->b = this->e = this->c = 0;
    int n = (int)((char*)src->e - (char*)src->b);
    this->RangeInitialize(n + 1);
    char* dst = (char*)this->b;
    DoInsertValue(dst, src->b, n);
    this->e = dst + n;
    *(dst + n) = 0;
    this->val = src->val;
    return this;
}

// ================================================================== @ 0x009fc4a0

// @ 0x009fc4a0
struct RBTreeX {
    char pad0[4];
    char head[0x10];
    int  count;
    void InsertIdx(void** out, void* where, uint32* key, char hint);
};
void RBTreeX::InsertIdx(void** out, void* where, uint32* key, char hint)
{
    int left = (hint == 0 && where != (void*)((char*)this + 4) && *key >= *(uint32*)((char*)where + 0x10)) ? 1 : 0;
    void* node = operator_new(0x1c, (const char*)0x1448758, 0, 0, (const char*)0x13ebb38, 0xd1);
    uint32* dst = (uint32*)((char*)node + 0x10);
    if (dst) {
        dst[0] = key[0];
        dst[1] = key[1];
        dst[2] = key[2];
    }
    RBTreeInsert(node, where, (char*)this + 4, left);
    count = count + 1;
    *out = node;
}

// ================================================================== @ 0x009fc5b0

// @ 0x009fc5b0
void ElemConstructRange(Elem14** out, Elem14* begin, Elem14* end, Elem14* dst0)
{
    Elem14* d = dst0;
    for (Elem14* s = begin; s != end; s = (Elem14*)((char*)s + 0x14))
        d->ElemCopy(s), d = (Elem14*)((char*)d + 0x14);
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
void ElemFill(Elem14* dst, unsigned n, Elem14* src)
{
    for (; n > 0; --n, dst = (Elem14*)((char*)dst + 0x14)) {
        if (dst) {
            dst->b = 0;
            dst->e = 0;
            dst->c = 0;
            unsigned len = (unsigned)((char*)src->e - (char*)src->b);
            unsigned sz = len + 1;
            if (sz > 1) {
                char* p = (char*)operator_new(sz, (const char*)0x13ebb38, 0, 0, (const char*)0x1448758, 0xd1);
                dst->b = p;
                dst->e = p;
                dst->c = p + sz;
            } else {
                dst->b = (void*)0x1667bac;
                dst->e = (void*)0x1667bac;
                dst->c = (void*)0x1667bad;
            }
            DoInsertValue(dst->b, src->b, len);
            dst->e = (char*)dst->b + len;
            *((char*)dst->b + len) = 0;
            dst->val = src->val;
        }
    }
}

// ================================================================== @ 0x009fc8b0

// @ 0x009fc8b0
Elem14* ElemCopyRange(Elem14* a, Elem14* b, Elem14* c)
{
    if (a == b)
        return c;
    do {
        if (c) {
            c->b = 0;
            c->e = 0;
            c->c = 0;
            unsigned len = (unsigned)((char*)a->e - (char*)a->b);
            unsigned sz = len + 1;
            if (sz > 1) {
                char* p = (char*)operator_new(sz, (const char*)0x13ebb38, 0, 0, (const char*)0x1448758, 0xd1);
                c->b = p;
                c->e = p;
                c->c = p + sz;
            } else {
                c->b = (void*)0x1667bac;
                c->e = (void*)0x1667bac;
                c->c = (void*)0x1667bad;
            }
            DoInsertValue(c->b, a->b, len);
            c->e = (char*)c->b + len;
            *((char*)c->b + len) = 0;
            c->val = a->val;
        }
        a = (Elem14*)((char*)a + 0x14);
        c = (Elem14*)((char*)c + 0x14);
    } while (a != b);
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
void ElemHeapSiftUp(int base, int pos, int end, Elem14 v, bool (*cmp)(Elem14*, Elem14*))
{
    int parent = (end - 1) >> 1;
    if (end > pos) {
        do {
            Elem14* pe = (Elem14*)(base + parent * 0x14);
            if (!cmp(pe, &v))
                break;
            Elem14* endE = (Elem14*)(base + end * 0x14);
            if (pe != endE)
                endE->assign(pe->b, pe->e);
            endE->val = pe->val;
            end = parent;
            parent = (parent - 1) >> 1;
        } while (end > pos);
    }
    Elem14* slot = (Elem14*)(base + end * 0x14);
    if (&v != slot)
        slot->assign(v.b, v.e);
    slot->val = v.val;
    if ((int)((char*)v.c - (char*)v.b) > 1 && v.b)
        operator delete[](v.b);
}
