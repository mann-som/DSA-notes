#include<iostream>
#include <vector>
using namespace std;

int solveUsingRec(int capacity, int wt[], int profit[], int index, int n){
    if(index >= n){
        return 0;
    }

    int include = 0;
    if(wt[index] <= capacity){
        include = profit[index] + solveUsingRec(capacity-wt[index], wt, profit, index+1, n);
    }
    int exclude = solveUsingRec(capacity, wt, profit, index+1, n);
    return max(include, exclude);
}

int solveUsingMem(int capacity, int wt[], int profit[], int index, int n, vector<vector<int>> &dp){
    if(index >= n) return 0;
    if (dp[capacity][index] != -1) return dp[capacity][index];

    int incl = 0;
    if(wt[index] <= capacity) incl = profit[index] + solveUsingMem(capacity-wt[index], wt, profit, index+1, n, dp);
    int excl = solveUsingMem(capacity, wt, profit, index+1, n, dp);
    
    return dp[capacity][index] = max(incl, excl);
}

int solveUsingTabulation(int capacity, int wt[], int profit[], int index, int n){
    vector<vector<int>> dp(n+1, vector<int>(capacity+1, 0));
    for(int index = n-1; index >= 0; index--){
        for(int cap = 0; cap <= capacity; cap++){
            int incl = wt[index] <= cap ? profit[index] + dp[index+1][cap - wt[index]] : 0;
            int excl = dp[index+1][cap];

            dp[index][cap] = max(incl, excl);
        }
    }
    return dp[0][capacity];

}

int solveUsingTabulationSO(int capacity, int wt[], int profit[], int index, int n){
    vector<int> curr(capacity+1, 0), next(capacity+1, 0);

    for(int index = n-1; index >= 0; index--){
        for(int cap = 0; cap <= capacity; cap++){
            int incl = wt[index] <= cap ? profit[index] + next[cap - wt[index]] : 0;
            int excl = next[cap];
            curr[cap] = max(incl, excl);
        }
        next = curr;        
    }
    return curr[capacity];
}

int main(){
    int capacity = 50, index = 0, n = 3;
    int weight[] = {10, 20, 30};
    int profit[] = {60, 100, 120};
    // vector<vector<int>> dp(capacity+1, vector<int>(n+1, -1));
    // cout<<"Ans: "<<solveUsingRec(capacity, weight, profit, index, n)<< endl;
    // cout<<"Ans: "<<solveUsingMem(capacity, weight, profit, index, n, dp)<< endl;
    // cout<<"Ans: "<<solveUsingTabulation(capacity, weight, profit, index, n)<<endl;
    cout<<"Ans: "<<solveUsingTabulationSO(capacity, weight, profit, index, n)<<endl;
    
}