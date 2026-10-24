// Slice s00bcf6f0 (continued): cSPGameDataUFO::FireAtTarget 0x00bd0140.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int uint;

struct Vector3 { float x, y, z; };

// Tool objects referenced through EA::AutoRefCount: slot 4 = AddRef, 8 = Release.
struct ToolObj {
    virtual void v00();
    virtual void AddRef();       // 0x04
    virtual void Release();      // 0x08

    bool  F0104bd50();           // 0x0104bd50
    float F0104be20();           // 0x0104be20
};

struct ToolMgr {
    void UseToolStop(ToolObj* tool);     // 0x0104fa90, ret 4
};
ToolMgr* GetToolMgr();                   // 0x00b3d390

struct ModelObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();     // 0x2c
};

struct IGameDataView {
    virtual void v00(); virtual void v04();
    virtual ModelObj* GetModel();             // 0x08
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void* Cast(uint typeId);          // 0x5c
};

// The part of the game object whose vtable sits at offset 0 (this == object + 0x554).
struct UFOBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();     // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual float GetScale();                 // 0x70
};

struct Planet {
    int F00c70e00();             // 0x00c70e00
};

unsigned __cdecl GetCurrentGameMode();          // 0x00b5b800
Planet*   __cdecl GetActivePlanet();            // 0x01021260
extern "C" float __cdecl sqrtf(float);          // CRT sqrt

extern float g_targetRangeScale;                // 0x013ec4b4

struct cGameData {
    char       m_pad000[0x48];        // 0x000
    void*      m_view48;              // +0x48
    char       m_pad04c[0x104 - 0x4c];
    ToolObj*   m_tool104;             // +0x104
    ToolObj*   m_tool108;             // +0x108
    ToolObj*   m_tool10c;             // +0x10c
    ToolObj*   m_tool110;             // +0x110

    void FireAtTarget(IGameDataView* view);     // 0x00bd0140 (ret 4)
    void WriteAsText(IGameDataView* view);      // 0x00bfc860
};

// @ 0x00bd0140
void cGameData::FireAtTarget(IGameDataView* view)
{
    if (view != m_view48 && m_tool104 != 0 && m_tool104->F0104bd50())
        GetToolMgr()->UseToolStop(m_tool104);

    ToolObj* sel;

    if (GetCurrentGameMode() == 0x1654c05
        && GetActivePlanet()->F00c70e00() == 5) {
        if (view == 0 || view->Cast(0xb033b403) == 0) {
            sel = m_tool10c;
        } else {
            UFOBase* base = (UFOBase*)((char*)this - 0x554);

            float range = base->GetScale() * g_targetRangeScale;

            const Vector3& p = base->GetPosition();
            float invLen = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);

            Vector3 off;
            off.x = p.x * invLen * range;
            off.y = p.y * invLen * range;
            off.z = p.z * invLen * range;

            const Vector3& origin = base->GetPosition();
            Vector3 target;
            target.x = origin.x + off.x;
            target.y = origin.y + off.y;
            target.z = origin.z + off.z;

            const Vector3& modelPos = view->GetModel()->GetPosition();
            Vector3 delta;
            delta.x = modelPos.x - target.x;
            delta.y = modelPos.y - target.y;
            delta.z = modelPos.z - target.z;

            float dist = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

            sel = (dist <= m_tool110->F0104be20()) ? m_tool10c : m_tool110;

            if (m_tool104 != 0 && m_tool104->F0104bd50() && m_tool104 != sel)
                GetToolMgr()->UseToolStop(m_tool104);
        }
    } else {
        if (view == 0)
            goto done;
        sel = m_tool108;
    }

    {
        ToolObj* old = m_tool104;
        if (sel != old) {
            if (sel != 0)
                sel->AddRef();
            m_tool104 = sel;
            if (old != 0)
                old->Release();
        }
    }

done:
    WriteAsText(view);
}
