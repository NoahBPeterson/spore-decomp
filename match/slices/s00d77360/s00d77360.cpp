// Decompiled from SporeApp.exe (gold6 batch, worker 33).
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef float          f32;

// ---------------------------------------------------------------------------
// Sub-object with a vtable pointer (used at creature+0xc0, tribe+0x120).
// ---------------------------------------------------------------------------
struct VtblObj {
    void** mVtbl;   // +0x00
};

// Sub-object passed to FUN_00cee330 (creature+0x34).
struct At34 {
    u32 mValue;              // +0x00 (placeholder keeps the sub-object 4 bytes)
    int Func_cee330();       // 0x00cee330
};

// ---------------------------------------------------------------------------
// Creature object layout (fields touched by this slice).
// ---------------------------------------------------------------------------
struct Creature {
    void** mVtbl;            // +0x00
    u8  mPad04[0x30];        // +0x04
    At34 mAt34;              // +0x34
    u8  mPad38[0x88];        // +0x38
    VtblObj mVec;            // +0xc0
    u8  mPadC4[0xa88];       // +0xc4
    void* mOrderMgr;         // +0xb4c
    u8  mPadB50[0x08];       // +0xb50
    u32 mFlags;              // +0xb58

    void* GetTribe();                // 0x00c22f50
    bool  Func_c0ba30();             // 0x00c0ba30
    void  Func_c17350(int, int);     // 0x00c17350
    void  Func_c0b970(float);        // 0x00c0b970
    void  Func_c0d0c0(int, int);     // 0x00c0d0c0
    void  SetCurrentToolEffect(int, int); // 0x00c24f40
    void  Func_c1d460(int, int);     // 0x00c1d460
    void  Func_c14750(int);          // 0x00c14750
};

// ---------------------------------------------------------------------------
// Tribe object layout (fields touched by FUN_00d77400).
// ---------------------------------------------------------------------------
struct Tribe {
    void** mVtbl;            // +0x00
    u8  mPad04[0x11c];       // +0x04
    VtblObj mPos120;         // +0x120

    bool IsAvailableInCurrentPlanet(); // 0x00b1e4d0
    void Func_c8e6b0();                // 0x00c8e6b0
};

// Minimal stubs for objects only reached through a pointer.
struct OrderMgr {
    void* FirstPending();                        // 0x00bca2c0
    void* FindNode(int, void*, void*);           // 0x00bca620
    void* Func_bcb0b0(int, int, int, const char*); // 0x00bcb0b0
    void  Func_bcb480(void*, void*, void*, void*); // 0x00bcb480
};
struct OrderMgrPlayApi {
    void* Play(int, int);    // 0x00bc96a0
};
struct OrderMgrPlay {
    u8  mPad00[8];            // +0x00
    OrderMgrPlayApi mApi;     // +0x08
};
struct PendingOrder {
    u32 m0;                  // +0x00
};
struct TribeTail {
    void Func_c8e6c0();      // 0x00c8e6c0
};
struct Node {
    u8  mPad00[0x1a4];       // +0x00
    f32 m1A4;                // +0x1a4
    void* Func_bc9b10();     // 0x00bc9b10
    bool  Func_bc9b50();     // 0x00bc9b50
};
struct Holder {
    u32 m0;                  // +0x00
    void* m4;                // +0x04
};
struct Ctx {
    u8  mPad00[4];           // +0x00
    void* m4;                // +0x04
};
struct PtrB770 {
    bool  Func_c0b770();     // 0x00c0b770
    void* GetTribe();        // 0x00c22f50
};
struct Arg1 {
    void* Func_bc9b10();     // 0x00bc9b10
};

extern "C" void* __cdecl FUN_00bc9b00();          // 0x00bc9b00
extern "C" void* __cdecl WatchMemoryBlock(void*); // 0x00d999d0
extern "C" bool  __cdecl FUN_00da6270(void*, int); // 0x00da6270

// ---------------------------------------------------------------------------
// 00d77360 -- SP::TRIBE_IN_HEAT_Deactivate (86 bytes)
// ---------------------------------------------------------------------------
// @ 0x00d77360
void FUN_00d77360(Creature* self)
{
    ((void (__thiscall*)(Creature*, int, int, int))self->mVtbl[0x84 / 4])(self, 0, 0, 0);
    self->mFlags &= ~0x10u;
    void* tribe = self->GetTribe();
    self->Func_c17350(0x9005e011, 0);
    void* pending = ((OrderMgr*)self->mOrderMgr)->FirstPending();
    if (pending != 0 && ((PendingOrder*)pending)->m0 == 0xb)
        return;
    ((TribeTail*)tribe)->Func_c8e6c0();
}

// ---------------------------------------------------------------------------
// 00d773c0 -- callback predicate (58 bytes)
// ---------------------------------------------------------------------------
// @ 0x00d773c0
bool FUN_00d773c0(void* a1, void* a2)
{
    void* p = ((Ctx*)a2)->m4;
    if (((PtrB770*)p)->Func_c0b770()) {
        void* x = ((Arg1*)a1)->Func_bc9b10();
        void* t1 = ((PtrB770*)x)->GetTribe();
        void* t2 = ((PtrB770*)p)->GetTribe();
        if (t1 == t2)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 00d77400 -- distance/radius check (262 bytes)
// ---------------------------------------------------------------------------
// @ 0x00d77400
float FUN_00d77400(Creature* self)
{
    if (self->mAt34.Func_cee330() == 0) {
        if (!self->Func_c0ba30()) {
            Tribe* tribe = (Tribe*)self->GetTribe();
            if (tribe->IsAvailableInCurrentPlanet()) {
                float* a = ((float* (__thiscall*)(VtblObj*))tribe->mPos120.mVtbl[0x2c / 4])(&tribe->mPos120);
                float* b = ((float* (__thiscall*)(VtblObj*))self->mVec.mVtbl[0x2c / 4])(&self->mVec);
                float dx = b[0] - a[0];
                float dy = b[1] - a[1];
                float dz = b[2] - a[2];
                float radius = ((float (__thiscall*)(Tribe*))tribe->mVtbl[0x60 / 4])(tribe);
                if ((dz * dz + dx * dx) + dy * dy < radius * radius) {
                    self->mFlags |= 0x10u;
                    tribe->Func_c8e6b0();
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 00d77510 -- SP::TRIBE_MATE_Activate (361 bytes)
// ---------------------------------------------------------------------------
namespace SP {
// @ 0x00d77510
bool TRIBE_MATE_Activate(Creature* self, int, int, int, int, Holder* holder)
{
    if (holder != 0)
        holder->m4 = 0;
    void* old = holder->m4;
    if (self != old) {
        if (self != 0)
            ((void (__thiscall*)(void*))(*(void***)self)[0])(self);
        holder->m4 = self;
        if (old != 0)
            ((void (__thiscall*)(void*))(*(void***)old)[1])(old);
    }

    void* played = ((OrderMgrPlay*)self->mOrderMgr)->mApi.Play(0x20000, 0);
    void* watched = WatchMemoryBlock(played);

    void* node = ((OrderMgr*)FUN_00bc9b00())->FindNode(0x4e3feef, (void*)0xd773c0, holder);
    void* ebp;
    if (node == 0) {
        void* n2 = ((OrderMgr*)FUN_00bc9b00())->Func_bcb0b0(0x4e3feef, 2, 0x18eb4b7, (const char*)0x147bf18);
        node = n2;
        ((Node*)node)->m1A4 = 0.0f;
        ebp = self;
    } else {
        ebp = ((Node*)node)->Func_bc9b10();
    }

    if (!((Node*)node)->Func_bc9b50()
        && (watched == 0 || ebp == self || ebp == watched || self == watched)) {
        ((OrderMgr*)self->mOrderMgr)->Func_bcb480(node, self, holder, (void*)0xd773c0);
        ((void (__thiscall*)(VtblObj*, int))self->mVec.mVtbl[0x54 / 4])(&self->mVec, 0);
        holder->m0 = 1;
        self->Func_c0b970(0.0f);
        self->Func_c0d0c0(6, 1);
        self->SetCurrentToolEffect(0, -1);
        self->Func_c1d460(0x9005e011, 0x9005e011);
        if (!((bool (__thiscall*)(VtblObj*))self->mVec.mVtbl[0xf8 / 4])(&self->mVec))
            self->Func_c14750(1);
        return true;
    }
    return FUN_00da6270(self, 0xb);
}
} // namespace SP
