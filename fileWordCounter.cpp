#include "fileWordCounter.hpp"
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>

bool compare(const FWCPair p1, const FWCPair p2) {
    if(p1.second < p2.second) { return false; }
    else if (p1.second > p2.second) { return true; }
    else { /* p1.second == p2.second */
        return p1.first.compare(p2.first) < 0;
    }
}

FileWordCounter::~FileWordCounter(void) {
}

FileWordCounter::FileWordCounter(const std::string file) {
    std::ifstream ifs(file);
    if(!ifs.is_open()) { throw std::runtime_error("Unable to open file: \'" + file + "\'"); }

    std::string token;  // may contain several words inside
    while(ifs >> token) {
        std::queue<std::string> foundWords = splitWordToken(token);
        while(!foundWords.empty()) {
            std::string word = cleanWord(foundWords.front());
            foundWords.pop();
            if(word.empty()) { continue; } // ignore empty words
            addWord(word);
        }
    }
    words.sort(compare);
}

void FileWordCounter::addWord(const std::string word) {
    FWCMap::iterator it = nodeMap.find(word);
    if(it != nodeMap.end()) {
        (it->second->second)++;
    } else {
        FWCPair newPair = std::make_pair(word, 1);
        words.push_back(newPair);
        nodeMap.insert({word, --words.end()});
    }
}

std::queue<std::string> FileWordCounter::splitWordToken(const std::string token) {
    std::queue<std::string> foundWords;
    std::string newWord;
    for(const char& c : token) {
        if(c == '_' || c == '/' || c == ':' || c == ';') {
            if(newWord.empty()) { continue; } // ignore lone-some punctuation
            foundWords.push(newWord);
            newWord.clear();
        } else {
            newWord.push_back(c);
        }
    }
    if(!newWord.empty()) { foundWords.push(newWord); }  // in case we haven't added the last newWord
    return foundWords;
}

std::string FileWordCounter::cleanWord(const std::string word) {
    std::string cleanedWord;
    for(const char& c : word) {
        if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c == '-')) {
            cleanedWord.push_back(c);
        }
        else if(c >= 'A' && c <= 'Z') {
            cleanedWord.push_back(c + ' ');  // make lowercase (ascii arithmetic)
        }
    }
    return cleanedWord;
}

unsigned int FileWordCounter::totalWordsCounted(void) {
    return nodeMap.size();
}

unsigned int FileWordCounter::count(const std::string word) {
    unsigned int count = 0;
    FWCMap::iterator node = nodeMap.find(word);
    if(node != nodeMap.end()) {
        count = node->second->second;
    }
    return count;
}

std::vector<FWCPair> FileWordCounter::topNWords(const unsigned int n) {
    std::vector<FWCPair> topN;
    FWCList::iterator it;
    unsigned int i = 0; // topN.size() may be greater than n as some words may have the same rank
    unsigned int prevCount = 0; // this default is fine because 0 count words are not stored
    for(it = words.begin(); (it != words.end()) && (i < n); ++it) {
        if(prevCount != it->second) {
            prevCount = it->second;
            i++;
        };
        topN.push_back(*it);
    }
    return topN;
}

void FileWordCounter::printTopNWords(const unsigned int n) {
    std::vector<FWCPair> topN = FileWordCounter::topNWords(n);
    for(FWCPair p : topN) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
}
