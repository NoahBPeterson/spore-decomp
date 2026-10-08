// Slice s005fb430 - cImportExport retail destructor + UpdateExportThumb, and the embedded-image import-info reader at 0x005fbb00.
// Flags: /O2 /MD /Gy /TP
#include "../s005fa8d0/s005fa8d0.h"

// A refcounted-buffer vector: freed only when the buffer's header refcount is non-zero.
struct RefVec {
  void* mpBegin;
  ~RefVec() {
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
  }
};

struct IHandlerBase {
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual ~IHandlerBase() {}
};

// Retail cImportExport: same map block as the dev PDB, but 8 string16 members after the
// embedding image. Layout used by the destructor at 0x005fb900.
struct cImportExportRetail : IHandlerBase {
  eastl::NameKeyMap mNameToKeyMap;   // +0x04
  eastl::KeyNameMap mKeyToNameMap;   // +0x24
  uint32_t mnMachineID;              // +0x44
  SP::Thumbnail::GuidKeyMap mGuidToKeyMap;  // +0x48
  SP::Thumbnail::KeyGuidMap mKeyToGuidMap;  // +0x68
  RefVec mVec88;                     // +0x88
  char pad8c[0xe0 - 0x8c];           // +0x8c
  RefVec mVecE0;                     // +0xe0
  char padE4[0x104 - 0xe4];          // +0xe4
  eastl::string16 s104, s114, s124, s134, s144, s154, s164, s174;
  ~cImportExportRetail();

  unsigned char UpdateExportThumb(void* param_2);   // 0x005fb430
};

// @ 0x005fb900
cImportExportRetail::~cImportExportRetail() {}

// @ 0x005fb430
unsigned char cImportExportRetail::UpdateExportThumb(void* param_2)
{
  // Reconstructed (behavioural) form of the multi-step image-update routine.
  (void)param_2;
  return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x005fbb00: reads the import info (and, optionally, the opened stream) out of an exported
// thumbnail image. The image carries a range-coded payload ("embedded data"): the member at
// cImportExportRetail+0x88 decodes it into a memory stream request, and the stream is then parsed
// as a text header: "spore", a decimal format version (0..6) and a series of fixed-width hex
// fields and length-prefixed strings that fill a cImportInfo.
// ---------------------------------------------------------------------------------------------
#include <stdlib.h>

void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
uint64_t FUN_0092d6f0(const char* s, char** end, int base);                       // 0x0092d6f0 (strtoull)
uint32_t FUN_004bbc70(uint32_t v, int flags);                                      // 0x004bbc70
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int flags);               // 0x00932f30 EA::Hash::FNV1_String16

namespace ImportRead {

struct allocator8 {};
struct string8 {                       // eastl::basic_string<char>
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator8 mAllocator;
    string8(unsigned n, char c, const allocator8& a);    // 0x005f8f30
    __forceinline ~string8() { if ((mpCapacity - mpBegin) > 1 && mpBegin) operator delete[](mpBegin); }
    void resize(unsigned n);                              // 0x00478930
    int compare(const char* s) const;                     // 0x005f79e0
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator; };
void WStr_Format(WString* dst, const wchar_t* fmt, ...);  // 0x0041e050 (eastl::string16::sprintf, this on the stack)

struct SimpleVectorU32 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void push_back(const uint32_t& v);                    // 0x00454860
};

// Layout of cImportInfo (0x90 bytes), see s005fa8d0.h.
struct ImportInfoData {
    uint32_t mVersion;                  // +0x00
    uint32_t m04;                       // +0x04
    uint32_t m08;                       // +0x08
    uint32_t m0c;                       // +0x0c
    uint32_t m10lo, m10hi;              // +0x10
    uint32_t m18lo, m18hi;              // +0x18
    uint32_t m20lo, m20hi;              // +0x20
    WString  mName;                     // +0x28
    uint32_t m38lo, m38hi;              // +0x38
    WString  mDisplayName;              // +0x40
    WString  mDescription;              // +0x50
    WString  mPath;                     // +0x60
    SimpleVectorU32 mIDs;               // +0x70
    uint32_t m7c;                       // +0x7c
    uint32_t m80;                       // +0x80
    uint32_t m84, m88, m8c;             // +0x84 .. +0x8c
    ImportInfoData();                                     // 0x005f8e00
    ~ImportInfoData();                                    // 0x005f8e40
    ImportInfoData& operator=(const ImportInfoData& o);   // 0x005fb350 (cImportInfo::operator=)
};

struct AsyncRequest;

// Memory stream with the text-parsing interface (own vtable).
struct IStream {
    virtual void s0();
    virtual int AddRef();                                  // +0x04
    virtual int Release();                                 // +0x08
    virtual void s3(); virtual void s4();
    virtual int GetState();                                // +0x14
    virtual void Close();                                  // +0x18
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void Read(void* dst, unsigned n);              // +0x30
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual bool Open(AsyncRequest* req);                  // +0x44
    char pad[0x24 - 4];
};
IStream* IStream_ctor(IStream* self, int a);               // 0x0067d800 (declared, see below)

struct AsyncRequest {                                      // Graphics::GraphicsFactoryAsyncRequest
    virtual void s0();
    virtual int AddRef();                                  // +0x04
    virtual int Release();                                 // +0x08
    virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void SetSize(unsigned n);                      // +0x20
    virtual void s9();
    virtual void vf28(int a, int b);                       // +0x28
    char pad[0x24 - 4];
    AsyncRequest(int a, int b, const char* typeName);      // 0x0093c270
    void SetProperty(int id, float value);                 // 0x0093bb40
    void* GetBuffer();                                     // 0x0093ba70
};

struct StreamNode : IStream {
    StreamNode(int a);                                     // 0x0067d800
};

template <typename T>
struct Ref {                                               // EA::AutoRefCount
    T* mp;
    __forceinline Ref(T* p) : mp(p) { if (mp) mp->AddRef(); }
    __forceinline ~Ref() { if (mp) mp->Release(); }
};

// The range decoder of the embedded data (member of cImportExport at +0x88).
struct RangeCoder {
    bool Open(const void* data);                           // 0x0068eb50
    bool GetSize(uint32_t* pSize);                         // 0x0068e670
    int  Read(void* dst, unsigned n);                      // 0x0068e3b0 ((anonymous)::RangeCoder::Read)
    bool Verify(int flags);                                // 0x0068e490 ((anonymous)::RangeCoder::Verify)
};

static __forceinline bool ReadBytes(IStream* s, void* dst, unsigned n)
{
    s->Read(dst, n);
    return s->GetState() == 0;
}

}  // namespace ImportRead

using namespace ImportRead;

struct cImportExportEmbedded {
    char pad[0x88];
    RangeCoder mCoder;                                     // +0x88
    bool ReadImportInfo(const void* data, ImportInfoData* pOutInfo, IStream** ppOutStream);   // 0x005fbb00
};

// @ 0x005fbb00
bool cImportExportEmbedded::ReadImportInfo(const void* data, ImportInfoData* pOutInfo, IStream** ppOutStream)
{
    if (!data)
        return false;

    uint32_t size = (uint32_t)-1;
    bool ok = false;
    if (mCoder.Open(data) && mCoder.GetSize(&size) && size <= 640000) {
        ok = true;

        AsyncRequest* pReq = new ("Thumbnail_cImportExport", 0, 0, 0, 0) AsyncRequest(0, 0, "UTF/MemoryStream");
        Ref<AsyncRequest> req(pReq);
        pReq->SetProperty(1, 1.0f);
        pReq->SetProperty(2, 2.0f);
        pReq->SetSize(size);
        if (mCoder.Read(pReq->GetBuffer(), size) == -1 || !mCoder.Verify(0)) {
            return false;
        }
        pReq->vf28(0, 0);

        StreamNode* pStream = new ("Thumbnail_cImportExport", 0, 0, 0, 0) StreamNode(0);
        Ref<IStream> stream(pStream);
        if (pStream->Open(pReq)) {
            ImportInfoData info;
            const allocator8 alloc;
            string8 buf(0x100, 0, alloc);
            char hex[4];

            buf.resize(5);
            pStream->Read(buf.mpBegin, buf.size());
            ok = pStream->GetState() == 0 && buf.compare("spore") == 0;

            buf.resize(4);
            ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
            info.mVersion = strtoul(buf.mpBegin, 0, 10);
            ok = ok && info.mVersion <= 6;

            buf.resize(8);
            ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
            info.m04 = strtoul(buf.mpBegin, 0, 16);

            if (info.mVersion >= 3) {
                buf.resize(8);
                ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
                info.m08 = strtoul(buf.mpBegin, 0, 16);
            } else {
                info.m08 = ((uint32_t)(uint8_t)FUN_004bbc70(info.m04, 0) << 16) | 0x40006200;
            }
            info.m88 = info.m08;

            if (info.mVersion >= 4) {
                buf.resize(8);
                ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
                info.m8c = strtoul(buf.mpBegin, 0, 16);
                ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
                info.m84 = strtoul(buf.mpBegin, 0, 16);
            }

            buf.resize(16);
            ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
            uint64_t v10 = FUN_0092d6f0(buf.mpBegin, 0, 16);
            info.m10lo = (uint32_t)v10;
            info.m10hi = (uint32_t)(v10 >> 32);

            if (info.mVersion >= 6) {
                buf.resize(16);
                ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
                uint64_t v18 = FUN_0092d6f0(buf.mpBegin, 0, 16);
                info.m18hi = (uint32_t)(v18 >> 32);
                info.m18lo = (uint32_t)v18;
            } else {
                info.m18hi = (uint32_t)-1;
                info.m18lo = (uint32_t)-1;
            }

            buf.resize(16);
            ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
            uint64_t v20 = FUN_0092d6f0(buf.mpBegin, 0, 16);
            info.m20lo = (uint32_t)v20;
            info.m20hi = (uint32_t)(v20 >> 32);

            hex[0] = hex[1] = hex[2] = hex[3] = 0;

            // name
            if (ok && ReadBytes(pStream, hex, 2)) {
                unsigned len = strtoul(hex, 0, 16);
                if (len < 0x100) {
                    buf.resize(len);
                    ok = true;
                    pStream->Read(buf.mpBegin, len);
                    WStr_Format(&info.mName, L"%hs", buf.mpBegin);
                } else
                    ok = false;
            } else
                ok = false;

            if (info.mVersion >= 2) {
                buf.resize(16);
                ok = ok && ReadBytes(pStream, buf.mpBegin, buf.size());
                uint64_t v38 = FUN_0092d6f0(buf.mpBegin, 0, 16);
                info.m38hi = (uint32_t)(v38 >> 32);
                info.m38lo = (uint32_t)v38;
            } else {
                info.m38hi = (uint32_t)-1;
                info.m38lo = (uint32_t)-1;
            }

            // display name, then description
            if (ok && ReadBytes(pStream, hex, 2)) {
                unsigned len = strtoul(hex, 0, 16);
                if (len < 0x100) {
                    buf.resize(len);
                    pStream->Read(buf.mpBegin, len);
                    WStr_Format(&info.mDisplayName, L"%hs", buf.mpBegin);
                    if (ReadBytes(pStream, hex, 3)) {
                        unsigned dlen = strtoul(hex, 0, 16);
                        if (dlen < 0x1000) {
                            ok = true;
                            buf.resize(dlen);
                            pStream->Read(buf.mpBegin, dlen);
                            WStr_Format(&info.mDescription, L"%hs", buf.mpBegin);
                        } else
                            ok = false;
                    } else
                        ok = false;
                } else
                    ok = false;
            } else
                ok = false;

            hex[2] = 0;

            // path
            if (ok && ReadBytes(pStream, hex, 2)) {
                unsigned len = strtoul(hex, 0, 16);
                if (len < 0x100) {
                    buf.resize(len);
                    ok = true;
                    pStream->Read(buf.mpBegin, len);
                    WStr_Format(&info.mPath, L"%hs", buf.mpBegin);
                } else
                    ok = false;
            } else
                ok = false;

            if (info.mVersion >= 5) {
                hex[3] = 0;
                pStream->Read(hex, 2);
                unsigned count = strtoul(hex, 0, 16);
                buf.resize(8);
                for (; count; --count) {
                    pStream->Read(buf.mpBegin, 8);
                    uint32_t id = strtoul(buf.mpBegin, 0, 16);
                    info.mIDs.push_back(id);
                }
            }

            if (info.mVersion < 4) {
                info.m8c = info.m20lo;
                info.m84 = FNV1_String16(info.mName.mpBegin, 0x811c9dc5, 0);
            }

            if (ok) {
                if (pOutInfo)
                    *pOutInfo = info;
                if (ppOutStream) {
                    stream.mp = 0;
                    *ppOutStream = pStream;
                } else {
                    pStream->Close();
                }
            }
        }
    }
    return ok;
}
