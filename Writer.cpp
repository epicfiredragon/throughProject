#include <fstream>
#include "Writer.h"
#include <Poco/JSON/Parser.h>


class TextWriter : public Writer {
    std::ostream &stream;

public:
    explicit TextWriter(std::ostream &ostream) : stream(ostream) {}

    void WriteLine(const std::string &line) override {
        stream << line << std::endl;
    }
};

class XMLWriter : public Writer {
    std::ostream &stream;
public:
    explicit XMLWriter(std::ostream &ostream) : stream(ostream) {

    }

    void WriteLine(const std::string & str) override {

    }
};

class JSONWriter : public Writer {
    std::ostream &stream;
    Poco::JSON::Array array;
public:
    explicit JSONWriter(std::ostream &ostream) : stream(ostream) {}

    void WriteLine(const std::string &str) override {
        array.add(Poco::Dynamic::Var(str));
    }

    ~JSONWriter() {
        array.stringify(stream);
    }
};

std::shared_ptr<Writer> ChooseWriter(TypeFile type, std::ostream &stream) {
    switch (type) {
        case TypeFile::Text:
            return std::make_shared<TextWriter>(stream);
        case TypeFile::XML:
            return std::make_shared<XMLWriter>(stream);
        case TypeFile::JSON:
            return std::make_shared<JSONWriter>(stream);
    }
    throw std::runtime_error("");
}
