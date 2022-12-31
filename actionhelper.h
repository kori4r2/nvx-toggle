#pragma once

#include <QObject>
#include <QProcess>
#include <KAuth/Action>
#include <KAuth/ActionReply>
#include <KAuth/ExecuteJob>
#include <KAuth/HelperSupport>

class ActionHelper: public QObject {
    Q_OBJECT

public Q_SLOTS:
    KAuth::ActionReply toggle(const QVariantMap& args);
};
