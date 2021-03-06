#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
  #include <stdio.h>
  #include <unistd.h>
  #include "CapteurLuminance.h"
}

#define DELTA 0.01

TEST_GROUP(Embedded)
{
  void setup()
  {
  }

  void teardown() 
  {
  }
};

TEST(Embedded, CountTens1)
{
  DOUBLES_EQUAL(0.906, BitToTens(1035), DELTA);
}

TEST(Embedded, CountTens2)
{
	DOUBLES_EQUAL(2, BitToTens(2276), DELTA);
}

TEST(Embedded, CountIntens1) 
{
	DOUBLES_EQUAL(486.1111, TensToIntens(3.5), DELTA);
}

TEST(Embedded, CountIntens2) 
{
	DOUBLES_EQUAL(13.89, TensToIntens(0.1), DELTA);
}

TEST(Embedded, CountLx1)
{
	DOUBLES_EQUAL(20, IntensToLx(10), DELTA);
}

TEST(Embedded, CountLx2)
{
	DOUBLES_EQUAL(200, IntensToLx(100), DELTA);
}


int ConvertADC_NuitTotale(char* filename, int access, int permission) 
{
  return 0;
}


TEST(Embedded, Luminance_Nuit_Total) 
{
// programme le mock de read dans un cas de nuit totale: retourne 0

  initializeLuminance(&ConvertADC_NuitTotale);
  DOUBLES_EQUAL(0, Luminance(), DELTA);
}

int ConvertADC_PleinJour(char* filename, int access, int permission)
{
  return 4095;
}

TEST(Embedded, Luminance_Jour_Total) 
{
// programme le mock de read dans un cas de jour totale: retourne 1000

  initializeLuminance(&ConvertADC_PleinJour);
  DOUBLES_EQUAL(999.8, Luminance(), 0.1);
}