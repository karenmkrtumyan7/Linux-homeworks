#include "colorprint.hpp"
#include <iostream>

Painter::Painter(std::ostream &stream,
                 const std::vector<std::string> &successPatterns,
                 const std::vector<std::string> &failPatterns)
        : stream(stream), successPatterns(successPatterns), failPatterns(failPatterns) {}

void Painter::printColoredLine(const std::string &line) {

    bool isPrevDigit = false;
    std::string replacedDigits;
    for (char c: line) {
        if (isdigit(c) and not isPrevDigit) {
            replacedDigits += "\033[33m";
        }
        if (not isdigit(c) and isPrevDigit) {
            replacedDigits += "\033[0m";
        }
        replacedDigits += c;
        isPrevDigit = isdigit(c);
    }
    if (isPrevDigit) {
        replacedDigits += "\033[0m";
    }

    std::string outputLine = replacedDigits;

    for (const std::string &pattern: successPatterns) {
        size_t index = 0;
        while (true) {
            index = outputLine.find(pattern, index);
            if (index == std::string::npos) break;
            std::string replacement = "\033[32m" + pattern + "\033[0m";
            outputLine.replace(index, pattern.length(), replacement);
            index += replacement.length();
        }
    }
    for (const std::string &pattern: failPatterns) {
        size_t index = 0;
        while (true) {
            index = outputLine.find(pattern, index);
            if (index == std::string::npos) break;
            std::string replacement = "\033[31m" + pattern + "\033[0m";
            outputLine.replace(index, pattern.length(), replacement);
            index += replacement.length();
        }
    }
    stream << outputLine << std::endl;
}


std::vector<std::string> Painter::defaultSuccessPatterns() {
    return std::vector<std::string>({"OK", "SUCCESS"});
}

std::vector<std::string> Painter::defaultFailPatterns() {
    return std::vector<std::string>({"FAIL", "ERROR"});
}
