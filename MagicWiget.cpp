#include "MagicWiget.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QMessageBox>
#include <Poco/XML/XMLException.h>
#include <Poco/JSON/JSONException.h>
#include "SolverType.h"
#include "ProcessAndHandleFile.h"
#include "FileInfo.h"
#include "exeptions.h"
#include "MagicWiget.h"

class InFileError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class OutFileError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class PreError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class PostError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

FileInfo setFileInfo(const std::string &in_file, const std::string &out_file,
                     const std::string &in_file_type, const std::string &out_file_type,
                     const std::string &pre_steps, const std::string &post_steps) {
    FileInfo info;
    info.in_file_name = in_file;
    info.out_file_name = out_file;
    if (in_file_type == "Text") {
        info.in_type = TypeFile::Text;
    } else {
        if (in_file_type == "XML") {
            info.in_type = TypeFile::XML;
        } else {
            if (in_file_type == "JSON") {
                info.in_type = TypeFile::JSON;
            } else {
                throw InFileError("");
            }
        }
    }
    if (out_file_type == "Text") {
        info.out_type = TypeFile::Text;
    } else {
        if (out_file_type == "XML") {
            info.out_type = TypeFile::XML;
        } else {
            if (out_file_type == "JSON") {
                info.out_type = TypeFile::JSON;
            } else {
                throw InFileError("");
            }
        }
    }
    int pos = 0;
    for (int i = 0; i < pre_steps.size(); i++) {
        if (pre_steps[i] == ' ' or i == pre_steps.size() - 1) {
            std::string temmpstring = pre_steps.substr(i + 1, i - pos - 1);
            if (temmpstring == "Zip") {
                info.pre_steps.push_back(FileProcessingStep::Zip);
            } else {
                if (temmpstring == "AES") {
                    info.pre_steps.push_back(FileProcessingStep::AES);
                } else {
                    throw PreError("");
                }
            }
            pos = i;
        }
    }
    pos = 0;
    for (int i = 0; i < post_steps.size(); i++) {
        if (post_steps[i] == ' ' or i == post_steps.size() - 1) {
            std::string temmpstring = post_steps.substr(i + 1, i - pos - 1);
            if (temmpstring == "Zip") {
                info.post_steps.push_back(FileProcessingStep::Zip);
            } else {
                if (temmpstring == "AES") {
                    info.post_steps.push_back(FileProcessingStep::AES);
                } else {
                    throw PostError("");
                }
            }
            pos = i;
        }
    }
    return info;
}


MagicWidget::MagicWidget(QWidget *parent) :
        QWidget(parent) {
    m_gridLayout = new QGridLayout(this);
    m_in_file = new QLineEdit(this);
    m_gridLayout->addWidget(m_in_file, 0, 0);
    m_out_file = new QLineEdit(this);
    m_gridLayout->addWidget(m_out_file, 1, 0);
    m_in_file_type = new QLineEdit(this);
    m_gridLayout->addWidget(m_in_file_type, 2, 0);
    m_out_file_type = new QLineEdit(this);
    m_gridLayout->addWidget(m_out_file_type, 3, 0);
    m_pre_steps = new QLineEdit(this);
    m_gridLayout->addWidget(m_pre_steps, 4, 0);
    m_post_steps = new QLineEdit(this);
    m_gridLayout->addWidget(m_post_steps, 5, 0);
    m_pushButton = new QPushButton("process", this);
    m_gridLayout->addWidget(m_pushButton, 6, 0);
    l_in_file = new QLabel(this);
    l_in_file->setText("input file");
    m_gridLayout->addWidget(l_in_file, 0, 1);
    l_out_file = new QLabel(this);
    l_out_file->setText("output file");
    m_gridLayout->addWidget(l_out_file, 1, 1);
    l_in_file_type = new QLabel(this);
    l_in_file_type->setText("input file type");
    m_gridLayout->addWidget(l_in_file_type, 2, 1);
    l_out_file_type = new QLabel(this);
    l_out_file_type->setText("output file type");
    m_gridLayout->addWidget(l_out_file_type, 3, 1);
    l_pre_steps = new QLabel(this);
    l_pre_steps->setText("pre steps");
    m_gridLayout->addWidget(l_pre_steps, 4, 1);
    l_post_steps = new QLabel(this);
    l_post_steps->setText("post steps");
    m_gridLayout->addWidget(l_post_steps, 5, 1);
    resize(640, 480);

    connect(m_pushButton, &QPushButton::clicked, this, &MagicWidget::process);
}

MagicWidget::~MagicWidget() = default;

void MagicWidget::process() {
    FileInfo info;
    try {
        info = setFileInfo(m_in_file->text().toStdString(), m_out_file->text().toStdString(),
                           m_in_file_type->text().toStdString(),
                           m_out_file_type->text().toStdString(),
                           m_pre_steps->text().toStdString(), m_post_steps->text().toStdString());
    }
    catch (InFileError &) {
        QMessageBox msgBox;
        msgBox.setText("In file type error");
        msgBox.exec();
        return;
    }
    catch (OutFileError &) {
        QMessageBox msgBox;
        msgBox.setText("Out file type error");
        msgBox.exec();
        return;
    }
    catch (PreError &) {
        QMessageBox msgBox;
        msgBox.setText("Pre steps error");
        msgBox.exec();
        return;
    }
    catch (PostError &) {
        QMessageBox msgBox;
        msgBox.setText("Post steps error");
        msgBox.exec();
        return;
    }

    try {
        ProcessAndHandleFile(info, typeSolver);
    }
    catch (FileOpenError &) {
        QMessageBox msgBox;
        msgBox.setText("No such file");
        msgBox.exec();
        return;
    }
    catch (FileCreationError &) {
        QMessageBox msgBox;
        msgBox.setText("File creation error");
        msgBox.exec();
        return;
    }
    catch (BadFileSyntaxError &) {
        QMessageBox msgBox;
        msgBox.setText("Syntax error");
        msgBox.exec();
        return;
    }
    catch (Poco::JSON::JSONException &) {
        QMessageBox msgBox;
        msgBox.setText("Syntax error");
        msgBox.exec();
        return;
    }
    catch (Poco::XML::XMLException &) {
        QMessageBox msgBox;
        msgBox.setText("Syntax error");
        msgBox.exec();
        return;
    }

}

