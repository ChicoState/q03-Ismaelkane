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
   ASSERT_EQ( remaining, 3 ); // should be 3 because guess is correct
}

TEST(GuesserTest, two_remaining)
{
  Guesser object("Secret");
  bool actual = object.match("Secre"); //m_remaing decreased by 1
   unsigned int remaining = object.remaining();
   ASSERT_EQ( remaining, 2 ); //3-1=2
}


TEST(GuesserTest, one_remaining)
{
  Guesser object("Secret");
  bool actual = object.match("Secre"); //m_remaing decreased by 1
  bool actual2 = object.match("Secre");//m_remaing decreased by 1
   unsigned int remaining = object.remaining();
   ASSERT_EQ( remaining, 1 ); //3-2=1
  
}


TEST(GuesserTest, zero_remaining)
{
  Guesser object("Secret");
  bool actual = object.match("Secre"); //m_remaing decreased by 1
  bool actual2 = object.match("Secre"); //m_remaing decreased by 1
  bool actual3 = object.match("Secre");//m_remaing decreased by 1
   unsigned int remaining = object.remaining();
   ASSERT_EQ( remaining, 0 ); //3-3=0
}

TEST(GuesserTest, locked_from_distance_greater_than_2)
{
  Guesser object("Secret");
  bool incorrect = object.match("Sec"); //distance = 3 
   bool correct_guess = object.match("Secret");
    ASSERT_FALSE(correct_guess);//shoudld return false because distance is greater than 2 before correct guess is made
}


TEST(GuesserTest, not_locked_from_distance_of_2)
{
  Guesser object("Secret");
  bool incorrect = object.match("Secr");  //distance = 2
   bool correct_guess = object.match("Secret");
    ASSERT_TRUE(correct_guess);// should be true because distance is not greater than 2 allowing to check password, which is the correct guess
  
}

TEST(GuesserTest, not_locked_from_distance_of_1)
{
  Guesser object("Secret");
  bool incorrect = object.match("Secre"); //distance =1
   bool correct = object.match("Secret");
    ASSERT_TRUE(correct);// should be true because distance is not greater than 2 allowing to check password, which is the correct guess
  
}



TEST(GuesserTest, locked_from_no_remaining_guesses)
{
  Guesser object("Secret");
  bool guess1 = object.match("Secre"); //remaining =2
  bool guess2 = object.match("Secre"); //remaining =1
  bool guess3 = object.match("Secre");//remaining =0
  bool correct_guess = object.match("Secret");
  ASSERT_FALSE(correct_guess); //should be false because your're locked out from no remaining guesses
  
}



TEST(GuesserTest, remaining_not_decreased_with_distance_greater_than_2)
{
   Guesser object("Secret"); 
  bool guess = object.match("Secretiojfojeofejo"); //distance =12
  ASSERT_EQ(object.remaining(), 2); //should return 2 because guess was incorrect meaning remaing should be decreased

}

TEST(GuesserTest, blank_guess)
{
  Guesser object(""); 
  bool guess=object.match(""); 
  ASSERT_EQ(object.remaining(), 3);//remaining is still 3 as correct guess has been made
}

TEST(GuesserTest, secret_is_truncated_to_32_charecters)
{
  Guesser object("123456789012345678901234567890123");
  ASSERT_TRUE(object.match("12345678901234567890123456789012"));//should be what user inputed not including the last charecter
 
}

TEST(GuesserTest, remaining_not_reset_to_3_with_correct_guess)
{
   Guesser object("Secret");
  bool guess = object.match("Secre");//remaining =2
   bool correct_guess = object.match("Secret");//correct guess
   ASSERT_EQ(object.remaining(), 3);//remaining should be reset to 3 because of correct guess
}
