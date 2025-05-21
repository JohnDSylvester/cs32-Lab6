// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int count = 0;
	for(size_t i = 0; i < CAPACITY;  i++){
                for(auto it = table[i].begin(); it != table[i].end(); ++it){
                        count += it->second;
                }
        }
        return count;
}

int WordCount::getNumUniqueWords() const {
	int count = 0;
	for(size_t i = 0; i < CAPACITY;  i++){
		for(auto it = table[i].begin(); it != table[i].end(); ++it){
			count++;
		}
	}
	return count;
}

int WordCount::getWordCount(std::string word) const {
	std::string str = makeValidWord(word);
	if(str == ""){
                return 0;
        }
        size_t key = hash(str);
        for(auto i = table[key].begin(); i != table[key].end(); ++i){
                if(i->first == str){
                        return i->second;
                }
        }
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	std::string str = makeValidWord(word);
	if(str == ""){
                return 0;
        }
	size_t key = hash(str);
	for(auto i = table[key].begin(); i != table[key].end(); ++i){
		if(i->first == str){
			(i->second)++;
			return i->second;
		}
	}	
	std::pair<std::string, int> p = std::make_pair(str, 1);
	table[key].push_back(p);
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	std::string str = makeValidWord(word);
	if(str == ""){
		return 0;
	}
        size_t key = hash(str);
        for(auto i = table[key].begin(); i != table[key].end(); ++i){
                if(i->first == str){
                        if(i->second > 1){
                        	i->second--;
				return i->second;
			}
			else{
				table[key].erase(i);
				return 0;
			}
                }
        }
        return -1;
}

bool WordCount::isWordChar(char c) {
	if(isalpha(c)){
		return true;
	}
	return false;
}

std::string WordCount::makeValidWord(std::string word) {
	std::string str = word;
	for(size_t i = 0; i < str.size(); i++){
		if(isWordChar(str[i]) || ((i >= 1 && i < str.size()-1) && (str[i] == '\'' || str[i] == '-') && isWordChar(str[i-1]) && isWordChar(str[i+1]))){
			if(isupper(str[i])){
				str[i] = tolower(str[i]);
			}
		}
		else{
			str.erase(str.begin() + i);
			i--;
		}
	}
	return str;
}
