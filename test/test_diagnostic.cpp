// gtest
#include <gtest/gtest.h>

//romea
#include "romea_common/diagnostic/DiagnosticEqualTo.hpp"
#include "romea_common/diagnostic/DiagnosticGreaterThan.hpp"
#include "romea_common/diagnostic/DiagnosticLowerThan.hpp"
#include "romea_common/diagnostic/DiagnosticReliability.hpp"
#include "romea_common/diagnostic/DiagnosticRate.hpp"


//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, compare)
{
  EXPECT_TRUE(romea::DiagnosticStatus::OK<romea::DiagnosticStatus::WARN);
  EXPECT_TRUE(romea::DiagnosticStatus::WARN<romea::DiagnosticStatus::ERROR);
  EXPECT_TRUE(romea::DiagnosticStatus::ERROR<romea::DiagnosticStatus::STALE);
}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, getWorse)
{
  EXPECT_EQ(worse(romea::DiagnosticStatus::OK,
                  romea::DiagnosticStatus::OK),romea::DiagnosticStatus::OK);

  EXPECT_EQ(worse(romea::DiagnosticStatus::OK,
                  romea::DiagnosticStatus::WARN),romea::DiagnosticStatus::WARN);

}



//-----------------------------------------------------------------------------
TEST(TestReport, setReportInfosValues)
{
  romea::DiagnosticReport report;

  romea::setReportInfo(report,"foo",1.2);
  romea::setReportInfo(report,"bar","hello");
  romea::setReportInfo(report,"baz",-2);

  EXPECT_STREQ(report.info.at("foo").c_str(),"1.2");
  EXPECT_STREQ(report.info.at("bar").c_str(),"hello");
  EXPECT_STREQ(report.info.at("baz").c_str(),"-2");
}

//-----------------------------------------------------------------------------
TEST(TestReport, setReportOtionalInfosValues)
{
  romea::DiagnosticReport report;
  boost::optional<double> foo(7.77);
  boost::optional<std::string> bar;

  romea::setReportInfo(report,"foo",foo);
  romea::setReportInfo(report,"bar",bar);

  EXPECT_STREQ(report.info.at("foo").c_str(),"7.77");
  EXPECT_STREQ(report.info.at("bar").c_str(),"");
}

class TestEqualTo : public ::testing::Test
{
 public:

  TestEqualTo():
    diagnostic("foo",0.8,0.1)
  {

  }

  romea::DiagnosticEqualTo2<double> diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestEqualTo, compareWithLowerValue)
{
  EXPECT_EQ(diagnostic.evaluate(0.5),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.5");
}

//-----------------------------------------------------------------------------
TEST_F(TestEqualTo, compareWithEqualValue)
{
  EXPECT_EQ(diagnostic.evaluate(0.85),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is OK.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.85");
}

//-----------------------------------------------------------------------------
TEST_F(TestEqualTo, compareWithHigherValue)
{
  EXPECT_EQ(diagnostic.evaluate(1.11),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is too high.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"1.11");
}


class TestGreaterThan : public ::testing::Test
{
 public:

  TestGreaterThan():
    diagnostic("foo",-0.3,0.1)
  {

  }

  romea::DiagnosticGreaterThan2<double> diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestGreaterThan, compareWithLowerValue)
{
  EXPECT_EQ(diagnostic.evaluate(-0.5),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"-0.5");
}

//-----------------------------------------------------------------------------
TEST_F(TestGreaterThan, compareWithHigherValue)
{
  EXPECT_EQ(diagnostic.evaluate(-0.25),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is OK.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"-0.25");
}

class TestLowerThan : public ::testing::Test
{
 public:

  TestLowerThan():
    diagnostic("foo",1.45,0.1)
  {

  }

  romea::DiagnosticLowerThan2<double> diagnostic;
};


//-----------------------------------------------------------------------------
TEST_F(TestLowerThan, compareWithLowerValue)
{
  EXPECT_EQ(diagnostic.evaluate(1.5),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is OK.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"1.5");
}

//-----------------------------------------------------------------------------
TEST_F(TestLowerThan, compareWithHigherValue)
{
  EXPECT_EQ(diagnostic.evaluate(1.7),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is too high.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"1.7");
}

class TestReliability : public ::testing::Test
{
 public:

  TestReliability():
    diagnostic("foo",0.7,0.9)
  {

  }

  romea::DiagnosticReliability2 diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestReliability, compareWithLowReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.6),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.6");
}

//-----------------------------------------------------------------------------
TEST_F(TestReliability, compareWithUncertainReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.75),romea::DiagnosticStatus::WARN);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::WARN);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is uncertain.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.75");
}

//-----------------------------------------------------------------------------
TEST_F(TestReliability, compareWithHighReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.95),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo is high.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.95");
}


class TestRate : public ::testing::Test
{
 public:

  TestRate():
    stamp(),
    diagnostic("foo",10,0.1)
  {

  }

  romea::Duration stamp;
  romea::DiagnosticRate diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestRate, testCheckWithUpperRate)
{
  double rate=20;

  stamp = romea::durationFromSecond(0);
  EXPECT_EQ(diagnostic.evaluate(stamp),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo_rate is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo_rate").c_str(),"0");

  for(size_t n=1;n<2/static_cast<size_t>(rate);++n)
  {
    stamp = romea::durationFromSecond(n/rate);
    EXPECT_EQ(diagnostic.evaluate(stamp),romea::DiagnosticStatus::OK);
    EXPECT_EQ(diagnostic.getReport().status,romea::DiagnosticStatus::OK);
    EXPECT_STREQ(diagnostic.getReport().message.c_str(),"foo rate is OK.");
    EXPECT_STREQ(diagnostic.getReport().info.at("foo_rate").c_str(),"0");
  }

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
