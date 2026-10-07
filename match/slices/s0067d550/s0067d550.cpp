// Slice s0067d550: EA::IO::StreamCompressionZLib / StreamDecompressionZLib (Open/Write/Read/Close,
// ctors/dtors), EA::Internet::HTTPMultipartFormDataPostBodyStream::Release, cheat-console support
// (SP::cCheatManager console broadcast helpers, built-in cheat commands, console stream) and small
// node/pair constructors for the cheat name containers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "s0067d550.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" long __fastcall _InterlockedExchange(long volatile*, long);
extern "C" long __fastcall _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)

// lib_zlib (called through local thunks; cdecl)
extern "C" int __cdecl deflate(z_stream_s*, int);
extern "C" int __cdecl deflateReset(z_stream_s*);
extern "C" int __cdecl deflateInit2_(z_stream_s*, int level, int method, int windowBits,
                                     int memLevel, int strategy, const char* version, int streamSize);
extern "C" int __cdecl inflate(z_stream_s*, int);
extern "C" int __cdecl inflateInit_(z_stream_s*, const char* version, int streamSize);
extern "C" int __cdecl inflateReset(z_stream_s*);
extern "C" int __cdecl deflateEnd(z_stream_s*);
extern "C" int __cdecl inflateEnd(z_stream_s*);
extern "C" uint32_t __cdecl crc32(uint32_t crc, const uint8_t* buf, uint32_t len);

// EASTL allocator helpers (0x00f473a0 / 0x00f47380)
extern "C" void* __cdecl eaAlloc(unsigned size, const char* pGroup, int flags, unsigned debug,
                                 const char* pFile, int line);
extern "C" void __cdecl eaFree(void* p);

// Placement operator new as used by EA ("App"/"Editor" tagged allocations).
void* __cdecl operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                           const char* pFile, int nLine);

// eastl rbtree helpers
struct SetNode {
  SetNode* mpNodeRight;
  SetNode* mpNodeLeft;
  SetNode* mpNodeParent;
  char mColor;
};
extern "C" SetNode* __cdecl RBTreeIncrement(SetNode* pNode);  // 0x00921580

namespace EA {

// Smart pointer member that AddRefs on attach (slot0 AddRef / slot1 Release interface).
struct IU01 {
  virtual int AddRef();   // +0x00
  virtual int Release();  // +0x04
};
struct Arc01 {
  IU01* mpObject;
  Arc01() : mpObject(0) {}
  explicit Arc01(IU01* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  ~Arc01() {
    if (mpObject) mpObject->Release();
  }
};

// Command interface with AddRef at slot 3 (+0xc) / Release at slot 4 (+0x10).
struct ICmd {
  virtual void pad0();
  virtual void pad1();
  virtual void pad2();
  virtual int AddRef();
  virtual int Release();
};
struct ArcICmd {
  ICmd* mpObject;
  ArcICmd() : mpObject(0) {}
  explicit ArcICmd(ICmd* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
};

// eastl::basic_string<char, allocator> shape (kEmptyString sharing; see 0x00475ab0).
class Key {
 public:
  Key(const char* pInit);                    // 0x0057cb10 (out of line)
  void RangeInitialize(uint32_t nCapacity);  // 0x00475ab0 (out of line)

  char* mpBegin;        // +0x00
  char* mpEnd;          // +0x04
  char* mpCapacity;     // +0x08
  uint32_t mAllocator;  // +0x0c
};

// Smart-pointer interface with AddRef at slot 3 (+0xc) and Release at slot 4 (+0x10).
struct IU34 {
  virtual void pad0();
  virtual void pad1();
  virtual void pad2();
  virtual int AddRef();
  virtual int Release();
};

}  // namespace EA

// hashtable node with only the command reference initialized (key bytes uninitialized).
class PairA {
 public:
  explicit PairA(const EA::Arc01& src) : mpObject(src.mpObject) {
    if (mpObject) mpObject->AddRef();
  }

  uint8_t pad[0x10];     // +0x00 (key string, uninitialized here)
  EA::IU01* mpObject;    // +0x10
};

// rbtree node for a set<basic_string>: 16-byte node header + string at +0x10.
class KeyNode {
 public:
  explicit KeyNode(const char* pInit) : key(pInit) {}

  uint8_t pad[0x10];  // +0x00 node header
  EA::Key key;        // +0x10
};

// ---------------------------------------------------------------- IO::StreamCompressionZLib

namespace EA {
namespace IO {

enum eCompressedFormat { kCompressedFormatZLib = 0, kCompressedFormatGZip = 1 };

// RefCountTemplate<AtomicInt<int>> as second base: vptr at +4, atomic refcount at +8.
struct AtomicIntT {
  volatile long mValue;
  AtomicIntT() { _InterlockedExchange(&mValue, 0); }
};
class RefCountAtomicBase {
 public:
  virtual ~RefCountAtomicBase() {}
  AtomicIntT mRefCount;
};

class StreamCompressionZLib : public IStream, public RefCountAtomicBase {
 public:
  StreamCompressionZLib(IStream* pOutputStream, int nHint);   // @ 0x0067da60
  ~StreamCompressionZLib();                                   // @ 0x0067db10

  bool InitPointers();                                        // 0x0067d330
  bool Open(IStream* pStream, int nHint);                     // @ 0x0067d550 (direct call in ctor)
  bool Close();                                               // @ 0x0067d720
  bool WriteData(const void* pData, uint32_t nSize);          // @ 0x0067d680 (IStream::Write)

  AutoRefT<IStream> mOutputStream;  // +0x0c
  bool mbOpen;                      // +0x10
  bool mbInited;                    // +0x11
  z_stream_s* mpZLibStream;         // +0x14
  eCompressedFormat mFormat;        // +0x18
  int mHint;                        // +0x1c
  uint8_t* mpOutputBuffer;          // +0x20
  uint32_t mnOutputBufferSize;      // +0x24
  uint32_t mInputCRC;               // +0x28
  uint32_t mInputSize;              // +0x2c
};

}  // namespace IO
}  // namespace EA

// @ 0x0067d550
bool EA::IO::StreamCompressionZLib::Open(IStream* pStream, int nHint) {
  bool result = false;
  if (pStream) {
    if (nHint != -1) mHint = nHint;
    mOutputStream = pStream;
    bool wasInited = mbInited;
    if (InitPointers()) {
      if (!wasInited) {
        if (mFormat == kCompressedFormatGZip) {
          deflateInit2_(mpZLibStream, mHint, 8, -15, 8, 1, "1.2.3", sizeof(z_stream_s));
          uint8_t hdr[10];
          hdr[0] = 0x1f;
          hdr[1] = 0x8b;
          hdr[2] = 8;
          hdr[3] = 0;
          hdr[4] = 0;
          hdr[5] = 0;
          hdr[6] = 0;
          hdr[7] = 0;
          hdr[8] = 0;
          hdr[9] = 3;
          mOutputStream.mpObject->Write(hdr, 10);
          mInputSize = 0;
          mInputCRC = crc32(0, 0, 0);
          result = (mFormat == kCompressedFormatGZip);
        } else {
          result = (deflateInit2_(mpZLibStream, mHint, 8, 15, 8, 1, "1.2.3",
                                  sizeof(z_stream_s)) == 0);
        }
      } else {
        result = (deflateReset(mpZLibStream) == 0);
      }
    }
  }
  mbOpen = result;
  return result;
}

// @ 0x0067d680
bool EA::IO::StreamCompressionZLib::WriteData(const void* pData, uint32_t nSize) {
  bool result = mbOpen;
  if (result) {
    mpZLibStream->avail_in = nSize;
    mpZLibStream->next_in = (const uint8_t*)pData;
    do {
      if (mpZLibStream->avail_in == 0) break;
      int r = deflate(mpZLibStream, 0);
      result = (r != -2);
      if (mpZLibStream->avail_out == 0) {
        mOutputStream.mpObject->Write(mpOutputBuffer, mnOutputBufferSize);
        mpZLibStream->avail_out = mnOutputBufferSize;
        mpZLibStream->next_out = mpOutputBuffer;
      }
    } while (result);
    if (mFormat == kCompressedFormatGZip) {
      mInputSize += nSize;
      mInputCRC = crc32(mInputCRC, (const uint8_t*)pData, nSize);
    }
  }
  return result;
}

// @ 0x0067d720
bool EA::IO::StreamCompressionZLib::Close() {
  bool result = true;
  if (mbOpen) {
    int r = deflate(mpZLibStream, 4);
    while (r == 0) {
      mOutputStream.mpObject->Write(mpOutputBuffer, mnOutputBufferSize);
      mpZLibStream->avail_out = mnOutputBufferSize;
      mpZLibStream->next_out = mpOutputBuffer;
      r = deflate(mpZLibStream, 4);
    }
    result = (r == 1);
    if (result) {
      result = mOutputStream.mpObject->Write(mpOutputBuffer,
                                             mnOutputBufferSize - mpZLibStream->avail_out);
      if (mFormat == kCompressedFormatGZip) {
        struct Tail {
          uint32_t crc;
          uint32_t size;
        } tail;
        tail.crc = mInputCRC;
        tail.size = mInputSize;
        result = result && mOutputStream.mpObject->Write(&tail, 8);
      }
    }
    mbOpen = false;
  }
  if (mOutputStream.mpObject) {
    IStream* p = mOutputStream.mpObject;
    mOutputStream.mpObject = 0;
    p->Release();
  }
  return result;
}

// @ 0x0067da60
EA::IO::StreamCompressionZLib::StreamCompressionZLib(IStream* pOutputStream, int nHint)
    : mOutputStream(), mbOpen(false), mbInited(false), mpZLibStream(0), mFormat(kCompressedFormatZLib),
      mHint(nHint), mpOutputBuffer(0), mnOutputBufferSize(0x2000) {
  if (pOutputStream) Open(pOutputStream, nHint);
}

// @ 0x0067db10
EA::IO::StreamCompressionZLib::~StreamCompressionZLib() {
  if (mbInited) {
    if (mbOpen) Close();
    if (mpZLibStream) {
      deflateEnd(mpZLibStream);
      eaFree(mpZLibStream);
      mpZLibStream = 0;
    }
    if (mpOutputBuffer) {
      eaFree(mpOutputBuffer);
      mpOutputBuffer = 0;
    }
  }
}

// ---------------------------------------------------------------- IO::StreamDecompressionZLib

namespace EA {
namespace IO {

class StreamDecompressionZLib : public IStream, public RefCountAtomicBase {
 public:
  StreamDecompressionZLib(int unusedArg);   // @ 0x0067d800
  ~StreamDecompressionZLib();               // @ 0x0067dbc0

  bool InitPointers();                      // 0x0067d490
  bool Open(IStream* pStream);              // @ 0x0067d890
  bool Close();                              // @ 0x0067da10
  int ReadData(void* pData, uint32_t nSize); // @ 0x0067d960 (IStream::Read)

  AutoRefT<IStream> mInputStream;   // +0x0c
  eCompressedFormat mFormat;        // +0x10
  bool mbOpen;                      // +0x14
  bool mbEOF;                       // +0x15
  bool mbInited;                    // +0x16
  z_stream_s* mpZLibStream;         // +0x18
  uint8_t* mpInputBuffer;           // +0x1c
  uint32_t mnInputBufferSize;       // +0x20
};

}  // namespace IO
}  // namespace EA

// @ 0x0067d800
EA::IO::StreamDecompressionZLib::StreamDecompressionZLib(int unusedArg)
    : mInputStream(), mFormat(kCompressedFormatZLib), mbOpen(false), mbEOF(false), mbInited(false),
      mpZLibStream(0), mpInputBuffer(0), mnInputBufferSize(0x2000) {
  (void)unusedArg;
}

// @ 0x0067d890
bool EA::IO::StreamDecompressionZLib::Open(IStream* pStream) {
  bool result = false;
  if (pStream) {
    mInputStream = pStream;
    bool wasInited = mbInited;
    if (InitPointers()) {
      uint32_t nRead = mInputStream.mpObject->Read(mpInputBuffer, mnInputBufferSize);
      mpZLibStream->avail_in = nRead;
      mpZLibStream->next_in = mpInputBuffer;
      mbEOF = (mpZLibStream->avail_in != mnInputBufferSize);
      result = (nRead != (uint32_t)-1);
      if (result) {
        if (wasInited) {
          mbOpen = (inflateReset(mpZLibStream) == 0);
          return mbOpen;
        }
        result = (inflateInit_(mpZLibStream, "1.2.3", sizeof(z_stream_s)) == 0);
      }
    }
  }
  mbOpen = result;
  return result;
}

// @ 0x0067d960
int EA::IO::StreamDecompressionZLib::ReadData(void* pData, uint32_t nSize) {
  bool ok = mbOpen;
  if (ok) {
    mpZLibStream->avail_out = nSize;
    mpZLibStream->next_out = (uint8_t*)pData;
    int r;
    do {
      if (mpZLibStream->avail_in == 0) {
        uint32_t nRead = mInputStream.mpObject->Read(mpInputBuffer, mnInputBufferSize);
        mpZLibStream->avail_in = nRead;
        ok = (nRead != (uint32_t)-1);
        mpZLibStream->next_in = mpInputBuffer;
      }
      r = inflate(mpZLibStream, 0);
      ok = ok && (r != -2);
      mbEOF = (r == 1);
      if (!ok) return -1;
    } while (mpZLibStream->avail_out != 0 && r != 1);
    if (ok) return nSize - mpZLibStream->avail_out;
  }
  return -1;
}

// @ 0x0067da10
bool EA::IO::StreamDecompressionZLib::Close() {
  mbOpen = false;
  IStream* p = mInputStream.mpObject;
  if (p) {
    mInputStream.mpObject = 0;
    p->Release();
  }
  return true;
}

// @ 0x0067dbc0
EA::IO::StreamDecompressionZLib::~StreamDecompressionZLib() {
  if (mbInited) {
    if (mbOpen) {
      mbOpen = false;
      if (mInputStream.mpObject) {
        IStream* p = mInputStream.mpObject;
        mInputStream.mpObject = 0;
        p->Release();
      }
    }
    if (mpZLibStream) {
      inflateEnd(mpZLibStream);
      eaFree(mpZLibStream);
      mpZLibStream = 0;
    }
    if (mpInputBuffer) {
      eaFree(mpInputBuffer);
      mpInputBuffer = 0;
    }
  }
}

// ------------------------------------------- EA::Internet::HTTPMultipartFormDataPostBodyStream

namespace EA {
namespace Internet {

// Second-base refcount block: virtual dtor at slot 0, atomic refcount at +4 of the base.
class RCAtomicBlock {
 public:
  virtual ~RCAtomicBlock() {}
  volatile long mRefCount;
};

class HTTPMultipartFormDataPostBodyStream : public IO::IStream, public RCAtomicBlock {
 public:
  int Release();  // overrides both bases; emitted adjusted for the IStream view
};

}  // namespace Internet
}  // namespace EA

// @ 0x0067da30
int EA::Internet::HTTPMultipartFormDataPostBodyStream::Release() {
  if (_InterlockedExchangeAdd(&mRefCount, -1) - 1 == 0) {
    _InterlockedExchange(&mRefCount, 1);
    delete this;
  }
  return 0;
}

// ------------------------------------------------------------- cheat commands / cCheatManager

// cICheatManager-style interface: AddRef slot0 / Release slot1 / AddCheat slot6.
class ICCheatMgr {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void pad2();
  virtual void pad3();
  virtual void pad4();
  virtual void pad5();
  virtual void AddCheat(const char* pName, void* pCommand, int flag);  // +0x18
};

// Parser interface used by the cheat manager: RegisterCommand slot7, FindCommand slot8.
class IArgParser {
 public:
  virtual void pad0();
  virtual void pad1();
  virtual void pad2();
  virtual void pad3();
  virtual void pad4();
  virtual void pad5();
  virtual void RegisterCommand(void* pCommand);            // +0x1c
  virtual EA::ICmd* FindCommand(const char* pName);        // +0x20
};

// Cheat console interface: Write slot5, SetVisible slot7, Update slot8, Activate slot9.
class IConsole {
 public:
  virtual void pad0();
  virtual void pad1();
  virtual void pad2();
  virtual void pad3();
  virtual void pad4();
  virtual void Write(uint32_t param);                 // +0x14
  virtual void pad6();
  virtual void SetVisible(int show, uint32_t param);  // +0x1c
  virtual void Update(uint32_t param);                // +0x20
  virtual void Activate(uint32_t param);              // +0x24
};

struct ConsoleSetNode : SetNode {
  IConsole* mpConsole;  // +0x10
};
struct ConsoleSet {
  SetNode mAnchor;    // +0x4c in cCheatManager
  uint32_t mnSize;
};

class cCheatManager : public ICCheatMgr {
 public:
  uint8_t pad0[0x44 - 0x4];
  IArgParser* mParser;         // +0x44 (AutoRefCount<cIParser>)
  uint8_t pad1[0x4c - 0x48];
  ConsoleSet mConsoles;        // +0x4c
  uint8_t pad2[0x64 - 0x60];
  bool mbLogEnabled;           // +0x64

  void AddBuiltInCheats();              // @ 0x0067e480
  void BroadcastVisible(uint32_t p);    // @ 0x0067e6f0
  void BroadcastHidden(uint32_t p);     // @ 0x0067e730
  void BroadcastUpdate(uint32_t p);     // @ 0x0067e770
  void BroadcastWrite(uint32_t p);      // @ 0x0067e7b0
  void ActivateConsole(uint32_t p);     // @ 0x0067e7f0
};

// @ 0x0067e6f0
void cCheatManager::BroadcastVisible(uint32_t param) {
  if (mbLogEnabled) {
    SetNode* end = (SetNode*)&mConsoles;
    SetNode* it = mConsoles.mAnchor.mpNodeLeft;
    while (it != end) {
      ((ConsoleSetNode*)it)->mpConsole->SetVisible(1, param);
      it = RBTreeIncrement(it);
    }
  }
}

// @ 0x0067e730
void cCheatManager::BroadcastHidden(uint32_t param) {
  SetNode* end = (SetNode*)&mConsoles;
  SetNode* it = mConsoles.mAnchor.mpNodeLeft;
  while (it != end) {
    ((ConsoleSetNode*)it)->mpConsole->SetVisible(0, param);
    it = RBTreeIncrement(it);
  }
}

// @ 0x0067e770
void cCheatManager::BroadcastUpdate(uint32_t param) {
  if (mbLogEnabled) {
    SetNode* end = (SetNode*)&mConsoles;
    SetNode* it = mConsoles.mAnchor.mpNodeLeft;
    while (it != end) {
      ((ConsoleSetNode*)it)->mpConsole->Update(param);
      it = RBTreeIncrement(it);
    }
  }
}

// @ 0x0067e7b0
void cCheatManager::BroadcastWrite(uint32_t param) {
  SetNode* end = (SetNode*)&mConsoles;
  SetNode* it = mConsoles.mAnchor.mpNodeLeft;
  while (it != end) {
    ((ConsoleSetNode*)it)->mpConsole->Write(param);
    it = RBTreeIncrement(it);
  }
}

// @ 0x0067e7f0
void cCheatManager::ActivateConsole(uint32_t param) {
  SetNode* end = (SetNode*)&mConsoles;
  SetNode* it = mConsoles.mAnchor.mpNodeLeft;
  while (it != end) {
    ((ConsoleSetNode*)it)->mpConsole->Activate(param);
    it = RBTreeIncrement(it);
  }
}

// ---------------------------------------------------------------- built-in cheat command types

// ArgScript command base: ctor out-of-line (0x0083c800), object size 0x10.
class CmdBase {
 public:
  CmdBase();
  uint8_t pad[0x10 - 0x4];
};

// cCheatManager-scope helper interface with AddRef at slot 0.
class ArcMgrTarget {
 public:
  virtual int AddRef();
};

// "help": holds the manager raw and the related command as AutoRefCount (AddRef slot 3).
class HelpCommand : public CmdBase {
 public:
  HelpCommand(cCheatManager* pManager, EA::ICmd* pRelated);
  cCheatManager* mManager;  // +0x10
  EA::ArcICmd mRelated;     // +0x14
};

// "history" / "clear": hold an owning reference to the cheat manager (AddRef slot 0).
class HistoryCommand : public CmdBase {
 public:
  struct ArcMgr {
    ICCheatMgr* mpObject;
    ArcMgr() : mpObject(0) {}
    explicit ArcMgr(ICCheatMgr* p) : mpObject(p) {
      if (mpObject) mpObject->AddRef();
    }
  };
  HistoryCommand(cCheatManager* pManager);
  virtual const char* Description(int idx);
  ArcMgr mOwner;  // +0x10
};

// @ 0x0067e220
HelpCommand::HelpCommand(cCheatManager* pManager, EA::ICmd* pRelated)
    : mManager(pManager), mRelated(pRelated) {}

// @ 0x0067e310
HistoryCommand::HistoryCommand(cCheatManager* pManager) : mOwner(pManager) {}

// @ 0x0067e370
const char* HistoryCommand::Description(int idx) {
  if (idx >= 0 && idx <= 1)
    return "[<items:int>] Lists the last n commands in the command history";
  return 0;
}

// @ 0x0067e3f0
class ClearConsoleCommand : public CmdBase {
 public:
  ClearConsoleCommand(cCheatManager* pManager);
  virtual const char* Description(int idx);
  HistoryCommand::ArcMgr mOwner;  // +0x10
};

ClearConsoleCommand::ClearConsoleCommand(cCheatManager* pManager) : mOwner(pManager) {}

// @ 0x0067e450
const char* ClearConsoleCommand::Description(int idx) {
  if (idx >= 0 && idx <= 1)
    return "Clears the debug console";
  return 0;
}

// @ 0x0067e480
void cCheatManager::AddBuiltInCheats() {
  EA::ICmd* pCmd = mParser->FindCommand("help");
  if (pCmd) pCmd->AddRef();
  if (pCmd) mParser->RegisterCommand(pCmd);
  HelpCommand* pH = new ("App/CheatManager", 0, 0, 0, 0) HelpCommand(this, pCmd);
  AddCheat("help", pH, 0);
  HistoryCommand* pI = new ("App/CheatManager", 0, 0, 0, 0) HistoryCommand(this);
  AddCheat("history", pI, 0);
  ClearConsoleCommand* pC = new ("App/CheatManager", 0, 0, 0, 0) ClearConsoleCommand(this);
  AddCheat("clear", pC, 0);
  if (pCmd) pCmd->Release();
}

// ---------------------------------------------------- cheat name map lookup (stricmp ordering)

// eastl::map<basic_string, ...> with the anchor at this+4 (cStrMap comparator).
class StrNameMap {
 public:
  void LowerBound(SetNode** ppOut, const EA::Key& key);  // @ 0x0067e5c0

  uint8_t pad[4];      // +0
  SetNode mAnchor;     // +4 (mpNodeParent = root)
};

// @ 0x0067e5c0
void StrNameMap::LowerBound(SetNode** ppOut, const EA::Key& key) {
  SetNode* pCandidate = (SetNode*)&mAnchor;
  SetNode* pNode = mAnchor.mpNodeParent;
  while (pNode) {
    if (_stricmp(*(const char**)((char*)pNode + 0x10), key.mpBegin) < 0) {
      pNode = pNode->mpNodeRight;
    } else {
      pCandidate = pNode;
      pNode = pNode->mpNodeLeft;
    }
  }
  *ppOut = pCandidate;
}

// ------------------------------------------------------------ cheat entry pair / node factories

// hashtable value: { basic_string (16 bytes, allocator untouched here), AutoRefCount (slot3/4) }.
class PairB {
 public:
  PairB(const PairB& x);  // @ 0x0067e900
  ~PairB();               // @ 0x0067e830

  char* mpBegin;         // +0x00
  char* mpEnd;           // +0x04
  char* mpCapacity;      // +0x08
  uint32_t mAllocator;   // +0x0c
  EA::IU34* mpCommand;   // +0x10
};

// @ 0x0067e900
PairB::PairB(const PairB& x) : mpBegin(0), mpEnd(0), mpCapacity(0) {
  uint32_t n = x.mpEnd - x.mpBegin;
  ((EA::Key*)this)->RangeInitialize(n + 1);
  memcpy(mpBegin, x.mpBegin, n);
  mpEnd = mpBegin + n;
  *mpEnd = 0;
  mpCommand = x.mpCommand;
  if (mpCommand) mpCommand->AddRef();
}

// @ 0x0067e830
PairB::~PairB() {
  if (mpCommand) mpCommand->Release();
  if ((mpCapacity - mpBegin) > 1 && mpBegin) eaFree(mpBegin);
}

// @ 0x0067e610
PairA* NewPairA(const EA::Arc01& src) {
  return new ("App", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
                           "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
               0xd1) PairA(src);
}

// @ 0x0067e890
KeyNode* NewKeyNode(const char* pString) {
  return new ("App", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
                           "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
               0xd1) KeyNode(pString);
}

// ---------------------------------------------------------------- console stream / dispatch

static char gEmptyStr[2];

// Stream that captures console output into an inline string; plain (non-atomic) refcount.
class RCPlainBlock {
 public:
  virtual ~RCPlainBlock() {}
  int mRefCount;
};

class ConsoleStream : public EA::IO::IStream, public RCPlainBlock {
 public:
  ConsoleStream(EA::IU01* pTarget);  // @ 0x0067e9a0
  ~ConsoleStream();                  // @ 0x0067ea40

  EA::IU01* mTarget;    // +0x0c
  char* mpBegin;        // +0x10
  char* mpEnd;          // +0x14
  char* mpCapacity;     // +0x18
};

// @ 0x0067e9a0
ConsoleStream::ConsoleStream(EA::IU01* pTarget) : mTarget(pTarget) {
  mpBegin = gEmptyStr;
  mpEnd = gEmptyStr;
  mpCapacity = gEmptyStr + 1;
}

// @ 0x0067ea40
ConsoleStream::~ConsoleStream() {
  if ((mpCapacity - mpBegin) > 1 && mpBegin) eaFree(mpBegin);
}

// Dispatch helper class: +8 service (slot 4 call), +0x24 owning cheat manager.
struct IDispatchSvc {
  virtual void pad0();
  virtual void pad1();
  virtual void pad2();
  virtual void pad3();
  virtual int Process(void* pArg);  // +0x10
};

class ConsoleDispatch {
 public:
  int Handle(void* pArg);  // @ 0x0067eab0

  uint8_t pad0[0x8];
  IDispatchSvc* mpService;      // +0x08
  uint8_t pad1[0x24 - 0xc];
  cCheatManager* mManager;      // +0x24
};

// @ 0x0067eab0
int ConsoleDispatch::Handle(void* pArg) {
  int v = mpService->Process(pArg);
  mManager->BroadcastWrite(v);
  return 0;
}

// ------------------------------------------------------------------- cheat reporter / checks

// EA::Trace::LogReporter base: out-of-line ctor (0x00924170), size 0x24.
class LogReporter {
 public:
  LogReporter(int nGroup);
  uint8_t pad[0x24 - 0x4];
};

// @ 0x0067e100
class CheatReporter : public LogReporter {
 public:
  CheatReporter(int nGroup, EA::IU01* pTarget);

  EA::Arc01 mTarget;  // +0x24
};

CheatReporter::CheatReporter(int nGroup, EA::IU01* pTarget) : LogReporter(nGroup), mTarget(pTarget) {}

// Serializer flag checks (helper thunks at 0x00923700 / 0x00923740, stdcall).
extern bool __stdcall FlagCheckA(void* pObj);
extern bool __stdcall FlagCheckB(void* pObj);

// @ 0x0067e160
int __stdcall CheckFlagA(void* pObj) {
  if (((uint8_t*)pObj)[8] & 1) {
    if (!FlagCheckA(pObj)) return 0;
  }
  return 1;
}

// @ 0x0067e190
int __stdcall CheckFlagB(void* pObj) {
  if (((uint8_t*)*((void**)pObj + 3))[8] & 1) {
    if (!FlagCheckB(pObj)) return 0;
  }
  return 1;
}
