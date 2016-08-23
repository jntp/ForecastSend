/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "UnitTests.h"

static TwilioTestSuite suite_TwilioTestSuite;

static CxxTest::List Tests_TwilioTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TwilioTestSuite( "UnitTests.h", 19, "TwilioTestSuite", suite_TwilioTestSuite, Tests_TwilioTestSuite );

static class TestDescription_TwilioTestSuite_testRest : public CxxTest::RealTestDescription {
public:
 TestDescription_TwilioTestSuite_testRest() : CxxTest::RealTestDescription( Tests_TwilioTestSuite, suiteDescription_TwilioTestSuite, 22, "testRest" ) {}
 void runTest() { suite_TwilioTestSuite.testRest(); }
} testDescription_TwilioTestSuite_testRest;

static class TestDescription_TwilioTestSuite_testTwiML : public CxxTest::RealTestDescription {
public:
 TestDescription_TwilioTestSuite_testTwiML() : CxxTest::RealTestDescription( Tests_TwilioTestSuite, suiteDescription_TwilioTestSuite, 50, "testTwiML" ) {}
 void runTest() { suite_TwilioTestSuite.testTwiML(); }
} testDescription_TwilioTestSuite_testTwiML;

static class TestDescription_TwilioTestSuite_testUtils : public CxxTest::RealTestDescription {
public:
 TestDescription_TwilioTestSuite_testUtils() : CxxTest::RealTestDescription( Tests_TwilioTestSuite, suiteDescription_TwilioTestSuite, 72, "testUtils" ) {}
 void runTest() { suite_TwilioTestSuite.testUtils(); }
} testDescription_TwilioTestSuite_testUtils;

#include <cxxtest/Root.cpp>
