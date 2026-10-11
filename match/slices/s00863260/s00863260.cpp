// Slice s00863260 - libjpeg 6a glue / memory-manager internals (SporeApp.exe)
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
//
// Many of these are internal libjpeg routines that were built with whole-program
// optimisation, so the original passes some arguments in fixed registers (EAX/ECX/ESI).
// They are rewritten here with explicit arguments; complete source, not byte-exact.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

#define NULL 0

// ------------------------------------------------------------------ runtime
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                                 // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
#pragma function(memset)
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" char* __cdecl strcpy(char* dst, const char* src);
extern "C" int   __cdecl strncmp(const char* a, const char* b, unsigned int n);
extern "C" char* __cdecl strncpy(char* dst, const char* src, unsigned int n);
extern "C" __declspec(dllimport,noreturn) void __cdecl longjmp(void* jb, int val);  // msvcr90!longjmp
extern "C" int   __cdecl setjmp3(void* jb, int arg);                               // 0x011e0cac

// ------------------------------------------------------------------ libjpeg
namespace lib_jpeg {
    void* jpeg_std_error(void* errmgr);
    void  jpeg_destroy(void* cinfo);
    void  jpeg_stdio_src(void* cinfo, void* io);
}
extern "C" void FUN_00857730(void* cinfo, int a, int size);
extern "C" void FUN_00857820(void* cinfo, int marker, void* reader);
extern "C" void FUN_00857bf0(void* cinfo, int a);
extern "C" void FUN_00857e10(void* cinfo);
extern "C" void FUN_00857d70(void* cinfo, void* buf, int n);
extern "C" void FUN_00857b20(void* cinfo);
extern "C" void* FUN_00862ef0(void* cinfo, int a, int b);  // alloc helper (jmemmgr)
extern "C" int  FUN_00862d80(void* cinfo, int a, int b, int c);
extern "C" void FUN_00862e80(void* cinfo, void* p, int n);
extern "C" int  FUN_00863100(void* cinfo, int a, int b, int c);
extern "C" int  FUN_008631b0(void* cinfo, int a, int b, int c);
extern "C" void FUN_008668f0(void* p, int n);              // jzero_far
extern "C" void FUN_00862d60(void* cinfo, void* p, int n); // jpeg_free_small

extern "C" int FUN_008634e0(void* cinfo, int* arr, int write);
extern "C" int FUN_00863580(void* cinfo, int* arr, int write);
extern "C" int FUN_00863620(void* cinfo, int* arr, u32 start, u32 rows, int writable);
extern "C" int FUN_00863770(void* cinfo, int* arr, u32 start, u32 rows, int writable);
extern "C" void FUN_008638c0(void* cinfo, int pool_id);
extern "C" void FUN_00863b10(u8* src, u8* dst);
extern "C" void FUN_00863b70(u8* dst, u8* src, int count1, int count2, int fmt, int flag);
extern "C" int FUN_00863c50(void* cinfo);
extern "C" int FUN_00863d50(void* cinfo);
extern "C" void FUN_00863e40(void* cinfo);
extern "C" int __stdcall FUN_00864000(void** out, void* io, int a3, int a4);

// ================================================================ 0x00863260
// Original region holds three libjpeg jmemmgr routines back-to-back; this is the
// first (allocate a small control block and push it on the pool's +0x40 list).
// @ 0x00863260
int* FUN_00863260(void* cinfo, int size, int a3, int a4, int a5, int a6)
{
    int  pool = ((int*)cinfo)[1];
    int* p;
    if (size != 1) {
        *(int*)(((int*)cinfo)[0] + 0x14) = 0xc;   // error code BAD_ALLOC
        *(int*)(((int*)cinfo)[0] + 0x18) = size;
        (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
    }
    p = (int*)FUN_00862ef0(cinfo, size, 0x80);
    p[1] = a5;
    p[2] = a4;
    p[0] = 0;
    p[3] = a6;
    p[8] = a3;
    p[10] = 0;
    p[0xb] = *(int*)(pool + 0x40);
    *(int**)(pool + 0x40) = p;
    return p;
}

// ================================================================ 0x008634e0
// realize one virtual array (element size taken straight from the control block).
// @ 0x008634e0
int FUN_008634e0(void* cinfo, int* arr, int write)
{
    int elem = arr[2];
    int rows = arr[4];
    int off  = arr[6] * elem;
    int done = 0;
    void** mem = (void**)(unsigned)arr[0];

    while (done < rows) {
        int n = rows - done;
        int t;
        if ((int)arr[5] < n) n = arr[5];
        t = arr[7] - (arr[6] + done);
        if (t <= n) n = t;
        t = arr[1] - (arr[6] + done);
        if (t <= n) n = t;
        if (n < 1) return 0;
        n = n * elem;
        if (write == 0)
            ((void (*)(void*, void*, void*, int, int))(unsigned)arr[0xc])(cinfo, arr + 0xc, mem[done], off, n);
        else
            ((void (*)(void*, void*, void*))(unsigned)arr[0xd])(cinfo, arr + 0xc, mem[done]);
        done += arr[5];
        rows = arr[4];
        off += n;
    }
    return 0;
}

// ================================================================ 0x00863580
// same as above but for a 128-byte item stride (block arrays).
// @ 0x00863580
int FUN_00863580(void* cinfo, int* arr, int write)
{
    int esz  = arr[2] << 7;
    int rows = arr[4];
    int off  = arr[6] * esz;
    int done = 0;
    void** mem = (void**)(unsigned)arr[0];

    while (done < rows) {
        int n = rows - done;
        int t;
        if ((int)arr[5] < n) n = arr[5];
        t = arr[7] - (arr[6] + done);
        if (t <= n) n = t;
        t = arr[1] - (arr[6] + done);
        if (t <= n) n = t;
        if (n < 1) return 0;
        n = n * esz;
        if (write == 0)
            ((void (*)(void*, void*, void*, int, int))(unsigned)arr[0xc])(cinfo, arr + 0xc, mem[done], off, n);
        else
            ((void (*)(void*, void*, void*))(unsigned)arr[0xd])(cinfo, arr + 0xc, mem[done]);
        done += arr[5];
        rows = arr[4];
        off += n;
    }
    return 0;
}

// ================================================================ 0x00863620
// access a virtual block array (libjpeg access_virt_barray).
// @ 0x00863620
int FUN_00863620(void* cinfo, int* arr, u32 start, u32 rows, int writable)
{
    u32 end = start + rows;
    u32 i;
    int* mem;
    int base, cnt;

    if ((u32)arr[1] < end || (u32)arr[3] < rows || arr[0] == 0) {
        *(int*)(((int*)cinfo)[0] + 0x14) = 0x14;
        (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
    }
    if (start < (u32)arr[6] || (u32)(arr[4] + arr[6]) < end) {
        if (arr[10] == 0) {
            *(int*)(((int*)cinfo)[0] + 0x14) = 0x44;
            (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
        }
        if (arr[9] != 0) {
            FUN_008634e0(cinfo, arr, 1);
            arr[9] = 0;
        }
        if ((u32)arr[6] < start) {
            arr[6] = (int)start;
        } else {
            int t = (int)(end - arr[4]);
            if (t < 0) t = 0;
            arr[6] = t;
        }
        FUN_008634e0(cinfo, arr, 0);
    }
    i = arr[7];
    if (i < end) {
        if (i < start) {
            i = start;
            if (writable != 0) {
                *(int*)(((int*)cinfo)[0] + 0x14) = 0x14;
                (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
            }
        }
        if (writable != 0) arr[7] = (int)end;
        if (arr[8] != 0) {
            int first = arr[6];
            int sz = arr[2];
            mem = (int*)(unsigned)arr[0];
            for (; (int)i - first < (int)end - first; i++)
                FUN_008668f0((void*)(unsigned)mem[i - first], sz);
            goto done;
        }
        if (writable == 0) {
            *(int*)(((int*)cinfo)[0] + 0x14) = 0x14;
            (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
            return (unsigned)arr[0] + (start - arr[6]) * 4;
        }
    }
    else {
done:
        if (writable == 0) goto ret;
    }
    arr[9] = 1;
ret:
    base = (unsigned)arr[0];
    cnt  = (int)start - arr[6];
    return base + cnt * 4;
}

// ================================================================ 0x00863770
// access a virtual sample array (128-byte items).
// @ 0x00863770
int FUN_00863770(void* cinfo, int* arr, u32 start, u32 rows, int writable)
{
    u32 end = start + rows;
    u32 i;

    if ((u32)arr[1] < end || (u32)arr[3] < rows || arr[0] == 0) {
        *(int*)(((int*)cinfo)[0] + 0x14) = 0x14;
        (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
    }
    if (start < (u32)arr[6] || (u32)(arr[4] + arr[6]) < end) {
        if (arr[10] == 0) {
            *(int*)(((int*)cinfo)[0] + 0x14) = 0x44;
            (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
        }
        if (arr[9] != 0) {
            FUN_00863580(cinfo, arr, 1);
            arr[9] = 0;
        }
        if ((u32)arr[6] < start) {
            arr[6] = (int)start;
        } else {
            int t = (int)(end - arr[4]);
            if (t < 0) t = 0;
            arr[6] = t;
        }
        FUN_00863580(cinfo, arr, 0);
    }
    i = arr[7];
    if (i < end) {
        if (i < start) {
            i = start;
            if (writable != 0) {
                *(int*)(((int*)cinfo)[0] + 0x14) = 0x14;
                (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
            }
        }
        if (writable != 0) arr[7] = (int)end;
        if (arr[8] != 0) {
            int first = arr[6];
            int sz = arr[2] << 7;
            for (; (int)i - first < (int)end - first; i++)
                FUN_008668f0((void*)(unsigned)((int*)(unsigned)arr[0])[i - first], sz);
            goto done;
        }
        if (writable == 0) {
            *(int*)(((int*)cinfo)[0] + 0x14) = 0x14;
            (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
            return (unsigned)arr[0] + (start - arr[6]) * 4;
        }
    }
    else {
done:
        if (writable == 0) goto ret;
    }
    arr[9] = 1;
ret:
    return (unsigned)arr[0] + ((int)start - arr[6]) * 4;
}

// ================================================================ 0x008638c0
// destroy the small/large pools of the memory manager (libjpeg jpeg_mem_term).
// @ 0x008638c0
void FUN_008638c0(void* cinfo, int pool_id)
{
    int  pool = ((int*)cinfo)[1];
    int* p;
    int  i;
    int* q;

    if (pool_id < 0 || pool_id >= 2) {
        *(int*)(((int*)cinfo)[0] + 0x14) = 0xc;
        *(int*)(((int*)cinfo)[0] + 0x18) = pool_id;
        (*(void(**)(void*))((int*)cinfo)[0])(cinfo);
    }
    if (pool_id == 1) {
        for (p = *(int**)(pool + 0x40); p != 0; p = *(int**)((char*)p + 0x2c)) {
            if (*(int*)((char*)p + 0x28) != 0) {
                *(int*)((char*)p + 0x28) = 0;
                (*(void(**)(void*, void*))((char*)p + 0x38))(cinfo, (char*)p + 0x30);
            }
        }
        p = *(int**)(pool + 0x44);
        *(int*)(pool + 0x40) = 0;
        for (; p != 0; p = *(int**)((char*)p + 0x2c)) {
            if (*(int*)((char*)p + 0x28) != 0) {
                *(int*)((char*)p + 0x28) = 0;
                (*(void(**)(void*, void*))((char*)p + 0x38))(cinfo, (char*)p + 0x30);
            }
        }
        *(int*)(pool + 0x44) = 0;
    }
    p = *(int**)(pool + 0x38 + pool_id * 4);
    *(int*)(pool + 0x38 + pool_id * 4) = 0;
    while (p != 0) {
        int* nxt = *(int**)p;
        int n = p[2] + 0x10 + p[1];
        FUN_00862d60(cinfo, p, n);
        *(int*)(pool + 0x48) -= n;
        p = nxt;
    }
    q = *(int**)(pool + 0x30 + pool_id * 4);
    *(int*)(pool + 0x30 + pool_id * 4) = 0;
    while (q != 0) {
        int* nxt = *(int**)q;
        int n = q[2] + 0x10 + q[1];
        FUN_00862d60(cinfo, q, n);
        *(int*)(pool + 0x48) -= n;
        q = nxt;
    }
    (void)i;
}

// ================================================================ 0x00863b10
// convert one packed 4-byte pixel to the inverted (negative) 3-byte form.
// @ 0x00863b10
void FUN_00863b10(u8* src, u8* dst)
{
    u32 v2 = src[3];
    i32 c1 = (u8)(src[0] + v2);
    u32 v3, v4;
    if (0xfe < src[0] + v2) c1 = -1;
    v3 = src[1] + v2;
    if (0xfe < v3) v3 = 0xff;
    v4 = v2 + src[2];
    if (0xfe < v4) v4 = 0xff;
    dst[0] = (u8)(-1 - c1);
    dst[1] = (u8)(-1 - (signed char)v3);
    dst[2] = (u8)(-1 - (signed char)v4);
}

// ================================================================ 0x00863b70
// null color conversion / sample reorder used by the decoder.
// @ 0x00863b70
void FUN_00863b70(u8* dst, u8* src, int count1, int count2, int fmt, int flag)
{
    int i;
    if (flag == 0) {
        if (fmt == 1) {
            strncpy((char*)dst, (char*)src, (u32)count2);
        }
        else if (fmt == 4) {
            u8 tmp[4];
            u8* p = dst + 2;
            while (count2 > 0) {
                FUN_00863b10(src, tmp);
                p[1] = 0xff;
                p[0] = tmp[0];
                p[-1] = tmp[1];
                p[-2] = tmp[2];
                p += 4;
                src += 4;
                count2--;
            }
        }
        else if (count2 > 0) {
            u8* s = src + 2;
            u8* d = dst + 2;
            do {
                d[1] = 0xff;
                d[0] = s[-2];
                d[-1] = s[-1];
                d[-2] = s[0];
                s += 3;
                d += 4;
            } while (--count2 != 0);
        }
    }
    else {
        u8* s = src + 2;
        i = 0;
        while (i < count1) {
            s[(int)((char*)dst - (char*)src) + 1] = s[-2];
            s[(int)((char*)dst - (char*)src)]     = s[-1];
            dst[i * 4 + 1] = s[0];
            dst[i * 4]     = s[1];
            i++;
            s += 4;
        }
    }
}

// ================================================================ 0x00863c50
// APP0 reader: detect the "GIMEXARGB" signature (libjpeg marker processor).
// @ 0x00863c50
int FUN_00863c50(void* cinfo)
{
    int* src = *(int**)((char*)cinfo + 0x14);
    u8*  p = (u8*)(unsigned)src[0];
    int  n = src[1];
    u8   a, b;
    int  i, rem;
    char buf[12];

    if (n == 0) {
        n = (*(int(**)(void*))(unsigned)src[3])(cinfo);
        if (n == 0) return 0;
        p = (u8*)(unsigned)src[0];
        n = src[1];
    }
    a = *p; n--; p++;
    if (n == 0) {
        n = (*(int(**)(void*))(unsigned)src[3])(cinfo);
        if (n == 0) return 0;
        p = (u8*)(unsigned)src[0];
        n = src[1];
    }
    b = *p;
    rem = ((int)a << 8 | b) - 2;
    n--; p++;
    if (rem > 8) {
        i = 0;
        do {
            if (n == 0) {
                n = (*(int(**)(void*))(unsigned)src[3])(cinfo);
                if (n == 0) return 0;
                p = (u8*)(unsigned)src[0];
                n = src[1];
            }
            buf[i] = (char)*p;
            i++; n--; p++;
        } while (i < 9);
        rem = ((int)a << 8 | b) - 0xb;
    }
    if (strncmp(buf, "GIMEXARGB", 9) == 0)
        *(int*)0x01650394 = 1;
    src[0] = (int)(unsigned)p;
    src[1] = n;
    if (rem > 0)
        (*(void(**)(void*, int))(*(int*)((char*)cinfo + 0x14) + 0x10))(cinfo, rem);
    return 1;
}

// ================================================================ 0x00863d50
// COM reader: pull a comment block into cinfo+0x130 (libjpeg comment processor).
// @ 0x00863d50
int FUN_00863d50(void* cinfo)
{
    int* src = *(int**)((char*)cinfo + 0x14);
    u8*  p = (u8*)(unsigned)src[0];
    int  n = src[1];
    u32  len, i;

    if (n == 0) {
        n = (*(int(**)(void*))(unsigned)src[3])(cinfo);
        if (n == 0) return 0;
        p = (u8*)(unsigned)src[0];
        n = src[1];
    }
    {
        u8 a = *p; n--; p++;
        if (n == 0) {
            n = (*(int(**)(void*))(unsigned)src[3])(cinfo);
            if (n == 0) return 0;
            p = (u8*)(unsigned)src[0];
            n = src[1];
        }
        len = ((u32)a << 8 | *p) - 2;
        n--; p++;
    }
    *(u32*)((char*)cinfo + 0x530) = len;
    if (len >= 0x400) *(u32*)((char*)cinfo + 0x530) = 0x3ff;
    i = 0;
    while (i < *(u32*)((char*)cinfo + 0x530)) {
        if (i >= 0x400) break;
        if (n == 0) {
            n = (*(int(**)(void*))(unsigned)src[3])(cinfo);
            if (n == 0) return 0;
            p = (u8*)(unsigned)src[0];
            n = src[1];
        }
        ((u8*)((char*)cinfo + 0x130))[i] = *p;
        i++; n--; p++;
        len--;
    }
    ((u8*)((char*)cinfo + 0x130))[i] = 0;
    src[0] = (int)(unsigned)p;
    src[1] = n;
    if ((int)len > 0)
        (*(void(**)(void*, int))(*(int*)((char*)cinfo + 0x14) + 0x10))(cinfo, (int)len);
    return 1;
}

// ================================================================ 0x00863e40
// error_exit: longjmp back into the client (libjpeg jpeg_error_mgr.error_exit).
// @ 0x00863e40
void FUN_00863e40(void* cinfo)
{
    longjmp((void*)(*(int*)cinfo + 0x84), 1);
}

// ================================================================ 0x00863e60
// @ 0x00863e60
u8* JPG_about(void)
{
    u8* d = (u8*)galloc(0x100);
    if (d != NULL) {
        memset(d, 0, 0x100);
        *(u32*)(d + 0x00) = 0x4a504547;                 // "JPEG"
        *(u32*)(d + 0x04) = 0x100;
        *(u32*)(d + 0x08) = 0x159;
        *(u32*)(d + 0x14) = 0;
        *(u32*)(d + 0x18) = 0x50;
        *(u32*)(d + 0x1c) = 0x4a504547;
        *(u32*)(d + 0x0c) = (*(u32*)(d + 0x0c) & 0xffffb3d7) | 0xb3d7;
        strcpy((char*)(d + 0x3c), ".jpg");
        strcpy((char*)(d + 0x44), ".jpeg");
        strcpy((char*)(d + 0x4c), ".jfif");
        strcpy((char*)(d + 0x7c), "FrANK G. Barchard");
        strcpy((char*)(d + 0x9c), "1.12");
        *(u32*)(d + 0xa4) = 0x47504a;
        strcpy((char*)(d + 0xac), "JPeg");
        strcpy((char*)(d + 0xbc), "JPeg");
    }
    return d;
}

// ================================================================ 0x00863f90
// @ 0x00863f90
int __stdcall JPG_is(void* io)
{
    u8  buf[4];
    u32 v;
    int r = 0;
    gseek(io, 0, 0);
    if (gread(io, buf, 4) != 0) {
        v = ((u32)buf[0] << 24) | ((u32)buf[1] << 16) | ((u32)buf[2] << 8) | buf[3];
        if (v == 0xffd8ffe0 || v == 0xffd8ffe1 || v == 0xffd8ffed)
            r = 0x63;
    }
    return r;
}

// ================================================================ 0x00864000
// @ 0x00864000
int __stdcall FUN_00864000(void** out, void* io, int a3, int a4)
{
    int  ok = 0;
    int* h = (int*)galloc(0x18);
    if (h != 0) {
        h[3] = 0;
        h[5] = 0;
        h[2] = 1;
        h[0] = 0x4a504547;
        h[1] = 0x18;
        h[4] = (int)io;
        *out = h;
        ok = 1;
    }
    return ok;
}

// ================================================================ 0x00864050
// JPG_info: fully decode a JPEG once to learn its dimensions/comment, then build
// the GIMEX descriptor.
// @ 0x00864050
void* __stdcall FUN_00864050(void* handle, int a2)
{
    u8   dec[0x5d8];
    u8   jmpbuf[64];
    u8   errmgr[0x40];
    u8   comment[1024];
    void* local_10 = 0;
    int  local_1c = 1;
    int  i;
    int  local_18, local_14, local_20, local_c, local_8;
    unsigned local_c8 = 0;
    int  local_588, local_57c;
    unsigned local_584, local_56c;
    char local_4dc;
    u16  local_4da;
    void* local_5f4;
    u32* d;
    int  rc;

    *(void**)(dec + 8) = lib_jpeg::jpeg_std_error(errmgr);
    *(void**)(dec + 0) = (void*)&FUN_00863e40;
    local_5f4 = *(void**)(dec + 4);

    rc = setjmp3(jmpbuf, 0);
    if (rc != 0) {
        lib_jpeg::jpeg_destroy(dec);
        return NULL;
    }
    FUN_00857730(dec + 4, 0x3d, 0x5d8);
    FUN_00857820(dec + 4, 0xed, (void*)&FUN_00863c50);
    FUN_00857820(dec + 4, 0xfe, (void*)&FUN_00863d50);
    gseek(*(void**)((u8*)handle + 0x10), 0, 0);
    lib_jpeg::jpeg_stdio_src(dec + 4, *(void**)((u8*)handle + 0x10));
    *(int*)0x01650394 = 0;
    FUN_00857bf0(dec + 4, 1);
    local_18 = *(int*)0x01650394;
    FUN_00857e10(dec + 4);
    local_14 = *(int*)(dec + 0x70);
    local_20 = *(unsigned*)(dec + 0x74);
    local_588 = *(int*)(dec + 0x70);
    local_584 = *(unsigned*)(dec + 0x74);
    local_57c = *(int*)(dec + 0x7c);
    local_56c = *(unsigned*)(dec + 0x8c);
    local_4dc = *(char*)(dec + 0x11c);
    local_4da = *(u16*)(dec + 0x11e);
    local_c = 0;
    if (local_4dc != 0)
        local_c = local_4da;
    {
        int  eax = local_57c * local_588;
        void* p;
        p = (*(void*(**)(void*, int, int, int))((char*)local_5f4 + 8))(dec + 4, 1, eax, 1);
        while (local_56c < local_584)
            FUN_00857d70(dec + 4, p, 1);
    }
    FUN_00857b20(dec + 4);
    lib_jpeg::jpeg_destroy(dec + 4);
    if (local_1c != 0) {
        local_8 = 0x18;
        if (local_57c == 1)
            local_8 = 8;
        d = (u32*)galloc(0x2a70);
        local_10 = NULL;
        if (d != NULL) {
            local_10 = d;
            memset(d, 0, 0x2a70);
            d[0] = 0x4a504547;
            d[1] = 0x2a70;
            d[2] = 0x159;
            d[3] = 0;
            d[4] = local_14;
            d[5] = local_20;
            d[0x10a] = (local_18 != 0);
            d[0x10b] = 1;
            d[0x10c] = 0x46;
            d[0x10e] = 0;
            d[0x10f] = 8;
            d[0x110] = 8;
            d[0x111] = 8;
            d[0x112] = 0;
            d[0x113] = 0;
            d[0x114] = 0;
            d[0x115] = 0;
            d[0x116] = 0;
            *(float*)((u8*)d + 0x2a5c) = (float)(int)local_c;
            *(u8*)((u8*)d + 0x45c) = 0;
            if (local_8 < 0xf) {
                d[6] = 8;
                d[7] = 8;
                d[9] = 0x100;
                {
                    u8* p = (u8*)d + 0x2a;
                    for (i = 0; i < 0x100; i++) {
                        p[1] = 0xff; p[0] = (u8)i; p[-1] = (u8)i; p[-2] = (u8)i; p += 4;
                    }
                }
            }
            else {
                d[6] = 0x20;
                d[7] = local_8;
                d[9] = 0;
            }
            strncpy((char*)d + 0x65c, (char*)comment, local_c8);
            return d;
        }
    }
    return local_10;
}
