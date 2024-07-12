# A Simple ASCII File Word Counter
## Instructions
1. In terminal 'cd' to the project directory and run 'make' to build the 'fileWordCounter' and 'test' programs.
2. To use 'fileWordCounter', use './fileWordCounter [file] [topN]' where [file] is a file path and [topN] is a non-negative number. For example, './fileWordCounter testFile.txt 10' will return the top 10 most frequent words in descending order from 'testFile.txt'.
3. To run the [Catch](https://github.com/catchorg/Catch2) tests, use './test'. Or, use './test -h' for more options.

# Assumptions/Concerns
1. ASCII characters only.
2. Anything that isn't a-z, A-Z, 0-9 or '-' is ignored. The dash character '-' is assumed to make single words (e.g. solar-powered) so it is not ignored.
3. A-Z characters are converted to lowercase (a-z) to help with the proper counting of words.
4. There may be issues with contractions. This is because ''' is ignored. For example, "she'll" and "shell" will be counted as the same.
5. Some punctuation is used to help split word tokens (conjoined words without proper spacing). These are '\_', '/', ':' and ';'.
6. Different words with the same count are considered to have the same rank. This means in a top N printout it is possible to have greater than N words displayed.
7. There is sufficient program memory to load all words from a typical file.
