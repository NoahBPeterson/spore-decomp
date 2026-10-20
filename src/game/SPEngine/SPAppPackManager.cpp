// src/game/SPEngine/SPAppPackManager.cpp -- migrated from slice(s) s007db1b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppPackManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern void* vtPropFilter[];                  // 0x013f662c
extern void* vtIMsgHandler[];                 // 0x013eb394
extern int g_153ed8c;                         // filter argument
#include <stdio.h>
#include <string.h>

// ---- items of slice s007db1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PtrVec {
    void** mpBegin;     // +0x0
    void** mpEnd;       // +0x4
    bool Contains(int key);     // 007db5b0
    void* Find(int key);        // 007db5e0
    void* At(int index);        // 007db620
};
void* PtrVec::Find(int key)
{
    int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i) {
        if (*(int*)mpBegin[i] == key)
            return mpBegin[i];
    }
    return 0;
}
void EDealloc(void* p);      // 0x00f47380
void EDealloc(void* p);      // 0x00f47380
extern void* vtPropFilter[];                  // 0x013f662c
extern void* vtIMsgHandler[];                 // 0x013eb394
extern int g_153ed8c;                         // filter argument
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int) throw(); // 0x00f473a0
void __cdecl EDealloc(void*);                 // 0x00f47380
struct PackKey3 { uint32_t a, b, c; PackKey3() { a = 0; b = 0; c = 0; } };
struct PackCString {                          // SP::cString (0x14 bytes)
    uint32_t d[5];
    PackCString();                            // 0x006b5060
};
struct PackLocStr {                           // SP::cLocalizedString-like: 3 words, then the placeholder cString
    uint32_t a, b, c;
    PackCString mPlaceholderId;               // +0xc (absolute +0x24)
    PackLocStr() : a(0), b(0), c(0) {}
};
struct PackInfo {
    int mPackId;                // +0x0
    int mSequenceNumber;        // +0x4
    uint32_t mLayoutID;         // +0x8
    PackKey3 mButtonIconKey;    // +0xc
    PackLocStr mName;           // +0x18
};
struct PackVariant { uint32_t f0, f4, f8, fc; uint16_t flags, typeId; };
struct IPackProps {
    virtual void AddRef();                    // +0x0
    virtual void Release();                   // +0x4
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t id, PackVariant** out);   // +0x24
};
struct IPackPropMgr {
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
    virtual void GetPropList(uint32_t inst, uint32_t grp, IPackProps** out);   // +0x2c
};
struct IPackResMgr {
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
virtual void v11();
virtual void v12();
virtual void v13();
    virtual int GetRecordKeyList(void* outVec, void* filter, void* dbs);       // +0x38
};
IPackResMgr* __cdecl PackGetManager();        // 0x0067dcd0  EA::ResourceMan::GetManager
IPackPropMgr* __cdecl PackPropertyManager();  // 0x0067de30  SP::PropertyManager
void __cdecl GetPropertyAsText(IPackProps*, uint32_t, void*);        // 0x006a1360
void __cdecl GetPropertyAsKeyInstance(IPackProps*, uint32_t, void*); // 0x006a12a0
void __cdecl GetPropertyAsKey(IPackProps*, uint32_t, void*);         // 0x006a1250
struct PackAutoRef {                          // EA::AutoRefCount<IPackProps>
    IPackProps* p;
    PackAutoRef() { p = 0; }
    ~PackAutoRef() { if (p) p->Release(); }
    IPackProps** Out() { if (p) { IPackProps* t = p; p = 0; t->Release(); } return &p; }
};
struct PackKeyVec {
    PackKey3* b; PackKey3* e; PackKey3* c;
    ~PackKeyVec() { if (b && ((int*)b)[-1]) EDealloc(b); }
};
struct PackFilter {
    void* vt; uint32_t id; int arg;
    ~PackFilter() { vt = vtIMsgHandler; }
};
struct PackInfoVec2 {
    PackInfo** mpBegin; PackInfo** mpEnd; PackInfo** mpCapacity;
    void DoInsertValue(PackInfo** pos, PackInfo* const& v);   // 0x00690b80
};
struct cPackManager {
    PackInfoVec2 mAvailablePacks;   // +0x0 (retail: stored at +0 of the manager object)
    bool Init();
};
// ---- items of slice s007db1b0 end

// @ 0x007db5b0
bool PtrVec::Contains(int key)
{
    for (void** p = mpBegin; p != mpEnd; ++p) {
        if (*(int*)*p == key)
            return true;
    }
    return false;
}

// @ 0x007db620
void* PtrVec::At(int index)
{
    if (index >= 0 && index < (int)(mpEnd - mpBegin))
        return mpBegin[index];
    return 0;
}

// @ 0x007db650
bool cPackManager::Init()
{
    PackKeyVec keys;
    keys.b = 0; keys.e = 0; keys.c = 0;
    PackFilter filt;
    filt.vt = vtPropFilter;
    filt.id = 0xb1b104;
    filt.arg = g_153ed8c;
    PackGetManager()->GetRecordKeyList(&keys, &filt, 0);
    PackKey3* end = keys.e;
    for (PackKey3* it = keys.b; it != end; ++it) {
        PackKey3 key;
        key.a = it->a; key.b = it->b; key.c = it->c;
        PackAutoRef list;
        IPackPropMgr* pm = PackPropertyManager();
        pm->GetPropList(key.a, key.c, list.Out());
        if (list.p) {
            PackInfo* info = new ("App", 0, 0, 0, 0) PackInfo();
            info->mPackId = key.a;
            GetPropertyAsText(list.p, 0xfe1e2bc2, &info->mName.mPlaceholderId);
            PackVariant* v;
            if (list.p && list.p->GetProperty(0x5d1a718, &v) && v->typeId == 9) {
                int* val = (int*)v;
                if (v->flags & 0x30)
                    val = *(int**)v;
                info->mSequenceNumber = *val;
            }
            GetPropertyAsKeyInstance(list.p, 0x5dfef47, &info->mLayoutID);
            GetPropertyAsKey(list.p, 0x5e4de4e, &info->mButtonIconKey);
            GetPropertyAsKey(list.p, 0x5dfef48, &info->mName);
            PackInfo** e2 = mAvailablePacks.mpEnd;
            PackInfo** pos;
            for (pos = mAvailablePacks.mpBegin; pos != e2; ++pos) {
                if (info->mSequenceNumber < (*pos)->mSequenceNumber)
                    break;
            }
            if (pos == e2 && e2 < mAvailablePacks.mpCapacity) {
                mAvailablePacks.mpEnd = e2 + 1;
                if (e2) *e2 = info;
            } else {
                mAvailablePacks.DoInsertValue(pos, info);
            }
        }
    }
    return true;
}
