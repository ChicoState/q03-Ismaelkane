/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}



TEST(GuesserTest, correct_match)
{
  Guesser object("Secret");
  bool actual = object.match("Secret");
  ASSERT_TRUE( actual);
}

TEST(GuesserTest, incorrect_match)
{
  Guesser object("Secret");
  bool actual = object.match("Secre");
  ASSERT_FALSE(actual);
}



TEST(GuesserTest, three_remaining)
{
  Guesser object("Secret");
  bool actual = object.match("Secret");
   unsigned int remaining = object.remaining();
   ASSERT_EQ( remaining, 3 );
}

TEST(GuesserTest, two_remaining)
{
  Guesser object("Secret");
  bool actual = object.match("Secre");
   unsigned int remaining = object.remaining();
   ASSERT_EQ( remaining, 2 );
}


TEST(GuesserTest, one_remaining)
{
  Guesser object("Secret");
  bool actual = object.match("Secre");
  bool actual2 = object.match("Secre");
   unsigned int remaining = object.remaining();
   ASSERT_EQ( remaining, 1 );
  
}


TEST(GuesserTest, zero_remaining)
{
  Guesser object("Secret");
  bool actual = object.match("Secre");
  bool actual2 = object.match("Secre");
  bool actual3 = object.match("Secre");
   unsigned int remaining = object.remaining();
   ASSERT_EQ( remaining, 0 );
}

TEST(GuesserTest, locked_from_distance_greater_than_2)
{
  Guesser object("Secret");
  bool incorrect = object.match("Sec");
   bool correct = object.match("Secret");
    ASSERT_FALSE(correct);
}


TEST(GuesserTest, not_locked_from_distance_of_2)
{
  Guesser object("Secret");
  bool incorrect = object.match("Secr");
   bool correct = object.match("Secret");
    ASSERT_TRUE(correct);
  
}

TEST(GuesserTest, not_locked_from_distance_of_1)
{
  Guesser object("Secret");
  bool incorrect = object.match("Secre");
   bool correct = object.match("Secret");
    ASSERT_TRUE(correct);
  
}



TEST(GuesserTest, locked_from_no_remaining_guesses)
{
  Guesser object("Secret");
  bool guess1 = object.match("Secre");
  bool guess2 = object.match("Secre");
  bool guess3 = object.match("Secre");
  ASSERT_EQ(object.remaining() , 0 );
  bool correct_guess = object.match("Secret");
  ASSERT_FALSE(correct_guess);
  
}



TEST(GuesserTest, remaining_not_decreased_with_distance_greater_than_2)
{
   Guesser object("Secret"); 
  bool guess = object.match("Secretiojfojeofejo");
  ASSERT_FALSE(guess); 
  ASSERT_EQ(object.remaining(), 2);

}

TEST(GuesserTest, blank_guess)
{
  Guesser object(""); 
  ASSERT_TRUE(object.match("")); 
  ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, secret_is_truncated_to_32_charecters)
{
  Guesser object("123456789012345678901234567890123");
  ASSERT_TRUE(object.match("12345678901234567890123456789012"));
 
}

TEST(GuesserTest, remaining_not_reset_to_3_with_correct_guess)
{
   Guesser object("Secret");
  bool guess = object.match("Secre");
  	ASSERT_EQ(object.remaining(), 2);
   bool correct_guess = object.match("Secret");
 
   ASSERT_EQ(object.remaining(), 3);
}
