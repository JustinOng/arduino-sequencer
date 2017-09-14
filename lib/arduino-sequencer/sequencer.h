#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <Arduino.h>

#define TIME_VARTYPE uint16_t

#define STEP_COUNT_VARTYPE uint8_t
#define STEP_COUNT_MAX 100

struct Sequencer_Step {
  TIME_VARTYPE time;
  uint8_t executed = false;
  void *data;
};

class Sequencer {
  public:
    Sequencer(void);
    void start(void);
    void stop(void);
    void reset(void);

    void loop(void);

    void set_callback(void (*_callback)(void *data));
    void set_loop_forever(uint8_t yes);
    void set_reset_time(TIME_VARTYPE time);

    void add(TIME_VARTYPE time, void *data);
    void execute(STEP_COUNT_VARTYPE step);
  private:
    uint32_t start_time = 0;
    uint32_t pause_time = 0;

    uint8_t active = false;
    // if reset is true, next call to start() will update start_time and step
    uint8_t is_reset = true;
    uint8_t loop_forever = false;

    TIME_VARTYPE reset_time = -1;

    void (*callback)(void *data) = NULL;

    STEP_COUNT_VARTYPE step_count = 0;
    Sequencer_Step steps[STEP_COUNT_MAX];
};

#endif
