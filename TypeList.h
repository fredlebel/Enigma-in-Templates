// Author: Frederic LeBel
// Date: March 2004
// Note: Probably very similar to the implementation in Loki

namespace TypeList {

// Used to terminate a list or as an empty list
struct NULLTYPE;

template <class T, class U = NULLTYPE>
struct TL
{
    typedef T This;
    typedef U Next;
};

//===========================================
// To compare two types for equality
template <class T1, class T2>
struct IsEqual
{
    enum { Result = false };
};

template <class T>
struct IsEqual< T, T >
{
    enum { Result = true };
};

//===========================================
// Counts the number of items in a list
template <class T> struct Length;

template <class This, class Next>
struct Length< TL<This, Next> >
{
    enum { value = 1 + Length<Next>::value };
};

template <>
struct Length<NULLTYPE>
{
    enum { value = 0 };
};

//===========================================
// Random access of an item in a list
template <class T, int index> struct GetAt;

template <class This, class Next, int index>
struct GetAt< TL<This, Next>, index >
{
    typedef typename GetAt<Next, index-1>::Result Result;
};

template <class This, class Next>
struct GetAt< TL<This, Next>, 0>
{
    typedef This Result;
};

//===========================================
// Searches for the first occurrence of an item
// Doesn't compTLe if it wasn't found
template <class T, class I> struct Find;

template <class This, class Next, class I>
struct Find< TL<This, Next>, I > // Not matching
{
    enum { index = 1 + Find<Next, I>::index };
};

template <class Next, class I>
struct Find< TL<I, Next>, I > // Matching
{
    enum { index = 0 };
};

template <class I>
struct Find< NULLTYPE, I > // Not found
{
    enum { index = -1 };
};

//===========================================
// Appends an item to the end of the list
template <class T, class I> struct Append;

template <class This, class Next, class I>
struct Append< TL<This, Next>, I >
{
    typedef TL< This, typename Append<Next, I>::Result > Result;
};

template <class I> // Appending a single type
struct Append< NULLTYPE, I >
{
    typedef TL<I> Result;
};

template <class This, class Next> // Appending a TL
struct Append< NULLTYPE, TL<This, Next> >
{
    typedef TL<This, Next> Result;
};

//===========================================
// Removes an indexed item from a list
template <class T, int index> struct Remove;

template <class This, class Next, int index>
struct Remove< TL<This, Next>, index >
{
    typedef TL<This, typename Remove<Next, index-1>::Result> Result;
};

template <class This, class Next>
struct Remove< TL<This, Next>, 0 >
{
    typedef Next Result;
};

//===========================================
// Removes all item of type I
template <class T, class I> struct RemoveAll;

template <class This, class Next, class I>
struct RemoveAll< TL<This, Next>, I >
{
    typedef TL<This, typename RemoveAll<Next, I>::Result> Result;
};

template <class Next, class I>
struct RemoveAll< TL<I, Next>, I >
{
    typedef typename RemoveAll<Next, I>::Result Result;
};

template <class I>
struct RemoveAll< NULLTYPE, I >
{
    typedef NULLTYPE Result;
};

//===========================================
// Removes duplicates, doesn't need to be sorted
template <class T> struct RemoveDuplicates;

template <class This, class Next>
struct RemoveDuplicates< TL<This, Next> >
{
    typedef TL< This, typename RemoveDuplicates<typename RemoveAll<Next, This>::Result>::Result > Result;
};

template <>
struct RemoveDuplicates< NULLTYPE >
{
    typedef NULLTYPE Result;
};

//===========================================
// A for_each operation
template <class T, template <class T> class UnOp> struct ForEach;

template <class This, class Next, template <class T> class UnOp>
struct ForEach< TL<This, Next>, UnOp >
{
    typedef TL<typename UnOp<This>::Result, typename ForEach<Next, UnOp>::Result> Result;
};

template <class UnOp>
struct ForEach< NULLTYPE, UnOp >
{
    typedef NULLTYPE Result;
};

//===========================================
// Rolls a list left or right
template <class T, int I> struct RollLeft;

template <class This, class Next, int I>
struct RollLeft< TL<This, Next>, I >
{
    typedef typename RollLeft<typename Append<Next, This>::Result, I-1>::Result Result;
};

template <class This, class Next>
struct RollLeft< TL<This, Next>, 0 >
{
    typedef TL<This, Next> Result;
};


template <class T, int I>
struct RollRight
{
    typedef typename RollRight< TL<
        typename GetAt<T, Length<T>::value-1>::Result, // The last element
        typename Remove<T, Length<T>::value-1>::Result >, I-1 >::Result Result;
};

template <class T>
struct RollRight< T, 0 >
{
    typedef T Result;
};

//===========================================
// Replaces all occurences of a type
// with another type
template <class T, class OLD_T, class NEW_T> struct ReplaceAll;

template <class This, class Next, class OLD_T, class NEW_T>
struct ReplaceAll< TL<This, Next>, OLD_T, NEW_T>
{
    typedef TL<This, typename ReplaceAll<Next, OLD_T, NEW_T>::Result> Result;
};

template <class Next, class OLD_T, class NEW_T>
struct ReplaceAll< TL<OLD_T, Next>, OLD_T, NEW_T>
{
    typedef TL<NEW_T, typename ReplaceAll<Next, OLD_T, NEW_T>::Result> Result;
};

template <class OLD_T, class NEW_T>
struct ReplaceAll< NULLTYPE, OLD_T, NEW_T>
{
    typedef NULLTYPE Result;
};


} // namespace TypeList