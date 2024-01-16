#include "MagicWiget.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

EncoderWidget::EncoderWidget(QWidget* parent) :
        QWidget(parent)
{
    m_gridLayout = new QGridLayout(this);
    m_textEdit = new QTextEdit(this);
    m_gridLayout->addWidget(m_textEdit, 0, 0, 1, 2);
    m_keyLineEdit = new QLineEdit(this);
    m_gridLayout->addWidget(m_keyLineEdit, 1, 0);
    m_pushButton = new QPushButton("Encode/Decode", this);
    m_gridLayout->addWidget(m_pushButton, 1, 1);
    resize(640, 480);

    connect(m_pushButton, &QPushButton::clicked, this, &EncoderWidget::encodeDecode);
}

EncoderWidget::~EncoderWidget()
{

}

void EncoderWidget::encodeDecode()
{

    const char* input = m_textEdit->toPlainText().toLatin1().data();
    int inputLength = m_textEdit->toPlainText().toLatin1().length();
    const char* key = m_keyLineEdit->text().toLatin1().data();
    int keyLength = m_keyLineEdit->text().toLatin1().length();

    char output[inputLength];

    for (int i = 0; i < inputLength + 1; ++i)
    {
        output[i] = input[i] ^ key[i % keyLength + 1];
    }

    m_textEdit->setText(QString::fromLatin1(output, inputLength));
}

