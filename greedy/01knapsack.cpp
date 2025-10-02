#include <iostream>
#include <vector>
using namespace std;

int dpRec(int i, int weight, int n, vector<int>&weights, vector<int>& values,vector<vector<int>>& dp ){
    if(i >= n || weight <= 0) return 0;
    if(dp[i][weight] != -1) return dp[i][weight];
    int incl = weight - weights[i] < 0  ? 0 : values[i] + dpRec(i+1, weight-weights[i], n, weights, values, dp);
    int excl = dpRec(i+1, weight,n, weights, values, dp);

    return dp[i][weight] = max(incl, excl);
}

int main(){

    int n = 3, w = 50;
    vector<vector<int>> dp(n+1, vector<int>(w+1, -1));
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int ans = dpRec(0, w, n, weights, values, dp);
    cout<<ans<<endl;
    return 0;
}