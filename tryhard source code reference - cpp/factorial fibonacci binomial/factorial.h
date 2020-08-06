
#ifndef _ZG_FACTORIAL_H
#define _ZG_FACTORIAL_H

#include <vector>

namespace zg{
  
  /* __________ Factorial */
  /* Templated */
  template<unsigned N_>
  struct TFactorial
  {
    constexpr static unsigned val = TFactorial<N_-1>::val * N_;
  };
  template<>
  struct TFactorial<1>
  {
    constexpr static unsigned val = 1;
  };
  template<>
  struct TFactorial<0>
  {
    constexpr static unsigned val = 1;
  };
  
  /*Plan old function */
  unsigned Factorial(unsigned N_);
  
  
  /* __________ Binomial */
  /* Templated */
  template<unsigned N, unsigned R>
  struct TnCr
  {
    constexpr static unsigned val = TFactorial<N>::val / (TFactorial<N-R>::val * TFactorial<R>::val);
  };
  
  /*Plan old function */
  unsigned nCr(unsigned N_, unsigned R_);
  
  template<typename T = unsigned>
  std::vector<T> GetBinomialSequence(unsigned N_)
  {
    std::vector<T> tmp;
    tmp.reserve(N_ + 1);
    tmp.push_back(T(1));
    
    for (unsigned i = 0; i < N_; ++i)
      tmp.push_back(T(1));
    
    //Loop is for N > 1, 3 term or more
    for (unsigned i = 1; i < N_; ++i)
    {
      T getprev = tmp[0];
      for (unsigned j = 1; j < i + 1; ++j)
      {
        T value = getprev + tmp[j];
        getprev = tmp[j];
        tmp[j] = value;
      }
    }
    return tmp;
    
    ////__________ Brute force
    //std::vector<T> tmp;
    //tmp.push_back(T(1));
    //
    //for (int j = 0; j < N_; ++j)
    //{
    //	std::vector<T> aatmp;
    //	for (auto i = 1; i < tmp.size(); ++i)
    //	{
    //		aatmp.push_back(tmp[i - 1] + tmp[i]);
    //	}
    //	aatmp.insert(aatmp.begin(), 1.0f);
    //	aatmp.push_back(T(1));
    //	tmp = aatmp;
    //}
    //return tmp;
  }
  
} //namespace zg

#endif //#ifndef _ZG_FACTORIAL_H
