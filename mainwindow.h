#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QMenu>
#include <QMultiHash>


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
    void on_pushButton_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);

    void on_anewch_triggered();

    void on_adel_triggered();

    void on_aneweel_triggered();

    void on_aris_triggered();

    void on_aris2_triggered();

    void on_label_17_linkActivated(const QString &link);

    void on_frame_4_customContextMenuRequested(const QPoint &pos);

    void on_achan_triggered();

    void on_asave_triggered();

    void on_atat_triggered();
    void mouseMove(QMouseEvent *mouseEvent);

    void on_astan_triggered();

    void on_azooz_triggered();

private:
    Ui::MainWindow *ui;
    QMultiHash<QString,QString> memory;


};

#endif // MAINWINDOW_H
