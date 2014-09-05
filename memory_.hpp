namespace Orion
{
    inline Cell Memory::new_block_nothrow(Cell s) noexcept
    {
        if (s > std::numeric_limits<std::size_t>::max()) return pc_null;

        Cell *ptr = new (std::nothrow) Cell [s];

        return to_pc(ptr);
    }

    inline Cell Memory::new_block(Cell s)
    {
        Cell pc = new_block_nothrow(s);
        if (pc == pc_null) throw std::bad_alloc();

        return pc;
    }

    inline void Memory::delete_block(Cell pc) noexcept
    {
        delete [] to_ptr(pc);
    }

    inline Cell &Memory::operator[](Cell pc) noexcept
    {
        return *to_ptr(pc);
    }
    
    inline Cell *Memory::to_ptr(Cell pc) noexcept
    {
        return reinterpret_cast<Cell *>(pc * 8);
    }
    
    inline Cell Memory::to_pc(Cell *ptr) noexcept
    {
        return reinterpret_cast<Cell>(ptr) / 8;
    }

    inline PCHandle::PCHandle(Memory &m, Cell s) : m_(m)
    {
        pc_ = m_.new_block(s);
    }

    inline PCHandle::~PCHandle()
    {
        m_.delete_block(pc_);
    }

    inline Cell PCHandle::pc(void) noexcept
    {
        return pc_;
    }

    inline Cell PCHandle::take_pc(void) noexcept
    {
        Cell pc = pc_;
        pc_ = pc_null;
        return pc;
    }
}

