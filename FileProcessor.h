#ifndef THROUGH_FILEPROCESSOR_H
#define THROUGH_FILEPROCESSOR_H

#include <memory>

enum class FileProcessingStep {
    Zip, AES
};

class FileProcessor {
public:
    virtual void Step(std::stringstream &) = 0;

    virtual void Restep(std::stringstream &) = 0;
};

std::shared_ptr<FileProcessor> ChooseFileProcessor(FileProcessingStep);

#endif //THROUGH_FILEPROCESSOR_H
