#include "ByReference.hpp"
#include "TransferOwnership.hpp"
#include "UsefulFunctions.hpp"
#include "SailingShip.hpp"
#include "ParallelAccumulate.hpp"
#include "ThreadLocalStorage.hpp"

int main(int argc, char* argv[])
{
    /**
    * Lessons
    */

    // ByReference br;
    // br.run();

    // TransferOwnership to;
    // to.run();

    // UsefulFunctions uf;
    // uf.run();

    ThreadLocalStorage tls;
    tls.run();

    /**
    * Excercises
    */

    // SailingShip ss;
    // ss.run();

    // ParallelAccumulate pa;
    // pa.run();
}
