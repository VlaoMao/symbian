
#ifndef UI_PAN_H
#define UI_PAN_H

/** ui application panic codes */
enum TuiPanics
	{
	EuiUi = 1
	// add further panics here
	};

inline void Panic(TuiPanics aReason)
	{
	_LIT(applicationName,"ui");
	User::Panic(applicationName, aReason);
	}

#endif // UI_PAN_H
