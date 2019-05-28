#ifndef SYMBFREQANALYSIS_H
#define SYMBFREQANALYSIS_H

#include "Cryptanalysis/Common/crypto_tools_errors.h"
#include "Cryptanalysis/Common/crypto_tools_types.h"
#include "symbolcnt.h"

#define SYMBOL_FREQ_MAX_CIPHER_LENGTH   (5000u)

class SymbFreqAnalysis
{
public:
    SymbFreqAnalysis();
    ~SymbFreqAnalysis();

    /**
     * Sets cipher text to be analysed.
     * NOTE: Does not trigger any analysis.
     *
     * @param newCipherTextpca      Pointer to new cipher text.
     * @param cipherTextLengthU32   Length of new cipher text.
     * @return CRYPTO_TOOLS_ERROR_PARAM_INVALID_LENGTH if length is too long
     * @return CRYPTO_TOOLS_ERROR_PARAM_NULL_PTR if null ptr is passed
     */
    CryptoToolsErrorT SetCipherText(const char* newCipherTextpca, uint32_t cipherTextLengthU32);

    /**
     * Synchronously performs analysis on cipher text, if text has changed since last analysis
     *
     * @return CRYPTO_TOOLS_ERROR_PARAM_NULL_PTR if no cipher text is currently set
     */
    CryptoToolsErrorT PerformAnalysis();

    /**
     * Gets number of unique symbols found in analysis
     *
     * @param output_no_u32      Pointer to store result.
     *
     * @return CRYPTO_TOOLS_ERROR_NO_ANALYSIS if no analysis has yet been triggered
     * @return CRYPTO_TOOLS_ERROR_CIPHER_TEXT_CHANGED if analysis has not been triggered since text has changed - output length will still be populated with previous analsysis length
     */
    CryptoToolsErrorT NumberOfSymbols(uint32_t* output_no_u32);


private:
    bool pTextChanged_b;
    char* pCipherTextpca;
    uint32_t pCipherTextLengthU32;
    symbolcnt* pSymbolCounter;

    bool pfDoesBufferContainSymbol(const char* buffer_pca, uint32_t bufferLength_u32, char symbol_c);
};

#endif // SYMBFREQANALYSIS_H
