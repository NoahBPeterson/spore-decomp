// src/game/SPCreatureAnim/parts_caps.cpp -- migrated from slice(s) s009feb30, s009fdb00, s009fb8e0, s009a7810 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/parts_caps.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <string.h>
#include "EA/ArgScript/cCommandBase.h"
#include "nSPCreatureAnim/creature_instance_data.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t DAT_015506c8[];   // deform rbtree overload table

// ---- items of slice s009a7810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t DAT_015506c8[];   // deform rbtree overload table
namespace nSPCreatureAnim {
    int* GetAvailableDeformsForContextTarget(uint32_t* p, uint32_t* out);
}
// ---- items of slice s009a7810 end

// ---- items of slice s009fb8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void   DoInsertValue(void* dst, void* src, int size);   // 0x011e0744
extern void   RBTreeInsert(void* node, void* where, void* head, int left);  // 0x009216a0
extern void*  g_1551774;   // 0x01551774  "deform"
extern void*  g_14487f4;   // 0x014487f4  vftable
typedef unsigned char  uint8;
typedef unsigned int   uint32;
extern void*  operator_new(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern void   operator delete[](void* p);             // 0x00f47380
typedef void  (__thiscall *vt_v_ii)(void*, int, int);
struct CmdNew { void mctor(); };              // 0x0083c800 cCommandBase::cCommandBase
struct cCmdObj {
    void** vtbl;
    char pad[0x2c];
    int f30;
    void SetAB(int a, int b);                 // 0x0083c780 (thiscall, ret 8)
    void InitDeform(int a, int b);
};
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
struct RBTreeX {
    char pad0[4];
    char head[0x10];
    int  count;
    void InsertIdx(void** out, void* where, uint32* key, char hint);
};
// ---- items of slice s009fb8e0 end

// ---- items of slice s009fdb00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void   ElemFree(void* p);                                       // 0x00f47380
extern void   ErrorString(void* out, const char* fmt, ...);            // 0x0052df30
extern __declspec(noreturn) void CxxThrowException(void* a, void* b);  // 0x011e0912
extern void*  g_TI_cError;                                             // 0x014f9174
extern char   g_emptyStr[];                                            // 0x01667bac
extern float  g_1550b84;                                               // 0x01550b84
extern void*  g_166c070;                                               // 0x0166c070
extern void*  g_166c074;                                               // 0x0166c074
extern void*  g_166c078;                                               // 0x0166c078
extern void*  g_166c080;                                               // 0x0166c080
extern void   ElemConstructRange(void** out, void* first, void* last, void* dst, void* extra); // 0x009fc5b0
extern void*  ElemCopyRange(void* first, void* last, void* dst);       // 0x009fc8b0
extern void   ElemDestroy3(void* a, void* b, void* c);                 // 0x009fc390
extern void   ElemAssignFrom(void* first, void* last, const void* src);// 0x009fc680
extern void*  ElemMove3(void* first, void* last, void* dst);           // 0x009fc970
extern void*  CopyBackwardElem(void* first, void* last, void* result);                              // 0x009fca70
extern void* RBTreeIncrement(void* node);                              // 0x00921580
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define VT(o) (*(void***)(o))
extern void*  EAAllocate(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern uint32 FNV1String8(const char* s, uint32 seed, int a);          // 0x00932e80
extern uint32 PackFourCC(const char* s);                               // 0x009fc090
struct TreeFind { void find(void* outIter, const uint32* key); };      // 0x00e5c780
struct cErr16 { void* p0; void* p1; void* p2; void* p3; };
extern void   ElemFill(void* first, uint32 n, const void* value, void* extra);                 // 0x009fc6c0
struct CapName;
struct Str16 {
    void* b;
    void* e;
    void* c;
    uint32 pad;
    Str16() : b(g_emptyStr), e(g_emptyStr), c(g_emptyStr + 1) {}
    void assign(const char* first, const char* last);                  // 0x00454cb0
    Str16& operator=(const char* s) { assign(s, s + strlen(s)); return *this; }
};
struct CapName {
    Str16  name;
    uint32 val;
    CapName() {}
    CapName(const CapName& o);                                         // 0x009fc440
    CapName& operator=(const CapName& o)
    {
        if (&o != this) name.assign((const char*)o.name.b, (const char*)o.name.e);
        val = o.val;
        return *this;
    }
};
typedef bool (*CapCmp)(const CapName&, const CapName&);
extern void   insertion_sort_elem(void* first, void* last, CapCmp compare);                         // 0x009fcdb0
extern void   insertion_sort_simple_elem(void* first, void* last, CapCmp compare);                  // 0x009fcef0
extern void*  get_partition_elem(void* first, void* last, CapName pivot, CapCmp compare);            // 0x009fd5a0
extern void   partial_sort_elem(void* first, void* middle, void* last, CapCmp compare);             // 0x009fd620
struct CapVec {
    CapName* begin;
    CapName* end;
    CapName* cap;
    void resize(uint32 n);                                                       // 0x009fe2d0
    void DoInsertValues(CapName* pos, uint32 n, const CapName& value);           // 0x009fdb00
    void erase(CapName* first, CapName* last);                                   // 0x009fda60
};
struct MapIdxA {
    void* f0;
    void* anchor0;
    void* anchor1;
    void* root;
    void* f10;
    uint32 size;
    void* insert(const uint32& key);                                   // 0x009fd950
};
struct MapIdxB {
    void* f0;
    void* anchor0;
    void* anchor1;
    void* root;
    void* f10;
    uint32 size;
    void* insert(const uint32& key);                                   // 0x009fd9e0
};
struct ThresholdTarget { char pad[0x1c]; float thr; };
struct ArgArgs { uint32* MainArguments(int n); };                      // 0x00838320 thiscall ret 4
typedef float (__thiscall *Fn_fp)(void*, uint32);
#define EXEC_ARGS ArgArgs* args
struct Node16 { char pad[0x14]; uint32 v0; uint32 v1; };
struct cRemapCommand {
    char pad[0xc];
    void* p0c;
    void Execute(EXEC_ARGS);
};
struct cDeformBlocksEnabledCommand {
    char pad[0x30];
    void* p30;
    void Execute(bool enable);
};
struct RawTree {
    void* f0;
    void* anchor;
    char* minNode;
    char* root;
    uint8 color;
    uint8 pad[3];
    uint32 size;
};
struct Nuke1 { void f(void* node); };                                  // 0x009a9600
struct Nuke2 { void DoNukeSubtree(void* node); };                      // 0x005d9320
struct VecErase { void f(void* a, void* b); };                         // 0x0083fd70
struct cSetThresholdCommand {
    char pad4[4];
    void* p4;
    char pad8[4];
    ThresholdTarget* pc;
    void Execute(EXEC_ARGS);
};
struct cAddCapabilityCommand {
    char pad4[4];
    void* p4;
    char pad8[4];
    ThresholdTarget* pc;
    void Execute(EXEC_ARGS);
};
// ---- items of slice s009fdb00 end

// ---- items of slice s009feb30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete__(void* p);                 // 0x00f47380
extern bool  g_registered;          // 0x0166cbd0
extern float g_maxAnimTime;         // 0x01550b84
extern "C" void __cdecl FUN_009fe010(void* begin, void* end, void* cb);   // 0x009fe010
extern "C" void __cdecl FUN_009fc080();                                   // 0x009fc080 (callback)
extern const char* g_cmdPriName;   // 0x01551780
extern const char* g_cmdCapName;   // 0x01551770
extern const char* g_cmdAggName;   // 0x0155176c
extern const char* g_cmdRmpName;   // 0x01551784
extern const char* g_cmdDefName;   // 0x01551778
struct ResKey3 { int instance; int type; int group; };
struct CmdBase {                                  // EA::ArgScript::cCommandBase, 0x10 bytes
    CmdBase();                                    // 0x0083c800
    virtual void Execute();
    char pad[12];
};
struct CmdProps : CmdBase { CmdProps(); char more[0x24]; };   // AppProps-style ctor, 0x34 bytes (0x0083cdd0)
struct PriCmd : CmdBase { virtual void Execute(); };          // vtbl 0x01448770
struct CapCmd : CmdBase { virtual void Execute(); };          // vtbl 0x01448788
struct AggCmd : CmdBase { virtual void Execute(); };          // vtbl 0x014487a0
struct RmpCmd : CmdBase { virtual void Execute(); };          // vtbl 0x014487b8
struct DefSpcBlkCmd : CmdProps { virtual void Execute(); };   // vtbl 0x014487d0
struct ParseOpts {                                // eastl::string-like source name + parser state
    int   id;                                     // 0x01ff0ee3
    int   a, b;
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   pad;
    float duration;                               // written by the parser
};
struct Stream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void Seek(int a, int b);              // slot 10 (+0x28)
};
struct Record {                                   // object returned by the manager's lookup
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void v5();
    virtual Stream* GetStream();                  // slot 6 (+0x18)
virtual void v7();
virtual void v8();
    virtual void Close();                         // slot 9 (+0x24)
virtual void v10();
virtual void v11();
virtual void v12();
    virtual char Open(ResKey3* key, Record** out, int a, int b, int c, int d);   // slot 13 (+0x34)
};
struct Parser {
    virtual void AddRef();                        // 0x00
    virtual void v1();                            // 0x04
    virtual void Reset();                         // 0x08
    virtual void v3();                            // 0x0c
    virtual void SetOptions(ParseOpts* o);        // 0x10
    virtual void AddCommand(const char* name, CmdBase* cmd);   // 0x14
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void SetMode(int a, int b);           // 0x28
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual void ParseStream(Stream* s);          // 0x4c
};
struct ResMan {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual int  GetKeys(ResKey3** outVec, void* filter, int flags);   // slot 14 (+0x38)
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual Record* Lookup(ResKey3* key);         // slot 22 (+0x58)
};
struct KeyFilter {                                // local filter object with a vtable and a type id
    virtual void Dummy();
    int   typeID;
    ResKey3* mpBegin;                             // result vector (begin,end,cap)
    ResKey3* mpEnd;
    ResKey3* mpCap;
};
extern "C" ResMan* __cdecl GetManager();                                  // 0x0067dcd0
extern "C" Parser* __cdecl CreateParser();                                // 0x008408d0
extern "C" int __cdecl ReadInt32(Stream* s, int* dst, int count, int bigEndian);  // 0x0093a780
extern "C" void __cdecl FUN_009fe6c0(Stream* s);                          // 0x009fe6c0
struct ResList { ResKey3* begin; ResKey3* end; };
extern ResList* g_resList;         // 0x0166c070
// ---- items of slice s009feb30 end

// @ 0x009a84f0
int* rbtree_find(int* param_1, uint32_t param_2, int param_3, uint32_t* param_4)
{
    uint32_t uVar3 = 0;
    int* piVar1 = param_1;
    if (param_2 != 0) {
        do {
            if (*piVar1 == param_3) {
                if (param_4 == 0) return param_1 + uVar3 * 7 + 1;
                uint32_t uVar2 = 0;
                int* q = param_1 + uVar3 * 7 + 1;
                do {
                    if (*q == 0) break;
                    uVar2++;
                    q++;
                } while (uVar2 < 6);
                *param_4 = uVar2;
                return param_1 + uVar3 * 7 + 1;
            }
            uVar3++;
            piVar1 += 7;
        } while (uVar3 < param_2);
    }
    if (param_4 != 0) *param_4 = 0;
    return 0;
}

// @ 0x009a8560
int* nSPCreatureAnim::GetAvailableDeformsForContextTarget(uint32_t* param_1, uint32_t* param_2)
{
    if ((*param_1 & 0x101c03) == 0) {
        return rbtree_find((int*)&DAT_015506c8, 8, (int)param_1[1], param_2);
    }
    if ((*param_1 & 0x100003) == 1) {
        return rbtree_find((int*)&DAT_015506c8, 8, 0x746f6f72, param_2);
    }
    if (param_2 != 0) *param_2 = 0;
    return 0;
}

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

// @ 0x009fc4a0
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

// @ 0x009fc5b0
void ElemConstructRange(Elem14** out, Elem14* begin, Elem14* end, Elem14* dst0)
{
    Elem14* d = dst0;
    for (Elem14* s = begin; s != end; s = (Elem14*)((char*)s + 0x14))
        d->ElemCopy(s), d = (Elem14*)((char*)d + 0x14);
    *out = d;
}

// @ 0x009fc680
void ElemAssignFrom(Elem14* a, Elem14* b, Elem14* c)
{
    for (Elem14* p = a; p != b; p = (Elem14*)((char*)p + 0x14)) {
        if (c != p)
            p->assign(c->b, c->e);
        p->val = c->val;
    }
}

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

// @ 0x009fdb00
void CapVec::DoInsertValues(CapName* pos, uint32 n, const CapName& value)
{
    if (n <= (uint32)((char*)cap - (char*)end) / 0x14) {
        if (n > 0) {
            CapName temp(value);
            uint32 nExtra = (uint32)((char*)end - (char*)pos) / 0x14;
            if (n < nExtra) {
                void* out = 0;
                ElemConstructRange(&out, (char*)end - n * 0x14, (char*)end, (char*)end, (void*)pos);
                end = (CapName*)((char*)end + n * 0x14);
                CopyBackwardElem(out, (char*)end - n * 0x14, (char*)end);
                ElemAssignFrom(pos, (char*)pos + n * 0x14, &temp);
            }
            else {
                uint32 nNew = n - nExtra;
                ElemFill((char*)end, nNew, &temp, (void*)pos);
                end = (CapName*)((char*)end + nNew * 0x14);
                char* newEnd = (char*)end;
                void* out = 0;
                ElemConstructRange(&out, (void*)pos, (char*)newEnd - nNew * 0x14, newEnd, (void*)pos);
                end = (CapName*)((char*)end + nExtra * 0x14);
                ElemAssignFrom(pos, (char*)pos + nExtra * 0x14, &temp);
            }
        }
    }
    else {
        uint32 nPrevSize = (uint32)((char*)end - (char*)begin) / 0x14;
        uint32 nGrowSize = nPrevSize << 1;
        if (nPrevSize == 0)
            nGrowSize = 1;
        uint32 nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        CapName* pNewData = 0;
        if (nNewSize)
            pNewData = (CapName*)EAAllocate(nNewSize * 0x14, "Anim/partscaps/untagged", 0, 0, ALLOC_FILE, 0xd1);
        CapName* pNewEnd = (CapName*)ElemCopyRange(begin, pos, pNewData);
        char* pNewEnd2 = (char*)pNewEnd;
        ElemDestroy3(begin, pos, pNewData);
        ElemFill(pNewEnd2, n, &value, pNewEnd2);
        char* pTail = pNewEnd2 + n * 0x14;
        char* pOldEnd = (char*)end;
        CapName* pRes = (CapName*)ElemCopyRange(pos, pOldEnd, pTail);
        ElemDestroy3(pos, pOldEnd, pTail);
        if (begin != 0 && *(uint32*)((char*)begin - 4) != 0)
            ElemFree(begin);
        begin = pNewData;
        end = pRes;
        cap = (CapName*)((char*)pNewData + nNewSize * 0x14);
    }
}

// @ 0x009fdd10
void quick_sort_elem(CapName* first, CapName* last, int nDepth, CapCmp compare)
{
    for (;;) {
        uint32 nCount = (uint32)((char*)last - (char*)first) / 0x14;
        if (nCount < 0x1d || nDepth < 1) {
            if (nDepth == 0)
                partial_sort_elem(first, last, last, compare);
            return;
        }
        CapName* mid = first + (ptrdiff_t)((uint32)((char*)last - (char*)first) / 0x14 / 2);
        CapName* lastMinus = last - 1;
        CapName* pivot;
        if (compare(*first, *mid)) {
            if (compare(*mid, *lastMinus))
                pivot = mid;
            else if (compare(*first, *lastMinus))
                pivot = lastMinus;
            else
                pivot = first;
        }
        else {
            if (compare(*first, *lastMinus))
                pivot = first;
            else if (compare(*mid, *lastMinus))
                pivot = lastMinus;
            else
                pivot = mid;
        }
        CapName* middle = (CapName*)get_partition_elem(first, last, CapName(*pivot), compare);
        quick_sort_elem(middle, last, nDepth - 1, compare);
        last = middle;
        nDepth = nDepth - 1;
    }
}

// @ 0x009fdec0
void cRemapCommand::Execute(EXEC_ARGS)
{
    if (g_1550b84 >= *(float*)((char*)p0c + 0x1c))
        return;
    void* tree = g_166c074;
    uint32* a = (uint32*)args->MainArguments(2);
    void* iter;
    uint32 hash;
    hash = FNV1String8((const char*)a[1], 0x811c9dc5, 1);
    ((TreeFind*)tree)->find(&iter, &hash);
    Node16* node = (Node16*)iter;
    if (iter == (void*)((char*)tree + 4)) {
        cErr16 buf;
        ErrorString(&buf, "remap capability \"%s\" doesn't exist", a[1]);
        CxxThrowException(&buf, &g_TI_cError);
    }
    hash = FNV1String8((const char*)a[0], 0x811c9dc5, 1);
    uint32* v = (uint32*)((MapIdxA*)tree)->insert(hash);
    v[0] = node->v0;
    v[1] = node->v1;
}

// @ 0x009fdf80
void cDeformBlocksEnabledCommand::Execute(bool enable)
{
    void* o = p30;
    if (!enable) {
        if (*(float*)((char*)o + 0x1c) > g_1550b84) {
            uint32 key = *(uint32*)((char*)o + 4);
            uint32* n = (uint32*)((MapIdxB*)g_166c078)->insert(key);
            n[0] = *(uint32*)((char*)o + 8);
            *(int*)((char*)p30 + 8) = 0;
        }
        else {
            *(int*)((char*)o + 8) = 0;
        }
        return;
    }
    int* q = *(int**)((char*)o + 8);
    if (q != 0) {
        int x = *q;
        if (x != 0 && *(int*)(x - 4) != 0)
            ElemFree((void*)x);
        ElemFree(q);
    }
    *(int**)((char*)p30 + 8) = 0;
}

// @ 0x009fe010
void sort_elem(CapName* first, CapName* last, CapCmp compare)
{
    if (first != last) {
        int nCount = (int)(last - first);
        int i = nCount;
        int nDepth = 0;
        while (i != 0) {
            i >>= 1;
            ++nDepth;
        }
        quick_sort_elem(first, last, nDepth * 2 - 2, compare);
        if (nCount > 0x1c) {
            insertion_sort_elem(first, first + 0x1c, compare);
            insertion_sort_simple_elem(first + 0x1c, last, compare);
        }
        else {
            insertion_sort_elem(first, last, compare);
        }
    }
}

// @ 0x009fe1a0
void PurgeCapabilityTables()
{
    {
        CapVec* caps = (CapVec*)g_166c070;
        void* r = ElemMove3(caps->begin, caps->end, caps->end);
        ((VecErase*)caps)->f(r, caps->end);
        uint32 count = (uint32)((char*)caps->end - (char*)caps->begin) / 0x14;
        caps->end = (CapName*)((char*)caps->end + count * 0x14);
    }
    {
        RawTree* t = (RawTree*)g_166c074;
        ((Nuke1*)t)->f(t->root);
        t->minNode = (char*)t + 4;
        t->root = 0;
        t->color = 0;
        t->size = 0;
        *(void**)((char*)t + 4) = (char*)t + 4;
    }
    {
        RawTree* t = (RawTree*)g_166c080;
        ((Nuke2*)t)->DoNukeSubtree(t->root);
        t->root = 0;
        *(void**)((char*)t + 4) = (char*)t + 4;
        t->minNode = (char*)t + 4;
        t->color = 0;
        t->size = 0;
    }
    {
        RawTree* t = (RawTree*)g_166c078;
        char* anchor = (char*)t + 4;
        char* node = t->minNode;
        while (node != anchor) {
            int* v = *(int**)(node + 0x14);
            if (v != 0) {
                int x = *v;
                if (x != 0 && *(int*)(x - 4) != 0)
                    ElemFree((void*)x);
                ElemFree(v);
            }
            node = (char*)RBTreeIncrement(node);
        }
        char* root = t->root;
        while (root != 0) {
            char* left = *(char**)root;
            ((Nuke1*)t)->f(left);
            char* right = *(char**)(root + 4);
            ElemFree(root);
            root = right;
        }
        t->color = 0;
        t->size = 0;
        t->minNode = anchor;
        t->root = 0;
        *(void**)anchor = anchor;
    }
}

// @ 0x009fe2d0
void CapVec::resize(uint32 n)
{
    if (n > (uint32)(int)(end - begin)) {
        CapName value;
        DoInsertValues(end, n - (uint32)(int)(end - begin), value);
    }
    else {
        erase(begin + n, end);
    }
}

// @ 0x009fe350
void cSetThresholdCommand::Execute(EXEC_ARGS)
{
    uint32* a = (uint32*)args->MainArguments(1);
    pc->thr = ((Fn_fp)VT(p4)[0x98 / 4])(p4, a[0]);
    if (g_1550b84 < pc->thr)
        PurgeCapabilityTables();
}

// @ 0x009fe390
void cAddCapabilityCommand::Execute(EXEC_ARGS)
{
    if (!(g_1550b84 >= pc->thr)) {
    CapVec* v = (CapVec*)g_166c070;
    const char** a = (const char**)args->MainArguments(2);
    v->resize((int)((char*)v->end - (char*)v->begin) / 0x14 + 1);
    v->end[-1].name = a[0];
    uint32 fourcc = PackFourCC(a[1]);
    v->end[-1].val = fourcc;
    uint32 idx = (uint32)((int)((char*)v->end - (char*)v->begin) / 0x14 - 1);
    uint32 h1 = FNV1String8((const char*)v->end[-1].name.b, 0x811c9dc5, 1);
    uint32* n1 = (uint32*)((MapIdxA*)g_166c074)->insert(h1);
    n1[0] = fourcc;
    n1[1] = idx;
    uint32 h2 = FNV1String8(a[1], 0x811c9dc5, 1);
    uint32* n2 = (uint32*)((MapIdxA*)g_166c074)->insert(h2);
    n2[0] = fourcc;
    n2[1] = idx;
    }
}

// @ 0x009feb30
bool __cdecl RegisterSPSkinPaintCommands(void)
{
    if (g_resList->begin != g_resList->end)
        return true;

    KeyFilter filter;
    filter.typeID = 0x7c19aa7a;
    filter.mpBegin = 0;
    filter.mpEnd = 0;
    filter.mpCap = 0;
    bool found = GetManager()->GetKeys(&filter.mpBegin, &filter, 0) > 0;
    if (found) {
        ParseOpts opts;
        opts.id = 0x1ff0ee3;
        opts.a = 0;
        opts.b = 0;
        opts.mpBegin = (char*)0x1667bac;
        opts.mpEnd = (char*)0x1667bac;
        opts.mpCapacity = (char*)0x1667bad;
        Parser* parser = CreateParser();
        if (parser)
            parser->AddRef();
        parser->Reset();
        parser->SetOptions(&opts);
        parser->SetMode(2, 4);

        parser->AddCommand(g_cmdPriName, new PriCmd);
        parser->AddCommand(g_cmdCapName, new CapCmd);
        parser->AddCommand(g_cmdAggName, new AggCmd);
        parser->AddCommand(g_cmdRmpName, new RmpCmd);
        parser->AddCommand(g_cmdDefName, new DefSpcBlkCmd);

        for (ResKey3* key = filter.mpBegin; key != filter.mpEnd; ++key) {
            Record* rec = GetManager()->Lookup(key);
            Record* opened = 0;
            if (rec) {
                if (rec->Open(key, &opened, 1, 6, 1, 0)) {
                    Stream* stream = opened->GetStream();
                    int tag;
                    ReadInt32(stream, &tag, 1, 0);
                    if (tag == 0x70637470) {
                        FUN_009fe6c0(stream);
                    } else {
                        stream->Seek(0, 0);
                        opts.duration = 0.0f;
                        parser->ParseStream(stream);
                        if (opts.duration > g_maxAnimTime)
                            g_maxAnimTime = opts.duration;
                    }
                    opened->Close();
                }
                if (opened)
                    ((CmdBase*)opened)->Execute();   // intrusive Release of the opened record
            }
        }
        FUN_009fe010(g_resList->begin, g_resList->end, (void*)FUN_009fc080);
        g_registered = true;
        parser->v3();
        parser->v1();
        if (opts.mpCapacity - opts.mpBegin > 1 && opts.mpBegin)
            operator_delete__(opts.mpBegin);
    }
    return found;
}
