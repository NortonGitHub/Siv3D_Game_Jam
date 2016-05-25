#pragma once

class SettingBase {
public:
protected:
	struct PARTICIPANT {
		int padNum;
		int orderNum;

		bool operator==(const PARTICIPANT &p) {
			return(this->padNum == p.padNum);
		}
	};



};