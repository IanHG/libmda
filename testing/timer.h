#ifndef LIBMDA_TESTING_TIMER_H
#define LIBMDA_TESTING_TIMER_H

#include <ctime>

namespace libmda
{
namespace testing
{

class clock_timer
{
   private:
      bool    m_running;
      clock_t m_start;
      clock_t m_last;
      clock_t m_stop;
      clock_t m_clocks_tot;
      clock_t m_clocks_rel;
      
      //
      // get current clock
      //
      void get_time(clock_t& a_clock) const
      { 
         a_clock = clock(); 
      }
      
      //
      // calculate clock difference
      //
      void accu_clock(clock_t a_beg, clock_t a_end, clock_t& a_accu) const
      { 
         a_accu = a_end - a_beg; 
      }

   public:
      clock_timer(): m_running(false)
                   , m_start(0.0) 
                   , m_last(0.0) 
                   , m_stop(0.0)
                   , m_clocks_tot(0.0)
                   , m_clocks_rel(0.0)
      { 
      }
      
      //
      // start the clock
      //
      void start()
      { 
         m_running = true;
         get_time(m_start); 
      }
      
      //
      //
      //
      void meassure()
      { 
         if(m_running) 
         {
            clock_t now = clock();
            accu_clock(m_last,now,m_clocks_rel);
            m_last = now; 
         }
      }
      
      //
      // stop the clock
      //
      void stop()
      { 
         if(m_running) 
         { 
            get_time(m_stop); 
            accu_clock(m_start,m_stop,m_clocks_tot);
            m_running = false;
         } 
      }
      
      //
      // some getters
      //
      clock_t tot_clocks() const
      { 
         return m_clocks_tot; 
      }

      clock_t rel_clocks() const
      { 
         return m_clocks_rel; 
      }

      double tot_clocks_per_sec() const 
      { 
         return double(m_clocks_tot)/CLOCKS_PER_SEC; 
      }
      
      double rel_clocks_per_sec() const
      { 
         return double(m_clocks_rel)/CLOCKS_PER_SEC; 
      }
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_TIMER_H */
