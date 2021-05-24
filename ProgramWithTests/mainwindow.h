#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QString>
#include "fileManager.h"
#include "fullQuestion.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    int currentQ;
    QTextEdit *Question;
    QGroupBox *Answers;
    QRadioButton** Buttons;

    QString UserAnswers[8];
    QString questions[8];
    QString variants[8][4];

    void loadNextQuestion();
    void applyToFormat(QString &path);

private slots:
    void handleButton();
    void handleOpenFile();
    void handleSaveFile();
};
#endif // MAINWINDOW_H
