// Slice s00f6a960 -- three-pass full-screen quad draw (constant buffers 0x242/0x201, 0x250, 0x251).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc: the function has no SEH frame)
#include "types.h"
#include <string.h>

struct Vec4 { float x, y, z, w; Vec4() {} Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };

struct Vec3 { float x, y, z; Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };

struct Rect { float x0, y0, x1, y1; };

struct Handle { uint32_t value; uint32_t flags; };   // lazily resolved resource handle (bit0 = resolved)

// singleton at 0x0067dd60: resolves a Handle through vtable slot 13 (+0x34)
struct IResolver { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                   virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                   virtual void v10(); virtual void v11(); virtual void v12();
                   virtual void Resolve(Handle* h); };                                  // +0x34
// singleton at 0x0067dda0: viewport query through vtable slot 9 (+0x24)
struct IViewportInfo { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                       virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
                       virtual void Query(uint32_t a, uint32_t b, int* px, int* py, int* w, int* h); }; // +0x24
IResolver* __cdecl GetResolver();       // 0x0067dd60
IViewportInfo* __cdecl GetViewportInfo(); // 0x0067dda0

struct ShaderIds { char pad[4]; uint32_t id; };      // [ptr+4] is the shader id
struct ShaderTable { char pad34[0x34]; ShaderIds* s34; ShaderIds* s38; ShaderIds* s3c; };
ShaderTable* __cdecl GetShaderTable();    // 0x00f48a60

void __cdecl SetShaderConst(int slot, const void* data, int zero);   // 0x00777ae0

// Constant/texture binding object (ctor at 0x00fc2c10, dtor at 0x00fc2830)
struct Binding {
    uint32_t m0, m4, m8, mc;
    Binding(uint32_t shader, int index, uint32_t value);
    ~Binding();
};

struct DrawData {                 // object returned by Owner-arg vtable slot 4 (+0x10)
    char pad00[0x31c];
    Handle* h31c;
    Handle* h320;
    Handle* h324;
    Handle* h328;
    char pad32c[0x43c - 0x32c];
    Vec4 c43c;
    Vec4 c44c;
    Vec4* Query1(Vec4* tmp);      // 0x00fb9ad0
    Vec4* Query2(Vec4* tmp);      // 0x00fb9ca0
};

struct Source {                   // arg1: vtable +0x10 returns DrawData; indexed handle getters
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual DrawData* GetData();   // +0x10
    uint32_t TexA(int i);         // 0x00f98260
    uint32_t TexB(int i);         // 0x00f98270
    uint32_t TexC(int i);         // 0x00f98280
};

struct Viewer {
    void SetRaster(const void* r, int flag);   // 0x007c4be0
    bool Update();                             // 0x007c4fd0
    void Finish();                             // 0x007c3c10
};

struct IBatch {
    virtual void v0(); virtual void v1();
    virtual bool Alloc(void** out, int stride, int count, int zero);   // +0x08
    virtual bool Apply(uint32_t shader, void* arg);                    // +0x0c
    virtual void Flush();                                              // +0x10
};

struct Compositor {
    char pad00[0x1c];
    Viewer* mViewer;
    char pad20[0x200 - 0x20];
    IBatch* mBatch;
    bool Draw(Source* src, const uint32_t* raster, int a3, Rect r,
              float v0, float v1, float v2, int a11, void* a12);       // 0x00f6a960
};

static inline uint32_t ResolveHandle(Handle* h)
{
    if (!(h->flags & 1))
        GetResolver()->Resolve(h);
    return h->value;
}

// @ 0x00f6a960
bool Compositor::Draw(Source* src, const uint32_t* raster, int a3, Rect r,
                      float v0, float v1, float v2, int a11, void* a12)
{
    DrawData* d = src->GetData();
    if (!d)
        return false;

    Vec4 v;
    v.x = v0;
    v.y = v1;
    v.z = 1.0f / (v2 - v0);
    v.w = 0.0f;
    int vx, vy, vw, vh;
    GetViewportInfo()->Query(raster[0], raster[1], &vx, &vy, &vw, &vh);

    uint32_t shader = GetShaderTable()->s34->id;
    static Vec4 cb0[4];
    cb0[0] = d->c44c;
    cb0[1] = d->c43c;
    cb0[2] = v;
    cb0[2].w = 0.5f / (float)vw;
    cb0[3] = Vec4(0.0f, -1.0f, 1.0f, 1.0f);

    void* out = 0;
    if (!mBatch->Alloc(&out, 0x18, 4, 0))
        return false;
    SetShaderConst(0x242, cb0, 0);
    SetShaderConst(0x201, 0, 0);
    memset(out, 0, 0x60);
    *(Vec3*)out = Vec3(r.x0, 1.0f - r.y1, 1.0f);
    *(Vec3*)((char*)out + 0x18) = Vec3(r.x1, 1.0f - r.y1, 1.0f);
    *(Vec3*)((char*)out + 0x30) = Vec3(r.x0, 1.0f - r.y0, 1.0f);
    *(Vec3*)((char*)out + 0x48) = Vec3(r.x1, 1.0f - r.y0, 1.0f);
    mViewer->SetRaster(raster, 1);
    if (mViewer->Update()) {
        Binding b0(shader, 0, src->TexC(a3));
        Binding b1(shader, 1, ResolveHandle(d->h328));
        if (!mBatch->Apply(shader, a12))
            return false;
        mViewer->Finish();
    }
    SetShaderConst(0x242, 0, 0);

    {
        shader = GetShaderTable()->s38->id;
        static Vec4 cb1;
        {
            Vec4 tmp;
            cb1 = *d->Query1(&tmp);
        }
        SetShaderConst(0x242, cb0, 0);
        SetShaderConst(0x250, &cb1, 0);
        mViewer->SetRaster(raster, 1);
        if (mViewer->Update()) {
            Binding b0(shader, 0, src->TexA(a3));
            Binding b1(shader, 1, ResolveHandle(d->h31c));
            if (!mBatch->Apply(shader, a12))
                return false;
            mViewer->Finish();
        }
        SetShaderConst(0x242, 0, 0);
        SetShaderConst(0x250, 0, 0);
    }

    {
        shader = GetShaderTable()->s3c->id;
        static Vec4 cb2;
        {
            Vec4 tmp;
            cb2 = *d->Query2(&tmp);
        }
        SetShaderConst(0x242, cb0, 0);
        SetShaderConst(0x251, &cb2, 0);
        mViewer->SetRaster(raster, 1);
        if (mViewer->Update()) {
            Binding b0(shader, 0, src->TexB(a3));
            Binding b1(shader, 1, src->TexA(a3));
            Binding b2(shader, 2, ResolveHandle(d->h320));
            if (!mBatch->Apply(shader, a12))
                return false;
            mBatch->Flush();
            mViewer->Finish();
        }
        SetShaderConst(0x242, 0, 0);
        SetShaderConst(0x251, 0, 0);
    }
    return true;
}

// =============================================================================================
// Sibling functions of the Compositor slice (0x00f6b000 family): an image/quad "source"
// descriptor and the container that owns a list of them.
//   0x00f6b000  copy-constructor for ImgDesc  (__thiscall, 1 stack arg, ret 4)
//   0x00f6b0e0  bulk copy of 0x1c4-byte tex descriptors (cdecl, 4 args)
//   0x00f6b2d0  destructor for ImgDesc        (__thiscall, no args)
//   0x00f6b330  assignment for ImgDesc from a raw record (__thiscall, 1 arg, ret 4, returns this)
//   0x00f6b4b0  copy-constructor for TexVector (__thiscall, 1 arg, ret 4, returns this)
//   0x00f6b670  copy-constructor for QuadSource (__thiscall, 1 arg, ret 4, returns this)
//   0x00f6b7c0  destructor for the intrusive list  (__thiscall, no args)
//   0x00f6b840  destructor for QuadSource      (__thiscall, no args)
// =============================================================================================

#include <intrin.h>
#include <new>

// ---- allocator / messaging / resource helpers -----------------------------------------------
extern "C" void* __stdcall GetImageResource(void* handle);          // 0x00576650 (ret 4)
extern "C" void  __cdecl operator_delete(void* p);                  // 0x00f47380
extern "C" void* __cdecl operator_new(int size, const char* file, int line, int a3,
                                      const char* name, int line2);  // 0x00f473a0
extern "C" void  __cdecl EA_MsgRemoveHandler(void* h, void* a, void* b, void* c, void* d);  // 0x00571db0
// viewport manager singleton at 0x0067dda0 (vtable slot 5 = +0x14 releases a slot pair)
struct IViewport {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void ReleaseSlot(uint32_t a, uint32_t b);   // +0x14
};
// small interface whose slot 1 (+0x04) destroys the object (this = mp74)
struct ISlot {
    virtual void v0();
    virtual void Release();                             // +0x04
};
IViewport* __cdecl GetViewportInfo2();                              // 0x0067dda0
extern "C" void  __fastcall FUN_00f674c0(void* self);               // 0x00f674c0 (ecx=this, no args)
extern "C" void  __stdcall FUN_00f672b0(void* p);                   // 0x00f672b0 (ret 4)
extern "C" void  __fastcall cViewer_dtor(void* self);               // 0x007c4000

extern const char kAllocFile[];      // 0x013f09b4  "Simulator"
extern const char kAllocFile2[];     // 0x013ebb38

// The intrusive-refcount release used all over this family: decrement, and if the count
// dropped below 1 put it back (it is a "still referenced" probe on the embedded counter).
static inline void RefRelease(int* p)
{
    volatile long* c = (volatile long*)p;
    _InterlockedDecrement(c);
    if (_InterlockedExchangeAdd(c, 0) < 1)
        _InterlockedIncrement(c);
    else
        _InterlockedExchangeAdd(c, 0);
}

// ---- image/quad descriptor (0x78 bytes) ------------------------------------------------------
struct ImgDesc {
    char* mpRes;                 // +0x00  intrusive resource pointer (counter at +8)
    uint8_t m04;                 // +0x04
    uint8_t m05;                 // +0x05
    uint8_t m06;                 // +0x06
    char  _pad07;
    float m08;                   // +0x08
    uint32_t m0c;                // +0x0c
    float m10;                   // +0x10
    float m14;                   // +0x14
    float m18;                   // +0x18
    float m1c;                   // +0x1c
    float m20;                   // +0x20
    float m24;                   // +0x24
    float m28;                   // +0x28
    float m2c;                   // +0x2c
    float m30;                   // +0x30
    float m34;                   // +0x34
    float m38;                   // +0x38
    uint32_t m3c;                // +0x3c
    float m40;                   // +0x40
    float m44;                   // +0x44
    float m48;                   // +0x48
    float m4c;                   // +0x4c
    float m50;                   // +0x50
    float m54;                   // +0x54
    float m58;                   // +0x58
    float m5c;                   // +0x5c
    float m60;                   // +0x60
    float m64;                   // +0x64
    float m68;                   // +0x68
    uint32_t m6c;                // +0x6c
    uint32_t m70;                // +0x70
    uint32_t m74;                // +0x74

    ImgDesc(const ImgDesc& o);          // 0x00f6b000
    ImgDesc& Assign(const char* rec);    // 0x00f6b330
};

// A raw 0x78-byte record with the same layout (what 0x00f6b330 assigns from).
struct ImgRecord {
    uint32_t mHandle;            // +0x00
    uint8_t  m04, m05, m06;      // +0x04..+0x06
    char     _pad07;
    float    m08;                // +0x08
    uint32_t m0c;                // +0x0c
    float    m10, m14, m18, m1c, m20, m24, m28, m2c, m30, m34;
    float    m38, m3c, m40, m44, m48, m4c, m50, m54, m58, m5c;
    float    m60, m64, m68, m6c, m70, m74;
};

// One 0x1c4-byte texture descriptor: a dword header then two 0xe0-byte float blocks.
struct TexBlock {                // 0xe0 bytes of packed floats
    float v[0xe0 / 4];
    TexBlock() {}
    TexBlock(const TexBlock& o) { for (int i = 0; i < 0xe0 / 4; ++i) v[i] = o.v[i]; }
};
struct TexDesc {                 // 0x1c4 bytes
    uint32_t m00;
    TexBlock b[2];               // +0x04 and +0xe4 (0xe0 each)
    TexDesc() {}
};

// Bulk-copy [first,last) TexDesc records into dst; *out receives the new dst cursor.
TexDesc** CopyTexRange(TexDesc** out, TexDesc* first, TexDesc* last, TexDesc* dst,
                       const void* owner);  // 0x00f6b0e0

// ---- the container ---------------------------------------------------------------------------
struct TexVector {
    TexDesc* mpBegin;
    TexDesc* mpCur;
    TexDesc* mpEnd;
    TexVector(const TexVector& o);      // 0x00f6b4b0
};

struct QuadSource {
    uint32_t _raw000[0x7c / 4];
    uint32_t m7c;                    // +0x7c
    ImgDesc  mDesc80;                // +0x80  (0x78)
    float    mf8;                    // +0xf8
    float    mfc;                    // +0xfc
    float    m100;                   // +0x100
    float    m104;                   // +0x104
    float    m108;                   // +0x108
    uint32_t m10c;                   // +0x10c
    char     mVec110[0x0c * 0x10];   // +0x110  inline array of 0x10 0xc-byte vectors
    uint32_t m1d0;                   // +0x1d0
    TexVector mTex1d4;               // +0x1d4

    QuadSource(const QuadSource& o); // 0x00f6b670
    QuadSource& CopyFrom(const QuadSource& o); // 0x00f6b670
    void Release();                  // 0x00f6b2d0
};

extern "C" void __cdecl VectorCopy(void* dst, const void* src, int elemSize, int count,
                                   void* ctor);   // 0x00406540
extern "C" void __cdecl kVec3Ctor();              // 0x004098a0

struct QuadNode {                   // intrusive list node; the sentinel embeds the same head
    QuadNode* mpNext;               // +0x00
    QuadNode* mpPrev;               // +0x04
    uint32_t  pad08[0x88 / 4 - 2];
    void*     mpRef88;              // +0x88  refcounted pointer (counter at +8)
    uint32_t  pad8c[(0x1dc - 0x8c) / 4];
    void*     mpRes1dc;             // +0x1dc intrusive resource pointer (counter at -4)
    void FreeAll();                 // 0x00f6b7c0  (called on the sentinel)
};

// The object this family of destructors belongs to (0x20c bytes).
struct QuadMgr {
    uint32_t  pad000[0x08 / 4];
    void*     mpHandler08;          // +0x08  EA::Messaging handler
    uint32_t  m0c, m10, m14, m18;   // +0x0c..+0x18
    void*     mpViewer1c;           // +0x1c  viewer (cViewer)
    uint32_t  mSlots20[6];          // +0x20..+0x34  per-slot "in use" flags
    uint32_t  mSlotArgs38[12];      // +0x38..+0x64  6 (arg,arg) pairs
    uint32_t  mSlot68;              // +0x68
    uint32_t  mSlotArgs6c[2];       // +0x6c,+0x70
    void*     mp74;                 // +0x74
    uint32_t  pad78[(0x17c - 0x78) / 4];
    void*     mpRef17c;             // +0x17c refcounted pointer (counter at +8)
    uint32_t  mBlob180[0x24 / 4];   // +0x180 (FUN_00f674c0)
    uint32_t  mBlob1a4[0x24 / 4];   // +0x1a4 (FUN_00f674c0)
    uint32_t  pad1c8[(0x200 - 0x1c8) / 4];
    void*     mp200;                // +0x200
    void*     mp204;                // +0x204
    void*     mp208;                // +0x208
    void Destroy();                 // 0x00f6b840
};

// @ 0x00f6b000
ImgDesc::ImgDesc(const ImgDesc& o)
{
    mpRes = o.mpRes;
    if (mpRes != 0)
        _InterlockedIncrement((volatile long*)(mpRes + 8));
    m04 = o.m04;
    m05 = o.m05;
    m06 = o.m06;
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    m18 = o.m18;
    m1c = o.m1c;
    m20 = o.m20;
    m24 = o.m24;
    m28 = o.m28;
    m2c = o.m2c;
    m30 = o.m30;
    m34 = o.m34;
    m38 = o.m38;
    m3c = o.m3c;
    m40 = o.m40;
    m44 = o.m44;
    m48 = o.m48;
    m4c = o.m4c;
    m50 = o.m50;
    m54 = o.m54;
    m58 = o.m58;
    m5c = o.m5c;
    m60 = o.m60;
    m64 = o.m64;
    m68 = o.m68;
    m6c = o.m6c;
    m70 = o.m70;
    m74 = o.m74;
}

// @ 0x00f6b0e0
TexDesc** CopyTexRange(TexDesc** out, TexDesc* first, TexDesc* last, TexDesc* dst,
                       const void* owner)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0)
                new (dst) TexDesc(*first);
            first = (TexDesc*)((char*)first + sizeof(TexDesc));
            dst   = (TexDesc*)((char*)dst   + sizeof(TexDesc));
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x00f6b2d0
void QuadSource::Release()
{
    TexDesc* tex = mTex1d4.mpBegin;
    if (tex != 0 && *(int*)((char*)tex - 4) != 0)
        operator_delete(tex);
    char* res = mDesc80.mpRes;
    if (res != 0)
        RefRelease((int*)(res + 8));
}

// @ 0x00f6b330
// Assign from a raw record: the destination's field classes are dictated by the caller's
// record layout (raw ints), so this view overlaps ImgDesc with the integer-typed fields.
struct ImgDescRaw {
    uint32_t mHandle;            // +0x00
    uint8_t  m04, m05, m06;      // +0x04..+0x06
    char     _pad07;
    float    m08;                // +0x08
    uint32_t m0c;                // +0x0c
    float    m10, m14, m18, m1c; // +0x10..+0x1c
    uint32_t m20, m24, m28, m2c, m30, m34, m38, m3c;   // +0x20..+0x3c
    uint32_t m40, m44, m48, m4c, m50, m54;             // +0x40..+0x54
    float    m58;                                      // +0x58
    uint32_t m5c, m60, m64;                            // +0x5c..+0x64
    float    m68;                                      // +0x68
    uint32_t m6c, m70, m74;                            // +0x6c..+0x74
};

ImgDesc&
ImgDesc::Assign(const char* rec)
{
    const ImgDescRaw* r = (const ImgDescRaw*)rec;
    ImgDescRaw* d = (ImgDescRaw*)this;
    GetImageResource((void*)r->mHandle);
    d->m04 = r->m04;
    d->m05 = r->m05;
    d->m06 = r->m06;
    d->m08 = r->m08;
    d->m0c = r->m0c;
    d->m10 = r->m10;
    d->m14 = r->m14;
    d->m18 = r->m18;
    d->m1c = r->m1c;
    d->m20 = r->m20;
    d->m24 = r->m24;
    d->m28 = r->m28;
    d->m2c = r->m2c;
    d->m30 = r->m30;
    d->m34 = r->m34;
    d->m38 = r->m38;
    d->m3c = r->m3c;
    d->m40 = r->m40;
    d->m44 = r->m44;
    d->m48 = r->m48;
    d->m4c = r->m4c;
    d->m50 = r->m50;
    d->m54 = r->m54;
    d->m58 = r->m58;
    d->m5c = r->m5c;
    d->m60 = r->m60;
    d->m64 = r->m64;
    d->m68 = r->m68;
    d->m6c = r->m6c;
    d->m70 = r->m70;
    d->m74 = r->m74;
    return *this;
}

// @ 0x00f6b4b0
TexVector::TexVector(const TexVector& o)
{
    int count = (int)((char*)o.mpCur - (char*)o.mpBegin) / 0x1c4;
    TexDesc* mem;
    if (count != 0)
        mem = (TexDesc*)operator_new(count * 0x1c4, kAllocFile, 0, 0, kAllocFile2, 0xd1);
    else
        mem = 0;
    mpBegin = mem;
    mpCur = mem;
    mpEnd = (TexDesc*)((char*)mem + count * 0x1c4);
    TexDesc* newCur;
    const TexVector* owner = &o;
    CopyTexRange(&newCur, o.mpBegin, o.mpCur, mpBegin, owner);
    mpCur = newCur;
}

// @ 0x00f6b7c0
void QuadNode::FreeAll()
{
    QuadNode* next = mpNext;
    while (next != this) {
        QuadNode* it = next;
        next = it->mpNext;
        void* res = it->mpRes1dc;
        if (res != 0 && *(int*)((char*)res - 4) != 0)
            operator_delete(res);
        void* cnt = it->mpRef88;
        if (cnt != 0)
            RefRelease((int*)((char*)cnt + 8));
        operator_delete(it);
    }
}

// @ 0x00f6b670
QuadSource& QuadSource::CopyFrom(const QuadSource& o)
{
    memcpy(this, &o, 0x7c);
    m7c = o.m7c;
    ImgDesc* pd = new (&mDesc80) ImgDesc(o.mDesc80);
    __assume(pd != 0);
    mf8 = o.mf8;
    mfc = o.mfc;
    m100 = o.m100;
    m104 = o.m104;
    m108 = o.m108;
    m10c = o.m10c;
    VectorCopy(mVec110, o.mVec110, 0xc, 0x10, (void*)kVec3Ctor);
    m1d0 = o.m1d0;
    TexVector* pt = new (&mTex1d4) TexVector(o.mTex1d4);
    __assume(pt != 0);
    return *this;
}

// @ 0x00f6b840
void QuadMgr::Destroy()
{
    void* h = mpHandler08;
    if (h != 0) {
        mpHandler08 = 0;
        EA_MsgRemoveHandler(h, (void*)m0c, (void*)m10, (void*)m14, (void*)m18);
    }
    IViewport* vp = GetViewportInfo2();
    ISlot* cb = (ISlot*)mp74;
    if (cb != 0) {
        mp74 = 0;
        cb->Release();
    }
    uint32_t* slot = mSlots20;
    uint32_t* arg = mSlotArgs38;
    for (int i = 6; i != 0; --i) {
        if (*slot != 0) {
            vp->ReleaseSlot(arg[0], arg[1]);
            *slot = 0;
        }
        arg += 2;
        ++slot;
    }
    if (mSlot68 != 0) {
        vp->ReleaseSlot(mSlotArgs6c[0], mSlotArgs6c[1]);
        mSlot68 = 0;
    }
    FUN_00f674c0(mBlob180);
    FUN_00f674c0(mBlob1a4);
    void* c17c = mpRef17c;
    if (c17c != 0) {
        mpRef17c = 0;
        RefRelease((int*)((char*)c17c + 8));
    }
    void* viewer = mpViewer1c;
    if (viewer != 0) {
        cViewer_dtor(viewer);
        operator_delete(viewer);
    }
    mpViewer1c = 0;
    QuadNode* sentinel = (QuadNode*)0x015b0e48;
    sentinel->FreeAll();
    sentinel->mpNext = sentinel;
    sentinel->mpPrev = sentinel;
    FUN_00f672b0(mp200);
    mp200 = 0;
    FUN_00f672b0(mp204);
    mp204 = 0;
    FUN_00f672b0(mp208);
    mp208 = 0;
}
