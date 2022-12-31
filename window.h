#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSystemTrayIcon>
#include <cstring>

class Window : public QWidget {
public:
    explicit Window(QWidget *parent = nullptr);

private:
    Q_OBJECT
    QPushButton *button;
    QLabel *label;
    QSystemTrayIcon *trayIcon;
    std::string labelString;
    std::string buttonString;
    void GetCurrentStatus();
    void UpdateStrings();
    bool status;

private slots:
    void ToggleStatus();
    void SystemTrayActivated(QSystemTrayIcon::ActivationReason reason);

signals:


    // QWidget interface
protected:
    void focusInEvent(QFocusEvent *event);

    // QWidget interface
public:
    bool event(QEvent *event);
};
