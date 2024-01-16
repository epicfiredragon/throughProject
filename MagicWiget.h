#ifndef THROUGH_MAGICWIGET_H
#define THROUGH_MAGICWIGET_H

#include <QtWidgets/QWidget>

class QTextEdit;
class QGridLayout;
class QLineEdit;
class QPushButton;

class EncoderWidget : public QWidget
{

public:
    explicit EncoderWidget(QWidget* parent = nullptr);
    virtual ~EncoderWidget();

signals:

private slots:
    void encodeDecode();

private:
    QGridLayout* m_gridLayout;
    QTextEdit* m_textEdit;
    QLineEdit* m_keyLineEdit;
    QPushButton* m_pushButton;
};


#endif //THROUGH_MAGICWIGET_H
