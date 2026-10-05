// @ 0x458f60  SP::CapabilityManager::InitNonDeformAnimations
// /Od editor module.  Walks the 0x5f-entry capability-key table, looks each up in the
// property list, and pushes per-vertex animation data through the model interface.
#include "types.h"

extern "C" void* SP_PropertyManager();          // 0x67de30  SP::PropertyManager()

extern uint32_t g_keys[];                       // 0x13ec608
extern float    g_defaultWeight;                // 0x1485378

// ---- stub interfaces (only vtable slot offsets matter; callees are masked) ----
struct IRefCounted {
    virtual void v0() = 0;
    virtual void Release() = 0;                 // +0x04
};

struct PropData {
    void*    data;        // +0x00
    uint32_t pad4;        // +0x04
    int      count;       // +0x08
    uint16_t flags;       // +0x10
    uint16_t inlineCount; // +0x12
};

struct PropertyList : IRefCounted {
    virtual void v8() = 0;
    virtual void vc() = 0;
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual bool Has(uint32_t key) = 0;         // +0x1c
    virtual void v20() = 0;
    virtual void v24() = 0;
    virtual PropData* GetData(uint32_t key) = 0; // +0x28
};

struct PropertyManager {
    virtual void v0() = 0;  virtual void v1() = 0;  virtual void v2() = 0;
    virtual void v3() = 0;  virtual void v4() = 0;  virtual void v5() = 0;
    virtual void v6() = 0;  virtual void v7() = 0;  virtual void v8() = 0;
    virtual void v9() = 0;  virtual void v10() = 0;
    virtual bool GetList(uint32_t a, uint32_t b, PropertyList** out) = 0;  // +0x2c
};

struct IModelIface {
    virtual void d00() = 0; virtual void d01() = 0; virtual void d02() = 0; virtual void d03() = 0;
    virtual void d04() = 0; virtual void d05() = 0; virtual void d06() = 0; virtual void d07() = 0;
    virtual void d08() = 0; virtual void d09() = 0; virtual void d10() = 0; virtual void d11() = 0;
    virtual void d12() = 0; virtual void d13() = 0; virtual void d14() = 0; virtual void d15() = 0;
    virtual void d16() = 0; virtual void d17() = 0; virtual void d18() = 0; virtual void d19() = 0;
    virtual void d20() = 0; virtual void d21() = 0; virtual void d22() = 0; virtual void d23() = 0;
    virtual void d24() = 0; virtual void d25() = 0; virtual void d26() = 0; virtual void d27() = 0;
    virtual void Begin(int model, int value, int type, int unused) = 0;   // +0x70
    virtual void Set(int model, int value, float v, int unused) = 0;      // +0x74
    virtual void End(int model, int value, float v, int unused) = 0;      // +0x78
    virtual void d31() = 0;                                               // +0x7c
    virtual void Range(int model, int value, float* lo, float* hi, int unused) = 0; // +0x80
};

static void ReleaseList(PropertyList*& p)
{
    if (p != 0) {
        p->Release();
        p = 0;
    }
}

void InitNonDeformAnimations(int model, IModelIface* iface, uint32_t propGroup,
                             uint32_t unused, uint32_t propName, char flag)
{
    if (model == 0 || iface == 0) {
        return;
    }

    PropertyList* list = 0;
    PropertyManager* pm = (PropertyManager*)SP_PropertyManager();
    if (!pm->GetList(propGroup, propName, &list)) {
        ReleaseList(list);
        return;
    }

    for (int i = 0; i < 0x5f; i = i + 1) {
        uint32_t key = g_keys[i];
        if (!list->Has(key)) {
            continue;
        }

        PropertyList* sub = 0;
        pm = (PropertyManager*)SP_PropertyManager();
        if (!pm->GetList(key, 0x047bf35f, &sub)) {
            ReleaseList(sub);
            continue;
        }

        // ---- position array (Vector3, stride 12) ----
        PropData* posObj = sub->GetData(0x047be908);
        int posCount;
        char* pos;
        if ((posObj->flags & 0x30) != 0) {
            posCount = posObj->count;
            pos = (char*)posObj->data;
        } else if (posObj->inlineCount != 0) {
            posCount = 1;
            pos = (char*)posObj;
        } else {
            posCount = 0;
            pos = 0;
        }

        // ---- scale array (float) ----
        PropData* scaleObj = sub->GetData(0x047be96f);
        int scaleCount;
        float* scale;
        if ((scaleObj->flags & 0x30) != 0) {
            scaleCount = scaleObj->count;
            scale = (float*)scaleObj->data;
        } else if (scaleObj->inlineCount != 0) {
            scaleCount = 1;
            scale = (float*)scaleObj;
        } else {
            scaleCount = 0;
            scale = 0;
        }

        // ---- fallback weight array (float) ----
        PropData* fallObj = sub->GetData(0x684d16c);
        float* fallback;
        if ((fallObj->flags & 0x30) != 0) {
            fallback = (float*)fallObj->data;
        } else if (fallObj->inlineCount != 0) {
            fallback = (float*)fallObj;
        } else {
            fallback = 0;
        }

        for (int j = 0; j < posCount; j = j + 1) {
            int value = ((int*)pos)[j * 3];
            iface->Begin(model, value, 3, 0);

            float lo;
            float hi;
            iface->Range(model, value, &lo, &hi, 0);

            iface->Set(model, value, (hi - lo) * scale[j] + lo, 0);

            float v;
            if (flag != 0) {
                v = g_defaultWeight;
            } else {
                v = fallback[j];
            }
            iface->End(model, value, v, 0);
        }

        ReleaseList(sub);
    }

    ReleaseList(list);
    return;
}
