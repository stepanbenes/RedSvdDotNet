// This is the main DLL file.

#include "stdafx.h"

#include "Driver.h"

#include <vector>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>

//#include "util.hpp"

using namespace std;
using namespace Eigen;

void REDSVD::Driver::Run(IEnumerable<cli::array<double>^>^ input, int numberOfRows, int numberOfColumns, int rank, [Out] cli::array<double>^% singularValues, [Out] cli::array<double>^% U_VT_columnwise)
{
	MatrixXf A;
	A.resize(numberOfRows, numberOfColumns);
	int i = 0;
	for each (cli::array<double>^ row in input)
	{
		for (int j = 0; j < numberOfColumns; j++)
		{
			A(i, j) = row[j];
		}
		i++;
	}

	// ====================
	RedSVD retMat(A, rank); // compute
	// ====================
	
	const MatrixXf& U = retMat.matrixU();
	const VectorXf& S = retMat.singularValues();
	const MatrixXf& V = retMat.matrixV();
	
	singularValues = gcnew cli::array<double>(S.rows());

	// S
	for (int i = 0; i < S.rows(); i++)
	{
		singularValues[i] = S(i);
	}

	U_VT_columnwise = gcnew cli::array<double>(U.rows() * U.cols() + V.cols() * V.rows());
	
	int index = 0;
	// U
	for (int j = 0; j < U.cols(); j++)
	{
		for (int i = 0; i < U.rows(); i++)
		{
			U_VT_columnwise[index] = U(i, j);
			index++;
		}
	}

	// V transposed
	for (int i = 0; i < V.rows(); i++)
	{
		for (int j = 0; j < V.cols(); j++)
		{
			U_VT_columnwise[index] = V(i, j);
			index++;
		}
	}
}
