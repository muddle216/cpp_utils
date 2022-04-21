//
// Created by LC on 2021/12/3.
//

#include "macro_util.h"
#include <string>
#include <sstream>

#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b, 3)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b, 3, d)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b, 3, d, 5)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b, 3, d, 5, e)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b, 3, d, 5, e, 7)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b, 3, d, 5, e, 7, 8)))
#pragma message(MACRO_PRINT(MACRO_ARGS_NUM(1, b, 3, d, 5, e, 7, 8, 9)))

std::string MacroTest() {
    std::stringstream ss;
    ss << MACRO_STREAM(MACRO_ARGS_NUM(1))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b, 3))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b, 3, d))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b, 3, d, 5))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b, 3, d, 5, e))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b, 3, d, 5, e, 7))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b, 3, d, 5, e, 7, 8))
       << MACRO_STREAM(MACRO_ARGS_NUM(1, b, 3, d, 5, e, 7, 8, 9));
    return ss.str();
}