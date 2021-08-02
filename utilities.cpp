#include "utilities.h"

#include <algorithm>
#include <iostream>
#include <math.h>

// MATRIX DETERMINANT CALCULATION 1
int CalcDeterminant(vector<vector<int>> Matrix){
        int det = 0;
        if (Matrix.size() == 1){
            return Matrix[0][0];
        } else if (Matrix.size() == 2){
            det = (Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0]);
            return det;
        } else {
            for (size_t p = 0; p < Matrix[0].size(); p++){
                vector<vector<int>> TempMatrix;
                for (size_t i = 1; i < Matrix.size(); i++){
                    vector<int> TempRow;
                    for (size_t j = 0; j < Matrix[i].size(); j++){
                        if (j != p){
                           TempRow.push_back(Matrix[i][j]);
                        }
                    }
                    if (TempRow.size() > 0)
                        TempMatrix.push_back(TempRow);
                }
                det = det + Matrix[0][p] * pow(-1, p) * CalcDeterminant(TempMatrix);
            }
            return det;
        }
}

// MATRIX DETERMINANT CALCULATION 2
int getDeterminant(std::vector<std::vector<int>> vect) {
    if(vect.size() != vect[0].size()) {
        throw std::runtime_error("Matrix is not quadratic");
    }
    int dimension = vect.size();

    if(dimension == 0) {
        return 1;
    }

    if(dimension == 1) {
        return vect[0][0];
    }

    //Formula for 2x2-matrix
    if(dimension == 2) {
        return vect[0][0] * vect[1][1] - vect[0][1] * vect[1][0];
    }

    int result = 0;
    int sign = 1;
    for(int i = 0; i < dimension; i++) {

        //Submatrix
        std::vector<std::vector<int>> subVect(dimension - 1, std::vector<int> (dimension - 1));
        for(int m = 1; m < dimension; m++) {
            int z = 0;
            for(int n = 0; n < dimension; n++) {
                if(n != i) {
                    subVect[m-1][z] = vect[m][n];
                    z++;
                }
            }
        }

        //recursive call
        result = result + sign * vect[0][i] * getDeterminant(subVect);
        sign = -sign;
    }

    return result;
}

// APLHABET INDEX FINDER
int getIndex(vector<char> v, char C){
    auto it = find(v.begin(), v.end(), C);

    if (it != v.end())
    {
        int index = it - v.begin();
        return index;
    }
    else {
        return 0;
    }
}

// INVERSE MATRIX 3x3
vector<vector<int>> inverseVec33(vector<vector<int>> J, int dim){
	//Matrix of Minors
	vector<vector<int > > invJ(dim,vector<int > (dim));
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			invJ[i][j] = (J[(i+1)%dim][(j+1)%dim]*J[(i+2)%dim][(j+2)%dim] -
						  J[(i+2)%dim][(j+1)%dim]*J[(i+1)%dim][(j+2)%dim]);
		}
	}

	//determinant of the matrix:
	int detJ = 0.0;
	for(int j=0; j<dim; j++)
	{ detJ += J[0][j]*invJ[0][j];}

	//Inverse of the given matrix.
	 vector<vector<int > > invJT(dim,vector<int > (dim));
	 for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			invJT[i][j] = invJ[j][i]/detJ;
		}
	}

	return invJT;
}

// INVERSE MATRIX GETTER
vector<vector<int>> getInverse(vector<vector<int>>& A){
	vector<vector<int>> result;

	if (A.size() == 2){
		// calculate as 2...
		int a = A[0][0];
		int b = A[0][1];
		int c = A[1][0];
		int d = A[1][1];
		b *= -1;
		c *= -1;

		vector<int> vec_1 = {d, b};
		vector<int> vec_2 = {c, a};
		result.push_back(vec_1);
		result.push_back(vec_2);
	}else if (A.size() == 3){
		result = inverseVec33(A, 3);
	}

    return result;
}

// ENTER Q-MATRIX
vector<vector<int>> EnterMatrix(){
	vector<vector<int>> matrix;
	int n, num, row_num_amount;

	cout << "Enter the number NxN number of matrix rows and columns: ";
	cin >> n;

	cout << "Enter matrix elements (row filling): " << endl;

	int counter = 0;
	vector<int> row;
	row_num_amount = 0;
	while (counter != n*n){
		cout << "Enter the number to fill in: ";
		cin >> num;

		row.push_back(num);

		++row_num_amount;
		if (row_num_amount == n){
			matrix.push_back(row);
			row.clear();
			row_num_amount = 0;
		}
		++counter;
	}

	if (getDeterminant(matrix) != 1){
		cout << "matrix determinant is not equal to 1" << endl;
		EnterMatrix();
	}

	return matrix;
}

// MATRIX MULTIPLICATION
vector<vector<int>> MultiplyMatrix(vector<vector<int>>& a, vector<vector<int>>& b){
    const int n = a.size();     // a rows
    const int m = a[0].size();  // a cols
    const int p = b[0].size();  // b cols

    vector<vector<int>> c(n, vector<int>(p, 0));
    for (auto j = 0; j < p; ++j){
        for (auto k = 0; k < m; ++k){
            for (auto i = 0; i < n; ++i){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

// FULL SENTENCE SUPPORT
vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }else{
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

// INPUT
vector<string> Input(){
	string input_to_use;
	cout << "Enter the text to encrypt/decrypt: "s;
	getline(cin, input_to_use);

	return SplitIntoWords(input_to_use);
}

// RESULT PRINT
void PrintResult(vector<string> encrypted_words){
	for (const auto& word : encrypted_words){
		if (word != encrypted_words[encrypted_words.size() - 1]){
			cout << word << " "s;
		}else{
			cout << word;
		}
	}
	cout << endl;
}
