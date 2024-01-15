#ifndef THROUGH_READER_H
#define THROUGH_READER_H

#include <memory>
#include "TypeFile.h"

class Reader {
public:
    virtual std::string ReadNextLine() = 0;

    virtual bool IsEnd() = 0;

    virtual ~Reader() = default;
};

std::shared_ptr<Reader> ChooseReader(TypeFile type, std::istream &stream);

#endif //THROUGH_READER_H
