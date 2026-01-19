class KalmanFilter {
  public:
    KalmanFilter(float processNoise, float measurementNoise, float estimationError, float initialValue) {
      Q = processNoise;
      R = measurementNoise;
      P = estimationError;
      X = initialValue;
    }

    float update(float measurement) {
      P = P + Q;
      float K = P / (P + R);   
      X = X + K * (measurement - X);
      P = (1 - K) * P;

      return X;
    }

  private:
    float Q;
    float R;
    float P;
    float X;
};
