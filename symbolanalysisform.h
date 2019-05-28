#ifndef SYMBOLANALYSISFORM_H
#define SYMBOLANALYSISFORM_H

#include <QWidget>

#include "Cryptanalysis/SymbolFreq/symbfreqanalysis.h"

namespace Ui {
class SymbolAnalysisForm;
}

class SymbolAnalysisForm : public QWidget
{
    Q_OBJECT

public:
    explicit SymbolAnalysisForm(QWidget *parent = nullptr);
    ~SymbolAnalysisForm();

private slots:
    void on_closeButton_clicked();

    void on_cipherTextEdit_textChanged();

private:
    Ui::SymbolAnalysisForm *ui;

    SymbFreqAnalysis pSymbAnal;
};

#endif // SYMBOLANALYSISFORM_H
