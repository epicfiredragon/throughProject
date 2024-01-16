#ifndef THROUGH_MAGICWIGET_H
#define THROUGH_MAGICWIGET_H

#include <QtWidgets/QWidget>

class QTextEdit;
class QGridLayout;
class QLineEdit;
class QPushButton;

class MagicWidget : public QWidget
{

public:
    explicit MagicWidget(QWidget* parent = nullptr);
    virtual ~MagicWidget();

signals:

private slots:
    void process();

private:
    QGridLayout* m_gridLayout;
    QTextEdit* m_textEdit;
    QLineEdit* m_keyLineEdit;
    QPushButton* m_pushButton;
};


#endif //THROUGH_MAGICWIGET_H
