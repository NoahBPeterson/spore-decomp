// Slice s00830c00 -- cSPUIStdDrawable per-index image-info accessors and color setters.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------- masked externs
extern char g_vtblEditorResource;
extern char g_vtblContentValidation;

extern "C" int  __cdecl FUN_00920090(int, void *, int, int);   // 0x920090
extern "C" void __cdecl MultiHeap_delete(void *);              // 0x951330

struct FactoryRegistry {
    void *vptr;
    int  *CreateInstance(int **out, int a1, int a2, int a3);   // 0x008304c0
};

struct ShadowDesc { char pad[0x28]; };
void FillDefaults(ShadowDesc *dst, const ShadowDesc *src);   // 0x00830380

// ---------------------------------------------------------------- cSPUIStdDrawable
struct Drawable {
    void    *vptr0;      // +0x00
    void    *vptr4;      // +0x04
    void    *f8;         // +0x08
    void    *vptrC;      // +0x0c
    void    *f10;        // +0x10
    char     pad14[0x7c - 0x14];
    char     mInfo[0x98];    // +0x7c mDefaultImageInfo
    void    *mImageInfos[8]; // +0x114
    uint8_t  mbHasUserDefaults;  // +0x134

    __declspec(noinline) void *GetImageInfo(int index);   // 0x00830c00
    void  SetImageColor(int index, int color);        // 0x00831170
    void  SetField18At(int index, int v);             // 0x008311f0
    void  SetField20At(int index, int v);             // 0x00831270
    void  SetPair38At(int index, float *v);           // 0x008312f0
    void  SetPair40At(int index, float *v);           // 0x00831380
    void *PickImageInfo(int flags, void *dst);        // 0x00831410
    bool  GetNaturalSize(float *out, int index);      // 0x00831530
    bool  HitTest(int a, int b);                      // 0x008315c0
    void  EnsureImageInfo0();                         // 0x00831650
    void  SetImageIcon(int index, void *img);         // 0x00831760
};

// ---------------------------------------------------------------- cSPUIStdDrawableImageInfo (scalar dtor)
struct ImageInfo2 {
    void    *vptr0;   // +0x00
    void    *vptr4;   // +0x04
    uint32_t r8;      // +0x08
    void    *mpImage; // +0x0c
    void    *mpIcon;  // +0x10
    char     pad14[0x84];
    void *ScalarDtor(unsigned flags); // 0x00831030
    void  CopyFrom(const ImageInfo2 *src); // 0x008310a0
};

// ---------------------------------------------------------------- 0x00830c00
void *Drawable::GetImageInfo(int index)
{
    void *def = mInfo;
    if ((unsigned)index >= 8)
        return def;
    if (mImageInfos[index] == 0) {
        void *old = mImageInfos[index];
        if (def != old) {
            if (def)
                ((void (__thiscall *)(void *))(*(void ***)def)[0])(def);
            mImageInfos[index] = def;
            if (old)
                ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    return mImageInfos[index];
}

// wrappers live on the interface subobject at +0xc
struct DSub {
    char pad[0xc];
    int  GetFieldC(int index);    // 0x00830c60
    int  GetField14(int index);   // 0x00830c80
    void GetPair28(float *out, int index);  // 0x00830c90
    void GetPair30(float *out, int index);  // 0x00830cc0
    int  GetField10(int index);   // 0x00830cf0
    int  GetField18(int index);   // 0x00830d10
    int  GetField20(int index);   // 0x00830d20
    void GetPair38(float *out, int index);  // 0x00830d30
    void GetPair40(float *out, int index);  // 0x00830d60
    void SetImage(int index, void *img);    // 0x008316b0
};

int DSub::GetFieldC(int index)
{
    return *(int *)((char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index) + 0xc);
}

int DSub::GetField14(int index)
{
    return *(int *)((char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index) + 0x14);
}

void DSub::GetPair28(float *out, int index)
{
    char *p = (char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x28);
    out[1] = *(float *)(p + 0x2c);
}

void DSub::GetPair30(float *out, int index)
{
    char *p = (char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x30);
    out[1] = *(float *)(p + 0x34);
}

int DSub::GetField10(int index)
{
    return *(int *)((char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index) + 0x10);
}

int DSub::GetField18(int index)
{
    return *(int *)((char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index) + 0x18);
}

int DSub::GetField20(int index)
{
    return *(int *)((char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index) + 0x20);
}

void DSub::GetPair38(float *out, int index)
{
    char *p = (char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x38);
    out[1] = *(float *)(p + 0x3c);
}

void DSub::GetPair40(float *out, int index)
{
    char *p = (char *)((Drawable *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x40);
    out[1] = *(float *)(p + 0x44);
}

// ---------------------------------------------------------------- 0x00831030
void *ImageInfo2::ScalarDtor(unsigned flags)
{
    if (mpIcon) {
        ((void (__thiscall *)(void *))(*(void ***)mpIcon)[1])(mpIcon);
    }
    if (mpImage) {
        ((void (__thiscall *)(void *))(*(void ***)mpImage)[1])(mpImage);
    }
    vptr4 = &g_vtblContentValidation;
    vptr0 = &g_vtblEditorResource;
    if (flags & 1)
        MultiHeap_delete(this);
    return this;
}

// ---------------------------------------------------------------- 0x008310a0
void ImageInfo2::CopyFrom(const ImageInfo2 *src)
{
    if (src->mpImage != mpImage) {
        if (src->mpImage)
            ((void (__thiscall *)(void *))(*(void ***)src->mpImage)[0])(src->mpImage);
        void *old = mpImage;
        mpImage = src->mpImage;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    if (src->mpIcon != mpIcon) {
        if (src->mpIcon)
            ((void (__thiscall *)(void *))(*(void ***)src->mpIcon)[0])(src->mpIcon);
        void *old = mpIcon;
        mpIcon = src->mpIcon;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    for (int i = 0; i < 13; ++i)
        ((uint32_t *)((char *)this + 0x14))[i] = ((const uint32_t *)((const char *)src + 0x14))[i];
    for (int b = 0; b < 2; ++b)
        for (int i = 0; i < 10; ++i)
            ((uint32_t *)((char *)this + 0x48 + b * 0x28))[i] =
                ((const uint32_t *)((const char *)src + 0x48 + b * 0x28))[i];
}

// ---------------------------------------------------------------- color/point setters
static void *MakeInfoAt(Drawable *self, unsigned index, void *slot)
{
    void *fr = (void *)FUN_00920090(0x540037e, slot, 0, 0);
    int *p = ((FactoryRegistry *)fr)->CreateInstance((int **)slot, 0x540037e, (int)slot, 0);
    ((ImageInfo2 *)p)->CopyFrom((const ImageInfo2 *)((char *)self + 0x7c));
    return p;
}

// @ 0x00831170
void Drawable::SetImageColor(int index, int color)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(uint32_t *)(info + 0x14) = (uint32_t)color;
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x008311f0
void Drawable::SetField18At(int index, int v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(uint32_t *)(info + 0x18) = (uint32_t)v;
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x00831270
void Drawable::SetField20At(int index, int v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(uint32_t *)(info + 0x20) = (uint32_t)v;
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x008312f0
void Drawable::SetPair38At(int index, float *v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(float *)(info + 0x38) = v[0];
    *(float *)(info + 0x3c) = v[1];
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x00831380
void Drawable::SetPair40At(int index, float *v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(float *)(info + 0x40) = v[0];
    *(float *)(info + 0x44) = v[1];
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// ---------------------------------------------------------------- 0x00831410
void *Drawable::PickImageInfo(int flags, void *dst)
{
    void *info = (char *)this + 0x7c;
    unsigned sel = (unsigned)flags & 7;
    if (sel <= 3) {
        static const int tbl[4] = { 0, 1, 2, 3 };
        int idx = tbl[sel];
        if (flags & 8)
            idx += 4;
        info = GetImageInfo(idx);
    }
    if (dst) {
        ((ImageInfo2 *)dst)->CopyFrom((ImageInfo2 *)info);
        void *a = *(void **)((char *)this + 0x88);
        if (*(void **)((char *)dst + 0xc) == 0) {
            void *old = *(void **)((char *)dst + 0xc);
            if (a != old) {
                if (a)
                    ((void (__thiscall *)(void *))(*(void ***)a)[0])(a);
                *(void **)((char *)dst + 0xc) = a;
                if (old)
                    ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
            }
        }
        void *b = *(void **)((char *)this + 0x8c);
        if (*(void **)((char *)dst + 0x10) == 0) {
            void *old = *(void **)((char *)dst + 0x10);
            if (b != old) {
                if (b)
                    ((void (__thiscall *)(void *))(*(void ***)b)[0])(b);
                *(void **)((char *)dst + 0x10) = b;
                if (old)
                    ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
            }
        }
        FillDefaults((ShadowDesc *)((char *)dst + 0x48), (const ShadowDesc *)((char *)this + 0xc4));
        FillDefaults((ShadowDesc *)((char *)dst + 0x70), (const ShadowDesc *)((char *)this + 0xec));
    }
    return info;
}

// ---------------------------------------------------------------- 0x00831650
void Drawable::EnsureImageInfo0()
{
    if (mbHasUserDefaults != 0)
        return;
    void *def = (char *)this + 0x7c;
    if (mImageInfos[0] == 0) {
        void *old = mImageInfos[0];
        if (def != old) {
            if (def)
                ((void (__thiscall *)(void *))(*(void ***)def)[0])(def);
            mImageInfos[0] = def;
            if (old)
                ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    ((ImageInfo2 *)mImageInfos[0])->CopyFrom((ImageInfo2 *)def);
}

// ---------------------------------------------------------------- 0x008316b0
void DSub::SetImage(int index, void *img)
{
    Drawable *self = (Drawable *)((char *)this - 0xc);
    char *info = (char *)self->GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)self + 0x7c) {
        void *slot = (char *)self + 0x114 + index * 4;
        info = (char *)MakeInfoAt(self, index, slot);
    }
    void *old = *(void **)(info + 0xc);
    if (img != old) {
        if (img)
            ((void (__thiscall *)(void *))(*(void ***)img)[0])(img);
        *(void **)(info + 0xc) = img;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    uint8_t v;
    if (self->mbHasUserDefaults == 0 && index != 8)
        v = 0;
    else
        v = 1;
    self->mbHasUserDefaults = v;
    self->EnsureImageInfo0();
}

// ---------------------------------------------------------------- 0x00831760
void Drawable::SetImageIcon(int index, void *img)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    void *old = *(void **)(info + 0x10);
    if (img != old) {
        if (img)
            ((void (__thiscall *)(void *))(*(void ***)img)[0])(img);
        *(void **)(info + 0x10) = img;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    uint8_t v;
    if (mbHasUserDefaults == 0 && index != 8)
        v = 0;
    else
        v = 1;
    mbHasUserDefaults = v;
    EnsureImageInfo0();
}

// ---------------------------------------------------------------- 0x00830d90
// draw_with_image_info: full draw dispatch is a large switch over the image mode.
// Translation not completed.
void FUN_00830d90(void * /*this*/, void * /*a*/, void * /*b*/, void * /*c*/, int /*mode*/)
{
}

// ---------------------------------------------------------------- 0x00831530 / 0x008315c0
float *FUN_00831530(void * /*this*/, float *out, int /*index*/)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    return out;
}

bool FUN_008315c0(void * /*this*/, int /*a*/, int /*b*/)
{
    return false;
}

