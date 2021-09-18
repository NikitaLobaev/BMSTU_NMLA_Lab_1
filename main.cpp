#include <Eigen/Dense>
#include <iostream>
#include "IO.cpp"
#include "Matrix.cpp"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: lab_1 <input filename> <output filename>" << std::endl;
        return 1;
    }

    std::basic_ifstream<char, std::char_traits<char>> input(argv[1]);

    Lobaev::Math::Vector<double> vector_a = Lobaev::IO::read_vector<double>(input);
    Lobaev::Math::Vector<double> vector_b = Lobaev::IO::read_vector<double>(input);
    Lobaev::Math::Matrix<double> matrix_a = Lobaev::IO::read_matrix<double>(input);
    Lobaev::Math::Matrix<double> matrix_b = Lobaev::IO::read_matrix<double>(input);

    input.close();

    std::ofstream output(argv[2]);

    { //Скалярное произведение
        const double result_scalar_multiply = vector_a * vector_b;
        Lobaev::IO::print<double>(output, result_scalar_multiply);
        output << std::endl;
    }

    { //Умножение матрицы на вектор
        const Lobaev::Math::Vector<double> result_vector = matrix_a * vector_a;
        Lobaev::IO::print_vector<double>(output, result_vector);
        output << std::endl;
    }

    { //Умножение матрицы на матрицу
        Lobaev::Math::Matrix<double> result_matrix = matrix_a * matrix_b;
        Lobaev::IO::print_matrix<double>(output, result_matrix);
        output << std::endl;
    }

    { //Транспонирование матрицы
        Lobaev::Math::Matrix<double> result_matrix = matrix_a.transpose();
        Lobaev::IO::print_matrix<double>(output, result_matrix);
        output << std::endl;
    }

    output.close();

    {
        Eigen::Matrix<int, 2, 3> eigen_matrix_1;
        eigen_matrix_1(0, 0) = 1;
        eigen_matrix_1(0, 1) = 2;
        eigen_matrix_1(0, 2) = 3;
        eigen_matrix_1(1, 0) = 4;
        eigen_matrix_1(1, 1) = 5;
        eigen_matrix_1(1, 2) = 6;

        eigen_matrix_1.transpose();

        output << "Eigen's matrix:" << std::endl;
        output << eigen_matrix_1 << std::endl;
    }

    return 0;
}
