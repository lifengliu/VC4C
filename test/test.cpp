/*
 * Author: doe300
 *
 * See the file "LICENSE" for the full license governing this code.
 */

#include <cstdlib>
#include <fstream>

#include "cpptest.h"
#include "cpptest-main.h"
#include "TestScanner.h"
#include "TestParser.h"
#include "TestInstructions.h"
#include "TestSPIRVFrontend.h"

#include "../lib/cpplog/include/logger.h"
#include "RegressionTest.h"

using namespace std;

template<bool R>
static Test::Suite* newLLVMCompilationTest()
{
	return new RegressionTest(vc4c::Frontend::LLVM_IR, R);
}

template<bool R>
static Test::Suite* newSPIRVCompiltionTest()
{
	return new RegressionTest(vc4c::Frontend::SPIR_V, R);
}

template<bool R>
static Test::Suite* newCompilationTest()
{
	return new RegressionTest(vc4c::Frontend::DEFAULT, R);
}

/*
 * 
 */
int main(int argc, char** argv)
{

    #if TEST_OUTPUT_CONSOLE == 1
    Test::TextOutput output(Test::TextOutput::Verbose);
    #else
    std::ofstream file;
    file.open("testResult.log", std::ios_base::out | std::ios_base::trunc);

    Test::TextOutput output(Test::TextOutput::Verbose, file);
    #endif

    //only output errors
    logging::LOGGER.reset(new logging::ConsoleLogger(logging::Level::WARNING));

    Test::registerSuite(Test::newInstance<TestScanner>, "test-scanner", "Tests the LLVM IR scanner");
    Test::registerSuite(Test::newInstance<TestParser>, "test-parser", "Tests the LLVM IR parser");
    Test::registerSuite(Test::newInstance<TestInstructions>, "test-instructions", "Tests some common instruction handling");
    Test::registerSuite(Test::newInstance<TestSPIRVFrontend>, "test-spirv", "Tests the SPIR-V front-end");
    Test::registerSuite(newLLVMCompilationTest<true>, "regressions-llvm", "Runs the regression-test using the LLVM-IR front-end", false);
    Test::registerSuite(newSPIRVCompiltionTest<true>, "regressions-spirv", "Runs the regression-test using the SPIR-V front-end", false);
    Test::registerSuite(newCompilationTest<true>, "regressions", "Runs the regression-test using the default front-end", false);
    Test::registerSuite(newCompilationTest<false>, "test-compilation", "Runs all the compilation tests using the default front-end", true);
    Test::registerSuite(newLLVMCompilationTest<false>, "test-compilation-llvm", "Runs all the compilation tests using the LLVM-IR front-end", false);
    Test::registerSuite(newSPIRVCompiltionTest<false>, "test-compilation-spirv", "Runs all the compilation tests using the SPIR-V front-end", false);

    return Test::runSuites(argc, argv);
}

