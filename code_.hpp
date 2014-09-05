namespace Orion
{
    template<typename... Args>
    void Code::wi(Cell &pc_next_instr, std::string instr, Args... args)
    {
        const auto arg_cells = wi_helper_args(args...);

        const auto it_sep = std::find(instr.cbegin(), instr.cend(), ' ');

        const std::string instr_name(instr.cbegin(), it_sep);

        std::vector<unsigned int> ads;
        if (it_sep != instr.cend())
        {
            std::transform(it_sep + 1, instr.cend(), std::back_inserter(ads), [] (char c)
                {
                    unsigned int ad;
                    switch (c)
                    {            
                    case 'c':
                        ad = 0;
                        break;
                    case 'v':
                        ad = 1;
                        break;
                    case 'p':
                        ad = 2;
                        break;
                    default:
                        throw std::invalid_argument("");
                    }
                    
                    return ad;
                }
            );
        }
        unsigned int na = ads.size();

        if (arg_cells.size() != na) throw std::invalid_argument("");

        unsigned int ii = instrs.at({instr_name, na}); 

        m_[pc_next_instr] = ii;
        unsigned int os = 16;

        m_[pc_next_instr] |= na << os;
        os += 16;

        for (auto ad : ads)
        {
            m_[pc_next_instr] |= ad << os;
            os += 8;
        }

        ++pc_next_instr;

        for (auto c_arg : arg_cells)
        {
            m_[pc_next_instr] = c_arg;
            ++pc_next_instr;
        }
    }

    inline std::vector<Cell> Code::wi_helper_args(void)
    {
        return std::vector<Cell> {};
    }

    template<typename... ArgsFirst, typename ArgLast>
    inline std::vector<Cell> Code::wi_helper_args(ArgsFirst... args_first, ArgLast arg_last)
    {
        static_assert(std::is_same<ArgLast, Cell>::value, "");

        auto v = wi_helper_args(args_first...);
        v.push_back(arg_last);

        return v;
    }
}

