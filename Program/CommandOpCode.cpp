/* vim:ts=4:sw=4:et:sts=4:
 *
 * Copyright 2022 Thunder422.  All rights reserved.
 * Distributed under GNU General Public License Version 3
 * (See accompanying file LICENSE or <http://www.gnu.org/licenses/>)
 */

#include <map>
#include <string_view>
#include "CommandOpCode.h"


namespace {

std::map<std::string_view, CommandOpCode *> command_codes;

}

const CommandOpCode *CommandOpCode::find(std::string_view keyword)
{
    if (auto it = command_codes.find(keyword); it != command_codes.end()) {
        return it->second;
    }
    return nullptr;
}

CommandOpCode::CommandOpCode(std::string_view keyword)
{
    command_codes[keyword] = this;
}
