// slice s004ee9b0 -- SP::cSPEditorModelValidity::TestLimbs / TestBounds
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

extern "C" float __cdecl sqrtf(float);

struct Property {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (1 = bool, 0xd = float)
    bool* GetBool();                // 0x0041e920
    float* GetFloat();              // 0x0041ea70
};

struct PropertyList {
    virtual int Release_();         // 0
    virtual int Release();          // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};

// EA::AutoRefCount<PropertyList>
struct PropListRef {
    PropertyList* mp;
    PropListRef() : mp(0) { if (mp) mp->Release_(); }
    ~PropListRef() { if (mp) mp->Release(); }
    PropListRef* operator&();       // 0x0041d870 (releases old, returns this)
};

struct PropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void GetPropertyList(uint32_t type, uint32_t group, PropListRef* out);   // +0x2c
};

struct ModelManager {
    char vt[0x58];
};
struct EntryOwner {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual PropertyList* GetPropertyList(uint32_t instance, uint32_t group);   // +0x58
};

struct Vec3f {
    float v[3];
    float operator[](int i) const { return v[i]; }
};

struct LimbEntry {                  // 0x1d8 bytes
    uint32_t group;                 // +0x00
    uint32_t instance;              // +0x04
    int      parent;                // +0x08
    char     pad0[8];
    Vec3f    pos;                   // +0x14
    char     pad1[0x1d8 - 0x20];
};

struct LimbVec {
    LimbEntry* mpBegin;
    LimbEntry* mpEnd;
    LimbEntry& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct Model {
    char pad0[0x18];
    uint32_t modelType;             // +0x18
    char pad1[0x98 - 0x1c];
    LimbVec mLimbs;                 // +0x98
};

struct ValidityBits {               // bitset<128>
    uint32_t w[4];
    __forceinline void set(unsigned pos, bool val)
    {
        if (pos < 0x80) {
            if (val) {
                uint32_t* p = &w[pos >> 5];
                *p |= 1u << (pos % 32);
            } else {
                uint32_t* p = &w[pos >> 5];
                *p &= ~(1u << (pos % 32));
            }
        }
    }
};

EntryOwner* FUN_00401010();                                         // 0x00401010
PropertyList* FUN_004ee930(int idx, Model* model);                   // 0x004ee930
void GetBoolProperty(PropertyList* pl, uint32_t id, bool& dst);      // 0x00407190
PropertyManager* PropertyManager_Get();                              // 0x0067de30 (SP::PropertyManager)
uint32_t RemapTypeId(uint32_t type);                                 // 0x00432f10
extern uint32_t g_ModelGroup;                                        // 0x015daa00
extern const float kTwo;                                             // 0x01470f1c

// @ 0x004ee9b0
bool TestLimbs(Model* model, ValidityBits* flags)
{
    int type = (int)model->modelType;
    bool isRelevant = false;
    switch (type) {
    case 0x372e2c04: case (int)0x9ea3031a: case (int)0xccc35c46: case (int)0xdfad9f51:
    case 0x4178b8e8: case 0x65672ade:
        isRelevant = true;
    }
    if (!isRelevant) {
        if (flags) flags->set(27, false);
        return true;
    }
    LimbVec* pv = &model->mLimbs;
    int i = 0;
    int n = pv->size();
    for (; i < n; i++) {
        PropertyList* pl = FUN_00401010()->GetPropertyList((*pv)[i].instance, (*pv)[i].group);
        if (!pl) {
            if (flags) flags->set(27, true);
            return false;
        }
        bool b = false;
        GetBoolProperty(pl, 0x4ff31eec, b);
        if (b) {
            int parent = (*pv)[i].parent;
            PropertyList* pp = FUN_004ee930(parent, model);
            if (!pp) {
                if (flags) flags->set(27, true);
                return false;
            }
            bool b1 = false;
            GetBoolProperty(pp, 0x4ff31eec, b1);
            bool b2 = false;
            GetBoolProperty(pp, 0x6ff31f12, b2);
            bool b3 = false;
            GetBoolProperty(pp, 0xafff3a14, b3);
            if (!b3 && (!b1 || !b2)) {
                if (flags) flags->set(27, true);
                return false;
            }
            bool isChain = false;
            if (pl) {
                Property* prop;
                if (pl->GetProperty(0x6ff31f12, prop) && prop->mType == 1)
                    isChain = *prop->GetBool();
            }
            if (isChain) {
                int nB = 0;
                int nA = 0;
                bool ok = true;
                for (unsigned j = 0; j < (unsigned)n; j++) {
                    if ((*pv)[j].parent == i) {
                        PropertyList* cp = FUN_004ee930(j, model);
                        bool ca = false;
                        if (cp) {
                            Property* p1;
                            if (cp->GetProperty(0x4ff31eec, p1) && p1->mType == 1)
                                ca = *p1->GetBool();
                        }
                        bool cb = false;
                        if (cp) {
                            Property* p2;
                            if (cp->GetProperty(0x6ff31f12, p2) && p2->mType == 1)
                                cb = *p2->GetBool();
                        }
                        if (cb && ca)
                            nB++;
                        else if (ca)
                            nA++;
                    }
                }
                if (!ok) {
                    if (flags) flags->set(27, true);
                    return false;
                }
                if (nA == 0 && nB == 0) {
                    if (flags) flags->set(27, true);
                    return false;
                }
            }
        }
    }
    if (flags) flags->set(27, false);
    return true;
}

// @ 0x004ef190
bool TestBounds(Model* model, ValidityBits* flags)
{
    LimbVec* pv = &model->mLimbs;
    uint32_t type = model->modelType;
    PropListRef cfg;
    PropertyManager* pm = PropertyManager_Get();
    pm->GetPropertyList(RemapTypeId(type), g_ModelGroup, &cfg);
    if (!cfg.mp) {
        if (flags) flags->set(8, true);
        return false;
    }
    float maxRadius, maxZ, minZ;
    if (cfg.mp) {
        PropertyList* c1 = cfg.mp;
        Property* p1;
        if (c1 && c1->GetProperty(0x700db77d, p1) && p1->mType == 0xd)
            maxRadius = *p1->GetFloat();
        PropertyList* c2 = cfg.mp;
        Property* p2;
        if (c2 && c2->GetProperty(0x2704959d, p2) && p2->mType == 0xd)
            maxZ = *p2->GetFloat();
        PropertyList* c3 = cfg.mp;
        Property* p3;
        if (c3 && c3->GetProperty(0x44c7f29f, p3) && p3->mType == 0xd)
            minZ = *p3->GetFloat();
        maxRadius = maxRadius / 2.0f;
        int i = 0;
        int n = pv->size();
        for (; i < n; i++) {
            bool flag = false;
            PropertyList* pl = FUN_00401010()->GetPropertyList((*pv)[i].instance, (*pv)[i].group);
            if (!pl) {
                if (flags) flags->set(8, true);
                return false;
            }
            if (pl) {
                Property* p4;
                if (pl->GetProperty(0x538a895, p4) && p4->mType == 1)
                    flag = *p4->GetBool();
            }
            if (!flag) {
                LimbEntry* e = &(*pv)[i];
                if (e->pos[2] > maxZ || minZ > (*pv)[i].pos[2]) {
                    if (flags) flags->set(8, true);
                    return false;
                }
                LimbEntry* e2 = &(*pv)[i];
                LimbEntry* e3 = &(*pv)[i];
                float x = e3->pos[0];
                float y = e2->pos[1];
                float dist = sqrtf(x * x + y * y);
                if (dist > maxRadius) {
                    if (flags) flags->set(8, true);
                    return false;
                }
            }
        }
    }
    if (flags) flags->set(8, false);
    return true;
}
