
#ifndef VCALLSETTINGS_PAN_H
#define VCALLSETTINGS_PAN_H

/** vcallsettings application panic codes */
enum TvcallsettingsPanics
	{
	EvcallsettingsUi = 1
	// add further panics here
	};

inline void Panic(TvcallsettingsPanics aReason)
	{
	_LIT(applicationName,"vcallsettings");
	User::Panic(applicationName, aReason);
	}

#endif // VCALLSETTINGS_PAN_H
