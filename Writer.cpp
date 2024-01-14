#include <fstream>
#include "Writer.h"

class TextWriter : public Writer {
    std::ostream& stream;
public:
    explicit TextWriter(std::ostream &filename) : stream(filename) {}

    void WriteLine(const std::string &line) override {
        stream << line << std::endl;
    }
};

class XMLWriter : public Writer {
public:
    explicit XMLWriter(std::ostream &filename) {

    }

    void WriteLine(const std::string &) override {

    }
};

class JSONWriter : public Writer {
public:
    explicit JSONWriter(std::ostream &filename) {

    }

    void WriteLine(const std::string &) override {

    }
};

std::shared_ptr<Writer> ChooseWriter(TypeFile type, std::ostream &out_file_name) {
    switch (type) {
        case TypeFile::Text:
            return std::make_shared<TextWriter>(out_file_name);
        case TypeFile::XML:
            return std::make_shared<XMLWriter>(out_file_name);
        case TypeFile::JSON:
            return std::make_shared<JSONWriter>(out_file_name);
    }
}
