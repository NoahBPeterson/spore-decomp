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
extern "C" void* __cdecl vec_uninit_copy(void** srcOut, AInfo8c* first, AInfo8c* last, AInfo8c* dst, void** srcIn);
extern "C" void  __cdecl vec_clear_range(AInfo8c* first, AInfo8c* last);
extern "C" AInfo8c* __cdecl vec_move_backward(AInfo8c* first, AInfo8c* last, AInfo8c* dst);
extern "C" void  __cdecl vec_fill(AInfo8c* first, AInfo8c* last, AInfo8c* src);
extern "C" void  __cdecl anim_copy_body(void* dst, void* src);     // FUN_007f6ff0
extern "C" void  __cdecl anim_dtor(void* p);                        // FUN_007f6d90
extern "C" void  __cdecl vec88_push_back(void* end, void* src);     // FUN_007f8820
extern "C" AInfo8c* __cdecl cAnimInfo_ctor(AInfo8c* p);             // FUN_007f8970
extern "C" void* __cdecl EA_operator_new(unsigned int size, const char* name, int a, int b, int c, int d);
void* operator new(size_t, const char* name, int a, int b, int c, int d);

inline void DestroyInfo(AInfo8c* p) {
    ((void(__thiscall*)(void*, int))(*(void**)(*(void**)p)))(p, 0);
}

// ---------------------------------------------------------------------------
// eastl::vector<AInfo8c> (sp_vector_allocator): size 0x10
// ---------------------------------------------------------------------------
struct Vec8c {
    AInfo8c* mpBegin;            // +0
    AInfo8c* mpEnd;              // +4
    AInfo8c* mpCapacity;         // +8
    void*    mAlloc;             // +0xc

    int size() const { return (int)((char*)mpEnd - (char*)mpBegin) / 0x8c; }
    int capacity() const { return (int)((char*)mpCapacity - (char*)mpBegin) / 0x8c; }

    AInfo8c* erase(AInfo8c* first, AInfo8c* last);
    AInfo8c* erase(AInfo8c* pos);
    void reserve(uint32_t n);        // 0x007f90f0
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

// @ 0x007f85b0  insert n copies of *value at pos
static void vec_insert_n(Vec8c* v, AInfo8c* pos, uint32_t n, const AInfo8c* value) {
    if ((uint32_t)v->capacity() < n) {
        int oldSize = v->size();
        uint32_t newCap = (oldSize == 0) ? 1u : (uint32_t)oldSize * 2u;
        if (oldSize + n > (int)newCap) newCap = (uint32_t)oldSize + n;
        AInfo8c* mem = 0;
        if (newCap != 0)
            mem = (AInfo8c*)eastl_alloc((int)(newCap * 0x8c), v->mAlloc, 0, 0, "alloc", 0xd1);
        AInfo8c* oldBegin = v->mpBegin;
        void* mid = vec_uninit_copy((void**)&oldBegin, oldBegin, pos, mem, &v->mAlloc);
        vec_clear_range(oldBegin, pos);
        AInfo8c* p = (AInfo8c*)mid;
        vec_fill(p, p + n, (AInfo8c*)value);
        AInfo8c* tail = (AInfo8c*)((char*)p + n * 0x8c);
        void* endp = vec_uninit_copy((void**)&pos, pos, (AInfo8c*)((char*)oldBegin + (oldSize) * 0), tail, &v->mAlloc);
        if (oldBegin != 0 && *(int*)((char*)oldBegin - 4) != 0) eastl_free(oldBegin);
        v->mpBegin = mem;
        v->mpEnd = (AInfo8c*)endp;
        v->mpCapacity = (AInfo8c*)((char*)mem + newCap * 0x8c);
    } else if (n != 0) {
        AInfo8c* oldEnd = v->mpEnd;
        uint32_t tail = (uint32_t)((char*)v->mpEnd - (char*)pos) / 0x8c;
        if (n < tail) {
            AInfo8c* mid = (AInfo8c*)((char*)v->mpEnd - n * 0x8c);
            vec_uninit_copy((void**)&v->mpEnd, mid, v->mpEnd, v->mpEnd, &v->mAlloc);
            v->mpEnd = (AInfo8c*)((char*)v->mpEnd + n * 0x8c);
            vec_move_backward(pos, mid, oldEnd);
            vec_fill(pos, (AInfo8c*)((char*)pos + n * 0x8c), (AInfo8c*)value);
        } else {
            AInfo8c* extra = (AInfo8c*)((char*)v->mpEnd + (n - tail) * 0x8c);
            vec_fill(v->mpEnd, extra, (AInfo8c*)value);
            v->mpEnd = extra;
            vec_uninit_copy((void**)&v->mpEnd, pos, oldEnd, v->mpEnd, &v->mAlloc);
            v->mpEnd = (AInfo8c*)((char*)v->mpEnd + tail * 0x8c);
        }
        vec_fill(pos, oldEnd, (AInfo8c*)value);
    }
}

// @ 0x007f89f0  insert one value at pos
static AInfo8c* vec_insert_one(Vec8c* v, AInfo8c* pos, const AInfo8c* value) {
    if (v->mpEnd != v->mpCapacity) {
        AInfo8c* oldEnd = v->mpEnd;
        vec_move_backward(pos, oldEnd - 1, oldEnd);
        if (oldEnd - 1 >= pos) {
            AInfo8c* t = pos;
            t->animAction = value->animAction;
            /* timer/refcount/data copy through the element assignment */
            anim_copy_body(t, (void*)value);
        }
        v->mpEnd = oldEnd + 1;
        return pos;
    }
    int oldSize = v->size();
    uint32_t newCap = (oldSize == 0) ? 1u : (uint32_t)oldSize * 2u;
    AInfo8c* mem = 0;
    if (newCap != 0) mem = (AInfo8c*)eastl_alloc((int)(newCap * 0x8c), v->mAlloc, 0, 0, "alloc", 0xd1);
    AInfo8c* oldBegin = v->mpBegin;
    void* mid = vec_uninit_copy((void**)&oldBegin, oldBegin, pos, mem, &v->mAlloc);
    AInfo8c* p = (AInfo8c*)mid;
    if (p != 0) anim_copy_body(p, (void*)value);
    void* endp = vec_uninit_copy((void**)&v->mpEnd, pos, v->mpEnd, p + 1, &v->mAlloc);
    if (oldBegin != 0 && *(int*)((char*)oldBegin - 4) != 0) eastl_free(oldBegin);
    v->mpBegin = mem;
    v->mpEnd = (AInfo8c*)endp + 1;
    v->mpCapacity = (AInfo8c*)((char*)mem + newCap * 0x8c);
    return p;
}

// @ 0x007f8b50  resize
static void vec_resize(Vec8c* v, uint32_t n) {
    AInfo8c* first = v->mpBegin;
    AInfo8c* end = v->mpEnd;
    if ((uint32_t)((char*)end - (char*)first) / 0x8c < n) {
        AInfo8c tmp;
        memset(&tmp, 0, sizeof(tmp));
        cAnimInfo_ctor(&tmp);
        vec_insert_n(v, end, n - (uint32_t)((char*)end - (char*)first) / 0x8c, &tmp);
    } else {
        v->erase((AInfo8c*)((char*)first + n * 0x8c), end);
    }
}

// @ 0x007f90f0  reserve
static void vec_reserve(Vec8c* v, uint32_t n) {
    if (n != 0xffffffffu && (uint32_t)v->size() < n) {
        AInfo8c* mem = 0;
        if (n != 0) mem = (AInfo8c*)eastl_alloc((int)(n * 0x8c), v->mAlloc, 0, 0, "alloc", 0xd1);
        AInfo8c* oldBegin = v->mpBegin;
        AInfo8c* oldEnd = v->mpEnd;
        vec_uninit_copy((void**)&oldBegin, oldBegin, oldEnd, mem, &v->mAlloc);
        vec_clear_range(oldBegin, oldEnd);
        if (v->mpBegin != 0 && *(int*)((char*)v->mpBegin - 4) != 0) eastl_free(v->mpBegin);
        int count = (int)((char*)oldEnd - (char*)oldBegin) / 0x8c;
        v->mpBegin = mem;
        v->mpCapacity = (AInfo8c*)((char*)mem + n * 0x8c);
        v->mpEnd = (AInfo8c*)((char*)mem + count * 0x8c);
        return;
    }
    if (n < (uint32_t)v->size()) vec_resize(v, n);
    AInfo8c tmp;
    cAnimInfo_ctor(&tmp);
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
    void InsertEnd(int anim, void* obj, int type);

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
        obj->AddRef();
        e->mpObject = obj;
        if (old) old->Release();
    }
    e->mType = (uint32_t)type;
    e->AssignBody(anim);
    e->animAction((char*)e + 8, 0.0f, 0.0f, 0, 0);
    mB1c = true;
}

// @ 0x007f8f00
void cSPUIAnimator::ClearAll() {
    uint32_t n = (uint32_t)size();
    for (uint32_t i = 0; i < n; ++i) {
        AInfo88* e = mAnimationInfos.mpBegin + i;
        ((void(__thiscall*)(void*, float, float, int, int))(e->animAction))((char*)e + 8, 0.0f, 0.0f, 1, 0);
        void* p = e->mpObject;
        if (p != 0) {
            e->mpObject = 0;
            RcRel(p);
        }
    }
    if (n > 0) {
        for (uint32_t i = 0; i < n; ++i) {
            AInfo88* e = mAnimationInfos.mpBegin + i;
            if (e->mpObject) RcRel(e->mpObject);
        }
        mAnimationInfos.mpEnd = mAnimationInfos.mpBegin;
    }
    mB1c = false;
}

// @ 0x007f8fd0
void cSPUIAnimator::InsertEnd(int anim, void* obj, int type) {
    AInfo88 tmp;
    memset(&tmp, 0, sizeof(tmp));
    AInfo88* end = mAnimationInfos.mpEnd;
    if (end < mAnimationInfos.mpCapacity) {
        mAnimationInfos.mpEnd = end + 1;
        if (end != 0) anim_dtor(&tmp);
    } else {
        vec88_push_back(end, &tmp);
    }
    AInfo88* e = mAnimationInfos.mpEnd - 1;
    anim_copy_body(e, (void*)anim);
    void* old = e->mpObject;
    if (obj != old) {
        if (obj) RcAdd(obj);
        e->mpObject = (IRef*)obj;
        if (old) RcRel(old);
    }
    e->mType = (uint32_t)type;
}

struct AnimHolder {             // object at (*(param_1 + 0x10))
    uint32_t pad0;
    cSPUIAnimator* mpAnimator;  // +4
    Vec8c mSeq;                 // +8 (begin/end of the cAnimInfo vector)
};
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
struct CSeq {
    void* vf;
    void* a; void* b; void* c; void* d;
    virtual ~CSeq();
    CSeq() : a(0), b(0), c(0), d(0) {}
};
CSeq::~CSeq() {}

void* FUN_007f9340(void** p, void** out) {
    p[0] = (void*)0;
    p[2] = (void*)0;
    p[3] = 0;
    CSeq* s = new ("UI/cSPUIAnimationSequence", 0, 0, 0, 0) CSeq();
    p[4] = s;
    if (out != 0) *out = s;
    p[1] = 0;
    return p;
}
