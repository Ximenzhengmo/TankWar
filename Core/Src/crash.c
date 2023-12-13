#include "bullet.h"

const CrashTest_T crashTest_bullet[20]={{.addpoint=AddPoint_0,.number=90}, {.addpoint=AddPoint_18,.number=30},
                                        {.addpoint=AddPoint_36,.number=27}, {.addpoint=AddPoint_54,.number=29},
                                        {.addpoint=AddPoint_72,.number=29},
                                        {.addpoint=AddPoint_90,.number=90}, {.addpoint=AddPoint_108,.number=30},
                                        {.addpoint=AddPoint_126,.number=27}, {.addpoint=AddPoint_144,.number=29},
                                        {.addpoint=AddPoint_162,.number=29},
                                        {.addpoint=AddPoint_180,.number=90}, {.addpoint=AddPoint_198,.number=30},
                                        {.addpoint=AddPoint_216,.number=27}, {.addpoint=AddPoint_234,.number=29},
                                        {.addpoint=AddPoint_252,.number=29},
                                        {.addpoint=AddPoint_270,.number=90}, {.addpoint=AddPoint_288,.number=30},
                                        {.addpoint=AddPoint_306,.number=27}, {.addpoint=AddPoint_324,.number=29},
                                        {.addpoint=AddPoint_342,.number=29},
};

const CrashTest_T crashTest_target = {
        .addpoint=AddPoint_target,
        .number=20,
        };

const Point_T AddPoint_0[]= {
        {-9,-8},{-8,-8},{-7,-8},{-6,-8},{-5,-8},{-4,-8},
        {-3,-8},{-2,-8},{-1,-8},{0,-8},{1,-8},{2,-8},
        {3,-8},{4,-8},{5,-8},{6,-8},{7,-8},{8,-8},
        {9,-8},{10,-8},
        {10,-8},{10,-7},{10,-6},{10,-5},{10,-4},{10,-3},
        {10,-2},{10,-1},{10,0},{10,1},{10,2},{10,3},
        {10,4},{10,5},{10,6},{10,7},{10,8},{10,9},
        {10,10},{10,11},{10,12},{10,13},{10,14},{10,15},
        {10,16},
        {-9,16},{-8,16},{-7,16},{-6,16},{-5,16},{-4,16},
        {-3,16},{-2,16},{-1,16},{0,16},{1,16},{2,16},
        {3,16},{4,16},{5,16},{6,16},{7,16},{8,16},
        {9,16},{10,16},
        {-9,-8},{-9,-7},{-9,-6},{-9,-5},{-9,-4},{-9,-3},
        {-9,-2},{-9,-1},{-9,0},{-9,1},{-9,2},{-9,3},
        {-9,4},{-9,5},{-9,6},{-9,7},{-9,8},{-9,9},
        {-9,10},{-9,11},{-9,12},{-9,13},{-9,14},{-9,15},
        {-9,16},
};

const Point_T AddPoint_18[30]={
        {-11,-5},{-8,-6},{-5,-7},{-2,-8},{1,-9},{4,-10},
        {7,-11},{8,-10},{9,-7},{10,-4},{11,-1},{12,2},
        {13,5},{14,8},{15,11},{14,14},{11,15},{8,16},
        {5,17},{2,18},{-1,19},{-4,18},{-6,15},{-6,15},
        {-7,12},{-8,9},{-9,6},{-10,3},{-11,0},{-12,-3},
};

const Point_T AddPoint_36[]={
        {-13,-4},{-10,-6},{-7,-8},{-4,-10},{-1,-12},{2,-14},
        {4,-13},{6,-10},{8,-7},{10,-4},{12,-1},{14,2},
        {16,5},{17,8},{14,10},{11,12},{8,14},{5,16},
        {2,18},{-1,18},{-3,16},{-5,13},{-7,10},{-9,7},{-12,3},
        {-14,0},{-15,-2}
};

const Point_T AddPoint_54[]={
        {-13,2},{-11,-1},{-9,-4},{-7,-7},{-5,-10},{-3,-13},
        {-2,-14},{1,-12},{4,-10},{7,-8},{10,-6},{13,-4},
        {16,-2},{19,0},{19,2},{17,4},
        {15,6},{14,8},{12,10},{10,13},{8,16},
        {6,17},{3,15},{0,13},{-3,11},
        {-6,9},{-9,7},{-11,5},{-13,2}
};

const Point_T AddPoint_72[]={
        {-11,4},{-10,1},{-9,-2},{-8,-5},{-7,-8},{-6,-11},
        {-4,-13},{-1,-12},{2,-11},{5,-10},{8,-9},{11,-8},
        {14,-7},{17,-6},{19,-4},{18,-1},{17,2},{16,5},
        {15,8},{14,11},{13,14},{9,14},{6,13},{3,12},{0,11},{-3,10},{-6,9},
        {-9,8},{-12,7},
};

const Point_T AddPoint_90[]={
        {-8,9},{-8,8},{-8,7},{-8,6},{-8,5},{-8,4},
        {-8,3},{-8,2},{-8,1},{-8,0},{-8,-1},{-8,-2},
        {-8,-3},{-8,-4},{-8,-5},{-8,-6},{-8,-7},{-8,-8},
        {-8,-9},{-8,-10},{-8,-10},{-7,-10},{-6,-10},{-5,-10},
        {-4,-10},{-3,-10},{-2,-10},{-1,-10},{0,-10},{1,-10},
        {2,-10},{3,-10},{4,-10},{5,-10},{6,-10},{7,-10},
        {8,-10},{9,-10},{10,-10},{11,-10},{12,-10},{13,-10},
        {14,-10},{15,-10},{16,-10},{16,9},{16,8},{16,7},
        {16,6},{16,5},{16,4},{16,3},{16,2},{16,1},
        {16,0},{16,-1},{16,-2},{16,-3},{16,-4},{16,-5},
        {16,-6},{16,-7},{16,-8},{16,-9},{16,-10},{-8,9},
        {-7,9},{-6,9},{-5,9},{-4,9},{-3,9},{-2,9},
        {-1,9},{0,9},{1,9},{2,9},{3,9},{4,9},
        {5,9},{6,9},{7,9},{8,9},{9,9},{10,9},
        {11,9},{12,9},{13,9},{14,9},{15,9},{16,9},
};

const Point_T  AddPoint_108[]={
        {-5,11},{-6,8},{-7,5},{-8,2},{-9,-1},{-10,-4},
        {-11,-7},{-10,-8},{-7,-9},{-4,-10},{-1,-11},{2,-12},
        {5,-13},{8,-14},{11,-15},{14,-14},{15,-11},{16,-8},
        {17,-5},{18,-2},{19,1},{18,4},{15,6},{15,6},
        {12,7},{9,8},{6,9},{3,10},{0,11},{-3,12},
};

const Point_T AddPoint_126[]={
        {-4,13},{-6,10},{-8,7},{-10,4},{-12,1},{-14,-2},
        {-13,-4},{-10,-6},{-7,-8},{-4,-10},{-1,-12},{2,-14},
        {5,-16},{8,-17},{10,-14},{12,-11},{14,-8},{16,-5},
        {18,-2},{18,1},{16,3},{13,5},{10,7},{7,9},
        {3,12},{0,14},{-2,15}
};

const Point_T AddPoint_144[]={
        {2,13},{-1,11},{-4,9},{-7,7},{-10,5},{-13,3},
        {-14,2},{-12,-1},{-10,-4},{-8,-7},{-6,-10},{-4,-13},
        {-2,-16},{0,-19},{2,-19},{4,-17},{6,-15},{8,-14},
        {10,-12},{13,-10},{16,-8},{17,-6},{15,-3},{13,0},
        {11,3},{9,6},{7,9},{5,11},{2,13},
};

const Point_T AddPoint_162[]={
        {4,11},{1,10},{-2,9},{-5,8},{-8,7},{-11,6},
        {-13,4},{-12,1},{-11,-2},{-10,-5},{-9,-8},{-8,-11},
        {-7,-14},{-6,-17},{-4,-19},{-1,-18},{2,-17},{5,-16},
        {8,-15},{11,-14},{14,-13},{14,-9},{13,-6},{12,-3},
        {11,0},{10,3},{9,6},{8,9},{7,12},
};

const Point_T AddPoint_180[]={
        {9,8},{8,8},{7,8},{6,8},{5,8},{4,8},
        {3,8},{2,8},{1,8},{0,8},{-1,8},{-2,8},
        {-3,8},{-4,8},{-5,8},{-6,8},{-7,8},{-8,8},
        {-9,8},{-10,8},{-10,8},{-10,7},{-10,6},{-10,5},
        {-10,4},{-10,3},{-10,2},{-10,1},{-10,0},{-10,-1},
        {-10,-2},{-10,-3},{-10,-4},{-10,-5},{-10,-6},{-10,-7},
        {-10,-8},{-10,-9},{-10,-10},{-10,-11},{-10,-12},{-10,-13},
        {-10,-14},{-10,-15},{-10,-16},{9,-16},{8,-16},{7,-16},
        {6,-16},{5,-16},{4,-16},{3,-16},{2,-16},{1,-16},
        {0,-16},{-1,-16},{-2,-16},{-3,-16},{-4,-16},{-5,-16},
        {-6,-16},{-7,-16},{-8,-16},{-9,-16},{-10,-16},{9,8},
        {9,7},{9,6},{9,5},{9,4},{9,3},{9,2},
        {9,1},{9,0},{9,-1},{9,-2},{9,-3},{9,-4},
        {9,-5},{9,-6},{9,-7},{9,-8},{9,-9},{9,-10},
        {9,-11},{9,-12},{9,-13},{9,-14},{9,-15},{9,-16},
};

const Point_T AddPoint_198[]={
        {11,5},{8,6},{5,7},{2,8},{-1,9},{-4,10},
        {-7,11},{-8,10},{-9,7},{-10,4},{-11,1},{-12,-2},
        {-13,-5},{-14,-8},{-15,-11},{-14,-14},{-11,-15},{-8,-16},
        {-5,-17},{-2,-18},{1,-19},{4,-18},{6,-15},{6,-15},
        {7,-12},{8,-9},{9,-6},{10,-3},{11,0},{12,3},
};

const Point_T AddPoint_216[]={
        {13,4},{10,6},{7,8},{4,10},{1,12},{-2,14},
        {-4,13},{-6,10},{-8,7},{-10,4},{-12,1},{-14,-2},
        {-16,-5},{-17,-8},{-14,-10},{-11,-12},{-8,-14},{-5,-16},
        {-2,-18},{1,-18},{3,-16},{5,-13},{7,-10},{9,-7},
        {12,-3},{14,0},{15,2}
};

const Point_T AddPoint_234[]={
        {13,-2},{11,1},{9,4},{7,7},{5,10},{3,13},
        {2,14},{-1,12},{-4,10},{-7,8},{-10,6},{-13,4},
        {-16,2},{-19,0},{-19,-2},{-17,-4},{-15,-6},{-14,-8},
        {-12,-10},{-10,-13},{-8,-16},{-6,-17},{-3,-15},{0,-13},
        {3,-11},{6,-9},{9,-7},{11,-5},{13,-2},
};

const Point_T AddPoint_252[]={
        {11,-4},{10,-1},{9,2},{8,5},{7,8},{6,11},
        {4,13},{1,12},{-2,11},{-5,10},{-8,9},{-11,8},
        {-14,7},{-17,6},{-19,4},{-18,1},{-17,-2},{-16,-5},
        {-15,-8},{-14,-11},{-13,-14},{-9,-14},{-6,-13},{-3,-12},
        {0,-11},{3,-10},{6,-9},{9,-8},{12,-7},
};

const Point_T AddPoint_270[]={
        {8,-9},{8,-8},{8,-7},{8,-6},{8,-5},{8,-4},
        {8,-3},{8,-2},{8,-1},{8,0},{8,1},{8,2},
        {8,3},{8,4},{8,5},{8,6},{8,7},{8,8},
        {8,9},{8,10},{8,10},{7,10},{6,10},{5,10},
        {4,10},{3,10},{2,10},{1,10},{0,10},{-1,10},
        {-2,10},{-3,10},{-4,10},{-5,10},{-6,10},{-7,10},
        {-8,10},{-9,10},{-10,10},{-11,10},{-12,10},{-13,10},
        {-14,10},{-15,10},{-16,10},{-16,-9},{-16,-8},{-16,-7},
        {-16,-6},{-16,-5},{-16,-4},{-16,-3},{-16,-2},{-16,-1},
        {-16,0},{-16,1},{-16,2},{-16,3},{-16,4},{-16,5},
        {-16,6},{-16,7},{-16,8},{-16,9},{-16,10},{8,-9},
        {7,-9},{6,-9},{5,-9},{4,-9},{3,-9},{2,-9},
        {1,-9},{0,-9},{-1,-9},{-2,-9},{-3,-9},{-4,-9},
        {-5,-9},{-6,-9},{-7,-9},{-8,-9},{-9,-9},{-10,-9},
        {-11,-9},{-12,-9},{-13,-9},{-14,-9},{-15,-9},{-16,-9},
};

const Point_T AddPoint_288[]={
        {5,-11},{6,-8},{7,-5},{8,-2},{9,1},{10,4},
        {11,7},{10,8},{7,9},{4,10},{1,11},{-2,12},
        {-5,13},{-8,14},{-11,15},{-14,14},{-15,11},{-16,8},
        {-17,5},{-18,2},{-19,-1},{-18,-4},{-15,-6},{-15,-6},
        {-12,-7},{-9,-8},{-6,-9},{-3,-10},{0,-11},{3,-12},
};

const Point_T AddPoint_306[]={
        {4,-13},{6,-10},{8,-7},{10,-4},{12,-1},{14,2},
        {13,4},{10,6},{7,8},{4,10},{1,12},{-2,14},
        {-5,16},{-8,17},{-10,14},{-12,11},{-14,8},{-16,5},
        {-18,2},{-18,-1},{-16,-3},{-13,-5},{-10,-7},{-7,-9},
        {-3,-12},{0,-14},{2,-15}
};

const Point_T AddPoint_324[]={
        {-2,-13},{1,-11},{4,-9},{7,-7},{10,-5},{13,-3},
        {14,-2},{12,1},{10,4},{8,7},{6,10},{4,13},
        {2,16},{0,19},{-2,19},{-4,17},{-6,15},{-8,14},
        {-10,12},{-13,10},{-16,8},{-17,6},{-15,3},{-13,0},
        {-11,-3},{-9,-6},{-7,-9},{-5,-11},{-2,-13},
};

const Point_T AddPoint_342[]={
        {-4,-11},{-1,-10},{2,-9},{5,-8},{8,-7},{11,-6},
        {13,-4},{12,-1},{11,2},{10,5},{9,8},{8,11},
        {7,14},{6,17},{4,19},{1,18},{-2,17},{-5,16},
        {-8,15},{-11,14},{-14,13},{-14,9},{-13,6},{-12,3},
        {-11,0},{-10,-3},{-9,-6},{-8,-9},{-7,-12},
};

const Point_T AddPoint_target[]={
        {0,8},{3,7},{5,6},{7,4},{8,2},
        {8,0},{3,-7},{5,-6},{7,-4},{8,-2},
        {0,-8},{-3,-7},{-5,-6},{-7,-4},{-8,-2},
        {-8,0},{-3,7},{-5,6},{-7,4},{-8,2},
};
