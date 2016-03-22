#pragma once

class SettingBase {
public:
protected:
	struct PARTICIPANT {
		int num;

		bool operator==(const PARTICIPANT &p) {
			return(this->num == p.num);
		}
	};
};