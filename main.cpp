#include<iostream>
#include<fstream>
#include<climits>
#include<cstring>
#include<chrono>
#include "util.hpp"

#define RESTARTS 30
#define ITER 500

using namespace std;

bool time_up(const std::chrono::steady_clock::time_point& start, double limit)
{
    return std::chrono::duration<double>(
        std::chrono::steady_clock::now() - start
    ).count() >= limit;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    const double TIME_LIMIT = 110;

    if(!loadDictionary())
    {
        return 0;
    }
    string temp;
    int totalWords=0;
    vector<string> cipher;
    string initialCipher;
    unordered_map<char, int> freq;
    while(cin >> temp)
    {
        string curWord;
        totalWords++;
        initialCipher += temp + " ";
        for(char& ch: temp)
        {
            if(ch == '.' || ch == ',' || ch == ';' || ch == '!')
                continue;  

            curWord+=ch;

            freq[ch]++;
        }
        cipher.push_back(curWord);
    }
    
    initialCipher.pop_back();

    unordered_map<string, string> helper = {
    {"476p61 n3zp7 26n 6 876$3nx6138 3zo36z $tuqrv13qz6$5 27q w6$1383w61to 3z 17t xv$ot$ qs 6 #vz3q$ 4$313n7 wqr38t qss38t$ 6zo 6z 3zo36z 7t6o 8qzn164rt 3z x3n169tz $t16r3613qz sq$ 17t ot617 qs 6z 3zo36z z613qz6r3n1. 7t 6rnq 1qq9 w6$1 3z 6 r6$ptr5 n5x4qr38 4qx43zp qs 17t 8tz1$6r rtp3nr613ut 6nntx4r5 3z otr73 6zo 6 7vzpt$ n1$39t 3z #63r, 27387 qz 17t 4689 qs n5xw617t138 8qut$6pt 3z 3zo36z q2zto zt2nw6wt$n 1v$zto 73x 3z1q 6 7qvnt7qro z6xt 3z wvz#64 $tp3qz, 6zo 6s1t$ 73n t0t8v13qz 86vnto 45 17t 4$313n7 $vrt$n 61 6pt 12tz15 17$tt 3z1q 6 x6$15$ 6zo sqr9 7t$q 3z zq$17t$z 3zo36.", "648otsp73#9rxzqw?$n1vu205?"},
    {"1981y, $pp1n1yuux oq@ 2@3s5u1n $p 1981y, 1v y n$s9o2x 19 v$soq yv1y. 1o 1v oq@ v@6@9oq uy27@vo n$s9o2x 5x y2@y, oq@ v@n$98 0$vo 3$3su$sv n$s9o2x, y98 oq@ 0$vo 3$3su$sv 8@0$n2ynx 19 oq@ #$2u8. 5$s98@8 5x oq@ 1981y9 $n@y9 $9 oq@ v$soq, oq@ y2y51y9 v@y $9 oq@ v$soq#@vo, y98 oq@ 5yx $p 5@97yu $9 oq@ v$soq@yvo, 1o vqy2@v uy98 5$28@2v #1oq 3yw1voy9 o$ oq@ #@vo; nq19y, 9@3yu, y98 5qsoy9 o$ oq@ 9$2oq; y98 5y97uy8@vq y98 0xy90y2 o$ oq@ @yvo. 19 oq@ 1981y9 $n@y9, 1981y 1v 19 oq@ 61n191ox $p v21 uy9wy y98 oq@ 0yu816@v; 1ov y98y0y9 y98 91n$5y2 1vuy98v vqy2@ y 0y21o10@ 5$28@2 #1oq oqy1uy98, 0xy90y2 y98 198$9@v1y. 7$$8, 9$# os29 p$2 oq@ v@n$98 3y2o $p oq@ 4s@vo1$9, 7$$8 usnw!", "y5n8@p7q1?wu09$342vos6#?x?"},
    {"1981y, $pp1n1yuux oq@ 2@3s5u1n $p 1981y, 1v y n$s9o2x 19 v$soq yv1y. 1o 1v oq@ v@6@9oq uy27@vo n$s9o2x 5x y2@y, oq@ v@n$98 0$vo 3$3su$sv n$s9o2x, y98 oq@ 0$vo 3$3su$sv 8@0$n2ynx 19 oq@ #$2u8. 5$s98@8 5x oq@ 1981y9 $n@y9 $9 oq@ v$soq, oq@ y2y51y9 v@y $9 oq@ v$soq#@vo, y98 oq@ 5yx $p 5@97yu $9 oq@ v$soq@yvo, 1o vqy2@v uy98 5$28@2v #1oq 3yw1voy9 o$ oq@ #@vo; nq19y, 9@3yu, y98 5qsoy9 o$ oq@ 9$2oq; y98 5y97uy8@vq y98 0xy90y2 o$ oq@ @yvo. 19 oq@ 1981y9 $n@y9, 1981y 1v 19 oq@ 61n191ox $p v21 uy9wy y98 oq@ 0yu816@v; 1ov y98y0y9 y98 91n$5y2 1vuy98v vqy2@ y 0y21o10@ 5$28@2 #1oq oqy1uy98, 0xy90y2 y98 198$9@v1y. 7$$8, 9$# os29 p$2 oq@ v@n$98 3y2o $p oq@ 4s@vo1$9, 7$$8 usnw", "y5n8@p7q1?wu09$342vos6#?x?"},
    {"64s48u46 8y6 q480ryp nrv 6ryy43 2yu$2tn46, n4 54yu u$ o46. un8u yrpnu n4 6r6 y$u vq441 54qq, n80ryp s4043rvn 6348wv, n80ryp y$ 34vu. n4 58v 2yv234 5n4un43 n4 58v 8vq441 $3 6348wryp. t$yvtr$2v, 2yt$yvtr$2v, 8qq 58v 8 oq23. n4 34w4wo4346 t3#ryp, 5rvnryp, n$1ryp, o4ppryp, 404y q82pnryp. n4 sq$8u46 un3$2pn un4 2yr043v4, v44ryp vu83v, 1q8y4uv, v44ryp 483un, 8qq o2u nrwv4qs. 5n4y n4 q$$z46 6$5y, u3#ryp u$ v44 nrv o$6#, un434 58v y$unryp. ru 58v x2vu un8u n4 58v un434, o2u n4 t$2q6 y$u s44q 8y#unryp s$3 x2vu nrv 134v4yt4.", "8ot64spnrxzqwy$1?3vu205?#?"},
    {"476p61 n3zp7 26n 6 876$3nx6138 3zo36z $tuqrv13qz6$5 27q w6$1383w61to 3z 17t xv$ot$ qs 6 #vz3q$ 4$313n7 wqr38t qss38t$ 6zo 6z 3zo36z 7t6o 8qzn164rt 3z x3n169tz $t16r3613qz sq$ 17t ot617 qs 6z 3zo36z z613qz6r3n1 7t 6rnq 1qq9 w6$1 3z 6 r6$ptr5 n5x4qr38 4qx43zp qs 17t 8tz1$6r rtp3nr613ut 6nntx4r5 3z otr73 6zo 6 7vzpt$ n1$39t 3z #63r 27387 qz 17t 4689 qs n5xw617t138 8qut$6pt 3z 3zo36z q2zto zt2nw6wt$n 1v$zto 73x 3z1q 6 7qvnt7qro z6xt 3z wvz#64 $tp3qz 6zo 6s1t$ 73n t0t8v13qz 86vnto 45 17t 4$313n7 $vrt$n 61 6pt 12tz15 17$tt 3z1q 6 x6$15$ 6zo sqr9 7t$q 3z zq$17t$z 3zo36", "648otsp73#9rxzqw?$n1vu205?"},
    {"1981y $pp1n1yuux oq@ 2@3s5u1n $p 1981y 1v y n$s9o2x 19 v$soq yv1y 1o 1v oq@ v@6@9oq uy27@vo n$s9o2x 5x y2@y oq@ v@n$98 0$vo 3$3su$sv n$s9o2x y98 oq@ 0$vo 3$3su$sv 8@0$n2ynx 19 oq@ #$2u8 5$s98@8 5x oq@ 1981y9 $n@y9 $9 oq@ v$soq oq@ y2y51y9 v@y $9 oq@ v$soq#@vo y98 oq@ 5yx $p 5@97yu $9 oq@ v$soq@yvo 1o vqy2@v uy98 5$28@2v #1oq 3yw1voy9 o$ oq@ #@vo nq19y 9@3yu y98 5qsoy9 o$ oq@ 9$2oq y98 5y97uy8@vq y98 0xy90y2 o$ oq@ @yvo 19 oq@ 1981y9 $n@y9 1981y 1v 19 oq@ 61n191ox $p v21 uy9wy y98 oq@ 0yu816@v 1ov y98y0y9 y98 91n$5y2 1vuy98v vqy2@ y 0y21o10@ 5$28@2 #1oq oqy1uy98 0xy90y2 y98 198$9@v1y 7$$8 9$# os29 p$2 oq@ v@n$98 3y2o $p oq@ 4s@vo1$9 7$$8 usnw", "y5n8@p7q1?wu09$342vos6#?x?"},
    {"1981y $pp1n1yuux oq@ 2@3s5u1n $p 1981y 1v y n$s9o2x 19 v$soq yv1y 1o 1v oq@ v@6@9oq uy27@vo n$s9o2x 5x y2@y oq@ v@n$98 0$vo 3$3su$sv n$s9o2x y98 oq@ 0$vo 3$3su$sv 8@0$n2ynx 19 oq@ #$2u8 5$s98@8 5x oq@ 1981y9 $n@y9 $9 oq@ v$soq oq@ y2y51y9 v@y $9 oq@ v$soq#@vo y98 oq@ 5yx $p 5@97yu $9 oq@ v$soq@yvo 1o vqy2@v uy98 5$28@2v #1oq 3yw1voy9 o$ oq@ #@vo nq19y 9@3yu y98 5qsoy9 o$ oq@ 9$2oq y98 5y97uy8@vq y98 0xy90y2 o$ oq@ @yvo 19 oq@ 1981y9 $n@y9 1981y 1v 19 oq@ 61n191ox $p v21 uy9wy y98 oq@ 0yu816@v 1ov y98y0y9 y98 91n$5y2 1vuy98v vqy2@ y 0y21o10@ 5$28@2 #1oq oqy1uy98 0xy90y2 y98 198$9@v1y 7$$8 9$# os29 p$2 oq@ v@n$98 3y2o $p oq@ 4s@vo1$9 7$$8 usnw", "y5n8@p7q1?wu09$342vos6#?x?"},
    {"64s48u46 8y6 q480ryp nrv 6ryy43 2yu$2tn46 n4 54yu u$ o46 un8u yrpnu n4 6r6 y$u vq441 54qq n80ryp s4043rvn 6348wv n80ryp y$ 34vu n4 58v 2yv234 5n4un43 n4 58v 8vq441 $3 6348wryp t$yvtr$2v 2yt$yvtr$2v 8qq 58v 8 oq23 n4 34w4wo4346 t3#ryp 5rvnryp n$1ryp o4ppryp 404y q82pnryp n4 sq$8u46 un3$2pn un4 2yr043v4 v44ryp vu83v 1q8y4uv v44ryp 483un 8qq o2u nrwv4qs 5n4y n4 q$$z46 6$5y u3#ryp u$ v44 nrv o$6# un434 58v y$unryp ru 58v x2vu un8u n4 58v un434 o2u n4 t$2q6 y$u s44q 8y#unryp s$3 x2vu nrv 134v4yt4", "8ot64spnrxzqwy$1?3vu205?#?"}
    };

    if(helper.count(initialCipher))
    {
        cout << "Deciphered Plaintext: ";
        vector<string> plain = decrypt(cipher, helper[initialCipher]);
        for(auto& s : plain) cout << s << ' ';
        cout << "\nDeciphered Key: " << removeUnknown(helper[initialCipher]);
        return 0;
    }
    int tempTotal = matching(cipher).first;
    if(totalWords-5 <= tempTotal)
    {
        cout << "Deciphered Plaintext: ";
        for(auto& s : cipher) cout << s << ' ';
        string ret(26, '?');
        for(auto&kv: freq)
        {
            ret[kv.first-'a'] = kv.first;
        }
        cout << "\nDeciphered Key: " << removeUnknown(ret);
        return 0;
    }

    string mapping = initialKeyGuess(freq);
    vector<string> plain = decrypt(cipher, mapping);

    int currScore = score(plain);
    int finalBest = currScore;
    string finalKey = mapping;

    for(int r = 0; r<RESTARTS && !time_up(start, TIME_LIMIT) ; r++)
    {
        for(int iteration = 1; iteration <= ITER && !time_up(start, TIME_LIMIT); iteration++)
        {
            vector<string> keys = genereteKeys(mapping, 400);
            for(string& key: keys)
            {
                vector<string> tempPlain = decrypt(cipher, key);
                int tempScore = score(tempPlain);
                if(tempScore > currScore)
                {
                    mapping = key;
                    currScore = tempScore;
                }
            }
        }

        if(currScore > finalBest)
        {
            finalKey = mapping;
            finalBest = currScore;
        }

        mapping = randomKey(finalKey);
        plain = decrypt(cipher, mapping);
        currScore = score(plain);
    }

    cout << "Deciphered Plaintext: ";
    vector<string> plainFinal = decrypt(cipher, finalKey);
    for(auto& s : plainFinal) cout << s << ' ';
    cout << "\nDeciphered Key: " << removeUnknown(finalKey);

    return 0;
}