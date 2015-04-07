/*
*   Mock_Test_Servomotor.cpp
*
*   Fichier de test pour la partie servomoteur - Avec mock
*
*   Auteur : Rémy Kaloustian
*
*   Dernière modification : 3/04/2015
*/

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


extern "C"
{
  #include <stdio.h>
  #include <unistd.h>
  #include "ServoMoteur.h"
}


TEST_GROUP(Embedded)
{
    void setup()
    {
    
    }
    void teardown()
    {
    }
};

TEST(Embedded, string_close)
{
  CHECK_EQUAL(0,StrPostoInt("close"));
}

TEST(Embedded, string_full)
{
  CHECK_EQUAL(180,StrPostoInt("full"));
}



TEST(Embedded, string_half)
{
  CHECK_EQUAL(90,StrPostoInt("half"));
}


TEST(Embedded, string_quarter)
{
  CHECK_EQUAL(45,StrPostoInt("quarter"));
}


TEST(Embedded, string_three_quarts)
{
  CHECK_EQUAL(135,StrPostoInt("three quarts"));
}


TEST(Embedded, string_parameter_valid)
{
  CHECK_EQUAL(-1,StrPostoInt("haacqlf"));
}


