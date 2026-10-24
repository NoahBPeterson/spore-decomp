// Slice s00bcf6f0 (continued): UFO tool refresh 0x00bd0000.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;

struct Vector3 { float x, y, z; };

// Tool objects referenced through EA::AutoRefCount: vtable slot 4 = AddRef, 8 = Release.
struct ToolObj {
    virtual void v00();
    virtual void AddRef();       // 0x04
    virtual void Release();      // 0x08

    float F0104be30();           // 0x0104be30
};

struct ToolMgr {
    bool CreateToolFromToolID(uint toolID, ToolObj** slot);   // 0x0104e340, ret 8
};
ToolMgr* GetToolMgr();                                       // 0x00b3d390

struct City {
    int GetVehicleSpecialty();                               // 0x00bd81d0
};

// One of the three vehicle-specialty parameter rows (raw 32-bit values).
struct SpecialtyRow {
    uint m_value;       // +0x00
    uint m_pad04;       // +0x04
    uint m_pad08;       // +0x08
};

extern SpecialtyRow g_specialtyB;    // 0x0168b630  (spec == 1)
extern SpecialtyRow g_specialtyC;    // 0x0168b63c  (spec == 2)
extern SpecialtyRow g_specialtyA;    // 0x0168b624  (any other value)
extern uint         g_specialtyInit; // 0x0168b648

struct UFOObject {
    char     m_pad000[0x2a0];            // 0x000
    float    m_flightTime;               // +0x2a0
    char     m_pad2a4[0x688 - 0x2a4];    // 0x2a4 .. 0x687
    City*    m_ownerCity;                // +0x688
    ToolObj* m_tool68c;                  // +0x68c
    ToolObj* m_tool690;                  // +0x690

    void RefreshTools();                 // 0x00bd0000
};

// @ 0x00bd0000
void UFOObject::RefreshTools()
{
    if ((g_specialtyInit & 1) == 0) {
        g_specialtyInit |= 1;
        g_specialtyA.m_value  = 0x4394a35e;
        g_specialtyA.m_pad04  = 0;
        g_specialtyA.m_pad08  = 0;
        g_specialtyB.m_value  = 0x6779050d;
        g_specialtyB.m_pad04  = 0;
        g_specialtyB.m_pad08  = 0;
        g_specialtyC.m_value  = 0x39a81b42;
        g_specialtyC.m_pad04  = 0;
        g_specialtyC.m_pad08  = 0;
    }

    if (m_ownerCity != 0) {
        switch (m_ownerCity->GetVehicleSpecialty()) {
        case 1:
            if (m_tool690 != 0) {
                ToolObj* t = m_tool690;
                m_tool690 = 0;
                t->Release();
            }
            GetToolMgr()->CreateToolFromToolID((uint)&g_specialtyB, &m_tool690);
            break;
        case 2:
            if (m_tool690 != 0) {
                ToolObj* t = m_tool690;
                m_tool690 = 0;
                t->Release();
            }
            GetToolMgr()->CreateToolFromToolID((uint)&g_specialtyC, &m_tool690);
            break;
        default:
            if (m_tool690 != 0) {
                ToolObj* t = m_tool690;
                m_tool690 = 0;
                t->Release();
            }
            GetToolMgr()->CreateToolFromToolID((uint)&g_specialtyA, &m_tool690);
            break;
        }
    }

    ToolObj* nw = m_tool690;
    ToolObj* old = m_tool68c;
    if (nw != old) {
        if (nw != 0)
            nw->AddRef();
        m_tool68c = nw;
        if (old != 0)
            old->Release();
    }

    m_flightTime = m_tool68c->F0104be30();
}
