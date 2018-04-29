#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ReaderWriter.h"
#include <QListWidget>
#include "overlap.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ReaderWriter *readerWriter, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_toggled(bool checked);

    void on_next1Button_clicked();

    void on_next2Button_clicked();

    void on_next3Button_clicked();

    void on_next4Button_clicked();

    void on_next5Button_clicked();

    void on_next6Button_clicked();

    void on_readerFirstButton_clicked();

    void on_writerFirstButton_clicked();

    void on_fairnessButton_clicked();

    void on_listWidget1_itemPressed(QListWidgetItem *item);

    void on_listWidget2_itemPressed(QListWidgetItem *item);

    void on_listWidget3_itemPressed(QListWidgetItem *item);

    void on_listWidget4_itemPressed(QListWidgetItem *item);

    void on_listWidget5_itemPressed(QListWidgetItem *item);

    void on_listWidget6_itemPressed(QListWidgetItem *item);

private:
    ReaderWriter *readerWriter;
    Ui::MainWindow *ui;
    QLabel *lastBoldLabel;
    QLabel *lastRedLabel;
    int mode;
    Config config;

    int listRow[7];

    void fillListWidgetItems(QListWidget *listWidget, vector<string> list);
    void updateObjects(Overlap overlap);
    void setConfig(Config config);
    void setBold(QLabel *label);
    void setRed(QLabel *label, bool flag = true);
};

#endif // MAINWINDOW_H
