#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, VeryHard = 4, MixLevel = 5 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
	long long Number1 = 0;
	long long Number2 = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	long long PlayerAnswer = 0;
	long long CorrectAnswer = 0;
	bool ResultAnswer = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestion = 0;
	enQuestionsLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = false;
};

short ReadHowManyQuestion()
{
	short NumberOfQuestions = 0;
	do
	{
		cout << "How Many Questions Do You Want To Answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Questions Level [1], Easy, [2] Med, [3] Hard, [4] VeryHard, [5] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 5);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;
	do
	{
		cout << "Enter Operation Type [1], Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void SetScreenColor(bool Color)
{
	if (Color)
	    system("color 2F");
	else
	{
	   system("color 4F");
	   cout << "\a";
	}

}

string GetNameQuestionLevel(enQuestionsLevel Name)
{
	string ArrQuestionLevel[5] = { "Easy", "Med", "Hard", "VeryHard", "Mix"};
	return ArrQuestionLevel[Name - 1];
}

string GetNameQuestionType(enOperationType Name)
{
	string ArrOperationType[5] = { "Add", "Sub", "Mul", "Div", "Mix"};
	return ArrOperationType[Name - 1];
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return  "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "+";
	}
}

long long SimpleCalculater(long long Num1, long long Num2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Num1 + Num2;
	case enOperationType::Sub:
		return Num1 - Num2;
	case enOperationType::Mul:
		return Num1 * Num2;
	case enOperationType::Div:
		return Num1 / Num2;
		default:
			return Num1 + Num2;
	}
}

enOperationType GetRandomOperationType()
{
	short Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenarateQuestion(enQuestionsLevel QuestionLevel , enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::MixLevel)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 4);
	}
	
	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:

		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		
		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	case enQuestionsLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::Hard:

		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::VeryHard:

		Question.Number1 = RandomNumber(1000, 5000);
		Question.Number2 = RandomNumber(1000, 5000);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	}
	return Question;
}

stQuizz GenarateQuizzQuestions(stQuizz& Quizz)
{

	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
	{
		Quizz.QuestionList[QuestionNumber] = GenarateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
	return Quizz;
}

long long PlayerAnswer()
{
	long long PlayerAnswer = 0;
	cin >> PlayerAnswer;
	return PlayerAnswer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].ResultAnswer = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :- (\n";
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;

	}
	else
	{
		Quizz.QuestionList[QuestionNumber].ResultAnswer = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].ResultAnswer);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass\n";
	else
		return "Fail\n";
}

void PrintQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << "____________\n";
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
	{
		PrintQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = PlayerAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

void PrintQuizzResult(stQuizz Quizz)
{

	cout << "\n_______________________________\n\n";
	cout << " Final Results is " << GetFinalResultsText(Quizz.IsPass);
	cout << "\n_______________________________\n\n";

	cout << "Number Of Question     :  " << Quizz.NumberOfQuestion << endl;
	cout << "Question Level         :  " << GetNameQuestionLevel(Quizz.QuestionLevel) << endl;
	cout << "OpType                 :  " << GetNameQuestionType(Quizz.OpType) << endl;
	cout << "Number Of Right Answer :  " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answer :  " << Quizz.NumberOfWrongAnswers << endl;
	cout << "_______________________________\n\n";

	this_thread::sleep_for(chrono::milliseconds(750));

	SetScreenColor(Quizz.IsPass);
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestion = ReadHowManyQuestion();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOperationType();

	GenarateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResult(Quizz);
}

void RestScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{

	char PlayAgain = 'Y';

	do
	{
		RestScreen();
		PlayMathGame();

		cout << "\n" << "Do You Wnat Play Again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

}
