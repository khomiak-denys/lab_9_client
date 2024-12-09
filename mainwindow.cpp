#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <string>
#include <sstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Folder search v1.0");
    setWindowIcon(QIcon("C:\\Users\\Denys\\Documents\\Labs\\Labs OS\\Lab 9\\client\\client\\appIcon.png"));
    setFixedSize(575, 550);

    ui->folderBtn->setIcon(QIcon("C:\\Users\\Denys\\Documents\\Labs\\Labs OS\\Lab 9\\client\\client\\folderIcon.png"));

    ui->typeComboBox->addItems({"txt", "docx", "pdf", "rar", "asm", "jpg", "png", "gif", "mp3", "mp4", "zip", "bat", "exe", "cpp", "py", "java"});
    ui->typeComboBox->setCurrentIndex(0);
    ui->dirEdit->setPlaceholderText("Шлях");

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Ім'я", "Розмір", "Час створення"});
    ui->tableWidget->setColumnWidth(0,180);
    ui->tableWidget->setColumnWidth(1,175);
    ui->tableWidget->setColumnWidth(2,150);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::fillTable(const std::vector<std::string> &info) {
    ui->tableWidget->setRowCount(info.size() / 3);

    for (size_t i = 0; i + 2 < info.size(); i += 3) {
        ui->tableWidget->setItem(i / 3, 0, new QTableWidgetItem(QString::fromStdString(info[i])));
        ui->tableWidget->setItem(i / 3, 1, new QTableWidgetItem(QString::fromStdString(info[i + 1])));
        ui->tableWidget->setItem(i / 3, 2, new QTableWidgetItem(QString::fromStdString(info[i + 2])));
    }
}

std::vector<std::string> MainWindow::parseServerResponse(const std::string &response) {
    std::istringstream iss(response);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

void MainWindow::on_folderBtn_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(
        this,
        tr("Оберіть директорію"),
        "C:\\Users\\Denys\\Documents\\Labs\\Labs OS\\Lab 9",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    ui->dirEdit->setText(directory);
}


void MainWindow::on_findBtn_clicked() {
    QString selectedExtension = ui->typeComboBox->currentText();
    QString directory = ui->dirEdit->text();

    if (directory.isEmpty() || selectedExtension.isEmpty()) {
        QMessageBox::warning(this, "Error", "Введіть назву директорії та виберіть розширення файлу");
        return;
    }

    // Ініціалізація Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        QMessageBox::critical(this, "Error", "Failed to initialize Winsock");
        return;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        QMessageBox::critical(this, "Error", "Failed to create socket");
        WSACleanup();
        return;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.56.1", &(serverAddress.sin_addr));
    serverAddress.sin_port = htons(8080);

    if (::connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        QMessageBox::critical(this, "Error", "Connection failed");
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    // Відправлення даних
    std::string message = selectedExtension.toStdString() + " " + directory.toStdString(); // Конвертація QString у std::string
    const char* ex = message.c_str(); // Отримання сирого C-style рядка
    qDebug() << "Message to send:" << message.c_str();
    if (send(clientSocket, ex, strlen(ex), 0) == SOCKET_ERROR) {
        QMessageBox::critical(this, "Error", "Send failed");
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    // Отримання даних від сервера
    char buffer[10000];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Завершуючий символ рядка
        qDebug() << "Received from server:" << buffer;
        std::string inputString(buffer);
        if (inputString.rfind("Error:", 0) == 0) {
            QMessageBox::warning(this, "Server Error", QString::fromStdString(inputString));
        } else {
            std::vector<std::string> info = parseServerResponse(inputString);
            fillTable(info);
        }
    } else {
        QMessageBox::critical(this, "Error", "Receive failed");
    }

    closesocket(clientSocket);
    WSACleanup();
}


