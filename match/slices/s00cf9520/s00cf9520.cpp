// Slice s00cf9520 -- SP::cCivModeStrategy teardown (0x00cf9520..0x00cf9868).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Relocations (calls, globals, vtable slots) are masked by the matcher, so a
// callee's symbol identity does not affect byte matching: only the calling
// convention and the number/shape of its arguments do.  Calls shaped
// `mov ecx, <obj>; call X` are modeled as __thiscall 0-arg members.

typedef unsigned int  uint32_t;
typedef unsigned char uint8_t;

#define VTFN(p, slot) ((*(void***)(p))[slot])

typedef void (__thiscall* TFnV)(void*);

// --- messaging server -------------------------------------------------------
// The strategy's message-handler sub-object at +0x24 is registered with the
// messaging server on startup (see 0x00cf7dc0) and unregistered here, under
// the same 23 message ids, with priority -9999.
struct MsgServer {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void Reg(void* handler, unsigned id);                  // slot 8  (0x20)
    virtual void m09(); virtual void m10();
    virtual void Unreg(void* handler, unsigned id, int priority);  // slot 11 (0x2c)
};

void* __cdecl SP_MessageServer();                       // 0x0067dcc0

// --- objects owned by the strategy ------------------------------------------
// Cache/editable wrapper at +0x10c: cleared, then released.
struct Cache {
    void Clear();                                       // 0x007b1950
};

// Effect-preload wrapper: freed, then destroyed with the plain destructor
// followed by operator delete (non-virtual destructor).
struct Preload {
    void Free();                                        // 0x007cfc60
    ~Preload();                                         // 0x007cfa90
};

// Ref-counted objects held at +0xe8 / +0xec.
struct ElemA {
    virtual void Release(int);                          // slot 0 (0x00)
    virtual void v01();                                 // slot 1 (0x04)
    virtual void Fini();                                // slot 2 (0x08)
};

struct ElemB {
    virtual void Release(int);                          // slot 0 (0x00)
};

// The sim-mode strategy singleton created at 0x00cf7dc0 and kept in
// DAT_0169d2b8.  Non-virtual destructor: the teardown calls it directly and
// then operator delete.
struct SimStrategy {
    ~SimStrategy();                                     // 0x00cee060
};

SimStrategy* DAT_0169d2b8;                              // 0x0169d2b8

// --- the strategy itself ----------------------------------------------------
struct Strat {
    char OnExit();                                      // 0x00cf9520
    void FUN_00cf86d0();                                // 0x00cf86d0 (sim singletons)

    uint32_t mPad0[0x24 / 4];                           // +0x00
    uint8_t  mSub_0x24[0xb0 - 0x24];                    // +0x24 message-handler sub-object
    uint8_t  mbFlag_0xb0;                               // +0xb0
    uint8_t  mPad1[0xe8 - 0xb1];                        // +0xb1
    ElemA*   mpElem_0xe8;                               // +0xe8
    ElemB*   mpElem_0xec;                               // +0xec
    uint8_t  mPad2[0x10c - 0xf0];                       // +0xf0
    Cache*   mpCache_0x10c;                             // +0x10c
    Preload* mpPreload_0x110;                           // +0x110
    Preload* mpPreload_0x114;                           // +0x114
};

// ===========================================================================
// @ 0x00cf9520
// SP::cCivModeStrategy::OnExit -- undo 0x00cf7dc0: drop the editable cache and
// the effect preloads, detach the sim singletons, unregister every civ-mode
// message, release the sim-mode strategy and the hint/other objects.
char Strat::OnExit()
{
    if (mpCache_0x10c) {
        mpCache_0x10c->Clear();
        if (mpCache_0x10c) {
            void* p = mpCache_0x10c;
            mpCache_0x10c = 0;
            ((TFnV)VTFN(p, 1))(p);
        }
    }
    if (mpPreload_0x110) {
        mpPreload_0x110->Free();
        delete mpPreload_0x110;
        mpPreload_0x110 = 0;
    }
    if (mpPreload_0x114) {
        mpPreload_0x114->Free();
        delete mpPreload_0x114;
        mpPreload_0x114 = 0;
    }
    this->FUN_00cf86d0();

    void* handler = (void*)&this->mSub_0x24;
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x1a0219e, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x164b4eb, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x44f1189, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x56cfe69, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5dbc31e, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5dfb3c8, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5dfb77f, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5dfb782, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5dfb786, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5f4d02a, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x604bf01, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5668f43, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x30c11c7, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5356bb5, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x53836de, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5badd9f, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x5bff9c8, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0xb2699149u, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x6270d2f, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x6417958, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x66e0e11, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x670eccd, -9999);
    ((MsgServer*)SP_MessageServer())->Unreg(handler, 0x679c40d, -9999);

    if (DAT_0169d2b8) {
        delete DAT_0169d2b8;
        DAT_0169d2b8 = 0;
    }

    if (mpElem_0xe8) {
        mpElem_0xe8->Fini();
        if (mpElem_0xe8)
            mpElem_0xe8->Release(1);
        mpElem_0xe8 = 0;
    }
    if (mpElem_0xec) {
        mpElem_0xec->Release(1);
        mpElem_0xec = 0;
    }

    char result = 1;
    if (mbFlag_0xb0)
        mbFlag_0xb0 = 0;
    return result;
}
