#include "types.h"

// ---------------------------------------------------------------------------
// SP::cTribeModeStrategy slice s00cdc8b0.
//
// All four functions in this slice are large (304..1413 bytes) transition-flow
// methods that read a global settings/property bag through a virtual slot,
// walk the game-data vector through five helper pointers, and perturb the
// strategy's transition-target vector (0x1c-stride records) with ownership
// transfers whose cleanup calls a non-null-checked operator delete. The field
// identities could not be recovered from the decompile within the round budget
// without resorting to unnamed raw-offset reads, so no function is emitted and
// all four rows live in partial.txt.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 0x00cdce40 -- append the strategy's transition targets: seed one record from
// the strategy itself, then one per object of the passed-in pointer vector.
// ---------------------------------------------------------------------------

struct CvgRec {                                        // 0x1c-byte timeline record
    uint32_t mX;                                       // +0x00
    uint32_t mY;                                       // +0x04
    uint32_t mZ;                                       // +0x08
    uint32_t mPad0c;                                   // +0x0c
    float    mF10;                                     // +0x10 (only set for list entries)
    void*    mHandle;                                  // +0x14
    uint32_t mId;                                      // +0x18
};
typedef char chk_cvgrec[(sizeof(CvgRec) == 0x1c) ? 1 : -1];

struct CvgVec {                                        // begin/end of the 0x1c-stride vector
    CvgRec* mpBegin;                                   // +0x00
    CvgRec* mpEnd;                                     // +0x04
    void InsertRange(CvgRec* first, CvgRec* last);     // 0x00cdb190
    void Append();                                     // 0x00cdb430
};

struct CvgObj {
    void**   mpVtbl;                                   // +0x000
    char     mPad04[0x300];                            // +0x004
    CvgVec   mTargets;                                 // +0x304
    char     mPad30c[0x814];                           // +0x30c
    uint32_t mB20;                                     // +0xb20
    char     mPadB24[0x14];                            // +0xb24
    uint32_t mB38;                                     // +0xb38
    uint32_t mB3c;                                     // +0xb3c
    uint32_t mB40;                                     // +0xb40
};

struct PtrVec {
    void** mpBegin;                                    // +0x00
    void** mpEnd;                                      // +0x04
};


void* __fastcall FUN_00c0c1a0(CvgObj* o);                                                // 0x00c0c1a0

typedef float (__fastcall* CvgSlot80)(CvgObj* o, int unused, int arg);

static void cvg_swap(CvgRec* r, CvgObj* o)
{
    uint32_t t0 = r->mX;
    r->mX = o->mB38;
    o->mB38 = t0;
    uint32_t t1 = r->mY;
    r->mY = o->mB3c;
    o->mB3c = t1;
    uint32_t t2 = r->mZ;
    r->mZ = o->mB40;
    o->mB40 = t2;
}

// @ 0x00cdce40
void __fastcall CvgObj_AppendTransitionTargets(CvgObj* self, int unused, PtrVec* list)
{
    CvgVec* vec = &self->mTargets;
    vec->InsertRange(vec->mpBegin, vec->mpEnd);
    vec->Append();
    CvgRec* rec = vec->mpEnd - 1;
    cvg_swap(rec, self);
    rec->mHandle = FUN_00c0c1a0(self);
    rec->mId = self->mB20;

    int count = (int)(list->mpEnd - list->mpBegin);
    for (int i = 0; i < count; ++i) {
        CvgObj* o = (CvgObj*)list->mpBegin[i];
        vec->Append();
        CvgRec* e = vec->mpEnd - 1;
        cvg_swap(e, o);
        e->mHandle = FUN_00c0c1a0(o);
        e->mId = o->mB20;
        e->mF10 = ((CvgSlot80)o->mpVtbl[0x20])(o, 0, 0);
    }
}
