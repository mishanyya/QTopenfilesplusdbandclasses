#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "QtGui"
#include "QFileDialog"//для диалоговых окон

#include "QSqlQuery"//для работы с SQL запросами
#include "QTableView"//для работы с графическим выводом информации в виде таблиц
#include "QSqlTableModel" //класс для работы с редактируемой одиночной таблицей из БД
#include "QSqlRelationalTableModel" //класс для работы с редактируемой таблицей из БД с поддержкой внешних ключей
#include "QSqlQueryModel" //класс для работы с таблицей только для чтения из БД для вывода SQL запросов

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openfile())); //для выбора файла на компьютере


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openfile(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");// db - это внешняя глобальная переменная, которую можно использовать тво всех файлах программы
    QSqlTableModel *model = new QSqlTableModel; //создается глобальный объект модели таблицы с редактируемыми ячейками

    //открывает стандартное окно с файлами и можно выбрать нужный файл
    //в переменную file после выбора поместится адрес выбранного файла
     QString file = QFileDialog::getOpenFileName(
                            this,
                            "Select one or more files to open",//заголовок открывающегося стандартного окна
                            "/home");//каталог, который открывается при запуске
                           //если прописать QDir :: currentPath (); то откроется каталог созданного приложения Qt с исполняемыми файлами программы

     //подключить БД по ее адресу на компьютере
     db.setDatabaseName(file);
     //открывает базу данных по адресу file
     db.open();
     model->setTable("basetable");//выбирается существующая табл БД
     //Возможны значения для редактирования записей:
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);//настраивается редактирование таблицы
     //model->setEditStrategy(QSqlTableModel::OnFieldChange);//данные сохранятся в БД сразу при переходе на другую ячейку
     //model->setEditStrategy(QSqlTableModel::OnRowChange);//данные сохранятся в БД сразу при переходе на другую строку
     model->select();//заполняет модель данными из таблицы, без этого кода выйдет пустая таблица
     ui->tableView->setModel(model);//выводит в виде таблицы все элементы в окне приложения
}
