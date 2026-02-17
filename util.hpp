#ifndef UTIL_HPP
#define UTIL_HPP

#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

int score(vector<string>& plain);
int countNgrams(vector<string>& plain);
string initialKeyGuess(unordered_map<char, int>& freq);
string mutateKey(string& key);
vector<string> decrypt(vector<string>& cipher, string& mapping);
pair<int, int> matching(vector<string>& plain);
bool loadDictionary();
string randomKey(string& pass);
vector<string> genereteKeys(string& baseKey, int numKeys);
string removeUnknown(string& mapping);


#endif