// Slice s0113dc00 -- RenderWare 4 audio core: Dac device loop, plug-in attribute command
// setters, and the AiffWriter plug-in.  The original used VC .NET 2003 (/vc71) and /GL + /LTCG,
// so functions that make calls cannot be byte-exact from one object; leaf functions
// (AiffWriter_IntToExtended, AiffWriter::PostCommand) are byte-exact candidates.
// Flags: /vc71 /O2 /MD /Gy /TP /arch:SSE
#include "../../include/types.h"

// ---------------------------------------------------------------------------
// imports (same IAT slots as the original)
// ---------------------------------------------------------------------------
extern "C" {
    __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int);   // winmm
    __declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int);     // winmm
    __declspec(dllimport) unsigned long __stdcall timeGetTime(void);              // winmm
    __declspec(dllimport) void __stdcall Sleep(unsigned long);                    // kernel32
    __declspec(dllimport) void* __cdecl memset(void*, int, unsigned int);
    __declspec(dllimport) void* __cdecl memcpy(void*, const void*, unsigned int);
    __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
    __declspec(dllimport) int   __cdecl fclose(void*);
    __declspec(dllimport) unsigned int __cdecl fwrite(const void*, unsigned int, unsigned int, void*);
    __declspec(dllimport) int   __cdecl fseek(void*, long, int);
    __declspec(dllimport) char* __cdecl strncpy(char*, const char*, unsigned int);
    unsigned int __cdecl strlen(const char*);
    long __cdecl _InterlockedExchangeAdd(volatile long*, long);
    int   __cdecl Plugin_GetSizeFir64(int channels, int a);              // 0x1153770
    void* __cdecl Plugin_CreateFir64(void* sys, int channels, int a, void* buf); // 0x1153790
}

// ---------------------------------------------------------------------------
// globals / constants
// ---------------------------------------------------------------------------
extern unsigned char g_16e6304;    // 0x16e6304
extern unsigned char g_16e6305;    // 0x16e6305
extern unsigned char g_16e6306;    // 0x16e6306
extern unsigned char g_16e6307;    // 0x16e6307
extern unsigned char g_16e633c;    // 0x16e633c
extern int           g_16e6308[];  // 0x16e6308
extern int           g_16e6300;    // 0x16e6300
extern int           g_16e7bbc;    // 0x16e7bbc
extern float         g_16e631c[];  // 0x16e631c
extern float         g_16e6320[];  // 0x16e6320
extern int           g_15bf51c[];  // 0x15bf51c
extern unsigned char g_14c2fa0[];  // 0x14c2fa0
extern int           g_16e7b98;    // 0x16e7b98
extern int           g_16e7b9c;    // 0x16e7b9c
extern int           g_16e7ba4;    // 0x16e7ba4
extern int           g_16e7ba8;    // 0x16e7ba8
extern unsigned char g_16e7ba0[];  // 0x16e7ba0
extern unsigned char g_14bc0fc[];  // 0x14bc0fc  vtable
extern unsigned char g_14c2fa8[];  // 0x14c2fa8  vtable
extern unsigned char g_14ca66c[];  // 0x14ca66c  vtable

// opaque framework entry points.  vc71 has no usable __thiscall in casts, so each direct
// thiscall callee is declared __fastcall with a dummy second (edx) parameter.
void __fastcall Sub_1154eb0(void* self);                                       // 0x1154eb0
void __fastcall Sub_1153b00(void* self);                                       // 0x1153b00
void __fastcall Sub_112dbb0(void* self);                                       // 0x112dbb0
void __fastcall Sub_743b50(void* self);                                        // 0x743b50
void __fastcall Sub_68c1b0(void* self, int pad, int a, int b);                 // 0x68c1b0
void __fastcall Sub_1154f00(void* self, int pad, void* sys);                   // 0x1154f00
void __fastcall Sub_1154e50(void* self);                                       // 0x1154e50
void __fastcall Sub_922900(void* self);                                        // 0x922900
void __fastcall Sub_922e10(void* self);                                        // 0x922e10
void __fastcall Sub_11548d0(void* self);                                       // 0x11548d0
int  __fastcall Sub_922f30(void* self, int pad, void* a, void* b, void* c, void* d); // 0x922f30
void* __cdecl Sub_922920(void);                                                // 0x922920
void  __cdecl Func_c620(void* self, int extra);                                // 0x113c620

// ---------------------------------------------------------------------------
// object stubs (retail layouts taken from the disassembly)
// ---------------------------------------------------------------------------
struct System;

struct System {                       // size 0x100
    char  pad00[0x08];
    double mSystemTime;               // +0x08
    char  pad10[0x20 - 0x10];
    char* mpCommandBuffer;            // +0x20
    char  pad24[0xb4 - 0x24];
    unsigned int mCommandIndex;       // +0xb4
    char  padb8[0x100 - 0xb8];

    void Lock();                                        // 0x112c560
    void Unlock();                                      // 0x112c570
    void ExecuteCommands();                             // 0x112c6e0
    void* Alloc(unsigned int size, const char* name,
                unsigned int align, unsigned int flags); // 0x112c820
    void Free(void* p, unsigned int flags);             // 0x112c850
    void Queue2(void* fn, void* obj);                   // 0xa16170
    void RemoveTimerPtr(void* handle);                  // 0x112dad0
    int  CreateVoicePool();                             // 0x1155670
    void SetThreadHandle(void* h);                      // 0x112c5f0
};

struct TimerManager {
    char pad[0x48];
    int AddTimer(void* handle, void* cb, void* ctx, const char* name, int a, int b); // 0x112d8e0
};

struct Region {
    char pad[0x10];
    void Init2(int a, int b);       // 0x68c1b0
    void Init3();                   // 0x11548d0
};

struct Cmd {
    void* fn;    // +0x00
    void* obj;   // +0x04
    int   val;   // +0x08
};

// sink object (DirectSound secondary buffer): COM __stdcall methods
typedef int (__stdcall *SinkLock)(void* self, unsigned dwOffset, unsigned dwBytes,
                                  void** p1, unsigned* n1, void** p2, unsigned* n2, unsigned flags);
typedef int (__stdcall *SinkUnlock)(void* self, void* p1, unsigned n1, void* p2, unsigned n2);

struct Dac {
    char pad[0x100];

    void Thread();                          // 0x113dc00
    void Func_cf70();                       // 0x113cf70
    void Func_cff0(int a, int b);           // 0x113cff0
    int  Func_d5d0();                       // 0x113d5d0
    int  Func_ce00();                       // 0x113ce00
    void Func_d200(int a);                  // 0x113d200
    int  Func_d930();                       // 0x113d930
    void Func_d9f0();                       // 0x113d9f0
    void Func_dae0(int a);                  // 0x113dae0
    void Func_db70();                       // 0x113db70
    void Func_cea0();                       // 0x113cea0
    void PostCmd(int cmd, void* val);       // 0x113e340
};

struct AiffWriter {                   // size 0x50, : PlugIn
    void*  vftable;                   // +0x00
    System* mpSystem;                 // +0x04
    char   pad08[0x20 - 0x08];
    unsigned char mInputChannels;     // +0x20
    unsigned char mOutputChannels;    // +0x21
    char   pad22[0x3c - 0x22];
    void*  mFp;                       // +0x3c
    void*  mpBuf;                     // +0x40
    unsigned int mSamplesWritten;     // +0x44
    unsigned int mSampleRate;         // +0x48
    unsigned char mBufAvailable;      // +0x4c
    unsigned char mTimerAdded;        // +0x4d
    char   pad4e[0x50 - 0x4e];

    void PostCommand(int sel, const char** str);   // 0x113ebe0
    void ReleaseEvent();                           // 0x113ebb0
};

// ---------------------------------------------------------------------------
// plug-in attribute command handlers
// ---------------------------------------------------------------------------

// @ 0x0113e110
int Dac_CmdA(int arg)
{
    Dac* self = *(Dac**)((char*)arg + 4);
    if (g_16e633c == 0) {
        *(float*)((char*)self + 0x28) = 1.0f;
        return 0xc;
    }
    int tbl[4] = { 3, 2, 1, 0 };
    float v = *(float*)((char*)arg + 8);
    int found = 0;
    for (int i = 0; i < 4; i++) {
        if (v == (float)tbl[i]) { found = i; break; }
    }
    unsigned char b = 0;
    if (found < 4) {
        do {
            if (b) break;
            unsigned cnt = g_16e633c;
            int j = 0;
            if ((int)cnt > 0) {
                int key = tbl[found];
                do {
                    if (key == g_16e6308[j]) {
                        *(float*)((char*)self + 0x28) = (float)key;
                        b = 1;
                        break;
                    }
                    j++;
                } while (j < (int)cnt);
            }
            found++;
        } while (found < 4);
    }
    float f = *(float*)((char*)self + 0x28);
    int idx;
    __asm {
        movss xmm0, f
        cvtss2si eax, xmm0
        mov idx, eax
    }
    g_16e6305 = g_14c2fa0[idx];
    self->Func_db70();
    return 0xc;
}

// @ 0x0113e200
int Dac_CmdB(int arg)
{
    Dac* self = *(Dac**)((char*)arg + 4);
    if (g_16e6306 != 0) {
        unsigned n = (unsigned char)g_16e6306;
        float v = *(float*)((char*)arg + 8);
        int u = 0;
        int i = 0;
        int found = 0;
        if (n != 0) {
            do {
                if (g_16e6320[i] >= v) { u = *(int*)&g_16e6320[i]; found = 1; break; }
                i++;
            } while (i < (int)n);
        }
        if (!found) u = *(int*)&g_16e631c[n];
        *(int*)((char*)self + 0x30) = u;
        System* sys = *(System**)((char*)self + 4);
        float f = *(float*)((char*)self + 0x30);
        float r = 256.0f / f;
        *(float*)((char*)sys + 0xc0) = f;
        *(float*)((char*)sys + 0xbc) = r;
        *(float*)((char*)sys + 0x98) = r;
        self->Func_db70();
    }
    return 0xc;
}

// @ 0x0113e280
int Dac_CmdStart(int arg)
{
    Dac* self = *(Dac**)((char*)arg + 4);
    if (g_16e7b9c == 0) {
        g_16e6304 = 1;
        *(int*)((char*)self + 0x5c) = 0;
        System* sys = *(System**)((char*)self + 4);
        *(unsigned*)((char*)self + 0x58) = 0x447a0000;   // 1000.0f
        *(double*)((char*)self + 0x80) = sys->mSystemTime + 10.0;
        *(int*)((char*)self + 0x68) = 5;
        *(double*)((char*)self + 0x70) = sys->mSystemTime + 1.0;
        self->Func_d9f0();
        g_16e7b9c = 1;
        Sub_1154eb0(g_16e7ba0);
        g_16e7ba8 = 1;
    }
    return 8;
}

// @ 0x0113e300
int Dac_CmdStop(int arg)
{
    if (g_16e7b9c == 0) {
        Dac* self = *(Dac**)((char*)arg + 4);
        int v = *(int*)((char*)arg + 8);
        self->Func_dae0(v);
        Sub_1154eb0(g_16e7ba0);
        g_16e7ba8 = 1;
    }
    return 0xc;
}

// @ 0x0113e340
void Dac::PostCmd(int cmd, void* val)
{
    Dac* self = this;
    System* sys = *(System**)((char*)self + 4);
    if (cmd == 0) {
        float x = *(float*)val;
        int idx;
        __asm {
            movss xmm0, x
            cvtss2si eax, xmm0
            mov idx, eax
        }
        *(int*)((char*)val + 8) = g_15bf51c[idx];
        *(float*)((char*)val + 4) = 0.0f;
        unsigned cnt = g_16e633c;
        for (int i = 0; i < (int)cnt; i++) {
            if (x == (float)g_16e6308[i]) {
                *(float*)((char*)val + 4) = 1.0f;
                break;
            }
        }
        return;
    }
    if (cmd >= 1 && cmd <= 4) {
        unsigned index = sys->mCommandIndex;
        char* base = sys->mpCommandBuffer;
        if (cmd == 1) {
            Cmd* c = (Cmd*)(base + index);
            sys->mCommandIndex = index + 0xc;
            c->fn = (void*)0x113e110;
            c->obj = self;
            c->val = *(int*)val;
        } else if (cmd == 2) {
            Cmd* c = (Cmd*)(base + index);
            sys->mCommandIndex = index + 0xc;
            c->fn = (void*)0x113e200;
            c->obj = self;
            c->val = *(int*)val;
        } else if (cmd == 3) {
            Cmd* c = (Cmd*)(base + index);
            sys->mCommandIndex = index + 8;
            c->fn = (void*)0x113e280;
            c->obj = self;
        } else {
            Cmd* c = (Cmd*)(base + index);
            sys->mCommandIndex = index + 0xc;
            c->fn = (void*)0x113e300;
            c->obj = self;
            c->val = (int)*(float*)val;
        }
        return;
    }
    if (cmd == 5) {
        sys->Queue2((void*)0x113d770, self);
    } else if (cmd == 6) {
        self->Func_cea0();
    }
}

// ---------------------------------------------------------------------------
// plug-in instances built on top of the attribute system (other classes)
// ---------------------------------------------------------------------------

// @ 0x0113e4e0
bool Plugin_InitA(void* self)
{
    if (self != 0) {
        *(void**)self = g_14bc0fc;
        Sub_1153b00((char*)self + 0x50);
    }
    *(void**)((char*)self + 0x0c) = (char*)self + 0x28;
    *(float*)((char*)self + 0x30) = 1.0f;
    *(float*)((char*)self + 0x28) = 120.0f;
    *(float*)((char*)self + 0x38) = 0.1f;
    *(float*)((char*)self + 0x48) = 1.0f;
    *(float*)((char*)self + 0xa4) = 1.0f;
    *(float*)((char*)self + 0x40) = 0.5f;
    *(float*)((char*)self + 0xa0) = 120.0f;
    *(float*)((char*)self + 0xa8) = 0.1f;
    *(float*)((char*)self + 0xb0) = 1.0f;
    *(float*)((char*)self + 0xac) = 0.5f;
    *(float*)((char*)self + 0xb4) = 0.0f;
    *(int*)((char*)self + 0xb8) = 0;
    return 1;
}

// @ 0x0113e5d0
bool Plugin_InitB(void* self)
{
    Func_c620(self, 0x28);
    void* tgt = *(void**)((char*)self + 8);
    *(float*)((char*)self + 0x28) = 1000000.0f;
    *(float*)((char*)self + 0xac) = 1000000.0f;
    *(float*)((char*)self + 0x30) = 1000000.0f;
    *(float*)((char*)self + 0xb0) = 1000000.0f;
    float f = 1000.0f - *(float*)((char*)self + 0x18) + *(float*)((char*)tgt + 0x28);
    *(float*)((char*)tgt + 0x28) = f;
    *(float*)((char*)self + 0x18) = 1000.0f;
    return 1;
}

// @ 0x0113e670
int Plugin_SizeA(void* self)
{
    int n = Plugin_GetSizeFir64(*(unsigned char*)((char*)self + 8), 0x40);
    return n + 0xd0;
}

// @ 0x0113e690
bool Plugin_InitC(void* self)
{
    if (self != 0) {
        *(void**)self = g_14bc0fc;
    }
    *(float*)((char*)self + 0x28) = 1000000.0f;
    *(float*)((char*)self + 0xc4) = 1000000.0f;
    *(float*)((char*)self + 0x30) = 1000000.0f;
    *(float*)((char*)self + 0xc8) = 1000000.0f;
    *(void**)((char*)self + 0x0c) = (char*)self + 0x28;
    *(float*)((char*)self + 0x14) = 32.0f;
    void* tgt = *(void**)((char*)self + 8);
    float f = 64.0f - *(float*)((char*)self + 0x18) + *(float*)((char*)tgt + 0x28);
    *(float*)((char*)tgt + 0x28) = f;
    *(float*)((char*)self + 0x18) = 64.0f;
    unsigned ch = *(unsigned char*)((char*)self + 0x21);
    Plugin_GetSizeFir64((int)ch, 0x40);
    unsigned char* buf = (unsigned char*)(((unsigned)self + 0xd7) & ~7u);
    Plugin_CreateFir64(*(void**)((char*)self + 4), (int)ch, 0x40, buf);
    *(unsigned short*)((char*)self + 0xcc) = (unsigned short)(buf - (unsigned char*)self);
    return 1;
}

// ---------------------------------------------------------------------------
// AiffWriter
// ---------------------------------------------------------------------------

// @ 0x0113e770
#pragma warning(push)
#pragma warning(disable:4333)
void AiffWriter_IntToExtended(unsigned char* out, unsigned int val)
{
    unsigned int e = 1;
    for (unsigned int x = val >> 1; x != 0; x >>= 1)
        e++;
    unsigned int mant = val << (32 - e);
    unsigned int be = e + 0x3ffe;
    out[1] = (unsigned char)be;
    out[0] = (unsigned char)(be >> 8);
    out[2] = (unsigned char)(mant >> 24);
    out[3] = (unsigned char)(mant >> 16);
    out[5] = (unsigned char)mant;
    out[4] = (unsigned char)(mant >> 8);
    out[6] = 0;
    out[7] = 0;
    out[8] = 0;
    out[9] = 0;
}
#pragma warning(pop)

// @ 0x0113e7f0
void AiffWriter_Timer(void* self)
{
    unsigned size = (unsigned)*(unsigned char*)((char*)self + 0x20) << 9;
    if (*(unsigned char*)((char*)self + 0x4c) == 0) {
        memset(*(void**)((char*)self + 0x40), 0, size);
    }
    fwrite(*(void**)((char*)self + 0x40), 1, size, *(void**)((char*)self + 0x3c));
    *(unsigned*)((char*)self + 0x44) += 0x100;
    *(unsigned char*)((char*)self + 0x4c) = 0;
}

// @ 0x0113e840
bool AiffWriter_CreateInstance(AiffWriter* self)
{
    if (self != 0) {
        self->vftable = g_14ca66c;
        Sub_112dbb0((char*)self + 0x24);
    }
    *(void**)((char*)self + 0x3c) = 0;
    *(unsigned char*)((char*)self + 0x4c) = 0;
    *(unsigned char*)((char*)self + 0x4d) = 0;
    unsigned size = (unsigned)*(unsigned char*)((char*)self + 0x21) << 9;
    void* p = self->mpSystem->Alloc(size, "rw::audio::core::AiffWriter::mpBuf", 0x10, 0);
    *(void**)((char*)self + 0x40) = p;
    return p != 0;
}

// @ 0x0113e890
int AiffWriter_StartHandler(void* event)
{
    AiffWriter* w = *(AiffWriter**)((char*)event + 4);
    volatile char hdr[0x54];
    hdr[0] = 'P'; hdr[1] = 'l'; hdr[2] = 'a'; hdr[3] = 'c';
    hdr[4] = 'e'; hdr[5] = 'H'; hdr[6] = 'o'; hdr[7] = 'l';
    hdr[8] = 'd'; hdr[9] = 'e'; hdr[10] = 'r'; hdr[11] = 0;
    void* (__cdecl * volatile pMemset)(void*, int, unsigned int) = memset;
    pMemset((void*)((char*)hdr + 12), 0, 0x46);
    if (*(void**)((char*)w + 0x3c) == 0) {
        *(unsigned char*)((char*)w + 0x4d) = 0;
        *(unsigned*)((char*)w + 0x44) = 0;
        *(unsigned*)((char*)w + 0x48) = 0;
        void* fp = fopen((const char*)event + 0xc, "wb");
        *(void**)((char*)w + 0x3c) = fp;
        if (fp != 0) {
            fwrite((const void*)hdr, 1, 0x52, fp);
            TimerManager* tm = (TimerManager*)((char*)w->mpSystem + 0x60);
            bool ok = tm->AddTimer((char*)w + 0x24, (void*)AiffWriter_Timer,
                                   w, "AiffWriter", 0, 1) != 0;
            if (!ok) {
                *(unsigned char*)((char*)w + 0x4d) = 1;
            }
        }
    }
    return *(int*)((char*)event + 8);
}

// @ 0x0113e940
int AiffWriter_StopHandler(void* event)
{
    AiffWriter* w = *(AiffWriter**)((char*)event + 4);
    if (*(void**)((char*)w + 0x3c) != 0) {
        fseek(*(void**)((char*)w + 0x3c), 0, 0);
        unsigned int n = (unsigned)*(unsigned char*)((char*)w + 0x20) *
                         *(unsigned*)((char*)w + 0x44) * 2;
        unsigned int formSize = n + 0x4a;
        char hdr[8];
        strncpy(hdr, "FORM", 4);
        hdr[4] = (char)(formSize >> 24);
        hdr[5] = (char)(formSize >> 16);
        hdr[6] = (char)(formSize >> 8);
        hdr[7] = (char)formSize;
        fwrite(hdr, 1, 8, *(void**)((char*)w + 0x3c));
        strncpy(hdr, "AIFF", 4);
        fwrite(hdr, 1, 4, *(void**)((char*)w + 0x3c));
        char comm[8];
        strncpy(comm, "COMM", 4);
        comm[4] = 0; comm[5] = 0; comm[6] = 0; comm[7] = 0x12;
        fwrite(comm, 1, 8, *(void**)((char*)w + 0x3c));
        unsigned char ext[10];
        AiffWriter_IntToExtended(ext, *(unsigned*)((char*)w + 0x48));
        unsigned char body[0x12];
        memset(body, 0, 0x12);
        body[1] = 0x10;
        body[2] = (unsigned char)((unsigned)*(unsigned char*)((char*)w + 0x20) >> 8);
        body[3] = *(unsigned char*)((char*)w + 0x20);
        body[4] = *(unsigned char*)((char*)w + 0x47);
        body[5] = *(unsigned char*)((char*)w + 0x46);
        body[6] = *(unsigned char*)((char*)w + 0x45);
        body[7] = *(unsigned char*)((char*)w + 0x44);
        memcpy(&body[8], ext, 10);
        fwrite(body, 1, 0x12, *(void**)((char*)w + 0x3c));
        char inst[8];
        strncpy(inst, "INST", 4);
        inst[4] = 0; inst[5] = 0; inst[6] = 0; inst[7] = 0x14;
        fwrite(inst, 1, 8, *(void**)((char*)w + 0x3c));
        unsigned char instData[0x14];
        memset(instData, 0, 0x14);
        instData[0] = 0x3c;
        instData[3] = 0x7f;
        instData[5] = 0x7f;
        fwrite(instData, 1, 0x14, *(void**)((char*)w + 0x3c));
        unsigned int ssnd = n + 8;
        strncpy(comm, "SSND", 4);
        comm[4] = (char)(ssnd >> 24);
        comm[5] = (char)(ssnd >> 16);
        comm[6] = (char)(ssnd >> 8);
        comm[7] = (char)ssnd;
        fwrite(comm, 1, 8, *(void**)((char*)w + 0x3c));
        unsigned char zero8[8];
        memset(zero8, 0, 8);
        fwrite(zero8, 1, 8, *(void**)((char*)w + 0x3c));
        fclose(*(void**)((char*)w + 0x3c));
        *(void**)((char*)w + 0x3c) = 0;
        if (*(unsigned char*)((char*)w + 0x4d) != 0) {
            ((System*)(*(void**)((char*)w + 4)))->RemoveTimerPtr((char*)w + 0x24);
            *(unsigned char*)((char*)w + 0x4d) = 0;
        }
    }
    return 8;
}

// @ 0x0113ebb0
void AiffWriter::ReleaseEvent()
{
    int ev[8];
    memset(ev, 0, sizeof(ev));
    ev[1] = (int)this;
    AiffWriter_StopHandler(ev);
    if (*(void**)((char*)this + 0x40) != 0) {
        ((System*)(*(void**)((char*)this + 4)))->Free(*(void**)((char*)this + 0x40), 0);
    }
}

// @ 0x0113ebe0
void AiffWriter::PostCommand(int sel, const char** str)
{
    System* sys = this->mpSystem;
    unsigned index = sys->mCommandIndex;
    char* base = sys->mpCommandBuffer;
    if (sel == 0) {
        const char* s = *str;
        unsigned len = strlen(s);
        unsigned size = (len + 0x10) & ~3u;
        Cmd* c = (Cmd*)(base + index);
        sys->mCommandIndex = index + size;
        c->fn = (void*)0x113e890;
        c->obj = this;
        *(unsigned*)((char*)c + 8) = size;
        char* dst = (char*)c + 0xc;
        const char* src = s;
        char ch;
        do {
            ch = *src;
            *dst = ch;
            src++;
            dst++;
        } while (ch != 0);
    } else {
        Cmd* c = (Cmd*)(base + index);
        sys->mCommandIndex = index + 8;
        c->fn = (void*)0x113e940;
        c->obj = this;
    }
}

// ---------------------------------------------------------------------------
// Dac device thread + factory
// ---------------------------------------------------------------------------

// @ 0x0113def0
int Dac_ThreadEntry(Dac* self)
{
    self->Thread();
    return 0;
}

// @ 0x0113dc00
void Dac::Thread()
{
    timeBeginPeriod(1);
    unsigned long t0 = timeGetTime();
    *(unsigned*)((char*)this + 0x78) = t0;
    unsigned long local1c = t0;
    g_16e7b98 = g_16e7b9c;
    System* sys = *(System**)((char*)this + 4);
    sys->Lock();
    if (g_16e6307 == 0) {
        goto done;
    }
    for (;;) {
        if (g_16e7b98 == 0) {
            sys->ExecuteCommands();
            if (g_16e6307 == 0) break;
        } else if (g_16e7b98 == 1) {
            g_16e7ba8 = 1;
            unsigned char* p = (unsigned char*)*(void**)((char*)this + 0x40) + 0x10;
            long old = _InterlockedExchangeAdd((volatile long*)p, 0);
            if ((old & 1) != 0) {
                if (*(unsigned char*)((char*)this + 0x9c) == 0) {
                    this->Func_cf70();
                } else if (g_16e7b9c != 2) {
                    g_16e6304 = 1;
                    *(int*)((char*)this + 0x5c) = 0;
                    double d = sys->mSystemTime;
                    *(unsigned*)((char*)this + 0x58) = 0x447a0000;
                    *(double*)((char*)this + 0x80) = d + 10.0;
                    d = sys->mSystemTime;
                    *(int*)((char*)this + 0x68) = 5;
                    *(double*)((char*)this + 0x70) = d + 1.0;
                    this->Func_d9f0();
                    g_16e7b9c = 1;
                }
            }
            *(unsigned*)((char*)this + 0x7c) = *(unsigned*)((char*)this + 0x78);
            *(unsigned*)((char*)this + 0x78) = timeGetTime();
            int n = this->Func_d5d0();
            int saved = *(int*)((char*)this + 0x5c);
            while (n > 0) {
                sys->ExecuteCommands();
                if (g_16e6307 == 0) goto done;
                if (g_16e7b9c != 1) goto afterloop;
                int v;
                if (*(int*)((char*)this + 0x68) < 1) {
                    v = this->Func_ce00();
                } else {
                    v = 0;
                }
                if (*(unsigned char*)((char*)this + 0x9c) == 0) {
                    unsigned char ch = *(unsigned char*)((char*)this + 0x89);
                    unsigned int off = (unsigned)(*(int*)((char*)this + 0x5c) * ch);
                    void* sink = *(void**)((char*)this + 0x50);
                    void* p1 = 0;
                    unsigned n1 = 0;
                    void* p2 = 0;
                    unsigned n2 = 0;
                    SinkLock lockFn = (SinkLock)(*(void***)sink)[0x2c / 4];
                    int r = lockFn(sink, off, (unsigned)ch << 8, &p1, &n1, &p2, &n2, 0);
                    int out = (int)p1;
                    if (r < 0) out = 0;
                    if (out == 0) {
                        this->Func_cf70();
                    } else {
                        this->Func_cff0(out, v);
                        unsigned char ch2 = *(unsigned char*)((char*)this + 0x89);
                        SinkUnlock unlockFn = (SinkUnlock)(*(void***)sink)[0x4c / 4];
                        int r2 = unlockFn(sink, (void*)out, (unsigned)ch2 << 8, 0, 0);
                        if (r2 < 0) {
                            this->Func_cf70();
                        } else {
                            *(int*)((char*)this + 0x5c) += 0x100;
                            if (*(int*)((char*)this + 0x5c) >= *(int*)((char*)this + 0x60)) {
                                *(int*)((char*)this + 0x5c) -= *(int*)((char*)this + 0x60);
                            }
                        }
                    }
                    if (*(unsigned char*)((char*)this + 0x9c) != 0) {
                        *(double*)((char*)this + 0x90) += 256.0;
                    }
                } else {
                    *(double*)((char*)this + 0x90) += 256.0;
                }
                n -= 0x100;
            }
        afterloop:
            if (g_16e7b9c == 1) {
                this->Func_d200(saved);
            }
        }
        if (*(int*)((char*)this + 0x68) > 0) {
            (*(int*)((char*)this + 0x68))--;
        }
        local1c += 0x14;
        unsigned long now = timeGetTime();
        long dt = (long)local1c - (long)now;
        int sleepMs;
        if (dt < 0 || dt > 0xc8) sleepMs = 1; else sleepMs = (int)dt;
        if (g_16e7b9c != 0 && g_16e7b98 != 2) {
            g_16e7ba4 += 1 - g_16e7ba8;
        }
        int x = g_16e7b98;
        if (g_16e7b98 != g_16e7b9c) {
            if (g_16e7b98 == 2) sys->Lock();
            x = g_16e7b9c;
            if (g_16e7b9c == 2) {
                sys->Unlock();
                x = g_16e7b9c;
            }
        }
        g_16e7b98 = x;
        Sleep(sleepMs);
        if (g_16e6307 == 0) break;
    }
done:
    timeEndPeriod(1);
    if (g_16e7b98 != 2) {
        sys->Unlock();
    }
}

// @ 0x0113df10
bool Dac_CreateInstance(Dac* self)
{
    if (self != 0) {
        *(void**)self = g_14c2fa8;
    }
    *(void**)((char*)self + 0x0c) = (char*)self + 0x28;
    void* region = (void*)(((unsigned)self + 0xa7) & ~7u);
    *(void**)((char*)self + 0x40) = region;
    Sub_743b50(region);
    *(void**)((char*)self + 0x24) = 0;
    g_16e7bbc = 0;
    System* sys = *(System**)((char*)self + 4);
    Sub_1154f00(g_16e7ba0, 0, sys);
    g_16e6300 = sys->CreateVoicePool();
    if (g_16e6300 == 0) {
        return false;
    }
    void* mixer = sys->Alloc(0x30080, 0, 0x80, 0);
    *(void**)((char*)self + 0x24) = mixer;
    if (mixer != 0) {
        Sub_1154e50(mixer);
        *(void**)((char*)self + 0x24) = mixer;
    }
    void* m = *(void**)((char*)self + 0x24);
    if (m == 0) {
        return false;
    }
    *(void**)((char*)m + 0x30008) = sys;
    g_16e6304 = 0;
    *(float*)((char*)self + 0x38) = 0.0f;
    g_16e6306 = 0;
    g_16e633c = 0;
    *(float*)((char*)self + 0x30) = 48000.0f;
    *(float*)((char*)self + 0x28) = 1.0f;
    g_16e6305 = 2;
    float rate = *(float*)((char*)self + 0x30);
    float inv = 256.0f / rate;
    *(float*)((char*)sys + 0xc0) = rate;
    *(float*)((char*)sys + 0xbc) = inv;
    *(float*)((char*)sys + 0x98) = inv;
    *(float*)((char*)self + 0x54) = 45.0f;
    *(void**)((char*)self + 0x48) = 0;
    *(void**)((char*)self + 0x4c) = 0;
    *(void**)((char*)self + 0x50) = 0;
    *(unsigned*)((char*)self + 0x78) = 0;
    *(unsigned*)((char*)self + 0x7c) = 0;
    g_16e6307 = 1;
    Sub_68c1b0((char*)*(void**)((char*)self + 0x40) + 8, 0, 0, 0);
    bool ok = self->Func_d930() != 0;
    if (ok) {
        void* p = *(void**)((char*)self + 0x48);
        if (p != 0) {
            ((void(__stdcall*)(void*))(*(void***)p)[2])(p);
            *(void**)((char*)self + 0x48) = 0;
        }
    }
    *(float*)((char*)self + 0x28) = 1.0f;
    g_16e6305 = g_14c2fa0[1];
    Sub_743b50((char*)self + 0x2c);
    Sub_922900((char*)self + 0x14);
    unsigned char desc[0x14];
    System* sys2 = *(System**)((char*)self + 4);
    *(int*)&desc[0x00] = *(int*)((char*)sys2 + 0xec);
    *(int*)&desc[0x04] = *(int*)((char*)sys2 + 0xe8);
    *(int*)&desc[0x08] = *(unsigned char*)((char*)sys2 + 0xf6);
    desc[0x0c] = 0;
    *(void**)&desc[0x10] = (void*)"RWAudioCore Dac";
    void* cb = Sub_922920();
    int handle = Sub_922f30((char*)self + 0x2c, 0, (void*)0x113def0, self, desc, cb);
    void* h = (void*)handle;
    sys2->SetThreadHandle(&h);
    Sub_11548d0(*(void**)((char*)self + 0x40));
    Sub_922e10((char*)self + 0x2c);
    return true;
}
