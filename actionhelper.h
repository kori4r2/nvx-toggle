#pragma once
#include <QObject>
#include <QProcess>
#include <KAuth>

#define ACTION_STATUS_PATH "toggleStatus"

using namespace KAuth;

class ActionHelper : public QObject {
    Q_OBJECT
public:
    explicit ActionHelper(QObject *parent = nullptr);

public Q_SLOTS:
    KAuth::ActionReply toggle(const QVariantMap &args);
};
