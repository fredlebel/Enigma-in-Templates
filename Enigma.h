#include "IntList.h"

namespace TypeList {
namespace IntList {

//===========================================
// Getting crazier, the German Enigma crypto machine
// A restriction, all rotors must be the same length
// There are three versions of the Enigma machine below,
// the micro, mini and full Enigma.

// --- Starting with the micro-Enigma --- //

template <bool ENC, class T, class R> struct Crypto_MicroEnigma;

template <class This, class Next, class R>
struct Crypto_MicroEnigma< true, TL<This, Next>, R >
{
    typedef TL<This, Next> T; // Clear text
    typedef TL< typename GetAt<R, This::value>::Result,
        typename Crypto_MicroEnigma< true, Next,
            typename RollRight<R,1>::Result >::Result > Result;
};

template <class This, class Next, class R>
struct Crypto_MicroEnigma< false, TL<This, Next>, R >
{
    typedef TL<This, Next> T; // Clear text
    typedef TL< CHAR<Find<R, This>::index+'A'>,
        typename Crypto_MicroEnigma< false, Next,
            typename RollRight<R,1>::Result >::Result > Result;
};

template <bool ENC, class R>
struct Crypto_MicroEnigma< ENC, NULLTYPE, R >
{
    typedef NULLTYPE Result;
};

// --- Next is the the mini-Enigma --- //

template <bool ENC, class T, class R1, class R2>
struct Crypto_MiniEnigma
{
    template <bool ENC, class I, class R1, class R2>
    struct ComputeVal
    {
        enum
        {
            Val1 = GetAt<R1, I::value>::Result::value,
            Val2 = GetAt<R2, Val1>::Result::value,
        };
        typedef CHAR<Val2+'A'> Result;
    };

    template <class I, class R1, class R2>
    struct ComputeVal< false, I, R1, R2 >
    {
        enum
        {
            Val1 = Find< R2, I >::index,
            Val2 = Find< R1, CHAR<Val1+'A'> >::index
        };
        typedef CHAR<Val2+'A'> Result;
    };

    template <class T, class R1, class R2, int I> struct DoCrypt;

    template <class This, class Next, class R1, class R2, int I>
    struct DoCrypt< TL<This, Next>, R1, R2, I >
    {
        typedef typename ComputeVal<ENC, This, R1, R2>::Result Val;
        typedef typename RollRight<R1,1>::Result NewR1;
        typedef TL< Val,
            typename DoCrypt< Next, NewR1, R2, I-1 >::Result > Result;
    };

    template <class This, class Next, class R1, class R2>
    struct DoCrypt< TL<This, Next>, R1, R2, 1 >
    {
        typedef typename ComputeVal<ENC, This, R1, R2>::Result Val;
        typedef typename RollRight<R1,1>::Result NewR1;
        typedef typename RollRight<R2,1>::Result NewR2;
        typedef TL< Val,
            typename DoCrypt< Next, NewR1, NewR2, Length<NewR1>::value >::Result > Result;
    };

    template <class R1, class R2, int I>
    struct DoCrypt< NULLTYPE, R1, R2, I >
    {
        typedef NULLTYPE Result;
    };

    typedef typename DoCrypt< T, R1, R2, Length<R1>::value >::Result Result;
};
/*
//======================
namespace aux
{
# pragma warning(push, 3)
// we only want one warning from MSVC, so turn off the other one
# pragma warning(disable: 4307)
}

template <class T>
struct print
  :  mpl::identity<T>
{
    enum { n = sizeof(T) + -1 };
};
*/
//======================

template <bool ENC, class R1, class R2>
struct Crypto_MiniEnigma< ENC, NULLTYPE, R1, R2 >
{
    typedef NULLTYPE Result;
};

// --- And now, the full-Enigma --- //

// class T      : cipher or plaintext
// class OR1    : original rotor 1
// class OR2    : original rotor 2
// class OR3    : original rotor 3
// class RF     : reflector
// int OFF1     : starting offset of rotor 1
// int OFF2     : starting offset of rotor 2
// int OFF3     : starting offset of rotor 3
// char K1      : Stepping character for Rotor 1
// char K2      : Stepping character for Rotor 2
// char K3      : Stepping character for Rotor 3
// char ST1     : stepping char for rotor 1
// char ST2     : stepping char for rotor 2
// char ST3     : stepping char for rotor 3
// class PLUGS  : Plug board
template <class T,
    class OR1, class OR2, class OR3, class RF,
    int  OFF1, int  OFF2, int  OFF3,
    char   K1, char   K2, char   K3,
    char  ST1, char  ST2, char  ST3,
    class PLUGS>
struct Crypto_FullEnigma
{
    // The actual stepping locations compensated with the
    // offsets of each rotor.
    enum {
        STEP1 = WrapRange<(ST1 - 'A') - (OFF1-1) , 26>::Value,
        STEP2 = WrapRange<(ST2 - 'A') - (OFF2-1) , 26>::Value,
        STEP3 = WrapRange<(ST3 - 'A') - (OFF3-1) , 26>::Value };


    // Encryption/Decryption path
    template <class I, int N1, int N2, int N3>
    struct ComputeVal
    {
        enum
        {
            // Get the value once plugged
            Plug1 = Find< PLUGS, CHAR<I::value+'A'> >::index,
            Plug2 = ( Plug1 >= 0 ? Plug1 : I::value ),
            // Go through the rotors from right to left
            Val1 = WrapRange< GetAt<OR3, (Plug2 + N3) % 26>::Result::value - N3, 26 >::Value,
            Val2 = WrapRange< GetAt<OR2,  (Val1 + N2) % 26>::Result::value - N2, 26 >::Value,
            Val3 = WrapRange< GetAt<OR1,  (Val2 + N1) % 26>::Result::value - N1, 26 >::Value,
            // Reflector
            Val4 = GetAt<RF, Val3>::Result::value,
            // Go back through the rotors from left to right
            Val5 = WrapRange< Find< OR1, CHAR<(Val4 + N1 ) % 26 + 'A'> >::index - N1, 26 >::Value,
            Val6 = WrapRange< Find< OR2, CHAR<(Val5 + N2 ) % 26 + 'A'> >::index - N2, 26 >::Value,
            Val7 = WrapRange< Find< OR3, CHAR<(Val6 + N3 ) % 26 + 'A'> >::index - N3, 26 >::Value,
            // Finally, go though the plugboard again
            Plug3 = Find< PLUGS, CHAR<Val7+'A'> >::index,
            Plug4 = ( Plug3 >= 0 ? Plug3 : Val7 ),
        };
        typedef CHAR<Plug4+'A'> Result;
    };

    // DoCrypt< list of items to enc/dec, rotor1, rotor2, rotor3
    template <class T, int N1, int N2, int N3> struct DoCrypt;

    // Path that rolls the first rotor
    template <class This, class Next, int N1, int N2, int N3>
    struct DoCrypt< TL<This, Next>, N1, N2, N3 >
    {
        enum { NewN3 = ( N3 + 1 ) % 26 };
        enum { NewN2 = ( (N3 == (STEP3)) || (N2 == (STEP2)) ? ((N2 + 1) % 26) : N2 ) };
        // ??? Possible bug in rotor 1 below ???
        enum { NewN1 = ( (N2 == (STEP2)) || (N1 == (STEP1)) ? ((N1 + 1) % 26) : N1 ) };
        typedef typename ComputeVal<This, NewN1, NewN2, NewN3>::Result Val;
        typedef TL< Val, typename DoCrypt< Next, NewN1, NewN2, NewN3 >::Result > Result;
    };
    template <int N1, int N2, int N3>
    struct DoCrypt< NULLTYPE, N1, N2, N3 >
    {
        typedef NULLTYPE Result;
    };

    typedef typename DoCrypt< T,
        WrapRange< (K1-'A'+1)-(OFF1), 26 >::Value,
        WrapRange< (K2-'A'+1)-(OFF2), 26 >::Value,
        WrapRange< (K3-'A'+1)-(OFF3), 26 >::Value
            >::Result Result;
};

// TODO: An enigma machine that takes a random number of rotors
// ENC -> true for encryption, false to decrypt
// T -> message to encrypt (list of CHAR)
// RL -> list of rotors (list of CHAR)
// RF -> reflector (list of CHAR)
/*
template <bool ENC, class T, class RL, class RF>
struct Crypto_FinalEnigma
{
    enum { RotorCount = Length<RL>::value };

    typedef typename DoCrypt< T, RL >::Result Result;
};

template <bool ENC, class T, class RL, class RF>
struct Crypto_FinalEnigma< ENC, NULLTYPE, RL, RF >
{
    typedef NULLTYPE Result;
};
*/

} // namespace IntList
} // namespace TypeList
