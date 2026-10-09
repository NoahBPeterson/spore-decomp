// Slice s00acd4a0 - Spore creature/city subsystem: vector clearing, serialization
// of record vectors, cGonzagoSubsystem scalar deleting dtor, city setup.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  byte;

struct RCObj { virtual void AddRef(); virtual void Release(); };
struct Pair {
    void* mpVtbl;   // +0x00
    byte  mb4;      // +0x04
    char  pad[3];
    RCObj* mp8;     // +0x08
};

extern "C" void  WriteUint32(void* s, void* v, int one, int zero);   // 0x93aa70
extern "C" void  ReadInt32(void* s, void* v, int one, int zero);     // 0x93a780
extern "C" void  operator_delete(void* p);                           // 0xf47380
extern "C" void* SP_NounManager();                                   // 0xb3d300
extern "C" void  SP_cGameNounManager_RemoveNoun(void* mgr, int noun);// 0xb225d0
extern "C" void* SP_cSPLivingUniverse_GetActivePlanet();             // 0x1021260
extern "C" void* SP_GetCurrentGameMode();                            // 0xb5b800
extern "C" void* FUN_00b33f40();                                     // 0xb33f40
extern "C" void  FUN_00a02c30(void* p);                              // 0xa02c30
extern "C" void  SP_cAnimatingCreature_Release(void* p);            // 0xa05270
extern "C" void  FUN_009cb4f0(void* p);                              // 0x9cb4f0
extern "C" void  FUN_00acc9b0(int n);                                // 0xacc9b0
extern "C" void  SP_cVarListSerializer_ctor(void* s, void* a, void* b, int c); // 0x692f90
extern "C" char  SP_cVarListSerializer_Serialize(void* s, void* p);   // 0x693e10
extern "C" void  SP_cGonzagoSubsystem_dtor(void* p);                 // 0xb5b9a0
extern "C" int   FUN_00ac9310(int a, void* b, bool c);               // 0xac9310
extern "C" int   FUN_00acbed0(int* a, int* b);                       // 0xacbed0
extern "C" int   FUN_00acbf30(int* a, int n, void* v);               // 0xacbf30
extern "C" void  FUN_00acb490(void* a);                              // 0xacb490
extern "C" int   FUN_00acc8c0(int* a, void* b, int c);               // 0xacc8c0
extern "C" void  FUN_00accd70(int* a, int* b);                       // 0xaccd70
extern "C" void  FUN_00ac9d30(int* a, void* b);                      // 0xac9d30
extern "C" void  FUN_1011cc0(void* a);                               // 0x1011cc0
extern "C" void  FUN_00aca7b0(int* a, int* b);                       // 0xaca7b0
extern "C" void  FUN_00aca820(int* a, int* b);                       // 0xaca820
extern "C" void  FUN_00ae6970(void* a);                              // 0xae6970
extern "C" void  FUN_00ac9d90(void* p);                              // 0xac9d90
extern "C" void  FUN_00b95070(void* a);                              // 0xb95070
extern "C" void  SP_cCityVisualizer_SetCity(void* self, int c);      // 0xd60f00
extern "C" void  SP_cCityVisualizer_SetCity2(void* self, int a, int b); // 0xd5fb60
extern "C" void* SP_App();                                           // 0x67dd10
extern "C" int   FUN_007c4900(void* a, void* b);                     // 0x7c4900

extern float DAT_0167a390, DAT_0167a394, DAT_0167a398;

// ===========================================================================
// @ 0x00acd4a0
// ===========================================================================
struct Rec {
    int   f00;                        // +0x00
    char  pad04[0x18 - 4];
    int*  p18;                        // +0x18
    int*  p1c;                        // +0x1c
    char  pad20[0x2c - 0x20];
    void** p2c;                       // +0x2c
    int*  p30;                        // +0x30
    char  pad34[0x40 - 0x34];
    int*  p40;                        // +0x40
    int*  p44;                        // +0x44
    char  pad48[0x54 - 0x48];
    int*  p54;                        // +0x54
    int*  p58;                        // +0x58
    char  pad5c[0x68 - 0x5c];
    int   p68;                        // +0x68
};
struct COwner {
    char pad0[0xc4];
    void** mpMap;    // +0xc4
    int    mIndex;   // +0xc8
    void FUN_00acd4a0();
};
extern "C" int* eastl_copy_dummy(int* a, int* b, int* c);   // 0x6782c0

void COwner::FUN_00acd4a0()
{
    SP_NounManager();
    void** p = mpMap;
    Rec* rec = (Rec*)*p;
    if (!rec) {
        ++p;
        while (*p == 0) ++p;
        rec = (Rec*)*p;
    }
    Rec* end = (Rec*)mpMap[mIndex];
    while (rec != end) {
        int n1 = (rec->p1c - rec->p18) >> 2;
        int n2 = (rec->p30 - (int*)rec->p2c) >> 2;
        int n3 = (rec->p44 - rec->p40) >> 2;
        int n4 = (rec->p58 - rec->p54) >> 2;
        int i = 0;
        if (rec->p18 != rec->p1c) {
            do {
                if (n1 <= i) break;
                (*(void (__thiscall*)(void*, int))((char*)*(void**)(rec->p1c - 1) + 0xc8))(*(void**)(rec->p1c - 1), 1);
                ++i;
            } while (rec->p18 != rec->p1c);
        }
        i = 0;
        if (n2 > 0) {
            do {
                int v = (int)rec->p2c[i];
                if (v) SP_cGameNounManager_RemoveNoun(0, v);
                ++i;
            } while (i < n2);
        }
        { int* b = (int*)rec->p2c; int* e = rec->p30; eastl_copy_dummy(e, e, b); }
        { int* q = rec->p30; for (int* it = q; it < rec->p30; ++it) { if (*it) ((RCObj*)*it)->Release(); } }
        rec->p30 = (int*)((char*)rec->p30 - n2*4);
        i = 0;
        if (n3 > 0) { do { SP_cGameNounManager_RemoveNoun(0, rec->p40[i]); ++i; } while (i < n3); }
        eastl_copy_dummy(rec->p44, rec->p44, rec->p40);
        { int* q = rec->p44; for (; q < rec->p44; ++q) { if (*q) ((RCObj*)*q)->Release(); } }
        rec->p44 = (int*)((char*)rec->p44 - n3*4);
        i = 0;
        if (n4 > 0) { do { SP_cGameNounManager_RemoveNoun(0, rec->p54[i]); ++i; } while (i < n4); }
        eastl_copy_dummy(rec->p58, rec->p58, rec->p54);
        { int* q = rec->p58; for (; q < rec->p58; ++q) { if (*q) ((RCObj*)*q)->Release(); } }
        rec->p58 = (int*)((char*)rec->p58 - n4*4);
        rec = (Rec*)rec->p68;
        while (!rec) { ++p; rec = (Rec*)*p; }
    }
}

extern "C" void FUN_01008600(void* p);   // 0x1008600
extern "C" int  FUN_00ac9480(int* p);    // 0xac9480
extern "C" void* FUN_00c70c10(void* planet);   // 0xc70c10

// ===========================================================================
// @ 0x00acd6c0
// ===========================================================================
struct CSys {
    char pad0[0xa0];
    void* mpA0;      // +0xa0
    byte FUN_00acd6c0(int msg, int* p);
};
extern int DAT_01565cfc;
extern "C" char FUN_00d58460(void* p);                // 0xd58460
extern "C" int  FUN_00acb190(void* a, int* b);        // 0xacb190
byte CSys::FUN_00acd6c0(int msg, int* p)
{
    if (msg == 0x1a0219e) {
        if (p[2] == 3) {
            int v = (*(int (__thiscall*)(void*))((char*)*(void**)p[4] + 0x20))((void*)p[4]);
            if (v == (int)0x18c43e8 || v == (int)0x18c6d19) DAT_01565cfc = 1;
        } else if (p[2] == 4 && p[4]) {
            int v = (*(int (__thiscall*)(void*, uint32))((char*)*(void**)p[4] + 0xc))((void*)p[4], 0x4f396a66);
            if (v) {
                byte* b = (byte*)((char*)this + 0x8c);
                if (*(void**)((char*)this + 0x8c) != *(void**)((char*)this + 0x90)) {
                    FUN_00ac9480((int*)(*(int*)((char*)this + 0x90) - 0x18));
                    FUN_01008600((int*)(*(int*)((char*)this + 0x90) - 0x14));
                    FUN_00acb190((void*)b, 0);
                }
            }
        }
    } else if (msg == 0x6130eb9) {
        FUN_00d58460(mpA0);
    }
    return 0;
}

// ===========================================================================
// @ 0x00acd790
// ===========================================================================
struct CCreature {
    char pad0[0x64];
    byte  mb64;        // +0x64
    char  pad65[0x88 - 0x65];
    uint32 mFlags88;   // +0x88
    char pad8c[0x118 - 0x8c];
    int*  mpVec118;    // +0x118
    char pad11c[0x17c - 0x11c];
    int*  mp17c;       // +0x17c
    void FUN_00acd790();
};
struct CPlanet {
    char pad[0x13c];
    int* mTree;   // +0x13c
};
void CCreature::FUN_00acd790()
{
    CPlanet* planet = (CPlanet*)SP_cSPLivingUniverse_GetActivePlanet();
    int* tree = (int*)planet->mTree;
    int count = (*(int*)((char*)tree + 0xd4) - *(int*)((char*)tree + 0xd0)) / 0xc;
    int mode = (int)SP_GetCurrentGameMode();
    if (mode == (int)0x1654c04) count = 5;
    else if (count < 1) return;
    int* vec = (int*)((char*)this + 0x118);
    FUN_00acc9b0(count);
    int k = 0;
    for (int i = 0; i < count; ++i) {
        int base = *(int*)((char*)tree + 0xd0);
        int* mgr = (int*)FUN_00b33f40();
        int* v = vec;
        int off = k * 4;
        int obj = (*(int (__thiscall*)(void*, int, int, void*, void*, int))((char*)*mgr + 0x30))(
                      mgr, base + i * 0xc, 4, &DAT_0167a390, (void*)0x1565d20, 1);
        int old = *(int*)(*v + off);
        if (obj != old) {
            if (obj) FUN_00a02c30((void*)obj);
            *(int*)(*v + off) = obj;
            if (old) SP_cAnimatingCreature_Release((void*)old);
        }
        if (*(int*)(*v + off) == 0) {
            int sp = (int)FUN_00c70c10(planet);
            mgr = (int*)FUN_00b33f40();
            int obj2 = (*(int (__thiscall*)(void*, int, int, void*, void*, int))((char*)*mgr + 0x30))(
                           mgr, sp + 0x504, 4, &DAT_0167a390, (void*)0x1565d20, 1);
            old = *(int*)(*v + off);
            if (obj2 != old) {
                if (obj2) FUN_00a02c30((void*)obj2);
                *(int*)(*v + off) = obj2;
                if (old) SP_cAnimatingCreature_Release((void*)old);
            }
        }
        int rec = *(int*)(*v + off);
        *(uint32*)(rec + 0x88) &= ~1;
        *(byte*)(rec + 0x64) = 0;
        if (*(int*)(rec + 0x17c)) FUN_009cb4f0(*(void**)(rec + 0x17c));
        k += 0xc;
    }
}

// ===========================================================================
// @ 0x00acd920
// ===========================================================================
struct Vec3 {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    void FUN_00acd920(unsigned n);
};
void Vec3::FUN_00acd920(unsigned n)
{
    unsigned cnt = (unsigned)((mpEnd - mpBegin) / 0xc);
    if (cnt < n) {
        Pair tmp;
        tmp.mpVtbl = (void*)0x145a158;
        tmp.mb4 = 0;
        tmp.mp8 = 0;
        FUN_00acbf30((int*)mpEnd, (int)(n - cnt), &tmp);
    } else {
        FUN_00acbed0((int*)(mpBegin + n * 0xc), (int*)mpEnd);
    }
}

// ===========================================================================
// @ 0x00acda30
// ===========================================================================
void FUN_00acda30(int* self, int* p)
{
    FUN_00accd70((int*)*(int*)((char*)p + 4), (int*)*(int*)((char*)p + 8));
    *(int*)((char*)p + 0xc) = 0;
    uint32 count = 0;
    int* q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
    ReadInt32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &count, 1, 0);
    for (uint32 i = 0; i < count; ++i) {
        Pair rec;
        rec.mpVtbl = (void*)0x145a184;
        rec.mb4 = 0;
        rec.mp8 = 0;
        // full 0x68-byte record body omitted: reads int32 then serializes
        int one = 0;
        q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
        ReadInt32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &one, 1, 0);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
        char srl[0xa14];
        SP_cVarListSerializer_ctor(srl, &rec, (void*)0x15661a8, 0x1a80d26);
        SP_cVarListSerializer_Serialize(srl, self);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
        int tmp[2];
        FUN_00acc8c0(tmp, &one, 0);
        (void)tmp;
    }
    (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
}

// ===========================================================================
// @ 0x00ace170
// ===========================================================================
struct CSet {
    char pad0[4];
    int*  mp4;      // +0x04
    int   m8;       // +0x08
    int FUN_00ace170(int* p);
};
int CSet::FUN_00ace170(int* p)
{
    int found[3];
    FUN_00ac9d30(found, p);
    if (found[0] == (int)(mp4)[m8]) {
        Pair rec;
        rec.mpVtbl = (void*)0x145a184;
        rec.mb4 = 0;
        rec.mp8 = 0;
        FUN_00acb490(&rec);
        FUN_00acc8c0(found, p, 0);
        FUN_00ae6970(&rec);
    }
    return found[0] + 4;
}

// ===========================================================================
// @ 0x00ace320
// ===========================================================================
struct GonzagoSub2 {
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    void FUN_00ace320();
};
void GonzagoSub2::FUN_00ace320()
{
    *(void**)this = (void*)0x145a1c8;
    *((void**)this + 1) = (void*)0x145a1c4;
    *((void**)this + 7) = (void*)0x145a1bc;
    int* g = *(int**)((char*)this + 0xa4);
    if (g) {
        (*(void (__thiscall*)(int*, int))(*g))(g, 1);
        *(void**)((char*)this + 0xa4) = 0;
    }
    int* b = *(int**)((char*)this + 0xbc);
    if (b) {
        (*(void (__thiscall*)(int*, int))(*b))(b, 1);
        *(void**)((char*)this + 0xbc) = 0;
    }
    FUN_00b95070((char*)this + 0x160);
    FUN_00b95070((char*)this + 0x12c);
    FUN_00ac9d90((char*)this + 0x118);
    int* p104 = *(int**)((char*)this + 0x104);
    int d = *(int*)((char*)this + 0x10c) - (int)p104;
    if ((d & 0xfffffffe) > 2 && p104) operator_delete(p104);
    FUN_00aca820((int*)((char*)this + 0xe0), (int*)*(int*)((char*)this + 0xe8));
    *(int*)((char*)this + 0xec) = 0;
    if (*(uint32*)((char*)this + 0xe8) > 1) operator_delete(*(void**)((char*)this + 0xe4));
    FUN_00accd70((int*)((char*)this + 0xc0), (int*)*(int*)((char*)this + 0xc8));
    *(int*)((char*)this + 0xcc) = 0;
    if (*(uint32*)((char*)this + 0xc8) > 1) operator_delete(*(void**)((char*)this + 0xc4));
    FUN_00aca7b0((int*)((char*)this + 0xa8), (int*)*(int*)((char*)this + 0xac));
    if (*(void**)((char*)this + 0xa8)) operator_delete(*(void**)((char*)this + 0xa8));
    FUN_00aca7b0((int*)((char*)this + 0x88), (int*)*(int*)((char*)this + 0x8c));
    if (*(void**)((char*)this + 0x88)) operator_delete(*(void**)((char*)this + 0x88));
    void* e = *(void**)((char*)this + 0x20);
    if (e && *(int*)((char*)e - 4)) operator_delete(e);
    *(void**)((char*)this + 0x1c) = (void*)0x13eb394;
    (*((void (__thiscall*)(void*))SP_cGonzagoSubsystem_dtor))(this);
}

// ===========================================================================
// @ 0x00ace4e0
// ===========================================================================
extern "C" void FUN_00d5fb60(void* self, int a, int b);   // 0xd5fb60
extern "C" void FUN_00d60f00(void* self, int c);          // 0xd60f00
extern "C" void* SP_cGameNounManager_GetGameDataVector(void* mgr, void* a, void* b, void* c, void* d, void* e); // 0xb21340
extern int DAT_0168d248;
struct CCityOwner {
    char pad0[0xa4];
    void* mpA4;      // +0xa4
    void FUN_00ace4e0(void* param_2);
};
void CCityOwner::FUN_00ace4e0(void* param_2)
{
    int* app = (int*)SP_App();
    int* a = (int*)(*(int (__thiscall*)(int*))((char*)*app + 0x50))(app);
    (*(void (__thiscall*)(int*))((char*)*a + 0x1c))(a);
    int st1[3], st2[3];
    FUN_007c4900(st1, st2);
    void* mgr = SP_NounManager();
    int vec = (int)SP_cGameNounManager_GetGameDataVector(mgr, (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0, (void*)0xb1e500, (void*)0x18c43e8);
    int city = FUN_00ac9310(vec + 4, st1, false);
    int* g = (int*)mpA4;
    if (city != *(int*)((char*)g + 0xaf0)) {
        FUN_00d60f00(g, city);
    }
    FUN_00d5fb60(g, (int)param_2, 0);
    int* gg = *(int**)((char*)g + 0xaf0);
    if (gg && DAT_0168d248) {
        (*(void (__thiscall*)(int*))((char*)*gg + 0x78))(gg);
    }
}
