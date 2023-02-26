#pragma once

#include <QSystemTrayIcon>
#include <QMenu>

class TrayIcon {
public:
	TrayIcon(QWidget* window);
	void ConnectActivationSlot(QObject* receiver, const char* member);
	void UpdateIcon(bool isActive);
	bool isVisible();
private:
	QWidget* window;
	QSystemTrayIcon* trayIcon;
	QAction* quitAction;
	QMenu* trayIconMenu;
	QIcon activeTrayIcon;
	QIcon inactiveTrayIcon;
	void SetupTrayIcon();
	void SetupTrayActions();
};