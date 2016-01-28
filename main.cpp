#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#define ERROR "Error: "
#define USHRT_MAX 65535
#define RANGE 1

using namespace std;

/* This program will generate two random square matrices 'A' and 'B'
 * then multiplies them together into matrix 'C'.
 * Afterwards it outputs the norm of matrix 'C'.
 *
 * Purpose of this is to test gcc optimizer options (like -O3)
 * and see the difference between various compiling.
 */
int main(int argc, char *argv[])
{

  // Two arguments needed.
  if (argc != 3) {
    cout << ERROR
    << "two arguments required: "
    << "matrix size (short int) and random seed (int)\n";

    return 1;
  }

  // Size of the square matrices.
  int size = atoi(argv[1]);

  // First argument is short int.
  if (size <= 0 || size > USHRT_MAX) {
    cout << ERROR
    << "first argument must be between 0 and "
    << USHRT_MAX
    << "\n";

    return 1;
  }

  // Start measuring time.
  clock_t begin = clock();

  // Pseudo random.
  srand(atoi(argv[2]));

  // Alloc space for matrices.
  double** A = new double*[size];
  for (int i = 0; i < size; i++)
    A[i] = new double[size];

  double** B = new double*[size];
  for (int i = 0; i < size; i++)
    B[i] = new double[size];

  double** C = new double*[size];
  for (int i = 0; i < size; i++)
    C[i] = new double[size];

  // Fill some values in matrices: 'A' and 'B'.
  for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
    A[i][j] = RANGE*(rand() / (RAND_MAX+1.0));
  }
  }

  for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
    B[i][j] = RANGE*(rand() / (RAND_MAX+1.0));
  }
  }

  // Value of a 'C' matrix element.
  double sum;
  // USELESS: Counter of diagonal elements.
  unsigned int diags = 0;
  // USELESS: actual element of C matrix (which is being calculated).
  double actual;

  // Matrix multiplication.
  for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
    sum = 0.0;
    actual = 0.0;

    // Necessary for multiplication.
    for (int x = 0; x < size; x++)
      sum += A[i][x] * B[x][j];
    C[i][j] = sum;

    // Yay, reached a diagonal element!
    if (i == j)
      diags += 1;

    // Dead code.
    if (i >= size || j >= size)
      cout << "How you did this?";

    // Let's calculate it again. BTW we won't use this variable.
    for (int x = 0; x < size; x++)
      actual += A[i][x] * B[x][j];
  }
  }

  // Calculate the matrix norm of 'C'.
  double* sum_col = new double[size];
  double col_max;

  for (int i = 0; i < size; i++) {
    sum = 0.0;

    for (int j = 0; j < size; j++)
      sum_col[i] += abs(C[i][j]);
  }

  col_max = sum_col[0];
  for (int i = 1; i < size; i++) {
    if (col_max < sum_col[i])
      col_max = sum_col[i];
  }

  cout << "Norm of matrix 'C': "
  << col_max
  << "\n";

  // Delete matrices, sum_col array.
  for (int i = 0; i < size; i++)
    delete[] A[i];
  delete[] A;

  for (int i = 0; i < size; i++)
    delete[] B[i];
  delete[] B;

  for (int i = 0; i < size; i++)
    delete[] C[i];
  delete[] C;

  delete[] sum_col;

  // Stop measuring time.
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  cout << "Elapsed secs: "
  << elapsed_secs
  << "\n";

  return 0;
}
