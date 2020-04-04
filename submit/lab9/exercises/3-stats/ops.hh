#ifndef OPS_HH_
#define OPS_HH_

/** sorting operations */
class Ops {
public:

  /** return < 0, == 0, > 0 if a < b, a == b, a > b */
  virtual int compare(int a, int b);
  
  /** swap a[i] and a[j] */
  virtual void swap(int a[], int i, int j);
};

class Counts : public Ops{
  private:
    unsigned int compareCount = 0;
    unsigned int swapCount = 0;

  public:

    int compare(int a, int b) {
      ++compareCount;
      return this -> Ops::compare(a, b);
    }
    void swap(int a[], int i, int j){
      ++swapCount;
      this -> Ops::swap(a, i, j);
    }

    unsigned int getCompareCount(){return compareCount; }
    unsigned int getSwapCount(){ return swapCount; }
};


#endif //ifndef OPS_HH_
