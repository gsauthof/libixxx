#include <iostream>
#include <ixxx/ixxx.hh>

using namespace ixxx;
using namespace std;

int main(int argc, char **argv)
{
    if (argc<2) { cerr << "Missing argument\n"; return 1; }
    try {
        posix::unlink(argv[1]);
    } catch (const ixxx::sys_error& e) {
        cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
