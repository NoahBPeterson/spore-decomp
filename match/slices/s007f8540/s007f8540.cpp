// slice s007f8540: /O2 region (eastl::vector<cAnimInfo> and cSPUIAnimator).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <new>

// ---------------------------------------------------------------------------
// element layouts
// ---------------------------------------------------------------------------
struct AInfo8c {                 // cSPUIAnimationSequence::cAnimInfo, size 0x8c
    void* vf;                    // +0
    void* animVf;                // +4
    void* animAction;            // +8
    void* timerVf;               // +0xc
    void* mpTimeFunction;        // +0x10
    char mData[0x70];            // +0x14
    void* mpObject;              // +0x84
    uint32_t mType;              // +0x88
};

struct IRef {                   // intrusive-refcounted interface: slot 0 AddRef, slot 1 Release
    virtual void AddRef();
    virtual void Release();
    IRef* AddRefChain() { AddRef(); return this; }   // chained at the call site
};
typedef void (__cdecl *AnimActionFn)(void* self, float a, float b, int c, int d);

struct AInfo88 {                 // cSPUIAnimator::cAnimationInfo, size 0x88
    IRef* mpObject;              // +0
    uint32_t mType;              // +4
    void* animVf;                // +8
    AnimActionFn animAction;     // +0xc
    void* timerVf;               // +0x10
    IRef* mpTimeFunction;        // +0x14
    uint32_t mData[(0x88 - 0x18) / 4];  // +0x18

    void CopyFrom(const AInfo88* src);  // 0x007f6d90 (copy-construct in place)
    void AssignBody(const void* src);   // 0x007f6ff0 (called on &animVf)
};

struct Vec88 {                   // eastl::vector<cAnimationInfo, sp_vector_allocator>: size 0x10
    AInfo88* mpBegin;
    AInfo88* mpEnd;
    AInfo88* mpCapacity;
    void*    mAlloc;
    Vec88() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroy(AInfo88* first, AInfo88* last);          // 0x007f78c0
    void PushBackSlow(AInfo88* end, const AInfo88* value);  // 0x007f8820
    int size() const { return (int)((char*)mpEnd - (char*)mpBegin) / 0x88; }
};

extern void* g_013f6400;   // animation vtable (temp element +8)
extern void* g_013f63fc;   // timer vtable (temp element +0x10)
extern "C" AInfo88* __cdecl copy_animinfo88(AInfo88* first, AInfo88* last, AInfo88* dst);  // 0x007f7b30

struct AInfo88T : AInfo88 {      // default-constructed temporary element
    AInfo88T() {
        mpObject = 0;
        animVf = &g_013f6400;
        timerVf = &g_013f63fc;
        mpTimeFunction = 0;
    }
    ~AInfo88T() {
        if (mpTimeFunction) mpTimeFunction->Release();
        if (mpObject) mpObject->Release();
    }
};

// external helpers (masked relocations)
extern "C" void RcAdd(void*);
extern "C" void RcRel(void*);
extern "C" AInfo8c* __cdecl do_copy_animinfo(AInfo8c* first, AInfo8c* last, AInfo8c* dst);
extern "C" void* __cdecl eastl_alloc(int n, void* a, int b, int c, const char* file, int line);
extern "C" void  __cdecl eastl_free(void* p);
// eastl helpers, all modelled with the real 3-argument ABI observed on the call sites.
extern "C" AInfo8c* __cdecl eastl_uninit_copy(AInfo8c* first, AInfo8c* last, AInfo8c* dst);   // 0x007f6ea0
extern "C" void    __cdecl eastl_destroy_range(AInfo8c* first, AInfo8c* last, void* alloc);   // 0x007f5fa0
extern "C" AInfo8c* __cdecl eastl_uninit_fill_n(AInfo8c* dst, uint32_t n, const void* value);  // 0x007f7a30
extern "C" void    __cdecl eastl_fill(AInfo8c* first, AInfo8c* last, const void* value);      // 0x007f7ce0
extern "C" void    __cdecl eastl_move_backward(AInfo8c* first, AInfo8c* last, AInfo8c* dst);  // 0x007f7db0
extern "C" void    __cdecl eastl_move_range(void* out, AInfo8c* first, AInfo8c* last, AInfo8c* dst, void* value);  // 0x007f6e60
extern "C" void    __cdecl anim_copy_body(void* dst, void* src);     // FUN_007f6ff0
extern "C" void    __cdecl anim_dtor(void* p);                        // FUN_007f6d90
extern "C" void    __cdecl anim_assign(void* dst, void* src);         // 0x007f7970 operator=
extern "C" void    __cdecl vec88_push_back(void* end, void* src);     // FUN_007f8820
extern "C" void* __cdecl EA_operator_new(unsigned int size, const char* name, int a, int b, int c, int d);
void* operator new(size_t, const char* name, int a, int b, int c, int d);

// The 0x8c-byte temporary element is built by a thiscall ctor at 0x007f6df0; modelled
// as a void member on a shadow type so placement-new/EH frames are not introduced.
struct AInfo8cCtor { void build(const void* value); };   // 0x007f6df0 (ecx = element)
inline AInfo8c* InfoCtor(AInfo8c* p, const void* value) {
    ((AInfo8cCtor*)p)->build(value);
    return p;
}
struct AInfo8cBuf { void* w[0x8c / 4]; };   // 0x8c-byte element-sized scratch buffer

extern char VtblCAnimInfo;                  // 0x014153bc: cAnimInfo's own vtable
// Default-constructed cAnimInfo temporary.  The original writes it inline (no call):
// vf, animVf, animAction = 0, timerVf, mpTimeFunction = 0, mpObject = 0.
inline void InfoDefault(AInfo8c* p) {
    void** w = (void**)p;
    w[0] = &VtblCAnimInfo;
    w[1] = (void*)0x13f6400;
    w[3] = (void*)0x13f63fc;
    w[4] = 0;
    w[0x84 / 4] = 0;
}

inline void DestroyInfo(AInfo8c* p) {
    ((void(__thiscall*)(void*, int))(*(void**)(*(void**)p)))(p, 0);
}

// ---------------------------------------------------------------------------
// eastl::vector<AInfo8c> (sp_vector_allocator): size 0x10
// ---------------------------------------------------------------------------
struct Vec8c;

// Address-only members of the same object layout used by reserve(): the vector's
// copy constructor, swap and destructor live in other translation units.
struct Vec8cOps {
    void CopyCtor(const Vec8c* src);   // 0x007f8350
    void Swap(Vec8c* other);           // 0x007f8970
    void Dtor();                       // 0x007f6d50
};

struct Vec8c {
    AInfo8c* mpBegin;            // +0
    AInfo8c* mpEnd;              // +4
    AInfo8c* mpCapacity;         // +8
    void*    mAlloc;             // +0xc

    int size() const { return (int)((char*)mpEnd - (char*)mpBegin) / 0x8c; }
    int capacity() const { return (int)((char*)mpCapacity - (char*)mpBegin) / 0x8c; }

    AInfo8c* erase(AInfo8c* first, AInfo8c* last);
    AInfo8c* erase(AInfo8c* pos);
    void     insert(AInfo8c* pos, uint32_t n, const AInfo8c* value);   // 0x007f85b0
    AInfo8c* insert(AInfo8c* pos, const AInfo8c* value);               // 0x007f89f0
    void     resize(uint32_t n);                                       // 0x007f8b50
    void     reserve(uint32_t n);                                      // 0x007f90f0
};

// @ 0x007f8540
AInfo8c* Vec8c::erase(AInfo8c* first, AInfo8c* last) {
    AInfo8c* end = mpEnd;
    AInfo8c* newEnd = do_copy_animinfo(last, end, first);
    for (AInfo8c* p = newEnd; p < end; p += 1) {
        DestroyInfo(p);
    }
    mpEnd -= (last - first);
    return first;
}

// @ 0x007f87e0
AInfo8c* Vec8c::erase(AInfo8c* pos) {
    if (pos + 1 < mpEnd) {
        do_copy_animinfo(pos + 1, mpEnd, pos);
    }
    mpEnd -= 1;
    DestroyInfo(mpEnd);
    return pos;
}

// ---------------------------------------------------------------------------
// The remaining /O2 functions are reconstructed behaviorally; see nonmatching
// / partial bookkeeping.  They are written as real C++ over the layouts above.
// ---------------------------------------------------------------------------

// @ 0x007f85b0
// insert n copies of *value at pos: __thiscall ret 0xc (this = vector)
void Vec8c::insert(AInfo8c* pos, uint32_t n, const AInfo8c* value) {
    Vec8c* v = this;
    char* begin = (char*)v->mpBegin;
    char* end   = (char*)v->mpEnd;
    if ((uint32_t)(((char*)v->mpCapacity - end) / 0x8c) < n) {
        /* reallocate: newCap = max(size + n, size == 0 ? 1 : size * 2) */
        int      oldSize = (int)((end - begin) / 0x8c);
        uint32_t newCap  = (oldSize == 0) ? 1u : (uint32_t)oldSize * 2u;
        uint32_t want    = (uint32_t)oldSize + n;
        if (want > newCap) newCap = want;
        char* mem = 0;
        if (newCap != 0)
            mem = (char*)eastl_alloc((int)(newCap * 0x8c), v->mAlloc, 0, 0,
                                     "EASTL/allocator.h", 0xd1);
        char* oldBegin = (char*)v->mpBegin;
        char* mid = (char*)eastl_uninit_copy((AInfo8c*)oldBegin, pos, (AInfo8c*)mem);
        eastl_destroy_range((AInfo8c*)oldBegin, pos, v->mAlloc);
        char* afterFill = (char*)eastl_uninit_fill_n((AInfo8c*)mid, n, value);
        char* oldEnd = (char*)v->mpEnd;
        char* newEnd = (char*)eastl_uninit_copy(pos, (AInfo8c*)oldEnd, (AInfo8c*)afterFill);
        eastl_destroy_range(pos, (AInfo8c*)oldEnd, v->mAlloc);
        if (oldBegin != 0 && *(int*)(oldBegin - 4) != 0) eastl_free(oldBegin);
        v->mpBegin    = (AInfo8c*)mem;
        v->mpEnd      = (AInfo8c*)newEnd;
        v->mpCapacity = (AInfo8c*)(mem + newCap * 0x8c);
    } else if (n != 0) {
        AInfo8cBuf tmp;
        InfoCtor((AInfo8c*)&tmp, value);
        char* oldEnd = (char*)v->mpEnd;
        uint32_t tail = (uint32_t)((oldEnd - (char*)pos) / 0x8c);
        char* fillEnd;
        char* scratch = (char*)&tmp;
        if (n < tail) {
            char* mid = oldEnd - n * 0x8c;
            eastl_move_range(scratch, (AInfo8c*)mid, (AInfo8c*)oldEnd, (AInfo8c*)oldEnd, scratch);
            v->mpEnd = (AInfo8c*)(oldEnd + n * 0x8c);
            eastl_move_backward(pos, (AInfo8c*)mid, (AInfo8c*)oldEnd);
            fillEnd = (char*)pos + n * 0x8c;
        } else {
            eastl_uninit_fill_n((AInfo8c*)oldEnd, n - tail, &tmp);
            v->mpEnd = (AInfo8c*)(oldEnd + (n - tail) * 0x8c);
            eastl_move_range(scratch, pos, (AInfo8c*)oldEnd, v->mpEnd, scratch);
            v->mpEnd = (AInfo8c*)((char*)v->mpEnd + tail * 0x8c);
            fillEnd = oldEnd;
        }
        eastl_fill(pos, (AInfo8c*)fillEnd, &tmp);
        IRef* a = *(IRef**)((char*)&tmp + 0x10);
        if (a != 0) a->Release();
        IRef* b = *(IRef**)((char*)&tmp + 0x84);
        if (b != 0) b->Release();
    }
}

// @ 0x007f89f0
// insert one value at pos: __thiscall ret 8 (this = vector)
AInfo8c* Vec8c::insert(AInfo8c* pos, const AInfo8c* value) {
    Vec8c* v = this;
    char* end = (char*)v->mpEnd;
    if (end != (char*)v->mpCapacity) {
        char* src = (char*)value;
        if ((char*)value >= (char*)pos && (char*)value < end) src += 0x8c;
        /* a temporary is built at end-0x8c, then the tail is shifted right by one slot */
        InfoCtor((AInfo8c*)(end - 0x8c), value);
        eastl_move_backward(pos, (AInfo8c*)(end - 0x8c), (AInfo8c*)end);
        anim_assign(pos, src);
        v->mpEnd = (AInfo8c*)(end + 0x8c);
        return pos;
    }
    int      oldSize = (int)((end - (char*)v->mpBegin) / 0x8c);
    uint32_t newCap  = (oldSize == 0) ? 1u : (uint32_t)oldSize * 2u;
    char* mem = 0;
    if (newCap != 0)
        mem = (char*)eastl_alloc((int)(newCap * 0x8c), v->mAlloc, 0, 0, "EASTL/allocator.h", 0xd1);
    char* oldBegin = (char*)v->mpBegin;
    char* mid = (char*)eastl_uninit_copy((AInfo8c*)oldBegin, pos, (AInfo8c*)mem);
    eastl_destroy_range((AInfo8c*)oldBegin, pos, v->mAlloc);
    if (mid != 0) InfoCtor((AInfo8c*)mid, value);
    char* oldEnd = (char*)v->mpEnd;
    char* newEnd = (char*)eastl_uninit_copy(pos, (AInfo8c*)oldEnd, (AInfo8c*)(mid + 0x8c));
    eastl_destroy_range(pos, (AInfo8c*)oldEnd, v->mAlloc);
    if (oldBegin != 0 && *(int*)(oldBegin - 4) != 0) eastl_free(oldBegin);
    v->mpBegin    = (AInfo8c*)mem;
    v->mpEnd      = (AInfo8c*)newEnd;
    v->mpCapacity = (AInfo8c*)(mem + newCap * 0x8c);
    return (AInfo8c*)mid;
}

// @ 0x007f8b50
// resize: __thiscall ret 4 (this = vector)
void Vec8c::resize(uint32_t n) {
    Vec8c* v = this;
    AInfo8c* first = v->mpBegin;
    AInfo8c* end   = v->mpEnd;
    uint32_t have  = (uint32_t)(((char*)end - (char*)first) / 0x8c);
    if (have < n) {
        AInfo8cBuf tmp;
        InfoDefault((AInfo8c*)&tmp);
        v->insert(end, n - have, (const AInfo8c*)&tmp);
        IRef* b = *(IRef**)((char*)&tmp + 0x84);
        IRef* a = *(IRef**)((char*)&tmp + 0x10);
        if (b != 0) b->Release();
        if (a != 0) {
            a->Release();
            return;
        }
    } else {
        v->erase((AInfo8c*)((char*)first + n * 0x8c), end);
    }
}

// @ 0x007f90f0
// reserve: __thiscall ret 4 (this = vector)
void Vec8c::reserve(uint32_t n) {
    Vec8c* v = this;
    if (n == 0xffffffffu) {
        Vec8c tmp;
        ((Vec8cOps*)&tmp)->CopyCtor(v);
        ((Vec8cOps*)v)->Swap(&tmp);
        ((Vec8cOps*)&tmp)->Dtor();
        return;
    }
    int have = (int)(((char*)v->mpEnd - (char*)v->mpBegin) / 0x8c);
    if ((uint32_t)have < n) {
        char* mem = 0;
        if (n != 0)
            mem = (char*)eastl_alloc((int)(n * 0x8c), v->mAlloc, 0, 0, "EASTL/allocator.h", 0xd1);
        char* oldBegin = (char*)v->mpBegin;
        char* oldEnd   = (char*)v->mpEnd;
        eastl_uninit_copy((AInfo8c*)oldBegin, (AInfo8c*)oldEnd, (AInfo8c*)mem);
        eastl_destroy_range((AInfo8c*)oldBegin, (AInfo8c*)oldEnd, v->mAlloc);
        if (oldBegin != 0 && *(int*)(oldBegin - 4) != 0) eastl_free(oldBegin);
        v->mpBegin    = (AInfo8c*)mem;
        v->mpCapacity = (AInfo8c*)(mem + n * 0x8c);
        v->mpEnd      = (AInfo8c*)(mem + have * 0x8c);
        return;
    }
    if (n < (uint32_t)have) v->resize(n);
    Vec8c tmp;
    ((Vec8cOps*)&tmp)->CopyCtor(v);    /* vector tmp(*this); */
    ((Vec8cOps*)v)->Swap(&tmp);        /* swap(tmp);        */
    ((Vec8cOps*)&tmp)->Dtor();         /* ~tmp             */
}

// ---------------------------------------------------------------------------
// cSPUIAnimator
// ---------------------------------------------------------------------------
struct cSPUIAnimator {
    // vptr at +0 (virtual destructor, slot 0)
    Vec88    mAnimationInfos;    // +4 (begin, end, capacity, allocator)
    float    mLastUpdate;        // +0x14
    float    mF18;               // +0x18
    bool     mB1c;               // +0x1c

    cSPUIAnimator() : mF18(0.0f), mB1c(false) {}
    virtual ~cSPUIAnimator();

    int size()  const { return (int)((char*)mAnimationInfos.mpEnd - (char*)mAnimationInfos.mpBegin) / 0x88; }
    int cap()   const { return (int)((char*)mAnimationInfos.mpCapacity - (char*)mAnimationInfos.mpBegin) / 0x88; }

    void callAction(int i, int a, int b, int c, int d) {
        AInfo88* e = mAnimationInfos.mpBegin + i;
        ((void(__thiscall*)(void*, int, int, int, int))(e->animAction))((char*)e + 8, a, b, c, d);
    }

    bool Empty();                // 0x007f6340
    void Update();               // 0x007f63b0
    void AddAnimation(void* anim, IRef* obj, int type);
    void ClearAll();

    static void* operator new(size_t n, const char* name, int a, int b, int c, int d) {
        return EA_operator_new((unsigned int)n, name, a, b, c, d);
    }
};

// @ 0x007f8c20
cSPUIAnimator::~cSPUIAnimator() {
    Vec88* v = &mAnimationInfos;
    for (uint32_t i = 0; i < (uint32_t)v->size(); ++i) {
        AInfo88* e = v->mpBegin + i;
        if (e->mpObject != 0) {
            e->animAction((char*)e + 8, 0.0f, 0.0f, 1, 0);
            if (e->mpObject != 0) {
                IRef* p = e->mpObject;
                e->mpObject = 0;
                p->Release();
            }
        }
    }
    AInfo88* first = v->mpBegin;
    AInfo88* last = v->mpEnd;
    AInfo88* ne = copy_animinfo88(last, last, first);
    v->DoDestroy(ne, v->mpEnd);
    v->mpEnd -= (last - first);
    AInfo88* e2 = v->mpEnd;
    v->DoDestroy(v->mpBegin, e2);
    if (v->mpBegin != 0 && ((int*)v->mpBegin)[-1] != 0) eastl_free(v->mpBegin);
}

// @ 0x007f8d10
void cSPUIAnimator::AddAnimation(void* anim, IRef* obj, int type) {
    if (obj == 0) return;
    if (*(int*)((char*)anim + 4) == 0) return;
    Vec88* v = &mAnimationInfos;
    uint32_t n = (uint32_t)v->size();
    uint32_t idx = n;
    uint32_t i = 0;
    if (v->size() != 0) {
        AInfo88* e = v->mpBegin;
        IRef* o;
        while (o = e->mpObject, idx = i, o != 0) {
            if (o == obj && e->mType == (uint32_t)type) {
                if (o != 0) e->animAction((char*)e + 8, 0.0f, 0.0f, 1, 0);
                break;
            }
            ++i;
            ++e;
            idx = n;
            if ((uint32_t)v->size() <= i) break;
        }
    }
    if (idx == (uint32_t)v->size()) {
        AInfo88* end = v->mpEnd;
        AInfo88T tmp;
        if (end < v->mpCapacity) {
            v->mpEnd = end + 1;
            if (end != 0) end->CopyFrom(&tmp);
        } else {
            v->PushBackSlow(end, &tmp);
        }
    }
    AInfo88* e = v->mpBegin + idx;
    IRef* old = e->mpObject;
    if (obj != old) {
        obj = obj->AddRefChain();
        e->mpObject = obj;
        if (old) old->Release();
    }
    e->mType = (uint32_t)type;
    e->AssignBody(anim);
    e->animAction((char*)e + 8, 0.0f, 0.0f, 0, 0);
    mB1c = true;
}

// @ 0x007f8f00
// stop every animation, release each object reference, then destroy the range and
// roll mpEnd back to mpBegin (capacity is kept).
void cSPUIAnimator::ClearAll() {
    for (int i = 0; i < size(); ++i) {
        AInfo88* e = &mAnimationInfos.mpBegin[i];
        e->animAction((char*)e + 8, 0.0f, 0.0f, 1, 0);
        IRef* p = e->mpObject;
        if (p != 0) {
            e->mpObject = 0;
            p->Release();
        }
    }
    AInfo88* begin = mAnimationInfos.mpBegin;
    AInfo88* end   = mAnimationInfos.mpEnd;
    mAnimationInfos.DoDestroy(copy_animinfo88(end, end, begin), end);
    mAnimationInfos.mpEnd -= (int)((char*)end - (char*)begin) / 0x88;
    mB1c = false;
}

// The sequence host: animator pointer at +4, the cAnimInfo vector at +8.
struct AnimHolder {
    uint32_t pad0;               // +0
    cSPUIAnimator* mpAnimator;   // +4
    Vec8c mSeq;                  // +8
    void Append(int anim, IRef* obj, int type);   // 0x007f8fd0
};

// @ 0x007f8fd0
// append one animation record: __thiscall ret 0xc (anim, obj, type)
void AnimHolder::Append(int anim, IRef* obj, int type) {
    AInfo8cBuf tmp;
    InfoDefault((AInfo8c*)&tmp);
    AInfo8c* end = mSeq.mpEnd;
    if (end < mSeq.mpCapacity) {
        mSeq.mpEnd = end + 1;
        if (end != 0) InfoCtor(end, (const void*)&tmp);
    } else {
        mSeq.insert(end, (const AInfo8c*)&tmp);
    }
    IRef* r = *(IRef**)((char*)&tmp + 0x84);
    if (r != 0) r->Release();
    IRef* t = *(IRef**)((char*)&tmp + 0x10);
    if (t != 0) t->Release();
    AInfo8c* e = (AInfo8c*)((char*)mSeq.mpEnd - 0x8c);
    anim_copy_body((char*)e + 4, (void*)anim);
    void* old = e->mpObject;
    if ((void*)obj != old) {
        obj = obj->AddRefChain();
        e->mpObject = obj;
        if (old) ((IRef*)old)->Release();
    }
    e->mType = (uint32_t)type;
}
// @ 0x007f9230
bool AnimatorAdvance(int param_1, int param_2, int param_3, int param_4) {
    AnimHolder* h = *(AnimHolder**)(param_1 + 0x10);
    (void)param_2; (void)param_3;
    if (param_4 == 0) {
        if (h->mSeq.mpBegin != h->mSeq.mpEnd) {
            cSPUIAnimator* a = new ("UI/cSPUIAnimator", 0, 0, 0, 0) cSPUIAnimator();
            AInfo8c* cur = h->mSeq.mpBegin;
            h->mpAnimator = a;
            a->AddAnimation((char*)cur + 4, (IRef*)cur->mpObject, (int)cur->mType);
            return !h->mpAnimator->Empty();
        }
    } else if (param_4 == 2) {
        h->mpAnimator->Update();
        if (h->mpAnimator->Empty()) {
            Vec8c* sq = &h->mSeq;
            sq->erase(sq->mpBegin);
            if (sq->mpBegin == sq->mpEnd) return false;
            AInfo8c* cur = sq->mpBegin;
            h->mpAnimator->AddAnimation((char*)cur + 4, (IRef*)cur->mpObject, (int)cur->mType);
        }
        return true;
    } else if (param_4 == 1) {
        cSPUIAnimator* a = h->mpAnimator;
        if (a != 0) ((void(__thiscall*)(cSPUIAnimator*, int))(*(void***)a)[0])(a, param_4);
        h->mpAnimator = 0;
        h->mSeq.reserve(0);
        return true;
    }
    return false;
}

// @ 0x007f9340
// Build the animation-sequence block: two interface vtable values, a freshly
// allocated 0x1c-byte sequence object (vtable 0x0141542c) and the advance thunk.
void* FUN_007f9340(void** p, void** out) {
    p[0] = (void*)0x13f6400;
    p[2] = (void*)0x13f63fc;
    p[3] = 0;
    void** obj = (void**)operator new(0x1c, "UI/cSPUIAnimationSequence", 0, 0, 0, 0);
    if (obj != 0) {
        obj[0] = (void*)0x141542c;
        obj[1] = 0;
        obj[2] = 0;
        obj[3] = 0;
        obj[4] = 0;
    } else {
        obj = 0;
    }
    p[4] = obj;
    if (out != 0) *out = obj;
    p[1] = (void*)0x7f9230;
    return p;
}
