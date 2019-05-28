#include "symbolcnt.h"

symbolcnt::symbolcnt()
{
    p_SymCnt_ptr = nullptr;
    p_totalSymbolCnt_u32 = 0;
    p_totalMemorySize_u32 = 0;
}

symbolcnt::~symbolcnt()
{
    if(p_SymCnt_ptr != nullptr)
    {
        delete p_SymCnt_ptr;
    }
}

uint32_t symbolcnt::AddSymbol(char symbol)
{
    symbolcnt_symbolcnt_st* symStPtr = nullptr;

    // check if we need to allocate buffer for first time
    if(p_SymCnt_ptr == nullptr)
    {
        p_SymCnt_ptr = new symbolcnt_symbolcnt_st[MEMORY_BLOCK_SIZE];
        p_totalMemorySize_u32 = MEMORY_BLOCK_SIZE;
    }
    else
    {
        symStPtr = P_GetSymbolSt(symbol);
    }

    // if this symbol does not exist we must add it to the list
    if(symStPtr == nullptr)
    {
        // if we have reached maximum buffer size, we better make a new bigger buffer
        if(p_totalSymbolCnt_u32 >= p_totalMemorySize_u32)
        {
            symbolcnt_symbolcnt_st* tempPtr = p_SymCnt_ptr;
            uint32_t oldSize = p_totalMemorySize_u32;

            p_totalMemorySize_u32 += MEMORY_BLOCK_SIZE;
            p_SymCnt_ptr = new symbolcnt_symbolcnt_st[p_totalMemorySize_u32];
            memcpy(p_SymCnt_ptr, tempPtr, sizeof(symbolcnt_symbolcnt_st) * oldSize);
            delete tempPtr;
        }

        p_SymCnt_ptr[p_totalSymbolCnt_u32].Cnt_u32 = 1u;
        p_SymCnt_ptr[p_totalSymbolCnt_u32].Symbol_c = symbol;
        p_totalSymbolCnt_u32++;
    }
    else
    {
        symStPtr->Cnt_u32++;
    }

    return p_totalSymbolCnt_u32;
}

uint32_t symbolcnt::TotalUniqueSymbols()
{
    return p_totalSymbolCnt_u32;
}

symbolcnt_symbolcnt_st *symbolcnt::P_GetSymbolSt(char symbol)
{
    uint32_t i;
    for(i = 0; i < p_totalSymbolCnt_u32; i++)
    {
        if(p_SymCnt_ptr[i].Symbol_c == symbol)
        {
            return &p_SymCnt_ptr[i];
        }
    }

    return nullptr;
}
