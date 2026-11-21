// Slice s00a58950: three more instances of the EAPd asset-table init (hashtable open, rehash
// to the element count, load-factor reset to {10000, 2, 0}, grow to the bucket count the
// factor asks for); the same code as EapdAssets::Init 0x00a685e0 (slice s00a68140), each table
// with its own Open / Grow.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE

namespace EA { namespace Audio { namespace Eapd {
    extern float g_ten_k;  // 0x013f0620 (10000.0f)
    extern float g_two;    // 0x01470f1c (2.0f)
}}}

struct Vec3F { float x, y; unsigned z; unsigned Fn(unsigned a); };  // Fn: 0x009213c0

struct CollRecvTable;    // Open 0x00a57750, Grow 0x00a57900
struct ListTableA;       // Open 0x00a656b0, Grow 0x00a658b0
struct ListTableB;       // Open 0x00a53360, Grow 0x00a659e0

template <typename Tag>
class AssetMgrT {
public:
    char pad[0x30];
    unsigned mCount;                   // +0x30
    bool Open(int a, int b, int c);
};

template <typename Tag>
class EapdAssetsT {
public:
    char pad0[8];
    unsigned m8;                       // +0x08
    unsigned mC;                       // +0x0c
    Vec3F    m10;                      // +0x10
    AssetMgrT<Tag> mAssets;            // +0x1c
    void Grow(unsigned n);
    bool Init(int a, int b, int c);
};

template <typename Tag>
bool EapdAssetsT<Tag>::Init(int a, int b, int c)
{
    AssetMgrT<Tag>* am = &mAssets;
    bool r = am->Open(a, b, c);
    if (r) {
        Grow(am->mCount - 1);
        Vec3F v;
        v.x = EA::Audio::Eapd::g_ten_k;
        v.y = EA::Audio::Eapd::g_two;
        v.z = 0;
        m10 = v;
        unsigned n = v.Fn(mC);
        if (n > m8)
            Grow(n);
    }
    return r;
}

// 0x00a58950, 0x00a65db0, 0x00a65e40 (manifest rows name each instance)
template class EapdAssetsT<CollRecvTable>;
template class EapdAssetsT<ListTableA>;
template class EapdAssetsT<ListTableB>;
