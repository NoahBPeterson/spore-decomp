// Slice s007e70b0.
#include "../s007e5220/s007e5220.h"

// ---- shared stub types for this slice ----
struct PLBase32 {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
  virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
  virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
  virtual void v90(); virtual void v94(); virtual void v98();
  virtual char vf24(void* a, void* b);   // +0x24
  int   vf18(int a);                     // +0x18
};
struct PropWatcher32 {
  uint32_t f0; void* f4; void* f8; int fc;
  PropWatcher32* ctor(void* list, void* owner, uint32_t value);
  void Read(void* p2);
};
void* gAllocator_13ebc58;
void* gVtbl_13eb90c;
void* gVtbl_13eb844;
void* operator_new(uint32_t sz, void* alloc, int a, int b, int c, int d);

// @ 0x007E7260  (PropWatcher constructor)
PropWatcher32* PropWatcher32::ctor(void* list, void* owner, uint32_t value) {
    f0 = value;
    f4 = list;
    if (list)
        ((PLBase32*)list)->v00();
    f8 = owner;
    fc = 0;
    if (list)
        Read(list);
    return this;
}

// @ 0x007E72D0  (cQuitCheat::Execute)
struct Arguments {
    char HasFlag(const char* name);
    const char*** MainArguments(int* count, int a, int b);
};
extern "C" long __cdecl atol(const char*);
struct MsgObj {
    void* vt;      // +0
    int   ref;     // +4
    int   val;     // +8
    char  pad_c[0x30 - 0xc];
    int   f30;     // +0x30
    char  pad34[0x38 - 0x34];
    int   f38;     // +0x38
};
struct QuitCheat { void Execute(Arguments* args); };
void QuitCheat::Execute(Arguments* args) {
    if (args->HasFlag("crash"))
        *(int*)0 = 0;
    int count = 0;
    const char*** argv = args->MainArguments(&count, 0, 1);
    long v = 0;
    if (count > 0)
        v = atol((const char*)argv[0]);
    MsgObj* m = (MsgObj*)operator_new(0x40, &gAllocator_13ebc58, 0, 0, 0, 0);
    if (m) {
        m->f30 = 0;
        m->vt = &gVtbl_13eb90c;
        m->ref = 0;
        m->vt = &gVtbl_13eb844;
        m->f38 = 0;
    }
    m->val = (int)v;
    SP_MessageServer()->SendMessage(0x153c326, (int)m, 0, 0);
}

// @ 0x007E70B0  (cAppSystem::HandleMessage)
int cAppSystemHandleMessage(cAppSystem* self, uint32_t msg, int data) {
    // Custom message dispatch (ResourceMan / effect messages); not reconstructed.
    (void)self; (void)msg; (void)data;
    return 0;
}

// @ 0x007E7380  (cAppSystem::Configure)
int cAppSystemConfigure(void* self, void* a, int b) {
    (void)self; (void)a; (void)b;
    return 0;
}

// @ 0x007E7630  (cAppSystem::cAppSystem)
void cAppSystemCtor(void* self, void* a) { (void)self; (void)a; }

// @ 0x007E78D0  (cAppSystem::~cAppSystem)
void cAppSystemDtor(void* self) { (void)self; }

// @ 0x007E7B50
void FUN_007e7b50(void* self) { (void)self; }
