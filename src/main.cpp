#include "sequencer.h"

Sequencer sequencer;

struct my_struct {
  uint8_t a, b;
};

my_struct my_data[4];

void callback(void *data) {
  my_struct step_data = *((my_struct *) data);

  Serial.print("a:");
  Serial.print(step_data.a);
  Serial.print(" b:");
  Serial.println(step_data.b);
}

void setup() {
  Serial.begin(115200);

  sequencer.set_loop_forever(true);
  sequencer.set_callback(callback);

  my_data[0] = {1, 2};
  sequencer.add(1000, &my_data[0]);

  my_data[1] = {3, 4};
  sequencer.add(2000, &my_data[1]);

  my_data[2] = {5, 6};
  sequencer.add(3000, &my_data[2]);

  my_data[3] = {7, 8};
  sequencer.add(4000, &my_data[3]);

  sequencer.set_reset_time(4000);

  sequencer.start();
}

void loop() {
  sequencer.loop();
}
