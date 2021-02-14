#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\linkedlist.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\pQueue.h"
#include"Motorcycle.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	///////////////////////// MotorCycles /////////////////////////////
	Queue<Motorcycle*> NMotA;
	Queue<Motorcycle*> NMotB;
	Queue<Motorcycle*> NMotC;
	Queue<Motorcycle*> NMotD;
	Queue<Motorcycle*> FMotA;
	Queue<Motorcycle*> FMotB;
	Queue<Motorcycle*> FMotC;
	Queue<Motorcycle*> FMotD;
	Queue<Motorcycle*> VMotA;
	Queue<Motorcycle*> VMotB;
	Queue<Motorcycle*> VMotC;
	Queue<Motorcycle*> VMotD;

	//////////////////////// Orders //////////////////////////

	pQueue<Order*> VOrdA;
	pQueue<Order*> VOrdB;
	pQueue<Order*> VOrdC;
	pQueue<Order*> VOrdD;
	Queue<Order *> FOrdA;
	Queue<Order *> FOrdB;
	Queue<Order *> FOrdC;
	Queue<Order *> FOrdD;
	linkedlist<Order *> NOrdA;
	linkedlist<Order *> NOrdB;
	linkedlist<Order *> NOrdC;
	linkedlist<Order *> NOrdD;

	pQueue<Order*> Done;     
	Queue<Motorcycle*> InServe;
	Event *Eve;
	Motorcycle * Mot;
	int mna, mnb, mnc, mnd, mfa, mfb, mfc, mfd, mva, mvb, mvc, mvd; //number of motorcycles for each type by region
	int Prom_Limit;
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Restaurant();
	~Restaurant();
	void clearall();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void AddNOrder(Order* pord);
	void AddFOrder(Order *pord);
	void AddVOrder(Order* pord);
	void AddVMot(Motorcycle *mot);
	void AddFMot(Motorcycle *mot);
	void AddNMot(Motorcycle *mot);
	void FileLoading();
	void PrintOrders();
	void AssignOrdersA(int);
	void AssignOrdersB(int);
	void AssignOrdersC(int);
	void AssignOrdersD(int);
	void MotBack(int);
	void SetStatusBar();//takes the Current Time Step as a parameter.
	bool getNOrdbyId(Order*&, int);
	void Auto_Promotion(int);
	void OutputFile();
	void Interactive();
	void Step_by_step(); 
	void Silent();


	//////////////////////////////////////////////////////////////////////////
	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 
	


	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif