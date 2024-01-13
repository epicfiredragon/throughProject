#include "Reader.h"
#include <fstream>

class TextReader : public Reader {
    std::ifstream stream;
    bool ended;
public:
    explicit TextReader(const std::string &filename): stream(filename) {
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
public:
    explicit XMLReader(const std::string &filename) {

    }

    std::string ReadNextLine() override {

    }

    bool IsEnd() override {

    }
};

class JSONReader : public Reader {
public:
    explicit JSONReader(const std::string &filename) {

    }

    std::string ReadNextLine() override {

    }

    bool IsEnd() override {

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
