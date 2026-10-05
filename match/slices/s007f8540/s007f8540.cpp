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

struct AInfo88 {                 // cSPUIAnimator::cAnimationInfo, size 0x88
    void* mpObject;              // +0
    uint32_t mType;              // +4
    void* animVf;                // +8
    void* animAction;            // +0xc
    void* timerVf;               // +0x10
    void* mpTimeFunction;        // +0x14
    char mData[0x88 - 0x18];     // +0x18
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
    void*    vftable;            // +0
    AInfo88* mpBegin;            // +4
    AInfo88* mpEnd;              // +8
    AInfo88* mpCapacity;         // +0xc
    void*    mAlloc;             // +0x10
    float    mLastUpdate;        // +0x14
    float    mF18;               // +0x18
    bool     mB1c;               // +0x1c

    int size()  const { return (int)((char*)mpEnd - (char*)mpBegin) / 0x88; }
    int cap()   const { return (int)((char*)mpCapacity - (char*)mpBegin) / 0x88; }

    void callAction(int i, int a, int b, int c, int d) {
        AInfo88* e = mpBegin + i;
        ((void(__thiscall*)(void*, int, int, int, int))(e->animAction))((char*)e + 8, a, b, c, d);
    }

    void dtor();
    void AddAnimation(int anim, void* obj, int type);
    void ClearAll();
    void InsertEnd(int anim, void* obj, int type);
};

// @ 0x007f8c20
void cSPUIAnimator::dtor() {
    vftable = (void*)0;
    int n = size();
    for (int i = 0; i < n; ++i) {
        AInfo88* e = mpBegin + i;
        if (e->animAction != 0) {
            ((void(__thiscall*)(void*, int, int, int, int))(e->animAction))((char*)e + 8, 0, 0, 1, 0);
            if (e->mpObject != 0) {
                void* p = e->mpObject;
                e->mpObject = 0;
                RcRel(p);
            }
        }
    }
    // shift elements to front then destroy
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            AInfo88* e = mpBegin + i;
            if (e->mpObject) RcRel(e->mpObject);
        }
        mpEnd = mpBegin;
    }
    if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) eastl_free(mpBegin);
}

// @ 0x007f8d10
void cSPUIAnimator::AddAnimation(int anim, void* obj, int type) {
    if (obj == 0) return;
    if (*(int*)((char*)anim + 4) == 0) return;
    uint32_t n = (uint32_t)size();
    uint32_t found = n;
    for (uint32_t i = 0; i < n; ++i) {
        AInfo88* e = mpBegin + i;
        if (e->mpObject == 0) break;
        if (e->mpObject == obj && e->mType == (uint32_t)type) {
            if (e->mpObject != 0)
                ((void(__thiscall*)(void*, int, int, int, int))(e->animAction))((char*)e + 8, 0, 0, 1, 0);
            found = i;
            break;
        }
    }
    if (found == (uint32_t)size()) {
        AInfo88* end = mpEnd;
        AInfo88 tmp;
        memset(&tmp, 0, sizeof(tmp));
        if (end < mpCapacity) {
            mpEnd = end + 1;
            if (end != 0) anim_dtor(&tmp);
        } else {
            vec88_push_back(end, &tmp);
        }
    }
    AInfo88* e = mpBegin + found;
    void* old = e->mpObject;
    if (obj != old) {
        if (obj) RcAdd(obj);
        e->mpObject = obj;
        if (old) RcRel(old);
    }
    e->mType = (uint32_t)type;
    anim_copy_body(e, (void*)anim);
    ((void(__thiscall*)(void*, int, int, int, int))(e->animAction))((char*)e + 8, 0, 0, 0, 0);
    mB1c = true;
}

// @ 0x007f8f00
void cSPUIAnimator::ClearAll() {
    uint32_t n = (uint32_t)size();
    for (uint32_t i = 0; i < n; ++i) {
        AInfo88* e = mpBegin + i;
        ((void(__thiscall*)(void*, float, float, int, int))(e->animAction))((char*)e + 8, 0.0f, 0.0f, 1, 0);
        void* p = e->mpObject;
        if (p != 0) {
            e->mpObject = 0;
            RcRel(p);
        }
    }
    if (n > 0) {
        for (uint32_t i = 0; i < n; ++i) {
            AInfo88* e = mpBegin + i;
            if (e->mpObject) RcRel(e->mpObject);
        }
        mpEnd = mpBegin;
    }
    mB1c = false;
}

// @ 0x007f8fd0
void cSPUIAnimator::InsertEnd(int anim, void* obj, int type) {
    AInfo88 tmp;
    memset(&tmp, 0, sizeof(tmp));
    AInfo88* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 1;
        if (end != 0) anim_dtor(&tmp);
    } else {
        vec88_push_back(end, &tmp);
    }
    AInfo88* e = mpEnd - 1;
    anim_copy_body(e, (void*)anim);
    void* old = e->mpObject;
    if (obj != old) {
        if (obj) RcAdd(obj);
        e->mpObject = obj;
        if (old) RcRel(old);
    }
    e->mType = (uint32_t)type;
}

// @ 0x007f9230
bool AnimatorAdvance(int param_1, int param_2, int param_3, int param_4) {
    int iVar1 = *(int*)(param_1 + 0x10);
    (void)param_2; (void)param_3;
    if (param_4 == 0) {
        if (*(int*)(iVar1 + 8) != *(int*)(iVar1 + 0xc)) {
            cSPUIAnimator* a = (cSPUIAnimator*)EA_operator_new(0x20, "UI/cSPUIAnimator", 0, 0, 0, 0);
            if (a != 0) {
                a->vftable = (void*)0;
                a->mpBegin = 0; a->mpEnd = 0; a->mpCapacity = 0;
                a->mLastUpdate = 0.0f; a->mF18 = 0.0f; a->mB1c = false;
            }
            int cur = *(int*)(iVar1 + 8);
            *(cSPUIAnimator**)(iVar1 + 4) = a;
            a->AddAnimation(cur + 4, *(void**)(cur + 0x84), *(int*)(cur + 0x88));
            return a->size() != 0 ? false : true;
        }
    } else if (param_4 == 2) {
        cSPUIAnimator* a = *(cSPUIAnimator**)(iVar1 + 4);
        (*(void(__thiscall**)(cSPUIAnimator*))(*(void**)a))(a);
        int cur = *(int*)(iVar1 + 8);
        ((Vec8c*)(iVar1 + 8))->erase(*(AInfo8c**)(iVar1 + 8));
        if (cur == *(int*)(iVar1 + 0xc)) return false;
        a->AddAnimation(cur + 4, *(void**)(cur + 0x84), *(int*)(cur + 0x88));
        return true;
    } else if (param_4 == 1) {
        void* p = *(void**)(iVar1 + 4);
        if (p != 0) ((void(__thiscall*)(void*, int))(*(void**)(*(void**)p)))(p, 1);
        *(void**)(iVar1 + 4) = 0;
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
