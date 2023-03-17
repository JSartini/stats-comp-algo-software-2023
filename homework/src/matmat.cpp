#include <Rcpp.h>

using Rcpp::NumericMatrix;
using Rcpp::NumericVector;

// [[Rcpp::export]]
NumericMatrix row_col_dot_matmat(
    const NumericMatrix& A, const NumericMatrix& B
  ) {
  if (A.ncol() != B.nrow()) {
    Rcpp::stop("Incompatible dimensions");
  }
  int n_row_out = A.nrow();
  int n_col_out = B.ncol();
  NumericMatrix result(n_row_out, n_col_out);
  
  for (int i = 0; i < n_row_out; ++i) {
    for (int j = 0; j < n_col_out; ++j) {
      result(i, j) = sum(A(i, Rcpp::_ ) * B( Rcpp::_ , j));
    }
  }
  return result;
}

// [[Rcpp::export]]
NumericMatrix col_oriented_matmat(
    const NumericMatrix& A, const NumericMatrix& B
  ) {
  if (A.ncol() != B.nrow()) {
    Rcpp::stop("Incompatible dimensions");
  }
  int n_row_out = A.nrow();
  int n_col_out = B.ncol();
  int n_dot = B.nrow();
  NumericMatrix result(n_row_out, n_col_out);
  std::fill(result.begin(), result.end(), 0);
  for(int j = 0; j < n_col_out; ++j) {
    for(int k = 0; k < n_dot; ++k) {
      for(int i = 0; i < n_row_out; ++i) {
        result(i, j) += A(i, k) * B(k, j);
      }
    }
  }
  return result;
}

