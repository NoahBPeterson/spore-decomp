// Slice s00950bb0: EA::UTFWin UI window-proc dispatch + small value/pool helpers (MSVC 2008 SP1,
// /O2 /MD /Gy /EHsc /TP /arch:SSE). PDB names used where known.
#include "types.h"
#include <intrin.h>

void* __fastcall LockedAllocCall(void* self, int reserved, unsigned size,
                                 int, int, int, int, int);  // 0x009289f0
void* __fastcall LockedAlignedCall(void* self, int reserved, int ptr,
                                   unsigned n, int align, int, int, int,
                                   int, int);  // 0x00928a30
extern "C" void  FUN_009276c0(void*, void*);
extern void* g_pMemPool16c8b44;  // 0x016c8b44

namespace EA { namespace UTFWin {

// vtable at +0, refcount at +0x1c.
class CustomWinProc { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    char pad[0x18];
    unsigned int mnRefCount;    // +0x1c

    void* AsInterface(int typeId);   // 0x00950EB0
    void* AsInterfaceA(int typeId);  // 0x00951240
    int   Release();                 // 0x009514A0
};

// @ 0x00950EB0
void* CustomWinProc::AsInterface(int typeId) {
    if (typeId == 0x2f009dd0) return this;
    if (typeId == (int)0xee3f516e || typeId == (int)0xeec58382) {
        if (this) return (char*)this + 4;
    }
    return 0;
}

// @ 0x00951240
void* CustomWinProc::AsInterfaceA(int typeId) {
    if (typeId == 0x6ec581fd) return this;
    if (typeId == (int)0xee3f516e || typeId == (int)0xeec58382) {
        if (this) return (char*)this + 4;
    }
    return 0;
}

// @ 0x009514A0
int CustomWinProc::Release() {
    int n = (*(volatile int*)&mnRefCount += -1);
    if (n == 0) slot2(1);
    return n;
}

class MultiHeapObject { public:
    static void operator_delete(void* p);
};

// @ 0x00951330  EA::UTFWin::MultiHeapObject::operator delete
struct MemPoolObj { void Free(void*); };
extern MemPoolObj* g_pool16c8b44;

void MultiHeapObject::operator_delete(void* p) {
    if (p) {
        int* alloc = *(int**)((char*)p - 8);
        p = (char*)p - 8;
        if (alloc) {
            ((void(__thiscall*)(void*, void*, int))((void**)*(void**)alloc)[3])(alloc, p, 0);
        } else {
            g_pool16c8b44->Free(p);
        }
    }
}

}} // namespace EA::UTFWin

using EA::UTFWin::CustomWinProc;

// ---------------------------------------------------------------------------------------------
// @ 0x00951D60  pool allocator
// ---------------------------------------------------------------------------------------------
struct MemPool {
    char pad0[0x40];
    int  free0;     // +0x40
    int  cur0;      // +0x44
    char pad1[0xc];
    int  free1;     // +0x54
    int  cur1;      // +0x58

    void* Alloc(unsigned size);
};

void* MemPool::Alloc(unsigned size) {
    if (size == 0) return 0;
    if (size < 0x80 && free0 != cur0) {
        void* v = *(void**)(cur0 - 4);
        cur0 -= 4;
        return v;
    }
    if (size < 0x800 && free1 != cur1) {
        void* v = *(void**)(cur1 - 4);
        cur1 -= 4;
        return v;
    }
    return LockedAllocCall(g_pMemPool16c8b44, 0, size, 0, 0, 0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x009512D0  aligned pool alloc with vtable-allocator fallback
// ---------------------------------------------------------------------------------------------
void* AllocAligned(int base, int size, int extra, int* allocator) {
    unsigned n = (size - 1U | 7) + 1;
    void* p;
    if (allocator == 0) {
        p = LockedAlignedCall(g_pMemPool16c8b44, 0, base + 8, n, 8,
                              0, 0, 0, 0, 0);
    } else {
        p = ((void*(__thiscall*)(void*, int, int, int, unsigned, int))((void**)*(void**)allocator)[1])(allocator, base + 8, extra, 0, n, 8);
    }
    if (p == 0) return 0;
    *(void**)p = allocator;
    return (char*)p + 8;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00951DC0  iterator copy
// ---------------------------------------------------------------------------------------------
struct IterCopy {
    int f0, f1, f2, f3, f4, f5, f6, f7;
    IterCopy* Set(int* src);
};

IterCopy* IterCopy::Set(int* src) {
    f0 = (int)(size_t)src;
    f1 = src[1];
    f2 = src[2];
    int v = src[3];
    f3 = v;
    f4 = v;
    int v2 = src[5];
    f5 = v2;
    f6 = src[6];
    f7 = 0;
    if (v2 != f6) f7 = f3 + *(int*)(v2 + 4) * 0x14;
    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x00952100 / 0x00952130 / 0x00952160  bounds value
// ---------------------------------------------------------------------------------------------
struct Bounds {
    char pad0[0x10];
    char  mValid;       // +0x10
    char pad1[3];
    float mMinX;        // +0x14
    float mMinY;        // +0x18
    float mMaxX;        // +0x1c
    float mMaxY;        // +0x20

    char GetBounds(float* out);
    void SetBounds(char valid, const float* r);
    const float* UnionBounds(const float* r);
};

// @ 0x00952100
char Bounds::GetBounds(float* out) {
    out[0] = mMinX;
    out[1] = mMinY;
    out[2] = mMaxX;
    out[3] = mMaxY;
    return mValid;
}

// @ 0x00952130
void Bounds::SetBounds(char valid, const float* r) {
    mValid = valid;
    if (valid) {
        mMinX = r[0]; mMinY = r[1]; mMaxX = r[2]; mMaxY = r[3];
    }
}

// @ 0x00952160
// The original loads arg1 into eax at entry and leaves it there on every path (a hidden return).
// The merge below must reload mMinX/mMinY/mMaxX/mMaxY: without the barrier cl 15.00 keeps all
// four bounds live across the early-out test in xmm1-xmm4, where the original uses only
// xmm0-xmm2 (it folds the early-out reads into comiss memory operands). _ReadWriteBarrier()
// is a compiler fence (no code emitted) that stops that hoist.
const float* Bounds::UnionBounds(const float* r) {
    if (mValid == 0) {
        mValid = 1;
        mMinX = r[0]; mMinY = r[1]; mMaxX = r[2]; mMaxY = r[3];
        return r;
    }
    if (mMaxX <= r[0] || r[2] <= mMinX || mMaxY <= r[1] || r[3] <= mMinY) {
        mMinX = 0; mMinY = 0; mMaxX = 0; mMaxY = 0;
        return r;
    }
    _ReadWriteBarrier();
    if (r[0] > mMinX) mMinX = r[0];
    if (r[1] > mMinY) mMinY = r[1];
    if (r[2] < mMaxX) mMaxX = r[2];
    if (r[3] < mMaxY) mMaxY = r[3];
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x009514D0
// ---------------------------------------------------------------------------------------------
bool ForwardCall514d0(int* a, int* b) {
    void* obj = *(void**)((char*)a + 4);
    ((void(__thiscall*)(void*, int, int))((void**)*(void**)obj)[0x24 / 4])(obj, b[1], b[2]);
    return true;
}

// ---------------------------------------------------------------------------------------------
// vertex-elem array init (stride 8 / 0xc)
// ---------------------------------------------------------------------------------------------
// @ 0x009513D0
bool InitArray8(int* out, int src, int, int* allocator) {
    int* obj = *(int**)(src + 4);
    int count = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    out[2] = count;
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, count * 8, 4);
    out[1] = (int)(size_t)p;
    out[0] = 0x1440200;
    if (count != 0) {
        if (p == 0) return false;
        ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, count);
    }
    return true;
}

// @ 0x009514F0
bool InitArray12(int* out, int src, int, int* allocator) {
    int* obj = *(int**)(src + 4);
    int count = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    out[2] = count;
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, count * 0xc, 4);
    out[1] = (int)(size_t)p;
    out[0] = 0x1440250;
    if (count != 0) {
        if (p == 0) return false;
        ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, count);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00950BB0 / 0x00950EF0  window message dispatchers
// The original lays the case bodies out in the order 3, 4, 1, 2, 5 .. 12, so the switch below
// follows that order as well (MSVC emits the bodies in source order; the jump tables in the image
// are in value order and are regenerated by the compiler).
// ---------------------------------------------------------------------------------------------
struct UIMessage {
    int mSender;     // +0x00  sender object
    int mPad04;      // +0x04
    unsigned int mCode; // +0x08  message id (1..0x1c, 0x1000, 0x1001)
    union {
        struct { int mArg0; int mArg1; int mArg2; int mArg3; };          // +0x0c
        struct { float mFArg0; float mFArg1; float mFArg2; float mFArg3; };
    };
};

class Window_s0095_ff20 {
public:
    bool DoMessage(UIMessage* msg);                      // 0x00960410 (defined in another TU)

    bool HandleMessage(UIMessage* msg);                  // 0x00950BB0
    bool HandleMessageExt(int arg, UIMessage* msg);      // 0x00950EF0
};

// @ 0x00950BB0  bool __thiscall Window_s0095_ff20::HandleMessage(UIMessage*)
bool Window_s0095_ff20::HandleMessage(UIMessage* msg) {
    switch (msg->mCode) {
    case 3:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x28 / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 4:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x2c / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 1:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x30 / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 2:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x34 / 4])(
            this, msg->mArg0, msg->mArg1, msg->mArg2);
    case 5:
        return ((bool (__thiscall*)(void*, int, unsigned short))(*(void***)this)[0x38 / 4])(
            this, msg->mArg0, (unsigned short)msg->mArg1);
    case 6:
        return ((bool (__thiscall*)(void*, float, float, int, int))(*(void***)this)[0x3c / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 7:
        return ((bool (__thiscall*)(void*, float, float, int, int))(*(void***)this)[0x40 / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 8:
        return ((bool (__thiscall*)(void*, float, float, int))(*(void***)this)[0x44 / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg2);
    case 9:
        return ((bool (__thiscall*)(void*, float, float, int, int))(*(void***)this)[0x48 / 4])(
            this, msg->mFArg0, msg->mFArg1, msg->mArg2, msg->mArg3);
    case 10:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x4c / 4])(
            this, msg->mArg0, msg->mArg3);
    case 22:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x50 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 11:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x54 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 12:
        return ((bool (__thiscall*)(void*))(*(void***)this)[0x58 / 4])(this);
    case 23:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x70 / 4])(
            this, msg->mSender, msg->mArg0);
    case 24:
        return ((bool (__thiscall*)(void*, int, int, UIMessage*))(*(void***)this)[0x74 / 4])(
            this, msg->mSender, msg->mArg0, msg);
    case 25:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x78 / 4])(
            this, msg->mArg0, msg->mArg1);
    case 26:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x7c / 4])(
            this, msg->mArg0, msg->mArg1);
    case 27:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x80 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 28:
        return ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x84 / 4])(
            this, msg->mArg0, msg->mArg3);
    case 17:
        ((bool (__thiscall*)(void*))(*(void***)this)[0x5c / 4])(this);
        return false;
    case 18:
        ((bool (__thiscall*)(void*))(*(void***)this)[0x60 / 4])(this);
        return false;
    case 20:
        if (!((bool (__thiscall*)(void*, float, float, int))(*(void***)this)[0x64 / 4])(
                this, msg->mFArg0, msg->mFArg1, msg->mArg3))
            return DoMessage(msg);
        // fall through: the "finish" body is shared with case 16
    case 16:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x68 / 4])(this, msg->mArg3);
        return false;
    case 21:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x6c / 4])(this, msg->mArg3);
        return false;
    default:
        return DoMessage(msg);
    }
}

// @ 0x00950EF0  bool __thiscall Window_s0095_ff20::HandleMessageExt(int arg, UIMessage*)
bool Window_s0095_ff20::HandleMessageExt(int arg, UIMessage* msg) {
    switch (msg->mCode) {
    case 3:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x1c / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 4:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x20 / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 1:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x24 / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 2:
        return ((bool (__thiscall*)(void*, int, int, int, int))(*(void***)this)[0x28 / 4])(
            this, arg, msg->mArg0, msg->mArg1, msg->mArg2);
    case 5:
        return ((bool (__thiscall*)(void*, int, int, unsigned short))(*(void***)this)[0x2c / 4])(
            this, arg, msg->mArg0, (unsigned short)msg->mArg1);
    case 6:
        return ((bool (__thiscall*)(void*, int, float, float, int, int))(*(void***)this)[0x30 / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 7:
        return ((bool (__thiscall*)(void*, int, float, float, int, int))(*(void***)this)[0x34 / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg3, msg->mArg2);
    case 8:
        return ((bool (__thiscall*)(void*, int, float, float, int))(*(void***)this)[0x38 / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg2);
    case 9:
        return ((bool (__thiscall*)(void*, int, float, float, int, int))(*(void***)this)[0x3c / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg2, msg->mArg3);
    case 10:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x40 / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 11:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x44 / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 23:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x68 / 4])(
            this, arg, msg->mSender, msg->mArg0);
    case 24:
        return ((bool (__thiscall*)(void*, int, int, int, UIMessage*))(*(void***)this)[0x6c / 4])(
            this, arg, msg->mSender, msg->mArg0, msg);
    case 25:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x70 / 4])(
            this, arg, msg->mArg0, msg->mArg1);
    case 26:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x74 / 4])(
            this, arg, msg->mArg0, msg->mArg1);
    case 12:
        return ((bool (__thiscall*)(void*, int))(*(void***)this)[0x48 / 4])(this, arg);
    case 20:
        return ((bool (__thiscall*)(void*, int, float, float, int))(*(void***)this)[0x4c / 4])(
            this, arg, msg->mFArg0, msg->mFArg1, msg->mArg3);
    case 27:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x78 / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 28:
        return ((bool (__thiscall*)(void*, int, int, int))(*(void***)this)[0x7c / 4])(
            this, arg, msg->mArg0, msg->mArg3);
    case 17:
        return ((bool (__thiscall*)(void*, int))(*(void***)this)[0x50 / 4])(this, arg);
    case 18:
        return ((bool (__thiscall*)(void*, int))(*(void***)this)[0x54 / 4])(this, arg);
    case 16:
        ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x58 / 4])(this, arg, msg->mArg3);
        return false;
    case 21:
        ((bool (__thiscall*)(void*, int, int))(*(void***)this)[0x5c / 4])(this, arg, msg->mArg3);
        return false;
    default:
        return false;
    case 0x1000:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x60 / 4])(this, arg);
        return true;
    case 0x1001:
        ((bool (__thiscall*)(void*, int))(*(void***)this)[0x64 / 4])(this, arg);
        return true;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00951E10  emit the skin vertices of one quad descriptor into the vertex array
// ---------------------------------------------------------------------------------------------
struct SkinVertex {         // 0x14 bytes of the shared vertex array
    float mX;               // +0x00
    float mY;               // +0x04
    float mZ;               // +0x08
    float mU;               // +0x0c
    float mV;               // +0x10
};

struct SkinRecord {         // 0x0c-byte index record
    unsigned short mVertex; // +0x00
    unsigned short mPad;    // +0x02
    float mOffsetX;         // +0x04
    float mOffsetY;         // +0x08
};

struct SkinBuilderData {
    char pad0[0x1c];
    SkinRecord* mpRecords;  // +0x1c
};

struct SkinQuadDesc {       // 0x14-byte descriptor, one per output quad
    void* mpMesh;           // +0x00
    int   mVertexIndex;     // +0x04  index into the SkinVertex array
    int   mRecordIndex;     // +0x08  index into the SkinRecord array
    int   mRecordCount;     // +0x0c
    int   mVersion;         // +0x10  cached device version
};

struct SkinMeshData {
    char pad0[0x1c];
    void* mField1c;         // +0x1c
};

struct SkinSourceVertex {   // scratch vertex handed to the mesh/renderer callbacks
    SkinMeshData* mpMeshData;  // +0x00
    int   mF4;                 // +0x04
    char  pad08[0x18];         // +0x08
    int   mF20;                // +0x20
    int   mF24;                // +0x24
};

struct SkinPosition {
    int   mFlags;           // +0x00
    float mX;               // +0x04
    float mY;               // +0x08
};

struct RenderContext {
    char  pad0[0x40];
    float mScale;           // +0x40
    char  pad44[8];
    int   mVersion;         // +0x4c
};

struct RenderService;

struct SkinBuilder {
    SkinBuilderData* mpData;    // +0x00
    char  pad04[8];             // +0x04
    SkinVertex* mpVertexBase;   // +0x0c
    void* mpVertexBuffer;       // +0x10
    SkinQuadDesc* mpQuadCur;    // +0x14
    SkinQuadDesc* mpQuadEnd;    // +0x18
    SkinVertex* mpQuadOut;      // +0x1c

    bool BuildSkinVertices(int arg);   // 0x00951E10
};

extern RenderService* g_pRenderService;  // 0x0166aab8

// Renderer service slots used here (offsets into the service vtable).
enum RenderServiceSlot {
    kSvcGetVertex    = 0x14 / 4,
    kSvcDrawVertex   = 0x1c / 4,
    kSvcGetContext   = 0x28 / 4,
    kSvcEvictContext = 0x34 / 4,
    kSvcBindContext  = 0x40 / 4,
    kSvcFlushContext = 0x44 / 4
};

enum SkinMeshSlot {
    kMeshGetSource   = 0x50 / 4,
    kMeshReleaseSrc  = 0x54 / 4
};

// @ 0x00951E10
bool SkinBuilder::BuildSkinVertices(int arg) {
    RenderService* service = g_pRenderService;
    RenderContext* ctx = ((RenderContext* (__thiscall*)(void*, int))
                              (*(void***)service)[kSvcGetContext])(service, 0);
    const int version = ctx->mVersion;
    SkinQuadDesc* desc = mpQuadCur;

    if (desc->mVersion != version) {
        void* mesh = desc->mpMesh;
        SkinVertex* out;
        SkinRecord* rec;
        char textured = 0;

    retry:
        rec = (SkinRecord*)((char*)mpData->mpRecords + desc->mRecordIndex * (int)sizeof(SkinRecord));
        out = mpQuadOut;
        for (unsigned i = 0; i < (unsigned)desc->mRecordCount; ++i, ++rec) {
            SkinPosition pos;
            SkinSourceVertex src;
            char rendered;

            if (!((bool (__thiscall*)(void*, void*, unsigned short, SkinPosition*))
                      (*(void***)service)[kSvcGetVertex])(service, mesh, rec->mVertex, &pos)) {
                if (arg != 0) return false;
                if (((bool (__thiscall*)(void*, SkinSourceVertex*, unsigned short, int, float, float))
                         (*(void***)mesh)[kMeshGetSource])(mesh, &src, rec->mVertex, 0, 0.0f, 0.0f)) {
                    if (textured == 0) {
                        RenderContext* r = ((RenderContext* (__thiscall*)(void*, int))
                                                (*(void***)service)[kSvcGetContext])(service, 0);
                        textured = ((bool (__thiscall*)(void*, RenderContext*))
                                        (*(void***)service)[kSvcBindContext])(service, r);
                        if (textured == 0) goto advance;
                    }
                    rendered = ((bool (__thiscall*)(void*, void*, unsigned short, void*, int, int, int,
                                                    int, SkinPosition*))
                                    (*(void***)service)[kSvcDrawVertex])(
                        service, mesh, rec->mVertex, src.mpMeshData->mField1c, src.mF4, src.mF4,
                        src.mF24, src.mF20, &pos);
                    ((void (__thiscall*)(void*, SkinSourceVertex*))
                         (*(void***)mesh)[kMeshReleaseSrc])(mesh, &src);
                    if (rendered == 0) {
                        RenderContext* r = ((RenderContext* (__thiscall*)(void*, int))
                                                (*(void***)service)[kSvcGetContext])(service, 0);
                        ((void (__thiscall*)(void*, RenderContext*))
                             (*(void***)service)[kSvcEvictContext])(service, r);
                        goto retry;
                    }
                } else {
                    pos.mX = 0.0f;
                    pos.mY = 0.0f;
                }
            }

            const float scale = ctx->mScale;
            const float x = rec->mOffsetX * scale + pos.mX;
            const float y = rec->mOffsetY * scale + pos.mY;
            const float x2 = (out[2].mX - out[0].mX) * scale + x;
            const float y2 = (out[2].mY - out[0].mY) * scale + y;
            out[0].mU = x;
            out[0].mV = y;
            out[1].mU = x2;
            out[1].mV = y;
            out[2].mU = x2;
            out[2].mV = y2;
            out[3].mU = x;
            out[3].mV = y2;
            out += 4;
        }
        if (textured != 0) {
            RenderContext* r = ((RenderContext* (__thiscall*)(void*, int))
                                    (*(void***)service)[kSvcGetContext])(service, 0);
            ((void (__thiscall*)(void*, RenderContext*))
                 (*(void***)service)[kSvcFlushContext])(service, r);
        }
        desc->mVersion = version;
    }

advance:
    mpQuadCur = (SkinQuadDesc*)((char*)mpQuadCur + sizeof(SkinQuadDesc));
    mpQuadOut = 0;
    if (mpQuadCur != mpQuadEnd)
        mpQuadOut = &mpVertexBase[mpQuadCur->mVertexIndex];
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x009520A0  small vftable object constructor (this in ecx, one stack arg)
// ---------------------------------------------------------------------------------------------
struct XformQuad {
    void* mVt;      // +0x00 (0x1440448)
    int   mF4;      // +0x04
    int   mOwner;   // +0x08
    int   mFc;      // +0x0c
    char  mFlag;    // +0x10
    char  mPad[3];  // +0x11
    float mF14;     // +0x14
    float mF18;     // +0x18
    float mF1c;     // +0x1c
    float mF20;     // +0x20

    XformQuad* Init(void* owner);
};

// @ 0x009520A0
XformQuad* XformQuad::Init(void* owner) {
    XformQuad* self = this;
    self->mVt = (void*)0x1440448;
    int zero = (int)(size_t)owner & 0;
    self->mF4 = zero;
    self->mOwner = (int)(size_t)owner;
    self->mFc = -1;
    self->mFlag = (char)zero;
    self->mF14 = 0.0f;
    self->mF18 = 0.0f;
    self->mF1c = 0.0f;
    self->mF20 = 0.0f;
    return self;
}

// ---------------------------------------------------------------------------------------------
// 0x00952230  add element with rounded corners (this in ecx, five float stack args)
// ---------------------------------------------------------------------------------------------
struct ElementList {
    void* mVt;          // +0x00
    int   mF4;          // +0x04
    char  mPad[0x1c];   // +0x08..+0x23
    char  mDefault[1];  // +0x24

    void AddQuad(float x0, float y0, float x1, float y1) {
        ((void(__thiscall*)(ElementList*, float, float, float, float))((void**)*(void**)this)[0x38 / 4])
            (this, x0, y0, x1, y1);
    }

    void AddElementRound(float x0, float y0, float x1, float y1, float z);
};

// @ 0x00952230
void ElementList::AddElementRound(float x0, float y0, float x1, float y1, float z) {
    if (mF4 == 0) mF4 = (int)(size_t)mDefault;
    float w = x1 - x0;
    float dw = *(w > z ? &z : &w);
    float h = y1 - y0;
    float dh = *(h > z ? &z : &h);
    if (0.0f >= dw) return;
    if (0.0f >= dh) return;
    AddQuad(x0, y0, x1, y0 + dh);
    AddQuad(x0, y1 - dh, x1, y1);
    AddQuad(x0, y0 + dh, x0 + dw, y1 - dh);
    AddQuad(x1 - dw, y0 + dh, x1, y1 - dh);
}
