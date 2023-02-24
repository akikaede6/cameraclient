#include "mainwindow.h"
#include "camerademo.h"
#include "mcudemo.h"
#include "../model/cameramanager.h"

#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CameraManager::Instance();
    init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    QTabWidget *tabWidget = new QTabWidget(this);
    CameraDemo *cameraDemoWidget = new CameraDemo(CameraManager::Instance()->model(), tabWidget);
    McuDemo *mcuDemoWidget = new McuDemo(CameraManager::Instance()->model(), tabWidget);
    tabWidget->addTab(cameraDemoWidget, "CameraDemo");
    tabWidget->addTab(mcuDemoWidget, "McuDemo");
    setCentralWidget(tabWidget);
}

