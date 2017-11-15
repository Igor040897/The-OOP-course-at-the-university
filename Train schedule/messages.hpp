// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const TrainMustBe = "Train must be";
	const char * const RouteMustBe = "Route must be";
	const char * const StationMustBe = "Station must be";
	const char * const NotEnoughFreePlatforms = "Not enough free platforms";
	const char * const AllStationsWithRoutes = "In all stations there are routes";
	const char * const NoIntersectionsOfRoutes = "Stations doesn`t connected more than two routes";
	const char * const NegativeID = "ID must be positive";
	const char * const NegativeCountPassengers = "Count Passengers must be positive";
	const char * const FewStations = "Stations must be greater than 5";
	const char * const FewRoute = "Route must be greater than 5";
	const char * const TimeIsNotValid = "Error: time is not valid!";
	const char * const NameEmpty= "Name empty";
	const char * const CountPlatformsMustBePositive = "Count platforms must be positive";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_