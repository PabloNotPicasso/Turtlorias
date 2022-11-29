#include <iostream>
#include <fstream>

/**
 * @brief This is example of stream to file redirection
 * 
 * std::ostream::rdbuf() function returns current buffer
 * std::ostream::rdbuf(buffer) function sets \p buffer as buffer to stream data
 */
int main()
{
    // Creating Log File
    std::ofstream logFile("logFile.txt");

    // Old rdbuf - console
    auto oldRdbuf = std::clog.rdbuf();
    std::clog << "Message to console\n";

    // Associate logFile buffer
    std::clog.rdbuf(logFile.rdbuf());
    std::clog << "Message to logFile\n";

    // Return console buffer
    std::clog.rdbuf(oldRdbuf);
    std::clog << "Message to console. Again\n";

    return 0;
}