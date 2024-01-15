#include "Reader.h"
#include "exeptions.h"
#include <fstream>
#include <Poco/JSON/Parser.h>
#include <Poco/XML/XMLStreamParser.h>
#include <Poco/XML/ParserEngine.h>

class TextReader : public Reader {
    std::istream& stream;
    bool ended;
public:
    explicit TextReader(std::istream &istream): stream(istream) {
        ended = (stream.peek() == EOF);
    }

    std::string ReadNextLine() override {
        std::string ret;
        std::getline(stream, ret);
        ended = (stream.peek() == EOF);
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
    explicit XMLReader(std::istream &istream) {

    }

    std::string ReadNextLine() override {
        return "0";
    }

    bool IsEnd() override {
        return true;
    }
};

class JSONReader : public Reader {
    Poco::SharedPtr<Poco::JSON::Array> array;
    size_t num_of_processed;
public:
    explicit JSONReader(std::istream &istream) {
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(istream);
        auto parsed = result.extract<Poco::JSON::Object::Ptr>();
        if (!parsed->has("expressions")) {
            throw BadFileSyntaxError("");
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

std::shared_ptr<Reader> ChooseReader(TypeFile type, std::istream &stream) {
    switch (type) {
        case TypeFile::Text:
            return std::make_shared<TextReader>(stream);
        case TypeFile::XML:
            return std::make_shared<XMLReader>(stream);
        case TypeFile::JSON:
            return std::make_shared<JSONReader>(stream);
    }
    throw std::runtime_error("");
}
