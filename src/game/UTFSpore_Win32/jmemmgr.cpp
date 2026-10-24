// src/game/UTFSpore_Win32/jmemmgr.cpp -- migrated from slice(s) s00863260 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/jmemmgr.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char* a, const char* b, unsigned int n);
extern "C" char* __cdecl strncpy(char* dst, const char* src, unsigned int n);
extern "C" void* FUN_00862ef0(void* cinfo, int a, int b);  // alloc helper (jmemmgr)
extern "C" void FUN_008668f0(void* p, int n);              // jzero_far
extern "C" void FUN_00862d60(void* cinfo, void* p, int n); // jpeg_free_small
extern "C" int FUN_008634e0(void* cinfo, int* arr, int write);
extern "C" int FUN_00863580(void* cinfo, int* arr, int write);
extern "C" void FUN_008638c0(void* cinfo, int pool_id);
extern "C" int FUN_00863c50(void* cinfo);
extern "C" int FUN_00863d50(void* cinfo);
#pragma function(memset)

// ---- items of slice s00863260 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
extern "C" __declspec(dllimport) int __cdecl strncmp(const char* a, const char* b, unsigned int n);
extern "C" char* __cdecl strncpy(char* dst, const char* src, unsigned int n);
extern "C" void* FUN_00862ef0(void* cinfo, int a, int b);  // alloc helper (jmemmgr)
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
// ---- items of slice s00863260 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" int FUN_00863620(void* cinfo, int* arr, u32 start, u32 rows, int writable);
extern "C" int FUN_00863770(void* cinfo, int* arr, u32 start, u32 rows, int writable);
extern "C" void FUN_00863b10(u8* src, u8* dst);
extern "C" void FUN_00863b70(u8* dst, u8* src, int count1, int count2, int fmt, int flag);

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

// The retail 0x008634e0/0x00863580 receive the virtual array in ESI (an LTCG
// usercall), so they cannot be entered through a normal C++ call. Reproduce the
// realization loop locally for the targets below.
static int RealizeVirtLocal(void* cinfo, int* arr, int write, int esz)
{
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
            ((void (__fastcall*)(void*, void*, void*, void*, void*, int, int))(unsigned)arr[0xc])(
                mem[done], cinfo, cinfo, arr + 0xc, mem[done], off, n);
        else
            ((void (__fastcall*)(void*, void*, void*, void*, void*))(unsigned)arr[0xd])(
                (void*)(unsigned)arr[0xd], arr + 0xc, cinfo, arr + 0xc, mem[done]);
        done += arr[5];
        rows = arr[4];
        off += n;
    }
    return 0;
}

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
            RealizeVirtLocal(cinfo, arr, 1, arr[2]);
            arr[9] = 0;
        }
        if ((u32)arr[6] < start) {
            arr[6] = (int)start;
        } else {
            int t = (int)(end - arr[4]);
            if (t < 0) t = 0;
            arr[6] = t;
        }
        RealizeVirtLocal(cinfo, arr, 0, arr[2]);
    }
    i = arr[7];
    if (i < end) {
        if (i < start) {
            i = start;
            if (writable != 0) {
                int* err = (int*)(unsigned)((int*)cinfo)[0];
                err[5] = 0x14;
                ((void (__fastcall*)(void*, void*, void*))(unsigned)err[0])(
                    (void*)(unsigned)err[0], err, cinfo);
            }
        }
        if (writable != 0) arr[7] = (int)end;
        if (arr[8] != 0) {
            u32 first = (u32)arr[6];
            u32 idx = i - first;
            u32 last = end - first;
            int sz = arr[2];
            mem = (int*)(unsigned)arr[0];
            for (; idx < last; idx++)
                FUN_008668f0((void*)(unsigned)mem[idx], sz);
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
            RealizeVirtLocal(cinfo, arr, 1, arr[2] << 7);
            arr[9] = 0;
        }
        if ((u32)arr[6] < start) {
            arr[6] = (int)start;
        } else {
            int t = (int)(end - arr[4]);
            if (t < 0) t = 0;
            arr[6] = t;
        }
        RealizeVirtLocal(cinfo, arr, 0, arr[2] << 7);
    }
    i = arr[7];
    if (i < end) {
        if (i < start) {
            i = start;
            if (writable != 0) {
                int* err = (int*)(unsigned)((int*)cinfo)[0];
                err[5] = 0x14;
                ((void (__fastcall*)(void*, void*, void*))(unsigned)err[0])(
                    (void*)(unsigned)err[0], err, cinfo);
            }
        }
        if (writable != 0) arr[7] = (int)end;
        if (arr[8] != 0) {
            u32 first = (u32)arr[6];
            u32 idx = i - first;
            u32 last = end - first;
            int sz = arr[2] << 7;
            int* mem = (int*)(unsigned)arr[0];
            for (; idx < last; idx++)
                FUN_008668f0((void*)(unsigned)mem[idx], sz);
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

// The marker reader's skip_input_data call is indirect.  The shim keeps the
// retail ECX value (a stack buffer in 0x00863c50, the callback itself in
// 0x00863d50) while still calling the cdecl callback with a balanced stack.
#pragma optimize("y", off)
static void __declspec(noinline) SkipInputLocal(void* ecxValue, void* edxValue, void* cinfo, int rem, void (*cb)(void*, int))
{
    volatile char pad[4];
    pad[0] = 0;
    ((void (__fastcall*)(void*, void*, void*, int))(unsigned)cb)(ecxValue, edxValue, cinfo, rem);
    pad[0] = 1;
}
#pragma optimize("y", on)

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
        n = ((int(*)(void*))(unsigned)src[3])(cinfo);
        if (n == 0) return 0;
        p = (u8*)(unsigned)src[0];
        n = src[1];
    }
    a = *p; n--; p++;
    if (n == 0) {
        n = ((int(*)(void*))(unsigned)src[3])(cinfo);
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
                n = ((int(*)(void*))(unsigned)src[3])(cinfo);
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
        SkipInputLocal(buf, 0, cinfo, rem, (void (*)(void*, int))(unsigned)src[4]);
    return 1;
}

// @ 0x00863d50
int FUN_00863d50(void* cinfo)
{
    int* src = *(int**)((char*)cinfo + 0x14);
    u8*  p = (u8*)(unsigned)src[0];
    int  n = src[1];
    u32  len, i;

    if (n == 0) {
        n = ((int(*)(void*))(unsigned)src[3])(cinfo);
        if (n == 0) return 0;
        p = (u8*)(unsigned)src[0];
        n = src[1];
    }
    {
        u8 a = *p; n--; p++;
        if (n == 0) {
            n = ((int(*)(void*))(unsigned)src[3])(cinfo);
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
            n = ((int(*)(void*))(unsigned)src[3])(cinfo);
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
        SkipInputLocal((void*)(unsigned)src[4], 0, cinfo, (int)len, (void (*)(void*, int))(unsigned)src[4]);
    return 1;
}
