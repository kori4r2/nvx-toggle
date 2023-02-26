#include "actionIDs.h"
#include "window.h"
#include <QApplication>
#include <QCloseEvent>
#include <QProcess>
#include <QProcessEnvironment>
#include <QStyle>
#include <KAuth/Action>
#include <KAuth/ExecuteJob>

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

QLabel* BuildLabel(Window* window) {
    QLabel* label = new QLabel("status", window);
    label->setGeometry(LABEL_X, LABEL_Y, LABEL_WIDTH, LABEL_HEIGHT);
    label->setAlignment(Qt::AlignCenter);
    return label;
}

QPushButton* BuildButton(Window* window) {
    QPushButton* button = new QPushButton("Toggle", window);
    button->setGeometry(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    return button;
}

Window::Window(QWidget* parent)
    : QWidget(parent), trayIcon(this) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setFocusPolicy(Qt::WheelFocus);

    envPath = QProcessEnvironment::systemEnvironment().value("PATH");
    label = BuildLabel(this);
    button = BuildButton(this);

    UpdateStringsAndIcons();
    GetCurrentStatus();

    connect(button, SIGNAL(clicked()), this, SLOT(ToggleStatus()));
    trayIcon.ConnectActivationSlot(this, SLOT(SystemTrayActivated(QSystemTrayIcon::ActivationReason)));
}

void Window::GetCurrentStatus() {
    bool previousStatus = status;
    QProcess process;
    process.start("nvx", QStringList() << "status");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    status = output.contains("on");
    if (status != previousStatus)
        UpdateStringsAndIcons();
}

void Window::UpdateStringsAndIcons() {
    labelString = status ? "nvidia GPU is currently on" : "nvidia GPU is currently off";
    label->setText(labelString.c_str());
    buttonString = status ? "Toggle off" : "Toggle on";
    button->setText(buttonString.c_str());
    trayIcon.UpdateIcon(status);
}

void Window::ToggleStatus() {
    QString newStatus = status ? "off" : "on";
    QVariantMap args;
    args[ACTION_STATUS_PATH] = newStatus;
    args[ACTION_ENV_PATH] = envPath;

    KAuth::Action toggleAction(ACTION_ID);
    toggleAction.setHelperId(ACTION_HELPER_ID);
    toggleAction.setArguments(args);
    KAuth::ExecuteJob* toggleJob = toggleAction.execute();
    toggleJob->exec();

    GetCurrentStatus();
}

void Window::SystemTrayActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger && !isVisible()) {
        GetCurrentStatus();
        show();
        activateWindow();
        raise();
    }
}

// QWidget interface
void Window::focusInEvent(QFocusEvent* event) {
    QWidget::focusInEvent(event);
    GetCurrentStatus();
}

void Window::closeEvent(QCloseEvent* event) {
    if (!event->spontaneous() || !isVisible())
        return;
    if (trayIcon.isVisible()) {
        hide();
        event->ignore();
    }
}

bool Window::event(QEvent* event) {
    if (event->type() == QEvent::WindowStateChange && isMinimized()) {
        hide();
        event->ignore();
        return true;
    }
    return QWidget::event(event);
}
