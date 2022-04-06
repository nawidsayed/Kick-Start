#pragma GCC optimize ("O3")

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <list>
#include <set>
#include <unordered_set>
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

long solve(long t){
    long N;
    string s;
    cin >> N >> s;
    list<long> l;   
    for(char c: s) l.push_back(c-'0');
    vector<list<list<long>::iterator>> v(10);
    auto it = l.begin();
    long prev, cur;
    prev = 100;
    while(it != l.end()) {
        cur = *it;
        if (prev +1 == cur || (prev == 9 && cur == 0)) v[prev].push_back(it);
        prev = cur;
        it++;
    }

    // FOR(i,0,10) {
    //     print(i)
    //     for (auto aaa: v[i]) print(&*aaa, *aaa)
    // }
    

    long i = 9;
    long changed = 0;
    while(changed < 12) {
        changed ++;
        i = (i+1) % 10;
        // print(i)
        // print("inset")
        // for (auto aaa: v[i]) print(&*aaa, *aaa)
        // printc(l);
        

        auto it2 = l.begin();
        // print("actually")
        // while(it2 != l.end()) {print(&*it2, *it2) it2++;}

        for(list<long>::iterator it: v[i]) {
            // print("here1", it == l.begin(), it==--l.end(), &*it, *it)
            // print(*--it) ++it;
            cur = *it;
            prev = *--it; ++it;
            

            

            if (prev == i && cur ==((i+1)%10)) {
                changed = 0;
                l.erase(it--);
                *it = (cur+1) % 10;
                cur = *it;
                if (it == l.begin()) prev = 100; else {prev = *--it; ++it;}
                if (prev +1 == cur || (prev == 9 && cur == 0)) v[prev].push_back(it);
                if (it != --l.end()) {
                    prev = *it;
                    cur = *++it;
                    if (prev +1 == cur || (prev == 9 && cur == 0)) v[prev].push_back(it);
                }
            }
        }
        v[i].clear();
    }
    




    s.clear();
    for (long c: l) s += to_string(c);

    cout << "Case #" << t+1 << ": " << s << endl;
    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}