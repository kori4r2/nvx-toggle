#include "trayicon.h"
#include <QStyle>
#include <QApplication>

TrayIcon::TrayIcon(QWidget* _window) {
	this->window = _window;

	trayIcon = new QSystemTrayIcon(window);

	QStyle* style = window->style();
	QIcon icon = style->standardIcon(style->SP_DriveHDIcon);
	trayIcon->setIcon(icon);

	trayIconMenu = new QMenu(window);
	quitAction = new QAction(QObject::tr("&Quit"), window);
	window->connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
	trayIconMenu->addAction(quitAction);
	trayIcon->setContextMenu(trayIconMenu);

	trayIcon->setToolTip("show " + QCoreApplication::applicationName());
	trayIcon->show();
}

void TrayIcon::ConnectActivationSlot(QObject* receiver, const char* member) {
	window->connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), receiver, member);
}

bool TrayIcon::isVisible() {
	return trayIcon->isVisible();
}
