#include <iostream>
#include "../../arrays/MultiDimArray.h"
using libmda::MDA;
//using namespace std;

typedef MDA<double,2> d_tens2d;
typedef MDA<double,3> d_tens3d;
typedef MDA<double,4> d_tens4d;
typedef MDA<double,5> d_tens5d;
typedef MDA<double,6> d_tens6d;
typedef MDA<double,7> d_tens7d;
typedef MDA<double,8> d_tens8d;
typedef MDA<double,9> d_tens9d;

#include "../../arrays/Mda.h"
using libmda::arrays::mda_impl::Mda;

//#define SIZE 16
#define SIZE 5

#include "access_test.h"
using namespace libmda::benchmark;
#include "../../testing/testing_interface.h"

int main()
{
    test_suite suite;
    
    //suite.add_performance_test<200000,access_test<d_tens2d,oper_at> >("oper at 2d tens");
    //suite.add_performance_test<200000,access_test<d_tens3d,oper_at> >("oper at 3d tens");
    //suite.add_performance_test<200000,access_test<d_tens4d,oper_at> >("oper at 4d tens");
    //suite.add_performance_test<200000,access_test<d_tens5d,oper_at> >("oper at 5d tens");
    //suite.add_performance_test<200000,access_test<d_tens6d,oper_at> >("oper at 6d tens");
    //suite.add_performance_test<200000,access_test<d_tens7d,oper_at> >("oper at 7d tens");
    //suite.add_performance_test<200000,access_test<d_tens8d,oper_at> >("oper at 8d tens");
    //suite.add_performance_test<200000,access_test<d_tens9d,oper_at> >("oper at 9d tens");
    //
    //suite.add_performance_test<200000,access_test<d_tens2d,oper_parenteses> >("oper parenteses 2d tens");
    //suite.add_performance_test<200000,access_test<d_tens3d,oper_parenteses> >("oper parenteses 3d tens");
    //suite.add_performance_test<200000,access_test<d_tens4d,oper_parenteses> >("oper parenteses 4d tens");
    //suite.add_performance_test<200000,access_test<d_tens5d,oper_parenteses> >("oper parenteses 5d tens");
    //
    //suite.add_performance_test<200000,vec_access_test<d_tens2d> >("vec access 2d tens");
    //suite.add_performance_test<200000,vec_access_test<d_tens3d> >("vec access 3d tens");
    //suite.add_performance_test<200000,vec_access_test<d_tens4d> >("vec access 4d tens");
    //suite.add_performance_test<200000,vec_access_test<d_tens5d> >("vec access 5d tens");
    //
    //suite.add_performance_test<200000,access_test<d_tens2d,oper_att> >("oper att 2d tens");
    //suite.add_performance_test<200000,access_test<d_tens3d,oper_att> >("oper att 3d tens");
    //suite.add_performance_test<200000,access_test<d_tens4d,oper_att> >("oper att 4d tens");
    //suite.add_performance_test<200000,access_test<d_tens5d,oper_att> >("oper att 5d tens");
    //suite.add_performance_test<200000,access_test<d_tens6d,oper_att> >("oper att 6d tens");
    //suite.add_performance_test<200000,access_test<d_tens7d,oper_att> >("oper att 7d tens");
    //suite.add_performance_test<200000,access_test<d_tens8d,oper_att> >("oper att 8d tens");
    //suite.add_performance_test<200000,access_test<d_tens9d,oper_att> >("oper att 9d tens");
    
    //suite.add_performance_test<200000,access_test<Mda<2>,oper_at> >("Mda 2d tens");
    //suite.add_performance_test<200000,access_test<Mda<3>,oper_at> >("Mda 3d tens");
    //suite.add_performance_test<200000,access_test<Mda<4>,oper_at> >("Mda 4d tens");
    //suite.add_performance_test<200000,access_test<Mda<5>,oper_at> >("Mda 5d tens");
    //suite.add_performance_test<200000,access_test<Mda<6>,oper_at> >("Mda 6d tens");
    suite.add_performance_test<200000,access_test<Mda<7>,oper_at> >("Mda 7d tens");
    //suite.add_performance_test<200000,access_test<Mda<8>,oper_at> >("Mda 8d tens");
    //suite.add_performance_test<200000,access_test<Mda<9>,oper_at> >("Mda 9d tens");
    
    suite.do_tests();
   
    ///// MDA access timing /////
    //clock_t start, end;
    //int N = 16;
    //MDA<double,3> a(N,N,N); both work now ;)
    /*MDA<double,3> a(16,16,16); 
    start = clock();
    for(int count=0;count<200000;++count)
        for(int i=0;i<a.dim<0>();++i)                    // First two same and little slower than att below - last much slower
            for(int j=0;j<a.dim<1>();++j)
                for(int k=0;k<a.dim<2>();++k)
                    a(i,j,k)=count;
                    //a[i][j][k]=count;
                    //a.at(i,j,k)=count;
    end = clock();
    cout << end - start << '\n';

    int NN = N*N*N;
    start = clock();
    for(int count=0;count<200000;++count)
        for(int i=0;i<NN;i++)
            a.att(i) = count;
    end = clock();
    cout << end - start << '\n'; */

  return 0;
}
