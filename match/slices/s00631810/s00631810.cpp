// SP::cSPPlayModePhotoBrowser helpers. Region 0x631810-0x632779.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);
typedef void (__thiscall *TF2)(void*, int, int);

struct RefObj3 { virtual void s0(); virtual void s1(); virtual void s2(); };

// ---- Retail layouts (offsets taken from the disassembly). -----------------
struct cJob;
struct cPlayModePhoto {
  void* vptr;                        // 0x00
  unsigned int field4;               // 0x04
  unsigned int field8;               // 0x08
  unsigned int fieldC;               // 0x0c
  unsigned char pad10[0x1c - 0x10];  // 0x10..0x1b
  unsigned int guid;                 // 0x1c
  unsigned char pad20[0x30 - 0x20];  // 0x20..0x2f
  cJob* mJob;                        // 0x30
  unsigned char pad34[0x38 - 0x34];  // 0x34..0x37
  unsigned char flag38;              // 0x38
  unsigned char selected39;          // 0x39
};

// eastl::basic_string<wchar_t, eastl::allocator>, retail layout (16 bytes).
struct WStr16 {
  wchar_t* mpBegin;                  // 0x00
  wchar_t* mpEnd;                    // 0x04
  wchar_t* mpCapacity;               // 0x08
  unsigned int mAlloc;               // 0x0c
};

// Engine entry points (resolved by name / embedded address).
extern "C" void* __cdecl SP_GetSaveArea(unsigned int id);                    // 0x6b1f90
extern "C" void __cdecl WStr_Format(void* dst, const wchar_t* fmt, ...);      // 0x41e050
extern "C" void __cdecl FUN_00931fd0(const wchar_t* path);                    // 0x931fd0 File::Remove
extern "C" void __cdecl FUN_00931ff0(const wchar_t* from, const wchar_t* to, bool overwrite); // 0x931ff0 File::Move
extern "C" void __cdecl FUN_00932960(const wchar_t* path);                    // 0x932960 Directory::CreatePath
extern "C" void __cdecl FUN_0062ffd0(void* first, void* last, void* result);  // 0x62ffd0 do_copy
extern "C" void FUN_00429580();                                               // 0x429580 WStr::Append
extern "C" void FUN_00423650();                                               // 0x423650 WStr::assign
extern "C" void FUN_00692400();                                               // 0x692400 cJob::Cancel
extern "C" void FUN_00690120();                                               // 0x690120 cJob::Release
extern "C" void FUN_00f47380();                                               // 0xf47380 operator delete[]
extern "C" void* __cdecl FUN_0067dd60(void);                                  // 0x67dd60

// Constant data (resolved by the address embedded in the identifier).
extern "C" const wchar_t g_1667bac[];      // 0x1667bac  eastl::gEmptyString16
extern "C" const wchar_t g_013fe428[];     // 0x13fe428  L"CRE_%s-%08x_ful.png"
extern "C" const wchar_t g_013fe450[];     // 0x13fe450  L"CRE_%s-%08x_sml.jpg"
extern "C" const wchar_t g_013fe62c[];     // 0x13fe62c  L"BackUp\\"

typedef bool (__thiscall *CancelFn)(void*, bool);
typedef int (__thiscall *ReleaseFn)(void*);
typedef void (__thiscall *AppendFn)(void*, const wchar_t*, const wchar_t*);
typedef void (__thiscall *AssignFn)(void*, const wchar_t*, const wchar_t*);
typedef void* (__thiscall *GetPathFn)(void*);

static void WStr16_InitEmpty(WStr16& s) {
  s.mpBegin = s.mpEnd = (wchar_t*)g_1667bac;
  s.mpCapacity = (wchar_t*)g_1667bac + 1;
}
static void WStr16_Free(WStr16& s) {
  int diff = (int)((char*)s.mpEnd - (char*)s.mpBegin);
  if (((diff & 0xfffffffe) > 2) && s.mpBegin != 0)
    ((void(__cdecl*)(void*))FUN_00f47380)(s.mpBegin);
}
// Wide-string equality (the original inlines a 32-bit-at-a-time compare).
static bool WStrEqual(const wchar_t* a, const wchar_t* b) {
  for (;;) {
    if (*a != *b) return false;
    if (*a == 0) return true;
    ++a;
    ++b;
  }
}

// Intrusive Release through the object's vtable (slot 2, byte 0x08).
static void ReleaseObj(void* obj) {
  void** vtbl = *(void***)obj;
  ((ReleaseFn)vtbl[2])(obj);
}
// SaveArea::GetPath()-style accessor (vtable slot 10, byte 0x28).
static const wchar_t* SaveAreaGetPath(void* saveArea) {
  void** vtbl = *(void***)saveArea;
  return (const wchar_t*)((GetPathFn)vtbl[0x28 / 4])(saveArea);
}

// ---- eastl::basic_string<char, eastl::allocator>, retail layout. ----------
struct CStr {
  char* mpBegin;                      // 0x00
  char* mpEnd;                        // 0x04
  char* mpCapacity;                   // 0x08
  unsigned int mAlloc;                // 0x0c
};

extern const char g_013fe61c[];    // 0x13fe61c  "0x%08x:0x%08x"
extern const char g_013f5b98[];    // 0x13f5b98
extern const char g_013fe618[];    // 0x13fe618

// engine string helpers
extern "C" int __cdecl CStr_sprintf(void* dst, const char* fmt, ...);   // 0x472fe0
extern "C" int __cdecl Sprintf8(char* dst, const char* fmt, ...);       // 0x938470
extern "C" int __cdecl GetCharacterAsUTF16(unsigned short* dst, unsigned int n,
                                           const char* src, int len);   // 0x93cf60
extern "C" void FUN_0091bec0();   // 0x91bec0  find_last_of
extern "C" void FUN_006082a0();   // 0x6082a0  substr
extern "C" void FUN_00454cb0();   // 0x454cb0  assign
extern "C" __declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);

typedef unsigned int (__thiscall *FindLastOfFn)(void*, const char*, unsigned int);
typedef void (__thiscall *SubstrFn)(void*, void*, unsigned int, unsigned int);
typedef void (__thiscall *AssignCFn)(void*, const char*, const char*);

static void CStr_InitEmpty(CStr& s) {
  s.mpBegin = s.mpEnd = (char*)g_1667bac;
  s.mpCapacity = (char*)g_1667bac + 1;
  s.mAlloc = 0;
}
static void CStr_Free(CStr& s) {
  int diff = (int)((char*)s.mpCapacity - (char*)s.mpBegin);
  if (diff > 1 && s.mpBegin != 0)
    ((void(__cdecl*)(void*))FUN_00f47380)(s.mpBegin);
}

// ---- SaveArea photo query support (00631e50 / 00631b30) --------------------
extern "C" const wchar_t g_013f5c04[];          // 0x13f5c04
extern "C" const wchar_t g_013ec468[];          // 0x13ec468
extern "C" const unsigned char g_013f8f14[];    // 0x13f8f14
extern "C" const char g_013eb430[];             // 0x13eb430  eastl allocator name
extern "C" void* __cdecl FUN_00f473a0(unsigned int size, const char* name,
                                      int a, int b, int c, int d);  // 0xf473a0
extern "C" void* __cdecl FUN_008de1a0(void);    // 0x8de1a0  resource manager

typedef void* (__thiscall *GetIterFn)(void*, const void*);
typedef void (__thiscall *QueryRangeFn)(void*, unsigned int*, unsigned int*);
typedef void (__thiscall *GetPathForKeyFn)(void*, const void*, WStr16*);

// dest = prefix + src (engine helper; cdecl, three stack arguments).
extern "C" void __cdecl OperatorPlus(WStr16* dest, const wchar_t* prefix, WStr16* src);  // 0x006309e0

// Engine file stream: the object is 0x22c bytes and ctor/SetPath16/Open/dtor
// are direct engine calls (ret 4 / ret 4 / ret 0x10 / ret).
struct FileStream {
  unsigned int pad[0x22c / 4];
  FileStream(int flags);                  // 0x00931da0
  ~FileStream();                          // 0x00931e70
  void SetPath16(const wchar_t* path);    // 0x00931810
  bool Open(int a, int b, int c, int d);  // 0x009318f0
};

// Deep copy of an eastl wide string, matching the allocation the original
// expands inline for the by-value argument of FUN_006312f0.
static void WStr16_Clone(WStr16& dst, const WStr16& src) {
  unsigned int count = (unsigned int)(src.mpEnd - src.mpBegin);
  unsigned int n = count + 1;
  if (n > 1) {
    wchar_t* p = (wchar_t*)FUN_00f473a0(n * 2, g_013eb430, 0, 0, (int)0x13ebb38, 0xd1);
    memcpy(p, src.mpBegin, count * 2);
    p[count] = 0;
    dst.mpBegin = p;
    dst.mpEnd = p + count;
    dst.mpCapacity = p + n;
  } else {
    dst.mpBegin = dst.mpEnd = (wchar_t*)g_1667bac;
    dst.mpCapacity = (wchar_t*)g_1667bac + 1;
  }
}

struct PhotoBrowser {
  void* vptr;                        // 0x00
  cPlayModePhoto** photosBegin;      // 0x04
  cPlayModePhoto** photosEnd;        // 0x08
  cPlayModePhoto** photosCap;        // 0x0c
  unsigned char pad10[0x18 - 0x10];  // 0x10..0x17
  unsigned int firstPhotoIndex;      // 0x18
  unsigned int selectedPhotoIndex;   // 0x1c
  unsigned char pad20[0xe78 - 0x20]; // 0x20..0xe77
  cPlayModePhoto** loadedBegin;      // 0xe78
  cPlayModePhoto** loadedEnd;        // 0xe7c
  cPlayModePhoto** loadedCap;        // 0xe80
  unsigned char padE84[0xe8c - 0xe84]; // 0xe84..0xe8b
  cPlayModePhoto* viewerPhoto;       // 0xe8c

  bool FUN_00631810(void* hdr, unsigned int u, int kind, WStr16 s);  // 0x00631810
  bool FUN_00631a10(cPlayModePhoto* p);                    // 0x00631a10
  unsigned int FUN_00631b30();                             // 0x00631b30
  bool FUN_00631e50(unsigned int guid, WStr16* out);       // 0x00631e50
  bool FUN_006312f0(WStr16 s, unsigned int* a, unsigned int* b, WStr16* c);  // 0x006312f0
  void FUN_006320d0(unsigned int index, bool deleteFile);  // 0x006320d0
  void FUN_00632320(unsigned int index);                   // 0x00632320
};

extern "C" void* __cdecl FUN_0067dd60(void);

// //AutoRefCount<...>::Release-equivalent intrusive count: drop the count unless it
// would fall below 1 (the original decrements, reads back, and re-increments if <1).
static void DecRefCount(void* obj) {
  int* count = (int*)((char*)obj + 8);
  int c = *count;
  if (c > 1) *count = c - 1;
}

// @ 0x00631810
// bool cSPPlayModePhotoBrowser::CompareGuidAndTypeWithHeader(void* hdr, uint u,
//                                                            int kind, wstring16 s)
bool PhotoBrowser::FUN_00631810(void* hdr, unsigned int u, int kind, WStr16 s) {
  CStr name, keep, tmp;
  CStr_InitEmpty(name);
  CStr_InitEmpty(keep);
  CStr_InitEmpty(tmp);
  int parsedKey = 0;
  int parsedKind = 0;
  sscanf((const char*)hdr + 0x65c, g_013fe61c, &parsedKey, &parsedKind);
  bool sameName = true;
  if (parsedKind == 0x417b3bc) {
    char buf[64];
    const char* src = (const char*)hdr + 0x65c;
    for (int i = 0; i < 64; ++i) buf[i] = src[i];
    CStr_sprintf(&name, g_013f5b98, buf);
    unsigned int pos = ((FindLastOfFn)FUN_0091bec0)(&name, g_013fe618, 0xffffffffu);
    unsigned int slen = 0;
    while (name.mpBegin[slen] != 0) ++slen;
    ((SubstrFn)FUN_006082a0)(&name, &tmp, pos + 1, slen - pos);
    ((AssignCFn)FUN_00454cb0)(&keep, tmp.mpBegin, tmp.mpEnd);
    CStr_Free(tmp);
    char txt[260];
    Sprintf8(txt, g_013f5b98, keep.mpBegin);
    unsigned short utf16[260];
    GetCharacterAsUTF16(utf16, 0x208, txt, -1);
    sameName = WStrEqual((const wchar_t*)utf16, s.mpBegin);
  }
  bool result = (parsedKey == (int)u) && (parsedKind == kind) && sameName;
  CStr_Free(name);
  CStr_Free(keep);
  WStr16_Free(s);
  return result;
}

// @ 0x00631a10
bool PhotoBrowser::FUN_00631a10(cPlayModePhoto* p) {
  cPlayModePhoto** end = loadedEnd;
  if (loadedBegin != end) {
    for (cPlayModePhoto** it = loadedBegin; it != end; ++it) {
      cPlayModePhoto* q = *it;
      if (q == p) {
        void* mgr = FUN_0067dd60();
        void* ref = (*(void* (__thiscall*)(void*, unsigned int, unsigned int, int))
                     (*((void**)mgr + 8)))(mgr, q->fieldC, q->field8, 0);
        DecRefCount(ref);
        q->selected39 = 0;
        if (it + 1 < end)
          memmove(it, it + 1, (char*)end - (char*)(it + 1));
        loadedEnd = end - 1;
        return true;
      }
    }
  }
  if (viewerPhoto == p) {
    void* mgr = FUN_0067dd60();
    void* ref = (*(void* (__thiscall*)(void*, unsigned int, unsigned int, int))
                 (*((void**)mgr + 8)))(mgr, p->fieldC, p->field8, 0);
    DecRefCount(ref);
    p->selected39 = 0;
    viewerPhoto = 0;
  }
  return false;
}

// @ 0x00631b30
// Counts the photos in the save area whose files can actually be opened:
// iterate the photo range, resolve each record's path, parse it with
// FUN_006312f0, and on success prepend the save-area base path and try to
// open the resulting file.
unsigned int PhotoBrowser::FUN_00631b30() {
  void* saveArea = SP_GetSaveArea(0x11ac196);
  void** saVt = *(void***)saveArea;
  void* iterA = ((GetIterFn)saVt[0x5c / 4])(saveArea, g_013f8f14);

  unsigned int filter[5];
  filter[0] = 0x13eb898;
  filter[1] = 0xffffffffu;
  filter[2] = 0x11ac196;
  filter[3] = (unsigned int)iterA;
  filter[4] = 0xffffffffu;
  unsigned int range[3];
  range[0] = 0;
  range[1] = 0;
  range[2] = 0;
  ((QueryRangeFn)saVt[0x30 / 4])(saveArea, range, filter);

  unsigned int count = 0;
  void* it = (void*)range[0];
  void* end = (void*)range[1];
  while (it != end) {
    const unsigned int* rec = (const unsigned int*)it;
    unsigned int key[3];
    key[0] = rec[0];
    key[1] = rec[1];
    key[2] = rec[2];
    void* rm = FUN_008de1a0();
    WStr16 str1;
    WStr16_InitEmpty(str1);
    ((GetPathForKeyFn)(*(void***)rm)[0x7c / 4])(rm, key, &str1);

    WStr16 localStr;
    WStr16_InitEmpty(localStr);
    unsigned int outA = 0;
    unsigned int outB = 0;
    WStr16 name;
    WStr16_Clone(name, str1);
    if (FUN_006312f0(name, &outA, &outB, &localStr)) {
      const wchar_t* base = SaveAreaGetPath(saveArea);
      WStr16 path;
      WStr16_InitEmpty(path);
      OperatorPlus(&path, base, &str1);
      {
        FileStream fs(0);
        fs.SetPath16(path.mpBegin);
        if (fs.Open(1, 6, 1, 0))
          count++;
      }
      WStr16_Free(path);
    }
    WStr16_Free(localStr);
    it = (char*)it + 12;
    WStr16_Free(str1);
  }

  filter[0] = 0x13eb394;
  if (range[0] != 0 && ((unsigned int*)range[0])[-1] != 0)
    ((void(__cdecl*)(void*))FUN_00f47380)((void*)range[0]);
  return count;
}

// @ 0x00631dc0
extern "C" void __cdecl CALLEE_memcpy_11e0744(void* dst, const void* src, unsigned n);
void __fastcall FUN_00631dc0(void* self) {
  int* s = (int*)self;
  void* end = (void*)s[1];
  void* beg = (void*)s[0];
  CALLEE_memcpy_11e0744(beg, end, 0);
  s[1] += (int)beg - (int)end;
}

// @ 0x00631df0
struct Photo; // opaque
extern "C" void __cdecl FUN_005c8480(void*, void**);
void __fastcall FUN_00631df0(void* self, void* p) {
  int* s = (int*)self;
  void* obj = p;
  if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 4)))(obj);
  if (s[2] < s[3]) {
    int* end = (int*)s[2];
    s[2] = (int)(end + 1);
    if (end != 0) {
      *end = (int)obj;
      if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 4)))(obj);
    }
  } else {
    FUN_005c8480((void*)s[2], &obj);
  }
  if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 8)))(obj);
}

// @ 0x00631e50
// bool cSPPlayModePhotoBrowser::GetPhotoDir(this, uint guid, wstring16* out)
bool PhotoBrowser::FUN_00631e50(unsigned int guid, WStr16* out) {
  void* saveArea = SP_GetSaveArea(0x11ac196);
  void** saVt = *(void***)saveArea;
  // Collection iterator returned by slot +0x5c (embeds the global photo query).
  void* iterA = ((GetIterFn)saVt[0x5c / 4])(saveArea, g_013f8f14);
  // Query filter object: {vtable, -1, save-area id, iterator, -1}.
  unsigned int filter[5];
  filter[0] = 0x13eb898;
  filter[1] = 0xffffffffu;
  filter[2] = 0x11ac196;
  filter[3] = (unsigned int)iterA;
  filter[4] = 0xffffffffu;
  // Out range {begin, end, capacity}, filled by slot +0x30.
  unsigned int range[3];
  range[0] = 0; range[1] = 0; range[2] = 0;
  ((QueryRangeFn)saVt[0x30 / 4])(saveArea, range, filter);

  WStr16 localWrap;
  WStr16_InitEmpty(localWrap);
  void* it = (void*)range[0];
  void* end = (void*)range[1];
  bool found = false;
  if (it != end) {
    do {
      const unsigned int* rec = (const unsigned int*)it;
      unsigned int key[3];
      key[0] = rec[0]; key[1] = rec[1]; key[2] = rec[2];
      void* rm = FUN_008de1a0();
      WStr16 str1;
      WStr16_InitEmpty(str1);
      ((GetPathForKeyFn)(*(void***)rm)[0x7c / 4])(rm, key, &str1);
      unsigned int type = 0xffffffffu;
      unsigned int parsedGuid = 0;
      WStr16 name;
      WStr16_Clone(name, str1);
      if (FUN_006312f0(name, &parsedGuid, &type, &localWrap) && parsedGuid == guid) {
        found = true;
        WStr16_Free(str1);
        WStr_Format(out, g_013f5c04, localWrap);
        goto done;
      }
      it = (char*)it + 12;
      WStr16_Free(str1);
    } while (it != end);
  }
  WStr_Format(out, g_013f5c04, g_013ec468);
done:
  WStr16_Free(localWrap);
  filter[0] = 0x13eb394;
  if (range[0] != 0 && ((unsigned int*)range[0])[-1] != 0)
    ((void(__cdecl*)(void*))FUN_00f47380)((void*)range[0]);
  return found;
}

// @ 0x006320d0
// void cSPPlayModePhotoBrowser::DeletePhoto(this, uint index, bool deleteFile)
void PhotoBrowser::FUN_006320d0(unsigned int index, bool deleteFile) {
  if (index >= (unsigned int)(photosEnd - photosBegin)) return;
  cPlayModePhoto** slot = photosBegin + index;
  cPlayModePhoto* p = *slot;
  void* job = p->mJob;
  if (job != 0) {
    ((CancelFn)FUN_00692400)(job, false);
    p = *slot;
    job = p->mJob;
    if (job != 0) {
      p->mJob = 0;
      ((ReleaseFn)FUN_00690120)(job);
    }
  }
  if (deleteFile) {
    WStr16 name, path, dir;
    WStr16_InitEmpty(name);
    WStr16_InitEmpty(path);
    void* saveArea = SP_GetSaveArea(0x11ac196);
    WStr16_InitEmpty(dir);
    if (FUN_00631e50(p->guid, &dir)) {
      const wchar_t* base = SaveAreaGetPath(saveArea);
      WStr_Format(&path, base);
      WStr_Format(&name, g_013fe428, dir.mpBegin, p->guid);
      ((AppendFn)FUN_00429580)(&path, name.mpBegin, name.mpEnd);
      FUN_00931fd0(path.mpBegin);
      base = SaveAreaGetPath(saveArea);
      WStr_Format(&path, base);
      WStr_Format(&name, g_013fe450, dir.mpBegin, p->guid);
      ((AppendFn)FUN_00429580)(&path, name.mpBegin, name.mpEnd);
      FUN_00931fd0(path.mpBegin);
    }
    WStr16_Free(dir);
    WStr16_Free(path);
    WStr16_Free(name);
  }
  FUN_00631a10(*slot);
  cPlayModePhoto* q = *slot;
  if (q != 0) {
    *slot = 0;
    ReleaseObj(q);
  }
  if (slot + 1 < photosEnd)
    FUN_0062ffd0(slot + 1, photosEnd, slot);
  photosEnd = photosEnd - 1;
  cPlayModePhoto* last = *photosEnd;
  if (last != 0)
    ReleaseObj(last);
  unsigned int cnt = (unsigned int)(photosEnd - photosBegin);
  if (cnt <= selectedPhotoIndex) selectedPhotoIndex = cnt - 1;
  if (selectedPhotoIndex < firstPhotoIndex) firstPhotoIndex = firstPhotoIndex - 5;
}

// @ 0x00632320
// void cSPPlayModePhotoBrowser::MovePhoto(this, uint index)
void PhotoBrowser::FUN_00632320(unsigned int index) {
  if (index >= (unsigned int)(photosEnd - photosBegin)) return;
  cPlayModePhoto** slot = photosBegin + index;
  cPlayModePhoto* p = *slot;
  void* job = p->mJob;
  if (job != 0) {
    ((CancelFn)FUN_00692400)(job, false);
    p = *slot;
    job = p->mJob;
    if (job != 0) {
      p->mJob = 0;
      ((ReleaseFn)FUN_00690120)(job);
    }
  }
  WStr16 backup, dst, name, cur, dir;
  WStr16_InitEmpty(backup);   // local_40..38
  WStr16_InitEmpty(dst);      // local_20..18
  WStr16_InitEmpty(name);     // local_50..48
  WStr16_InitEmpty(cur);      // local_30..28
  WStr16_InitEmpty(dir);      // local_10..08
  void* saveArea = SP_GetSaveArea(0x11ac196);
  {
    WStr_Format(&backup, SaveAreaGetPath(saveArea));
    int n = 0;
    while (g_013fe62c[n] != 0) ++n;
    ((AppendFn)FUN_00429580)(&backup, g_013fe62c, g_013fe62c + n);
    FUN_00932960(backup.mpBegin);
  }
  if (FUN_00631e50(p->guid, &dir)) {
    WStr_Format(&dst, SaveAreaGetPath(saveArea));
    WStr_Format(&name, g_013fe428, dir.mpBegin, p->guid);
    ((AppendFn)FUN_00429580)(&dst, name.mpBegin, name.mpEnd);
    ((AssignFn)FUN_00423650)(&cur, backup.mpBegin, backup.mpEnd);
    ((AppendFn)FUN_00429580)(&cur, name.mpBegin, name.mpEnd);
    FUN_00931ff0(dst.mpBegin, cur.mpBegin, true);
    WStr_Format(&dst, SaveAreaGetPath(saveArea));
    WStr_Format(&name, g_013fe450, dir.mpBegin, p->guid);
    ((AppendFn)FUN_00429580)(&dst, name.mpBegin, name.mpEnd);
    ((AssignFn)FUN_00423650)(&cur, backup.mpBegin, backup.mpEnd);
    ((AppendFn)FUN_00429580)(&cur, name.mpBegin, name.mpEnd);
    FUN_00931ff0(dst.mpBegin, cur.mpBegin, true);
  }
  FUN_00631a10(*slot);
  cPlayModePhoto* q = *slot;
  if (q != 0) {
    *slot = 0;
    ReleaseObj(q);
  }
  if (slot + 1 < photosEnd)
    FUN_0062ffd0(slot + 1, photosEnd, slot);
  photosEnd = photosEnd - 1;
  cPlayModePhoto* last = *photosEnd;
  if (last != 0)
    ReleaseObj(last);
  unsigned int cnt = (unsigned int)(photosEnd - photosBegin);
  if (cnt <= selectedPhotoIndex) selectedPhotoIndex = cnt - 1;
  if (selectedPhotoIndex < firstPhotoIndex) firstPhotoIndex = firstPhotoIndex - 5;
  WStr16_Free(dir);
  WStr16_Free(dst);
  WStr16_Free(name);
  WStr16_Free(cur);
  WStr16_Free(backup);
}

// @ 0x00632660
extern void __fastcall ExitDeleteMode(void*);
void __fastcall FUN_00632660(void* self) {
  int* s = (int*)self;
  int n = (s[2] - s[1]) >> 2;
  for (int i = n - 1; i >= 0; --i) {
    void* p;
    if (i < ((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    if (*(unsigned char*)((char*)p + 0x38)) ((PhotoBrowser*)self)->FUN_006320d0(i, 1);
  }
  for (unsigned i = 0; i < (unsigned)((s[2] - s[1]) >> 2); ++i) {
    void* p;
    if (i < (unsigned)((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
  }
  ExitDeleteMode(self);
}

// @ 0x006326f0
extern void __fastcall ExitMoveMode(void*);
void __fastcall FUN_006326f0(void* self) {
  int* s = (int*)self;
  int n = (s[2] - s[1]) >> 2;
  for (int i = n - 1; i >= 0; --i) {
    void* p;
    if (i < ((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    if (*(unsigned char*)((char*)p + 0x38)) ((PhotoBrowser*)self)->FUN_00632320(i);
  }
  for (unsigned i = 0; i < (unsigned)((s[2] - s[1]) >> 2); ++i) {
    void* p;
    if (i < (unsigned)((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
  }
  ExitMoveMode(self);
}
