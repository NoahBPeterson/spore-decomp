// Slice s00c87be0 -- Simulator cGameData/cCommunity/cSpatialObject view helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);

// ============================================================ Serialisables
struct Ser {
    char pad00[0xbc];
    int  mBC;   // 0xbc
    void Inc(int a);
    void Dec(int a);
};
// @ 0x00c88480
void Ser::Inc(int a) { (void)a; mBC++; }
// @ 0x00c88490
void Ser::Dec(int a) { (void)a; mBC--; }

// ============================================================ Spatial flags
struct VObj84 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual void v84();
};
struct SpatialA {
    char    pad00[0x64];
    float   f64;   // 0x64
    char    pad68[0x76 - 0x68];
    uint8_t b76;   // 0x76
    char    pad77[0x7c - 0x77];
    float   f7c;   // 0x7c
    char    pad80[0x88 - 0x80];
    float   f88;   // 0x88
    char    pad8c[0xa6 - 0x8c];
    uint8_t bA6;   // 0xa6
    uint8_t bA7;   // 0xa7
    void SetValue(float v);
    void Sync(int v);
    void MaybeCall();
};
// @ 0x00c88530
void SpatialA::SetValue(float v) { f7c = v; f88 = 0.0f; }
// @ 0x00c88550
void SpatialA::Sync(int v) { (void)v; if (f64 != f7c) f64 = f7c; }
// @ 0x00c88510
void SpatialA::MaybeCall() { if (bA7 || bA6) ((VObj84*)this)->v84(); }

// ============================================================ cGameData
struct ObjA0 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
    virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
    virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
    virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
    virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
    virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
    virtual void v88();
    virtual void v89();
};

struct GameData {
    char    pad00[0x68];
    float   f68;    // 0x68
    char    pad6c;
    uint8_t m6d;    // 0x6d
    char    pad6e[0x76 - 0x6e];
    uint8_t b76;    // 0x76
    char    pad77[0x9c - 0x77];
    char*   mp9c;   // 0x9c
    void*   mpA0;   // 0xa0
    char    padA4[0xc0 - 0xa4];
    char*   mpBegin; // 0xc0
    char*   mpEnd;   // 0xc4

    void RemoveOwner(bool b);
    float GetValue();
    int  HasFlag();
    int  FindEntry(int id);
    bool HasEffect(int id);
};

// @ 0x00c88790
void GameData::RemoveOwner(bool b) {
    m6d = b;
    if (mpA0 && b)
        ((ObjA0*)mpA0)->v89();
}
// @ 0x00c887c0
float GameData::GetValue() {
    if (mp9c)
        return *(float*)(mp9c + 0x88);
    return f68;
}
// @ 0x00c887e0  (complete, near miss: block ordering / byte-vs-dword return)
int GameData::HasFlag() {
    if (mp9c == 0)
        return b76;
    if (*(float*)(mp9c + 0x8c) > 0.0f)
        return 0;
    return 1;
}
// @ 0x00c888e0
int GameData::FindEntry(int id) {
    for (char* p = mpBegin; p != mpEnd; p += 0x3c) {
        if (*(int*)p == id)
            return *(int*)(p + 0x38);
    }
    return 0;
}
// @ 0x00c88910
bool GameData::HasEffect(int id) {
    char* p = mpBegin;
    char* end = mpEnd;
    while (p != end) {
        if (*(int*)p == id)
            goto found;
        p += 0x3c;
    }
    p = 0;
found:
    return p != 0;
}

// ============================================================ effect list
struct EffObj3 { virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(int a); };
struct EffObj17 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual void v17(int a, int* b, int c);
};
struct Effects {
    char  pad00[0xc0];
    char* mpBegin;   // 0xc0
    char* mpEnd;     // 0xc4
    int   F40(int id);
    void  StartEffect(int id, int b);
    void  StopEffect(int id, int a);
    void  F00(int id, float v);
    void  F30(int id, int* v);
};
// @ 0x00c88940
int Effects::F40(int id) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        goto none;
    do {
        if (*(int*)p == id) {
            if (p[8] == 0)
                goto none;
            return 1;
        }
        p += 0x3c;
    } while (p != end);
none:
    return 0;
}
// @ 0x00c88980
void Effects::StartEffect(int id, int b) {
    (void)b;
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            if (p[8] == 0) {
                p[8] = 1;
                p[0xa] = 1;
            }
            return;
        }
        p += 0x3c;
    } while (p != end);
}
// @ 0x00c889c0
void Effects::StopEffect(int id, int a) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            p[8] = 0;
            EffObj3* obj = *(EffObj3**)(p + 0x38);
            if (obj)
                obj->v03(a);
            return;
        }
        p += 0x3c;
    } while (p != end);
}
// @ 0x00c88a00
void Effects::F00(int id, float v) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            *(float*)(p + 0xc) = v;
            return;
        }
        p += 0x3c;
    } while (p != end);
}
// @ 0x00c88a30
void Effects::F30(int id, int* v) {
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            p[0x28] = 1;
            *(int*)(p + 0x2c) = v[0];
            *(int*)(p + 0x30) = v[1];
            *(int*)(p + 0x34) = v[2];
            EffObj17* obj = *(EffObj17**)(p + 0x38);
            if (obj)
                obj->v17(5, v, 3);
            return;
        }
        p += 0x3c;
    } while (p != end);
}

// ============================================================ model key
struct VObj8c {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual void v8c(int a);
};
struct SpatialModel {
    char     pad00[0x90];
    uint32_t m90;   // 0x90
    uint32_t m94;   // 0x94
    uint32_t m98;   // 0x98
    void SetModelKey3(uint32_t* key);
};
// @ 0x00c88810  (complete, near miss: load scheduling of the key comparison)
void SpatialModel::SetModelKey3(uint32_t* key) {
    if (m90 == key[0] && m94 == key[1] && m98 == key[2])
        return;
    m90 = key[0];
    m94 = key[1];
    m98 = key[2];
    ((VObj8c*)this)->v8c(1);
}

// ============================================================ spatial model refresh
void* SP_PlanetModel();            // 0x00b3d350
void* FUN_00b3d310(void* self);    // 0x00b3d310
struct PlanetCall { void v(); };   // 0x00b3e810

struct SpatialPos {
    char  pad00[4];
    float x;   // 0x04
    float y;   // 0x08
    float z;   // 0x0c
    void Fn();
};
// @ 0x00c88870  (complete, near miss)
void SpatialPos::Fn() {
    if (SP_PlanetModel()) {
        float x = this->x;
        float y = this->y;
        float z = this->z;
        if (x * x + y * y + z * z > 0.001f) {
            void* r = FUN_00b3d310(this);
            ((PlanetCall*)r)->v();
        }
    }
}

// ============================================================ vector compare/copy
struct VecThing {
    char     pad00[4];
    float    x;    // 0x04
    float    y;    // 0x08
    float    z;    // 0x0c
    float    w;    // 0x10
    float    x2;   // 0x14
    float    y2;   // 0x18
    float    z2;   // 0x1c
    char     pad20[0x50 - 0x20];
    uint32_t f50;  // 0x50
    char     pad54[0x74 - 0x54];
    uint8_t  b74;  // 0x74
    void Set3(float* v);
    void Set4(float* v);
};
// @ 0x00c88670  (complete, near miss: float compare operand order)
void VecThing::Set3(float* v) {
    bool changed;
    if (x == v[0] && y == v[1] && z == v[2])
        changed = false;
    else
        changed = true;
    x = v[0];
    y = v[1];
    z = v[2];
    if (changed) {
        f50 |= 1;
        b74 = 1;
    }
}
// @ 0x00c886d0  (complete, near miss)
void VecThing::Set4(float* v) {
    bool changed;
    if (w == v[0] && x2 == v[1] && y2 == v[2] && z2 == v[3])
        changed = false;
    else
        changed = true;
    w = v[0];
    x2 = v[1];
    y2 = v[2];
    z2 = v[3];
    if (changed) {
        f50 |= 1;
        b74 = 1;
    }
}

// =====================================================================
// Partially-reconstructed functions (see partial.txt).
// =====================================================================

// @ 0x00c87be0  (partial: STL sequence serialiser)
void FUN_c87be0() {}
// @ 0x00c87c80  (partial)
void FUN_c87c80() {}
// @ 0x00c87cc0  (partial)
void FUN_c87cc0() {}
// @ 0x00c87d80  (partial)
void FUN_c87d80() {}
// @ 0x00c87df0  (partial)
void FUN_c87df0() {}
// @ 0x00c88060  (partial)
void FUN_c88060() {}
// @ 0x00c88310  (partial)
void FUN_c88310() {}
// @ 0x00c883d0  (partial)
void FUN_c883d0() {}
// @ 0x00c884a0  (partial)
void FUN_c884a0() {}
// @ 0x00c885b0  (partial)
void FUN_c885b0() {}
// @ 0x00c88610  (partial)
void FUN_c88610() {}
// @ 0x00c88740  (partial)
void FUN_c88740() {}
// @ 0x00c88a90  (partial)
void FUN_c88a90() {}
// @ 0x00c88ba0  (partial)
void FUN_c88ba0() {}
// @ 0x00c88c30  (partial)
void FUN_c88c30() {}
// @ 0x00c88d90  (partial)
void FUN_c88d90() {}
