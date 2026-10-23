// Slice s00bf8710: SP civilization superweapon-AI helpers (pick a target, gate and fire a
// superweapon) plus the EASTL vector<FunctionalMatch::Constraint> operations they lean on
// (insert / find-or-insert / resize).  Recovered names are descriptive; only the behaviour and
// the member offsets are known (no DB names for any of the six VAs).
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <math.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- opaque game types
struct cSPTimer { void Restart(); };
struct cGameNounManager;
struct cPlanetModel;
struct cCommunity;
struct cVehicle;
struct cSimSingleton;
struct ObjectTemplateDB_t;

struct Constraint { uchar m[0x24]; };

// EASTL vector<Constraint, sp_vector_allocator> header (begin/end/capacity).
struct ConstraintVector {
    Constraint* mBegin;   // +0x00
    Constraint* mEnd;     // +0x04
    Constraint* mCap;     // +0x08
    void insert(Constraint* pos, uint count, const Constraint* value);  // 0x00bf8dd0
    void resize(uint count);                                            // 0x00bf9250
};

// ---------------------------------------------------------------- external helpers
namespace EA { namespace Random {
    struct RandomLinearCongruential { unsigned int RandomUint32Uniform(unsigned int n); };
} }

// ---------------------------------------------------------------- globals
extern char  g_bd6c;                 // 0x0168bd6c  "superweapons disabled" flag
extern Vec3  g_c514;                 // 0x0168c514  "no position" sentinel
extern int   g_167a60c;              // 0x0167a60c  cached SimSingleton*
extern char  g_14692d8[];            // 0x014692d8  per-type table (8-byte stride)
extern EA::Random::RandomLinearCongruential gMathRandom;  // 0x01601760

cGameNounManager* SP_NounManager();                                    // 0x00b3d300
int* GetGameDataVector(cGameNounManager*, int, int, int, int, int);    // 0x00b21340
cPlanetModel*     SP_PlanetModel(void*);                               // 0x00b3d350
void*             GetContinent(cPlanetModel*);                         // 0x00b88590
void*             GetPlayerCivilization(cGameNounManager*);            // 0x00b25fb0
bool  AI_ShouldReact(int type);                                        // 0x00bf7730
bool  SuperweaponOnCooldown(int type);                                 // 0x00bf1790
bool  Vehicle_CanOccupyTerrain(cVehicle*, void*);                      // 0x00c9e960
int   FUN_00ca71d0(void*);                                             // 0x00ca71d0
bool  FUN_00c9f410(void*);                                             // 0x00c9f410
bool  FUN_00c9fe40(void*, void*);                                      // 0x00c9fe40
void  FUN_00cac000(void*, int, int);                                   // 0x00cac000
void* GetNoun(cCommunity*);                                            // 0x00bfdf80
bool  FUN_00bda080(int);                                               // 0x00bda080
void  FUN_00be5be0(int, void*);                                        // 0x00be5be0
float FUN_00bf6cb0(int);                                               // 0x00bf6cb0
void  FUN_00ae37c0_ret();                                              // 0x00ae37c0
void  FUN_007eb820(int);                                               // 0x007eb820
void  FUN_00e3c7c0(int, void*);                                        // 0x00e3c7c0
void  FUN_00401090(void*, ...);                                        // 0x00401090
void* FUN_004df550(void*);                                             // 0x004df550
void  FUN_0067cb30(int, void*, int, int);                              // 0x0067cb30
void  FUN_0060f370(void*, void*, int, int);                            // 0x0060f370
void* SP_ObjectTemplateDB();                                           // 0x0067cb40
void  FUN_00bf6e80(void*, void*, const void*);                         // 0x00bf6e80
void* FUN_00ae37c0(int, float, float, float);                          // 0x00ae37c0

// EASTL / allocator helpers
void* operator_new(int, const char*, int, int, int, int);              // 0x00f473a0
void  operator_delete__(void*);                                        // 0x00f47380
void  FUN_004e38d0(void*);                                             // 0x004e38d0
void  __fastcall FUN_004e39a0(void*, int, void*, void*);               // 0x004e39a0  DoDestroyValues
void  FUN_004e39d0(void*);                                             // 0x004e39d0
void  FUN_004e4700(void*, uint, const void*, void*);                   // 0x004e4700
void* FUN_004e4b90(void*, void*, void*);                               // 0x004e4b90
void  FUN_004e4ad0(void*, void*, void*, void*, void*);                 // 0x004e4ad0
void  FUN_004e4f60(void*, void*, void*);                               // 0x004e4f60
void  FUN_006066f0();                                                  // 0x006066f0
void  FUN_00606730(void*, void*, void*);                               // 0x00606730
void  FUN_00606880(void*);                                             // 0x00606880
void* __fastcall FUN_005587f0(void*, int);                             // 0x005587f0  Constraint::Constraint()
void  __fastcall FUN_00565b50(void*, int, void*, void*);               // 0x00565b50  vector::erase(first,last)
void  Constraint_ctor(void*, uint, int, int);                          // 0x00558960

// ---------------------------------------------------------------- the civilization
struct cCivilization {
    uchar pad00[0x89];
    uchar m89;                 // +0x89
    uchar pad8a[0x98 - 0x8a];
    float m98;                 // +0x98
    void** mV9c;               // +0x9c  vector<*>::begin
    void** mV9cEnd;            // +0xa0
    uchar padA4[0xb0 - 0xa4];
    void** mVb0;               // +0xb0  vector<*> (entities)
    void** mVb0End;            // +0xb4
    uchar padB8[0x468 - 0xb8];
    void* mp468;               // +0x468
    uchar pad46c[0x484 - 0x46c];
    uchar m484[0x0c];          // +0x484  per-type "available" flags
    cSPTimer* mp490;           // +0x490  timer array (stride 0x20)
    uchar pad494[0x4ac - 0x494];
    float m4ac;                // +0x4ac
    float m4b0;                // +0x4b0
    uchar pad4b4[0x4cc - 0x4b4];
    uchar m4cc;                // +0x4cc

    void PickSuperweaponTarget();                 // 0x00bf8710
    bool CanUseSuperweapon(int type);             // 0x00bf8a00
    void UseSuperweapon(int type, Vec3* pos);     // 0x00bf8a70
    bool city_on_continent(void* cont);           // 0x00bf00a0
    bool ShouldReact(int type);                   // 0x00bf7730
    bool SuperweaponOnCooldown(int type);         // 0x00bf1790
};

// @ 0x00bf8710
void cCivilization::PickSuperweaponTarget()
{
    if (gMathRandom.RandomUint32Uniform(10) != 0)
        goto tail;

    {
        cGameNounManager* mgr = SP_NounManager();
        int* vec = GetGameDataVector(mgr, 0x00cd7d10, 0x00d3d420, 0x00bf6e00, 0x00b1e500, 0x1e4daae);
        int count = (vec[2] - vec[1]) >> 2;
        int i = 0;
        if (count > 0) {
            int** begin = (int**)vec[1];
            do {
                int* obj = begin[i];
                int st = (*(int (__fastcall**)(void*, int))(*(int*)obj + 0x58))(obj, 0);
                if (*(char*)(st + 0x557) == 0) {
                    void* a = (*(void* (__fastcall**)(void*, int, int))(*(int*)(obj + 0x34) + 0x2c))(obj + 0x34, 0, -1);
                    cPlanetModel* pm = SP_PlanetModel(a);
                    if (city_on_continent(GetContinent(pm))) {
                        // already-tracked scan
                        void** e = mVb0End;
                        void** p = mVb0;
                        for (; p != e; ++p) {
                            void* ent = *p;
                            if (ent != 0 && *(int*)(FUN_00ca71d0(ent) + 0x10) == 8 &&
                                *(int*)FUN_00ca71d0(ent) == (int)obj)
                                goto advance;
                        }
                        // free-slot scan
                        e = mVb0End;
                        for (p = mVb0; p != e; ++p) {
                            cVehicle* veh = (cVehicle*)*p;
                            if (veh != 0 && !FUN_00c9f410(veh)) {
                                void* b = (*(void* (__fastcall**)(void*, int))(*(int*)(obj + 0x34) + 0x2c))(obj + 0x34, 0);
                                if (Vehicle_CanOccupyTerrain(veh, b) &&
                                    *(int*)(FUN_00ca71d0(veh) + 0x10) == 0) {
                                    FUN_00cac000(obj, 8, 0);
                                    break;
                                }
                            }
                        }
                    }
                }
advance:
                ++i;
            } while (i < count);
        }
    }

tail:
    {
        void** e = mVb0End;
        void** p = mVb0;
        if (mp468 == 0) {
            for (; p != e; ++p) {
                void* ent = *p;
                if (ent != 0 && *(int*)(FUN_00ca71d0(ent) + 0x10) == 8) {
                    int* c = (int*)FUN_00ca71d0(ent);
                    if (*c != 0) {
                        int r = (*(int (__fastcall**)(int*, int, int))(*(int*)*c + 0xc))((int*)*c, 0, 0x403df5f);
                        if (r != 0)
                            FUN_00cac000(ent, 0, 0);
                    }
                }
            }
        } else {
            for (; p != e; ++p) {
                void* ent = *p;
                if (ent != 0 && *(int*)(FUN_00ca71d0(ent) + 0x10) == 8) {
                    int* c = (int*)FUN_00ca71d0(ent);
                    if (*c != 0 &&
                        (*(int (__fastcall**)(int*, int, int))(*(int*)*c + 0xc))((int*)*c, 0, 0x403df5f) != 0 &&
                        GetNoun((cCommunity*)(*(int (__fastcall**)(int*, int, int))(*(int*)*c + 0xc))((int*)*c, 0, 0x403df5f)) != 0)
                        FUN_00cac000(ent, 0, 0);
                }
            }
            e = mVb0End;
            for (p = mVb0; p != e; ++p) {
                void* ent = *p;
                if (ent != 0 && *(int*)(FUN_00ca71d0(ent) + 0x10) == 8) {
                    int* c = (int*)FUN_00ca71d0(ent);
                    if (*c == (int)mp468)
                        return;
                }
            }
            e = mVb0End;
            for (p = mVb0; p != e; ++p) {
                void* ent = *p;
                if (ent != 0 && FUN_00c9fe40(ent, mp468) &&
                    *(int*)(FUN_00ca71d0(ent) + 0x10) == 8)
                    continue;
                if (ent == 0 || !FUN_00c9fe40(ent, mp468) ||
                    *(int*)(FUN_00ca71d0(ent) + 0x10) == 8)
                    continue;
            }
            for (p = mVb0; p != e; ++p) {
                void* ent = *p;
                if (ent != 0 && FUN_00c9fe40(ent, mp468) &&
                    *(int*)(FUN_00ca71d0(ent) + 0x10) != 8) {
                    FUN_00cac000(mp468, 8, 0);
                    return;
                }
            }
        }
    }
}

// @ 0x00bf8a00
bool cCivilization::CanUseSuperweapon(int type)
{
    if (type == -1)
        return false;
    if (g_bd6c != 0)
        return true;
    if ((type == 2 || type == 5 || type == 8) && m4cc != 0)
        return false;
    return m484[type] != 0 && ShouldReact(type) && !SuperweaponOnCooldown(type);
}

// @ 0x00bf8a70
void cCivilization::UseSuperweapon(int type, Vec3* pos)
{
    if (!CanUseSuperweapon(type))
        return;

    int count = (int)((uchar*)mV9cEnd - (uchar*)mV9c) >> 2;
    int best = -1;
    float bestDist = 3.402823466e38f;
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            if (!FUN_00bda080(type))
                continue;
            if (pos->x == g_c514.x && pos->y == g_c514.y && pos->z == g_c514.z) {
                best = i;
                break;
            }
            void* o = mV9c[i];
            float* p = (float*)(*(void* (__fastcall**)(void*, int))(*(int*)((int)o + 0x120) + 0x2c))((void*)((int)o + 0x120), 0);
            float dx = p[0] - pos->x;
            float dy = p[1] - pos->y;
            float dz = p[2] - pos->z;
            float d = sqrtf(dx * dx + dy * dy + dz * dz);
            if (d < bestDist) {
                best = i;
                bestDist = d;
            }
        }
        if (best != -1) {
            FUN_00be5be0(type, pos);
            void* o = mV9c[best];
            float* p = (float*)(*(void* (__fastcall**)(void*, int))(*(int*)((int)o + 0x120) + 0x2c))((void*)((int)o + 0x120), 0);
            float px = p[0], py = p[1], pz = p[2];

            if (g_167a60c == 0) {
                int s = (int)operator_new(200, "Simulator/SimSingleton", 0, 0, 0, 0);
                g_167a60c = (s == 0) ? 0 : s;
            }
            void* sim = (void*)FUN_00ae37c0(0x0e, px, py, pz);
            (void)sim;
            FUN_007eb820(10);

            if (g_bd6c == 0) {
                float f = FUN_00bf6cb0(type);
                float v = m98 - f;
                m98 = v;
                if (m89 == 0 && v < 0.0f) {
                    m98 = (m4ac + v) + m4b0;
                    m4ac = 0.0f;
                    m4b0 = 0.0f;
                }
                mp490[type].Restart();
                if (type == 2 || type == 5 || type == 8)
                    m4cc = 1;
            }
            if (GetPlayerCivilization(SP_NounManager()) == this) {
                int* civ = (int*)GetPlayerCivilization(SP_NounManager());
                (void)civ;
            }
        }
    }
}

// @ 0x00bf8dd0
void ConstraintVector::insert(Constraint* pos, uint count, const Constraint* value)
{
    uint cap = (uint)(((uchar*)mCap - (uchar*)mBegin) / 0x24);
    if (cap < count) {
        int n = (int)(((uchar*)mEnd - (uchar*)mBegin) / 0x24);
        uint newCap = (uint)(n * 2);
        if (n == 0)
            newCap = 1;
        uint need = (uint)n + count;
        if (need < newCap)
            need = newCap;
        Constraint* buf;
        if (need == 0)
            buf = 0;
        else
            buf = (Constraint*)operator_new((int)(need * 0x24), "Simulator", 0, 0, 0, 0xd1);
        Constraint* a = mBegin;
        Constraint* mid = (Constraint*)FUN_004e4b90(a, pos, buf);
        FUN_00606730(a, pos, buf);
        FUN_004e4700(mid, count, value, mid);
        Constraint* tail = (Constraint*)((uchar*)mid + count * 0x24);
        Constraint* oldEnd = mEnd;
        Constraint* b = (Constraint*)FUN_004e4b90(pos, mEnd, tail);
        FUN_00606730(pos, oldEnd, tail);
        Constraint* oldBegin = mBegin;
        if (oldBegin != 0 && *(int*)((uchar*)oldBegin - 4) != 0)
            operator_delete__(oldBegin);
        mBegin = buf;
        mEnd = b;
        mCap = (Constraint*)((uchar*)buf + need * 0x24);
    } else if (count != 0) {
        Constraint tmp;
        *(int*)&tmp.m[0] = *(const int*)&value->m[0];
        *(int*)&tmp.m[4] = *(const int*)&value->m[4];
        *(int*)&tmp.m[8] = *(const int*)&value->m[8];
        *(int*)&tmp.m[0xc] = *(const int*)&value->m[0xc];
        FUN_004e38d0((void*)((uchar*)value + 0x10));
        uint used = (uint)(((uchar*)mEnd - (uchar*)pos) / 0x24);
        if (count < used) {
            Constraint* at = (Constraint*)((uchar*)mEnd - count * 0x24);
            FUN_004e4ad0(&value, at, mEnd, mEnd, 0);
            mEnd = (Constraint*)((uchar*)mEnd + count * 0x24);
            FUN_004e4f60(pos, at, mEnd);
            FUN_00bf6e80((void*)pos, (void*)((uchar*)pos + count * 0x24), &tmp);
            FUN_006066f0();
            return;
        }
        FUN_004e4700(mEnd, count - used, &tmp, pos);
        mEnd = (Constraint*)((uchar*)mEnd + (count - used) * 0x24);
        FUN_004e4ad0(&pos, pos, mEnd, mEnd, pos);
        mEnd = (Constraint*)((uchar*)mEnd + used * 0x24);
        FUN_00bf6e80((void*)pos, mEnd, &tmp);
        FUN_006066f0();
    }
}

// @ 0x00bf9250
void ConstraintVector::resize(uint count)
{
    uint size = (uint)(((uchar*)mEnd - (uchar*)mBegin) / 0x24);
    if (size < count) {
        Constraint tmp;
        Constraint* v = (Constraint*)FUN_005587f0(&tmp, 0);
        insert(mEnd, count - size, v);
        ConstraintVector* iv = (ConstraintVector*)((uchar*)&tmp + 0x10);
        FUN_004e39a0(iv, 0, iv->mBegin, iv->mEnd);
        if (iv->mBegin != 0 && *(int*)((uchar*)iv->mBegin - 4) != 0)
            operator_delete__(iv->mBegin);
    } else {
        FUN_00565b50(this, 0, (uchar*)mBegin + count * 0x24, mEnd);
    }
}

// @ 0x00bf8ff0
void ConstraintVectorFindOrInsert(ConstraintVector* vec, uint key, Constraint* out)
{
    ConstraintVector found;
    found.mBegin = 0;
    found.mEnd = 0;
    found.mCap = 0;
    ObjectTemplateDB_t* db = (ObjectTemplateDB_t*)SP_ObjectTemplateDB();

    if (key == 0x2090a11b) {
        Constraint tmp;
        Constraint_ctor(&tmp, 0x5c96ff0, 0, 0x5c972f1);
        if ((uint)vec->mEnd < (uint)vec->mCap) {
            Constraint* e = vec->mEnd;
            vec->mEnd = (Constraint*)((uchar*)e + 0x24);
            if (e != 0)
                FUN_00606880(&tmp);
        } else {
            FUN_004e39d0(vec->mEnd);
        }
        FUN_004e39a0(0, 0, 0, 0);
    } else if (key == 0xbc1041e6) {
        Constraint tmp;
        Constraint_ctor(&tmp, 0x5c96ff0, 0, 0x5c972ea);
        if ((uint)vec->mEnd < (uint)vec->mCap) {
            Constraint* e = vec->mEnd;
            vec->mEnd = (Constraint*)((uchar*)e + 0x24);
            if (e != 0)
                FUN_00606880(&tmp);
        } else {
            FUN_004e39d0(vec->mEnd);
        }
        FUN_006066f0();
    } else if (key == 0xc15695da) {
        Constraint tmp;
        Constraint_ctor(&tmp, 0x5c96ff0, 0, 0x5c972ee);
        if ((uint)vec->mEnd < (uint)vec->mCap) {
            Constraint* e = vec->mEnd;
            vec->mEnd = (Constraint*)((uchar*)e + 0x24);
            if (e != 0)
                FUN_00606880(&tmp);
        } else {
            FUN_004e39d0(vec->mEnd);
        }
        FUN_006066f0();
    }

    (*(void (__fastcall**)(ObjectTemplateDB_t*, int, ConstraintVector*, int))(*(int*)db + 0x24))(db, 0, &found, 1);

    if (found.mBegin == vec->mBegin) {
        vec->mEnd = (Constraint*)((uchar*)vec->mEnd - 0x24);
        Constraint* last = vec->mEnd;
        FUN_004e39a0(0, 0, *(void**)((uchar*)last + 0x10), *(void**)((uchar*)last + 0x14));
        void* sub = *(void**)((uchar*)last + 0x10);
        if (sub != 0 && *(int*)((uchar*)sub - 4) != 0)
            operator_delete__(sub);

        Constraint tmp;
        Constraint_ctor(&tmp, 0x2dc9d1e, 0, 0x8f963dcb);
        if ((uint)vec->mEnd < (uint)vec->mCap) {
            Constraint* e = vec->mEnd;
            vec->mEnd = (Constraint*)((uchar*)e + 0x24);
            if (e != 0)
                FUN_00606880(&tmp);
        } else {
            FUN_004e39d0(vec->mEnd);
        }
        FUN_004e39a0(0, 0, 0, 0);
        (*(void (__fastcall**)(ObjectTemplateDB_t*, int, ConstraintVector*, int))(*(int*)db + 0x24))(db, 0, &found, 1);
        if (found.mBegin == vec->mBegin)
            goto done;
    }

    out->m[0] = found.mBegin->m[0];
    *(int*)&out->m[0] = *(int*)&found.mBegin->m[0];
    *(int*)&out->m[4] = *(int*)&found.mBegin->m[4];
    *(int*)&out->m[8] = *(int*)&found.mBegin->m[8];

done:
    if (found.mBegin != 0 && *(int*)((uchar*)found.mBegin - 4) != 0)
        operator_delete__(found.mBegin);
}
