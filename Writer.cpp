#include "Writer.h"

class TextWriter : public Writer {
public:
    explicit TextWriter(const std::string &filename);

    void WriteLine(const std::string &) override;
};

class XMLWriter : public Writer {
public:
    explicit XMLWriter(const std::string &filename);

    void WriteLine(const std::string &) override;
};

class JSONWriter : public Writer {
public:
    explicit JSONWriter(const std::string &filename);

    void WriteLine(const std::string &) override;
};

TextWriter::TextWriter(const std::string &filename) {}

void TextWriter::WriteLine(const std::string &) {}

XMLWriter::XMLWriter(const std::string &filename) {}

void XMLWriter::WriteLine(const std::string &) {}

JSONWriter::JSONWriter(const std::string &filename) {}

void JSONWriter::WriteLine(const std::string &) {}

std::shared_ptr<Writer> ChooseWriter(TypeFile type, const std::string& out_file_name) {
    switch (type) {
        case TypeFile::Text:
            return std::make_shared<TextWriter>(out_file_name);
        case TypeFile::XML:
            return std::make_shared<XMLWriter>(out_file_name);
        case TypeFile::JSON:
            return std::make_shared<JSONWriter>(out_file_name);
    }
}
