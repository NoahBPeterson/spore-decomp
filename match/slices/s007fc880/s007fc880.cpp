// slice s007fc880 — /Od /Ob1 module: UI::BehaviorMessage + cSPUIBehaviorEventBase helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include <cstddef>
#include "types.h"

// ---------------------------------------------------------------------------
// Layout / vtable stubs.
// Relocations are masked, so only slot *indices* matter, not vtable contents.
// ---------------------------------------------------------------------------
struct PredBase;
struct Cont;

// generic thiscall vtable helpers (mirror the original's `mov eax,[o];
// mov edx,[eax+off]; call edx` schedule)
inline void* VCallR(void* o, int off) {
    return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline bool VCallB(void* o, int off) {
    return ((bool(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline int VCallI(void* o, int off) {
    return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCallV(void* o, int off) {
    ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
// slot call that also takes a class id on the stack (0x007fd34d pushes $0x2439c2f; the callee
// pops it, so it is a normal thiscall argument)
inline void* VCallR1(void* o, int off, int id) {
    return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, id);
}
inline void VCall1(void* o, int off, void* a) {
    ((void(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)o + off)))(o, a);
}
inline void VCall2(void* o, int off, void* a, void* b) {
    ((void(__thiscall*)(void*, void*, void*))(*(void**)((char*)*(void**)o + off)))(o, a, b);
}

// the +0x10 sub-object of cSPUIBehaviorEventBase used by this region
struct Ev {
    char pad0[8];
    void* iface;                    // +0x8  (Iface at Cont+0x18)
    char pad1[0x40];                // +0xc .. +0x4b
    bool mbActive;                  // +0x4c (Cont+0x5c)
    char pad2[0x1b];                // +0x4d .. +0x67
    void* handle;                   // +0x68 (AutoRefCount window)
    unsigned BaseHandle(void* msg, void* arg);   // @ 0x007fc4b0
    bool HandleBase(int msg, void* arg);          // @ 0x007fcf00
    bool Dispatch(int msg, void* arg);            // @ 0x007fc880
    void** SlotB(int i);                          // 0x007f93b0
    void** SlotC(int i);                          // 0x007f93c0
    void** SlotD(int i);                          // 0x007f93d0
};

struct Cont {
    char pad0[0x10];
    void** SlotC(int i);
    void** SlotD(int i);
    unsigned BaseHandle(void* msg, void* arg);
};

struct Server {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
};

// ---- externs (only names/conventions matter; relocations are masked) ----
Server* GetServer();                                  // @ 0x00883860
void* f_7fa4c0(void* p, int v);                       // @ 0x007fa4c0
unsigned f_883870(void*);
void* f_5701b0(void* a, void* b, void* c, unsigned d); // hash find
void  f_50e200(void* p);                              // hash free node
void  f_56f3e0(void* a, void* b);                     // hash lookup
void  f_571d10(void* p, int n);                       // deallocate
void* f_42dee0(void* alloc, int n, int align, int flag); // allocate
void* f_8ac360(int n, void* p);                       // allocate raw
void* f_7fbdb0(void* begin, void* end, void* out);    // uninitialized copy
void* f_7f53c0(void* p);                              // base pointer accessor
void  f_7fcff0(void* p);                              // refcount release
void  f_7fd140(void* p);                              // refcount add

// ===========================================================================
// Byte-exact candidates
// ===========================================================================

// ---------------------------------------------------------------------------
// UI::BehaviorMessage factory used by the event subsystem.
// ---------------------------------------------------------------------------
struct BehaviorMessage { char pad[0x48]; BehaviorMessage(); };
void* operator new(size_t, const char*, int, int, int, int);

// @ 0x007fcc40
void Factory(BehaviorMessage** out, int arg) {
    *out = new ("UI/BehaviorMessage", 0, 0, 0, 0) BehaviorMessage();
    f_7fa4c0(*out, arg);
}

// @ 0x007fcf00
bool Ev::HandleBase(int msg, void* arg) {
    BaseHandle((void*)msg, arg);
    if (msg == 0xc) {
        Server* from = GetServer();
        VCallV(from, 0x38);
    }
    return false;
}

// ---------------------------------------------------------------------------
// Bit-flag setter (cSPUIBehaviorActionBase-like, field at +0x10).
// ---------------------------------------------------------------------------
struct FlagObj {
    char pad0[0x10];
    unsigned mFlags;        // +0x10
    char pad1[0x24];        // +0x14 .. +0x37
    void* mpOwner;          // +0x38
    void SetFlag(unsigned mask, bool on);   // @ 0x007fd200
};

// @ 0x007fd200
void FlagObj::SetFlag(unsigned mask, bool on) {
    unsigned old = mFlags;
    unsigned nv = old & ~mask;
    if (on)
        nv |= mask;
    if (old == nv)
        return;
    mFlags = nv;
    void* p;
    if (mpOwner == 0)
        p = 0;
    else
        p = VCallR(mpOwner, 0x1c);
    if (p != 0 && ((old ^ nv) & 1) != 0 && VCallB(mpOwner, 0x54)) {
        if ((mFlags & 1) == 0)
            f_7fcff0(p);
        else
            f_7fd140(p);
    }
}

// ---------------------------------------------------------------------------
// Serialization read helper (SerItem buffer).
// ---------------------------------------------------------------------------
struct SerBuffer {
    void* type;      // +0
    void* base;      // +4
    unsigned count;  // +8
};
struct SerItem {
    void* type;      // +0
    void* base;      // +4
    unsigned count;  // +8
    void* extra;     // +0xc
};
struct SerItem14 {
    char pad[0x14];
    unsigned count;  // +0x14
};
struct C53 {
    char pad0[4];
    unsigned off;
    void* M(SerItem14* item);
};
extern char g_ser_type_7fd430[];

// @ 0x007fd430
bool ReadSerItem(SerBuffer* p, C53* self, SerItem14* item) {
    p->type = g_ser_type_7fd430;
    p->base = self->M(item);
    p->count = item->count;
    return true;
}

// @ 0x007fd390
bool WriteSerItem(SerBuffer* p, C53* self, SerItem14* item, void* alloc) {
    void* begin = self->M(item);
    void* dst = (void*)((void*(__thiscall*)(void*, int, int))VCallR(alloc, 0))(alloc, item->count << 2, 4);
    if (dst == 0)
        return false;
    p->base = dst;
    p->count = item->count;
    p->type = g_ser_type_7fd430;
    void* s = begin;
    void* d = dst;
    for (unsigned i = 0; i < item->count; ++i) {
        *(void**)d = *(void**)s;
        s = (char*)s + 4;
        d = (char*)d + 4;
    }
    return true;
}

// ---------------------------------------------------------------------------
// EASTL vector<{int,int}> insert helpers.
// ---------------------------------------------------------------------------
struct Vec8 {
    void* b; void* e; void* c; void* alloc;
    void* Insert(void* pos, void* value);
    void* Emplace(void* pos, void* value);
};

// @ 0x007fcf40
void* Vec8::Emplace(void* pos, void* value) {
    void** self = (void**)this;
    void* begin = *self;
    int idx = ((char*)pos - (char*)begin) >> 3;
    if (pos == self[1] && self[1] != self[2]) {
        void* slot = self[1];
        self[1] = (char*)self[1] + 8;
        void* m = f_8ac360(8, slot);
        if (m) {
            *(void**)m = *(void**)value;
            *((void**)m + 1) = *((void**)value + 1);
        }
    } else {
        Insert(pos, value);
    }
    return (char*)*self + idx * 8;
}

// @ 0x007fcca0
void* Vec8::Insert(void* pos, void* value) {
    void** self = (void**)this;
    if (self[1] == self[2]) {
        int cap = (int)(((char*)self[1] - (char*)*self) >> 3);
        int ncap = cap > 0 ? cap << 1 : 1;
        void* nd = ncap ? f_42dee0(self + 3, ncap << 3, 4, 0) : 0;
        void* at = f_7fbdb0(*self, pos, nd);
        void* m = f_8ac360(8, at);
        if (m) {
            *(void**)m = *(void**)value;
            *((void**)m + 1) = *((void**)value + 1);
        }
        at = f_7fbdb0(pos, self[1], (char*)at + 8);
        if (*self)
            f_571d10(*self, (int)(((char*)self[2] - (char*)*self) >> 3) << 3);
        *self = nd;
        self[1] = at;
        self[2] = (char*)nd + (ncap << 3);
        return at;
    }
    void* at = value;
    if (pos <= value && value < self[1])
        at = (char*)value + 8;
    void* m = f_8ac360(8, self[1]);
    if (m) {
        *(void**)m = *((void**)self[1] - 2);
        *((void**)m + 1) = *((void**)self[1] - 1);
    }
    void* cur = self[1];
    void* prev = (char*)self[1] - 8;
    while (prev != pos) {
        *((void**)cur - 2) = *((void**)prev - 2);
        *((void**)cur - 1) = *((void**)prev - 1);
        cur = (char*)cur - 8;
        prev = (char*)prev - 8;
    }
    *(void**)pos = *(void**)at;
    *((void**)pos + 1) = *((void**)at + 1);
    self[1] = (char*)self[1] + 8;
    return 0;
}

// ---------------------------------------------------------------------------
// EASTL hashtable find_or_insert (node holds refcount at +4).
// ---------------------------------------------------------------------------
// @ 0x007fd090
void** MapFindInsert(void** self, void** out, unsigned* key) {
    unsigned* found = (unsigned*)f_5701b0(*self, self[1], key, *(unsigned char*)(self + 5));
    if (found == (unsigned*)self[1] || *key < *found) {
        *out = ((Vec8*)0)->Emplace(found, key);
        *((unsigned char*)out + 4) = 1;
    } else {
        *out = found;
        *((unsigned char*)out + 4) = 0;
    }
    return out;
}

// @ 0x007fcff0
void RefCountRelease(void* p) {
    if (p == 0)
        return;
    void* node;
    f_56f3e0(&node, &p);
    void* n = (node == 0) ? 0 : node;
    if (n != 0 && (*(int*)((char*)n + 4) = *(int*)((char*)n + 4) - 1, *(int*)((char*)n + 4) == 0)) {
        VCallV(p, 0xa0);
        f_50e200(n);
        VCallV(p, 4);
    }
}

// @ 0x007fd140
void RefCountAdd(void* p) {
    if (p == 0)
        return;
    int c = 1;
    void* node;
    f_56f3e0(&node, &p);
    void* n = (node == 0) ? 0 : node;
    if (n == 0) {
        void* v = p;
        int cc = c;
        unsigned char res[8];
        MapFindInsert((void**)0, (void**)res, (unsigned*)&v);
        VCallV(p, 0);
    } else {
        *(int*)((char*)n + 4) = *(int*)((char*)n + 4) + 1;
        c = *(int*)((char*)n + 4);
    }
    if (c == 1)
        VCallV(p, 0x9c);
}

// ---------------------------------------------------------------------------
// vector copy helper.
// ---------------------------------------------------------------------------
struct VecSrc {
    char pad0[4];
    void** begin;   // +4
    void** end;     // +8
};
struct VecHit {
    void* p;        // +0
    unsigned char inserted;  // +4
};

// The element span and the element count live in two different objects: 0x007f53c0 returns
// owner->[4] + list->[0x10] (thiscall, `ret $4`), and the loop bound is list->[0x14].
struct VecElemList {
    char pad0[0x10];
    void*    mpBase;    // +0x10
    unsigned mCount;    // +0x14
};
struct VecOwner {
    char pad0[4];
    void** mpBegin;     // +4
    void** Elements(VecElemList* list);   // 0x007f53c0
};

// @ 0x007fd2d0
bool __cdecl Vec8CopyFrom(VecOwner* owner, VecSrc* src, VecElemList* list) {
    void** d = src->begin;
    void** s = owner->Elements(list);
    for (unsigned i = 0; i < list->mCount; ++i) {
        void* created = 0;
        void* old = *s;
        if (old)
            VCallV(old, 4);
        void* slot = *d;
        if (slot) {
            created = VCallR1(slot, 0xc, 0x2439c2f);
            if (created)
                VCallV(created, 0);
        }
        *s = created;
        ++s;
        ++d;
    }
    return true;
}

// ===========================================================================
// BehaviorMessage dispatch (this points 0x10 into the event base).
// ===========================================================================

struct DispIface;
struct DispReceiver {
    virtual void v0();
    virtual void OnMessage(int msg, void* arg);                // +0x04
};
struct DispSlot {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool IsActive();                                   // +0x18
    virtual void v1c();
    virtual int GetFlags();                                    // +0x20
    virtual void v24();
    virtual void Detach(DispIface* iface);                     // +0x28
    virtual DispReceiver* GetReceiver();                       // +0x2c
    virtual void Attach(DispIface* iface);                     // +0x30
};
struct DispIface {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38();
    virtual void SetActive(int v);                             // +0x3c
};
struct DispCont {
    char pad0[0x10];
    DispSlot** SlotC(int i);        // 0x007f93c0
    DispSlot** SlotD(int i);        // 0x007f93d0
};
struct DispHandleObj {
    virtual int AddRef();                                      // +0x00
    virtual int Release();                                     // +0x04
};
template <class T>
struct DispARC {
    T* mpObject;
    DispARC& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
#define DISP_CONT() ((DispCont*)((char*)this - 0x10))
#define DISP_IFACE() (DISP_CONT() ? (DispIface*)((char*)DISP_CONT() + 0x18) : (DispIface*)0)

struct EvD {
    char pad0[8];
    char pad1[0x44];                // +0x8 .. +0x4b
    bool mbActive;                  // +0x4c
    char pad2[0x1b];                // +0x4d .. +0x67
    DispARC<DispHandleObj> mHandle; // +0x68
    unsigned BaseHandle(int msg, void* arg);   // @ 0x007fc4b0
    bool Dispatch(int msg, void* arg);         // @ 0x007fc880
};

// @ 0x007fc880
bool EvD::Dispatch(int msg, void* arg) {
    BaseHandle(msg, arg);
    switch (msg) {
    case 0x11:
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotC(i) != 0)
                (*DISP_CONT()->SlotC(i))->Attach(DISP_IFACE());
        }
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotD(i) != 0)
                (*DISP_CONT()->SlotD(i))->Detach(DISP_IFACE());
        }
        break;
    case 0x12:
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotC(i) != 0)
                (*DISP_CONT()->SlotC(i))->Attach(0);
        }
        for (int i = 0; i < 4; ++i) {
            if (*DISP_CONT()->SlotD(i) != 0)
                (*DISP_CONT()->SlotD(i))->Detach(0);
        }
        mHandle = 0;
        break;
    case 0xc:
        if (mbActive) {
            int cnt = 0;
            for (int i = 0; i < 4; ++i) {
                DispSlot** slot = DISP_CONT()->SlotD(i);
                if (*slot != 0 && (*slot)->IsActive()) {
                    ++cnt;
                    if ((*slot)->IsActive() && ((*slot)->GetFlags() & 0x80)) {
                        DispReceiver* o = (*slot)->GetReceiver();
                        if (o != 0)
                            o->OnMessage(msg, arg);
                    }
                }
            }
            if (cnt == 0)
                ((DispIface*)((char*)this + 8))->SetActive(0);
        }
        break;
    case 0x15:
        if (mbActive) {
            for (int i = 0; i < 4; ++i) {
                DispSlot** slot = DISP_CONT()->SlotD(i);
                if (*slot != 0 && ((*slot)->GetFlags() & 0x100)) {
                    DispReceiver* o = (*slot)->GetReceiver();
                    if (o != 0)
                        o->OnMessage(msg, arg);
                }
            }
        }
        break;
    }
    return false;
}
