#include "sequencer.h"

Sequencer::Sequencer() {

}

void Sequencer::start(void) {
  if (is_reset) {
    start_time = millis();
    is_reset = false;
  }

  active = true;
}

void Sequencer::stop(void) {
  active = false;
}

void Sequencer::reset(void) {
  is_reset = true;

  for(STEP_COUNT_VARTYPE i = 0; i < step_count; i++) {
    steps[i].executed = false;
  }
}

void Sequencer::set_loop_forever(uint8_t yes) {
  loop_forever = yes;
}

void Sequencer::set_reset_time(TIME_VARTYPE _reset_time) {
  reset_time = _reset_time;
}

void Sequencer::add(TIME_VARTYPE time, void *data) {
  steps[step_count].time = time;
  steps[step_count].data = data;

  step_count ++;
}

void Sequencer::set_callback(void (*_callback)(void *data)) {
  callback = _callback;
}

void Sequencer::loop(void) {
  if (callback == NULL || !active) return;

  for(STEP_COUNT_VARTYPE i = 0; i < step_count; i++) {
    if (!steps[i].executed && (millis() - start_time) > steps[i].time) {
      callback(steps[i].data);
      steps[i].executed = true;
    }
  }

  if (loop_forever && (millis() - start_time) > reset_time) {
    reset();
    start();
  }
}
