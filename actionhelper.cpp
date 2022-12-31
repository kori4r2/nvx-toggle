#include "actionhelper.h"

ActionHelper::ActionHelper(QObject *parent)
    : QObject{parent} {
}

ActionReply ActionHelper::toggle(const QVariantMap &args) {
    ActionReply reply;
    QString toggleParameter = args[ACTION_STATUS_PATH].toString();
    QProcess process;
    process.start("nvx", QStringList() << toggleParameter);
    process.waitForFinished();
    return reply;
}

KAUTH_HELPER_MAIN("org.kde.nvx-toggle", ActionHelper);
