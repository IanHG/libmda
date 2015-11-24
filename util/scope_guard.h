#ifndef LIBMDA_UTIL_SCOPE_GUARD_H_INCLUDED
#define LIBMDA_UTIL_SCOPE_GUARD_H_INCLUDED

namespace libmda
{
namespace util
{

/**
 * @class scope_guard
 *    guard dat scope!
 **/
template<class F>
class scope_guard
{
   private:
      F m_func;
      bool m_run = true;

   public:
      /**
       *
       **/
      scope_guard(const F& f)
         : m_func(f)
      {
      }

      /**
       *
       **/
      scope_guard(F&& f)
         : m_func(std::move(f))
      {
      }
      
      /**
       *
       **/
      scope_guard(const scope_guard<F>&) = delete;

      /**
       *
       **/
      scope_guard(scope_guard<F>&& sg)
         : m_func(std::move(sg.m_func))
         , m_run(sg.m_run)
      {
      }

      /**
       *
       **/
      scope_guard<F>& operator=(const scope_guard<F>&) = delete;
      
      /**
       * deleted move assignment
       * strictly not nescesary, but gives clear intent
       **/
      scope_guard<F>& operator=(scope_guard<F>&&) = delete;

      /**
       * @function ~scope_guard
       *    destructor calls functions if m_run is set to true
       **/
      ~scope_guard()
      {
         if(m_run)
         {
            m_func();
         }
      }
      
      /**
       * @function dismiss
       *    dismiss the scope guard, i.e. do not call it at end of scope
       **/
      void dismiss()
      {
         m_run = false;
      }
};

/**
 * @function make_scope_guard
 *    make a scope guard from a function pointer / lambda / functor
 * @param f
 *    function to call at end of scope
 **/
template<class F>
scope_guard<F> make_scope_guard(F&& f)
{
   return scope_guard<F>(std::forward<F>(f));
}

// define some MACROs used later
#define CONCAT_IMPL( x, y ) x##y
#define MACRO_CONCAT( x, y ) CONCAT_IMPL( x, y )

/**
 * @def on_exit_do
 *    make function call on scope exit.
 **/
#define scope_exit_do(a) auto MACRO_CONCAT(LIBMDA_SCOPE_GUARD_, __COUNTER__) = libmda::util::make_scope_guard(a)

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_SCOPE_GUARD_H_INCLUDED */
