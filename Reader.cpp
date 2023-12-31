#include "Reader.h"

class TextReader : public Reader {
public:
    explicit TextReader(const std::string &filename);

    std::string ReadNextLine() override;

    bool IsEnd() override;
};

class XMLReader : public Reader {
public:
    explicit XMLReader(const std::string &filename);

    std::string ReadNextLine() override;

    bool IsEnd() override;
};

class JSONReader : public Reader {
public:
    explicit JSONReader(const std::string &filename);

    std::string ReadNextLine() override;

    bool IsEnd() override;
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

TextReader::TextReader(const std::string &filename) {}

std::string TextReader::ReadNextLine() {
    return "";
}

bool TextReader::IsEnd() {
    return true;
}

XMLReader::XMLReader(const std::string &filename) {}

std::string XMLReader::ReadNextLine() {
    return "";
}

bool XMLReader::IsEnd() {
    return true;
}

JSONReader::JSONReader(const std::string &filename) {}

std::string JSONReader::ReadNextLine() {
    return "";
}

bool JSONReader::IsEnd() {
    return true;
}