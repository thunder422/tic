/* vim:ts=4:sw=4:et:sts=4:
 *
 * Copyright 2022 Thunder422.  All rights reserved.
 * Distributed under GNU General Public License Version 3
 * (See accompanying file LICENSE or <http://www.gnu.org/licenses/>)
 */

#pragma once

#include <iosfwd>


class Console {
public:
    Console(std::istream &is, std::ostream &os);
    void run();

private:
    std::istream &is;
    std::ostream &os;
};
