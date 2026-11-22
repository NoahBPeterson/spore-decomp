// Slice s00fca0b0: rw::movie::MovieEncoder_Avi scalar deleting destructor. The class's
// destructor destroys the callback slot at +0x14 (an empty out-of-line destructor) and the base
// destructor restores the base vtable (0x01493d00).
#include "types.h"

namespace rw {
namespace movie {

struct MovieEncoderBase {
  virtual ~MovieEncoderBase() {}  // vtable at +0x00
  int mField04;                   // +0x04
};

struct EncodedDataCallback {
  void* mpCallback;  // +0x00
  void* mpContext;   // +0x04
  ~EncodedDataCallback();
};

class MovieEncoder_Avi : public MovieEncoderBase {
public:
  MovieEncoder_Avi();
  virtual ~MovieEncoder_Avi() {}

  void*               mpErrorCallback;      // +0x08
  void*               mpErrorContext;       // +0x0c
  int                 mField10;             // +0x10
  EncodedDataCallback mEncodedDataCallback; // +0x14
};

MovieEncoder_Avi::MovieEncoder_Avi() {}

}  // namespace movie
}  // namespace rw

// The compiler emits the destructor with the class's vtable:
// @ 0x00fca0b0  ??_GMovieEncoder_Avi@movie@rw@@UAEPAXI@Z (scalar deleting destructor)
