#ifndef MTPWORKER_H
#define MTPWORKER_H

#include <QObject>
#include <QTimer>
#include <QVariantList>
#include <QProcess>
#include <QRegularExpression>
#include <QSet>
#include <QDebug>

class MtpWorker : public QObject
{
    Q_OBJECT
public:
    explicit MtpWorker(QObject *parent = nullptr);

public slots:
    void start();
    void scan();

signals:
    void devicesFound(QVariantList devices);

private:
    QTimer *m_timer;
};

#endif // MTPWORKER_H
