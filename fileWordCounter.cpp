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

FileWordCounter::FileWordCounter(std::string file) {
    std::ifstream ifs(file);
    if(!ifs.is_open()) { throw std::runtime_error("Unable to open file: " + file); }

    std::string token;  // May contain several words inside
    while(ifs >> token) {
        std::queue<std::string> que = splitWordToken(token);
        while(!que.empty()) {
            std::string word = cleanWord(que.front());
            que.pop();
            if(word.empty()) { continue; }
            addWord(word);
        }
    }
    words.sort(compare);
}

void FileWordCounter::addWord(std::string word) {
    FWCMap::iterator it = nodeMap.find(word);
    if(it != nodeMap.end()) {
        (it->second->second)++;
    } else {
        FWCPair newPair = std::make_pair(word, 1);
        words.push_back(newPair);
        nodeMap.insert({word, --words.end()});
    }
}

std::queue<std::string> FileWordCounter::splitWordToken(std::string token) {
    std::queue<std::string> que;
    std::string word;
    for(char c : token) {
        if(c == '_' || c == '/' || c == ':' || c == ';') {
            if(word.empty()) { continue; }
            que.push(word);
            word.clear();
        } else {
            word.push_back(c);
        }
    }
    if(!word.empty()) { que.push(word); }
    return que;
}

std::string FileWordCounter::cleanWord(std::string word) {
    std::string cleanedWord;
    for(char c : word) {
        if(c >= '0' && c <= '9') {
            cleanedWord.push_back(c);
        }
        else if(c >= 'a' && c <= 'z') {
            cleanedWord.push_back(c);
        }
        else if(c >= 'A' && c <= 'Z') {
            cleanedWord.push_back(c + ' ');
        }
        else if(c == '-') {
            cleanedWord.push_back(c);
        }
    }
    return cleanedWord;
}

std::vector<FWCPair> FileWordCounter::topNWords(unsigned int n) {
    std::vector<FWCPair> topN;
    FWCList::iterator it;
    unsigned int i = 0;
    unsigned int prevCount = 0;  // 0 count words are not stored in words list
    for(it = words.begin(); (it != words.end()) && (i < n); ++it) {
        if(prevCount != it->second) {
            prevCount = it->second;
            i++;
        };
        topN.push_back(*it);
    }
    return topN;
}

unsigned int FileWordCounter::totalWordsCounted(void) {
    return nodeMap.size();
}

unsigned int FileWordCounter::count(std::string word) {
    unsigned int count = 0;
    FWCMap::iterator node = nodeMap.find(word);
    if(node != nodeMap.end()) {
        count = node->second->second;
    }
    return count;
}

void FileWordCounter::printTopNWords(unsigned int n) {
    std::vector<FWCPair> topN = FileWordCounter::topNWords(n);
    for(FWCPair p : topN) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
}
