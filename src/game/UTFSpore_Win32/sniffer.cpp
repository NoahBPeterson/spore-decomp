// src/game/UTFSpore_Win32/sniffer.cpp -- migrated from slice(s) s008b6400 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/sniffer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl strcmp(const char*, const char*);
extern "C" void  Delete_sfnt_OffsetTable(void*);                               // 0x008cd910
extern "C" int   setjmp3(void*, int);                                          // 0x011e0cac
#pragma intrinsic(strcmp)

// ---- items of slice s008b6400 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t uint8;
typedef uint32_t uint32;
struct tsiMemObject;
struct InputStream;
extern "C" int   Seek_InputStream(InputStream*, int);                          // 0x008cc580
extern "C" int   PeekInt16(InputStream*, void*, int);                          // 0x008cc220
extern "C" tsiMemObject* tsi_NewMemhandler(void*);                             // 0x008d11f0
extern "C" void* tsi_AllocMem(tsiMemObject*, uint32);                          // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject*, void*);                         // 0x008d1440
extern "C" void  tsi_DeleteMemhandler(tsiMemObject*);                          // 0x008d1570
extern "C" void  tsi_EmergencyShutDown(tsiMemObject*);                         // 0x008d1210
extern "C" void* New_sfnt_OffsetTable(tsiMemObject*, InputStream*);            // 0x008cd860
extern "C" void  Delete_sfnt_OffsetTable(void*);                               // 0x008cd910
extern "C" void* GetTableDirEntry_sfntClass(void*, uint32);                    // 0x008cebe0
extern "C" int   setjmp3(void*, int);                                          // 0x011e0cac
// ---- items of slice s008b6400 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" int   Seek_InputStream(InputStream*, int);                          // 0x008cc580
extern "C" int   PeekInt16(InputStream*, void*, int);                          // 0x008cc220
extern "C" tsiMemObject* tsi_NewMemhandler(void*);                             // 0x008d11f0
extern "C" void* tsi_AllocMem(tsiMemObject*, uint32);                          // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject*, void*);                         // 0x008d1440
extern "C" void  tsi_DeleteMemhandler(tsiMemObject*);                          // 0x008d1570
extern "C" void  tsi_EmergencyShutDown(tsiMemObject*);                         // 0x008d1210
extern "C" void* New_sfnt_OffsetTable(tsiMemObject*, InputStream*);            // 0x008cd860
extern "C" void* GetTableDirEntry_sfntClass(void*, uint32);                    // 0x008cebe0

// @ 0x008b6400
static int IsPFR(InputStream* s)
{
    char buf[10];
    int result;
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 10);
    if (buf[0] == 'P' && buf[1] == 'F' && buf[2] == 'R') {
        result = 1;
        Seek_InputStream(s, 0);
    } else {
        result = 0;
        Seek_InputStream(s, 0);
    }
    return result;
}

// @ 0x008b6460
static int IsOTF(InputStream* s)
{
    int ok = 0;
    int mh;
    char buf[10];
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 10);
    if (buf[0] == 0) {
        if ((buf[1] != 1 && buf[1] != 2) || buf[2] != 0 || buf[3] != 0)
            goto fail;
    } else if (buf[0] != 'O' || buf[1] != 'T' || buf[2] != 'T' || buf[3] != 'O') {
        goto fail;
    }
    Seek_InputStream(s, 0);
    {
        tsiMemObject* mem = tsi_NewMemhandler(&mh);
        void** table = (void**)tsi_AllocMem(mem, 0xf8);
        *table = New_sfnt_OffsetTable(mem, s);
        ok = GetTableDirEntry_sfntClass(table, 0x44534947) != 0;    // 'DSIG'
        if (!ok)
            ok = GetTableDirEntry_sfntClass(table, 0x43464620) != 0; // ' CFF'
        Delete_sfnt_OffsetTable(*table);
        tsi_DeAllocMem(mem, table);
        tsi_DeleteMemhandler(mem);
    }
    Seek_InputStream(s, 0);
    return ok;
fail:
    Seek_InputStream(s, 0);
    return ok;
}

// @ 0x008b6570
static int IsTT(InputStream* s)
{
    int mh;
    char buf[10];
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 10);
    int found = 0;
    if (buf[0] == 0) {
        if ((buf[1] != 1 && buf[1] != 2) || buf[2] != 0 || buf[3] != 0)
            goto fail;
    } else if (buf[0] == 'O') {
        if (buf[1] != 'T' || buf[2] != 'T' || buf[3] != 'O')
            goto fail;
    } else {
        goto check_true;
    }
    Seek_InputStream(s, 0);
    {
        tsiMemObject* mem = tsi_NewMemhandler(&mh);
        void** table = (void**)tsi_AllocMem(mem, 0xf8);
        *table = New_sfnt_OffsetTable(mem, s);
        found = GetTableDirEntry_sfntClass(table, 0x6c6f6361) != 0; // 'acol'
        if (!found)
            found = GetTableDirEntry_sfntClass(table, 0x736c6f63) != 0; // 'cols'
        if (!found)
            found = GetTableDirEntry_sfntClass(table, 0x45424454) != 0; // 'TDBE'
        if (!found)
            found = GetTableDirEntry_sfntClass(table, 0x626c6f63) != 0; // 'colb'
        Delete_sfnt_OffsetTable(*table);
        tsi_DeAllocMem(mem, table);
        tsi_DeleteMemhandler(mem);
        if (found)
            goto done;
    }
check_true:
    if (buf[0] == 't') {
        if (buf[1] == 't') {
            if (buf[2] == 'c' && buf[3] == 'f') {
                Seek_InputStream(s, 0);
                return 1;
            }
        } else if (buf[1] == 'r' && buf[2] == 'u' && buf[3] == 'e') {
            Seek_InputStream(s, 0);
            return 1;
        }
    }
fail:
    found = 0;
done:
    Seek_InputStream(s, 0);
    return found;
}

// @ 0x008b6710
static int IsT1(InputStream* s)
{
    char buf[16];
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 16);
    char i = 0;
    while (buf[i] != '%' && i < 13) {
        ++i;
    }
    if (buf[i] == '%' && buf[i + 1] == '!') {
        Seek_InputStream(s, 0);
        return 1;
    }
    Seek_InputStream(s, 0);
    return 0;
}

// @ 0x008b6780
static int IsCFF(InputStream* s)
{
    uint8 buf[0x96];
    int result = 1;
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 0x96);
    if (buf[0] != 1
        || buf[2] + 4 >= 0x96
        || buf[buf[2] + 4] == 0
        || (int)buf[buf[2] + 4] >= 0x92 - buf[2]
        || buf[buf[buf[2] + 4] + buf[2] + 4] != 0)
        result = 0;
    Seek_InputStream(s, 0);
    return result;
}

// @ 0x008b6800
int ff_FontTypeFromStream(InputStream* s)
{
    if (IsOTF(s))
        return 7;
    if (IsTT(s))
        return 2;
    if (IsPFR(s))
        return 3;
    if (IsCFF(s))
        return 0x16;
    if (IsT1(s))
        return 1;
    return -1;
}

// @ 0x008b6870
#pragma optimize("y", off)
extern "C" short FF_FontTypeFromStream(int hdr, int* out)
{
    int r = setjmp3((void*)(*(int*)(hdr + 0x22c) + 0x10), 0);
    *out = r;
    if (r == 0)
        return (short)ff_FontTypeFromStream((InputStream*)hdr);
    tsi_EmergencyShutDown(*(tsiMemObject**)(hdr + 0x22c));
    return (short)*out;
}
#pragma optimize("y", on)
