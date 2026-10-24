// Spore retail 00ac0180..00ac129e -- cInteractionTarget / cAnimalCargoInfo
// family: constructors, destructors, slot-vector helpers, distance comparators,
// the cargo-item factory and the property-list serializers.
// Every field touched is named in one of the structs below; no raw-offset
// pointer arithmetic is used.
// Compile: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast

typedef unsigned int  u32;
typedef unsigned char u8;

typedef float* (__fastcall* GetVecFn)(void*);
typedef int  (__fastcall* VFnI)(void*);
typedef void* (__fastcall* VFnP)(void*);

// ---------------------------------------------------------------------------
// Imports (names are irrelevant; relocations are masked on both sides).
// ---------------------------------------------------------------------------
extern "C" {
    void  __cdecl FUN_00401090(void*);              // 0x401090 GetSetting9
    void* __cdecl FUN_004dff50(void*);              // 0x4dff50 load resource key
    void  __cdecl FUN_004cea40(void*, int, void*);  // 0x4cea40 vector insert
    void* __cdecl SP_ObjectTemplateDB();            // 0x67cb40 SP::ObjectTemplateDB
    void* __cdecl operator_new(u32, const char*, int, int, int, int); // 0xf473a0
    void  __cdecl operator_delete_array(void*);     // 0xf47380
    void* __cdecl FUN_010212a0();                   // 0x10212a0 GetActivePlanetRecord
}

void* __cdecl SP_NounManager();                     // 0xb3d300

// ---------------------------------------------------------------------------
// Image constants (named by address).
// ---------------------------------------------------------------------------
#define VTBL_01459be8  ((void*)0x1459be8)
#define VTBL_01459c04  ((void*)0x1459c04)
#define VTBL_01459c20  ((void*)0x1459c20)
#define VTBL_01459c30  ((void*)0x1459c30)
#define VTBL_01459c6c  ((void*)0x1459c6c)
#define VTBL_01459c90  ((void*)0x1459c90)
#define VTBL_01459c98  ((void*)0x1459c98)

#define VBASE_01459be5 ((void*)0x1459be5)   // "Interaction History:\n"
#define VBASE_01459bd0 ((void*)0x1459bd0)

#define G_013eb960  (*(float*)0x13eb960)    // +0.01
#define G_0140ced4  (*(float*)0x140ced4)    // -0.01
#define G_01459c48  (*(float*)0x1459c48)    // +1.5258789e-05
#define G_013f89b8  (*(float*)0x13f89b8)    // -1.5258789e-05
#define G_1459c44   (*(float*)0x1459c44)    // FLT_MAX

#define STR_1459d0c ((const char*)0x1459d0c) // "Simulator/cAnimalCargoInfo"
#define STR_1565ad8 ((const char*)0x1565ad8) // serialized field name

// Static int3 tables consulted by the item-state selector (copied verbatim).
struct Int3Table { int x, y, z; };
#define TBL_1565a78 (*(Int3Table*)0x1565a78)
#define TBL_1565a84 (*(Int3Table*)0x1565a84)
#define TBL_1565a90 (*(Int3Table*)0x1565a90)

// ---------------------------------------------------------------------------
// AutoRefCount-like item base: vftable + reference count at +0x08.
// ---------------------------------------------------------------------------
struct RefObj {
    void* mpVftable;                                // +0x00
    u8    mPad04[0x04];                             // +0x04
    void* mpVftable2;                               // +0x08
};

// ---------------------------------------------------------------------------
// Deque used inside a slot-vector entry.
// ---------------------------------------------------------------------------
struct InnerDeque {
    int* mpBlocks;                                  // +0x00
    u8   mPad04[0x08];                              // +0x04
    int* mpBegin;                                   // +0x0c
    int* mpEnd;                                     // +0x10
    int* mpCapacity;                                // +0x14
    int  mnCursor;                                  // +0x18
};

struct SlotEntry {
    void*      mpItem;                              // +0x00
    u8         mPad04[0x08];                        // +0x04
    InnerDeque mInner;                              // +0x0c
};

// ---------------------------------------------------------------------------
// The slot vector subobject shared by 00ac0180 / 00ac0450.
// ---------------------------------------------------------------------------
struct SlotDeque {
    u8   mPad00[0x18];                              // +0x00
    int* mpBegin;                                   // +0x18
    int* mpEnd;                                     // +0x1c
    int* mpCapacity;                                // +0x20
    int* mpBlockBase;                               // +0x24
};

// Receiver of 00ac0180 / 00ac0450 / 00ac0520 / 00ac0540.
struct EntityArg;

struct InterObj {
    void*     mpVftable;                            // +0x00
    u8        mPad04[0x30];                         // +0x04
    SlotDeque mDeque;                               // +0x34

    bool FUN_00ac0180(EntityArg* arg, int unused);  // 0xac0180
};

// Entity argument of 00ac0180: only the +0x6c flag is read.
struct EntityArg {
    u8  mPad00[0x6c];                               // +0x00
    int mf6c;                                       // +0x6c
};

// ---------------------------------------------------------------------------
// cAnimalCargoInfo (0x80 bytes).
// ---------------------------------------------------------------------------
struct SpeciesProfile {
    u8  mPad000[0x608];                             // +0x000
    int mf608;                                      // +0x608
    int mf60c;                                      // +0x60c
};

struct CargoItem {
    void*           mpVftable;                      // +0x00
    int             mnRefCount;                     // +0x04
    void*           mpHandlerVftable;               // +0x08
    void*           mpSerializableVftable;          // +0x0c
    int             mnItemCount;                    // +0x10
    int             mnItemType;                     // +0x14
    u8              mPad18[0x64];                   // +0x18
    SpeciesProfile* mpSpeciesProfile;               // +0x7c
};

// ---------------------------------------------------------------------------
// Small call-shape stubs (members default to __thiscall: this in ECX).
// ---------------------------------------------------------------------------
struct ThiscallStub {
    void Object_Cast(int* entity);                  // 0xac0570
    int  FUN_00ac05d0(int classId);                 // 0xac05d0
    int* FUN_00ac06c0(float* pos, float a, float b); // 0xac06c0
    int  FUN_00ac0730(void* a, void* b);            // 0xac0730
    int  FUN_00ac0810(void* a, void* b);            // 0xac0810
    void FUN_00ac0bb0(void** out);                  // 0xac0bb0
    void FUN_00ac0e50(float* out);                  // 0xac0e50
    bool FUN_00ac0f40(void* stream);                // 0xac0f40
    bool FUN_00ac0fd0(void* stream);                // 0xac0fd0
    int* FUN_00ac1060(int arg2, int arg3);          // 0xac1060
    void* FUN_00ac10a0(void* arg1);                 // 0xac10a0
    void FUN_00c870b0(void* src);                   // 0xc870b0 operator=
};

// eastl vector destructor (this in ECX, no stack arguments).
struct VecDtor {
    void dtor();                                    // 0xae6970
};

// Separate declaration of the cInteractionTarget ctor so call sites emit a
// real external call instead of inlining the body.
struct InteractionTargetCtor {
    InterObj* ctor();                               // 0xac03d0
};

// Generic slot-map helper at <object>+0x4c.
struct SlotMap {
    int* FUN_00ac0010(int** out);                   // 0xac0010
    void FUN_00c92bd0(int** out);                   // 0xc92bd0
};

// Base-class helper invoked with `this` in ECX and two stack arguments.
struct BaseStub {
    void FUN_00767700(int arg2, int arg3);          // 0x767700
};

// cInteractionTarget itself (vftable + AutoRefCount vector).
struct cInteractionTarget {
    void*  mpVftable;                               // +0x00
    void*  mpBegin;                                 // +0x04
    void*  mpEnd;                                   // +0x08
    void*  mpCapacity;                              // +0x0c

    cInteractionTarget* ctor();                     // 0xac03d0
    void   FUN_00ac0450();                          // 0xac0450
    void   FUN_00ac0520();                          // 0xac0520
    cInteractionTarget* FUN_00ac0540(char free);    // 0xac0540
};

// ===========================================================================
// 0x00ac0180 -- move/adjust the slot vector and register an interaction.
// ===========================================================================
// @ 0x00ac0180
bool InterObj::FUN_00ac0180(EntityArg* arg, int unused)
{
    (void)unused;
    if (arg->mf6c == 0) {
        ((void(__fastcall*)(void*))(*(void***)this)[0x34 / 4])(this);
        ((void(__fastcall*)(void*))(*(void***)this)[0x38 / 4])(this);
    }
    int count = ((int(__fastcall*)(void*))(*(void***)this)[0x38 / 4])(this);
    if (count > 0) {
        int*  at   = mDeque.mpBegin;
        int*  end  = mDeque.mpEnd;
        int*  base = mDeque.mpBlockBase;
        if (at == end) {
            base = base - 1;
            at   = (int*)(*base + 0x100);
        }
        int* item = *(int**)(at - 1);
        if (item != 0)
            ((void(__fastcall*)(void*))(*(void***)item)[0])(item);
        int* slot = (int*)this;
        int* dst = ((SlotMap*)((char*)item + 0x4c))->FUN_00ac0010(&slot);
        *dst = 1;
        if (item != 0)
            ((void(__fastcall*)(void*))(*(void***)item)[1])(item);
    }

    int* slot2 = (int*)this;
    int* dst2 = ((SlotMap*)((char*)arg + 0x4c))->FUN_00ac0010(&slot2);
    *dst2 = 0;

    int* entity = (int*)arg;
    ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);

    SlotDeque* dq = &mDeque;
    int** pos = (int**)dq->mpBegin;
    if ((int*)((char*)pos + 4) != dq->mpCapacity) {
        dq->mpBegin = (int*)((char*)pos + 4);
        if (pos != 0) {
            *pos = entity;
            ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);
            ((void(__fastcall*)(void*))(*(void***)entity)[1])(entity);
            return true;
        }
    } else {
        ((SlotMap*)dq)->FUN_00c92bd0(&slot2);
    }
    ((void(__fastcall*)(void*))(*(void***)entity)[1])(entity);
    return true;
}

// ===========================================================================
// 0x00ac0270 -- build an "Interaction History" string from a deque of slots.
// ===========================================================================
// @ 0x00ac0270
void __fastcall FUN_00ac0270(int self, void* str)
{
    extern void __cdecl ebg_string_assign(void*, const char*, const char*); // 0x454cb0
    ebg_string_assign(str, (const char*)VBASE_01459be5, (const char*)VBASE_01459bd0);
    int cur    = *(int*)(self + 0x20);
    int last   = *(int*)(self + 0x24);
    int capEnd = *(int*)(self + 0x2c);
    int limit  = *(int*)(self + 0x10);
    int n = 0;
    extern void __fastcall ebg_string_append(void*, int, int);   // 0x455d60
    extern void __fastcall ebg_string_push_back(void*, int);     // 0x5306c0
    while (cur != limit) {
        int e = cur;
        if (cur == last)
            e = *(int*)(capEnd - 4) + 0x100;
        ebg_string_append(str, *(int*)(e - 0x10), *(int*)(e - 0xc));
        ebg_string_push_back(str, 10);
        if (++n >= 4)
            break;
        if (cur == last) {
            last = *(int*)(capEnd - 4);
            capEnd -= 4;
            cur = last + 0x100;
        }
        cur -= 0x10;
    }
}

// ===========================================================================
// 0x00ac0340 -- Object::_virtual_dtor: erase a vtable-slot entry.
// ===========================================================================
// @ 0x00ac0340
void __fastcall Object_virtual_dtor(RefObj* self, int* entry)
{
    int n = (int)(((char*)self->mpVftable2 - (char*)self->mpVftable) >> 2);
    if (n <= 0)
        return;
    RefObj** slots = (RefObj**)self->mpVftable;
    int i = 0;
    while ((int*)slots[i] != entry) {
        if (++i >= n)
            return;
    }
    RefObj** begin = (RefObj**)self->mpVftable;
    int  cnt   = (int)(((char*)self->mpVftable2 - (char*)self->mpVftable) >> 2);
    RefObj* lastv = begin[cnt - 1];
    RefObj* oldv  = begin[i];
    if (lastv != oldv) {
        if (lastv != 0)
            ((void(__fastcall*)(void*))(*(void***)lastv)[0])(lastv);
        begin[i] = lastv;
        if (oldv != 0)
            ((void(__fastcall*)(void*))(*(void***)oldv)[1])(oldv);
    }
    self->mpVftable2 = (void*)((char*)self->mpVftable2 - 4);
    RefObj* tail = *(RefObj**)self->mpVftable2;
    if (tail != 0)
        ((void(__fastcall*)(void*))(*(void***)tail)[1])(tail);
}

// ===========================================================================
// 0x00ac03d0 -- cInteractionTarget::cInteractionTarget
// ===========================================================================
// @ 0x00ac03d0
cInteractionTarget* cInteractionTarget::ctor()
{
    mpVftable  = VTBL_01459be8;
    mpBegin    = 0;
    mpEnd      = 0;
    mpCapacity = 0;
    return this;
}

// ===========================================================================
// 0x00ac03f0 -- advance a slot-vector iterator to a matching element.
// ===========================================================================
// @ 0x00ac03f0
void __cdecl FUN_00ac03f0(int* out, int* begin, u32 slot, int endA, int endB, int* target)
{
    extern void SlotIter_inc(u32*);                 // 0xabe9b0 iterator::operator++
    while (endB + endA != (int)slot + (int)begin) {
        if (*(int*)(*(int*)(*begin + (slot >> 7) * 4) + 4 + (slot & 0x7f) * 8) == *target)
            break;
        SlotIter_inc(&slot);
    }
    *out = (int)begin;
    out[1] = (int)slot;
}

// ===========================================================================
// 0x00ac0450 -- release every element of a slot vector, then clear it.
// ===========================================================================
// @ 0x00ac0450
void cInteractionTarget::FUN_00ac0450()
{
    SlotEntry* base = (SlotEntry*)this;
    SlotEntry** beginp = (SlotEntry**)((char*)this + 4);
    SlotEntry** endp   = (SlotEntry**)((char*)this + 8);
    if (*beginp == *endp)
        return;
    SlotEntry* cur = 0;
    do {
        SlotEntry* elem = *(SlotEntry**)*beginp;
        SlotEntry* prev = cur;
        if (elem != cur) {
            if (elem != 0)
                ((void(__fastcall*)(void*))(*(void***)elem)[0])(elem);
            prev = elem;
            if (cur != 0)
                ((void(__fastcall*)(void*))(*(void***)cur)[1])(cur);
        }
        cur = prev;
        InnerDeque* dq = &cur->mInner;
        int n    = (int)((dq->mpEnd - dq->mpBegin) >> 2);
        int cap  = (int)dq->mpCapacity;
        int limit = (n << 7) + cap - 0x7f;
        int slot = dq->mnCursor;
        int use  = ((u32)slot < 0x3fffffff) ? slot : limit;
        struct Pair { int x, y; } it;
        FUN_00ac03f0(&it.x, (int*)dq, (u32)use, (int)dq, limit, (int*)&cur);
        if (limit + (int)dq != it.y + it.x)
            ((void(__fastcall*)(void*, int, int))(*(void***)cur)[0x50 / 4])(
                (void*)&it, it.x, it.y);
        cur = prev;
    } while (*beginp != *endp);
    if (cur != 0)
        ((void(__fastcall*)(void*))(*(void***)cur)[1])(cur);
}

// ===========================================================================
// 0x00ac0520 -- destroying destructor (tail-jmp to vector dtor).
// ===========================================================================
// @ 0x00ac0520
void cInteractionTarget::FUN_00ac0520()
{
    mpVftable = VTBL_01459be8;
    FUN_00ac0450();
    ((VecDtor*)((char*)this + 4))->dtor();
}

// ===========================================================================
// 0x00ac0540 -- scalar deleting destructor.
// ===========================================================================
// @ 0x00ac0540
cInteractionTarget* cInteractionTarget::FUN_00ac0540(char free)
{
    mpVftable = VTBL_01459be8;
    FUN_00ac0450();
    ((VecDtor*)((char*)this + 4))->dtor();
    if (free & 1)
        operator_delete_array(this);
    return this;
}

// ===========================================================================
// 0x00ac0570 -- Object::Cast: append an AddRef'd pointer to a slot vector.
// ===========================================================================
// @ 0x00ac0570
void ThiscallStub::Object_Cast(int* entity)
{
    int** self = (int**)this;
    if (entity != 0)
        ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);
    int* begin = self[2];
    int* end   = self[3];
    if (begin < end) {
        self[2] = (int*)((char*)begin + 4);
        if (begin != 0) {
            *begin = (int)entity;
            if (entity != 0)
                ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);
        }
    } else {
        extern void __cdecl FUN_00aea5d0(int, void*, int*); // 0xaea5d0 DoInsertPtr
        FUN_00aea5d0((int)begin, (void*)(self + 1), (int*)&entity);
    }
    if (entity != 0)
        ((void(__fastcall*)(void*))(*(void***)entity)[1])(entity);
}

// ===========================================================================
// 0x00ac05d0 -- interface query (dynamic cast by class id).
// ===========================================================================
// @ 0x00ac05d0
int ThiscallStub::FUN_00ac05d0(int classId)
{
    int self = (int)this;
    if (classId != (int)0xee3f516e) {
        if (classId == 0xe69e1e)
            return self;
        return self & (((classId != 0x102a041a) ? 1 : 0) - 1);
    }
    if (self != 0)
        return self + 0x18;
    return 0;
}

// ===========================================================================
// 0x00ac06c0 -- build an interaction-record object with position/scale.
// ===========================================================================
// @ 0x00ac06c0
int* ThiscallStub::FUN_00ac06c0(float* pos, float a, float b)
{
    int* self = (int*)this;
    ((InteractionTargetCtor*)self)->ctor();
    self[6] = (int)0x13f1ab0;
    self[7] = (int)0x13ec458;
    self[8] = 0;
    self[0] = (int)VTBL_01459c04;
    self[6] = (int)VTBL_01459c30;
    self[7] = (int)VTBL_01459c20;
    *(float*)(self + 9)  = pos[0];
    *(float*)(self + 10) = pos[1];
    *(float*)(self + 11) = pos[2];
    *(float*)(self + 0xc) = a;
    *(float*)(self + 0xd) = b;
    return self;
}

// ===========================================================================
// 0x00ac0730 -- distance comparator (point vs two entities), 0.01 tie band.
// ===========================================================================
// @ 0x00ac0730
int ThiscallStub::FUN_00ac0730(void* a, void* b)
{
    float* self = (float*)this;
    float* pa = ((GetVecFn)((*(void***)a)[0x2c / 4]))(a);
    float dxa = self[0] - pa[0];
    float dya = self[1] - pa[1];
    float dza = self[2] - pa[2];
    float da  = dya * dya + dxa * dxa + dza * dza;

    float* pb = ((GetVecFn)((*(void***)b)[0x2c / 4]))(b);
    float dxb = self[0] - pb[0];
    float dyb = self[1] - pb[1];
    float dzb = self[2] - pb[2];
    float db  = dzb * dzb + dyb * dyb + dxb * dxb;

    float diff = db - da;
    if (diff < G_013eb960 && G_0140ced4 < diff)
        return (int)(a < b);
    if (da < db)
        return 1;
    return 0;
}

// ===========================================================================
// 0x00ac0810 -- distance comparator using cCivData::GetCities positions.
// ===========================================================================
// @ 0x00ac0810
int ThiscallStub::FUN_00ac0810(void* a, void* b)
{
    float* self = (float*)this;
    extern float* __fastcall cCivData_GetCities(void*); // 0x5c65e0
    float* pa = cCivData_GetCities(a);
    float dxa = self[0] - pa[0];
    float dya = self[1] - pa[1];
    float dza = self[2] - pa[2];
    float da  = dya * dya + dxa * dxa + dza * dza;

    float* pb = cCivData_GetCities(b);
    float dxb = self[0] - pb[0];
    float dyb = self[1] - pb[1];
    float dzb = self[2] - pb[2];
    float db  = dzb * dzb + dyb * dyb + dxb * dxb;

    float diff = db - da;
    if (diff < G_01459c48 && G_013f89b8 < diff)
        return (int)(a < b);
    if (da < db)
        return 1;
    return 0;
}

// ===========================================================================
// 0x00ac08f0 -- nearest-element search over an array of float3 (12 bytes).
// ===========================================================================
// @ 0x00ac08f0
int __cdecl FUN_00ac08f0(int* range, float* query)
{
    float best = G_1459c44;
    float qx = query[0];
    float qy = query[1];
    float qz = query[2];
    int n = (range[1] - range[0]) / 12;
    int idx = 0;
    int bestIdx = -1;
    float* p = (float*)range[0];
    for (; idx < n - 3; idx += 4, p += 12) {
        float d0 = (p[0] - qx) * (p[0] - qx) + (p[1] - qy) * (p[1] - qy)
                 + (p[2] - qz) * (p[2] - qz);
        if (d0 < best) { best = d0; bestIdx = idx; }
        float d1 = (p[3] - qx) * (p[3] - qx) + (p[4] - qy) * (p[4] - qy)
                 + (p[5] - qz) * (p[5] - qz);
        if (d1 < best) { best = d1; bestIdx = idx + 1; }
        float d2 = (p[6] - qx) * (p[6] - qx) + (p[7] - qy) * (p[7] - qy)
                 + (p[8] - qz) * (p[8] - qz);
        if (d2 < best) { best = d2; bestIdx = idx + 2; }
        float d3 = (p[9] - qx) * (p[9] - qx) + (p[10] - qy) * (p[10] - qy)
                 + (p[11] - qz) * (p[11] - qz);
        if (d3 < best) { best = d3; bestIdx = idx + 3; }
    }
    for (; idx < n; idx += 1, p += 3) {
        float d = (p[0] - qx) * (p[0] - qx) + (p[1] - qy) * (p[1] - qy)
                + (p[2] - qz) * (p[2] - qz);
        if (d < best) { best = d; bestIdx = idx; }
    }
    return bestIdx;
}

// ===========================================================================
// 0x00ac0b00 -- cAnimalCargoInfo constructor (species variant).
// ===========================================================================
// @ 0x00ac0b00
CargoItem* __fastcall FUN_00ac0b00(CargoItem* self)
{
    extern void __fastcall cSPSpaceInventoryItem_ctor(void*); // 0xc87660
    cSPSpaceInventoryItem_ctor(self);
    self->mpVftable             = VTBL_01459c98;
    self->mpHandlerVftable      = VTBL_01459c90;
    self->mpSerializableVftable = VTBL_01459c6c;
    self->mpSpeciesProfile      = 0;
    return self;
}

// ===========================================================================
// 0x00ac0bb0 -- clone a cAnimalCargoInfo into an out-parameter slot.
// ===========================================================================
// @ 0x00ac0bb0
void ThiscallStub::FUN_00ac0bb0(void** out)
{
    CargoItem* src = (CargoItem*)this;
    CargoItem* p = (CargoItem*)operator_new(0x80, STR_1459d0c, 0, 0, 0, 0);
    CargoItem* result = 0;
    if (p != 0) {
        FUN_00ac0b00(p);
        ((ThiscallStub*)p)->FUN_00c870b0(src);
        if (p != src)
            p->mpSpeciesProfile = src->mpSpeciesProfile;
        ((void(__fastcall*)(void*))(*(void***)p)[1])(p);
        result = p;
    }
    *out = result;
}

// ===========================================================================
// 0x00ac0c30 -- query: is the species profile field 0x60c populated?
// ===========================================================================
// @ 0x00ac0c30
bool __fastcall FUN_00ac0c30(CargoItem* self)
{
    SpeciesProfile* obj = self->mpSpeciesProfile;
    if (obj != 0)
        return *(u32*)&obj->mf60c > 0u;
    return true;
}

// ===========================================================================
// 0x00ac0c50 -- query: is the species profile field 0x608 populated?
// ===========================================================================
// @ 0x00ac0c50
bool __fastcall FUN_00ac0c50(CargoItem* self)
{
    SpeciesProfile* obj = self->mpSpeciesProfile;
    if (obj != 0)
        return *(u32*)&obj->mf608 > 0u;
    return true;
}

// ===========================================================================
// 0x00ac0cb0 -- MakeInventoryItemFromSpecies
// ===========================================================================
// @ 0x00ac0cb0
void __fastcall FUN_00ac0cb0(int self, int speciesKey, int count, void** out)
{
    (void)self;
    int n = count;
    if (n < 1)
        n = 1;
    FUN_00401090((void*)speciesKey);
    extern void* __fastcall FUN_004df550_(void*);    // 0x4df550 GetProfile
    int profile = (int)FUN_004df550_((void*)speciesKey);
    if (profile == 0)
        return;
    CargoItem* p = (CargoItem*)operator_new(0x80, STR_1459d0c, 0, 0, 0, 0);
    if (p == 0)
        p = 0;
    else
        FUN_00ac0b00(p);
    ((void(__fastcall*)(void*))(*(void***)p)[1])(p);
    ((void(__fastcall*)(void*, int))(*(void***)p)[0x14 / 4])(p, profile + 0x504);
    p->mpSpeciesProfile = (SpeciesProfile*)profile;
    p->mnItemType  = ((count != 0) ? 5 : 0) + 1;
    extern void __fastcall cSPSpaceInventoryItem_SetPropertyList(void*, int); // 0xc877f0
    cSPSpaceInventoryItem_SetPropertyList(p, 0);
    p->mnItemCount = n;
    *out = p;
}

// ===========================================================================
// 0x00ac0d80 -- eastl::find over 12-byte ResourceMan::Key entries.
// ===========================================================================
// @ 0x00ac0d80
int* __cdecl FUN_00ac0d80(int* first, int* last, int* key)
{
    if (first != last) {
        do {
            if (first[0] == key[0] && first[1] == key[1] && first[2] == key[2])
                break;
            first += 3;
        } while (first != last);
    }
    return first;
}

// ===========================================================================
// 0x00ac0e50 -- choose one of three static int3 tables by item state.
// ===========================================================================
// @ 0x00ac0e50
void ThiscallStub::FUN_00ac0e50(float* out)
{
    CargoItem* self = (CargoItem*)this;
    int* o = (int*)out;
    int z = 0;
    o[0] = z; o[1] = z; o[2] = z;
    if (self->mnItemType == 6) {
        o[0] = TBL_1565a90.x; o[1] = TBL_1565a90.y; o[2] = TBL_1565a90.z;
        return;
    }
    SpeciesProfile* obj = self->mpSpeciesProfile;
    if (obj != 0) {
        bool populated = (*(u32*)&obj->mf608) > 0u;
        if (!populated) {
            o[0] = TBL_1565a84.x; o[1] = TBL_1565a84.y; o[2] = TBL_1565a84.z;
            return;
        }
    }
    o[0] = TBL_1565a78.x; o[1] = TBL_1565a78.y; o[2] = TBL_1565a78.z;
}

// ===========================================================================
// 0x00ac0ed0 -- is this item's key present in the active planet's key list?
// ===========================================================================
// @ 0x00ac0ed0
bool __fastcall FUN_00ac0ed0(int* self)
{
    bool result = false;
    void* rec = FUN_010212a0();
    if (rec != 0) {
        struct PlanetKeys { u8 mPad00[0xd0]; int* mpFirst; int* mpLast; };
        PlanetKeys* pk = (PlanetKeys*)rec;
        int* first = pk->mpFirst;
        int* last  = pk->mpLast;
        int* key   = (int*)((VFnI)((*(void***)self)[0x18 / 4]))(self);
        int* found = FUN_00ac0d80(first, last, key);
        result = (last != found);
    }
    return result;
}

// ===========================================================================
// 0x00ac0f40 -- write a uint32 then serialize the property list.
// ===========================================================================
// @ 0x00ac0f40
bool ThiscallStub::FUN_00ac0f40(void* stream)
{
    int self = (int)this;
    void* inner = ((VFnP)((*(void***)stream)[0x20 / 4]))(stream);
    u32   val   = 0x30fc270b;
    void* out   = ((VFnP)((*(void***)inner)[0x18 / 4]))(inner);
    extern bool __cdecl EA_IO_WriteUint32(void*, u32*, int, int); // 0x93aa70
    EA_IO_WriteUint32(out, &val, 1, 0);
    extern bool __fastcall FUN_00c87580(void*);      // 0xc87580
    bool flag = FUN_00c87580(stream);
    extern void __fastcall cVarListSerializer_ctor(void*, int, const char*, int); // 0x692f90
    extern bool __fastcall cVarListSerializer_Serialize(void*, void*);            // 0x692900
    char buf[0x9f0];
    cVarListSerializer_ctor(buf, self - 0xc, STR_1565ad8, 0x1a80d26);
    bool ser = cVarListSerializer_Serialize(buf, stream);
    return ser && flag;
}

// ===========================================================================
// 0x00ac0fd0 -- read a uint32, deserialize the property list, refresh profile.
// ===========================================================================
// @ 0x00ac0fd0
bool ThiscallStub::FUN_00ac0fd0(void* stream)
{
    int self = (int)this;
    void* inner = ((VFnP)((*(void***)stream)[0x20 / 4]))(stream);
    void* out   = ((VFnP)((*(void***)inner)[0x18 / 4]))(inner);
    u32   val   = 0;
    extern bool __cdecl EA_IO_ReadInt32(void*, u32*, int, int); // 0x93a780
    EA_IO_ReadInt32(out, &val, 1, 0);
    extern bool __fastcall FUN_00c879a0(void*);      // 0xc879a0
    bool flag = FUN_00c879a0(stream);
    extern void __fastcall cVarListSerializer_ctor(void*, int, const char*, int); // 0x692f90
    extern bool __fastcall cVarListSerializer_Serialize(void*, void*);            // 0x693e10
    char buf[0x9f0];
    cVarListSerializer_ctor(buf, self - 0xc, STR_1565ad8, 0x1a80d26);
    bool ser = cVarListSerializer_Serialize(buf, stream);
    bool ok = ser && flag;
    void* key = (void*)(self + 0x50);
    FUN_00401090(key);
    extern void* __cdecl FUN_004df550(void*);        // 0x4df550 GetProfile
    *(void**)(self + 0x70) = FUN_004df550(key);
    return ok;
}

// ===========================================================================
// 0x00ac1060 -- construct an inline-array object and init its base part.
// ===========================================================================
// @ 0x00ac1060
int* ThiscallStub::FUN_00ac1060(int arg2, int arg3)
{
    int* self = (int*)this;
    int* begin = self + 6;
    self[0] = (int)begin;
    self[1] = (int)begin;
    self[2] = (int)(begin + 0x100);
    self[5] = 0;
    ((BaseStub*)self)->FUN_00767700(arg2, arg3);
    return self;
}

// ===========================================================================
// 0x00ac10a0 -- create (or fetch) an object template from a setting key.
// ===========================================================================
// @ 0x00ac10a0
void* ThiscallStub::FUN_00ac10a0(void* arg1)
{
    (void)arg1;
    char local[0x400];
    void* vbegin = local;
    int   val = 0;
    void* vend = vbegin;
    FUN_004cea40(vbegin, 1, &val);
    void* res = FUN_004dff50(&vbegin);
    if (res == 0) {
        res = FUN_004dff50(&vbegin);
        if (res == 0) {
            if (vbegin != 0 && *((int*)vbegin - 1) != 0)
                operator_delete_array(vbegin);
            return 0;
        }
    }
    void* db = SP_ObjectTemplateDB();
    ((void(__fastcall*)(void*, int, int))(*(void***)db)[0x58 / 4])(
        db, *(int*)vbegin + 0x504, 1);
    void* out = *(void**)vbegin;
    if (*((int*)vbegin - 1) != 0)
        operator_delete_array(vbegin);
    (void)vend;
    return out;
}

// ===========================================================================
// 0x00ac1190 -- select a key by category, then create/fetch the template.
// ===========================================================================
// @ 0x00ac1190
void* __fastcall FUN_00ac1190(int self, u32 category)
{
    void* nm = (void*)SP_NounManager();
    extern void* __fastcall cTerrainEditor_GetCurrentTerrainSphere(void*); // 0xf67d90
    void* s = cTerrainEditor_GetCurrentTerrainSphere(nm);
    if (s != 0) {
        nm = (void*)SP_NounManager();
        s = cTerrainEditor_GetCurrentTerrainSphere(nm);
        extern void __fastcall FUN_00c75570(void*);  // 0xc75570
        FUN_00c75570(s);
    }

    u32 key;
    switch (category) {
    case 0: case 2: case 5: case 9: case 0xb: case 0xe: case 0x12:
        key = 0x9c45b1be; break;
    case 1: case 6: case 10: case 0xf: case 0x11:
        key = 0xd122cd50; break;
    case 3: case 4: case 7: case 0xc: case 0xd: case 0x10:
        key = 0x59ad24fd; break;
    default:
        key = 0;
        break;
    }

    FUN_00401090(0);
    char local[0x400];
    void* vbegin = local;
    int   z = 0;
    void* vend = vbegin;
    FUN_004cea40(vbegin, 1, &z);
    void* res = FUN_004dff50(&vbegin);
    int result;
    if (res != 0) {
        void* db = SP_ObjectTemplateDB();
        void* e = *(void**)vbegin;
        ((void(__fastcall*)(void*, int, int))(*(void***)db)[0x58 / 4])(
            db, (int)e + 0x504, 1);
        result = (int)e;
    } else {
        result = (int)((ThiscallStub*)self)->FUN_00ac10a0((void*)0xfc5a17bc);
    }
    if (vbegin != 0 && *((int*)vbegin - 1) != 0)
        operator_delete_array(vbegin);
    (void)key;
    (void)vend;
    return (void*)result;
}
