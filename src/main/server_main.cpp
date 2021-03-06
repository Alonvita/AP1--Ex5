/**
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class server_main.
 *
 * Creates and runs a server.
 */

#include "../easy_logging/easylogging++.h"
_INITIALIZE_EASYLOGGINGPP

#include "../server/server_side/Server.h"

using namespace std;

int main() {
    Server server(8000);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}