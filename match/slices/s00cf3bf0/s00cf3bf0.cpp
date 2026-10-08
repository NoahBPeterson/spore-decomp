// Slice s00cf3bf0 - SP::cCityInputStrategy::DoObjectInteraction (city mode: click/drag an object).
// Flags /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

struct Vec3 { float x, y, z; };
void __cdecl operator delete[](void*);             // 0x00f47380

// ---- virtual-call helpers (vtable slot by byte offset, thiscall) -------------------------------
template <class R> static inline R VC0(void* o, int off)
{ return ((R(__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template <class R, class A> static inline R VC1(void* o, int off, A a)
{ return ((R(__thiscall*)(void*, A))(*(void***)o)[off / 4])(o, a); }

// ---- stubs -------------------------------------------------------------------------------------
struct Obj {                       // cast-capable game object; Cast() is vtable slot 3
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void* Cast(uint32_t id);
};

struct Vehicle {                   // SP::cVehicle (fields used here)
    char pad[0xb1c];
    int  mbFlagB1C;                // +0xb1c
    int  mState;                   // +0xb20
    bool Func_C9FE40(void* o);                    // 0x00c9fe40
    void Func_CAC000(void* o, int a, int b);      // 0x00cac000
    void Func_C9EE30(int id);                     // 0x00c9ee30
    bool CanOccupyTerrain(const Vec3* pos);       // 0x00c9e960
    bool Func_CA8340(void* x);                    // 0x00ca8340
    void Func_CA80E0(int a);                      // 0x00ca80e0
};
struct ObjB {
    void Func_BD1AB0(int a);  // 0x00bd1ab0
};
struct TerrainSphere {
    void Func_C77BF0(uint32_t id);  // 0x00c77bf0
};
struct NounMgr {
    TerrainSphere* GetCurrentTerrainSphere();  // 0x00f67d90
};
struct IdSource {
    int NextId();  // 0x00ac15e0
};
struct PlanetModel {
    int GetContinent(const Vec3* pos);  // 0x00b88590
};
struct EventLog {
    void RemoveAllEventsOfSameType(uint32_t type, int a, int b);  // 0x00dd7620
};
struct CivModeStrategy {
    bool HasCivTutorialOccurred(uint32_t id);                  // 0x00cf7830
    void DoNextCivTutorial(uint32_t id, int a);                // 0x00cfa990
};
struct AudioSystem {                                           // vtable slot 0x20 = GetToken
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void* GetToken();
};
struct Release_ { virtual void s0(); virtual void s1(); };

NounMgr*       __cdecl NounManager();             // 0x00b3d300
EventLog*      __cdecl GetEventLog();             // 0x00b3d3e0
IdSource*      __cdecl GetIdSource();             // 0x00b3d290
PlanetModel*   __cdecl GetPlanetModel();          // 0x00b3d350
CivModeStrategy* __cdecl GetCivModeStrategy();    // 0x00cf74c0
AudioSystem*   __cdecl GetSystemAT();             // 0x00a206f0
void*          __cdecl GetRecorderState();        // 0x00435e90
void           __cdecl KillSetiEffects(uint32_t hash, void* state);          // 0x00435ed0
void           __cdecl Start3dSoundByName(uint32_t hash, void* state, Vec3 pos);  // 0x00571f80
Vehicle*       __cdecl CastVehicle(void** it);    // 0x00bd8440
void*          __cdecl Func_BCE5C0(void* x);      // 0x00bce5c0 (thiscall on x, no args)

struct ObjVec {                    // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
    Obj** mpBegin; Obj** mpEnd; Obj** mpCap;
    void Destroy();                // 0x00ad92d0 (out-of-line ~vector)
};
void* __cdecl GetGameTerrainCursor();             // 0x00b30d70

struct VRef {                      // EA::AutoRefCount<cVehicle>
    Vehicle* p;
    VRef(Vehicle* v);              // 0x00572660
    ~VRef() { if (p) VC0<void>(p, 4); }
};
struct VRefInline {                // same object, constructed inline (AddRef of a known non-null pointer)
    Vehicle* p;
    VRefInline(Vehicle* v) { p = v; VC0<void>(v, 0); }
    ~VRefInline() { if (p) VC0<void>(p, 4); }
};
struct VehVec {                    // eastl::vector<AutoRefCount<cVehicle>, sp_vector_allocator>
    Vehicle** mpBegin; Vehicle** mpEnd; Vehicle** mpCap;
    void erase(Vehicle** first, Vehicle** last);          // 0x00e25bd0
    void push_back(VRef* v);                              // 0x00e1c7f0
    void DoInsertValue(Vehicle** pos, Vehicle** v);       // 0x00aea5d0
};

struct CityInputStrategy {
    char   pad[0xe8];
    VehVec mSelected;                                     // +0xe8
    void Func_CF30B0(Obj* target, Vec3 pos, int flag);    // 0x00cf30b0
    int  DoObjectInteraction(Obj* pObj, int arg2);
};

// @ 0x00cf3bf0
int CityInputStrategy::DoObjectInteraction(Obj* pObj, int arg2)
{
    if (!pObj)
        return 0;

    Obj*  pAnimal = (Obj*)pObj->Cast(0xd0036e08);
    Obj*  pB      = (Obj*)pObj->Cast(0x0e9cb8ba);
    if (pB) {
        if (pB->Cast(0x1007ae63))
            pB = 0;
    }
    Obj*  pE      = (Obj*)pObj->Cast(0x00ee02c7);
    pObj->Cast(0x137e8e0);
    pObj->Cast(0x4f176642);
    pObj->Cast(0x116d858);
    pObj->Cast(0x629baec);

    ObjVec objects;
    objects.mpBegin = 0; objects.mpEnd = 0; objects.mpCap = 0;
    VC1<void, ObjVec*>(GetGameTerrainCursor(), 0x5c, &objects);   // GetObjectsUnderCursor
    if (objects.mpBegin == objects.mpEnd) {
        objects.Destroy();
        return 0;
    }
    if (!VC1<void*, uint32_t>(*objects.mpBegin, 0xb8, 0x137e8e0)) {
        objects.Destroy();
        return 0;
    }

    bool bAny = false;
    Obj* pC = (Obj*)pObj->Cast(0x436f315);
    Obj* pD = (Obj*)pObj->Cast(0x403df5f);
    int  nextId = GetIdSource()->NextId();

    if (!pB && !pC && !pAnimal) {
        if (pD) {
            bool bFlag = false;
            int id = VC0<int>(pD, 0x4c);
            Obj** it = objects.mpBegin;
            if (it != objects.mpEnd) {
                do {
                    Vehicle* v = CastVehicle((void**)it);
                    if (bFlag || v->mState == 2)
                        bFlag = true;
                    if (id == -1) {
                        if (v->Func_C9FE40(pD)) {
                            NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f2);
                            v->Func_CAC000(pD, 8, 1);
                            bAny = true;
                            GetEventLog()->RemoveAllEventsOfSameType(0x6889d3f5, 0, 0);
                        }
                    } else {
                        int st = v->mState;
                        if (st == 0 || st == 1) {
                            if (VC0<int>(v, 0x4c) != id) {
                                if (v->Func_C9FE40(pD)) {
                                    NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x57fbc70);
                                    v->Func_CAC000(pObj, 1, 1);
                                    v->Func_C9EE30(nextId);
                                    bAny = true;
                                }
                            }
                        }
                    }
                    ++it;
                } while (it != objects.mpEnd);
                if (!bAny) {
                    if (!bFlag)
                        KillSetiEffects(0x594303b7, GetRecorderState());
                } else {
                    Vec3* p = VC0<Vec3*>((char*)pD + 0x34, 0x2c);
                    Start3dSoundByName(0xc6f2fe9b, GetRecorderState(), *p);
                }
            } else {
                KillSetiEffects(0x594303b7, GetRecorderState());
            }
        } else if (pE) {
            char* pEpos = (char*)pE + 0x34;
            if (!*((char*)VC0<char*>(pE, 0x58) + 0x557)) {
                Obj** it = objects.mpBegin;
                if (it != objects.mpEnd) {
                    do {
                        Vehicle* v = CastVehicle((void**)it);
                        if (v->CanOccupyTerrain(VC0<Vec3*>(pEpos, 0x2c))) {
                            NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x57fbc6b);
                            v->Func_CAC000(pObj, 8, 1);
                            v->Func_C9EE30(nextId);
                            bAny = true;
                        }
                        ++it;
                    } while (it != objects.mpEnd);
                    if (!bAny) {
                        KillSetiEffects(0x594303b7, GetRecorderState());
                    } else {
                        Vec3* p = VC0<Vec3*>(pEpos, 0x2c);
                        Start3dSoundByName(0x5580e0f9, GetRecorderState(), *p);
                    }
                } else {
                    KillSetiEffects(0x594303b7, GetRecorderState());
                }
            }
        }
    } else {
        mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
        for (Obj** it = objects.mpBegin; it != objects.mpEnd; ++it) {
            Obj* o = *it;
            if (!o) continue;
            Vehicle* v = (Vehicle*)VC1<void*, uint32_t>(o, 0xb8, 0x137e8e0);
            if (!v) continue;
            if ((pB || pC) && (v->mState == 0 || v->mState == 1)) {
                void* x;
                if (pB)
                    x = VC0<void*>(pB, 0x84);
                else
                    x = Func_BCE5C0(pC);
                if (v->mbFlagB1C != 0 || v->Func_CA8340(x)) {
                    VRefInline ref(v);
                    mSelected.push_back((VRef*)&ref);
                }
            } else if (pAnimal) {
                int st = v->mState;
                if (st == 0 || st == 1) {
                    if (v->mbFlagB1C != 0 || v->CanOccupyTerrain(VC0<Vec3*>((char*)pAnimal + 0xc0, 0x2c))) {
                        VRef ref(v);
                        mSelected.push_back(&ref);
                    }
                }
            }
        }
        if (mSelected.mpBegin != mSelected.mpEnd) {
            Obj* q = (Obj*)pObj->Cast(0x1186577);
            if (q) {
                if (pB || pC || pAnimal) {
                    Vec3* pp = VC0<Vec3*>(q, 0x2c);
                    Func_CF30B0(pObj, *pp, 1);
                    if (pAnimal)
                        NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x57fbc60);
                    else
                        NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f6);
                    bAny = true;
                    char* src;
                    if (pB) src = (char*)pB + 0x34;
                    else if (pC) src = (char*)pC + 0x34;
                    else src = 0;
                    if (src) {
                        Vec3 p2 = *VC0<Vec3*>(src, 0x2c);
                        AudioSystem* at = GetSystemAT();
                        void* tok = at ? at->GetToken() : 0;
                        Start3dSoundByName(0x8216c026, tok, p2);
                        if (pB)
                            ((ObjB*)pB)->Func_BD1AB0(2);
                    }
                }
            }
        }
    }

    // Step 2: pick up vehicles when the clicked object itself is a vehicle.
    Vehicle* pV = (Vehicle*)pObj->Cast(0x137e8e0);
    bool bTutorial = bAny;
    if (pV) {
        mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
        for (Obj** it = objects.mpBegin; it != objects.mpEnd; ++it) {
            Obj* o = *it;
            if (!o) continue;
            Vehicle* v = (Vehicle*)VC1<void*, uint32_t>(o, 0xb8, 0x137e8e0);
            if (!v) continue;
            if (v->mState == 2) continue;
            if (v->mbFlagB1C == 0 && pV->mbFlagB1C == 0) {
                PlanetModel* pm = GetPlanetModel();
                if (pm) {
                    int c1 = pm->GetContinent(VC0<Vec3*>((char*)pV + 0x34, 0x2c));
                    int c2 = pm->GetContinent(VC0<Vec3*>((char*)v + 0x34, 0x2c));
                    if (c2 != c1) continue;
                }
            }
            Vehicle* ref = v;
            VC0<void>(ref, 0);                         // AddRef
            if (mSelected.mpEnd < mSelected.mpCap) {
                Vehicle** slot = mSelected.mpEnd++;
                if (slot) {
                    *slot = v;
                    VC0<void>(v, 0);
                }
            } else {
                mSelected.DoInsertValue(mSelected.mpEnd, &ref);
            }
            if (ref) VC0<void>(ref, 4);                // Release
        }
        if (mSelected.mpBegin != mSelected.mpEnd) {
            Vec3 p = *VC0<Vec3*>((char*)pV + 0x34, 0x2c);
            Func_CF30B0(pObj, p, 1);
            pV->Func_CA80E0(0xb);
            AudioSystem* at = GetSystemAT();
            void* tok = at ? at->GetToken() : 0;
            Start3dSoundByName(0x8541328e, tok, p);
            bTutorial = true;
        }
    }

    if (bTutorial) {
        CivModeStrategy* cs = GetCivModeStrategy();
        if (cs->HasCivTutorialOccurred(0x64e667b))
            cs->DoNextCivTutorial(0x64e667d, 1);
    }

    // inlined ~vector: release every element, then free the block
    for (Obj** p = objects.mpBegin; p < objects.mpEnd; ++p) {
        if (*p) VC0<void>(*p, 0xc0);
    }
    if (objects.mpBegin && ((int*)objects.mpBegin)[-1])
        operator delete[](objects.mpBegin);
    return 0;
}
