
#include "Control.h"

const string Control::rocket_name[ROCKET_NUM] = {"Falcon Heavy", "Starship", "Tie Fighter"};
const string Control::parts[PART_NUM]={"Merlin Engine", "Booster", "Oxidiser Tank", "Fuel Tank", "Vehicle Equipment Bay", "Cyogenic Upper Stage","Cryogenic Main Core", "Fuzzy Dice", "Fairing", "Upper Stage"};

const int Control::max_launches[PART_NUM] = {1, 2, 3, 4, 3, 2, 3, 0, 0, 0};
const int Control::max_days[PART_NUM] = {0, 0, 0, 0, 30, 60, 45, 50, 100, 90};

const string Control::menu[MENU_ITEMS] ={
    "Print all rockets",
    "Print all parts",
    "Launch rocket",
    "Inspect rocket",
    "Launch all rockets", 
    "Inspect all rockets",
    "Inspection report",
    "Advance date",
};

void Control::launch(){

    
    initSpaceW();

    int choice = -1;

    while (choice!= 0){
        cout<<endl<<today<<endl;
        view.menu(menu, MENU_ITEMS, choice);
        switch(choice){
            case 1: sw.printRockets(); break;
            case 2: sw.printParts(); break;
            case 3: launchRocket(); break;
            case 4: inspectRocket(); break;
            case 5: launchAllRockets(); break;
            case 6: inspectAllRockets(); break;
            case 7: inspectionReport(); break;   
            case 8: advanceDay(); break;
        }
    }
    cout<<"exiting program!!!"<<endl;
}

void Control::advanceDay(){
    int num = 0;
    cout<<"How many days to advance?"<<endl;
    view.getNumber(num);
    today+=num;
}

void Control::inspectRocket(){
    cout<<"Enter the number of the rocket to inspect: ";
    int choice;
    view.menu(rocket_name, ROCKET_NUM, choice);
    sw.inspect(rocket_name[choice-1], today+=7); //inspection takes 7 days
}

void Control::inspectAllRockets(){
    today+=7; //inspection takes 7 days
    for (int i = 0; i < ROCKET_NUM; ++i){
        sw.inspect(rocket_name[i], today); 
    }
}

void Control::launchRocket(){
    cout<<"Enter the number of the rocket to launch: ";
    int choice;
    view.menu(rocket_name, ROCKET_NUM, choice);
    sw.launch(rocket_name[choice-1], today+=20); //launch takes 20 days to plan and execute
}

void Control::launchAllRockets(){
    today+=(20); //launch takes 20 days to plan and execute
    for (int i = 0; i < ROCKET_NUM; ++i){
        sw.launch(rocket_name[i], today); 
    }
}

void Control::inspectionReport(){
    sw.inspectionReport(today);
}

void Control::initSpaceW(){
    for (int i = 0; i < ROCKET_NUM; ++i){
        sw.addRocket(rocket_name[i]);
    }

    for (int i = 0; i < PART_NUM; ++i){
        sw.addPart(parts[i], today+=(i*2), max_launches[i], max_days[i]);
    }


    sw.installPart(rocket_name[0],parts[0], today+=1);
    sw.installPart(rocket_name[0],parts[1], today);
    sw.installPart(rocket_name[0],parts[3], today);
    sw.installPart(rocket_name[1],parts[2], today);
    sw.installPart(rocket_name[1],parts[4], today);
    sw.installPart(rocket_name[2],parts[5], today);
    sw.installPart(rocket_name[2],parts[8], today);
    sw.installPart(rocket_name[2],parts[9], today);


}

