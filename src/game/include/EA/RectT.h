// EA::RectT<T>: left, top, right, bottom (dev: RectT<float>/<int>/<unsigned int> are 0x10).  Hand-maintained.
#ifndef GAME_EA_RECTT_H
#define GAME_EA_RECTT_H
namespace EA {
template <typename T>
class RectT {
 public:
  T mLeft;
  T mTop;
  T mRight;
  T mBottom;
};
}  // namespace EA
#endif
