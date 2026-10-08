// Slice s00de41b0: 00de4e70, a property lookup that reads two int properties
// from a property list returned by the property manager.

typedef unsigned int uint32;

struct Property {
    char pad[0x12];
    short type;                 // +0x12, 9 = int
    int* GetInt();              // thiscall, returns int& (asm: Property::GetInt)
};

struct PropertyList {
    virtual void v0();
    virtual void Release();     // slot 1
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool GetProperty(uint32 id, Property** out);  // slot 9 (+0x24)
};

// Intrusive reference to a PropertyList (AutoRefCount-style, Release at slot 1).
struct PropertyListRef {
    PropertyList* p;
    PropertyListRef() : p(0) {}
    void Reset() {
        PropertyList* old = p;
        p = 0;
        if (old) old->Release();
    }
};

struct PropertyManager {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32 a, uint32 b, PropertyListRef* out);  // slot 11 (+0x2c)
};

PropertyManager* GetPropertyManager();   // free function, no args (SP::PropertyManager)

// @ 0x00de4e70
int ReadIntPropertyPair(uint32 a1, uint32 a2) {
    int ret = 0;
    int v1 = 0;
    PropertyListRef list;
    PropertyManager* mgr = GetPropertyManager();
    list.Reset();
    if (mgr->GetPropertyList(a1, a2, &list)) {
        Property* tmp;
        if (list.p && list.p->GetProperty(0x22e7847, &tmp)) {
            if (tmp->type == 9) {
                v1 = *tmp->GetInt();
            }
        }
        int v2 = 0;
        if (list.p && list.p->GetProperty(0x22e785c, &tmp)) {
            if (tmp->type == 9) {
                v2 = *tmp->GetInt();
            }
        }
        if (v1 > 0) {
            ret = (v2 <= 0) ? 4 : 2;
        } else if (v2 > 0) {
            ret = 1;
        }
    }
    if (list.p) {
        list.p->Release();
    }
    return ret;
}
