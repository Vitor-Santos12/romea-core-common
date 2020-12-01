// gtest
#include <gtest/gtest.h>

//romea
#include "romea_common/diagnostic/CheckupEqualTo.hpp"
#include "romea_common/diagnostic/CheckupGreaterThan.hpp"
#include "romea_common/diagnostic/CheckupLowerThan.hpp"
#include "romea_common/diagnostic/CheckupReliability.hpp"
#include "romea_common/diagnostic/CheckupRate.hpp"

//-----------------------------------------------------------------------------
const romea::Diagnostic & diagnostic(const romea::DiagnosticReport & report,
                                     const size_t & index)
{
  return *std::next(std::cbegin(report.diagnostics),index);
}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, checkComparison)
{
  EXPECT_TRUE(romea::DiagnosticStatus::OK<romea::DiagnosticStatus::WARN);
  EXPECT_TRUE(romea::DiagnosticStatus::WARN<romea::DiagnosticStatus::ERROR);
  EXPECT_TRUE(romea::DiagnosticStatus::ERROR<romea::DiagnosticStatus::STALE);
}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, checkWorseStatus)
{
  EXPECT_EQ(worse(romea::DiagnosticStatus::OK,
                  romea::DiagnosticStatus::OK),romea::DiagnosticStatus::OK);

  EXPECT_EQ(worse(romea::DiagnosticStatus::OK,
                  romea::DiagnosticStatus::WARN),romea::DiagnosticStatus::WARN);

}


//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, checkToStringConversion)
{
  EXPECT_STREQ(toString(romea::DiagnosticStatus::OK).c_str(),"OK");
  EXPECT_STREQ(toString(romea::DiagnosticStatus::WARN).c_str(),"WARN");
  EXPECT_STREQ(toString(romea::DiagnosticStatus::ERROR).c_str(),"ERROR");
  EXPECT_STREQ(toString(romea::DiagnosticStatus::STALE).c_str(),"STALE");

}


//-----------------------------------------------------------------------------
TEST(TestDiagnosticReport, checkSetInfosValues)
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
TEST(TestDiagnosticReport, checkSetReportOtionalInfosValues)
{
  romea::DiagnosticReport report;
  boost::optional<double> foo(7.77);
  boost::optional<std::string> bar;

  romea::setReportInfo(report,"foo",foo);
  romea::setReportInfo(report,"bar",bar);

  EXPECT_STREQ(report.info.at("foo").c_str(),"7.77");
  EXPECT_STREQ(report.info.at("bar").c_str(),"");
}

//-----------------------------------------------------------------------------
TEST(TestReport, checkAgregation)
{
  romea::DiagnosticReport report1;
  report1.diagnostics.emplace_back(romea::DiagnosticStatus::OK,std::string("foo"));
  report1.info["foo"]="0.1";

  romea::DiagnosticReport report2;
  report2.diagnostics.emplace_back(romea::DiagnosticStatus::OK,"bar");
  report2.diagnostics.emplace_back(romea::DiagnosticStatus::ERROR,"baz");
  report2.info["bar"]="enable";
  report2.info["baz"]="disable";

  romea::DiagnosticReport report3;
  report3+=report1;
  report3+=report2;

  EXPECT_EQ(diagnostic(report3,0).status,romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic(report3,0).message,"foo");
  EXPECT_EQ(diagnostic(report3,1).status,romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic(report3,1).message,"bar");
  EXPECT_EQ(diagnostic(report3,2).status,romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic(report3,2).message,"baz");
  EXPECT_STREQ(report3.info["foo"].c_str(),"0.1");
  EXPECT_STREQ(report3.info["bar"].c_str(),"enable");
  EXPECT_STREQ(report3.info["baz"].c_str(),"disable");
}

class TestEqualTo : public ::testing::Test
{
public:

  TestEqualTo():
    diagnostic("foo",0.8,0.1)
  {

  }

  romea::CheckEqualTo<double> diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestEqualTo, compareWithLowerValue)
{
  EXPECT_EQ(diagnostic.evaluate(0.5),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.5");
}

//-----------------------------------------------------------------------------
TEST_F(TestEqualTo, compareWithEqualValue)
{
  EXPECT_EQ(diagnostic.evaluate(0.85),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is OK.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.85");
}

//-----------------------------------------------------------------------------
TEST_F(TestEqualTo, compareWithHigherValue)
{
  EXPECT_EQ(diagnostic.evaluate(1.11),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is too high.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"1.11");
}


class TestGreaterThan : public ::testing::Test
{
public:

  TestGreaterThan():
    diagnostic("foo",-0.3,0.1)
  {

  }

  romea::CheckupGreaterThan<double> diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestGreaterThan, compareWithLowerValue)
{
  EXPECT_EQ(diagnostic.evaluate(-0.5),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"-0.5");
}

//-----------------------------------------------------------------------------
TEST_F(TestGreaterThan, compareWithHigherValue)
{
  EXPECT_EQ(diagnostic.evaluate(-0.25),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is OK.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"-0.25");
}

class TestLowerThan : public ::testing::Test
{
public:

  TestLowerThan():
    diagnostic("foo",1.45,0.1)
  {

  }

  romea::CheckupLowerThan<double> diagnostic;
};


//-----------------------------------------------------------------------------
TEST_F(TestLowerThan, compareWithLowerValue)
{
  EXPECT_EQ(diagnostic.evaluate(1.5),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is OK.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"1.5");
}

//-----------------------------------------------------------------------------
TEST_F(TestLowerThan, compareWithHigherValue)
{
  EXPECT_EQ(diagnostic.evaluate(1.7),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is too high.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"1.7");
}

class TestReliability : public ::testing::Test
{
public:

  TestReliability():
    diagnostic("foo",0.7,0.9)
  {

  }

  romea::CheckupReliability diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestReliability, compareWithLowReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.6),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.6");
}

//-----------------------------------------------------------------------------
TEST_F(TestReliability, compareWithUncertainReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.75),romea::DiagnosticStatus::WARN);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::WARN);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is uncertain.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(),"0.75");
}

//-----------------------------------------------------------------------------
TEST_F(TestReliability, compareWithHighReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.95),romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo is high.");
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
  romea::CheckupRate diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestRate, testCheckWithUpperRate)
{
  double rate=20;

  stamp = romea::durationFromSecond(0);
  EXPECT_EQ(diagnostic.evaluate(stamp),romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo_rate is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo_rate").c_str(),"0");

  for(size_t n=1;n<2/static_cast<size_t>(rate);++n)
  {
    stamp = romea::durationFromSecond(n/rate);
    EXPECT_EQ(diagnostic.evaluate(stamp),romea::DiagnosticStatus::OK);
    EXPECT_EQ(diagnostic.getReport().diagnostics.front().status,romea::DiagnosticStatus::OK);
    EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(),"foo rate is OK.");
    EXPECT_STREQ(diagnostic.getReport().info.at("foo_rate").c_str(),"0");
  }

}


//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
