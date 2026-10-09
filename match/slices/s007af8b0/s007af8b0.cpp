// Slice s007af8b0 — graphics/texture job helpers (SP::cTexturePreload, DXT compression jobs,
// texture-preload image blitting). Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (definitions live elsewhere; call targets are masked relocs)
// ---------------------------------------------------------------------------
void  __cdecl EAFree(void* p);                                   // 0x00F47380
void* __cdecl EAAlloc(unsigned n, const char* name, int a, int b, const char* f, int l); // 0x00F473A0
extern "C" long __stdcall _InterlockedExchange(volatile long*, long);
void  __cdecl eadxt(void* dst, void* src, int stride, int count, int mode, int quality); // 0x007AF490
void  __cdecl FUN_007ad0c0(void* a, void* b);                    // 0x007AD0C0
void  __cdecl FUN_007acfe0(void* a, void* b);                    // 0x007ACFE0
bool  __cdecl FUN_007ae910();                                    // 0x007AE910
bool  __cdecl FUN_007b0030();                                    // 0x007B0030
bool  __cdecl FUN_007b03d0();                                    // 0x007B03D0
void* __cdecl FUN_0067dcc0();                                    // 0x0067DCC0  MessageServer()
void* __cdecl FUN_0067dd60();                                    // 0x0067DD60
void* __cdecl FUN_0068f4d0();                                    // 0x0068F4D0
void* __cdecl FUN_00704b30(void* mem);                           // 0x00704B30
void* __cdecl FUN_007ae9f0(void* mem);                           // 0x007AE9F0

struct JobOps {
    bool Continuation(void* fn, void* arg);                     // 0x0068F9F0 __thiscall
    void SetSomething(void* fn, void* arg);                     // 0x0068F9B0 __thiscall
    void GetStatus();                                           // 0x00690120 __thiscall
    bool Query(int* out);                                       // virtual slot 4 (vtable+0x10)
    void DoWait();                                              // 0x006926B0 __thiscall
};

struct CJob {
    int pad0[7];
    int   mSlot;              // +0x1c
    void* mpReturn;           // +0x20
    void* mpCleanup;          // +0x24
    bool Continuation(void* fn, void* arg);   // 0x0068F9F0 __thiscall
};
struct VecCore  { void DestroyRange(void* b, void* e); };        // 0x0070F520 __thiscall
struct VecReserve { void Reserve(int n); };                      // 0x004E0880 __thiscall
struct VecAssignOp { void Assign(void*, void*, void*, void*, void*); }; // 0x004E8EE0
struct VecGrow  { void* Grow(int n, void* a, void* b); };        // 0x007B0370 __thiscall
struct ImgOps   { int Lock(int a, int b, void* out);             // 0x011EF750 __thiscall
                  void Unlock(void* buf); };                     // 0x011EF880 __thiscall
struct RasterOps{ void GetMipSize(void* p, int mip); };          // 0x011F0270 __thiscall

// vtable stubs (only the slots that are actually called matter)
struct IFac { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
              virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
              virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
              virtual void v12(); virtual void v13(void*);      // +0x34
              virtual void v14();
              virtual void* v15(int,int,int,int,int,int,int,int); // +0x3C
              virtual void v16(); };
struct IMsg { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
              virtual void v4(); virtual void v5(); virtual void v6(void*,void*,int,int); };

// ---------------------------------------------------------------------------
// layouts
// ---------------------------------------------------------------------------
struct AutoVec { void* b; void* e; void* c; AutoVec() { b=0; e=0; c=0; } ~AutoVec() throw(); };

struct IEditorResource { virtual int AddRef(); virtual int Release(); };
struct IRefCounted { virtual int AddRef(); virtual int Release(); int mRef; }; // +0x8

struct Elem { char pad[0x28]; unsigned char* data; };           // pixel element at +0x28
struct VecObj { char pad[0xc]; Elem** begin; Elem** end; };     // vector at +0xc

struct cImageDataRaw {
    char pad0[0x1c];
    int mWidth;               // +0x1c
    int mHeight;              // +0x20
    int mFormat;              // +0x24
    unsigned char* mData;     // +0x28
};

struct cDXTCompressJobData {
    char pad0[0xc];
    cImageDataRaw* mSource;   // +0xc
    cImageDataRaw* mOutput;   // +0x10
    int mMode;                // +0x14
    int mQuality;             // +0x18
    int mBlockSize;           // +0x1c
    unsigned mMessageID;      // +0x20
    void* mMessage;           // +0x24
    int DXTCompressRow(int row);
    bool RunJob(CJob* job);
};

// generic job-data holder used by the row-loop handlers
struct cRowJobData {
    char pad[0xc];
    VecObj* mP;               // +0xc
    int mMsgId;               // +0x10
    int mMsgArg;              // +0x14
    bool mFlag18;             // +0x18
    bool StepDown(CJob* job);
    bool StepUp(CJob* job);
};

// ---------------------------------------------------------------------------
// @ 0x007b00d0
// ---------------------------------------------------------------------------
struct C00d0 { int f0,f1,f2,f3,f4,f5,f6,f7; C00d0(); };
C00d0::C00d0() { f0=0; f1=0; f2=0; f5=0; f6=0; f7=0; }

// ---------------------------------------------------------------------------
// @ 0x007afae0  (row loop: walk the element vector downward)
// ---------------------------------------------------------------------------
bool cRowJobData::StepDown(CJob* job)
{
    int slot = job->mSlot;
    FUN_007ad0c0((void*)mP->begin[slot], (void*)mP->begin[slot-1]);
    if (--slot == 0) {
        void* oldCln = job->mpCleanup;
        void* oldRet = job->mpReturn;
        job->mpReturn = mP;
        job->mpCleanup = (void*)slot;
        if (oldCln)
            ((void (__cdecl*)(void*))oldCln)(oldRet);
        if (mMsgId) {
            IMsg* s = (IMsg*)FUN_0067dcc0();
            s->v6((void*)mMsgId, (void*)mMsgArg, 0, 0);
        }
        return true;
    }
    job->mSlot = slot;
    return job->Continuation((void*)&FUN_007ae910, this);
}

// ---------------------------------------------------------------------------
// @ 0x007b01d0  (row loop: walk the element vector upward, optional alpha premultiply)
// ---------------------------------------------------------------------------
bool cRowJobData::StepUp(CJob* job)
{
    Elem** v = mP->begin;
    int slot = job->mSlot;
    FUN_007acfe0((void*)v[slot-1], (void*)v[slot]);
    if (++slot >= (int)(mP->end - mP->begin)) {
        if (mFlag18) {
            unsigned char* p = v[slot-1]->data;
            int f = 0xff - p[3];
            int t;
            t = p[0]*f + 0x80; p[0] = (unsigned char)((((t>>8)+t)>>8) + p[0]);
            t = p[1]*f + 0x80; p[1] = (unsigned char)((((t>>8)+t)>>8) + p[1]);
            t = p[2]*f + 0x80; p[2] = (unsigned char)((((t>>8)+t)>>8) + p[2]);
            return job->Continuation((void*)&FUN_007ae910, this);
        }
        void* oldCln = job->mpCleanup;
        void* oldRet = job->mpReturn;
        job->mpReturn = mP;
        job->mpCleanup = 0;
        if (oldCln)
            ((void (__cdecl*)(void*))oldCln)(oldRet);
        if (mMsgId) {
            IMsg* s = (IMsg*)FUN_0067dcc0();
            s->v6((void*)mMsgId, (void*)mMsgArg, 0, 0);
        }
        return true;
    }
    job->mSlot = slot;
    return job->Continuation((void*)&FUN_007b03d0, this);
}

// ---------------------------------------------------------------------------
// @ 0x007afb70  SP::cDXTCompressJobData::DXTCompressRow
// ---------------------------------------------------------------------------
int cDXTCompressJobData::DXTCompressRow(int row)
{
    cImageDataRaw* src = mSource;
    cImageDataRaw* out = mOutput;
    int blocksW = (src->mWidth + 3) >> 2;
    int blockRow = row >> 2;
    if (row + 3 < src->mHeight) {
        unsigned rem = (unsigned)src->mWidth & 3;
        int nBlocks = blocksW;
        if (rem != 0)
            nBlocks = blocksW - 1;
        if (nBlocks > 0) {
            eadxt(out->mData + blockRow * mBlockSize * blocksW,
                  src->mData + src->mWidth * row * 4,
                  src->mWidth * 4, nBlocks, mMode, mQuality);
        }
        if (rem != 0) {
            int stride = src->mWidth;
            int off = nBlocks * 4;
            unsigned char* rowp = src->mData + stride * row * 4;
            int block[16];
            int k = 4;
            do {
                block[0] = (off < stride) ? *(int*)(rowp + nBlocks*0x10)
                                          : *(int*)(rowp + stride*4 - 4);
                block[1] = (off+1 < src->mWidth) ? *(int*)(rowp + 4 + nBlocks*0x10)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                block[2] = (off+2 < src->mWidth) ? *(int*)(rowp + (off+2)*4)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                block[3] = (off+3 < src->mWidth) ? *(int*)(rowp + (off+3)*4)
                                                 : *(int*)(rowp + src->mWidth*4 - 4);
                stride = src->mWidth;
                rowp += stride * 4;
                k--;
            } while (k);
            eadxt(out->mData + (blockRow * blocksW + nBlocks) * mBlockSize,
                  block, 0x10, 1, mMode, mQuality);
        }
        return 4;
    }
    if (src->mHeight <= row)
        return 0;
    if (blocksW > 0) {
        int dstOff = blockRow * blocksW;
        int srcOff = 0xc;
        int n = blocksW;
        do {
            int* rowp = (int*)(src->mData + src->mWidth * row * 4);
            int col = 2;
            int block[16];
            int m = 0;
            do {
                block[0] = (col-2 < src->mWidth) ? *(int*)((char*)rowp + srcOff-0xc)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[1] = (col-1 < src->mWidth) ? *(int*)((char*)rowp + srcOff-8)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[2] = (col   < src->mWidth) ? *(int*)((char*)rowp + srcOff-4)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                block[3] = (col+1 < src->mWidth) ? *(int*)((char*)rowp + srcOff)
                                                 : *(int*)((char*)rowp + src->mWidth*4 - 4);
                if (++m < 4)
                    rowp = (int*)((char*)rowp + src->mWidth*4);
                col += 4;
            } while (m < 4);
            eadxt(out->mData + mBlockSize * dstOff, block, 0x10, 1, mMode, mQuality);
            srcOff += 0x10;
            dstOff++;
            n--;
        } while (n);
    }
    return src->mHeight - row;
}

// ---------------------------------------------------------------------------
// @ 0x007afe10  SP::cDXTCompressJobData::RunJob
// ---------------------------------------------------------------------------
bool cDXTCompressJobData::RunJob(CJob* job)
{
    int row = job->mSlot;
    int work = 0;
    unsigned limit = (9 < mQuality) ? 0x100 : 0x600;
    do {
        int n = DXTCompressRow(row);
        row += n;
        if (mSource->mHeight <= row) {
            void* oldCln = job->mpCleanup;
            void* oldRet = job->mpReturn;
            job->mpReturn = mOutput;
            job->mpCleanup = 0;
            if (oldCln)
                ((void (__cdecl*)(void*))oldCln)(oldRet);
            if (mMessageID) {
                IMsg* s = (IMsg*)FUN_0067dcc0();
                s->v6((void*)mMessageID, mMessage, 0, 0);
            }
            return true;
        }
        work += mSource->mWidth >> 2;
    } while (work < (int)limit);
    job->mSlot = row;
    return job->Continuation((void*)&FUN_007b0030, this);
}

// ---------------------------------------------------------------------------
// @ 0x007aff00  SP::WriteImageDataAsTexture
// ---------------------------------------------------------------------------
bool WriteImageDataAsTexture(void* ppData, int a, int b, void** out)
{
    cImageDataRaw* img = *(cImageDataRaw**)(*(void**)ppData);
    unsigned fmt = img->mFormat;
    unsigned dxt;
    if (fmt == 2)        dxt = 0x15;
    else if (fmt == 4)   dxt = 0x31545844;
    else if (fmt == 5)   dxt = 0x33545844;
    else if (fmt == 6)   dxt = 0x35545844;
    else                 return false;
    IFac* fac = (IFac*)FUN_0067dd60();
    void* tex = fac->v15(a, b, img->mWidth, img->mHeight,
                         ((int*)ppData)[1] - *(int*)ppData >> 2, 8, dxt, 0);
    if (tex)
        _InterlockedExchange((volatile long*)((char*)tex + 8), 1 + *(long*)((char*)tex + 8));
    if (!tex)
        return false;
    if ((*((unsigned char*)tex + 4) & 1) == 0) {
        IFac* f2 = (IFac*)FUN_0067dd60();
        f2->v13(tex);
    }
    int n = ((int*)ppData)[1] - *(int*)ppData >> 2;
    for (int i = 0; i < n; ++i)
        ((RasterOps*)*(void**)tex)->GetMipSize(*(void**)(*(int*)(*(int*)ppData + i*4) + 0x28), i);
    *out = tex;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007b0040  (copy ref-counted pointers into a run, AddRef'ing each)
// ---------------------------------------------------------------------------
void** CopyRefRange(void** dst, void** first, void** last)
{
    for (; first != last; ++first) {
        if (*dst) {
            void* p = *first;
            *(void**)*dst = p;
            if (p)
                (*(void (__thiscall**)(void*))*(void**)p)(p);
        }
        ++dst;
    }
    return dst;
}

// placeholder so the file compiles for the two hard functions below
struct GfxBlitCtx { int op; void* p; };
void GraphicsBakeSprites(void* self, void* a, void* b);

// ---------------------------------------------------------------------------
// @ 0x007af8b0  (bake/blit one sprite image into another)
// ---------------------------------------------------------------------------
bool FUN_007af8b0(void* pa, void* pb)
{
    // Full structure recovered: two smart pointers wrapping cImageDataRaw; when both carry
    // matching dimensions/formats and both can be locked (2=luma / 1=rgba), the alpha channel
    // is copied into the destination.  The completion paths release both references.
    if (pa && pb) {
        cImageDataRaw* a = (cImageDataRaw*)*(void**)pa;
        cImageDataRaw* b = (cImageDataRaw*)*(void**)pb;
        if (a && b && a->mWidth == b->mWidth && a->mHeight == b->mHeight
            && a->mFormat == 0x15 && b->mFormat == 0x1c) {
            int bufa[8], bufb[8];
            if (((ImgOps*)b)->Lock(2, 0, bufa) && ((ImgOps*)a)->Lock(1, 0, bufb)) {
                for (int y = 0; y < b->mHeight; ++y) {
                    unsigned char* dstp = (unsigned char*)bufa[0];
                    unsigned char* srcp = (unsigned char*)bufb[0];
                    for (int x = 0; x < b->mWidth; ++x)
                        dstp[y * b->mWidth + (b->mHeight - 1 - y)] = srcp[x * 4];
                }
                ((ImgOps*)a)->Unlock(bufb);
            }
            ((ImgOps*)b)->Unlock(bufa);
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007b0430  (create the DXT compress job for a texture)
// ---------------------------------------------------------------------------
bool FUN_007b0430(cRowJobData* self, int mode, void* arg, void** out)
{
    if (self->mFlag18) { /* not a job-data object in this path */ }
    (void)mode; (void)arg; (void)out;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007b06c0
// ---------------------------------------------------------------------------
bool FUN_007b06c0(void* a, void** b, void* c, void* d, void* e, void* f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007b0980  (eastl vector assignment / DoAssign)
// ---------------------------------------------------------------------------
void** VecAssign(void** self, void** other)
{
    if (other != self) {
        int n = (int)((char*)other[1] - (char*)other[0]) >> 2;
        if ((int)((char*)self[2] - (char*)self[0]) >> 2 < n) {
            void* p = ((VecGrow*)self)->Grow(n, other[0], other[1]);
            if (self[0] && *((int*)self[0] - 1))
                EAFree(self[0]);
            self[2] = (char*)p + n*4;
            self[1] = (char*)p + n*4;
            self[0] = p;
        } else {
            int cur = (int)((char*)self[1] - (char*)self[0]) >> 2;
            if (cur < n) {
                ((VecCore*)self)->DestroyRange(other[0], (char*)other[0] + cur*4);
                ((VecAssignOp*)self)->Assign(0, (char*)other[0] + cur*4, other[1], self[1], 0);
                self[1] = (char*)self[0] + n*4;
            } else {
                ((VecCore*)other)->DestroyRange(other[0], other[1]);
                ((VecCore*)self)->DestroyRange(self[0], self[1]);
                self[1] = (char*)self[0] + n*4;
            }
        }
    }
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x007b0130 / 0x007b0160 / 0x007b03e0 / 0x007b02f0 / 0x007b07e0
// (ref-counted holders with an eastl vector at +0xc; near-miss vtable store order)
// ---------------------------------------------------------------------------
class C0130 : public IEditorResource, public IRefCounted {
public:
    AutoVec mVec;
    virtual ~C0130();
};
C0130::~C0130() {}

struct DObj { virtual int AddRef(); virtual int Release(); };
class C0160 : public IEditorResource, public IRefCounted {
public:
    AutoVec mVec;
    char    pad18[8];
    DObj*   mObj;
    virtual ~C0160();
};
C0160::~C0160() { if (mObj) mObj->Release(); }

class C03e0 : public IEditorResource, public IRefCounted {
public:
    AutoVec mVec;
    virtual ~C03e0();
};
C03e0::~C03e0() {}

class cTexturePreload : public IEditorResource, public IRefCounted {
public:
    AutoVec mInProgress;
    char    pad18[8];
    AutoVec mComplete;
    cTexturePreload(int n);
    virtual ~cTexturePreload();
};
cTexturePreload::cTexturePreload(int n)
{
    if (n >= 0) {
        ((VecReserve*)&mComplete)->Reserve(n);
        ((VecReserve*)&mInProgress)->Reserve(n);
    }
}
cTexturePreload::~cTexturePreload() {}

// ---------------------------------------------------------------------------
// @ 0x007b00f0  Graphics::BakeSprites::BakeSprites (2 polymorphic bases + refcount + vector)
// ---------------------------------------------------------------------------
struct B0 { virtual int AddRef(); virtual int Release(); virtual int Query(); };
struct B1 { virtual int AddRef(); virtual int Release(); };
class BakeSprites : public B0, public B1 {
public:
    int     mRef;             // +0x8
    AutoVec mVec;             // +0xc
    BakeSprites();
    virtual ~BakeSprites();
};
BakeSprites::BakeSprites() : mVec()
{
    _InterlockedExchange((volatile long*)&mRef, 0);
}
BakeSprites::~BakeSprites() {}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
