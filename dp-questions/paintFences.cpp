#include <iostream>
#include <vector>
using namespace std;

int solveUsingRec(int n, int k){
    if(n == 1) return k;
    if(n == 2) return k + (k-1)*k;

    int ans = (solveUsingRec(n-1, k) + solveUsingRec(n-2, k))*(k-1);
    return ans;
}

int solveUsingMem(int n, int k, vector<int> &dp){
    if(n == 1) return k;
    if(n == 2) return k + (k-1)*k;

    if(dp[n-1] != -1) return dp[n];

    dp[n-1] = (solveUsingMem(n-1, k, dp) + solveUsingMem(n-2, k, dp))*(k-1);
    return dp[n-1];
}

int solveUsingTabulation(int n, int k){
    vector<int> dp(n, -1);

    dp[0] = k;
    if(n <= 1) return dp[0];
    dp [1] = k + k*(k-1);
    for(int i = 2; i < n; i++){
        dp[i] = (dp[i-1] + dp[i-2])*(k-1);

    } 
    return dp[n-1];
}

int SpaceOptimization(int n, int k){
    // vector<int> dp(n, -1);

    int prev2 = k;
    if(n <= 1) return prev2;
    int prev1 = k + k*(k-1);
    int curr;
    for(int i = 3; i <= n; i++){
        int curr = (prev1 + prev2)*(k-1);
        prev2 = prev1;
        prev1 = curr;
    } 
    return curr;
}

int main(){
    int n = 3, k = 3;
    // vector<int> dp(n, -1);
    // int ans = solveUsingRec(n, k);
    // int ans = solveUsingMem(n, k, dp);
    // int ans = solveUsingTabulation(n, k);
    int ans = SpaceOptimization(n, k);
    cout<<ans<<endl;
    return 0;
}