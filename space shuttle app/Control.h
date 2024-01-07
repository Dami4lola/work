
#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <string>
#include <iomanip>

#include "View.h"
#include "SpaceW.h"

#define ROCKET_NUM 3
#define PART_NUM 10
#define MENU_ITEMS 8

using namespace std;

class Control {
		
	public:
		Control(): today(2023, 7, 1){}
		void launch();
	
	private:
		View view;
		SpaceW sw;
		void initSpaceW();
		void launchRocket();
		void launchAllRockets();
		void inspectRocket();
		void inspectAllRockets();
		void inspectionReport();
		void advanceDay();

		Date today;

		const static string rocket_name[ROCKET_NUM];
		const static string parts[PART_NUM];
		const static int max_launches[PART_NUM];
		const static int max_days[PART_NUM];
		const static string menu[MENU_ITEMS];
	
};
#endif