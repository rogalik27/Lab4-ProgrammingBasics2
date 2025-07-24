#include <iostream>
#include <stdexcept>
#include <iomanip>

class MatrixSizeMismatch : public std::runtime_error {
public:
    MatrixSizeMismatch(const std::string& msg) : std::runtime_error(msg) {}
};

class MatrixIndexOutOfBounds : public std::runtime_error {
public:
    MatrixIndexOutOfBounds(const std::string& msg) : std::runtime_error(msg) {}
};

class SimpleFraction {
private:
    int num, den;
    void reduce() {
        int a = std::abs(num), b = std::abs(den);
        while (b) { int t = b; b = a % b; a = t; }
        num /= a; den /= a;
        if (den < 0) { num = -num; den = -den; }
    }
public:
    SimpleFraction(int n = 0, int d = 1) : num(n), den(d) {
        if (d == 0) throw std::invalid_argument("Denominator cannot be zero");
        reduce();
    }
    bool operator<(const SimpleFraction& other) const {
        return num * other.den < other.num * den;
    }
    bool operator>(const SimpleFraction& other) const { return other < *this; }
    bool operator<=(const SimpleFraction& other) const { return !(other < *this); }
    bool operator>=(const SimpleFraction& other) const { return !(*this < other); }
    friend std::istream& operator>>(std::istream& in, SimpleFraction& f) {
        char slash;
        in >> f.num >> slash >> f.den;
        if (f.den == 0) throw std::invalid_argument("Denominator cannot be zero");
        f.reduce();
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const SimpleFraction& f) {
        out << f.num << '/' << f.den;
        return out;
    }
};

template <typename T>
class Matrix {
private:
    T** data;
    int rows, cols;

    void allocate(int r, int c) {
        rows = r; cols = c;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols]();
    }

    void deallocate() {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

public:
    Matrix() : data(nullptr), rows(0), cols(0) {}

    Matrix(int r, int c) {
        if (r <= 0 || c <= 0) throw std::invalid_argument("Invalid matrix size");
        allocate(r, c);
    }

    Matrix(const Matrix& other) {
        allocate(other.rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = other.data[i][j];
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            if (data) deallocate();
            allocate(other.rows, other.cols);
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < cols; ++j)
                    data[i][j] = other.data[i][j];
        }
        return *this;
    }

    ~Matrix() { if (data) deallocate(); }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw MatrixSizeMismatch("Addition: size mismatch");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw MatrixSizeMismatch("Subtraction: size mismatch");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw MatrixSizeMismatch("Multiplication: incompatible sizes");
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    T* operator[](int index) {
        if (index < 0 || index >= rows)
            throw MatrixIndexOutOfBounds("Row index out of bounds");
        return data[index];
    }
    const T* operator[](int index) const {
        if (index < 0 || index >= rows)
            throw MatrixIndexOutOfBounds("Row index out of bounds");
        return data[index];
    }

    friend std::istream& operator>>(std::istream& in, Matrix& m) {
        for (int i = 0; i < m.rows; ++i)
            for (int j = 0; j < m.cols; ++j)
                in >> m.data[i][j];
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j)
                out << std::setw(6) << m.data[i][j];
            out << '\n';
        }
        return out;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

template <typename T>
T findMinElement(const Matrix<T>& m) {
    if (m.getRows() == 0 || m.getCols() == 0)
        throw std::runtime_error("Cannot find minimum in empty matrix");
    T minVal = m[0][0];
    for (int i = 0; i < m.getRows(); ++i)
        for (int j = 0; j < m.getCols(); ++j)
            if (m[i][j] < minVal)
                minVal = m[i][j];
    return minVal;
}

int main() {
    try {
        Matrix<int> mi(2, 3);
        std::cout << "Enter 2x3 int matrix:\n";
        std::cin >> mi;
        std::cout << "Int matrix:\n" << mi;
        std::cout << "Min element: " << findMinElement(mi) << "\n\n";

        Matrix<double> md(2, 3);
        std::cout << "Enter 2x3 double matrix:\n";
        std::cin >> md;
        std::cout << "Double matrix:\n" << md;
        std::cout << "Min element: " << findMinElement(md) << "\n\n";

        Matrix<SimpleFraction> mf(2, 3);
        std::cout << "Enter 2x3 simple fractions (format n/d):\n";
        std::cin >> mf;
        std::cout << "Fraction matrix:\n" << mf;
        std::cout << "Min element: " << findMinElement(mf) << "\n\n";

    } catch (const MatrixSizeMismatch& ex) {
        std::cerr << "Matrix size error: " << ex.what() << '\n';
    } catch (const MatrixIndexOutOfBounds& ex) {
        std::cerr << "Index error: " << ex.what() << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
    }
    return 0;
}

