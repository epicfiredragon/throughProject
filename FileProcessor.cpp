#include <fstream>
#include "FileProcessor.h"
#include <Poco/Zip/Decompress.h>
#include <Poco/Zip/Compress.h>
#include <Poco/Zip/ZipStream.h>
#include <Poco/StreamCopier.h>
#include <sstream>
#include "key.h"
#include <Poco/Crypto/CipherKey.h>
#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/Cipher.h>
#include <Poco/Crypto/CryptoStream.h>


class ZipFileProcessor : public FileProcessor {
public:
    void Step(std::stringstream &stream) override {
        std::stringstream zip;
        Poco::Zip::Compress compressor(zip, true);
        compressor.addFile(stream, Poco::DateTime(), Poco::Path(".file"));
        compressor.close();
        stream.clear();
        Poco::StreamCopier::copyStream(zip, stream);
    }

    void Restep(std::stringstream &stream) override {
        Poco::Zip::ZipArchive zip(stream);
        auto header = zip.findHeader(".file");
        Poco::Zip::ZipInputStream zip_input_stream(stream, header->second);
        std::stringstream buffer;
        Poco::StreamCopier::copyStream(zip_input_stream, buffer);
        stream.str(std::string());
        stream.clear();
        Poco::StreamCopier::copyStream(buffer, stream);
    }
};

class AESFileProcessor : public FileProcessor {
public:
    void Step(std::stringstream &stream) override {

        Poco::Crypto::CipherFactory &factory = Poco::Crypto::CipherFactory::defaultFactory();
        Poco::Crypto::CryptoInputStream encryptor(stream, factory.createCipher(
                Poco::Crypto::CipherKey("aes-256", key, salt))->createEncryptor());
        Poco::StreamCopier::copyStream(encryptor, stream);
    }

    void Restep(std::stringstream &stream) override {
        Poco::Crypto::CipherFactory &factory = Poco::Crypto::CipherFactory::defaultFactory();
        Poco::Crypto::CryptoInputStream encryptor(stream, factory.createCipher(
                Poco::Crypto::CipherKey("aes-256", key, salt))->createDecryptor());
        Poco::StreamCopier::copyStream(encryptor, stream);
    }
};

std::shared_ptr<FileProcessor> ChooseFileProcessor(FileProcessingStep type) {
    switch (type) {
        case FileProcessingStep::Zip:
            return std::make_shared<ZipFileProcessor>();
        case FileProcessingStep::AES:
            return std::make_shared<AESFileProcessor>();
    }
    throw std::runtime_error("");
}
