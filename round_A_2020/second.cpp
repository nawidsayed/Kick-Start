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


long solve(long t){
    long N,K,P;
    cin >> N;
    cin >> K;
    cin >> P;

    ml plates(N, vl(K));

    long b;

    FOR(n,0,N){
        long cur = 0;
        FOR(k,0,K){
            cin >> b;
            cur += b;
            plates[n][k] = cur;
        }
    }    

    long max_plates = N*K;

    vl valueForPlates(max_plates+1, 0);
    vl valueForPlatesNext(valueForPlates.size());


    for(vl stack: plates){

        FOR(i,0,valueForPlatesNext.size()){
            valueForPlatesNext[i] = valueForPlates[i];
        }
        
        FOR(p, 0, max_plates+1){
            long best = valueForPlatesNext[p];
            long bound = min(p,K);
            FOR(i,0,bound){
                long value = stack[i];
                long num = i+1;   
                best = max(valueForPlates[p-num]+value, best);
            }
            valueForPlatesNext[p] = best;
        }

        FOR(i,0,valueForPlatesNext.size()){
            valueForPlates[i] = valueForPlatesNext[i];
        }
    }



    cout << "Case #" << t+1 << ": " << valueForPlates[P] << endl;
    return 0;
}

int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}