// Property variant setters, EASTL pointer-vector insert, member-function-pointer call thunks
// and a behavior-message handler. Built unoptimized: /Od /Ob1 /MD /Gy /EHsc /TP.
#include "types.h"

typedef unsigned int uint;

void  __cdecl EASTL_allocator_deallocate(void* p);                       // 0xF47380
void* __cdecl AllocatorAllocate(void* alloc, uint size, uint align, uint offset);   // 0x42DEE0

// ---------------------------------------------------------------------------
// Variant: 16 bytes payload, flags word at +0x10, type id at +0x12.
// ---------------------------------------------------------------------------
struct Variant {
    uint32_t data[4];
    uint16_t flags;      // 2 = owns/typed, 4 = needs clear
    uint16_t type;

    void __thiscall Clear(int full);                                                    // 0x93DB80
    void __thiscall Set(int type, int flags, const void* src, int elemSize, int count); // 0x93DD80

    Variant() : flags(0), type(0) {}
    inline Variant(const bool* v);
    ~Variant() { if (flags & 4) Clear(0); }
    void __thiscall SetBool(const bool* v);         // 0x422E20
    Variant* __thiscall SetInt(const int* v);       // 0x427FD0
    Variant* __thiscall SetFloat(const float* v);   // 0x428060
};

static const bool kTrue = true;   // compile-time constant condition kept by /Od

// @ 0x00427FD0
Variant* __thiscall Variant::SetInt(const int* v)
{
    if (flags & 4)
        Clear(1);
    if (kTrue && (!(flags & 2) || type == 10)) {
        *(int*)this = *v;
        type = 10;
        flags = flags & 2;
    } else {
        Set(10, 0, v, 4, 1);
    }
    return this;
}

// @ 0x00428060
Variant* __thiscall Variant::SetFloat(const float* v)
{
    if (flags & 4)
        Clear(1);
    if (kTrue && (!(flags & 2) || type == 13)) {
        *(float*)this = *v;
        type = 13;
        flags = flags & 2;
    } else {
        Set(13, 0, v, 4, 1);
    }
    return this;
}

// ---------------------------------------------------------------------------
// Member-function-pointer call thunks: (obj->*pm)(arg)
// ---------------------------------------------------------------------------
struct HandlerBaseA { virtual void a(); };
struct HandlerBaseB { virtual void b(); };
struct HandlerA : HandlerBaseA, HandlerBaseB { void __thiscall Run(int arg); };   // 0x40AEB0
struct HandlerB : HandlerBaseA, HandlerBaseB { void __thiscall Run(int arg); };   // 0x40E5B0
struct HandlerC : HandlerBaseA, HandlerBaseB {
    uint32_t pad;
    bool     mFired;     // +0xC
    bool __thiscall Run(int arg);   // 0x428450
};
struct IRef { virtual void v0(); virtual void Release(); };

// Intrusive reference holder: operator-> is inline (its result is spilled at /Od).
template<class T> struct Ref {
    T* mPtr;
    Ref() : mPtr(0) {}
    T* operator->() const { return mPtr; }
    T** __thiscall OutImpl();                // 0x41D870 (out-parameter accessor)
    T** Out() { return OutImpl(); }
    ~Ref() { if (mPtr) mPtr->Release(); }
};

struct IPropertyList : IRef {
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, const void* value);   // +0x14 (takes Variant*/info)
};
struct IPropertyInfo { char pad[0x12]; uint16_t type; };
struct IPropertySource : IRef {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual IPropertyInfo* GetInfo(uint32_t id);                 // +0x28
};
struct IService {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool Resolve(uint32_t a, uint32_t b, void* out);     // +0x2c
};
struct IMessageBus {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Send(uint32_t id, const void* msg, int flags);  // +0x14
};
IService*    __cdecl GetService();       // 0x67DE30
IMessageBus* __cdecl GetMessageBus();    // 0x67DCC0
bool         __cdecl GetArrayProperty(IPropertyList* list, uint32_t id, int* count, int** data);  // 0x6A07D0

// Message object posted on the bus. The root (0x40FD50) is constructed out of line; the parameter
// block (entries of 8 bytes at +0, message id at +0x28) is an inline base constructed first.
struct ParamEntry { uint32_t value; uint32_t tag; };
struct ParamBlock {
    ParamEntry entry[5];    // 8-byte entries; only the first dword of each is written here
    uint32_t id;            // +0x28
    uint32_t tail;          // +0x2C
    ParamBlock() { id = 0xF62DEF; }
    inline void SetParam(int index, uint32_t v) { entry[index].value = v; }
};
struct MessageRoot { uint32_t rootField; MessageRoot(); virtual void r0(); };            // 0x40FD50
struct BehaviorMessageBase : MessageRoot { virtual void r1(); };     // vtable 0x13EB90C
struct ParamMessage : ParamBlock, BehaviorMessageBase {
    uint32_t extra;
    ParamMessage() { extra = 0; }
    virtual void r2();
};
void __fastcall DestroyMessage(ParamMessage* m);   // 0x421CF0

struct HandlerD : HandlerBaseA, HandlerBaseB {
    uint32_t pad[2];
    uint32_t mObject;      // +0x10
    uint32_t mKind;        // +0x14
    bool __thiscall Run(int arg);   // 0x4284D0
};
struct HandlerE : HandlerBaseA, HandlerBaseB { void __thiscall Run(int arg); };   // 0x4143E0

// @ 0x004280F0
void __cdecl CallHandlerA(int arg, HandlerA* obj)
{
    void (__thiscall HandlerA::*pm)(int) = &HandlerA::Run;
    (obj->*pm)(arg);
}

// @ 0x00428190
void __cdecl CallHandlerB(int arg, HandlerB* obj)
{
    void (__thiscall HandlerB::*pm)(int) = &HandlerB::Run;
    (obj->*pm)(arg);
}

// @ 0x00428410
void __cdecl CallHandlerC(int arg, HandlerC* obj)
{
    bool (__thiscall HandlerC::*pm)(int) = &HandlerC::Run;
    (obj->*pm)(arg);
}

// @ 0x00428490
void __cdecl CallHandlerD(int arg, HandlerD* obj)
{
    bool (__thiscall HandlerD::*pm)(int) = &HandlerD::Run;
    (obj->*pm)(arg);
}

// @ 0x004288C0
void __cdecl CallHandlerE(int arg, HandlerE* obj)
{
    void (__thiscall HandlerE::*pm)(int) = &HandlerE::Run;
    (obj->*pm)(arg);
}

// ---------------------------------------------------------------------------
// Vector of 48-byte elements: deallocate storage (no element dtors)
// ---------------------------------------------------------------------------
struct Elem48 { char b[0x30]; };
struct Vector48 {
    Elem48* mBegin;
    Elem48* mEnd;
    Elem48* mCapEnd;
    uint32_t mAllocator;
    Elem48* mInline;
};

// @ 0x00428130
void __fastcall Vector48_Free(Vector48* v)
{
    void* q;
    if (v->mBegin) {
        int bytes = ((char*)v->mCapEnd - (char*)v->mBegin) / 0x30 * 0x30;
        void* p = v->mBegin;
        if (p != v->mInline) {
            q = p;
            EASTL_allocator_deallocate(q);
        }
    }
}

// ---------------------------------------------------------------------------
// vector<uint32_t>::insert(pos, value) for a trivially copyable 4-byte element, with a
// fixed overflow buffer at +0x10 (fixed_vector style). The EASTL helpers (move_backward,
// uninitialized_copy and the trivial-copy dispatch) are spelled out as inline functions;
// their bool locals mirror the dispatch tags the original expands.
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, uint);
extern "C" void* __cdecl memcpy(void*, const void*, uint);
#pragma intrinsic(memcpy)

inline void* operator new(unsigned int, void* p) { return p; }

inline uint32_t* MoveBackward(uint32_t* first, uint32_t* last, uint32_t* result)
{
    bool pNext; bool tag = false; pNext = false; bool copyable2 = true;
    memmove(result - (last - first), first, (char*)last - (char*)first);
    return result - (last - first);
}
inline uint32_t* CopyTrivial(uint32_t* first, uint32_t* last, uint32_t* result)
{
    bool cur = true;
    return (uint32_t*)memcpy(result, first, (char*)last - (char*)first) + (last - first);
}
inline void MarkTrivial() { bool isTrivial = true; }
inline uint32_t* UninitCopy(uint32_t* first, uint32_t* last, uint32_t* result)
{
    uint32_t* t = CopyTrivial(first, last, result);
    MarkTrivial();
    return t;
}

struct PtrVector {
    uint32_t* mBegin;
    uint32_t* mEnd;
    uint32_t* mCapEnd;
    uint32_t  mAllocator;
    uint32_t* mInline;

    void __thiscall Insert(uint32_t* pos, const uint32_t* value);   // 0x4281D0
    inline void __thiscall Free(uint32_t* old, uint cnt);
};

void __thiscall PtrVector::Free(uint32_t* old, uint bb)
{
    if (old && old != mInline) {
        void* w = old;
        EASTL_allocator_deallocate(w);
    }
}

// @ 0x004281D0
void __thiscall PtrVector::Insert(uint32_t* pos, const uint32_t* value)
{
    if (mEnd != mCapEnd) {
        const uint32_t* src = value;
        if (src >= pos && src < mEnd)
            ++src;
        new (mEnd) uint32_t(*(mEnd - 1));
        MoveBackward(pos, mEnd - 1, mEnd);
        *pos = *src;
        ++mEnd;
    } else {
        uint b = mEnd - mBegin;
        uint aa = b > 0 ? b * 2 : 1;
        uint32_t* ret = aa ? (uint32_t*)AllocatorAllocate(&mAllocator, aa * 4, 4, 0) : 0;
        uint32_t* i = UninitCopy(mBegin, pos, ret);
        new (i) uint32_t(*value);
        ++i;
        i = UninitCopy(pos, mEnd, i);
        Free(mBegin, mCapEnd - mBegin);
        mBegin = ret;
        mEnd = i;
        mCapEnd = ret + aa;
    }
}


// ---------------------------------------------------------------------------
// Handler bodies
// ---------------------------------------------------------------------------
static const uint32_t kBehaviorMsgId = 0xF62DEF;

inline uint32_t SetByte1(uint32_t v, unsigned char b)
{
    v = ((b & 0xFF) << 8) | (v & 0xFFFF00FF);
    return v;
}

inline Variant::Variant(const bool* v)
{
    flags = 0;
    type = 0;
    type = 1;
    flags = 2;
    SetBool(v);
}

// @ 0x00428450
bool __thiscall HandlerC::Run(int)
{
    mFired = true;
    GetMessageBus()->Send(0x29D3C4C, 0, 0);
    return true;
}

// @ 0x004284D0
bool __thiscall HandlerD::Run(int)
{
    Ref<IPropertyList> list;
    Ref<IPropertySource> source;
    uint32_t key = SetByte1(mKind, 0x71);

    if (GetService()->Resolve(mObject, mKind, list.Out())) {
        if (GetService()->Resolve(mObject, key, source.Out())) {
            IPropertyInfo* info = source->GetInfo(0xF9EFBB);
            if (info->type == 0x20)
                list->SetProperty(0xF9EFC1, info);
            bool one = true;
            list->SetProperty(0x3704E56, &Variant(&one));
            int count;
            int* data;
            if (!GetArrayProperty(list.operator->(), 0x60CBBEF, &count, &data)) {
                count = 0;
                data = 0;
            }
            if (count > 5)
                count = 5;
            uint32_t arr[6];
            uint i;
            for (i = 0; (int)i < count; ++i)
                arr[i] = data[i];
            for (; i < 6; ++i)
                arr[i] = 0xFFFFFFFF;
            arr[5] = arr[0];
            Variant arrVar;
            if (kTrue)
                arrVar.Set(9, (uint16_t)0x80 | 0x10 | 8, arr, 4, 6);
            else
                arrVar.Set(9, (uint16_t)0x80 | 0x20, arr, 4, 6);
            list->SetProperty(0x60CBBEF, &arrVar);

            ParamMessage msg;
            msg.SetParam(0, 0xB1B104);
            msg.SetParam(1, mKind);
            msg.SetParam(2, mObject);
            GetMessageBus()->Send(kBehaviorMsgId, &msg, 0);
            DestroyMessage(&msg);
        }
    }
    return true;
}
