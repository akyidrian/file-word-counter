#ifndef FILE_WORD_COUNTER_H
#define FILE_WORD_COUNTER_H

#include <unordered_map>
#include <list>
#include <string>
#include <vector>

typedef std::pair<std::string, unsigned int> FWCPair;
typedef std::list<FWCPair> FWCList;
typedef std::unordered_map<std::string, FWCList::iterator> FWCMap;

class FileWordCounter {
public:
    FileWordCounter(std::string file);
    ~FileWordCounter();
    unsigned int count(std::string word);
    unsigned int totalWordsCounted();
    std::vector<FWCPair> topNWords(unsigned int n);
    void printTopNWords(unsigned int n);

private:
    FWCList words;
    FWCMap nodeMap; 
    std::string file; 
};

#endif /* FILE_WORD_COUNTER_H */
