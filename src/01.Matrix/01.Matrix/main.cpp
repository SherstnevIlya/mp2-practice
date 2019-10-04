#include "TMatrix.h"
#include <string>

using namespace std;

void main() {
	TMatrix<int> a(5), d(4), e(5), f(5);
	TVector<TVector<int>> c(5);
	
	a.Fill(0, 100);
	d.Fill(0, 100);
	
	/*cout << "Enter matrix E: " << endl;
	try {
		cin >> e;
	}
	catch (std::string k) { cout << k << endl; }

	try {
		cout << "Trying to create invalid matrix: ";
		TMatrix<double> InvalidMatrix(-4);
	}
	catch (std::string k) { cout << k << endl; }*/

	try {
		cout << "Trying to convert Vector<Vector> to Matrix: " << endl;
		TVector<int> v1(3, 0);
		TVector<int> v2(2, 1);
		TVector<int> v3(1, 2);
		cin >> v1 >> v2 >> v3;
		TVector<TVector<int>> v(3);
		v[2] = v3;
		v[1] = v2;
		v[0] = v1;
		TMatrix<int> ConvertedMatrix(v);
		cout << "Converted matrix" << endl << ConvertedMatrix;
	}
	catch (std::string k) { cout << k << endl; }
	
	cout << "Testing copy-constructor:" << endl << "Matrix A:" << endl << a;
	TMatrix<int> b(a);
	cout << "Copy from A to B:" << endl << b;

	try {
		cout << "Testing A == B: " << (a == b) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	try {
		cout << "Testing A != B: " << (a != b) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	try {
		cout << "Testing A == D: " << (a == d) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	try {
		cout << "Testing A != D: " << (a != d) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	cout << "Testing A + 5: " << endl << (a + 5) << endl;
	cout << "Testing A - 5: " << endl << (a - 5) << endl;
	cout << "Testing A * 2: " << endl << (a * 2) << endl;

	cout << "Matrix E: " << endl << e << endl;
	cout << "Determinant of E: ";
	try {
		cout << e.Determinant() << endl;
	}
	catch (std::string k) { cout << k << endl; }

	f = e;
	cout << "F = E: " << endl;
	try {
		cout << "F[0][0] = ";
		cout << f[0][0] << endl;
	}
	catch (std::string k) { cout << k << endl; }

	try {
		cout << "F[100][100] = ";
		cout << f[100][100] << endl;
	}
	catch (std::string k) { cout << k << endl; }

	cout << "Testing A + E: " << endl;
	try {
		cout << (a + e) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	cout << "Testing A + D: " << endl;
	try {
		cout << (a + d) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	cout << "Testing A - E: " << endl;
	try {
		cout << (a - e) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	cout << "Testing A - D: " << endl;
	try {
		cout << (a - d) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	cout << "Testing A * E: " << endl;
	try {
		cout << (a * e) << endl;
	}
	catch (std::string k) { cout << k << endl; }

	cout << "Testing A * D: " << endl;
	try {
		cout << (a * d) << endl;
	}
	catch (std::string k) { cout << k << endl; }
	
	int t;
	cin >> t;
}