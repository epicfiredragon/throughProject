#include "Reader.h"
#include <fstream>
#include <Poco/JSON/Parser.h>
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/Node.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/SAX/InputSource.h"

class TextReader : public Reader {
    std::istream &stream;

    bool ended;

public:
    explicit TextReader(std::istream &istream) : stream(istream) {
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
    std::vector<std::string> array;

    size_t num_of_processed = 0;

public:
    explicit XMLReader(std::istream &istream) {
        Poco::XML::DOMParser parser;
        Poco::XML::InputSource src(istream);
        auto xmlDocument = parser.parse(&src);
        auto node = xmlDocument->getNodeByPath("/xml");
        std::string str = Poco::XML::fromXMLString(node->innerText());
        std::stringstream stringstream(str);
        std::string segment;
        while (std::getline(stringstream, segment)) {
            if (!segment.empty()) {
                array.push_back(segment);
            }
        }
    }

    std::string ReadNextLine() override {
        return array[num_of_processed++];
    }

    bool IsEnd() override {
        return array.size() == num_of_processed;
    }
};

class JSONReader : public Reader {
    Poco::JSON::Array::Ptr array;

    size_t num_of_processed;

public:
    explicit JSONReader(std::istream &istream) {
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(istream);
        array = result.extract<Poco::JSON::Array::Ptr>();
        num_of_processed = 0;
    }

    std::string ReadNextLine() override {
        return array->getElement<std::string>(num_of_processed++);
    }

    bool IsEnd() override {
        return array->size() == num_of_processed;
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
