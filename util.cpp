#include "util.hpp"
#include<vector>
#include<string>
#include<unordered_set>
#include<random>
#include<algorithm>
#include<fstream>
#include<iostream>
using namespace std;

std::mt19937 gen(std::random_device{}());

unordered_set<string> dict;

unordered_set<string> bigram = {
    "th", "he", "in", "er", "an", "re",
    "on", "at", "en", "nd", "ti", "to",
    "or", "it", "is", "as", "of", "be",
    "by", "so", "es", "ed", "le", "sa",
    "si", "ar", "ve", "ra", "al", "ta",
    "se", "li", "ou", "hi", "ne", "me",
    "de", "co", "ec", "ur", "ul","wa",
    "ss", "tt", "ll", "oo", "ff", "pp",
    "dd", "gg", "io", "ea", "ro", "nt",
    "ha", "ng", "us", "ho", "rs", "lo",
    "ma", "ic", "el", "ch", "tr", "ly",
    "ca", "ad", "il", "no", "po", "ut",
    "ri", "mo", "pe", "pa", "di", "mi",
    "fo", "wi", "sp", "la", "bo", "da",
    "sh", "pl", "gr", "ke"
};

unordered_set<string> trigram = {
    "the", "and", "ing", "her", "ere", "ent",
    "tha", "nth", "was", "eth", "for", "dth",
    "hat", "his", "tha", "ere", "ati", "ver",
    "ter", "res", "ont", "tio", "men", "ith",
    "all", "hes", "rea", "con", "wit", "are",
    "not", "but", "you", "one", "our", "out",
    "day", "had", "has", "who", "were", "can",
    "use", "how", "man", "new", "now", "old",
    "see", "two", "way", "may", "get", "say",
    "she", "did", "its", "let", "put", "end",
    "any", "try", "ask", "run", "set", "own",
    "off", "why", "few", "big", "far", "lot",
    "yet", "job", "law", "war", "pay", "car",
    "god", "air", "sea", "art", "red", "win",
    "bad", "hot", "box", "sun"
};

unordered_set<string> quadgram = {
    "that", "ther", "with", "tion", "here",
    "ould", "ight", "have", "hich", "whic",
    "this", "thin", "they", "atio", "ever",
    "from", "were", "ment", "when", "your",
    "them", "some", "into", "than", "each",
    "will", "over", "also", "more", "such",
    "only", "been", "most", "make", "time",
    "know", "take", "good", "work", "life",
    "back", "want", "need", "feel", "seem",
    "give", "find", "tell", "call", "help",
    "keep", "turn", "move", "play", "read",
    "walk", "talk", "live", "look", "brin",
    "star", "migh", "thin", "righ", "plac",
    "wher", "worl", "hous", "poin", "grea",
    "smal", "larg", "youn", "earl", "late",
    "ofte", "neve", "unde", "agai", "ever",
    "afte", "firs", "othe", "thin", "whil",
    "sinc", "unti", "abou", "arou", "beca",
    "duri", "with", "with", "thou"
};

bool loadDictionary()
{
    ifstream file("words_alpha.txt");
    if (!file) return false;

    string word;
    while (file >> word)
    dict.insert(word);
    file.close();
    return true;
}

string removeUnknown(string& mapping)
{
    string temp = mapping;

    for(int i=0;i<26;i++)
    {
        if(temp[i]=='?')
        temp[i] = 'x';
    }
    return temp;
}

string initialKeyGuess(unordered_map<char, int>& freq)
{
    string generalFreqDistribution = "etaonihsrdlumcwfygpbvkxjqz";
    vector<pair<int, char>> freq2;
    for(auto it: freq)
    {
        char ch = it.first;
        int count = it.second;
        freq2.push_back({count, ch});
    }
    sort(freq2.rbegin(), freq2.rend());
    string mapping(26, '?');
    for(int i=0;i < freq2.size() && i<26;i++)
    {
        mapping[generalFreqDistribution[i]-'a'] = freq2[i].second;
    }
    return mapping;
}

vector<string> decrypt(vector<string>& cipher, string& mapping)
{
    vector<string> plain;
    char mapArr[256]={0};
    for(int i = 0; i < 26; i++) {
        unsigned char cipherChar = mapping[i];
        mapArr[cipherChar] = 'a' + i;
    }
    string temp;
    for(string& str: cipher)
    {  
        temp.clear();
        for(char ch: str)
        {
            if(ch == '.' || ch == ',' || ch == ';' || ch == '!')
            {
                // temp += ch;
                continue;
            }
            else
            {
                if(mapArr[(unsigned char)ch] != 0)
                {
                    temp += mapArr[(unsigned char)ch];
                }
                else
                temp += '_';
            }
        }
        plain.push_back(temp);
    }
    return plain;
}
int mostFrequentWords(vector<string>& plain)
{
    int count = 0;
    unordered_set<string> commonWords = {"the", "and", "that", "have", "for", "not", "with", "you", "this", "but", "has", "who", "were", "am", "how", "are", "they", "his", "her", "its", "on", "in", "at", "to", "of", "is", "been", "being", "would", "one", "be", "it", "he", "she", "as", "do", "by", "from", "we", "or", "an", "will", "can", "could", "my", "all"};
    for(string& str: plain)
    {
        if(commonWords.count(str))
        count++;
    }
    return count*5;
}
bool hasVowel(string& str)
{
    for(char& ch: str)
    if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
    return true;
    return false;
}
int countNgrams(vector<string>& plain)
{
    int bi,tri,quad;
    bi=tri=quad = 0;
    int bad=0;
    int n = plain.size();
    int totalScore = 0;
    int unmapped=0;
    int noVowel = 0;
    for(string& str: plain)
    {
        if(!hasVowel(str))
        noVowel++;
        int n = str.size();
        for(int i=0;i<n-1;i++)
        {
            if(str[i] == '_')
            {
                unmapped++;
                continue;
            }
            string temp;
            temp += str[i];
            temp+=str[i+1];
            //bi
            if(bigram.count(temp))
            bi++;

            //tri
            if(i<=n-3)
            {
                temp+=str[i+2];
                if(trigram.count(temp))
                tri++;
            }

            //quad
            if(i<=n-4)
            {
                temp += str[i+3];
                if(quadgram.count(temp))
                quad++;
            }
        }
    }
    totalScore = quad*4 - noVowel*4 - unmapped*3;
    // totalScore =  -noVowel*4 - unmapped*3;  
    return totalScore;
}
pair<int, int> matching(vector<string>& plain)
{
    int total = plain.size();
    int matched = 0;
    int partiallyMatched = 0;
    int n = plain.size();
    unordered_set<string> matchedWords;
    string temp;
    for(int i=0;i<n;i++)
    {
        temp = plain[i];
        if(temp.back() == '.' || temp.back() == ',' || temp.back() == ';')
            temp.pop_back();
        if(dict.count(temp))
        {
            matched++;
            matchedWords.insert(temp);
        }
    }
    return {matched, matchedWords.size()};
}
int score(vector<string>& plain)
{
    int totalScore = 0;
    // totalScore += countNgrams(plain);
    totalScore += matching(plain).second;
    totalScore += mostFrequentWords(plain);

    return totalScore;
}
string mutateKey(string& key)
{
    string newKey = key;

    uniform_int_distribution<int> dist(0, 25);

    int choice = dist(gen);

    if(choice<=20)
    {
        int idx1 = dist(gen);
        while(key[idx1] == '?')
        idx1 = dist(gen);

        int idx2 = dist(gen);
        while(idx2 == idx1 || key[idx2] == 'x')
        {
            idx2 = dist(gen);
        }
        //swap
        swap(newKey[idx1], newKey[idx2]);
    }
    else
    {
        int idx = dist(gen)%5;
        shuffle(newKey.begin()+26-idx, newKey.end(), gen);
    }

    return newKey;
}

string randomKey(string& pass)
{
    string mapping = pass;
    uniform_int_distribution<int> dist(0, 22);
    int rand = dist(gen)%2;
    int temp;
    switch(rand)
    {
        case 3:
            shuffle(mapping.begin(), mapping.end(), gen);
            break;
        case 1:
            for(int i=0;i<10;i++)
            {
                mapping = mutateKey(mapping);
            }
            break;
        case 4:
            reverse(mapping.begin(), mapping.end());
            break;
        case 0:
            temp = dist(gen);
            rotate(mapping.begin()+temp, mapping.begin()+temp+3, mapping.end());
            break;
    }
    return mapping;
}

vector<string> genereteKeys(string& baseKey, int numKeys)
{
    vector<string> keys;
    for(int i=1;i<=numKeys;i++)
    {
        string newKey = mutateKey(baseKey);
        keys.push_back(newKey);
    }
    return keys;
}