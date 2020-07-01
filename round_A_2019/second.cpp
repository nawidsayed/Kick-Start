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
#include <queue>
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

ml mat(1, vl(1,0));
long R,C;


list<pll> neighbors(pll cord){
    long r = cord.first;
    long c = cord.second;
    list<pll> l;

    if (r>0 && mat[r-1][c] == MAXLONG) l.push_back(make_pair(r-1,c));
    if (r<R-1 && mat[r+1][c] == MAXLONG) l.push_back(make_pair(r+1,c));
    if (c>0 && mat[r][c-1] == MAXLONG) l.push_back(make_pair(r,c-1));
    if (c<C-1 && mat[r][c+1] == MAXLONG) l.push_back(make_pair(r,c+1));

    return l;
}


long solve(long t){
    cin >> R >> C;
    mat = ml(R, vl(C,MAXLONG));
    
    vector<pll> ones;

    string s; 
    FOR(r,0,R){
        cin >> s;
        FOR(c,0,C){
            if (s[c] == '1'){ 
                ones.push_back(make_pair(r,c));            
                mat[r][c] = 0;
            }
        }
    }

    list<pll> cur;
    for (pll p: ones) cur.push_back(p);

    list<pll> next;
    long d = 0;

    while (!cur.empty()) {
        next.clear();
        for (pll p: cur){
            mat[p.first][p.second] = min(mat[p.first][p.second], d);
            next.splice(next.end(), neighbors(p));
        }
        cur = next;
        d++;
    }

    long max_d = - MAXLONG;

    FOR(r,0,R){
        FOR(c,0,C){
            max_d = max(max_d, mat[r][c]);
        }
    }

    max_d++;

    print(mat)

    vl posMin(max_d,MAXLONG);
    vl posMax(max_d, -MAXLONG);
    vl negMin(max_d,MAXLONG);
    vl negMax(max_d, -MAXLONG);

    FOR(r,0,R){
        FOR(c,0,C){
            long thisd = mat[r][c];
            posMin[thisd] = min(r+c, posMin[thisd]);
            posMax[thisd] = max(r+c, posMax[thisd]);
            negMin[thisd] = min(r-c, negMin[thisd]);
            negMax[thisd] = max(r-c, negMax[thisd]);   
        }
    }

    // print(posMin)
    // print(posMax)
    // print(negMin)
    // print(negMax)

    FORR(dr,0,max_d-1){
        posMin[dr] = min(posMin[dr], posMin[dr+1]);
        posMax[dr] = max(posMax[dr], posMax[dr+1]);
        negMin[dr] = min(negMin[dr], negMin[dr+1]);
        negMax[dr] = max(negMax[dr], negMax[dr+1]);
    }    

    // print(posMin)
    // print(posMax)
    // print(negMin)
    // print(negMax)


    vl maxDists(max_d,0);
    FOR(d, 0, max_d){
        maxDists[d] = (max(posMax[d] - posMin[d], negMax[d] - negMin[d]) + 1) / 2;
    }

    print(maxDists)

    long sol = 0;
    max_d--;

    for(long dist: maxDists){
        print(dist, sol)
        if(dist < sol){
            sol--;
            break;
        }
        if(dist <= sol) break;
        sol ++;
    }
    print(sol, max_d)
    sol = min(max_d,sol);



    cout << "Case #" << t+1 << ": " << sol << endl;

    return 0;
}


int main(){
    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}