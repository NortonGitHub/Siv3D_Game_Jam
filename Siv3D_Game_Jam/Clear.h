#pragma once
#include "SceneBase.h"
#include "VisualColorBase.h"

class Clear :
	public SceneBase , VisualColorBase ,GamePadManager
{
public:
	Clear(int numOfparticipants ,int winnerNum );
	~Clear();

	SceneBase* update() override;
	void draw() override;

private:
	static std::vector<int> playerWinningNum;

	const static Ellipse eggs[4];
	const static Rect framesOfNum[4];
	const static Rect framesOfChoices[2];

	const static String strOfChoices[2];
	
//	const static Font eggNums[4];
	const Font eggNum;
	Font winningNum;
	const Font choices;

	int _numOfParticipant;

	Color frameOfChoicesCol[2];

	std::string choicingStatus;

	int changeChoicesIcon(std::string _padPovStatus);
	void increaseWinningNum(int winnerNum);

	SceneBase* changeScene(int request);

};

