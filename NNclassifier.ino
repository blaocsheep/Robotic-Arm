#include <Servo.h>

#define NUM_FINGERS 5
#define NUM_LETTERS 5

const int flexPins[NUM_FINGERS] = {A0, A1, A2, A3, A4};
const int servoPins[NUM_FINGERS] = {3, 5, 6, 9, 10};

Servo servos[NUM_FINGERS];

int flexMin[NUM_FINGERS] = {300, 310, 320, 315, 305};
int flexMax[NUM_FINGERS] = {700, 710, 720, 715, 705};

class KalmanFilter {
  public:
    KalmanFilter(float q, float r, float p, float initial) {
      Q = q;
      R = r;
      P = p;
      X = initial;
    }

    float update(float measurement) {
      P = P + Q;
      float K = P / (P + R);
      X = X + K * (measurement - X);
      P = (1 - K) * P;
      return X;
    }

  private:
    float Q, R, P, X;
};

KalmanFilter kf[NUM_FINGERS] = {
  KalmanFilter(0.5, 5.0, 1.0, 90),
  KalmanFilter(0.5, 5.0, 1.0, 90),
  KalmanFilter(0.5, 5.0, 1.0, 90),
  KalmanFilter(0.5, 5.0, 1.0, 90),
  KalmanFilter(0.5, 5.0, 1.0, 90)
};

const char aslLabels[NUM_LETTERS] = {'A', 'B', 'C', 'D', 'E'};

const int aslPrototypes[NUM_LETTERS][NUM_FINGERS] = {
  {10, 70, 70, 70, 70},
  {10, 10, 10, 10, 10},
  {60, 40, 40, 40, 60},
  {10, 10, 70, 70, 70},
  {70, 70, 70, 70, 70}
};

int distanceSquared(const int a[], const int b[]) {
  int sum = 0;
  for (int i = 0; i < NUM_FINGERS; i++) {
    int diff = a[i] - b[i];
    sum += diff * diff;
  }
  return sum;
}

char classifyASL(const int angles[]) {
  int minDist = 999999;
  int bestIdx = -1;

  for (int i = 0; i < NUM_LETTERS; i++) {
    int d = distanceSquared(angles, aslPrototypes[i]);
    if (d < minDist) {
      minDist = d;
      bestIdx = i;
    }
  }
  return aslLabels[bestIdx];
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_FINGERS; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  int filteredAngles[NUM_FINGERS];

  for (int i = 0; i < NUM_FINGERS; i++) {
    int flexRaw = analogRead(flexPins[i]);
    float angle = map(flexRaw, flexMin[i], flexMax[i], 0, 180);
    angle = constrain(angle, 0, 180);
    float smoothAngle = kf[i].update(angle);
    filteredAngles[i] = (int)smoothAngle;
    servos[i].write(filteredAngles[i]);
  }

  char detectedLetter = classifyASL(filteredAngles);

  Serial.print("Angles: ");
  for (int i = 0; i < NUM_FINGERS; i++) {
    Serial.print(filteredAngles[i]);
    Serial.print(" ");
  }
  Serial.print("| ASL: ");
  Serial.println(detectedLetter);

  delay(20);
}
