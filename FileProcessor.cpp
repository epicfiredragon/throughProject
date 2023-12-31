#include "FileProcessor.h"

class ZipFileProcessor : public FileProcessor {
public:
    void Process(std::string str) override {

    }
};

class RSAFileProcessor : public FileProcessor {
public:
    void Process(std::string str) override {

    }
};

std::shared_ptr<FileProcessor> ChooseFileProcessor(FileProcessingStep type) {
    switch (type) {
        case FileProcessingStep::Zip:
            return std::make_shared<ZipFileProcessor>();
        case FileProcessingStep::RSA:
            return std::make_shared<RSAFileProcessor>();
    }
}
