# include <iostream>
# include <vector>
# include <iostream>
using namespace std;

int longestCommonSubsequence(const vector<int>& nums1, const vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

vector<int> mass_search(vector<int> request, vector<vector<int>> all_indexes) {
    vector<int> best_matches = {};
    for (int i = 0; i < all_indexes.length(); i++) {
        int lcs = longestCommonSubsequence(request, all_indexes[i]);
        if (lcs < 11) {
            best_matches.push_back(lcs);
        }
    }

    return best_matches
}