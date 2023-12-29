#ifndef THROUGH_FILEINFO_H
#define THROUGH_FILEINFO_H

#include <iostream>
#include <memory>
#include <vector>
#include "TypeFile.h"

struct FileProcessingStep {

};

struct FileInfo {
    std::string in_file_name;
    std::string out_file_name;
    TypeFile in_type;
    TypeFile out_type;
    std::vector<FileProcessingStep> pre_steps;
    std::vector<FileProcessingStep> post_steps;
};

#endif //THROUGH_FILEINFO_H
