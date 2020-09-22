#include<bits/stdc++.h>
using namespace std;
int **matrix_allocate(int x1,int y1){
    int **mat= new int*[x1];
    for(int i=0; i<x1; i++) mat[i] = new int[y1];
    return mat;
}
void showResult(int **result, int m, int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
        {
          cout<<result[i][j]<<" ";
        }
        cout<<endl;
    }
}
void matrix_free(int **mat, int row){
    for (int i = 0; i < row; i++) {
        free(mat[i]);
    }
    free(mat);
}
int **matrix_add(int **a, int **b,int row){
    int **mat = matrix_allocate(row,row);
    for(int i=0; i<row; i++){
        for(int j=0; j<row; j++) mat[i][j]=a[i][j]+b[i][j];
    }
    return mat;
}
int **mat_subtract(int **a, int **b,int row){
    int **mat = matrix_allocate(row,row);
    for(int i=0; i<row; i++){
        for(int j=0; j<row; j++) mat[i][j]=a[i][j]-b[i][j];
    }
    return mat;
}
void traditionMult(int **m1,int **m2,int x1, int y1, int x2, int y2){
    int **res= new int*[x1];
    for(int i=0; i<x1; i++) res[i] = new int[y2];
    for(int i=0;i<x1;i++)
    {
        for(int j=0;j<y2;j++)
        {
           res[i][j]=0;
           for(int k=0;k<y1;k++)
           res[i][j]=res[i][j]+m1[i][k]*m2[k][j];
        }
    }
    showResult(res, x1,y2);
}

int **divideAndConq(int **A,int **B,int row){
    int **C = matrix_allocate(row, row);
    if (row == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int row2 = row / 2;
        int **a11 = matrix_allocate(row2, row2);
        int **a12 = matrix_allocate(row2, row2);
        int **a21 = matrix_allocate(row2, row2);
        int **a22 = matrix_allocate(row2, row2);
        int **b11 = matrix_allocate(row2, row2);
        int **b12 = matrix_allocate(row2, row2);
        int **b21 = matrix_allocate(row2, row2);
        int **b22 = matrix_allocate(row2, row2);

        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < row2; j++) {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + row2];
                a21[i][j] = A[i + row2][j];
                a22[i][j] = A[i + row2][j + row2];
                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + row2];
                b21[i][j] = B[i + row2][j];
                b22[i][j] = B[i + row2][j + row2];
            }
        }

        int **c11 = matrix_add(divideAndConq(a11, b11, row2),
                               divideAndConq(a12, b21, row2), row2);
        int **c12 = matrix_add(divideAndConq(a11, b12, row2),
                               divideAndConq(a12, b22, row2), row2);
        int **c21 = matrix_add(divideAndConq(a21, b11, row2),
                               divideAndConq(a22, b21, row2), row2);
        int **c22 = matrix_add(divideAndConq(a21, b12, row2),
                               divideAndConq(a22, b22, row2), row2);

        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < row2; j++) {
                C[i][j] = c11[i][j];
                C[i][j + row2] = c12[i][j];
                C[i + row2][j] = c21[i][j];
                C[i + row2][j + row2] = c22[i][j];
            }
        }
        matrix_free(c11, row2);
        matrix_free(c12, row2);
        matrix_free(c21, row2);
        matrix_free(c22, row2);
    }
    return C;
}
int **StrassenM(int **A,int **B, int row){
    int **C = matrix_allocate(row, row);
    if(row==1){
        C[0][0]= A[0][0]*B[0][0];
    }
    else{
        int row2 = row / 2;
        int **a11 = matrix_allocate(row2, row2);
        int **a12 = matrix_allocate(row2, row2);
        int **a21 = matrix_allocate(row2, row2);
        int **a22 = matrix_allocate(row2, row2);
        int **b11 = matrix_allocate(row2, row2);
        int **b12 = matrix_allocate(row2, row2);
        int **b21 = matrix_allocate(row2, row2);
        int **b22 = matrix_allocate(row2, row2);

        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < row2; j++) {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + row2];
                a21[i][j] = A[i + row2][j];
                a22[i][j] = A[i + row2][j + row2];
                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + row2];
                b21[i][j] = B[i + row2][j];
                b22[i][j] = B[i + row2][j + row2];
            }
        }
        int **p= StrassenM(matrix_add(a11,a22,row2),matrix_add(b11,b22,row2),row2);
        int **q= StrassenM(matrix_add(a21,a22,row2),b11,row2);
        int **r= StrassenM(a11,mat_subtract(b12,b22,row2),row2);
        int **s= StrassenM(a22,mat_subtract(b21,b11,row2),row2);
        int **t= StrassenM(matrix_add(a11,a12,row2),b22,row2);
        int **u= StrassenM(mat_subtract(a21,a11,row2),matrix_add(b11,b12,row2),row2);
        int **v= StrassenM(mat_subtract(a12,a22,row2),matrix_add(b21,b22,row2),row2);

        for(int i=0; i<row2; i++){
            for(int j=0; j<row2; j++){
                C[i][j]=p[i][j]+s[i][j]-t[i][j]+v[i][j];
                C[i][j+row2]=r[i][j]+t[i][j];
                C[i+row2][j]=q[i][j]+s[i][j];
                C[i+row2][j+row2]=p[i][j]+r[i][j]-q[i][j]+u[i][j];
            }
        }
    }
    return C;
}
int main(){
    int **m1;
    int **m2;
    int x1,y1,x2,y2;
    cout<<"enter rows and cols of matrix 1";
    cin>>x1>>y1;
    m1 = new int*[x1];
    for(int i=0; i<x1; i++) m1[i] = new int[y1];
    for(int i=0; i<x1; i++){
        for(int j=0; j<y1; j++) cin>>m1[i][j];
    }
    cout<<"enter rows and cols of matrix 2";
    cin>>x2>>y2;
    m2 = new int*[x2];
    for(int i=0; i<x2; i++) m2[i] = new int[y2];
    for(int i=0; i<x2; i++){
        for(int j=0; j<y2; j++) cin>>m2[i][j];
    }
    cout<<"Result of traditional matrix multiplication is\n";
    traditionMult(m1,m2, x1,y1, x2,y2);
    cout<<"Result of matrix multiplication using Divide and Conquer is\n";
    int **M=divideAndConq(m1,m2,x1);
    showResult(M,x1,y1);
    cout<<"Result of matrix multiplication using Strassen is\n";
    int **N=StrassenM(m1,m2,x1);
    showResult(N,x1,y1);
return 0;
}
