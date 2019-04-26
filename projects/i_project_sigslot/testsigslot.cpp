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


#include "sigslot.h"

#include "sigslot.h"
#include <iostream>

class CSender
{
public:
	sigslot::signal0<> Click0;
	sigslot::signal1<int> Click1;
};

class CReceiver : public sigslot::has_slots<>
{
public:
	void OnClick0()
	{
		std::cout << "OnClick0..." << std::endl;
	}

	virtual void OnClick1(int a)
	{
		std::cout << "OnClick1 " << a << " ..." << std::endl;
	}
};

class CDeliver : public CReceiver
{
public:
	void OnClick0()
	{
		std::cout << "CDeliver OnClick0..." << std::endl;
	}

	virtual void OnClick1(int a)
	{
		std::cout << "CDeliver OnClick1 " << a << " ..." << std::endl;
	}
};

void test_sigslot_c()
{
	CReceiver recv;
	CDeliver deliver;
	CSender sender;

	sender.Click0.connect(&recv, &CReceiver::OnClick0);
	sender.Click1.connect(&recv, &CReceiver::OnClick1);
	sender.Click1.connect(&deliver, &CDeliver::OnClick1);

	sender.Click0();
	sender.Click1(2);

	sender.Click0.disconnect_all();
	sender.Click1.disconnect(&deliver);

	sender.Click0();
	sender.Click1(2);
}