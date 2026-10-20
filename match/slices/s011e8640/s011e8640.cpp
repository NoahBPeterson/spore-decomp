// Slice s011e8640 -- RenderWare 4 core: rw::core::filesys::AsyncOp (DoWrite/SetPriority/
// GetStatus/GetResultHandle/GetResultSize/DoClose/Read/Write/DoOpen/Close/Open) and
// rw::core::stdc string helpers (StringCopy, StringAppend, StringCompare, ...) plus the
// double/float-to-ASCII conversion helpers ConvertfToA / ConvertDtoA / ConvertGtoA and
// the printf %s/%ls emitters.
//
// RenderWare 4 core: built with VC .NET 2003 (cl 13.10) AND /GL+/LTCG
// (symbols/renderware4_core.txt) => equivalence-only; flags /vc71.
//
// Compiled with: /vc71 /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <new>

typedef unsigned short wchar_t_;

// ---------------------------------------------------------------------------
// out-of-slice helpers (real addresses)
// ---------------------------------------------------------------------------
struct AsyncOp;
struct Device;
struct Handle;

struct FsManager {                                   // 07 style manager (retail +0x10)
    char pad[0x10];
    Device* mpDefaultDevice;                         // 0x10
    char pad2[0x14];
    int mMaxReadSize;                                // 0x24
};
FsManager* __cdecl GetFsManager();                   // 0x011e58f0

struct Allocator {
    virtual void v0();
    virtual void* Alloc(unsigned int size, const char* name, unsigned int flags, unsigned int align, unsigned int offset); // +0x04
    virtual void Free(void* p);                      // +0x08
};
extern Allocator* g_AllocatorManager;                // 0x016f4b10

void* __cdecl StreamImplOperatorNew(unsigned int size);                 // 0x011e6d20
void* __cdecl MemoryCopy(void* dst, const void* src, unsigned int n);   // 0x011ea910
void  __cdecl f_011ecf40(Handle* h);                                    // 0x011ecf40 (Handle close)
int   __cdecl ieee_ftol2(void);                                         // 0x011e0846 ftol2

typedef void (*CompletionCallback)(AsyncOp* op);
typedef int (*DoIoCallback)(AsyncOp* op);

// io interface: the transfer slots are thiscall members (this in ecx)
class StreamIo {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual int  slot14(void* key, void* buf, unsigned int want, void* drv, void* ctxKey);
    virtual int  slot18(void* key, void* buf, unsigned int count, void* drv, void* ctxKey);
    virtual unsigned __int64 slot1c(void* key, unsigned __int64 pos, unsigned int flags, void* drv, void* ctxKey);
    virtual unsigned __int64 slot20(void* key);
    virtual void slot24();
    virtual void slot28();
    virtual unsigned int slot2c();
};
// the "stream" object AsyncOp::mFileHandle points at (IoStream in the X360 model)
struct IoStream {
    char pad0[4];
    struct Ctx {
        char pad[8];
        void* mDriverKey;                            // +0x08
        Device* mpDevice;                            // +0x0c
        char pad2[0x10];
        unsigned __int64 mLeadPos;                   // +0x20
    };
    Ctx* mpContext;                                  // +0x04
    void* mDriverKey;                                // +0x08
    Device* mpDevice;                                // +0x0c
    StreamIo* mpIo;                                  // +0x10
    char pad14[4];
    unsigned __int64 mWritePos;                      // +0x18
};

struct Handle {
    unsigned int mField0;                            // +0x00
    unsigned int mField1;                            // +0x04
    unsigned int mbIsOpen;                           // +0x08
    unsigned int mField3;                            // +0x0c
    void* mpDevice;                                  // +0x10
    unsigned int pad14;                              // +0x14
    unsigned __int64 mu64Size;                       // +0x18
    unsigned int pad20;                              // +0x20
    unsigned int pad24;                              // +0x24
    Handle(const char* path, unsigned int posHi, Device* device) throw();   // 0x011ecdf0
    void Close();                                    // 0x011ecf40
    void* operator new(unsigned int size);           // 0x011e6d20
};

struct Device {
    char pad0[4];
    char mRunning;                                   // +0x04
    char mTerminate;                                 // +0x05
    char mIsVirtual;                                 // +0x06
    char pad7[0x119];
    void* mDriver;                                   // +0x120
    int InsertOp(AsyncOp* op);                       // 0x011e6340
    void Wait(const AsyncOp* op, const unsigned int* timeout);     // 0x011e5da0
    int ChangeOpPriority(AsyncOp* op, int prio);                   // 0x011e6450
    void* Open(const char* name, unsigned int flags, Handle** out); // 0x011e5b80
};

Device* __cdecl DeviceGetInstance(const char* name, int shared);   // 0x011e5ff0

struct ListNodeS { ListNodeS* next; };

struct AsyncOp : ListNodeS {                         // size 0x48
    int mStatus;                                     // 0x004
    bool mCancelled;                                 // 0x008
    bool mIsRead;                                    // 0x009
    int mPriority;                                   // 0x00c
    IoStream* mFileHandle;                           // 0x010
    void* mContext;                                  // 0x014
    CompletionCallback mCallbackFunc;                // 0x018
    unsigned __int64 mValue;                         // 0x020
    unsigned __int64 mAmount;                        // 0x028
    void* mData;                                     // 0x030
    unsigned __int64 mTotalBytes;                    // 0x038
    Device* mDevice;                                 // 0x040
    DoIoCallback mExecFunc;                          // 0x044

    void SetPriority(int prio);
    int GetStatus(const unsigned int& wait);
    void* GetResultHandle();
    unsigned __int64 GetResultSize();

    void Read(IoStream* stream, void* data, unsigned __int64 pos, unsigned __int64 amount,
              CompletionCallback cb, void* context, int prio);
    void Write(IoStream* stream, void* data, unsigned __int64 pos, unsigned __int64 amount,
               CompletionCallback cb, void* context, int prio);
    void Close(IoStream* stream, CompletionCallback cb, void* context, int prio);
    void Open(const char* name, unsigned int flags, CompletionCallback cb, void* context, int prio);

    // static transfer callbacks (the same-TU free functions below)

};

void __cdecl NoOpCallback(AsyncOp* op);              // 0x011fb220
int  __cdecl AsyncOpDoRead(AsyncOp* op);             // 0x011e8550
int  __cdecl AsyncOpDoClose(AsyncOp* op);            // 0x011e87d0
int  __cdecl AsyncOpDoOpen(AsyncOp* op);             // 0x011e8920

// ---------------------------------------------------------------------------
// rw::core::stdc
// ---------------------------------------------------------------------------
char* StringCopy(char* dst, const char* src);        // 0x011e8b20
char* StringAppend(char* dst, const char* src);      // 0x011e8b50
int  StringCompare(const char* a, const char* b);    // 0x011e8b90
int  StringCompareNoCase(const char* a, const char* b);   // 0x011e8bd0
int  StringLength(const char* s);                    // 0x011e8c40
char* StringFindChar(const char* s, char c);         // 0x011e8c60
void ConvertDtoA(double value, int* exp10, double* mantissa);          // 0x011e8c90
int  ConvertfToA(char* out, double value, unsigned int decimals);      // 0x011e8f10
char* ConvertfToALow(char* out, double value, unsigned int decimals, char e);  // 0x011e9090
char* ConvertfToAHigh(char* out, double value, unsigned int decimals, char e); // 0x011e9100
void ConvertIToA(int value, char* out, int base);    // 0x011ed0f0
char* ConvertGtoA(char* out, double value, int width, char upper);     // 0x011e91a0
void __cdecl BuildWideString(unsigned short* out, const char* src);   // 0x011ed270

struct UnsizedList {
    void* mpNode;                                    // +0x00
    void* mpNext;                                    // +0x04
    void* mpPrev;                                    // +0x08
    void* mpOwner;                                   // +0x0c
};

// ---------------------------------------------------------------------------
// AsyncOp::DoWrite  (exec callback for Write)
// ---------------------------------------------------------------------------
// @ 0x011e8640
int __cdecl AsyncOpDoWrite(AsyncOp* op)
{
    IoStream* stream = op->mFileHandle;
    stream->mpContext->mLeadPos = stream->mpIo->slot1c(stream->mDriverKey, op->mValue, 0,
                                                       ((Device*)stream->mpContext->mpDevice)->mDriver,
                                                       stream->mpContext->mDriverKey);
    int written = stream->mpIo->slot18(stream->mDriverKey, op->mData, (unsigned int)op->mAmount,
                                       ((Device*)stream->mpContext->mpDevice)->mDriver,
                                       stream->mpContext->mDriverKey);
    op->mAmount = (unsigned int)written;
    stream->mpContext->mLeadPos += (unsigned int)written;
    stream->mWritePos = stream->mpIo->slot20(stream->mDriverKey);
    op->mTotalBytes += op->mAmount;
    return 1;
}

// @ 0x011e8920
int __cdecl AsyncOpDoOpen(AsyncOp* op)
{
    UnsizedList list;
    Handle* handle = new Handle((const char*)op->mData, (unsigned int)op->mValue, op->mDevice);
    op->mFileHandle = (IoStream*)handle;
    list.mpNext = 0;
    list.mpPrev = 0;
    list.mpOwner = 0;
    list.mpNode = op->mData;
    g_AllocatorManager->Free(&list);
    IoStream* stream = op->mFileHandle;
    if (((Handle*)stream)->mbIsOpen)
        return 1;
    if (stream)
    {
        ((Handle*)stream)->Close();
        list.mpNext = 0;
        list.mpPrev = 0;
        list.mpOwner = 0;
        list.mpNode = stream;
        g_AllocatorManager->Free(&list);
    }
    op->mFileHandle = 0;
    return -2;
}

// @ 0x011e8710
void AsyncOp::SetPriority(int prio)
{
    if (mPriority != prio)
    {
        Device* dev = mDevice;
        if (dev->mIsVirtual)
            dev = GetFsManager()->mpDefaultDevice;
        dev->ChangeOpPriority(this, prio);
    }
}

// @ 0x011e8740
int AsyncOp::GetStatus(const unsigned int& wait)
{
    if (wait != 0)
    {
        Device* dev = mDevice;
        if (dev->mIsVirtual)
            dev = GetFsManager()->mpDefaultDevice;
        dev->Wait(this, &wait);
    }
    return mStatus;
}

// @ 0x011e8770
void* AsyncOp::GetResultHandle()
{
    Device* dev = mDevice;
    if (dev->mIsVirtual)
        dev = GetFsManager()->mpDefaultDevice;
    dev->Wait(this, (const unsigned int*)0x014f6584);
    return mFileHandle;
}

// @ 0x011e87a0
unsigned __int64 AsyncOp::GetResultSize()
{
    Device* dev = mDevice;
    if (dev->mIsVirtual)
        dev = GetFsManager()->mpDefaultDevice;
    dev->Wait(this, (const unsigned int*)0x014f6584);
    return mTotalBytes;
}

// @ 0x011e87d0
int __cdecl AsyncOpDoClose(AsyncOp* op)
{
    IoStream* stream = op->mFileHandle;
    if (stream)
    {
        ((Handle*)stream)->Close();
        UnsizedList list = {};
        list.mpNode = stream;
        g_AllocatorManager->Free(&list);
    }
    op->mFileHandle = 0;
    return 1;
}

// @ 0x011e8820
void AsyncOp::Read(IoStream* stream, void* data, unsigned __int64 pos, unsigned __int64 amount,
                   CompletionCallback cb, void* context, int prio)
{
    mStatus = 0;
    mCancelled = false;
    mIsRead = true;
    mFileHandle = stream;
    mValue = pos;
    mAmount = amount;
    mData = data;
    mContext = context;
    mPriority = prio;
    mTotalBytes = 0;
    mDevice = stream->mpDevice;
    CompletionCallback fn = cb;
    if (fn == 0)
        fn = NoOpCallback;
    mCallbackFunc = fn;
    mExecFunc = AsyncOpDoRead;
    mDevice->InsertOp(this);
}

// @ 0x011e88a0
void AsyncOp::Write(IoStream* stream, void* data, unsigned __int64 pos, unsigned __int64 amount,
                    CompletionCallback cb, void* context, int prio)
{
    mStatus = 0;
    mCancelled = false;
    mIsRead = false;
    mFileHandle = stream;
    mValue = pos;
    mAmount = amount;
    mData = data;
    mContext = context;
    mPriority = prio;
    mTotalBytes = 0;
    mDevice = stream->mpDevice;
    CompletionCallback fn = cb;
    if (fn == 0)
        fn = NoOpCallback;
    mCallbackFunc = fn;
    mExecFunc = AsyncOpDoWrite;
    mDevice->InsertOp(this);
}

// @ 0x011e89e0
void AsyncOp::Close(IoStream* stream, CompletionCallback cb, void* context, int prio)
{
    mStatus = 0;
    mPriority = prio;
    mContext = context;
    mCancelled = false;
    mIsRead = false;
    mFileHandle = stream;
    CompletionCallback fn = cb;
    if (fn == 0)
        fn = NoOpCallback;
    mCallbackFunc = fn;
    mValue = 0;
    mAmount = 0;
    mData = 0;
    mTotalBytes = 0;
    mDevice = stream->mpDevice;
    mExecFunc = AsyncOpDoClose;
    mDevice->InsertOp(this);
}

// @ 0x011e8a40
void AsyncOp::Open(const char* name, unsigned int flags, CompletionCallback cb, void* context, int prio)
{
    Device* dev = DeviceGetInstance(name, 0);
    int len = StringLength(name) + 1;
    mStatus = 0;
    mCancelled = false;
    mIsRead = false;
    mPriority = prio;
    mFileHandle = 0;
    mContext = context;
    mValue = flags;
    mAmount = 0;
    mData = 0;
    mTotalBytes = 0;
    mDevice = 0;
    mExecFunc = AsyncOpDoOpen;
    mData = g_AllocatorManager->Alloc(len, "rw::core::filesystem::Manager::Allocate", 0, 4, 0);
    MemoryCopy(mData, name, len);
    mDevice = dev;
    mCallbackFunc = cb;
    if (cb == 0)
        mCallbackFunc = NoOpCallback;
    if (dev->mIsVirtual)
        dev = GetFsManager()->mpDefaultDevice;
    dev->InsertOp(this);
}

// ---------------------------------------------------------------------------
// rw::core::stdc string helpers
// ---------------------------------------------------------------------------
// @ 0x011e8b20
char* StringCopy(char* dst, const char* src)
{
    char* d = dst;
    char c = *src;
    while (c != 0)
    {
        *d = c;
        ++d;
        c = *++src;
    }
    *d = 0;
    return dst;
}

// @ 0x011e8b50
char* StringAppend(char* dst, const char* src)
{
    char* d = dst;
    char c = *d;
    while (c != 0)
    {
        ++d;
        c = *d;
    }
    c = *src;
    while (c != 0)
    {
        *d = c;
        ++d;
        ++src;
        c = *src;
    }
    *d = 0;
    return dst;
}
// @ 0x011e8b90
int StringCompare(const char* a, const char* b)
{
    while (*a != 0 && *a == *b)
    {
        ++a;
        ++b;
    }
    if (*a > *b)
        return 1;
    return (*a >= *b) - 1;
}

// @ 0x011e8bd0
int StringCompareNoCase(const char* a, const char* b)
{
    char ca, cb;
    do
    {
        ca = *a++;
        cb = *b++;
        if (ca >= 'A' && ca <= 'Z' && cb >= 'a' && cb <= 'z')
            ca += ' ';
        else if (ca >= 'a' && ca <= 'z' && cb >= 'A' && cb <= 'Z')
            ca -= ' ';
    } while (ca != 0 && cb != 0 && ca == cb);
    if (ca > cb)
        return 1;
    return ca < cb ? -1 : 0;
}

// @ 0x011e8c40
int StringLength(const char* s)
{
    int n = 0;
    char c = *s;
    while (c != 0)
    {
        ++s;
        ++n;
        c = *s;
    }
    return n;
}

// @ 0x011e8c60
char* StringFindChar(const char* s, char c)
{
    char ch = *s;
    for (;;)
    {
        if (ch == 0)
        {
            if (*s != c)
                s = 0;
            return (char*)s;
        }
        if (c == ch)
            return (char*)s;
        ++s;
        ch = *s;
    }
}

// ---------------------------------------------------------------------------
// double / float to ASCII
// ---------------------------------------------------------------------------
// @ 0x011e8c90
void ConvertDtoA(double value, int* exp10, double* mantissa)
{
    double x = value;
    *exp10 = 0;
    if (x == 0.0)
    {
        *mantissa = 0.0;
        return;
    }
    bool neg = x < 0.0;
    x = x < 0.0 ? -x : x;
    if (x < 1.0 && x <= 1e-10)
    {
        int n = 0;
        do
        {
            x *= 10000000000.0;
            n -= 10;
        } while (x <= 1e-10);
        *exp10 = n;
    }
    if (x < 1.0)
    {
        while (x < 1.0)
        {
            x *= 10.0;
            (*exp10)--;
        }
    }
    else
    {
        if (x >= 10000000000.0)
        {
            int n = 0;
            do
            {
                x *= 1e-10;
                n += 10;
            } while (x >= 10000000000.0);
            *exp10 = n;
        }
        while (x >= 10.0)
        {
            x *= 0.1;
            (*exp10)++;
        }
    }
    if (*exp10 == -312)
    {
        *mantissa = 0.0;
        *exp10 = 999;
        return;
    }
    if (neg)
        x = -x;
    *mantissa = x;
}

// @ 0x011e8e00
// recursive digit emitter used by ConvertfToA
static int EmitInt(char*& out, double value, unsigned int roundDigit, int decimals, int* exp10)
{
    int pos = *exp10;
    --decimals;
    *exp10 = pos + 1;
    if (pos + 1 > 0x2d)
        return (int)(size_t)out;
    int digit;
    if (value > 9.223372036854776e18 || value < -9.223372036854776e18)
        digit = 0;
    else
    {
        __int64 v = (__int64)value;
        if (v < 0)
            v = 0;
        digit = (int)(v % 10);
    }
    if (roundDigit != 0)
    {
        digit += roundDigit;
        if (digit == 10)
            digit = 0;
        else
            roundDigit = 0;
    }
    if (value >= 10.0 || decimals >= 0)
        EmitInt(out, value * 0.1, roundDigit, decimals, exp10);
    else if (digit == 0 && roundDigit == 1)
    {
        *out++ = '1';
    }
    if (decimals == 0)
        *out++ = '.';
    *out++ = (char)(digit + '0');
    return (int)(size_t)out;
}

// @ 0x011e8f10
int ConvertfToA(char* out, double value, unsigned int decimals)
{
    unsigned int udec = decimals;
    char* p = out;
    unsigned int hi = *(unsigned int*)((char*)&value + 4);
    if (((hi & 0xffe00000) == 0xffe00000 || (hi & 0x7fe00000) == 0x7fe00000)
        && (*(unsigned int*)&value != 0 || (hi != 0xfff00000 && hi != 0x7ff00000)))
    {
        p[0] = '#';
        p[1] = 'N';
        p[2] = 'A';
        p[3] = 'N';
        p[4] = 0;
        return (int)(size_t)(p + 4);
    }
    if (value < 0.0)
    {
        *p++ = '-';
        value = -value;
    }
    char* start = p;
    double scale = 1.0;
    unsigned int i = udec;
    while (i != 0)
    {
        scale *= 10.0;
        --i;
    }
    // The original's remainder is an unsigned 64-bit modulo (it calls aullrem,
    // not allrem) but the rounding test compares the low word signed.
    unsigned long long rem = (unsigned long long)(scale * value * 10.0) % 10u;
    int roundDigit = (int)rem > 4 ? 1 : 0;
    int ex = 0;
    char* end = (char*)(size_t)EmitInt(p, scale * value, roundDigit, (int)udec, &ex);
    if (ex > 0x2d)
    {
        *start = '?';
        if ((int)udec > 0)
        {
            start[1] = '.';
            char* q = start + 2;
            unsigned int n = udec;
            while (n != 0) { *q++ = '?'; --n; }
            start[udec + 2] = 0;
            *end = 0;
            return (int)(size_t)end;
        }
        start[1] = 0;
    }
    *end = 0;
    return (int)(size_t)end;
}

// @ 0x011e9090
char* ConvertfToALow(char* out, double value, unsigned int decimals)
{
    int ex;
    double mantissa;
    ConvertDtoA(value, &ex, &mantissa);
    char* p = (char*)(size_t)ConvertfToA(out, mantissa, decimals);
    *p = 'e';
    ++p;
    if (ex == 999)
    {
        p[0] = '?';
        p[1] = '?';
        p[2] = 0;
        return p;
    }
    ConvertIToA(ex, p, 10);
    return p;
}

// @ 0x011e9100
char* ConvertfToAHigh(char* out, double value, unsigned int decimals)
{
    int ex;
    double mantissa;
    ConvertDtoA(value, &ex, &mantissa);
    char* p = (char*)(size_t)ConvertfToA(out, mantissa, decimals);
    *p = 'E';
    ++p;
    if (ex == 999)
    {
        p[0] = '?';
        p[1] = '?';
        p[2] = 0;
        return p;
    }
    ConvertIToA(ex, p, 10);
    return p;
}

// @ 0x011e9170
static char* TrimZeros(char* p)
{
    while (p[-1] == '0')
    {
        --p;
        *p = 0;
    }
    if (p[-1] == '.')
    {
        --p;
        *p = 0;
    }
    return p;
}

// @ 0x011e91a0
char* ConvertGtoA(char* out, double value, int width, char upper)
{
    int ex;
    double mantissa;
    ConvertDtoA(value, &ex, &mantissa);
    if (ex >= -4 && ex < width)
    {
        ConvertfToA(out, value, width);
        TrimZeros(out + StringLength(out));
        return out;
    }
    char* p = out + StringLength(out);
    TrimZeros(p);
    *p++ = upper ? 'E' : 'e';
    if (ex == 999)
    {
        p[0] = '?';
        p[1] = '?';
        p[2] = 0;
        return p;
    }
    ConvertIToA(ex, p, 10);
    return p;
}

// ---------------------------------------------------------------------------
// scanf-style conversion helpers and the printf %s / %ls emitters
// ---------------------------------------------------------------------------
// @ 0x011e9270
char* __fastcall SkipSign(char* s, char* negFlag, char* zeroFlag)
{
    *negFlag = 0;
    *zeroFlag = 1;
    switch (*s)
    {
    case '-':
        *zeroFlag = 0;
        return s + 1;
    case '0':
        *negFlag = 1;
        // fall through
    case ' ':
    case '#':
    case '+':
        ++s;
        // fall through
    default:
        return s;
    }
}

// @ 0x011e92c0
static void ParseWidth(char* s, int* width)
{
    *width = 0;
    char c = *s;
    while (c > '/' && c < ':')
    {
        *width *= 10;
        *width += *s - '0';
        ++s;
        c = *s;
    }
}

// @ 0x011e9300
static void ParsePrecision(char* s, int* prec)
{
    *prec = 6;
    if (*s != '.')
        return;
    ++s;
    *prec = 0;
    char c = *s;
    if (c > '/' && c < ':')
    {
        do
        {
            int v = *prec;
            *prec = v * 10;
            c = *s;
            ++s;
            *prec = c + v * 10 - '0';
        } while (*s > '/' && *s < ':');
    }
    if (*prec > 10)
        *prec = 10;
}

// @ 0x011e9350
char* EmitStr(char* dst, const char* src, unsigned int* count, int* width, char wide)
{
    static const char kNull[] = "(null)";

    if (wide)
    {
        unsigned short buf[10];
        const unsigned short* ws;
        BuildWideString(buf, kNull);
        ws = src ? (const unsigned short*)src : buf;
        while (*ws != 0)
        {
            if (*count != 0)
            {
                *dst = *(const char*)ws;
                ++dst;
                --*count;
            }
            ++ws;
            ++*width;
        }
        return dst;
    }
    const char* s = src ? src : kNull;
    char c = *s;
    while (c != 0)
    {
        if (*count != 0)
        {
            *dst = c;
            ++dst;
            --*count;
        }
        ++s;
        ++*width;
        c = *s;
    }
    return dst;
}

// @ 0x011e9400
char* EmitStrPadded(char* dst, const char* src, int pad, unsigned int* count, int* width, char wide)
{
    static const char kNull[] = "(null)";
    unsigned short buf[10];
    int len = 0;

    if (wide)
    {
        const unsigned short* ws;
        BuildWideString(buf, kNull);
        ws = src ? (const unsigned short*)src : buf;
        while (*ws != 0)
        {
            if (*count != 0)
            {
                *dst = *(const char*)ws;
                ++dst;
                --*count;
            }
            ++ws;
            ++*width;
            ++len;
        }
    }
    else
    {
        const char* s = src ? src : kNull;
        char c = *s;
        while (c != 0)
        {
            if (*count != 0)
            {
                *dst = c;
                ++dst;
                --*count;
            }
            ++s;
            ++*width;
            ++len;
            c = *s;
        }
    }
    for (pad -= len; pad > 0; --pad)
    {
        if (*count != 0)
        {
            *dst = ' ';
            ++dst;
            --*count;
        }
        ++*width;
    }
    return dst;
}
