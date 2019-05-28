#ifndef SYMBOLCNT_H
#define SYMBOLCNT_H

#include "Cryptanalysis/Common/crypto_tools_types.h"

/* Amount of memory spaces to allocate everytime we need more space */
#define MEMORY_BLOCK_SIZE   (50u)

typedef struct
{
    uint32_t Cnt_u32;
    char Symbol_c;
}symbolcnt_symbolcnt_st;

class symbolcnt
{
public:
    symbolcnt();
    ~symbolcnt();

    /**
     * Add symbol to symbol counter. If symbol exists, it will increment that symbol's count.
     * If symbol does not exist, it will be added tothe list.
     *
     * @return Total number of unique symbols
     */
    uint32_t AddSymbol(char symbol);

    /**
     * Get number of unique symbols in counter object
     *
     * @return Total number of unique symbols
     */
    uint32_t TotalUniqueSymbols();

private:
    symbolcnt_symbolcnt_st* p_SymCnt_ptr;
    uint32_t p_totalSymbolCnt_u32;
    uint32_t p_totalMemorySize_u32;

    symbolcnt_symbolcnt_st* P_GetSymbolSt(char symbol);
};

#endif // SYMBOLCNT_H
