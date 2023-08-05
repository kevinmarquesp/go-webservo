#ifndef PRECISESERVO_H
#define PRECISESERVO_H

#include <Arduino.h>
#include <Servo.h>

#define u8  uint8_t
#define u64 uint64_t

/** base attributes/methods that every servo class has in this library */
class _BaseServo: public Servo
{
  public:
    void config(u8 pin, u8 min=0, u8 max=180);
    u8 getMin(void);
    u8 getMax(void);

  protected:
    void _adjustDegValues(u8& deg);
    bool _isRedundant(u8 deg, u8 sleep);
    u8 _min;
    u8 _max;
};

/** delayed servo - class to handle the servo speed with delay() function */
class PreciseServo: public _BaseServo
{
  public:
    void move(u8 deg, u8 sleep=0);
};

/** millis servo - same as PreciseServo but with millis() instead of delay() */
class AdvancedServo: public _BaseServo
{
  public:
    AdvancedServo(void);

    AdvancedServo* move(bool cond, u8 deg, u8 sleep);
    AdvancedServo* move(u8 deg, u8 sleep);

    u8 getId(void);
    bool is(u8 id);
    bool isDone(void);
    bool isDone(u8 id);

    void lock(void);
    void unlock(void);
    void toggleLock(void);
    void reset(void);
    void whenDone(void fn(void));

  private:
    void _update(u8 deg, u8 sleep);
    void _markAsDone(void);

    bool _isLocked;
    bool _isMoving;
    bool _isDone;
    u8   _movementId;
    u64  _scheduler;
};

#endif
