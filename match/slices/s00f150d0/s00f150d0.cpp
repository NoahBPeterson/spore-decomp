// slice s00f150d0 -- FUN_00f150d0 (1969 B): reads 21 int properties from a property list
// (selected by the argument) and forwards each to the owner's setter, 20 of them with a
// localized cString built from (0xea25b547, instance, 0).
#include "types.h"

struct Property {
    char pad0[0x12]; unsigned short type;
    int* GetInt();                       // @ 0x41e990
};
struct IPropList {
    virtual void v00();
    virtual void Release();              // +4
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20();
    virtual bool GetProperty(unsigned int id, Property** pp);   // +0x24
};
class cString {
public:
    uint32_t mData[5];
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* source);  // @ 0x6b5770
    ~cString();                                                       // @ 0x6b5240
};
void GetPropList(unsigned int a, IPropList** out);   // @ 0x5bf0e0, cdecl

struct Owner {
    void Reset();                                          // @ 0xf14980
    void SetLocalized(int value, const cString& name, unsigned int id);   // @ 0xf14b30
    void SetPlain(int value, unsigned int id);             // @ 0xf14ba0
    void Load(unsigned int arg);                           // @ 0xf150d0
};

__forceinline int ReadInt(IPropList* l, unsigned int key)
{
    int v = 0;
    Property* p;
    if (l && l->GetProperty(key, &p) && p->type == 9) v = *p->GetInt();
    return v;
}

#define LOCALIZED(key, inst, id) \
    { int v = ReadInt(list, key); SetLocalized(v, cString(0xea25b547, inst, 0), id); }

void Owner::Load(unsigned int arg)
{
    IPropList* list = 0;
    GetPropList(arg, &list);
    Reset();
    LOCALIZED(0x99a62668, 0x7736327, 0x7ca2b56)
    LOCALIZED(0x0db76cb8, 0x7736328, 0x7ca2b57)
    LOCALIZED(0x59df6558, 0x7736329, 0x7ca2b58)
    SetPlain(ReadInt(list, 0x86a6dced), 0x7ca2b60);
    LOCALIZED(0x5ff28470, 0x7736316, 0x7ca2b50)
    LOCALIZED(0xdbcffa7d, 0x773631c, 0x7ca2b66)
    LOCALIZED(0x384fb43e, 0x773631d, 0x7ca2b61)
    LOCALIZED(0xf469cdc3, 0x773631e, 0x7ca2b63)
    LOCALIZED(0x42abfeab, 0x7736323, 0x7ca2b62)
    LOCALIZED(0xad4e4ce0, 0x773631f, 0x7ca2b64)
    LOCALIZED(0xebed2519, 0x7736322, 0x7ca2b65)
    LOCALIZED(0xfbec5f0c, 0x7736317, 0x7ca2b51)
    LOCALIZED(0xb77e5335, 0x7736319, 0x7ca2b51)
    LOCALIZED(0x02e88517, 0x7736318, 0x7ca2b51)
    LOCALIZED(0xf27fefd1, 0x7736324, 0x7ca2b51)
    LOCALIZED(0x547fecc1, 0x7736325, 0x7ca2b54)
    LOCALIZED(0x76134ba7, 0x773631a, 0x7ca2b52)
    LOCALIZED(0x9d8493b2, 0x7736326, 0x7ca2b55)
    LOCALIZED(0xa55c05aa, 0x773631b, 0x7ca2b53)
    LOCALIZED(0xceb2889b, 0x7736320, 0x7ca2b68)
    LOCALIZED(0xc5ff81b3, 0x7736321, 0x7ca2b67)
    if (list) list->Release();
}
