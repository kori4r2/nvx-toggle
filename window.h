#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSystemTrayIcon>
#include <cstring>

class Window: public QWidget {
    Q_OBJECT

public:
    explicit Window(QWidget* parent = nullptr);

private:
    QLabel* label;
    QPushButton* button;
    QSystemTrayIcon* trayIcon;
    QString envPath;
    std::string labelString;
    std::string buttonString;
    void GetCurrentStatus();
    void UpdateStrings();
    bool status;

private slots:
    void ToggleStatus();
    void SystemTrayActivated(QSystemTrayIcon::ActivationReason reason);

    // QWidget interface
protected:
    void focusInEvent(QFocusEvent* event);

public:
    bool event(QEvent* event);
};
