#ifndef CHANNEL_TEST_H
#define CHANNEL_TEST_H

#include <QObject>

class CChannelTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void checkAppendFlags();
    void checkRemoveFlags();
};


#endif // CHANNEL_TEST_H
