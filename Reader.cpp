#include "Reader.h"
#include "exeptions.h"
#include <fstream>
#include <Poco/JSON/Parser.h>
#include <Poco/XML/XMLStreamParser.h>
#include <Poco/XML/ParserEngine.h>

class TextReader : public Reader {
    std::ifstream stream;
    bool ended;
public:
    explicit TextReader(const std::string &filename): stream(filename) {
        if (!stream.is_open()) {
            throw FileOpenError(filename);
        }
        ended = (stream.peek() != EOF);
    }

    std::string ReadNextLine() override {
        std::string ret;
        std::getline(stream, ret);
        ended = (stream.peek() != EOF);
        return ret;
    }

    bool IsEnd() override {
        return ended;
    }
};

class XMLReader : public Reader {
    Poco::SharedPtr<Poco::JSON::Array> array;
    size_t num_of_processed;
public:
    explicit XMLReader(const std::string &filename) {

    }

    std::string ReadNextLine() override {

    }

    bool IsEnd() override {
        return ended;
    }
};

class JSONReader : public Reader {
    Poco::SharedPtr<Poco::JSON::Array> array;
    size_t num_of_processed;
public:
    explicit JSONReader(const std::string &filename) {
        std::ifstream stream(filename);
        if (!stream.is_open()) {
            throw FileOpenError(filename);
        }
        Poco::JSON::Parser parser;
        auto parsed = parser.parse(stream).extract<Poco::JSON::Object::Ptr>();
        if (!parsed->has("expressions")) {
            throw BadFileSyntaxError(filename);
        }
        array = parsed->getArray("expressions");
        num_of_processed = 0;
    }

    std::string ReadNextLine() override {
        return array->getElement<std::string>(num_of_processed++);
    }

    bool IsEnd() override {
        return array->size() > num_of_processed;
    }
};

std::shared_ptr<Reader> ChooseReader(TypeFile type, const std::string &in_file_name) {
    switch (type) {
        case TypeFile::Text:
            return std::make_shared<TextReader>(in_file_name);
        case TypeFile::XML:
            return std::make_shared<XMLReader>(in_file_name);
        case TypeFile::JSON:
            return std::make_shared<JSONReader>(in_file_name);
    }
}
