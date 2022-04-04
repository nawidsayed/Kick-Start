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

vl fac;
vector<vl> numbers;
long digits = 4;

void init_fac() {
    fac = vl(18);
    fac[0] = 1;
    FOR(i,1,18) fac[i] = i* fac[i-1];
}

long perm(vl &v) {
    long sum = 0;
    long prod = 1;
    for(long k: v) {
        prod *= fac[k];
        sum += k;
    }
    return fac[sum] / prod;
} 


vl to_vec(long k) {
    vl v;
    while (k != 0) {
        v.push_back(k % 10);
        k /= 10;
    }
    return v;
}

bool is_interesting(vl &v) {
    long sum = 0;
    long prod = 1;
    FOR(i,1,10) {
        sum += v[i] * i;
        FOR(j,0,v[i]) prod *= i;
    }
    if (sum == 0) return false;
    return prod % sum == 0;
}

void init_numbers() {
    numbers = {{0}};
    vector<vl> next;
    FOR(i,1,10) {
        next.clear();
        for(vl num: numbers) {
            long sum = 0;
            FOR(j,0,num.size()) sum += num[j];
            FOR(j,0,digits - sum + 1) {
                vl num2 = num;
                num2.push_back(j);
                next.push_back(num2);
            }
        }
        numbers = next;
    }
    next.clear();
    for (vl num: numbers){
        if (is_interesting(num)) next.push_back(num);
    }
    numbers = next;
}

long sum_func (vl &v) {
    long sum = 0;
    for(long x: v) sum += x;
    return sum;
}

// Assume sum (v) is k.size()
long poss(vl k, vl v) {
    // print(v)
    // print(k)
    if (k.size() != sum_func(v)) throw 1;
    if (k.size() == 0) return 1;
    long sig = k[k.size() - 1];
    long sum = 0;
    FOR(i,0,sig) {
        if (v[i] > 0) {
            v[i] --;
            sum +=  perm(v);
            v[i] ++;
        }
    }
    if (v[sig] == 0) return sum;
    v[sig] --;
    k.pop_back();
    return sum + poss(k,v);
}

long subnum0(long k) {
    long p1 = 1;
    long p2 = 1;
    FOR(i,0,k) {
        p1 *= 10;
        p2 *= 9;
    }
    return p1-p2;
}

long subnum(long k) {
    long p1 = 1;
    long p2 = 1;
    FOR(i,0,k) {
        p1 *= 10;
        p2 *= 9;
    }
    return p1;    
}

long num_with_0(long a){
    long sum = 0;
    FOR(i,0,a){
        for (long x: to_vec(i)){
            if (x == 0) {sum++; break;}
        }
    }
    return sum;
}

long solve(long t){
    long a, b;
    cin >> a >> b;

    long sum = 0;
    vl ka = to_vec(a-1);
    vl kb = to_vec(b);
    for (vl num: numbers) {        
        long diff = 0;
        if (sum_func(num) < kb.size()) diff += perm(num);
        if (sum_func(num) < ka.size()) diff -= perm(num);
        if (sum_func(num) == kb.size()) diff += poss(kb, num);
        if (sum_func(num) == ka.size()) diff -= poss(ka, num);
        sum += diff; 
    }
    print(a, num_with_0(a));
    print(b, num_with_0(b+1));


    cout << "Case #" << t+1 << ": " << sum << endl;
    return 0;
}




int main(){
    init_fac();
    init_numbers();
    print(numbers.size())

    // vl v = {0,2,0,3};
    // vl k = to_vec(22222);
    // print(k)
    // print(v)

    // print(poss(k , v))
    // print(perm(v))

    long T;
    cin >> T;
    FOR(t,0,T) solve(t);
}