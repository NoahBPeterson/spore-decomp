#include "types.h"

// Slice s004145c0: three members around the editor palette (list of placeable editor objects).
//   0x004145C0  PaletteEditor::SetItem     (replace/clear the current item, then notify)
//   0x004147B0  PaletteEditor::AddEntry    (build an Entry from a definition + its property list and queue it)
//   0x00414E10  EditorObject::GetField78   (trivial getter)
// The module is built without optimization and without C++ EH: /Od /Ob1 /MD /Gy /TP.
//
// /Od notes learned here (on top of s00403af0's):
//  - Stack slots of named locals follow a name-dependent order; the locals of AddEntry were renamed
//    until the order matched (editSize, cmd, groupType, ok, objKey, isDebug, self, pDesc, enableAll, seq,
//    otherList, rank, i, a2, jj). The names are placeholders chosen for that order, not recovered names.
//  - Unused locals in an inline function still reserve slots: the `d1, d2, d3` in ip<>::assign/operator=
//    and the `u0..u11` in Slot's constructor reproduce 3-dword and 12-dword holes in the inline-slot region.
//  - A by-value temporary of a one-member struct (GroupBits(x).Type()) yields the load-to-temp, reload,
//    shr/and sequence; a plain inline helper would be substituted with no slot.
//  - Out-of-line ReleaseRef() wrapped by an inline AsOutParamX() pre-evaluates the call into a temp.

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);

struct DefaultRefCounted {
    void* vtable;
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};
struct ThreadedObject {
    void* vtable;
    volatile long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();
};
struct IRefCounted { virtual int AddRef() = 0; virtual int Release() = 0; };

struct ResourceKey { unsigned int instanceID, typeID, groupID; ResourceKey(); };
struct ExtraInfo { int a; unsigned short flags; unsigned short pad; };   // 8 bytes; low flag bits tested below

struct Property {
    char pad0[0x12]; unsigned short type;
    int* GetInt();
    bool* GetBool();
};
struct IPropList : IRefCounted {
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20();
    virtual bool GetProperty(unsigned int id, Property** pp);
};
struct IPropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(unsigned int a, unsigned int b, IPropList** pp);
};
IPropManager* PropManager();

template <class T> struct ip {
    T* p;
    ip() : p(0) {}
    ip(T* o) : p(o) { if (p) p->AddRef(); }
    ~ip() { if (p) p->Release(); }
    void assign(T* o) { T* const pTemp = p; int d1, d2, d3; if (o) o->AddRef(); p = o; if (pTemp) pTemp->Release(); }
    ip& operator=(T* o) { if (o != p) { T* const pTemp = p; int d1, d2, d3; if (o) o->AddRef(); p = o; if (pTemp) pTemp->Release(); } return *this; }
    T* get() const { return p; }
    T* operator->() const { return p; }
    T** AsOutParam() { if (p) { T* t = p; p = 0; t->Release(); } return &p; }
    ip& ReleaseRef();   // out of line
    __forceinline void reset() { if (p) assign(0); }
    T** AsOutParamX() { return &ReleaseRef().p; }
};
template <class T> struct tip {
    T* p;
    tip& operator=(T* o) { if (o != p) { T* const pTemp = p; if (o) o->AddRef(); p = o; if (pTemp) pTemp->Release(); } return *this; }
};
struct ItemBase : DefaultRefCounted { unsigned pad[(0x6b-8)/4]; char p1[3]; bool f6b; bool f6c; };
typedef ItemBase Item;

struct V3 { int x, y, z; };
struct DefTail {              // Def + 0x18
    int nameHash; int x1c;
    int ids[3];               // 0x20
    int ids2[3];              // 0x2c
    V3 pos[3];                // 0x38
};
struct Def {
    void* vt; int rc;
    ResourceKey key;       // 8
    int x14;
    DefTail tail;          // 0x18
};
struct DefRef : ThreadedObject {
    Def* pDef;             // 8
    Def* GetDef() const { return pDef; }
};
struct Entry : DefaultRefCounted {   // 0x84 bytes
    tip<ThreadedObject> owner;   // 8
    ResourceKey key;            // 0xc
    int ids[4];                 // 0x18
    int ids2[3];                // 0x28
    int pad34;
    V3 pos[3];                  // 0x38
    int flags;                  // 0x5c
    int priority;               // 0x60
    bool b64, b65, b66, b67, b68, b69, b6a, b6b;
    unsigned pad6c[(0x84 - 0x6c) / 4];
    Entry();
};
unsigned int SetKeyType(ResourceKey* k, int a, int b);         // 0x68c6d0
unsigned int HashName(int v);                                  // 0x4bb860
unsigned int ResolveName(int v);                               // 0x432f10
bool GetArrayImpl(IPropList* l, unsigned int id, int* count, int** arr);   // 0x6a0840
extern unsigned int g_015d13e8;

struct SlotTail { int a; int b; ip<IRefCounted> cb; SlotTail(ip<Entry>* pe); };
struct Slot {  // 0x24 bytes
    ResourceKey key; ExtraInfo extra; int pad; SlotTail tail;
    int pad2[3];
    Slot(ip<Entry>* pe) : tail(pe) { int u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11; }
    ~Slot();
};
struct Container { void Add(Slot* s, int); };  // 0x4204f0

inline void GetIntProp(IPropList* l, unsigned int id, int& out) {
    Property* p;
    if (l && l->GetProperty(id, &p) && p->type == 9) out = *p->GetInt();
}
inline void GetBoolProp(IPropList* l, unsigned int id, bool& out) {
    Property* p;
    if (l && l->GetProperty(id, &p) && p->type == 1) out = *p->GetBool();
}
struct GroupBits { unsigned int raw; unsigned int Type() const { return (raw >> 16) & 0xff; } GroupBits(unsigned int v) : raw(v) {} };
struct PropArray { int* data; int count; unsigned int id; PropArray() : count(0), id(0x5e68c2e) {} };

struct PaletteEditor {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40();
    virtual bool TestPlacement(V3* pos, int a);
    virtual void v48();
    virtual void ApplyPlacement(V3* pos, ExtraInfo* extra);
    void Refresh(int);   // 0x00411890
    unsigned pad0[(0xbc-4)/4];
    ip<Item> m_item;               // 0xbc
    unsigned pad4[2];
    Container m_container;         // 0xc8
    char pad5[3];
    unsigned pad1[(0x228-0xcc)/4];
    V3 m_pos;                      // 0x228
    ExtraInfo m_pair; unsigned padx;
    ip<Item> m_cur;
    unsigned pad2[(0x258-0x244)/4];
    bool m_dirty; bool m_b259;
    unsigned pad3[(0x2c4-0x25c)/4];
    bool m_b2c4;
    bool SetItem(Item* n);
    bool AddEntry(DefRef* src, ExtraInfo* extra, IRefCounted* cb);
};

// @ 0x004145c0
// Replaces the current item: a selected/visible item is dropped first, then the new one is stored
// and, if the palette is active, the placement is re-validated and applied.
bool PaletteEditor::SetItem(Item* n)
{
    if (m_item.get() && (m_item->f6c || m_item->f6b)) {
        if (m_cur.get() == m_item.get()) { m_dirty = true; Refresh(0); }
        m_item.reset();
    }
    if (!m_item.get()) {
        m_item = n;
        if (m_b2c4 || m_b259) {
            V3 vec = m_pos;
            ExtraInfo flags = m_pair;
            m_dirty = true;
            if (TestPlacement(&vec, flags.a)) {
                flags.flags |= 1;
                ApplyPlacement(&vec, &flags);
            } else m_dirty = false;
        }
        return true;
    }
    return false;
}

// @ 0x004147b0
// Creates an Entry for a definition: reads sizing/priority/flags from the definition's property list,
// copies per-slot data from the definition, patches up special type hashes, then queues it.
bool PaletteEditor::AddEntry(DefRef* src, ExtraInfo* extra, IRefCounted* cb)
{
    ResourceKey objKey = src->GetDef()->key;
    objKey.typeID = HashName(src->GetDef()->tail.nameHash);
    int editSize = 0x200;
    int seq = -1;
    bool enableAll = true;
    bool isDebug = false;
    ip<IPropList> pDesc;
    if (PropManager()->GetPropertyList(objKey.instanceID, objKey.groupID, pDesc.AsOutParamX())) {
        GetIntProp(pDesc.get(), 0x4c6ba29, editSize);
        GetIntProp(pDesc.get(), 0x52f7b17, seq);
        GetBoolProp(pDesc.get(), 0x521fc0e, enableAll);
        GetBoolProp(pDesc.get(), 0x680a2b1, isDebug);
    }
    int groupType = GroupBits(objKey.groupID).Type();
    bool ok = (groupType == 0x66 || groupType == 0x6b) ? 0 : 1;
    ip<Entry> self(new("Editor", 0, 0, 0, 0) Entry());
    self->owner = src;
    self->key = objKey;
    SetKeyType(&self->key, 0x29, 0);
    self->flags = editSize;
    self->priority = seq;
    self->b64 = isDebug;
    self->b65 = enableAll;
    self->b66 = ok;
    self->b67 = false;
    self->b68 = !(extra->flags & 2);
    self->b69 = true;
    self->b6a = false;
    if (groupType == 0x6b) {
        self->ids[0] = 0x8ec5176c;
    } else {
        DefTail* rank = &src->GetDef()->tail;
        for (int i = 0; i < 3; i++) {
            self->pos[i] = rank->pos[i];
            self->ids[i] = rank->ids[i];
            self->ids2[i] = rank->ids2[i];
        }
        ip<IPropList> otherList;
        if (PropManager()->GetPropertyList(ResolveName(rank->nameHash), g_015d13e8, otherList.AsOutParam())) {
            PropArray a2;
            if (GetArrayImpl(otherList.get(), 0x5e68c2e, &a2.count, &a2.data)) {
                for (int jj = 0; jj < 3 && jj < a2.count; jj++) {
                    if (self->ids[jj] == 0) self->ids[jj] = a2.data[jj];
                }
            }
        }
        if (objKey.typeID == 0x2b978c46 && groupType != 0x6b) self->ids[3] = 0xd723b947;
        if (objKey.typeID == 0x3d97a8e4) { self->ids[3] = 0; self->ids[2] = 0; self->ids[1] = 0; }
    }
    Slot cmd(&self);
    cmd.key = objKey;
    cmd.extra = *extra;
    cmd.tail.cb = cb;
    m_container.Add(&cmd, 0);
    m_dirty = true;
    return true;
}

// @ 0x00414e10
struct EditorObject {
    unsigned pad[0x78 / 4];
    int m_field78;
    int GetField78();
    int Field78() const { return m_field78; }
};
int EditorObject::GetField78() { return Field78(); }
