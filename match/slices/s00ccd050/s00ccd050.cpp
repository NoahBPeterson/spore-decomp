// Slice s00ccd050: 0x00CCD050..0x00CCDC30.
//  0x00ccd050  SP::cTribeDisplayStrategy::Deactivate                 (848 B)
//  0x00ccd3a0  SP::cTribeDisplayStrategy::UpdateTargetedTreeEffects  (1277 B)
//  0x00ccd8a0  SP::cTribeDisplayStrategy::MakeTribeIcons             (902 B)
//  0x00ccdc30  SP::cTribeDisplayStrategy::DrawLayer                  (310 B, migrated)
//
// Retail layout of cTribeDisplayStrategy (recovered from the asm; see s00ccdd70 and
// s00ccc190 for the same object):
//   +0x000 vtable                          +0x038/+0x3c/+0x40 MixIn base vtables
//   +0x04c global tribe UI                 +0x050 mode strategy (refcount slot 0)
//   +0x054 flag                            +0x058 message server      +0x05c handler
//   +0x060 message-id table                +0x064 id count (10)       +0x068 0
//   +0x06c 0                               +0x070 civ minimap (slot 1)
//   +0x074 layout (slot 2)                 +0x078 posse set (refcount slot 0)
//   +0x094 eastl rbtree header (count +0x94, anchor +0x98 self, end +0x9c, node +0xa0,
//         +0xa4 byte, +0xa8 flags)
//   +0x0b0 ornament (refcount slot 0)      +0x0b4 swatch manager (slot 1)
//   +0x0b8 cModelInstanceSet[2] (stride 0x60; +0xc4/+0x124 assign 0x38-byte transforms)
//   +0x178 two 0xA0-byte ornament tables
//   +0x2b8 swatch (slot 7 then manager, refcount)   +0x2bc swatch window (slot 1)
//   +0x2c0 ornament open-hash container (buckets +0x2c4, bucket count +0x2c8, size +0x2cc)
//   +0x4d8 dynamic array                   +0x4dc/+0x4e0 scratch
//   +0x4f0/+0x4f4 cSelectionEffectStreamer helpers (slot 1)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;
typedef signed   char  i8;

struct Vector3 { float x, y, z; };

// Dispatch through vftable slot <byteOffset> of an object whose exact class is not known
// here (the accepted convention for an unknown vtable).
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

// --------------------------------------------------------------------------- opaque services
void* NounManager();                     // 0x00b3d300
void* TribeModeInstance();               // 0x00cd40b0  SP::cTribeModeStrategy::Instance
void* PlanetModel();                     // 0x00b3d350
void* FindWindowByID(u32 id);            // 0x00e012b0  cSPUIGlobalUI::FindWindowByID
void* FUN_00401020(void* swatch);        // 0x00401020  SwatchManager::GetOrCreate
struct GlobalUI { void* FindWindowByID(u32 id); };   // 0x00e012b0 thiscall

void  FUN_00b759b0(void* buckets, u32 count);        // 0x00b759b0  free every bucket node
void  FUN_00ce8d80(void* self);                      // 0x00ce8d80  cSelectionEffectStreamer
void cSPUILayout_Shutdown(void* self, u32 flag);     // 0x00811ad0
void  FUN_005f0a60(void* self, void* obj);           // 0x005f0a60  SwatchManager::RemoveContent
void  FUN_00cc9890();                                // 0x00cc9890
void  VerbTray_Update(float f);                      // 0x00d4a930
void* GetCameraCtl();                                // 0x00b3d280
void  FUN_00e0f9c0(void* minimap, void* citizen, int a, int b);  // 0x00e0f9c0
void* FUN_00b88590(void* key);                       // 0x00b88590  planet model GetContinent
void* FUN_00b3d440(void* pos, float radius, void* out, void* filter);   // 0x00b3d440
void  FUN_00b09070(void* self, void* pos, void* out);                   // 0x00b09070
void  FUN_00b09340(void* self, float radius, void* out, int a, int b);  // 0x00b09340
u32   FUN_00b05980(void* obj);                       // 0x00b05980
void  FUN_00b01b50(void* obj, int a, int b);         // 0x00b01b50
void* FUN_00bca2c0(void* mgr);                       // 0x00bca2c0  FirstPending

// retail thiscall service entry points (the receiver is the implicit `ecx`), modelled as
// members of opaque wrappers so the pointer lands in ecx exactly as retail does.
struct Svc28a80 { void Call(); };                    // 0x00e28a80
struct Svc8ba0  { void Call(); };                    // 0x00cc8ba0
struct SvcE31130{ void Call(); };                    // 0x00e31130
struct SvcEB6280{ void Call(void* node); };          // 0x00eb6280
struct SvcB225d0{ void Call(void* noun); };          // 0x00b225d0
struct Svc81ad0 { void Shutdown(u32 flag); };        // 0x00811ad0
struct Svc5f0a60{ void RemoveContent(); };           // 0x005f0a60
struct SvcReleaseIf { void Call(); };                // 0x006f33d0
struct SvcAssign  { void* Call(const void* src); };  // 0x00537dc0 cSPTransformOps::Assign
struct Svc759b0   { void Free(void* buckets, u32 count); };  // 0x00b759b0
struct Svc8d80    { void Call(); };                  // 0x00ce8d80

// message handler
void  EA_RemoveHandler(void* server, void* handler, void* table, u32 count, u32 zero);  // 0x00571db0

// --------------------------------------------------------------------------- engine interfaces
struct RefObj {                                  // intrusive refcount object, slot 1 release
    virtual void Destroy(int flag);              // +0x00
    virtual void Unbind();                       // +0x04
    i32 mRef;                                    // +0x04
};

template <class T> inline void DecRef(T* p, int mode)
{
    i32 r = --p->mRef;
    if (r == 0) {
        p->mRef = 1;
        p->Destroy(mode);
    }
}

struct UiWindow {                                // window handle (unknown vtable)
    char pad[0x108];
    void v108(void* arg);                        // width-only dispatch below
};

struct Swatch {                                  // swatch object at +0x2b8
    virtual void Destroy(int flag);              // +0x00
    virtual void Unbind();                       // +0x04
    virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018();
    virtual void v01c();                         // +0x1c  called before the manager drop
    i32 mRef;                                    // +0x04
};

struct cSphere {                                 // cTerrainEditor's terrain sphere
    u8    pad00[0x10f0];
    float mA;                                    // +0x10f0
    float mB;                                    // +0x10f4
};
struct cTerrainEditor { cSphere* GetCurrentTerrainSphere(); };          // 0x00f67d90
struct cNounMgr { void* SetGameDataOwner2(); };                          // 0x00bfc5f0
struct cCam {
    void*  FUN_00b13900(void* out);              // 0x00b13900
    float* FUN_00b10200();                       // 0x00b10200
};
struct c70Obj {
    virtual void v000();
    virtual void v004();                         // +0x04  release
    void FUN_00e0c490(float* b, void* a);        // 0x00e0c490
};
struct c50Obj {
    virtual void v000();
    virtual void v004();                         // +0x04  release
    void FUN_00e313c0(float f);                  // 0x00e313c0
};
struct c74Obj {
    virtual void v000();
    virtual void v004();
    virtual void v008();                         // +0x08  release
};
void ReleaseIf(void* self);                      // 0x006f33d0
void cSPTransformOps_Assign(void* self, const void* src);   // 0x00537dc0
struct c78Obj {
    virtual void v000();
    void FUN_00ccb2c0(float f);                  // 0x00ccb2c0
};
struct cProgressBar {
    virtual void Destroy(int flag);              // +0x00
    virtual void v004();
    void Update(float progress, void* amount);   // 0x00e29da0
    i32 mRef;                                    // +0x04
};
struct cTribe {
    u8 pad00[0xa4];
    virtual void* v0a4();                        // +0xa4
};
struct tLocal3 { int a, b, c; };

// --------------------------------------------------------------------------- string tables
struct XVec {                                    // model set transform vector at +0xc
    u8* mpBegin;                                 // +0x0c
    u8* mpEnd;                                   // +0x10
    u8* mpCapacity;                              // +0x14
};
struct DisplayBlock {                            // cModelInstanceSet, stride 0x60
    u8   pad00[0x0c];
    XVec mVec;                                   // +0x0c
    u8   pad18[0x60 - 0x18];
};

struct TreeNode {                                // open-hash node of the +0x2c0 container
    u8   pad00[0x08];
    RefObj* mpValue;                             // +0x08
    u8   pad0c[0x04];
    TreeNode* mpNext;                            // +0x10
};
struct TreeHeader {                              // eastl rbtree header at +0x94
    u32   mCount;                                // +0x00
    void* mpAnchor;                              // +0x04
    void* mpEnd;                                 // +0x08
    void* mpNode;                                // +0x0c
    u8    mB10;                                  // +0x10
    u8    pad11[3];
    u32   mFlags;                                // +0x14
};
struct Pool {                                    // ornament open-hash container at +0x2c0
    u8       pad00[0x04];
    TreeNode** mpBuckets;                        // +0x04
    u32      mBucketCount;                       // +0x08
    u32      mSize;                              // +0x0c
    u8       pad10[0x218 - 0x10];
};

// --------------------------------------------------------------------------- the strategy
struct cTribeDisplayStrategy {
    void*   m_vtable;                            // +0x000
    u8      pad004[0x038 - 0x004];
    void*   m_vt38;                              // +0x038
    void*   m_vt3c;                              // +0x03c
    void*   m_vt40;                              // +0x040
    u8      pad044[0x04c - 0x044];
    void*   m_ui;                                // +0x04c
    c50Obj* m50;                                 // +0x050
    u8      m_b54;                               // +0x054
    u8      pad055[0x058 - 0x055];
    void*   m_server;                            // +0x058
    void*   m_handler;                           // +0x05c
    void*   m_idTable;                           // +0x060
    u32     m_idCount;                           // +0x064
    u32     m_p68;                               // +0x068
    u8      pad06c[4];
    c70Obj* m70;                                 // +0x070
    c74Obj* m74;                                 // +0x074
    c78Obj* m78;                                 // +0x078
    u8      pad07c[0x094 - 0x07c];
    TreeHeader m_tree;                           // +0x094
    u8      pad0ac[0x0b0 - 0x0ac];
    cProgressBar* mb0;                           // +0x0b0
    u8      pad0b4[4];
    DisplayBlock m_blocks[2];                    // +0x0b8  stride 0x60
    // +0x178: two 0x60-stride transform-vector blocks (vector at block+4)
    u8      m_vecs[2 * 0xa0];                    // +0x178
    Swatch* m_swatch;                            // +0x2b8
    RefObj* m_swatchWin;                         // +0x2bc
    Pool    m_pool;                              // +0x2c0
    u8      pad4d8[0x4dc - 0x4d8];
    void*   m_p4dc;                              // +0x4dc
    u8      pad4e0[0x4f0 - 0x4e0];
    void*   m_helperA;                           // +0x4f0
    void*   m_helperB;                           // +0x4f4

    void Deactivate();                           // 0x00ccd050
    void UpdateTargetedTreeEffects();            // 0x00ccd3a0
    void MakeTribeIcons();                       // 0x00ccd8a0
    void DrawLayer(void* p2, unsigned p3, unsigned p4);   // 0x00ccdc30
    void FUN_00ccc640();                         // 0x00ccc640
    void FUN_00ccd3a0();                         // 0x00ccd3a0
    void OnWinProcAdd(void* p2);                 // 0x010829f0
};

// =========================================================================== 0x00ccd050
// @ 0x00ccd050
void cTribeDisplayStrategy::Deactivate()
{
    if (m_server != 0) {
        void* srv = m_server;
        m_server = 0;
        EA_RemoveHandler(srv, m_handler, m_idTable, m_idCount, m_p68);
    }

    if (m_ui != 0) {
        UiWindow* w = (UiWindow*)((GlobalUI*)m_ui)->FindWindowByID(0x6454b47);
        if (w != 0) {
            void* inst = TribeModeInstance();
            void* arg = inst ? (void*)((char*)inst + 4) : 0;
            ((void(__thiscall*)(void*, void*))(*(void***)w)[0x108 / 4])(w, arg);
        }
        ((void(__thiscall*)(void*))(*(void***)m_ui)[0x0c / 4])(m_ui);
        if (m_ui != 0)
            ((void(__thiscall*)(void*, int))(*(void***)m_ui)[0])(m_ui, 1);
        m_ui = 0;

        if (m70 != 0) {
            c70Obj* p = m70;
            m70 = 0;
            p->v004();
        }
    }

    if (mb0 != 0) {
        ((Svc28a80*)mb0)->Call();
        cProgressBar* p = mb0;
        if (p != 0) {
            mb0 = 0;
            DecRef(p, 1);
        }
    }

    if (m74 != 0) {
        ((Svc81ad0*)m74)->Shutdown(1);
        c74Obj* p = m74;
        if (p != 0) {
            m74 = 0;
            p->v008();
        }
    }

    if (m78 != 0) {
        ((Svc8ba0*)m78)->Call();
        c78Obj* p = m78;
        if (p != 0) {
            m78 = 0;
            ((void(__thiscall*)(void*, int))(*(void***)p)[0])(p, 1);
        }
        ((SvcEB6280*)&m_tree)->Call(m_tree.mpNode);
        m_tree.mpAnchor = &m_tree.mpAnchor;
        m_tree.mpEnd = &m_tree.mpAnchor;
        m_tree.mpNode = 0;
        m_tree.mB10 = 0;
        m_tree.mFlags = 0;
    }

    if (m50 != 0) {
        ((SvcE31130*)m50)->Call();
        c50Obj* p = m50;
        if (p != 0) {
            m50 = 0;
            p->v004();
        }
    }

    if (m_swatch != 0) {
        Swatch* p = m_swatch;
        ((void(__thiscall*)(void*))(*(void***)p)[0x1c / 4])(p);
        void* mgr = FUN_00401020(p);
        ((Svc5f0a60*)mgr)->RemoveContent();
        if (p != 0) {
            m_swatch = 0;
            p->Unbind();
        }
    }
    if (m_swatchWin != 0) {
        RefObj* p = m_swatchWin;
        m_swatchWin = 0;
        p->Unbind();
    }

    {
        u8* inst = (u8*)TribeModeInstance();
        void* nm = NounManager();
        RefObj** pp = (RefObj**)(inst + 0x258);
        for (int n = 0x14; n != 0; --n, ++pp) {
            RefObj* o = *pp;
            if (o != 0) {
                ((SvcB225d0*)nm)->Call(o);
                o = *pp;
                if (o != 0) {
                    *pp = 0;
                    o->Unbind();
                }
            }
        }
        pp = (RefObj**)(inst + 0x2a8);
        for (int n = 0x14; n != 0; --n, ++pp) {
            RefObj* o = *pp;
            if (o != 0) {
                ((SvcB225d0*)nm)->Call(o);
                o = *pp;
                if (o != 0) {
                    *pp = 0;
                    o->Unbind();
                }
            }
        }
    }

    {
        u8* p = (u8*)&m_blocks[0];
        for (int n = 2; n != 0; --n, p += 0x60)
            ((SvcReleaseIf*)p)->Call();
    }

    {
        XVec* v = (XVec*)(m_vecs + 4);
        for (int n = 2; n != 0; --n, v += 0x60 / sizeof(XVec)) {
            u8* b = v->mpBegin;
            u8* e = v->mpEnd;
            while (b != e) {
                ((SvcAssign*)b)->Call(e);
                b += 0x38;
                e += 0x38;
            }
            int cnt = (int)(e - b) / 0x38;
            v->mpEnd = v->mpEnd + cnt * 0x38;
        }
    }

    {
        Pool& p = m_pool;
        TreeNode** bucket = p.mpBuckets;
        TreeNode* n = *bucket;
        if (n == 0) {
            ++bucket;
            while (*bucket == 0)
                ++bucket;
            n = *bucket;
        }
        TreeNode* end = p.mpBuckets[p.mBucketCount];
        while (n != end) {
            if (n->mpValue != 0)
                ((void(__thiscall*)(void*, int))(*(void***)n->mpValue)[0x0c / 4])(n->mpValue, 1);
            n = n->mpNext;
            if (n == 0) {
                ++bucket;
                do { n = *bucket; } while (n == 0);
            }
        }
        ((Svc759b0*)&p)->Free(p.mpBuckets, p.mBucketCount);
        p.mSize = 0;
    }

    ((Svc8d80*)m_helperA)->Call();
    ((Svc8d80*)m_helperB)->Call();
}

// =========================================================================== 0x00ccd3a0
// @ 0x00ccd3a0
void cTribeDisplayStrategy::UpdateTargetedTreeEffects()
{
    // Rebuild the shared 0x18-byte vertex scratch from this object's +0x4d8 array and
    // mark the player tribe's rideable-tree markers.  Not reconstructed (eastl
    // fixed-vector / rbtree template bodies, atexit-guarded statics, _ftol2 packing).
}

// =========================================================================== 0x00ccd8a0
// @ 0x00ccd8a0
void cTribeDisplayStrategy::MakeTribeIcons()
{
    // Minimap icon pass (RemoveAllIcons, the citizen/tribe icon filters and the final
    // MakeTribeIcon loop).  Not reconstructed (eastl vector sweeps at 0x902 bytes).
}

// ---------------------------------------------------------------- 0x00ccdc30

// @ 0x00ccdc30
void cTribeDisplayStrategy::DrawLayer(void* p2, unsigned p3, unsigned p4)
{
    float f = (float)p3;
    VerbTray_Update(f * 0.0001f);

    cCam* cam = (cCam*)GetCameraCtl();
    if (cam != 0 && m70 != 0) {
        tLocal3 local_c;
        void* a = cam->FUN_00b13900(&local_c);
        float* b = cam->FUN_00b10200();
        m70->FUN_00e0c490(b, a);
    }

    cNounMgr* nm = (cNounMgr*)NounManager();
    cTribe* tribe = (cTribe*)nm->SetGameDataOwner2();
    if (tribe != 0) {
        cTerrainEditor* te = (cTerrainEditor*)NounManager();
        cSphere* s = te->GetCurrentTerrainSphere();
        float* q = &s->mA;
        if (s->mA > s->mB)
            q = &s->mB;
        float ratio = *q / s->mB;
        if (mb0 != 0) {
            void* v = tribe->v0a4();
            mb0->Update(ratio, v);
        }
        FUN_00ccc640();
        FUN_00ccd3a0();
        FUN_00cc9890();
        m78->FUN_00ccb2c0(f * 0.001f);
        m50->FUN_00e313c0((float)p4 * 0.001f);
        OnWinProcAdd(p2);
    }
}
