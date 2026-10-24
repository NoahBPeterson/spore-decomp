// s00b9bed0.cpp -- gold6 batch, worker 25
// Reconstructed from the annotated disassembly + Ghidra decompiles in
// work/match/scratch_s00b9bed0_cards.txt.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

class TObj {
public:
    int*  mBegin;    // +0x00
    int*  mEnd;      // +0x04
    void* mArr;      // +0x08
    int   m0c;       // +0x0c
    int   m10;       // +0x10
    int   m14;       // +0x14
    int   m18;       // +0x18
    void* mRef1c;    // +0x1c
    void* mRef20;    // +0x20
    int   m24;       // +0x24
    int   m28;       // +0x28
    int   m2c;       // +0x2c
    void* mSub30;    // +0x30

    void FUN_00b9c250(void);        // 0xb9c250
    void FUN_00b9c5c0(void);        // 0xb9c5c0
    void F_1023030(int, int);       // 0x1023030  eastl vector dtor-ish (thiscall, 2 args)
    void F_b9a630(void);            // 0xb9a630
};

extern "C" int  __cdecl FUN_00b969a0(int, int, int);   // 0xb969a0
extern "C" void __cdecl FUN_00b9bb40(int);             // 0xb9bb40
extern "C" void __cdecl FUN_00f47380(void*);           // 0xf47380 operator_delete_array

// ===========================================================================
// 0x00b9c250 - shrink a vector<...> back by one 0x14-byte element and destroy it
// ===========================================================================
// @ 0x00b9c250
void TObj::FUN_00b9c250(void) {
    int iVar3 = (int)mBegin;
    int iVar1 = (int)mEnd;
    int uVar2 = FUN_00b969a0(iVar1, iVar1, iVar3);
    F_1023030(uVar2, (int)mEnd);
    mEnd = (int*)((int)mEnd + (-((iVar1 - iVar3) / 0x14)) * 0x14);
}

// ===========================================================================
// 0x00b9c5b0 - tail-call forwarder: fn(this->mSub30)
// ===========================================================================
// @ 0x00b9c5b0
void __cdecl FUN_00b9c5b0(TObj* p) {
    FUN_00b9bb40((int)p->mSub30);
}

// ===========================================================================
// 0x00b9c5c0 - release the two AutoRefCount members and free the +8 array
// ===========================================================================
// @ 0x00b9c5c0
void TObj::FUN_00b9c5c0(void) {
    F_b9a630();
    void* r20 = mRef20;
    if (r20 != 0) {
        unsigned* rc = (unsigned*)((char*)r20 + 4);
        unsigned c = rc[0] + -1;
        rc[0] = c;
        if (c == 0) {
            rc[0] = 1;
            ((void(__thiscall*)(void*, int))VF(r20, 0))(r20, 1);
        }
    }
    void* r1c = mRef1c;
    if (r1c != 0) {
        unsigned* rc = (unsigned*)((char*)r1c + 4);
        unsigned c = rc[0] + -1;
        rc[0] = c;
        if (c == 0) {
            rc[0] = 1;
            ((void(__thiscall*)(void*, int))VF(r1c, 0))(r1c, 1);
        }
    }
    void* a = mArr;
    if (a != 0 && *(int*)((char*)a - 4) != 0) {
        FUN_00f47380(a);
    }
}