#include "trayicon.h"
#include <QStyle>
#include <QApplication>

TrayIcon::TrayIcon(QWidget* _window) {
	this->window = _window;
	SetupTrayIcon();
	SetupTrayActions();
	trayIcon->setToolTip("show " + QCoreApplication::applicationName());
	trayIcon->show();
}

void TrayIcon::ConnectActivationSlot(QObject* receiver, const char* member) {
	window->connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), receiver, member);
}

void TrayIcon::UpdateIcon(bool isActive) {
	if (isActive)
		trayIcon->setIcon(activeTrayIcon);
	else
		trayIcon->setIcon(inactiveTrayIcon);
}

bool TrayIcon::isVisible() {
	return trayIcon->isVisible();
}

void TrayIcon::SetupTrayIcon() {
	trayIcon = new QSystemTrayIcon(window);
	QStyle* style = window->style();
	activeTrayIcon = style->standardIcon(style->SP_MediaPlay);
	inactiveTrayIcon = style->standardIcon(style->SP_MediaPause);
	UpdateIcon(false);
}

void TrayIcon::SetupTrayActions() {
	trayIconMenu = new QMenu(window);
	quitAction = new QAction(QObject::tr("&Quit"), window);
	window->connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
	trayIconMenu->addAction(quitAction);
	trayIcon->setContextMenu(trayIconMenu);
}
