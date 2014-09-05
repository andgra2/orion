#pragma once

#include "memory.hpp"

namespace Orion
{
    struct ProgramInstrArgParam
    {
    };

    class Program
    {
    public:
        void nb(void);
        void wi(std::string instr, Args... args);
    private:
        std::vector<Cell> wi_helper_args(void);
        template<typename... ArgsFirst, typename ArgLast>
        std::vector<Cell> wi_helper_args(ArgsFirst... args_first, ArgLast arg_last);
    };
}

#include "program_.hpp"

