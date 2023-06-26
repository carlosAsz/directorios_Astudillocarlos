#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);  // Nuevo: conectar la señal del itemClicked al slot personalizado.
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "C:/Users/USER/Desktop/ProyectosQt", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        ui->label->setText(directory); // Establecer la ruta de la carpeta en el QLabel

        QDir dir(directory);
        QStringList entries = dir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot); // Obtener carpetas y archivos dentro del directorio

        ui->listWidget->clear(); // Limpiar la lista antes de agregar nuevos elementos

        for (const QString& entry : entries) {
            ui->listWidget->addItem(entry); // Agregar cada carpeta o archivo a la lista
        }
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString fullPath = QDir(ui->label->text()).filePath(item->text()); // Obtiene la ruta completa del archivo/directorio seleccionado
    QFileInfo fileInfo(fullPath);

    ui->Propiedades->clear(); // Limpia la lista de propiedades
    ui->Propiedades->addItem("Nombre del Archivo: " + fileInfo.fileName());
    ui->Propiedades->addItem("Ubicación: " + fileInfo.absoluteFilePath());
    ui->Propiedades->addItem("Extensión: " + fileInfo.suffix());
    ui->Propiedades->addItem("Tamaño: " + QString::number(fileInfo.size()) + " bytes");
    ui->Propiedades->addItem(fileInfo.isFile() ? "Es un archivo" : "No es un archivo");
    ui->Propiedades->addItem("Fecha de última modificación: " + fileInfo.lastModified().toString());

    if (fileInfo.isDir()) {
        QDir dir(fullPath);
        int fileCount = dir.entryList(QDir::Files | QDir::NoDotAndDotDot).count();
        ui->Propiedades->addItem("Cantidad de archivos en la carpeta: " + QString::number(fileCount));

        QDateTime creationTime = fileInfo.created();
        ui->Propiedades->addItem("Fecha de creación: " + creationTime.toString());
    }
}

