// Slice s00c61390 — 0x00c61390 .. 0x00c62750.
//
// Simulator/SP mission classes: terraforming mission state machine, trade and
// trade-route missions, and the mission-track badge.
//
// All of the mission entry points are real __thiscall members so the compiler
// emits the same callee-cleanup (ret N) code and keeps "this" in ecx.

typedef unsigned int   uint32;
typedef unsigned char  uint8;

struct Mission {
    // Functions defined by this slice.
    void  FUN_00c61390(int arg);
    void  FUN_00c61450(int msg, int arg);
    void  FUN_00c61550();
    void  FUN_00c61570();
    int   FUN_00c615c0(int param);
    void* FUN_00c61bb0();
    char  FUN_00c61d70();
    int   FUN_00c61dd0(int param);
    void  FUN_00c61e20(int msg, int arg);
    char  FUN_00c61e80(int msg, int out);
    void* FUN_00c61f20();
    int   FUN_00c620c0(int tag);
    void  FUN_00c62100();
    void  FUN_00c62180(int* a, int* b);
    char  FUN_00c62200();
    void  FUN_00c62250(int msg, int arg);
    void* FUN_00c62370();
    char  FUN_00c624c0();
    int   FUN_00c62540(int param);
    void  FUN_00c62590(int msg, int arg);
    int   FUN_00c62710();
    void  FUN_00c62750(int msg, int arg);

    // __thiscall helpers from the rest of the game.
    void* FUN_0970b30();
    void* FUN_00b21340(int a, int b, int c, int d, int e);
    void  FUN_00ba95a0(void* src);
    void  FUN_00bdc4a0(int arg);
    void* FUN_00bbc870(void* out, int score, int id, int zero);
    void* FUN_00bbc950(void* out, int score, int id, int zero);
    void* FUN_00bbca30(void* out, int score, int id);
    int   FUN_00c478b0(int arg);
    void  FUN_00c4a6b0(int msg, int arg);
    void  FUN_00c47d80();
    void  FUN_00c46160();
    void  FUN_00c461d0();
    void  FUN_00c46250();
    void  FUN_00c471c0();
    void  FUN_00c472e0();
    void  FUN_00c46590();
    char  FUN_00c4ad50();
    void  FUN_00c4a0c0();
    void  FUN_00c4b760();
    char  FUN_00c491c0(int msg, int out);
    void* FUN_00bfc5f0();
    int   FUN_00fe6770(int id);
    int   FUN_00fe66f0(int id);
    char  FUN_00fe4180(int id);
    void* FUN_00c451e0();
    int   FUN_00ff0420();
    int   FUN_00ff0870();
    void  FUN_00ff0760();
    char  FUN_00c308e0(int arg);
    void  FUN_00c48e90();
    int   FUN_00c70fb0();
    int   FUN_00c60ab0();
    char  FUN_00c60af0();
    char  FUN_00c60cc0();
    char  FUN_00c609d0();
    void* FUN_005c65e0();
    char  FUN_00ae9390();
    void  FUN_00dd8640(int a, int b, int c, int d, int e, int f);
    void* FUN_008414c0();
    void* FUN_00ba6dc0(int arg);
    void* FUN_00b8de30();
    void* FUN_00b1fdb0();
};

// cdecl functions.
void* FUN_01021260();
void* FUN_01021080();
void* FUN_01021090();
void* FUN_01021300();
void* FUN_00b3d300();
void* FUN_00b3d2a0();
void* FUN_00b3d3e0();
void* FUN_00b3d420();
void* FUN_00b3d430();
void* FUN_00b3d4a0();
void* FUN_01002bd0();
char  FUN_006a1250(void* obj, int key, void* out);
char  FUN_006a12a0(void* obj, int key, void* out);
char  FUN_005f78f0(const void* a, const void* b);
int   FUN_0041e050(void* out, const void* fmt, int v);
int   FUN_01041c50(const char* name, int id, int b);
void  FUN_00f47380(void* p);
char  FUN_00c70150(void* civs, void* owner, int flag);

typedef char (__thiscall* VTCFn)(void*);
typedef void (__thiscall* VTVFn)(void*);
#define VTC(o,off) (((VTCFn)(*(void***)(o))[(off)/4])((void*)(o)))
#define VTV(o,off) (((VTVFn)(*(void***)(o))[(off)/4])((void*)(o)))

// @ 0x00c61390
void Mission::FUN_00c61390(int arg)
{
    void* planet = this->FUN_0970b30();
    void* active = FUN_01021260();
    if (active != planet)
        return;
    if (FUN_01021080() != 0)
        return;

    void* nm = FUN_00b3d300();
    void* vec = ((Mission*)nm)->FUN_00b21340(
        0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, 0x018c43e8);
    int local[5];
    ((Mission*)local)->FUN_00ba95a0((char*)vec + 4);
    int* begin = (int*)local[0];
    int* end = (int*)local[1];

    for (int* it = begin; it != end; it++)
        if (*it)
            ((Mission*)*it)->FUN_00bdc4a0(arg);
    for (int* it = begin; it < end; it++)
        if (*it)
            VTV((void*)*it, 4);
    if (begin != 0 && begin[-1] != 0)
        FUN_00f47380(begin);
}

// @ 0x00c61450
void Mission::FUN_00c61450(int msg, int arg)
{
    switch (msg) {
    case 0x248975f:
        if (*(int*)((char*)this + 0x44) != (int)0xd85005e9)
            goto handle;
        if (*(int*)((char*)this + 0x1bc) == 0)
            ((Mission*)((char*)this - 0x34))->FUN_00c46160();
        goto lab_14a9;
    case 0x2489766:
    case 0x248976a:
    case 0x490d429:
        goto lab_1514;
    case 0x43f2583:
        goto lab_14a9;
    default:
        goto handle;
    }

lab_1514:
    if (*(int*)((char*)this + 0x44) == (int)0xd85005e9) {
        Mission* p = (Mission*)((char*)this - 0x34);
        if (VTC(p, 0xf8) == 0)
            p->FUN_00c47d80();
    }
    goto handle;

lab_14a9:
    if (*(int*)((char*)this + 0x44) == (int)0xd85005e9) {
        Mission* p = (Mission*)((char*)this - 0x34);
        void* planet = p->FUN_0970b30();
        if (FUN_01021260() == planet) {
            if (VTC(p, 0xf8) == 0) {
                p->FUN_00c47d80();
                p->FUN_00c61390(*(int*)((char*)this + 0x1bc) == 3);
            }
        }
    }
handle:
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c61550
void Mission::FUN_00c61550()
{
    this->FUN_00c46590();
    this->FUN_00c61390(0);
}

// @ 0x00c61570
void Mission::FUN_00c61570()
{
    if (*(int*)((char*)this + 0x1f0) == 4)
        return;
    VTV(this, 0x6c);
    if (*(int*)((char*)this + 0x1f0) != 4) {
        if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
            this->FUN_00c61390(0);
        *(int*)((char*)this + 0x1f0) = 4;
        this->FUN_00c47d80();
    }
    this->FUN_00c472e0();
    this->FUN_00c471c0();
}

// @ 0x00c615c0
int Mission::FUN_00c615c0(int param)
{
    int rc = this->FUN_00c478b0(param);
    int st;

    if (rc != 3)
        return rc;

    if (VTC(this, 0xf8) == 0) {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() == planet) {
            int f = ((Mission*)this->FUN_0970b30())->FUN_00c70fb0();
            int score = this->FUN_00c60ab0();
            st = *(int*)((char*)this + 0x1f0);
            if (st != 0 && score > f) {
                if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                    this->FUN_00c61390(0);
                *(int*)((char*)this + 0x1f0) = 0;
                this->FUN_00c47d80();
            } else if (st != 1 && this->FUN_00c60af0()) {
                if (*(int*)((char*)this + 0x1f0) != 1) {
                    if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                        this->FUN_00c61390(0);
                    *(int*)((char*)this + 0x1f0) = 1;
                    this->FUN_00c47d80();
                }
                this->FUN_00c461d0();
            } else if (*(int*)((char*)this + 0x78) == (int)0xd85005e9 &&
                       st != 2 && this->FUN_00c60cc0()) {
                if (*(int*)((char*)this + 0x1f0) != 2) {
                    if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                        this->FUN_00c61390(0);
                    *(int*)((char*)this + 0x1f0) = 2;
                    this->FUN_00c47d80();
                }
                this->FUN_00c46250();
            }
        }
    }

    switch (*(int*)((char*)this + 0x1f0)) {
    case 0: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_17ca;
        if (FUN_01021080() != 0)
            goto lab_17ca;
        {
            int f = ((Mission*)this->FUN_0970b30())->FUN_00c70fb0();
            int score = this->FUN_00c60ab0();
            if (score > f) {
                if (*(int*)((char*)this + 0x78) != (int)0xd85005e9)
                    goto lab_17ca;
                if (*(uint8*)((char*)this + 0x1f4) != 0)
                    goto lab_17d7;
                if (!this->FUN_00c609d0()) {
                    void* body = ((Mission*)this->FUN_0970b30())->FUN_008414c0();
                    if (body != 0 &&
                        *(float*)0x013f9428 >= *(float*)((char*)body + 0x1fd4) &&
                        *(float*)0x013f9428 >= *(float*)((char*)body + 0x1fd8)) {
                        *(uint8*)((char*)this + 0x1f4) = 1;
                        this->FUN_00c47d80();
                    }
                }
                goto lab_17ca;
            }
            if (*(int*)((char*)this + 0x1f0) != 1) {
                if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                    this->FUN_00c61390(0);
                *(int*)((char*)this + 0x1f0) = 1;
                this->FUN_00c47d80();
            }
            this->FUN_00c461d0();
        }
lab_17ca:
        if (*(uint8*)((char*)this + 0x1f4) == 0)
            goto lab_1b74;
lab_17d7:
        if (!this->FUN_00c609d0())
            goto lab_1b74;
        *(uint8*)((char*)this + 0x1f4) = 0;
        this->FUN_00c47d80();
        break;
    }
    case 1: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_1b74;
        int score = this->FUN_00c60ab0();
        int k1[3], k2[3], k3[3];
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc870(k1, score, 0x6d60a1cc, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc870(k2, score, 0x029c388a, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc870(k3, score, 0x3a8be428, 0),
                (void*)0x01693170))
            goto lab_1b74;

        if (*(int*)((char*)this + 0x78) != (int)0xd85005e9)
            goto lab_1b31;
        if (*(int*)((char*)this + 0x1f0) != 2) {
            this->FUN_00c61390(0);
            *(int*)((char*)this + 0x1f0) = 2;
            this->FUN_00c47d80();
        }
        this->FUN_00c46250();
        break;
    }
    case 2: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_1b74;
        int score = this->FUN_00c60ab0();
        int k1[3], k2[3], k3[3];
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc950(k1, score, 0, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbc950(k2, score, 1, 0),
                (void*)0x01693170))
            goto lab_1b74;
        if (!FUN_005f78f0(
                ((Mission*)FUN_00b3d430())->FUN_00bbca30(k3, score, 0),
                (void*)0x01693170))
            goto lab_1b74;

        if (*(int*)((char*)this + 0x78) == (int)0xd85005e9) {
            void* p = this->FUN_0970b30();
            int civs = *(int*)((char*)p + 0x13c);
            if (((Mission*)FUN_01021300())->FUN_00c308e0(civs)) {
                if (*(int*)((char*)this + 0x1f0) == 3)
                    break;
                if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
                    this->FUN_00c61390(1);
                *(int*)((char*)this + 0x1f0) = 3;
                this->FUN_00c47d80();
                break;
            }
        }
        goto lab_1b31;
    }
    case 3: {
        void* planet = this->FUN_0970b30();
        if (FUN_01021260() != planet)
            goto lab_1b74;
        void* tp = this->FUN_0970b30();
        if (*(uint8*)((char*)this + 0x1f5) == 0) {
            void* civs = (void*)*(int*)((char*)tp + 0x13c);
            void* owner = this->FUN_00c451e0();
            if (FUN_00c70150(civs, owner, 0) != 0) {
                *(uint8*)((char*)this + 0x1f5) = 1;
                this->FUN_00c47d80();
            }
            break;
        }
        {
            char* civVec = (char*)*(int*)((char*)tp + 0x13c);
            void* owner = this->FUN_00c451e0();
            if (FUN_00c70150(civVec, owner, 0) == 0) {
                *(uint8*)((char*)this + 0x1f5) = 0;
                this->FUN_00c47d80();
                break;
            }
            int n = (*(int*)(civVec + 0x160) - *(int*)(civVec + 0x15c)) >> 2;
            char found = 0;
            for (int i = 0; i < n; i++) {
                Mission* civ = *(Mission**)(*(int*)(civVec + 0x15c) + i * 4);
                void* owner2 = this->FUN_00c451e0();
                int eid = *(int*)((char*)owner2 + 0x84);
                if (civ->FUN_00ff0420() == eid) {
                    int* cities = (int*)civ->FUN_005c65e0();
                    int nc = (cities[1] - cities[0]) >> 2;
                    for (int j = 0; j < nc; j++) {
                        Mission* city = *(Mission**)(cities[0] + j * 4);
                        int nb = city->FUN_00ff0870();
                        char* link = *(char**)((char*)city + 0x7c) + 0x34;
                        for (int k = 0; k < nb; k++) {
                            if (*(int*)link == 0x018ea2cc)
                                found = 1;
                            link += 0x38;
                        }
                        city->FUN_00ff0760();
                    }
                }
            }
            if (found)
                goto lab_1b31;
        }
        break;
    }
    }

lab_1b74:
    return rc;
lab_1b31:
    this->FUN_00c61570();
    return rc;
}

// @ 0x00c61bb0
void* Mission::FUN_00c61bb0()
{
    this->FUN_00c48e90();
    *(int*)((char*)this + 0x1f0) = 0;
    *(int*)((char*)this + 0x1f4) = 0;
    *(int*)((char*)this + 0x1f8) = 0;
    *(void**)((char*)this + 0) = (void*)0x01470330;
    *(void**)((char*)this + 4) = (void*)0x0146dfb4;
    *(void**)((char*)this + 0x34) = (void*)0x01470320;
    return this;
}

// @ 0x00c61d70
char Mission::FUN_00c61d70()
{
    if (!this->FUN_00c4ad50())
        return 0;
    FUN_006a12a0(*(void**)((char*)this + 0x180), 0x6d03cf73,
                 (char*)this + 0x1f4);
    void* gd = ((Mission*)FUN_01002bd0())->FUN_00bfc5f0();
    *(int*)((char*)this + 0x1f8) =
        ((Mission*)gd)->FUN_00fe6770(*(int*)((char*)this + 0x1f4));
    this->FUN_00c4a0c0();
    return 1;
}

// @ 0x00c61dd0
int Mission::FUN_00c61dd0(int param)
{
    int rc = this->FUN_00c478b0(param);
    if (VTC(this, 0xf8) == 0) {
        if (((Mission*)((Mission*)FUN_01002bd0())->FUN_00bfc5f0())->
                FUN_00fe4180(*(int*)((char*)this + 0x1f4)))
            this->FUN_00c4b760();
    }
    return rc;
}

// @ 0x00c61e20
void Mission::FUN_00c61e20(int msg, int arg)
{
    int* pa = (int*)arg;
    switch (msg) {
    case 0x038cf2fb:
        ((Mission*)((char*)this - 0x34))->FUN_00c47d80();
        break;
    case 0x038cf2fc:
        if (pa[2] == *(int*)((char*)this + 0x1c0)) {
            ((Mission*)((char*)this - 0x34))->FUN_00c4b760();
            this->FUN_00c4a6b0(msg, arg);
            return;
        }
        break;
    }
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c61e80
char Mission::FUN_00c61e80(int msg, int out)
{
    void* gd = ((Mission*)FUN_01002bd0())->FUN_00bfc5f0();
    if (msg == (int)0xe58ee16c) {
        FUN_0041e050((void*)out, (const void*)0x013f01bc,
                     *(int*)((char*)this + 0x1f8));
        return 1;
    }
    if (msg == (int)0xd4814edd) {
        int a = ((Mission*)gd)->FUN_00fe6770(*(int*)((char*)this + 0x1f4));
        int b = ((Mission*)gd)->FUN_00fe66f0(*(int*)((char*)this + 0x1f4));
        FUN_0041e050((void*)out, (const void*)0x013f01bc, a - b);
        return 1;
    }
    return this->FUN_00c491c0(msg, out);
}

// @ 0x00c61f20
void* Mission::FUN_00c61f20()
{
    this->FUN_00c48e90();
    *(int*)((char*)this + 0x1f0) = 0;
    *(int*)((char*)this + 0x1f4) = 0;
    *(int*)((char*)this + 0x1f8) = 0;
    *(uint8*)((char*)this + 0x1fc) = 0;
    *(uint8*)((char*)this + 0x1fd) = 0;
    *(void**)((char*)this + 0) = (void*)0x01470540;
    *(void**)((char*)this + 4) = (void*)0x0146dfb4;
    *(void**)((char*)this + 0x34) = (void*)0x01470530;
    return this;
}

// @ 0x00c620c0
int Mission::FUN_00c620c0(int tag)
{
    int id = *(int*)((char*)this + 0x1f4);
    switch (id) {
    case 0x082af541:
        return tag == 0x082af541;
    case 0x7ecbe6f5:
        return tag == 0x7ecbe6f5;
    }
    return id & 0xffffff00;
}

// @ 0x00c62100
void Mission::FUN_00c62100()
{
    if (*(int*)((char*)this + 0x1f0) != 0)
        return;
    VTV(this, 0x6c);
    if (*(int*)((char*)this + 0x1f0) != 1) {
        *(int*)((char*)this + 0x1f0) = 1;
        this->FUN_00c47d80();
    }
    this->FUN_00c472e0();
    this->FUN_00c471c0();
    if (*(int*)((char*)this + 0x78) == (int)0xdec64aa7) {
        ((Mission*)FUN_00b3d3e0())->FUN_00dd8640(
            0xe737105a, 0x131a9f54, 0, 0, 1, 0);
    }
}

// @ 0x00c62180
void Mission::FUN_00c62180(int* a, int* b)
{
    void* obj = *(void**)((char*)this + 0x180);
    int k1[3] = {0, 0, 0};
    if (FUN_006a1250(obj, 0x6d03cf71, k1))
        *a = k1[0];
    void* obj2 = *(void**)((char*)this + 0x180);
    int k2[3] = {0, 0, 0};
    if (FUN_006a1250(obj2, 0x6d03cf72, k2))
        *b = k2[0];
}

// @ 0x00c62200
char Mission::FUN_00c62200()
{
    if (!this->FUN_00c4ad50())
        return 0;
    VTV(this, 0x16c);
    this->FUN_00c62180((int*)((char*)this + 0x1f4),
                       (int*)((char*)this + 0x1f8));
    this->FUN_00c4a0c0();
    VTV(this, 0x170);
    return 1;
}

// @ 0x00c62250
void Mission::FUN_00c62250(int msg, int arg)
{
    if (msg == (int)0xf46092c1 && *(int*)((char*)this + 0x1bc) == 0) {
        int v1 = *(int*)(arg + 8);
        void* v2 = *(void**)(arg + 0x28);
        void* v3 = *(void**)(arg + 0x10);
        char ok = 1;
        if (*(int*)((char*)this + 0x44) == (int)0xdec64aa7) {
            void* p = ((Mission*)FUN_00b3d2a0())->FUN_00ba6dc0((int)v2);
            if (p != 0) {
                void* av = ((Mission*)p)->FUN_00b8de30();
                av = ((Mission*)av)->FUN_00b1fdb0();
                int pid = (int)FUN_01021090();
                ok = (av != (void*)pid);
            }
        }
        if (((Mission*)((char*)this - 0x34))->FUN_00c620c0((int)v3) && ok) {
            if (v1 == 0)
                *(uint8*)((char*)this + 0x1c9) = 1;
            else
                *(uint8*)((char*)this + 0x1c8) = 1;
        }
        switch (*(int*)((char*)this + 0x1c4)) {
        case 0x2a99c94f:
            if (*(uint8*)((char*)this + 0x1c8))
                goto do_update;
            break;
        case 0x8f063c70:
            if (*(uint8*)((char*)this + 0x1c8))
                goto do_update;
            if (*(uint8*)((char*)this + 0x1c9))
                goto do_update;
            break;
        case 0x31e0a061:
            if (*(uint8*)((char*)this + 0x1c9))
                goto do_update;
            break;
        case 0x52f6f862:
            if (!*(uint8*)((char*)this + 0x1c8))
                goto handle;
            if (*(uint8*)((char*)this + 0x1c9))
                goto do_update;
            break;
        }
    }
handle:
    this->FUN_00c4a6b0(msg, arg);
    return;
do_update:
    ((Mission*)((char*)this - 0x34))->FUN_00c62100();
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c62370
void* Mission::FUN_00c62370()
{
    this->FUN_00c48e90();
    *(int*)((char*)this + 0x1f0) = 0;
    *(uint8*)((char*)this + 0x1f4) = 0;
    *(void**)((char*)this + 0) = (void*)0x01470758;
    *(void**)((char*)this + 4) = (void*)0x0146dfb4;
    *(void**)((char*)this + 0x34) = (void*)0x01470748;
    return this;
}

// @ 0x00c624c0
char Mission::FUN_00c624c0()
{
    if (!this->FUN_00c4ad50())
        return 0;
    if (!VTC(this, 0x128))
        return 0;
    this->FUN_00c4a0c0();
    VTV(this, 0x170);
    return 1;
}

// @ 0x00c62540
int Mission::FUN_00c62540(int param)
{
    if (*(uint8*)((char*)this + 0x1f4) != 0) {
        void* cm = FUN_00b3d4a0();
        if (!((Mission*)cm)->FUN_00ae9390()) {
            *(uint8*)((char*)this + 0x1f4) = 0;
            FUN_01041c50("SPG_TutorialTradeRoute", 0xf6691319, 1);
        }
    }
    return this->FUN_00c478b0(param);
}

// @ 0x00c62590
void Mission::FUN_00c62590(int msg, int arg)
{
    if (msg == (int)0xf46092d1 && *(int*)((char*)this + 0x1bc) == 0) {
        int a = *(int*)(arg + 0x20);
        int b = *(int*)(arg + 0x18);
        int pid = (int)FUN_01021090();
        if (b == pid || a == pid) {
            ((Mission*)((char*)this - 0x34))->FUN_00c4b760();
            unsigned u = *(unsigned*)((char*)this + 0xfc);
            if ((u >> 3) & 1)
                *(uint8*)((char*)this + 0x1c0) = 1;
        }
    }
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c62710
int Mission::FUN_00c62710()
{
    int n = *(int*)((char*)this + 0x20c) - *(int*)((char*)this + 0x208);
    int result = 0;
    int i = 0;
    if (n > 0) {
        const char* flags = (const char*)*(int*)((char*)this + 0x208);
        for (; i < n; i++) {
            if (flags[i] == 0) {
                result = *(int*)(*(int*)((char*)this + 0x1f4) + i * 12);
                break;
            }
        }
    }
    return result;
}

// @ 0x00c62750
void Mission::FUN_00c62750(int msg, int arg)
{
    if (msg == 0x056690bb && *(int*)((char*)this + 0x1bc) == 0) {
        int* rec = *(int**)(arg + 8);
        int n = (*(int*)((char*)this + 0x1c4) - *(int*)((char*)this + 0x1c0)) / 12;
        char found = 0;
        int i;
        for (i = 0; i < n; i++) {
            int* p = (int*)(*(int*)((char*)this + 0x1c0) + i * 12);
            if (p[0] == rec[0] && p[1] == rec[1] && p[2] == rec[2]) {
                *(uint8*)(*(int*)((char*)this + 0x1d4) + i) = 1;
                found = 1;
            }
        }
        if (found) {
            Mission* m = (Mission*)((char*)this - 0x34);
            m->FUN_00c47d80();
            n = (*(int*)((char*)this + 0x1c4) - *(int*)((char*)this + 0x1c0)) / 12;
            for (i = 0; i < n; i++) {
                if (*(uint8*)(*(int*)((char*)this + 0x1d4) + i) == 0)
                    goto handle;
            }
            if (*(int*)((char*)m + 0x1f0) == 0) {
                VTV(m, 0x6c);
                if (*(int*)((char*)m + 0x1f0) != 1) {
                    *(int*)((char*)m + 0x1f0) = 1;
                    m->FUN_00c47d80();
                }
                m->FUN_00c472e0();
                m->FUN_00c471c0();
            }
        }
    }
handle:
    this->FUN_00c4a6b0(msg, arg);
}
