// SP cell stage: arm the "start from egg" notification, sibling of
// SP::sHatchFromIce_Start (0x00e6ecb0, dev 0x00a7d630).  Same shape as its
// sibling, one release/notification slot earlier.
//
// Retail reads its only input, a cHandleRef*, from ESI at entry and finishes
// with `mov eax,[esi]; jmp 0x00e5ec10` (SP::sCellBeginSpawn, whose int argument
// arrives in EAX at 0x00e5ec10).  Per docs/codegen.md 6.3 those are static
// callees with register calling conventions, so both are kept `static` and
// given same-TU stand-in callers; the build must then pick the register
// convention instead of a stack argument.

typedef unsigned int uint32;

struct cHandleRef {                 // 4-byte handle holder (cf. s00e7fd00.cpp)
    uint32 mHandle;
};

struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };

// ---------------------------------------------------------------- globals
extern void*   gspCellGame;         // 0x016b3c04  cCellGame*
extern void*   gspCellUI;           // 0x016b3c0c  cCellUI*
extern Vector3 gNotifyPos;          // 0x016b3c28  copied to +0x48 and +0x54
extern Vector4 gNotifyColor;        // 0x015a7c4c  copied to +0x60

// ---------------------------------------------------------------- callees
extern "C" uint32 __cdecl FUN_00932e80(const char* name, uint32 hash, int flag); // 0x00932e80
struct cNotifyTarget {              // object reached through 0xe66840
    virtual void v00();             // called as (*target)[0]
};
extern "C" cNotifyTarget* __cdecl FUN_00e66840(cHandleRef* ref, uint32 key); // 0x00e66840

// handle maps at cCellGame+0x1c / +0x54 (this in ECX, the handle on the stack,
// as retail shows: `mov ecx,<game>; add ecx,0x1c; push key; call`).
struct cHandleMap {
    int   Head();                   // 0x00b72160
    void* Find(uint32 handle);      // 0x00b72210
};

extern "C" float __cdecl FUN_00e6d200(void* src, int a, int b, int c);          // 0x00e6d200

extern "C" void* __stdcall FUN_00b3d4d0(int which);                             // 0x00b3d4d0
struct cCellScreen { void ClearModal(); };                                      // 0x00ad7e40

// record produced by cHandleMap::Find for a notification slot
struct cNotify {
    uint32        field_00;
    uint32        field_04;
    unsigned char field_08;
    unsigned char pad_09[0x1c - 0x09];
    float         field_1c;
    float         field_20;
    uint32        field_24;          // 0x1c (record kind/size)
    uint32        field_28;          // source handle
    uint32        field_2c;
    uint32        field_30;          // -1
    uint32        field_34;          // -1
    uint32        field_38;
    uint32        field_3c;
    float         field_40;
    float         field_44;
    Vector3       field_48;
    Vector3       field_54;
    Vector4       field_60;
    cNotifyTarget* field_70;
    unsigned char field_74;
    unsigned char pad_75[3];
    uint32        field_78;
};

// Build with /O2 /MD /Gy /TP /arch:SSE /fp:fast (the cell-stage slices' flags).
// Stand-in callers / stand-in body (see the note at the top): they exist only to
// make this TU give both helpers the retail register convention, so the body of
// 0x00e5ec10's stand-in keeps a side effect (a dead one would be discarded by
// /O2 and the tail call would vanish).
__declspec(noinline) static bool sCellBeginSpawn(int handle);   // 0x00e5ec10
void sCellBeginSpawn_probe(int handle);
void FUN_00e6eb60_probe(cHandleRef* ref);

// @ 0x00e6eb60
__declspec(noinline) static void FUN_00e6eb60(cHandleRef* ref)
{
    // object that owns this notification's window/behaviour
    cNotifyTarget* target = FUN_00e66840(ref, FUN_00932e80("CellGameStart", 0x811c9dc5u, 1));
    target->v00();

    // timing/behaviour record of the same key in the "current" table.  The map
    // half of cCellGame is spelled out at every use: retail reloads
    // gspCellGame and re-adds +0x1c / +0x54 for each call instead of caching it.
    uint32 key = ref->mHandle;
    cHandleMap* current = (cHandleMap*)((char*)gspCellGame + 0x1c);
    void* src = current->Find(key);
    float time = FUN_00e6d200(src, 0, 0x2b, *(int*)((char*)src + 0x1b0));

    // the notification slot itself
    uint32 refHandle = ref->mHandle;
    int handle = ((cHandleMap*)((char*)gspCellGame + 0x54))->Head();
    // the sibling 0x00e6ecb0 (match/slices/s00e6ecb0) binds the second pool as a
    // reference before the lookup; that keeps the `add ecx,0x54` ahead of the
    // `push` of the handle, as retail has it.
    cHandleMap& slots = *(cHandleMap*)((char*)gspCellGame + 0x54);
    cNotify* n = (cNotify*)slots.Find(handle);

    n->field_1c = time;
    n->field_20 = time;
    n->field_28 = refHandle;
    n->field_24 = 0x1c;
    n->field_2c = 0;
    n->field_38 = 0;
    n->field_3c = 0;
    n->field_40 = 0.0f;
    n->field_44 = 0.0f;
    n->field_30 = -1;
    n->field_34 = -1;
    n->field_48 = gNotifyPos;
    n->field_54 = gNotifyPos;
    n->field_60 = gNotifyColor;
    n->field_70 = target;
    n->field_74 = 0;
    n->field_78 = 0;
    n->field_04 = 0;
    n->field_08 = 0;

    ((cCellScreen*)FUN_00b3d4d0(1))->ClearModal();
    *((unsigned char*)gspCellUI + 0x936) = 1;
    *((uint32*)((char*)gspCellGame + 0x5194)) = (uint32)handle;
    sCellBeginSpawn((int)ref->mHandle);
}

void FUN_00e6eb60_probe(cHandleRef* ref)
{
    FUN_00e6eb60(ref);
}

void sCellBeginSpawn_probe(int handle)
{
    sCellBeginSpawn(handle);
}

volatile int gSpawnStandIn;
__declspec(noinline) static bool sCellBeginSpawn(int handle)
{
    gSpawnStandIn = handle;
    return handle != 0;
}
