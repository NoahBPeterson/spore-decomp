// Slice s0097cea0: EA::UTFWinControls WinGrid + ImageCursorProvider tail (MSVC 2008 SP1, /O2).
// PDB names used where known:
//   WinGrid::SetCellWindow / Refresh, ImageDrawable::{GetNaturalSize,CreateRenderables,scalar deleting dtor},
//   CustomWinProc::Release, ImageCursorProvider::*, eastl hashtable helpers, CursorListMarshaller::Read.
#include "types.h"

extern "C" void* ea_new(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
extern "C" void  ea_delete(void*);
extern "C" void  FUN_00951330(void*);              // MultiHeapObject::operator_delete
extern "C" void* UTFWin_GetManager();
extern "C" void* Hashtable_find(void* out, const void* key, void* table);
extern "C" void  Hashtable_DoRehash();
extern "C" void  Hashtable_DoFreeNodes();

extern char g_vtblImageDrawable;
extern char g_vtblImageDrawable2;
extern char g_vtblImageDrawable3;
extern char g_vtblEditorResource;

// ---------------------------------------------------------------------------------------------
// @ 0x0097DA40  EA::UTFWin::CustomWinProc::Release
// ---------------------------------------------------------------------------------------------
struct CustomWinProc2 {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    int field4;         // +4
    int mRefCount;      // +8

    int Release();
};

int CustomWinProc2::Release() {
    int n = (*(volatile int*)&mRefCount += -1);
    if (n == 0) slot2(1);
    return n;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097DA60  EA::UTFWinControls::ImageCursorProvider::AsInterface
// ---------------------------------------------------------------------------------------------
struct ImageCursorProvider {
    virtual void slot0();
    virtual void slot1();   // added to make the vtable live
    char pad[0x0c];
    void* AsInterface(unsigned int id);
};

void* ImageCursorProvider::AsInterface(unsigned int id) {
    if (id <= 0xee3f516e) {
        if (id == 0xee3f516e) return this;
        if (id == 0x2ce4360) return this;
        if (id == 0x2cf3268) return this;
    } else if (id == 0xeec58382 && this != 0) {
        return (char*)this + 4;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D950  EA::UTFWinControls::ImageDrawable::`scalar deleting destructor'
// ---------------------------------------------------------------------------------------------
struct ImageDrawable {
    void* vtbl0;        // +0
    void* vtbl1;        // +4
    char  pad[0x1c];
    void* mpImage;      // +0x24
    ImageDrawable* DestroyScalar(unsigned char flags);
};

ImageDrawable* ImageDrawable::DestroyScalar(unsigned char flags) {
    void* img = mpImage;
    vtbl0 = &g_vtblImageDrawable;
    vtbl1 = &g_vtblImageDrawable2;
    ((void**)((char*)this + 0xc))[0] = &g_vtblImageDrawable3;
    if (img) {
        ((void(__thiscall*)(void*))((void**)*(void**)img)[1])(img);
    }
    *(void**)((char*)this + 0xc) = &g_vtblEditorResource;
    vtbl1 = &g_vtblEditorResource;
    vtbl0 = &g_vtblEditorResource;
    if (flags & 1) FUN_00951330(this);
    return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D080  EA::UTFWinControls::WinGrid::Refresh  (adjustor thunk into FUN_0097bc80)
// ---------------------------------------------------------------------------------------------
struct WinGridBase { void RefreshImpl(); };   // 0x97bc80, thiscall
struct WinGridRefreshThunk { void Refresh(); };
void WinGridRefreshThunk::Refresh() { ((WinGridBase*)((char*)this - 0x20c))->RefreshImpl(); }

// ---------------------------------------------------------------------------------------------
// @ 0x0097D100  intrusive pointer field setter
// ---------------------------------------------------------------------------------------------
struct IntrusiveHolder { void SetIntrusive18(void* p); };
void IntrusiveHolder::SetIntrusive18(void* p) {
    void* self = this;
    if (*(void**)((char*)self + 0x18) != p) {
        if (p) ((void(__thiscall*)(void*))((void**)*(void**)p)[0])(p);
        void* old = *(void**)((char*)self + 0x18);
        if (old) ((void(__thiscall*)(void*))((void**)*(void**)old)[1])(old);
        *(void**)((char*)self + 0x18) = p;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D170  EA::UTFWinControls::ImageDrawable::GetNaturalSize
// ---------------------------------------------------------------------------------------------
struct NaturalSizeImage { char pad[0x1c]; int mWidth; int mHeight; };   // image w/h at +0x1c/+0x20
struct NaturalSizeHolder {
    char pad[0x24];
    NaturalSizeImage* mpImage;      // +0x24
    bool GetNaturalSize(int* outW, int* outH, int unused);
};
bool NaturalSizeHolder::GetNaturalSize(int* outW, int* outH, int unused) {
    (void)unused;
    (void)outH;
    if (mpImage != 0) {
        ((float*)outW)[0] = (float)mpImage->mWidth;
        ((float*)outW)[1] = (float)mpImage->mHeight;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D1A0  ImageDrawable shadow-mode refresh (free helper over the +0x28 descriptor)
// ---------------------------------------------------------------------------------------------
void FUN_00c2e4e0(void);            // 0x00c2e4e0  empty retail stub (ILayoutElement::SetSerializer)
void FUN_00830280(void);            // 0x00830280  cDropShadowDescriptor::SetSize
void FUN_00830150(void);            // 0x00830150  cDropShadowDescriptor::SetStrength
typedef void (__thiscall* EmptyThunkFn)(void* self);
typedef int  (__thiscall* ShadowSetSizeFn)(void* self, unsigned value);
typedef int  (__thiscall* ShadowSetStrengthFn)(void* self, unsigned value);

struct ShadowDescriptor {
    unsigned mSize;         // +0x00
    unsigned mStrength;     // +0x04
    char pad[0x20];         // +0x08 .. +0x27
};
struct ImageDrawableShadow {
    ImageDrawable base;             // 0x28 bytes up to mpImage
    ShadowDescriptor mDropShadow;   // +0x28
};

int ImageDrawable_GetWidth(void* self) {
    ImageDrawableShadow* d = (ImageDrawableShadow*)self;
    ((EmptyThunkFn)FUN_00c2e4e0)(self);
    ((ShadowSetSizeFn)FUN_00830280)(&d->mDropShadow, d->mDropShadow.mSize);
    return ((ShadowSetStrengthFn)FUN_00830150)(&d->mDropShadow, d->mDropShadow.mStrength);
}


// ---------------------------------------------------------------------------------------------
// @ 0x0097D270  EA::UTFWinControls::ImageDrawable::CreateRenderables  (draws the image + drop shadow)
// ---------------------------------------------------------------------------------------------
#include <math.h>

namespace Cr {
struct Image { char pad[0x1c]; int mW; int mH; };

struct Target2D {                       // object returned by RenderContext::Begin2D
    virtual void slot0();
    virtual void SetColor(unsigned int argb);
};

struct RenderContext {
    Target2D* Begin2D(int);             // 0x95bc10, thiscall ret 4
};

struct cDropShadowDescriptor {          // 0x28 bytes
    unsigned int mSize, mStrength, mQuality;
    float mOffsetX, mOffsetY, mSizeX, mSizeY, mSmoothness, mSaturation;
    unsigned int mColor;
    cDropShadowDescriptor() {
        mSize = 0; mStrength = 2; mQuality = 3;
        mSizeX = 0.0f; mSizeY = 0.0f; mOffsetX = 0.0f; mOffsetY = 0.0f;
        mColor = 0;
        SetMode(2);
    }
    void SetMode(int mode);             // 0x830150, thiscall ret 4 (sets +4, +0x1c, +0x20)
    static void CopyWithQualityAdjustment(cDropShadowDescriptor* dst, const cDropShadowDescriptor* src, int q); // 0x96e3a0 cdecl
};
}

extern "C" void DrawImageTiled(Cr::Target2D*, const float* rect, Cr::Image*, float sx, float sy, float ox, float oy); // 0x95c420 cdecl
extern "C" void DrawImage9Slice(Cr::Target2D*, const float* dst, const float* uv, Cr::Image*, const float* inner, float sx, float sy); // 0x95ca40 cdecl
extern "C" void DrawImageStretch(Cr::Target2D*, const float* dst, Cr::Image*, const float* src); // 0x95c0d0 cdecl

namespace Cr {
struct ImageDrawable {
    char pad0[0x10];
    float mfScale;                      // +0x10
    unsigned int mnFlags;               // +0x14
    unsigned int mnTiling;              // +0x18
    unsigned int mnAlignmentH;          // +0x1c
    unsigned int mnAlignmentV;          // +0x20
    Cr::Image* mpImage;                 // +0x24
    Cr::cDropShadowDescriptor mDropShadow; // +0x28
    void CreateRenderables(Cr::RenderContext* ctx, const float* rc, int unused);
};
}

static __forceinline void DrawTiling(Cr::ImageDrawable* d, Cr::Target2D* t, const float* dst, const float* expanded) {
    if (d->mnTiling == 2) {
        float inner[4]; float uv[4];
        inner[0] = 1.0f / 3.0f; inner[1] = 1.0f / 3.0f; inner[2] = 2.0f / 3.0f; inner[3] = 2.0f / 3.0f;
        uv[0] = 0.0f; uv[1] = 0.0f; uv[2] = 1.0f; uv[3] = 1.0f;
        DrawImage9Slice(t, dst, uv, d->mpImage, inner, d->mfScale, d->mfScale);
    } else if (d->mnTiling == 1) {
        DrawImageTiled(t, dst, d->mpImage, d->mfScale, d->mfScale, 0.0f, 0.0f);
    } else {
        DrawImageStretch(t, dst, d->mpImage, expanded);
    }
}

void Cr::ImageDrawable::CreateRenderables(Cr::RenderContext* ctx, const float* rc, int unused) {
    if (!mpImage) return;
    Cr::Target2D* t = ctx->Begin2D(0);
    t->SetColor(0xffffffff);
    float r[4];
    r[0] = rc[0]; r[1] = rc[1]; r[2] = rc[2]; r[3] = rc[3];
    if (mnFlags & 1) {
        float w = (float)mpImage->mW * mfScale;
        switch (mnAlignmentH) {
        case 1: break;
        case 2: r[0] = r[2] - w; break;
        case 3: r[0] = ((r[2] - r[0]) - w) * 0.5f + r[0]; break;
        }
        r[2] = r[0] + w;
    }
    if (mnFlags & 2) {
        float h = (float)mpImage->mH * mfScale;
        switch (mnAlignmentV) {
        case 1: break;
        case 2: r[1] = r[3] - h; break;
        case 3: r[1] = ((r[3] - rc[1]) - h) * 0.5f + rc[1]; break;
        }
        r[3] = r[1] + h;
    }
    Cr::cDropShadowDescriptor sh;
    Cr::cDropShadowDescriptor::CopyWithQualityAdjustment(&sh, &mDropShadow, 0);
    float sx = sh.mSizeX, sy = sh.mSizeY;
    float loY = -sy, loX = -sx;
    float cy = (loY + sy) * 0.5f;
    float cx = (loX + sx) * 0.5f;
    float norm = ((sy - cy) * (sy - cy) + (sx - cx) * (sx - cx)) + 1.0f;
    unsigned int rgb = sh.mColor & 0xffffff;
    float R = sqrt(sy * sy + sx * sx) + 1.0f;
    float ex[4];
    ex[0] = (rc[0] - R) - sh.mOffsetX;
    ex[1] = (rc[1] - R) - sh.mOffsetY;
    ex[2] = (rc[2] + R) + sh.mOffsetX;
    ex[3] = (rc[3] + R) + sh.mOffsetY;
    for (float i = loX; sx >= i; i += 1.0f) {
        if (sy >= loY) {
            float dx = floor(i + sh.mOffsetX);
            for (float j = loY; sy >= j; j += 1.0f) {
                float dy = floor(j + sh.mOffsetY);
                if (dx != 0.0f || dy != 0.0f) {
                    float d[4];
                    d[0] = rc[0] + dx; d[1] = rc[1] + dy; d[2] = rc[2] + dx; d[3] = rc[3] + dy;
                    float a = (sh.mSaturation / R) * (1.0f - ((i - cx) * (i - cx) + (j - cy) * (j - cy)) / norm) + sh.mSmoothness;
                    if (0.0f > a) a = 0.0f;
                    else if (a > 1.0f) a = 1.0f;
                    unsigned int ai = (unsigned int)(a * 255.0f + 0.5f);
                    t->SetColor((ai << 24) + rgb);
                    DrawTiling(this, t, d, ex);
                }
            }
        }
    }
    t->SetColor(0xffffffff);
    DrawTiling(this, t, r, ex);
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D8D0  EA::UTFWinControls::ImageDrawable::ImageDrawable  (constructor, returns this)
// ---------------------------------------------------------------------------------------------
extern char g_vtblResourceAsync;       // 0x013fa72c
extern char g_vtblAddRef;              // 0x01443050
extern char g_vtblImageDrawableC;      // 0x014430f8
extern char g_vtblImageDrawableC4;     // 0x014430e0
extern char g_vtblImageDrawableC12;    // 0x01443098

namespace Cr {
struct P0  { virtual void p0(); };
struct P4  { virtual void p4(); int mRefCount; P4() : mRefCount(0) {} };   // +4, +8
struct P12 { virtual void p12(); };                                         // +0xc
struct CustomDrawableX : P0, P4, P12 {
    float mfScale;                     // +0x10
    CustomDrawableX() : mfScale(1.0f) {}
};
struct ImageDrawableCtor : CustomDrawableX {
    unsigned int mnFlags;              // +0x14
    unsigned int mnTiling;             // +0x18
    unsigned int mnAlignmentH;         // +0x1c
    unsigned int mnAlignmentV;         // +0x20
    void*        mpImage;              // +0x24
    cDropShadowDescriptor mDropShadow; // +0x28
    ImageDrawableCtor();
};
ImageDrawableCtor::ImageDrawableCtor()
    : mnFlags(0), mnTiling(0), mnAlignmentH(3), mnAlignmentV(3), mpImage(0) {}
}

// ---------------------------------------------------------------------------------------------
// 0x0097CEA0  EA::UTFWinControls::WinGrid::SetCellWindow  (465 bytes); marker on the definition below
//   `this` is the IWinGrid subobject at WinGrid+0x20c; ret 0x18
// ---------------------------------------------------------------------------------------------
namespace Gr {

#define GVT(o, i) ((*(void***)(o))[i])

struct CellData {                        // 0x1c bytes, allocated "UTFWin/Grid"
    int mType;                           // +0
    int mCol, mRow;                      // +4, +8
    void* mpWindow;                      // +0xc
    int pad10, pad14;
    unsigned mFlags;                     // +0x18
};

struct SparseMatrix {                    // SparseMatrix<CellData*> at IWinGrid+0x114
    int  GetMaxUsedColAndRow(int* pOut);                              // 0x973980, ret 4
    bool GetMinMaxUsedColForRow(int row, int* pMin, int* pMax);      // 0x975350, ret 0xc
    bool GetMinMaxUsedRowForCol(int col, int* pMin, int* pMax);      // 0x973800, ret 0xc
    void InsertCell(int col, int row, CellData** ppCell, int flag);  // 0x976f90, ret 0x10
};

struct WinGridMain {                     // the full WinGrid object (IWinGrid subobject - 0x20c)
    void SetupCell(int col, int row, int one, int flag);             // 0x97bfb0, ret 0x10
    void InitCellWindow(int col, int row, void* w, bool b1, bool b2); // 0x975ea0, ret 0x14
};

struct WinGridIface {                    // IWinGrid subobject
    void* vtbl;                          // +0
    char  pad4[4];
    bool  mbDirty;                       // +8
    char  pad9[0x7c - 9];
    int   mLastCol;                      // +0x7c
    int   mLastRow;                      // +0x80
    char  pad84[0x114 - 0x84];
    SparseMatrix mCells;                 // +0x114
    bool SetCellWindow(int col, int row, void* w, bool b1, bool b2, int flag);
};

// @ 0x0097cea0
bool WinGridIface::SetCellWindow(int colIn, int rowIn, void* w, bool b1, bool b2, int flag) {
    if (flag == 0) flag = 1;
    if (((bool(__thiscall*)(void*, void*, int, int, int))GVT(this, 0x1b8 / 4))(this, w, 0, 0, 0))
        return false;
    int col = colIn, row = rowIn;
    {
    int mn, mx;
    if (col == 0x7fffffff) {
        bool skipToRow = false;
        if (row == 0x7fffffff) {
            col = mCells.GetMaxUsedColAndRow(&mx);
            if (col == (int)0x80000000) { col = 0; skipToRow = true; }
            else if (col != 0x7fffffff) skipToRow = true;
        }
        if (!skipToRow) {
            if (!mCells.GetMinMaxUsedColForRow(row, &mn, &mx)) col = 0;
            else col = mx + 1;
        }
    }
    if (row == 0x7fffffff) {
        if (!mCells.GetMinMaxUsedRowForCol(col, &mn, &mx)) row = 0;
        else row = mx + 1;
    }
    }
    if (!((bool(__thiscall*)(void*, int, int))GVT(this, 0xd4 / 4))(this, col, row)) {
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);
        return false;
    }
    if (w == 0) {
        ((void(__thiscall*)(void*, int, int))GVT(this, 0x164 / 4))(this, col, row);
        mLastRow = row;
        mLastCol = col;
        return true;
    }
    CellData* cell = 0;
    CellData* n = (CellData*)ea_new(0x1c, "UTFWin/Grid", 0, 0, 0, 0);
    if (n) {
        n->pad10 = 0;
        n->pad14 = 0;
        n->mFlags = 0;
        n->mType = 1;
        n->mCol = col;
        n->mRow = row;
        n->mpWindow = w;
        cell = n;
        if (b1) n->mFlags |= 1;
        if (b2) n->mFlags |= 2;
        WinGridMain* wg = (WinGridMain*)((char*)this - 0x20c);
        wg->SetupCell(col, row, 1, flag);
        mCells.InsertCell(col, row, &cell, 0);
        wg->InitCellWindow(col, row, w, b1, b2);
    }
    mbDirty = true;
    void* sub = (char*)this - 0x208;
    ((void(__thiscall*)(void*, int, int))GVT(sub, 0x7c / 4))(sub, 8, 1);
    mLastRow = row;
    mLastCol = col;
    return true;
}

}  // namespace Gr

// ---------------------------------------------------------------------------------------------
// ImageCursorProvider tail: CursorWindow, eastl::fixed_hash_map<unsigned, ImageCursor> helpers
// ---------------------------------------------------------------------------------------------
#include <new>
namespace Cur {

#define VT(o, i) ((*(void***)(o))[i])
#define VCALL0(R, o, i)    (((R(__thiscall*)(void*))VT(o, i))(o))
#define VCALL1(R, o, i, A, a) (((R(__thiscall*)(void*, A))VT(o, i))(o, a))

struct IRef {                            // AutoRefCount target: slot 0 AddRef, slot 1 Release
    virtual int AddRef() throw();
    virtual int Release() throw();
};

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

struct PlaceTag {};

struct ImageCursor {                     // 0xc bytes
    int mX, mY;                          // mPickPoint, deliberately left uninitialised
    ImgRef mpImage;                      // +8
    ImageCursor() throw() {}
    ImageCursor(const ImageCursor& o) throw() : mX(o.mX), mY(o.mY), mpImage(o.mpImage) {}
};

struct CursorPair {                      // eastl::pair<unsigned const, ImageCursor>, 0x10 bytes
    unsigned first;
    ImageCursor second;
    CursorPair(unsigned k, const ImageCursor& v) throw() : first(k), second(v) {}
    CursorPair(const CursorPair& o) throw() : first(o.first), second(o.second) {}
    static void* operator new(unsigned, void* p, PlaceTag) throw() { return p; }
    static void operator delete(void*, void*, PlaceTag) throw() {}
};


struct HNode {                           // eastl hash_node, 0x14 bytes
    CursorPair mValue;                   // +0
    HNode* mpNext;                       // +0x10
};

struct HIter { HNode* mpNode; HNode** mpBucket; };

struct TrueTag { char pad; TrueTag() : pad(0) {} };

void*  ea_alloc(unsigned, const char*, int, int, const char*, int);   // 0x00f473a0
void   ea_free(void*);                                                // 0x00f47380

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

struct Sub4 {                            // second interface at CursorWindow+4
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual int  Slot5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void Slot36();
    virtual void v37();
    virtual void Slot38();
};

struct Target2D {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void DrawImage(float x, float y, IRef* img);          // slot 24
};

struct RenderContext {
    Target2D* Begin2D(int);              // 0x95bc10, thiscall ret 4
    void End2D();                        // 0x95bb20, thiscall
};

struct Vec3Sink { void Apply(const float* v3); };                 // 0x95e890, thiscall ret 4

struct CursorWindow {
    Sub4 mIface;                         // +0 (vptr slot of the primary base is the first word; see pad)
};

struct Pt { int x, y; };

struct PrimaryBase { virtual void p0(); };

struct CursorWindowObj : PrimaryBase, Sub4 {   // Sub4 is the interface at +4
    char    pad[0x204];                  // +8 .. +0x20c
    ImageCursor* mpCursor;               // +0x20c
    Pt      mMouse;                      // +0x210, +0x214
    bool    OnRebuild(RenderContext* ctx);                // 0x97db30, ret 4
    void    PushMouse(Vec3Sink* sink);                    // 0x97db90, ret 4
};

struct Mgr1 {};

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

struct Manager {
    void* vt;
};
Manager* GetManager();                   // 0x957f30

struct ReadEntry { unsigned key; int x, y; IRef* img; };
struct ReadList  { int pad0; ReadEntry* mpBegin; unsigned mnCount; };
struct ReadOwner { int pad0; Provider* mpProvider; };
bool CursorListMarshaller_Read(ReadOwner* self, ReadList* list);   // 0x97e140, cdecl

// @ 0x0097DB30  ImageCursorProvider::CursorWindow::OnRebuild
bool CursorWindowObj::OnRebuild(RenderContext* ctx) {
    if (mpCursor) {
        Target2D* t = ctx->Begin2D(0);
        ImageCursor* c = mpCursor;
        t->DrawImage((float)-c->mX, (float)-c->mY, c->mpImage.p);
        ctx->End2D();
    }
    return true;
}

// @ 0x0097DB90  ImageCursorProvider helper (CursorWindow::PushMouse)
void CursorWindowObj::PushMouse(Vec3Sink* sink) {
    float v[3];
    v[0] = (float)mMouse.x;
    v[1] = (float)mMouse.y;
    v[2] = 0.0f;
    sink->Apply(v);
}

// @ 0x0097DC00  ImageCursorProvider::UpdateMousePosition
void Provider::UpdateMousePosition(const int* pt) {
    CursorWindowObj* w = mpCursorWindow;
    w->mMouse.x = pt[0];
    w->mMouse.y = pt[1];
    static_cast<Sub4*>(w)->Slot38();
}

// @ 0x0097DD80  eastl hashtable node alloc+copy
HNode* Table::AllocNodeCopy(const CursorPair* src) {
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

// @ 0x0097DDF0  ImageCursorProvider::HasCursor
bool Provider::HasCursor(unsigned key) {
    Table* t = &mCursorMap;
    HNode* end = t->End();
    HIter it;
    return t->Find(&it, &key)->mpNode != end;
}

// @ 0x0097DE20  ImageCursorProvider::SetCursor
bool Provider::SetCursor(unsigned key) {
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

// @ 0x0097DC30  eastl hashtable::DoRehash
void Table::DoRehash(unsigned n) {
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

// @ 0x0097E030  eastl hashtable::DoFreeNodes
void Table::DoFreeNodes(HNode** buckets, unsigned n) {
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

// @ 0x0097E0B0  eastl hash_map::operator[]
ImageCursor* Table::Index(const unsigned* key) {
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

// @ 0x0097E140  CursorListMarshaller::Read
bool CursorListMarshaller_Read(ReadOwner* self, ReadList* list) {
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

// ---------------------------------------------------------------------------------------------
// @ 0x0097DAD0
//   EA::UTFWinControls::ImageCursorProvider::CursorWindow::CursorWindow (constructor):
//   Window base ctor (0x962a10), the two derived vptrs, three zeroed fields (mpCursor/mMouseX/
//   mMouseY at +0x20c/+0x210/+0x214), then SetFlag(0x40/0x10/0x200, 1) on the Win subobject (+4).
// ---------------------------------------------------------------------------------------------
namespace Cur {
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
}  // namespace Cur
