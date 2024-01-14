#ifndef THROUGH_FILEPROCESSOR_H
#define THROUGH_FILEPROCESSOR_H

#include <memory>

enum class FileProcessingStep {
    Zip, RSA
};

class FileProcessor {
public:
    virtual void Step(std::iostream&) = 0;

    virtual void Restep(std::iostream&) = 0;
};

std::shared_ptr<FileProcessor> ChooseFileProcessor(FileProcessingStep);

#endif //THROUGH_FILEPROCESSOR_H
