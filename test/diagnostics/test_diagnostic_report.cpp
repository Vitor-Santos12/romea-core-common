// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// gtest
#include <gtest/gtest.h>

// std
#include <string>

// romea
#include "romea_core_common/diagnostic/DiagnosticReport.hpp"

//-----------------------------------------------------------------------------
const romea::Diagnostic & diagnostic(
  const romea::DiagnosticReport & report,
  const size_t & index)
{
  return *std::next(std::cbegin(report.diagnostics), index);
}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticReport, checkSetInfosValues)
{
  romea::DiagnosticReport report;

  romea::setReportInfo(report, "foo", 1.2);
  romea::setReportInfo(report, "bar", "hello");
  romea::setReportInfo(report, "baz", -2);

  EXPECT_STREQ(report.info.at("foo").c_str(), "1.2");
  EXPECT_STREQ(report.info.at("bar").c_str(), "hello");
  EXPECT_STREQ(report.info.at("baz").c_str(), "-2");
}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticReport, checkSetReportOtionalInfosValues)
{
  romea::DiagnosticReport report;
  std::optional<double> foo(7.77);
  std::optional<std::string> bar;

  romea::setReportInfo(report, "foo", foo);
  romea::setReportInfo(report, "bar", bar);

  EXPECT_STREQ(report.info.at("foo").c_str(), "7.77");
  EXPECT_STREQ(report.info.at("bar").c_str(), "");
}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticReport, checkAgregation)
{
  romea::DiagnosticReport report1;
  report1.diagnostics.emplace_back(romea::DiagnosticStatus::OK, std::string("foo"));
  report1.info["foo"] = "0.1";

  romea::DiagnosticReport report2;
  report2.diagnostics.emplace_back(romea::DiagnosticStatus::OK, "bar");
  report2.diagnostics.emplace_back(romea::DiagnosticStatus::ERROR, "baz");
  report2.info["bar"] = "enable";
  report2.info["baz"] = "disable";

  romea::DiagnosticReport report3;
  report3 += report1;
  report3 += report2;

  EXPECT_EQ(diagnostic(report3, 0).status, romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic(report3, 0).message, "foo");
  EXPECT_EQ(diagnostic(report3, 1).status, romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic(report3, 1).message, "bar");
  EXPECT_EQ(diagnostic(report3, 2).status, romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic(report3, 2).message, "baz");
  EXPECT_STREQ(report3.info["foo"].c_str(), "0.1");
  EXPECT_STREQ(report3.info["bar"].c_str(), "enable");
  EXPECT_STREQ(report3.info["baz"].c_str(), "disable");
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
