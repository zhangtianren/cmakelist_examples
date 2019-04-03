
#include "cpp11_header.h"

int main(void)
{
	test_auto();
	test_nullptr();
	test_for();

	test_array();
	test_forwardlist();
	test_unorderedmap();
	test_unorderedset();

	test_atomic();
	test_unatomic();
	test_threadsync();

	test_sharedptr();
	test_weakptr();

	test_functional();
	test_lamda();
}