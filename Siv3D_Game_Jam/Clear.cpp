#include "Clear.h"
#include "Game.h"
#include "Setting.h"

#define ELLIPSE_WIDTH 35
#define ELLIPSE_HEIGHT 50
#define BOX_LENGTH 90
#define BOX_POS_Y 210
#define CHOICES_WIDTH 160
#define CHOICES_HEIGHT 80
#define CHOICES_POS_Y 360

const Ellipse Clear::eggs[4] = {
	Ellipse::Ellipse(Vec2(155,100),Vec2(ELLIPSE_WIDTH,ELLIPSE_HEIGHT)),
	Ellipse::Ellipse(Vec2(265,100),Vec2(ELLIPSE_WIDTH,ELLIPSE_HEIGHT)),
	Ellipse::Ellipse(Vec2(375,100),Vec2(ELLIPSE_WIDTH,ELLIPSE_HEIGHT)),
	Ellipse::Ellipse(Vec2(485,100),Vec2(ELLIPSE_WIDTH,ELLIPSE_HEIGHT))
};

const Rect Clear::framesOfChoices[2] = {
	Rect::Rectangle(Point(110,CHOICES_POS_Y),Point(CHOICES_WIDTH,CHOICES_HEIGHT)),
	Rect::Rectangle(Point(370,CHOICES_POS_Y),Point(CHOICES_WIDTH,CHOICES_HEIGHT))
};

const Rect Clear::framesOfNum[4] = {
	Rect::Rectangle(Point(110, BOX_POS_Y), Point(BOX_LENGTH, BOX_LENGTH)),
	Rect::Rectangle(Point(220, BOX_POS_Y), Point(BOX_LENGTH, BOX_LENGTH)),
	Rect::Rectangle(Point(330, BOX_POS_Y), Point(BOX_LENGTH, BOX_LENGTH)),
	Rect::Rectangle(Point(440, BOX_POS_Y), Point(BOX_LENGTH, BOX_LENGTH))
};

const String Clear::strOfChoices[2] = {
	String::String(L"ë±ÇØÇÈ"),
	String::String(L"èIóπÇ∑ÇÈ")
};

std::vector<int> Clear::playerWinningNum;

Clear::Clear(int numOfparticipants, int winnerNum)
	: eggNum(28,L"ÇlÇr ÇoÉSÉVÉbÉN", FontStyle::BitmapBold),
	choices(22,L"ÇlÇr ÇoÉSÉVÉbÉN", FontStyle::BitmapBold)
{
	if (playerWinningNum.empty()) {
		playerWinningNum.resize(numOfparticipants);
		for (auto &p : playerWinningNum) {
			p = 0;
		}
	}

	winningNum = Font::Font(30, Typeface::Heavy, FontStyle::Outline);
	_numOfParticipant = numOfparticipants;
	choicingStatus = "Left";

	increaseWinningNum(winnerNum);
}


Clear::~Clear()
{
}

SceneBase* Clear::update()
{
	int selecting = 0;

	SceneBase* beforeScene = this;

	//for (int i = 0; i < GamePadManager::countGamepadConnecting(); i++) {
		for (int i = 0; i < 16; i++) {
			choicingStatus = GamePadManager::getClickedPov(i, choicingStatus);

			selecting = changeChoicesIcon(choicingStatus);

			if (GamePadManager::isClickedAnyButton(i)) {
				beforeScene = changeScene(selecting);
			}
		}
	//}
	return beforeScene;
}

void Clear::draw()
{
	for (int i = 0; i < _numOfParticipant; i++) {
		eggs[i].draw(selectBodyColor(i));
//		eggNum(i + 1).drawCenter(eggs[i].center);
		framesOfNum[i].draw(selectBodyColor(i));
		winningNum(playerWinningNum[i]).drawCenter(framesOfNum[i].center);
	}

	for (int i = 0; i < 2; i++) {
		framesOfChoices[i].draw(frameOfChoicesCol[i]);
		choices(strOfChoices[i]).drawCenter(framesOfChoices[i].center);
	}

}

void Clear::increaseWinningNum(int winnerNum)
{
	for ( int i = 0; i < _numOfParticipant;i++) {
		if (i == winnerNum) {
			playerWinningNum[i]++;
			break;
		}
	}
}

SceneBase * Clear::changeScene(int request)
{
	if (request == 1) {
		return new Game();
	}
	else if (request == 2) {
		playerWinningNum.clear();
		playerWinningNum.shrink_to_fit();
		return new Setting();
	}
	return this;
}

int Clear::changeChoicesIcon(std::string _padPovStatus)
{
	if (_padPovStatus == "Left") {
		frameOfChoicesCol[0] = Palette::Yellow;
		frameOfChoicesCol[1] = Palette::Gray;
		return 1;
	}
	else if (_padPovStatus == "Right") {
		frameOfChoicesCol[0] = Palette::Gray;
		frameOfChoicesCol[1] = Palette::Yellow;
		return 2;
	}
	return 0;
}
