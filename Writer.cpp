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
        stream << "<xml>" << std::endl;
    }

    void WriteLine(const std::string &str) override {
        std::stringstream stringstream(str);
        std::string segment;
        while (std::getline(stringstream, segment, '\r')) {
            stream << "<res>" << segment << "</res>" << std::endl;
        }
    }

    ~XMLWriter() {
        stream << "</xml>" << std::endl;
    }
};

class JSONWriter : public Writer {
    std::ostream &stream;

    Poco::JSON::Array array;

public:
    explicit JSONWriter(std::ostream &ostream) : stream(ostream) {}

    void WriteLine(const std::string &str) override {
        std::stringstream stringstream(str);
        std::string segment;
        while (std::getline(stringstream, segment, '\r')) {
            array.add(Poco::Dynamic::Var(segment));
        }
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
