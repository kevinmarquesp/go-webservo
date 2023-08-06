#include "PreciseServo.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * _BaseServo METHOD DEFFINITIONS
 */

/** attach the object to the pin and set the min and max deggre values */
void _BaseServo::config(u8 pin, u8 min=0, u8 max=180)
{
    this->attach(pin);
    this->write(min); // ... also, it resets to the min value on config
    _min = min;
    _max = max;
}

/** getter method - get the this->_min <u8> value */
u8 _BaseServo::getMin(void)
{
    return _min;
}

/** getter method - get the this->_max <u8> value */
u8 _BaseServo::getMax(void)
{
    return _max;
}

/** adjust the deg value to correspond to a value between the min and max value */
void _BaseServo::_adjustDegValues(u8& deg)
{
    deg = deg < _min ? _min : deg; // use the min value if it is lesser than that
    deg = deg > _max ? _max : deg; // use the max value if it is greater than that
}

/** write the position when the sleep speed is zero, and says if it's already in position */
bool _BaseServo::_isRedundant(u8 deg, u8 sleep)
{
    if (sleep < 1)
        this->write(deg);
    return deg == this->read();
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * PreciseServo METHOD DEFFINITIONS
 */ 

/** delayed write - sleep x milliseconds each deggre movement to reach the deg position */
void PreciseServo::move(u8 deg, u8 sleep=0)
{
    _adjustDegValues(deg);
    if (_isRedundant(deg, sleep))
        return; 

    u8 curr = this->read();

    // while curr != deg, it will approach the target position waiting the sleep time each deggre
    while (curr != deg)
    {
        deg > curr ? ++curr : --curr; // ... iterator

        this->write(curr);
        delay(curr == deg ? 0 : sleep); // the last sleep is irrelevant
    }
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * AdvancedServo METHOD DEFFINITIONS
 */

/** AdvancedServo - constructor to set the boolean values to false by default */
AdvancedServo::AdvancedServo(void)
{
    _movementId = 0;
    _isLocked = false;
    _isMoving = false;
    _isDone = false;
}

/** [private] update loop - it will count the milliseconds and write the deg based on that */
void AdvancedServo::_update(u8 deg, u8 sleep)
{
    // count the millis() to check if it is able to make a single movement
    if (millis() - _scheduler >= sleep)
    {
        u8 curr = this->read();
        _scheduler = millis();

        if (deg > curr)
            this->write(this->read() + 1);
        else
            this->write(this->read() - 1);
    }
}

/** [private] instructions that mark this servo object as done */
void AdvancedServo::_markAsDone(void)
{
    _isDone = true;
    _isMoving = false;
    ++_movementId;
}

/** movement core - backbone of the movement validation */
AdvancedServo* AdvancedServo::move(bool cond, u8 deg, u8 sleep)
{
    _adjustDegValues(deg);

    // if the user condition isn't true, stop, otherwise, start a new movement
    if (!cond || _isLocked)
        return this;
    else
        _isDone = false;

    // validade the values and finish the movement if it is ok to do that
    if (_isRedundant(deg, sleep))
        _markAsDone();

    // when it is ready to move but hasen't started yet, start the shceduler thing
    if (!_isMoving && !_isDone)
    {
        _scheduler = millis();
        _isMoving = true;
    }

    // when already is moving, and every thing is ok, just update the position
    else if (_isMoving && !_isDone)
        _update(deg, sleep);

    return this;
}

/** instructions to reset the values of an AdvancedServo object instance */
void AdvancedServo::reset(void)
{
    _movementId = 0;
    _isMoving = false;
    _isDone = false;
}

/** shorthand to call the real move function, that has a condition to start */
AdvancedServo* AdvancedServo::move(u8 deg, u8 sleep)
{
    return this->move(_movementId == 0, deg, sleep);
}

/** getter - return the current position ID */
u8 AdvancedServo::getId(void)
{
    return _movementId;
}

/** user id validation - check if the current motor is the expected id by the user */
bool AdvancedServo::is(u8 id)
{
    return id == _movementId;
}

/** getter - get the done value of this object instance */
bool AdvancedServo::isDone(void)
{
    return _isDone;
}

/** getter (aternative) - get the done value if the motor is in a specific movement */
bool AdvancedServo::isDone(u8 id)
{
    return _isDone && id == _movementId;
}

/** just a syntaxe helper to run anonymous functions when the movement is completed */
void AdvancedServo::whenDone(void fn(void))
{
    if (_isDone) fn();
}

/** lock the servo motor to interrupt any movement update */
void AdvancedServo::lock(void)
{
    _isLocked = true;
}

/** unlock the motor to continue to update the movement values */
void AdvancedServo::unlock(void)
{
    _isLocked = false;
}

/** toggle the lock state of the servo object */
void AdvancedServo::toggleLock(void)
{
    _isLocked = !_isLocked;
}
