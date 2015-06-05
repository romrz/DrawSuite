class Matrix
{
 private:
  float* mData;
  int mR;
  int mC;

 public:
  Matrix() : mR(0), mC(0)  {}
  Matrix(int r, int c) : mR(r), mC(c), mData(new float[mR*mC])  {}

  Matrix& operator=(Matrix& m) { mR = m.mR; mC = m.mC; delete[] mData; mData = new float[mR*mC]; }
  
  float& operator()(int i, int j) const { return mData[i*mR + j]; }

  friend Matrix operator*(const Matrix& a, const Matrix& b);
};
