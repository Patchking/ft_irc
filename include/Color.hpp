#pragma once
namespace dtg {
	enum SEC {};
	enum FIR {};
	enum BLACK {};
	enum RED {};
	enum GREEN {};
	enum BROWN {};
	enum BLUE {};
	enum PURPLE {};
	enum CYAN {};
	enum GRAY{};
#if 0
	enum GRAY {};
	enum LRED {};
	enum LGREEN {};
	enum YELLOW {};
	enum LBLUE {};
	enum LPURPLE {};
	enum LCYAN {};
	enum WHITE {};
#endif
	enum NONE {};
	enum NONE0 {};
	enum NONE1 {};
	enum NORMAL {};//0
	enum BOLD {};//1
	enum UNDER {};//4
	enum BLINK {};//5
	enum REVERSE {};//7

	template<class, class>
	struct color_internal;

	template<>
	struct color_internal<FIR, BLACK> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'), fg2('['), fg3('3'), fg4('0') {
		}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, BLACK> {
		color_internal():bg1(';'), bg2('4'), bg3('0'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};

	template<>
	struct color_internal<FIR, RED> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('3'),fg4('1'){}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, RED> {
		color_internal():bg1(';'),bg2('4'),bg3('1'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};

	template<>
	struct color_internal<FIR, GREEN> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('3'),fg4('2'){}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, GREEN> {
		color_internal():bg1(';'),bg2('4'),bg3('2'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};

	template<>
	struct color_internal<FIR, BROWN> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('3'),fg4('3'){}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, BROWN> {
		color_internal():bg1(';'),bg2('4'),bg3('3'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};
	template<>
	struct color_internal<FIR, BLUE> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('3'),fg4('4'){}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, BLUE> {
		color_internal():bg1(';'), bg2('4'), bg3('4'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};
	template<>
	struct color_internal<FIR, PURPLE> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('3'),fg4('5'){}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, PURPLE> {
		color_internal():bg1(';'), bg2('4'), bg3('5'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};
	template<>
	struct color_internal<FIR, CYAN> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('3'),fg4('6'){}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, CYAN> {
		color_internal():bg1(';'), bg2('4'), bg3('6'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};
	template<>
	struct color_internal<FIR, GRAY> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('3'),fg4('7'){}
		const char fg1;
		const char fg2;
		const char fg3;
		const char fg4;
	};

	template<>
	struct color_internal<SEC, GRAY> {
		color_internal():bg1(';'), bg2('4'), bg3('7'){}
		const char bg1;
		const char bg2;
		const char bg3;
	};
#if 0
	template<>
	struct color_internal<GRAY> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '0'};
	};

	template<>
	struct color_internal<SEC, GRAY> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '0'};
	};

	template<>
	struct color_internal<LRED> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '1'};
	};
	template<>
	struct color_internal<SEC, LRED> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '1'};
	};
	template<>
	struct color_internal<LGREEN> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '2'};
	};
	template<>
	struct color_internal<SEC, LGREEN> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '2'};
	};
	template<>
	struct color_internal<YELLOW> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '3'};
	};
	template<>
	struct color_internal<SEC, YELLOW> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '3'};
	};
	template<>
	struct color_internal<LBLUE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '4'};
	};
	template<>
	struct color_internal<SEC, LBLUE> {
		/*private:*/ const char fg[5] = {';', '1', ';', '4', '4'};
	};

	template<>
	struct color_internal<LPURPLE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '5'};
	};

	template<>
	struct color_internal<SEC, LPURPLE> {
		/*private:*/ const char bg[5] = {';', '1', ';', '4', '5'};
	};

	template<>
	struct color_internal<LCYAN> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '6'};
	};

	template<>
	struct color_internal<SEC, LCYAN> {
		/*private:*/ const char fg[5] = {';', '1', ';', '4', '6'};
	};

	template<>
	struct color_internal<WHITE> {
		operator const char *() const {
			return fg;
		}
		/*private:*/ const char fg[6] = {'\033', '[', '1', ';', '3', '7'};
	};

	template<>
	struct color_internal<SEC, WHITE> {
		/*private:*/ const char fg[5] = {';', '1', ';', '4', '7'};
	};
#endif

	template<>
	struct color_internal<FIR, NORMAL> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('0'){}
		const char fg1;
		const char fg2;
		const char fg3;
	};

	template<>
	struct color_internal<FIR, BOLD> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('1'){}
		const char fg1;
		const char fg2;
		const char fg3;
	};

	template<>
	struct color_internal<FIR, UNDER> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('4'){}
		const char fg1;
		const char fg2;
		const char fg3;
	};

	template<>
	struct color_internal<FIR, BLINK> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('5'){}
		const char fg1;
		const char fg2;
		const char fg3;
	};

	template<>
	struct color_internal<FIR, REVERSE> {
		operator const char *() const {
			return &fg1;
		}
		color_internal():fg1('\033'),fg2('['),fg3('7'){}
		const char fg1;
		const char fg2;
		const char fg3;
	};

	template<>
	struct color_internal<SEC, NORMAL> {
		color_internal():st1(';'), st2('0') {}
		const char st1;
		const char st2;
	};

	template<>
	struct color_internal<SEC, BOLD> {
		color_internal():st1(';'), st2('1') {}
		const char st1;
		const char st2;
	};

	template<>
	struct color_internal<SEC, UNDER> {
		color_internal():st1(';'), st2('4') {}
		const char st1;
		const char st2;
	};

	template<>
	struct color_internal<SEC, BLINK> {
		color_internal():st1(';'), st2('5') {}
		const char st1;
		const char st2;
	};

	template<>
	struct color_internal<SEC, REVERSE> {
		color_internal():st1(';'), st2('7') {}
		const char st1;
		const char st2;
	};
/*
	template<>
	struct color_internal<FIR, SEC> {
		operator const char *() const {
			return bg;
		}
		const char bg[2] = {'\033', '['};
	};
*/
	template<>
	struct color_internal<SEC, NONE>{};

	template<>
	struct color_internal<SEC, NONE0>{};

	template<>
	struct color_internal<SEC, NONE1>{};

	template<class fg, class bg = NONE, class st = NONE0, class st2 = NONE1>
	struct color
	: color_internal<FIR, fg>
	, color_internal<SEC, bg>
	, color_internal<SEC, st>
	, color_internal<SEC, st2> {
		color():end1('m'), end2('\0') {}
		const char end1;
		const char end2;
	};

}//namespace dtg
