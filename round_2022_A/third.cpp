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
#include <bitset>
#include <queue>
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
// Always make sure to read everything in before printing and returning a solution!!!!!
// In case of circular function references, declare an empty function at the top e.g. long func(long k);
// reassigning containers, e.g. vl vec2 = vec makes a copy.
// get iterator pointer via &(*iter)
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


bool is_pal(string v) {
    if (v.size() != 6) {
        print(v)
        throw 1;}
    bool pal = true;
    // Check 6 pals
    FOR(i,0,3) {
        if (v[i] != v[5-i]) pal = false;
    }
    if (pal) return true;
    pal = true;
    // Check 5 pals
    FOR(i,0,2) {
        if (v[i+1] != v[5-i]) return false;
    }
    return true;
}

long solve(long t){
    string s;
    long N;
    cin >> N;
    cin >> s;
    if (N < 5) {
        cout << "Case #" << t+1 << ": " << "POSSIBLE" << endl;
        return 0;
    }
    if (N < 6) {
        set<string> cur = {"0", "1"};
        FOR(i,0,N) {
            set<string> next;
            for (string x: cur) {
                if(s[i] == '?') {
                    next.insert(x+"0");
                    next.insert(x+"1");
                } else {
                    x.push_back(s[i]);
                    next.insert(x);
                }
            }
            cur = next;
        }
        for(string x: cur) if (!is_pal(x)) {
            cout << "Case #" << t+1 << ": " << "POSSIBLE" << endl;
            return 0;            
        }
        cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
        return 0;     
    }

    set<string> cur = {"0", "1"};
    set<string> next;
    FOR(i,0,5) {
        next.clear();
        for (string x: cur) {
            if(s[i] == '?') {
                next.insert(x+"0");
                next.insert(x+"1");
            } else {
                x.push_back(s[i]);
                next.insert(x);
            }
        }
        cur = next;
    }
    next.clear();
    for (string x: cur) if (!is_pal(x)) next.insert(x);
    cur = next;
    if (cur.size() == 0) {
        cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
        return 0;             
    }


    FOR(i,5,N) {
        next.clear();
        for (string x: cur) {
            if(s[i] == '?') {
                next.insert(x.substr(1,5)+"0");
                next.insert(x.substr(1,5)+"1");
            } else {
                x.push_back(s[i]);
                next.insert(x.substr(1,6));
            }
        }
        cur = next;
        next.clear();
        for (string x: cur) if (!is_pal(x)) next.insert(x);
        cur = next;
        if (cur.size() == 0) {
            cout << "Case #" << t+1 << ": " << "IMPOSSIBLE" << endl;
        return 0;             
        }
    }


    cout << "Case #" << t+1 << ": " << "POSSIBLE" << endl;
    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}