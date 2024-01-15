#ifndef THROUGH_FILEINFO_H
#define THROUGH_FILEINFO_H

#include <vector>
#include <string>
#include "TypeFile.h"
#include "FileProcessor.h"

struct FileInfo {
    std::string in_file_name;
    std::string out_file_name;
    TypeFile in_type;
    TypeFile out_type;
    std::vector<FileProcessingStep> pre_steps;
    std::vector<FileProcessingStep> post_steps;
};

#endif //THROUGH_FILEINFO_H
