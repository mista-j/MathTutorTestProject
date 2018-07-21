﻿/*
@Project : p2mathtutorNicholasMorgan.cpp :
@Creator : Nicholas Morgan
@Description : This program is supposed to generate problems for a user and check the answers the user inputs
@Version : 7/11/2018 First Build, created problem selection/menu,
@version 2 : 7/14/2018 broke math functions into int and decimal portions to allow scaling, added more customizeable parts
@known bugs : if EPSILON is changed the floating decimal place for floatgen doesnt change with it 
*/

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

//Global Constants
const int NUMBEROFPROBLEMS = 5;
const double EPSILON = 0.1;
const string CORRECT = "Correct!";
const string INCORRECT = "Incorrect.";
const int CORRECTSCORE = 1;
const int INCORRECTSCORE = 0;
const int MAXINTINTERVAL = 8;
const int MININTINTERVAL = 1;
const double MAXDOUBLEINTERVAL = 8.0;
const double MINDOUBLEINTERVAL = 1.0;

//Function Prototypes

//You have all these prototypes but you never leave comments as to the jobs of the prototypes
// look up google guide on how to use comments or look up something called javadocs for an example of how comments should look
// javadocs are not java specific but instead OO specific
int problemSelection(void);  //you dont have to write void in each of these when they are void... just write problemSelection()
void problemTree(int selection, int decimalOrInteger);
void additionTestInt(void);
void additionTestDouble(void);
void subtractionTestInt(void);
void subtractionTestDouble(void);
void multiplicationTestInt(void);
void multiplicationTestDouble(void);
void divisionTestInt(void);
void divisionTestDouble(void);
void remainderTestInt(void);
void remainderTestDouble(void);
int getUserIntOrDoubleSelection(void);
void userScore(int testScores);
int genInt(void);
float genFloat(void);
bool closeEnough(double userDouble, double answerDouble);
int answerCheckInt(int answerInt, int userAnswer);
int answerCheckDouble(double answerDouble, double userAnswer);

int main()
{
	//Local Variables
	int exitValue = 1;

	srand(time(0));
	/*
	* Here you used a variable exitValue for the single use of calling it as an exit value for loop
	* so there are an infinate number of ways to run this function in this case but one example might be
	*  
	* 
	* while (problemSelection() != 0) {}
	*
	* C++ syntax might ask you to change this a bit but as you can see I do it all in one line thus reducing whitespace
	*/
	while (exitValue != 0)
	{
		exitValue = problemSelection();

	}
	return 0;
}

int problemSelection(void)
{
	//local Variables
	int userInputSelection = 0;
	// This exitValue is never used
	int exitValue = 0;
	//Here you are needlessly setting decimalOfInt to 1, just set it to the getUserIntOrDoubleSelection();
	int decimalOrInteger = 1;
	//Ask for decimal or integer tests
	decimalOrInteger = getUserIntOrDoubleSelection();

	//Present test types
	// all of these print statements should be their own function to make reading a bit easier
	cout << "Which type of problems would you like to test yourself on?" << endl;
	cout << "Press 0 to quit" << endl;
	cout << "1. Addition" << endl;
	cout << "2. Subtraction" << endl;
	cout << "3. Multiplication" << endl;
	cout << "4. Division" << endl;
	cout << "5. Remainder" << endl;

	//Grab users input
	cin >> userInputSelection;

	//Pass selection to the decision tree
	//If the user is going to quit then the program should never run the problem tree correct?
	// You are making the computer do a bunch of extra work just so that you can quit somewhere else.
	// also you created a while loop one stack above this at line 64 when you could just have put the while loop in here
	//  this is usually the resualt of not very clear top down coding implementations
	problemTree(userInputSelection, decimalOrInteger);
	return userInputSelection;

}

void problemTree(int selection, int decimalOrInteger)
{
	// this is the proper syntax use of enum but not the proper use case of enume.  You use enum for a class system when you
	// are going to be calling on several instances of code over and over again however you are only calling on it this one time
	// in this case.
	enum problems_t { quit = 0, addition, subtraction, multiplication, division, remainder };
	if (selection == quit)
	{
		cout << "Have a good day." << endl;
		system("pause");

	}
	else if (selection == addition)
	{
		if (decimalOrInteger == 1)
		{
			additionTestInt();
		}
		else
		{
			additionTestDouble();
		}

	}
	else if (selection == subtraction)
	{
		if (decimalOrInteger == 1)
		{
			subtractionTestInt();
		}
		else
		{
			multiplicationTestDouble();
		}


	}
	else if (selection == multiplication)
	{
		if (decimalOrInteger == 1)
		{
			multiplicationTestInt();
		}
		else
		{
			multiplicationTestDouble();
		}

	}
	else if (selection == division)
	{
		if (decimalOrInteger == 1)
		{
			divisionTestInt();
		}
		else
		{
			divisionTestDouble();
		}

	}
	else if (selection == remainder)
	{
		if (decimalOrInteger == 1)
		{
			remainderTestInt();
		}
		else
		{
			remainderTestDouble();
		}

	}
	else
	{
		//This is anohter example of poor top down design thnking if there was an "incorrect value" why did i just
		// wait till now to figure it out, this could be handled at higher levels
		cout << "Sorry, please choose a valid selection." << endl;
		problemSelection();
	}
}

// Was this function at all neccssary? was it assignment based.  Generally for any real math you would always use doubles
// even in cases where you are looking for floor amounts you would use doubles and then just remove the floating numbers on use
int getUserIntOrDoubleSelection(void)
{
	
	//Local Variables
	//This is another odd use of declaring a variable just to put something in it and get rid of it
	// I give this one some flex though because you did have print statements in front of it so I guess its ok then?
	int userSelection = 0;

	cout << "Would you like to test decimals or integers? " << endl;
	cout << "1. Integers\n";
	cout << "2. Decimals\n";
	cin >> userSelection;

	return userSelection;
}

int answerCheckDouble(double answerDouble, double userAnswerDouble)
{
	// you are creating two variables here just to store two varialbes you already have access to
	double correctAnswerDouble = answerDouble;
	double userDoubleInput = userAnswerDouble;
	// you are declaring and init a variable just so in the next line you can init again, this is needless
	bool correctAnswerBool = false;

	correctAnswerBool = closeEnough(userDoubleInput, correctAnswerDouble);

	if (correctAnswerBool == CORRECTSCORE)
	{
		cout << CORRECT << endl;
		return CORRECTSCORE;

	}
	else
	{
		cout << INCORRECT << endl;
		return INCORRECTSCORE;
	}

}
//Calculates and presents the users score for that excersice
void userScore(int score)
{
	//Local variables
	// normally never leave a variable non initialized, in this case you are doing it the ver next line so its not to big a deal
	// but as before just move it up such tath "double totalScore = score / NUMBEROFPROBLEMS
	double totalScore;

	totalScore = (score / NUMBEROFPROBLEMS);

	cout << "Your score was " << setprecision(2) << totalScore << "% ( " << score << " / " << NUMBEROFPROBLEMS << " ) " << endl;


}
//generates a random int value between the max and min constnats
int genInt(void)
{
	//Local Variables
	int randomNumber = 0;

	randomNumber = (rand() % 10);
	if (randomNumber >= MININTINTERVAL || randomNumber >= MAXINTINTERVAL)
	{
		return randomNumber;
	}
	else 
	{
		genInt();
	}
	
}
//generates a random float value between the max and min constants
float genFloat(void)
{
	//Local Variables
	float randomFloat = 0;
	float truncatedFloat = 0;

	// generate a random floating point number between max double interval and min
	randomFloat = ( ( (rand() / (float)RAND_MAX) * (MAXDOUBLEINTERVAL - 1)) + MINDOUBLEINTERVAL); 
	
	//truncate the float to the first decimal
	truncatedFloat = roundf(randomFloat * 10) / 10;

	return truncatedFloat;
	
}
//checks answer vs user answer withing the epsilon value
bool closeEnough(double answerDouble, double userAnswerDouble)
{
	double closeEnoughCheck = 0;
	double errorMin = (0 - EPSILON);
	double errorMax = (EPSILON);

	closeEnoughCheck = answerDouble - userAnswerDouble;

	if (closeEnoughCheck >= 0 && closeEnoughCheck <= errorMax)
	{
		return CORRECTSCORE;
	}
	else if (closeEnoughCheck <= 0 && closeEnoughCheck >= errorMax)
	{
		return CORRECTSCORE;
	}
	else
	{
		return INCORRECTSCORE;
	}
}

//compates generated answer vs user's answer
int answerCheckInt(int answerInt, int userInputInt)
{
	if (answerInt == userInputInt)
	{
		cout << CORRECT << endl;
		cout << "Correct answer " << answerInt << endl;
		return CORRECTSCORE;
	}
	else
	{
		cout << INCORRECT << endl;
		cout << "Correct answer " << answerInt << endl;
		return INCORRECTSCORE;
	}
}

//Generates a integer addition problem and presents it 
void additionTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;
	///.................
	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		answer = firstIntNumber + secondIntNumber;
		
		cout << "What is the sum of " << firstIntNumber << "+" << secondIntNumber << " ?" << endl;
		
		cin >> userAnswer;
		
		currentScore = currentScore + answerCheckInt(answer, userAnswer);
		
	}

	userScore(currentScore);
}

//Generates a decimal addition problem and presents it 
void additionTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();
	
		answer = (firstFloatNumber + secondFloatNumber);

		cout << "What is the sum of " << firstFloatNumber << "+" << secondFloatNumber << " ?" << endl;

		cin >> userAnswer;

		currentScore = currentScore + answerCheckDouble(answer, userAnswer);
	}

	userScore(currentScore);
}

//Generates a integer subtraction problem and presents it 
void subtractionTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;
	//// there are not enough tears on the trail of tears for this to run
	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		if (firstIntNumber >= secondIntNumber)
		{
			answer = firstIntNumber - secondIntNumber;

			cout << "What is " << firstIntNumber << "-" << secondIntNumber << " ?" << endl;

			cin >> userAnswer;

			currentScore = currentScore + answerCheckInt(answer, userAnswer);

		}
		else
		{
			answer = secondIntNumber - firstIntNumber;

			cout << "What is " << secondIntNumber << "-" << firstIntNumber << " ?" << endl;

			cin >> userAnswer;

			currentScore = currentScore + answerCheckInt(answer, userAnswer);
		}
	}

	userScore(currentScore);
}

//Generates a decimal subtraction problem and presents it 
void subtractionTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;
	//REALLY HOW DID THIS RUN?  VS IS SO NICE TO YOU
	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();

		if (firstFloatNumber >= secondFloatNumber)
		{
			answer = (firstFloatNumber - secondFloatNumber);
			cout << "What is  " << firstFloatNumber << "-" << secondFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
		else
		{
			answer = (secondFloatNumber - firstFloatNumber);
			cout << "What is " << secondFloatNumber << "-" << firstFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
	}
	userScore(currentScore);
}

//Generates a integer multiplication problem and presents it 
void multiplicationTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;
	
	
	//DID THIS PROGRAM EVEN COMPILE YOU DECLARED I TWICE
	//THIS IS A BIG NO NO
	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();

		answer = firstIntNumber * secondIntNumber;
		
		cout << "What is " << firstIntNumber << "*" << secondIntNumber << " ?" << endl;
		
		cin >> userAnswer;
		
		currentScore = currentScore + answerCheckInt(answer, userAnswer);
	}

	userScore(currentScore);
}

//Generates a decimal multiplication problem and presents it 
void multiplicationTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();

			answer = (firstFloatNumber * secondFloatNumber);

			cout << "What is " << firstFloatNumber << "*" << secondFloatNumber << " to one decimal place?" << endl;
	
			cin >> userAnswer;
	
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
	}
	userScore(currentScore);
}
//Generates a integer division problem and presents it 
void divisionTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;

	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		if (firstIntNumber >= secondIntNumber)
		{
			answer = firstIntNumber / secondIntNumber;
			cout << "What is " << firstIntNumber << "/" << secondIntNumber << " in integers?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);

		}
		else
		{
			answer = secondIntNumber / firstIntNumber;
			cout << "What is " << secondIntNumber << "/" << firstIntNumber << " in integers?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);
		}
	}

	userScore(currentScore);
}
//Generates a decimal division problem and presents it 
void divisionTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();
		if (firstFloatNumber >= secondFloatNumber)
		{
			answer = (firstFloatNumber / secondFloatNumber);
			cout << "What is " << firstFloatNumber << "/" << secondFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
		else
		{
			answer = (secondFloatNumber / firstFloatNumber);
			cout << "What is " << secondFloatNumber << "/" << firstFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
	}
	userScore(currentScore);
}
//Generates a integer remainder problem and presents it 
void remainderTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;

	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		if (firstIntNumber >= secondIntNumber)
		{
			answer = firstIntNumber % secondIntNumber;
			cout << "What is the integer remainder of " << firstIntNumber << "/" << secondIntNumber << " ?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);

		}
		else
		{
			answer = secondIntNumber % firstIntNumber;
			cout << "What is the integer remainder of " << secondIntNumber << "/" << firstIntNumber << " ?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);
		}
	}

	userScore(currentScore);
}

//Generates a decimal remainder problem and presents it 
void remainderTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();
		if (firstFloatNumber >= secondFloatNumber)
		{
			answer = fmod(firstFloatNumber, secondFloatNumber);
			cout << "What is the remainder of " << firstFloatNumber << "/" << secondFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
		else
		{
			answer = fmod(secondFloatNumber, firstFloatNumber);
			cout << "What is the remainder of " << secondFloatNumber << "/" << firstFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
	}
	userScore(currentScore);
}

// I wanted to cry when I got to your last several functions. So I have to stop reading them
/*
*  You dont want to ever repeat code but look how many times you used the genFloat(); and genInt() over and over.
*   There should be a way to simplfy all of thise.
*
*/
