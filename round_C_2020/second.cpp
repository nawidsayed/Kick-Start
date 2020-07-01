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


long solve(long t){
    long R,C;
    cin >> R >> C;
    ml mat(R, vl(C));
    map<long, vector<pll>> blocks;

    long id;
    char ch;
    FOR(r,0,R){
        FOR(c,0,C){
            cin >> ch;
            id = ch - 'A';
            mat[r][c] = id;
            blocks[id].push_back({r,c});
        }
    }

    map<long, vector<pll>> conditions;
    for(auto p: blocks){
        id = p.first;
        conditions[id] = {};
        vector<pll> v = p.second;
        for (pll rc: v){
            if(rc.first < R-1 && mat[rc.first+1][rc.second] != id){
                conditions[id].push_back({rc.first+1, rc.second});
            }
        }
    }

    ml wall(R,vl(C,0));


    string ans;
    bool poss, poss_inner;

    while(!conditions.empty()){
        poss = false;
        for(auto p: conditions){
            id = p.first;
            poss_inner = true;
            for (pll rc: p.second){
                if(!wall[rc.first][rc.second]){
                    poss_inner = false;
                    break;
                }
            }
            if (poss_inner){
                conditions.erase(id);
                ans += 'A' + id;
                poss = true;
                for(pll rc: blocks[id]){
                    wall[rc.first][rc.second] = 1;
                }
                break;
            } 
        }

        if (!poss){
            cout << "Case #" << t+1 << ": " << -1 << endl;
            return 0;
        }
    }



    cout << "Case #" << t+1 << ": " << ans << endl;
    return 0;


}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}