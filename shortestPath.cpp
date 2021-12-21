#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace std::string_literals;

constexpr auto infinity64 = numeric_limits<int64_t>::max();

struct edge{
    int next ;
    int w;
};

bool is_differ_one(const string & lhs , const string & rhs ){
    auto k = lhs.size();
    int diff_cnt{};
    for(size_t i = 0 ; i < k ; ++i) 
        if(lhs[i] !=  rhs[i]) ++diff_cnt ;
    return diff_cnt == 1 ;
}

// build a graph { V , E } using Adjacency Table 
// which V contains indices of input nums { 0 , ... , n - 1} 
// and E contains element of tuple{ i , j , 2 * a[j] - a[i] }
auto build_gragh(const vector<string> & a ) {

    const int n = a.size();
    auto g = vector<vector<edge>>{};
    g.resize(a.size());

    for(int i = 0 ; i < n ; ++i) {
        int vi = stoi(a[i]);
        for(int j = i + 1; j < n ; ++j) {
            if(is_differ_one(a[i] , a[j])){
                int vj = stoi(a[j]);
                g[i].push_back({j , 2 * vj - vi});
                g[j].push_back({i , 2 * vi - vj});
            }
        }
    }

    return g; 
} 

auto optimized_bellman_ford(vector<string> a) -> pair<long long , vector<int>> {
    if(a.empty()) {
        return {infinity64 , vector<int>{}};
    }

    // 1.initial
    const auto n = a.size();
    auto g = build_gragh(a);
    auto vis = vector<bool>(n); // test if a[i] is in queue
    auto dist= vector<int64_t>(n , infinity64); // cost array
    auto prev = vector<int>(n , -1);    // record the prev num on the optimal path

    // 2. run Bellman-Ford algorithm with queue optimized
    // condition : no negative ring in the graph 

    auto q = queue<int>{};
    vis[0] = true ;
    dist[0] = 0 ;
    q.push(0);

    while(q.size()){
        int idx = q.front();
        q.pop();
        assert(vis[idx]);
        vis[idx] = false;
        // for each next "diff-one" digit of a[idx]
        // relaxing the edge & update the cost if lower
        for(const auto & e : g[idx]) {
            if(dist[idx] + e.w < dist[e.next] ) {
                dist[e.next] = dist[idx] + e.w;
                prev[e.next] = idx;
                // using vis array to avoid repeated push
                if(!vis[e.next]) {  
                    q.push(e.next);
                    vis[e.next] = true ; 
                }
            }
        }
    }
    
    // 3. retrieve path (backtrace)
    int end = n - 1;
    auto path = vector<int>{};
    if(dist[end] != infinity64) {
        int idx = end;
        while(idx != 0) {
            path.push_back(stoi(a[idx]));
            idx = prev[idx];
            assert(idx != -1);
        }
        path.push_back(stoi(a[0]));
        reverse(path.begin() , path.end());
    }
    
    return {dist[end] , move(path)};
}

auto input() -> vector<string>{
    auto nums = vector<string>{};
    int n , k ;
    cin >> n >> k ;
    string s ;
    for(int i = 0 ; i < n ; ++i) {
        cin >> s ; 
        nums.push_back(move(s));
    }
    return nums ;
} 

void output(long long cost , const vector<int> & path) {
    if(cost == infinity64) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << cost << " " << path.size() << endl;
        for(int num : path) cout << num << " ";
        cout << endl;
    }
} 

int main() {
    auto nums = input();
    auto result = optimized_bellman_ford(move(nums));
    output(result.first , result.second);
}