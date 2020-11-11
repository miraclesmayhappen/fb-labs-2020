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

int alpha_size = 31;

map<string, int> AlphNum =
{
   {"à", 0},	{"á", 1},	{"â", 2},	{"ã", 3},
   {"ä", 4},	{"å", 5},	{"æ", 6},	{"ç", 7},
   {"è", 8},	{"é", 9},	{"ê", 10},	{"ë", 11},
   {"ì", 12},	{"í", 13},	{"î", 14},	{"ï", 15},
   {"ð", 16},	{"ñ", 17},	{"ò", 18},	{"ó", 19},
   {"ô", 20},	{"õ", 21},	{"ö", 22},	{"÷", 23},
   {"ø", 24},	{"ù", 25},	{"ü", 26},	{"û", 27},
   {"ý", 28},	{"þ", 29},	{"ÿ", 30},

};

map<int, string> NumAlph =
{
   {0,"à"},		{1,"á"},	{2,"â"},	{3,"ã"},
   {4,"ä"},		{5,"å"},	{6,"æ"},	{7,"ç"},
   {8,"è"},		{9,"é"},	{10,"ê"},	{11,"ë"},
   {12,"ì"},	{13,"í"},	{14,"î"},	{15,"ï"},
   {16,"ð"},	{17,"ñ"},	{18,"ò"},	{19,"ó"},
   {20,"ô"},	{21,"õ"},	{22,"ö"},	{23,"÷"},
   {24,"ø"},	{25,"ù"},	{26,"ü"},	{27,"û"},
   {28,"ý"},	{29,"þ"},	{30,"ÿ"},

};




#endif