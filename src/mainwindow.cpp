#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include <QSplitter>
#include <QTextEdit>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    createStatusBar();

    rightSpliter = new QSplitter(Qt::Vertical);
    commentView = new QTextEdit();
    stepTreeView = new QTreeView();
    rightSpliter->addWidget(commentView);
    rightSpliter->addWidget(stepTreeView);

    mainSpliter = new QSplitter(Qt::Horizontal);
    boardView = new Board(this);
    mainSpliter->addWidget(boardView);
    mainSpliter->addWidget(rightSpliter);
    QList<int> tmp;
    tmp.append(400);
    tmp.append(100);
    mainSpliter->setSizes(tmp);


    setCentralWidget(mainSpliter);

    setWindowTitle(tr("Go"));
}

MainWindow::~MainWindow()
{
    delete boardView;
    delete commentView;
    delete stepTreeView;
    delete rightSpliter;
    delete mainSpliter;

    delete openAction;
    delete statusLabel;
    delete ui;
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(open()));
}

void MainWindow::open()
{
    qInfo("open");
}

void MainWindow::createStatusBar()
{
    statusLabel = new QLabel;
    statusLabel->setIndent(5);
    statusBar()->addWidget(statusLabel);
}

void MainWindow::updateStatusBar(QString &str)
{
    statusLabel->setText(str);
}
