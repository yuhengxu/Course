#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "overlap.h"


MainWindow::MainWindow(ReaderWriter *readerWriter, QWidget *parent) :
    QMainWindow(parent), readerWriter(readerWriter),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Reader and Writer");
    lastBoldLabel = nullptr;
    lastRedLabel = nullptr;
    mode = 0;

//    ui->listWidget1->installEventFilter(this);
    ui->startButton->setEnabled(false);

    ui->next1Button->setEnabled(false);
    ui->next2Button->setEnabled(false);
    ui->next3Button->setEnabled(false);
    ui->next4Button->setEnabled(false);
    ui->next5Button->setEnabled(false);
    ui->next6Button->setEnabled(false);
}

void MainWindow::on_readerFirstButton_clicked()
{
    qDebug() << "readerFirstButton Clicked.";
    mode = 1;
    config = readerWriter->getReaderFirstConfig();
    setConfig(config);
}

void MainWindow::setConfig(Config config)
{
    fillListWidgetItems(ui->listWidget1, config.readerActions);
    fillListWidgetItems(ui->listWidget2, config.readerActions);
    fillListWidgetItems(ui->listWidget3, config.readerActions);

    fillListWidgetItems(ui->listWidget4, config.writerActions);
    fillListWidgetItems(ui->listWidget5, config.writerActions);
    fillListWidgetItems(ui->listWidget6, config.writerActions);

    ui->label1->setText("");
    ui->label2->setText("");
    ui->label3->setText("");
    ui->label4->setText("");
    ui->label5->setText("");
    ui->label6->setText("");

    for (int i = 0; i < config.semaphores.size(); i++)
    {
        Config::Object object = config.semaphores[i];
        QString label = QString::fromStdString(object.name)
                + " = " + QString::number(object.value);
        switch (i)
        {
        case 0: ui->label1->setText(label); break;
        case 1: ui->label2->setText(label); break;
        case 2: ui->label3->setText(label); break;
        }
    }

    for (int i = 0; i < config.counters.size(); i++)
    {
        Config::Object object = config.counters[i];
        QString label = QString::fromStdString(object.name)
                + " = " + QString::number(object.value);
        switch (i)
        {
        case 0: ui->label4->setText(label); break;
        case 1: ui->label5->setText(label); break;
        case 2: ui->label6->setText(label); break;
        }
    }

    ui->startButton->setEnabled(true);
//    ui->startButton->toggled(false);
}

void MainWindow::fillListWidgetItems(
        QListWidget *listWidget,
        vector<string> list)
{
    listWidget->clear();
    for (int i = 0; i < list.size(); i++)
    {
        QString text = QString::fromStdString(list[i]);
        QListWidgetItem *item = new QListWidgetItem(text);
        listWidget->addItem(item);
    }
    listWidget->setCurrentRow(0);
}

void MainWindow::on_writerFirstButton_clicked()
{
    qDebug() << "writerFirstButton Clicked.";
    mode = 2;
    config = readerWriter->getWriterFirstConfig();
    setConfig(config);
}

void MainWindow::on_fairnessButton_clicked()
{
    qDebug() << "fairnessButton Clicked.";
    mode = 3;
    config = readerWriter->getFairnessConfig();
    setConfig(config);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_toggled(bool checked)
{
    qDebug() << "StartButton " << checked;
    if (checked)
    {
        ui->startButton->setText("Stop");
        if (lastBoldLabel != nullptr)
        {
            QFont font = lastBoldLabel->font();
            font.setWeight(QFont::Normal);
            lastBoldLabel->setFont(font);
            lastBoldLabel = nullptr;
        }
        if (lastRedLabel != nullptr)
        {
            QPalette palette = lastRedLabel->palette();
            palette.setColor(lastRedLabel->foregroundRole(), Qt::black);
            lastRedLabel->setPalette(palette);
            lastRedLabel = nullptr;
        }
        setConfig(config);
        readerWriter->start();

        for (int i = 1; i <= 6; i++) listRow[i] = 0;

//        Config config;
//        switch (mode)
//        {
//        case 1:
//            config = readerWriter->getReaderFirstConfig();
//            setConfig(config);
//            break;
//        case 2:
//            config = readerWriter->getWriterFirstConfig();
//            setConfig(config);
//            break;
//        case 3:
//            config = readerWriter->getFairnessConfig();
//            setConfig(config);
//            break;
//        }

        ui->listWidget1->setCurrentRow(0);
        ui->listWidget2->setCurrentRow(0);
        ui->listWidget3->setCurrentRow(0);
        ui->listWidget4->setCurrentRow(0);
        ui->listWidget5->setCurrentRow(0);
        ui->listWidget6->setCurrentRow(0);

        ui->next1Button->setEnabled(true);
        ui->next2Button->setEnabled(true);
        ui->next3Button->setEnabled(true);
        ui->next4Button->setEnabled(true);
        ui->next5Button->setEnabled(true);
        ui->next6Button->setEnabled(true);

        ui->readerFirstButton->setEnabled(false);
        ui->writerFirstButton->setEnabled(false);
        ui->fairnessButton->setEnabled(false);
    }
    else
    {
        readerWriter->stop();
        ui->startButton->setText("Start");

        ui->listWidget1->setCurrentRow(-1);
        ui->listWidget2->setCurrentRow(-1);
        ui->listWidget3->setCurrentRow(-1);
        ui->listWidget4->setCurrentRow(-1);
        ui->listWidget5->setCurrentRow(-1);
        ui->listWidget6->setCurrentRow(-1);

        ui->next1Button->setEnabled(false);
        ui->next2Button->setEnabled(false);
        ui->next3Button->setEnabled(false);
        ui->next4Button->setEnabled(false);
        ui->next5Button->setEnabled(false);
        ui->next6Button->setEnabled(false);

        ui->readerFirstButton->setEnabled(true);
        ui->writerFirstButton->setEnabled(true);
        ui->fairnessButton->setEnabled(true);
    }
}

void MainWindow::updateObjects(Overlap overlap)
{
    if (lastRedLabel != nullptr)
    {
        QPalette palette = lastRedLabel->palette();
        palette.setColor(lastRedLabel->foregroundRole(), Qt::black);
        lastRedLabel->setPalette(palette);
        lastRedLabel = nullptr;
    }


    if (overlap.id < 1 || overlap.id > 6) return;

    QString number = QString::number(overlap.value);
    QString name;
    switch (overlap.id)
    {
    case 1:
        name = QString::fromStdString(overlap.name);
        ui->label1->setText(name + " = " + number);
        setBold(ui->label1);
        setRed(ui->label1, overlap.blocked);
        break;
    case 2:
        name = QString::fromStdString(overlap.name);
        ui->label2->setText(name + " = " + number);
        setBold(ui->label2);
        setRed(ui->label2, overlap.blocked);
        break;
    case 3:
        name = QString::fromStdString(overlap.name);
        ui->label3->setText(name + " = " + number);
        setBold(ui->label3);
        setRed(ui->label3, overlap.blocked);
        break;
    case 4:
        name = QString::fromStdString(overlap.name);
        ui->label4->setText(name + " = " + number);
        setBold(ui->label4);
        setRed(ui->label4, overlap.blocked);
        break;
    case 5:
        name = QString::fromStdString(overlap.name);
        ui->label5->setText(name + " = " + number);
        setBold(ui->label5);
        setRed(ui->label5, overlap.blocked);
        break;
    case 6:
        name = QString::fromStdString(overlap.name);
        ui->label6->setText(name + " = " + number);
        setBold(ui->label6);
        setRed(ui->label6, overlap.blocked);
        break;
    }
}

void MainWindow::setRed(QLabel *label, bool flag)
{
    if (lastRedLabel != nullptr)
    {
        QPalette palette = lastRedLabel->palette();
        palette.setColor(lastRedLabel->foregroundRole(), Qt::black);
        lastRedLabel->setPalette(palette);
    }

    if (flag)
    {
        QPalette palette = label->palette();
        palette.setColor(label->foregroundRole(), Qt::red);
        label->setPalette(palette);

        lastRedLabel = label;
    }
    else
    {
        QPalette palette = label->palette();
        palette.setColor(label->foregroundRole(), Qt::black);
        label->setPalette(palette);

        lastRedLabel = nullptr;
    }
}

void MainWindow::setBold(QLabel *label)
{
    if (label == nullptr) return;
    if (lastBoldLabel != nullptr)
    {
        QFont font = lastBoldLabel->font();
        font.setWeight(QFont::Normal);
        lastBoldLabel->setFont(font);
    }
    QFont font = label->font();
    font.setWeight(QFont::Bold);
    label->setFont(font);

    lastBoldLabel = label;
}

void MainWindow::on_next1Button_clicked()
{
    ui->next1Button->setEnabled(false);
    ui->listWidget1->setFocus();
    Overlap overlap = readerWriter->next(1);
//    if (overlap.line < 0)
//    {
//        ui->next1Button->setEnabled(false);
//        return;
//    }
    ui->listWidget1->setCurrentRow(overlap.line);
    listRow[1] = overlap.line;
    updateObjects(overlap);
//    setRed(ui->listWidget1, false);
    ui->next1Button->setEnabled(true);
}

void MainWindow::on_next2Button_clicked()
{
    ui->next2Button->setEnabled(false);
    ui->listWidget2->setFocus();
    Overlap overlap = readerWriter->next(2);
//    if (overlap.line < 0)
//    {
//        ui->next1Button->setEnabled(false);
//        return;
//    }
    ui->listWidget2->setCurrentRow(overlap.line);
    listRow[2] = overlap.line;
    updateObjects(overlap);
//    setRed(ui->listWidget2, false);
    ui->next2Button->setEnabled(true);
}

void MainWindow::on_next3Button_clicked()
{
    ui->next3Button->setEnabled(false);
    ui->listWidget3->setFocus();
    Overlap overlap = readerWriter->next(3);
//    if (overlap.line < 0)
//    {
//        ui->next1Button->setEnabled(false);
//        return;
//    }
    ui->listWidget3->setCurrentRow(overlap.line);
    listRow[3] = overlap.line;
    updateObjects(overlap);
//    setRed(ui->listWidget3, false);
    ui->next3Button->setEnabled(true);
}

void MainWindow::on_next4Button_clicked()
{
    ui->next4Button->setEnabled(false);
    ui->listWidget4->setFocus();
    Overlap overlap = readerWriter->next(4);
//    if (overlap.line < 0)
//    {
//        ui->next1Button->setEnabled(false);
//        return;
//    }
    ui->listWidget4->setCurrentRow(overlap.line);
    listRow[4] = overlap.line;
    updateObjects(overlap);
//    setRed(ui->listWidget4, false);
    ui->next4Button->setEnabled(true);
}

void MainWindow::on_next5Button_clicked()
{
    ui->next5Button->setEnabled(false);
    ui->listWidget5->setFocus();
    Overlap overlap = readerWriter->next(5);
//    if (overlap.line < 0)
//    {
//        ui->next1Button->setEnabled(false);
//        return;
//    }
    ui->listWidget5->setCurrentRow(overlap.line);
    listRow[5] = overlap.line;
    updateObjects(overlap);
//    setRed(ui->listWidget5, false);
    ui->next5Button->setEnabled(true);
}

void MainWindow::on_next6Button_clicked()
{
    ui->next6Button->setEnabled(false);
    ui->listWidget6->setFocus();
    Overlap overlap = readerWriter->next(6);
//    if (overlap.line < 0)
//    {
//        ui->next1Button->setEnabled(false);
//        return;
//    }
    ui->listWidget6->setCurrentRow(overlap.line);
    listRow[6] = overlap.line;
    updateObjects(overlap);
//    setRed(ui->listWidget6, false);
    ui->next6Button->setEnabled(true);
}

void MainWindow::on_listWidget1_itemPressed(QListWidgetItem *item)
{
    qDebug() << "on_listWidget1_itemPressed " << listRow[1];
    ui->listWidget1->setCurrentRow(listRow[1]);
}

void MainWindow::on_listWidget2_itemPressed(QListWidgetItem *item)
{
    ui->listWidget2->setCurrentRow(listRow[2]);
}

void MainWindow::on_listWidget3_itemPressed(QListWidgetItem *item)
{
    ui->listWidget3->setCurrentRow(listRow[3]);
}

void MainWindow::on_listWidget4_itemPressed(QListWidgetItem *item)
{
    ui->listWidget4->setCurrentRow(listRow[4]);
}

void MainWindow::on_listWidget5_itemPressed(QListWidgetItem *item)
{
    ui->listWidget5->setCurrentRow(listRow[5]);
}

void MainWindow::on_listWidget6_itemPressed(QListWidgetItem *item)
{
    ui->listWidget6->setCurrentRow(listRow[6]);
}
