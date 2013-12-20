#ifndef MultiDimArrayImpl_H
#define MultiDimArrayImpl_H

#include "../utility/TPN.h"

namespace libmda
{
//namespace mdaimpl
//{

//------------------    operator()     ------------------                   // Upgrade notation else OK

template<typename T, int D, typename first, typename... ints> 
struct parantesesImpl<T,D,first,ints...>
{
    static T& apply(utility::TPN<T,D> m, first ii, ints... i)
    {
        return parantesesImpl<T,D-1,ints...>::apply(m[ii],i...);
    }
};

template<typename T, typename first> 
struct parantesesImpl<T,1,first>        // May make with 0 instead?
{
    static T& apply(T* m, first i) { return m[i]; }
};

//------------------     to1DIndex     ------------------                    // Upgrade notation

template<int D, typename last, typename... ints> 
struct to1DIndex<D,last,ints...>
{
    static int apply(const int* intervals, ints... i, last ii)
    {
        return ii*intervals[D-1]+to1DIndex<D-1,ints...>::apply(intervals,i...);
    }
};

template<> struct to1DIndex<0>
{
    static int apply(const int* intervals) { return 0; }
};

//------------------     allocate      ------------------

template<typename T, int D, int i> 
struct allocateImpl
{
	static T* apply(utility::TPN<T,i+1>& p, const int* n, int size)
	{
		size *= n[D-i];
		p[0] = (utility::TPN<T,i>)malloc(size*sizeof(utility::TPN<T,i-1>));
		for(int j=0;j<size/n[D-i];j++)
			p[j] = p[0] + j*n[D-i];
		return allocateImpl<T,D,i-1>::apply(p[0],n,size);
	}
};

template<typename T, int D> 
struct allocateImpl<T,D,0>
{
	static T* apply(T*& p, const int* n, int size)
	{
		return p;
	}
};

template<typename T, int D> 
void MDA<T,D>::allocate()
{
    int size = _n[0];

	_m = (utility::TPN<T,D>)malloc(size*sizeof(utility::TPN<T,D-1>));

	_data = allocateImpl<T,D,D-1>::apply(_m,_n,size);
}

//// What is needed to allocate a 3D array with subscript range a[0..nmat][0..nrow][0..ncol]
//
//	//T*   p = (T*)malloc(nmat*nrow*ncol*sizeof(T));
//	//T**  p1 = (T**)malloc(nmat*nrow*sizeof(T*));
//	//T*** p2 = (T***)malloc(nmat*sizeof(T**));
//
//	//for(long i=0;i<nmat;i++)		// For length
//	//	p2[i] = p1 + i*nrow;
//	//for(long i=0;i<nmat*nrow;i++)	// For length
//	//	p1[i] = p  + i*ncol;

//------------------    deallocate     ------------------                   // Optimal

template<typename T, int i> 
struct deallocate
{
	static void apply(utility::TPN<T,i> a)
	{
		deallocate<T,i-1>::apply(a[0]);
		free(a);
	}
};

template<typename T> 
struct deallocate<T,1>
{
	static void apply(T* a) { free(a); }
};

//} // namespace mdaimpl
} // namespace libmda
#endif

// Put this in a hidden namespace
// Comment how works - maybe use 3D array as example?
// Wikepedia suggest using && to ensure perfect forwarding

// May use get_argument<0> and remove_argument<0> to get head & tail in operator() & to1DIndex if can make remove_argument<0>
// Still need stop struct & less easy to optimize so should one?
