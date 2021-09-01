#pragma once

namespace chess {

	enum class BorderColorCell {
		GREEN,
		RED,
		BLUE,
		WHITE
	};

	enum class TeamColor {
		WHITE,
		BLACK
	};

	enum class StateMouse {
		FREE,
		PUSH,
		RELEASE
	};

	enum class KillingKing {
		WHITE,
		BLACK,
		LIVE
	};

	enum class CurrentTeamMove {
		WHITE,
		BLACK
	};
}