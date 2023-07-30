#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

//Make the previous day's data as CONSTANT
#define DAY_9_NEW_CASES  9
#define DAY_9_TOTAL_CASES 100
#define DAY_9_TOTAL_DEATHS 2
#define DAY_9_TOTAL_RECOVERED 10
#define DAY_9_UNDER_TREATMENT  88

//Declare function
void access();
void heading();
void previous();
char nextReport();
int reportMenu();
void comment(int totalNewCases, int prevNewCases);
int userInput(int* localNewCases, int* importedNewCases, int* numberOfDeaths, int* numberOfRecovered);
void currentTable(int localNewCases, int importedNewCases, int numberOfDeaths, int numberOfRecovered);
int reportTypes(int localNewCases, int importedNewCases, int numberOfDeaths, int numberOfRecovered, int totalCases, int totalNewCases, int prevNewCases, int prevTotalCases, int prevTotalDeaths, int prevTotalRecovered, int prevDay, int today);


/*
Name                           :CHEAN KAE LUN
Programme and Tutorial Group   :DCO1 S1 GROUP4
Assignment                     :PCD1 COVID19 TRACKING SYSTEM

Information                    :When debugging this program, please maximize the window of debugger (Before login) so the layout of logo design will not go wrong
                                UserName : admin
								Password : admin
*/

void main() {
	
	//User access verification 
	access();

	//Title of the program
	heading();
	
	//Memory
	int localNewCases, importedNewCases, numberOfDeaths, numberOfRecovered, totalNewCases;
	int totalCases = DAY_9_TOTAL_CASES, totalDeaths, totalRecovered;
	int prevNewCases = DAY_9_NEW_CASES, prevTotalCases = DAY_9_TOTAL_CASES, prevTotalDeaths = DAY_9_TOTAL_DEATHS, prevTotalRecovered = DAY_9_TOTAL_RECOVERED;
	int numberOfDay = 10, countOfDay = 0, prevDay = 9, today = 10;
	char nextDay;

	//Using array to store highest cases and day & lowest cases and day
	//highestCasesAndDay[0] and lowestCasesAndDay[0] store the cases
	//highestCasesAndDay[1] and highestCasesAndDay[1] store the day
	int highestCasesAndDay[2] = { DAY_9_NEW_CASES,9 }, lowestCasesAndDay[2] = { DAY_9_NEW_CASES, 9 };
	
	
	//Using loop to enter the next day's Input
	do {
		if (numberOfDay > 10) {
			prevNewCases = totalNewCases;
			prevTotalCases += totalNewCases;
			prevTotalDeaths += numberOfDeaths;
			prevTotalRecovered = totalRecovered;
		}
		printf("\n\n");
		printf("Day %d data input!\n", numberOfDay);
		printf("\n");

		//Return multiple value from userInput() using pointers
		totalNewCases = userInput(&localNewCases, &importedNewCases, &numberOfDeaths, &numberOfRecovered);
		totalCases += totalNewCases;

		printf("\n\nDay %d\n", numberOfDay);

		//The function that shows the table which arranged the current day's data will be calling
		currentTable(localNewCases, importedNewCases, numberOfDeaths, numberOfRecovered);


		//Making choice on type of reports to show data in detail and Return the value of Total Recovered
		totalRecovered = reportTypes(localNewCases, importedNewCases, numberOfDeaths, numberOfRecovered, totalCases, totalNewCases, prevNewCases, prevTotalCases, prevTotalDeaths, prevTotalRecovered, prevDay, today);


		//Giving comment according to the situation
		comment(totalNewCases, prevNewCases);
		printf("\n=================================================== End Of Day %d Reporting ======================================================\n", numberOfDay);

		//Asking the decision from user to continue next day data input
		nextDay = nextReport();
		
		//Display yesterday's Total Cases
		printf("\nYesterday's Total - (Day %d) : %d\n", numberOfDay, totalCases);
		
		
		if (totalNewCases > highestCasesAndDay[0]) {

			//Store the highest cases
			highestCasesAndDay[0] = totalNewCases;
			
			//Store the day of highest cases
			highestCasesAndDay[1] = numberOfDay;
		}
		if (totalNewCases < lowestCasesAndDay[0]) {
			
			//Store the lowest cases
			lowestCasesAndDay[0] = totalNewCases;
			
			//Store the day of lowest cases
			lowestCasesAndDay[1] = numberOfDay;
		}

		//Increase the day if the next day data input needed
		numberOfDay++;

		//Counting the total day recorded
		countOfDay++;

		//Use for comparative report
		prevDay++;
		today++;

	} while (nextDay == 'Y' || nextDay == 'y');

	//The conclusion in the Final
	printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TOTAL Days recorded     = %d\n", countOfDay);
	printf("HIGHEST Number Of Cases = %d, occuring on Day %d\n", highestCasesAndDay[0], highestCasesAndDay[1]);
	printf("LOWEST Number Of Cases  = %d, occuring on Day %d\n", lowestCasesAndDay[0], lowestCasesAndDay[1]);
	printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Bye ! ThankYou ^^\n");


	system("pause");
}


void heading() {
	printf("\033[0;34m");
	printf("\t+------------------------------------------------------------------------------------------------------------------+\n");
	printf("\t| !!!!!!!!!!\t!!!!!!!!!!\t!!         !!\t!!!!!!!!!!\t!!!!!!!!!  \t       \t !!!!!    \t!!!!!!!!!! |\n");
	printf("\t| !!        \t!!      !!\t!!         !!\t    !!    \t!!      !! \t       \t    !!    \t!!      !! |\n"); 
	printf("\t| !!        \t!!      !!\t !!       !! \t    !!    \t!!       !!\t ~~~~~~\t    !!    \t!!      !! |\n");
	printf("\t| !!        \t!!      !!\t  !!     !!  \t    !!    \t!!       !!\t ~~~~~~\t    !!    \t!!!!!!!!!! |\n");
	printf("\t| !!        \t!!      !!\t   !!   !!   \t    !!    \t!!       !!\t ~~~~~~\t    !!    \t        !! |\n");
	printf("\t| !!        \t!!      !!\t    !! !!    \t    !!    \t!!      !! \t       \t    !!    \t        !! |\n");
	printf("\t| !!!!!!!!!!\t!!!!!!!!!!\t     !!!     \t!!!!!!!!!!\t!!!!!!!!!  \t       \t!!!!!!!!!!\t!!!!!!!!!! |\n");
	printf("\t+------------------------------------------------------------------------------------------------------------------+\n");
	printf("\033[0m");

	//Display the previous day's data
	previous();
}

//Pointers is used for returning mulltiple values purpose
int userInput(int* localNewCases,int* importedNewCases,int* numberOfDeaths,int* numberOfRecovered) {
	
	int totalNewCases;
	
	//this variable is use to validate the integer input
	char validator[4];

	//Validation of Input is made to ensure proper input by user with suitable prompt
	do {
		rewind(stdin);
		printf("Enter the number of new cases (Local)       > ");
		scanf("%d%c", &*localNewCases, &validator[0]);
		*localNewCases;
		if (localNewCases < 0 || validator[0] != '\n') {
			printf("\033[1;31m");
			printf("Invalid input's data type or range , only numeric input available !\n\n\a");
			printf("\033[0m");
		}
	} while (localNewCases < 0 || validator[0] != '\n');

	do {
		rewind(stdin);
		printf("Enter the number of new cases (Imported)    > ");
		scanf("%d%c", &*importedNewCases, &validator[1]);
		*importedNewCases;
		if (importedNewCases < 0 || validator[1] != '\n') {
			printf("\033[1;31m");
			printf("Invalid input's data type or range , only numeric input available !\n\n\a");
			printf("\033[0m");
		}
	} while (importedNewCases < 0 || validator[1] != '\n');

	do {
		rewind(stdin);
		printf("Enter the number of deaths                  > ");
		scanf("%d%c", &*numberOfDeaths, &validator[2]);
		*numberOfDeaths;
		if (numberOfDeaths < 0 || validator[2] != '\n') {
			printf("\033[1;31m");
			printf("Invalid input's data type or range , only numeric input available !\n\n\a");
			printf("\033[0m");
		}
	} while (numberOfDeaths < 0 || validator[2] != '\n');

	do {
		rewind(stdin);
		printf("Enter the number of recovered / discharged  > ");
		scanf("%d%c", &*numberOfRecovered, &validator[3]);
		*numberOfRecovered;
		if (numberOfRecovered < 0 || validator[3] != '\n') {
			printf("\033[1;31m");
			printf("Invalid input's data type or range , only numeric input available !\n\n\a");
			printf("\033[0m");
		}
	} while (numberOfRecovered < 0 || validator[3] != '\n');


	totalNewCases = *localNewCases + *importedNewCases;

	return totalNewCases;
}

void previous() {
	printf("\n\n");
	printf("%74s\n","+-------------------+");
	printf("%74s\n","|Previous Day's Data|");
	printf("%74s\n","+-------------------+");
	printf("=================================================================================================================================\n");
	printf("||%-20s|%-20s|%-20s|%-20s|%-20s|%-20s||\n", "", "New Cases", "Total Cases", "Total deaths", "Total Recovered", "Under treatment");
	printf("=================================================================================================================================\n");
	printf("||%-20s|%-20d|%-20d|%-20d|%-20d|%-20d||\n", "Day 9th", DAY_9_NEW_CASES, DAY_9_TOTAL_CASES, DAY_9_TOTAL_DEATHS, DAY_9_TOTAL_RECOVERED, DAY_9_UNDER_TREATMENT);
	printf("=================================================================================================================================\n");
}


void currentTable(int localNewCases, int importedNewCases, int numberOfDeaths, int numberOfRecovered) {

	printf("=================================================================================================================================\n");
	printf("||%-50s|%10d[Local] %10d[Imported]%38s\n", "Number of new cases : local and imported", localNewCases, importedNewCases, "||");
	printf("=================================================================================================================================\n");
	printf("||%-50s|%10d %65s\n", "Number of deaths", numberOfDeaths, "||");
	printf("=================================================================================================================================\n");
	printf("||%-50s|%10d %65s\n", "Number of recovered / discharged", numberOfRecovered, "||");
	printf("=================================================================================================================================\n");

}

int reportMenu() {
	int choice;
	char validator;
	do {
		rewind(stdin);
		printf("What type of report would you like to VIEW ? \n");
		printf("[1]for Daily Summary Report\n");
		printf("[2]for Daily Comparative Report\n");
		scanf("%d%c", &choice, &validator);
		if (choice != 1 && choice != 2 || validator != '\n') {
			printf("\033[1;31m");
			printf("Invalid input's data type or range , only numeric input available !\n\n\a");
			printf("\033[0m");
		}
	} while (choice != 1 && choice != 2 || validator != '\n');

	return choice;
}

int reportTypes(int localNewCases, int importedNewCases, int numberOfDeaths, int numberOfRecovered, int totalCases, int totalNewCases, int prevNewCases, int prevTotalCases, int prevTotalDeaths, int prevTotalRecovered, int prevDay, int today) {
	int choice;
	int totalDeaths, totalRecovered, underTreatment;
	float percentageOfDeaths, percentageOfRecovered, percentageOfUnderTreatment,previousDeathsRate,previousRecoveryRate;

	//Basic operation
	totalDeaths = prevTotalDeaths + numberOfDeaths;
	totalRecovered = prevTotalRecovered + numberOfRecovered;
	underTreatment = totalCases - totalDeaths - totalRecovered;
	
	//Process of counting percentages
	previousDeathsRate = (float)prevTotalDeaths / prevTotalCases * 100;
	previousRecoveryRate = (float)prevTotalRecovered / prevTotalCases * 100;
	percentageOfDeaths = (float)totalDeaths / totalCases * 100;
	percentageOfRecovered = (float)totalRecovered / totalCases * 100;
	percentageOfUnderTreatment = (float)underTreatment / totalCases * 100;

	choice = reportMenu();

	switch (choice)
	{
	case 1: {
		printf("\n\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{Daily Summary Report}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("=================================================================================================================================\n");
		printf("||%-24s|%-25s|%-25s|%-25s|%-22s||\n", "New Cases", "Total Cases", "Total Deaths", "Total Recovered", "Under Treatment");
		printf("=================================================================================================================================\n");
		printf("||%-14s%-10d| %-24s| %-24s| %-24s| %-21s||\n", "Local", localNewCases, "---------------", "---------------", "---------------", "---------------");
		printf("||%-14s%-10d| %-24s| %-24s| %-24s| %-21s||\n", "Imported", importedNewCases, "---------------", "---------------", "---------------", "---------------");
		printf("||%-14s%-10d| %-24d| %-24d| %-24d| %-21d||\n", "Total =", totalNewCases, totalCases, totalDeaths, totalRecovered, underTreatment);
		printf("=================================================================================================================================\n");
		printf("||%-24s%| %-24s| %-23.1f%%| %-23.1f%%| %-20.1f%%||\n", "Percentage(%)", "", percentageOfDeaths, percentageOfRecovered, percentageOfUnderTreatment);
		printf("=================================================================================================================================\n");
	}break;
	case 2: {

		//Process of counting differences 
		float differenceofDeaths,differenceOfRecovered;
		int differenceOfNewCases, differenceOfTotal;
		differenceOfNewCases = totalNewCases - prevNewCases;
		differenceOfTotal = totalCases - prevTotalCases;
		differenceofDeaths = percentageOfDeaths - previousDeathsRate;
		differenceOfRecovered = percentageOfRecovered - previousRecoveryRate;
		

		printf("=================================================================================================================================\n");
		printf("||%-27s|%10s%-22s|%10s%-22s|%9s%-22s||\n", "", "","Yesterday","", "Today","", "Difference");
		printf("||%-27s|%10s%-4s%-18d|%10s%-4s%-18d|%31s||\n", "", "", "Day ", prevDay, "", "Day ", today, "");
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");
		if (differenceOfNewCases < 0) {
			differenceOfNewCases *= -1;
			printf("||%-27s|%32d|%32d|%23s[-%5d]||\n", "New Cases", prevNewCases, totalNewCases, "", differenceOfNewCases);
		}
		else {
			printf("||%-27s|%32d|%32d|%23s[+%5d]||\n", "New Cases", prevNewCases, totalNewCases, "", differenceOfNewCases);
		}
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");
		printf("||%-27s|%32d|%32d|%23s[+%5d]||\n", "Total Cases", prevTotalCases, totalCases, "",differenceOfTotal);
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");
		if (differenceofDeaths < 0) {
			differenceofDeaths *= -1;
			printf("||%-27s|%21s%10.1f%s|%21s%10.1f%s|%21s[-%5.1f%2s]||\n", "Death Rate", "", previousDeathsRate, "%", "", percentageOfDeaths, "%", "", differenceofDeaths, "%");
		}
		else {
			printf("||%-27s|%21s%10.1f%s|%21s%10.1f%s|%21s[+%5.1f%2s]||\n", "Death Rate", "", previousDeathsRate, "%", "", percentageOfDeaths, "%", "", differenceofDeaths, "%");
		}
		printf("---------------------------------------------------------------------------------------------------------------------------------\n");
		if (differenceOfRecovered< 0) {
			differenceOfRecovered *= -1;
			printf("||%-27s|%21s%10.1f%s|%21s%10.1f%s|%21s[-%5.1f%2s]||\n", "Recovery Rate", "", previousRecoveryRate, "%", "", percentageOfRecovered, "%", "", differenceOfRecovered, "%");
		}
		else {
			printf("||%-27s|%21s%10.1f%s|%21s%10.1f%s|%21s[+%5.1f%2s]||\n", "Recovery Rate", "", previousRecoveryRate, "%", "", percentageOfRecovered, "%", "", differenceOfRecovered, "%");
		}
		printf("=================================================================================================================================\n");
	}
	
	}
	return totalRecovered;
	}
	
	
void comment(int totalNewCases, int prevNewCases) {
		
	    //Memory 
	    int difference;

		//Produce difference output according to the data 
		if (totalNewCases == prevNewCases) {
			printf("\n\n");
			printf("----------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\033[0;31m");
			printf("%85s\n", "Well Done! ! ! No Change from yesterday");
			printf("\033[0m");
			printf("----------------------------------------------------------------------------------------------------------------------------------\n");
		}
		else if (totalNewCases > prevNewCases) {
			printf("\n\n");
			difference = totalNewCases - prevNewCases;
			printf("----------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\033[0;31m");
			printf("%70s%d%-70s\n", "The new cases has increased ", difference, " compared to Previous day");
			printf("%85s\n", "Keep striving,The Virus is being Gone!");
			printf("\033[0m");
			printf("----------------------------------------------------------------------------------------------------------------------------------\n");
		}
		else {
			difference = prevNewCases - totalNewCases;
			printf("\n\n");
			printf("----------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\033[0;31m");
			printf("%70s%d%-70s\n", "Congrats ! The new cases has decreased ", difference, " compared to Previous day");
			printf("\033[0m");


			printf("----------------------------------------------------------------------------------------------------------------------------------\n");

		}
		
	}

char nextReport() {

	//Memory that store decision to enter next day
	char decision;


	printf("\n\n");
	printf("CONTINUE TO NEXT DAY ? (Y / y = Yes) or CLICK OTHER KEYS TO EXIT >");
	scanf("%c", &decision);
	
	return decision;
}

void access() {

	//Memory
	char userName[50], defaultUserName[50] = "admin";
	char password[50], defaultPassword[50] = "admin";
	int wrongCount;

	do {

		printf("Log In to Access the Covid-19 Tracking System\n\n");
		wrongCount = 0;
		do {
			printf("\n");
			rewind(stdin);
			printf("UserName :");
			scanf("%[^\n]", &userName);
			if (strcmp(userName, defaultUserName) != 0)
			{
				printf("No user's account found\n");
			}
		} while (strcmp(userName, defaultUserName) != 0);

		do {
			rewind(stdin);
			printf("Password :");
			scanf("%[^\n]", &password);
			if (strcmp(password, defaultPassword) != 0)
			{
				printf("Wrong Password\n\n");
				wrongCount++;
			}
		} while (strcmp(password, defaultPassword) != 0 && wrongCount < 3);
		system("cls");

	} while (wrongCount == 3);
	
}