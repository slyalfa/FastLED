#pragma once


#include <stdint.h>
#include <stddef.h>
#include "filehandle.h"
#include "namespace.h"
#include "ptr.h"
#include "filehandle.h"
#include "filereader.h"


FASTLED_NAMESPACE_BEGIN

DECLARE_SMART_PTR(SdCard);

class SdCard : public Referent, public FileReader {
  public:
    static SdCardPtr New(int cs_pin);

    virtual ~SdCard() {}  // Use default pins for spi.
    virtual bool begin(int chipSelect) = 0;
    //  End use of card
    virtual void end() = 0;
    virtual void close(FileHandlePtr file) = 0;
    virtual FileHandlePtr openRead(const char *path) = 0;

    virtual bool ls(FileReader::Visitor &visitor) {
      // todo: implement.
      return false;
    }
};

DECLARE_SMART_PTR_CONSTRUCTOR(SdCard, SdCard::New);

FASTLED_NAMESPACE_END
