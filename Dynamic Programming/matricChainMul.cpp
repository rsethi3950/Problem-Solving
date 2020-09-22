#include<bits/stdc++.h>
using namespace std;
void matrixChain(int p[], int n){
    int m[n+1][n+1],s[n+1][n+1];
    for(int i=0; i<=n; i++){
        for(int j=0; j<n; j++){
            m[i][j]=0;
            s[i][j]=0;
        }
    }
    int cost= INT_MAX;
    for (int l=2; l<=n; l++){
        for(int i=1; i<=n-l+1; i++){
            int j=i+l-1;
            m[i][j]= INT_MAX;
            for(int k=i; k<j; k++){
                cost= m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if (cost<m[i][j]){
                    m[i][j]=cost;
                    s[i][j]=k;
                }
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\nMinimum number of operations are :"<<m[1][n];

}
int main(){
    int n=4;
    int arr[]={5,4,6,2,7};
    matrixChain(arr,n);
    return 0;
}
