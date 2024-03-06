#include <iostream>
#include <string>
#include <cmath>

using namespace std;

enum enQuestionsLevel {Easy = 1, Medium = 2, Hard = 3, Mix = 4};
enum enOpType {Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5};

struct stQuestion
{
	int Number1 = 0, Number2 = 0;
	enOpType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int UserAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOpType OpType;
	short PlayerRightAnswers = 0;
	short PlayerWrongAnswers = 0;
	bool isPass = false;
};

string GetOpTypeSymbol(enOpType OpType)
{
	string Level[5] = { "+", "-", "*", "/", "Mix"};
	return Level[OpType - 1];
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string Level[4] = { "Easy", "Medium", "Hard", "Mix"};
	return Level[QuestionLevel - 1];
}

int RandomNumber(int from, int to)
{
	int Num = rand() % (to - from + 1) + 1;
	return Num;
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How Many Questions do you want to answer? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;
	do {
		cout << "Enter Questions Level: [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);
	return (enQuestionsLevel)QuestionLevel;
}

enOpType ReadOperationType()
{
	short OpType = 0;
	do {
		cout << "Enter Operation Type: [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);
	return (enOpType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOpType OpType)
{
	switch (OpType)
	{
	case enOpType::Add:
		return Number1 + Number2;
	case enOpType::Sub:
		return Number1 - Number2;
	case enOpType::Mult:
		return Number1 * Number2;
	case enOpType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOpType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOpType::MixOp)
	{
		OpType = (enOpType)RandomNumber(1, 4);
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionsLevel::Medium:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionsLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2;
	cout << "\n__________" << endl;
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	while (cin.fail())
	{
		cin.clear();

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cin >> Answer;
	}

	return Answer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].UserAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.PlayerWrongAnswers++;

		system("color 4f");
		cout << "Wrong Answer :-( \n";
		cout << "The right answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.PlayerRightAnswers++;

		system("color 2f");
		cout << "Right Answer :-) \n";
	}
	cout << endl;

}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].UserAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.PlayerRightAnswers >= Quizz.PlayerWrongAnswers);
}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "FAIL :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "_________________________________\n\n";
	cout << "Final Result is " << GetFinalResultText(Quizz.isPass);
	cout << "\n_________________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type     : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.PlayerRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.PlayerWrongAnswers << endl;
	cout << "_________________________________\n\n";
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);

	PrintQuizzResult(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do {

		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
