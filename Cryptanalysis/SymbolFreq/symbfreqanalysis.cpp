#include "symbfreqanalysis.h"
#include "symbolcnt.h"

SymbFreqAnalysis::SymbFreqAnalysis()
{
    pSymbolCounter = nullptr;
    pCipherTextpca = nullptr;
    pCipherTextLengthU32 = 0;
    pTextChanged_b = false;
}

SymbFreqAnalysis::~SymbFreqAnalysis()
{
    if(pCipherTextpca != nullptr)
    {
        delete pCipherTextpca;
    }

    if(pSymbolCounter != nullptr)
    {
        delete pSymbolCounter;
    }
}

CryptoToolsErrorT SymbFreqAnalysis::PerformAnalysis()
{
    uint32_t i = 0;

    if(pCipherTextpca == nullptr)
    {
        return CRYPTO_TOOLS_ERROR_PARAM_NULL_PTR;
    }

    if(pTextChanged_b == true)
    {
        if(pSymbolCounter != nullptr)
        {
            delete pSymbolCounter;
        }

        pSymbolCounter = new symbolcnt;

        // add symbols to symbol counter
        for(i = 0; i < pCipherTextLengthU32; i++)
        {
            pSymbolCounter->AddSymbol(pCipherTextpca[i]);
        }

        pTextChanged_b = false;
    }

    return CRYPTO_TOOLS_NO_ERROR;
}

CryptoToolsErrorT SymbFreqAnalysis::SetCipherText(const char *newCipherTextpca, uint32_t cipherTextLengthU32)
{
    // check if length is sane
    if(cipherTextLengthU32 > SYMBOL_FREQ_MAX_CIPHER_LENGTH)
    {
        return CRYPTO_TOOLS_ERROR_PARAM_INVALID_LENGTH;
    }

    // check input pointer is not null
    if(newCipherTextpca == nullptr)
    {
        return  CRYPTO_TOOLS_ERROR_PARAM_NULL_PTR;
    }

    // delete current text if exists
    if(pCipherTextpca != nullptr)
    {
        delete pCipherTextpca;
        pCipherTextpca = nullptr;
    }

    // create new cipher text
    if(cipherTextLengthU32 > 0)
    {
        pCipherTextpca = new char[cipherTextLengthU32];
        pCipherTextLengthU32 = cipherTextLengthU32;
        memcpy(pCipherTextpca, newCipherTextpca, pCipherTextLengthU32);
    }

    pTextChanged_b = true;

    return CRYPTO_TOOLS_NO_ERROR;
}

CryptoToolsErrorT SymbFreqAnalysis::NumberOfSymbols(uint32_t* output_no_u32)
{
    CryptoToolsErrorT error = CRYPTO_TOOLS_NO_ERROR;

    *output_no_u32 = 0u;

    if(pSymbolCounter == nullptr)
    {
        return CRYPTO_TOOLS_ERROR_NO_ANALYSIS;
    }

    if(pTextChanged_b == true)
    {
        error = CRYPTO_TOOLS_ERROR_CIPHER_TEXT_CHANGED;
    }

    *output_no_u32 = pSymbolCounter->TotalUniqueSymbols();

    return error;
}

/****************************************************************************/
/*******************    PRIVATE FUNCTIONS    ********************************/
/****************************************************************************/

bool SymbFreqAnalysis::pfDoesBufferContainSymbol(const char *buffer_pca, uint32_t bufferLength_u32, char symbol_c)
{
    uint32_t i;
    bool return_b = false;
    for(i = 0; (i < bufferLength_u32) && (return_b == false); i++)
    {
        if(buffer_pca[i] == symbol_c)
        {
            return_b = true;
        }
    }
    return return_b;
}
