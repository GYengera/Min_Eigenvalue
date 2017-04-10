#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Spectra/SymEigsShiftSolver.h>
#include <Spectra/MatOp/SparseSymShiftSolve.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace Eigen;
using namespace Spectra;
using namespace std;

typedef Triplet<double> Trip;

int main(int argc, char* argv[])
{
	int n = atoi(argv[2]), d = atoi(argv[3]), ND = n*d;
	// Read Q matrix from file into an Eigen::SparseMatrix object
	ifstream input(argv[1],std::ios::in);
	if(!input)
	{
		std::cout << "ERROR: Q matrix data not defined" << endl;
		return 0;
	}
	vector<Trip> coefficients;
	int row, col;
	double value;
	string line;
	while(std::getline(input,line))
	{
		stringstream entry(line);	
		entry >> row >> col >> value;
		coefficients.push_back(Trip(row-1,col-1,value));
	}
	input.close();
	SparseMatrix<double> Q(ND,ND);
	Q.setFromTriplets(coefficients.begin(), coefficients.end());
	
	//Define the required eigen solver using SPECTRA
	//Q matrix is sparse and symmetric 
	//The Shift Solver is used (with sigma = 0) as it is the preferred method for minimum eigenvalue computation
	SparseSymShiftSolve<double> op(Q);
	SymEigsShiftSolver< double, LARGEST_ALGE, SparseSymShiftSolve<double> > eigs(&op, 1, 10, 0.0);
	eigs.init();
	int nconv = eigs.compute();
	VectorXd evalue, eigvec;	
	if(eigs.info() == SUCCESSFUL){
		evalue = eigs.eigenvalues();
		cout << evalue << endl; //Minimum eigenvalue is displayed
		eigvec = eigs.eigenvectors();	
	}

	//Saving the eigenvector to a file
	ofstream outfile;
	outfile.open("/home/gaurav/eigen_vector.txt"); //Required path should be defined here
	if(!outfile) {
    		std::cout << "Cannot open file to save the eigenvector";
	}
	for(int i = 0; i < ND; ++i){
			outfile << *(eigvec.data() + i);	
			outfile << std::endl;
	}
	outfile.close();

	return 0;
}
