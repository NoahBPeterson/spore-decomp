// slice s00bca040 -- Spore cAgentOrder / cAgentOrderManager (agent-order queue).
//
// Compile: /O2 /MD /Gy /EHsc /TP
//
// The order record is 0x88 bytes; in the manager's slot array the stride is
// 0x44 (the low 0x44 bytes are copied and the rest lives in the queue node).
// The manager's slot array overlaps with a block of 8 intrusive-list nodes
// (stride 0x38) that the destructor walks at this+0x34+0x38*i -- see
// cAgentOrderManager::~cAgentOrderManager for the union overlay used to
// reproduce the original bytes exactly.

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

struct cGonzagoTimer;                 // sizeof 0x20
struct IRefCount;
struct cOutStream;
struct cSerializer;

// ---- cGonzagoTimer ---------------------------------------------------------
struct cGonzagoTimer {
    void* mVtbl;   // +0x00
    int   m04;     // +0x04
    int   m08;     // +0x08
    int   m0c;     // +0x0c
    int   m10;     // +0x10
    int   m14;     // +0x14
    char  m18;     // +0x18
    int   m1c;     // +0x1c
};
void cGonzagoTimer_ctor(cGonzagoTimer* t);   // @ 0x00b63890
void cGonzagoTimer_dtor(cGonzagoTimer* t);   // @ 0x00b638b0

// ---- IRefCount -------------------------------------------------------------
struct IRefCount {
    virtual void AddRef();                      // vtbl+0x00
    virtual void Release();                     // vtbl+0x04
    virtual void vtbl08();                      // vtbl+0x08
    virtual void* QueryInterface(unsigned id);  // vtbl+0x0c
    virtual void vtbl1c(void* a);               // vtbl+0x1c
    virtual void vtbl20();
    virtual int  vtbl2c();                      // vtbl+0x2c
};

// Minimal 12-slot vtable used for thiscall dispatch at vtbl+0x2c.
struct IVtbl2c {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(void*);
};

// ---- cAgentOrder -----------------------------------------------------------
// Layout recovered from the machine code:
//   +0x00 int              mId
//   +0x08 cGonzagoTimer    mTimer
//   +0x28 IRefCount*       mSource
//   +0x2c float            mTimeLeft
//   +0x30 float            mF1
//   +0x34 float            mF2
//   +0x38 char             mFlag
//   four EA::Variant (size 0x14) whose 16-byte payloads start at
//   0x39 / 0x4d / 0x61 / 0x75 and whose tag shorts are at
//   0x49/0x4b / 0x5d/0x5f / 0x71/0x73 / 0x85/0x87 -- i.e. an unaligned overlay.
//   Emulated with byte accessors below.
struct cAgentOrder {
    int           mId;        // +0x00
    char          mPad04[4];  // +0x04
    cGonzagoTimer mTimer;     // +0x08
    IRefCount*    mSource;    // +0x28
    float         mTimeLeft;  // +0x2c
    float         mF1;        // +0x30
    float         mF2;        // +0x34
    char          mFlag;      // +0x38
    char          mVariant0[0x14];  // +0x39 .. payload 0x39, tags 0x49/0x4b
    char          mVariant1[0x14];  // +0x4d .. payload 0x4d, tags 0x5d/0x5f
    char          mVariant2[0x14];  // +0x61 .. payload 0x61, tags 0x71/0x73
    char          mVariant3[0x14];  // +0x75 .. payload 0x75, tags 0x85/0x87

    cAgentOrder();
    ~cAgentOrder();
    int  operator_eq(cAgentOrder const& o);
    cAgentOrder* Assign(cAgentOrder const& o);
    cAgentOrder* CopyConstruct(cAgentOrder const& o);
    char Serialize(cOutStream* s);
};

// ---- cAgentOrderManager ----------------------------------------------------
struct cAgentOrderManager {
    // slot record: stride 0x44, 8 slots, base == this
    struct Slot {
        int           mId;        // +0x00   (shifted: slot+0x20 id is at mId+0x20)
    };
    char            mSlots[0x220];       // +0x000  8 slots * 0x44
    void*           mTemplates;          // +0x220
    char            mPad224[8];
    u32             mActiveMask;         // +0x22c
    char            mPad230[0x3b8];
    void*           mArray;              // +0x5e8
    char            mPad5ec[0x14];
    IRefCount*      mSource;             // +0x600
    int             mSourceStamp;        // +0x604
    char            mPad608[4];
    // intrusive list 0: head at +0x60c, tail at +0x610, size at +0x614
    char*           mList0Head;          // +0x60c
    char*           mList0Tail;          // +0x610
    u32             mList0Size;          // +0x614
    char            mPad618[0x0c];
    char*           mFree0;              // +0x624
    char            mPad628[0x0c];
    char*           mList1Head;          // +0x634
    char*           mList1Tail;          // +0x638
    u32             mList1Size;          // +0x63c
    char            mPad640[0x0c];
    char*           mFree1;              // +0x64c
    char            mPad650[0x0c];
    char*           mArrayBegin;         // +0x65c
    char*           mArrayEnd;           // +0x664

    void  DeactivateSlot(int id);
    u32   FindSlot(int a, int b, int c, int d);
    int   IsSourceAtEnd();
    int   IsSourceEmpty();
    cAgentOrder* FirstPending();
    void  Tick(float dt);
    cAgentOrder* FindNode(int key, int (*pred)(void*, void*), void* ctx);
    u32   Activate(int tmplIdx, int type, IRefCount* p1,
                   float timeLeft, void* header, IRefCount* p2);
    void  SaveList2(cOutStream* s, char* list);
    void  FreeAll();
    void ReleaseNode(char** out, char* node);
    void  AllocNode();
    void  ClearList();
    void  AllocLink();
    void  DoInsertValues(char* pos, u32 n, void* val);
    ~cAgentOrderManager();
    void  PopFront();
    cAgentOrder* PushBack(void* a, IRefCount* b, char clear);
    void  ReleaseQueueObject(char* obj, u32 idx);
};

// cSerializer is only used for the SaveObject call in cAgentOrderManager::SaveList.
struct cSerializer {
    void SaveObject(void* obj, void* desc, void* name);   // @ 0x00695b40
};

// ---- externs ---------------------------------------------------------------
void  FUN_00bc8fa0(void*);                             // 0x00bc8fa0
void  FUN_0093db80(void*, int);                        // 0x0093db80 Variant::Destruct
void  FUN_00542b80(void*, void*);                      // 0x00542b80 Variant::operator=
void* FUN_00692f90(void*, void*, void*, unsigned);     // 0x00692f90 cVarListSerializer ctor
char  FUN_00692900(void*, void*);                      // 0x00692900 cVarListSerializer::Serialize
int   FUN_0093aa70(void*, unsigned*, int, int);        // 0x0093aa70 EA::IO::WriteUint32
void  FUN_00926640(void*);                             // 0x00926640 ~FixedAllocatorBase thunk
char  FUN_00926650(void*, void*, unsigned);            // 0x00926650 FixedAllocatorBase::AddCore
void* EAAllocate(unsigned, const char*, int, int, int, int); // 0x00f473a0
void  FUN_00f47380(void*);                             // 0x00f47380 operator delete
void* FUN_007f1890(void*, void*, void*, void*, void*); // 0x007f1890 UninitCopy16
void* FUN_00edba80(void*, void*, void*);               // 0x00edba80 eastl copy_backward
void  FUN_00898580(void*, void*, void*);               // 0x00898580 eastl fill
void  FUN_0088f820(void*, unsigned, void*, void*);     // 0x0088f820 eastl uninit_fill_n
void* FUN_00c7ea30(void*, void*, void*);               // 0x00c7ea30 memmove helper

extern float gFloatMax;      // 0x0146697c  3.4028235e38
extern float gZeroFloat;     // 0x01485378  0.0f
extern short gAgentOrderId;  // 0x0156d290
extern float gOrderDef0;     // 0x0168b580
extern float gOrderDef1;     // 0x0168b584
extern float gOrderDef2;     // 0x0168b588
extern wchar_t gNameAgentOrder[]; // 0x01466980 L"cAgentOrder"
extern char   gDescAgentOrder;    // 0x0156d2a8

// cdecl helpers used through function pointers / as callbacks.
void FUN_00bca670(void* p);                            // 0x00bca670
void FUN_00bca6a0(void* p);                            // 0x00bca6a0
void FUN_00bca6f0(void);                               // 0x00bca6f0
bool FUN_00bca7a0(void* ser, char* list);              // 0x00bca7a0
bool FUN_00bca7e0(void* a1, void** slot);              // 0x00bca7e0
bool FUN_00bca960(void* a1, void** slot);              // 0x00bca960
void FUN_00bca990(void* a1, char* list);               // 0x00bca990
int  FUN_00bcacb0(char* list, IRefCount* obj);         // 0x00bcacb0

// ===========================================================================
// @ 0x00bca040  cAgentOrderManager::DeactivateSlot(int)
void cAgentOrderManager::DeactivateSlot(int id)
{
    unsigned idx = (unsigned)id >> 16;
    char* slot = (char*)this + idx * 0x44;
    if (*(short*)(slot + 0x20) == (short)id && *(int*)(slot + 0x24) != -1) {
        void (*cb)(void*) = *(void(**)(void*))(slot + 0x34);
        if (cb != 0) {
            cb(slot);
        }
        *(int*)(slot + 0x24) = -1;

        IRefCount* r1 = *(IRefCount**)(slot + 0x3c);
        if (r1 != 0) {
            *(void**)(slot + 0x3c) = 0;
            r1->Release();
        }
        IRefCount* r2 = *(IRefCount**)(slot + 0x40);
        if (r2 != 0) {
            *(void**)(slot + 0x40) = 0;
            r2->Release();
        }
        *(u32*)((char*)this + 0x22c) &= ~(1u << idx);
    }
}

// ===========================================================================
// @ 0x00bca0c0  cAgentOrderManager::FindSlot(int,int,int,int)
u32 cAgentOrderManager::FindSlot(int a, int b, int c, int d)
{
    char* p = (char*)this + 0x28;
    u32 i = 0;
    do {
        if (*(int*)(p - 4) == a && *(int*)(p) == b &&
            (c == 0 || *(int*)(p + 0x14) == c) &&
            (d == 0 || *(int*)(p + 0x18) == d)) {
            return (u32)*(u16*)(p - 8) | (i << 16);
        }
        ++i;
        p += 0x44;
    } while (i < 8);
    return 0xffffffffu;
}

// ===========================================================================
// @ 0x00bca120  cAgentOrder::~cAgentOrder()
cAgentOrder::~cAgentOrder()
{
    char* self = (char*)this;
    if (self[0x85] & 4) {
        FUN_0093db80(self + 0x75, 0);
    }
    if (self[0x71] & 4) {
        FUN_0093db80(self + 0x61, 0);
    }
    if (self[0x5d] & 4) {
        FUN_0093db80(self + 0x4d, 0);
    }
    if (self[0x49] & 4) {
        FUN_0093db80(self + 0x39, 0);
    }
    if (mSource != 0) {
        mSource->Release();
    }
    cGonzagoTimer_dtor(&mTimer);
}

// ===========================================================================
// @ 0x00bca180  cAgentOrder::operator_eq(cAgentOrder const&)
int cAgentOrder::operator_eq(cAgentOrder const& o)
{
    char* a = (char*)this;
    char* b = (char*)&o;
    if (*(int*)a != *(int*)b) return 0;
    if (*(int*)(a + 0x28) != *(int*)(b + 0x28)) return 0;
    if (*(short*)(a + 0x4b) != *(short*)(b + 0x4b)) return 0;
    if (*(int*)(a + 0x39) != *(int*)(b + 0x39)) return 0;
    if (*(int*)(a + 0x3d) != *(int*)(b + 0x3d)) return 0;
    if (*(int*)(a + 0x41) != *(int*)(b + 0x41)) return 0;
    if (*(int*)(a + 0x45) != *(int*)(b + 0x45)) return 0;
    if (*(short*)(a + 0x5f) != *(short*)(b + 0x5f)) return 0;
    if (*(int*)(a + 0x4d) != *(int*)(b + 0x4d)) return 0;
    if (*(int*)(a + 0x51) != *(int*)(b + 0x51)) return 0;
    if (*(int*)(a + 0x55) != *(int*)(b + 0x55)) return 0;
    if (*(int*)(a + 0x59) != *(int*)(b + 0x59)) return 0;
    if (*(short*)(a + 0x73) != *(short*)(b + 0x73)) return 0;
    if (*(int*)(a + 0x61) != *(int*)(b + 0x61)) return 0;
    if (*(int*)(a + 0x65) != *(int*)(b + 0x65)) return 0;
    if (*(int*)(a + 0x69) != *(int*)(b + 0x69)) return 0;
    if (*(int*)(a + 0x6d) != *(int*)(b + 0x6d)) return 0;
    if (*(short*)(a + 0x87) != *(short*)(b + 0x87)) return 0;
    if (*(int*)(a + 0x75) != *(int*)(b + 0x75)) return 0;
    if (*(int*)(a + 0x79) != *(int*)(b + 0x79)) return 0;
    if (*(int*)(a + 0x7d) != *(int*)(b + 0x7d)) return 0;
    if (*(int*)(a + 0x81) != *(int*)(b + 0x81)) return 0;
    return 1;
}

// ===========================================================================
// @ 0x00bca280  cAgentOrderManager::IsSourceAtEnd()
int cAgentOrderManager::IsSourceAtEnd()
{
    IRefCount* s = mSource;
    if (s != 0 && *(int*)((char*)s + 0x14) == mSourceStamp) {
        return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00bca2a0  cAgentOrderManager::IsSourceEmpty()
int cAgentOrderManager::IsSourceEmpty()
{
    IRefCount* s = mSource;
    if (s != 0 && *(int*)((char*)s + 0x18) == *(int*)((char*)s + 0x10)) {
        return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00bca2c0  cAgentOrderManager::FirstPending()
cAgentOrder* cAgentOrderManager::FirstPending()
{
    char* head = (char*)this + 0x60c;
    if (*(char**)head != head) {
        return (cAgentOrder*)(*(char**)head + 8);
    }
    return 0;
}

// ===========================================================================
// @ 0x00bca350  cAgentOrderManager::Tick(float)
void cAgentOrderManager::Tick(float dt)
{
    u32 live = mActiveMask;
    if (live == 0) {
        return;
    }
    char* slot = (char*)this + 0x38;
    u32 i = 0;
    do {
        if (i >= 8) {
            return;
        }
        u32 bit = 1u << i;
        if (live & bit) {
            float v = *(float*)(slot - 0x0c) - dt;
            live &= ~bit;
            *(float*)(slot - 0x0c) = v;
            if (!(0.0f <= v)) {
                DeactivateSlot((int)(*(u16*)(slot - 0x18) | (i << 16)));
            } else {
                bool (*cb)(void*, float) = *(bool(**)(void*, float))(slot);
                if (cb != 0 && !cb(slot - 0x38, dt)) {
                    DeactivateSlot((int)(*(u16*)(slot - 0x18) | (i << 16)));
                }
            }
        }
        ++i;
        slot += 0x44;
    } while (live != 0);
}

// ===========================================================================
// @ 0x00bca3d0  cAgentOrder::Assign(cAgentOrder const&)   (returns this)
cAgentOrder* cAgentOrder::Assign(cAgentOrder const& o)
{
    char* dst = (char*)this;
    char* src = (char*)&o;
    u32* d = (u32*)dst;
    u32* s = (u32*)src;
    for (int i = 0; i < 8; ++i) {
        d[i] = s[i];
    }
    *(u16*)(dst + 0x20) = *(u16*)(src + 0x20);
    *(u32*)(dst + 0x24) = *(u32*)(src + 0x24);
    *(u32*)(dst + 0x28) = *(u32*)(src + 0x28);
    *(u32*)(dst + 0x2c) = *(u32*)(src + 0x2c);
    *(u32*)(dst + 0x30) = *(u32*)(src + 0x30);
    *(u32*)(dst + 0x34) = *(u32*)(src + 0x34);
    *(u32*)(dst + 0x38) = *(u32*)(src + 0x38);

    IRefCount* ns = *(IRefCount**)(src + 0x3c);
    IRefCount* os = *(IRefCount**)(dst + 0x3c);
    if (ns != os) {
        if (ns != 0) {
            ns->AddRef();
        }
        *(IRefCount**)(dst + 0x3c) = ns;
        if (os != 0) {
            os->Release();
        }
    }
    IRefCount* n2 = *(IRefCount**)(src + 0x40);
    IRefCount* o2 = *(IRefCount**)(dst + 0x40);
    if (n2 != o2) {
        if (n2 != 0) {
            n2->AddRef();
        }
        *(IRefCount**)(dst + 0x40) = n2;
        if (o2 != 0) {
            o2->Release();
        }
    }
    return this;
}

// ===========================================================================
// @ 0x00bca470  cAgentOrder::cAgentOrder()
cAgentOrder::cAgentOrder()
{
    mId = -1;
    cGonzagoTimer_ctor(&mTimer);
    mSource = 0;
    mTimeLeft = gOrderDef0;
    mF1 = gOrderDef1;
    mF2 = gOrderDef2;
    mFlag = 0;
    char* self = (char*)this;
    *(u16*)(self + 0x49) = 0;
    *(u16*)(self + 0x4b) = 0;
    *(u16*)(self + 0x5f) = 0;
    *(u16*)(self + 0x5d) = 0;
    *(u16*)(self + 0x71) = 0;
    *(u16*)(self + 0x73) = 0;
    *(u16*)(self + 0x85) = 0;
    *(u16*)(self + 0x87) = 0;
}

// ===========================================================================
// @ 0x00bca4e0  cAgentOrder::Serialize(cOutStream*)
char cAgentOrder::Serialize(cOutStream* stream)
{
    char pad[0xa14];
    (void)pad;
    IRefCount* keep = mSource;
    if (keep != 0) {
        keep->AddRef();
    }

    if (mSource != 0) {
        IRefCount* cur = mSource;
        int dropped = 0;
        if (cur != 0) {
            IRefCount* qi = (IRefCount*)cur->QueryInterface(0x17f243b);
            if (qi != 0 && qi->vtbl2c()) {
                if (cur != 0) {
                    mSource = 0;
                    cur->Release();
                }
                dropped = 1;
                if (keep != 0) {
                    keep->Release();
                }
                keep = 0;
            }
            if (!dropped) {
                cur = keep;
                if (cur == 0 || cur->QueryInterface(0x179c807) == 0) {
                    if (mSource != 0) {
                        mSource = 0;
                        if (cur != 0) {
                            cur->Release();
                        }
                    }
                }
            }
        }
    }

    char ser[0xa14];
    FUN_00692f90(ser, this, &gDescAgentOrder, 0x1a80d26);
    char ok = FUN_00692900(ser, stream);
    {
        IRefCount* old = mSource;
        if (keep != old) {
            if (keep != 0) {
                keep->AddRef();
            }
            mSource = keep;
            if (old != 0) {
                old->Release();
            }
        }
        if (keep != 0) {
            keep->Release();
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x00bca620  cAgentOrderManager::FindNode(int, pred, ctx)
cAgentOrder* cAgentOrderManager::FindNode(int key,
                                          int (*pred)(void*, void*), void* ctx)
{
    char* self = (char*)this;
    char* node = *(char**)self;
    while (node != self) {
        if (*(int*)(node + 0x10) == key && node[0x1c] == 0) {
            if (pred == 0 || pred(node + 8, ctx)) {
                return (cAgentOrder*)(node + 8);
            }
        }
        node = *(char**)node;
    }
    return 0;
}

// ===========================================================================
// @ 0x00bca670  (cdecl) source-changed callback
void FUN_00bca670(void* p)
{
    char* self = (char*)p;
    if (*(int*)(self + 0x2c) != 0 && *(char**)(self + 0x2c) != 0) {
        char* o = *(char**)(self + 0x2c);
        char* qi = (char*)((IRefCount*)o)->QueryInterface(0xce9f6639);
        if (qi != 0) {
            *(u32*)(self + 0x30) = *(u32*)(qi + 0xe54);
        }
    }
}

// ===========================================================================
// @ 0x00bca6a0  (cdecl) source-gone callback
void FUN_00bca6a0(void* p)
{
    char* self = (char*)p;
    if (*(int*)(self + 0x2c) != 0 && *(char**)(self + 0x2c) != 0) {
        char* o = *(char**)(self + 0x2c);
        char* qi = (char*)((IRefCount*)o)->QueryInterface(0xce9f6639);
        if (qi != 0) {
            if (*(u32*)(self + 0x30) != *(u32*)(qi + 0xe54)) {
                char* cur = *(char**)(self + 0x2c);
                if (cur != 0) {
                    *(u32*)(self + 0x2c) = 0;
                    ((IRefCount*)cur)->Release();
                }
                *(u32*)(self + 0x30) = 0;
            }
        }
    }
}

// ===========================================================================
// @ 0x00bca6f0  cAgentOrderManager::RegisterClassCallbacks()
void FUN_00bca6f0(void)
{
    *(void**)0x168b54c = (void*)&FUN_00bca670;
    *(void**)0x168b550 = (void*)&FUN_00bca6a0;
    FUN_00bc8fa0((void*)0x1590800);
    FUN_00bc8fa0((void*)0x1590888);
    FUN_00bc8fa0((void*)0x15906f0);
    FUN_00bc8fa0((void*)0x1590778);
    FUN_00bc8fa0((void*)0x1590910);
    FUN_00bc8fa0((void*)0x1590998);
    FUN_00bc8fa0((void*)0x1590a20);
    FUN_00bc8fa0((void*)0x1590aa8);
    FUN_00bc8fa0((void*)0x1590b30);
    FUN_00bc8fa0((void*)0x15aa9e8);
}

// ===========================================================================
// @ 0x00bca7a0  cAgentOrderManager::SaveList(list*, cSerializer*)
bool FUN_00bca7a0(void* ser, char* list)
{
    char* node = *(char**)list;
    while (node != list) {
        char* order = node + 8;
        if (order != 0) {
            ((cSerializer*)ser)->SaveObject(order, &gDescAgentOrder, gNameAgentOrder);
        }
        node = *(char**)node;
    }
    return true;
}

// ===========================================================================
// @ 0x00bca7e0  cAgentOrderManager::SaveListOne(cSerializer*, cAgentOrder**)
bool FUN_00bca7e0(void* a1, void** slot)
{
    void* obj = *slot;
    if (obj != 0) {
        IRefCount* qi = (IRefCount*)((IRefCount*)obj)->QueryInterface(0x179c807);
        if (qi != 0) {
            qi->vtbl1c(a1);
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00bca810  cAgentOrderManager::Activate(int,int,IRefCount*,float,void*,IRefCount*)
u32 cAgentOrderManager::Activate(int tmplIdx, int type, IRefCount* p1,
                                 float timeLeft, void* header, IRefCount* p2)
{
    float best = gFloatMax;
    u32 idx = 0;
    u32 chosen = 0;
    char* f = (char*)this + 0x2c;
    do {
        if (*(int*)(f - 8) == -1) {
            chosen = idx;
            break;
        }
        if (best >= *(float*)f) {
            best = *(float*)f;
            chosen = idx;
        }
        ++idx;
        f += 0x44;
    } while (idx < 8);

    char* slot = (char*)this + chosen * 0x44;
    DeactivateSlot((int)(*(u16*)((char*)this + 0x20 + chosen * 0x44) | (chosen << 16)));
    ((cAgentOrder*)slot)->Assign(
        *(cAgentOrder*)(*(char**)((char*)this + 0x220 + type * 4) + tmplIdx * 0x44));

    {
        IRefCount* old = *(IRefCount**)(slot + 0x3c);
        if (p1 != old) {
            if (p1 != 0) {
                p1->AddRef();
            }
            *(IRefCount**)(slot + 0x3c) = p1;
            if (old != 0) {
                old->Release();
            }
        }
    }
    *(u16*)(slot + 0x20) = gAgentOrderId;
    ++gAgentOrderId;
    *(int*)(slot + 0x28) = type;
    if (!(timeLeft == gZeroFloat)) {
        *(float*)(slot + 0x2c) = timeLeft;
    }
    if (header != 0) {
        u32* d = (u32*)slot;
        u32* s = (u32*)header;
        for (int i = 0; i < 8; ++i) {
            d[i] = s[i];
        }
    }
    {
        IRefCount* old = *(IRefCount**)(slot + 0x40);
        if (p2 != old) {
            if (p2 != 0) {
                p2->AddRef();
            }
            *(IRefCount**)(slot + 0x40) = p2;
            if (old != 0) {
                old->Release();
            }
        }
    }
    mActiveMask |= 1u << chosen;
    {
        void (*cb)(void*) = *(void(**)(void*))(slot + 0x30);
        if (cb != 0) {
            cb(slot);
        }
    }
    return (u32)*(u16*)(slot + 0x20) | (chosen << 16);
}

// ===========================================================================
// @ 0x00bca960  cAgentOrderManager::ActivateOne(cSerializer*, cAgentOrder**)
bool FUN_00bca960(void* a1, void** slot)
{
    void* o = 0;
    if (*slot != 0) {
        o = (void*)((IRefCount*)*slot)->QueryInterface(0x179c807);
    }
    ((IVtbl2c*)a1)->v2c(o);
    return true;
}

// ===========================================================================
// @ 0x00bca990  cAgentOrderManager::SaveList2(cOutStream*, list*)
void FUN_00bca990(void* a1, char* list)
{
    int n = 0;
    for (char* n2 = *(char**)list; n2 != list; n2 = *(char**)n2) {
        ++n;
    }
    void* s = (void*)(*(void*(**)(void*))(*(char**)a1 + 0x20))(a1);
    void* ws = (void*)(*(void*(**)(void*))(*(char**)s + 0x18))(s);
    FUN_0093aa70(ws, (unsigned*)&n, 1, 0);
    for (char* n2 = *(char**)list; n2 != list; n2 = *(char**)n2) {
        ((cAgentOrder*)(n2 + 8))->Serialize((cOutStream*)a1);
    }
    void (*fn)(void*) = *(void(**)(void*))(*(char**)a1 + 0x1c);
    fn(a1);
}

// ===========================================================================
// @ 0x00bcaa00  cAgentOrderManager::FreeAll()
void cAgentOrderManager::FreeAll()
{
    char* self = (char*)this;
    char* node = *(char**)self;
    while (node != self) {
        char* next = *(char**)node;
        *(void**)(node + 8) = (void*)0x1466998;
        IRefCount* r = *(IRefCount**)(node + 0x1a8);
        if (r != 0) {
            r->Release();
        }
        *(void**)(node + 8) = (void*)0x13ec458;
        *(void**)node = *(void**)(self + 0x18);
        *(void**)(self + 0x18) = node;
        node = next;
    }
}

// ===========================================================================
// @ 0x00bcaa50  cAgentOrderManager::ReleaseNode(list*, iterator*)
void cAgentOrderManager::ReleaseNode(char** out, char* node)
{
    char* self = (char*)this;
    char* next = *(char**)node;
    char* prev = *(char**)(node + 4);
    *(char**)prev = next;
    *(char**)(next + 4) = prev;

    *(void**)(node + 8) = (void*)0x1466998;
    IRefCount* r = *(IRefCount**)(node + 0x1a8);
    if (r != 0) {
        r->Release();
    }
    *(void**)(node + 8) = (void*)0x13ec458;
    *(void**)node = *(void**)((char*)self + 0x18);
    *(void**)((char*)self + 0x18) = node;
    *out = next;
}

// ===========================================================================
// @ 0x00bcaab0  cAgentOrderManager::AllocNode()
void cAgentOrderManager::AllocNode()
{
    char* esi = (char*)this + 8;
    char* p;
    for (;;) {
        if (*(char**)(esi + 0x10) != 0) {
            p = *(char**)(esi + 0x10);
            *(char**)(esi + 0x10) = *(char**)p;
            break;
        }
        if (!FUN_00926650(esi, 0, 0)) {
            p = 0;
            break;
        }
    }
    if (p != 0) {
        *(u32*)(p + 4) = 0;
        *(void**)p = (void*)0x1466998;
        *(u8*)(p + 0x1c) = 0;
        *(u32*)(p + 0x1a0) = 0;
        *(u32*)(p + 0x224) = 0;
        *(u32*)(p + 0x228) = 0;
    }
}

// ===========================================================================
// @ 0x00bcab00  cAgentOrderManager::ClearList()
void cAgentOrderManager::ClearList()
{
    char* self = (char*)this;
    char* node = *(char**)self;
    while (node != self) {
        char* esi = node;
        char* next = *(char**)node;
        node = next;
        if (esi[0x8d] & 4) {
            FUN_0093db80(esi + 0x7d, 0);
        }
        if (esi[0x79] & 4) {
            FUN_0093db80(esi + 0x69, 0);
        }
        if (esi[0x65] & 4) {
            FUN_0093db80(esi + 0x55, 0);
        }
        if (esi[0x51] & 4) {
            FUN_0093db80(esi + 0x41, 0);
        }
        IRefCount* r = *(IRefCount**)(esi + 0x30);
        if (r != 0) {
            r->Release();
        }
        cGonzagoTimer_dtor((cGonzagoTimer*)(esi + 0x10));
        *(void**)esi = *(void**)(self + 0x18);
        *(void**)(self + 0x18) = esi;
    }
}

// ===========================================================================
// @ 0x00bcab80  cAgentOrder::CopyConstruct(cAgentOrder const&)  (returns this)
cAgentOrder* cAgentOrder::CopyConstruct(cAgentOrder const& o)
{
    char* self = (char*)this;
    char* src = (char*)&o;
    *(u32*)self = *(u32*)src;
    *(void**)(self + 8) = (void*)0x1465d54;
    *(u32*)(self + 0x0c) = 0;
    *(u32*)(self + 0x10) = *(u32*)(src + 0x10);
    *(u32*)(self + 0x14) = *(u32*)(src + 0x14);
    *(u32*)(self + 0x18) = *(u32*)(src + 0x18);
    *(u32*)(self + 0x1c) = *(u32*)(src + 0x1c);
    *(u8*)(self + 0x20) = *(u8*)(src + 0x20);
    *(u32*)(self + 0x24) = *(u32*)(src + 0x24);
    *(void**)(self + 8) = (void*)0x1464450;

    IRefCount* sp = *(IRefCount**)(src + 0x28);
    *(IRefCount**)(self + 0x28) = sp;
    if (sp != 0) {
        sp->AddRef();
    }
    *(u32*)(self + 0x2c) = *(u32*)(src + 0x2c);
    *(u32*)(self + 0x30) = *(u32*)(src + 0x30);
    *(u32*)(self + 0x34) = *(u32*)(src + 0x34);
    *(u8*)(self + 0x38) = *(u8*)(src + 0x38);

    *(u16*)(self + 0x49) = 0;
    *(u16*)(self + 0x4b) = 0;
    FUN_00542b80(self + 0x39, src + 0x39);
    *(u16*)(self + 0x5d) = 0;
    *(u16*)(self + 0x5f) = 0;
    FUN_00542b80(self + 0x4d, src + 0x4d);
    *(u16*)(self + 0x71) = 0;
    *(u16*)(self + 0x73) = 0;
    FUN_00542b80(self + 0x61, src + 0x61);
    *(u16*)(self + 0x85) = 0;
    *(u16*)(self + 0x87) = 0;
    FUN_00542b80(self + 0x75, src + 0x75);
    return this;
}

// ===========================================================================
// @ 0x00bcac60  cAgentOrderManager::AllocLink()
void cAgentOrderManager::AllocLink()
{
    char* self = (char*)this;
    char* edi = self + 8;
    char* p;
    for (;;) {
        if (*(char**)(edi + 0x10) != 0) {
            p = *(char**)(edi + 0x10);
            *(char**)(edi + 0x10) = *(char**)p;
            break;
        }
        if (!FUN_00926650(edi, 0, 0)) {
            p = 0;
            break;
        }
    }
    if (p != 0) {
        ((cAgentOrder*)(p + 8))->cAgentOrder::cAgentOrder();
    }
    *(char**)p = self;
    *(char**)(p + 4) = *(char**)(self + 4);
    **(char***)(self + 4) = p;
    *(char**)(self + 4) = p;
}

// ===========================================================================
// @ 0x00bcacb0  (cdecl) cAgentOrderManager::Erase(list*, cAgentOrder*)
int FUN_00bcacb0(char* list, IRefCount* obj)
{
    char* node = *(char**)list;
    while (node != list) {
        if ((IRefCount*)(node + 8) == obj) {
            char* next;
            ((cAgentOrderManager*)list)->ReleaseNode(&next, node);
            return 1;
        }
        node = *(char**)node;
    }
    return 0;
}

// ===========================================================================
// @ 0x00bcacf0  eastl vector<16-byte>::DoInsertValues
void cAgentOrderManager::DoInsertValues(char* pos, u32 n, void* val)
{
    char* self = (char*)this;
    char* begin = *(char**)self;
    char* end = *(char**)(self + 4);
    u32 cap = (u32)(end - begin) >> 4;
    if (n > cap) {
        u32 oldLen = (u32)(end - begin) >> 4;
        u32 newCap = oldLen * 2;
        if (oldLen == 0) {
            newCap = 1;
        }
        u32 need = oldLen + n;
        u32 alloc = need > newCap ? need : newCap;
        char* mem;
        if (alloc == 0) {
            mem = 0;
        } else {
            mem = (char*)EAAllocate(alloc << 4, "Simulator", 0, 0,
                                    (int)0x13ebb38, 0xd1);
        }
        char* first = (char*)FUN_00c7ea30(begin, pos, mem);
        FUN_0088f820(first, n, val, pos);
        char* cur = *(char**)(self + 4);
        char* second = (char*)FUN_00c7ea30(pos, cur, mem + (n << 4) + (first - mem));
        if (begin != 0 && *(int*)(begin - 4) != 0) {
            FUN_00f47380(begin);
        }
        *(char**)self = mem;
        *(char**)(self + 4) = second;
        *(char**)(self + 8) = mem + (alloc << 4);
        return;
    }
    if (n == 0) {
        return;
    }
    struct V { u32 a, b, c, d; } v;
    v.a = *(u32*)val;
    v.b = *((u32*)val + 1);
    v.c = *((u32*)val + 2);
    v.d = *((u32*)val + 3);

    u32 tail = (u32)(end - pos) >> 4;
    if (n > tail) {
        u32 extra = n - tail;
        FUN_0088f820(end, extra, &v, pos);
        *(char**)(self + 4) = *(char**)(self + 4) + (extra << 4);
        char* newEnd = *(char**)(self + 4);
        FUN_007f1890(&pos, pos, end, newEnd, pos);
        *(char**)(self + 4) = *(char**)(self + 4) + (tail << 4);
        FUN_00898580(pos, end, &v);
    } else {
        char* src = end - (n << 4);
        FUN_007f1890(&val, src, end, end, 0);
        *(char**)(self + 4) = *(char**)(self + 4) + (n << 4);
        FUN_00edba80(pos, src, end);
        FUN_00898580(pos, pos + (n << 4), &v);
    }
}

// ===========================================================================
// @ 0x00bcae90  cAgentOrderManager::~cAgentOrderManager()
cAgentOrderManager::~cAgentOrderManager()
{
    char* self = (char*)this;
    char* arr = *(char**)(self + 0x65c);
    char* arrEnd = *(char**)(self + 0x664);
    if (arrEnd - arr > 1 && arr != 0) {
        FUN_00f47380(arr);
    }

    {
        char* lst = self + 0x634;
        char* p = *(char**)lst;
        while (p != lst) {
            char* next = *(char**)p;
            *(void**)p = *(void**)(lst + 0x18);
            *(void**)(lst + 0x18) = p;
            p = next;
        }
    }
    FUN_00926640(self + 0x63c);

    ClearList();
    FUN_00926640(self + 0x614);

    if (mSource != 0) {
        mSource->vtbl08();
    }
    char* ap = *(char**)(self + 0x5e8);
    if (ap != 0 && *(int*)(ap - 4) != 0) {
        FUN_00f47380(ap);
    }

    char* p = self + 0x1f4;
    for (int i = 7; i >= 0; --i) {
        p -= 0x38;
        IRefCount* r = *(IRefCount**)p;
        if (r != 0) {
            r->Release();
        }
    }
}

// ===========================================================================
// @ 0x00bcaf40  cAgentOrderManager::PopFront()
void cAgentOrderManager::PopFront()
{
    char* self = (char*)this;
    char* head = self + 0x60c;
    if (*(char**)head == head) {
        return;
    }
    char* node = *(char**)head;
    char* next = *(char**)(node + 4);
    char* prev = *(char**)node;
    *(char**)next = prev;
    *(char**)(prev + 4) = next;
    ((cAgentOrder*)(node + 8))->cAgentOrder::~cAgentOrder();
    *(void**)node = *(void**)(head + 0x18);
    *(void**)(head + 0x18) = node;
}

// ===========================================================================
// @ 0x00bcaf70  cAgentOrderManager::PushBack(void*, IRefCount*, bool)
cAgentOrder* cAgentOrderManager::PushBack(void* a, IRefCount* b, char clear)
{
    char* self = (char*)this;
    if (clear != 0) {
        char* lst = self + 0x60c;
        ClearList();
        *(char**)lst = lst;
        *(char**)(lst + 4) = lst;
    }
    AllocLink();
    char* node = *(char**)(self + 0x610);
    *(void**)(node + 8) = a;
    IRefCount* old = *(IRefCount**)(node + 0x30);
    if (b != old) {
        if (b != 0) {
            b->AddRef();
        }
        *(IRefCount**)(node + 0x30) = b;
        if (old != 0) {
            old->Release();
        }
    }
    return (cAgentOrder*)(node + 8);
}

// ===========================================================================
// @ 0x00bcafe0  cAgentOrderManager::ReleaseQueueObject(void*, unsigned)
void cAgentOrderManager::ReleaseQueueObject(char* obj, u32 idx)
{
    if (obj == 0) {
        return;
    }
    u32 count = *(u32*)(obj + 0x18);
    if (idx >= count) {
        return;
    }
    if (*(u32*)(obj + 0x10) > 1 && idx == *(u32*)(obj + 0x14)) {
        char found = 0;
        u32 i = 0;
        if (count != 0) {
            char* e = obj + 0x20;
            do {
                if (i != idx && *e != 0) {
                    int (*cb)(char*, u32) = *(int(**)(char*, u32))(obj + 0x228);
                    if (cb == 0) {
                        *(u32*)(obj + 0x14) = i;
                        goto cleared;
                    }
                    int r = cb(obj, *(u32*)(e + 4));
                    if (r == 0) {
                        *(u32*)(obj + 0x14) = i;
                        goto cleared;
                    }
                    if (r == 1) {
                        *(u32*)(obj + 0x14) = i;
                        found = 1;
                    }
                }
                ++i;
                e += 0xc;
            } while (i < *(u32*)(obj + 0x18));
            if (found) {
                goto cleared;
            }
        }
        obj[0x1c] = 1;
    }

cleared:
    obj[0x20 + idx * 0xc] = 0;
    if (--*(int*)(obj + 0x10) == 0) {
        obj[0x1c] = 1;
        void (*cb)(char*) = *(void(**)(char*))(obj + 0x224);
        if (cb != 0) {
            cb(obj);
        }
        FUN_00bcacb0((char*)this, (IRefCount*)obj);
    }
}
