#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>

class QAction;
class QMenu;
class QSplitter;
class QTextEdit;
class QTreeView;
class RecordNode;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();

private:
    Ui::MainWindow *ui;

    QAction *openAction;

    QMenu *fileMenu;

    QLabel *statusLabel;

    QGraphicsView *boardView;
    QTextEdit *commentView;
    QTreeView *stepTreeView;

    QSplitter *mainSpliter;
    QSplitter *rightSpliter;

    void createActions();
    void createMenus();
    void createStatusBar();
    void updateStatusBar(QString &str);
    void setGameRecordTree(RecordNode *node);
};

#endif // MAINWINDOW_H
