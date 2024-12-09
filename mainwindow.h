#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fillTable(const std::vector<std::string> &info);

    std::vector<std::string> parseServerResponse(const std::string &response);

    void on_folderBtn_clicked();

    void on_findBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
