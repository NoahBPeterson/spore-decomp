// SporeApp feedback-event rbtree / map helpers (slice s00baf630).
// Built with VS2008 SP1 (cl 15.00.30729.01) at /arch:SSE.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------
// Globals — the module-wide feedback-event rbtree (keyed by unsigned).
// ---------------------------------------------------------------------------
extern char g_0156c61c[];   // 0x0156c61c  global rbtree object
extern char g_0156c620[];   // 0x0156c620  its end/sentinel node

// ---------------------------------------------------------------------------
// Callees (all reconstructed as members so ecx=this and ret N are reproduced).
// ---------------------------------------------------------------------------
struct FeedbackEvent
{
    virtual void AddRef(void);                  // vtable[0x00]
    virtual void Release(void);                 // vtable[0x04]
    void FUN_00bb9b00(int a, int b);            // 0x00bb9b00
    int  FUN_00bb9b80(void);                    // 0x00bb9b80
    void FUN_00bb9b90(int v);                   // 0x00bb9b90
    void FUN_00a16a90(int v);                   // 0x00a16a90
};

struct RBTree
{
    void  find(void** pOut, const void* pKey);  // 0x00e5c780
    void* FUN_00dd85c0(void* p);                // 0x00dd85c0
    void  FUN_00baa110(void* p);                // 0x00baa110
};

struct Obj700
{
    void* FUN_00c30e80(void);                   // 0x00c30e80
};

extern int __cdecl FUN_0067de30(void);          // 0x0067de30  SP::PropertyManager

// vtable[0x2c] of the SP::PropertyManager singleton.
struct PropertyManager
{
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28();
    virtual void p2c(void* a, const char* name, void* b);
};

// ---------------------------------------------------------------------------
// @ 0x00baf630
// ---------------------------------------------------------------------------
struct Obj630
{
    void FUN_00baf630(int param_2, void* param_3);   // 0x00baf630
};

void Obj630::FUN_00baf630(int param_2, void* param_3)
{
    char* self = (char*)this;
    RBTree* tree = (RBTree*)(self + 0x12c);
    void* it;
    int key = param_2;

    tree->find(&it, &key);
    if (it != (void*)(self + 0x130))
    {
        FeedbackEvent* node = *(FeedbackEvent**)((char*)it + 0x14);
        if (node != 0)
        {
            node->FUN_00bb9b00(4, 0);
            if (param_3 != 0)
                ((FeedbackEvent*)param_3)->FUN_00bb9b90(node->FUN_00bb9b80());
        }
    }

    if (param_3 != 0)
    {
        FeedbackEvent* pe = (FeedbackEvent*)param_3;
        pe->FUN_00bb9b00(4, 1);
        pe->FUN_00a16a90(key);
        FeedbackEvent** slot = (FeedbackEvent**)tree->FUN_00dd85c0(&param_2);
        FeedbackEvent* old = *slot;
        if (pe != old)
        {
            pe->AddRef();
            *slot = pe;
            if (old != 0)
                old->Release();
        }
    }
    else
    {
        tree->FUN_00baa110(&param_2);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00baf700
// ---------------------------------------------------------------------------
void* __stdcall FUN_00baf700(void* param_1)
{
    void* key = ((Obj700*)param_1)->FUN_00c30e80();

    void* it;
    ((RBTree*)(void*)g_0156c61c)->find(&it, &key);
    if (it != (void*)g_0156c620)
        return *(void**)((char*)it + 0x14);

    PropertyManager* pm = (PropertyManager*)FUN_0067de30();
    FeedbackEvent** slot =
        (FeedbackEvent**)((RBTree*)(void*)g_0156c61c)->FUN_00dd85c0(&key);
    FeedbackEvent* old = *slot;
    if (old != 0)
    {
        *slot = 0;
        old->Release();
    }
    pm->p2c(key, (const char*)0x568de14, slot);

    FeedbackEvent** s2 =
        (FeedbackEvent**)((RBTree*)(void*)g_0156c61c)->FUN_00dd85c0(&key);
    return *s2;
}

// ---------------------------------------------------------------------------
// @ 0x00baf790
// ---------------------------------------------------------------------------
struct StarRef
{
    int GetCommContext(void);                   // 0x00ce6950
};

struct EmbassyMap
{
    int* operator[](const int* key);            // 0x00643a40
};

struct ObjC33
{
    int FUN_00c33cc0(void* a, int b);           // 0x00c33cc0
};

extern void __cdecl FUN_00ba7c20(void* a, int b);    // 0x00ba7c20
extern void* __cdecl FUN_00921580(void* node);       // 0x00921580  eastl::RBTreeIncrement
extern void  __cdecl FUN_00921880(void* a, void* b); // 0x00921880  eastl::RBTreeErase
extern void  __cdecl FUN_00f47380(void* p);          // 0x00f47380  operator delete

struct Obj790
{
    void FUN_00baf790(int param_2, void* param_3, int param_4);   // 0x00baf790
};

void Obj790::FUN_00baf790(int param_2, void* param_3, int param_4)
{
    char* self = (char*)this;
    int orig = param_2;

    param_2 = ((StarRef*)param_2)->GetCommContext();
    EmbassyMap* map = (EmbassyMap*)(self + 0x184);
    int* slot = map->operator[](&param_2);
    *slot = param_4;

    FUN_00ba7c20((void*)orig, param_4);
    param_2 = ((ObjC33*)param_3)->FUN_00c33cc0((void*)orig, param_4);

    if (param_2 != 0)
    {
        ((RBTree*)map)->find((void**)&param_4, &param_2);
        if (param_4 != (int)(self + 0x188))
        {
            *(int*)(self + 0x198) -= 1;
            FUN_00921580((void*)param_4);
            FUN_00921880((void*)param_4, self + 0x188);
            FUN_00f47380((void*)param_4);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00baf880
// ---------------------------------------------------------------------------
struct Range3
{
    char* begin;                                // +0x00
    char* end;                                  // +0x04
    char* cap;                                  // +0x08
};

struct VObjX
{
    virtual void x00(); virtual void x04(); virtual void x08();
    virtual void x0c(); virtual void x10(); virtual void x14();
    virtual VObjX* x18();                       // vtable[0x18]
    virtual int  x1c();                         // vtable[0x1c]
    virtual void x20(); virtual void x24(); virtual void x28(int a, int b);
    virtual void x2c(); virtual void x30(void* a, int b);
    virtual void x34(); virtual void x38(void* a, int b);
};

struct Obj224
{
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(Range3* r, int zero);
    virtual void s34(void* elem, void* out, int a, int b, int c, int d);
    virtual void s38(); virtual void s3c();
    virtual void s40(void* elem);
};

struct Obj880
{
    void FUN_00baf880(void);                    // 0x00baf880
};

void Obj880::FUN_00baf880(void)
{
    char* self = (char*)this;
    Obj224* c = *(Obj224**)(self + 0x224);
    Obj224* s = *(Obj224**)(self + 0x228);

    Range3 range;
    range.begin = 0;
    range.end = 0;
    range.cap = 0;

    void* elRef = 0;        // per-element refcounted object from the source range
    void* elOut = 0;        // per-element refcounted object from the target range
    void* bv0 = 0;          // eastl::vector<bool> data
    void* bv1 = 0;          // eastl::vector<bool> end
    void* bv2 = 0;          // eastl::vector<bool> capacity

    c->s30(&range, 0);
    int count = (int)((range.end - range.begin) / 0xc);
    for (int i = 0; i < count; i++)
    {
        elRef = 0;
        elOut = 0;
        c->s34(range.begin + i * 0xc, &elRef, 1, 3, 1, 0);
        if (elOut != 0)
        {
            void* dead = elOut;
            elOut = 0;
            ((VObjX*)dead)->x08();
        }
        s->s34(range.begin + i * 0xc, &elOut, 2, 4, 1, 0);

        VObjX* o1 = ((VObjX*)elRef)->x18();
        int n = o1->x1c();
        int have = (int)((char*)bv1 - (char*)bv0);
        if (n > have)
        {
            int old = have;
            bv1 = (char*)bv1 + (n - have);
            bv0 = bv0;
            (void)old;
        }
        else
        {
            memcpy((char*)bv0 + have, bv1, 0);
        }

        o1->x28(0, 0);
        o1->x30(bv0, n);
        ((VObjX*)elRef)->x24();

        VObjX* o2 = ((VObjX*)elOut)->x18();
        o2->x28(0, 0);
        o2->x38(bv0, n);
        ((VObjX*)elOut)->x24();

        c->s40(range.begin + i * 0xc);

        if (elOut != 0)
            ((VObjX*)elOut)->x08();
        if (elRef != 0)
            ((VObjX*)elRef)->x08();

        (void)o1;
        (void)o2;
        (void)bv2;
    }

    s->s24();
    c->s24();

    c->s30(&range, 0);
    if (bv0 != 0 && *(int*)((char*)bv0 - 4) != 0)
        FUN_00f47380(bv0);
    if (bv1 != 0 && *(int*)((char*)bv1 - 4) != 0)
        FUN_00f47380(bv1);
}
