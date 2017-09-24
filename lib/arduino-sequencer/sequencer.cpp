#include "sequencer.h"

Sequencer::Sequencer() {

}

void Sequencer::start(void) {
  if (is_reset) {
    start_time = millis();
    is_reset = false;
  }
  else {
    start_time += (millis() - pause_time);
  }

  active = true;
}

void Sequencer::stop(void) {
  if (active) {
    active = false;
    pause_time = millis();
  }
}

void Sequencer::reset(void) {
  if (!loop_forever) {
    active = false;
  }
  is_reset = true;
  start_time = millis();

  for(STEP_COUNT_VARTYPE i = 0; i < step_count; i++) {
    steps[i].executed = false;
  }
  last_executed_step = 0;
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

void Sequencer::execute(STEP_COUNT_VARTYPE step) {
  callback(steps[step].data);
}

void Sequencer::clear() {
  step_count = 0;
}

uint8_t Sequencer::get_last_executed_step() {
  return last_executed_step;
}

void Sequencer::loop(void) {
  if (callback == NULL || !active) return;

  for(STEP_COUNT_VARTYPE i = 0; i < step_count; i++) {
    if (!steps[i].executed && (millis() - start_time) > steps[i].time) {
      execute(i);
      steps[i].executed = true;
      last_executed_step = i;
    }
  }

  if (loop_forever && (millis() - start_time) > reset_time) {
    reset();
    start();
  }
}
