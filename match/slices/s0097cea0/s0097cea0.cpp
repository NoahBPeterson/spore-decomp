// Slice s0097cea0: EA::UTFWinControls WinGrid + ImageCursorProvider tail (MSVC 2008 SP1, /O2).
// PDB names used where known:
//   WinGrid::SetCellWindow / Refresh, ImageDrawable::{GetNaturalSize,CreateRenderables,scalar deleting dtor},
//   CustomWinProc::Release, ImageCursorProvider::*, eastl hashtable helpers, CursorListMarshaller::Read.
#include "types.h"

extern "C" void* ea_new(unsigned, const char*, int, int, const char*, int);
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
extern "C" void FUN_0097bc80(void*);
void WinGrid_Refresh(void* self) { FUN_0097bc80((char*)self - 0x20c); }

// ---------------------------------------------------------------------------------------------
// @ 0x0097D100  intrusive pointer field setter
// ---------------------------------------------------------------------------------------------
void SetIntrusive18(void* self, void* p) {
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
bool ImageDrawable_GetNaturalSize(void* self, int* outW, int* outH) {
    if (*(void**)((char*)self + 0x24) == 0) return false;
    (void)outW; (void)outH;
    return true;   // approximated
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D1A0 / 0x0097D270 / 0x0097D8D0  ImageDrawable helpers (approximated)
// ---------------------------------------------------------------------------------------------
int  ImageDrawable_GetWidth(void* self) { return self ? *(int*)((char*)self + 0x14) : 0; }
void ImageDrawable_Destroy(void* self) { (void)self; }


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
    cDropShadowDescriptor()
        : mSize(0), mStrength(2), mQuality(3), mOffsetX(0.0f), mOffsetY(0.0f), mSizeX(0.0f), mSizeY(0.0f), mColor(0)
    { SetMode(2); }
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
                    unsigned int ai = (unsigned int)(a * 255.0f);
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
// @ 0x0097CEA0  EA::UTFWinControls::WinGrid::SetCellWindow  (465 bytes)
// ---------------------------------------------------------------------------------------------
extern "C" bool WinGrid_AssignCell(void* self, int row, int col);
bool WinGrid_SetCellWindow(void* self, int row, int col, int window, int flags) {
    (void)flags;
    if (!WinGrid_AssignCell(self, row, col)) {
        return false;
    }
    return true;   // control flow approximated (SparseMatrix cell insert)
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097DAD0  ImageCursorProvider::CursorWindow::CursorWindow  (ctor)
// @ 0x0097DB30  ImageCursorProvider::CursorWindow::OnRebuild
// @ 0x0097DB90  (provider helper)
// @ 0x0097DC00  ImageCursorProvider::UpdateMousePosition
// @ 0x0097DC30  hashtable<...>::DoRehash
// @ 0x0097DD80  (hashtable helper)
// @ 0x0097DDF0  ImageCursorProvider::HasCursor
// @ 0x0097DE20  ImageCursorProvider::SetCursor
// @ 0x0097E030  hashtable<...>::DoFreeNodes
// @ 0x0097E0B0  hash_map<...>::operator[]
// @ 0x0097E140  CursorListMarshaller::Read
// ---------------------------------------------------------------------------------------------
void CursorWindow_ctor(void* self) { (void)self; }
void CursorWindow_OnRebuild(void* self) { (void)self; }
void CursorProvider_helper_db90(void* self) { (void)self; }
void ImageCursorProvider_UpdateMousePosition(void* self) { (void)self; }
void Hashtable_DoRehashStub(void* self) { Hashtable_DoRehash(); }
void Hashtable_helper_dd80(void* self) { (void)self; }

bool ImageCursorProvider_HasCursor(void* self) {
    (void)self;
    return false;   // eastl hashtable<unsigned,...>::find -> approximated
}

bool ImageCursorProvider_SetCursor(void* self, int cursor) {
    (void)self; (void)cursor;
    return false;   // 325-byte manager interaction approximated
}

void Hashtable_DoFreeNodesStub(void* self) { Hashtable_DoFreeNodes(); }

void* Hashmap_operator_index(void* self, unsigned key) {
    (void)self; (void)key;
    return 0;   // find + insert + rehash approximation
}

bool CursorListMarshaller_Read(void* self, void* r) {
    (void)self; (void)r;
    return false;   // stream read approximation
}
