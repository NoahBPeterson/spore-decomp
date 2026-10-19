// src/game/UTFSpore_Win32/ImageCursorProvider.cpp -- migrated from slice(s) s0097cea0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ImageCursorProvider.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWinControls/ImageDrawable.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"
#include <math.h>
#include <new>

// ---- items of slice s0097cea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ImageCursorProvider {
    virtual void slot0();
    virtual void slot1();   // added to make the vtable live
    char pad[0x0c];
    void* AsInterface(unsigned int id);
};
namespace Cr {
struct Target2D {                       // object returned by RenderContext::Begin2D
    virtual void slot0();
    virtual void SetColor(unsigned int argb);
};
}
namespace Cr {
struct RenderContext {
    Target2D* Begin2D(int);             // 0x95bc10, thiscall ret 4
};
}
namespace Cur {
#define VT(o, i) ((*(void***)(o))[i])
}
namespace Cur {
#define VCALL0(R, o, i)    (((R(__thiscall*)(void*))VT(o, i))(o))
}
namespace Cur {
#define VCALL1(R, o, i, A, a) (((R(__thiscall*)(void*, A))VT(o, i))(o, a))
}
namespace Cur {
struct IRef {                            // AutoRefCount target: slot 0 AddRef, slot 1 Release
    virtual int AddRef() throw();
    virtual int Release() throw();
};
}
namespace Cur {
struct ImgRef {                          // EA::AutoRefCount<Image>
    IRef* p;
    ImgRef() throw() : p(0) {}
    ImgRef(const ImgRef& o) throw() : p(o.p) { if (p) p->AddRef(); }
    ~ImgRef() throw() { if (p) p->Release(); }
    ImgRef& operator=(IRef* q) {
        IRef* old = p;
        if (q != old) {
            if (q) q->AddRef();
            p = q;
            if (old) old->Release();
        }
        return *this;
    }
};
}
namespace Cur {
struct PlaceTag {};
}
namespace Cur {
struct ImageCursor {                     // 0xc bytes
    int mX, mY;                          // mPickPoint, deliberately left uninitialised
    ImgRef mpImage;                      // +8
    ImageCursor() throw() {}
    ImageCursor(const ImageCursor& o) throw() : mX(o.mX), mY(o.mY), mpImage(o.mpImage) {}
};
}
namespace Cur {
struct CursorPair {                      // eastl::pair<unsigned const, ImageCursor>, 0x10 bytes
    unsigned first;
    ImageCursor second;
    CursorPair(unsigned k, const ImageCursor& v) throw() : first(k), second(v) {}
    CursorPair(const CursorPair& o) throw() : first(o.first), second(o.second) {}
    static void* operator new(unsigned, void* p, PlaceTag) throw() { return p; }
    static void operator delete(void*, void*, PlaceTag) throw() {}
};
}
namespace Cur {
struct HNode {                           // eastl hash_node, 0x14 bytes
    CursorPair mValue;                   // +0
    HNode* mpNext;                       // +0x10
};
}
namespace Cur {
struct HIter { HNode* mpNode; HNode** mpBucket; };
}
namespace Cur {
struct TrueTag { char pad; TrueTag() : pad(0) {} };
}
namespace Cur {
void*  ea_alloc(unsigned, const char*, int, int, const char*, int);   // 0x00f473a0
}
namespace Cur {
void   ea_free(void*);                                                // 0x00f47380
}
namespace Cur {
struct Table {                           // eastl::hashtable<unsigned, pair<..>, fixed_hashtable_allocator<65,20,64,4,0,1>, ...>
    int       pad0;                      // +0
    HNode**   mpBucketArray;             // +4
    unsigned  mnBucketCount;             // +8
    unsigned  mnElementCount;            // +0xc
    int       policy[3];                 // +0x10 prime_rehash_policy
    HNode*    mpFreeList;                // +0x1c
    int       pad20;
    void*     mpPoolBegin;               // +0x24
    void*     mpPoolEnd;                 // +0x28
    unsigned  mnNodeSize;                // +0x2c
    void*     mpInlineBuckets;           // +0x30
    HNode* End() const { return mpBucketArray[mnBucketCount]; }
    HNode*  AllocNodeCopy(const CursorPair* src);                  // 0x97dd80
    HNode** AllocBuckets(unsigned n);                              // 0xa21e40, ret 4
    HIter*  Find(HIter* out, const unsigned* key) throw();        // 0xdb4780
    void    DoFreeNodes(HNode** buckets, unsigned n);              // 0x97e030
    void    DoRehash(unsigned n);                                  // 0x97dc30
    HIter*  DoInsertValue(HIter* out, const CursorPair* v, TrueTag t) throw(); // 0x97df70
    ImageCursor* Index(const unsigned* key);                       // 0x97e0b0
};
}
namespace Cur {
struct Sub4 {                            // second interface at CursorWindow+4
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual int  Slot5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
    virtual void Slot36();
    virtual void v37();
    virtual void Slot38();
};
}
namespace Cur {
struct Target2D {
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
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual void DrawImage(float x, float y, IRef* img);          // slot 24
};
}
namespace Cur {
struct RenderContext {
    Target2D* Begin2D(int);              // 0x95bc10, thiscall ret 4
    void End2D();                        // 0x95bb20, thiscall
};
}
namespace Cur {
struct Vec3Sink { void Apply(const float* v3); };                 // 0x95e890, thiscall ret 4
}
namespace Cur {
struct Pt { int x, y; };
}
namespace Cur {
struct PrimaryBase { virtual void p0(); };
}
namespace Cur {
struct CursorWindowObj : PrimaryBase, Sub4 {   // Sub4 is the interface at +4
    char    pad[0x204];                  // +8 .. +0x20c
    ImageCursor* mpCursor;               // +0x20c
    Pt      mMouse;                      // +0x210, +0x214
    bool    OnRebuild(RenderContext* ctx);                // 0x97db30, ret 4
    void    PushMouse(Vec3Sink* sink);                    // 0x97db90, ret 4
};
}
namespace Cur {
struct Provider {
    void*   vt0;                         // +0
    void*   vt1;                         // +4
    int     mRefCount;                   // +8
    Table   mCursorMap;                  // +0xc
    char    pad[0x75c - 0xc - sizeof(Table)];
    CursorWindowObj* mpCursorWindow;     // +0x75c
    void    UpdateMousePosition(const int* pt);           // 0x97dc00, ret 4
    bool    HasCursor(unsigned key);                      // 0x97ddf0, ret 4
    bool    SetCursor(unsigned key);                      // 0x97de20, ret 4
};
}
namespace Cur {
struct Manager {
    void* vt;
};
}
namespace Cur {
Manager* GetManager();                   // 0x957f30
}
namespace Cur {
struct ReadEntry { unsigned key; int x, y; IRef* img; };
}
namespace Cur {
struct ReadList  { int pad0; ReadEntry* mpBegin; unsigned mnCount; };
}
namespace Cur {
struct ReadOwner { int pad0; Provider* mpProvider; };
}
namespace Cur {
bool CursorListMarshaller_Read(ReadOwner* self, ReadList* list);   // 0x97e140, cdecl
}
// ---- items of slice s0097cea0 end

// @ 0x0097da60
void* ImageCursorProvider::AsInterface(unsigned int id)
{
    if (id <= 0xee3f516e) {
        if (id == 0xee3f516e) return this;
        if (id == 0x2ce4360) return this;
        if (id == 0x2cf3268) return this;
    } else if (id == 0xeec58382 && this != 0) {
        return (char*)this + 4;
    }
    return 0;
}

// @ 0x0097dad0
namespace Cur
{
struct Win {
    virtual void w0();                                       // 0x7f31d0
    virtual void w1();                                       // 0x7f31c0
    void SetFlag(unsigned int flag, unsigned char value);    // 0x961760
};
struct IWindow {
    virtual void i0();                                       // 0x95f990
    virtual void i1();                                       // 0x95f9a0
};
struct Window : IWindow, Win {                               // IWindow +0, Win +4
    Window();                                                // 0x962a10
    char pad[0x20c - 8];
};
struct CursorWindowCtor : Window {
    virtual void cw0();                                      // 0x962bc0
    virtual void cw1();                                      // 0x95f960
    virtual void cw2();                                      // 0x960520
    virtual void cw3();                                      // 0x7f3190
    virtual void cw4();                                      // 0xb1fbf0
    virtual void cw5();                                      // 0x961e80
    virtual void cw6();                                      // 0x950bb0
    ImageCursor* mpCursor;   // +0x20c
    int          mMouseX;    // +0x210
    int          mMouseY;    // +0x214
    CursorWindowCtor();
};
CursorWindowCtor::CursorWindowCtor() {
    mpCursor = 0;
    mMouseX = 0;
    mMouseY = 0;
    SetFlag(0x40, 1);
    SetFlag(0x10, 1);
    SetFlag(0x200, 1);
}
}

// @ 0x0097db30
namespace Cur {
bool CursorWindowObj::OnRebuild(RenderContext* ctx)
{
    if (mpCursor) {
        Target2D* t = ctx->Begin2D(0);
        ImageCursor* c = mpCursor;
        t->DrawImage((float)-c->mX, (float)-c->mY, c->mpImage.p);
        ctx->End2D();
    }
    return true;
}
}  // namespace Cur

// @ 0x0097db90
namespace Cur {
void CursorWindowObj::PushMouse(Vec3Sink* sink)
{
    float v[3];
    v[0] = (float)mMouse.x;
    v[1] = (float)mMouse.y;
    v[2] = 0.0f;
    sink->Apply(v);
}
}  // namespace Cur

// @ 0x0097dc00
namespace Cur {
void Provider::UpdateMousePosition(const int* pt)
{
    CursorWindowObj* w = mpCursorWindow;
    w->mMouse.x = pt[0];
    w->mMouse.y = pt[1];
    static_cast<Sub4*>(w)->Slot38();
}
}  // namespace Cur

// @ 0x0097dc30
namespace Cur {
void Table::DoRehash(unsigned n)
{
    HNode** nb = AllocBuckets(n);
    for (unsigned i = 0; i < mnBucketCount; ++i) {
        while (HNode* node = mpBucketArray[i]) {
            unsigned idx = node->mValue.first % n;
            mpBucketArray[i] = node->mpNext;
            node->mpNext = nb[idx];
            nb[idx] = node;
        }
    }
    HNode** old = mpBucketArray;
    if (mnBucketCount > 1 && (void*)old != mpInlineBuckets) {
        if ((void*)old >= mpPoolBegin && (void*)old < mpPoolEnd) {
            HNode* fl = mpFreeList;
            mpFreeList = (HNode*)old;
            *(HNode**)old = fl;
        } else {
            ea_free(old);
        }
    }
    mnBucketCount = n;
    mpBucketArray = nb;
}
}  // namespace Cur

// @ 0x0097dd80
namespace Cur {
HNode* Table::AllocNodeCopy(const CursorPair* src)
{
    HNode* n = mpFreeList;
    if (n) {
        mpFreeList = *(HNode**)n;
    } else {
        n = (HNode*)ea_alloc(mnNodeSize, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    new ((void*)n, PlaceTag()) CursorPair(*src);
    n->mpNext = 0;
    return n;
}
}  // namespace Cur

// @ 0x0097ddf0
namespace Cur {
bool Provider::HasCursor(unsigned key)
{
    Table* t = &mCursorMap;
    HNode* end = t->End();
    HIter it;
    return t->Find(&it, &key)->mpNode != end;
}
}  // namespace Cur

// @ 0x0097de20
namespace Cur {
bool Provider::SetCursor(unsigned key)
{
    bool ok = false;
    Manager* mgr = GetManager();
    if (!mgr) return ok;
    void* obj = VCALL0(void*, mgr, 1);
    if (!obj) return false;
    ImageCursor* cur = 0;
    ok = true;
    if (key) {
        HIter it;
        Table* t = &mCursorMap;
        t->Find(&it, &key);
        if (it.mpNode == t->End()) ok = false;
        else cur = &it.mpNode->mValue.second;
    }
    CursorWindowObj* w = mpCursorWindow;
    w->mpCursor = cur;
    w->Slot36();
    w = mpCursorWindow;
    if (cur) {
        if (!w->Slot5()) {
            w = mpCursorWindow;
            VCALL1(void, obj, 54, void*, w ? static_cast<Sub4*>(w) : 0);
            w = mpCursorWindow;
            VCALL1(void, obj, 58, void*, w ? static_cast<Sub4*>(w) : 0);
        }
    } else {
        if (w->Slot5()) {
            w = mpCursorWindow;
            VCALL1(void, obj, 55, void*, w ? static_cast<Sub4*>(w) : 0);
        }
    }
    return ok;
}
}  // namespace Cur

// @ 0x0097e030
namespace Cur {
void Table::DoFreeNodes(HNode** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        HNode* node = buckets[i];
        while (node) {
            HNode* cur = node;
            node = node->mpNext;
            if (cur->mValue.second.mpImage.p) cur->mValue.second.mpImage.p->Release();
            if (cur != (HNode*)mpInlineBuckets) {
                if ((void*)cur >= mpPoolBegin && (void*)cur < mpPoolEnd) {
                    *(HNode**)cur = mpFreeList;
                    mpFreeList = cur;
                } else {
                    ea_free(cur);
                }
            }
        }
        buckets[i] = 0;
    }
}
}  // namespace Cur

// @ 0x0097e0b0
namespace Cur {
ImageCursor* Table::Index(const unsigned* key)
{
    HIter it;
    Find(&it, key);
    if (it.mpNode != mpBucketArray[mnBucketCount])
        return &it.mpNode->mValue.second;
    ImageCursor def;
    CursorPair v(*key, def);
    TrueTag tag;
    DoInsertValue(&it, &v, tag);
    return &it.mpNode->mValue.second;
}
}  // namespace Cur

// @ 0x0097e140
namespace Cur {
bool CursorListMarshaller_Read(ReadOwner* self, ReadList* list)
{
    Provider* prov = self->mpProvider;
    ReadEntry* e = list->mpBegin;
    unsigned n = list->mnCount;
    Table* t = &prov->mCursorMap;
    t->DoFreeNodes(t->mpBucketArray, t->mnBucketCount);
    t->mnElementCount = 0;
    if (n) {
        do {
            IRef* img = e->img;
            if (img) {
                unsigned key = e->key;
                ImageCursor* c = t->Index(&key);
                IRef* old = c->mpImage.p;
                if (img != old) {
                    if (img) img->AddRef();
                    c->mpImage.p = img;
                    if (old) old->Release();
                }
                c->mX = e->x;
                c->mY = e->y;
                e->img->Release();
            }
            ++e;
        } while (--n);
    }
    return true;
}
}  // namespace Cur
