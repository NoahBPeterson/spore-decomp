// Slice s00d67140 -- FIGHT module (tribe fight group + fight action helpers).
// Reconstructed from disassembly.  Only intrinsic/primitive types are used so
// that the file is self-contained; every modeled field carries a name.

typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;
typedef int            I32;

// ---------------------------------------------------------------------------
// Shared virtual-dispatch view.  The objects in this module are unrelated, but
// the vtable slots that are actually *called* live at disjoint offsets, so a
// single view class with 64 slots can be used for all of them.
// ---------------------------------------------------------------------------
struct VT {
    virtual void  q00();
    virtual void  q01();                  // +0x04
    virtual void* q02();                  // +0x08
    virtual void* q03(int id);            // +0x0c
    virtual void  q04();
    virtual void  q05();
    virtual void  q06();
    virtual void  q07();
    virtual void* q08();                  // +0x20
    virtual void  q09();
    virtual void  q10();
    virtual void* q11();                  // +0x2c
    virtual void  q12();
    virtual void  q13();
    virtual void  q14();
    virtual void  q15();
    virtual void  q16();
    virtual void  q17();
    virtual void  q18();
    virtual void  q19();
    virtual void  q20();
    virtual void  q21();
    virtual bool  q22();                  // +0x58
    virtual void* q23(int id);            // +0x5c
    virtual void  q24();
    virtual void  q25();                  // +0x64
    virtual void  q26();
    virtual void  q27();
    virtual void  q28();
    virtual float q29();                  // +0x74
    virtual void  q30();
    virtual void  q31();
    virtual void  q32();
    virtual void  q33(void* a, int b, int c);   // +0x84
    virtual void  q34();
    virtual void  q35();
    virtual void  q36();
    virtual void  q37();
    virtual void  q38();
    virtual void  q39();
    virtual void  q40();
    virtual void  q41();
    virtual void  q42();
    virtual void  q43();
    virtual void  q44();
    virtual void  q45();
    virtual void  q46();
    virtual void  q47();                  // +0xbc
    virtual void  q48();                  // +0xc0
    virtual void  q49();
    virtual void  q50();
    virtual void  q51();
    virtual void  q52();
    virtual void  q53();
    virtual void  q54();
    virtual void  q55();
    virtual void  q56();
    virtual void  q57();
    virtual void  q58();
    virtual void  q59();                  // +0xec
    virtual void  q60();
    virtual void  q61();
    virtual bool  q62();                  // +0xf8
    virtual void  q63();
};

// ---------------------------------------------------------------------------
// Slot storage: 0x18 byte records made of a 4 byte flag word plus a 0x14 byte
// payload.  The low 30 bits of the flag word index a free list; the two high
// bits are "in use" markers.
// ---------------------------------------------------------------------------
struct SlotPayload {
    U32   mNounID;    // +0x00
    U32   mType;      // +0x04
    U32   mToken;     // +0x08
    U32   mTimerBits; // +0x0c  (float timer stored as its bit pattern)
    U32   mCount;     // +0x10
};

struct Slot {
    U32         mFlags;     // +0x00
    SlotPayload mPayload;   // +0x04
    // sizeof == 0x18
};

struct SlotPool {
    Slot* mpBegin;          // +0x00
    Slot* mpEnd;            // +0x04
    Slot* mpCapacity;       // +0x08
    U32   mPad0C;           // +0x0c
    U32   mPad10;           // +0x10
    U32   mMinFreeIndex;    // +0x14
    U32   mFreeListHead;    // +0x18

    Slot* begin()  { return mpBegin; }
    Slot* end()    { return mpEnd; }
    U32   count()  { return (U32)(mpEnd - mpBegin); }

    void  reserve(U32 newCapacity);
    void  insert_impl(Slot* position, Slot* value);
    U32   alloc(const SlotPayload* value);
};

extern SlotPool gTribeFightSlotsPool;

// ---------------------------------------------------------------------------
// Tree/order container header (slot at +0x00, links at +0x04/+0x08, root at
// +0x0c, size at +0x14).
// ---------------------------------------------------------------------------
struct TreeObject {
    U32   mUnk00;      // +0x00
    void* mLeft;       // +0x04
    void* mRight;      // +0x08
    void* mRoot;       // +0x0c
    U8    mByte10;     // +0x10
    U8    mPad11[3];
    U32   mCount;      // +0x14
};

struct Stimuli {
    void  Play(int a, int b);
    void  ClearAll(int a, int b);
};

struct B4CObj;

struct FightAction {
    U32        mSlot;       // +0x00
    float      mF04;        // +0x04
    float      mF08;        // +0x08
    float      mF0C;        // +0x0c
    float      mF10;        // +0x10
    float      mF14;        // +0x14
    U32        mField18;    // +0x18
    float      mF1C;        // +0x1c
    void*      mpField20;   // +0x20
    U16        mW24;        // +0x24
    U8         mPad26[2];
    void*      mpCreature;  // +0x28
    U32        mField2C;    // +0x2c
    void*      mpField30;   // +0x30
    void*      mpField34;   // +0x34
    U32        mField38;    // +0x38
    U32        mField3C;    // +0x3c
    float      mF40;        // +0x40
    U8         mByte44;     // +0x44
    U8         mPad45[3];
    void*      mpField48;   // +0x48
    U16        mW4C;        // +0x4c
    U8         mByte4E;     // +0x4e
    U8         mByte4F;     // +0x4f
    float      mF50;        // +0x50
    float      mF54;        // +0x54
    float      mF58;        // +0x58
    float      mF5C;        // +0x5c
    U32        mField60;    // +0x60
    TreeObject mTree64;     // +0x64 (root at +0x70)
};

// A fight group hanging off B4CObj::mpGroup.
struct FightGroup {
    U32   mPad00[4];        // +0x00
    U32   mField10;         // +0x10
    U8    mPad14[0x1a4 - 0x14];
    U32   mSlot1A4;         // +0x1a4
    U8    mByte1A8;         // +0x1a8
    U8    mPad1A9[3];
    U32   mVec1AC[3];       // +0x1ac .. +0x1b4
    U8    mPad1B8[0x1d8 - 0x1b8];
    U32   mField1D8;        // +0x1d8
};

struct B4CObj {
    U32       mPad00[2];        // +0x00
    Stimuli   mStimuli;         // +0x08
    U8        mPad0C[0x1d8 - 0x0c];
    U32       mField1D8;        // +0x1d8
    U8        mPad1DC[0x600 - 0x1dc];
    FightGroup* mpGroup;        // +0x600
};

struct Combatant : VT { };      // embedded combatant view (+0x5a8)

struct SubSys : VT { };         // creature subsystem (+0xc0)

struct Creature : VT {
    U8      mPad04[0xc0 - 0x04];
    SubSys  mSubSys;            // +0xc0
    U8      mPadC4[0x5a8 - 0xc4];
    Combatant mCombatant;       // +0x5a8
    U8      mPad5AC[0x5b4 - 0x5ac];
    TreeObject mTree;           // +0x5b4
    U8      mPad5CC[0xb4c - 0x5cc];
    B4CObj* mpB4C;              // +0xb4c
    U8      mPadB50[0xb58 - 0xb50];
    U32     mFlagsB58;          // +0xb58
    U8      mPadB5C[2];
    U8      mFlagB5E;           // +0xb5e
    U8      mPadB5F[0xe8c - 0xb5f];
    U32     mFieldE8C;          // +0xe8c
    U32     mFieldE90;          // +0xe90
    float   mFieldE94;          // +0xe94
    void*   mpFieldE98;         // +0xe98
    void*   mpFieldE9C;         // +0xe9c
    U8      mPadEA0[0x1124 - 0xea0];
    U8      mField1124[0x10];   // +0x1124

    void  ResetFightAction();   // helper used by several callees
};

// ---------------------------------------------------------------------------
// Small helper views for objects that are only touched at a handful of offsets.
// ---------------------------------------------------------------------------
struct TribeModeStrategy {
    U8    mPad00[0x1c8];
    void* mpManager;        // +0x1c8
};

struct HasB4C {
    U8       mPad00[0xb4c];
    B4CObj*  mpB4C;         // +0xb4c
};

struct EntryWithPtr {       // a neighbour entry: pointer at +0x08
    void* mpField00;
    void* mpField08;
};

struct Arg7Object {         // activation context object
    void* mpField04;
    void* mpField08;
};

struct FieldHolder {        // object owning a dword at +0x3f8
    U8  mPad00[0x3f8];
    U32 mField3F8;
};

// ---------------------------------------------------------------------------
// Callee declarations.  ``FnXXXX`` structs model member-like (thiscall) calls.
// ---------------------------------------------------------------------------
void* operator_new(U32 size, const char* category, int a, int b, const char* file, int line);
void  operator_delete_array(void* p);
void* __cdecl memcpy(void* dst, const void* src, U32 n);

extern "C" {
    void* FUN_00d661a0(void* first, void* last, void* dest);
    void* FUN_00d66210(void* first, void* last, void* destEnd);
    void  FUN_00d66250(void* out, void* obj, float value);
    void  FUN_00d66e10(Creature* creature, U32 slot);
    void  FUN_00b3d480(void* p);
    void* FUN_00bc9b00();
    void* FUN_00bca620(void* self, int key, void* fn, void* pair);
    void* FUN_00bcb0b0(void* self, int key, U32 b, U32 c, const char* name);
    void* FUN_00c0c1a0(void* self);
    int   FUN_00d99470(void* p);
    void* FUN_00d99a10(void* p);
    void* FUN_00b41a40(void* out, void* collection, void* ctx);
    U32   FUN_00b5b800();
    int   FUN_008e7f80(void* self);
    void* SP_GetAnimalFromStimulus(void* s);
    void* SP_GetCreatureFromStimulus(void* s);
    void* SP_GetSpeciesProfile(void* creature);
    void* SP_cTribeModeStrategy_Instance();
    void* SP_cCreatureModeStrategy_Instance(int key, void* out);
    int   FUN_00d995c0();
    void* FUN_00d39360(void* self);
    char  SP_IsValidNeighbourEntry(void* self, void* entry);
}

// model the void(bool) helper that the tree uses
struct FnNukeTree { void __thiscall f(void* node); };
struct FnClearSlot { void __thiscall f(const void* src); };
struct FnMoveSlot  { void __thiscall f(const void* src); };
struct FnD66E70    { void* __thiscall f(Creature* creature); };
struct FnD670E0    { void __thiscall f(); };
struct FnC14750    { void __thiscall f(int a); };
struct FnC0EE60    { void* __thiscall f(); };
struct FnC0BA10    { void __thiscall f(); };
struct FnACA360    { void __thiscall f(); };
struct FnC19940    { void __thiscall f(int a); };
struct FnC232B0    { char __thiscall f(); };
struct FnC0C0E0    { char __thiscall f(); };
struct FnGetTarget { void* __thiscall f(); };
struct FnB41A40    { void __thiscall f(void* collection, void* ctx); };
struct FnIsValid   { char __thiscall f(void* entry); };
struct FnD66320    { SlotPayload* __thiscall f(); };
struct FnD39360    { void __thiscall f(); };
struct FnBC2180    { void __thiscall f(void* a); };
struct FnBCB430    { void __thiscall f(); };
struct FnBC9B50    { char __thiscall f(); };
struct FnBCB480    { void __thiscall f(void* a, void* b, int c, int d); };
struct FnBC97F0    { void __thiscall f(int a, int b, float c, void* d); };
struct FnSpotPlay   { void* __thiscall f(int a, int b); };
struct FnStealth    { void __thiscall f(int a, int b); };
struct FnSprint     { void __thiscall f(int a); };
struct FnInterrupt  { int __thiscall f(int id, int a, int b); };
struct FnPlay2      { void* __thiscall f(int a, int b); };
struct FnSetStealth2{ void __thiscall f(int a, int b); };

SlotPayload* FUN_00d66320(U32 slot);

SlotPayload* FUN_00d67660();
int FUN_00d678d0(FightAction* self, U8 param);
void __cdecl FUN_00d67300(Creature* c, int a2, int a3, int a4, int a5, FightAction* fa);
void __cdecl FUN_00d67410(Creature* c, int a2, int a3, int a4, int a5, FightAction* fa);

// ===========================================================================
// @ 0x00d67140
void SlotPool::reserve(U32 newCapacity)
{
    U32 current = (U32)(mpCapacity - mpBegin);
    if (newCapacity > current) {
        Slot* newBuffer = (newCapacity != 0)
            ? (Slot*)operator_new(
                  newCapacity * 0x18, "Simulator", 0, 0,
                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                  0xd1)
            : 0;
        FUN_00d661a0(mpBegin, mpEnd, newBuffer);
        if (mpBegin != 0) {
            operator_delete_array(mpBegin);
        }
        U32 moved = (U32)(mpEnd - mpBegin);
        mpBegin    = newBuffer;
        mpEnd      = newBuffer + moved;
        mpCapacity = newBuffer + newCapacity;
    }
}

// ===========================================================================
// @ 0x00d671f0
void SlotPool::insert_impl(Slot* position, Slot* value)
{
    if (mpEnd != mpCapacity) {
        if (position <= value && value < mpEnd) {
            value = value + 1;
        }
        if (mpEnd != 0) {
            ((FnClearSlot*)mpEnd)->f(mpEnd - 1);
        }
        FUN_00d66210(position, mpEnd - 1, mpEnd);
        ((FnMoveSlot*)position)->f(value);
        mpEnd = mpEnd + 1;
        return;
    }

    U32 newCapacity = (U32)(mpEnd - mpBegin);
    if (newCapacity == 0) {
        newCapacity = 1;
    } else {
        newCapacity = newCapacity * 2;
        if (newCapacity == 0) {
            goto skip_alloc;
        }
    }
    {
        Slot* newBuffer = (Slot*)operator_new(
            newCapacity * 0x18, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        void* newEnd = FUN_00d661a0(mpBegin, position, newBuffer);
        if (newEnd != 0) {
            ((FnClearSlot*)newEnd)->f(value);
        }
        newEnd = FUN_00d661a0(position, mpEnd, (char*)newEnd + 0x18);
        if (mpBegin != 0) {
            operator_delete_array(mpBegin);
        }
        mpEnd      = (Slot*)newEnd;
        mpBegin    = newBuffer;
        mpCapacity = newBuffer + newCapacity;
        return;
    }
skip_alloc:
    {
        void* newEnd = FUN_00d661a0(mpBegin, position, 0);
        if (newEnd != 0) {
            ((FnClearSlot*)newEnd)->f(value);
        }
        newEnd = FUN_00d661a0(position, mpEnd, (char*)newEnd + 0x18);
        if (mpBegin != 0) {
            operator_delete_array(mpBegin);
        }
        mpEnd      = (Slot*)newEnd;
        mpBegin    = 0;
        mpCapacity = (Slot*)0 + newCapacity;
    }
}

// ===========================================================================
// @ 0x00d67300
void __cdecl FUN_00d67300(Creature* c, int a2, int a3, int a4, int a5, FightAction* fa)
{
    (void)a2; (void)a3; (void)a4; (void)a5;

    if (c->mFlagB5E == 0) {
        c->mpB4C->mStimuli.ClearAll(0x10, 0);
        c->mSubSys.q59();
        if (((c->mFlagsB58 >> 9) & 1) == 0) {
            c->q33(0, 0, 0);
        }
    }

    ((FnD670E0*)fa)->f();

    c->mFieldE8C = 0xffffffff;
    c->mFieldE90 = 0xffffffff;
    c->mFieldE94 = 0.0f;

    {
        void* src = c->mpFieldE9C;
        void* dst = c->mpFieldE98;
        memcpy(dst, src, (U32)((int)src - (int)src));
        c->mpFieldE9C = (void*)((int)c->mpFieldE9C + (((int)src - (int)dst) >> 2) * -4);
    }

    ((FnC14750*)c)->f(0);
    c->mFlagsB58 &= 0xffffdfff;

    ((FnNukeTree*)&c->mTree)->f(c->mTree.mRoot);
    c->mTree.mLeft   = (void*)&c->mTree.mLeft;
    c->mTree.mRight  = (void*)&c->mTree.mLeft;
    c->mTree.mRoot   = 0;
    c->mTree.mByte10 = 0;
    c->mTree.mCount  = 0;

    if (fa != 0) {
        ((FnNukeTree*)&fa->mTree64)->f(fa->mTree64.mRoot);
        void* p = fa->mpField20;
        if (p != 0) {
            ((VT*)p)->q48();
        }
    }
}

// ===========================================================================
// @ 0x00d67410
void __cdecl FUN_00d67410(Creature* c, int a2, int a3, int a4, int a5, FightAction* fa)
{
    (void)a2; (void)a3; (void)a4; (void)a5;

    ((FnSetStealth2*)c)->f(0, 0);
    if (c->mSubSys.q22()) {
        void* o = ((FnC0EE60*)c)->f();
        if (o != 0) {
            void* r = ((VT*)o)->q03(0);
            FUN_00b3d480(r);
            ((FnACA360*)r)->f();
        }
    }
    c->q33(0, 0, 0);
    c->mFlagsB58 &= 0xffffdfff;
    ((FnSprint*)c)->f(0);
    ((FnC0BA10*)c)->f();

    c->mFieldE8C = 0xffffffff;
    c->mFieldE90 = 0xffffffff;
    c->mFieldE94 = 0.0f;

    {
        void* src = c->mpFieldE9C;
        void* dst = c->mpFieldE98;
        memcpy(dst, src, (U32)((int)src - (int)src));
        c->mpFieldE9C = (void*)((int)c->mpFieldE9C + (((int)src - (int)dst) >> 2) * -4);
    }

    FUN_00d66e10(c, (U32)*(int*)&fa->mF08);

    TribeModeStrategy* strat = (TribeModeStrategy*)SP_cTribeModeStrategy_Instance();
    ((FnBC2180*)strat->mpManager)->f((void*)(int)fa->mF0C);
    fa->mF0C = 0.0f;

    if (fa->mpField34 != 0) {
        ((VT*)fa->mpField34)->q25();
    }
    if (fa->mpField30 != 0) {
        ((VT*)fa->mpField30)->q01();
    }
}

// ===========================================================================
// @ 0x00d67520
U32 SlotPool::alloc(const SlotPayload* value)
{
    // The low 30 bits of the slot header either index the free list head or, when the header is
    // the sentinel 0x3fffffff, mark that the pool must grow instead of recycling a freed slot.
    U32 index = mFreeListHead;
    Slot* result;

    if (index != 0x3fffffff) {
        result = &mpBegin[index];
        mFreeListHead = result->mFlags & 0x3fffffff;
        result->mFlags &= 0x7fffffff;
        result->mPayload = *value;
    } else {
        index = (U32)(mpEnd - mpBegin);
        if (mpEnd < mpCapacity) {
            if (mpEnd != 0) {
                mpEnd->mFlags = 0x80000000;
            }
            mpEnd = mpEnd + 1;
        } else {
            Slot tmp;
            tmp.mFlags = 0x80000000;
            insert_impl(mpEnd, &tmp);
        }
        if (index != 0) {
            Slot* prev = &mpBegin[index - 1];
            prev->mFlags &= 0xbfffffff;
        }
        result = &mpBegin[index];
        result->mFlags |= 0x40000000;
        result->mFlags &= 0x7fffffff;
        result->mPayload = *value;
    }

    if (mMinFreeIndex > index) {
        mMinFreeIndex = index;
    }
    return index;
}

// ===========================================================================
// @ 0x00d67660
SlotPayload* FUN_00d67660()
{
    SlotPayload value;
    value.mNounID    = 0;
    value.mType      = 0;
    value.mToken     = 0;
    value.mTimerBits = 0;
    value.mCount     = 0;

    U32 index = gTribeFightSlotsPool.alloc(&value);
    U32 token = index | 0x40000000;
    U32 i = token & 0xbfffffff;

    SlotPayload* result;
    if (i < gTribeFightSlotsPool.count() &&
        (int)gTribeFightSlotsPool.mpBegin[i].mFlags >= 0) {
        result = &gTribeFightSlotsPool.mpBegin[i].mPayload;
    } else {
        result = 0;
    }

    result->mToken = token;
    result->mCount = 0;
    result->mNounID = 0;
    result->mType = 0x1f;
    *(float*)&result->mTimerBits = 1.0f;
    return result;
}

struct FindKey {
    void* mpObject;
    void* mpCreature;
};

// ===========================================================================
// @ 0x00d67700
void FindGroup(Creature* creature)
{
    void* manager = FUN_00bc9b00();
    void* objA = ((FnC0EE60*)creature)->f();

    FindKey key;
    key.mpObject = objA;
    key.mpCreature = creature;

    void* group = FUN_00bca620(manager, 0x60995fc, (void*)&FUN_00d995c0, &key);
    if (group != 0) {
        if (((FnBC9B50*)group)->f() == 0) {
            return;
        }
    }

    group = FUN_00bcb0b0(manager, 0x60995fc, 0x20, 0xce9f6639, "Fight");

    SlotPayload* slot = FUN_00d67660();
    ((FightGroup*)group)->mSlot1A4 = slot->mToken;
    ((FightGroup*)group)->mByte1A8 = 0;

    void* objB = ((VT*)objA)->q02();
    U32* vec = (U32*)((VT*)objB)->q11();
    ((FightGroup*)group)->mVec1AC[0] = vec[0];
    ((FightGroup*)group)->mVec1AC[1] = vec[1];
    ((FightGroup*)group)->mVec1AC[2] = vec[2];

    float f = creature->mSubSys.q29();
    void* r = ((VT*)objA)->q02();
    FUN_00d66250(slot, r, f);

    ((FnBCB480*)creature->mpB4C)->f(group, creature, 0, 0);
}

// ===========================================================================
// @ 0x00d678d0
int FUN_00d678d0(FightAction* self, U8 param)
{
    Creature* creature = (Creature*)self->mpCreature;
    ((FnD670E0*)self)->f();
    FindGroup(creature);

    FightGroup* group = creature->mpB4C->mpGroup;
    if (group == 0) {
        return 0;
    }

    U32 v = self->mField2C;
    if (v < group->mField10 && group->mByte1A8 != 0) {
        SlotPayload* sp = FUN_00d66320(group->mSlot1A4);
        param = (U8)(param | (sp->mNounID < (1u << ((v - 1) & 0x1f))));
    }

    if (group->mField10 > v && param == 0) {
        return 0;
    }

    {
        Creature* target = (Creature*)((FnGetTarget*)creature)->f();

        self->mF10 = self->mF14;
        self->mField18 = 1;
        self->mF04 = 0.0f;
        self->mF08 = 0.0f;
        self->mF0C = 0.0f;

        U8 ch = 0;
        if (target != 0 && ((target->mFlagsB58 >> 9) & 1) != 0) {
            ch = 1;
        }
        group->mByte1A8 = ch;

        if (self->mpField48 != 0 &&
            group->mField10 <= ((FieldHolder*)self->mpField48)->mField3F8) {
            self->mByte4E = 1;
        }

        if (ch != 0) {
            U32 local[3];
            local[0] = 0;
            local[1] = 0;
            local[2] = 1;
            void* strat = SP_cCreatureModeStrategy_Instance(0xd3353637, local);
            ((FnD39360*)strat)->f();
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00d679e0
char FIGHT_Activate(Creature* c, int a2, int a3, int a4, U32 bits, FightAction* fa, void* arg7)
{
    (void)a2; (void)a3; (void)a4;

    if (fa != 0) {
        ((FnD66E70*)fa)->f(c);
    }
    if ((bits & 0x20) != 0) {
        fa->mByte4F = 1;
    }

    void* combatant = 0;
    void* foundCreature = 0;
    int   haveFound = 0;

    if (((c->mFlagsB58 >> 8) & 1) != 0) {
        void* played = ((FnSpotPlay*)&c->mpB4C->mStimuli)->f(0x10, 0);
        if (played != 0) {
            if (FUN_00b5b800() != 0x1654c10) {
                void* animal = SP_GetAnimalFromStimulus(played);
                if (animal != 0 && ((Creature*)animal)->mFlagB5E == 0) {
                    combatant = (void*)&((Creature*)animal)->mCombatant;
                    foundCreature = animal;
                    haveFound = 1;
                }
            } else {
                void* y = FUN_00d99a10(played);
                if (y != 0 && FUN_008e7f80(y) != 2) {
                    combatant = y;
                    foundCreature = SP_GetCreatureFromStimulus(y);
                    haveFound = 1;
                }
            }
        }
    }

    if (haveFound) {
        if (foundCreature != 0 && FUN_00d99470(foundCreature) == 0) {
            return 0;
        }
    } else {
        void* esi = 0;
        if (arg7 != 0) {
            void* q = ((Arg7Object*)arg7)->mpField08;
            combatant = ((Arg7Object*)arg7)->mpField04;
            if (q != 0) {
                esi = ((VT*)q)->q03(0x1186577);
            }
        } else {
            combatant = 0;
        }

        void* old = fa->mpField20;
        if (esi != old) {
            if (esi != 0) {
                ((VT*)esi)->q47();
            }
            fa->mpField20 = esi;
            if (old != 0) {
                ((VT*)old)->q48();
            }
        }

        if (combatant == 0) {
            return 0;
        }
        {
            void* x = ((VT*)combatant)->q23(0xce9f6639);
            if (x != 0 && FUN_00d99470(x) == 0) {
                return 0;
            }
        }
    }

    c->q33(combatant, 1, 0);

    if (((bits >> 2) & 1) != 0 && ((bits >> 4) & 1) == 0) {
        ((FnInterrupt*)c)->f(0x2481df9, -1, 0);

        U32 local[3];
        local[0] = 0;
        local[1] = 0;
        local[2] = 0;
        ((FnB41A40*)local)->f(c->mField1124, fa);

        void** p = (void**)local[0];
        void** e = (void**)local[1];
        for (;;) {
            if (p == e) {
                break;
            }
            void* entry = *p;
            void* obj = ((EntryWithPtr*)entry)->mpField08;
            if (obj != 0 && ((VT*)obj)->q08() == (void*)0x18eb45e) {
                void* sp1 = SP_GetSpeciesProfile(obj);
                void* sp2 = SP_GetSpeciesProfile(c);
                if (sp1 == sp2) {
                    void* r = ((VT*)combatant)->q03(0);
                    B4CObj* stim = ((HasB4C*)obj)->mpB4C;
                    ((FnBC97F0*)&stim->mStimuli)->f(0x800000, 0, 10.0f, r);
                }
            }
            for (;;) {
                p++;
                if (p == e) {
                    goto loop_done;
                }
                if (((FnIsValid*)(local + 2))->f(*p)) {
                    break;
                }
            }
        }
    loop_done: ;
    } else {
        if (!c->mSubSys.q62()) {
            ((FnInterrupt*)c)->f(0x39e477b, -1, 0);
        } else {
            ((FnC14750*)c)->f(0);
        }
    }

    U8 flag = 0;
    if (c->mpB4C->mField1D8 != 0x2d852e6) {
        void* played = ((FnPlay2*)&c->mpB4C->mStimuli)->f(0x400, 0);
        if (played != 0) {
            if (!((FnC0C0E0*)c)->f()) {
                fa->mField38 = (U32)((FnInterrupt*)c)->f(0x35ee23c, -1, 0);
            }
            flag = 1;
        }
    }

    fa->mF58 = 0.0f;

    U8 arg = (flag != 0 || ((c->mFlagsB58 >> 8) & 1) != 0) ? 1 : 0;
    FUN_00d678d0(fa, arg);

    fa->mByte44 = 1;
    c->mSubSys.q59();
    c->mFlagsB58 |= 0x2000;
    ((FnC19940*)c)->f(0);

    if (combatant != 0) {
        void* x = ((VT*)combatant)->q23(0x4f176642);
        if (x != 0 && ((FnC232B0*)x)->f()) {
            void* r = ((VT*)c)->q03(0xee3f516e);
            B4CObj* stim = ((HasB4C*)x)->mpB4C;
            ((FnBC97F0*)&stim->mStimuli)->f(0, 0x80, 10.0f, r);
        }
    }
    return 1;
}