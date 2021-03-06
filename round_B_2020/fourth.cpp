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

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORR(i,a,b) for (int i = (b)-1; i >= (a); i--)
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

long W,H,L,U,R,D;

void pushProb(matrix<double> &state, long w){
    double upper = 0;
    double lefter;
    double facUp, facLeft;
    double cur;
    FOR(h,0,H){
        if(h==0 && w == 0) {upper = 1.0; continue;};
        facLeft = 0.5;
        facUp = 0.5;
        if(w == W-1) facUp = 1.0;
        if(h == H-1) facLeft = 1.0;

        lefter = 0;
        if(w!=0) lefter = state[w-1][h];

        cur = facUp*upper + facLeft*lefter;

        if (L <= w && w <= R && U <= h && h <= D) cur = 0;
        
        state[w][h] = cur;

        upper = cur;
    }
}


long solve(long t){

    cin >> W;
    cin >> H;
    cin >> L;
    cin >> U;
    cin >> R;
    cin >> D;

    L--;
    U--;
    R--;
    D--;

    matrix<double> state(W,vector<double>(H));
    state[0][0] = 1;

    print(H,W)

    FOR(w,0,W){
        pushProb(state, w);
    }

    print(state)



    cout << "Case #" << t+1 << ": " << state[W-1][H-1] << endl;
    return 0;
}

int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}