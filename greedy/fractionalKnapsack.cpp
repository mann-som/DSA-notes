#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// bool myComp(pair<int, int> p1, pair<int, int> p2){
//     return p1.first > p2.first;
// }
int main(){

    int n = 3;
    int weight = 50;
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    priority_queue<pair<float, int>> pq;
    for(int i = 0; i < n; i++){
        float ratio = values[i]/weights[i];
        pq.push({ratio, i});
    }

    // int i = 0;
    int ans = 0;
    while(!pq.empty() || weight > 0){
        auto pair = pq.top(); pq.pop();
        float ratio = pair.first;
        int index = pair.second;
        int w = weights[index], v = values[index];

        if(w <= weight){
            ans += v;
            weight -= w;
        }
        else{
            ans += (ratio * weight);
            break;
        }
    }

    cout<<ans<<endl;
    return 0;
}