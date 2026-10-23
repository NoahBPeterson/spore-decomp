// Slice s00c72c60: Simulator cPlanet / cVisiblePlanet debug-info, vector-insert and
// reset/dtor routines (retail). Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
#include "types.h"

extern uint32_t g_01693efc, g_01693f00, g_01693f04;
extern uint16_t gEmptyString16_01667bac;
extern void* vtbl_CPlanet_014725d8;
extern void* vtbl_CPlanet_gd_01472580;
extern void* vtbl_CPlanet_d8_01472570;

// ---------------------------------------------------------------- free calls
void  StrAppendSprintf(void* s, const char* fmt, ...);               // 0x005f9450
void* FUN_00ecdba0(void* p);                                        // 0x00ecdba0
int   FUN_00b8dab0(void* p);                                        // 0x00b8dab0
void* SP_StarManager_00b3d2a0(void* p);                             // 0x00b3d2a0
void* cStarManager_GetEmpireByID_00ba9370(void* sm);                // 0x00ba9370
void* cEmpire_DebugArchetype_00c30eb0(void* e);                     // 0x00c30eb0
void  FUN_00f47380(void* p);                                        // 0x00f47380 (operator delete)
void* FUN_00f473a0(int size, const char* file, int a, int b, int c, int d); // 0x00f473a0
void* FUN_00c72540(void* a, void* b, void* c, int d);               // 0x00c72540
void  FUN_00b96600(void* cur, void* elem);                          // 0x00b96600
void* FUN_00bef6c0(void);                                           // 0x00bef6c0
void* FUN_00ff0db0(int v);                                          // 0x00ff0db0
void* FUN_00ff23b0(int v);                                          // 0x00ff23b0
void* FUN_00ff3220(void* a, void* b, void* c);                      // 0x00ff3220
void  FUN_00bd81e0(void* p);                                        // 0x00bd81e0
void* FUN_00bd81f0(void* p);                                        // 0x00bd81f0
void  FUN_00a110b0(void* p, void* q);                               // 0x00a110b0
void  FUN_00c9eae0(void* p);                                        // 0x00c9eae0
void  FUN_00b8eec0(void* p);                                        // 0x00b8eec0
void* SP_NounManager_00b3d300();                                    // 0x00b3d300 (no args)
void  cGameNounManager_RemoveNoun_00b225d0(void* mgr, void* noun);  // 0x00b225d0
struct NounMgr_00b225d0 { void Remove(void* noun); };               // 0x00b225d0 (ecx=mgr)
void* cStarRecordRef_GetCommContext_00ce6950(void* p);              // 0x00ce6950
struct CommRef_00ce6950 { void* GetCommContext(); };                // 0x00ce6950 (ecx=self)
void* GetCurrentTerrainSphere_00f67d90(void* p);                    // 0x00f67d90
struct TerrainSphere_00f67d90 { void* GetCurrentTerrainSphere(); }; // 0x00f67d90 (ecx=nounmgr)
void* SP_cCivData_GetCities_005c65e0(void* p);                      // 0x005c65e0
struct CivData_005c65e0 { void* GetCities(); };                     // 0x005c65e0 (ecx=civ)
struct PtrPair { int* begin; int* end; };
void  DoInsertValue_00ac9200(void* a);                              // 0x00ac9200
void  FUN_00acb810(void* cur, void* v);                             // 0x00acb810

// --------------------------------------------------- eastl vector helper decls
// push_back(indirect) called with ecx = the vector; args (position, value).
struct VecH_00b96600 { void Push(void* cur, const void* v); };            // 0x00b96600
struct VecH_004e3e10 { void GrowAndAppend(void* pos, const void* v); };   // 0x004e3e10
struct VecH_0050f740 { void erase(void* first, void* last); };            // 0x0050f740
// A 3-pointer eastl vector laid out in-place inside a struct.
struct EaVec3 { void* begin; void* end; void* cap; void erase(void* first, void* last); };
struct PlanetTail { char pad0[0xbc]; EaVec3 vbc; };                        // vector at +0xbc
struct PlanetTailD0 { char pad0[0xd0]; EaVec3 vd0; };                      // vector at +0xd0
void  FUN_00533500(void* a, void* b);                               // 0x00533500
void  cGonzagoTimer_dtor_00b638b0(void* p);                         // 0x00b638b0
void  cGameData_dtor_00b184c0(void* p);                             // 0x00b184c0
void  FUN_00c8a420(void);                                           // 0x00c8a420
void  FUN_00c72d00(void* a, void* b);                               // 0x00c72d00
void  FUN_00ba70d0(void* p);                                        // 0x00ba70d0
// eastl wide-string assign-from-cstr (used inline in FUN_00c72e10/00c737a0).
void  WStr_Assign(void* vec3, const uint16_t* src);                 // helper (not a slice VA)
void* SP_cGameNounManager_GetGameDataVector(void* mgr, void* f1, void* f2, void* f3, void* f4, void* id); // 0x00b21340
void  FUN_00b8de60(void* p);                                        // 0x00b8de60
void  FUN_00b8df20(void* p);                                        // 0x00b8df20
void  FUN_00c8ea30(void* p, void* d);                               // 0x00c8ea30
void  FUN_00b8ef00(void* p, void* d);                               // 0x00b8ef00
void* cTribeData_ctor_00ff0610(int v);                              // 0x00ff0610
void  FUN_00b3d480(void);                                           // 0x00b3d480
void  FUN_00ac8e90(void);                                           // 0x00ac8e90
void  FUN_00bef8f0(void* p);                                        // 0x00bef8f0
void* FUN_00c30c80(void);                                           // 0x00c30c80
void  FUN_00bebdd0(void* p);                                        // 0x00bebdd0
void* FUN_00bce4c0(void);                                           // 0x00bce4c0
void  FUN_00bf1f40(void* p);                                        // 0x00bf1f40
void* SP_SpaceGameGet(void);                                        // (noun manager helper)
void* SP_cGameNounManager_GetAvatar(void* mgr);                     // helper
void* cEmpire_GetColor(void* e, void* out);                         // helper
void  FUN_00bfc6a0(void);                                           // 0x00bfc6a0
void  FUN_00be5700(void* p);                                        // 0x00be5700
void* SP_cTribe_GetMembers(void* t);                                // helper
void  FUN_00ff9520(void* p);                                        // 0x00ff9520
void* cSPLivingUniverse_GetPlayerEmpire(void);                      // helper
void* FUN_00cd7d10(void);                                           // 0x00cd7d10
void* FUN_00d3d420(void);                                           // 0x00d3d420
void* FUN_00b1e500(void);                                           // 0x00b1e500
void* FUN_00acdff0(void);                                           // 0x00acdff0
void* FUN_00ae72d0(void);                                           // 0x00ae72d0
void* FUN_00accbb0(void);                                           // 0x00accbb0
void* FUN_00b236c0(void);                                           // 0x00b236c0
void* FUN_00b21080(void);                                           // 0x00b21080
void* FUN_00b8de30(void* p);                                        // 0x00b8de30
void  FUN_00a16a90(void* p);                                        // 0x00a16a90
struct PlanetMap_00c729b0 { void find_00c729b0(void* out, void* key); };  // 0x00c729b0 (ecx=this)
void  FUN_00705250(void* dst, void* end, void* src);                // 0x00705250
void  FUN_00c723d0_local(void* self);                               // 0x00c723d0
void  FUN_00c8b2e0_00(void);                                        // 0x00c8b2e0
void* FUN_00d01260(void* a, void* b, void* c, int d);               // 0x00d01260
void  FUN_004b5440(void* p);                                        // 0x004b5440

// ===========================================================================
// @ 0x00c72c60
// cPlanet::AddDebugInfo -- append the planet name and, when the planet data
// reports kind 5, the owning empire's archetype name.
// ===========================================================================
struct PlanetCls {
    void AddDebugInfo_00c72c60(void* str);
    void AddDebugInfo_00c72ce0(void* str);
    bool FUN_00c72d70(int key);
    void FUN_00c72dd0(int v);
    void FUN_00c72e10(char* pd);
    bool FUN_00c73250();
    void FUN_00c73270(int* key);
    void FUN_00c732c0(int* key);
    void FUN_00c73310();
    void FUN_00c73330();
    int FUN_00c73350(int* key);
    void FUN_00c733b0();
    void** FUN_00c73520(void** out);
    int* FUN_00c735e0(int* key);
    void FUN_00c73680();
    void FUN_00c73b60();
};

void PlanetCls::AddDebugInfo_00c72c60(void* str)
{
    char* s = (char*)this;
    void* pd = *(void**)(s + 0x13c);
    StrAppendSprintf(str, "\nPlanet Name: %S", ((void**)FUN_00ecdba0(pd))[0]);

    pd = *(void**)(s + 0x13c);
    if (pd != 0 && FUN_00b8dab0(pd) == 5) {
        void* gd = *(void**)(s + 0xd4);
        void* slot = ((void*(__thiscall*)(void*))(*(void***)gd)[0x4c / 4])(gd);
        void* sm = SP_StarManager_00b3d2a0(slot);
        void* emp = cStarManager_GetEmpireByID_00ba9370(sm);
        if (emp != 0)
            StrAppendSprintf(str, "\nArchetype: %s\n", cEmpire_DebugArchetype_00c30eb0(emp));
    }
}

// ===========================================================================
// @ 0x00c72ce0
// ===========================================================================
void PlanetCls::AddDebugInfo_00c72ce0(void* str)
{
    StrAppendSprintf(str, "\nVisiblePlanet");
}

// ===========================================================================
// @ 0x00c72d70
// Look up `key` in the object's map and report whether the found node's byte at
// +0xaa is set.
// ===========================================================================
bool PlanetCls::FUN_00c72d70(int key)
{
    char* s = (char*)this;
    int* end = *(int**)(s + 0x11c4);
    int* r = (int*)FUN_00c72540(*(void**)(s + 0x11c0), end, &key,
                                *(unsigned char*)(s + 0x11d4));
    if (r == end || key < *r || r == (int*)((char*)r + 0xb0))
        r = end;
    if (r != end)
        return *(char*)((char*)r + 0xaa) != 0;
    return false;
}

// ===========================================================================
// @ 0x00c72dd0
// Push a dword onto the int vector at planet->+0xe4.
// ===========================================================================
void PlanetCls::FUN_00c72dd0(int v)
{
    char* p = *(char**)((char*)this + 0x13c);
    int* vec = (int*)(p + 0xe4);
    int* cur = (int*)vec[1];
    if (cur < (int*)vec[2]) {
        vec[1] = (int)(cur + 1);
        if (cur != 0) {
            *cur = v;
            return;
        }
    } else {
        ((VecH_00b96600*)vec)->Push(cur, &v);
    }
}

// ===========================================================================
// @ 0x00c72e10
// Rebuild the vehicle and city data lists from the planet's +0xb0 vectors.
// ===========================================================================
void PlanetCls::FUN_00c72e10(char* pd)
{
    void* self = this;
    (void)self;
    int nVeh = *(int**)(pd + 0xb4) - *(int**)(pd + 0xb0);

    char* vehMap[3] = {0, 0, 0};
    if (nVeh > 0) {
        for (int i = 0; i < nVeh; ++i) {
            int v = (*(int**)(pd + 0xb0))[i];
            void* raw = FUN_00f473a0(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
            void* node = raw ? FUN_00ff0db0(v) : 0;
            FUN_00a110b0((void*)v, node);
            if (vehMap[1] < vehMap[2]) {
                int* p = (int*)vehMap[1];
                vehMap[1] = (char*)(p + 1);
                if (p) *p = (int)node;
            } else {
                ((VecH_00b96600*)vehMap)->Push(vehMap[1], &node);
            }
        }
    }

    void* civVec = FUN_00bef6c0();
    int nCity = (((int*)civVec)[1] - ((int*)civVec)[0]) >> 2;

    char* cityMap[3] = {0, 0, 0};
    if (nCity > 0) {
        for (int i = 0; i < nCity; ++i) {
            int v = *(int*)(((int*)civVec)[0] + i * 4);
            void* raw = FUN_00f473a0(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
            void* city = raw ? FUN_00ff23b0(v) : 0;
            void* name = ((void*(__thiscall*)(void*))(*(void***)(v + 0x34))[1])((void*)(v + 0x34));
            WStr_Assign(&cityMap[0], (const uint16_t*)name);
            FUN_00bd81e0(city);
            void* got = FUN_00bd81f0(city);
            if (cityMap[1] < cityMap[2]) {
                int* p = (int*)cityMap[1];
                cityMap[1] = (char*)(p + 1);
                if (p) *p = (int)got;
            } else {
                ((VecH_00b96600*)cityMap)->Push(cityMap[1], &got);
            }
        }
    }

    void* raw = FUN_00f473a0(0x50, "Simulator/cCivData", 0, 0, 0, 0);
    void* civ = raw ? FUN_00ff3220(pd, &vehMap[0], &cityMap[0]) : 0;
    FUN_00b8eec0(civ);
    int n = *(int**)(pd + 0xb4) - *(int**)(pd + 0xb0);
    for (int i = 0; i < n; ++i)
        FUN_00c9eae0(civ);

    if (cityMap[0] && *(int*)(cityMap[0] - 4) != 0)
        FUN_00f47380(cityMap[0]);
    if (vehMap[0] && *(int*)(vehMap[0] - 4) != 0)
        FUN_00f47380(vehMap[0]);
}

// ===========================================================================
// @ 0x00c731a0
// Build a 0x2c-byte entry in the vector at self+0x134, then construct it.
// ===========================================================================
void FUN_00c731a0(void* self, char b2, void* p3, uint16_t w4, char b5,
                  int d6, int d7, int d8, char b9)
{
    char* s = (char*)self;
    char local[0x2c];
    local[0x00] = *(int*)p3;
    local[0x04] = d6;
    local[0x08] = d7;
    local[0x0c] = d8;
    local[0x10] = w4;
    local[0x12] = b2;
    local[0x14] = 0;
    local[0x18] = 0;
    local[0x1c] = 0;
    local[0x20] = 0;
    local[0x24] = 0;
    local[0x28] = (char)((1 << ((b9 != 0) + 3)) | (-(b5 != 0) & 2) | 0x20);

    int* vec = (int*)(s + 0x134);
    if (vec[1] < vec[2]) {
        vec[1] += 0x2c;
        if (vec[1] != 0) {
            DoInsertValue_00ac9200(local);
            return;
        }
    } else {
        char* cur = (char*)vec[1];
        FUN_00acb810(cur, local);
    }
}

// ===========================================================================
// @ 0x00c73250
// ===========================================================================
bool PlanetCls::FUN_00c73250()
{
    return ((PlanetCls*)((TerrainSphere_00f67d90*)SP_NounManager_00b3d300())
                ->GetCurrentTerrainSphere())
        ->FUN_00c72d70((int)((CommRef_00ce6950*)*(void**)((char*)this + 0x13c))->GetCommContext());
}

// ===========================================================================
// @ 0x00c73270
// Push a 12-byte key onto the vector at planet->+0xbc.
// ===========================================================================
void PlanetCls::FUN_00c73270(int* key)
{
    char* p = *(char**)((char*)this + 0x13c);
    int* vec = (int*)(p + 0xbc);
    int* cur = (int*)vec[1];
    if (cur < (int*)vec[2]) {
        vec[1] = (int)(cur + 3);
        if (cur != 0) {
            cur[0] = key[0];
            cur[1] = key[1];
            cur[2] = key[2];
            return;
        }
    } else {
        ((VecH_004e3e10*)vec)->GrowAndAppend(cur, key);
    }
}

// ===========================================================================
// @ 0x00c732c0
// Push a 12-byte key onto the vector at planet->+0xd0.
// ===========================================================================
void PlanetCls::FUN_00c732c0(int* key)
{
    char* p = *(char**)((char*)this + 0x13c);
    int* vec = (int*)(p + 0xd0);
    int* cur = (int*)vec[1];
    if (cur < (int*)vec[2]) {
        vec[1] = (int)(cur + 3);
        if (cur != 0) {
            cur[0] = key[0];
            cur[1] = key[1];
            cur[2] = key[2];
            return;
        }
    } else {
        ((VecH_004e3e10*)vec)->GrowAndAppend(cur, key);
    }
}

// ===========================================================================
// @ 0x00c73310
// Erase the vector at planet->+0xbc.
// ===========================================================================
void PlanetCls::FUN_00c73310()
{
    char* p = *(char**)((char*)this + 0x13c);
    void* e = *(void**)(p + 0xc0);
    void* b = *(void**)(p + 0xbc);
    ((EaVec3*)(p + 0xbc))->erase(b, e);
}

// ===========================================================================
// @ 0x00c73330
// Erase the vector at planet->+0xd0.
// ===========================================================================
void PlanetCls::FUN_00c73330()
{
    char* p = *(char**)((char*)this + 0x13c);
    void* e = *(void**)(p + 0xd4);
    void* b = *(void**)(p + 0xd0);
    ((EaVec3*)(p + 0xd0))->erase(b, e);
}

// ===========================================================================
// @ 0x00c73350
// Erase the 0x10-byte element at *key from the vector at self+4.
// ===========================================================================
int PlanetCls::FUN_00c73350(int* key)
{
    char* s = (char*)this;
    int local[2];
    ((PlanetMap_00c729b0*)this)->find_00c729b0(&local[0], key);
    unsigned cur = (unsigned)local[0];
    if (cur == (unsigned)local[1])
        cur = *(unsigned*)(s + 4);
    unsigned end = *(unsigned*)(s + 4);
    if (cur != end) {
        if ((char*)cur + 0x10 < (char*)end)
            FUN_00705250((void*)((char*)cur + 0x10), (void*)end, (void*)cur);
        *(int*)(s + 4) -= 0x10;
        return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00c733b0
// Simulator::cSpatialObject::Reset -- release sub-objects and clear state.
// ===========================================================================
void PlanetCls::FUN_00c733b0()
{
    char* s = (char*)this;
    void* p = *(void**)(s + 0x188);
    if (p != 0) {
        void* nm = SP_NounManager_00b3d300();
        cGameNounManager_RemoveNoun_00b225d0(nm, p);
        p = *(void**)(s + 0x188);
        if (p != 0) {
            *(void**)(s + 0x188) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
    }
    p = *(void**)(s + 0x154);
    if (p != 0) {
        void* nm = SP_NounManager_00b3d300();
        cGameNounManager_RemoveNoun_00b225d0(nm, p);
        p = *(void**)(s + 0x154);
        if (p != 0) {
            *(void**)(s + 0x154) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
    }
    p = *(void**)(s + 0x18c);
    if (p != 0) {
        void* nm = SP_NounManager_00b3d300();
        cGameNounManager_RemoveNoun_00b225d0(nm, (char*)p + 0xd4);
        p = *(void**)(s + 0x18c);
        if (p != 0) {
            *(void**)(s + 0x18c) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
        }
    }
    p = *(void**)(s + 0x1c0);
    if (p != 0) {
        *(void**)(s + 0x1c0) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    }
    p = *(void**)(s + 0x13c);
    if (p != 0) {
        *(void**)(s + 0x13c) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    *(uint32_t*)(s + 0x148) = g_01693efc;
    *(uint32_t*)(s + 0x14c) = g_01693f00;
    *(uint32_t*)(s + 0x150) = g_01693f04;
    p = *(void**)(s + 0x13c);
    if (p != 0) {
        *(void**)(s + 0x13c) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    char* v = s + 0x170;
    for (int* it = *(int**)v; it != *(int**)(s + 0x174); ++it) {
        void* o = (void*)*it;
        ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
    }
    FUN_00533500(*(void**)v, *(void**)(s + 0x174));
    FUN_00c723d0_local(this);
    p = *(void**)(s + 0x100);
    if (p != 0) {
        *(void**)(s + 0x100) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    FUN_00c8b2e0_00();
}

// ===========================================================================
// @ 0x00c73520
// Collect all cities of every civ on the planet into `out`.
// ===========================================================================
void** PlanetCls::FUN_00c73520(void** out)
{
    out[0] = 0; out[1] = 0; out[2] = 0;
    char* p = *(char**)((char*)this + 0x13c);
    int n = *(int**)(p + 0x160) - *(int**)(p + 0x15c);
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            void* civ = ((void**)*(void**)(p + 0x15c))[i];
            PtrPair* cities = (PtrPair*)((CivData_005c65e0*)civ)->GetCities();
            int m = cities->end - cities->begin;
            for (int j = 0; j < m; ++j) {
                int* src = cities->begin + j;
                if (out[1] < out[2]) {
                    int* d = (int*)out[1];
                    out[1] = d + 1;
                    if (d) *d = *src;
                } else {
                    ((VecH_00b96600*)out)->Push(out[1], src);
                }
            }
        }
    }
    return out;
}

// ===========================================================================
// @ 0x00c735e0
// lower_bound-style lookup of `key` in the map at self+0, returning node+1.
// ===========================================================================
int* PlanetCls::FUN_00c735e0(int* key)
{
    char* s = (char*)this;
    int* beg = *(int**)s;
    int* end = *(int**)(s + 4);
    int* r = (int*)FUN_00d01260(beg, end, key, *(unsigned char*)(s + 0x14));
    if (r == end || *key < *r) {
        int k = *key;
        if (r == end || *r <= k) {
            r = (int*)FUN_00d01260(r, end, &k, *(unsigned char*)(s + 0x14));
        } else {
            r = (int*)FUN_00d01260(beg, r, &k, *(unsigned char*)(s + 0x14));
        }
        if (r == end || k < *r)
            FUN_00c72d00(r, &k);
    }
    return r + 1;
}

// ===========================================================================
// @ 0x00c73680
// Simulator::cPlanet destructor.
// ===========================================================================
void PlanetCls::FUN_00c73680()
{
    char* s = (char*)this;
    *(void**)s = &vtbl_CPlanet_014725d8;
    *(void**)(s + 0xd4) = &vtbl_CPlanet_gd_01472580;
    *(void**)(s + 0xd8) = &vtbl_CPlanet_d8_01472570;
    void* sm = SP_StarManager_00b3d2a0(s);
    FUN_00ba70d0(sm);
    FUN_00c733b0();

    void* p = *(void**)(s + 0x1c0);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    cGonzagoTimer_dtor_00b638b0(s + 0x198);
    p = *(void**)(s + 0x18c);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    p = *(void**)(s + 0x188);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    FUN_004b5440(s + 0x170);
    {
        int* a = *(int**)(s + 0x15c);
        int* b = *(int**)(s + 0x164);
        int d = ((char*)b - (char*)a) & 0xfffffffe;
        if (d > 2 && a != 0)
            FUN_00f47380(a);
    }
    p = *(void**)(s + 0x154);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = *(void**)(s + 0x13c);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    int* m = *(int**)(s + 0x138);
    if (m != 0) {
        if (m[0x40 / 4] > 1) {
            m[0x40 / 4] -= 1;
            cGameData_dtor_00b184c0(s + 0xd4);
            FUN_00c8a420();
            return;
        }
        unsigned f = (unsigned)m[1] >> 31;
        ((void(__thiscall*)(void*, unsigned))(*(void***)m)[0x170 / 4])(m, f);
    }
    cGameData_dtor_00b184c0(s + 0xd4);
    FUN_00c8a420();
}

// ===========================================================================
// @ 0x00c737a0
// ===========================================================================
void FUN_00c737a0(void* self, void* a, void* b)
{
    char* s = (char*)self;
    void* pd = *(void**)(s + 0x13c);
    void* gd = FUN_00b8de30(pd);
    FUN_00a16a90(gd);
    void* sm = SP_StarManager_00b3d2a0(b);
    (void)sm;
    (void)a;
}

// ===========================================================================
// @ 0x00c73b60
// Rebuild the planet's tribe and city data.
// ===========================================================================
void PlanetCls::FUN_00c73b60()
{
    char* s = (char*)this;
    FUN_00b8de60(*(void**)(s + 0x13c));
    FUN_00b8df20(*(void**)(s + 0x13c));

    void* nm = SP_NounManager_00b3d300();
    void* vec = SP_cGameNounManager_GetGameDataVector(nm, (void*)0x00b21080, (void*)0x00d3d420,
                                                      (void*)0x00b236c0, (void*)0x00b1e500,
                                                      (void*)0x018c816a);
    int n = *(int**)((char*)vec + 8) - *(int**)((char*)vec + 4);
    for (int i = 0; i < n; ++i) {
        char* t = *(char**)(*(int**)((char*)vec + 4) + i * 4);
        void* civ = FUN_00bef6c0();
        if (*(int*)civ != *(int*)((char*)civ + 4) ||
            *(int*)(t + 0xb0) != *(int*)(t + 0xb4))
            FUN_00c72e10(t);
    }

    void* vec2 = SP_cGameNounManager_GetGameDataVector(nm, (void*)0x00cd7d10, (void*)0x00d3d420,
                                                       (void*)0x00accbb0, (void*)0x00b1e500,
                                                       (void*)0x018c6d19);
    int n2 = *(int**)((char*)vec2 + 8) - *(int**)((char*)vec2 + 4);
    for (int i = 0; i < n2; ++i) {
        int v = *(int*)(*(int**)((char*)vec2 + 4) + i * 4);
        void* raw = FUN_00f473a0(0x18, "Simulator/cTribeData", 0, 0, 0, 0);
        void* td = raw ? cTribeData_ctor_00ff0610(v) : 0;
        FUN_00c8ea30((void*)v, td);
        FUN_00b8ef00(*(void**)(s + 0x13c), td);
    }
}
