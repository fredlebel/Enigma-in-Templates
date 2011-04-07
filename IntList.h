// Author: Frederic LeBel
// Date: March 2004
// Note: Utilities for processing lists of integers

#include "TypeList.h"

// basic IntList structure
namespace TypeList {
namespace IntList {

template <int I>
struct INT
{
    enum { value = I };
};

template <char c>
struct CHAR
{
    enum { value = c - 'A' };
};

//===========================================
// Finds the index and value of the smallest number
template <class T> struct Smallest;

template <class This, class Next>
struct Smallest< TL<This, Next> >
{
    enum { value = This::value < Smallest<Next>::value ? This::value : Smallest<Next>::value };
    enum { index = This::value < Smallest<Next>::value ? 0 : 1 + Smallest<Next>::index };
};

template <class This>
struct Smallest< TL<This, NULLTYPE> >
{
    enum { value = This::value };
    enum { index = 0 };
};

//===========================================
// Finds the index and value of the largest number
template <class T> struct Largest;

template <class This, class Next>
struct Largest< TL<This, Next> >
{
    enum { value = This::value > Largest<Next>::value ? This::value : Largest<Next>::value };
    enum { index = This::value > Largest<Next>::value ? 0 : 1 + Largest<Next>::index };
};

template <class This>
struct Largest< TL<This, NULLTYPE> >
{
    enum { value = This::value };
    enum { index = 0 };
};

//===========================================
// Sorts a list in ascending order
template <class T> struct SortAscending;

template <class This, class Next>
struct SortAscending< TL<This, Next> >
{
    typedef TL<This, Next> T;
    typedef TL< INT<Smallest<T>::value >,
        typename SortAscending< typename Remove<T, Smallest<T>::index>::Result >::Result > Result;
};

template <class This>
struct SortAscending< TL<This, NULLTYPE> >
{
    typedef TL<This, NULLTYPE> Result;
};

//===========================================
// Sorts a list in descending order
template <class T> struct SortDescending;

template <class This, class Next>
struct SortDescending< TL<This, Next> >
{
    typedef TL<This, Next> T;
    typedef TL< INT<Largest<T>::value >,
        typename SortDescending< typename Remove<T, Largest<T>::index>::Result >::Result > Result;
};

template <class This>
struct SortDescending< TL<This, NULLTYPE> >
{
    typedef TL<This, NULLTYPE> Result;
};

//===========================================
// Custom unary operations to use in ForEach
template <class T>
struct Inc
{
    typedef INT<T::value + 1> Result;
};

template <int I>
struct Abs
{
    template <bool GTZ>
    struct AbsImpl { enum { Value = I }; };

    template <>
    struct AbsImpl<false> { enum { Value = -I }; };

    enum { Value = AbsImpl<(I > 0)>::Value };
};

template <int I, int R>
struct WrapRange
{
    template <bool GTE, bool LT> struct WrapRangeImpl;

    template <> // Within the range
    struct WrapRangeImpl<false, false> { enum { Value = I }; };

    template <> // Below the range
    struct WrapRangeImpl<false, true> { enum { Value = I + R }; };

    template <> // Above or equal the range
    struct WrapRangeImpl<true, false> { enum { Value = I - R }; };

    enum { Value = WrapRangeImpl<(I >= R), (I < 0 )>::Value };
};

//===========================================
// Checks if a number is a prime

template <int I>
struct IsPrime
{
    template <int D>
    struct CheckPrimeRecursive
    {
        enum { Result = ( I % D == 0 ?
            false : CheckPrimeRecursive<D - 1>::Result ) };
    };

    template <>
    struct CheckPrimeRecursive<1>
    {
        enum { Result = true };
    };

    template <>
    struct CheckPrimeRecursive<0>
    {
        enum { Result = false };
    };

    enum { Result = CheckPrimeRecursive<(I >> 1)>::Result };
};

//===========================================
// Create a list of consecutive numbers
template <int I1, int I2>
struct MakeList
{
    typedef TL< INT<I1>, typename MakeList<I1+1, I2>::Result > Result;
};

template <int I>
struct MakeList<I, I>
{
    typedef TL<INT<I>, NULLTYPE> Result;
};

//===========================================
// Extracts all the prime numbers from a list

template <class T> struct FindPrimes;

template <class This, class Next>
struct FindPrimes< TL<This, Next> >
{
    typedef TL<This, Next> MyList;

    template <bool B, class T> struct TakePrimes;

    template <class This, class Next>
    struct TakePrimes< true, TL<This, Next> >
    {
        typedef TL< This, typename FindPrimes<Next>::Result > Result;
    };

    template <class This, class Next>
    struct TakePrimes< false, TL<This, Next> >
    {
        typedef typename FindPrimes<Next>::Result Result;
    };

    template <bool B>
    struct TakePrimes<B, NULLTYPE>
    {
        typedef NULLTYPE Result;
    };

    typedef typename TakePrimes< IsPrime<This::value>::Result, MyList >::Result Result;
};

template <>
struct FindPrimes<NULLTYPE>
{
    typedef NULLTYPE Result;
};


} // namespace IntList
} // namespace TypeList

