/*
 * Problem: CSES 1651 - Range Update Queries
 * 
 * Problem Statement:
 * Given an array of n integers, process q queries:
 * 1. Type 1: Increase each value in range [a,b] by u
 * 2. Type 2: Get the value at position k
 * 
 * Approach Using Difference Array + Prefix Sum:
 * 1. Maintain a difference array to handle range updates efficiently
 * 2. For range update [a,b] by u:
 *    - diff[a] += u (start of range)
 *    - diff[b+1] -= u (end of range + 1)
 * 3. For point query at position k:
 *    - Calculate prefix sum from 1 to k in difference array
 *    - Add this to original value at position k
 * 
 * Key Insight:
 * - Difference array converts O(n) range update to O(1)
 * - Prefix sum reconstructs actual increments at any position
 * - diff[i] represents the "change" that starts at position i
 * - prefix_sum(diff[1..k]) gives total increment at position k
 * 
 * Time Complexity: O(n + q) where n = array size, q = queries
 *   - Each update query: O(1)
 *   - Each point query: O(1) with prefix sum maintenance
 * 
 * Space Complexity: O(n) for difference array
 * 
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    // Read initial array (1-indexed for convenience)
    vector<long long> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    // Difference array to track range updates
    // diff[i] = change that starts at position i
    vector<long long> diff(n + 2, 0); // Extra space to avoid out of bounds
    
    // Process queries
    while (q--) {
        int type;
        cin >> type;
        
        if (type == 1) {
            // Range update query: increase [a,b] by u
            int a, b;
            long long u;
            cin >> a >> b >> u;
            
            // Difference array update
            // Add u starting from position a
            diff[a] += u;
            // Subtract u starting from position b+1 (to stop the increment)
            diff[b + 1] -= u;
            
        } else {
            // Point query: get value at position k
            int k;
            cin >> k;
            
            // Calculate prefix sum of difference array up to position k
            // This gives us the total increment at position k
            long long total_increment = 0;
            for (int i = 1; i <= k; i++) {
                total_increment += diff[i];
            }
            
            // Final value = original value + all increments
            long long result = arr[k] + total_increment;
            cout << result << "\n";
        }
    }
    
    return 0;
}
