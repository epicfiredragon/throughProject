#include <fstream>
#include "Writer.h"

class TextWriter : public Writer {
    std::ostream& stream;
public:
    explicit TextWriter(std::ostream &istream) : stream(istream) {}

    void WriteLine(const std::string &line) override {
        stream << line << std::endl;
    }
};

class XMLWriter : public Writer {
public:
    explicit XMLWriter(std::ostream &istream) {

    }

    void WriteLine(const std::string &) override {

    }
};

class JSONWriter : public Writer {
public:
    explicit JSONWriter(std::ostream &istream) {

    }

    void WriteLine(const std::string &) override {

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
}
