#include <iostream>
#include <vector>

// TODO: fix this code, its crap
class NaiveBayes {
  const static long N = 200, M = 200;

  long n, m;

  // std::string type[N]; // names [N]
  double u[N][M];  // mean [N][M]
  double s[N][M];  // variance [N][M]
  long R[N][M];    // amount of data [N][M]

  std::vector<double> data[N][M];  // training data [N][M][R]

  void initializeMean() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) u[i][j] = 0;
    }
  }
  void initializeVariance() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) s[i][j] = 1;
    }
  }
  void initializeR() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) R[i][j] = 0;
    }
  }
  void initializeData() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        data[i][j].push_back(0);
      }
    }
  }

  void calculateMean() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        double sum = 0;
        for (int k = 0; k < R[i][j]; k++) sum += data[i][j][k];
        sum /= R[i][j];

        u[i][j] = sum;
      }
    }
  }

  void calculateVariance() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        double sum = 0;
        for (int k = 0; k < R[i][j]; k++)
          sum += pow(u[i][j] - data[i][j][k], 2);

        // sum /= (R[i][j] - 1*(R[i][j] > 1));
        sum /= R[i][j];

        s[i][j] = sum;
      }
    }
  }

  double p(double x, long type, long var) {
    return pow(M_E, (-1.0 / 2.0) *
                        pow((x - u[type][var]) / sqrt(s[type][var]), 2.0)) /
           sqrt(2.0 * M_PI * s[type][var]);
  }

  double probability(double input[], long type) {
    double product = 1.0;

    for (int j = 0; j < m; j++) {
      product *= p(input[j], type, j);
    }

    return product;
  }

 public:
  void train() {
    this->calculateMean();
    this->calculateVariance();
  }

  NaiveBayes(long nn, long mm) {
    n = nn;
    m = mm;
    this->initializeMean();
    this->initializeVariance();
    this->initializeR();
    this->initializeVariance();
  }

  // NaiveBayes(std::string names[N]) {type = names;}

  void addData(long r, std::vector<double> newData[][M]) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < r; k++) {
          data[i][j].push_back(newData[i][j][k]);
        }
        R[i][j] = data[i][j].size();
      }
    }
  }

  void addData(long r, std::vector<double> newData[], long type[]) {
    for (int k = 0; k < r; k++) {
      for (int j = 0; j < m; j++) {
        data[type[k]][j].push_back(newData[j][k]);
        R[type[k]][j] = data[type[k]][j].size();
      }
    }
  }

  void qAddData(long r, std::vector<double> newData[][M]) {
    this->addData(r, newData);
    this->train();
  }

  void qAddData(long r, std::vector<double> newData[], long type[]) {
    this->addData(r, newData, type);
    this->train();
  }

  // void clearData() {
  //     for (int i = 0; i < N; i++) data[i].clear();
  // }

  long get(double input[]) {
    double prob = 0;
    double maxProb = 0;
    long maxType = 0;

    for (int i = 0; i < n; i++) {
      prob = this->probability(input, i);
      if (prob > maxProb) {
        maxProb = prob;
        maxType = i;
      }
    }

    // return type[maxType];
    return maxType;
  }

  double getProbability(double input[], long type) {
    return this->probability(input, type);
  }

  void print() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < R[i][j]; k++) std::cout << data[i][j][k] << " ";
        std::cout << std::endl;
      }
    }
  }

  // std::string[] getNames() {return type;}
  // double** getMean() {return u;}
  // double** getVariance() {return s;}
  // long** getR() {return R;}
  // std::vector<double>** getData() {return data;}
};
