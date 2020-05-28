#include <iostream>
#include <fstream>
#include <random>


std::vector<double> GenerateRandomObservations(const double& mean, const double& stddev,
  const int& n_obs) {
  std::default_random_engine generator;
  std::normal_distribution<double> dist(mean, stddev);
  std::vector<double> obs;
  for (int i = 1; i < n_obs; i++) {
    obs.push_back(dist(generator));
  }
  return obs;
}

std::ofstream OpenFile(const std::string& path_file) {
  std::ofstream file_stream;
  file_stream.open(path_file);
  return file_stream;
}

void CloseFile(std::ofstream& file_stream) {
  file_stream.close();
}

void LogValues(std::ofstream& file_stream, const std::vector<double> valueVec) {
  for (int i = 0; i < valueVec.size(); i++) {
    file_stream << valueVec[i];
    if (i != valueVec.size()-1) {
      file_stream << " ";
    }
  }
  file_stream << "\n";
}

int main()
{
  // Process
  const double A {1};
  const double process_std_dev {sqrt(1e-5)};
  const double Q {process_std_dev * process_std_dev};

  // Observations
  const int n_obs {50};
  const double obs_mean {-0.37727};
  const double obs_std_dev {0.1};
  const double R {obs_std_dev * obs_std_dev};

  // Initial values
  double x_hat {0};
  double P {1}; // initial variance of the x_hat

  // A priori estimates ("predict")
  double x_hat_minus;
  double P_minus;

  double K; // gain matrix

  const std::string kPathLogfile {"logfile.dat"};

  std::vector<double> z {GenerateRandomObservations(obs_mean, obs_std_dev, n_obs)};

  std::ofstream logfile_stream {OpenFile(kPathLogfile)};

  for (int i = 0; i < z.size(); i++) {

    // Time update ("predict")
    x_hat_minus = A * x_hat;
    P_minus = A * P * A + Q;

    // Measurement update ("correct")
    K = P_minus / (P_minus + R); // gain
    x_hat = x_hat_minus + K * (z[i] - x_hat_minus);
    P = (1-K)*P_minus;

    // Logging
    if (i == 0) { logfile_stream << "# i K x_hat sqrt(P)\n"; }
    LogValues(logfile_stream, std::vector<double> {double(i), K, x_hat, sqrt(P)});

  }

  CloseFile(logfile_stream);

  return 0;
}
