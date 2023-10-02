#include "Logger/LoggerApi.h"

#include <gtest/gtest.h>

TEST(logger, view)
{
    int iVar = 123;
    bool bVar = true;

    {
        LOG_FUNCTION;
        LOG_INF("Message between Enter - Leave");
    }

    LOG_VRB(
        "Big "
        << "long "
        << "message "
        << "bool:" << bVar << " int:" << iVar);
    LOG_INF(
        "Big "
        << "long "
        << "message "
        << "bool:" << bVar << " int:" << iVar);
    LOG_ERR(
        "Big "
        << "long "
        << "message "
        << "bool:" << bVar << " int:" << iVar);
    LOG_FTL(
        "Big "
        << "long "
        << "message "
        << "bool:" << bVar << " int:" << iVar);
}
