#ifndef FILE_WORD_COUNTER_H
#define FILE_WORD_COUNTER_H

#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include <queue>

typedef std::pair<std::string, unsigned int> FWCPair;
typedef std::list<FWCPair> FWCList;
typedef std::unordered_map<std::string, FWCList::iterator> FWCMap;

class FileWordCounter {
public:
    FileWordCounter(const std::string& file);
    ~FileWordCounter(void);
    unsigned int count(const std::string& word);
    unsigned int totalWordsCounted(void);
    std::vector<FWCPair> topNWords(const unsigned int n);
    void printTopNWords(const unsigned int n);
    std::string getFilePath(void);

private:
    FWCList words; // sorted by count in descending order after object construction
    FWCMap nodeMap;  // acts as a fact lookup to nodes in 'words' list
    std::string file;  // file path

    std::string cleanWord(const std::string& word);
    std::queue<std::string> splitWordToken(const std::string& token);
    void addWord(const std::string& word);
};

#endif /* FILE_WORD_COUNTER_H */
