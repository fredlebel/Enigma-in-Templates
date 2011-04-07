// Author: Frederic LeBel
// Date: March 2004
// Note: Driver program to test "TypeList.h" and "IntList.h"

#include <stdio.h>
#include "Enigma.h"


//===========================================
//===========================================
// Handy function for printing a TL
namespace TypeList {
namespace IntList {

template <class T> struct PrintList
{
    template <class T1> struct PrintListItems;

    template <class This, class Next>
    struct PrintListItems< TL<This, Next> >
    {
        static void go()
        {
            printf( "%i, ", This::value );
            PrintListItems<Next>::go();
        }
    };

    template <class This>
    struct PrintListItems< TL< This, NULLTYPE > >
    {
        static void go()
        {
            printf( "%i", This::value );
        }
    };

    static void go()
    {
        printf( "[ " );
        PrintListItems<T>::go();
        printf( " ]\n" );
    }
};

template <>
struct PrintList< NULLTYPE >
{
    static void go()
    {
        printf( "!Empty list!\n" );
    }
};
//===== PrintList_Str =====================
template <class T> struct PrintList_Str
{
    template <class T> struct PrintListItems;

    template <char C, class Next>
    struct PrintListItems< TL< CHAR<C>, Next > >
    {
        static void go()
        {
            printf( "%c", C );
            PrintListItems<Next>::go();
        }
    };

    template <char C>
    struct PrintListItems< TL< CHAR<C>, NULLTYPE > >
    {
        static void go()
        {
            printf( "%c", C );
        }
    };

    static void go()
    {
        printf( "[ " );
        PrintListItems<T>::go();
        printf( " ]\n" );
    }
};

template <>
struct PrintList_Str< NULLTYPE >
{
    static void go()
    {
        printf( "!Empty list!\n" );
    }
};

} // namespace IntList
} // namespace TypeList

//============================================
//============================================
//=========== MAIN ===========================
//============================================
//============================================

using namespace TypeList;
using namespace TypeList::IntList;

typedef TL< INT< 4 >, // 0
        TL< INT< 6 >, // 1
        TL< INT< 9 >, // 2
        TL< INT< 5 >, // 3
        TL< INT< 7 >, // 4
        TL< INT< 3 >, // 5
        TL< INT< 1 >, // 6
        TL< INT< 2 >, // 7
        TL< INT< 2 >, // 8
        TL< INT< 4 >, // 9
        TL< INT< 8 >, // 10
        TL< INT< 0 >  // 11
        > > > > > > > > > > > > MyList;

int main(int , char** )
{

    printf( "------MyList------\n" );
    PrintList<MyList>::go();
/*
    printf( "Length = %i\n", Length<MyList>::value );
    printf( "GetAt 0 = %i\n", GetAt<MyList, 0>::Result::value );
    printf( "GetAt 7 = %i\n", GetAt<MyList, 7>::Result::value );
    printf( "Smallest at %i, value %i\n", Smallest<MyList>::index, Smallest<MyList>::value );
    printf( "Largest at %i, value %i\n", Largest<MyList>::index, Largest<MyList>::value );

    //===============================================
    printf( "\n--- Appending 99 at end of list ---\n" );
    PrintList<Append< MyList, INT<99> >::Result>::go();

    //===============================================
    printf( "\n--- Removing INT at index 3 ---\n" );
    PrintList<Remove<MyList, 3>::Result>::go();

    //===============================================
    printf( "\n--- Sorting in ascending order ---\n" );
    PrintList<SortAscending<MyList>::Result>::go();

    //===============================================
    printf( "\n--- Sorting in descending order ---\n" );
    PrintList<SortDescending<MyList>::Result>::go();

    //===============================================
    printf( "\n--- Searching for value 4 ---\n" );
    printf( "Index is %i\n", Find< MyList, INT<4> >::index );
    printf( "--- Searching for value 0 ---\n" );
    printf( "Index is %i\n", Find< MyList, INT<0> >::index );
    printf( "--- Searching for value 2 ---\n" );
    printf( "Index is %i\n", Find< MyList, INT<2> >::index );

    //===============================================
    printf( "\n--- Removing all 4s ---\n" );
    PrintList< RemoveAll< MyList, INT<4> >::Result >::go();

    //===============================================
    printf( "\n--- Removing all duplicates ---\n" );
    PrintList< RemoveDuplicates<MyList>::Result >::go();

    //===============================================
    printf( "\n--- Sorted ascending, no duplicates ---\n" );
    PrintList< SortAscending<typename RemoveDuplicates<MyList>::Result>::Result >::go();

    //===============================================
    printf( "\n--- Increment all elements by 1 ---\n" );
    PrintList< MyList >::go();
    PrintList< ForEach<MyList, Inc>::Result >::go();

    //===============================================
    printf( "\n--- All prime numbers in the list ---\n" );
    PrintList< FindPrimes<MyList>::Result >::go();

    //===============================================
    printf( "\n--- All prime numbers between 0 and 100 ---\n" );
    PrintList< FindPrimes< MakeList<0, 100>::Result >::Result >::go();
*/
    //===============================================
    printf( "\n--- Rolling left and right ---\n" );
    PrintList< RollLeft<MyList, 1>::Result >::go();
    PrintList< RollLeft<MyList, 2>::Result >::go();
    PrintList< RollRight<MyList, 1>::Result >::go();

    //=== used for testing the enigma machine =======
    // message to encrypt "thelinemustbedrawnherethisfarnofurther"
    typedef TL< CHAR< 'T' >, TL< CHAR< 'H' >, TL< CHAR< 'E' >,
            TL< CHAR< 'L' >, TL< CHAR< 'I' >, TL< CHAR< 'N' >, TL< CHAR< 'E' >,
            TL< CHAR< 'M' >, TL< CHAR< 'U' >, TL< CHAR< 'S' >, TL< CHAR< 'T' >,
            TL< CHAR< 'B' >, TL< CHAR< 'E' >,
            TL< CHAR< 'D' >, TL< CHAR< 'R' >, TL< CHAR< 'A' >, TL< CHAR< 'W' >, TL< CHAR< 'N' >,
            TL< CHAR< 'H' >, TL< CHAR< 'E' >, TL< CHAR< 'R' >, TL< CHAR< 'E' >,
            TL< CHAR< 'T' >, TL< CHAR< 'H' >, TL< CHAR< 'I' >, TL< CHAR< 'S' >,
            TL< CHAR< 'F' >, TL< CHAR< 'A' >, TL< CHAR< 'R' >,
            TL< CHAR< 'N' >, TL< CHAR< 'O' >,
            TL< CHAR< 'F' >, TL< CHAR< 'U' >, TL< CHAR< 'R' >, TL< CHAR< 'T' >, TL< CHAR< 'H' >, TL< CHAR< 'E' >, TL< CHAR< 'R' >
            > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > ClearText;

    typedef TL< CHAR< 'T' >, TL< CHAR< 'H' >, TL< CHAR< 'E' >, TL< CHAR< 'X' >,
            TL< CHAR< 'L' >, TL< CHAR< 'I' >, TL< CHAR< 'N' >, TL< CHAR< 'E' >, TL< CHAR< 'X' >,
            TL< CHAR< 'M' >, TL< CHAR< 'U' >, TL< CHAR< 'S' >, TL< CHAR< 'T' >, TL< CHAR< 'X' >,
            TL< CHAR< 'B' >, TL< CHAR< 'E' >, TL< CHAR< 'X' >,
            TL< CHAR< 'D' >, TL< CHAR< 'R' >, TL< CHAR< 'A' >, TL< CHAR< 'W' >, TL< CHAR< 'N' >, TL< CHAR< 'X' >,
            TL< CHAR< 'H' >, TL< CHAR< 'E' >, TL< CHAR< 'R' >, TL< CHAR< 'E' >, TL< CHAR< 'X' >,
            TL< CHAR< 'T' >, TL< CHAR< 'H' >, TL< CHAR< 'I' >, TL< CHAR< 'S' >, TL< CHAR< 'X' >,
            TL< CHAR< 'F' >, TL< CHAR< 'A' >, TL< CHAR< 'R' >, TL< CHAR< 'X' >,
            TL< CHAR< 'N' >, TL< CHAR< 'O' >, TL< CHAR< 'X' >,
            TL< CHAR< 'F' >, TL< CHAR< 'U' >, TL< CHAR< 'R' >, TL< CHAR< 'T' >, TL< CHAR< 'H' >, TL< CHAR< 'E' >, TL< CHAR< 'R' >
            > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > ClearTextBig;

    //-----------------------------------------
    // Real German enigma rotors as found on
    // http://www.codesandciphers.org.uk/enigma/rotorspec.htm
    //-----------------------------------------
    // INPUT       [ABCDEFGHIJKLMNOPQRSTUVWXYZ]
    // Rotor I     [EKMFLGDQVZNTOWYHXUSPAIBRCJ]
    // Rotor II    [AJDKSIRUXBLHWTMCQGZNPYFVOE]
    // Rotor III   [BDFHJLCPRTXVZNYEIWGAKMUSQO]
    // Rotor IV    [ESOVPZJAYQUIRHXLNFTGKDCMWB]
    // Rotor V     [VZBRGITYUPSDNHLXAWMJQOFECK]
    // Rotor VI    [JPGVOUMFYQBENHZRDKASXLICTW]
    // Rotor VII   [NZJHGRCXMYSWBOUFAIVLPEKQDT]
    // Rotor VIII  [FKQHTLXOCBJSPDZRAMEWNIUYGV]
    // Beta rotor  [LEYJVCNIXWPBQMDRTAKZGFUHOS]
    // Gamma rotor [FSOKANUERHMBTIYCWLQPZXVGJD]
    //-----------------------------------------
    // reflector B      (AY) (BR) (CU) (DH) (EQ) (FS) (GL) (IP) (JX) (KN) (MO) (TZ) (VW)
    //             [YRUHQSLDPXNGOKMIEBFZCWVJAT]
    // reflector C      (AF) (BV) (CP) (DJ) (EI) (GO) (HY) (KR) (LZ) (MX) (NW) (TQ) (SU)
    //             [FVPJIAOYEDRZXWGCTKUQSBNMHL]
    // reflector B Dünn (AE) (BN) (CK) (DQ) (FU) (GY) (HW) (IJ) (LO) (MP) (RX) (SZ) (TV)
    // reflector C Dünn (AR) (BD) (CO) (EJ) (FN) (GT) (HK) (IV) (LM) (PW) (QZ) (SX) (UY)
    //-----------------------------------------
    // Rotor I      at R    'Q'
    // Rotor II     at F    'E'
    // Rotor III    at W    'V'
    // Rotor IV     at K    'J'
    // Rotor V      at A    'Z'
    // Rotors VI, VII and VIII at A and at N
    //-----------------------------------------

#define MAKEROTOR( name, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z ) \
    typedef TL< CHAR< #@A >, TL< CHAR< #@B >, TL< CHAR< #@C >, TL< CHAR< #@D >, TL< CHAR< #@E >, TL< CHAR< #@F >,\
            TL< CHAR< #@G >, TL< CHAR< #@H >, TL< CHAR< #@I >, TL< CHAR< #@J >, TL< CHAR< #@K >, TL< CHAR< #@L >,\
            TL< CHAR< #@M >, TL< CHAR< #@N >, TL< CHAR< #@O >, TL< CHAR< #@P >, TL< CHAR< #@Q >, TL< CHAR< #@R >,\
            TL< CHAR< #@S >, TL< CHAR< #@T >, TL< CHAR< #@U >, TL< CHAR< #@V >, TL< CHAR< #@W >, TL< CHAR< #@X >,\
            TL< CHAR< #@Y >, TL< CHAR< #@Z >\
            > > > > > > > > > > > > > > > > > > > > > > > > > > name;

    MAKEROTOR( PlainR,      A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z );
    // real rotor 1 [EKMFLGDQVZNTOWYHXUSPAIBRCJ]
    MAKEROTOR( Rotor1,      E,K,M,F,L,G,D,Q,V,Z,N,T,O,W,Y,H,X,U,S,P,A,I,B,R,C,J );
    // real rotor 2 [AJDKSIRUXBLHWTMCQGZNPYFVOE]
    MAKEROTOR( Rotor2,      A,J,D,K,S,I,R,U,X,B,L,H,W,T,M,C,Q,G,Z,N,P,Y,F,V,O,E );
    // real rotor 3 [BDFHJLCPRTXVZNYEIWGAKMUSQO]
    MAKEROTOR( Rotor3,      B,D,F,H,J,L,C,P,R,T,X,V,Z,N,Y,E,I,W,G,A,K,M,U,S,Q,O );

    // real rotor 4 [ESOVPZJAYQUIRHXLNFTGKDCMWB]
    MAKEROTOR( Rotor4,      E,S,O,V,P,Z,J,A,Y,Q,U,I,R,H,X,L,N,F,T,G,K,D,C,M,W,B );
    // real rotor 5 [VZBRGITYUPSDNHLXAWMJQOFECK]
    MAKEROTOR( Rotor5,      V,Z,B,R,G,I,T,Y,U,P,S,D,N,H,L,X,A,W,M,J,Q,O,F,E,C,K );
    // real rotor 6 [JPGVOUMFYQBENHZRDKASXLICTW]
    MAKEROTOR( Rotor6,      J,P,G,V,O,U,M,F,Y,Q,B,E,N,H,Z,R,D,K,A,S,X,L,I,C,T,W );
    // real rotor 7 [NZJHGRCXMYSWBOUFAIVLPEKQDT]
    MAKEROTOR( Rotor7,      N,Z,J,H,G,R,C,X,M,Y,S,W,B,O,U,F,A,I,V,L,P,E,K,Q,D,T );
    // real rotor 8 [FKQHTLXOCBJSPDZRAMEWNIUYGV]
    MAKEROTOR( Rotor8,      F,K,Q,H,T,L,X,O,C,B,J,S,P,D,Z,R,A,M,E,W,N,I,U,Y,G,V );

    // real reflector b [YRUHQSLDPXNGOKMIEBFZCWVJAT]
    MAKEROTOR( ReflectorB,  Y,R,U,H,Q,S,L,D,P,X,N,G,O,K,M,I,E,B,F,Z,C,W,V,J,A,T );
    // real reflector c [FVPJIAOYEDRZXWGCTKUQSBNMHL]
    MAKEROTOR( ReflectorC,  F,V,P,J,I,A,O,Y,E,D,R,Z,X,W,G,C,T,K,U,Q,S,B,N,M,H,L );

    //===============================================
    {
        printf( "\n--- Full Enigma test ---\n" );
        printf( "ClearText  = " );
        PrintList_Str< ClearTextBig >::go();
        printf( "Rotor2     = " );
        PrintList_Str< Rotor2 >::go();
        printf( "Rotor1     = " );
        PrintList_Str< Rotor1 >::go();
        printf( "Rotor3     = " );
        PrintList_Str< Rotor3 >::go();
        printf( "ReflectorB = " );
        PrintList_Str< ReflectorB >::go();
        printf( "Rotor      = II(E) | I(Q)  | III(V)\n" );
        printf( "Rings      =   1   |   23  |   4\n" );
        printf( "Key        =  'P'  |  'U'  |  'G'\n" );
        printf( "Plugboard  = " );
        MAKEROTOR( Plugboard, A,L,C,D,Z,F,G,H,U,O,K,B,V,N,J,X,Q,W,S,T,I,M,R,P,Y,E );
        PrintList_Str< Plugboard >::go();
        printf( "Cipher     = " );
        typedef Crypto_FullEnigma<ClearTextBig, Rotor2, Rotor1, Rotor3, ReflectorB,
            1, 23, 4, 'P', 'U', 'G', 'E', 'Q', 'V', Plugboard >::Result FullCipher;
        PrintList_Str< FullCipher >::go();
        printf( "Decrypted  = " );
        typedef Crypto_FullEnigma< FullCipher, Rotor2, Rotor1, Rotor3, ReflectorB,
            1, 23, 4, 'P', 'U', 'G', 'E', 'Q', 'V', Plugboard >::Result Decrypted;
        PrintList_Str< Decrypted >::go();
        printf( "Cleaned    = " );
        PrintList_Str< typename ReplaceAll< Decrypted, CHAR<'X'>, CHAR<' '> >::Result >::go();
    }

    //====================================================================================
    {
        printf( "\n--- True German cipher test ---\n" );
        MAKEROTOR( TrueGermanCipher,  Q,K,R,Q,W,U,Q,T,Z,K,F,X,Z,O,M,J,F,O,Y,R,H,Y,Z,W,V,B );
        printf( "Encrypted   = " );
        PrintList_Str< TrueGermanCipher >::go();
        printf( "!Decrypted! = [ AIZLJWZHODZTFUWGSRZYLZRNQL ]\n" );
        printf( "Decrypted   = " );
        PrintList_Str< Crypto_FullEnigma<
            TrueGermanCipher,
            Rotor2, Rotor1, Rotor3, ReflectorB,
            1, 23, 4,
            'B', 'G', 'I',
            'E', 'Q', 'V',
            NULLTYPE>::Result >::go();
        // ==== Using the correct plug board ====
        // Plug board: (EZ) (RW) (MV) (IU) (BL) (PX) (JO)
        MAKEROTOR( PlugBoard, A,L,C,D,Z,F,G,H,U,O,K,B,V,N,J,X,Q,W,S,T,I,M,R,P,Y,E );
        printf( "Decrypted   = " );
        typedef Crypto_FullEnigma<
            TrueGermanCipher,
            Rotor2, Rotor1, Rotor3, ReflectorB,
            1, 23, 4,
            'B', 'G', 'I',
            'E', 'Q', 'V',
            PlugBoard>::Result Decrypted;
        PrintList_Str< Decrypted >::go();
    }

    //====================================================================================
    {
        printf( "\n--- Double step test ---\n" );
        typedef TL< CHAR< 'A' >, TL< CHAR< 'A' >, TL< CHAR< 'A' >, TL< CHAR< 'A' >, TL< CHAR< 'A' > > > > > > DoubleStep;
        printf( "[ EOBSM ] / \n" );
        PrintList_Str< Crypto_FullEnigma<DoubleStep, Rotor1, Rotor2, Rotor3, ReflectorB, 1, 1, 1, 'E', 'D', 'U', 'Q', 'E', 'V', NULLTYPE>::Result >::go();
    }


    //====================================================================================
    // THIS IS A SECRET MESSAGE
    {
        printf( "\n--- True cipher test ---\n" );
        MAKEROTOR( ThisMessage_P, T,H,I,S,X,I,S,X,A,X,S,E,C,R,E,T,X,M,E,S,S,A,G,E,X,X );
        printf( "Encrypted = " );
        PrintList_Str< Crypto_FullEnigma< ThisMessage_P, Rotor1, Rotor2, Rotor3, ReflectorB, 1, 1, 1, 'A', 'A', 'A', 'R', 'F', 'W', NULLTYPE>::Result >::go();
        MAKEROTOR( ThisMessage_C, O,P,G,N,T,L,V,A,L,R,J,T,Q,M,S,W,Q,D,O,T,K,F,Y,Z,I,A );
        printf( "Decrypted = " );
        PrintList_Str< typename ReplaceAll<
            Crypto_FullEnigma< ThisMessage_C, Rotor1, Rotor2, Rotor3, ReflectorB, 1, 1, 1, 'A', 'A', 'A', 'R', 'F', 'W', NULLTYPE>::Result,
            CHAR<'X'>, CHAR<' '> >::Result >::go();
    }

    //====================================================================================
    {
        // :) pragma to disable warnings about ridiculously long type names
        #pragma warning( disable:4503 )
        printf( "\n--- Full German cipher test ---\n" );
        #define MAKELINE(\
            A1, A2, A3, A4, A5, \
            B1, B2, B3, B4, B5, \
            C1, C2, C3, C4, C5, \
            D1, D2, D3, D4, D5, \
            E1, E2, E3, E4, E5, \
            F1, F2, F3, F4, F5, \
            G1, G2, G3, G4, G5, \
            H1, H2, H3, H4, H5, \
            I1, I2, I3, I4, I5, \
            J1, J2, J3, J4, J5 )\
            TL< CHAR< #@A1 >, TL< CHAR< #@A2 >, TL< CHAR< #@A3 >, TL< CHAR< #@A4 >, TL< CHAR< #@A5 >, \
            TL< CHAR< #@B1 >, TL< CHAR< #@B2 >, TL< CHAR< #@B3 >, TL< CHAR< #@B4 >, TL< CHAR< #@B5 >, \
            TL< CHAR< #@C1 >, TL< CHAR< #@C2 >, TL< CHAR< #@C3 >, TL< CHAR< #@C4 >, TL< CHAR< #@C5 >, \
            TL< CHAR< #@D1 >, TL< CHAR< #@D2 >, TL< CHAR< #@D3 >, TL< CHAR< #@D4 >, TL< CHAR< #@D5 >, \
            TL< CHAR< #@E1 >, TL< CHAR< #@E2 >, TL< CHAR< #@E3 >, TL< CHAR< #@E4 >, TL< CHAR< #@E5 >, \
            TL< CHAR< #@F1 >, TL< CHAR< #@F2 >, TL< CHAR< #@F3 >, TL< CHAR< #@F4 >, TL< CHAR< #@F5 >, \
            TL< CHAR< #@G1 >, TL< CHAR< #@G2 >, TL< CHAR< #@G3 >, TL< CHAR< #@G4 >, TL< CHAR< #@G5 >, \
            TL< CHAR< #@H1 >, TL< CHAR< #@H2 >, TL< CHAR< #@H3 >, TL< CHAR< #@H4 >, TL< CHAR< #@H5 >, \
            TL< CHAR< #@I1 >, TL< CHAR< #@I2 >, TL< CHAR< #@I3 >, TL< CHAR< #@I4 >, TL< CHAR< #@I5 >, \
            TL< CHAR< #@J1 >, TL< CHAR< #@J2 >, TL< CHAR< #@J3 >, TL< CHAR< #@J4 >, TL< CHAR< #@J5 >  \
            > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > >

        typedef MAKELINE( Q,K,R,Q,W,U,Q,T,Z,K,F,X,Z,O,M,J,F,O,Y,R,H,Y,Z,W,V,B,X,Y,S,I,W,M,M,V,W,B,L,E,B,D,M,W,U,W,B,T,V,H,M,R ) FullCipher1;
        typedef MAKELINE( F,L,K,S,D,C,C,E,X,I,Y,P,A,H,R,M,P,Z,I,O,V,B,B,R,V,L,N,H,Z,U,P,O,S,Y,E,I,P,W,J,T,U,G,Y,O,S,L,A,O,X,R ) FullCipher2;
        typedef MAKELINE( H,K,V,C,H,Q,O,S,V,D,T,R,B,P,D,J,E,U,K,S,B,B,X,H,T,T,G,V,H,G,F,I,C,A,C,V,G,U,V,O,Q,F,A,Q,W,B,K,X,Z,J ) FullCipher3;
        typedef MAKELINE( S,Q,J,F,Z,P,E,V,J,R,O,J,T,O,E,S,L,B,Q,H,Q,T,R,A,A,H,X,V,Y,A,U,H,T,N,B,G,I,B,V,C,L,B,L,X,C,Y,B,D,M,Q ) FullCipher4;
        typedef MAKELINE( R,T,V,P,Y,K,F,F,Z,X,N,D,D,P,C,C,J,B,H,Q,F,D,K,X,E,E,Y,W,P,B,Y,Q,W,D,X,D,R,D,H,N,I,G,D,X,E,U,J,J,P,V ) FullCipher5;
        typedef MAKELINE( M,H,U,K,P,C,F,H,L,L,F,E,R,A,Z,H,Z,O,H,X,D,G,B,K,O,Q,X,K,T,L,D,V,D,C,W,K,A,E,D,H,C,P,H,J,I,W,Z,M,M,T ) FullCipher6;
        typedef MAKELINE( U,A,M,Q,E,N,N,F,C,H,U,I,A,W,C,C,H,N,C,F,Y,P,W,U,A,R,B,B,N,I,E,P,H,G,D,D,K,M,D,Q,L,M,S,N,M,T,W,O,H,M ) FullCipher7;
        typedef MAKELINE( A,U,H,R,H,G,C,U,M,Q,P,K,Q,R,K,D,V,S,W,V,M,T,Y,V,N,F,F,D,D,S,K,I,I,S,X,O,N,X,Q,H,H,L,I,Y,Q,S,D,F,H,E ) FullCipher8;
        typedef MAKELINE( N,C,M,C,O,M,R,E,Z,Q,D,R,P,B,M,R,V,P,Q,T,V,R,S,W,Z,P,G,L,P,I,T,R,V,I,B,P,X,X,H,P,R,F,I,S,Z,T,P,U,E,P ) FullCipher9;
        typedef MAKELINE( L,K,O,T,T,X,N,A,Z,M,H,T,J,P,C,H,A,A,S,F,Z,L,E,F,C,E,Z,U,T,P,Y,B,A,O,S,K,P,Z,C,J,C,Y,Z,O,V,A,P,Z,Z,V ) FullCipher10;
        typedef MAKELINE( E,L,B,L,L,Z,E,V,D,C,H,R,M,I,O,Y,E,P,F,V,U,G,N,D,L,E,N,I,S,X,Y,C,H,K,S,J,U,W,V,X,U,S,B,I,T,D,E,Q,T,C ) FullCipher11;
        typedef MAKELINE( N,K,R,L,S,N,X,M,X,Y,Z,G,C,U,P,A,W,F,U,L,T,Z,Z,S,F,A,H,M,P,X,G,L,L,N,Z,R,X,Y,J,N,S,K,Y,N,Q,A,M,Z,B,U ) FullCipher12;
        typedef MAKELINE( G,F,Z,J,C,U,R,W,G,T,Q,Z,C,T,L,L,O,I,E,K,A,O,I,S,K,H,A,A,Q,F,O,P,F,U,Z,I,R,T,L,W,E,V,Y,W,M,D,N,F,R,Q ) FullCipher13;

        typedef Append< FullCipher1, FullCipher2 >::Result TempCipher1;
        typedef Append< TempCipher1, FullCipher3 >::Result TempCipher2;
        typedef Append< TempCipher2, FullCipher4 >::Result TempCipher3;
        typedef Append< TempCipher3, FullCipher5 >::Result TempCipher4;
        typedef Append< TempCipher4, FullCipher6 >::Result TempCipher5;
        typedef Append< TempCipher5, FullCipher7 >::Result TempCipher6;
        typedef Append< TempCipher6, FullCipher8 >::Result TempCipher7;
        typedef Append< TempCipher7, FullCipher9 >::Result TempCipher8;
//        typedef Append< TempCipher8, FullCipher10 >::Result TempCipher9;
//        typedef Append< TempCipher9, FullCipher11 >::Result TempCipher10;
//        typedef Append< TempCipher10, FullCipher12 >::Result TempCipher11;
//        typedef Append< TempCipher11, FullCipher13 >::Result TempCipher12;

        typedef TempCipher8 FullCipher;

        printf( "Encrypted   = " );
        PrintList_Str< FullCipher >::go();
        MAKEROTOR( PlugBoard, A,L,C,D,Z,F,G,H,U,O,K,B,V,N,J,X,Q,W,S,T,I,M,R,P,Y,E );
        printf( "Decrypted   = " );
        typedef Crypto_FullEnigma<
            FullCipher,
            Rotor2, Rotor1, Rotor3, ReflectorB,
            1, 23, 4,
            'B', 'G', 'I',
            'E', 'Q', 'V',
            PlugBoard>::Result Decrypted;
        PrintList_Str< Decrypted >::go();
    }

}


//=============================================================
// QKRQW UQTZK FXZOM JFOYR HYZWV BXYSI WMMVW BLEBD MWUWB TVHMR
// FLKSD CCEXI YPAHR MPZIO VBBRV LNHZU POSYE IPWJT UGYOS LAOXR
// HKVCH QOSVD TRBPD JEUKS BBXHT TGVHG FICAC VGUVO QFAQW BKXZJ
// SQJFZ PEVJR OJTOE SLBQH QTRAA HXVYA UHTNB GIBVC LBLXC YBDMQ
// RTVPY KFFZX NDDPC CJBHQ FDKXE EYWPB YQWDX DRDHN IGDXE UJJPV
// MHUKP CFHLL FERAZ HZOHX DGBKO QXKTL DVDCW KAEDH CPHJI WZMMT
// UAMQE NNFCH UIAWC CHNCF YPWUA RBBNI EPHGD DKMDQ LMSNM TWOHM
// AUHRH GCUMQ PKQRK DVSWV MTYVN FFDDS KIISX ONXQH HLIYQ SDFHE
// NCMCO MREZQ DRPBM RVPQT VRSWZ PGLPI TRVIB PXXHP RFISZ TPUEP
// LKOTT XNAZM HTJPC HAASF ZLEFC EZUTP YBAOS KPZCJ CYZOV APZZV
// ELBLL ZEVDC HRMIO YEPFV UGNDL ENISX YCHKS JUWVX USBIT DEQTC
// NKRLS NXMXY ZGCUP AWFUL TZZSF AHMPX GLLNZ RXYJN SKYNQ AMZBU
// GFZJC URWGT QZCTL LOIEK AOISK HAAQF OPFUZ IRTLW EVYWM DN(FRQ)
//=============================================================
// AUFBEFEHLDESOBERSTENBEFEHLSHABERSSINDIMFALLEXZXZTX
// UNWAHRSCHEINLICHENXFRANZOESISQENANGRIFFSDIEWESTBEF
// ESTIGUNGENJEDERZAHLENMAESKIGENUEBERLEGENHEITZUMTRO
// TZZUHALTENXFUEHRUNGUNDTRUPPEMUESSENVONDIESEREHRENP
// FLIQTDURQDRUNGENSEINXABSXDEMGEMAESSBEHALTEIQMIRDIE
// ERMAEQTIGUNGZURPUFGABEDERBEFESTIGUNGENODERAUQVONTE
// ILENAUSDRUECKLIQPERSOENLIQVORXABSXAENDERUNGDERANWE
// ISUNGXOKHXGENXSTXDXHXERSTEABTXNRXDREIDREIZWOEINSXD
// REIAQTGXKDOSXVOMJULIEINSNEUNDREIAQTBLEIBTVORBEHALT
// ENXDEROBERBEFEHLSHABERDESHEERESKRKRFLOTTENCHEFANOK
// MMMXXTORPEDOTREFFERACHTERAUSXSCHIFFMANOEVRIERUNFAE
// HIGXWIRKAEMPFENBISZURLETZTENGRANATEXESLEBEDERFUEHR
// ERXDERFUEHRERISTTOTXDERKAMPFGEHTWEITERXDOENITZX(XXX)
//=============================================================
// Rotors:   II   I  III
// Rings:     1  23   4
// Message:   2   7   9
// Plugboard: EZ RW MV IU BL PX JO

// 1  1  1
// 2 11  6
// B  K  F

// Rings:    26  17  22
// Message:   1   1   1
//=============================================================


//=============================================================
// http://frode.home.cern.ch/frode/crypto/tbombe.html
//=============================================================
// Teleprinter message:
//
// Fernschreiben H.F.M.No. 563
//
//
// + HRKM 13617 1807 -
// AN HEERESGRUPPENKOMMANDO 2=             06 18 24 (FRX)
// 2109 -1750 - 3 TLE - FRX FRX -          1TL -172=
//
//                         01 07 09 (In pencil; AGI)
// HCALN UQKRQ AXPWT WUQTZ KFXZO MJFOY RHYZW VBXYS IWMMV WBLEB
// DMWUW BTVHM RFLKS DCCEX IYPAH RMPZI OVBBR VLNHZ UPOSY EIPWJ
// TUGYO SLAOX RHKVC HQOSV DTRBP DJEUK SBBXH TYGVH GFICA CVGUV
// OQFAQ WBKXZ JSQJF ZPEVJ RO -
//
// 2TL - 166 -             25 02 05 (In pencil; YBE)
// ZZWTV SYBDO YDTEC DMVWQ KWJPZ OCZJW XOFWP XWGAR KLRLX TOFCD
// SZHEV INQWI NRMBS QPTCK LKCQR MTYVG UQODM EIEUT VSQFI MWORP
// RPLHG XKMCM PASOM YRORP CVICA HUEAF BZNVR VZWXX MTWOE GIEBS
// ZZQIU JAPGN FJXDK I -
//
// 3TL - 176 -             12 21 14 (In pencil; LUN)
// DHHAO FWQQM EIHBF BMHTT YFBHK YYXJK IXKDF RTSHB HLUEJ MFLAC
// ZRJDL CJZVK HFBYL GFSEW NRSGS KHLFW JKLLZ TFMWD QDQQV JUTJS
// VPRDE MUVPM BPBXX USOPG IVHFC ISGPY IYKST VQUIO CAVCW AKEQQ
// EFRVM XSLQC FPFTF SPIIU ENLUW O =
// 1 ABT GEN ST D H NR. 2050/38 G KDOS +
//
// Note:
//
//
// The starting positions, 01 07 09 in the case of part I, was not
// part of the original teleprinted message, but had been added in
// pencil on the received message form as an aid in the deciphering
// process. I have added as well the starting positions in letters,
// 01 07 09 corresponds to AGI.
//
// Decrypts:
//
// Part I:
//
//
// AUF BEFEHL DES OBERSTEN BEFEHLSHABERS SIND IM
// FALLE X Z X ZT X UNWAHRSCHEINLICHEN X FRANZOESISQEN
// ANGRIFFS DIE WESTBEFESTIGUNGEN JEDER ZAHLENMAESSIGEN
// UEBERLEGENHEIT ZUM TROTZ ZU HALTEN X
//
// Part II:
//
//
// FUEHRUNG UND TRUPPE MUESSEN VON DIESER EHRENPFLIQT
// DURQDRUNGEN SEIN X ABS X DEM GEMAESS BEHALTE IQ
// MIR DIE ERMAEQTIGUNG ZUR PUFGABE DER BEFESTIGUNGEN
// ODER AUQ VON TEILEN AUSDRUECKLIQ
//
// Part III:
//
//
// PERSOENLIQ VOR X ABS X AENDERUNG DER ANWEISUNG
// X OKH X GEN X ST X D X H X ERSTE ABT X NR X DREI DREI
// ZWO EINS X DREI AQT G X KDOS X VOM JULI EINS NEUN DREI AQT
// BLEIBT VORBEHALTEN X DER OBERBEFEHLSHABER DES HEERES
//
// Completely assembled German message:
//
//
// AUF BEFEHL DES OBERSTEN BEFEHLSHABERS SIND IM
// FALLE X Z X ZT X UNWAHRSCHEINLICHEN X FRANZOESISQEN
// ANGRIFFS DIE WESTBEFESTIGUNGEN JEDER ZAHLENMAESSIGEN
// UEBERLEGENHEIT ZUM TROTZ ZU HALTEN X
// FUEHRUNG UND TRUPPE MUESSEN VON DIESER EHRENPFLIQT
// DURQDRUNGEN SEIN X
// ABS X DEM GEMAESS BEHALTE IQ MIR DIE ERMAEQTIGUNG
// ZUR PUFGABE DER BEFESTIGUNGEN ODER AUQ VON TEILEN
// AUSDRUECKLIQ PERSOENLIQ VOR X
// ABS X AENDERUNG DER ANWEISUNG X OKH X GEN X ST
// X D X H X ERSTE ABT X NR X DREI DREI ZWO EINS
// X DREI AQT G X KDOS X VOM JULI EINS NEUN DREI AQT
// BLEIBT VORBEHALTEN X
// DER OBERBEFEHLSHABER DES HEERES
//=============================================================

//========================
// Example of an original
// Funkspruch (radio telegram)
//========================
// fuer m7g 1715 195 BUO IHO
// ENSIV TINIF MFUNK DSPXR
// KBKQA DAJZN JZUQW CPHTK
// GQQPB XXBDM NQWKJ BYMOG
// MYOPT RHCNV ASAAG EZDRC
// KGVUJ MKLIW CVVPP TSCIL
// DPLRV PNCAU IMMUD RYMGJ
// YWNVA DCUCT QGTEJ HGABO
// SEXCS RDXGO YKWKI WDIDT
// ZTEPX FGMRD YMDQJ KBOEJ
// AZLJU PAWMN WYQDG
//========================


//======================================
// Enigma Code Book
//======================================
// Day Rotors Rings Reflector Plugs
// 1   5 6 1  G G P    B       E-O F-P L-Y
// 2   5 1 3  T T X    B       E-M T-V U-Y
// 3   1 3 6  W O U    C       B-K D-Q J-O
// 4   1 5 6  Z K O    B       I-T M-P O-Q
// 5   3 1 4  F C I    C       B-T F-V Q-U
// 6   3 5 2  W J Y    C       A-S L-R O-X
// 7   4 7 2  E W F    B       A-U B-F D-H
// 8   4 5 8  Z A N    B       D-K G-O N-Q
// 9   1 3 2  Q M A    B       B-V E-I F-G
// 10  5 2 1  Z G T    C       B-O F-N W-X
// 11  2 4 5  N H M    B       A-Q E-H T-X
// 12  2 1 5  B Z Q    C       A-U F-W I-Y
// 13  3 4 1  L V D    C       D-K E-S I-L
// 14  3 2 7  D X G    B       C-T F-J X-Z
// 15  5 4 2  C S D    B       B-P G-S J-U
// 16  4 2 5  M K P    C       E-R F-Q U-W
// 17  1 4 8  Q G T    B       A-X B-M H-W
// 18  6 2 5  K F G    B       J-P O-Q X-Z
// 19  8 4 1  B U W    C       C-I F-W G-Z
// 20  4 2 1  P A Z    C       I-J K-U R-W
// 21  4 1 2  J D G    C       B-E L-N Q-R
// 22  1 3 4  G J L    B       E-F M-N T-U
// 23  5 8 3  J J J    C       B-R D-L O-Y
// 24  2 3 1  I A M    C       A-Y E-P T-V
// 25  7 5 3  P I Z    B       G-R J-N U-Z
// 26  3 1 4  Q T O    B       A-P G-R Q-V
// 27  3 5 4  I Z I    C       B-M F-J I-Q
// 28  5 7 1  M H A    B       B-W D-R I-Q
// 29  5 7 2  Y D F    B       A-G E-X W-Y
// 30  1 3 8  G Q L    C       C-G K-W L-U
// 31  1 5 6  J P P    C       C-E I-P J-R
//======================================

//    Z  Y  X  W  V  U  T  S  R  Q  P  O  N  M  L  K  J  I  H  G  F  E  D  C  B  A
//    1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
//    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z

