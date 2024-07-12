#include "fileWordCounter.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if(argc != 3) {
        std::cerr << "Argument(s) missing. To run program use './fileWordCounter [fileName] [topN]'\n";
        std::cerr << "where [fileName] is a file path and [topN] is a non-negative number.\n\n";
        return 1;
    }

    int n = std::stoi(argv[2], nullptr);
    if(n < 0) {
        std::cerr << "[topN] argument must be a non-negative number.\n\n";
    }

    FileWordCounter fwc(argv[1]);
    fwc.printTopNWords(n);
    std::cout << "\nTotal Words Counted from File: " << fwc.totalWordsCounted() << std::endl;

    return 0;
}
