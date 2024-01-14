#include <fstream>
#include "FileProcessor.h"
#include "exeptions.h"
#include <Poco/FileStream.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Zip/Compress.h>
#include <Poco/Timestamp.h>
#include <Poco/File.h>

class ZipFileProcessor : public FileProcessor {
public:
    void Step(std::string str) override {
        std::ofstream zip_file(str + '0', std::ios::binary);
        if (!zip_file.is_open()) {
            throw FileCreationError(str);
        }
        Poco::Zip::Compress compressor(zip_file, true);
        Poco::File from_file(str);
        if (!from_file.exists()) {
            throw FileOpenError(str);
        }
        compressor.addDirectory(from_file.path(), Poco::DateTime());
        compressor.close();
        zip_file.close();
        if (std::remove(str.c_str())) {
            throw FileRemovingError(str);
        }
        if (std::rename((str + '0').c_str(), str.c_str())) {
            throw FileRenamingError(str + '0');
        }
    }

    void Restep(std::string str) override {
        std::ofstream res_file(str + '0', std::ios::binary);
        if (!res_file.is_open()) {
            throw FileCreationError(str);
        }
        Poco::Zip::Compress compressor(res_file, true);
        Poco::File from_file(str);
        if (!from_file.exists()) {
            throw FileOpenError(str);
        }
        compressor.addDirectory(from_file.path(), Poco::DateTime());
        compressor.close();
        res_file.close();
        if (std::remove(str.c_str())) {
            throw FileRemovingError(str);
        }
        if (std::rename((str + '0').c_str(), str.c_str())) {
            throw FileRenamingError(str + '0');
        }
    }
};

class RSAFileProcessor : public FileProcessor {
public:
    void Step(std::string str) override {

    }

    void Restep(std::string str) override {

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
