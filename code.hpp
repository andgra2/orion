#pragma once

#include <algorithm>
#include <map>
#include "memory.hpp"

namespace Orion
{
    class Code
    {
    public:
        Code(Memory &m);
        template<typename... Args>
        void wi(Cell &pc_next_instr, std::string instr, Args... args);
    private:
        static std::map<std::pair<std::string, unsigned int>, unsigned int> instrs;
        Memory m_;
        std::vector<Cell> wi_helper_args(void);
        template<typename... ArgsFirst, typename ArgLast>
        std::vector<Cell> wi_helper_args(ArgsFirst... args_first, ArgLast arg_last);
    };
}

#include "code_.hpp"

