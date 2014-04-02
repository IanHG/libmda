#ifndef LIBMDA_BENCHMARK_ACCESS_H
#define LIBMDA_BENCHMARK_ACCESS_H

#include <iostream>
using std::cout;
using std::endl;

#include "../../meta/get_type_n_.h"
using libmda::meta::get_type_n_;
#include "../../testing/testing_interface.h"
#include "../../util/for_loop_expand.h"

namespace libmda
{
namespace benchmark
{

//template<typename... T>
//typename get_type_n_<0,T...>::type sum(T... t);

/*template<typename T, typename... U>
typename get_type_n_<0,T,U...>::type sum(T t, U... u)
{ return t + sum(u...); }

template<typename T>
typename get_type_n_<0,T>::type sum(T t)
{ return t; }*/

struct oper_at
{
   template<class V, typename... ints>
   static void apply(V& v, ints... i) { v.at(i...) = 1.0; }
};

struct oper_att
{
   template<class V, typename... ints>
   static void apply(V& v, ints... i) { v.att(i...) = 1.0; }
};

struct oper_parenteses
{
   template<class V, typename... ints>
   static void apply(V& v, ints... i) { v(i...) = 1.0; }
};
   
#ifndef SIZE
#define SIZE 10
#endif /* SIZE */

template<class tensor_type, int size, int N>
struct create_tensor
{ 
   template<typename... ints>
   static tensor_type create(ints... i)
   { return create_tensor<tensor_type,size,N-1>::create(size,i...); }
};

template<class tensor_type, int size>
struct create_tensor<tensor_type,size,0>
{
   template<typename... ints>
   static tensor_type create(ints... i)
   { return tensor_type(i...); }
};

template<class tensor_type>
struct manage_tensor: virtual public unit_test
{
   tensor_type m_tens;
   manage_tensor(): m_tens(create_tensor<tensor_type,SIZE,tensor_type::num_dim>::create()) { };
   void setup() { }
   //{ swap(m_tens,create_tensor<tensor_type,SIZE,tensor_type::num_dim>::create()); }
   void teardown() { }
   //{ m_tens.tensor_type::~tensor_type(); }
};

template<class tensor_type, class access_oper>
struct access_test: virtual public unit_test,
                    virtual public manage_tensor<tensor_type> 
{
   void do_test() throw(test_failed)
   { for_loop_expand<access_oper>::apply(manage_tensor<tensor_type>::m_tens); }
};

template<class tensor_type>
struct vec_access_test: virtual public unit_test,
                        virtual public manage_tensor<tensor_type> 
{
   using manage_tensor<tensor_type>::m_tens;
   void do_test() throw(test_failed)
   { for(int i=0; i<m_tens.size(); ++i) m_tens.vec_at(i) = 1.0; }
};

} // namespace benchmark
} // namespace libmda



#endif /* LIBMDA_BENCHMARK_ACCESS_H */
