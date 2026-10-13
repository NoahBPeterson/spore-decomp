// EA::Messaging::MessageBasic<N>: N 8-byte data slots and a message id (dev: MessageBasic<5> is 0x30 = 5*8 + 4, aligned
// to 8; MessageBasic<15> 0x80).  Hand-maintained.  Retail layout unverified.
#ifndef GAME_EA_MESSAGING_MESSAGEBASIC_H
#define GAME_EA_MESSAGING_MESSAGEBASIC_H
namespace EA { namespace Messaging {
#pragma pack(push, 8)
template <int N>
class MessageBasic {
 public:
  union Data {
    unsigned int mUint32;
    unsigned __int64 mUint64;
    float mFloat;
    double mDouble;
    void* mpVoid;
  };
  Data mData[N];
  unsigned int mId;
};
#pragma pack(pop)
}}  // namespace EA::Messaging
#endif
