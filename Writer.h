#ifndef THROUGH_WRITER_H
#define THROUGH_WRITER_H

#include <iostream>
#include <vector>
#include <memory>
#include "TypeFile.h"

class Writer {
public:
    virtual void WriteLine(const std::string &) = 0;
};

std::shared_ptr<Writer> ChooseWriter(TypeFile type, const std::string& out_file_name);

#endif //THROUGH_WRITER_H
