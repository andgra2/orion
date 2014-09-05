namespace Orion
{
    inline CPU::CPU(Memory &m, Cell &pc_destructor_code, Cell &pc_api_code, Cell &pc_api_data) noexcept :
        m_(m),
        pc_destructor_code_(pc_destructor_code),
        pc_api_code_(pc_api_code),
        pc_api_data_(pc_api_data),
        pc_next_instr_(pc_null)
    {
    }

    inline void CPU::run_init(Cell pc_start_instr) noexcept
    {
        pc_next_instr_ = pc_start_instr;
    }

    inline bool CPU::run_step(void) noexcept
    {
        Cell c_instr_head = m_[pc_next_instr_];

        unsigned int ii = c_instr_head & 0xFFFF;
        c_instr_head >>= 16;

        unsigned int na = c_instr_head & 0xFFFF;
        c_instr_head >>= 16;

        pc_next_instr_ += 1;

        for (unsigned int ai = 0; ai != na; ++ai)
        {
            unsigned int ad = c_instr_head & 0xFF;
            c_instr_head >>= 8;

            for (a_[ai] = &m_[pc_next_instr_]; ad != 0; --ad) a_[ai] = &m_[*a_[ai]];

            pc_next_instr_ += 1;
        }

        run_instr(ii);

        return pc_next_instr_ != pc_null;
    }

    inline void CPU::run(Cell pc_start_instr) noexcept
    {
        run_init(pc_start_instr);
        while (run_step());
    }

    inline Cell &CPU::a(unsigned int ai) noexcept
    {
        return *a_[ai];
    }

    inline void CPU::run_instr(unsigned int ii) noexcept
    {
        switch (ii)
        {
        case 0:  pc_next_instr_ = pc_null; break;
        case 1:  pc_next_instr_ = a(0); break;
        case 2:  if (a(0)) pc_next_instr_ = a(1); break;
        case 3:  a(0) = a(1); break;
        case 4:  a(0) = ~a(1); break;
        case 5:  a(0) = !a(1); break;
        case 6:  a(0) = a(1) +  a(2); break;
        case 7:  a(0) = a(1) -  a(2); break;
        case 8:  a(0) = a(1) *  a(2); break;
        case 9:  a(0) = a(1) /  a(2); break;
        case 10: a(0) = a(1) %  a(2); break;
        case 11: a(0) = a(1) << a(2); break;
        case 12: a(0) = a(1) >> a(2); break;
        case 13: a(0) = a(1) &  a(2); break;
        case 14: a(0) = a(1) |  a(2); break;
        case 15: a(0) = a(1) ^  a(2); break;
        case 16: a(0) = a(1) && a(2); break;
        case 17: a(0) = a(1) || a(2); break;
        case 18: a(0) = a(1) == a(2); break;
        case 19: a(0) = a(1) != a(2); break;
        case 20: a(0) = a(1) <= a(2); break;
        case 21: a(0) = a(1) <  a(2); break;
        case 22: a(0) = a(1) >= a(2); break;
        case 23: a(0) = a(1) >  a(2); break;
        case 24: a(0) = m_.new_block_nothrow(a(1)); break;
        case 25: m_.delete_block(a(0)); break;
        case 26: m_.delete_block(a(0)); pc_next_instr_ = pc_null; break;
        case 27: a(0) = pc_destructor_code_; break;
        case 28: pc_destructor_code_ = a(0); break;
        case 29: a(0) = pc_api_code_; break;
        case 30: pc_api_code_ = a(0); break;
        case 31: a(0) = pc_api_data_; break;
        case 32: pc_api_data_ = a(0); break;
        }
    }
}

