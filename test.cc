#include "finite-state-machine/dfa.h"

using namespace std;

int main(int argc, char *argv[])
{

    string chrs;
    cin >> chrs;
    DFA dfa(argv[1], chrs);
    dfa.alphabetInfo();
    dfa.vectorInfo();
    dfa.testString();
    return 0;
}