// Slice s00b0e560 (batch bfs1) — 19 functions.
// Module "Spore".  Source for every VA in the slice; each block starts with its
// original address.  See s00b0e560.h for the recovered class shapes.
//
// Functions 00b0e560..00b0ee10 operate on a serialization / render-queue manager
// that owns several spstl::slot_vector and EASTL list members; the virtual calls
// go through the interfaces returned by the reader chain.  They are behaviourally
// complete but not byte-exact (the spstl container templates are not reproduced).

#include "s00b0e560.h"
#include "types.h"
#include <math.h>

extern "C" void ResetEffectStates();                          // 0x006f3290
extern "C" void ReadInt32(void*, void*, int, int);            // EA::IO::ReadInt32 0x0093a780
extern "C" void ctor_00afb7a0();                              // 0x00afb7a0
extern "C" void* SP_BehaviorManager();                        // 0x00b3d260
extern "C" void destructor_00f47380(void*);                   // operator delete 0x00f47380
extern "C" void eastl_list_erase(void*);                      // 0x0075f3f0
extern "C" void FUN_00b0d710(void*, int, void*);
extern "C" void FUN_00b0dec0(void*, ...);
extern "C" void FUN_00b0e250(void*, void*);
extern "C" void FUN_00b0e490(void*);
extern "C" void* FUN_00b0d1d0(void*, void*, void*);
extern "C" void FUN_00b0cfd0(void*, void*);
extern "C" void FUN_00b0cf80(void*, void*, void*, void*);
extern "C" void FUN_00b0d500(void*, void*);
extern "C" void FUN_00b0d050(void*);
extern "C" void FUN_00abec70(void*);
extern "C" void FUN_00abf2b0();
extern "C" void FUN_00abf110(void*);
extern "C" void FUN_00ac0010(void*);
extern "C" void FUN_00abe9b0();                                // slot-vector iterator++
extern "C" int  FUN_00b0d010(void*, void*, int);               // live slot count
extern "C" void* FUN_00b30d70();                               // SP::GetGameTerrainCursor
extern "C" void FUN_00b0dc60();
extern float g_2pi;                                           // +0x167bd10

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }

// slot_vector_base<...> method shape: the vector itself is `this` (ECX) and the
// value to store is the only stack argument (0x00b0e490 calls end with `ret 4`).
struct SlotVectorStore
{
    void FUN_00b0e490(void* src);                  // 0x00b0e490
    void FUN_00b0d500(void** out, void* from);     // 0x00b0d500
};

template<class R> static inline R vcall0(void* p, int off)
{ return ((R(__thiscall*)(void*))g_vfn(p, off))(p); }
template<class R, class A1> static inline R vcall1(void* p, int off, A1 a1)
{ return ((R(__thiscall*)(void*, A1))g_vfn(p, off))(p, a1); }
template<class R, class A1, class A2> static inline R vcall2(void* p, int off, A1 a1, A2 a2)
{ return ((R(__thiscall*)(void*, A1, A2))g_vfn(p, off))(p, a1, a2); }
template<class R, class A1, class A2, class A3> static inline R vcall3(void* p, int off, A1 a1, A2 a2, A3 a3)
{ return ((R(__thiscall*)(void*, A1, A2, A3))g_vfn(p, off))(p, a1, a2, a3); }

// ===========================================================================
// Polymorphic input host (vtable + cLocalInputState at +0x31c)
// ===========================================================================

// @ 0x00b0f140
bool InputHost::FUN_00b0f140(int /*unused*/)
{
    mInput.Reset();
    return false;
}

// @ 0x00b0f170
void InputHost::FUN_00b0f170()
{
    v50();
    ResetEffectStates();
}

// @ 0x00b0f190
bool InputHost::FUN_00b0f190(int vkCode, int modifiers)
{
    mInput.OnKeyDown(vkCode, modifiers);
    return false;
}

// @ 0x00b0f1b0
bool InputHost::FUN_00b0f1b0(int button, float x, float y, int state)
{
    mInput.OnMouseDown(button, x, y, state);
    return true;
}

// @ 0x00b0f1e0
bool InputHost::FUN_00b0f1e0(int button, float x, float y, int state)
{
    mInput.OnMouseUp(button, x, y, state);
    return false;
}

// @ 0x00b0f210
void InputHost::FUN_00b0f210(float* out0, float* out1, float* out2)
{
    *out0 = m15c;
    *out1 = m138;
    *out2 = m114;
}

// @ 0x00b0f240
void InputHost::FUN_00b0f240(float* out0, float* out1, float* out2)
{
    *out0 = m154;
    *out1 = m130;
    *out2 = m10c;
}

// ===========================================================================
// Math helpers
// ===========================================================================

// @ 0x00b0f060
// Hermite smoothstep: clamp x into [lo,hi], normalise, then t*t*(3 - 2t).
// The Clamp step is the module's SSE __asm helper (maxss/minss), as used by the
// /arch:SSE math code in this binary.
static __forceinline float ClampSSE(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x;
        maxss xmm0, lo;
        minss xmm0, hi;
        movss x, xmm0;
    }
    return x;
}

float FUN_00b0f060(float lo, float hi, float x)
{
    float v = ClampSSE(x, lo, hi);
    float t = (v - lo) / (hi - lo);
    return t * t * (3.0f - 2.0f * t);
}

// @ 0x00b0f0c0
// Wraps the delta (b - a) into (-pi, pi] and returns a + delta * t.
extern float g_pi;                              // +0x1567dc8
float FUN_00b0f0c0(float a, float b, float t)
{
    float d = b - a;
    float r = (float)fmod((double)d, (double)g_2pi);
    if (r > g_pi)
        r = r - g_2pi;
    else if (r < -g_pi)
        r = r + g_2pi;
    return r * t + a;
}

// ===========================================================================
// Serialization / render-queue manager
// ===========================================================================

// @ 0x00b0e560
// Reads a count from the stream, resizes the slot vector, then for each slot
// releases the old element and lets the host re-create it.
void cRenderQueue::FUN_00b0e560(int host_, int vec_, uint32_t flags)
{
    char* host = (char*)host_;
    uint32_t* vec = (uint32_t*)vec_;
    void* obj = vcall0<void*>(host, 0x20);
    void* reader = vcall0<void*>(obj, 0x18);
    int count = 0;
    ReadInt32(reader, &count, 1, (int)flags);

    uint32_t beg = vec[0], end = vec[1];
    int n = (int)(end - beg) >> 2;
    if (n < count)
    {
        int zero = 0;
        FUN_00b0d710((void*)end, count - n, &zero);
    }
    else
    {
        FUN_00b0dec0((void*)(beg + count * 4), (void*)end);
    }

    for (int i = 0; i < count; ++i)
    {
        char* slot = (char*)(vec[0] + i * 4);
        void* p = *(void**)slot;
        if (p)
        {
            *(void**)slot = 0;
            vcall0<void>(p, 0x5c);
        }
        vcall3<void, uint32_t, void*, int>(host, 0x28, flags, slot, 0);
    }
}

// @ 0x00b0e610
// Clears the +0x20 slot vector then reads a replacement from the stream.
bool cRenderQueue::FUN_00b0e610(int host_)
{
    char* self = (char*)this;
    char* host = (char*)host_;
    uint32_t tmp[3] = { 0, 0, 0 };
    FUN_00b0e250(tmp, self + 0x20);
    FUN_00b0dec0(tmp, (void*)0, (void*)0);
    void* obj = vcall0<void*>(host, 0x20);
    void* reader = vcall0<void*>(obj, 0x18);
    ReadInt32(reader, self + 0x94, 1, 0);
    FUN_00b0e560(host_, (int)(self + 0x20), 0x11c0ba3u);
    ctor_00afb7a0();
    return true;
}

// @ 0x00b0e6a0
// Resets the two slot vectors at +0x5c and +0x78 and empties the render-job list.
void cRenderQueue::FUN_00b0e6a0()
{
    char* self = (char*)this;
    uint32_t tmp[3] = { 0, 0, 0 };
    FUN_00b0e250(tmp, self + 0x20);
    FUN_00b0dec0(tmp, (void*)0, (void*)0);

    {   // slot vector at +0x5c
        void* b = *(void**)(self + 0x5c);
        void* e = *(void**)(self + 0x60);
        void* p = FUN_00b0d1d0(e, e, b);
        FUN_00b0cfd0(p, *(void**)(self + 0x60));
        *(int*)(self + 0x60) = *(int*)(self + 0x60) + ((int)((char*)e - (char*)b) >> 3) * -8;
        *(uint32_t*)(self + 0x70) = 0x3fffffffu;
        *(uint32_t*)(self + 0x74) = 0x3fffffffu;
    }
    {   // slot vector at +0x78
        void* b = *(void**)(self + 0x78);
        void* e = *(void**)(self + 0x7c);
        void* p = FUN_00b0d1d0(e, e, b);
        FUN_00b0cfd0(p, *(void**)(self + 0x7c));
        *(int*)(self + 0x7c) = *(int*)(self + 0x7c) + ((int)((char*)e - (char*)b) >> 3) * -8;
        *(uint32_t*)(self + 0x8c) = 0x3fffffffu;
        *(uint32_t*)(self + 0x90) = 0x3fffffffu;
    }
    eastl_list_erase(self + 0x34);            // eastl::list<cRenderJob>::clear()
    *(int*)(self + 0x34) = (int)(self + 0x34);
    *(int*)(self + 0x38) = (int)(self + 0x34);
    *(int*)(self + 0x98) = 0;
    ctor_00afb7a0();
}

// @ 0x00b0e780
// Iterates a bit-index range and relocates the referenced slot entries.
cRenderQueue* cRenderQueue::FUN_00b0e780(int src_)
{
    char* self = (char*)this;
    uint32_t* src = (uint32_t*)src_;
    FUN_00abec70(src);

    uint32_t count = (((src[1] - src[0]) >> 2) << 7) + src[5] - 0x7f;
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t* s = (uint32_t*)(*(uint32_t*)(src[0] + (i >> 7) * 4) + (i & 0x7f) * 8);
        FUN_00abf2b0();
        uint32_t* d = (uint32_t*)(*(uint32_t*)(*(uint32_t*)(self + 4) - 4) + *(uint32_t*)(self + 0x14) * 8);
        if (d)
        {
            *d = *s;
            if ((*s & 0x80000000u) == 0 && d + 1)
            {
                d[1] = s[1];
                if (s[1])
                    vcall0<void>((void*)s[1], 0x60);
            }
        }
    }
    return this;
}

// @ 0x00b0e810
// Refcounts one element into the +0x60 slot vector and swaps it out.
void cRenderQueue::FUN_00b0e810(int p_)
{
    char* self = (char*)this;
    void* p = (void*)p_;
    if (p)
        vcall0<void>(p, 0x0);
    // 0x00b0e490 is a slot_vector_base method: the vector (+0x60) is `this`, the
    // AutoRefCount to store arrives on the stack.
    ((SlotVectorStore*)(self + 0x60))->FUN_00b0e490(&p);
    if (p)
        vcall0<void>(p, 0x4);

    char* v = self + 0x44;
    uint32_t idx = *(uint32_t*)(v + 0x14);
    void* cur = (idx < 0x3fffffffu)
        ? (void*)(*(uint32_t*)v + idx * 8)
        : *(void**)(v + 4);
    // 0x00b0cf80 writes the slot holding `p` to its out pointer and 0x00b0d500
    // (a slot_vector method) then finds room for it, writing the slot back out.
    void* slot = p;                  // 0x00b0cf80 overwrites it with the found slot
    void* ref  = p;                  // the value it searches for
    FUN_00b0cf80(&slot, cur, *(void**)(v + 4), &ref);
    ((SlotVectorStore*)v)->FUN_00b0d500(&p, slot);
}

// @ 0x00b0e890
// Removes all dead jobs from the +0x38 list.
void cRenderQueue::FUN_00b0e890()
{
    char* self = (char*)this;
    char* sentinel = self + 0x38;
    char* it = *(char**)sentinel;
    while (it != sentinel)
    {
        void* job = *(void**)(it + 8);
        char* next;
        if (job)
            vcall0<void>(job, 0x0);
        if (!vcall0<int>(job, 0x58))
        {
            next = *(char**)it;
        }
        else
        {
            vcall0<void>(job, 0x20);
            FUN_00b0e490(&job);
            next = *(char**)it;
            char* node = *(char**)(next + 4);
            *(int*)(*(int*)(node + 4)) = *(int*)node;
            *(int*)(*(int*)node + 4) = *(int*)(node + 4);
            if (*(void**)(node + 8))
                vcall0<void>(*(void**)(node + 8), 0x4);
            destructor_00f47380(node);
        }
        if (job)
            vcall0<void>(job, 0x4);
        it = next;
    }
}

// @ 0x00b0e920
// Empties the +0x7c slot vector, then moves every live slot of the +0x60 vector
// into it and releases the +0x60 entries.
int cRenderQueue::FUN_00b0e920()
{
    RenderQueueView* q = (RenderQueueView*)this;
    SlotVector* vc = &q->mVecC;   // +0x7c
    SlotVector* vb = &q->mVecB;   // +0x60

    // 1) erase everything the +0x7c vector currently holds
    uint8_t* begC = vc->mpSlots;
    uint8_t* endC = vc->mpSlotsEnd;
    void* moved = FUN_00b0d1d0(endC, endC, begC);
    ((void (__thiscall*)(SlotVector*, void*, void*))FUN_00b0cfd0)(vc, moved, vc->mpSlotsEnd);
    vc->mpSlotsEnd += -8 * (int)((endC - begC) >> 3);
    vc->mBegin = SlotVector::kNil;
    vc->mFreeChain = SlotVector::kNil;

    // 2) re-insert every live slot of the +0x60 vector, skipping free runs
    uint8_t* cur = vb->beginSlot();
    uint8_t* endB = vb->mpSlotsEnd;
    while (endB != cur)
    {
        ((void (__thiscall*)(SlotVector*, void*))FUN_00b0e490)(vc, cur + 4);
        do
        {
            uint32_t w = *(uint32_t*)cur;
            cur += 8;
            if (w & 0x40000000u) break;
        } while ((int)*(uint32_t*)cur < 0);
    }

    // 3) release and drop every slot of the +0x60 vector
    uint8_t* begB = vb->mpSlots;
    uint8_t* p = begB;
    uint8_t* endVb = vb->mpSlotsEnd;
    while (p < endVb)
    {
        SlotEntry* e = (SlotEntry*)p;
        if ((int)e->mSlotInfo >= 0 && e->mpData != 0)
            vcall0<void>(e->mpData, 0x4);
        p += 8;
    }
    vb->mpSlotsEnd += -8 * (int)((endVb - begB) >> 3);
    vb->mBegin = SlotVector::kNil;
    vb->mFreeChain = SlotVector::kNil;

    return 0x3fffffff;
}

// @ 0x00b0ea30
// Destroys the per-frame jobs and empties the manager.
void cRenderQueue::FUN_00b0ea30()
{
    RenderQueueView* q = (RenderQueueView*)this;

    // 1) notify every entry of the +0x24 job vector
    uint32_t n = (uint32_t)(q->mpJobEnd - q->mpJobBegin);
    for (uint32_t i = 0; i < n; ++i)
        vcall0<void>(q->mpJobBegin[i], 0x34);

    // 2) drop every live slot of the +0x44 vector
    SlotVector* va = &q->mVecA;   // +0x44
    while (va->mBegin != SlotVector::kNil)
        vcall1<void, void*>(this, 0x18, va->slotData(va->mBegin));

    // 3) drain the +0x60 and +0x7c vectors
    while (q->mVecB.mBegin != SlotVector::kNil || q->mVecC.mBegin != SlotVector::kNil)
    {
        ((void (__thiscall*)(void*))FUN_00b0dc60)(this);
        FUN_00b0e920();
    }

    // 4) tear down the +0x38 intrusive list
    JobListNode* sentinel = &q->mJobList;
    JobListNode* it = sentinel->mpNext;
    while (it != sentinel)
    {
        JobListNode* next = it->mpNext;
        if (it->mpPayload != 0)
            vcall0<void>(it->mpPayload, 0x4);
        destructor_00f47380(it);
        it = next;
    }
    sentinel->mpPrev = sentinel;
    sentinel->mpNext = sentinel;
}

// lower_bound probe of the ordered map embedded at InteractionAgentView::+0x50
// (the map's own header node is at +0x50, its root pointer at +0x58, a node's
// key at +0x10).
static MapNode* rq_map_lower_bound(InteractionAgentView* agent, uint32_t key)
{
    MapNode* header = (MapNode*)&agent->mpMapHeader;
    MapNode* node   = (MapNode*)agent->mpMapRoot;
    MapNode* best   = header;
    while (node != 0)
    {
        if (node->mKey < key)
            node = node->mpChild0;
        else
        {
            best = node;
            node = node->mpChild1;
        }
    }
    if (best != header && key >= best->mKey)
        return best;
    return header;
}

// @ 0x00b0eae0
// Interaction-agent tick: rebuild the +0x40 slot vector, account every slot of
// each agent's own vector, then push each job's interaction object.
// `this` is 4 bytes above the base the other methods see; the two member calls
// and FUN_00b0e890() are therefore made through this-4.
void cRenderQueue::FUN_00b0eae0(int /*unused*/, int agents_)
{
    char* self = (char*)this;
    cRenderQueue* base = (cRenderQueue*)(void*)(self - 4);
    ((void (__thiscall*)(void*))FUN_00b0dc60)(self - 4);
    base->FUN_00b0e920();

    if (agents_ == 0 || *(char*)(self + 0x9c) != 0)
        return;
    *(int*)(self + 0x98) = agents_;

    RenderQueueInnerView* q = (RenderQueueInnerView*)self;
    SlotVector* va = &q->mVecA;   // +0x40

    uint8_t* it = va->beginSlot();
    uint8_t* vend = va->mpSlotsEnd;
    while (vend != it)
    {
        InteractionAgentView* agent = (InteractionAgentView*)((SlotEntry*)it)->mpData;
        if (agent)
            vcall0<void>(agent, 0x0);

        if (agent->mTickState == 1)
        {
            // walk the agent's own slot vector (at +0x2c), accounting every slot
            SlotIter iter;
            iter.mpOwner = &agent->mpBlocks;
            iter.mIndex  = agent->mFreeChain;
            if (iter.mIndex >= SlotVector::kNil)
                iter.mIndex = agent->indexEnd();
            while (iter.mIndex != agent->indexEnd())
            {
                uint32_t key = (uint32_t)(uintptr_t)((SlotEntry*)((char*)agent->mpBlocks[iter.mIndex >> 7]
                                             + (iter.mIndex & 0x7f) * 8))->mpData;
                MapNode* header = (MapNode*)&agent->mpMapHeader;
                MapNode* node = rq_map_lower_bound(agent, key);
                if (node == header || node->mValue == 0)
                {
                    MapNode* found = rq_map_lower_bound(agent, key);
                    int32_t v  = (found == header) ? 0 : found->mValue2;
                    int32_t lo = (v <= agents_) ? v : agents_;
                    uint32_t lookup = key;
                    MapNode* ins = (MapNode*)((void* (__thiscall*)(void*, uint32_t*))FUN_00ac0010)(
                                       (char*)agent + 0x4c, &lookup);
                    ins->mValue = v - lo;
                }
                ((void (__thiscall*)(void*))FUN_00abe9b0)(&iter);
            }
            agent->mTickState = vcall0<int>(agent, 0x18);
        }

        if (vcall0<int>(agent, 0x58) == 0)
        {
            void* bm = SP_BehaviorManager();
            vcall1<void, void*>(bm, 0x18, agent);
        }
        vcall0<void>(agent, 0x4);

        do
        {
            uint32_t w = *(uint32_t*)it; it += 8;
            if (w & 0x40000000u) break;
        } while ((int)*(uint32_t*)it < 0);
    }

    // push each job's interaction object into the +0x20 job vector
    typedef void (__thiscall* FnV44)(void*, uint32_t, uint32_t, uint32_t,
                                     uint32_t, uint32_t, uint32_t);
    void** p     = q->mpJobBegin;
    void** pend  = q->mpJobEnd;
    void*  g2    = 0;
    void*  g3    = 0;
    void*  prevG2 = 0;
    void*  prevG3 = 0;
    for (; p != pend; ++p)
    {
        void* x   = *p;
        void* cur = prevG2;
        if (x != prevG2)
        {
            if (x) vcall0<void>(x, 0x60);
            cur = x;
            if (prevG2) vcall0<void>(prevG2, 0x5c);
        }
        g2 = cur;

        void* y = prevG3;
        if (vcall0<char>(g2, 0x1c) != 0)
        {
            InteractionAgentView* a2 = (InteractionAgentView*)vcall0<void*>(g2, 0x20);
            if (a2->mTickState == 0)
            {
                void* y2 = vcall0<void*>(g2, 0x20);
                if (y2 != prevG3)
                {
                    if (y2) vcall0<void>(y2, 0x0);
                    y = y2;
                    if (prevG3) vcall0<void>(prevG3, 0x4);
                }
                uint32_t buf[6] = { 0, 0, 0, 0, 0, 0 };
                ((void (__thiscall*)(void*, uint32_t*, void*))FUN_00abf110)(y, buf, g2);
                if (buf[0] + buf[1] != buf[2] + buf[3])
                    ((FnV44)g_vfn(y, 0x44))(y, buf[0], buf[1], buf[2],
                                            buf[3], buf[4], buf[5]);
            }
        }
        g3 = y;
        prevG2 = g2;
        prevG3 = g3;
    }

    base->FUN_00b0e890();
    if (g3) vcall0<void>(g3, 0x4);
    if (g2) vcall0<void>(g2, 0x5c);
}

// @ 0x00b0ee10
// Walks the +0x44 slot vector from `start_`, skipping one live slot per unit of
// budget; when the budget runs out it flags the selected agent's interactions
// and returns the budget, otherwise it returns -1.
int cRenderQueue::FUN_00b0ee10(int start_)
{
    RenderQueueView* q = (RenderQueueView*)this;
    SlotVector* va = &q->mVecA;   // +0x44

    int budget;                       // decremented as live slots are consumed
    if (start_ == -1)
        budget = 0;
    else
    {
        budget = start_ + 1;
        if (FUN_00b0d010(va->beginSlot(), va->mpSlotsEnd, start_) <= start_ + 1)
            budget = 0;
    }
    int ret = budget;                 // stored back into the result slot

    AgentBlocks lv = { 0, 0, 0, 0 };
    uint32_t    lvCur = 0x7f;
    uint32_t    lvIdx  = SlotVector::kNil;   // agent + 0x44
    uint32_t    lvIdx2 = SlotVector::kNil;   // agent + 0x48 (unused, kept for parity)

    uint8_t* it = va->beginSlot();
    uint8_t* vend = va->mpSlotsEnd;
    while (vend != it)
    {
        InteractionAgentView* agent = (InteractionAgentView*)((SlotEntry*)it)->mpData;
        ((cRenderQueue*)(void*)&lv)->FUN_00b0e780((int)((char*)agent + 0x2c));
        lvIdx  = *(uint32_t*)((char*)agent + 0x44);
        lvIdx2 = *(uint32_t*)((char*)agent + 0x48);
        if (lvIdx != SlotVector::kNil)
        {
            void* ref = ((SlotEntry*)((char*)lv.mpBegin[lvIdx >> 7]
                                      + (lvIdx & 0x7f) * 8))->mpData;
            if (ref != 0)
            {
                void* itf = vcall1<void*, int>(ref, 0x8, 0x1186577);
                if (itf != 0 && vcall0<char>(itf, 0x58) != 0)
                {
                    if (budget == 0) break;           // -> the "found" tail
                    --budget;
                }
            }
            ((void (__thiscall*)(void*, int))FUN_00abec70)(&lv, ret);
            lvIdx  = SlotVector::kNil;
            lvIdx2 = SlotVector::kNil;
        }
        (void)lvIdx2;

        do
        {
            uint32_t w = *(uint32_t*)it; it += 8;
            if (w & 0x40000000u) break;
        } while ((int)*(uint32_t*)it < 0);
    }

    if (budget == 0 && lvIdx != SlotVector::kNil)
    {
        vcall0<void>(FUN_00b30d70(), 0x64);

        SlotIter iter;
        iter.mpOwner = &lv;
        iter.mIndex  = lvIdx;
        if (iter.mIndex >= SlotVector::kNil)
            iter.mIndex = (uint32_t)(((char*)lv.mpEnd - (char*)lv.mpBegin) >> 2) * 0x80
                          - 0x7f + lvCur;
        for (;;)
        {
            uint32_t endIdx = (uint32_t)(((char*)lv.mpEnd - (char*)lv.mpBegin) >> 2) * 0x80
                              - 0x7f + lvCur;
            if (iter.mIndex == endIdx) break;
            void* ref = ((SlotEntry*)((char*)lv.mpBegin[iter.mIndex >> 7]
                                      + (iter.mIndex & 0x7f) * 8))->mpData;
            if (ref != 0)
            {
                void* itf = vcall1<void*, int>(ref, 0x8, 0x1186577);
                if (itf != 0 && vcall0<char>(itf, 0x58) != 0)
                    vcall1<void, int>(itf, 0x54, 1);
            }
            ((void (__thiscall*)(void*))FUN_00abe9b0)(&iter);
        }
    }
    else
        ret = -1;

    vcall0<void>(FUN_00b30d70(), 0x74);
    ((void (__thiscall*)(void*, int))FUN_00abec70)(&lv, ret);
    if (lv.mpBegin)
        destructor_00f47380(lv.mpBegin);
    return ret;
}