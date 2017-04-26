//
// Created by Eugenia Cheskidova on 26/04/2017.
//

#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(const std::string &file_name) : file_name(file_name) {}

FileNotFoundException::~FileNotFoundException() {

}

const char *FileNotFoundException::what() const noexcept {
    return (std::string("File ") + file_name +  std::string(" not found")).c_str();
}
