#pragma GCC optimize ("O3")

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <unordered_map>
#include <numeric>
using namespace std;

#define FOR(i,a,b) for (long i = (a); i < (b); i++)
#define FORR(i,a,b) for (long i = (b)-1; i >= (a); i--)
#define all(x) (x).begin(), (x).end()

#define MAX(cont) *max_element(all((cont))) 
#define MIN(cont) *min_element(all((cont))) 
#define ARGMAX(cont) max_element(all((cont))) - (cont).begin()
#define ARGMIN(cont) min_element(all((cont))) - (cont).begin()

#define MAXLONG 9223372036854775807L
#define MINLONG -9223372036854775808L

typedef pair<long, long> pll;
typedef vector<long> vl;
typedef vector<vector<long>> ml;

template<typename T> 
using matrix = vector<vector<T>>;

template<class Container>
void printc(const Container &cont){
    for (auto e: cont) cout << e << " "; cout << endl;
}

template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH> void _dbg(const char *sdbg, const vector<TH> &vec){ 
    cerr<<sdbg<<'=';
    for (TH e: vec) cerr << e << " "; cerr << endl; 
}
template<class TH> void _dbg(const char *sdbg, const vector<vector<TH>> &mat){ 
    cerr<<sdbg<<'='<< endl;
    for(vector<TH> vec: mat){for(TH e: vec) cerr << e << " "; cerr << endl;}
}
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
    while(*sdbg!=',')cerr<<*sdbg++;
    cerr<<'='<<h<<','<<' '; _dbg(sdbg+1, a...);
}
#define print(...) _dbg(#__VA_ARGS__, __VA_ARGS__);

// Things to be aware of:
// use g++sane for debugging, it catches array out of bound shenanigans
// you can do an ultimate return with a try / catch block 
// map is always ordered according to key
// always assume the worst :D use MAX and MIN for boundaries of long
// long a = 1; max(0,a); fails as max is on long and int
// for interactove problems write a function "query", which sends and reads at the same time
// Usually copies are inserted into containers or functions, pass by reference if needed
// Erasing in a container by iterator causes errors in g++6.3 e.g. list.erase(iter), use iter++ and account for increment 
// Be aware of functions with mod returning negative remainders
// print(...) macro can slow down the program


map<long, set<long*>> scorePointers;
map<long*, long> pointerScore;

pair<long, long*> popBestScorePointer(){
    long bestScore = (*prev(scorePointers.end())).first;
    set<long*>* pointers = &(*prev(scorePointers.end())).second;
    long* pointer = *(*pointers).begin();
    (*pointers).erase((*pointers).begin());
    return make_pair(bestScore, pointer);
}

long prefixAgreement(string s1, string s2){
    long minSize = min(s1.size(), s2.size());
    FOR(i,0,minSize){
        if (s1[i] != s2[i]) return i;
    }
    return minSize;
}

long solve(long t){
    scorePointers.clear();
    pointerScore.clear();

    long N,K;
    cin >> N;
    cin >> K;
    list<string> words;
    string word;
    FOR(i,0,N){
        cin >> word;
        words.push_back(word);
    }
    words.sort();

    auto itStart = words.begin();
    auto itEnd = words.begin();

    FOR(k,0,K-1){
        itEnd++;
    }

    list<long> scores;

    string wordStart, wordEnd;
    while(itEnd != words.end()){
        wordStart = *itStart;
        wordEnd = *itEnd;

        long score = prefixAgreement(wordStart, wordEnd);
        scores.push_back(score);

        scorePointers[score].insert(&score);
        pointerScore.insert({&score, score});

        itStart++;
        itEnd++;
    }
    FOR(i,0,N-K+1){
        auto res = popBestScorePointer();
        print(res.first)    
    }
    









    cout << "Case #" << t+1 << ": " << -1 << endl;
    return 0;
}

int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}