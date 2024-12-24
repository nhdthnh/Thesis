#include <MQ135.h>

const byte mq135Pin = A0;
long preMQ135 = 0;
float mq135Rate = 1;

MQ135 mq135_sensor(mq135Pin);

void checkMQ135() {
  if (now - preMQ135 >= 1000 / mq135Rate) {
    preMQ135 = now;
    ppm = mq135_sensor.getPPM();
  }
}