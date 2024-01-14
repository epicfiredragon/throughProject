#include <fstream>
#include "Poco/Foundation.h"
#include "FileProcessor.h"
#include <Poco/Zip/Decompress.h>
#include <Poco/Zip/Compress.h>
#include <Poco/Zip/ZipStream.h>
#include <Poco/StreamCopier.h>
#include <sstream>

class ZipFileProcessor : public FileProcessor {
public:
    void Step(std::iostream &stream) override {
        std::stringstream zip;
        Poco::Zip::Compress compressor(zip, true);
        compressor.addFile(stream, Poco::DateTime(), Poco::Path(".file"));
        compressor.close();
        stream.clear();
        Poco::StreamCopier::copyStream(zip, stream);
    }

    void Restep(std::iostream& stream) override {
        Poco::Zip::ZipArchive zip(stream);
        auto header = zip.findHeader(".file");
        Poco::Zip::ZipInputStream zip_input_stream(stream, header->second);
        Poco::StreamCopier::copyStream(zip_input_stream, stream);
    }
};

class RSAFileProcessor : public FileProcessor {
public:
    void Step(std::iostream& stream) override {

    }

    void Restep(std::iostream& stream) override {

    }
};

std::shared_ptr<FileProcessor> ChooseFileProcessor(FileProcessingStep type) {
    switch (type) {
        case FileProcessingStep::Zip:
            return std::make_shared<ZipFileProcessor>();
        case FileProcessingStep::RSA:
            return std::make_shared<RSAFileProcessor>();
    }
    throw std::runtime_error("");
}
