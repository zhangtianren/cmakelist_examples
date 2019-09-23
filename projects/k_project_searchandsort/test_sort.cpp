
#include "test_sort.h"
#include "sort.h"
#include <iostream>
#include "util.h"


namespace sort
{

int test_sort15_01[] = {76, 13, -81, 62, 95, 88, -5, 87, 3, -39, 65, 52, 17, 1, 85};
int test_sort15_02[] = {49, -56, -12, -53, -55, 61, 81, 47, -95, -40, 86, 5, 80, 60, -33};

int test_sort10_03[] = {-18, 30, 29, 3, -27, 5, -24, 28, 19, -9};
int test_sort10_04[] = {-16, 24, 8, 25, 29, 15, 7, 3, 14, 4};
int test_sort10_05[] = {0, -19, 18, 20, 21, 23, 2, 2, 1, 12};
int test_sort10_06[] = {-12, 20, 8, -24, -18, -23, 3, -21, 11, -11};
int test_sort10_07[] = {23, 28, -13, -2, 11, 21, -12, 11, 7, -14};

int test_sort10_15[] = {0, 19, 18, 20, 21, 23, 2, 2, 1, 12};
int test_sort10_16[] = {12, 20, 8, 24, 18, 23, 3, 21, 11, 11};
int test_sort10_17[] = {23, 28, 13, 2, 11, 21, 12, 11, 7, 14};

int test_sort500_08[] = {525, 971, 205, 623, 130, 5, 564, 529, 452, 891, 238, 769, 265, 542, 738, 589, 557, 705, 285, 681, 437, 169, 38, 225, 987, 497, 30, 667, 586, 557, 43, 182, 407, 674, 270, 22, 445, 672, 536, 871, 145, 909, 199, 671, 711, 728, 704, 185, 197, 864, 458, 648, 160, 887, 245, 40, 339, 172, 971, 940, 632, 144, 296, 700, 330, 543, 981, 547, 552, 982, 401, 919, 427, 6, 137, 923, 248, 925, 49, 558, 857, 97, 960, 945, 578, 308, 726, 730, 648, 20, 118, 600, 504, 619, 199, 988, 400, 315, 758, 150, 665, 958, 257, 777, 637, 274, 787, 131, 36, 478, 432, 210, 112, 65, 13, 282, 466, 81, 954, 600, 751, 108, 196, 881, 685, 453, 430, 972, 94, 322, 48, 773, 757, 632, 546, 525, 580, 246, 869, 720, 560, 698, 50, 555, 241, 162, 720, 199, 25, 499, 139, 264, 181, 81, 467, 421, 276, 694, 785, 617, 123, 430, 798, 826, 298, 641, 922, 95, 793, 212, 814, 285, 442, 581, 679, 971, 357, 605, 860, 26, 315, 963, 207, 526, 555, 995, 997, 204, 196, 353, 353, 589, 323, 651, 662, 709, 969, 383, 907, 234, 861, 860, 16, 960, 986, 428, 124, 712, 969, 510, 447, 694, 780, 893, 13, 490, 814, 554, 542, 445, 484, 647, 702, 780, 372, 898, 465, 371, 3, 731, 651, 305, 185, 567, 491, 191, 814, 362, 413, 252, 495, 477, 733, 888, 7, 278, 309, 224, 356, 384, 340, 525, 138, 584, 640, 933, 174, 788, 270, 210, 871, 6, 700, 676, 337, 699, 736, 83, 383, 614, 83, 402, 489, 236, 101, 155, 98, 452, 470, 259, 846, 797, 77, 601, 797, 790, 776, 407, 688, 882, 778, 30, 740, 766, 351, 393, 853, 724, 525, 964, 508, 306, 298, 209, 55, 30, 78, 628, 692, 854, 657, 655, 319, 185, 238, 200, 642, 680, 568, 77, 699, 912, 848, 436, 829, 435, 65, 329, 414, 775, 39, 481, 477, 151, 556, 34, 484, 973, 250, 563, 426, 733, 656, 213, 794, 333, 148, 364, 980, 822, 120, 304, 806, 249, 481, 146, 666, 24, 489, 982, 54, 611, 34, 513, 39, 562, 313, 462, 401, 639, 67, 289, 709, 324, 957, 744, 328, 107, 685, 318, 669, 769, 631, 439, 454, 589, 247, 693, 56, 84, 371, 569, 924, 305, 996, 651, 372, 486, 766, 473, 340, 99, 886, 872, 731, 246, 305, 413, 554, 552, 456, 529, 826, 575, 11, 335, 430, 627, 399, 488, 385, 392, 576, 862, 386, 921, 428, 807, 600, 440, 423, 687, 798, 449, 520, 883, 683, 428, 225, 773, 58, 295, 647, 966, 399, 400, 877, 327, 859, 379, 822, 173, 82, 627, 664, 693, 445, 549, 571, 707, 636, 332, 211, 903, 408, 31, 257, 10, 406, 693, 596, 484, 934, 887, 16, 813, 670, 599, 686, 512, 818, 527, 75, 490, 961, 781, 730, 594, 920, 490, 10, 121, 62, 317, 239, 890, 403, 834, 573, 737};


void run_bubble_sort()
{
    Sort::bubble_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::bubble_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::bubble_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::bubble_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}

void run_quick_sort()
{
    Sort::quick_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::quick_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::quick_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::quick_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}

void run_insert_direct_sort()
{
    Sort::insert_direct_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::insert_direct_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::insert_direct_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::insert_direct_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}


void run_insert_binary_sort()
{
    Sort::insert_binary_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::insert_binary_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::insert_binary_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::insert_binary_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}

void run_shell_sort()
{
    Sort::shell_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::shell_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::shell_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::shell_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}

void run_choose_sort()
{
    Sort::choose_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::choose_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::choose_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::choose_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}

void run_heap_sort()
{
    Sort::heap_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::heap_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::heap_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::heap_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}

void run_merge_sort()
{
    Sort::merge_sort(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]));
    printCheckArray(test_sort15_01, sizeof(test_sort15_01) / sizeof(test_sort15_01[0]), true);

    Sort::merge_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    Sort::merge_sort(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]));
    printCheckArray(test_sort10_07, sizeof(test_sort10_07) / sizeof(test_sort10_07[0]), true);

    Sort::merge_sort(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]));
    printCheckArray(test_sort15_02, sizeof(test_sort15_02) / sizeof(test_sort15_02[0]), true);
}


void run_test_sort()
{
    // run_bubble_sort();
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // Sort::bubble_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);


    // run_quick_sort();
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // Sort::quick_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    // run_insert_direct_sort();
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // Sort::insert_direct_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    // run_insert_binary_sort();
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // Sort::insert_binary_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    //run_shell_sort();
    //printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    //Sort::shell_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    //printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    //printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    // run_choose_sort();
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // Sort::choose_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    // run_heap_sort();
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // Sort::heap_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);

    // run_merge_sort();
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // Sort::merge_sort(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]));
    // printCheckArray(test_sort10_03, sizeof(test_sort10_03) / sizeof(test_sort10_03[0]), true);


    //run_merge_sort();
    printArray(test_sort10_15, sizeof(test_sort10_15) / sizeof(test_sort10_15[0]));
    Sort::radix_sort(test_sort10_15, sizeof(test_sort10_15) / sizeof(test_sort10_15[0]));
    printArray(test_sort10_15, sizeof(test_sort10_15) / sizeof(test_sort10_15[0]));
    //printCheckArray(test_sort10_15, sizeof(test_sort10_15) / sizeof(test_sort10_15[0]), true);
}

}
