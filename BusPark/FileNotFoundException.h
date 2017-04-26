//
// Created by Eugenia Cheskidova on 26/04/2017.
//

#ifndef SEMINARWORKSHOP_FILENOTFOUNDEXCEPTION_H
#define SEMINARWORKSHOP_FILENOTFOUNDEXCEPTION_H


#include <exception>
#include <string>

class FileNotFoundException: public std::exception {
public:

    FileNotFoundException(const std::string &file_name);

    ~FileNotFoundException() override;

    const char *what() const noexcept override;

private:
    std::string file_name;
};


#endif //SEMINARWORKSHOP_FILENOTFOUNDEXCEPTION_H
