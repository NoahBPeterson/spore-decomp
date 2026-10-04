// "Insert disc" prompt dialog and its manager (UI::InsertDisc), the Pollen AES helpers (Encrypt/Decrypt over
// OpenSSL EVP + base64 BIO) and EA::Internet::HTTPMultipartRelatedPostBodyStream.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-  (no /EHsc)
#include "s0060b730.h"

extern IRefCounted* gpInsertDiscHandle;  // 0x015f4200

struct ListNodeBase {
  ListNodeBase* mpNext;
  ListNodeBase* mpPrev;
};

int GetDiscState(int);  // 0x00606610

namespace UI {

class AsyncResourceBase {  // Resource::Async, +0x4
 public:
  AsyncResourceBase() { mpResource = 0; }
  virtual ~AsyncResourceBase() {}
  virtual void as0();
  virtual void as1();
  virtual void as2();
  uint32_t mpResource;  // +0x8
};

class cInsertDiscDialog : public UTFWin::IWinProc, public AsyncResourceBase {
 public:
  __declspec(noinline) cInsertDiscDialog();
  virtual void pv0();
  virtual void pv1();
  virtual void pv2();
  virtual void pv3();
  bool Init();                                      // 0x0060b550 (slice s0060a720)
  void Show(void* pWinProc, uint32_t captionInstanceID);  // 0x0060b5e0
  bool HandleUIMessage(void*, void* pMessage);  // vtable slot 6
  cSPUILayout mLayout;  // +0xc
};

// @ 0x0060b730
cInsertDiscDialog::cInsertDiscDialog() {}

class IEditorDialogA {  // +0x0
 public:
  ~IEditorDialogA() {}
  virtual void a0() = 0;
  virtual void a1() = 0;
  virtual void a2() = 0;
  virtual void Cast() = 0;
  virtual bool Init() = 0;      // +0x10
  virtual bool Shutdown() = 0;  // +0x14
  virtual void Show() = 0;      // +0x18
};
class cEditorResourceB {  // +0x4
 public:
  cEditorResourceB() {}
  ~cEditorResourceB() {}
  virtual void b0();
  virtual void b1();
  virtual void b2();
};
class __declspec(novtable) IWinProcC {  // +0x8
 public:
  virtual void c0() = 0;
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, uint32_t controlID) = 0;  // +0x4
  virtual void c2() = 0;
};
class IPaintSystemD {  // +0xc
 public:
  ~IPaintSystemD() {}
  virtual void d0() = 0;
  virtual bool HandleMessage(uint32_t messageID, void* pData) = 0;  // +0x4
};
class cContentValidationSummarizer {  // +0x10
 public:
  cContentValidationSummarizer() : mField(0) {}
  ~cContentValidationSummarizer() {}
  virtual void e0();
  virtual void e1();
  virtual void e2();
  virtual void e3();
  uint32_t mField;  // +0x14
};
template <typename T>
struct DialogRef {
  T* mpObject;
  DialogRef() : mpObject(0) {}
  ~DialogRef() {
    if (mpObject) mpObject->Release();
  }
  void Assign(T* p);  // 0x00b5f950
  void reset() {
    T* const p = mpObject;
    if (p) {
      mpObject = 0;
      p->Release();
    }
  }
};

// Stack message sent through the message server (SP::MessageBasicRC<5>-like).
class IMessageBase {
 public:
  IMessageBase() {
    mpData[0] = 0;
    pad38 = 0;
  }
  virtual void m0();
  virtual void m1();
  EA::Thread::AtomicInt<int> mRefCount;  // +0x4
  uint32_t mFlags;                       // +0x8
  char pad[0x24];
  uint32_t mpData[2];                    // +0x30, +0x34 (+0x38 follows)
  uint32_t pad38;
  uint32_t pad3c;
};
class SlotMessage : public IMessageBase {
 public:
  SlotMessage() { mFlags = 1; }
  ~SlotMessage();  // 0x00421cf0
  virtual void m0();
  virtual void m1();
};

class InsertDisc : public IEditorDialogA,
                   public cEditorResourceB,
                   public IWinProcC,
                   public IPaintSystemD,
                   public cContentValidationSummarizer {
 public:
  InsertDisc();
  ~InsertDisc();
  virtual void Cast();
  virtual bool Init();
  __declspec(noinline) virtual bool Shutdown();
  virtual void Show();
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, uint32_t controlID);
  virtual bool HandleMessage(uint32_t messageID, void* pData);
  virtual void b0();
  virtual void b1();
  virtual void b2();
  virtual void d0();
  virtual void c0();
  virtual void c2();
  virtual void a0();
  virtual void a1();
  virtual void a2();
  virtual void e0();
  virtual void e1();
  virtual void e2();
  virtual void e3();
  DialogRef<IRefCounted> mpDialog;  // +0x18
  bool mbFlag1c;                    // +0x1c
  bool mbFlag1d;                    // +0x1d
};

// @ 0x0060b760
InsertDisc::InsertDisc() : mbFlag1c(true), mbFlag1d(true) {}

// @ 0x0060b9e0 (destructor body)
InsertDisc::~InsertDisc() {
  Shutdown();
}

// @ 0x0060b800
bool InsertDisc::Shutdown() {
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) {
    pServer->RemoveListener((IMessageListener*)(IPaintSystemD*)this, 0x49a32cb, -9999);
    pServer->RemoveListener((IMessageListener*)(IPaintSystemD*)this, 0x238de9c, -9999);
  }
  mpDialog.reset();
  return true;
}

// @ 0x0060b870
void InsertDisc::OnWinProcEvent(UTFWin::IWindow* pWindow, uint32_t controlID) {
  if (pWindow->GetControlID() == 0x7f86a40 && controlID == 0x7f869a8) mpDialog.reset();
}

// @ 0x0060b8b0
void SetInsertDiscHandle(IRefCounted* p) {
  if (p) p->AddRef();
  if (gpInsertDiscHandle) {
    gpInsertDiscHandle->Release();
    gpInsertDiscHandle = 0;
  }
  if (p) {
    gpInsertDiscHandle = p->Query(0x35ec342a);
    return;
  }
  gpInsertDiscHandle = 0;
}

struct UIMessage {
  UTFWin::IWindow* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mType;             // +0x8
};
struct IInsertDiscHandle : public IRefCounted {
  char pad[0x14];
  IRefCounted* mpDialog;  // +0x18
};
extern IInsertDiscHandle* gpInsertDiscOwner;  // 0x015f4200 (same global, owner view)

// @ 0x0060b910
bool cInsertDiscDialog::HandleUIMessage(void*, void* pMessage) {
  UIMessage* const pMsg = (UIMessage*)pMessage;
  if (pMsg->mType == 0x287259f6) {
    if (pMsg->mpSource->GetControlID() == 0x7f869a8) {
      if (gpInsertDiscHandle) gpInsertDiscHandle->Query(0x7201461);
      IMessageServer* const pServer = SP::MessageServer();
      pServer->MessagePost(0x153c326, 0, 0, 0);
      UTFWin::IWindow* const pWindow = mLayout.FindWindowByID(0x7f86a40, 1);
      if (pWindow) {
        SPUIHelpers::EndModal(pWindow, pMsg->mpSource->GetControlID(), 1);
        pWindow->RemoveWinProc(this);
      }
      mLayout.Shutdown(1);
      IInsertDiscHandle* const pOwner = gpInsertDiscOwner;
      IRefCounted* const p = pOwner->mpDialog;
      if (p) {
        pOwner->mpDialog = 0;
        p->Release();
      }
      return true;
    }
  }
  return false;
}

// @ 0x0060ba40
bool InsertDisc::HandleMessage(uint32_t messageID, void* pData) {
  if (messageID == 0x49a32cb) {
    Show();
    IMessageServer* const pServer = SP::MessageServer();
    if (pServer) pServer->RemoveListener((IMessageListener*)(IPaintSystemD*)this, 0x49a32cb, -9999);
    return true;
  }
  if (messageID == 0x238de9c) {
    Shutdown();
    if (gpInsertDiscHandle) gpInsertDiscHandle->Release();
    gpInsertDiscHandle = 0;
    return true;
  }
  return false;
}

// @ 0x0060bae0
void InsertDisc::Show() {
  IMessageServer* const pServer = SP::MessageServer();
  SlotMessage msg;
  int nResult = 3;
  const int nState = GetDiscState(0);
  switch (nState) {
  case 0:
    msg.mFlags = 1;
    nResult = 6;
    pServer->MessageSend(0x67c75bd6, &msg, 0);
    if (mpDialog.mpObject) mpDialog.reset();
    break;
  case 1:
    msg.mFlags = 1;
    pServer->MessageSend(0x275a9c8c, &msg, 0);
    if (!mpDialog.mpObject) {
      void* const pMem = AllocUIObject(0x24, 4, "UI/cInsertDiscDialog", GetUIHeap());
      mpDialog.Assign(pMem ? (IRefCounted*)new (pMem) cInsertDiscDialog() : 0);
      ((cInsertDiscDialog*)mpDialog.mpObject)->Init();
    }
    ((cInsertDiscDialog*)mpDialog.mpObject)->Show((IWinProcC*)this, 0xdd0763ff);
    break;
  case 2:
    nResult = 0;
    {
      msg.mFlags = 1;
      pServer->MessageSend(0x634297ad, &msg, 0);
      if (!mpDialog.mpObject) {
        void* const pMem = AllocUIObject(0x24, 4, "UI/cInsertDiscDialog", GetUIHeap());
        mpDialog.Assign(pMem ? (IRefCounted*)new (pMem) cInsertDiscDialog() : 0);
        ((cInsertDiscDialog*)mpDialog.mpObject)->Init();
      }
      ((cInsertDiscDialog*)mpDialog.mpObject)->Show((IWinProcC*)this, 0x49d1ee03);
    }
    break;
  default:
    nResult = 0;
    break;
  }
  msg.mFlags = nResult * 7;
  SP::MessageServer()->MessageSend(0xeda117de, &msg, 0);
}

}  // namespace UI

// ---------------------------------------------------------------------------------------------
// Pollen AES helpers (OpenSSL EVP + base64 BIO)

struct evp_cipher_st;
struct bio_st;
struct bio_method_st;
struct evp_cipher_ctx_st {
  uint32_t pad[35];  // size 0x8c
};
extern "C" {
int RAND_pseudo_bytes(unsigned char* buf, int num);  // 0x01178650
void EVP_CIPHER_CTX_init(evp_cipher_ctx_st* ctx);     // 0x011765f0
int EVP_CIPHER_CTX_cleanup(evp_cipher_ctx_st* ctx);   // 0x01176a20
const evp_cipher_st* EVP_aes_256_cbc();               // 0x01178390 (exact cipher unverified)
int EVP_EncryptInit_ex(evp_cipher_ctx_st* ctx, const evp_cipher_st* type, void* impl, const unsigned char* key,
                       const unsigned char* iv);  // 0x01176d50
int EVP_EncryptUpdate(evp_cipher_ctx_st* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);  // 0x01176610
int EVP_EncryptFinal_ex(evp_cipher_ctx_st* ctx, unsigned char* out, int* outl);  // 0x01176770
int EVP_DecryptInit_ex(evp_cipher_ctx_st* ctx, const evp_cipher_st* type, void* impl, const unsigned char* key,
                       const unsigned char* iv);  // 0x01176d80
int EVP_DecryptUpdate(evp_cipher_ctx_st* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);  // 0x01176820
int EVP_DecryptFinal_ex(evp_cipher_ctx_st* ctx, unsigned char* out, int* outl);  // 0x01176910
const bio_method_st* BIO_f_base64();                 // 0x01177970
const bio_method_st* BIO_s_mem();                    // 0x011774f0
bio_st* BIO_new(const bio_method_st* type);          // 0x01177470
bio_st* BIO_new_mem_buf(void* buf, int len);         // 0x01177500
void BIO_set_flags(bio_st* b, int flags);            // 0x01176fb0
bio_st* BIO_push(bio_st* b, bio_st* append);         // 0x01177380
int BIO_read(bio_st* b, void* data, int len);        // 0x01176fc0
int BIO_write(bio_st* b, const void* data, int len); // 0x01177070
long BIO_ctrl(bio_st* b, int cmd, long larg, void* parg);  // 0x01177260
void BIO_free_all(bio_st* a);                        // 0x01177420
void Memset32(void* pDest, uint32_t value, uint32_t count);  // 0x0092cb00
}

const uint32_t kAESKeyWords = 8;

// @ 0x0060bc90
void GetAESKey(uint32_t* pKey) {
  pKey[0] = 0x44db12e;
  pKey[1] = 0x5005f78;
  pKey[2] = 0x50fad80;
  pKey[3] = 0xb7bcef68;
  pKey[4] = 0x662da01;
  pKey[5] = 0x4fd2bd3;
  pKey[6] = 0x662d9ed;
  pKey[7] = 0x5005f78;
}

// @ 0x0060bcd0
template <>
string8& string8::assign(const char* p, size_type n) {
  return assign(p, p + n);
}

// @ 0x0060c4e0
template <>
string8& string8::append(const char* p) {
  const char* const p1 = p + 1;
  const char* q = p;
  while (*q++) {
  }
  return append(p, p + (q - p1));
}

// @ 0x0060bcf0
void Encrypt(const string8& plain, string8& out) {
  if (plain.mpEnd - plain.mpBegin == 0) {
    out.assign("", "");
    return;
  }
  unsigned char iv[16];
  struct {
    unsigned char iv[16];
    unsigned char data[0x70];
  } packet;
  RAND_pseudo_bytes(iv, 16);
  ((uint32_t*)packet.iv)[0] = ((uint32_t*)iv)[0];
  ((uint32_t*)packet.iv)[1] = ((uint32_t*)iv)[1];
  ((uint32_t*)packet.iv)[2] = ((uint32_t*)iv)[2];
  ((uint32_t*)packet.iv)[3] = ((uint32_t*)iv)[3];
  evp_cipher_ctx_st ctx;
  EVP_CIPHER_CTX_init(&ctx);
  uint32_t key[64];
  key[0] = 0x44db12e;
  key[1] = 0x5005f78;
  key[2] = 0x50fad80;
  key[3] = 0xb7bcef68;
  key[4] = 0x662da01;
  key[5] = 0x4fd2bd3;
  key[6] = 0x662d9ed;
  key[7] = 0x5005f78;
  if (EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), 0, (const unsigned char*)key, iv) > 0) {
    int nOut = 0x70;
    if (EVP_EncryptUpdate(&ctx, packet.data, &nOut, (const unsigned char*)plain.c_str(), (int)plain.size()) > 0) {
      const int nFirst = nOut;
      nOut = 0x70 - nOut;
      if (EVP_EncryptFinal_ex(&ctx, packet.data + nFirst, &nOut) > 0) {
        bio_st* const pBase64 = BIO_new(BIO_f_base64());
        bio_st* const pMem = BIO_new(BIO_s_mem());
        BIO_set_flags(pBase64, 0x100);
        bio_st* const pChain = BIO_push(pBase64, pMem);
        if (pChain) {
          BIO_write(pChain, packet.iv, nFirst + 0x10 + nOut);
          BIO_ctrl(pChain, 11, 0, 0);
          char* pData;
          nOut = (int)BIO_ctrl(pChain, 3, 0, &pData);
          out.assign(pData, nOut);
        }
        BIO_free_all(pChain);
      }
    }
  }
  Memset32(key, 0, kAESKeyWords);
  EVP_CIPHER_CTX_cleanup(&ctx);
}

// @ 0x0060bf00
void Decrypt(const string8& encrypted, string8& out) {
  if (encrypted.size() == 0) {
    out.assign("", "");
    return;
  }
  bio_st* const pBase64 = BIO_new(BIO_f_base64());
  bio_st* const pSource = BIO_new_mem_buf((void*)encrypted.c_str(), -1);
  BIO_set_flags(pBase64, 0x100);
  bio_st* const pChain = BIO_push(pBase64, pSource);
  if (pChain) {
    struct {
      unsigned char iv[16];
      unsigned char data[0x70];
    } packet;
    int nRead = BIO_read(pChain, &packet, 0x80);
    if (nRead > 0x10) {
      uint32_t iv[4];
      iv[0] = ((uint32_t*)packet.iv)[0];
      iv[1] = ((uint32_t*)packet.iv)[1];
      iv[2] = ((uint32_t*)packet.iv)[2];
      iv[3] = ((uint32_t*)packet.iv)[3];
      evp_cipher_ctx_st ctx;
      EVP_CIPHER_CTX_init(&ctx);
      uint32_t key[64];
      GetAESKey(key);
      if (EVP_DecryptInit_ex(&ctx, EVP_aes_256_cbc(), 0, (const unsigned char*)key, (const unsigned char*)iv) > 0) {
        unsigned char plain[0x80];
        int nOut = 0x80;
        if (EVP_DecryptUpdate(&ctx, plain, &nOut, packet.data, nRead - 0x10) > 0) {
          const int nFirst = nOut;
          nOut = 0x80 - nOut;
          if (EVP_DecryptFinal_ex(&ctx, plain + nFirst, &nOut) > 0) out.sprintf("%.*s", nFirst + nOut, plain);
        }
      }
      Memset32(key, 0, kAESKeyWords);
      EVP_CIPHER_CTX_cleanup(&ctx);
    }
  }
  BIO_free_all(pChain);
}

// ---------------------------------------------------------------------------------------------
// EA::Internet::HTTPMultipartRelatedPostBodyStream (layout from the 2008 PDB)

namespace EA {
namespace IO {
class IStream {
 public:
  IStream() {}
  virtual ~IStream() {}
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;  // +0x24
  virtual bool SetPosition(int position, int positionType);
  virtual uint32_t GetAvailable() const;
  virtual uint32_t Read(void* pData, uint32_t nSize);
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);  // +0x38
};
class MemoryStream : public IStream {
 public:
  MemoryStream(void* pData, uint32_t nSize, const char* pName);  // 0x0093c270
  void SetOption(int option, float value);                       // 0x0093bb40
  char pad[0x24 - 4];
};
}  // namespace IO
namespace COM {
template <typename T>
class RefCountTemplateA {
 public:
  virtual ~RefCountTemplateA() {}
  T mRefCount;
};
}  // namespace COM
}  // namespace EA

namespace EA {
namespace Internet {

class IHTTPPostBodyStream : public IO::IStream {
 public:
  virtual void pv3c();
  virtual bool GetContentTypeString(string8& sContentType);  // +0x40
  virtual bool Finalize();                                    // +0x44
  virtual bool SetBoundary(const char* pBoundary);            // +0x48
  virtual const char* GetBoundary() const;                    // +0x4c
  virtual void pv50();
  virtual bool AddFormData(const char* pName, const char* pValue);  // +0x54
  virtual bool AddFormDataXML(const char* pXML);                    // +0x58
  virtual void pv5c();
  virtual void WriteToStream(const char* pText, IO::IStream* pStream);  // +0x60
  virtual bool WriteEndBoundary();                                      // +0x64
  virtual bool pv68();
};

struct IStreamNode : public ListNodeBase {
  IO::IStream* mpStream;
};
struct IStreamList {
  IStreamList() {
    mNode.mpNext = &mNode;
    mNode.mpPrev = &mNode;
  }
  ~IStreamList() { DoClear(); }
  ListNodeBase mNode;
  uint32_t mAllocator;
  void DoClear();  // 0x0060c4a0
};

struct MemStreamRef {
  IO::MemoryStream* mpObject;
  MemStreamRef() : mpObject(0) {}
  ~MemStreamRef() {
    if (mpObject) mpObject->Release();
  }
  MemStreamRef& operator=(IO::MemoryStream* p) {
    IO::MemoryStream* const pTemp = mpObject;
    if (p != pTemp) {
      if (p) p->AddRef();
      mpObject = p;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
};

static __forceinline unsigned int InlineStrlen(const char* p) {
  const char* c = p;
  const char* const p1 = c + 1;
  while (*c++) {
  }
  return (unsigned int)(c - p1);
}

class HTTPMultipartRelatedPostBodyStream : public IHTTPPostBodyStream,
                                           public COM::RefCountTemplateA<Thread::AtomicInt<int> > {
 public:
  enum eFormDataType { kText = 0, kStream = 1 };
  HTTPMultipartRelatedPostBodyStream();
  ~HTTPMultipartRelatedPostBodyStream();

  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;
  virtual bool SetPosition(int position, int positionType);
  virtual uint32_t GetAvailable() const;
  virtual uint32_t Read(void* pData, uint32_t nSize);
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);
  virtual bool GetContentTypeString(string8& sContentType);
  virtual bool Finalize();
  virtual bool SetBoundary(const char* pBoundary);
  virtual const char* GetBoundary() const;
  virtual bool AddFormData(const char* pName, const char* pValue);
  virtual bool AddFormDataXML(const char* pXML);
  virtual void WriteToStream(const char* pText, IO::IStream* pStream);
  virtual bool WriteEndBoundary();

  IStreamList mFormDataList;       // +0xc
  string8 msBoundary;              // +0x18
  IStreamNode* mReadItr;           // +0x28
  long mnPosition;                 // +0x2c
  unsigned int mnSize;             // +0x30
  int mnState;                     // +0x34
  bool mbFinal;                    // +0x38
  eFormDataType mLastDataType;     // +0x3c
  unsigned int mnTextStart;        // +0x40
  MemStreamRef mpMemStream;        // +0x44
};

// Same layout as the related stream; only GetAvailable of this variant is in this slice.
class HTTPMultipartFormDataPostBodyStream {
 public:
  uint32_t GetAvailable() const;  // vtable slot 0x2c
  char pad[0x2c];
  long mnPosition;       // +0x2c
  unsigned int mnSize;   // +0x30
  int mnState;           // +0x34
  bool mbFinal;          // +0x38
};

// @ 0x0060c0f0
uint32_t HTTPMultipartFormDataPostBodyStream::GetAvailable() const {
  if (!mbFinal) return (uint32_t)-1;
  if (mnState != 0) return (uint32_t)-1;
  return mnSize - mnPosition;
}

// @ 0x0060c0b0
int HTTPMultipartRelatedPostBodyStream::GetPosition(int positionType) const {
  int nResult = -1;
  if (mbFinal && mnState == 0) {
    if (positionType == 0) return mnPosition;
    if (positionType == 1) return 0;
    if (positionType == 2) nResult = mnPosition - mnSize;
  }
  return nResult;
}

// @ 0x0060c110
void HTTPMultipartRelatedPostBodyStream::WriteToStream(const char* pText, IO::IStream* pStream) {
  const uint32_t nLength = InlineStrlen(pText);
  pStream->Write(pText, nLength);
}

// @ 0x0060c140
bool HTTPMultipartRelatedPostBodyStream::Flush() {
  mnState = -1;
  return false;
}

// @ 0x0060c150
bool HTTPMultipartRelatedPostBodyStream::Write(const void*, uint32_t) {
  mnState = -1;
  return false;
}

// @ 0x0060c160
bool HTTPMultipartRelatedPostBodyStream::Finalize() {
  if (!mbFinal && mnState != -1) {
    if (mpMemStream.mpObject->GetPosition(0) > 0) {
      mbFinal = WriteEndBoundary();
      mnPosition = 0;
      return mbFinal;
    }
    mbFinal = true;
    mnPosition = 0;
  }
  return mbFinal;
}

// @ 0x0060c1b0
bool HTTPMultipartRelatedPostBodyStream::AddFormData(const char* pName, const char* pValue) {
  if (mbFinal) mnState = -1;
  if (!pName) mnState = -1;
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream.mpObject->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream.mpObject);
    mpMemStream.mpObject->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\nContent-Disposition: form-data; name=\"", mpMemStream.mpObject);
    WriteToStream(pName, mpMemStream.mpObject);
    WriteToStream("\"\r\n\r\n", mpMemStream.mpObject);
    WriteToStream(pValue, mpMemStream.mpObject);
    if (mpMemStream.mpObject->GetState() != 0)
      mnState = -1;
    else
      return true;
  }
  return false;
}

// @ 0x0060c290
bool HTTPMultipartRelatedPostBodyStream::AddFormDataXML(const char* pXML) {
  if (mbFinal) mnState = -1;
  if (!pXML) mnState = -1;
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream.mpObject->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream.mpObject);
    mpMemStream.mpObject->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\nContent-Type: application/atom+xml; charset=UTF-8", mpMemStream.mpObject);
    WriteToStream("\r\n\r\n", mpMemStream.mpObject);
    WriteToStream(pXML, mpMemStream.mpObject);
    if (mpMemStream.mpObject->GetState() != 0)
      mnState = -1;
    else
      return true;
  }
  return false;
}

// @ 0x0060c360
bool HTTPMultipartRelatedPostBodyStream::WriteEndBoundary() {
  if (mpMemStream.mpObject) {
    const uint32_t nPosition = mpMemStream.mpObject->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream.mpObject);
    mpMemStream.mpObject->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("--\r\n", mpMemStream.mpObject);
    if (mpMemStream.mpObject->GetState() != 0) {
      mnState = -1;
    } else {
      mLastDataType = kText;
      return pv68();
    }
  }
  return false;
}


// @ 0x0060c3f0
uint32_t HTTPMultipartRelatedPostBodyStream::Read(void* pData, uint32_t nSize) {
  if (!mbFinal) return (uint32_t)-1;
  if (mnState != 0) return (uint32_t)-1;
  if (!pData) {
    mnState = -1;
    return (uint32_t)-1;
  }
  if (mnPosition == 0 && (IStreamNode*)&mFormDataList == mReadItr) mReadItr = (IStreamNode*)mFormDataList.mNode.mpNext;
  uint32_t nRead = 0;
  while (nRead < nSize) {
    if (mReadItr == (IStreamNode*)&mFormDataList) break;
    const uint32_t n = mReadItr->mpStream->Read((char*)pData + nRead, nSize - nRead);
    if (n == (uint32_t)-1) {
      nRead = (uint32_t)-1;
      break;
    }
    mnPosition += n;
    nRead += n;
    if (mReadItr->mpStream->GetAvailable() == 0) {
      mReadItr = (IStreamNode*)mReadItr->mpNext;
      if (mReadItr == (IStreamNode*)&mFormDataList) break;
    }
  }
  return nRead;
}

// @ 0x0060c510
HTTPMultipartRelatedPostBodyStream::HTTPMultipartRelatedPostBodyStream()
    : msBoundary("EA_HTTP_REQUEST_SIMPLE_BOUNDARY"),
      mnPosition(-1),
      mnSize(0),
      mnState(0),
      mbFinal(false),
      mLastDataType(kStream),
      mnTextStart(0) {
  mReadItr = (IStreamNode*)&mFormDataList;
  mpMemStream = new ("Pollinator", 0, 0, 0, 0) IO::MemoryStream(0, 0, "UTF/MemoryStream");
  mpMemStream.mpObject->SetOption(1, 1.0f);
  mpMemStream.mpObject->SetOption(2, 0.0f);
  mpMemStream.mpObject->SetOption(3, 1024.0f);
}

// @ 0x0060c660
HTTPMultipartRelatedPostBodyStream::~HTTPMultipartRelatedPostBodyStream() {}

// @ 0x0060c6d0
bool HTTPMultipartRelatedPostBodyStream::SetBoundary(const char* pBoundary) {
  if (pBoundary && InlineStrlen(pBoundary) <= 0x46 && InlineStrlen(pBoundary) >= 1 &&
      mFormDataList.mNode.mpNext == &mFormDataList.mNode) {
    msBoundary.assign(pBoundary);
    return true;
  }
  mnState = -1;
  return false;
}

// @ 0x0060c730
bool HTTPMultipartRelatedPostBodyStream::GetContentTypeString(string8& sContentType) {
  sContentType.assign("multipart/related; boundary=", "multipart/related; boundary=" + 28);
  const char* const pBoundary = GetBoundary();
  sContentType.append(pBoundary, pBoundary + InlineStrlen(pBoundary));
  return true;
}

}  // namespace Internet
}  // namespace EA
