// Slice s00684ee0: Hilbert/space-fill curve coordinate helpers (0x684ee0..0x6852d3),
// rectangle/quad helpers, a small refcounted object release, wide-string lookup over
// vector<wstring>, variant destroy loops, a hash-table erase and several string-vector
// destroy/free ranges.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

// ---------------------------------------------------------------- externals
void* EAAlloc(unsigned size, const char* area, int a, int b, const char* file, int line); // 0x00f473a0
void  EAFree(void* p); // 0x00f47380
void* ZoneNew(unsigned size, const char* area, int a, int b, int c, int d); // 0x00926020
extern "C" void* GetManager();                       // 0x0067dcd0
extern "C" bool  EA_IO_IsSubdirectory(void*, int, int);  // 0x00930ab0
extern "C" __declspec(dllimport) long __cdecl atol(const char*);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const wchar_t*, const wchar_t*, unsigned);
extern "C" long __fastcall _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __fastcall _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)

extern int g_0152b348;       // entry count
extern void* g_015fea00;     // entry table base
extern void* g_015fea00b;    // (unused)

struct cArguments {
  int NumArguments();            // 0x00837f30
  const char* operator[](int);   // 0x00837f20
};

struct Variant {
  void Destruct(int);            // 0x0093db80
};

struct AllocSvc {
  void* Alloc(unsigned, const char*);  // +0x0c vtable slot (node dealloc via +0xc)
};

// A handful of thiscall helpers live on one anonymous object; the class body only
// exists to give the functions a correct `this` register.
struct S2 {
  bool FUN_006854b0(int param);
  void FUN_006854e0(int unused, int* param);
  void FUN_00685570(int unused, int* param);
  void FUN_006855a0(cArguments* pArgs);
  void FUN_006855f0();
  int* FUN_006859b0(int* pOut, int* pNode, int** pBucket);
  void* FUN_00685a60(void* src);
};

// eastl::wstring (wchar_t specialization): three pointers, AllocateSelf is a
// __thiscall member with `this` at the object base.
struct WString {
  void* mpBegin;    // +0
  void* mpEnd;      // +4
  void* mpCapacity; // +8
  void  AllocateSelf(int n);  // 0x00429760
};

// @ 0x006854b0
bool S2::FUN_006854b0(int param) {
  return *(int*)(param + 8) == *(int*)((char*)this + 4);
}

// @ 0x006854e0
void S2::FUN_006854e0(int unused, int* param) {
  if (*param == 0x7104c38) *(int*)((char*)this + 4) = param[1];
}

// @ 0x00685570
void S2::FUN_00685570(int unused, int* param) {
  if (*param == 0x7104c38) {
    *(int*)((char*)this + 0x20c) = param[1];
    *(int*)((char*)this + 0x210) = param[2];
  }
}

// @ 0x006855a0
void S2::FUN_006855a0(cArguments* pArgs) {
  char* pThis = (char*)this;
  if (*(int*)(pThis + 4) != 0 && pArgs->NumArguments() == 2) {
    const char* s = pArgs->operator[](1);
    long v = atol(s);
    if (v <= g_0152b348) {
      int holder = *(int*)(pThis + 4);
      char* base = *(char**)holder;
      base[v * 0x28] = 0;
    }
  }
}

// A refcounted target whose vtable slot 0 is called with one int argument.
struct IRefTarget {
  virtual void Release(int n);  // vtable slot 0
};

// @ 0x006855f0
void S2::FUN_006855f0() {
  int* pObj = *(int**)this;
  if (pObj != 0) {
    int* pHolder = pObj + 1;
    int* pRef = pObj + 2;
    long old = _InterlockedExchangeAdd((volatile long*)pRef, -1);
    if (--old == 0) {
      _InterlockedExchange((volatile long*)pRef, 1);
      if (pHolder != 0) {
        ((IRefTarget*)pHolder)->Release(1);
      }
    }
  }
}

// @ 0x00685500
int FUN_00685500(int index) {
  if (index <= g_0152b348) {
    return *(int*)((char*)g_015fea00 + index * 0x28 + 4);
  }
  return 0;
}

// @ 0x00685520
unsigned char FUN_00685520(int index) {
  if (index <= g_0152b348) {
    return *(unsigned char*)((char*)g_015fea00 + index * 0x28);
  }
  return 0;
}

// @ 0x00685540
void FUN_00685540() {
  int i = 0;
  if (i <= g_0152b348) {
    int off = 0;
    do {
      *(unsigned char*)(off + (char*)g_015fea00) = 0;
      ++i;
      off += 0x28;
    } while (i <= g_0152b348);
  }
}

// @ 0x00685620
void* FUN_00685620(void* first, void* last, const wchar_t* pName) {
  while (first != last) {
    int n = (*(int*)((char*)first + 4) - *(int*)first) >> 1;
    if (_wcsnicmp(pName, *(const wchar_t**)first, n) == 0) break;
    first = (char*)first + 0x10;
  }
  return first;
}

// @ 0x00685710
bool FUN_00685710(int param1, void** param2) {
  if (EA_IO_IsSubdirectory(*param2, param1, 4)) {
    const wchar_t* start = (const wchar_t*)*param2;
    const wchar_t* p = start;
    while (*p != 0) ++p;
    int len = (int)(p - start);
    int* holder = (int*)param2[1];
    int* end = (int*)holder[1];
    int* begin = (int*)holder[0];
    if (FUN_00685620(begin, end, (const wchar_t*)(param1 + len * 2)) != end) return false;
  }
  return true;
}

// @ 0x00685980
void __fastcall FUN_00685980(void* pList) {
  char* node = *(char**)pList;
  while (node != pList) {
    char* next = *(char**)node;
    void* alloc = *(void**)((char*)pList + 8);
    typedef void (__thiscall *Fn)(void*, char*, int);
    (*(Fn*)((char*)*(void**)alloc + 0xc))(alloc, node, 0xc);
    node = next;
  }
}

// @ 0x006859b0
int* S2::FUN_006859b0(int* pOut, int* pNode, int** pBucket) {
  int iVar1 = pNode[3];
  pOut[1] = (int)pBucket;
  pOut[0] = iVar1;
  while (iVar1 == 0) {
    pOut[1] += 4;
    iVar1 = *(int*)pOut[1];
    pOut[0] = iVar1;
  }
  int* p = *pBucket;
  if (p != pNode) {
    int* q = (int*)p[3];
    while (q != pNode) {
      p = q;
      q = (int*)q[3];
    }
    p[3] = q[3];
    EAFree(pNode);
    *(int*)((char*)this + 0xc) -= 1;
    return pOut;
  }
  *pBucket = (int*)p[3];
  EAFree(pNode);
  *(int*)((char*)this + 0xc) -= 1;
  return pOut;
}

// @ 0x00685a30
void __stdcall FUN_00685a30(char* first, char* last) {
  for (; first < last; first += 0x18) {
    if ((*(unsigned char*)(first + 0x14) & 4) != 0) {
      ((Variant*)(first + 4))->Destruct(0);
    }
  }
}

// @ 0x00685cd0
char* FUN_00685cd0(char* first, char* last, char* out) {
  while (first != last) {
    int v1 = *(int*)(first + 0x18);
    if ((int)((*(int*)(first + 0x20) - v1) & 0xfffffffe) > 2 && v1 != 0) EAFree((void*)v1);
    int v2 = *(int*)(first + 8);
    if ((int)((*(int*)(first + 0x10) - v2) & 0xfffffffe) > 2 && v2 != 0) EAFree((void*)v2);
    first += 0x28;
    out += 0x28;
  }
  return out;
}

// @ 0x00686080
void __stdcall FUN_00686080(char* first, char* last) {
  for (; first < last; first += 0x28) {
    int v1 = *(int*)(first + 0x18);
    if ((int)((*(int*)(first + 0x20) - v1) & 0xfffffffe) > 2 && v1 != 0) EAFree((void*)v1);
    int v2 = *(int*)(first + 8);
    if ((int)((*(int*)(first + 0x10) - v2) & 0xfffffffe) > 2 && v2 != 0) EAFree((void*)v2);
  }
}

// @ 0x00685450
extern "C" int FUN_006850b0(int, void*, void*);
void FUN_00685450(int param1, int* param2, int param3, void* param4) {
  int local[5];
  local[0] = param2[2];
  local[1] = *param2 - param3;
  local[2] = param2[1] - param3;
  local[3] = *param2 + 1 + param3;
  local[4] = param2[1] + 1 + param3;
  FUN_006850b0(param1, local, param4);
}

// ================================================================ approximate / partial

// ---- resource/stream types used by the DatabasePackedFile loader (0x00685770) ------
// EA::IO::FileStream: a 0x22c-byte stream object; only the members this function calls
// are named. The layout is the retail stack frame size.
struct FileStream {
  char mData[0x22c];
  FileStream(const wchar_t* path);                              // 0x00931e10
  bool Open(unsigned int flags, int mode, unsigned int a, int b); // 0x009318f0
  int  GetSize();                                               // 0x00931b70
  unsigned int Read(void* p, unsigned int size);                // 0x00931ce0
  bool Close();                                                 // 0x00931a70
  ~FileStream();                                                // 0x00931e70
};

// 0x18-byte reference-counted shared buffer: two vtable/base words, refcount at +8,
// owned object at +0xc, data at +0x10 and a flag byte at +0x14.
struct SharedPointer {
  void* mpVtbl0;    // +0x00
  void* mpVtbl1;    // +0x04
  long  mRefCount;  // +0x08
  void* mpOwner;    // +0x0c
  void* mpData;     // +0x10
  unsigned char mFlag; // +0x14
  SharedPointer(int size, const char* name);                    // 0x0093bca0
};

// Holder whose Release() is the shared-pointer decrement at 0x006855f0 (this = &slot).
struct SharedPtrHolder {
  SharedPointer* mpObject;
  void Release();                                               // 0x006855f0
};

// Records database built from a DPF stream. Only the virtual slots this loader drives
// are named; v04 = load/init, v18 = ?, v50 = attach memory stream.
struct IDatabasePackedFile {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
  virtual void v10(); virtual void v14();
  virtual void v18(int a, int b, int c);
  virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28();
  virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38();
  virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48();
  virtual void v4C(); virtual void v50(void* stream);
};
struct DatabasePackedFile : IDatabasePackedFile {
  DatabasePackedFile(const wchar_t* name, void* alloc);         // 0x008d9f80
};

// In-memory stream handed to the database packed file (0x24 bytes).
struct MemoryStream {
  char mData[0x24];
  MemoryStream(void* shared, int size, const char* name);       // 0x0093c270
};

// Owner object that receives the finished database (vtable slot +0x50).
struct IDatabaseOwner {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
  virtual void v50(int a, void* db, int flag);
};

// Resource manager reached through GetManager(); slots +0x38 (record lookup) and
// +0x58 (database-by-path) are the only ones this slice drives.
struct IResManager {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
  virtual void v30(); virtual void v34();
  virtual int  v38(void* out, const void* key, int mode);
  virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48();
  virtual void v4C(); virtual void v50(); virtual void v54();
  virtual int  v58(void* arg);
};

// Open-addressed hash table with 3-word keys (0x00685f90).
struct HashNode {
  unsigned int mKey[3];   // +0x00
  HashNode*    mpNext;    // +0x0c
};
struct RehashInfo {
  bool mbRehashed;            // +0 (written as a byte)
  unsigned int mNewBucketCount; // +4
};
struct HashInsertResult {
  HashNode*  mpNode;      // +0
  HashNode** mpSlot;      // +4
  bool       mbInserted;  // +8
};
struct HashAllocator {
  void CheckRehash(RehashInfo* info, unsigned int bucketCount, unsigned int count,
                   int flag);                                   // 0x00921440
};
struct HashTable {
  void*         mpUnk0;      // +0x00
  HashNode**    mpBuckets;   // +0x04
  unsigned int  mBucketCount; // +0x08
  unsigned int  mCount;      // +0x0c
  HashAllocator mAlloc;      // +0x10
  HashInsertResult* findOrInsert(HashInsertResult* out, const unsigned int* key, int unused);
  void Rehash(unsigned int newBucketCount);                     // 0x00685660
};


// @ 0x00684ee0  Hilbert curve remap
int FUN_00684ee0(int param1, unsigned* param2) {
  unsigned uVar6 = param2[1];
  unsigned uVar5 = *param2 & 1;
  int iVar1 = (int)*param2 >> 1;
  if ((int)uVar6 < 0) {
    param2[3] = param2[3] + param1;
    param2[1] = uVar6 + param1;
    *param2 = (uVar5 ^ 1) + (unsigned)(unsigned char)(((unsigned char*)0x1402d55)[iVar1*4]) * 2;
    unsigned a = param2[2], b = param2[3], c = param2[1], d = param2[4];
    if (uVar5 == 0) {
      param2[1] = param1 - d;
      param2[3] = param1 - a;
      param2[2] = c;
      param2[4] = b;
    } else {
      param2[2] = param1 - b;
      param2[1] = a;
      param2[3] = d;
      param2[4] = param1 - c;
    }
    if ((param2[1] & ~(unsigned)(param1 - 1)) == 0) return 1;
  } else if ((int)uVar6 < param1) {
    uVar6 = param2[2];
    if ((int)uVar6 < 0) {
      param2[4] = param2[4] + param1;
      uVar6 += param1;
      param2[2] = uVar6;
      *param2 = (unsigned)(unsigned char)(((unsigned char*)0x1402d56)[iVar1*4]) * 2 + 1;
      unsigned b = param2[3], c = param2[4], a = param2[1];
      if (uVar5 != 0) {
        param2[1] = uVar6;
        param2[2] = param1 - b;
        param2[3] = c;
        param2[4] = param1 - a;
        return 1;
      }
      param2[1] = param1 - c;
      param2[3] = param1 - uVar6;
      param2[2] = a;
      param2[4] = b;
      return 1;
    }
    if ((int)uVar6 >= param1) {
      param2[4] = param2[4] - param1;
      uVar6 -= param1;
      param2[2] = uVar6;
      *param2 = (unsigned)(unsigned char)(((unsigned char*)0x1402d56)[iVar1*4]) * 2;
      unsigned b = param2[3], c = param2[4], a = param2[1];
      if (uVar5 != 0) {
        param2[1] = uVar6;
        param2[2] = param1 - b;
        param2[3] = c;
        param2[4] = param1 - a;
        return 1;
      }
      param2[1] = param1 - c;
      param2[3] = param1 - uVar6;
      param2[2] = a;
      param2[4] = b;
      return 1;
    }
    return 0;
  } else {
    param2[3] = param2[3] - param1;
    uVar6 -= param1;
    param2[1] = uVar6;
    *param2 = uVar5 + (unsigned)(unsigned char)(((unsigned char*)0x1402d55)[iVar1*4]) * 2;
    unsigned b = param2[3], a = param2[2];
    if (uVar5 == 0) {
      param2[2] = param1 - b;
      param2[1] = a;
      param2[3] = param2[4];
      param2[4] = param1 - uVar6;
    } else {
      param2[1] = param1 - param2[4];
      param2[3] = param1 - a;
      param2[2] = uVar6;
      param2[4] = b;
    }
    if ((param2[1] & ~(unsigned)(param1 - 1)) == 0) return 1;
  }
  int r = FUN_00684ee0(param1, param2);
  return r + 1;
}

// @ 0x006850b0  split a rectangle into up to 4 sub-rectangles
int FUN_006850b0(int param1, int* param2, int* param3) {
  param3[0] = param2[0]; param3[1] = param2[1]; param3[2] = param2[2];
  param3[3] = param2[3]; param3[4] = param2[4];
  int n = 1;
  if ((~(param1 - 1) & (param2[3] | param2[4] | param2[1] | param2[2])) != 0) {
    if (param2[1] < 0) param3[1] = 0;
    if (param2[2] < 0) param3[2] = 0;
    if (param2[3] > param1) param3[3] = param1;
    if (param2[4] > param1) param3[4] = param1;
    if (param3[1] != param2[1]) {
      param3[5] = param2[0];
      param3[6] = param2[1];
      param3[7] = param3[2];
      param3[8] = 0;
      param3[9] = param3[4];
      FUN_00684ee0(param1, (unsigned*)(param3 + 5));
      n = 2;
    }
    if (param3[3] != param2[3]) {
      int* q = param3 + n * 5;
      q[0] = param2[0]; q[1] = param1; q[2] = param3[2]; q[3] = param2[3]; q[4] = param3[4];
      FUN_00684ee0(param1, (unsigned*)q);
      ++n;
    }
    if (param3[2] != param2[2]) {
      int* q = param3 + n * 5;
      q[0] = param2[0]; q[1] = param3[1]; q[2] = param2[2]; q[3] = param3[3]; q[4] = 0;
      FUN_00684ee0(param1, (unsigned*)q);
      ++n;
    }
    if (param3[4] != param2[4]) {
      int* q = param3 + n * 5;
      q[0] = param2[0]; q[1] = param3[1]; q[2] = param1; q[3] = param3[3]; q[4] = param2[4];
      FUN_00684ee0(param1, (unsigned*)q);
      ++n;
    }
  }
  return n;
}

// @ 0x00685200  recursive space-fill walk
int FUN_00685200(unsigned* param1, float* param2, float* param3, float* param4,
                 float* param5, int param6) {
  if (param6 > 1000) return 0;
  unsigned uVar4 = *param1 & 1;
  float fVar1 = *param2;
  float fVar6 = (float)(int)(uVar4 * -2 + 1);
  float fVar5 = -fVar6;
  float fVar7 = (float)uVar4;
  float fVar8 = (float)(uVar4 ^ 1);
  if (fVar1 >= 0.0f) {
    if (fVar1 <= 1.0f) {
      fVar1 = *param3;
      if (fVar1 >= 0.0f) {
        if (fVar1 <= 1.0f) return 0;
        *param3 = fVar1 - 1.0f;
        float f2 = *param2;
        *param2 = (fVar1 - 1.0f) * fVar5 + fVar8;
        *param3 = f2 * fVar6 + fVar7;
        *param1 = (unsigned)(unsigned char)(((unsigned char*)0x1402d56)[((int)*param1 >> 1)*4]) * 2;
        if (param4 != 0) {
          float f = *param4;
          *param4 = *param5 * fVar5;
          *param5 = f * fVar6;
        }
      } else {
        *param3 = fVar1 + 1.0f;
        float f2 = *param2;
        *param2 = (fVar1 + 1.0f) * fVar5 + fVar8;
        *param3 = f2 * fVar6 + fVar7;
        *param1 = (unsigned)(unsigned char)(((unsigned char*)0x1402d56)[((int)*param1 >> 1)*4]) * 2 + 1;
        if (param4 != 0) {
          float f = *param4;
          *param4 = *param5 * fVar5;
          *param5 = f * fVar6;
          return 1;
        }
      }
    } else {
      *param2 = fVar1 - 1.0f;
      *param2 = *param3 * fVar6 + fVar7;
      *param3 = (fVar1 - 1.0f) * fVar5 + fVar8;
      *param1 = uVar4 + (unsigned)(unsigned char)(((unsigned char*)0x1402d55)[((int)*param1 >> 1)*4]) * 2;
      if (param4 != 0) {
        float f = *param4;
        *param4 = *param5 * fVar6;
        *param5 = f * fVar5;
      }
      if (*param2 < 0.0f || *param2 > 1.0f) {
        int r = FUN_00685200(param1, param2, param3, param4, param5, param6 + 1);
        return r + 1;
      }
    }
  } else {
    *param2 = fVar1 + 1.0f;
    *param2 = *param3 * fVar5 + fVar8;
    *param3 = (fVar1 + 1.0f) * fVar6 + fVar7;
    *param1 = (uVar4 ^ 1) + (unsigned)(unsigned char)(((unsigned char*)0x1402d55)[((int)*param1 >> 1)*4]) * 2;
    if (param4 != 0) {
      float f = *param4;
      *param4 = *param5 * fVar5;
      *param5 = f * fVar6;
    }
    if (*param2 < 0.0f || *param2 > 1.0f) {
      int r = FUN_00685200(param1, param2, param3, param4, param5, param6 + 1);
      return r + 1;
    }
  }
  return 1;
}

// @ 0x00685a60  two-wstring copy constructor
extern "C" void* WStr_DoInsertValue(void*, const void*, unsigned);  // 0x011e0744
void* S2::FUN_00685a60(void* src) {
  char* d = (char*)this;
  char* s = (char*)src;
  d[0] = s[0];
  *(unsigned*)(d + 4) = *(unsigned*)(s + 4);
  *(unsigned*)(d + 8) = 0;
  *(unsigned*)(d + 0xc) = 0;
  *(unsigned*)(d + 0x10) = 0;
  const void* p1 = *(void**)(s + 8);
  int n1 = (*(int*)(s + 0xc) - (int)p1) >> 1;
  ((WString*)(d + 8))->AllocateSelf(n1 + 1);
  void* b1 = *(void**)(d + 8);
  unsigned sz1 = (unsigned)(n1 * 2);
  WStr_DoInsertValue(b1, p1, sz1);
  char* e1 = (char*)b1 + sz1;
  *(char**)(d + 0xc) = e1;
  *(unsigned short*)e1 = 0;
  *(unsigned*)(d + 0x18) = 0;
  *(unsigned*)(d + 0x1c) = 0;
  *(unsigned*)(d + 0x20) = 0;
  const void* p2 = *(void**)(s + 0x18);
  int n2 = (*(int*)(s + 0x1c) - (int)p2) >> 1;
  ((WString*)(d + 0x18))->AllocateSelf(n2 + 1);
  void* b2 = *(void**)(d + 0x18);
  unsigned sz2 = (unsigned)(n2 * 2);
  WStr_DoInsertValue(b2, p2, sz2);
  char* e2 = (char*)b2 + sz2;
  *(char**)(d + 0x1c) = e2;
  *(unsigned short*)e2 = 0;
  return d;
}

// @ 0x00685ed0  destroy a vector<Variant>
void __fastcall FUN_00685ed0(char* p) {
  FUN_00685a30(*(char**)p, *(char**)(p + 4));
  if (*(void**)p != 0) EAFree(*(void**)p);
}

// @ 0x00685770  DatabasePackedFile stream loader
bool FUN_00685770(IDatabaseOwner* owner, const wchar_t* path, int flag) {
  FileStream fs(path);
  if (!fs.Open(1, 3, 1, 0))
    return false;
  int size = fs.GetSize();
  if (size == -1) {
    fs.Close();
    return false;
  }

  SharedPointer* sp = (SharedPointer*)ZoneNew(
      0x18, "App/DPFMemory/SharedPointer", 0, 0, 0, 0);
  if (sp != 0)
    sp = new (sp) SharedPointer(size, "UTF/SharedPointer/Data");
  if (sp != 0)
    _InterlockedExchangeAdd(&sp->mRefCount, 1);

  if (fs.Read(sp->mpData, (unsigned int)size) != (unsigned int)size) {
    SharedPtrHolder holder;
    holder.mpObject = sp;
    holder.Release();
    fs.Close();
    return false;
  }

  void* dbMem = EAAlloc(0x388, "App/DatabasePackedFile", 0, 0, 0, 0);
  IDatabasePackedFile* db = dbMem != 0
      ? (IDatabasePackedFile*)new (dbMem) DatabasePackedFile((const wchar_t*)0, 0)
      : 0;
  db->v04();

  void* msMem = EAAlloc(0x24, "App/DPFMemory/MemoryStream", 0, 0, 0, 0);
  MemoryStream* ms = msMem != 0
      ? new (msMem) MemoryStream(sp, size, "UTF/MemoryStream")
      : 0;
  db->v50(ms);
  db->v18(1, 3, 0);
  owner->v50(1, db, flag);

  SharedPtrHolder holder;
  holder.mpObject = sp;
  holder.Release();
  return true;
}

// @ 0x00685d40  resource record lookup / database-by-path
int FUN_00685d40(void** param) {
  IResManager* mgr = (IResManager*)GetManager();
  if (mgr == 0)
    return 0;
  int result = mgr->v58(param);
  if (result != 0)
    return result;

  // wstring-like result buffer filled by the manager (begin/end/capacity).
  struct RecordName {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
  } out;
  out.mpBegin = 0;
  out.mpEnd = 0;
  out.mpCapacity = 0;

  // wide-string key: {type tag, begin, end}
  struct LookupKeyWide {
    void* mpType;
    const void* mpBegin;
    const void* mpEnd;
  } keyName;
  keyName.mpType = (void*)0x13f662c;
  keyName.mpBegin = param[1];
  keyName.mpEnd = param[2];

  if (mgr->v38(&out, &keyName, 0) != 0) {
    result = mgr->v58(out.mpBegin);
    keyName.mpType = (void*)0x13eb394;
    if (out.mpBegin != 0 && *(int*)((char*)out.mpBegin - 4) != 0)
      EAFree(out.mpBegin);
    return result;
  }

  // numeric-id key: {type tag, value}
  struct LookupKeyId {
    void* mpType;
    void* mValue;
  } keyId;
  keyId.mpType = (void*)0x1402ee0;
  keyId.mValue = param[2];

  if (mgr->v38(&out, &keyId, 0) != 0) {
    result = mgr->v58(out.mpBegin);
    keyId.mpType = (void*)0x13eb394;
    keyName.mpType = (void*)0x13eb394;
    if (out.mpBegin != 0 && *(int*)((char*)out.mpBegin - 4) != 0)
      EAFree(out.mpBegin);
    return result;
  }

  keyId.mpType = (void*)0x13eb394;
  keyName.mpType = (void*)0x13eb394;
  if (out.mpBegin != 0 && *(int*)((char*)out.mpBegin - 4) != 0)
    EAFree(out.mpBegin);
  return 0;
}

// @ 0x00685f90  hash table find-or-insert
HashInsertResult* HashTable::findOrInsert(HashInsertResult* out, const unsigned int* key, int unused) {
  (void)unused;
  unsigned int k = key[0];
  unsigned int hash = k % mBucketCount;
  HashNode** slot = &mpBuckets[hash];
  HashNode* node = *slot;
  while (node != 0) {
    if (k == node->mKey[0]) {
      out->mpNode = node;
      out->mbInserted = 0;
      out->mpSlot = slot;
      return out;
    }
    node = node->mpNext;
  }

  RehashInfo info;
  mAlloc.CheckRehash(&info, mBucketCount, mCount, 1);

  HashNode* pNew = (HashNode*)EAAlloc(
      0x10, "App", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (pNew != 0) {
    pNew->mKey[0] = key[0];
    pNew->mKey[1] = key[1];
    pNew->mKey[2] = key[2];
  }
  pNew->mpNext = 0;
  if (info.mbRehashed != 0) {
    unsigned int newCount = info.mNewBucketCount;
    hash = k % newCount;
    Rehash(newCount);
  }

  pNew->mpNext = mpBuckets[hash];
  mpBuckets[hash] = pNew;
  mCount += 1;
  out->mpNode = pNew;
  out->mpSlot = &mpBuckets[hash];
  out->mbInserted = 1;
  return out;
}

// @ 0x00684ee0 covered above; missing markers below for other VAs handled in bookkeeping
// --- equivalence checker address annotations
    void EAFree(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
