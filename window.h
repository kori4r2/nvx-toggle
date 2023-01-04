#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QMenu>
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
    void UpdateStringsAndIcons();
    QSystemTrayIcon* BuildTrayIcon(Window* window);
    bool status;
    QAction* quitAction;
    QMenu* trayIconMenu;

private slots:
    void ToggleStatus();
    void SystemTrayActivated(QSystemTrayIcon::ActivationReason reason);

    // QWidget interface
protected:
    void focusInEvent(QFocusEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

public:
    bool event(QEvent* event);
};
