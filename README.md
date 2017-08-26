# arduino-sequencer
A library to make non blocking sequencing of actions easier

Library can be found at lib/arduino-sequencer
Sample (src/main.cpp):

```cpp
#include "sequencer.h"

Sequencer sequencer;

// completely arbitrary data structure to pass to callback when triggered
struct my_struct {
  uint8_t a, b;
};

// declaring array of 4 my_structs for demo
my_struct my_data[4];

// this is the function that will be called when any step gets triggered
// sample callback just prints variables to serial
void callback(void *data) {
  my_struct step_data = *((my_struct *) data);

  Serial.print("a:");
  Serial.print(step_data.a);
  Serial.print(" b:");
  Serial.println(step_data.b);
}

void setup() {
  Serial.begin(115200);

  // controls whether the sequence will restart automatically, see
  // sequencer.set_reset_time(time)
  sequencer.set_loop_forever(true);

  // controls which function gets called upon each step being triggered
  sequencer.set_callback(callback);

  my_data[0] = {1, 2};
  sequencer.add(1000, &my_data[0]);

  my_data[1] = {3, 4};
  sequencer.add(2000, &my_data[1]);

  my_data[2] = {5, 6};
  sequencer.add(3000, &my_data[2]);

  my_data[3] = {7, 8};
  sequencer.add(4000, &my_data[3]);

  // if sequence is set to loop forever with sequence.set_loop_forever, this specifies
  // a time at which the sequence should be reset
  sequencer.set_reset_time(4000);

  // start running the sequence
  sequencer.start();  
}

void loop() {
  // this function needs to be called as often as possible to ensure that steps
  // are triggered on time
  sequencer.loop();
}
```


The following functions are available:

## Sequencer::start()
Starts executing the sequence

## Sequencer::stop()
Stops executing the sequence (but does not reset it)
Call Sequencer::start() to resume

## Sequencer::reset()
Resets the sequence, call Sequencer::start() to resume

## Sequencer::loop()
This function needs to be called as often as possible in your void loop() to ensure that steps are called on time

## Sequencer::add(uint16_t *time*, void *data)
*time* - time in ms at which to pass *data to the callback function

## Sequencer::set_callback(*function*)
*function* - a function with the prototype void function(void *data)

*function* gets passed the same pointer that was given to Sequencer::add(...)

## Sequencer::set_reset_time(uint16_t *time*)
*time* - time in ms at which to reset the sequence (only applies if sequence is set to loop forever)

## Sequencer::set_loop_forever(uint8_t *yes*)
*yes* - 1 or 0 to denote sequence looping forever or not respectively
