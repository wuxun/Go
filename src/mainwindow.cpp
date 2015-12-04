#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include <QSplitter>
#include <QTextEdit>
#include <QTextStream>
#include <QTreeView>
#include <QFileDialog>
#include <QDebug>

#include "parser/sgfparser.h"
#include "parser/gamerecord.h"

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
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("SGF Files (*.sgf)"));
    RecordNode *root = NULL;
    if (!fileName.isEmpty()) {
        qInfo("Open:%s", fileName.toStdString().c_str());
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream in(&file);
            SgfParser parser;
            root = new RecordNode;
            parser.doParse(in, root);
            file.close();
            qDebug("------------------");
            qDebug() << root->toString();
        }
    }

//    QString str = "(;AP[Ha\\]ndTalk]GM[1][2]PW[wuxun]PB[panda][dapan](;W[aa](;B[cc]C[a\\]nother];W[dd]);B[ee]))";
//    QTextStream in(&str);
//    SgfParser parser;
//    RecordNode *record = new RecordNode;
//    parser.doParse(in, record);
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
