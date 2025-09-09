//分治 Strassen方法

#include <iostream>
#include <vector>
using namespace std;

// 矩阵相加
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// 矩阵相减
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// 传统矩阵乘法（基本情况）
vector<vector<int>> multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// 分割矩阵为四个子矩阵
void split(const vector<vector<int>>& parent, vector<vector<int>>& child, int row, int col) {
    int n = child.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            child[i][j] = parent[i + row][j + col];
        }
    }
}

// 合并四个子矩阵到父矩阵
void join(vector<vector<int>>& parent, const vector<vector<int>>& child, int row, int col) {
    int n = child.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            parent[i + row][j + col] = child[i][j];
        }
    }
}

// Strassen 矩阵乘法
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    
    // 基本情况：小矩阵使用传统乘法
    if(n <= 2) {
        return multiply(A, B);
    }
    
    // 确保n是偶数，如果不是则填充0
    if(n % 2 != 0) {
        // 这里简化处理，实际应用中需要处理非2的幂次大小的矩阵
    }
    
    int newSize = n / 2;
    vector<vector<int>> result(n, vector<int>(n));
    
    // 分割矩阵A和B为四个子矩阵
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));
    
    // 分割A矩阵
    split(A, A11, 0, 0);
    split(A, A12, 0, newSize);
    split(A, A21, newSize, 0);
    split(A, A22, newSize, newSize);
    
    // 分割B矩阵
    split(B, B11, 0, 0);
    split(B, B12, 0, newSize);
    split(B, B21, newSize, 0);
    split(B, B22, newSize, newSize);
    
    // 计算Strassen的7个乘法项
    vector<vector<int>> M1 = strassen(add(A11, A22), add(B11, B22));      // M1 = (A11+A22)(B11+B22)
    vector<vector<int>> M2 = strassen(add(A21, A22), B11);                // M2 = (A21+A22)B11
    vector<vector<int>> M3 = strassen(A11, subtract(B12, B22));           // M3 = A11(B12-B22)
    vector<vector<int>> M4 = strassen(A22, subtract(B21, B11));           // M4 = A22(B21-B11)
    vector<vector<int>> M5 = strassen(add(A11, A12), B22);                // M5 = (A11+A12)B22
    vector<vector<int>> M6 = strassen(subtract(A21, A11), add(B11, B12)); // M6 = (A21-A11)(B11+B12)
    vector<vector<int>> M7 = strassen(subtract(A12, A22), add(B21, B22)); // M7 = (A12-A22)(B21+B22)
    
    // 计算结果子矩阵
    vector<vector<int>> C11 = add(subtract(add(M1, M4), M5), M7);  // C11 = M1+M4-M5+M7
    vector<vector<int>> C12 = add(M3, M5);                         // C12 = M3+M5
    vector<vector<int>> C21 = add(M2, M4);                         // C21 = M2+M4
    vector<vector<int>> C22 = add(subtract(add(M1, M3), M2), M6);  // C22 = M1+M3-M2+M6
    
    // 合并子矩阵到结果矩阵
    join(result, C11, 0, 0);
    join(result, C12, 0, newSize);
    join(result, C21, newSize, 0);
    join(result, C22, newSize, newSize);
    
    return result;
}

// 打印矩阵
void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // 测试 4x4 矩阵
    vector<vector<int>> A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    vector<vector<int>> B = {
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1}
    };
    
    cout << "矩阵 A:" << endl;
    printMatrix(A);
    
    cout << "\n矩阵 B:" << endl;
    printMatrix(B);
    
    cout << "\n使用 Strassen 算法计算 A × B:" << endl;
    vector<vector<int>> result = strassen(A, B);
    printMatrix(result);
    
    cout << "\n使用传统算法验证结果:" << endl;
    vector<vector<int>> traditional = multiply(A, B);
    printMatrix(traditional);
    
    return 0;
}