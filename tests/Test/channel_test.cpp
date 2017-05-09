#include "channel_test.h"

#include <QtTest>

#include "Phisics/channel.h"

using namespace BattleCity::Phisics;

void CChannelTest::checkAppendFlags()
{
    // Arrange.
    CChannel chan{ CChannel::eC_EnemyTank, CChannel::eC_PlayerProjectile, CChannel::eC_Wall};
    bool resNon = false;
    bool resWall = false;
    bool resPlayerTank = false;
    bool resEnemyTank = false;
    bool resPlayerProjectile = false;
    bool resEnemyProjectile = false;
    bool resSpawn = false;

    // Act.
    resNon = chan.isFlag(CChannel::eC_Non);
    resWall = chan.isFlag(CChannel::eC_Wall);
    resPlayerTank = chan.isFlag(CChannel::eC_PlayerTank);
    resEnemyTank = chan.isFlag(CChannel::eC_EnemyTank);
    resPlayerProjectile = chan.isFlag(CChannel::eC_PlayerProjectile);
    resEnemyProjectile = chan.isFlag(CChannel::eC_EnemyProjectile);
    resSpawn = chan.isFlag(CChannel::eC_Spawn);

    // Assert.
    QVERIFY2(!resNon, "eC_Non must be set to 0.");
    QVERIFY2(resWall, "eC_Wall must be set to 1.");
    QVERIFY2(!resPlayerTank, "eC_PlayerTank must be set to 0.");
    QVERIFY2(resEnemyTank, "eC_EnemyTank must be set to 1.");
    QVERIFY2(resPlayerProjectile, "eC_PlayerProjectile must be set to 1.");
    QVERIFY2(!resEnemyProjectile, "eC_EnemyProjectile must be set to 0.");
    QVERIFY2(!resSpawn, "eC_Spawn must be set to 0.");

}

void CChannelTest::checkRemoveFlags()
{
    // Arrange.
    CChannel chan{CChannel::eC_EnemyTank, CChannel::eC_Spawn, CChannel::eC_Wall, CChannel::eC_EnemyProjectile, CChannel::eC_PlayerProjectile};
    bool resNon = false;
    bool resWall = false;
    bool resPlayerTank = false;
    bool resEnemyTank = false;
    bool resPlayerProjectile = false;
    bool resEnemyProjectile = false;
    bool resSpawn = false;

    // Act.
    chan.removeFlags({CChannel::eC_Wall, CChannel::eC_EnemyTank});
    resNon = chan.isFlag(CChannel::eC_Non);
    resWall = chan.isFlag(CChannel::eC_Wall);
    resPlayerTank = chan.isFlag(CChannel::eC_PlayerTank);
    resEnemyTank = chan.isFlag(CChannel::eC_EnemyTank);
    resPlayerProjectile = chan.isFlag(CChannel::eC_PlayerProjectile);
    resEnemyProjectile = chan.isFlag(CChannel::eC_EnemyProjectile);
    resSpawn = chan.isFlag(CChannel::eC_Spawn);

    // Assert.
    QVERIFY2(!resNon, "eC_Non must be set to 0.");
    QVERIFY2(!resWall, "eC_Wall must be set to 0.");
    QVERIFY2(!resPlayerTank, "eC_PlayerTank must be set to 0.");
    QVERIFY2(!resEnemyTank, "eC_EnemyTank must be set to 0.");
    QVERIFY2(resPlayerProjectile, "eC_PlayerProjectile must be set to 1.");
    QVERIFY2(resEnemyProjectile, "eC_EnemyProjectile must be set to 1.");
    QVERIFY2(resSpawn, "eC_Spawn must be set to 1.");

}

