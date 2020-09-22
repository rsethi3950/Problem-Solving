#include<bits/stdc++.h>
using namespace std;
int main(){
    string a="longest";
    string b="stone";
    int m=a.length();
    int n=b.length();
    int dp[m+1][n+1];

    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++ ){
            if(i==0 || j==0) dp[i][j]=0;
            else if(a[i-1]==b[j-1]){
                dp[i][j]=1+dp[i-1][j-1];
            }
            else {

                dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
            }
        }
    }
    int index = dp[m][n];
    char lcs[index+1];
    lcs[index] = '\0';
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
      if (a[i-1] == b[j-1])
      {
          lcs[index-1] = a[i-1];
          i--; j--; index--;
      }

      else if (dp[i-1][j] > dp[i][j-1])
         i--;
      else
         j--;
    }
    cout << "LCS of " << a << " and " << b << " is " << lcs;
    cout<<"\nLength of subsequence is "<<dp[m][n];
    return 0;
}
