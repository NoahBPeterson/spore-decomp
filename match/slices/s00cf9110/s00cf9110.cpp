
#include "types.h"

struct CivObject {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int Query(unsigned int id); // +0x0c
};

struct CivRefTable {
    int SetField0C(int value); // 0x00cfe780
    int SetField10(int value); // 0x00cfe790
};

struct EventLog {
    int PostFeedbackEvent(
        int a,
        int b,
        int c,
        int d,
        int e,
        int f
    ); // 0x00dd8640
};

extern CivRefTable* g_civRefTable; // 0x0169d3c8

EventLog* __cdecl GetEventLog(); // 0x00b3d3e0

// @ 0x00cf9110
int __stdcall FUN_00cf9110(
    CivObject* object,
    int a2,
    int a3,
    int a4,
    int a5,
    int a6,
    int a7,
    int a8
)
{
    CivRefTable* table = g_civRefTable;

    int id = object
        ? object->Query(0x017f243b)
        : 0;

    int previousCiv = table->SetField0C(id);
    int previousValue = table->SetField10(a2);

    int result = GetEventLog()->PostFeedbackEvent(
        a3,
        a4,
        a5,
        a6,
        a7,
        a8
    );

    table->SetField0C(previousCiv);
    table->SetField10(previousValue);

    return result;
}
