# Min_Eigenvalue
Compute the minimum eigenvalue and corresponding eigenvector of sparse symmetric matrix

Make sure that the Spectra and Eigen header files are included.
Command to compile the file in ubuntu is:

$ g++ mineig.cpp -o mineig

The command to run the compiled file is:

$ ./mineig < Q Matrix Path> < n > < d >

Q is of size nd x nd. Datasets for matrix Q can be found at: http://mapir.isa.uma.es/jbriales/GSOC_project8_data.zip

The minimum eigenvalue is displayed and the corresponding eigenvector is saved in a file.
