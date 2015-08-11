#ifndef LIBMDA_BINARY_EXPRESSION_H_INCLUDED
#define LIBMDA_BINARY_EXPRESSION_H_INCLUDED

template<class L, class R, class F>
struct binary_expression
{
   private:
      const L& l_;
      const R& r_;
      const F& f_;
      
      binary_expression() = delete;
      binary_expression<L,R,F>& operator=(const binary_expression<L,R,F>&) = delete;

   public:
      binary_expression(const L& l, const R& r, const F& f): l_(l), r_(r), f_(f)
      {
      }

      ~binary_expression() {};
      
      auto operator()() const
         -> decltype( f_(l_,r_) )
      {
         return f_(l_,r_);
      }
};

#endif /* LIBMDA_BINARY_EXPRESSION_H_INCLUDED */
