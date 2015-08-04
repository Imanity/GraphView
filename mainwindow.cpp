#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.setPen(Qt::gray);
    for(size_t i = 0; i < view.subdivision_points_for_edge.size(); i++)
    {
        std::vector<Point> current_points = view.subdivision_points_for_edge[i];

        for(size_t k = 0; k < current_points.size() - 1; k++)
        {
            p.drawLine(current_points[k].X, current_points[k].Y, current_points[k + 1].X, current_points[k + 1].Y);
        }
    }
    p.setPen(Qt::black);
    p.setBrush(Qt::red);
    for(size_t i = 0; i < view.data_nodes.size(); i++)
    {
        p.drawEllipse(view.data_nodes[i].X - 4, view.data_nodes[i].Y - 4, 8, 8);
    }
}
