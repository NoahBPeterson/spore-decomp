// src/game/SPGonzago/SPGameBehaviorManager.cpp -- migrated from slice(s) s00b0d2a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameBehaviorManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl op_del_array(void* p);
extern "C" void* __cdecl FUN_00b0d0d0(void* dst, void* src, void* param);
#include <intrin.h>

// ---- items of slice s00b0d2a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
extern "C" void  __cdecl op_del_array(void* p);
struct ObjVec {                             // +0 begin, +4 end, +8 capacity
    void** mpBegin;
    void** mpEnd;
    void** mpCap;

    void InsertN(void* at, u32 count, void** val);          // 0x00b0d710
    ObjVec* AssignVec(ObjVec* other);                       // 0x00b0ddd0
    void* EraseRange(void** first, void** last);            // 0x00b0dec0
};
struct VecGrowStub {
    void Assign(void** a, void** b);                    // 0x00afb1a0
    void* Realloc(u32 n, void** a, void** b);           // 0x00b0d2f0
    void GrowOne(void** at, void** val);                // 0x00b0df20
};
extern "C" void* __cdecl FUN_00b0d0d0(void* dst, void* src, void* param);
extern "C" void  __cdecl FUN_00dc6730(void* a, void* b, void* c, void* d, void* e = 0);
// ---- items of slice s00b0d2a0 end

// @ 0x00b0ddd0
ObjVec* ObjVec::AssignVec(ObjVec* other)
{
    ObjVec* self = this;

    if (other == self)
        return self;

    void** srcBegin = other->mpBegin;
    void** srcEnd   = other->mpEnd;
    u32 n = (u32)(srcEnd - srcBegin);

    if ((u32)(self->mpCap - self->mpBegin) < n) {
        void* buf = ((VecGrowStub*)self)->Realloc(n, srcBegin, srcEnd);
        ((VecGrowStub*)self)->Assign(self->mpBegin, self->mpEnd);
        if (self->mpBegin != 0 && *(u32*)((char*)self->mpBegin - 4) != 0)
            op_del_array(self->mpBegin);
        self->mpCap   = (void**)((char*)buf + n * 4);
        self->mpEnd   = (void**)((char*)buf + n * 4);
        self->mpBegin = (void**)buf;
        return self;
    }

    u32 have = (u32)(self->mpEnd - self->mpBegin);
    if (have < n) {
        FUN_00b0d0d0(srcBegin, (char*)srcBegin + have * 4, self->mpBegin);
        FUN_00dc6730(&other, (char*)srcBegin + (u32)(self->mpEnd - self->mpBegin) * 4,
                     other->mpEnd, self->mpEnd, other);
        self->mpEnd = (void**)((char*)self->mpBegin + n * 4);
        return self;
    }

    void* res = FUN_00b0d0d0(srcBegin, srcEnd, self->mpBegin);
    ((VecGrowStub*)self)->Assign((void**)res, self->mpEnd);
    self->mpEnd = (void**)((char*)self->mpBegin + n * 4);
    return self;
}
