/* vim:ts=4:sw=4:et:sts=4:
 *
 * Copyright 2022 Thunder422.  All rights reserved.
 * Distributed under GNU General Public License Version 3
 * (See accompanying file LICENSE or <http://www.gnu.org/licenses/>)
 */

#include <charconv>
#include <cmath>
#include <iostream>
#include "Code.h"
#include "OpCodes.h"
#include "Runner.h"


void runPrint(Runner &runner)
{
    runner.output("\n");
}

void runPrintNum(Runner &runner)
{
    char string[20];
    auto number = runner.popNumber();
    auto [end, error_code] = std::to_chars(string, string + sizeof(string), number);
    runner.output(std::string{string, end});
}

void runEnd(Runner &runner)
{
    runner.output("End Program.\n");
    runner.endProgram();
}

void runConstNum(Runner &runner)
{
    auto index = runner.getOperand();
    auto number = runner.getConstNum(index);
    runner.pushNumber(number);
}

void runNeg(Runner &runner)
{
    runner.topNumber() = -runner.topNumber();
}

void runAdd(Runner &runner)
{
    auto rhs = runner.popNumber();
    runner.topNumber() += rhs;
}

void runSub(Runner &runner)
{
    auto rhs = runner.popNumber();
    runner.topNumber() -= rhs;
}

void runMul(Runner &runner)
{
    auto rhs = runner.popNumber();
    runner.topNumber() *= rhs;
}

void runDiv(Runner &runner)
{
    auto rhs = runner.popNumber();
    runner.topNumber() /= rhs;
}

void runMod(Runner &runner)
{
    auto rhs = runner.popNumber();
    runner.topNumber() = std::fmod(runner.topNumber(), rhs);
}

void runIdiv(Runner &runner)
{
    auto rhs = runner.popNumber();
    runner.topNumber() = std::trunc(runner.topNumber() / rhs);
}

void runPow(Runner &runner)
{
    auto rhs = runner.popNumber();
    runner.topNumber() = std::pow(runner.topNumber(), rhs);
}

Runner::Runner(ProgramCode &code, std::ostream &os) :
    code {code},
    os {os}
{
}

void Runner::runProgram()
{
    pc = 0;
    while (!is_done) {
        auto opcode = code.getWord(pc);
        OpCodes::getRunFunction(opcode)(*this);
        ++pc;
    }
}

std::size_t Runner::getOperand()
{
    return code.getWord(++pc);
}

double Runner::getConstNum(std::size_t index)
{
    return code.getConstNum(index);
}

void Runner::output(std::string_view string)
{
    os << string;
}

void Runner::endProgram()
{
   is_done = true;
}
