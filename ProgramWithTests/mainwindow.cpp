#include "mainwindow.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include "fileManager.h"
#include "fullQuestion.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(500,500,300,500);
/*    FileManager Fman;
    FullQuestion FQ;*/
//Зчитати з файлу по замовчуванню
    QString defaultPath="C:/Users/denko/Desktop/Cpp/cpp/FilesToRead/test.txt";
    applyToFormat(defaultPath);
    currentQ=0;
//Запитання
    Question = new QTextEdit(questions[currentQ],this);
    Question->setGeometry(10,10,280,150);
    Question->setReadOnly(true);
//Можливі відповіді
    Answers= new QGroupBox(this);
    Answers->setGeometry(50,170,200,100);
    QVBoxLayout *vbox= new QVBoxLayout;
    Buttons=new QRadioButton*[4];
    for(int i=0; i<4; i++){
        Buttons[i]=new QRadioButton(this);
        Buttons[i]->setText(variants[currentQ][i]);
        vbox->addWidget(Buttons[i]);
    }
    vbox->addStretch(1);
    Answers->setLayout(vbox);
//Кнопка "Відповісти"
    QPushButton *giveAnswer=new QPushButton("Answer",this);
    giveAnswer->setGeometry(50,270,200,50);
    connect(giveAnswer,SIGNAL(released()),this,SLOT(handleButton()));
//Кнопка "Вибрати файл"
    QPushButton *openFile=new QPushButton("Open File",this);
    openFile->setGeometry(50,390,200,50);
    connect(openFile,SIGNAL(released()),this,SLOT(handleOpenFile()));
//Кнопка "Зберегти відповіді у файл"
    QPushButton *saveFile=new QPushButton("Save Answers",this);
    saveFile->setGeometry(50,330,200,50);
    connect(saveFile,SIGNAL(released()),this,SLOT(handleSaveFile()));
}
void MainWindow::loadNextQuestion(){
    Question->setText(questions[currentQ]);
    for(int i=0; i<4; i++){
        Buttons[i]->setText(variants[currentQ][i]);
    }
}
void MainWindow::handleButton(){
   for(int i=0; i<4; i++){
       if(Buttons[i]->isChecked()){
           UserAnswers[currentQ]=Buttons[i]->text();
           Buttons[i]->setAutoExclusive(false);
           Buttons[i]->setChecked(false);
           Buttons[i]->setAutoExclusive(true);
           currentQ+=1;
           loadNextQuestion();
       }
   }
}
void MainWindow::handleOpenFile(){
    QString path = QFileDialog::getOpenFileName(this, "Open Text File", "C:/Temp", "Text files(*.txt);;All files (*.*)");
    currentQ=0;

    applyToFormat(path);
    loadNextQuestion();
}
void MainWindow::handleSaveFile(){
    QString path = QFileDialog::getSaveFileName(this, "Save Text File", "C:/Temp", "Text files(*.txt);;All files (*.*)");
    FileManager FM;
    FM.saveAns(path,UserAnswers);
}
void MainWindow::applyToFormat(QString &path){
    FileManager FM;
    FullQuestion FQ;
    QString *FQs=FM.getFQs(path);
    for (int i=0; i<8; i++) {
        FQ.ParseFQ(FQs[i]);
        questions[i]=FQ.getQuestion();
        QString *answers=FQ.getAnswers();
        for (int j=0;j<4 ;j++ ) {
            variants[i][j]=answers[j];
        }
    }
}
MainWindow::~MainWindow()
{

}

