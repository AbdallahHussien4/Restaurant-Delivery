#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "../Events/CancellationEvent.h"
#include "../Events/PromotionEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}
//////////////////////////////////////    Choose Mode          /////////////////////////////////////////////////////
void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		Step_by_step();
		break;
	case MODE_SLNT:
		Silent();
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

} 
//////////////////////////    1-Interactive Mode Function       //////////////////////////////
void Restaurant::Interactive()
{
	int CurrentTimeStep = 1;

		pGUI->PrintMessage("Inreactive Mode. Enter The Input filename:");
		FileLoading();
			pGUI->PrintMessage("Click To Go To Next Time Step");
		pGUI->waitForClick();
		pGUI->PrintMessage(" ");
		
		while(!EventsQueue.isEmpty()||!VOrdA.isempty()||!VOrdB.isempty()||!VOrdC.isempty()||!VOrdD.isempty()||!FOrdA.isEmpty()||!FOrdB.isEmpty()||!FOrdC.isEmpty()||!FOrdD.isEmpty()||!NOrdA.isempty()||!NOrdB.isempty()||!NOrdC.isempty()||!NOrdD.isempty())
		{
			ExecuteEvents(CurrentTimeStep);
			pGUI->PrintMessage("Time Step: "+to_string(CurrentTimeStep));
			Auto_Promotion(CurrentTimeStep);
			PrintOrders();
			SetStatusBar();
			MotBack(CurrentTimeStep);
			AssignOrdersA(CurrentTimeStep);
			AssignOrdersB(CurrentTimeStep);
			AssignOrdersC(CurrentTimeStep);
			AssignOrdersD(CurrentTimeStep);
			pGUI->waitForClick();
			CurrentTimeStep++;
		}
		pGUI->PrintMessage("Time Step: "+to_string(CurrentTimeStep));
		PrintOrders();
		SetStatusBar();
		pGUI->PrintMessage("Enter Output filename: ");
		OutputFile();
		pGUI->waitForClick();
		pGUI->PrintMessage("Click To End Simulation");
		pGUI->waitForClick();
}

/////////////////////////   2-Step by Step Mode Function   //////////////////

void Restaurant :: Step_by_step()
{
	int CurrentTimeStep = 1;//we start with a time step 1 then we increament.
	
	srand(time(NULL));

		pGUI->PrintMessage("Step By Step Mode. Enter The Input filename:");
		FileLoading();
			pGUI->PrintMessage("Click To Start ");
		pGUI->waitForClick();
		pGUI->PrintMessage(" ");
		
		while(!EventsQueue.isEmpty()||!VOrdA.isempty()||!VOrdB.isempty()||!VOrdC.isempty()||!VOrdD.isempty()||!FOrdA.isEmpty()||!FOrdB.isEmpty()||!FOrdC.isEmpty()||!FOrdD.isEmpty()||!NOrdA.isempty()||!NOrdB.isempty()||!NOrdC.isempty()||!NOrdD.isempty())
		{
			ExecuteEvents(CurrentTimeStep);
			pGUI->PrintMessage("Time Step: "+to_string(CurrentTimeStep));
			Auto_Promotion(CurrentTimeStep);
			PrintOrders();
			SetStatusBar();
			MotBack(CurrentTimeStep);
			AssignOrdersA(CurrentTimeStep);
			AssignOrdersB(CurrentTimeStep);
			AssignOrdersC(CurrentTimeStep);
			AssignOrdersD(CurrentTimeStep);
			Sleep(1000);//wait for one second
			CurrentTimeStep++;	//advance timestep
		}

		pGUI->PrintMessage("Time Step: "+to_string(CurrentTimeStep));
		PrintOrders();
		SetStatusBar();
		Sleep(1000);//wait for one second
		pGUI->PrintMessage("Enter Output filename: ");
		OutputFile();
		pGUI->PrintMessage("Click To End Simulation");
		pGUI->waitForClick();
}
/////////////////////////////// 3-Silent Mode Function //////////////////////////////////////////
void Restaurant::Silent()
{
	int CurrentTimeStep = 1;//we start with a time step 1 then we increament.

	srand(time(NULL));

	pGUI->PrintMessage("Silent Mode. Enter The Input filename:");
	FileLoading();

	while (!EventsQueue.isEmpty() || !VOrdA.isempty() || !VOrdB.isempty() || !VOrdC.isempty() || !VOrdD.isempty() || !FOrdA.isEmpty() || !FOrdB.isEmpty() || !FOrdC.isEmpty() || !FOrdD.isEmpty() || !NOrdA.isempty() || !NOrdB.isempty() || !NOrdC.isempty() || !NOrdD.isempty())
	{
		ExecuteEvents(CurrentTimeStep);
		Auto_Promotion(CurrentTimeStep);
		MotBack(CurrentTimeStep);
		AssignOrdersA(CurrentTimeStep);
		AssignOrdersB(CurrentTimeStep);
		AssignOrdersC(CurrentTimeStep);
		AssignOrdersD(CurrentTimeStep);

		CurrentTimeStep++;	//advance timestep
	}

	pGUI->PrintMessage("Enter Output filename: ");
	OutputFile();
	pGUI->PrintMessage("Click To End Simulation");
	pGUI->waitForClick();
}
///////////////////////////////// File Loading Function /////////////////////////////
void Restaurant:: FileLoading()
{
	string s=pGUI->GetString();
	ifstream file;
	int NS,FS,VS;
	int arr[12];
	file.open(s+".txt",ios::in);
	if(!file.is_open())
	{              ////////// check the validity of file
		pGUI->PrintMessage("UnFounded file");
		return ;
	}
	
	file>>NS>>FS>>VS;
	mna = 0; mnb = 0; mnc = 0; mnd = 0; mfa = 0; mfb = 0; mfc = 0; mfd = 0; mva = 0; mvb = 0; mvc = 0; mvd=0;
	for(int i=0;i<12;i++)
	{
		file>>arr[i];
		if(i%3==0) //Normal
		{
			for (int j = 0; j < arr[i]; j++)
			{
			
				Mot = new Motorcycle(j + 1, TYPE_NRM, NS);
				if (i == 0) {
					mna++;;
					Mot->setRegion(A_REG);
				}
				else if (i == 3) {
					mnb++;
					Mot->setRegion(B_REG);
				}
				else if (i == 6) {
					mnc++;
					Mot->setRegion(C_REG);
				}
				else if (i == 9) {
					mnd++;
					Mot->setRegion(D_REG);
				}
				AddNMot(Mot);
			}
		}
		else if (i % 3 == 1) //Frozen
		{
			for (int j = 0; j < arr[i]; j++)
			{
				Mot = new Motorcycle(j + 1, TYPE_FROZ, FS);
				if (i == 1) {
					mfa++;
					Mot->setRegion(A_REG);
				}
				else if (i == 4) {
					mfb++;
					Mot->setRegion(B_REG);
				}
				else if (i == 7) {
					mfc++;
					Mot->setRegion(C_REG);
				}
				else if (i == 10) {
					mfd++;
					Mot->setRegion(D_REG);
				}
				AddFMot(Mot);
			}
		}
		else if (i % 3 == 2)
		{
			for (int j = 0; j < arr[i]; j++)
			{
				Mot = new Motorcycle(j + 1, TYPE_VIP, VS);
				if (i == 2) {
					mva++;
					Mot->setRegion(A_REG);
				}
				else if (i == 5) {
					mvb++;
					Mot->setRegion(B_REG);
				}
				else if (i == 8) {
					mvc++;
					Mot->setRegion(C_REG);
				}
				else if (i == 11) {
					mvd++;
					Mot->setRegion(D_REG);
				}
				AddVMot(Mot);
			}
		}
			
	}
	int P,num;
	char x;
	file >> P>>num;  //Promotion Limit
	Prom_Limit=P;
	int ArrivalTime, ID, DST, MON,extra;
	char TYP, REG;
	for (int i = 0; i < num; i++)
	{
		file >>x;
		if (x == 'R')
		{
			file >> ArrivalTime >> TYP >> ID >> DST >> MON >> REG;
			if (TYP == 'N'&&REG == 'A')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_NRM, A_REG, MON, DST);
			else if (TYP == 'N'&&REG == 'B')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_NRM, B_REG, MON, DST);
			else if (TYP == 'N'&&REG == 'C')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_NRM, C_REG, MON, DST);
			else if (TYP == 'N'&&REG == 'D')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_NRM, D_REG, MON, DST);
			else if (TYP == 'F'&&REG == 'A')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_FROZ, A_REG, MON, DST);
			else if (TYP == 'F'&&REG == 'B')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_FROZ, B_REG, MON, DST);
			else if (TYP == 'F'&&REG == 'C')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_FROZ, C_REG, MON, DST);
			else if (TYP == 'F'&&REG == 'D')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_FROZ, D_REG, MON, DST);
			else if (TYP == 'V'&&REG == 'A')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_VIP, A_REG, MON, DST);
			else if (TYP == 'V'&&REG == 'B')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_VIP, B_REG, MON, DST);
			else if (TYP == 'V'&&REG == 'C')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_VIP, C_REG, MON, DST);
			else if (TYP == 'V'&&REG == 'D')
				Eve = new ArrivalEvent(ArrivalTime, ID, TYPE_VIP, D_REG, MON, DST);
							AddEvent(Eve);
		}
		else if (x == 'X')
		{
			file >> ArrivalTime >> ID;
			Eve = new CancellationEvent(ArrivalTime, ID);

			AddEvent(Eve);
		}
		else if(x=='P')
		{
			file>>ArrivalTime>>ID>>extra;
			Eve=new PromotionEvent(ArrivalTime,ID,extra);
			AddEvent(Eve);
		}
	}
	
}
/////////////////////////////// Add Orders And MotorCycles To Data Structures /////////////////////////////////
void Restaurant::AddNOrder(Order*ord)
{
	if(ord->GetRegion()==A_REG)
		NOrdA.pushback(ord);
	else if(ord->GetRegion()==B_REG)
		NOrdB.pushback(ord);
	else if(ord->GetRegion()==C_REG)
		NOrdC.pushback(ord);
	else NOrdD.pushback(ord);
}

void Restaurant::AddFOrder(Order*ord)
{
	if(ord->GetRegion()==A_REG)
		FOrdA.enqueue(ord);
	else if(ord->GetRegion()==B_REG)
		FOrdB.enqueue(ord);
	else if(ord->GetRegion()==C_REG)
		FOrdC.enqueue(ord);
	else FOrdD.enqueue(ord);
}
void Restaurant::AddVOrder(Order*ord)
{
	int p=(ord->getmoney())/(ord->GetDistance()*ord->getArrTime()) ;
	if(ord->GetRegion()==A_REG)
		VOrdA.enqueue(ord,p);
	else if(ord->GetRegion()==B_REG)
		VOrdB.enqueue(ord,p);
	else if(ord->GetRegion()==C_REG)
		VOrdC.enqueue(ord,p);
	else VOrdD.enqueue(ord,p);
}

void Restaurant::AddVMot(Motorcycle*mot) {
	if (mot->getRegion() == A_REG)
		VMotA.enqueue(mot);
	else if (mot->getRegion() == B_REG)
		VMotB.enqueue(mot);
	else if (mot->getRegion() == C_REG)
		VMotC.enqueue(mot);
	else VMotD.enqueue(mot);
}

void Restaurant::AddFMot(Motorcycle*mot) {
	if (mot->getRegion() == A_REG)
		FMotA.enqueue(mot);
	else if (mot->getRegion() == B_REG)
		FMotB.enqueue(mot);
	else if (mot->getRegion() == C_REG)
		FMotC.enqueue(mot);
	else FMotD.enqueue(mot);
}

void Restaurant::AddNMot(Motorcycle*mot) {
	if (mot->getRegion() == A_REG)
		NMotA.enqueue(mot);
	else if (mot->getRegion() == B_REG)
		NMotB.enqueue(mot);
	else if (mot->getRegion() == C_REG)
		NMotC.enqueue(mot);
	else NMotD.enqueue(mot);
}
/////////////////////////////// Print Orders Function //////////////////////////
void Restaurant:: PrintOrders()
{
	Order *pOrd;
	pQueue<Order*> VOrdATmp;
	pQueue<Order*> VOrdBTmp;
	pQueue<Order*> VOrdCTmp;
	pQueue<Order*> VOrdDTmp;
	while(VOrdA.dequeue(pOrd))
	{
		pGUI->AddOrderForDrawing(pOrd);
		VOrdATmp.enqueue(pOrd,pOrd->getpriorty());
	}
	while(VOrdB.dequeue(pOrd))
	{
		pGUI->AddOrderForDrawing(pOrd);
		VOrdBTmp.enqueue(pOrd,pOrd->getpriorty());
	}
	while(VOrdC.dequeue(pOrd))
	{
		pGUI->AddOrderForDrawing(pOrd);
		VOrdCTmp.enqueue(pOrd,pOrd->getpriorty());
	}
	while(VOrdD.dequeue(pOrd))
	{
		pGUI->AddOrderForDrawing(pOrd);
		VOrdDTmp.enqueue(pOrd,pOrd->getpriorty());
	}
	while(VOrdATmp.dequeue(pOrd))
	{
		VOrdA.enqueue(pOrd,pOrd->getpriorty());
	}
	while(VOrdBTmp.dequeue(pOrd))
	{
		VOrdB.enqueue(pOrd,pOrd->getpriorty());
	}
	while(VOrdCTmp.dequeue(pOrd))
	{
		VOrdC.enqueue(pOrd,pOrd->getpriorty());
	}
	while(VOrdDTmp.dequeue(pOrd))
	{
		VOrdD.enqueue(pOrd,pOrd->getpriorty());
	}
	
	for(int i=0;i<FOrdA.getsize();i++)
			{
				FOrdA.dequeue(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				FOrdA.enqueue(pOrd);
			}
	for(int i=0;i<FOrdB.getsize();i++)
			{
				FOrdB.dequeue(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				FOrdB.enqueue(pOrd);
			}
	for(int i=0;i<FOrdC.getsize();i++)
			{
				FOrdC.dequeue(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				FOrdC.enqueue(pOrd);
			}
	for(int i=0;i<FOrdD.getsize();i++)
			{
				FOrdD.dequeue(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				FOrdD.enqueue(pOrd);
			}
	for(int i=0;i<NOrdA.getsize();i++)
			{
				NOrdA.popfront(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				NOrdA.pushback(pOrd);
			}
	for(int i=0;i<NOrdB.getsize();i++)
			{
				NOrdB.popfront(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				NOrdB.pushback(pOrd);
			}
	for(int i=0;i<NOrdC.getsize();i++)
			{
				NOrdC.popfront(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				NOrdC.pushback(pOrd);
			}
	for(int i=0;i<NOrdD.getsize();i++)
			{
				NOrdD.popfront(pOrd);
				pGUI->AddOrderForDrawing(pOrd);
				NOrdD.pushback(pOrd);
			}
	pGUI->UpdateInterface();
	pGUI->ResetDrawingList();
}
///////////////////////////// Set Status Bar Functoin /////////////////////////////////
void Restaurant :: SetStatusBar()
{
	pGUI->PrintSMessage("Region 'A' :  Normal Orders:"+to_string(NOrdA.getsize())+"   Frozen Order:"+to_string(FOrdA.getsize())+"    VIP Orders:"+to_string(VOrdA.getsize())+"    Normal Motorcycles:"+to_string(NMotA.getsize())+"    Frozen Motorcycles:"+to_string(FMotA.getsize())+"    VIP Motorcycles:"+to_string(VMotA.getsize()),'A');
	pGUI->PrintSMessage("Region 'B' :  Normal Orders:"+to_string(NOrdB.getsize())+"   Frozen Order:"+to_string(FOrdB.getsize())+"    VIP Orders:"+to_string(VOrdB.getsize())+"    Normal Motorcycles:"+to_string(NMotB.getsize())+"    Frozen Motorcycles:"+to_string(FMotB.getsize())+"    VIP Motorcycles:"+to_string(VMotB.getsize()),'B');
	pGUI->PrintSMessage("Region 'C' :  Normal Orders:"+to_string(NOrdC.getsize())+"   Frozen Order:"+to_string(FOrdC.getsize())+"    VIP Orders:"+to_string(VOrdC.getsize())+"    Normal Motorcycles:"+to_string(NMotC.getsize())+"    Frozen Motorcycles:"+to_string(FMotC.getsize())+"    VIP Motorcycles:"+to_string(VMotC.getsize()),'C');
	pGUI->PrintSMessage("Region 'D' :  Normal Orders:"+to_string(NOrdD.getsize())+"   Frozen Order:"+to_string(FOrdD.getsize())+"    VIP Orders:"+to_string(VOrdD.getsize())+"    Normal Motorcycles:"+to_string(NMotD.getsize())+"    Frozen Motorcycles:"+to_string(FMotD.getsize())+"    VIP Motorcycles:"+to_string(VMotD.getsize()),'D');
}
///////////////////////////   Assign Orders To MotorCycles Function    //////////////////////////////////////////
void Restaurant:: AssignOrdersA(int c)
{
	Order*pOrd;
	Motorcycle*Mot;
	while(!VMotA.isEmpty()&&!VOrdA.isempty())
	{
		VMotA.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdA.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

		while(!NMotA.isEmpty()&&!VOrdA.isempty())
	{
		NMotA.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdA.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

	while(!FMotA.isEmpty()&&!VOrdA.isempty())
	
	{
		FMotA.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdA.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	
	
	while(!FMotA.isEmpty()&&!FOrdA.isEmpty())
	{
		FMotA.dequeue(Mot);
		Mot->SetStatus(SERV);
		FOrdA.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	
	while(!NMotA.isEmpty()&&!NOrdA.isempty())
	{
		NMotA.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdA.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	while(!VMotA.isEmpty()&&!NOrdA.isempty())
	{
		VMotA.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdA.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

}

void Restaurant:: AssignOrdersB(int c)
{
	Order*pOrd;
	Motorcycle*Mot;
	while(!VMotB.isEmpty()&&!VOrdB.isempty())
	{
		VMotB.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdB.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

	while(!NMotB.isEmpty()&&!VOrdB.isempty())
	{
		NMotB.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdB.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

	while(!FMotB.isEmpty()&&!VOrdB.isempty())
	
	{
		FMotB.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdB.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	

	
	while(!FMotB.isEmpty()&&!FOrdB.isEmpty())
	{
		FMotB.dequeue(Mot);
		Mot->SetStatus(SERV);
		FOrdB.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	
	while(!NMotB.isEmpty()&&!NOrdB.isempty())
	{
		NMotB.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdB.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	while(!VMotB.isEmpty()&&!NOrdB.isempty())
	{
		VMotB.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdB.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

}

void Restaurant:: AssignOrdersC(int c)
{
	Order*pOrd;
	Motorcycle*Mot;
	while(!VMotC.isEmpty()&&!VOrdC.isempty())
	{
		VMotC.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdC.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

	while(!NMotC.isEmpty()&&!VOrdC.isempty())
	{
		NMotC.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdC.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

	while(!FMotC.isEmpty()&&!VOrdC.isempty())
	
	{
		FMotC.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdC.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	

	
	while(!FMotC.isEmpty()&&!FOrdC.isEmpty())
	{
		FMotC.dequeue(Mot);
		Mot->SetStatus(SERV);
		FOrdC.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	
	while(!NMotC.isEmpty()&&!NOrdC.isempty())
	{
		NMotC.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdC.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	while(!VMotC.isEmpty()&&!NOrdC.isempty())
	{
		VMotC.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdC.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

}

void Restaurant:: AssignOrdersD(int c)
{
	Order*pOrd;
	Motorcycle*Mot;
	while(!VMotD.isEmpty()&&!VOrdD.isempty())
	{
		VMotD.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdD.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

	while(!NMotD.isEmpty()&&!VOrdD.isempty())
	{
		NMotD.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdD.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	

	while(!FMotD.isEmpty()&&!VOrdD.isempty())
	
	{
		FMotD.dequeue(Mot);
		Mot->SetStatus(SERV);
		VOrdD.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	

	while(!FMotD.isEmpty()&&!FOrdD.isEmpty())
	{
		FMotD.dequeue(Mot);
		Mot->SetStatus(SERV);
		FOrdD.dequeue(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	
	while(!NMotD.isEmpty()&&!NOrdD.isempty())
	{
		NMotD.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdD.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}
	while(!VMotD.isEmpty()&&!NOrdD.isempty())
	{
		VMotD.dequeue(Mot);
		Mot->SetStatus(SERV);
		NOrdD.popfront(pOrd);
		pOrd->SetServTime(pOrd->GetDistance()/Mot->getspeed());
		pOrd->SetWaitTime(c-pOrd->getArrTime());
		pOrd->SetFinishTime(pOrd->getArrTime()+pOrd->getServTime()+pOrd->getWaitTime());
		Mot->SetBackTime(c+2*pOrd->getServTime());
		Done.enqueue(pOrd,-pOrd->getFinishTime());
		InServe.enqueue(Mot);
	}

}

//////////////////////////////// Get The MotorCycle Back After Serving ////////////////////////////////////
void Restaurant::MotBack(int c)
{
	int x=InServe.getsize();
	Motorcycle *Mot;
	for(int i=0;i<x;i++)
	{
		InServe.dequeue(Mot);
		if(Mot->GetBackTime()==c)
		{
			if(Mot->getRegion()==A_REG&&Mot->gettype()==TYPE_VIP)
			{
				Mot->SetStatus(IDLE);
				VMotA.enqueue(Mot);
			}
			else if(Mot->getRegion()==A_REG&&Mot->gettype()==TYPE_NRM)
			{
				Mot->SetStatus(IDLE);
				NMotA.enqueue(Mot);
			}
			else if(Mot->getRegion()==A_REG&&Mot->gettype()==TYPE_FROZ)
			{
				Mot->SetStatus(IDLE);
				FMotA.enqueue(Mot);
			}
			else if(Mot->getRegion()==B_REG&&Mot->gettype()==TYPE_VIP)
			{
				Mot->SetStatus(IDLE);
				VMotB.enqueue(Mot);
			}
			else if(Mot->getRegion()==B_REG&&Mot->gettype()==TYPE_NRM)
			{
				Mot->SetStatus(IDLE);
				NMotB.enqueue(Mot);
			}
			else if(Mot->getRegion()==B_REG&&Mot->gettype()==TYPE_FROZ)
			{
				Mot->SetStatus(IDLE);
				FMotB.enqueue(Mot);
			}
			else if(Mot->getRegion()==C_REG&&Mot->gettype()==TYPE_VIP)
			{
				Mot->SetStatus(IDLE);
				VMotC.enqueue(Mot);
			}
			else if(Mot->getRegion()==C_REG&&Mot->gettype()==TYPE_NRM)
			{
				Mot->SetStatus(IDLE);
				NMotC.enqueue(Mot);
			}
			else if(Mot->getRegion()==C_REG&&Mot->gettype()==TYPE_FROZ)
			{
				Mot->SetStatus(IDLE);
				FMotC.enqueue(Mot);
			}
			else if(Mot->getRegion()==D_REG&&Mot->gettype()==TYPE_VIP)
			{
				Mot->SetStatus(IDLE);
				VMotD.enqueue(Mot);
			}
			else if(Mot->getRegion()==D_REG&&Mot->gettype()==TYPE_NRM)
			{
				Mot->SetStatus(IDLE);
				NMotD.enqueue(Mot);
			}
			else if(Mot->getRegion()==D_REG&&Mot->gettype()==TYPE_FROZ)
			{
				Mot->SetStatus(IDLE);
				FMotD.enqueue(Mot);
			}
		}
		else InServe.enqueue(Mot);
	}
}
//////////////////////////////////// Auto Promotion Function /////////////////////////////////////
void Restaurant::Auto_Promotion(int CurrentTimeStep) {
	linkedlist<Order*>tempA;
	linkedlist<Order*>tempB;
	linkedlist<Order*>tempC;
	linkedlist<Order*>tempD;
	Order*ord;
	while (!NOrdA.isempty()) {
		NOrdA.popfront(ord);
		tempA.pushback(ord);
	}
	while (!NOrdB.isempty()) {
		NOrdB.popfront(ord);
		tempB.pushback(ord);
	}
	while (!NOrdC.isempty()) {
		NOrdC.popfront(ord);
		tempC.pushback(ord);
	}
	while (!NOrdD.isempty()) {
		NOrdD.popfront(ord);
		tempD.pushback(ord);
	}
	while (!tempA.isempty()) {
		tempA.popfront(ord);
		if (CurrentTimeStep - ord->getArrTime() == Prom_Limit) {
			ord->SetOrdType(TYPE_VIP);
			VOrdA.enqueue(ord, ord->getpriorty());
			Eve = new PromotionEvent(ord->getArrTime() + Prom_Limit, ord->GetID(), 0);
			AddEvent(Eve);
		}
		else NOrdA.pushback(ord);
	}
	while (!tempB.isempty()) {
		tempB.popfront(ord);
		if (CurrentTimeStep - ord->getArrTime() == Prom_Limit) {
			ord->SetOrdType(TYPE_VIP);
			VOrdB.enqueue(ord, ord->getpriorty());
			Eve = new PromotionEvent(ord->getArrTime() + Prom_Limit, ord->GetID(), 0);
			AddEvent(Eve);
		}
		else NOrdB.pushback(ord);
	}
	while (!tempC.isempty()) {
		tempC.popfront(ord);
		if (CurrentTimeStep - ord->getArrTime() == Prom_Limit) {
			ord->SetOrdType(TYPE_VIP);
			VOrdC.enqueue(ord, ord->getpriorty());
			Eve = new PromotionEvent(ord->getArrTime() + Prom_Limit, ord->GetID(), 0);
			AddEvent(Eve);
		}
		else NOrdC.pushback(ord);
	}
	while (!tempD.isempty()) {
		tempD.popfront(ord);
		if (CurrentTimeStep - ord->getArrTime() == Prom_Limit) {
			ord->SetOrdType(TYPE_VIP);
			VOrdD.enqueue(ord, ord->getpriorty());
			Eve = new PromotionEvent(ord->getArrTime() + Prom_Limit, ord->GetID(), 0);
			AddEvent(Eve);
		}
		else NOrdD.pushback(ord);
	}
}

////////////////////////////////////////////// Get Ord By ID //////////////////////////////////////
bool Restaurant::getNOrdbyId(Order *&ord, int id) {
	Node<Order*>* p = NOrdA.gethead();
	int k = 0;
	while (p != NULL) {
		if (p->getItem()->GetID() == id) {
			ord = p->getItem();
			NOrdA.remove(k);
			return true;
		}
		else {
			k++;
			p = p->getNext();
		}

	}
	p = NOrdB.gethead();
	k = 0;
	while (p != NULL) {
		if (p->getItem()->GetID() == id) {
			ord = p->getItem();
			NOrdB.remove(k);
			return true;
		}
		else {
			k++;
			p = p->getNext();
		}

	}
	p = NOrdC.gethead();
	k = 0;
	while (p != NULL) {
		if (p->getItem()->GetID() == id) {
			ord = p->getItem();
			NOrdC.remove(k);
			return true;
		}
		else {
			k++;
			p = p->getNext();
		}

	}
	p = NOrdD.gethead();
	k = 0;
	while (p != NULL) {
		if (p->getItem()->GetID() == id) {
			ord = p->getItem();
			NOrdD.remove(k);
			return true;
		}
		else {
			k++;
			p = p->getNext();
		}

	}
	return false;
}
///////////////////////////////////////////// OutPut File Function //////////////////////////////////////////
void Restaurant::OutputFile()
{
	string s = pGUI->GetString();
	ofstream file;
	file.open(s + ".txt");
	int oa = 0; int ob = 0; int oc = 0; int od=0; //number of serviced orders in each region
	int na = 0; int nb = 0; int nc = 0; int nd = 0; int fa = 0; int fb = 0; int fc = 0; int fd = 0;
	int va = 0; int vb = 0; int vc = 0; int vd=0; //number of orders of a certain type for each region
	double wa = 0; double wb = 0; double wc = 0; double wd = 0; double wt = 0; //avg waiting time for each region +total
	double sa = 0; double sb = 0; double sc = 0; double sd = 0; double st = 0; //avg service time for eah region  +total
	Queue<Order*> p; //queue of serviced orders sorted by ascending FT then by descending ST
	//creating p
	Order * pOrd;
	while (!Done.isempty())
	{
		pQueue<Order*> temp; //contains orders of same FT
		Done.dequeue(pOrd);
		temp.enqueue(pOrd, pOrd->getServTime());
		int t = pOrd->getFinishTime();
		while (!Done.isempty())
		{
			Done.peekfront(pOrd);
			if (pOrd->getFinishTime() != t)
				break;
			Done.dequeue(pOrd);
			temp.enqueue(pOrd, pOrd->getServTime());
		}
		while (!temp.isempty())
		{
			temp.dequeue(pOrd);
			p.enqueue(pOrd);
		}
	}
	//outputing serviced orders and populating variables
	file << "FT ID AT WT ST" << endl;
	while (!p.isEmpty())
	{
		p.dequeue(pOrd);
		file << pOrd->getFinishTime() << " " << pOrd->GetID() << " " << pOrd->getArrTime() << " " << pOrd->getWaitTime() << " " << pOrd->getServTime() << endl;
		switch (pOrd->GetRegion())
		{
		case A_REG:
			oa++;
			wa += pOrd->getWaitTime();
			sa += pOrd->getServTime();
			switch (pOrd->GetType())
			{
			case TYPE_NRM:
				na++;
				break;
			case TYPE_FROZ:
				fa++;
				break;
			case TYPE_VIP:
				va++;
			}
			break;
		case B_REG:
			ob++;
			wb += pOrd->getWaitTime();
			sb += pOrd->getServTime();
			switch (pOrd->GetType())
			{
			case TYPE_NRM:
				nb++;
				break;
			case TYPE_FROZ:
				fb++;
				break;
			case TYPE_VIP:
				vb++;
			}
			break;
		case C_REG:
			oc++;
			wc += pOrd->getWaitTime();
			sc += pOrd->getServTime();
			switch (pOrd->GetType())
			{
			case TYPE_NRM:
				nc++;
				break;
			case TYPE_FROZ:
				fc++;
				break;
			case TYPE_VIP:
				vc++;
			}
			break;
		case D_REG:
			od++;
			wd += pOrd->getWaitTime();
			sd += pOrd->getServTime();
			switch (pOrd->GetType())
			{
			case TYPE_NRM:
				nd++;
				break;
			case TYPE_FROZ:
				fd++;
				break;
			case TYPE_VIP:
				vd++;
			}
		}
	}
	wt = (wa + wb + wc + wd) / (oa + ob + oc + od);
	st= (sa+sb+sc+sd)/ (oa + ob + oc + od);
	wa = wa / oa; wb = wb / ob; wc = wc / oc; wd = wd / od;
	sa = sa / oa; sb = sb / ob; sc = sc / oc; sd = sd / od;

	file << endl << endl << endl;

	file << "RegionA:" << endl << "    Orders: " << oa << " [Norm: " << na << ", Froz: " << fa << ", VIP: " << va << "]" << endl;
	file << "    MotorC: " << mna + mfa + mva << " [Norm: " << mna << ", Froz: " << mfa << ", VIP: " << mva << "]" << endl;
	file << "    Avg Wait = " << wa << ", Avg Serv = " << sa << endl;
	file << "RegionB:" << endl << "    Orders: " << ob << " [Norm: " << nb << ", Froz: " << fb << ", VIP: " << vb << "]" << endl;
	file << "    MotorC: " << mnb + mfb + mvb << " [Norm: " << mnb << ", Froz: " << mfb << ", VIP: " << mvb << "]" << endl;
	file << "    Avg Wait = " << wb << ", Avg Serv = " << sb << endl;
	file << "RegionC:" << endl << "    Orders: " << oc << " [Norm: " << nc << ", Froz: " << fc<< ", VIP: " << vc << "]" << endl;
	file << "    MotorC: " << mnc + mfc + mvc << " [Norm: " << mnc << ", Froz: " << mfc << ", VIP: " << mvc << "]" << endl;
	file << "    Avg Wait = " << wc << ", Avg Serv = " << sc << endl;
	file << "RegionD:" << endl << "    Orders: " << od << " [Norm: " << nd << ", Froz: " << fd << ", VIP: " << vd << "]" << endl;
	file << "    MotorC: " << mnd + mfd + mvd << " [Norm: " << mnd << ", Froz: " << mfd << ", VIP: " << mvd << "]" << endl;
	file << "    Avg Wait = " << wd << ", Avg Serv = " << sd << endl;
	file << "Restaurant:" << endl << "    Orders: " << oa+ob+oc+od << " [Norm: " << na+nb+nc+nd << ", Froz: " << fa+fb+fc+fd << ", VIP: " << 
		va+vb+vc+vd << "]" << endl;
	file << "    MotorC: " << mna + mfa + mva+ mnb + mfb + mvb+ mnc + mfc + mvc+ mnd + mfd + mvd << " [Norm: " <<mna+mnb+mnc+ mnd << ", Froz: " << mfa+mfb+mfc+mfd << ", VIP: " <<
		mva+mvb+mvc+mvd << "]" << endl;
	file << "    Avg Wait = " << wt << ", Avg Serv = " << st << endl;
	
	file.close();
}


//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}





////////////////////////////////////////  Clear Function To Deallocate Memory /////////////////////////////////
void Restaurant::clearall() {
	VMotA.clear();
	VMotB.clear();
	VMotC.clear();
	VMotD.clear();
	NMotA.clear();
	NMotB.clear();
	NMotC.clear();
	NMotD.clear();
	VMotA.clear();
	FMotA.clear();
	FMotB.clear();
	FMotC.clear();
	FMotD.clear();
	VOrdA.clear();
	VOrdB.clear();
	VOrdC.clear();
	VOrdD.clear();
	FOrdA.clear();
	FOrdB.clear();
	FOrdC.clear();
	FOrdD.clear();
	NOrdA.clear();
	NOrdB.clear();
	NOrdC.clear();
	NOrdD.clear();
}

///////////////////////////////////  Destructor //////////////////////////////////

Restaurant::~Restaurant()
{
		delete pGUI;
}




////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}


/// ==> end of DEMO-related function

