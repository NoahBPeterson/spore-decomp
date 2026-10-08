// Slice s0054f1a0: SP::Pollen::cAssetDirectory::Save-style serializer (mutex-guarded save of the
// directory's four hash containers to a save-area file stream).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

namespace EA { namespace Thread {
class Mutex {
public:
    int Lock(const void* pTimeoutAbsolute);   // 0x009221B0
    int Unlock();                             // 0x00922270
    uint32_t mData[0x30 / 4];
};
} }

// Stream written to (slot 14 = Write(data, size)).
class IWriteStream {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual bool Write(const void* pData, int nSize);
};
// Open save file (ref counted; slot 6 = GetStream, slot 9 = Close).
class ISaveFile {
public:
    virtual void s0(); virtual void s1();
    virtual void Release();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual IWriteStream* GetStream();
    virtual void s7(); virtual void s8();
    virtual void Close();
};
// Save area (slot 9 = Close, slot 13 = OpenFile).
class ISaveArea {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8();
    virtual void Close();
    virtual void s10(); virtual void s11(); virtual void s12();
    virtual bool OpenFile(const void* pKey, ISaveFile** ppOut, int a, int b, int c, int d);
};
ISaveArea* GetSaveArea(int id);   // SP::GetSaveArea 0x006B1F90

// intrusive pointer whose operator& releases the current value (0x0041DA30)
struct SaveFilePtr {
    ISaveFile* p;
    SaveFilePtr() : p(0) {}
    ~SaveFilePtr() { if (p) p->Release(); }
    ISaveFile** Reset();       // 0x0041DA30 (releases the held file, returns &p)
    ISaveFile** operator&() { return Reset(); }
    ISaveFile* operator->() const { return p; }
};

template <class Node> struct HBase {
    Node* mpNode;
    Node** mpBucket;
    HBase(Node* n, Node** b) : mpNode(n), mpBucket(b) {}
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0) {
            mpBucket = mpBucket + 1;
            mpNode = *mpBucket;
        }
    }
    __declspec(noinline) void increment_bucket() {   // eastl::hashtable_iterator_base::increment_bucket 0x00552750
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
};
template <class Node> struct HIter : public HBase<Node> {
    HIter(Node* n = 0, Node** b = 0) : HBase<Node>(n, b) {}
    HIter(Node** b) : HBase<Node>(*b, b) {}
    HIter(const HIter& x) : HBase<Node>(x.mpNode, x.mpBucket) {}
};
template <class Node> struct HIterC : public HBase<Node> {
    HIterC(Node* n = 0, Node** b = 0) : HBase<Node>(n, b) {}
    HIterC(Node** b) : HBase<Node>(*b, b) {}
    HIterC(const HIter<Node>& x) : HBase<Node>(x.mpNode, x.mpBucket) {}
    HIterC& operator++() {
        this->mpNode = this->mpNode->mpNext;
        while (this->mpNode == 0) {
            this->mpBucket = this->mpBucket + 1;
            this->mpNode = *this->mpBucket;
        }
        return *this;
    }
};
template <class Node> inline bool operator!=(const HBase<Node>& a, const HBase<Node>& b) { return a.mpNode != b.mpNode; }

// Hash container prefix layout: +4 bucket array, +8 bucket count, +0xc element count.
template <class Node> struct HTable {
    int mPad0;
    Node** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    char mRest[0x20 - 0x10];
    __declspec(noinline) HIter<Node> begin() {                                     // 0x00564140 (out of line in the original)
        HIter<Node> it(mpBucketArray);
        if (it.mpNode == 0) it.increment_bucket();
        return it;
    }
    HIter<Node> beginInline() {
        HIter<Node> it(mpBucketArray);
        if (it.mpNode == 0) it.increment_bucket();
        return it;
    }
    HIter<Node> end() { return HIter<Node>(mpBucketArray + mnBucketCount); }
    uint32_t size() const { return mnElementCount; }
    bool empty() const { return mnElementCount == 0; }
};

struct NodeA { char v[0x18]; NodeA* mpNext; };       // 24-byte value, next at +0x18
struct NodeB { char v[0x10]; NodeB* mpNext; };       // next at +0x10
struct NodeD { char v[8]; NodeD* mpNext; };          // next at +8

// Retail cAssetDirectory layout (only what this function touches).
struct AssetDir {
    int vtbl;
    int pad4;
    EA::Thread::Mutex mMutex;          // +0x08
    char pad38[0x3c - 0x38];
    HTable<NodeA> mTableA;             // +0x3c
    char pad5c[0x9c - 0x5c];
    HTable<NodeD> mTableD;             // +0x9c
    int mbBusy;                        // +0xbc
    char padc0[0xe0 - 0xc0];
    HTable<NodeB> mTableB;             // +0xe0
    HTable<NodeB> mTableC;             // +0x100

    bool Save();
};

struct MutexGuard {
    EA::Thread::Mutex* mpMutex;
    MutexGuard(EA::Thread::Mutex* m, const void* t) : mpMutex(m) { mpMutex->Lock(t); }
    ~MutexGuard() { mpMutex->Unlock(); }
};

extern const int kSaveTimeout;   // 0x013F3CB0
extern const int kSaveKey;       // 0x015E3294
extern const int kMagicA;        // 0x013F3CEC
extern const int kMagicB;        // 0x013F3CE8

// @ 0x0054f1a0
bool AssetDir::Save()
{
    MutexGuard guard(&mMutex, &kSaveTimeout);
    ISaveArea* sa = GetSaveArea(0x11ac19d);
    if (sa != 0) {
        SaveFilePtr file;
        bool ok = true;
        if (!mTableA.empty()) {
            if (sa->OpenFile(&kSaveKey, &file, 2, 2, 1, 0)) {
                IWriteStream* st = file->GetStream();
                ok = st->Write(&kMagicA, 4);
                ok = ok && st->Write(&kMagicB, 4);
                int n = mTableA.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeA> it = mTableA.begin(), e = mTableA.end(); ok && it != e; ++it) {
                    NodeA* nd = it.mpNode;
                    ok = st->Write(nd, 8);
                    ok = ok && st->Write((char*)nd + 0xc, 4);
                    ok = ok && st->Write((char*)nd + 0x10, 4);
                    ok = ok && st->Write((char*)nd + 8, 4);
                }
                n = mTableB.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeB> it = mTableB.begin(), e = mTableB.end(); it != e; ++it) {
                    NodeB* nd = it.mpNode;
                    ok = ok && st->Write(nd, 4);
                    ok = ok && st->Write((char*)nd + 8, 8);
                }
                n = mTableC.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeB> it = mTableC.begin(), e = mTableC.end(); it != e; ++it) {
                    NodeB* nd = it.mpNode;
                    ok = ok && st->Write(nd, 4);
                    ok = ok && st->Write((char*)nd + 8, 8);
                }
                n = mTableD.size();
                ok = ok && st->Write(&n, 4);
                for (HIterC<NodeD> it = mTableD.beginInline(), e = mTableD.end(); ok && it != e; ++it) {
                    NodeD* nd = it.mpNode;
                    ok = st->Write(nd, 8);
                }
                file->Close();
                sa->Close();
            } else {
                return false;
            }
        }
        mbBusy = 0;
        return ok;
    }
    return false;
}
