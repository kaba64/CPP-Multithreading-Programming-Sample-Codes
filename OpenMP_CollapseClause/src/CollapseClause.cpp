#include <iostream>
#include <memory>
#include <chrono>
#include <execution>
#include <cstdlib>
#include <cblas.h>
#include <omp.h>
#include "common.h"

using TypeVar = double;
constexpr int iterations{1000};

template<typename T>
void initMatrix(T* ptr,const int M,const int N,Random<T>& rand){
  /*Matrix is stored in column-major format*/
  for (int j = 0; j < N; ++j){
    for (int i = 0; i < M; ++i){
      ptr[j*M+i] = rand.randomNumber();
    }
  }
}

template<typename T>
void GEMM(const int M,const int N,const int K,const T alpha,const T* A,
		const int lda,const T* B,const int ldb,const T beta,
	  T* C,const int ldc){
  
  for (int j = 0; j < N; ++j){
    for (int i = 0; i< M; ++i){
      T temp = beta*C[j*M+i];
      for(int p=0;p<K;++p){
	temp+=alpha*A[i+p*M]*B[j*M+p];
      }
      C[j*M+i] = temp;
    }
  }
}

template<typename T>
void GEMM_OpenMP(const int M,const int N,const int K,const T alpha,const T* A,
                const int lda,const T* B,const int ldb,const T beta,
          T* C,const int ldc){

#pragma	omp parallel for collapse(2)
  for (int j = 0; j < N; ++j){
    for (int i = 0; i< M; ++i){
      T temp = beta*C[j*M+i];
      for(int p=0;p<K;++p){
        temp+=alpha*A[i+p*M]*B[j*M+p];
      }
      C[j*M+i] = temp;
    }
  }
}

template<typename T>
void compareResults(const int M,const int N, const T* Aref,
		    const T* Acomput){
  T eps{1e-10};
  for (int j = 0; j < N; ++j){
    for (int i = 0; i < M; ++i){
      if(std::abs(Aref[j*M+i]-Acomput[j*M+i])>eps){
	std::cerr<<j*M+i<<"\t"<<std::abs(Aref[j*M+i]-Acomput[j*M+i])<<"\n";
	std::cerr<<"Error\n";
	exit(EXIT_FAILURE);
      }
    }
  }
}

int main(int argc, char * argv[]) {
  
  int m, n,k;
  if (argc != 4){
    std::cerr<<"Enter the dimensions of the matrices\n";
    std::cerr<<"A(m,k) \t B(k,n) \t C(m,n)\n";
    exit(EXIT_FAILURE);
  }else{
    m = std::atoi(argv[1]); n = std::atoi(argv[2]);
    k = std::atoi(argv[3]);
  }
  
  std::unique_ptr<TypeVar[]> A           = std::make_unique<TypeVar[]>(m*k);
  std::unique_ptr<TypeVar[]> B           = std::make_unique<TypeVar[]>(k*n);
  std::unique_ptr<TypeVar[]> C           = std::make_unique<TypeVar[]>(m*n);
  std::unique_ptr<TypeVar[]> C_OpenMP    = std::make_unique<TypeVar[]>(m*n);
  std::unique_ptr<TypeVar[]> C_blas      = std::make_unique<TypeVar[]>(m*n);
  
  /*BLAS parameters: https://www.netlib.org/lapack/explore-html-3.6.1/dc/d18*/
  enum CBLAS_LAYOUT layout    = CblasColMajor;
  enum CBLAS_TRANSPOSE transA = CblasNoTrans;
  enum CBLAS_TRANSPOSE transB = CblasNoTrans;
  Random<TypeVar> random;
  TypeVar one = static_cast<TypeVar>(1), zero = static_cast<TypeVar>(0);
  
   
  initMatrix(A.get(),m,k,random);
  initMatrix(B.get(),k,n,random);
  std::fill(std::execution::par_unseq,C.get(),C.get()+m*n,static_cast<TypeVar>(0));
  std::fill(std::execution::par_unseq,C_OpenMP.get(),C_OpenMP.get()+m*n,static_cast<TypeVar>(0));
  std::fill(std::execution::par_unseq,C_blas.get(),C_blas.get()+m*n,static_cast<TypeVar>(0));
  
  std::chrono::duration<double, std::milli> chronoBlas;
  double TimeBlas{0.0};
  for(int t=0;t<iterations;++t){
    auto start = std::chrono::high_resolution_clock::now();
    cblas_dgemm(layout,transA,transB,m,n,k,one,A.get(),m,B.get(),k,zero,C_blas.get(),m);
    auto end = std::chrono::high_resolution_clock::now();
    chronoBlas = end-start;
    TimeBlas+=chronoBlas.count();
  }
  std::cout << "OpenBLAS time : " <<TimeBlas/iterations<<" ms\n";
  
  std::chrono::duration<double, std::milli> chronoGEMM;
  double TimeGEMM{0.0};
  for(int t=0;t<iterations;++t){
    auto start = std::chrono::high_resolution_clock::now();
    GEMM(m,n,k,one,A.get(),m,B.get(),k,zero,C.get(),m);
    auto end = std::chrono::high_resolution_clock::now();
    chronoGEMM = end-start;
    TimeGEMM+=chronoGEMM.count();
  }
  std::cout << "GEMM time : " <<TimeGEMM/iterations<<" ms\n";

  std::chrono::duration<double, std::milli> chronoGEMM_OpenMP;
  double TimeGEMM_OpenMP{0.0};
  for(int t=0;t<iterations;++t){
    auto start = std::chrono::high_resolution_clock::now();
    GEMM_OpenMP(m,n,k,one,A.get(),m,B.get(),k,zero,C_OpenMP.get(),m);
    auto end = std::chrono::high_resolution_clock::now();
    chronoGEMM_OpenMP = end-start;
    TimeGEMM_OpenMP+=chronoGEMM_OpenMP.count();
  }
  std::cout << "GEMM_OpenMP time : " <<TimeGEMM_OpenMP/iterations<<" ms\n";
  
  compareResults(m,n,C_blas.get(),C_OpenMP.get());
 
  return 0;
}
