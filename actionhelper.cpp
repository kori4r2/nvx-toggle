#include "actionhelper.h"
#include "actionIDs.h"
#include <QFile>
#include <QTextStream>

void DebugRun(QProcess* process) {
    QFile file("~/actionHelperDebug.out");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "executed command: " << process->program() << " with arguments: " << process->arguments().join(' ') << Qt::endl;
        stream << "stdout:" << Qt::endl << process->readAllStandardOutput() << Qt::endl;
        stream << "stderr:" << Qt::endl << process->readAllStandardError() << Qt::endl;
        file.close();
    }
}

KAuth::ActionReply ActionHelper::toggle(const QVariantMap& args) {
    KAuth::ActionReply reply;
    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
    env.remove("PATH");
    env.insert("PATH", args[ACTION_ENV_PATH].toString());
    QProcess process;
    process.setProcessEnvironment(env);
    process.start("nvx", QStringList() << args[ACTION_STATUS_PATH].toString());
    process.waitForFinished();
    return reply;
}

KAUTH_HELPER_MAIN(ACTION_HELPER_ID, ActionHelper);
