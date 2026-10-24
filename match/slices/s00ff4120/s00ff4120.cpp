// Slice s00ff4120 (batch gold6): SP::cSPPlayerInventory inventory / tool-set
// methods (AddToInventory, UseToolSet, RemoveItem, the tool-fill helpers, and
// the wrappers around Simulator::cSpaceInventory::RemoveItem / func7Ch).
//
// Flags: /O2 /MD /Gy /TP
//
// The stub classes below carry role-named fields at the retail offsets read off
// the disassembly (the migrated headers hold the 2008 dev-PDB layout, which is
// shifted relative to retail).

#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ---------------------------------------------------------------------------
// singleton accessors (no-argument; the address bytes are masked by the checker)
// ---------------------------------------------------------------------------
void* SP_MessageServer();     // 0x0067dcc0
void* SP_PropertyManager();   // 0x0067de30
void* SP_ToolManager();       // 0x00b3d390 (decompiler labels it eastl::vector::erase)
void* SP_EventLog();          // 0x00b3d3e0
void* SP_SpaceGameGet();      // 0x01002bd0
void* SP_GetUFOSimulator();   // 0x00ffbe50
void* EA_COM_interface_cast(void* p);            // 0x00c87070
void  FUN_0062ffd0(void* a, void* b, void* c);   // 0x0062ffd0 eastl copy_impl::do_copy

struct cInvItem;
struct cFillEntry;
struct cProperty;

// ---------------------------------------------------------------------------
// type stubs
// ---------------------------------------------------------------------------
struct cItemSub {                       // embedded sub-object at cInvItem+0x0c
    virtual void  s00();
    virtual void  s04();
    virtual void  s08();
    virtual void* s0c(u32 id);          // 0x0c  -> tool for the key
    u32 m10;
};

struct cSubObj30 {                      // object pointed to by cInvItem+0x30
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20();
    virtual u8   s24(u32 id, void** out);   // 0x24
};

struct cInvItem {
    virtual void  v00();                // 0x00
    virtual void  v04();                // 0x04  AddRef
    virtual void  v08();                // 0x08  Release
    virtual void  v0c();                // 0x0c
    virtual void  v10();                // 0x10
    virtual void  v14();                // 0x14
    virtual u32*  v18();                // 0x18  item id / key (pointer to a 12-byte key)
    virtual void  v1c();                // 0x1c
    virtual u8    v20();                // 0x20  predicate
    virtual void  v24();                // 0x24
    virtual void  v28();                // 0x28
    u8          pad04[0x0c - 0x04];
    cItemSub    m0c;                    // +0x0c
    u32         m14;                    // +0x14
    u8          pad18[0x24 - 0x18];
    u32         m24;                    // +0x24
    u8          m28;                    // +0x28
    u8          pad29[0x30 - 0x29];
    cSubObj30*  m30;                    // +0x30
    // direct (non-virtual) member callees
    u8    FUN_0104feb0();               // 0x0104feb0
    u8    FUN_0104ccd0();               // 0x0104ccd0
    u32   FUN_0104bd80();               // 0x0104bd80
    u32*  FUN_0104be80(u32* out);       // 0x0104be80
};

struct cProperty {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18();
    virtual u8   p1c(u32 id);           // 0x1c
    virtual void p20(); virtual void p24();
    virtual void* p28_(u32 id);         // 0x28  (container for the id)
    u8*  GetBool();                     // 0x0041e920
};

struct cPropMgr {
    virtual void q00(); virtual void q04(); virtual void q08(); virtual void q0c();
    virtual void q10(); virtual void q14(); virtual void q18(); virtual void q1c();
    virtual void q20(); virtual void q24(); virtual void q28();
    virtual void q2c(u32 a, u32 b, void** out);  // 0x2c
};

struct cToolMgr {                       // singleton from SP_ToolManager()
    virtual void r00();                 // AddRef
    virtual void r04();                 // Release
    u8   CreateToolFromToolID(const void* entry, void** out);   // 0x0104e340
    void ActivateTool(void* tool);                              // 0x0104fbb0
    void DeactivateTool(void* tool);                            // 0x0104fc10
};

struct cMsgServer {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10();
    virtual void m14(u32 a, u32 b, u32 c);              // 0x14
    virtual void m18(u32 a, u32 b, u32 c, u32 d);       // 0x18
};

struct cAutoRef {                       // AutoRefCount<T> (a single owned pointer)
    cInvItem* mp;                       // +0x00
    void Push(cInvItem* p);             // 0x00572620
};

struct cItemVec {                       // sp_ref_vector<T>
    cInvItem** mBegin;                  // +0x00
    cInvItem** mEnd;                    // +0x04
    cInvItem** mCap;                    // +0x08
    void FUN_00d01790(u32 n);                               // 0x00d01790
    void FUN_00f14270(cInvItem** end, cInvItem** val);      // 0x00f14270
    void FUN_005c2170(cInvItem** first, cInvItem** last);   // 0x005c2170
};

struct cFillEntry {                     // 12-byte FillEntry
    void* m0; u32 m4; u32 m8;
};

struct cFillVec {                       // SpVector<FillEntry> at +0x74
    void* mBegin; void* mEnd; void* mCap;
    void push_back(const cFillEntry& v);    // 0x004e19a0
};

struct cSSO {                           // sp_vector-like SSO container returned by v28(id)
    void* mpHeapBegin;                  // +0x00  (also the SSO storage base)
    u32   m04;                          // +0x04
    int   mSize;                        // +0x08
    u32   m0c;                          // +0x0c
    u16   mFlags;                       // +0x10
    u16   mSSOCount;                    // +0x12
};

struct cTranslator { u8 pad00[0x14]; void* m14; };
struct cEventLog {
    void PostFeedbackEvent(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);  // 0x00dd8640
};
struct cVecElem { u8 pad00[0x1c]; u32 m1c; u32 m20; };
struct cVec { u8 pad00[0x0c]; cVecElem* mpElems; void resize(u32 n); };  // IntVector
struct cSimGame { void* FUN_01005180(u32 n); };                     // 0x01005180
struct cToolSetObj { void Assign(void* src); };                     // 0x00c70110
struct cObj508 {
    virtual void a00(); virtual void a04();
    virtual void* a08();                // 0x08
};
struct cPlayerInventory {
    u8 pad00[0x508];
    cObj508 m508;                       // +0x508
};
struct cUFOSim { cPlayerInventory* GetPlayerInventory(); };         // 0x00a1ad60

// ---------------------------------------------------------------------------
// SP::cSPPlayerInventory
// ---------------------------------------------------------------------------
struct cSpaceInvBase {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void w40(); virtual void w44(); virtual void w48(); virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60();
    virtual int   w64(u32 a, void* b);                              // 0x64
    virtual void* w68(u32 a);                                       // 0x68
    virtual void  w6c();
    virtual u8    w70(u32 a, void* b);                              // 0x70
    virtual void  w74();
    virtual void  w78(void* a);                                     // 0x78
    virtual void  w7c();
    virtual void  w80(void* a, u32 b, u32 c);                       // 0x80
    virtual void  w84(); virtual void w88(); virtual void w8c();
    virtual void  w90();
    virtual void  w94(u32 a);                                       // 0x94
    // non-virtual callees implemented in the base classes
    u8 RemoveItemBase(void* item);                                 // 0x00c87d80
    u8 TakeFromInventory(u32 idx, u32 a, u32 b);                   // 0x00c87df0
    u8 AddToInventoryBase(void* item, u32 a, u32 b);               // 0x00c88060
};

struct cSPPlayerInventory : cSpaceInvBase {
    u8        pad04[0x34 - 0x04];
    cItemVec  mInventoryItems;      // +0x34
    u8        pad40[0x4c - 0x40];
    cItemVec  mToolSet;             // +0x4c
    u8        pad58[0x74 - 0x58];
    cFillVec  mFillStack;           // +0x74
    u8        pad80[0x88 - 0x80];
    cAutoRef  mTool88;              // +0x88
    cAutoRef  mTool8c;              // +0x8c
    cAutoRef  mTool90;              // +0x90
    u8        m94;                  // +0x94

    u8   RemoveItem(void* item);                       // 0x00ff4120
    u8   func7Ch(u32 idx, u32 a, u32 b);               // 0x00ff4200
    void FUN_00ff4310();                               // 0x00ff4310
    void FUN_00ff4470(cInvItem* item);                 // 0x00ff4470
    void FUN_00ff4540(cInvItem* item);                 // 0x00ff4540
    void FUN_00ff45e0(cFillEntry* entry);              // 0x00ff45e0
    void FUN_00ff46e0();                               // 0x00ff46e0
    u8   FUN_00ff4840(void* key);                      // 0x00ff4840
    u8   AddToInventory(void* item, u32 a, bool flag); // 0x00ff48d0
    void FUN_00ff4b10(cInvItem* item);                 // 0x00ff4b10
    void UseToolSet(u32 set);                          // 0x00ff4b90
    // callees living elsewhere in the class
    void  SetActiveTool();                             // 0x00ff3e80
    void* GetToolFromToolID(u32* key);                 // 0x00ff3d40
};

extern cTranslator* gTokenTranslator;   // 0x016e0d08
extern u32 gToolKey[3];                 // 0x016dadec
extern u32 gCargoKey[3];                // 0x016daedc

// ---------------------------------------------------------------------------
// SP::cSPPlayerInventory methods
// ---------------------------------------------------------------------------
// @ 0x00ff4120 RemoveItem
u8 cSPPlayerInventory::RemoveItem(void* item) {
    cInvItem* p = (cInvItem*)item;
    if (p != 0) p->v04();
    u8 r = cSpaceInvBase::RemoveItemBase(p);
    if (r != 0) {
        if (mTool88.mp == p) {
            cInvItem* old = mTool88.mp;
            if (old != 0) {
                mTool88.mp = 0;
                old->v08();
            }
        }
        if (mTool8c.mp == p) SetActiveTool();
        if (mTool90.mp == p) {
            cInvItem* old = mTool90.mp;
            if (old != 0) {
                mTool90.mp = 0;
                old->v08();
            }
        }
        ((cMsgServer*)SP_MessageServer())->m14(0x5e793ad, (u32)p, 0);
        ((cMsgServer*)SP_MessageServer())->m18(0x57f3749, 0, 0, 0);
        if (p != 0) p->v08();
        return 1;
    }
    if (p != 0) p->v08();
    return 0;
}

// @ 0x00ff4200 func7Ch
u8 cSPPlayerInventory::func7Ch(u32 idx, u32 a, u32 b) {
    cInvItem* it = mInventoryItems.mBegin[idx];
    if (it != 0) it->v04();
    u8 r = cSpaceInvBase::TakeFromInventory(idx, a, b);
    if (r != 0) {
        void* id = it->v18();
        u8 has = w70(it->m14, id);
        if (has != 0) {
            ((cMsgServer*)SP_MessageServer())->m14(0x635ae7e, (u32)it, 0);
        } else {
            if (mTool88.mp == it) {
                cInvItem* old = mTool88.mp;
                if (old != 0) {
                    mTool88.mp = 0;
                    old->v08();
                }
            }
            if (mTool8c.mp == it) SetActiveTool();
            if (mTool90.mp == it) {
                cInvItem* old = mTool90.mp;
                if (old != 0) {
                    mTool90.mp = 0;
                    old->v08();
                }
            }
            ((cMsgServer*)SP_MessageServer())->m14(0x5e793ad, (u32)it, 0);
        }
        ((cMsgServer*)SP_MessageServer())->m18(0x57f3749, 0, 0, 0);
        it->v08();
        return 1;
    }
    if (it != 0) it->v08();
    return 0;
}

// @ 0x00ff4310 FUN_00ff4310
void cSPPlayerInventory::FUN_00ff4310() {
    cProperty* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
    ((cPropMgr*)pm)->q2c(0x59252ee9, 0x30608f0b, (void**)&prop);
    void* tm = SP_ToolManager();
    if (tm != 0) ((cToolMgr*)tm)->r00();
    void* out = 0;
    if (prop != 0 && prop->p1c(0x6553d45) != 0) {
        cSSO* vec = (cSSO*)prop->p28_(0x6553d45);
        u16 f = vec->mFlags;
        cFillEntry* data;
        int count;
        if ((f & 0x30) != 0) {
            data = (cFillEntry*)vec->mpHeapBegin;
            count = vec->mSize;
        } else {
            data = vec->mSSOCount ? (cFillEntry*)vec : 0;
            count = vec->mSSOCount ? 1 : 0;
        }
        if (count > 0) {
            do {
                cFillEntry entry;
                entry.m0 = *(void**)data;
                entry.m4 = 0;
                entry.m8 = 0;
                if (out != 0) {
                    cInvItem* old = (cInvItem*)out;
                    out = 0;
                    old->v08();
                }
                ((cToolMgr*)tm)->CreateToolFromToolID(&entry, &out);
                if (out != 0) ((cSpaceInvBase*)this)->w80(out, 0, 1);
                data = data + 1;
                count = count - 1;
            } while (count != 0);
        }
    }
    if (out != 0) ((cInvItem*)out)->v08();
    if (tm != 0) ((cToolMgr*)tm)->r04();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
}

// @ 0x00ff4470 FUN_00ff4470
void cSPPlayerInventory::FUN_00ff4470(cInvItem* item) {
    void* id = item->v18();
    int i = w64(item->m14, id);
    if (i < 0) return;
    cInvItem* tool = mInventoryItems.mBegin[i];
    cInvItem* target;
    if (tool->v20() != 0) target = mTool88.mp;
    else target = (cInvItem*)tool->m0c.s0c(0x707459f0);
    if (target == 0) return;
    u8 one = 1;
    if (target->FUN_0104feb0() == 0 && target->FUN_0104ccd0() == 0) {
        SetActiveTool();
        mTool8c.Push(target);
        if (tool->v20() != 0) {
            mTool90.Push(tool);
            tool->m28 = one;
        }
    }
    target->m28 = one;
    ((cMsgServer*)SP_MessageServer())->m14(0x61dae5c, (u32)target, 0);
    ((cToolMgr*)SP_ToolManager())->ActivateTool(target);
}

// @ 0x00ff4540 FUN_00ff4540
void cSPPlayerInventory::FUN_00ff4540(cInvItem* item) {
    void* id = item->v18();
    int i = w64(item->m14, id);
    if (i < 0) return;
    cInvItem* tool = mInventoryItems.mBegin[i];
    cInvItem* target;
    if (tool->v20() != 0) target = mTool88.mp;
    else target = (cInvItem*)tool->m0c.s0c(0x707459f0);
    if (target == 0) return;
    if (target == mTool8c.mp) {
        SetActiveTool();
        return;
    }
    ((cMsgServer*)SP_MessageServer())->m14(0x61dae65, (u32)target, 0);
    ((cToolMgr*)SP_ToolManager())->DeactivateTool(target);
    target->m28 = 0;
}

// @ 0x00ff45e0 FUN_00ff45e0
void cSPPlayerInventory::FUN_00ff45e0(cFillEntry* entry) {
    cInvItem* local = 0;
    ((cToolMgr*)SP_ToolManager())->CreateToolFromToolID(entry, (void**)&local);
    if (local == 0) return;
    ((cSpaceInvBase*)this)->w80(local, 0, 1);
    cSubObj30* sub = local->m30;
    void* prop = 0;
    if (sub == 0
        || sub->s24(0x6723e59, &prop) == 0
        || *(u16*)((u8*)prop + 0x12) != 1
        || *((cProperty*)prop)->GetBool() != 0) {
        gTokenTranslator->m14 = local;
        ((cEventLog*)SP_EventLog())->PostFeedbackEvent(0x15e1a624, 0x131a9f54, 0, 0, 1, 0);
    }
    cVec* vec = (cVec*)((cSimGame*)SP_SpaceGameGet())->FUN_01005180(0xf);
    vec->resize(9);
    vec->mpElems->m1c = (u32)entry->m0;
    vec->mpElems->m20 = 0;
    if (local != 0) local->v08();
}

// @ 0x00ff46e0 FUN_00ff46e0
void cSPPlayerInventory::FUN_00ff46e0() {
    cProperty* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
    ((cPropMgr*)pm)->q2c(0x59252ee9, 0x30608f0b, (void**)&prop);
    void* tm = SP_ToolManager();
    if (tm != 0) ((cToolMgr*)tm)->r00();
    if (prop != 0 && prop->p1c(0xf0609ec3) != 0) {
        cSSO* vec = (cSSO*)prop->p28_(0xf0609ec3);
        u16 f = vec->mFlags;
        cFillEntry* data;
        int count;
        if ((f & 0x30) != 0) {
            data = (cFillEntry*)vec->mpHeapBegin;
            count = vec->mSize;
        } else {
            data = vec->mSSOCount ? (cFillEntry*)vec : 0;
            count = vec->mSSOCount ? 1 : 0;
        }
        void* out = 0;
        mInventoryItems.FUN_00d01790(count);
        if (count > 0) {
            do {
                cFillEntry entry;
                entry.m0 = *(void**)data;
                entry.m4 = 0;
                entry.m8 = 0;
                if (out != 0) {
                    cInvItem* old = (cInvItem*)out;
                    out = 0;
                    old->v08();
                }
                ((cToolMgr*)tm)->CreateToolFromToolID(&entry, &out);
                if (out != 0) ((cSpaceInvBase*)this)->w80(out, 0, 1);
                data = data + 1;
                count = count - 1;
            } while (count != 0);
        }
        if (out != 0) ((cInvItem*)out)->v08();
    }
    if (tm != 0) ((cToolMgr*)tm)->r04();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
}

// @ 0x00ff4840 FUN_00ff4840
u8 cSPPlayerInventory::FUN_00ff4840(void* key) {
    cInvItem** it = mToolSet.mBegin;
    cInvItem** end = mToolSet.mEnd;
    if (it == end) return 0;
    do {
        u32* k = it[0]->v18();
        if (k[0] == ((u32*)key)[0] && k[1] == ((u32*)key)[1] && k[2] == ((u32*)key)[2]) {
            ((cSpaceInvBase*)this)->w80(it[0], 0, 1);
            cInvItem** e = mToolSet.mEnd;
            cInvItem** src = it + 1;
            if (src < e) FUN_0062ffd0(src, e, it);
            mToolSet.mEnd = (cInvItem**)((u8*)mToolSet.mEnd - 4);
            cInvItem* last = *(cInvItem**)mToolSet.mEnd;
            if (last != 0) last->v08();
            return 1;
        }
        it = it + 1;
    } while (it != end);
    return 0;
}

// @ 0x00ff48d0 AddToInventory
u8 cSPPlayerInventory::AddToInventory(void* item_, u32 a, bool flag) {
    cInvItem* item = (cInvItem*)item_;
    cInvItem* tool = 0;
    if (item != 0) tool = (cInvItem*)item->m0c.s0c(0x707459f0);
    cInvItem* found = 0;
    if (tool != 0) {
        u32 buf[3];
        u32* k = tool->FUN_0104be80(buf);
        if (k[0] != gToolKey[0] || k[1] != gToolKey[1] || k[2] != gToolKey[2]) {
            u32 buf2[3];
            u32* k2 = tool->FUN_0104be80(buf2);
            found = (cInvItem*)GetToolFromToolID(k2);
            if (found == 0) return 0;
        }
    }
    int idx = w64(item->m14, item->v18());
    u8 r = cSpaceInvBase::AddToInventoryBase(item, a, (u32)flag);
    if (r == 0) return 0;
    if (tool != 0) {
        if (flag) {
            if (tool->FUN_0104bd80() == 0xa8cfdbda) ((cSpaceInvBase*)this)->w94(5);
            if (tool->FUN_0104feb0() != 0) FUN_00ff4470(tool);
        }
        void* ufo = SP_GetUFOSimulator();
        if (ufo != 0) {
            cPlayerInventory* inv = ((cUFOSim*)ufo)->GetPlayerInventory();
            if (inv != 0) {
                void* src = inv->m508.a08();
                ((cToolSetObj*)((u8*)tool + 0x114))->Assign(src);
            }
        }
        if (flag && found != 0) {
            if (mTool8c.mp == found) FUN_00ff4470(tool);
            item->m24 = found->m24;
            mFillStack.push_back(*(cFillEntry*)found->v18());
            ((cSpaceInvBase*)this)->w78(found);
        }
    }
    if (flag) {
        m94 = 1;
        if (idx < 0) {
            ((cMsgServer*)SP_MessageServer())->m14(0x5e793a6, (u32)item, 0);
            u32* id = item->v18();
            if (id[0] == gCargoKey[0] && id[1] == gCargoKey[1] && id[2] == gCargoKey[2]) {
                void* t = ((cSpaceInvBase*)this)->w68((u32)gCargoKey);
                mTool88.Push((cInvItem*)EA_COM_interface_cast(t));
            }
        } else {
            ((cMsgServer*)SP_MessageServer())->m14(0x635ae73, (u32)mInventoryItems.mBegin[idx], 0);
        }
    }
    ((cMsgServer*)SP_MessageServer())->m18(0x57f3749, 0, 0, 0);
    return 1;
}

// @ 0x00ff4b10 FUN_00ff4b10
void cSPPlayerInventory::FUN_00ff4b10(cInvItem* item) {
    cInvItem** p = mToolSet.mBegin;
    cInvItem** e = mToolSet.mEnd;
    if (p != e) {
        do {
            if (*p == item) return;
            p = p + 1;
        } while (p != e);
    }
    cInvItem* local = item;
    cItemVec& v = mToolSet;
    if (item != 0) item->v04();
    if (v.mEnd < v.mCap) {
        cInvItem** slot = v.mEnd;
        v.mEnd = slot + 1;
        if (slot != 0) {
            *slot = item;
            if (item != 0) item->v04();
        }
        if (local != 0) local->v08();
    } else {
        v.FUN_00f14270(v.mEnd, &local);
        if (local != 0) local->v08();
    }
}

// @ 0x00ff4b90 UseToolSet
void cSPPlayerInventory::UseToolSet(u32 set) {
    cProperty* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
    ((cPropMgr*)pm)->q2c(0x59252ee9, 0x30608f0b, (void**)&prop);
    if (prop == 0) return;
    if (prop->p1c(set) == 0) return;
    mInventoryItems.FUN_005c2170(mInventoryItems.mBegin, mInventoryItems.mEnd);
    ((cSpaceInvBase*)this)->w94(10);
    void* tm = SP_ToolManager();
    if (tm != 0) ((cToolMgr*)tm)->r00();
    cSSO* vec = (cSSO*)prop->p28_(set);
    u16 f = vec->mFlags;
    cFillEntry* data;
    int count;
    if ((f & 0x30) != 0) {
        data = (cFillEntry*)vec->mpHeapBegin;
        count = vec->mSize;
    } else {
        data = vec->mSSOCount ? (cFillEntry*)vec : 0;
        count = vec->mSSOCount ? 1 : 0;
    }
    void* out = 0;
    if (count > 0) {
        do {
            cFillEntry entry;
            entry.m0 = *(void**)data;
            entry.m4 = 0;
            entry.m8 = 0;
            if (out != 0) {
                cInvItem* old = (cInvItem*)out;
                out = 0;
                old->v08();
            }
            ((cToolMgr*)tm)->CreateToolFromToolID(&entry, &out);
            if (out != 0) {
                cInvItem* made = (cInvItem*)out;
                made->v04();
                if (mToolSet.mEnd < mToolSet.mCap) {
                    cInvItem** slot = mToolSet.mEnd;
                    mToolSet.mEnd = slot + 1;
                    if (slot != 0) {
                        *slot = made;
                        made->v04();
                    }
                } else {
                    mToolSet.FUN_00f14270(mToolSet.mEnd, &made);
                }
                if (made != 0) made->v08();
            }
            data = data + 1;
            count = count - 1;
        } while (count != 0);
    }
    if (out != 0) ((cInvItem*)out)->v08();
    if (tm != 0) ((cToolMgr*)tm)->r04();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
}