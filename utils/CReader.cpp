//
// Created by chengli on 18-5-16.
//
#include "utils/CReader.h"

char* CReader::textFileRead(char *chFileName) {
    if (chFileName != nullptr) {
        _fp = fopen(chFileName, "rt");
        if (_fp != nullptr) {
            fseek(_fp, 0, SEEK_END);
            _count = ftell(_fp);
            rewind(_fp);
            if (_count > 0) {
                _content = (char *) malloc(sizeof(char) * (_count + 1));
                _count = fread(_content, sizeof(char), _count, _fp);
                _content[_count] = '\0';
            }
            fclose(_fp);
        }
    }
    return _content;
}


void CReader::init() {
    _content = nullptr;
    _count = 0;
}
