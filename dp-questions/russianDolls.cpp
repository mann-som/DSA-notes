#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main()
{
    vector<vector<int>> envelopes;
    envelopes.push_back({5, 4});
    envelopes.push_back({6, 4});
    envelopes.push_back({6, 7});
    envelopes.push_back({2, 3});

    // sort(envelopes.begin(), envelopes.end());
    sort(envelopes.begin(), envelopes.end(), [](auto &a, auto &b){
        if(a[0] == b[0]) return a[1] > b[1];
        return a[0] < b[0];
    });

    for(auto env:envelopes){
        cout<<env[0]<<" "<< env[1]<<"\n";
    }

    return 0;
}