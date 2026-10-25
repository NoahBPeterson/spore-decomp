// Heap/sort helpers for a UI list, plus two message dispatchers.
// Elements are pointers to nodes whose +0x24 dword is a priority kind
// (rank: 2 -> 0, 9 -> 1, anything else -> 2).  /O2.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#include <math.h>
#include <xmmintrin.h>
#include <intrin.h>

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;

struct Node {
    char pad[0x24];
    int  mKind;   // +0x24
};

__forceinline int Rank(Node* n)
{
    int k = n->mKind;
    int r = 0;
    if (k != 2)
        r = (k != 9) + 1;
    return r;
}

extern char* g_pTable;   // 0x016c7d90

// ---------------------------------------------------------------------------
// 0x00f07770  priority comparison
// ---------------------------------------------------------------------------
// @ 0x00f07770
bool __stdcall FUN_00f07770(Node* a, Node* b)
{
    int ra = Rank(a);
    int rb = b->mKind == 2 ? 0 : ((b->mKind != 9) + 1);
    int c = ra <= rb;
    return c != 0;
}

// ---------------------------------------------------------------------------
// 0x00f077c0  table lookup + kind switch
// ---------------------------------------------------------------------------
struct Entry { int k, pad1, slot, pad2; };   // 0x10

struct Box {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual int  GetKey();     // +0x10
    virtual void v5(); virtual void v6();
    virtual int  GetKind();    // +0x1c
};

// @ 0x00f077c0
void FUN_00f077c0(Box* box)
{
    int key = box->GetKey();
    Entry* p = 0;
    for (int i = 0; i < 5; ++i) {
        if (((Entry*)g_pTable)[i + 1].k == key) {
            p = &((Entry*)g_pTable)[i + 1];
            break;
        }
    }
    switch (box->GetKind()) {
    case 0xcefa1210: p->slot = 0; return;
    case 0xcefa1220: p->slot = 1; return;
    case 0xcefa1230: p->slot = 2; return;
    case 0xcefa1240: p->slot = 3; return;
    }
    p->slot = 0;
}

// ---------------------------------------------------------------------------
// 0x00f078a0  table lookup accessor
// ---------------------------------------------------------------------------
// @ 0x00f078a0
int FUN_00f078a0()
{
    if (g_pTable)
        return *(int*)(g_pTable + 0xc);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f078b0  float -> bucket index
// ---------------------------------------------------------------------------
// @ 0x00f078b0
int FUN_00f078b0(float* p, float scale)
{
    float v = p[1];
    if (-scale > v)
        return -1;
    if (v > scale * 4.5f)
        return -1;
    if (-100.0f > p[0])
        return -1;
    if (p[0] > 100.0f)
        return -1;
    __m128 q = _mm_set_ss(v / scale);
    q = _mm_cvtsi32_ss(q, _mm_cvtss_si32(q));
    __m128 lo = _mm_setzero_ps();
    __m128 hi = _mm_set_ss(4.0f);
    q = _mm_max_ss(q, lo);
    q = _mm_min_ss(q, hi);
    return _mm_cvttss_si32(q);
}

// ---------------------------------------------------------------------------
// 0x00f07960  x87 blend helper
// ---------------------------------------------------------------------------
// @ 0x00f07960
float FUN_00f07960(float a, float b)
{
    if (fabsf(a - b) < 4.0f)
        return b;
    float v = (b - a) * 0.2f + a;
    if (4.0f <= fabsf(a - v))
        return v;
    float d = b - a;
    return (fabsf(d) / d) * 4.0f + a;
}

// ---------------------------------------------------------------------------
// 0x00f079e0  insertion sort (backward shift)
// ---------------------------------------------------------------------------
// @ 0x00f079e0
void FUN_00f079e0(Node** first, Node** last)
{
    if (last == first)
        return;
    Node** it = first + 1;
    if (last == it)
        return;
    do {
        Node* v = *it;
        Node** q = it;
        while (q != first) {
            int rv = Rank(v);
            int rp = Rank(q[-1]);
            if (rp < rv)
                break;
            *q = q[-1];
            --q;
        }
        *q = v;
        ++it;
    } while (it != last);
}

// ---------------------------------------------------------------------------
// 0x00f07a60  insertion sort (forward shift)
// ---------------------------------------------------------------------------
// @ 0x00f07a60
void FUN_00f07a60(Node** first, Node** last)
{
    for (; first != last; ++first) {
        Node* v = *first;
        Node** p = first;
        Node** q = first;
        for (;;) {
            --q;
            if (Rank(v) > Rank(*q))
                break;
            *p = *q;
            --p;
        }
        *p = v;
    }
}

// ---------------------------------------------------------------------------
// 0x00f07ae0  choose the minimum of three (heap-based)
// ---------------------------------------------------------------------------
// @ 0x00f07ae0
Node** FUN_00f07ae0(Node** a, Node** b, Node** c)
{
    Node* x = *a;
    Node* y = *b;
    if (Rank(y) < Rank(x)) {
        Node* z = *c;
        if (Rank(x) <= Rank(z))
            return a;
        if (FUN_00f07770(y, z))
            return c;
    } else {
        Node* z = *c;
        if (Rank(y) <= Rank(z))
            return b;
        if (FUN_00f07770(x, z))
            return c;
        return a;
    }
    return b;
}

// ---------------------------------------------------------------------------
// 0x00f07bd0  destroy a range of 0x44-byte elements
// ---------------------------------------------------------------------------
extern void FUN_00f280f0(void* self);   // element dtor (thiscall)
struct Destructible { void dtor(); };

// @ 0x00f07bd0
char* FUN_00f07bd0(char* first, char* last, char* out)
{
    if (first != last) {
        do {
            ((Destructible*)(first + 4))->dtor();
            first += 0x44;
            out += 0x44;
        } while (first != last);
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00f07c10  sift-up
// ---------------------------------------------------------------------------
// @ 0x00f07c10
void FUN_00f07c10(Node** heap, int top, int idx, Node* v)
{
    if (idx <= top) {
        heap[idx] = v;
        return;
    }
    for (;;) {
        int parent = (idx - 1) >> 1;
        Node* p = heap[parent];
        if (Rank(p) > Rank(v))
            break;
        heap[idx] = p;
        idx = parent;
        if (idx <= top)
            break;
    }
    heap[idx] = v;
}

// ---------------------------------------------------------------------------
// shared stubs for the two message dispatchers
// ---------------------------------------------------------------------------
struct Msg;

union PtrInt {
    void* p;
    int   i;
};

struct Msg {                    // message handed to the dispatchers
    char   m00[8];
    int    m08;                 // +0x08 message kind (1 / 0x287259f6)
    int    m0c;                 // +0x0c message id
    PtrInt m10;                 // +0x10 payload
    void*  m14;                 // +0x14
    void*  m18;                 // +0x18 payload
    void*  m1c;                 // +0x1c
    void*  m20;                 // +0x20 payload
};

struct SubMsg {                 // object pointed at by Msg::m18 / Msg::m20
    char m00[0x0c];
    int  m0c;                   // +0x0c
};

struct WStr {                   // SP::WString, 16 bytes (eastl string + allocator tag)
    const wchar_t* mBegin;      // +0x00
    const wchar_t* mEnd;        // +0x04
    const wchar_t* mCap;        // +0x08
    unsigned int   mAllocator;  // +0x0c
    void append(const wchar_t* s);              // 0x005c3d90
    void DeallocateSelf();                      // 0x00933960
    void F_0057cb60(const WStr& src);           // 0x0057cb60  operator=
};

struct CharStr {                // eastl::basic_string<char>, 12 bytes
    char* mBegin;
    char* mEnd;
    char* mCap;
};

struct DateTime {               // 8 bytes on the original frame
    int mData[2];
    void Set(int param);                        // 0x0092e3d0
    int  GetParameter(int param);               // 0x0092df80
};

struct CStringStub {            // SP::cString
    char mData[0x14];
    void Ctor(unsigned int a, unsigned int b, const wchar_t* c);  // 0x006b5770
    const wchar_t* GetText();                                     // 0x006b55c0
    void Dtor();                                                  // 0x006b5240
};

struct TextSlots {              // pointed at by g_015f7cf4
    char           m00[0x30];
    const wchar_t* m30;         // +0x30
    char           m34[0x10];
    const wchar_t* m44;         // +0x44
    const wchar_t* m48;         // +0x48
    const wchar_t* m4c;         // +0x4c
    const wchar_t* m50;         // +0x50
    const wchar_t* m54;         // +0x54
};

struct PtrVector {              // vector of smart pointers
    void* mBegin;
    void* mEnd;
    void* mCap;
    void F_00420660(void** value);              // 0x00420660
};

struct TempRef {                // smart-pointer wrapper (one pointer)
    void* mPtr;
    void F_00576620();                          // 0x00576620
};

struct AutoRef {                // wrapper around PhotoHandler::m_c4
    void* F_00a16f40();                         // 0x00a16f40
};

struct LimitStopwatch {
    char mData[0x10];
    void F_0093a480(unsigned int ms, bool b);   // 0x0093a480
};

struct Layout {
    void* F_008105b0(int id, int flag);         // 0x008105b0
};

struct GameTime {
    void F_00b32250(unsigned int id);           // 0x00b32250
};

struct MainWin {
    void F_008143a0();                          // 0x008143a0
};

struct Movie {                  // SP::cSPPlayModeSubModeMovie
    char      m00[0x04];
    char      m04[0x24];        // +0x04 callout-message-box context
    int       m28;              // +0x28 dialog state
    Layout*   m2c;              // +0x2c UI layout
    char      m30[0x0c];
    uint32_t  m3c;              // +0x3c
    uint32_t  m40;              // +0x40
    char      m44[0x10];
    WStr      m54;              // +0x54
    WStr      m64;              // +0x64
    int       m74;              // +0x74
    bool      m78;              // +0x78
    bool      m79;              // +0x79

    void F_00f065d0();                          // 0x00f065d0 ShowUploadProgressDialog
    void F_00f06660();                          // 0x00f06660 ShowSendVideoURLDialog
    void F_00f069a0(int a);                     // 0x00f069a0 BeginRecording
    void F_00f06ac0();                          // 0x00f06ac0 ClearIndicatorTextures
    void F_00f03fc0(int a);                     // 0x00f03fc0
    void F_00f044d0();                          // 0x00f044d0
    void F_00f03e20();                          // 0x00f03e20
    void F_00f03e40();                          // 0x00f03e40
    void F_00f03e90();                          // 0x00f03e90
    void F_00f03fa0();                          // 0x00f03fa0
    void F_00f05790();                          // 0x00f05790
    void F_00f05c40();                          // 0x00f05c40 SendPublicAuth
    void F_00f04bd0();                          // 0x00f04bd0
    void F_00f05b00();                          // 0x00f05b00 CloseUpload
    void F_00f04070(int a);                     // 0x00f04070
    bool F_00f06d40(int msgId, Msg* msg);       // 0x00f06d40
};

struct PhotoHandler {           // handler subobject embedded at Movie+8
    char      m00[0x20];
    int       m20;              // +0x20 = Movie+0x28 dialog state
    Layout*   m24;              // +0x24 = Movie+0x2c UI layout
    char      m28[0x4c];
    CharStr   m74;              // +0x74
    char      m80[0x04];
    CharStr   m84;              // +0x84
    char      m90[0x14];
    WStr      m_a4;             // +0xa4
    bool      m_b4;             // +0xb4
    bool      m_b5;             // +0xb5
    char      m_b6[0x01];
    bool      m_b7;             // +0xb7
    bool      m_b8;             // +0xb8
    char      m_b9[0x01];
    bool      m_ba;             // +0xba
    char      m_bb[0x01];
    bool      m_bc;             // +0xbc
    bool      m_bd;             // +0xbd
    bool      m_be;             // +0xbe
    char      m_bf[0x01];
    uint32_t  m_c0;             // +0xc0
    void*     m_c4;             // +0xc4
    char      m_c8[0x14];
    PtrVector m_dc;             // +0xdc
    char      m_e8[0x08];
    bool      m_f0;             // +0xf0
    bool      m_f1;             // +0xf1
    char      m_f2[0x06];
    LimitStopwatch m_f8;        // +0xf8

    bool F_00f072b0(int msgId, Msg* msg);       // 0x00f072b0
};

extern void*        F_0067dd30();               // 0x0067dd30 ConfigManager
extern void*        F_00607a60();               // 0x00607a60 Pollen::AuthManager
extern int          F_00435e90();               // 0x00435e90 GetRecorderState
extern void         F_00435ed0(unsigned int id, unsigned int state); // 0x00435ed0 RecordEvent2
extern void         F_00809db0(void* ctx, const wchar_t* text);      // 0x00809db0 CalloutMessageBox
extern unsigned char F_0063b890();              // 0x0063b890 GetYTPrompt
extern unsigned char F_0063c0a0();              // 0x0063c0a0 IsLocaleEnglish
extern void         F_0063bc70();               // 0x0063bc70 CreateConnectingDialog
extern void         F_0063c060(bool b);         // 0x0063c060 DestroyConnectingDialog
extern void*        F_00a206f0();               // 0x00a206f0 EA::Audio::GetSystemAT
extern void*        F_0067cb10();               // 0x0067cb10 MovieSystem
extern void*        F_006b1f90(int area);       // 0x006b1f90 SP_GetSaveArea
extern void         F_004af210(void* props, int key, unsigned int* out); // 0x004af210
extern void         F_00935fb0(const wchar_t* url, bool b);          // 0x00935fb0 OpenBrowser
extern WStr*        F_0041e050(WStr* dest, const wchar_t* fmt, ...); // 0x0041e050 WStr_Format
extern void         F_00472fe0(void* dest, const char* fmt, ...);    // 0x00472fe0 string::sprintf
extern void*        F_00f04530(bool b);         // 0x00f04530
extern unsigned char F_0063d170(WStr* a, WStr* b); // 0x0063d170 ConstructVideoURL
extern void*        F_0067ddd0();               // 0x0067ddd0 EffectsManager
extern void*        F_0067caa0();               // 0x0067caa0 WindowManager
extern void*        F_0067dcc0();               // 0x0067dcc0 MessageServer
extern void*        F_00b3d380();               // 0x00b3d380 GameTimeManager

extern const wchar_t g_01667bac[];              // 0x01667bac eastl::gEmptyString16
extern TextSlots*    g_015f7cf4;                // 0x015f7cf4
extern void*         g_015fd918;                // 0x015fd918 app properties

// ---------------------------------------------------------------------------
// 0x00f06d40  message dispatcher (big)
// ---------------------------------------------------------------------------
// @ 0x00f06d40
bool Movie::F_00f06d40(int msgId, Msg* msg)
{
    (void)msgId;
    switch (msg->m08) {
    case 0x287259f6:
        switch (msg->m0c) {
        case 0x56be960:                                 // ShowSendVideoURLDialog
            F_00f06660();
            return true;
        case 0x5665f58: {                               // toggle a config value
            void* cm = F_0067dd30();
            bool on = ((int (__thiscall*)(void*, int))((*(void***)cm)[0x30 / 4]))(cm, 0x5664a8b) != 0;
            void* cm2 = F_0067dd30();
            ((void (__thiscall*)(void*, int, int))((*(void***)cm2)[0x2c / 4]))(cm2, 0x5664a8b, on ? 0 : 1);
            return true;
        }
        case 0x5652348:                                 // ShowUploadProgressDialog
            F_00f065d0();
            return true;
        case 0x5adbea8:
            F_00f03fc0(0);
            F_00f044d0();
            return true;
        case 0x5b5ef51: {                               // begin the YouTube auth flow
            F_00435ed0(0xe76c9b4f, F_00435e90());
            F_00f03e20();
            void* auth = F_00607a60();
            if (!((unsigned char (__thiscall*)(void*))((*(void***)auth)[0x58 / 4]))(auth)) {
                m28 = 8;                                // YouTube login check
                F_00809db0(m04, (const wchar_t*)0x15ad498);
                return true;
            }
            if (((unsigned char (__thiscall*)(void*))((*(void***)auth)[0x24 / 4]))(auth)) {
                m28 = 7;                                // YouTube register check
                F_00809db0(m04, (const wchar_t*)0x15ad48c);
                return true;
            }
            if (F_0063b890()) {
                F_00f03e90();
                return true;
            }
            F_0063bc70();
            F_00f05c40();
            return true;
        }
        case 0x5b5bd80:
            F_00f03fa0();
            m28 = 0;
            F_00f05790();
            return true;
        case 0x5b5ef52: {                               // reset the auth UI
            void* at = F_00a206f0();
            unsigned int v = 0;
            if (at)
                v = ((unsigned int (__thiscall*)(void*))((*(void***)at)[0x20 / 4]))(at);
            F_00435ed0(0xe76c9b4f, v);
            void* win = m2c->F_008105b0(0x5b5ef50, 1);
            ((void (__thiscall*)(void*, int, int))((*(void***)win)[0x7c / 4]))(win, 1, 0);
            F_00f044d0();
            return true;
        }
        case 0x5baefc8:                                 // open the signup page
            if (!F_0063c0a0()) {
                F_00f03fa0();
                m28 = 0xc;                              // English signup warning
                F_00809db0(m04, (const wchar_t*)0x15ad4bc);
                return true;
            }
            F_00935fb0((const wchar_t*)0x13ff35c, true);
            return true;
        case 0x5b5ef53:                                 // open the terms page
            F_00435ed0(0xe76c9b4f, F_00435e90());
            if (F_0063c0a0()) {
                F_00935fb0((const wchar_t*)0x13ff398, true);
                return true;
            }
            F_00f03e20();
            m28 = 0xd;                                  // English TOS warning
            F_00809db0(m04, (const wchar_t*)0x15ad4bc);
            return true;
        case 0x78d57d0:
        case 0x78ec978: {
            // ---- media capture / YouTube metadata ---------------------------
            void* msys = F_0067cb10();
            if (((unsigned char (__thiscall*)(void*))((*(void***)msys)[0x30 / 4]))(msys)) {
                ((void (__thiscall*)(void*))((*(void***)msys)[0x38 / 4]))(msys);
                return true;
            }

            WStr s1, s2, s3, s4, s5;
            DateTime dt;
            CStringStub cs;

            s1.mBegin = s1.mEnd = g_01667bac; s1.mCap = g_01667bac + 1;
            s2.mBegin = s2.mEnd = g_01667bac; s2.mCap = g_01667bac + 1;
            s3.mBegin = s3.mEnd = g_01667bac; s3.mCap = g_01667bac + 1;
            s4.mBegin = s4.mEnd = g_01667bac; s4.mCap = g_01667bac + 1;
            s5.mBegin = s5.mEnd = g_01667bac; s5.mCap = g_01667bac + 1;

            F_0041e050(&s1, (const wchar_t*)0x13f5c04, (const wchar_t*)0x13ff420);
            g_015f7cf4->m54 = s1.mBegin;

            dt.Set(2);
            F_0041e050(&s5, (const wchar_t*)0x13f5bf8, dt.GetParameter(1));
            g_015f7cf4->m44 = s5.mBegin;
            F_0041e050(&s4, (const wchar_t*)0x13f5bec, dt.GetParameter(2));
            g_015f7cf4->m48 = s4.mBegin;
            F_0041e050(&s3, (const wchar_t*)0x13f5bec, dt.GetParameter(6));
            g_015f7cf4->m4c = s3.mBegin;
            F_0041e050(&s2, (const wchar_t*)0x13f5bcc,
                       dt.GetParameter(0xa), dt.GetParameter(9), dt.GetParameter(8));
            g_015f7cf4->m50 = s2.mBegin;

            cs.Ctor(0x7518573e, 0x5dbc9ee, 0);
            m54.append(cs.GetText());
            void* area = F_006b1f90(0x11ac197);
            const wchar_t* name =
                (const wchar_t*)((unsigned int (__thiscall*)(void*))((*(void***)area)[0x28 / 4]))(area);
            m64.append(name);

            F_004af210(g_015fd918, 0x456f975, &m3c);
            F_004af210(g_015fd918, 0x456f976, &m40);
            ((void (__thiscall*)(void*, const wchar_t*, uint32_t*))((*(void***)msys)[0x2c / 4]))
                (msys, m54.mBegin, &m3c);

            m78 = true;
            m79 = false;
            F_00f03e40();
            m74 = 0;
            cs.Dtor();
            s1.DeallocateSelf();
            s2.DeallocateSelf();
            s3.DeallocateSelf();
            s4.DeallocateSelf();
            s5.DeallocateSelf();
            return true;
        }
        case 0x78d57d8:
            F_00f069a0(0);                              // BeginRecording
            return true;
        default:
            break;
        }
        return false;
    case 1:
        if (msg->m10.i == 0xd && m28 == 3) {
            F_00f065d0();
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00f072b0  message dispatcher (big)
// ---------------------------------------------------------------------------
// @ 0x00f072b0
bool PhotoHandler::F_00f072b0(int msgId, Msg* msg)
{
    TempRef tmp;

    switch (msgId) {
    case 0x7c651b1: {
        void* gtm = F_00b3d380();
        ((GameTime*)gtm)->F_00b32250(0x4bf38a7);

        void* q = m_c4;
        if (q) {
            ((void (__thiscall*)(void*, int))((*(void***)q)[0x0c / 4]))(q, 0);
            q = m_c4;
            if (q) {
                m_c4 = 0;
                ((void (__thiscall*)(void*))((*(void***)q)[0x04 / 4]))(q);
            }
        }

        if (!m_f1) {
            void* em = F_0067ddd0();
            unsigned char (__thiscall* play)(void*, int, int, void*) =
                (unsigned char (__thiscall*)(void*, int, int, void*))((*(void***)em)[0x2c / 4]);
            void* param = ((AutoRef*)&m_c4)->F_00a16f40();
            unsigned char ok = play(em, 0x44ed103, 0, param);
            if (ok) {
                void* r = m_c4;
                ((void (__thiscall*)(void*, int))((*(void***)r)[0x08 / 4]))(r, 0);
            }
        }

        if (m_f1) {
            void* wm = F_0067caa0();
            void* w = ((void* (__thiscall*)(void*))((*(void***)wm)[0x04 / 4]))(wm);
            if (w)
                ((MainWin*)((char*)w - 4))->F_008143a0();
            else
                ((MainWin*)0)->F_008143a0();
        } else {
            m_f8.F_0093a480(0x1f4, true);
        }
        return false;
    }
    case 0x7c651b0: {
        void* p = F_00f04530(1);
        tmp.mPtr = p;
        if (p)
            _InterlockedIncrement((volatile long*)((char*)p + 8));
        m_dc.F_00420660(&tmp.mPtr);
        tmp.F_00576620();
        return false;
    }
    case 0x7d62123:
        m_f0 = false;
        ((Movie*)((char*)this - 8))->F_00f04070(1);
        return false;
    case 0x7e1e46d: {
        Movie* movie = (Movie*)((char*)this - 8);
        movie->F_00f06ac0();                            // ClearIndicatorTextures
        movie->F_00f04070(1);
        return false;
    }
    }

    if (m24 == 0)
        return false;

    switch (msgId) {
    case 0x55e5212: {
        int a = msg->m10.i;
        int b = msg->m08;
        if (a)
            m_b5 = true;
        else
            m_b8 = true;
        if (b) {
            if (a) {
                m_b4 = true;
                return false;
            }
            F_00472fe0(&m74, (const char*)0x13f5b98, ((SubMsg*)msg->m18)->m0c);
            F_00472fe0(&m84, (const char*)0x13f5b98, ((SubMsg*)msg->m20)->m0c);
            m_b7 = true;
            return false;
        }
        m_b4 = false;
        m_b7 = false;
        m_c0 = (uint32_t)msg->m18;
        return false;
    }
    case 0x44db12e: {
        if (msg == 0)
            return false;
        int st = m20;
        if (st != 7 && st != 8)
            return false;
        if (m_bd) {
            m_be = true;
            return false;
        }
        if (F_0063b890()) {
            ((Movie*)((char*)this - 8))->F_00f03e90();
            return false;
        }
        F_0063bc70();
        ((Movie*)((char*)this - 8))->F_00f05c40();
        return false;
    }
    case 0x55e8be4: {
        if (msg->m08)
            m_ba = true;
        if (!m_ba) {
            m_c0 = (uint32_t)msg->m10.p;
            m_bc = true;
            return false;
        }
        WStr url;
        url.mBegin = url.mEnd = g_01667bac; url.mCap = g_01667bac + 1;
        F_0041e050(&url, (const wchar_t*)0x13f5c04,
                   (const wchar_t*)((SubMsg*)msg->m10.p)->m0c);
        if (!F_0063d170(&url, &m_a4))
            m_a4.F_0057cb60(url);
        g_015f7cf4->m30 = m_a4.mBegin;
        url.DeallocateSelf();
        m_bc = true;
        return false;
    }
    case 0x5b98f52: {
        int st = m20;
        if (st != 7 && st != 8)
            return false;
        ((Movie*)((char*)this - 8))->F_00f05790();
        return false;
    }
    case 0x5b96086: {
        void* auth = F_00607a60();
        if (!((unsigned char (__thiscall*)(void*))((*(void***)auth)[0x58 / 4]))(auth))
            return false;
        ((Movie*)((char*)this - 8))->F_00f044d0();
        return false;
    }
    case 0x5bd6378:
        m_bd = true;
        return false;
    case 0x5dd52c7:
        m_bd = false;
        if (!m_be)
            return false;
        m_be = false;
        if (F_0063b890()) {
            ((Movie*)((char*)this - 8))->F_00f03e90();
            return false;
        }
        F_0063bc70();
        ((Movie*)((char*)this - 8))->F_00f05c40();
        return false;
    case 0x5d2c5c0: {
        F_0063c060(false);
        void* ctx = (void*)((char*)this - 4);
        F_00809db0(ctx, (const wchar_t*)0x15ad4b0);
        m20 = 0xb;
        tmp.mPtr = (void*)0x55e7aed;
        void* ms = F_0067dcc0();
        ((void (__thiscall*)(void*, int, void**, int))((*(void***)ms)[0x14 / 4]))
            (ms, 0x5d313c7, &tmp.mPtr, 0);
        return true;
    }
    case 0x62ff413:
        ((Movie*)((char*)this - 8))->F_00f04bd0();
        return false;
    case 0x62ff414:
    case 0x62ff415:
        ((Movie*)((char*)this - 8))->F_00f05b00();
        return false;
    default:
        break;
    }
    return false;
}
