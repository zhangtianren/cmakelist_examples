#include "testsigslot.h"

#include "sigslot_cpp.h"


#include <iostream>
using namespace std;

class Emitter {
    public:
        Signal<int> the_signal;

        void do_emit(int value)
        {
            the_signal.emit(value);
        }
};

class Receiver: public SigSlotBase
{
    public:
        void slot(int v)
        {
            cout << "Yay! " << v << endl;
        }
};

void test_sigslot_cpp()
{
    // Create both an emitting and receiving instance
    Emitter em;
    Receiver recv;

    // Bind the slot to the signal
    em.the_signal.bind(&Receiver::slot, &recv);

    // Emit
    em.do_emit(42);
}

