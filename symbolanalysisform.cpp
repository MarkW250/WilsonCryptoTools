#include "symbolanalysisform.h"
#include "ui_symbolanalysisform.h"

SymbolAnalysisForm::SymbolAnalysisForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SymbolAnalysisForm)
{
    ui->setupUi(this);

}

SymbolAnalysisForm::~SymbolAnalysisForm()
{
    delete ui;
}

void SymbolAnalysisForm::on_closeButton_clicked()
{
    this->close();
}

void SymbolAnalysisForm::on_cipherTextEdit_textChanged()
{
    QTextEdit *cTextEdit = this->findChild<QTextEdit*>("cipherTextEdit");
    pSymbAnal.SetCipherText(cTextEdit->toPlainText().toLocal8Bit().data(), uint32_t(cTextEdit->toPlainText().toLocal8Bit().length()));
    if(pSymbAnal.PerformAnalysis() == CRYPTO_TOOLS_NO_ERROR)
    {
        uint32_t numberOfSymbols = 0u;
        pSymbAnal.NumberOfSymbols(&numberOfSymbols);
    }


}
