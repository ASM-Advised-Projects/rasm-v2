/**
 * Defines the RasmTime class.
 */

#include <Poco/Clock.h>
#include <Poco/Exception.h>

/**
 * Keeps track of the amount of time that has elapsed since startup. This
 * elapsed time can be statically queried.
 */
class RasmTime
{
private:
  static Poco::Clock startup_time;

  /**
   * Don't allow instance creation.
   */
  RasmTime()
  {
  }

public:
  /**
   * Returns the elapsed milliseconds since this program was started.
   */
  static unsigned int current_time_millis()
  {
    return startup_time.elapsed();
  }

  /**
   * Returns the elapsed seconds since this program was started.
   */
  static unsigned int current_time_seconds()
  {
    return 1000 * startup_time.elapsed();
  }
};

/**
 * A simple class for clocking how long a section of code takes to execute.
 * This stopwatch is layered in the sense that multiple timers can be ran at
 * the same time. A timer is started by calling the start method. It is stopped
 * by called the stop method. If the start method is called twice, then the
 * first call to the stop method will stop the 2nd start. The 2nd call to the
 * stop method will stop the 1st start.
 *
 * Here's a more comprehensive example:
 * ...        // represents lines of other code
 * start()    // starts timer #1
 * ...
 * start()    // starts timer #2 - now 2 timers are running
 * ...
 * ...
 * stop()     // stops timer #2
 * elapsed()  // returns the time that timer #2 was running for
 * ...
 * start()    // starts timer #2
 * ...
 * stop()     // stops timer #2
 * elapsed()  // returns the time that timer #2 was just running for
 * stop()     // stops timer #1
 * elapsed()  // returns the time that timer #1 was running for
 *
 * A max of 5 timers can be running at the same time. In other words, at any
 * one time, the start method can have been called up to 5 more times than the
 * stop method. If the number of starts compared to stops become any more
 * numerous than that, or if the stop method is called more than the start
 * method, an exception is thrown.
 */
class Stopwatch
{
private:
  Poco::Clock clock;
  unsigned int start_times[5];
  int current_timer;
  unsigned int elapsed_time;

public:
  /**
   * Constructs a new stopwatch with no timers running.
   */
  Stopwatch()
  : start_times {0,0,0,0,0}
  , current_timer(-1)
  , elapsed_time(0)
  {
  }

  /**
   * Starts a new timer.
   * Throws Poco::IllegalStateException if there are already 5 timers running.
   */
  void start()
  {
    if (current_timer == 4)
    {
      throw Poco::IllegalStateException("In Stopwatch::start()\n"
      "Start cannot be called if there are already 5 timers running.");
    }
    start_times[++current_timer] = clock.elapsed();
  }

  /**
   * Stops the most recently started timer.
   * Throws Poco::IllegalStateException if there are no timers currently running.
   */
  void stop()
  {
    if (current_timer == -1)
    {
      throw Poco::IllegalStateException("In Stopwatch::stop()\n"
      "Stop cannot be called if there are no timers currently running.");
    }
    elapsed_time = clock.elapsed() - start_times[current_timer];
  }

  /**
   * Returns the time elapsed for the timer that was stopped last. In other
   * words, returns the time between the last set of start-stop calls.
   */
  unsigned int elapsed()
  {
    return elapsed_time;
  }
};