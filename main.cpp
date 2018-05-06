#include "fileWordCounter.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if(argc != 3) {
        std::cerr << "Argument(s) missing. To run program use './fileWordCounter [file] [topN]'\n";
        std::cerr << "where [file] is a file path and [topN] is a non-negative number.\n\n";
        return 1;
    }

    int n = std::stoi(argv[2], nullptr); // std::invalid_argument is thrown if argv[2] is not a number
    if(n < 0) {
        std::cerr << "[topN] argument must be a non-negative number.\n\n";
        return 1;
    }

    FileWordCounter fwc(argv[1]); // std::runtime_error is thrown if argv[1] is not a number
    fwc.printTopNWords(n);
    std::cout << "\nTotal Words Counted from File: " << fwc.totalWordsCounted() << std::endl;

    return 0;
}
