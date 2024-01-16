#ifndef THROUGH_MAGICWIGET_H
#define THROUGH_MAGICWIGET_H

#include <QtWidgets/QWidget>
#include <QLabel>
#include "SolverType.h"

class QTextEdit;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class MagicWidget : public QWidget
{
    SolverType typeSolver;

public:
    explicit MagicWidget(QWidget* parent = nullptr);
    void setSolverType(SolverType solver) {
        typeSolver = solver;
    }
    virtual ~MagicWidget();

signals:

private slots:
    void process();

private:
    QGridLayout* m_gridLayout;
    QLineEdit* m_in_file;
    QLineEdit* m_out_file;
    QLineEdit* m_in_file_type;
    QLineEdit* m_out_file_type;
    QLineEdit* m_pre_steps;
    QLineEdit* m_post_steps;
    QLabel* l_in_file;
    QLabel* l_out_file;
    QLabel* l_in_file_type;
    QLabel* l_out_file_type;
    QLabel* l_pre_steps;
    QLabel* l_post_steps;
    QPushButton* m_pushButton;
};


#endif //THROUGH_MAGICWIGET_H
