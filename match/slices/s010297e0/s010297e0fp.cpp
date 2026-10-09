// Slice s010297e0 (second TU): SP::FUN_01029950, needs /fp:fast (SSE comiss).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Obj4c;
struct IUnk { virtual int AddRef(); virtual int Release(); };
struct Obj4c {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18();
    virtual int v4c();
};
struct cStarManager {
    Obj4c* GetEmpireByID(int id);            // 0x00ba9370
};
struct cRelationshipManager {
    bool RecordEvent(Obj4c* a, Obj4c* b);    // 0x00d01f50
};
void* StarManager();                         // 0x00b3d2a0
void* GetPlayerEmpire();                     // 0x01021300
void* RelationshipManager();                 // 0x00b3d2c0

struct Planet {
    Obj4c base;                              // vptr @0
    char pad0[0x220 - 4];
    float f220;                              // +0x220
    char pad1[0x748 - 0x224];
    float f748;                              // +0x748
};

// @ 0x01029950
bool FUN_01029950(Planet* p) {
    Obj4c* emp = ((cStarManager*)StarManager())->GetEmpireByID(p->base.v4c());
    Obj4c* player = (Obj4c*)GetPlayerEmpire();
    if (emp == player) return false;
    if (p->f748 >= 100.0f) return false;
    if (p->f220 > 0.0f) return true;
    if (emp) return ((cRelationshipManager*)RelationshipManager())->RecordEvent(emp, player);
    return false;
}
