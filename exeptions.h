#ifndef THROUGH_EXEPTIONS_H
#define THROUGH_EXEPTIONS_H
#include <exception>
#include <iostream>
#include <locale>
#include <typeinfo>
class FileOpenError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class BadFileSyntaxError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class FileCreationError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class FileRenamingError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class FileRemovingError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

#endif //THROUGH_EXEPTIONS_H
