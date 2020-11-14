#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <Windows.h> //for 1251
#include <iomanip> // for setpresicion
#include <algorithm> // for remove replace
#include <cmath>
#include <utility> //pair


#define BASE_DIR "D:\\cryptolab3\\"

using namespace std;



map<string, int> AlphNum =
{
   {"�", 0},	{"�", 1},	{"�", 2},	{"�", 3},
   {"�", 4},	{"�", 5},	{"�", 6},	{"�", 7},
   {"�", 8},	{"�", 9},	{"�", 10},	{"�", 11},
   {"�", 12},	{"�", 13},	{"�", 14},	{"�", 15},
   {"�", 16},	{"�", 17},	{"�", 18},	{"�", 19},
   {"�", 20},	{"�", 21},	{"�", 22},	{"�", 23},
   {"�", 24},	{"�", 25},	{"�", 26},	{"�", 27},
   {"�", 28},	{"�", 29},	{"�", 30},

};

map<int, string> NumAlph =
{
   {0,"�"},		{1,"�"},	{2,"�"},	{3,"�"},
   {4,"�"},		{5,"�"},	{6,"�"},	{7,"�"},
   {8,"�"},		{9,"�"},	{10,"�"},	{11,"�"},
   {12,"�"},	{13,"�"},	{14,"�"},	{15,"�"},
   {16,"�"},	{17,"�"},	{18,"�"},	{19,"�"},
   {20,"�"},	{21,"�"},	{22,"�"},	{23,"�"},
   {24,"�"},	{25,"�"},	{26,"�"},	{27,"�"},
   {28,"�"},	{29,"�"},	{30,"�"},

};

vector<string> top5bigr = {
	{"��"}, {"��"}, {"��"}, {"��"}, {"��"}

};

int alpha_size = AlphNum.size();

ifstream fin;
ofstream fout;

#endif