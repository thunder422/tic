/* vim:ts=4:sw=4:et:sts=4:
 *
 * Copyright 2022 Thunder422.  All rights reserved.
 * Distributed under GNU General Public License Version 3
 * (See accompanying file LICENSE or <http://www.gnu.org/licenses/>)
 */

#include <charconv>
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
    runner.setTopNumber(-runner.getTopNumber());
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

void Runner::pushNumber(double number)
{
    stack = number;
}

double Runner::getTopNumber() const
{
    return stack;
}

void Runner::setTopNumber(double number)
{
    stack = number;
}

double Runner::popNumber()
{
    return stack;
}

void Runner::output(std::string_view string)
{
    os << string;
}

void Runner::endProgram()
{
   is_done = true;
}
