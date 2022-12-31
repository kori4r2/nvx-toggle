#include "window.h"
#include <QApplication>
#include <QProcess>
#include <QStyle>

#define WINDOW_WIDTH 250
#define WINDOW_HEIGHT 100
#define BUTTON_X 85
#define BUTTON_Y 60
#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 30
#define LABEL_X 10
#define LABEL_Y 10
#define LABEL_WIDTH 240
#define LABEL_HEIGHT 30

QLabel* BuildLabel(Window* window){
    QLabel *label = new QLabel("status", window);
    label->setGeometry(LABEL_X, LABEL_Y, LABEL_WIDTH, LABEL_HEIGHT);
    label->setAlignment(Qt::AlignCenter);
    return label;
}

QPushButton* BuildButton(Window *window){
    QPushButton *button = new QPushButton("Toggle", window);
    button->setGeometry(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    return button;
}

QSystemTrayIcon* BuildTrayIcon(Window *window) {
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(window);
    QStyle *style = window->style();
    QIcon icon = style->standardIcon(style->SP_DriveHDIcon);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("show nvx-toggle");
    return trayIcon;
}

Window::Window(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setFocusPolicy(Qt::WheelFocus);

    label = BuildLabel(this);
    button = BuildButton(this);
    trayIcon = BuildTrayIcon(this);
    GetCurrentStatus();
    UpdateStrings();
    connect(button, SIGNAL(clicked()), this, SLOT(ToggleStatus()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(SystemTrayActivated(QSystemTrayIcon::ActivationReason)));
}

void Window::GetCurrentStatus() {
    QProcess process;
    process.start("nvx", QStringList() << "status");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    status = output.contains("on");
}

void Window::UpdateStrings() {
    buttonString = status? "Toggle off" : "Toggle on";
    button->setText(buttonString.c_str());
    labelString = status? "nvidia GPU is currently on" : "nvidia GPU is currently off";
    label->setText(labelString.c_str());
}

static void ChangeGPUState(bool status){
    QProcess process;
    process.start("kdesu", QStringList() << "-n" << "--noignorebutton" << "nvx" << (status? "on" : "off"));
    process.waitForFinished();
}

void Window::ToggleStatus() {
    status = !status;
    ChangeGPUState(status);
    UpdateStrings();
}

void Window::SystemTrayActivated(QSystemTrayIcon::ActivationReason reason) {
    if(reason == QSystemTrayIcon::Trigger){
        show();
        GetCurrentStatus();
        UpdateStrings();
        trayIcon->hide();
    }
}

void Window::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    GetCurrentStatus();
    UpdateStrings();
}

bool Window::event(QEvent *event) {
    if(event->type() == QEvent::WindowStateChange && isMinimized()) {
        trayIcon->show();
        hide();
        event->ignore();
        return true;
    }
    return QWidget::event(event);
}
